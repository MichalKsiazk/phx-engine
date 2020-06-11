#include "collision_system.h"

#include <stdio.h>
#include <stdlib.h> 
#include <float.h>

typedef struct collision_event
{
    unsigned int a_id;
    unsigned int b_id;

    double dst;

    struct collision_event* next;

} cls_event_t;



cls_event_t* new_cls_event(unsigned int a_id, unsigned int b_id, double dst, cls_event_t* next)
{
    cls_event_t* new_event = (cls_event_t*) malloc(sizeof(cls_event_t));
    new_event->a_id = a_id;
    new_event->b_id = b_id;

    new_event->dst = dst;

    new_event->next = next;
    return new_event;
}

void push_cls_event(cls_event_t* event_list, cls_event_t* new_event)
{
    cls_event_t * current = event_list;
    while (current->next != NULL) 
    {
        current = current->next;
    }
    current->next = new_event;
}

void init_cls_event_system(unsigned int atoms_count)
{
    cls_event_list = (cls_event_t*) calloc(1, sizeof(cls_event_t));

}

void clear_cls_event_list()
{
    cls_event_t * current = cls_event_list;
    while (1) 
    {
        cls_event_t* next;
        if(current->next != NULL)
        {
            next = current->next;
            free(current);
            current = next;
        }
        else { break; }
    }
    //free(cls_event_list);
    cls_event_list = (cls_event_t*) calloc(1, sizeof(cls_event_t));
}

uint8_t check_collision(atom3d* atom_a, atom3d* atom_b)
{
    return 0;
}

uint8_t test_nn_collision(unsigned int atom_id, atom3d** atoms, unsigned int ac_size)
{
    float red_color = 0;

    uint8_t colliding = 0x0;

    for(int j = 0; j < ac_size; j++)
    {
        if(j == atom_id) continue;
        
        double dst = distance3d(get_atom_pos(atoms[atom_id]), get_atom_pos(atoms[j]));

        
        

        if(dst < 2 * GLOBAL_ATOM_RADIUS)
        {
            colliding = 0x1;
            red_color = (float)dst / (2 * GLOBAL_ATOM_RADIUS);
            vec3d* dir = get_dir_normalized(get_atom_pos(atoms[atom_id]), get_atom_pos(atoms[j]));

            set_outer_border_color(atoms[atom_id], 1 - red_color, 1 + 1/red_color, 0);
            //set_outer_border_color(atoms[atom_id], 1, 1, 0);

            double force = (float)dst / (2 * GLOBAL_ATOM_RADIUS);

            move_in_direction(get_translation(atoms[atom_id]), dir, -0.0000004 * pow((1/force), 9));
            free(dir);
        }
        else
        {
            //set_outer_border_color(atoms[atom_id], 0, 1, 0);
        }
        
    }
    return colliding;
}

void find_collisions(unsigned int atom_id, atom3d** atoms, unsigned int ac_size)
{
    for(int j = 0; j < ac_size; j++)
    {
        if(j == atom_id) continue;
        
        uint8_t was_detected = check_for_cls(atoms[atom_id], j);

        if(was_detected)
        {
            continue;
        }

        double dst = distance3d(get_atom_pos(atoms[atom_id]), get_atom_pos(atoms[j]));

        
        

        if(dst < 2 * GLOBAL_ATOM_RADIUS)
        {
            cls_t* cls = new_cls_t(atom_id, NULL);
            push_cls(atoms[j], cls);
            cls_event_t* new_event = new_cls_event(atom_id, j, dst, NULL);

            push_cls_event(cls_event_list, new_event);
        }
        else
        {
            //set_outer_border_color(atoms[atom_id], 0, 1, 0);
        }
        
    }
}

int nearest_atom_id(atom3d** atoms, unsigned int ac_size, vec3f* point)
{

    double min_dst = DBL_MAX;

    int atom_id = -1;

    for(int i = 0; i < ac_size; i++)
    {
        double new_dst = distance2d(get_atom_pos(atoms[i]), point);
        if(new_dst < min_dst)
        {
            min_dst = new_dst;
            atom_id = i;
        }
    }
    return atom_id;
}

void execute_cls_events(atom3d** atoms)
{
    cls_event_t * current = cls_event_list;
    while (current->next != NULL) 
    {
    current = current->next;
    
    vec3d* dir = get_dir_normalized(get_atom_pos(atoms[current->a_id]), get_atom_pos(atoms[current->b_id]));

    double force = (float)current->dst / (2 * GLOBAL_ATOM_RADIUS);

    //0.0000004
    move_in_direction(get_translation(atoms[current->a_id]), dir, -0.00003 * pow((1/force), 3));
    invert_vec3d(dir);
    move_in_direction(get_translation(atoms[current->b_id]), dir, -0.00003 * pow((1/force), 3));

    free(dir);

    }
}



unsigned int list_lenght(void* head)
{
    unsigned int retval = 0;
    cls_event_t * current = head;
    while (current->next != NULL) 
    {
        current = current->next;
        retval++;
    }
    return retval;
}

uint8_t check_point(vec3d* point, double radius, vec3d* pos)
{
    double dst = distance2d(point, pos);
    if(dst < radius)
    {
        return 0x1;
    }
    return 0x0;
}