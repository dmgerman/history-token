multiline_comment|/*&n; *  linux/drivers/video/vfb.c -- Virtual frame buffer device&n; *&n; *&t;Copyright (C) 1997 Geert Uytterhoeven&n; *&n; *  This file is subject to the terms and conditions of the GNU General Public&n; *  License. See the file COPYING in the main directory of this archive for&n; *  more details.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/fb.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;video/fbcon.h&gt;
macro_line|#include &lt;video/fbcon-mfb.h&gt;
macro_line|#include &lt;video/fbcon-cfb2.h&gt;
macro_line|#include &lt;video/fbcon-cfb4.h&gt;
macro_line|#include &lt;video/fbcon-cfb8.h&gt;
macro_line|#include &lt;video/fbcon-cfb16.h&gt;
macro_line|#include &lt;video/fbcon-cfb24.h&gt;
macro_line|#include &lt;video/fbcon-cfb32.h&gt;
multiline_comment|/*&n;     *  RAM we reserve for the frame buffer. This defines the maximum screen&n;     *  size&n;     *&n;     *  The default can be overridden if the driver is compiled as a module&n;     */
DECL|macro|VIDEOMEMSIZE
mdefine_line|#define VIDEOMEMSIZE&t;(1*1024*1024)&t;/* 1 MB */
DECL|variable|videomemory
DECL|variable|videomemorysize
r_static
id|u_long
id|videomemory
comma
id|videomemorysize
op_assign
id|VIDEOMEMSIZE
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|videomemorysize
comma
l_string|&quot;l&quot;
)paren
suffix:semicolon
DECL|variable|disp
r_static
r_struct
id|display
id|disp
suffix:semicolon
DECL|variable|fb_info
r_static
r_struct
id|fb_info
id|fb_info
suffix:semicolon
DECL|member|red
DECL|member|green
DECL|member|blue
DECL|member|pad
DECL|variable|palette
r_static
r_struct
(brace
id|u_char
id|red
comma
id|green
comma
id|blue
comma
id|pad
suffix:semicolon
)brace
id|palette
(braket
l_int|256
)braket
suffix:semicolon
r_static
r_union
(brace
macro_line|#ifdef FBCON_HAS_CFB16
DECL|member|cfb16
id|u16
id|cfb16
(braket
l_int|16
)braket
suffix:semicolon
macro_line|#endif
macro_line|#ifdef FBCON_HAS_CFB24
DECL|member|cfb24
id|u32
id|cfb24
(braket
l_int|16
)braket
suffix:semicolon
macro_line|#endif
macro_line|#ifdef FBCON_HAS_CFB32
DECL|member|cfb32
id|u32
id|cfb32
(braket
l_int|16
)braket
suffix:semicolon
macro_line|#endif
DECL|variable|fbcon_cmap
)brace
id|fbcon_cmap
suffix:semicolon
DECL|variable|vfb_name
r_static
r_char
id|vfb_name
(braket
l_int|16
)braket
op_assign
l_string|&quot;Virtual FB&quot;
suffix:semicolon
DECL|variable|vfb_default
r_static
r_struct
id|fb_var_screeninfo
id|vfb_default
op_assign
(brace
multiline_comment|/* 640x480, 8 bpp */
l_int|640
comma
l_int|480
comma
l_int|640
comma
l_int|480
comma
l_int|0
comma
l_int|0
comma
l_int|8
comma
l_int|0
comma
(brace
l_int|0
comma
l_int|8
comma
l_int|0
)brace
comma
(brace
l_int|0
comma
l_int|8
comma
l_int|0
)brace
comma
(brace
l_int|0
comma
l_int|8
comma
l_int|0
)brace
comma
(brace
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
l_int|0
comma
l_int|0
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
l_int|0
comma
l_int|20000
comma
l_int|64
comma
l_int|64
comma
l_int|32
comma
l_int|32
comma
l_int|64
comma
l_int|2
comma
l_int|0
comma
id|FB_VMODE_NONINTERLACED
)brace
suffix:semicolon
DECL|variable|vfb_enable
r_static
r_int
id|vfb_enable
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* disabled by default */
multiline_comment|/*&n;     *  Interface used by the world&n;     */
r_int
id|vfb_setup
c_func
(paren
r_char
op_star
)paren
suffix:semicolon
r_static
r_int
id|vfb_get_fix
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
suffix:semicolon
r_static
r_int
id|vfb_get_var
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
suffix:semicolon
r_static
r_int
id|vfb_set_var
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
suffix:semicolon
r_static
r_int
id|vfb_setcolreg
c_func
(paren
id|u_int
id|regno
comma
id|u_int
id|red
comma
id|u_int
id|green
comma
id|u_int
id|blue
comma
id|u_int
id|transp
comma
r_struct
id|fb_info
op_star
id|info
)paren
suffix:semicolon
r_static
r_int
id|vfb_pan_display
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
suffix:semicolon
r_static
r_int
id|vfb_get_cmap
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
suffix:semicolon
r_static
r_int
id|vfb_set_cmap
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
suffix:semicolon
multiline_comment|/*&n;     *  Interface to the low level console driver&n;     */
r_int
id|vfb_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_int
id|vfbcon_switch
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
suffix:semicolon
r_static
r_int
id|vfbcon_updatevar
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
suffix:semicolon
multiline_comment|/*&n;     *  Internal routines&n;     */
r_static
id|u_long
id|get_line_length
c_func
(paren
r_int
id|xres_virtual
comma
r_int
id|bpp
)paren
suffix:semicolon
r_static
r_void
id|vfb_encode_fix
c_func
(paren
r_struct
id|fb_fix_screeninfo
op_star
id|fix
comma
r_struct
id|fb_var_screeninfo
op_star
id|var
)paren
suffix:semicolon
r_static
r_void
id|set_color_bitfields
c_func
(paren
r_struct
id|fb_var_screeninfo
op_star
id|var
)paren
suffix:semicolon
r_static
r_int
id|vfb_getcolreg
c_func
(paren
id|u_int
id|regno
comma
id|u_int
op_star
id|red
comma
id|u_int
op_star
id|green
comma
id|u_int
op_star
id|blue
comma
id|u_int
op_star
id|transp
comma
r_struct
id|fb_info
op_star
id|info
)paren
suffix:semicolon
r_static
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
suffix:semicolon
DECL|variable|vfb_ops
r_static
r_struct
id|fb_ops
id|vfb_ops
op_assign
(brace
id|owner
suffix:colon
id|THIS_MODULE
comma
id|fb_get_fix
suffix:colon
id|vfb_get_fix
comma
id|fb_get_var
suffix:colon
id|vfb_get_var
comma
id|fb_set_var
suffix:colon
id|vfb_set_var
comma
id|fb_get_cmap
suffix:colon
id|vfb_get_cmap
comma
id|fb_set_cmap
suffix:colon
id|vfb_set_cmap
comma
id|fb_setcolreg
suffix:colon
id|vfb_setcolreg
comma
id|fb_pan_display
suffix:colon
id|vfb_pan_display
comma
)brace
suffix:semicolon
multiline_comment|/*&n;     *  Get the Fixed Part of the Display&n;     */
DECL|function|vfb_get_fix
r_static
r_int
id|vfb_get_fix
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
id|fb_var_screeninfo
op_star
id|var
suffix:semicolon
r_if
c_cond
(paren
id|con
op_eq
op_minus
l_int|1
)paren
id|var
op_assign
op_amp
id|vfb_default
suffix:semicolon
r_else
id|var
op_assign
op_amp
id|fb_display
(braket
id|con
)braket
dot
id|var
suffix:semicolon
id|vfb_encode_fix
c_func
(paren
id|fix
comma
id|var
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;     *  Get the User Defined Part of the Display&n;     */
DECL|function|vfb_get_var
r_static
r_int
id|vfb_get_var
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
r_if
c_cond
(paren
id|con
op_eq
op_minus
l_int|1
)paren
op_star
id|var
op_assign
id|vfb_default
suffix:semicolon
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
id|set_color_bitfields
c_func
(paren
id|var
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;     *  Set the User Defined Part of the Display&n;     */
DECL|function|vfb_set_var
r_static
r_int
id|vfb_set_var
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
comma
id|activate
op_assign
id|var-&gt;activate
suffix:semicolon
r_int
id|oldxres
comma
id|oldyres
comma
id|oldvxres
comma
id|oldvyres
comma
id|oldbpp
suffix:semicolon
id|u_long
id|line_length
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
op_amp
id|disp
suffix:semicolon
multiline_comment|/* used during initialization */
multiline_comment|/*&n;     *  FB_VMODE_CONUPDATE and FB_VMODE_SMOOTH_XPAN are equal!&n;     *  as FB_VMODE_SMOOTH_XPAN is only used internally&n;     */
r_if
c_cond
(paren
id|var-&gt;vmode
op_amp
id|FB_VMODE_CONUPDATE
)paren
(brace
id|var-&gt;vmode
op_or_assign
id|FB_VMODE_YWRAP
suffix:semicolon
id|var-&gt;xoffset
op_assign
id|display-&gt;var.xoffset
suffix:semicolon
id|var-&gt;yoffset
op_assign
id|display-&gt;var.yoffset
suffix:semicolon
)brace
multiline_comment|/*&n;     *  Some very basic checks&n;     */
r_if
c_cond
(paren
op_logical_neg
id|var-&gt;xres
)paren
id|var-&gt;xres
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|var-&gt;yres
)paren
id|var-&gt;yres
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|var-&gt;xres
OG
id|var-&gt;xres_virtual
)paren
id|var-&gt;xres_virtual
op_assign
id|var-&gt;xres
suffix:semicolon
r_if
c_cond
(paren
id|var-&gt;yres
OG
id|var-&gt;yres_virtual
)paren
id|var-&gt;yres_virtual
op_assign
id|var-&gt;yres
suffix:semicolon
r_if
c_cond
(paren
id|var-&gt;bits_per_pixel
op_le
l_int|1
)paren
id|var-&gt;bits_per_pixel
op_assign
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
id|var-&gt;bits_per_pixel
op_le
l_int|8
)paren
id|var-&gt;bits_per_pixel
op_assign
l_int|8
suffix:semicolon
r_else
r_if
c_cond
(paren
id|var-&gt;bits_per_pixel
op_le
l_int|16
)paren
id|var-&gt;bits_per_pixel
op_assign
l_int|16
suffix:semicolon
macro_line|#if 0
multiline_comment|/* fbcon doesn&squot;t support this (yet) */
r_else
r_if
c_cond
(paren
id|var-&gt;bits_per_pixel
op_le
l_int|24
)paren
id|var-&gt;bits_per_pixel
op_assign
l_int|24
suffix:semicolon
r_else
r_if
c_cond
(paren
id|var-&gt;bits_per_pixel
op_le
l_int|32
)paren
id|var-&gt;bits_per_pixel
op_assign
l_int|32
suffix:semicolon
macro_line|#endif
r_else
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/*&n;     *  Memory limit&n;     */
id|line_length
op_assign
id|get_line_length
c_func
(paren
id|var-&gt;xres_virtual
comma
id|var-&gt;bits_per_pixel
)paren
suffix:semicolon
r_if
c_cond
(paren
id|line_length
op_star
id|var-&gt;yres_virtual
OG
id|videomemorysize
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|set_color_bitfields
c_func
(paren
id|var
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|activate
op_amp
id|FB_ACTIVATE_MASK
)paren
op_eq
id|FB_ACTIVATE_NOW
)paren
(brace
id|oldxres
op_assign
id|display-&gt;var.xres
suffix:semicolon
id|oldyres
op_assign
id|display-&gt;var.yres
suffix:semicolon
id|oldvxres
op_assign
id|display-&gt;var.xres_virtual
suffix:semicolon
id|oldvyres
op_assign
id|display-&gt;var.yres_virtual
suffix:semicolon
id|oldbpp
op_assign
id|display-&gt;var.bits_per_pixel
suffix:semicolon
id|display-&gt;var
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
id|oldvxres
op_ne
id|var-&gt;xres_virtual
op_logical_or
id|oldvyres
op_ne
id|var-&gt;yres_virtual
op_logical_or
id|oldbpp
op_ne
id|var-&gt;bits_per_pixel
)paren
(brace
r_struct
id|fb_fix_screeninfo
id|fix
suffix:semicolon
id|vfb_encode_fix
c_func
(paren
op_amp
id|fix
comma
id|var
)paren
suffix:semicolon
id|display-&gt;screen_base
op_assign
(paren
r_char
op_star
)paren
id|videomemory
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
id|display-&gt;can_soft_blank
op_assign
l_int|1
suffix:semicolon
id|display-&gt;inverse
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|var-&gt;bits_per_pixel
)paren
(brace
macro_line|#ifdef FBCON_HAS_MFB
r_case
l_int|1
suffix:colon
id|display-&gt;dispsw
op_assign
op_amp
id|fbcon_mfb
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef FBCON_HAS_CFB2
r_case
l_int|2
suffix:colon
id|display-&gt;dispsw
op_assign
op_amp
id|fbcon_cfb2
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef FBCON_HAS_CFB4
r_case
l_int|4
suffix:colon
id|display-&gt;dispsw
op_assign
op_amp
id|fbcon_cfb4
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef FBCON_HAS_CFB8
r_case
l_int|8
suffix:colon
id|display-&gt;dispsw
op_assign
op_amp
id|fbcon_cfb8
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef FBCON_HAS_CFB16
r_case
l_int|16
suffix:colon
id|display-&gt;dispsw
op_assign
op_amp
id|fbcon_cfb16
suffix:semicolon
id|display-&gt;dispsw_data
op_assign
id|fbcon_cmap.cfb16
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef FBCON_HAS_CFB24
r_case
l_int|24
suffix:colon
id|display-&gt;dispsw
op_assign
op_amp
id|fbcon_cfb24
suffix:semicolon
id|display-&gt;dispsw_data
op_assign
id|fbcon_cmap.cfb24
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef FBCON_HAS_CFB32
r_case
l_int|32
suffix:colon
id|display-&gt;dispsw
op_assign
op_amp
id|fbcon_cfb32
suffix:semicolon
id|display-&gt;dispsw_data
op_assign
id|fbcon_cmap.cfb32
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
r_default
suffix:colon
id|display-&gt;dispsw
op_assign
op_amp
id|fbcon_dummy
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|fb_info.changevar
)paren
(paren
op_star
id|fb_info.changevar
)paren
(paren
id|con
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|oldbpp
op_ne
id|var-&gt;bits_per_pixel
)paren
(brace
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
id|display-&gt;cmap
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
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;     *  Pan or Wrap the Display&n;     *&n;     *  This call looks only at xoffset, yoffset and the FB_VMODE_YWRAP flag&n;     */
DECL|function|vfb_pan_display
r_static
r_int
id|vfb_pan_display
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
r_if
c_cond
(paren
id|var-&gt;vmode
op_amp
id|FB_VMODE_YWRAP
)paren
(brace
r_if
c_cond
(paren
id|var-&gt;yoffset
OL
l_int|0
op_logical_or
id|var-&gt;yoffset
op_ge
id|fb_display
(braket
id|con
)braket
dot
id|var.yres_virtual
op_logical_or
id|var-&gt;xoffset
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|var-&gt;xoffset
op_plus
id|fb_display
(braket
id|con
)braket
dot
id|var.xres
OG
id|fb_display
(braket
id|con
)braket
dot
id|var.xres_virtual
op_logical_or
id|var-&gt;yoffset
op_plus
id|fb_display
(braket
id|con
)braket
dot
id|var.yres
OG
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
multiline_comment|/*&n;     *  Get the Colormap&n;     */
DECL|function|vfb_get_cmap
r_static
r_int
id|vfb_get_cmap
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
r_if
c_cond
(paren
id|con
op_eq
id|info-&gt;currcon
)paren
multiline_comment|/* current console? */
r_return
id|fb_get_cmap
c_func
(paren
id|cmap
comma
id|kspc
comma
id|vfb_getcolreg
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
multiline_comment|/* non default colormap? */
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
id|fb_copy_cmap
c_func
(paren
id|fb_default_cmap
c_func
(paren
l_int|1
op_lshift
id|fb_display
(braket
id|con
)braket
dot
id|var.bits_per_pixel
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
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;     *  Set the Colormap&n;     */
DECL|function|vfb_set_cmap
r_static
r_int
id|vfb_set_cmap
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
multiline_comment|/* no colormap allocated? */
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
l_int|1
op_lshift
id|fb_display
(braket
id|con
)braket
dot
id|var.bits_per_pixel
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
multiline_comment|/* current console? */
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
DECL|function|vfb_setup
r_int
id|__init
id|vfb_setup
c_func
(paren
r_char
op_star
id|options
)paren
(brace
r_char
op_star
id|this_opt
suffix:semicolon
id|fb_info.fontname
(braket
l_int|0
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|vfb_enable
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|options
op_logical_or
op_logical_neg
op_star
id|options
)paren
r_return
l_int|0
suffix:semicolon
r_while
c_loop
(paren
(paren
id|this_opt
op_assign
id|strsep
c_func
(paren
op_amp
id|options
comma
l_string|&quot;,&quot;
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|this_opt
comma
l_string|&quot;font:&quot;
comma
l_int|5
)paren
)paren
id|strcpy
c_func
(paren
id|fb_info.fontname
comma
id|this_opt
op_plus
l_int|5
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;     *  Initialisation&n;     */
DECL|function|vfb_init
r_int
id|__init
id|vfb_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|vfb_enable
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|videomemory
op_assign
(paren
id|u_long
)paren
id|vmalloc
c_func
(paren
id|videomemorysize
)paren
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|strcpy
c_func
(paren
id|fb_info.modename
comma
id|vfb_name
)paren
suffix:semicolon
id|fb_info.changevar
op_assign
l_int|NULL
suffix:semicolon
id|fb_info.node
op_assign
id|NODEV
suffix:semicolon
id|fb_info.fbops
op_assign
op_amp
id|vfb_ops
suffix:semicolon
id|fb_info.disp
op_assign
op_amp
id|disp
suffix:semicolon
id|fb_info.currcon
op_assign
op_minus
l_int|1
suffix:semicolon
id|fb_info.switch_con
op_assign
op_amp
id|vfbcon_switch
suffix:semicolon
id|fb_info.updatevar
op_assign
op_amp
id|vfbcon_updatevar
suffix:semicolon
id|fb_info.flags
op_assign
id|FBINFO_FLAG_DEFAULT
suffix:semicolon
id|vfb_set_var
c_func
(paren
op_amp
id|vfb_default
comma
op_minus
l_int|1
comma
op_amp
id|fb_info
)paren
suffix:semicolon
r_if
c_cond
(paren
id|register_framebuffer
c_func
(paren
op_amp
id|fb_info
)paren
OL
l_int|0
)paren
(brace
id|vfree
c_func
(paren
(paren
r_void
op_star
)paren
id|videomemory
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;fb%d: Virtual frame buffer device, using %ldK of video memory&bslash;n&quot;
comma
id|GET_FB_IDX
c_func
(paren
id|fb_info.node
)paren
comma
id|videomemorysize
op_rshift
l_int|10
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|vfbcon_switch
r_static
r_int
id|vfbcon_switch
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
multiline_comment|/* Do we have to save the colormap? */
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
id|vfb_getcolreg
comma
id|info
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
multiline_comment|/*&n;     *  Update the `var&squot; structure (called by fbcon.c)&n;     */
DECL|function|vfbcon_updatevar
r_static
r_int
id|vfbcon_updatevar
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
multiline_comment|/* Nothing */
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|get_line_length
r_static
id|u_long
id|get_line_length
c_func
(paren
r_int
id|xres_virtual
comma
r_int
id|bpp
)paren
(brace
id|u_long
id|length
suffix:semicolon
id|length
op_assign
id|xres_virtual
op_star
id|bpp
suffix:semicolon
id|length
op_assign
(paren
id|length
op_plus
l_int|31
)paren
op_amp
op_minus
l_int|32
suffix:semicolon
id|length
op_rshift_assign
l_int|3
suffix:semicolon
r_return
id|length
suffix:semicolon
)brace
DECL|function|vfb_encode_fix
r_static
r_void
id|vfb_encode_fix
c_func
(paren
r_struct
id|fb_fix_screeninfo
op_star
id|fix
comma
r_struct
id|fb_var_screeninfo
op_star
id|var
)paren
(brace
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
id|strcpy
c_func
(paren
id|fix-&gt;id
comma
id|vfb_name
)paren
suffix:semicolon
id|fix-&gt;smem_start
op_assign
id|videomemory
suffix:semicolon
id|fix-&gt;smem_len
op_assign
id|videomemorysize
suffix:semicolon
id|fix-&gt;type
op_assign
id|FB_TYPE_PACKED_PIXELS
suffix:semicolon
id|fix-&gt;type_aux
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|var-&gt;bits_per_pixel
)paren
(brace
r_case
l_int|1
suffix:colon
id|fix-&gt;visual
op_assign
id|FB_VISUAL_MONO01
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
r_case
l_int|4
suffix:colon
r_case
l_int|8
suffix:colon
id|fix-&gt;visual
op_assign
id|FB_VISUAL_PSEUDOCOLOR
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|16
suffix:colon
r_case
l_int|24
suffix:colon
r_case
l_int|32
suffix:colon
id|fix-&gt;visual
op_assign
id|FB_VISUAL_TRUECOLOR
suffix:semicolon
r_break
suffix:semicolon
)brace
id|fix-&gt;ywrapstep
op_assign
l_int|1
suffix:semicolon
id|fix-&gt;xpanstep
op_assign
l_int|1
suffix:semicolon
id|fix-&gt;ypanstep
op_assign
l_int|1
suffix:semicolon
id|fix-&gt;line_length
op_assign
id|get_line_length
c_func
(paren
id|var-&gt;xres_virtual
comma
id|var-&gt;bits_per_pixel
)paren
suffix:semicolon
)brace
DECL|function|set_color_bitfields
r_static
r_void
id|set_color_bitfields
c_func
(paren
r_struct
id|fb_var_screeninfo
op_star
id|var
)paren
(brace
r_switch
c_cond
(paren
id|var-&gt;bits_per_pixel
)paren
(brace
r_case
l_int|1
suffix:colon
r_case
l_int|8
suffix:colon
id|var-&gt;red.offset
op_assign
l_int|0
suffix:semicolon
id|var-&gt;red.length
op_assign
l_int|8
suffix:semicolon
id|var-&gt;green.offset
op_assign
l_int|0
suffix:semicolon
id|var-&gt;green.length
op_assign
l_int|8
suffix:semicolon
id|var-&gt;blue.offset
op_assign
l_int|0
suffix:semicolon
id|var-&gt;blue.length
op_assign
l_int|8
suffix:semicolon
id|var-&gt;transp.offset
op_assign
l_int|0
suffix:semicolon
id|var-&gt;transp.length
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|16
suffix:colon
multiline_comment|/* RGB 565 */
id|var-&gt;red.offset
op_assign
l_int|0
suffix:semicolon
id|var-&gt;red.length
op_assign
l_int|5
suffix:semicolon
id|var-&gt;green.offset
op_assign
l_int|5
suffix:semicolon
id|var-&gt;green.length
op_assign
l_int|6
suffix:semicolon
id|var-&gt;blue.offset
op_assign
l_int|11
suffix:semicolon
id|var-&gt;blue.length
op_assign
l_int|5
suffix:semicolon
id|var-&gt;transp.offset
op_assign
l_int|0
suffix:semicolon
id|var-&gt;transp.length
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|24
suffix:colon
multiline_comment|/* RGB 888 */
id|var-&gt;red.offset
op_assign
l_int|0
suffix:semicolon
id|var-&gt;red.length
op_assign
l_int|8
suffix:semicolon
id|var-&gt;green.offset
op_assign
l_int|8
suffix:semicolon
id|var-&gt;green.length
op_assign
l_int|8
suffix:semicolon
id|var-&gt;blue.offset
op_assign
l_int|16
suffix:semicolon
id|var-&gt;blue.length
op_assign
l_int|8
suffix:semicolon
id|var-&gt;transp.offset
op_assign
l_int|0
suffix:semicolon
id|var-&gt;transp.length
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|32
suffix:colon
multiline_comment|/* RGBA 8888 */
id|var-&gt;red.offset
op_assign
l_int|0
suffix:semicolon
id|var-&gt;red.length
op_assign
l_int|8
suffix:semicolon
id|var-&gt;green.offset
op_assign
l_int|8
suffix:semicolon
id|var-&gt;green.length
op_assign
l_int|8
suffix:semicolon
id|var-&gt;blue.offset
op_assign
l_int|16
suffix:semicolon
id|var-&gt;blue.length
op_assign
l_int|8
suffix:semicolon
id|var-&gt;transp.offset
op_assign
l_int|24
suffix:semicolon
id|var-&gt;transp.length
op_assign
l_int|8
suffix:semicolon
r_break
suffix:semicolon
)brace
id|var-&gt;red.msb_right
op_assign
l_int|0
suffix:semicolon
id|var-&gt;green.msb_right
op_assign
l_int|0
suffix:semicolon
id|var-&gt;blue.msb_right
op_assign
l_int|0
suffix:semicolon
id|var-&gt;transp.msb_right
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;     *  Read a single color register and split it into&n;     *  colors/transparent. Return != 0 for invalid regno.&n;     */
DECL|function|vfb_getcolreg
r_static
r_int
id|vfb_getcolreg
c_func
(paren
id|u_int
id|regno
comma
id|u_int
op_star
id|red
comma
id|u_int
op_star
id|green
comma
id|u_int
op_star
id|blue
comma
id|u_int
op_star
id|transp
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
id|regno
OG
l_int|255
)paren
r_return
l_int|1
suffix:semicolon
op_star
id|red
op_assign
(paren
id|palette
(braket
id|regno
)braket
dot
id|red
op_lshift
l_int|8
)paren
op_or
id|palette
(braket
id|regno
)braket
dot
id|red
suffix:semicolon
op_star
id|green
op_assign
(paren
id|palette
(braket
id|regno
)braket
dot
id|green
op_lshift
l_int|8
)paren
op_or
id|palette
(braket
id|regno
)braket
dot
id|green
suffix:semicolon
op_star
id|blue
op_assign
(paren
id|palette
(braket
id|regno
)braket
dot
id|blue
op_lshift
l_int|8
)paren
op_or
id|palette
(braket
id|regno
)braket
dot
id|blue
suffix:semicolon
op_star
id|transp
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;     *  Set a single color register. The values supplied are already&n;     *  rounded down to the hardware&squot;s capabilities (according to the&n;     *  entries in the var structure). Return != 0 for invalid regno.&n;     */
DECL|function|vfb_setcolreg
r_static
r_int
id|vfb_setcolreg
c_func
(paren
id|u_int
id|regno
comma
id|u_int
id|red
comma
id|u_int
id|green
comma
id|u_int
id|blue
comma
id|u_int
id|transp
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
id|regno
OG
l_int|255
)paren
r_return
l_int|1
suffix:semicolon
id|red
op_rshift_assign
l_int|8
suffix:semicolon
id|green
op_rshift_assign
l_int|8
suffix:semicolon
id|blue
op_rshift_assign
l_int|8
suffix:semicolon
id|palette
(braket
id|regno
)braket
dot
id|red
op_assign
id|red
suffix:semicolon
id|palette
(braket
id|regno
)braket
dot
id|green
op_assign
id|green
suffix:semicolon
id|palette
(braket
id|regno
)braket
dot
id|blue
op_assign
id|blue
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|do_install_cmap
r_static
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
id|fb_set_cmap
c_func
(paren
id|fb_default_cmap
c_func
(paren
l_int|1
op_lshift
id|fb_display
(braket
id|con
)braket
dot
id|var.bits_per_pixel
)paren
comma
l_int|1
comma
id|info
)paren
suffix:semicolon
)brace
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
id|vfb_init
c_func
(paren
)paren
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
id|unregister_framebuffer
c_func
(paren
op_amp
id|fb_info
)paren
suffix:semicolon
id|vfree
c_func
(paren
(paren
r_void
op_star
)paren
id|videomemory
)paren
suffix:semicolon
)brace
macro_line|#endif /* MODULE */
eof
