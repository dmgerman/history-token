multiline_comment|/*&n; *  ATI Mach64 CT/VT/GT/LT Cursor Support&n; */
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/fb.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;video/fbcon.h&gt;
macro_line|#ifdef __sparc__
macro_line|#include &lt;asm/pbm.h&gt;
macro_line|#include &lt;asm/fbio.h&gt;
macro_line|#endif
macro_line|#include &lt;video/mach64.h&gt;
macro_line|#include &quot;atyfb.h&quot;
DECL|macro|DEFAULT_CURSOR_BLINK_RATE
mdefine_line|#define DEFAULT_CURSOR_BLINK_RATE&t;(20)
DECL|macro|CURSOR_DRAW_DELAY
mdefine_line|#define CURSOR_DRAW_DELAY&t;&t;(2)
multiline_comment|/*&n;     *  Hardware Cursor support.&n;     */
DECL|variable|cursor_pixel_map
r_static
r_const
id|u8
id|cursor_pixel_map
(braket
l_int|2
)braket
op_assign
(brace
l_int|0
comma
l_int|15
)brace
suffix:semicolon
DECL|variable|cursor_color_map
r_static
r_const
id|u8
id|cursor_color_map
(braket
l_int|2
)braket
op_assign
(brace
l_int|0
comma
l_int|0xff
)brace
suffix:semicolon
DECL|variable|cursor_bits_lookup
r_static
r_const
id|u8
id|cursor_bits_lookup
(braket
l_int|16
)braket
op_assign
(brace
l_int|0x00
comma
l_int|0x40
comma
l_int|0x10
comma
l_int|0x50
comma
l_int|0x04
comma
l_int|0x44
comma
l_int|0x14
comma
l_int|0x54
comma
l_int|0x01
comma
l_int|0x41
comma
l_int|0x11
comma
l_int|0x51
comma
l_int|0x05
comma
l_int|0x45
comma
l_int|0x15
comma
l_int|0x55
)brace
suffix:semicolon
DECL|variable|cursor_mask_lookup
r_static
r_const
id|u8
id|cursor_mask_lookup
(braket
l_int|16
)braket
op_assign
(brace
l_int|0xaa
comma
l_int|0x2a
comma
l_int|0x8a
comma
l_int|0x0a
comma
l_int|0xa2
comma
l_int|0x22
comma
l_int|0x82
comma
l_int|0x02
comma
l_int|0xa8
comma
l_int|0x28
comma
l_int|0x88
comma
l_int|0x08
comma
l_int|0xa0
comma
l_int|0x20
comma
l_int|0x80
comma
l_int|0x00
)brace
suffix:semicolon
DECL|function|aty_set_cursor_color
r_void
id|aty_set_cursor_color
c_func
(paren
r_struct
id|fb_info
op_star
id|info
)paren
(brace
r_struct
id|atyfb_par
op_star
id|par
op_assign
(paren
r_struct
id|atyfb_par
op_star
)paren
id|info-&gt;par
suffix:semicolon
r_struct
id|aty_cursor
op_star
id|c
op_assign
id|par-&gt;cursor
suffix:semicolon
r_const
id|u8
op_star
id|pixel
op_assign
id|cursor_pixel_map
suffix:semicolon
multiline_comment|/* ++Geert: Why?? */
r_const
id|u8
op_star
id|red
op_assign
id|cursor_color_map
suffix:semicolon
r_const
id|u8
op_star
id|green
op_assign
id|cursor_color_map
suffix:semicolon
r_const
id|u8
op_star
id|blue
op_assign
id|cursor_color_map
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|c
)paren
r_return
suffix:semicolon
macro_line|#ifdef __sparc__
r_if
c_cond
(paren
id|par-&gt;mmaped
op_logical_and
(paren
op_logical_neg
id|info-&gt;display_fg
op_logical_or
id|info-&gt;display_fg-&gt;vc_num
op_eq
id|par-&gt;vtconsole
)paren
)paren
r_return
suffix:semicolon
macro_line|#endif
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|2
suffix:semicolon
id|i
op_increment
)paren
(brace
id|c-&gt;color
(braket
id|i
)braket
op_assign
(paren
id|u32
)paren
id|red
(braket
id|i
)braket
op_lshift
l_int|24
suffix:semicolon
id|c-&gt;color
(braket
id|i
)braket
op_or_assign
(paren
id|u32
)paren
id|green
(braket
id|i
)braket
op_lshift
l_int|16
suffix:semicolon
id|c-&gt;color
(braket
id|i
)braket
op_or_assign
(paren
id|u32
)paren
id|blue
(braket
id|i
)braket
op_lshift
l_int|8
suffix:semicolon
id|c-&gt;color
(braket
id|i
)braket
op_or_assign
(paren
id|u32
)paren
id|pixel
(braket
id|i
)braket
suffix:semicolon
)brace
id|wait_for_fifo
c_func
(paren
l_int|2
comma
id|par
)paren
suffix:semicolon
id|aty_st_le32
c_func
(paren
id|CUR_CLR0
comma
id|c-&gt;color
(braket
l_int|0
)braket
comma
id|par
)paren
suffix:semicolon
id|aty_st_le32
c_func
(paren
id|CUR_CLR1
comma
id|c-&gt;color
(braket
l_int|1
)braket
comma
id|par
)paren
suffix:semicolon
)brace
DECL|function|aty_set_cursor_shape
r_void
id|aty_set_cursor_shape
c_func
(paren
r_struct
id|fb_info
op_star
id|info
)paren
(brace
r_struct
id|atyfb_par
op_star
id|par
op_assign
(paren
r_struct
id|atyfb_par
op_star
)paren
id|info-&gt;par
suffix:semicolon
r_struct
id|aty_cursor
op_star
id|c
op_assign
id|par-&gt;cursor
suffix:semicolon
id|u8
op_star
id|ram
comma
id|m
comma
id|b
suffix:semicolon
r_int
id|x
comma
id|y
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|c
)paren
r_return
suffix:semicolon
macro_line|#ifdef __sparc__
r_if
c_cond
(paren
id|par-&gt;mmaped
op_logical_and
(paren
op_logical_neg
id|info-&gt;display_fg
op_logical_or
id|info-&gt;display_fg-&gt;vc_num
op_eq
id|par-&gt;vtconsole
)paren
)paren
r_return
suffix:semicolon
macro_line|#endif
id|ram
op_assign
id|c-&gt;ram
suffix:semicolon
r_for
c_loop
(paren
id|y
op_assign
l_int|0
suffix:semicolon
id|y
OL
id|c-&gt;size.y
suffix:semicolon
id|y
op_increment
)paren
(brace
r_for
c_loop
(paren
id|x
op_assign
l_int|0
suffix:semicolon
id|x
OL
id|c-&gt;size.x
op_rshift
l_int|2
suffix:semicolon
id|x
op_increment
)paren
(brace
id|m
op_assign
id|c-&gt;mask
(braket
id|x
)braket
(braket
id|y
)braket
suffix:semicolon
id|b
op_assign
id|c-&gt;bits
(braket
id|x
)braket
(braket
id|y
)braket
suffix:semicolon
id|fb_writeb
c_func
(paren
id|cursor_mask_lookup
(braket
id|m
op_rshift
l_int|4
)braket
op_or
id|cursor_bits_lookup
(braket
(paren
id|b
op_amp
id|m
)paren
op_rshift
l_int|4
)braket
comma
id|ram
op_increment
)paren
suffix:semicolon
id|fb_writeb
c_func
(paren
id|cursor_mask_lookup
(braket
id|m
op_amp
l_int|0x0f
)braket
op_or
id|cursor_bits_lookup
(braket
(paren
id|b
op_amp
id|m
)paren
op_amp
l_int|0x0f
)braket
comma
id|ram
op_increment
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
suffix:semicolon
id|x
OL
l_int|8
suffix:semicolon
id|x
op_increment
)paren
(brace
id|fb_writeb
c_func
(paren
l_int|0xaa
comma
id|ram
op_increment
)paren
suffix:semicolon
id|fb_writeb
c_func
(paren
l_int|0xaa
comma
id|ram
op_increment
)paren
suffix:semicolon
)brace
)brace
id|fb_memset
c_func
(paren
id|ram
comma
l_int|0xaa
comma
(paren
l_int|64
op_minus
id|c-&gt;size.y
)paren
op_star
l_int|16
)paren
suffix:semicolon
)brace
DECL|function|aty_set_cursor
r_static
r_void
id|aty_set_cursor
c_func
(paren
r_struct
id|fb_info
op_star
id|info
comma
r_int
id|on
)paren
(brace
r_struct
id|atyfb_par
op_star
id|par
op_assign
(paren
r_struct
id|atyfb_par
op_star
)paren
id|info-&gt;par
suffix:semicolon
r_struct
id|aty_cursor
op_star
id|c
op_assign
id|par-&gt;cursor
suffix:semicolon
id|u16
id|xoff
comma
id|yoff
suffix:semicolon
r_int
id|x
comma
id|y
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|c
)paren
r_return
suffix:semicolon
macro_line|#ifdef __sparc__
r_if
c_cond
(paren
id|par-&gt;mmaped
op_logical_and
(paren
op_logical_neg
id|info-&gt;display_fg
op_logical_or
id|info-&gt;display_fg-&gt;vc_num
op_eq
id|par-&gt;vtconsole
)paren
)paren
r_return
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|on
)paren
(brace
id|x
op_assign
id|c-&gt;pos.x
op_minus
id|c-&gt;hot.x
op_minus
id|info-&gt;var.xoffset
suffix:semicolon
r_if
c_cond
(paren
id|x
OL
l_int|0
)paren
(brace
id|xoff
op_assign
op_minus
id|x
suffix:semicolon
id|x
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|xoff
op_assign
l_int|0
suffix:semicolon
)brace
id|y
op_assign
id|c-&gt;pos.y
op_minus
id|c-&gt;hot.y
op_minus
id|info-&gt;var.yoffset
suffix:semicolon
r_if
c_cond
(paren
id|y
OL
l_int|0
)paren
(brace
id|yoff
op_assign
op_minus
id|y
suffix:semicolon
id|y
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|yoff
op_assign
l_int|0
suffix:semicolon
)brace
id|wait_for_fifo
c_func
(paren
l_int|4
comma
id|par
)paren
suffix:semicolon
id|aty_st_le32
c_func
(paren
id|CUR_OFFSET
comma
(paren
id|c-&gt;offset
op_rshift
l_int|3
)paren
op_plus
(paren
id|yoff
op_lshift
l_int|1
)paren
comma
id|par
)paren
suffix:semicolon
id|aty_st_le32
c_func
(paren
id|CUR_HORZ_VERT_OFF
comma
(paren
(paren
id|u32
)paren
(paren
l_int|64
op_minus
id|c-&gt;size.y
op_plus
id|yoff
)paren
op_lshift
l_int|16
)paren
op_or
id|xoff
comma
id|par
)paren
suffix:semicolon
id|aty_st_le32
c_func
(paren
id|CUR_HORZ_VERT_POSN
comma
(paren
(paren
id|u32
)paren
id|y
op_lshift
l_int|16
)paren
op_or
id|x
comma
id|par
)paren
suffix:semicolon
id|aty_st_le32
c_func
(paren
id|GEN_TEST_CNTL
comma
id|aty_ld_le32
c_func
(paren
id|GEN_TEST_CNTL
comma
id|par
)paren
op_or
id|HWCURSOR_ENABLE
comma
id|par
)paren
suffix:semicolon
)brace
r_else
(brace
id|wait_for_fifo
c_func
(paren
l_int|1
comma
id|par
)paren
suffix:semicolon
id|aty_st_le32
c_func
(paren
id|GEN_TEST_CNTL
comma
id|aty_ld_le32
c_func
(paren
id|GEN_TEST_CNTL
comma
id|par
)paren
op_amp
op_complement
id|HWCURSOR_ENABLE
comma
id|par
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|par-&gt;blitter_may_be_busy
)paren
id|wait_for_idle
c_func
(paren
id|par
)paren
suffix:semicolon
)brace
DECL|function|aty_cursor_timer_handler
r_static
r_void
id|aty_cursor_timer_handler
c_func
(paren
r_int
r_int
id|dev_addr
)paren
(brace
r_struct
id|fb_info
op_star
id|info
op_assign
(paren
r_struct
id|fb_info
op_star
)paren
id|dev_addr
suffix:semicolon
r_struct
id|atyfb_par
op_star
id|par
op_assign
(paren
r_struct
id|atyfb_par
op_star
)paren
id|info-&gt;par
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|par-&gt;cursor
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|par-&gt;cursor-&gt;enable
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|par-&gt;cursor-&gt;vbl_cnt
op_logical_and
op_decrement
id|par-&gt;cursor-&gt;vbl_cnt
op_eq
l_int|0
)paren
(brace
id|par-&gt;cursor-&gt;on
op_xor_assign
l_int|1
suffix:semicolon
id|aty_set_cursor
c_func
(paren
id|info
comma
id|par-&gt;cursor-&gt;on
)paren
suffix:semicolon
id|par-&gt;cursor-&gt;vbl_cnt
op_assign
id|par-&gt;cursor-&gt;blink_rate
suffix:semicolon
)brace
id|out
suffix:colon
id|par-&gt;cursor-&gt;timer-&gt;expires
op_assign
id|jiffies
op_plus
(paren
id|HZ
op_div
l_int|50
)paren
suffix:semicolon
id|add_timer
c_func
(paren
id|par-&gt;cursor-&gt;timer
)paren
suffix:semicolon
)brace
DECL|function|atyfb_cursor
r_void
id|atyfb_cursor
c_func
(paren
r_struct
id|display
op_star
id|p
comma
r_int
id|mode
comma
r_int
id|x
comma
r_int
id|y
)paren
(brace
r_struct
id|fb_info
op_star
id|info
op_assign
id|p-&gt;fb_info
suffix:semicolon
r_struct
id|atyfb_par
op_star
id|par
op_assign
(paren
r_struct
id|atyfb_par
op_star
)paren
id|info-&gt;par
suffix:semicolon
r_struct
id|aty_cursor
op_star
id|c
op_assign
id|par-&gt;cursor
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|c
)paren
r_return
suffix:semicolon
macro_line|#ifdef __sparc__
r_if
c_cond
(paren
id|par-&gt;mmaped
op_logical_and
(paren
op_logical_neg
id|info-&gt;display_fg
op_logical_or
id|info-&gt;display_fg-&gt;vc_num
op_eq
id|par-&gt;vtconsole
)paren
)paren
r_return
suffix:semicolon
macro_line|#endif
id|x
op_mul_assign
id|fontwidth
c_func
(paren
id|p
)paren
suffix:semicolon
id|y
op_mul_assign
id|fontheight
c_func
(paren
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c-&gt;pos.x
op_eq
id|x
op_logical_and
id|c-&gt;pos.y
op_eq
id|y
op_logical_and
(paren
id|mode
op_eq
id|CM_ERASE
)paren
op_eq
op_logical_neg
id|c-&gt;enable
)paren
r_return
suffix:semicolon
id|c-&gt;enable
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|c-&gt;on
)paren
id|aty_set_cursor
c_func
(paren
id|info
comma
l_int|0
)paren
suffix:semicolon
id|c-&gt;pos.x
op_assign
id|x
suffix:semicolon
id|c-&gt;pos.y
op_assign
id|y
suffix:semicolon
r_switch
c_cond
(paren
id|mode
)paren
(brace
r_case
id|CM_ERASE
suffix:colon
id|c-&gt;on
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
r_if
c_cond
(paren
id|c-&gt;on
)paren
id|aty_set_cursor
c_func
(paren
id|info
comma
l_int|1
)paren
suffix:semicolon
r_else
id|c-&gt;vbl_cnt
op_assign
id|CURSOR_DRAW_DELAY
suffix:semicolon
id|c-&gt;enable
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
DECL|function|aty_init_cursor
r_struct
id|aty_cursor
op_star
id|__init
id|aty_init_cursor
c_func
(paren
r_struct
id|fb_info
op_star
id|info
)paren
(brace
r_struct
id|aty_cursor
op_star
id|cursor
suffix:semicolon
r_int
r_int
id|addr
suffix:semicolon
id|cursor
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|aty_cursor
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cursor
)paren
r_return
l_int|0
suffix:semicolon
id|memset
c_func
(paren
id|cursor
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|cursor
)paren
)paren
suffix:semicolon
id|cursor-&gt;timer
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|cursor-&gt;timer
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cursor-&gt;timer
)paren
(brace
id|kfree
c_func
(paren
id|cursor
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|memset
c_func
(paren
id|cursor-&gt;timer
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|cursor-&gt;timer
)paren
)paren
suffix:semicolon
id|cursor-&gt;blink_rate
op_assign
id|DEFAULT_CURSOR_BLINK_RATE
suffix:semicolon
id|info-&gt;fix.smem_len
op_sub_assign
id|PAGE_SIZE
suffix:semicolon
id|cursor-&gt;offset
op_assign
id|info-&gt;fix.smem_len
suffix:semicolon
macro_line|#ifdef __sparc__
id|addr
op_assign
id|info-&gt;screen_base
op_minus
l_int|0x800000
op_plus
id|cursor-&gt;offset
suffix:semicolon
id|cursor-&gt;ram
op_assign
(paren
id|u8
op_star
)paren
id|addr
suffix:semicolon
macro_line|#else
macro_line|#ifdef __BIG_ENDIAN
id|addr
op_assign
id|info-&gt;fix.smem_start
op_minus
l_int|0x800000
op_plus
id|cursor-&gt;offset
suffix:semicolon
id|cursor-&gt;ram
op_assign
(paren
id|u8
op_star
)paren
id|ioremap
c_func
(paren
id|addr
comma
l_int|1024
)paren
suffix:semicolon
macro_line|#else
id|addr
op_assign
(paren
r_int
r_int
)paren
id|info-&gt;screen_base
op_plus
id|cursor-&gt;offset
suffix:semicolon
id|cursor-&gt;ram
op_assign
(paren
id|u8
op_star
)paren
id|addr
suffix:semicolon
macro_line|#endif
macro_line|#endif
r_if
c_cond
(paren
op_logical_neg
id|cursor-&gt;ram
)paren
(brace
id|kfree
c_func
(paren
id|cursor
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|init_timer
c_func
(paren
id|cursor-&gt;timer
)paren
suffix:semicolon
id|cursor-&gt;timer-&gt;expires
op_assign
id|jiffies
op_plus
(paren
id|HZ
op_div
l_int|50
)paren
suffix:semicolon
id|cursor-&gt;timer-&gt;data
op_assign
(paren
r_int
r_int
)paren
id|info
suffix:semicolon
id|cursor-&gt;timer-&gt;function
op_assign
id|aty_cursor_timer_handler
suffix:semicolon
id|add_timer
c_func
(paren
id|cursor-&gt;timer
)paren
suffix:semicolon
r_return
id|cursor
suffix:semicolon
)brace
DECL|function|atyfb_set_font
r_int
id|atyfb_set_font
c_func
(paren
r_struct
id|display
op_star
id|d
comma
r_int
id|width
comma
r_int
id|height
)paren
(brace
r_struct
id|fb_info
op_star
id|info
op_assign
id|d-&gt;fb_info
suffix:semicolon
r_struct
id|atyfb_par
op_star
id|par
op_assign
(paren
r_struct
id|atyfb_par
op_star
)paren
id|info-&gt;par
suffix:semicolon
r_struct
id|aty_cursor
op_star
id|c
op_assign
id|par-&gt;cursor
suffix:semicolon
r_int
id|i
comma
id|j
suffix:semicolon
r_if
c_cond
(paren
id|c
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|width
op_logical_or
op_logical_neg
id|height
)paren
(brace
id|width
op_assign
l_int|8
suffix:semicolon
id|height
op_assign
l_int|16
suffix:semicolon
)brace
id|c-&gt;hot.x
op_assign
l_int|0
suffix:semicolon
id|c-&gt;hot.y
op_assign
l_int|0
suffix:semicolon
id|c-&gt;size.x
op_assign
id|width
suffix:semicolon
id|c-&gt;size.y
op_assign
id|height
suffix:semicolon
id|memset
c_func
(paren
id|c-&gt;bits
comma
l_int|0xff
comma
r_sizeof
(paren
id|c-&gt;bits
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
id|c-&gt;mask
comma
l_int|0
comma
r_sizeof
(paren
id|c-&gt;mask
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
comma
id|j
op_assign
id|width
suffix:semicolon
id|j
op_ge
l_int|0
suffix:semicolon
id|j
op_sub_assign
l_int|8
comma
id|i
op_increment
)paren
(brace
id|c-&gt;mask
(braket
id|i
)braket
(braket
id|height
op_minus
l_int|2
)braket
op_assign
(paren
id|j
op_ge
l_int|8
)paren
ques
c_cond
l_int|0xff
suffix:colon
(paren
l_int|0xff
op_lshift
(paren
l_int|8
op_minus
id|j
)paren
)paren
suffix:semicolon
id|c-&gt;mask
(braket
id|i
)braket
(braket
id|height
op_minus
l_int|1
)braket
op_assign
(paren
id|j
op_ge
l_int|8
)paren
ques
c_cond
l_int|0xff
suffix:colon
(paren
l_int|0xff
op_lshift
(paren
l_int|8
op_minus
id|j
)paren
)paren
suffix:semicolon
)brace
id|aty_set_cursor_color
c_func
(paren
id|info
)paren
suffix:semicolon
id|aty_set_cursor_shape
c_func
(paren
id|info
)paren
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
eof
