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
id|u32
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
DECL|variable|anakinfb_var
r_static
r_struct
id|fb_var_screeninfo
id|anakinfb_var
op_assign
(brace
id|xres
suffix:colon
l_int|400
comma
id|yres
suffix:colon
l_int|234
comma
id|xres_virtual
suffix:colon
l_int|400
comma
id|yres_virtual
suffix:colon
l_int|234
comma
id|bits_per_pixel
suffix:colon
l_int|16
comma
id|red
suffix:colon
(brace
l_int|11
comma
l_int|5
comma
l_int|0
)brace
comma
id|green
suffix:colon
(brace
l_int|5
comma
l_int|6
comma
l_int|0
)brace
comma
id|blue
suffix:colon
(brace
l_int|0
comma
l_int|5
comma
l_int|0
)brace
comma
id|activate
suffix:colon
id|FB_ACTIVATE_NOW
comma
id|height
suffix:colon
op_minus
l_int|1
comma
id|width
suffix:colon
op_minus
l_int|1
comma
id|vmode
suffix:colon
id|FB_VMODE_NONINTERLACED
comma
)brace
suffix:semicolon
DECL|variable|anakinfb_fix
r_static
r_struct
id|fb_fix_screeninfo
id|anakinfb_fix
op_assign
(brace
id|id
suffix:colon
l_string|&quot;AnakinFB&quot;
comma
id|smem_start
suffix:colon
id|VGA_START
comma
id|smem_len
suffix:colon
id|VGA_SIZE
comma
id|type
suffix:colon
id|FB_TYPE_PACKED_PIXELS
comma
id|visual
suffix:colon
id|FB_VISUAL_TRUECOLOR
comma
id|line_length
suffix:colon
l_int|400
op_star
l_int|2
comma
id|accel
suffix:colon
id|FB_ACCEL_NONE
comma
)brace
suffix:semicolon
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
id|gen_get_fix
comma
id|fb_get_var
suffix:colon
id|gen_get_var
comma
id|fb_set_var
suffix:colon
id|gen_set_var
comma
id|fb_get_cmap
suffix:colon
id|gen_get_cmap
comma
id|fb_set_cmap
suffix:colon
id|gen_set_cmap
comma
id|fb_setcolreg
suffix:colon
id|anakinfb_setcolreg
comma
id|fb_fillrect
suffix:colon
id|cfb_fillrect
comma
id|fb_copyarea
suffix:colon
id|cfb_copyarea
comma
id|fb_imageblit
suffix:colon
id|cfb_imageblit
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
id|strcpy
c_func
(paren
id|fb_info.modename
comma
id|anakinfb_fix.id
)paren
suffix:semicolon
id|fb_info.node
op_assign
id|fb_info.currcon
op_assign
op_minus
l_int|1
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
id|fb_info.var
op_assign
id|anakinfb_var
suffix:semicolon
id|fb_info.fix
op_assign
id|anakinfb_fix
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
id|gen_switch_con
suffix:semicolon
id|fb_info.updatevar
op_assign
id|gen_update_var
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|request_mem_region
c_func
(paren
id|VGA_START
comma
id|VGA_SIZE
comma
l_string|&quot;vga&quot;
)paren
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
id|fb_info.screen_base
op_assign
id|ioremap
c_func
(paren
id|VGA_START
comma
id|VGA_SIZE
)paren
)paren
(brace
id|release_mem_region
c_func
(paren
id|VGA_START
comma
id|VGA_SIZE
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|fb_alloc_cmap
c_func
(paren
op_amp
id|fb_info.cmap
comma
l_int|16
comma
l_int|0
)paren
suffix:semicolon
id|gen_set_disp
c_func
(paren
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
id|iounmap
c_func
(paren
id|display.screen_base
)paren
suffix:semicolon
id|release_mem_region
c_func
(paren
id|VGA_START
comma
id|VGA_SIZE
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
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
