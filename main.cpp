#include"GL/glew.h"
#include"GL/glut.h"
#ifdef _WIN32
#else
#include <unistd.h>
#endif
#include <iostream>
#include <fstream>

#include <stdio.h>
#include "SOIL/SOIL.h"
float avt = 0.016; //Average time (0.016 = 60fps, 0.032 = 30fps)
int speed = -5; //Face rot.
int goUp, goLeft, goDown, goRight;
using namespace std;float dr=255.0;float dg=255.0;float db=255.0;float da=1.0;
int aa = 255;int ab = 255;int ac = 255;int ad = 255;
int ba = 255;int bb = 255;int bc = 255;int bd = 255;
int ca = 255;int cb = 255;int cc = 255;int cd = 255;

unsigned int microsecond = 1000000; //necessary for usleep in unix
GLuint texture; //face text bmp
GLuint core_program;

void NormalKeyHandler (unsigned char key, int x, int y)
{
    if (key == 'q'){
    if (dr==0.0){
    cout << "Changing background color to white..." << endl;
    dr=1.0;dg=1.0;db=1.0;
    }else{
    cout << "Changing background color to black..." << endl;
    dr=0.0;dg=0.0;db=0.0;
    }}
    else if (key == 'e'){
    exit(0);
    }else if (key == 'a'){
    cout << "\nABOUT:\n";
    cout << "See https://github.com/davidlao27/epicgl for info!\n";
    }else if (key == '1'){
        cout << "1 - Slow speed\n";speed = -2;
    }else if (key == '2'){
        cout << "2 - Medium speed\n";speed = -5;
    }else if (key == '3'){
        cout << "3 - 5V DC Motor speed\n";speed = -12;
    }else if (key == '4'){
        cout << "4 - Wheel\n";speed = -50;
    }else if (key == '5'){
        cout << "5 - Plane\n";speed = -100;
    }else if (key == '6'){
        cout << "6 - Slower than earth for sure\n";speed = -250;
    }else if (key == '7'){
        cout << "7 - Maximum point\n";speed = -500;
    }else if (key == 's'){
        if (cb == 255) {
        aa = 255;ab = 255;ac = 255;ad = 0;
        ba = 0;bb = 255;bc = 100;bd = 0;
        ca = 0;cb = 0;cc = 0;cd = 255;
        cout << "Shaders! AWESOME\n";
        }else{
        aa = 255;ab = 255;ac = 255;ad = 255;
        ba = 255;bb = 255;bc = 255;bd = 255;
        ca = 255;cb = 255;cc = 255;cd = 255;
        cout << "Original! AWESOME\n";
        }
    }
    else if (key == 'u'){goUp = 1;}
    else if (key == 'h'){goLeft = 1;}
    else if (key == 'j'){goDown = 1;}
    else if (key == 'k'){goRight = 1;}
}

//Personal note: Vertex goes clockwise
void display1(void) {
#ifdef _WIN32
cout << "Oops! This code wasnt intended for Windows.\n";
exit(-1);
#else
usleep(avt * microsecond);//sleeps for 16ms ~ 60fps
#endif
glClearColor(dr, dg, db, da); //BG Color

int image_width, image_height;
unsigned char* image = SOIL_load_image("face.png", &image_width, &image_height, NULL, SOIL_LOAD_RGBA);

GLuint texture0;

glBindTexture(GL_TEXTURE_2D, texture0);
glGenTextures(1, &texture0);
glActiveTexture(GL_TEXTURE0);

glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

if (image)
{
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
}
else
{
cout << "ERROR::TEXTURE_LOADING_fAILED" << "\n";
}

//Draw first 2 vertices
glEnable(GL_TEXTURE_2D);
glRotatef(speed,0,1,1); //-5 med

if (goUp == 1){
    glPopMatrix();
    glTranslatef(0,0.2,0);
    glPushMatrix();
    goUp = 0;
}

if (goLeft == 1){
    glPopMatrix();
    glTranslatef(-0.2,0,0);
    glPushMatrix();
    goLeft = 0;
}

if (goDown == 1){
    glPopMatrix();
    glTranslatef(0,-0.2,0);
    glPushMatrix();
    goDown = 0;
}

if (goRight == 1){
    glPopMatrix();
    glTranslatef(0.2,0,0);
    glPushMatrix();
    goRight = 0;
}

glBegin(GL_QUADS);
glColor3ub(aa, ba, ca); //Start vert. color
glTexCoord2f(0.0f, 1.0f); glVertex2f(-.5, .5); //A
glColor3ub(ab, bb, cb); //Start vert. color
glTexCoord2f(1.0f, 1.0f); glVertex2f(.5, .5); //B
glColor3ub(ac, bc, cc); //Start vert. color
glTexCoord2f(1.0f, 0.0f); glVertex2f(.5, -.5); //C
glColor3ub(ad, bd, cd); //Start vert. color
glTexCoord2f(0.0f, 0.0f); glVertex2f(-.5, -.5); //D

glEnd();

SOIL_free_image_data(image);

glFlush();
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
glutPostRedisplay();
}

bool loadShaders(GLuint &program)
{
cout << "Opening vertex shader" << endl;
bool loadSuccess = true;
char infoLog[512];
GLint success;

string temp = "";
string src = "";

ifstream in_file;

in_file.open("vertex_core.glsl");

if (in_file.is_open())
{
while(getline(in_file, temp))
src += temp + "\n";
}
else
{
cout << "ERROR::LOADSHADERS::COULD_NOT_OPEN_VERTEX_FILE" << "\n";
loadSuccess = false;
}
in_file.close();
cout << "Opened vertex shader" << endl;
cout << "Creating vertex shader (compile)" << endl;
GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
const GLchar* vertSrc = src.c_str();
glShaderSource(vertexShader, 1, &vertSrc, NULL);
cout << "Compiling..." << endl;
glCompileShader(vertexShader);

glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
if (!success)
{
glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
cout << "ERROR::LOADSHADERS::COULD_NOT_COMPILE_VERTEX_SHADER" << "\n";
cout << infoLog << "\n";
loadSuccess = false;
}

temp = "";
src = "";

cout << "Done vertex shader" << endl;
cout << "Opening fragment shader" << endl;

in_file.open("fragment_core.glsl");

if (in_file.is_open())
{
while(getline(in_file, temp))
src += temp + "\n";
}
else
{
cout << "ERROR::LOADSHADERS::COULD_NOT_OPEN_FRAGMENT_FILE" << "\n";
loadSuccess = false;
}

in_file.close();

cout << "Creating fragment shader (compile)" << endl;

GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
const GLchar* fragSrc = src.c_str();
glShaderSource(fragmentShader, 1, &fragSrc, NULL);
cout << "Compiling..." << endl;
glCompileShader(fragmentShader);

glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
if (!success)
{
glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
cout << "ERROR::LOADSHADERS::COULD_NOT_COMPILE_FRAGMENT_SHADER" << "\n";
cout << infoLog << "\n";
loadSuccess = false;
}

cout << "Done fragment shader" << endl;

cout << "Creating program" << endl;
//Program
program = glCreateProgram();
glAttachShader(program, vertexShader);
glAttachShader(program, fragmentShader);

glLinkProgram(program);

glGetProgramiv(program, GL_LINK_STATUS, &success);

if (!success)
{
glGetProgramInfoLog(program, 512, NULL, infoLog);
cout << "ERROR::LOADSHADERS::COULD_NOT_LINK_PROGRAM" << "\n";
cout << infoLog << "\n";
loadSuccess = false;
}

cout << "Linked program" << endl;

//End
cout << "Using program..." << endl;
glUseProgram(0);
cout << "OK" << endl;
cout << "Deleting shaders..." << endl;
glDeleteShader(vertexShader);
cout << "Vertex OK" << endl;
glDeleteShader(fragmentShader);
cout << "Fragment OK" << endl;

return loadSuccess;
}

int main(int argc, char** argv){
cout << "glut init" << endl;
glutInit(&argc,argv);
cout << "creating window" << endl;
glutCreateWindow("EpicGL 1.0");
cout << "setting size" << endl;
glutInitWindowSize(800,600);
cout << "binding displayf" << endl;
glutDisplayFunc(display1);

GLenum err = glewInit();
if (GLEW_OK != err)
{
   /* Problem: glewInit failed, something is seriously wrong. */
   std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
}
std::cerr << "Status: Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;

cout << "binding keyboardf" << endl;
glutKeyboardFunc (NormalKeyHandler);
cout << "loading shaders" << endl;
if (!loadShaders(core_program))
{
cout << "error loading shaders" << endl;
}

cout << "Enabling DEPTH_TEST" << endl;
glEnable(GL_DEPTH_TEST);

cout << "Enabling GL_BLEND" << endl;
glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

cout << "Welcome!\nPress Q to alternate between white and black background colors\n";
cout << "Press E to exit anytime.\nPress 1-4 to change the rotation speed.\nPress S to enable 'shading'.\n\n";
cout << "CONTROLS:\nU: Up\nH: Left\nJ: Down\nK: Right\n\n";
glPushMatrix();

glutMainLoop();
glDeleteProgram(core_program);
}
