#version 330 core
layout (location = 0) in vec4 position;

uniform mat4 projection;

out vec2 textureCoord;

void main() {
    gl_Position = projection  * vec4(position.xy,1.0f, 1.0f);
    textureCoord = position.zw;
}