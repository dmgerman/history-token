multiline_comment|/* $Id: mtfsb0.c,v 1.1 1999/08/23 19:00:16 cort Exp $&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &quot;soft-fp.h&quot;
r_int
DECL|function|mtfsb0
id|mtfsb0
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
op_and_assign
op_complement
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
