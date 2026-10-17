        #version 330 core
        struct Material
        {
            sampler2D diffuse;
            sampler2D specular;
            sampler2D emission;
            float shininess;            
        };
        struct DirLight
        {
            vec3 direction;

            vec3 ambient;
            vec3 diffuse;
            vec3 specular;
        };
        struct PointLight
        {
            vec3 position;

            float constant;
            float linear;
            float quadratic;
            
            vec3 ambient;
            vec3 diffuse;
            vec3 specular;
        };   
        
        struct SpotLight
        {
            vec3 position;
            vec3 direction;

            vec3 ambient;
            vec3 diffuse;
            vec3 specular;

            float innerCutoff;
            float outerCutoff;
            
            float constant;
            float linear;
            float quadratic;
        };

        in vec3 Normal;
        in vec3 FragPos;
        in vec2 TexCoords;

        out vec4 FragColor;       
        
        #define MAX_POINT_LIGHTS 32
        #define MAX_SPOT_LIGHTS 32
        #define MAX_DIRECTIONAL_LIGHTS 4        
        
        uniform Material material;
        uniform vec3 viewPos;

        uniform int pointLightCount;
        uniform int directionalLightCount;
        uniform int spotLightCount;

        uniform PointLight pointLights[MAX_POINT_LIGHTS];
        uniform DirLight directionalLights[MAX_DIRECTIONAL_LIGHTS];
        uniform SpotLight spotLights[MAX_SPOT_LIGHTS];

        vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
        vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
        vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

        void main()
        {     
        
            vec3 norm = normalize(Normal);
            vec3 viewDir = normalize(viewPos - FragPos);

            vec3 result = vec3(0.0);

            for (int i = 0; i < directionalLightCount; i++)
            {
                result += CalcDirLight(
                    directionalLights[i],
                    norm,
                    viewDir);
            }
            for (int i = 0; i < pointLightCount; i++)
            {
                result += CalcPointLight(
                    pointLights[i],
                    norm,
                    FragPos,
                    viewDir);
            }
            for (int i = 0; i < spotLightCount; i++)
            {
                result += CalcSpotLight(
                    spotLights[i],
                    norm,
                    FragPos,
                    viewDir);
            }
            FragColor = vec4(result, 1.0);          
        }
        vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
        {
            vec3 lightDir = normalize(-light.direction);

            float diff = max(dot(normal, lightDir), 0.0);

            vec3 reflectDir = reflect(-lightDir, normal);
            float spec = pow(max(dot(viewDir, reflectDir), 0.0),
                                material.shininess);

            vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));

            vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));

            vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
            
            return (ambient + diffuse + specular);
        }
        vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
        {
            vec3 lightDir = normalize(light.position - fragPos);

            float diff = max(dot(normal, lightDir), 0.0);

            vec3 reflectDir = reflect(-lightDir, normal);
            float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

            float distance = length(light.position - fragPos);
            float attenuation = 1.0 / (light.constant - light.linear * distance +
                                    light.quadratic * (distance * distance));
            vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
            vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
            vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));

            ambient *= attenuation;
            diffuse *= attenuation;
            specular *= attenuation;

            return (ambient + diffuse + specular);
        }
        vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
        {
            vec3 lightDir = normalize(light.position - fragPos);

            float diff = max(dot(normal, lightDir), 0.0);

            vec3 reflectDir = reflect(-lightDir, normal);
            float spec = 0.0;

            if (diff > 0.0)
            {
                spec = pow(
                    max(dot(viewDir, reflectDir), 0.0),
                    material.shininess);
            }

            float distance = length(light.position - fragPos);

            float attenuation = 1.0 / (
                light.constant
                + light.linear * distance
                + light.quadratic * distance * distance);

            float theta = dot(
                lightDir,
                normalize(-light.direction));

            float epsilon = light.innerCutoff - light.outerCutoff;

            float intensity = clamp(
                (theta - light.outerCutoff) / epsilon,
                0.0,
                1.0);

            vec3 albedo = vec3(texture(material.diffuse, TexCoords));
            vec3 specularMap = vec3(texture(material.specular, TexCoords));

            vec3 ambient = light.ambient * albedo;
            vec3 diffuse = light.diffuse * diff * albedo;
            vec3 specular = light.specular * spec * specularMap;

            float lightingFactor = intensity * attenuation;

            ambient *= lightingFactor;
            diffuse *= lightingFactor;
            specular *= lightingFactor;

            return ambient + diffuse + specular;
        }
    