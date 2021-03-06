macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/module.h&gt;
DECL|function|__memcpy_toio
r_void
id|__memcpy_toio
c_func
(paren
r_int
r_int
id|dst
comma
r_const
r_void
op_star
id|src
comma
r_int
id|len
)paren
(brace
id|__inline_memcpy
c_func
(paren
(paren
r_void
op_star
)paren
id|dst
comma
id|src
comma
id|len
)paren
suffix:semicolon
)brace
DECL|variable|__memcpy_toio
id|EXPORT_SYMBOL
c_func
(paren
id|__memcpy_toio
)paren
suffix:semicolon
DECL|function|__memcpy_fromio
r_void
id|__memcpy_fromio
c_func
(paren
r_void
op_star
id|dst
comma
r_int
r_int
id|src
comma
r_int
id|len
)paren
(brace
id|__inline_memcpy
c_func
(paren
id|dst
comma
(paren
r_const
r_void
op_star
)paren
id|src
comma
id|len
)paren
suffix:semicolon
)brace
DECL|variable|__memcpy_fromio
id|EXPORT_SYMBOL
c_func
(paren
id|__memcpy_fromio
)paren
suffix:semicolon
DECL|function|memset_io
r_void
id|memset_io
c_func
(paren
r_volatile
r_void
id|__iomem
op_star
id|a
comma
r_int
id|b
comma
r_int
id|c
)paren
(brace
multiline_comment|/* XXX: memset can mangle the IO patterns quite a bit.&n;&t;   perhaps it would be better to use a dumb one */
id|memset
c_func
(paren
(paren
r_void
op_star
)paren
id|a
comma
id|b
comma
id|c
)paren
suffix:semicolon
)brace
DECL|variable|memset_io
id|EXPORT_SYMBOL
c_func
(paren
id|memset_io
)paren
suffix:semicolon
eof
