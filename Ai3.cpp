#include <GLFW/glfw3.h>



struct Cell {
    bool visited;
    bool walls[4]; // Top, Right, Bottom, Left
};

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);


        glBegin(GL_LINES);
        glColor3f(1.0, 0.0, 0.0);  // Red color
        glVertex2f(0.0, 0.0);  // Starting point of the line
        glVertex2f(1.0, 1.0);  // Ending point of the line
        glEnd();


        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}