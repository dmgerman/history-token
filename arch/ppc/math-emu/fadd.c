macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &quot;soft-fp.h&quot;
macro_line|#include &quot;double.h&quot;
r_int
DECL|function|fadd
id|fadd
c_func
(paren
r_void
op_star
id|frD
comma
r_void
op_star
id|frA
comma
r_void
op_star
id|frB
)paren
(brace
id|FP_DECL_D
c_func
(paren
id|A
)paren
suffix:semicolon
id|FP_DECL_D
c_func
(paren
id|B
)paren
suffix:semicolon
id|FP_DECL_D
c_func
(paren
id|R
)paren
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;%s: %p %p %p&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|frD
comma
id|frA
comma
id|frB
)paren
suffix:semicolon
macro_line|#endif
id|__FP_UNPACK_D
c_func
(paren
id|A
comma
id|frA
)paren
suffix:semicolon
id|__FP_UNPACK_D
c_func
(paren
id|B
comma
id|frB
)paren
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;A: %ld %lu %lu %ld (%ld)&bslash;n&quot;
comma
id|A_s
comma
id|A_f1
comma
id|A_f0
comma
id|A_e
comma
id|A_c
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;B: %ld %lu %lu %ld (%ld)&bslash;n&quot;
comma
id|B_s
comma
id|B_f1
comma
id|B_f0
comma
id|B_e
comma
id|B_c
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|A_s
op_ne
id|B_s
op_logical_and
id|A_c
op_eq
id|FP_CLS_INF
op_logical_and
id|B_c
op_eq
id|FP_CLS_INF
)paren
id|ret
op_or_assign
id|EFLAG_VXISI
suffix:semicolon
id|FP_ADD_D
c_func
(paren
id|R
comma
id|A
comma
id|B
)paren
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;D: %ld %lu %lu %ld (%ld)&bslash;n&quot;
comma
id|R_s
comma
id|R_f1
comma
id|R_f0
comma
id|R_e
comma
id|R_c
)paren
suffix:semicolon
macro_line|#endif
r_return
(paren
id|ret
op_or
id|__FP_PACK_D
c_func
(paren
id|frD
comma
id|R
)paren
)paren
suffix:semicolon
)brace
eof
