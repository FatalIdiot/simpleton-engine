rmdir /s /q "./build"
cmake -S . -B build
cmake --build build
cd build/sandbox/Debug
sandbox
cd ../../..