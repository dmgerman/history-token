multiline_comment|/*&n; * linux/drivers/video/skeletonfb.c -- Skeleton for a frame buffer device&n; *&n; *  Created 28 Dec 1997 by Geert Uytterhoeven&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file COPYING in the main directory of this archive&n; * for more details.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/fb.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;video/fbcon.h&gt;
multiline_comment|/*&n;     *  This is just simple sample code.&n;     *&n;     *  No warranty that it actually compiles.&n;     *  Even less warranty that it actually works :-)&n;     */
DECL|struct|xxxfb_info
r_struct
id|xxxfb_info
(brace
multiline_comment|/*&n;     *  Choose _one_ of the two alternatives:&n;     *&n;     *    1. Use the generic frame buffer operations (fbgen_*).&n;     */
DECL|member|gen
r_struct
id|fb_info_gen
id|gen
suffix:semicolon
multiline_comment|/*&n;     *    2. Provide your own frame buffer operations.&n;     */
DECL|member|info
r_struct
id|fb_info
id|info
suffix:semicolon
multiline_comment|/* Here starts the frame buffer device dependent part */
multiline_comment|/* You can use this to store e.g. the board number if you support */
multiline_comment|/* multiple boards */
)brace
suffix:semicolon
DECL|struct|xxxfb_par
r_struct
id|xxxfb_par
(brace
multiline_comment|/*&n;     *  The hardware specific data in this structure uniquely defines a video&n;     *  mode.&n;     *&n;     *  If your hardware supports only one video mode, you can leave it empty.&n;     */
)brace
suffix:semicolon
multiline_comment|/*&n;     *  If your driver supports multiple boards, you should make these arrays,&n;     *  or allocate them dynamically (using kmalloc()).&n;     */
DECL|variable|fb_info
r_static
r_struct
id|xxxfb_info
id|fb_info
suffix:semicolon
DECL|variable|current_par
r_static
r_struct
id|xxxfb_par
id|current_par
suffix:semicolon
DECL|variable|current_par_valid
r_static
r_int
id|current_par_valid
op_assign
l_int|0
suffix:semicolon
DECL|variable|disp
r_static
r_struct
id|display
id|disp
suffix:semicolon
DECL|variable|default_var
r_static
r_struct
id|fb_var_screeninfo
id|default_var
suffix:semicolon
DECL|variable|inverse
r_static
r_int
id|inverse
op_assign
l_int|0
suffix:semicolon
r_int
id|xxxfb_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|xxxfb_setup
c_func
(paren
r_char
op_star
)paren
suffix:semicolon
multiline_comment|/* ------------------- chipset specific functions -------------------------- */
DECL|function|xxx_detect
r_static
r_void
id|xxx_detect
c_func
(paren
r_void
)paren
(brace
multiline_comment|/*&n;     *  This function should detect the current video mode settings and store&n;     *  it as the default video mode&n;     */
r_struct
id|xxxfb_par
id|par
suffix:semicolon
multiline_comment|/* ... */
id|xxx_get_par
c_func
(paren
op_amp
id|par
)paren
suffix:semicolon
id|xxx_encode_var
c_func
(paren
op_amp
id|default_var
comma
op_amp
id|par
)paren
suffix:semicolon
)brace
DECL|function|xxx_encode_fix
r_static
r_int
id|xxx_encode_fix
c_func
(paren
r_struct
id|fb_fix_screeninfo
op_star
id|fix
comma
r_struct
id|xxxfb_par
op_star
id|par
comma
r_const
r_struct
id|fb_info
op_star
id|info
)paren
(brace
multiline_comment|/*&n;     *  This function should fill in the &squot;fix&squot; structure based on the values&n;     *  in the `par&squot; structure.&n;     */
multiline_comment|/* ... */
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|xxx_decode_var
r_static
r_int
id|xxx_decode_var
c_func
(paren
r_struct
id|fb_var_screeninfo
op_star
id|var
comma
r_struct
id|xxxfb_par
op_star
id|par
comma
r_const
r_struct
id|fb_info
op_star
id|info
)paren
(brace
multiline_comment|/*&n;     *  Get the video params out of &squot;var&squot;. If a value doesn&squot;t fit, round it up,&n;     *  if it&squot;s too big, return -EINVAL.&n;     *&n;     *  Suggestion: Round up in the following order: bits_per_pixel, xres,&n;     *  yres, xres_virtual, yres_virtual, xoffset, yoffset, grayscale,&n;     *  bitfields, horizontal timing, vertical timing.&n;     */
multiline_comment|/* ... */
multiline_comment|/* pixclock in picos, htotal in pixels, vtotal in scanlines */
r_if
c_cond
(paren
op_logical_neg
id|fbmon_valid_timings
c_func
(paren
id|pixclock
comma
id|htotal
comma
id|vtotal
comma
id|info
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|xxx_encode_var
r_static
r_int
id|xxx_encode_var
c_func
(paren
r_struct
id|fb_var_screeninfo
op_star
id|var
comma
r_struct
id|xxxfb_par
op_star
id|par
comma
r_const
r_struct
id|fb_info
op_star
id|info
)paren
(brace
multiline_comment|/*&n;     *  Fill the &squot;var&squot; structure based on the values in &squot;par&squot; and maybe other&n;     *  values read out of the hardware.&n;     */
multiline_comment|/* ... */
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|xxx_get_par
r_static
r_void
id|xxx_get_par
c_func
(paren
r_struct
id|xxxfb_par
op_star
id|par
comma
r_const
r_struct
id|fb_info
op_star
id|info
)paren
(brace
multiline_comment|/*&n;     *  Fill the hardware&squot;s &squot;par&squot; structure.&n;     */
r_if
c_cond
(paren
id|current_par_valid
)paren
op_star
id|par
op_assign
id|current_par
suffix:semicolon
r_else
(brace
multiline_comment|/* ... */
)brace
)brace
DECL|function|xxx_set_par
r_static
r_void
id|xxx_set_par
c_func
(paren
r_struct
id|xxxfb_par
op_star
id|par
comma
r_const
r_struct
id|fb_info
op_star
id|info
)paren
(brace
multiline_comment|/*&n;     *  Set the hardware according to &squot;par&squot;.&n;     */
id|current_par
op_assign
op_star
id|par
suffix:semicolon
id|current_par_valid
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* ... */
)brace
DECL|function|xxx_getcolreg
r_static
r_int
id|xxx_getcolreg
c_func
(paren
r_int
id|regno
comma
r_int
op_star
id|red
comma
r_int
op_star
id|green
comma
r_int
op_star
id|blue
comma
r_int
op_star
id|transp
comma
r_const
r_struct
id|fb_info
op_star
id|info
)paren
(brace
multiline_comment|/*&n;     *  Read a single color register and split it into colors/transparent.&n;     *  The return values must have a 16 bit magnitude.&n;     *  Return != 0 for invalid regno.&n;     */
multiline_comment|/* ... */
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|xxxfb_setcolreg
r_static
r_int
id|xxxfb_setcolreg
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
r_const
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
OL
l_int|16
)paren
(brace
multiline_comment|/*&n;&t; *  Make the first 16 colors of the palette available to fbcon&n;&t; */
r_if
c_cond
(paren
id|is_cfb15
)paren
multiline_comment|/* RGB 555 */
dot
dot
dot
id|fbcon_cmap.cfb16
(braket
id|regno
)braket
op_assign
(paren
(paren
id|red
op_amp
l_int|0xf800
)paren
op_rshift
l_int|1
)paren
op_or
(paren
(paren
id|green
op_amp
l_int|0xf800
)paren
op_rshift
l_int|6
)paren
op_or
(paren
(paren
id|blue
op_amp
l_int|0xf800
)paren
op_rshift
l_int|11
)paren
suffix:semicolon
r_if
c_cond
(paren
id|is_cfb16
)paren
multiline_comment|/* RGB 565 */
dot
dot
dot
id|fbcon_cmap.cfb16
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
(paren
id|green
op_amp
l_int|0xfc00
)paren
op_rshift
l_int|5
)paren
op_or
(paren
(paren
id|blue
op_amp
l_int|0xf800
)paren
op_rshift
l_int|11
)paren
suffix:semicolon
r_if
c_cond
(paren
id|is_cfb24
)paren
multiline_comment|/* RGB 888 */
dot
dot
dot
id|fbcon_cmap.cfb24
(braket
id|regno
)braket
op_assign
(paren
(paren
id|red
op_amp
l_int|0xff00
)paren
op_lshift
l_int|8
)paren
op_or
(paren
id|green
op_amp
l_int|0xff00
)paren
op_or
(paren
(paren
id|blue
op_amp
l_int|0xff00
)paren
op_rshift
l_int|8
)paren
suffix:semicolon
r_if
c_cond
(paren
id|is_cfb32
)paren
multiline_comment|/* RGBA 8888 */
dot
dot
dot
id|fbcon_cmap.cfb32
(braket
id|regno
)braket
op_assign
(paren
(paren
id|red
op_amp
l_int|0xff00
)paren
op_lshift
l_int|16
)paren
op_or
(paren
(paren
id|green
op_amp
l_int|0xff00
)paren
op_lshift
l_int|8
)paren
op_or
(paren
id|blue
op_amp
l_int|0xff00
)paren
op_or
(paren
(paren
id|transp
op_amp
l_int|0xff00
)paren
op_rshift
l_int|8
)paren
suffix:semicolon
)brace
multiline_comment|/* ... */
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|xxx_pan_display
r_static
r_int
id|xxx_pan_display
c_func
(paren
r_struct
id|fb_var_screeninfo
op_star
id|var
comma
r_struct
id|xxxfb_par
op_star
id|par
comma
r_const
r_struct
id|fb_info
op_star
id|info
)paren
(brace
multiline_comment|/*&n;     *  Pan (or wrap, depending on the `vmode&squot; field) the display using the&n;     *  `xoffset&squot; and `yoffset&squot; fields of the `var&squot; structure.&n;     *  If the values don&squot;t fit, return -EINVAL.&n;     */
multiline_comment|/* ... */
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|xxx_blank
r_static
r_int
id|xxx_blank
c_func
(paren
r_int
id|blank_mode
comma
r_const
r_struct
id|fb_info
op_star
id|info
)paren
(brace
multiline_comment|/*&n;     *  Blank the screen if blank_mode != 0, else unblank. If blank == NULL&n;     *  then the caller blanks by setting the CLUT (Color Look Up Table) to all&n;     *  black. Return 0 if blanking succeeded, != 0 if un-/blanking failed due&n;     *  to e.g. a video mode which doesn&squot;t support it. Implements VESA suspend&n;     *  and powerdown modes on hardware that supports disabling hsync/vsync:&n;     *    blank_mode == 2: suspend vsync&n;     *    blank_mode == 3: suspend hsync&n;     *    blank_mode == 4: powerdown&n;     */
multiline_comment|/* ... */
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|xxx_set_disp
r_static
r_void
id|xxx_set_disp
c_func
(paren
r_const
r_void
op_star
id|par
comma
r_struct
id|display
op_star
id|disp
comma
r_struct
id|fb_info_gen
op_star
id|info
)paren
(brace
multiline_comment|/*&n;     *  Fill in a pointer with the virtual address of the mapped frame buffer.&n;     *  Fill in a pointer to appropriate low level text console operations (and&n;     *  optionally a pointer to help data) for the video mode `par&squot; of your&n;     *  video hardware. These can be generic software routines, or hardware&n;     *  accelerated routines specifically tailored for your hardware.&n;     *  If you don&squot;t have any appropriate operations, you must fill in a&n;     *  pointer to dummy operations, and there will be no text output.&n;     */
macro_line|#ifdef FBCON_HAS_CFB8
r_if
c_cond
(paren
id|is_cfb8
)paren
(brace
id|disp-&gt;dispsw
op_assign
id|fbcon_cfb8
suffix:semicolon
)brace
r_else
macro_line|#endif
macro_line|#ifdef FBCON_HAS_CFB16
r_if
c_cond
(paren
id|is_cfb16
)paren
(brace
id|disp-&gt;dispsw
op_assign
id|fbcon_cfb16
suffix:semicolon
id|disp-&gt;dispsw_data
op_assign
dot
dot
dot
id|fbcon_cmap.cfb16
suffix:semicolon
multiline_comment|/* console palette */
)brace
r_else
macro_line|#endif
macro_line|#ifdef FBCON_HAS_CFB24
r_if
c_cond
(paren
id|is_cfb24
)paren
(brace
id|disp-&gt;dispsw
op_assign
id|fbcon_cfb24
suffix:semicolon
id|disp-&gt;dispsw_data
op_assign
dot
dot
dot
id|fbcon_cmap.cfb24
suffix:semicolon
multiline_comment|/* console palette */
)brace
r_else
macro_line|#endif
macro_line|#ifdef FBCON_HAS_CFB32
r_if
c_cond
(paren
id|is_cfb32
)paren
(brace
id|disp-&gt;dispsw
op_assign
id|fbcon_cfb32
suffix:semicolon
id|disp-&gt;dispsw_data
op_assign
dot
dot
dot
id|fbcon_cmap.cfb32
suffix:semicolon
multiline_comment|/* console palette */
)brace
r_else
macro_line|#endif
id|disp-&gt;dispsw
op_assign
op_amp
id|fbcon_dummy
suffix:semicolon
)brace
multiline_comment|/* ------------ Interfaces to hardware functions ------------ */
DECL|variable|xxx_switch
r_struct
id|fbgen_hwswitch
id|xxx_switch
op_assign
(brace
id|xxx_detect
comma
id|xxx_encode_fix
comma
id|xxx_decode_var
comma
id|xxx_encode_var
comma
id|xxx_get_par
comma
id|xxx_set_par
comma
id|xxx_getcolreg
comma
id|xxx_pan_display
comma
id|xxx_blank
comma
id|xxx_set_disp
)brace
suffix:semicolon
multiline_comment|/* ------------ Hardware Independent Functions ------------ */
multiline_comment|/*&n;     *  Initialization&n;     */
DECL|function|xxxfb_init
r_int
id|__init
id|xxxfb_init
c_func
(paren
r_void
)paren
(brace
id|fb_info.gen.fbhw
op_assign
op_amp
id|xxx_switch
suffix:semicolon
id|fb_info.gen.fbhw
op_member_access_from_pointer
id|detect
c_func
(paren
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|fb_info.gen.info.modename
comma
l_string|&quot;XXX&quot;
)paren
suffix:semicolon
id|fb_info.gen.info.changevar
op_assign
l_int|NULL
suffix:semicolon
id|fb_info.gen.info.node
op_assign
id|NODEV
suffix:semicolon
id|fb_info.gen.info.fbops
op_assign
op_amp
id|xxxfb_ops
suffix:semicolon
id|fb_info.gen.info.screen_base
op_assign
id|virtual_frame_buffer_address
suffix:semicolon
id|fb_info.gen.info.disp
op_assign
op_amp
id|disp
suffix:semicolon
id|fb_info.gen.info.currcon
op_assign
op_minus
l_int|1
suffix:semicolon
id|fb_info.gen.info.switch_con
op_assign
op_amp
id|xxxfb_switch
suffix:semicolon
id|fb_info.gen.info.updatevar
op_assign
op_amp
id|xxxfb_update_var
suffix:semicolon
id|fb_info.gen.info.flags
op_assign
id|FBINFO_FLAG_DEFAULT
suffix:semicolon
multiline_comment|/* This should give a reasonable default video mode */
id|fbgen_get_var
c_func
(paren
op_amp
id|disp.var
comma
op_minus
l_int|1
comma
op_amp
id|fb_info.gen.info
)paren
suffix:semicolon
id|fbgen_do_set_var
c_func
(paren
op_amp
id|disp.var
comma
l_int|1
comma
op_amp
id|fb_info.gen
)paren
suffix:semicolon
id|fbgen_set_disp
c_func
(paren
op_minus
l_int|1
comma
op_amp
id|fb_info.gen
)paren
suffix:semicolon
id|do_install_cmap
c_func
(paren
l_int|0
comma
op_amp
id|fb_info.gen
)paren
suffix:semicolon
r_if
c_cond
(paren
id|register_framebuffer
c_func
(paren
op_amp
id|fb_info.gen.info
)paren
OL
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;fb%d: %s frame buffer device&bslash;n&quot;
comma
id|GET_FB_IDX
c_func
(paren
id|fb_info.gen.info.node
)paren
comma
id|fb_info.gen.info.modename
)paren
suffix:semicolon
multiline_comment|/* uncomment this if your driver cannot be unloaded */
multiline_comment|/* MOD_INC_USE_COUNT; */
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;     *  Cleanup&n;     */
DECL|function|xxxfb_cleanup
r_void
id|xxxfb_cleanup
c_func
(paren
r_struct
id|fb_info
op_star
id|info
)paren
(brace
multiline_comment|/*&n;     *  If your driver supports multiple boards, you should unregister and&n;     *  clean up all instances.&n;     */
id|unregister_framebuffer
c_func
(paren
id|info
)paren
suffix:semicolon
multiline_comment|/* ... */
)brace
multiline_comment|/*&n;     *  Setup&n;     */
DECL|function|xxxfb_setup
r_int
id|__init
id|xxxfb_setup
c_func
(paren
r_char
op_star
id|options
)paren
(brace
multiline_comment|/* Parse user speficied options (`video=xxxfb:&squot;) */
)brace
multiline_comment|/* ------------------------------------------------------------------------- */
multiline_comment|/*&n;     *  Frame buffer operations&n;     */
multiline_comment|/* If all you need is that - just don&squot;t define -&gt;fb_open */
DECL|function|xxxfb_open
r_static
r_int
id|xxxfb_open
c_func
(paren
r_const
r_struct
id|fb_info
op_star
id|info
comma
r_int
id|user
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* If all you need is that - just don&squot;t define -&gt;fb_release */
DECL|function|xxxfb_release
r_static
r_int
id|xxxfb_release
c_func
(paren
r_const
r_struct
id|fb_info
op_star
id|info
comma
r_int
id|user
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;     *  In most cases the `generic&squot; routines (fbgen_*) should be satisfactory.&n;     *  However, you&squot;re free to fill in your own replacements.&n;     */
DECL|variable|xxxfb_ops
r_static
r_struct
id|fb_ops
id|xxxfb_ops
op_assign
(brace
id|owner
suffix:colon
id|THIS_MODULE
comma
id|fb_open
suffix:colon
id|xxxfb_open
comma
multiline_comment|/* only if you need it to do something */
id|fb_release
suffix:colon
id|xxxfb_release
comma
multiline_comment|/* only if you need it to do something */
id|fb_get_fix
suffix:colon
id|fbgen_get_fix
comma
id|fb_get_var
suffix:colon
id|fbgen_get_var
comma
id|fb_set_var
suffix:colon
id|fbgen_set_var
comma
id|fb_get_cmap
suffix:colon
id|fbgen_get_cmap
comma
id|fb_set_cmap
suffix:colon
id|fbgen_set_cmap
comma
id|fb_setcolreg
suffix:colon
id|xxxfb_setcolreg
comma
id|fb_pan_display
suffix:colon
id|fbgen_pan_display
comma
id|fb_blank
suffix:colon
id|fbgen_blank
comma
id|fb_ioctl
suffix:colon
id|xxxfb_ioctl
comma
multiline_comment|/* optional */
)brace
suffix:semicolon
multiline_comment|/* ------------------------------------------------------------------------- */
multiline_comment|/*&n;     *  Modularization&n;     */
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
id|xxxfb_init
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
id|xxxfb_cleanup
c_func
(paren
r_void
)paren
suffix:semicolon
)brace
macro_line|#endif /* MODULE */
eof
