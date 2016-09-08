/*
 * Author: Manuel
 * Email: Manuel_Angel99@outlook.com 
 * Created: 2016-09-08 11:32:02 
 * @Last Modified by: Manuel
 * @Last Modified time: 2016-09-08 11:34:00
 * 
 * Description: Lonh double version of the ceil function
 */

#include <math.h>

long double ceilld(long double value)
{
	int temporal = (int)value;
	return value < temporal ? temporal : temporal + 1;

}