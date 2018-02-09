#include "main.h"
#include "timer.h"
#include "ball.h"
#include "enemy.h"
#include "ground.h"
#include <cstdlib>
#include "pointer.h"
#include "trampoline.h"
#include "porcupine.h"
#include "pond.h"
#include "magnet.h"
#include "enemy_slope.h"
#include <string.h>
#include "digit.h"
using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Ball ball1;
Enemy enemy[10],ene;
Enemy_slope ene1[5];
ground ground1;
Pointer pointer1;
Trampoline trampoline1;
Porcupine porcupine1,porcupine2;
Pond pond1;
Magnet magnet1;
Digit digit1,digit2,digit3,digit4;
int pond_stat = 1;
int water_ball = 0;
float Z;
int pan=0;
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
bool jump;
int air =0;
int porcu_count = 0;
int y=0,i;
int state[11];
int score = 0;
int spike_stat =1;
int level = 1;
float d,e = -2.7;
int mouse_count = 1;
int count_magnet =0,magnet_status = 0;
float x_rand,y_rand;
Timer t60(1.0 / 60);
double xin,yin,xout,yout;

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    // glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    // glm::vec3 target (0, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    // glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    // Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
//    Matrices.view = glm::lookAt(glm::vec3(ball1.position.x, 0, 3), glm::vec3(ball1.position.x, 0, 0), glm::vec3(0, 1, 0));
    Matrices.view = glm::lookAt(glm::vec3(y+(pan/8), 0, 3), glm::vec3(y+(pan/8), 0, 0), glm::vec3(0, 1, 0));
// Matrices.view = glm::lookAt(glm::vec3((pan/8), 0, 3), glm::vec3((pan/8), 0, 0), glm::vec3(0, 1, 0));
// Matrices.view = glm::lookAt(glm::vec3(y, 0, 3), glm::vec3(y, 0, 0), glm::vec3(0, 1, 0));
    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model


    // Scene render

    trampoline1.set_position(y -2.8,ground1.dist + trampoline1.radius + 0.3);
    trampoline1.draw(VP);
//    porcupine1.set_position(y+2.0,-3.0);
    if (spike_stat)
    {
        porcupine1.draw(VP);
        if(y !=0 )
        {
            porcupine2.set_position(y+porcupine1.position.x,ground1.dist + abs(y/10));
            porcupine2.draw(VP);
        }
    }
    ground1.set_position(y,(ground1.dist - ground1.high));
    ground1.draw(VP);
    pond1.set_position(y,ground1.dist);
    pond1.draw(VP);
    ball1.draw(VP);
    for (i=0;i<11;i++)
    {
        enemy[i].draw(VP);
    }
    for (i=0;i<5;i++)
        ene1[i].draw(VP);

//     digit1 = Digit(0,1,COLOR_GREEN,(score%10));


    if (score > 15)
    {
        if(magnet_status == 0)
        {
            ;
        }
        else if(magnet_status == 1)
        {
            magnet1.set_position(y - magnet1.distance,0.0);
            magnet1.draw(VP);
        }
        else if(magnet_status == -1)
        {
            magnet1.set_position(y + magnet1.distance,0.0);
            magnet1.draw(VP);
        }
    }
//    porcupine1.set_position();
    if(ball1.position.y > 3.9 )
    {
        pointer1.set_position(ball1.position.x,ground1.dist + 0.05);
        pointer1.draw(VP);
    }
    digit1.set_position(y+3,3);
    digit2.set_position(y+2.7,3);
    digit3.set_position(y+2.4,3);
    digit4.set_position(y-3,3);
    digit2.number = (score - (score)%10)/10;
  digit1.number = (score % 10);
  digit3.number = score/100;

  digit1.draw(VP);
  digit2.draw(VP);
  digit3.draw(VP);
  digit4.number = 3;
   digit4.number = ball1.lives;
  digit4.draw(VP);

//     ground1.draw(VP);
//    ene1.draw(VP);
//    ball2.draw(VP);
}
void screen_zoom_in(){
    screen_zoom -= 0.1;
    reset_screen();
}
void screen_zoom_out(){
    screen_zoom += 0.1;
    reset_screen();
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int space = glfwGetKey(window, GLFW_KEY_SPACE);
    if(mouse_count == 1)
    {
        glfwGetCursorPos(window,&xin,&yin);
//        std :: cout << xin;
//        std :: cout << "\n";

    }
    int D = glfwGetKey(window, GLFW_KEY_1);
    int A = glfwGetKey(window, GLFW_KEY_2);
    int W = glfwGetKey(window, GLFW_KEY_3);
    int S = glfwGetKey(window, GLFW_KEY_4);
    int mouseleft = glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_LEFT);
    int mouseright = glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_RIGHT);
//    double mousescroll =    glfwSetScrollCallback(window,scroll_callback);
    mouse_count=0;
    if(mouse_count == 0)
    {
       glfwGetCursorPos(window,&xout,&yout);
//       std :: cout << xin;
//       std :: cout << "\n";
    }
    y = 8*round(ball1.position.x/8);
    if (D)
    {
        pan += 1;
    }
    if (A)
        pan -= 1;
    if(W /*|| (mousescroll >0)*/)
    {
        screen_zoom += 0.01;
        reset_screen();
    }
    if(S /*|| (mousescroll<0)*/)
     {
        screen_zoom -= 0.01   ;
        reset_screen();
    }
    if(left || ((mouseleft == GLFW_PRESS) && (xout - xin <0)) )
    {
        if(detect_collision_leftside(ball1.bounding_box(),trampoline1.bounding_box()))
        {
            ball1.rotation += 2.0;
        }
        else if (pond_stat && (ball1.position.x < y + (pond1.radius -ball1.radius) && ball1.position.x > y - (pond1.radius-ball1.radius))) {
            ball1.position = ball1.position + (glm::vec3(-0.03,0,0));
            ball1.rotation += 5.0;
        }
        else {
            ball1.position = ball1.position + (glm::vec3(-0.06,0,0));
            ball1.rotation += 2.0;
        }
            mouse_count =1;
    }
    if(right || (((mouseleft == GLFW_PRESS) && (xout - xin >0)) ))
    {
        if(detect_collision_rightside(ball1.bounding_box(),trampoline1.bounding_box()))
        {
            ball1.rotation -= 2.0;
        }
        else if (pond_stat && (ball1.position.x < y + (pond1.radius -ball1.radius) && ball1.position.x > y - (pond1.radius-ball1.radius)))
        {
            ball1.position = ball1.position + (glm::vec3(+0.06,0,0));
            ball1.rotation -= 5.0;
        }
        else {
            ball1.position = ball1.position + (glm::vec3(0.03,0,0));
            ball1.rotation -= 2.0;
        }
        mouse_count = 1;
    }

    if (space && air == 0 ||(air == 0 && mouseright == GLFW_PRESS))
    {

        if (!(ball1.position.x < y + (pond1.radius -ball1.radius) && ball1.position.x > y - (pond1.radius-ball1.radius)))
        {
            e = -2.7;
            ball1.speedy = 0.28 ;
            jump = true;
            d = 0;
            ball1.tick1();
//             std :: cout << "outside";
        }
        else
        {
            e = ball1.position.y;
            ball1.speedy = 0.20 ;
            jump = true;
            d = 1.0;
            ball1.tick1();
//                   std :: cout << "inside";
        }
    }
//    if(ball1.position.y < -2.73 && !(ball1.position.x < y + (pond1.radius - ball1.radius) && ball1.position.x > y- (pond1.radius - ball1.radius)))
//    {
//        ball1.position.y = -2.7;
//        d = 0;
//}
}

void tick_elements() {

    for(i=0;i<11;i++)
    {
        enemy[i].tick();
        if (detect_collision(ball1.bounding_box(), enemy[i].bounding_box()))
        {
           enemy[i].set_position(enemy[i].position.x + 4, enemy[i].position.y);
           score += 5;
           if (score > 10)
           {
               pond_stat = 1;
           }
           if (score > 15)
           {
               spike_stat = 1;
           }
           // std :: cout << score;
           ball1.speedy = (-ball1.speedy) + 0.05 ;
           enemy[i].speed = (0.01 + (0.005*score/10));
        }
        if (enemy[i].position.x < -12.0)
            enemy[i].position.x = 12.0;
    }
    for(i=0;i<5;i++)
     {
        ene1[i].tick();
        if (detect_collision(ball1.bounding_box(), ene1[i].bounding_box()))
        {
           ene1[i].set_position(ene1[i].position.x + 4, ene1[i].position.y);
           score += 10;
//           digit1.number = score%10
           if (score > 10)
           {
               pond_stat = 1;
           }
           if (score > 15)
           {
               spike_stat = 1;
           }
           // std :: cout << score;
           ball1.speed = ball1.speedy;
           ball1.speedy = (-ball1.speedy) + 0.05 ;
           enemy[i].speed = (0.01 + (0.01*score/10));
        }
        if (ene1[i].position.x < -12.0)
            ene1[i].position.x = 12.0;
    }
   ball1.tick2();
    porcupine1.position.y = ground1.dist + abs(y/10);
    if(porcupine1.position.x > /*ground1.wid*/ 4.0- porcupine1.width)
    {
        porcupine1.speed = -0.005;
    }
    if(porcupine1.position.x < pond1.radius + porcupine1.width)
    {
        porcupine1.speed = 0.005;
    }
    porcupine1.tick();

    if(detect_collision_porcupine(ball1.bounding_box(),porcupine1.bounding_box()))
    {
//        spike_stat = 0;
        ball1.lives = ball1.lives -1;
        porcupine1.set_position(y + 4.2,porcupine1.position.y);
        score -= 5;
//        std :: cout << score;
    }
    if(detect_collision_porcupine(ball1.bounding_box(),porcupine2.bounding_box()))
    {
        ball1.lives = ball1.lives -1;
        porcupine1.set_position(y + 4.2,porcupine1.position.y);
        score -= 5;
    }
    if(detect_collision_tramp(ball1.bounding_box(),trampoline1.bounding_box()))
    {
        ball1.speedy = (1.2 * -ball1.speedy);
    }

//    if(ball1.position.x < y + 0.6 && ball1.position.x > y-0.6 )
//    {
//        d = 0;
//    }

    if(jump && (d==1.0))
    {
        if(ball1.position.y > e)
         {
            air =1;
            ball1.tick1();
        }
        else
        {
            ball1.position.y = e;
            air = 0;
        }
//        std :: cout << "outside";
    }
    else if(jump && (d==0))
    {
        if(ball1.position.y > e)
        {
            air =1 ;
            ball1.tick1();
        }
        else
        {
            air =0;
            ball1.position.y =e;
        }
//          std :: cout << "inside";
    }
    else
        air =0;
//     std :: cout << d;
    if(ball1.position.x < y + 0.6 && ball1.position.x > y-0.6 && !air   && pond_stat)
    {
            if(ball1.position.x > y+0)
            {
                ball1.position.x -= 0.005;
                ball1.rotation += 1.0;
            }
            else
             {
                ball1.rotation -= 1.0;
                ball1.position.x += 0.005;
            }
            ball1.position.y = -3.0 - sqrt((0.6*0.6) -((y - ball1.position.x) * (y -ball1.position.x)));
    }
//    if(!(ball1.position.x < y + (pond1.radius -ball1.radius) && ball1.position.x > y - (pond1.radius-ball1.radius)) && ball1.position.y < -2.8)
//    {
//        ball1.position.y = -2.7;
//    }

    if(score > 10)
    {
        count_magnet += 1;
        if (count_magnet % 360 < 120)
        {
            magnet_status = 0;
        }
        else if (count_magnet %360 < 240)
        {
            magnet_status = 1;
        }
        else
        {
            magnet_status = -1;
        }
        if(count_magnet > 360)
            count_magnet = 0;
    }
    if(ball1.position.y > -magnet1.height/2 && ball1.position.y < magnet1.height/2)
    {
        if (magnet_status == 1)
        {
            ball1.speed = -0.05;
            ball1.tick3();
        }
        if (magnet_status == -1)
        {
            ball1.speed = 0.05;
            ball1.tick3();
        }
    }

//      ball1.tick1();


}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models
    ground1 = ground(1,16,-3.0,COLOR_GREEN,COLOR_DARKBROWN);
    ground1.set_position(0,ground1.dist - ground1.high);
    trampoline1 = Trampoline(-2.4,-2.8, COLOR_YELLOW,0.4);
    porcupine1 = Porcupine(-2.0,-2.0,COLOR_RED);
    porcupine1.set_position(2.0,ground1.dist);
    porcupine2 = Porcupine(-2.0,-2.0,COLOR_RED);
    porcupine2.set_position(2.0+100,ground1.dist);
    trampoline1.set_position(-2.4,-2.3);
    pond1 = Pond(-0.0,-3.0,COLOR_SKYBLUE,0.9);
    pond1.set_position(-2.0,-2.0);
    ball1       = Ball(2, -2.7, COLOR_RED, 0.3);
    ball1.lives = 1;
    pointer1 = Pointer(2,-2.4,COLOR_BROWN);
    magnet1 = Magnet(1.2, 0.4, 4.0 ,COLOR_RED);
    for(i=0;i<10;i++)
    {
        x_rand = (rand()%20)/4.0 -2;
        y_rand = (rand()%20)/4.0 -1.5;
        enemy[i] = Enemy(x_rand,y_rand,COLOR_GREEN,0.2 * (i%3),i);
//        cout << x_rand;
        state[i] = 1;
//        cout << "\n";
    }
    for(i=0;i<5;i++)
    {
        x_rand = (rand()%20)/4.0 + 2.0;
        y_rand = (rand()%20)/4.0 -1.5;
        ene1[i] = Enemy_slope(x_rand,y_rand,COLOR_GREEN,0.2,i);
//        cout << x_rand;
        state[i] = 1;
//        cout << "\n";
    }
    state[10] = 1;
    enemy[10] = Enemy(2, -1,COLOR_GREEN,0.2,4);
    digit1 = Digit(0,1,COLOR_GREEN,0);
    digit2 = Digit(0,1,COLOR_GREEN,0);
    digit3 = Digit(0,1,COLOR_GREEN,0);
    digit4 = Digit(0,1,COLOR_RED,3);
//    ene1 = Enemy_slope(2,-1.5,COLOR_BROWN,0.2,4);
    i=0;
//    ball2       = Ball(-2, -3, COLOR_RED);
//    ball2.speed = -ball2.speed;

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (0,0,0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);


    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 480;
    int height = 480;
    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers
           /////////////////////////////
        //        string Result;
        //                    stringstream convert;
        //                    //cout << "nonedit score:" << score << endl;
        //                    convert << score;
        //                    Result = convert.str();

        //                    const char *one = "Score ";
        //                    const char *two = Result.c_str();
        //                    const char *three = "   Level ";
        //                    string Result1;
        //                    stringstream convert1;
        //                    convert1 << level;
        //                    Result1 = convert1.str();
        //                    const char *four = Result1.c_str();
        //                    string total( string(one) + two + string(three) + four);
        //                    glfwSetWindowTitle(window, total.c_str());
        //                    ///////////////////////////////
//      std::string s = std::to_string(score);

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
            if(ball1.lives < 0)
                break;
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }
    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x)*2 < (a.width + b.width)) &&
           (abs(a.y - b.y)*2  < (a.height + b.height) && a.speed   < -0.0000000001 );
}
bool detect_collision_tramp(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) < (a.width + b.width)) &&
           (abs(a.y - b.y)  < (a.height + 0.25));
}
bool detect_collision_porcupine(bounding_box_t a,bounding_box_t b)
{
    return (abs(a.x - b.x)*2 < (a.width + b.width)) &&
           (abs(a.y - b.y)*2  < (a.height + b.height));
}
bool detect_collision_rightside(bounding_box_t a,bounding_box_t b)
{
     return (abs(a.x - b.x) < (a.width + b.width)) && (a.x - b.x < 0) && (a.y < b.y);
}

bool detect_collision_pond(bounding_box_t a, bounding_box_t b)
{
    return (abs(a.x - b.x));
}

bool detect_collision_leftside(bounding_box_t a,bounding_box_t b)
{
     return (abs(a.x - b.x) < (a.width + b.width)) && (a.x - b.x > 0) && (a.y < b.y);
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
