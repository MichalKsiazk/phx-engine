#include "phx_engine.h"

#include <stdio.h>
#include <stdlib.h> 
#include <time.h> 

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "renderer.h"
#include "shader.h"
#include "phx_config.h"
#include "atom.h"
#include "collision_system.h"
#include "utils.h"
#include "sp_system.h"


void init_engine(GLFWwindow* window)
{
    //createCapabilities();
    bmfont_init(DEBUG_FONT_IMG_LOCATION , DEBUG_FONT_CFG_LOCATION);

    zero_point = new_vec3d(0,0,0);
    glClearColor(0.0f, 0.2f, 0.2f, 0.0f);

    init_renderer();
    int atoms_count = 10;
    atom3d** atoms = (atom3d*) malloc(get_atom3d_size() * atoms_count);

    init_counter();
	init_sp_system();
    set_random_seed();

    for(int i = 0; i < atoms_count; i++)
    {

        double rx = random_range(-2,2);
        double ry = random_range(-2,2);
        double rz = random_range(-2,2);

        atoms[i] = init_atom3d(i, new_vec3d(rx, ry, rz), NULL);
		set_color(atoms[i], DEFAULT_ATOM_COLOR);
    }

	color_changes = 0;
    
    vec3d* mouse_pos = new_vec3d(0,0,0);





    //printf("WTF IG GOING ON\n");
    init_cls_event_system(atoms_count);
    while ( !glfwWindowShouldClose(window) ) 
    {
        
        move_camera(window);     

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the framebuffer

		set_font_color(1,1,1,1);
        count_fps();
		//update_sp_system();	
		for(int i = 0; i < atoms_count; i++)
		{
			move_towards(get_translation(atoms[i]), get_atom_pos(atoms[i]), zero_point, 0.00006);
		}
        for(int i = 0; i < atoms_count; i++)
        {
            
            find_collisions(i, atoms, atoms_count);

        }
		

        execute_cls_events(atoms);
		
        for(int i = 0; i < atoms_count; i++)
        {
            reset_cls_list(atoms[i]);
        }
        clear_cls_event_list();
        
        for(int i = 0; i < atoms_count; i++)
        {
            move_atom3d(atoms[i]);
        }
        render_atoms(atoms, atoms_count, GLOBAL_ATOM_RADIUS);

        render_scenery();
        
        glfwSwapBuffers(window); // swap the color buffers

        glfwPollEvents();
		printf("COLLISIONS: %d\n", detected_collisions);
		color_changes = 0;
		detected_collisions = 0;
  }
}
