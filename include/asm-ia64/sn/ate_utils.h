macro_line|#ifndef _ASM_IA64_SN_ATE_UTILS_H
DECL|macro|_ASM_IA64_SN_ATE_UTILS_H
mdefine_line|#define _ASM_IA64_SN_ATE_UTILS_H
multiline_comment|/* $Id$&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997, 2000-2002 Silicon Graphics, Inc. All rights reserved.&n; */
multiline_comment|/*&n; *&t;struct map&t;X[]&t;.m_size&t;&t;.m_addr&n; *&t;&t;&t;---&t;------------&t;-----------&n; *&t;&t;&t;[0]&t;mapsize(X)&t;unused&n; *&t;&t;&t;&t;# X[] unused&n; *&t;&t;&t;[1]&t;map lock *&t;mapwant sv_t *&n; *&t;&t;&t;&t;map access&t;wait for free map space&n; *&n; *&t;  mapstart(X)-&gt; [2]&t;# units&t;&t;unit number&n; *&t;&t;&t; :&t;    :&t;&t;  :&n; *&t;&t;&t;[ ]&t;    0&n; */
macro_line|#include &lt;linux/types.h&gt;
DECL|macro|ulong_t
mdefine_line|#define ulong_t uint64_t
DECL|struct|map
r_struct
id|map
(brace
DECL|member|m_size
r_int
r_int
id|m_size
suffix:semicolon
multiline_comment|/* number of units available */
DECL|member|m_addr
r_int
r_int
id|m_addr
suffix:semicolon
multiline_comment|/* address of first available unit */
)brace
suffix:semicolon
DECL|macro|mapstart
mdefine_line|#define mapstart(X)&t;&t;&amp;X[2]&t;&t;/* start of map array */
DECL|macro|mapsize
mdefine_line|#define mapsize(X)&t;&t;X[0].m_size&t;/* number of empty slots */
multiline_comment|/* remaining in map array */
DECL|macro|maplock
mdefine_line|#define maplock(X)&t;&t;(((spinlock_t *) X[1].m_size))
DECL|macro|mapout
mdefine_line|#define mapout(X)&t;&t;((sv_t *) X[1].m_addr)
r_extern
id|ulong_t
id|atealloc
c_func
(paren
r_struct
id|map
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_struct
id|map
op_star
id|atemapalloc
c_func
(paren
id|ulong_t
)paren
suffix:semicolon
r_extern
r_void
id|atefree
c_func
(paren
r_struct
id|map
op_star
comma
r_int
comma
id|ulong_t
)paren
suffix:semicolon
r_extern
r_void
id|atemapfree
c_func
(paren
r_struct
id|map
op_star
)paren
suffix:semicolon
macro_line|#endif /* _ASM_IA64_SN_ATE_UTILS_H  */
eof
