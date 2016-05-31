#include "Object.h"
#include <math.h>

double fmin(double a, double b)
{
	return (a < b) ? a : b;
}
//----------------------Plane class-----------------------//
vec3d plane :: get_normal(){
	return normal;
}
double plane ::get_distance(){
	return distance;
}
double plane :: find_intersection_at(ray v){
	double t = 0.0;
	if (normal.dotProduct(v.getDirection()) == 0)
		return -1.0;
	else 
		return 	t = -(normal.dotProduct(v.getOrigin()) + distance) / (normal.dotProduct(v.getDirection()));
}

//------------------------Sphere class ---------------------------//
sphere :: sphere(vec3d c, double r) :center(c),  radius(r)
{}
double sphere :: get_radius(){
	return radius;
}

vec3d sphere ::get_center(){
	return center;
}
vec3d sphere :: get_normal_at(vec3d v){
	vec3d temp; 
	temp = (v.vecAdd(center.negative())).normalized();
	return temp;
}
color sphere ::get_color()
{
	return c;
}
double sphere :: find_intersection_at(ray ray_arg){
	double a = 1.0;
	double b = 2 * (ray_arg.getOrigin().vecAdd(center.negative())).dotProduct(ray_arg.getDirection());
	vec3d PminO = ray_arg.getOrigin().vecAdd(center.negative());
		double c = PminO.dotProduct(PminO) - (radius * radius);

		double insideSqrt = b * b - 4 * c;

		if (insideSqrt < 0) {			
			return -1;				
		}								
		else if (insideSqrt > 0) {							
			double T1 = -(b + sqrt(insideSqrt)) / 2;
			double T2 = -(b - sqrt(insideSqrt)) / 2;

			if (T1 < 0) {
				if (T2 < 0)
					return -1;
				else if (T2 >= 0)
					return T2;
			}
			else if (T1 >= 0) {
				if (T2 < 0)
					return T1;
				else if (T2 >= 0)
					return fmin(T1, T2);
			}
		}
		else {
			double T = - b / 2;
			return T;
		}
}