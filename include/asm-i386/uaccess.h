macro_line|#ifndef __i386_UACCESS_H
DECL|macro|__i386_UACCESS_H
mdefine_line|#define __i386_UACCESS_H
multiline_comment|/*&n; * User space memory access functions&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/thread_info.h&gt;
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
mdefine_line|#define KERNEL_DS&t;MAKE_MM_SEG(0xFFFFFFFF)
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
multiline_comment|/*&n; * movsl can be slow when source and dest are not both 8-byte aligned&n; */
macro_line|#ifdef CONFIG_X86_INTEL_USERCOPY
DECL|struct|movsl_mask
r_extern
r_struct
id|movsl_mask
(brace
DECL|member|mask
r_int
id|mask
suffix:semicolon
)brace
id|____cacheline_aligned_in_smp
id|movsl_mask
suffix:semicolon
macro_line|#endif
r_int
id|__verify_write
c_func
(paren
r_const
r_void
op_star
comma
r_int
r_int
)paren
suffix:semicolon
DECL|macro|__addr_ok
mdefine_line|#define __addr_ok(addr) ((unsigned long)(addr) &lt; (current_thread_info()-&gt;addr_limit.seg))
multiline_comment|/*&n; * Test whether a block of memory is a valid user space address.&n; * Returns 0 if the range is valid, nonzero otherwise.&n; *&n; * This is equivalent to the following test:&n; * (u33)addr + (u33)size &gt;= (u33)current-&gt;addr_limit.seg&n; *&n; * This needs 33-bit arithmetic. We have a carry...&n; */
DECL|macro|__range_ok
mdefine_line|#define __range_ok(addr,size) ({ &bslash;&n;&t;unsigned long flag,sum; &bslash;&n;&t;asm(&quot;addl %3,%1 ; sbbl %0,%0; cmpl %1,%4; sbbl $0,%0&quot; &bslash;&n;&t;&t;:&quot;=&amp;r&quot; (flag), &quot;=r&quot; (sum) &bslash;&n;&t;&t;:&quot;1&quot; (addr),&quot;g&quot; ((int)(size)),&quot;g&quot; (current_thread_info()-&gt;addr_limit.seg)); &bslash;&n;&t;flag; })
macro_line|#ifdef CONFIG_X86_WP_WORKS_OK
multiline_comment|/**&n; * access_ok: - Checks if a user space pointer is valid&n; * @type: Type of access: %VERIFY_READ or %VERIFY_WRITE.  Note that&n; *        %VERIFY_WRITE is a superset of %VERIFY_READ - if it is safe&n; *        to write to a block, it is always safe to read from it.&n; * @addr: User space pointer to start of block to check&n; * @size: Size of block to check&n; *&n; * Context: User context only.  This function may sleep.&n; *&n; * Checks if a pointer to a block of memory in user space is valid.&n; *&n; * Returns true (nonzero) if the memory block may be valid, false (zero)&n; * if it is definitely invalid.&n; *&n; * Note that, depending on architecture, this function probably just&n; * checks that the pointer is in the user space range - after calling&n; * this function, memory access functions may still return -EFAULT.&n; */
DECL|macro|access_ok
mdefine_line|#define access_ok(type,addr,size) (__range_ok(addr,size) == 0)
macro_line|#else
DECL|macro|access_ok
mdefine_line|#define access_ok(type,addr,size) ( (__range_ok(addr,size) == 0) &amp;&amp; &bslash;&n;&t;&t;&t; ((type) == VERIFY_READ || boot_cpu_data.wp_works_ok || &bslash;&n;&t;&t;&t;  __verify_write((void *)(addr),(size))))
macro_line|#endif
multiline_comment|/**&n; * verify_area: - Obsolete, use access_ok()&n; * @type: Type of access: %VERIFY_READ or %VERIFY_WRITE&n; * @addr: User space pointer to start of block to check&n; * @size: Size of block to check&n; *&n; * Context: User context only.  This function may sleep.&n; *&n; * This function has been replaced by access_ok().&n; *&n; * Checks if a pointer to a block of memory in user space is valid.&n; *&n; * Returns zero if the memory block may be valid, -EFAULT&n; * if it is definitely invalid.&n; *&n; * See access_ok() for more details.&n; */
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
r_extern
r_int
id|fixup_exception
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
multiline_comment|/*&n; * These are the main single-value transfer routines.  They automatically&n; * use the right size if we just have the right pointer type.&n; *&n; * This gets kind of ugly. We want to return _two_ values in &quot;get_user()&quot;&n; * and yet we don&squot;t want to do any pointers, because that is too much&n; * of a performance impact. Thus we have a few rather ugly macros here,&n; * and hide all the ugliness from the user.&n; *&n; * The &quot;__xxx&quot; versions of the user access functions are versions that&n; * do not verify the address space, that must have been done previously&n; * with a separate &quot;access_ok()&quot; call (this is used when we do multiple&n; * accesses to the same area of user memory).&n; */
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
DECL|macro|__get_user_x
mdefine_line|#define __get_user_x(size,ret,x,ptr) &bslash;&n;&t;__asm__ __volatile__(&quot;call __get_user_&quot; #size &bslash;&n;&t;&t;:&quot;=a&quot; (ret),&quot;=d&quot; (x) &bslash;&n;&t;&t;:&quot;0&quot; (ptr))
multiline_comment|/* Careful: we have to cast the result to the type of the pointer for sign reasons */
multiline_comment|/**&n; * get_user: - Get a simple variable from user space.&n; * @x:   Variable to store result.&n; * @ptr: Source address, in user space.&n; *&n; * Context: User context only.  This function may sleep.&n; *&n; * This macro copies a single simple variable from user space to kernel&n; * space.  It supports simple types like char and int, but not larger&n; * data types like structures or arrays.&n; *&n; * @ptr must have pointer-to-simple-variable type, and the result of&n; * dereferencing @ptr must be assignable to @x without a cast.&n; *&n; * Returns zero on success, or -EFAULT on error.&n; * On error, the variable @x is set to zero.&n; */
DECL|macro|get_user
mdefine_line|#define get_user(x,ptr)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;int __ret_gu,__val_gu;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;switch(sizeof (*(ptr))) {&t;&t;&t;&t;&t;&bslash;&n;&t;case 1:  __get_user_x(1,__ret_gu,__val_gu,ptr); break;&t;&t;&bslash;&n;&t;case 2:  __get_user_x(2,__ret_gu,__val_gu,ptr); break;&t;&t;&bslash;&n;&t;case 4:  __get_user_x(4,__ret_gu,__val_gu,ptr); break;&t;&t;&bslash;&n;&t;default: __get_user_x(X,__ret_gu,__val_gu,ptr); break;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(x) = (__typeof__(*(ptr)))__val_gu;&t;&t;&t;&t;&bslash;&n;&t;__ret_gu;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
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
multiline_comment|/**&n; * put_user: - Write a simple value into user space.&n; * @x:   Value to copy to user space.&n; * @ptr: Destination address, in user space.&n; *&n; * Context: User context only.  This function may sleep.&n; *&n; * This macro copies a single simple value from kernel space to user&n; * space.  It supports simple types like char and int, but not larger&n; * data types like structures or arrays.&n; *&n; * @ptr must have pointer-to-simple-variable type, and @x must be assignable&n; * to the result of dereferencing @ptr.&n; *&n; * Returns zero on success, or -EFAULT on error.&n; */
DECL|macro|put_user
mdefine_line|#define put_user(x,ptr)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  __put_user_check((__typeof__(*(ptr)))(x),(ptr),sizeof(*(ptr)))
multiline_comment|/**&n; * __get_user: - Get a simple variable from user space, with less checking.&n; * @x:   Variable to store result.&n; * @ptr: Source address, in user space.&n; *&n; * Context: User context only.  This function may sleep.&n; *&n; * This macro copies a single simple variable from user space to kernel&n; * space.  It supports simple types like char and int, but not larger&n; * data types like structures or arrays.&n; *&n; * @ptr must have pointer-to-simple-variable type, and the result of&n; * dereferencing @ptr must be assignable to @x without a cast.&n; *&n; * Caller must check the pointer with access_ok() before calling this&n; * function.&n; *&n; * Returns zero on success, or -EFAULT on error.&n; * On error, the variable @x is set to zero.&n; */
DECL|macro|__get_user
mdefine_line|#define __get_user(x,ptr) &bslash;&n;  __get_user_nocheck((x),(ptr),sizeof(*(ptr)))
multiline_comment|/**&n; * __put_user: - Write a simple value into user space, with less checking.&n; * @x:   Value to copy to user space.&n; * @ptr: Destination address, in user space.&n; *&n; * Context: User context only.  This function may sleep.&n; *&n; * This macro copies a single simple value from kernel space to user&n; * space.  It supports simple types like char and int, but not larger&n; * data types like structures or arrays.&n; *&n; * @ptr must have pointer-to-simple-variable type, and @x must be assignable&n; * to the result of dereferencing @ptr.&n; *&n; * Caller must check the pointer with access_ok() before calling this&n; * function.&n; *&n; * Returns zero on success, or -EFAULT on error.&n; */
DECL|macro|__put_user
mdefine_line|#define __put_user(x,ptr) &bslash;&n;  __put_user_nocheck((__typeof__(*(ptr)))(x),(ptr),sizeof(*(ptr)))
DECL|macro|__put_user_nocheck
mdefine_line|#define __put_user_nocheck(x,ptr,size)&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;long __pu_err;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__put_user_size((x),(ptr),(size),__pu_err,-EFAULT);&t;&bslash;&n;&t;__pu_err;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|__put_user_check
mdefine_line|#define __put_user_check(x,ptr,size)&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;long __pu_err = -EFAULT;&t;&t;&t;&t;&t;&bslash;&n;&t;__typeof__(*(ptr)) *__pu_addr = (ptr);&t;&t;&t;&t;&bslash;&n;&t;if (access_ok(VERIFY_WRITE,__pu_addr,size))&t;&t;&t;&bslash;&n;&t;&t;__put_user_size((x),__pu_addr,(size),__pu_err,-EFAULT);&t;&bslash;&n;&t;__pu_err;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})&t;&t;&t;&t;&t;&t;&t;
DECL|macro|__put_user_u64
mdefine_line|#define __put_user_u64(x, addr, err)&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;1:&t;movl %%eax,0(%2)&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;2:&t;movl %%edx,4(%2)&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;3:&bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;4:&t;movl %3,%0&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;jmp 3b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.previous&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.align 4&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.long 1b,4b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.long 2b,4b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.previous&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=r&quot;(err)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;A&quot; (x), &quot;r&quot; (addr), &quot;i&quot;(-EFAULT), &quot;0&quot;(err))
DECL|macro|__put_user_size
mdefine_line|#define __put_user_size(x,ptr,size,retval,errret)&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;retval = 0;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;switch (size) {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;case 1: __put_user_asm(x,ptr,retval,&quot;b&quot;,&quot;b&quot;,&quot;iq&quot;,errret);break;&t;&bslash;&n;&t;case 2: __put_user_asm(x,ptr,retval,&quot;w&quot;,&quot;w&quot;,&quot;ir&quot;,errret);break; &bslash;&n;&t;case 4: __put_user_asm(x,ptr,retval,&quot;l&quot;,&quot;&quot;,&quot;ir&quot;,errret); break;&t;&bslash;&n;&t;case 8: __put_user_u64((__typeof__(*ptr))(x),ptr,retval); break;&bslash;&n;&t;  default: __put_user_bad();&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
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
mdefine_line|#define __put_user_asm(x, addr, err, itype, rtype, ltype, errret)&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;1:&t;mov&quot;itype&quot; %&quot;rtype&quot;1,%2&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;2:&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;3:&t;movl %3,%0&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;jmp 2b&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.previous&bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.align 4&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.long 1b,3b&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.previous&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=r&quot;(err)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: ltype (x), &quot;m&quot;(__m(addr)), &quot;i&quot;(errret), &quot;0&quot;(err))
DECL|macro|__get_user_nocheck
mdefine_line|#define __get_user_nocheck(x,ptr,size)&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;long __gu_err, __gu_val;&t;&t;&t;&t;&bslash;&n;&t;__get_user_size(__gu_val,(ptr),(size),__gu_err,-EFAULT);&bslash;&n;&t;(x) = (__typeof__(*(ptr)))__gu_val;&t;&t;&t;&bslash;&n;&t;__gu_err;&t;&t;&t;&t;&t;&t;&bslash;&n;})
r_extern
r_int
id|__get_user_bad
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|__get_user_size
mdefine_line|#define __get_user_size(x,ptr,size,retval,errret)&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;retval = 0;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;switch (size) {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;case 1: __get_user_asm(x,ptr,retval,&quot;b&quot;,&quot;b&quot;,&quot;=q&quot;,errret);break;&t;&bslash;&n;&t;case 2: __get_user_asm(x,ptr,retval,&quot;w&quot;,&quot;w&quot;,&quot;=r&quot;,errret);break;&t;&bslash;&n;&t;case 4: __get_user_asm(x,ptr,retval,&quot;l&quot;,&quot;&quot;,&quot;=r&quot;,errret);break;&t;&bslash;&n;&t;default: (x) = __get_user_bad();&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|__get_user_asm
mdefine_line|#define __get_user_asm(x, addr, err, itype, rtype, ltype, errret)&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;1:&t;mov&quot;itype&quot; %2,%&quot;rtype&quot;1&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;2:&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;3:&t;movl %3,%0&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;xor&quot;itype&quot; %&quot;rtype&quot;1,%&quot;rtype&quot;1&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&quot;&t;jmp 2b&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.previous&bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.align 4&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.long 1b,3b&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.previous&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=r&quot;(err), ltype (x)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;m&quot;(__m(addr)), &quot;i&quot;(errret), &quot;0&quot;(err))
r_int
r_int
id|__copy_to_user_ll
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
suffix:semicolon
r_int
r_int
id|__copy_from_user_ll
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
suffix:semicolon
multiline_comment|/*&n; * Here we special-case 1, 2 and 4-byte copy_*_user invocations.  On a fault&n; * we return the initial request size (1, 2 or 4), as copy_*_user should do.&n; * If a store crosses a page boundary and gets a fault, the x86 will not write&n; * anything, so this is accurate.&n; */
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
)brace
)brace
r_return
id|__copy_to_user_ll
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
)brace
)brace
r_return
id|__copy_from_user_ll
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
r_return
id|n
suffix:semicolon
)brace
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
multiline_comment|/**&n; * strlen_user: - Get the size of a string in user space.&n; * @str: The string to measure.&n; *&n; * Context: User context only.  This function may sleep.&n; *&n; * Get the size of a NUL-terminated string in user space.&n; *&n; * Returns the size of the string INCLUDING the terminating NUL.&n; * On exception, returns 0.&n; *&n; * If there is a limit on the length of a valid string, you may wish to&n; * consider using strnlen_user() instead.&n; */
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
macro_line|#endif /* __i386_UACCESS_H */
eof
