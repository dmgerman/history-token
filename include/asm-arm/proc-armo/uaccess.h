multiline_comment|/*&n; *  linux/include/asm-arm/proc-armo/segment.h&n; *&n; *  Copyright (C) 1996 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
multiline_comment|/*&n; * The fs functions are implemented on the ARM2 and ARM3 architectures&n; * manually.&n; * Use *_user functions to access user memory with faulting behaving&n; *   as though the user is accessing the memory.&n; * Use set_fs(get_ds()) and then the *_user functions to allow them to&n; *   access kernel memory.&n; */
multiline_comment|/*&n; * These are the values used to represent the user `fs&squot; and the kernel `ds&squot;&n; */
DECL|macro|KERNEL_DS
mdefine_line|#define KERNEL_DS&t;0x03000000
DECL|macro|USER_DS
mdefine_line|#define USER_DS   &t;0x02000000
r_extern
id|uaccess_t
id|uaccess_user
comma
id|uaccess_kernel
suffix:semicolon
DECL|function|set_fs
r_static
r_inline
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
id|current-&gt;thread.uaccess
op_assign
id|fs
op_eq
id|USER_DS
ques
c_cond
op_amp
id|uaccess_user
suffix:colon
op_amp
id|uaccess_kernel
suffix:semicolon
)brace
DECL|macro|__range_ok
mdefine_line|#define __range_ok(addr,size) ({&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long flag, sum;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&quot;subs %1, %0, %3; cmpcs %1, %2; movcs %0, #0&quot; &bslash;&n;&t;&t;: &quot;=&amp;r&quot; (flag), &quot;=&amp;r&quot; (sum)&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;r&quot; (addr), &quot;Ir&quot; (size), &quot;0&quot; (current-&gt;addr_limit)&t;&bslash;&n;&t;&t;: &quot;cc&quot;);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;flag; })
DECL|macro|__addr_ok
mdefine_line|#define __addr_ok(addr) ({&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long flag;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&quot;cmp %2, %0; movlo %0, #0&quot;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=&amp;r&quot; (flag)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;0&quot; (current-&gt;addr_limit), &quot;r&quot; (addr)&t;&t;&t;&bslash;&n;&t;&t;: &quot;cc&quot;);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(flag == 0); })
DECL|macro|__put_user_asm_byte
mdefine_line|#define __put_user_asm_byte(x,addr,err)&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;mov&t;r0, %1&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;mov&t;r1, %2&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;mov&t;r2, %0&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;mov&t;lr, pc&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;mov&t;pc, %3&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;mov&t;%0, r2&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;=r&quot; (err)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;r&quot; (x), &quot;r&quot; (addr), &quot;r&quot; (current-&gt;thread.uaccess-&gt;put_byte),&t;&bslash;&n;&t;  &quot;0&quot; (err)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;r0&quot;, &quot;r1&quot;, &quot;r2&quot;, &quot;lr&quot;)
DECL|macro|__put_user_asm_half
mdefine_line|#define __put_user_asm_half(x,addr,err)&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;mov&t;r0, %1&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;mov&t;r1, %2&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;mov&t;r2, %0&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;mov&t;lr, pc&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;mov&t;pc, %3&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;mov&t;%0, r2&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;=r&quot; (err)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;r&quot; (x), &quot;r&quot; (addr), &quot;r&quot; (current-&gt;thread.uaccess-&gt;put_half),&t;&bslash;&n;&t;  &quot;0&quot; (err)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;r0&quot;, &quot;r1&quot;, &quot;r2&quot;, &quot;lr&quot;)
DECL|macro|__put_user_asm_word
mdefine_line|#define __put_user_asm_word(x,addr,err)&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;mov&t;r0, %1&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;mov&t;r1, %2&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;mov&t;r2, %0&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;mov&t;lr, pc&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;mov&t;pc, %3&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;mov&t;%0, r2&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;=r&quot; (err)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;r&quot; (x), &quot;r&quot; (addr), &quot;r&quot; (current-&gt;thread.uaccess-&gt;put_word),&t;&bslash;&n;&t;  &quot;0&quot; (err)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;r0&quot;, &quot;r1&quot;, &quot;r2&quot;, &quot;lr&quot;)
DECL|macro|__get_user_asm_byte
mdefine_line|#define __get_user_asm_byte(x,addr,err)&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;mov&t;r0, %2&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;mov&t;r1, %0&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;mov&t;lr, pc&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;mov&t;pc, %3&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;mov&t;%0, r1&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;mov&t;%1, r0&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;=r&quot; (err), &quot;=r&quot; (x)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;r&quot; (addr), &quot;r&quot; (current-&gt;thread.uaccess-&gt;get_byte), &quot;0&quot; (err)&t;&bslash;&n;&t;: &quot;r0&quot;, &quot;r1&quot;, &quot;r2&quot;, &quot;lr&quot;)
DECL|macro|__get_user_asm_half
mdefine_line|#define __get_user_asm_half(x,addr,err)&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;mov&t;r0, %2&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;mov&t;r1, %0&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;mov&t;lr, pc&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;mov&t;pc, %3&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;mov&t;%0, r1&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;mov&t;%1, r0&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;=r&quot; (err), &quot;=r&quot; (x)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;r&quot; (addr), &quot;r&quot; (current-&gt;thread.uaccess-&gt;get_half), &quot;0&quot; (err)&t;&bslash;&n;&t;: &quot;r0&quot;, &quot;r1&quot;, &quot;r2&quot;, &quot;lr&quot;)
DECL|macro|__get_user_asm_word
mdefine_line|#define __get_user_asm_word(x,addr,err)&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;mov&t;r0, %2&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;mov&t;r1, %0&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;mov&t;lr, pc&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;mov&t;pc, %3&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;mov&t;%0, r1&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;mov&t;%1, r0&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;=r&quot; (err), &quot;=r&quot; (x)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;r&quot; (addr), &quot;r&quot; (current-&gt;thread.uaccess-&gt;get_word), &quot;0&quot; (err)&t;&bslash;&n;&t;: &quot;r0&quot;, &quot;r1&quot;, &quot;r2&quot;, &quot;lr&quot;)
DECL|macro|__do_copy_from_user
mdefine_line|#define __do_copy_from_user(to,from,n)&t;&t;&t;&t;&t;&bslash;&n;&t;(n) = current-&gt;thread.uaccess-&gt;copy_from_user((to),(from),(n))
DECL|macro|__do_copy_to_user
mdefine_line|#define __do_copy_to_user(to,from,n)&t;&t;&t;&t;&t;&bslash;&n;&t;(n) = current-&gt;thread.uaccess-&gt;copy_to_user((to),(from),(n))
DECL|macro|__do_clear_user
mdefine_line|#define __do_clear_user(addr,sz)&t;&t;&t;&t;&t;&bslash;&n;&t;(sz) = current-&gt;thread.uaccess-&gt;clear_user((addr),(sz))
DECL|macro|__do_strncpy_from_user
mdefine_line|#define __do_strncpy_from_user(dst,src,count,res)&t;&t;&t;&bslash;&n;&t;(res) = current-&gt;thread.uaccess-&gt;strncpy_from_user(dst,src,count)
DECL|macro|__do_strnlen_user
mdefine_line|#define __do_strnlen_user(s,n,res)&t;&t;&t;&t;&t;&bslash;&n;&t;(res) = current-&gt;thread.uaccess-&gt;strnlen_user(s,n)
eof
