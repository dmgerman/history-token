multiline_comment|/*&n; * BK Id: SCCS/s.mtfsb1.c 1.6 05/17/01 18:14:23 cort&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &quot;soft-fp.h&quot;
r_int
DECL|function|mtfsb1
id|mtfsb1
c_func
(paren
r_int
id|crbD
)paren
(brace
r_if
c_cond
(paren
(paren
id|crbD
op_ne
l_int|1
)paren
op_logical_and
(paren
id|crbD
op_ne
l_int|2
)paren
)paren
id|__FPU_FPSCR
op_or_assign
(paren
l_int|1
op_lshift
(paren
l_int|31
op_minus
id|crbD
)paren
)paren
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;%s: %d %08lx&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|crbD
comma
id|__FPU_FPSCR
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
eof
