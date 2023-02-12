#pragma once

#include "defines.h"

typedef struct shader_program {
    u32 id;
} shader_program;

shader_program* shader_program_create(const char* vertex_filepath, const char* fragment_filepath);

void shader_program_bind(shader_program* program);

void shader_program_unbind(shader_program* program);

void shader_program_delete(shader_program* program);

void shader_program_upload_vec2(shader_program* program, const char* uniform_name, vector2 uniform_value);

void shader_program_upload_vec3(shader_program* program, const char* uniform_name, vector3 uniform_value);

void shader_program_upload_vec4(shader_program* program, const char* uniform_name, vector4 uniform_value);

void shader_program_upload_mat4(shader_program* program, const char* uniform_name, matrix4 uniform_value);

void shader_program_upload_int(shader_program* program, const char* uniform_name, i32 uniform_value);

void shader_program_upload_int_array(shader_program* program, const char* uniform_name, i32* values, u32 count);

void shader_program_upload_float(shader_program* program, const char* uniform_name, float uniform_value);

void _link_gl_shader_program(shader_program* program, render_id vertex_shader, render_id fragment_shader);

render_id _compile_gl_shader(const char* shader_source, u32 type);
