multiline_comment|/*&n; *  linux/drivers/video/cfb2.c -- Low level frame buffer operations for 2 bpp&n; *&t;&t;&t;&t;  packed pixels&n; *&n; *&t;Created 26 Dec 1997 by Michael Schmitz&n; *&t;Based on cfb4.c&n; *&n; *  This file is subject to the terms and conditions of the GNU General Public&n; *  License.  See the file COPYING in the main directory of this archive for&n; *  more details.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/fb.h&gt;
macro_line|#include &lt;video/fbcon.h&gt;
macro_line|#include &lt;video/fbcon-cfb2.h&gt;
multiline_comment|/*&n;     *  2 bpp packed pixels&n;     */
multiline_comment|/*&n;     *  IFF the font is even pixel aligned (that is to say each&n;     *  character start is a byte start in the pixel pairs). That&n;     *  avoids us having to mask bytes and means we won&squot;t be here&n;     *  all week. On a MacII that matters _lots_&n;     */
DECL|variable|nibbletab_cfb2
r_static
id|u_char
id|nibbletab_cfb2
(braket
)braket
op_assign
initialization_block
suffix:semicolon
DECL|function|fbcon_cfb2_setup
r_void
id|fbcon_cfb2_setup
c_func
(paren
r_struct
id|display
op_star
id|p
)paren
(brace
id|p-&gt;next_line
op_assign
id|p-&gt;line_length
ques
c_cond
id|p-&gt;line_length
suffix:colon
id|p-&gt;var.xres_virtual
op_rshift
l_int|2
suffix:semicolon
id|p-&gt;next_plane
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|fbcon_cfb2_bmove
r_void
id|fbcon_cfb2_bmove
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
id|bytes
op_assign
id|p-&gt;next_line
comma
id|linesize
op_assign
id|bytes
op_star
id|fontheight
c_func
(paren
id|p
)paren
comma
id|rows
suffix:semicolon
id|u8
op_star
id|src
comma
op_star
id|dst
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
op_star
l_int|2
op_eq
id|bytes
)paren
(brace
id|fb_memmove
c_func
(paren
id|p-&gt;screen_base
op_plus
id|dy
op_star
id|linesize
comma
id|p-&gt;screen_base
op_plus
id|sy
op_star
id|linesize
comma
id|height
op_star
id|linesize
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|dy
OL
id|sy
op_logical_or
(paren
id|dy
op_eq
id|sy
op_logical_and
id|dx
OL
id|sx
)paren
)paren
(brace
id|src
op_assign
id|p-&gt;screen_base
op_plus
id|sy
op_star
id|linesize
op_plus
id|sx
op_star
l_int|2
suffix:semicolon
id|dst
op_assign
id|p-&gt;screen_base
op_plus
id|dy
op_star
id|linesize
op_plus
id|dx
op_star
l_int|2
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
id|fb_memmove
c_func
(paren
id|dst
comma
id|src
comma
id|width
op_star
l_int|2
)paren
suffix:semicolon
id|src
op_add_assign
id|bytes
suffix:semicolon
id|dst
op_add_assign
id|bytes
suffix:semicolon
)brace
)brace
r_else
(brace
id|src
op_assign
id|p-&gt;screen_base
op_plus
(paren
id|sy
op_plus
id|height
)paren
op_star
id|linesize
op_plus
id|sx
op_star
l_int|2
op_minus
id|bytes
suffix:semicolon
id|dst
op_assign
id|p-&gt;screen_base
op_plus
(paren
id|dy
op_plus
id|height
)paren
op_star
id|linesize
op_plus
id|dx
op_star
l_int|2
op_minus
id|bytes
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
id|fb_memmove
c_func
(paren
id|dst
comma
id|src
comma
id|width
op_star
l_int|2
)paren
suffix:semicolon
id|src
op_sub_assign
id|bytes
suffix:semicolon
id|dst
op_sub_assign
id|bytes
suffix:semicolon
)brace
)brace
)brace
)brace
DECL|function|fbcon_cfb2_clear
r_void
id|fbcon_cfb2_clear
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
id|dest0
comma
op_star
id|dest
suffix:semicolon
r_int
id|bytes
op_assign
id|p-&gt;next_line
comma
id|lines
op_assign
id|height
op_star
id|fontheight
c_func
(paren
id|p
)paren
comma
id|rows
comma
id|i
suffix:semicolon
id|u32
id|bgx
suffix:semicolon
id|dest
op_assign
id|p-&gt;screen_base
op_plus
id|sy
op_star
id|fontheight
c_func
(paren
id|p
)paren
op_star
id|bytes
op_plus
id|sx
op_star
l_int|2
suffix:semicolon
id|bgx
op_assign
id|attr_bgcol_ec
c_func
(paren
id|p
comma
id|conp
)paren
suffix:semicolon
id|bgx
op_or_assign
(paren
id|bgx
op_lshift
l_int|2
)paren
suffix:semicolon
multiline_comment|/* expand the colour to 16 bits */
id|bgx
op_or_assign
(paren
id|bgx
op_lshift
l_int|4
)paren
suffix:semicolon
id|bgx
op_or_assign
(paren
id|bgx
op_lshift
l_int|8
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
op_star
l_int|2
op_eq
id|bytes
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|lines
op_star
id|width
suffix:semicolon
id|i
op_increment
)paren
(brace
id|fb_writew
(paren
id|bgx
comma
id|dest
)paren
suffix:semicolon
id|dest
op_add_assign
l_int|2
suffix:semicolon
)brace
)brace
r_else
(brace
id|dest0
op_assign
id|dest
suffix:semicolon
r_for
c_loop
(paren
id|rows
op_assign
id|lines
suffix:semicolon
id|rows
op_decrement
suffix:semicolon
id|dest0
op_add_assign
id|bytes
)paren
(brace
id|dest
op_assign
id|dest0
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
id|width
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/* memset ?? */
id|fb_writew
(paren
id|bgx
comma
id|dest
)paren
suffix:semicolon
id|dest
op_add_assign
l_int|2
suffix:semicolon
)brace
)brace
)brace
)brace
DECL|function|fbcon_cfb2_putc
r_void
id|fbcon_cfb2_putc
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
r_int
id|bytes
op_assign
id|p-&gt;next_line
comma
id|rows
suffix:semicolon
id|u32
id|eorx
comma
id|fgx
comma
id|bgx
suffix:semicolon
id|dest
op_assign
id|p-&gt;screen_base
op_plus
id|yy
op_star
id|fontheight
c_func
(paren
id|p
)paren
op_star
id|bytes
op_plus
id|xx
op_star
l_int|2
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
id|fgx
op_assign
l_int|3
suffix:semicolon
multiline_comment|/*attr_fgcol(p,c);*/
id|bgx
op_assign
id|attr_bgcol
c_func
(paren
id|p
comma
id|c
)paren
suffix:semicolon
id|fgx
op_or_assign
(paren
id|fgx
op_lshift
l_int|2
)paren
suffix:semicolon
multiline_comment|/* expand color to 8 bits */
id|fgx
op_or_assign
(paren
id|fgx
op_lshift
l_int|4
)paren
suffix:semicolon
id|bgx
op_or_assign
(paren
id|bgx
op_lshift
l_int|2
)paren
suffix:semicolon
id|bgx
op_or_assign
(paren
id|bgx
op_lshift
l_int|4
)paren
suffix:semicolon
id|eorx
op_assign
id|fgx
op_xor
id|bgx
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
id|bytes
)paren
(brace
id|fb_writeb
c_func
(paren
(paren
id|nibbletab_cfb2
(braket
op_star
id|cdat
op_rshift
l_int|4
)braket
op_amp
id|eorx
)paren
op_xor
id|bgx
comma
id|dest
op_plus
l_int|0
)paren
suffix:semicolon
id|fb_writeb
c_func
(paren
(paren
id|nibbletab_cfb2
(braket
op_star
id|cdat
op_increment
op_amp
l_int|0xf
)braket
op_amp
id|eorx
)paren
op_xor
id|bgx
comma
id|dest
op_plus
l_int|1
)paren
suffix:semicolon
)brace
)brace
DECL|function|fbcon_cfb2_putcs
r_void
id|fbcon_cfb2_putcs
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
id|cdat
comma
op_star
id|dest
comma
op_star
id|dest0
suffix:semicolon
id|u16
id|c
suffix:semicolon
r_int
id|rows
comma
id|bytes
op_assign
id|p-&gt;next_line
suffix:semicolon
id|u32
id|eorx
comma
id|fgx
comma
id|bgx
suffix:semicolon
id|dest0
op_assign
id|p-&gt;screen_base
op_plus
id|yy
op_star
id|fontheight
c_func
(paren
id|p
)paren
op_star
id|bytes
op_plus
id|xx
op_star
l_int|2
suffix:semicolon
id|fgx
op_assign
l_int|3
multiline_comment|/*attr_fgcol(p,scr_readw(s))*/
suffix:semicolon
id|bgx
op_assign
id|attr_bgcol
c_func
(paren
id|p
comma
id|scr_readw
c_func
(paren
id|s
)paren
)paren
suffix:semicolon
id|fgx
op_or_assign
(paren
id|fgx
op_lshift
l_int|2
)paren
suffix:semicolon
id|fgx
op_or_assign
(paren
id|fgx
op_lshift
l_int|4
)paren
suffix:semicolon
id|bgx
op_or_assign
(paren
id|bgx
op_lshift
l_int|2
)paren
suffix:semicolon
id|bgx
op_or_assign
(paren
id|bgx
op_lshift
l_int|4
)paren
suffix:semicolon
id|eorx
op_assign
id|fgx
op_xor
id|bgx
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
comma
id|dest
op_assign
id|dest0
suffix:semicolon
id|rows
op_decrement
suffix:semicolon
id|dest
op_add_assign
id|bytes
)paren
(brace
id|fb_writeb
c_func
(paren
(paren
id|nibbletab_cfb2
(braket
op_star
id|cdat
op_rshift
l_int|4
)braket
op_amp
id|eorx
)paren
op_xor
id|bgx
comma
id|dest
op_plus
l_int|0
)paren
suffix:semicolon
id|fb_writeb
c_func
(paren
(paren
id|nibbletab_cfb2
(braket
op_star
id|cdat
op_increment
op_amp
l_int|0xf
)braket
op_amp
id|eorx
)paren
op_xor
id|bgx
comma
id|dest
op_plus
l_int|1
)paren
suffix:semicolon
)brace
id|dest0
op_add_assign
l_int|2
suffix:semicolon
)brace
)brace
DECL|function|fbcon_cfb2_revc
r_void
id|fbcon_cfb2_revc
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
suffix:semicolon
r_int
id|bytes
op_assign
id|p-&gt;next_line
comma
id|rows
suffix:semicolon
id|dest
op_assign
id|p-&gt;screen_base
op_plus
id|yy
op_star
id|fontheight
c_func
(paren
id|p
)paren
op_star
id|bytes
op_plus
id|xx
op_star
l_int|2
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
id|bytes
)paren
(brace
id|fb_writew
c_func
(paren
id|fb_readw
c_func
(paren
id|dest
)paren
op_xor
l_int|0xffff
comma
id|dest
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;     *  `switch&squot; for the low level operations&n;     */
DECL|variable|fbcon_cfb2
r_struct
id|display_switch
id|fbcon_cfb2
op_assign
(brace
id|setup
suffix:colon
id|fbcon_cfb2_setup
comma
id|bmove
suffix:colon
id|fbcon_cfb2_bmove
comma
id|clear
suffix:colon
id|fbcon_cfb2_clear
comma
id|putc
suffix:colon
id|fbcon_cfb2_putc
comma
id|putcs
suffix:colon
id|fbcon_cfb2_putcs
comma
id|revc
suffix:colon
id|fbcon_cfb2_revc
comma
id|fontwidthmask
suffix:colon
id|FONTWIDTH
c_func
(paren
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
DECL|variable|fbcon_cfb2
id|EXPORT_SYMBOL
c_func
(paren
id|fbcon_cfb2
)paren
suffix:semicolon
DECL|variable|fbcon_cfb2_setup
id|EXPORT_SYMBOL
c_func
(paren
id|fbcon_cfb2_setup
)paren
suffix:semicolon
DECL|variable|fbcon_cfb2_bmove
id|EXPORT_SYMBOL
c_func
(paren
id|fbcon_cfb2_bmove
)paren
suffix:semicolon
DECL|variable|fbcon_cfb2_clear
id|EXPORT_SYMBOL
c_func
(paren
id|fbcon_cfb2_clear
)paren
suffix:semicolon
DECL|variable|fbcon_cfb2_putc
id|EXPORT_SYMBOL
c_func
(paren
id|fbcon_cfb2_putc
)paren
suffix:semicolon
DECL|variable|fbcon_cfb2_putcs
id|EXPORT_SYMBOL
c_func
(paren
id|fbcon_cfb2_putcs
)paren
suffix:semicolon
DECL|variable|fbcon_cfb2_revc
id|EXPORT_SYMBOL
c_func
(paren
id|fbcon_cfb2_revc
)paren
suffix:semicolon
eof
