multiline_comment|/* $Id: uaccess.h,v 1.9 2003/05/06 23:28:51 lethal Exp $&n; *&n; * User space memory access functions&n; *&n; * Copyright (C) 1999, 2002  Niibe Yutaka&n; * Copyright (C) 2003  Paul Mundt&n; *&n; *  Based on:&n; *     MIPS implementation version 1.15 by&n; *              Copyright (C) 1996, 1997, 1998 by Ralf Baechle&n; *     and i386 version.&n; */
macro_line|#ifndef __ASM_SH_UACCESS_H
DECL|macro|__ASM_SH_UACCESS_H
mdefine_line|#define __ASM_SH_UACCESS_H
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
multiline_comment|/*&n; * NOTE: Macro/functions in this file depends on threads_info.h implementation.&n; * Assumes:&n; * TI_FLAGS == 8&n; * TIF_USERSPACE == 31&n; * USER_ADDR_LIMIT == 0x80000000&n; */
DECL|macro|VERIFY_READ
mdefine_line|#define VERIFY_READ    0
DECL|macro|VERIFY_WRITE
mdefine_line|#define VERIFY_WRITE   1
r_typedef
r_struct
(brace
DECL|member|is_user_space
r_int
r_int
id|is_user_space
suffix:semicolon
DECL|typedef|mm_segment_t
)brace
id|mm_segment_t
suffix:semicolon
multiline_comment|/*&n; * The fs value determines whether argument validity checking should be&n; * performed or not.  If get_fs() == USER_DS, checking is performed, with&n; * get_fs() == KERNEL_DS, checking is bypassed.&n; *&n; * For historical reasons (Data Segment Register?), these macros are misnamed.&n; */
DECL|macro|MAKE_MM_SEG
mdefine_line|#define MAKE_MM_SEG(s)&t;((mm_segment_t) { (s) })
DECL|macro|segment_eq
mdefine_line|#define segment_eq(a,b)&t;((a).is_user_space == (b).is_user_space)
DECL|macro|USER_ADDR_LIMIT
mdefine_line|#define USER_ADDR_LIMIT&t;0x80000000
DECL|macro|KERNEL_DS
mdefine_line|#define KERNEL_DS&t;MAKE_MM_SEG(0)
DECL|macro|USER_DS
mdefine_line|#define USER_DS&t;&t;MAKE_MM_SEG(1)
DECL|macro|get_ds
mdefine_line|#define get_ds()&t;(KERNEL_DS)
macro_line|#if !defined(CONFIG_MMU)
DECL|function|get_fs
r_static
r_inline
id|mm_segment_t
id|get_fs
c_func
(paren
r_void
)paren
(brace
r_return
id|USER_DS
suffix:semicolon
)brace
DECL|function|set_fs
r_static
r_inline
r_void
id|set_fs
c_func
(paren
id|mm_segment_t
id|s
)paren
(brace
)brace
multiline_comment|/*&n; * __access_ok: Check if address with size is OK or not.&n; *&n; * If we don&squot;t have an MMU (or if its disabled) the only thing we really have&n; * to look out for is if the address resides somewhere outside of what&n; * available RAM we have.&n; *&n; * TODO: This check could probably also stand to be restricted somewhat more..&n; * though it still does the Right Thing(tm) for the time being.&n; */
DECL|function|__access_ok
r_static
r_inline
r_int
id|__access_ok
c_func
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|size
)paren
(brace
r_extern
r_int
r_int
id|memory_start
comma
id|memory_end
suffix:semicolon
r_return
(paren
(paren
id|addr
op_ge
id|memory_start
)paren
op_logical_and
(paren
(paren
id|addr
op_plus
id|size
)paren
OL
id|memory_end
)paren
)paren
suffix:semicolon
)brace
macro_line|#else /* CONFIG_MMU */
DECL|function|get_fs
r_static
r_inline
id|mm_segment_t
id|get_fs
c_func
(paren
r_void
)paren
(brace
r_return
id|MAKE_MM_SEG
c_func
(paren
id|test_thread_flag
c_func
(paren
id|TIF_USERSPACE
)paren
)paren
suffix:semicolon
)brace
DECL|function|set_fs
r_static
r_inline
r_void
id|set_fs
c_func
(paren
id|mm_segment_t
id|s
)paren
(brace
r_int
r_int
id|ti
comma
id|flag
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;stc&t;r7_bank, %0&bslash;n&bslash;t&quot;
l_string|&quot;mov.l&t;@(8,%0), %1&bslash;n&bslash;t&quot;
l_string|&quot;shal&t;%1&bslash;n&bslash;t&quot;
l_string|&quot;cmp/pl&t;%2&bslash;n&bslash;t&quot;
l_string|&quot;rotcr&t;%1&bslash;n&bslash;t&quot;
l_string|&quot;mov.l&t;%1, @(8,%0)&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|ti
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|flag
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|s.is_user_space
)paren
suffix:colon
l_string|&quot;t&quot;
)paren
suffix:semicolon
multiline_comment|/****&n;&t;if (s.is_user_space)&n;&t;&t;set_thread_flag(TIF_USERSPACE);&n;&t;else&n;&t;&t;clear_thread_flag(TIF_USERSPACE);&n;****/
)brace
multiline_comment|/*&n; * __access_ok: Check if address with size is OK or not.&n; *&n; * We do three checks:&n; * (1) is it user space? &n; * (2) addr + size --&gt; carry?&n; * (3) addr + size &gt;= 0x80000000  (USER_ADDR_LIMIT)&n; *&n; * (1) (2) (3) | RESULT&n; *  0   0   0  |  ok&n; *  0   0   1  |  ok&n; *  0   1   0  |  bad&n; *  0   1   1  |  bad&n; *  1   0   0  |  ok&n; *  1   0   1  |  bad&n; *  1   1   0  |  bad&n; *  1   1   1  |  bad&n; */
DECL|function|__access_ok
r_static
r_inline
r_int
id|__access_ok
c_func
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|size
)paren
(brace
r_int
r_int
id|flag
comma
id|tmp
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;stc&t;r7_bank, %0&bslash;n&bslash;t&quot;
l_string|&quot;mov.l&t;@(8,%0), %0&bslash;n&bslash;t&quot;
l_string|&quot;clrt&bslash;n&bslash;t&quot;
l_string|&quot;addc&t;%2, %1&bslash;n&bslash;t&quot;
l_string|&quot;and&t;%1, %0&bslash;n&bslash;t&quot;
l_string|&quot;rotcl&t;%0&bslash;n&bslash;t&quot;
l_string|&quot;rotcl&t;%0&bslash;n&bslash;t&quot;
l_string|&quot;and&t;#3, %0&quot;
suffix:colon
l_string|&quot;=&amp;z&quot;
(paren
id|flag
)paren
comma
l_string|&quot;=r&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;1&quot;
(paren
id|size
)paren
suffix:colon
l_string|&quot;t&quot;
)paren
suffix:semicolon
r_return
id|flag
op_eq
l_int|0
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_MMU */
DECL|function|access_ok
r_static
r_inline
r_int
id|access_ok
c_func
(paren
r_int
id|type
comma
r_const
r_void
op_star
id|p
comma
r_int
r_int
id|size
)paren
(brace
r_int
r_int
id|addr
op_assign
(paren
r_int
r_int
)paren
id|p
suffix:semicolon
r_return
id|__access_ok
c_func
(paren
id|addr
comma
id|size
)paren
suffix:semicolon
)brace
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
mdefine_line|#define __get_user_check(x,ptr,size)&t;&t;&t;&bslash;&n;({ __typeof__(*(ptr)) __val; long __err;&t;&t;&bslash;&n; switch(size) {&t;&t;&t;&t;&t;&t;&bslash;&n; case 1: __err = __get_user_1(__val, ptr); break;&t;&bslash;&n; case 2: __err = __get_user_2(__val, ptr); break;&t;&bslash;&n; case 4: __err = __get_user_4(__val, ptr); break;&t;&bslash;&n; default: __get_user_unknown(); break;&t;&t;&t;&bslash;&n; }&t;&t;&t;&t;&t;&t;&t;&bslash;&n; (x) = __val; __err; })
DECL|macro|__get_user_1
mdefine_line|#define __get_user_1(x,ptr) ({&t;&t;&t;&bslash;&n;long __gu_err;&t;&t;&t;&t;&t;&bslash;&n;__typeof__(*(ptr)) __gu_val;&t;&t;&t;&bslash;&n;long __gu_addr = (long) (ptr);&t;&t;&t;&bslash;&n;__asm__(&quot;stc&t;r7_bank, %1&bslash;n&bslash;t&quot;&t;&t;&bslash;&n;&t;&quot;mov.l&t;@(8,%1), %1&bslash;n&bslash;t&quot;&t;&t;&bslash;&n;&t;&quot;and&t;%2, %1&bslash;n&bslash;t&quot;&t;&t;&t;&bslash;&n;&t;&quot;cmp/pz&t;%1&bslash;n&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;bt/s&t;1f&bslash;n&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot; mov&t;#0, %0&bslash;n&bslash;t&quot;&t;&t;&t;&bslash;&n;&t;&quot;0:&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;mov&t;#-14, %0&bslash;n&bslash;t&quot;&t;&t;&t;&bslash;&n;&t;&quot;bra&t;2f&bslash;n&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot; mov&t;#0, %1&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&quot;1:&bslash;n&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;mov.b&t;@%2, %1&bslash;n&bslash;t&quot;&t;&t;&t;&bslash;&n;&t;&quot;extu.b&t;%1, %1&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&quot;2:&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.section&t;__ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&bslash;t&quot;&t;&bslash;&n;&t;&quot;.long&t;1b, 0b&bslash;n&bslash;t&quot;&t;&t;&t;&bslash;&n;&t;&quot;.previous&quot;&t;&t;&t;&t;&bslash;&n;&t;: &quot;=&amp;r&quot; (__gu_err), &quot;=&amp;r&quot; (__gu_val)&t;&bslash;&n;&t;: &quot;r&quot; (__gu_addr)&t;&t;&t;&bslash;&n;&t;: &quot;t&quot;);&t;&t;&t;&t;&t;&bslash;&n;x = (__typeof__(*(ptr))) __gu_val; __gu_err; })
DECL|macro|__get_user_2
mdefine_line|#define __get_user_2(x,ptr) ({&t;&t;&t;&bslash;&n;long __gu_err;&t;&t;&t;&t;&t;&bslash;&n;__typeof__(*(ptr)) __gu_val;&t;&t;&t;&bslash;&n;long __gu_addr = (long) (ptr);&t;&t;&t;&bslash;&n;__asm__(&quot;stc&t;r7_bank, %1&bslash;n&bslash;t&quot;&t;&t;&bslash;&n;&t;&quot;mov.l&t;@(8,%1), %1&bslash;n&bslash;t&quot;&t;&t;&bslash;&n;&t;&quot;and&t;%2, %1&bslash;n&bslash;t&quot;&t;&t;&t;&bslash;&n;&t;&quot;cmp/pz&t;%1&bslash;n&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;bt/s&t;1f&bslash;n&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot; mov&t;#0, %0&bslash;n&bslash;t&quot;&t;&t;&t;&bslash;&n;&t;&quot;0:&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;mov&t;#-14, %0&bslash;n&bslash;t&quot;&t;&t;&t;&bslash;&n;&t;&quot;bra&t;2f&bslash;n&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot; mov&t;#0, %1&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&quot;1:&bslash;n&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;mov.w&t;@%2, %1&bslash;n&bslash;t&quot;&t;&t;&t;&bslash;&n;&t;&quot;extu.w&t;%1, %1&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&quot;2:&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.section&t;__ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&bslash;t&quot;&t;&bslash;&n;&t;&quot;.long&t;1b, 0b&bslash;n&bslash;t&quot;&t;&t;&t;&bslash;&n;&t;&quot;.previous&quot;&t;&t;&t;&t;&bslash;&n;&t;: &quot;=&amp;r&quot; (__gu_err), &quot;=&amp;r&quot; (__gu_val)&t;&bslash;&n;&t;: &quot;r&quot; (__gu_addr)&t;&t;&t;&bslash;&n;&t;: &quot;t&quot;);&t;&t;&t;&t;&t;&bslash;&n;x = (__typeof__(*(ptr))) __gu_val; __gu_err; })
DECL|macro|__get_user_4
mdefine_line|#define __get_user_4(x,ptr) ({&t;&t;&t;&bslash;&n;long __gu_err;&t;&t;&t;&t;&t;&bslash;&n;__typeof__(*(ptr)) __gu_val;&t;&t;&t;&bslash;&n;long __gu_addr = (long) (ptr);&t;&t;&t;&bslash;&n;__asm__(&quot;stc&t;r7_bank, %1&bslash;n&bslash;t&quot;&t;&t;&bslash;&n;&t;&quot;mov.l&t;@(8,%1), %1&bslash;n&bslash;t&quot;&t;&t;&bslash;&n;&t;&quot;and&t;%2, %1&bslash;n&bslash;t&quot;&t;&t;&t;&bslash;&n;&t;&quot;cmp/pz&t;%1&bslash;n&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;bt/s&t;1f&bslash;n&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot; mov&t;#0, %0&bslash;n&bslash;t&quot;&t;&t;&t;&bslash;&n;&t;&quot;0:&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;mov&t;#-14, %0&bslash;n&bslash;t&quot;&t;&t;&t;&bslash;&n;&t;&quot;bra&t;2f&bslash;n&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot; mov&t;#0, %1&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&quot;1:&bslash;n&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;mov.l&t;@%2, %1&bslash;n&bslash;t&quot;&t;&t;&t;&bslash;&n;&t;&quot;2:&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.section&t;__ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&bslash;t&quot;&t;&bslash;&n;&t;&quot;.long&t;1b, 0b&bslash;n&bslash;t&quot;&t;&t;&t;&bslash;&n;&t;&quot;.previous&quot;&t;&t;&t;&t;&bslash;&n;&t;: &quot;=&amp;r&quot; (__gu_err), &quot;=&amp;r&quot; (__gu_val)&t;&bslash;&n;&t;: &quot;r&quot; (__gu_addr)&t;&t;&t;&bslash;&n;&t;: &quot;t&quot;);&t;&t;&t;&t;&t;&bslash;&n;x = (__typeof__(*(ptr))) __gu_val; __gu_err; })
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
r_extern
id|__kernel_size_t
id|__copy_user
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
id|__kernel_size_t
id|n
)paren
suffix:semicolon
DECL|macro|copy_to_user
mdefine_line|#define copy_to_user(to,from,n) ({ &bslash;&n;void *__copy_to = (void *) (to); &bslash;&n;__kernel_size_t __copy_size = (__kernel_size_t) (n); &bslash;&n;__kernel_size_t __copy_res; &bslash;&n;if(__copy_size &amp;&amp; __access_ok((unsigned long)__copy_to, __copy_size)) { &bslash;&n;__copy_res = __copy_user(__copy_to, (void *) (from), __copy_size); &bslash;&n;} else __copy_res = __copy_size; &bslash;&n;__copy_res; })
DECL|macro|__copy_to_user
mdefine_line|#define __copy_to_user(to,from,n)&t;&t;&bslash;&n;&t;__copy_user((void *)(to),&t;&t;&bslash;&n;&t;&t;    (void *)(from), n)
DECL|macro|copy_from_user
mdefine_line|#define copy_from_user(to,from,n) ({ &bslash;&n;void *__copy_to = (void *) (to); &bslash;&n;void *__copy_from = (void *) (from); &bslash;&n;__kernel_size_t __copy_size = (__kernel_size_t) (n); &bslash;&n;__kernel_size_t __copy_res; &bslash;&n;if(__copy_size &amp;&amp; __access_ok((unsigned long)__copy_from, __copy_size)) { &bslash;&n;__copy_res = __copy_user(__copy_to, __copy_from, __copy_size); &bslash;&n;} else __copy_res = __copy_size; &bslash;&n;__copy_res; })
DECL|macro|__copy_from_user
mdefine_line|#define __copy_from_user(to,from,n)&t;&t;&bslash;&n;&t;__copy_user((void *)(to),&t;&t;&bslash;&n;&t;&t;    (void *)(from), n)
multiline_comment|/*&n; * Clear the area and return remaining number of bytes&n; * (on failure.  Usually it&squot;s 0.)&n; */
r_extern
id|__kernel_size_t
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
suffix:semicolon
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
DECL|function|strlen_user
r_static
id|__inline__
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
l_int|0
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
op_complement
l_int|0UL
op_rshift
l_int|1
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
macro_line|#endif /* __ASM_SH_UACCESS_H */
eof
