multiline_comment|/*&n; * linux/include/asm-arm/arch-cl7500/hardware.h&n; *&n; * Copyright (C) 1996-1999 Russell King.&n; * Copyright (C) 1999 Nexus Electronics Ltd.&n; *&n; * This file contains the hardware definitions of the &n; * CL7500 evaluation board.&n; */
macro_line|#ifndef __ASM_ARCH_HARDWARE_H
DECL|macro|__ASM_ARCH_HARDWARE_H
mdefine_line|#define __ASM_ARCH_HARDWARE_H
macro_line|#include &lt;asm/arch/memory.h&gt;
macro_line|#include &lt;asm/hardware/iomd.h&gt;
multiline_comment|/*&n; * What hardware must be present&n; */
DECL|macro|HAS_IOMD
mdefine_line|#define HAS_IOMD
DECL|macro|HAS_VIDC20
mdefine_line|#define HAS_VIDC20
multiline_comment|/* Hardware addresses of major areas.&n; *  *_START is the physical address&n; *  *_SIZE  is the size of the region&n; *  *_BASE  is the virtual address&n; */
DECL|macro|IO_START
mdefine_line|#define IO_START&t;&t;0x03000000&t;/* I/O */
DECL|macro|IO_SIZE
mdefine_line|#define IO_SIZE&t;&t;&t;0x01000000
DECL|macro|IO_BASE
mdefine_line|#define IO_BASE&t;&t;&t;0xe0000000
DECL|macro|ISA_START
mdefine_line|#define ISA_START&t;&t;0x0c000000&t;/* ISA */
DECL|macro|ISA_SIZE
mdefine_line|#define ISA_SIZE&t;&t;0x00010000
DECL|macro|ISA_BASE
mdefine_line|#define ISA_BASE&t;&t;0xe1000000
DECL|macro|FLASH_START
mdefine_line|#define FLASH_START&t;&t;0x01000000&t;/* XXX */
DECL|macro|FLASH_SIZE
mdefine_line|#define FLASH_SIZE&t;&t;0x01000000
DECL|macro|FLASH_BASE
mdefine_line|#define FLASH_BASE&t;&t;0xe2000000
DECL|macro|LED_START
mdefine_line|#define LED_START&t;&t;0x0302B000
DECL|macro|LED_SIZE
mdefine_line|#define LED_SIZE&t;&t;0x00001000
DECL|macro|LED_BASE
mdefine_line|#define LED_BASE&t;&t;0xe3000000
DECL|macro|LED_ADDRESS
mdefine_line|#define LED_ADDRESS&t;&t;(LED_BASE + 0xa00)
multiline_comment|/* Let&squot;s define SCREEN_START for CL7500, even though it&squot;s a lie. */
DECL|macro|SCREEN_START
mdefine_line|#define SCREEN_START&t;&t;0x02000000&t;/* VRAM */
DECL|macro|SCREEN_END
mdefine_line|#define SCREEN_END&t;&t;0xdfc00000
DECL|macro|SCREEN_BASE
mdefine_line|#define SCREEN_BASE&t;&t;0xdf800000
DECL|macro|FLUSH_BASE
mdefine_line|#define FLUSH_BASE&t;&t;0xdf000000
DECL|macro|VIDC_BASE
mdefine_line|#define VIDC_BASE&t;&t;0xe0400000
DECL|macro|IOMD_BASE
mdefine_line|#define IOMD_BASE&t;&t;0xe0200000
DECL|macro|IOC_BASE
mdefine_line|#define IOC_BASE&t;&t;0xe0200000
DECL|macro|FLOPPYDMA_BASE
mdefine_line|#define FLOPPYDMA_BASE&t;&t;0xe002a000
DECL|macro|PCIO_BASE
mdefine_line|#define PCIO_BASE&t;&t;0xe0010000
DECL|macro|FLUSH_BASE_PHYS
mdefine_line|#define FLUSH_BASE_PHYS&t;&t;0x00000000&t;/* ROM */
DECL|macro|vidc_writel
mdefine_line|#define vidc_writel(val)&t;__raw_writel(val, VIDC_BASE)
multiline_comment|/* in/out bias for the ISA slot region */
DECL|macro|ISASLOT_IO
mdefine_line|#define ISASLOT_IO&t;&t;0x80400000
macro_line|#endif
eof
