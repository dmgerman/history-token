multiline_comment|/*&n; *  linux/drivers/video/anakinfb.c&n; *&n; *  Copyright (C) 2001 Aleph One Ltd. for Acunia N.V.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  Changelog:&n; *   23-Apr-2001 TTC&t;Created&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/fb.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;video/fbcon.h&gt;
macro_line|#include &lt;video/fbcon-cfb16.h&gt;
DECL|variable|colreg
r_static
id|u16
id|colreg
(braket
l_int|16
)braket
suffix:semicolon
DECL|variable|fb_info
r_static
r_struct
id|fb_info
id|fb_info
suffix:semicolon
DECL|variable|display
r_static
r_struct
id|display
id|display
suffix:semicolon
r_static
r_int
DECL|function|anakinfb_getcolreg
id|anakinfb_getcolreg
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
l_int|15
)paren
r_return
l_int|1
suffix:semicolon
op_star
id|red
op_assign
id|colreg
(braket
id|regno
)braket
op_amp
l_int|0xf800
suffix:semicolon
op_star
id|green
op_assign
id|colreg
(braket
id|regno
)braket
op_amp
l_int|0x7e0
op_lshift
l_int|5
suffix:semicolon
op_star
id|blue
op_assign
id|colreg
(braket
id|regno
)braket
op_amp
l_int|0x1f
op_lshift
l_int|11
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
r_static
r_int
DECL|function|anakinfb_setcolreg
id|anakinfb_setcolreg
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
l_int|15
)paren
r_return
l_int|1
suffix:semicolon
id|colreg
(braket
id|regno
)braket
op_assign
(paren
id|red
op_amp
l_int|0xf800
)paren
op_or
(paren
id|green
op_amp
l_int|0xfc00
op_rshift
l_int|5
)paren
op_or
(paren
id|blue
op_amp
l_int|0xf800
op_rshift
l_int|11
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|anakinfb_get_fix
id|anakinfb_get_fix
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
l_string|&quot;AnakinFB&quot;
)paren
suffix:semicolon
id|fix-&gt;smem_start
op_assign
id|VGA_START
suffix:semicolon
id|fix-&gt;smem_len
op_assign
id|VGA_SIZE
suffix:semicolon
id|fix-&gt;type
op_assign
id|FB_TYPE_PACKED_PIXELS
suffix:semicolon
id|fix-&gt;type_aux
op_assign
l_int|0
suffix:semicolon
id|fix-&gt;visual
op_assign
id|FB_VISUAL_TRUECOLOR
suffix:semicolon
id|fix-&gt;xpanstep
op_assign
l_int|0
suffix:semicolon
id|fix-&gt;ypanstep
op_assign
l_int|0
suffix:semicolon
id|fix-&gt;ywrapstep
op_assign
l_int|0
suffix:semicolon
id|fix-&gt;line_length
op_assign
l_int|400
op_star
l_int|2
suffix:semicolon
id|fix-&gt;accel
op_assign
id|FB_ACCEL_NONE
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|anakinfb_get_var
id|anakinfb_get_var
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
id|memset
c_func
(paren
id|var
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|fb_var_screeninfo
)paren
)paren
suffix:semicolon
id|var-&gt;xres
op_assign
l_int|400
suffix:semicolon
id|var-&gt;yres
op_assign
l_int|234
suffix:semicolon
id|var-&gt;xres_virtual
op_assign
l_int|400
suffix:semicolon
id|var-&gt;yres_virtual
op_assign
l_int|234
suffix:semicolon
id|var-&gt;xoffset
op_assign
l_int|0
suffix:semicolon
id|var-&gt;yoffset
op_assign
l_int|0
suffix:semicolon
id|var-&gt;bits_per_pixel
op_assign
l_int|16
suffix:semicolon
id|var-&gt;grayscale
op_assign
l_int|0
suffix:semicolon
id|var-&gt;red.offset
op_assign
l_int|11
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
l_int|0
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
id|var-&gt;nonstd
op_assign
l_int|0
suffix:semicolon
id|var-&gt;activate
op_assign
id|FB_ACTIVATE_NOW
suffix:semicolon
id|var-&gt;height
op_assign
op_minus
l_int|1
suffix:semicolon
id|var-&gt;width
op_assign
op_minus
l_int|1
suffix:semicolon
id|var-&gt;pixclock
op_assign
l_int|0
suffix:semicolon
id|var-&gt;left_margin
op_assign
l_int|0
suffix:semicolon
id|var-&gt;right_margin
op_assign
l_int|0
suffix:semicolon
id|var-&gt;upper_margin
op_assign
l_int|0
suffix:semicolon
id|var-&gt;lower_margin
op_assign
l_int|0
suffix:semicolon
id|var-&gt;hsync_len
op_assign
l_int|0
suffix:semicolon
id|var-&gt;vsync_len
op_assign
l_int|0
suffix:semicolon
id|var-&gt;sync
op_assign
l_int|0
suffix:semicolon
id|var-&gt;vmode
op_assign
id|FB_VMODE_NONINTERLACED
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|anakinfb_set_var
id|anakinfb_set_var
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
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_static
r_int
DECL|function|anakinfb_get_cmap
id|anakinfb_get_cmap
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
id|anakinfb_getcolreg
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
l_int|16
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
r_static
r_int
DECL|function|anakinfb_switch_con
id|anakinfb_switch_con
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
id|info-&gt;currcon
op_assign
id|con
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|anakinfb_updatevar
id|anakinfb_updatevar
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
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_void
DECL|function|anakinfb_blank
id|anakinfb_blank
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
multiline_comment|/*&n;&t; * TODO: use I2C to blank/unblank the screen&n;&t; */
)brace
DECL|variable|anakinfb_ops
r_static
r_struct
id|fb_ops
id|anakinfb_ops
op_assign
(brace
id|owner
suffix:colon
id|THIS_MODULE
comma
id|fb_get_fix
suffix:colon
id|anakinfb_get_fix
comma
id|fb_get_var
suffix:colon
id|anakinfb_get_var
comma
id|fb_set_var
suffix:colon
id|anakinfb_set_var
comma
id|fb_get_cmap
suffix:colon
id|anakinfb_get_cmap
comma
id|fb_set_cmap
suffix:colon
id|gen_set_cmap
comma
id|fb_setcolreg
suffix:colon
id|anakinfb_setcolreg
comma
id|fb_blank
suffix:colon
id|anakinfb_blank
comma
)brace
suffix:semicolon
r_int
id|__init
DECL|function|anakinfb_init
id|anakinfb_init
c_func
(paren
r_void
)paren
(brace
id|memset
c_func
(paren
op_amp
id|fb_info
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|fb_info
)paren
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|fb_info.modename
comma
l_string|&quot;AnakinFB&quot;
)paren
suffix:semicolon
id|fb_info.node
op_assign
id|NODEV
suffix:semicolon
id|fb_info.flags
op_assign
id|FBINFO_FLAG_DEFAULT
suffix:semicolon
id|fb_info.fbops
op_assign
op_amp
id|anakinfb_ops
suffix:semicolon
id|fb_info.currcon
op_assign
op_minus
l_int|1
suffix:semicolon
id|fb_info.disp
op_assign
op_amp
id|display
suffix:semicolon
id|strcpy
c_func
(paren
id|fb_info.fontname
comma
l_string|&quot;VGA8x16&quot;
)paren
suffix:semicolon
id|fb_info.changevar
op_assign
l_int|NULL
suffix:semicolon
id|fb_info.switch_con
op_assign
op_amp
id|anakinfb_switch_con
suffix:semicolon
id|fb_info.updatevar
op_assign
op_amp
id|anakinfb_updatevar
suffix:semicolon
id|fb_info.screen_base
op_assign
id|ioremap
c_func
(paren
id|VGA_START
comma
id|VGA_SIZE
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|display
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|display
)paren
)paren
suffix:semicolon
id|anakinfb_get_var
c_func
(paren
op_amp
id|display.var
comma
l_int|0
comma
op_amp
id|fb_info
)paren
suffix:semicolon
id|display.visual
op_assign
id|FB_VISUAL_TRUECOLOR
suffix:semicolon
id|display.type
op_assign
id|FB_TYPE_PACKED_PIXELS
suffix:semicolon
id|display.type_aux
op_assign
l_int|0
suffix:semicolon
id|display.ypanstep
op_assign
l_int|0
suffix:semicolon
id|display.ywrapstep
op_assign
l_int|0
suffix:semicolon
id|display.line_length
op_assign
l_int|400
op_star
l_int|2
suffix:semicolon
id|display.can_soft_blank
op_assign
l_int|1
suffix:semicolon
id|display.inverse
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef FBCON_HAS_CFB16
id|display.dispsw
op_assign
op_amp
id|fbcon_cfb16
suffix:semicolon
id|display.dispsw_data
op_assign
id|colreg
suffix:semicolon
macro_line|#else
id|display.dispsw
op_assign
op_amp
id|fbcon_dummy
suffix:semicolon
macro_line|#endif
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
id|EINVAL
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Tak-Shing Chan &lt;chan@aleph1.co.uk&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Anakin framebuffer driver&quot;
)paren
suffix:semicolon
id|MODULE_SUPPORTED_DEVICE
c_func
(paren
l_string|&quot;fb&quot;
)paren
suffix:semicolon
eof
