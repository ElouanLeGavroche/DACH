#version 460 core
layout (location = 0) in vec3 a_pos; // La variable position a l'attribut de position 0
layout (location = 1) in vec3 a_color; // Variable color à la pos 1

uniform mat4 transform;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 our_color;             // Nous définirons la couleur dans cette variable

void main()
{
    gl_Position =  projection * view * model * transform * vec4(a_pos, 1.0);
    //gl_Position = transform * vec4(a_pos, 1.0); // un vec3 est utilisé pour construire un vec4
    our_color = a_color;
}