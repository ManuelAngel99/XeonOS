/*
 * Author: Manuel
 * Email: Manuel_Angel99@outlook.com 
 * Created: 2016-09-08 13:29:47 
 * @Last Modified by: Manuel
 * @Last Modified time: 2016-09-08 13:46:20
 * 
 * Description: Implementation of the fwrite finction that puts data on a stream
 */

#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <syscall.h>

/*
* Buffer, the data to write
* size, the number of bytes in each record
* number, the number of record to write
* stram, the output stream
*/
size_t fwrite(const void* buffer, size_t size, size_t number, FILE * stream)
{
    size_t left, written, return_value;

    if(!size || !number )
        return 0;
    
    left = size*number;
    written = 0;

    while(left > 0 && !stream->error)
    {
        return_value = write(stream->file_descriptor, buffer + written, left);

        if( return_value <= 0)
            stream->error = 1;
        else
        {
            left -= return_value;
            written += return_value;
        }

    }

    return (written / size);
}