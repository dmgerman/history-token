multiline_comment|/*&n; *  linux/include/asm-arm/arch-epxa10db/io.h&n; *&n; *  Copyright (C) 1999 ARM Limited&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef __ASM_ARM_ARCH_IO_H
DECL|macro|__ASM_ARM_ARCH_IO_H
mdefine_line|#define __ASM_ARM_ARCH_IO_H
DECL|macro|IO_SPACE_LIMIT
mdefine_line|#define IO_SPACE_LIMIT 0xffff
multiline_comment|/*&n; * Generic virtual read/write&n; */
multiline_comment|/*#define outsw   __arch_writesw&n;#define outsl   __arch_writesl&n;#define outsb   __arch_writesb&n;#define insb    __arch_readsb&n;#define insw    __arch_readsw&n;#define insl    __arch_readsl*/
DECL|macro|__io
mdefine_line|#define __io(a)&t;&t;&t;(a)
DECL|macro|__mem_pci
mdefine_line|#define __mem_pci(a)            (a) 
macro_line|#endif
eof
