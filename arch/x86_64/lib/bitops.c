macro_line|#include &lt;linux/bitops.h&gt;
DECL|macro|find_first_zero_bit
macro_line|#undef find_first_zero_bit
DECL|macro|find_next_zero_bit
macro_line|#undef find_next_zero_bit
DECL|macro|find_first_bit
macro_line|#undef find_first_bit
DECL|macro|find_next_bit
macro_line|#undef find_next_bit
multiline_comment|/**&n; * find_first_zero_bit - find the first zero bit in a memory region&n; * @addr: The address to start the search at&n; * @size: The maximum size to search&n; *&n; * Returns the bit-number of the first zero bit, not the number of the byte&n; * containing a bit.&n; */
DECL|function|find_first_zero_bit
r_inline
r_int
id|find_first_zero_bit
c_func
(paren
r_const
r_int
r_int
op_star
id|addr
comma
r_int
r_int
id|size
)paren
(brace
r_int
id|d0
comma
id|d1
comma
id|d2
suffix:semicolon
r_int
id|res
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|size
)paren
r_return
l_int|0
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;  repe; scasq&bslash;n&quot;
l_string|&quot;  je 1f&bslash;n&quot;
l_string|&quot;  xorq -8(%%rdi),%%rax&bslash;n&quot;
l_string|&quot;  subq $8,%%rdi&bslash;n&quot;
l_string|&quot;  bsfq %%rax,%%rdx&bslash;n&quot;
l_string|&quot;1:  subq %[addr],%%rdi&bslash;n&quot;
l_string|&quot;  shlq $3,%%rdi&bslash;n&quot;
l_string|&quot;  addq %%rdi,%%rdx&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|res
)paren
comma
l_string|&quot;=&amp;c&quot;
(paren
id|d0
)paren
comma
l_string|&quot;=&amp;D&quot;
(paren
id|d1
)paren
comma
l_string|&quot;=&amp;a&quot;
(paren
id|d2
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
l_int|0ULL
)paren
comma
l_string|&quot;1&quot;
(paren
(paren
id|size
op_plus
l_int|63
)paren
op_rshift
l_int|6
)paren
comma
l_string|&quot;2&quot;
(paren
id|addr
)paren
comma
l_string|&quot;3&quot;
(paren
op_minus
l_int|1ULL
)paren
comma
(braket
id|addr
)braket
l_string|&quot;r&quot;
(paren
id|addr
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
multiline_comment|/**&n; * find_next_zero_bit - find the first zero bit in a memory region&n; * @addr: The address to base the search on&n; * @offset: The bitnumber to start searching at&n; * @size: The maximum size to search&n; */
DECL|function|find_next_zero_bit
r_int
id|find_next_zero_bit
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
l_int|6
)paren
suffix:semicolon
r_int
r_int
id|set
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|res
comma
id|bit
op_assign
id|offset
op_amp
l_int|63
suffix:semicolon
r_if
c_cond
(paren
id|bit
)paren
(brace
multiline_comment|/*&n;&t;&t; * Look for zero in first word&n;&t;&t; */
id|asm
c_func
(paren
l_string|&quot;bsfq %1,%0&bslash;n&bslash;t&quot;
l_string|&quot;cmoveq %2,%0&quot;
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
comma
l_string|&quot;r&quot;
(paren
l_int|64L
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|set
OL
(paren
l_int|64
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
l_int|64
op_minus
id|bit
suffix:semicolon
id|p
op_increment
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * No zero yet, search remaining full words for a zero&n;&t; */
id|res
op_assign
id|find_first_zero_bit
(paren
(paren
r_const
r_int
r_int
op_star
)paren
id|p
comma
id|size
op_minus
l_int|64
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
r_static
r_inline
r_int
DECL|function|__find_first_bit
id|__find_first_bit
c_func
(paren
r_const
r_int
r_int
op_star
id|addr
comma
r_int
r_int
id|size
)paren
(brace
r_int
id|d0
comma
id|d1
suffix:semicolon
r_int
id|res
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;   repe; scasq&bslash;n&quot;
l_string|&quot;   jz 1f&bslash;n&quot;
l_string|&quot;   subq $8,%%rdi&bslash;n&quot;
l_string|&quot;   bsfq (%%rdi),%%rax&bslash;n&quot;
l_string|&quot;1: subq %[addr],%%rdi&bslash;n&quot;
l_string|&quot;   shlq $3,%%rdi&bslash;n&quot;
l_string|&quot;   addq %%rdi,%%rax&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|res
)paren
comma
l_string|&quot;=&amp;c&quot;
(paren
id|d0
)paren
comma
l_string|&quot;=&amp;D&quot;
(paren
id|d1
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
l_int|0ULL
)paren
comma
l_string|&quot;1&quot;
(paren
(paren
id|size
op_plus
l_int|63
)paren
op_rshift
l_int|6
)paren
comma
l_string|&quot;2&quot;
(paren
id|addr
)paren
comma
(braket
id|addr
)braket
l_string|&quot;r&quot;
(paren
id|addr
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
multiline_comment|/**&n; * find_first_bit - find the first set bit in a memory region&n; * @addr: The address to start the search at&n; * @size: The maximum size to search&n; *&n; * Returns the bit-number of the first set bit, not the number of the byte&n; * containing a bit.&n; */
DECL|function|find_first_bit
r_int
id|find_first_bit
c_func
(paren
r_const
r_int
r_int
op_star
id|addr
comma
r_int
r_int
id|size
)paren
(brace
r_return
id|__find_first_bit
c_func
(paren
id|addr
comma
id|size
)paren
suffix:semicolon
)brace
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
l_int|6
)paren
suffix:semicolon
r_int
r_int
id|set
op_assign
l_int|0
comma
id|bit
op_assign
id|offset
op_amp
l_int|63
comma
id|res
suffix:semicolon
r_if
c_cond
(paren
id|bit
)paren
(brace
multiline_comment|/*&n;&t;&t; * Look for nonzero in the first 64 bits:&n;&t;&t; */
id|asm
c_func
(paren
l_string|&quot;bsfq %1,%0&bslash;n&bslash;t&quot;
l_string|&quot;cmoveq %2,%0&bslash;n&bslash;t&quot;
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
comma
l_string|&quot;r&quot;
(paren
l_int|64L
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|set
OL
(paren
l_int|64
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
l_int|64
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
id|__find_first_bit
(paren
id|p
comma
id|size
op_minus
l_int|64
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
macro_line|#include &lt;linux/module.h&gt;
DECL|variable|find_next_bit
id|EXPORT_SYMBOL
c_func
(paren
id|find_next_bit
)paren
suffix:semicolon
DECL|variable|find_first_bit
id|EXPORT_SYMBOL
c_func
(paren
id|find_first_bit
)paren
suffix:semicolon
DECL|variable|find_first_zero_bit
id|EXPORT_SYMBOL
c_func
(paren
id|find_first_zero_bit
)paren
suffix:semicolon
DECL|variable|find_next_zero_bit
id|EXPORT_SYMBOL
c_func
(paren
id|find_next_zero_bit
)paren
suffix:semicolon
eof
