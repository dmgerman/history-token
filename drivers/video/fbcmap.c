multiline_comment|/*&n; *  linux/drivers/video/fbcmap.c -- Colormap handling for frame buffer devices&n; *&n; *&t;Created 15 Jun 1997 by Geert Uytterhoeven&n; *&n; *&t;2001 - Documented with DocBook&n; *&t;- Brad Douglas &lt;brad@neruo.com&gt;&n; *&n; *  This file is subject to the terms and conditions of the GNU General Public&n; *  License.  See the file COPYING in the main directory of this archive for&n; *  more details.&n; */
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/fb.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
DECL|variable|red2
r_static
id|u16
id|red2
(braket
)braket
op_assign
(brace
l_int|0x0000
comma
l_int|0xaaaa
)brace
suffix:semicolon
DECL|variable|green2
r_static
id|u16
id|green2
(braket
)braket
op_assign
(brace
l_int|0x0000
comma
l_int|0xaaaa
)brace
suffix:semicolon
DECL|variable|blue2
r_static
id|u16
id|blue2
(braket
)braket
op_assign
(brace
l_int|0x0000
comma
l_int|0xaaaa
)brace
suffix:semicolon
DECL|variable|red4
r_static
id|u16
id|red4
(braket
)braket
op_assign
(brace
l_int|0x0000
comma
l_int|0xaaaa
comma
l_int|0x5555
comma
l_int|0xffff
)brace
suffix:semicolon
DECL|variable|green4
r_static
id|u16
id|green4
(braket
)braket
op_assign
(brace
l_int|0x0000
comma
l_int|0xaaaa
comma
l_int|0x5555
comma
l_int|0xffff
)brace
suffix:semicolon
DECL|variable|blue4
r_static
id|u16
id|blue4
(braket
)braket
op_assign
(brace
l_int|0x0000
comma
l_int|0xaaaa
comma
l_int|0x5555
comma
l_int|0xffff
)brace
suffix:semicolon
DECL|variable|red8
r_static
id|u16
id|red8
(braket
)braket
op_assign
(brace
l_int|0x0000
comma
l_int|0x0000
comma
l_int|0x0000
comma
l_int|0x0000
comma
l_int|0xaaaa
comma
l_int|0xaaaa
comma
l_int|0xaaaa
comma
l_int|0xaaaa
)brace
suffix:semicolon
DECL|variable|green8
r_static
id|u16
id|green8
(braket
)braket
op_assign
(brace
l_int|0x0000
comma
l_int|0x0000
comma
l_int|0xaaaa
comma
l_int|0xaaaa
comma
l_int|0x0000
comma
l_int|0x0000
comma
l_int|0x5555
comma
l_int|0xaaaa
)brace
suffix:semicolon
DECL|variable|blue8
r_static
id|u16
id|blue8
(braket
)braket
op_assign
(brace
l_int|0x0000
comma
l_int|0xaaaa
comma
l_int|0x0000
comma
l_int|0xaaaa
comma
l_int|0x0000
comma
l_int|0xaaaa
comma
l_int|0x0000
comma
l_int|0xaaaa
)brace
suffix:semicolon
DECL|variable|red16
r_static
id|u16
id|red16
(braket
)braket
op_assign
(brace
l_int|0x0000
comma
l_int|0x0000
comma
l_int|0x0000
comma
l_int|0x0000
comma
l_int|0xaaaa
comma
l_int|0xaaaa
comma
l_int|0xaaaa
comma
l_int|0xaaaa
comma
l_int|0x5555
comma
l_int|0x5555
comma
l_int|0x5555
comma
l_int|0x5555
comma
l_int|0xffff
comma
l_int|0xffff
comma
l_int|0xffff
comma
l_int|0xffff
)brace
suffix:semicolon
DECL|variable|green16
r_static
id|u16
id|green16
(braket
)braket
op_assign
(brace
l_int|0x0000
comma
l_int|0x0000
comma
l_int|0xaaaa
comma
l_int|0xaaaa
comma
l_int|0x0000
comma
l_int|0x0000
comma
l_int|0x5555
comma
l_int|0xaaaa
comma
l_int|0x5555
comma
l_int|0x5555
comma
l_int|0xffff
comma
l_int|0xffff
comma
l_int|0x5555
comma
l_int|0x5555
comma
l_int|0xffff
comma
l_int|0xffff
)brace
suffix:semicolon
DECL|variable|blue16
r_static
id|u16
id|blue16
(braket
)braket
op_assign
(brace
l_int|0x0000
comma
l_int|0xaaaa
comma
l_int|0x0000
comma
l_int|0xaaaa
comma
l_int|0x0000
comma
l_int|0xaaaa
comma
l_int|0x0000
comma
l_int|0xaaaa
comma
l_int|0x5555
comma
l_int|0xffff
comma
l_int|0x5555
comma
l_int|0xffff
comma
l_int|0x5555
comma
l_int|0xffff
comma
l_int|0x5555
comma
l_int|0xffff
)brace
suffix:semicolon
DECL|variable|default_2_colors
r_static
r_struct
id|fb_cmap
id|default_2_colors
op_assign
(brace
l_int|0
comma
l_int|2
comma
id|red2
comma
id|green2
comma
id|blue2
comma
l_int|NULL
)brace
suffix:semicolon
DECL|variable|default_8_colors
r_static
r_struct
id|fb_cmap
id|default_8_colors
op_assign
(brace
l_int|0
comma
l_int|8
comma
id|red8
comma
id|green8
comma
id|blue8
comma
l_int|NULL
)brace
suffix:semicolon
DECL|variable|default_4_colors
r_static
r_struct
id|fb_cmap
id|default_4_colors
op_assign
(brace
l_int|0
comma
l_int|4
comma
id|red4
comma
id|green4
comma
id|blue4
comma
l_int|NULL
)brace
suffix:semicolon
DECL|variable|default_16_colors
r_static
r_struct
id|fb_cmap
id|default_16_colors
op_assign
(brace
l_int|0
comma
l_int|16
comma
id|red16
comma
id|green16
comma
id|blue16
comma
l_int|NULL
)brace
suffix:semicolon
multiline_comment|/**&n; *&t;fb_alloc_cmap - allocate a colormap&n; *&t;@cmap: frame buffer colormap structure&n; *&t;@len: length of @cmap&n; *&t;@transp: boolean, 1 if there is transparency, 0 otherwise&n; *&n; *&t;Allocates memory for a colormap @cmap.  @len is the&n; *&t;number of entries in the palette.&n; *&n; *&t;Returns -1 errno on error, or zero on success.&n; *&n; */
DECL|function|fb_alloc_cmap
r_int
id|fb_alloc_cmap
c_func
(paren
r_struct
id|fb_cmap
op_star
id|cmap
comma
r_int
id|len
comma
r_int
id|transp
)paren
(brace
r_int
id|size
op_assign
id|len
op_star
r_sizeof
(paren
id|u16
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cmap-&gt;len
op_ne
id|len
)paren
(brace
id|fb_dealloc_cmap
c_func
(paren
id|cmap
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|len
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|cmap-&gt;red
op_assign
id|kmalloc
c_func
(paren
id|size
comma
id|GFP_ATOMIC
)paren
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|cmap-&gt;green
op_assign
id|kmalloc
c_func
(paren
id|size
comma
id|GFP_ATOMIC
)paren
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|cmap-&gt;blue
op_assign
id|kmalloc
c_func
(paren
id|size
comma
id|GFP_ATOMIC
)paren
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|transp
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|cmap-&gt;transp
op_assign
id|kmalloc
c_func
(paren
id|size
comma
id|GFP_ATOMIC
)paren
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_else
id|cmap-&gt;transp
op_assign
l_int|NULL
suffix:semicolon
)brace
id|cmap-&gt;start
op_assign
l_int|0
suffix:semicolon
id|cmap-&gt;len
op_assign
id|len
suffix:semicolon
id|fb_copy_cmap
c_func
(paren
id|fb_default_cmap
c_func
(paren
id|len
)paren
comma
id|cmap
comma
l_int|0
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; *      fb_dealloc_cmap - deallocate a colormap&n; *      @cmap: frame buffer colormap structure&n; *&n; *      Deallocates a colormap that was previously allocated with&n; *      fb_alloc_cmap().&n; *&n; */
DECL|function|fb_dealloc_cmap
r_void
id|fb_dealloc_cmap
c_func
(paren
r_struct
id|fb_cmap
op_star
id|cmap
)paren
(brace
r_if
c_cond
(paren
id|cmap-&gt;red
)paren
id|kfree
c_func
(paren
id|cmap-&gt;red
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cmap-&gt;green
)paren
id|kfree
c_func
(paren
id|cmap-&gt;green
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cmap-&gt;blue
)paren
id|kfree
c_func
(paren
id|cmap-&gt;blue
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cmap-&gt;transp
)paren
id|kfree
c_func
(paren
id|cmap-&gt;transp
)paren
suffix:semicolon
id|cmap-&gt;red
op_assign
id|cmap-&gt;green
op_assign
id|cmap-&gt;blue
op_assign
id|cmap-&gt;transp
op_assign
l_int|NULL
suffix:semicolon
id|cmap-&gt;len
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;fb_copy_cmap - copy a colormap&n; *&t;@from: frame buffer colormap structure&n; *&t;@to: frame buffer colormap structure&n; *&t;@fsfromto: determine copy method&n; *&n; *&t;Copy contents of colormap from @from to @to.&n; *&n; *&t;@fsfromto accepts the following integer parameters:&n; *&t;0: memcpy function&n; *&t;1: copy_from_user() function to copy from userspace&n; *&t;2: copy_to_user() function to copy to userspace&n; *&n; */
DECL|function|fb_copy_cmap
r_void
id|fb_copy_cmap
c_func
(paren
r_struct
id|fb_cmap
op_star
id|from
comma
r_struct
id|fb_cmap
op_star
id|to
comma
r_int
id|fsfromto
)paren
(brace
r_int
id|size
suffix:semicolon
r_int
id|tooff
op_assign
l_int|0
comma
id|fromoff
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|to-&gt;start
OG
id|from-&gt;start
)paren
id|fromoff
op_assign
id|to-&gt;start
op_minus
id|from-&gt;start
suffix:semicolon
r_else
id|tooff
op_assign
id|from-&gt;start
op_minus
id|to-&gt;start
suffix:semicolon
id|size
op_assign
id|to-&gt;len
op_minus
id|tooff
suffix:semicolon
r_if
c_cond
(paren
id|size
OG
(paren
r_int
)paren
(paren
id|from-&gt;len
op_minus
id|fromoff
)paren
)paren
id|size
op_assign
id|from-&gt;len
op_minus
id|fromoff
suffix:semicolon
r_if
c_cond
(paren
id|size
op_le
l_int|0
)paren
r_return
suffix:semicolon
id|size
op_mul_assign
r_sizeof
(paren
id|u16
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|fsfromto
)paren
(brace
r_case
l_int|0
suffix:colon
id|memcpy
c_func
(paren
id|to-&gt;red
op_plus
id|tooff
comma
id|from-&gt;red
op_plus
id|fromoff
comma
id|size
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|to-&gt;green
op_plus
id|tooff
comma
id|from-&gt;green
op_plus
id|fromoff
comma
id|size
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|to-&gt;blue
op_plus
id|tooff
comma
id|from-&gt;blue
op_plus
id|fromoff
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|from-&gt;transp
op_logical_and
id|to-&gt;transp
)paren
id|memcpy
c_func
(paren
id|to-&gt;transp
op_plus
id|tooff
comma
id|from-&gt;transp
op_plus
id|fromoff
comma
id|size
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|copy_from_user
c_func
(paren
id|to-&gt;red
op_plus
id|tooff
comma
id|from-&gt;red
op_plus
id|fromoff
comma
id|size
)paren
suffix:semicolon
id|copy_from_user
c_func
(paren
id|to-&gt;green
op_plus
id|tooff
comma
id|from-&gt;green
op_plus
id|fromoff
comma
id|size
)paren
suffix:semicolon
id|copy_from_user
c_func
(paren
id|to-&gt;blue
op_plus
id|tooff
comma
id|from-&gt;blue
op_plus
id|fromoff
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|from-&gt;transp
op_logical_and
id|to-&gt;transp
)paren
id|copy_from_user
c_func
(paren
id|to-&gt;transp
op_plus
id|tooff
comma
id|from-&gt;transp
op_plus
id|fromoff
comma
id|size
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|copy_to_user
c_func
(paren
id|to-&gt;red
op_plus
id|tooff
comma
id|from-&gt;red
op_plus
id|fromoff
comma
id|size
)paren
suffix:semicolon
id|copy_to_user
c_func
(paren
id|to-&gt;green
op_plus
id|tooff
comma
id|from-&gt;green
op_plus
id|fromoff
comma
id|size
)paren
suffix:semicolon
id|copy_to_user
c_func
(paren
id|to-&gt;blue
op_plus
id|tooff
comma
id|from-&gt;blue
op_plus
id|fromoff
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|from-&gt;transp
op_logical_and
id|to-&gt;transp
)paren
id|copy_to_user
c_func
(paren
id|to-&gt;transp
op_plus
id|tooff
comma
id|from-&gt;transp
op_plus
id|fromoff
comma
id|size
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/**&n; *&t;fb_set_cmap - set the colormap&n; *&t;@cmap: frame buffer colormap structure&n; *&t;@kspc: boolean, 0 copy local, 1 get_user() function&n; *&t;@info: frame buffer info structure&n; *&n; *&t;Sets the colormap @cmap for a screen of device @info.&n; *&n; *&t;Returns negative errno on error, or zero on success.&n; *&n; */
DECL|function|fb_set_cmap
r_int
id|fb_set_cmap
c_func
(paren
r_struct
id|fb_cmap
op_star
id|cmap
comma
r_int
id|kspc
comma
r_struct
id|fb_info
op_star
id|info
)paren
(brace
r_int
id|i
comma
id|start
suffix:semicolon
id|u16
op_star
id|red
comma
op_star
id|green
comma
op_star
id|blue
comma
op_star
id|transp
suffix:semicolon
id|u_int
id|hred
comma
id|hgreen
comma
id|hblue
comma
id|htransp
suffix:semicolon
id|red
op_assign
id|cmap-&gt;red
suffix:semicolon
id|green
op_assign
id|cmap-&gt;green
suffix:semicolon
id|blue
op_assign
id|cmap-&gt;blue
suffix:semicolon
id|transp
op_assign
id|cmap-&gt;transp
suffix:semicolon
id|start
op_assign
id|cmap-&gt;start
suffix:semicolon
r_if
c_cond
(paren
id|start
OL
l_int|0
op_logical_or
op_logical_neg
id|info-&gt;fbops-&gt;fb_setcolreg
)paren
r_return
op_minus
id|EINVAL
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
id|cmap-&gt;len
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|kspc
)paren
(brace
id|hred
op_assign
op_star
id|red
suffix:semicolon
id|hgreen
op_assign
op_star
id|green
suffix:semicolon
id|hblue
op_assign
op_star
id|blue
suffix:semicolon
id|htransp
op_assign
id|transp
ques
c_cond
op_star
id|transp
suffix:colon
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|get_user
c_func
(paren
id|hred
comma
id|red
)paren
suffix:semicolon
id|get_user
c_func
(paren
id|hgreen
comma
id|green
)paren
suffix:semicolon
id|get_user
c_func
(paren
id|hblue
comma
id|blue
)paren
suffix:semicolon
r_if
c_cond
(paren
id|transp
)paren
id|get_user
c_func
(paren
id|htransp
comma
id|transp
)paren
suffix:semicolon
r_else
id|htransp
op_assign
l_int|0
suffix:semicolon
)brace
id|red
op_increment
suffix:semicolon
id|green
op_increment
suffix:semicolon
id|blue
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|transp
)paren
id|transp
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;fbops
op_member_access_from_pointer
id|fb_setcolreg
c_func
(paren
id|start
op_increment
comma
id|hred
comma
id|hgreen
comma
id|hblue
comma
id|htransp
comma
id|info
)paren
)paren
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;fb_default_cmap - get default colormap&n; *&t;@len: size of palette for a depth&n; *&n; *&t;Gets the default colormap for a specific screen depth.  @len&n; *&t;is the size of the palette for a particular screen depth.&n; *&n; *&t;Returns pointer to a frame buffer colormap structure.&n; *&n; */
DECL|function|fb_default_cmap
r_struct
id|fb_cmap
op_star
id|fb_default_cmap
c_func
(paren
r_int
id|len
)paren
(brace
r_if
c_cond
(paren
id|len
op_le
l_int|2
)paren
r_return
op_amp
id|default_2_colors
suffix:semicolon
r_if
c_cond
(paren
id|len
op_le
l_int|4
)paren
r_return
op_amp
id|default_4_colors
suffix:semicolon
r_if
c_cond
(paren
id|len
op_le
l_int|8
)paren
r_return
op_amp
id|default_8_colors
suffix:semicolon
r_return
op_amp
id|default_16_colors
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;fb_invert_cmaps - invert all defaults colormaps&n; *&n; *&t;Invert all default colormaps.&n; *&n; */
DECL|function|fb_invert_cmaps
r_void
id|fb_invert_cmaps
c_func
(paren
r_void
)paren
(brace
id|u_int
id|i
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
l_int|2
suffix:semicolon
id|i
op_increment
)paren
(brace
id|red2
(braket
id|i
)braket
op_assign
op_complement
id|red2
(braket
id|i
)braket
suffix:semicolon
id|green2
(braket
id|i
)braket
op_assign
op_complement
id|green2
(braket
id|i
)braket
suffix:semicolon
id|blue2
(braket
id|i
)braket
op_assign
op_complement
id|blue2
(braket
id|i
)braket
suffix:semicolon
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
l_int|4
suffix:semicolon
id|i
op_increment
)paren
(brace
id|red4
(braket
id|i
)braket
op_assign
op_complement
id|red4
(braket
id|i
)braket
suffix:semicolon
id|green4
(braket
id|i
)braket
op_assign
op_complement
id|green4
(braket
id|i
)braket
suffix:semicolon
id|blue4
(braket
id|i
)braket
op_assign
op_complement
id|blue4
(braket
id|i
)braket
suffix:semicolon
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
l_int|8
suffix:semicolon
id|i
op_increment
)paren
(brace
id|red8
(braket
id|i
)braket
op_assign
op_complement
id|red8
(braket
id|i
)braket
suffix:semicolon
id|green8
(braket
id|i
)braket
op_assign
op_complement
id|green8
(braket
id|i
)braket
suffix:semicolon
id|blue8
(braket
id|i
)braket
op_assign
op_complement
id|blue8
(braket
id|i
)braket
suffix:semicolon
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
l_int|16
suffix:semicolon
id|i
op_increment
)paren
(brace
id|red16
(braket
id|i
)braket
op_assign
op_complement
id|red16
(braket
id|i
)braket
suffix:semicolon
id|green16
(braket
id|i
)braket
op_assign
op_complement
id|green16
(braket
id|i
)braket
suffix:semicolon
id|blue16
(braket
id|i
)braket
op_assign
op_complement
id|blue16
(braket
id|i
)braket
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;     *  Visible symbols for modules&n;     */
DECL|variable|fb_alloc_cmap
id|EXPORT_SYMBOL
c_func
(paren
id|fb_alloc_cmap
)paren
suffix:semicolon
DECL|variable|fb_dealloc_cmap
id|EXPORT_SYMBOL
c_func
(paren
id|fb_dealloc_cmap
)paren
suffix:semicolon
DECL|variable|fb_copy_cmap
id|EXPORT_SYMBOL
c_func
(paren
id|fb_copy_cmap
)paren
suffix:semicolon
DECL|variable|fb_set_cmap
id|EXPORT_SYMBOL
c_func
(paren
id|fb_set_cmap
)paren
suffix:semicolon
DECL|variable|fb_default_cmap
id|EXPORT_SYMBOL
c_func
(paren
id|fb_default_cmap
)paren
suffix:semicolon
DECL|variable|fb_invert_cmaps
id|EXPORT_SYMBOL
c_func
(paren
id|fb_invert_cmaps
)paren
suffix:semicolon
eof
