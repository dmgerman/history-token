multiline_comment|/*&n; *      linux/drivers/video/maxinefb.c&n; *&n; *&t;DECstation 5000/xx onboard framebuffer support ... derived from:&n; *&t;&quot;HP300 Topcat framebuffer support (derived from macfb of all things)&n; *&t;Phil Blundell &lt;philb@gnu.org&gt; 1998&quot;, the original code can be&n; *      found in the file hpfb.c in the same directory.&n; *&n; *      DECstation related code Copyright (C) 1999,2000,2001 by&n; *      Michael Engel &lt;engel@unix-ag.org&gt; and&n; *      Karsten Merker &lt;merker@linuxtag.org&gt;.&n; *      This file is subject to the terms and conditions of the GNU General&n; *      Public License.  See the file COPYING in the main directory of this&n; *      archive for more details.&n; *&n; */
multiline_comment|/*&n; * Changes:&n; * 2001/01/27 removed debugging and testing code, fixed fb_ops&n; *            initialization which had caused a crash before,&n; *            general cleanup, first official release (KM)&n; *&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/fb.h&gt;
macro_line|#include &quot;maxinefb.h&quot;
multiline_comment|/* bootinfo.h defines the machine type values, needed when checking */
multiline_comment|/* whether are really running on a maxine, KM                       */
macro_line|#include &lt;asm/bootinfo.h&gt;
DECL|variable|fb_info
r_static
r_struct
id|fb_info
id|fb_info
suffix:semicolon
DECL|variable|maxinefb_defined
r_static
r_struct
id|fb_var_screeninfo
id|maxinefb_defined
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
l_int|768
comma
dot
id|xres_virtual
op_assign
l_int|1024
comma
dot
id|yres_virtual
op_assign
l_int|768
comma
dot
id|bits_per_pixel
op_assign
l_int|8
comma
dot
id|activate
op_assign
id|FB_ACTIVATE_NOW
comma
dot
id|height
op_assign
op_minus
l_int|1
comma
dot
id|width
op_assign
op_minus
l_int|1
comma
dot
id|vmode
op_assign
id|FB_VMODE_NONINTERLACED
comma
)brace
suffix:semicolon
DECL|variable|maxinefb_fix
r_static
r_struct
id|fb_fix_screeninfo
id|maxinefb_fix
op_assign
(brace
dot
id|id
op_assign
l_string|&quot;Maxine onboard graphics 1024x768x8&quot;
comma
dot
id|smem_len
op_assign
(paren
l_int|1024
op_star
l_int|768
)paren
comma
dot
id|type
op_assign
id|FB_TYPE_PACKED_PIXELS
comma
dot
id|visual
op_assign
id|FB_VISUAL_PSEUDOCOLOR
comma
dot
id|line_length
op_assign
l_int|1024
comma
)brace
multiline_comment|/* Reference to machine type set in arch/mips/dec/prom/identify.c, KM */
r_extern
r_int
r_int
id|mips_machtype
suffix:semicolon
multiline_comment|/* Handle the funny Inmos RamDAC/video controller ... */
DECL|function|maxinefb_ims332_write_register
r_void
id|maxinefb_ims332_write_register
c_func
(paren
r_int
id|regno
comma
r_register
r_int
r_int
id|val
)paren
(brace
r_register
r_int
r_char
op_star
id|regs
op_assign
(paren
r_char
op_star
)paren
id|MAXINEFB_IMS332_ADDRESS
suffix:semicolon
r_int
r_char
op_star
id|wptr
suffix:semicolon
id|wptr
op_assign
id|regs
op_plus
l_int|0xa0000
op_plus
(paren
id|regno
op_lshift
l_int|4
)paren
suffix:semicolon
op_star
(paren
(paren
r_volatile
r_int
r_int
op_star
)paren
(paren
id|regs
)paren
)paren
op_assign
(paren
id|val
op_rshift
l_int|8
)paren
op_amp
l_int|0xff00
suffix:semicolon
op_star
(paren
(paren
r_volatile
r_int
r_int
op_star
)paren
(paren
id|wptr
)paren
)paren
op_assign
id|val
suffix:semicolon
)brace
DECL|function|maxinefb_ims332_read_register
r_int
r_int
id|maxinefb_ims332_read_register
c_func
(paren
r_int
id|regno
)paren
(brace
r_register
r_int
r_char
op_star
id|regs
op_assign
(paren
r_char
op_star
)paren
id|MAXINEFB_IMS332_ADDRESS
suffix:semicolon
r_int
r_char
op_star
id|rptr
suffix:semicolon
r_register
r_int
r_int
id|j
comma
id|k
suffix:semicolon
id|rptr
op_assign
id|regs
op_plus
l_int|0x80000
op_plus
(paren
id|regno
op_lshift
l_int|4
)paren
suffix:semicolon
id|j
op_assign
op_star
(paren
(paren
r_volatile
r_int
r_int
op_star
)paren
id|rptr
)paren
suffix:semicolon
id|k
op_assign
op_star
(paren
(paren
r_volatile
r_int
r_int
op_star
)paren
id|regs
)paren
suffix:semicolon
r_return
(paren
id|j
op_amp
l_int|0xffff
)paren
op_or
(paren
(paren
id|k
op_amp
l_int|0xff00
)paren
op_lshift
l_int|8
)paren
suffix:semicolon
)brace
multiline_comment|/* Set the palette */
DECL|function|maxinefb_setcolreg
r_static
r_int
id|maxinefb_setcolreg
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
multiline_comment|/* value to be written into the palette reg. */
r_int
r_int
id|hw_colorvalue
op_assign
l_int|0
suffix:semicolon
id|red
op_rshift_assign
l_int|8
suffix:semicolon
multiline_comment|/* The cmap fields are 16 bits    */
id|green
op_rshift_assign
l_int|8
suffix:semicolon
multiline_comment|/* wide, but the harware colormap */
id|blue
op_rshift_assign
l_int|8
suffix:semicolon
multiline_comment|/* registers are only 8 bits wide */
id|hw_colorvalue
op_assign
(paren
id|blue
op_lshift
l_int|16
)paren
op_plus
(paren
id|green
op_lshift
l_int|8
)paren
op_plus
(paren
id|red
)paren
suffix:semicolon
id|maxinefb_ims332_write_register
c_func
(paren
id|IMS332_REG_COLOR_PALETTE
op_plus
id|regno
comma
id|hw_colorvalue
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|maxinefb_ops
r_static
r_struct
id|fb_ops
id|maxinefb_ops
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
id|maxinefb_setcolreg
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
DECL|function|maxinefb_init
r_int
id|__init
id|maxinefb_init
c_func
(paren
r_void
)paren
(brace
r_volatile
r_int
r_char
op_star
id|fboff
suffix:semicolon
r_int
r_int
id|fb_start
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/* Validate we&squot;re on the proper machine type */
r_if
c_cond
(paren
id|mips_machtype
op_ne
id|MACH_DS5000_XX
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Maxinefb: Personal DECstation detected&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Maxinefb: initializing onboard framebuffer&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Framebuffer display memory base address */
id|fb_start
op_assign
id|DS5000_xx_ONBOARD_FBMEM_START
suffix:semicolon
multiline_comment|/* Clear screen */
r_for
c_loop
(paren
id|fboff
op_assign
id|fb_start
suffix:semicolon
id|fboff
OL
id|fb_start
op_plus
l_int|0x1ffff
suffix:semicolon
id|fboff
op_increment
)paren
op_star
id|fboff
op_assign
l_int|0x0
suffix:semicolon
id|maxinefb_fix.smem_start
op_assign
id|fb_start
suffix:semicolon
multiline_comment|/* erase hardware cursor */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|512
suffix:semicolon
id|i
op_increment
)paren
(brace
id|maxinefb_ims332_write_register
c_func
(paren
id|IMS332_REG_CURSOR_RAM
op_plus
id|i
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;   if (i&amp;0x8 == 0)&n;&t;&t;   maxinefb_ims332_write_register (IMS332_REG_CURSOR_RAM + i, 0x0f);&n;&t;&t;   else&n;&t;&t;   maxinefb_ims332_write_register (IMS332_REG_CURSOR_RAM + i, 0xf0);&n;&t;&t; */
)brace
id|fb_info.node
op_assign
id|NODEV
suffix:semicolon
id|fb_info.fbops
op_assign
op_amp
id|maxinefb_ops
suffix:semicolon
id|fb_info.screen_base
op_assign
(paren
r_char
op_star
)paren
id|maxinefb_fix.smem_start
suffix:semicolon
id|fb_info.var
op_assign
id|maxinefb_defined
suffix:semicolon
id|fb_info.fix
op_assign
id|maxinefb_fix
suffix:semicolon
id|fb_info.flags
op_assign
id|FBINFO_FLAG_DEFAULT
suffix:semicolon
id|fb_alloc_cmap
c_func
(paren
op_amp
id|fb_info.cmap
comma
l_int|256
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
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|maxinefb_exit
r_static
r_void
id|__exit
id|maxinefb_exit
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
)brace
macro_line|#ifdef MODULE
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|maxinefb_init
id|module_init
c_func
(paren
id|maxinefb_init
)paren
suffix:semicolon
macro_line|#endif
DECL|variable|maxinefb_exit
id|module_exit
c_func
(paren
id|maxinefb_exit
)paren
suffix:semicolon
eof
