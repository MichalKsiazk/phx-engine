#include <stdint.h>
#include "atom.h"
#include "sp_system.h"
#include "phx_config.h"

enum collision_status
{
    COLLISION_NOT_DETECTED = 0x00,
    COLLISION_DETECTED = 0x01
};

typedef struct collision_event cls_event_t;
typedef struct detected_collision_list dtc_cls_list_t;



cls_event_t* cls_event_list;



cls_event_t* new_cls_event(unsigned int a_id, unsigned int b_id, double dst, cls_event_t* next);
void push_cls_event(cls_event_t* event_list, cls_event_t* new_event);
void init_cls_event_system(unsigned int atoms_count);

int nearest_atom_id(atom3d** atoms, unsigned int ac_size, vec3f* point);

uint8_t check_point(vec3d* point, double radius, vec3d* pos);

void find_collisions(unsigned int atom_id, atom3d** atoms, unsigned int ac_size);

void update_system();

uint8_t test_nn_collision(unsigned int atom_id, atom3d** atoms, unsigned int ac_size);

void execute_cls_events(atom3d** atoms);

void clear_cls_event_list();

unsigned int list_lenght(void* head);
void clear_cls_index(unsigned int arr_size);


