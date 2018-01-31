#include "main.h"

#ifndef TRAMPOLINE_H
#define TRAMPOLINE_H


class Trampoline
{
public:
    Trampoline() {};
    Trampoline(float x, float y, color_t color1,float radius);
    glm::vec3 position;
    float rotation,radius;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    bounding_box_t bounding_box();
private:
    VAO *nets;
    VAO *stick1;
    VAO *stick2;

};

#endif // TRAMPOLINE_H
