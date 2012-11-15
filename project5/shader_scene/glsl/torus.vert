
attribute vec2 parametric;

uniform vec3 lightPosition;  // Object-space
uniform vec3 eyePosition;    // Object-space
uniform vec2 torusInfo;

varying vec2 normalMapTexCoord;

varying vec3 lightDirection;
varying vec3 halfAngle;
varying vec3 eyeDirection;
varying vec3 c0, c1, c2;

void main()
{
  const float pi2 = 6.28318530;  // 2 times Pi
  float ro =torusInfo[0]; //r outer 
  float ri = torusInfo[1]; // r inner
  float u = parametric[0];
  float v = parametric[1];
  normalMapTexCoord = vec2(6.0*(1.0-u), 2.0*v);

  u = u*pi2;
  v = v *pi2;
  float x = (ro + ri*cos(v))*cos(u);
  float y = (ro + ri*cos(v))*sin(u);
  float z = ri*sin(v);

  float sin_u = sin(u);
  float cos_u = cos(u);
  float dxdu = sin(u)*(-(ro+ri*cos(v)));
  float dydu = cos(u)*(ro+ri*cos(v));
  float dzdu = 0.0;

  float dxdv = -ri*cos(u)*sin(v);
  float dydv = -ri*sin(u)*sin(v);
  float dzdv = ri*cos(v); // extra pi2 makes cool mistake

  vec3 T = vec3(dxdu, dydu, dzdu);
  vec3 T_ = vec3(dxdv, dydv, dzdv);
  vec3 N = cross(T, T_);
  vec3 B = cross(T, N);
  mat3 M = mat3(T, B, N);
  gl_Position = gl_ModelViewProjectionMatrix * vec4(x, y, z, 1);
  lightDirection = (lightPosition - vec3(x,y,z)) * M;  // XXX fix me

  eyeDirection = vec3(0);  // XXX fix me
  
  // halfAngle = vec3(0);  // XXX fix me
  c0 = vec3(0);  // XXX fix me
  c1 = vec3(0);  // XXX fix me
  c2 = vec3(0);  // XXX fix me
}

