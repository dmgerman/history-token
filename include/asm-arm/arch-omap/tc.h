multiline_comment|/*&n; * linux/include/asm-arm/arch-omap/tc.h&n; *&n; * OMAP Traffic Controller&n; *&n; * Copyright (C) 2004 Nokia Corporation&n; * Author: Imre Deak &lt;imre.deak@nokia.com&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2 of the License, or (at your&n; * option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n; * General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write to the Free Software Foundation, Inc.,&n; * 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.&n; */
macro_line|#ifndef __ASM_ARCH_TC_H
DECL|macro|__ASM_ARCH_TC_H
mdefine_line|#define __ASM_ARCH_TC_H
DECL|macro|TCMIF_BASE
mdefine_line|#define TCMIF_BASE&t;&t;0xfffecc00
DECL|macro|OMAP_TC_OCPT1_PRIOR
mdefine_line|#define OMAP_TC_OCPT1_PRIOR&t;(TCMIF_BASE + 0x00)
DECL|macro|OMAP_TC_EMIFS_PRIOR
mdefine_line|#define OMAP_TC_EMIFS_PRIOR&t;(TCMIF_BASE + 0x04)
DECL|macro|OMAP_TC_EMIFF_PRIOR
mdefine_line|#define OMAP_TC_EMIFF_PRIOR&t;(TCMIF_BASE + 0x08)
DECL|macro|EMIFS_CONFIG
mdefine_line|#define EMIFS_CONFIG&t;&t;(TCMIF_BASE + 0x0c)
DECL|macro|EMIFS_CS0_CONFIG
mdefine_line|#define EMIFS_CS0_CONFIG&t;(TCMIF_BASE + 0x10)
DECL|macro|EMIFS_CS1_CONFIG
mdefine_line|#define EMIFS_CS1_CONFIG&t;(TCMIF_BASE + 0x14)
DECL|macro|EMIFS_CS2_CONFIG
mdefine_line|#define EMIFS_CS2_CONFIG&t;(TCMIF_BASE + 0x18)
DECL|macro|EMIFS_CS3_CONFIG
mdefine_line|#define EMIFS_CS3_CONFIG&t;(TCMIF_BASE + 0x1c)
DECL|macro|EMIFF_SDRAM_CONFIG
mdefine_line|#define EMIFF_SDRAM_CONFIG&t;(TCMIF_BASE + 0x20)
DECL|macro|EMIFF_MRS
mdefine_line|#define EMIFF_MRS&t;&t;(TCMIF_BASE + 0x24)
DECL|macro|TC_TIMEOUT1
mdefine_line|#define TC_TIMEOUT1&t;&t;(TCMIF_BASE + 0x28)
DECL|macro|TC_TIMEOUT2
mdefine_line|#define TC_TIMEOUT2&t;&t;(TCMIF_BASE + 0x2c)
DECL|macro|TC_TIMEOUT3
mdefine_line|#define TC_TIMEOUT3&t;&t;(TCMIF_BASE + 0x30)
DECL|macro|TC_ENDIANISM
mdefine_line|#define TC_ENDIANISM&t;&t;(TCMIF_BASE + 0x34)
DECL|macro|EMIFF_SDRAM_CONFIG_2
mdefine_line|#define EMIFF_SDRAM_CONFIG_2&t;(TCMIF_BASE + 0x3c)
DECL|macro|EMIF_CFG_DYNAMIC_WS
mdefine_line|#define EMIF_CFG_DYNAMIC_WS&t;(TCMIF_BASE + 0x40)
DECL|macro|EMIFS_ACS0
mdefine_line|#define EMIFS_ACS0&t;&t;(TCMIF_BASE + 0x50)
DECL|macro|EMIFS_ACS1
mdefine_line|#define EMIFS_ACS1&t;&t;(TCMIF_BASE + 0x54)
DECL|macro|EMIFS_ACS2
mdefine_line|#define EMIFS_ACS2&t;&t;(TCMIF_BASE + 0x58)
DECL|macro|EMIFS_ACS3
mdefine_line|#define EMIFS_ACS3&t;&t;(TCMIF_BASE + 0x5c)
DECL|macro|OMAP_TC_OCPT2_PRIOR
mdefine_line|#define OMAP_TC_OCPT2_PRIOR&t;(TCMIF_BASE + 0xd0)
multiline_comment|/* external EMIFS chipselect regions */
DECL|macro|OMAP_CS0_PHYS
mdefine_line|#define&t;OMAP_CS0_PHYS&t;&t;0x00000000
DECL|macro|OMAP_CS0_SIZE
mdefine_line|#define&t;OMAP_CS0_SIZE&t;&t;SZ_64M
DECL|macro|OMAP_CS1_PHYS
mdefine_line|#define&t;OMAP_CS1_PHYS&t;&t;0x04000000
DECL|macro|OMAP_CS1_SIZE
mdefine_line|#define&t;OMAP_CS1_SIZE&t;&t;SZ_64M
DECL|macro|OMAP_CS1A_PHYS
mdefine_line|#define&t;OMAP_CS1A_PHYS&t;&t;OMAP_CS1_PHYS
DECL|macro|OMAP_CS1A_SIZE
mdefine_line|#define&t;OMAP_CS1A_SIZE&t;&t;SZ_32M
DECL|macro|OMAP_CS1B_PHYS
mdefine_line|#define&t;OMAP_CS1B_PHYS&t;&t;(OMAP_CS1A_PHYS + OMAP_CS1A_SIZE)
DECL|macro|OMAP_CS1B_SIZE
mdefine_line|#define&t;OMAP_CS1B_SIZE&t;&t;SZ_32M
DECL|macro|OMAP_CS2_PHYS
mdefine_line|#define&t;OMAP_CS2_PHYS&t;&t;0x08000000
DECL|macro|OMAP_CS2_SIZE
mdefine_line|#define&t;OMAP_CS2_SIZE&t;&t;SZ_64M
DECL|macro|OMAP_CS2A_PHYS
mdefine_line|#define&t;OMAP_CS2A_PHYS&t;&t;OMAP_CS2_PHYS
DECL|macro|OMAP_CS2A_SIZE
mdefine_line|#define&t;OMAP_CS2A_SIZE&t;&t;SZ_32M
DECL|macro|OMAP_CS2B_PHYS
mdefine_line|#define&t;OMAP_CS2B_PHYS&t;&t;(OMAP_CS2A_PHYS + OMAP_CS2A_SIZE)
DECL|macro|OMAP_CS2B_SIZE
mdefine_line|#define&t;OMAP_CS2B_SIZE&t;&t;SZ_32M
DECL|macro|OMAP_CS3_PHYS
mdefine_line|#define&t;OMAP_CS3_PHYS&t;&t;0x0c000000
DECL|macro|OMAP_CS3_SIZE
mdefine_line|#define&t;OMAP_CS3_SIZE&t;&t;SZ_64M
macro_line|#ifndef&t;__ASSEMBLER__
multiline_comment|/* EMIF Slow Interface Configuration Register */
DECL|macro|OMAP_EMIFS_CONFIG_REG
mdefine_line|#define&t;OMAP_EMIFS_CONFIG_REG&t;__REG32(EMIFS_CONFIG)
DECL|macro|OMAP_EMIFS_CONFIG_FR
mdefine_line|#define OMAP_EMIFS_CONFIG_FR&t;&t;(1 &lt;&lt; 4)
DECL|macro|OMAP_EMIFS_CONFIG_PDE
mdefine_line|#define OMAP_EMIFS_CONFIG_PDE&t;&t;(1 &lt;&lt; 3)
DECL|macro|OMAP_EMIFS_CONFIG_PWD_EN
mdefine_line|#define OMAP_EMIFS_CONFIG_PWD_EN&t;(1 &lt;&lt; 2)
DECL|macro|OMAP_EMIFS_CONFIG_BM
mdefine_line|#define OMAP_EMIFS_CONFIG_BM&t;&t;(1 &lt;&lt; 1)
DECL|macro|OMAP_EMIFS_CONFIG_WP
mdefine_line|#define OMAP_EMIFS_CONFIG_WP&t;&t;(1 &lt;&lt; 0)
DECL|macro|EMIFS_CCS
mdefine_line|#define EMIFS_CCS(n)&t;&t;__REG32(EMIFS_CS0_CONFIG + (4 * (n)))
DECL|macro|EMIFS_ACS
mdefine_line|#define EMIFS_ACS(n)&t;&t;__REG32(EMIFS_ACS0 + (4 * (n)))
multiline_comment|/* Almost all documentation for chip and board memory maps assumes&n; * BM is clear.  Most devel boards have a switch to control booting&n; * from NOR flash (using external chipselect 3) rather than mask ROM,&n; * which uses BM to interchange the physical CS0 and CS3 addresses.&n; */
DECL|function|omap_cs0_phys
r_static
r_inline
id|u32
id|omap_cs0_phys
c_func
(paren
r_void
)paren
(brace
r_return
(paren
id|OMAP_EMIFS_CONFIG_REG
op_amp
id|OMAP_EMIFS_CONFIG_BM
)paren
ques
c_cond
id|OMAP_CS3_PHYS
suffix:colon
l_int|0
suffix:semicolon
)brace
DECL|function|omap_cs3_phys
r_static
r_inline
id|u32
id|omap_cs3_phys
c_func
(paren
r_void
)paren
(brace
r_return
(paren
id|OMAP_EMIFS_CONFIG_REG
op_amp
id|OMAP_EMIFS_CONFIG_BM
)paren
ques
c_cond
l_int|0
suffix:colon
id|OMAP_CS3_PHYS
suffix:semicolon
)brace
macro_line|#endif&t;/* __ASSEMBLER__ */
macro_line|#endif&t;/* __ASM_ARCH_TC_H */
eof
