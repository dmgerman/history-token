macro_line|#ifndef _ASM_IA64_UACCESS_H
DECL|macro|_ASM_IA64_UACCESS_H
mdefine_line|#define _ASM_IA64_UACCESS_H
multiline_comment|/*&n; * This file defines various macros to transfer memory areas across&n; * the user/kernel boundary.  This needs to be done carefully because&n; * this code is executed in kernel mode and uses user-specified&n; * addresses.  Thus, we need to be careful not to let the user to&n; * trick us into accessing kernel memory that would normally be&n; * inaccessible.  This code is also fairly performance sensitive,&n; * so we want to spend as little time doing safety checks as&n; * possible.&n; *&n; * To make matters a bit more interesting, these macros sometimes also&n; * called from within the kernel itself, in which case the address&n; * validity check must be skipped.  The get_fs() macro tells us what&n; * to do: if get_fs()==USER_DS, checking is performed, if&n; * get_fs()==KERNEL_DS, checking is bypassed.&n; *&n; * Note that even if the memory area specified by the user is in a&n; * valid address range, it is still possible that we&squot;ll get a page&n; * fault while accessing it.  This is handled by filling out an&n; * exception handler fixup entry for each instruction that has the&n; * potential to fault.  When such a fault occurs, the page fault&n; * handler checks to see whether the faulting instruction has a fixup&n; * associated and, if so, sets r8 to -EFAULT and clears r9 to 0 and&n; * then resumes execution at the continuation point.&n; *&n; * Based on &lt;asm-alpha/uaccess.h&gt;.&n; *&n; * Copyright (C) 1998, 1999, 2001-2004 Hewlett-Packard Co&n; *&t;David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; */
macro_line|#include &lt;linux/compiler.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/intrinsics.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
multiline_comment|/*&n; * For historical reasons, the following macros are grossly misnamed:&n; */
DECL|macro|KERNEL_DS
mdefine_line|#define KERNEL_DS&t;((mm_segment_t) { ~0UL })&t;&t;/* cf. access_ok() */
DECL|macro|USER_DS
mdefine_line|#define USER_DS&t;&t;((mm_segment_t) { TASK_SIZE-1 })&t;/* cf. access_ok() */
DECL|macro|VERIFY_READ
mdefine_line|#define VERIFY_READ&t;0
DECL|macro|VERIFY_WRITE
mdefine_line|#define VERIFY_WRITE&t;1
DECL|macro|get_ds
mdefine_line|#define get_ds()  (KERNEL_DS)
DECL|macro|get_fs
mdefine_line|#define get_fs()  (current_thread_info()-&gt;addr_limit)
DECL|macro|set_fs
mdefine_line|#define set_fs(x) (current_thread_info()-&gt;addr_limit = (x))
DECL|macro|segment_eq
mdefine_line|#define segment_eq(a, b)&t;((a).seg == (b).seg)
multiline_comment|/*&n; * When accessing user memory, we need to make sure the entire area really is in&n; * user-level space.  In order to do this efficiently, we make sure that the page at&n; * address TASK_SIZE is never valid.  We also need to make sure that the address doesn&squot;t&n; * point inside the virtually mapped linear page table.&n; */
DECL|macro|__access_ok
mdefine_line|#define __access_ok(addr, size, segment)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__chk_user_ptr(addr);&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(likely((unsigned long) (addr) &lt;= (segment).seg)&t;&t;&t;&t;&bslash;&n;&t; &amp;&amp; ((segment).seg == KERNEL_DS.seg&t;&t;&t;&t;&t;&t;&bslash;&n;&t;     || likely(REGION_OFFSET((unsigned long) (addr)) &lt; RGN_MAP_LIMIT)));&t;&bslash;&n;})
DECL|macro|access_ok
mdefine_line|#define access_ok(type, addr, size)&t;__access_ok((addr), (size), get_fs())
r_static
r_inline
r_int
DECL|function|verify_area
id|verify_area
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
multiline_comment|/*&n; * These are the main single-value transfer routines.  They automatically&n; * use the right size if we just have the right pointer type.&n; *&n; * Careful to not&n; * (a) re-use the arguments for side effects (sizeof/typeof is ok)&n; * (b) require any knowledge of processes at this stage&n; */
DECL|macro|put_user
mdefine_line|#define put_user(x, ptr)&t;__put_user_check((__typeof__(*(ptr))) (x), (ptr), sizeof(*(ptr)), get_fs())
DECL|macro|get_user
mdefine_line|#define get_user(x, ptr)&t;__get_user_check((x), (ptr), sizeof(*(ptr)), get_fs())
multiline_comment|/*&n; * The &quot;__xxx&quot; versions do not do address space checking, useful when&n; * doing multiple accesses to the same area (the programmer has to do the&n; * checks by hand with &quot;access_ok()&quot;)&n; */
DECL|macro|__put_user
mdefine_line|#define __put_user(x, ptr)&t;__put_user_nocheck((__typeof__(*(ptr))) (x), (ptr), sizeof(*(ptr)))
DECL|macro|__get_user
mdefine_line|#define __get_user(x, ptr)&t;__get_user_nocheck((x), (ptr), sizeof(*(ptr)))
r_extern
r_int
id|__put_user_unaligned_unknown
(paren
r_void
)paren
suffix:semicolon
DECL|macro|__put_user_unaligned
mdefine_line|#define __put_user_unaligned(x, ptr)&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;long __ret;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;switch (sizeof(*(ptr))) {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;case 1: __ret = __put_user((x), (ptr)); break;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;case 2: __ret = (__put_user((x), (u8 __user *)(ptr)))&t;&t;&t;&t;&bslash;&n;&t;&t;&t;| (__put_user((x) &gt;&gt; 8, ((u8 __user *)(ptr) + 1))); break;&t;&t;&bslash;&n;&t;&t;case 4: __ret = (__put_user((x), (u16 __user *)(ptr)))&t;&t;&t;&t;&bslash;&n;&t;&t;&t;| (__put_user((x) &gt;&gt; 16, ((u16 __user *)(ptr) + 1))); break;&t;&t;&bslash;&n;&t;&t;case 8: __ret = (__put_user((x), (u32 __user *)(ptr)))&t;&t;&t;&t;&bslash;&n;&t;&t;&t;| (__put_user((x) &gt;&gt; 32, ((u32 __user *)(ptr) + 1))); break;&t;&t;&bslash;&n;&t;&t;default: __ret = __put_user_unaligned_unknown();&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__ret;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
r_extern
r_int
id|__get_user_unaligned_unknown
(paren
r_void
)paren
suffix:semicolon
DECL|macro|__get_user_unaligned
mdefine_line|#define __get_user_unaligned(x, ptr)&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;long __ret;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;switch (sizeof(*(ptr))) {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;case 1: __ret = __get_user((x), (ptr)); break;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;case 2: __ret = (__get_user((x), (u8 __user *)(ptr)))&t;&t;&t;&t;&bslash;&n;&t;&t;&t;| (__get_user((x) &gt;&gt; 8, ((u8 __user *)(ptr) + 1))); break;&t;&t;&bslash;&n;&t;&t;case 4: __ret = (__get_user((x), (u16 __user *)(ptr)))&t;&t;&t;&t;&bslash;&n;&t;&t;&t;| (__get_user((x) &gt;&gt; 16, ((u16 __user *)(ptr) + 1))); break;&t;&t;&bslash;&n;&t;&t;case 8: __ret = (__get_user((x), (u32 __user *)(ptr)))&t;&t;&t;&t;&bslash;&n;&t;&t;&t;| (__get_user((x) &gt;&gt; 32, ((u32 __user *)(ptr) + 1))); break;&t;&t;&bslash;&n;&t;&t;default: __ret = __get_user_unaligned_unknown();&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__ret;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
macro_line|#ifdef ASM_SUPPORTED
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
macro_line|# define __m(x) (*(struct __large_struct __user *)(x))
multiline_comment|/* We need to declare the __ex_table section before we can use it in .xdata.  */
id|asm
(paren
l_string|&quot;.section &bslash;&quot;__ex_table&bslash;&quot;, &bslash;&quot;a&bslash;&quot;&bslash;n&bslash;t.previous&quot;
)paren
suffix:semicolon
DECL|macro|__get_user_size
macro_line|# define __get_user_size(val, addr, n, err)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;register long __gu_r8 asm (&quot;r8&quot;) = 0;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;register long __gu_r9 asm (&quot;r9&quot;);&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;asm (&quot;&bslash;n[1:]&bslash;tld&quot;#n&quot; %0=%2%P2&bslash;t
singleline_comment|// %0 and %1 get overwritten by exception handler&bslash;n&quot;&t;&bslash;
l_string|&quot;&bslash;t.xdata4 &bslash;&quot;__ex_table&bslash;&quot;, 1b-., 1f-.+4&bslash;n&quot;
"&bslash;"
l_string|&quot;[1:]&quot;
"&bslash;"
suffix:colon
l_string|&quot;=r&quot;
(paren
id|__gu_r9
)paren
comma
l_string|&quot;=r&quot;
(paren
id|__gu_r8
)paren
suffix:colon
l_string|&quot;m&quot;
(paren
id|__m
c_func
(paren
id|addr
)paren
)paren
comma
l_string|&quot;1&quot;
(paren
id|__gu_r8
)paren
)paren
suffix:semicolon
"&bslash;"
(paren
id|err
)paren
op_assign
id|__gu_r8
suffix:semicolon
"&bslash;"
(paren
id|val
)paren
op_assign
id|__gu_r9
suffix:semicolon
"&bslash;"
)brace
r_while
c_loop
(paren
l_int|0
)paren
multiline_comment|/*&n; * The &quot;__put_user_size()&quot; macro tells gcc it reads from memory instead of writing it.  This&n; * is because they do not write to any memory gcc knows about, so there are no aliasing&n; * issues.&n; */
DECL|macro|__put_user_size
macro_line|# define __put_user_size(val, addr, n, err)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;register long __pu_r8 asm (&quot;r8&quot;) = 0;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;asm volatile (&quot;&bslash;n[1:]&bslash;tst&quot;#n&quot; %1=%r2%P1&bslash;t
singleline_comment|// %0 gets overwritten by exception handler&bslash;n&quot;&t;&bslash;
l_string|&quot;&bslash;t.xdata4 &bslash;&quot;__ex_table&bslash;&quot;, 1b-., 1f-.&bslash;n&quot;
"&bslash;"
l_string|&quot;[1:]&quot;
"&bslash;"
suffix:colon
l_string|&quot;=r&quot;
(paren
id|__pu_r8
)paren
suffix:colon
l_string|&quot;m&quot;
(paren
id|__m
c_func
(paren
id|addr
)paren
)paren
comma
l_string|&quot;rO&quot;
(paren
id|val
)paren
comma
l_string|&quot;0&quot;
(paren
id|__pu_r8
)paren
)paren
suffix:semicolon
"&bslash;"
(paren
id|err
)paren
op_assign
id|__pu_r8
suffix:semicolon
"&bslash;"
)brace
r_while
c_loop
(paren
l_int|0
)paren
macro_line|#else /* !ASM_SUPPORTED */
DECL|macro|RELOC_TYPE
macro_line|# define RELOC_TYPE&t;2&t;/* ip-rel */
DECL|macro|__get_user_size
macro_line|# define __get_user_size(val, addr, n, err)&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__ld_user(&quot;__ex_table&quot;, (unsigned long) addr, n, RELOC_TYPE);&t;&bslash;&n;&t;(err) = ia64_getreg(_IA64_REG_R8);&t;&t;&t;&t;&bslash;&n;&t;(val) = ia64_getreg(_IA64_REG_R9);&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|__put_user_size
macro_line|# define __put_user_size(val, addr, n, err)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__st_user(&quot;__ex_table&quot;, (unsigned long) addr, n, RELOC_TYPE, (unsigned long) (val));&t;&bslash;&n;&t;(err) = ia64_getreg(_IA64_REG_R8);&t;&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
macro_line|#endif /* !ASM_SUPPORTED */
r_extern
r_void
id|__get_user_unknown
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * Evaluating arguments X, PTR, SIZE, and SEGMENT may involve subroutine-calls, which&n; * could clobber r8 and r9 (among others).  Thus, be careful not to evaluate it while&n; * using r8/r9.&n; */
DECL|macro|__do_get_user
mdefine_line|#define __do_get_user(check, x, ptr, size, segment)&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;const __typeof__(*(ptr)) __user *__gu_ptr = (ptr);&t;&t;&t;&t;&bslash;&n;&t;__typeof__ (size) __gu_size = (size);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;long __gu_err = -EFAULT, __gu_val = 0;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (!check || __access_ok(__gu_ptr, size, segment))&t;&t;&t;&t;&bslash;&n;&t;&t;switch (__gu_size) {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;      case 1: __get_user_size(__gu_val, __gu_ptr, 1, __gu_err); break;&t;&bslash;&n;&t;&t;      case 2: __get_user_size(__gu_val, __gu_ptr, 2, __gu_err); break;&t;&bslash;&n;&t;&t;      case 4: __get_user_size(__gu_val, __gu_ptr, 4, __gu_err); break;&t;&bslash;&n;&t;&t;      case 8: __get_user_size(__gu_val, __gu_ptr, 8, __gu_err); break;&t;&bslash;&n;&t;&t;      default: __get_user_unknown(); break;&t;&t;&t;&t;&bslash;&n;&t;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(x) = (__typeof__(*(__gu_ptr))) __gu_val;&t;&t;&t;&t;&t;&bslash;&n;&t;__gu_err;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|__get_user_nocheck
mdefine_line|#define __get_user_nocheck(x, ptr, size)&t;__do_get_user(0, x, ptr, size, KERNEL_DS)
DECL|macro|__get_user_check
mdefine_line|#define __get_user_check(x, ptr, size, segment)&t;__do_get_user(1, x, ptr, size, segment)
r_extern
r_void
id|__put_user_unknown
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * Evaluating arguments X, PTR, SIZE, and SEGMENT may involve subroutine-calls, which&n; * could clobber r8 (among others).  Thus, be careful not to evaluate them while using r8.&n; */
DECL|macro|__do_put_user
mdefine_line|#define __do_put_user(check, x, ptr, size, segment)&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__typeof__ (x) __pu_x = (x);&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__typeof__ (*(ptr)) __user *__pu_ptr = (ptr);&t;&t;&t;&t;&t;&bslash;&n;&t;__typeof__ (size) __pu_size = (size);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;long __pu_err = -EFAULT;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (!check || __access_ok(__pu_ptr, __pu_size, segment))&t;&t;&t;&bslash;&n;&t;&t;switch (__pu_size) {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;      case 1: __put_user_size(__pu_x, __pu_ptr, 1, __pu_err); break;&t;&bslash;&n;&t;&t;      case 2: __put_user_size(__pu_x, __pu_ptr, 2, __pu_err); break;&t;&bslash;&n;&t;&t;      case 4: __put_user_size(__pu_x, __pu_ptr, 4, __pu_err); break;&t;&bslash;&n;&t;&t;      case 8: __put_user_size(__pu_x, __pu_ptr, 8, __pu_err); break;&t;&bslash;&n;&t;&t;      default: __put_user_unknown(); break;&t;&t;&t;&t;&bslash;&n;&t;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__pu_err;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|__put_user_nocheck
mdefine_line|#define __put_user_nocheck(x, ptr, size)&t;__do_put_user(0, x, ptr, size, KERNEL_DS)
DECL|macro|__put_user_check
mdefine_line|#define __put_user_check(x, ptr, size, segment)&t;__do_put_user(1, x, ptr, size, segment)
multiline_comment|/*&n; * Complex access routines&n; */
r_extern
r_int
r_int
id|__must_check
id|__copy_user
(paren
r_void
id|__user
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
id|count
)paren
suffix:semicolon
r_static
r_inline
r_int
r_int
DECL|function|__copy_to_user
id|__copy_to_user
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
id|count
)paren
(brace
r_return
id|__copy_user
c_func
(paren
id|to
comma
(paren
r_void
id|__user
op_star
)paren
id|from
comma
id|count
)paren
suffix:semicolon
)brace
r_static
r_inline
r_int
r_int
DECL|function|__copy_from_user
id|__copy_from_user
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
id|count
)paren
(brace
r_return
id|__copy_user
c_func
(paren
(paren
r_void
id|__user
op_star
)paren
id|to
comma
id|from
comma
id|count
)paren
suffix:semicolon
)brace
DECL|macro|__copy_to_user_inatomic
mdefine_line|#define __copy_to_user_inatomic&t;&t;__copy_to_user
DECL|macro|__copy_from_user_inatomic
mdefine_line|#define __copy_from_user_inatomic&t;__copy_from_user
DECL|macro|copy_to_user
mdefine_line|#define copy_to_user(to, from, n)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;void __user *__cu_to = (to);&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;const void *__cu_from = (from);&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;long __cu_len = (n);&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (__access_ok(__cu_to, __cu_len, get_fs()))&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__cu_len = __copy_user(__cu_to, (void __user *) __cu_from, __cu_len);&t;&bslash;&n;&t;__cu_len;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|copy_from_user
mdefine_line|#define copy_from_user(to, from, n)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;void *__cu_to = (to);&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;const void __user *__cu_from = (from);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;long __cu_len = (n);&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__chk_user_ptr(__cu_from);&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (__access_ok(__cu_from, __cu_len, get_fs()))&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__cu_len = __copy_user((void __user *) __cu_to, __cu_from, __cu_len);&t;&bslash;&n;&t;__cu_len;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|__copy_in_user
mdefine_line|#define __copy_in_user(to, from, size)&t;__copy_user((to), (from), (size))
r_static
r_inline
r_int
r_int
DECL|function|copy_in_user
id|copy_in_user
(paren
r_void
id|__user
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
id|likely
c_func
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
op_logical_and
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
)paren
id|n
op_assign
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
r_extern
r_int
r_int
id|__do_clear_user
(paren
r_void
id|__user
op_star
comma
r_int
r_int
)paren
suffix:semicolon
DECL|macro|__clear_user
mdefine_line|#define __clear_user(to, n)&t;&t;__do_clear_user(to, n)
DECL|macro|clear_user
mdefine_line|#define clear_user(to, n)&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long __cu_len = (n);&t;&t;&t;&t;&bslash;&n;&t;if (__access_ok(to, __cu_len, get_fs()))&t;&t;&bslash;&n;&t;&t;__cu_len = __do_clear_user(to, __cu_len);&t;&bslash;&n;&t;__cu_len;&t;&t;&t;&t;&t;&t;&bslash;&n;})
multiline_comment|/*&n; * Returns: -EFAULT if exception before terminator, N if the entire buffer filled, else&n; * strlen.&n; */
r_extern
r_int
id|__must_check
id|__strncpy_from_user
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
id|to_len
)paren
suffix:semicolon
DECL|macro|strncpy_from_user
mdefine_line|#define strncpy_from_user(to, from, n)&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;const char __user * __sfu_from = (from);&t;&t;&t;&bslash;&n;&t;long __sfu_ret = -EFAULT;&t;&t;&t;&t;&t;&bslash;&n;&t;if (__access_ok(__sfu_from, 0, get_fs()))&t;&t;&t;&bslash;&n;&t;&t;__sfu_ret = __strncpy_from_user((to), __sfu_from, (n));&t;&bslash;&n;&t;__sfu_ret;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
multiline_comment|/* Returns: 0 if bad, string length+1 (memory size) of string if ok */
r_extern
r_int
r_int
id|__strlen_user
(paren
r_const
r_char
id|__user
op_star
)paren
suffix:semicolon
DECL|macro|strlen_user
mdefine_line|#define strlen_user(str)&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;const char __user *__su_str = (str);&t;&t;&bslash;&n;&t;unsigned long __su_ret = 0;&t;&t;&t;&bslash;&n;&t;if (__access_ok(__su_str, 0, get_fs()))&t;&t;&bslash;&n;&t;&t;__su_ret = __strlen_user(__su_str);&t;&bslash;&n;&t;__su_ret;&t;&t;&t;&t;&t;&bslash;&n;})
multiline_comment|/*&n; * Returns: 0 if exception before NUL or reaching the supplied limit&n; * (N), a value greater than N if the limit would be exceeded, else&n; * strlen.&n; */
r_extern
r_int
r_int
id|__strnlen_user
(paren
r_const
r_char
id|__user
op_star
comma
r_int
)paren
suffix:semicolon
DECL|macro|strnlen_user
mdefine_line|#define strnlen_user(str, len)&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;const char __user *__su_str = (str);&t;&t;&t;&bslash;&n;&t;unsigned long __su_ret = 0;&t;&t;&t;&t;&bslash;&n;&t;if (__access_ok(__su_str, 0, get_fs()))&t;&t;&t;&bslash;&n;&t;&t;__su_ret = __strnlen_user(__su_str, len);&t;&bslash;&n;&t;__su_ret;&t;&t;&t;&t;&t;&t;&bslash;&n;})
multiline_comment|/* Generic code can&squot;t deal with the location-relative format that we use for compactness.  */
DECL|macro|ARCH_HAS_SORT_EXTABLE
mdefine_line|#define ARCH_HAS_SORT_EXTABLE
DECL|macro|ARCH_HAS_SEARCH_EXTABLE
mdefine_line|#define ARCH_HAS_SEARCH_EXTABLE
DECL|struct|exception_table_entry
r_struct
id|exception_table_entry
(brace
DECL|member|addr
r_int
id|addr
suffix:semicolon
multiline_comment|/* location-relative address of insn this fixup is for */
DECL|member|cont
r_int
id|cont
suffix:semicolon
multiline_comment|/* location-relative continuation addr.; if bit 2 is set, r9 is set to 0 */
)brace
suffix:semicolon
r_extern
r_void
id|ia64_handle_exception
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_const
r_struct
id|exception_table_entry
op_star
id|e
)paren
suffix:semicolon
r_extern
r_const
r_struct
id|exception_table_entry
op_star
id|search_exception_tables
(paren
r_int
r_int
id|addr
)paren
suffix:semicolon
r_static
r_inline
r_int
DECL|function|ia64_done_with_exception
id|ia64_done_with_exception
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_const
r_struct
id|exception_table_entry
op_star
id|e
suffix:semicolon
id|e
op_assign
id|search_exception_tables
c_func
(paren
id|regs-&gt;cr_iip
op_plus
id|ia64_psr
c_func
(paren
id|regs
)paren
op_member_access_from_pointer
id|ri
)paren
suffix:semicolon
r_if
c_cond
(paren
id|e
)paren
(brace
id|ia64_handle_exception
c_func
(paren
id|regs
comma
id|e
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif /* _ASM_IA64_UACCESS_H */
eof
