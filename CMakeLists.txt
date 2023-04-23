cmake_minimum_required(VERSION 3.25)

project(PDF_OCR_Translation)

if(MSVC)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
endif()

set(CMAKE_CXX_STANDARD 17)

# Set the appropriate runtime library
if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

# Force iterator debug level to 0
add_definitions(-D_ITERATOR_DEBUG_LEVEL=0)

# Add Tessdata files
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/tessdata DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Release)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/opus DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Release)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/marian DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Release)

# Use vcpkg integration
find_package(Threads REQUIRED)
find_package(tesseract CONFIG REQUIRED)
find_package(leptonica CONFIG REQUIRED)

# MuPDF paths
set(MUPDF_INCLUDE_DIR "C:/Users/yugsh/openSource/mupdf/include")
set(MUPDF_LIBRARY_DIR "C:/Users/yugsh/openSource/mupdf/platform/win32/x64/Release")

# Tesseract path
set(Tesseract_LIBRARY_DIR "C:/Users/yugsh/openSource/vcpkg/installed/x64-windows/lib")

# Add include directories
include_directories(
        ${MUPDF_INCLUDE_DIR}
        ${Tesseract_INCLUDE_DIRS}
        ${Leptonica_INCLUDE_DIRS}
)

add_executable(PDF_OCR_Translation main.cpp)

target_link_libraries(PDF_OCR_Translation
        Threads::Threads
        ${MUPDF_LIBRARY_DIR}/libmupdf.lib
        ${Tesseract_LIBRARY_DIR}/tesseract53.lib
        ${Tesseract_LIBRARY_DIR}/leptonica-1.83.1.lib
        )
