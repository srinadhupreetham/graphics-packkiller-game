#include "enemy.h"
#include "main.h"
#include <cstdlib>

Enemy::Enemy(float x, float y, color_t color1,float radius,int index) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this ->speed = 0.02;
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
    if(index%4 == 0)
    {
        color1 = COLOR_BLACK;
        this -> speed = 0.015;}
    else if (index%4 == 1)
    {color1 = COLOR_RED;this-> speed = 0.02;}
    else if (index%4 == 2)
    {color1 = COLOR_GREEN;this -> speed = 0.03;}
    else
    {color1 = COLOR_SKYBLUE;this -> speed = 0.025;}
//         glDrawArrays(GL_TRIANGLES, 0, 720*3);
        this->object = create3DObject(GL_TRIANGLES, 180*3, vertex_buffer_data, color1, GL_FILL);
//    this->object = create3DObject(GL_TRIANGLES, 355*3, vertex_buffer_data, color2, GL_FILL);
}

void Enemy::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Enemy::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}
void Enemy::tick() {
   this->position.x -= this->speed;
}


bounding_box_t Enemy::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, 0.2, 0.2};
    return bbox;
}
