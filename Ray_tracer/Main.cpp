#include "Tracer_Objects.h"
#include <omp.h>

int main (int argc, char *argv[]){
	omp_set_num_threads(4);
	int width = 4000; int height = 4000;
	int dpi = 72;
	double a,b,c;
	color green(0,1,0,0.0);
	color red(1,0,0,0);
	color blue(0.8,0.8,0.8,1.0);
	color black(0,0,0,0);
	color black2(0,0,0,0.0);
	srand(time(NULL));
	vec3d x(1,0,0), y(0,1,0), z(0,0,1), O(0,0,0);
	vec3d campos = O, Camdir = y, camright = x, camUp = z;
	camera scene(camUp, camright, campos, Camdir);
	light_point_source l;
	l.b = color(1,1,1,0);
	l.position = vec3d(-10,-10,100);
	

	color * picture = new color [width* height ];

	plane sceneplane;
	sceneplane.normal = x;
	sceneplane.distance = 100;
	sceneplane.c = green;

	vec3d s(3,10,0);
	
	vec3d s2(4,15,-2);
	//vec3d s(-1,4,0);
	//vec3d s2(3,2,-2);
	sphere sceneSphere2(s2,1.5);
	sphere sceneSphere(s,0.5);
	sphere sceneSphere_3(vec3d(0,10,2),1);

	sceneSphere_3.c = red;
	sceneSphere.c = red;
	sceneSphere2.c = blue;
	vector <object*> Objts;
	
	Objts.push_back(dynamic_cast<object*>(&sceneplane));
	Objts.push_back(dynamic_cast<object*>(&sceneSphere));
	Objts.push_back(dynamic_cast<object*>(&sceneSphere_3));
	Objts.push_back(dynamic_cast<object*>(&sceneSphere2));
	double start = omp_get_wtime();
#pragma omp parallel for schedule(dynamic)
	for (int x=0; x <width; x++){
		for (int y=0; y<height ; y++){
			int thisOne = x*width+y;
			double xr = float(x)/width, yr = float(y)/width;
			vec3d ray_origin   = scene.getcamPosition();
			vec3d ray_direction; 
			ray_direction = scene.getcamDirection().vecAdd(scene.getcamRight().vecMult(xr -0.5).vecAdd(scene.getcamUp().vecMult(yr-0.5))).normalized();
			ray r(ray_origin, ray_direction);
			vector<double> intersections;
			for(size_t i = 0; i<Objts.size(); i++){
				intersections.push_back(Objts[i]->find_intersection_at(r));
			}
			int indx = find(intersections);
			if (indx == -1 || intersections[indx]<0.01)
			{
				picture[thisOne].setColorRed(0);
				picture[thisOne].setColorBlue(0);
				picture[thisOne].setColorGreen(0);
			}
			else
			{
				vec3d intpos = scene.getcamPosition().vecAdd(ray_direction.vecMult(intersections[indx]));
				color finalColor = getColor(intpos, ray_direction, Objts, indx, l);
				picture[thisOne].setColorRed( finalColor.getColorRed());
				picture[thisOne].setColorBlue( finalColor.getColorBlue());
				picture[thisOne].setColorGreen( finalColor.getColorGreen());
			}
		}
	}
	double end = omp_get_wtime();
	cout <<"Time = "<< end - start<<endl;
	saveBMP("test.bmp", width, height, dpi, picture);
	return 0;
}