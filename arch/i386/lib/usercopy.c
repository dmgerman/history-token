multiline_comment|/* &n; * User address space access functions.&n; * The non inlined parts of asm-i386/uaccess.h are here.&n; *&n; * Copyright 1997 Andi Kleen &lt;ak@muc.de&gt;&n; * Copyright 1997 Linus Torvalds&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/mmx.h&gt;
DECL|function|movsl_is_ok
r_static
r_inline
r_int
id|movsl_is_ok
c_func
(paren
r_const
r_void
op_star
id|a1
comma
r_const
r_void
op_star
id|a2
comma
r_int
r_int
id|n
)paren
(brace
macro_line|#ifdef CONFIG_X86_INTEL_USERCOPY
r_if
c_cond
(paren
id|n
op_ge
l_int|64
op_logical_and
(paren
(paren
(paren
r_const
r_int
)paren
id|a1
op_xor
(paren
r_const
r_int
)paren
id|a2
)paren
op_amp
id|movsl_mask.mask
)paren
)paren
r_return
l_int|0
suffix:semicolon
macro_line|#endif
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * Copy a null terminated string from userspace.&n; */
DECL|macro|__do_strncpy_from_user
mdefine_line|#define __do_strncpy_from_user(dst,src,count,res)&t;&t;&t;   &bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;   &bslash;&n;&t;int __d0, __d1, __d2;&t;&t;&t;&t;&t;&t;   &bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;&t;testl %1,%1&bslash;n&quot;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;&t;jz 2f&bslash;n&quot;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;0:&t;lodsb&bslash;n&quot;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;&t;stosb&bslash;n&quot;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;&t;testb %%al,%%al&bslash;n&quot;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;&t;jz 1f&bslash;n&quot;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;&t;decl %1&bslash;n&quot;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;&t;jnz 0b&bslash;n&quot;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;1:&t;subl %1,%0&bslash;n&quot;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;2:&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;3:&t;movl %5,%0&bslash;n&quot;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;&t;jmp 2b&bslash;n&quot;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;.previous&bslash;n&quot;&t;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;&t;.align 4&bslash;n&quot;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;&t;.long 0b,3b&bslash;n&quot;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;.previous&quot;&t;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;: &quot;=d&quot;(res), &quot;=c&quot;(count), &quot;=&amp;a&quot; (__d0), &quot;=&amp;S&quot; (__d1),&t;   &bslash;&n;&t;&t;  &quot;=&amp;D&quot; (__d2)&t;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;: &quot;i&quot;(-EFAULT), &quot;0&quot;(count), &quot;1&quot;(count), &quot;3&quot;(src), &quot;4&quot;(dst) &bslash;&n;&t;&t;: &quot;memory&quot;);&t;&t;&t;&t;&t;&t;   &bslash;&n;} while (0)
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
DECL|macro|__do_clear_user
mdefine_line|#define __do_clear_user(addr,size)&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;int __d0;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  &t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;0:&t;rep; stosl&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;movl %2,%0&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;1:&t;rep; stosb&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;2:&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;3:&t;lea 0(%2,%0,4),%0&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;jmp 2b&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.previous&bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.align 4&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.long 0b,3b&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.long 1b,2b&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.previous&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=&amp;c&quot;(size), &quot;=&amp;D&quot; (__d0)&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;r&quot;(size &amp; 3), &quot;0&quot;(size / 4), &quot;1&quot;(addr), &quot;a&quot;(0));&t;&bslash;&n;} while (0)
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
comma
id|tmp
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&t;testl %0, %0&bslash;n&quot;
l_string|&quot;&t;jz 3f&bslash;n&quot;
l_string|&quot;&t;andl %0,%%ecx&bslash;n&quot;
l_string|&quot;0:&t;repne; scasb&bslash;n&quot;
l_string|&quot;&t;setne %%al&bslash;n&quot;
l_string|&quot;&t;subl %%ecx,%0&bslash;n&quot;
l_string|&quot;&t;addl %0,%%eax&bslash;n&quot;
l_string|&quot;1:&bslash;n&quot;
l_string|&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
l_string|&quot;2:&t;xorl %%eax,%%eax&bslash;n&quot;
l_string|&quot;&t;jmp 1b&bslash;n&quot;
l_string|&quot;3:&t;movb $1,%%al&bslash;n&quot;
l_string|&quot;&t;jmp 1b&bslash;n&quot;
l_string|&quot;.previous&bslash;n&quot;
l_string|&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;
l_string|&quot;&t;.align 4&bslash;n&quot;
l_string|&quot;&t;.long 0b,2b&bslash;n&quot;
l_string|&quot;.previous&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|n
)paren
comma
l_string|&quot;=D&quot;
(paren
id|s
)paren
comma
l_string|&quot;=a&quot;
(paren
id|res
)paren
comma
l_string|&quot;=c&quot;
(paren
id|tmp
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
l_string|&quot;2&quot;
(paren
l_int|0
)paren
comma
l_string|&quot;3&quot;
(paren
id|mask
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_return
id|res
op_amp
id|mask
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_X86_INTEL_USERCOPY
r_static
r_int
r_int
DECL|function|__copy_user_intel
id|__copy_user_intel
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
id|size
)paren
(brace
r_int
id|d0
comma
id|d1
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;       .align 2,0x90&bslash;n&quot;
l_string|&quot;0:     movl 32(%4), %%eax&bslash;n&quot;
l_string|&quot;       cmpl $67, %0&bslash;n&quot;
l_string|&quot;       jbe 1f&bslash;n&quot;
l_string|&quot;       movl 64(%4), %%eax&bslash;n&quot;
l_string|&quot;       .align 2,0x90&bslash;n&quot;
l_string|&quot;1:     movl 0(%4), %%eax&bslash;n&quot;
l_string|&quot;       movl 4(%4), %%edx&bslash;n&quot;
l_string|&quot;2:     movl %%eax, 0(%3)&bslash;n&quot;
l_string|&quot;21:    movl %%edx, 4(%3)&bslash;n&quot;
l_string|&quot;       movl 8(%4), %%eax&bslash;n&quot;
l_string|&quot;       movl 12(%4),%%edx&bslash;n&quot;
l_string|&quot;3:     movl %%eax, 8(%3)&bslash;n&quot;
l_string|&quot;31:    movl %%edx, 12(%3)&bslash;n&quot;
l_string|&quot;       movl 16(%4), %%eax&bslash;n&quot;
l_string|&quot;       movl 20(%4), %%edx&bslash;n&quot;
l_string|&quot;4:     movl %%eax, 16(%3)&bslash;n&quot;
l_string|&quot;41:    movl %%edx, 20(%3)&bslash;n&quot;
l_string|&quot;       movl 24(%4), %%eax&bslash;n&quot;
l_string|&quot;       movl 28(%4), %%edx&bslash;n&quot;
l_string|&quot;10:    movl %%eax, 24(%3)&bslash;n&quot;
l_string|&quot;51:    movl %%edx, 28(%3)&bslash;n&quot;
l_string|&quot;       movl 32(%4), %%eax&bslash;n&quot;
l_string|&quot;       movl 36(%4), %%edx&bslash;n&quot;
l_string|&quot;11:    movl %%eax, 32(%3)&bslash;n&quot;
l_string|&quot;61:    movl %%edx, 36(%3)&bslash;n&quot;
l_string|&quot;       movl 40(%4), %%eax&bslash;n&quot;
l_string|&quot;       movl 44(%4), %%edx&bslash;n&quot;
l_string|&quot;12:    movl %%eax, 40(%3)&bslash;n&quot;
l_string|&quot;71:    movl %%edx, 44(%3)&bslash;n&quot;
l_string|&quot;       movl 48(%4), %%eax&bslash;n&quot;
l_string|&quot;       movl 52(%4), %%edx&bslash;n&quot;
l_string|&quot;13:    movl %%eax, 48(%3)&bslash;n&quot;
l_string|&quot;81:    movl %%edx, 52(%3)&bslash;n&quot;
l_string|&quot;       movl 56(%4), %%eax&bslash;n&quot;
l_string|&quot;       movl 60(%4), %%edx&bslash;n&quot;
l_string|&quot;14:    movl %%eax, 56(%3)&bslash;n&quot;
l_string|&quot;91:    movl %%edx, 60(%3)&bslash;n&quot;
l_string|&quot;       addl $-64, %0&bslash;n&quot;
l_string|&quot;       addl $64, %4&bslash;n&quot;
l_string|&quot;       addl $64, %3&bslash;n&quot;
l_string|&quot;       cmpl $63, %0&bslash;n&quot;
l_string|&quot;       ja  0b&bslash;n&quot;
l_string|&quot;5:     movl  %0, %%eax&bslash;n&quot;
l_string|&quot;       shrl  $2, %0&bslash;n&quot;
l_string|&quot;       andl  $3, %%eax&bslash;n&quot;
l_string|&quot;       cld&bslash;n&quot;
l_string|&quot;6:     rep; movsl&bslash;n&quot;
l_string|&quot;       movl %%eax, %0&bslash;n&quot;
l_string|&quot;7:     rep; movsb&bslash;n&quot;
l_string|&quot;8:&bslash;n&quot;
l_string|&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
l_string|&quot;9:     lea 0(%%eax,%0,4),%0&bslash;n&quot;
l_string|&quot;       jmp 8b&bslash;n&quot;
l_string|&quot;.previous&bslash;n&quot;
l_string|&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;
l_string|&quot;       .align 4&bslash;n&quot;
l_string|&quot;       .long 2b,8b&bslash;n&quot;
l_string|&quot;       .long 21b,8b&bslash;n&quot;
l_string|&quot;       .long 3b,8b&bslash;n&quot;
l_string|&quot;       .long 31b,8b&bslash;n&quot;
l_string|&quot;       .long 4b,8b&bslash;n&quot;
l_string|&quot;       .long 41b,8b&bslash;n&quot;
l_string|&quot;       .long 10b,8b&bslash;n&quot;
l_string|&quot;       .long 51b,8b&bslash;n&quot;
l_string|&quot;       .long 11b,8b&bslash;n&quot;
l_string|&quot;       .long 61b,8b&bslash;n&quot;
l_string|&quot;       .long 12b,8b&bslash;n&quot;
l_string|&quot;       .long 71b,8b&bslash;n&quot;
l_string|&quot;       .long 13b,8b&bslash;n&quot;
l_string|&quot;       .long 81b,8b&bslash;n&quot;
l_string|&quot;       .long 14b,8b&bslash;n&quot;
l_string|&quot;       .long 91b,8b&bslash;n&quot;
l_string|&quot;       .long 6b,9b&bslash;n&quot;
l_string|&quot;       .long 7b,8b&bslash;n&quot;
l_string|&quot;.previous&quot;
suffix:colon
l_string|&quot;=&amp;c&quot;
(paren
id|size
)paren
comma
l_string|&quot;=&amp;D&quot;
(paren
id|d0
)paren
comma
l_string|&quot;=&amp;S&quot;
(paren
id|d1
)paren
suffix:colon
l_string|&quot;1&quot;
(paren
id|to
)paren
comma
l_string|&quot;2&quot;
(paren
id|from
)paren
comma
l_string|&quot;0&quot;
(paren
id|size
)paren
suffix:colon
l_string|&quot;eax&quot;
comma
l_string|&quot;edx&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|size
suffix:semicolon
)brace
r_static
r_int
r_int
DECL|function|__copy_user_zeroing_intel
id|__copy_user_zeroing_intel
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
id|size
)paren
(brace
r_int
id|d0
comma
id|d1
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;        .align 2,0x90&bslash;n&quot;
l_string|&quot;0:      movl 32(%4), %%eax&bslash;n&quot;
l_string|&quot;        cmpl $67, %0&bslash;n&quot;
l_string|&quot;        jbe 2f&bslash;n&quot;
l_string|&quot;1:      movl 64(%4), %%eax&bslash;n&quot;
l_string|&quot;        .align 2,0x90&bslash;n&quot;
l_string|&quot;2:      movl 0(%4), %%eax&bslash;n&quot;
l_string|&quot;21:     movl 4(%4), %%edx&bslash;n&quot;
l_string|&quot;        movl %%eax, 0(%3)&bslash;n&quot;
l_string|&quot;        movl %%edx, 4(%3)&bslash;n&quot;
l_string|&quot;3:      movl 8(%4), %%eax&bslash;n&quot;
l_string|&quot;31:     movl 12(%4),%%edx&bslash;n&quot;
l_string|&quot;        movl %%eax, 8(%3)&bslash;n&quot;
l_string|&quot;        movl %%edx, 12(%3)&bslash;n&quot;
l_string|&quot;4:      movl 16(%4), %%eax&bslash;n&quot;
l_string|&quot;41:     movl 20(%4), %%edx&bslash;n&quot;
l_string|&quot;        movl %%eax, 16(%3)&bslash;n&quot;
l_string|&quot;        movl %%edx, 20(%3)&bslash;n&quot;
l_string|&quot;10:     movl 24(%4), %%eax&bslash;n&quot;
l_string|&quot;51:     movl 28(%4), %%edx&bslash;n&quot;
l_string|&quot;        movl %%eax, 24(%3)&bslash;n&quot;
l_string|&quot;        movl %%edx, 28(%3)&bslash;n&quot;
l_string|&quot;11:     movl 32(%4), %%eax&bslash;n&quot;
l_string|&quot;61:     movl 36(%4), %%edx&bslash;n&quot;
l_string|&quot;        movl %%eax, 32(%3)&bslash;n&quot;
l_string|&quot;        movl %%edx, 36(%3)&bslash;n&quot;
l_string|&quot;12:     movl 40(%4), %%eax&bslash;n&quot;
l_string|&quot;71:     movl 44(%4), %%edx&bslash;n&quot;
l_string|&quot;        movl %%eax, 40(%3)&bslash;n&quot;
l_string|&quot;        movl %%edx, 44(%3)&bslash;n&quot;
l_string|&quot;13:     movl 48(%4), %%eax&bslash;n&quot;
l_string|&quot;81:     movl 52(%4), %%edx&bslash;n&quot;
l_string|&quot;        movl %%eax, 48(%3)&bslash;n&quot;
l_string|&quot;        movl %%edx, 52(%3)&bslash;n&quot;
l_string|&quot;14:     movl 56(%4), %%eax&bslash;n&quot;
l_string|&quot;91:     movl 60(%4), %%edx&bslash;n&quot;
l_string|&quot;        movl %%eax, 56(%3)&bslash;n&quot;
l_string|&quot;        movl %%edx, 60(%3)&bslash;n&quot;
l_string|&quot;        addl $-64, %0&bslash;n&quot;
l_string|&quot;        addl $64, %4&bslash;n&quot;
l_string|&quot;        addl $64, %3&bslash;n&quot;
l_string|&quot;        cmpl $63, %0&bslash;n&quot;
l_string|&quot;        ja  0b&bslash;n&quot;
l_string|&quot;5:      movl  %0, %%eax&bslash;n&quot;
l_string|&quot;        shrl  $2, %0&bslash;n&quot;
l_string|&quot;        andl $3, %%eax&bslash;n&quot;
l_string|&quot;        cld&bslash;n&quot;
l_string|&quot;6:      rep; movsl&bslash;n&quot;
l_string|&quot;        movl %%eax,%0&bslash;n&quot;
l_string|&quot;7:      rep; movsb&bslash;n&quot;
l_string|&quot;8:&bslash;n&quot;
l_string|&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
l_string|&quot;9:      lea 0(%%eax,%0,4),%0&bslash;n&quot;
l_string|&quot;16:     pushl %0&bslash;n&quot;
l_string|&quot;        pushl %%eax&bslash;n&quot;
l_string|&quot;        xorl %%eax,%%eax&bslash;n&quot;
l_string|&quot;        rep; stosb&bslash;n&quot;
l_string|&quot;        popl %%eax&bslash;n&quot;
l_string|&quot;        popl %0&bslash;n&quot;
l_string|&quot;        jmp 8b&bslash;n&quot;
l_string|&quot;.previous&bslash;n&quot;
l_string|&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;
l_string|&quot;&t;.align 4&bslash;n&quot;
l_string|&quot;&t;.long 0b,16b&bslash;n&quot;
l_string|&quot;&t;.long 1b,16b&bslash;n&quot;
l_string|&quot;&t;.long 2b,16b&bslash;n&quot;
l_string|&quot;&t;.long 21b,16b&bslash;n&quot;
l_string|&quot;&t;.long 3b,16b&bslash;n&quot;
l_string|&quot;&t;.long 31b,16b&bslash;n&quot;
l_string|&quot;&t;.long 4b,16b&bslash;n&quot;
l_string|&quot;&t;.long 41b,16b&bslash;n&quot;
l_string|&quot;&t;.long 10b,16b&bslash;n&quot;
l_string|&quot;&t;.long 51b,16b&bslash;n&quot;
l_string|&quot;&t;.long 11b,16b&bslash;n&quot;
l_string|&quot;&t;.long 61b,16b&bslash;n&quot;
l_string|&quot;&t;.long 12b,16b&bslash;n&quot;
l_string|&quot;&t;.long 71b,16b&bslash;n&quot;
l_string|&quot;&t;.long 13b,16b&bslash;n&quot;
l_string|&quot;&t;.long 81b,16b&bslash;n&quot;
l_string|&quot;&t;.long 14b,16b&bslash;n&quot;
l_string|&quot;&t;.long 91b,16b&bslash;n&quot;
l_string|&quot;&t;.long 6b,9b&bslash;n&quot;
l_string|&quot;        .long 7b,16b&bslash;n&quot;
l_string|&quot;.previous&quot;
suffix:colon
l_string|&quot;=&amp;c&quot;
(paren
id|size
)paren
comma
l_string|&quot;=&amp;D&quot;
(paren
id|d0
)paren
comma
l_string|&quot;=&amp;S&quot;
(paren
id|d1
)paren
suffix:colon
l_string|&quot;1&quot;
(paren
id|to
)paren
comma
l_string|&quot;2&quot;
(paren
id|from
)paren
comma
l_string|&quot;0&quot;
(paren
id|size
)paren
suffix:colon
l_string|&quot;eax&quot;
comma
l_string|&quot;edx&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|size
suffix:semicolon
)brace
macro_line|#else
multiline_comment|/*&n; * Leave these declared but undefined.  They should not be any references to&n; * them&n; */
r_int
r_int
id|__copy_user_zeroing_intel
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
id|size
)paren
suffix:semicolon
r_int
r_int
id|__copy_user_intel
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
id|size
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_X86_INTEL_USERCOPY */
multiline_comment|/* Generic arbitrary sized copy.  */
DECL|macro|__copy_user
mdefine_line|#define __copy_user(to,from,size)&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;int __d0, __d1, __d2;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;cmp  $7,%0&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;jbe  1f&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;movl %1,%0&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;negl %0&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;andl $7,%0&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;subl %0,%3&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;4:&t;rep; movsb&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;movl %3,%0&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;shrl $2,%0&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;andl $3,%3&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.align 2,0x90&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;0:&t;rep; movsl&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;movl %3,%0&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;1:&t;rep; movsb&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;2:&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;5:&t;addl %3,%0&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;jmp 2b&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;3:&t;lea 0(%3,%0,4),%0&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;jmp 2b&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.previous&bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.align 4&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.long 4b,5b&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.long 0b,3b&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.long 1b,2b&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.previous&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=&amp;c&quot;(size), &quot;=&amp;D&quot; (__d0), &quot;=&amp;S&quot; (__d1), &quot;=r&quot;(__d2)&t;&bslash;&n;&t;&t;: &quot;3&quot;(size), &quot;0&quot;(size), &quot;1&quot;(to), &quot;2&quot;(from)&t;&t;&bslash;&n;&t;&t;: &quot;memory&quot;);&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|__copy_user_zeroing
mdefine_line|#define __copy_user_zeroing(to,from,size)&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;int __d0, __d1, __d2;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;cmp  $7,%0&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;jbe  1f&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;movl %1,%0&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;negl %0&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;andl $7,%0&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;subl %0,%3&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;4:&t;rep; movsb&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;movl %3,%0&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;shrl $2,%0&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;andl $3,%3&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.align 2,0x90&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;0:&t;rep; movsl&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;movl %3,%0&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;1:&t;rep; movsb&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;2:&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;5:&t;addl %3,%0&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;jmp 6f&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;3:&t;lea 0(%3,%0,4),%0&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;6:&t;pushl %0&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;pushl %%eax&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;xorl %%eax,%%eax&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;rep; stosb&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;popl %%eax&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;popl %0&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;jmp 2b&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.previous&bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.align 4&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.long 4b,5b&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.long 0b,3b&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.long 1b,6b&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.previous&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=&amp;c&quot;(size), &quot;=&amp;D&quot; (__d0), &quot;=&amp;S&quot; (__d1), &quot;=r&quot;(__d2)&t;&bslash;&n;&t;&t;: &quot;3&quot;(size), &quot;0&quot;(size), &quot;1&quot;(to), &quot;2&quot;(from)&t;&t;&bslash;&n;&t;&t;: &quot;memory&quot;);&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|function|__copy_to_user_ll
r_int
r_int
id|__copy_to_user_ll
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
r_if
c_cond
(paren
id|movsl_is_ok
c_func
(paren
id|to
comma
id|from
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
r_else
id|n
op_assign
id|__copy_user_intel
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
DECL|function|__copy_from_user_ll
r_int
r_int
id|__copy_from_user_ll
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
r_if
c_cond
(paren
id|movsl_is_ok
c_func
(paren
id|to
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
id|n
op_assign
id|__copy_user_zeroing_intel
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
eof
