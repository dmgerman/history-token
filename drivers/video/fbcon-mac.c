multiline_comment|/*&n; *  linux/drivers/video/fbcon-mac.c -- Low level frame buffer operations for &n; *&t;&t;&t;&t;       x bpp packed pixels, font width != 8&n; *&n; *&t;Created 26 Dec 1997 by Michael Schmitz&n; *&t;Based on the old macfb.c 6x11 code by Randy Thelen&n; *&n; *&t;This driver is significantly slower than the 8bit font drivers &n; *&t;and would probably benefit from splitting into drivers for each depth.&n; *&n; *  This file is subject to the terms and conditions of the GNU General Public&n; *  License.  See the file COPYING in the main directory of this archive for&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/fb.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;video/fbcon.h&gt;
macro_line|#include &lt;video/fbcon-mac.h&gt;
multiline_comment|/*&n;     *  variable bpp packed pixels&n;     */
r_static
r_void
id|plot_pixel_mac
c_func
(paren
r_struct
id|display
op_star
id|p
comma
r_int
id|bw
comma
r_int
id|pixel_x
comma
r_int
id|pixel_y
)paren
suffix:semicolon
r_static
r_int
id|get_pixel_mac
c_func
(paren
r_struct
id|display
op_star
id|p
comma
r_int
id|pixel_x
comma
r_int
id|pixel_y
)paren
suffix:semicolon
DECL|function|fbcon_mac_setup
r_void
id|fbcon_mac_setup
c_func
(paren
r_struct
id|display
op_star
id|p
)paren
(brace
r_if
c_cond
(paren
id|p-&gt;line_length
)paren
id|p-&gt;next_line
op_assign
id|p-&gt;line_length
suffix:semicolon
r_else
id|p-&gt;next_line
op_assign
id|p-&gt;var.xres_virtual
op_rshift
l_int|3
suffix:semicolon
id|p-&gt;next_plane
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;    *    Macintosh&n;    */
DECL|macro|PIXEL_BLACK_MAC
mdefine_line|#define PIXEL_BLACK_MAC          0
DECL|macro|PIXEL_WHITE_MAC
mdefine_line|#define PIXEL_WHITE_MAC          1
DECL|macro|PIXEL_INVERT_MAC
mdefine_line|#define PIXEL_INVERT_MAC         2
DECL|function|fbcon_mac_bmove
r_void
id|fbcon_mac_bmove
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
r_int
id|i
comma
id|j
suffix:semicolon
id|u8
op_star
id|dest
comma
op_star
id|src
suffix:semicolon
r_int
id|l
comma
id|r
comma
id|t
comma
id|b
comma
id|w
comma
id|lo
comma
id|s
suffix:semicolon
r_int
id|dl
comma
id|dr
comma
id|dt
comma
id|db
comma
id|dw
comma
id|dlo
suffix:semicolon
r_int
id|move_up
suffix:semicolon
id|src
op_assign
(paren
id|u8
op_star
)paren
(paren
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
)paren
suffix:semicolon
id|dest
op_assign
(paren
id|u8
op_star
)paren
(paren
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
)paren
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
id|p-&gt;conp-&gt;vc_cols
)paren
(brace
id|s
op_assign
id|height
op_star
id|fontheight
c_func
(paren
id|p
)paren
op_star
id|p-&gt;next_line
suffix:semicolon
id|fb_memmove
c_func
(paren
id|dest
comma
id|src
comma
id|s
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|l
op_assign
id|sx
op_star
id|fontwidth
c_func
(paren
id|p
)paren
suffix:semicolon
id|r
op_assign
id|l
op_plus
id|width
op_star
id|fontwidth
c_func
(paren
id|p
)paren
suffix:semicolon
id|t
op_assign
id|sy
op_star
id|fontheight
c_func
(paren
id|p
)paren
suffix:semicolon
id|b
op_assign
id|t
op_plus
id|height
op_star
id|fontheight
c_func
(paren
id|p
)paren
suffix:semicolon
id|dl
op_assign
id|dx
op_star
id|fontwidth
c_func
(paren
id|p
)paren
suffix:semicolon
id|dr
op_assign
id|dl
op_plus
id|width
op_star
id|fontwidth
c_func
(paren
id|p
)paren
suffix:semicolon
id|dt
op_assign
id|dy
op_star
id|fontheight
c_func
(paren
id|p
)paren
suffix:semicolon
id|db
op_assign
id|dt
op_plus
id|height
op_star
id|fontheight
c_func
(paren
id|p
)paren
suffix:semicolon
multiline_comment|/* w is the # pixels between two long-aligned points, left and right */
id|w
op_assign
(paren
id|r
op_amp
op_complement
l_int|31
)paren
op_minus
(paren
(paren
id|l
op_plus
l_int|31
)paren
op_amp
op_complement
l_int|31
)paren
suffix:semicolon
id|dw
op_assign
(paren
id|dr
op_amp
op_complement
l_int|31
)paren
op_minus
(paren
(paren
id|dl
op_plus
l_int|31
)paren
op_amp
op_complement
l_int|31
)paren
suffix:semicolon
multiline_comment|/* lo is the # pixels between the left edge and a long-aligned left pixel */
id|lo
op_assign
(paren
(paren
id|l
op_plus
l_int|31
)paren
op_amp
op_complement
l_int|31
)paren
op_minus
id|l
suffix:semicolon
id|dlo
op_assign
(paren
(paren
id|dl
op_plus
l_int|31
)paren
op_amp
op_complement
l_int|31
)paren
op_minus
id|dl
suffix:semicolon
multiline_comment|/* if dx != sx then, logic has to align the left and right edges for fast moves */
r_if
c_cond
(paren
id|lo
op_ne
id|dlo
)paren
(brace
id|lo
op_assign
(paren
(paren
id|l
op_plus
l_int|7
)paren
op_amp
op_complement
l_int|7
)paren
op_minus
id|l
suffix:semicolon
id|dlo
op_assign
(paren
(paren
id|dl
op_plus
l_int|7
)paren
op_amp
op_complement
l_int|7
)paren
op_minus
id|dl
suffix:semicolon
id|w
op_assign
(paren
id|r
op_amp
op_complement
l_int|7
)paren
op_minus
(paren
(paren
id|l
op_plus
l_int|7
)paren
op_amp
op_complement
l_int|7
)paren
suffix:semicolon
id|dw
op_assign
(paren
id|dr
op_amp
op_complement
l_int|7
)paren
op_minus
(paren
(paren
id|dl
op_plus
l_int|7
)paren
op_amp
op_complement
l_int|7
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lo
op_ne
id|dlo
)paren
(brace
r_int
r_char
id|err_str
(braket
l_int|128
)braket
suffix:semicolon
r_int
r_int
id|err_buf
(braket
l_int|256
)braket
suffix:semicolon
r_int
r_int
id|cnt
comma
id|len
suffix:semicolon
id|sprintf
c_func
(paren
id|err_str
comma
l_string|&quot;ERROR: Shift algorithm: sx=%d,sy=%d,dx=%d,dy=%d,w=%d,h=%d,bpp=%d&quot;
comma
id|sx
comma
id|sy
comma
id|dx
comma
id|dy
comma
id|width
comma
id|height
comma
id|p-&gt;var.bits_per_pixel
)paren
suffix:semicolon
id|len
op_assign
id|strlen
c_func
(paren
id|err_str
)paren
suffix:semicolon
r_for
c_loop
(paren
id|cnt
op_assign
l_int|0
suffix:semicolon
id|cnt
OL
id|len
suffix:semicolon
id|cnt
op_increment
)paren
id|err_buf
(braket
id|cnt
)braket
op_assign
l_int|0x700
op_or
id|err_str
(braket
id|cnt
)braket
suffix:semicolon
id|fbcon_mac_putcs
c_func
(paren
id|p-&gt;conp
comma
id|p
comma
id|err_buf
comma
id|len
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* pause for the user */
id|printk
c_func
(paren
l_string|&quot;ERROR: shift algorithm...&bslash;n&quot;
)paren
suffix:semicolon
id|mdelay
c_func
(paren
l_int|5000
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
id|s
op_assign
l_int|0
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
id|s
op_assign
id|w
op_rshift
l_int|3
suffix:semicolon
id|src
op_add_assign
id|lo
op_rshift
l_int|3
suffix:semicolon
id|dest
op_add_assign
id|lo
op_rshift
l_int|3
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|s
op_assign
id|w
op_rshift
l_int|2
suffix:semicolon
id|src
op_add_assign
id|lo
op_rshift
l_int|2
suffix:semicolon
id|dest
op_add_assign
id|lo
op_rshift
l_int|2
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|s
op_assign
id|w
op_rshift
l_int|1
suffix:semicolon
id|src
op_add_assign
id|lo
op_rshift
l_int|1
suffix:semicolon
id|dest
op_add_assign
id|lo
op_rshift
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|8
suffix:colon
id|s
op_assign
id|w
suffix:semicolon
id|src
op_add_assign
id|lo
suffix:semicolon
id|dest
op_add_assign
id|lo
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|16
suffix:colon
id|s
op_assign
id|w
op_lshift
l_int|1
suffix:semicolon
id|src
op_add_assign
id|lo
op_lshift
l_int|1
suffix:semicolon
id|dest
op_add_assign
id|lo
op_lshift
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|32
suffix:colon
id|s
op_assign
id|w
op_lshift
l_int|2
suffix:semicolon
id|src
op_add_assign
id|lo
op_lshift
l_int|2
suffix:semicolon
id|dest
op_add_assign
id|lo
op_lshift
l_int|2
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sy
op_le
id|sx
)paren
(brace
id|i
op_assign
id|b
suffix:semicolon
id|move_up
op_assign
l_int|0
suffix:semicolon
id|src
op_add_assign
id|height
op_star
id|fontheight
c_func
(paren
id|p
)paren
suffix:semicolon
id|dest
op_add_assign
id|height
op_star
id|fontheight
c_func
(paren
id|p
)paren
suffix:semicolon
)brace
r_else
(brace
id|i
op_assign
id|t
suffix:semicolon
id|move_up
op_assign
l_int|1
suffix:semicolon
)brace
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
id|t
suffix:semicolon
id|i
OL
id|b
suffix:semicolon
id|i
op_increment
)paren
(brace
id|j
op_assign
id|l
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|j
op_amp
l_int|31
op_logical_and
id|j
OL
id|r
suffix:semicolon
id|j
op_increment
)paren
id|plot_pixel_mac
c_func
(paren
id|p
comma
id|get_pixel_mac
c_func
(paren
id|p
comma
id|j
op_plus
(paren
id|dx
op_minus
id|sx
)paren
comma
id|i
op_plus
(paren
id|dy
op_minus
id|sy
)paren
)paren
comma
id|j
comma
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
id|j
OL
id|r
)paren
(brace
id|fb_memmove
c_func
(paren
id|dest
comma
id|src
comma
id|s
)paren
suffix:semicolon
r_if
c_cond
(paren
id|move_up
)paren
(brace
id|dest
op_add_assign
id|p-&gt;next_line
suffix:semicolon
id|src
op_add_assign
id|p-&gt;next_line
suffix:semicolon
)brace
r_else
(brace
id|dest
op_sub_assign
id|p-&gt;next_line
suffix:semicolon
id|src
op_sub_assign
id|p-&gt;next_line
suffix:semicolon
)brace
id|j
op_add_assign
id|w
suffix:semicolon
)brace
r_for
c_loop
(paren
suffix:semicolon
id|j
OL
id|r
suffix:semicolon
id|j
op_increment
)paren
id|plot_pixel_mac
c_func
(paren
id|p
comma
id|get_pixel_mac
c_func
(paren
id|p
comma
id|j
op_plus
(paren
id|dx
op_minus
id|sx
)paren
comma
id|i
op_plus
(paren
id|dy
op_minus
id|sy
)paren
)paren
comma
id|j
comma
id|i
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|move_up
)paren
(brace
id|i
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ge
id|b
)paren
r_break
suffix:semicolon
)brace
r_else
(brace
id|i
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|i
OL
id|t
)paren
r_break
suffix:semicolon
)brace
)brace
)brace
DECL|function|fbcon_mac_clear
r_void
id|fbcon_mac_clear
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
r_int
id|pixel
suffix:semicolon
r_int
id|i
comma
id|j
suffix:semicolon
r_int
id|inverse
suffix:semicolon
id|u8
op_star
id|dest
suffix:semicolon
r_int
id|l
comma
id|r
comma
id|t
comma
id|b
comma
id|w
comma
id|lo
comma
id|s
suffix:semicolon
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
id|conp-&gt;vc_attr
)paren
suffix:colon
l_int|0
suffix:semicolon
id|pixel
op_assign
id|inverse
ques
c_cond
id|PIXEL_WHITE_MAC
suffix:colon
id|PIXEL_BLACK_MAC
suffix:semicolon
id|dest
op_assign
(paren
id|u8
op_star
)paren
(paren
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
)paren
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
id|p-&gt;conp-&gt;vc_cols
)paren
(brace
id|s
op_assign
id|height
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
id|fb_memclear
c_func
(paren
id|dest
comma
id|s
)paren
suffix:semicolon
r_else
id|fb_memset255
c_func
(paren
id|dest
comma
id|s
)paren
suffix:semicolon
)brace
id|l
op_assign
id|sx
op_star
id|fontwidth
c_func
(paren
id|p
)paren
suffix:semicolon
id|r
op_assign
id|l
op_plus
id|width
op_star
id|fontwidth
c_func
(paren
id|p
)paren
suffix:semicolon
id|t
op_assign
id|sy
op_star
id|fontheight
c_func
(paren
id|p
)paren
suffix:semicolon
id|b
op_assign
id|t
op_plus
id|height
op_star
id|fontheight
c_func
(paren
id|p
)paren
suffix:semicolon
multiline_comment|/* w is the # pixels between two long-aligned points, left and right */
id|w
op_assign
(paren
id|r
op_amp
op_complement
l_int|31
)paren
op_minus
(paren
(paren
id|l
op_plus
l_int|31
)paren
op_amp
op_complement
l_int|31
)paren
suffix:semicolon
multiline_comment|/* lo is the # pixels between the left edge and a long-aligned left pixel */
id|lo
op_assign
(paren
(paren
id|l
op_plus
l_int|31
)paren
op_amp
op_complement
l_int|31
)paren
op_minus
id|l
suffix:semicolon
id|s
op_assign
l_int|0
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
id|s
op_assign
id|w
op_rshift
l_int|3
suffix:semicolon
id|dest
op_add_assign
id|lo
op_rshift
l_int|3
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|s
op_assign
id|w
op_rshift
l_int|2
suffix:semicolon
id|dest
op_add_assign
id|lo
op_rshift
l_int|2
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|s
op_assign
id|w
op_rshift
l_int|1
suffix:semicolon
id|dest
op_add_assign
id|lo
op_rshift
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|8
suffix:colon
id|s
op_assign
id|w
suffix:semicolon
id|dest
op_add_assign
id|lo
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|16
suffix:colon
id|s
op_assign
id|w
op_lshift
l_int|1
suffix:semicolon
id|dest
op_add_assign
id|lo
op_lshift
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|32
suffix:colon
id|s
op_assign
id|w
op_lshift
l_int|2
suffix:semicolon
id|dest
op_add_assign
id|lo
op_lshift
l_int|2
suffix:semicolon
r_break
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
id|t
suffix:semicolon
id|i
OL
id|b
suffix:semicolon
id|i
op_increment
)paren
(brace
id|j
op_assign
id|l
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|j
op_amp
l_int|31
op_logical_and
id|j
OL
id|r
suffix:semicolon
id|j
op_increment
)paren
id|plot_pixel_mac
c_func
(paren
id|p
comma
id|pixel
comma
id|j
comma
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
id|j
OL
id|r
)paren
(brace
r_if
c_cond
(paren
id|PIXEL_WHITE_MAC
op_eq
id|pixel
)paren
id|fb_memclear
c_func
(paren
id|dest
comma
id|s
)paren
suffix:semicolon
r_else
id|fb_memset255
c_func
(paren
id|dest
comma
id|s
)paren
suffix:semicolon
id|dest
op_add_assign
id|p-&gt;next_line
suffix:semicolon
id|j
op_add_assign
id|w
suffix:semicolon
)brace
r_for
c_loop
(paren
suffix:semicolon
id|j
OL
id|r
suffix:semicolon
id|j
op_increment
)paren
id|plot_pixel_mac
c_func
(paren
id|p
comma
id|pixel
comma
id|j
comma
id|i
)paren
suffix:semicolon
)brace
)brace
DECL|function|fbcon_mac_putc
r_void
id|fbcon_mac_putc
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
id|cdat
suffix:semicolon
id|u_int
id|rows
comma
id|bold
comma
id|ch_reverse
comma
id|ch_underline
suffix:semicolon
id|u8
id|d
suffix:semicolon
r_int
id|j
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
id|ch_reverse
op_assign
id|attr_reverse
c_func
(paren
id|p
comma
id|c
)paren
suffix:semicolon
id|ch_underline
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
l_int|0
suffix:semicolon
id|rows
OL
id|fontheight
c_func
(paren
id|p
)paren
suffix:semicolon
id|rows
op_increment
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
op_logical_neg
id|conp-&gt;vc_can_do_color
)paren
(brace
r_if
c_cond
(paren
id|ch_underline
op_logical_and
id|rows
op_eq
(paren
id|fontheight
c_func
(paren
id|p
)paren
op_minus
l_int|2
)paren
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
id|ch_reverse
)paren
id|d
op_assign
op_complement
id|d
suffix:semicolon
)brace
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|fontwidth
c_func
(paren
id|p
)paren
suffix:semicolon
id|j
op_increment
)paren
(brace
id|plot_pixel_mac
c_func
(paren
id|p
comma
(paren
id|d
op_amp
l_int|0x80
)paren
op_rshift
l_int|7
comma
(paren
id|xx
op_star
id|fontwidth
c_func
(paren
id|p
)paren
)paren
op_plus
id|j
comma
(paren
id|yy
op_star
id|fontheight
c_func
(paren
id|p
)paren
)paren
op_plus
id|rows
)paren
suffix:semicolon
id|d
op_lshift_assign
l_int|1
suffix:semicolon
)brace
)brace
)brace
DECL|function|fbcon_mac_putcs
r_void
id|fbcon_mac_putcs
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
id|u16
id|c
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
suffix:semicolon
id|fbcon_mac_putc
c_func
(paren
id|conp
comma
id|p
comma
id|c
comma
id|yy
comma
id|xx
op_increment
)paren
suffix:semicolon
)brace
)brace
DECL|function|fbcon_mac_revc
r_void
id|fbcon_mac_revc
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
id|u_int
id|rows
comma
id|j
suffix:semicolon
r_for
c_loop
(paren
id|rows
op_assign
l_int|0
suffix:semicolon
id|rows
OL
id|fontheight
c_func
(paren
id|p
)paren
suffix:semicolon
id|rows
op_increment
)paren
(brace
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|fontwidth
c_func
(paren
id|p
)paren
suffix:semicolon
id|j
op_increment
)paren
(brace
id|plot_pixel_mac
(paren
id|p
comma
id|PIXEL_INVERT_MAC
comma
(paren
id|xx
op_star
id|fontwidth
c_func
(paren
id|p
)paren
)paren
op_plus
id|j
comma
(paren
id|yy
op_star
id|fontheight
c_func
(paren
id|p
)paren
)paren
op_plus
id|rows
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|function|plot_helper
r_static
r_inline
r_void
id|plot_helper
c_func
(paren
id|u8
op_star
id|dest
comma
id|u8
id|bit
comma
r_int
id|bw
)paren
(brace
r_switch
c_cond
(paren
id|bw
)paren
(brace
r_case
id|PIXEL_BLACK_MAC
suffix:colon
id|fb_writeb
c_func
(paren
id|fb_readb
c_func
(paren
id|dest
)paren
op_or
id|bit
comma
id|dest
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PIXEL_WHITE_MAC
suffix:colon
id|fb_writeb
c_func
(paren
id|fb_readb
c_func
(paren
id|dest
)paren
op_amp
(paren
op_complement
id|bit
)paren
comma
id|dest
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PIXEL_INVERT_MAC
suffix:colon
id|fb_writeb
c_func
(paren
id|fb_readb
c_func
(paren
id|dest
)paren
op_xor
id|bit
comma
id|dest
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;ERROR: Unknown pixel value in plot_pixel_mac&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * plot_pixel_mac&n; */
DECL|function|plot_pixel_mac
r_static
r_void
id|plot_pixel_mac
c_func
(paren
r_struct
id|display
op_star
id|p
comma
r_int
id|bw
comma
r_int
id|pixel_x
comma
r_int
id|pixel_y
)paren
(brace
id|u8
op_star
id|dest
comma
id|bit
suffix:semicolon
id|u16
op_star
id|dest16
comma
id|pix16
suffix:semicolon
id|u32
op_star
id|dest32
comma
id|pix32
suffix:semicolon
multiline_comment|/* There *are* 68k Macs that support more than 832x624, you know :-) */
r_if
c_cond
(paren
id|pixel_x
OL
l_int|0
op_logical_or
id|pixel_y
OL
l_int|0
op_logical_or
id|pixel_x
op_ge
id|p-&gt;var.xres
op_logical_or
id|pixel_y
op_ge
id|p-&gt;var.yres
)paren
(brace
id|printk
(paren
l_string|&quot;ERROR: pixel_x == %d, pixel_y == %d&quot;
comma
id|pixel_x
comma
id|pixel_y
)paren
suffix:semicolon
id|mdelay
c_func
(paren
l_int|1000
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|p-&gt;var.bits_per_pixel
)paren
(brace
r_case
l_int|1
suffix:colon
id|dest
op_assign
(paren
id|u8
op_star
)paren
(paren
(paren
id|pixel_x
op_rshift
l_int|3
)paren
op_plus
id|p-&gt;fb_info-&gt;screen_base
op_plus
id|pixel_y
op_star
id|p-&gt;next_line
)paren
suffix:semicolon
id|bit
op_assign
l_int|0x80
op_rshift
(paren
id|pixel_x
op_amp
l_int|7
)paren
suffix:semicolon
id|plot_helper
c_func
(paren
id|dest
comma
id|bit
comma
id|bw
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|dest
op_assign
(paren
id|u8
op_star
)paren
(paren
(paren
id|pixel_x
op_rshift
l_int|2
)paren
op_plus
id|p-&gt;fb_info-&gt;screen_base
op_plus
id|pixel_y
op_star
id|p-&gt;next_line
)paren
suffix:semicolon
id|bit
op_assign
l_int|0xC0
op_rshift
(paren
(paren
id|pixel_x
op_amp
l_int|3
)paren
op_lshift
l_int|1
)paren
suffix:semicolon
id|plot_helper
c_func
(paren
id|dest
comma
id|bit
comma
id|bw
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|dest
op_assign
(paren
id|u8
op_star
)paren
(paren
(paren
id|pixel_x
op_rshift
l_int|1
)paren
op_plus
id|p-&gt;fb_info-&gt;screen_base
op_plus
id|pixel_y
op_star
id|p-&gt;next_line
)paren
suffix:semicolon
id|bit
op_assign
l_int|0xF0
op_rshift
(paren
(paren
id|pixel_x
op_amp
l_int|1
)paren
op_lshift
l_int|2
)paren
suffix:semicolon
id|plot_helper
c_func
(paren
id|dest
comma
id|bit
comma
id|bw
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|8
suffix:colon
id|dest
op_assign
(paren
id|u8
op_star
)paren
(paren
id|pixel_x
op_plus
id|p-&gt;fb_info-&gt;screen_base
op_plus
id|pixel_y
op_star
id|p-&gt;next_line
)paren
suffix:semicolon
id|bit
op_assign
l_int|0xFF
suffix:semicolon
id|plot_helper
c_func
(paren
id|dest
comma
id|bit
comma
id|bw
)paren
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* FIXME: You can&squot;t access framebuffer directly like this! */
r_case
l_int|16
suffix:colon
id|dest16
op_assign
(paren
id|u16
op_star
)paren
(paren
(paren
id|pixel_x
op_star
l_int|2
)paren
op_plus
id|p-&gt;fb_info-&gt;screen_base
op_plus
id|pixel_y
op_star
id|p-&gt;next_line
)paren
suffix:semicolon
id|pix16
op_assign
l_int|0xFFFF
suffix:semicolon
r_switch
c_cond
(paren
id|bw
)paren
(brace
r_case
id|PIXEL_BLACK_MAC
suffix:colon
op_star
id|dest16
op_assign
op_complement
id|pix16
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PIXEL_WHITE_MAC
suffix:colon
op_star
id|dest16
op_assign
id|pix16
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PIXEL_INVERT_MAC
suffix:colon
op_star
id|dest16
op_xor_assign
id|pix16
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;ERROR: Unknown pixel value in plot_pixel_mac&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_int|32
suffix:colon
id|dest32
op_assign
(paren
id|u32
op_star
)paren
(paren
(paren
id|pixel_x
op_star
l_int|4
)paren
op_plus
id|p-&gt;fb_info-&gt;screen_base
op_plus
id|pixel_y
op_star
id|p-&gt;next_line
)paren
suffix:semicolon
id|pix32
op_assign
l_int|0xFFFFFFFF
suffix:semicolon
r_switch
c_cond
(paren
id|bw
)paren
(brace
r_case
id|PIXEL_BLACK_MAC
suffix:colon
op_star
id|dest32
op_assign
op_complement
id|pix32
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PIXEL_WHITE_MAC
suffix:colon
op_star
id|dest32
op_assign
id|pix32
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PIXEL_INVERT_MAC
suffix:colon
op_star
id|dest32
op_xor_assign
id|pix32
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;ERROR: Unknown pixel value in plot_pixel_mac&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
)brace
DECL|function|get_pixel_mac
r_static
r_int
id|get_pixel_mac
c_func
(paren
r_struct
id|display
op_star
id|p
comma
r_int
id|pixel_x
comma
r_int
id|pixel_y
)paren
(brace
id|u8
op_star
id|dest
comma
id|bit
suffix:semicolon
id|u16
op_star
id|dest16
suffix:semicolon
id|u32
op_star
id|dest32
suffix:semicolon
id|u8
id|pixel
op_assign
l_int|0
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
id|dest
op_assign
(paren
id|u8
op_star
)paren
(paren
(paren
id|pixel_x
op_div
l_int|8
)paren
op_plus
id|p-&gt;fb_info-&gt;screen_base
op_plus
id|pixel_y
op_star
id|p-&gt;next_line
)paren
suffix:semicolon
id|bit
op_assign
l_int|0x80
op_rshift
(paren
id|pixel_x
op_amp
l_int|7
)paren
suffix:semicolon
id|pixel
op_assign
op_star
id|dest
op_amp
id|bit
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|dest
op_assign
(paren
id|u8
op_star
)paren
(paren
(paren
id|pixel_x
op_div
l_int|4
)paren
op_plus
id|p-&gt;fb_info-&gt;screen_base
op_plus
id|pixel_y
op_star
id|p-&gt;next_line
)paren
suffix:semicolon
id|bit
op_assign
l_int|0xC0
op_rshift
(paren
id|pixel_x
op_amp
l_int|3
)paren
suffix:semicolon
id|pixel
op_assign
op_star
id|dest
op_amp
id|bit
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|dest
op_assign
(paren
id|u8
op_star
)paren
(paren
(paren
id|pixel_x
op_div
l_int|2
)paren
op_plus
id|p-&gt;fb_info-&gt;screen_base
op_plus
id|pixel_y
op_star
id|p-&gt;next_line
)paren
suffix:semicolon
id|bit
op_assign
l_int|0xF0
op_rshift
(paren
id|pixel_x
op_amp
l_int|1
)paren
suffix:semicolon
id|pixel
op_assign
op_star
id|dest
op_amp
id|bit
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|8
suffix:colon
id|dest
op_assign
(paren
id|u8
op_star
)paren
(paren
id|pixel_x
op_plus
id|p-&gt;fb_info-&gt;screen_base
op_plus
id|pixel_y
op_star
id|p-&gt;next_line
)paren
suffix:semicolon
id|pixel
op_assign
op_star
id|dest
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|16
suffix:colon
id|dest16
op_assign
(paren
id|u16
op_star
)paren
(paren
(paren
id|pixel_x
op_star
l_int|2
)paren
op_plus
id|p-&gt;fb_info-&gt;screen_base
op_plus
id|pixel_y
op_star
id|p-&gt;next_line
)paren
suffix:semicolon
id|pixel
op_assign
op_star
id|dest16
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|32
suffix:colon
id|dest32
op_assign
(paren
id|u32
op_star
)paren
(paren
(paren
id|pixel_x
op_star
l_int|4
)paren
op_plus
id|p-&gt;fb_info-&gt;screen_base
op_plus
id|pixel_y
op_star
id|p-&gt;next_line
)paren
suffix:semicolon
id|pixel
op_assign
op_star
id|dest32
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|pixel
ques
c_cond
id|PIXEL_BLACK_MAC
suffix:colon
id|PIXEL_WHITE_MAC
suffix:semicolon
)brace
multiline_comment|/*&n;     *  `switch&squot; for the low level operations&n;     */
DECL|variable|fbcon_mac
r_struct
id|display_switch
id|fbcon_mac
op_assign
(brace
id|setup
suffix:colon
id|fbcon_mac_setup
comma
id|bmove
suffix:colon
id|fbcon_redraw_bmove
comma
id|clear
suffix:colon
id|fbcon_redraw_clear
comma
id|putc
suffix:colon
id|fbcon_mac_putc
comma
id|putcs
suffix:colon
id|fbcon_mac_putcs
comma
id|revc
suffix:colon
id|fbcon_mac_revc
comma
id|fontwidthmask
suffix:colon
id|FONTWIDTHRANGE
c_func
(paren
l_int|1
comma
l_int|8
)paren
)brace
suffix:semicolon
macro_line|#ifdef MODULE
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
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
DECL|function|cleanup_module
r_void
id|cleanup_module
c_func
(paren
r_void
)paren
(brace
)brace
macro_line|#endif /* MODULE */
multiline_comment|/*&n;     *  Visible symbols for modules&n;     */
DECL|variable|fbcon_mac
id|EXPORT_SYMBOL
c_func
(paren
id|fbcon_mac
)paren
suffix:semicolon
DECL|variable|fbcon_mac_setup
id|EXPORT_SYMBOL
c_func
(paren
id|fbcon_mac_setup
)paren
suffix:semicolon
DECL|variable|fbcon_mac_bmove
id|EXPORT_SYMBOL
c_func
(paren
id|fbcon_mac_bmove
)paren
suffix:semicolon
DECL|variable|fbcon_mac_clear
id|EXPORT_SYMBOL
c_func
(paren
id|fbcon_mac_clear
)paren
suffix:semicolon
DECL|variable|fbcon_mac_putc
id|EXPORT_SYMBOL
c_func
(paren
id|fbcon_mac_putc
)paren
suffix:semicolon
DECL|variable|fbcon_mac_putcs
id|EXPORT_SYMBOL
c_func
(paren
id|fbcon_mac_putcs
)paren
suffix:semicolon
DECL|variable|fbcon_mac_revc
id|EXPORT_SYMBOL
c_func
(paren
id|fbcon_mac_revc
)paren
suffix:semicolon
eof
