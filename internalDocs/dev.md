# Developer Notes

## Commands

### Build Command

NOTE: Before building, see dependencies section for installing outside packages

```bash
git clone https://github.com/IvanW5X/audio-prod.git
cd audio-prod
mkdir build
cmake -G "MinGW Makefiles" -S . -B ./build
cmake --build build
```

This should create the executable, so you can run the program using

```bash
./build/audioprod.exe
```

### Testing

To build and run test executables, run

```bash
cmake -S . -B ./build -DENABLE_TESTING=ON

# To run
cd build; ctest; cd ..
```

### Handle Dependencies

In progress...
