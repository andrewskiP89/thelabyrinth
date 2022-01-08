//
// Created by andreaporru on 04/01/22.
//

#ifndef THELABYRINTH_MODEL_H
#define THELABYRINTH_MODEL_H

#include "Libraries.h"
#include "StandardHeaders.h"

enum ModelInited {MODEL_INITED_FALSE, MODEL_INITED_TRUE};

struct Shader{
    GLuint m_programId, m_mvpId;
    glm::mat4 m_model;
    glm::mat4 m_view;
    glm::mat4 m_mvp;
    void create();
    void updateView(const glm::mat4 &view);
};
// we are using property of the struct of
// having its memory layout sequential for all its items.
// Because of that, we can invoke the glBufferData and just pass a vertex pointer
struct Vertex{
    glm::vec3 m_position;
    //glm::vec3 m_normal;
    glm::vec3 m_color;
};

struct Mesh{
    GLuint m_VAO; // vertex
    GLuint m_VBO; // buffer
    GLuint m_CBO; // color
    GLuint m_EBO; // @TODO it will be used to manage the indexes
    std::vector<Vertex> m_vertices;
    GLfloat *m_positions;
    Shader *m_shader = nullptr;
    void setShader(Shader *shader);
    Mesh(std::vector<Vertex> &vertices) : m_vertices(vertices){};
    void create();
    void update(float delta);
    void display() const;
};

struct Model{
    std::vector<std::shared_ptr<Mesh>> m_meshes;
    Shader *m_shader = nullptr;
    void setShader(Shader *shader);
    void load(const std::string &modelPath);
    void create();
    void update(float delta);
    void display() const;
};
#endif //THELABYRINTH_MODEL_H
