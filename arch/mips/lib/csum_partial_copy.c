multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1994, 1995 Waldorf Electronics GmbH&n; * Copyright (C) 1998, 1999 Ralf Baechle&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &lt;asm/string.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;net/checksum.h&gt;
multiline_comment|/*&n; * copy while checksumming, otherwise like csum_partial&n; */
DECL|function|csum_partial_copy_nocheck
r_int
r_int
id|csum_partial_copy_nocheck
c_func
(paren
r_const
r_int
r_char
op_star
id|src
comma
r_int
r_char
op_star
id|dst
comma
r_int
id|len
comma
r_int
r_int
id|sum
)paren
(brace
multiline_comment|/*&n;&t; * It&squot;s 2:30 am and I don&squot;t feel like doing it real ...&n;&t; * This is lots slower than the real thing (tm)&n;&t; */
id|sum
op_assign
id|csum_partial
c_func
(paren
id|src
comma
id|len
comma
id|sum
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|dst
comma
id|src
comma
id|len
)paren
suffix:semicolon
r_return
id|sum
suffix:semicolon
)brace
multiline_comment|/*&n; * Copy from userspace and compute checksum.  If we catch an exception&n; * then zero the rest of the buffer.&n; */
DECL|function|csum_partial_copy_from_user
r_int
r_int
id|csum_partial_copy_from_user
(paren
r_const
r_int
r_char
op_star
id|src
comma
r_int
r_char
op_star
id|dst
comma
r_int
id|len
comma
r_int
r_int
id|sum
comma
r_int
op_star
id|err_ptr
)paren
(brace
r_int
id|missing
suffix:semicolon
id|might_sleep
c_func
(paren
)paren
suffix:semicolon
id|missing
op_assign
id|copy_from_user
c_func
(paren
id|dst
comma
id|src
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|missing
)paren
(brace
id|memset
c_func
(paren
id|dst
op_plus
id|len
op_minus
id|missing
comma
l_int|0
comma
id|missing
)paren
suffix:semicolon
op_star
id|err_ptr
op_assign
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
id|csum_partial
c_func
(paren
id|dst
comma
id|len
comma
id|sum
)paren
suffix:semicolon
)brace
eof
