#include "../../include/src_include/Model/model_group_context.h"


void create_an_object(int name, st_mesh mesh, int texture_id, float x, float y, float z, st_mesh_group *dest)
{
    st_render_object obj;
    obj.mesh_obj = mesh;
    obj.texture_id = texture_id;
    obj.x_pos = x;
    obj.y_pos = y;
    obj.z_pos = z;
    
    object_init(&obj, name);

    put_object_in_a_mesh_group(dest, &obj);

}

void create_a_shader(unsigned int id, st_mesh_group *dest)
{
    st_shader shader;
    shader_init(&shader, id);
    put_shader_in_mesh_group(dest, &shader);
}




// INSTANCED

void create_a_shared_shader(unsigned int id, st_mesh_group *dest)
{
    st_shader shader;
    shader_init(&shader, id);
    put_shader_in_mesh_group(dest, &shader);
}