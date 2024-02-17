echo -n "Do you allow this program to Fetch Raylib content from github to properly build the program[Y/N] " 
read choice

if [ "$choice" = "Y" ]; then
  echo -n "What do you want to name the project: "
  read name
  mkdir build
  cd build
  cmake -DPROJECT_NAME=$name ..
  make
  ./$name
  cd ..
else
  echo "The project will not build then!"
  echo "Canceling project building process..."
fi
