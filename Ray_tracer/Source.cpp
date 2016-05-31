#include "Source.h"

vec3d light_point_source :: get_light_position(){
	return position;
}
color light_point_source :: get_light_color(){
	return b;
}