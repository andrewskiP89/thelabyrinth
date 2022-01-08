//
// Created by andreaporru on 28/12/21.
//

#include <iostream>
#include "Renderer.h"
#include "Camera.h"
#include "Model.h"
#include "IOManager.h"

// initing the array buffers. This will be handled by the
// Frustum routine at one point
enum VAO_IDs {Triangles, NumVAOs};
enum Buffer_IDs {ArrayBuffer, NumBuffers};
enum Attrib_IDs {vPosition = 0};

GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];

GLuint vertexArrayId, vertexBuffer;
GLuint colorArrayId, colorBuffer;

const GLuint NumVertices = 6;

// Create and compile our GLSL program from the shaders
GLuint programID = -1;

GLuint mvpId;
glm::mat4 MVP;

static const GLfloat vertices[NumVertices][2] = {
        {-0.90, -0.90}, // triangle 1
        {-0.90, -0.90},
        {-0.90, -0.90},
        {-0.90, -0.90},// triangle 2
        {-0.90, -0.90},
        {-0.90, -0.90}
};

//    static const GLfloat g_vertex_buffer_data[] = {
//        -1.0f, -1.0f, 0.0f,
//        1.0f, -1.0f, 0.0f,
//        0.0f,  1.0f, 0.0f,
//};

int Window::init() {
    if(glfwInit() != GLFW_TRUE){
        std::cout << " Unable to init glfw. Quitting...\n";
        glfwTerminate();
        return INITED_FALSE;
    }
    // added to make sure shaders compile under 330
    glfwWindowHint(GLFW_SAMPLES, 4); // this is needed!!
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

    m_window = glfwCreateWindow(1080, 720, APP_TITLE, nullptr, nullptr);
    glfwMakeContextCurrent(m_window);
    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if(glewInit() != GLEW_OK){
        std::cout << "Unable to init glew Quitting...\n";
        glfwTerminate();
        return INITED_FALSE;
    }

    // setting starting mode
    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(m_window, GLFW_STICKY_KEYS, GL_TRUE);


    // loading the shaders
    programID = LoadShaders( "./shaders/VertexShader.shader", "./shaders/FragmentShader.shader" );
    mvpId = glGetUniformLocation(programID, "MVP");

    // initing the camera
    if(m_camera.init() != CAMERA_INITED_TRUE)
        return INITED_FALSE;

    // Dark blue background
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);
    // enabling culling
    glEnable(GL_CULL_FACE);

    // initing a simple model
    // creating the shader
    Shader *sh = new Shader();
    sh->create();
    sh->m_programId = programID;
    sh->m_mvpId = mvpId;
    Model *sampleModel = new Model();
    sampleModel->load("");
    sampleModel->setShader(sh);
    sampleModel->create();
    m_worldItems.push_back(sampleModel);

    // vertex generation and binding the first one
    /*glGenVertexArrays(1, &vertexArrayId);
    glBindVertexArray(vertexArrayId);

    // VERTEX BUFFER
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    // COLOR BUFFER
    glGenBuffers(1, &colorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);*/

    // initing a sample model

    return INITED_TRUE;
}

void Window::update(float delta) {
    static float angle = 0;
    angle += delta;
    glm::mat4 projection = getProjection();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0,0,0));
    model = glm::rotate(model, angle, glm::vec3(0, 1, 0));
    glm::mat4 view = m_camera.getView();
    for(auto &model : m_worldItems){
        model->m_shader->m_view = view; // updating the view
        model->update(delta);
    }
    MVP = projection * view * model;
}

bool Window::quitting() const{
    return glfwWindowShouldClose(m_window);
}

void Window::display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /*glUseProgram(programID);
    // applying mvp transformations
    glUniformMatrix4fv(mvpId, 1, GL_FALSE, &MVP[0][0]);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

    glVertexAttribPointer(
            0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            nullptr            // array buffer offset
    );
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);

    glVertexAttribPointer(
            1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
            3,                                // size
            GL_FLOAT,                         // type
            GL_FALSE,                         // normalized?
            0,                                // stride
            (void*)0                          // array buffer offset
    );
    // finally, draw the vertices
    glDrawArrays(GL_TRIANGLES,
                 0,
                 sizeof(g_vertex_buffer_data) / sizeof(*g_vertex_buffer_data) / 3);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);*/
    for(auto item : m_worldItems){
        item->display();
    }

    glfwSwapBuffers(m_window);




}

void Window::exit() const{
    glDeleteBuffers(1, &vertexBuffer);
    glDeleteVertexArrays(1, &vertexArrayId  );
    glfwDestroyWindow(m_window);

    glfwTerminate();
}

glm::mat4 Window::getProjection(bool ortho) {
    if(ortho)
        return glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f);
    else
        return glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
}

vec2i const Window::getCenter() {
    vec2i center;
    glfwGetWindowSize(m_window,   &(center.x) , &(center.y) );

    return vec2i (center.x / 2, center.y /2 );
}

Camera& Window::getCamera() {
    return m_camera;
}

