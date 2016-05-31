#include "Camera.h"

camera :: camera(): camUp(vec3d()),camRight (vec3d()),camPosition (vec3d()), camDirection(vec3d())
{}
camera :: camera (vec3d d,vec3d r,vec3d o,vec3d l): camUp(d),camRight (r),camPosition(o),camDirection(l)
{}
vec3d camera:: getcamUp(){
	return camUp;
}
vec3d camera:: getcamRight(){
	return camRight;
}
vec3d camera:: getcamPosition(){
	return camPosition;
}
vec3d camera:: getcamDirection(){
	return camDirection;
}