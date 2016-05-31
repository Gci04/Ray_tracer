#include "color.h"
#include "Ray.h"

class object
{
public:
	virtual double find_intersection_at(ray v) = 0;
	virtual  color get_color() = 0;
	virtual  vec3d get_normal_at(vec3d v) = 0;

};
class triangle : public object{
public:
	vec3d a,b,c;
	triangle ();
};
class sphere : public object{
private :
	
	vec3d  center;
	double  radius; 
public:
	color c;
	sphere();
	sphere(vec3d c, double r);
	double get_radius ();
	vec3d get_center();
	vec3d get_normal_at(vec3d v);
	double find_intersection_at(ray v);
	color get_color();

};
class plane : public object
{
public :
	double distance;
	vec3d normal;
	color c;
	plane ()
	{
		distance = 0;
		normal = vec3d(0,0,1);
	}
	vec3d get_normal();
	color get_color()
	{
		return c;
	}
	double get_distance();
	vec3d get_normal_at(vec3d v)
	{
		return normal;
	}
	double find_intersection_at(ray v);
};
