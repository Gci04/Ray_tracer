#include "color.h"

double color ::getColorRed(){
	return red;
}
double color ::getColorGreen(){
	return green;
}
double color ::getColorBlue(){
	return blue;
}
double color ::getSpecial(){
	return special;
}
void color ::setSpecial(double s){
	special = s;
}
void color ::setColorRed(double r){
	red = r;
}
void color ::setColorBlue(double b){
	blue = b;
}
void color ::setColorGreen(double g){
	green = g;
}
color color::add(color c){
	color result;
	result.blue = blue + c.blue;
	result.green = green + c.green;
	result.red = red + c.red;
	result.special = special;
	return result;
}

color color::mult(double d){
	color result;
	result.blue = d*blue;
	result.green = d* green;
	result.red = d*red;
	result.special = special;
	return result;
}
color color::mult(color d){
	color result;
	result.blue = d.blue*blue;
	result.green = d.green* green;
	result.red = d.red*red;
	result.special = special;
	return result;
}
void color::norm(){
	double sum = red+green+blue;
	double diff = sum-3;
	if (diff > 0)
	{
		red = red+diff*(red/sum);
		green = green+diff*(green/sum);
		blue = blue+diff*(blue/sum);
	}
	if (red>1) {red = 1;}
	if (green>1) {green = 1;}
	if (blue>1) {blue = 1;}

	if (red<0) {red = 0;}
	if (green<0) {green = 0;}
	if (blue<0) {blue = 0;}
}