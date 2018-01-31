#include "trampoline.h"
#include "main.h"
Trampoline::Trampoline(float x,float y, color_t color1 ,float radius)
{
        this -> radius = radius;
        GLfloat vertex_buffer_data[180*3*3];
            int i=0;
            float param = 0.0;
            for(i=0;i<180;i++)
            {
             vertex_buffer_data[9*i] = 0.0f;
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
       static const GLfloat vertex_buffer_data1[] = {
                radius, 0, 0, // vertex 1
                radius, -0.8, 0, // vertex 2
                radius+0.1, -0.8, 0, // vertex 3

                radius+0.1, -0.8, 0, // vertex 3
                radius+0.1, 0, 0, // vertex 4
                radius, 0, 0 // vertex 1
            };
       static const GLfloat vertex_buffer_data2[] = {
                -radius, 0, 0, // vertex 1
                -radius, -0.8, 0, // vertex 2
                -(radius+0.1), -0.8, 0, // vertex 3

                -(radius+0.1), -0.8, 0, // vertex 3
                -(radius+0.1), 0, 0, // vertex 4
                -radius, 0, 0 // vertex 1
            };
        this->nets = create3DObject(GL_TRIANGLES, 90*3, vertex_buffer_data + 90*9, color1, GL_FILL);
        this->stick1 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data1, color1, GL_FILL);
        this->stick2 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data2, color1, GL_FILL);
}

void Trampoline::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->nets);
    draw3DObject(this->stick1);
    draw3DObject(this->stick2);
}

void Trampoline::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

bounding_box_t Trampoline::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, this->radius +0.1, 0.9,0};
    return bbox;
}
