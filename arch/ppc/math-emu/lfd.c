multiline_comment|/* $Id: lfd.c,v 1.1 1999/08/23 19:00:08 cort Exp $&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &quot;sfp-machine.h&quot;
macro_line|#include &quot;double.h&quot;
r_int
DECL|function|lfd
id|lfd
c_func
(paren
r_void
op_star
id|frD
comma
r_void
op_star
id|ea
)paren
(brace
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|frD
comma
id|ea
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
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;%s: D %p, ea %p: &quot;
comma
id|__FUNCTION__
comma
id|frD
comma
id|ea
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
