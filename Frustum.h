//
// Created by andreaporru on 28/12/21.
//

#ifndef THELABYRINTH_FRUSTUM_H
#define THELABYRINTH_FRUSTUM_H
#include <GLFW/glfw3.h>
enum VAO_IDs {Triangles, NumVAOs};
enum Buffer_IDs {ArrayBuffer, NumBuffers};
enum Attrib_IDs {vPosition = 0};

GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];

const GLuint NumVertices = 6;

struct Cube{

};
#endif //THELABYRINTH_FRUSTUM_H
