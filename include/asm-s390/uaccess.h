multiline_comment|/*&n; *  include/asm-s390/uaccess.h&n; *&n; *  S390 version&n; *    Copyright (C) 1999,2000 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Hartmut Penner (hp@de.ibm.com),&n; *               Martin Schwidefsky (schwidefsky@de.ibm.com)&n; *&n; *  Derived from &quot;include/asm-i386/uaccess.h&quot;&n; */
macro_line|#ifndef __S390_UACCESS_H
DECL|macro|__S390_UACCESS_H
mdefine_line|#define __S390_UACCESS_H
multiline_comment|/*&n; * User space memory access functions&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
DECL|macro|VERIFY_READ
mdefine_line|#define VERIFY_READ     0
DECL|macro|VERIFY_WRITE
mdefine_line|#define VERIFY_WRITE    1
multiline_comment|/*&n; * The fs value determines whether argument validity checking should be&n; * performed or not.  If get_fs() == USER_DS, checking is performed, with&n; * get_fs() == KERNEL_DS, checking is bypassed.&n; *&n; * For historical reasons, these macros are grossly misnamed.&n; */
DECL|macro|MAKE_MM_SEG
mdefine_line|#define MAKE_MM_SEG(a)  ((mm_segment_t) { (a) })
DECL|macro|KERNEL_DS
mdefine_line|#define KERNEL_DS       MAKE_MM_SEG(0)
DECL|macro|USER_DS
mdefine_line|#define USER_DS         MAKE_MM_SEG(1)
DECL|macro|get_ds
mdefine_line|#define get_ds()        (KERNEL_DS)
DECL|macro|get_fs
mdefine_line|#define get_fs()        (current-&gt;thread.mm_segment)
macro_line|#ifdef __s390x__
DECL|macro|set_fs
mdefine_line|#define set_fs(x) &bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long __pto;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;current-&gt;thread.mm_segment = (x);&t;&t;&t;&t;&bslash;&n;&t;__pto = current-&gt;thread.mm_segment.ar4 ?&t;&t;&t;&bslash;&n;&t;&t;S390_lowcore.user_asce : S390_lowcore.kernel_asce;&t;&bslash;&n;&t;asm volatile (&quot;lctlg 7,7,%0&quot; : : &quot;m&quot; (__pto) );&t;&t;&t;&bslash;&n;})
macro_line|#else
DECL|macro|set_fs
mdefine_line|#define set_fs(x) &bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long __pto;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;current-&gt;thread.mm_segment = (x);&t;&t;&t;&t;&bslash;&n;&t;__pto = current-&gt;thread.mm_segment.ar4 ?&t;&t;&t;&bslash;&n;&t;&t;S390_lowcore.user_asce : S390_lowcore.kernel_asce;&t;&bslash;&n;&t;asm volatile (&quot;lctl  7,7,%0&quot; : : &quot;m&quot; (__pto) );&t;&t;&t;&bslash;&n;})
macro_line|#endif
DECL|macro|segment_eq
mdefine_line|#define segment_eq(a,b) ((a).ar4 == (b).ar4)
DECL|macro|__access_ok
mdefine_line|#define __access_ok(addr,size) (1)
DECL|macro|access_ok
mdefine_line|#define access_ok(type,addr,size) __access_ok(addr,size)
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
macro_line|#ifndef __s390x__
DECL|macro|__uaccess_fixup
mdefine_line|#define __uaccess_fixup &bslash;&n;&t;&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;&t;&bslash;&n;&t;&quot;2: lhi    %0,%4&bslash;n&quot;&t;&t;&bslash;&n;&t;&quot;   bras   1,3f&bslash;n&quot;&t;&t;&bslash;&n;&t;&quot;   .long  1b&bslash;n&quot;&t;&t;&bslash;&n;&t;&quot;3: l      1,0(1)&bslash;n&quot;&t;&t;&bslash;&n;&t;&quot;   br     1&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&quot;.previous&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;&t;&bslash;&n;&t;&quot;   .align 4&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&quot;   .long  0b,2b&bslash;n&quot;&t;&t;&bslash;&n;&t;&quot;.previous&quot;
DECL|macro|__uaccess_clobber
mdefine_line|#define __uaccess_clobber &quot;cc&quot;, &quot;1&quot;
macro_line|#else /* __s390x__ */
DECL|macro|__uaccess_fixup
mdefine_line|#define __uaccess_fixup &bslash;&n;&t;&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;&t;&bslash;&n;&t;&quot;2: lghi   %0,%4&bslash;n&quot;&t;&t;&bslash;&n;&t;&quot;   jg     1b&bslash;n&quot;&t;&t;&bslash;&n;&t;&quot;.previous&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;&t;&bslash;&n;&t;&quot;   .align 8&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&quot;   .quad  0b,2b&bslash;n&quot;&t;&t;&bslash;&n;&t;&quot;.previous&quot;
DECL|macro|__uaccess_clobber
mdefine_line|#define __uaccess_clobber &quot;cc&quot;
macro_line|#endif /* __s390x__ */
multiline_comment|/*&n; * These are the main single-value transfer routines.  They automatically&n; * use the right size if we just have the right pointer type.&n; */
macro_line|#if __GNUC__ &gt; 3 || (__GNUC__ == 3 &amp;&amp; __GNUC_MINOR__ &gt; 2)
DECL|macro|__put_user_asm
mdefine_line|#define __put_user_asm(x, ptr, err) &bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;err = 0;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;asm volatile(&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;0: mvcs  0(%1,%2),%3,%0&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;1:&bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__uaccess_fixup&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;+&amp;d&quot; (err)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;d&quot; (sizeof(*(ptr))), &quot;a&quot; (ptr), &quot;Q&quot; (x),&t;&bslash;&n;&t;&t;  &quot;K&quot; (-EFAULT)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: __uaccess_clobber );&t;&t;&t;&t;&bslash;&n;})
macro_line|#else
DECL|macro|__put_user_asm
mdefine_line|#define __put_user_asm(x, ptr, err) &bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;err = 0;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;asm volatile(&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;0: mvcs  0(%1,%2),0(%3),%0&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;1:&bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__uaccess_fixup&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;+&amp;d&quot; (err)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;d&quot; (sizeof(*(ptr))), &quot;a&quot; (ptr), &quot;a&quot; (&amp;(x)),&t;&bslash;&n;&t;&t;  &quot;K&quot; (-EFAULT), &quot;m&quot; (x)&t;&t;&t;&bslash;&n;&t;&t;: __uaccess_clobber );&t;&t;&t;&t;&bslash;&n;})
macro_line|#endif
macro_line|#ifndef __CHECKER__
DECL|macro|__put_user
mdefine_line|#define __put_user(x, ptr) &bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__typeof__(*(ptr)) __x = (x);&t;&t;&t;&t;&bslash;&n;&t;int __pu_err;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;switch (sizeof (*(ptr))) {&t;&t;&t;&t;&bslash;&n;&t;case 1:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;case 2:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;case 4:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;case 8:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__put_user_asm(__x, ptr, __pu_err);&t;&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;default:&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__put_user_bad();&t;&t;&t;&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;&t; }&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__pu_err;&t;&t;&t;&t;&t;&t;&bslash;&n;})
macro_line|#else
DECL|macro|__put_user
mdefine_line|#define __put_user(x, ptr)&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&bslash;&n;&t;void __user *p;&t;&t;&t;&t;&bslash;&n;&t;p = (ptr);&t;&t;&t;&t;&bslash;&n;&t;0;&t;&t;&t;&t;&t;&bslash;&n;})
macro_line|#endif
DECL|macro|put_user
mdefine_line|#define put_user(x, ptr)&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;might_sleep();&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__put_user(x, ptr);&t;&t;&t;&t;&t;&bslash;&n;})
r_extern
r_int
id|__put_user_bad
c_func
(paren
r_void
)paren
id|__attribute__
c_func
(paren
(paren
id|noreturn
)paren
)paren
suffix:semicolon
macro_line|#if __GNUC__ &gt; 3 || (__GNUC__ == 3 &amp;&amp; __GNUC_MINOR__ &gt; 2)
DECL|macro|__get_user_asm
mdefine_line|#define __get_user_asm(x, ptr, err) &bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;err = 0;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;asm volatile (&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;0: mvcp  %O1(%2,%R1),0(%3),%0&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&quot;1:&bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__uaccess_fixup&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;+&amp;d&quot; (err), &quot;=Q&quot; (x)&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;d&quot; (sizeof(*(ptr))), &quot;a&quot; (ptr),&t;&t;&bslash;&n;&t;&t;  &quot;K&quot; (-EFAULT)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: __uaccess_clobber );&t;&t;&t;&t;&bslash;&n;})
macro_line|#else
DECL|macro|__get_user_asm
mdefine_line|#define __get_user_asm(x, ptr, err) &bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;err = 0;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;asm volatile (&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;0: mvcp  0(%2,%5),0(%3),%0&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;1:&bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__uaccess_fixup&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;+&amp;d&quot; (err), &quot;=m&quot; (x)&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;d&quot; (sizeof(*(ptr))), &quot;a&quot; (ptr),&t;&t;&bslash;&n;&t;&t;  &quot;K&quot; (-EFAULT), &quot;a&quot; (&amp;(x))&t;&t;&t;&bslash;&n;&t;&t;: __uaccess_clobber );&t;&t;&t;&t;&bslash;&n;})
macro_line|#endif
macro_line|#ifndef __CHECKER__
DECL|macro|__get_user
mdefine_line|#define __get_user(x, ptr)&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__typeof__(*(ptr)) __x;&t;&t;&t;&t;&t;&bslash;&n;&t;int __gu_err;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;switch (sizeof(*(ptr))) {&t;&t;&t;&t;&bslash;&n;&t;case 1:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;case 2:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;case 4:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;case 8:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__get_user_asm(__x, ptr, __gu_err);&t;&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;default:&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__get_user_bad();&t;&t;&t;&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(x) = __x;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__gu_err;&t;&t;&t;&t;&t;&t;&bslash;&n;})
macro_line|#else
DECL|macro|__get_user
mdefine_line|#define __get_user(x, ptr)&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&bslash;&n;&t;void __user *p;&t;&t;&t;&t;&bslash;&n;&t;p = (ptr);&t;&t;&t;&t;&bslash;&n;&t;0;&t;&t;&t;&t;&t;&bslash;&n;})
macro_line|#endif
DECL|macro|get_user
mdefine_line|#define get_user(x, ptr)&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;might_sleep();&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__get_user(x, ptr);&t;&t;&t;&t;&t;&bslash;&n;})
r_extern
r_int
id|__get_user_bad
c_func
(paren
r_void
)paren
id|__attribute__
c_func
(paren
(paren
id|noreturn
)paren
)paren
suffix:semicolon
DECL|macro|__put_user_unaligned
mdefine_line|#define __put_user_unaligned __put_user
DECL|macro|__get_user_unaligned
mdefine_line|#define __get_user_unaligned __get_user
r_extern
r_int
id|__copy_to_user_asm
c_func
(paren
r_const
r_void
op_star
id|from
comma
r_int
id|n
comma
r_void
id|__user
op_star
id|to
)paren
suffix:semicolon
multiline_comment|/**&n; * __copy_to_user: - Copy a block of data into user space, with less checking.&n; * @to:   Destination address, in user space.&n; * @from: Source address, in kernel space.&n; * @n:    Number of bytes to copy.&n; *&n; * Context: User context only.  This function may sleep.&n; *&n; * Copy data from kernel space to user space.  Caller must check&n; * the specified block with access_ok() before calling this function.&n; *&n; * Returns number of bytes that could not be copied.&n; * On success, this will be zero.&n; */
r_static
r_inline
r_int
r_int
DECL|function|__copy_to_user
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
id|__copy_to_user_asm
c_func
(paren
id|from
comma
id|n
comma
id|to
)paren
suffix:semicolon
)brace
DECL|macro|__copy_to_user_inatomic
mdefine_line|#define __copy_to_user_inatomic __copy_to_user
DECL|macro|__copy_from_user_inatomic
mdefine_line|#define __copy_from_user_inatomic __copy_from_user
multiline_comment|/**&n; * copy_to_user: - Copy a block of data into user space.&n; * @to:   Destination address, in user space.&n; * @from: Source address, in kernel space.&n; * @n:    Number of bytes to copy.&n; *&n; * Context: User context only.  This function may sleep.&n; *&n; * Copy data from kernel space to user space.&n; *&n; * Returns number of bytes that could not be copied.&n; * On success, this will be zero.&n; */
r_static
r_inline
r_int
r_int
DECL|function|copy_to_user
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
id|might_sleep
c_func
(paren
)paren
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
id|n
op_assign
id|__copy_to_user
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
id|__copy_from_user_asm
c_func
(paren
r_void
op_star
id|to
comma
r_int
id|n
comma
r_const
r_void
id|__user
op_star
id|from
)paren
suffix:semicolon
multiline_comment|/**&n; * __copy_from_user: - Copy a block of data from user space, with less checking.&n; * @to:   Destination address, in kernel space.&n; * @from: Source address, in user space.&n; * @n:    Number of bytes to copy.&n; *&n; * Context: User context only.  This function may sleep.&n; *&n; * Copy data from user space to kernel space.  Caller must check&n; * the specified block with access_ok() before calling this function.&n; *&n; * Returns number of bytes that could not be copied.&n; * On success, this will be zero.&n; *&n; * If some data could not be copied, this function will pad the copied&n; * data to the requested size using zero bytes.&n; */
r_static
r_inline
r_int
r_int
DECL|function|__copy_from_user
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
id|__copy_from_user_asm
c_func
(paren
id|to
comma
id|n
comma
id|from
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * copy_from_user: - Copy a block of data from user space.&n; * @to:   Destination address, in kernel space.&n; * @from: Source address, in user space.&n; * @n:    Number of bytes to copy.&n; *&n; * Context: User context only.  This function may sleep.&n; *&n; * Copy data from user space to kernel space.&n; *&n; * Returns number of bytes that could not be copied.&n; * On success, this will be zero.&n; *&n; * If some data could not be copied, this function will pad the copied&n; * data to the requested size using zero bytes.&n; */
r_static
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
id|__user
op_star
id|from
comma
r_int
r_int
id|n
)paren
(brace
id|might_sleep
c_func
(paren
)paren
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
id|n
op_assign
id|__copy_from_user
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
id|n
suffix:semicolon
)brace
r_extern
r_int
r_int
id|__copy_in_user_asm
c_func
(paren
r_const
r_void
id|__user
op_star
id|from
comma
r_int
id|n
comma
r_void
id|__user
op_star
id|to
)paren
suffix:semicolon
r_static
r_inline
r_int
r_int
DECL|function|__copy_in_user
id|__copy_in_user
c_func
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
r_return
id|__copy_in_user_asm
c_func
(paren
id|from
comma
id|n
comma
id|to
)paren
suffix:semicolon
)brace
r_static
r_inline
r_int
r_int
DECL|function|copy_in_user
id|copy_in_user
c_func
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
id|might_sleep
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|__access_ok
c_func
(paren
id|from
comma
id|n
)paren
op_logical_and
id|__access_ok
c_func
(paren
id|to
comma
id|n
)paren
)paren
id|n
op_assign
id|__copy_in_user_asm
c_func
(paren
id|from
comma
id|n
comma
id|to
)paren
suffix:semicolon
r_return
id|n
suffix:semicolon
)brace
multiline_comment|/*&n; * Copy a null terminated string from userspace.&n; */
r_extern
r_int
id|__strncpy_from_user_asm
c_func
(paren
r_int
id|count
comma
r_char
op_star
id|dst
comma
r_const
r_char
id|__user
op_star
id|src
)paren
suffix:semicolon
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
id|might_sleep
c_func
(paren
)paren
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
id|__strncpy_from_user_asm
c_func
(paren
id|count
comma
id|dst
comma
id|src
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
r_extern
r_int
id|__strnlen_user_asm
c_func
(paren
r_int
id|count
comma
r_const
r_char
id|__user
op_star
id|src
)paren
suffix:semicolon
r_static
r_inline
r_int
r_int
DECL|function|strnlen_user
id|strnlen_user
c_func
(paren
r_const
r_char
id|__user
op_star
id|src
comma
r_int
r_int
id|n
)paren
(brace
id|might_sleep
c_func
(paren
)paren
suffix:semicolon
r_return
id|__strnlen_user_asm
c_func
(paren
id|n
comma
id|src
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * strlen_user: - Get the size of a string in user space.&n; * @str: The string to measure.&n; *&n; * Context: User context only.  This function may sleep.&n; *&n; * Get the size of a NUL-terminated string in user space.&n; *&n; * Returns the size of the string INCLUDING the terminating NUL.&n; * On exception, returns 0.&n; *&n; * If there is a limit on the length of a valid string, you may wish to&n; * consider using strnlen_user() instead.&n; */
DECL|macro|strlen_user
mdefine_line|#define strlen_user(str) strnlen_user(str, ~0UL)
multiline_comment|/*&n; * Zero Userspace&n; */
r_extern
r_int
id|__clear_user_asm
c_func
(paren
r_void
id|__user
op_star
id|to
comma
r_int
id|n
)paren
suffix:semicolon
r_static
r_inline
r_int
r_int
DECL|function|__clear_user
id|__clear_user
c_func
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
id|__clear_user_asm
c_func
(paren
id|to
comma
id|n
)paren
suffix:semicolon
)brace
r_static
r_inline
r_int
r_int
DECL|function|clear_user
id|clear_user
c_func
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
id|might_sleep
c_func
(paren
)paren
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
id|n
op_assign
id|__clear_user_asm
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
macro_line|#endif /* __S390_UACCESS_H */
eof
