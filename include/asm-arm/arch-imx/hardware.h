multiline_comment|/*&n; *  linux/include/asm-arm/arch-imx/hardware.h&n; *&n; *  Copyright (C) 1999 ARM Limited.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef __ASM_ARCH_HARDWARE_H
DECL|macro|__ASM_ARCH_HARDWARE_H
mdefine_line|#define __ASM_ARCH_HARDWARE_H
macro_line|#include &lt;asm/sizes.h&gt;
macro_line|#include &quot;imx-regs.h&quot;
macro_line|#ifndef __ASSEMBLY__
DECL|macro|__REG
macro_line|# define __REG(x)&t;(*((volatile u32 *)IO_ADDRESS(x)))
DECL|macro|__REG2
macro_line|# define __REG2(x,y)        (*(volatile u32 *)((u32)&amp;__REG(x) + (y)))
macro_line|#endif
multiline_comment|/*&n; * Memory map&n; */
DECL|macro|IMX_IO_PHYS
mdefine_line|#define IMX_IO_PHYS&t;&t;0x00200000
DECL|macro|IMX_IO_SIZE
mdefine_line|#define IMX_IO_SIZE&t;&t;0x00100000
DECL|macro|IMX_IO_BASE
mdefine_line|#define IMX_IO_BASE&t;&t;0xe0000000
DECL|macro|IMX_CS0_PHYS
mdefine_line|#define IMX_CS0_PHYS&t;&t;0x10000000
DECL|macro|IMX_CS0_SIZE
mdefine_line|#define IMX_CS0_SIZE&t;&t;0x02000000
DECL|macro|IMX_CS0_VIRT
mdefine_line|#define IMX_CS0_VIRT&t;&t;0xe8000000
DECL|macro|IMX_CS1_PHYS
mdefine_line|#define IMX_CS1_PHYS&t;&t;0x12000000
DECL|macro|IMX_CS1_SIZE
mdefine_line|#define IMX_CS1_SIZE&t;&t;0x01000000
DECL|macro|IMX_CS1_VIRT
mdefine_line|#define IMX_CS1_VIRT&t;&t;0xea000000
DECL|macro|IMX_CS2_PHYS
mdefine_line|#define IMX_CS2_PHYS&t;&t;0x13000000
DECL|macro|IMX_CS2_SIZE
mdefine_line|#define IMX_CS2_SIZE&t;&t;0x01000000
DECL|macro|IMX_CS2_VIRT
mdefine_line|#define IMX_CS2_VIRT&t;&t;0xeb000000
DECL|macro|IMX_CS3_PHYS
mdefine_line|#define IMX_CS3_PHYS&t;&t;0x14000000
DECL|macro|IMX_CS3_SIZE
mdefine_line|#define IMX_CS3_SIZE&t;&t;0x01000000
DECL|macro|IMX_CS3_VIRT
mdefine_line|#define IMX_CS3_VIRT&t;&t;0xec000000
DECL|macro|IMX_CS4_PHYS
mdefine_line|#define IMX_CS4_PHYS&t;&t;0x15000000
DECL|macro|IMX_CS4_SIZE
mdefine_line|#define IMX_CS4_SIZE&t;&t;0x01000000
DECL|macro|IMX_CS4_VIRT
mdefine_line|#define IMX_CS4_VIRT&t;&t;0xed000000
DECL|macro|IMX_CS5_PHYS
mdefine_line|#define IMX_CS5_PHYS&t;&t;0x16000000
DECL|macro|IMX_CS5_SIZE
mdefine_line|#define IMX_CS5_SIZE&t;&t;0x01000000
DECL|macro|IMX_CS5_VIRT
mdefine_line|#define IMX_CS5_VIRT&t;&t;0xee000000
DECL|macro|IMX_FB_VIRT
mdefine_line|#define IMX_FB_VIRT&t;&t;0xF1000000
DECL|macro|IMX_FB_SIZE
mdefine_line|#define IMX_FB_SIZE&t;&t;(256*1024)
multiline_comment|/* macro to get at IO space when running virtually */
DECL|macro|IO_ADDRESS
mdefine_line|#define IO_ADDRESS(x) ((x) | IMX_IO_BASE)
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/*&n; * Handy routine to set GPIO functions&n; */
r_extern
r_void
id|imx_gpio_mode
c_func
(paren
r_int
id|gpio_mode
)paren
suffix:semicolon
multiline_comment|/* get frequencies in Hz */
r_extern
r_int
r_int
id|imx_get_system_clk
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_int
id|imx_get_mcu_clk
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_int
id|imx_get_perclk1
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* UART[12], Timer[12], PWM */
r_extern
r_int
r_int
id|imx_get_perclk2
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* LCD, SD, SPI[12]         */
r_extern
r_int
r_int
id|imx_get_perclk3
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* SSI                      */
r_extern
r_int
r_int
id|imx_get_hclk
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* SDRAM, CSI, Memory Stick,*/
multiline_comment|/* I2C, DMA                 */
macro_line|#endif
DECL|macro|MAXIRQNUM
mdefine_line|#define MAXIRQNUM                       62
DECL|macro|MAXFIQNUM
mdefine_line|#define MAXFIQNUM                       62
DECL|macro|MAXSWINUM
mdefine_line|#define MAXSWINUM                       62
multiline_comment|/*&n; * Use SDRAM for memory&n; */
DECL|macro|MEM_SIZE
mdefine_line|#define MEM_SIZE&t;&t;0x01000000
macro_line|#ifdef CONFIG_ARCH_MX1ADS
macro_line|#include &quot;mx1ads.h&quot;
macro_line|#endif
macro_line|#endif
eof
