# Linux
## Dependencies
SFML 2.5 or greater is needed to compile and run the game. To install it in Ubuntu:

```
apt-get install libsfml-dev
```

In Arch:

```
pacman -S sfml 
```

To be able to build the sources, make sure you have CMake installed, as well as a C++ compiler with C++11 support.

## Compiling
To compile the game in release mode, cd into the game's root directory, and then run the following commands:

```
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
```

The executable for the game as well as the required libraries will appear in the build directory.
