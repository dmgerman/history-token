#include <linux/init.h>
#include <asm/page.h>

	.section ".data.page_aligned"

	.globl vdso32_start, vdso32_end
	.balign PAGE_SIZE
vdso32_start:
	.incbin "arch/ppc64/kernel/vdso32/vdso32.so"
	.balign PAGE_SIZE
vdso32_end:

	.previous
