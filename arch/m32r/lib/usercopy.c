multiline_comment|/*&n; * User address space access functions.&n; * The non inlined parts of asm-m32r/uaccess.h are here.&n; *&n; * Copyright 1997 Andi Kleen &lt;ak@muc.de&gt;&n; * Copyright 1997 Linus Torvalds&n; * Copyright 2001, 2002, 2004 Hirokazu Takata&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/prefetch.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/thread_info.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
r_int
r_int
DECL|function|__generic_copy_to_user
id|__generic_copy_to_user
c_func
(paren
r_void
op_star
id|to
comma
r_const
r_void
op_star
id|from
comma
r_int
r_int
id|n
)paren
(brace
id|prefetch
c_func
(paren
id|from
)paren
suffix:semicolon
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
id|__copy_user
c_func
(paren
id|to
comma
id|from
comma
id|n
)paren
suffix:semicolon
r_return
id|n
suffix:semicolon
)brace
r_int
r_int
DECL|function|__generic_copy_from_user
id|__generic_copy_from_user
c_func
(paren
r_void
op_star
id|to
comma
r_const
r_void
op_star
id|from
comma
r_int
r_int
id|n
)paren
(brace
id|prefetchw
c_func
(paren
id|to
)paren
suffix:semicolon
r_if
c_cond
(paren
id|access_ok
c_func
(paren
id|VERIFY_READ
comma
id|from
comma
id|n
)paren
)paren
id|__copy_user_zeroing
c_func
(paren
id|to
comma
id|from
comma
id|n
)paren
suffix:semicolon
r_else
id|memset
c_func
(paren
id|to
comma
l_int|0
comma
id|n
)paren
suffix:semicolon
r_return
id|n
suffix:semicolon
)brace
multiline_comment|/*&n; * Copy a null terminated string from userspace.&n; */
macro_line|#ifdef CONFIG_ISA_DUAL_ISSUE
DECL|macro|__do_strncpy_from_user
mdefine_line|#define __do_strncpy_from_user(dst,src,count,res)&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;int __d0, __d1, __d2;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;beqz&t;%1, 2f&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.fillinsn&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;0:&t;ldb&t;r14, @%3    ||&t;addi&t;%3, #1&bslash;n&quot;&t;&bslash;&n;&t;&t;&quot;&t;stb&t;r14, @%4    ||&t;addi&t;%4, #1&bslash;n&quot;&t;&bslash;&n;&t;&t;&quot;&t;beqz&t;r14, 1f&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;addi&t;%1, #-1&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;bnez&t;%1, 0b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.fillinsn&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;1:&t;sub&t;%0, %1&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.fillinsn&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;2:&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.balign 4&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;3:&t;seth&t;r14, #high(2b)&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;or3&t;r14, r14, #low(2b)&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;jmp&t;r14&t;    ||&t;ldi&t;%0, #%5&bslash;n&quot;&t;&bslash;&n;&t;&t;&quot;.previous&bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.balign 4&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.long 0b,3b&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.previous&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=r&quot;(res), &quot;=r&quot;(count), &quot;=&amp;r&quot; (__d0), &quot;=&amp;r&quot; (__d1),&t;&bslash;&n;&t;&t;  &quot;=&amp;r&quot; (__d2)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;i&quot;(-EFAULT), &quot;0&quot;(count), &quot;1&quot;(count), &quot;3&quot;(src), &t;&bslash;&n;&t;&t;  &quot;4&quot;(dst)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;r14&quot;, &quot;cbit&quot;, &quot;memory&quot;);&t;&t;&t;&t;&bslash;&n;} while (0)
macro_line|#else /* not CONFIG_ISA_DUAL_ISSUE */
DECL|macro|__do_strncpy_from_user
mdefine_line|#define __do_strncpy_from_user(dst,src,count,res)&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;int __d0, __d1, __d2;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;beqz&t;%1, 2f&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.fillinsn&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;0:&t;ldb&t;r14, @%3&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;stb&t;r14, @%4&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;addi&t;%3, #1&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;addi&t;%4, #1&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;beqz&t;r14, 1f&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;addi&t;%1, #-1&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;bnez&t;%1, 0b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.fillinsn&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;1:&t;sub&t;%0, %1&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.fillinsn&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;2:&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.balign 4&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;3:&t;ldi&t;%0, #%5&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;seth&t;r14, #high(2b)&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;or3&t;r14, r14, #low(2b)&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;jmp&t;r14&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.previous&bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.balign 4&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.long 0b,3b&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.previous&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=r&quot;(res), &quot;=r&quot;(count), &quot;=&amp;r&quot; (__d0), &quot;=&amp;r&quot; (__d1),&t;&bslash;&n;&t;&t;  &quot;=&amp;r&quot; (__d2)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;i&quot;(-EFAULT), &quot;0&quot;(count), &quot;1&quot;(count), &quot;3&quot;(src),&t;&bslash;&n;&t;&t;  &quot;4&quot;(dst)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;r14&quot;, &quot;cbit&quot;, &quot;memory&quot;);&t;&t;&t;&t;&bslash;&n;} while (0)
macro_line|#endif /* CONFIG_ISA_DUAL_ISSUE */
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
macro_line|#ifdef CONFIG_ISA_DUAL_ISSUE
DECL|macro|__do_clear_user
mdefine_line|#define __do_clear_user(addr,size)&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;int __dst, __c;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  &t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;beqz&t;%1, 9f&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;and3&t;r14, %0, #3&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;bnez&t;r14, 2f&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;and3&t;r14, %1, #3&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;bnez&t;r14, 2f&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;and3&t;%1, %1, #3&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;beqz&t;%2, 2f&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;addi&t;%0, #-4&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.fillinsn&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;0:&t;; word clear &bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;st&t;%6, @+%0    ||&t;addi&t;%2, #-1&bslash;n&quot;&t;&bslash;&n;&t;&t;&quot;&t;bnez&t;%2, 0b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;beqz&t;%1, 9f&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.fillinsn&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;2:&t;; byte clear &bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;stb&t;%6, @%0&t;    ||&t;addi&t;%1, #-1&bslash;n&quot;&t;&bslash;&n;&t;&t;&quot;&t;addi&t;%0, #1&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;bnez&t;%1, 2b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.fillinsn&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;9:&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.balign 4&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;4:&t;slli&t;%2, #2&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;seth&t;r14, #high(9b)&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;or3&t;r14, r14, #low(9b)&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;jmp&t;r14&t;    ||&t;add&t;%1, %2&bslash;n&quot;&t;&bslash;&n;&t;&t;&quot;.previous&bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.balign 4&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.long 0b,4b&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.long 2b,9b&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.previous&bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=&amp;r&quot;(__dst), &quot;=&amp;r&quot;(size), &quot;=&amp;r&quot;(__c)&t;&t;&t;&bslash;&n;&t;&t;: &quot;0&quot;(addr), &quot;1&quot;(size), &quot;2&quot;(size / 4), &quot;r&quot;(0)&t;&t;&bslash;&n;&t;&t;: &quot;r14&quot;, &quot;cbit&quot;, &quot;memory&quot;);&t;&t;&t;&t;&bslash;&n;} while (0)
macro_line|#else /* not CONFIG_ISA_DUAL_ISSUE */
DECL|macro|__do_clear_user
mdefine_line|#define __do_clear_user(addr,size)&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;int __dst, __c;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  &t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;beqz&t;%1, 9f&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;and3&t;r14, %0, #3&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;bnez&t;r14, 2f&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;and3&t;r14, %1, #3&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;bnez&t;r14, 2f&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;and3&t;%1, %1, #3&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;beqz&t;%2, 2f&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;addi&t;%0, #-4&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.fillinsn&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;0:&t;st&t;%6, @+%0&t;; word clear &bslash;n&quot;&t;&bslash;&n;&t;&t;&quot;&t;addi&t;%2, #-1&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;bnez&t;%2, 0b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;beqz&t;%1, 9f&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.fillinsn&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;2:&t;stb&t;%6, @%0&t;&t;; byte clear &bslash;n&quot;&t;&bslash;&n;&t;&t;&quot;&t;addi&t;%1, #-1&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;addi&t;%0, #1&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;bnez&t;%1, 2b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.fillinsn&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;9:&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.balign 4&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;4:&t;slli&t;%2, #2&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;add&t;%1, %2&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;seth&t;r14, #high(9b)&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;or3&t;r14, r14, #low(9b)&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;jmp&t;r14&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.previous&bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.balign 4&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.long 0b,4b&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.long 2b,9b&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.previous&bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=&amp;r&quot;(__dst), &quot;=&amp;r&quot;(size), &quot;=&amp;r&quot;(__c)&t;&t;&t;&bslash;&n;&t;&t;: &quot;0&quot;(addr), &quot;1&quot;(size), &quot;2&quot;(size / 4), &quot;r&quot;(0)&t;&t;&bslash;&n;&t;&t;: &quot;r14&quot;, &quot;cbit&quot;, &quot;memory&quot;);&t;&t;&t;&t;&bslash;&n;} while (0)
macro_line|#endif /* not CONFIG_ISA_DUAL_ISSUE */
r_int
r_int
DECL|function|clear_user
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
id|__do_clear_user
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
r_int
r_int
DECL|function|__clear_user
id|__clear_user
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
id|__do_clear_user
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
macro_line|#ifdef CONFIG_ISA_DUAL_ISSUE
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
r_int
id|mask
op_assign
op_minus
id|__addr_ok
c_func
(paren
id|s
)paren
suffix:semicolon
r_int
r_int
id|res
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&t;and&t;%0, %5&t;    ||&t;mv&t;r1, %1&bslash;n&quot;
l_string|&quot;&t;beqz&t;%0, strnlen_exit&bslash;n&quot;
l_string|&quot;&t;and3&t;r0, %1, #3&bslash;n&quot;
l_string|&quot;&t;bnez&t;r0, strnlen_byte_loop&bslash;n&quot;
l_string|&quot;&t;cmpui&t;%0, #4&bslash;n&quot;
l_string|&quot;&t;bc&t;strnlen_byte_loop&bslash;n&quot;
l_string|&quot;strnlen_word_loop:&bslash;n&quot;
l_string|&quot;0:&t;ld&t;r0, @%1+&bslash;n&quot;
l_string|&quot;&t;pcmpbz&t;r0&bslash;n&quot;
l_string|&quot;&t;bc&t;strnlen_last_bytes_fixup&bslash;n&quot;
l_string|&quot;&t;addi&t;%0, #-4&bslash;n&quot;
l_string|&quot;&t;beqz&t;%0, strnlen_exit&bslash;n&quot;
l_string|&quot;&t;bgtz&t;%0, strnlen_word_loop&bslash;n&quot;
l_string|&quot;strnlen_last_bytes:&bslash;n&quot;
l_string|&quot;&t;mv&t;%0, %4&bslash;n&quot;
l_string|&quot;strnlen_last_bytes_fixup:&bslash;n&quot;
l_string|&quot;&t;addi&t;%1, #-4&bslash;n&quot;
l_string|&quot;strnlen_byte_loop:&bslash;n&quot;
l_string|&quot;1:&t;ldb&t;r0, @%1&t;    ||&t;addi&t;%0, #-1&bslash;n&quot;
l_string|&quot;&t;beqz&t;r0, strnlen_exit&bslash;n&quot;
l_string|&quot;&t;addi&t;%1, #1&bslash;n&quot;
l_string|&quot;&t;bnez&t;%0, strnlen_byte_loop&bslash;n&quot;
l_string|&quot;strnlen_exit:&bslash;n&quot;
l_string|&quot;&t;sub&t;%1, r1&bslash;n&quot;
l_string|&quot;&t;add3&t;%0, %1, #1&bslash;n&quot;
l_string|&quot;&t;.fillinsn&bslash;n&quot;
l_string|&quot;9:&bslash;n&quot;
l_string|&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
l_string|&quot;&t;.balign 4&bslash;n&quot;
l_string|&quot;4:&t;addi&t;%1, #-4&bslash;n&quot;
l_string|&quot;&t;.fillinsn&bslash;n&quot;
l_string|&quot;5:&t;seth&t;r1, #high(9b)&bslash;n&quot;
l_string|&quot;&t;or3&t;r1, r1, #low(9b)&bslash;n&quot;
l_string|&quot;&t;jmp&t;r1&t;    ||&t;ldi&t;%0, #0&bslash;n&quot;
l_string|&quot;.previous&bslash;n&quot;
l_string|&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;
l_string|&quot;&t;.balign 4&bslash;n&quot;
l_string|&quot;&t;.long 0b,4b&bslash;n&quot;
l_string|&quot;&t;.long 1b,5b&bslash;n&quot;
l_string|&quot;.previous&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|res
)paren
comma
l_string|&quot;=r&quot;
(paren
id|s
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|n
)paren
comma
l_string|&quot;1&quot;
(paren
id|s
)paren
comma
l_string|&quot;r&quot;
(paren
id|n
op_amp
l_int|3
)paren
comma
l_string|&quot;r&quot;
(paren
id|mask
)paren
comma
l_string|&quot;r&quot;
(paren
l_int|0x01010101
)paren
suffix:colon
l_string|&quot;r0&quot;
comma
l_string|&quot;r1&quot;
comma
l_string|&quot;cbit&quot;
)paren
suffix:semicolon
multiline_comment|/* NOTE: strnlen_user() algorism:&n;&t; * {&n;&t; *   char *p;&n;&t; *   for (p = s; n-- &amp;&amp; *p != &squot;&bslash;0&squot;; ++p)&n;&t; *     ;&n;&t; *   return p - s + 1;&n;&t; * }&n;&t; */
multiline_comment|/* NOTE: If a null char. exists, return 0.&n;&t; * if ((x - 0x01010101) &amp; ~x &amp; 0x80808080)&bslash;n&quot;&n;&t; *   return 0;&bslash;n&quot;&n;&t; */
r_return
id|res
op_amp
id|mask
suffix:semicolon
)brace
macro_line|#else /* not CONFIG_ISA_DUAL_ISSUE */
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
r_int
id|mask
op_assign
op_minus
id|__addr_ok
c_func
(paren
id|s
)paren
suffix:semicolon
r_int
r_int
id|res
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&t;and&t;%0, %5&bslash;n&quot;
l_string|&quot;&t;mv&t;r1, %1&bslash;n&quot;
l_string|&quot;&t;beqz&t;%0, strnlen_exit&bslash;n&quot;
l_string|&quot;&t;and3&t;r0, %1, #3&bslash;n&quot;
l_string|&quot;&t;bnez&t;r0, strnlen_byte_loop&bslash;n&quot;
l_string|&quot;&t;cmpui&t;%0, #4&bslash;n&quot;
l_string|&quot;&t;bc&t;strnlen_byte_loop&bslash;n&quot;
l_string|&quot;&t;sll3&t;r3, %6, #7&bslash;n&quot;
l_string|&quot;strnlen_word_loop:&bslash;n&quot;
l_string|&quot;0:&t;ld&t;r0, @%1+&bslash;n&quot;
l_string|&quot;&t;not&t;r2, r0&bslash;n&quot;
l_string|&quot;&t;sub&t;r0, %6&bslash;n&quot;
l_string|&quot;&t;and&t;r2, r3&bslash;n&quot;
l_string|&quot;&t;and&t;r2, r0&bslash;n&quot;
l_string|&quot;&t;bnez&t;r2, strnlen_last_bytes_fixup&bslash;n&quot;
l_string|&quot;&t;addi&t;%0, #-4&bslash;n&quot;
l_string|&quot;&t;beqz&t;%0, strnlen_exit&bslash;n&quot;
l_string|&quot;&t;bgtz&t;%0, strnlen_word_loop&bslash;n&quot;
l_string|&quot;strnlen_last_bytes:&bslash;n&quot;
l_string|&quot;&t;mv&t;%0, %4&bslash;n&quot;
l_string|&quot;strnlen_last_bytes_fixup:&bslash;n&quot;
l_string|&quot;&t;addi&t;%1, #-4&bslash;n&quot;
l_string|&quot;strnlen_byte_loop:&bslash;n&quot;
l_string|&quot;1:&t;ldb&t;r0, @%1&bslash;n&quot;
l_string|&quot;&t;addi&t;%0, #-1&bslash;n&quot;
l_string|&quot;&t;beqz&t;r0, strnlen_exit&bslash;n&quot;
l_string|&quot;&t;addi&t;%1, #1&bslash;n&quot;
l_string|&quot;&t;bnez&t;%0, strnlen_byte_loop&bslash;n&quot;
l_string|&quot;strnlen_exit:&bslash;n&quot;
l_string|&quot;&t;sub&t;%1, r1&bslash;n&quot;
l_string|&quot;&t;add3&t;%0, %1, #1&bslash;n&quot;
l_string|&quot;&t;.fillinsn&bslash;n&quot;
l_string|&quot;9:&bslash;n&quot;
l_string|&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
l_string|&quot;&t;.balign 4&bslash;n&quot;
l_string|&quot;4:&t;addi&t;%1, #-4&bslash;n&quot;
l_string|&quot;&t;.fillinsn&bslash;n&quot;
l_string|&quot;5:&t;ldi&t;%0, #0&bslash;n&quot;
l_string|&quot;&t;seth&t;r1, #high(9b)&bslash;n&quot;
l_string|&quot;&t;or3&t;r1, r1, #low(9b)&bslash;n&quot;
l_string|&quot;&t;jmp&t;r1&bslash;n&quot;
l_string|&quot;.previous&bslash;n&quot;
l_string|&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;
l_string|&quot;&t;.balign 4&bslash;n&quot;
l_string|&quot;&t;.long 0b,4b&bslash;n&quot;
l_string|&quot;&t;.long 1b,5b&bslash;n&quot;
l_string|&quot;.previous&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|res
)paren
comma
l_string|&quot;=r&quot;
(paren
id|s
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|n
)paren
comma
l_string|&quot;1&quot;
(paren
id|s
)paren
comma
l_string|&quot;r&quot;
(paren
id|n
op_amp
l_int|3
)paren
comma
l_string|&quot;r&quot;
(paren
id|mask
)paren
comma
l_string|&quot;r&quot;
(paren
l_int|0x01010101
)paren
suffix:colon
l_string|&quot;r0&quot;
comma
l_string|&quot;r1&quot;
comma
l_string|&quot;r2&quot;
comma
l_string|&quot;r3&quot;
comma
l_string|&quot;cbit&quot;
)paren
suffix:semicolon
multiline_comment|/* NOTE: strnlen_user() algorism:&n;&t; * {&n;&t; *   char *p;&n;&t; *   for (p = s; n-- &amp;&amp; *p != &squot;&bslash;0&squot;; ++p)&n;&t; *     ;&n;&t; *   return p - s + 1;&n;&t; * }&n;&t; */
multiline_comment|/* NOTE: If a null char. exists, return 0.&n;&t; * if ((x - 0x01010101) &amp; ~x &amp; 0x80808080)&bslash;n&quot;&n;&t; *   return 0;&bslash;n&quot;&n;&t; */
r_return
id|res
op_amp
id|mask
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_ISA_DUAL_ISSUE */
eof
