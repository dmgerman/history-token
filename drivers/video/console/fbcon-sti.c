multiline_comment|/*&n; * linux/drivers/video/fbcon-sti.c -- Low level frame buffer&n; *  &t;operations for generic HP video boards using STI (standard&n; *  &t;text interface) firmware&n; *&n; *  Based on linux/drivers/video/fbcon-artist.c&n; *&t;Created 5 Apr 1997 by Geert Uytterhoeven&n; *&t;Copyright (C) 2000 Philipp Rumpf &lt;prumpf@tux.org&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file COPYING in the main directory of this archive for&n; * more details.  */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/fb.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;asm/gsc.h&gt;&t;&t;/* for gsc_read/write */
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;video/fbcon.h&gt;
macro_line|#include &lt;video/fbcon-mfb.h&gt;
macro_line|#include &quot;../sticore.h&quot;
r_static
r_inline
id|u32
DECL|function|ram2log
id|ram2log
c_func
(paren
r_void
op_star
id|addr
)paren
(brace
r_return
(paren
r_int
r_int
)paren
id|addr
suffix:semicolon
)brace
multiline_comment|/* All those functions need better names. */
r_static
r_void
DECL|function|memcpy_fromhp_tohp
id|memcpy_fromhp_tohp
c_func
(paren
r_void
op_star
id|dest
comma
r_void
op_star
id|src
comma
r_int
id|count
)paren
(brace
r_int
r_int
id|d
op_assign
id|ram2log
c_func
(paren
id|dest
)paren
suffix:semicolon
r_int
r_int
id|s
op_assign
id|ram2log
c_func
(paren
id|src
)paren
suffix:semicolon
id|count
op_add_assign
l_int|3
suffix:semicolon
id|count
op_and_assign
op_complement
l_int|3
suffix:semicolon
multiline_comment|/* XXX */
r_while
c_loop
(paren
id|count
)paren
(brace
id|count
op_decrement
suffix:semicolon
id|gsc_writel
c_func
(paren
op_complement
id|gsc_readl
c_func
(paren
id|s
)paren
comma
id|d
)paren
suffix:semicolon
id|d
op_add_assign
l_int|32
op_star
l_int|4
suffix:semicolon
id|s
op_add_assign
l_int|32
op_star
l_int|4
suffix:semicolon
)brace
)brace
r_static
r_void
DECL|function|memset_tohp
id|memset_tohp
c_func
(paren
r_void
op_star
id|dest
comma
id|u32
id|word
comma
r_int
id|count
)paren
(brace
r_int
r_int
id|d
op_assign
id|ram2log
c_func
(paren
id|dest
)paren
suffix:semicolon
id|count
op_add_assign
l_int|3
suffix:semicolon
id|count
op_and_assign
op_complement
l_int|3
suffix:semicolon
r_while
c_loop
(paren
id|count
)paren
(brace
id|count
op_decrement
suffix:semicolon
id|gsc_writel
c_func
(paren
id|word
comma
id|d
)paren
suffix:semicolon
id|d
op_add_assign
l_int|32
suffix:semicolon
)brace
)brace
r_static
id|u8
DECL|function|readb_hp
id|readb_hp
c_func
(paren
r_void
op_star
id|src
)paren
(brace
r_int
r_int
id|s
op_assign
id|ram2log
c_func
(paren
id|src
)paren
suffix:semicolon
r_return
op_complement
id|gsc_readb
c_func
(paren
id|s
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|writeb_hp
id|writeb_hp
c_func
(paren
id|u8
id|b
comma
r_void
op_star
id|dst
)paren
(brace
r_int
r_int
id|d
op_assign
id|ram2log
c_func
(paren
id|dst
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|d
op_amp
l_int|0xf0000000
)paren
op_ne
l_int|0xf0000000
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;writeb_hp %02x %p (%08lx) (%p)&bslash;n&quot;
comma
id|b
comma
id|dst
comma
id|d
comma
id|__builtin_return_address
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|gsc_writeb
c_func
(paren
id|b
comma
id|d
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|fbcon_sti_setup
id|fbcon_sti_setup
c_func
(paren
r_struct
id|display
op_star
id|p
)paren
(brace
multiline_comment|/* in kernel 2.5 the value of sadly line_length disapeared */
r_if
c_cond
(paren
id|p-&gt;var.xres_virtual
multiline_comment|/*line_length*/
)paren
id|p-&gt;next_line
op_assign
id|p-&gt;var.xres_virtual
op_rshift
l_int|3
suffix:semicolon
r_else
id|p-&gt;next_line
op_assign
l_int|2048
suffix:semicolon
multiline_comment|/* default STI value */
id|p-&gt;next_plane
op_assign
l_int|0
suffix:semicolon
)brace
r_static
r_void
DECL|function|fbcon_sti_bmove
id|fbcon_sti_bmove
c_func
(paren
r_struct
id|display
op_star
id|p
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
macro_line|#if 0 /* Unfortunately, still broken */
id|sti_bmove
c_func
(paren
id|default_sti
multiline_comment|/* FIXME */
comma
id|sy
comma
id|sx
comma
id|dy
comma
id|dx
comma
id|height
comma
id|width
)paren
suffix:semicolon
macro_line|#else
id|u8
op_star
id|src
comma
op_star
id|dest
suffix:semicolon
id|u_int
id|rows
suffix:semicolon
r_if
c_cond
(paren
id|sx
op_eq
l_int|0
op_logical_and
id|dx
op_eq
l_int|0
op_logical_and
id|width
op_eq
id|p-&gt;next_line
)paren
(brace
id|src
op_assign
id|p-&gt;fb_info-&gt;screen_base
op_plus
id|sy
op_star
id|fontheight
c_func
(paren
id|p
)paren
op_star
id|width
suffix:semicolon
id|dest
op_assign
id|p-&gt;fb_info-&gt;screen_base
op_plus
id|dy
op_star
id|fontheight
c_func
(paren
id|p
)paren
op_star
id|width
suffix:semicolon
id|memcpy_fromhp_tohp
c_func
(paren
id|dest
comma
id|src
comma
id|height
op_star
id|fontheight
c_func
(paren
id|p
)paren
op_star
id|width
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|dy
op_le
id|sy
)paren
(brace
id|src
op_assign
id|p-&gt;fb_info-&gt;screen_base
op_plus
id|sy
op_star
id|fontheight
c_func
(paren
id|p
)paren
op_star
id|p-&gt;next_line
op_plus
id|sx
suffix:semicolon
id|dest
op_assign
id|p-&gt;fb_info-&gt;screen_base
op_plus
id|dy
op_star
id|fontheight
c_func
(paren
id|p
)paren
op_star
id|p-&gt;next_line
op_plus
id|dx
suffix:semicolon
r_for
c_loop
(paren
id|rows
op_assign
id|height
op_star
id|fontheight
c_func
(paren
id|p
)paren
suffix:semicolon
id|rows
op_decrement
suffix:semicolon
)paren
(brace
id|memcpy_fromhp_tohp
c_func
(paren
id|dest
comma
id|src
comma
id|width
)paren
suffix:semicolon
id|src
op_add_assign
id|p-&gt;next_line
suffix:semicolon
id|dest
op_add_assign
id|p-&gt;next_line
suffix:semicolon
)brace
)brace
r_else
(brace
id|src
op_assign
id|p-&gt;fb_info-&gt;screen_base
op_plus
(paren
(paren
id|sy
op_plus
id|height
)paren
op_star
id|fontheight
c_func
(paren
id|p
)paren
op_minus
l_int|1
)paren
op_star
id|p-&gt;next_line
op_plus
id|sx
suffix:semicolon
id|dest
op_assign
id|p-&gt;fb_info-&gt;screen_base
op_plus
(paren
(paren
id|dy
op_plus
id|height
)paren
op_star
id|fontheight
c_func
(paren
id|p
)paren
op_minus
l_int|1
)paren
op_star
id|p-&gt;next_line
op_plus
id|dx
suffix:semicolon
r_for
c_loop
(paren
id|rows
op_assign
id|height
op_star
id|fontheight
c_func
(paren
id|p
)paren
suffix:semicolon
id|rows
op_decrement
suffix:semicolon
)paren
(brace
id|memcpy_fromhp_tohp
c_func
(paren
id|dest
comma
id|src
comma
id|width
)paren
suffix:semicolon
id|src
op_sub_assign
id|p-&gt;next_line
suffix:semicolon
id|dest
op_sub_assign
id|p-&gt;next_line
suffix:semicolon
)brace
)brace
macro_line|#endif
)brace
r_static
r_void
DECL|function|fbcon_sti_clear
id|fbcon_sti_clear
c_func
(paren
r_struct
id|vc_data
op_star
id|conp
comma
r_struct
id|display
op_star
id|p
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
id|u8
op_star
id|dest
suffix:semicolon
id|u_int
id|rows
suffix:semicolon
r_int
id|inverse
op_assign
id|conp
ques
c_cond
id|attr_reverse
c_func
(paren
id|p
comma
id|conp-&gt;vc_video_erase_char
)paren
suffix:colon
l_int|0
suffix:semicolon
id|dest
op_assign
id|p-&gt;fb_info-&gt;screen_base
op_plus
id|sy
op_star
id|fontheight
c_func
(paren
id|p
)paren
op_star
id|p-&gt;next_line
op_plus
id|sx
suffix:semicolon
r_if
c_cond
(paren
id|sx
op_eq
l_int|0
op_logical_and
id|width
op_eq
id|p-&gt;next_line
)paren
(brace
r_if
c_cond
(paren
id|inverse
)paren
id|memset_tohp
c_func
(paren
id|dest
comma
op_complement
l_int|0
comma
id|height
op_star
id|fontheight
c_func
(paren
id|p
)paren
op_star
id|width
)paren
suffix:semicolon
r_else
id|memset_tohp
c_func
(paren
id|dest
comma
l_int|0
comma
id|height
op_star
id|fontheight
c_func
(paren
id|p
)paren
op_star
id|width
)paren
suffix:semicolon
)brace
r_else
r_for
c_loop
(paren
id|rows
op_assign
id|height
op_star
id|fontheight
c_func
(paren
id|p
)paren
suffix:semicolon
id|rows
op_decrement
suffix:semicolon
id|dest
op_add_assign
id|p-&gt;next_line
)paren
r_if
c_cond
(paren
id|inverse
)paren
id|memset_tohp
c_func
(paren
id|dest
comma
l_int|0xffffffff
comma
id|width
)paren
suffix:semicolon
r_else
id|memset_tohp
c_func
(paren
id|dest
comma
l_int|0x00000000
comma
id|width
)paren
suffix:semicolon
)brace
DECL|function|fbcon_sti_putc
r_static
r_void
id|fbcon_sti_putc
c_func
(paren
r_struct
id|vc_data
op_star
id|conp
comma
r_struct
id|display
op_star
id|p
comma
r_int
id|c
comma
r_int
id|yy
comma
r_int
id|xx
)paren
(brace
id|u8
op_star
id|dest
comma
op_star
id|cdat
suffix:semicolon
id|u_int
id|rows
comma
id|bold
comma
id|revs
comma
id|underl
suffix:semicolon
id|u8
id|d
suffix:semicolon
id|dest
op_assign
id|p-&gt;fb_info-&gt;screen_base
op_plus
id|yy
op_star
id|fontheight
c_func
(paren
id|p
)paren
op_star
id|p-&gt;next_line
op_plus
id|xx
suffix:semicolon
id|cdat
op_assign
id|p-&gt;fontdata
op_plus
(paren
id|c
op_amp
id|p-&gt;charmask
)paren
op_star
id|fontheight
c_func
(paren
id|p
)paren
suffix:semicolon
id|bold
op_assign
id|attr_bold
c_func
(paren
id|p
comma
id|c
)paren
suffix:semicolon
id|revs
op_assign
id|attr_reverse
c_func
(paren
id|p
comma
id|c
)paren
suffix:semicolon
id|underl
op_assign
id|attr_underline
c_func
(paren
id|p
comma
id|c
)paren
suffix:semicolon
r_for
c_loop
(paren
id|rows
op_assign
id|fontheight
c_func
(paren
id|p
)paren
suffix:semicolon
id|rows
op_decrement
suffix:semicolon
id|dest
op_add_assign
id|p-&gt;next_line
)paren
(brace
id|d
op_assign
op_star
id|cdat
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|underl
op_logical_and
op_logical_neg
id|rows
)paren
id|d
op_assign
l_int|0xff
suffix:semicolon
r_else
r_if
c_cond
(paren
id|bold
)paren
id|d
op_or_assign
id|d
op_rshift
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|revs
)paren
id|d
op_assign
op_complement
id|d
suffix:semicolon
id|writeb_hp
(paren
id|d
comma
id|dest
)paren
suffix:semicolon
)brace
)brace
DECL|function|fbcon_sti_putcs
r_static
r_void
id|fbcon_sti_putcs
c_func
(paren
r_struct
id|vc_data
op_star
id|conp
comma
r_struct
id|display
op_star
id|p
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
)paren
(brace
id|u8
op_star
id|dest
comma
op_star
id|dest0
comma
op_star
id|cdat
suffix:semicolon
id|u_int
id|rows
comma
id|bold
comma
id|revs
comma
id|underl
suffix:semicolon
id|u8
id|d
suffix:semicolon
id|u16
id|c
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
r_int
)paren
id|xx
OG
l_int|200
)paren
op_logical_or
(paren
(paren
r_int
)paren
id|yy
OG
l_int|200
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;refusing to putcs %p %p %p %d %d %d (%p)&bslash;n&quot;
comma
id|conp
comma
id|p
comma
id|s
comma
id|count
comma
id|yy
comma
id|xx
comma
id|__builtin_return_address
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|dest0
op_assign
id|p-&gt;fb_info-&gt;screen_base
op_plus
id|yy
op_star
id|fontheight
c_func
(paren
id|p
)paren
op_star
id|p-&gt;next_line
op_plus
id|xx
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|u32
)paren
id|dest0
op_amp
l_int|0xf0000000
)paren
op_ne
l_int|0xf0000000
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;refusing to putcs %p %p %p %d %d %d (%p) %p = %p + %d * %d * %ld + %d&bslash;n&quot;
comma
id|conp
comma
id|p
comma
id|s
comma
id|count
comma
id|yy
comma
id|xx
comma
id|__builtin_return_address
c_func
(paren
l_int|0
)paren
comma
id|dest0
comma
id|p-&gt;fb_info-&gt;screen_base
comma
id|yy
comma
id|fontheight
c_func
(paren
id|p
)paren
comma
id|p-&gt;next_line
comma
id|xx
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|c
op_assign
id|scr_readw
c_func
(paren
id|s
)paren
suffix:semicolon
id|bold
op_assign
id|attr_bold
c_func
(paren
id|p
comma
id|c
)paren
suffix:semicolon
id|revs
op_assign
id|attr_reverse
c_func
(paren
id|p
comma
id|c
)paren
suffix:semicolon
id|underl
op_assign
id|attr_underline
c_func
(paren
id|p
comma
id|c
)paren
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
)paren
(brace
id|c
op_assign
id|scr_readw
c_func
(paren
id|s
op_increment
)paren
op_amp
id|p-&gt;charmask
suffix:semicolon
id|dest
op_assign
id|dest0
op_increment
suffix:semicolon
id|cdat
op_assign
id|p-&gt;fontdata
op_plus
id|c
op_star
id|fontheight
c_func
(paren
id|p
)paren
suffix:semicolon
r_for
c_loop
(paren
id|rows
op_assign
id|fontheight
c_func
(paren
id|p
)paren
suffix:semicolon
id|rows
op_decrement
suffix:semicolon
id|dest
op_add_assign
id|p-&gt;next_line
)paren
(brace
id|d
op_assign
op_star
id|cdat
op_increment
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_logical_and
id|underl
op_logical_and
op_logical_neg
id|rows
)paren
id|d
op_assign
l_int|0xff
suffix:semicolon
r_else
r_if
c_cond
(paren
l_int|0
op_logical_and
id|bold
)paren
id|d
op_or_assign
id|d
op_rshift
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|revs
)paren
id|d
op_assign
op_complement
id|d
suffix:semicolon
id|writeb_hp
(paren
id|d
comma
id|dest
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|function|fbcon_sti_revc
r_static
r_void
id|fbcon_sti_revc
c_func
(paren
r_struct
id|display
op_star
id|p
comma
r_int
id|xx
comma
r_int
id|yy
)paren
(brace
id|u8
op_star
id|dest
comma
id|d
suffix:semicolon
id|u_int
id|rows
suffix:semicolon
id|dest
op_assign
id|p-&gt;fb_info-&gt;screen_base
op_plus
id|yy
op_star
id|fontheight
c_func
(paren
id|p
)paren
op_star
id|p-&gt;next_line
op_plus
id|xx
suffix:semicolon
r_for
c_loop
(paren
id|rows
op_assign
id|fontheight
c_func
(paren
id|p
)paren
suffix:semicolon
id|rows
op_decrement
suffix:semicolon
id|dest
op_add_assign
id|p-&gt;next_line
)paren
(brace
id|d
op_assign
id|readb_hp
c_func
(paren
id|dest
)paren
suffix:semicolon
id|writeb_hp
(paren
op_complement
id|d
comma
id|dest
)paren
suffix:semicolon
)brace
)brace
r_static
r_void
DECL|function|fbcon_sti_clear_margins
id|fbcon_sti_clear_margins
c_func
(paren
r_struct
id|vc_data
op_star
id|conp
comma
r_struct
id|display
op_star
id|p
comma
r_int
id|bottom_only
)paren
(brace
id|u8
op_star
id|dest
suffix:semicolon
r_int
id|height
comma
id|bottom
suffix:semicolon
r_int
id|inverse
op_assign
id|conp
ques
c_cond
id|attr_reverse
c_func
(paren
id|p
comma
id|conp-&gt;vc_video_erase_char
)paren
suffix:colon
l_int|0
suffix:semicolon
multiline_comment|/* XXX Need to handle right margin? */
id|height
op_assign
id|p-&gt;var.yres
op_minus
id|conp-&gt;vc_rows
op_star
id|fontheight
c_func
(paren
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|height
)paren
r_return
suffix:semicolon
id|bottom
op_assign
id|conp-&gt;vc_rows
op_plus
id|p-&gt;yscroll
suffix:semicolon
r_if
c_cond
(paren
id|bottom
op_ge
id|p-&gt;vrows
)paren
id|bottom
op_sub_assign
id|p-&gt;vrows
suffix:semicolon
id|dest
op_assign
id|p-&gt;fb_info-&gt;screen_base
op_plus
id|bottom
op_star
id|fontheight
c_func
(paren
id|p
)paren
op_star
id|p-&gt;next_line
suffix:semicolon
r_if
c_cond
(paren
id|inverse
)paren
id|memset_tohp
c_func
(paren
id|dest
comma
l_int|0xffffffff
comma
id|height
op_star
id|p-&gt;next_line
)paren
suffix:semicolon
r_else
id|memset_tohp
c_func
(paren
id|dest
comma
l_int|0x00000000
comma
id|height
op_star
id|p-&gt;next_line
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;     *  `switch&squot; for the low level operations&n;     */
DECL|variable|fbcon_sti
r_struct
id|display_switch
id|fbcon_sti
op_assign
(brace
dot
id|setup
op_assign
id|fbcon_sti_setup
comma
dot
id|bmove
op_assign
id|fbcon_sti_bmove
comma
dot
id|clear
op_assign
id|fbcon_sti_clear
comma
dot
id|putc
op_assign
id|fbcon_sti_putc
comma
dot
id|putcs
op_assign
id|fbcon_sti_putcs
comma
dot
id|revc
op_assign
id|fbcon_sti_revc
comma
dot
id|clear_margins
op_assign
id|fbcon_sti_clear_margins
comma
dot
id|fontwidthmask
op_assign
id|FONTWIDTH
c_func
(paren
l_int|8
)paren
)brace
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
