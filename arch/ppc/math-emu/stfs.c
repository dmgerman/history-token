macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &quot;soft-fp.h&quot;
macro_line|#include &quot;double.h&quot;
macro_line|#include &quot;single.h&quot;
r_int
DECL|function|stfs
id|stfs
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
id|FP_DECL_D
c_func
(paren
id|A
)paren
suffix:semicolon
id|FP_DECL_S
c_func
(paren
id|R
)paren
suffix:semicolon
r_float
id|f
suffix:semicolon
r_int
id|err
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;%s: S %p, ea %p&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|frS
comma
id|ea
)paren
suffix:semicolon
macro_line|#endif
id|__FP_UNPACK_D
c_func
(paren
id|A
comma
id|frS
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
macro_line|#endif
id|FP_CONV
c_func
(paren
id|S
comma
id|D
comma
l_int|1
comma
l_int|2
comma
id|R
comma
id|A
)paren
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;R: %ld %lu %ld (%ld)&bslash;n&quot;
comma
id|R_s
comma
id|R_f
comma
id|R_e
comma
id|R_c
)paren
suffix:semicolon
macro_line|#endif
id|err
op_assign
id|_FP_PACK_CANONICAL
c_func
(paren
id|S
comma
l_int|1
comma
id|R
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|err
op_logical_or
op_logical_neg
id|__FPU_TRAP_P
c_func
(paren
id|err
)paren
)paren
(brace
id|__FP_PACK_RAW_1
c_func
(paren
id|S
comma
op_amp
id|f
comma
id|R
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|ea
comma
op_amp
id|f
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
)brace
r_return
id|err
suffix:semicolon
)brace
eof
