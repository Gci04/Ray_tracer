#include "vec3D.h"

vec3d ::vec3d(): x(0), y(0),z(0)
{}
vec3d ::vec3d(double x,double y,double z): x(x), y(y),z(z)
{}
vec3d vec3d :: vecAdd (vec3d v){
	vec3d temp;
	temp.x = v.x + x;
	temp.y = v.y + y;
	temp.z = v.z + z;
	return temp;
}
vec3d vec3d :: vecMult(double v){
	vec3d temp;
	temp.x = v * x;
	temp.y = v * y;
	temp.z = v * z;
	return temp;
}

vec3d vec3d ::  vecSubtract(vec3d v){
	vec3d temp; 
	temp.x = x - v.x ;
	temp.y = y - v.y ;
	temp.z = z - v.z;
	return temp;
}

double vec3d ::dotProduct(vec3d v){
	double temp;
	temp = (v.x*x) + (v.y*y) + (v.z*z);
	return temp;
}

double vec3d :: magnitude(){
	double temp;
	temp = (x*x)+(y*y)+(z*z);
	return sqrt(temp);
}
vec3d vec3d ::normalized(){
	vec3d temp ;
	temp.x = x/magnitude();
	temp.y = y/magnitude();
	temp.z = z/magnitude();
	return temp;
}
vec3d vec3d :: negative(){
	vec3d temp;
	temp.x = -x;
	temp.y = -y;
	temp.z = -z;
	return temp;
}
vec3d vec3d  :: crossProduct(vec3d v){
	vec3d temp;
	temp.x = (y*v.z) - (z*v.y);
	temp.y = (z*v.y) - (x*v.z);
	temp.z = (x*v.y) - (y*v.x);
	return temp;
}
