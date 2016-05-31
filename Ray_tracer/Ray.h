#include "vec3D.h"

class ray{
private :
	vec3d Origin;
	vec3d direction;

public:
	ray() : Origin(vec3d()), direction(vec3d(0,0,1))
	{}
	ray(vec3d O, vec3d D):Origin(vec3d(O)), direction(vec3d(D))
	{}
	void setOrigin(vec3d a){
		Origin = a;
	}
	void setDirection(vec3d b){
		direction = b;
	}
	vec3d getOrigin(){
		return Origin;
	}
	vec3d getDirection(){
		return direction;
	}
};


