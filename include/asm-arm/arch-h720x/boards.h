multiline_comment|/*&n; * linux/include/asm-arm/arch-h720x/boards.h&n; *&n; * Copyright (C) 2003 Thomas Gleixner &lt;tglx@linutronix.de&gt;&n; *           (C) 2003 Robert Schwebel &lt;r.schwebel@pengutronix.de&gt;&n; *&n; * This file contains the board specific defines for various devices&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#ifndef __ASM_ARCH_HARDWARE_INCMACH_H
macro_line|#error Do not include this file directly. Include asm/hardware.h instead !
macro_line|#endif
multiline_comment|/* Hynix H7202 developer board specific device defines */
macro_line|#ifdef CONFIG_ARCH_H7202
multiline_comment|/* FLASH */
DECL|macro|FLASH_VIRT
mdefine_line|#define FLASH_VIRT&t;&t;0xd0000000
DECL|macro|FLASH_PHYS
mdefine_line|#define FLASH_PHYS&t;&t;0x00000000
DECL|macro|FLASH_SIZE
mdefine_line|#define FLASH_SIZE&t;&t;0x02000000
multiline_comment|/* onboard LAN controller */
DECL|macro|ETH0_PHYS
macro_line|# define ETH0_PHYS&t;&t;0x08000000
multiline_comment|/* Touch screen defines */
multiline_comment|/* GPIO Port */
DECL|macro|PEN_GPIO
mdefine_line|#define PEN_GPIO&t;&t;GPIO_B_VIRT
multiline_comment|/* Bitmask for pen down interrupt */
DECL|macro|PEN_INT_BIT
mdefine_line|#define PEN_INT_BIT&t;&t;(1&lt;&lt;7)
multiline_comment|/* Bitmask for pen up interrupt */
DECL|macro|PEN_ENA_BIT
mdefine_line|#define PEN_ENA_BIT&t;&t;(1&lt;&lt;6)
multiline_comment|/* pen up interrupt */
DECL|macro|IRQ_PEN
mdefine_line|#define IRQ_PEN&t;&t;&t;IRQ_MUX_GPIOB(7)
macro_line|#endif
multiline_comment|/* Hynix H7201 developer board specific device defines */
macro_line|#if defined (CONFIG_ARCH_H7201)
multiline_comment|/* ROM DISK SPACE */
DECL|macro|ROM_DISK_BASE
mdefine_line|#define ROM_DISK_BASE           0xc1800000
DECL|macro|ROM_DISK_START
mdefine_line|#define ROM_DISK_START          0x41800000
DECL|macro|ROM_DISK_SIZE
mdefine_line|#define ROM_DISK_SIZE           0x00700000
multiline_comment|/* SRAM DISK SPACE */
DECL|macro|SRAM_DISK_BASE
mdefine_line|#define SRAM_DISK_BASE          0xf1000000
DECL|macro|SRAM_DISK_START
mdefine_line|#define SRAM_DISK_START         0x04000000
DECL|macro|SRAM_DISK_SIZE
mdefine_line|#define SRAM_DISK_SIZE          0x00400000
macro_line|#endif
eof
