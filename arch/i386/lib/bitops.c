macro_line|#include &lt;linux/bitops.h&gt;
macro_line|#include &lt;linux/module.h&gt;
multiline_comment|/**&n; * find_next_bit - find the first set bit in a memory region&n; * @addr: The address to base the search on&n; * @offset: The bitnumber to start searching at&n; * @size: The maximum size to search&n; */
DECL|function|find_next_bit
r_int
id|find_next_bit
c_func
(paren
r_const
r_int
r_int
op_star
id|addr
comma
r_int
id|size
comma
r_int
id|offset
)paren
(brace
r_const
r_int
r_int
op_star
id|p
op_assign
id|addr
op_plus
(paren
id|offset
op_rshift
l_int|5
)paren
suffix:semicolon
r_int
id|set
op_assign
l_int|0
comma
id|bit
op_assign
id|offset
op_amp
l_int|31
comma
id|res
suffix:semicolon
r_if
c_cond
(paren
id|bit
)paren
(brace
multiline_comment|/*&n;&t;&t; * Look for nonzero in the first 32 bits:&n;&t;&t; */
id|__asm__
c_func
(paren
l_string|&quot;bsfl %1,%0&bslash;n&bslash;t&quot;
l_string|&quot;jne 1f&bslash;n&bslash;t&quot;
l_string|&quot;movl $32, %0&bslash;n&quot;
l_string|&quot;1:&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|set
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
op_star
id|p
op_rshift
id|bit
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|set
OL
(paren
l_int|32
op_minus
id|bit
)paren
)paren
r_return
id|set
op_plus
id|offset
suffix:semicolon
id|set
op_assign
l_int|32
op_minus
id|bit
suffix:semicolon
id|p
op_increment
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * No set bit yet, search remaining full words for a bit&n;&t; */
id|res
op_assign
id|find_first_bit
(paren
id|p
comma
id|size
op_minus
l_int|32
op_star
(paren
id|p
op_minus
id|addr
)paren
)paren
suffix:semicolon
r_return
(paren
id|offset
op_plus
id|set
op_plus
id|res
)paren
suffix:semicolon
)brace
DECL|variable|find_next_bit
id|EXPORT_SYMBOL
c_func
(paren
id|find_next_bit
)paren
suffix:semicolon
multiline_comment|/**&n; * find_next_zero_bit - find the first zero bit in a memory region&n; * @addr: The address to base the search on&n; * @offset: The bitnumber to start searching at&n; * @size: The maximum size to search&n; */
DECL|function|find_next_zero_bit
r_int
id|find_next_zero_bit
c_func
(paren
r_const
r_int
r_int
op_star
id|addr
comma
r_int
id|size
comma
r_int
id|offset
)paren
(brace
r_int
r_int
op_star
id|p
op_assign
(paren
(paren
r_int
r_int
op_star
)paren
id|addr
)paren
op_plus
(paren
id|offset
op_rshift
l_int|5
)paren
suffix:semicolon
r_int
id|set
op_assign
l_int|0
comma
id|bit
op_assign
id|offset
op_amp
l_int|31
comma
id|res
suffix:semicolon
r_if
c_cond
(paren
id|bit
)paren
(brace
multiline_comment|/*&n;&t;&t; * Look for zero in the first 32 bits.&n;&t;&t; */
id|__asm__
c_func
(paren
l_string|&quot;bsfl %1,%0&bslash;n&bslash;t&quot;
l_string|&quot;jne 1f&bslash;n&bslash;t&quot;
l_string|&quot;movl $32, %0&bslash;n&quot;
l_string|&quot;1:&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|set
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
op_complement
(paren
op_star
id|p
op_rshift
id|bit
)paren
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|set
OL
(paren
l_int|32
op_minus
id|bit
)paren
)paren
r_return
id|set
op_plus
id|offset
suffix:semicolon
id|set
op_assign
l_int|32
op_minus
id|bit
suffix:semicolon
id|p
op_increment
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * No zero yet, search remaining full bytes for a zero&n;&t; */
id|res
op_assign
id|find_first_zero_bit
(paren
id|p
comma
id|size
op_minus
l_int|32
op_star
(paren
id|p
op_minus
(paren
r_int
r_int
op_star
)paren
id|addr
)paren
)paren
suffix:semicolon
r_return
(paren
id|offset
op_plus
id|set
op_plus
id|res
)paren
suffix:semicolon
)brace
DECL|variable|find_next_zero_bit
id|EXPORT_SYMBOL
c_func
(paren
id|find_next_zero_bit
)paren
suffix:semicolon
eof
