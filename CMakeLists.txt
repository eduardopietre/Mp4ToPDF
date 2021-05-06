cmake_minimum_required(VERSION 3.8)
project("Mp4ToPDF")

file (GLOB_RECURSE Mp4ToPDF_SOURCES CONFIGURE_DEPENDS "src/*.cpp")
file (GLOB_RECURSE Mp4ToPDF_HEADERS CONFIGURE_DEPENDS "src/*.h")

set(OpenCV_FOUND 1)
set(OpenCV_DIR D:/InPath/opencv/building_gpu)
find_package(OpenCV REQUIRED PATHS D:/InPath/opencv/building_cpu NO_DEFAULT_PATH)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(Mp4ToPDF ${Mp4ToPDF_SOURCES})
target_link_libraries(Mp4ToPDF PRIVATE ${OpenCV_LIBS})
