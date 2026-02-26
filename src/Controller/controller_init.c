#include "../../include/src_include/Controller/controller_init.h"

int init_game()
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return EXIT_FAILURE;

    /* Create a windowed mode window and its OpenGL context */
    // -1- Charger les donnée propre à la fenêtre
    t_loaded_windows_data data;
    int res;

    res = c_load_screen_data(&data);
    
    if(res == ERROR){
        printf("Erreur\n");
        return EXIT_FAILURE;
    }
    // -2- Crée le contexte OpenGL
    window = glfwCreateWindow(data.size_x, data.size_y, "Hello World", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return EXIT_FAILURE;
    }
    
    /* Make the window's context current */
    glfwMakeContextCurrent(window);

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
    return EXIT_SUCCESS;
}