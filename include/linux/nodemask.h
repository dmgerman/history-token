macro_line|#ifndef __LINUX_NODEMASK_H
DECL|macro|__LINUX_NODEMASK_H
mdefine_line|#define __LINUX_NODEMASK_H
multiline_comment|/*&n; * Nodemasks provide a bitmap suitable for representing the&n; * set of Node&squot;s in a system, one bit position per Node number.&n; *&n; * See detailed comments in the file linux/bitmap.h describing the&n; * data type on which these nodemasks are based.&n; *&n; * For details of nodemask_scnprintf() and nodemask_parse(),&n; * see bitmap_scnprintf() and bitmap_parse() in lib/bitmap.c.&n; * For details of nodelist_scnprintf() and nodelist_parse(), see&n; * bitmap_scnlistprintf() and bitmap_parselist(), also in bitmap.c.&n; *&n; * The available nodemask operations are:&n; *&n; * void node_set(node, mask)&t;&t;turn on bit &squot;node&squot; in mask&n; * void node_clear(node, mask)&t;&t;turn off bit &squot;node&squot; in mask&n; * void nodes_setall(mask)&t;&t;set all bits&n; * void nodes_clear(mask)&t;&t;clear all bits&n; * int node_isset(node, mask)&t;&t;true iff bit &squot;node&squot; set in mask&n; * int node_test_and_set(node, mask)&t;test and set bit &squot;node&squot; in mask&n; *&n; * void nodes_and(dst, src1, src2)&t;dst = src1 &amp; src2  [intersection]&n; * void nodes_or(dst, src1, src2)&t;dst = src1 | src2  [union]&n; * void nodes_xor(dst, src1, src2)&t;dst = src1 ^ src2&n; * void nodes_andnot(dst, src1, src2)&t;dst = src1 &amp; ~src2&n; * void nodes_complement(dst, src)&t;dst = ~src&n; *&n; * int nodes_equal(mask1, mask2)&t;Does mask1 == mask2?&n; * int nodes_intersects(mask1, mask2)&t;Do mask1 and mask2 intersect?&n; * int nodes_subset(mask1, mask2)&t;Is mask1 a subset of mask2?&n; * int nodes_empty(mask)&t;&t;Is mask empty (no bits sets)?&n; * int nodes_full(mask)&t;&t;&t;Is mask full (all bits sets)?&n; * int nodes_weight(mask)&t;&t;Hamming weight - number of set bits&n; *&n; * void nodes_shift_right(dst, src, n)&t;Shift right&n; * void nodes_shift_left(dst, src, n)&t;Shift left&n; *&n; * int first_node(mask)&t;&t;&t;Number lowest set bit, or MAX_NUMNODES&n; * int next_node(node, mask)&t;&t;Next node past &squot;node&squot;, or MAX_NUMNODES&n; * int first_unset_node(mask)&t;&t;First node not set in mask, or &n; *&t;&t;&t;&t;&t;MAX_NUMNODES.&n; *&n; * nodemask_t nodemask_of_node(node)&t;Return nodemask with bit &squot;node&squot; set&n; * NODE_MASK_ALL&t;&t;&t;Initializer - all bits set&n; * NODE_MASK_NONE&t;&t;&t;Initializer - no bits set&n; * unsigned long *nodes_addr(mask)&t;Array of unsigned long&squot;s in mask&n; *&n; * int nodemask_scnprintf(buf, len, mask) Format nodemask for printing&n; * int nodemask_parse(ubuf, ulen, mask)&t;Parse ascii string as nodemask&n; * int nodelist_scnprintf(buf, len, mask) Format nodemask as list for printing&n; * int nodelist_parse(buf, map)&t;&t;Parse ascii string as nodelist&n; *&n; * for_each_node_mask(node, mask)&t;for-loop node over mask&n; *&n; * int num_online_nodes()&t;&t;Number of online Nodes&n; * int num_possible_nodes()&t;&t;Number of all possible Nodes&n; *&n; * int node_online(node)&t;&t;Is some node online?&n; * int node_possible(node)&t;&t;Is some node possible?&n; *&n; * int any_online_node(mask)&t;&t;First online node in mask&n; *&n; * node_set_online(node)&t;&t;set bit &squot;node&squot; in node_online_map&n; * node_set_offline(node)&t;&t;clear bit &squot;node&squot; in node_online_map&n; *&n; * for_each_node(node)&t;&t;&t;for-loop node over node_possible_map&n; * for_each_online_node(node)&t;&t;for-loop node over node_online_map&n; *&n; * Subtlety:&n; * 1) The &squot;type-checked&squot; form of node_isset() causes gcc (3.3.2, anyway)&n; *    to generate slightly worse code.  So use a simple one-line #define&n; *    for node_isset(), instead of wrapping an inline inside a macro, the&n; *    way we do the other calls.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;linux/bitmap.h&gt;
macro_line|#include &lt;linux/numa.h&gt;
macro_line|#include &lt;asm/bug.h&gt;
DECL|typedef|nodemask_t
r_typedef
r_struct
(brace
id|DECLARE_BITMAP
c_func
(paren
id|bits
comma
id|MAX_NUMNODES
)paren
suffix:semicolon
)brace
id|nodemask_t
suffix:semicolon
r_extern
id|nodemask_t
id|_unused_nodemask_arg_
suffix:semicolon
DECL|macro|node_set
mdefine_line|#define node_set(node, dst) __node_set((node), &amp;(dst))
DECL|function|__node_set
r_static
r_inline
r_void
id|__node_set
c_func
(paren
r_int
id|node
comma
r_volatile
id|nodemask_t
op_star
id|dstp
)paren
(brace
id|set_bit
c_func
(paren
id|node
comma
id|dstp-&gt;bits
)paren
suffix:semicolon
)brace
DECL|macro|node_clear
mdefine_line|#define node_clear(node, dst) __node_clear((node), &amp;(dst))
DECL|function|__node_clear
r_static
r_inline
r_void
id|__node_clear
c_func
(paren
r_int
id|node
comma
r_volatile
id|nodemask_t
op_star
id|dstp
)paren
(brace
id|clear_bit
c_func
(paren
id|node
comma
id|dstp-&gt;bits
)paren
suffix:semicolon
)brace
DECL|macro|nodes_setall
mdefine_line|#define nodes_setall(dst) __nodes_setall(&amp;(dst), MAX_NUMNODES)
DECL|function|__nodes_setall
r_static
r_inline
r_void
id|__nodes_setall
c_func
(paren
id|nodemask_t
op_star
id|dstp
comma
r_int
id|nbits
)paren
(brace
id|bitmap_fill
c_func
(paren
id|dstp-&gt;bits
comma
id|nbits
)paren
suffix:semicolon
)brace
DECL|macro|nodes_clear
mdefine_line|#define nodes_clear(dst) __nodes_clear(&amp;(dst), MAX_NUMNODES)
DECL|function|__nodes_clear
r_static
r_inline
r_void
id|__nodes_clear
c_func
(paren
id|nodemask_t
op_star
id|dstp
comma
r_int
id|nbits
)paren
(brace
id|bitmap_zero
c_func
(paren
id|dstp-&gt;bits
comma
id|nbits
)paren
suffix:semicolon
)brace
multiline_comment|/* No static inline type checking - see Subtlety (1) above. */
DECL|macro|node_isset
mdefine_line|#define node_isset(node, nodemask) test_bit((node), (nodemask).bits)
DECL|macro|node_test_and_set
mdefine_line|#define node_test_and_set(node, nodemask) &bslash;&n;&t;&t;&t;__node_test_and_set((node), &amp;(nodemask))
DECL|function|__node_test_and_set
r_static
r_inline
r_int
id|__node_test_and_set
c_func
(paren
r_int
id|node
comma
id|nodemask_t
op_star
id|addr
)paren
(brace
r_return
id|test_and_set_bit
c_func
(paren
id|node
comma
id|addr-&gt;bits
)paren
suffix:semicolon
)brace
DECL|macro|nodes_and
mdefine_line|#define nodes_and(dst, src1, src2) &bslash;&n;&t;&t;&t;__nodes_and(&amp;(dst), &amp;(src1), &amp;(src2), MAX_NUMNODES)
DECL|function|__nodes_and
r_static
r_inline
r_void
id|__nodes_and
c_func
(paren
id|nodemask_t
op_star
id|dstp
comma
r_const
id|nodemask_t
op_star
id|src1p
comma
r_const
id|nodemask_t
op_star
id|src2p
comma
r_int
id|nbits
)paren
(brace
id|bitmap_and
c_func
(paren
id|dstp-&gt;bits
comma
id|src1p-&gt;bits
comma
id|src2p-&gt;bits
comma
id|nbits
)paren
suffix:semicolon
)brace
DECL|macro|nodes_or
mdefine_line|#define nodes_or(dst, src1, src2) &bslash;&n;&t;&t;&t;__nodes_or(&amp;(dst), &amp;(src1), &amp;(src2), MAX_NUMNODES)
DECL|function|__nodes_or
r_static
r_inline
r_void
id|__nodes_or
c_func
(paren
id|nodemask_t
op_star
id|dstp
comma
r_const
id|nodemask_t
op_star
id|src1p
comma
r_const
id|nodemask_t
op_star
id|src2p
comma
r_int
id|nbits
)paren
(brace
id|bitmap_or
c_func
(paren
id|dstp-&gt;bits
comma
id|src1p-&gt;bits
comma
id|src2p-&gt;bits
comma
id|nbits
)paren
suffix:semicolon
)brace
DECL|macro|nodes_xor
mdefine_line|#define nodes_xor(dst, src1, src2) &bslash;&n;&t;&t;&t;__nodes_xor(&amp;(dst), &amp;(src1), &amp;(src2), MAX_NUMNODES)
DECL|function|__nodes_xor
r_static
r_inline
r_void
id|__nodes_xor
c_func
(paren
id|nodemask_t
op_star
id|dstp
comma
r_const
id|nodemask_t
op_star
id|src1p
comma
r_const
id|nodemask_t
op_star
id|src2p
comma
r_int
id|nbits
)paren
(brace
id|bitmap_xor
c_func
(paren
id|dstp-&gt;bits
comma
id|src1p-&gt;bits
comma
id|src2p-&gt;bits
comma
id|nbits
)paren
suffix:semicolon
)brace
DECL|macro|nodes_andnot
mdefine_line|#define nodes_andnot(dst, src1, src2) &bslash;&n;&t;&t;&t;__nodes_andnot(&amp;(dst), &amp;(src1), &amp;(src2), MAX_NUMNODES)
DECL|function|__nodes_andnot
r_static
r_inline
r_void
id|__nodes_andnot
c_func
(paren
id|nodemask_t
op_star
id|dstp
comma
r_const
id|nodemask_t
op_star
id|src1p
comma
r_const
id|nodemask_t
op_star
id|src2p
comma
r_int
id|nbits
)paren
(brace
id|bitmap_andnot
c_func
(paren
id|dstp-&gt;bits
comma
id|src1p-&gt;bits
comma
id|src2p-&gt;bits
comma
id|nbits
)paren
suffix:semicolon
)brace
DECL|macro|nodes_complement
mdefine_line|#define nodes_complement(dst, src) &bslash;&n;&t;&t;&t;__nodes_complement(&amp;(dst), &amp;(src), MAX_NUMNODES)
DECL|function|__nodes_complement
r_static
r_inline
r_void
id|__nodes_complement
c_func
(paren
id|nodemask_t
op_star
id|dstp
comma
r_const
id|nodemask_t
op_star
id|srcp
comma
r_int
id|nbits
)paren
(brace
id|bitmap_complement
c_func
(paren
id|dstp-&gt;bits
comma
id|srcp-&gt;bits
comma
id|nbits
)paren
suffix:semicolon
)brace
DECL|macro|nodes_equal
mdefine_line|#define nodes_equal(src1, src2) &bslash;&n;&t;&t;&t;__nodes_equal(&amp;(src1), &amp;(src2), MAX_NUMNODES)
DECL|function|__nodes_equal
r_static
r_inline
r_int
id|__nodes_equal
c_func
(paren
r_const
id|nodemask_t
op_star
id|src1p
comma
r_const
id|nodemask_t
op_star
id|src2p
comma
r_int
id|nbits
)paren
(brace
r_return
id|bitmap_equal
c_func
(paren
id|src1p-&gt;bits
comma
id|src2p-&gt;bits
comma
id|nbits
)paren
suffix:semicolon
)brace
DECL|macro|nodes_intersects
mdefine_line|#define nodes_intersects(src1, src2) &bslash;&n;&t;&t;&t;__nodes_intersects(&amp;(src1), &amp;(src2), MAX_NUMNODES)
DECL|function|__nodes_intersects
r_static
r_inline
r_int
id|__nodes_intersects
c_func
(paren
r_const
id|nodemask_t
op_star
id|src1p
comma
r_const
id|nodemask_t
op_star
id|src2p
comma
r_int
id|nbits
)paren
(brace
r_return
id|bitmap_intersects
c_func
(paren
id|src1p-&gt;bits
comma
id|src2p-&gt;bits
comma
id|nbits
)paren
suffix:semicolon
)brace
DECL|macro|nodes_subset
mdefine_line|#define nodes_subset(src1, src2) &bslash;&n;&t;&t;&t;__nodes_subset(&amp;(src1), &amp;(src2), MAX_NUMNODES)
DECL|function|__nodes_subset
r_static
r_inline
r_int
id|__nodes_subset
c_func
(paren
r_const
id|nodemask_t
op_star
id|src1p
comma
r_const
id|nodemask_t
op_star
id|src2p
comma
r_int
id|nbits
)paren
(brace
r_return
id|bitmap_subset
c_func
(paren
id|src1p-&gt;bits
comma
id|src2p-&gt;bits
comma
id|nbits
)paren
suffix:semicolon
)brace
DECL|macro|nodes_empty
mdefine_line|#define nodes_empty(src) __nodes_empty(&amp;(src), MAX_NUMNODES)
DECL|function|__nodes_empty
r_static
r_inline
r_int
id|__nodes_empty
c_func
(paren
r_const
id|nodemask_t
op_star
id|srcp
comma
r_int
id|nbits
)paren
(brace
r_return
id|bitmap_empty
c_func
(paren
id|srcp-&gt;bits
comma
id|nbits
)paren
suffix:semicolon
)brace
DECL|macro|nodes_full
mdefine_line|#define nodes_full(nodemask) __nodes_full(&amp;(nodemask), MAX_NUMNODES)
DECL|function|__nodes_full
r_static
r_inline
r_int
id|__nodes_full
c_func
(paren
r_const
id|nodemask_t
op_star
id|srcp
comma
r_int
id|nbits
)paren
(brace
r_return
id|bitmap_full
c_func
(paren
id|srcp-&gt;bits
comma
id|nbits
)paren
suffix:semicolon
)brace
DECL|macro|nodes_weight
mdefine_line|#define nodes_weight(nodemask) __nodes_weight(&amp;(nodemask), MAX_NUMNODES)
DECL|function|__nodes_weight
r_static
r_inline
r_int
id|__nodes_weight
c_func
(paren
r_const
id|nodemask_t
op_star
id|srcp
comma
r_int
id|nbits
)paren
(brace
r_return
id|bitmap_weight
c_func
(paren
id|srcp-&gt;bits
comma
id|nbits
)paren
suffix:semicolon
)brace
DECL|macro|nodes_shift_right
mdefine_line|#define nodes_shift_right(dst, src, n) &bslash;&n;&t;&t;&t;__nodes_shift_right(&amp;(dst), &amp;(src), (n), MAX_NUMNODES)
DECL|function|__nodes_shift_right
r_static
r_inline
r_void
id|__nodes_shift_right
c_func
(paren
id|nodemask_t
op_star
id|dstp
comma
r_const
id|nodemask_t
op_star
id|srcp
comma
r_int
id|n
comma
r_int
id|nbits
)paren
(brace
id|bitmap_shift_right
c_func
(paren
id|dstp-&gt;bits
comma
id|srcp-&gt;bits
comma
id|n
comma
id|nbits
)paren
suffix:semicolon
)brace
DECL|macro|nodes_shift_left
mdefine_line|#define nodes_shift_left(dst, src, n) &bslash;&n;&t;&t;&t;__nodes_shift_left(&amp;(dst), &amp;(src), (n), MAX_NUMNODES)
DECL|function|__nodes_shift_left
r_static
r_inline
r_void
id|__nodes_shift_left
c_func
(paren
id|nodemask_t
op_star
id|dstp
comma
r_const
id|nodemask_t
op_star
id|srcp
comma
r_int
id|n
comma
r_int
id|nbits
)paren
(brace
id|bitmap_shift_left
c_func
(paren
id|dstp-&gt;bits
comma
id|srcp-&gt;bits
comma
id|n
comma
id|nbits
)paren
suffix:semicolon
)brace
multiline_comment|/* FIXME: better would be to fix all architectures to never return&n;          &gt; MAX_NUMNODES, then the silly min_ts could be dropped. */
DECL|macro|first_node
mdefine_line|#define first_node(src) __first_node(&amp;(src))
DECL|function|__first_node
r_static
r_inline
r_int
id|__first_node
c_func
(paren
r_const
id|nodemask_t
op_star
id|srcp
)paren
(brace
r_return
id|min_t
c_func
(paren
r_int
comma
id|MAX_NUMNODES
comma
id|find_first_bit
c_func
(paren
id|srcp-&gt;bits
comma
id|MAX_NUMNODES
)paren
)paren
suffix:semicolon
)brace
DECL|macro|next_node
mdefine_line|#define next_node(n, src) __next_node((n), &amp;(src))
DECL|function|__next_node
r_static
r_inline
r_int
id|__next_node
c_func
(paren
r_int
id|n
comma
r_const
id|nodemask_t
op_star
id|srcp
)paren
(brace
r_return
id|min_t
c_func
(paren
r_int
comma
id|MAX_NUMNODES
comma
id|find_next_bit
c_func
(paren
id|srcp-&gt;bits
comma
id|MAX_NUMNODES
comma
id|n
op_plus
l_int|1
)paren
)paren
suffix:semicolon
)brace
DECL|macro|nodemask_of_node
mdefine_line|#define nodemask_of_node(node)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;typeof(_unused_nodemask_arg_) m;&t;&t;&t;&t;&bslash;&n;&t;if (sizeof(m) == sizeof(unsigned long)) {&t;&t;&t;&bslash;&n;&t;&t;m.bits[0] = 1UL&lt;&lt;(node);&t;&t;&t;&t;&bslash;&n;&t;} else {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;nodes_clear(m);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;node_set((node), m);&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;m;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|first_unset_node
mdefine_line|#define first_unset_node(mask) __first_unset_node(&amp;(mask))
DECL|function|__first_unset_node
r_static
r_inline
r_int
id|__first_unset_node
c_func
(paren
r_const
id|nodemask_t
op_star
id|maskp
)paren
(brace
r_return
id|min_t
c_func
(paren
r_int
comma
id|MAX_NUMNODES
comma
id|find_first_zero_bit
c_func
(paren
id|maskp-&gt;bits
comma
id|MAX_NUMNODES
)paren
)paren
suffix:semicolon
)brace
DECL|macro|NODE_MASK_LAST_WORD
mdefine_line|#define NODE_MASK_LAST_WORD BITMAP_LAST_WORD_MASK(MAX_NUMNODES)
macro_line|#if MAX_NUMNODES &lt;= BITS_PER_LONG
DECL|macro|NODE_MASK_ALL
mdefine_line|#define NODE_MASK_ALL&t;&t;&t;&t;&t;&t;&t;&bslash;&n;((nodemask_t) { {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;[BITS_TO_LONGS(MAX_NUMNODES)-1] = NODE_MASK_LAST_WORD&t;&t;&bslash;&n;} })
macro_line|#else
DECL|macro|NODE_MASK_ALL
mdefine_line|#define NODE_MASK_ALL&t;&t;&t;&t;&t;&t;&t;&bslash;&n;((nodemask_t) { {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;[0 ... BITS_TO_LONGS(MAX_NUMNODES)-2] = ~0UL,&t;&t;&t;&bslash;&n;&t;[BITS_TO_LONGS(MAX_NUMNODES)-1] = NODE_MASK_LAST_WORD&t;&t;&bslash;&n;} })
macro_line|#endif
DECL|macro|NODE_MASK_NONE
mdefine_line|#define NODE_MASK_NONE&t;&t;&t;&t;&t;&t;&t;&bslash;&n;((nodemask_t) { {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;[0 ... BITS_TO_LONGS(MAX_NUMNODES)-1] =  0UL&t;&t;&t;&bslash;&n;} })
DECL|macro|nodes_addr
mdefine_line|#define nodes_addr(src) ((src).bits)
DECL|macro|nodemask_scnprintf
mdefine_line|#define nodemask_scnprintf(buf, len, src) &bslash;&n;&t;&t;&t;__nodemask_scnprintf((buf), (len), &amp;(src), MAX_NUMNODES)
DECL|function|__nodemask_scnprintf
r_static
r_inline
r_int
id|__nodemask_scnprintf
c_func
(paren
r_char
op_star
id|buf
comma
r_int
id|len
comma
r_const
id|nodemask_t
op_star
id|srcp
comma
r_int
id|nbits
)paren
(brace
r_return
id|bitmap_scnprintf
c_func
(paren
id|buf
comma
id|len
comma
id|srcp-&gt;bits
comma
id|nbits
)paren
suffix:semicolon
)brace
DECL|macro|nodemask_parse
mdefine_line|#define nodemask_parse(ubuf, ulen, dst) &bslash;&n;&t;&t;&t;__nodemask_parse((ubuf), (ulen), &amp;(dst), MAX_NUMNODES)
DECL|function|__nodemask_parse
r_static
r_inline
r_int
id|__nodemask_parse
c_func
(paren
r_const
r_char
id|__user
op_star
id|buf
comma
r_int
id|len
comma
id|nodemask_t
op_star
id|dstp
comma
r_int
id|nbits
)paren
(brace
r_return
id|bitmap_parse
c_func
(paren
id|buf
comma
id|len
comma
id|dstp-&gt;bits
comma
id|nbits
)paren
suffix:semicolon
)brace
DECL|macro|nodelist_scnprintf
mdefine_line|#define nodelist_scnprintf(buf, len, src) &bslash;&n;&t;&t;&t;__nodelist_scnprintf((buf), (len), &amp;(src), MAX_NUMNODES)
DECL|function|__nodelist_scnprintf
r_static
r_inline
r_int
id|__nodelist_scnprintf
c_func
(paren
r_char
op_star
id|buf
comma
r_int
id|len
comma
r_const
id|nodemask_t
op_star
id|srcp
comma
r_int
id|nbits
)paren
(brace
r_return
id|bitmap_scnlistprintf
c_func
(paren
id|buf
comma
id|len
comma
id|srcp-&gt;bits
comma
id|nbits
)paren
suffix:semicolon
)brace
DECL|macro|nodelist_parse
mdefine_line|#define nodelist_parse(buf, dst) __nodelist_parse((buf), &amp;(dst), MAX_NUMNODES)
DECL|function|__nodelist_parse
r_static
r_inline
r_int
id|__nodelist_parse
c_func
(paren
r_const
r_char
op_star
id|buf
comma
id|nodemask_t
op_star
id|dstp
comma
r_int
id|nbits
)paren
(brace
r_return
id|bitmap_parselist
c_func
(paren
id|buf
comma
id|dstp-&gt;bits
comma
id|nbits
)paren
suffix:semicolon
)brace
macro_line|#if MAX_NUMNODES &gt; 1
DECL|macro|for_each_node_mask
mdefine_line|#define for_each_node_mask(node, mask)&t;&t;&t;&bslash;&n;&t;for ((node) = first_node(mask);&t;&t;&t;&bslash;&n;&t;&t;(node) &lt; MAX_NUMNODES;&t;&t;&t;&bslash;&n;&t;&t;(node) = next_node((node), (mask)))
macro_line|#else /* MAX_NUMNODES == 1 */
DECL|macro|for_each_node_mask
mdefine_line|#define for_each_node_mask(node, mask)&t;&t;&t;&bslash;&n;&t;if (!nodes_empty(mask))&t;&t;&t;&t;&bslash;&n;&t;&t;for ((node) = 0; (node) &lt; 1; (node)++)
macro_line|#endif /* MAX_NUMNODES */
multiline_comment|/*&n; * The following particular system nodemasks and operations&n; * on them manage all possible and online nodes.&n; */
r_extern
id|nodemask_t
id|node_online_map
suffix:semicolon
r_extern
id|nodemask_t
id|node_possible_map
suffix:semicolon
macro_line|#if MAX_NUMNODES &gt; 1
DECL|macro|num_online_nodes
mdefine_line|#define num_online_nodes()&t;nodes_weight(node_online_map)
DECL|macro|num_possible_nodes
mdefine_line|#define num_possible_nodes()&t;nodes_weight(node_possible_map)
DECL|macro|node_online
mdefine_line|#define node_online(node)&t;node_isset((node), node_online_map)
DECL|macro|node_possible
mdefine_line|#define node_possible(node)&t;node_isset((node), node_possible_map)
macro_line|#else
DECL|macro|num_online_nodes
mdefine_line|#define num_online_nodes()&t;1
DECL|macro|num_possible_nodes
mdefine_line|#define num_possible_nodes()&t;1
DECL|macro|node_online
mdefine_line|#define node_online(node)&t;((node) == 0)
DECL|macro|node_possible
mdefine_line|#define node_possible(node)&t;((node) == 0)
macro_line|#endif
DECL|macro|any_online_node
mdefine_line|#define any_online_node(mask)&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&bslash;&n;&t;int node;&t;&t;&t;&t;&bslash;&n;&t;for_each_node_mask(node, (mask))&t;&bslash;&n;&t;&t;if (node_online(node))&t;&t;&bslash;&n;&t;&t;&t;break;&t;&t;&t;&bslash;&n;&t;node;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|node_set_online
mdefine_line|#define node_set_online(node)&t;   set_bit((node), node_online_map.bits)
DECL|macro|node_set_offline
mdefine_line|#define node_set_offline(node)&t;   clear_bit((node), node_online_map.bits)
DECL|macro|for_each_node
mdefine_line|#define for_each_node(node)&t;   for_each_node_mask((node), node_possible_map)
DECL|macro|for_each_online_node
mdefine_line|#define for_each_online_node(node) for_each_node_mask((node), node_online_map)
macro_line|#endif /* __LINUX_NODEMASK_H */
eof
