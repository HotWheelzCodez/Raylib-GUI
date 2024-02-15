echo -n "Do you allow this program to Fetch Raylib content from github to properly build the program[Y/N] " 
read choice

if [ "$choice" = "Y" ]; then
  mkdir build
  cd build
  cmake -DPROJECT_NAME=gui ..
  make
  ./gui
  cd ..
else
  echo "The project will not build then!"
  echo "Canceling project building process..."
fi
