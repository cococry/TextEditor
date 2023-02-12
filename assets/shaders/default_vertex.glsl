#version 460 core

layout(location = 0) in vec2 aPosition;
layout(location = 1) in vec2 aTexcoord;

uniform mat4 uProj;
uniform mat4 uModel;

out vec2 vTexcoord;

void main() {
    vTexcoord = aTexcoord;
    gl_Position =  uProj * uModel * vec4(aPosition, 0.0, 1.0);
}