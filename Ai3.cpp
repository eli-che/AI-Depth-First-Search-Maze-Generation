#include <GLFW/glfw3.h>
#include <vector>
#include <windows.h>

struct Cell {
    bool visited;
    bool walls[4]; // Top, Right, Bottom, Left
};

void drawCell(float x, float y, float wallLength, const Cell& cell) {
    // Left Wall
    if (cell.walls[3]) { // Check if left wall should be drawn
        glBegin(GL_LINES);
        glColor3f(1.0, 0.0, 0.0); // Red color
        glVertex2f(x - wallLength, y + wallLength);
        glVertex2f(x - wallLength, y - wallLength);
        glEnd();
    }

    // Top Wall
    if (cell.walls[0]) { // Check if top wall should be drawn
        glBegin(GL_LINES);
        glColor3f(1.0, 0.0, 0.0); // Red color
        glVertex2f(x - wallLength, y + wallLength);
        glVertex2f(x + wallLength, y + wallLength);
        glEnd();
    }

    // Right Wall
    if (cell.walls[1]) { // Check if right wall should be drawn
        glBegin(GL_LINES);
        glColor3f(1.0, 0.0, 0.0); // Red color
        glVertex2f(x + wallLength, y + wallLength);
        glVertex2f(x + wallLength, y - wallLength);
        glEnd();
    }

    // Bottom Wall
    if (cell.walls[2]) { // Check if bottom wall should be drawn
        glBegin(GL_LINES);
        glColor3f(1.0, 0.0, 0.0); // Red color
        glVertex2f(x - wallLength, y - wallLength);
        glVertex2f(x + wallLength, y - wallLength);
        glEnd();
    }
}


int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "DFS Maze Generator", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);



    const int gridSize = 15;
    std::vector<Cell> cells(gridSize * gridSize);
    const float wallLength = 0.06f;

    //Set all cell walls to true
    for (int i = 0; i < gridSize * gridSize; ++i) {
		cells[i].walls[0] = true;
		cells[i].walls[1] = true;
		cells[i].walls[2] = true;
		cells[i].walls[3] = true;
	}
        

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {

        //on keyboard press set all cells walls to false
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
            for (int i = 0; i < gridSize * gridSize; ++i) {
				cells[i].walls[0] = false;
				cells[i].walls[1] = false;
				cells[i].walls[2] = false;
				cells[i].walls[3] = false;
			}
		}

        //on keyboard alt press set all cell walls to true


        if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS) {
			for (int i = 0; i < gridSize * gridSize; ++i) {
            cells[i].walls[0] = true;
            cells[i].walls[1] = true;
            cells[i].walls[2] = true;
            cells[i].walls[3] = true;
            }
        }

        //set a few random walls to false to create a maze
        for (int i = 0; i < gridSize * gridSize; ++i) {
            if (rand() % 2 == 0) {
				cells[i].walls[0] = false;
			}
            if (rand() % 2 == 0) {
				cells[i].walls[1] = false;
			}
            if (rand() % 2 == 0) {
				cells[i].walls[2] = false;
			}
            if (rand() % 2 == 0) {
				cells[i].walls[3] = false;
			}
		}


        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);


       
        for (int i = 0; i < gridSize; ++i) {
            for (int j = 0; j < gridSize; ++j) {
                float x = wallLength * i + wallLength; // Cell center x-coordinate
                float y = wallLength * j + wallLength; // Cell center y-coordinate
                drawCell(x, y, wallLength, cells[i * gridSize + j]);
            }
        }
       
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

