#include "pond.h"
#include "main.h"

Pond::Pond(float x, float y, color_t color1,float radius)
{
    GLfloat vertex_buffer_data[180*3*3];
        int i=0;
        float param = 0.0;
        for(i=0;i<180;i++)
        {
         vertex_buffer_data[9*i] = 0.0f;
         vertex_buffer_data[9*i+1] = 0.0f;
         vertex_buffer_data[9*i+1] = 0.0f;
         vertex_buffer_data[9*i+2] = 0.0f;
         vertex_buffer_data[9*i+3] = radius * cos(param * M_PI/180);
         vertex_buffer_data[9*i+4] = radius * sin(param * M_PI/180);
         vertex_buffer_data[9*i+5] = 0.0f;
         param += 2.0;
         vertex_buffer_data[9*i+6] = radius * cos(param * M_PI/180);
         vertex_buffer_data[9*i+7] = radius * sin(param * M_PI/180);
         vertex_buffer_data[9*i+8] = 0.0f;
        }
        this->object = create3DObject(GL_TRIANGLES, 90*3, vertex_buffer_data+90*9, color1, GL_FILL);
}

void Pond::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Pond::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

bounding_box_t Pond::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, 0.3, 0.3};
    return bbox;
}
