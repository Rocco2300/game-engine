#version 440 core

in vec2 TexCoords;

out vec4 FragColor;

uniform vec4 color;
uniform sampler2D glyph;
uniform bool isCharacter;

void main() {
    if (isCharacter) {
        vec4 sampled = vec4(1.0, 1.0, 1.0, texture(glyph, TexCoords).r);
        FragColor = color * sampled;
    } else {
        FragColor = color;
    }
}
