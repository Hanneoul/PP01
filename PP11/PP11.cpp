#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>

#include "MMath.hpp"
#include "Player.hpp"

#pragma comment(lib, "OpenGL32")




Player* p = new Player(0.1f, 0.9f, 0.9f, MuSeoun::vec3(1.0f, 0.0f, 0.0f));
Player* e = new Player(0.1f, 0.0f, 0.0f, MuSeoun::vec3(0.0f, 0.0f, 1.0f));

static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);

    if (key == GLFW_KEY_UP && action == GLFW_PRESS)
        p->MoveUp(0.01f);
    if (key == GLFW_KEY_UP && action == GLFW_RELEASE)
        p->MoveUp(0.0f);
    if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
        p->MoveUp(-0.01f);
    if (key == GLFW_KEY_DOWN && action == GLFW_RELEASE)
        p->MoveUp(0.0f);
    if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
        p->MoveRight(0.01f);
    if (key == GLFW_KEY_RIGHT && action == GLFW_RELEASE)
        p->MoveRight(0.0f);
    if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
        p->MoveRight(-0.01f);
    if (key == GLFW_KEY_LEFT && action == GLFW_RELEASE)
        p->MoveRight(0.0f);



}






int main(void)
{
    GLFWwindow* window;
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        exit(EXIT_FAILURE);
    window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    while (!glfwWindowShouldClose(window))
    {
        float ratio;
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float)height;



        glClearColor(.0f, 0.0f, 0.0f, 0.1f);
        glClear(GL_COLOR_BUFFER_BIT);

        for (int i = 0; i < 4; i++)
        {
            if (p->quad[2].x < e->quad[i].x && e->quad[i].x < p->quad[1].x)
            {
                if (p->quad[2].y < e->quad[i].y && e->quad[i].y < p->quad[1].y)
                {
                    printf("충돌!!\n");
                }
            }

        }


        p->Render();
        e->Render();

        /*
        glBegin(GL_TRIANGLES);
        glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
        glVertex3f(0.0f, 1.0f, 0.0f);
        glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
        glVertex3f(1.0f, -1.0f, 0.0f);
        glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
        glVertex3f(-1.0f, -1.0f, 0.0f);
        glEnd();

        glBegin(GL_TRIANGLES);
        glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
        glVertex2f(0.0f, 1.0f);

        glVertex2f(1.0f, -1.0f);

        glVertex2f(-1.0f, -1.0f);
        glEnd();

        glBegin(GL_TRIANGLES);
        glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
        glVertex2f(0.0f, 1.0f);

        glVertex2f(1.0f, -1.0f);

        glVertex2f(-1.0f, -1.0f);
        glEnd();
        */
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    delete(p);
    delete(e);
    exit(EXIT_SUCCESS);
}