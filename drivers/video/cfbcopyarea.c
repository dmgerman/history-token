multiline_comment|/*&n; *  Generic function for frame buffer with packed pixels of any depth.&n; *&n; *      Copyright (C)  June 1999 James Simmons&n; *&n; *  This file is subject to the terms and conditions of the GNU General Public&n; *  License.  See the file COPYING in the main directory of this archive for&n; *  more details.&n; *&n; * NOTES:&n; * &n; *  This is for cfb packed pixels. Iplan and such are incorporated in the &n; *  drivers that need them.&n; * &n; *  FIXME&n; *  The code for 24 bit is horrible. It copies byte by byte size instead of &n; *  longs like the other sizes. Needs to be optimized. &n; *&n; *  Also need to add code to deal with cards endians that are different than &n; *  the native cpu endians. I also need to deal with MSB position in the word.&n; *  &n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/fb.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;asm/io.h&gt;
DECL|macro|LONG_MASK
mdefine_line|#define LONG_MASK  (BITS_PER_LONG - 1)
macro_line|#if BITS_PER_LONG == 32
DECL|macro|FB_WRITEL
mdefine_line|#define FB_WRITEL fb_writel
DECL|macro|FB_READL
mdefine_line|#define FB_READL  fb_readl
DECL|macro|SHIFT_PER_LONG
mdefine_line|#define SHIFT_PER_LONG 5
DECL|macro|BYTES_PER_LONG
mdefine_line|#define BYTES_PER_LONG 4
macro_line|#else
DECL|macro|FB_WRITEL
mdefine_line|#define FB_WRITEL fb_writeq
DECL|macro|FB_READL
mdefine_line|#define FB_READL  fb_readq
DECL|macro|SHIFT_PER_LONG
mdefine_line|#define SHIFT_PER_LONG 6
DECL|macro|BYTES_PER_LONG
mdefine_line|#define BYTES_PER_LONG 8
macro_line|#endif
DECL|function|bitcpy
r_static
r_void
id|bitcpy
c_func
(paren
r_int
r_int
op_star
id|dst
comma
r_int
id|dst_idx
comma
r_const
r_int
r_int
op_star
id|src
comma
r_int
id|src_idx
comma
r_int
r_int
id|n
)paren
(brace
r_int
r_int
id|first
comma
id|last
suffix:semicolon
r_int
id|shift
op_assign
id|dst_idx
op_minus
id|src_idx
comma
id|left
comma
id|right
suffix:semicolon
r_int
r_int
id|d0
comma
id|d1
suffix:semicolon
r_int
id|m
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|n
)paren
r_return
suffix:semicolon
id|shift
op_assign
id|dst_idx
op_minus
id|src_idx
suffix:semicolon
id|first
op_assign
op_complement
l_int|0UL
op_rshift
id|dst_idx
suffix:semicolon
id|last
op_assign
op_complement
(paren
op_complement
l_int|0UL
op_rshift
(paren
(paren
id|dst_idx
op_plus
id|n
)paren
op_mod
id|BITS_PER_LONG
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|shift
)paren
(brace
singleline_comment|// Same alignment for source and dest
r_if
c_cond
(paren
id|dst_idx
op_plus
id|n
op_le
id|BITS_PER_LONG
)paren
(brace
singleline_comment|// Single word
r_if
c_cond
(paren
id|last
)paren
id|first
op_and_assign
id|last
suffix:semicolon
id|FB_WRITEL
c_func
(paren
(paren
id|FB_READL
c_func
(paren
id|src
)paren
op_amp
id|first
)paren
op_or
(paren
id|FB_READL
c_func
(paren
id|dst
)paren
op_amp
op_complement
id|first
)paren
comma
id|dst
)paren
suffix:semicolon
)brace
r_else
(brace
singleline_comment|// Multiple destination words
singleline_comment|// Leading bits
r_if
c_cond
(paren
id|first
)paren
(brace
id|FB_WRITEL
c_func
(paren
(paren
id|FB_READL
c_func
(paren
id|src
)paren
op_amp
id|first
)paren
op_or
(paren
id|FB_READL
c_func
(paren
id|dst
)paren
op_amp
op_complement
id|first
)paren
comma
id|dst
)paren
suffix:semicolon
id|dst
op_increment
suffix:semicolon
id|src
op_increment
suffix:semicolon
id|n
op_sub_assign
id|BITS_PER_LONG
op_minus
id|dst_idx
suffix:semicolon
)brace
singleline_comment|// Main chunk
id|n
op_div_assign
id|BITS_PER_LONG
suffix:semicolon
r_while
c_loop
(paren
id|n
op_ge
l_int|8
)paren
(brace
id|FB_WRITEL
c_func
(paren
id|FB_READL
c_func
(paren
id|src
op_increment
)paren
comma
id|dst
op_increment
)paren
suffix:semicolon
id|FB_WRITEL
c_func
(paren
id|FB_READL
c_func
(paren
id|src
op_increment
)paren
comma
id|dst
op_increment
)paren
suffix:semicolon
id|FB_WRITEL
c_func
(paren
id|FB_READL
c_func
(paren
id|src
op_increment
)paren
comma
id|dst
op_increment
)paren
suffix:semicolon
id|FB_WRITEL
c_func
(paren
id|FB_READL
c_func
(paren
id|src
op_increment
)paren
comma
id|dst
op_increment
)paren
suffix:semicolon
id|FB_WRITEL
c_func
(paren
id|FB_READL
c_func
(paren
id|src
op_increment
)paren
comma
id|dst
op_increment
)paren
suffix:semicolon
id|FB_WRITEL
c_func
(paren
id|FB_READL
c_func
(paren
id|src
op_increment
)paren
comma
id|dst
op_increment
)paren
suffix:semicolon
id|FB_WRITEL
c_func
(paren
id|FB_READL
c_func
(paren
id|src
op_increment
)paren
comma
id|dst
op_increment
)paren
suffix:semicolon
id|FB_WRITEL
c_func
(paren
id|FB_READL
c_func
(paren
id|src
op_increment
)paren
comma
id|dst
op_increment
)paren
suffix:semicolon
id|n
op_sub_assign
l_int|8
suffix:semicolon
)brace
r_while
c_loop
(paren
id|n
op_decrement
)paren
id|FB_WRITEL
c_func
(paren
id|FB_READL
c_func
(paren
id|src
op_increment
)paren
comma
id|dst
op_increment
)paren
suffix:semicolon
singleline_comment|// Trailing bits
r_if
c_cond
(paren
id|last
)paren
id|FB_WRITEL
c_func
(paren
(paren
id|FB_READL
c_func
(paren
id|src
)paren
op_amp
id|last
)paren
op_or
(paren
id|FB_READL
c_func
(paren
id|dst
)paren
op_amp
op_complement
id|last
)paren
comma
id|dst
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
singleline_comment|// Different alignment for source and dest
id|right
op_assign
id|shift
op_amp
(paren
id|BITS_PER_LONG
op_minus
l_int|1
)paren
suffix:semicolon
id|left
op_assign
op_minus
id|shift
op_amp
(paren
id|BITS_PER_LONG
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dst_idx
op_plus
id|n
op_le
id|BITS_PER_LONG
)paren
(brace
singleline_comment|// Single destination word
r_if
c_cond
(paren
id|last
)paren
id|first
op_and_assign
id|last
suffix:semicolon
r_if
c_cond
(paren
id|shift
OG
l_int|0
)paren
(brace
singleline_comment|// Single source word
id|FB_WRITEL
c_func
(paren
(paren
(paren
id|FB_READL
c_func
(paren
id|src
)paren
op_rshift
id|right
)paren
op_amp
id|first
)paren
op_or
(paren
id|FB_READL
c_func
(paren
id|dst
)paren
op_amp
op_complement
id|first
)paren
comma
id|dst
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|src_idx
op_plus
id|n
op_le
id|BITS_PER_LONG
)paren
(brace
singleline_comment|// Single source word
id|FB_WRITEL
c_func
(paren
(paren
(paren
id|FB_READL
c_func
(paren
id|src
)paren
op_lshift
id|left
)paren
op_amp
id|first
)paren
op_or
(paren
id|FB_READL
c_func
(paren
id|dst
)paren
op_amp
op_complement
id|first
)paren
comma
id|dst
)paren
suffix:semicolon
)brace
r_else
(brace
singleline_comment|// 2 source words
id|d0
op_assign
id|FB_READL
c_func
(paren
id|src
op_increment
)paren
suffix:semicolon
id|d1
op_assign
id|FB_READL
c_func
(paren
id|src
)paren
suffix:semicolon
id|FB_WRITEL
c_func
(paren
(paren
(paren
id|d0
op_lshift
id|left
op_or
id|d1
op_rshift
id|right
)paren
op_amp
id|first
)paren
op_or
(paren
id|FB_READL
c_func
(paren
id|dst
)paren
op_amp
op_complement
id|first
)paren
comma
id|dst
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
singleline_comment|// Multiple destination words
id|d0
op_assign
id|FB_READL
c_func
(paren
id|src
op_increment
)paren
suffix:semicolon
singleline_comment|// Leading bits
r_if
c_cond
(paren
id|shift
OG
l_int|0
)paren
(brace
singleline_comment|// Single source word
id|FB_WRITEL
c_func
(paren
(paren
(paren
id|d0
op_rshift
id|right
)paren
op_amp
id|first
)paren
op_or
(paren
id|FB_READL
c_func
(paren
id|dst
)paren
op_amp
op_complement
id|first
)paren
comma
id|dst
)paren
suffix:semicolon
id|dst
op_increment
suffix:semicolon
id|n
op_sub_assign
id|BITS_PER_LONG
op_minus
id|dst_idx
suffix:semicolon
)brace
r_else
(brace
singleline_comment|// 2 source words
id|d1
op_assign
id|FB_READL
c_func
(paren
id|src
op_increment
)paren
suffix:semicolon
id|FB_WRITEL
c_func
(paren
(paren
(paren
id|d0
op_lshift
id|left
op_or
id|d1
op_rshift
id|right
)paren
op_amp
id|first
)paren
op_or
(paren
id|FB_READL
c_func
(paren
id|dst
)paren
op_amp
op_complement
id|first
)paren
comma
id|dst
)paren
suffix:semicolon
id|d0
op_assign
id|d1
suffix:semicolon
id|dst
op_increment
suffix:semicolon
id|n
op_sub_assign
id|BITS_PER_LONG
op_minus
id|dst_idx
suffix:semicolon
)brace
singleline_comment|// Main chunk
id|m
op_assign
id|n
op_mod
id|BITS_PER_LONG
suffix:semicolon
id|n
op_div_assign
id|BITS_PER_LONG
suffix:semicolon
r_while
c_loop
(paren
id|n
op_ge
l_int|4
)paren
(brace
id|d1
op_assign
id|FB_READL
c_func
(paren
id|src
op_increment
)paren
suffix:semicolon
id|FB_WRITEL
c_func
(paren
id|d0
op_lshift
id|left
op_or
id|d1
op_rshift
id|right
comma
id|dst
op_increment
)paren
suffix:semicolon
id|d0
op_assign
id|d1
suffix:semicolon
id|d1
op_assign
id|FB_READL
c_func
(paren
id|src
op_increment
)paren
suffix:semicolon
id|FB_WRITEL
c_func
(paren
id|d0
op_lshift
id|left
op_or
id|d1
op_rshift
id|right
comma
id|dst
op_increment
)paren
suffix:semicolon
id|d0
op_assign
id|d1
suffix:semicolon
id|d1
op_assign
id|FB_READL
c_func
(paren
id|src
op_increment
)paren
suffix:semicolon
id|FB_WRITEL
c_func
(paren
id|d0
op_lshift
id|left
op_or
id|d1
op_rshift
id|right
comma
id|dst
op_increment
)paren
suffix:semicolon
id|d0
op_assign
id|d1
suffix:semicolon
id|d1
op_assign
id|FB_READL
c_func
(paren
id|src
op_increment
)paren
suffix:semicolon
id|FB_WRITEL
c_func
(paren
id|d0
op_lshift
id|left
op_or
id|d1
op_rshift
id|right
comma
id|dst
op_increment
)paren
suffix:semicolon
id|d0
op_assign
id|d1
suffix:semicolon
id|n
op_sub_assign
l_int|4
suffix:semicolon
)brace
r_while
c_loop
(paren
id|n
op_decrement
)paren
(brace
id|d1
op_assign
id|FB_READL
c_func
(paren
id|src
op_increment
)paren
suffix:semicolon
id|FB_WRITEL
c_func
(paren
id|d0
op_lshift
id|left
op_or
id|d1
op_rshift
id|right
comma
id|dst
op_increment
)paren
suffix:semicolon
id|d0
op_assign
id|d1
suffix:semicolon
)brace
singleline_comment|// Trailing bits
r_if
c_cond
(paren
id|last
)paren
(brace
r_if
c_cond
(paren
id|m
op_le
id|right
)paren
(brace
singleline_comment|// Single source word
id|FB_WRITEL
c_func
(paren
(paren
(paren
id|d0
op_lshift
id|left
)paren
op_amp
id|last
)paren
op_or
(paren
id|FB_READL
c_func
(paren
id|dst
)paren
op_amp
op_complement
id|last
)paren
comma
id|dst
)paren
suffix:semicolon
)brace
r_else
(brace
singleline_comment|// 2 source words
id|d1
op_assign
id|FB_READL
c_func
(paren
id|src
)paren
suffix:semicolon
id|FB_WRITEL
c_func
(paren
(paren
(paren
id|d0
op_lshift
id|left
op_or
id|d1
op_rshift
id|right
)paren
op_amp
id|last
)paren
op_or
(paren
id|FB_READL
c_func
(paren
id|dst
)paren
op_amp
op_complement
id|last
)paren
comma
id|dst
)paren
suffix:semicolon
)brace
)brace
)brace
)brace
)brace
DECL|function|bitcpy_rev
r_static
r_void
id|bitcpy_rev
c_func
(paren
r_int
r_int
op_star
id|dst
comma
r_int
id|dst_idx
comma
r_const
r_int
r_int
op_star
id|src
comma
r_int
id|src_idx
comma
r_int
r_int
id|n
)paren
(brace
r_int
r_int
id|first
comma
id|last
suffix:semicolon
r_int
id|shift
op_assign
id|dst_idx
op_minus
id|src_idx
comma
id|left
comma
id|right
suffix:semicolon
r_int
r_int
id|d0
comma
id|d1
suffix:semicolon
r_int
id|m
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|n
)paren
r_return
suffix:semicolon
id|dst
op_add_assign
(paren
id|n
op_minus
l_int|1
)paren
op_div
id|BITS_PER_LONG
suffix:semicolon
id|src
op_add_assign
(paren
id|n
op_minus
l_int|1
)paren
op_div
id|BITS_PER_LONG
suffix:semicolon
r_if
c_cond
(paren
(paren
id|n
op_minus
l_int|1
)paren
op_mod
id|BITS_PER_LONG
)paren
(brace
id|dst_idx
op_add_assign
(paren
id|n
op_minus
l_int|1
)paren
op_mod
id|BITS_PER_LONG
suffix:semicolon
id|dst
op_add_assign
id|dst_idx
op_rshift
id|SHIFT_PER_LONG
suffix:semicolon
id|dst_idx
op_and_assign
id|BITS_PER_LONG
op_minus
l_int|1
suffix:semicolon
id|src_idx
op_add_assign
(paren
id|n
op_minus
l_int|1
)paren
op_mod
id|BITS_PER_LONG
suffix:semicolon
id|src
op_add_assign
id|src_idx
op_rshift
id|SHIFT_PER_LONG
suffix:semicolon
id|src_idx
op_and_assign
id|BITS_PER_LONG
op_minus
l_int|1
suffix:semicolon
)brace
id|shift
op_assign
id|dst_idx
op_minus
id|src_idx
suffix:semicolon
id|first
op_assign
op_complement
l_int|0UL
op_lshift
(paren
id|BITS_PER_LONG
op_minus
l_int|1
op_minus
id|dst_idx
)paren
suffix:semicolon
id|last
op_assign
op_complement
(paren
op_complement
l_int|0UL
op_lshift
(paren
id|BITS_PER_LONG
op_minus
l_int|1
op_minus
(paren
(paren
id|dst_idx
op_minus
id|n
)paren
op_mod
id|BITS_PER_LONG
)paren
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|shift
)paren
(brace
singleline_comment|// Same alignment for source and dest
r_if
c_cond
(paren
(paren
r_int
r_int
)paren
id|dst_idx
op_plus
l_int|1
op_ge
id|n
)paren
(brace
singleline_comment|// Single word
r_if
c_cond
(paren
id|last
)paren
id|first
op_and_assign
id|last
suffix:semicolon
id|FB_WRITEL
c_func
(paren
(paren
id|FB_READL
c_func
(paren
id|src
)paren
op_amp
id|first
)paren
op_or
(paren
id|FB_READL
c_func
(paren
id|dst
)paren
op_amp
op_complement
id|first
)paren
comma
id|dst
)paren
suffix:semicolon
)brace
r_else
(brace
singleline_comment|// Multiple destination words
singleline_comment|// Leading bits
r_if
c_cond
(paren
id|first
)paren
(brace
id|FB_WRITEL
c_func
(paren
(paren
id|FB_READL
c_func
(paren
id|src
)paren
op_amp
id|first
)paren
op_or
(paren
id|FB_READL
c_func
(paren
id|dst
)paren
op_amp
op_complement
id|first
)paren
comma
id|dst
)paren
suffix:semicolon
id|dst
op_decrement
suffix:semicolon
id|src
op_decrement
suffix:semicolon
id|n
op_sub_assign
id|dst_idx
op_plus
l_int|1
suffix:semicolon
)brace
singleline_comment|// Main chunk
id|n
op_div_assign
id|BITS_PER_LONG
suffix:semicolon
r_while
c_loop
(paren
id|n
op_ge
l_int|8
)paren
(brace
id|FB_WRITEL
c_func
(paren
id|FB_READL
c_func
(paren
id|src
op_decrement
)paren
comma
id|dst
op_decrement
)paren
suffix:semicolon
id|FB_WRITEL
c_func
(paren
id|FB_READL
c_func
(paren
id|src
op_decrement
)paren
comma
id|dst
op_decrement
)paren
suffix:semicolon
id|FB_WRITEL
c_func
(paren
id|FB_READL
c_func
(paren
id|src
op_decrement
)paren
comma
id|dst
op_decrement
)paren
suffix:semicolon
id|FB_WRITEL
c_func
(paren
id|FB_READL
c_func
(paren
id|src
op_decrement
)paren
comma
id|dst
op_decrement
)paren
suffix:semicolon
id|FB_WRITEL
c_func
(paren
id|FB_READL
c_func
(paren
id|src
op_decrement
)paren
comma
id|dst
op_decrement
)paren
suffix:semicolon
id|FB_WRITEL
c_func
(paren
id|FB_READL
c_func
(paren
id|src
op_decrement
)paren
comma
id|dst
op_decrement
)paren
suffix:semicolon
id|FB_WRITEL
c_func
(paren
id|FB_READL
c_func
(paren
id|src
op_decrement
)paren
comma
id|dst
op_decrement
)paren
suffix:semicolon
id|FB_WRITEL
c_func
(paren
id|FB_READL
c_func
(paren
id|src
op_decrement
)paren
comma
id|dst
op_decrement
)paren
suffix:semicolon
id|n
op_sub_assign
l_int|8
suffix:semicolon
)brace
r_while
c_loop
(paren
id|n
op_decrement
)paren
id|FB_WRITEL
c_func
(paren
id|FB_READL
c_func
(paren
id|src
op_decrement
)paren
comma
id|dst
op_decrement
)paren
suffix:semicolon
singleline_comment|// Trailing bits
r_if
c_cond
(paren
id|last
)paren
id|FB_WRITEL
c_func
(paren
(paren
id|FB_READL
c_func
(paren
id|src
)paren
op_amp
id|last
)paren
op_or
(paren
id|FB_READL
c_func
(paren
id|dst
)paren
op_amp
op_complement
id|last
)paren
comma
id|dst
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
singleline_comment|// Different alignment for source and dest
id|right
op_assign
id|shift
op_amp
(paren
id|BITS_PER_LONG
op_minus
l_int|1
)paren
suffix:semicolon
id|left
op_assign
op_minus
id|shift
op_amp
(paren
id|BITS_PER_LONG
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
r_int
r_int
)paren
id|dst_idx
op_plus
l_int|1
op_ge
id|n
)paren
(brace
singleline_comment|// Single destination word
r_if
c_cond
(paren
id|last
)paren
id|first
op_and_assign
id|last
suffix:semicolon
r_if
c_cond
(paren
id|shift
OL
l_int|0
)paren
(brace
singleline_comment|// Single source word
id|FB_WRITEL
c_func
(paren
(paren
id|FB_READL
c_func
(paren
id|src
)paren
op_lshift
id|left
op_amp
id|first
)paren
op_or
(paren
id|FB_READL
c_func
(paren
id|dst
)paren
op_amp
op_complement
id|first
)paren
comma
id|dst
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
l_int|1
op_plus
(paren
r_int
r_int
)paren
id|src_idx
op_ge
id|n
)paren
(brace
singleline_comment|// Single source word
id|FB_WRITEL
c_func
(paren
(paren
(paren
id|FB_READL
c_func
(paren
id|src
)paren
op_rshift
id|right
)paren
op_amp
id|first
)paren
op_or
(paren
id|FB_READL
c_func
(paren
id|dst
)paren
op_amp
op_complement
id|first
)paren
comma
id|dst
)paren
suffix:semicolon
)brace
r_else
(brace
singleline_comment|// 2 source words
id|d0
op_assign
id|FB_READL
c_func
(paren
id|src
op_decrement
)paren
suffix:semicolon
id|d1
op_assign
id|FB_READL
c_func
(paren
id|src
)paren
suffix:semicolon
id|FB_WRITEL
c_func
(paren
(paren
(paren
id|d0
op_rshift
id|right
op_or
id|d1
op_lshift
id|left
)paren
op_amp
id|first
)paren
op_or
(paren
id|FB_READL
c_func
(paren
id|dst
)paren
op_amp
op_complement
id|first
)paren
comma
id|dst
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
singleline_comment|// Multiple destination words
id|d0
op_assign
id|FB_READL
c_func
(paren
id|src
op_decrement
)paren
suffix:semicolon
singleline_comment|// Leading bits
r_if
c_cond
(paren
id|shift
OL
l_int|0
)paren
(brace
singleline_comment|// Single source word
id|FB_WRITEL
c_func
(paren
(paren
(paren
id|d0
op_lshift
id|left
)paren
op_amp
id|first
)paren
op_or
(paren
id|FB_READL
c_func
(paren
id|dst
)paren
op_amp
op_complement
id|first
)paren
comma
id|dst
)paren
suffix:semicolon
id|dst
op_decrement
suffix:semicolon
id|n
op_sub_assign
id|dst_idx
op_plus
l_int|1
suffix:semicolon
)brace
r_else
(brace
singleline_comment|// 2 source words
id|d1
op_assign
id|FB_READL
c_func
(paren
id|src
op_decrement
)paren
suffix:semicolon
id|FB_WRITEL
c_func
(paren
(paren
(paren
id|d0
op_rshift
id|right
op_or
id|d1
op_lshift
id|left
)paren
op_amp
id|first
)paren
op_or
(paren
id|FB_READL
c_func
(paren
id|dst
)paren
op_amp
op_complement
id|first
)paren
comma
id|dst
)paren
suffix:semicolon
id|d0
op_assign
id|d1
suffix:semicolon
id|dst
op_decrement
suffix:semicolon
id|n
op_sub_assign
id|dst_idx
op_plus
l_int|1
suffix:semicolon
)brace
singleline_comment|// Main chunk
id|m
op_assign
id|n
op_mod
id|BITS_PER_LONG
suffix:semicolon
id|n
op_div_assign
id|BITS_PER_LONG
suffix:semicolon
r_while
c_loop
(paren
id|n
op_ge
l_int|4
)paren
(brace
id|d1
op_assign
id|FB_READL
c_func
(paren
id|src
op_decrement
)paren
suffix:semicolon
id|FB_WRITEL
c_func
(paren
id|d0
op_rshift
id|right
op_or
id|d1
op_lshift
id|left
comma
id|dst
op_decrement
)paren
suffix:semicolon
id|d0
op_assign
id|d1
suffix:semicolon
id|d1
op_assign
id|FB_READL
c_func
(paren
id|src
op_decrement
)paren
suffix:semicolon
id|FB_WRITEL
c_func
(paren
id|d0
op_rshift
id|right
op_or
id|d1
op_lshift
id|left
comma
id|dst
op_decrement
)paren
suffix:semicolon
id|d0
op_assign
id|d1
suffix:semicolon
id|d1
op_assign
id|FB_READL
c_func
(paren
id|src
op_decrement
)paren
suffix:semicolon
id|FB_WRITEL
c_func
(paren
id|d0
op_rshift
id|right
op_or
id|d1
op_lshift
id|left
comma
id|dst
op_decrement
)paren
suffix:semicolon
id|d0
op_assign
id|d1
suffix:semicolon
id|d1
op_assign
id|FB_READL
c_func
(paren
id|src
op_decrement
)paren
suffix:semicolon
id|FB_WRITEL
c_func
(paren
id|d0
op_rshift
id|right
op_or
id|d1
op_lshift
id|left
comma
id|dst
op_decrement
)paren
suffix:semicolon
id|d0
op_assign
id|d1
suffix:semicolon
id|n
op_sub_assign
l_int|4
suffix:semicolon
)brace
r_while
c_loop
(paren
id|n
op_decrement
)paren
(brace
id|d1
op_assign
id|FB_READL
c_func
(paren
id|src
op_decrement
)paren
suffix:semicolon
id|FB_WRITEL
c_func
(paren
id|d0
op_rshift
id|right
op_or
id|d1
op_lshift
id|left
comma
id|dst
op_decrement
)paren
suffix:semicolon
id|d0
op_assign
id|d1
suffix:semicolon
)brace
singleline_comment|// Trailing bits
r_if
c_cond
(paren
id|last
)paren
(brace
r_if
c_cond
(paren
id|m
op_le
id|left
)paren
(brace
singleline_comment|// Single source word
id|FB_WRITEL
c_func
(paren
(paren
(paren
id|d0
op_rshift
id|right
)paren
op_amp
id|last
)paren
op_or
(paren
id|FB_READL
c_func
(paren
id|dst
)paren
op_amp
op_complement
id|last
)paren
comma
id|dst
)paren
suffix:semicolon
)brace
r_else
(brace
singleline_comment|// 2 source words
id|d1
op_assign
id|FB_READL
c_func
(paren
id|src
)paren
suffix:semicolon
id|FB_WRITEL
c_func
(paren
(paren
(paren
id|d0
op_rshift
id|right
op_or
id|d1
op_lshift
id|left
)paren
op_amp
id|last
)paren
op_or
(paren
id|FB_READL
c_func
(paren
id|dst
)paren
op_amp
op_complement
id|last
)paren
comma
id|dst
)paren
suffix:semicolon
)brace
)brace
)brace
)brace
)brace
DECL|function|cfb_copyarea
r_void
id|cfb_copyarea
c_func
(paren
r_struct
id|fb_info
op_star
id|p
comma
r_const
r_struct
id|fb_copyarea
op_star
id|area
)paren
(brace
id|u32
id|dx
op_assign
id|area-&gt;dx
comma
id|dy
op_assign
id|area-&gt;dy
comma
id|sx
op_assign
id|area-&gt;sx
comma
id|sy
op_assign
id|area-&gt;sy
suffix:semicolon
id|u32
id|height
op_assign
id|area-&gt;height
comma
id|width
op_assign
id|area-&gt;width
suffix:semicolon
r_int
id|x2
comma
id|y2
comma
id|old_dx
comma
id|old_dy
comma
id|vxres
comma
id|vyres
suffix:semicolon
r_int
r_int
id|next_line
op_assign
id|p-&gt;fix.line_length
suffix:semicolon
r_int
id|dst_idx
op_assign
l_int|0
comma
id|src_idx
op_assign
l_int|0
comma
id|rev_copy
op_assign
l_int|0
suffix:semicolon
r_int
r_int
op_star
id|dst
op_assign
l_int|NULL
comma
op_star
id|src
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;state
op_ne
id|FBINFO_STATE_RUNNING
)paren
r_return
suffix:semicolon
multiline_comment|/* We want rotation but lack hardware to do it for us. */
r_if
c_cond
(paren
op_logical_neg
id|p-&gt;fbops-&gt;fb_rotate
op_logical_and
id|p-&gt;var.rotate
)paren
(brace
)brace
id|vxres
op_assign
id|p-&gt;var.xres_virtual
suffix:semicolon
id|vyres
op_assign
id|p-&gt;var.yres_virtual
suffix:semicolon
r_if
c_cond
(paren
id|area-&gt;dx
OG
id|vxres
op_logical_or
id|area-&gt;sx
OG
id|vxres
op_logical_or
id|area-&gt;dy
OG
id|vyres
op_logical_or
id|area-&gt;sy
OG
id|vyres
)paren
r_return
suffix:semicolon
multiline_comment|/* clip the destination */
id|old_dx
op_assign
id|area-&gt;dx
suffix:semicolon
id|old_dy
op_assign
id|area-&gt;dy
suffix:semicolon
multiline_comment|/*&n;&t; * We could use hardware clipping but on many cards you get around&n;&t; * hardware clipping by writing to framebuffer directly.&n;&t; */
id|x2
op_assign
id|area-&gt;dx
op_plus
id|area-&gt;width
suffix:semicolon
id|y2
op_assign
id|area-&gt;dy
op_plus
id|area-&gt;height
suffix:semicolon
id|dx
op_assign
id|area-&gt;dx
OG
l_int|0
ques
c_cond
id|area-&gt;dx
suffix:colon
l_int|0
suffix:semicolon
id|dy
op_assign
id|area-&gt;dy
OG
l_int|0
ques
c_cond
id|area-&gt;dy
suffix:colon
l_int|0
suffix:semicolon
id|x2
op_assign
id|x2
OL
id|vxres
ques
c_cond
id|x2
suffix:colon
id|vxres
suffix:semicolon
id|y2
op_assign
id|y2
OL
id|vyres
ques
c_cond
id|y2
suffix:colon
id|vyres
suffix:semicolon
id|width
op_assign
id|x2
op_minus
id|dx
suffix:semicolon
id|height
op_assign
id|y2
op_minus
id|dy
suffix:semicolon
multiline_comment|/* update sx1,sy1 */
id|sx
op_add_assign
(paren
id|dx
op_minus
id|old_dx
)paren
suffix:semicolon
id|sy
op_add_assign
(paren
id|dy
op_minus
id|old_dy
)paren
suffix:semicolon
multiline_comment|/* the source must be completely inside the virtual screen */
r_if
c_cond
(paren
id|sx
template_param
id|vyres
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
(paren
id|dy
op_eq
id|sy
op_logical_and
id|dx
OG
id|sx
)paren
op_logical_or
(paren
id|dy
OG
id|sy
)paren
)paren
(brace
id|dy
op_add_assign
id|height
suffix:semicolon
id|sy
op_add_assign
id|height
suffix:semicolon
id|rev_copy
op_assign
l_int|1
suffix:semicolon
)brace
id|dst
op_assign
id|src
op_assign
(paren
r_int
r_int
op_star
)paren
(paren
(paren
r_int
r_int
)paren
id|p-&gt;screen_base
op_amp
op_complement
(paren
id|BYTES_PER_LONG
op_minus
l_int|1
)paren
)paren
suffix:semicolon
id|dst_idx
op_assign
id|src_idx
op_assign
(paren
r_int
r_int
)paren
id|p-&gt;screen_base
op_amp
(paren
id|BYTES_PER_LONG
op_minus
l_int|1
)paren
suffix:semicolon
id|dst_idx
op_add_assign
id|dy
op_star
id|next_line
op_star
l_int|8
op_plus
id|dx
op_star
id|p-&gt;var.bits_per_pixel
suffix:semicolon
id|src_idx
op_add_assign
id|sy
op_star
id|next_line
op_star
l_int|8
op_plus
id|sx
op_star
id|p-&gt;var.bits_per_pixel
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;fbops-&gt;fb_sync
)paren
id|p-&gt;fbops
op_member_access_from_pointer
id|fb_sync
c_func
(paren
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rev_copy
)paren
(brace
r_while
c_loop
(paren
id|height
op_decrement
)paren
(brace
id|dst_idx
op_sub_assign
id|next_line
op_star
l_int|8
suffix:semicolon
id|src_idx
op_sub_assign
id|next_line
op_star
l_int|8
suffix:semicolon
id|dst
op_add_assign
id|dst_idx
op_rshift
id|SHIFT_PER_LONG
suffix:semicolon
id|dst_idx
op_and_assign
(paren
id|BYTES_PER_LONG
op_minus
l_int|1
)paren
suffix:semicolon
id|src
op_add_assign
id|src_idx
op_rshift
id|SHIFT_PER_LONG
suffix:semicolon
id|src_idx
op_and_assign
(paren
id|BYTES_PER_LONG
op_minus
l_int|1
)paren
suffix:semicolon
id|bitcpy_rev
c_func
(paren
id|dst
comma
id|dst_idx
comma
id|src
comma
id|src_idx
comma
id|width
op_star
id|p-&gt;var.bits_per_pixel
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
r_while
c_loop
(paren
id|height
op_decrement
)paren
(brace
id|dst
op_add_assign
id|dst_idx
op_rshift
id|SHIFT_PER_LONG
suffix:semicolon
id|dst_idx
op_and_assign
(paren
id|BYTES_PER_LONG
op_minus
l_int|1
)paren
suffix:semicolon
id|src
op_add_assign
id|src_idx
op_rshift
id|SHIFT_PER_LONG
suffix:semicolon
id|src_idx
op_and_assign
(paren
id|BYTES_PER_LONG
op_minus
l_int|1
)paren
suffix:semicolon
id|bitcpy
c_func
(paren
id|dst
comma
id|dst_idx
comma
id|src
comma
id|src_idx
comma
id|width
op_star
id|p-&gt;var.bits_per_pixel
)paren
suffix:semicolon
id|dst_idx
op_add_assign
id|next_line
op_star
l_int|8
suffix:semicolon
id|src_idx
op_add_assign
id|next_line
op_star
l_int|8
suffix:semicolon
)brace
)brace
)brace
DECL|variable|cfb_copyarea
id|EXPORT_SYMBOL
c_func
(paren
id|cfb_copyarea
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;James Simmons &lt;jsimmons@users.sf.net&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Generic software accelerated copyarea&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
