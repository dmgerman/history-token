multiline_comment|/*&n; *  platinumfb.c -- frame buffer device for the PowerMac &squot;platinum&squot; display&n; *&n; *  Copyright (C) 1998 Franz Sirl&n; *&n; *  Frame buffer structure from:&n; *    drivers/video/controlfb.c -- frame buffer device for&n; *    Apple &squot;control&squot; display chip.&n; *    Copyright (C) 1998 Dan Jacobowitz&n; *&n; *  Hardware information from:&n; *    platinum.c: Console support for PowerMac &quot;platinum&quot; display adaptor.&n; *    Copyright (C) 1996 Paul Mackerras and Mark Abene&n; *&n; *  This file is subject to the terms and conditions of the GNU General Public&n; *  License. See the file COPYING in the main directory of this archive for&n; *  more details.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/fb.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/nvram.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &quot;macmodes.h&quot;
macro_line|#include &quot;platinumfb.h&quot;
DECL|variable|default_vmode
r_static
r_int
id|default_vmode
op_assign
id|VMODE_NVRAM
suffix:semicolon
DECL|variable|default_cmode
r_static
r_int
id|default_cmode
op_assign
id|CMODE_NVRAM
suffix:semicolon
DECL|struct|fb_par_platinum
r_struct
id|fb_par_platinum
(brace
DECL|member|vmode
DECL|member|cmode
r_int
id|vmode
comma
id|cmode
suffix:semicolon
DECL|member|xres
DECL|member|yres
r_int
id|xres
comma
id|yres
suffix:semicolon
DECL|member|vxres
DECL|member|vyres
r_int
id|vxres
comma
id|vyres
suffix:semicolon
DECL|member|xoffset
DECL|member|yoffset
r_int
id|xoffset
comma
id|yoffset
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|fb_info_platinum
r_struct
id|fb_info_platinum
(brace
DECL|member|info
r_struct
id|fb_info
id|info
suffix:semicolon
DECL|member|par
r_struct
id|fb_par_platinum
id|par
suffix:semicolon
r_struct
(brace
DECL|member|red
DECL|member|green
DECL|member|blue
id|__u8
id|red
comma
id|green
comma
id|blue
suffix:semicolon
DECL|member|palette
)brace
id|palette
(braket
l_int|256
)braket
suffix:semicolon
DECL|member|pseudo_palette
id|u32
id|pseudo_palette
(braket
l_int|17
)braket
suffix:semicolon
DECL|member|cmap_regs
r_volatile
r_struct
id|cmap_regs
op_star
id|cmap_regs
suffix:semicolon
DECL|member|cmap_regs_phys
r_int
r_int
id|cmap_regs_phys
suffix:semicolon
DECL|member|platinum_regs
r_volatile
r_struct
id|platinum_regs
op_star
id|platinum_regs
suffix:semicolon
DECL|member|platinum_regs_phys
r_int
r_int
id|platinum_regs_phys
suffix:semicolon
DECL|member|frame_buffer
id|__u8
op_star
id|frame_buffer
suffix:semicolon
DECL|member|base_frame_buffer
r_volatile
id|__u8
op_star
id|base_frame_buffer
suffix:semicolon
DECL|member|frame_buffer_phys
r_int
r_int
id|frame_buffer_phys
suffix:semicolon
DECL|member|total_vram
r_int
r_int
id|total_vram
suffix:semicolon
DECL|member|clktype
r_int
id|clktype
suffix:semicolon
DECL|member|dactype
r_int
id|dactype
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Frame buffer device API&n; */
r_static
r_int
id|platinumfb_setcolreg
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
suffix:semicolon
r_static
r_int
id|platinumfb_blank
c_func
(paren
r_int
id|blank_mode
comma
r_struct
id|fb_info
op_star
id|info
)paren
suffix:semicolon
r_static
r_int
id|platinumfb_set_par
(paren
r_struct
id|fb_info
op_star
id|info
)paren
suffix:semicolon
r_static
r_int
id|platinumfb_check_var
(paren
r_struct
id|fb_var_screeninfo
op_star
id|var
comma
r_struct
id|fb_info
op_star
id|info
)paren
suffix:semicolon
multiline_comment|/*&n; * internal functions&n; */
r_static
r_void
id|platinum_of_init
c_func
(paren
r_struct
id|device_node
op_star
id|dp
)paren
suffix:semicolon
r_static
r_inline
r_int
id|platinum_vram_reqd
c_func
(paren
r_int
id|video_mode
comma
r_int
id|color_mode
)paren
suffix:semicolon
r_static
r_int
id|read_platinum_sense
c_func
(paren
r_struct
id|fb_info_platinum
op_star
id|info
)paren
suffix:semicolon
r_static
r_void
id|set_platinum_clock
c_func
(paren
r_struct
id|fb_info_platinum
op_star
id|info
)paren
suffix:semicolon
r_static
r_void
id|platinum_set_hardware
c_func
(paren
r_struct
id|fb_info_platinum
op_star
id|info
comma
r_const
r_struct
id|fb_par_platinum
op_star
id|par
)paren
suffix:semicolon
r_static
r_int
id|platinum_par_to_var
c_func
(paren
r_struct
id|fb_var_screeninfo
op_star
id|var
comma
r_const
r_struct
id|fb_par_platinum
op_star
id|par
comma
r_const
r_struct
id|fb_info_platinum
op_star
id|info
)paren
suffix:semicolon
r_static
r_int
id|platinum_var_to_par
c_func
(paren
r_const
r_struct
id|fb_var_screeninfo
op_star
id|var
comma
r_struct
id|fb_par_platinum
op_star
id|par
comma
r_const
r_struct
id|fb_info_platinum
op_star
id|info
)paren
suffix:semicolon
multiline_comment|/*&n; * Interface used by the world&n; */
r_int
id|platinum_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|platinum_setup
c_func
(paren
r_char
op_star
)paren
suffix:semicolon
DECL|variable|platinumfb_ops
r_static
r_struct
id|fb_ops
id|platinumfb_ops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|fb_check_var
op_assign
id|platinumfb_check_var
comma
dot
id|fb_set_par
op_assign
id|platinumfb_set_par
comma
dot
id|fb_setcolreg
op_assign
id|platinumfb_setcolreg
comma
dot
id|fb_blank
op_assign
id|platinumfb_blank
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
multiline_comment|/*&n; * Checks a var structure&n; */
DECL|function|platinumfb_check_var
r_static
r_int
id|platinumfb_check_var
(paren
r_struct
id|fb_var_screeninfo
op_star
id|var
comma
r_struct
id|fb_info
op_star
id|info
)paren
(brace
r_struct
id|fb_info_platinum
op_star
id|p
op_assign
(paren
r_struct
id|fb_info_platinum
op_star
)paren
id|info
suffix:semicolon
r_struct
id|fb_par_platinum
id|par
suffix:semicolon
r_int
id|err
suffix:semicolon
id|err
op_assign
id|platinum_var_to_par
c_func
(paren
id|var
comma
op_amp
id|par
comma
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_return
id|err
suffix:semicolon
id|platinum_par_to_var
c_func
(paren
id|var
comma
op_amp
id|par
comma
id|p
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Applies current var to display&n; */
DECL|function|platinumfb_set_par
r_static
r_int
id|platinumfb_set_par
(paren
r_struct
id|fb_info
op_star
id|info
)paren
(brace
r_struct
id|fb_info_platinum
op_star
id|p
op_assign
(paren
r_struct
id|fb_info_platinum
op_star
)paren
id|info
suffix:semicolon
r_struct
id|platinum_regvals
op_star
id|init
suffix:semicolon
r_struct
id|fb_par_platinum
id|par
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|platinum_var_to_par
c_func
(paren
op_amp
id|info-&gt;var
comma
op_amp
id|par
comma
id|p
)paren
)paren
)paren
(brace
id|printk
(paren
id|KERN_ERR
l_string|&quot;platinumfb_set_par: error calling&quot;
l_string|&quot; platinum_var_to_par: %d.&bslash;n&quot;
comma
id|err
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
id|platinum_set_hardware
c_func
(paren
id|p
comma
op_amp
id|par
)paren
suffix:semicolon
id|init
op_assign
id|platinum_reg_init
(braket
id|p-&gt;par.vmode
op_minus
l_int|1
)braket
suffix:semicolon
id|info-&gt;screen_base
op_assign
(paren
r_char
op_star
)paren
id|p-&gt;frame_buffer
op_plus
id|init-&gt;fb_offset
op_plus
l_int|0x20
suffix:semicolon
id|info-&gt;fix.smem_start
op_assign
(paren
id|p-&gt;frame_buffer_phys
)paren
op_plus
id|init-&gt;fb_offset
op_plus
l_int|0x20
suffix:semicolon
id|info-&gt;fix.visual
op_assign
(paren
id|p-&gt;par.cmode
op_eq
id|CMODE_8
)paren
ques
c_cond
id|FB_VISUAL_PSEUDOCOLOR
suffix:colon
id|FB_VISUAL_DIRECTCOLOR
suffix:semicolon
id|info-&gt;fix.line_length
op_assign
id|vmode_attrs
(braket
id|p-&gt;par.vmode
op_minus
l_int|1
)braket
dot
id|hres
op_star
(paren
l_int|1
op_lshift
id|p-&gt;par.cmode
)paren
op_plus
l_int|0x20
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|platinumfb_blank
r_static
r_int
id|platinumfb_blank
c_func
(paren
r_int
id|blank
comma
r_struct
id|fb_info
op_star
id|fb
)paren
(brace
multiline_comment|/*&n; *  Blank the screen if blank_mode != 0, else unblank. If blank == NULL&n; *  then the caller blanks by setting the CLUT (Color Look Up Table) to all&n; *  black. Return 0 if blanking succeeded, != 0 if un-/blanking failed due&n; *  to e.g. a video mode which doesn&squot;t support it. Implements VESA suspend&n; *  and powerdown modes on hardware that supports disabling hsync/vsync:&n; *    blank_mode == 2: suspend vsync&n; *    blank_mode == 3: suspend hsync&n; *    blank_mode == 4: powerdown&n; */
multiline_comment|/* [danj] I think there&squot;s something fishy about those constants... */
multiline_comment|/*&n;&t;struct fb_info_platinum *info = (struct fb_info_platinum *) fb;&n;&t;int&t;ctrl;&n;&n;&t;ctrl = ld_le32(&amp;info-&gt;platinum_regs-&gt;ctrl.r) | 0x33;&n;&t;if (blank)&n;&t;&t;--blank_mode;&n;&t;if (blank &amp; VESA_VSYNC_SUSPEND)&n;&t;&t;ctrl &amp;= ~3;&n;&t;if (blank &amp; VESA_HSYNC_SUSPEND)&n;&t;&t;ctrl &amp;= ~0x30;&n;&t;out_le32(&amp;info-&gt;platinum_regs-&gt;ctrl.r, ctrl);&n;*/
multiline_comment|/* TODO: Figure out how the heck to powerdown this thing! */
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|platinumfb_setcolreg
r_static
r_int
id|platinumfb_setcolreg
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
r_struct
id|fb_info_platinum
op_star
id|p
op_assign
(paren
r_struct
id|fb_info_platinum
op_star
)paren
id|info
suffix:semicolon
r_volatile
r_struct
id|cmap_regs
op_star
id|cmap_regs
op_assign
id|p-&gt;cmap_regs
suffix:semicolon
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
l_int|8
suffix:semicolon
id|green
op_rshift_assign
l_int|8
suffix:semicolon
id|blue
op_rshift_assign
l_int|8
suffix:semicolon
id|p-&gt;palette
(braket
id|regno
)braket
dot
id|red
op_assign
id|red
suffix:semicolon
id|p-&gt;palette
(braket
id|regno
)braket
dot
id|green
op_assign
id|green
suffix:semicolon
id|p-&gt;palette
(braket
id|regno
)braket
dot
id|blue
op_assign
id|blue
suffix:semicolon
id|out_8
c_func
(paren
op_amp
id|cmap_regs-&gt;addr
comma
id|regno
)paren
suffix:semicolon
multiline_comment|/* tell clut what addr to fill&t;*/
id|out_8
c_func
(paren
op_amp
id|cmap_regs-&gt;lut
comma
id|red
)paren
suffix:semicolon
multiline_comment|/* send one color channel at&t;*/
id|out_8
c_func
(paren
op_amp
id|cmap_regs-&gt;lut
comma
id|green
)paren
suffix:semicolon
multiline_comment|/* a time...&t;&t;&t;*/
id|out_8
c_func
(paren
op_amp
id|cmap_regs-&gt;lut
comma
id|blue
)paren
suffix:semicolon
r_if
c_cond
(paren
id|regno
OL
l_int|16
)paren
(brace
r_int
id|i
suffix:semicolon
id|u32
op_star
id|pal
op_assign
id|info-&gt;pseudo_palette
suffix:semicolon
r_switch
c_cond
(paren
id|p-&gt;par.cmode
)paren
(brace
r_case
id|CMODE_16
suffix:colon
id|pal
(braket
id|regno
)braket
op_assign
(paren
id|regno
op_lshift
l_int|10
)paren
op_or
(paren
id|regno
op_lshift
l_int|5
)paren
op_or
id|regno
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CMODE_32
suffix:colon
id|i
op_assign
(paren
id|regno
op_lshift
l_int|8
)paren
op_or
id|regno
suffix:semicolon
id|pal
(braket
id|regno
)braket
op_assign
(paren
id|i
op_lshift
l_int|16
)paren
op_or
id|i
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|platinum_vram_reqd
r_static
r_inline
r_int
id|platinum_vram_reqd
c_func
(paren
r_int
id|video_mode
comma
r_int
id|color_mode
)paren
(brace
r_return
id|vmode_attrs
(braket
id|video_mode
op_minus
l_int|1
)braket
dot
id|vres
op_star
(paren
id|vmode_attrs
(braket
id|video_mode
op_minus
l_int|1
)braket
dot
id|hres
op_star
(paren
l_int|1
op_lshift
id|color_mode
)paren
op_plus
l_int|0x20
)paren
op_plus
l_int|0x1000
suffix:semicolon
)brace
DECL|macro|STORE_D2
mdefine_line|#define STORE_D2(a, d) { &bslash;&n;&t;out_8(&amp;cmap_regs-&gt;addr, (a+32)); &bslash;&n;&t;out_8(&amp;cmap_regs-&gt;d2, (d)); &bslash;&n;}
DECL|function|set_platinum_clock
r_static
r_void
id|set_platinum_clock
c_func
(paren
r_struct
id|fb_info_platinum
op_star
id|info
)paren
(brace
r_volatile
r_struct
id|cmap_regs
op_star
id|cmap_regs
op_assign
id|info-&gt;cmap_regs
suffix:semicolon
r_struct
id|platinum_regvals
op_star
id|init
suffix:semicolon
id|init
op_assign
id|platinum_reg_init
(braket
id|info-&gt;par.vmode
op_minus
l_int|1
)braket
suffix:semicolon
id|STORE_D2
c_func
(paren
l_int|6
comma
l_int|0xc6
)paren
suffix:semicolon
id|out_8
c_func
(paren
op_amp
id|cmap_regs-&gt;addr
comma
l_int|3
op_plus
l_int|32
)paren
suffix:semicolon
r_if
c_cond
(paren
id|in_8
c_func
(paren
op_amp
id|cmap_regs-&gt;d2
)paren
op_eq
l_int|2
)paren
(brace
id|STORE_D2
c_func
(paren
l_int|7
comma
id|init-&gt;clock_params
(braket
id|info-&gt;clktype
)braket
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|STORE_D2
c_func
(paren
l_int|8
comma
id|init-&gt;clock_params
(braket
id|info-&gt;clktype
)braket
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|STORE_D2
c_func
(paren
l_int|3
comma
l_int|3
)paren
suffix:semicolon
)brace
r_else
(brace
id|STORE_D2
c_func
(paren
l_int|4
comma
id|init-&gt;clock_params
(braket
id|info-&gt;clktype
)braket
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|STORE_D2
c_func
(paren
l_int|5
comma
id|init-&gt;clock_params
(braket
id|info-&gt;clktype
)braket
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|STORE_D2
c_func
(paren
l_int|3
comma
l_int|2
)paren
suffix:semicolon
)brace
id|__delay
c_func
(paren
l_int|5000
)paren
suffix:semicolon
id|STORE_D2
c_func
(paren
l_int|9
comma
l_int|0xa6
)paren
suffix:semicolon
)brace
multiline_comment|/* Now how about actually saying, Make it so! */
multiline_comment|/* Some things in here probably don&squot;t need to be done each time. */
DECL|function|platinum_set_hardware
r_static
r_void
id|platinum_set_hardware
c_func
(paren
r_struct
id|fb_info_platinum
op_star
id|info
comma
r_const
r_struct
id|fb_par_platinum
op_star
id|par
)paren
(brace
r_volatile
r_struct
id|platinum_regs
op_star
id|platinum_regs
op_assign
id|info-&gt;platinum_regs
suffix:semicolon
r_volatile
r_struct
id|cmap_regs
op_star
id|cmap_regs
op_assign
id|info-&gt;cmap_regs
suffix:semicolon
r_struct
id|platinum_regvals
op_star
id|init
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
id|vmode
comma
id|cmode
suffix:semicolon
id|info-&gt;par
op_assign
op_star
id|par
suffix:semicolon
id|vmode
op_assign
id|par-&gt;vmode
suffix:semicolon
id|cmode
op_assign
id|par-&gt;cmode
suffix:semicolon
id|init
op_assign
id|platinum_reg_init
(braket
id|vmode
op_minus
l_int|1
)braket
suffix:semicolon
multiline_comment|/* Initialize display timing registers */
id|out_be32
c_func
(paren
op_amp
id|platinum_regs-&gt;reg
(braket
l_int|24
)braket
dot
id|r
comma
l_int|7
)paren
suffix:semicolon
multiline_comment|/* turn display off */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|26
suffix:semicolon
op_increment
id|i
)paren
id|out_be32
c_func
(paren
op_amp
id|platinum_regs-&gt;reg
(braket
id|i
op_plus
l_int|32
)braket
dot
id|r
comma
id|init-&gt;regs
(braket
id|i
)braket
)paren
suffix:semicolon
id|out_be32
c_func
(paren
op_amp
id|platinum_regs-&gt;reg
(braket
l_int|26
op_plus
l_int|32
)braket
dot
id|r
comma
(paren
id|info-&gt;total_vram
op_eq
l_int|0x100000
ques
c_cond
id|init-&gt;offset
(braket
id|cmode
)braket
op_plus
l_int|4
op_minus
id|cmode
suffix:colon
id|init-&gt;offset
(braket
id|cmode
)braket
)paren
)paren
suffix:semicolon
id|out_be32
c_func
(paren
op_amp
id|platinum_regs-&gt;reg
(braket
l_int|16
)braket
dot
id|r
comma
(paren
r_int
)paren
id|info-&gt;frame_buffer_phys
op_plus
id|init-&gt;fb_offset
op_plus
l_int|0x10
)paren
suffix:semicolon
id|out_be32
c_func
(paren
op_amp
id|platinum_regs-&gt;reg
(braket
l_int|18
)braket
dot
id|r
comma
id|init-&gt;pitch
(braket
id|cmode
)braket
)paren
suffix:semicolon
id|out_be32
c_func
(paren
op_amp
id|platinum_regs-&gt;reg
(braket
l_int|19
)braket
dot
id|r
comma
(paren
id|info-&gt;total_vram
op_eq
l_int|0x100000
ques
c_cond
id|init-&gt;mode
(braket
id|cmode
op_plus
l_int|1
)braket
suffix:colon
id|init-&gt;mode
(braket
id|cmode
)braket
)paren
)paren
suffix:semicolon
id|out_be32
c_func
(paren
op_amp
id|platinum_regs-&gt;reg
(braket
l_int|20
)braket
dot
id|r
comma
(paren
id|info-&gt;total_vram
op_eq
l_int|0x100000
ques
c_cond
l_int|0x11
suffix:colon
l_int|0x1011
)paren
)paren
suffix:semicolon
id|out_be32
c_func
(paren
op_amp
id|platinum_regs-&gt;reg
(braket
l_int|21
)braket
dot
id|r
comma
l_int|0x100
)paren
suffix:semicolon
id|out_be32
c_func
(paren
op_amp
id|platinum_regs-&gt;reg
(braket
l_int|22
)braket
dot
id|r
comma
l_int|1
)paren
suffix:semicolon
id|out_be32
c_func
(paren
op_amp
id|platinum_regs-&gt;reg
(braket
l_int|23
)braket
dot
id|r
comma
l_int|1
)paren
suffix:semicolon
id|out_be32
c_func
(paren
op_amp
id|platinum_regs-&gt;reg
(braket
l_int|26
)braket
dot
id|r
comma
l_int|0xc00
)paren
suffix:semicolon
id|out_be32
c_func
(paren
op_amp
id|platinum_regs-&gt;reg
(braket
l_int|27
)braket
dot
id|r
comma
l_int|0x235
)paren
suffix:semicolon
multiline_comment|/* out_be32(&amp;platinum_regs-&gt;reg[27].r, 0x2aa); */
id|STORE_D2
c_func
(paren
l_int|0
comma
(paren
id|info-&gt;total_vram
op_eq
l_int|0x100000
ques
c_cond
id|init-&gt;dacula_ctrl
(braket
id|cmode
)braket
op_amp
l_int|0xf
suffix:colon
id|init-&gt;dacula_ctrl
(braket
id|cmode
)braket
)paren
)paren
suffix:semicolon
id|STORE_D2
c_func
(paren
l_int|1
comma
l_int|4
)paren
suffix:semicolon
id|STORE_D2
c_func
(paren
l_int|2
comma
l_int|0
)paren
suffix:semicolon
id|set_platinum_clock
c_func
(paren
id|info
)paren
suffix:semicolon
id|out_be32
c_func
(paren
op_amp
id|platinum_regs-&gt;reg
(braket
l_int|24
)braket
dot
id|r
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* turn display on */
)brace
multiline_comment|/*&n; * Set misc info vars for this driver&n; */
DECL|function|platinum_init_info
r_static
r_void
id|__init
id|platinum_init_info
c_func
(paren
r_struct
id|fb_info
op_star
id|info
comma
r_struct
id|fb_info_platinum
op_star
id|p
)paren
(brace
multiline_comment|/* Fill fb_info */
id|info-&gt;par
op_assign
op_amp
id|p-&gt;par
suffix:semicolon
id|info-&gt;node
op_assign
id|NODEV
suffix:semicolon
id|info-&gt;fbops
op_assign
op_amp
id|platinumfb_ops
suffix:semicolon
id|info-&gt;pseudo_palette
op_assign
id|p-&gt;pseudo_palette
suffix:semicolon
id|info-&gt;flags
op_assign
id|FBINFO_FLAG_DEFAULT
suffix:semicolon
id|info-&gt;screen_base
op_assign
(paren
r_char
op_star
)paren
id|p-&gt;frame_buffer
op_plus
l_int|0x20
suffix:semicolon
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
suffix:semicolon
multiline_comment|/* Fill fix common fields */
id|strcpy
c_func
(paren
id|info-&gt;fix.id
comma
l_string|&quot;platinum&quot;
)paren
suffix:semicolon
id|info-&gt;fix.mmio_start
op_assign
id|p-&gt;platinum_regs_phys
suffix:semicolon
id|info-&gt;fix.mmio_len
op_assign
l_int|0x1000
suffix:semicolon
id|info-&gt;fix.type
op_assign
id|FB_TYPE_PACKED_PIXELS
suffix:semicolon
id|info-&gt;fix.smem_start
op_assign
id|p-&gt;frame_buffer_phys
op_plus
l_int|0x20
suffix:semicolon
multiline_comment|/* will be updated later */
id|info-&gt;fix.smem_len
op_assign
id|p-&gt;total_vram
op_minus
l_int|0x20
suffix:semicolon
id|info-&gt;fix.ywrapstep
op_assign
l_int|0
suffix:semicolon
id|info-&gt;fix.xpanstep
op_assign
l_int|0
suffix:semicolon
id|info-&gt;fix.ypanstep
op_assign
l_int|0
suffix:semicolon
id|info-&gt;fix.type_aux
op_assign
l_int|0
suffix:semicolon
id|info-&gt;fix.accel
op_assign
id|FB_ACCEL_NONE
suffix:semicolon
)brace
DECL|function|init_platinum
r_static
r_int
id|__init
id|init_platinum
c_func
(paren
r_struct
id|fb_info_platinum
op_star
id|p
)paren
(brace
r_struct
id|fb_var_screeninfo
id|var
suffix:semicolon
r_int
id|sense
comma
id|rc
suffix:semicolon
id|sense
op_assign
id|read_platinum_sense
c_func
(paren
id|p
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Monitor sense value = 0x%x, &quot;
comma
id|sense
)paren
suffix:semicolon
r_if
c_cond
(paren
id|default_vmode
op_eq
id|VMODE_NVRAM
)paren
(brace
id|default_vmode
op_assign
id|nvram_read_byte
c_func
(paren
id|NV_VMODE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|default_vmode
op_le
l_int|0
op_logical_or
id|default_vmode
OG
id|VMODE_MAX
op_logical_or
op_logical_neg
id|platinum_reg_init
(braket
id|default_vmode
op_minus
l_int|1
)braket
)paren
id|default_vmode
op_assign
id|VMODE_CHOOSE
suffix:semicolon
)brace
r_if
c_cond
(paren
id|default_vmode
op_eq
id|VMODE_CHOOSE
)paren
(brace
id|default_vmode
op_assign
id|mac_map_monitor_sense
c_func
(paren
id|sense
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|default_vmode
op_le
l_int|0
op_logical_or
id|default_vmode
OG
id|VMODE_MAX
)paren
id|default_vmode
op_assign
id|VMODE_640_480_60
suffix:semicolon
r_if
c_cond
(paren
id|default_cmode
op_eq
id|CMODE_NVRAM
)paren
id|default_cmode
op_assign
id|nvram_read_byte
c_func
(paren
id|NV_CMODE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|default_cmode
template_param
id|CMODE_32
)paren
id|default_cmode
op_assign
id|CMODE_8
suffix:semicolon
multiline_comment|/*&n;&t; * Reduce the pixel size if we don&squot;t have enough VRAM.&n;&t; */
r_while
c_loop
(paren
id|default_cmode
OG
id|CMODE_8
op_logical_and
id|platinum_vram_reqd
c_func
(paren
id|default_vmode
comma
id|default_cmode
)paren
OG
id|p-&gt;total_vram
)paren
(brace
id|default_cmode
op_decrement
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;using video mode %d and color mode %d.&bslash;n&quot;
comma
id|default_vmode
comma
id|default_cmode
)paren
suffix:semicolon
multiline_comment|/* Setup default var */
r_if
c_cond
(paren
id|mac_vmode_to_var
c_func
(paren
id|default_vmode
comma
id|default_cmode
comma
op_amp
id|var
)paren
OL
l_int|0
)paren
(brace
multiline_comment|/* This shouldn&squot;t happen! */
id|printk
c_func
(paren
l_string|&quot;mac_vmode_to_var(%d, %d,) failed&bslash;n&quot;
comma
id|default_vmode
comma
id|default_cmode
)paren
suffix:semicolon
id|try_again
suffix:colon
id|default_vmode
op_assign
id|VMODE_640_480_60
suffix:semicolon
id|default_cmode
op_assign
id|CMODE_8
suffix:semicolon
r_if
c_cond
(paren
id|mac_vmode_to_var
c_func
(paren
id|default_vmode
comma
id|default_cmode
comma
op_amp
id|var
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;platinumfb: mac_vmode_to_var() failed&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
)brace
multiline_comment|/* Initialize info structure */
id|platinum_init_info
c_func
(paren
op_amp
id|p-&gt;info
comma
id|p
)paren
suffix:semicolon
multiline_comment|/* Apply default var */
id|p-&gt;info.var
op_assign
id|var
suffix:semicolon
id|var.activate
op_assign
id|FB_ACTIVATE_NOW
suffix:semicolon
id|rc
op_assign
id|fb_set_var
c_func
(paren
op_amp
id|var
comma
op_amp
id|p-&gt;info
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_logical_and
(paren
id|default_vmode
op_ne
id|VMODE_640_480_60
op_logical_or
id|default_cmode
op_ne
id|CMODE_8
)paren
)paren
r_goto
id|try_again
suffix:semicolon
multiline_comment|/* Register with fbdev layer */
r_if
c_cond
(paren
id|register_framebuffer
c_func
(paren
op_amp
id|p-&gt;info
)paren
OL
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;fb%d: platinum frame buffer device&bslash;n&quot;
comma
id|minor
c_func
(paren
id|p-&gt;info.node
)paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|platinum_init
r_int
id|__init
id|platinum_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|device_node
op_star
id|dp
suffix:semicolon
id|dp
op_assign
id|find_devices
c_func
(paren
l_string|&quot;platinum&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dp
op_ne
l_int|0
)paren
id|platinum_of_init
c_func
(paren
id|dp
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef __powerpc__
DECL|macro|invalidate_cache
mdefine_line|#define invalidate_cache(addr) &bslash;&n;&t;asm volatile(&quot;eieio; dcbf 0,%1&quot; &bslash;&n;&t;: &quot;=m&quot; (*(addr)) : &quot;r&quot; (addr) : &quot;memory&quot;);
macro_line|#else
DECL|macro|invalidate_cache
mdefine_line|#define invalidate_cache(addr)
macro_line|#endif
DECL|function|platinum_of_init
r_static
r_void
id|__init
id|platinum_of_init
c_func
(paren
r_struct
id|device_node
op_star
id|dp
)paren
(brace
r_struct
id|fb_info_platinum
op_star
id|info
suffix:semicolon
r_int
r_int
id|addr
comma
id|size
suffix:semicolon
r_volatile
id|__u8
op_star
id|fbuffer
suffix:semicolon
r_int
id|i
comma
id|bank0
comma
id|bank1
comma
id|bank2
comma
id|bank3
suffix:semicolon
r_if
c_cond
(paren
id|dp-&gt;n_addrs
op_ne
l_int|2
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;expecting 2 address for platinum (got %d)&quot;
comma
id|dp-&gt;n_addrs
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|info
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|info
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|info
op_eq
l_int|0
)paren
r_return
suffix:semicolon
id|memset
c_func
(paren
id|info
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|info
)paren
)paren
suffix:semicolon
multiline_comment|/* Map in frame buffer and registers */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|dp-&gt;n_addrs
suffix:semicolon
op_increment
id|i
)paren
(brace
id|addr
op_assign
id|dp-&gt;addrs
(braket
id|i
)braket
dot
id|address
suffix:semicolon
id|size
op_assign
id|dp-&gt;addrs
(braket
id|i
)braket
dot
id|size
suffix:semicolon
multiline_comment|/* Let&squot;s assume we can request either all or nothing */
r_if
c_cond
(paren
op_logical_neg
id|request_mem_region
c_func
(paren
id|addr
comma
id|size
comma
l_string|&quot;platinumfb&quot;
)paren
)paren
(brace
id|kfree
c_func
(paren
id|info
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|size
op_ge
l_int|0x400000
)paren
(brace
multiline_comment|/* frame buffer - map only 4MB */
id|info-&gt;frame_buffer_phys
op_assign
id|addr
suffix:semicolon
id|info-&gt;frame_buffer
op_assign
id|__ioremap
c_func
(paren
id|addr
comma
l_int|0x400000
comma
id|_PAGE_WRITETHRU
)paren
suffix:semicolon
id|info-&gt;base_frame_buffer
op_assign
id|info-&gt;frame_buffer
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* registers */
id|info-&gt;platinum_regs_phys
op_assign
id|addr
suffix:semicolon
id|info-&gt;platinum_regs
op_assign
id|ioremap
c_func
(paren
id|addr
comma
id|size
)paren
suffix:semicolon
)brace
)brace
id|info-&gt;cmap_regs_phys
op_assign
l_int|0xf301b000
suffix:semicolon
multiline_comment|/* XXX not in prom? */
id|request_mem_region
c_func
(paren
id|info-&gt;cmap_regs_phys
comma
l_int|0x1000
comma
l_string|&quot;platinumfb cmap&quot;
)paren
suffix:semicolon
id|info-&gt;cmap_regs
op_assign
id|ioremap
c_func
(paren
id|info-&gt;cmap_regs_phys
comma
l_int|0x1000
)paren
suffix:semicolon
multiline_comment|/* Grok total video ram */
id|out_be32
c_func
(paren
op_amp
id|info-&gt;platinum_regs-&gt;reg
(braket
l_int|16
)braket
dot
id|r
comma
(paren
r_int
)paren
id|info-&gt;frame_buffer_phys
)paren
suffix:semicolon
id|out_be32
c_func
(paren
op_amp
id|info-&gt;platinum_regs-&gt;reg
(braket
l_int|20
)braket
dot
id|r
comma
l_int|0x1011
)paren
suffix:semicolon
multiline_comment|/* select max vram */
id|out_be32
c_func
(paren
op_amp
id|info-&gt;platinum_regs-&gt;reg
(braket
l_int|24
)braket
dot
id|r
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* switch in vram */
id|fbuffer
op_assign
id|info-&gt;base_frame_buffer
suffix:semicolon
id|fbuffer
(braket
l_int|0x100000
)braket
op_assign
l_int|0x34
suffix:semicolon
id|fbuffer
(braket
l_int|0x100008
)braket
op_assign
l_int|0x0
suffix:semicolon
id|invalidate_cache
c_func
(paren
op_amp
id|fbuffer
(braket
l_int|0x100000
)braket
)paren
suffix:semicolon
id|fbuffer
(braket
l_int|0x200000
)braket
op_assign
l_int|0x56
suffix:semicolon
id|fbuffer
(braket
l_int|0x200008
)braket
op_assign
l_int|0x0
suffix:semicolon
id|invalidate_cache
c_func
(paren
op_amp
id|fbuffer
(braket
l_int|0x200000
)braket
)paren
suffix:semicolon
id|fbuffer
(braket
l_int|0x300000
)braket
op_assign
l_int|0x78
suffix:semicolon
id|fbuffer
(braket
l_int|0x300008
)braket
op_assign
l_int|0x0
suffix:semicolon
id|invalidate_cache
c_func
(paren
op_amp
id|fbuffer
(braket
l_int|0x300000
)braket
)paren
suffix:semicolon
id|bank0
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* builtin 1MB vram, always there */
id|bank1
op_assign
id|fbuffer
(braket
l_int|0x100000
)braket
op_eq
l_int|0x34
suffix:semicolon
id|bank2
op_assign
id|fbuffer
(braket
l_int|0x200000
)braket
op_eq
l_int|0x56
suffix:semicolon
id|bank3
op_assign
id|fbuffer
(braket
l_int|0x300000
)braket
op_eq
l_int|0x78
suffix:semicolon
id|info-&gt;total_vram
op_assign
(paren
id|bank0
op_plus
id|bank1
op_plus
id|bank2
op_plus
id|bank3
)paren
op_star
l_int|0x100000
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Total VRAM = %dMB %d%d%d%d&bslash;n&quot;
comma
(paren
r_int
)paren
(paren
id|info-&gt;total_vram
op_div
l_int|1024
op_div
l_int|1024
)paren
comma
id|bank3
comma
id|bank2
comma
id|bank1
comma
id|bank0
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Try to determine whether we have an old or a new DACula.&n;&t; */
id|out_8
c_func
(paren
op_amp
id|info-&gt;cmap_regs-&gt;addr
comma
l_int|0x40
)paren
suffix:semicolon
id|info-&gt;dactype
op_assign
id|in_8
c_func
(paren
op_amp
id|info-&gt;cmap_regs-&gt;d2
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|info-&gt;dactype
)paren
(brace
r_case
l_int|0x3c
suffix:colon
id|info-&gt;clktype
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x84
suffix:colon
id|info-&gt;clktype
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|info-&gt;clktype
op_assign
l_int|0
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Unknown DACula type: %x&bslash;n&quot;
comma
id|info-&gt;dactype
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|init_platinum
c_func
(paren
id|info
)paren
)paren
(brace
id|kfree
c_func
(paren
id|info
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Get the monitor sense value.&n; * Note that this can be called before calibrate_delay,&n; * so we can&squot;t use udelay.&n; */
DECL|function|read_platinum_sense
r_static
r_int
id|read_platinum_sense
c_func
(paren
r_struct
id|fb_info_platinum
op_star
id|info
)paren
(brace
r_volatile
r_struct
id|platinum_regs
op_star
id|platinum_regs
op_assign
id|info-&gt;platinum_regs
suffix:semicolon
r_int
id|sense
suffix:semicolon
id|out_be32
c_func
(paren
op_amp
id|platinum_regs-&gt;reg
(braket
l_int|23
)braket
dot
id|r
comma
l_int|7
)paren
suffix:semicolon
multiline_comment|/* turn off drivers */
id|__delay
c_func
(paren
l_int|2000
)paren
suffix:semicolon
id|sense
op_assign
(paren
op_complement
id|in_be32
c_func
(paren
op_amp
id|platinum_regs-&gt;reg
(braket
l_int|23
)braket
dot
id|r
)paren
op_amp
l_int|7
)paren
op_lshift
l_int|8
suffix:semicolon
multiline_comment|/* drive each sense line low in turn and collect the other 2 */
id|out_be32
c_func
(paren
op_amp
id|platinum_regs-&gt;reg
(braket
l_int|23
)braket
dot
id|r
comma
l_int|3
)paren
suffix:semicolon
multiline_comment|/* drive A low */
id|__delay
c_func
(paren
l_int|2000
)paren
suffix:semicolon
id|sense
op_or_assign
(paren
op_complement
id|in_be32
c_func
(paren
op_amp
id|platinum_regs-&gt;reg
(braket
l_int|23
)braket
dot
id|r
)paren
op_amp
l_int|3
)paren
op_lshift
l_int|4
suffix:semicolon
id|out_be32
c_func
(paren
op_amp
id|platinum_regs-&gt;reg
(braket
l_int|23
)braket
dot
id|r
comma
l_int|5
)paren
suffix:semicolon
multiline_comment|/* drive B low */
id|__delay
c_func
(paren
l_int|2000
)paren
suffix:semicolon
id|sense
op_or_assign
(paren
op_complement
id|in_be32
c_func
(paren
op_amp
id|platinum_regs-&gt;reg
(braket
l_int|23
)braket
dot
id|r
)paren
op_amp
l_int|4
)paren
op_lshift
l_int|1
suffix:semicolon
id|sense
op_or_assign
(paren
op_complement
id|in_be32
c_func
(paren
op_amp
id|platinum_regs-&gt;reg
(braket
l_int|23
)braket
dot
id|r
)paren
op_amp
l_int|1
)paren
op_lshift
l_int|2
suffix:semicolon
id|out_be32
c_func
(paren
op_amp
id|platinum_regs-&gt;reg
(braket
l_int|23
)braket
dot
id|r
comma
l_int|6
)paren
suffix:semicolon
multiline_comment|/* drive C low */
id|__delay
c_func
(paren
l_int|2000
)paren
suffix:semicolon
id|sense
op_or_assign
(paren
op_complement
id|in_be32
c_func
(paren
op_amp
id|platinum_regs-&gt;reg
(braket
l_int|23
)braket
dot
id|r
)paren
op_amp
l_int|6
)paren
op_rshift
l_int|1
suffix:semicolon
id|out_be32
c_func
(paren
op_amp
id|platinum_regs-&gt;reg
(braket
l_int|23
)braket
dot
id|r
comma
l_int|7
)paren
suffix:semicolon
multiline_comment|/* turn off drivers */
r_return
id|sense
suffix:semicolon
)brace
multiline_comment|/* This routine takes a user-supplied var, and picks the best vmode/cmode from it. */
DECL|function|platinum_var_to_par
r_static
r_int
id|platinum_var_to_par
c_func
(paren
r_const
r_struct
id|fb_var_screeninfo
op_star
id|var
comma
r_struct
id|fb_par_platinum
op_star
id|par
comma
r_const
r_struct
id|fb_info_platinum
op_star
id|info
)paren
(brace
r_if
c_cond
(paren
id|mac_var_to_vmode
c_func
(paren
id|var
comma
op_amp
id|par-&gt;vmode
comma
op_amp
id|par-&gt;cmode
)paren
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;platinum_var_to_par: mac_var_to_vmode unsuccessful.&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;platinum_var_to_par: var-&gt;xres = %d&bslash;n&quot;
comma
id|var-&gt;xres
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;platinum_var_to_par: var-&gt;yres = %d&bslash;n&quot;
comma
id|var-&gt;yres
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;platinum_var_to_par: var-&gt;xres_virtual = %d&bslash;n&quot;
comma
id|var-&gt;xres_virtual
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;platinum_var_to_par: var-&gt;yres_virtual = %d&bslash;n&quot;
comma
id|var-&gt;yres_virtual
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;platinum_var_to_par: var-&gt;bits_per_pixel = %d&bslash;n&quot;
comma
id|var-&gt;bits_per_pixel
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;platinum_var_to_par: var-&gt;pixclock = %d&bslash;n&quot;
comma
id|var-&gt;pixclock
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;platinum_var_to_par: var-&gt;vmode = %d&bslash;n&quot;
comma
id|var-&gt;vmode
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|platinum_reg_init
(braket
id|par-&gt;vmode
op_minus
l_int|1
)braket
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;platinum_var_to_par, vmode %d not valid.&bslash;n&quot;
comma
id|par-&gt;vmode
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|platinum_vram_reqd
c_func
(paren
id|par-&gt;vmode
comma
id|par-&gt;cmode
)paren
OG
id|info-&gt;total_vram
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;platinum_var_to_par, not enough ram for vmode %d, cmode %d.&bslash;n&quot;
comma
id|par-&gt;vmode
comma
id|par-&gt;cmode
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|par-&gt;xres
op_assign
id|vmode_attrs
(braket
id|par-&gt;vmode
op_minus
l_int|1
)braket
dot
id|hres
suffix:semicolon
id|par-&gt;yres
op_assign
id|vmode_attrs
(braket
id|par-&gt;vmode
op_minus
l_int|1
)braket
dot
id|vres
suffix:semicolon
id|par-&gt;xoffset
op_assign
l_int|0
suffix:semicolon
id|par-&gt;yoffset
op_assign
l_int|0
suffix:semicolon
id|par-&gt;vxres
op_assign
id|par-&gt;xres
suffix:semicolon
id|par-&gt;vyres
op_assign
id|par-&gt;yres
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|platinum_par_to_var
r_static
r_int
id|platinum_par_to_var
c_func
(paren
r_struct
id|fb_var_screeninfo
op_star
id|var
comma
r_const
r_struct
id|fb_par_platinum
op_star
id|par
comma
r_const
r_struct
id|fb_info_platinum
op_star
id|info
)paren
(brace
r_return
id|mac_vmode_to_var
c_func
(paren
id|par-&gt;vmode
comma
id|par-&gt;cmode
comma
id|var
)paren
suffix:semicolon
)brace
multiline_comment|/* &n; * Parse user speficied options (`video=platinumfb:&squot;)&n; */
DECL|function|platinum_setup
r_int
id|__init
id|platinum_setup
c_func
(paren
r_char
op_star
id|options
)paren
(brace
r_char
op_star
id|this_opt
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|options
op_logical_or
op_logical_neg
op_star
id|options
)paren
r_return
l_int|0
suffix:semicolon
r_while
c_loop
(paren
(paren
id|this_opt
op_assign
id|strsep
c_func
(paren
op_amp
id|options
comma
l_string|&quot;,&quot;
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|this_opt
comma
l_string|&quot;vmode:&quot;
comma
l_int|6
)paren
)paren
(brace
r_int
id|vmode
op_assign
id|simple_strtoul
c_func
(paren
id|this_opt
op_plus
l_int|6
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vmode
OG
l_int|0
op_logical_and
id|vmode
op_le
id|VMODE_MAX
)paren
id|default_vmode
op_assign
id|vmode
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|this_opt
comma
l_string|&quot;cmode:&quot;
comma
l_int|6
)paren
)paren
(brace
r_int
id|depth
op_assign
id|simple_strtoul
c_func
(paren
id|this_opt
op_plus
l_int|6
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|depth
)paren
(brace
r_case
l_int|0
suffix:colon
r_case
l_int|8
suffix:colon
id|default_cmode
op_assign
id|CMODE_8
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|15
suffix:colon
r_case
l_int|16
suffix:colon
id|default_cmode
op_assign
id|CMODE_16
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|24
suffix:colon
r_case
l_int|32
suffix:colon
id|default_cmode
op_assign
id|CMODE_32
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
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
