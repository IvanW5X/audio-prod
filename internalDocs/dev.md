# Developer Notes

## Commands

### Build Command

NOTE: Before building, see dependencies section for installing outside packages

```bash
git clone https://github.com/IvanW5X/audio-prod.git
cd audio-prod
mkdir build
cmake -G "MinGW Makefiles" -S . -B ./build

# This should create the executable
cmake --build build
```

### Run Command

```bash
./build/audioprod.exe
```

### Testing

To build and run test executables, run

```bash
# Create build files with testing
cmake -S . -B ./build -DENABLE_TESTING=ON

# Compile exe and tests
cmake --build build --config Release --target all

# To run
cd build; ctest; cd ..
```

### Handle Dependencies

In progress...
