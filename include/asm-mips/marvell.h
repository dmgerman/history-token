multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2004 by Ralf Baechle&n; */
macro_line|#ifndef __ASM_MIPS_MARVELL_H
DECL|macro|__ASM_MIPS_MARVELL_H
mdefine_line|#define __ASM_MIPS_MARVELL_H
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
r_extern
r_int
r_int
id|marvell_base
suffix:semicolon
multiline_comment|/*&n; * Because of an error/peculiarity in the Galileo chip, we need to swap the&n; * bytes when running bigendian.&n; */
DECL|macro|__MV_READ
mdefine_line|#define __MV_READ(ofs)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(*(volatile u32 *)(marvell_base+(ofs)))
DECL|macro|__MV_WRITE
mdefine_line|#define __MV_WRITE(ofs, data)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;do { *(volatile u32 *)(marvell_base+(ofs)) = (data); } while (0)
DECL|macro|MV_READ
mdefine_line|#define MV_READ(ofs)&t;&t;le32_to_cpu(__MV_READ(ofs))
DECL|macro|MV_WRITE
mdefine_line|#define MV_WRITE(ofs, data)&t;__MV_WRITE(ofs, cpu_to_le32(data))
DECL|macro|MV_READ_16
mdefine_line|#define MV_READ_16(ofs)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;        le16_to_cpu(*(volatile u16 *)(marvell_base+(ofs)))
DECL|macro|MV_WRITE_16
mdefine_line|#define MV_WRITE_16(ofs, data)  &bslash;&n;        *(volatile u16 *)(marvell_base+(ofs)) = cpu_to_le16(data)
DECL|macro|MV_READ_8
mdefine_line|#define MV_READ_8(ofs)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;*(volatile u8 *)(marvell_base+(ofs))
DECL|macro|MV_WRITE_8
mdefine_line|#define MV_WRITE_8(ofs, data)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;*(volatile u8 *)(marvell_base+(ofs)) = data
DECL|macro|MV_SET_REG_BITS
mdefine_line|#define MV_SET_REG_BITS(ofs, bits)&t;&t;&t;&t;&t;&bslash;&n;&t;(*((volatile u32 *)(marvell_base + (ofs)))) |= ((u32)cpu_to_le32(bits))
DECL|macro|MV_RESET_REG_BITS
mdefine_line|#define MV_RESET_REG_BITS(ofs, bits)&t;&t;&t;&t;&t;&bslash;&n;&t;(*((volatile u32 *)(marvell_base + (ofs)))) &amp;= ~((u32)cpu_to_le32(bits))
r_extern
r_struct
id|pci_ops
id|mv_pci_ops
suffix:semicolon
DECL|struct|mv_pci_controller
r_struct
id|mv_pci_controller
(brace
DECL|member|pcic
r_struct
id|pci_controller
id|pcic
suffix:semicolon
multiline_comment|/*&n;&t; * GT-64240/MV-64340 specific, per host bus information&n;&t; */
DECL|member|config_addr
r_int
r_int
id|config_addr
suffix:semicolon
DECL|member|config_vreg
r_int
r_int
id|config_vreg
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif&t;/* __ASM_MIPS_MARVELL_H */
eof
