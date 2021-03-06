macro_line|#ifndef _PPC64_UACCESS_H
DECL|macro|_PPC64_UACCESS_H
mdefine_line|#define _PPC64_UACCESS_H
multiline_comment|/* &n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
DECL|macro|VERIFY_READ
mdefine_line|#define VERIFY_READ&t;0
DECL|macro|VERIFY_WRITE
mdefine_line|#define VERIFY_WRITE&t;1
multiline_comment|/*&n; * The fs value determines whether argument validity checking should be&n; * performed or not.  If get_fs() == USER_DS, checking is performed, with&n; * get_fs() == KERNEL_DS, checking is bypassed.&n; *&n; * For historical reasons, these macros are grossly misnamed.&n; */
DECL|macro|MAKE_MM_SEG
mdefine_line|#define MAKE_MM_SEG(s)  ((mm_segment_t) { (s) })
DECL|macro|KERNEL_DS
mdefine_line|#define KERNEL_DS&t;MAKE_MM_SEG(0UL)
DECL|macro|USER_DS
mdefine_line|#define USER_DS&t;&t;MAKE_MM_SEG(0xf000000000000000UL)
DECL|macro|get_ds
mdefine_line|#define get_ds()&t;(KERNEL_DS)
DECL|macro|get_fs
mdefine_line|#define get_fs()&t;(current-&gt;thread.fs)
DECL|macro|set_fs
mdefine_line|#define set_fs(val)&t;(current-&gt;thread.fs = (val))
DECL|macro|segment_eq
mdefine_line|#define segment_eq(a,b)&t;((a).seg == (b).seg)
multiline_comment|/*&n; * Use the alpha trick for checking ranges:&n; *&n; * Is a address valid? This does a straightforward calculation rather&n; * than tests.&n; *&n; * Address valid if:&n; *  - &quot;addr&quot; doesn&squot;t have any high-bits set&n; *  - AND &quot;size&quot; doesn&squot;t have any high-bits set&n; *  - OR we are in kernel mode.&n; *&n; * We dont have to check for high bits in (addr+size) because the first&n; * two checks force the maximum result to be below the start of the&n; * kernel region.&n; */
DECL|macro|__access_ok
mdefine_line|#define __access_ok(addr,size,segment) &bslash;&n;&t;(((segment).seg &amp; (addr | size )) == 0)
DECL|macro|access_ok
mdefine_line|#define access_ok(type,addr,size) &bslash;&n;&t;__access_ok(((__force unsigned long)(addr)),(size),get_fs())
multiline_comment|/* this function will go away soon - use access_ok() instead */
DECL|function|verify_area
r_static
r_inline
r_int
id|__deprecated
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
multiline_comment|/*&n; * These are the main single-value transfer routines.  They automatically&n; * use the right size if we just have the right pointer type.&n; *&n; * This gets kind of ugly. We want to return _two_ values in &quot;get_user()&quot;&n; * and yet we don&squot;t want to do any pointers, because that is too much&n; * of a performance impact. Thus we have a few rather ugly macros here,&n; * and hide all the ugliness from the user.&n; *&n; * The &quot;__xxx&quot; versions of the user access functions are versions that&n; * do not verify the address space, that must have been done previously&n; * with a separate &quot;access_ok()&quot; call (this is used when we do multiple&n; * accesses to the same area of user memory).&n; *&n; * As we use the same address space for kernel and user data on the&n; * PowerPC, we can just do these as direct assignments.  (Of course, the&n; * exception handling means that it&squot;s no longer &quot;just&quot;...)&n; */
DECL|macro|get_user
mdefine_line|#define get_user(x,ptr) &bslash;&n;  __get_user_check((x),(ptr),sizeof(*(ptr)))
DECL|macro|put_user
mdefine_line|#define put_user(x,ptr) &bslash;&n;  __put_user_check((__typeof__(*(ptr)))(x),(ptr),sizeof(*(ptr)))
DECL|macro|__get_user
mdefine_line|#define __get_user(x,ptr) &bslash;&n;  __get_user_nocheck((x),(ptr),sizeof(*(ptr)))
DECL|macro|__put_user
mdefine_line|#define __put_user(x,ptr) &bslash;&n;  __put_user_nocheck((__typeof__(*(ptr)))(x),(ptr),sizeof(*(ptr)))
DECL|macro|__get_user_unaligned
mdefine_line|#define __get_user_unaligned __get_user
DECL|macro|__put_user_unaligned
mdefine_line|#define __put_user_unaligned __put_user
r_extern
r_int
id|__put_user_bad
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|__put_user_nocheck
mdefine_line|#define __put_user_nocheck(x,ptr,size)&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;long __pu_err;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;might_sleep();&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__chk_user_ptr(ptr);&t;&t;&t;&t;&t;&bslash;&n;&t;__put_user_size((x),(ptr),(size),__pu_err,-EFAULT);&t;&bslash;&n;&t;__pu_err;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|__put_user_check
mdefine_line|#define __put_user_check(x,ptr,size)&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;long __pu_err = -EFAULT;&t;&t;&t;&t;&t;&bslash;&n;&t;void __user *__pu_addr = (ptr);&t;&t;&t;&t;&t;&bslash;&n;&t;might_sleep();&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (access_ok(VERIFY_WRITE,__pu_addr,size))&t;&t;&t;&bslash;&n;&t;&t;__put_user_size((x),__pu_addr,(size),__pu_err,-EFAULT);&t;&bslash;&n;&t;__pu_err;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|__put_user_size
mdefine_line|#define __put_user_size(x,ptr,size,retval,errret)&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;retval = 0;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;switch (size) {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;  case 1: __put_user_asm(x,ptr,retval,&quot;stb&quot;,errret); break;&t;&bslash;&n;&t;  case 2: __put_user_asm(x,ptr,retval,&quot;sth&quot;,errret); break;&t;&bslash;&n;&t;  case 4: __put_user_asm(x,ptr,retval,&quot;stw&quot;,errret); break;&t;&bslash;&n;&t;  case 8: __put_user_asm(x,ptr,retval,&quot;std&quot;,errret); break; &t;&bslash;&n;&t;  default: __put_user_bad();&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
multiline_comment|/*&n; * We don&squot;t tell gcc that we are accessing memory, but this is OK&n; * because we do not write to any memory gcc knows about, so there&n; * are no aliasing issues.&n; */
DECL|macro|__put_user_asm
mdefine_line|#define __put_user_asm(x, addr, err, op, errret)&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;1:&t;&quot;op&quot; %1,0(%2)  &t;# put_user&bslash;n&quot; &t; &t;&bslash;&n;&t;&t;&quot;2:&bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;3:&t;li %0,%3&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;b 2b&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.previous&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.align 3&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.llong 1b,3b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.previous&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=r&quot;(err)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;r&quot;(x), &quot;b&quot;(addr), &quot;i&quot;(errret), &quot;0&quot;(err))
DECL|macro|__get_user_nocheck
mdefine_line|#define __get_user_nocheck(x,ptr,size)&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;long __gu_err, __gu_val;&t;&t;&t;&t;&bslash;&n;&t;might_sleep();&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__get_user_size(__gu_val,(ptr),(size),__gu_err,-EFAULT);&bslash;&n;&t;(x) = (__typeof__(*(ptr)))__gu_val;&t;&t;&t;&bslash;&n;&t;__gu_err;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|__get_user_check
mdefine_line|#define __get_user_check(x,ptr,size)&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;long __gu_err = -EFAULT, __gu_val = 0;&t;&t;&t;&t;&bslash;&n;&t;const __typeof__(*(ptr)) __user *__gu_addr = (ptr);&t;&t;&bslash;&n;&t;might_sleep();&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (access_ok(VERIFY_READ,__gu_addr,size))&t;&t;&t;&bslash;&n;&t;&t;__get_user_size(__gu_val,__gu_addr,(size),__gu_err,-EFAULT);&bslash;&n;&t;(x) = (__typeof__(*(ptr)))__gu_val;&t;&t;&t;&t;&bslash;&n;&t;__gu_err;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
r_extern
r_int
id|__get_user_bad
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|__get_user_size
mdefine_line|#define __get_user_size(x,ptr,size,retval,errret)&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;retval = 0;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__chk_user_ptr(ptr);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;switch (size) {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;  case 1: __get_user_asm(x,ptr,retval,&quot;lbz&quot;,errret); break;&t;&bslash;&n;&t;  case 2: __get_user_asm(x,ptr,retval,&quot;lhz&quot;,errret); break;&t;&bslash;&n;&t;  case 4: __get_user_asm(x,ptr,retval,&quot;lwz&quot;,errret); break;&t;&bslash;&n;&t;  case 8: __get_user_asm(x,ptr,retval,&quot;ld&quot;,errret);  break;&t;&bslash;&n;&t;  default: (x) = __get_user_bad();&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|__get_user_asm
mdefine_line|#define __get_user_asm(x, addr, err, op, errret)&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;1:&t;&quot;op&quot; %1,0(%2)&t;# get_user&bslash;n&quot;  &t;&bslash;&n;&t;&t;&quot;2:&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&quot;3:&t;li %0,%3&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;li %1,0&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;b 2b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.previous&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&quot;&t;.align 3&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.llong 1b,3b&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;.previous&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=r&quot;(err), &quot;=r&quot;(x)&t;&t;&t;&bslash;&n;&t;&t;: &quot;b&quot;(addr), &quot;i&quot;(errret), &quot;0&quot;(err))
multiline_comment|/* more complex routines */
r_extern
r_int
r_int
id|__copy_tofrom_user
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
id|size
)paren
suffix:semicolon
r_static
r_inline
r_int
r_int
DECL|function|__copy_from_user_inatomic
id|__copy_from_user_inatomic
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
r_if
c_cond
(paren
id|__builtin_constant_p
c_func
(paren
id|n
)paren
)paren
(brace
r_int
r_int
id|ret
suffix:semicolon
r_switch
c_cond
(paren
id|n
)paren
(brace
r_case
l_int|1
suffix:colon
id|__get_user_size
c_func
(paren
op_star
(paren
id|u8
op_star
)paren
id|to
comma
id|from
comma
l_int|1
comma
id|ret
comma
l_int|1
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
r_case
l_int|2
suffix:colon
id|__get_user_size
c_func
(paren
op_star
(paren
id|u16
op_star
)paren
id|to
comma
id|from
comma
l_int|2
comma
id|ret
comma
l_int|2
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
r_case
l_int|4
suffix:colon
id|__get_user_size
c_func
(paren
op_star
(paren
id|u32
op_star
)paren
id|to
comma
id|from
comma
l_int|4
comma
id|ret
comma
l_int|4
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
r_case
l_int|8
suffix:colon
id|__get_user_size
c_func
(paren
op_star
(paren
id|u64
op_star
)paren
id|to
comma
id|from
comma
l_int|8
comma
id|ret
comma
l_int|8
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
)brace
r_return
id|__copy_tofrom_user
c_func
(paren
(paren
id|__force
r_void
id|__user
op_star
)paren
id|to
comma
id|from
comma
id|n
)paren
suffix:semicolon
)brace
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
id|might_sleep
c_func
(paren
)paren
suffix:semicolon
r_return
id|__copy_from_user_inatomic
c_func
(paren
id|to
comma
id|from
comma
id|n
)paren
suffix:semicolon
)brace
r_static
r_inline
r_int
r_int
DECL|function|__copy_to_user_inatomic
id|__copy_to_user_inatomic
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
r_if
c_cond
(paren
id|__builtin_constant_p
c_func
(paren
id|n
)paren
)paren
(brace
r_int
r_int
id|ret
suffix:semicolon
r_switch
c_cond
(paren
id|n
)paren
(brace
r_case
l_int|1
suffix:colon
id|__put_user_size
c_func
(paren
op_star
(paren
id|u8
op_star
)paren
id|from
comma
(paren
id|u8
id|__user
op_star
)paren
id|to
comma
l_int|1
comma
id|ret
comma
l_int|1
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
r_case
l_int|2
suffix:colon
id|__put_user_size
c_func
(paren
op_star
(paren
id|u16
op_star
)paren
id|from
comma
(paren
id|u16
id|__user
op_star
)paren
id|to
comma
l_int|2
comma
id|ret
comma
l_int|2
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
r_case
l_int|4
suffix:colon
id|__put_user_size
c_func
(paren
op_star
(paren
id|u32
op_star
)paren
id|from
comma
(paren
id|u32
id|__user
op_star
)paren
id|to
comma
l_int|4
comma
id|ret
comma
l_int|4
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
r_case
l_int|8
suffix:colon
id|__put_user_size
c_func
(paren
op_star
(paren
id|u64
op_star
)paren
id|from
comma
(paren
id|u64
id|__user
op_star
)paren
id|to
comma
l_int|8
comma
id|ret
comma
l_int|8
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
)brace
r_return
id|__copy_tofrom_user
c_func
(paren
id|to
comma
(paren
id|__force
r_const
r_void
id|__user
op_star
)paren
id|from
comma
id|n
)paren
suffix:semicolon
)brace
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
id|might_sleep
c_func
(paren
)paren
suffix:semicolon
r_return
id|__copy_to_user_inatomic
c_func
(paren
id|to
comma
id|from
comma
id|n
)paren
suffix:semicolon
)brace
DECL|macro|__copy_in_user
mdefine_line|#define __copy_in_user(to, from, size) &bslash;&n;&t;__copy_tofrom_user((to), (from), (size))
r_extern
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
id|__user
op_star
id|from
comma
r_int
r_int
id|n
)paren
suffix:semicolon
r_extern
r_int
r_int
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
suffix:semicolon
r_extern
r_int
r_int
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
suffix:semicolon
r_extern
r_int
r_int
id|__clear_user
c_func
(paren
r_void
id|__user
op_star
id|addr
comma
r_int
r_int
id|size
)paren
suffix:semicolon
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
id|addr
comma
r_int
r_int
id|size
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
id|likely
c_func
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
)paren
id|size
op_assign
id|__clear_user
c_func
(paren
id|addr
comma
id|size
)paren
suffix:semicolon
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
id|__user
op_star
id|src
comma
r_int
id|count
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
id|might_sleep
c_func
(paren
)paren
suffix:semicolon
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
id|src
comma
l_int|1
)paren
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
id|__user
op_star
id|str
comma
r_int
id|len
)paren
suffix:semicolon
multiline_comment|/*&n; * Returns the length of the string at str (including the null byte),&n; * or 0 if we hit a page we can&squot;t access,&n; * or something &gt; len if we didn&squot;t find a null byte.&n; */
DECL|function|strnlen_user
r_static
r_inline
r_int
id|strnlen_user
c_func
(paren
r_const
r_char
id|__user
op_star
id|str
comma
r_int
id|len
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
id|likely
c_func
(paren
id|access_ok
c_func
(paren
id|VERIFY_READ
comma
id|str
comma
l_int|1
)paren
)paren
)paren
r_return
id|__strnlen_user
c_func
(paren
id|str
comma
id|len
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|macro|strlen_user
mdefine_line|#define strlen_user(str)&t;strnlen_user((str), 0x7ffffffe)
macro_line|#endif  /* __ASSEMBLY__ */
macro_line|#endif&t;/* _PPC64_UACCESS_H */
eof
