multiline_comment|/*&n; * Copyright 2002 Momentum Computer Inc.&n; * Author: Matthew Dharm &lt;mdharm@momenco.com&gt;&n; *&n; * include/asm-mips/mv64340-dep.h&n; *     Board-dependent definitions for MV-64340 chip.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; */
macro_line|#ifndef __MV64340_DEP_H__
DECL|macro|__MV64340_DEP_H__
mdefine_line|#define __MV64340_DEP_H__
macro_line|#include &lt;asm/addrspace.h&gt;&t;&t;/* for KSEG1ADDR() */
macro_line|#include &lt;asm/byteorder.h&gt;&t;&t;/* for cpu_to_le32() */
r_extern
r_int
r_int
id|mv64340_base
suffix:semicolon
DECL|macro|MV64340_BASE
mdefine_line|#define MV64340_BASE       (mv64340_base)
multiline_comment|/*&n; * Because of an error/peculiarity in the Galileo chip, we need to swap the&n; * bytes when running bigendian.&n; */
DECL|macro|MV_WRITE
mdefine_line|#define MV_WRITE(ofs, data)  &bslash;&n;        *(volatile u32 *)(MV64340_BASE+(ofs)) = cpu_to_le32(data)
DECL|macro|MV_READ
mdefine_line|#define MV_READ(ofs, data)   &bslash;&n;        *(data) = le32_to_cpu(*(volatile u32 *)(MV64340_BASE+(ofs)))
DECL|macro|MV_READ_DATA
mdefine_line|#define MV_READ_DATA(ofs)    &bslash;&n;        le32_to_cpu(*(volatile u32 *)(MV64340_BASE+(ofs)))
DECL|macro|MV_WRITE_16
mdefine_line|#define MV_WRITE_16(ofs, data)  &bslash;&n;        *(volatile u16 *)(MV64340_BASE+(ofs)) = cpu_to_le16(data)
DECL|macro|MV_READ_16
mdefine_line|#define MV_READ_16(ofs, data)   &bslash;&n;        *(data) = le16_to_cpu(*(volatile u16 *)(MV64340_BASE+(ofs)))
DECL|macro|MV_WRITE_8
mdefine_line|#define MV_WRITE_8(ofs, data)  &bslash;&n;        *(volatile u8 *)(MV64340_BASE+(ofs)) = data
DECL|macro|MV_READ_8
mdefine_line|#define MV_READ_8(ofs, data)   &bslash;&n;        *(data) = *(volatile u8 *)(MV64340_BASE+(ofs))
DECL|macro|MV_SET_REG_BITS
mdefine_line|#define MV_SET_REG_BITS(ofs,bits) &bslash;&n;&t;(*((volatile u32 *)(MV64340_BASE+(ofs)))) |= ((u32)cpu_to_le32(bits))
DECL|macro|MV_RESET_REG_BITS
mdefine_line|#define MV_RESET_REG_BITS(ofs,bits) &bslash;&n;&t;(*((volatile u32 *)(MV64340_BASE+(ofs)))) &amp;= ~((u32)cpu_to_le32(bits))
macro_line|#endif
eof
