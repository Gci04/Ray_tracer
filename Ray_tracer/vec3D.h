#pragma once 
#include <math.h>
class vec3d
{
private :
	double x,y,z;

public :
	vec3d();
	vec3d(double x,double y,double z);
	vec3d vecAdd (vec3d v);
	vec3d vecMult(double v);
	vec3d vecSubtract(vec3d v);
	double dotProduct(vec3d v);
	double magnitude();
	vec3d normalized();
	vec3d negative();
	vec3d crossProduct(vec3d v);
};
