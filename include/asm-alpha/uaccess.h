macro_line|#ifndef __ALPHA_UACCESS_H
DECL|macro|__ALPHA_UACCESS_H
mdefine_line|#define __ALPHA_UACCESS_H
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
multiline_comment|/*&n; * The fs value determines whether argument validity checking should be&n; * performed or not.  If get_fs() == USER_DS, checking is performed, with&n; * get_fs() == KERNEL_DS, checking is bypassed.&n; *&n; * Or at least it did once upon a time.  Nowadays it is a mask that&n; * defines which bits of the address space are off limits.  This is a&n; * wee bit faster than the above.&n; *&n; * For historical reasons, these macros are grossly misnamed.&n; */
DECL|macro|KERNEL_DS
mdefine_line|#define KERNEL_DS&t;((mm_segment_t) { 0UL })
DECL|macro|USER_DS
mdefine_line|#define USER_DS&t;&t;((mm_segment_t) { -0x40000000000UL })
DECL|macro|VERIFY_READ
mdefine_line|#define VERIFY_READ&t;0
DECL|macro|VERIFY_WRITE
mdefine_line|#define VERIFY_WRITE&t;1
DECL|macro|get_fs
mdefine_line|#define get_fs()  (current_thread_info()-&gt;addr_limit)
DECL|macro|get_ds
mdefine_line|#define get_ds()  (KERNEL_DS)
DECL|macro|set_fs
mdefine_line|#define set_fs(x) (current_thread_info()-&gt;addr_limit = (x))
DECL|macro|segment_eq
mdefine_line|#define segment_eq(a,b)&t;((a).seg == (b).seg)
multiline_comment|/*&n; * Is a address valid? This does a straightforward calculation rather&n; * than tests.&n; *&n; * Address valid if:&n; *  - &quot;addr&quot; doesn&squot;t have any high-bits set&n; *  - AND &quot;size&quot; doesn&squot;t have any high-bits set&n; *  - AND &quot;addr+size&quot; doesn&squot;t have any high-bits set&n; *  - OR we are in kernel mode.&n; */
DECL|macro|__access_ok
mdefine_line|#define __access_ok(addr,size,segment) &bslash;&n;&t;(((segment).seg &amp; (addr | size | (addr+size))) == 0)
DECL|macro|access_ok
mdefine_line|#define access_ok(type,addr,size) &bslash;&n;&t;__access_ok(((unsigned long)(addr)),(size),get_fs())
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
multiline_comment|/*&n; * These are the main single-value transfer routines.  They automatically&n; * use the right size if we just have the right pointer type.&n; *&n; * As the alpha uses the same address space for kernel and user&n; * data, we can just do these as direct assignments.  (Of course, the&n; * exception handling means that it&squot;s no longer &quot;just&quot;...)&n; *&n; * Careful to not&n; * (a) re-use the arguments for side effects (sizeof/typeof is ok)&n; * (b) require any knowledge of processes at this stage&n; */
DECL|macro|put_user
mdefine_line|#define put_user(x,ptr) &bslash;&n;  __put_user_check((__typeof__(*(ptr)))(x),(ptr),sizeof(*(ptr)),get_fs())
DECL|macro|get_user
mdefine_line|#define get_user(x,ptr) &bslash;&n;  __get_user_check((x),(ptr),sizeof(*(ptr)),get_fs())
multiline_comment|/*&n; * The &quot;__xxx&quot; versions do not do address space checking, useful when&n; * doing multiple accesses to the same area (the programmer has to do the&n; * checks by hand with &quot;access_ok()&quot;)&n; */
DECL|macro|__put_user
mdefine_line|#define __put_user(x,ptr) &bslash;&n;  __put_user_nocheck((__typeof__(*(ptr)))(x),(ptr),sizeof(*(ptr)))
DECL|macro|__get_user
mdefine_line|#define __get_user(x,ptr) &bslash;&n;  __get_user_nocheck((x),(ptr),sizeof(*(ptr)))
multiline_comment|/*&n; * The &quot;lda %1, 2b-1b(%0)&quot; bits are magic to get the assembler to&n; * encode the bits we need for resolving the exception.  See the&n; * more extensive comments with fixup_inline_exception below for&n; * more information.&n; */
r_extern
r_void
id|__get_user_unknown
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|__get_user_nocheck
mdefine_line|#define __get_user_nocheck(x,ptr,size)&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;long __gu_err = 0, __gu_val;&t;&t;&t;&t;&bslash;&n;&t;switch (size) {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;  case 1: __get_user_8(ptr); break;&t;&t;&t;&bslash;&n;&t;  case 2: __get_user_16(ptr); break;&t;&t;&t;&bslash;&n;&t;  case 4: __get_user_32(ptr); break;&t;&t;&t;&bslash;&n;&t;  case 8: __get_user_64(ptr); break;&t;&t;&t;&bslash;&n;&t;  default: __get_user_unknown(); break;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(x) = (__typeof__(*(ptr))) __gu_val;&t;&t;&t;&bslash;&n;&t;__gu_err;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|__get_user_check
mdefine_line|#define __get_user_check(x,ptr,size,segment)&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;long __gu_err = -EFAULT, __gu_val = 0;&t;&t;&t;&bslash;&n;&t;const __typeof__(*(ptr)) *__gu_addr = (ptr);&t;&t;&bslash;&n;&t;if (__access_ok((long)__gu_addr,size,segment)) {&t;&bslash;&n;&t;&t;__gu_err = 0;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;switch (size) {&t;&t;&t;&t;&t;&bslash;&n;&t;&t;  case 1: __get_user_8(__gu_addr); break;&t;&bslash;&n;&t;&t;  case 2: __get_user_16(__gu_addr); break;&t;&bslash;&n;&t;&t;  case 4: __get_user_32(__gu_addr); break;&t;&bslash;&n;&t;&t;  case 8: __get_user_64(__gu_addr); break;&t;&bslash;&n;&t;&t;  default: __get_user_unknown(); break;&t;&t;&bslash;&n;&t;&t;}&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(x) = (__typeof__(*(ptr))) __gu_val;&t;&t;&t;&bslash;&n;&t;__gu_err;&t;&t;&t;&t;&t;&t;&bslash;&n;})
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
DECL|macro|__get_user_64
mdefine_line|#define __get_user_64(addr)&t;&t;&t;&t;&bslash;&n;&t;__asm__(&quot;1: ldq %0,%2&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&quot;2:&bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&quot;&t;.long 1b - .&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;lda %0, 2b-1b(%1)&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&quot;.previous&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=r&quot;(__gu_val), &quot;=r&quot;(__gu_err)&t;&bslash;&n;&t;&t;: &quot;m&quot;(__m(addr)), &quot;1&quot;(__gu_err))
DECL|macro|__get_user_32
mdefine_line|#define __get_user_32(addr)&t;&t;&t;&t;&bslash;&n;&t;__asm__(&quot;1: ldl %0,%2&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&quot;2:&bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&quot;&t;.long 1b - .&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;lda %0, 2b-1b(%1)&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&quot;.previous&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=r&quot;(__gu_val), &quot;=r&quot;(__gu_err)&t;&bslash;&n;&t;&t;: &quot;m&quot;(__m(addr)), &quot;1&quot;(__gu_err))
macro_line|#ifdef __alpha_bwx__
multiline_comment|/* Those lucky bastards with ev56 and later CPUs can do byte/word moves.  */
DECL|macro|__get_user_16
mdefine_line|#define __get_user_16(addr)&t;&t;&t;&t;&bslash;&n;&t;__asm__(&quot;1: ldwu %0,%2&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&quot;2:&bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&quot;&t;.long 1b - .&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;lda %0, 2b-1b(%1)&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&quot;.previous&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=r&quot;(__gu_val), &quot;=r&quot;(__gu_err)&t;&bslash;&n;&t;&t;: &quot;m&quot;(__m(addr)), &quot;1&quot;(__gu_err))
DECL|macro|__get_user_8
mdefine_line|#define __get_user_8(addr)&t;&t;&t;&t;&bslash;&n;&t;__asm__(&quot;1: ldbu %0,%2&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&quot;2:&bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&quot;&t;.long 1b - .&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;lda %0, 2b-1b(%1)&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&quot;.previous&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=r&quot;(__gu_val), &quot;=r&quot;(__gu_err)&t;&bslash;&n;&t;&t;: &quot;m&quot;(__m(addr)), &quot;1&quot;(__gu_err))
macro_line|#else
multiline_comment|/* Unfortunately, we can&squot;t get an unaligned access trap for the sub-word&n;   load, so we have to do a general unaligned operation.  */
DECL|macro|__get_user_16
mdefine_line|#define __get_user_16(addr)&t;&t;&t;&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;long __gu_tmp;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__(&quot;1: ldq_u %0,0(%3)&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;2:&t;ldq_u %1,1(%3)&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;extwl %0,%3,%0&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;extwh %1,%3,%1&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;or %0,%1,%0&bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;3:&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.long 1b - .&bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;lda %0, 3b-1b(%2)&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.long 2b - .&bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;lda %0, 3b-2b(%2)&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.previous&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=&amp;r&quot;(__gu_val), &quot;=&amp;r&quot;(__gu_tmp), &quot;=r&quot;(__gu_err)&t;&bslash;&n;&t;&t;: &quot;r&quot;(addr), &quot;2&quot;(__gu_err));&t;&t;&t;&t;&bslash;&n;}
DECL|macro|__get_user_8
mdefine_line|#define __get_user_8(addr)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__(&quot;1: ldq_u %0,0(%2)&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;extbl %0,%2,%0&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;2:&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.long 1b - .&bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;lda %0, 2b-1b(%1)&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.previous&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=&amp;r&quot;(__gu_val), &quot;=r&quot;(__gu_err)&t;&t;&t;&bslash;&n;&t;&t;: &quot;r&quot;(addr), &quot;1&quot;(__gu_err))
macro_line|#endif
r_extern
r_void
id|__put_user_unknown
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|__put_user_nocheck
mdefine_line|#define __put_user_nocheck(x,ptr,size)&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;long __pu_err = 0;&t;&t;&t;&t;&t;&bslash;&n;&t;switch (size) {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;  case 1: __put_user_8(x,ptr); break;&t;&t;&t;&bslash;&n;&t;  case 2: __put_user_16(x,ptr); break;&t;&t;&t;&bslash;&n;&t;  case 4: __put_user_32(x,ptr); break;&t;&t;&t;&bslash;&n;&t;  case 8: __put_user_64(x,ptr); break;&t;&t;&t;&bslash;&n;&t;  default: __put_user_unknown(); break;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__pu_err;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|__put_user_check
mdefine_line|#define __put_user_check(x,ptr,size,segment)&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;long __pu_err = -EFAULT;&t;&t;&t;&t;&bslash;&n;&t;__typeof__(*(ptr)) *__pu_addr = (ptr);&t;&t;&t;&bslash;&n;&t;if (__access_ok((long)__pu_addr,size,segment)) {&t;&bslash;&n;&t;&t;__pu_err = 0;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;switch (size) {&t;&t;&t;&t;&t;&bslash;&n;&t;&t;  case 1: __put_user_8(x,__pu_addr); break;&t;&bslash;&n;&t;&t;  case 2: __put_user_16(x,__pu_addr); break;&t;&bslash;&n;&t;&t;  case 4: __put_user_32(x,__pu_addr); break;&t;&bslash;&n;&t;&t;  case 8: __put_user_64(x,__pu_addr); break;&t;&bslash;&n;&t;&t;  default: __put_user_unknown(); break;&t;&t;&bslash;&n;&t;&t;}&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__pu_err;&t;&t;&t;&t;&t;&t;&bslash;&n;})
multiline_comment|/*&n; * The &quot;__put_user_xx()&quot; macros tell gcc they read from memory&n; * instead of writing: this is because they do not write to&n; * any memory gcc knows about, so there are no aliasing issues&n; */
DECL|macro|__put_user_64
mdefine_line|#define __put_user_64(x,addr)&t;&t;&t;&t;&t;&bslash;&n;__asm__ __volatile__(&quot;1: stq %r2,%1&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;2:&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.long 1b - .&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;lda $31,2b-1b(%0)&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;.previous&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=r&quot;(__pu_err)&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;m&quot; (__m(addr)), &quot;rJ&quot; (x), &quot;0&quot;(__pu_err))
DECL|macro|__put_user_32
mdefine_line|#define __put_user_32(x,addr)&t;&t;&t;&t;&t;&bslash;&n;__asm__ __volatile__(&quot;1: stl %r2,%1&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;2:&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.long 1b - .&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;lda $31,2b-1b(%0)&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;.previous&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=r&quot;(__pu_err)&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;m&quot;(__m(addr)), &quot;rJ&quot;(x), &quot;0&quot;(__pu_err))
macro_line|#ifdef __alpha_bwx__
multiline_comment|/* Those lucky bastards with ev56 and later CPUs can do byte/word moves.  */
DECL|macro|__put_user_16
mdefine_line|#define __put_user_16(x,addr)&t;&t;&t;&t;&t;&bslash;&n;__asm__ __volatile__(&quot;1: stw %r2,%1&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;2:&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.long 1b - .&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;lda $31,2b-1b(%0)&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;.previous&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=r&quot;(__pu_err)&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;m&quot;(__m(addr)), &quot;rJ&quot;(x), &quot;0&quot;(__pu_err))
DECL|macro|__put_user_8
mdefine_line|#define __put_user_8(x,addr)&t;&t;&t;&t;&t;&bslash;&n;__asm__ __volatile__(&quot;1: stb %r2,%1&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;2:&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.long 1b - .&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;lda $31,2b-1b(%0)&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;.previous&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=r&quot;(__pu_err)&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;m&quot;(__m(addr)), &quot;rJ&quot;(x), &quot;0&quot;(__pu_err))
macro_line|#else
multiline_comment|/* Unfortunately, we can&squot;t get an unaligned access trap for the sub-word&n;   write, so we have to do a general unaligned operation.  */
DECL|macro|__put_user_16
mdefine_line|#define __put_user_16(x,addr)&t;&t;&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;long __pu_tmp1, __pu_tmp2, __pu_tmp3, __pu_tmp4;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;1:&t;ldq_u %2,1(%5)&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;2:&t;ldq_u %1,0(%5)&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;inswh %6,%5,%4&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;inswl %6,%5,%3&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;mskwh %2,%5,%2&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;mskwl %1,%5,%1&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;or %2,%4,%2&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;or %1,%3,%1&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;3:&t;stq_u %2,1(%5)&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;4:&t;stq_u %1,0(%5)&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;5:&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.long 1b - .&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;lda $31, 5b-1b(%0)&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.long 2b - .&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;lda $31, 5b-2b(%0)&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.long 3b - .&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;lda $31, 5b-3b(%0)&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.long 4b - .&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;lda $31, 5b-4b(%0)&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;.previous&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=r&quot;(__pu_err), &quot;=&amp;r&quot;(__pu_tmp1),&t;&t;&bslash;&n;&t;&t;  &quot;=&amp;r&quot;(__pu_tmp2), &quot;=&amp;r&quot;(__pu_tmp3),&t;&t;&bslash;&n;&t;&t;  &quot;=&amp;r&quot;(__pu_tmp4)&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;r&quot;(addr), &quot;r&quot;((unsigned long)(x)), &quot;0&quot;(__pu_err)); &bslash;&n;}
DECL|macro|__put_user_8
mdefine_line|#define __put_user_8(x,addr)&t;&t;&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;long __pu_tmp1, __pu_tmp2;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;1:&t;ldq_u %1,0(%4)&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;insbl %3,%4,%2&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;mskbl %1,%4,%1&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;or %1,%2,%1&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;2:&t;stq_u %1,0(%4)&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;3:&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.long 1b - .&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;lda $31, 3b-1b(%0)&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.long 2b - .&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;lda $31, 3b-2b(%0)&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;.previous&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=r&quot;(__pu_err),&t;&t;&t;&t;&bslash;&n;&t;  &t;  &quot;=&amp;r&quot;(__pu_tmp1), &quot;=&amp;r&quot;(__pu_tmp2)&t;&t;&bslash;&n;&t;&t;: &quot;r&quot;((unsigned long)(x)), &quot;r&quot;(addr), &quot;0&quot;(__pu_err)); &bslash;&n;}
macro_line|#endif
multiline_comment|/*&n; * Complex access routines&n; */
r_extern
r_void
id|__copy_user
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_inline
r_int
DECL|function|__copy_tofrom_user_nocheck
id|__copy_tofrom_user_nocheck
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
(brace
multiline_comment|/* This little bit of silliness is to get the GP loaded for&n;&t;   a function that ordinarily wouldn&squot;t.  Otherwise we could&n;&t;   have it done by the macro directly, which can be optimized&n;&t;   the linker.  */
r_register
r_void
op_star
id|pv
id|__asm__
c_func
(paren
l_string|&quot;$27&quot;
)paren
op_assign
id|__copy_user
suffix:semicolon
r_register
r_void
op_star
id|__cu_to
id|__asm__
c_func
(paren
l_string|&quot;$6&quot;
)paren
op_assign
id|to
suffix:semicolon
r_register
r_const
r_void
op_star
id|__cu_from
id|__asm__
c_func
(paren
l_string|&quot;$7&quot;
)paren
op_assign
id|from
suffix:semicolon
r_register
r_int
id|__cu_len
id|__asm__
c_func
(paren
l_string|&quot;$0&quot;
)paren
op_assign
id|len
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;jsr $28,(%3),__copy_user&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|__cu_len
)paren
comma
l_string|&quot;=r&quot;
(paren
id|__cu_from
)paren
comma
l_string|&quot;=r&quot;
(paren
id|__cu_to
)paren
comma
l_string|&quot;=r&quot;
(paren
id|pv
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|__cu_len
)paren
comma
l_string|&quot;1&quot;
(paren
id|__cu_from
)paren
comma
l_string|&quot;2&quot;
(paren
id|__cu_to
)paren
comma
l_string|&quot;3&quot;
(paren
id|pv
)paren
suffix:colon
l_string|&quot;$1&quot;
comma
l_string|&quot;$2&quot;
comma
l_string|&quot;$3&quot;
comma
l_string|&quot;$4&quot;
comma
l_string|&quot;$5&quot;
comma
l_string|&quot;$28&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|__cu_len
suffix:semicolon
)brace
r_extern
r_inline
r_int
DECL|function|__copy_tofrom_user
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
id|len
comma
r_const
r_void
op_star
id|validate
)paren
(brace
r_if
c_cond
(paren
id|__access_ok
c_func
(paren
(paren
r_int
)paren
id|validate
comma
id|len
comma
id|get_fs
c_func
(paren
)paren
)paren
)paren
(brace
r_register
r_void
op_star
id|pv
id|__asm__
c_func
(paren
l_string|&quot;$27&quot;
)paren
op_assign
id|__copy_user
suffix:semicolon
r_register
r_void
op_star
id|__cu_to
id|__asm__
c_func
(paren
l_string|&quot;$6&quot;
)paren
op_assign
id|to
suffix:semicolon
r_register
r_const
r_void
op_star
id|__cu_from
id|__asm__
c_func
(paren
l_string|&quot;$7&quot;
)paren
op_assign
id|from
suffix:semicolon
r_register
r_int
id|__cu_len
id|__asm__
c_func
(paren
l_string|&quot;$0&quot;
)paren
op_assign
id|len
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;jsr $28,(%3),__copy_user&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|__cu_len
)paren
comma
l_string|&quot;=r&quot;
(paren
id|__cu_from
)paren
comma
l_string|&quot;=r&quot;
(paren
id|__cu_to
)paren
comma
l_string|&quot;=r&quot;
(paren
id|pv
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|__cu_len
)paren
comma
l_string|&quot;1&quot;
(paren
id|__cu_from
)paren
comma
l_string|&quot;2&quot;
(paren
id|__cu_to
)paren
comma
l_string|&quot;3&quot;
(paren
id|pv
)paren
suffix:colon
l_string|&quot;$1&quot;
comma
l_string|&quot;$2&quot;
comma
l_string|&quot;$3&quot;
comma
l_string|&quot;$4&quot;
comma
l_string|&quot;$5&quot;
comma
l_string|&quot;$28&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
id|len
op_assign
id|__cu_len
suffix:semicolon
)brace
r_return
id|len
suffix:semicolon
)brace
DECL|macro|__copy_to_user
mdefine_line|#define __copy_to_user(to,from,n)   __copy_tofrom_user_nocheck((to),(from),(n))
DECL|macro|__copy_from_user
mdefine_line|#define __copy_from_user(to,from,n) __copy_tofrom_user_nocheck((to),(from),(n))
r_extern
r_inline
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
id|n
)paren
(brace
r_return
id|__copy_tofrom_user
c_func
(paren
id|to
comma
id|from
comma
id|n
comma
id|to
)paren
suffix:semicolon
)brace
r_extern
r_inline
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
id|n
)paren
(brace
r_return
id|__copy_tofrom_user
c_func
(paren
id|to
comma
id|from
comma
id|n
comma
id|from
)paren
suffix:semicolon
)brace
r_extern
r_void
id|__do_clear_user
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_inline
r_int
DECL|function|__clear_user
id|__clear_user
c_func
(paren
r_void
op_star
id|to
comma
r_int
id|len
)paren
(brace
multiline_comment|/* This little bit of silliness is to get the GP loaded for&n;&t;   a function that ordinarily wouldn&squot;t.  Otherwise we could&n;&t;   have it done by the macro directly, which can be optimized&n;&t;   the linker.  */
r_register
r_void
op_star
id|pv
id|__asm__
c_func
(paren
l_string|&quot;$27&quot;
)paren
op_assign
id|__do_clear_user
suffix:semicolon
r_register
r_void
op_star
id|__cl_to
id|__asm__
c_func
(paren
l_string|&quot;$6&quot;
)paren
op_assign
id|to
suffix:semicolon
r_register
r_int
id|__cl_len
id|__asm__
c_func
(paren
l_string|&quot;$0&quot;
)paren
op_assign
id|len
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;jsr $28,(%2),__do_clear_user&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|__cl_len
)paren
comma
l_string|&quot;=r&quot;
(paren
id|__cl_to
)paren
comma
l_string|&quot;=r&quot;
(paren
id|pv
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|__cl_len
)paren
comma
l_string|&quot;1&quot;
(paren
id|__cl_to
)paren
comma
l_string|&quot;2&quot;
(paren
id|pv
)paren
suffix:colon
l_string|&quot;$1&quot;
comma
l_string|&quot;$2&quot;
comma
l_string|&quot;$3&quot;
comma
l_string|&quot;$4&quot;
comma
l_string|&quot;$5&quot;
comma
l_string|&quot;$28&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|__cl_len
suffix:semicolon
)brace
r_extern
r_inline
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
id|len
)paren
(brace
r_if
c_cond
(paren
id|__access_ok
c_func
(paren
(paren
r_int
)paren
id|to
comma
id|len
comma
id|get_fs
c_func
(paren
)paren
)paren
)paren
(brace
r_register
r_void
op_star
id|pv
id|__asm__
c_func
(paren
l_string|&quot;$27&quot;
)paren
op_assign
id|__do_clear_user
suffix:semicolon
r_register
r_void
op_star
id|__cl_to
id|__asm__
c_func
(paren
l_string|&quot;$6&quot;
)paren
op_assign
id|to
suffix:semicolon
r_register
r_int
id|__cl_len
id|__asm__
c_func
(paren
l_string|&quot;$0&quot;
)paren
op_assign
id|len
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;jsr $28,(%2),__do_clear_user&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|__cl_len
)paren
comma
l_string|&quot;=r&quot;
(paren
id|__cl_to
)paren
comma
l_string|&quot;=r&quot;
(paren
id|pv
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|__cl_len
)paren
comma
l_string|&quot;1&quot;
(paren
id|__cl_to
)paren
comma
l_string|&quot;2&quot;
(paren
id|pv
)paren
suffix:colon
l_string|&quot;$1&quot;
comma
l_string|&quot;$2&quot;
comma
l_string|&quot;$3&quot;
comma
l_string|&quot;$4&quot;
comma
l_string|&quot;$5&quot;
comma
l_string|&quot;$28&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
id|len
op_assign
id|__cl_len
suffix:semicolon
)brace
r_return
id|len
suffix:semicolon
)brace
multiline_comment|/* Returns: -EFAULT if exception before terminator, N if the entire&n;   buffer filled, else strlen.  */
r_extern
r_int
id|__strncpy_from_user
c_func
(paren
r_char
op_star
id|__to
comma
r_const
r_char
op_star
id|__from
comma
r_int
id|__to_len
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
id|to
comma
r_const
r_char
op_star
id|from
comma
r_int
id|n
)paren
(brace
r_int
id|ret
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|__access_ok
c_func
(paren
(paren
r_int
)paren
id|from
comma
l_int|0
comma
id|get_fs
c_func
(paren
)paren
)paren
)paren
id|ret
op_assign
id|__strncpy_from_user
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
id|ret
suffix:semicolon
)brace
multiline_comment|/* Returns: 0 if bad, string length+1 (memory size) of string if ok */
r_extern
r_int
id|__strlen_user
c_func
(paren
r_const
r_char
op_star
)paren
suffix:semicolon
DECL|function|strlen_user
r_extern
r_inline
r_int
id|strlen_user
c_func
(paren
r_const
r_char
op_star
id|str
)paren
(brace
r_return
id|access_ok
c_func
(paren
id|VERIFY_READ
comma
id|str
comma
l_int|0
)paren
ques
c_cond
id|__strlen_user
c_func
(paren
id|str
)paren
suffix:colon
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Returns: 0 if exception before NUL or reaching the supplied limit (N),&n; * a value greater than N if the limit would be exceeded, else strlen.  */
r_extern
r_int
id|__strnlen_user
c_func
(paren
r_const
r_char
op_star
comma
r_int
)paren
suffix:semicolon
DECL|function|strnlen_user
r_extern
r_inline
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
(brace
r_return
id|access_ok
c_func
(paren
id|VERIFY_READ
comma
id|str
comma
l_int|0
)paren
ques
c_cond
id|__strnlen_user
c_func
(paren
id|str
comma
id|n
)paren
suffix:colon
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * About the exception table:&n; *&n; * - insn is a 32-bit pc-relative offset from the faulting insn.&n; * - nextinsn is a 16-bit offset off of the faulting instruction&n; *   (not off of the *next* instruction as branches are).&n; * - errreg is the register in which to place -EFAULT.&n; * - valreg is the final target register for the load sequence&n; *   and will be zeroed.&n; *&n; * Either errreg or valreg may be $31, in which case nothing happens.&n; *&n; * The exception fixup information &quot;just so happens&quot; to be arranged&n; * as in a MEM format instruction.  This lets us emit our three&n; * values like so:&n; *&n; *      lda valreg, nextinsn(errreg)&n; *&n; */
DECL|struct|exception_table_entry
r_struct
id|exception_table_entry
(brace
DECL|member|insn
r_int
r_int
id|insn
suffix:semicolon
DECL|union|exception_fixup
r_union
id|exception_fixup
(brace
DECL|member|unit
r_int
id|unit
suffix:semicolon
r_struct
(brace
DECL|member|nextinsn
r_int
r_int
id|nextinsn
suffix:colon
l_int|16
suffix:semicolon
DECL|member|errreg
r_int
r_int
id|errreg
suffix:colon
l_int|5
suffix:semicolon
DECL|member|valreg
r_int
r_int
id|valreg
suffix:colon
l_int|5
suffix:semicolon
DECL|member|bits
)brace
id|bits
suffix:semicolon
DECL|member|fixup
)brace
id|fixup
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Returns the new pc */
DECL|macro|fixup_exception
mdefine_line|#define fixup_exception(map_reg, fixup, pc)&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if ((fixup)-&gt;fixup.bits.valreg != 31)&t;&t;&t;&bslash;&n;&t;&t;map_reg((fixup)-&gt;fixup.bits.valreg) = 0;&t;&bslash;&n;&t;if ((fixup)-&gt;fixup.bits.errreg != 31)&t;&t;&t;&bslash;&n;&t;&t;map_reg((fixup)-&gt;fixup.bits.errreg) = -EFAULT;&t;&bslash;&n;&t;(pc) + (fixup)-&gt;fixup.bits.nextinsn;&t;&t;&t;&bslash;&n;})
macro_line|#endif /* __ALPHA_UACCESS_H */
eof
