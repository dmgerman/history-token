multiline_comment|/*&n; *  Generic fillrect for frame buffers with packed pixels of any depth. &n; *&n; *      Copyright (C)  2000 James Simmons (jsimmons@linux-fbdev.org) &n; *&n; *  This file is subject to the terms and conditions of the GNU General Public&n; *  License.  See the file COPYING in the main directory of this archive for&n; *  more details.&n; *&n; * NOTES:&n; *&n; *  The code for depths like 24 that don&squot;t have integer number of pixels per &n; *  long is broken and needs to be fixed. For now I turned these types of &n; *  mode off.&n; *&n; *  Also need to add code to deal with cards endians that are different than&n; *  the native cpu endians. I also need to deal with MSB position in the word.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/fb.h&gt;
macro_line|#include &lt;asm/types.h&gt;
macro_line|#if BITS_PER_LONG == 32
DECL|macro|FB_WRITEL
mdefine_line|#define FB_WRITEL fb_writel
DECL|macro|FB_READL
mdefine_line|#define FB_READL  fb_readl
DECL|macro|BYTES_PER_LONG
mdefine_line|#define BYTES_PER_LONG 4
DECL|macro|SHIFT_PER_LONG
mdefine_line|#define SHIFT_PER_LONG 5
macro_line|#else
DECL|macro|FB_WRITEL
mdefine_line|#define FB_WRITEL fb_writeq
DECL|macro|FB_READL
mdefine_line|#define FB_READL  fb_readq
DECL|macro|BYTES_PER_LONG
mdefine_line|#define BYTES_PER_LONG 8
DECL|macro|SHIFT_PER_LONG
mdefine_line|#define SHIFT_PER_LONG 6
macro_line|#endif
DECL|macro|EXP1
mdefine_line|#define EXP1(x)&t;&t;0xffffffffU*x
DECL|macro|EXP2
mdefine_line|#define EXP2(x)&t;&t;0x55555555U*x
DECL|macro|EXP4
mdefine_line|#define EXP4(x)&t;&t;0x11111111U*0x ## x
DECL|typedef|pixel_t
r_typedef
id|u32
id|pixel_t
suffix:semicolon
DECL|variable|bpp1tab
r_static
r_const
id|u32
id|bpp1tab
(braket
l_int|2
)braket
op_assign
(brace
id|EXP1
c_func
(paren
l_int|0
)paren
comma
id|EXP1
c_func
(paren
l_int|1
)paren
)brace
suffix:semicolon
DECL|variable|bpp2tab
r_static
r_const
id|u32
id|bpp2tab
(braket
l_int|4
)braket
op_assign
(brace
id|EXP2
c_func
(paren
l_int|0
)paren
comma
id|EXP2
c_func
(paren
l_int|1
)paren
comma
id|EXP2
c_func
(paren
l_int|2
)paren
comma
id|EXP2
c_func
(paren
l_int|3
)paren
)brace
suffix:semicolon
DECL|variable|bpp4tab
r_static
r_const
id|u32
id|bpp4tab
(braket
l_int|16
)braket
op_assign
(brace
id|EXP4
c_func
(paren
l_int|0
)paren
comma
id|EXP4
c_func
(paren
l_int|1
)paren
comma
id|EXP4
c_func
(paren
l_int|2
)paren
comma
id|EXP4
c_func
(paren
l_int|3
)paren
comma
id|EXP4
c_func
(paren
l_int|4
)paren
comma
id|EXP4
c_func
(paren
l_int|5
)paren
comma
id|EXP4
c_func
(paren
l_int|6
)paren
comma
id|EXP4
c_func
(paren
l_int|7
)paren
comma
id|EXP4
c_func
(paren
l_int|8
)paren
comma
id|EXP4
c_func
(paren
l_int|9
)paren
comma
id|EXP4
c_func
(paren
id|a
)paren
comma
id|EXP4
c_func
(paren
id|b
)paren
comma
id|EXP4
c_func
(paren
id|c
)paren
comma
id|EXP4
c_func
(paren
id|d
)paren
comma
id|EXP4
c_func
(paren
id|e
)paren
comma
id|EXP4
c_func
(paren
id|f
)paren
)brace
suffix:semicolon
multiline_comment|/*&n;     *  Compose two values, using a bitmask as decision value&n;     *  This is equivalent to (a &amp; mask) | (b &amp; ~mask)&n;     */
DECL|function|comp
r_static
r_inline
r_int
r_int
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
DECL|function|pixel_to_pat32
r_static
r_inline
id|u32
id|pixel_to_pat32
c_func
(paren
r_const
r_struct
id|fb_info
op_star
id|p
comma
id|pixel_t
id|pixel
)paren
(brace
id|u32
id|pat
op_assign
id|pixel
suffix:semicolon
r_switch
c_cond
(paren
id|p-&gt;var.bits_per_pixel
)paren
(brace
r_case
l_int|1
suffix:colon
id|pat
op_assign
id|bpp1tab
(braket
id|pat
)braket
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|pat
op_assign
id|bpp2tab
(braket
id|pat
)braket
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|pat
op_assign
id|bpp4tab
(braket
id|pat
)braket
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|8
suffix:colon
id|pat
op_or_assign
id|pat
op_lshift
l_int|8
suffix:semicolon
singleline_comment|// Fall through
r_case
l_int|16
suffix:colon
id|pat
op_or_assign
id|pat
op_lshift
l_int|16
suffix:semicolon
singleline_comment|// Fall through
r_case
l_int|32
suffix:colon
r_break
suffix:semicolon
)brace
r_return
id|pat
suffix:semicolon
)brace
multiline_comment|/*&n;     *  Expand a pixel value to a generic 32/64-bit pattern and rotate it to&n;     *  the correct start position&n;     */
DECL|function|pixel_to_pat
r_static
r_inline
r_int
r_int
id|pixel_to_pat
c_func
(paren
r_const
r_struct
id|fb_info
op_star
id|p
comma
id|pixel_t
id|pixel
comma
r_int
id|left
)paren
(brace
r_int
r_int
id|pat
op_assign
id|pixel
suffix:semicolon
id|u32
id|bpp
op_assign
id|p-&gt;var.bits_per_pixel
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/* expand pixel value */
r_for
c_loop
(paren
id|i
op_assign
id|bpp
suffix:semicolon
id|i
OL
id|BITS_PER_LONG
suffix:semicolon
id|i
op_mul_assign
l_int|2
)paren
id|pat
op_or_assign
id|pat
op_lshift
id|i
suffix:semicolon
multiline_comment|/* rotate pattern to correct start position */
id|pat
op_assign
id|pat
op_lshift
id|left
op_or
id|pat
op_rshift
(paren
id|bpp
op_minus
id|left
)paren
suffix:semicolon
r_return
id|pat
suffix:semicolon
)brace
multiline_comment|/*&n;     *  Unaligned 32-bit pattern fill using 32/64-bit memory accesses&n;     */
DECL|function|bitfill32
r_void
id|bitfill32
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
id|u32
id|pat
comma
id|u32
id|n
)paren
(brace
r_int
r_int
id|val
op_assign
id|pat
suffix:semicolon
r_int
r_int
id|first
comma
id|last
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|n
)paren
r_return
suffix:semicolon
macro_line|#if BITS_PER_LONG == 64
id|val
op_or_assign
id|val
op_lshift
l_int|32
suffix:semicolon
macro_line|#endif
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
id|val
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
)paren
(brace
id|FB_WRITEL
c_func
(paren
id|comp
c_func
(paren
id|val
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
id|val
comma
id|dst
op_increment
)paren
suffix:semicolon
id|FB_WRITEL
c_func
(paren
id|val
comma
id|dst
op_increment
)paren
suffix:semicolon
id|FB_WRITEL
c_func
(paren
id|val
comma
id|dst
op_increment
)paren
suffix:semicolon
id|FB_WRITEL
c_func
(paren
id|val
comma
id|dst
op_increment
)paren
suffix:semicolon
id|FB_WRITEL
c_func
(paren
id|val
comma
id|dst
op_increment
)paren
suffix:semicolon
id|FB_WRITEL
c_func
(paren
id|val
comma
id|dst
op_increment
)paren
suffix:semicolon
id|FB_WRITEL
c_func
(paren
id|val
comma
id|dst
op_increment
)paren
suffix:semicolon
id|FB_WRITEL
c_func
(paren
id|val
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
id|val
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
id|val
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
multiline_comment|/*&n;     *  Unaligned generic pattern fill using 32/64-bit memory accesses&n;     *  The pattern must have been expanded to a full 32/64-bit value&n;     *  Left/right are the appropriate shifts to convert to the pattern to be&n;     *  used for the next 32/64-bit word&n;     */
DECL|function|bitfill
r_void
id|bitfill
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
r_int
r_int
id|pat
comma
r_int
id|left
comma
r_int
id|right
comma
id|u32
id|n
)paren
(brace
r_int
r_int
id|first
comma
id|last
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|n
)paren
r_return
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
id|pat
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
)paren
(brace
id|FB_WRITEL
c_func
(paren
id|comp
c_func
(paren
id|pat
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
id|pat
op_assign
id|pat
op_lshift
id|left
op_or
id|pat
op_rshift
id|right
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
l_int|4
)paren
(brace
id|FB_WRITEL
c_func
(paren
id|pat
comma
id|dst
op_increment
)paren
suffix:semicolon
id|pat
op_assign
id|pat
op_lshift
id|left
op_or
id|pat
op_rshift
id|right
suffix:semicolon
id|FB_WRITEL
c_func
(paren
id|pat
comma
id|dst
op_increment
)paren
suffix:semicolon
id|pat
op_assign
id|pat
op_lshift
id|left
op_or
id|pat
op_rshift
id|right
suffix:semicolon
id|FB_WRITEL
c_func
(paren
id|pat
comma
id|dst
op_increment
)paren
suffix:semicolon
id|pat
op_assign
id|pat
op_lshift
id|left
op_or
id|pat
op_rshift
id|right
suffix:semicolon
id|FB_WRITEL
c_func
(paren
id|pat
comma
id|dst
op_increment
)paren
suffix:semicolon
id|pat
op_assign
id|pat
op_lshift
id|left
op_or
id|pat
op_rshift
id|right
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
id|FB_WRITEL
c_func
(paren
id|pat
comma
id|dst
op_increment
)paren
suffix:semicolon
id|pat
op_assign
id|pat
op_lshift
id|left
op_or
id|pat
op_rshift
id|right
suffix:semicolon
)brace
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
id|pat
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
DECL|function|bitfill32_rev
r_void
id|bitfill32_rev
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
id|u32
id|pat
comma
id|u32
id|n
)paren
(brace
r_int
r_int
id|val
op_assign
id|pat
comma
id|dat
suffix:semicolon
r_int
r_int
id|first
comma
id|last
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|n
)paren
r_return
suffix:semicolon
macro_line|#if BITS_PER_LONG == 64
id|val
op_or_assign
id|val
op_lshift
l_int|32
suffix:semicolon
macro_line|#endif
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
id|dat
op_assign
id|FB_READL
c_func
(paren
id|dst
)paren
suffix:semicolon
id|FB_WRITEL
c_func
(paren
id|comp
c_func
(paren
id|dat
op_xor
id|val
comma
id|dat
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
)paren
(brace
id|dat
op_assign
id|FB_READL
c_func
(paren
id|dst
)paren
suffix:semicolon
id|FB_WRITEL
c_func
(paren
id|comp
c_func
(paren
id|dat
op_xor
id|val
comma
id|dat
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
id|dst
)paren
op_xor
id|val
comma
id|dst
)paren
suffix:semicolon
id|dst
op_increment
suffix:semicolon
id|FB_WRITEL
c_func
(paren
id|FB_READL
c_func
(paren
id|dst
)paren
op_xor
id|val
comma
id|dst
)paren
suffix:semicolon
id|dst
op_increment
suffix:semicolon
id|FB_WRITEL
c_func
(paren
id|FB_READL
c_func
(paren
id|dst
)paren
op_xor
id|val
comma
id|dst
)paren
suffix:semicolon
id|dst
op_increment
suffix:semicolon
id|FB_WRITEL
c_func
(paren
id|FB_READL
c_func
(paren
id|dst
)paren
op_xor
id|val
comma
id|dst
)paren
suffix:semicolon
id|dst
op_increment
suffix:semicolon
id|FB_WRITEL
c_func
(paren
id|FB_READL
c_func
(paren
id|dst
)paren
op_xor
id|val
comma
id|dst
)paren
suffix:semicolon
id|dst
op_increment
suffix:semicolon
id|FB_WRITEL
c_func
(paren
id|FB_READL
c_func
(paren
id|dst
)paren
op_xor
id|val
comma
id|dst
)paren
suffix:semicolon
id|dst
op_increment
suffix:semicolon
id|FB_WRITEL
c_func
(paren
id|FB_READL
c_func
(paren
id|dst
)paren
op_xor
id|val
comma
id|dst
)paren
suffix:semicolon
id|dst
op_increment
suffix:semicolon
id|FB_WRITEL
c_func
(paren
id|FB_READL
c_func
(paren
id|dst
)paren
op_xor
id|val
comma
id|dst
)paren
suffix:semicolon
id|dst
op_increment
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
(brace
id|FB_WRITEL
c_func
(paren
id|FB_READL
c_func
(paren
id|dst
)paren
op_xor
id|val
comma
id|dst
)paren
suffix:semicolon
id|dst
op_increment
suffix:semicolon
)brace
singleline_comment|// Trailing bits
r_if
c_cond
(paren
id|last
)paren
(brace
id|dat
op_assign
id|FB_READL
c_func
(paren
id|dst
)paren
suffix:semicolon
id|FB_WRITEL
c_func
(paren
id|comp
c_func
(paren
id|dat
op_xor
id|val
comma
id|dat
comma
id|first
)paren
comma
id|dst
)paren
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n;     *  Unaligned generic pattern fill using 32/64-bit memory accesses&n;     *  The pattern must have been expanded to a full 32/64-bit value&n;     *  Left/right are the appropriate shifts to convert to the pattern to be&n;     *  used for the next 32/64-bit word&n;     */
DECL|function|bitfill_rev
r_void
id|bitfill_rev
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
r_int
r_int
id|pat
comma
r_int
id|left
comma
r_int
id|right
comma
id|u32
id|n
)paren
(brace
r_int
r_int
id|first
comma
id|last
comma
id|dat
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|n
)paren
r_return
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
id|dat
op_assign
id|FB_READL
c_func
(paren
id|dst
)paren
suffix:semicolon
id|FB_WRITEL
c_func
(paren
id|comp
c_func
(paren
id|dat
op_xor
id|pat
comma
id|dat
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
)paren
(brace
id|dat
op_assign
id|FB_READL
c_func
(paren
id|dst
)paren
suffix:semicolon
id|FB_WRITEL
c_func
(paren
id|comp
c_func
(paren
id|dat
op_xor
id|pat
comma
id|dat
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
id|pat
op_assign
id|pat
op_lshift
id|left
op_or
id|pat
op_rshift
id|right
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
l_int|4
)paren
(brace
id|FB_WRITEL
c_func
(paren
id|FB_READL
c_func
(paren
id|dst
)paren
op_xor
id|pat
comma
id|dst
)paren
suffix:semicolon
id|dst
op_increment
suffix:semicolon
id|pat
op_assign
id|pat
op_lshift
id|left
op_or
id|pat
op_rshift
id|right
suffix:semicolon
id|FB_WRITEL
c_func
(paren
id|FB_READL
c_func
(paren
id|dst
)paren
op_xor
id|pat
comma
id|dst
)paren
suffix:semicolon
id|dst
op_increment
suffix:semicolon
id|pat
op_assign
id|pat
op_lshift
id|left
op_or
id|pat
op_rshift
id|right
suffix:semicolon
id|FB_WRITEL
c_func
(paren
id|FB_READL
c_func
(paren
id|dst
)paren
op_xor
id|pat
comma
id|dst
)paren
suffix:semicolon
id|dst
op_increment
suffix:semicolon
id|pat
op_assign
id|pat
op_lshift
id|left
op_or
id|pat
op_rshift
id|right
suffix:semicolon
id|FB_WRITEL
c_func
(paren
id|FB_READL
c_func
(paren
id|dst
)paren
op_xor
id|pat
comma
id|dst
)paren
suffix:semicolon
id|dst
op_increment
suffix:semicolon
id|pat
op_assign
id|pat
op_lshift
id|left
op_or
id|pat
op_rshift
id|right
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
id|FB_WRITEL
c_func
(paren
id|FB_READL
c_func
(paren
id|dst
)paren
op_xor
id|pat
comma
id|dst
)paren
suffix:semicolon
id|dst
op_increment
suffix:semicolon
id|pat
op_assign
id|pat
op_lshift
id|left
op_or
id|pat
op_rshift
id|right
suffix:semicolon
)brace
singleline_comment|// Trailing bits
r_if
c_cond
(paren
id|last
)paren
(brace
id|dat
op_assign
id|FB_READL
c_func
(paren
id|dst
)paren
suffix:semicolon
id|FB_WRITEL
c_func
(paren
id|comp
c_func
(paren
id|dat
op_xor
id|pat
comma
id|dat
comma
id|first
)paren
comma
id|dst
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|function|cfb_fillrect
r_void
id|cfb_fillrect
c_func
(paren
r_struct
id|fb_info
op_star
id|p
comma
r_const
r_struct
id|fb_fillrect
op_star
id|rect
)paren
(brace
id|u32
id|bpp
op_assign
id|p-&gt;var.bits_per_pixel
suffix:semicolon
r_int
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
id|height
comma
id|width
comma
id|fg
suffix:semicolon
r_int
r_int
op_star
id|dst
suffix:semicolon
r_int
id|dst_idx
comma
id|left
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
op_logical_neg
id|rect-&gt;width
op_logical_or
op_logical_neg
id|rect-&gt;height
op_logical_or
id|rect-&gt;dx
OG
id|vxres
op_logical_or
id|rect-&gt;dy
OG
id|vyres
)paren
r_return
suffix:semicolon
multiline_comment|/* We could use hardware clipping but on many cards you get around&n;&t; * hardware clipping by writing to framebuffer directly. */
id|x2
op_assign
id|rect-&gt;dx
op_plus
id|rect-&gt;width
suffix:semicolon
id|y2
op_assign
id|rect-&gt;dy
op_plus
id|rect-&gt;height
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
id|rect-&gt;dx
suffix:semicolon
id|height
op_assign
id|y2
op_minus
id|rect-&gt;dy
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;fix.visual
op_eq
id|FB_VISUAL_TRUECOLOR
op_logical_or
id|p-&gt;fix.visual
op_eq
id|FB_VISUAL_DIRECTCOLOR
)paren
id|fg
op_assign
(paren
(paren
id|u32
op_star
)paren
(paren
id|p-&gt;pseudo_palette
)paren
)paren
(braket
id|rect-&gt;color
)braket
suffix:semicolon
r_else
id|fg
op_assign
id|rect-&gt;color
suffix:semicolon
id|dst
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
op_star
l_int|8
suffix:semicolon
id|dst_idx
op_add_assign
id|rect-&gt;dy
op_star
id|p-&gt;fix.line_length
op_star
l_int|8
op_plus
id|rect-&gt;dx
op_star
id|bpp
suffix:semicolon
multiline_comment|/* FIXME For now we support 1-32 bpp only */
id|left
op_assign
id|BITS_PER_LONG
op_mod
id|bpp
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
op_logical_neg
id|left
)paren
(brace
id|u32
id|pat
op_assign
id|pixel_to_pat32
c_func
(paren
id|p
comma
id|fg
)paren
suffix:semicolon
r_void
(paren
op_star
id|fill_op32
)paren
(paren
r_int
r_int
op_star
id|dst
comma
r_int
id|dst_idx
comma
id|u32
id|pat
comma
id|u32
id|n
)paren
op_assign
l_int|NULL
suffix:semicolon
r_switch
c_cond
(paren
id|rect-&gt;rop
)paren
(brace
r_case
id|ROP_XOR
suffix:colon
id|fill_op32
op_assign
id|bitfill32_rev
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ROP_COPY
suffix:colon
r_default
suffix:colon
id|fill_op32
op_assign
id|bitfill32
suffix:semicolon
r_break
suffix:semicolon
)brace
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
id|BITS_PER_LONG
op_minus
l_int|1
)paren
suffix:semicolon
id|fill_op32
c_func
(paren
id|dst
comma
id|dst_idx
comma
id|pat
comma
id|width
op_star
id|bpp
)paren
suffix:semicolon
id|dst_idx
op_add_assign
id|p-&gt;fix.line_length
op_star
l_int|8
suffix:semicolon
)brace
)brace
r_else
(brace
r_int
r_int
id|pat
op_assign
id|pixel_to_pat
c_func
(paren
id|p
comma
id|fg
comma
(paren
id|left
op_minus
id|dst_idx
)paren
op_mod
id|bpp
)paren
suffix:semicolon
r_int
id|right
op_assign
id|bpp
op_minus
id|left
suffix:semicolon
r_int
id|r
suffix:semicolon
r_void
(paren
op_star
id|fill_op
)paren
(paren
r_int
r_int
op_star
id|dst
comma
r_int
id|dst_idx
comma
r_int
r_int
id|pat
comma
r_int
id|left
comma
r_int
id|right
comma
id|u32
id|n
)paren
op_assign
l_int|NULL
suffix:semicolon
r_switch
c_cond
(paren
id|rect-&gt;rop
)paren
(brace
r_case
id|ROP_XOR
suffix:colon
id|fill_op
op_assign
id|bitfill_rev
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ROP_COPY
suffix:colon
r_default
suffix:colon
id|fill_op
op_assign
id|bitfill
suffix:semicolon
r_break
suffix:semicolon
)brace
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
id|BITS_PER_LONG
op_minus
l_int|1
)paren
suffix:semicolon
id|fill_op
c_func
(paren
id|dst
comma
id|dst_idx
comma
id|pat
comma
id|left
comma
id|right
comma
id|width
op_star
id|bpp
)paren
suffix:semicolon
id|r
op_assign
(paren
id|p-&gt;fix.line_length
op_star
l_int|8
)paren
op_mod
id|bpp
suffix:semicolon
id|pat
op_assign
id|pat
op_lshift
(paren
id|bpp
op_minus
id|r
)paren
op_or
id|pat
op_rshift
id|r
suffix:semicolon
id|dst_idx
op_add_assign
id|p-&gt;fix.line_length
op_star
l_int|8
suffix:semicolon
)brace
)brace
)brace
DECL|variable|cfb_fillrect
id|EXPORT_SYMBOL
c_func
(paren
id|cfb_fillrect
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
l_string|&quot;Generic software accelerated fill rectangle&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
