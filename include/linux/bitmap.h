macro_line|#ifndef __LINUX_BITMAP_H
DECL|macro|__LINUX_BITMAP_H
mdefine_line|#define __LINUX_BITMAP_H
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/compiler.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/bitops.h&gt;
macro_line|#include &lt;linux/string.h&gt;
r_int
id|bitmap_empty
c_func
(paren
r_const
r_int
r_int
op_star
id|bitmap
comma
r_int
id|bits
)paren
suffix:semicolon
r_int
id|bitmap_full
c_func
(paren
r_const
r_int
r_int
op_star
id|bitmap
comma
r_int
id|bits
)paren
suffix:semicolon
r_int
id|bitmap_equal
c_func
(paren
r_const
r_int
r_int
op_star
id|bitmap1
comma
r_int
r_int
op_star
id|bitmap2
comma
r_int
id|bits
)paren
suffix:semicolon
r_void
id|bitmap_complement
c_func
(paren
r_int
r_int
op_star
id|bitmap
comma
r_int
id|bits
)paren
suffix:semicolon
DECL|function|bitmap_clear
r_static
r_inline
r_void
id|bitmap_clear
c_func
(paren
r_int
r_int
op_star
id|bitmap
comma
r_int
id|bits
)paren
(brace
id|CLEAR_BITMAP
c_func
(paren
(paren
r_int
r_int
op_star
)paren
id|bitmap
comma
id|bits
)paren
suffix:semicolon
)brace
DECL|function|bitmap_fill
r_static
r_inline
r_void
id|bitmap_fill
c_func
(paren
r_int
r_int
op_star
id|bitmap
comma
r_int
id|bits
)paren
(brace
id|memset
c_func
(paren
id|bitmap
comma
l_int|0xff
comma
id|BITS_TO_LONGS
c_func
(paren
id|bits
)paren
op_star
r_sizeof
(paren
r_int
r_int
)paren
)paren
suffix:semicolon
)brace
DECL|function|bitmap_copy
r_static
r_inline
r_void
id|bitmap_copy
c_func
(paren
r_int
r_int
op_star
id|dst
comma
r_const
r_int
r_int
op_star
id|src
comma
r_int
id|bits
)paren
(brace
id|memcpy
c_func
(paren
id|dst
comma
id|src
comma
id|BITS_TO_LONGS
c_func
(paren
id|bits
)paren
op_star
r_sizeof
(paren
r_int
r_int
)paren
)paren
suffix:semicolon
)brace
r_void
id|bitmap_shift_right
c_func
(paren
r_int
r_int
op_star
id|dst
comma
r_const
r_int
r_int
op_star
id|src
comma
r_int
id|shift
comma
r_int
id|bits
)paren
suffix:semicolon
r_void
id|bitmap_shift_left
c_func
(paren
r_int
r_int
op_star
id|dst
comma
r_const
r_int
r_int
op_star
id|src
comma
r_int
id|shift
comma
r_int
id|bits
)paren
suffix:semicolon
r_void
id|bitmap_and
c_func
(paren
r_int
r_int
op_star
id|dst
comma
r_const
r_int
r_int
op_star
id|bitmap1
comma
r_const
r_int
r_int
op_star
id|bitmap2
comma
r_int
id|bits
)paren
suffix:semicolon
r_void
id|bitmap_or
c_func
(paren
r_int
r_int
op_star
id|dst
comma
r_const
r_int
r_int
op_star
id|bitmap1
comma
r_const
r_int
r_int
op_star
id|bitmap2
comma
r_int
id|bits
)paren
suffix:semicolon
r_int
id|bitmap_weight
c_func
(paren
r_const
r_int
r_int
op_star
id|bitmap
comma
r_int
id|bits
)paren
suffix:semicolon
r_int
id|bitmap_scnprintf
c_func
(paren
r_char
op_star
id|buf
comma
r_int
r_int
id|buflen
comma
r_const
r_int
r_int
op_star
id|maskp
comma
r_int
id|bits
)paren
suffix:semicolon
r_int
id|bitmap_parse
c_func
(paren
r_const
r_char
id|__user
op_star
id|ubuf
comma
r_int
r_int
id|ubuflen
comma
r_int
r_int
op_star
id|maskp
comma
r_int
id|bits
)paren
suffix:semicolon
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#endif /* __LINUX_BITMAP_H */
eof
