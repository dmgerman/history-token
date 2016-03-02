multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1999,2001-2003 Silicon Graphics, Inc.  All Rights Reserved.&n; * Copyright (C) 1999 by Ralf Baechle&n; */
macro_line|#ifndef _ASM_IA64_SN_TYPES_H
DECL|macro|_ASM_IA64_SN_TYPES_H
mdefine_line|#define _ASM_IA64_SN_TYPES_H
DECL|typedef|cpuid_t
r_typedef
r_int
r_int
id|cpuid_t
suffix:semicolon
DECL|typedef|nasid_t
r_typedef
r_int
r_int
id|nasid_t
suffix:semicolon
multiline_comment|/* node id in numa-as-id space */
DECL|typedef|partid_t
r_typedef
r_int
r_char
id|partid_t
suffix:semicolon
multiline_comment|/* partition ID type */
DECL|typedef|moduleid_t
r_typedef
r_int
r_int
id|moduleid_t
suffix:semicolon
multiline_comment|/* user-visible module number type */
DECL|typedef|cmoduleid_t
r_typedef
r_int
r_int
id|cmoduleid_t
suffix:semicolon
multiline_comment|/* kernel compact module id type */
DECL|typedef|slabid_t
r_typedef
r_int
r_char
id|slabid_t
suffix:semicolon
DECL|typedef|iopaddr_t
r_typedef
r_int
r_int
id|iopaddr_t
suffix:semicolon
DECL|typedef|paddr_t
r_typedef
r_int
r_int
id|paddr_t
suffix:semicolon
DECL|typedef|cnodeid_t
r_typedef
r_int
id|cnodeid_t
suffix:semicolon
macro_line|#endif /* _ASM_IA64_SN_TYPES_H */
eof
