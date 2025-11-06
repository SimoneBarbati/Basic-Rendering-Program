
# Basic Rendering Program

This is a Basic Rendering Program written in c++ using the GLFW library to handle window creation and input, and OpenGL to handle the rendering.

# Install dependencies
- [GLAD](https://glad.dav1d.de/) (Download the glad library for OpenGL core 3.3
  be sure to move the contents to your include and src dirs or the system include and src)

```bash
sudo apt install git cmake libglfw3-dev libglm-dev
```

## Run Locally

Clone the project

```bash
git clone https://github.com/SimoneBarbati/Basic-Rendering-Program BRP
```

Go to the project directory

```bash
cd BRP
```

Create build directory

```bash
mkdir build && cd build
```

Build (CMake)

```bash
cmake ..
cmake --build .
```
