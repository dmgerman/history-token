multiline_comment|/*&n; *      linux/drivers/video/pmag-ba-fb.c&n; *&n; *&t;PMAG-BA TurboChannel framebuffer card support ... derived from:&n; *&t;&quot;HP300 Topcat framebuffer support (derived from macfb of all things)&n; *&t;Phil Blundell &lt;philb@gnu.org&gt; 1998&quot;, the original code can be&n; *      found in the file hpfb.c in the same directory.&n; *&n; *&t;Based on digital document:&n; * &t;&quot;PMAG-BA TURBOchannel Color Frame Buffer&n; *&t; Functional Specification&quot;, Revision 1.2, August 27, 1990&n; *&n; *      DECstation related code Copyright (C) 1999, 2000, 2001 by&n; *      Michael Engel &lt;engel@unix-ag.org&gt;, &n; *      Karsten Merker &lt;merker@linuxtag.org&gt; and&n; *&t;Harald Koerfgen.&n; *      This file is subject to the terms and conditions of the GNU General&n; *      Public License.  See the file COPYING in the main directory of this&n; *      archive for more details.&n; *&n; */
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
macro_line|#include &lt;video/pmag-ba-fb.h&gt;
DECL|struct|pmag_ba_ramdac_regs
r_struct
id|pmag_ba_ramdac_regs
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
multiline_comment|/*&n; * Max 3 TURBOchannel slots -&gt; max 3 PMAG-BA :)&n; */
DECL|variable|pmagba_fb_info
r_static
r_struct
id|fb_info
id|pmagba_fb_info
(braket
l_int|3
)braket
suffix:semicolon
DECL|variable|pmagbafb_defined
r_static
r_struct
id|fb_var_screeninfo
id|pmagbafb_defined
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
l_int|864
comma
dot
id|xres_virtual
op_assign
l_int|1024
comma
dot
id|yres_virtual
op_assign
l_int|864
comma
dot
id|bits_per_pixel
op_assign
l_int|8
comma
dot
id|red.length
op_assign
l_int|8
comma
dot
id|green.length
op_assign
l_int|8
comma
dot
id|blue.length
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
l_int|274
comma
dot
id|width
op_assign
l_int|195
comma
dot
id|accel
op_assign
id|FB_ACCEL_NONE
comma
dot
id|vmode
op_assign
id|FB_VMODE_NONINTERLACED
comma
)brace
suffix:semicolon
DECL|variable|pmagbafb_fix
r_static
r_struct
id|fb_fix_screeninfo
id|pmagbafb_fix
op_assign
(brace
dot
id|id
op_assign
l_string|&quot;PMAG-BA&quot;
comma
dot
id|smem_len
op_assign
(paren
l_int|1024
op_star
l_int|864
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
suffix:semicolon
multiline_comment|/*&n; * Turn hardware cursor off&n; */
DECL|function|pmagbafb_erase_cursor
r_void
id|pmagbafb_erase_cursor
c_func
(paren
r_struct
id|pmag_ba_ramdac_regs
op_star
id|bt459_regs
)paren
(brace
id|bt459_regs-&gt;addr_low
op_assign
l_int|0
suffix:semicolon
id|bt459_regs-&gt;addr_hi
op_assign
l_int|3
suffix:semicolon
id|bt459_regs-&gt;data
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Set the palette. &n; */
DECL|function|pmagbafb_setcolreg
r_static
r_int
id|pmagbafb_setcolreg
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
r_struct
id|pmag_ba_ramdac_regs
op_star
id|bt459_regs
op_assign
(paren
r_struct
id|pmag_ba_ramdac_regs
op_star
)paren
id|info-&gt;par
suffix:semicolon
r_if
c_cond
(paren
id|regno
op_ge
id|info-&gt;cmap.len
)paren
r_return
l_int|1
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
id|bt459_regs-&gt;addr_low
op_assign
(paren
id|__u8
)paren
id|regno
suffix:semicolon
id|bt459_regs-&gt;addr_hi
op_assign
l_int|0
suffix:semicolon
id|bt459_regs-&gt;cmap
op_assign
id|red
suffix:semicolon
id|bt459_regs-&gt;cmap
op_assign
id|green
suffix:semicolon
id|bt459_regs-&gt;cmap
op_assign
id|blue
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|pmagbafb_ops
r_static
r_struct
id|fb_ops
id|pmagbafb_ops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|fb_get_fix
op_assign
id|gen_get_fix
comma
dot
id|fb_get_var
op_assign
id|gen_get_var
comma
dot
id|fb_setcolreg
op_assign
id|pmagbafb_setcolreg
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
DECL|function|pmagbafb_init_one
r_int
id|__init
id|pmagbafb_init_one
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
id|fb_info
op_star
id|info
op_assign
op_amp
id|pmagba_fb_info
(braket
id|slot
)braket
suffix:semicolon
r_struct
id|display
op_star
id|disp
op_assign
op_amp
id|pmagba_disp
(braket
id|slot
)braket
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;PMAG-BA framebuffer in slot %d&bslash;n&quot;
comma
id|slot
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Framebuffer display memory base address and friends&n;&t; */
id|pmagbafb_fix.smem_start
op_assign
id|base_addr
op_plus
id|PMAG_BA_ONBOARD_FBMEM_OFFSET
suffix:semicolon
id|info-&gt;par
op_assign
(paren
id|base_addr
op_plus
id|PMAG_BA_BT459_OFFSET
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Configure the Bt459 RAM DAC&n;&t; */
id|pmagbafb_erase_cursor
c_func
(paren
(paren
r_struct
id|pmag_ba_ramdac_regs
op_star
)paren
id|info-&gt;par
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *      Let there be consoles..&n;&t; */
id|info-&gt;fbops
op_assign
op_amp
id|pmagbafb_ops
suffix:semicolon
id|info-&gt;var
op_assign
id|pmagbafb_defined
suffix:semicolon
id|info-&gt;fix
op_assign
id|pmagbafb_fix
suffix:semicolon
id|info-&gt;screen_base
op_assign
id|pmagbafb_fix.smem_start
suffix:semicolon
id|info-&gt;flags
op_assign
id|FBINFO_DEFAULT
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
id|info
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
DECL|function|pmagbafb_init
r_int
id|__init
id|pmagbafb_init
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
id|fb_get_options
c_func
(paren
l_string|&quot;pmagbafb&quot;
comma
l_int|NULL
)paren
)paren
r_return
op_minus
id|ENODEV
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
l_string|&quot;PMAG-BA&quot;
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
id|pmagbafb_init_one
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
DECL|variable|pmagbafb_init
id|module_init
c_func
(paren
id|pmagbafb_init
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
