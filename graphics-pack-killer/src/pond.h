#include "main.h"

#ifndef POND_H
#define POND_H


class Pond
{
public:
    Pond() {};
    Pond(float x, float y, color_t color1, float radius);
    glm::vec3 position;
    float rotation;
    float radius;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // POND_H
