multiline_comment|/*&n; *  Generic function for frame buffer with packed pixels of any depth.&n; *&n; *      Copyright (C)  June 1999 James Simmons&n; *&n; *  This file is subject to the terms and conditions of the GNU General Public&n; *  License.  See the file COPYING in the main directory of this archive for&n; *  more details.&n; *&n; * NOTES:&n; * &n; *  This is for cfb packed pixels. Iplan and such are incorporated in the &n; *  drivers that need them.&n; * &n; *  FIXME&n; *  The code for 24 bit is horrible. It copies byte by byte size instead of &n; *  longs like the other sizes. Needs to be optimized. &n; *&n; *  Also need to add code to deal with cards endians that are different than &n; *  the native cpu endians. I also need to deal with MSB position in the word.&n; *  &n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/fb.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;video/fbcon.h&gt;
macro_line|#if BITS_PER_LONG == 32
DECL|macro|FB_READ
mdefine_line|#define FB_READ&t;&t;fb_readl
DECL|macro|FB_WRITE
mdefine_line|#define FB_WRITE&t;fb_writel
macro_line|#else
DECL|macro|FB_READ
mdefine_line|#define FB_READ&t;&t;fb_readq
DECL|macro|FB_WRITE
mdefine_line|#define FB_WRITE&t;fb_writeq
macro_line|#endif
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
r_struct
id|fb_copyarea
op_star
id|area
)paren
(brace
r_int
id|x2
comma
id|y2
comma
id|lineincr
comma
id|shift
comma
id|shift_right
comma
id|shift_left
comma
id|old_dx
comma
id|old_dy
suffix:semicolon
r_int
id|j
comma
id|linesize
op_assign
id|p-&gt;fix.line_length
comma
id|bpl
op_assign
r_sizeof
(paren
r_int
r_int
)paren
suffix:semicolon
r_int
r_int
id|start_index
comma
id|end_index
comma
id|start_mask
comma
id|end_mask
comma
id|last
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
r_char
op_star
id|src1
comma
op_star
id|dst1
suffix:semicolon
r_int
id|tmp
comma
id|height
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
id|area-&gt;dx
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
id|area-&gt;dy
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
id|p-&gt;var.xres_virtual
ques
c_cond
id|x2
suffix:colon
id|p-&gt;var.xres_virtual
suffix:semicolon
id|y2
op_assign
id|y2
OL
id|p-&gt;var.yres_virtual
ques
c_cond
id|y2
suffix:colon
id|p-&gt;var.yres_virtual
suffix:semicolon
id|area-&gt;width
op_assign
id|x2
op_minus
id|area-&gt;dx
suffix:semicolon
id|area-&gt;height
op_assign
id|y2
op_minus
id|area-&gt;dy
suffix:semicolon
multiline_comment|/* update sx1,sy1 */
id|area-&gt;sx
op_add_assign
(paren
id|area-&gt;dx
op_minus
id|old_dx
)paren
suffix:semicolon
id|area-&gt;sy
op_add_assign
(paren
id|area-&gt;dy
op_minus
id|old_dy
)paren
suffix:semicolon
id|height
op_assign
id|area-&gt;height
suffix:semicolon
multiline_comment|/* the source must be completely inside the virtual screen */
r_if
c_cond
(paren
id|area-&gt;sx
template_param
id|p-&gt;var.yres_virtual
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|area-&gt;dy
OL
id|area-&gt;sy
op_logical_or
(paren
id|area-&gt;dy
op_eq
id|area-&gt;sy
op_logical_and
id|area-&gt;dx
OL
id|area-&gt;sx
)paren
)paren
(brace
multiline_comment|/* start at the top */
id|src1
op_assign
id|p-&gt;screen_base
op_plus
id|area-&gt;sy
op_star
id|linesize
op_plus
(paren
(paren
id|area-&gt;sx
op_star
id|p-&gt;var.bits_per_pixel
)paren
op_rshift
l_int|3
)paren
suffix:semicolon
id|dst1
op_assign
id|p-&gt;screen_base
op_plus
id|area-&gt;dy
op_star
id|linesize
op_plus
(paren
(paren
id|area-&gt;dx
op_star
id|p-&gt;var.bits_per_pixel
)paren
op_rshift
l_int|3
)paren
suffix:semicolon
id|lineincr
op_assign
id|linesize
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* start at the bottom */
id|src1
op_assign
id|p-&gt;screen_base
op_plus
(paren
id|area-&gt;sy
op_plus
id|area-&gt;height
op_minus
l_int|1
)paren
op_star
id|linesize
op_plus
(paren
(paren
(paren
id|area-&gt;sx
op_plus
id|area-&gt;width
op_minus
l_int|1
)paren
op_star
id|p-&gt;var.bits_per_pixel
)paren
op_rshift
l_int|3
)paren
suffix:semicolon
id|dst1
op_assign
id|p-&gt;screen_base
op_plus
(paren
id|area-&gt;dy
op_plus
id|area-&gt;height
op_minus
l_int|1
)paren
op_star
id|linesize
op_plus
(paren
(paren
(paren
id|area-&gt;dx
op_plus
id|area-&gt;width
op_minus
l_int|1
)paren
op_star
id|p-&gt;var.bits_per_pixel
)paren
op_rshift
l_int|3
)paren
suffix:semicolon
id|lineincr
op_assign
op_minus
id|linesize
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|BITS_PER_LONG
op_mod
id|p-&gt;var.bits_per_pixel
)paren
op_eq
l_int|0
)paren
(brace
r_int
id|ppw
op_assign
id|BITS_PER_LONG
op_div
id|p-&gt;var.bits_per_pixel
suffix:semicolon
r_int
id|n
op_assign
(paren
(paren
id|area-&gt;width
op_star
id|p-&gt;var.bits_per_pixel
)paren
op_rshift
l_int|3
)paren
suffix:semicolon
id|start_index
op_assign
(paren
(paren
r_int
r_int
)paren
id|src1
op_amp
(paren
id|bpl
op_minus
l_int|1
)paren
)paren
suffix:semicolon
id|end_index
op_assign
(paren
(paren
r_int
r_int
)paren
(paren
id|src1
op_plus
id|n
)paren
op_amp
(paren
id|bpl
op_minus
l_int|1
)paren
)paren
suffix:semicolon
id|shift
op_assign
(paren
(paren
r_int
r_int
)paren
id|dst1
op_amp
(paren
id|bpl
op_minus
l_int|1
)paren
)paren
op_minus
(paren
(paren
r_int
r_int
)paren
id|src1
op_amp
(paren
id|bpl
op_minus
l_int|1
)paren
)paren
suffix:semicolon
id|start_mask
op_assign
id|end_mask
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|start_index
)paren
(brace
id|start_mask
op_assign
op_minus
l_int|1
op_rshift
(paren
id|start_index
op_lshift
l_int|3
)paren
suffix:semicolon
id|n
op_sub_assign
(paren
id|bpl
op_minus
id|start_index
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|end_index
)paren
(brace
id|end_mask
op_assign
op_minus
l_int|1
op_lshift
(paren
(paren
id|bpl
op_minus
id|end_index
)paren
op_lshift
l_int|3
)paren
suffix:semicolon
id|n
op_sub_assign
id|end_index
suffix:semicolon
)brace
id|n
op_div_assign
id|bpl
suffix:semicolon
r_if
c_cond
(paren
id|n
op_le
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|start_mask
)paren
(brace
r_if
c_cond
(paren
id|end_mask
)paren
id|end_mask
op_and_assign
id|start_mask
suffix:semicolon
r_else
id|end_mask
op_assign
id|start_mask
suffix:semicolon
id|start_mask
op_assign
l_int|0
suffix:semicolon
)brace
id|n
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|shift
)paren
(brace
r_if
c_cond
(paren
id|shift
OG
l_int|0
)paren
(brace
multiline_comment|/* dest is over to right more */
id|shift_right
op_assign
id|shift
op_star
id|p-&gt;var.bits_per_pixel
suffix:semicolon
id|shift_left
op_assign
(paren
id|ppw
op_minus
id|shift
)paren
op_star
id|p-&gt;var.bits_per_pixel
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* source is to the right more */
id|shift_right
op_assign
(paren
id|ppw
op_plus
id|shift
)paren
op_star
id|p-&gt;var.bits_per_pixel
suffix:semicolon
id|shift_left
op_assign
op_minus
id|shift
op_star
id|p-&gt;var.bits_per_pixel
suffix:semicolon
)brace
multiline_comment|/* general case, positive increment */
r_if
c_cond
(paren
id|lineincr
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|shift
OL
l_int|0
)paren
id|n
op_increment
suffix:semicolon
r_do
(brace
id|dst
op_assign
(paren
r_int
r_int
op_star
)paren
id|dst1
suffix:semicolon
id|src
op_assign
(paren
r_int
r_int
op_star
)paren
id|src1
suffix:semicolon
id|last
op_assign
(paren
id|FB_READ
c_func
(paren
id|src
)paren
op_amp
id|start_mask
)paren
suffix:semicolon
r_if
c_cond
(paren
id|shift
OG
l_int|0
)paren
id|FB_WRITE
c_func
(paren
id|FB_READ
c_func
(paren
id|dst
)paren
op_or
(paren
id|last
op_rshift
id|shift_right
)paren
comma
id|dst
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|n
suffix:semicolon
id|j
op_increment
)paren
(brace
id|dst
op_increment
suffix:semicolon
id|tmp
op_assign
id|FB_READ
c_func
(paren
id|src
)paren
suffix:semicolon
id|src
op_increment
suffix:semicolon
id|FB_WRITE
c_func
(paren
(paren
id|last
op_lshift
id|shift_left
)paren
op_or
(paren
id|tmp
op_rshift
id|shift_right
)paren
comma
id|dst
)paren
suffix:semicolon
id|last
op_assign
id|tmp
suffix:semicolon
id|src
op_increment
suffix:semicolon
)brace
id|FB_WRITE
c_func
(paren
id|FB_READ
c_func
(paren
id|dst
)paren
op_or
(paren
id|last
op_lshift
id|shift_left
)paren
comma
id|dst
)paren
suffix:semicolon
id|src1
op_add_assign
id|lineincr
suffix:semicolon
id|dst1
op_add_assign
id|lineincr
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|height
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* general case, negative increment */
r_if
c_cond
(paren
id|shift
OG
l_int|0
)paren
id|n
op_increment
suffix:semicolon
r_do
(brace
id|dst
op_assign
(paren
r_int
r_int
op_star
)paren
id|dst1
suffix:semicolon
id|src
op_assign
(paren
r_int
r_int
op_star
)paren
id|src1
suffix:semicolon
id|last
op_assign
(paren
id|FB_READ
c_func
(paren
id|src
)paren
op_amp
id|end_mask
)paren
suffix:semicolon
r_if
c_cond
(paren
id|shift
OL
l_int|0
)paren
id|FB_WRITE
c_func
(paren
id|FB_READ
c_func
(paren
id|dst
)paren
op_or
(paren
id|last
op_rshift
id|shift_right
)paren
comma
id|dst
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|n
suffix:semicolon
id|j
op_increment
)paren
(brace
id|dst
op_decrement
suffix:semicolon
id|tmp
op_assign
id|FB_READ
c_func
(paren
id|src
)paren
suffix:semicolon
id|src
op_decrement
suffix:semicolon
id|FB_WRITE
c_func
(paren
(paren
id|tmp
op_lshift
id|shift_left
)paren
op_or
(paren
id|last
op_rshift
id|shift_right
)paren
comma
id|dst
)paren
suffix:semicolon
id|last
op_assign
id|tmp
suffix:semicolon
id|src
op_decrement
suffix:semicolon
)brace
id|FB_WRITE
c_func
(paren
id|FB_READ
c_func
(paren
id|dst
)paren
op_or
(paren
id|last
op_rshift
id|shift_right
)paren
comma
id|dst
)paren
suffix:semicolon
id|src1
op_add_assign
id|lineincr
suffix:semicolon
id|dst1
op_add_assign
id|lineincr
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|height
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* no shift needed */
r_if
c_cond
(paren
id|lineincr
OG
l_int|0
)paren
(brace
multiline_comment|/* positive increment */
r_do
(brace
id|dst
op_assign
(paren
r_int
r_int
op_star
)paren
(paren
id|dst1
op_minus
id|start_index
)paren
suffix:semicolon
id|src
op_assign
(paren
r_int
r_int
op_star
)paren
(paren
id|src1
op_minus
id|start_index
)paren
suffix:semicolon
r_if
c_cond
(paren
id|start_mask
)paren
id|FB_WRITE
c_func
(paren
id|FB_READ
c_func
(paren
id|src
)paren
op_or
id|start_mask
comma
id|dst
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|n
suffix:semicolon
id|j
op_increment
)paren
(brace
id|FB_WRITE
c_func
(paren
id|FB_READ
c_func
(paren
id|src
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
)brace
r_if
c_cond
(paren
id|end_mask
)paren
id|FB_WRITE
c_func
(paren
id|FB_READ
c_func
(paren
id|src
)paren
op_or
id|end_mask
comma
id|dst
)paren
suffix:semicolon
id|src1
op_add_assign
id|lineincr
suffix:semicolon
id|dst1
op_add_assign
id|lineincr
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|height
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* negative increment */
r_do
(brace
id|dst
op_assign
(paren
r_int
r_int
op_star
)paren
id|dst1
suffix:semicolon
id|src
op_assign
(paren
r_int
r_int
op_star
)paren
id|src1
suffix:semicolon
r_if
c_cond
(paren
id|start_mask
)paren
id|FB_WRITE
c_func
(paren
id|FB_READ
c_func
(paren
id|src
)paren
op_or
id|start_mask
comma
id|dst
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|n
suffix:semicolon
id|j
op_increment
)paren
(brace
id|FB_WRITE
c_func
(paren
id|FB_READ
c_func
(paren
id|src
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
)brace
id|src1
op_add_assign
id|lineincr
suffix:semicolon
id|dst1
op_add_assign
id|lineincr
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|height
)paren
suffix:semicolon
)brace
)brace
)brace
)brace
eof
