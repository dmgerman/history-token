multiline_comment|/*&n; * linux/drivers/video/softcursor.c -- Generic software cursor for frame buffer devices&n; *&n; *  Created 14 Nov 2002 by James Simmons &n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file COPYING in the main directory of this archive&n; * for more details.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/fb.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/io.h&gt;
DECL|function|soft_cursor
r_int
id|soft_cursor
c_func
(paren
r_struct
id|fb_info
op_star
id|info
comma
r_struct
id|fb_cursor
op_star
id|cursor
)paren
(brace
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
id|i
comma
id|size
comma
id|dsize
comma
id|s_pitch
comma
id|d_pitch
suffix:semicolon
id|u8
op_star
id|dst
comma
id|src
(braket
l_int|64
)braket
suffix:semicolon
r_if
c_cond
(paren
id|cursor-&gt;set
op_amp
id|FB_CUR_SETSIZE
)paren
(brace
id|info-&gt;cursor.image.height
op_assign
id|cursor-&gt;image.height
suffix:semicolon
id|info-&gt;cursor.image.width
op_assign
id|cursor-&gt;image.width
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cursor-&gt;set
op_amp
id|FB_CUR_SETPOS
)paren
(brace
id|info-&gt;cursor.image.dx
op_assign
id|cursor-&gt;image.dx
suffix:semicolon
id|info-&gt;cursor.image.dy
op_assign
id|cursor-&gt;image.dy
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cursor-&gt;set
op_amp
id|FB_CUR_SETHOT
)paren
id|info-&gt;cursor.hot
op_assign
id|cursor-&gt;hot
suffix:semicolon
r_if
c_cond
(paren
id|cursor-&gt;set
op_amp
id|FB_CUR_SETCMAP
)paren
(brace
r_if
c_cond
(paren
id|cursor-&gt;image.depth
op_eq
l_int|1
)paren
(brace
id|info-&gt;cursor.image.bg_color
op_assign
id|cursor-&gt;image.bg_color
suffix:semicolon
id|info-&gt;cursor.image.fg_color
op_assign
id|cursor-&gt;image.fg_color
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|cursor-&gt;image.cmap.len
)paren
id|fb_copy_cmap
c_func
(paren
op_amp
id|cursor-&gt;image.cmap
comma
op_amp
id|info-&gt;cursor.image.cmap
comma
l_int|0
)paren
suffix:semicolon
)brace
id|info-&gt;cursor.image.depth
op_assign
id|cursor-&gt;image.depth
suffix:semicolon
)brace
r_if
c_cond
(paren
id|info-&gt;state
op_ne
id|FBINFO_STATE_RUNNING
)paren
r_return
l_int|0
suffix:semicolon
id|s_pitch
op_assign
(paren
id|info-&gt;cursor.image.width
op_plus
l_int|7
)paren
op_rshift
l_int|3
suffix:semicolon
id|dsize
op_assign
id|s_pitch
op_star
id|info-&gt;cursor.image.height
suffix:semicolon
id|d_pitch
op_assign
(paren
id|s_pitch
op_plus
id|scan_align
)paren
op_amp
op_complement
id|scan_align
suffix:semicolon
id|size
op_assign
id|d_pitch
op_star
id|info-&gt;cursor.image.height
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
id|info-&gt;pixmap.addr
op_plus
id|fb_get_buffer_offset
c_func
(paren
id|info
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;cursor.enable
)paren
(brace
r_switch
c_cond
(paren
id|info-&gt;cursor.rop
)paren
(brace
r_case
id|ROP_XOR
suffix:colon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|dsize
suffix:semicolon
id|i
op_increment
)paren
id|src
(braket
id|i
)braket
op_assign
id|cursor-&gt;image.data
(braket
id|i
)braket
op_xor
id|info-&gt;cursor.mask
(braket
id|i
)braket
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ROP_COPY
suffix:colon
r_default
suffix:colon
(brace
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|dsize
suffix:semicolon
id|i
op_increment
)paren
id|src
(braket
id|i
)braket
op_assign
id|cursor-&gt;image.data
(braket
id|i
)braket
op_amp
id|info-&gt;cursor.mask
(braket
id|i
)braket
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_else
id|memcpy
c_func
(paren
id|src
comma
id|cursor-&gt;image.data
comma
id|dsize
)paren
suffix:semicolon
id|move_buf_aligned
c_func
(paren
id|info
comma
id|dst
comma
id|src
comma
id|d_pitch
comma
id|s_pitch
comma
id|info-&gt;cursor.image.height
)paren
suffix:semicolon
id|info-&gt;cursor.image.data
op_assign
id|dst
suffix:semicolon
id|info-&gt;fbops
op_member_access_from_pointer
id|fb_imageblit
c_func
(paren
id|info
comma
op_amp
id|info-&gt;cursor.image
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|soft_cursor
id|EXPORT_SYMBOL
c_func
(paren
id|soft_cursor
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
l_string|&quot;Generic software cursor&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
