multiline_comment|/*&n; *  linux/include/asm-arm/arch-anakin/hardware.h&n; *&n; *  Copyright (C) 2001 Aleph One Ltd. for Acunia N.V.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  Changelog:&n; *   10-Apr-2001 TTC&t;Created&n; */
macro_line|#ifndef __ASM_ARCH_HARDWARE_H
DECL|macro|__ASM_ARCH_HARDWARE_H
mdefine_line|#define __ASM_ARCH_HARDWARE_H
multiline_comment|/*&n; * Memory map&n; */
DECL|macro|SRAM_START
mdefine_line|#define SRAM_START&t;&t;0x00000000
DECL|macro|SRAM_SIZE
mdefine_line|#define SRAM_SIZE&t;&t;0x00100000
DECL|macro|SRAM_BASE
mdefine_line|#define SRAM_BASE&t;&t;0xdf000000
DECL|macro|SDRAM_START
mdefine_line|#define SDRAM_START&t;&t;0x20000000
DECL|macro|SDRAM_SIZE
mdefine_line|#define SDRAM_SIZE&t;&t;0x04000000
DECL|macro|SDRAM_BASE
mdefine_line|#define SDRAM_BASE&t;&t;0xc0000000
DECL|macro|IO_START
mdefine_line|#define IO_START&t;&t;0x40000000
DECL|macro|IO_SIZE
mdefine_line|#define IO_SIZE&t;&t;&t;0x00100000
DECL|macro|IO_BASE
mdefine_line|#define IO_BASE&t;&t;&t;0xe0000000
DECL|macro|FLASH_START
mdefine_line|#define FLASH_START&t;&t;0x60000000
DECL|macro|FLASH_SIZE
mdefine_line|#define FLASH_SIZE&t;&t;0x00080000
DECL|macro|FLASH_BASE
mdefine_line|#define FLASH_BASE&t;&t;0xe8000000
DECL|macro|VGA_START
mdefine_line|#define VGA_START&t;&t;0x80000000
DECL|macro|VGA_SIZE
mdefine_line|#define VGA_SIZE&t;&t;0x0002db40
DECL|macro|VGA_BASE
mdefine_line|#define VGA_BASE&t;&t;0xf0000000
multiline_comment|/*&n; * IO map&n; */
DECL|macro|IO_CONTROLLER
mdefine_line|#define IO_CONTROLLER&t;&t;0x00000
DECL|macro|INTERRUPT_CONTROLLER
mdefine_line|#define INTERRUPT_CONTROLLER&t;0x02000
DECL|macro|UART0
mdefine_line|#define UART0&t;&t;&t;0x04000
DECL|macro|UART1
mdefine_line|#define UART1&t;&t;&t;0x06000
DECL|macro|UART2
mdefine_line|#define UART2&t;&t;&t;0x08000
DECL|macro|CODEC
mdefine_line|#define CODEC&t;&t;&t;0x0a000
DECL|macro|UART4
mdefine_line|#define UART4&t;&t;&t;0x0c000
DECL|macro|UART3
mdefine_line|#define UART3&t;&t;&t;0x0e000
DECL|macro|DISPLAY_CONTROLLER
mdefine_line|#define DISPLAY_CONTROLLER&t;0x10000
DECL|macro|DAB
mdefine_line|#define DAB&t;&t;&t;0x12000
DECL|macro|STATE_CONTROLLER
mdefine_line|#define STATE_CONTROLLER&t;0x14000
DECL|macro|CAN
mdefine_line|#define CAN&t;&t;&t;0x23000
DECL|macro|COMPACTFLASH
mdefine_line|#define COMPACTFLASH&t;&t;0x24000
multiline_comment|/*&n; * Use SRAM for D-cache flush&n; */
DECL|macro|FLUSH_BASE_PHYS
mdefine_line|#define FLUSH_BASE_PHYS&t;&t;SRAM_START
DECL|macro|FLUSH_BASE
mdefine_line|#define FLUSH_BASE&t;&t;SRAM_BASE
DECL|macro|UNCACHEABLE_ADDR
mdefine_line|#define UNCACHEABLE_ADDR&t;(SRAM_BASE + 0x10000)
multiline_comment|/*&n; * Use SDRAM for memory&n; */
DECL|macro|MEM_SIZE
mdefine_line|#define MEM_SIZE&t;&t;SDRAM_SIZE
macro_line|#endif
eof
