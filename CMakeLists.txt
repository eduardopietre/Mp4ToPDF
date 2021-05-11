cmake_minimum_required(VERSION 3.8)
project("Mp4ToPDF")

add_compile_definitions(GPU_SSIM)

file(GLOB_RECURSE Mp4ToPDF_SOURCES CONFIGURE_DEPENDS "src/*.cpp")
file(GLOB_RECURSE Mp4ToPDF_HEADERS CONFIGURE_DEPENDS "src/*.h")

set(OpenCV_FOUND 1)
set(OpenCV_DIR D:/InPath/opencv/building_gpu)
find_package(OpenCV REQUIRED PATHS D:/InPath/opencv/building_cpu NO_DEFAULT_PATH)
include_directories(${OpenCV_INCLUDE_DIRS})

# Main executable, the program itself.
add_executable(Mp4ToPDF ${Mp4ToPDF_SOURCES})
target_link_libraries(Mp4ToPDF PRIVATE ${OpenCV_LIBS})


# Executable with tests. Exclude Main.cpp.
file(GLOB_RECURSE Mp4ToPDF_Testing_SRC CONFIGURE_DEPENDS "src/*.cpp" "tests/*.cpp")
file(GLOB_RECURSE Mp4ToPDF_Testing_HEADERS CONFIGURE_DEPENDS "src/*.h" "tests/*.h")
list(FILTER Mp4ToPDF_Testing_SRC EXCLUDE REGEX "src/Main.cpp" )

add_executable(Mp4ToPDF_Testing ${Mp4ToPDF_Testing_SRC})
target_link_libraries(Mp4ToPDF_Testing PRIVATE ${OpenCV_LIBS})
