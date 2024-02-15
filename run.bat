@echo off
set /p "choice=Do you allow this program to Fetch Raylib content from github to properly build the program[Y/N] "
if /i "%choice%"=="Y" (
  mkdir build
  cd build
  cmake -DPROJECT_NAME=gui ..
  cmake --build .
  cd Debug
  gui
  cd ../..
) else (
  echo The project will not build then!
  echo Canceling project building process...
)
