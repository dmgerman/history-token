multiline_comment|/*&n; *  linux/include/asm-arm/arch-clps711x/syspld.h&n; *&n; *  System Control PLD register definitions.&n; *&n; *  Copyright (C) 2000 Deep Blue Solutions Ltd.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef __ASM_ARCH_SYSPLD_H
DECL|macro|__ASM_ARCH_SYSPLD_H
mdefine_line|#define __ASM_ARCH_SYSPLD_H
DECL|macro|SYSPLD_PHYS_BASE
mdefine_line|#define SYSPLD_PHYS_BASE&t;(0x10000000)
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;asm/types.h&gt;
DECL|macro|SYSPLD_REG
mdefine_line|#define SYSPLD_REG(type,off)&t;(*(volatile type *)(SYSPLD_BASE + off))
macro_line|#else
DECL|macro|SYSPLD_REG
mdefine_line|#define SYSPLD_REG(type,off)&t;(off)
macro_line|#endif
DECL|macro|PLD_INT
mdefine_line|#define PLD_INT&t;&t;SYSPLD_REG(u32, 0x000000)
DECL|macro|PLD_INT_PENIRQ
mdefine_line|#define PLD_INT_PENIRQ&t;&t;(1 &lt;&lt; 5)
DECL|macro|PLD_INT_UCB_IRQ
mdefine_line|#define PLD_INT_UCB_IRQ&t;&t;(1 &lt;&lt; 1)
DECL|macro|PLD_INT_KBD_ATN
mdefine_line|#define PLD_INT_KBD_ATN&t;&t;(1 &lt;&lt; 0)&t;/* EINT1 */
DECL|macro|PLD_PWR
mdefine_line|#define PLD_PWR&t;&t;SYSPLD_REG(u32, 0x000004)
DECL|macro|PLD_PWR_EXT
mdefine_line|#define PLD_PWR_EXT&t;&t;(1 &lt;&lt; 5)
DECL|macro|PLD_PWR_MODE
mdefine_line|#define PLD_PWR_MODE&t;&t;(1 &lt;&lt; 4)&t;/* 1 = PWM, 0 = PFM */
DECL|macro|PLD_S4_ON
mdefine_line|#define PLD_S4_ON&t;&t;(1 &lt;&lt; 3)&t;/* LCD bias voltage enable */
DECL|macro|PLD_S3_ON
mdefine_line|#define PLD_S3_ON&t;&t;(1 &lt;&lt; 2)&t;/* LCD backlight enable */
DECL|macro|PLD_S2_ON
mdefine_line|#define PLD_S2_ON&t;&t;(1 &lt;&lt; 1)&t;/* LCD 3V3 supply enable */
DECL|macro|PLD_S1_ON
mdefine_line|#define PLD_S1_ON&t;&t;(1 &lt;&lt; 0)&t;/* LCD 3V supply enable */
DECL|macro|PLD_KBD
mdefine_line|#define PLD_KBD&t;&t;SYSPLD_REG(u32, 0x000008)
DECL|macro|PLD_KBD_WAKE
mdefine_line|#define PLD_KBD_WAKE&t;&t;(1 &lt;&lt; 1)
DECL|macro|PLD_KBD_EN
mdefine_line|#define PLD_KBD_EN&t;&t;(1 &lt;&lt; 0)
DECL|macro|PLD_SPI
mdefine_line|#define PLD_SPI&t;&t;SYSPLD_REG(u32, 0x00000c)
DECL|macro|PLD_SPI_EN
mdefine_line|#define PLD_SPI_EN&t;&t;(1 &lt;&lt; 0)
DECL|macro|PLD_IO
mdefine_line|#define PLD_IO&t;&t;SYSPLD_REG(u32, 0x000010)
DECL|macro|PLD_IO_BOOTSEL
mdefine_line|#define PLD_IO_BOOTSEL&t;&t;(1 &lt;&lt; 6)&t;/* boot sel switch */
DECL|macro|PLD_IO_USER
mdefine_line|#define PLD_IO_USER&t;&t;(1 &lt;&lt; 5)&t;/* user defined switch */
DECL|macro|PLD_IO_LED3
mdefine_line|#define PLD_IO_LED3&t;&t;(1 &lt;&lt; 4)
DECL|macro|PLD_IO_LED2
mdefine_line|#define PLD_IO_LED2&t;&t;(1 &lt;&lt; 3)
DECL|macro|PLD_IO_LED1
mdefine_line|#define PLD_IO_LED1&t;&t;(1 &lt;&lt; 2)
DECL|macro|PLD_IO_LED0
mdefine_line|#define PLD_IO_LED0&t;&t;(1 &lt;&lt; 1)
DECL|macro|PLD_IO_LEDEN
mdefine_line|#define PLD_IO_LEDEN&t;&t;(1 &lt;&lt; 0)
DECL|macro|PLD_IRDA
mdefine_line|#define PLD_IRDA&t;SYSPLD_REG(u32, 0x000014)
DECL|macro|PLD_IRDA_EN
mdefine_line|#define PLD_IRDA_EN&t;&t;(1 &lt;&lt; 0)
DECL|macro|PLD_COM2
mdefine_line|#define PLD_COM2&t;SYSPLD_REG(u32, 0x000018)
DECL|macro|PLD_COM2_EN
mdefine_line|#define PLD_COM2_EN&t;&t;(1 &lt;&lt; 0)
DECL|macro|PLD_COM1
mdefine_line|#define PLD_COM1&t;SYSPLD_REG(u32, 0x00001c)
DECL|macro|PLD_COM1_EN
mdefine_line|#define PLD_COM1_EN&t;&t;(1 &lt;&lt; 0)
DECL|macro|PLD_AUD
mdefine_line|#define PLD_AUD&t;&t;SYSPLD_REG(u32, 0x000020)
DECL|macro|PLD_AUD_DIV1
mdefine_line|#define PLD_AUD_DIV1&t;&t;(1 &lt;&lt; 6)
DECL|macro|PLD_AUD_DIV0
mdefine_line|#define PLD_AUD_DIV0&t;&t;(1 &lt;&lt; 5)
DECL|macro|PLD_AUD_CLK_SEL1
mdefine_line|#define PLD_AUD_CLK_SEL1&t;(1 &lt;&lt; 4)
DECL|macro|PLD_AUD_CLK_SEL0
mdefine_line|#define PLD_AUD_CLK_SEL0&t;(1 &lt;&lt; 3)
DECL|macro|PLD_AUD_MIC_PWR
mdefine_line|#define PLD_AUD_MIC_PWR&t;&t;(1 &lt;&lt; 2)
DECL|macro|PLD_AUD_MIC_GAIN
mdefine_line|#define PLD_AUD_MIC_GAIN&t;(1 &lt;&lt; 1)
DECL|macro|PLD_AUD_CODEC_EN
mdefine_line|#define PLD_AUD_CODEC_EN&t;(1 &lt;&lt; 0)
DECL|macro|PLD_CF
mdefine_line|#define PLD_CF&t;&t;SYSPLD_REG(u32, 0x000024)
DECL|macro|PLD_CF2_SLEEP
mdefine_line|#define PLD_CF2_SLEEP&t;&t;(1 &lt;&lt; 5)
DECL|macro|PLD_CF1_SLEEP
mdefine_line|#define PLD_CF1_SLEEP&t;&t;(1 &lt;&lt; 4)
DECL|macro|PLD_CF2_nPDREQ
mdefine_line|#define PLD_CF2_nPDREQ&t;&t;(1 &lt;&lt; 3)
DECL|macro|PLD_CF1_nPDREQ
mdefine_line|#define PLD_CF1_nPDREQ&t;&t;(1 &lt;&lt; 2)
DECL|macro|PLD_CF2_nIRQ
mdefine_line|#define PLD_CF2_nIRQ&t;&t;(1 &lt;&lt; 1)
DECL|macro|PLD_CF1_nIRQ
mdefine_line|#define PLD_CF1_nIRQ&t;&t;(1 &lt;&lt; 0)
DECL|macro|PLD_SDC
mdefine_line|#define PLD_SDC&t;&t;SYSPLD_REG(u32, 0x000028)
DECL|macro|PLD_SDC_INT_EN
mdefine_line|#define PLD_SDC_INT_EN&t;&t;(1 &lt;&lt; 2)
DECL|macro|PLD_SDC_WP
mdefine_line|#define PLD_SDC_WP&t;&t;(1 &lt;&lt; 1)
DECL|macro|PLD_SDC_CD
mdefine_line|#define PLD_SDC_CD&t;&t;(1 &lt;&lt; 0)
DECL|macro|PLD_FPGA
mdefine_line|#define PLD_FPGA&t;SYSPLD_REG(u32, 0x00002c)
DECL|macro|PLD_CODEC
mdefine_line|#define PLD_CODEC&t;SYSPLD_REG(u32, 0x400000)
DECL|macro|PLD_CODEC_IRQ3
mdefine_line|#define PLD_CODEC_IRQ3&t;&t;(1 &lt;&lt; 4)
DECL|macro|PLD_CODEC_IRQ2
mdefine_line|#define PLD_CODEC_IRQ2&t;&t;(1 &lt;&lt; 3)
DECL|macro|PLD_CODEC_IRQ1
mdefine_line|#define PLD_CODEC_IRQ1&t;&t;(1 &lt;&lt; 2)
DECL|macro|PLD_CODEC_EN
mdefine_line|#define PLD_CODEC_EN&t;&t;(1 &lt;&lt; 0)
DECL|macro|PLD_BRITE
mdefine_line|#define PLD_BRITE&t;SYSPLD_REG(u32, 0x400004)
DECL|macro|PLD_BRITE_UP
mdefine_line|#define PLD_BRITE_UP&t;&t;(1 &lt;&lt; 1)
DECL|macro|PLD_BRITE_DN
mdefine_line|#define PLD_BRITE_DN&t;&t;(1 &lt;&lt; 0)
DECL|macro|PLD_LCDEN
mdefine_line|#define PLD_LCDEN&t;SYSPLD_REG(u32, 0x400008)
DECL|macro|PLD_LCDEN_EN
mdefine_line|#define PLD_LCDEN_EN&t;&t;(1 &lt;&lt; 0)
DECL|macro|PLD_ID
mdefine_line|#define PLD_ID&t;&t;SYSPLD_REG(u32, 0x40000c)
DECL|macro|PLD_TCH
mdefine_line|#define PLD_TCH&t;&t;SYSPLD_REG(u32, 0x400010)
DECL|macro|PLD_TCH_PENIRQ
mdefine_line|#define PLD_TCH_PENIRQ&t;&t;(1 &lt;&lt; 1)
DECL|macro|PLD_TCH_EN
mdefine_line|#define PLD_TCH_EN&t;&t;(1 &lt;&lt; 0)
DECL|macro|PLD_GPIO
mdefine_line|#define PLD_GPIO&t;SYSPLD_REG(u32, 0x400014)
DECL|macro|PLD_GPIO2
mdefine_line|#define PLD_GPIO2&t;&t;(1 &lt;&lt; 2)
DECL|macro|PLD_GPIO1
mdefine_line|#define PLD_GPIO1&t;&t;(1 &lt;&lt; 1)
DECL|macro|PLD_GPIO0
mdefine_line|#define PLD_GPIO0&t;&t;(1 &lt;&lt; 0)
macro_line|#endif
eof
