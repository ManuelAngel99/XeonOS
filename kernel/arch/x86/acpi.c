/*
* Author: Manuel Ángel Suárez Álvarez
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-15 17:25:08
* 
* File: acpi.c
* Description: A set of functions to detect and parse the ACPI tables
*/
#include <arch/x86/acpi.h>
#include <arch/x86/system.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

RSPDDescriptor_t* 	RSDP  = 0;
RSPDDescriptorV2_t* RSDPV2= 0;
RSDT_t*  			RSDT  = 0;
XSDT_t*  			XSDT  = 0;
FATDT_t* 			FATDT = 0;

FATDT_t				FATDT_COPY;

uint8_t acpi_version = 0;

void find_tables(void)
{	
    uint16_t *ebda_base = (uint16_t*)0x40E0;
    
    uint8_t *ebda_pointer = (uint8_t*)0x40E0;
    uint8_t *bios_pointer = (uint8_t*)0x000E0000;

	//The RSD can be in the first 1KB of the ebda or in the lower 1MiB of the bios extended memory
	while( (uint32_t)ebda_pointer < (uint32_t)(ebda_base + 0x400) )
	{
		if( memcmp(ebda_pointer, "RSD PTR ", 8) == 0)
		{
			if( checksum( (uint32_t*)ebda_pointer, sizeof(RSPDDescriptor_t) ) )
			{
				RSDP = (RSPDDescriptor_t*)ebda_pointer;
				acpi_version = RSDP->revision;

				if(acpi_version != 0)
					RSDPV2 = (RSPDDescriptorV2_t*)ebda_pointer;

				break;
			}
		}

		//the rsd pointer is located in a 16 byte boundary
		ebda_pointer += 16;
	}

	while( (uint32_t)bios_pointer < 0x000FFFFF && RSDP == 0 && RSDPV2 == 0)
	{
		if( memcmp(bios_pointer, "RSD PTR ", 8) == 0 )
		{
			if( checksum( (uint32_t*)bios_pointer, sizeof(RSPDDescriptor_t) ) )
			{
				RSDP = (RSPDDescriptor_t*)bios_pointer;
				acpi_version = RSDP->revision;
				
				if(acpi_version != 0)
					RSDPV2 = (RSPDDescriptorV2_t*)bios_pointer;

				break;
			}
		}

		//the rsd pointer is located in a 16 byte boundary
		bios_pointer += 16;
	}

	//Use XSDT if we are acpi version is over 1.0
	if(RSDPV2 != 0)
	{
		XSDT = (XSDT_t*)(uint32_t)RSDPV2->xsdt_address;

		if(checksum( (uint32_t*)XSDT, (uint32_t)XSDT->header.length ))
		{

			FATDT = (FATDT_t*)find_entry_at_xsdt("FACP");
			if(!checksum( (uint32_t*)FATDT, FATDT->header.length))
				FATDT = NULL;
			FATDT_COPY = *FATDT;
		}
	}
	else if( RSDP != 0)
	{
		RSDT = (RSDT_t*)RSDP->rsdt_address;

		if( checksum( (uint32_t*)RSDT, RSDT->header.length ))
		{
			FATDT = (FATDT_t*)find_entry_at_rsdt("FACP");
			if(!checksum( (uint32_t*)FATDT, FATDT->header.length))
				FATDT = NULL;
		}
		else
			RSDT = 0;
	}
}

//Check if an address has a valid table in it by adding all the values in that table and comparing the result to 0
bool checksum(void *address, uint32_t length)
{
	uint8_t* base_pointer = (uint8_t*) address;
	uint8_t checksum = 0;

	for(uint32_t i = 0; i < length; i++)
	{
		checksum += *base_pointer;
		base_pointer++;
	}
	//If the checksum is equal to 0 the table is valid
	return checksum == 0 ? true : false;

}


void* find_entry_at_xsdt(char* identifier)
{
	if(XSDT == 0)
		return NULL;
	
	uint32_t i, number_of_entries = ( XSDT->header.length - sizeof(RSDT->header)) / 8;
	ACPISDTHeader_t* header;

	for(i = 0; i < number_of_entries; i++)
	{
		header = (ACPISDTHeader_t*)(XSDT->pointer_to_other_SDT + i);

		//Compare the signature of the header with the identifier
		if(memcmp( (void*)header, (void*)identifier, 4) == 0)
			if(checksum( (uint32_t*)header, header->length))
				return (void*)header;
	}

	return NULL;
}

void* find_entry_at_rsdt(char* identifier)
{
	if(RSDT == 0)
		return NULL;

	uint32_t i, number_of_entries = (RSDT->header.length - sizeof(RSDT->header)) / 4;
	ACPISDTHeader_t* header;

	for(i = 0; i < number_of_entries; i++)
	{
		header = (ACPISDTHeader_t*)(RSDT->pointer_to_other_SDT + i);
		//Compare the signature of the header with the identifier
		if(memcmp( (void*)header, (void*)identifier,  4) == 0)
			if(checksum( (uint32_t*)header, header->length))
				return (void*)header;

	}
	return NULL;
}

bool check_ps2_controller(void)
{
	if(acpi_version != 0)
		if((FATDT_COPY.boot_architecture_flags >> 1) & 0x1)
			return true;
		else
			return false;
	else
		return true;
}