multiline_comment|/*&n; *  linux/drivers/video/anakinfb.c&n; *&n; *  Copyright (C) 2001 Aleph One Ltd. for Acunia N.V.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  Changelog:&n; *   23-Apr-2001 TTC&t;Created&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/fb.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;asm/io.h&gt;
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
DECL|variable|anakinfb_var
r_static
r_struct
id|fb_var_screeninfo
id|anakinfb_var
op_assign
(brace
dot
id|xres
op_assign
l_int|400
comma
dot
id|yres
op_assign
l_int|234
comma
dot
id|xres_virtual
op_assign
l_int|400
comma
dot
id|yres_virtual
op_assign
l_int|234
comma
dot
id|bits_per_pixel
op_assign
l_int|16
comma
dot
id|red
op_assign
(brace
l_int|11
comma
l_int|5
comma
l_int|0
)brace
comma
dot
id|green
op_assign
(brace
l_int|5
comma
l_int|6
comma
l_int|0
)brace
comma
dot
id|blue
op_assign
(brace
l_int|0
comma
l_int|5
comma
l_int|0
)brace
comma
dot
id|activate
id|FB_ACTIVATE_NOW
comma
dot
id|height
op_minus
l_int|1
comma
dot
id|width
op_minus
l_int|1
comma
dot
id|vmode
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
dot
id|id
op_assign
l_string|&quot;AnakinFB&quot;
comma
dot
id|smem_start
op_assign
id|VGA_START
comma
dot
id|smem_len
op_assign
id|VGA_SIZE
comma
dot
id|type
op_assign
id|FB_TYPE_PACKED_PIXELS
comma
dot
id|visual
op_assign
id|FB_VISUAL_TRUECOLOR
comma
dot
id|line_length
op_assign
l_int|400
op_star
l_int|2
comma
dot
id|accel
op_assign
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
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|fb_setcolreg
op_assign
id|anakinfb_setcolreg
comma
dot
id|fb_fillrect
op_assign
id|cfb_fillrect
comma
dot
id|fb_copyarea
op_assign
id|cfb_copyarea
comma
dot
id|fb_imageblit
op_assign
id|cfb_imageblit
comma
dot
id|fb_cursor
op_assign
id|cfb_cursor
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
id|fb_info.var
op_assign
id|anakinfb_var
suffix:semicolon
id|fb_info.fix
op_assign
id|anakinfb_fix
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
id|fb_info.screen_base
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
