# EXPERIEMENTAL PDF TRANSLATOR

## WORK IN PROGRESS!! 
### This project is still very much an idea than a full fledged prototype. But feel free to checkout and comment on my C++ code!!
### Any help would be much appreciated
Pre-reqs
- MNT Decoder or Marian Decoder
- A pretrained Translator model.
  - OpenMT Model zoo 
  - Helsinki Opus dataset trained models are good sources with almost 50+ BLEU score on some eval data
- C++ 17 Compiler
- Cmake
- A semi powerful system (Have only tested on a Windows Ryzen 5900 and Radeon 6900XT)
- Lots of patience (This project is definitely not a production ready project and won't be for quite some time.)

### How to Build On Windows
- Git clone the project
- `mkdir pages` (youll need it later)
- Install Tesseract-OCR from the Wizard UI AND Vcpkg (important for now; will try to fix this later)
- Move the tessdata folder from C:\Program Files\Tesseract-OCR\tessdata to /path/to/this/project/tessdata
- For now I am assuming you have Marian Decoder and Opus model
- Move marian decoder executable file and opus model directory also to the project top level
- mkdir build
- cd build
- `cmake ..`
- In Powershell run build/Release/PDF_OCR_Tesseract.exe /path/to/pdf
- For now you will only understand translated text on the Terminal But the idea is to regenerate a new Pdf with the original typeset intact
  - Thoughts on how to do this are
  - Integrate Mathpix for formulae etc (The original motivation for this was to read [Sabine Hossenfelder's PhD thesis](https://publikationen.ub.uni-frankfurt.de/opus4/frontdoor/deliver/index/docId/5305/file/HossenfelderSabine.pdf) which is in German)
  - Integrate other OCR/Translator libraries
  - Another major major motivation is to be able to use a Foundational model to compare the state of the art
    - My theory is that with improvements in Transformers and/or the new [Hyena arch](https://arxiv.org/pdf/2103.03404.pdf) it should be possible to do this much faster and shopping around for Kindle/Epub/Pdf books in different langauges will be a breeze! 
    - imagine the possibilities with onprem bulk translations!!