#pragma once  
class color
{
	double special; 
	double red;
	double green;
	double blue;
public:
	color(): red(0), green(0), blue(0), special(0.7)
	{}
	color(double r, double g, double b, double s) : red(r), green(g), blue(b), special(s) 
	{}
	double getColorRed();
	double getColorGreen();
	double getColorBlue();
	double getSpecial();

	void setSpecial(double s);
	void setColorRed(double r);
	void setColorGreen(double g);
	void setColorBlue(double b);
	color add(color c);
	color mult(double d);
	color mult(color c);
	void norm();
};