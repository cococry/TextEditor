#pragma once

#include "defines.h"

typedef struct subtexture2d {
    u32 atlas_width, atlas_height;
    vector2 coords, cell_size, sprite_scale;
} subtexture2d;

subtexture2d subtexture2d_create(u32 width, u32 height, vector2 coords, vector2 cell_size, vector2 sprite_scale);

typedef struct subtexture_coords {
    vector2 min, max;
} subtexture_coords;

subtexture_coords subtexture2d_get_texcoords(subtexture2d texture);