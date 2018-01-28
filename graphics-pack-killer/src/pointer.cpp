#include "pointer.h"
#include "main.h"
#include "pointer.h"
Pointer::Pointer(float x, float y, color_t color1)
{
    this->position = glm::vec3(x, y, 0);
    static const GLfloat vertex_buffer_data[] = {
        0, 0.03, 0, // vertex 1
        0.15, 0, 0, // vertex 2
        0,  0.15, 0, // vertex 3

        0,  0.15, 0, // vertex 3
        -0.15, 0, 0, // vertex 4
        0, 0.03, 0 // vertex 1
    };

    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color1, GL_FILL);
}

void Pointer::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Pointer::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}
