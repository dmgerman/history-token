multiline_comment|/*&n; *  linux/include/asm-arm/uaccess.h&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#ifndef _ASMARM_UACCESS_H
DECL|macro|_ASMARM_UACCESS_H
mdefine_line|#define _ASMARM_UACCESS_H
multiline_comment|/*&n; * User space memory access functions&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/errno.h&gt;
macro_line|#include &lt;asm/memory.h&gt;
macro_line|#include &lt;asm/domain.h&gt;
macro_line|#include &lt;asm/system.h&gt;
DECL|macro|VERIFY_READ
mdefine_line|#define VERIFY_READ 0
DECL|macro|VERIFY_WRITE
mdefine_line|#define VERIFY_WRITE 1
multiline_comment|/*&n; * The exception table consists of pairs of addresses: the first is the&n; * address of an instruction that is allowed to fault, and the second is&n; * the address at which the program should continue.  No registers are&n; * modified, so it is entirely up to the continuation code to figure out&n; * what to do.&n; *&n; * All the routines below use bits of fixup code that are out of line&n; * with the main instruction path.  This means when everything is well,&n; * we don&squot;t even have to jump over them.  Further, they do not intrude&n; * on our cache or tlb entries.&n; */
DECL|struct|exception_table_entry
r_struct
id|exception_table_entry
(brace
DECL|member|insn
DECL|member|fixup
r_int
r_int
id|insn
comma
id|fixup
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_int
id|fixup_exception
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
multiline_comment|/*&n; * Note that this is actually 0x1,0000,0000&n; */
DECL|macro|KERNEL_DS
mdefine_line|#define KERNEL_DS&t;0x00000000
DECL|macro|USER_DS
mdefine_line|#define USER_DS&t;&t;TASK_SIZE
DECL|macro|get_ds
mdefine_line|#define get_ds()&t;(KERNEL_DS)
DECL|macro|get_fs
mdefine_line|#define get_fs()&t;(current_thread_info()-&gt;addr_limit)
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
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|addr_limit
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
DECL|macro|segment_eq
mdefine_line|#define segment_eq(a,b)&t;((a) == (b))
DECL|macro|__addr_ok
mdefine_line|#define __addr_ok(addr) ({ &bslash;&n;&t;unsigned long flag; &bslash;&n;&t;__asm__(&quot;cmp %2, %0; movlo %0, #0&quot; &bslash;&n;&t;&t;: &quot;=&amp;r&quot; (flag) &bslash;&n;&t;&t;: &quot;0&quot; (current_thread_info()-&gt;addr_limit), &quot;r&quot; (addr) &bslash;&n;&t;&t;: &quot;cc&quot;); &bslash;&n;&t;(flag == 0); })
multiline_comment|/* We use 33-bit arithmetic here... */
DECL|macro|__range_ok
mdefine_line|#define __range_ok(addr,size) ({ &bslash;&n;&t;unsigned long flag, sum; &bslash;&n;&t;__chk_user_ptr(addr);&t;&bslash;&n;&t;__asm__(&quot;adds %1, %2, %3; sbcccs %1, %1, %0; movcc %0, #0&quot; &bslash;&n;&t;&t;: &quot;=&amp;r&quot; (flag), &quot;=&amp;r&quot; (sum) &bslash;&n;&t;&t;: &quot;r&quot; (addr), &quot;Ir&quot; (size), &quot;0&quot; (current_thread_info()-&gt;addr_limit) &bslash;&n;&t;&t;: &quot;cc&quot;); &bslash;&n;&t;flag; })
DECL|macro|access_ok
mdefine_line|#define access_ok(type,addr,size)&t;(__range_ok(addr,size) == 0)
multiline_comment|/* this function will go away soon - use access_ok() instead */
DECL|function|verify_area
r_static
r_inline
r_int
id|__deprecated
id|verify_area
c_func
(paren
r_int
id|type
comma
r_const
r_void
id|__user
op_star
id|addr
comma
r_int
r_int
id|size
)paren
(brace
r_return
id|access_ok
c_func
(paren
id|type
comma
id|addr
comma
id|size
)paren
ques
c_cond
l_int|0
suffix:colon
op_minus
id|EFAULT
suffix:semicolon
)brace
multiline_comment|/*&n; * Single-value transfer routines.  They automatically use the right&n; * size if we just have the right pointer type.  Note that the functions&n; * which read from user space (*get_*) need to take care not to leak&n; * kernel data even if the calling code is buggy and fails to check&n; * the return value.  This means zeroing out the destination variable&n; * or buffer on error.  Normally this is done out of line by the&n; * fixup code, but there are a few places where it intrudes on the&n; * main code path.  When we only write to user space, there is no&n; * problem.&n; *&n; * The &quot;__xxx&quot; versions of the user access functions do not verify the&n; * address space - it must have been done previously with a separate&n; * &quot;access_ok()&quot; call.&n; *&n; * The &quot;xxx_error&quot; versions set the third argument to EFAULT if an&n; * error occurs, and leave it unchanged on success.  Note that these&n; * versions are void (ie, don&squot;t return a value as such).&n; */
r_extern
r_int
id|__get_user_1
c_func
(paren
r_void
op_star
)paren
suffix:semicolon
r_extern
r_int
id|__get_user_2
c_func
(paren
r_void
op_star
)paren
suffix:semicolon
r_extern
r_int
id|__get_user_4
c_func
(paren
r_void
op_star
)paren
suffix:semicolon
r_extern
r_int
id|__get_user_8
c_func
(paren
r_void
op_star
)paren
suffix:semicolon
r_extern
r_int
id|__get_user_bad
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|__get_user_x
mdefine_line|#define __get_user_x(__r2,__p,__e,__s,__i...)&t;&t;&t;&t;&bslash;&n;&t;   __asm__ __volatile__ (&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__asmeq(&quot;%0&quot;, &quot;r0&quot;) __asmeq(&quot;%1&quot;, &quot;r2&quot;)&t;&t;&t;&bslash;&n;&t;&t;&quot;bl&t;__get_user_&quot; #__s&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=&amp;r&quot; (__e), &quot;=r&quot; (__r2)&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;0&quot; (__p)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: __i, &quot;cc&quot;)
DECL|macro|get_user
mdefine_line|#define get_user(x,p)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;const register typeof(*(p)) __user *__p asm(&quot;r0&quot;) = (p);&bslash;&n;&t;&t;register typeof(*(p)) __r2 asm(&quot;r2&quot;);&t;&t;&t;&bslash;&n;&t;&t;register int __e asm(&quot;r0&quot;);&t;&t;&t;&t;&bslash;&n;&t;&t;switch (sizeof(*(__p))) {&t;&t;&t;&t;&bslash;&n;&t;&t;case 1:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;__get_user_x(__r2, __p, __e, 1, &quot;lr&quot;);&t;&t;&bslash;&n;&t;       &t;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;case 2:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;__get_user_x(__r2, __p, __e, 2, &quot;r3&quot;, &quot;lr&quot;);&t;&bslash;&n;&t;&t;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;case 4:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;       &t;&t;__get_user_x(__r2, __p, __e, 4, &quot;lr&quot;);&t;&t;&bslash;&n;&t;&t;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;case 8:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;__get_user_x(__r2, __p, __e, 8, &quot;lr&quot;);&t;&t;&bslash;&n;&t;       &t;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;default: __e = __get_user_bad(); break;&t;&t;&t;&bslash;&n;&t;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;x = __r2;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__e;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;})
DECL|macro|__get_user
mdefine_line|#define __get_user(x,ptr)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;long __gu_err = 0;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__get_user_err((x),(ptr),__gu_err);&t;&t;&t;&t;&bslash;&n;&t;__gu_err;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|__get_user_error
mdefine_line|#define __get_user_error(x,ptr,err)&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__get_user_err((x),(ptr),err);&t;&t;&t;&t;&t;&bslash;&n;&t;(void) 0;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|__get_user_err
mdefine_line|#define __get_user_err(x,ptr,err)&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long __gu_addr = (unsigned long)(ptr);&t;&t;&t;&bslash;&n;&t;unsigned long __gu_val;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__chk_user_ptr(ptr);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;switch (sizeof(*(ptr))) {&t;&t;&t;&t;&t;&bslash;&n;&t;case 1:&t;__get_user_asm_byte(__gu_val,__gu_addr,err);&t;break;&t;&bslash;&n;&t;case 2:&t;__get_user_asm_half(__gu_val,__gu_addr,err);&t;break;&t;&bslash;&n;&t;case 4:&t;__get_user_asm_word(__gu_val,__gu_addr,err);&t;break;&t;&bslash;&n;&t;default: (__gu_val) = __get_user_bad();&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(x) = (__typeof__(*(ptr)))__gu_val;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|__get_user_asm_byte
mdefine_line|#define __get_user_asm_byte(x,addr,err)&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;1:&t;ldrbt&t;%1,[%2],#0&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;2:&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&quot;&t;.align&t;2&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;3:&t;mov&t;%0, %3&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;mov&t;%1, #0&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;b&t;2b&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.previous&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&quot;&t;.align&t;3&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.long&t;1b, 3b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.previous&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;+r&quot; (err), &quot;=&amp;r&quot; (x)&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;r&quot; (addr), &quot;i&quot; (-EFAULT)&t;&t;&t;&t;&bslash;&n;&t;: &quot;cc&quot;)
macro_line|#ifndef __ARMEB__
DECL|macro|__get_user_asm_half
mdefine_line|#define __get_user_asm_half(x,__gu_addr,err)&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long __b1, __b2;&t;&t;&t;&t;&bslash;&n;&t;__get_user_asm_byte(__b1, __gu_addr, err);&t;&t;&bslash;&n;&t;__get_user_asm_byte(__b2, __gu_addr + 1, err);&t;&t;&bslash;&n;&t;(x) = __b1 | (__b2 &lt;&lt; 8);&t;&t;&t;&t;&bslash;&n;})
macro_line|#else
DECL|macro|__get_user_asm_half
mdefine_line|#define __get_user_asm_half(x,__gu_addr,err)&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long __b1, __b2;&t;&t;&t;&t;&bslash;&n;&t;__get_user_asm_byte(__b1, __gu_addr, err);&t;&t;&bslash;&n;&t;__get_user_asm_byte(__b2, __gu_addr + 1, err);&t;&t;&bslash;&n;&t;(x) = (__b1 &lt;&lt; 8) | __b2;&t;&t;&t;&t;&bslash;&n;})
macro_line|#endif
DECL|macro|__get_user_asm_word
mdefine_line|#define __get_user_asm_word(x,addr,err)&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;1:&t;ldrt&t;%1,[%2],#0&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;2:&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&quot;&t;.align&t;2&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;3:&t;mov&t;%0, %3&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;mov&t;%1, #0&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;b&t;2b&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.previous&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&quot;&t;.align&t;3&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.long&t;1b, 3b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.previous&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;+r&quot; (err), &quot;=&amp;r&quot; (x)&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;r&quot; (addr), &quot;i&quot; (-EFAULT)&t;&t;&t;&t;&bslash;&n;&t;: &quot;cc&quot;)
r_extern
r_int
id|__put_user_1
c_func
(paren
r_void
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
id|__put_user_2
c_func
(paren
r_void
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
id|__put_user_4
c_func
(paren
r_void
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
id|__put_user_8
c_func
(paren
r_void
op_star
comma
r_int
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
id|__put_user_bad
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|__put_user_x
mdefine_line|#define __put_user_x(__r2,__p,__e,__s)&t;&t;&t;&t;&t;&bslash;&n;&t;   __asm__ __volatile__ (&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__asmeq(&quot;%0&quot;, &quot;r0&quot;) __asmeq(&quot;%2&quot;, &quot;r2&quot;)&t;&t;&t;&bslash;&n;&t;&t;&quot;bl&t;__put_user_&quot; #__s&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=&amp;r&quot; (__e)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;0&quot; (__p), &quot;r&quot; (__r2)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;ip&quot;, &quot;lr&quot;, &quot;cc&quot;)
DECL|macro|put_user
mdefine_line|#define put_user(x,p)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;const register typeof(*(p)) __r2 asm(&quot;r2&quot;) = (x);&t;&bslash;&n;&t;&t;const register typeof(*(p)) __user *__p asm(&quot;r0&quot;) = (p);&bslash;&n;&t;&t;register int __e asm(&quot;r0&quot;);&t;&t;&t;&t;&bslash;&n;&t;&t;switch (sizeof(*(__p))) {&t;&t;&t;&t;&bslash;&n;&t;&t;case 1:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;__put_user_x(__r2, __p, __e, 1);&t;&t;&bslash;&n;&t;&t;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;case 2:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;__put_user_x(__r2, __p, __e, 2);&t;&t;&bslash;&n;&t;&t;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;case 4:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;__put_user_x(__r2, __p, __e, 4);&t;&t;&bslash;&n;&t;&t;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;case 8:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;__put_user_x(__r2, __p, __e, 8);&t;&t;&bslash;&n;&t;&t;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;default: __e = __put_user_bad(); break;&t;&t;&t;&bslash;&n;&t;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__e;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;})
DECL|macro|__put_user
mdefine_line|#define __put_user(x,ptr)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;long __pu_err = 0;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__put_user_err((x),(ptr),__pu_err);&t;&t;&t;&t;&bslash;&n;&t;__pu_err;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|__put_user_error
mdefine_line|#define __put_user_error(x,ptr,err)&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__put_user_err((x),(ptr),err);&t;&t;&t;&t;&t;&bslash;&n;&t;(void) 0;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|__put_user_err
mdefine_line|#define __put_user_err(x,ptr,err)&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long __pu_addr = (unsigned long)(ptr);&t;&t;&t;&bslash;&n;&t;__typeof__(*(ptr)) __pu_val = (x);&t;&t;&t;&t;&bslash;&n;&t;__chk_user_ptr(ptr);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;switch (sizeof(*(ptr))) {&t;&t;&t;&t;&t;&bslash;&n;&t;case 1: __put_user_asm_byte(__pu_val,__pu_addr,err);&t;break;&t;&bslash;&n;&t;case 2: __put_user_asm_half(__pu_val,__pu_addr,err);&t;break;&t;&bslash;&n;&t;case 4: __put_user_asm_word(__pu_val,__pu_addr,err);&t;break;&t;&bslash;&n;&t;case 8:&t;__put_user_asm_dword(__pu_val,__pu_addr,err);&t;break;&t;&bslash;&n;&t;default: __put_user_bad();&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|__put_user_asm_byte
mdefine_line|#define __put_user_asm_byte(x,__pu_addr,err)&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;1:&t;strbt&t;%1,[%2],#0&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;2:&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&quot;&t;.align&t;2&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;3:&t;mov&t;%0, %3&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;b&t;2b&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.previous&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&quot;&t;.align&t;3&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.long&t;1b, 3b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.previous&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;+r&quot; (err)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;r&quot; (x), &quot;r&quot; (__pu_addr), &quot;i&quot; (-EFAULT)&t;&t;&bslash;&n;&t;: &quot;cc&quot;)
macro_line|#ifndef __ARMEB__
DECL|macro|__put_user_asm_half
mdefine_line|#define __put_user_asm_half(x,__pu_addr,err)&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long __temp = (unsigned long)(x);&t;&t;&bslash;&n;&t;__put_user_asm_byte(__temp, __pu_addr, err);&t;&t;&bslash;&n;&t;__put_user_asm_byte(__temp &gt;&gt; 8, __pu_addr + 1, err);&t;&bslash;&n;})
macro_line|#else
DECL|macro|__put_user_asm_half
mdefine_line|#define __put_user_asm_half(x,__pu_addr,err)&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long __temp = (unsigned long)(x);&t;&t;&bslash;&n;&t;__put_user_asm_byte(__temp &gt;&gt; 8, __pu_addr, err);&t;&bslash;&n;&t;__put_user_asm_byte(__temp, __pu_addr + 1, err);&t;&bslash;&n;})
macro_line|#endif
DECL|macro|__put_user_asm_word
mdefine_line|#define __put_user_asm_word(x,__pu_addr,err)&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;1:&t;strt&t;%1,[%2],#0&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;2:&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&quot;&t;.align&t;2&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;3:&t;mov&t;%0, %3&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;b&t;2b&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.previous&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&quot;&t;.align&t;3&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.long&t;1b, 3b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.previous&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;+r&quot; (err)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;r&quot; (x), &quot;r&quot; (__pu_addr), &quot;i&quot; (-EFAULT)&t;&t;&bslash;&n;&t;: &quot;cc&quot;)
macro_line|#ifndef __ARMEB__
DECL|macro|__reg_oper0
mdefine_line|#define&t;__reg_oper0&t;&quot;%R2&quot;
DECL|macro|__reg_oper1
mdefine_line|#define&t;__reg_oper1&t;&quot;%Q2&quot;
macro_line|#else
DECL|macro|__reg_oper0
mdefine_line|#define&t;__reg_oper0&t;&quot;%Q2&quot;
DECL|macro|__reg_oper1
mdefine_line|#define&t;__reg_oper1&t;&quot;%R2&quot;
macro_line|#endif
DECL|macro|__put_user_asm_dword
mdefine_line|#define __put_user_asm_dword(x,__pu_addr,err)&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;1:&t;strt&t;&quot; __reg_oper1 &quot;, [%1], #4&bslash;n&quot;&t;&t;&bslash;&n;&t;&quot;2:&t;strt&t;&quot; __reg_oper0 &quot;, [%1], #0&bslash;n&quot;&t;&t;&bslash;&n;&t;&quot;3:&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&quot;&t;.align&t;2&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;4:&t;mov&t;%0, %3&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;b&t;3b&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.previous&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&quot;&t;.align&t;3&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.long&t;1b, 4b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.long&t;2b, 4b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.previous&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;+r&quot; (err), &quot;+r&quot; (__pu_addr)&t;&t;&t;&t;&bslash;&n;&t;: &quot;r&quot; (x), &quot;i&quot; (-EFAULT)&t;&t;&t;&t;&bslash;&n;&t;: &quot;cc&quot;)
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
id|__user
op_star
id|from
comma
r_int
r_int
id|n
)paren
suffix:semicolon
r_extern
r_int
r_int
id|__arch_copy_to_user
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
suffix:semicolon
r_extern
r_int
r_int
id|__arch_clear_user
c_func
(paren
r_void
id|__user
op_star
id|addr
comma
r_int
r_int
id|n
)paren
suffix:semicolon
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
id|__user
op_star
id|from
comma
r_int
r_int
id|count
)paren
suffix:semicolon
r_extern
r_int
r_int
id|__arch_strnlen_user
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
suffix:semicolon
DECL|function|copy_from_user
r_static
r_inline
r_int
r_int
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
id|__arch_copy_from_user
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
multiline_comment|/* security hole - plug it */
id|memzero
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
DECL|function|__copy_from_user
r_static
r_inline
r_int
r_int
id|__copy_from_user
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
r_return
id|__arch_copy_from_user
c_func
(paren
id|to
comma
id|from
comma
id|n
)paren
suffix:semicolon
)brace
DECL|function|copy_to_user
r_static
r_inline
r_int
r_int
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
id|__arch_copy_to_user
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
DECL|function|__copy_to_user
r_static
r_inline
r_int
r_int
id|__copy_to_user
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
r_return
id|__arch_copy_to_user
c_func
(paren
id|to
comma
id|from
comma
id|n
)paren
suffix:semicolon
)brace
DECL|macro|__copy_to_user_inatomic
mdefine_line|#define __copy_to_user_inatomic __copy_to_user
DECL|macro|__copy_from_user_inatomic
mdefine_line|#define __copy_from_user_inatomic __copy_from_user
DECL|function|clear_user
r_static
r_inline
r_int
r_int
id|clear_user
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
id|__arch_clear_user
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
DECL|function|__clear_user
r_static
r_inline
r_int
r_int
id|__clear_user
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
r_return
id|__arch_clear_user
c_func
(paren
id|to
comma
id|n
)paren
suffix:semicolon
)brace
DECL|function|strncpy_from_user
r_static
r_inline
r_int
id|strncpy_from_user
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
id|res
op_assign
id|__arch_strncpy_from_user
c_func
(paren
id|dst
comma
id|src
comma
id|count
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
DECL|function|__strncpy_from_user
r_static
r_inline
r_int
id|__strncpy_from_user
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
r_return
id|__arch_strncpy_from_user
c_func
(paren
id|dst
comma
id|src
comma
id|count
)paren
suffix:semicolon
)brace
DECL|macro|strlen_user
mdefine_line|#define strlen_user(s)&t;strnlen_user(s, ~0UL &gt;&gt; 1)
DECL|function|strnlen_user
r_static
r_inline
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
id|res
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|__addr_ok
c_func
(paren
id|s
)paren
)paren
id|res
op_assign
id|__arch_strnlen_user
c_func
(paren
id|s
comma
id|n
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
macro_line|#endif /* _ASMARM_UACCESS_H */
eof
