multiline_comment|/*&n; * include/asm-sh/cpu-sh2/ubc.h&n; *&n; * Copyright (C) 2003 Paul Mundt&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; */
macro_line|#ifndef __ASM_CPU_SH2_UBC_H
DECL|macro|__ASM_CPU_SH2_UBC_H
mdefine_line|#define __ASM_CPU_SH2_UBC_H
DECL|macro|UBC_BARA
mdefine_line|#define UBC_BARA                0xffffff40
DECL|macro|UBC_BAMRA
mdefine_line|#define UBC_BAMRA               0xffffff44
DECL|macro|UBC_BBRA
mdefine_line|#define UBC_BBRA                0xffffff48
DECL|macro|UBC_BARB
mdefine_line|#define UBC_BARB                0xffffff60
DECL|macro|UBC_BAMRB
mdefine_line|#define UBC_BAMRB               0xffffff64
DECL|macro|UBC_BBRB
mdefine_line|#define UBC_BBRB                0xffffff68
DECL|macro|UBC_BDRB
mdefine_line|#define UBC_BDRB                0xffffff70
DECL|macro|UBC_BDMRB
mdefine_line|#define UBC_BDMRB               0xffffff74
DECL|macro|UBC_BRCR
mdefine_line|#define UBC_BRCR                0xffffff78
multiline_comment|/*&n; * We don&squot;t have any ASID changes to make in the UBC on the SH-2.&n; *&n; * Make these purposely invalid to track misuse.&n; */
DECL|macro|UBC_BASRA
mdefine_line|#define UBC_BASRA&t;&t;0x00000000
DECL|macro|UBC_BASRB
mdefine_line|#define UBC_BASRB&t;&t;0x00000000
macro_line|#endif /* __ASM_CPU_SH2_UBC_H */
eof
