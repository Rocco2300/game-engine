#version 440 core

in vec2 uv;
in vec3 fragNormal;

out vec4 FragColor;

uniform int lightType;
uniform vec3 lightPosition;
uniform vec3 lightDirection;

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
    vec3 directionToLight = lightDirection;
    directionToLight.x *= -1;
    directionToLight.y *= -1;

    float diffuse = max(dot(normalize(fragNormal), normalize(directionToLight)), 0.0);
    FragColor = color * diffuse;
}