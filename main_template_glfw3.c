// D:\bin\tcc\tcc.exe -v -ID:/bin/tcc/include -lglfw3 -lopengl32 -lglu32 -run main_template_glfw3.c

#define WIN32_LEAN_AND_MEAN
#define GLFW_DLL


#include <windows.h>		// Header File For Windows
#include <math.h>			// Header File For Windows Math Library
#include <stdio.h>			// Header File For Standard Input/Output
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <GL/glfw3.h>


// Desired fullscreen resolution
//#define WIDTH  640
//#define HEIGHT 480

// Window dimensions
double WIDTH=640;
double HEIGHT=480;


// "Running" flag (true if program shall continue to run)
int running;


// "wireframe" flag (true if we use wireframe view)
int wireframe;


static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS)
    {
        switch (key)
        {
            case GLFW_KEY_ESCAPE:
                glfwSetWindowShouldClose(window, GLFW_TRUE);
                break;
            case GLFW_KEY_W:
                wireframe = !wireframe;
                glPolygonMode(GL_FRONT_AND_BACK,
                              wireframe ? GL_LINE : GL_FILL);
                break;
            default:
                break;
        }
    }
}


//========================================================================
// Resize() - GLFW window resize callback function
//========================================================================


static void resize_callback(GLFWwindow* window, int x, int y)
{
    WIDTH = x;
    HEIGHT = y > 0 ? y : 1;   // Prevent division by zero in aspect calc.
    glViewport(0, 0, x, y);
}


int main(int argc, char **argv){

    int        frames;
    double     t0, t;

    GLFWwindow* window;
    GLFWmonitor* monitor = NULL;

	printf("glfw3 version: %s\n ", glfwGetVersionString());

    // Initialize GLFW
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        exit( EXIT_FAILURE );
    }


    window = glfwCreateWindow(WIDTH, HEIGHT, "Template glfw3", monitor, NULL);
    if (!window)
    {
        fprintf(stderr, "Failed to create GLFW window\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }


    glfwMakeContextCurrent(window);
    // Disable VSync (we want to get as high FPS as possible!)
    glfwSwapInterval( 1 );


    // Window resize callback function
    glfwSetFramebufferSizeCallback(window, resize_callback);


    // Set keyboard input callback function
    glfwSetKeyCallback(window, key_callback);



    // Main loop
    t0 = glfwGetTime();
    frames = 0;

    // Set "running" flag
    running = 1;
    
    fprintf( stderr, "Running GLFW window\n" );

    while( running )
    {

        // Get frame time
        t = glfwGetTime() - t0;

        // Draw...
//        Draw( t );
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();


        // Check if window was closed
        running = running && !glfwWindowShouldClose(window);

        // Increase frame count
        frames ++;

        // End of benchmark?
       // после 1 минуты выход из цикла
        if(  t >= 60.0 )
        {
            running = 0;
        }
 
   }
     t = glfwGetTime() - t0;

    // Display profiling information
    printf( "%d frames in %.2f seconds   =   %.1f FPS \n", frames, t,
            (double)frames / t );


   // Terminate OpenGL
    glfwTerminate();

    exit( EXIT_SUCCESS );

}


     
