#include "main.h"

#ifndef BALL_H
#define BALL_H


class Ball {
public:
    Ball() {}
    Ball(float x, float y, color_t color1, color_t color2);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick1();
    void tick2();
    double speed;
    double speedy;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // BALL_H
