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
macro_line|#include &lt;video/fbcon.h&gt;
macro_line|#include &quot;maxinefb.h&quot;
multiline_comment|/* bootinfo.h defines the machine type values, needed when checking */
multiline_comment|/* whether are really running on a maxine, KM                       */
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;video/fbcon-mfb.h&gt;
macro_line|#include &lt;video/fbcon-cfb2.h&gt;
macro_line|#include &lt;video/fbcon-cfb4.h&gt;
macro_line|#include &lt;video/fbcon-cfb8.h&gt;
DECL|macro|arraysize
mdefine_line|#define arraysize(x)    (sizeof(x)/sizeof(*(x)))
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
DECL|variable|fb_start
DECL|variable|fb_size
DECL|variable|fb_line_length
r_int
r_int
id|fb_start
comma
id|fb_size
op_assign
l_int|1024
op_star
l_int|768
comma
id|fb_line_length
op_assign
l_int|1024
suffix:semicolon
DECL|variable|fb_regs
r_int
r_int
id|fb_regs
suffix:semicolon
DECL|variable|fb_bitmask
r_int
r_char
id|fb_bitmask
suffix:semicolon
DECL|variable|maxinefb_defined
r_static
r_struct
id|fb_var_screeninfo
id|maxinefb_defined
op_assign
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* W,H, W, H (virtual) load xres,xres_virtual */
l_int|0
comma
l_int|0
comma
multiline_comment|/* virtual -&gt; visible no offset */
l_int|0
comma
multiline_comment|/* depth -&gt; load bits_per_pixel */
l_int|0
comma
multiline_comment|/* greyscale ? */
(brace
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* R */
(brace
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* G */
(brace
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* B */
(brace
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* transparency */
l_int|0
comma
multiline_comment|/* standard pixel format */
id|FB_ACTIVATE_NOW
comma
l_int|274
comma
l_int|195
comma
multiline_comment|/* 14&quot; monitor */
id|FB_ACCEL_NONE
comma
l_int|0L
comma
l_int|0L
comma
l_int|0L
comma
l_int|0L
comma
l_int|0L
comma
l_int|0L
comma
l_int|0L
comma
l_int|0
comma
multiline_comment|/* No sync info */
id|FB_VMODE_NONINTERLACED
comma
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
)brace
suffix:semicolon
DECL|struct|maxinefb_par
r_struct
id|maxinefb_par
(brace
)brace
suffix:semicolon
DECL|variable|currcon
r_static
r_int
id|currcon
op_assign
l_int|0
suffix:semicolon
DECL|variable|current_par
r_struct
id|maxinefb_par
id|current_par
suffix:semicolon
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
DECL|function|maxinefb_encode_var
r_static
r_void
id|maxinefb_encode_var
c_func
(paren
r_struct
id|fb_var_screeninfo
op_star
id|var
comma
r_struct
id|maxinefb_par
op_star
id|par
)paren
(brace
r_int
id|i
op_assign
l_int|0
suffix:semicolon
id|var-&gt;xres
op_assign
l_int|1024
suffix:semicolon
id|var-&gt;yres
op_assign
l_int|768
suffix:semicolon
id|var-&gt;xres_virtual
op_assign
l_int|1024
suffix:semicolon
id|var-&gt;yres_virtual
op_assign
l_int|768
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
l_int|8
suffix:semicolon
id|var-&gt;grayscale
op_assign
l_int|0
suffix:semicolon
id|var-&gt;transp.offset
op_assign
l_int|0
suffix:semicolon
id|var-&gt;transp.length
op_assign
l_int|0
suffix:semicolon
id|var-&gt;transp.msb_right
op_assign
l_int|0
suffix:semicolon
id|var-&gt;nonstd
op_assign
l_int|0
suffix:semicolon
id|var-&gt;activate
op_assign
l_int|1
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
id|var-&gt;vmode
op_assign
id|FB_VMODE_NONINTERLACED
suffix:semicolon
id|var-&gt;pixclock
op_assign
l_int|0
suffix:semicolon
id|var-&gt;sync
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
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|arraysize
c_func
(paren
id|var-&gt;reserved
)paren
suffix:semicolon
id|i
op_increment
)paren
id|var-&gt;reserved
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|maxinefb_get_par
r_static
r_void
id|maxinefb_get_par
c_func
(paren
r_struct
id|maxinefb_par
op_star
id|par
)paren
(brace
op_star
id|par
op_assign
id|current_par
suffix:semicolon
)brace
DECL|function|maxinefb_fb_update_var
r_static
r_int
id|maxinefb_fb_update_var
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
DECL|function|maxinefb_do_fb_set_var
r_static
r_int
id|maxinefb_do_fb_set_var
c_func
(paren
r_struct
id|fb_var_screeninfo
op_star
id|var
comma
r_int
id|isactive
)paren
(brace
r_struct
id|maxinefb_par
id|par
suffix:semicolon
id|maxinefb_get_par
c_func
(paren
op_amp
id|par
)paren
suffix:semicolon
id|maxinefb_encode_var
c_func
(paren
id|var
comma
op_amp
id|par
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Get the palette */
DECL|function|maxinefb_get_cmap
r_static
r_int
id|maxinefb_get_cmap
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
r_int
id|i
suffix:semicolon
r_int
r_int
id|hw_colorvalue
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* raw color value from the register */
r_int
r_int
id|length
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|cmap-&gt;start
)paren
op_plus
(paren
id|cmap-&gt;len
)paren
)paren
op_ge
l_int|256
)paren
(brace
id|length
op_assign
l_int|256
op_minus
(paren
id|cmap-&gt;start
)paren
suffix:semicolon
)brace
r_else
(brace
id|length
op_assign
id|cmap-&gt;len
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
id|length
suffix:semicolon
id|i
op_increment
)paren
(brace
id|hw_colorvalue
op_assign
id|maxinefb_ims332_read_register
c_func
(paren
id|IMS332_REG_COLOR_PALETTE
op_plus
id|cmap-&gt;start
op_plus
id|i
)paren
suffix:semicolon
(paren
id|cmap-&gt;red
(braket
id|i
)braket
)paren
op_assign
(paren
(paren
id|hw_colorvalue
op_amp
l_int|0x0000ff
)paren
)paren
suffix:semicolon
(paren
id|cmap-&gt;green
(braket
id|i
)braket
)paren
op_assign
(paren
(paren
id|hw_colorvalue
op_amp
l_int|0x00ff00
)paren
op_rshift
l_int|8
)paren
suffix:semicolon
(paren
id|cmap-&gt;blue
(braket
id|i
)braket
)paren
op_assign
(paren
(paren
id|hw_colorvalue
op_amp
l_int|0xff0000
)paren
op_rshift
l_int|16
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Set the palette */
DECL|function|maxinefb_set_cmap
r_static
r_int
id|maxinefb_set_cmap
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
r_int
id|i
suffix:semicolon
r_int
r_int
id|hw_colorvalue
suffix:semicolon
multiline_comment|/* value to be written into the palette reg. */
r_int
r_int
id|cmap_red
suffix:semicolon
r_int
r_int
id|cmap_green
suffix:semicolon
r_int
r_int
id|cmap_blue
suffix:semicolon
r_int
r_int
id|length
suffix:semicolon
id|hw_colorvalue
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|cmap-&gt;start
)paren
op_plus
(paren
id|cmap-&gt;len
)paren
)paren
op_ge
l_int|256
)paren
(brace
id|length
op_assign
l_int|256
op_minus
(paren
id|cmap-&gt;start
)paren
suffix:semicolon
)brace
r_else
(brace
id|length
op_assign
id|cmap-&gt;len
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
id|length
suffix:semicolon
id|i
op_increment
)paren
(brace
id|cmap_red
op_assign
(paren
(paren
id|cmap-&gt;red
(braket
id|i
)braket
)paren
op_rshift
l_int|8
)paren
suffix:semicolon
multiline_comment|/* The cmap fields are 16 bits    */
id|cmap_green
op_assign
(paren
(paren
id|cmap-&gt;green
(braket
id|i
)braket
)paren
op_rshift
l_int|8
)paren
suffix:semicolon
multiline_comment|/* wide, but the harware colormap */
id|cmap_blue
op_assign
(paren
(paren
id|cmap-&gt;blue
(braket
id|i
)braket
)paren
op_rshift
l_int|8
)paren
suffix:semicolon
multiline_comment|/* registers are only 8 bits wide */
id|hw_colorvalue
op_assign
(paren
id|cmap_blue
op_lshift
l_int|16
)paren
op_plus
(paren
id|cmap_green
op_lshift
l_int|8
)paren
op_plus
(paren
id|cmap_red
)paren
suffix:semicolon
id|maxinefb_ims332_write_register
c_func
(paren
id|IMS332_REG_COLOR_PALETTE
op_plus
id|cmap-&gt;start
op_plus
id|i
comma
id|hw_colorvalue
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|maxinefb_get_var
r_static
r_int
id|maxinefb_get_var
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
id|maxinefb_par
id|par
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
id|maxinefb_get_par
c_func
(paren
op_amp
id|par
)paren
suffix:semicolon
id|maxinefb_encode_var
c_func
(paren
id|var
comma
op_amp
id|par
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
DECL|function|maxinefb_set_var
r_static
r_int
id|maxinefb_set_var
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
(paren
id|err
op_assign
id|maxinefb_do_fb_set_var
c_func
(paren
id|var
comma
l_int|1
)paren
)paren
)paren
r_return
id|err
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|maxinefb_encode_fix
r_static
r_void
id|maxinefb_encode_fix
c_func
(paren
r_struct
id|fb_fix_screeninfo
op_star
id|fix
comma
r_struct
id|maxinefb_par
op_star
id|par
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
l_string|&quot;maxinefb&quot;
)paren
suffix:semicolon
multiline_comment|/* fix-&gt;id is a char[16], so a maximum of 15 characters, KM */
id|fix-&gt;smem_start
op_assign
(paren
r_char
op_star
)paren
id|fb_start
suffix:semicolon
multiline_comment|/* display memory base address, KM */
id|fix-&gt;smem_len
op_assign
id|fb_size
suffix:semicolon
id|fix-&gt;type
op_assign
id|FB_TYPE_PACKED_PIXELS
suffix:semicolon
id|fix-&gt;visual
op_assign
id|FB_VISUAL_PSEUDOCOLOR
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
id|fb_line_length
suffix:semicolon
)brace
DECL|function|maxinefb_get_fix
r_static
r_int
id|maxinefb_get_fix
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
id|maxinefb_par
id|par
suffix:semicolon
id|maxinefb_get_par
c_func
(paren
op_amp
id|par
)paren
suffix:semicolon
id|maxinefb_encode_fix
c_func
(paren
id|fix
comma
op_amp
id|par
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|maxinefb_switch
r_static
r_int
id|maxinefb_switch
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
id|maxinefb_do_fb_set_var
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
)paren
suffix:semicolon
id|currcon
op_assign
id|con
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|maxinefb_set_disp
r_static
r_void
id|maxinefb_set_disp
c_func
(paren
r_int
id|con
)paren
(brace
r_struct
id|fb_fix_screeninfo
id|fix
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
id|maxinefb_get_fix
c_func
(paren
op_amp
id|fix
comma
id|con
comma
l_int|0
)paren
suffix:semicolon
id|display-&gt;screen_base
op_assign
id|fix.smem_start
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
id|display-&gt;next_line
op_assign
id|fix.line_length
suffix:semicolon
id|display-&gt;can_soft_blank
op_assign
l_int|0
suffix:semicolon
id|display-&gt;inverse
op_assign
l_int|0
suffix:semicolon
id|display-&gt;dispsw
op_assign
op_amp
id|fbcon_cfb8
suffix:semicolon
)brace
DECL|variable|maxinefb_ops
r_static
r_struct
id|fb_ops
id|maxinefb_ops
op_assign
(brace
id|owner
suffix:colon
id|THIS_MODULE
comma
id|fb_get_fix
suffix:colon
id|maxinefb_get_fix
comma
id|fb_get_var
suffix:colon
id|maxinefb_get_var
comma
id|fb_set_var
suffix:colon
id|maxinefb_set_var
comma
id|fb_get_cmap
suffix:colon
id|maxinefb_get_cmap
comma
id|fb_set_cmap
suffix:colon
id|maxinefb_set_cmap
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
multiline_comment|/* Fill in the available video resolution */
id|maxinefb_defined.xres
op_assign
l_int|1024
suffix:semicolon
id|maxinefb_defined.yres
op_assign
l_int|768
suffix:semicolon
id|maxinefb_defined.xres_virtual
op_assign
l_int|1024
suffix:semicolon
id|maxinefb_defined.yres_virtual
op_assign
l_int|768
suffix:semicolon
id|maxinefb_defined.bits_per_pixel
op_assign
l_int|8
suffix:semicolon
multiline_comment|/* Let there be consoles... */
id|strcpy
c_func
(paren
id|fb_info.modename
comma
l_string|&quot;Maxine onboard graphics 1024x768x8&quot;
)paren
suffix:semicolon
multiline_comment|/* fb_info.modename: maximum of 39 characters + trailing nullbyte, KM */
id|fb_info.changevar
op_assign
l_int|NULL
suffix:semicolon
id|fb_info.node
op_assign
op_minus
l_int|1
suffix:semicolon
id|fb_info.fbops
op_assign
op_amp
id|maxinefb_ops
suffix:semicolon
id|fb_info.disp
op_assign
op_amp
id|disp
suffix:semicolon
id|fb_info.switch_con
op_assign
op_amp
id|maxinefb_switch
suffix:semicolon
id|fb_info.updatevar
op_assign
op_amp
id|maxinefb_fb_update_var
suffix:semicolon
id|fb_info.blank
op_assign
l_int|NULL
suffix:semicolon
id|fb_info.flags
op_assign
id|FBINFO_FLAG_DEFAULT
suffix:semicolon
id|maxinefb_do_fb_set_var
c_func
(paren
op_amp
id|maxinefb_defined
comma
l_int|1
)paren
suffix:semicolon
id|maxinefb_get_var
c_func
(paren
op_amp
id|disp.var
comma
op_minus
l_int|1
comma
op_amp
id|fb_info
)paren
suffix:semicolon
id|maxinefb_set_disp
c_func
(paren
op_minus
l_int|1
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
