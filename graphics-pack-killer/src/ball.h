#include "main.h"

#ifndef BALL_H
#define BALL_H


class Ball {
public:
    Ball() {}
    Ball(float x, float y, color_t color1, float radius);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick1();
    void tick2();
    int level;
    float radius;
    double speed;
    double speedy;
    bounding_box_t bounding_box();
private:
    VAO *red;
    VAO *black;
    VAO *brown;
    VAO *darkbrown;
    VAO *green;
    VAO *background;
};

#endif // BALL_H
