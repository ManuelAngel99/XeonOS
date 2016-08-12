/*
* Author: Manuel Ángel Suárez Álvarez
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-11 16:31:06
* 
* File: memcmp.c
* Description: Implementation of the standard c memcmp function
*/

int memcmp(const void* first_chunk, const void* second_chunk, size_t size)
{
	const unsigned char* first_ptr =  (const unsigned char*) first_ptr;
	const unsigned char* second_ptr = (const unsigned char*) second_ptr;

	for(size_t i = 0; i < size; i++)
	{
		if(first_ptr[i] != second_ptr[i])
		{
			return first_ptr[i] < second_ptr[i] ? -1 : 1;
		}
	}
	
	return 0;
}