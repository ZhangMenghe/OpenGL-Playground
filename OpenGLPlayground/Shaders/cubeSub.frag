#version 330 core
out vec4 FragColor;

in VS_OUT {
	vec3 raydir;
	vec3 screenPos;
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
} fs_in;

// uniform sampler2D uSampler_depth;
uniform vec3 uCamposObjSpace;

//cutting-plane
struct Plane{
	vec3 p;
	vec3 normal;
	bool upwards;
};
struct Sphere{
	vec3 center;
	float radius;
	bool outside;
};
uniform Plane uPlane;
uniform Sphere uSphere;
// uniform mat4 uProjMat_inv, uMVMat_inv;//inverse camera projection matrix, modelview matrix
uniform vec3 uBaseColor;
uniform bool uIsCut;

vec2 RaySphere(vec3 ro, vec3 rd, vec3 center, float radius){
    vec3 oc = ro - center;
    float a = dot(rd, rd);
    float b = 2.0 * dot(oc, rd);
    float c = dot(oc,oc) - radius*radius;
    float discriminant = b*b - 4*a*c;
    return discriminant < 1e-5? vec2(1e5, -1e5): vec2(-b - sqrt(discriminant) , -b + sqrt(discriminant)) / (2.0*a);
}

vec2 RayCube(vec3 ro, vec3 rd, vec3 extents) {
    vec3 tMin = (-extents - ro) / rd;
    vec3 tMax = (extents - ro) / rd;
    vec3 t1 = min(tMin, tMax);
    vec3 t2 = max(tMin, tMax);
    return vec2(max(max(t1.x, t1.y), t1.z), min(min(t2.x, t2.y), t2.z));
}
float RayPlane(vec3 ro, vec3 rd, vec3 planep, vec3 planen) {
	float d = dot(planen, rd);
	float t = dot(planep - ro, planen);
	return d > 1e-5 ? (t / d) : (t > 0 ? 1e5 : -1e5);
}

// depth texture to object-space ray depth
// float DepthTextureToObjectDepth(vec3 ray_origin, vec3 screenPos) {
// 	vec4 clip = vec4(screenPos.xy / screenPos.z, 0.0, 1.0);
// 	clip.z = textureLod(uSampler_depth, clip.xy * .5 + .5, 0.0).r * 2.0 - 1.0;

//     vec4 viewSpacePosition = uProjMat_inv * clip;
//     viewSpacePosition /= viewSpacePosition.w;

// 	return length((uMVMat_inv * viewSpacePosition).xyz - ray_origin);
// }

void main(){
	if(!uIsCut){
		FragColor = vec4(uBaseColor, 1.0);
		return;
	}
	// shot ray from camera to each vertex
	vec3 ray_origin = uCamposObjSpace;
	vec3 ray_dir = normalize(fs_in.raydir);


	vec2 intersect = RayCube(ray_origin, ray_dir, vec3(1.0));
	intersect.x = max(.0, intersect.x);
	
	//Ray-plane

	if(uPlane.upwards)//要上面
		intersect.x = max(intersect.x, RayPlane(ray_origin, ray_dir, uPlane.p, uPlane.normal));
	else//要下面
		intersect.y = min(RayPlane(ray_origin, ray_dir, uPlane.p, uPlane.normal), intersect.y);

	//Ray-Sphere
	vec2 sphere_limit = RaySphere(ray_origin, ray_dir, uSphere.center, uSphere.radius);//vec3(-0.5,.0,.0), 1.0);
	if(uSphere.outside){//要豁口
		if(sphere_limit.x < sphere_limit.y)
			intersect = vec2(sphere_limit.y, sphere_limit.x);
	}else//要球 
		intersect.y = min(intersect.y, sphere_limit.y);


	// depth buffer intersection
	// float z = DepthTextureToObjectDepth(ray_origin, fs_in.screenPos);
	// z = max(z, 1.0);
	// intersect.y = min(intersect.y, z);
	if (intersect.y < intersect.x) 
		// FragColor = vec4(1.0,.0,.0, 1.0); 
		discard;
	else
		FragColor = vec4(uBaseColor, 1.0);
}