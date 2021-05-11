# Mp4ToPDF
A command line executable written in C++ that extracts 'unique' frames from a Mp4 video, exporting them as a PDF file.

## Building / Compilation
Although it should work (with small changes) in other OS, compilation as here described was only tested on Windows 10.  
Mp4ToPDF relies on OpenCV, that must be compile WITH CUDA ENABLED.  
What I did and advise:

### Building OpenCV
1. Make sure to have [Microsoft Visual Studio 2019](https://visualstudio.microsoft.com/), [CUDA](https://developer.nvidia.com/cuda-downloads) and [CMake](https://cmake.org/) installed and correctly in Windows PATH.  
2. Git clone the [OpenCV](https://github.com/opencv/opencv) repository (chose wisely, this will end up as a huge folder).  
3. Git clone the [OpenCV-Contrib](https://github.com/opencv/opencv_contrib) repository.  
4. Create a folder inside the clonned OpenCV folder. I opted for naming it 'building_gpu'.  
5. Open a terminal (CMD) and cd to this folder.  
6. Run CMake with `-D WITH_CUDA=ON` and `-D OPENCV_EXTRA_MODULES_PATH=[path to OpenCV-Contribe modules]`. In my case it was: `cmake -D WITH_CUDA=ON -D OPENCV_EXTRA_MODULES_PATH=D:/InPath/opencv_contrib/modules ..` .  
7. Inside the choosed folder, open `OpenCV.sln` in Visual Studio.  
8. Proceed to compile in Visual Studio. This may take a while, be sure to pick Debug or Release (or both).  
9. Add `[your building path]\install\x64\vc16\bin`,  `[your building path]\bin\Debug` and / or `[your building path]\bin\Release` to Windows Path.  
10. Done!  

### Building Mp4ToPDF
1. After cloning this repository, edit `CMakeLists.txt` at `set(OpenCV_DIR` and `find_package(OpenCV` to reflect your installation PATH.  
2. Open the folder in Visual Studio as a CMake project.
3. Compile it!

### Troubleshooting
- If it does not compile, you probably have not correctly setup CUDA or OpenCV. Make sure to compile OpenCV with CUDA support `WITH_CUDA=ON`.
- CUDA is hardware dependent, check CUDA documentation for help.

## Usage
When compiling Mp4ToPDF, `Mp4ToPDF.exe` will be created.  
This file can them be used through CMD as:  
`Mp4ToPDF.exe inputfile.mp4 24` where the second argument is the frame skip argument. 24 means checking every 24th frame.  

