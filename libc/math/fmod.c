/*
 * Author: Manuel
 * Email: Manuel_Angel99@outlook.com 
 * Created: 2016-09-08 11:22:03 
 * @Last Modified by: Manuel
 * @Last Modified time: 2016-09-08 11:51:23
 * 
 * Description: This function returns the modulus of a floating point division
 */
#include <math.h>

double fmod(double x, double y)
{
	double i, f;
	
	if (y == 0.0)
		return 0.0;

	i = floor(x/y);
	f = x - i*y;
	if ((x < 0.0) != (y < 0.0))
		f = f-y;

	return f;
}