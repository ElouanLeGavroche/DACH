#include "../../../include/src_include/Context/View/view_main_menu_context.h"
void init_render_main_menu(st_render_data *render)
{
    // On va associé la caméra dans Opengl, car on peut-en avoir besoin dans les callbacks
    GLFWwindow *window = glfwGetCurrentContext();
    
    st_window_user_data *data = glfwGetWindowUserPointer(window);
    data->camera = &render->camera;
}
void update_render_main_menu(st_render_data *render, double time)
{
    render_context(render, time);   
}
