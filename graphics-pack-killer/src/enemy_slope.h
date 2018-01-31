#include "main.h"
#ifndef ENEMY_SLOPE_H
#define ENEMY_SLOPE_H


class Enemy_slope
{
public:
    Enemy_slope() {};
    Enemy_slope(float x, float y, color_t color1, float radius, int index);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
//    int index1;
    double speed;
    bounding_box_t bounding_box();
private:
    VAO *object1;
    VAO *object2;
};

#endif // ENEMY_SLOPE_H
