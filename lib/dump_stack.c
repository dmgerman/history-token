multiline_comment|/*&n; * Provide a default dump_stack() function for architectures&n; * which don&squot;t implement their own.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
DECL|function|dump_stack
r_void
id|dump_stack
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;This architecture does not implement dump_stack()&bslash;n&quot;
)paren
suffix:semicolon
)brace
eof
