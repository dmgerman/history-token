macro_line|#ifndef __M68K_UACCESS_H
DECL|macro|__M68K_UACCESS_H
mdefine_line|#define __M68K_UACCESS_H
multiline_comment|/*&n; * User space memory access functions&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
DECL|macro|VERIFY_READ
mdefine_line|#define VERIFY_READ&t;0
DECL|macro|VERIFY_WRITE
mdefine_line|#define VERIFY_WRITE&t;1
multiline_comment|/* We let the MMU do all checking */
DECL|macro|access_ok
mdefine_line|#define access_ok(type,addr,size) 1
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
DECL|macro|put_user
mdefine_line|#define put_user(x, ptr)&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    int __pu_err;&t;&t;&t;&t;&t;&bslash;&n;    typeof(*(ptr)) __pu_val = (x);&t;&t;&t;&bslash;&n;    switch (sizeof (*(ptr))) {&t;&t;&t;&t;&bslash;&n;    case 1:&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__put_user_asm(__pu_err, __pu_val, ptr, b);&t;&bslash;&n;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;    case 2:&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__put_user_asm(__pu_err, __pu_val, ptr, w);&t;&bslash;&n;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;    case 4:&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__put_user_asm(__pu_err, __pu_val, ptr, l);&t;&bslash;&n;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;    case 8:                                             &bslash;&n;       __pu_err = __constant_copy_to_user(ptr, &amp;__pu_val, 8);        &bslash;&n;       break;                                           &bslash;&n;    default:&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__pu_err = __put_user_bad();&t;&t;&t;&bslash;&n;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;    }&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    __pu_err;&t;&t;&t;&t;&t;&t;&bslash;&n;})
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
DECL|macro|__put_user_asm
mdefine_line|#define __put_user_asm(err,x,ptr,bwl)&t;&t;&t;&bslash;&n;__asm__ __volatile__&t;&t;&t;&t;&t;&bslash;&n;    (&quot;21:moves&quot; #bwl &quot; %2,%1&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;     &quot;1:&bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;     &quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;     &quot;   .even&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;     &quot;2: movel %3,%0&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;     &quot;   jra 1b&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;     &quot;.previous&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;     &quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;&t;&t;&t;&bslash;&n;     &quot;   .align 4&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;     &quot;   .long 21b,2b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;     &quot;   .long 1b,2b&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;     &quot;.previous&quot;&t;&t;&t;&t;&t;&bslash;&n;     : &quot;=d&quot;(err)&t;&t;&t;&t;&t;&bslash;&n;     : &quot;m&quot;(*(ptr)), &quot;r&quot;(x), &quot;i&quot;(-EFAULT), &quot;0&quot;(0))
DECL|macro|get_user
mdefine_line|#define get_user(x, ptr)&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    int __gu_err;&t;&t;&t;&t;&t;&t;&bslash;&n;    typeof(*(ptr)) __gu_val;&t;&t;&t;&t;&t;&bslash;&n;    switch (sizeof(*(ptr))) {&t;&t;&t;&t;&t;&bslash;&n;    case 1:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__get_user_asm(__gu_err, __gu_val, ptr, b, &quot;=d&quot;);&t;&bslash;&n;&t;break;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    case 2:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__get_user_asm(__gu_err, __gu_val, ptr, w, &quot;=r&quot;);&t;&bslash;&n;&t;break;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    case 4:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__get_user_asm(__gu_err, __gu_val, ptr, l, &quot;=r&quot;);&t;&bslash;&n;&t;break;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    case 8:                                                     &bslash;&n;        __gu_err = __constant_copy_from_user(&amp;__gu_val, ptr, 8);  &bslash;&n;        break;                                                  &bslash;&n;    default:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__gu_val = 0;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__gu_err = __get_user_bad();&t;&t;&t;&t;&bslash;&n;&t;break;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    }&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    (x) = __gu_val;&t;&t;&t;&t;&t;&t;&bslash;&n;    __gu_err;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
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
DECL|macro|__get_user_asm
mdefine_line|#define __get_user_asm(err,x,ptr,bwl,reg)&t;&bslash;&n;__asm__ __volatile__&t;&t;&t;&t;&bslash;&n;    (&quot;1: moves&quot; #bwl &quot; %2,%1&bslash;n&quot;&t;&t;&t;&bslash;&n;     &quot;2:&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;     &quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;&t;&t;&t;&bslash;&n;     &quot;   .even&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;     &quot;3: movel %3,%0&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;     &quot;   sub&quot; #bwl &quot; %1,%1&bslash;n&quot;&t;&t;&t;&bslash;&n;     &quot;   jra 2b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;     &quot;.previous&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;     &quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;&t;&t;&bslash;&n;     &quot;   .align 4&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;     &quot;   .long 1b,3b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;     &quot;.previous&quot;&t;&t;&t;&t;&bslash;&n;     : &quot;=d&quot;(err), reg(x)&t;&t;&t;&bslash;&n;     : &quot;m&quot;(*(ptr)), &quot;i&quot; (-EFAULT), &quot;0&quot;(0))
r_static
r_inline
r_int
r_int
DECL|function|__generic_copy_from_user
id|__generic_copy_from_user
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
r_int
r_int
id|tmp
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;   tstl %2&bslash;n&quot;
l_string|&quot;   jeq 2f&bslash;n&quot;
l_string|&quot;1: movesl (%1)+,%3&bslash;n&quot;
l_string|&quot;   movel %3,(%0)+&bslash;n&quot;
l_string|&quot;   subql #1,%2&bslash;n&quot;
l_string|&quot;   jne 1b&bslash;n&quot;
l_string|&quot;2: movel %4,%2&bslash;n&quot;
l_string|&quot;   bclr #1,%2&bslash;n&quot;
l_string|&quot;   jeq 4f&bslash;n&quot;
l_string|&quot;3: movesw (%1)+,%3&bslash;n&quot;
l_string|&quot;   movew %3,(%0)+&bslash;n&quot;
l_string|&quot;4: bclr #0,%2&bslash;n&quot;
l_string|&quot;   jeq 6f&bslash;n&quot;
l_string|&quot;5: movesb (%1)+,%3&bslash;n&quot;
l_string|&quot;   moveb %3,(%0)+&bslash;n&quot;
l_string|&quot;6:&bslash;n&quot;
l_string|&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
l_string|&quot;   .even&bslash;n&quot;
l_string|&quot;7: movel %2,%%d0&bslash;n&quot;
l_string|&quot;71:clrl (%0)+&bslash;n&quot;
l_string|&quot;   subql #1,%%d0&bslash;n&quot;
l_string|&quot;   jne 71b&bslash;n&quot;
l_string|&quot;   lsll #2,%2&bslash;n&quot;
l_string|&quot;   addl %4,%2&bslash;n&quot;
l_string|&quot;   btst #1,%4&bslash;n&quot;
l_string|&quot;   jne 81f&bslash;n&quot;
l_string|&quot;   btst #0,%4&bslash;n&quot;
l_string|&quot;   jne 91f&bslash;n&quot;
l_string|&quot;   jra 6b&bslash;n&quot;
l_string|&quot;8: addql #2,%2&bslash;n&quot;
l_string|&quot;81:clrw (%0)+&bslash;n&quot;
l_string|&quot;   btst #0,%4&bslash;n&quot;
l_string|&quot;   jne 91f&bslash;n&quot;
l_string|&quot;   jra 6b&bslash;n&quot;
l_string|&quot;9: addql #1,%2&bslash;n&quot;
l_string|&quot;91:clrb (%0)+&bslash;n&quot;
l_string|&quot;   jra 6b&bslash;n&quot;
l_string|&quot;.previous&bslash;n&quot;
l_string|&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;
l_string|&quot;   .align 4&bslash;n&quot;
l_string|&quot;   .long 1b,7b&bslash;n&quot;
l_string|&quot;   .long 3b,8b&bslash;n&quot;
l_string|&quot;   .long 5b,9b&bslash;n&quot;
l_string|&quot;.previous&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|to
)paren
comma
l_string|&quot;=a&quot;
(paren
id|from
)paren
comma
l_string|&quot;=d&quot;
(paren
id|n
)paren
comma
l_string|&quot;=&amp;d&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|n
op_amp
l_int|3
)paren
comma
l_string|&quot;0&quot;
(paren
id|to
)paren
comma
l_string|&quot;1&quot;
(paren
id|from
)paren
comma
l_string|&quot;2&quot;
(paren
id|n
op_div
l_int|4
)paren
suffix:colon
l_string|&quot;d0&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|n
suffix:semicolon
)brace
r_static
r_inline
r_int
r_int
DECL|function|__generic_copy_to_user
id|__generic_copy_to_user
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
r_int
r_int
id|tmp
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;   tstl %2&bslash;n&quot;
l_string|&quot;   jeq 3f&bslash;n&quot;
l_string|&quot;1: movel (%1)+,%3&bslash;n&quot;
l_string|&quot;22:movesl %3,(%0)+&bslash;n&quot;
l_string|&quot;2: subql #1,%2&bslash;n&quot;
l_string|&quot;   jne 1b&bslash;n&quot;
l_string|&quot;3: movel %4,%2&bslash;n&quot;
l_string|&quot;   bclr #1,%2&bslash;n&quot;
l_string|&quot;   jeq 4f&bslash;n&quot;
l_string|&quot;   movew (%1)+,%3&bslash;n&quot;
l_string|&quot;24:movesw %3,(%0)+&bslash;n&quot;
l_string|&quot;4: bclr #0,%2&bslash;n&quot;
l_string|&quot;   jeq 5f&bslash;n&quot;
l_string|&quot;   moveb (%1)+,%3&bslash;n&quot;
l_string|&quot;25:movesb %3,(%0)+&bslash;n&quot;
l_string|&quot;5:&bslash;n&quot;
l_string|&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
l_string|&quot;   .even&bslash;n&quot;
l_string|&quot;60:addql #1,%2&bslash;n&quot;
l_string|&quot;6: lsll #2,%2&bslash;n&quot;
l_string|&quot;   addl %4,%2&bslash;n&quot;
l_string|&quot;   jra 5b&bslash;n&quot;
l_string|&quot;7: addql #2,%2&bslash;n&quot;
l_string|&quot;   jra 5b&bslash;n&quot;
l_string|&quot;8: addql #1,%2&bslash;n&quot;
l_string|&quot;   jra 5b&bslash;n&quot;
l_string|&quot;.previous&bslash;n&quot;
l_string|&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;
l_string|&quot;   .align 4&bslash;n&quot;
l_string|&quot;   .long 1b,60b&bslash;n&quot;
l_string|&quot;   .long 22b,6b&bslash;n&quot;
l_string|&quot;   .long 2b,6b&bslash;n&quot;
l_string|&quot;   .long 24b,7b&bslash;n&quot;
l_string|&quot;   .long 3b,60b&bslash;n&quot;
l_string|&quot;   .long 4b,7b&bslash;n&quot;
l_string|&quot;   .long 25b,8b&bslash;n&quot;
l_string|&quot;   .long 5b,8b&bslash;n&quot;
l_string|&quot;.previous&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|to
)paren
comma
l_string|&quot;=a&quot;
(paren
id|from
)paren
comma
l_string|&quot;=d&quot;
(paren
id|n
)paren
comma
l_string|&quot;=&amp;d&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|n
op_amp
l_int|3
)paren
comma
l_string|&quot;0&quot;
(paren
id|to
)paren
comma
l_string|&quot;1&quot;
(paren
id|from
)paren
comma
l_string|&quot;2&quot;
(paren
id|n
op_div
l_int|4
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|n
suffix:semicolon
)brace
DECL|macro|__copy_from_user_big
mdefine_line|#define __copy_from_user_big(to, from, n, fixup, copy)&t;&bslash;&n;    __asm__ __volatile__&t;&t;&t;&t;&bslash;&n;&t;(&quot;10: movesl (%1)+,%%d0&bslash;n&quot;&t;&t;&t;&bslash;&n;&t; &quot;    movel %%d0,(%0)+&bslash;n&quot;&t;&t;&t;&bslash;&n;&t; &quot;    subql #1,%2&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t; &quot;    jne 10b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t; &quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;&t;&t;&t;&bslash;&n;&t; &quot;    .even&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t; &quot;11: movel %2,%%d0&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t; &quot;13: clrl (%0)+&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t; &quot;    subql #1,%%d0&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t; &quot;    jne 13b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t; &quot;    lsll #2,%2&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t; fixup &quot;&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t; &quot;    jra 12f&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t; &quot;.previous&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t; &quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;&t;&t;&t;&bslash;&n;&t; &quot;    .align 4&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t; &quot;    .long 10b,11b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t; &quot;.previous&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t; copy &quot;&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t; &quot;12:&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t; : &quot;=a&quot;(to), &quot;=a&quot;(from), &quot;=d&quot;(n)&t;&t;&bslash;&n;&t; : &quot;0&quot;(to), &quot;1&quot;(from), &quot;2&quot;(n/4)&t;&t;&t;&bslash;&n;&t; : &quot;d0&quot;, &quot;memory&quot;)
r_static
r_inline
r_int
r_int
DECL|function|__constant_copy_from_user
id|__constant_copy_from_user
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
r_switch
c_cond
(paren
id|n
)paren
(brace
r_case
l_int|0
suffix:colon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|__asm__
id|__volatile__
(paren
l_string|&quot;1: movesb (%1)+,%%d0&bslash;n&quot;
l_string|&quot;   moveb %%d0,(%0)+&bslash;n&quot;
l_string|&quot;2:&bslash;n&quot;
l_string|&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
l_string|&quot;   .even&bslash;n&quot;
l_string|&quot;3: addql #1,%2&bslash;n&quot;
l_string|&quot;   clrb (%0)+&bslash;n&quot;
l_string|&quot;   jra 2b&bslash;n&quot;
l_string|&quot;.previous&bslash;n&quot;
l_string|&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;
l_string|&quot;   .align 4&bslash;n&quot;
l_string|&quot;   .long 1b,3b&bslash;n&quot;
l_string|&quot;.previous&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|to
)paren
comma
l_string|&quot;=a&quot;
(paren
id|from
)paren
comma
l_string|&quot;=d&quot;
(paren
id|n
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|to
)paren
comma
l_string|&quot;1&quot;
(paren
id|from
)paren
comma
l_string|&quot;2&quot;
(paren
l_int|0
)paren
suffix:colon
l_string|&quot;d0&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|__asm__
id|__volatile__
(paren
l_string|&quot;1: movesw (%1)+,%%d0&bslash;n&quot;
l_string|&quot;   movew %%d0,(%0)+&bslash;n&quot;
l_string|&quot;2:&bslash;n&quot;
l_string|&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
l_string|&quot;   .even&bslash;n&quot;
l_string|&quot;3: addql #2,%2&bslash;n&quot;
l_string|&quot;   clrw (%0)+&bslash;n&quot;
l_string|&quot;   jra 2b&bslash;n&quot;
l_string|&quot;.previous&bslash;n&quot;
l_string|&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;
l_string|&quot;   .align 4&bslash;n&quot;
l_string|&quot;   .long 1b,3b&bslash;n&quot;
l_string|&quot;.previous&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|to
)paren
comma
l_string|&quot;=a&quot;
(paren
id|from
)paren
comma
l_string|&quot;=d&quot;
(paren
id|n
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|to
)paren
comma
l_string|&quot;1&quot;
(paren
id|from
)paren
comma
l_string|&quot;2&quot;
(paren
l_int|0
)paren
suffix:colon
l_string|&quot;d0&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|__asm__
id|__volatile__
(paren
l_string|&quot;1: movesw (%1)+,%%d0&bslash;n&quot;
l_string|&quot;   movew %%d0,(%0)+&bslash;n&quot;
l_string|&quot;2: movesb (%1)+,%%d0&bslash;n&quot;
l_string|&quot;   moveb %%d0,(%0)+&bslash;n&quot;
l_string|&quot;3:&quot;
l_string|&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
l_string|&quot;   .even&bslash;n&quot;
l_string|&quot;4: addql #2,%2&bslash;n&quot;
l_string|&quot;   clrw (%0)+&bslash;n&quot;
l_string|&quot;5: addql #1,%2&bslash;n&quot;
l_string|&quot;   clrb (%0)+&bslash;n&quot;
l_string|&quot;   jra 3b&bslash;n&quot;
l_string|&quot;.previous&bslash;n&quot;
l_string|&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;
l_string|&quot;   .align 4&bslash;n&quot;
l_string|&quot;   .long 1b,4b&bslash;n&quot;
l_string|&quot;   .long 2b,5b&bslash;n&quot;
l_string|&quot;.previous&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|to
)paren
comma
l_string|&quot;=a&quot;
(paren
id|from
)paren
comma
l_string|&quot;=d&quot;
(paren
id|n
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|to
)paren
comma
l_string|&quot;1&quot;
(paren
id|from
)paren
comma
l_string|&quot;2&quot;
(paren
l_int|0
)paren
suffix:colon
l_string|&quot;d0&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|__asm__
id|__volatile__
(paren
l_string|&quot;1: movesl (%1)+,%%d0&bslash;n&quot;
l_string|&quot;   movel %%d0,(%0)+&bslash;n&quot;
l_string|&quot;2:&quot;
l_string|&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
l_string|&quot;   .even&bslash;n&quot;
l_string|&quot;3: addql #4,%2&bslash;n&quot;
l_string|&quot;   clrl (%0)+&bslash;n&quot;
l_string|&quot;   jra 2b&bslash;n&quot;
l_string|&quot;.previous&bslash;n&quot;
l_string|&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;
l_string|&quot;   .align 4&bslash;n&quot;
l_string|&quot;   .long 1b,3b&bslash;n&quot;
l_string|&quot;.previous&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|to
)paren
comma
l_string|&quot;=a&quot;
(paren
id|from
)paren
comma
l_string|&quot;=d&quot;
(paren
id|n
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|to
)paren
comma
l_string|&quot;1&quot;
(paren
id|from
)paren
comma
l_string|&quot;2&quot;
(paren
l_int|0
)paren
suffix:colon
l_string|&quot;d0&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|8
suffix:colon
id|__asm__
id|__volatile__
(paren
l_string|&quot;1: movesl (%1)+,%%d0&bslash;n&quot;
l_string|&quot;   movel %%d0,(%0)+&bslash;n&quot;
l_string|&quot;2: movesl (%1)+,%%d0&bslash;n&quot;
l_string|&quot;   movel %%d0,(%0)+&bslash;n&quot;
l_string|&quot;3:&quot;
l_string|&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
l_string|&quot;   .even&bslash;n&quot;
l_string|&quot;4: addql #4,%2&bslash;n&quot;
l_string|&quot;   clrl (%0)+&bslash;n&quot;
l_string|&quot;5: addql #4,%2&bslash;n&quot;
l_string|&quot;   clrl (%0)+&bslash;n&quot;
l_string|&quot;   jra 3b&bslash;n&quot;
l_string|&quot;.previous&bslash;n&quot;
l_string|&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;
l_string|&quot;   .align 4&bslash;n&quot;
l_string|&quot;   .long 1b,4b&bslash;n&quot;
l_string|&quot;   .long 2b,5b&bslash;n&quot;
l_string|&quot;.previous&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|to
)paren
comma
l_string|&quot;=a&quot;
(paren
id|from
)paren
comma
l_string|&quot;=d&quot;
(paren
id|n
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|to
)paren
comma
l_string|&quot;1&quot;
(paren
id|from
)paren
comma
l_string|&quot;2&quot;
(paren
l_int|0
)paren
suffix:colon
l_string|&quot;d0&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|12
suffix:colon
id|__asm__
id|__volatile__
(paren
l_string|&quot;1: movesl (%1)+,%%d0&bslash;n&quot;
l_string|&quot;   movel %%d0,(%0)+&bslash;n&quot;
l_string|&quot;2: movesl (%1)+,%%d0&bslash;n&quot;
l_string|&quot;   movel %%d0,(%0)+&bslash;n&quot;
l_string|&quot;3: movesl (%1)+,%%d0&bslash;n&quot;
l_string|&quot;   movel %%d0,(%0)+&bslash;n&quot;
l_string|&quot;4:&quot;
l_string|&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
l_string|&quot;   .even&bslash;n&quot;
l_string|&quot;5: addql #4,%2&bslash;n&quot;
l_string|&quot;   clrl (%0)+&bslash;n&quot;
l_string|&quot;6: addql #4,%2&bslash;n&quot;
l_string|&quot;   clrl (%0)+&bslash;n&quot;
l_string|&quot;7: addql #4,%2&bslash;n&quot;
l_string|&quot;   clrl (%0)+&bslash;n&quot;
l_string|&quot;   jra 4b&bslash;n&quot;
l_string|&quot;.previous&bslash;n&quot;
l_string|&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;
l_string|&quot;   .align 4&bslash;n&quot;
l_string|&quot;   .long 1b,5b&bslash;n&quot;
l_string|&quot;   .long 2b,6b&bslash;n&quot;
l_string|&quot;   .long 3b,7b&bslash;n&quot;
l_string|&quot;.previous&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|to
)paren
comma
l_string|&quot;=a&quot;
(paren
id|from
)paren
comma
l_string|&quot;=d&quot;
(paren
id|n
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|to
)paren
comma
l_string|&quot;1&quot;
(paren
id|from
)paren
comma
l_string|&quot;2&quot;
(paren
l_int|0
)paren
suffix:colon
l_string|&quot;d0&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|16
suffix:colon
id|__asm__
id|__volatile__
(paren
l_string|&quot;1: movesl (%1)+,%%d0&bslash;n&quot;
l_string|&quot;   movel %%d0,(%0)+&bslash;n&quot;
l_string|&quot;2: movesl (%1)+,%%d0&bslash;n&quot;
l_string|&quot;   movel %%d0,(%0)+&bslash;n&quot;
l_string|&quot;3: movesl (%1)+,%%d0&bslash;n&quot;
l_string|&quot;   movel %%d0,(%0)+&bslash;n&quot;
l_string|&quot;4: movesl (%1)+,%%d0&bslash;n&quot;
l_string|&quot;   movel %%d0,(%0)+&bslash;n&quot;
l_string|&quot;5:&quot;
l_string|&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
l_string|&quot;   .even&bslash;n&quot;
l_string|&quot;6: addql #4,%2&bslash;n&quot;
l_string|&quot;   clrl (%0)+&bslash;n&quot;
l_string|&quot;7: addql #4,%2&bslash;n&quot;
l_string|&quot;   clrl (%0)+&bslash;n&quot;
l_string|&quot;8: addql #4,%2&bslash;n&quot;
l_string|&quot;   clrl (%0)+&bslash;n&quot;
l_string|&quot;9: addql #4,%2&bslash;n&quot;
l_string|&quot;   clrl (%0)+&bslash;n&quot;
l_string|&quot;   jra 5b&bslash;n&quot;
l_string|&quot;.previous&bslash;n&quot;
l_string|&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;
l_string|&quot;   .align 4&bslash;n&quot;
l_string|&quot;   .long 1b,6b&bslash;n&quot;
l_string|&quot;   .long 2b,7b&bslash;n&quot;
l_string|&quot;   .long 3b,8b&bslash;n&quot;
l_string|&quot;   .long 4b,9b&bslash;n&quot;
l_string|&quot;.previous&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|to
)paren
comma
l_string|&quot;=a&quot;
(paren
id|from
)paren
comma
l_string|&quot;=d&quot;
(paren
id|n
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|to
)paren
comma
l_string|&quot;1&quot;
(paren
id|from
)paren
comma
l_string|&quot;2&quot;
(paren
l_int|0
)paren
suffix:colon
l_string|&quot;d0&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
(brace
)brace
r_switch
c_cond
(paren
id|n
op_amp
l_int|3
)paren
(brace
r_case
l_int|0
suffix:colon
id|__copy_from_user_big
c_func
(paren
id|to
comma
id|from
comma
id|n
comma
l_string|&quot;&quot;
comma
l_string|&quot;&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|__copy_from_user_big
c_func
(paren
id|to
comma
id|from
comma
id|n
comma
multiline_comment|/* fixup */
l_string|&quot;1: addql #1,%2&bslash;n&quot;
l_string|&quot;   clrb (%0)+&quot;
comma
multiline_comment|/* copy */
l_string|&quot;2: movesb (%1)+,%%d0&bslash;n&quot;
l_string|&quot;   moveb %%d0,(%0)+&bslash;n&quot;
l_string|&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;
l_string|&quot;   .long 2b,1b&bslash;n&quot;
l_string|&quot;.previous&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|__copy_from_user_big
c_func
(paren
id|to
comma
id|from
comma
id|n
comma
multiline_comment|/* fixup */
l_string|&quot;1: addql #2,%2&bslash;n&quot;
l_string|&quot;   clrw (%0)+&quot;
comma
multiline_comment|/* copy */
l_string|&quot;2: movesw (%1)+,%%d0&bslash;n&quot;
l_string|&quot;   movew %%d0,(%0)+&bslash;n&quot;
l_string|&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;
l_string|&quot;   .long 2b,1b&bslash;n&quot;
l_string|&quot;.previous&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|__copy_from_user_big
c_func
(paren
id|to
comma
id|from
comma
id|n
comma
multiline_comment|/* fixup */
l_string|&quot;1: addql #2,%2&bslash;n&quot;
l_string|&quot;   clrw (%0)+&bslash;n&quot;
l_string|&quot;2: addql #1,%2&bslash;n&quot;
l_string|&quot;   clrb (%0)+&quot;
comma
multiline_comment|/* copy */
l_string|&quot;3: movesw (%1)+,%%d0&bslash;n&quot;
l_string|&quot;   movew %%d0,(%0)+&bslash;n&quot;
l_string|&quot;4: movesb (%1)+,%%d0&bslash;n&quot;
l_string|&quot;   moveb %%d0,(%0)+&bslash;n&quot;
l_string|&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;
l_string|&quot;   .long 3b,1b&bslash;n&quot;
l_string|&quot;   .long 4b,2b&bslash;n&quot;
l_string|&quot;.previous&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
r_return
id|n
suffix:semicolon
)brace
DECL|macro|__copy_to_user_big
mdefine_line|#define __copy_to_user_big(to, from, n, fixup, copy)&t;&bslash;&n;    __asm__ __volatile__&t;&t;&t;&t;&bslash;&n;&t;(&quot;10: movel (%1)+,%%d0&bslash;n&quot;&t;&t;&t;&bslash;&n;&t; &quot;31: movesl %%d0,(%0)+&bslash;n&quot;&t;&t;&t;&bslash;&n;&t; &quot;11: subql #1,%2&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t; &quot;    jne 10b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t; &quot;41:&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t; &quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;&t;&t;&t;&bslash;&n;&t; &quot;   .even&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t; &quot;22: addql #1,%2&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t; &quot;12: lsll #2,%2&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t; fixup &quot;&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t; &quot;    jra 13f&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t; &quot;.previous&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t; &quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;&t;&t;&t;&bslash;&n;&t; &quot;    .align 4&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t; &quot;    .long 10b,22b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t; &quot;    .long 31b,12b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t; &quot;    .long 11b,12b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t; &quot;    .long 41b,22b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t; &quot;.previous&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t; copy &quot;&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t; &quot;13:&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t; : &quot;=a&quot;(to), &quot;=a&quot;(from), &quot;=d&quot;(n)&t;&t;&bslash;&n;&t; : &quot;0&quot;(to), &quot;1&quot;(from), &quot;2&quot;(n/4)&t;&t;&t;&bslash;&n;&t; : &quot;d0&quot;, &quot;memory&quot;)
r_static
r_inline
r_int
r_int
DECL|function|__constant_copy_to_user
id|__constant_copy_to_user
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
r_switch
c_cond
(paren
id|n
)paren
(brace
r_case
l_int|0
suffix:colon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|__asm__
id|__volatile__
(paren
l_string|&quot;   moveb (%1)+,%%d0&bslash;n&quot;
l_string|&quot;21:movesb %%d0,(%0)+&bslash;n&quot;
l_string|&quot;1:&bslash;n&quot;
l_string|&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
l_string|&quot;   .even&bslash;n&quot;
l_string|&quot;2: addql #1,%2&bslash;n&quot;
l_string|&quot;   jra 1b&bslash;n&quot;
l_string|&quot;.previous&bslash;n&quot;
l_string|&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;
l_string|&quot;   .align 4&bslash;n  &quot;
l_string|&quot;   .long 21b,2b&bslash;n&quot;
l_string|&quot;   .long 1b,2b&bslash;n&quot;
l_string|&quot;.previous&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|to
)paren
comma
l_string|&quot;=a&quot;
(paren
id|from
)paren
comma
l_string|&quot;=d&quot;
(paren
id|n
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|to
)paren
comma
l_string|&quot;1&quot;
(paren
id|from
)paren
comma
l_string|&quot;2&quot;
(paren
l_int|0
)paren
suffix:colon
l_string|&quot;d0&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|__asm__
id|__volatile__
(paren
l_string|&quot;   movew (%1)+,%%d0&bslash;n&quot;
l_string|&quot;21:movesw %%d0,(%0)+&bslash;n&quot;
l_string|&quot;1:&bslash;n&quot;
l_string|&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
l_string|&quot;   .even&bslash;n&quot;
l_string|&quot;2: addql #2,%2&bslash;n&quot;
l_string|&quot;   jra 1b&bslash;n&quot;
l_string|&quot;.previous&bslash;n&quot;
l_string|&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;
l_string|&quot;   .align 4&bslash;n&quot;
l_string|&quot;   .long 21b,2b&bslash;n&quot;
l_string|&quot;   .long 1b,2b&bslash;n&quot;
l_string|&quot;.previous&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|to
)paren
comma
l_string|&quot;=a&quot;
(paren
id|from
)paren
comma
l_string|&quot;=d&quot;
(paren
id|n
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|to
)paren
comma
l_string|&quot;1&quot;
(paren
id|from
)paren
comma
l_string|&quot;2&quot;
(paren
l_int|0
)paren
suffix:colon
l_string|&quot;d0&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|__asm__
id|__volatile__
(paren
l_string|&quot;   movew (%1)+,%%d0&bslash;n&quot;
l_string|&quot;21:movesw %%d0,(%0)+&bslash;n&quot;
l_string|&quot;1: moveb (%1)+,%%d0&bslash;n&quot;
l_string|&quot;22:movesb %%d0,(%0)+&bslash;n&quot;
l_string|&quot;2:&bslash;n&quot;
l_string|&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
l_string|&quot;   .even&bslash;n&quot;
l_string|&quot;3: addql #2,%2&bslash;n&quot;
l_string|&quot;4: addql #1,%2&bslash;n&quot;
l_string|&quot;   jra 2b&bslash;n&quot;
l_string|&quot;.previous&bslash;n&quot;
l_string|&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;
l_string|&quot;   .align 4&bslash;n&quot;
l_string|&quot;   .long 21b,3b&bslash;n&quot;
l_string|&quot;   .long 1b,3b&bslash;n&quot;
l_string|&quot;   .long 22b,4b&bslash;n&quot;
l_string|&quot;   .long 2b,4b&bslash;n&quot;
l_string|&quot;.previous&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|to
)paren
comma
l_string|&quot;=a&quot;
(paren
id|from
)paren
comma
l_string|&quot;=d&quot;
(paren
id|n
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|to
)paren
comma
l_string|&quot;1&quot;
(paren
id|from
)paren
comma
l_string|&quot;2&quot;
(paren
l_int|0
)paren
suffix:colon
l_string|&quot;d0&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|__asm__
id|__volatile__
(paren
l_string|&quot;   movel (%1)+,%%d0&bslash;n&quot;
l_string|&quot;21:movesl %%d0,(%0)+&bslash;n&quot;
l_string|&quot;1:&bslash;n&quot;
l_string|&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
l_string|&quot;   .even&bslash;n&quot;
l_string|&quot;2: addql #4,%2&bslash;n&quot;
l_string|&quot;   jra 1b&bslash;n&quot;
l_string|&quot;.previous&bslash;n&quot;
l_string|&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;
l_string|&quot;   .align 4&bslash;n&quot;
l_string|&quot;   .long 21b,2b&bslash;n&quot;
l_string|&quot;   .long 1b,2b&bslash;n&quot;
l_string|&quot;.previous&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|to
)paren
comma
l_string|&quot;=a&quot;
(paren
id|from
)paren
comma
l_string|&quot;=d&quot;
(paren
id|n
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|to
)paren
comma
l_string|&quot;1&quot;
(paren
id|from
)paren
comma
l_string|&quot;2&quot;
(paren
l_int|0
)paren
suffix:colon
l_string|&quot;d0&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|8
suffix:colon
id|__asm__
id|__volatile__
(paren
l_string|&quot;   movel (%1)+,%%d0&bslash;n&quot;
l_string|&quot;21:movesl %%d0,(%0)+&bslash;n&quot;
l_string|&quot;1: movel (%1)+,%%d0&bslash;n&quot;
l_string|&quot;22:movesl %%d0,(%0)+&bslash;n&quot;
l_string|&quot;2:&bslash;n&quot;
l_string|&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
l_string|&quot;   .even&bslash;n&quot;
l_string|&quot;3: addql #4,%2&bslash;n&quot;
l_string|&quot;4: addql #4,%2&bslash;n&quot;
l_string|&quot;   jra 2b&bslash;n&quot;
l_string|&quot;.previous&bslash;n&quot;
l_string|&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;
l_string|&quot;   .align 4&bslash;n&quot;
l_string|&quot;   .long 21b,3b&bslash;n&quot;
l_string|&quot;   .long 1b,3b&bslash;n&quot;
l_string|&quot;   .long 22b,4b&bslash;n&quot;
l_string|&quot;   .long 2b,4b&bslash;n&quot;
l_string|&quot;.previous&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|to
)paren
comma
l_string|&quot;=a&quot;
(paren
id|from
)paren
comma
l_string|&quot;=d&quot;
(paren
id|n
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|to
)paren
comma
l_string|&quot;1&quot;
(paren
id|from
)paren
comma
l_string|&quot;2&quot;
(paren
l_int|0
)paren
suffix:colon
l_string|&quot;d0&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|12
suffix:colon
id|__asm__
id|__volatile__
(paren
l_string|&quot;   movel (%1)+,%%d0&bslash;n&quot;
l_string|&quot;21:movesl %%d0,(%0)+&bslash;n&quot;
l_string|&quot;1: movel (%1)+,%%d0&bslash;n&quot;
l_string|&quot;22:movesl %%d0,(%0)+&bslash;n&quot;
l_string|&quot;2: movel (%1)+,%%d0&bslash;n&quot;
l_string|&quot;23:movesl %%d0,(%0)+&bslash;n&quot;
l_string|&quot;3:&bslash;n&quot;
l_string|&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
l_string|&quot;   .even&bslash;n&quot;
l_string|&quot;4: addql #4,%2&bslash;n&quot;
l_string|&quot;5: addql #4,%2&bslash;n&quot;
l_string|&quot;6: addql #4,%2&bslash;n&quot;
l_string|&quot;   jra 3b&bslash;n&quot;
l_string|&quot;.previous&bslash;n&quot;
l_string|&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;
l_string|&quot;   .align 4&bslash;n&quot;
l_string|&quot;   .long 21b,4b&bslash;n&quot;
l_string|&quot;   .long 1b,4b&bslash;n&quot;
l_string|&quot;   .long 22b,5b&bslash;n&quot;
l_string|&quot;   .long 2b,5b&bslash;n&quot;
l_string|&quot;   .long 23b,6b&bslash;n&quot;
l_string|&quot;   .long 3b,6b&bslash;n&quot;
l_string|&quot;.previous&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|to
)paren
comma
l_string|&quot;=a&quot;
(paren
id|from
)paren
comma
l_string|&quot;=d&quot;
(paren
id|n
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|to
)paren
comma
l_string|&quot;1&quot;
(paren
id|from
)paren
comma
l_string|&quot;2&quot;
(paren
l_int|0
)paren
suffix:colon
l_string|&quot;d0&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|16
suffix:colon
id|__asm__
id|__volatile__
(paren
l_string|&quot;   movel (%1)+,%%d0&bslash;n&quot;
l_string|&quot;21:movesl %%d0,(%0)+&bslash;n&quot;
l_string|&quot;1: movel (%1)+,%%d0&bslash;n&quot;
l_string|&quot;22:movesl %%d0,(%0)+&bslash;n&quot;
l_string|&quot;2: movel (%1)+,%%d0&bslash;n&quot;
l_string|&quot;23:movesl %%d0,(%0)+&bslash;n&quot;
l_string|&quot;3: movel (%1)+,%%d0&bslash;n&quot;
l_string|&quot;24:movesl %%d0,(%0)+&bslash;n&quot;
l_string|&quot;4:&quot;
l_string|&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
l_string|&quot;   .even&bslash;n&quot;
l_string|&quot;5: addql #4,%2&bslash;n&quot;
l_string|&quot;6: addql #4,%2&bslash;n&quot;
l_string|&quot;7: addql #4,%2&bslash;n&quot;
l_string|&quot;8: addql #4,%2&bslash;n&quot;
l_string|&quot;   jra 4b&bslash;n&quot;
l_string|&quot;.previous&bslash;n&quot;
l_string|&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;
l_string|&quot;   .align 4&bslash;n&quot;
l_string|&quot;   .long 21b,5b&bslash;n&quot;
l_string|&quot;   .long 1b,5b&bslash;n&quot;
l_string|&quot;   .long 22b,6b&bslash;n&quot;
l_string|&quot;   .long 2b,6b&bslash;n&quot;
l_string|&quot;   .long 23b,7b&bslash;n&quot;
l_string|&quot;   .long 3b,7b&bslash;n&quot;
l_string|&quot;   .long 24b,8b&bslash;n&quot;
l_string|&quot;   .long 4b,8b&bslash;n&quot;
l_string|&quot;.previous&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|to
)paren
comma
l_string|&quot;=a&quot;
(paren
id|from
)paren
comma
l_string|&quot;=d&quot;
(paren
id|n
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|to
)paren
comma
l_string|&quot;1&quot;
(paren
id|from
)paren
comma
l_string|&quot;2&quot;
(paren
l_int|0
)paren
suffix:colon
l_string|&quot;d0&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
(brace
)brace
r_switch
c_cond
(paren
id|n
op_amp
l_int|3
)paren
(brace
r_case
l_int|0
suffix:colon
id|__copy_to_user_big
c_func
(paren
id|to
comma
id|from
comma
id|n
comma
l_string|&quot;&quot;
comma
l_string|&quot;&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|__copy_to_user_big
c_func
(paren
id|to
comma
id|from
comma
id|n
comma
multiline_comment|/* fixup */
l_string|&quot;1: addql #1,%2&quot;
comma
multiline_comment|/* copy */
l_string|&quot;   moveb (%1)+,%%d0&bslash;n&quot;
l_string|&quot;22:movesb %%d0,(%0)+&bslash;n&quot;
l_string|&quot;2:&quot;
l_string|&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;
l_string|&quot;   .long 22b,1b&bslash;n&quot;
l_string|&quot;   .long 2b,1b&bslash;n&quot;
l_string|&quot;.previous&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|__copy_to_user_big
c_func
(paren
id|to
comma
id|from
comma
id|n
comma
multiline_comment|/* fixup */
l_string|&quot;1: addql #2,%2&quot;
comma
multiline_comment|/* copy */
l_string|&quot;   movew (%1)+,%%d0&bslash;n&quot;
l_string|&quot;22:movesw %%d0,(%0)+&bslash;n&quot;
l_string|&quot;2:&quot;
l_string|&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;
l_string|&quot;   .long 22b,1b&bslash;n&quot;
l_string|&quot;   .long 2b,1b&bslash;n&quot;
l_string|&quot;.previous&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|__copy_to_user_big
c_func
(paren
id|to
comma
id|from
comma
id|n
comma
multiline_comment|/* fixup */
l_string|&quot;1: addql #2,%2&bslash;n&quot;
l_string|&quot;2: addql #1,%2&quot;
comma
multiline_comment|/* copy */
l_string|&quot;   movew (%1)+,%%d0&bslash;n&quot;
l_string|&quot;23:movesw %%d0,(%0)+&bslash;n&quot;
l_string|&quot;3: moveb (%1)+,%%d0&bslash;n&quot;
l_string|&quot;24:movesb %%d0,(%0)+&bslash;n&quot;
l_string|&quot;4:&quot;
l_string|&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;
l_string|&quot;   .long 23b,1b&bslash;n&quot;
l_string|&quot;   .long 3b,1b&bslash;n&quot;
l_string|&quot;   .long 24b,2b&bslash;n&quot;
l_string|&quot;   .long 4b,2b&bslash;n&quot;
l_string|&quot;.previous&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
r_return
id|n
suffix:semicolon
)brace
DECL|macro|copy_from_user
mdefine_line|#define copy_from_user(to, from, n)&t;&t;&bslash;&n;(__builtin_constant_p(n) ?&t;&t;&t;&bslash;&n; __constant_copy_from_user(to, from, n) :&t;&bslash;&n; __generic_copy_from_user(to, from, n))
DECL|macro|copy_to_user
mdefine_line|#define copy_to_user(to, from, n)&t;&t;&bslash;&n;(__builtin_constant_p(n) ?&t;&t;&t;&bslash;&n; __constant_copy_to_user(to, from, n) :&t;&t;&bslash;&n; __generic_copy_to_user(to, from, n))
DECL|macro|__copy_from_user
mdefine_line|#define __copy_from_user(to, from, n) copy_from_user(to, from, n)
DECL|macro|__copy_to_user
mdefine_line|#define __copy_to_user(to, from, n) copy_to_user(to, from, n)
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
r_int
id|res
suffix:semicolon
r_if
c_cond
(paren
id|count
op_eq
l_int|0
)paren
r_return
id|count
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;1: movesb (%2)+,%%d0&bslash;n&quot;
l_string|&quot;12:moveb %%d0,(%1)+&bslash;n&quot;
l_string|&quot;   jeq 2f&bslash;n&quot;
l_string|&quot;   subql #1,%3&bslash;n&quot;
l_string|&quot;   jne 1b&bslash;n&quot;
l_string|&quot;2: subl %3,%0&bslash;n&quot;
l_string|&quot;3:&bslash;n&quot;
l_string|&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
l_string|&quot;   .even&bslash;n&quot;
l_string|&quot;4: movel %4,%0&bslash;n&quot;
l_string|&quot;   jra 3b&bslash;n&quot;
l_string|&quot;.previous&bslash;n&quot;
l_string|&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;
l_string|&quot;   .align 4&bslash;n&quot;
l_string|&quot;   .long 1b,4b&bslash;n&quot;
l_string|&quot;   .long 12b,4b&bslash;n&quot;
l_string|&quot;.previous&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|res
)paren
comma
l_string|&quot;=a&quot;
(paren
id|dst
)paren
comma
l_string|&quot;=a&quot;
(paren
id|src
)paren
comma
l_string|&quot;=d&quot;
(paren
id|count
)paren
suffix:colon
l_string|&quot;i&quot;
(paren
op_minus
id|EFAULT
)paren
comma
l_string|&quot;0&quot;
(paren
id|count
)paren
comma
l_string|&quot;1&quot;
(paren
id|dst
)paren
comma
l_string|&quot;2&quot;
(paren
id|src
)paren
comma
l_string|&quot;3&quot;
(paren
id|count
)paren
suffix:colon
l_string|&quot;d0&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
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
r_int
id|res
suffix:semicolon
id|res
op_assign
op_minus
(paren
r_int
)paren
id|src
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;1:&bslash;n&quot;
l_string|&quot;   tstl %2&bslash;n&quot;
l_string|&quot;   jeq 3f&bslash;n&quot;
l_string|&quot;2: movesb (%1)+,%%d0&bslash;n&quot;
l_string|&quot;22:&bslash;n&quot;
l_string|&quot;   subql #1,%2&bslash;n&quot;
l_string|&quot;   tstb %%d0&bslash;n&quot;
l_string|&quot;   jne 1b&bslash;n&quot;
l_string|&quot;   jra 4f&bslash;n&quot;
l_string|&quot;3:&bslash;n&quot;
l_string|&quot;   addql #1,%0&bslash;n&quot;
l_string|&quot;4:&bslash;n&quot;
l_string|&quot;   addl %1,%0&bslash;n&quot;
l_string|&quot;5:&bslash;n&quot;
l_string|&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
l_string|&quot;   .even&bslash;n&quot;
l_string|&quot;6: moveq %3,%0&bslash;n&quot;
l_string|&quot;   jra 5b&bslash;n&quot;
l_string|&quot;.previous&bslash;n&quot;
l_string|&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;
l_string|&quot;   .align 4&bslash;n&quot;
l_string|&quot;   .long 2b,6b&bslash;n&quot;
l_string|&quot;   .long 22b,6b&bslash;n&quot;
l_string|&quot;.previous&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|res
)paren
comma
l_string|&quot;=a&quot;
(paren
id|src
)paren
comma
l_string|&quot;=d&quot;
(paren
id|n
)paren
suffix:colon
l_string|&quot;i&quot;
(paren
l_int|0
)paren
comma
l_string|&quot;0&quot;
(paren
id|res
)paren
comma
l_string|&quot;1&quot;
(paren
id|src
)paren
comma
l_string|&quot;2&quot;
(paren
id|n
)paren
suffix:colon
l_string|&quot;d0&quot;
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
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
id|__asm__
id|__volatile__
(paren
l_string|&quot;   tstl %1&bslash;n&quot;
l_string|&quot;   jeq 3f&bslash;n&quot;
l_string|&quot;1: movesl %3,(%0)+&bslash;n&quot;
l_string|&quot;2: subql #1,%1&bslash;n&quot;
l_string|&quot;   jne 1b&bslash;n&quot;
l_string|&quot;3: movel %2,%1&bslash;n&quot;
l_string|&quot;   bclr #1,%1&bslash;n&quot;
l_string|&quot;   jeq 4f&bslash;n&quot;
l_string|&quot;24:movesw %3,(%0)+&bslash;n&quot;
l_string|&quot;4: bclr #0,%1&bslash;n&quot;
l_string|&quot;   jeq 5f&bslash;n&quot;
l_string|&quot;25:movesb %3,(%0)+&bslash;n&quot;
l_string|&quot;5:&bslash;n&quot;
l_string|&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
l_string|&quot;   .even&bslash;n&quot;
l_string|&quot;61:addql #1,%1&bslash;n&quot;
l_string|&quot;6: lsll #2,%1&bslash;n&quot;
l_string|&quot;   addl %2,%1&bslash;n&quot;
l_string|&quot;   jra 5b&bslash;n&quot;
l_string|&quot;7: addql #2,%1&bslash;n&quot;
l_string|&quot;   jra 5b&bslash;n&quot;
l_string|&quot;8: addql #1,%1&bslash;n&quot;
l_string|&quot;   jra 5b&bslash;n&quot;
l_string|&quot;.previous&bslash;n&quot;
l_string|&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;
l_string|&quot;   .align 4&bslash;n&quot;
l_string|&quot;   .long 1b,61b&bslash;n&quot;
l_string|&quot;   .long 2b,6b&bslash;n&quot;
l_string|&quot;   .long 3b,61b&bslash;n&quot;
l_string|&quot;   .long 24b,7b&bslash;n&quot;
l_string|&quot;   .long 4b,7b&bslash;n&quot;
l_string|&quot;   .long 25b,8b&bslash;n&quot;
l_string|&quot;   .long 5b,8b&bslash;n&quot;
l_string|&quot;.previous&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|to
)paren
comma
l_string|&quot;=d&quot;
(paren
id|n
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|n
op_amp
l_int|3
)paren
comma
l_string|&quot;r&quot;
(paren
l_int|0
)paren
comma
l_string|&quot;0&quot;
(paren
id|to
)paren
comma
l_string|&quot;1&quot;
(paren
id|n
op_div
l_int|4
)paren
)paren
suffix:semicolon
r_return
id|n
suffix:semicolon
)brace
macro_line|#endif /* _M68K_UACCESS_H */
eof
