multiline_comment|/*&n; *  Generic BitBLT function for frame buffer with packed pixels of any depth.&n; *&n; *      Copyright (C)  June 1999 James Simmons&n; *&n; *  This file is subject to the terms and conditions of the GNU General Public&n; *  License.  See the file COPYING in the main directory of this archive for&n; *  more details.&n; *&n; * NOTES:&n; *&n; *    This function copys a image from system memory to video memory. The&n; *  image can be a bitmap where each 0 represents the background color and&n; *  each 1 represents the foreground color. Great for font handling. It can&n; *  also be a color image. This is determined by image_depth. The color image&n; *  must be laid out exactly in the same format as the framebuffer. Yes I know&n; *  their are cards with hardware that coverts images of various depths to the&n; *  framebuffer depth. But not every card has this. All images must be rounded&n; *  up to the nearest byte. For example a bitmap 12 bits wide must be two &n; *  bytes width. &n; *&n; *  FIXME&n; *  The code for 24 bit is horrible. It copies byte by byte size instead of&n; *  longs like the other sizes. Needs to be optimized.&n; *  &n; *  Tony: &n; *  Incorporate mask tables similar to fbcon-cfb*.c in 2.4 API.  This speeds &n; *  up the code significantly.&n; *  &n; *  Code for depths not multiples of BITS_PER_LONG is still kludgy, which is&n; *  still processed a bit at a time.   &n; *&n; *  Also need to add code to deal with cards endians that are different than&n; *  the native cpu endians. I also need to deal with MSB position in the word.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/fb.h&gt;
macro_line|#include &lt;asm/types.h&gt;
DECL|macro|DEBUG
mdefine_line|#define DEBUG
macro_line|#ifdef DEBUG
DECL|macro|DPRINTK
mdefine_line|#define DPRINTK(fmt, args...) printk(KERN_DEBUG &quot;%s: &quot; fmt,__FUNCTION__,## args)
macro_line|#else
DECL|macro|DPRINTK
mdefine_line|#define DPRINTK(fmt, args...)
macro_line|#endif
DECL|variable|cfb_tab8
r_static
id|u32
id|cfb_tab8
(braket
)braket
op_assign
(brace
macro_line|#if defined(__BIG_ENDIAN)
l_int|0x00000000
comma
l_int|0x000000ff
comma
l_int|0x0000ff00
comma
l_int|0x0000ffff
comma
l_int|0x00ff0000
comma
l_int|0x00ff00ff
comma
l_int|0x00ffff00
comma
l_int|0x00ffffff
comma
l_int|0xff000000
comma
l_int|0xff0000ff
comma
l_int|0xff00ff00
comma
l_int|0xff00ffff
comma
l_int|0xffff0000
comma
l_int|0xffff00ff
comma
l_int|0xffffff00
comma
l_int|0xffffffff
macro_line|#elif defined(__LITTLE_ENDIAN)
l_int|0x00000000
comma
l_int|0xff000000
comma
l_int|0x00ff0000
comma
l_int|0xffff0000
comma
l_int|0x0000ff00
comma
l_int|0xff00ff00
comma
l_int|0x00ffff00
comma
l_int|0xffffff00
comma
l_int|0x000000ff
comma
l_int|0xff0000ff
comma
l_int|0x00ff00ff
comma
l_int|0xffff00ff
comma
l_int|0x0000ffff
comma
l_int|0xff00ffff
comma
l_int|0x00ffffff
comma
l_int|0xffffffff
macro_line|#else
macro_line|#error FIXME: No endianness??
macro_line|#endif
)brace
suffix:semicolon
DECL|variable|cfb_tab16
r_static
id|u32
id|cfb_tab16
(braket
)braket
op_assign
(brace
macro_line|#if defined(__BIG_ENDIAN)
l_int|0x00000000
comma
l_int|0x0000ffff
comma
l_int|0xffff0000
comma
l_int|0xffffffff
macro_line|#elif defined(__LITTLE_ENDIAN)
l_int|0x00000000
comma
l_int|0xffff0000
comma
l_int|0x0000ffff
comma
l_int|0xffffffff
macro_line|#else
macro_line|#error FIXME: No endianness??
macro_line|#endif
)brace
suffix:semicolon
DECL|variable|cfb_tab32
r_static
id|u32
id|cfb_tab32
(braket
)braket
op_assign
(brace
l_int|0x00000000
comma
l_int|0xffffffff
)brace
suffix:semicolon
macro_line|#if BITS_PER_LONG == 32
DECL|macro|FB_WRITEL
mdefine_line|#define FB_WRITEL fb_writel
DECL|macro|FB_READL
mdefine_line|#define FB_READL  fb_readl
macro_line|#else
DECL|macro|FB_WRITEL
mdefine_line|#define FB_WRITEL fb_writeq
DECL|macro|FB_READL
mdefine_line|#define FB_READL  fb_readq
macro_line|#endif 
macro_line|#if defined (__BIG_ENDIAN)
DECL|macro|LEFT_POS
mdefine_line|#define LEFT_POS(bpp)          (BITS_PER_LONG - bpp)
DECL|macro|NEXT_POS
mdefine_line|#define NEXT_POS(pos, bpp)     ((pos) -= (bpp))
DECL|macro|SHIFT_HIGH
mdefine_line|#define SHIFT_HIGH(val, bits)  ((val) &gt;&gt; (bits))
DECL|macro|SHIFT_LOW
mdefine_line|#define SHIFT_LOW(val, bits)   ((val) &lt;&lt; (bits))
macro_line|#else
DECL|macro|LEFT_POS
mdefine_line|#define LEFT_POS(bpp)          (0)
DECL|macro|NEXT_POS
mdefine_line|#define NEXT_POS(pos, bpp)     ((pos) += (bpp))
DECL|macro|SHIFT_HIGH
mdefine_line|#define SHIFT_HIGH(val, bits)  ((val) &lt;&lt; (bits))
DECL|macro|SHIFT_LOW
mdefine_line|#define SHIFT_LOW(val, bits)   ((val) &gt;&gt; (bits))
macro_line|#endif
DECL|function|color_imageblit
r_static
r_inline
r_void
id|color_imageblit
c_func
(paren
r_struct
id|fb_image
op_star
id|image
comma
r_struct
id|fb_info
op_star
id|p
comma
id|u8
op_star
id|dst1
comma
r_int
r_int
id|start_index
comma
r_int
r_int
id|pitch_index
)paren
(brace
multiline_comment|/* Draw the penguin */
r_int
id|i
comma
id|n
suffix:semicolon
r_int
r_int
id|bitmask
op_assign
id|SHIFT_LOW
c_func
(paren
op_complement
l_int|0UL
comma
id|BITS_PER_LONG
op_minus
id|p-&gt;var.bits_per_pixel
)paren
suffix:semicolon
r_int
r_int
op_star
id|palette
op_assign
(paren
r_int
r_int
op_star
)paren
id|p-&gt;pseudo_palette
suffix:semicolon
r_int
r_int
op_star
id|dst
comma
op_star
id|dst2
comma
id|color
op_assign
l_int|0
comma
id|val
comma
id|shift
suffix:semicolon
r_int
r_int
id|null_bits
op_assign
id|BITS_PER_LONG
op_minus
id|p-&gt;var.bits_per_pixel
suffix:semicolon
id|u8
op_star
id|src
op_assign
id|image-&gt;data
suffix:semicolon
id|dst2
op_assign
(paren
r_int
r_int
op_star
)paren
id|dst1
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|image-&gt;height
suffix:semicolon
id|i
op_decrement
suffix:semicolon
)paren
(brace
id|n
op_assign
id|image-&gt;width
suffix:semicolon
id|dst
op_assign
(paren
r_int
r_int
op_star
)paren
id|dst1
suffix:semicolon
id|shift
op_assign
l_int|0
suffix:semicolon
id|val
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|start_index
)paren
(brace
r_int
r_int
id|start_mask
op_assign
op_complement
(paren
id|SHIFT_HIGH
c_func
(paren
op_complement
l_int|0UL
comma
id|start_index
)paren
)paren
suffix:semicolon
id|val
op_assign
id|FB_READL
c_func
(paren
id|dst
)paren
op_amp
id|start_mask
suffix:semicolon
id|shift
op_assign
id|start_index
suffix:semicolon
)brace
r_while
c_loop
(paren
id|n
op_decrement
)paren
(brace
r_if
c_cond
(paren
id|p-&gt;fix.visual
op_eq
id|FB_VISUAL_PSEUDOCOLOR
)paren
id|color
op_assign
op_star
id|src
op_amp
id|bitmask
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
id|color
op_assign
id|palette
(braket
op_star
id|src
)braket
op_amp
id|bitmask
suffix:semicolon
id|val
op_or_assign
id|SHIFT_HIGH
c_func
(paren
id|color
comma
id|shift
)paren
suffix:semicolon
r_if
c_cond
(paren
id|shift
op_ge
id|null_bits
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
r_if
c_cond
(paren
id|shift
op_eq
id|null_bits
)paren
id|val
op_assign
l_int|0
suffix:semicolon
r_else
id|val
op_assign
id|SHIFT_LOW
c_func
(paren
id|color
comma
id|BITS_PER_LONG
op_minus
id|shift
)paren
suffix:semicolon
)brace
id|shift
op_add_assign
id|p-&gt;var.bits_per_pixel
suffix:semicolon
id|shift
op_and_assign
(paren
id|BITS_PER_LONG
op_minus
l_int|1
)paren
suffix:semicolon
id|src
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|shift
)paren
(brace
r_int
r_int
id|end_mask
op_assign
id|SHIFT_HIGH
c_func
(paren
op_complement
l_int|0UL
comma
id|shift
)paren
suffix:semicolon
id|FB_WRITEL
c_func
(paren
(paren
id|FB_READL
c_func
(paren
id|dst
)paren
op_amp
id|end_mask
)paren
op_or
id|val
comma
id|dst
)paren
suffix:semicolon
)brace
id|dst1
op_add_assign
id|p-&gt;fix.line_length
suffix:semicolon
r_if
c_cond
(paren
id|pitch_index
)paren
(brace
id|dst2
op_add_assign
id|p-&gt;fix.line_length
suffix:semicolon
id|dst1
op_assign
(paren
r_char
op_star
)paren
id|dst2
suffix:semicolon
(paren
r_int
r_int
)paren
id|dst1
op_and_assign
op_complement
(paren
r_sizeof
(paren
r_int
r_int
)paren
op_minus
l_int|1
)paren
suffix:semicolon
id|start_index
op_add_assign
id|pitch_index
suffix:semicolon
id|start_index
op_and_assign
id|BITS_PER_LONG
op_minus
l_int|1
suffix:semicolon
)brace
)brace
)brace
DECL|function|slow_imageblit
r_static
r_inline
r_void
id|slow_imageblit
c_func
(paren
r_struct
id|fb_image
op_star
id|image
comma
r_struct
id|fb_info
op_star
id|p
comma
id|u8
op_star
id|dst1
comma
r_int
r_int
id|fgcolor
comma
r_int
r_int
id|bgcolor
comma
r_int
r_int
id|start_index
comma
r_int
r_int
id|pitch_index
)paren
(brace
r_int
r_int
id|i
comma
id|j
comma
id|l
op_assign
l_int|8
suffix:semicolon
r_int
r_int
id|shift
comma
id|color
comma
id|bpp
op_assign
id|p-&gt;var.bits_per_pixel
suffix:semicolon
r_int
r_int
op_star
id|dst
comma
op_star
id|dst2
comma
id|val
comma
id|pitch
op_assign
id|p-&gt;fix.line_length
suffix:semicolon
r_int
r_int
id|null_bits
op_assign
id|BITS_PER_LONG
op_minus
id|bpp
suffix:semicolon
id|u8
op_star
id|src
op_assign
id|image-&gt;data
suffix:semicolon
id|dst2
op_assign
(paren
r_int
r_int
op_star
)paren
id|dst1
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|image-&gt;height
suffix:semicolon
id|i
op_decrement
suffix:semicolon
)paren
(brace
id|shift
op_assign
l_int|0
suffix:semicolon
id|val
op_assign
l_int|0
suffix:semicolon
id|j
op_assign
id|image-&gt;width
suffix:semicolon
id|dst
op_assign
(paren
r_int
r_int
op_star
)paren
id|dst1
suffix:semicolon
multiline_comment|/* write leading bits */
r_if
c_cond
(paren
id|start_index
)paren
(brace
r_int
r_int
id|start_mask
op_assign
op_complement
(paren
id|SHIFT_HIGH
c_func
(paren
op_complement
l_int|0UL
comma
id|start_index
)paren
)paren
suffix:semicolon
id|val
op_assign
id|FB_READL
c_func
(paren
id|dst
)paren
op_amp
id|start_mask
suffix:semicolon
id|shift
op_assign
id|start_index
suffix:semicolon
)brace
r_while
c_loop
(paren
id|j
op_decrement
)paren
(brace
id|l
op_decrement
suffix:semicolon
r_if
c_cond
(paren
op_star
id|src
op_amp
(paren
l_int|1
op_lshift
id|l
)paren
)paren
id|color
op_assign
id|fgcolor
suffix:semicolon
r_else
id|color
op_assign
id|bgcolor
suffix:semicolon
id|val
op_or_assign
id|SHIFT_HIGH
c_func
(paren
id|color
comma
id|shift
)paren
suffix:semicolon
multiline_comment|/* Did the bitshift spill bits to the next long? */
r_if
c_cond
(paren
id|shift
op_ge
id|null_bits
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
r_if
c_cond
(paren
id|shift
op_eq
id|null_bits
)paren
id|val
op_assign
l_int|0
suffix:semicolon
r_else
id|val
op_assign
id|SHIFT_LOW
c_func
(paren
id|color
comma
id|BITS_PER_LONG
op_minus
id|shift
)paren
suffix:semicolon
)brace
id|shift
op_add_assign
id|bpp
suffix:semicolon
id|shift
op_and_assign
(paren
id|BITS_PER_LONG
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|l
)paren
(brace
id|l
op_assign
l_int|8
suffix:semicolon
id|src
op_increment
suffix:semicolon
)brace
suffix:semicolon
)brace
multiline_comment|/* write trailing bits */
r_if
c_cond
(paren
id|shift
)paren
(brace
r_int
r_int
id|end_mask
op_assign
id|SHIFT_HIGH
c_func
(paren
op_complement
l_int|0UL
comma
id|shift
)paren
suffix:semicolon
id|FB_WRITEL
c_func
(paren
(paren
id|FB_READL
c_func
(paren
id|dst
)paren
op_amp
id|end_mask
)paren
op_or
id|val
comma
id|dst
)paren
suffix:semicolon
)brace
id|dst1
op_add_assign
id|pitch
suffix:semicolon
r_if
c_cond
(paren
id|pitch_index
)paren
(brace
id|dst2
op_add_assign
id|pitch
suffix:semicolon
id|dst1
op_assign
(paren
r_char
op_star
)paren
id|dst2
suffix:semicolon
(paren
r_int
r_int
)paren
id|dst1
op_and_assign
op_complement
(paren
r_sizeof
(paren
r_int
r_int
)paren
op_minus
l_int|1
)paren
suffix:semicolon
id|start_index
op_add_assign
id|pitch_index
suffix:semicolon
id|start_index
op_and_assign
id|BITS_PER_LONG
op_minus
l_int|1
suffix:semicolon
)brace
)brace
)brace
DECL|function|fast_imageblit
r_static
r_inline
r_void
id|fast_imageblit
c_func
(paren
r_struct
id|fb_image
op_star
id|image
comma
r_struct
id|fb_info
op_star
id|p
comma
id|u8
op_star
id|dst1
comma
r_int
r_int
id|fgcolor
comma
r_int
r_int
id|bgcolor
)paren
(brace
r_int
id|i
comma
id|j
comma
id|k
comma
id|l
op_assign
l_int|8
comma
id|n
suffix:semicolon
r_int
r_int
id|bit_mask
comma
id|end_mask
comma
id|eorx
suffix:semicolon
r_int
r_int
id|fgx
op_assign
id|fgcolor
comma
id|bgx
op_assign
id|bgcolor
comma
id|pad
comma
id|bpp
op_assign
id|p-&gt;var.bits_per_pixel
suffix:semicolon
r_int
r_int
id|tmp
op_assign
(paren
l_int|1
op_lshift
id|bpp
)paren
op_minus
l_int|1
suffix:semicolon
r_int
r_int
id|ppw
op_assign
id|BITS_PER_LONG
op_div
id|bpp
comma
id|ppos
suffix:semicolon
r_int
r_int
op_star
id|dst
suffix:semicolon
id|u32
op_star
id|tab
op_assign
l_int|NULL
suffix:semicolon
r_char
op_star
id|src
op_assign
id|image-&gt;data
suffix:semicolon
r_switch
c_cond
(paren
id|ppw
)paren
(brace
r_case
l_int|4
suffix:colon
id|tab
op_assign
id|cfb_tab8
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|tab
op_assign
id|cfb_tab16
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|tab
op_assign
id|cfb_tab32
suffix:semicolon
r_break
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
id|ppw
op_minus
l_int|1
suffix:semicolon
id|i
op_decrement
suffix:semicolon
)paren
(brace
id|fgx
op_lshift_assign
id|bpp
suffix:semicolon
id|bgx
op_lshift_assign
id|bpp
suffix:semicolon
id|fgx
op_or_assign
id|fgcolor
suffix:semicolon
id|bgx
op_or_assign
id|bgcolor
suffix:semicolon
)brace
id|n
op_assign
(paren
(paren
id|image-&gt;width
op_plus
l_int|7
)paren
op_div
l_int|8
)paren
suffix:semicolon
id|pad
op_assign
(paren
id|n
op_star
l_int|8
)paren
op_minus
id|image-&gt;width
suffix:semicolon
id|n
op_assign
id|image-&gt;width
op_mod
id|ppw
suffix:semicolon
id|bit_mask
op_assign
(paren
l_int|1
op_lshift
id|ppw
)paren
op_minus
l_int|1
suffix:semicolon
id|eorx
op_assign
id|fgx
op_xor
id|bgx
suffix:semicolon
id|k
op_assign
id|image-&gt;width
op_div
id|ppw
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|image-&gt;height
suffix:semicolon
id|i
op_decrement
suffix:semicolon
)paren
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
r_for
c_loop
(paren
id|j
op_assign
id|k
suffix:semicolon
id|j
op_decrement
suffix:semicolon
)paren
(brace
id|l
op_sub_assign
id|ppw
suffix:semicolon
id|end_mask
op_assign
id|tab
(braket
(paren
op_star
id|src
op_rshift
id|l
)paren
op_amp
id|bit_mask
)braket
suffix:semicolon
id|FB_WRITEL
c_func
(paren
(paren
id|end_mask
op_amp
id|eorx
)paren
op_xor
id|bgx
comma
id|dst
op_increment
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|l
)paren
(brace
id|l
op_assign
l_int|8
suffix:semicolon
id|src
op_increment
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|n
)paren
(brace
id|end_mask
op_assign
l_int|0
suffix:semicolon
id|ppos
op_assign
id|LEFT_POS
c_func
(paren
id|bpp
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
id|n
suffix:semicolon
id|j
OG
l_int|0
suffix:semicolon
id|j
op_decrement
)paren
(brace
id|l
op_decrement
suffix:semicolon
r_if
c_cond
(paren
op_star
id|src
op_amp
(paren
l_int|1
op_lshift
id|l
)paren
)paren
id|end_mask
op_or_assign
id|tmp
op_lshift
id|ppos
suffix:semicolon
id|NEXT_POS
c_func
(paren
id|ppos
comma
id|bpp
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|l
)paren
(brace
id|l
op_assign
l_int|8
suffix:semicolon
id|src
op_increment
suffix:semicolon
)brace
)brace
id|FB_WRITEL
c_func
(paren
(paren
id|end_mask
op_amp
id|eorx
)paren
op_xor
id|bgx
comma
id|dst
op_increment
)paren
suffix:semicolon
)brace
id|l
op_sub_assign
id|pad
suffix:semicolon
id|dst1
op_add_assign
id|p-&gt;fix.line_length
suffix:semicolon
)brace
)brace
DECL|function|cfb_imageblit
r_void
id|cfb_imageblit
c_func
(paren
r_struct
id|fb_info
op_star
id|p
comma
r_struct
id|fb_image
op_star
id|image
)paren
(brace
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
id|fgcolor
comma
id|bgcolor
comma
id|start_index
comma
id|bitstart
comma
id|pitch_index
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|bpl
op_assign
r_sizeof
(paren
r_int
r_int
)paren
comma
id|bpp
op_assign
id|p-&gt;var.bits_per_pixel
suffix:semicolon
id|u8
op_star
id|dst1
suffix:semicolon
id|vxres
op_assign
id|p-&gt;var.xres_virtual
suffix:semicolon
id|vyres
op_assign
id|p-&gt;var.yres_virtual
suffix:semicolon
multiline_comment|/* &n;&t; * We could use hardware clipping but on many cards you get around hardware&n;&t; * clipping by writing to framebuffer directly like we are doing here. &n;&t; */
r_if
c_cond
(paren
id|image-&gt;dx
OG
id|vxres
op_logical_or
id|image-&gt;dy
OG
id|vyres
)paren
r_return
suffix:semicolon
id|x2
op_assign
id|image-&gt;dx
op_plus
id|image-&gt;width
suffix:semicolon
id|y2
op_assign
id|image-&gt;dy
op_plus
id|image-&gt;height
suffix:semicolon
id|image-&gt;dx
op_assign
id|image-&gt;dx
OG
l_int|0
ques
c_cond
id|image-&gt;dx
suffix:colon
l_int|0
suffix:semicolon
id|image-&gt;dy
op_assign
id|image-&gt;dy
OG
l_int|0
ques
c_cond
id|image-&gt;dy
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
id|image-&gt;width
op_assign
id|x2
op_minus
id|image-&gt;dx
suffix:semicolon
id|image-&gt;height
op_assign
id|y2
op_minus
id|image-&gt;dy
suffix:semicolon
id|bitstart
op_assign
(paren
id|image-&gt;dy
op_star
id|p-&gt;fix.line_length
op_star
l_int|8
)paren
op_plus
(paren
id|image-&gt;dx
op_star
id|bpp
)paren
suffix:semicolon
id|start_index
op_assign
id|bitstart
op_amp
(paren
id|BITS_PER_LONG
op_minus
l_int|1
)paren
suffix:semicolon
id|pitch_index
op_assign
(paren
id|p-&gt;fix.line_length
op_amp
(paren
id|bpl
op_minus
l_int|1
)paren
)paren
op_star
l_int|8
suffix:semicolon
id|bitstart
op_div_assign
l_int|8
suffix:semicolon
id|bitstart
op_and_assign
op_complement
(paren
id|bpl
op_minus
l_int|1
)paren
suffix:semicolon
id|dst1
op_assign
id|p-&gt;screen_base
op_plus
id|bitstart
suffix:semicolon
r_if
c_cond
(paren
id|image-&gt;depth
op_eq
l_int|1
)paren
(brace
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
(brace
id|fgcolor
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
id|image-&gt;fg_color
)braket
suffix:semicolon
id|bgcolor
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
id|image-&gt;bg_color
)braket
suffix:semicolon
)brace
r_else
(brace
id|fgcolor
op_assign
id|image-&gt;fg_color
suffix:semicolon
id|bgcolor
op_assign
id|image-&gt;bg_color
suffix:semicolon
)brace
r_if
c_cond
(paren
id|BITS_PER_LONG
op_mod
id|bpp
op_eq
l_int|0
op_logical_and
op_logical_neg
id|start_index
op_logical_and
op_logical_neg
id|pitch_index
op_logical_and
id|bpp
op_ge
l_int|8
op_logical_and
id|bpp
op_le
l_int|32
op_logical_and
(paren
id|image-&gt;width
op_amp
l_int|7
)paren
op_eq
l_int|0
)paren
id|fast_imageblit
c_func
(paren
id|image
comma
id|p
comma
id|dst1
comma
id|fgcolor
comma
id|bgcolor
)paren
suffix:semicolon
r_else
id|slow_imageblit
c_func
(paren
id|image
comma
id|p
comma
id|dst1
comma
id|fgcolor
comma
id|bgcolor
comma
id|start_index
comma
id|pitch_index
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|image-&gt;depth
op_eq
id|bpp
)paren
id|color_imageblit
c_func
(paren
id|image
comma
id|p
comma
id|dst1
comma
id|start_index
comma
id|pitch_index
)paren
suffix:semicolon
)brace
macro_line|#ifdef MODULE
DECL|function|init_module
r_int
id|init_module
c_func
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
suffix:semicolon
DECL|function|cleanup_module
r_void
id|cleanup_module
c_func
(paren
r_void
)paren
(brace
)brace
suffix:semicolon
macro_line|#endif
DECL|variable|cfb_imageblit
id|EXPORT_SYMBOL
c_func
(paren
id|cfb_imageblit
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
l_string|&quot;Generic software accelerated imaging drawing&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
