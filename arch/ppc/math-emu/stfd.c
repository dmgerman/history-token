multiline_comment|/*&n; * BK Id: SCCS/s.stfd.c 1.6 05/17/01 18:14:23 cort&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
r_int
DECL|function|stfd
id|stfd
c_func
(paren
r_void
op_star
id|frS
comma
r_void
op_star
id|ea
)paren
(brace
macro_line|#if 0
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;%s: S %p, ea %p: &quot;
comma
id|__FUNCTION__
comma
id|frS
comma
id|ea
)paren
suffix:semicolon
id|dump_double
c_func
(paren
id|frS
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|ea
comma
id|frS
comma
r_sizeof
(paren
r_float
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
