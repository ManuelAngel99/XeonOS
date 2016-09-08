/*
 * Author: Manuel
 * Email: Manuel_Angel99@outlook.com 
 * Created: 2016-09-08 11:31:24 
 * @Last Modified by: Manuel
 * @Last Modified time: 2016-09-08 11:31:51
 * 
 * Description: Long double version of floor
 */

#include <math.h>

long double floorld(long double value)
{
	int temporal = (int)value;
	return value < temporal ? temporal -1 : temporal;
}

