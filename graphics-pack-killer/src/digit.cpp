#include "digit.h"
#include "main.h"
Digit::Digit(float x,float y, color_t color1,int number)
{
    int t=this->t =0;
    int m=this->m=0;
    int b=this->b=0;
    int rb=this ->rb=0;
    int rt=this -> rt=0;
    int lb=this -> lb=0;
    int lt=this -> lt=0;
    this -> number = number;
    static const GLfloat vertex_buffer_datam[] = {

        -0.1, 0.1, 0, // vertex 1
        -0.1,  -0.1, 0, // vertex 2
        0.1,  -0.1, 0, // vertex 3

        -0.1,  0.1, 0, // vertex 3
        0.1, -0.1, 0, // vertex 4
        0.1, 0.1, 0, // vertex 1
    };
    this -> middle = create3DObject(GL_TRIANGLES, 6, vertex_buffer_datam, color1, GL_FILL);
    static const GLfloat vertex_buffer_datat[] = {

        -0.1, 0.5, 0, // vertex 1
        -0.1,  0.3, 0, // vertex 2
        0.1,  0.3, 0, // vertex 3

        -0.1,  0.5, 0, // vertex 3
        0.1, 0.3, 0, // vertex 4
        0.1, 0.5, 0, // vertex 1
    };
    this -> top = create3DObject(GL_TRIANGLES, 6, vertex_buffer_datat, color1, GL_FILL);
    static const GLfloat vertex_buffer_datab[] = {

        -0.1, -0.3, 0, // vertex 1
        -0.1,  -0.5, 0, // vertex 2
        0.1,  -0.5, 0, // vertex 3

        -0.1,  -0.3, 0, // vertex 3
        0.1, -0.5, 0, // vertex 4
        0.1, -0.3, 0, // vertex 1
    };
    this -> bottom = create3DObject(GL_TRIANGLES, 6, vertex_buffer_datab, color1, GL_FILL);
    static const GLfloat vertex_buffer_datalt[] = {

        -0.1, 0.1, 0, // vertex 1
        -0.1,  0.5, 0, // vertex 2
        -0.06,  0.1, 0, // vertex 3

        -0.06,  0.1, 0, // vertex 3
        -0.06, 0.5, 0, // vertex 4
        -0.1, 0.5, 0, // vertex 1
    };
    this -> lefttop = create3DObject(GL_TRIANGLES, 6, vertex_buffer_datalt, color1, GL_FILL);
    static const GLfloat vertex_buffer_datart[] = {

        0.06, 0.1, 0, // vertex 1
        0.06,  0.5, 0, // vertex 2
        0.1,  0.1, 0, // vertex 3

        0.1,  0.1, 0, // vertex 3
       0.1, 0.5, 0, // vertex 4
        0.06, 0.5, 0, // vertex 1
    };
    this -> righttop = create3DObject(GL_TRIANGLES, 6, vertex_buffer_datart, color1, GL_FILL);
    static const GLfloat vertex_buffer_datalb[] = {

        -0.1, -0.1, 0, // vertex 1
        -0.1,  -0.5, 0, // vertex 2
        -0.06,  -0.1, 0, // vertex 3

        -0.06,  -0.1, 0, // vertex 3
        -0.06, -0.5, 0, // vertex 4
        -0.1, -0.5, 0, // vertex 1
    };
    this -> leftbottom = create3DObject(GL_TRIANGLES, 6, vertex_buffer_datalb, color1, GL_FILL);
    static const GLfloat vertex_buffer_datarb[] = {

        0.06, -0.1, 0, // vertex 1
        0.06,  -0.5, 0, // vertex 2
        0.1,  -0.1, 0, // vertex 3

        0.1,  -0.1, 0, // vertex 3
       0.1, -0.5, 0, // vertex 4
        0.06, -0.5, 0, // vertex 1
    };
    this -> rightbottom = create3DObject(GL_TRIANGLES, 6, vertex_buffer_datarb, color1, GL_FILL);

//    this->t =t;
//    this->m=m;
//    this->b=b;
//    this ->rb=rb;
//    this -> rt=rt;
//    this -> lb=lb;
//    this -> lt=lt;

}

void Digit::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    if(this-> number == 0)
    {
        this->t=1;this->lt=1;this->lb=1;this->rt=1;this->rb=1;this->m=0;this->b=1;
    }
    if(this -> number == 1)
    {
        this->t=0;this->lt=0;this->lb=0;this->rt=1;this->rb=1;this->m=0;this->b=0;
    }
    if(this -> number == 2)
    {
        this->t=0;this->lt=0;this->lb=0;this->rt=1;this->rb=1;this->m=0;this->b=0;
    }
    if(this -> number == 3)
    {
        this->t=1;this->lt=0;this->lb=0;this->rt=1;this->rb=1;this->m=1;this->b=1;
    }
    if(this -> number == 4)
    {
        this->t=0;this->lt=1;this->lb=0;this->rt=1;this->rb=1;this->m=1;this->b=0;
    }
    if(this -> number == 5)
    {
        this->t=1;this->lt=1;this->lb=0;this->rt=0;this->rb=1;this->m=1;this->b=1;
    }
    if(this -> number == 6)
    {
        this->t=1;this->lt=1;this->lb=1;this->rt=0;this->rb=1;this->m=1;this->b=1;
    }
    if(this -> number == 7)
    {
        this->t=1;this->lt=0;this->lb=0;this->rt=1;this->rb=1;this->m=0;this->b=0;
    }
    if(this -> number == 8)
    {
        this->t=1;this->lt=1;this->lb=1;this->rt=1;this->rb=1;this->m=1;this->b=1;
    }
    if(this -> number == 9)
    {
        this->t=1;this->lt=1;this->lb=0;this->rt=1;this->rb=1;this->m=1;this->b=1;
    }
   if (this -> t)
    draw3DObject(this->top);
   if(this->b)
   draw3DObject(this->bottom);
   if(this ->m)
   draw3DObject(this->middle);
   if(this ->lt)
   draw3DObject(this->lefttop);
   if(this ->lb)
   draw3DObject(this->leftbottom);
   if(this ->rt)
   draw3DObject(this->righttop);
   if(this ->rb)
   draw3DObject(this->rightbottom);
}

void Digit::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}


