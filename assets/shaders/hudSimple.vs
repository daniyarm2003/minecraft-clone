#version 330 core

uniform mat4 hudTransform;
uniform mat4 componentTransform;

layout (location=0) in vec2 aPos;
layout (location=1) in vec2 aTexCoord;

out vec2 texCoord;

void main() {
    gl_Position = hudTransform * componentTransform * vec4(aPos, 0.0, 1.0);
    texCoord = aTexCoord;
}