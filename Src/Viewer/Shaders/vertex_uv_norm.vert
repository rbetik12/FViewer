#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec3 normal;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out FRAG_OUT {
    vec3 normal;
    vec3 position;
    vec2 uv;
} fragOut;

void main() {
    fragOut.normal = normal;
    fragOut.uv = uv;
    fragOut.position = vec3(model * vec4(position.xyz, 1.0f));
    gl_Position = projection * view * model * vec4(position.xyz, 1.0f);
}
