/*
* Author: Manuel Ángel Suárez Álvarez
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-15 17:04:48
* 
* File: acpi.h
* Description: Defines the necesary infraestructure to use the ACPI
*/


#ifndef ACPI_H
#define ACPI_H

#ifdef _cplusplus
	extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

//Root System Description Pointer
typedef struct RSPDDescriptor
{
	char signature[8];
	uint8_t checksum;
	char OEMID[6];
	uint8_t revision;
	uint32_t rsdt_address;
}__attribute__((packed)) RSPDDescriptor_t;

//Root System Description Pointer v2!
typedef struct RSPDDescriptorV2
{
	RSPDDescriptor_t first_part;

	uint32_t lenght;
	uint64_t xsdt_address;
	uint8_t extended_checksum;
	uint8_t reserved[3];
}__attribute__((packed)) RSPDDescriptorV2_t;


typedef struct ACPISDTHeader {
  char signature[4];
  uint32_t length;
  uint8_t revision;
  uint8_t checksum;
  char OEMID[6];
  char OEM_table_id[8];
  uint32_t OEM_revision;
  uint32_t creator_id;
  uint32_t creator_revision;
}__attribute__((packed)) ACPISDTHeader_t;

//RSDT structure if rsdt pointer is used
typedef struct RSDT {
 	ACPISDTHeader_t header;
 	uint32_t* pointer_to_other_SDT;
}__attribute__((packed)) RSDT_t;

//RSDT structure if xsdt pointer is used
typedef struct XSDT
{
	ACPISDTHeader_t header;
	uint64_t* pointer_to_other_SDT;
}__attribute__((packed)) XSDT_t;

typedef struct GenericAddressStructure
{
  uint8_t address_space;
  uint8_t bit_width;
  uint8_t bit_offset;
  uint8_t access_size;
  uint64_t address;
}__attribute__((packed)) GenericAddressStructure_t;


//Fixed ACPI Description table

typedef struct FADT
{
    ACPISDTHeader_t header;
    uint32_t firmware_ctrl;
    uint32_t dsdt;
 
    // field used in ACPI 1.0; no longer in use, for compatibility only
    uint8_t  reserved;
 
    uint8_t  preferred_power_management_profile;
    uint16_t SCI_interrupt;
    uint32_t SMI_command_port;
    uint8_t  acpi_enable;
    uint8_t  acpi_disable;
    uint8_t  S4BIOS_REQ;
    uint8_t  PSTATE_control;
    uint32_t PM1a_event_block;
    uint32_t PM1b_event_block;
    uint32_t PM1a_control_block;
    uint32_t PM1b_control_block;
    uint32_t PM2_control_block;
    uint32_t PM_timer_block;
    uint32_t GPE0_block;
    uint32_t GPE1_block;
    uint8_t  PM1_event_length;
    uint8_t  PM1_control_length;
    uint8_t  PM2_control_length;
    uint8_t  PM_timer_length;
    uint8_t  GPE0_length;
    uint8_t  GPE1_length;
    uint8_t  GPE1_base;
    uint8_t  c_state_control;
    uint16_t worst_C2_latency;
    uint16_t worst_C3_latency;
    uint16_t flush_size;
    uint16_t flush_stride;
    uint8_t  duty_offset;
    uint8_t  duty_width;
    uint8_t  day_alarm;
    uint8_t  month_alarm;
    uint8_t  century;
 
    // reserved in ACPI 1.0; used since ACPI 2.0+
    uint16_t boot_architecture_flags;
 
    uint8_t  reserved_2;
    uint32_t flags;
 
    // 12 byte structure; see below for details
    GenericAddressStructure_t reset_reg;
 
    uint8_t  reset_value;
    uint8_t  reserved_3[3];
 
    // 64bit pointers - Available on ACPI 2.0+
    uint64_t                X_firmware_control;
    uint64_t                X_dsdt;
 
    GenericAddressStructure_t X_PM1a_event_block;
    GenericAddressStructure_t X_PM1b_event_block;
    GenericAddressStructure_t X_PM1a_control_block;
    GenericAddressStructure_t X_PM1b_control_block;
    GenericAddressStructure_t X_PM2_control_block;
    GenericAddressStructure_t X_PM_timer_block;
    GenericAddressStructure_t X_GPE0_block;
    GenericAddressStructure_t X_GPE1_block;
}__attribute__((packed)) FATDT_t;

bool checksum(void *address, uint32_t length);

void find_tables(void);
void* find_entry_at_rsdt(char* identifier);
void* find_entry_at_xsdt(char* identifier);

#ifdef _cplusplus
	}
#endif

#endif // ACPI_H


