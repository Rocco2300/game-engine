#version 440 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;
layout (location = 2) in vec3 aTangent;
layout (location = 3) in vec3 aBitangent;
layout (location = 4) in vec2 aTexCoords;

uniform mat4 view;
uniform mat4 model;
uniform mat4 projection;

out vec2 uv;
out mat3 TBN;
out vec3 fragNormal;
out vec3 fragPosition;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);

    uv = aTexCoords;

    mat3 normalMatrix = transpose(inverse(mat3(model)));
    vec3 T = normalize(vec3(model * vec4(aTangent, 1.0)));
    vec3 B = normalize(vec3(model * vec4(aBitangent, 1.0)));
    vec3 N = normalize(vec3(model * vec4(aNorm, 1.0)));
    TBN = mat3(T, B, N);

    fragNormal = normalMatrix * aNorm;
    fragPosition = aPos;
}