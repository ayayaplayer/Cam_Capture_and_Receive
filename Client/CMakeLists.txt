cmake_minimum_required(VERSION 3.0)
project(CaptureAndSendImage)

set(TIFF_INCLUDE_DIR "D:/Programming/vcpkg-master/installed/x64-windows/include")
set(TIFF_LIBRARY "tiff.lib")

set(ZLIB_INCLUDE_DIR "D:/Programming/vcpkg-master/installed/x64-windows/include")
set(ZLIB_LIBRARY "zlib.lib")

# Найти необходимые пакеты
find_package(OpenCV REQUIRED)
find_package(CURL REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(TIFF REQUIRED)

# Добавить исполняемый файл
add_executable(capture_and_send_image 
    D:/Programming/Client/src/PictureCapture.cpp 
    D:/Programming/Client/src/base64.cpp)

# Включить директории заголовочных файлов для OpenCV, CURL, nlohmann/json и base64.h
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${CURL_INCLUDE_DIRS})
include_directories(${nlohmann_json_INCLUDE_DIRS})
include_directories(${TIFF_INCLUDE_DIR})
include_directories(D:/Programming/Client/include)  # Путь к директории, содержащей base64.h

# Целевая библиотека для исполняемого файла
target_link_libraries(capture_and_send_image 
    ${OpenCV_LIBS} 
    ${CURL_LIBRARIES} 
    nlohmann_json::nlohmann_json 
    ${TIFF_LIBRARIES})
