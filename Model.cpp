//
// Created by andreaporru on 04/01/22.
//
#include "Model.h"
#include "Shapes.h"
void Mesh::create() {
    // initializing the objects
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_CBO);

    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), (GLfloat *) &m_vertices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    //glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

    glVertexAttribPointer(
            0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            sizeof(Vertex),        // stride
            (void*) 0             // array buffer offset
    );

    //glBindBuffer(GL_ARRAY_BUFFER, m_CBO);
    //glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), &m_vertices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(1);
    //glBindBuffer(GL_ARRAY_BUFFER, m_CBO);
    /*void *data = glMapBuffer(GL_ARRAY_BUFFER, GL_READ_ONLY);*/
    glVertexAttribPointer(
            1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
            3,                                // size
            GL_FLOAT,                         // type
            GL_FALSE,                         // normalized?
            sizeof(Vertex),                   // stride
            (void*) offsetof(Vertex,m_color)  // array buffer offset
    );
    //glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), &g_vertex_buffer_data[0], GL_STATIC_DRAW);

    //glBindBuffer(GL_ARRAY_BUFFER, m_CBO);
    //glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), &m_vertices[0], GL_STATIC_DRAW);


}

void Mesh::setShader(Shader *shader) {
    m_shader = shader;
}

void Mesh::update(float delta) {
    // @TODO apply transformation to array (movements and lightning changes)
    glm::mat4 perspective = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
    m_shader->m_mvp = perspective * m_shader->m_view * m_shader->m_model;

}

void Mesh::display() const {
    glUseProgram(m_shader->m_programId);

    glUniformMatrix4fv(m_shader->m_mvpId, 1, GL_FALSE, & (m_shader->m_mvp[0][0]));

    /*glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

    glVertexAttribPointer(
            0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,        // stride
            (void*) 0             // array buffer offset
    );*/

    /*glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, m_CBO);
    void *data = glMapBuffer(GL_ARRAY_BUFFER, GL_READ_ONLY);
        glVertexAttribPointer(
            1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
            3,                                // size
            GL_FLOAT,                         // type
            GL_FALSE,                         // normalized?
            0,                   // stride
            (void*) offsetof(Vertex,m_color)  // array buffer offset
    );*/
    // finally, draw the vertices
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    void *data = glMapBuffer(GL_ARRAY_BUFFER, GL_READ_ONLY);
    glDrawArrays(GL_TRIANGLES,
                 0,
                 m_vertices.size() * 3  ); // @TODO needed optimization: avoid drawing same vertices multiple times

    //glDisableVertexAttribArray(0);
    //glDisableVertexAttribArray(1);

}


void Model::update(float delta) {
    // nothing to do for now
    for(auto mesh : m_meshes){
        mesh->update(delta);
    }
}

void Model::display() const {
    for(auto mesh : m_meshes){
        mesh->display();
    }
}

void Model::load(const std::string &modelPath) {
    // loading vertices
    uint vertexSize = sizeof(g_vertex_buffer_data) / sizeof(*g_vertex_buffer_data);
    std::vector<Vertex> vertices;
    std::vector<GLfloat> positions;
    for(uint16_t p = 0; p < vertexSize; p = p + 3){
        Vertex v;
        v.m_position = glm::vec3(g_vertex_buffer_data[p], g_vertex_buffer_data[p + 1], g_vertex_buffer_data[p + 2]);
        v.m_color = glm::vec3(g_color_buffer_data[p], g_color_buffer_data[p + 1], g_color_buffer_data[p + 2]);
        vertices.push_back(v);
    }
    std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>(vertices);
    mesh->m_positions = (GLfloat*) malloc(sizeof(g_vertex_buffer_data));
    memcpy(mesh->m_positions, &g_vertex_buffer_data[0], sizeof(g_vertex_buffer_data));
    m_meshes.push_back(mesh);
}

void Model::create(){

    for(auto &mesh : m_meshes){
        if(m_shader != nullptr){
            mesh->setShader(m_shader);
        }
        mesh->create();
    }
}

void Model::setShader(Shader *shader) {
    m_shader = shader;
}

void Shader::create(){
    m_model = m_view = glm::mat4(1.0f);
}
void Shader::updateView(const glm::mat4 &view) {
    m_view = view;
}
