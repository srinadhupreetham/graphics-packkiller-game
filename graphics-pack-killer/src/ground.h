#include "main.h"

#ifndef GROUND_H
#define GROUND_H


class ground
{
public:
    ground() {}
    ground(float height, float width, color_t color);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    float rotation;
private:
    VAO *object;

};

#endif // GROUND_H
