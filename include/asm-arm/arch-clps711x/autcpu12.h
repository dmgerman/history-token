multiline_comment|/*&n; * AUTCPU12 specific defines&n; *&n; * (c) 2001 Thomas Gleixner, autronix automation &lt;gleixner@autronix.de&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef __ASM_ARCH_AUTCPU12_H
DECL|macro|__ASM_ARCH_AUTCPU12_H
mdefine_line|#define __ASM_ARCH_AUTCPU12_H
multiline_comment|/*&n; * The CS8900A ethernet chip has its I/O registers wired to chip select 2&n; * (nCS2). This is the mapping for it.&n; */
DECL|macro|AUTCPU12_PHYS_CS8900A
mdefine_line|#define AUTCPU12_PHYS_CS8900A&t;&t;CS2_PHYS_BASE&t;&t;/* physical */
DECL|macro|AUTCPU12_VIRT_CS8900A
mdefine_line|#define AUTCPU12_VIRT_CS8900A&t;&t;(0xfe000000)&t;&t;/* virtual */
multiline_comment|/*&n; * The flash bank is wired to chip select 0&n; */
DECL|macro|AUTCPU12_PHYS_FLASH
mdefine_line|#define AUTCPU12_PHYS_FLASH&t;&t;CS0_PHYS_BASE&t;&t;/* physical */
multiline_comment|/* offset for device specific information structure */
DECL|macro|AUTCPU12_LCDINFO_OFFS
mdefine_line|#define AUTCPU12_LCDINFO_OFFS&t;&t;(0x00010000)&t;
multiline_comment|/*&n;* Videomemory is the internal SRAM (CS 6)&t;&n;*/
DECL|macro|AUTCPU12_PHYS_VIDEO
mdefine_line|#define AUTCPU12_PHYS_VIDEO&t;&t;CS6_PHYS_BASE
DECL|macro|AUTCPU12_VIRT_VIDEO
mdefine_line|#define AUTCPU12_VIRT_VIDEO&t;&t;(0xfd000000)
multiline_comment|/*&n;* All special IO&squot;s are tied to CS1&n;*/
DECL|macro|AUTCPU12_PHYS_CHAR_LCD
mdefine_line|#define AUTCPU12_PHYS_CHAR_LCD         &t;CS1_PHYS_BASE +0x00000000  /* physical */
DECL|macro|AUTCPU12_PHYS_NVRAM
mdefine_line|#define AUTCPU12_PHYS_NVRAM            &t;CS1_PHYS_BASE +0x02000000  /* physical */
DECL|macro|AUTCPU12_PHYS_CSAUX1
mdefine_line|#define AUTCPU12_PHYS_CSAUX1           &t;CS1_PHYS_BASE +0x04000000  /* physical */
DECL|macro|AUTCPU12_PHYS_SMC
mdefine_line|#define AUTCPU12_PHYS_SMC              &t;CS1_PHYS_BASE +0x06000000  /* physical */
DECL|macro|AUTCPU12_PHYS_CAN
mdefine_line|#define AUTCPU12_PHYS_CAN              &t;CS1_PHYS_BASE +0x08000000  /* physical */
DECL|macro|AUTCPU12_PHYS_TOUCH
mdefine_line|#define AUTCPU12_PHYS_TOUCH            &t;CS1_PHYS_BASE +0x0A000000  /* physical */
DECL|macro|AUTCPU12_PHYS_IO
mdefine_line|#define AUTCPU12_PHYS_IO               &t;CS1_PHYS_BASE +0x0C000000  /* physical */
DECL|macro|AUTCPU12_PHYS_LPT
mdefine_line|#define AUTCPU12_PHYS_LPT              &t;CS1_PHYS_BASE +0x0E000000  /* physical */
multiline_comment|/* &n;* defines for smartmedia card access &n;*/
DECL|macro|AUTCPU12_SMC_RDY
mdefine_line|#define AUTCPU12_SMC_RDY&t;&t;(1&lt;&lt;2)
DECL|macro|AUTCPU12_SMC_ALE
mdefine_line|#define AUTCPU12_SMC_ALE&t;&t;(1&lt;&lt;3)
DECL|macro|AUTCPU12_SMC_CLE
mdefine_line|#define AUTCPU12_SMC_CLE  &t;&t;(1&lt;&lt;4)
DECL|macro|AUTCPU12_SMC_PORT_OFFSET
mdefine_line|#define AUTCPU12_SMC_PORT_OFFSET&t;PBDR
DECL|macro|AUTCPU12_SMC_SELECT_OFFSET
mdefine_line|#define AUTCPU12_SMC_SELECT_OFFSET &t;0x10
multiline_comment|/*&n;* defines for lcd contrast &n;*/
DECL|macro|AUTCPU12_DPOT_PORT_OFFSET
mdefine_line|#define AUTCPU12_DPOT_PORT_OFFSET&t;PEDR
DECL|macro|AUTCPU12_DPOT_CS
mdefine_line|#define&t;AUTCPU12_DPOT_CS&t;&t;(1&lt;&lt;0)
DECL|macro|AUTCPU12_DPOT_CLK
mdefine_line|#define AUTCPU12_DPOT_CLK    &t;&t;(1&lt;&lt;1)
DECL|macro|AUTCPU12_DPOT_UD
mdefine_line|#define&t;AUTCPU12_DPOT_UD&t;&t;(1&lt;&lt;2)
macro_line|#endif
eof
