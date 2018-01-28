#include "main.h"

#ifndef ENEMY_H
#define ENEMY_H


class Enemy {
public:
    Enemy() {}
    Enemy(float x, float y, color_t color1, float radius, int index);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
//    int index1;
    double speed;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // ENEMY_H
