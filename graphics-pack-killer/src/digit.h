#include "main.h"
#ifndef DIGIT_H
#define DIGIT_H


class Digit
{
public:
    Digit() {};
    Digit(float x, float y, color_t color1, int number);
    glm::vec3 position;
    float rotation;
    int number;
    int t;
    int m;
    int b;
    int rb;
    int rt;
    int lb;
    int lt;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
private:
    VAO *top;
    VAO *bottom;
    VAO *middle;
    VAO *lefttop;
    VAO *leftbottom;
    VAO *righttop;
    VAO *rightbottom;
};

#endif // DIGIT_H
