multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (c) 1994 - 2000 by Ralf Baechle&n; * Copyright (c) 2000 by Silicon Graphics, Inc.&n; */
macro_line|#ifndef _ASM_STRING_H
DECL|macro|_ASM_STRING_H
mdefine_line|#define _ASM_STRING_H
DECL|macro|__HAVE_ARCH_MEMSET
mdefine_line|#define __HAVE_ARCH_MEMSET
r_extern
r_void
op_star
id|memset
c_func
(paren
r_void
op_star
id|__s
comma
r_int
id|__c
comma
r_int
id|__count
)paren
suffix:semicolon
DECL|macro|__HAVE_ARCH_MEMCPY
mdefine_line|#define __HAVE_ARCH_MEMCPY
r_extern
r_void
op_star
id|memcpy
c_func
(paren
r_void
op_star
id|__to
comma
id|__const__
r_void
op_star
id|__from
comma
r_int
id|__n
)paren
suffix:semicolon
DECL|macro|__HAVE_ARCH_MEMMOVE
mdefine_line|#define __HAVE_ARCH_MEMMOVE
r_extern
r_void
op_star
id|memmove
c_func
(paren
r_void
op_star
id|__dest
comma
id|__const__
r_void
op_star
id|__src
comma
r_int
id|__n
)paren
suffix:semicolon
multiline_comment|/* Don&squot;t build bcopy at all ...  */
DECL|macro|__HAVE_ARCH_BCOPY
mdefine_line|#define __HAVE_ARCH_BCOPY
macro_line|#endif /* _ASM_STRING_H */
eof
