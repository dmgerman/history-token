multiline_comment|/*&n; * Carsten Langgaard, carstenl@mips.com&n; * Copyright (C) 2000 MIPS Technologies, Inc.  All rights reserved.&n; *&n; * ########################################################################&n; *&n; *  This program is free software; you can distribute it and/or modify it&n; *  under the terms of the GNU General Public License (Version 2) as&n; *  published by the Free Software Foundation.&n; *&n; *  This program is distributed in the hope it will be useful, but WITHOUT&n; *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or&n; *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License&n; *  for more details.&n; *&n; *  You should have received a copy of the GNU General Public License along&n; *  with this program; if not, write to the Free Software Foundation, Inc.,&n; *  59 Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * ########################################################################&n; *&n; * Defines of the MIPS boards specific address-MAP, registers, etc.&n; *&n; */
macro_line|#ifndef _MIPS_GENERIC_H
DECL|macro|_MIPS_GENERIC_H
mdefine_line|#define _MIPS_GENERIC_H
macro_line|#include &lt;asm/addrspace.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
multiline_comment|/*&n; * Display register base.&n; */
DECL|macro|ASCII_DISPLAY_WORD_BASE
mdefine_line|#define ASCII_DISPLAY_WORD_BASE    (KSEG1ADDR(0x1f000410))
DECL|macro|ASCII_DISPLAY_POS_BASE
mdefine_line|#define ASCII_DISPLAY_POS_BASE     (KSEG1ADDR(0x1f000418))
multiline_comment|/*&n; * Yamon Prom print address.&n; */
DECL|macro|YAMON_PROM_PRINT_ADDR
mdefine_line|#define YAMON_PROM_PRINT_ADDR      (KSEG1ADDR(0x1fc00504))
multiline_comment|/*&n; * Reset register.&n; */
DECL|macro|SOFTRES_REG
mdefine_line|#define SOFTRES_REG       (KSEG1ADDR(0x1f000500))
DECL|macro|GORESET
mdefine_line|#define GORESET           0x42
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
macro_line|#endif  /* !(_MIPS_GENERIC_H) */
eof
