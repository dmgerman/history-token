multiline_comment|/* $Id$&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997, 2000-2001 Silicon Graphics, Inc. All rights reserved.&n; */
macro_line|#ifndef _ASM_IA64_SN_SN1_HUBXB_NEXT_H
DECL|macro|_ASM_IA64_SN_SN1_HUBXB_NEXT_H
mdefine_line|#define _ASM_IA64_SN_SN1_HUBXB_NEXT_H
multiline_comment|/* XB_FIRST_ERROR fe_source field encoding */
DECL|macro|XVE_SOURCE_POQ0
mdefine_line|#define XVE_SOURCE_POQ0 0xf&t;/* 1111 */
DECL|macro|XVE_SOURCE_PIQ0
mdefine_line|#define XVE_SOURCE_PIQ0 0xe&t;/* 1110 */
DECL|macro|XVE_SOURCE_POQ1
mdefine_line|#define XVE_SOURCE_POQ1 0xd&t;/* 1101 */
DECL|macro|XVE_SOURCE_PIQ1
mdefine_line|#define XVE_SOURCE_PIQ1 0xc&t;/* 1100 */
DECL|macro|XVE_SOURCE_MP0
mdefine_line|#define XVE_SOURCE_MP0  0xb&t;/* 1011 */
DECL|macro|XVE_SOURCE_MP1
mdefine_line|#define XVE_SOURCE_MP1  0xa&t;/* 1010 */
DECL|macro|XVE_SOURCE_MMQ
mdefine_line|#define XVE_SOURCE_MMQ  0x9&t;/* 1001 */
DECL|macro|XVE_SOURCE_MIQ
mdefine_line|#define XVE_SOURCE_MIQ  0x8&t;/* 1000 */
DECL|macro|XVE_SOURCE_NOQ
mdefine_line|#define XVE_SOURCE_NOQ  0x7&t;/* 0111 */
DECL|macro|XVE_SOURCE_NIQ
mdefine_line|#define XVE_SOURCE_NIQ  0x6&t;/* 0110 */
DECL|macro|XVE_SOURCE_IOQ
mdefine_line|#define XVE_SOURCE_IOQ  0x5&t;/* 0101 */
DECL|macro|XVE_SOURCE_IIQ
mdefine_line|#define XVE_SOURCE_IIQ  0x4&t;/* 0100 */
DECL|macro|XVE_SOURCE_LOQ
mdefine_line|#define XVE_SOURCE_LOQ  0x3&t;/* 0011 */
DECL|macro|XVE_SOURCE_LIQ
mdefine_line|#define XVE_SOURCE_LIQ  0x2&t;/* 0010 */
multiline_comment|/* XB_PARMS fields */
DECL|macro|XBP_RESET_DEFAULTS
mdefine_line|#define XBP_RESET_DEFAULTS&t;0x0008000080000021LL
DECL|macro|XBP_ACTIVE_DEFAULTS
mdefine_line|#define XBP_ACTIVE_DEFAULTS&t;0x00080000fffff021LL
macro_line|#endif /* _ASM_IA64_SN_SN1_HUBXB_NEXT_H */
eof
