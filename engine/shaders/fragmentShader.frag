#version 430

struct PointLight
{
    vec3 position;
    vec3 color;
    float intensity;
};

uniform PointLight pointLight;
uniform sampler2D texture1;

in vec3 fragPos;
in vec3 fragNormal;
in vec2 TexCoord;

out vec4 FragColor;

void main()
{
    // Normalize the fragment normal
    vec3 norm = normalize(fragNormal);

    // Compute light direction
    vec3 lightDir = normalize(pointLight.position - fragPos);

    // Ambient lighting
    vec3 ambient = 0.1 * pointLight.color;

    // Diffuse lighting
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * pointLight.color * pointLight.intensity;

    // Combine lighting components
    vec3 lighting = ambient + diffuse;

    // Apply texture and lighting
    vec4 texColor = texture(texture1, TexCoord);
    FragColor = vec4(lighting, 1.0) * texColor;
}



//in vec3 fragPos; 
//in vec3 fragNormal; 
//in vec4 color;
//in vec2 TexCoord;
//
//uniform sampler2D texture1;
//uniform vec3 viewPos; 
//
//out vec4 FragColor;
//out vec4 Color;
////void main()
////{
////	FragColor = texture(texture1, TexCoord);
////}
////
//// Point light properties
//struct PointLight {
//    vec3 position;
//    vec3 color;
//    float intensity;
//};
//uniform PointLight pointLight;
//
//// Directional light properties
//struct DirectionalLight {
//    vec3 direction;
//    vec3 color;
//    float intensity;
//};
//uniform DirectionalLight dirLight;
//
//// Lighting calculations
//vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 viewDir) {
//    // Ambient
//    vec3 ambient = 0.1 * light.color;
//
//    // Diffuse
//    vec3 lightDir = normalize(light.position - fragPos);
//    float diff = max(dot(normal, lightDir), 0.0);
//    vec3 diffuse = diff * light.color * light.intensity;
//
//    // Specular
//    vec3 reflectDir = reflect(-lightDir, normal);
//    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
//    vec3 specular = spec * light.color * light.intensity;
//
//    return ambient + diffuse + specular;
//}
//
//vec3 CalculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir) {
//    // Ambient
//    vec3 ambient = 0.1 * light.color;
//
//    // Diffuse
//    vec3 lightDir = normalize(-light.direction);
//    float diff = max(dot(normal, lightDir), 0.0);
//    vec3 diffuse = diff * light.color * light.intensity;
//
//    // Specular
//    vec3 reflectDir = reflect(-lightDir, normal);
//    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
//    vec3 specular = spec * light.color * light.intensity;
//
//    return ambient + diffuse + specular;
//}
//
//void main() {
//    vec3 norm = normalize(fragNormal);
//    vec3 viewDir = normalize(viewPos - fragPos);
//
//    vec3 pointLightEffect = CalculatePointLight(pointLight, norm, viewDir);
//    vec3 dirLightEffect = CalculateDirectionalLight(dirLight, norm, viewDir);
//
//    vec3 lighting = pointLightEffect + dirLightEffect;
//
//    vec4 texColor = texture(texture1, TexCoord);
//    FragColor = vec4(lighting, 1.0) * texColor;
//}





