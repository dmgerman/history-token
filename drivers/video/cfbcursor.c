multiline_comment|/*&n; * linux/drivers/video/cfbcursor.c -- Generic software cursor for frame buffer devices&n; *&n; *  Created 14 Nov 2002 by James Simmons &n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file COPYING in the main directory of this archive&n; * for more details.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/fb.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/io.h&gt;
DECL|function|cfb_cursor
r_int
id|cfb_cursor
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
id|i
comma
id|size
op_assign
(paren
(paren
id|cursor-&gt;image.width
op_plus
l_int|7
)paren
op_div
l_int|8
)paren
op_star
id|cursor-&gt;image.height
suffix:semicolon
r_struct
id|fb_image
id|image
suffix:semicolon
r_static
r_char
id|data
(braket
l_int|64
)braket
suffix:semicolon
r_if
c_cond
(paren
id|cursor-&gt;enable
)paren
(brace
r_switch
c_cond
(paren
id|cursor-&gt;rop
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
id|size
suffix:semicolon
id|i
op_increment
)paren
id|data
(braket
id|i
)braket
op_assign
(paren
id|cursor-&gt;image.data
(braket
id|i
)braket
op_amp
id|cursor-&gt;mask
(braket
id|i
)braket
)paren
op_xor
id|cursor-&gt;dest
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
id|size
suffix:semicolon
id|i
op_increment
)paren
id|data
(braket
id|i
)braket
op_assign
id|cursor-&gt;image.data
(braket
id|i
)braket
op_amp
id|cursor-&gt;mask
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
id|data
comma
id|cursor-&gt;dest
comma
id|size
)paren
suffix:semicolon
id|image.bg_color
op_assign
id|cursor-&gt;image.bg_color
suffix:semicolon
id|image.fg_color
op_assign
id|cursor-&gt;image.fg_color
suffix:semicolon
id|image.dx
op_assign
id|cursor-&gt;image.dx
suffix:semicolon
id|image.dy
op_assign
id|cursor-&gt;image.dy
suffix:semicolon
id|image.width
op_assign
id|cursor-&gt;image.width
suffix:semicolon
id|image.height
op_assign
id|cursor-&gt;image.height
suffix:semicolon
id|image.depth
op_assign
id|cursor-&gt;image.depth
suffix:semicolon
id|image.data
op_assign
id|data
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;fbops-&gt;fb_imageblit
)paren
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
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|cfb_cursor
id|EXPORT_SYMBOL
c_func
(paren
id|cfb_cursor
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
