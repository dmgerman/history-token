multiline_comment|/*&n; * linux/drivers/video/fbgen.c -- Generic routines for frame buffer devices&n; *&n; *  Created 3 Jan 1998 by Geert Uytterhoeven&n; *&n; *&t;2001 - Documented with DocBook&n; *&t;- Brad Douglas &lt;brad@neruo.com&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file COPYING in the main directory of this archive&n; * for more details.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/fb.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;video/fbcon.h&gt;
macro_line|#include &lt;video/fbcon-mfb.h&gt;
macro_line|#include &lt;video/fbcon-cfb2.h&gt;
macro_line|#include &lt;video/fbcon-cfb4.h&gt;
macro_line|#include &lt;video/fbcon-cfb8.h&gt;
macro_line|#include &lt;video/fbcon-cfb16.h&gt;
macro_line|#include &lt;video/fbcon-cfb24.h&gt;
macro_line|#include &lt;video/fbcon-cfb32.h&gt;
macro_line|#include &quot;fbcon-accel.h&quot;
multiline_comment|/* ---- `Generic&squot; versions of the frame buffer device operations ----------- */
multiline_comment|/**&n; *&t;fbgen_get_fix - get fixed part of display&n; *&t;@fix: fb_fix_screeninfo structure&n; *&t;@con: virtual console number&n; *&t;@info: frame buffer info structure&n; *&n; *&t;Get the fixed information part of the display and place it&n; *&t;into @fix for virtual console @con on device @info.&n; *&n; *&t;Returns negative errno on error, or zero on success.&n; *&n; */
DECL|function|fbgen_get_fix
r_int
id|fbgen_get_fix
c_func
(paren
r_struct
id|fb_fix_screeninfo
op_star
id|fix
comma
r_int
id|con
comma
r_struct
id|fb_info
op_star
id|info
)paren
(brace
r_struct
id|fb_info_gen
op_star
id|info2
op_assign
(paren
r_struct
id|fb_info_gen
op_star
)paren
id|info
suffix:semicolon
r_struct
id|fbgen_hwswitch
op_star
id|fbhw
op_assign
id|info2-&gt;fbhw
suffix:semicolon
r_char
id|par
(braket
id|info2-&gt;parsize
)braket
suffix:semicolon
r_if
c_cond
(paren
id|con
op_eq
op_minus
l_int|1
)paren
id|fbhw
op_member_access_from_pointer
id|get_par
c_func
(paren
op_amp
id|par
comma
id|info2
)paren
suffix:semicolon
r_else
(brace
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|fbhw
op_member_access_from_pointer
id|decode_var
c_func
(paren
op_amp
id|fb_display
(braket
id|con
)braket
dot
id|var
comma
op_amp
id|par
comma
id|info2
)paren
)paren
)paren
r_return
id|err
suffix:semicolon
)brace
id|memset
c_func
(paren
id|fix
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|fb_fix_screeninfo
)paren
)paren
suffix:semicolon
r_return
id|fbhw
op_member_access_from_pointer
id|encode_fix
c_func
(paren
id|fix
comma
op_amp
id|par
comma
id|info2
)paren
suffix:semicolon
)brace
DECL|function|gen_get_fix
r_int
id|gen_get_fix
c_func
(paren
r_struct
id|fb_fix_screeninfo
op_star
id|fix
comma
r_int
id|con
comma
r_struct
id|fb_info
op_star
id|info
)paren
(brace
op_star
id|fix
op_assign
id|info-&gt;fix
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;fbgen_get_var - get user defined part of display&n; *&t;@var: fb_var_screeninfo structure&n; *&t;@con: virtual console number&n; *&t;@info: frame buffer info structure&n; *&n; *&t;Get the user defined part of the display and place it into @var&n; *&t;for virtual console @con on device @info.&n; *&n; *&t;Returns negative errno on error, or zero for success.&n; *&n; */
DECL|function|fbgen_get_var
r_int
id|fbgen_get_var
c_func
(paren
r_struct
id|fb_var_screeninfo
op_star
id|var
comma
r_int
id|con
comma
r_struct
id|fb_info
op_star
id|info
)paren
(brace
r_struct
id|fb_info_gen
op_star
id|info2
op_assign
(paren
r_struct
id|fb_info_gen
op_star
)paren
id|info
suffix:semicolon
r_struct
id|fbgen_hwswitch
op_star
id|fbhw
op_assign
id|info2-&gt;fbhw
suffix:semicolon
r_char
id|par
(braket
id|info2-&gt;parsize
)braket
suffix:semicolon
r_if
c_cond
(paren
id|con
op_eq
op_minus
l_int|1
)paren
(brace
id|fbhw
op_member_access_from_pointer
id|get_par
c_func
(paren
op_amp
id|par
comma
id|info2
)paren
suffix:semicolon
id|fbhw
op_member_access_from_pointer
id|encode_var
c_func
(paren
id|var
comma
op_amp
id|par
comma
id|info2
)paren
suffix:semicolon
)brace
r_else
op_star
id|var
op_assign
id|fb_display
(braket
id|con
)braket
dot
id|var
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|gen_get_var
r_int
id|gen_get_var
c_func
(paren
r_struct
id|fb_var_screeninfo
op_star
id|var
comma
r_int
id|con
comma
r_struct
id|fb_info
op_star
id|info
)paren
(brace
op_star
id|var
op_assign
id|info-&gt;var
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;fbgen_set_var - set the user defined part of display&n; *&t;@var: fb_var_screeninfo user defined part of the display&n; *&t;@con: virtual console number&n; *&t;@info: frame buffer info structure&n; *&n; *&t;Set the user defined part of the display as dictated by @var&n; *&t;for virtual console @con on device @info.&n; *&n; *&t;Returns negative errno on error, or zero for success.&n; *&n; */
DECL|function|fbgen_set_var
r_int
id|fbgen_set_var
c_func
(paren
r_struct
id|fb_var_screeninfo
op_star
id|var
comma
r_int
id|con
comma
r_struct
id|fb_info
op_star
id|info
)paren
(brace
r_struct
id|fb_info_gen
op_star
id|info2
op_assign
(paren
r_struct
id|fb_info_gen
op_star
)paren
id|info
suffix:semicolon
r_int
id|err
suffix:semicolon
r_int
id|oldxres
comma
id|oldyres
comma
id|oldbpp
comma
id|oldxres_virtual
comma
id|oldyres_virtual
comma
id|oldyoffset
suffix:semicolon
r_struct
id|fb_bitfield
id|oldred
comma
id|oldgreen
comma
id|oldblue
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|fbgen_do_set_var
c_func
(paren
id|var
comma
id|con
op_eq
id|info-&gt;currcon
comma
id|info2
)paren
)paren
)paren
r_return
id|err
suffix:semicolon
r_if
c_cond
(paren
(paren
id|var-&gt;activate
op_amp
id|FB_ACTIVATE_MASK
)paren
op_eq
id|FB_ACTIVATE_NOW
)paren
(brace
id|oldxres
op_assign
id|fb_display
(braket
id|con
)braket
dot
id|var.xres
suffix:semicolon
id|oldyres
op_assign
id|fb_display
(braket
id|con
)braket
dot
id|var.yres
suffix:semicolon
id|oldxres_virtual
op_assign
id|fb_display
(braket
id|con
)braket
dot
id|var.xres_virtual
suffix:semicolon
id|oldyres_virtual
op_assign
id|fb_display
(braket
id|con
)braket
dot
id|var.yres_virtual
suffix:semicolon
id|oldbpp
op_assign
id|fb_display
(braket
id|con
)braket
dot
id|var.bits_per_pixel
suffix:semicolon
id|oldred
op_assign
id|fb_display
(braket
id|con
)braket
dot
id|var.red
suffix:semicolon
id|oldgreen
op_assign
id|fb_display
(braket
id|con
)braket
dot
id|var.green
suffix:semicolon
id|oldblue
op_assign
id|fb_display
(braket
id|con
)braket
dot
id|var.blue
suffix:semicolon
id|oldyoffset
op_assign
id|fb_display
(braket
id|con
)braket
dot
id|var.yoffset
suffix:semicolon
id|fb_display
(braket
id|con
)braket
dot
id|var
op_assign
op_star
id|var
suffix:semicolon
r_if
c_cond
(paren
id|oldxres
op_ne
id|var-&gt;xres
op_logical_or
id|oldyres
op_ne
id|var-&gt;yres
op_logical_or
id|oldxres_virtual
op_ne
id|var-&gt;xres_virtual
op_logical_or
id|oldyres_virtual
op_ne
id|var-&gt;yres_virtual
op_logical_or
id|oldbpp
op_ne
id|var-&gt;bits_per_pixel
op_logical_or
(paren
op_logical_neg
(paren
id|memcmp
c_func
(paren
op_amp
id|oldred
comma
op_amp
(paren
id|var-&gt;red
)paren
comma
r_sizeof
(paren
r_struct
id|fb_bitfield
)paren
)paren
)paren
)paren
op_logical_or
(paren
op_logical_neg
(paren
id|memcmp
c_func
(paren
op_amp
id|oldgreen
comma
op_amp
(paren
id|var-&gt;green
)paren
comma
r_sizeof
(paren
r_struct
id|fb_bitfield
)paren
)paren
)paren
)paren
op_logical_or
(paren
op_logical_neg
(paren
id|memcmp
c_func
(paren
op_amp
id|oldblue
comma
op_amp
(paren
id|var-&gt;blue
)paren
comma
r_sizeof
(paren
r_struct
id|fb_bitfield
)paren
)paren
)paren
)paren
op_logical_or
id|oldyoffset
op_ne
id|var-&gt;yoffset
)paren
(brace
id|fbgen_set_disp
c_func
(paren
id|con
comma
id|info2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;changevar
)paren
(paren
op_star
id|info-&gt;changevar
)paren
(paren
id|con
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|fb_alloc_cmap
c_func
(paren
op_amp
id|fb_display
(braket
id|con
)braket
dot
id|cmap
comma
l_int|0
comma
l_int|0
)paren
)paren
)paren
r_return
id|err
suffix:semicolon
id|do_install_cmap
c_func
(paren
id|con
comma
id|info
)paren
suffix:semicolon
)brace
)brace
id|var-&gt;activate
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|gen_set_var
r_int
id|gen_set_var
c_func
(paren
r_struct
id|fb_var_screeninfo
op_star
id|var
comma
r_int
id|con
comma
r_struct
id|fb_info
op_star
id|info
)paren
(brace
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
id|con
OL
l_int|0
op_logical_or
(paren
id|memcmp
c_func
(paren
op_amp
id|info-&gt;var
comma
id|var
comma
r_sizeof
(paren
r_struct
id|fb_var_screeninfo
)paren
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|info-&gt;fbops-&gt;fb_check_var
)paren
(brace
op_star
id|var
op_assign
id|info-&gt;var
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|err
op_assign
id|info-&gt;fbops
op_member_access_from_pointer
id|fb_check_var
c_func
(paren
id|var
comma
id|info
)paren
)paren
)paren
r_return
id|err
suffix:semicolon
r_if
c_cond
(paren
(paren
id|var-&gt;activate
op_amp
id|FB_ACTIVATE_MASK
)paren
op_eq
id|FB_ACTIVATE_NOW
)paren
(brace
id|info-&gt;var
op_assign
op_star
id|var
suffix:semicolon
r_if
c_cond
(paren
id|con
op_eq
id|info-&gt;currcon
)paren
(brace
r_if
c_cond
(paren
id|info-&gt;fbops-&gt;fb_set_par
)paren
id|info-&gt;fbops
op_member_access_from_pointer
id|fb_set_par
c_func
(paren
id|info
)paren
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;fbops-&gt;fb_pan_display
)paren
id|info-&gt;fbops
op_member_access_from_pointer
id|fb_pan_display
c_func
(paren
op_amp
id|info-&gt;var
comma
id|con
comma
id|info
)paren
suffix:semicolon
id|gen_set_disp
c_func
(paren
id|con
comma
id|info
)paren
suffix:semicolon
id|fb_set_cmap
c_func
(paren
op_amp
id|info-&gt;cmap
comma
l_int|1
comma
id|info
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|info-&gt;changevar
)paren
id|info
op_member_access_from_pointer
id|changevar
c_func
(paren
id|con
)paren
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;fbgen_get_cmap - get the colormap&n; *&t;@cmap: frame buffer colormap structure&n; *&t;@kspc: boolean, 0 copy local, 1 put_user() function&n; *&t;@con: virtual console number&n; *&t;@info: frame buffer info structure&n; *&n; *&t;Gets the colormap for virtual console @con and places it into&n; *&t;@cmap for device @info.&n; *&n; *&t;Returns negative errno on error, or zero for success.&n; *&n; */
DECL|function|fbgen_get_cmap
r_int
id|fbgen_get_cmap
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
r_int
id|con
comma
r_struct
id|fb_info
op_star
id|info
)paren
(brace
r_struct
id|fb_info_gen
op_star
id|info2
op_assign
(paren
r_struct
id|fb_info_gen
op_star
)paren
id|info
suffix:semicolon
r_struct
id|fbgen_hwswitch
op_star
id|fbhw
op_assign
id|info2-&gt;fbhw
suffix:semicolon
r_if
c_cond
(paren
id|con
op_eq
id|info-&gt;currcon
)paren
multiline_comment|/* current console ? */
r_return
id|fb_get_cmap
c_func
(paren
id|cmap
comma
id|kspc
comma
id|fbhw-&gt;getcolreg
comma
id|info
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|fb_display
(braket
id|con
)braket
dot
id|cmap.len
)paren
multiline_comment|/* non default colormap ? */
id|fb_copy_cmap
c_func
(paren
op_amp
id|fb_display
(braket
id|con
)braket
dot
id|cmap
comma
id|cmap
comma
id|kspc
ques
c_cond
l_int|0
suffix:colon
l_int|2
)paren
suffix:semicolon
r_else
(brace
r_int
id|size
op_assign
id|fb_display
(braket
id|con
)braket
dot
id|var.bits_per_pixel
op_eq
l_int|16
ques
c_cond
l_int|64
suffix:colon
l_int|256
suffix:semicolon
id|fb_copy_cmap
c_func
(paren
id|fb_default_cmap
c_func
(paren
id|size
)paren
comma
id|cmap
comma
id|kspc
ques
c_cond
l_int|0
suffix:colon
l_int|2
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|gen_get_cmap
r_int
id|gen_get_cmap
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
r_int
id|con
comma
r_struct
id|fb_info
op_star
id|info
)paren
(brace
id|fb_copy_cmap
(paren
op_amp
id|info-&gt;cmap
comma
id|cmap
comma
id|kspc
ques
c_cond
l_int|0
suffix:colon
l_int|2
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;fbgen_set_cmap - set the colormap&n; *&t;@cmap: frame buffer colormap structure&n; *&t;@kspc: boolean, 0 copy local, 1 get_user() function&n; *&t;@con: virtual console number&n; *&t;@info: frame buffer info structure&n; *&n; *&t;Sets the colormap @cmap for virtual console @con on&n; *&t;device @info.&n; *&n; *&t;Returns negative errno on error, or zero for success.&n; *&n; */
DECL|function|fbgen_set_cmap
r_int
id|fbgen_set_cmap
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
r_int
id|con
comma
r_struct
id|fb_info
op_star
id|info
)paren
(brace
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fb_display
(braket
id|con
)braket
dot
id|cmap.len
)paren
(brace
multiline_comment|/* no colormap allocated ? */
r_int
id|size
op_assign
id|fb_display
(braket
id|con
)braket
dot
id|var.bits_per_pixel
op_eq
l_int|16
ques
c_cond
l_int|64
suffix:colon
l_int|256
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|fb_alloc_cmap
c_func
(paren
op_amp
id|fb_display
(braket
id|con
)braket
dot
id|cmap
comma
id|size
comma
l_int|0
)paren
)paren
)paren
r_return
id|err
suffix:semicolon
)brace
r_if
c_cond
(paren
id|con
op_eq
id|info-&gt;currcon
)paren
multiline_comment|/* current console ? */
r_return
id|fb_set_cmap
c_func
(paren
id|cmap
comma
id|kspc
comma
id|info
)paren
suffix:semicolon
r_else
id|fb_copy_cmap
c_func
(paren
id|cmap
comma
op_amp
id|fb_display
(braket
id|con
)braket
dot
id|cmap
comma
id|kspc
ques
c_cond
l_int|0
suffix:colon
l_int|1
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|gen_set_cmap
r_int
id|gen_set_cmap
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
r_int
id|con
comma
r_struct
id|fb_info
op_star
id|info
)paren
(brace
r_struct
id|display
op_star
id|disp
op_assign
(paren
id|con
OL
l_int|0
)paren
ques
c_cond
id|info-&gt;disp
suffix:colon
(paren
id|fb_display
op_plus
id|con
)paren
suffix:semicolon
r_struct
id|fb_cmap
op_star
id|dcmap
op_assign
op_amp
id|disp-&gt;cmap
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* No colormap allocated ? */
r_if
c_cond
(paren
op_logical_neg
id|dcmap-&gt;len
)paren
(brace
r_int
id|size
op_assign
id|info-&gt;cmap.len
suffix:semicolon
id|err
op_assign
id|fb_alloc_cmap
c_func
(paren
id|dcmap
comma
id|size
comma
l_int|0
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|err
op_logical_and
id|con
op_eq
id|info-&gt;currcon
)paren
(brace
id|err
op_assign
id|fb_set_cmap
c_func
(paren
id|cmap
comma
id|kspc
comma
id|info
)paren
suffix:semicolon
id|dcmap
op_assign
op_amp
id|info-&gt;cmap
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|err
)paren
id|fb_copy_cmap
c_func
(paren
id|cmap
comma
id|dcmap
comma
id|kspc
ques
c_cond
l_int|0
suffix:colon
l_int|1
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;fbgen_pan_display - pan or wrap the display&n; *&t;@var: frame buffer user defined part of display&n; *&t;@con: virtual console number&n; *&t;@info: frame buffer info structure&n; *&n; *&t;Pan or wrap virtual console @con for device @info.&n; *&n; *&t;This call looks only at xoffset, yoffset and the&n; *&t;FB_VMODE_YWRAP flag in @var.&n; *&n; *&t;Returns negative errno on error, or zero for success.&n; *&n; */
DECL|function|fbgen_pan_display
r_int
id|fbgen_pan_display
c_func
(paren
r_struct
id|fb_var_screeninfo
op_star
id|var
comma
r_int
id|con
comma
r_struct
id|fb_info
op_star
id|info
)paren
(brace
r_struct
id|fb_info_gen
op_star
id|info2
op_assign
(paren
r_struct
id|fb_info_gen
op_star
)paren
id|info
suffix:semicolon
r_struct
id|fbgen_hwswitch
op_star
id|fbhw
op_assign
id|info2-&gt;fbhw
suffix:semicolon
r_int
id|xoffset
op_assign
id|var-&gt;xoffset
suffix:semicolon
r_int
id|yoffset
op_assign
id|var-&gt;yoffset
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
id|xoffset
template_param
id|fb_display
(braket
id|con
)braket
dot
id|var.xres_virtual
op_logical_or
id|yoffset
template_param
id|fb_display
(braket
id|con
)braket
dot
id|var.yres_virtual
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|con
op_eq
id|info-&gt;currcon
)paren
(brace
r_if
c_cond
(paren
id|fbhw-&gt;pan_display
)paren
(brace
r_if
c_cond
(paren
(paren
id|err
op_assign
id|fbhw
op_member_access_from_pointer
id|pan_display
c_func
(paren
id|var
comma
id|info2
)paren
)paren
)paren
r_return
id|err
suffix:semicolon
)brace
r_else
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|fb_display
(braket
id|con
)braket
dot
id|var.xoffset
op_assign
id|var-&gt;xoffset
suffix:semicolon
id|fb_display
(braket
id|con
)braket
dot
id|var.yoffset
op_assign
id|var-&gt;yoffset
suffix:semicolon
r_if
c_cond
(paren
id|var-&gt;vmode
op_amp
id|FB_VMODE_YWRAP
)paren
id|fb_display
(braket
id|con
)braket
dot
id|var.vmode
op_or_assign
id|FB_VMODE_YWRAP
suffix:semicolon
r_else
id|fb_display
(braket
id|con
)braket
dot
id|var.vmode
op_and_assign
op_complement
id|FB_VMODE_YWRAP
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* ---- Helper functions --------------------------------------------------- */
multiline_comment|/**&n; *&t;fbgen_do_set_var - change the video mode&n; *&t;@var: frame buffer user defined part of display&n; *&t;@isactive: boolean, 0 inactive, 1 active&n; *&t;@info: generic frame buffer info structure&n; *&n; *&t;Change the video mode settings for device @info.  If @isactive&n; *&t;is non-zero, the changes will be activated immediately.&n; *&n; *&t;Return negative errno on error, or zero for success.&n; *&n; */
DECL|function|fbgen_do_set_var
r_int
id|fbgen_do_set_var
c_func
(paren
r_struct
id|fb_var_screeninfo
op_star
id|var
comma
r_int
id|isactive
comma
r_struct
id|fb_info_gen
op_star
id|info
)paren
(brace
r_struct
id|fbgen_hwswitch
op_star
id|fbhw
op_assign
id|info-&gt;fbhw
suffix:semicolon
r_int
id|err
comma
id|activate
suffix:semicolon
r_char
id|par
(braket
id|info-&gt;parsize
)braket
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|fbhw
op_member_access_from_pointer
id|decode_var
c_func
(paren
id|var
comma
op_amp
id|par
comma
id|info
)paren
)paren
)paren
r_return
id|err
suffix:semicolon
id|activate
op_assign
id|var-&gt;activate
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|var-&gt;activate
op_amp
id|FB_ACTIVATE_MASK
)paren
op_eq
id|FB_ACTIVATE_NOW
)paren
op_logical_and
id|isactive
)paren
id|fbhw
op_member_access_from_pointer
id|set_par
c_func
(paren
op_amp
id|par
comma
id|info
)paren
suffix:semicolon
id|fbhw
op_member_access_from_pointer
id|encode_var
c_func
(paren
id|var
comma
op_amp
id|par
comma
id|info
)paren
suffix:semicolon
id|var-&gt;activate
op_assign
id|activate
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;fbgen_set_disp - set generic display&n; *&t;@con: virtual console number&n; *&t;@info: generic frame buffer info structure&n; *&n; *&t;Sets a display on virtual console @con for device @info.&n; *&n; */
DECL|function|fbgen_set_disp
r_void
id|fbgen_set_disp
c_func
(paren
r_int
id|con
comma
r_struct
id|fb_info_gen
op_star
id|info
)paren
(brace
r_struct
id|fbgen_hwswitch
op_star
id|fbhw
op_assign
id|info-&gt;fbhw
suffix:semicolon
r_struct
id|fb_fix_screeninfo
id|fix
suffix:semicolon
r_char
id|par
(braket
id|info-&gt;parsize
)braket
suffix:semicolon
r_struct
id|display
op_star
id|display
suffix:semicolon
r_if
c_cond
(paren
id|con
op_ge
l_int|0
)paren
id|display
op_assign
op_amp
id|fb_display
(braket
id|con
)braket
suffix:semicolon
r_else
id|display
op_assign
id|info-&gt;info.disp
suffix:semicolon
multiline_comment|/* used during initialization */
r_if
c_cond
(paren
id|con
op_eq
op_minus
l_int|1
)paren
id|fbhw
op_member_access_from_pointer
id|get_par
c_func
(paren
op_amp
id|par
comma
id|info
)paren
suffix:semicolon
r_else
id|fbhw
op_member_access_from_pointer
id|decode_var
c_func
(paren
op_amp
id|fb_display
(braket
id|con
)braket
dot
id|var
comma
op_amp
id|par
comma
id|info
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|fix
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|fb_fix_screeninfo
)paren
)paren
suffix:semicolon
id|fbhw
op_member_access_from_pointer
id|encode_fix
c_func
(paren
op_amp
id|fix
comma
op_amp
id|par
comma
id|info
)paren
suffix:semicolon
id|display-&gt;visual
op_assign
id|fix.visual
suffix:semicolon
id|display-&gt;type
op_assign
id|fix.type
suffix:semicolon
id|display-&gt;type_aux
op_assign
id|fix.type_aux
suffix:semicolon
id|display-&gt;ypanstep
op_assign
id|fix.ypanstep
suffix:semicolon
id|display-&gt;ywrapstep
op_assign
id|fix.ywrapstep
suffix:semicolon
id|display-&gt;line_length
op_assign
id|fix.line_length
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;fbhw-&gt;blank
op_logical_or
id|fix.visual
op_eq
id|FB_VISUAL_PSEUDOCOLOR
op_logical_or
id|fix.visual
op_eq
id|FB_VISUAL_DIRECTCOLOR
)paren
id|display-&gt;can_soft_blank
op_assign
l_int|1
suffix:semicolon
r_else
id|display-&gt;can_soft_blank
op_assign
l_int|0
suffix:semicolon
id|fbhw
op_member_access_from_pointer
id|set_disp
c_func
(paren
op_amp
id|par
comma
id|display
comma
id|info
)paren
suffix:semicolon
macro_line|#if 0 /* FIXME: generic inverse is not supported yet */
id|display-&gt;inverse
op_assign
(paren
id|fix.visual
op_eq
id|FB_VISUAL_MONO01
ques
c_cond
op_logical_neg
id|inverse
suffix:colon
id|inverse
)paren
suffix:semicolon
macro_line|#else
id|display-&gt;inverse
op_assign
id|fix.visual
op_eq
id|FB_VISUAL_MONO01
suffix:semicolon
macro_line|#endif
)brace
DECL|function|gen_set_disp
r_void
id|gen_set_disp
c_func
(paren
r_int
id|con
comma
r_struct
id|fb_info
op_star
id|info
)paren
(brace
r_struct
id|display
op_star
id|display
op_assign
(paren
id|con
OL
l_int|0
)paren
ques
c_cond
id|info-&gt;disp
suffix:colon
(paren
id|fb_display
op_plus
id|con
)paren
suffix:semicolon
id|display-&gt;visual
op_assign
id|info-&gt;fix.visual
suffix:semicolon
id|display-&gt;type
op_assign
id|info-&gt;fix.type
suffix:semicolon
id|display-&gt;type_aux
op_assign
id|info-&gt;fix.type_aux
suffix:semicolon
id|display-&gt;ypanstep
op_assign
id|info-&gt;fix.ypanstep
suffix:semicolon
id|display-&gt;ywrapstep
op_assign
id|info-&gt;fix.ywrapstep
suffix:semicolon
id|display-&gt;line_length
op_assign
id|info-&gt;fix.line_length
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;fix.visual
op_eq
id|FB_VISUAL_PSEUDOCOLOR
op_logical_or
id|info-&gt;fix.visual
op_eq
id|FB_VISUAL_DIRECTCOLOR
)paren
(brace
id|display-&gt;can_soft_blank
op_assign
id|info-&gt;fbops-&gt;fb_blank
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
id|display-&gt;dispsw_data
op_assign
l_int|NULL
suffix:semicolon
)brace
r_else
(brace
id|display-&gt;can_soft_blank
op_assign
l_int|0
suffix:semicolon
id|display-&gt;dispsw_data
op_assign
id|info-&gt;pseudo_palette
suffix:semicolon
)brace
id|display-&gt;var
op_assign
id|info-&gt;var
suffix:semicolon
multiline_comment|/*&n;&t; * If we are setting all the virtual consoles, also set&n;&t; * the defaults used to create new consoles.&n;&t; */
r_if
c_cond
(paren
id|con
OL
l_int|0
op_logical_or
id|info-&gt;var.activate
op_amp
id|FB_ACTIVATE_ALL
)paren
id|info-&gt;disp-&gt;var
op_assign
id|info-&gt;var
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;var.bits_per_pixel
op_eq
l_int|24
)paren
(brace
macro_line|#ifdef FBCON_HAS_CFB24
id|display-&gt;scrollmode
op_assign
id|SCROLL_YREDRAW
suffix:semicolon
id|display-&gt;dispsw
op_assign
op_amp
id|fbcon_cfb24
suffix:semicolon
r_return
suffix:semicolon
macro_line|#endif
)brace
macro_line|#ifdef FBCON_HAS_ACCEL
id|display-&gt;scrollmode
op_assign
id|SCROLL_YNOMOVE
suffix:semicolon
id|display-&gt;dispsw
op_assign
op_amp
id|fbcon_accel
suffix:semicolon
macro_line|#endif
r_return
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;do_install_cmap - install the current colormap&n; *&t;@con: virtual console number&n; *&t;@info: generic frame buffer info structure&n; *&n; *&t;Installs the current colormap for virtual console @con on&n; *&t;device @info.&n; *&n; */
DECL|function|do_install_cmap
r_void
id|do_install_cmap
c_func
(paren
r_int
id|con
comma
r_struct
id|fb_info
op_star
id|info
)paren
(brace
r_if
c_cond
(paren
id|con
op_ne
id|info-&gt;currcon
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|fb_display
(braket
id|con
)braket
dot
id|cmap.len
)paren
id|fb_set_cmap
c_func
(paren
op_amp
id|fb_display
(braket
id|con
)braket
dot
id|cmap
comma
l_int|1
comma
id|info
)paren
suffix:semicolon
r_else
(brace
r_int
id|size
op_assign
id|fb_display
(braket
id|con
)braket
dot
id|var.bits_per_pixel
op_eq
l_int|16
ques
c_cond
l_int|64
suffix:colon
l_int|256
suffix:semicolon
id|fb_set_cmap
c_func
(paren
id|fb_default_cmap
c_func
(paren
id|size
)paren
comma
l_int|1
comma
id|info
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/**&n; *&t;fbgen_update_var - update user defined part of display&n; *&t;@con: virtual console number&n; *&t;@info: frame buffer info structure&n; *&n; *&t;Updates the user defined part of the display (&squot;var&squot;&n; *&t;structure) on virtual console @con for device @info.&n; *&t;This function is called by fbcon.c.&n; *&n; *&t;Returns negative errno on error, or zero for success.&n; *&n; */
DECL|function|fbgen_update_var
r_int
id|fbgen_update_var
c_func
(paren
r_int
id|con
comma
r_struct
id|fb_info
op_star
id|info
)paren
(brace
r_struct
id|fb_info_gen
op_star
id|info2
op_assign
(paren
r_struct
id|fb_info_gen
op_star
)paren
id|info
suffix:semicolon
r_struct
id|fbgen_hwswitch
op_star
id|fbhw
op_assign
id|info2-&gt;fbhw
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
id|fbhw-&gt;pan_display
)paren
(brace
r_if
c_cond
(paren
(paren
id|err
op_assign
id|fbhw
op_member_access_from_pointer
id|pan_display
c_func
(paren
op_amp
id|fb_display
(braket
id|con
)braket
dot
id|var
comma
id|info2
)paren
)paren
)paren
r_return
id|err
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|gen_update_var
r_int
id|gen_update_var
c_func
(paren
r_int
id|con
comma
r_struct
id|fb_info
op_star
id|info
)paren
(brace
r_struct
id|display
op_star
id|disp
op_assign
(paren
id|con
OL
l_int|0
)paren
ques
c_cond
id|info-&gt;disp
suffix:colon
(paren
id|fb_display
op_plus
id|con
)paren
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
id|con
op_eq
id|info-&gt;currcon
)paren
(brace
id|info-&gt;var.xoffset
op_assign
id|disp-&gt;var.xoffset
suffix:semicolon
id|info-&gt;var.yoffset
op_assign
id|disp-&gt;var.yoffset
suffix:semicolon
id|info-&gt;var.vmode
op_assign
id|disp-&gt;var.vmode
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;fbops-&gt;fb_pan_display
)paren
(brace
r_if
c_cond
(paren
(paren
id|err
op_assign
id|info-&gt;fbops
op_member_access_from_pointer
id|fb_pan_display
c_func
(paren
op_amp
id|info-&gt;var
comma
id|con
comma
id|info
)paren
)paren
)paren
r_return
id|err
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;fbgen_switch - switch to a different virtual console.&n; *&t;@con: virtual console number&n; *&t;@info: frame buffer info structure&n; *&n; *&t;Switch to virtuall console @con on device @info.&n; *&n; *&t;Returns zero.&n; *&n; */
DECL|function|fbgen_switch
r_int
id|fbgen_switch
c_func
(paren
r_int
id|con
comma
r_struct
id|fb_info
op_star
id|info
)paren
(brace
r_struct
id|fb_info_gen
op_star
id|info2
op_assign
(paren
r_struct
id|fb_info_gen
op_star
)paren
id|info
suffix:semicolon
r_struct
id|fbgen_hwswitch
op_star
id|fbhw
op_assign
id|info2-&gt;fbhw
suffix:semicolon
multiline_comment|/* Do we have to save the colormap ? */
r_if
c_cond
(paren
id|fb_display
(braket
id|info-&gt;currcon
)braket
dot
id|cmap.len
)paren
id|fb_get_cmap
c_func
(paren
op_amp
id|fb_display
(braket
id|info-&gt;currcon
)braket
dot
id|cmap
comma
l_int|1
comma
id|fbhw-&gt;getcolreg
comma
op_amp
id|info2-&gt;info
)paren
suffix:semicolon
id|fbgen_do_set_var
c_func
(paren
op_amp
id|fb_display
(braket
id|con
)braket
dot
id|var
comma
l_int|1
comma
id|info2
)paren
suffix:semicolon
id|info-&gt;currcon
op_assign
id|con
suffix:semicolon
multiline_comment|/* Install new colormap */
id|do_install_cmap
c_func
(paren
id|con
comma
id|info
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|gen_switch
r_int
id|gen_switch
c_func
(paren
r_int
id|con
comma
r_struct
id|fb_info
op_star
id|info
)paren
(brace
r_struct
id|display
op_star
id|disp
suffix:semicolon
r_struct
id|fb_cmap
op_star
id|cmap
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;currcon
op_ge
l_int|0
)paren
(brace
id|disp
op_assign
id|fb_display
op_plus
id|info-&gt;currcon
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Save the old colormap and graphics mode.&n;&t;&t; */
id|disp-&gt;var
op_assign
id|info-&gt;var
suffix:semicolon
r_if
c_cond
(paren
id|disp-&gt;cmap.len
)paren
id|fb_copy_cmap
c_func
(paren
op_amp
id|info-&gt;cmap
comma
op_amp
id|disp-&gt;cmap
comma
l_int|0
)paren
suffix:semicolon
)brace
id|info-&gt;currcon
op_assign
id|con
suffix:semicolon
id|disp
op_assign
id|fb_display
op_plus
id|con
suffix:semicolon
multiline_comment|/*&n;&t; * Install the new colormap and change the graphics mode. By default&n;&t; * fbcon sets all the colormaps and graphics modes to the default&n;&t; * values at bootup.&n;&t; *&n;&t; * Really, we want to set the colormap size depending on the&n;&t; * depth of the new grpahics mode. For now, we leave it as its&n;&t; * default 256 entry.&n;&t; */
r_if
c_cond
(paren
id|disp-&gt;cmap.len
)paren
id|cmap
op_assign
op_amp
id|disp-&gt;cmap
suffix:semicolon
r_else
id|cmap
op_assign
id|fb_default_cmap
c_func
(paren
l_int|1
op_lshift
id|disp-&gt;var.bits_per_pixel
)paren
suffix:semicolon
id|fb_copy_cmap
c_func
(paren
id|cmap
comma
op_amp
id|info-&gt;cmap
comma
l_int|0
)paren
suffix:semicolon
id|disp-&gt;var.activate
op_assign
id|FB_ACTIVATE_NOW
suffix:semicolon
id|info-&gt;fbops
op_member_access_from_pointer
id|fb_set_var
c_func
(paren
op_amp
id|disp-&gt;var
comma
id|con
comma
id|info
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;fbgen_blank - blank the screen&n; *&t;@blank: boolean, 0 unblank, 1 blank&n; *&t;@info: frame buffer info structure&n; *&n; *&t;Blank the screen on device @info.&n; *&n; */
DECL|function|fbgen_blank
r_int
id|fbgen_blank
c_func
(paren
r_int
id|blank
comma
r_struct
id|fb_info
op_star
id|info
)paren
(brace
r_struct
id|fb_info_gen
op_star
id|info2
op_assign
(paren
r_struct
id|fb_info_gen
op_star
)paren
id|info
suffix:semicolon
r_struct
id|fbgen_hwswitch
op_star
id|fbhw
op_assign
id|info2-&gt;fbhw
suffix:semicolon
id|u16
id|black
(braket
l_int|16
)braket
suffix:semicolon
r_struct
id|fb_cmap
id|cmap
suffix:semicolon
r_if
c_cond
(paren
id|fbhw-&gt;blank
op_logical_and
op_logical_neg
id|fbhw
op_member_access_from_pointer
id|blank
c_func
(paren
id|blank
comma
id|info2
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|blank
)paren
(brace
id|memset
c_func
(paren
id|black
comma
l_int|0
comma
l_int|16
op_star
r_sizeof
(paren
id|u16
)paren
)paren
suffix:semicolon
id|cmap.red
op_assign
id|black
suffix:semicolon
id|cmap.green
op_assign
id|black
suffix:semicolon
id|cmap.blue
op_assign
id|black
suffix:semicolon
id|cmap.transp
op_assign
l_int|NULL
suffix:semicolon
id|cmap.start
op_assign
l_int|0
suffix:semicolon
id|cmap.len
op_assign
l_int|16
suffix:semicolon
id|fb_set_cmap
c_func
(paren
op_amp
id|cmap
comma
l_int|1
comma
id|info
)paren
suffix:semicolon
)brace
r_else
id|do_install_cmap
c_func
(paren
id|info-&gt;currcon
comma
id|info
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* generic frame buffer operations */
DECL|variable|fbgen_get_fix
id|EXPORT_SYMBOL
c_func
(paren
id|fbgen_get_fix
)paren
suffix:semicolon
DECL|variable|gen_get_fix
id|EXPORT_SYMBOL
c_func
(paren
id|gen_get_fix
)paren
suffix:semicolon
DECL|variable|fbgen_get_var
id|EXPORT_SYMBOL
c_func
(paren
id|fbgen_get_var
)paren
suffix:semicolon
DECL|variable|gen_get_var
id|EXPORT_SYMBOL
c_func
(paren
id|gen_get_var
)paren
suffix:semicolon
DECL|variable|fbgen_set_var
id|EXPORT_SYMBOL
c_func
(paren
id|fbgen_set_var
)paren
suffix:semicolon
DECL|variable|gen_set_var
id|EXPORT_SYMBOL
c_func
(paren
id|gen_set_var
)paren
suffix:semicolon
DECL|variable|fbgen_get_cmap
id|EXPORT_SYMBOL
c_func
(paren
id|fbgen_get_cmap
)paren
suffix:semicolon
DECL|variable|gen_get_cmap
id|EXPORT_SYMBOL
c_func
(paren
id|gen_get_cmap
)paren
suffix:semicolon
DECL|variable|fbgen_set_cmap
id|EXPORT_SYMBOL
c_func
(paren
id|fbgen_set_cmap
)paren
suffix:semicolon
DECL|variable|gen_set_cmap
id|EXPORT_SYMBOL
c_func
(paren
id|gen_set_cmap
)paren
suffix:semicolon
DECL|variable|fbgen_pan_display
id|EXPORT_SYMBOL
c_func
(paren
id|fbgen_pan_display
)paren
suffix:semicolon
multiline_comment|/* helper functions */
DECL|variable|fbgen_do_set_var
id|EXPORT_SYMBOL
c_func
(paren
id|fbgen_do_set_var
)paren
suffix:semicolon
DECL|variable|fbgen_set_disp
id|EXPORT_SYMBOL
c_func
(paren
id|fbgen_set_disp
)paren
suffix:semicolon
DECL|variable|do_install_cmap
id|EXPORT_SYMBOL
c_func
(paren
id|do_install_cmap
)paren
suffix:semicolon
DECL|variable|fbgen_update_var
id|EXPORT_SYMBOL
c_func
(paren
id|fbgen_update_var
)paren
suffix:semicolon
DECL|variable|gen_update_var
id|EXPORT_SYMBOL
c_func
(paren
id|gen_update_var
)paren
suffix:semicolon
DECL|variable|fbgen_switch
id|EXPORT_SYMBOL
c_func
(paren
id|fbgen_switch
)paren
suffix:semicolon
DECL|variable|gen_switch
id|EXPORT_SYMBOL
c_func
(paren
id|gen_switch
)paren
suffix:semicolon
DECL|variable|fbgen_blank
id|EXPORT_SYMBOL
c_func
(paren
id|fbgen_blank
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
