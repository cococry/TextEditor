#include "font_renderer.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <glad/glad.h>
#include <stb_image.h>
#include "subtexture.h"

font_struct font_renderer_init_font(const char* filepath) {
    font_struct ret;
    glGenTextures(1, &ret.font_texture_id);
    glBindTexture(GL_TEXTURE_2D, ret.font_texture_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    stbi_set_flip_vertically_on_load(true);

    i32 number_of_channles;
    u8* data = stbi_load(filepath, &ret.width, &ret.height, &number_of_channles, 0);

    if(data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, ret.width, ret.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    } else {
        printf("Failed to load texture %s", filepath);
    }

    stbi_image_free(data);

    glCreateVertexArrays(1, &ret.vao); 
    glBindVertexArray(ret.vao);

    glCreateBuffers(1, &ret.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, ret.vbo);
    ret.vertex_buffer_capacity = 20;
    ret.vertex_data = malloc(sizeof(font_vertex) * 6 * ret.vertex_buffer_capacity);
    glBufferData(GL_ARRAY_BUFFER, sizeof(font_vertex) * 6 * ret.vertex_buffer_capacity, nullptr, GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, nullptr);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void*)(intptr_t)(sizeof(float) * 2));

    
   return ret;
}

void font_renderer_delete_font(font_struct* font) {
}

void font_renderer_render_string(float x, float y, float scale, vector4 color, const char* text, font_struct font, shader_program* shader) {
    glBindVertexArray(font.vao);
    glBindBuffer(GL_ARRAY_BUFFER, font.vbo);

    shader_program_upload_int(shader, "uTexture", 0);
    shader_program_upload_mat4(shader, "uProj", orthographic_matrix(0.0f, 900.0f, 600.0f, 0.0f));
    glActiveTexture(font.font_texture_id);
    glBindTexture(GL_ARRAY_BUFFER, font.font_texture_id);

    u32 len = strlen(text);

    if(font.vertex_buffer_capacity < len) {
        font.vertex_buffer_capacity = len;
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 4 * 6 * font.vertex_buffer_capacity, nullptr, GL_STATIC_DRAW);
        free(font.vertex_data);
        font.vertex_data = malloc(sizeof(font_vertex) * 6 * font.vertex_buffer_capacity);
    }

    u32 num_vertices = 0;
    u32 xoffset = 0;
    for(u32 i = 0; i < len; i++) {
        
        vector2 coords;
        for(u32 i = 0; i < (int)text[i]; i++) {
            coords.x++;
            if(i % (int)(font.width / 32.0f) == 0) {
                coords.y++;
                coords.x = 0;
            }
        }

        subtexture2d tex = subtexture2d_create(font.width, font.height, (vector2){0.0f, 3.0f}, (vector2){32.0f, 32.0f}, (vector2){1.0f, 1.0f});

        subtexture_coords texcoords = subtexture2d_get_texcoords(tex);

        font.vertex_data[0].position = (vector2){-0.5f, -0.5f}; font.vertex_data[0].texcoord = (vector2){texcoords.min.x, texcoords.min.y};
        font.vertex_data[1].position = (vector2){-0.5f,  0.5f}; font.vertex_data[1].texcoord = (vector2){texcoords.min.x, texcoords.max.y};
        font.vertex_data[2].position = (vector2){ 0.5f,  0.5f}; font.vertex_data[2].texcoord = (vector2){texcoords.max.x, texcoords.max.y};
        font.vertex_data[3].position = (vector2){-0.5f, -0.5f}; font.vertex_data[3].texcoord = (vector2){texcoords.min.x, texcoords.min.y};
        font.vertex_data[4].position = (vector2){ 0.5f, -0.5f}; font.vertex_data[4].texcoord = (vector2){texcoords.max.x, texcoords.min.y};
        font.vertex_data[5].position = (vector2){ 0.5f,  0.5f}; font.vertex_data[5].texcoord = (vector2){texcoords.max.x, texcoords.max.y};


        shader_program_bind(shader);
        shader_program_upload_mat4(shader, "uModel", matrix4_mult(translate_mv(matrix4_identity(), (vector3){x, y, 0.0f}), scale_mv(matrix4_identity(), (vector3){scale, scale, scale})));

        num_vertices += 6;
        xoffset += 32.0f;
    }
    
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(font_vertex) * 6 * font.vertex_buffer_capacity, font.vertex_data);

    printf("%i\n",num_vertices);
    glDrawArrays(GL_TRIANGLES, 0, num_vertices);
}