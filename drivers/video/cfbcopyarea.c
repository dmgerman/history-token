multiline_comment|/*&n; *  Generic function for frame buffer with packed pixels of any depth.&n; *&n; *      Copyright (C)  June 1999 James Simmons&n; *&n; *  This file is subject to the terms and conditions of the GNU General Public&n; *  License.  See the file COPYING in the main directory of this archive for&n; *  more details.&n; *&n; * NOTES:&n; *&n; *  This is for cfb packed pixels. Iplan and such are incorporated in the&n; *  drivers that need them.&n; *&n; *  FIXME&n; *&n; *  Also need to add code to deal with cards endians that are different than&n; *  the native cpu endians. I also need to deal with MSB position in the word.&n; *&n; *  The two functions or copying forward and backward could be split up like&n; *  the ones for filling, i.e. in aligned and unaligned versions. This would&n; *  help moving some redundant computations and branches out of the loop, too.&n; */
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
macro_line|#  define FB_WRITEL fb_writel
DECL|macro|FB_READL
macro_line|#  define FB_READL  fb_readl
DECL|macro|SHIFT_PER_LONG
macro_line|#  define SHIFT_PER_LONG 5
DECL|macro|BYTES_PER_LONG
macro_line|#  define BYTES_PER_LONG 4
macro_line|#else
DECL|macro|FB_WRITEL
macro_line|#  define FB_WRITEL fb_writeq
DECL|macro|FB_READL
macro_line|#  define FB_READL  fb_readq
DECL|macro|SHIFT_PER_LONG
macro_line|#  define SHIFT_PER_LONG 6
DECL|macro|BYTES_PER_LONG
macro_line|#  define BYTES_PER_LONG 8
macro_line|#endif
multiline_comment|/*&n;     *  Compose two values, using a bitmask as decision value&n;     *  This is equivalent to (a &amp; mask) | (b &amp; ~mask)&n;     */
r_static
r_inline
r_int
r_int
DECL|function|comp
id|comp
c_func
(paren
r_int
r_int
id|a
comma
r_int
r_int
id|b
comma
r_int
r_int
id|mask
)paren
(brace
r_return
(paren
(paren
id|a
op_xor
id|b
)paren
op_amp
id|mask
)paren
op_xor
id|b
suffix:semicolon
)brace
multiline_comment|/*&n;     *  Generic bitwise copy algorithm&n;     */
r_static
r_void
DECL|function|bitcpy
id|bitcpy
c_func
(paren
r_int
r_int
id|__iomem
op_star
id|dst
comma
r_int
id|dst_idx
comma
r_const
r_int
r_int
id|__iomem
op_star
id|src
comma
r_int
id|src_idx
comma
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
r_const
id|shift
op_assign
id|dst_idx
op_minus
id|src_idx
suffix:semicolon
r_int
id|left
comma
id|right
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
id|comp
c_func
(paren
id|FB_READL
c_func
(paren
id|src
)paren
comma
id|FB_READL
c_func
(paren
id|dst
)paren
comma
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
op_ne
op_complement
l_int|0UL
)paren
(brace
id|FB_WRITEL
c_func
(paren
id|comp
c_func
(paren
id|FB_READL
c_func
(paren
id|src
)paren
comma
id|FB_READL
c_func
(paren
id|dst
)paren
comma
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
id|comp
c_func
(paren
id|FB_READL
c_func
(paren
id|src
)paren
comma
id|FB_READL
c_func
(paren
id|dst
)paren
comma
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
r_int
r_int
id|d0
comma
id|d1
suffix:semicolon
r_int
id|m
suffix:semicolon
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
id|comp
c_func
(paren
id|FB_READL
c_func
(paren
id|src
)paren
op_rshift
id|right
comma
id|FB_READL
c_func
(paren
id|dst
)paren
comma
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
id|comp
c_func
(paren
id|FB_READL
c_func
(paren
id|src
)paren
op_lshift
id|left
comma
id|FB_READL
c_func
(paren
id|dst
)paren
comma
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
id|comp
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
id|FB_READL
c_func
(paren
id|dst
)paren
comma
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
multiline_comment|/** We must always remember the last value read, because in case&n;&t;&t;&t;SRC and DST overlap bitwise (e.g. when moving just one pixel in&n;&t;&t;&t;1bpp), we always collect one full long for DST and that might&n;&t;&t;&t;overlap with the current long from SRC. We store this value in&n;&t;&t;&t;&squot;d0&squot;. */
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
id|comp
c_func
(paren
id|d0
op_rshift
id|right
comma
id|FB_READL
c_func
(paren
id|dst
)paren
comma
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
id|comp
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
id|FB_READL
c_func
(paren
id|dst
)paren
comma
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
id|comp
c_func
(paren
id|d0
op_lshift
id|left
comma
id|FB_READL
c_func
(paren
id|dst
)paren
comma
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
id|comp
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
id|FB_READL
c_func
(paren
id|dst
)paren
comma
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
multiline_comment|/*&n;     *  Generic bitwise copy algorithm, operating backward&n;     */
r_static
r_void
DECL|function|bitcpy_rev
id|bitcpy_rev
c_func
(paren
r_int
r_int
id|__iomem
op_star
id|dst
comma
r_int
id|dst_idx
comma
r_const
r_int
r_int
id|__iomem
op_star
id|src
comma
r_int
id|src_idx
comma
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
id|comp
c_func
(paren
id|FB_READL
c_func
(paren
id|src
)paren
comma
id|FB_READL
c_func
(paren
id|dst
)paren
comma
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
op_ne
op_complement
l_int|0UL
)paren
(brace
id|FB_WRITEL
c_func
(paren
id|comp
c_func
(paren
id|FB_READL
c_func
(paren
id|src
)paren
comma
id|FB_READL
c_func
(paren
id|dst
)paren
comma
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
id|comp
c_func
(paren
id|FB_READL
c_func
(paren
id|src
)paren
comma
id|FB_READL
c_func
(paren
id|dst
)paren
comma
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
r_int
r_const
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
r_int
r_const
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
id|comp
c_func
(paren
id|FB_READL
c_func
(paren
id|src
)paren
op_lshift
id|left
comma
id|FB_READL
c_func
(paren
id|dst
)paren
comma
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
id|comp
c_func
(paren
id|FB_READL
c_func
(paren
id|src
)paren
op_rshift
id|right
comma
id|FB_READL
c_func
(paren
id|dst
)paren
comma
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
id|FB_WRITEL
c_func
(paren
id|comp
c_func
(paren
(paren
id|FB_READL
c_func
(paren
id|src
)paren
op_rshift
id|right
op_or
id|FB_READL
c_func
(paren
id|src
op_minus
l_int|1
)paren
op_lshift
id|left
)paren
comma
id|FB_READL
c_func
(paren
id|dst
)paren
comma
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
multiline_comment|/** We must always remember the last value read, because in case&n;&t;&t;&t;SRC and DST overlap bitwise (e.g. when moving just one pixel in&n;&t;&t;&t;1bpp), we always collect one full long for DST and that might&n;&t;&t;&t;overlap with the current long from SRC. We store this value in&n;&t;&t;&t;&squot;d0&squot;. */
r_int
r_int
id|d0
comma
id|d1
suffix:semicolon
r_int
id|m
suffix:semicolon
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
id|comp
c_func
(paren
(paren
id|d0
op_lshift
id|left
)paren
comma
id|FB_READL
c_func
(paren
id|dst
)paren
comma
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
id|comp
c_func
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
comma
id|FB_READL
c_func
(paren
id|dst
)paren
comma
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
)brace
id|dst
op_decrement
suffix:semicolon
id|n
op_sub_assign
id|dst_idx
op_plus
l_int|1
suffix:semicolon
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
id|comp
c_func
(paren
id|d0
op_rshift
id|right
comma
id|FB_READL
c_func
(paren
id|dst
)paren
comma
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
id|comp
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
id|FB_READL
c_func
(paren
id|dst
)paren
comma
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
id|vxres
comma
id|vyres
suffix:semicolon
r_int
r_int
r_const
id|bits_per_line
op_assign
id|p-&gt;fix.line_length
op_star
l_int|8u
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
id|__iomem
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
multiline_comment|/* clip the destination&n;&t; * We could use hardware clipping but on many cards you get around&n;&t; * hardware clipping by writing to framebuffer directly.&n;&t; */
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
r_if
c_cond
(paren
(paren
id|width
op_eq
l_int|0
)paren
op_logical_or
(paren
id|height
op_eq
l_int|0
)paren
)paren
r_return
suffix:semicolon
multiline_comment|/* update sx1,sy1 */
id|sx
op_add_assign
(paren
id|dx
op_minus
id|area-&gt;dx
)paren
suffix:semicolon
id|sy
op_add_assign
(paren
id|dy
op_minus
id|area-&gt;dy
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
multiline_comment|/* if the beginning of the target area might overlap with the end of&n;&t;the source area, be have to copy the area reverse. */
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
singleline_comment|// split the base of the framebuffer into a long-aligned address and the
singleline_comment|// index of the first bit
id|dst
op_assign
id|src
op_assign
(paren
r_int
r_int
id|__iomem
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
l_int|8
op_star
(paren
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
)paren
suffix:semicolon
singleline_comment|// add offset of source and target area
id|dst_idx
op_add_assign
id|dy
op_star
id|bits_per_line
op_plus
id|dx
op_star
id|p-&gt;var.bits_per_pixel
suffix:semicolon
id|src_idx
op_add_assign
id|sy
op_star
id|bits_per_line
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
id|bits_per_line
suffix:semicolon
id|src_idx
op_sub_assign
id|bits_per_line
suffix:semicolon
id|dst
op_add_assign
id|dst_idx
op_rshift
id|SHIFT_PER_LONG
suffix:semicolon
id|dst_idx
op_and_assign
id|LONG_MASK
suffix:semicolon
id|src
op_add_assign
id|src_idx
op_rshift
id|SHIFT_PER_LONG
suffix:semicolon
id|src_idx
op_and_assign
id|LONG_MASK
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
id|LONG_MASK
suffix:semicolon
id|src
op_add_assign
id|src_idx
op_rshift
id|SHIFT_PER_LONG
suffix:semicolon
id|src_idx
op_and_assign
id|LONG_MASK
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
id|bits_per_line
suffix:semicolon
id|src_idx
op_add_assign
id|bits_per_line
suffix:semicolon
)brace
)brace
)brace
DECL|macro|CFB_DEBUG
macro_line|#undef CFB_DEBUG
macro_line|#ifdef CFB_DEBUG
multiline_comment|/** all this init-function does is to perform a few unittests.&n;The idea it always to invoke the function to test on a predefined bitmap and&n;compare the results to the expected output.&n;TODO:&n; - this currently only tests bitcpy_rev, as that was the only one giving me trouble&n; - this assumes 32 bit longs&n; - not sure about endianess, I only tested this on a 32 bit MIPS little endian system&n; - could reuse testcases to test forward copying, too, just reverse the operation&n;*/
DECL|function|cfb_copyarea_init
r_int
id|__init
id|cfb_copyarea_init
c_func
(paren
r_void
)paren
(brace
r_char
r_const
op_star
id|comment
op_assign
l_int|0
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;cfb_copyarea_init()&bslash;n&quot;
)paren
suffix:semicolon
(brace
id|comment
op_assign
l_string|&quot;copy a single u32, source and target u32-aligned&quot;
suffix:semicolon
id|u32
id|tmp
(braket
)braket
op_assign
(brace
l_int|0xaaaaaaaau
comma
l_int|0x55555555u
comma
l_int|0xffffffffu
comma
l_int|0x00000000u
)brace
suffix:semicolon
id|u32
r_const
id|expect
(braket
)braket
op_assign
(brace
l_int|0xaaaaaaaau
comma
l_int|0xaaaaaaaau
comma
l_int|0xffffffffu
comma
l_int|0x00000000u
)brace
suffix:semicolon
id|bitcpy_rev
c_func
(paren
id|tmp
comma
l_int|0
comma
id|tmp
op_plus
l_int|1
comma
l_int|0
comma
l_int|32
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_ne
id|memcmp
c_func
(paren
id|expect
comma
id|tmp
comma
r_sizeof
id|tmp
)paren
)paren
(brace
r_goto
id|error
suffix:semicolon
)brace
)brace
(brace
id|comment
op_assign
l_string|&quot;copy a single u32, source u32-aligned&quot;
suffix:semicolon
id|u32
id|tmp
(braket
)braket
op_assign
(brace
l_int|0x11112222u
comma
l_int|0x33334444u
comma
l_int|0x55556666u
comma
l_int|0x77778888u
)brace
suffix:semicolon
id|u32
r_const
id|expect
(braket
)braket
op_assign
(brace
l_int|0x11112222u
comma
l_int|0x22224444u
comma
l_int|0x55551111u
comma
l_int|0x77778888u
)brace
suffix:semicolon
id|bitcpy_rev
c_func
(paren
id|tmp
comma
l_int|0
comma
id|tmp
op_plus
l_int|1
comma
l_int|16
comma
l_int|32
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_ne
id|memcmp
c_func
(paren
id|expect
comma
id|tmp
comma
r_sizeof
id|tmp
)paren
)paren
(brace
r_goto
id|error
suffix:semicolon
)brace
)brace
(brace
id|comment
op_assign
l_string|&quot;copy a single u32, target u32-aligned&quot;
suffix:semicolon
id|u32
id|tmp
(braket
)braket
op_assign
(brace
l_int|0x11112222u
comma
l_int|0x33334444u
comma
l_int|0x55556666u
comma
l_int|0x77778888u
)brace
suffix:semicolon
id|u32
r_const
id|expect
(braket
)braket
op_assign
(brace
l_int|0x11112222u
comma
l_int|0x33334444u
comma
l_int|0x44441111u
comma
l_int|0x77778888u
)brace
suffix:semicolon
id|bitcpy_rev
c_func
(paren
id|tmp
comma
l_int|16
comma
id|tmp
op_plus
l_int|2
comma
l_int|0
comma
l_int|32
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_ne
id|memcmp
c_func
(paren
id|expect
comma
id|tmp
comma
r_sizeof
id|tmp
)paren
)paren
(brace
r_goto
id|error
suffix:semicolon
)brace
)brace
(brace
id|comment
op_assign
l_string|&quot;copy two u32, source and target u32-aligned&quot;
suffix:semicolon
id|u32
id|tmp
(braket
)braket
op_assign
(brace
l_int|0xaaaaaaaau
comma
l_int|0x55555555u
comma
l_int|0xffffffffu
comma
l_int|0x00000000u
)brace
suffix:semicolon
id|u32
r_const
id|expect
(braket
)braket
op_assign
(brace
l_int|0xaaaaaaaau
comma
l_int|0xaaaaaaaau
comma
l_int|0x55555555u
comma
l_int|0x00000000u
)brace
suffix:semicolon
id|bitcpy_rev
c_func
(paren
id|tmp
comma
l_int|0
comma
id|tmp
op_plus
l_int|1
comma
l_int|0
comma
l_int|64
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_ne
id|memcmp
c_func
(paren
id|expect
comma
id|tmp
comma
r_sizeof
id|tmp
)paren
)paren
(brace
r_goto
id|error
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
id|error
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot; framebuffer self-test(%s) failed&bslash;n&quot;
comma
id|comment
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|variable|cfb_copyarea_init
id|module_init
c_func
(paren
id|cfb_copyarea_init
)paren
suffix:semicolon
macro_line|#endif
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
