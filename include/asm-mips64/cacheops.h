multiline_comment|/*&n; * Cache operations for the cache instruction.&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * (C) Copyright 1996, 97, 99, 2002, 03 Ralf Baechle&n; * (C) Copyright 1999 Silicon Graphics, Inc.&n; */
macro_line|#ifndef&t;__ASM_CACHEOPS_H
DECL|macro|__ASM_CACHEOPS_H
mdefine_line|#define&t;__ASM_CACHEOPS_H
multiline_comment|/*&n; * Cache Operations available on all MIPS processors with R4000-style caches&n; */
DECL|macro|Index_Invalidate_I
mdefine_line|#define Index_Invalidate_I      0x00
DECL|macro|Index_Writeback_Inv_D
mdefine_line|#define Index_Writeback_Inv_D   0x01
DECL|macro|Index_Load_Tag_I
mdefine_line|#define Index_Load_Tag_I&t;0x04
DECL|macro|Index_Load_Tag_D
mdefine_line|#define Index_Load_Tag_D&t;0x05
DECL|macro|Index_Store_Tag_I
mdefine_line|#define Index_Store_Tag_I&t;0x08
DECL|macro|Index_Store_Tag_D
mdefine_line|#define Index_Store_Tag_D&t;0x09
DECL|macro|Hit_Invalidate_I
mdefine_line|#define Hit_Invalidate_I&t;0x10
DECL|macro|Hit_Invalidate_D
mdefine_line|#define Hit_Invalidate_D&t;0x11
DECL|macro|Hit_Writeback_Inv_D
mdefine_line|#define Hit_Writeback_Inv_D&t;0x15
multiline_comment|/*&n; * R4000-specific cacheops&n; */
DECL|macro|Create_Dirty_Excl_D
mdefine_line|#define Create_Dirty_Excl_D&t;0x0d
DECL|macro|Fill
mdefine_line|#define Fill&t;&t;&t;0x14
DECL|macro|Hit_Writeback_I
mdefine_line|#define Hit_Writeback_I&t;&t;0x18
DECL|macro|Hit_Writeback_D
mdefine_line|#define Hit_Writeback_D&t;&t;0x19
multiline_comment|/*&n; * R4000SC and R4400SC-specific cacheops&n; */
DECL|macro|Index_Invalidate_SI
mdefine_line|#define Index_Invalidate_SI     0x02
DECL|macro|Index_Writeback_Inv_SD
mdefine_line|#define Index_Writeback_Inv_SD  0x03
DECL|macro|Index_Load_Tag_SI
mdefine_line|#define Index_Load_Tag_SI&t;0x06
DECL|macro|Index_Load_Tag_SD
mdefine_line|#define Index_Load_Tag_SD&t;0x07
DECL|macro|Index_Store_Tag_SI
mdefine_line|#define Index_Store_Tag_SI&t;0x0A
DECL|macro|Index_Store_Tag_SD
mdefine_line|#define Index_Store_Tag_SD&t;0x0B
DECL|macro|Create_Dirty_Excl_SD
mdefine_line|#define Create_Dirty_Excl_SD&t;0x0f
DECL|macro|Hit_Invalidate_SI
mdefine_line|#define Hit_Invalidate_SI&t;0x12
DECL|macro|Hit_Invalidate_SD
mdefine_line|#define Hit_Invalidate_SD&t;0x13
DECL|macro|Hit_Writeback_Inv_SD
mdefine_line|#define Hit_Writeback_Inv_SD&t;0x17
DECL|macro|Hit_Writeback_SD
mdefine_line|#define Hit_Writeback_SD&t;0x1b
DECL|macro|Hit_Set_Virtual_SI
mdefine_line|#define Hit_Set_Virtual_SI&t;0x1e
DECL|macro|Hit_Set_Virtual_SD
mdefine_line|#define Hit_Set_Virtual_SD&t;0x1f
multiline_comment|/*&n; * R5000-specific cacheops&n; */
DECL|macro|R5K_Page_Invalidate_S
mdefine_line|#define R5K_Page_Invalidate_S&t;0x17
multiline_comment|/*&n; * RM7000-specific cacheops&n; */
DECL|macro|Page_Invalidate_T
mdefine_line|#define Page_Invalidate_T&t;0x16
multiline_comment|/*&n; * R1000-specific cacheops&n; *&n; * Cacheops 0x02, 0x06, 0x0a, 0x0c-0x0e, 0x16, 0x1a and 0x1e are unused.&n; * Most of the _S cacheops are identical to the R4000SC _SD cacheops.&n; */
DECL|macro|Index_Writeback_Inv_S
mdefine_line|#define Index_Writeback_Inv_S&t;0x03
DECL|macro|Index_Load_Tag_S
mdefine_line|#define Index_Load_Tag_S&t;0x07
DECL|macro|Index_Store_Tag_S
mdefine_line|#define Index_Store_Tag_S&t;0x0B
DECL|macro|Hit_Invalidate_S
mdefine_line|#define Hit_Invalidate_S&t;0x13
DECL|macro|Cache_Barrier
mdefine_line|#define Cache_Barrier&t;&t;0x14
DECL|macro|Hit_Writeback_Inv_S
mdefine_line|#define Hit_Writeback_Inv_S&t;0x17
DECL|macro|Index_Load_Data_I
mdefine_line|#define Index_Load_Data_I&t;0x18
DECL|macro|Index_Load_Data_D
mdefine_line|#define Index_Load_Data_D&t;0x19
DECL|macro|Index_Load_Data_S
mdefine_line|#define Index_Load_Data_S&t;0x1b
DECL|macro|Index_Store_Data_I
mdefine_line|#define Index_Store_Data_I&t;0x1c
DECL|macro|Index_Store_Data_D
mdefine_line|#define Index_Store_Data_D&t;0x1d
DECL|macro|Index_Store_Data_S
mdefine_line|#define Index_Store_Data_S&t;0x1f
macro_line|#endif&t;/* __ASM_CACHEOPS_H */
eof
