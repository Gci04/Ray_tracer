#pragma once 
#include <iostream>
#include <math.h>
#include "color.h"
#include <time.h>
#include <cstdlib>
using namespace std;
#include "vec3D.h"
#include "Camera.h"
#include "Object.h"
#include <vector>
#include "Source.h"

void saveBMP(const char *filename, int width, int height , int dpi, color *data){
	FILE *f;
	int k = width* height;
	int s = 4*k;
	int filesize = 54+s;

	double factor = 39.375;
	int m = int(factor);
	int ppm = dpi * m;
	unsigned char bpmFileHeader[14]= {'B', 'M', 0,0,0,0, 0,0,0,0, 54,0,0,0} ;
	unsigned char bpmInfoHeader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0,24,0};

	bpmFileHeader [2] = (unsigned char)(filesize);
	bpmFileHeader [3] = (unsigned char)(filesize>>8);
	bpmFileHeader [4] = (unsigned char)(filesize>>16);
	bpmFileHeader [5] = (unsigned char)(filesize>>24);

	bpmInfoHeader [4] = (unsigned char)(width);
	bpmInfoHeader [5] = (unsigned char)(width>>8);
	bpmInfoHeader [6] = (unsigned char)(width>>16);
	bpmInfoHeader [7] = (unsigned char)(width>>24);

	bpmInfoHeader [8] = (unsigned char)(height);
	bpmInfoHeader [9] = (unsigned char)(height>>8);
	bpmInfoHeader [10] = (unsigned char)(height>>16);
	bpmInfoHeader [11] = (unsigned char)(height>>24);

	bpmInfoHeader [21] = (unsigned char)(s);
	bpmInfoHeader [22] = (unsigned char)(s>>8);
	bpmInfoHeader [23] = (unsigned char)(s>>16);
	bpmInfoHeader [24] = (unsigned char)(s>>24);

	bpmInfoHeader [25] = (unsigned char)(ppm);
	bpmInfoHeader [26] = (unsigned char)(ppm>>8);
	bpmInfoHeader [27] = (unsigned char)(ppm>>16);
	bpmInfoHeader [28] = (unsigned char)(ppm>>24);

	bpmInfoHeader [29] = (unsigned char)(ppm);
	bpmInfoHeader [30] = (unsigned char)(ppm>>8);
	bpmInfoHeader [31] = (unsigned char)(ppm>>16);
	bpmInfoHeader [32] = (unsigned char)(ppm>>24);

	f = fopen (filename, "wb");
	fwrite(bpmFileHeader, 1,14,f);
	fwrite(bpmInfoHeader, 1,40,f);

	for (int i=0; i<k; i++){
		double red= data[i].getColorRed()*255;
		double green= data[i].getColorGreen()*255;
		double blue= data[i].getColorBlue()*255;

		unsigned char color[3] = {(int)blue, (int)green, (int)red};
		fwrite(color, 1,3,f);
	}
		fclose(f);
}
int find(vector<double> a){
	double max,min;
	int index;
	if (a.size() == 0)
		return -1;
	else{
		max = a[0];
		index = 0;
		for (size_t i=1; i<a.size(); i++){
			if (a[i] > max)
			{
				max = a[i];
				index = i;
			}
		}
		if (max<=0.0001)
			return -1;
		min = max;
		for (size_t i=1; i<a.size(); i++){
			if ((a[i] < min) && (a[i] > 0))
			{
				min = a[i];
				index = i;
			}
		}
		return index;
	}
}

int find2( vector<double> a, int ind){
	double max,min;
	int index;
	if (a.size() == 0)
		return -1;
	else{
		max = a[0];
		index = 0;
		for (size_t i=1; i<a.size(); i++){
			if (a[i] > max && i != ind)
			{
				max = a[i];
				index = i;
			}
		}
		if (max<=0.0001)
			return -1;
		min = max;
		for (size_t i=1; i<a.size(); i++){
			if ((a[i] < min) && (a[i] > 0) &&(i != ind))
			{
				min = a[i];
				index = i;
			}
		}
		return index;
	}
}

color getColor(vec3d intPos, vec3d initRayDir, vector <object*> &Objts, int indx, light_point_source light )
{
	color finalColor;
	finalColor  = Objts[indx]->get_color();
	vec3d coNormal =Objts[indx]->get_normal_at(intPos);
	finalColor = finalColor.mult(0.9);
	if((Objts[indx]->get_color().getSpecial() > 0.0) && (Objts[indx]->get_color().getSpecial()<=1.0)){
		vec3d reflection_dir ;
		reflection_dir = (initRayDir.negative().vecAdd(coNormal.vecMult(initRayDir.negative().dotProduct(coNormal)).vecAdd(initRayDir).vecMult(2.0))).normalized();
		ray reflection(intPos, reflection_dir);

		vector<double> intersections;
			for(size_t i = 0; i<Objts.size(); i++){
				intersections.push_back(Objts[i]->find_intersection_at(reflection));
			}
			int indx2 = find2(intersections,indx);
			if ((indx2 != -1) )
			{
				vec3d intpos = intPos.vecAdd(reflection_dir.vecMult(intersections[indx2]));
				color reflectionColor = getColor(intpos, reflection_dir, Objts, indx2, light);
				finalColor = finalColor.add(reflectionColor.mult(Objts[indx]->get_color().getSpecial()));
			}
	}
	bool shadowed = false;
	vec3d lightDir = (light.get_light_position().vecSubtract(intPos)).normalized();
	double  cos =lightDir.dotProduct(coNormal);
	if (cos > 0){
		double disToLight =((light.get_light_position().vecSubtract(intPos)).magnitude());
		ray shadowRay(intPos, lightDir);
		for (size_t i = 0; i< Objts.size(); i++){
			if (disToLight > Objts[i]->find_intersection_at(shadowRay) && i!=indx){
				shadowed = true;
			}
		}
	}
	if (shadowed == false )
		finalColor = finalColor.add(Objts[indx]->get_color().mult(light.get_light_color()).mult(cos));
	finalColor.norm();
	return finalColor;
}
void makeSpheres(vector <sphere> &Spheres, int total){
	vec3d s(-2,10,0);
	color red(1,0,0,0.9);
	for (int i =0; i<total;i++){
		sphere temp(s,1.5);
		temp.c = red;
		Spheres.push_back(temp);
	}
}