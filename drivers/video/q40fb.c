multiline_comment|/*&n; * linux/drivers/video/q40fb.c -- Q40 frame buffer device&n; *&n; * Copyright (C) 2001&n; *&n; *      Richard Zidlicky &lt;rz@linux-m68k.org&gt;&n; *&n; *  This file is subject to the terms and conditions of the GNU General Public&n; *  License. See the file COPYING in the main directory of this archive for&n; *  more details.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/q40_master.h&gt;
macro_line|#include &lt;linux/fb.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
DECL|macro|Q40_PHYS_SCREEN_ADDR
mdefine_line|#define Q40_PHYS_SCREEN_ADDR 0xFE800000
DECL|variable|__initdata
r_static
r_struct
id|fb_fix_screeninfo
id|q40fb_fix
id|__initdata
op_assign
(brace
dot
id|id
op_assign
l_string|&quot;Q40&quot;
comma
dot
id|smem_len
op_assign
l_int|1024
op_star
l_int|1024
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
l_int|1024
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
DECL|variable|__initdata
r_static
r_struct
id|fb_var_screeninfo
id|q40fb_var
id|__initdata
op_assign
(brace
dot
id|xres
op_assign
l_int|1024
comma
dot
id|yres
op_assign
l_int|512
comma
dot
id|xres_virtual
op_assign
l_int|1024
comma
dot
id|yres_virtual
op_assign
l_int|512
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
l_int|6
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
l_int|11
comma
l_int|5
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
l_int|6
comma
l_int|0
)brace
comma
dot
id|activate
op_assign
id|FB_ACTIVATE_NOW
comma
dot
id|height
op_assign
l_int|230
comma
dot
id|width
op_assign
l_int|300
comma
dot
id|vmode
op_assign
id|FB_VMODE_NONINTERLACED
comma
)brace
suffix:semicolon
DECL|function|q40fb_setcolreg
r_static
r_int
id|q40fb_setcolreg
c_func
(paren
r_int
id|regno
comma
r_int
id|red
comma
r_int
id|green
comma
r_int
id|blue
comma
r_int
id|transp
comma
r_struct
id|fb_info
op_star
id|info
)paren
(brace
multiline_comment|/*&n;     *  Set a single color register. The values supplied have a 16 bit&n;     *  magnitude.&n;     *  Return != 0 for invalid regno.&n;     */
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
l_int|11
suffix:semicolon
id|green
op_rshift_assign
l_int|11
suffix:semicolon
id|blue
op_rshift_assign
l_int|10
suffix:semicolon
r_if
c_cond
(paren
id|regno
OL
l_int|16
)paren
(brace
(paren
(paren
id|u32
op_star
)paren
id|info-&gt;pseudo_palette
)paren
(braket
id|regno
)braket
op_assign
(paren
(paren
id|red
op_amp
l_int|31
)paren
op_lshift
l_int|6
)paren
op_or
(paren
(paren
id|green
op_amp
l_int|31
)paren
op_lshift
l_int|11
)paren
op_or
(paren
id|blue
op_amp
l_int|63
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|q40fb_ops
r_static
r_struct
id|fb_ops
id|q40fb_ops
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
id|q40fb_setcolreg
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
id|soft_cursor
comma
)brace
suffix:semicolon
DECL|function|q40fb_probe
r_static
r_int
id|__init
id|q40fb_probe
c_func
(paren
r_struct
id|device
op_star
id|device
)paren
(brace
r_struct
id|platform_device
op_star
id|dev
op_assign
id|to_platform_device
c_func
(paren
id|device
)paren
suffix:semicolon
r_struct
id|fb_info
op_star
id|info
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|MACH_IS_Q40
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
multiline_comment|/* mapped in q40/config.c */
id|q40fb_fix.smem_start
op_assign
id|Q40_PHYS_SCREEN_ADDR
suffix:semicolon
id|info
op_assign
id|framebuffer_alloc
c_func
(paren
r_sizeof
(paren
id|u32
)paren
op_star
l_int|256
comma
op_amp
id|dev-&gt;dev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|info
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|info-&gt;var
op_assign
id|q40fb_var
suffix:semicolon
id|info-&gt;fix
op_assign
id|q40fb_fix
suffix:semicolon
id|info-&gt;fbops
op_assign
op_amp
id|q40fb_ops
suffix:semicolon
id|info-&gt;flags
op_assign
id|FBINFO_DEFAULT
suffix:semicolon
multiline_comment|/* not as module for now */
id|info-&gt;pseudo_palette
op_assign
id|info-&gt;par
suffix:semicolon
id|info-&gt;par
op_assign
l_int|NULL
suffix:semicolon
id|info-&gt;screen_base
op_assign
(paren
r_char
op_star
)paren
id|q40fb_fix.smem_start
suffix:semicolon
r_if
c_cond
(paren
id|fb_alloc_cmap
c_func
(paren
op_amp
id|info-&gt;cmap
comma
l_int|256
comma
l_int|0
)paren
OL
l_int|0
)paren
(brace
id|framebuffer_release
c_func
(paren
id|info
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|master_outb
c_func
(paren
l_int|3
comma
id|DISPLAY_CONTROL_REG
)paren
suffix:semicolon
r_if
c_cond
(paren
id|register_framebuffer
c_func
(paren
id|info
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Unable to register Q40 frame buffer&bslash;n&quot;
)paren
suffix:semicolon
id|fb_dealloc_cmap
c_func
(paren
op_amp
id|info-&gt;cmap
)paren
suffix:semicolon
id|framebuffer_release
c_func
(paren
id|info
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
l_string|&quot;fb%d: Q40 frame buffer alive and kicking !&bslash;n&quot;
comma
id|info-&gt;node
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|q40fb_driver
r_static
r_struct
id|device_driver
id|q40fb_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;q40fb&quot;
comma
dot
id|bus
op_assign
op_amp
id|platform_bus_type
comma
dot
id|probe
op_assign
id|q40fb_probe
comma
)brace
suffix:semicolon
DECL|variable|q40fb_device
r_static
r_struct
id|platform_device
id|q40fb_device
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;q40fb&quot;
comma
)brace
suffix:semicolon
DECL|function|q40fb_init
r_int
id|__init
id|q40fb_init
c_func
(paren
r_void
)paren
(brace
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
id|ret
op_assign
id|driver_register
c_func
(paren
op_amp
id|q40fb_driver
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
(brace
id|ret
op_assign
id|platform_device_register
c_func
(paren
op_amp
id|q40fb_device
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
id|driver_unregister
c_func
(paren
op_amp
id|q40fb_driver
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
