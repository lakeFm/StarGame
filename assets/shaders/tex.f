#version 330 core
in vec3 ourColor;
in vec2 textureCoord;

out vec4 color;
uniform sampler2D ourTexture;

void main() {
    vec4 c = texture(ourTexture, textureCoord);

    if(c.xyz != vec3(0,0,0))
        color = c;
    else
        color = vec4(0,0,0,0);

}