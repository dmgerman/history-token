multiline_comment|/* &n; * Authors:    Bjorn Wesen (bjornw@axis.com)&n; *&t;       Hans-Peter Nilsson (hp@axis.com)&n; *&n; */
macro_line|#ifndef _CRIS_ARCH_UACCESS_H
DECL|macro|_CRIS_ARCH_UACCESS_H
mdefine_line|#define _CRIS_ARCH_UACCESS_H
multiline_comment|/*&n; * We don&squot;t tell gcc that we are accessing memory, but this is OK&n; * because we do not write to any memory gcc knows about, so there&n; * are no aliasing issues.&n; *&n; * Note that PC at a fault is the address *after* the faulting&n; * instruction.&n; */
DECL|macro|__put_user_asm
mdefine_line|#define __put_user_asm(x, addr, err, op)&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;&quot;op&quot; %1,[%2]&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;2:&bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&quot;3:&t;move.d %3,%0&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;jump 2b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.previous&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&quot;&t;.dword 2b,3b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.previous&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=r&quot; (err)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;r&quot; (x), &quot;r&quot; (addr), &quot;g&quot; (-EFAULT), &quot;0&quot; (err))
DECL|macro|__put_user_asm_64
mdefine_line|#define __put_user_asm_64(x, addr, err)&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;move.d %M1,[%2]&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;2:&t;move.d %H1,[%2+4]&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;4:&bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&quot;3:&t;move.d %3,%0&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;jump 4b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.previous&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&quot;&t;.dword 2b,3b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.dword 4b,3b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.previous&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=r&quot; (err)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;r&quot; (x), &quot;r&quot; (addr), &quot;g&quot; (-EFAULT), &quot;0&quot; (err))
multiline_comment|/* See comment before __put_user_asm.  */
DECL|macro|__get_user_asm
mdefine_line|#define __get_user_asm(x, addr, err, op)&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;&quot;op&quot; [%2],%1&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;2:&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;&t;&bslash;&n;&t;&t;&quot;3:&t;move.d %3,%0&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;moveq 0,%1&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;jump 2b&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.previous&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;&t;&bslash;&n;&t;&t;&quot;&t;.dword 2b,3b&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.previous&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=r&quot; (err), &quot;=r&quot; (x)&t;&t;&t;&bslash;&n;&t;&t;: &quot;r&quot; (addr), &quot;g&quot; (-EFAULT), &quot;0&quot; (err))
DECL|macro|__get_user_asm_64
mdefine_line|#define __get_user_asm_64(x, addr, err)&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;move.d [%2],%M1&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&quot;2:&t;move.d [%2+4],%H1&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&quot;4:&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;&t;&bslash;&n;&t;&t;&quot;3:&t;move.d %3,%0&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;moveq 0,%1&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;jump 4b&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.previous&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;&t;&bslash;&n;&t;&t;&quot;&t;.dword 2b,3b&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.dword 4b,3b&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.previous&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=r&quot; (err), &quot;=r&quot; (x)&t;&t;&t;&bslash;&n;&t;&t;: &quot;r&quot; (addr), &quot;g&quot; (-EFAULT), &quot;0&quot; (err))
multiline_comment|/*&n; * Copy a null terminated string from userspace.&n; *&n; * Must return:&n; * -EFAULT&t;&t;for an exception&n; * count&t;&t;if we hit the buffer limit&n; * bytes copied&t;&t;if we hit a null byte&n; * (without the null byte)&n; */
r_extern
r_inline
r_int
DECL|function|__do_strncpy_from_user
id|__do_strncpy_from_user
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
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * Currently, in 2.4.0-test9, most ports use a simple byte-copy loop.&n;&t; *  So do we.&n;&t; *&n;&t; *  This code is deduced from:&n;&t; *&n;&t; *&t;char tmp2;&n;&t; *&t;long tmp1, tmp3&t;&n;&t; *&t;tmp1 = count;&n;&t; *&t;while ((*dst++ = (tmp2 = *src++)) != 0&n;&t; *&t;       &amp;&amp; --tmp1)&n;&t; *&t;  ;&n;&t; *&n;&t; *&t;res = count - tmp1;&n;&t; *&n;&t; *  with tweaks.&n;&t; */
id|__asm__
id|__volatile__
(paren
l_string|&quot;&t;move.d %3,%0&bslash;n&quot;
l_string|&quot;&t;move.b [%2+],$r9&bslash;n&quot;
l_string|&quot;1:&t;beq 2f&bslash;n&quot;
l_string|&quot;&t;move.b $r9,[%1+]&bslash;n&quot;
l_string|&quot;&t;subq 1,%0&bslash;n&quot;
l_string|&quot;&t;bne 1b&bslash;n&quot;
l_string|&quot;&t;move.b [%2+],$r9&bslash;n&quot;
l_string|&quot;2:&t;sub.d %3,%0&bslash;n&quot;
l_string|&quot;&t;neg.d %0,%0&bslash;n&quot;
l_string|&quot;3:&bslash;n&quot;
l_string|&quot;&t;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
l_string|&quot;4:&t;move.d %7,%0&bslash;n&quot;
l_string|&quot;&t;jump 3b&bslash;n&quot;
multiline_comment|/* There&squot;s one address for a fault at the first move, and&n;&t;&t;   two possible PC values for a fault at the second move,&n;&t;&t;   being a delay-slot filler.  However, the branch-target&n;&t;&t;   for the second move is the same as the first address.&n;&t;&t;   Just so you don&squot;t get confused...  */
l_string|&quot;&t;.previous&bslash;n&quot;
l_string|&quot;&t;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;
l_string|&quot;&t;.dword 1b,4b&bslash;n&quot;
l_string|&quot;&t;.dword 2b,4b&bslash;n&quot;
l_string|&quot;&t;.previous&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|res
)paren
comma
l_string|&quot;=r&quot;
(paren
id|dst
)paren
comma
l_string|&quot;=r&quot;
(paren
id|src
)paren
comma
l_string|&quot;=r&quot;
(paren
id|count
)paren
suffix:colon
l_string|&quot;3&quot;
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
l_string|&quot;g&quot;
(paren
op_minus
id|EFAULT
)paren
suffix:colon
l_string|&quot;r9&quot;
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
multiline_comment|/* A few copy asms to build up the more complex ones from.&n;&n;   Note again, a post-increment is performed regardless of whether a bus&n;   fault occurred in that instruction, and PC for a faulted insn is the&n;   address *after* the insn.  */
DECL|macro|__asm_copy_user_cont
mdefine_line|#define __asm_copy_user_cont(to, from, ret, COPY, FIXUP, TENTRY) &bslash;&n;&t;__asm__ __volatile__ (&t;&t;&t;&t;&bslash;&n;&t;&t;&t;COPY&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;1:&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;&t;&bslash;&n;&t;&t;&t;FIXUP&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;jump 1b&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.previous&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;&t;&bslash;&n;&t;&t;&t;TENTRY&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.previous&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=r&quot; (to), &quot;=r&quot; (from), &quot;=r&quot; (ret)&t;&bslash;&n;&t;&t;: &quot;0&quot; (to), &quot;1&quot; (from), &quot;2&quot; (ret)&t;&bslash;&n;&t;&t;: &quot;r9&quot;, &quot;memory&quot;)
DECL|macro|__asm_copy_from_user_1
mdefine_line|#define __asm_copy_from_user_1(to, from, ret) &bslash;&n;&t;__asm_copy_user_cont(to, from, ret,&t;&bslash;&n;&t;&t;&quot;&t;move.b [%1+],$r9&bslash;n&quot;&t;&bslash;&n;&t;&t;&quot;2:&t;move.b $r9,[%0+]&bslash;n&quot;,&t;&bslash;&n;&t;&t;&quot;3:&t;addq 1,%2&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&quot;&t;clear.b [%0+]&bslash;n&quot;,&t;&bslash;&n;&t;&t;&quot;&t;.dword 2b,3b&bslash;n&quot;)
DECL|macro|__asm_copy_from_user_2x_cont
mdefine_line|#define __asm_copy_from_user_2x_cont(to, from, ret, COPY, FIXUP, TENTRY) &bslash;&n;&t;__asm_copy_user_cont(to, from, ret,&t;&t;&bslash;&n;&t;&t;&quot;&t;move.w [%1+],$r9&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&quot;2:&t;move.w $r9,[%0+]&bslash;n&quot; COPY,&t;&bslash;&n;&t;&t;&quot;3:&t;addq 2,%2&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;clear.w [%0+]&bslash;n&quot; FIXUP,&t;&t;&bslash;&n;&t;&t;&quot;&t;.dword 2b,3b&bslash;n&quot; TENTRY)
DECL|macro|__asm_copy_from_user_2
mdefine_line|#define __asm_copy_from_user_2(to, from, ret) &bslash;&n;&t;__asm_copy_from_user_2x_cont(to, from, ret, &quot;&quot;, &quot;&quot;, &quot;&quot;)
DECL|macro|__asm_copy_from_user_3
mdefine_line|#define __asm_copy_from_user_3(to, from, ret)&t;&t;&bslash;&n;&t;__asm_copy_from_user_2x_cont(to, from, ret,&t;&bslash;&n;&t;&t;&quot;&t;move.b [%1+],$r9&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&quot;4:&t;move.b $r9,[%0+]&bslash;n&quot;,&t;&t;&bslash;&n;&t;&t;&quot;5:&t;addq 1,%2&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;clear.b [%0+]&bslash;n&quot;,&t;&t;&bslash;&n;&t;&t;&quot;&t;.dword 4b,5b&bslash;n&quot;)
DECL|macro|__asm_copy_from_user_4x_cont
mdefine_line|#define __asm_copy_from_user_4x_cont(to, from, ret, COPY, FIXUP, TENTRY) &bslash;&n;&t;__asm_copy_user_cont(to, from, ret,&t;&t;&bslash;&n;&t;&t;&quot;&t;move.d [%1+],$r9&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&quot;2:&t;move.d $r9,[%0+]&bslash;n&quot; COPY,&t;&bslash;&n;&t;&t;&quot;3:&t;addq 4,%2&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;clear.d [%0+]&bslash;n&quot; FIXUP,&t;&t;&bslash;&n;&t;&t;&quot;&t;.dword 2b,3b&bslash;n&quot; TENTRY)
DECL|macro|__asm_copy_from_user_4
mdefine_line|#define __asm_copy_from_user_4(to, from, ret) &bslash;&n;&t;__asm_copy_from_user_4x_cont(to, from, ret, &quot;&quot;, &quot;&quot;, &quot;&quot;)
DECL|macro|__asm_copy_from_user_5
mdefine_line|#define __asm_copy_from_user_5(to, from, ret) &bslash;&n;&t;__asm_copy_from_user_4x_cont(to, from, ret,&t;&bslash;&n;&t;&t;&quot;&t;move.b [%1+],$r9&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&quot;4:&t;move.b $r9,[%0+]&bslash;n&quot;,&t;&t;&bslash;&n;&t;&t;&quot;5:&t;addq 1,%2&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;clear.b [%0+]&bslash;n&quot;,&t;&t;&bslash;&n;&t;&t;&quot;&t;.dword 4b,5b&bslash;n&quot;)
DECL|macro|__asm_copy_from_user_6x_cont
mdefine_line|#define __asm_copy_from_user_6x_cont(to, from, ret, COPY, FIXUP, TENTRY) &bslash;&n;&t;__asm_copy_from_user_4x_cont(to, from, ret,&t;&bslash;&n;&t;&t;&quot;&t;move.w [%1+],$r9&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&quot;4:&t;move.w $r9,[%0+]&bslash;n&quot; COPY,&t;&bslash;&n;&t;&t;&quot;5:&t;addq 2,%2&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;clear.w [%0+]&bslash;n&quot; FIXUP,&t;&t;&bslash;&n;&t;&t;&quot;&t;.dword 4b,5b&bslash;n&quot; TENTRY)
DECL|macro|__asm_copy_from_user_6
mdefine_line|#define __asm_copy_from_user_6(to, from, ret) &bslash;&n;&t;__asm_copy_from_user_6x_cont(to, from, ret, &quot;&quot;, &quot;&quot;, &quot;&quot;)
DECL|macro|__asm_copy_from_user_7
mdefine_line|#define __asm_copy_from_user_7(to, from, ret) &bslash;&n;&t;__asm_copy_from_user_6x_cont(to, from, ret,&t;&bslash;&n;&t;&t;&quot;&t;move.b [%1+],$r9&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&quot;6:&t;move.b $r9,[%0+]&bslash;n&quot;,&t;&t;&bslash;&n;&t;&t;&quot;7:&t;addq 1,%2&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;clear.b [%0+]&bslash;n&quot;,&t;&t;&bslash;&n;&t;&t;&quot;&t;.dword 6b,7b&bslash;n&quot;)
DECL|macro|__asm_copy_from_user_8x_cont
mdefine_line|#define __asm_copy_from_user_8x_cont(to, from, ret, COPY, FIXUP, TENTRY) &bslash;&n;&t;__asm_copy_from_user_4x_cont(to, from, ret,&t;&bslash;&n;&t;&t;&quot;&t;move.d [%1+],$r9&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&quot;4:&t;move.d $r9,[%0+]&bslash;n&quot; COPY,&t;&bslash;&n;&t;&t;&quot;5:&t;addq 4,%2&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;clear.d [%0+]&bslash;n&quot; FIXUP,&t;&t;&bslash;&n;&t;&t;&quot;&t;.dword 4b,5b&bslash;n&quot; TENTRY)
DECL|macro|__asm_copy_from_user_8
mdefine_line|#define __asm_copy_from_user_8(to, from, ret) &bslash;&n;&t;__asm_copy_from_user_8x_cont(to, from, ret, &quot;&quot;, &quot;&quot;, &quot;&quot;)
DECL|macro|__asm_copy_from_user_9
mdefine_line|#define __asm_copy_from_user_9(to, from, ret) &bslash;&n;&t;__asm_copy_from_user_8x_cont(to, from, ret,&t;&bslash;&n;&t;&t;&quot;&t;move.b [%1+],$r9&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&quot;6:&t;move.b $r9,[%0+]&bslash;n&quot;,&t;&t;&bslash;&n;&t;&t;&quot;7:&t;addq 1,%2&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;clear.b [%0+]&bslash;n&quot;,&t;&t;&bslash;&n;&t;&t;&quot;&t;.dword 6b,7b&bslash;n&quot;)
DECL|macro|__asm_copy_from_user_10x_cont
mdefine_line|#define __asm_copy_from_user_10x_cont(to, from, ret, COPY, FIXUP, TENTRY) &bslash;&n;&t;__asm_copy_from_user_8x_cont(to, from, ret,&t;&bslash;&n;&t;&t;&quot;&t;move.w [%1+],$r9&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&quot;6:&t;move.w $r9,[%0+]&bslash;n&quot; COPY,&t;&bslash;&n;&t;&t;&quot;7:&t;addq 2,%2&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;clear.w [%0+]&bslash;n&quot; FIXUP,&t;&t;&bslash;&n;&t;&t;&quot;&t;.dword 6b,7b&bslash;n&quot; TENTRY)
DECL|macro|__asm_copy_from_user_10
mdefine_line|#define __asm_copy_from_user_10(to, from, ret) &bslash;&n;&t;__asm_copy_from_user_10x_cont(to, from, ret, &quot;&quot;, &quot;&quot;, &quot;&quot;)
DECL|macro|__asm_copy_from_user_11
mdefine_line|#define __asm_copy_from_user_11(to, from, ret)&t;&t;&bslash;&n;&t;__asm_copy_from_user_10x_cont(to, from, ret,&t;&bslash;&n;&t;&t;&quot;&t;move.b [%1+],$r9&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&quot;8:&t;move.b $r9,[%0+]&bslash;n&quot;,&t;&t;&bslash;&n;&t;&t;&quot;9:&t;addq 1,%2&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;clear.b [%0+]&bslash;n&quot;,&t;&t;&bslash;&n;&t;&t;&quot;&t;.dword 8b,9b&bslash;n&quot;)
DECL|macro|__asm_copy_from_user_12x_cont
mdefine_line|#define __asm_copy_from_user_12x_cont(to, from, ret, COPY, FIXUP, TENTRY) &bslash;&n;&t;__asm_copy_from_user_8x_cont(to, from, ret,&t;&bslash;&n;&t;&t;&quot;&t;move.d [%1+],$r9&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&quot;6:&t;move.d $r9,[%0+]&bslash;n&quot; COPY,&t;&bslash;&n;&t;&t;&quot;7:&t;addq 4,%2&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;clear.d [%0+]&bslash;n&quot; FIXUP,&t;&t;&bslash;&n;&t;&t;&quot;&t;.dword 6b,7b&bslash;n&quot; TENTRY)
DECL|macro|__asm_copy_from_user_12
mdefine_line|#define __asm_copy_from_user_12(to, from, ret) &bslash;&n;&t;__asm_copy_from_user_12x_cont(to, from, ret, &quot;&quot;, &quot;&quot;, &quot;&quot;)
DECL|macro|__asm_copy_from_user_13
mdefine_line|#define __asm_copy_from_user_13(to, from, ret) &bslash;&n;&t;__asm_copy_from_user_12x_cont(to, from, ret,&t;&bslash;&n;&t;&t;&quot;&t;move.b [%1+],$r9&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&quot;8:&t;move.b $r9,[%0+]&bslash;n&quot;,&t;&t;&bslash;&n;&t;&t;&quot;9:&t;addq 1,%2&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;clear.b [%0+]&bslash;n&quot;,&t;&t;&bslash;&n;&t;&t;&quot;&t;.dword 8b,9b&bslash;n&quot;)
DECL|macro|__asm_copy_from_user_14x_cont
mdefine_line|#define __asm_copy_from_user_14x_cont(to, from, ret, COPY, FIXUP, TENTRY) &bslash;&n;&t;__asm_copy_from_user_12x_cont(to, from, ret,&t;&bslash;&n;&t;&t;&quot;&t;move.w [%1+],$r9&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&quot;8:&t;move.w $r9,[%0+]&bslash;n&quot; COPY,&t;&bslash;&n;&t;&t;&quot;9:&t;addq 2,%2&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;clear.w [%0+]&bslash;n&quot; FIXUP,&t;&t;&bslash;&n;&t;&t;&quot;&t;.dword 8b,9b&bslash;n&quot; TENTRY)
DECL|macro|__asm_copy_from_user_14
mdefine_line|#define __asm_copy_from_user_14(to, from, ret) &bslash;&n;&t;__asm_copy_from_user_14x_cont(to, from, ret, &quot;&quot;, &quot;&quot;, &quot;&quot;)
DECL|macro|__asm_copy_from_user_15
mdefine_line|#define __asm_copy_from_user_15(to, from, ret) &bslash;&n;&t;__asm_copy_from_user_14x_cont(to, from, ret,&t;&bslash;&n;&t;&t;&quot;&t;move.b [%1+],$r9&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&quot;10:&t;move.b $r9,[%0+]&bslash;n&quot;,&t;&t;&bslash;&n;&t;&t;&quot;11:&t;addq 1,%2&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;clear.b [%0+]&bslash;n&quot;,&t;&t;&bslash;&n;&t;&t;&quot;&t;.dword 10b,11b&bslash;n&quot;)
DECL|macro|__asm_copy_from_user_16x_cont
mdefine_line|#define __asm_copy_from_user_16x_cont(to, from, ret, COPY, FIXUP, TENTRY) &bslash;&n;&t;__asm_copy_from_user_12x_cont(to, from, ret,&t;&bslash;&n;&t;&t;&quot;&t;move.d [%1+],$r9&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&quot;8:&t;move.d $r9,[%0+]&bslash;n&quot; COPY,&t;&bslash;&n;&t;&t;&quot;9:&t;addq 4,%2&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;clear.d [%0+]&bslash;n&quot; FIXUP,&t;&t;&bslash;&n;&t;&t;&quot;&t;.dword 8b,9b&bslash;n&quot; TENTRY)
DECL|macro|__asm_copy_from_user_16
mdefine_line|#define __asm_copy_from_user_16(to, from, ret) &bslash;&n;&t;__asm_copy_from_user_16x_cont(to, from, ret, &quot;&quot;, &quot;&quot;, &quot;&quot;)
DECL|macro|__asm_copy_from_user_20x_cont
mdefine_line|#define __asm_copy_from_user_20x_cont(to, from, ret, COPY, FIXUP, TENTRY) &bslash;&n;&t;__asm_copy_from_user_16x_cont(to, from, ret,&t;&bslash;&n;&t;&t;&quot;&t;move.d [%1+],$r9&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&quot;10:&t;move.d $r9,[%0+]&bslash;n&quot; COPY,&t;&bslash;&n;&t;&t;&quot;11:&t;addq 4,%2&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;clear.d [%0+]&bslash;n&quot; FIXUP,&t;&t;&bslash;&n;&t;&t;&quot;&t;.dword 10b,11b&bslash;n&quot; TENTRY)
DECL|macro|__asm_copy_from_user_20
mdefine_line|#define __asm_copy_from_user_20(to, from, ret) &bslash;&n;&t;__asm_copy_from_user_20x_cont(to, from, ret, &quot;&quot;, &quot;&quot;, &quot;&quot;)
DECL|macro|__asm_copy_from_user_24x_cont
mdefine_line|#define __asm_copy_from_user_24x_cont(to, from, ret, COPY, FIXUP, TENTRY) &bslash;&n;&t;__asm_copy_from_user_20x_cont(to, from, ret,&t;&bslash;&n;&t;&t;&quot;&t;move.d [%1+],$r9&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&quot;12:&t;move.d $r9,[%0+]&bslash;n&quot; COPY,&t;&bslash;&n;&t;&t;&quot;13:&t;addq 4,%2&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;clear.d [%0+]&bslash;n&quot; FIXUP,&t;&t;&bslash;&n;&t;&t;&quot;&t;.dword 12b,13b&bslash;n&quot; TENTRY)
DECL|macro|__asm_copy_from_user_24
mdefine_line|#define __asm_copy_from_user_24(to, from, ret) &bslash;&n;&t;__asm_copy_from_user_24x_cont(to, from, ret, &quot;&quot;, &quot;&quot;, &quot;&quot;)
multiline_comment|/* And now, the to-user ones.  */
DECL|macro|__asm_copy_to_user_1
mdefine_line|#define __asm_copy_to_user_1(to, from, ret)&t;&bslash;&n;&t;__asm_copy_user_cont(to, from, ret,&t;&bslash;&n;&t;&t;&quot;&t;move.b [%1+],$r9&bslash;n&quot;&t;&bslash;&n;&t;&t;&quot;&t;move.b $r9,[%0+]&bslash;n2:&bslash;n&quot;,&t;&bslash;&n;&t;&t;&quot;3:&t;addq 1,%2&bslash;n&quot;,&t;&t;&bslash;&n;&t;&t;&quot;&t;.dword 2b,3b&bslash;n&quot;)
DECL|macro|__asm_copy_to_user_2x_cont
mdefine_line|#define __asm_copy_to_user_2x_cont(to, from, ret, COPY, FIXUP, TENTRY) &bslash;&n;&t;__asm_copy_user_cont(to, from, ret,&t;&t;&bslash;&n;&t;&t;&quot;&t;move.w [%1+],$r9&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&quot;&t;move.w $r9,[%0+]&bslash;n2:&bslash;n&quot; COPY,&t;&bslash;&n;&t;&t;&quot;3:&t;addq 2,%2&bslash;n&quot; FIXUP,&t;&t;&bslash;&n;&t;&t;&quot;&t;.dword 2b,3b&bslash;n&quot; TENTRY)
DECL|macro|__asm_copy_to_user_2
mdefine_line|#define __asm_copy_to_user_2(to, from, ret) &bslash;&n;&t;__asm_copy_to_user_2x_cont(to, from, ret, &quot;&quot;, &quot;&quot;, &quot;&quot;)
DECL|macro|__asm_copy_to_user_3
mdefine_line|#define __asm_copy_to_user_3(to, from, ret) &bslash;&n;&t;__asm_copy_to_user_2x_cont(to, from, ret,&t;&bslash;&n;&t;&t;&quot;&t;move.b [%1+],$r9&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&quot;&t;move.b $r9,[%0+]&bslash;n4:&bslash;n&quot;,&t;&t;&bslash;&n;&t;&t;&quot;5:&t;addq 1,%2&bslash;n&quot;,&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.dword 4b,5b&bslash;n&quot;)
DECL|macro|__asm_copy_to_user_4x_cont
mdefine_line|#define __asm_copy_to_user_4x_cont(to, from, ret, COPY, FIXUP, TENTRY) &bslash;&n;&t;__asm_copy_user_cont(to, from, ret,&t;&t;&bslash;&n;&t;&t;&quot;&t;move.d [%1+],$r9&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&quot;&t;move.d $r9,[%0+]&bslash;n2:&bslash;n&quot; COPY,&t;&bslash;&n;&t;&t;&quot;3:&t;addq 4,%2&bslash;n&quot; FIXUP,&t;&t;&bslash;&n;&t;&t;&quot;&t;.dword 2b,3b&bslash;n&quot; TENTRY)
DECL|macro|__asm_copy_to_user_4
mdefine_line|#define __asm_copy_to_user_4(to, from, ret) &bslash;&n;&t;__asm_copy_to_user_4x_cont(to, from, ret, &quot;&quot;, &quot;&quot;, &quot;&quot;)
DECL|macro|__asm_copy_to_user_5
mdefine_line|#define __asm_copy_to_user_5(to, from, ret) &bslash;&n;&t;__asm_copy_to_user_4x_cont(to, from, ret,&t;&bslash;&n;&t;&t;&quot;&t;move.b [%1+],$r9&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&quot;&t;move.b $r9,[%0+]&bslash;n4:&bslash;n&quot;,&t;&t;&bslash;&n;&t;&t;&quot;5:&t;addq 1,%2&bslash;n&quot;,&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.dword 4b,5b&bslash;n&quot;)
DECL|macro|__asm_copy_to_user_6x_cont
mdefine_line|#define __asm_copy_to_user_6x_cont(to, from, ret, COPY, FIXUP, TENTRY) &bslash;&n;&t;__asm_copy_to_user_4x_cont(to, from, ret,&t;&bslash;&n;&t;&t;&quot;&t;move.w [%1+],$r9&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&quot;&t;move.w $r9,[%0+]&bslash;n4:&bslash;n&quot; COPY,&t;&bslash;&n;&t;&t;&quot;5:&t;addq 2,%2&bslash;n&quot; FIXUP,&t;&t;&bslash;&n;&t;&t;&quot;&t;.dword 4b,5b&bslash;n&quot; TENTRY)
DECL|macro|__asm_copy_to_user_6
mdefine_line|#define __asm_copy_to_user_6(to, from, ret) &bslash;&n;&t;__asm_copy_to_user_6x_cont(to, from, ret, &quot;&quot;, &quot;&quot;, &quot;&quot;)
DECL|macro|__asm_copy_to_user_7
mdefine_line|#define __asm_copy_to_user_7(to, from, ret) &bslash;&n;&t;__asm_copy_to_user_6x_cont(to, from, ret,&t;&bslash;&n;&t;&t;&quot;&t;move.b [%1+],$r9&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&quot;&t;move.b $r9,[%0+]&bslash;n6:&bslash;n&quot;,&t;&t;&bslash;&n;&t;&t;&quot;7:&t;addq 1,%2&bslash;n&quot;,&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.dword 6b,7b&bslash;n&quot;)
DECL|macro|__asm_copy_to_user_8x_cont
mdefine_line|#define __asm_copy_to_user_8x_cont(to, from, ret, COPY, FIXUP, TENTRY) &bslash;&n;&t;__asm_copy_to_user_4x_cont(to, from, ret,&t;&bslash;&n;&t;&t;&quot;&t;move.d [%1+],$r9&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&quot;&t;move.d $r9,[%0+]&bslash;n4:&bslash;n&quot; COPY,&t;&bslash;&n;&t;&t;&quot;5:&t;addq 4,%2&bslash;n&quot;  FIXUP,&t;&t;&bslash;&n;&t;&t;&quot;&t;.dword 4b,5b&bslash;n&quot; TENTRY)
DECL|macro|__asm_copy_to_user_8
mdefine_line|#define __asm_copy_to_user_8(to, from, ret) &bslash;&n;&t;__asm_copy_to_user_8x_cont(to, from, ret, &quot;&quot;, &quot;&quot;, &quot;&quot;)
DECL|macro|__asm_copy_to_user_9
mdefine_line|#define __asm_copy_to_user_9(to, from, ret) &bslash;&n;&t;__asm_copy_to_user_8x_cont(to, from, ret,&t;&bslash;&n;&t;&t;&quot;&t;move.b [%1+],$r9&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&quot;&t;move.b $r9,[%0+]&bslash;n6:&bslash;n&quot;,&t;&t;&bslash;&n;&t;&t;&quot;7:&t;addq 1,%2&bslash;n&quot;,&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.dword 6b,7b&bslash;n&quot;)
DECL|macro|__asm_copy_to_user_10x_cont
mdefine_line|#define __asm_copy_to_user_10x_cont(to, from, ret, COPY, FIXUP, TENTRY) &bslash;&n;&t;__asm_copy_to_user_8x_cont(to, from, ret,&t;&bslash;&n;&t;&t;&quot;&t;move.w [%1+],$r9&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&quot;&t;move.w $r9,[%0+]&bslash;n6:&bslash;n&quot; COPY,&t;&bslash;&n;&t;&t;&quot;7:&t;addq 2,%2&bslash;n&quot; FIXUP,&t;&t;&bslash;&n;&t;&t;&quot;&t;.dword 6b,7b&bslash;n&quot; TENTRY)
DECL|macro|__asm_copy_to_user_10
mdefine_line|#define __asm_copy_to_user_10(to, from, ret) &bslash;&n;&t;__asm_copy_to_user_10x_cont(to, from, ret, &quot;&quot;, &quot;&quot;, &quot;&quot;)
DECL|macro|__asm_copy_to_user_11
mdefine_line|#define __asm_copy_to_user_11(to, from, ret) &bslash;&n;&t;__asm_copy_to_user_10x_cont(to, from, ret,&t;&bslash;&n;&t;&t;&quot;&t;move.b [%1+],$r9&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&quot;&t;move.b $r9,[%0+]&bslash;n8:&bslash;n&quot;,&t;&t;&bslash;&n;&t;&t;&quot;9:&t;addq 1,%2&bslash;n&quot;,&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.dword 8b,9b&bslash;n&quot;)
DECL|macro|__asm_copy_to_user_12x_cont
mdefine_line|#define __asm_copy_to_user_12x_cont(to, from, ret, COPY, FIXUP, TENTRY) &bslash;&n;&t;__asm_copy_to_user_8x_cont(to, from, ret,&t;&bslash;&n;&t;&t;&quot;&t;move.d [%1+],$r9&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&quot;&t;move.d $r9,[%0+]&bslash;n6:&bslash;n&quot; COPY,&t;&bslash;&n;&t;&t;&quot;7:&t;addq 4,%2&bslash;n&quot; FIXUP,&t;&t;&bslash;&n;&t;&t;&quot;&t;.dword 6b,7b&bslash;n&quot; TENTRY)
DECL|macro|__asm_copy_to_user_12
mdefine_line|#define __asm_copy_to_user_12(to, from, ret) &bslash;&n;&t;__asm_copy_to_user_12x_cont(to, from, ret, &quot;&quot;, &quot;&quot;, &quot;&quot;)
DECL|macro|__asm_copy_to_user_13
mdefine_line|#define __asm_copy_to_user_13(to, from, ret) &bslash;&n;&t;__asm_copy_to_user_12x_cont(to, from, ret,&t;&bslash;&n;&t;&t;&quot;&t;move.b [%1+],$r9&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&quot;&t;move.b $r9,[%0+]&bslash;n8:&bslash;n&quot;,&t;&t;&bslash;&n;&t;&t;&quot;9:&t;addq 1,%2&bslash;n&quot;,&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.dword 8b,9b&bslash;n&quot;)
DECL|macro|__asm_copy_to_user_14x_cont
mdefine_line|#define __asm_copy_to_user_14x_cont(to, from, ret, COPY, FIXUP, TENTRY) &bslash;&n;&t;__asm_copy_to_user_12x_cont(to, from, ret,&t;&bslash;&n;&t;&t;&quot;&t;move.w [%1+],$r9&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&quot;&t;move.w $r9,[%0+]&bslash;n8:&bslash;n&quot; COPY,&t;&bslash;&n;&t;&t;&quot;9:&t;addq 2,%2&bslash;n&quot; FIXUP,&t;&t;&bslash;&n;&t;&t;&quot;&t;.dword 8b,9b&bslash;n&quot; TENTRY)
DECL|macro|__asm_copy_to_user_14
mdefine_line|#define __asm_copy_to_user_14(to, from, ret)&t;&bslash;&n;&t;__asm_copy_to_user_14x_cont(to, from, ret, &quot;&quot;, &quot;&quot;, &quot;&quot;)
DECL|macro|__asm_copy_to_user_15
mdefine_line|#define __asm_copy_to_user_15(to, from, ret) &bslash;&n;&t;__asm_copy_to_user_14x_cont(to, from, ret,&t;&bslash;&n;&t;&t;&quot;&t;move.b [%1+],$r9&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&quot;&t;move.b $r9,[%0+]&bslash;n10:&bslash;n&quot;,&t;&t;&bslash;&n;&t;&t;&quot;11:&t;addq 1,%2&bslash;n&quot;,&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.dword 10b,11b&bslash;n&quot;)
DECL|macro|__asm_copy_to_user_16x_cont
mdefine_line|#define __asm_copy_to_user_16x_cont(to, from, ret, COPY, FIXUP, TENTRY) &bslash;&n;&t;__asm_copy_to_user_12x_cont(to, from, ret,&t;&bslash;&n;&t;&t;&quot;&t;move.d [%1+],$r9&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&quot;&t;move.d $r9,[%0+]&bslash;n8:&bslash;n&quot; COPY,&t;&bslash;&n;&t;&t;&quot;9:&t;addq 4,%2&bslash;n&quot; FIXUP,&t;&t;&bslash;&n;&t;&t;&quot;&t;.dword 8b,9b&bslash;n&quot; TENTRY)
DECL|macro|__asm_copy_to_user_16
mdefine_line|#define __asm_copy_to_user_16(to, from, ret) &bslash;&n;&t;__asm_copy_to_user_16x_cont(to, from, ret, &quot;&quot;, &quot;&quot;, &quot;&quot;)
DECL|macro|__asm_copy_to_user_20x_cont
mdefine_line|#define __asm_copy_to_user_20x_cont(to, from, ret, COPY, FIXUP, TENTRY) &bslash;&n;&t;__asm_copy_to_user_16x_cont(to, from, ret,&t;&bslash;&n;&t;&t;&quot;&t;move.d [%1+],$r9&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&quot;&t;move.d $r9,[%0+]&bslash;n10:&bslash;n&quot; COPY,&t;&bslash;&n;&t;&t;&quot;11:&t;addq 4,%2&bslash;n&quot; FIXUP,&t;&t;&bslash;&n;&t;&t;&quot;&t;.dword 10b,11b&bslash;n&quot; TENTRY)
DECL|macro|__asm_copy_to_user_20
mdefine_line|#define __asm_copy_to_user_20(to, from, ret) &bslash;&n;&t;__asm_copy_to_user_20x_cont(to, from, ret, &quot;&quot;, &quot;&quot;, &quot;&quot;)
DECL|macro|__asm_copy_to_user_24x_cont
mdefine_line|#define __asm_copy_to_user_24x_cont(to, from, ret, COPY, FIXUP, TENTRY)&t;&bslash;&n;&t;__asm_copy_to_user_20x_cont(to, from, ret,&t;&bslash;&n;&t;&t;&quot;&t;move.d [%1+],$r9&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&quot;&t;move.d $r9,[%0+]&bslash;n12:&bslash;n&quot; COPY,&t;&bslash;&n;&t;&t;&quot;13:&t;addq 4,%2&bslash;n&quot; FIXUP,&t;&t;&bslash;&n;&t;&t;&quot;&t;.dword 12b,13b&bslash;n&quot; TENTRY)
DECL|macro|__asm_copy_to_user_24
mdefine_line|#define __asm_copy_to_user_24(to, from, ret)&t;&bslash;&n;&t;__asm_copy_to_user_24x_cont(to, from, ret, &quot;&quot;, &quot;&quot;, &quot;&quot;)
multiline_comment|/* Define a few clearing asms with exception handlers.  */
multiline_comment|/* This frame-asm is like the __asm_copy_user_cont one, but has one less&n;   input.  */
DECL|macro|__asm_clear
mdefine_line|#define __asm_clear(to, ret, CLEAR, FIXUP, TENTRY) &bslash;&n;&t;__asm__ __volatile__ (&t;&t;&t;&t;&bslash;&n;&t;&t;&t;CLEAR&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;1:&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;&t;&bslash;&n;&t;&t;&t;FIXUP&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;jump 1b&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.previous&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;&t;&bslash;&n;&t;&t;&t;TENTRY&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.previous&quot;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=r&quot; (to), &quot;=r&quot; (ret)&t;&t;&t;&bslash;&n;&t;&t;: &quot;0&quot; (to), &quot;1&quot; (ret)&t;&t;&t;&bslash;&n;&t;&t;: &quot;memory&quot;)
DECL|macro|__asm_clear_1
mdefine_line|#define __asm_clear_1(to, ret) &bslash;&n;&t;__asm_clear(to, ret,&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;clear.b [%0+]&bslash;n2:&bslash;n&quot;,&t;&bslash;&n;&t;&t;&quot;3:&t;addq 1,%1&bslash;n&quot;,&t;&t;&bslash;&n;&t;&t;&quot;&t;.dword 2b,3b&bslash;n&quot;)
DECL|macro|__asm_clear_2
mdefine_line|#define __asm_clear_2(to, ret) &bslash;&n;&t;__asm_clear(to, ret,&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;clear.w [%0+]&bslash;n2:&bslash;n&quot;,&t;&bslash;&n;&t;&t;&quot;3:&t;addq 2,%1&bslash;n&quot;,&t;&t;&bslash;&n;&t;&t;&quot;&t;.dword 2b,3b&bslash;n&quot;)
DECL|macro|__asm_clear_3
mdefine_line|#define __asm_clear_3(to, ret) &bslash;&n;     __asm_clear(to, ret,&t;&t;&t;&bslash;&n;&t;&t; &quot;&t;clear.w [%0+]&bslash;n&quot;&t;&bslash;&n;&t;&t; &quot;2:&t;clear.b [%0+]&bslash;n3:&bslash;n&quot;,&t;&bslash;&n;&t;&t; &quot;4:&t;addq 2,%1&bslash;n&quot;&t;&t;&bslash;&n;&t;&t; &quot;5:&t;addq 1,%1&bslash;n&quot;,&t;&t;&bslash;&n;&t;&t; &quot;&t;.dword 2b,4b&bslash;n&quot;&t;&t;&bslash;&n;&t;&t; &quot;&t;.dword 3b,5b&bslash;n&quot;)
DECL|macro|__asm_clear_4x_cont
mdefine_line|#define __asm_clear_4x_cont(to, ret, CLEAR, FIXUP, TENTRY) &bslash;&n;&t;__asm_clear(to, ret,&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;clear.d [%0+]&bslash;n2:&bslash;n&quot; CLEAR,&t;&bslash;&n;&t;&t;&quot;3:&t;addq 4,%1&bslash;n&quot; FIXUP,&t;&t;&bslash;&n;&t;&t;&quot;&t;.dword 2b,3b&bslash;n&quot; TENTRY)
DECL|macro|__asm_clear_4
mdefine_line|#define __asm_clear_4(to, ret) &bslash;&n;&t;__asm_clear_4x_cont(to, ret, &quot;&quot;, &quot;&quot;, &quot;&quot;)
DECL|macro|__asm_clear_8x_cont
mdefine_line|#define __asm_clear_8x_cont(to, ret, CLEAR, FIXUP, TENTRY) &bslash;&n;&t;__asm_clear_4x_cont(to, ret,&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;clear.d [%0+]&bslash;n4:&bslash;n&quot; CLEAR,&t;&bslash;&n;&t;&t;&quot;5:&t;addq 4,%1&bslash;n&quot; FIXUP,&t;&t;&bslash;&n;&t;&t;&quot;&t;.dword 4b,5b&bslash;n&quot; TENTRY)
DECL|macro|__asm_clear_8
mdefine_line|#define __asm_clear_8(to, ret) &bslash;&n;&t;__asm_clear_8x_cont(to, ret, &quot;&quot;, &quot;&quot;, &quot;&quot;)
DECL|macro|__asm_clear_12x_cont
mdefine_line|#define __asm_clear_12x_cont(to, ret, CLEAR, FIXUP, TENTRY) &bslash;&n;&t;__asm_clear_8x_cont(to, ret,&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;clear.d [%0+]&bslash;n6:&bslash;n&quot; CLEAR,&t;&bslash;&n;&t;&t;&quot;7:&t;addq 4,%1&bslash;n&quot; FIXUP,&t;&t;&bslash;&n;&t;&t;&quot;&t;.dword 6b,7b&bslash;n&quot; TENTRY)
DECL|macro|__asm_clear_12
mdefine_line|#define __asm_clear_12(to, ret) &bslash;&n;&t;__asm_clear_12x_cont(to, ret, &quot;&quot;, &quot;&quot;, &quot;&quot;)
DECL|macro|__asm_clear_16x_cont
mdefine_line|#define __asm_clear_16x_cont(to, ret, CLEAR, FIXUP, TENTRY) &bslash;&n;&t;__asm_clear_12x_cont(to, ret,&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;clear.d [%0+]&bslash;n8:&bslash;n&quot; CLEAR,&t;&bslash;&n;&t;&t;&quot;9:&t;addq 4,%1&bslash;n&quot; FIXUP,&t;&t;&bslash;&n;&t;&t;&quot;&t;.dword 8b,9b&bslash;n&quot; TENTRY)
DECL|macro|__asm_clear_16
mdefine_line|#define __asm_clear_16(to, ret) &bslash;&n;&t;__asm_clear_16x_cont(to, ret, &quot;&quot;, &quot;&quot;, &quot;&quot;)
DECL|macro|__asm_clear_20x_cont
mdefine_line|#define __asm_clear_20x_cont(to, ret, CLEAR, FIXUP, TENTRY) &bslash;&n;&t;__asm_clear_16x_cont(to, ret,&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;clear.d [%0+]&bslash;n10:&bslash;n&quot; CLEAR,&t;&bslash;&n;&t;&t;&quot;11:&t;addq 4,%1&bslash;n&quot; FIXUP,&t;&t;&bslash;&n;&t;&t;&quot;&t;.dword 10b,11b&bslash;n&quot; TENTRY)
DECL|macro|__asm_clear_20
mdefine_line|#define __asm_clear_20(to, ret) &bslash;&n;&t;__asm_clear_20x_cont(to, ret, &quot;&quot;, &quot;&quot;, &quot;&quot;)
DECL|macro|__asm_clear_24x_cont
mdefine_line|#define __asm_clear_24x_cont(to, ret, CLEAR, FIXUP, TENTRY) &bslash;&n;&t;__asm_clear_20x_cont(to, ret,&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;clear.d [%0+]&bslash;n12:&bslash;n&quot; CLEAR,&t;&bslash;&n;&t;&t;&quot;13:&t;addq 4,%1&bslash;n&quot; FIXUP,&t;&t;&bslash;&n;&t;&t;&quot;&t;.dword 12b,13b&bslash;n&quot; TENTRY)
DECL|macro|__asm_clear_24
mdefine_line|#define __asm_clear_24(to, ret) &bslash;&n;&t;__asm_clear_24x_cont(to, ret, &quot;&quot;, &quot;&quot;, &quot;&quot;)
multiline_comment|/*&n; * Return the size of a string (including the ending 0)&n; *&n; * Return length of string in userspace including terminating 0&n; * or 0 for error.  Return a value greater than N if too long.&n; */
r_extern
r_inline
r_int
DECL|function|strnlen_user
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
r_int
id|res
comma
id|tmp1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|access_ok
c_func
(paren
id|VERIFY_READ
comma
id|s
comma
l_int|0
)paren
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * This code is deduced from:&n;&t; *&n;&t; *&t;tmp1 = n;&n;&t; *&t;while (tmp1-- &gt; 0 &amp;&amp; *s++)&n;&t; *&t;  ;&n;&t; *&n;&t; *&t;res = n - tmp1;&n;&t; *&n;&t; *  (with tweaks).&n;&t; */
id|__asm__
id|__volatile__
(paren
l_string|&quot;&t;move.d %1,$r9&bslash;n&quot;
l_string|&quot;0:&bslash;n&quot;
l_string|&quot;&t;ble 1f&bslash;n&quot;
l_string|&quot;&t;subq 1,$r9&bslash;n&quot;
l_string|&quot;&t;test.b [%0+]&bslash;n&quot;
l_string|&quot;&t;bne 0b&bslash;n&quot;
l_string|&quot;&t;test.d $r9&bslash;n&quot;
l_string|&quot;1:&bslash;n&quot;
l_string|&quot;&t;move.d %1,%0&bslash;n&quot;
l_string|&quot;&t;sub.d $r9,%0&bslash;n&quot;
l_string|&quot;2:&bslash;n&quot;
l_string|&quot;&t;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
l_string|&quot;3:&t;clear.d %0&bslash;n&quot;
l_string|&quot;&t;jump 2b&bslash;n&quot;
multiline_comment|/* There&squot;s one address for a fault at the first move, and&n;&t;&t;   two possible PC values for a fault at the second move,&n;&t;&t;   being a delay-slot filler.  However, the branch-target&n;&t;&t;   for the second move is the same as the first address.&n;&t;&t;   Just so you don&squot;t get confused...  */
l_string|&quot;&t;.previous&bslash;n&quot;
l_string|&quot;&t;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;
l_string|&quot;&t;.dword 0b,3b&bslash;n&quot;
l_string|&quot;&t;.dword 1b,3b&bslash;n&quot;
l_string|&quot;&t;.previous&bslash;n&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|res
)paren
comma
l_string|&quot;=r&quot;
(paren
id|tmp1
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|s
)paren
comma
l_string|&quot;1&quot;
(paren
id|n
)paren
suffix:colon
l_string|&quot;r9&quot;
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
macro_line|#endif
eof
