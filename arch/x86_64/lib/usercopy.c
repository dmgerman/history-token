multiline_comment|/* &n; * User address space access functions.&n; *&n; * Copyright 1997 Andi Kleen &lt;ak@muc.de&gt;&n; * Copyright 1997 Linus Torvalds&n; * Copyright 2002 Andi Kleen &lt;ak@suse.de&gt;&n; */
macro_line|#include &lt;asm/uaccess.h&gt;
multiline_comment|/*&n; * Copy a null terminated string from userspace.&n; */
DECL|macro|__do_strncpy_from_user
mdefine_line|#define __do_strncpy_from_user(dst,src,count,res)&t;&t;&t;   &bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;   &bslash;&n;&t;long __d0, __d1, __d2;&t;&t;&t;&t;&t;&t;   &bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;&t;testq %1,%1&bslash;n&quot;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;&t;jz 2f&bslash;n&quot;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;0:&t;lodsb&bslash;n&quot;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;&t;stosb&bslash;n&quot;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;&t;testb %%al,%%al&bslash;n&quot;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;&t;jz 1f&bslash;n&quot;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;&t;decq %1&bslash;n&quot;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;&t;jnz 0b&bslash;n&quot;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;1:&t;subq %1,%0&bslash;n&quot;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;2:&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;3:&t;movq %5,%0&bslash;n&quot;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;&t;jmp 2b&bslash;n&quot;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;.previous&bslash;n&quot;&t;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;&t;.align 8&bslash;n&quot;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;&t;.quad 0b,3b&bslash;n&quot;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;.previous&quot;&t;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;: &quot;=r&quot;(res), &quot;=c&quot;(count), &quot;=&amp;a&quot; (__d0), &quot;=&amp;S&quot; (__d1),&t;   &bslash;&n;&t;&t;  &quot;=&amp;D&quot; (__d2)&t;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;: &quot;i&quot;(-EFAULT), &quot;0&quot;(count), &quot;1&quot;(count), &quot;3&quot;(src), &quot;4&quot;(dst) &bslash;&n;&t;&t;: &quot;memory&quot;);&t;&t;&t;&t;&t;&t;   &bslash;&n;} while (0)
r_int
DECL|function|__strncpy_from_user
id|__strncpy_from_user
c_func
(paren
r_char
op_star
id|dst
comma
r_const
r_char
op_star
id|src
comma
r_int
id|count
)paren
(brace
r_int
id|res
suffix:semicolon
id|__do_strncpy_from_user
c_func
(paren
id|dst
comma
id|src
comma
id|count
comma
id|res
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
r_int
DECL|function|strncpy_from_user
id|strncpy_from_user
c_func
(paren
r_char
op_star
id|dst
comma
r_const
r_char
op_star
id|src
comma
r_int
id|count
)paren
(brace
r_int
id|res
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|access_ok
c_func
(paren
id|VERIFY_READ
comma
id|src
comma
l_int|1
)paren
)paren
id|__do_strncpy_from_user
c_func
(paren
id|dst
comma
id|src
comma
id|count
comma
id|res
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
multiline_comment|/*&n; * Zero Userspace&n; */
DECL|function|__clear_user
r_int
r_int
id|__clear_user
c_func
(paren
r_void
op_star
id|addr
comma
r_int
r_int
id|size
)paren
(brace
r_int
id|__d0
suffix:semicolon
multiline_comment|/* no memory constraint because it doesn&squot;t change any memory gcc knows&n;&t;   about */
id|asm
r_volatile
(paren
l_string|&quot;&t;testq  %[size8],%[size8]&bslash;n&quot;
l_string|&quot;&t;jz     4f&bslash;n&quot;
l_string|&quot;0:&t;movnti %[zero],(%[dst])&bslash;n&quot;
l_string|&quot;&t;addq   %[eight],%[dst]&bslash;n&quot;
l_string|&quot;&t;decl %%ecx ; jnz   0b&bslash;n&quot;
l_string|&quot;4:&t;movq  %[size1],%%rcx&bslash;n&quot;
l_string|&quot;&t;testl %%ecx,%%ecx&bslash;n&quot;
l_string|&quot;&t;jz     2f&bslash;n&quot;
l_string|&quot;1:&t;movb   %b[zero],(%[dst])&bslash;n&quot;
l_string|&quot;&t;incq   %[dst]&bslash;n&quot;
l_string|&quot;&t;decl %%ecx ; jnz  1b&bslash;n&quot;
l_string|&quot;2:&t;sfence&bslash;n&quot;
l_string|&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
l_string|&quot;3:&t;lea 0(%[size1],%[size8],8),%[size8]&bslash;n&quot;
l_string|&quot;&t;jmp 2b&bslash;n&quot;
l_string|&quot;.previous&bslash;n&quot;
l_string|&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;
l_string|&quot;       .align 8&bslash;n&quot;
l_string|&quot;&t;.quad 0b,3b&bslash;n&quot;
l_string|&quot;&t;.quad 1b,2b&bslash;n&quot;
l_string|&quot;.previous&quot;
suffix:colon
(braket
id|size8
)braket
l_string|&quot;=c&quot;
(paren
id|size
)paren
comma
(braket
id|dst
)braket
l_string|&quot;=&amp;D&quot;
(paren
id|__d0
)paren
suffix:colon
(braket
id|size1
)braket
l_string|&quot;r&quot;
(paren
id|size
op_amp
l_int|7
)paren
comma
l_string|&quot;[size8]&quot;
(paren
id|size
op_div
l_int|8
)paren
comma
l_string|&quot;[dst] &quot;
(paren
id|addr
)paren
comma
(braket
id|zero
)braket
l_string|&quot;r&quot;
(paren
l_int|0UL
)paren
comma
(braket
id|eight
)braket
l_string|&quot;r&quot;
(paren
l_int|8UL
)paren
)paren
suffix:semicolon
r_return
id|size
suffix:semicolon
)brace
DECL|function|clear_user
r_int
r_int
id|clear_user
c_func
(paren
r_void
op_star
id|to
comma
r_int
r_int
id|n
)paren
(brace
r_if
c_cond
(paren
id|access_ok
c_func
(paren
id|VERIFY_WRITE
comma
id|to
comma
id|n
)paren
)paren
r_return
id|__clear_user
c_func
(paren
id|to
comma
id|n
)paren
suffix:semicolon
r_return
id|n
suffix:semicolon
)brace
multiline_comment|/*&n; * Return the size of a string (including the ending 0)&n; *&n; * Return 0 on exception, a value greater than N if too long&n; */
DECL|function|strnlen_user
r_int
id|strnlen_user
c_func
(paren
r_const
r_char
op_star
id|s
comma
r_int
id|n
)paren
(brace
r_int
id|res
op_assign
l_int|0
suffix:semicolon
r_char
id|c
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|access_ok
c_func
(paren
id|VERIFY_READ
comma
id|s
comma
id|n
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|res
OG
id|n
)paren
r_return
id|n
op_plus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|__get_user
c_func
(paren
id|c
comma
id|s
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|c
)paren
r_return
id|res
op_plus
l_int|1
suffix:semicolon
id|res
op_increment
suffix:semicolon
id|s
op_increment
suffix:semicolon
)brace
)brace
DECL|function|strlen_user
r_int
id|strlen_user
c_func
(paren
r_const
r_char
op_star
id|s
)paren
(brace
r_int
id|res
op_assign
l_int|0
suffix:semicolon
r_char
id|c
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|c
comma
id|s
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|c
)paren
r_return
id|res
op_plus
l_int|1
suffix:semicolon
id|res
op_increment
suffix:semicolon
id|s
op_increment
suffix:semicolon
)brace
)brace
eof
