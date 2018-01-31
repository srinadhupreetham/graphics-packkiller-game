#include "main.h"

#ifndef MAGNET_H
#define MAGNET_H


class Magnet
{
public:
    Magnet() {};
    Magnet(float height, float width,float distance, color_t color1);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    float height,width,distance;
    void set_position(float x, float y);
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // MAGNET_H
