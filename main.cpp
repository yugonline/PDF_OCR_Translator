#include <iostream>
#include <vector>
#include "tesseract/baseapi.h"
#include <mupdf/fitz.h>
#include "leptonica/allheaders.h"
#include <cstdlib>
#include <array>

using namespace std;


//This is not working yet.
std::string run_marian_decoder(const std::string &text_to_translate) {
    std::string script = R"(
    $model_dir = "opus/"
    $echoString = ")" + text_to_translate + R"("
    $executable = "./path/to/opus-dev/build/opus-decoder"
    $arguments = "-c $($model_dir)/config.yml"

    echo $echoString | & $executable $arguments
    )";

    std::string command = "powershell.exe -Command \"" + script + "\"";
    std::array<char, 128> buffer{};
    std::string result;
    FILE *pipe = _popen(command.c_str(), "r");
    if (!pipe) {
        throw std::runtime_error("_popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
        result += buffer.data();
    }
    _pclose(pipe);

    return result;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " pdfPath" << endl;
        return 1;
    }

    std::locale::global(std::locale("en_US.UTF-8"));

    tesseract::TessBaseAPI tess;
    tess.Init("tessdata/", "deu+en+equ", tesseract::OEM_DEFAULT);
    tess.SetPageSegMode(tesseract::PSM_AUTO);

    fz_context *ctx = fz_new_context(NULL, NULL, FZ_STORE_UNLIMITED);
    fz_register_document_handlers(ctx);

    fz_document *doc = fz_open_document(ctx, argv[1]);
    if (!doc) {
        cerr << "Error: could not load PDF file " << argv[1] << endl;
        fz_drop_context(ctx);
        return 1;
    }

    int numPages = fz_count_pages(ctx, doc);
    cout << "Number of pages: " << numPages << endl;

    vector<string> results;
    results.resize(numPages);

    for (int i = 0; i < numPages; ++i) {
        string imagePath = "pages/page-" + to_string(i + 1) + ".png";

        fz_pixmap *pixmap = fz_new_pixmap_from_page_number(ctx, doc, i, fz_identity, fz_device_rgb(ctx), 0);
        fz_save_pixmap_as_png(ctx, pixmap, imagePath.c_str());
        fz_drop_pixmap(ctx, pixmap);

        PIX *image = pixRead(imagePath.c_str());

        tess.SetImage(image);

        char *text = tess.GetUTF8Text();
        results[i] = text;

        delete[] text;
        pixDestroy(&image);
    }

    for (int i = 0; i < numPages; ++i) {
        std::string translated_text = translate_text(results[i]);
        cout<< "ORIGINAL: \n";
        cout << "Page " << i + 1 << ":\n" << results[i] << endl;
        cout<< "------------------------------------------------\n";
        cout<< "TRANSLATED: \n";
        cout << "Page " << i + 1 << ":\n" << translated_text << endl;
    }

    tess.End();
    fz_drop_document(ctx, doc);
    fz_drop_context(ctx);
    return 0;
}
