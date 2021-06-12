# epicgl
A "basic" OpenGL program made in C++.
## MOVED TO https://davidlao.ro.lt/epicgl PLEASE GO THERE!

# REQUIREMENTS
Since some computers dont have GLU apparently, you might have to install GLEW, GLU, GLUT and other libraries. This command should do the work:
```sudo apt-get install -y libglfw3-dev libgl1-mesa-dev libglu1-mesa-dev libglew-dev libsoil-dev freeglut3-dev```

## Controls
Controls like rotation speed, "shading" or moving around are available when executing it on the terminal.

## Compiling
```g++ main.cpp -o EpicGL_Linux64 -static-libstdc++ -static-libgcc -lGLEW -lGLU -lSOIL -lglut -lGL```
<br>
Remember to compile in amd64 and have GLEW, GLUT, SOIL and GL libraries. Should be installable with the above command.<br>
For more info on compiling, message me. Make an issue to do so, it's the fastest way for me.
