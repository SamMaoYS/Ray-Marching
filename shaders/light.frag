#version 330 core
out vec4 FragColor;

struct Light {
    vec3 pos;
    vec3 color;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform vec3 viewPos;
uniform Light light;

void main()
{
    FragColor = vec4(light.color, 1.0);
}