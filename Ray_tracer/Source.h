#include "Color.h"
#include "vec3D.h"

class source
{
public:
	virtual vec3d get_light_position() = 0;
	virtual color get_light_color() = 0;
};

class light_point_source : public source
{
public:
	vec3d position;
	color b;

	vec3d get_light_position();
	color get_light_color();
};