multiline_comment|/*&n; * BK Id: %F% %I% %G% %U% %#%&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef _PPC_UACCESS_H
DECL|macro|_PPC_UACCESS_H
mdefine_line|#define _PPC_UACCESS_H
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
DECL|macro|VERIFY_READ
mdefine_line|#define VERIFY_READ&t;0
DECL|macro|VERIFY_WRITE
mdefine_line|#define VERIFY_WRITE&t;1
multiline_comment|/*&n; * The fs value determines whether argument validity checking should be&n; * performed or not.  If get_fs() == USER_DS, checking is performed, with&n; * get_fs() == KERNEL_DS, checking is bypassed.&n; *&n; * For historical reasons, these macros are grossly misnamed.&n; */
DECL|macro|KERNEL_DS
mdefine_line|#define KERNEL_DS&t;((mm_segment_t) { 0 })
DECL|macro|USER_DS
mdefine_line|#define USER_DS&t;&t;((mm_segment_t) { 1 })
DECL|macro|get_ds
mdefine_line|#define get_ds()&t;(KERNEL_DS)
DECL|macro|get_fs
mdefine_line|#define get_fs()&t;(current-&gt;thread.fs)
DECL|macro|set_fs
mdefine_line|#define set_fs(val)&t;(current-&gt;thread.fs = (val))
DECL|macro|segment_eq
mdefine_line|#define segment_eq(a,b)&t;((a).seg == (b).seg)
DECL|macro|__kernel_ok
mdefine_line|#define __kernel_ok (segment_eq(get_fs(), KERNEL_DS))
DECL|macro|__user_ok
mdefine_line|#define __user_ok(addr,size) (((size) &lt;= TASK_SIZE)&amp;&amp;((addr) &lt;= TASK_SIZE-(size)))
DECL|macro|__access_ok
mdefine_line|#define __access_ok(addr,size) (__kernel_ok || __user_ok((addr),(size)))
DECL|macro|access_ok
mdefine_line|#define access_ok(type,addr,size) __access_ok((unsigned long)(addr),(size))
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
multiline_comment|/* Returns 0 if exception not found and fixup otherwise.  */
r_extern
r_int
r_int
id|search_exception_table
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|sort_exception_table
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * These are the main single-value transfer routines.  They automatically&n; * use the right size if we just have the right pointer type.&n; *&n; * This gets kind of ugly. We want to return _two_ values in &quot;get_user()&quot;&n; * and yet we don&squot;t want to do any pointers, because that is too much&n; * of a performance impact. Thus we have a few rather ugly macros here,&n; * and hide all the uglyness from the user.&n; *&n; * The &quot;__xxx&quot; versions of the user access functions are versions that&n; * do not verify the address space, that must have been done previously&n; * with a separate &quot;access_ok()&quot; call (this is used when we do multiple&n; * accesses to the same area of user memory).&n; *&n; * As we use the same address space for kernel and user data on the&n; * PowerPC, we can just do these as direct assignments.  (Of course, the&n; * exception handling means that it&squot;s no longer &quot;just&quot;...)&n; */
DECL|macro|get_user
mdefine_line|#define get_user(x,ptr) &bslash;&n;  __get_user_check((x),(ptr),sizeof(*(ptr)))
DECL|macro|put_user
mdefine_line|#define put_user(x,ptr) &bslash;&n;  __put_user_check((__typeof__(*(ptr)))(x),(ptr),sizeof(*(ptr)))
DECL|macro|__get_user
mdefine_line|#define __get_user(x,ptr) &bslash;&n;  __get_user_nocheck((x),(ptr),sizeof(*(ptr)))
DECL|macro|__put_user
mdefine_line|#define __put_user(x,ptr) &bslash;&n;  __put_user_nocheck((__typeof__(*(ptr)))(x),(ptr),sizeof(*(ptr)))
r_extern
r_int
id|__put_user_bad
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|__put_user_nocheck
mdefine_line|#define __put_user_nocheck(x,ptr,size)&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;long __pu_err;&t;&t;&t;&t;&t;&bslash;&n;&t;__put_user_size((x),(ptr),(size),__pu_err);&t;&bslash;&n;&t;__pu_err;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|__put_user_check
mdefine_line|#define __put_user_check(x,ptr,size)&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;long __pu_err = -EFAULT;&t;&t;&t;&t;&bslash;&n;&t;__typeof__(*(ptr)) *__pu_addr = (ptr);&t;&t;&t;&bslash;&n;&t;if (access_ok(VERIFY_WRITE,__pu_addr,size))&t;&t;&bslash;&n;&t;&t;__put_user_size((x),__pu_addr,(size),__pu_err);&t;&bslash;&n;&t;__pu_err;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|__put_user_size
mdefine_line|#define __put_user_size(x,ptr,size,retval)&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;retval = 0;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;switch (size) {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;  case 1: __put_user_asm(x,ptr,retval,&quot;stb&quot;); break;&t;&bslash;&n;&t;  case 2: __put_user_asm(x,ptr,retval,&quot;sth&quot;); break;&t;&bslash;&n;&t;  case 4: __put_user_asm(x,ptr,retval,&quot;stw&quot;); break;&t;&bslash;&n;&t;  case 8: __put_user_asm2(x,ptr,retval); break;&t;&t;&bslash;&n;&t;  default: __put_user_bad();&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
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
multiline_comment|/*&n; * We don&squot;t tell gcc that we are accessing memory, but this is OK&n; * because we do not write to any memory gcc knows about, so there&n; * are no aliasing issues.&n; */
DECL|macro|__put_user_asm
mdefine_line|#define __put_user_asm(x, addr, err, op)&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;1:&t;&quot;op&quot; %1,0(%2)&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;2:&bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;3:&t;li %0,%3&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;b 2b&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.previous&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.align 2&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.long 1b,3b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.previous&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=r&quot;(err)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;r&quot;(x), &quot;b&quot;(addr), &quot;i&quot;(-EFAULT), &quot;0&quot;(err))
DECL|macro|__put_user_asm2
mdefine_line|#define __put_user_asm2(x, addr, err)&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;1:&t;stw %1,0(%2)&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;2:&t;stw %1+1,4(%2)&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;3:&bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;4:&t;li %0,%3&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;b 3b&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.previous&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.align 2&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.long 1b,4b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.long 2b,4b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.previous&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=r&quot;(err)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;r&quot;(x), &quot;b&quot;(addr), &quot;i&quot;(-EFAULT), &quot;0&quot;(err))
DECL|macro|__get_user_nocheck
mdefine_line|#define __get_user_nocheck(x,ptr,size)&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;long __gu_err, __gu_val;&t;&t;&t;&t;&bslash;&n;&t;__get_user_size(__gu_val,(ptr),(size),__gu_err);&t;&bslash;&n;&t;(x) = (__typeof__(*(ptr)))__gu_val;&t;&t;&t;&bslash;&n;&t;__gu_err;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|__get_user_check
mdefine_line|#define __get_user_check(x,ptr,size)&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;long __gu_err = -EFAULT, __gu_val = 0;&t;&t;&t;&t;&bslash;&n;&t;const __typeof__(*(ptr)) *__gu_addr = (ptr);&t;&t;&t;&bslash;&n;&t;if (access_ok(VERIFY_READ,__gu_addr,size))&t;&t;&t;&bslash;&n;&t;&t;__get_user_size(__gu_val,__gu_addr,(size),__gu_err);&t;&bslash;&n;&t;(x) = (__typeof__(*(ptr)))__gu_val;&t;&t;&t;&t;&bslash;&n;&t;__gu_err;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
r_extern
r_int
id|__get_user_bad
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|__get_user_size
mdefine_line|#define __get_user_size(x,ptr,size,retval)&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;retval = 0;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;switch (size) {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;  case 1: __get_user_asm(x,ptr,retval,&quot;lbz&quot;); break;&t;&bslash;&n;&t;  case 2: __get_user_asm(x,ptr,retval,&quot;lhz&quot;); break;&t;&bslash;&n;&t;  case 4: __get_user_asm(x,ptr,retval,&quot;lwz&quot;); break;&t;&bslash;&n;&t;  case 8: __get_user_asm2(x, ptr, retval);&t;&t;&bslash;&n;&t;  default: (x) = __get_user_bad();&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|__get_user_asm
mdefine_line|#define __get_user_asm(x, addr, err, op)&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;1:&t;&quot;op&quot; %1,0(%2)&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&quot;2:&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&quot;3:&t;li %0,%3&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;li %1,0&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;b 2b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.previous&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&quot;&t;.align 2&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.long 1b,3b&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;.previous&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=r&quot;(err), &quot;=r&quot;(x)&t;&t;&t;&bslash;&n;&t;&t;: &quot;b&quot;(addr), &quot;i&quot;(-EFAULT), &quot;0&quot;(err))
DECL|macro|__get_user_asm2
mdefine_line|#define __get_user_asm2(x, addr, err)&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;1:&t;lwz %1,0(%2)&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;2:&t;lwz %1+1,4(%2)&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&quot;3:&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&quot;4:&t;li %0,%3&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;li %1,0&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;li %1+1,0&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;b 3b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.previous&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&quot;&t;.align 2&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.long 1b,4b&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.long 2b,4b&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;.previous&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=r&quot;(err), &quot;=&amp;r&quot;(x)&t;&t;&t;&bslash;&n;&t;&t;: &quot;b&quot;(addr), &quot;i&quot;(-EFAULT), &quot;0&quot;(err))
multiline_comment|/* more complex routines */
r_extern
r_int
id|__copy_tofrom_user
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
r_extern
r_inline
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
op_star
id|from
comma
r_int
r_int
id|n
)paren
(brace
r_int
r_int
id|over
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
r_return
id|__copy_tofrom_user
c_func
(paren
id|to
comma
id|from
comma
id|n
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
r_int
r_int
)paren
id|from
OL
id|TASK_SIZE
)paren
(brace
id|over
op_assign
(paren
r_int
r_int
)paren
id|from
op_plus
id|n
op_minus
id|TASK_SIZE
suffix:semicolon
r_return
id|__copy_tofrom_user
c_func
(paren
id|to
comma
id|from
comma
id|n
op_minus
id|over
)paren
op_plus
id|over
suffix:semicolon
)brace
r_return
id|n
suffix:semicolon
)brace
r_extern
r_inline
r_int
r_int
DECL|function|copy_to_user
id|copy_to_user
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
r_int
r_int
id|over
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
r_return
id|__copy_tofrom_user
c_func
(paren
id|to
comma
id|from
comma
id|n
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
r_int
r_int
)paren
id|to
OL
id|TASK_SIZE
)paren
(brace
id|over
op_assign
(paren
r_int
r_int
)paren
id|to
op_plus
id|n
op_minus
id|TASK_SIZE
suffix:semicolon
r_return
id|__copy_tofrom_user
c_func
(paren
id|to
comma
id|from
comma
id|n
op_minus
id|over
)paren
op_plus
id|over
suffix:semicolon
)brace
r_return
id|n
suffix:semicolon
)brace
DECL|macro|__copy_from_user
mdefine_line|#define __copy_from_user(to, from, size) &bslash;&n;&t;__copy_tofrom_user((to), (from), (size))
DECL|macro|__copy_to_user
mdefine_line|#define __copy_to_user(to, from, size) &bslash;&n;&t;__copy_tofrom_user((to), (from), (size))
r_extern
r_int
r_int
id|__clear_user
c_func
(paren
r_void
op_star
id|addr
comma
r_int
r_int
id|size
)paren
suffix:semicolon
r_extern
r_inline
r_int
r_int
DECL|function|clear_user
id|clear_user
c_func
(paren
r_void
op_star
id|addr
comma
r_int
r_int
id|size
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
id|addr
comma
id|size
)paren
)paren
r_return
id|__clear_user
c_func
(paren
id|addr
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
r_int
r_int
)paren
id|addr
OL
id|TASK_SIZE
)paren
(brace
r_int
r_int
id|over
op_assign
(paren
r_int
r_int
)paren
id|addr
op_plus
id|size
op_minus
id|TASK_SIZE
suffix:semicolon
r_return
id|__clear_user
c_func
(paren
id|addr
comma
id|size
op_minus
id|over
)paren
op_plus
id|over
suffix:semicolon
)brace
r_return
id|size
suffix:semicolon
)brace
r_extern
r_int
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
suffix:semicolon
r_extern
r_inline
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
r_return
id|__strncpy_from_user
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
op_minus
id|EFAULT
suffix:semicolon
)brace
multiline_comment|/*&n; * Return the size of a string (including the ending 0)&n; *&n; * Return 0 for error&n; */
r_extern
r_int
id|__strnlen_user
c_func
(paren
r_const
r_char
op_star
id|str
comma
r_int
id|len
comma
r_int
r_int
id|top
)paren
suffix:semicolon
multiline_comment|/*&n; * Returns the length of the string at str (including the null byte),&n; * or 0 if we hit a page we can&squot;t access,&n; * or something &gt; len if we didn&squot;t find a null byte.&n; *&n; * The `top&squot; parameter to __strnlen_user is to make sure that&n; * we can never overflow from the user area into kernel space.&n; */
DECL|function|strnlen_user
r_extern
id|__inline__
r_int
id|strnlen_user
c_func
(paren
r_const
r_char
op_star
id|str
comma
r_int
id|len
)paren
(brace
r_int
r_int
id|top
op_assign
id|__kernel_ok
ques
c_cond
op_complement
l_int|0UL
suffix:colon
id|TASK_SIZE
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
(paren
r_int
r_int
)paren
id|str
OG
id|top
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|__strnlen_user
c_func
(paren
id|str
comma
id|len
comma
id|top
)paren
suffix:semicolon
)brace
DECL|macro|strlen_user
mdefine_line|#define strlen_user(str)&t;strnlen_user((str), 0x7ffffffe)
macro_line|#endif  /* __ASSEMBLY__ */
macro_line|#endif&t;/* _PPC_UACCESS_H */
macro_line|#endif /* __KERNEL__ */
eof
