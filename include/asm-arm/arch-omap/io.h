multiline_comment|/*&n; * linux/include/asm-arm/arch-omap/io.h&n; *&n; * Copied from linux/include/asm-arm/arch-sa1100/io.h&n; * Copyright (C) 1997-1999 Russell King&n; *&n; * Modifications:&n; *  06-12-1997&t;RMK&t;Created.&n; *  07-04-1999&t;RMK&t;Major cleanup&n; */
macro_line|#ifndef __ASM_ARM_ARCH_IO_H
DECL|macro|__ASM_ARM_ARCH_IO_H
mdefine_line|#define __ASM_ARM_ARCH_IO_H
DECL|macro|IO_SPACE_LIMIT
mdefine_line|#define IO_SPACE_LIMIT 0xffffffff
multiline_comment|/*&n; * We don&squot;t actually have real ISA nor PCI buses, but there is so many&n; * drivers out there that might just work if we fake them...&n; */
DECL|macro|__io
mdefine_line|#define __io(a)&t;&t;&t;(PCIO_BASE + (a))
DECL|macro|__mem_pci
mdefine_line|#define __mem_pci(a)&t;&t;((unsigned long)(a))
DECL|macro|__mem_isa
mdefine_line|#define __mem_isa(a)&t;&t;((unsigned long)(a))
multiline_comment|/*&n; * Functions to access the OMAP IO region&n; *&n; * NOTE: - Use omap_read/write[bwl] for physical register addresses&n; *&t; - Use __raw_read/write[bwl]() for virtual register addresses&n; *&t; - Use IO_ADDRESS(phys_addr) to convert registers to virtual addresses&n; *&t; - DO NOT use hardcoded virtual addresses to allow changing the&n; *&t;   IO address space again if needed&n; */
DECL|macro|omap_readb
mdefine_line|#define omap_readb(a)&t;&t;(*(volatile unsigned char  *)IO_ADDRESS(a))
DECL|macro|omap_readw
mdefine_line|#define omap_readw(a)&t;&t;(*(volatile unsigned short *)IO_ADDRESS(a))
DECL|macro|omap_readl
mdefine_line|#define omap_readl(a)&t;&t;(*(volatile unsigned int   *)IO_ADDRESS(a))
DECL|macro|omap_writeb
mdefine_line|#define omap_writeb(v,a)&t;(*(volatile unsigned char  *)IO_ADDRESS(a) = (v))
DECL|macro|omap_writew
mdefine_line|#define omap_writew(v,a)&t;(*(volatile unsigned short *)IO_ADDRESS(a) = (v))
DECL|macro|omap_writel
mdefine_line|#define omap_writel(v,a)&t;(*(volatile unsigned int   *)IO_ADDRESS(a) = (v))
macro_line|#endif
eof
