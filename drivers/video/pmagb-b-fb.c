multiline_comment|/*&n; *      linux/drivers/video/pmagb-b-fb.c&n; *&n; *&t;PMAGB-B TurboChannel framebuffer card support ... derived from:&n; *&t;&quot;HP300 Topcat framebuffer support (derived from macfb of all things)&n; *&t;Phil Blundell &lt;philb@gnu.org&gt; 1998&quot;, the original code can be&n; *      found in the file hpfb.c in the same directory.&n; *&n; *      DECstation related code Copyright (C) 1999, 2000, 2001 by&n; *      Michael Engel &lt;engel@unix-ag.org&gt;,&n; *      Karsten Merker &lt;merker@linuxtag.org&gt; and &n; *&t;Harald Koerfgen.&n; *      This file is subject to the terms and conditions of the GNU General&n; *      Public License.  See the file COPYING in the main directory of this&n; *      archive for more details.&n; *&n; */
multiline_comment|/*&n; *      We currently only support the PMAGB-B in high resolution mode&n; *      as I know of no way to detect low resolution mode set via jumper.&n; *      KM, 2001/01/07&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/fb.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/dec/machtype.h&gt;
macro_line|#include &lt;asm/dec/tc.h&gt;
macro_line|#include &quot;pmagb-b-fb.h&quot;
macro_line|#include &lt;video/fbcon.h&gt;
macro_line|#include &lt;video/fbcon-mfb.h&gt;
macro_line|#include &lt;video/fbcon-cfb2.h&gt;
macro_line|#include &lt;video/fbcon-cfb4.h&gt;
macro_line|#include &lt;video/fbcon-cfb8.h&gt;
DECL|macro|arraysize
mdefine_line|#define arraysize(x)    (sizeof(x)/sizeof(*(x)))
DECL|struct|pmagb_b_ramdac_regs
r_struct
id|pmagb_b_ramdac_regs
(brace
DECL|member|addr_low
r_int
r_char
id|addr_low
suffix:semicolon
DECL|member|pad0
r_int
r_char
id|pad0
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|addr_hi
r_int
r_char
id|addr_hi
suffix:semicolon
DECL|member|pad1
r_int
r_char
id|pad1
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|data
r_int
r_char
id|data
suffix:semicolon
DECL|member|pad2
r_int
r_char
id|pad2
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|cmap
r_int
r_char
id|cmap
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|pmagb_b_my_fb_info
r_struct
id|pmagb_b_my_fb_info
(brace
DECL|member|info
r_struct
id|fb_info
id|info
suffix:semicolon
DECL|member|bt459_regs
r_struct
id|pmagb_b_ramdac_regs
op_star
id|bt459_regs
suffix:semicolon
DECL|member|pmagbb_fb_start
r_int
r_int
id|pmagbb_fb_start
suffix:semicolon
DECL|member|pmagbb_fb_size
r_int
r_int
id|pmagbb_fb_size
suffix:semicolon
DECL|member|pmagbb_fb_line_length
r_int
r_int
id|pmagbb_fb_line_length
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|disp
r_static
r_struct
id|display
id|disp
suffix:semicolon
multiline_comment|/*&n; * Max 3 TURBOchannel slots -&gt; max 3 PMAGB-B :)&n; */
DECL|variable|pmagbb_fb_info
r_static
r_struct
id|pmagb_b_my_fb_info
id|pmagbb_fb_info
(braket
l_int|3
)braket
suffix:semicolon
DECL|variable|pmagbbfb_defined
r_static
r_struct
id|fb_var_screeninfo
id|pmagbbfb_defined
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
DECL|struct|pmagbbfb_par
r_struct
id|pmagbbfb_par
(brace
)brace
suffix:semicolon
DECL|variable|current_par
r_struct
id|pmagbbfb_par
id|current_par
suffix:semicolon
DECL|function|pmagbbfb_encode_var
r_static
r_void
id|pmagbbfb_encode_var
c_func
(paren
r_struct
id|fb_var_screeninfo
op_star
id|var
comma
r_struct
id|pmagbbfb_par
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
l_int|1280
suffix:semicolon
id|var-&gt;yres
op_assign
l_int|1024
suffix:semicolon
id|var-&gt;xres_virtual
op_assign
l_int|1280
suffix:semicolon
id|var-&gt;yres_virtual
op_assign
l_int|1024
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
DECL|function|pmagbbfb_get_par
r_static
r_void
id|pmagbbfb_get_par
c_func
(paren
r_struct
id|pmagbbfb_par
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
DECL|function|pmagbb_fb_update_var
r_static
r_int
id|pmagbb_fb_update_var
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
DECL|function|pmagbb_do_fb_set_var
r_static
r_int
id|pmagbb_do_fb_set_var
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
id|pmagbbfb_par
id|par
suffix:semicolon
id|pmagbbfb_get_par
c_func
(paren
op_amp
id|par
)paren
suffix:semicolon
id|pmagbbfb_encode_var
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
multiline_comment|/*&n; * Turn hardware cursor off&n; */
DECL|function|pmagbbfb_erase_cursor
r_void
id|pmagbbfb_erase_cursor
c_func
(paren
r_struct
id|pmagb_b_my_fb_info
op_star
id|info
)paren
(brace
id|info-&gt;bt459_regs-&gt;addr_low
op_assign
l_int|0
suffix:semicolon
id|info-&gt;bt459_regs-&gt;addr_hi
op_assign
l_int|3
suffix:semicolon
id|info-&gt;bt459_regs-&gt;data
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Write to a Bt459 color map register&n; */
DECL|function|pmagb_b_bt459_write_colormap
r_void
id|pmagb_b_bt459_write_colormap
c_func
(paren
r_struct
id|pmagb_b_my_fb_info
op_star
id|info
comma
r_int
id|reg
comma
id|__u8
id|red
comma
id|__u8
id|green
comma
id|__u8
id|blue
)paren
(brace
id|info-&gt;bt459_regs-&gt;addr_low
op_assign
(paren
id|__u8
)paren
id|reg
suffix:semicolon
id|info-&gt;bt459_regs-&gt;addr_hi
op_assign
l_int|0
suffix:semicolon
id|info-&gt;bt459_regs-&gt;cmap
op_assign
id|red
suffix:semicolon
id|info-&gt;bt459_regs-&gt;cmap
op_assign
id|green
suffix:semicolon
id|info-&gt;bt459_regs-&gt;cmap
op_assign
id|blue
suffix:semicolon
)brace
multiline_comment|/*&n; * Get the palette&n; */
DECL|function|pmagbbfb_get_cmap
r_static
r_int
id|pmagbbfb_get_cmap
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
multiline_comment|/*&n;&t;&t; * TODO&n;&t;&t; */
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Set the palette. &n; */
DECL|function|pmagbbfb_set_cmap
r_static
r_int
id|pmagbbfb_set_cmap
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
id|__u8
id|cmap_red
comma
id|cmap_green
comma
id|cmap_blue
suffix:semicolon
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
id|length
op_assign
l_int|256
op_minus
(paren
id|cmap-&gt;start
)paren
suffix:semicolon
r_else
id|length
op_assign
id|cmap-&gt;len
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
id|pmagb_b_bt459_write_colormap
c_func
(paren
(paren
r_struct
id|pmagb_b_my_fb_info
op_star
)paren
id|info
comma
id|cmap-&gt;start
op_plus
id|i
comma
id|cmap_red
comma
id|cmap_green
comma
id|cmap_blue
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pmagbbfb_get_var
r_static
r_int
id|pmagbbfb_get_var
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
id|pmagbbfb_par
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
id|pmagbbfb_get_par
c_func
(paren
op_amp
id|par
)paren
suffix:semicolon
id|pmagbbfb_encode_var
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
DECL|function|pmagbbfb_set_var
r_static
r_int
id|pmagbbfb_set_var
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
id|pmagbb_do_fb_set_var
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
DECL|function|pmagbbfb_encode_fix
r_static
r_void
id|pmagbbfb_encode_fix
c_func
(paren
r_struct
id|fb_fix_screeninfo
op_star
id|fix
comma
r_struct
id|pmagbbfb_par
op_star
id|par
comma
r_struct
id|pmagb_b_my_fb_info
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
l_string|&quot;PMAGB-BA&quot;
)paren
suffix:semicolon
id|fix-&gt;smem_start
op_assign
id|info-&gt;pmagbb_fb_start
suffix:semicolon
id|fix-&gt;smem_len
op_assign
id|info-&gt;pmagbb_fb_size
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
id|info-&gt;pmagbb_fb_line_length
suffix:semicolon
)brace
DECL|function|pmagbbfb_get_fix
r_static
r_int
id|pmagbbfb_get_fix
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
id|pmagbbfb_par
id|par
suffix:semicolon
id|pmagbbfb_get_par
c_func
(paren
op_amp
id|par
)paren
suffix:semicolon
id|pmagbbfb_encode_fix
c_func
(paren
id|fix
comma
op_amp
id|par
comma
(paren
r_struct
id|pmagb_b_my_fb_info
op_star
)paren
id|info
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pmagbbfb_ioctl
r_static
r_int
id|pmagbbfb_ioctl
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
r_int
r_int
id|cmd
comma
r_int
r_int
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
DECL|function|pmagbbfb_switch
r_static
r_int
id|pmagbbfb_switch
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
id|pmagbb_do_fb_set_var
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
id|info-&gt;currcon
op_assign
id|con
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* 0 unblank, 1 blank, 2 no vsync, 3 no hsync, 4 off */
DECL|function|pmagbbfb_blank
r_static
r_void
id|pmagbbfb_blank
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
multiline_comment|/* Not supported */
)brace
DECL|function|pmagbbfb_open
r_static
r_int
id|pmagbbfb_open
c_func
(paren
r_struct
id|fb_info
op_star
id|info
comma
r_int
id|user
)paren
(brace
multiline_comment|/*&n;&t; * Nothing, only a usage count for the moment&n;&t; */
id|MOD_INC_USE_COUNT
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|pmagbbfb_set_disp
r_static
r_void
id|pmagbbfb_set_disp
c_func
(paren
r_int
id|con
comma
r_struct
id|pmagb_b_my_fb_info
op_star
id|info
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
id|pmagbbfb_get_fix
c_func
(paren
op_amp
id|fix
comma
id|con
comma
(paren
r_struct
id|fb_info
op_star
)paren
id|info
)paren
suffix:semicolon
id|display-&gt;screen_base
op_assign
(paren
r_char
op_star
)paren
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
DECL|function|pmagbbfb_release
r_static
r_int
id|pmagbbfb_release
c_func
(paren
r_struct
id|fb_info
op_star
id|info
comma
r_int
id|user
)paren
(brace
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
DECL|variable|pmagbbfb_ops
r_static
r_struct
id|fb_ops
id|pmagbbfb_ops
op_assign
(brace
id|owner
suffix:colon
id|THIS_MODULE
comma
id|fb_open
suffix:colon
id|pmagbbfb_open
comma
id|fb_release
suffix:colon
id|pmagbbfb_release
comma
id|fb_get_fix
suffix:colon
id|pmagbbfb_get_fix
comma
id|fb_get_var
suffix:colon
id|pmagbbfb_get_var
comma
id|fb_set_var
suffix:colon
id|pmagbbfb_set_var
comma
id|fb_get_cmap
suffix:colon
id|pmagbbfb_get_cmap
comma
id|fb_set_cmap
suffix:colon
id|pmagbbfb_set_cmap
comma
id|fb_ioctl
suffix:colon
id|pmagbbfb_ioctl
comma
id|fb_mmap
suffix:colon
l_int|0
comma
id|fb_rasterimg
suffix:colon
l_int|0
)brace
suffix:semicolon
DECL|function|pmagbbfb_init_one
r_int
id|__init
id|pmagbbfb_init_one
c_func
(paren
r_int
id|slot
)paren
(brace
r_int
r_int
id|base_addr
op_assign
id|get_tc_base_addr
c_func
(paren
id|slot
)paren
suffix:semicolon
r_struct
id|pmagb_b_my_fb_info
op_star
id|ip
op_assign
(paren
r_struct
id|pmagb_b_my_fb_info
op_star
)paren
op_amp
id|pmagbb_fb_info
(braket
id|slot
)braket
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;PMAGB-BA framebuffer in slot %d&bslash;n&quot;
comma
id|slot
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Framebuffer display memory base address and friends&n;&t; */
id|ip-&gt;bt459_regs
op_assign
(paren
r_struct
id|pmagb_b_ramdac_regs
op_star
)paren
(paren
id|base_addr
op_plus
id|PMAGB_B_BT459_OFFSET
)paren
suffix:semicolon
id|ip-&gt;pmagbb_fb_start
op_assign
id|base_addr
op_plus
id|PMAGB_B_ONBOARD_FBMEM_OFFSET
suffix:semicolon
id|ip-&gt;pmagbb_fb_size
op_assign
l_int|1280
op_star
l_int|1024
suffix:semicolon
id|ip-&gt;pmagbb_fb_line_length
op_assign
l_int|1280
suffix:semicolon
multiline_comment|/*&n;&t; * Configure the Bt459 RAM DAC&n;&t; */
id|pmagbbfb_erase_cursor
c_func
(paren
id|ip
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *      Fill in the available video resolution&n;&t; */
id|pmagbbfb_defined.xres
op_assign
l_int|1280
suffix:semicolon
id|pmagbbfb_defined.yres
op_assign
l_int|1024
suffix:semicolon
id|pmagbbfb_defined.xres_virtual
op_assign
l_int|1280
suffix:semicolon
id|pmagbbfb_defined.yres_virtual
op_assign
l_int|1024
suffix:semicolon
id|pmagbbfb_defined.bits_per_pixel
op_assign
l_int|8
suffix:semicolon
multiline_comment|/*&n;&t; *      Let there be consoles..&n;&t; */
id|strcpy
c_func
(paren
id|ip-&gt;info.modename
comma
l_string|&quot;PMAGB-BA&quot;
)paren
suffix:semicolon
id|ip-&gt;info.changevar
op_assign
l_int|NULL
suffix:semicolon
id|ip-&gt;info.node
op_assign
id|NODEV
suffix:semicolon
id|ip-&gt;info.fbops
op_assign
op_amp
id|pmagbbfb_ops
suffix:semicolon
id|ip-&gt;info.disp
op_assign
op_amp
id|disp
suffix:semicolon
id|ip-&gt;info.currcon
op_assign
op_minus
l_int|1
suffix:semicolon
id|ip-&gt;info.switch_con
op_assign
op_amp
id|pmagbbfb_switch
suffix:semicolon
id|ip-&gt;info.updatevar
op_assign
op_amp
id|pmagbb_fb_update_var
suffix:semicolon
id|ip-&gt;info.blank
op_assign
op_amp
id|pmagbbfb_blank
suffix:semicolon
id|ip-&gt;info.flags
op_assign
id|FBINFO_FLAG_DEFAULT
suffix:semicolon
id|pmagbb_do_fb_set_var
c_func
(paren
op_amp
id|pmagbbfb_defined
comma
l_int|1
)paren
suffix:semicolon
id|pmagbbfb_get_var
c_func
(paren
op_amp
id|disp.var
comma
op_minus
l_int|1
comma
(paren
r_struct
id|fb_info
op_star
)paren
id|ip
)paren
suffix:semicolon
id|pmagbbfb_set_disp
c_func
(paren
op_minus
l_int|1
comma
id|ip
)paren
suffix:semicolon
r_if
c_cond
(paren
id|register_framebuffer
c_func
(paren
(paren
r_struct
id|fb_info
op_star
)paren
id|ip
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
multiline_comment|/* &n; * Initialise the framebuffer&n; */
DECL|function|pmagbbfb_init
r_int
id|__init
id|pmagbbfb_init
c_func
(paren
r_void
)paren
(brace
r_int
id|sid
suffix:semicolon
r_int
id|found
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|TURBOCHANNEL
)paren
(brace
r_while
c_loop
(paren
(paren
id|sid
op_assign
id|search_tc_card
c_func
(paren
l_string|&quot;PMAGB-BA&quot;
)paren
)paren
op_ge
l_int|0
)paren
(brace
id|found
op_assign
l_int|1
suffix:semicolon
id|claim_tc_card
c_func
(paren
id|sid
)paren
suffix:semicolon
id|pmagbbfb_init_one
c_func
(paren
id|sid
)paren
suffix:semicolon
)brace
r_return
id|found
ques
c_cond
l_int|0
suffix:colon
op_minus
id|ENODEV
suffix:semicolon
)brace
r_else
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
)brace
DECL|function|pmagbbfb_setup
r_int
id|__init
id|pmagbbfb_setup
c_func
(paren
r_char
op_star
id|options
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
