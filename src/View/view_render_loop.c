#include "../../include/src_include/View/view_render_loop.h"

void view_render_loop(GLFWwindow *window){
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
}