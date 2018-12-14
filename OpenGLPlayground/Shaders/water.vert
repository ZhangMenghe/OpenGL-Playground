#version 330 core

attribute vec3 aPosition;
attribute vec2 aTexCoord;

/* Multiple bump coordinates for animated bump mapping */
out vec2 bumpCoord0, bumpCoord1, bumpCoord2;
out vec3 vBinormal, vTangent, vNormal, vView;

uniform mat4 uProjMat, uViewMat;
uniform vec3 uEye;
uniform float uTime;

const float A[2]={1.0,0.5};//amplitude
const float Dx[2] = { -1.0 , -0.7 };//(DX,DZ)direction of travel
const float Dz[2] = {0.0 , 0.7};
const float f[2] = {0.2,0.4} ;//frequency
const float p[2] = {0.5,1.3};//phase
const float k[2] = {2.0,2.0};//sharpness

const vec2 texScale = vec2(8, 4);
const vec2 bumpSpeed = vec2(-0.05, 0);

void main(){
	vec4 P = vec4(aPosition, 1.0);
    //waves:y=G(x,z,t)

    float wave1 = A[0] * pow((sin((Dx[0] * P.x + Dz[0] * P.z)*f[0] + uTime *p[0])*0.5 + 0.5),k[0]);
    float dGx1  = 0.5 * k[0] * f[0] * A[0] * pow((sin((Dx[0] * P.x + Dz[0] * P.z)*f[0] + uTime *p[0])*0.5+0.5),k[0]-1) * cos((Dx[0] * P.x + Dz[0] * P.z)*f[0] + uTime *p[0])*Dx[0];
    float dGz1  = 0.5 * k[0] * f[0] * A[0] * pow((sin((Dx[0] * P.x + Dz[0] * P.z)*f[0] + uTime *p[0])*0.5+0.5),k[0]-1) * cos((Dx[0] * P.x + Dz[0] * P.z)*f[0] + uTime *p[0])*Dz[0];

	float wave2 = A[1] * pow((sin((Dx[1] * P.x + Dz[1] * P.z)*f[1] + uTime *p[1])*0.5 + 0.5),k[1]);
    float dGx2  = 0.5 * k[1] * f[1] * A[1] * pow((sin((Dx[1] * P.x + Dz[1] * P.z)*f[1] + uTime *p[1])*0.5+0.5),k[1]-1) * cos((Dx[1] * P.x + Dz[1] * P.z)*f[1] + uTime *p[1])*Dx[1];
    float dGz2  = 0.5 * k[1] * f[1] * A[1] * pow((sin((Dx[1] * P.x + Dz[1] * P.z)*f[1] + uTime *p[1])*0.5+0.5),k[1]-1) * cos((Dx[1] * P.x + Dz[1] * P.z)*f[1] + uTime *p[1])*Dz[1];

    //sum of waves
    P.y = wave1 + wave2;
    float dHx = dGx1 + dGx2;
    float dHz = dGz1 + dGz2;

    vBinormal = vec3(1, dHx, 0);
    vTangent = vec3(0, dHz, 1);
    vNormal = vec3(-dHx, 1, -dHz);
    vView = uEye - aPosition; //normalize in frag

	/* Compute bumpmap coordinates */
	float bumpTime = mod(uTime,100.0);
	
	bumpCoord0.xy = aTexCoord.xy * texScale + bumpTime * bumpSpeed;
	bumpCoord1.xy = aTexCoord.xy * texScale *2 + bumpTime * bumpSpeed*4;
	bumpCoord2.xy = aTexCoord.xy * texScale *4 + bumpTime * bumpSpeed*8;

	gl_Position = uProjMat *uViewMat* vec4(aPosition, 1.0); //P;
}
