macro_line|#ifndef __H8300_UACCESS_H
DECL|macro|__H8300_UACCESS_H
mdefine_line|#define __H8300_UACCESS_H
multiline_comment|/*&n; * User space memory access functions&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
DECL|macro|VERIFY_READ
mdefine_line|#define VERIFY_READ&t;0
DECL|macro|VERIFY_WRITE
mdefine_line|#define VERIFY_WRITE&t;1
multiline_comment|/* We let the MMU do all checking */
DECL|macro|access_ok
mdefine_line|#define access_ok(type, addr, size) __access_ok((unsigned long)addr,size)
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
DECL|macro|RANGE_CHECK_OK
mdefine_line|#define&t;RANGE_CHECK_OK(addr, size, lower, upper) &bslash;&n;&t;(((addr) &gt;= (lower)) &amp;&amp; (((addr) + (size)) &lt; (upper)))
r_extern
r_int
r_int
id|_ramend
suffix:semicolon
r_return
id|RANGE_CHECK_OK
c_func
(paren
id|addr
comma
id|size
comma
l_int|0L
comma
(paren
r_int
r_int
)paren
op_amp
id|_ramend
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
multiline_comment|/*&n; * These are the main single-value transfer routines.  They automatically&n; * use the right size if we just have the right pointer type.&n; */
DECL|macro|put_user
mdefine_line|#define put_user(x, ptr)&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    int __pu_err = 0;&t;&t;&t;&t;&t;&bslash;&n;    typeof(*(ptr)) __pu_val = (x);&t;&t;&t;&bslash;&n;    switch (sizeof (*(ptr))) {&t;&t;&t;&t;&bslash;&n;    case 1:&t;&t;&t;&t;&t;&t;&bslash;&n;    case 2:&t;&t;&t;&t;&t;&t;&bslash;&n;    case 4:&t;&t;&t;&t;&t;&t;&bslash;&n;&t;*(ptr) = (__pu_val);   &t;        &t;&t;&bslash;&n;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;    case 8:&t;&t;&t;&t;&t;&t;&bslash;&n;&t;memcpy(ptr, &amp;__pu_val, sizeof (*(ptr)));        &bslash;&n;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;    default:&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__pu_err = __put_user_bad();&t;&t;&t;&bslash;&n;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;    }&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    __pu_err;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|__put_user
mdefine_line|#define __put_user(x, ptr) put_user(x, ptr)
r_extern
r_int
id|__put_user_bad
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * Tell gcc we read from memory instead of writing: this is because&n; * we do not write to any memory gcc knows about, so there are no&n; * aliasing issues.&n; */
DECL|macro|__ptr
mdefine_line|#define __ptr(x) ((unsigned long *)(x))
multiline_comment|/*&n; * Tell gcc we read from memory instead of writing: this is because&n; * we do not write to any memory gcc knows about, so there are no&n; * aliasing issues.&n; */
DECL|macro|get_user
mdefine_line|#define get_user(x, ptr)&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    int __gu_err = 0;&t;&t;&t;&t;&t;&t;&bslash;&n;    typeof(*(ptr)) __gu_val = 0;&t;&t;&t;&t;&bslash;&n;    switch (sizeof(*(ptr))) {&t;&t;&t;&t;&t;&bslash;&n;    case 1:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    case 2:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    case 4:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__gu_val = *(ptr);&t;                &t;&t;&bslash;&n;&t;break;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    case 8:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;memcpy(&amp;__gu_val, ptr, sizeof (*(ptr))); &t;&t;&bslash;&n;&t;break;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    default:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__gu_val = 0;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__gu_err = __get_user_bad();&t;&t;&t;&t;&bslash;&n;&t;break;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    }&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    (x) = __gu_val;&t;&t;&t;&t;&t;&t;&bslash;&n;    __gu_err;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|__get_user
mdefine_line|#define __get_user(x, ptr) get_user(x, ptr)
r_extern
r_int
id|__get_user_bad
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|copy_from_user
mdefine_line|#define copy_from_user(to, from, n)&t;&t;(memcpy(to, from, n), 0)
DECL|macro|copy_to_user
mdefine_line|#define copy_to_user(to, from, n)&t;&t;(memcpy(to, from, n), 0)
DECL|macro|__copy_from_user
mdefine_line|#define __copy_from_user(to, from, n) copy_from_user(to, from, n)
DECL|macro|__copy_to_user
mdefine_line|#define __copy_to_user(to, from, n) copy_to_user(to, from, n)
DECL|macro|copy_to_user_ret
mdefine_line|#define copy_to_user_ret(to,from,n,retval) ({ if (copy_to_user(to,from,n)) return retval; })
DECL|macro|copy_from_user_ret
mdefine_line|#define copy_from_user_ret(to,from,n,retval) ({ if (copy_from_user(to,from,n)) return retval; })
multiline_comment|/*&n; * Copy a null terminated string from userspace.&n; */
r_static
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
r_char
op_star
id|tmp
suffix:semicolon
id|strncpy
c_func
(paren
id|dst
comma
id|src
comma
id|count
)paren
suffix:semicolon
r_for
c_loop
(paren
id|tmp
op_assign
id|dst
suffix:semicolon
op_star
id|tmp
op_logical_and
id|count
OG
l_int|0
suffix:semicolon
id|tmp
op_increment
comma
id|count
op_decrement
)paren
suffix:semicolon
r_return
id|tmp
op_minus
id|dst
suffix:semicolon
multiline_comment|/* DAVIDM should we count a NUL ?  check getname */
)brace
multiline_comment|/*&n; * Return the size of a string (including the ending 0)&n; *&n; * Return 0 on exception, a value greater than N if too long&n; */
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
id|src
comma
r_int
id|n
)paren
(brace
r_return
id|strlen
c_func
(paren
id|src
)paren
op_plus
l_int|1
suffix:semicolon
multiline_comment|/* DAVIDM make safer */
)brace
DECL|macro|strlen_user
mdefine_line|#define strlen_user(str) strnlen_user(str, 32767)
multiline_comment|/*&n; * Zero Userspace&n; */
r_static
r_inline
r_int
r_int
DECL|function|clear_user
id|clear_user
c_func
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
id|memset
c_func
(paren
id|to
comma
l_int|0
comma
id|n
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif /* _H8300_UACCESS_H */
eof
