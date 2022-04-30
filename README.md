# epicgl
A "basic" OpenGL program made in C++.

# REQUIREMENTS
Since some computers dont have certain dependencies, you might have to install GLEW, GLU, GLUT and other libraries. This command should do the work:<br>
```sudo apt-get install -y libglfw3-dev libgl1-mesa-dev libglu1-mesa-dev libglew-dev libsoil-dev freeglut3-dev```

## Controls
Controls like rotation speed, "shading" or moving around are shown when executing it on the terminal.

## Compilation command
```g++ main.cpp -o EpicGL_Linux64 -static-libstdc++ -static-libgcc -lGLEW -lGLU -lSOIL -lglut -lGL```
<br>
Remember to compile under Linux, for **amd64** and have the required libraries!<br>
For more info on compiling, message me. Make an issue to do so, it's the fastest way to reach.
