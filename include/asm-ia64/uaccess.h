macro_line|#ifndef _ASM_IA64_UACCESS_H
DECL|macro|_ASM_IA64_UACCESS_H
mdefine_line|#define _ASM_IA64_UACCESS_H
multiline_comment|/*&n; * This file defines various macros to transfer memory areas across&n; * the user/kernel boundary.  This needs to be done carefully because&n; * this code is executed in kernel mode and uses user-specified&n; * addresses.  Thus, we need to be careful not to let the user to&n; * trick us into accessing kernel memory that would normally be&n; * inaccessible.  This code is also fairly performance sensitive,&n; * so we want to spend as little time doing saftey checks as&n; * possible.&n; *&n; * To make matters a bit more interesting, these macros sometimes also&n; * called from within the kernel itself, in which case the address&n; * validity check must be skipped.  The get_fs() macro tells us what&n; * to do: if get_fs()==USER_DS, checking is performed, if&n; * get_fs()==KERNEL_DS, checking is bypassed.&n; *&n; * Note that even if the memory area specified by the user is in a&n; * valid address range, it is still possible that we&squot;ll get a page&n; * fault while accessing it.  This is handled by filling out an&n; * exception handler fixup entry for each instruction that has the&n; * potential to fault.  When such a fault occurs, the page fault&n; * handler checks to see whether the faulting instruction has a fixup&n; * associated and, if so, sets r8 to -EFAULT and clears r9 to 0 and&n; * then resumes execution at the continuation point.&n; * &n; * Copyright (C) 1998, 1999 Hewlett-Packard Co&n; * Copyright (C) 1998, 1999 David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
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
mdefine_line|#define get_fs()  (current-&gt;addr_limit)
DECL|macro|set_fs
mdefine_line|#define set_fs(x) (current-&gt;addr_limit = (x))
DECL|macro|segment_eq
mdefine_line|#define segment_eq(a,b)&t;((a).seg == (b).seg)
multiline_comment|/*&n; * When accessing user memory, we need to make sure the entire area&n; * really is in user-level space.  In order to do this efficiently, we&n; * make sure that the page at address TASK_SIZE is never valid (we do&n; * this by selecting VMALLOC_START as TASK_SIZE+PAGE_SIZE).  This way,&n; * we can simply check whether the starting address is &lt; TASK_SIZE&n; * and, if so, start accessing the memory.  If the user specified bad&n; * length, we will fault on the NaT page and then return the&n; * appropriate error.&n; */
DECL|macro|__access_ok
mdefine_line|#define __access_ok(addr,size,segment)&t;(((unsigned long) (addr)) &lt;= (segment).seg)
DECL|macro|access_ok
mdefine_line|#define access_ok(type,addr,size)&t;__access_ok((addr),(size),get_fs())
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
mdefine_line|#define put_user(x,ptr)&t;__put_user_check((__typeof__(*(ptr)))(x),(ptr),sizeof(*(ptr)),get_fs())
DECL|macro|get_user
mdefine_line|#define get_user(x,ptr)&t;__get_user_check((x),(ptr),sizeof(*(ptr)),get_fs())
multiline_comment|/*&n; * The &quot;__xxx&quot; versions do not do address space checking, useful when&n; * doing multiple accesses to the same area (the programmer has to do the&n; * checks by hand with &quot;access_ok()&quot;)&n; */
DECL|macro|__put_user
mdefine_line|#define __put_user(x,ptr)&t;__put_user_nocheck((__typeof__(*(ptr)))(x),(ptr),sizeof(*(ptr)))
DECL|macro|__get_user
mdefine_line|#define __get_user(x,ptr)&t;__get_user_nocheck((x),(ptr),sizeof(*(ptr)))
r_extern
r_void
id|__get_user_unknown
(paren
r_void
)paren
suffix:semicolon
DECL|macro|__get_user_nocheck
mdefine_line|#define __get_user_nocheck(x,ptr,size)&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;register long __gu_err __asm__ (&quot;r8&quot;) = 0;&t;&t;&bslash;&n;&t;register long __gu_val __asm__ (&quot;r9&quot;) = 0;&t;&t;&bslash;&n;&t;switch (size) {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;  case 1: __get_user_8(ptr); break;&t;&t;&t;&bslash;&n;&t;  case 2: __get_user_16(ptr); break;&t;&t;&t;&bslash;&n;&t;  case 4: __get_user_32(ptr); break;&t;&t;&t;&bslash;&n;&t;  case 8: __get_user_64(ptr); break;&t;&t;&t;&bslash;&n;&t;  default: __get_user_unknown(); break;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(x) = (__typeof__(*(ptr))) __gu_val;&t;&t;&t;&bslash;&n;&t;__gu_err;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|__get_user_check
mdefine_line|#define __get_user_check(x,ptr,size,segment)&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;register long __gu_err __asm__ (&quot;r8&quot;) = -EFAULT;&t;&bslash;&n;&t;register long __gu_val __asm__ (&quot;r9&quot;) = 0;&t;&t;&bslash;&n;&t;const __typeof__(*(ptr)) *__gu_addr = (ptr);&t;&t;&bslash;&n;&t;if (__access_ok((long)__gu_addr,size,segment)) {&t;&bslash;&n;&t;&t;__gu_err = 0;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;switch (size) {&t;&t;&t;&t;&t;&bslash;&n;&t;&t;  case 1: __get_user_8(__gu_addr); break;&t;&bslash;&n;&t;&t;  case 2: __get_user_16(__gu_addr); break;&t;&bslash;&n;&t;&t;  case 4: __get_user_32(__gu_addr); break;&t;&bslash;&n;&t;&t;  case 8: __get_user_64(__gu_addr); break;&t;&bslash;&n;&t;&t;  default: __get_user_unknown(); break;&t;&t;&bslash;&n;&t;&t;}&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(x) = (__typeof__(*(ptr))) __gu_val;&t;&t;&t;&bslash;&n;&t;__gu_err;&t;&t;&t;&t;&t;&t;&bslash;&n;})
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
multiline_comment|/* We need to declare the __ex_table section before we can use it in .xdata.  */
id|__asm__
(paren
l_string|&quot;.section &bslash;&quot;__ex_table&bslash;&quot;, &bslash;&quot;a&bslash;&quot;&bslash;n&bslash;t.previous&quot;
)paren
suffix:semicolon
DECL|macro|__get_user_64
mdefine_line|#define __get_user_64(addr)&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ (&quot;&bslash;n1:&bslash;tld8 %0=%2%P2&bslash;t
singleline_comment|// %0 and %1 get overwritten by exception handler&bslash;n&quot;&t;&bslash;
l_string|&quot;2:&bslash;n&bslash;t.xdata4 &bslash;&quot;__ex_table&bslash;&quot;, @gprel(1b), (2b-1b)|1&bslash;n&quot;
"&bslash;"
suffix:colon
l_string|&quot;=r&quot;
(paren
id|__gu_val
)paren
comma
l_string|&quot;=r&quot;
(paren
id|__gu_err
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
id|__gu_err
)paren
)paren
suffix:semicolon
DECL|macro|__get_user_32
mdefine_line|#define __get_user_32(addr)&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ (&quot;&bslash;n1:&bslash;tld4 %0=%2%P2&bslash;t
singleline_comment|// %0 and %1 get overwritten by exception handler&bslash;n&quot;&t;&bslash;
l_string|&quot;2:&bslash;n&bslash;t.xdata4 &bslash;&quot;__ex_table&bslash;&quot;, @gprel(1b), (2b-1b)|1&bslash;n&quot;
"&bslash;"
suffix:colon
l_string|&quot;=r&quot;
(paren
id|__gu_val
)paren
comma
l_string|&quot;=r&quot;
(paren
id|__gu_err
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
id|__gu_err
)paren
)paren
suffix:semicolon
DECL|macro|__get_user_16
mdefine_line|#define __get_user_16(addr)&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ (&quot;&bslash;n1:&bslash;tld2 %0=%2%P2&bslash;t
singleline_comment|// %0 and %1 get overwritten by exception handler&bslash;n&quot;&t;&bslash;
l_string|&quot;2:&bslash;n&bslash;t.xdata4 &bslash;&quot;__ex_table&bslash;&quot;, @gprel(1b), (2b-1b)|1&bslash;n&quot;
"&bslash;"
suffix:colon
l_string|&quot;=r&quot;
(paren
id|__gu_val
)paren
comma
l_string|&quot;=r&quot;
(paren
id|__gu_err
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
id|__gu_err
)paren
)paren
suffix:semicolon
DECL|macro|__get_user_8
mdefine_line|#define __get_user_8(addr)&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ (&quot;&bslash;n1:&bslash;tld1 %0=%2%P2&bslash;t
singleline_comment|// %0 and %1 get overwritten by exception handler&bslash;n&quot;&t;&bslash;
l_string|&quot;2:&bslash;n&bslash;t.xdata4 &bslash;&quot;__ex_table&bslash;&quot;, @gprel(1b), (2b-1b)|1&bslash;n&quot;
"&bslash;"
suffix:colon
l_string|&quot;=r&quot;
(paren
id|__gu_val
)paren
comma
l_string|&quot;=r&quot;
(paren
id|__gu_err
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
id|__gu_err
)paren
)paren
suffix:semicolon
r_extern
r_void
id|__put_user_unknown
(paren
r_void
)paren
suffix:semicolon
DECL|macro|__put_user_nocheck
mdefine_line|#define __put_user_nocheck(x,ptr,size)&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;register long __pu_err __asm__ (&quot;r8&quot;) = 0;&t;&t;&bslash;&n;&t;switch (size) {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;  case 1: __put_user_8(x,ptr); break;&t;&t;&t;&bslash;&n;&t;  case 2: __put_user_16(x,ptr); break;&t;&t;&t;&bslash;&n;&t;  case 4: __put_user_32(x,ptr); break;&t;&t;&t;&bslash;&n;&t;  case 8: __put_user_64(x,ptr); break;&t;&t;&t;&bslash;&n;&t;  default: __put_user_unknown(); break;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__pu_err;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|__put_user_check
mdefine_line|#define __put_user_check(x,ptr,size,segment)&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;register long __pu_err __asm__ (&quot;r8&quot;) = -EFAULT;&t;&bslash;&n;&t;__typeof__(*(ptr)) *__pu_addr = (ptr);&t;&t;&t;&bslash;&n;&t;if (__access_ok((long)__pu_addr,size,segment)) {&t;&bslash;&n;&t;&t;__pu_err = 0;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;switch (size) {&t;&t;&t;&t;&t;&bslash;&n;&t;&t;  case 1: __put_user_8(x,__pu_addr); break;&t;&bslash;&n;&t;&t;  case 2: __put_user_16(x,__pu_addr); break;&t;&bslash;&n;&t;&t;  case 4: __put_user_32(x,__pu_addr); break;&t;&bslash;&n;&t;&t;  case 8: __put_user_64(x,__pu_addr); break;&t;&bslash;&n;&t;&t;  default: __put_user_unknown(); break;&t;&t;&bslash;&n;&t;&t;}&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__pu_err;&t;&t;&t;&t;&t;&t;&bslash;&n;})
multiline_comment|/*&n; * The &quot;__put_user_xx()&quot; macros tell gcc they read from memory&n; * instead of writing: this is because they do not write to&n; * any memory gcc knows about, so there are no aliasing issues&n; */
DECL|macro|__put_user_64
mdefine_line|#define __put_user_64(x,addr)&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__ (&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t; &quot;&bslash;n1:&bslash;tst8 %1=%r2%P1&bslash;t
singleline_comment|// %0 gets overwritten by exception handler&bslash;n&quot;&t;&bslash;
l_string|&quot;2:&bslash;n&bslash;t.xdata4 &bslash;&quot;__ex_table&bslash;&quot;, @gprel(1b), (2b-1b)&bslash;n&quot;
"&bslash;"
suffix:colon
l_string|&quot;=r&quot;
(paren
id|__pu_err
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
id|x
)paren
comma
l_string|&quot;0&quot;
(paren
id|__pu_err
)paren
)paren
DECL|macro|__put_user_32
mdefine_line|#define __put_user_32(x,addr)&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__ (&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t; &quot;&bslash;n1:&bslash;tst4 %1=%r2%P1&bslash;t
singleline_comment|// %0 gets overwritten by exception handler&bslash;n&quot;&t;&bslash;
l_string|&quot;2:&bslash;n&bslash;t.xdata4 &bslash;&quot;__ex_table&bslash;&quot;, @gprel(1b), (2b-1b)&bslash;n&quot;
"&bslash;"
suffix:colon
l_string|&quot;=r&quot;
(paren
id|__pu_err
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
id|x
)paren
comma
l_string|&quot;0&quot;
(paren
id|__pu_err
)paren
)paren
DECL|macro|__put_user_16
mdefine_line|#define __put_user_16(x,addr)&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__ (&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t; &quot;&bslash;n1:&bslash;tst2 %1=%r2%P1&bslash;t
singleline_comment|// %0 gets overwritten by exception handler&bslash;n&quot;&t;&bslash;
l_string|&quot;2:&bslash;n&bslash;t.xdata4 &bslash;&quot;__ex_table&bslash;&quot;, @gprel(1b), (2b-1b)&bslash;n&quot;
"&bslash;"
suffix:colon
l_string|&quot;=r&quot;
(paren
id|__pu_err
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
id|x
)paren
comma
l_string|&quot;0&quot;
(paren
id|__pu_err
)paren
)paren
DECL|macro|__put_user_8
mdefine_line|#define __put_user_8(x,addr)&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__ (&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t; &quot;&bslash;n1:&bslash;tst1 %1=%r2%P1&bslash;t
singleline_comment|// %0 gets overwritten by exception handler&bslash;n&quot;&t;&bslash;
l_string|&quot;2:&bslash;n&bslash;t.xdata4 &bslash;&quot;__ex_table&bslash;&quot;, @gprel(1b), (2b-1b)&bslash;n&quot;
"&bslash;"
suffix:colon
l_string|&quot;=r&quot;
(paren
id|__pu_err
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
id|x
)paren
comma
l_string|&quot;0&quot;
(paren
id|__pu_err
)paren
)paren
multiline_comment|/*&n; * Complex access routines&n; */
r_extern
r_int
r_int
id|__copy_user
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
id|count
)paren
suffix:semicolon
DECL|macro|__copy_to_user
mdefine_line|#define __copy_to_user(to,from,n)&t;__copy_user((to), (from), (n))
DECL|macro|__copy_from_user
mdefine_line|#define __copy_from_user(to,from,n) &t;__copy_user((to), (from), (n))
DECL|macro|copy_to_user
mdefine_line|#define copy_to_user(to,from,n)   __copy_tofrom_user((to), (from), (n), 1)
DECL|macro|copy_from_user
mdefine_line|#define copy_from_user(to,from,n) __copy_tofrom_user((to), (from), (n), 0)
DECL|macro|__copy_tofrom_user
mdefine_line|#define __copy_tofrom_user(to,from,n,check_to)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;void *__cu_to = (to);&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;const void *__cu_from = (from);&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;long __cu_len = (n);&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (__access_ok((long) ((check_to) ? __cu_to : __cu_from), __cu_len, get_fs())) {&t;&bslash;&n;&t;&t;__cu_len = __copy_user(__cu_to, __cu_from, __cu_len);&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__cu_len;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
r_extern
r_int
r_int
id|__do_clear_user
(paren
r_void
op_star
comma
r_int
r_int
)paren
suffix:semicolon
DECL|macro|__clear_user
mdefine_line|#define __clear_user(to,n)&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__do_clear_user(to,n);&t;&t;&t;&bslash;&n;})
DECL|macro|clear_user
mdefine_line|#define clear_user(to,n)&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long __cu_len = (n);&t;&t;&t;&t;&bslash;&n;&t;if (__access_ok((long) to, __cu_len, get_fs())) {&t;&bslash;&n;&t;&t;__cu_len = __do_clear_user(to, __cu_len);&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__cu_len;&t;&t;&t;&t;&t;&t;&bslash;&n;})
multiline_comment|/* Returns: -EFAULT if exception before terminator, N if the entire&n;   buffer filled, else strlen.  */
r_extern
r_int
id|__strncpy_from_user
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
id|to_len
)paren
suffix:semicolon
DECL|macro|strncpy_from_user
mdefine_line|#define strncpy_from_user(to,from,n)&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;const char * __sfu_from = (from);&t;&t;&t;&t;&bslash;&n;&t;long __sfu_ret = -EFAULT;&t;&t;&t;&t;&t;&bslash;&n;&t;if (__access_ok((long) __sfu_from, 0, get_fs()))&t;&t;&bslash;&n;&t;&t;__sfu_ret = __strncpy_from_user((to), __sfu_from, (n));&t;&bslash;&n;&t;__sfu_ret;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
multiline_comment|/* Returns: 0 if bad, string length+1 (memory size) of string if ok */
r_extern
r_int
r_int
id|__strlen_user
(paren
r_const
r_char
op_star
)paren
suffix:semicolon
DECL|macro|strlen_user
mdefine_line|#define strlen_user(str)&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;const char *__su_str = (str);&t;&t;&t;&bslash;&n;&t;unsigned long __su_ret = 0;&t;&t;&t;&bslash;&n;&t;if (__access_ok((long) __su_str, 0, get_fs()))&t;&bslash;&n;&t;&t;__su_ret = __strlen_user(__su_str);&t;&bslash;&n;&t;__su_ret;&t;&t;&t;&t;&t;&bslash;&n;})
multiline_comment|/*&n; * Returns: 0 if exception before NUL or reaching the supplied limit&n; * (N), a value greater than N if the limit would be exceeded, else&n; * strlen.&n; */
r_extern
r_int
r_int
id|__strnlen_user
(paren
r_const
r_char
op_star
comma
r_int
)paren
suffix:semicolon
DECL|macro|strnlen_user
mdefine_line|#define strnlen_user(str, len)&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;const char *__su_str = (str);&t;&t;&t;&t;&bslash;&n;&t;unsigned long __su_ret = 0;&t;&t;&t;&t;&bslash;&n;&t;if (__access_ok((long) __su_str, 0, get_fs()))&t;&t;&bslash;&n;&t;&t;__su_ret = __strnlen_user(__su_str, len);&t;&bslash;&n;&t;__su_ret;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|struct|exception_table_entry
r_struct
id|exception_table_entry
(brace
DECL|member|addr
r_int
id|addr
suffix:semicolon
multiline_comment|/* gp-relative address of insn this fixup is for */
DECL|member|skip
r_int
id|skip
suffix:semicolon
multiline_comment|/* number of bytes to skip to get to the continuation point.&n;&t;&t;&t;   Bit 0 tells us if r9 should be cleared to 0*/
)brace
suffix:semicolon
r_extern
r_const
r_struct
id|exception_table_entry
op_star
id|search_exception_table
(paren
r_int
r_int
id|addr
)paren
suffix:semicolon
macro_line|#endif /* _ASM_IA64_UACCESS_H */
eof
