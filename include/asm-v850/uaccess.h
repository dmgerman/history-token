macro_line|#ifndef __V850_UACCESS_H__
DECL|macro|__V850_UACCESS_H__
mdefine_line|#define __V850_UACCESS_H__
multiline_comment|/*&n; * User space memory access functions&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
DECL|macro|VERIFY_READ
mdefine_line|#define VERIFY_READ&t;0
DECL|macro|VERIFY_WRITE
mdefine_line|#define VERIFY_WRITE&t;1
DECL|function|access_ok
r_extern
r_inline
r_int
id|access_ok
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
multiline_comment|/* XXX I guess we should check against real ram bounds at least, and&n;&t;   possibly make sure ADDR is not within the kernel.&n;&t;   For now we just check to make sure it&squot;s not a small positive&n;&t;   or negative value, as that will at least catch some kinds of&n;&t;   error.  In particular, we make sure that ADDR&squot;s not within the&n;&t;   interrupt vector area, which we know starts at zero, or within the&n;&t;   peripheral-I/O area, which is located just _before_ zero.  */
r_int
r_int
id|val
op_assign
(paren
r_int
r_int
)paren
id|addr
suffix:semicolon
r_return
id|val
op_ge
(paren
l_int|0x80
op_plus
id|NUM_CPU_IRQS
op_star
l_int|16
)paren
op_logical_and
id|val
OL
l_int|0xFFFFF000
suffix:semicolon
)brace
DECL|function|verify_area
r_extern
r_inline
r_int
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
(paren
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; * These are the main single-value transfer routines.  They automatically&n; * use the right size if we just have the right pointer type.&n; */
r_extern
r_int
id|bad_user_access_length
(paren
r_void
)paren
suffix:semicolon
DECL|macro|__get_user
mdefine_line|#define __get_user(var, ptr)&t;&t;&t;&t;&t;&t;      &bslash;&n;  ({&t;&t;&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;  int __gu_err = 0;&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;  typeof(*(ptr)) __gu_val = 0;&t;&t;&t;&t;&t;      &bslash;&n;&t;  switch (sizeof (*(ptr))) {&t;&t;&t;&t;&t;      &bslash;&n;&t;  case 1:&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;  case 2:&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;  case 4:&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;&t;  __gu_val = *(ptr);&t;&t;&t;&t;&t;      &bslash;&n;&t;&t;  break;&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;  case 8:&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;&t;  memcpy(&amp;__gu_val, ptr, sizeof(__gu_val));&t;&t;      &bslash;&n;&t;&t;  break;&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;  default:&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;&t;  __gu_val = 0;&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;&t;  __gu_err = __get_user_bad ();&t;&t;&t;&t;      &bslash;&n;&t;&t;  break;&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;  }&t;&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;  (var) = __gu_val;&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;  __gu_err;&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;  })
DECL|macro|__get_user_bad
mdefine_line|#define __get_user_bad()&t;(bad_user_access_length (), (-EFAULT))
DECL|macro|__put_user
mdefine_line|#define __put_user(var, ptr)&t;&t;&t;&t;&t;&t;      &bslash;&n;  ({&t;&t;&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;  int __pu_err = 0;&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;  switch (sizeof (*(ptr))) {&t;&t;&t;&t;&t;      &bslash;&n;&t;  case 1:&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;  case 2:&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;  case 4:&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;&t;  *(ptr) = (var);&t;&t;&t;&t;&t;      &bslash;&n;&t;&t;  break;&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;  case 8: {&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;  &t;  typeof(*(ptr)) __pu_val = 0;&t;&t;&t;&t;      &bslash;&n;&t;&t;  memcpy(ptr, &amp;__pu_val, sizeof(__pu_val));&t;&t;      &bslash;&n;&t;&t;  }&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;&t;  break;&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;  default:&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;&t;  __pu_err = __put_user_bad ();&t;&t;&t;&t;      &bslash;&n;&t;&t;  break;&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;  }&t;&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;  __pu_err;&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;  })
DECL|macro|__put_user_bad
mdefine_line|#define __put_user_bad()&t;(bad_user_access_length (), (-EFAULT))
DECL|macro|put_user
mdefine_line|#define put_user(x, ptr)&t;__put_user(x, ptr)
DECL|macro|get_user
mdefine_line|#define get_user(x, ptr)&t;__get_user(x, ptr)
DECL|macro|__copy_from_user
mdefine_line|#define __copy_from_user(to, from, n)&t;(memcpy (to, from, n), 0)
DECL|macro|__copy_to_user
mdefine_line|#define __copy_to_user(to, from, n)&t;(memcpy(to, from, n), 0)
DECL|macro|copy_from_user
mdefine_line|#define copy_from_user(to, from, n)&t;__copy_from_user (to, from, n)
DECL|macro|copy_to_user
mdefine_line|#define copy_to_user(to, from, n) &t;__copy_to_user(to, from, n)
DECL|macro|copy_to_user_ret
mdefine_line|#define copy_to_user_ret(to,from,n,retval) &bslash;&n;  ({ if (copy_to_user (to,from,n)) return retval; })
DECL|macro|copy_from_user_ret
mdefine_line|#define copy_from_user_ret(to,from,n,retval) &bslash;&n;  ({ if (copy_from_user (to,from,n)) return retval; })
multiline_comment|/*&n; * Copy a null terminated string from userspace.&n; */
r_static
r_inline
r_int
DECL|function|strncpy_from_user
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
r_char
op_star
id|tmp
suffix:semicolon
id|strncpy
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
)brace
multiline_comment|/*&n; * Return the size of a string (including the ending 0)&n; *&n; * Return 0 on exception, a value greater than N if too long&n; */
DECL|function|strnlen_user
r_static
r_inline
r_int
id|strnlen_user
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
(paren
id|src
)paren
op_plus
l_int|1
suffix:semicolon
)brace
DECL|macro|strlen_user
mdefine_line|#define strlen_user(str)&t;strnlen_user (str, 32767)
multiline_comment|/*&n; * Zero Userspace&n; */
r_static
r_inline
r_int
r_int
DECL|function|clear_user
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
id|memset
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
macro_line|#endif /* __V850_UACCESS_H__ */
eof
