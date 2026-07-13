#version 460 core
layout (location = 0) in vec3 a_pos; // La variable position a l'attribut de position 0
layout (location = 1) in vec3 a_color; // Variable color à la pos 1
layout (location = 2) in vec2 a_tex_coord; // Les textures

layout (location = 3) in vec4 mod_col0;
layout (location = 4) in vec4 mod_col1;
layout (location = 5) in vec4 mod_col2;
layout (location = 6) in vec4 mod_col3;

uniform mat4 view;
uniform mat4 projection;

out vec3 our_color;             // Nous définirons la couleur dans cette variable
out vec2 text_coord;


void main()
{
    mat4 model = mat4(mod_col0, mod_col1, mod_col2, mod_col3);
    gl_Position =  projection * view * model * vec4(a_pos , 1.0);

    our_color = a_color;
    text_coord = a_tex_coord;
}