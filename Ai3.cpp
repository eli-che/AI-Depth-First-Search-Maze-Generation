#include <GLFW/glfw3.h>
#include <vector>
#include <windows.h>
#include <iostream>
#include <chrono>
#include <random>
#include <algorithm>
#include <math.h>
#include <stack>
#include <cstdlib>

bool areAlmostEqual(float a, float b) {
    float epsilon = 0.01f;
    return std::abs(a - b) <= epsilon;
}

struct Cell {
    bool visited;
    bool walls[4]; // Top, Right, Bottom, Left
    float x;
    float y;
    // Generate random color values
    float randomRed = 1.0f; // Generates values between 0.3 and 1.0
    float randomGreen = 0.0f; // Set green component to 0 (no green)
    float randomBlue = 0.0f;  // Set blue component to 0 (no blue)

};

void drawCell(const Cell& cell, float wallLength) {
    wallLength /= 2.0f; // Half the wall length to get the corner coordinates
    // Left Wall
    if (cell.walls[3]) { // Check if left wall should be drawn
        glBegin(GL_LINES);
        glColor3f(cell.randomRed, cell.randomGreen, cell.randomBlue); // Set random color
        glVertex2f(cell.x - wallLength, cell.y + wallLength);
        glVertex2f(cell.x - wallLength, cell.y - wallLength);
        glEnd();
    }

    // Top Wall
    if (cell.walls[0]) { // Check if top wall should be drawn
        glBegin(GL_LINES);
        glColor3f(cell.randomRed, cell.randomGreen, cell.randomBlue); // Set random color
        glVertex2f(cell.x - wallLength, cell.y + wallLength);
        glVertex2f(cell.x + wallLength, cell.y + wallLength);
        glEnd();
    }

    // Right Wall
    if (cell.walls[1]) { // Check if right wall should be drawn
        glBegin(GL_LINES);
        glColor3f(cell.randomRed, cell.randomGreen, cell.randomBlue); // Set random color
        glVertex2f(cell.x + wallLength, cell.y + wallLength);
        glVertex2f(cell.x + wallLength, cell.y - wallLength);
        glEnd();
    }

    // Bottom Wall
    if (cell.walls[2]) { // Check if bottom wall should be drawn
        glBegin(GL_LINES);
        glColor3f(cell.randomRed, cell.randomGreen, cell.randomBlue); // Set random color
        glVertex2f(cell.x - wallLength, cell.y - wallLength);
        glVertex2f(cell.x + wallLength, cell.y - wallLength);
        glEnd();
    }
}


int main(void)
{
    int width = 1000;
    int height = 1000;
    int gridSize = 30;
    float wallLength = 1.8f / gridSize;
    float offset = (gridSize / 2) * wallLength;

    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(width, height, "DFS Maze Generator", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    std::vector<Cell> cells(gridSize * gridSize);

    //Set all cell walls to true
    for (int i = 0; i < gridSize * gridSize; ++i) {
        cells[i].walls[0] = true;
        cells[i].walls[1] = true;
        cells[i].walls[2] = true;
        cells[i].walls[3] = true;
    }
    


    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            float x = wallLength * i - offset; // Cell center x-coordinate
            float y = wallLength * j - offset; // Cell center y-coordinate
            //print the cell center coordinates
           // std::cout << "Cell center coordinates: " << x << ", " << y << std::endl;
            //set the cell center coordinates in the struct
            cells[i * gridSize + j].x = x;
            cells[i * gridSize + j].y = y;
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);



            for (int i = 0; i < gridSize; ++i) {
                for (int j = 0; j < gridSize; ++j) {
                    drawCell(cells[i * gridSize + j], wallLength);
                }
            }

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }



    //select a random starting cell
    srand(time(NULL));
    int currentCell = rand() % (gridSize * gridSize);
    //print currentCell
    //set the starting cell to visited
    cells[currentCell].visited = true;
    //create a stack for the visited cells
    std::vector<int> visitedStack;
    //push the starting cell to the stack
    visitedStack.push_back(currentCell);
    //Randomly select an adjecent cell that has not been visisted and remove the wall between them. If all neighbors have been visited, pop the stack. until the stack is empty or there are no unvisited neighbors
    while (!visitedStack.empty()) {
        //sleep 100ms
        Sleep(50);
        //Randomly find an unvisited neighbor for the current cell on top of the stack
        bool topCheck = false;
        bool rightCheck = false;
        bool bottomCheck = false;
        bool leftCheck = false;
        bool found = false;
        //if the stack is not empty, set the current cell to the top of the stack

        currentCell = visitedStack.back();


        while (found == false && (topCheck == false || rightCheck == false || bottomCheck == false || leftCheck == false)) {
        //check the top neighbor by taking the coordinate of the current cell and adding one walllength to the y coordinate and looping through the cells to find the cell with the same coordinates and check if it has been visited
        //Generate number 0-3 to randomly select a neighbor
            int randomNeighbor = rand() % 4;

            if (randomNeighbor == 0) {
                topCheck = true;
                if (found == false) {
                    for (int i = 0; i < gridSize * gridSize; ++i) {
                        if(areAlmostEqual(cells[i].y, cells[currentCell].y + wallLength) && areAlmostEqual(cells[i].x, cells[currentCell].x)){
                            if (!cells[i].visited) {
                                //mark cell as visited
                                cells[i].visited = true;
                                //push the cell ontop of the stack
                                visitedStack.push_back(i);
                                //remove the wall between the current cell and the neighbor
                                cells[currentCell].walls[0] = false;
                                cells[i].walls[2] = false;
                                //restart at top of while loop
                                found = true;
                                //break out of for loop

        /* Render here */
                                glClear(GL_COLOR_BUFFER_BIT);



                                for (int i = 0; i < gridSize; ++i) {
                                    for (int j = 0; j < gridSize; ++j) {
                                        drawCell(cells[i * gridSize + j], wallLength);
                                    }
                                }

                                //at currentCell.x and currentCell.y, draw a circle
                                glBegin(GL_POLYGON);
                                glColor3f(0.0, 0.0, 1.0); // Blue color
                                glVertex2f(cells[currentCell].x - 0.01f, cells[currentCell].y + 0.01f);
                                glVertex2f(cells[currentCell].x + 0.01f, cells[currentCell].y + 0.01f);
                                glVertex2f(cells[currentCell].x + 0.01f, cells[currentCell].y - 0.01f);
                                glVertex2f(cells[currentCell].x - 0.01f, cells[currentCell].y - 0.01f);
                                glEnd();

                                /* Swap front and back buffers */
                                glfwSwapBuffers(window);

                                /* Poll for and process events */
                                glfwPollEvents();
                                break;
                            }
                        }
                    }
                    //break out of while loop
                    if(found == true)
                    break;
                }
            }

            if (randomNeighbor == 1) {
                rightCheck = true;
                if (found == false) {
                    //check the right neighbor by taking the coordinate of the current cell and adding one walllength to the x coordinate and looping through the cells to find the cell with the same coordinates and check if it has been visited
                    for (int i = 0; i < gridSize * gridSize; ++i) {
                        if(areAlmostEqual(cells[i].x, cells[currentCell].x + wallLength) && areAlmostEqual(cells[i].y, cells[currentCell].y)){
                            if (!cells[i].visited) {
                                //mark cell as visited
                                cells[i].visited = true;
                                //push the cell ontop of the stack
                                visitedStack.push_back(i);
                                //remove the wall between the current cell and the neighbor
                                cells[currentCell].walls[1] = false;
                                cells[i].walls[3] = false;
                                //restart at top of while loop
                                found = true;

                                /* Render here */
                                glClear(GL_COLOR_BUFFER_BIT);


                               
                                for (int i = 0; i < gridSize; ++i) {
                                    for (int j = 0; j < gridSize; ++j) {
                                        drawCell(cells[i * gridSize + j], wallLength);
                                    }
                                }
                                //at currentCell.x and currentCell.y, draw a circle
                                glBegin(GL_POLYGON);
                                glColor3f(1.0, 1.0, 0.0);
                                glVertex2f(cells[currentCell].x - 0.01f, cells[currentCell].y + 0.01f);
                                glVertex2f(cells[currentCell].x + 0.01f, cells[currentCell].y + 0.01f);
                                glVertex2f(cells[currentCell].x + 0.01f, cells[currentCell].y - 0.01f);
                                glVertex2f(cells[currentCell].x - 0.01f, cells[currentCell].y - 0.01f);
                                glEnd();

                                /* Swap front and back buffers */
                                glfwSwapBuffers(window);

                                /* Poll for and process events */
                                glfwPollEvents();
                                break;
                            }
                        }
                    }
                    if(found == true)
                    break;
                }
            }
            if (randomNeighbor == 2) {
                bottomCheck = true;
                if (found == false) {
                    //check the bottom neighbor by taking the coordinate of the current cell and subtracting one walllength to the y coordinate and looping through the cells to find the cell with the same coordinates and check if it has been visited
                    for (int i = 0; i < gridSize * gridSize; ++i) {
                        if(areAlmostEqual(cells[i].y, cells[currentCell].y - wallLength) && areAlmostEqual(cells[i].x, cells[currentCell].x)){
                            if (!cells[i].visited) {
                                //mark cell as visited
                                cells[i].visited = true;
                                //push the cell ontop of the stack
                                visitedStack.push_back(i);
                                //remove the wall between the current cell and the neighbor
                                cells[currentCell].walls[2] = false;
                                cells[i].walls[0] = false;
                                //restart at top of while loop
                                found = true;

                                /* Render here */
                                glClear(GL_COLOR_BUFFER_BIT);



                                for (int i = 0; i < gridSize; ++i) {
                                    for (int j = 0; j < gridSize; ++j) {
                                        drawCell(cells[i * gridSize + j], wallLength);
                                    }
                                }

                                //at currentCell.x and currentCell.y, draw a circle
                                glBegin(GL_POLYGON);
                                glColor3f(1.0, 1.0, 0.0);
                                glVertex2f(cells[currentCell].x - 0.01f, cells[currentCell].y + 0.01f);
                                glVertex2f(cells[currentCell].x + 0.01f, cells[currentCell].y + 0.01f);
                                glVertex2f(cells[currentCell].x + 0.01f, cells[currentCell].y - 0.01f);
                                glVertex2f(cells[currentCell].x - 0.01f, cells[currentCell].y - 0.01f);
                                glEnd();

                                /* Swap front and back buffers */
                                glfwSwapBuffers(window);

                                /* Poll for and process events */
                                glfwPollEvents();
                                break;
                            }
                        }
                    }
                    if(found == true)
                    break;
                }
            }

            if (randomNeighbor == 3) {
                leftCheck = true;
                if (found == false) {
                    //check the left neighbor by taking the coordinate of the current cell and subtracting one walllength to the x coordinate and looping through the cells to find the cell with the same coordinates and check if it has been visited
                    for (int i = 0; i < gridSize * gridSize; ++i) {
                        if(areAlmostEqual(cells[i].x, cells[currentCell].x - wallLength) && areAlmostEqual(cells[i].y, cells[currentCell].y)){
                            if (!cells[i].visited) {
                                //mark cell as visited
                                cells[i].visited = true;
                                //push the cell ontop of the stack
                                visitedStack.push_back(i);
                                //remove the wall between the current cell and the neighbor
                                cells[currentCell].walls[3] = false;
                                cells[i].walls[1] = false;
                                //restart at top of while loop
                                found = true;
                                //break out of for loop

        /* Render here */
                                glClear(GL_COLOR_BUFFER_BIT);



                                for (int i = 0; i < gridSize; ++i) {
                                    for (int j = 0; j < gridSize; ++j) {
                                        drawCell(cells[i * gridSize + j], wallLength);
                                    }
                                }

                                //at currentCell.x and currentCell.y, draw a circle
                                glBegin(GL_POLYGON);
                                glColor3f(1.0, 1.0, 0.0);
                                glVertex2f(cells[currentCell].x - 0.01f, cells[currentCell].y + 0.01f);
                                glVertex2f(cells[currentCell].x + 0.01f, cells[currentCell].y + 0.01f);
                                glVertex2f(cells[currentCell].x + 0.01f, cells[currentCell].y - 0.01f);
                                glVertex2f(cells[currentCell].x - 0.01f, cells[currentCell].y - 0.01f);
                                glEnd();

                                /* Swap front and back buffers */
                                glfwSwapBuffers(window);

                                /* Poll for and process events */
                                glfwPollEvents();
                                break;
                            }
                        }
                    }
                    //break out of while loop
                    if(found == true)
                    break;
                }
            }
        }
    
       
        if (found == false) {
            //if all neighbors have been visited, pop the stack
            visitedStack.pop_back();

        }

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);



        for (int i = 0; i < gridSize; ++i) {
            for (int j = 0; j < gridSize; ++j) {
                drawCell(cells[i * gridSize + j], wallLength);
            }
        }
        glBegin(GL_POLYGON);
        glColor3f(1.0, 1.0, 0.0);
        glVertex2f(cells[currentCell].x - 0.01f, cells[currentCell].y + 0.01f);
        glVertex2f(cells[currentCell].x + 0.01f, cells[currentCell].y + 0.01f);
        glVertex2f(cells[currentCell].x + 0.01f, cells[currentCell].y - 0.01f);
        glVertex2f(cells[currentCell].x - 0.01f, cells[currentCell].y - 0.01f);
        glEnd();
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();



    }

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {


        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);


       
        for (int i = 0; i < gridSize; ++i) {
            for (int j = 0; j < gridSize; ++j) {
                drawCell(cells[i * gridSize + j], wallLength);
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

