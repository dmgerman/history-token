multiline_comment|/* linux/include/asm-arm/arch-s3c2410/map.h&n; *&n; * (c) 2003 Simtec Electronics&n; *  Ben Dooks &lt;ben@simtec.co.uk&gt;&n; *&n; * S3C2410 - Memory map definitions&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * Changelog:&n; *  12-May-2003 BJD  Created file&n; *  06-Jan-2003 BJD  Linux 2.6.0 version, moved bast specifics out&n; *  10-Feb-2005 BJD  Added CAMIF definition from guillaume.gourat@nexvision.tv&n;*/
macro_line|#ifndef __ASM_ARCH_MAP_H
DECL|macro|__ASM_ARCH_MAP_H
mdefine_line|#define __ASM_ARCH_MAP_H
multiline_comment|/* we have a bit of a tight squeeze to fit all our registers from&n; * 0xF00000000 upwards, since we use all of the nGCS space in some&n; * capacity, and also need to fit the S3C2410 registers in as well...&n; *&n; * we try to ensure stuff like the IRQ registers are available for&n; * an single MOVS instruction (ie, only 8 bits of set data)&n; *&n; * Note, we are trying to remove some of these from the implementation&n; * as they are only useful to certain drivers...&n; */
DECL|macro|S3C2410_ADDR
mdefine_line|#define S3C2410_ADDR(x)&t;  (0xF0000000 + (x))
multiline_comment|/* interrupt controller is the first thing we put in, to make&n; * the assembly code for the irq detection easier&n; */
DECL|macro|S3C2410_VA_IRQ
mdefine_line|#define S3C2410_VA_IRQ&t;   S3C2410_ADDR(0x00000000)
DECL|macro|S3C2410_PA_IRQ
mdefine_line|#define S3C2410_PA_IRQ&t;   (0x4A000000)
DECL|macro|S3C2410_SZ_IRQ
mdefine_line|#define S3C2410_SZ_IRQ&t;   SZ_1M
multiline_comment|/* memory controller registers */
DECL|macro|S3C2410_VA_MEMCTRL
mdefine_line|#define S3C2410_VA_MEMCTRL S3C2410_ADDR(0x00100000)
DECL|macro|S3C2410_PA_MEMCTRL
mdefine_line|#define S3C2410_PA_MEMCTRL (0x48000000)
DECL|macro|S3C2410_SZ_MEMCTRL
mdefine_line|#define S3C2410_SZ_MEMCTRL SZ_1M
multiline_comment|/* USB host controller */
DECL|macro|S3C2410_VA_USBHOST
mdefine_line|#define S3C2410_VA_USBHOST S3C2410_ADDR(0x00200000)
DECL|macro|S3C2410_PA_USBHOST
mdefine_line|#define S3C2410_PA_USBHOST (0x49000000)
DECL|macro|S3C2410_SZ_USBHOST
mdefine_line|#define S3C2410_SZ_USBHOST SZ_1M
multiline_comment|/* DMA controller */
DECL|macro|S3C2410_VA_DMA
mdefine_line|#define S3C2410_VA_DMA&t;   S3C2410_ADDR(0x00300000)
DECL|macro|S3C2410_PA_DMA
mdefine_line|#define S3C2410_PA_DMA&t;   (0x4B000000)
DECL|macro|S3C2410_SZ_DMA
mdefine_line|#define S3C2410_SZ_DMA&t;   SZ_1M
multiline_comment|/* Clock and Power management */
DECL|macro|S3C2410_VA_CLKPWR
mdefine_line|#define S3C2410_VA_CLKPWR  S3C2410_ADDR(0x00400000)
DECL|macro|S3C2410_PA_CLKPWR
mdefine_line|#define S3C2410_PA_CLKPWR  (0x4C000000)
DECL|macro|S3C2410_SZ_CLKPWR
mdefine_line|#define S3C2410_SZ_CLKPWR  SZ_1M
multiline_comment|/* LCD controller */
DECL|macro|S3C2410_VA_LCD
mdefine_line|#define S3C2410_VA_LCD&t;   S3C2410_ADDR(0x00600000)
DECL|macro|S3C2410_PA_LCD
mdefine_line|#define S3C2410_PA_LCD&t;   (0x4D000000)
DECL|macro|S3C2410_SZ_LCD
mdefine_line|#define S3C2410_SZ_LCD&t;   SZ_1M
multiline_comment|/* NAND flash controller */
DECL|macro|S3C2410_VA_NAND
mdefine_line|#define S3C2410_VA_NAND&t;   S3C2410_ADDR(0x00700000)
DECL|macro|S3C2410_PA_NAND
mdefine_line|#define S3C2410_PA_NAND&t;   (0x4E000000)
DECL|macro|S3C2410_SZ_NAND
mdefine_line|#define S3C2410_SZ_NAND&t;   SZ_1M
multiline_comment|/* UARTs */
DECL|macro|S3C2410_VA_UART
mdefine_line|#define S3C2410_VA_UART&t;   S3C2410_ADDR(0x00800000)
DECL|macro|S3C2410_PA_UART
mdefine_line|#define S3C2410_PA_UART&t;   (0x50000000)
DECL|macro|S3C2410_SZ_UART
mdefine_line|#define S3C2410_SZ_UART&t;   SZ_1M
multiline_comment|/* Timers */
DECL|macro|S3C2410_VA_TIMER
mdefine_line|#define S3C2410_VA_TIMER   S3C2410_ADDR(0x00900000)
DECL|macro|S3C2410_PA_TIMER
mdefine_line|#define S3C2410_PA_TIMER   (0x51000000)
DECL|macro|S3C2410_SZ_TIMER
mdefine_line|#define S3C2410_SZ_TIMER   SZ_1M
multiline_comment|/* USB Device port */
DECL|macro|S3C2410_VA_USBDEV
mdefine_line|#define S3C2410_VA_USBDEV  S3C2410_ADDR(0x00A00000)
DECL|macro|S3C2410_PA_USBDEV
mdefine_line|#define S3C2410_PA_USBDEV  (0x52000000)
DECL|macro|S3C2410_SZ_USBDEV
mdefine_line|#define S3C2410_SZ_USBDEV  SZ_1M
multiline_comment|/* Watchdog */
DECL|macro|S3C2410_VA_WATCHDOG
mdefine_line|#define S3C2410_VA_WATCHDOG S3C2410_ADDR(0x00B00000)
DECL|macro|S3C2410_PA_WATCHDOG
mdefine_line|#define S3C2410_PA_WATCHDOG (0x53000000)
DECL|macro|S3C2410_SZ_WATCHDOG
mdefine_line|#define S3C2410_SZ_WATCHDOG SZ_1M
multiline_comment|/* IIC hardware controller */
DECL|macro|S3C2410_VA_IIC
mdefine_line|#define S3C2410_VA_IIC&t;   S3C2410_ADDR(0x00C00000)
DECL|macro|S3C2410_PA_IIC
mdefine_line|#define S3C2410_PA_IIC&t;   (0x54000000)
DECL|macro|S3C2410_SZ_IIC
mdefine_line|#define S3C2410_SZ_IIC&t;   SZ_1M
DECL|macro|VA_IIC_BASE
mdefine_line|#define VA_IIC_BASE&t;   (S3C2410_VA_IIC)
multiline_comment|/* IIS controller */
DECL|macro|S3C2410_VA_IIS
mdefine_line|#define S3C2410_VA_IIS&t;   S3C2410_ADDR(0x00D00000)
DECL|macro|S3C2410_PA_IIS
mdefine_line|#define S3C2410_PA_IIS&t;   (0x55000000)
DECL|macro|S3C2410_SZ_IIS
mdefine_line|#define S3C2410_SZ_IIS&t;   SZ_1M
multiline_comment|/* GPIO ports */
DECL|macro|S3C2410_VA_GPIO
mdefine_line|#define S3C2410_VA_GPIO&t;   S3C2410_ADDR(0x00E00000)
DECL|macro|S3C2410_PA_GPIO
mdefine_line|#define S3C2410_PA_GPIO&t;   (0x56000000)
DECL|macro|S3C2410_SZ_GPIO
mdefine_line|#define S3C2410_SZ_GPIO&t;   SZ_1M
multiline_comment|/* RTC */
DECL|macro|S3C2410_VA_RTC
mdefine_line|#define S3C2410_VA_RTC&t;   S3C2410_ADDR(0x00F00000)
DECL|macro|S3C2410_PA_RTC
mdefine_line|#define S3C2410_PA_RTC&t;   (0x57000000)
DECL|macro|S3C2410_SZ_RTC
mdefine_line|#define S3C2410_SZ_RTC&t;   SZ_1M
multiline_comment|/* ADC */
DECL|macro|S3C2410_VA_ADC
mdefine_line|#define S3C2410_VA_ADC&t;   S3C2410_ADDR(0x01000000)
DECL|macro|S3C2410_PA_ADC
mdefine_line|#define S3C2410_PA_ADC&t;   (0x58000000)
DECL|macro|S3C2410_SZ_ADC
mdefine_line|#define S3C2410_SZ_ADC&t;   SZ_1M
multiline_comment|/* SPI */
DECL|macro|S3C2410_VA_SPI
mdefine_line|#define S3C2410_VA_SPI&t;   S3C2410_ADDR(0x01100000)
DECL|macro|S3C2410_PA_SPI
mdefine_line|#define S3C2410_PA_SPI&t;   (0x59000000)
DECL|macro|S3C2410_SZ_SPI
mdefine_line|#define S3C2410_SZ_SPI&t;   SZ_1M
multiline_comment|/* SDI */
DECL|macro|S3C2410_VA_SDI
mdefine_line|#define S3C2410_VA_SDI&t;   S3C2410_ADDR(0x01200000)
DECL|macro|S3C2410_PA_SDI
mdefine_line|#define S3C2410_PA_SDI&t;   (0x5A000000)
DECL|macro|S3C2410_SZ_SDI
mdefine_line|#define S3C2410_SZ_SDI&t;   SZ_1M
multiline_comment|/* CAMIF */
DECL|macro|S3C2440_PA_CAMIF
mdefine_line|#define S3C2440_PA_CAMIF   (0x4F000000)
DECL|macro|S3C2440_SZ_CAMIF
mdefine_line|#define S3C2440_SZ_CAMIF   SZ_1M
multiline_comment|/* ISA style IO, for each machine to sort out mappings for, if it&n; * implements it. We reserve two 16M regions for ISA.&n; */
DECL|macro|S3C2410_VA_ISA_WORD
mdefine_line|#define S3C2410_VA_ISA_WORD  S3C2410_ADDR(0x02000000)
DECL|macro|S3C2410_VA_ISA_BYTE
mdefine_line|#define S3C2410_VA_ISA_BYTE  S3C2410_ADDR(0x03000000)
multiline_comment|/* physical addresses of all the chip-select areas */
DECL|macro|S3C2410_CS0
mdefine_line|#define S3C2410_CS0 (0x00000000)
DECL|macro|S3C2410_CS1
mdefine_line|#define S3C2410_CS1 (0x08000000)
DECL|macro|S3C2410_CS2
mdefine_line|#define S3C2410_CS2 (0x10000000)
DECL|macro|S3C2410_CS3
mdefine_line|#define S3C2410_CS3 (0x18000000)
DECL|macro|S3C2410_CS4
mdefine_line|#define S3C2410_CS4 (0x20000000)
DECL|macro|S3C2410_CS5
mdefine_line|#define S3C2410_CS5 (0x28000000)
DECL|macro|S3C2410_CS6
mdefine_line|#define S3C2410_CS6 (0x30000000)
DECL|macro|S3C2410_CS7
mdefine_line|#define S3C2410_CS7 (0x38000000)
DECL|macro|S3C2410_SDRAM_PA
mdefine_line|#define S3C2410_SDRAM_PA    (S3C2410_CS6)
macro_line|#endif /* __ASM_ARCH_MAP_H */
eof
