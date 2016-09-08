/*
 * Author: Manuel
 * Email: Manuel_Angel99@outlook.com 
 * Created: 2016-09-08 11:27:40 
 * @Last Modified by: Manuel
 * @Last Modified time: 2016-09-08 11:36:17
 * 
 * Description: Implements the roundld function that rounds a long double to a certain number of decimal places
 */
#include <math.h>

long double roundld(long double num)
{
	return (num - floorld(num) > 0.5) ? ceilld(num) : floorld(num);
}