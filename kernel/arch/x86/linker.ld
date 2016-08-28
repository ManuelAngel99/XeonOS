ENTRY(start) /*The entry point will be the start function*/

SECTIONS
{
	/* Place the kernel at 1MiB*/
	. = 1M;

	.text BLOCK(4K) : ALIGN(4K)
	{
		*(.multiboot) /*Multiboot header is placed at the beggining of the executable do grub can find it*/
		*(.text)
	}

	/* Read-only data. */
	.rodata BLOCK(4K) : ALIGN(4K)
	{
		*(.rodata)
	}

	/* Read-write data (initialized) */
	.data BLOCK(4K) : ALIGN(4K)
	{
		*(.data)
	}

	/* Read-write data (uninitialized) and stack */
	.bss BLOCK(4K) : ALIGN(4K)
	{
		*(COMMON)
		*(.bss)
		*(.bootstrap_stack)
	}
	end_of_kernel = .;
}