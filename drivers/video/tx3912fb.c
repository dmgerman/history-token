multiline_comment|/*&n; * linux/drivers/video/tx3912fb.c&n; *&n; * Copyright (C) 1999 Harald Koerfgen&n; * Copyright (C) 2001 Steven Hill (sjhill@realitydiluted.com)&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License. See the file COPYING in the main directory of this archive for&n; * more details.&n; *&n; * Framebuffer for LCD controller in TMPR3912/05 and PR31700 processors&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pm.h&gt;
macro_line|#include &lt;linux/fb.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;video/fbcon.h&gt;
macro_line|#include &lt;video/fbcon-mfb.h&gt;
macro_line|#include &lt;video/fbcon-cfb2.h&gt;
macro_line|#include &lt;video/fbcon-cfb4.h&gt;
macro_line|#include &lt;video/fbcon-cfb8.h&gt;
macro_line|#include &quot;tx3912fb.h&quot;
multiline_comment|/*&n; * Frame buffer, palette and console structures&n; */
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
DECL|variable|global_disp
r_static
r_struct
id|display
id|global_disp
suffix:semicolon
multiline_comment|/*&n; * Interface used by the world&n; */
r_static
r_int
id|tx3912fb_get_fix
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
id|tx3912fb_get_var
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
id|tx3912fb_set_var
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
id|tx3912fb_get_cmap
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
id|tx3912fb_set_cmap
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
id|tx3912fb_ioctl
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
comma
id|u_int
id|cmd
comma
id|u_long
id|arg
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
multiline_comment|/*&n; * Interface used by console driver&n; */
r_int
id|tx3912fb_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_int
id|tx3912fbcon_switch
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
id|tx3912fbcon_updatevar
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
r_void
id|tx3912fbcon_blank
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
suffix:semicolon
multiline_comment|/*&n; * Macros&n; */
DECL|macro|get_line_length
mdefine_line|#define get_line_length(xres_virtual, bpp) &bslash;&n;&t;&t;(u_long) (((int) xres_virtual * (int) bpp + 7) &gt;&gt; 3)
multiline_comment|/*&n; * Internal routines&n; */
r_static
r_int
id|tx3912fb_getcolreg
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
r_int
id|tx3912fb_setcolreg
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
r_void
id|tx3912fb_install_cmap
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
multiline_comment|/*&n; * Frame buffer operations structure used by console driver&n; */
DECL|variable|tx3912fb_ops
r_static
r_struct
id|fb_ops
id|tx3912fb_ops
op_assign
(brace
id|owner
suffix:colon
id|THIS_MODULE
comma
id|fb_get_fix
suffix:colon
id|tx3912fb_get_fix
comma
id|fb_get_var
suffix:colon
id|tx3912fb_get_var
comma
id|fb_set_var
suffix:colon
id|tx3912fb_set_var
comma
id|fb_get_cmap
suffix:colon
id|tx3912fb_get_cmap
comma
id|fb_set_cmap
suffix:colon
id|tx3912fb_set_cmap
comma
id|fb_ioctl
suffix:colon
id|tx3912fb_ioctl
comma
)brace
suffix:semicolon
multiline_comment|/*&n; *  Get fixed display data&n; */
DECL|function|tx3912fb_get_fix
r_static
r_int
id|tx3912fb_get_fix
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
id|display
op_star
id|display
suffix:semicolon
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
id|TX3912FB_NAME
)paren
suffix:semicolon
r_if
c_cond
(paren
id|con
op_eq
op_minus
l_int|1
)paren
id|display
op_assign
op_amp
id|global_disp
suffix:semicolon
r_else
id|display
op_assign
op_amp
id|fb_display
(braket
id|con
)braket
suffix:semicolon
id|fix-&gt;smem_start
op_assign
id|tx3912fb_vaddr
suffix:semicolon
id|fix-&gt;smem_len
op_assign
id|tx3912fb_size
suffix:semicolon
id|fix-&gt;type
op_assign
id|display-&gt;type
suffix:semicolon
id|fix-&gt;type_aux
op_assign
id|display-&gt;type_aux
suffix:semicolon
id|fix-&gt;xpanstep
op_assign
l_int|0
suffix:semicolon
id|fix-&gt;ypanstep
op_assign
id|display-&gt;ypanstep
suffix:semicolon
id|fix-&gt;ywrapstep
op_assign
id|display-&gt;ywrapstep
suffix:semicolon
id|fix-&gt;visual
op_assign
id|display-&gt;visual
suffix:semicolon
id|fix-&gt;line_length
op_assign
id|display-&gt;line_length
suffix:semicolon
id|fix-&gt;accel
op_assign
id|FB_ACCEL_NONE
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Get user display data&n; */
DECL|function|tx3912fb_get_var
r_static
r_int
id|tx3912fb_get_var
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
id|tx3912fb_info
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
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *  Set user display data&n; */
DECL|function|tx3912fb_set_var
r_static
r_int
id|tx3912fb_set_var
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
op_eq
op_minus
l_int|1
)paren
id|display
op_assign
op_amp
id|global_disp
suffix:semicolon
r_else
id|display
op_assign
op_amp
id|fb_display
(braket
id|con
)braket
suffix:semicolon
multiline_comment|/*&n;&t; * FB_VMODE_CONUPDATE and FB_VMODE_SMOOTH_XPAN are equal&n;&t; * as FB_VMODE_SMOOTH_XPAN is only used internally&n;&t; */
r_if
c_cond
(paren
id|var-&gt;vmode
op_amp
id|FB_VMODE_CONUPDATE
)paren
(brace
id|var-&gt;xoffset
op_assign
id|display-&gt;var.xoffset
suffix:semicolon
id|var-&gt;yoffset
op_assign
id|display-&gt;var.yoffset
suffix:semicolon
id|var-&gt;vmode
op_or_assign
id|FB_VMODE_YWRAP
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Make sure values are in range&n;&t; */
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
l_int|2
)paren
id|var-&gt;bits_per_pixel
op_assign
l_int|2
suffix:semicolon
r_else
r_if
c_cond
(paren
id|var-&gt;bits_per_pixel
op_le
l_int|4
)paren
id|var-&gt;bits_per_pixel
op_assign
l_int|4
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
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/*&n;&t; * Memory limit&n;&t; */
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
(paren
id|line_length
op_star
id|var-&gt;yres_virtual
)paren
OG
id|tx3912fb_size
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
multiline_comment|/*&n;&t; * This is only for color and we only support 8-bit color&n;&t; */
r_if
c_cond
(paren
id|var-&gt;bits_per_pixel
)paren
(brace
multiline_comment|/* RGB 332 */
id|var-&gt;red.offset
op_assign
l_int|5
suffix:semicolon
id|var-&gt;red.length
op_assign
l_int|3
suffix:semicolon
id|var-&gt;green.offset
op_assign
l_int|2
suffix:semicolon
id|var-&gt;green.length
op_assign
l_int|3
suffix:semicolon
id|var-&gt;blue.offset
op_assign
l_int|0
suffix:semicolon
id|var-&gt;blue.length
op_assign
l_int|2
suffix:semicolon
id|var-&gt;transp.offset
op_assign
l_int|0
suffix:semicolon
id|var-&gt;transp.length
op_assign
l_int|0
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
multiline_comment|/*&n;&t; * Make changes if necessary&n;&t; */
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
id|display-&gt;screen_base
op_assign
(paren
id|u_char
op_star
)paren
id|tx3912fb_vaddr
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
id|display-&gt;visual
op_assign
id|FB_VISUAL_MONO10
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|display-&gt;visual
op_assign
id|FB_VISUAL_PSEUDOCOLOR
suffix:semicolon
r_case
l_int|4
suffix:colon
r_case
l_int|8
suffix:colon
id|display-&gt;visual
op_assign
id|FB_VISUAL_TRUECOLOR
suffix:semicolon
r_break
suffix:semicolon
)brace
id|display-&gt;type
op_assign
id|FB_TYPE_PACKED_PIXELS
suffix:semicolon
id|display-&gt;type_aux
op_assign
l_int|0
suffix:semicolon
id|display-&gt;ypanstep
op_assign
l_int|0
suffix:semicolon
id|display-&gt;ywrapstep
op_assign
l_int|0
suffix:semicolon
id|display-&gt;next_line
op_assign
id|display-&gt;line_length
op_assign
id|get_line_length
c_func
(paren
id|var-&gt;xres_virtual
comma
id|var-&gt;bits_per_pixel
)paren
suffix:semicolon
id|display-&gt;can_soft_blank
op_assign
l_int|0
suffix:semicolon
id|display-&gt;inverse
op_assign
id|FB_IS_INVERSE
suffix:semicolon
r_switch
c_cond
(paren
id|var-&gt;bits_per_pixel
)paren
(brace
macro_line|#ifdef CONFIG_FBCON_MFB
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
macro_line|#ifdef CONFIG_FBCON_CFB2
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
macro_line|#ifdef CONFIG_FBCON_CFB4
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
macro_line|#ifdef CONFIG_FBCON_CFB8
r_case
l_int|8
suffix:colon
id|display-&gt;dispsw
op_assign
op_amp
id|fbcon_cfb8
suffix:semicolon
id|display-&gt;dispsw_data
op_assign
id|fbcon_cmap.cfb8
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
id|tx3912fb_install_cmap
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
multiline_comment|/*&n; *  Get the colormap&n; */
DECL|function|tx3912fb_get_cmap
r_static
r_int
id|tx3912fb_get_cmap
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
r_return
id|fb_get_cmap
c_func
(paren
id|cmap
comma
id|kspc
comma
id|tx3912fb_getcolreg
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
multiline_comment|/*&n; *  Set the Colormap&n; */
DECL|function|tx3912fb_set_cmap
r_static
r_int
id|tx3912fb_set_cmap
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
r_if
c_cond
(paren
id|con
op_eq
id|info-&gt;currcon
)paren
r_return
id|fb_set_cmap
c_func
(paren
id|cmap
comma
id|kspc
comma
id|tx3912fb_setcolreg
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
multiline_comment|/*&n; *  Framebuffer ioctl&n; */
DECL|function|tx3912fb_ioctl
r_static
r_int
id|tx3912fb_ioctl
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
comma
id|u_int
id|cmd
comma
id|u_long
id|arg
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
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/*&n; * Initialization of the framebuffer&n; */
DECL|function|tx3912fb_init
r_int
id|__init
id|tx3912fb_init
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Stop the video logic when frame completes */
id|VidCtrl1
op_or_assign
id|ENFREEZEFRAME
suffix:semicolon
id|IntClear1
op_or_assign
id|INT1_LCDINT
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
(paren
id|IntStatus1
op_amp
id|INT1_LCDINT
)paren
)paren
suffix:semicolon
multiline_comment|/* Disable the video logic */
id|VidCtrl1
op_and_assign
op_complement
(paren
id|ENVID
op_or
id|DISPON
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|200
)paren
suffix:semicolon
multiline_comment|/* Set start address for DMA transfer */
id|VidCtrl3
op_assign
id|tx3912fb_paddr
op_amp
(paren
id|TX3912_VIDCTRL3_VIDBANK_MASK
op_or
id|TX3912_VIDCTRL3_VIDBASEHI_MASK
)paren
suffix:semicolon
multiline_comment|/* Set end address for DMA transfer */
id|VidCtrl4
op_assign
(paren
id|tx3912fb_paddr
op_plus
id|tx3912fb_size
op_plus
l_int|1
)paren
op_amp
id|TX3912_VIDCTRL4_VIDBASELO_MASK
suffix:semicolon
multiline_comment|/* Set the pixel depth */
r_switch
c_cond
(paren
id|tx3912fb_info.bits_per_pixel
)paren
(brace
r_case
l_int|1
suffix:colon
multiline_comment|/* Monochrome */
id|VidCtrl1
op_and_assign
op_complement
id|TX3912_VIDCTRL1_BITSEL_MASK
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
multiline_comment|/* 4-bit gray */
id|VidCtrl1
op_and_assign
op_complement
id|TX3912_VIDCTRL1_BITSEL_MASK
suffix:semicolon
id|VidCtrl1
op_or_assign
id|TX3912_VIDCTRL1_4BIT_GRAY
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|8
suffix:colon
multiline_comment|/* 8-bit color */
id|VidCtrl1
op_and_assign
op_complement
id|TX3912_VIDCTRL1_BITSEL_MASK
suffix:semicolon
id|VidCtrl1
op_or_assign
id|TX3912_VIDCTRL1_8BIT_COLOR
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
r_default
suffix:colon
multiline_comment|/* 2-bit gray */
id|VidCtrl1
op_and_assign
op_complement
id|TX3912_VIDCTRL1_BITSEL_MASK
suffix:semicolon
id|VidCtrl1
op_or_assign
id|TX3912_VIDCTRL1_2BIT_GRAY
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* Unfreeze video logic and enable DF toggle */
id|VidCtrl1
op_and_assign
op_complement
(paren
id|ENFREEZEFRAME
op_or
id|DFMODE
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|200
)paren
suffix:semicolon
multiline_comment|/* Clear the framebuffer */
id|memset
c_func
(paren
(paren
r_void
op_star
)paren
id|tx3912fb_vaddr
comma
l_int|0xff
comma
id|tx3912fb_size
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|200
)paren
suffix:semicolon
multiline_comment|/* Enable the video logic */
id|VidCtrl1
op_or_assign
(paren
id|DISPON
op_or
id|ENVID
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|fb_info.modename
comma
id|TX3912FB_NAME
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
id|tx3912fb_ops
suffix:semicolon
id|fb_info.disp
op_assign
op_amp
id|global_disp
suffix:semicolon
id|fb_info.currcon
op_assign
op_minus
l_int|1
suffix:semicolon
id|fb_info.switch_con
op_assign
op_amp
id|tx3912fbcon_switch
suffix:semicolon
id|fb_info.updatevar
op_assign
op_amp
id|tx3912fbcon_updatevar
suffix:semicolon
id|fb_info.blank
op_assign
op_amp
id|tx3912fbcon_blank
suffix:semicolon
id|fb_info.flags
op_assign
id|FBINFO_FLAG_DEFAULT
suffix:semicolon
id|tx3912fb_set_var
c_func
(paren
op_amp
id|tx3912fb_info
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
r_return
op_minus
l_int|1
suffix:semicolon
id|printk
(paren
id|KERN_INFO
l_string|&quot;fb%d: TX3912 frame buffer using %uKB.&bslash;n&quot;
comma
id|GET_FB_IDX
c_func
(paren
id|fb_info.node
)paren
comma
(paren
id|u_int
)paren
(paren
id|tx3912fb_size
op_rshift
l_int|10
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Switch the console to be the framebuffer&n; */
DECL|function|tx3912fbcon_switch
r_static
r_int
id|tx3912fbcon_switch
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
multiline_comment|/* Save off the color map if needed */
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
id|tx3912fb_getcolreg
comma
id|info
)paren
suffix:semicolon
multiline_comment|/* Make the switch */
id|info-&gt;currcon
op_assign
id|con
suffix:semicolon
multiline_comment|/* Install new colormap */
id|tx3912fb_install_cmap
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
multiline_comment|/*&n; * Update variable structure&n; */
DECL|function|tx3912fbcon_updatevar
r_static
r_int
id|tx3912fbcon_updatevar
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
multiline_comment|/*&n; * Blank the display&n; */
DECL|function|tx3912fbcon_blank
r_static
r_void
id|tx3912fbcon_blank
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
multiline_comment|/* FIXME */
id|printk
c_func
(paren
l_string|&quot;tx3912fbcon_blank&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Read a single color register&n; */
DECL|function|tx3912fb_getcolreg
r_static
r_int
id|tx3912fb_getcolreg
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
macro_line|#if FB_IS_GREY
(brace
id|u_int
id|grey
suffix:semicolon
id|grey
op_assign
id|regno
op_star
l_int|255
op_div
l_int|15
suffix:semicolon
macro_line|#if FB_IS_INVERSE
id|grey
op_xor_assign
l_int|255
suffix:semicolon
macro_line|#endif
id|grey
op_or_assign
id|grey
op_lshift
l_int|8
suffix:semicolon
op_star
id|red
op_assign
id|grey
suffix:semicolon
op_star
id|green
op_assign
id|grey
suffix:semicolon
op_star
id|blue
op_assign
id|grey
suffix:semicolon
)brace
macro_line|#else
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
macro_line|#endif
op_star
id|transp
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Set a single color register&n; */
DECL|function|tx3912fb_setcolreg
r_static
r_int
id|tx3912fb_setcolreg
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
macro_line|#ifdef FBCON_HAS_CFB8
r_if
c_cond
(paren
id|regno
OL
l_int|16
)paren
(brace
id|fbcon_cmap.cfb8
(braket
id|regno
)braket
op_assign
(paren
(paren
id|red
op_amp
l_int|0xe000
)paren
op_rshift
l_int|8
)paren
op_or
(paren
(paren
id|green
op_amp
l_int|0xe000
)paren
op_rshift
l_int|11
)paren
op_or
(paren
(paren
id|blue
op_amp
l_int|0xc000
)paren
op_rshift
l_int|14
)paren
suffix:semicolon
)brace
macro_line|#endif 
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
multiline_comment|/*&n; * Install the color map&n; */
DECL|function|tx3912fb_install_cmap
r_static
r_void
id|tx3912fb_install_cmap
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
id|tx3912fb_setcolreg
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
id|tx3912fb_setcolreg
comma
id|info
)paren
suffix:semicolon
)brace
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
