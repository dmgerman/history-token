multiline_comment|/* $Id: mffs.c,v 1.1 1999/08/23 19:00:14 cort Exp $&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &quot;soft-fp.h&quot;
r_int
DECL|function|mffs
id|mffs
c_func
(paren
id|u32
op_star
id|frD
)paren
(brace
id|frD
(braket
l_int|1
)braket
op_assign
id|__FPU_FPSCR
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;%s: frD %p: %08x.%08x&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|frD
comma
id|frD
(braket
l_int|0
)braket
comma
id|frD
(braket
l_int|1
)braket
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
eof
