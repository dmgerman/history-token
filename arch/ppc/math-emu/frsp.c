multiline_comment|/*&n; * BK Id: SCCS/s.frsp.c 1.6 05/17/01 18:14:22 cort&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &quot;soft-fp.h&quot;
macro_line|#include &quot;double.h&quot;
macro_line|#include &quot;single.h&quot;
r_int
DECL|function|frsp
id|frsp
c_func
(paren
r_void
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
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;%s: D %p, B %p&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|frD
comma
id|frB
)paren
suffix:semicolon
macro_line|#endif
id|__FP_UNPACK_D
c_func
(paren
id|B
comma
id|frB
)paren
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;B: %ld %lu %lu %ld (%ld)&bslash;n&quot;
comma
id|B_s
comma
id|B_f1
comma
id|B_f0
comma
id|B_e
comma
id|B_c
)paren
suffix:semicolon
macro_line|#endif
r_return
id|__FP_PACK_DS
c_func
(paren
id|frD
comma
id|B
)paren
suffix:semicolon
)brace
eof
