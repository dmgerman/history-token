multiline_comment|/*&n; * Carsten Langgaard, carstenl@mips.com&n; * Copyright (C) 2000 MIPS Technologies, Inc.  All rights reserved.&n; *&n; * This program is free software; you can distribute it and/or modify it&n; * under the terms of the GNU General Public License (Version 2) as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope it will be useful, but WITHOUT&n; * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or&n; * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License&n; * for more details.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write to the Free Software Foundation, Inc.,&n; * 59 Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Defines of the MIPS boards specific address-MAP, registers, etc.&n; */
macro_line|#ifndef __ASM_MIPS_BOARDS_GENERIC_H
DECL|macro|__ASM_MIPS_BOARDS_GENERIC_H
mdefine_line|#define __ASM_MIPS_BOARDS_GENERIC_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/addrspace.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &lt;asm/mips-boards/bonito64.h&gt;
multiline_comment|/*&n; * Display register base.&n; */
macro_line|#ifdef CONFIG_MIPS_SEAD
DECL|macro|ASCII_DISPLAY_POS_BASE
mdefine_line|#define ASCII_DISPLAY_POS_BASE     0x1f0005c0
macro_line|#else
DECL|macro|ASCII_DISPLAY_WORD_BASE
mdefine_line|#define ASCII_DISPLAY_WORD_BASE    0x1f000410
DECL|macro|ASCII_DISPLAY_POS_BASE
mdefine_line|#define ASCII_DISPLAY_POS_BASE     0x1f000418
macro_line|#endif
multiline_comment|/*&n; * Yamon Prom print address.&n; */
DECL|macro|YAMON_PROM_PRINT_ADDR
mdefine_line|#define YAMON_PROM_PRINT_ADDR      0x1fc00504
multiline_comment|/*&n; * Reset register.&n; */
macro_line|#ifdef CONFIG_MIPS_SEAD
DECL|macro|SOFTRES_REG
mdefine_line|#define SOFTRES_REG       0x1e800050
DECL|macro|GORESET
mdefine_line|#define GORESET           0x4d
macro_line|#else
DECL|macro|SOFTRES_REG
mdefine_line|#define SOFTRES_REG       0x1f000500
DECL|macro|GORESET
mdefine_line|#define GORESET           0x42
macro_line|#endif
multiline_comment|/*&n; * Revision register.&n; */
DECL|macro|MIPS_REVISION_REG
mdefine_line|#define MIPS_REVISION_REG                  0x1fc00010
DECL|macro|MIPS_REVISION_CORID_QED_RM5261
mdefine_line|#define MIPS_REVISION_CORID_QED_RM5261     0
DECL|macro|MIPS_REVISION_CORID_CORE_LV
mdefine_line|#define MIPS_REVISION_CORID_CORE_LV        1
DECL|macro|MIPS_REVISION_CORID_BONITO64
mdefine_line|#define MIPS_REVISION_CORID_BONITO64       2
DECL|macro|MIPS_REVISION_CORID_CORE_20K
mdefine_line|#define MIPS_REVISION_CORID_CORE_20K       3
DECL|macro|MIPS_REVISION_CORID_CORE_FPGA
mdefine_line|#define MIPS_REVISION_CORID_CORE_FPGA      4
DECL|macro|MIPS_REVISION_CORID_CORE_MSC
mdefine_line|#define MIPS_REVISION_CORID_CORE_MSC       5
DECL|macro|MIPS_REVISION_CORID_CORE_EMUL
mdefine_line|#define MIPS_REVISION_CORID_CORE_EMUL      6
DECL|macro|MIPS_REVISION_CORID_CORE_FPGA2
mdefine_line|#define MIPS_REVISION_CORID_CORE_FPGA2     7
DECL|macro|MIPS_REVISION_CORID_CORE_FPGAR2
mdefine_line|#define MIPS_REVISION_CORID_CORE_FPGAR2    8
multiline_comment|/**** Artificial corid defines ****/
multiline_comment|/*&n; *  CoreEMUL with   Bonito   System Controller is treated like a Core20K&n; *  CoreEMUL with SOC-it 101 System Controller is treated like a CoreMSC&n; */
DECL|macro|MIPS_REVISION_CORID_CORE_EMUL_BON
mdefine_line|#define MIPS_REVISION_CORID_CORE_EMUL_BON  0x63
DECL|macro|MIPS_REVISION_CORID_CORE_EMUL_MSC
mdefine_line|#define MIPS_REVISION_CORID_CORE_EMUL_MSC  0x65
DECL|macro|MIPS_REVISION_CORID
mdefine_line|#define MIPS_REVISION_CORID (((*(volatile u32 *)ioremap(MIPS_REVISION_REG, 4)) &gt;&gt; 10) &amp; 0x3f)
r_extern
r_int
r_int
id|mips_revision_corid
suffix:semicolon
macro_line|#endif  /* __ASM_MIPS_BOARDS_GENERIC_H */
eof
