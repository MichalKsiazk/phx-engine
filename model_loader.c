#include "model_loader.h"

typedef struct model3d
{
    float* vertices_array;
    unsigned int* indices_array;
    unsigned int v_size;
    unsigned int i_size;
} m3d_t;


m3d_t* new_m3d(char *source_name)
{
    m3d_t* new_model = (m3d_t*) malloc(sizeof(m3d_t));
    char* source = read_model_source(source_name);

    read_vertices(new_model, source);
    read_indices(new_model, source);
    free(source);
    return new_model;
}

char* read_model_source(char *source_name)
{
    FILE *file_pointer;
    file_pointer = fopen(source_name, "r");


    char *source;
    if(file_pointer == NULL) 
    {
        perror(strcat("Error while opening the file: ", source_name));
        return 0;
    }
    else 
    {
        //read file
        fseek(file_pointer, 0, SEEK_END);
        long fsize = ftell(file_pointer);
        fseek(file_pointer, 0, SEEK_SET);

        source = (char*)malloc(fsize + 1);
        fread(source, 1, fsize, file_pointer);

    }
    fclose(file_pointer);
    return source;
}

void read_vertices(m3d_t* model, char* source)
{
    unsigned int source_size = strlen(source);
    char* vertices = malloc(sizeof(char*) * source_size);
    uint8_t write_mode = 0x0;
    int i = 0;
    int n = 0;
    while(1)
    {
        if(source[n] == 'v')
        {
            write_mode = 0xF;
        }
        if(source[n] == '\n')
        {
            write_mode = 0x0;
        }

        if(source[n] != 'v' && source[n] != '\n' && write_mode)
        {
            vertices[i] = source[n];
            i++;
        }
        n++;
        if(n == source_size)
        {
            break;
        }
    }
    vertices[i] = '\0';

    int start = 0;
    int end = 0;

    int total = 1;



    for(int n = 1; n <= i; n++)
    {
        if(vertices[n] == ' ')
        {
            end = n;
            start = end;
            total++;
        }
    }


    start = 0;
    end = 0;

    model->v_size = total;
    model->vertices_array = (float*) malloc(sizeof(float) * (total));
    total = 0;
    for(int n = 1; n <= i; n++)
    {
        if(vertices[n] == ' ' || vertices[n] == '\0')
        {
            end = n;
            int size = end - start;
            char v[size];
            strncpy(v, &vertices[start], size);
            v[size] = '\0';
            start = end;
            model->vertices_array[total] = strtof(v, NULL);
            total ++;
        }
    }
    free(vertices);
}

void read_indices(m3d_t* model, char* source)
{
    unsigned int source_size = strlen(source);
    char* indices = malloc(sizeof(char*) * source_size);
    uint8_t write_mode = 0x0;
    int i = 0;
    int n = 0;
    while(1)
    {
        if(source[n] == 'f')
        {
            write_mode = 0xF;
        }
        if(source[n] == '\n')
        {
            write_mode = 0x0;
        }

        if(source[n] != 'f' && source[n] != '\n' && write_mode)
        {
            indices[i] = source[n];
            i++;
        }
        n++;
        if(n == source_size)
        {
            break;
        }
    }
    indices[i] = '\0';
    //printf("%s\n", indices);

    int start = 0;
    int end = 0;

    int total = 1;



    for(int n = 1; n <= i; n++)
    {
        if(indices[n] == ' ')
        {
            end = n;
            start = end;
            total++;
        }
    }
    printf("%d\n", total);

    start = 0;
    end = 0;

    model->i_size = total;
    model->indices_array = (int*) malloc(sizeof(unsigned int) * (total));
    total = 0;

    for(int n = 1; n <= i; n++)
    {
        if(indices[n] == ' ' || indices[n] == '\0')
        {
            end = n;
            int size = end - start;
            char v[size];
            strncpy(v, &indices[start+1], size);
            v[size] = '\0';
            start = end;
            //printf("%s\n", v);
            model->indices_array[total] = (int)strtol(v, (char **)NULL, 10) - 1;
            total ++;
        }
    }
    free(indices);

}

void free_m3d(m3d_t* model)
{
    //free(model->indices_array);
    //free(model->vertices_array);
    //free(model);
}

float* get_vertices(m3d_t* model)
{
    return model->vertices_array;
}
unsigned int* get_indices(m3d_t* model)
{
    return model->indices_array;
}
unsigned int get_vertices_size(m3d_t* model)
{
    return model->v_size;
}
unsigned int get_indices_size(m3d_t* model)
{
    return model->i_size;
}

void print_vertices(m3d_t* model)
{
    for(int i = 0; i < model->v_size; i++)
    {
        printf("%f\n", model->vertices_array[i]);
    }
}

void print_indices(m3d_t* model)
{
    for(int i = 0; i < model->i_size; i++)
    {
        printf("%d\n", model->indices_array[i]);
    }
}
