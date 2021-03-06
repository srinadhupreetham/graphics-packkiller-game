#include "ball.h"
#include "main.h"

Ball::Ball(float x, float y, color_t color1,float radius) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->radius = radius;
    speed = 0.0;
    speedy = 0.4;
//    static const GLfloat vertex_buffer_data[] = {
//        -0.2, -0.2, 0, // vertex 1
//        0.2,  -0.2, 0, // vertex 2
//        0.2,  0.2, 0, // vertex 3

//        0.2,  0.2, 0, // vertex 3
//        -0.2, 0.2, 0, // vertex 4
//        -0.2, -0.2, 0 // vertex 1
//    };
    GLfloat vertex_buffer_data[720*3*3];
        int i=0;
        float param = 0.0;
        for(i=0;i<720;i++)
        {
         vertex_buffer_data[9*i] = 0.0f;
         vertex_buffer_data[9*i+1] = 0.0f;
         vertex_buffer_data[9*i+2] = 0.0f;

         vertex_buffer_data[9*i+3] = radius * cos(param * M_PI/180);
         vertex_buffer_data[9*i+4] = radius * sin(param * M_PI/180);
         vertex_buffer_data[9*i+5] = 0.0f;

         param += 0.5;
         vertex_buffer_data[9*i+6] = radius * cos(param * M_PI/180);
         vertex_buffer_data[9*i+7] = radius * sin(param * M_PI/180);
         vertex_buffer_data[9*i+8] = 0.0f;
        }
//         glDrawArrays(GL_TRIANGLES, 0, 720*3);

   // this->object = create3DObject(GL_TRIANGLES, 710*3, vertex_buffer_data, color1, GL_FILL);
        this->red = create3DObject(GL_TRIANGLES, 120*3, vertex_buffer_data, COLOR_RED, GL_FILL);
        this->black = create3DObject(GL_TRIANGLES, 120*3, vertex_buffer_data + 9 *120, COLOR_BLACK, GL_FILL);
        this->brown = create3DObject(GL_TRIANGLES, 120*3, vertex_buffer_data + 9 *240, COLOR_BROWN, GL_FILL);
        this->darkbrown = create3DObject(GL_TRIANGLES, 120*3, vertex_buffer_data + 9 *360, COLOR_DARKBROWN, GL_FILL);
        this->green = create3DObject(GL_TRIANGLES, 120*3, vertex_buffer_data + 9 *480, COLOR_GREEN, GL_FILL);
        this->background = create3DObject(GL_TRIANGLES, 120*3, vertex_buffer_data + 9 *600, COLOR_BACKGROUND, GL_FILL);
}

void Ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->red);
    draw3DObject(this->black);
    draw3DObject(this->brown);
    draw3DObject(this->darkbrown);
    draw3DObject(this->green);
    draw3DObject(this->background);
}

void Ball::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}
void Ball::tick1() {
        speedy = speedy - 0.012;
         this -> position.y += speedy;
}
void Ball::tick2() {
    if(this -> speed < 0)
    {   this -> position.x += this->speed;
        this -> speed += 0.0055;
    }
}
void Ball::tick3(){
    this -> position.x += this->speed;
      this -> speed += 0.0055;
}

bounding_box_t Ball::bounding_box() {
    float x = this->position.x, y = this->position.y;
    float s = this->speedy;
    bounding_box_t bbox = { x, y, 0.34, 0.34,s };
    return bbox;
}
