multiline_comment|/*&n; * linux/include/asm-arm/arch-omap/tc.h&n; *&n; * OMAP Traffic Controller&n; *&n; * Copyright (C) 2004 Nokia Corporation&n; * Author: Imre Deak &lt;imre.deak@nokia.com&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2 of the License, or (at your&n; * option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n; * General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write to the Free Software Foundation, Inc.,&n; * 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.&n; */
macro_line|#ifndef __ASM_ARCH_TC_H
DECL|macro|__ASM_ARCH_TC_H
mdefine_line|#define __ASM_ARCH_TC_H
DECL|macro|OMAP_TC_OCPT1_PRIOR
mdefine_line|#define OMAP_TC_OCPT1_PRIOR&t;0xFFFECC00
DECL|macro|OMAP_TC_EMIFS_PRIOR
mdefine_line|#define OMAP_TC_EMIFS_PRIOR&t;0xFFFECC04
DECL|macro|OMAP_TC_EMIFF_PRIOR
mdefine_line|#define OMAP_TC_EMIFF_PRIOR&t;0xFFFECC08
DECL|macro|OMAP_TC_OCPT2_PRIOR
mdefine_line|#define OMAP_TC_OCPT2_PRIOR&t;0xFFFECCD0
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
multiline_comment|/* external EMIFS chipselect regions */
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
macro_line|#endif&t;/* __ASM_ARCH_TC_H */
eof
