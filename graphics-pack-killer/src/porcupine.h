#include "main.h"

#ifndef PORCUPINE_H
#define PORCUPINE_H


class Porcupine
{
public:
    Porcupine() {};
    Porcupine(float x, float y, color_t color1);
    glm::vec3 position;
    float rotation;
    double speed;
    void draw(glm::mat4 VP);
    void tick();
    void set_position(float x, float y);
    bounding_box_t bounding_box();
private:
    VAO *object;

};

#endif // PORCUPINE_H
