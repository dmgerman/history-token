macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
r_int
DECL|function|fabs
id|fabs
c_func
(paren
id|u32
op_star
id|frD
comma
id|u32
op_star
id|frB
)paren
(brace
id|frD
(braket
l_int|0
)braket
op_assign
id|frB
(braket
l_int|0
)braket
op_amp
l_int|0x7fffffff
suffix:semicolon
id|frD
(braket
l_int|1
)braket
op_assign
id|frB
(braket
l_int|1
)braket
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
