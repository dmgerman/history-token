multiline_comment|/*&n; *  include/asm-s390/uaccess.h&n; *&n; *  S390 version&n; *    Copyright (C) 1999 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Hartmut Penner (hpenner@de.ibm.com),&n; *               Martin Schwidefsky (schwidefsky@de.ibm.com)&n; *&n; *  Derived from &quot;include/asm-i386/uaccess.h&quot;&n; */
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
mdefine_line|#define MAKE_MM_SEG(s)&t;((mm_segment_t) { (s) })
DECL|macro|KERNEL_DS
mdefine_line|#define KERNEL_DS&t;MAKE_MM_SEG(0)
DECL|macro|USER_DS
mdefine_line|#define USER_DS&t;&t;MAKE_MM_SEG(1)
DECL|macro|get_ds
mdefine_line|#define get_ds()&t;(KERNEL_DS)
DECL|macro|get_fs
mdefine_line|#define get_fs()        ({ mm_segment_t __x; &bslash;&n;&t;&t;&t;   asm volatile(&quot;ear   %0,4&quot;:&quot;=a&quot; (__x)); &bslash;&n;&t;&t;&t;   __x;})
DECL|macro|set_fs
mdefine_line|#define set_fs(x)       ({asm volatile(&quot;sar   4,%0&quot;::&quot;a&quot; ((x).ar4));})
DECL|macro|segment_eq
mdefine_line|#define segment_eq(a,b)&t;((a).ar4 == (b).ar4)
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
DECL|function|__put_user_asm_8
r_extern
r_inline
r_int
id|__put_user_asm_8
c_func
(paren
id|__u64
id|x
comma
r_void
op_star
id|ptr
)paren
(brace
r_int
id|err
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;   sr    %0,%0&bslash;n&quot;
l_string|&quot;   la    4,%1&bslash;n&quot;
l_string|&quot;   sacf  512&bslash;n&quot;
l_string|&quot;0: stg   %2,0(4)&bslash;n&quot;
l_string|&quot;1: sacf  0&bslash;n&quot;
l_string|&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
l_string|&quot;2: lhi   %0,%h3&bslash;n&quot;
l_string|&quot;   jg    1b&bslash;n&quot;
l_string|&quot;.previous&bslash;n&quot;
l_string|&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;
l_string|&quot;   .align 8&bslash;n&quot;
l_string|&quot;   .quad  0b,2b&bslash;n&quot;
l_string|&quot;.previous&quot;
suffix:colon
l_string|&quot;=&amp;d&quot;
(paren
id|err
)paren
suffix:colon
l_string|&quot;m&quot;
(paren
op_star
(paren
(paren
id|__u64
op_star
)paren
id|ptr
)paren
)paren
comma
l_string|&quot;d&quot;
(paren
id|x
)paren
comma
l_string|&quot;K&quot;
(paren
op_minus
id|EFAULT
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;4&quot;
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|__put_user_asm_4
r_extern
r_inline
r_int
id|__put_user_asm_4
c_func
(paren
id|__u32
id|x
comma
r_void
op_star
id|ptr
)paren
(brace
r_int
id|err
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;   sr    %0,%0&bslash;n&quot;
l_string|&quot;   la    4,%1&bslash;n&quot;
l_string|&quot;   sacf  512&bslash;n&quot;
l_string|&quot;0: st    %2,0(4)&bslash;n&quot;
l_string|&quot;1: sacf  0&bslash;n&quot;
l_string|&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
l_string|&quot;2: lhi   %0,%h3&bslash;n&quot;
l_string|&quot;   jg    1b&bslash;n&quot;
l_string|&quot;.previous&bslash;n&quot;
l_string|&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;
l_string|&quot;   .align 8&bslash;n&quot;
l_string|&quot;   .quad  0b,2b&bslash;n&quot;
l_string|&quot;.previous&quot;
suffix:colon
l_string|&quot;=&amp;d&quot;
(paren
id|err
)paren
suffix:colon
l_string|&quot;m&quot;
(paren
op_star
(paren
(paren
id|__u32
op_star
)paren
id|ptr
)paren
)paren
comma
l_string|&quot;d&quot;
(paren
id|x
)paren
comma
l_string|&quot;K&quot;
(paren
op_minus
id|EFAULT
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;4&quot;
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|__put_user_asm_2
r_extern
r_inline
r_int
id|__put_user_asm_2
c_func
(paren
id|__u16
id|x
comma
r_void
op_star
id|ptr
)paren
(brace
r_int
id|err
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;   sr    %0,%0&bslash;n&quot;
l_string|&quot;   la    4,%1&bslash;n&quot;
l_string|&quot;   sacf  512&bslash;n&quot;
l_string|&quot;0: sth   %2,0(4)&bslash;n&quot;
l_string|&quot;1: sacf  0&bslash;n&quot;
l_string|&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
l_string|&quot;2: lhi   %0,%h3&bslash;n&quot;
l_string|&quot;   jg    1b&bslash;n&quot;
l_string|&quot;.previous&bslash;n&quot;
l_string|&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;
l_string|&quot;   .align 8&bslash;n&quot;
l_string|&quot;   .quad  0b,2b&bslash;n&quot;
l_string|&quot;.previous&quot;
suffix:colon
l_string|&quot;=&amp;d&quot;
(paren
id|err
)paren
suffix:colon
l_string|&quot;m&quot;
(paren
op_star
(paren
(paren
id|__u16
op_star
)paren
id|ptr
)paren
)paren
comma
l_string|&quot;d&quot;
(paren
id|x
)paren
comma
l_string|&quot;K&quot;
(paren
op_minus
id|EFAULT
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;4&quot;
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|__put_user_asm_1
r_extern
r_inline
r_int
id|__put_user_asm_1
c_func
(paren
id|__u8
id|x
comma
r_void
op_star
id|ptr
)paren
(brace
r_int
id|err
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;   sr    %0,%0&bslash;n&quot;
l_string|&quot;   la    4,%1&bslash;n&quot;
l_string|&quot;   sacf  512&bslash;n&quot;
l_string|&quot;0: stc   %2,0(4)&bslash;n&quot;
l_string|&quot;1: sacf  0&bslash;n&quot;
l_string|&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
l_string|&quot;2: lhi   %0,%h3&bslash;n&quot;
l_string|&quot;   jg    1b&bslash;n&quot;
l_string|&quot;.previous&bslash;n&quot;
l_string|&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;
l_string|&quot;   .align 8&bslash;n&quot;
l_string|&quot;   .quad  0b,2b&bslash;n&quot;
l_string|&quot;.previous&quot;
suffix:colon
l_string|&quot;=&amp;d&quot;
(paren
id|err
)paren
suffix:colon
l_string|&quot;m&quot;
(paren
op_star
(paren
(paren
id|__u8
op_star
)paren
id|ptr
)paren
)paren
comma
l_string|&quot;d&quot;
(paren
id|x
)paren
comma
l_string|&quot;K&quot;
(paren
op_minus
id|EFAULT
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;4&quot;
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/*&n; * (u?)(u64) ... autsch, but that the only way we can suppress the&n; * warnings when compiling binfmt_elf.c&n; */
DECL|macro|__put_user
mdefine_line|#define __put_user(x, ptr)                                      &bslash;&n;({                                                              &bslash;&n;        __typeof__(*(ptr)) *__pu_addr = (ptr);                  &bslash;&n;        __typeof__(*(ptr)) __x = (x);                           &bslash;&n;        int __pu_err;                                           &bslash;&n;        switch (sizeof (*(__pu_addr))) {                        &bslash;&n;        case 1:                                                 &bslash;&n;                __pu_err = __put_user_asm_1((__u8)(__u64)(__x), &bslash;&n;                                            __pu_addr);         &bslash;&n;                break;                                          &bslash;&n;        case 2:                                                 &bslash;&n;                __pu_err = __put_user_asm_2((__u16)(__u64)(__x),&bslash;&n;                                            __pu_addr);         &bslash;&n;                break;                                          &bslash;&n;        case 4:                                                 &bslash;&n;                __pu_err = __put_user_asm_4((__u32)(__u64)(__x),&bslash;&n;                                            __pu_addr);         &bslash;&n;                break;                                          &bslash;&n;        case 8:                                                 &bslash;&n;                __pu_err = __put_user_asm_8((__u64)(__x),       &bslash;&n;                                            __pu_addr);         &bslash;&n;                break;                                          &bslash;&n;        default:                                                &bslash;&n;                __pu_err = __put_user_bad();                    &bslash;&n;                break;                                          &bslash;&n;         }                                                      &bslash;&n;        __pu_err;                                               &bslash;&n;})
DECL|macro|put_user
mdefine_line|#define put_user(x, ptr) __put_user(x, ptr)
r_extern
r_int
id|__put_user_bad
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|__get_user_asm_8
mdefine_line|#define __get_user_asm_8(x, ptr, err)                                      &bslash;&n;({                                                                         &bslash;&n;        __asm__ __volatile__ (  &quot;   sr    %1,%1&bslash;n&quot;                         &bslash;&n;                                &quot;   la    4,%2&bslash;n&quot;                          &bslash;&n;                                &quot;   sacf  512&bslash;n&quot;                           &bslash;&n;                                &quot;0: lg    %0,0(4)&bslash;n&quot;                       &bslash;&n;                                &quot;1: sacf  0&bslash;n&quot;                             &bslash;&n;                                &quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;                 &bslash;&n;                                &quot;2: lhi   %1,%h3&bslash;n&quot;                        &bslash;&n;                                &quot;   jg    1b&bslash;n&quot;                            &bslash;&n;                                &quot;.previous&bslash;n&quot;                              &bslash;&n;                                &quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;              &bslash;&n;                                &quot;   .align 8&bslash;n&quot;                            &bslash;&n;                                &quot;   .quad 0b,2b&bslash;n&quot;                         &bslash;&n;                                &quot;.previous&quot;                                &bslash;&n;                                : &quot;=d&quot; (x) , &quot;=&amp;d&quot; (err)                   &bslash;&n;                                : &quot;m&quot; (*(const __u64*)(ptr)),&quot;K&quot; (-EFAULT) &bslash;&n;                                : &quot;cc&quot;, &quot;4&quot; );                             &bslash;&n;})
DECL|macro|__get_user_asm_4
mdefine_line|#define __get_user_asm_4(x, ptr, err)                                      &bslash;&n;({                                                                         &bslash;&n;        __asm__ __volatile__ (  &quot;   sr    %1,%1&bslash;n&quot;                         &bslash;&n;                                &quot;   la    4,%2&bslash;n&quot;                          &bslash;&n;                                &quot;   sacf  512&bslash;n&quot;                           &bslash;&n;                                &quot;0: l     %0,0(4)&bslash;n&quot;                       &bslash;&n;                                &quot;1: sacf  0&bslash;n&quot;                             &bslash;&n;                                &quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;                 &bslash;&n;                                &quot;2: lhi   %1,%h3&bslash;n&quot;                        &bslash;&n;                                &quot;   jg    1b&bslash;n&quot;                            &bslash;&n;                                &quot;.previous&bslash;n&quot;                              &bslash;&n;                                &quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;              &bslash;&n;                                &quot;   .align 8&bslash;n&quot;                            &bslash;&n;                                &quot;   .quad 0b,2b&bslash;n&quot;                         &bslash;&n;                                &quot;.previous&quot;                                &bslash;&n;                                : &quot;=d&quot; (x) , &quot;=&amp;d&quot; (err)                   &bslash;&n;                                : &quot;m&quot; (*(const __u32*)(ptr)),&quot;K&quot; (-EFAULT) &bslash;&n;                                : &quot;cc&quot;, &quot;4&quot; );                             &bslash;&n;})
DECL|macro|__get_user_asm_2
mdefine_line|#define __get_user_asm_2(x, ptr, err)                                      &bslash;&n;({                                                                         &bslash;&n;        __asm__ __volatile__ (  &quot;   sr    %1,%1&bslash;n&quot;                         &bslash;&n;                                &quot;   la    4,%2&bslash;n&quot;                          &bslash;&n;                                &quot;   sacf  512&bslash;n&quot;                           &bslash;&n;                                &quot;0: lh    %0,0(4)&bslash;n&quot;                       &bslash;&n;                                &quot;1: sacf  0&bslash;n&quot;                             &bslash;&n;                                &quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;                 &bslash;&n;                                &quot;2: lhi   %1,%h3&bslash;n&quot;                        &bslash;&n;                                &quot;   jg    1b&bslash;n&quot;                            &bslash;&n;                                &quot;.previous&bslash;n&quot;                              &bslash;&n;                                &quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;              &bslash;&n;                                &quot;   .align 8&bslash;n&quot;                            &bslash;&n;                                &quot;   .quad 0b,2b&bslash;n&quot;                         &bslash;&n;                                &quot;.previous&quot;                                &bslash;&n;                                : &quot;=d&quot; (x) , &quot;=&amp;d&quot; (err)                   &bslash;&n;                                : &quot;m&quot; (*(const __u16*)(ptr)),&quot;K&quot; (-EFAULT) &bslash;&n;                                : &quot;cc&quot;, &quot;4&quot; );                             &bslash;&n;})
DECL|macro|__get_user_asm_1
mdefine_line|#define __get_user_asm_1(x, ptr, err)                                     &bslash;&n;({                                                                        &bslash;&n;        __asm__ __volatile__ (  &quot;   sr    %1,%1&bslash;n&quot;                        &bslash;&n;                                &quot;   la    4,%2&bslash;n&quot;                         &bslash;&n;                                &quot;   sr    %0,%0&bslash;n&quot;                        &bslash;&n;                                &quot;   sacf  512&bslash;n&quot;                          &bslash;&n;                                &quot;0: ic    %0,0(4)&bslash;n&quot;                      &bslash;&n;                                &quot;1: sacf  0&bslash;n&quot;                            &bslash;&n;                                &quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;                &bslash;&n;                                &quot;2: lhi   %1,%h3&bslash;n&quot;                       &bslash;&n;                                &quot;   jg    1b&bslash;n&quot;                           &bslash;&n;                                &quot;.previous&bslash;n&quot;                             &bslash;&n;                                &quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;             &bslash;&n;                                &quot;   .align 8&bslash;n&quot;                           &bslash;&n;                                &quot;   .quad 0b,2b&bslash;n&quot;                        &bslash;&n;                                &quot;.previous&quot;                               &bslash;&n;                                : &quot;=d&quot; (x) , &quot;=&amp;d&quot; (err)                  &bslash;&n;                                : &quot;m&quot; (*(const __u8*)(ptr)),&quot;K&quot; (-EFAULT) &bslash;&n;                                : &quot;cc&quot;, &quot;4&quot; );                            &bslash;&n;})
DECL|macro|__get_user
mdefine_line|#define __get_user(x, ptr)                                      &bslash;&n;({                                                              &bslash;&n;        __typeof__(ptr) __gu_addr = (ptr);                      &bslash;&n;        __typeof__(*(ptr)) __x;                                 &bslash;&n;        int __gu_err;                                           &bslash;&n;        switch (sizeof(*(ptr))) {                               &bslash;&n;        case 1:                                                 &bslash;&n;                __get_user_asm_1(__x,__gu_addr,__gu_err);       &bslash;&n;                break;                                          &bslash;&n;        case 2:                                                 &bslash;&n;                __get_user_asm_2(__x,__gu_addr,__gu_err);       &bslash;&n;                break;                                          &bslash;&n;        case 4:                                                 &bslash;&n;                __get_user_asm_4(__x,__gu_addr,__gu_err);       &bslash;&n;                break;                                          &bslash;&n;        case 8:                                                 &bslash;&n;                __get_user_asm_8(__x,__gu_addr,__gu_err);       &bslash;&n;                break;                                          &bslash;&n;        default:                                                &bslash;&n;                __x = 0;                                        &bslash;&n;                __gu_err = __get_user_bad();                    &bslash;&n;                break;                                          &bslash;&n;        }                                                       &bslash;&n;        (x) = __x;                                              &bslash;&n;        __gu_err;                                               &bslash;&n;})
DECL|macro|get_user
mdefine_line|#define get_user(x, ptr) __get_user(x, ptr)
r_extern
r_int
id|__get_user_bad
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * access register are set up, that 4 points to secondary (user) , 2 to primary (kernel)&n; */
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
op_star
id|to
)paren
suffix:semicolon
DECL|macro|__copy_to_user
mdefine_line|#define __copy_to_user(to, from, n)                             &bslash;&n;({                                                              &bslash;&n;        __copy_to_user_asm(from, n, to);                        &bslash;&n;})
DECL|macro|copy_to_user
mdefine_line|#define copy_to_user(to, from, n)                               &bslash;&n;({                                                              &bslash;&n;        long err = 0;                                           &bslash;&n;        __typeof__(n) __n = (n);                                &bslash;&n;        if (__access_ok(to,__n)) {                              &bslash;&n;                err = __copy_to_user_asm(from, __n, to);        &bslash;&n;        }                                                       &bslash;&n;        else                                                    &bslash;&n;                err = __n;                                      &bslash;&n;        err;                                                    &bslash;&n;})
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
op_star
id|from
)paren
suffix:semicolon
DECL|macro|__copy_from_user
mdefine_line|#define __copy_from_user(to, from, n)                           &bslash;&n;({                                                              &bslash;&n;        __copy_from_user_asm(to, n, from);                      &bslash;&n;})
DECL|macro|copy_from_user
mdefine_line|#define copy_from_user(to, from, n)                             &bslash;&n;({                                                              &bslash;&n;        long err = 0;                                           &bslash;&n;        __typeof__(n) __n = (n);                                &bslash;&n;        if (__access_ok(from,__n)) {                            &bslash;&n;                err = __copy_from_user_asm(to, __n, from);      &bslash;&n;        }                                                       &bslash;&n;        else                                                    &bslash;&n;                err = __n;                                      &bslash;&n;        err;                                                    &bslash;&n;})
multiline_comment|/*&n; * Copy a null terminated string from userspace.&n; */
r_static
r_inline
r_int
DECL|function|__strncpy_from_user
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
(brace
r_int
id|len
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;   slgr  %0,%0&bslash;n&quot;
l_string|&quot;   lgr   2,%1&bslash;n&quot;
l_string|&quot;   lgr   4,%2&bslash;n&quot;
l_string|&quot;   slr   3,3&bslash;n&quot;
l_string|&quot;   sacf  512&bslash;n&quot;
l_string|&quot;0: ic    3,0(%0,4)&bslash;n&quot;
l_string|&quot;1: stc   3,0(%0,2)&bslash;n&quot;
l_string|&quot;   ltr   3,3&bslash;n&quot;
l_string|&quot;   jz    2f&bslash;n&quot;
l_string|&quot;   aghi  %0,1&bslash;n&quot;
l_string|&quot;   cgr   %0,%3&bslash;n&quot;
l_string|&quot;   jl    0b&bslash;n&quot;
l_string|&quot;2: sacf  0&bslash;n&quot;
l_string|&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
l_string|&quot;3: lghi  %0,%h4&bslash;n&quot;
l_string|&quot;   jg    2b&bslash;n&quot;
l_string|&quot;.previous&bslash;n&quot;
l_string|&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;
l_string|&quot;   .align 8&bslash;n&quot;
l_string|&quot;   .quad  0b,3b&bslash;n&quot;
l_string|&quot;   .quad  1b,3b&bslash;n&quot;
l_string|&quot;.previous&quot;
suffix:colon
l_string|&quot;=&amp;a&quot;
(paren
id|len
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|dst
)paren
comma
l_string|&quot;d&quot;
(paren
id|src
)paren
comma
l_string|&quot;d&quot;
(paren
id|count
)paren
comma
l_string|&quot;K&quot;
(paren
op_minus
id|EFAULT
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;2&quot;
comma
l_string|&quot;3&quot;
comma
l_string|&quot;4&quot;
)paren
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
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
id|res
op_assign
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
id|res
suffix:semicolon
)brace
multiline_comment|/*&n; * Return the size of a string (including the ending 0)&n; *&n; * Return 0 for error&n; */
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
op_star
id|src
comma
r_int
r_int
id|n
)paren
(brace
macro_line|#if 0
id|__asm__
id|__volatile__
(paren
l_string|&quot;   algr  %0,%1&bslash;n&quot;
l_string|&quot;   slgr  0,0&bslash;n&quot;
l_string|&quot;   lgr   4,%1&bslash;n&quot;
l_string|&quot;   sacf  512&bslash;n&quot;
l_string|&quot;0: srst  %0,4&bslash;n&quot;
l_string|&quot;   jo    0b&bslash;n&quot;
l_string|&quot;   slgr  %0,%1&bslash;n&quot;
l_string|&quot;   aghi  %0,1&bslash;n&quot;
l_string|&quot;1: sacf  0&bslash;n&quot;
l_string|&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
l_string|&quot;2: slgr  %0,%0&bslash;n&quot;
l_string|&quot;   jg    1b&bslash;n&quot;
l_string|&quot;.previous&bslash;n&quot;
l_string|&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;
l_string|&quot;   .align 8&bslash;n&quot;
l_string|&quot;   .quad  0b,2b&bslash;n&quot;
l_string|&quot;.previous&quot;
suffix:colon
l_string|&quot;+&amp;a&quot;
(paren
id|n
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|src
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;0&quot;
comma
l_string|&quot;4&quot;
)paren
suffix:semicolon
macro_line|#else
id|__asm__
id|__volatile__
(paren
l_string|&quot;   lgr   4,%1&bslash;n&quot;
l_string|&quot;   sacf  512&bslash;n&quot;
l_string|&quot;0: cli   0(4),0x00&bslash;n&quot;
l_string|&quot;   la    4,1(4)&bslash;n&quot;
l_string|&quot;   je    1f&bslash;n&quot;
l_string|&quot;   brctg %0,0b&bslash;n&quot;
l_string|&quot;1: lgr   %0,4&bslash;n&quot;
l_string|&quot;   slgr  %0,%1&bslash;n&quot;
l_string|&quot;2: sacf  0&bslash;n&quot;
l_string|&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
l_string|&quot;3: slgr  %0,%0&bslash;n&quot;
l_string|&quot;   jg    2b&bslash;n&quot;
l_string|&quot;.previous&bslash;n&quot;
l_string|&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;
l_string|&quot;   .align 8&bslash;n&quot;
l_string|&quot;   .quad  0b,3b&bslash;n&quot;
l_string|&quot;.previous&quot;
suffix:colon
l_string|&quot;+&amp;a&quot;
(paren
id|n
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|src
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;4&quot;
)paren
suffix:semicolon
macro_line|#endif
r_return
id|n
suffix:semicolon
)brace
DECL|macro|strlen_user
mdefine_line|#define strlen_user(str) strnlen_user(str, ~0UL)
multiline_comment|/*&n; * Zero Userspace&n; */
r_extern
r_int
id|__clear_user_asm
c_func
(paren
r_void
op_star
id|to
comma
r_int
id|n
)paren
suffix:semicolon
DECL|macro|__clear_user
mdefine_line|#define __clear_user(to, n)                                     &bslash;&n;({                                                              &bslash;&n;        __clear_user_asm(to, n);                                &bslash;&n;})
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
id|__clear_user
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
macro_line|#endif                                 /* _S390_UACCESS_H                  */
eof
