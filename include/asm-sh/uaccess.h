multiline_comment|/* $Id: uaccess.h,v 1.13 2001/10/01 02:22:01 gniibe Exp $&n; *&n; * User space memory access functions&n; *&n; * Copyright (C) 1999  Niibe Yutaka&n; *&n; *  Based on:&n; *     MIPS implementation version 1.15 by&n; *              Copyright (C) 1996, 1997, 1998 by Ralf Baechle&n; *     and i386 version.&n; */
macro_line|#ifndef __ASM_SH_UACCESS_H
DECL|macro|__ASM_SH_UACCESS_H
mdefine_line|#define __ASM_SH_UACCESS_H
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
DECL|macro|VERIFY_READ
mdefine_line|#define VERIFY_READ    0
DECL|macro|VERIFY_WRITE
mdefine_line|#define VERIFY_WRITE   1
multiline_comment|/*&n; * The fs value determines whether argument validity checking should be&n; * performed or not.  If get_fs() == USER_DS, checking is performed, with&n; * get_fs() == KERNEL_DS, checking is bypassed.&n; *&n; * For historical reasons (Data Segment Register?), these macros are misnamed.&n; */
DECL|macro|MAKE_MM_SEG
mdefine_line|#define MAKE_MM_SEG(s)&t;((mm_segment_t) { (s) })
DECL|macro|KERNEL_DS
mdefine_line|#define KERNEL_DS&t;MAKE_MM_SEG(0xFFFFFFFF)
DECL|macro|USER_DS
mdefine_line|#define USER_DS&t;&t;MAKE_MM_SEG(0x80000000)
DECL|macro|get_ds
mdefine_line|#define get_ds()&t;(KERNEL_DS)
DECL|macro|get_fs
mdefine_line|#define get_fs()        (current-&gt;addr_limit)
DECL|macro|set_fs
mdefine_line|#define set_fs(x)       (current-&gt;addr_limit=(x))
DECL|macro|segment_eq
mdefine_line|#define segment_eq(a,b)&t;((a).seg == (b).seg)
DECL|macro|__addr_ok
mdefine_line|#define __addr_ok(addr) ((unsigned long)(addr) &lt; (current-&gt;addr_limit.seg))
multiline_comment|/*&n; * Uhhuh, this needs 33-bit arithmetic. We have a carry..&n; *&n; * sum := addr + size;  carry? --&gt; flag = true;&n; * if (sum &gt;= addr_limit) flag = true;&n; */
DECL|macro|__range_ok
mdefine_line|#define __range_ok(addr,size) ({&t;&t;&t;&t;&t;      &bslash;&n;&t;unsigned long flag,sum; &t;&t;&t;&t;&t;      &bslash;&n;&t;__asm__(&quot;clrt; addc %3, %1; movt %0; cmp/hi %4, %1; rotcl %0&quot;&t;      &bslash;&n;&t;&t;:&quot;=&amp;r&quot; (flag), &quot;=r&quot; (sum) &t;&t;&t;&t;      &bslash;&n;&t;&t;:&quot;1&quot; (addr), &quot;r&quot; ((int)(size)), &quot;r&quot; (current-&gt;addr_limit.seg) &bslash;&n;&t;&t;:&quot;t&quot;); &t;&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;flag; })
DECL|macro|access_ok
mdefine_line|#define access_ok(type,addr,size) (__range_ok(addr,size) == 0)
DECL|macro|__access_ok
mdefine_line|#define __access_ok(addr,size) (__range_ok(addr,size) == 0)
DECL|function|verify_area
r_static
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
multiline_comment|/*&n; * Uh, these should become the main single-value transfer routines ...&n; * They automatically use the right size if we just have the right&n; * pointer type ...&n; *&n; * As SuperH uses the same address space for kernel and user data, we&n; * can just do these as direct assignments.&n; *&n; * Careful to not&n; * (a) re-use the arguments for side effects (sizeof is ok)&n; * (b) require any knowledge of processes at this stage&n; */
DECL|macro|put_user
mdefine_line|#define put_user(x,ptr)&t;__put_user_check((x),(ptr),sizeof(*(ptr)))
DECL|macro|get_user
mdefine_line|#define get_user(x,ptr) __get_user_check((x),(ptr),sizeof(*(ptr)))
multiline_comment|/*&n; * The &quot;__xxx&quot; versions do not do address space checking, useful when&n; * doing multiple accesses to the same area (the user has to do the&n; * checks by hand with &quot;access_ok()&quot;)&n; */
DECL|macro|__put_user
mdefine_line|#define __put_user(x,ptr) __put_user_nocheck((x),(ptr),sizeof(*(ptr)))
DECL|macro|__get_user
mdefine_line|#define __get_user(x,ptr) __get_user_nocheck((x),(ptr),sizeof(*(ptr)))
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
DECL|macro|__get_user_nocheck
mdefine_line|#define __get_user_nocheck(x,ptr,size) ({ &bslash;&n;long __gu_err; &bslash;&n;__typeof(*(ptr)) __gu_val; &bslash;&n;long __gu_addr; &bslash;&n;__asm__(&quot;&quot;:&quot;=r&quot; (__gu_val)); &bslash;&n;__gu_addr = (long) (ptr); &bslash;&n;__asm__(&quot;&quot;:&quot;=r&quot; (__gu_err)); &bslash;&n;switch (size) { &bslash;&n;case 1: __get_user_asm(&quot;b&quot;); break; &bslash;&n;case 2: __get_user_asm(&quot;w&quot;); break; &bslash;&n;case 4: __get_user_asm(&quot;l&quot;); break; &bslash;&n;default: __get_user_unknown(); break; &bslash;&n;} x = (__typeof__(*(ptr))) __gu_val; __gu_err; })
DECL|macro|__get_user_check
mdefine_line|#define __get_user_check(x,ptr,size) ({ &bslash;&n;long __gu_err; &bslash;&n;__typeof__(*(ptr)) __gu_val; &bslash;&n;long __gu_addr; &bslash;&n;__asm__(&quot;&quot;:&quot;=r&quot; (__gu_val)); &bslash;&n;__gu_addr = (long) (ptr); &bslash;&n;__asm__(&quot;&quot;:&quot;=r&quot; (__gu_err)); &bslash;&n;if (__access_ok(__gu_addr,size)) { &bslash;&n;switch (size) { &bslash;&n;case 1: __get_user_asm(&quot;b&quot;); break; &bslash;&n;case 2: __get_user_asm(&quot;w&quot;); break; &bslash;&n;case 4: __get_user_asm(&quot;l&quot;); break; &bslash;&n;default: __get_user_unknown(); break; &bslash;&n;} } x = (__typeof__(*(ptr))) __gu_val; __gu_err; })
DECL|macro|__get_user_asm
mdefine_line|#define __get_user_asm(insn) &bslash;&n;({ &bslash;&n;__asm__ __volatile__( &bslash;&n;&t;&quot;1:&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;mov.&quot; insn &quot;&t;%2, %1&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;mov&t;#0, %0&bslash;n&quot; &bslash;&n;&t;&quot;2:&bslash;n&quot; &bslash;&n;&t;&quot;.section&t;.fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot; &bslash;&n;&t;&quot;3:&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;mov&t;#0, %1&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;mov.l&t;4f, %0&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;jmp&t;@%0&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot; mov&t;%3, %0&bslash;n&quot; &bslash;&n;&t;&quot;4:&t;.long&t;2b&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.previous&bslash;n&quot; &bslash;&n;&t;&quot;.section&t;__ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.long&t;1b, 3b&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.previous&quot; &bslash;&n;&t;:&quot;=&amp;r&quot; (__gu_err), &quot;=&amp;r&quot; (__gu_val) &bslash;&n;&t;:&quot;m&quot; (__m(__gu_addr)), &quot;i&quot; (-EFAULT)); })
r_extern
r_void
id|__get_user_unknown
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|__put_user_nocheck
mdefine_line|#define __put_user_nocheck(x,ptr,size) ({ &bslash;&n;long __pu_err; &bslash;&n;__typeof__(*(ptr)) __pu_val; &bslash;&n;long __pu_addr; &bslash;&n;__pu_val = (x); &bslash;&n;__pu_addr = (long) (ptr); &bslash;&n;__asm__(&quot;&quot;:&quot;=r&quot; (__pu_err)); &bslash;&n;switch (size) { &bslash;&n;case 1: __put_user_asm(&quot;b&quot;); break; &bslash;&n;case 2: __put_user_asm(&quot;w&quot;); break; &bslash;&n;case 4: __put_user_asm(&quot;l&quot;); break; &bslash;&n;case 8: __put_user_u64(__pu_val,__pu_addr,__pu_err); break; &bslash;&n;default: __put_user_unknown(); break; &bslash;&n;} __pu_err; })
DECL|macro|__put_user_check
mdefine_line|#define __put_user_check(x,ptr,size) ({ &bslash;&n;long __pu_err; &bslash;&n;__typeof__(*(ptr)) __pu_val; &bslash;&n;long __pu_addr; &bslash;&n;__pu_val = (x); &bslash;&n;__pu_addr = (long) (ptr); &bslash;&n;__asm__(&quot;&quot;:&quot;=r&quot; (__pu_err)); &bslash;&n;if (__access_ok(__pu_addr,size)) { &bslash;&n;switch (size) { &bslash;&n;case 1: __put_user_asm(&quot;b&quot;); break; &bslash;&n;case 2: __put_user_asm(&quot;w&quot;); break; &bslash;&n;case 4: __put_user_asm(&quot;l&quot;); break; &bslash;&n;case 8: __put_user_u64(__pu_val,__pu_addr,__pu_err); break; &bslash;&n;default: __put_user_unknown(); break; &bslash;&n;} } __pu_err; })
DECL|macro|__put_user_asm
mdefine_line|#define __put_user_asm(insn) &bslash;&n;({ &bslash;&n;__asm__ __volatile__( &bslash;&n;&t;&quot;1:&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;mov.&quot; insn &quot;&t;%1, %2&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;mov&t;#0, %0&bslash;n&quot; &bslash;&n;&t;&quot;2:&bslash;n&quot; &bslash;&n;&t;&quot;.section&t;.fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot; &bslash;&n;&t;&quot;3:&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;nop&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;mov.l&t;4f, %0&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;jmp&t;@%0&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;mov&t;%3, %0&bslash;n&quot; &bslash;&n;&t;&quot;4:&t;.long&t;2b&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.previous&bslash;n&quot; &bslash;&n;&t;&quot;.section&t;__ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.long&t;1b, 3b&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.previous&quot; &bslash;&n;&t;:&quot;=&amp;r&quot; (__pu_err) &bslash;&n;&t;:&quot;r&quot; (__pu_val), &quot;m&quot; (__m(__pu_addr)), &quot;i&quot; (-EFAULT) &bslash;&n;        :&quot;memory&quot;); })
macro_line|#if defined(__LITTLE_ENDIAN__)
DECL|macro|__put_user_u64
mdefine_line|#define __put_user_u64(val,addr,retval) &bslash;&n;({ &bslash;&n;__asm__ __volatile__( &bslash;&n;&t;&quot;1:&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;mov.l&t;%R1,%2&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;mov.l&t;%S1,%T2&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;mov&t;#0,%0&bslash;n&quot; &bslash;&n;&t;&quot;2:&bslash;n&quot; &bslash;&n;&t;&quot;.section&t;.fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot; &bslash;&n;&t;&quot;3:&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;nop&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;mov.l&t;4f,%0&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;jmp&t;@%0&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot; mov&t;%3,%0&bslash;n&quot; &bslash;&n;&t;&quot;4:&t;.long&t;2b&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.previous&bslash;n&quot; &bslash;&n;&t;&quot;.section&t;__ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.long&t;1b, 3b&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.previous&quot; &bslash;&n;&t;: &quot;=r&quot; (retval) &bslash;&n;&t;: &quot;r&quot; (val), &quot;m&quot; (__m(addr)), &quot;i&quot; (-EFAULT) &bslash;&n;        : &quot;memory&quot;); })
macro_line|#else
DECL|macro|__put_user_u64
mdefine_line|#define __put_user_u64(val,addr,retval) &bslash;&n;({ &bslash;&n;__asm__ __volatile__( &bslash;&n;&t;&quot;1:&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;mov.l&t;%S1,%2&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;mov.l&t;%R1,%T2&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;mov&t;#0,%0&bslash;n&quot; &bslash;&n;&t;&quot;2:&bslash;n&quot; &bslash;&n;&t;&quot;.section&t;.fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot; &bslash;&n;&t;&quot;3:&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;nop&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;mov.l&t;4f,%0&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;jmp&t;@%0&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot; mov&t;%3,%0&bslash;n&quot; &bslash;&n;&t;&quot;4:&t;.long&t;2b&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.previous&bslash;n&quot; &bslash;&n;&t;&quot;.section&t;__ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.long&t;1b, 3b&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.previous&quot; &bslash;&n;&t;: &quot;=r&quot; (retval) &bslash;&n;&t;: &quot;r&quot; (val), &quot;m&quot; (__m(addr)), &quot;i&quot; (-EFAULT) &bslash;&n;        : &quot;memory&quot;); })
macro_line|#endif
r_extern
r_void
id|__put_user_unknown
c_func
(paren
r_void
)paren
suffix:semicolon
"&f;"
multiline_comment|/* Generic arbitrary sized copy.  */
multiline_comment|/* Return the number of bytes NOT copied */
multiline_comment|/* XXX: should be such that: 4byte and the rest. */
r_static
id|__inline__
id|__kernel_size_t
DECL|function|__copy_user
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
id|__kernel_size_t
id|__n
)paren
(brace
r_int
r_int
id|__dummy
comma
id|_f
comma
id|_t
suffix:semicolon
id|__kernel_size_t
id|res
suffix:semicolon
r_if
c_cond
(paren
(paren
id|res
op_assign
id|__n
)paren
)paren
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;9:&bslash;n&bslash;t&quot;
l_string|&quot;mov.b&t;@%2+, %1&bslash;n&bslash;t&quot;
l_string|&quot;dt&t;%0&bslash;n&quot;
l_string|&quot;1:&bslash;n&bslash;t&quot;
l_string|&quot;mov.b&t;%1, @%3&bslash;n&bslash;t&quot;
l_string|&quot;bf/s&t;9b&bslash;n&bslash;t&quot;
l_string|&quot; add&t;#1, %3&bslash;n&quot;
l_string|&quot;2:&bslash;n&quot;
l_string|&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
l_string|&quot;3:&bslash;n&bslash;t&quot;
l_string|&quot;mov.l&t;5f, %1&bslash;n&bslash;t&quot;
l_string|&quot;jmp&t;@%1&bslash;n&bslash;t&quot;
l_string|&quot; add&t;#1, %0&bslash;n&bslash;t&quot;
l_string|&quot;.balign 4&bslash;n&quot;
l_string|&quot;5:&t;.long 2b&bslash;n&quot;
l_string|&quot;.previous&bslash;n&quot;
l_string|&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;
l_string|&quot;&t;.balign 4&bslash;n&quot;
l_string|&quot;&t;.long 9b,2b&bslash;n&quot;
l_string|&quot;&t;.long 1b,3b&bslash;n&quot;
l_string|&quot;.previous&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|res
)paren
comma
l_string|&quot;=&amp;z&quot;
(paren
id|__dummy
)paren
comma
l_string|&quot;=r&quot;
(paren
id|_f
)paren
comma
l_string|&quot;=r&quot;
(paren
id|_t
)paren
suffix:colon
l_string|&quot;2&quot;
(paren
id|__from
)paren
comma
l_string|&quot;3&quot;
(paren
id|__to
)paren
comma
l_string|&quot;0&quot;
(paren
id|res
)paren
suffix:colon
l_string|&quot;memory&quot;
comma
l_string|&quot;t&quot;
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
DECL|macro|copy_to_user
mdefine_line|#define copy_to_user(to,from,n) ({ &bslash;&n;void *__copy_to = (void *) (to); &bslash;&n;__kernel_size_t __copy_size = (__kernel_size_t) (n); &bslash;&n;__kernel_size_t __copy_res; &bslash;&n;if(__copy_size &amp;&amp; __access_ok((unsigned long)__copy_to, __copy_size)) { &bslash;&n;__copy_res = __copy_user(__copy_to, (void *) (from), __copy_size); &bslash;&n;} else __copy_res = __copy_size; &bslash;&n;__copy_res; })
DECL|macro|__copy_to_user
mdefine_line|#define __copy_to_user(to,from,n)&t;&t;&bslash;&n;&t;__copy_user((void *)(to),&t;&t;&bslash;&n;&t;&t;    (void *)(from), n)
DECL|macro|copy_from_user
mdefine_line|#define copy_from_user(to,from,n) ({ &bslash;&n;void *__copy_to = (void *) (to); &bslash;&n;void *__copy_from = (void *) (from); &bslash;&n;__kernel_size_t __copy_size = (__kernel_size_t) (n); &bslash;&n;__kernel_size_t __copy_res; &bslash;&n;if(__copy_size &amp;&amp; __access_ok((unsigned long)__copy_from, __copy_size)) { &bslash;&n;__copy_res = __copy_user(__copy_to, __copy_from, __copy_size); &bslash;&n;} else __copy_res = __copy_size; &bslash;&n;__copy_res; })
DECL|macro|__copy_from_user
mdefine_line|#define __copy_from_user(to,from,n)&t;&t;&bslash;&n;&t;__copy_user((void *)(to),&t;&t;&bslash;&n;&t;&t;    (void *)(from), n)
multiline_comment|/* XXX: Not sure it works well..&n;   should be such that: 4byte clear and the rest. */
r_static
id|__inline__
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
r_int
r_int
id|__a
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;9:&bslash;n&bslash;t&quot;
l_string|&quot;dt&t;%0&bslash;n&quot;
l_string|&quot;1:&bslash;n&bslash;t&quot;
l_string|&quot;mov.b&t;%4, @%1&bslash;n&bslash;t&quot;
l_string|&quot;bf/s&t;9b&bslash;n&bslash;t&quot;
l_string|&quot; add&t;#1, %1&bslash;n&quot;
l_string|&quot;2:&bslash;n&quot;
l_string|&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
l_string|&quot;3:&bslash;n&bslash;t&quot;
l_string|&quot;mov.l&t;4f, %1&bslash;n&bslash;t&quot;
l_string|&quot;jmp&t;@%1&bslash;n&bslash;t&quot;
l_string|&quot; nop&bslash;n&quot;
l_string|&quot;.balign 4&bslash;n&quot;
l_string|&quot;4:&t;.long 2b&bslash;n&quot;
l_string|&quot;.previous&bslash;n&quot;
l_string|&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;
l_string|&quot;&t;.balign 4&bslash;n&quot;
l_string|&quot;&t;.long 1b,3b&bslash;n&quot;
l_string|&quot;.previous&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|size
)paren
comma
l_string|&quot;=r&quot;
(paren
id|__a
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|size
)paren
comma
l_string|&quot;1&quot;
(paren
id|addr
)paren
comma
l_string|&quot;r&quot;
(paren
l_int|0
)paren
suffix:colon
l_string|&quot;memory&quot;
comma
l_string|&quot;t&quot;
)paren
suffix:semicolon
r_return
id|size
suffix:semicolon
)brace
DECL|macro|clear_user
mdefine_line|#define clear_user(addr,n) ({ &bslash;&n;void * __cl_addr = (addr); &bslash;&n;unsigned long __cl_size = (n); &bslash;&n;if (__cl_size &amp;&amp; __access_ok(((unsigned long)(__cl_addr)), __cl_size)) &bslash;&n;__cl_size = __clear_user(__cl_addr, __cl_size); &bslash;&n;__cl_size; })
r_static
id|__inline__
r_int
DECL|function|__strncpy_from_user
id|__strncpy_from_user
c_func
(paren
r_int
r_int
id|__dest
comma
r_int
r_int
id|__src
comma
r_int
id|__count
)paren
(brace
id|__kernel_size_t
id|res
suffix:semicolon
r_int
r_int
id|__dummy
comma
id|_d
comma
id|_s
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;9:&bslash;n&quot;
l_string|&quot;mov.b&t;@%2+, %1&bslash;n&bslash;t&quot;
l_string|&quot;cmp/eq&t;#0, %1&bslash;n&bslash;t&quot;
l_string|&quot;bt/s&t;2f&bslash;n&quot;
l_string|&quot;1:&bslash;n&quot;
l_string|&quot;mov.b&t;%1, @%3&bslash;n&bslash;t&quot;
l_string|&quot;dt&t;%7&bslash;n&bslash;t&quot;
l_string|&quot;bf/s&t;9b&bslash;n&bslash;t&quot;
l_string|&quot; add&t;#1, %3&bslash;n&bslash;t&quot;
l_string|&quot;2:&bslash;n&bslash;t&quot;
l_string|&quot;sub&t;%7, %0&bslash;n&quot;
l_string|&quot;3:&bslash;n&quot;
l_string|&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
l_string|&quot;4:&bslash;n&bslash;t&quot;
l_string|&quot;mov.l&t;5f, %1&bslash;n&bslash;t&quot;
l_string|&quot;jmp&t;@%1&bslash;n&bslash;t&quot;
l_string|&quot; mov&t;%8, %0&bslash;n&bslash;t&quot;
l_string|&quot;.balign 4&bslash;n&quot;
l_string|&quot;5:&t;.long 3b&bslash;n&quot;
l_string|&quot;.previous&bslash;n&quot;
l_string|&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;
l_string|&quot;&t;.balign 4&bslash;n&quot;
l_string|&quot;&t;.long 9b,4b&bslash;n&quot;
l_string|&quot;.previous&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|res
)paren
comma
l_string|&quot;=&amp;z&quot;
(paren
id|__dummy
)paren
comma
l_string|&quot;=r&quot;
(paren
id|_s
)paren
comma
l_string|&quot;=r&quot;
(paren
id|_d
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|__count
)paren
comma
l_string|&quot;2&quot;
(paren
id|__src
)paren
comma
l_string|&quot;3&quot;
(paren
id|__dest
)paren
comma
l_string|&quot;r&quot;
(paren
id|__count
)paren
comma
l_string|&quot;i&quot;
(paren
op_minus
id|EFAULT
)paren
suffix:colon
l_string|&quot;memory&quot;
comma
l_string|&quot;t&quot;
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
DECL|macro|strncpy_from_user
mdefine_line|#define strncpy_from_user(dest,src,count) ({ &bslash;&n;unsigned long __sfu_src = (unsigned long) (src); &bslash;&n;int __sfu_count = (int) (count); &bslash;&n;long __sfu_res = -EFAULT; &bslash;&n;if(__access_ok(__sfu_src, __sfu_count)) { &bslash;&n;__sfu_res = __strncpy_from_user((unsigned long) (dest), __sfu_src, __sfu_count); &bslash;&n;} __sfu_res; })
DECL|macro|strlen_user
mdefine_line|#define strlen_user(str) strnlen_user(str, ~0UL &gt;&gt; 1)
multiline_comment|/*&n; * Return the size of a string (including the ending 0!)&n; */
DECL|function|__strnlen_user
r_static
id|__inline__
r_int
id|__strnlen_user
c_func
(paren
r_const
r_char
op_star
id|__s
comma
r_int
id|__n
)paren
(brace
r_int
r_int
id|res
suffix:semicolon
r_int
r_int
id|__dummy
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;9:&bslash;n&quot;
l_string|&quot;cmp/eq&t;%4, %0&bslash;n&bslash;t&quot;
l_string|&quot;bt&t;2f&bslash;n&quot;
l_string|&quot;1:&bslash;t&quot;
l_string|&quot;mov.b&t;@(%0,%3), %1&bslash;n&bslash;t&quot;
l_string|&quot;tst&t;%1, %1&bslash;n&bslash;t&quot;
l_string|&quot;bf/s&t;9b&bslash;n&bslash;t&quot;
l_string|&quot; add&t;#1, %0&bslash;n&quot;
l_string|&quot;2:&bslash;n&quot;
l_string|&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
l_string|&quot;3:&bslash;n&bslash;t&quot;
l_string|&quot;mov.l&t;4f, %1&bslash;n&bslash;t&quot;
l_string|&quot;jmp&t;@%1&bslash;n&bslash;t&quot;
l_string|&quot; mov&t;%5, %0&bslash;n&quot;
l_string|&quot;.balign 4&bslash;n&quot;
l_string|&quot;4:&t;.long 2b&bslash;n&quot;
l_string|&quot;.previous&bslash;n&quot;
l_string|&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;
l_string|&quot;&t;.balign 4&bslash;n&quot;
l_string|&quot;&t;.long 1b,3b&bslash;n&quot;
l_string|&quot;.previous&quot;
suffix:colon
l_string|&quot;=z&quot;
(paren
id|res
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|__dummy
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
l_int|0
)paren
comma
l_string|&quot;r&quot;
(paren
id|__s
)paren
comma
l_string|&quot;r&quot;
(paren
id|__n
)paren
comma
l_string|&quot;i&quot;
(paren
op_minus
id|EFAULT
)paren
suffix:colon
l_string|&quot;t&quot;
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
DECL|function|strnlen_user
r_static
id|__inline__
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
r_if
c_cond
(paren
op_logical_neg
id|__addr_ok
c_func
(paren
id|s
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_else
r_return
id|__strnlen_user
c_func
(paren
id|s
comma
id|n
)paren
suffix:semicolon
)brace
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
macro_line|#endif /* __ASM_SH_UACCESS_H */
eof
