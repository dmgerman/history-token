multiline_comment|/* $Id: fctiw.c,v 1.1 1999/08/23 18:59:30 cort Exp $&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &quot;soft-fp.h&quot;
macro_line|#include &quot;double.h&quot;
r_int
DECL|function|fctiw
id|fctiw
c_func
(paren
id|u32
op_star
id|frD
comma
r_void
op_star
id|frB
)paren
(brace
id|FP_DECL_D
c_func
(paren
id|B
)paren
suffix:semicolon
r_int
r_int
id|r
suffix:semicolon
id|__FP_UNPACK_D
c_func
(paren
id|B
comma
id|frB
)paren
suffix:semicolon
id|FP_TO_INT_D
c_func
(paren
id|r
comma
id|B
comma
l_int|32
comma
l_int|1
)paren
suffix:semicolon
id|frD
(braket
l_int|1
)braket
op_assign
id|r
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;%s: D %p, B %p: &quot;
comma
id|__FUNCTION__
comma
id|frD
comma
id|frB
)paren
suffix:semicolon
id|dump_double
c_func
(paren
id|frD
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
eof
