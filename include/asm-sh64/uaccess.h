macro_line|#ifndef __ASM_SH64_UACCESS_H
DECL|macro|__ASM_SH64_UACCESS_H
mdefine_line|#define __ASM_SH64_UACCESS_H
multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * include/asm-sh64/uaccess.h&n; *&n; * Copyright (C) 2000, 2001  Paolo Alberelli&n; * Copyright (C) 2003, 2004  Paul Mundt&n; *&n; * User space memory access functions&n; *&n; * Copyright (C) 1999  Niibe Yutaka&n; *&n; *  Based on:&n; *     MIPS implementation version 1.15 by&n; *              Copyright (C) 1996, 1997, 1998 by Ralf Baechle&n; *     and i386 version.&n; *&n; */
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
mdefine_line|#define get_fs()        (current_thread_info()-&gt;addr_limit)
DECL|macro|set_fs
mdefine_line|#define set_fs(x)       (current_thread_info()-&gt;addr_limit=(x))
DECL|macro|segment_eq
mdefine_line|#define segment_eq(a,b)&t;((a).seg == (b).seg)
DECL|macro|__addr_ok
mdefine_line|#define __addr_ok(addr) ((unsigned long)(addr) &lt; (current_thread_info()-&gt;addr_limit.seg))
multiline_comment|/*&n; * Uhhuh, this needs 33-bit arithmetic. We have a carry..&n; *&n; * sum := addr + size;  carry? --&gt; flag = true;&n; * if (sum &gt;= addr_limit) flag = true;&n; */
DECL|macro|__range_ok
mdefine_line|#define __range_ok(addr,size) (((unsigned long) (addr) + (size) &lt; (current_thread_info()-&gt;addr_limit.seg)) ? 0 : 1)
DECL|macro|access_ok
mdefine_line|#define access_ok(type,addr,size) (__range_ok(addr,size) == 0)
DECL|macro|__access_ok
mdefine_line|#define __access_ok(addr,size) (__range_ok(addr,size) == 0)
multiline_comment|/* this function will go away soon - use access_ok() instead */
DECL|function|verify_area
r_extern
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
multiline_comment|/*&n; * Uh, these should become the main single-value transfer routines ...&n; * They automatically use the right size if we just have the right&n; * pointer type ...&n; *&n; * As MIPS uses the same address space for kernel and user data, we&n; * can just do these as direct assignments.&n; *&n; * Careful to not&n; * (a) re-use the arguments for side effects (sizeof is ok)&n; * (b) require any knowledge of processes at this stage&n; */
DECL|macro|put_user
mdefine_line|#define put_user(x,ptr)&t;__put_user_check((x),(ptr),sizeof(*(ptr)))
DECL|macro|get_user
mdefine_line|#define get_user(x,ptr) __get_user_check((x),(ptr),sizeof(*(ptr)))
multiline_comment|/*&n; * The &quot;__xxx&quot; versions do not do address space checking, useful when&n; * doing multiple accesses to the same area (the user has to do the&n; * checks by hand with &quot;access_ok()&quot;)&n; */
DECL|macro|__put_user
mdefine_line|#define __put_user(x,ptr) __put_user_nocheck((x),(ptr),sizeof(*(ptr)))
DECL|macro|__get_user
mdefine_line|#define __get_user(x,ptr) __get_user_nocheck((x),(ptr),sizeof(*(ptr)))
multiline_comment|/*&n; * The &quot;xxx_ret&quot; versions return constant specified in third argument, if&n; * something bad happens. These macros can be optimized for the&n; * case of just returning from the function xxx_ret is used.&n; */
DECL|macro|put_user_ret
mdefine_line|#define put_user_ret(x,ptr,ret) ({ &bslash;&n;if (put_user(x,ptr)) return ret; })
DECL|macro|get_user_ret
mdefine_line|#define get_user_ret(x,ptr,ret) ({ &bslash;&n;if (get_user(x,ptr)) return ret; })
DECL|macro|__put_user_ret
mdefine_line|#define __put_user_ret(x,ptr,ret) ({ &bslash;&n;if (__put_user(x,ptr)) return ret; })
DECL|macro|__get_user_ret
mdefine_line|#define __get_user_ret(x,ptr,ret) ({ &bslash;&n;if (__get_user(x,ptr)) return ret; })
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
DECL|macro|__get_user_size
mdefine_line|#define __get_user_size(x,ptr,size,retval)&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;retval = 0;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;switch (size) {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;case 1:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;retval = __get_user_asm_b(x, ptr);&t;&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;case 2:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;retval = __get_user_asm_w(x, ptr);&t;&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;case 4:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;retval = __get_user_asm_l(x, ptr);&t;&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;case 8:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;retval = __get_user_asm_q(x, ptr);&t;&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;default:&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__get_user_unknown();&t;&t;&t;&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|__get_user_nocheck
mdefine_line|#define __get_user_nocheck(x,ptr,size)&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;long __gu_addr = (long)(ptr);&t;&t;&t;&t;&bslash;&n;&t;long __gu_err;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__typeof(*(ptr)) __gu_val;&t;&t;&t;&t;&bslash;&n;&t;__asm__ (&quot;&quot;:&quot;=r&quot; (__gu_val));&t;&t;&t;&t;&bslash;&n;&t;__asm__ (&quot;&quot;:&quot;=r&quot; (__gu_err));&t;&t;&t;&t;&bslash;&n;&t;__get_user_size((void *)&amp;__gu_val, __gu_addr, (size), __gu_err); &bslash;&n;&t;(x) = (__typeof__(*(ptr))) __gu_val;&t;&t;&t;&bslash;&n;&t;__gu_err;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|__get_user_check
mdefine_line|#define __get_user_check(x,ptr,size)&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;long __gu_addr = (long)(ptr);&t;&t;&t;&t;&bslash;&n;&t;long __gu_err = -EFAULT;&t;&t;&t;&t;&bslash;&n;&t;__typeof(*(ptr)) __gu_val;&t;&t;&t;&t;&bslash;&n;&t;__asm__ (&quot;&quot;:&quot;=r&quot; (__gu_val));&t;&t;&t;&t;&bslash;&n;&t;__asm__ (&quot;&quot;:&quot;=r&quot; (__gu_err));&t;&t;&t;&t;&bslash;&n;&t;if (__access_ok(__gu_addr, (size)))&t;&t;&t;&bslash;&n;&t;&t;__get_user_size((void *)&amp;__gu_val, __gu_addr, (size), __gu_err); &bslash;&n;&t;(x) = (__typeof__(*(ptr))) __gu_val;&t;&t;&t;&bslash;&n;&t;__gu_err;&t;&t;&t;&t;&t;&t;&bslash;&n;})
r_extern
r_int
id|__get_user_asm_b
c_func
(paren
r_void
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|__get_user_asm_w
c_func
(paren
r_void
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|__get_user_asm_l
c_func
(paren
r_void
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|__get_user_asm_q
c_func
(paren
r_void
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|__get_user_unknown
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|__put_user_size
mdefine_line|#define __put_user_size(x,ptr,size,retval)&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;retval = 0;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;switch (size) {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;case 1:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;retval = __put_user_asm_b(x, ptr);&t;&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;case 2:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;retval = __put_user_asm_w(x, ptr);&t;&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;case 4:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;retval = __put_user_asm_l(x, ptr);&t;&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;case 8:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;retval = __put_user_asm_q(x, ptr);&t;&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;default:&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__put_user_unknown();&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|__put_user_nocheck
mdefine_line|#define __put_user_nocheck(x,ptr,size)&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;long __pu_err;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__typeof__(*(ptr)) __pu_val = (x);&t;&t;&t;&bslash;&n;&t;__put_user_size((void *)&amp;__pu_val, (long)(ptr), (size), __pu_err); &bslash;&n;&t;__pu_err;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|__put_user_check
mdefine_line|#define __put_user_check(x,ptr,size)&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;long __pu_err = -EFAULT;&t;&t;&t;&t;&bslash;&n;&t;long __pu_addr = (long)(ptr);&t;&t;&t;&t;&bslash;&n;&t;__typeof__(*(ptr)) __pu_val = (x);&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (__access_ok(__pu_addr, (size)))&t;&t;&t;&bslash;&n;&t;&t;__put_user_size((void *)&amp;__pu_val, __pu_addr, (size), __pu_err);&bslash;&n;&t;__pu_err;&t;&t;&t;&t;&t;&t;&bslash;&n;})
r_extern
r_int
id|__put_user_asm_b
c_func
(paren
r_void
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|__put_user_asm_w
c_func
(paren
r_void
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|__put_user_asm_l
c_func
(paren
r_void
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|__put_user_asm_q
c_func
(paren
r_void
op_star
comma
r_int
)paren
suffix:semicolon
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
r_extern
id|__kernel_size_t
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
suffix:semicolon
DECL|macro|copy_to_user
mdefine_line|#define copy_to_user(to,from,n) ({ &bslash;&n;void *__copy_to = (void *) (to); &bslash;&n;__kernel_size_t __copy_size = (__kernel_size_t) (n); &bslash;&n;__kernel_size_t __copy_res; &bslash;&n;if(__copy_size &amp;&amp; __access_ok((unsigned long)__copy_to, __copy_size)) { &bslash;&n;__copy_res = __copy_user(__copy_to, (void *) (from), __copy_size); &bslash;&n;} else __copy_res = __copy_size; &bslash;&n;__copy_res; })
DECL|macro|copy_to_user_ret
mdefine_line|#define copy_to_user_ret(to,from,n,retval) ({ &bslash;&n;if (copy_to_user(to,from,n)) &bslash;&n;&t;return retval; &bslash;&n;})
DECL|macro|__copy_to_user
mdefine_line|#define __copy_to_user(to,from,n)&t;&t;&bslash;&n;&t;__copy_user((void *)(to),&t;&t;&bslash;&n;&t;&t;    (void *)(from), n)
DECL|macro|__copy_to_user_ret
mdefine_line|#define __copy_to_user_ret(to,from,n,retval) ({ &bslash;&n;if (__copy_to_user(to,from,n)) &bslash;&n;&t;return retval; &bslash;&n;})
DECL|macro|copy_from_user
mdefine_line|#define copy_from_user(to,from,n) ({ &bslash;&n;void *__copy_to = (void *) (to); &bslash;&n;void *__copy_from = (void *) (from); &bslash;&n;__kernel_size_t __copy_size = (__kernel_size_t) (n); &bslash;&n;__kernel_size_t __copy_res; &bslash;&n;if(__copy_size &amp;&amp; __access_ok((unsigned long)__copy_from, __copy_size)) { &bslash;&n;__copy_res = __copy_user(__copy_to, __copy_from, __copy_size); &bslash;&n;} else __copy_res = __copy_size; &bslash;&n;__copy_res; })
DECL|macro|copy_from_user_ret
mdefine_line|#define copy_from_user_ret(to,from,n,retval) ({ &bslash;&n;if (copy_from_user(to,from,n)) &bslash;&n;&t;return retval; &bslash;&n;})
DECL|macro|__copy_from_user
mdefine_line|#define __copy_from_user(to,from,n)&t;&t;&bslash;&n;&t;__copy_user((void *)(to),&t;&t;&bslash;&n;&t;&t;    (void *)(from), n)
DECL|macro|__copy_from_user_ret
mdefine_line|#define __copy_from_user_ret(to,from,n,retval) ({ &bslash;&n;if (__copy_from_user(to,from,n)) &bslash;&n;&t;return retval; &bslash;&n;})
DECL|macro|__copy_to_user_inatomic
mdefine_line|#define __copy_to_user_inatomic __copy_to_user
DECL|macro|__copy_from_user_inatomic
mdefine_line|#define __copy_from_user_inatomic __copy_from_user
multiline_comment|/* XXX: Not sure it works well..&n;   should be such that: 4byte clear and the rest. */
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
r_extern
r_int
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
suffix:semicolon
DECL|macro|strncpy_from_user
mdefine_line|#define strncpy_from_user(dest,src,count) ({ &bslash;&n;unsigned long __sfu_src = (unsigned long) (src); &bslash;&n;int __sfu_count = (int) (count); &bslash;&n;long __sfu_res = -EFAULT; &bslash;&n;if(__access_ok(__sfu_src, __sfu_count)) { &bslash;&n;__sfu_res = __strncpy_from_user((unsigned long) (dest), __sfu_src, __sfu_count); &bslash;&n;} __sfu_res; })
DECL|macro|strlen_user
mdefine_line|#define strlen_user(str) strnlen_user(str, ~0UL &gt;&gt; 1)
multiline_comment|/*&n; * Return the size of a string (including the ending 0!)&n; */
r_extern
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
suffix:semicolon
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
DECL|macro|ARCH_HAS_SEARCH_EXTABLE
mdefine_line|#define ARCH_HAS_SEARCH_EXTABLE
multiline_comment|/* If gcc inlines memset, it will use st.q instructions.  Therefore, we need&n;   kmalloc allocations to be 8-byte aligned.  Without this, the alignment&n;   becomes BYTE_PER_WORD i.e. only 4 (since sizeof(long)==sizeof(void*)==4 on&n;   sh64 at the moment). */
DECL|macro|ARCH_KMALLOC_MINALIGN
mdefine_line|#define ARCH_KMALLOC_MINALIGN 8
multiline_comment|/*&n; * We want 8-byte alignment for the slab caches as well, otherwise we have&n; * the same BYTES_PER_WORD (sizeof(void *)) min align in kmem_cache_create().&n; */
DECL|macro|ARCH_SLAB_MINALIGN
mdefine_line|#define ARCH_SLAB_MINALIGN 8
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
macro_line|#endif /* __ASM_SH64_UACCESS_H */
eof
