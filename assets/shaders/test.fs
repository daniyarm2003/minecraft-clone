#version 330 core

uniform sampler2D blockAtlas;

in vec3 color;
in vec2 texCoord;

out vec4 fragColor;

void main() {
    fragColor = texture(blockAtlas, texCoord) * vec4(color, 1.0);
}