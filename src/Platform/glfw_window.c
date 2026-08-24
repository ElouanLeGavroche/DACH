#include "../../include/src_include/Platform/glfw_window.h"

int init_window(st_window_user_data *user_data, st_loaded_windows_data *window_data)
{
    // Charger les informations de la fenêtre dans le Json
    // Fichier    
    FILE *fp;
    char buffer[1024] = {'\0'};

    // Structures des différents éléments stocké dans le JSON
    struct json_object *parsed_json;
    struct json_object *size_x;
    struct json_object *size_y;
    struct json_object *frame_rate;

    // Variables des valeur à récuperer
    int size_x_value;
    int size_y_value;
    int frame_rate_value;

    fp = fopen(PATH_LOAD_GAME_DATA, "r");
    if(fp == NULL){
        printf("Fichier non trouvé\n");
        return RES_NULL_POINTER;
    }
    else{
        printf("fichier ouvert\n");
    }

    fread(buffer, 1024, 1, fp);
    fclose(fp);

    parsed_json = json_tokener_parse(buffer);

    // Parser la struct dans les sous structures adéquat 
    json_object_object_get_ex(parsed_json, "size_x", &size_x);
    json_object_object_get_ex(parsed_json, "size_y", &size_y);
    json_object_object_get_ex(parsed_json, "frame_rate", &frame_rate);

    size_x_value = json_object_get_int(size_x);
    size_y_value = json_object_get_int(size_y);
    frame_rate_value = json_object_get_int(frame_rate);

    
    //Vider la mémoire
    json_object_put(parsed_json);

    // Vérification de la cohérence des données récuperer
    if
    (
        !(
        (7680 > size_x_value && size_x_value > 352) &&
        (4320 > size_y_value && size_y_value > 240) &&
        (360 > frame_rate_value && frame_rate_value > 20)
        )    
    )
    
    {
        printf(" Valeur incohérente ! \n mise en place de valeur par défault : \n x:%d \n y:%d \n fps:%d \n",
        SCREEN_WITH_DEFAULT, SCREEN_HEIGHT_DEFAULT, SCREEN_FRAME_RATE_DEFAUL);
        
        size_x_value = SCREEN_WITH_DEFAULT;
        size_y_value = SCREEN_HEIGHT_DEFAULT;
        frame_rate_value = SCREEN_FRAME_RATE_DEFAUL;
    }
    // Allocation des informations de la fenêtre
    global_window = malloc(sizeof(st_loaded_windows_data));
    if(!global_window)
    {
        fprintf(stderr, "Allocation échouer : %s\n", strerror(errno));
        return RES_FAILED_MALLOC;
    }

    global_window->size_x = size_x_value;
    global_window->size_y = size_y_value;
    global_window->frame_rate = frame_rate_value;
    
    window_data = global_window;

    // Initialiser les informations récupéré
    if (!glfwInit())
        return RES_ERROR;
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(window_data->size_x, window_data->size_y, "Douar ar c'hornôg", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return RES_ERROR;
    }
    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        glfwDestroyWindow(window);
        glfwTerminate();

        fprintf(stderr, "Failed to initialize GLAD\n");
        return RES_ERROR;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetWindowUserPointer(window, user_data);

    return RES_DONE;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height){
    
    st_window_user_data *data = glfwGetWindowUserPointer(window);
    if(data != NULL)
    {
        
        if(data->window != NULL && data->camera != NULL)
        {
            st_loaded_windows_data *window_parametr = data->window;
            st_camera *camera = data->camera;

            window_parametr->size_x = width;
            window_parametr->size_y = height;

            camera->ratio = ((float)window_parametr->size_x / (float)window_parametr->size_y) * (4.0f / 3.0f);

            gl_update_view_port(window_parametr->size_x, window_parametr->size_y);
        }
    }

}

void view_clear(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void view_swap(){
    // Récupéré le context openGL
    GLFWwindow *window = glfwGetCurrentContext();
    
    // Actualisation du swap
    glfwSwapBuffers(window);
}

void view_close_window(){
    GLFWwindow *window = glfwGetCurrentContext();
    
    glfwDestroyWindow(window);
    glfwTerminate();
}

int window_should_close(){
    if (glfwWindowShouldClose(glfwGetCurrentContext()))
    {
        return -1;
    }
    else
    {
        return 0;
    }
}


st_loaded_windows_data *get_window_information()
{
    return global_window;
}