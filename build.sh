mkdir build
cd build
rm -rf ./*
cmake ../
make
mv tetris ../
cd ../
rm -rf ./build