#version 440 core

in vec2 uv;
in mat3 TBN;
in vec3 fragNormal;
in vec3 fragPosition;

out vec4 FragColor;

uniform vec3 viewPosition;

uniform int lightType;
uniform vec3 lightPosition;
uniform vec3 lightDirection;

uniform float specularStrength;

uniform bool hasNormalTexture;
uniform sampler2D normalTexture;
uniform sampler2D diffuseTexture;
uniform sampler2D specularTexture;

vec4 getDiffuseColor() {
    return texture(diffuseTexture, uv);
}

vec4 getSpecularColor() {
    return texture(specularTexture, uv);
}

vec3 getNormal() {
    if (!hasNormalTexture) {
        return normalize(fragNormal);
    }

    vec3 normal = texture(normalTexture, uv).rgb;
    normal = normal * 2.0 - 1.0;
    normal = normalize(TBN * normal);
    return normal;
}

void main()
{
    const float ambientStrength = 0.1;
    vec4 ambient = ambientStrength * vec4(1.0);

    vec4 color = getDiffuseColor();

    vec3 norm = getNormal();
    vec3 lightDir = normalize(-lightDirection);
    float diff = max(dot(norm, lightDir), 0.0);

    const vec4 lightColor = vec4(1, 1, 0.9, 1.0);
    vec4 diffuse = diff * lightColor;

    vec3 viewDir = normalize(viewPosition - fragPosition);
    vec3 reflectDir = reflect(-lightDir, norm);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec4 specular = 0.5 * spec * lightColor;

    vec4 finalColor = (ambient + diffuse + specular) * color;

    FragColor = finalColor;
}