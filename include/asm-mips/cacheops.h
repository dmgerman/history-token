multiline_comment|/*&n; * Cache operations for the cache instruction.&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * (C) Copyright 1996, 1997 by Ralf Baechle&n; */
macro_line|#ifndef&t;__ASM_MIPS_CACHEOPS_H
DECL|macro|__ASM_MIPS_CACHEOPS_H
mdefine_line|#define&t;__ASM_MIPS_CACHEOPS_H
multiline_comment|/*&n; * Cache Operations&n; */
DECL|macro|Index_Invalidate_I
mdefine_line|#define Index_Invalidate_I      0x00
DECL|macro|Index_Writeback_Inv_D
mdefine_line|#define Index_Writeback_Inv_D   0x01
DECL|macro|Index_Invalidate_SI
mdefine_line|#define Index_Invalidate_SI     0x02
DECL|macro|Index_Writeback_Inv_SD
mdefine_line|#define Index_Writeback_Inv_SD  0x03
DECL|macro|Index_Load_Tag_I
mdefine_line|#define Index_Load_Tag_I&t;0x04
DECL|macro|Index_Load_Tag_D
mdefine_line|#define Index_Load_Tag_D&t;0x05
DECL|macro|Index_Load_Tag_SI
mdefine_line|#define Index_Load_Tag_SI&t;0x06
DECL|macro|Index_Load_Tag_SD
mdefine_line|#define Index_Load_Tag_SD&t;0x07
DECL|macro|Index_Store_Tag_I
mdefine_line|#define Index_Store_Tag_I&t;0x08
DECL|macro|Index_Store_Tag_D
mdefine_line|#define Index_Store_Tag_D&t;0x09
DECL|macro|Index_Store_Tag_SI
mdefine_line|#define Index_Store_Tag_SI&t;0x0A
DECL|macro|Index_Store_Tag_SD
mdefine_line|#define Index_Store_Tag_SD&t;0x0B
DECL|macro|Create_Dirty_Excl_D
mdefine_line|#define Create_Dirty_Excl_D&t;0x0d
DECL|macro|Create_Dirty_Excl_SD
mdefine_line|#define Create_Dirty_Excl_SD&t;0x0f
DECL|macro|Hit_Invalidate_I
mdefine_line|#define Hit_Invalidate_I&t;0x10
DECL|macro|Hit_Invalidate_D
mdefine_line|#define Hit_Invalidate_D&t;0x11
DECL|macro|Hit_Invalidate_SI
mdefine_line|#define Hit_Invalidate_SI&t;0x12
DECL|macro|Hit_Invalidate_SD
mdefine_line|#define Hit_Invalidate_SD&t;0x13
DECL|macro|Fill
mdefine_line|#define Fill&t;&t;&t;0x14
DECL|macro|Hit_Writeback_Inv_D
mdefine_line|#define Hit_Writeback_Inv_D&t;0x15
multiline_comment|/* 0x16 is unused */
DECL|macro|Hit_Writeback_Inv_SD
mdefine_line|#define Hit_Writeback_Inv_SD&t;0x17
DECL|macro|Hit_Writeback_I
mdefine_line|#define Hit_Writeback_I&t;&t;0x18
DECL|macro|Hit_Writeback_D
mdefine_line|#define Hit_Writeback_D&t;&t;0x19
multiline_comment|/* 0x1a is unused */
DECL|macro|Hit_Writeback_SD
mdefine_line|#define Hit_Writeback_SD&t;0x1b
multiline_comment|/* 0x1c is unused */
multiline_comment|/* 0x1e is unused */
DECL|macro|Hit_Set_Virtual_SI
mdefine_line|#define Hit_Set_Virtual_SI&t;0x1e
DECL|macro|Hit_Set_Virtual_SD
mdefine_line|#define Hit_Set_Virtual_SD&t;0x1f
macro_line|#endif&t;/* __ASM_MIPS_CACHEOPS_H */
eof
