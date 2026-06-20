#version 460 core

out vec4 frag_color;
in vec3 our_color; // Variable d'entrée identique à la sortie du vertex shader

void main()
{
    frag_color = vec4(our_color, 1.0);
}