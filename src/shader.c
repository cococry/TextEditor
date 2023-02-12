#include "shader.h"
#include <stdio.h>
#include <stdlib.h>
#include <glad/glad.h>

char* get_file_content(const char* filename) {
    char* buffer = 0;
    long length;
    FILE* f = fopen(filename, "rb");

    if (f) {
        fseek(f, 0, SEEK_END);
        length = ftell(f);
        fseek(f, 0, SEEK_SET);
        buffer = malloc(length);
        if (buffer) {
            fread(buffer, 1, length, f);
        }
        fclose(f);

        buffer[length] = '\0';
    }

    ASSERT(buffer != nullptr);

    return buffer;
}


shader_program* shader_program_create(const char* vertex_filepath, const char* fragment_filepath) {
    shader_program* ret = malloc(sizeof(shader_program));
    const char* vertex_source = get_file_content(vertex_filepath);
    const char* fragment_source = get_file_content(fragment_filepath);

    render_id vertex_shader = _compile_gl_shader(vertex_source, GL_VERTEX_SHADER);
    render_id fragment_shader = _compile_gl_shader(fragment_source, GL_FRAGMENT_SHADER);

    _link_gl_shader_program(ret, vertex_shader, fragment_shader);

    return ret;
}

void shader_program_bind(shader_program* program) {
    glUseProgram(program->id);
}

void shader_program_unbind(shader_program* program) {
    glUseProgram(0);
}

void shader_program_delete(shader_program* program) {
    glDeleteProgram(program->id);

    free(program);
}

void shader_program_upload_vec2(shader_program* program, const char* uniform_name, vector2 uniform_value) {
    glUniform2fv(glGetUniformLocation(program->id, uniform_name), 1, vector2_value_ptr(uniform_value));
}
void shader_program_upload_vec3(shader_program* program, const char* uniform_name, vector3 uniform_value) {
    glUniform3fv(glGetUniformLocation(program->id, uniform_name), 1, vector3_value_ptr(uniform_value));
}

void shader_program_upload_vec4(shader_program* program, const char* uniform_name, vector4 uniform_value) {
    float* value = vector4_value_ptr(uniform_value);
    glUniform4fv(glGetUniformLocation(program->id, uniform_name), 1, value);
    free(value);
}

void shader_program_upload_int(shader_program* program, const char* uniform_name, i32 uniform_value) {
    glUniform1i(glGetUniformLocation(program->id, uniform_name), uniform_value);
}

void shader_program_upload_int_array(shader_program* program, const char* uniform_name, i32* values, u32 count) {
    glUniform1iv(glGetUniformLocation(program->id, uniform_name), count, values);
}

void shader_program_upload_mat4(shader_program* program, const char* uniform_name, matrix4 uniform_value) {
    float* value = matrix4_value_ptr(uniform_value);
    glUniformMatrix4fv(glGetUniformLocation(program->id, uniform_name), 1, GL_FALSE, value);
    free(value);
}

void shader_program_upload_float(shader_program* program, const char* uniform_name, float uniform_value) {
    glUniform1f(glGetUniformLocation(program->id, uniform_name), uniform_value);
}
void _link_gl_shader_program(shader_program* program, render_id vertex_shader, render_id fragment_shader) {
    int linking_success;
    char info_log[512];

    program->id = glCreateProgram();

    glAttachShader(program->id, vertex_shader);
    glAttachShader(program->id, fragment_shader);

    glLinkProgram(program->id);

    glGetProgramiv(program->id, GL_LINK_STATUS, &linking_success);

    if (!linking_success) {
        glGetProgramInfoLog(program->id, 512, nullptr, info_log);

        printf("Failed to link shader program.\n");
        printf("%s", info_log);
    } else {
        printf("Successfully linked shader program (render id: %i)\n", program->id);
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}

render_id _compile_gl_shader(const char* shader_source, u32 type) {
    int compile_success;
    char info_log[512];

    render_id ret;

    ret = glCreateShader(type);
    glShaderSource(ret, 1, &shader_source, nullptr);
    glCompileShader(ret);

    glGetShaderiv(ret, GL_COMPILE_STATUS, &compile_success);

    char* shader_name = malloc(sizeof(char) * 15);
    switch (type) {
        case GL_VERTEX_SHADER:
            shader_name = "vertex";
            break;
        case GL_FRAGMENT_SHADER:
            shader_name = "fragment";
            break;
        default:
            shader_name = "unknown";
            break;
    }

    if (!compile_success) {
        glGetShaderInfoLog(ret, 512, nullptr, info_log);

        printf("Failed to compile %s shader.\n", shader_name);
        printf("%s\n", info_log);
    } else {
        printf("Successfully compiled %s shader.\n", shader_name);
    }

    return ret;
}