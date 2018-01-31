#include "main.h"

#ifndef GROUND_H
#define GROUND_H


class ground
{
public:
    ground() {}
    ground(float height, float width,float distance,color_t color1, color_t color2);
    glm::vec3 position;
    float high,dist;
    float wid;
    void draw(glm::mat4 VP);
    float rotation;
    void set_position(float x, float y);
private:
    VAO *grass;
    VAO *soil;

};

#endif // GROUND_H
