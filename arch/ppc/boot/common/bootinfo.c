multiline_comment|/*&n; * arch/ppc/common/bootinfo.c&n; *&n; * General bootinfo record utilities&n; * Author: Randy Vinson &lt;rvinson@mvista.com&gt;&n; *&n; * 2002 (c) MontaVista Software, Inc. This file is licensed under the terms&n; * of the GNU General Public License version 2. This program is licensed&n; * &quot;as is&quot; without any warranty of any kind, whether express or implied.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &quot;nonstdio.h&quot;
DECL|variable|birec
r_static
r_struct
id|bi_record
op_star
id|birec
op_assign
l_int|NULL
suffix:semicolon
r_static
r_struct
id|bi_record
op_star
DECL|function|__bootinfo_build
id|__bootinfo_build
c_func
(paren
r_struct
id|bi_record
op_star
id|rec
comma
r_int
r_int
id|tag
comma
r_int
r_int
id|size
comma
r_void
op_star
id|data
)paren
(brace
multiline_comment|/* set the tag */
id|rec-&gt;tag
op_assign
id|tag
suffix:semicolon
multiline_comment|/* if the caller has any data, copy it */
r_if
c_cond
(paren
id|size
)paren
id|memcpy
c_func
(paren
id|rec-&gt;data
comma
(paren
r_char
op_star
)paren
id|data
comma
id|size
)paren
suffix:semicolon
multiline_comment|/* set the record size */
id|rec-&gt;size
op_assign
r_sizeof
(paren
r_struct
id|bi_record
)paren
op_plus
id|size
suffix:semicolon
multiline_comment|/* advance to the next available space */
id|rec
op_assign
(paren
r_struct
id|bi_record
op_star
)paren
(paren
(paren
r_int
r_int
)paren
id|rec
op_plus
id|rec-&gt;size
)paren
suffix:semicolon
r_return
id|rec
suffix:semicolon
)brace
r_void
DECL|function|bootinfo_init
id|bootinfo_init
c_func
(paren
r_struct
id|bi_record
op_star
id|rec
)paren
(brace
multiline_comment|/* save start of birec area */
id|birec
op_assign
id|rec
suffix:semicolon
multiline_comment|/* create an empty list */
id|rec
op_assign
id|__bootinfo_build
c_func
(paren
id|rec
comma
id|BI_FIRST
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
(paren
r_void
)paren
id|__bootinfo_build
c_func
(paren
id|rec
comma
id|BI_LAST
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
)brace
r_void
DECL|function|bootinfo_append
id|bootinfo_append
c_func
(paren
r_int
r_int
id|tag
comma
r_int
r_int
id|size
comma
r_void
op_star
id|data
)paren
(brace
r_struct
id|bi_record
op_star
id|rec
op_assign
id|birec
suffix:semicolon
multiline_comment|/* paranoia */
r_if
c_cond
(paren
(paren
id|rec
op_eq
l_int|NULL
)paren
op_logical_or
(paren
id|rec-&gt;tag
op_ne
id|BI_FIRST
)paren
)paren
r_return
suffix:semicolon
multiline_comment|/* find the last entry in the list */
r_while
c_loop
(paren
id|rec-&gt;tag
op_ne
id|BI_LAST
)paren
id|rec
op_assign
(paren
r_struct
id|bi_record
op_star
)paren
(paren
(paren
id|ulong
)paren
id|rec
op_plus
id|rec-&gt;size
)paren
suffix:semicolon
multiline_comment|/* overlay BI_LAST record with new one and tag on a new BI_LAST */
id|rec
op_assign
id|__bootinfo_build
c_func
(paren
id|rec
comma
id|tag
comma
id|size
comma
id|data
)paren
suffix:semicolon
(paren
r_void
)paren
id|__bootinfo_build
c_func
(paren
id|rec
comma
id|BI_LAST
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
)brace
eof
