#ifndef GLFW_WINDOW
#define GLFW_WINDOW

#include "../Config/constantes.h"
#include "../../types.h"
#include "../../../extern_lib/glad/glad.h"


#include "../Renderer/opengl_renderer.h"

#include <GLFW/glfw3.h>
#include <json-c/json.h>
#include <errno.h>
#include <string.h>

int init_window(st_window_user_data *user_data, st_loaded_windows_data *window_data);
void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void view_clear();
void view_swap();
void view_close_window();
int window_should_close();
st_loaded_windows_data *get_window_information();

static st_loaded_windows_data *global_window;

#endif