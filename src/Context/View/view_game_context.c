#include "../../../include/src_include/Context/View/view_game_context.h"

void update_render_game(st_render_data *render){
    
    glClearColor(num_to_01(5), num_to_01(12), num_to_01(123), 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
    };  
    /*
    unsigned int VBO;
    glGenBuffers(1, &VBO);  

    glBindBuffer(GL_ARRAY_BUFFER, VBO);  

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    */
}