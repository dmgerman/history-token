multiline_comment|/*&n; *  linux/drivers/video/console/bitblit.c -- BitBlitting Operation&n; *&n; *  Originally from the &squot;accel_*&squot; routines in drivers/video/console/fbcon.c&n; *&n; *      Copyright (C) 2004 Antonino Daplas &lt;adaplas @pol.net&gt;&n; *&n; *  This file is subject to the terms and conditions of the GNU General Public&n; *  License.  See the file COPYING in the main directory of this archive for&n; *  more details.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/fb.h&gt;
macro_line|#include &lt;linux/vt_kern.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &quot;fbcon.h&quot;
multiline_comment|/*&n; * Accelerated handlers.&n; */
DECL|macro|FBCON_ATTRIBUTE_UNDERLINE
mdefine_line|#define FBCON_ATTRIBUTE_UNDERLINE 1
DECL|macro|FBCON_ATTRIBUTE_REVERSE
mdefine_line|#define FBCON_ATTRIBUTE_REVERSE   2
DECL|macro|FBCON_ATTRIBUTE_BOLD
mdefine_line|#define FBCON_ATTRIBUTE_BOLD      4
DECL|function|real_y
r_static
r_inline
r_int
id|real_y
c_func
(paren
r_struct
id|display
op_star
id|p
comma
r_int
id|ypos
)paren
(brace
r_int
id|rows
op_assign
id|p-&gt;vrows
suffix:semicolon
id|ypos
op_add_assign
id|p-&gt;yscroll
suffix:semicolon
r_return
id|ypos
OL
id|rows
ques
c_cond
id|ypos
suffix:colon
id|ypos
op_minus
id|rows
suffix:semicolon
)brace
DECL|function|get_attribute
r_static
r_inline
r_int
id|get_attribute
c_func
(paren
r_struct
id|fb_info
op_star
id|info
comma
id|u16
id|c
)paren
(brace
r_int
id|attribute
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|fb_get_color_depth
c_func
(paren
op_amp
id|info-&gt;var
)paren
op_eq
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|attr_underline
c_func
(paren
id|c
)paren
)paren
id|attribute
op_or_assign
id|FBCON_ATTRIBUTE_UNDERLINE
suffix:semicolon
r_if
c_cond
(paren
id|attr_reverse
c_func
(paren
id|c
)paren
)paren
id|attribute
op_or_assign
id|FBCON_ATTRIBUTE_REVERSE
suffix:semicolon
r_if
c_cond
(paren
id|attr_bold
c_func
(paren
id|c
)paren
)paren
id|attribute
op_or_assign
id|FBCON_ATTRIBUTE_BOLD
suffix:semicolon
)brace
r_return
id|attribute
suffix:semicolon
)brace
DECL|function|update_attr
r_static
r_inline
r_void
id|update_attr
c_func
(paren
id|u8
op_star
id|dst
comma
id|u8
op_star
id|src
comma
r_int
id|attribute
comma
r_struct
id|vc_data
op_star
id|vc
)paren
(brace
r_int
id|i
comma
id|offset
op_assign
(paren
id|vc-&gt;vc_font.height
OL
l_int|10
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|2
suffix:semicolon
r_int
id|width
op_assign
(paren
id|vc-&gt;vc_font.width
op_plus
l_int|7
)paren
op_rshift
l_int|3
suffix:semicolon
r_int
r_int
id|cellsize
op_assign
id|vc-&gt;vc_font.height
op_star
id|width
suffix:semicolon
id|u8
id|c
suffix:semicolon
id|offset
op_assign
id|cellsize
op_minus
(paren
id|offset
op_star
id|width
)paren
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
id|cellsize
suffix:semicolon
id|i
op_increment
)paren
(brace
id|c
op_assign
id|src
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|attribute
op_amp
id|FBCON_ATTRIBUTE_UNDERLINE
op_logical_and
id|i
op_ge
id|offset
)paren
id|c
op_assign
l_int|0xff
suffix:semicolon
r_if
c_cond
(paren
id|attribute
op_amp
id|FBCON_ATTRIBUTE_BOLD
)paren
id|c
op_or_assign
id|c
op_rshift
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|attribute
op_amp
id|FBCON_ATTRIBUTE_REVERSE
)paren
id|c
op_assign
op_complement
id|c
suffix:semicolon
id|dst
(braket
id|i
)braket
op_assign
id|c
suffix:semicolon
)brace
)brace
DECL|function|bit_bmove
r_static
r_void
id|bit_bmove
c_func
(paren
r_struct
id|vc_data
op_star
id|vc
comma
r_struct
id|fb_info
op_star
id|info
comma
r_int
id|sy
comma
r_int
id|sx
comma
r_int
id|dy
comma
r_int
id|dx
comma
r_int
id|height
comma
r_int
id|width
)paren
(brace
r_struct
id|fb_copyarea
id|area
suffix:semicolon
id|area.sx
op_assign
id|sx
op_star
id|vc-&gt;vc_font.width
suffix:semicolon
id|area.sy
op_assign
id|sy
op_star
id|vc-&gt;vc_font.height
suffix:semicolon
id|area.dx
op_assign
id|dx
op_star
id|vc-&gt;vc_font.width
suffix:semicolon
id|area.dy
op_assign
id|dy
op_star
id|vc-&gt;vc_font.height
suffix:semicolon
id|area.height
op_assign
id|height
op_star
id|vc-&gt;vc_font.height
suffix:semicolon
id|area.width
op_assign
id|width
op_star
id|vc-&gt;vc_font.width
suffix:semicolon
id|info-&gt;fbops
op_member_access_from_pointer
id|fb_copyarea
c_func
(paren
id|info
comma
op_amp
id|area
)paren
suffix:semicolon
)brace
DECL|function|bit_clear
r_static
r_void
id|bit_clear
c_func
(paren
r_struct
id|vc_data
op_star
id|vc
comma
r_struct
id|fb_info
op_star
id|info
comma
r_int
id|sy
comma
r_int
id|sx
comma
r_int
id|height
comma
r_int
id|width
)paren
(brace
r_int
id|bgshift
op_assign
(paren
id|vc-&gt;vc_hi_font_mask
)paren
ques
c_cond
l_int|13
suffix:colon
l_int|12
suffix:semicolon
r_struct
id|fb_fillrect
id|region
suffix:semicolon
id|region.color
op_assign
id|attr_bgcol_ec
c_func
(paren
id|bgshift
comma
id|vc
)paren
suffix:semicolon
id|region.dx
op_assign
id|sx
op_star
id|vc-&gt;vc_font.width
suffix:semicolon
id|region.dy
op_assign
id|sy
op_star
id|vc-&gt;vc_font.height
suffix:semicolon
id|region.width
op_assign
id|width
op_star
id|vc-&gt;vc_font.width
suffix:semicolon
id|region.height
op_assign
id|height
op_star
id|vc-&gt;vc_font.height
suffix:semicolon
id|region.rop
op_assign
id|ROP_COPY
suffix:semicolon
id|info-&gt;fbops
op_member_access_from_pointer
id|fb_fillrect
c_func
(paren
id|info
comma
op_amp
id|region
)paren
suffix:semicolon
)brace
DECL|function|bit_putcs
r_static
r_void
id|bit_putcs
c_func
(paren
r_struct
id|vc_data
op_star
id|vc
comma
r_struct
id|fb_info
op_star
id|info
comma
r_const
r_int
r_int
op_star
id|s
comma
r_int
id|count
comma
r_int
id|yy
comma
r_int
id|xx
comma
r_int
id|fg
comma
r_int
id|bg
)paren
(brace
r_void
(paren
op_star
id|move_unaligned
)paren
(paren
r_struct
id|fb_info
op_star
id|info
comma
r_struct
id|fb_pixmap
op_star
id|buf
comma
id|u8
op_star
id|dst
comma
id|u32
id|d_pitch
comma
id|u8
op_star
id|src
comma
id|u32
id|idx
comma
id|u32
id|height
comma
id|u32
id|shift_high
comma
id|u32
id|shift_low
comma
id|u32
id|mod
)paren
suffix:semicolon
r_void
(paren
op_star
id|move_aligned
)paren
(paren
r_struct
id|fb_info
op_star
id|info
comma
r_struct
id|fb_pixmap
op_star
id|buf
comma
id|u8
op_star
id|dst
comma
id|u32
id|d_pitch
comma
id|u8
op_star
id|src
comma
id|u32
id|s_pitch
comma
id|u32
id|height
)paren
suffix:semicolon
r_int
r_int
id|charmask
op_assign
id|vc-&gt;vc_hi_font_mask
ques
c_cond
l_int|0x1ff
suffix:colon
l_int|0xff
suffix:semicolon
r_int
r_int
id|width
op_assign
(paren
id|vc-&gt;vc_font.width
op_plus
l_int|7
)paren
op_rshift
l_int|3
suffix:semicolon
r_int
r_int
id|cellsize
op_assign
id|vc-&gt;vc_font.height
op_star
id|width
suffix:semicolon
r_int
r_int
id|maxcnt
op_assign
id|info-&gt;pixmap.size
op_div
id|cellsize
suffix:semicolon
r_int
r_int
id|scan_align
op_assign
id|info-&gt;pixmap.scan_align
op_minus
l_int|1
suffix:semicolon
r_int
r_int
id|buf_align
op_assign
id|info-&gt;pixmap.buf_align
op_minus
l_int|1
suffix:semicolon
r_int
r_int
id|shift_low
op_assign
l_int|0
comma
id|mod
op_assign
id|vc-&gt;vc_font.width
op_mod
l_int|8
suffix:semicolon
r_int
r_int
id|shift_high
op_assign
l_int|8
comma
id|pitch
comma
id|cnt
comma
id|size
comma
id|k
suffix:semicolon
r_int
r_int
id|idx
op_assign
id|vc-&gt;vc_font.width
op_rshift
l_int|3
suffix:semicolon
r_int
r_int
id|attribute
op_assign
id|get_attribute
c_func
(paren
id|info
comma
id|scr_readw
c_func
(paren
id|s
)paren
)paren
suffix:semicolon
r_struct
id|fb_image
id|image
suffix:semicolon
id|u8
op_star
id|src
comma
op_star
id|dst
comma
op_star
id|buf
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|attribute
)paren
(brace
id|buf
op_assign
id|kmalloc
c_func
(paren
id|cellsize
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buf
)paren
r_return
suffix:semicolon
)brace
id|image.fg_color
op_assign
id|fg
suffix:semicolon
id|image.bg_color
op_assign
id|bg
suffix:semicolon
id|image.dx
op_assign
id|xx
op_star
id|vc-&gt;vc_font.width
suffix:semicolon
id|image.dy
op_assign
id|yy
op_star
id|vc-&gt;vc_font.height
suffix:semicolon
id|image.height
op_assign
id|vc-&gt;vc_font.height
suffix:semicolon
id|image.depth
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;pixmap.outbuf
op_logical_and
id|info-&gt;pixmap.inbuf
)paren
(brace
id|move_aligned
op_assign
id|fb_iomove_buf_aligned
suffix:semicolon
id|move_unaligned
op_assign
id|fb_iomove_buf_unaligned
suffix:semicolon
)brace
r_else
(brace
id|move_aligned
op_assign
id|fb_sysmove_buf_aligned
suffix:semicolon
id|move_unaligned
op_assign
id|fb_sysmove_buf_unaligned
suffix:semicolon
)brace
r_while
c_loop
(paren
id|count
)paren
(brace
r_if
c_cond
(paren
id|count
OG
id|maxcnt
)paren
id|cnt
op_assign
id|k
op_assign
id|maxcnt
suffix:semicolon
r_else
id|cnt
op_assign
id|k
op_assign
id|count
suffix:semicolon
id|image.width
op_assign
id|vc-&gt;vc_font.width
op_star
id|cnt
suffix:semicolon
id|pitch
op_assign
(paren
(paren
id|image.width
op_plus
l_int|7
)paren
op_rshift
l_int|3
)paren
op_plus
id|scan_align
suffix:semicolon
id|pitch
op_and_assign
op_complement
id|scan_align
suffix:semicolon
id|size
op_assign
id|pitch
op_star
id|image.height
op_plus
id|buf_align
suffix:semicolon
id|size
op_and_assign
op_complement
id|buf_align
suffix:semicolon
id|dst
op_assign
id|fb_get_buffer_offset
c_func
(paren
id|info
comma
op_amp
id|info-&gt;pixmap
comma
id|size
)paren
suffix:semicolon
id|image.data
op_assign
id|dst
suffix:semicolon
r_if
c_cond
(paren
id|mod
)paren
(brace
r_while
c_loop
(paren
id|k
op_decrement
)paren
(brace
id|src
op_assign
id|vc-&gt;vc_font.data
op_plus
(paren
id|scr_readw
c_func
(paren
id|s
op_increment
)paren
op_amp
id|charmask
)paren
op_star
id|cellsize
suffix:semicolon
r_if
c_cond
(paren
id|attribute
)paren
(brace
id|update_attr
c_func
(paren
id|buf
comma
id|src
comma
id|attribute
comma
id|vc
)paren
suffix:semicolon
id|src
op_assign
id|buf
suffix:semicolon
)brace
id|move_unaligned
c_func
(paren
id|info
comma
op_amp
id|info-&gt;pixmap
comma
id|dst
comma
id|pitch
comma
id|src
comma
id|idx
comma
id|image.height
comma
id|shift_high
comma
id|shift_low
comma
id|mod
)paren
suffix:semicolon
id|shift_low
op_add_assign
id|mod
suffix:semicolon
id|dst
op_add_assign
(paren
id|shift_low
op_ge
l_int|8
)paren
ques
c_cond
id|width
suffix:colon
id|width
op_minus
l_int|1
suffix:semicolon
id|shift_low
op_and_assign
l_int|7
suffix:semicolon
id|shift_high
op_assign
l_int|8
op_minus
id|shift_low
suffix:semicolon
)brace
)brace
r_else
(brace
r_while
c_loop
(paren
id|k
op_decrement
)paren
(brace
id|src
op_assign
id|vc-&gt;vc_font.data
op_plus
(paren
id|scr_readw
c_func
(paren
id|s
op_increment
)paren
op_amp
id|charmask
)paren
op_star
id|cellsize
suffix:semicolon
r_if
c_cond
(paren
id|attribute
)paren
(brace
id|update_attr
c_func
(paren
id|buf
comma
id|src
comma
id|attribute
comma
id|vc
)paren
suffix:semicolon
id|src
op_assign
id|buf
suffix:semicolon
)brace
id|move_aligned
c_func
(paren
id|info
comma
op_amp
id|info-&gt;pixmap
comma
id|dst
comma
id|pitch
comma
id|src
comma
id|idx
comma
id|image.height
)paren
suffix:semicolon
id|dst
op_add_assign
id|width
suffix:semicolon
)brace
)brace
id|info-&gt;fbops
op_member_access_from_pointer
id|fb_imageblit
c_func
(paren
id|info
comma
op_amp
id|image
)paren
suffix:semicolon
id|image.dx
op_add_assign
id|cnt
op_star
id|vc-&gt;vc_font.width
suffix:semicolon
id|count
op_sub_assign
id|cnt
suffix:semicolon
)brace
r_if
c_cond
(paren
id|buf
)paren
id|kfree
c_func
(paren
id|buf
)paren
suffix:semicolon
)brace
DECL|function|bit_clear_margins
r_static
r_void
id|bit_clear_margins
c_func
(paren
r_struct
id|vc_data
op_star
id|vc
comma
r_struct
id|fb_info
op_star
id|info
comma
r_int
id|bottom_only
)paren
(brace
r_int
id|bgshift
op_assign
(paren
id|vc-&gt;vc_hi_font_mask
)paren
ques
c_cond
l_int|13
suffix:colon
l_int|12
suffix:semicolon
r_int
r_int
id|cw
op_assign
id|vc-&gt;vc_font.width
suffix:semicolon
r_int
r_int
id|ch
op_assign
id|vc-&gt;vc_font.height
suffix:semicolon
r_int
r_int
id|rw
op_assign
id|info-&gt;var.xres
op_minus
(paren
id|vc-&gt;vc_cols
op_star
id|cw
)paren
suffix:semicolon
r_int
r_int
id|bh
op_assign
id|info-&gt;var.yres
op_minus
(paren
id|vc-&gt;vc_rows
op_star
id|ch
)paren
suffix:semicolon
r_int
r_int
id|rs
op_assign
id|info-&gt;var.xres
op_minus
id|rw
suffix:semicolon
r_int
r_int
id|bs
op_assign
id|info-&gt;var.yres
op_minus
id|bh
suffix:semicolon
r_struct
id|fb_fillrect
id|region
suffix:semicolon
id|region.color
op_assign
id|attr_bgcol_ec
c_func
(paren
id|bgshift
comma
id|vc
)paren
suffix:semicolon
id|region.rop
op_assign
id|ROP_COPY
suffix:semicolon
r_if
c_cond
(paren
id|rw
op_logical_and
op_logical_neg
id|bottom_only
)paren
(brace
id|region.dx
op_assign
id|info-&gt;var.xoffset
op_plus
id|rs
suffix:semicolon
id|region.dy
op_assign
l_int|0
suffix:semicolon
id|region.width
op_assign
id|rw
suffix:semicolon
id|region.height
op_assign
id|info-&gt;var.yres_virtual
suffix:semicolon
id|info-&gt;fbops
op_member_access_from_pointer
id|fb_fillrect
c_func
(paren
id|info
comma
op_amp
id|region
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|bh
)paren
(brace
id|region.dx
op_assign
id|info-&gt;var.xoffset
suffix:semicolon
id|region.dy
op_assign
id|info-&gt;var.yoffset
op_plus
id|bs
suffix:semicolon
id|region.width
op_assign
id|rs
suffix:semicolon
id|region.height
op_assign
id|bh
suffix:semicolon
id|info-&gt;fbops
op_member_access_from_pointer
id|fb_fillrect
c_func
(paren
id|info
comma
op_amp
id|region
)paren
suffix:semicolon
)brace
)brace
DECL|function|bit_cursor
r_static
r_void
id|bit_cursor
c_func
(paren
r_struct
id|vc_data
op_star
id|vc
comma
r_struct
id|fb_info
op_star
id|info
comma
r_struct
id|display
op_star
id|p
comma
r_int
id|mode
comma
r_int
id|fg
comma
r_int
id|bg
)paren
(brace
r_struct
id|fb_cursor
id|cursor
suffix:semicolon
r_struct
id|fbcon_ops
op_star
id|ops
op_assign
(paren
r_struct
id|fbcon_ops
op_star
)paren
id|info-&gt;fbcon_par
suffix:semicolon
r_int
r_int
id|charmask
op_assign
id|vc-&gt;vc_hi_font_mask
ques
c_cond
l_int|0x1ff
suffix:colon
l_int|0xff
suffix:semicolon
r_int
id|w
op_assign
(paren
id|vc-&gt;vc_font.width
op_plus
l_int|7
)paren
op_rshift
l_int|3
comma
id|c
suffix:semicolon
r_int
id|y
op_assign
id|real_y
c_func
(paren
id|p
comma
id|vc-&gt;vc_y
)paren
suffix:semicolon
r_int
id|attribute
comma
id|use_sw
op_assign
(paren
id|vc-&gt;vc_cursor_type
op_amp
l_int|0x10
)paren
suffix:semicolon
r_char
op_star
id|src
suffix:semicolon
id|cursor.set
op_assign
l_int|0
suffix:semicolon
id|c
op_assign
id|scr_readw
c_func
(paren
(paren
id|u16
op_star
)paren
id|vc-&gt;vc_pos
)paren
suffix:semicolon
id|attribute
op_assign
id|get_attribute
c_func
(paren
id|info
comma
id|c
)paren
suffix:semicolon
id|src
op_assign
id|vc-&gt;vc_font.data
op_plus
(paren
(paren
id|c
op_amp
id|charmask
)paren
op_star
(paren
id|w
op_star
id|vc-&gt;vc_font.height
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ops-&gt;cursor_state.image.data
op_ne
id|src
op_logical_or
id|ops-&gt;cursor_reset
)paren
(brace
id|ops-&gt;cursor_state.image.data
op_assign
id|src
suffix:semicolon
id|cursor.set
op_or_assign
id|FB_CUR_SETIMAGE
suffix:semicolon
)brace
r_if
c_cond
(paren
id|attribute
)paren
(brace
id|u8
op_star
id|dst
suffix:semicolon
id|dst
op_assign
id|kmalloc
c_func
(paren
id|w
op_star
id|vc-&gt;vc_font.height
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dst
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|ops-&gt;cursor_data
)paren
id|kfree
c_func
(paren
id|ops-&gt;cursor_data
)paren
suffix:semicolon
id|ops-&gt;cursor_data
op_assign
id|dst
suffix:semicolon
id|update_attr
c_func
(paren
id|dst
comma
id|src
comma
id|attribute
comma
id|vc
)paren
suffix:semicolon
id|src
op_assign
id|dst
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ops-&gt;cursor_state.image.fg_color
op_ne
id|fg
op_logical_or
id|ops-&gt;cursor_state.image.bg_color
op_ne
id|bg
op_logical_or
id|ops-&gt;cursor_reset
)paren
(brace
id|ops-&gt;cursor_state.image.fg_color
op_assign
id|fg
suffix:semicolon
id|ops-&gt;cursor_state.image.bg_color
op_assign
id|bg
suffix:semicolon
id|cursor.set
op_or_assign
id|FB_CUR_SETCMAP
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|ops-&gt;cursor_state.image.dx
op_ne
(paren
id|vc-&gt;vc_font.width
op_star
id|vc-&gt;vc_x
)paren
)paren
op_logical_or
(paren
id|ops-&gt;cursor_state.image.dy
op_ne
(paren
id|vc-&gt;vc_font.height
op_star
id|y
)paren
)paren
op_logical_or
id|ops-&gt;cursor_reset
)paren
(brace
id|ops-&gt;cursor_state.image.dx
op_assign
id|vc-&gt;vc_font.width
op_star
id|vc-&gt;vc_x
suffix:semicolon
id|ops-&gt;cursor_state.image.dy
op_assign
id|vc-&gt;vc_font.height
op_star
id|y
suffix:semicolon
id|cursor.set
op_or_assign
id|FB_CUR_SETPOS
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ops-&gt;cursor_state.image.height
op_ne
id|vc-&gt;vc_font.height
op_logical_or
id|ops-&gt;cursor_state.image.width
op_ne
id|vc-&gt;vc_font.width
op_logical_or
id|ops-&gt;cursor_reset
)paren
(brace
id|ops-&gt;cursor_state.image.height
op_assign
id|vc-&gt;vc_font.height
suffix:semicolon
id|ops-&gt;cursor_state.image.width
op_assign
id|vc-&gt;vc_font.width
suffix:semicolon
id|cursor.set
op_or_assign
id|FB_CUR_SETSIZE
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ops-&gt;cursor_state.hot.x
op_logical_or
id|ops-&gt;cursor_state.hot.y
op_logical_or
id|ops-&gt;cursor_reset
)paren
(brace
id|ops-&gt;cursor_state.hot.x
op_assign
id|cursor.hot.y
op_assign
l_int|0
suffix:semicolon
id|cursor.set
op_or_assign
id|FB_CUR_SETHOT
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cursor.set
op_amp
id|FB_CUR_SETSIZE
op_logical_or
id|vc-&gt;vc_cursor_type
op_ne
id|p-&gt;cursor_shape
op_logical_or
id|ops-&gt;cursor_state.mask
op_eq
l_int|NULL
op_logical_or
id|ops-&gt;cursor_reset
)paren
(brace
r_char
op_star
id|mask
op_assign
id|kmalloc
c_func
(paren
id|w
op_star
id|vc-&gt;vc_font.height
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_int
id|cur_height
comma
id|size
comma
id|i
op_assign
l_int|0
suffix:semicolon
id|u8
id|msk
op_assign
l_int|0xff
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mask
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|ops-&gt;cursor_state.mask
)paren
id|kfree
c_func
(paren
id|ops-&gt;cursor_state.mask
)paren
suffix:semicolon
id|ops-&gt;cursor_state.mask
op_assign
id|mask
suffix:semicolon
id|p-&gt;cursor_shape
op_assign
id|vc-&gt;vc_cursor_type
suffix:semicolon
id|cursor.set
op_or_assign
id|FB_CUR_SETSHAPE
suffix:semicolon
r_switch
c_cond
(paren
id|p-&gt;cursor_shape
op_amp
id|CUR_HWMASK
)paren
(brace
r_case
id|CUR_NONE
suffix:colon
id|cur_height
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CUR_UNDERLINE
suffix:colon
id|cur_height
op_assign
(paren
id|vc-&gt;vc_font.height
OL
l_int|10
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|2
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CUR_LOWER_THIRD
suffix:colon
id|cur_height
op_assign
id|vc-&gt;vc_font.height
op_div
l_int|3
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CUR_LOWER_HALF
suffix:colon
id|cur_height
op_assign
id|vc-&gt;vc_font.height
op_rshift
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CUR_TWO_THIRDS
suffix:colon
id|cur_height
op_assign
(paren
id|vc-&gt;vc_font.height
op_lshift
l_int|1
)paren
op_div
l_int|3
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CUR_BLOCK
suffix:colon
r_default
suffix:colon
id|cur_height
op_assign
id|vc-&gt;vc_font.height
suffix:semicolon
r_break
suffix:semicolon
)brace
id|size
op_assign
(paren
id|vc-&gt;vc_font.height
op_minus
id|cur_height
)paren
op_star
id|w
suffix:semicolon
r_while
c_loop
(paren
id|size
op_decrement
)paren
id|mask
(braket
id|i
op_increment
)braket
op_assign
op_complement
id|msk
suffix:semicolon
id|size
op_assign
id|cur_height
op_star
id|w
suffix:semicolon
r_while
c_loop
(paren
id|size
op_decrement
)paren
id|mask
(braket
id|i
op_increment
)braket
op_assign
id|msk
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|mode
)paren
(brace
r_case
id|CM_ERASE
suffix:colon
id|ops-&gt;cursor_state.enable
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CM_DRAW
suffix:colon
r_case
id|CM_MOVE
suffix:colon
r_default
suffix:colon
id|ops-&gt;cursor_state.enable
op_assign
(paren
id|use_sw
)paren
ques
c_cond
l_int|0
suffix:colon
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
id|cursor.image.data
op_assign
id|src
suffix:semicolon
id|cursor.image.fg_color
op_assign
id|ops-&gt;cursor_state.image.fg_color
suffix:semicolon
id|cursor.image.bg_color
op_assign
id|ops-&gt;cursor_state.image.bg_color
suffix:semicolon
id|cursor.image.dx
op_assign
id|ops-&gt;cursor_state.image.dx
suffix:semicolon
id|cursor.image.dy
op_assign
id|ops-&gt;cursor_state.image.dy
suffix:semicolon
id|cursor.image.height
op_assign
id|ops-&gt;cursor_state.image.height
suffix:semicolon
id|cursor.image.width
op_assign
id|ops-&gt;cursor_state.image.width
suffix:semicolon
id|cursor.hot.x
op_assign
id|ops-&gt;cursor_state.hot.x
suffix:semicolon
id|cursor.hot.y
op_assign
id|ops-&gt;cursor_state.hot.y
suffix:semicolon
id|cursor.mask
op_assign
id|ops-&gt;cursor_state.mask
suffix:semicolon
id|cursor.enable
op_assign
id|ops-&gt;cursor_state.enable
suffix:semicolon
id|cursor.image.depth
op_assign
l_int|1
suffix:semicolon
id|cursor.rop
op_assign
id|ROP_XOR
suffix:semicolon
id|info-&gt;fbops
op_member_access_from_pointer
id|fb_cursor
c_func
(paren
id|info
comma
op_amp
id|cursor
)paren
suffix:semicolon
id|ops-&gt;cursor_reset
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|fbcon_set_bitops
r_void
id|fbcon_set_bitops
c_func
(paren
r_struct
id|fbcon_ops
op_star
id|ops
)paren
(brace
id|ops-&gt;bmove
op_assign
id|bit_bmove
suffix:semicolon
id|ops-&gt;clear
op_assign
id|bit_clear
suffix:semicolon
id|ops-&gt;putcs
op_assign
id|bit_putcs
suffix:semicolon
id|ops-&gt;clear_margins
op_assign
id|bit_clear_margins
suffix:semicolon
id|ops-&gt;cursor
op_assign
id|bit_cursor
suffix:semicolon
)brace
DECL|variable|fbcon_set_bitops
id|EXPORT_SYMBOL
c_func
(paren
id|fbcon_set_bitops
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Antonino Daplas &lt;adaplas@pol.net&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Bit Blitting Operation&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
