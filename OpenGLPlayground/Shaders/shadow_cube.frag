#version 330 core
out vec4 FragColor;
in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec4 FragPosLightSpace;
} fs_in;

uniform vec3 uBaseColor;
uniform sampler2D uSampler_tex, uSampler_depth;
uniform vec3 uLightPos, uViewPos;

const vec3 lightColor = vec3(0.3);
const float ambient_intensity = 0.3;
const float ambientStrength = 0.1;
const float specularStrength = 0.5;
const float specularAlpha = 32;

float ShadowCalculation(vec4 fragPosLightSpace){
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(uSampler_depth, projCoords.xy).r; 
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    // calculate bias (based on depth map resolution and slope)
    vec3 normal = normalize(fs_in.Normal);
    vec3 lightDir = normalize(uLightPos - fs_in.FragPos);
    float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);
    // check whether current frag pos is in shadow
    // float shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0;
    // PCF
    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(uSampler_depth, 0);
    for(int x = -1; x <= 1; ++x)
    {
        for(int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture(uSampler_depth, projCoords.xy + vec2(x, y) * texelSize).r; 
            shadow += currentDepth - bias > pcfDepth  ? 1.0 : 0.0;        
        }    
    }
    shadow /= 9.0;
    
    // keep the shadow at 0.0 when outside the far_plane region of the light's frustum.
    if(projCoords.z > 1.0)
        shadow = 0.0;
        
    return shadow;
}

void main(){
	vec3 diffuse_color = uBaseColor;//texture(uSampler_tex, fs_in.TexCoords).rgb;
	vec3 N = normalize(fs_in.Normal);
	//ambient
	vec3 ambient = ambient_intensity * diffuse_color;
	//diffuse
	vec3 lightDir = normalize(uLightPos - fs_in.FragPos);
	vec3 diffuse = max(dot(lightDir, N), 0.0) * lightColor;
	//specular
	vec3 viewDir = normalize(uViewPos - fs_in.FragPos);
	vec3 reflectDir = reflect(-lightDir, N);
	vec3 specular = vec3(0.0);//specularStrength * pow(max(dot(viewDir, reflectDir), 0.0), specularAlpha) * diffuse_color;

 	// calculate shadow
    float shadow = ShadowCalculation(fs_in.FragPosLightSpace);                      
    vec3 shadow_color = (ambient + (1.0 - shadow) * (diffuse + specular)) * diffuse_color;    
    FragColor = vec4(shadow_color, 1.0);
	//FragColor = vec4(uBaseColor, 1.0);
}
