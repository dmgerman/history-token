macro_line|#ifndef _ASMARM_UACCESS_H
DECL|macro|_ASMARM_UACCESS_H
mdefine_line|#define _ASMARM_UACCESS_H
multiline_comment|/*&n; * User space memory access functions&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/errno.h&gt;
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
DECL|macro|get_ds
mdefine_line|#define get_ds()&t;(KERNEL_DS)
DECL|macro|get_fs
mdefine_line|#define get_fs()&t;(current_thread_info()-&gt;addr_limit)
DECL|macro|segment_eq
mdefine_line|#define segment_eq(a,b)&t;((a) == (b))
macro_line|#include &lt;asm/proc/uaccess.h&gt;
DECL|macro|access_ok
mdefine_line|#define access_ok(type,addr,size)&t;(__range_ok(addr,size) == 0)
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
mdefine_line|#define __get_user_x(__r1,__p,__e,__s,__i...)&t;&t;&t;&t;&bslash;&n;&t;   __asm__ __volatile__ (&quot;bl&t;__get_user_&quot; #__s&t;&t;&bslash;&n;&t;&t;: &quot;=&amp;r&quot; (__e), &quot;=r&quot; (__r1)&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;0&quot; (__p)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: __i)
DECL|macro|get_user
mdefine_line|#define get_user(x,p)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;const register typeof(*(p)) *__p asm(&quot;r0&quot;) = (p);&t;&bslash;&n;&t;&t;register typeof(*(p)) __r1 asm(&quot;r1&quot;);&t;&t;&t;&bslash;&n;&t;&t;register int __e asm(&quot;r0&quot;);&t;&t;&t;&t;&bslash;&n;&t;&t;switch (sizeof(*(__p))) {&t;&t;&t;&t;&bslash;&n;&t;&t;case 1:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;__get_user_x(__r1, __p, __e, 1, &quot;lr&quot;);&t;&t;&bslash;&n;&t;       &t;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;case 2:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;__get_user_x(__r1, __p, __e, 2, &quot;r2&quot;, &quot;lr&quot;);&t;&bslash;&n;&t;&t;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;case 4:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;       &t;&t;__get_user_x(__r1, __p, __e, 4, &quot;lr&quot;);&t;&t;&bslash;&n;&t;&t;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;case 8:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;__get_user_x(__r1, __p, __e, 8, &quot;lr&quot;);&t;&t;&bslash;&n;&t;       &t;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;default: __e = __get_user_bad(); break;&t;&t;&t;&bslash;&n;&t;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;x = __r1;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__e;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;})
DECL|macro|__get_user
mdefine_line|#define __get_user(x,p)&t;&t;__get_user_nocheck((x),(p),sizeof(*(p)))
DECL|macro|__get_user_error
mdefine_line|#define __get_user_error(x,p,e)&t;__get_user_nocheck_error((x),(p),sizeof(*(p)),(e))
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
mdefine_line|#define __put_user_x(__r1,__p,__e,__s,__i...)&t;&t;&t;&t;&bslash;&n;&t;   __asm__ __volatile__ (&quot;bl&t;__put_user_&quot; #__s&t;&t;&bslash;&n;&t;&t;: &quot;=&amp;r&quot; (__e)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;0&quot; (__p), &quot;r&quot; (__r1)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: __i)
DECL|macro|put_user
mdefine_line|#define put_user(x,p)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;const register typeof(*(p)) __r1 asm(&quot;r1&quot;) = (x);&t;&bslash;&n;&t;&t;const register typeof(*(p)) *__p asm(&quot;r0&quot;) = (p);&t;&bslash;&n;&t;&t;register int __e asm(&quot;r0&quot;);&t;&t;&t;&t;&bslash;&n;&t;&t;switch (sizeof(*(__p))) {&t;&t;&t;&t;&bslash;&n;&t;&t;case 1:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;__put_user_x(__r1, __p, __e, 1, &quot;r2&quot;, &quot;lr&quot;);&t;&bslash;&n;&t;&t;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;case 2:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;__put_user_x(__r1, __p, __e, 2, &quot;r2&quot;, &quot;lr&quot;);&t;&bslash;&n;&t;&t;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;case 4:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;__put_user_x(__r1, __p, __e, 4, &quot;r2&quot;, &quot;lr&quot;);&t;&bslash;&n;&t;&t;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;case 8:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;__put_user_x(__r1, __p, __e, 8, &quot;ip&quot;, &quot;lr&quot;);&t;&bslash;&n;&t;&t;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;default: __e = __put_user_bad(); break;&t;&t;&t;&bslash;&n;&t;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__e;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;})
DECL|macro|__put_user
mdefine_line|#define __put_user(x,p)&t;&t;__put_user_nocheck((__typeof(*(p)))(x),(p),sizeof(*(p)))
DECL|macro|__put_user_error
mdefine_line|#define __put_user_error(x,p,e)&t;__put_user_nocheck_error((x),(p),sizeof(*(p)),(e))
DECL|function|copy_from_user
r_static
id|__inline__
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
id|__do_copy_from_user
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
id|__inline__
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
op_star
id|from
comma
r_int
r_int
id|n
)paren
(brace
id|__do_copy_from_user
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
DECL|function|copy_to_user
r_static
id|__inline__
r_int
r_int
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
id|__do_copy_to_user
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
id|__inline__
r_int
r_int
id|__copy_to_user
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
id|__do_copy_to_user
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
DECL|function|clear_user
r_static
id|__inline__
r_int
r_int
id|clear_user
(paren
r_void
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
DECL|function|__clear_user
r_static
id|__inline__
r_int
r_int
id|__clear_user
(paren
r_void
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
DECL|function|strncpy_from_user
r_static
id|__inline__
r_int
id|strncpy_from_user
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
DECL|function|__strncpy_from_user
r_static
id|__inline__
r_int
id|__strncpy_from_user
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
id|__do_strnlen_user
c_func
(paren
id|s
comma
id|n
comma
id|res
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
multiline_comment|/*&n; * These are the work horses of the get/put_user functions&n; */
macro_line|#if 0
mdefine_line|#define __get_user_check(x,ptr,size)&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;long __gu_err = -EFAULT, __gu_val = 0;&t;&t;&t;&t;&bslash;&n;&t;const __typeof__(*(ptr)) *__gu_addr = (ptr);&t;&t;&t;&bslash;&n;&t;if (access_ok(VERIFY_READ,__gu_addr,size)) {&t;&t;&t;&bslash;&n;&t;&t;__gu_err = 0;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__get_user_size(__gu_val,__gu_addr,(size),__gu_err);&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(x) = (__typeof__(*(ptr)))__gu_val;&t;&t;&t;&t;&bslash;&n;&t;__gu_err;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
macro_line|#endif
DECL|macro|__get_user_nocheck
mdefine_line|#define __get_user_nocheck(x,ptr,size)&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;long __gu_err = 0, __gu_val;&t;&t;&t;&t;&t;&bslash;&n;&t;__get_user_size(__gu_val,(ptr),(size),__gu_err);&t;&t;&bslash;&n;&t;(x) = (__typeof__(*(ptr)))__gu_val;&t;&t;&t;&t;&bslash;&n;&t;__gu_err;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|__get_user_nocheck_error
mdefine_line|#define __get_user_nocheck_error(x,ptr,size,err)&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;long __gu_val;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__get_user_size(__gu_val,(ptr),(size),(err));&t;&t;&t;&bslash;&n;&t;(x) = (__typeof__(*(ptr)))__gu_val;&t;&t;&t;&t;&bslash;&n;&t;(void) 0;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|__put_user_check
mdefine_line|#define __put_user_check(x,ptr,size)&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;long __pu_err = -EFAULT;&t;&t;&t;&t;&t;&bslash;&n;&t;__typeof__(*(ptr)) *__pu_addr = (ptr);&t;&t;&t;&t;&bslash;&n;&t;if (access_ok(VERIFY_WRITE,__pu_addr,size)) {&t;&t;&t;&bslash;&n;&t;&t;__pu_err = 0;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__put_user_size((x),__pu_addr,(size),__pu_err);&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__pu_err;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|__put_user_nocheck
mdefine_line|#define __put_user_nocheck(x,ptr,size)&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;long __pu_err = 0;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long __pu_addr = (unsigned long)(ptr);&t;&t;&t;&bslash;&n;&t;__put_user_size((x),__pu_addr,(size),__pu_err);&t;&t;&t;&bslash;&n;&t;__pu_err;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|__put_user_nocheck_error
mdefine_line|#define __put_user_nocheck_error(x,ptr,size,err)&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long __pu_addr = (unsigned long)(ptr);&t;&t;&t;&bslash;&n;&t;__put_user_size((x),__pu_addr,(size),err);&t;&t;&t;&bslash;&n;&t;(void) 0;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|__get_user_size
mdefine_line|#define __get_user_size(x,ptr,size,retval)&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;switch (size) {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;case 1:&t;__get_user_asm_byte(x,ptr,retval);&t;break;&t;&t;&bslash;&n;&t;case 2:&t;__get_user_asm_half(x,ptr,retval);&t;break;&t;&t;&bslash;&n;&t;case 4:&t;__get_user_asm_word(x,ptr,retval);&t;break;&t;&t;&bslash;&n;&t;case 8:&t;__get_user_asm_dword(x,ptr,retval);&t;break;&t;&t;&bslash;&n;&t;default: (x) = __get_user_bad();&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|__put_user_size
mdefine_line|#define __put_user_size(x,ptr,size,retval)&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;switch (size) {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;case 1: __put_user_asm_byte(x,ptr,retval);&t;break;&t;&t;&bslash;&n;&t;case 2: __put_user_asm_half(x,ptr,retval);&t;break;&t;&t;&bslash;&n;&t;case 4: __put_user_asm_word(x,ptr,retval);&t;break;&t;&t;&bslash;&n;&t;case 8:&t;__put_user_asm_dword(x,ptr,retval);&t;break;&t;&t;&bslash;&n;&t;default: __put_user_bad();&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
macro_line|#endif /* _ASMARM_UACCESS_H */
eof
