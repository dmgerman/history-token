multiline_comment|/*&n; *  linux/include/asm-arm/arch-clps711x/io.h&n; *&n; *  Copyright (C) 1999 ARM Limited&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef __ASM_ARM_ARCH_IO_H
DECL|macro|__ASM_ARM_ARCH_IO_H
mdefine_line|#define __ASM_ARM_ARCH_IO_H
DECL|macro|IO_SPACE_LIMIT
mdefine_line|#define IO_SPACE_LIMIT 0xffffffff
DECL|macro|__io
mdefine_line|#define __io(a)&t;&t;&t;((a))
DECL|macro|__mem_pci
mdefine_line|#define __mem_pci(a)&t;&t;((unsigned long)(a))
DECL|macro|__mem_isa
mdefine_line|#define __mem_isa(a)&t;&t;((unsigned long)(a))
multiline_comment|/*&n; * We don&squot;t support ins[lb]/outs[lb].  Make them fault.&n; */
DECL|macro|__raw_readsb
mdefine_line|#define __raw_readsb(p,d,l)&t;do { *(int *)0 = 0; } while (0)
DECL|macro|__raw_readsl
mdefine_line|#define __raw_readsl(p,d,l)&t;do { *(int *)0 = 0; } while (0)
DECL|macro|__raw_writesb
mdefine_line|#define __raw_writesb(p,d,l)&t;do { *(int *)0 = 0; } while (0)
DECL|macro|__raw_writesl
mdefine_line|#define __raw_writesl(p,d,l)&t;do { *(int *)0 = 0; } while (0)
macro_line|#endif
eof
