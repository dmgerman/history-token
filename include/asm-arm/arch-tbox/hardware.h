multiline_comment|/*&n; * linux/include/asm-arm/arch-tbox/hardware.h&n; *&n; * Copyright (C) 1998, 1999, 2000 Philip Blundell&n; * Copyright (C) 2000 FutureTV Labs Ltd&n; *&n; * This file contains the hardware definitions of the Tbox&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef __ASM_ARCH_HARDWARE_H
DECL|macro|__ASM_ARCH_HARDWARE_H
mdefine_line|#define __ASM_ARCH_HARDWARE_H
multiline_comment|/*    Logical    Physical&n; * 0xfff00000&t;0x00100000&t;I/O&n; * 0xfff00000&t;0x00100000&t;  Expansion CS0&n; * 0xfff10000&t;0x00110000&t;  DMA&n; * 0xfff20000&t;0x00120000&t;  C-Cube&n; * 0xfff30000&t;0x00130000&t;  FPGA 1&n; * 0xfff40000&t;0x00140000&t;  UART 2&n; * 0xfff50000&t;0x00150000&t;  UART 1&n; * 0xfff60000&t;0x00160000&t;  CS8900&n; * 0xfff70000&t;0x00170000&t;  INTCONT&n; * 0xfff80000&t;0x00180000&t;  RAMDAC&n; * 0xfff90000&t;0x00190000&t;  Control 0&n; * 0xfffa0000&t;0x001a0000&t;  Control 1&n; * 0xfffb0000&t;0x001b0000&t;  Control 2&n; * 0xfffc0000&t;0x001c0000&t;  FPGA 2&n; * 0xfffd0000&t;0x001d0000&t;  INTRESET&n; * 0xfffe0000&t;0x001e0000&t;  C-Cube DMA throttle&n; * 0xffff0000&t;0x001f0000&t;  Expansion CS1&n; * 0xffe00000&t;0x82000000&t;cache flush&n; */
multiline_comment|/*&n; * Mapping areas&n; */
DECL|macro|IO_BASE
mdefine_line|#define IO_BASE&t;&t;&t;0xfff00000
DECL|macro|IO_START
mdefine_line|#define IO_START&t;&t;0x00100000
DECL|macro|FLUSH_BASE
mdefine_line|#define FLUSH_BASE&t;&t;0xffe00000
DECL|macro|INTCONT
mdefine_line|#define INTCONT&t;&t;&t;0xfff70000
DECL|macro|FPGA1CONT
mdefine_line|#define FPGA1CONT&t;&t;0xffff3000
multiline_comment|/*&n; * RAM definitions&n; */
DECL|macro|RAM_BASE
mdefine_line|#define RAM_BASE&t;&t;0x80000000
DECL|macro|FLUSH_BASE_PHYS
mdefine_line|#define FLUSH_BASE_PHYS&t;&t;0x82000000
DECL|macro|UNCACHEABLE_ADDR
mdefine_line|#define UNCACHEABLE_ADDR&t;INTCONT
macro_line|#endif
eof
