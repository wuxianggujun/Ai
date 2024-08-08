#version 330 core
out vec4 FragColor;

struct DirLight {
    vec3 direction;
    vec3 color;
};

in vec3 Normal;  
in vec3 FragPos;
in vec2 TexCoords;

// uniform vec3 viewPos;
uniform DirLight dirLight;
uniform sampler2D texture_diffuse1;

void main()
{
    vec3 color = vec3(texture(texture_diffuse1, TexCoords));
    vec3 coolColor = vec3(0.0, 0.0, 1.0) + 0.2 * color;
    vec3 warmColor = vec3(1.0, 1.0, 0.0) + 0.6 * color;
     
    float nl = dot(normalize(Normal), normalize(dirLight.direction));
    float it = (1.0 + nl) / 2.0;
    
    vec3 result = it * coolColor + (1 - it) * warmColor;

    FragColor = vec4(result, 1.0);
    // FragColor = texture(texture_diffuse1, TexCoords);
} 