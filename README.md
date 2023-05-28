# Snake

Snake game written in C++ with OpenGL

## Linux

Install requirements
```bash
sudo apt install build-essential cmake ninja-build git
```

X11 dependencies
```bash
sudo apt install xorg-dev
```

Wayland dependencies
```bash
sudo apt install libwayland-dev libxkbcommon-dev wayland-protocols extra-cmake-modules
```

Compilation
```bash
cd snake
mkdir build
cd build
cmake -G Ninja ..
ninja
```

## Windows

Clone and update the submodules

Open the **snake** directory in ***Visual Studio***
