multiline_comment|/***********************************************************************&n; * Copyright 2001 MontaVista Software Inc.&n; * Author: Jun Sun, jsun@mvista.com or jsun@junsun.net&n; *&n; * arch/mips/gt64240/gt64240-dep.h&n; *     Board-dependent definitions for GT-64120 chip.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; ***********************************************************************&n; */
macro_line|#ifndef _ASM_GT64240_DEP_H
DECL|macro|_ASM_GT64240_DEP_H
mdefine_line|#define _ASM_GT64240_DEP_H
macro_line|#include &lt;asm/addrspace.h&gt;&t;&t;/* for KSEG1ADDR() */
macro_line|#include &lt;asm/byteorder.h&gt;&t;&t;/* for cpu_to_le32() */
multiline_comment|/*&n; * PCI address allocation&n; */
macro_line|#if 0
mdefine_line|#define GT_PCI_MEM_BASE    (0x22000000)
mdefine_line|#define GT_PCI_MEM_SIZE    GT_DEF_PCI0_MEM0_SIZE
mdefine_line|#define GT_PCI_IO_BASE     (0x20000000)
mdefine_line|#define GT_PCI_IO_SIZE     GT_DEF_PCI0_IO_SIZE
macro_line|#endif
r_extern
r_int
r_int
id|gt64240_base
suffix:semicolon
DECL|macro|GT64240_BASE
mdefine_line|#define GT64240_BASE       (gt64240_base)
multiline_comment|/*&n; * Because of an error/peculiarity in the Galileo chip, we need to swap the&n; * bytes when running bigendian.&n; */
DECL|macro|GT_WRITE
mdefine_line|#define GT_WRITE(ofs, data)  &bslash;&n;        *(volatile u32 *)(GT64240_BASE+(ofs)) = cpu_to_le32(data)
DECL|macro|GT_READ
mdefine_line|#define GT_READ(ofs, data)   &bslash;&n;        *(data) = le32_to_cpu(*(volatile u32 *)(GT64240_BASE+(ofs)))
DECL|macro|GT_READ_DATA
mdefine_line|#define GT_READ_DATA(ofs)    &bslash;&n;        le32_to_cpu(*(volatile u32 *)(GT64240_BASE+(ofs)))
DECL|macro|GT_WRITE_16
mdefine_line|#define GT_WRITE_16(ofs, data)  &bslash;&n;        *(volatile u16 *)(GT64240_BASE+(ofs)) = cpu_to_le16(data)
DECL|macro|GT_READ_16
mdefine_line|#define GT_READ_16(ofs, data)   &bslash;&n;        *(data) = le16_to_cpu(*(volatile u16 *)(GT64240_BASE+(ofs)))
DECL|macro|GT_WRITE_8
mdefine_line|#define GT_WRITE_8(ofs, data)  &bslash;&n;        *(volatile u8 *)(GT64240_BASE+(ofs)) = data
DECL|macro|GT_READ_8
mdefine_line|#define GT_READ_8(ofs, data)   &bslash;&n;        *(data) = *(volatile u8 *)(GT64240_BASE+(ofs))
macro_line|#endif  /* _ASM_GT64120_MOMENCO_OCELOT_GT64120_DEP_H */
eof
