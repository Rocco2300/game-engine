#version 440 core

in vec2 uv;
in vec3 fragNormal;
in vec3 fragPosition;

out vec4 FragColor;

uniform vec3 viewPosition;

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

vec4 getAmbientColor() {
    return vec4(ambient, 1.0);
}

vec4 getDiffuseColor() {
    if (hasDiffuseTexture) {
        return texture(diffuseTexture, uv);
    }

    return vec4(diffuse, 1.0);
}

vec4 getSpecularColor() {
    if (hasSpecularTexture) {
        return texture(specularTexture, uv);
    }

    return vec4(specular, 1.0);
}

void main()
{
    const float ambientStrength = 0.1;
    vec4 ambient = ambientStrength * getAmbientColor();

    vec4 color = getDiffuseColor();

    vec3 norm = fragNormal;
    vec3 lightDir = normalize(-lightDirection);
    float diff = max(dot(norm, lightDir), 0.0);

    const vec4 lightColor = vec4(1, 1, 0.1, 1.0);
    vec4 diffuse = diff * lightColor;

    vec3 viewDir = normalize(viewPosition - fragPosition);
    vec3 reflectDir = reflect(-lightDir, norm);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec4 specular = 0.5 * spec * lightColor;

    vec4 finalColor = (ambient + diffuse + specular) * color;

    FragColor = finalColor;
}