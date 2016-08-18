/*
* Author: manuel
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-17 10:56:36
* 
* File: cpuid.c
* Description: The set of functions necesaty to get the advanced programable interrupt controller working
*/


#include <cpuid.h>
#include <arch/x86/system.h>
#include <stdio.h>

uint32_t detect_cpu_family(void)
{
	unsigned int unused_register = 0, ebx = 0;

	if(__get_cpuid(0, &unused_register, &ebx, &unused_register, &unused_register) != 0)
	{
		printf("CPU VENDOR:\t");
		switch(ebx)
		{
			case signature_AMD_ebx:
				printf("AMD CPU DETECTED\n");
			break;
			case signature_INTEL_ebx:
				printf("INTEL CPU DETECTED\n");
			break;
			case signature_CENTAUR_ebx:
				printf("CENTAUR CPU DETECTED\n");
			break;
			default:
				printf("UNKNOWN CPU VENDOR\n");
			break;
		}
		return 0;
	}
	
	return -1;
}

bool check_cpuid_availability(void)
{
	unsigned int void_register = 0;
	return __get_cpuid(0, &void_register, & void_register, & void_register, &void_register);
}