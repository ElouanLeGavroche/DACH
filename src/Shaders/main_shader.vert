#version 460 core
layout (location = 0) in vec2 a_pos; // La variable position a l'attribut de position 0
layout (location = 1) in vec3 a_color; // Variable color à la pos 1
layout (location = 2) in vec2 a_tex_coord; // Les textures

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 our_color;             // Nous définirons la couleur dans cette variable
out vec2 text_coord;

uniform vec2 offests[52*52];

void main()
{
    vec2 offest = offests[gl_InstanceID];
    gl_Position =  projection * view * model * vec4(a_pos + offest, 0.0, 1.0);
    our_color = a_color;
    text_coord = a_tex_coord;
}