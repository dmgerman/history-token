multiline_comment|/*&n; *  linux/include/asm-arm/proc-armv/uaccess.h&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &lt;asm/arch/memory.h&gt;
macro_line|#include &lt;asm/proc/domain.h&gt;
multiline_comment|/*&n; * Note that this is actually 0x1,0000,0000&n; */
DECL|macro|KERNEL_DS
mdefine_line|#define KERNEL_DS&t;0x00000000
DECL|macro|USER_DS
mdefine_line|#define USER_DS&t;&t;PAGE_OFFSET
DECL|function|set_fs
r_extern
id|__inline__
r_void
id|set_fs
(paren
id|mm_segment_t
id|fs
)paren
(brace
id|current-&gt;addr_limit
op_assign
id|fs
suffix:semicolon
id|modify_domain
c_func
(paren
id|DOMAIN_KERNEL
comma
id|fs
ques
c_cond
id|DOMAIN_CLIENT
suffix:colon
id|DOMAIN_MANAGER
)paren
suffix:semicolon
)brace
multiline_comment|/* We use 33-bit arithmetic here... */
DECL|macro|__range_ok
mdefine_line|#define __range_ok(addr,size) ({ &bslash;&n;&t;unsigned long flag, sum; &bslash;&n;&t;__asm__(&quot;adds %1, %2, %3; sbcccs %1, %1, %0; movcc %0, #0&quot; &bslash;&n;&t;&t;: &quot;=&amp;r&quot; (flag), &quot;=&amp;r&quot; (sum) &bslash;&n;&t;&t;: &quot;r&quot; (addr), &quot;Ir&quot; (size), &quot;0&quot; (current-&gt;addr_limit) &bslash;&n;&t;&t;: &quot;cc&quot;); &bslash;&n;&t;flag; })
DECL|macro|__addr_ok
mdefine_line|#define __addr_ok(addr) ({ &bslash;&n;&t;unsigned long flag; &bslash;&n;&t;__asm__(&quot;cmp %2, %0; movlo %0, #0&quot; &bslash;&n;&t;&t;: &quot;=&amp;r&quot; (flag) &bslash;&n;&t;&t;: &quot;0&quot; (current-&gt;addr_limit), &quot;r&quot; (addr) &bslash;&n;&t;&t;: &quot;cc&quot;); &bslash;&n;&t;(flag == 0); })
DECL|macro|__put_user_asm_byte
mdefine_line|#define __put_user_asm_byte(x,addr,err)&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;1:&t;strbt&t;%1,[%2],#0&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;2:&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&quot;&t;.align&t;2&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;3:&t;mov&t;%0, %3&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;b&t;2b&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.previous&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&quot;&t;.align&t;3&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.long&t;1b, 3b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.previous&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;=r&quot; (err)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;r&quot; (x), &quot;r&quot; (addr), &quot;i&quot; (-EFAULT), &quot;0&quot; (err))
DECL|macro|__put_user_asm_half
mdefine_line|#define __put_user_asm_half(x,addr,err)&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long __temp = (unsigned long)(x);&t;&t;&bslash;&n;&t;__put_user_asm_byte(__temp, addr, err);&t;&t;&t;&bslash;&n;&t;__put_user_asm_byte(__temp &gt;&gt; 8, (int)(addr) + 1, err);&t;&bslash;&n;})
DECL|macro|__put_user_asm_word
mdefine_line|#define __put_user_asm_word(x,addr,err)&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;1:&t;strt&t;%1,[%2],#0&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;2:&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&quot;&t;.align&t;2&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;3:&t;mov&t;%0, %3&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;b&t;2b&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.previous&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&quot;&t;.align&t;3&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.long&t;1b, 3b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.previous&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;=r&quot; (err)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;r&quot; (x), &quot;r&quot; (addr), &quot;i&quot; (-EFAULT), &quot;0&quot; (err))
DECL|macro|__get_user_asm_byte
mdefine_line|#define __get_user_asm_byte(x,addr,err)&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;1:&t;ldrbt&t;%1,[%2],#0&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;2:&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&quot;&t;.align&t;2&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;3:&t;mov&t;%0, %3&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;mov&t;%1, #0&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;b&t;2b&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.previous&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&quot;&t;.align&t;3&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.long&t;1b, 3b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.previous&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;=r&quot; (err), &quot;=r&quot; (x)&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;r&quot; (addr), &quot;i&quot; (-EFAULT), &quot;0&quot; (err))
DECL|macro|__get_user_asm_half
mdefine_line|#define __get_user_asm_half(x,addr,err)&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long __b1, __b2;&t;&t;&t;&t;&bslash;&n;&t;__get_user_asm_byte(__b1, addr, err);&t;&t;&t;&bslash;&n;&t;__get_user_asm_byte(__b2, (int)(addr) + 1, err);&t;&bslash;&n;&t;(x) = __b1 | (__b2 &lt;&lt; 8);&t;&t;&t;&t;&bslash;&n;})
DECL|macro|__get_user_asm_word
mdefine_line|#define __get_user_asm_word(x,addr,err)&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;1:&t;ldrt&t;%1,[%2],#0&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;2:&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&quot;&t;.align&t;2&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;3:&t;mov&t;%0, %3&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;mov&t;%1, #0&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;b&t;2b&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.previous&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&quot;&t;.align&t;3&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.long&t;1b, 3b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.previous&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;=r&quot; (err), &quot;=r&quot; (x)&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;r&quot; (addr), &quot;i&quot; (-EFAULT), &quot;0&quot; (err))
r_extern
r_int
r_int
id|__arch_copy_from_user
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
suffix:semicolon
DECL|macro|__do_copy_from_user
mdefine_line|#define __do_copy_from_user(to,from,n)&t;&t;&t;&t;&bslash;&n;&t;(n) = __arch_copy_from_user(to,from,n)
r_extern
r_int
r_int
id|__arch_copy_to_user
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
suffix:semicolon
DECL|macro|__do_copy_to_user
mdefine_line|#define __do_copy_to_user(to,from,n)&t;&t;&t;&t;&bslash;&n;&t;(n) = __arch_copy_to_user(to,from,n)
r_extern
r_int
r_int
id|__arch_clear_user
c_func
(paren
r_void
op_star
id|addr
comma
r_int
r_int
id|n
)paren
suffix:semicolon
DECL|macro|__do_clear_user
mdefine_line|#define __do_clear_user(addr,sz)&t;&t;&t;&t;&bslash;&n;&t;(sz) = __arch_clear_user(addr,sz)
r_extern
r_int
r_int
id|__arch_strncpy_from_user
c_func
(paren
r_char
op_star
id|to
comma
r_const
r_char
op_star
id|from
comma
r_int
r_int
id|count
)paren
suffix:semicolon
DECL|macro|__do_strncpy_from_user
mdefine_line|#define __do_strncpy_from_user(dst,src,count,res)&t;&t;&bslash;&n;&t;(res) = __arch_strncpy_from_user(dst,src,count)
r_extern
r_int
r_int
id|__arch_strnlen_user
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
suffix:semicolon
DECL|macro|__do_strnlen_user
mdefine_line|#define __do_strnlen_user(s,n,res)&t;&t;&t;&t;&t;&bslash;&n;&t;(res) = __arch_strnlen_user(s,n)
eof
