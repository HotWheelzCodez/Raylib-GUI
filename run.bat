@echo off
set /p "choice=Do you allow this program to Fetch Raylib content from github to properly build the program[Y/N] "
if /i "%choice%"=="Y" (
  set /p "name=What do you want to name the project: "
  mkdir build
  cd build
  cmake -DPROJECT_NAME=%name% ..
  cmake --build .
  cd Debug
  %name% 
  cd ../..
) else (
  echo The project will not build then!
  echo Canceling project building process...
)
