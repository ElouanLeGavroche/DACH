#version 460 core

out vec4 frag_color;
  
in vec3 our_color;
in vec2 text_coord;

uniform sampler2D our_texture;

void main()
{
    frag_color = texture(our_texture, text_coord) * vec4(our_color, 1.0);;
}