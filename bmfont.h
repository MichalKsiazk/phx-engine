#ifndef BMFONT_H
#define BMFONT_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "model_loader.h"
#include "renderer.h"
#include "shader.h"
#include "phx_config.h"
#include <cglm/cglm.h>

#define DEBUG_FONT_IMG_LOCATION "fonts/ubuntu.png" 
#define DEBUG_FONT_CFG_LOCATION "fonts/ubuntu.fnt"

#define CFG_ID_SHIFT        8
#define CFG_X_SHIFT         18  
#define CFG_Y_SHIFT         25 
#define CFG_WIDTH_SHIFT     36
#define CFG_HEIGHT_SHIFT    48


#define CHARSET_LENGHT 128

static float r, g, b, a;

typedef struct ascii_symbol a_symbol;

static int font_vao;
static int font_vbo;
static unsigned int vbo_size;

static int font_eab;
static unsigned int eab_size;

static int font_shader;

static int font_texture;
static int fsize_x;
static int fsize_y;

void bmfont_init(char* img_path, char* cfg_path);

void bmfont_render_char(char c, float size, float x, float y);
void bmfont_render_string(char* s, float size, float x, float y);

static void load_font_config(char* filename);
static void gen_texture_maps(a_symbol** ascii_charset, char* img, int width, int height);
static void gen_map(a_symbol* ascii_charset, int width, int height);

static uint64_t gen_texture(char* img, int width, int height, int channels);

static void set_charset(a_symbol** ascii_charset, char* cfg_line);

static uint64_t get_parameter(char* cfg_line, uint64_t shift);

a_symbol** ascii_charset;
static void print_ascii_charset(uint64_t id);

void set_font_color(float _r, float _g, float _b, float _a);

#endif
