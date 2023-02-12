#pragma once

#include "defines.h"
#include "shader.h"

typedef struct font_vertex {
    vector2 position, texcoord;
} font_vertex;

typedef struct font_struct {
    u32 font_texture_id;
    i32 width, height;
    u32 vbo, vao;
    u32 vertex_buffer_capacity;
    font_vertex* vertex_data;
} font_struct;

font_struct font_renderer_init_font(const char* filepath);

void font_renderer_delete_font(font_struct* font);

void font_renderer_render_string(float x, float y, float scale, vector4 color, const char* text, font_struct font, shader_program* shader);