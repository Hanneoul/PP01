#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>

#pragma comment(lib, "OpenGL32")




static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
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

    while (!glfwWindowShouldClose(window))
    {
        float ratio;
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float)height;


        glClearColor(0.3f, 0.3f, 0.3f, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);

        glBegin(GL_TRIANGLES);
        glColor4f(1.0f, 0.0f, 0.0f,0.3f);
        glVertex3f(0.0f,1.0f,0.0f);
        glColor4f(1.0f, 0.0f, 0.0f, 0.3f);
        glVertex3f(1.0f, -1.0f, 0.0f);
        glColor4f(1.0f, 0.0f, 0.0f, 0.3f);
        glVertex3f(-1.0f, -1.0f, 0.0f);
        glEnd();

        glBegin(GL_TRIANGLES);
        glColor4f(1.0f, 1.0f, 0.0f, 0.3f);
        glVertex3f(0.0f, 1.0f, 0.0f);
        glColor4f(1.0f, 1.0f, 0.0f, 0.3f);
        glVertex3f(1.0f, -1.0f, 0.0f);
        glColor4f(1.0f, 0.0f, 1.0f, 0.3f);
        glVertex3f(-1.0f, -1.0f, 0.0f);
        glEnd();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}