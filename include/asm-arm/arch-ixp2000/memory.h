multiline_comment|/*&n; * linux/include/asm-arm/arch-ixp2000/memory.h&n; *&n; * Copyright (c) 2002 Intel Corp.&n; * Copyright (c) 2003-2004 MontaVista Software, Inc.&n; *&n; *  This program is free software; you can redistribute  it and/or modify it&n; *  under  the terms of  the GNU General  Public License as published by the&n; *  Free Software Foundation;  either version 2 of the  License, or (at your&n; *  option) any later version.&n; */
macro_line|#ifndef __ASM_ARCH_MEMORY_H
DECL|macro|__ASM_ARCH_MEMORY_H
mdefine_line|#define __ASM_ARCH_MEMORY_H
DECL|macro|PHYS_OFFSET
mdefine_line|#define PHYS_OFFSET&t;(0x00000000UL)
multiline_comment|/*&n; * Virtual view &lt;-&gt; DMA view memory address translations&n; * virt_to_bus: Used to translate the virtual address to an&n; *&t;&t;address suitable to be passed to set_dma_addr&n; * bus_to_virt: Used to convert an address for DMA operations&n; *&t;&t;to an address that the kernel can use.&n; */
macro_line|#include &lt;asm/arch/ixp2000-regs.h&gt;
DECL|macro|__virt_to_bus
mdefine_line|#define __virt_to_bus(v) &bslash;&n;&t;(((__virt_to_phys(v) - 0x0) + (*IXP2000_PCI_SDRAM_BAR &amp; 0xfffffff0)))
DECL|macro|__bus_to_virt
mdefine_line|#define __bus_to_virt(b) &bslash;&n;&t;__phys_to_virt((((b - (*IXP2000_PCI_SDRAM_BAR &amp; 0xfffffff0)) + 0x0)))
macro_line|#endif
eof
