#version 440 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;
layout (location = 2) in vec2 aTexCoords;

uniform mat4 mvp;

out vec2 uv;
out vec3 fragNormal;

void main()
{
    gl_Position = mvp * vec4(aPos, 1.0);

    uv = aTexCoords;
    fragNormal = aNorm;
}