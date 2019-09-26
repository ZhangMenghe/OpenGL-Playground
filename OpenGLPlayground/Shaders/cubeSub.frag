#version 330 core
out vec4 FragColor;

in VS_OUT {
	vec3 camposObjSpace;
	vec3 raydir;
	vec3 screenPos;
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    mat4 uMVMat_inv;
} fs_in;

uniform sampler2D uSampler_depth;
uniform vec3 uViewPos, uPlanePoint, uPlaneNormal;
uniform mat4 uProjMat_inv;//inverse camera projection matrix, modelview matrix
uniform vec3 uBaseColor;
uniform bool uIsCut;
float RayPlane(vec3 ray_origin, vec3 ray_dir, vec3 plane_p, vec3 plane_n) {
	float d = dot(plane_n, ray_dir);
	float t = dot(plane_p - ray_origin, plane_n);
	return d > 1e-5 ? (t / d) : (t > 0 ? 1e5 : -1e5);
}

// depth texture to object-space ray depth
float DepthTextureToObjectDepth(vec3 ray_origin, vec3 screenPos) {
	vec4 clip = vec4(screenPos.xy / screenPos.z, 0.0, 1.0);

	clip.z = texture(uSampler_depth, clip.xy * .5 + .5, 0.0).r * 2.0 - 1.0;

    vec4 viewSpacePosition = uProjMat_inv * clip;
    viewSpacePosition /= viewSpacePosition.w;

	return length((fs_in.uMVMat_inv * viewSpacePosition).xyz - ray_origin);
}

void main(){
	if(!uIsCut){
		FragColor = vec4(uBaseColor, 1.0);
		return;
	}
	// shot ray from camera to each vertex
	vec3 ray_origin = fs_in.camposObjSpace;
	vec3 ray_dir = normalize(fs_in.raydir);

	float limit = RayPlane(ray_origin, ray_dir, uPlanePoint, uPlaneNormal);
	limit = min(limit, 1.0);
	vec2 intersect = vec2(.0, limit);

	// depth buffer intersection
	float z = DepthTextureToObjectDepth(ray_origin, fs_in.screenPos);
	intersect.y = min(intersect.y, z);
	if (intersect.y < intersect.x) discard;

	FragColor = vec4(uBaseColor, 1.0);
}