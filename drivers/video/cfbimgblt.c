multiline_comment|/*&n; *  Generic BitBLT function for frame buffer with packed pixels of any depth.&n; *&n; *      Copyright (C)  June 1999 James Simmons&n; *&n; *  This file is subject to the terms and conditions of the GNU General Public&n; *  License.  See the file COPYING in the main directory of this archive for&n; *  more details.&n; *&n; * NOTES:&n; *&n; *    This function copys a image from system memory to video memory. The&n; *  image can be a bitmap where each 0 represents the background color and&n; *  each 1 represents the foreground color. Great for font handling. It can&n; *  also be a color image. This is determined by image_depth. The color image&n; *  must be laid out exactly in the same format as the framebuffer. Yes I know&n; *  their are cards with hardware that coverts images of various depths to the&n; *  framebuffer depth. But not every card has this. All images must be rounded&n; *  up to the nearest byte. For example a bitmap 12 bits wide must be two &n; *  bytes width. &n; *&n; *  FIXME&n; *  The code for 24 bit is horrible. It copies byte by byte size instead of&n; *  longs like the other sizes. Needs to be optimized.&n; *  &n; *  Tony: &n; *  Incorporate mask tables similar to fbcon-cfb*.c in 2.4 API.  This speeds &n; *  up the code significantly.&n; *  &n; *  Code for depths not multiples of BITS_PER_LONG is still kludgy, which is&n; *  still processed a bit at a time.   &n; *&n; *  Also need to add code to deal with cards endians that are different than&n; *  the native cpu endians. I also need to deal with MSB position in the word.&n; *&n; */
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
DECL|variable|cfb_pixarray
r_static
id|u32
id|cfb_pixarray
(braket
l_int|4
)braket
suffix:semicolon
DECL|variable|cfb_tabdef
r_static
id|u32
id|cfb_tabdef
(braket
l_int|2
)braket
suffix:semicolon
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
r_char
op_star
id|dst1
comma
r_int
id|fgcolor
comma
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
suffix:semicolon
r_int
r_int
id|tmp
op_assign
op_complement
l_int|0
op_lshift
(paren
id|BITS_PER_LONG
op_minus
id|p-&gt;var.bits_per_pixel
)paren
suffix:semicolon
r_int
r_int
id|ppw
op_assign
id|BITS_PER_LONG
op_div
id|p-&gt;var.bits_per_pixel
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
id|p-&gt;var.bits_per_pixel
suffix:semicolon
id|bgx
op_lshift_assign
id|p-&gt;var.bits_per_pixel
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
op_rshift
l_int|3
)paren
suffix:semicolon
id|pad
op_assign
(paren
id|n
op_lshift
l_int|3
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
id|fb_writel
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
id|test_bit
c_func
(paren
id|l
comma
(paren
r_int
r_int
op_star
)paren
id|src
)paren
)paren
id|end_mask
op_or_assign
(paren
id|tmp
op_rshift
(paren
id|p-&gt;var.bits_per_pixel
op_star
(paren
id|j
op_minus
l_int|1
)paren
)paren
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
id|fb_writel
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
multiline_comment|/*&n; * Slow method:  The idea is to find the number of pixels necessary to form&n; * dword-sized multiples that will be written to the framebuffer.  For BPP24, &n; * 4 pixels has to be read which are then packed into 3 double words that &n; * are then written to the framebuffer.&n; * &n; * With this method, processing is done 1 pixel at a time.&n; */
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
r_char
op_star
id|dst1
comma
r_int
id|fgcolor
comma
r_int
id|bgcolor
)paren
(brace
r_int
id|bytes
op_assign
(paren
id|p-&gt;var.bits_per_pixel
op_plus
l_int|7
)paren
op_rshift
l_int|3
suffix:semicolon
r_int
id|tmp
op_assign
op_complement
l_int|0UL
op_rshift
(paren
id|BITS_PER_LONG
op_minus
id|p-&gt;var.bits_per_pixel
)paren
suffix:semicolon
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
id|m
comma
id|end_mask
comma
id|eorx
suffix:semicolon
r_int
id|read
comma
id|write
comma
id|total
comma
id|pack_size
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
op_star
id|dst
suffix:semicolon
r_char
op_star
id|dst2
op_assign
(paren
r_char
op_star
)paren
id|cfb_pixarray
comma
op_star
id|src
op_assign
id|image-&gt;data
suffix:semicolon
id|cfb_tabdef
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
id|cfb_tabdef
(braket
l_int|1
)braket
op_assign
id|tmp
suffix:semicolon
id|eorx
op_assign
id|fgcolor
op_xor
id|bgcolor
suffix:semicolon
id|read
op_assign
(paren
id|bytes
op_plus
(paren
id|bpl
op_minus
l_int|1
)paren
)paren
op_amp
op_complement
(paren
id|bpl
op_minus
l_int|1
)paren
suffix:semicolon
id|write
op_assign
id|bytes
suffix:semicolon
id|total
op_assign
id|image-&gt;width
op_star
id|bytes
suffix:semicolon
id|pack_size
op_assign
id|bpl
op_star
id|write
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
id|j
op_assign
id|total
suffix:semicolon
id|m
op_assign
id|read
suffix:semicolon
r_while
c_loop
(paren
id|j
op_ge
id|pack_size
)paren
(brace
id|l
op_decrement
suffix:semicolon
id|m
op_decrement
suffix:semicolon
id|end_mask
op_assign
id|cfb_tabdef
(braket
(paren
op_star
id|src
op_rshift
id|l
)paren
op_amp
l_int|1
)braket
suffix:semicolon
op_star
(paren
r_int
r_int
op_star
)paren
id|dst2
op_assign
(paren
id|end_mask
op_amp
id|eorx
)paren
op_xor
id|bgcolor
suffix:semicolon
id|dst2
op_add_assign
id|bytes
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|m
)paren
(brace
r_for
c_loop
(paren
id|k
op_assign
l_int|0
suffix:semicolon
id|k
OL
id|write
suffix:semicolon
id|k
op_increment
)paren
id|fb_writel
c_func
(paren
id|cfb_pixarray
(braket
id|k
)braket
comma
id|dst
op_increment
)paren
suffix:semicolon
id|dst2
op_assign
(paren
r_char
op_star
)paren
id|cfb_pixarray
suffix:semicolon
id|j
op_sub_assign
id|pack_size
suffix:semicolon
id|m
op_assign
id|read
suffix:semicolon
)brace
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
multiline_comment|/* write residual pixels */
r_if
c_cond
(paren
id|j
)paren
(brace
id|k
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|j
op_decrement
)paren
id|fb_writeb
c_func
(paren
(paren
(paren
id|u8
op_star
)paren
id|cfb_pixarray
)paren
(braket
id|k
op_increment
)braket
comma
id|dst
op_increment
)paren
suffix:semicolon
)brace
id|dst1
op_add_assign
id|p-&gt;fix.line_length
suffix:semicolon
)brace
)brace
DECL|function|bitwise_blit
r_static
r_inline
r_void
id|bitwise_blit
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
r_char
op_star
id|dst1
comma
r_int
id|fgcolor
comma
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
comma
id|pad
comma
id|ppw
suffix:semicolon
r_int
r_int
id|tmp
op_assign
op_complement
l_int|0
op_lshift
(paren
id|BITS_PER_LONG
op_minus
id|p-&gt;var.bits_per_pixel
)paren
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
id|eorx
suffix:semicolon
r_int
r_int
id|end_mask
suffix:semicolon
r_int
r_int
op_star
id|dst
op_assign
l_int|NULL
suffix:semicolon
r_char
op_star
id|src
op_assign
id|image-&gt;data
suffix:semicolon
id|ppw
op_assign
id|BITS_PER_LONG
op_div
id|p-&gt;var.bits_per_pixel
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|ppw
op_minus
l_int|1
suffix:semicolon
id|i
op_increment
)paren
(brace
id|fgx
op_lshift_assign
id|p-&gt;var.bits_per_pixel
suffix:semicolon
id|bgx
op_lshift_assign
id|p-&gt;var.bits_per_pixel
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
id|eorx
op_assign
id|fgx
op_xor
id|bgx
suffix:semicolon
id|n
op_assign
(paren
(paren
id|image-&gt;width
op_plus
l_int|7
)paren
op_rshift
l_int|3
)paren
suffix:semicolon
id|pad
op_assign
(paren
id|n
op_lshift
l_int|3
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
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|image-&gt;height
suffix:semicolon
id|i
op_increment
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
id|image-&gt;width
op_div
id|ppw
suffix:semicolon
id|j
OG
l_int|0
suffix:semicolon
id|j
op_decrement
)paren
(brace
id|end_mask
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|k
op_assign
id|ppw
suffix:semicolon
id|k
OG
l_int|0
suffix:semicolon
id|k
op_decrement
)paren
(brace
id|l
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|l
comma
(paren
r_int
r_int
op_star
)paren
id|src
)paren
)paren
id|end_mask
op_or_assign
(paren
id|tmp
op_rshift
(paren
id|p-&gt;var.bits_per_pixel
op_star
(paren
id|k
op_minus
l_int|1
)paren
)paren
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
id|fb_writel
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
)paren
suffix:semicolon
id|dst
op_increment
suffix:semicolon
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
id|test_bit
c_func
(paren
id|l
comma
(paren
r_int
r_int
op_star
)paren
id|src
)paren
)paren
id|end_mask
op_or_assign
(paren
id|tmp
op_rshift
(paren
id|p-&gt;var.bits_per_pixel
op_star
(paren
id|j
op_minus
l_int|1
)paren
)paren
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
id|fb_writel
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
)paren
suffix:semicolon
id|dst
op_increment
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
id|n
suffix:semicolon
r_int
r_int
id|fgcolor
comma
id|bgcolor
suffix:semicolon
r_int
r_int
id|end_mask
suffix:semicolon
id|u8
op_star
id|dst1
suffix:semicolon
multiline_comment|/* &n;&t; * We could use hardware clipping but on many cards you get around hardware&n;&t; * clipping by writing to framebuffer directly like we are doing here. &n;&t; */
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
id|dst1
op_assign
id|p-&gt;screen_base
op_plus
id|image-&gt;dy
op_star
id|p-&gt;fix.line_length
op_plus
(paren
(paren
id|image-&gt;dx
op_star
id|p-&gt;var.bits_per_pixel
)paren
op_rshift
l_int|3
)paren
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
id|p-&gt;var.bits_per_pixel
op_ge
l_int|8
)paren
(brace
r_if
c_cond
(paren
id|BITS_PER_LONG
op_mod
id|p-&gt;var.bits_per_pixel
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
)paren
suffix:semicolon
)brace
r_else
multiline_comment|/* Is there such a thing as 3 or 5 bits per pixel? */
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
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Draw the penguin */
id|n
op_assign
(paren
(paren
id|image-&gt;width
op_star
id|p-&gt;var.bits_per_pixel
)paren
op_rshift
l_int|3
)paren
suffix:semicolon
id|end_mask
op_assign
l_int|0
suffix:semicolon
)brace
)brace
eof
