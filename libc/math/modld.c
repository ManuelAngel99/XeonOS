/*
 * Author: Manuel
 * Email: Manuel_Angel99@outlook.com 
 * Created: 2016-09-08 11:10:42 
 * @Last Modified by: Manuel
 * @Last Modified time: 2016-09-08 11:52:37
 * 
 * Description: The modld function is the long double version of modf
 */

#include <math.h>

long double modld(long double value, long double* intpart)
{
	long double decimal_part = 0.0;
	if( value >= 0)
	{
		decimal_part = value - (long double)floorld(value);
		*intpart = value - decimal_part;
	}
	else 
	{
		decimal_part = -(value - (long double)ceilld(value));
		*intpart = value + decimal_part;
	}
	return decimal_part;
}