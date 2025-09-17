#version 330 core

const int CHUNK_SIZE_X = 16;
const int CHUNK_SIZE_Y = 64;
const int CHUNK_SIZE_Z = 16;

uniform mat4 viewProjMatrix;

uniform int blockAtlasWidthInBlocks;
uniform int blockAtlasHeightInBlocks;
uniform int blockAtlasBlockPixelSize;

uniform int blockSize;

uniform int chunkCoordX;
uniform int chunkCoordZ;

layout (location=0) in uvec3 blockPos;
layout (location=1) in uvec2 blockTexCoords;

out vec2 texCoords;

void main() {
    ivec3 chunkOffset = ivec3(CHUNK_SIZE_X * chunkCoordX, 0, CHUNK_SIZE_Z * chunkCoordZ);
    vec3 actualPos = float(blockSize) * vec3(ivec3(blockPos) + chunkOffset);

    gl_Position = viewProjMatrix * vec4(actualPos, 1.0);
    texCoords = vec2(float(blockTexCoords.x) / float(blockAtlasWidthInBlocks), float(blockTexCoords.y) / float(blockAtlasHeightInBlocks));
}