multiline_comment|/*&n; * BK Id: SCCS/s.fres.c 1.6 05/17/01 18:14:22 cort&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
r_int
DECL|function|fres
id|fres
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
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;%s: %p %p&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|frD
comma
id|frB
)paren
suffix:semicolon
macro_line|#endif
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
eof
