macro_line|#include &quot;asm/uaccess.h&quot;
macro_line|#include &quot;linux/errno.h&quot;
macro_line|#include &quot;linux/module.h&quot;
r_extern
r_int
r_int
id|arch_csum_partial
c_func
(paren
r_const
r_char
op_star
id|buff
comma
r_int
id|len
comma
r_int
id|sum
)paren
suffix:semicolon
DECL|function|csum_partial
r_extern
r_int
r_int
id|csum_partial
c_func
(paren
r_char
op_star
id|buff
comma
r_int
id|len
comma
r_int
id|sum
)paren
(brace
r_return
id|arch_csum_partial
c_func
(paren
id|buff
comma
id|len
comma
id|sum
)paren
suffix:semicolon
)brace
DECL|variable|csum_partial
id|EXPORT_SYMBOL
c_func
(paren
id|csum_partial
)paren
suffix:semicolon
DECL|function|csum_partial_copy_to
r_int
r_int
id|csum_partial_copy_to
c_func
(paren
r_const
r_char
op_star
id|src
comma
r_char
op_star
id|dst
comma
r_int
id|len
comma
r_int
id|sum
comma
r_int
op_star
id|err_ptr
)paren
(brace
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|dst
comma
id|src
comma
id|len
)paren
)paren
(brace
op_star
id|err_ptr
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_return
id|arch_csum_partial
c_func
(paren
id|src
comma
id|len
comma
id|sum
)paren
suffix:semicolon
)brace
DECL|function|csum_partial_copy_from
r_int
r_int
id|csum_partial_copy_from
c_func
(paren
r_const
r_char
op_star
id|src
comma
r_char
op_star
id|dst
comma
r_int
id|len
comma
r_int
id|sum
comma
r_int
op_star
id|err_ptr
)paren
(brace
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|dst
comma
id|src
comma
id|len
)paren
)paren
(brace
op_star
id|err_ptr
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_return
id|arch_csum_partial
c_func
(paren
id|dst
comma
id|len
comma
id|sum
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
