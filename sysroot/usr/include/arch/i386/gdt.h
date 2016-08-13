/*
* Author: manuel
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-13 20:00:54
* 
* File: gdt.h
* Description: 	Defines the data structure of the GDT every GDT entry, GDT pointer as well as some
*				functions that make installing the GDT easier
*/
#ifndef GDT_H
#define GDT_H

/*
    GDT ENTRY LAYOUT:
    Bits:       Description:
    0-15        Segment lenght(limit)
    16-31       Pointer to the beggining of the zone(base)
    32-39       Extension of the pointer
    40-47       Access rights
    48-55       Segment lenght extension
    56-63       Extension of the pointer
*/

struct GlobalDescriptorTableEntry
{
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t  base_middle;
    uint8_t  access;
    uint8_t  granularity;
    uint8_t  base_high;
} __attribute__((packed)); //Prevent GCC to create padding spaces or rearrange the structure

struct GoblalDescriptorPointer
{
    uint16_t base;            //The total size of the GDT
    uint32_t address;         //The address of the first GDT entry
}__attribute__((packed));

	//This two variables will store the gdt and the gdt pointer
struct GlobalDescriptorTableEntry gdt[5];
struct GoblalDescriptorPointer gdt_pointer;

void gdt_set_gate(size_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);
void setup_gdt(void);
extern void load_gdt();



#endif // GDT_H
