# Raylib-GUI
This is a simple to use and very customizable immediate GUI using raylib in C++ with the intent to resemble
a CSS style of coding when creating different styles for different components. While there are other options
primarly raygui I wanted to make something more modern looking as far as UI, this project was started because
I wanted a 'cleaner' (in my opinion) GUI.

This project does require the use of CMake to build and compile, this does not build into a library, it just
compiles right along with your project. If you are on Windows; run the 'run.bat' file, if you are on Unix 
machine; then run the 'run.sh'. Both of these files will fetch raylib, build raylib and your project (and the gui),
then link raylib and, then run the project. The CMakeLists.txt file was not fully mine, but obtained from: [Sas Luca](https://github.com/SasLuca),
I have modified the file to work with C++ and the project directory, this is the [original](https://github.com/SasLuca/raylib-cmake-template) file / project.

You do not have to give any credit to this project, however please do not right it off as your own, any one is more than welcome to contribute to this project.
I hope someone else is looking for a GUI project like this and will find use in it.
