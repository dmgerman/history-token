multiline_comment|/*&n; * BK Id: SCCS/s.stfiwx.c 1.6 05/17/01 18:14:23 cort&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
r_int
DECL|function|stfiwx
id|stfiwx
c_func
(paren
id|u32
op_star
id|frS
comma
r_void
op_star
id|ea
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
id|frS
comma
id|ea
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|ea
comma
op_amp
id|frS
(braket
l_int|1
)braket
comma
r_sizeof
(paren
id|frS
(braket
l_int|1
)braket
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
