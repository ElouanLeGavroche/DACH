#version 460 core

out vec4 frag_color;
  
in vec3 our_color;
in vec2 texture_coord;

uniform sampler2D our_texture;

void main()
{
    frag_color = texture(our_texture, texture_coord);
}