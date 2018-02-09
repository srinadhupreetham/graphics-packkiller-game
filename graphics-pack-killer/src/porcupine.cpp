#include "porcupine.h"
#include "main.h"
Porcupine::Porcupine(float x,float y, color_t color1)
{
    this->position = glm::vec3(x, y, 0);
//    static const GLfloat vertex_buffer_data[] = {
//        -0.4, 0.4, 0, // vertex 1
//        -0.4,  -0.4, 0, // vertex 2
//        0.2,  0, 0, // vertex 3

//        0.2,  0, 0, // vertex 3
//        0, 0.4, 0, // vertex 4
//        0, -0.4, 0, // vertex 1

//        0, 0.4, 0, // vertex 4
//        0, -0.4, 0, // vertex 1

//        -0.2,  0, 0, // vertex 3

//        -0.2,  0, 0, // vertex 3
//        0.4, 0.4, 0, // vertex 4
//        0.4, -0.4, 0 // vertex 1
//    };
    static const GLfloat vertex_buffer_data[] = {
        -0.3,0.2,0,
        -0.3,-0.2,0,
        -0.2,0,0,

        -0.2, 0, 0, // vertex 1
        -0.1,  -0.2, 0, // vertex 2
        0,  0, 0, // vertex 3

        0,  0, 0, // vertex 3
        -0.1, 0.2, 0, // vertex 4
        -0.2, 0, 0, // vertex 1

        0.2, 0, 0, // vertex 4
        0.1, -0.2, 0, // vertex 1

        0,  0, 0, // vertex 3

        0,  0, 0, // vertex 3
        0.1, 0.2, 0, // vertex 4
        0.2, 0, 0, // vertex 1

        0.3,0.2,0,
        0.3,-0.2,0,
        0.2,0,0
    };

    this -> width = 0.4;
    this -> height = 0.2;
    this -> speed = 0.03;
    this->object = create3DObject(GL_TRIANGLES, 18, vertex_buffer_data, color1, GL_FILL);
}

void Porcupine::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (1.2 * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Porcupine::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}
void Porcupine::tick() {
   this->position.x += this->speed;
}

bounding_box_t Porcupine::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, 0.6, 0.4, 0};
    return bbox;
}
