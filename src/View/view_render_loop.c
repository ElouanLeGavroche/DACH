#include "../../include/src_include/View/view_render_loop.h"

void view_render_loop(bool safe_lock){
    /**
     * Cette fonction utilise un booléen pour locker les deux threads (controller et view) afin d'éviter les conflits d'accès à la mémoire partagée.
     * Le thread view va se mettre en attente tant que le booléen est à false.
     */
    
    /*récupérer le contexte OpenGl*/
    GLFWwindow *window = glfwGetCurrentContext();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    
    {
        safe_lock = false;

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();

        safe_lock = true;
    }   
    glfwTerminate();
}