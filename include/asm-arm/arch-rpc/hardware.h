multiline_comment|/*&n; *  linux/include/asm-arm/arch-rpc/hardware.h&n; *&n; *  Copyright (C) 1996-1999 Russell King.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  This file contains the hardware definitions of the RiscPC series machines.&n; */
macro_line|#ifndef __ASM_ARCH_HARDWARE_H
DECL|macro|__ASM_ARCH_HARDWARE_H
mdefine_line|#define __ASM_ARCH_HARDWARE_H
macro_line|#include &lt;asm/arch/memory.h&gt;
multiline_comment|/*&n; * What hardware must be present&n; */
DECL|macro|HAS_IOMD
mdefine_line|#define HAS_IOMD
DECL|macro|HAS_VIDC20
mdefine_line|#define HAS_VIDC20
multiline_comment|/* Hardware addresses of major areas.&n; *  *_START is the physical address&n; *  *_SIZE  is the size of the region&n; *  *_BASE  is the virtual address&n; */
DECL|macro|RAM_SIZE
mdefine_line|#define RAM_SIZE&t;&t;0x10000000
DECL|macro|RAM_START
mdefine_line|#define RAM_START&t;&t;0x10000000
DECL|macro|EASI_SIZE
mdefine_line|#define EASI_SIZE&t;&t;0x08000000&t;/* EASI I/O */
DECL|macro|EASI_START
mdefine_line|#define EASI_START&t;&t;0x08000000
DECL|macro|EASI_BASE
mdefine_line|#define EASI_BASE&t;&t;0xe5000000
DECL|macro|IO_START
mdefine_line|#define IO_START&t;&t;0x03000000&t;/* I/O */
DECL|macro|IO_SIZE
mdefine_line|#define IO_SIZE&t;&t;&t;0x01000000
DECL|macro|IO_BASE
mdefine_line|#define IO_BASE&t;&t;&t;0xe0000000
DECL|macro|SCREEN_START
mdefine_line|#define SCREEN_START&t;&t;0x02000000&t;/* VRAM */
DECL|macro|SCREEN_END
mdefine_line|#define SCREEN_END&t;&t;0xdfc00000
DECL|macro|SCREEN_BASE
mdefine_line|#define SCREEN_BASE&t;&t;0xdf800000
DECL|macro|FLUSH_BASE
mdefine_line|#define FLUSH_BASE&t;&t;0xdf000000
DECL|macro|UNCACHEABLE_ADDR
mdefine_line|#define UNCACHEABLE_ADDR&t;0xdf010000
multiline_comment|/*&n; * IO Addresses&n; */
DECL|macro|VIDC_BASE
mdefine_line|#define VIDC_BASE&t;&t;0xe0400000
DECL|macro|EXPMASK_BASE
mdefine_line|#define EXPMASK_BASE&t;&t;0xe0360000
DECL|macro|IOMD_BASE
mdefine_line|#define IOMD_BASE&t;&t;0xe0200000
DECL|macro|IOC_BASE
mdefine_line|#define IOC_BASE&t;&t;0xe0200000
DECL|macro|PCIO_BASE
mdefine_line|#define PCIO_BASE&t;&t;0xe0010000
DECL|macro|FLOPPYDMA_BASE
mdefine_line|#define FLOPPYDMA_BASE&t;&t;0xe002a000
DECL|macro|FLUSH_BASE_PHYS
mdefine_line|#define FLUSH_BASE_PHYS&t;&t;0x00000000&t;/* ROM */
DECL|macro|vidc_writel
mdefine_line|#define vidc_writel(val)&t;__raw_writel(val, VIDC_BASE)
DECL|macro|IO_EC_EASI_BASE
mdefine_line|#define IO_EC_EASI_BASE&t;&t;0x81400000
DECL|macro|IO_EC_IOC4_BASE
mdefine_line|#define IO_EC_IOC4_BASE&t;&t;0x8009c000
DECL|macro|IO_EC_IOC_BASE
mdefine_line|#define IO_EC_IOC_BASE&t;&t;0x80090000
DECL|macro|IO_EC_MEMC8_BASE
mdefine_line|#define IO_EC_MEMC8_BASE&t;0x8000ac00
DECL|macro|IO_EC_MEMC_BASE
mdefine_line|#define IO_EC_MEMC_BASE&t;&t;0x80000000
DECL|macro|EXPMASK_STATUS
mdefine_line|#define&t;EXPMASK_STATUS&t;&t;(EXPMASK_BASE + 0x00)
DECL|macro|EXPMASK_ENABLE
mdefine_line|#define EXPMASK_ENABLE&t;&t;(EXPMASK_BASE + 0x04)
macro_line|#endif
eof
