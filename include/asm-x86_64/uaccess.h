macro_line|#ifndef __X86_64_UACCESS_H
DECL|macro|__X86_64_UACCESS_H
mdefine_line|#define __X86_64_UACCESS_H
multiline_comment|/*&n; * User space memory access functions&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/prefetch.h&gt;
macro_line|#include &lt;asm/page.h&gt;
DECL|macro|VERIFY_READ
mdefine_line|#define VERIFY_READ 0
DECL|macro|VERIFY_WRITE
mdefine_line|#define VERIFY_WRITE 1
multiline_comment|/*&n; * The fs value determines whether argument validity checking should be&n; * performed or not.  If get_fs() == USER_DS, checking is performed, with&n; * get_fs() == KERNEL_DS, checking is bypassed.&n; *&n; * For historical reasons, these macros are grossly misnamed.&n; */
DECL|macro|MAKE_MM_SEG
mdefine_line|#define MAKE_MM_SEG(s)&t;((mm_segment_t) { (s) })
DECL|macro|KERNEL_DS
mdefine_line|#define KERNEL_DS&t;MAKE_MM_SEG(0xFFFFFFFFFFFFFFFF)
DECL|macro|USER_DS
mdefine_line|#define USER_DS&t;&t;MAKE_MM_SEG(PAGE_OFFSET)
DECL|macro|get_ds
mdefine_line|#define get_ds()&t;(KERNEL_DS)
DECL|macro|get_fs
mdefine_line|#define get_fs()&t;(current_thread_info()-&gt;addr_limit)
DECL|macro|set_fs
mdefine_line|#define set_fs(x)&t;(current_thread_info()-&gt;addr_limit = (x))
DECL|macro|segment_eq
mdefine_line|#define segment_eq(a,b)&t;((a).seg == (b).seg)
DECL|macro|__addr_ok
mdefine_line|#define __addr_ok(addr) (!((unsigned long)(addr) &amp; (current_thread_info()-&gt;addr_limit.seg)))
multiline_comment|/*&n; * Uhhuh, this needs 65-bit arithmetic. We have a carry..&n; */
DECL|macro|__range_not_ok
mdefine_line|#define __range_not_ok(addr,size) ({ &bslash;&n;&t;unsigned long flag,sum; &bslash;&n;&t;asm(&quot;# range_ok&bslash;n&bslash;r&quot; &bslash;&n;&t;&t;&quot;addq %3,%1 ; sbbq %0,%0 ; cmpq %1,%4 ; sbbq $0,%0&quot;  &bslash;&n;&t;&t;:&quot;=&amp;r&quot; (flag), &quot;=r&quot; (sum) &bslash;&n;&t;&t;:&quot;1&quot; (addr),&quot;g&quot; ((long)(size)),&quot;g&quot; (current_thread_info()-&gt;addr_limit.seg)); &bslash;&n;&t;flag; })
DECL|macro|access_ok
mdefine_line|#define access_ok(type,addr,size) (__range_not_ok(addr,size) == 0)
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
multiline_comment|/*&n; * These are the main single-value transfer routines.  They automatically&n; * use the right size if we just have the right pointer type.&n; *&n; * This gets kind of ugly. We want to return _two_ values in &quot;get_user()&quot;&n; * and yet we don&squot;t want to do any pointers, because that is too much&n; * of a performance impact. Thus we have a few rather ugly macros here,&n; * and hide all the uglyness from the user.&n; *&n; * The &quot;__xxx&quot; versions of the user access functions are versions that&n; * do not verify the address space, that must have been done previously&n; * with a separate &quot;access_ok()&quot; call (this is used when we do multiple&n; * accesses to the same area of user memory).&n; */
r_extern
r_void
id|__get_user_1
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__get_user_2
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__get_user_4
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__get_user_8
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|__get_user_x
mdefine_line|#define __get_user_x(size,ret,x,ptr) &bslash;&n;&t;__asm__ __volatile__(&quot;call __get_user_&quot; #size &bslash;&n;&t;&t;:&quot;=a&quot; (ret),&quot;=d&quot; (x) &bslash;&n;&t;&t;:&quot;0&quot; (ptr) &bslash;&n;&t;&t;:&quot;rbx&quot;)
multiline_comment|/* Careful: we have to cast the result to the type of the pointer for sign reasons */
DECL|macro|get_user
mdefine_line|#define get_user(x,ptr)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;long __ret_gu,__val_gu;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;switch(sizeof (*(ptr))) {&t;&t;&t;&t;&t;&bslash;&n;&t;case 1:  __get_user_x(1,__ret_gu,__val_gu,ptr); break;&t;&t;&bslash;&n;&t;case 2:  __get_user_x(2,__ret_gu,__val_gu,ptr); break;&t;&t;&bslash;&n;&t;case 4:  __get_user_x(4,__ret_gu,__val_gu,ptr); break;&t;&t;&bslash;&n;&t;case 8:  __get_user_x(8,__ret_gu,__val_gu,ptr); break;&t;&t;&bslash;&n;&t;default: __get_user_bad(); break;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(x) = (__typeof__(*(ptr)))__val_gu;&t;&t;&t;&t;&bslash;&n;&t;__ret_gu;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
r_extern
r_void
id|__put_user_1
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__put_user_2
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__put_user_4
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__put_user_8
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__put_user_bad
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|__put_user_x
mdefine_line|#define __put_user_x(size,ret,x,ptr)&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&quot;call __put_user_&quot; #size&t;&t;&t;&bslash;&n;&t;&t;:&quot;=a&quot; (ret)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;:&quot;0&quot; (ptr),&quot;d&quot; (x)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;:&quot;rbx&quot;)
DECL|macro|put_user
mdefine_line|#define put_user(x,ptr)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  __put_user_check((__typeof__(*(ptr)))(x),(ptr),sizeof(*(ptr)))
DECL|macro|__get_user
mdefine_line|#define __get_user(x,ptr) &bslash;&n;  __get_user_nocheck((x),(ptr),sizeof(*(ptr)))
DECL|macro|__put_user
mdefine_line|#define __put_user(x,ptr) &bslash;&n;  __put_user_nocheck((__typeof__(*(ptr)))(x),(ptr),sizeof(*(ptr)))
DECL|macro|__put_user_nocheck
mdefine_line|#define __put_user_nocheck(x,ptr,size)&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;long __pu_err;&t;&t;&t;&t;&t;&bslash;&n;&t;__put_user_size((x),(ptr),(size),__pu_err);&t;&bslash;&n;&t;__pu_err;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|__put_user_check
mdefine_line|#define __put_user_check(x,ptr,size)&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;long __pu_err = -EFAULT;&t;&t;&t;&bslash;&n;&t;__typeof__(*(ptr)) *__pu_addr = (ptr);&t;&t;&bslash;&n;&t;if (access_ok(VERIFY_WRITE,__pu_addr,size))&t;&bslash;&n;&t;&t;__put_user_size((x),__pu_addr,(size),__pu_err);&t;&bslash;&n;&t;__pu_err;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|__put_user_size
mdefine_line|#define __put_user_size(x,ptr,size,retval)&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;retval = 0;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;switch (size) {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;  case 1: __put_user_asm(x,ptr,retval,&quot;b&quot;,&quot;b&quot;,&quot;iq&quot;); break;&t;&bslash;&n;&t;  case 2: __put_user_asm(x,ptr,retval,&quot;w&quot;,&quot;w&quot;,&quot;ir&quot;); break;&t;&bslash;&n;&t;  case 4: __put_user_asm(x,ptr,retval,&quot;l&quot;,&quot;k&quot;,&quot;ir&quot;); break;&t;&bslash;&n;&t;  case 8: __put_user_asm(x,ptr,retval,&quot;q&quot;,&quot;&quot;,&quot;ir&quot;); break;&t;&bslash;&n;&t;  default: __put_user_bad();&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
multiline_comment|/* FIXME: this hack is definitely wrong -AK */
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
multiline_comment|/*&n; * Tell gcc we read from memory instead of writing: this is because&n; * we do not write to any memory gcc knows about, so there are no&n; * aliasing issues.&n; */
DECL|macro|__put_user_asm
mdefine_line|#define __put_user_asm(x, addr, err, itype, rtype, ltype)&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;1:&t;mov&quot;itype&quot; %&quot;rtype&quot;1,%2&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&quot;2:&bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;3:&t;movq %3,%0&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;jmp 2b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.previous&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.align 8&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.quad 1b,3b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.previous&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=r&quot;(err)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: ltype (x), &quot;m&quot;(__m(addr)), &quot;i&quot;(-EFAULT), &quot;0&quot;(err))
DECL|macro|__get_user_nocheck
mdefine_line|#define __get_user_nocheck(x,ptr,size)&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;long __gu_err, __gu_val;&t;&t;&t;&t;&bslash;&n;&t;__get_user_size(__gu_val,(ptr),(size),__gu_err);&t;&bslash;&n;&t;(x) = (__typeof__(*(ptr)))__gu_val;&t;&t;&t;&bslash;&n;&t;__gu_err;&t;&t;&t;&t;&t;&t;&bslash;&n;})
r_extern
r_int
id|__get_user_bad
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|__get_user_size
mdefine_line|#define __get_user_size(x,ptr,size,retval)&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;retval = 0;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;switch (size) {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;  case 1: __get_user_asm(x,ptr,retval,&quot;b&quot;,&quot;b&quot;,&quot;=q&quot;); break;&t;&bslash;&n;&t;  case 2: __get_user_asm(x,ptr,retval,&quot;w&quot;,&quot;w&quot;,&quot;=r&quot;); break;&t;&bslash;&n;&t;  case 4: __get_user_asm(x,ptr,retval,&quot;l&quot;,&quot;k&quot;,&quot;=r&quot;); break;&t;&bslash;&n;&t;  case 8: __get_user_asm(x,ptr,retval,&quot;q&quot;,&quot;&quot;,&quot;=r&quot;); break;&t;&bslash;&n;&t;  default: (x) = __get_user_bad();&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|__get_user_asm
mdefine_line|#define __get_user_asm(x, addr, err, itype, rtype, ltype)&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;1:&t;mov&quot;itype&quot; %2,%&quot;rtype&quot;1&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&quot;2:&bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;3:&t;mov %3,%0&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;xor&quot;itype&quot; %&quot;rtype&quot;1,%&quot;rtype&quot;1&bslash;n&quot;&t;&bslash;&n;&t;&t;&quot;&t;jmp 2b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.previous&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.align 8&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.quad 1b,3b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.previous&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=r&quot;(err), ltype (x)&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;m&quot;(__m(addr)), &quot;i&quot;(-EFAULT), &quot;0&quot;(err))
multiline_comment|/*&n; * Copy To/From Userspace&n; * &n; * This relies on an optimized common worker function.&n; * &n; * Could do special inline versions for small constant copies, but avoid this&n; * for now. It&squot;s not clear it is worth it. &n; */
r_extern
r_int
r_int
id|copy_user_generic
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
id|len
)paren
suffix:semicolon
r_extern
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
id|len
)paren
suffix:semicolon
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
op_star
id|from
comma
r_int
id|len
)paren
suffix:semicolon
DECL|macro|__copy_to_user
mdefine_line|#define __copy_to_user copy_user_generic
DECL|macro|__copy_from_user
mdefine_line|#define __copy_from_user copy_user_generic
r_int
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
suffix:semicolon
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
DECL|macro|strlen_user
mdefine_line|#define strlen_user(str) strnlen_user(str, ~0UL &gt;&gt; 1)
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
id|n
)paren
suffix:semicolon
r_int
r_int
id|clear_user
c_func
(paren
r_void
op_star
id|mem
comma
r_int
r_int
id|len
)paren
suffix:semicolon
r_int
r_int
id|__clear_user
c_func
(paren
r_void
op_star
id|mem
comma
r_int
r_int
id|len
)paren
suffix:semicolon
macro_line|#endif /* __X86_64_UACCESS_H */
eof
