multiline_comment|/* include/asm-arm/arch-lh7a40x/constants.h&n; *&n; *  Copyright (C) 2004 Coastal Environmental Systems&n; *  Copyright (C) 2004 Logic Product Development&n; *&n; *  This program is free software; you can redistribute it and/or&n; *  modify it under the terms of the GNU General Public License&n; *  version 2 as published by the Free Software Foundation.&n; *&n; */
macro_line|#ifndef __ASM_ARCH_CONSTANTS_H
DECL|macro|__ASM_ARCH_CONSTANTS_H
mdefine_line|#define __ASM_ARCH_CONSTANTS_H
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/* Addressing constants */
multiline_comment|/* SoC CPU IO addressing */
DECL|macro|IO_PHYS
mdefine_line|#define IO_PHYS&t;&t;&t;(0x80000000)
DECL|macro|IO_VIRT
mdefine_line|#define IO_VIRT&t;&t;&t;(0xf8000000)
DECL|macro|IO_SIZE
mdefine_line|#define IO_SIZE&t;&t;&t;(0x0000B000)
macro_line|#ifdef CONFIG_MACH_KEV7A400
DECL|macro|CPLD_PHYS
macro_line|# define CPLD_PHYS&t;&t;(0x20000000)
DECL|macro|CPLD_VIRT
macro_line|# define CPLD_VIRT&t;&t;(0xf2000000)
DECL|macro|CPLD_SIZE
macro_line|# define CPLD_SIZE&t;&t;PAGE_SIZE
macro_line|#endif
macro_line|#if defined (CONFIG_MACH_LPD7A400) || defined (CONFIG_MACH_LPD7A404)
DECL|macro|IOBARRIER_PHYS
macro_line|# define IOBARRIER_PHYS&t;&t;0xc0000000 /* Start of SDRAM */
multiline_comment|/*# define IOBARRIER_PHYS&t;&t;0x00000000 */
multiline_comment|/* Start of flash */
DECL|macro|IOBARRIER_VIRT
macro_line|# define IOBARRIER_VIRT&t;&t;0xf0000000
DECL|macro|IOBARRIER_SIZE
macro_line|# define IOBARRIER_SIZE&t;&t;PAGE_SIZE
DECL|macro|CF_PHYS
macro_line|# define CF_PHYS&t;&t;0x60200000
DECL|macro|CF_VIRT
macro_line|# define CF_VIRT&t;&t;0xf6020000
DECL|macro|CF_SIZE
macro_line|# define CF_SIZE&t;&t;(8*1024)
multiline_comment|/* The IO mappings for the LPD CPLD are, unfortunately, sparse.  */
DECL|macro|CPLDX_PHYS
macro_line|# define CPLDX_PHYS(x)&t;&t;(0x70000000 | ((x) &lt;&lt; 20))
DECL|macro|CPLDX_VIRT
macro_line|# define CPLDX_VIRT(x)&t;&t;(0xf7000000 | ((x) &lt;&lt; 16))
DECL|macro|CPLD00_PHYS
macro_line|# define CPLD00_PHYS&t;&t;CPLDX_PHYS (0x00) /* Wired LAN */
DECL|macro|CPLD00_VIRT
macro_line|# define CPLD00_VIRT&t;&t;CPLDX_VIRT (0x00)
DECL|macro|CPLD00_SIZE
macro_line|# define CPLD00_SIZE&t;&t;PAGE_SIZE
DECL|macro|CPLD02_PHYS
macro_line|# define CPLD02_PHYS&t;&t;CPLDX_PHYS (0x02)
DECL|macro|CPLD02_VIRT
macro_line|# define CPLD02_VIRT&t;&t;CPLDX_VIRT (0x02)
DECL|macro|CPLD02_SIZE
macro_line|# define CPLD02_SIZE&t;&t;PAGE_SIZE
DECL|macro|CPLD06_PHYS
macro_line|# define CPLD06_PHYS&t;&t;CPLDX_PHYS (0x06)
DECL|macro|CPLD06_VIRT
macro_line|# define CPLD06_VIRT&t;&t;CPLDX_VIRT (0x06)
DECL|macro|CPLD06_SIZE
macro_line|# define CPLD06_SIZE&t;&t;PAGE_SIZE
DECL|macro|CPLD08_PHYS
macro_line|# define CPLD08_PHYS&t;&t;CPLDX_PHYS (0x08)
DECL|macro|CPLD08_VIRT
macro_line|# define CPLD08_VIRT&t;&t;CPLDX_VIRT (0x08)
DECL|macro|CPLD08_SIZE
macro_line|# define CPLD08_SIZE&t;&t;PAGE_SIZE
DECL|macro|CPLD0C_PHYS
macro_line|# define CPLD0C_PHYS&t;&t;CPLDX_PHYS (0x0c)
DECL|macro|CPLD0C_VIRT
macro_line|# define CPLD0C_VIRT&t;&t;CPLDX_VIRT (0x0c)
DECL|macro|CPLD0C_SIZE
macro_line|# define CPLD0C_SIZE&t;&t;PAGE_SIZE
DECL|macro|CPLD0E_PHYS
macro_line|# define CPLD0E_PHYS&t;&t;CPLDX_PHYS (0x0e)
DECL|macro|CPLD0E_VIRT
macro_line|# define CPLD0E_VIRT&t;&t;CPLDX_VIRT (0x0e)
DECL|macro|CPLD0E_SIZE
macro_line|# define CPLD0E_SIZE&t;&t;PAGE_SIZE
DECL|macro|CPLD10_PHYS
macro_line|# define CPLD10_PHYS&t;&t;CPLDX_PHYS (0x10)
DECL|macro|CPLD10_VIRT
macro_line|# define CPLD10_VIRT&t;&t;CPLDX_VIRT (0x10)
DECL|macro|CPLD10_SIZE
macro_line|# define CPLD10_SIZE&t;&t;PAGE_SIZE
DECL|macro|CPLD12_PHYS
macro_line|# define CPLD12_PHYS&t;&t;CPLDX_PHYS (0x12)
DECL|macro|CPLD12_VIRT
macro_line|# define CPLD12_VIRT&t;&t;CPLDX_VIRT (0x12)
DECL|macro|CPLD12_SIZE
macro_line|# define CPLD12_SIZE&t;&t;PAGE_SIZE
DECL|macro|CPLD14_PHYS
macro_line|# define CPLD14_PHYS&t;&t;CPLDX_PHYS (0x14)
DECL|macro|CPLD14_VIRT
macro_line|# define CPLD14_VIRT&t;&t;CPLDX_VIRT (0x14)
DECL|macro|CPLD14_SIZE
macro_line|# define CPLD14_SIZE&t;&t;PAGE_SIZE
DECL|macro|CPLD16_PHYS
macro_line|# define CPLD16_PHYS&t;&t;CPLDX_PHYS (0x16)
DECL|macro|CPLD16_VIRT
macro_line|# define CPLD16_VIRT&t;&t;CPLDX_VIRT (0x16)
DECL|macro|CPLD16_SIZE
macro_line|# define CPLD16_SIZE&t;&t;PAGE_SIZE
DECL|macro|CPLD18_PHYS
macro_line|# define CPLD18_PHYS&t;&t;CPLDX_PHYS (0x18)
DECL|macro|CPLD18_VIRT
macro_line|# define CPLD18_VIRT&t;&t;CPLDX_VIRT (0x18)
DECL|macro|CPLD18_SIZE
macro_line|# define CPLD18_SIZE&t;&t;PAGE_SIZE
DECL|macro|CPLD1A_PHYS
macro_line|# define CPLD1A_PHYS&t;&t;CPLDX_PHYS (0x1a)
DECL|macro|CPLD1A_VIRT
macro_line|# define CPLD1A_VIRT&t;&t;CPLDX_VIRT (0x1a)
DECL|macro|CPLD1A_SIZE
macro_line|# define CPLD1A_SIZE&t;&t;PAGE_SIZE
macro_line|#endif
multiline_comment|/* Timing constants */
DECL|macro|XTAL_IN
mdefine_line|#define&t;XTAL_IN&t;&t;&t;14745600&t;/* 14.7456 MHz crystal */
DECL|macro|PLL_CLOCK
mdefine_line|#define PLL_CLOCK&t;&t;(XTAL_IN * 21)&t;/* 309 MHz PLL clock */
DECL|macro|MAX_HCLK_KHZ
mdefine_line|#define MAX_HCLK_KHZ&t;&t;100000&t;&t;/* HCLK max limit ~100MHz */
macro_line|#endif /* __ASM_ARCH_CONSTANTS_H */
eof
