multiline_comment|/*&n; *  linux/include/asm-arm/arch-clps711x/hardware.h&n; *&n; *  This file contains the hardware definitions of the Prospector P720T.&n; *&n; *  Copyright (C) 2000 Deep Blue Solutions Ltd.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef __ASM_ARCH_HARDWARE_H
DECL|macro|__ASM_ARCH_HARDWARE_H
mdefine_line|#define __ASM_ARCH_HARDWARE_H
macro_line|#include &lt;linux/config.h&gt;
DECL|macro|CLPS7111_VIRT_BASE
mdefine_line|#define CLPS7111_VIRT_BASE&t;0xff000000
DECL|macro|CLPS7111_BASE
mdefine_line|#define CLPS7111_BASE&t;&t;CLPS7111_VIRT_BASE
multiline_comment|/*&n; * The physical addresses that the external chip select signals map to is&n; * dependent on the setting of the nMEDCHG signal on EP7211 and EP7212&n; * processors.  CONFIG_EP72XX_BOOT_ROM is only available if these&n; * processors are in use.&n; */
macro_line|#ifndef CONFIG_EP72XX_ROM_BOOT
DECL|macro|CS0_PHYS_BASE
mdefine_line|#define CS0_PHYS_BASE&t;&t;(0x00000000)
DECL|macro|CS1_PHYS_BASE
mdefine_line|#define CS1_PHYS_BASE&t;&t;(0x10000000)
DECL|macro|CS2_PHYS_BASE
mdefine_line|#define CS2_PHYS_BASE&t;&t;(0x20000000)
DECL|macro|CS3_PHYS_BASE
mdefine_line|#define CS3_PHYS_BASE&t;&t;(0x30000000)
DECL|macro|CS4_PHYS_BASE
mdefine_line|#define CS4_PHYS_BASE&t;&t;(0x40000000)
DECL|macro|CS5_PHYS_BASE
mdefine_line|#define CS5_PHYS_BASE&t;&t;(0x50000000)
DECL|macro|CS6_PHYS_BASE
mdefine_line|#define CS6_PHYS_BASE&t;&t;(0x60000000)
DECL|macro|CS7_PHYS_BASE
mdefine_line|#define CS7_PHYS_BASE&t;&t;(0x70000000)
macro_line|#else
DECL|macro|CS0_PHYS_BASE
mdefine_line|#define CS0_PHYS_BASE&t;&t;(0x70000000)
DECL|macro|CS1_PHYS_BASE
mdefine_line|#define CS1_PHYS_BASE&t;&t;(0x60000000)
DECL|macro|CS2_PHYS_BASE
mdefine_line|#define CS2_PHYS_BASE&t;&t;(0x50000000)
DECL|macro|CS3_PHYS_BASE
mdefine_line|#define CS3_PHYS_BASE&t;&t;(0x40000000)
DECL|macro|CS4_PHYS_BASE
mdefine_line|#define CS4_PHYS_BASE&t;&t;(0x30000000)
DECL|macro|CS5_PHYS_BASE
mdefine_line|#define CS5_PHYS_BASE&t;&t;(0x20000000)
DECL|macro|CS6_PHYS_BASE
mdefine_line|#define CS6_PHYS_BASE&t;&t;(0x10000000)
DECL|macro|CS7_PHYS_BASE
mdefine_line|#define CS7_PHYS_BASE&t;&t;(0x00000000)
macro_line|#endif
macro_line|#if defined (CONFIG_ARCH_EP7211)
DECL|macro|EP7211_VIRT_BASE
mdefine_line|#define EP7211_VIRT_BASE&t;CLPS7111_VIRT_BASE
DECL|macro|EP7211_BASE
mdefine_line|#define EP7211_BASE&t;&t;CLPS7111_VIRT_BASE
macro_line|#include &lt;asm/hardware/ep7211.h&gt;
macro_line|#elif defined (CONFIG_ARCH_EP7212)
DECL|macro|EP7212_VIRT_BASE
mdefine_line|#define EP7212_VIRT_BASE&t;CLPS7111_VIRT_BASE
DECL|macro|EP7212_BASE
mdefine_line|#define EP7212_BASE&t;&t;CLPS7111_VIRT_BASE
macro_line|#include &lt;asm/hardware/ep7212.h&gt;
macro_line|#endif
DECL|macro|SYSPLD_VIRT_BASE
mdefine_line|#define SYSPLD_VIRT_BASE&t;0xfe000000
DECL|macro|SYSPLD_BASE
mdefine_line|#define SYSPLD_BASE&t;&t;SYSPLD_VIRT_BASE
macro_line|#ifndef __ASSEMBLER__
DECL|macro|PCIO_BASE
mdefine_line|#define PCIO_BASE&t;&t;IO_BASE
macro_line|#endif
macro_line|#if  defined (CONFIG_ARCH_AUTCPU12)
DECL|macro|CS89712_VIRT_BASE
mdefine_line|#define  CS89712_VIRT_BASE&t;CLPS7111_VIRT_BASE
DECL|macro|CS89712_BASE
mdefine_line|#define  CS89712_BASE&t;&t;CLPS7111_VIRT_BASE
macro_line|#include &lt;asm/hardware/clps7111.h&gt;
macro_line|#include &lt;asm/hardware/ep7212.h&gt;
macro_line|#include &lt;asm/hardware/cs89712.h&gt;
macro_line|#endif
macro_line|#if defined (CONFIG_ARCH_CDB89712)
macro_line|#include &lt;asm/hardware/clps7111.h&gt;
macro_line|#include &lt;asm/hardware/ep7212.h&gt;
macro_line|#include &lt;asm/hardware/cs89712.h&gt;
multiline_comment|/* dynamic ioremap() areas */
DECL|macro|FLASH_START
mdefine_line|#define FLASH_START      0x00000000
DECL|macro|FLASH_SIZE
mdefine_line|#define FLASH_SIZE       0x800000
DECL|macro|FLASH_WIDTH
mdefine_line|#define FLASH_WIDTH      4
DECL|macro|SRAM_START
mdefine_line|#define SRAM_START       0x60000000
DECL|macro|SRAM_SIZE
mdefine_line|#define SRAM_SIZE        0xc000
DECL|macro|SRAM_WIDTH
mdefine_line|#define SRAM_WIDTH       4
DECL|macro|BOOTROM_START
mdefine_line|#define BOOTROM_START    0x70000000
DECL|macro|BOOTROM_SIZE
mdefine_line|#define BOOTROM_SIZE     0x80
DECL|macro|BOOTROM_WIDTH
mdefine_line|#define BOOTROM_WIDTH    4
multiline_comment|/* static cdb89712_map_io() areas */
DECL|macro|REGISTER_START
mdefine_line|#define REGISTER_START   0x80000000
DECL|macro|REGISTER_SIZE
mdefine_line|#define REGISTER_SIZE    0x4000
DECL|macro|REGISTER_BASE
mdefine_line|#define REGISTER_BASE    0xff000000
DECL|macro|ETHER_START
mdefine_line|#define ETHER_START      0x20000000
DECL|macro|ETHER_SIZE
mdefine_line|#define ETHER_SIZE       0x1000
DECL|macro|ETHER_BASE
mdefine_line|#define ETHER_BASE       0xfe000000
macro_line|#endif
macro_line|#if defined (CONFIG_ARCH_EDB7211)
multiline_comment|/*&n; * The extra 8 lines of the keyboard matrix are wired to chip select 3 (nCS3) &n; * and repeat across it. This is the mapping for it.&n; *&n; * In jumpered boot mode, nCS3 is mapped to 0x4000000, not 0x3000000. This &n; * was cause for much consternation and headscratching. This should probably&n; * be made a compile/run time kernel option.&n; */
DECL|macro|EP7211_PHYS_EXTKBD
mdefine_line|#define EP7211_PHYS_EXTKBD&t;&t;CS3_PHYS_BASE&t;/* physical */
DECL|macro|EP7211_VIRT_EXTKBD
mdefine_line|#define EP7211_VIRT_EXTKBD&t;&t;(0xfd000000)&t;/* virtual */
multiline_comment|/*&n; * The CS8900A ethernet chip has its I/O registers wired to chip select 2 &n; * (nCS2). This is the mapping for it.&n; *&n; * In jumpered boot mode, nCS2 is mapped to 0x5000000, not 0x2000000. This &n; * was cause for much consternation and headscratching. This should probably&n; * be made a compile/run time kernel option.&n; */
DECL|macro|EP7211_PHYS_CS8900A
mdefine_line|#define EP7211_PHYS_CS8900A&t;&t;CS2_PHYS_BASE&t;/* physical */
DECL|macro|EP7211_VIRT_CS8900A
mdefine_line|#define EP7211_VIRT_CS8900A&t;&t;(0xfc000000)&t;/* virtual */
multiline_comment|/*&n; * The two flash banks are wired to chip selects 0 and 1. This is the mapping&n; * for them.&n; *&n; * nCS0 and nCS1 are at 0x70000000 and 0x60000000, respectively, when running&n; * in jumpered boot mode.&n; */
DECL|macro|EP7211_PHYS_FLASH1
mdefine_line|#define EP7211_PHYS_FLASH1&t;&t;CS0_PHYS_BASE&t;/* physical */
DECL|macro|EP7211_PHYS_FLASH2
mdefine_line|#define EP7211_PHYS_FLASH2&t;&t;CS1_PHYS_BASE&t;/* physical */
DECL|macro|EP7211_VIRT_FLASH1
mdefine_line|#define EP7211_VIRT_FLASH1&t;&t;(0xfa000000)&t;/* virtual */
DECL|macro|EP7211_VIRT_FLASH2
mdefine_line|#define EP7211_VIRT_FLASH2&t;&t;(0xfb000000)&t;/* virtual */
macro_line|#endif /* CONFIG_ARCH_EDB7211 */
multiline_comment|/*&n; * Relevant bits in port D, which controls power to the various parts of&n; * the LCD on the EDB7211.&n; */
DECL|macro|EDB_PD1_LCD_DC_DC_EN
mdefine_line|#define EDB_PD1_LCD_DC_DC_EN&t;(1&lt;&lt;1)
DECL|macro|EDB_PD2_LCDEN
mdefine_line|#define EDB_PD2_LCDEN&t;&t;(1&lt;&lt;2)
DECL|macro|EDB_PD3_LCDBL
mdefine_line|#define EDB_PD3_LCDBL&t;&t;(1&lt;&lt;3)
macro_line|#endif
eof
