multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1996, 1997, 1998, 1999, 2000 by Ralf Baechle&n; * Copyright (C) 1999, 2000 Silicon Graphics, Inc.&n; */
macro_line|#ifndef _ASM_UACCESS_H
DECL|macro|_ASM_UACCESS_H
mdefine_line|#define _ASM_UACCESS_H
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
DECL|macro|STR
mdefine_line|#define STR(x)  __STR(x)
DECL|macro|__STR
mdefine_line|#define __STR(x)  #x
multiline_comment|/*&n; * The fs value determines whether argument validity checking should be&n; * performed or not.  If get_fs() == USER_DS, checking is performed, with&n; * get_fs() == KERNEL_DS, checking is bypassed.&n; *&n; * For historical reasons, these macros are grossly misnamed.&n; */
DECL|macro|KERNEL_DS
mdefine_line|#define KERNEL_DS&t;((mm_segment_t) { (unsigned long) 0L })
DECL|macro|USER_DS
mdefine_line|#define USER_DS&t;&t;((mm_segment_t) { (unsigned long) -1L })
DECL|macro|VERIFY_READ
mdefine_line|#define VERIFY_READ    0
DECL|macro|VERIFY_WRITE
mdefine_line|#define VERIFY_WRITE   1
DECL|macro|get_fs
mdefine_line|#define get_fs()        (current-&gt;thread.current_ds)
DECL|macro|get_ds
mdefine_line|#define get_ds()&t;(KERNEL_DS)
DECL|macro|set_fs
mdefine_line|#define set_fs(x)       (current-&gt;thread.current_ds=(x))
DECL|macro|segment_eq
mdefine_line|#define segment_eq(a,b)&t;((a).seg == (b).seg)
multiline_comment|/*&n; * Is a address valid? This does a straighforward calculation rather&n; * than tests.&n; *&n; * Address valid if:&n; *  - &quot;addr&quot; doesn&squot;t have any high-bits set&n; *  - AND &quot;size&quot; doesn&squot;t have any high-bits set&n; *  - AND &quot;addr+size&quot; doesn&squot;t have any high-bits set&n; *  - OR we are in kernel mode.&n; */
DECL|macro|__ua_size
mdefine_line|#define __ua_size(size)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(__builtin_constant_p(size) &amp;&amp; (signed long) (size) &gt; 0 ? 0 : (size))
DECL|macro|__access_ok
mdefine_line|#define __access_ok(addr,size,mask)                                     &bslash;&n;&t;(((signed long)((mask)&amp;(addr | (addr + size) | __ua_size(size)))) &gt;= 0)
DECL|macro|__access_mask
mdefine_line|#define __access_mask ((long)(get_fs().seg))
DECL|macro|access_ok
mdefine_line|#define access_ok(type,addr,size) &bslash;&n;__access_ok(((unsigned long)(addr)),(size),__access_mask)
DECL|function|verify_area
r_extern
r_inline
r_int
id|verify_area
c_func
(paren
r_int
id|type
comma
r_const
r_void
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
multiline_comment|/*&n; * Uh, these should become the main single-value transfer routines ...&n; * They automatically use the right size if we just have the right&n; * pointer type ...&n; *&n; * As MIPS uses the same address space for kernel and user data, we&n; * can just do these as direct assignments.&n; *&n; * Careful to not&n; * (a) re-use the arguments for side effects (sizeof is ok)&n; * (b) require any knowledge of processes at this stage&n; */
DECL|macro|put_user
mdefine_line|#define put_user(x,ptr)&t;&bslash;&n;&t;__put_user_check((__typeof__(*(ptr)))(x),(ptr),sizeof(*(ptr)))
DECL|macro|get_user
mdefine_line|#define get_user(x,ptr) &bslash;&n;&t;__get_user_check((__typeof__(*(ptr)))(x),(ptr),sizeof(*(ptr)))
multiline_comment|/*&n; * The &quot;__xxx&quot; versions do not do address space checking, useful when&n; * doing multiple accesses to the same area (the user has to do the&n; * checks by hand with &quot;access_ok()&quot;)&n; */
DECL|macro|__put_user
mdefine_line|#define __put_user(x,ptr) &bslash;&n;&t;__put_user_nocheck((__typeof__(*(ptr)))(x),(ptr),sizeof(*(ptr)))
DECL|macro|__get_user
mdefine_line|#define __get_user(x,ptr) &bslash;&n;&t;__get_user_nocheck((__typeof__(*(ptr)))(x),(ptr),sizeof(*(ptr)))
DECL|struct|__large_struct
DECL|member|buf
r_struct
id|__large_struct
(brace
r_int
r_int
id|buf
(braket
l_int|100
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|__m
mdefine_line|#define __m(x) (*(struct __large_struct *)(x))
multiline_comment|/*&n; * Yuck.  We need two variants, one for 64bit operation and one&n; * for 32 bit mode and old iron.&n; */
macro_line|#ifdef __mips64
DECL|macro|__GET_USER_DW
mdefine_line|#define __GET_USER_DW __get_user_asm(&quot;ld&quot;)
macro_line|#else
DECL|macro|__GET_USER_DW
mdefine_line|#define __GET_USER_DW __get_user_asm_ll32
macro_line|#endif
DECL|macro|__get_user_nocheck
mdefine_line|#define __get_user_nocheck(x,ptr,size) ({ &bslash;&n;long __gu_err; &bslash;&n;__typeof(*(ptr)) __gu_val; &bslash;&n;long __gu_addr; &bslash;&n;__asm__(&quot;&quot;:&quot;=r&quot; (__gu_val)); &bslash;&n;__gu_addr = (long) (ptr); &bslash;&n;__asm__(&quot;&quot;:&quot;=r&quot; (__gu_err)); &bslash;&n;switch (size) { &bslash;&n;case 1: __get_user_asm(&quot;lb&quot;); break; &bslash;&n;case 2: __get_user_asm(&quot;lh&quot;); break; &bslash;&n;case 4: __get_user_asm(&quot;lw&quot;); break; &bslash;&n;case 8: __GET_USER_DW; break; &bslash;&n;default: __get_user_unknown(); break; &bslash;&n;} x = (__typeof__(*(ptr))) __gu_val; __gu_err; })
DECL|macro|__get_user_check
mdefine_line|#define __get_user_check(x,ptr,size) ({ &bslash;&n;long __gu_err; &bslash;&n;__typeof__(*(ptr)) __gu_val; &bslash;&n;long __gu_addr; &bslash;&n;__asm__(&quot;&quot;:&quot;=r&quot; (__gu_val)); &bslash;&n;__gu_addr = (long) (ptr); &bslash;&n;__asm__(&quot;&quot;:&quot;=r&quot; (__gu_err)); &bslash;&n;if (__access_ok(__gu_addr,size,__access_mask)) { &bslash;&n;switch (size) { &bslash;&n;case 1: __get_user_asm(&quot;lb&quot;); break; &bslash;&n;case 2: __get_user_asm(&quot;lh&quot;); break; &bslash;&n;case 4: __get_user_asm(&quot;lw&quot;); break; &bslash;&n;case 8: __GET_USER_DW; break; &bslash;&n;default: __get_user_unknown(); break; &bslash;&n;} } x = (__typeof__(*(ptr))) __gu_val; __gu_err; })
DECL|macro|__get_user_asm
mdefine_line|#define __get_user_asm(insn) &bslash;&n;({ &bslash;&n;__asm__ __volatile__( &bslash;&n;&t;&quot;1:&bslash;t&quot; insn &quot;&bslash;t%1,%2&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;move&bslash;t%0,$0&bslash;n&quot; &bslash;&n;&t;&quot;2:&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.section&bslash;t.fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot; &bslash;&n;&t;&quot;3:&bslash;tli&bslash;t%0,%3&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;move&bslash;t%1,$0&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;j&bslash;t2b&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.previous&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.section&bslash;t__ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.word&bslash;t1b,3b&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.previous&quot; &bslash;&n;&t;:&quot;=r&quot; (__gu_err), &quot;=r&quot; (__gu_val) &bslash;&n;&t;:&quot;o&quot; (__m(__gu_addr)), &quot;i&quot; (-EFAULT)); })
multiline_comment|/*&n; * Get a long long 64 using 32 bit registers.&n; */
DECL|macro|__get_user_asm_ll32
mdefine_line|#define __get_user_asm_ll32 &bslash;&n;({ &bslash;&n;__asm__ __volatile__( &bslash;&n;&t;&quot;1:&bslash;tlw&bslash;t%1,%2&bslash;n&quot; &bslash;&n;&t;&quot;2:&bslash;tlw&bslash;t%D1,%3&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;move&bslash;t%0,$0&bslash;n&quot; &bslash;&n;&t;&quot;3:&bslash;t.section&bslash;t.fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot; &bslash;&n;&t;&quot;4:&bslash;tli&bslash;t%0,%4&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;move&bslash;t%1,$0&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;move&bslash;t%D1,$0&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;j&bslash;t3b&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.previous&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.section&bslash;t__ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.word&bslash;t1b,4b&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.word&bslash;t2b,4b&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.previous&quot; &bslash;&n;&t;:&quot;=r&quot; (__gu_err), &quot;=&amp;r&quot; (__gu_val) &bslash;&n;&t;:&quot;o&quot; (__m(__gu_addr)), &quot;o&quot; (__m(__gu_addr + 4)), &bslash;&n;&t; &quot;i&quot; (-EFAULT)); })
r_extern
r_void
id|__get_user_unknown
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * Yuck.  We need two variants, one for 64bit operation and one&n; * for 32 bit mode and old iron.&n; */
macro_line|#ifdef __mips64
DECL|macro|__PUT_USER_DW
mdefine_line|#define __PUT_USER_DW __put_user_asm(&quot;sd&quot;)
macro_line|#else
DECL|macro|__PUT_USER_DW
mdefine_line|#define __PUT_USER_DW __put_user_asm_ll32
macro_line|#endif
DECL|macro|__put_user_nocheck
mdefine_line|#define __put_user_nocheck(x,ptr,size) ({ &bslash;&n;long __pu_err; &bslash;&n;__typeof__(*(ptr)) __pu_val; &bslash;&n;long __pu_addr; &bslash;&n;__pu_val = (x); &bslash;&n;__pu_addr = (long) (ptr); &bslash;&n;__asm__(&quot;&quot;:&quot;=r&quot; (__pu_err)); &bslash;&n;switch (size) { &bslash;&n;case 1: __put_user_asm(&quot;sb&quot;); break; &bslash;&n;case 2: __put_user_asm(&quot;sh&quot;); break; &bslash;&n;case 4: __put_user_asm(&quot;sw&quot;); break; &bslash;&n;case 8: __PUT_USER_DW; break; &bslash;&n;default: __put_user_unknown(); break; &bslash;&n;} __pu_err; })
DECL|macro|__put_user_check
mdefine_line|#define __put_user_check(x,ptr,size) ({ &bslash;&n;long __pu_err; &bslash;&n;__typeof__(*(ptr)) __pu_val; &bslash;&n;long __pu_addr; &bslash;&n;__pu_val = (x); &bslash;&n;__pu_addr = (long) (ptr); &bslash;&n;__asm__(&quot;&quot;:&quot;=r&quot; (__pu_err)); &bslash;&n;if (__access_ok(__pu_addr,size,__access_mask)) { &bslash;&n;switch (size) { &bslash;&n;case 1: __put_user_asm(&quot;sb&quot;); break; &bslash;&n;case 2: __put_user_asm(&quot;sh&quot;); break; &bslash;&n;case 4: __put_user_asm(&quot;sw&quot;); break; &bslash;&n;case 8: __PUT_USER_DW; break; &bslash;&n;default: __put_user_unknown(); break; &bslash;&n;} } __pu_err; })
DECL|macro|__put_user_asm
mdefine_line|#define __put_user_asm(insn) &bslash;&n;({ &bslash;&n;__asm__ __volatile__( &bslash;&n;&t;&quot;1:&bslash;t&quot; insn &quot;&bslash;t%z1, %2&bslash;t&bslash;t&bslash;t# __put_user_asm&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;move&bslash;t%0, $0&bslash;n&quot; &bslash;&n;&t;&quot;2:&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.section&bslash;t.fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot; &bslash;&n;&t;&quot;3:&bslash;tli&bslash;t%0,%3&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;j&bslash;t2b&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.previous&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.section&bslash;t__ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.word&bslash;t1b,3b&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.previous&quot; &bslash;&n;&t;:&quot;=r&quot; (__pu_err) &bslash;&n;&t;:&quot;Jr&quot; (__pu_val), &quot;o&quot; (__m(__pu_addr)), &quot;i&quot; (-EFAULT)); })
DECL|macro|__put_user_asm_ll32
mdefine_line|#define __put_user_asm_ll32 &bslash;&n;({ &bslash;&n;__asm__ __volatile__( &bslash;&n;&t;&quot;1:&bslash;tsw&bslash;t%1, %2&bslash;t&bslash;t&bslash;t# __put_user_asm_ll32&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;2:&bslash;tsw&bslash;t%D1, %3&bslash;n&quot; &bslash;&n;&t;&quot;move&bslash;t%0, $0&bslash;n&quot; &bslash;&n;&t;&quot;3:&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.section&bslash;t.fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot; &bslash;&n;&t;&quot;4:&bslash;tli&bslash;t%0,%4&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;j&bslash;t3b&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.previous&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.section&bslash;t__ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.word&bslash;t1b,4b&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.word&bslash;t2b,4b&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.previous&quot; &bslash;&n;&t;:&quot;=r&quot; (__pu_err) &bslash;&n;&t;:&quot;r&quot; (__pu_val), &quot;o&quot; (__m(__pu_addr)), &quot;o&quot; (__m(__pu_addr + 4)), &bslash;&n;&t; &quot;i&quot; (-EFAULT)); })
r_extern
r_void
id|__put_user_unknown
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * We&squot;re generating jump to subroutines which will be outside the range of&n; * jump instructions&n; */
macro_line|#ifdef MODULE
DECL|macro|__MODULE_JAL
mdefine_line|#define __MODULE_JAL(destination) &bslash;&n;&t;&quot;.set&bslash;tnoat&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;la&bslash;t$1, &quot; #destination &quot;&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;jalr&bslash;t$1&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.set&bslash;tat&bslash;n&bslash;t&quot;
macro_line|#else
DECL|macro|__MODULE_JAL
mdefine_line|#define __MODULE_JAL(destination) &bslash;&n;&t;&quot;jal&bslash;t&quot; #destination &quot;&bslash;n&bslash;t&quot;
macro_line|#endif
r_extern
r_int
id|__copy_user
c_func
(paren
r_void
op_star
id|__to
comma
r_const
r_void
op_star
id|__from
comma
r_int
id|__n
)paren
suffix:semicolon
DECL|macro|__copy_to_user
mdefine_line|#define __copy_to_user(to,from,n) ({ &bslash;&n;&t;void *__cu_to; &bslash;&n;&t;const void *__cu_from; &bslash;&n;&t;long __cu_len; &bslash;&n;&t;&bslash;&n;&t;__cu_to = (to); &bslash;&n;&t;__cu_from = (from); &bslash;&n;&t;__cu_len = (n); &bslash;&n;&t;__asm__ __volatile__( &bslash;&n;&t;&t;&quot;move&bslash;t$4, %1&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&quot;move&bslash;t$5, %2&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&quot;move&bslash;t$6, %3&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;__MODULE_JAL(__copy_user) &bslash;&n;&t;&t;&quot;move&bslash;t%0, $6&quot; &bslash;&n;&t;&t;: &quot;=r&quot; (__cu_len) &bslash;&n;&t;&t;: &quot;r&quot; (__cu_to), &quot;r&quot; (__cu_from), &quot;r&quot; (__cu_len) &bslash;&n;&t;&t;: &quot;$4&quot;, &quot;$5&quot;, &quot;$6&quot;, &quot;$8&quot;, &quot;$9&quot;, &quot;$10&quot;, &quot;$11&quot;, &quot;$12&quot;, &quot;$15&quot;, &bslash;&n;&t;&t;  &quot;$24&quot;, &quot;$31&quot;,&quot;memory&quot;); &bslash;&n;&t;__cu_len; &bslash;&n;})
DECL|macro|__copy_from_user
mdefine_line|#define __copy_from_user(to,from,n) ({ &bslash;&n;&t;void *__cu_to; &bslash;&n;&t;const void *__cu_from; &bslash;&n;&t;long __cu_len; &bslash;&n;&t;&bslash;&n;&t;__cu_to = (to); &bslash;&n;&t;__cu_from = (from); &bslash;&n;&t;__cu_len = (n); &bslash;&n;&t;__asm__ __volatile__( &bslash;&n;&t;&t;&quot;move&bslash;t$4, %1&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&quot;move&bslash;t$5, %2&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&quot;move&bslash;t$6, %3&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&quot;.set&bslash;tnoreorder&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;__MODULE_JAL(__copy_user) &bslash;&n;&t;&t;&quot;.set&bslash;tnoat&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&quot;addu&bslash;t$1, %2, %3&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&quot;.set&bslash;tat&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&quot;.set&bslash;treorder&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&quot;move&bslash;t%0, $6&quot; &bslash;&n;&t;&t;: &quot;=r&quot; (__cu_len) &bslash;&n;&t;&t;: &quot;r&quot; (__cu_to), &quot;r&quot; (__cu_from), &quot;r&quot; (__cu_len) &bslash;&n;&t;&t;: &quot;$4&quot;, &quot;$5&quot;, &quot;$6&quot;, &quot;$8&quot;, &quot;$9&quot;, &quot;$10&quot;, &quot;$11&quot;, &quot;$12&quot;, &quot;$15&quot;, &bslash;&n;&t;&t;  &quot;$24&quot;, &quot;$31&quot;,&quot;memory&quot;); &bslash;&n;&t;__cu_len; &bslash;&n;})
DECL|macro|copy_to_user
mdefine_line|#define copy_to_user(to,from,n) ({ &bslash;&n;&t;void *__cu_to; &bslash;&n;&t;const void *__cu_from; &bslash;&n;&t;long __cu_len; &bslash;&n;&t;&bslash;&n;&t;__cu_to = (to); &bslash;&n;&t;__cu_from = (from); &bslash;&n;&t;__cu_len = (n); &bslash;&n;&t;if (access_ok(VERIFY_WRITE, __cu_to, __cu_len)) &bslash;&n;&t;&t;__asm__ __volatile__( &bslash;&n;&t;&t;&t;&quot;move&bslash;t$4, %1&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&t;&quot;move&bslash;t$5, %2&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&t;&quot;move&bslash;t$6, %3&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&t;__MODULE_JAL(__copy_user) &bslash;&n;&t;&t;&t;&quot;move&bslash;t%0, $6&quot; &bslash;&n;&t;&t;&t;: &quot;=r&quot; (__cu_len) &bslash;&n;&t;&t;&t;: &quot;r&quot; (__cu_to), &quot;r&quot; (__cu_from), &quot;r&quot; (__cu_len) &bslash;&n;&t;&t;&t;: &quot;$4&quot;, &quot;$5&quot;, &quot;$6&quot;, &quot;$8&quot;, &quot;$9&quot;, &quot;$10&quot;, &quot;$11&quot;, &quot;$12&quot;, &bslash;&n;&t;&t;&t;  &quot;$15&quot;, &quot;$24&quot;, &quot;$31&quot;,&quot;memory&quot;); &bslash;&n;&t;__cu_len; &bslash;&n;})
DECL|macro|copy_from_user
mdefine_line|#define copy_from_user(to,from,n) ({ &bslash;&n;&t;void *__cu_to; &bslash;&n;&t;const void *__cu_from; &bslash;&n;&t;long __cu_len; &bslash;&n;&t;&bslash;&n;&t;__cu_to = (to); &bslash;&n;&t;__cu_from = (from); &bslash;&n;&t;__cu_len = (n); &bslash;&n;&t;if (access_ok(VERIFY_READ, __cu_from, __cu_len)) &bslash;&n;&t;&t;__asm__ __volatile__( &bslash;&n;&t;&t;&t;&quot;move&bslash;t$4, %1&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&t;&quot;move&bslash;t$5, %2&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&t;&quot;move&bslash;t$6, %3&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&t;&quot;.set&bslash;tnoreorder&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&t;__MODULE_JAL(__copy_user) &bslash;&n;&t;&t;&t;&quot;.set&bslash;tnoat&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&t;&quot;addu&bslash;t$1, %2, %3&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&t;&quot;.set&bslash;tat&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&t;&quot;.set&bslash;treorder&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&t;&quot;move&bslash;t%0, $6&quot; &bslash;&n;&t;&t;&t;: &quot;=r&quot; (__cu_len) &bslash;&n;&t;&t;&t;: &quot;r&quot; (__cu_to), &quot;r&quot; (__cu_from), &quot;r&quot; (__cu_len) &bslash;&n;&t;&t;&t;: &quot;$4&quot;, &quot;$5&quot;, &quot;$6&quot;, &quot;$8&quot;, &quot;$9&quot;, &quot;$10&quot;, &quot;$11&quot;, &quot;$12&quot;, &bslash;&n;&t;&t;&t;  &quot;$15&quot;, &quot;$24&quot;, &quot;$31&quot;,&quot;memory&quot;); &bslash;&n;&t;__cu_len; &bslash;&n;})
r_extern
r_inline
id|__kernel_size_t
DECL|function|__clear_user
id|__clear_user
c_func
(paren
r_void
op_star
id|addr
comma
id|__kernel_size_t
id|size
)paren
(brace
id|__kernel_size_t
id|res
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;move&bslash;t$4, %1&bslash;n&bslash;t&quot;
l_string|&quot;move&bslash;t$5, $0&bslash;n&bslash;t&quot;
l_string|&quot;move&bslash;t$6, %2&bslash;n&bslash;t&quot;
id|__MODULE_JAL
c_func
(paren
id|__bzero
)paren
l_string|&quot;move&bslash;t%0, $6&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|res
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;r&quot;
(paren
id|size
)paren
suffix:colon
l_string|&quot;$4&quot;
comma
l_string|&quot;$5&quot;
comma
l_string|&quot;$6&quot;
comma
l_string|&quot;$8&quot;
comma
l_string|&quot;$9&quot;
comma
l_string|&quot;$31&quot;
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
DECL|macro|clear_user
mdefine_line|#define clear_user(addr,n) ({ &bslash;&n;void * __cl_addr = (addr); &bslash;&n;unsigned long __cl_size = (n); &bslash;&n;if (__cl_size &amp;&amp; access_ok(VERIFY_WRITE, ((unsigned long)(__cl_addr)), __cl_size)) &bslash;&n;__cl_size = __clear_user(__cl_addr, __cl_size); &bslash;&n;__cl_size; })
multiline_comment|/*&n; * Returns: -EFAULT if exception before terminator, N if the entire&n; * buffer filled, else strlen.&n; */
r_extern
r_inline
r_int
DECL|function|__strncpy_from_user
id|__strncpy_from_user
c_func
(paren
r_char
op_star
id|__to
comma
r_const
r_char
op_star
id|__from
comma
r_int
id|__len
)paren
(brace
r_int
id|res
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;move&bslash;t$4, %1&bslash;n&bslash;t&quot;
l_string|&quot;move&bslash;t$5, %2&bslash;n&bslash;t&quot;
l_string|&quot;move&bslash;t$6, %3&bslash;n&bslash;t&quot;
id|__MODULE_JAL
c_func
(paren
id|__strncpy_from_user_nocheck_asm
)paren
l_string|&quot;move&bslash;t%0, $2&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|res
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|__to
)paren
comma
l_string|&quot;r&quot;
(paren
id|__from
)paren
comma
l_string|&quot;r&quot;
(paren
id|__len
)paren
suffix:colon
l_string|&quot;$2&quot;
comma
l_string|&quot;$3&quot;
comma
l_string|&quot;$4&quot;
comma
l_string|&quot;$5&quot;
comma
l_string|&quot;$6&quot;
comma
l_string|&quot;$8&quot;
comma
l_string|&quot;$31&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
r_extern
r_inline
r_int
DECL|function|strncpy_from_user
id|strncpy_from_user
c_func
(paren
r_char
op_star
id|__to
comma
r_const
r_char
op_star
id|__from
comma
r_int
id|__len
)paren
(brace
r_int
id|res
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;move&bslash;t$4, %1&bslash;n&bslash;t&quot;
l_string|&quot;move&bslash;t$5, %2&bslash;n&bslash;t&quot;
l_string|&quot;move&bslash;t$6, %3&bslash;n&bslash;t&quot;
id|__MODULE_JAL
c_func
(paren
id|__strncpy_from_user_asm
)paren
l_string|&quot;move&bslash;t%0, $2&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|res
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|__to
)paren
comma
l_string|&quot;r&quot;
(paren
id|__from
)paren
comma
l_string|&quot;r&quot;
(paren
id|__len
)paren
suffix:colon
l_string|&quot;$2&quot;
comma
l_string|&quot;$3&quot;
comma
l_string|&quot;$4&quot;
comma
l_string|&quot;$5&quot;
comma
l_string|&quot;$6&quot;
comma
l_string|&quot;$8&quot;
comma
l_string|&quot;$31&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
multiline_comment|/* Returns: 0 if bad, string length+1 (memory size) of string if ok */
DECL|function|__strlen_user
r_extern
r_inline
r_int
id|__strlen_user
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
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;move&bslash;t$4, %1&bslash;n&bslash;t&quot;
id|__MODULE_JAL
c_func
(paren
id|__strlen_user_nocheck_asm
)paren
l_string|&quot;move&bslash;t%0, $2&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|res
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|s
)paren
suffix:colon
l_string|&quot;$2&quot;
comma
l_string|&quot;$4&quot;
comma
l_string|&quot;$8&quot;
comma
l_string|&quot;$31&quot;
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
DECL|function|strlen_user
r_extern
r_inline
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
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;move&bslash;t$4, %1&bslash;n&bslash;t&quot;
id|__MODULE_JAL
c_func
(paren
id|__strlen_user_asm
)paren
l_string|&quot;move&bslash;t%0, $2&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|res
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|s
)paren
suffix:colon
l_string|&quot;$2&quot;
comma
l_string|&quot;$4&quot;
comma
l_string|&quot;$8&quot;
comma
l_string|&quot;$31&quot;
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
multiline_comment|/* Returns: 0 if bad, string length+1 (memory size) of string if ok */
DECL|function|__strnlen_user
r_extern
r_inline
r_int
id|__strnlen_user
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
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;move&bslash;t$4, %1&bslash;n&bslash;t&quot;
l_string|&quot;move&bslash;t$5, %2&bslash;n&bslash;t&quot;
id|__MODULE_JAL
c_func
(paren
id|__strnlen_user_nocheck_asm
)paren
l_string|&quot;move&bslash;t%0, $2&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|res
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|s
)paren
comma
l_string|&quot;r&quot;
(paren
id|n
)paren
suffix:colon
l_string|&quot;$2&quot;
comma
l_string|&quot;$4&quot;
comma
l_string|&quot;$5&quot;
comma
l_string|&quot;$8&quot;
comma
l_string|&quot;$31&quot;
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
DECL|function|strnlen_user
r_extern
r_inline
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
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;move&bslash;t$4, %1&bslash;n&bslash;t&quot;
l_string|&quot;move&bslash;t$5, %2&bslash;n&bslash;t&quot;
id|__MODULE_JAL
c_func
(paren
id|__strnlen_user_asm
)paren
l_string|&quot;move&bslash;t%0, $2&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|res
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|s
)paren
comma
l_string|&quot;r&quot;
(paren
id|n
)paren
suffix:colon
l_string|&quot;$2&quot;
comma
l_string|&quot;$4&quot;
comma
l_string|&quot;$5&quot;
comma
l_string|&quot;$8&quot;
comma
l_string|&quot;$31&quot;
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
DECL|struct|exception_table_entry
r_struct
id|exception_table_entry
(brace
DECL|member|insn
r_int
r_int
id|insn
suffix:semicolon
DECL|member|nextinsn
r_int
r_int
id|nextinsn
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Returns 0 if exception not found and fixup.unit otherwise.  */
r_extern
r_int
r_int
id|search_exception_table
c_func
(paren
r_int
r_int
id|addr
)paren
suffix:semicolon
multiline_comment|/* Returns the new pc */
DECL|macro|fixup_exception
mdefine_line|#define fixup_exception(map_reg, fixup_unit, pc)                &bslash;&n;({                                                              &bslash;&n;&t;fixup_unit;                                             &bslash;&n;})
macro_line|#endif /* _ASM_UACCESS_H */
eof
