multiline_comment|/*&n; * csum_partial_copy - do IP checksumming and copy&n; *&n; * (C) Copyright 1996 Linus Torvalds&n; * accellerated versions (and 21264 assembly versions ) contributed by&n; *&t;Rick Gorton&t;&lt;rick.gorton@alpha-processor.com&gt;&n; *&n; * Don&squot;t look at this too closely - you&squot;ll go mad. The things&n; * we do for performance..&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
DECL|macro|ldq_u
mdefine_line|#define ldq_u(x,y) &bslash;&n;__asm__ __volatile__(&quot;ldq_u %0,%1&quot;:&quot;=r&quot; (x):&quot;m&quot; (*(const unsigned long *)(y)))
DECL|macro|stq_u
mdefine_line|#define stq_u(x,y) &bslash;&n;__asm__ __volatile__(&quot;stq_u %1,%0&quot;:&quot;=m&quot; (*(unsigned long *)(y)):&quot;r&quot; (x))
DECL|macro|extql
mdefine_line|#define extql(x,y,z) &bslash;&n;__asm__ __volatile__(&quot;extql %1,%2,%0&quot;:&quot;=r&quot; (z):&quot;r&quot; (x),&quot;r&quot; (y))
DECL|macro|extqh
mdefine_line|#define extqh(x,y,z) &bslash;&n;__asm__ __volatile__(&quot;extqh %1,%2,%0&quot;:&quot;=r&quot; (z):&quot;r&quot; (x),&quot;r&quot; (y))
DECL|macro|mskql
mdefine_line|#define mskql(x,y,z) &bslash;&n;__asm__ __volatile__(&quot;mskql %1,%2,%0&quot;:&quot;=r&quot; (z):&quot;r&quot; (x),&quot;r&quot; (y))
DECL|macro|mskqh
mdefine_line|#define mskqh(x,y,z) &bslash;&n;__asm__ __volatile__(&quot;mskqh %1,%2,%0&quot;:&quot;=r&quot; (z):&quot;r&quot; (x),&quot;r&quot; (y))
DECL|macro|insql
mdefine_line|#define insql(x,y,z) &bslash;&n;__asm__ __volatile__(&quot;insql %1,%2,%0&quot;:&quot;=r&quot; (z):&quot;r&quot; (x),&quot;r&quot; (y))
DECL|macro|insqh
mdefine_line|#define insqh(x,y,z) &bslash;&n;__asm__ __volatile__(&quot;insqh %1,%2,%0&quot;:&quot;=r&quot; (z):&quot;r&quot; (x),&quot;r&quot; (y))
DECL|macro|__get_user_u
mdefine_line|#define __get_user_u(x,ptr)&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;long __guu_err;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&bslash;&n;&t;&quot;1:&t;ldq_u %0,%2&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;2:&bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&quot;&t;.long 1b - .&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;lda %0,2b-1b(%1)&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&quot;.previous&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=r&quot;(x), &quot;=r&quot;(__guu_err)&t;&t;&bslash;&n;&t;&t;: &quot;m&quot;(__m(ptr)), &quot;1&quot;(0));&t;&t;&bslash;&n;&t;__guu_err;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|__put_user_u
mdefine_line|#define __put_user_u(x,ptr)&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;long __puu_err;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&bslash;&n;&t;&quot;1:&t;stq_u %2,%1&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;2:&bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&quot;&t;.long 1b - .&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;lda $31,2b-1b(%0)&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&quot;.previous&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=r&quot;(__puu_err)&t;&t;&t;&bslash;&n;&t;&t;: &quot;m&quot;(__m(addr)), &quot;rJ&quot;(x), &quot;0&quot;(0));&t;&bslash;&n;&t;__puu_err;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|function|from64to16
r_static
r_inline
r_int
r_int
id|from64to16
c_func
(paren
r_int
r_int
id|x
)paren
(brace
multiline_comment|/* Using extract instructions is a bit more efficient&n;&t;   than the original shift/bitmask version.  */
r_union
(brace
r_int
r_int
id|ul
suffix:semicolon
r_int
r_int
id|ui
(braket
l_int|2
)braket
suffix:semicolon
r_int
r_int
id|us
(braket
l_int|4
)braket
suffix:semicolon
)brace
id|in_v
comma
id|tmp_v
comma
id|out_v
suffix:semicolon
id|in_v.ul
op_assign
id|x
suffix:semicolon
id|tmp_v.ul
op_assign
(paren
r_int
r_int
)paren
id|in_v.ui
(braket
l_int|0
)braket
op_plus
(paren
r_int
r_int
)paren
id|in_v.ui
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* Since the bits of tmp_v.sh[3] are going to always be zero,&n;&t;   we don&squot;t have to bother to add that in.  */
id|out_v.ul
op_assign
(paren
r_int
r_int
)paren
id|tmp_v.us
(braket
l_int|0
)braket
op_plus
(paren
r_int
r_int
)paren
id|tmp_v.us
(braket
l_int|1
)braket
op_plus
(paren
r_int
r_int
)paren
id|tmp_v.us
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Similarly, out_v.us[2] is always zero for the final add.  */
r_return
id|out_v.us
(braket
l_int|0
)braket
op_plus
id|out_v.us
(braket
l_int|1
)braket
suffix:semicolon
)brace
multiline_comment|/*&n; * Ok. This isn&squot;t fun, but this is the EASY case.&n; */
r_static
r_inline
r_int
r_int
DECL|function|csum_partial_cfu_aligned
id|csum_partial_cfu_aligned
c_func
(paren
r_const
r_int
r_int
op_star
id|src
comma
r_int
r_int
op_star
id|dst
comma
r_int
id|len
comma
r_int
r_int
id|checksum
comma
r_int
op_star
id|errp
)paren
(brace
r_int
r_int
id|carry
op_assign
l_int|0
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|len
op_ge
l_int|0
)paren
(brace
r_int
r_int
id|word
suffix:semicolon
id|err
op_or_assign
id|__get_user
c_func
(paren
id|word
comma
id|src
)paren
suffix:semicolon
id|checksum
op_add_assign
id|carry
suffix:semicolon
id|src
op_increment
suffix:semicolon
id|checksum
op_add_assign
id|word
suffix:semicolon
id|len
op_sub_assign
l_int|8
suffix:semicolon
id|carry
op_assign
id|checksum
OL
id|word
suffix:semicolon
op_star
id|dst
op_assign
id|word
suffix:semicolon
id|dst
op_increment
suffix:semicolon
)brace
id|len
op_add_assign
l_int|8
suffix:semicolon
id|checksum
op_add_assign
id|carry
suffix:semicolon
r_if
c_cond
(paren
id|len
)paren
(brace
r_int
r_int
id|word
comma
id|tmp
suffix:semicolon
id|err
op_or_assign
id|__get_user
c_func
(paren
id|word
comma
id|src
)paren
suffix:semicolon
id|tmp
op_assign
op_star
id|dst
suffix:semicolon
id|mskql
c_func
(paren
id|word
comma
id|len
comma
id|word
)paren
suffix:semicolon
id|checksum
op_add_assign
id|word
suffix:semicolon
id|mskqh
c_func
(paren
id|tmp
comma
id|len
comma
id|tmp
)paren
suffix:semicolon
id|carry
op_assign
id|checksum
OL
id|word
suffix:semicolon
op_star
id|dst
op_assign
id|word
op_or
id|tmp
suffix:semicolon
id|checksum
op_add_assign
id|carry
suffix:semicolon
)brace
r_if
c_cond
(paren
id|err
)paren
op_star
id|errp
op_assign
id|err
suffix:semicolon
r_return
id|checksum
suffix:semicolon
)brace
multiline_comment|/*&n; * This is even less fun, but this is still reasonably&n; * easy.&n; */
r_static
r_inline
r_int
r_int
DECL|function|csum_partial_cfu_dest_aligned
id|csum_partial_cfu_dest_aligned
c_func
(paren
r_const
r_int
r_int
op_star
id|src
comma
r_int
r_int
op_star
id|dst
comma
r_int
r_int
id|soff
comma
r_int
id|len
comma
r_int
r_int
id|checksum
comma
r_int
op_star
id|errp
)paren
(brace
r_int
r_int
id|first
suffix:semicolon
r_int
r_int
id|word
comma
id|carry
suffix:semicolon
r_int
r_int
id|lastsrc
op_assign
l_int|7
op_plus
id|len
op_plus
(paren
r_int
r_int
)paren
id|src
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
id|err
op_or_assign
id|__get_user_u
c_func
(paren
id|first
comma
id|src
)paren
suffix:semicolon
id|carry
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|len
op_ge
l_int|0
)paren
(brace
r_int
r_int
id|second
suffix:semicolon
id|err
op_or_assign
id|__get_user_u
c_func
(paren
id|second
comma
id|src
op_plus
l_int|1
)paren
suffix:semicolon
id|extql
c_func
(paren
id|first
comma
id|soff
comma
id|word
)paren
suffix:semicolon
id|len
op_sub_assign
l_int|8
suffix:semicolon
id|src
op_increment
suffix:semicolon
id|extqh
c_func
(paren
id|second
comma
id|soff
comma
id|first
)paren
suffix:semicolon
id|checksum
op_add_assign
id|carry
suffix:semicolon
id|word
op_or_assign
id|first
suffix:semicolon
id|first
op_assign
id|second
suffix:semicolon
id|checksum
op_add_assign
id|word
suffix:semicolon
op_star
id|dst
op_assign
id|word
suffix:semicolon
id|dst
op_increment
suffix:semicolon
id|carry
op_assign
id|checksum
OL
id|word
suffix:semicolon
)brace
id|len
op_add_assign
l_int|8
suffix:semicolon
id|checksum
op_add_assign
id|carry
suffix:semicolon
r_if
c_cond
(paren
id|len
)paren
(brace
r_int
r_int
id|tmp
suffix:semicolon
r_int
r_int
id|second
suffix:semicolon
id|err
op_or_assign
id|__get_user_u
c_func
(paren
id|second
comma
id|lastsrc
)paren
suffix:semicolon
id|tmp
op_assign
op_star
id|dst
suffix:semicolon
id|extql
c_func
(paren
id|first
comma
id|soff
comma
id|word
)paren
suffix:semicolon
id|extqh
c_func
(paren
id|second
comma
id|soff
comma
id|first
)paren
suffix:semicolon
id|word
op_or_assign
id|first
suffix:semicolon
id|mskql
c_func
(paren
id|word
comma
id|len
comma
id|word
)paren
suffix:semicolon
id|checksum
op_add_assign
id|word
suffix:semicolon
id|mskqh
c_func
(paren
id|tmp
comma
id|len
comma
id|tmp
)paren
suffix:semicolon
id|carry
op_assign
id|checksum
OL
id|word
suffix:semicolon
op_star
id|dst
op_assign
id|word
op_or
id|tmp
suffix:semicolon
id|checksum
op_add_assign
id|carry
suffix:semicolon
)brace
r_if
c_cond
(paren
id|err
)paren
op_star
id|errp
op_assign
id|err
suffix:semicolon
r_return
id|checksum
suffix:semicolon
)brace
multiline_comment|/*&n; * This is slightly less fun than the above..&n; */
r_static
r_inline
r_int
r_int
DECL|function|csum_partial_cfu_src_aligned
id|csum_partial_cfu_src_aligned
c_func
(paren
r_const
r_int
r_int
op_star
id|src
comma
r_int
r_int
op_star
id|dst
comma
r_int
r_int
id|doff
comma
r_int
id|len
comma
r_int
r_int
id|checksum
comma
r_int
r_int
id|partial_dest
comma
r_int
op_star
id|errp
)paren
(brace
r_int
r_int
id|carry
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|word
suffix:semicolon
r_int
r_int
id|second_dest
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
id|mskql
c_func
(paren
id|partial_dest
comma
id|doff
comma
id|partial_dest
)paren
suffix:semicolon
r_while
c_loop
(paren
id|len
op_ge
l_int|0
)paren
(brace
id|err
op_or_assign
id|__get_user
c_func
(paren
id|word
comma
id|src
)paren
suffix:semicolon
id|len
op_sub_assign
l_int|8
suffix:semicolon
id|insql
c_func
(paren
id|word
comma
id|doff
comma
id|second_dest
)paren
suffix:semicolon
id|checksum
op_add_assign
id|carry
suffix:semicolon
id|stq_u
c_func
(paren
id|partial_dest
op_or
id|second_dest
comma
id|dst
)paren
suffix:semicolon
id|src
op_increment
suffix:semicolon
id|checksum
op_add_assign
id|word
suffix:semicolon
id|insqh
c_func
(paren
id|word
comma
id|doff
comma
id|partial_dest
)paren
suffix:semicolon
id|carry
op_assign
id|checksum
OL
id|word
suffix:semicolon
id|dst
op_increment
suffix:semicolon
)brace
id|len
op_add_assign
l_int|8
suffix:semicolon
r_if
c_cond
(paren
id|len
)paren
(brace
id|checksum
op_add_assign
id|carry
suffix:semicolon
id|err
op_or_assign
id|__get_user
c_func
(paren
id|word
comma
id|src
)paren
suffix:semicolon
id|mskql
c_func
(paren
id|word
comma
id|len
comma
id|word
)paren
suffix:semicolon
id|len
op_sub_assign
l_int|8
suffix:semicolon
id|checksum
op_add_assign
id|word
suffix:semicolon
id|insql
c_func
(paren
id|word
comma
id|doff
comma
id|second_dest
)paren
suffix:semicolon
id|len
op_add_assign
id|doff
suffix:semicolon
id|carry
op_assign
id|checksum
OL
id|word
suffix:semicolon
id|partial_dest
op_or_assign
id|second_dest
suffix:semicolon
r_if
c_cond
(paren
id|len
op_ge
l_int|0
)paren
(brace
id|stq_u
c_func
(paren
id|partial_dest
comma
id|dst
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|len
)paren
r_goto
id|out
suffix:semicolon
id|dst
op_increment
suffix:semicolon
id|insqh
c_func
(paren
id|word
comma
id|doff
comma
id|partial_dest
)paren
suffix:semicolon
)brace
id|doff
op_assign
id|len
suffix:semicolon
)brace
id|ldq_u
c_func
(paren
id|second_dest
comma
id|dst
)paren
suffix:semicolon
id|mskqh
c_func
(paren
id|second_dest
comma
id|doff
comma
id|second_dest
)paren
suffix:semicolon
id|stq_u
c_func
(paren
id|partial_dest
op_or
id|second_dest
comma
id|dst
)paren
suffix:semicolon
id|out
suffix:colon
id|checksum
op_add_assign
id|carry
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
op_star
id|errp
op_assign
id|err
suffix:semicolon
r_return
id|checksum
suffix:semicolon
)brace
multiline_comment|/*&n; * This is so totally un-fun that it&squot;s frightening. Don&squot;t&n; * look at this too closely, you&squot;ll go blind.&n; */
r_static
r_inline
r_int
r_int
DECL|function|csum_partial_cfu_unaligned
id|csum_partial_cfu_unaligned
c_func
(paren
r_const
r_int
r_int
op_star
id|src
comma
r_int
r_int
op_star
id|dst
comma
r_int
r_int
id|soff
comma
r_int
r_int
id|doff
comma
r_int
id|len
comma
r_int
r_int
id|checksum
comma
r_int
r_int
id|partial_dest
comma
r_int
op_star
id|errp
)paren
(brace
r_int
r_int
id|carry
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|first
suffix:semicolon
r_int
r_int
id|lastsrc
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
id|err
op_or_assign
id|__get_user_u
c_func
(paren
id|first
comma
id|src
)paren
suffix:semicolon
id|lastsrc
op_assign
l_int|7
op_plus
id|len
op_plus
(paren
r_int
r_int
)paren
id|src
suffix:semicolon
id|mskql
c_func
(paren
id|partial_dest
comma
id|doff
comma
id|partial_dest
)paren
suffix:semicolon
r_while
c_loop
(paren
id|len
op_ge
l_int|0
)paren
(brace
r_int
r_int
id|second
comma
id|word
suffix:semicolon
r_int
r_int
id|second_dest
suffix:semicolon
id|err
op_or_assign
id|__get_user_u
c_func
(paren
id|second
comma
id|src
op_plus
l_int|1
)paren
suffix:semicolon
id|extql
c_func
(paren
id|first
comma
id|soff
comma
id|word
)paren
suffix:semicolon
id|checksum
op_add_assign
id|carry
suffix:semicolon
id|len
op_sub_assign
l_int|8
suffix:semicolon
id|extqh
c_func
(paren
id|second
comma
id|soff
comma
id|first
)paren
suffix:semicolon
id|src
op_increment
suffix:semicolon
id|word
op_or_assign
id|first
suffix:semicolon
id|first
op_assign
id|second
suffix:semicolon
id|insql
c_func
(paren
id|word
comma
id|doff
comma
id|second_dest
)paren
suffix:semicolon
id|checksum
op_add_assign
id|word
suffix:semicolon
id|stq_u
c_func
(paren
id|partial_dest
op_or
id|second_dest
comma
id|dst
)paren
suffix:semicolon
id|carry
op_assign
id|checksum
OL
id|word
suffix:semicolon
id|insqh
c_func
(paren
id|word
comma
id|doff
comma
id|partial_dest
)paren
suffix:semicolon
id|dst
op_increment
suffix:semicolon
)brace
id|len
op_add_assign
id|doff
suffix:semicolon
id|checksum
op_add_assign
id|carry
suffix:semicolon
r_if
c_cond
(paren
id|len
op_ge
l_int|0
)paren
(brace
r_int
r_int
id|second
comma
id|word
suffix:semicolon
r_int
r_int
id|second_dest
suffix:semicolon
id|err
op_or_assign
id|__get_user_u
c_func
(paren
id|second
comma
id|lastsrc
)paren
suffix:semicolon
id|extql
c_func
(paren
id|first
comma
id|soff
comma
id|word
)paren
suffix:semicolon
id|extqh
c_func
(paren
id|second
comma
id|soff
comma
id|first
)paren
suffix:semicolon
id|word
op_or_assign
id|first
suffix:semicolon
id|first
op_assign
id|second
suffix:semicolon
id|mskql
c_func
(paren
id|word
comma
id|len
op_minus
id|doff
comma
id|word
)paren
suffix:semicolon
id|checksum
op_add_assign
id|word
suffix:semicolon
id|insql
c_func
(paren
id|word
comma
id|doff
comma
id|second_dest
)paren
suffix:semicolon
id|carry
op_assign
id|checksum
OL
id|word
suffix:semicolon
id|stq_u
c_func
(paren
id|partial_dest
op_or
id|second_dest
comma
id|dst
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
)paren
(brace
id|ldq_u
c_func
(paren
id|second_dest
comma
id|dst
op_plus
l_int|1
)paren
suffix:semicolon
id|insqh
c_func
(paren
id|word
comma
id|doff
comma
id|partial_dest
)paren
suffix:semicolon
id|mskqh
c_func
(paren
id|second_dest
comma
id|len
comma
id|second_dest
)paren
suffix:semicolon
id|stq_u
c_func
(paren
id|partial_dest
op_or
id|second_dest
comma
id|dst
op_plus
l_int|1
)paren
suffix:semicolon
)brace
id|checksum
op_add_assign
id|carry
suffix:semicolon
)brace
r_else
(brace
r_int
r_int
id|second
comma
id|word
suffix:semicolon
r_int
r_int
id|second_dest
suffix:semicolon
id|err
op_or_assign
id|__get_user_u
c_func
(paren
id|second
comma
id|lastsrc
)paren
suffix:semicolon
id|extql
c_func
(paren
id|first
comma
id|soff
comma
id|word
)paren
suffix:semicolon
id|extqh
c_func
(paren
id|second
comma
id|soff
comma
id|first
)paren
suffix:semicolon
id|word
op_or_assign
id|first
suffix:semicolon
id|ldq_u
c_func
(paren
id|second_dest
comma
id|dst
)paren
suffix:semicolon
id|mskql
c_func
(paren
id|word
comma
id|len
op_minus
id|doff
comma
id|word
)paren
suffix:semicolon
id|checksum
op_add_assign
id|word
suffix:semicolon
id|mskqh
c_func
(paren
id|second_dest
comma
id|len
comma
id|second_dest
)paren
suffix:semicolon
id|carry
op_assign
id|checksum
OL
id|word
suffix:semicolon
id|insql
c_func
(paren
id|word
comma
id|doff
comma
id|word
)paren
suffix:semicolon
id|stq_u
c_func
(paren
id|partial_dest
op_or
id|word
op_or
id|second_dest
comma
id|dst
)paren
suffix:semicolon
id|checksum
op_add_assign
id|carry
suffix:semicolon
)brace
r_if
c_cond
(paren
id|err
)paren
op_star
id|errp
op_assign
id|err
suffix:semicolon
r_return
id|checksum
suffix:semicolon
)brace
r_static
r_int
r_int
DECL|function|do_csum_partial_copy_from_user
id|do_csum_partial_copy_from_user
c_func
(paren
r_const
r_char
op_star
id|src
comma
r_char
op_star
id|dst
comma
r_int
id|len
comma
r_int
r_int
id|sum
comma
r_int
op_star
id|errp
)paren
(brace
r_int
r_int
id|checksum
op_assign
(paren
r_int
)paren
id|sum
suffix:semicolon
r_int
r_int
id|soff
op_assign
l_int|7
op_amp
(paren
r_int
r_int
)paren
id|src
suffix:semicolon
r_int
r_int
id|doff
op_assign
l_int|7
op_amp
(paren
r_int
r_int
)paren
id|dst
suffix:semicolon
r_if
c_cond
(paren
id|len
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|doff
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|soff
)paren
id|checksum
op_assign
id|csum_partial_cfu_aligned
c_func
(paren
(paren
r_const
r_int
r_int
op_star
)paren
id|src
comma
(paren
r_int
r_int
op_star
)paren
id|dst
comma
id|len
op_minus
l_int|8
comma
id|checksum
comma
id|errp
)paren
suffix:semicolon
r_else
id|checksum
op_assign
id|csum_partial_cfu_dest_aligned
c_func
(paren
(paren
r_const
r_int
r_int
op_star
)paren
id|src
comma
(paren
r_int
r_int
op_star
)paren
id|dst
comma
id|soff
comma
id|len
op_minus
l_int|8
comma
id|checksum
comma
id|errp
)paren
suffix:semicolon
)brace
r_else
(brace
r_int
r_int
id|partial_dest
suffix:semicolon
id|ldq_u
c_func
(paren
id|partial_dest
comma
id|dst
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|soff
)paren
id|checksum
op_assign
id|csum_partial_cfu_src_aligned
c_func
(paren
(paren
r_const
r_int
r_int
op_star
)paren
id|src
comma
(paren
r_int
r_int
op_star
)paren
id|dst
comma
id|doff
comma
id|len
op_minus
l_int|8
comma
id|checksum
comma
id|partial_dest
comma
id|errp
)paren
suffix:semicolon
r_else
id|checksum
op_assign
id|csum_partial_cfu_unaligned
c_func
(paren
(paren
r_const
r_int
r_int
op_star
)paren
id|src
comma
(paren
r_int
r_int
op_star
)paren
id|dst
comma
id|soff
comma
id|doff
comma
id|len
op_minus
l_int|8
comma
id|checksum
comma
id|partial_dest
comma
id|errp
)paren
suffix:semicolon
)brace
id|checksum
op_assign
id|from64to16
(paren
id|checksum
)paren
suffix:semicolon
)brace
r_return
id|checksum
suffix:semicolon
)brace
r_int
r_int
DECL|function|csum_partial_copy_from_user
id|csum_partial_copy_from_user
c_func
(paren
r_const
r_char
op_star
id|src
comma
r_char
op_star
id|dst
comma
r_int
id|len
comma
r_int
r_int
id|sum
comma
r_int
op_star
id|errp
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|access_ok
c_func
(paren
id|src
comma
id|len
comma
id|VERIFY_READ
)paren
)paren
(brace
op_star
id|errp
op_assign
op_minus
id|EFAULT
suffix:semicolon
id|memset
c_func
(paren
id|dst
comma
l_int|0
comma
id|len
)paren
suffix:semicolon
r_return
id|sum
suffix:semicolon
)brace
r_return
id|do_csum_partial_copy_from_user
c_func
(paren
id|src
comma
id|dst
comma
id|len
comma
id|sum
comma
id|errp
)paren
suffix:semicolon
)brace
r_int
r_int
DECL|function|csum_partial_copy_nocheck
id|csum_partial_copy_nocheck
c_func
(paren
r_const
r_char
op_star
id|src
comma
r_char
op_star
id|dst
comma
r_int
id|len
comma
r_int
r_int
id|sum
)paren
(brace
r_return
id|do_csum_partial_copy_from_user
c_func
(paren
id|src
comma
id|dst
comma
id|len
comma
id|sum
comma
l_int|NULL
)paren
suffix:semicolon
)brace
eof
