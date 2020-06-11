#include "bmfont.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"

typedef struct ascii_symbol
{
    uint64_t id;

    uint64_t x;
    uint64_t y;

    uint64_t height;
    uint64_t width;

    float text_coords_buffer_id;

} a_symbol;

void bmfont_init(char* img_path, char* cfg_path)
{

    load_font_config(cfg_path);

    float vertices[] =
    {
        -1.0,  1.0, 0.0, 
         1.0,  1.0, 0.0,
        -1.0, -1.0, 0.0,
         1.0, -1.0, 0.0
    };

    unsigned int faces[] =
    {
        1, 2, 0,
        1, 3, 2
    };

    vbo_size = sizeof(vertices);
    eab_size = sizeof(faces);


    glGenVertexArrays(1, &font_vao);
    glBindVertexArray(font_vao);

    glGenBuffers(1, &font_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, font_vbo);
    glBufferData(GL_ARRAY_BUFFER, vbo_size, vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glGenBuffers(1, &font_eab );
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, font_eab);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, eab_size, faces, GL_STATIC_DRAW);



    font_shader = gen_shader_program(GEN_VS("shaders/font.vert"), 0, GEN_FS("shaders/font.frag"));
    int width, height, channels;

    char* font_image = stbi_load(img_path, &width, &height, &channels, STBI_rgb_alpha);

    stbi__vertical_flip(font_image, width, height, STBI_rgb_alpha);

    fsize_x = width;
    fsize_y = height;


    if(!font_image)
    {
        printf("failed to load texture\n");
        return;
    }

	glActiveTexture(GL_TEXTURE0);
    glEnable(GL_TEXTURE_2D);
    gen_texture_maps(ascii_charset, font_image, width, height);
    glEnable( GL_BLEND );
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

    stbi_image_free(font_image);

}

static void load_font_config(char* filename)
{
    char* line = NULL;
    size_t len = 0;
    size_t read;

    uint64_t line_number = 0;

    ascii_charset = (a_symbol*) malloc(CHARSET_LENGHT * sizeof(a_symbol));
    FILE* config_file = fopen(filename, "r");
    if(config_file == NULL)
    {
        printf("cant open config file\n");
        return;
    }
    while ((read = getline(&line, &len, config_file)) != -1) 
    {

        //printf("%s\n", line);
        if(line_number > 1)
        {
            set_charset(ascii_charset, line);
        }
        line_number++;
    }

    fclose(config_file);

}

static void set_charset(a_symbol** ascii_charset, char* cfg_line)
{
    uint64_t id = get_parameter(cfg_line, CFG_ID_SHIFT);

    a_symbol* new_symbol = (a_symbol*) malloc(sizeof(a_symbol));

    new_symbol->id      = id;
    new_symbol->x       = get_parameter(cfg_line, CFG_X_SHIFT);
    new_symbol->y       = get_parameter(cfg_line, CFG_Y_SHIFT);
    new_symbol->height  = get_parameter(cfg_line, CFG_HEIGHT_SHIFT);
    new_symbol->width   = get_parameter(cfg_line, CFG_WIDTH_SHIFT);

    ascii_charset[id] = new_symbol;
}

static uint64_t get_parameter(char* cfg_line, uint64_t shift)
{
    int i = 0;
    while(cfg_line[shift + i] >= 48 && cfg_line[shift + i] <= 57)
    {       
        i++;
    }
    char parameter[i+1];
    memcpy(parameter, &cfg_line[shift], i);
    parameter[i] = '\0';
    return strtol(parameter, NULL, 10);
}

static uint64_t gen_texture(char* img, int width, int height, int channels)
{
    uint64_t texture; 
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameterf(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); 
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img);
    glGenerateMipmap(GL_TEXTURE_2D);
    return texture;
}

void bmfont_render_char(char c, float size, float x, float y)
{

    glUseProgram(font_shader);


    glUniform2f(glGetUniformLocation(font_shader, "scale"), size, size);
    glUniform1f(glGetUniformLocation(font_shader, "aspect_ratio"), PHX_ASPECT_RATIO);
    glUniform2f(glGetUniformLocation(font_shader, "position"), x, y);

    glBindTexture(GL_TEXTURE_2D, font_texture);

    glBindBuffer(GL_ARRAY_BUFFER, font_vbo);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);


    glBindBuffer(GL_ARRAY_BUFFER, ascii_charset[c]->text_coords_buffer_id);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, false, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, font_eab);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glDisableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
	glBindVertexArray(0);  
}

void bmfont_render_string(char* s, float size, float x, float y)
{
    float x_pointer = x;
    float y_pointer = y;
    for(int i = 0; i < strlen(s); i++)
    {
        bmfont_render_char((char)s[i], size, x_pointer, y_pointer);
        x_pointer += 1.5 * size;
    }
}

static void gen_texture_maps(a_symbol** ascii_charset, char* img, int width, int height)
{
    font_texture = gen_texture(img, width, height, 0);
    for(int i = 0; i < CHARSET_LENGHT; i++)
    {
        if(ascii_charset[i] != NULL)
        {
            gen_map(ascii_charset[i], width, height);
        }
    }
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

static void gen_map(a_symbol* ac, int width, int height)
{
    float coords[8];
    //LU , RU, LD, RD
    coords[0] = (float) ac->x / (float) width; //x
    coords[1] = (float) (height - ac->y) / height; //y
    coords[2] = (float) (ac->x + ac->width) / (float) width;; //x
    coords[3] = (float) (height - ac->y) / height;
    coords[4] = (float) ac->x / (float) width;
    coords[5] = (float) (height - ac->y - ac->height) / height; //y
    coords[6] = (float) (ac->x + ac->width) / (float) width;; //x
    coords[7] = (float) (height - ac->y - ac->height) / height; //y

    int buffer_id; 


    glGenBuffers(1, &buffer_id);
    glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
    glBufferData(GL_ARRAY_BUFFER, sizeof(coords), coords, GL_STATIC_DRAW);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
    ac->text_coords_buffer_id = buffer_id;
}


static void print_ascii_charset(uint64_t id)
{
    printf("id: %d x: %d y: %d: width: %d height: %d\n",
    ascii_charset[id]->id,
    ascii_charset[id]->x,
    ascii_charset[id]->y,
    ascii_charset[id]->width,
    ascii_charset[id]->height
    );
}

void set_font_color(float _r, float _g, float _b, float _a)
{
    r = _r;
    g = _g;
    b = _b;
    a = _a;
    glUseProgram(font_shader);
    glUniform4f(glGetUniformLocation(font_shader, "color"), r, g, b, a);
    glUseProgram(0);
}




