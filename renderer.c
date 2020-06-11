#include <math.h>

#include "renderer.h"



const float aspect_ratio = WINDOW_SIZE_X / WINDOW_SIZE_Y;
float fov = 70;
float near_plane = 0.1f;
float far_plane = 1000.0f;

float camera_pos_x = 1;
float camera_pos_y = 0;
float camera_pos_z = 0;

float camera_dir_x = 0;
float camera_dir_y = 0;
float camera_dir_z = 0;


mat4 projection;

void init_renderer()
{

    glEnable(GL_DEPTH_TEST); 
    glDisable(GL_CULL_FACE);

    float y_scale = (float) ((1.0f / tanf(deg_to_rad(fov / 2.0f))) * aspect_ratio);
    float x_scale = (float) y_scale / aspect_ratio;
    float frustum_lenght = far_plane - near_plane;

    projection[0][0] = x_scale;
    projection[1][1] = y_scale;
    projection[2][2] = -((far_plane + near_plane) / frustum_lenght);
    projection[3][2] = -((2 * near_plane * far_plane) / frustum_lenght);
    projection[2][3] = -1;


    //init_camera(glm_ve

    float zero_point_buffer[] = { 0.0f,  0.0f, 0.0f};

    #ifdef GEOMETRY_RENDERER

    common_vbo_id = gen_vbo(&zero_point_buffer[0], 3);


    atom_vert_shader = gen_shader(GL_VERTEX_SHADER, "shaders/test.vert");
    atom_geom_shader = gen_shader(GL_GEOMETRY_SHADER, "shaders/test.geom");
    atom_frag_shader = gen_shader(GL_FRAGMENT_SHADER, "shaders/test.frag");

    atom_shader_program = gen_shader_program(atom_vert_shader, atom_geom_shader, atom_frag_shader);

    glUseProgram(atom_shader_program);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, common_vbo_id);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0,(void*) 0);

    glUniform1f(glGetUniformLocation(atom_shader_program, "aspect_ratio"), (float)PHX_ASPECT_RATIO);
    printf("%f\n", (float)PHX_ASPECT_RATIO);

    #endif
    #ifdef INSTANCE_RENDERER

    m3d_t* plane = new_m3d("models/plane.obj");
    gen_model(plane, &floor_vbo, &floor_vao, &floor_ibo, &floor_vao_lenght);

    m3d_t* model = new_m3d("models/sphere2.obj");
    gen_model(model, &common_vbo, &common_vao, &common_ibo, &common_vao_lenght);


    atom_vert_shader = gen_shader(GL_VERTEX_SHADER, "shaders/instance.vert");
    atom_frag_shader = gen_shader(GL_FRAGMENT_SHADER, "shaders/instance.frag");

    atom_shader_program = gen_shader_program(atom_vert_shader, 0, atom_frag_shader);

    glUseProgram(atom_shader_program);
    free_m3d(model);
    #endif

    


}


 void gen_model(m3d_t* model, unsigned int* vbo, unsigned int* vao, unsigned int* ibo, unsigned int* lenght)
 {
    unsigned int vertices_array_size = sizeof(float) * get_vertices_size(model);

    unsigned int indices_array_size = sizeof(unsigned int) * get_indices_size(model);
    *lenght = get_indices_size(model);

    glGenVertexArrays(1, vao);
    glBindVertexArray(vao);

    glGenBuffers(1, vbo );
    glBindBuffer(GL_ARRAY_BUFFER, *vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices_array_size, get_vertices(model), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glGenBuffers(1, ibo );
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_array_size, get_indices(model), GL_STATIC_DRAW);
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
 }

 

void render_atoms(atom3d** atoms, unsigned int atoms_count, float scale)
{
    glUseProgram(atom_shader_program);
    //glUniform1f(glGetUniformLocation(atom_shader_program, "radius"), GLOBAL_ATOM_RADIUS);
    glUniform1f(glGetUniformLocation(atom_shader_program, "scale"), scale);

    glUniformMatrix4fv(glGetUniformLocation(atom_shader_program, "projection"), 1, GL_FALSE, projection);
    load_view_matrix();


    mat4 transformation;
    glm_mat4_identity(transformation);
    glm_translate(transformation, (vec3){0, -0.5f, -1});
    glm_rotate(transformation, TO_RADIANS(0), (vec3){1,0,0});
    glm_rotate(transformation, TO_RADIANS(0), (vec3){0,1,0});
    glm_rotate(transformation, TO_RADIANS(0), (vec3){0,0,1});
    glm_scale(transformation, (vec3){GLOBAL_ATOM_RADIUS,GLOBAL_ATOM_RADIUS,GLOBAL_ATOM_RADIUS});

    glUniformMatrix4fv(glGetUniformLocation(atom_shader_program, "transformation"), 1, GL_FALSE, (float*)transformation);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, common_vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, common_ibo);

    for(int i = 0; i < atoms_count; i++)
    {         

        #ifdef GEOMETRY_RENDERER
        geometry_render_atom3d(atoms[i], atom_shader_program);
        #endif
        #ifdef INSTANCE_RENDERER
        instance_render_atom3d(atoms[i], atom_shader_program, common_vao_lenght);
        #endif
    }

    glDisableVertexAttribArray(0);

}

void load_view_matrix()
{
    mat4 view;

    glm_mat4_identity(view);
    glm_translate(view, (vec3) {camera_pos_x, camera_pos_y, camera_pos_z});
    glm_rotate(view, TO_RADIANS(camera_dir_x), (vec3){1,0,0});
    glm_rotate(view, TO_RADIANS(camera_dir_y), (vec3){0,1,0});
    glm_rotate(view, TO_RADIANS(camera_dir_z), (vec3){0,0,1});
    glm_scale(view, (vec3){1,1,1});


    glUniformMatrix4fv(glGetUniformLocation(atom_shader_program, "view"), 1, GL_FALSE, (float *)view);
}


int gen_vbo(float *vertices, unsigned int vertices_size)
{
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices_size, vertices, GL_STATIC_DRAW);
    return VBO;
}

void render_shape(unsigned int vao_id, unsigned int vao_size)
{
    glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vao_id);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0,(void*) 0);
	glDrawArrays(GL_TRIANGLES, 0, vao_size);
	glDisableVertexAttribArray(0);
}

void move_camera(GLFWwindow* window)
{
    int w_state = glfwGetKey(window, GLFW_KEY_W);
    int s_state = glfwGetKey(window, GLFW_KEY_S);
    int a_state = glfwGetKey(window, GLFW_KEY_A);
    int d_state = glfwGetKey(window, GLFW_KEY_D);

    if(w_state == GLFW_PRESS)
        camera_pos_z += 0.1f;
    if(s_state == GLFW_PRESS)
        camera_pos_z -= 0.1f;

    if(a_state == GLFW_PRESS)
        camera_pos_x += 0.1f;
    if(d_state == GLFW_PRESS)
        camera_pos_x -= 0.1f;

    int up_state = glfwGetKey(window, GLFW_KEY_UP);
    int left_state = glfwGetKey(window, GLFW_KEY_LEFT);
    int right_state = glfwGetKey(window, GLFW_KEY_RIGHT);
    int down_state = glfwGetKey(window, GLFW_KEY_DOWN);

    if(up_state == GLFW_PRESS)
        camera_dir_x -= 0.5f;
    if(down_state == GLFW_PRESS)
        camera_dir_x += 0.5f;

    if(left_state == GLFW_PRESS)
        camera_dir_y -= 0.5f;
    if(right_state == GLFW_PRESS)
        camera_dir_y += 0.5f;


}

void render_scenery()
{
    glEnableVertexAttribArray(0);

    glUniform1f(glGetUniformLocation(atom_shader_program, "scale"), 10);
    mat4 transformation;
    glm_mat4_identity(transformation);
    glm_translate(transformation, (vec3){0, -5 - GLOBAL_ATOM_RADIUS, 0});
    glm_rotate(transformation, TO_RADIANS(0), (vec3){1,0,0});
    glm_rotate(transformation, TO_RADIANS(0), (vec3){0,1,0});
    glm_rotate(transformation, TO_RADIANS(0), (vec3){0,0,1});
    glm_scale(transformation, (vec3){1,1,1});

    glUniformMatrix4fv(glGetUniformLocation(atom_shader_program, "transformation"), 1, GL_FALSE, (float*)transformation);
    glUniform3f(glGetUniformLocation(atom_shader_program, "new_color"), 0.7f, 0.7f, 0.7f);

    glBindBuffer(GL_ARRAY_BUFFER, floor_vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, floor_ibo);
    glDrawElements(GL_TRIANGLES, floor_vao_lenght, GL_UNSIGNED_INT, NULL);
    glDisableVertexAttribArray(0);
}
