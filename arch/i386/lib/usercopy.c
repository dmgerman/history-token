multiline_comment|/* &n; * User address space access functions.&n; * The non inlined parts of asm-i386/uaccess.h are here.&n; *&n; * Copyright 1997 Andi Kleen &lt;ak@muc.de&gt;&n; * Copyright 1997 Linus Torvalds&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/highmem.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/mmx.h&gt;
DECL|function|__movsl_is_ok
r_static
r_inline
r_int
id|__movsl_is_ok
c_func
(paren
r_int
r_int
id|a1
comma
r_int
r_int
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
id|a1
op_xor
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
DECL|macro|movsl_is_ok
mdefine_line|#define movsl_is_ok(a1,a2,n) &bslash;&n;&t;__movsl_is_ok((unsigned long)(a1),(unsigned long)(a2),(n))
multiline_comment|/*&n; * Copy a null terminated string from userspace.&n; */
DECL|macro|__do_strncpy_from_user
mdefine_line|#define __do_strncpy_from_user(dst,src,count,res)&t;&t;&t;   &bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;   &bslash;&n;&t;int __d0, __d1, __d2;&t;&t;&t;&t;&t;&t;   &bslash;&n;&t;might_sleep();&t;&t;&t;&t;&t;&t;&t;   &bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;&t;testl %1,%1&bslash;n&quot;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;&t;jz 2f&bslash;n&quot;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;0:&t;lodsb&bslash;n&quot;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;&t;stosb&bslash;n&quot;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;&t;testb %%al,%%al&bslash;n&quot;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;&t;jz 1f&bslash;n&quot;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;&t;decl %1&bslash;n&quot;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;&t;jnz 0b&bslash;n&quot;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;1:&t;subl %1,%0&bslash;n&quot;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;2:&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;3:&t;movl %5,%0&bslash;n&quot;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;&t;jmp 2b&bslash;n&quot;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;.previous&bslash;n&quot;&t;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;&t;.align 4&bslash;n&quot;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;&t;.long 0b,3b&bslash;n&quot;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;.previous&quot;&t;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;: &quot;=d&quot;(res), &quot;=c&quot;(count), &quot;=&amp;a&quot; (__d0), &quot;=&amp;S&quot; (__d1),&t;   &bslash;&n;&t;&t;  &quot;=&amp;D&quot; (__d2)&t;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;: &quot;i&quot;(-EFAULT), &quot;0&quot;(count), &quot;1&quot;(count), &quot;3&quot;(src), &quot;4&quot;(dst) &bslash;&n;&t;&t;: &quot;memory&quot;);&t;&t;&t;&t;&t;&t;   &bslash;&n;} while (0)
multiline_comment|/**&n; * __strncpy_from_user: - Copy a NUL terminated string from userspace, with less checking.&n; * @dst:   Destination address, in kernel space.  This buffer must be at&n; *         least @count bytes long.&n; * @src:   Source address, in user space.&n; * @count: Maximum number of bytes to copy, including the trailing NUL.&n; * &n; * Copies a NUL-terminated string from userspace to kernel space.&n; * Caller must check the specified block with access_ok() before calling&n; * this function.&n; *&n; * On success, returns the length of the string (not including the trailing&n; * NUL).&n; *&n; * If access to userspace fails, returns -EFAULT (some data may have been&n; * copied).&n; *&n; * If @count is smaller than the length of the string, copies @count bytes&n; * and returns @count.&n; */
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
id|__user
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
multiline_comment|/**&n; * strncpy_from_user: - Copy a NUL terminated string from userspace.&n; * @dst:   Destination address, in kernel space.  This buffer must be at&n; *         least @count bytes long.&n; * @src:   Source address, in user space.&n; * @count: Maximum number of bytes to copy, including the trailing NUL.&n; * &n; * Copies a NUL-terminated string from userspace to kernel space.&n; *&n; * On success, returns the length of the string (not including the trailing&n; * NUL).&n; *&n; * If access to userspace fails, returns -EFAULT (some data may have been&n; * copied).&n; *&n; * If @count is smaller than the length of the string, copies @count bytes&n; * and returns @count.&n; */
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
id|__user
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
mdefine_line|#define __do_clear_user(addr,size)&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;int __d0;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;might_sleep();&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  &t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;0:&t;rep; stosl&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;movl %2,%0&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;1:&t;rep; stosb&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;2:&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;3:&t;lea 0(%2,%0,4),%0&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;jmp 2b&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.previous&bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.align 4&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.long 0b,3b&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.long 1b,2b&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.previous&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=&amp;c&quot;(size), &quot;=&amp;D&quot; (__d0)&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;r&quot;(size &amp; 3), &quot;0&quot;(size / 4), &quot;1&quot;(addr), &quot;a&quot;(0));&t;&bslash;&n;} while (0)
multiline_comment|/**&n; * clear_user: - Zero a block of memory in user space.&n; * @to:   Destination address, in user space.&n; * @n:    Number of bytes to zero.&n; *&n; * Zero a block of memory in user space.&n; *&n; * Returns number of bytes that could not be cleared.&n; * On success, this will be zero.&n; */
r_int
r_int
DECL|function|clear_user
id|clear_user
c_func
(paren
r_void
id|__user
op_star
id|to
comma
r_int
r_int
id|n
)paren
(brace
id|might_sleep
c_func
(paren
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
multiline_comment|/**&n; * __clear_user: - Zero a block of memory in user space, with less checking.&n; * @to:   Destination address, in user space.&n; * @n:    Number of bytes to zero.&n; *&n; * Zero a block of memory in user space.  Caller must check&n; * the specified block with access_ok() before calling this function.&n; *&n; * Returns number of bytes that could not be cleared.&n; * On success, this will be zero.&n; */
r_int
r_int
DECL|function|__clear_user
id|__clear_user
c_func
(paren
r_void
id|__user
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
multiline_comment|/**&n; * strlen_user: - Get the size of a string in user space.&n; * @s: The string to measure.&n; * @n: The maximum valid length&n; *&n; * Get the size of a NUL-terminated string in user space.&n; *&n; * Returns the size of the string INCLUDING the terminating NUL.&n; * On exception, returns 0.&n; * If the string is too long, returns a value greater than @n.&n; */
DECL|function|strnlen_user
r_int
id|strnlen_user
c_func
(paren
r_const
r_char
id|__user
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
id|might_sleep
c_func
(paren
)paren
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
id|__user
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
l_string|&quot;1:     movl 32(%4), %%eax&bslash;n&quot;
l_string|&quot;       cmpl $67, %0&bslash;n&quot;
l_string|&quot;       jbe 3f&bslash;n&quot;
l_string|&quot;2:     movl 64(%4), %%eax&bslash;n&quot;
l_string|&quot;       .align 2,0x90&bslash;n&quot;
l_string|&quot;3:     movl 0(%4), %%eax&bslash;n&quot;
l_string|&quot;4:     movl 4(%4), %%edx&bslash;n&quot;
l_string|&quot;5:     movl %%eax, 0(%3)&bslash;n&quot;
l_string|&quot;6:     movl %%edx, 4(%3)&bslash;n&quot;
l_string|&quot;7:     movl 8(%4), %%eax&bslash;n&quot;
l_string|&quot;8:     movl 12(%4),%%edx&bslash;n&quot;
l_string|&quot;9:     movl %%eax, 8(%3)&bslash;n&quot;
l_string|&quot;10:    movl %%edx, 12(%3)&bslash;n&quot;
l_string|&quot;11:    movl 16(%4), %%eax&bslash;n&quot;
l_string|&quot;12:    movl 20(%4), %%edx&bslash;n&quot;
l_string|&quot;13:    movl %%eax, 16(%3)&bslash;n&quot;
l_string|&quot;14:    movl %%edx, 20(%3)&bslash;n&quot;
l_string|&quot;15:    movl 24(%4), %%eax&bslash;n&quot;
l_string|&quot;16:    movl 28(%4), %%edx&bslash;n&quot;
l_string|&quot;17:    movl %%eax, 24(%3)&bslash;n&quot;
l_string|&quot;18:    movl %%edx, 28(%3)&bslash;n&quot;
l_string|&quot;19:    movl 32(%4), %%eax&bslash;n&quot;
l_string|&quot;20:    movl 36(%4), %%edx&bslash;n&quot;
l_string|&quot;21:    movl %%eax, 32(%3)&bslash;n&quot;
l_string|&quot;22:    movl %%edx, 36(%3)&bslash;n&quot;
l_string|&quot;23:    movl 40(%4), %%eax&bslash;n&quot;
l_string|&quot;24:    movl 44(%4), %%edx&bslash;n&quot;
l_string|&quot;25:    movl %%eax, 40(%3)&bslash;n&quot;
l_string|&quot;26:    movl %%edx, 44(%3)&bslash;n&quot;
l_string|&quot;27:    movl 48(%4), %%eax&bslash;n&quot;
l_string|&quot;28:    movl 52(%4), %%edx&bslash;n&quot;
l_string|&quot;29:    movl %%eax, 48(%3)&bslash;n&quot;
l_string|&quot;30:    movl %%edx, 52(%3)&bslash;n&quot;
l_string|&quot;31:    movl 56(%4), %%eax&bslash;n&quot;
l_string|&quot;32:    movl 60(%4), %%edx&bslash;n&quot;
l_string|&quot;33:    movl %%eax, 56(%3)&bslash;n&quot;
l_string|&quot;34:    movl %%edx, 60(%3)&bslash;n&quot;
l_string|&quot;       addl $-64, %0&bslash;n&quot;
l_string|&quot;       addl $64, %4&bslash;n&quot;
l_string|&quot;       addl $64, %3&bslash;n&quot;
l_string|&quot;       cmpl $63, %0&bslash;n&quot;
l_string|&quot;       ja  1b&bslash;n&quot;
l_string|&quot;35:    movl  %0, %%eax&bslash;n&quot;
l_string|&quot;       shrl  $2, %0&bslash;n&quot;
l_string|&quot;       andl  $3, %%eax&bslash;n&quot;
l_string|&quot;       cld&bslash;n&quot;
l_string|&quot;99:    rep; movsl&bslash;n&quot;
l_string|&quot;36:    movl %%eax, %0&bslash;n&quot;
l_string|&quot;37:    rep; movsb&bslash;n&quot;
l_string|&quot;100:&bslash;n&quot;
l_string|&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
l_string|&quot;101:   lea 0(%%eax,%0,4),%0&bslash;n&quot;
l_string|&quot;       jmp 100b&bslash;n&quot;
l_string|&quot;.previous&bslash;n&quot;
l_string|&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;
l_string|&quot;       .align 4&bslash;n&quot;
l_string|&quot;       .long 1b,100b&bslash;n&quot;
l_string|&quot;       .long 2b,100b&bslash;n&quot;
l_string|&quot;       .long 3b,100b&bslash;n&quot;
l_string|&quot;       .long 4b,100b&bslash;n&quot;
l_string|&quot;       .long 5b,100b&bslash;n&quot;
l_string|&quot;       .long 6b,100b&bslash;n&quot;
l_string|&quot;       .long 7b,100b&bslash;n&quot;
l_string|&quot;       .long 8b,100b&bslash;n&quot;
l_string|&quot;       .long 9b,100b&bslash;n&quot;
l_string|&quot;       .long 10b,100b&bslash;n&quot;
l_string|&quot;       .long 11b,100b&bslash;n&quot;
l_string|&quot;       .long 12b,100b&bslash;n&quot;
l_string|&quot;       .long 13b,100b&bslash;n&quot;
l_string|&quot;       .long 14b,100b&bslash;n&quot;
l_string|&quot;       .long 15b,100b&bslash;n&quot;
l_string|&quot;       .long 16b,100b&bslash;n&quot;
l_string|&quot;       .long 17b,100b&bslash;n&quot;
l_string|&quot;       .long 18b,100b&bslash;n&quot;
l_string|&quot;       .long 19b,100b&bslash;n&quot;
l_string|&quot;       .long 20b,100b&bslash;n&quot;
l_string|&quot;       .long 21b,100b&bslash;n&quot;
l_string|&quot;       .long 22b,100b&bslash;n&quot;
l_string|&quot;       .long 23b,100b&bslash;n&quot;
l_string|&quot;       .long 24b,100b&bslash;n&quot;
l_string|&quot;       .long 25b,100b&bslash;n&quot;
l_string|&quot;       .long 26b,100b&bslash;n&quot;
l_string|&quot;       .long 27b,100b&bslash;n&quot;
l_string|&quot;       .long 28b,100b&bslash;n&quot;
l_string|&quot;       .long 29b,100b&bslash;n&quot;
l_string|&quot;       .long 30b,100b&bslash;n&quot;
l_string|&quot;       .long 31b,100b&bslash;n&quot;
l_string|&quot;       .long 32b,100b&bslash;n&quot;
l_string|&quot;       .long 33b,100b&bslash;n&quot;
l_string|&quot;       .long 34b,100b&bslash;n&quot;
l_string|&quot;       .long 35b,100b&bslash;n&quot;
l_string|&quot;       .long 36b,100b&bslash;n&quot;
l_string|&quot;       .long 37b,100b&bslash;n&quot;
l_string|&quot;       .long 99b,101b&bslash;n&quot;
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
id|__user
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
id|__user
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
id|__user
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
id|__user
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
id|BUG_ON
c_func
(paren
(paren
r_int
)paren
id|n
OL
l_int|0
)paren
suffix:semicolon
macro_line|#ifndef CONFIG_X86_WP_WORKS_OK
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|boot_cpu_data.wp_works_ok
op_eq
l_int|0
)paren
op_logical_and
(paren
(paren
r_int
r_int
)paren
id|to
)paren
OL
id|TASK_SIZE
)paren
(brace
multiline_comment|/* &n;&t;&t; * CPU does not honor the WP bit when writing&n;&t;&t; * from supervisory mode, and due to preemption or SMP,&n;&t;&t; * the page tables can change at any time.&n;&t;&t; * Do it manually.&t;Manfred &lt;manfred@colorfullife.com&gt;&n;&t;&t; */
r_while
c_loop
(paren
id|n
)paren
(brace
r_int
r_int
id|offset
op_assign
(paren
(paren
r_int
r_int
)paren
id|to
)paren
op_mod
id|PAGE_SIZE
suffix:semicolon
r_int
r_int
id|len
op_assign
id|PAGE_SIZE
op_minus
id|offset
suffix:semicolon
r_int
id|retval
suffix:semicolon
r_struct
id|page
op_star
id|pg
suffix:semicolon
r_void
op_star
id|maddr
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|n
)paren
id|len
op_assign
id|n
suffix:semicolon
id|survive
suffix:colon
id|down_read
c_func
(paren
op_amp
id|current-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
id|retval
op_assign
id|get_user_pages
c_func
(paren
id|current
comma
id|current-&gt;mm
comma
(paren
r_int
r_int
)paren
id|to
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
op_amp
id|pg
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
op_eq
op_minus
id|ENOMEM
op_logical_and
id|current-&gt;pid
op_eq
l_int|1
)paren
(brace
id|up_read
c_func
(paren
op_amp
id|current-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
id|blk_congestion_wait
c_func
(paren
id|WRITE
comma
id|HZ
op_div
l_int|50
)paren
suffix:semicolon
r_goto
id|survive
suffix:semicolon
)brace
r_if
c_cond
(paren
id|retval
op_ne
l_int|1
)paren
(brace
id|up_read
c_func
(paren
op_amp
id|current-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|maddr
op_assign
id|kmap_atomic
c_func
(paren
id|pg
comma
id|KM_USER0
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|maddr
op_plus
id|offset
comma
id|from
comma
id|len
)paren
suffix:semicolon
id|kunmap_atomic
c_func
(paren
id|maddr
comma
id|KM_USER0
)paren
suffix:semicolon
id|set_page_dirty_lock
c_func
(paren
id|pg
)paren
suffix:semicolon
id|put_page
c_func
(paren
id|pg
)paren
suffix:semicolon
id|up_read
c_func
(paren
op_amp
id|current-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
id|from
op_add_assign
id|len
suffix:semicolon
id|to
op_add_assign
id|len
suffix:semicolon
id|n
op_sub_assign
id|len
suffix:semicolon
)brace
r_return
id|n
suffix:semicolon
)brace
macro_line|#endif
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
r_int
r_int
DECL|function|__copy_from_user_ll
id|__copy_from_user_ll
c_func
(paren
r_void
op_star
id|to
comma
r_const
r_void
id|__user
op_star
id|from
comma
r_int
r_int
id|n
)paren
(brace
id|BUG_ON
c_func
(paren
(paren
r_int
)paren
id|n
OL
l_int|0
)paren
suffix:semicolon
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
multiline_comment|/**&n; * copy_to_user: - Copy a block of data into user space.&n; * @to:   Destination address, in user space.&n; * @from: Source address, in kernel space.&n; * @n:    Number of bytes to copy.&n; *&n; * Context: User context only.  This function may sleep.&n; *&n; * Copy data from kernel space to user space.&n; *&n; * Returns number of bytes that could not be copied.&n; * On success, this will be zero.&n; */
r_int
r_int
DECL|function|copy_to_user
id|copy_to_user
c_func
(paren
r_void
id|__user
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
id|might_sleep
c_func
(paren
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
(paren
r_int
)paren
id|n
OL
l_int|0
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
id|n
op_assign
id|__copy_to_user
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
DECL|variable|copy_to_user
id|EXPORT_SYMBOL
c_func
(paren
id|copy_to_user
)paren
suffix:semicolon
multiline_comment|/**&n; * copy_from_user: - Copy a block of data from user space.&n; * @to:   Destination address, in kernel space.&n; * @from: Source address, in user space.&n; * @n:    Number of bytes to copy.&n; *&n; * Context: User context only.  This function may sleep.&n; *&n; * Copy data from user space to kernel space.&n; *&n; * Returns number of bytes that could not be copied.&n; * On success, this will be zero.&n; *&n; * If some data could not be copied, this function will pad the copied&n; * data to the requested size using zero bytes.&n; */
r_int
r_int
DECL|function|copy_from_user
id|copy_from_user
c_func
(paren
r_void
op_star
id|to
comma
r_const
r_void
id|__user
op_star
id|from
comma
r_int
r_int
id|n
)paren
(brace
id|might_sleep
c_func
(paren
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
(paren
r_int
)paren
id|n
OL
l_int|0
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
id|n
op_assign
id|__copy_from_user
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
DECL|variable|copy_from_user
id|EXPORT_SYMBOL
c_func
(paren
id|copy_from_user
)paren
suffix:semicolon
eof
