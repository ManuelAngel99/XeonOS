/*
* Author: manuel
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-17 10:14:00
* 
* File: system.h
* Description: A bunch of system utilities

*/

#ifndef KERNEL_SYSTEM_H
#define KERNEL_SYSTEM_H

#include <stdint.h>
#include <stdbool.h>

#ifdef _cplusplus
    extern "C" {
#endif

enum
{
    master_pic_command   = 0x20,
    master_pic_data      = 0x21,

    slave_pic_command    = 0xA0,
    slave_pic_data       = 0xA1,

    cmos_address         = 0x70,
    cmos_data            = 0x71,

    keyboard_data_port   = 0x60,
    keyboard_ack_port    = 0x61,
    keyboard_command_port= 0x64

} ports;



//Implemented in interrupts.c
void setup_interrupts(void);

//Implemented in gdt.c
void setup_gdt(void);

//Implemented in cpuid.c
uint32_t detect_cpu_family(void);
bool check_cpuid_availability(void);

//Implemented in acpi.c
bool check_ps2_controller(void);


#ifdef _cplusplus
}
#endif


#endif // SYSTEM_H
