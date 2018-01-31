#include "ground.h"
#include "main.h"

ground::ground(float height, float width, float distance,color_t color1,color_t color2)
{
        this -> wid = width/2;
        static const GLfloat vertex_buffer_data1[] = {
            -width/2, height/2, 0, // vertex 1
            -width/2, height/6, 0, // vertex 2
            width/2, height/6, 0, // vertex 3

            width/2, height/6, 0, // vertex 3
            width/2, height/2, 0, // vertex 4
            -width/2, height/2, 0 // vertex 1
        };
        static const GLfloat vertex_buffer_data2[] = {
            -width/2, height/6, 0, // vertex 1
            -width/2, -height/2, 0, // vertex 2
            width/2, -height/2, 0, // vertex 3

            width/2, -height/2, 0, // vertex 3
            width/2, height/6, 0, // vertex 4
            -width/2, height/6, 0 // vertex 1
        };
        this->dist = distance;
        this->high = height/2 ;
        this->grass = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data1, color1, GL_FILL);
        this->soil = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data2, color2, GL_FILL);
}
void ground::draw(glm::mat4 VP) {
        Matrices.model = glm::mat4(1.0f);
        glm::mat4 translate = glm::translate (this->position);    // glTranslatef
        glm::mat4 rotate    = glm::rotate((float) (0 * M_PI / 180.0f), glm::vec3(0, 0, 1));
        rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
        Matrices.model *= (translate * rotate);
        glm::mat4 MVP = VP * Matrices.model;
        glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
        draw3DObject(this->grass);
        draw3DObject(this->soil);
}

void ground::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}
