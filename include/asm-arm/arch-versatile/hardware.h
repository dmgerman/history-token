multiline_comment|/*&n; *  linux/include/asm-arm/arch-versatile/hardware.h&n; *&n; *  This file contains the hardware definitions of the Versatile boards.&n; *&n; *  Copyright (C) 2003 ARM Limited.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef __ASM_ARCH_HARDWARE_H
DECL|macro|__ASM_ARCH_HARDWARE_H
mdefine_line|#define __ASM_ARCH_HARDWARE_H
macro_line|#include &lt;asm/sizes.h&gt;
macro_line|#include &lt;asm/arch/platform.h&gt;
singleline_comment|// FIXME = PCI settings need to be fixed!!!!!
multiline_comment|/*&n; * Similar to above, but for PCI addresses (memory, IO, Config and the&n; * V3 chip itself).  WARNING: this has to mirror definitions in platform.h&n; */
DECL|macro|PCI_MEMORY_VADDR
mdefine_line|#define PCI_MEMORY_VADDR       0xe8000000
DECL|macro|PCI_CONFIG_VADDR
mdefine_line|#define PCI_CONFIG_VADDR       0xec000000
DECL|macro|PCI_V3_VADDR
mdefine_line|#define PCI_V3_VADDR           0xed000000
DECL|macro|PCI_IO_VADDR
mdefine_line|#define PCI_IO_VADDR           0xee000000
DECL|macro|PCIO_BASE
mdefine_line|#define PCIO_BASE&t;&t;PCI_IO_VADDR
DECL|macro|PCIMEM_BASE
mdefine_line|#define PCIMEM_BASE&t;&t;PCI_MEMORY_VADDR
multiline_comment|/* macro to get at IO space when running virtually */
DECL|macro|IO_ADDRESS
mdefine_line|#define IO_ADDRESS(x)&t;&t;(((x) &amp; 0x0fffffff) + (((x) &gt;&gt; 4) &amp; 0x0f000000) + 0xf0000000)
macro_line|#endif
eof
