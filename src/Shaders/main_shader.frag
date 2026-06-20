#version 460 core
out vec4 FragColor;
  
in vec4 vertexColor; // Variable d'entrée identique à la sortie du vertex shader
uniform vec4 our_color;

void main()
{
    FragColor = our_color;
}