multiline_comment|/*&n; * linux/drivers/video/stifb.c - Generic frame buffer driver for HP&n; * workstations with STI (standard text interface) video firmware.&n; *&n; * Based on:&n; * linux/drivers/video/artistfb.c -- Artist frame buffer driver&n; *&n; *&t;Copyright (C) 2000 Philipp Rumpf &lt;prumpf@tux.org&gt;&n; *&n; *  based on skeletonfb, which was&n; *&t;Created 28 Dec 1997 by Geert Uytterhoeven&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file COPYING in the main directory of this archive&n; * for more details.  */
multiline_comment|/*&n; * Notes:&n; *&n; * This driver assumes that the video has been set up in 1bpp mode by&n; * the firmware.  Since HP video tends to be planar rather than&n; * packed-pixel this will probably work anyway even if it isn&squot;t.&n; */
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
macro_line|#include &quot;sti.h&quot;
DECL|variable|stifb_ops
r_static
r_struct
id|fb_ops
id|stifb_ops
suffix:semicolon
DECL|struct|stifb_info
r_struct
id|stifb_info
(brace
DECL|member|gen
r_struct
id|fb_info_gen
id|gen
suffix:semicolon
DECL|member|sti
r_struct
id|sti_struct
op_star
id|sti
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|stifb_par
r_struct
id|stifb_par
(brace
)brace
suffix:semicolon
DECL|variable|fb_info
r_static
r_struct
id|stifb_info
id|fb_info
suffix:semicolon
DECL|variable|disp
r_static
r_struct
id|display
id|disp
suffix:semicolon
r_int
id|stifb_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|stifb_setup
c_func
(paren
r_char
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|display_switch
id|fbcon_sti
suffix:semicolon
multiline_comment|/* ------------------- chipset specific functions -------------------------- */
r_static
r_int
DECL|function|sti_encode_fix
id|sti_encode_fix
c_func
(paren
r_struct
id|fb_fix_screeninfo
op_star
id|fix
comma
r_const
r_void
op_star
id|par
comma
r_struct
id|fb_info_gen
op_star
id|info
)paren
(brace
multiline_comment|/* XXX: what about smem_len? */
id|fix-&gt;smem_start
op_assign
id|PTR_STI
c_func
(paren
id|fb_info.sti-&gt;glob_cfg
)paren
op_member_access_from_pointer
id|region_ptrs
(braket
l_int|1
)braket
suffix:semicolon
id|fix-&gt;type
op_assign
id|FB_TYPE_PLANES
suffix:semicolon
multiline_comment|/* well, sort of */
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|sti_decode_var
id|sti_decode_var
c_func
(paren
r_const
r_struct
id|fb_var_screeninfo
op_star
id|var
comma
r_void
op_star
id|par
comma
r_struct
id|fb_info_gen
op_star
id|info
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|sti_encode_var
id|sti_encode_var
c_func
(paren
r_struct
id|fb_var_screeninfo
op_star
id|var
comma
r_const
r_void
op_star
id|par
comma
r_struct
id|fb_info_gen
op_star
id|info
)paren
(brace
id|var-&gt;xres
op_assign
id|PTR_STI
c_func
(paren
id|fb_info.sti-&gt;glob_cfg
)paren
op_member_access_from_pointer
id|onscreen_x
suffix:semicolon
id|var-&gt;yres
op_assign
id|PTR_STI
c_func
(paren
id|fb_info.sti-&gt;glob_cfg
)paren
op_member_access_from_pointer
id|onscreen_y
suffix:semicolon
id|var-&gt;xres_virtual
op_assign
id|PTR_STI
c_func
(paren
id|fb_info.sti-&gt;glob_cfg
)paren
op_member_access_from_pointer
id|total_x
suffix:semicolon
id|var-&gt;yres_virtual
op_assign
id|PTR_STI
c_func
(paren
id|fb_info.sti-&gt;glob_cfg
)paren
op_member_access_from_pointer
id|total_y
suffix:semicolon
id|var-&gt;xoffset
op_assign
id|var-&gt;yoffset
op_assign
l_int|0
suffix:semicolon
id|var-&gt;bits_per_pixel
op_assign
l_int|1
suffix:semicolon
id|var-&gt;grayscale
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_void
DECL|function|sti_get_par
id|sti_get_par
c_func
(paren
r_void
op_star
id|par
comma
r_struct
id|fb_info_gen
op_star
id|info
)paren
(brace
)brace
r_static
r_void
DECL|function|sti_set_par
id|sti_set_par
c_func
(paren
r_const
r_void
op_star
id|par
comma
r_struct
id|fb_info_gen
op_star
id|info
)paren
(brace
)brace
r_static
r_int
DECL|function|sti_getcolreg
id|sti_getcolreg
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
DECL|function|sti_set_disp
id|sti_set_disp
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
id|disp-&gt;dispsw
op_assign
op_amp
id|fbcon_sti
suffix:semicolon
)brace
r_static
r_void
DECL|function|sti_detect
id|sti_detect
c_func
(paren
r_void
)paren
(brace
)brace
multiline_comment|/* ------------ Interfaces to hardware functions ------------ */
DECL|variable|sti_switch
r_struct
id|fbgen_hwswitch
id|sti_switch
op_assign
(brace
id|detect
suffix:colon
id|sti_detect
comma
id|encode_fix
suffix:colon
id|sti_encode_fix
comma
id|decode_var
suffix:colon
id|sti_decode_var
comma
id|encode_var
suffix:colon
id|sti_encode_var
comma
id|get_par
suffix:colon
id|sti_get_par
comma
id|set_par
suffix:colon
id|sti_set_par
comma
id|getcolreg
suffix:colon
id|sti_getcolreg
comma
id|set_disp
suffix:colon
id|sti_set_disp
)brace
suffix:semicolon
multiline_comment|/* ------------ Hardware Independent Functions ------------ */
multiline_comment|/*&n;     *  Initialization&n;     */
r_int
id|__init
DECL|function|stifb_init
id|stifb_init
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;searching for word mode STI ROMs&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* XXX: in the future this will return a list of ROMs */
r_if
c_cond
(paren
(paren
id|fb_info.sti
op_assign
id|sti_init_roms
c_func
(paren
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
id|fb_info.gen.info.node
op_assign
id|NODEV
suffix:semicolon
id|fb_info.gen.info.flags
op_assign
id|FBINFO_FLAG_DEFAULT
suffix:semicolon
id|fb_info.gen.info.fbops
op_assign
op_amp
id|stifb_ops
suffix:semicolon
id|fb_info.gen.info.disp
op_assign
op_amp
id|disp
suffix:semicolon
id|fb_info.gen.info.changevar
op_assign
l_int|NULL
suffix:semicolon
id|fb_info.gen.info.switch_con
op_assign
op_amp
id|fbgen_switch
suffix:semicolon
id|fb_info.gen.info.updatevar
op_assign
op_amp
id|fbgen_update_var
suffix:semicolon
id|strcpy
c_func
(paren
id|fb_info.gen.info.modename
comma
l_string|&quot;STI Generic&quot;
)paren
suffix:semicolon
id|fb_info.gen.fbhw
op_assign
op_amp
id|sti_switch
suffix:semicolon
id|fb_info.gen.fbhw
op_member_access_from_pointer
id|detect
c_func
(paren
)paren
suffix:semicolon
id|fb_info.gen.info.screen_base
op_assign
(paren
r_void
op_star
)paren
id|PTR_STI
c_func
(paren
id|fb_info.sti-&gt;glob_cfg
)paren
op_member_access_from_pointer
id|region_ptrs
(braket
l_int|1
)braket
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
id|fbgen_install_cmap
c_func
(paren
l_int|0
comma
op_amp
id|fb_info.gen
)paren
suffix:semicolon
id|pdc_console_die
c_func
(paren
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
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;     *  Cleanup&n;     */
r_void
DECL|function|stifb_cleanup
id|stifb_cleanup
c_func
(paren
r_struct
id|fb_info
op_star
id|info
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;stifb_cleanup: you&squot;re on crack&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_int
id|__init
DECL|function|stifb_setup
id|stifb_setup
c_func
(paren
r_char
op_star
id|options
)paren
(brace
multiline_comment|/* XXX: we should take the resolution, bpp as command line arguments. */
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* ------------------------------------------------------------------------- */
DECL|variable|stifb_ops
r_static
r_struct
id|fb_ops
id|stifb_ops
op_assign
(brace
id|owner
suffix:colon
id|THIS_MODULE
comma
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
id|fb_pan_display
suffix:colon
id|fbgen_pan_display
comma
id|fb_blank
suffix:colon
id|fbgen_blank
comma
)brace
suffix:semicolon
eof
