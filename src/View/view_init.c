#include "../../include/src_include/View/view_init.h"

//#include VIEW_PATH "view_init.h"

int init_View(st_loaded_windows_data *window_data)
{
    
    if (!glfwInit())
        return ERROR;
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(window_data->size_x, window_data->size_y, "Douar ar c'hornôg", NULL, NULL);
    
    if (!window)
    {
        glfwTerminate();
        return EXIT_FAILURE;
    }
    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Failed to initialize GLAD");
        return -1;
    }

    /* Activer le test de profondeur */
    glEnable(GL_DEPTH_TEST);

    return DONE;
}

void init_camera(st_render_data *render)
{
    glm_mat4_identity(render->camera.view_point);
    printf("yo\n");
    float radius = 10.0f;
    float cam_x = sin(glfwGetTime()) * radius;
    float cam_z = cos(glfwGetTime()) * radius;

    mat4 view;
    glm_mat4_identity(view);

    glm_lookat((vec3){cam_x, 0.0, cam_z}, (vec3){0.0, 0.0, 0.0}, (vec3){0.0, 1.0, 0.0}, view);
    
    glm_mat4_copy(view, render->camera.view_point);
}