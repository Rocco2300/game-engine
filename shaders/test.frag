#version 440 core

in vec2 uv;
in vec3 fragNormal;

out vec4 FragColor;

const vec3 sunDirection = vec3(-0.25, -1.0, -0.125);

uniform vec3 ambient;
uniform vec3 diffuse;
uniform vec3 specular;

uniform float specularStrength;

uniform bool hasNormalTexture;
uniform bool hasDiffuseTexture;
uniform bool hasSpecularTexture;

uniform sampler2D normalTexture;
uniform sampler2D diffuseTexture;
uniform sampler2D specularTexture;

void main()
{
    vec4 color = texture(diffuseTexture, uv);
    //vec4 color = vec4(diffuse, 1);
    float diffuse = max(dot(normalize(sunDirection), normalize(fragNormal)), 0.0);
    FragColor = color * diffuse;
}