#include "vec3D.h"

class camera
{
public :
	
	vec3d camUp;
	vec3d camRight;
	vec3d camPosition;
	vec3d camDirection;

	camera ();
	camera (vec3d d,vec3d r,vec3d o,vec3d l);
	vec3d getcamUp();
	vec3d getcamRight();
	vec3d getcamPosition();
	vec3d getcamDirection();
};