multiline_comment|/*&n; *  linux/include/asm-arm/arch-integrator/hardware.h&n; *&n; *  This file contains the hardware definitions of the Integrator.&n; *&n; *  Copyright (C) 1999 ARM Limited.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef __ASM_ARCH_HARDWARE_H
DECL|macro|__ASM_ARCH_HARDWARE_H
mdefine_line|#define __ASM_ARCH_HARDWARE_H
macro_line|#include &lt;asm/sizes.h&gt;
macro_line|#include &lt;asm/arch/platform.h&gt;
multiline_comment|/*&n; * Where in virtual memory the IO devices (timers, system controllers&n; * and so on)&n; */
DECL|macro|IO_BASE
mdefine_line|#define IO_BASE&t;&t;&t;0xF0000000                 
singleline_comment|// VA of IO 
DECL|macro|IO_SIZE
mdefine_line|#define IO_SIZE&t;&t;&t;0x0B000000                 
singleline_comment|// How much?
DECL|macro|IO_START
mdefine_line|#define IO_START&t;&t;INTEGRATOR_HDR_BASE        
singleline_comment|// PA of IO
multiline_comment|/*&n; * Similar to above, but for PCI addresses (memory, IO, Config and the&n; * V3 chip itself).  WARNING: this has to mirror definitions in platform.h&n; */
DECL|macro|PCI_MEMORY_VADDR
mdefine_line|#define PCI_MEMORY_VADDR        0xe8000000
DECL|macro|PCI_CONFIG_VADDR
mdefine_line|#define PCI_CONFIG_VADDR        0xec000000
DECL|macro|PCI_V3_VADDR
mdefine_line|#define PCI_V3_VADDR            0xed000000
DECL|macro|PCI_IO_VADDR
mdefine_line|#define PCI_IO_VADDR            0xee000000
DECL|macro|PCIO_BASE
mdefine_line|#define PCIO_BASE&t;&t;PCI_IO_VADDR
DECL|macro|PCIMEM_BASE
mdefine_line|#define PCIMEM_BASE&t;&t;PCI_MEMORY_VADDR
multiline_comment|/* macro to get at IO space when running virtually */
DECL|macro|IO_ADDRESS
mdefine_line|#define IO_ADDRESS(x) (((x) &gt;&gt; 4) + IO_BASE) 
DECL|macro|pcibios_assign_all_busses
mdefine_line|#define pcibios_assign_all_busses()&t;1
DECL|macro|PCIBIOS_MIN_IO
mdefine_line|#define PCIBIOS_MIN_IO&t;&t;0x6000
DECL|macro|PCIBIOS_MIN_MEM
mdefine_line|#define PCIBIOS_MIN_MEM &t;0x00100000
macro_line|#endif
eof
