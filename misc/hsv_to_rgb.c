
#include <math.h>

#include <debug.h>

#include "hsv_to_rgb.h"

struct rgb hsv_to_rgb(double hue, double sat, double val)
{
	double c = val * sat;
	double x = c * (1 - fabs(fmod(hue / (M_PI / 3), 2) - 1));
	double m = val - c;
	
	double r, g, b;
	
	     if (hue < 1 * M_PI / 3) r = c, g = x, b = 0;
	else if (hue < 2 * M_PI / 3) r = x, g = c, b = 0;
	else if (hue < 3 * M_PI / 3) r = 0, g = c, b = x;
	else if (hue < 4 * M_PI / 3) r = 0, g = x, b = c;
	else if (hue < 5 * M_PI / 3) r = x, g = 0, b = c;
	else                         r = c, g = 0, b = x;
	
	return (struct rgb) { (r + m) * 255, (g + m) * 255, (b + m) * 255 };
}

