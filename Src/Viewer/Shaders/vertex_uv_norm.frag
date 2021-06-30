#version 330 core

in FRAG_OUT {
    vec3 normal;
    vec3 position;
    vec2 uv;
} fragOut;

struct DirectionalLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform DirectionalLight directionalLight;
uniform vec3 viewPos;
uniform bool isLight;
out vec4 fragColor;

void main() {
    vec4 texColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
    if (isLight) {
        vec3 ambient = directionalLight.ambient * texColor.rgb;

        vec3 norm = normalize(fragOut.normal);
        vec3 lightDir = normalize(-directionalLight.direction);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = directionalLight.diffuse * diff;

        vec3 viewDir = normalize(viewPos - fragOut.position);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64);
        vec3 specular = spec * directionalLight.specular;

        vec3 result = ambient + diffuse + specular;
        fragColor = vec4(result, texColor.a);
    }
    else {
        fragColor = texColor;
    }
}