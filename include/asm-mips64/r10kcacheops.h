multiline_comment|/* $Id: r10kcacheops.h,v 1.1 2000/01/12 23:18:32 ralf Exp $&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Cache operations for the cache instruction.&n; *&n; * (C) Copyright 1996, 1997, 1999 by Ralf Baechle&n; * (C) Copyright 1999 Silicon Graphics, Inc.&n; */
macro_line|#ifndef&t;_ASM_R10KCACHEOPS_H
DECL|macro|_ASM_R10KCACHEOPS_H
mdefine_line|#define&t;_ASM_R10KCACHEOPS_H
multiline_comment|/*&n; * Cache Operations&n; */
DECL|macro|Index_Invalidate_I
mdefine_line|#define Index_Invalidate_I      0x00
DECL|macro|Index_Writeback_Inv_D
mdefine_line|#define Index_Writeback_Inv_D   0x01
multiline_comment|/* 0x02 is unused */
DECL|macro|Index_Writeback_Inv_S
mdefine_line|#define Index_Writeback_Inv_S&t;0x03
DECL|macro|Index_Load_Tag_I
mdefine_line|#define Index_Load_Tag_I&t;0x04
DECL|macro|Index_Load_Tag_D
mdefine_line|#define Index_Load_Tag_D&t;0x05
multiline_comment|/* 0x06 is unused */
DECL|macro|Index_Load_Tag_S
mdefine_line|#define Index_Load_Tag_S&t;0x07
DECL|macro|Index_Store_Tag_I
mdefine_line|#define Index_Store_Tag_I&t;0x08
DECL|macro|Index_Store_Tag_D
mdefine_line|#define Index_Store_Tag_D&t;0x09
multiline_comment|/* 0x0a is unused */
DECL|macro|Index_Store_Tag_S
mdefine_line|#define Index_Store_Tag_S&t;0x0b
multiline_comment|/* 0x0c - 0x0e are unused */
DECL|macro|Hit_Invalidate_I
mdefine_line|#define Hit_Invalidate_I&t;0x10
DECL|macro|Hit_Invalidate_D
mdefine_line|#define Hit_Invalidate_D&t;0x11
multiline_comment|/* 0x12 is unused */
DECL|macro|Hit_Invalidate_S
mdefine_line|#define Hit_Invalidate_S&t;0x13
DECL|macro|Cache_Barrier
mdefine_line|#define Cache_Barrier&t;&t;0x14
DECL|macro|Hit_Writeback_Inv_D
mdefine_line|#define Hit_Writeback_Inv_D&t;0x15
multiline_comment|/* 0x16 is unused */
DECL|macro|Hit_Writeback_Inv_S
mdefine_line|#define Hit_Writeback_Inv_S&t;0x17
DECL|macro|Index_Load_Data_I
mdefine_line|#define Index_Load_Data_I&t;0x18
DECL|macro|Index_Load_Data_D
mdefine_line|#define Index_Load_Data_D&t;0x19
multiline_comment|/* 0x1a is unused */
DECL|macro|Index_Load_Data_S
mdefine_line|#define Index_Load_Data_S&t;0x1b
DECL|macro|Index_Store_Data_I
mdefine_line|#define Index_Store_Data_I&t;0x1c
DECL|macro|Index_Store_Data_D
mdefine_line|#define Index_Store_Data_D&t;0x1d
multiline_comment|/* 0x1e is unused */
DECL|macro|Index_Store_Data_S
mdefine_line|#define Index_Store_Data_S&t;0x1f
macro_line|#endif&t;/* _ASM_R10KCACHEOPS_H */
eof
