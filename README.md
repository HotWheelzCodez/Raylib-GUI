# Raylib-GUI

Raylib-GUI is an immediate GUI library for C++, built on top of [Raylib](https://github.com/raysan5/raylib). It aims to provide a simple-to-use and highly customizable GUI solution, resembling a CSS style of coding for creating various styles for different components.

## Why Raylib-GUI?

While there are existing options like raygui, Raylib-GUI distinguishes itself by offering a more modern and clean user interface design. It is designed to facilitate the development of visually appealing GUIs with ease.

## Getting Started

Raylib-GUI requires the use of CMake for building and compiling. The project does not build into a separate library but compiles directly alongside your project.

### Building and Running

1. If you are on a Windows machine, run `run.bat`. 
2. If you are on a Unix-based system, execute `run.sh`.

    **Note:** Before executing `run.sh`, ensure that it has executable permissions. If not, you may need to run `chmod +x run.sh` in your terminal. If `chmod +x` doesn't work, you can create the executable file manually from the text inside `run.sh`.

These scripts will automatically fetch Raylib, build it along with your project (including the GUI), link Raylib, and then run your project.


## Acknowledgements

The `CMakeLists.txt` file used in this project was originally obtained from [Sas Luca](https://github.com/SasLuca) and has been modified to suit the requirements of this project. You can find the original file/project [here](https://github.com/SasLuca/raylib-cmake-template).

## Contributing

Contributions to Raylib-GUI are highly encouraged. Whether it's bug fixes, new features, or improvements, everyone is welcome to contribute to this project.

## License

Raylib-GUI is open-source software - please just don't write it off as your own project.
