multiline_comment|/*&n; * Carsten Langgaard, carstenl@mips.com&n; * Copyright (C) 2000 MIPS Technologies, Inc.  All rights reserved.&n; *&n; * ########################################################################&n; *&n; *  This program is free software; you can distribute it and/or modify it&n; *  under the terms of the GNU General Public License (Version 2) as&n; *  published by the Free Software Foundation.&n; *&n; *  This program is distributed in the hope it will be useful, but WITHOUT&n; *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or&n; *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License&n; *  for more details.&n; *&n; *  You should have received a copy of the GNU General Public License along&n; *  with this program; if not, write to the Free Software Foundation, Inc.,&n; *  59 Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * ########################################################################&n; *&n; * Defines of the MIPS boards specific address-MAP, registers, etc.&n; *&n; */
macro_line|#ifndef _MIPS_GENERIC_H
DECL|macro|_MIPS_GENERIC_H
mdefine_line|#define _MIPS_GENERIC_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/addrspace.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &lt;asm/mips-boards/bonito64.h&gt;
multiline_comment|/*&n; * Display register base.&n; */
macro_line|#if defined(CONFIG_MIPS_SEAD)
DECL|macro|ASCII_DISPLAY_POS_BASE
mdefine_line|#define ASCII_DISPLAY_POS_BASE     (KSEG1ADDR(0x1f0005c0))
macro_line|#else
DECL|macro|ASCII_DISPLAY_WORD_BASE
mdefine_line|#define ASCII_DISPLAY_WORD_BASE    (KSEG1ADDR(0x1f000410))
DECL|macro|ASCII_DISPLAY_POS_BASE
mdefine_line|#define ASCII_DISPLAY_POS_BASE     (KSEG1ADDR(0x1f000418))
macro_line|#endif
multiline_comment|/*&n; * Yamon Prom print address.&n; */
DECL|macro|YAMON_PROM_PRINT_ADDR
mdefine_line|#define YAMON_PROM_PRINT_ADDR      (KSEG1ADDR(0x1fc00504))
multiline_comment|/*&n; * Reset register.&n; */
macro_line|#if defined(CONFIG_MIPS_SEAD)
DECL|macro|SOFTRES_REG
mdefine_line|#define SOFTRES_REG       (KSEG1ADDR(0x1e800050))
DECL|macro|GORESET
mdefine_line|#define GORESET           0x4d
macro_line|#else
DECL|macro|SOFTRES_REG
mdefine_line|#define SOFTRES_REG       (KSEG1ADDR(0x1f000500))
DECL|macro|GORESET
mdefine_line|#define GORESET           0x42
macro_line|#endif
multiline_comment|/*&n; * Revision register.&n; */
DECL|macro|MIPS_REVISION_REG
mdefine_line|#define MIPS_REVISION_REG                  (KSEG1ADDR(0x1fc00010))
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
DECL|macro|MIPS_REVISION_CORID
mdefine_line|#define MIPS_REVISION_CORID (((*(volatile u32 *)(MIPS_REVISION_REG)) &gt;&gt; 10) &amp; 0x3f)
r_extern
r_int
r_int
id|mips_revision_corid
suffix:semicolon
multiline_comment|/*&n; * Galileo GT64120 system controller register base.&n; */
DECL|macro|MIPS_GT_BASE
mdefine_line|#define MIPS_GT_BASE    (KSEG1ADDR(0x1be00000))
multiline_comment|/*&n; * Because of the way the internal register works on the Galileo chip,&n; * we need to swap the bytes when running bigendian.&n; */
DECL|macro|GT_WRITE
mdefine_line|#define GT_WRITE(ofs, data)  &bslash;&n;             *(volatile u32 *)(MIPS_GT_BASE+ofs) = cpu_to_le32(data)
DECL|macro|GT_READ
mdefine_line|#define GT_READ(ofs, data)   &bslash;&n;             data = le32_to_cpu(*(volatile u32 *)(MIPS_GT_BASE+ofs))
DECL|macro|GT_PCI_WRITE
mdefine_line|#define GT_PCI_WRITE(ofs, data)  &bslash;&n;&t;*(volatile u32 *)(MIPS_GT_BASE+ofs) = data
DECL|macro|GT_PCI_READ
mdefine_line|#define GT_PCI_READ(ofs, data)   &bslash;&n;&t;data = *(volatile u32 *)(MIPS_GT_BASE+ofs)
multiline_comment|/*&n; * Algorithmics Bonito64 system controller register base.&n; */
DECL|variable|_bonito
r_static
r_char
op_star
r_const
id|_bonito
op_assign
(paren
r_char
op_star
)paren
id|KSEG1ADDR
c_func
(paren
id|BONITO_REG_BASE
)paren
suffix:semicolon
multiline_comment|/*&n; * MIPS System controller PCI register base.&n; */
DECL|macro|MSC01_PCI_REG_BASE
mdefine_line|#define MSC01_PCI_REG_BASE  (KSEG1ADDR(0x1bd00000))
DECL|macro|MSC_WRITE
mdefine_line|#define MSC_WRITE(reg, data)  &bslash;&n;&t;*(volatile u32 *)(reg) = data
DECL|macro|MSC_READ
mdefine_line|#define MSC_READ(reg, data)   &bslash;&n;&t;data = *(volatile u32 *)(reg)
macro_line|#endif  /* !(_MIPS_GENERIC_H) */
eof
