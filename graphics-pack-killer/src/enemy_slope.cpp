#include "main.h"
#include "enemy_slope.h"

Enemy_slope::Enemy_slope(float x, float y, color_t color1 ,float radius , int index)
{
    this->position = glm::vec3(x, y, 0);
    this->rotation = 45;
    this ->speed = 0.01;
    GLfloat vertex_buffer_data1[180*3*3];
        int i=0;
        float param = 0.0;
        for(i=0;i<180;i++)
        {
         vertex_buffer_data1[9*i] = 0.0f;
         vertex_buffer_data1[9*i+1] = 0.0f;
         vertex_buffer_data1[9*i+1] = 0.0f;
         vertex_buffer_data1[9*i+2] = 0.0f;
         vertex_buffer_data1[9*i+3] = radius * cos(param * M_PI/180);
         vertex_buffer_data1[9*i+4] = radius * sin(param * M_PI/180);
         vertex_buffer_data1[9*i+5] = 0.0f;
         param += 2.0;
         vertex_buffer_data1[9*i+6] = radius * cos(param * M_PI/180);
         vertex_buffer_data1[9*i+7] = radius * sin(param * M_PI/180);
         vertex_buffer_data1[9*i+8] = 0.0f;
        }
     static const GLfloat vertex_buffer_data2[6*3*3]={
            -2*radius,radius+0.1,0,
             -2*radius,radius,0,
            2*radius,radius,0,
         2*radius,radius,0,
         -2*radius,radius+0.1,0,
         2*radius,radius+0.1,0
          };
     if(index%4 == 0)
     {
         color1 = COLOR_YELLOW;
         this -> speed = 0.017;}
     else if (index%4 == 1)
     {color1 = COLOR_RED;this-> speed = 0.01;}
     else if (index%4 == 2)
     {color1 = COLOR_GREEN;this -> speed = 0.028;}
     else
     {color1 = COLOR_SKYBLUE;this -> speed = 0.013 ;}
//         glDrawArrays(GL_TRIANGLES, 0, 720*3);
        this->object1 = create3DObject(GL_TRIANGLES, 180*3, vertex_buffer_data1, color1, GL_FILL);
        this->object2 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data2, COLOR_DARKBROWN, GL_FILL);
//    this->object = create3DObject(GL_TRIANGLES, 355*3, vertex_buffer_data, color2, GL_FILL);
}

void Enemy_slope::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
}

void Enemy_slope::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}
void Enemy_slope::tick() {
   this->position.x -= this->speed;
}


bounding_box_t Enemy_slope::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, 0.2, 0.2};
    return bbox;
}
