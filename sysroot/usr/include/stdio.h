/*
* Author: Manuel Ángel Suárez Álvarez
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-11 14:00:08
* 
* File: stdio.h
* Description: Defines the basic input and output functions
*/
#ifndef STDIO_H
#define STDIO_H


#include <sys/cdefs.h>
#include <stddef.h>
#include <stdarg.h>


#ifdef _cplusplus
	extern "C" {
#endif

#define PRINT_FLOAT_PRECISION 5

#define BUFSIZ (256) 	//Size of the buffer
#define EOF (-1)		//End of file mark
#define OPEN_MAX (32) 	//Max number of files to open at once

enum FileFlags {_F_READ = 0x0001, _F_WRIT = 0x0002, _F_RDWR = 0x0003, _F_ERR = 0x0010, _F_EOF = 0x0020, _F_BIN = 0x0040};

typedef struct FILE 
{
	int file_descriptor;				// File handle pointer
	char is_valid;					// Stores if the file is valif or not
	short flags;					// Flags for the file (masks defined below)
	void* base;						// Pointer to the start of the file
	char* file_position;			// Current postion in the file
	short unget;					// 1 bit buffer for ungetc (the bit 15 is set if not empty)
	char error;
	unsigned long alloc;			// Number of allocated bytes in the file
	unsigned short buffer_increment;// Number of bytes to be allocated at once from this file
}FILE;

//The file array for the keyboard-screen input output streams
extern FILE __input_output_buffers[];


#define stdin  &__input_output_buffers[0]
#define stdout &__input_output_buffers[1]
#define stderr &__input_output_buffers[2]

//Filestream open-close
FILE* fopen(const char*, const char*);
int fclose(FILE*);


//Get from file streams
int   getchar(void);
int   ungetc(int, FILE*);

int scanf(const char*  __restrict, ...);
int vfscanf(FILE *, const char*  __restrict, va_list);

int sscanf(const char*, const char*, ...);
int vsscanf(const char*, const char*, va_list);


int    fgetc(FILE* file);
char*  fgets(char*, size_t, FILE*);
size_t fread(void*, size_t, size_t, FILE*);
int    fscanf(FILE*, const char*, ...);


//Send to file streams
int	 fprintf(FILE *, const char*  __restrict, ...);
int	 fputc(int , FILE *);
int	 fputs(const char *, FILE *);
size_t fwrite(const void *, size_t, size_t, FILE *);

int	printf	(const char * __restrict , ...);
int	putc	(int, FILE *);
int	putchar	(int);
int	puts	(const char *);

int	 sprintf(char *, const char *, ...);
int	 snprintf(char *, size_t, const char *, ...);
int	 vfprintf (FILE *, const char *  __restrict, va_list);
int	 vprintf	(const char *, va_list);
int	 vsprintf (char *, const char *, va_list);
void perror (const char *);



int getchar(void);
int getc(void);
int getline(char*, size_t*);
int getch(void);
char kbhit(void);

//File utilites
void clearerr(FILE*);
int	feof	(FILE *);
int	ferror	(FILE *);
int	fileno	(FILE *);
int	fflush	(FILE *);
int	fseek	(FILE *, long int, int);


//NOT IMPLEMENTED!
char key_is_pressed(unsigned char key_code);

#ifdef _cplusplus
}
#endif

#endif