macro_line|#ifndef __PARISC_UACCESS_H
DECL|macro|__PARISC_UACCESS_H
mdefine_line|#define __PARISC_UACCESS_H
multiline_comment|/*&n; * User space memory access functions&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/cache.h&gt;
DECL|macro|VERIFY_READ
mdefine_line|#define VERIFY_READ 0
DECL|macro|VERIFY_WRITE
mdefine_line|#define VERIFY_WRITE 1
DECL|macro|KERNEL_DS
mdefine_line|#define KERNEL_DS&t;((mm_segment_t){0})
DECL|macro|USER_DS
mdefine_line|#define USER_DS &t;((mm_segment_t){1})
DECL|macro|segment_eq
mdefine_line|#define segment_eq(a,b)&t;((a).seg == (b).seg)
DECL|macro|get_ds
mdefine_line|#define get_ds()&t;(KERNEL_DS)
DECL|macro|get_fs
mdefine_line|#define get_fs()&t;(current_thread_info()-&gt;addr_limit)
DECL|macro|set_fs
mdefine_line|#define set_fs(x)&t;(current_thread_info()-&gt;addr_limit = (x))
multiline_comment|/*&n; * Note that since kernel addresses are in a separate address space on&n; * parisc, we don&squot;t need to do anything for access_ok() or verify_area().&n; * We just let the page fault handler do the right thing. This also means&n; * that put_user is the same as __put_user, etc.&n; */
DECL|macro|access_ok
mdefine_line|#define access_ok(type,addr,size)   (1)
DECL|macro|verify_area
mdefine_line|#define verify_area(type,addr,size) (0)
DECL|macro|put_user
mdefine_line|#define put_user __put_user
DECL|macro|get_user
mdefine_line|#define get_user __get_user
macro_line|#if BITS_PER_LONG == 32
DECL|macro|LDD_KERNEL
mdefine_line|#define LDD_KERNEL(ptr)&t;&t;BUG()
DECL|macro|LDD_USER
mdefine_line|#define LDD_USER(ptr)&t;&t;BUG()
DECL|macro|STD_KERNEL
mdefine_line|#define STD_KERNEL(x, ptr) __put_kernel_asm64((u32)x,ptr)
DECL|macro|STD_USER
mdefine_line|#define STD_USER(x, ptr) __put_user_asm64((u32)x,ptr)
macro_line|#else
DECL|macro|LDD_KERNEL
mdefine_line|#define LDD_KERNEL(ptr) __get_kernel_asm(&quot;ldd&quot;,ptr)
DECL|macro|LDD_USER
mdefine_line|#define LDD_USER(ptr) __get_user_asm(&quot;ldd&quot;,ptr)
DECL|macro|STD_KERNEL
mdefine_line|#define STD_KERNEL(x, ptr) __put_kernel_asm(&quot;std&quot;,x,ptr)
DECL|macro|STD_USER
mdefine_line|#define STD_USER(x, ptr) __put_user_asm(&quot;std&quot;,x,ptr)
macro_line|#endif
multiline_comment|/*&n; * The exception table contains two values: the first is an address&n; * for an instruction that is allowed to fault, and the second is&n; * the number of bytes to skip if a fault occurs. We also support in&n; * two bit flags: 0x2 tells the exception handler to clear register&n; * r9 and 0x1 tells the exception handler to put -EFAULT in r8.&n; * This allows us to handle the simple cases for put_user and&n; * get_user without having to have .fixup sections.&n; */
DECL|struct|exception_table_entry
r_struct
id|exception_table_entry
(brace
DECL|member|addr
r_int
r_int
id|addr
suffix:semicolon
multiline_comment|/* address of insn that is allowed to fault.   */
DECL|member|skip
r_int
id|skip
suffix:semicolon
multiline_comment|/* pcoq skip | r9 clear flag | r8 -EFAULT flag */
)brace
suffix:semicolon
DECL|macro|__get_user
mdefine_line|#define __get_user(x,ptr)                               &bslash;&n;({                                                      &bslash;&n;&t;register long __gu_err __asm__ (&quot;r8&quot;) = 0;      &bslash;&n;&t;register long __gu_val __asm__ (&quot;r9&quot;) = 0;      &bslash;&n;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (segment_eq(get_fs(),KERNEL_DS)) {           &bslash;&n;&t;    switch (sizeof(*(ptr))) {                   &bslash;&n;&t;    case 1: __get_kernel_asm(&quot;ldb&quot;,ptr); break; &bslash;&n;&t;    case 2: __get_kernel_asm(&quot;ldh&quot;,ptr); break; &bslash;&n;&t;    case 4: __get_kernel_asm(&quot;ldw&quot;,ptr); break; &bslash;&n;&t;    case 8: LDD_KERNEL(ptr); break;&t;&t;&bslash;&n;&t;    default: BUG(); break;                      &bslash;&n;&t;    }                                           &bslash;&n;&t;}                                               &bslash;&n;&t;else {                                          &bslash;&n;&t;    switch (sizeof(*(ptr))) {                   &bslash;&n;&t;    case 1: __get_user_asm(&quot;ldb&quot;,ptr); break;   &bslash;&n;&t;    case 2: __get_user_asm(&quot;ldh&quot;,ptr); break;   &bslash;&n;&t;    case 4: __get_user_asm(&quot;ldw&quot;,ptr); break;   &bslash;&n;&t;    case 8: LDD_USER(ptr);  break;&t;&t;&bslash;&n;&t;    default: BUG(); break;                      &bslash;&n;&t;    }                                           &bslash;&n;&t;}                                               &bslash;&n;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(x) = (__typeof__(*(ptr))) __gu_val;            &bslash;&n;&t;__gu_err;                                       &bslash;&n;})
macro_line|#ifdef __LP64__
DECL|macro|__get_kernel_asm
mdefine_line|#define __get_kernel_asm(ldx,ptr)                       &bslash;&n;&t;__asm__(&quot;&bslash;n1:&bslash;t&quot; ldx &quot;&bslash;t0(%2),%0&bslash;n&quot;             &bslash;&n;&t;&t;&quot;2:&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&bslash;t.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;         &bslash;&n;&t;&t; &quot;&bslash;t.dword&bslash;t1b&bslash;n&quot;                       &bslash;&n;&t;&t; &quot;&bslash;t.dword&bslash;t(2b-1b)+3&bslash;n&quot;                &bslash;&n;&t;&t; &quot;&bslash;t.previous&quot;                          &bslash;&n;&t;&t;: &quot;=r&quot;(__gu_val), &quot;=r&quot;(__gu_err)        &bslash;&n;&t;&t;: &quot;r&quot;(ptr), &quot;1&quot;(__gu_err));
DECL|macro|__get_user_asm
mdefine_line|#define __get_user_asm(ldx,ptr)                         &bslash;&n;&t;__asm__(&quot;&bslash;n1:&bslash;t&quot; ldx &quot;&bslash;t0(%%sr3,%2),%0&bslash;n&quot;       &bslash;&n;&t;&t;&quot;2:&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&bslash;t.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;         &bslash;&n;&t;&t; &quot;&bslash;t.dword&bslash;t1b&bslash;n&quot;                       &bslash;&n;&t;&t; &quot;&bslash;t.dword&bslash;t(2b-1b)+3&bslash;n&quot;                &bslash;&n;&t;&t; &quot;&bslash;t.previous&quot;                          &bslash;&n;&t;&t;: &quot;=r&quot;(__gu_val), &quot;=r&quot;(__gu_err)        &bslash;&n;&t;&t;: &quot;r&quot;(ptr), &quot;1&quot;(__gu_err));
macro_line|#else
DECL|macro|__get_kernel_asm
mdefine_line|#define __get_kernel_asm(ldx,ptr)                       &bslash;&n;&t;__asm__(&quot;&bslash;n1:&bslash;t&quot; ldx &quot;&bslash;t0(%2),%0&bslash;n&quot;             &bslash;&n;&t;&t;&quot;2:&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&bslash;t.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;         &bslash;&n;&t;&t; &quot;&bslash;t.word&bslash;t1b&bslash;n&quot;                        &bslash;&n;&t;&t; &quot;&bslash;t.word&bslash;t(2b-1b)+3&bslash;n&quot;                 &bslash;&n;&t;&t; &quot;&bslash;t.previous&quot;                          &bslash;&n;&t;&t;: &quot;=r&quot;(__gu_val), &quot;=r&quot;(__gu_err)        &bslash;&n;&t;&t;: &quot;r&quot;(ptr), &quot;1&quot;(__gu_err));
DECL|macro|__get_user_asm
mdefine_line|#define __get_user_asm(ldx,ptr)                         &bslash;&n;&t;__asm__(&quot;&bslash;n1:&bslash;t&quot; ldx &quot;&bslash;t0(%%sr3,%2),%0&bslash;n&quot;       &bslash;&n;&t;&t;&quot;2:&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&bslash;t.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;         &bslash;&n;&t;&t; &quot;&bslash;t.word&bslash;t1b&bslash;n&quot;                        &bslash;&n;&t;&t; &quot;&bslash;t.word&bslash;t(2b-1b)+3&bslash;n&quot;                 &bslash;&n;&t;&t; &quot;&bslash;t.previous&quot;                          &bslash;&n;&t;&t;: &quot;=r&quot;(__gu_val), &quot;=r&quot;(__gu_err)        &bslash;&n;&t;&t;: &quot;r&quot;(ptr), &quot;1&quot;(__gu_err));
macro_line|#endif
DECL|macro|__put_user
mdefine_line|#define __put_user(x,ptr)                                       &bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;register long __pu_err __asm__ (&quot;r8&quot;) = 0;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (segment_eq(get_fs(),KERNEL_DS)) {                   &bslash;&n;&t;    switch (sizeof(*(ptr))) {                           &bslash;&n;&t;    case 1: __put_kernel_asm(&quot;stb&quot;,x,ptr); break;       &bslash;&n;&t;    case 2: __put_kernel_asm(&quot;sth&quot;,x,ptr); break;       &bslash;&n;&t;    case 4: __put_kernel_asm(&quot;stw&quot;,x,ptr); break;       &bslash;&n;&t;    case 8: STD_KERNEL(x,ptr); break;&t;&t;&t;&bslash;&n;&t;    default: BUG(); break;                              &bslash;&n;&t;    }                                                   &bslash;&n;&t;}                                                       &bslash;&n;&t;else {                                                  &bslash;&n;&t;    switch (sizeof(*(ptr))) {                           &bslash;&n;&t;    case 1: __put_user_asm(&quot;stb&quot;,x,ptr); break;         &bslash;&n;&t;    case 2: __put_user_asm(&quot;sth&quot;,x,ptr); break;         &bslash;&n;&t;    case 4: __put_user_asm(&quot;stw&quot;,x,ptr); break;         &bslash;&n;&t;    case 8: STD_USER(x,ptr); break;&t;&t;&t;&bslash;&n;&t;    default: BUG(); break;                              &bslash;&n;&t;    }                                                   &bslash;&n;&t;}                                                       &bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__pu_err;&t;&t;&t;&t;&t;&t;&bslash;&n;})
multiline_comment|/*&n; * The &quot;__put_user/kernel_asm()&quot; macros tell gcc they read from memory&n; * instead of writing. This is because they do not write to any memory&n; * gcc knows about, so there are no aliasing issues.&n; */
macro_line|#ifdef __LP64__
DECL|macro|__put_kernel_asm
mdefine_line|#define __put_kernel_asm(stx,x,ptr)                         &bslash;&n;&t;__asm__ __volatile__ (                              &bslash;&n;&t;&t;&quot;&bslash;n1:&bslash;t&quot; stx &quot;&bslash;t%2,0(%1)&bslash;n&quot;                 &bslash;&n;&t;&t;&quot;2:&bslash;n&quot;&t;&t;&t;&t;&t;    &bslash;&n;&t;&t;&quot;&bslash;t.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;             &bslash;&n;&t;&t; &quot;&bslash;t.dword&bslash;t1b&bslash;n&quot;                           &bslash;&n;&t;&t; &quot;&bslash;t.dword&bslash;t(2b-1b)+1&bslash;n&quot;                    &bslash;&n;&t;&t; &quot;&bslash;t.previous&quot;                              &bslash;&n;&t;&t;: &quot;=r&quot;(__pu_err)                            &bslash;&n;&t;&t;: &quot;r&quot;(ptr), &quot;r&quot;(x), &quot;0&quot;(__pu_err))
DECL|macro|__put_user_asm
mdefine_line|#define __put_user_asm(stx,x,ptr)                           &bslash;&n;&t;__asm__ __volatile__ (                              &bslash;&n;&t;&t;&quot;&bslash;n1:&bslash;t&quot; stx &quot;&bslash;t%2,0(%%sr3,%1)&bslash;n&quot;           &bslash;&n;&t;&t;&quot;2:&bslash;n&quot;&t;&t;&t;&t;&t;    &bslash;&n;&t;&t;&quot;&bslash;t.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;             &bslash;&n;&t;&t; &quot;&bslash;t.dword&bslash;t1b&bslash;n&quot;                           &bslash;&n;&t;&t; &quot;&bslash;t.dword&bslash;t(2b-1b)+1&bslash;n&quot;                    &bslash;&n;&t;&t; &quot;&bslash;t.previous&quot;                              &bslash;&n;&t;&t;: &quot;=r&quot;(__pu_err)                            &bslash;&n;&t;&t;: &quot;r&quot;(ptr), &quot;r&quot;(x), &quot;0&quot;(__pu_err))
macro_line|#else
DECL|macro|__put_kernel_asm
mdefine_line|#define __put_kernel_asm(stx,x,ptr)                         &bslash;&n;&t;__asm__ __volatile__ (                              &bslash;&n;&t;&t;&quot;&bslash;n1:&bslash;t&quot; stx &quot;&bslash;t%2,0(%1)&bslash;n&quot;                 &bslash;&n;&t;&t;&quot;2:&bslash;n&quot;&t;&t;&t;&t;&t;    &bslash;&n;&t;&t;&quot;&bslash;t.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;             &bslash;&n;&t;&t; &quot;&bslash;t.word&bslash;t1b&bslash;n&quot;                            &bslash;&n;&t;&t; &quot;&bslash;t.word&bslash;t(2b-1b)+1&bslash;n&quot;                     &bslash;&n;&t;&t; &quot;&bslash;t.previous&quot;                              &bslash;&n;&t;&t;: &quot;=r&quot;(__pu_err)                            &bslash;&n;&t;&t;: &quot;r&quot;(ptr), &quot;r&quot;(x), &quot;0&quot;(__pu_err))
DECL|macro|__put_user_asm
mdefine_line|#define __put_user_asm(stx,x,ptr)                           &bslash;&n;&t;__asm__ __volatile__ (                              &bslash;&n;&t;&t;&quot;&bslash;n1:&bslash;t&quot; stx &quot;&bslash;t%2,0(%%sr3,%1)&bslash;n&quot;           &bslash;&n;&t;&t;&quot;2:&bslash;n&quot;&t;&t;&t;&t;&t;    &bslash;&n;&t;&t;&quot;&bslash;t.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;             &bslash;&n;&t;&t; &quot;&bslash;t.word&bslash;t1b&bslash;n&quot;                            &bslash;&n;&t;&t; &quot;&bslash;t.word&bslash;t(2b-1b)+1&bslash;n&quot;                     &bslash;&n;&t;&t; &quot;&bslash;t.previous&quot;                              &bslash;&n;&t;&t;: &quot;=r&quot;(__pu_err)                            &bslash;&n;&t;&t;: &quot;r&quot;(ptr), &quot;r&quot;(x), &quot;0&quot;(__pu_err))
DECL|function|__put_kernel_asm64
r_static
r_inline
r_void
id|__put_kernel_asm64
c_func
(paren
id|u64
id|x
comma
r_void
op_star
id|ptr
)paren
(brace
id|u32
id|hi
op_assign
id|x
op_rshift
l_int|32
suffix:semicolon
id|u32
id|lo
op_assign
id|x
op_amp
l_int|0xffffffff
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;&bslash;n1:&bslash;tstw %1,0(%0)&bslash;n&quot;
l_string|&quot;&bslash;n2:&bslash;tstw %2,4(%0)&bslash;n&quot;
l_string|&quot;3:&bslash;n&quot;
l_string|&quot;&bslash;t.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;
l_string|&quot;&bslash;t.word&bslash;t1b&bslash;n&quot;
l_string|&quot;&bslash;t.word&bslash;t(3b-1b)+1&bslash;n&quot;
l_string|&quot;&bslash;t.word&bslash;t2b&bslash;n&quot;
l_string|&quot;&bslash;t.word&bslash;t(3b-2b)+1&bslash;n&quot;
l_string|&quot;&bslash;t.previous&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|ptr
)paren
comma
l_string|&quot;r&quot;
(paren
id|hi
)paren
comma
l_string|&quot;r&quot;
(paren
id|lo
)paren
)paren
suffix:semicolon
)brace
DECL|function|__put_user_asm64
r_static
r_inline
r_void
id|__put_user_asm64
c_func
(paren
id|u64
id|x
comma
r_void
op_star
id|ptr
)paren
(brace
id|u32
id|hi
op_assign
id|x
op_rshift
l_int|32
suffix:semicolon
id|u32
id|lo
op_assign
id|x
op_amp
l_int|0xffffffff
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;&bslash;n1:&bslash;tstw %1,0(%%sr3,%0)&bslash;n&quot;
l_string|&quot;&bslash;n2:&bslash;tstw %2,4(%%sr3,%0)&bslash;n&quot;
l_string|&quot;3:&bslash;n&quot;
l_string|&quot;&bslash;t.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;
l_string|&quot;&bslash;t.word&bslash;t1b&bslash;n&quot;
l_string|&quot;&bslash;t.word&bslash;t(3b-1b)+1&bslash;n&quot;
l_string|&quot;&bslash;t.word&bslash;t2b&bslash;n&quot;
l_string|&quot;&bslash;t.word&bslash;t(3b-2b)+1&bslash;n&quot;
l_string|&quot;&bslash;t.previous&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|ptr
)paren
comma
l_string|&quot;r&quot;
(paren
id|hi
)paren
comma
l_string|&quot;r&quot;
(paren
id|lo
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; * Complex access routines -- external declarations&n; */
r_extern
r_int
r_int
id|lcopy_to_user
c_func
(paren
r_void
op_star
comma
r_const
r_void
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
r_int
id|lcopy_from_user
c_func
(paren
r_void
op_star
comma
r_const
r_void
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
id|lstrncpy_from_user
c_func
(paren
r_char
op_star
comma
r_const
r_char
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|lclear_user
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
id|lstrnlen_user
c_func
(paren
r_const
r_char
op_star
comma
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; * Complex access routines -- macros&n; */
DECL|macro|strncpy_from_user
mdefine_line|#define strncpy_from_user lstrncpy_from_user
DECL|macro|strnlen_user
mdefine_line|#define strnlen_user lstrnlen_user
DECL|macro|strlen_user
mdefine_line|#define strlen_user(str) lstrnlen_user(str, 0x7fffffffL)
DECL|macro|clear_user
mdefine_line|#define clear_user lclear_user
DECL|macro|__clear_user
mdefine_line|#define __clear_user lclear_user
DECL|macro|copy_from_user
mdefine_line|#define copy_from_user lcopy_from_user
DECL|macro|__copy_from_user
mdefine_line|#define __copy_from_user lcopy_from_user
DECL|macro|copy_to_user
mdefine_line|#define copy_to_user lcopy_to_user
DECL|macro|__copy_to_user
mdefine_line|#define __copy_to_user lcopy_to_user
macro_line|#endif /* __PARISC_UACCESS_H */
eof
