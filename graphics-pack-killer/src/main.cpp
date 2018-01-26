#include "main.h"
#include "timer.h"
#include "ball.h"
#include "enemy.h"
#include "ground.h"
#include <cstdlib>
using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Ball ball1;
Enemy enemy[10],ene1;
ground ground1;
float Z;
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
bool jump;
int count =0;
int y=0,i;
int state[11];
float x_rand,y_rand;
Timer t60(1.0 / 60);

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
        Matrices.view = glm::lookAt(glm::vec3(y, 0, 3), glm::vec3(y, 0, 0), glm::vec3(0, 1, 0));
    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    ball1.draw(VP);
    for (i=0;i<11;i++)
    {
        if(state[i] == 1)
        enemy[i].draw(VP);
    }
   // ground1.draw(VP);
//    ene1.draw(VP);
//    ball2.draw(VP);
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int space = glfwGetKey(window, GLFW_KEY_SPACE);
    y = 8*round(ball1.position.x/8);
    if (left) {
        // Do something
        ball1.position = ball1.position + (glm::vec3(-0.03,0,0));
        ball1.rotation += 2.0;
    }
    if (right) {
        ball1.position = ball1.position + (glm::vec3(0.03,0,0));
        ball1.rotation -= 2.0;
//        std:: cout << ball1.position.x ;
//        std:: cout << "\n";
    }
    if (space && count == 0) {
//       Z = ball1.position.y;
//       ball1.tick1();
//       if (ball1.position.y > Z + 0.1)
//       {
//           ball1.tick2();
//       }
        ball1.speedy = 0.3 ;
        jump = true;
        ball1.tick1();
        std::cout << ball1.speedy;
        std::cout << "\n";

//        ball1.tick();
//        ball1.position += (glm ::vec3(0, 0.1,0));
//        ball1.position += (glm ::vec3(0, -0.1,0));
    }

}

void tick_elements() {
    for(i=0;i<11;i++)
    {
        if(state[i] == 1)
        {
            enemy[i].tick();
        }
        if (detect_collision(ball1.bounding_box(), enemy[i].bounding_box()))
        {
           state[i] = 0;
           enemy[i].set_position(-100,-100);
           state[i] = 0;
//           kill_enemy_jump[i] = 1
           ball1.speedy = (-ball1.speedy) + 0.05 ;
        }
    }
//    ene1.tick();`
    if(jump && ball1.position.y > -3)
    {
        ball1.tick1();
        count =1;
    }else
        count =0;
//      ball1.tick1();


}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models
    ground(1,1,COLOR_GREEN);
    ball1       = Ball(2, -3, COLOR_GREEN, COLOR_RED);
    for(i=0;i<10;i++)
    {
        x_rand = (rand()%20)/4.0 -2;
        y_rand = (rand()%20)/4.0 -1;
        enemy[i] = Enemy(x_rand,y_rand,COLOR_RED,i);
        cout << x_rand;
        state[i] = 1;
////        cout << "\n";
    }
    state[10] = 1;
    enemy[10] = Enemy(2, -1,COLOR_BLACK,4);
    i=0;
//    ball2       = Ball(-2, -3, COLOR_RED);
//    ball2.speed = -ball2.speed;

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r * 1, COLOR_BACKGROUND.g *1, COLOR_BACKGROUND.b *1, 0.0f); // R, G, B, A
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
    int width  = 1480;
    int height = 1024;
    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
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

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
