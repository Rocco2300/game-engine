#version 440 core

in vec2 uv;
in vec3 fragNormal;

out vec4 FragColor;

const vec3 sunDirection = vec3(-0.25, -1.0, -0.125);

uniform sampler2D tex;

void main()
{
    vec4 color = texture(tex, uv);
    float diffuse = max(dot(normalize(sunDirection), normalize(fragNormal)), 0.0);
    FragColor = color * diffuse;
}