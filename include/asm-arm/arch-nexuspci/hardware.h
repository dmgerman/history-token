multiline_comment|/*&n; * linux/include/asm-arm/arch-nexuspci/hardware.h&n; *&n; * Copyright (C) 1998, 1999, 2000 FutureTV Labs Ltd.&n; *&n; * This file contains the hardware definitions of the FTV PCI card.&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef __ASM_ARCH_HARDWARE_H
DECL|macro|__ASM_ARCH_HARDWARE_H
mdefine_line|#define __ASM_ARCH_HARDWARE_H
multiline_comment|/*    Logical    Physical&n; * 0xffe00000&t;0x20000000&t;INTCONT&n; * 0xffd00000&t;0x30000000&t;Status&n; * 0xffc00000&t;0x60000000&t;PLX registers&n; * 0xfe000000&t;0xC0000000&t;PCI I/O&n; * 0xfd000000&t;0x70000000&t;cache flush&n; * 0xfc000000&t;0x80000000&t;PCI/ISA memory&n; * 0xe0000000&t;0x10000000&t;SCC2691 DUART&n; */
multiline_comment|/*&n; * Mapping areas&n; */
DECL|macro|INTCONT_BASE
mdefine_line|#define INTCONT_BASE&t;&t;0xffe00000
DECL|macro|STATUS_BASE
mdefine_line|#define STATUS_BASE&t;&t;0xffd00000
DECL|macro|PLX_BASE
mdefine_line|#define PLX_BASE&t;&t;0xffc00000
DECL|macro|PCIO_BASE
mdefine_line|#define PCIO_BASE&t;&t;0xfe000000
DECL|macro|FLUSH_BASE
mdefine_line|#define FLUSH_BASE&t;&t;0xfd000000
DECL|macro|DUART_BASE
mdefine_line|#define DUART_BASE&t;&t;0xe0000000
DECL|macro|PCIMEM_BASE
mdefine_line|#define PCIMEM_BASE&t;&t;0xfc000000
DECL|macro|PLX_IO_START
mdefine_line|#define PLX_IO_START&t;&t;0xC0000000
DECL|macro|PLX_MEM_START
mdefine_line|#define PLX_MEM_START&t;&t;0x80000000
DECL|macro|PLX_START
mdefine_line|#define PLX_START&t;&t;0x60000000
DECL|macro|STATUS_START
mdefine_line|#define STATUS_START&t;&t;0x30000000
DECL|macro|INTCONT_START
mdefine_line|#define INTCONT_START&t;&t;0x20000000
DECL|macro|DUART_START
mdefine_line|#define DUART_START&t;&t;0x10000000
multiline_comment|/*&n; * RAM definitions&n; */
DECL|macro|RAM_BASE
mdefine_line|#define RAM_BASE&t;&t;0x40000000
DECL|macro|FLUSH_BASE_PHYS
mdefine_line|#define FLUSH_BASE_PHYS&t;&t;0x70000000
multiline_comment|/*&n; * Miscellaneous INTCONT bits&n; */
DECL|macro|INTCONT_FIQ_PLX
mdefine_line|#define INTCONT_FIQ_PLX&t;&t;0x00
DECL|macro|INTCONT_FIQ_D
mdefine_line|#define INTCONT_FIQ_D&t;&t;0x02
DECL|macro|INTCONT_FIQ_C
mdefine_line|#define INTCONT_FIQ_C&t;&t;0x04
DECL|macro|INTCONT_FIQ_B
mdefine_line|#define INTCONT_FIQ_B&t;&t;0x06
DECL|macro|INTCONT_FIQ_A
mdefine_line|#define INTCONT_FIQ_A&t;&t;0x08
DECL|macro|INTCONT_FIQ_SYSERR
mdefine_line|#define INTCONT_FIQ_SYSERR&t;0x0a
DECL|macro|INTCONT_IRQ_DUART
mdefine_line|#define INTCONT_IRQ_DUART&t;0x0c
DECL|macro|INTCONT_IRQ_PLX
mdefine_line|#define INTCONT_IRQ_PLX&t;&t;0x0e
DECL|macro|INTCONT_IRQ_D
mdefine_line|#define INTCONT_IRQ_D&t;&t;0x10
DECL|macro|INTCONT_IRQ_C
mdefine_line|#define INTCONT_IRQ_C&t;&t;0x12
DECL|macro|INTCONT_IRQ_B
mdefine_line|#define INTCONT_IRQ_B&t;&t;0x14
DECL|macro|INTCONT_IRQ_A
mdefine_line|#define INTCONT_IRQ_A&t;&t;0x16
DECL|macro|INTCONT_IRQ_SYSERR
mdefine_line|#define INTCONT_IRQ_SYSERR&t;0x1e
DECL|macro|INTCONT_WATCHDOG
mdefine_line|#define INTCONT_WATCHDOG&t;0x18
DECL|macro|INTCONT_LED
mdefine_line|#define INTCONT_LED&t;&t;0x1a
DECL|macro|INTCONT_PCI_RESET
mdefine_line|#define INTCONT_PCI_RESET&t;0x1c
DECL|macro|UNCACHEABLE_ADDR
mdefine_line|#define UNCACHEABLE_ADDR&t;STATUS_BASE
macro_line|#endif
eof
