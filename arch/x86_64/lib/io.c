macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/module.h&gt;
DECL|function|memcpy_toio
r_void
op_star
id|memcpy_toio
c_func
(paren
r_void
op_star
id|dst
comma
r_void
op_star
id|src
comma
r_int
id|len
)paren
(brace
r_return
id|__inline_memcpy
c_func
(paren
id|__io_virt
c_func
(paren
id|dst
)paren
comma
id|src
comma
id|len
)paren
suffix:semicolon
)brace
DECL|function|memcpy_fromio
r_void
op_star
id|memcpy_fromio
c_func
(paren
r_void
op_star
id|dst
comma
r_void
op_star
id|src
comma
r_int
id|len
)paren
(brace
r_return
id|__inline_memcpy
c_func
(paren
id|dst
comma
id|__io_virt
c_func
(paren
id|src
)paren
comma
id|len
)paren
suffix:semicolon
)brace
DECL|variable|memcpy_toio
id|EXPORT_SYMBOL
c_func
(paren
id|memcpy_toio
)paren
suffix:semicolon
DECL|variable|memcpy_fromio
id|EXPORT_SYMBOL
c_func
(paren
id|memcpy_fromio
)paren
suffix:semicolon
eof
