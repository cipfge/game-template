# Game

2D game written in C++ with OpenGL

## Linux
Clone and update the submodules
```bash
git clone [url]
git submodule update --init --recursive
```

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
cd game
mkdir build
cd build
cmake -G Ninja ..
ninja
```

## Windows
Install [git-scm](https://git-scm.com/)

Clone and update the submodules
```
git clone [url]
git submodule update --init --recursive
```

Open the **game** directory in ***Visual Studio***

Don't forget to copy all assets to **build** directory
