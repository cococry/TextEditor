#version 460 core

out vec4 oColor;

in vec2 vTexcoord;

uniform sampler2D uTexture;

uniform vec4 uColor;

void main() {
    vec4 color = texture(uTexture, vTexcoord);

    oColor = color;
}