multiline_comment|/*&n; *  valkyriefb.c -- frame buffer device for the PowerMac &squot;valkyrie&squot; display&n; *&n; *  Created 8 August 1998 by &n; *  Martin Costabel &lt;costabel@wanadoo.fr&gt; and Kevin Schoedel&n; *&n; *  Vmode-switching changes and vmode 15/17 modifications created 29 August&n; *  1998 by Barry K. Nathan &lt;barryn@pobox.com&gt;.&n; *&n; *  Ported to m68k Macintosh by David Huggins-Daines &lt;dhd@debian.org&gt;&n; *&n; *  Derived directly from:&n; *&n; *   controlfb.c -- frame buffer device for the PowerMac &squot;control&squot; display&n; *   Copyright (C) 1998 Dan Jacobowitz &lt;dan@debian.org&gt;&n; *&n; *   pmc-valkyrie.c -- Console support for PowerMac &quot;valkyrie&quot; display adaptor.&n; *   Copyright (C) 1997 Paul Mackerras.&n; *&n; *  and indirectly:&n; *&n; *  Frame buffer structure from:&n; *    drivers/video/chipsfb.c -- frame buffer device for&n; *    Chips &amp; Technologies 65550 chip.&n; *&n; *    Copyright (C) 1998 Paul Mackerras&n; *&n; *    This file is derived from the Powermac &quot;chips&quot; driver:&n; *    Copyright (C) 1997 Fabio Riccardi.&n; *    And from the frame buffer device for Open Firmware-initialized devices:&n; *    Copyright (C) 1997 Geert Uytterhoeven.&n; *&n; *  Hardware information from:&n; *    control.c: Console support for PowerMac &quot;control&quot; display adaptor.&n; *    Copyright (C) 1996 Paul Mackerras&n; *&n; *  This file is subject to the terms and conditions of the GNU General Public&n; *  License. See the file COPYING in the main directory of this archive for&n; *  more details.&n; */
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
macro_line|#include &lt;linux/selection.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/nvram.h&gt;
macro_line|#include &lt;linux/adb.h&gt;
macro_line|#include &lt;linux/cuda.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#ifdef CONFIG_MAC
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/macintosh.h&gt;
macro_line|#else
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#endif
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &quot;macmodes.h&quot;
macro_line|#include &quot;valkyriefb.h&quot;
macro_line|#ifdef CONFIG_MAC
multiline_comment|/* We don&squot;t yet have functions to read the PRAM... perhaps we can&n;   adapt them from the PPC code? */
DECL|variable|default_vmode
r_static
r_int
id|default_vmode
op_assign
id|VMODE_640_480_67
suffix:semicolon
DECL|variable|default_cmode
r_static
r_int
id|default_cmode
op_assign
id|CMODE_8
suffix:semicolon
macro_line|#else
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
macro_line|#endif
DECL|struct|fb_par_valkyrie
r_struct
id|fb_par_valkyrie
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
DECL|member|init
r_struct
id|valkyrie_regvals
op_star
id|init
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|fb_info_valkyrie
r_struct
id|fb_info_valkyrie
(brace
DECL|member|info
r_struct
id|fb_info
id|info
suffix:semicolon
DECL|member|par
r_struct
id|fb_par_valkyrie
id|par
suffix:semicolon
DECL|member|cmap_regs
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
DECL|member|valkyrie_regs
r_struct
id|valkyrie_regs
op_star
id|valkyrie_regs
suffix:semicolon
DECL|member|valkyrie_regs_phys
r_int
r_int
id|valkyrie_regs_phys
suffix:semicolon
DECL|member|frame_buffer
id|__u8
op_star
id|frame_buffer
suffix:semicolon
DECL|member|frame_buffer_phys
r_int
r_int
id|frame_buffer_phys
suffix:semicolon
DECL|member|sense
r_int
id|sense
suffix:semicolon
DECL|member|total_vram
r_int
r_int
id|total_vram
suffix:semicolon
DECL|member|pseudo_palette
id|u32
id|pseudo_palette
(braket
l_int|16
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Exported functions&n; */
r_int
id|valkyriefb_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|valkyriefb_setup
c_func
(paren
r_char
op_star
)paren
suffix:semicolon
r_static
r_int
id|valkyriefb_check_var
c_func
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
r_static
r_int
id|valkyriefb_set_par
c_func
(paren
r_struct
id|fb_info
op_star
id|info
)paren
suffix:semicolon
r_static
r_int
id|valkyriefb_setcolreg
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
id|valkyriefb_blank
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
id|read_valkyrie_sense
c_func
(paren
r_struct
id|fb_info_valkyrie
op_star
id|p
)paren
suffix:semicolon
r_static
r_void
id|set_valkyrie_clock
c_func
(paren
r_int
r_char
op_star
id|params
)paren
suffix:semicolon
r_static
r_int
id|valkyrie_var_to_par
c_func
(paren
r_struct
id|fb_var_screeninfo
op_star
id|var
comma
r_struct
id|fb_par_valkyrie
op_star
id|par
comma
r_const
r_struct
id|fb_info
op_star
id|fb_info
)paren
suffix:semicolon
r_static
r_void
id|valkyrie_init_info
c_func
(paren
r_struct
id|fb_info
op_star
id|info
comma
r_struct
id|fb_info_valkyrie
op_star
id|p
)paren
suffix:semicolon
r_static
r_void
id|valkyrie_par_to_fix
c_func
(paren
r_struct
id|fb_par_valkyrie
op_star
id|par
comma
r_struct
id|fb_fix_screeninfo
op_star
id|fix
)paren
suffix:semicolon
r_static
r_void
id|valkyrie_init_fix
c_func
(paren
r_struct
id|fb_fix_screeninfo
op_star
id|fix
comma
r_struct
id|fb_info_valkyrie
op_star
id|p
)paren
suffix:semicolon
DECL|variable|valkyriefb_ops
r_static
r_struct
id|fb_ops
id|valkyriefb_ops
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
id|valkyriefb_check_var
comma
dot
id|fb_set_par
op_assign
id|valkyriefb_set_par
comma
dot
id|fb_setcolreg
op_assign
id|valkyriefb_setcolreg
comma
dot
id|fb_blank
op_assign
id|valkyriefb_blank
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
multiline_comment|/* Sets the video mode according to info-&gt;var */
DECL|function|valkyriefb_set_par
r_static
r_int
id|valkyriefb_set_par
c_func
(paren
r_struct
id|fb_info
op_star
id|info
)paren
(brace
r_struct
id|fb_info_valkyrie
op_star
id|p
op_assign
(paren
r_struct
id|fb_info_valkyrie
op_star
)paren
id|info
suffix:semicolon
r_volatile
r_struct
id|valkyrie_regs
op_star
id|valkyrie_regs
op_assign
id|p-&gt;valkyrie_regs
suffix:semicolon
r_struct
id|fb_par_valkyrie
op_star
id|par
op_assign
id|info-&gt;par
suffix:semicolon
r_struct
id|valkyrie_regvals
op_star
id|init
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
id|valkyrie_var_to_par
c_func
(paren
op_amp
id|info-&gt;var
comma
id|par
comma
id|info
)paren
)paren
)paren
r_return
id|err
suffix:semicolon
id|valkyrie_par_to_fix
c_func
(paren
id|par
comma
op_amp
id|info-&gt;fix
)paren
suffix:semicolon
multiline_comment|/* Reset the valkyrie */
id|out_8
c_func
(paren
op_amp
id|valkyrie_regs-&gt;status.r
comma
l_int|0
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|100
)paren
suffix:semicolon
multiline_comment|/* Initialize display timing registers */
id|init
op_assign
id|par-&gt;init
suffix:semicolon
id|out_8
c_func
(paren
op_amp
id|valkyrie_regs-&gt;mode.r
comma
id|init-&gt;mode
op_or
l_int|0x80
)paren
suffix:semicolon
id|out_8
c_func
(paren
op_amp
id|valkyrie_regs-&gt;depth.r
comma
id|par-&gt;cmode
op_plus
l_int|3
)paren
suffix:semicolon
id|set_valkyrie_clock
c_func
(paren
id|init-&gt;clock_params
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|100
)paren
suffix:semicolon
multiline_comment|/* Turn on display */
id|out_8
c_func
(paren
op_amp
id|valkyrie_regs-&gt;mode.r
comma
id|init-&gt;mode
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|valkyrie_par_to_var
r_static
r_inline
r_int
id|valkyrie_par_to_var
c_func
(paren
r_struct
id|fb_par_valkyrie
op_star
id|par
comma
r_struct
id|fb_var_screeninfo
op_star
id|var
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
r_static
r_int
DECL|function|valkyriefb_check_var
id|valkyriefb_check_var
c_func
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
r_int
id|err
suffix:semicolon
r_struct
id|fb_par_valkyrie
id|par
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|valkyrie_var_to_par
c_func
(paren
id|var
comma
op_amp
id|par
comma
id|info
)paren
)paren
)paren
r_return
id|err
suffix:semicolon
id|valkyrie_par_to_var
c_func
(paren
op_amp
id|par
comma
id|var
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *  Blank the screen if blank_mode != 0, else unblank. If blank_mode == NULL&n; *  then the caller blanks by setting the CLUT (Color Look Up Table) to all&n; *  black. Return 0 if blanking succeeded, != 0 if un-/blanking failed due&n; *  to e.g. a video mode which doesn&squot;t support it. Implements VESA suspend&n; *  and powerdown modes on hardware that supports disabling hsync/vsync:&n; *    blank_mode == 2: suspend vsync&n; *    blank_mode == 3: suspend hsync&n; *    blank_mode == 4: powerdown&n; */
DECL|function|valkyriefb_blank
r_static
r_int
id|valkyriefb_blank
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
(brace
r_struct
id|fb_info_valkyrie
op_star
id|p
op_assign
(paren
r_struct
id|fb_info_valkyrie
op_star
)paren
id|info
suffix:semicolon
r_struct
id|fb_par_valkyrie
op_star
id|par
op_assign
id|info-&gt;par
suffix:semicolon
r_struct
id|valkyrie_regvals
op_star
id|init
op_assign
id|par-&gt;init
suffix:semicolon
r_if
c_cond
(paren
id|init
op_eq
l_int|NULL
)paren
r_return
l_int|1
suffix:semicolon
r_switch
c_cond
(paren
id|blank_mode
)paren
(brace
r_case
l_int|0
suffix:colon
multiline_comment|/* unblank */
id|out_8
c_func
(paren
op_amp
id|p-&gt;valkyrie_regs-&gt;mode.r
comma
id|init-&gt;mode
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
r_return
l_int|1
suffix:semicolon
multiline_comment|/* get caller to set CLUT to all black */
r_case
id|VESA_VSYNC_SUSPEND
op_plus
l_int|1
suffix:colon
r_case
id|VESA_HSYNC_SUSPEND
op_plus
l_int|1
suffix:colon
multiline_comment|/*&n;&t;&t; * [kps] Value extracted from MacOS. I don&squot;t know&n;&t;&t; * whether this bit disables hsync or vsync, or&n;&t;&t; * whether the hardware can do the other as well.&n;&t;&t; */
id|out_8
c_func
(paren
op_amp
id|p-&gt;valkyrie_regs-&gt;mode.r
comma
id|init-&gt;mode
op_or
l_int|0x40
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|VESA_POWERDOWN
op_plus
l_int|1
suffix:colon
id|out_8
c_func
(paren
op_amp
id|p-&gt;valkyrie_regs-&gt;mode.r
comma
l_int|0x66
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|valkyriefb_setcolreg
r_static
r_int
id|valkyriefb_setcolreg
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
id|fb_info_valkyrie
op_star
id|p
op_assign
(paren
r_struct
id|fb_info_valkyrie
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
r_struct
id|fb_par_valkyrie
op_star
id|par
op_assign
id|info-&gt;par
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
multiline_comment|/* tell clut which address to fill */
id|out_8
c_func
(paren
op_amp
id|p-&gt;cmap_regs-&gt;addr
comma
id|regno
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
multiline_comment|/* send one color channel at a time */
id|out_8
c_func
(paren
op_amp
id|cmap_regs-&gt;lut
comma
id|red
)paren
suffix:semicolon
id|out_8
c_func
(paren
op_amp
id|cmap_regs-&gt;lut
comma
id|green
)paren
suffix:semicolon
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
op_logical_and
id|par-&gt;cmode
op_eq
id|CMODE_16
)paren
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
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|valkyrie_vram_reqd
r_static
r_inline
r_int
id|valkyrie_vram_reqd
c_func
(paren
r_int
id|video_mode
comma
r_int
id|color_mode
)paren
(brace
r_int
id|pitch
suffix:semicolon
r_struct
id|valkyrie_regvals
op_star
id|init
op_assign
id|valkyrie_reg_init
(braket
id|video_mode
op_minus
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
(paren
id|pitch
op_assign
id|init-&gt;pitch
(braket
id|color_mode
)braket
)paren
op_eq
l_int|0
)paren
id|pitch
op_assign
l_int|2
op_star
id|init-&gt;pitch
(braket
l_int|0
)braket
suffix:semicolon
r_return
id|init-&gt;vres
op_star
id|pitch
suffix:semicolon
)brace
DECL|function|set_valkyrie_clock
r_static
r_void
id|set_valkyrie_clock
c_func
(paren
r_int
r_char
op_star
id|params
)paren
(brace
r_struct
id|adb_request
id|req
suffix:semicolon
r_int
id|i
suffix:semicolon
macro_line|#ifdef CONFIG_ADB_CUDA
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|3
suffix:semicolon
op_increment
id|i
)paren
(brace
id|cuda_request
c_func
(paren
op_amp
id|req
comma
l_int|NULL
comma
l_int|5
comma
id|CUDA_PACKET
comma
id|CUDA_GET_SET_IIC
comma
l_int|0x50
comma
id|i
op_plus
l_int|1
comma
id|params
(braket
id|i
)braket
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|req.complete
)paren
id|cuda_poll
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
DECL|function|valkyrie_choose_mode
r_static
r_void
id|__init
id|valkyrie_choose_mode
c_func
(paren
r_struct
id|fb_info_valkyrie
op_star
id|p
)paren
(brace
id|p-&gt;sense
op_assign
id|read_valkyrie_sense
c_func
(paren
id|p
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Monitor sense value = 0x%x&bslash;n&quot;
comma
id|p-&gt;sense
)paren
suffix:semicolon
multiline_comment|/* Try to pick a video mode out of NVRAM if we have one. */
macro_line|#ifndef CONFIG_MAC
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
id|valkyrie_reg_init
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
macro_line|#endif
r_if
c_cond
(paren
id|default_vmode
op_eq
id|VMODE_CHOOSE
)paren
id|default_vmode
op_assign
id|mac_map_monitor_sense
c_func
(paren
id|p-&gt;sense
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|valkyrie_reg_init
(braket
id|default_vmode
op_minus
l_int|1
)braket
)paren
id|default_vmode
op_assign
id|VMODE_640_480_67
suffix:semicolon
macro_line|#ifndef CONFIG_MAC
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
macro_line|#endif
multiline_comment|/*&n;&t; * Reduce the pixel size if we don&squot;t have enough VRAM or bandwidth.&n;&t; */
r_if
c_cond
(paren
id|default_cmode
template_param
id|CMODE_16
op_logical_or
id|valkyrie_reg_init
(braket
id|default_vmode
op_minus
l_int|1
)braket
op_member_access_from_pointer
id|pitch
(braket
id|default_cmode
)braket
op_eq
l_int|0
op_logical_or
id|valkyrie_vram_reqd
c_func
(paren
id|default_vmode
comma
id|default_cmode
)paren
OG
id|p-&gt;total_vram
)paren
id|default_cmode
op_assign
id|CMODE_8
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;using video mode %d and color mode %d.&bslash;n&quot;
comma
id|default_vmode
comma
id|default_cmode
)paren
suffix:semicolon
)brace
DECL|function|valkyriefb_init
r_int
id|__init
id|valkyriefb_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|fb_info_valkyrie
op_star
id|p
suffix:semicolon
r_int
r_int
id|frame_buffer_phys
comma
id|cmap_regs_phys
comma
id|flags
suffix:semicolon
r_int
id|err
suffix:semicolon
id|valkyriefb_setup
c_func
(paren
id|fb_get_options
c_func
(paren
l_string|&quot;valkyriefb&quot;
)paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_MAC
r_if
c_cond
(paren
op_logical_neg
id|MACH_IS_MAC
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|mac_bi_data.id
op_eq
id|MAC_MODEL_Q630
multiline_comment|/* I&squot;m not sure about this one */
op_logical_or
id|mac_bi_data.id
op_eq
id|MAC_MODEL_P588
)paren
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Hardcoded addresses... welcome to 68k Macintosh country :-) */
id|frame_buffer_phys
op_assign
l_int|0xf9000000
suffix:semicolon
id|cmap_regs_phys
op_assign
l_int|0x50f24000
suffix:semicolon
id|flags
op_assign
id|IOMAP_NOCACHE_SER
suffix:semicolon
multiline_comment|/* IOMAP_WRITETHROUGH?? */
macro_line|#else /* ppc (!CONFIG_MAC) */
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
l_string|&quot;valkyrie&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dp
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|dp-&gt;n_addrs
op_ne
l_int|1
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;expecting 1 address for valkyrie (got %d)&bslash;n&quot;
comma
id|dp-&gt;n_addrs
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|frame_buffer_phys
op_assign
id|dp-&gt;addrs
(braket
l_int|0
)braket
dot
id|address
suffix:semicolon
id|cmap_regs_phys
op_assign
id|dp-&gt;addrs
(braket
l_int|0
)braket
dot
id|address
op_plus
l_int|0x304000
suffix:semicolon
id|flags
op_assign
id|_PAGE_WRITETHRU
suffix:semicolon
macro_line|#endif /* ppc (!CONFIG_MAC) */
id|p
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|p
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p
op_eq
l_int|0
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
id|p
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|p
)paren
)paren
suffix:semicolon
multiline_comment|/* Map in frame buffer and registers */
r_if
c_cond
(paren
op_logical_neg
id|request_mem_region
c_func
(paren
id|frame_buffer_phys
comma
l_int|0x100000
comma
l_string|&quot;valkyriefb&quot;
)paren
)paren
(brace
id|kfree
c_func
(paren
id|p
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|p-&gt;total_vram
op_assign
l_int|0x100000
suffix:semicolon
id|p-&gt;frame_buffer_phys
op_assign
id|frame_buffer_phys
suffix:semicolon
id|p-&gt;frame_buffer
op_assign
id|__ioremap
c_func
(paren
id|frame_buffer_phys
comma
id|p-&gt;total_vram
comma
id|flags
)paren
suffix:semicolon
id|p-&gt;cmap_regs_phys
op_assign
id|cmap_regs_phys
suffix:semicolon
id|p-&gt;cmap_regs
op_assign
id|ioremap
c_func
(paren
id|p-&gt;cmap_regs_phys
comma
l_int|0x1000
)paren
suffix:semicolon
id|p-&gt;valkyrie_regs_phys
op_assign
id|cmap_regs_phys
op_plus
l_int|0x6000
suffix:semicolon
id|p-&gt;valkyrie_regs
op_assign
id|ioremap
c_func
(paren
id|p-&gt;valkyrie_regs_phys
comma
l_int|0x1000
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;frame_buffer
op_eq
l_int|NULL
op_logical_or
id|p-&gt;cmap_regs
op_eq
l_int|NULL
op_logical_or
id|p-&gt;valkyrie_regs
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;valkyriefb: couldn&squot;t map resources&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out_free
suffix:semicolon
)brace
id|valkyrie_choose_mode
c_func
(paren
id|p
)paren
suffix:semicolon
id|mac_vmode_to_var
c_func
(paren
id|default_vmode
comma
id|default_cmode
comma
op_amp
id|p-&gt;info.var
)paren
suffix:semicolon
id|valkyrie_init_info
c_func
(paren
op_amp
id|p-&gt;info
comma
id|p
)paren
suffix:semicolon
id|valkyrie_init_fix
c_func
(paren
op_amp
id|p-&gt;info.fix
comma
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
id|valkyriefb_set_par
c_func
(paren
op_amp
id|p-&gt;info
)paren
)paren
multiline_comment|/* &quot;can&squot;t happen&quot; */
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;valkyriefb: can&squot;t set default video mode&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|register_framebuffer
c_func
(paren
op_amp
id|p-&gt;info
)paren
)paren
op_ne
l_int|0
)paren
r_goto
id|out_free
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;fb%d: valkyrie frame buffer device&bslash;n&quot;
comma
id|p-&gt;info.node
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|out_free
suffix:colon
r_if
c_cond
(paren
id|p-&gt;frame_buffer
)paren
id|iounmap
c_func
(paren
id|p-&gt;frame_buffer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;cmap_regs
)paren
id|iounmap
c_func
(paren
id|p-&gt;cmap_regs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;valkyrie_regs
)paren
id|iounmap
c_func
(paren
id|p-&gt;valkyrie_regs
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|p
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/*&n; * Get the monitor sense value.&n; */
DECL|function|read_valkyrie_sense
r_static
r_int
id|read_valkyrie_sense
c_func
(paren
r_struct
id|fb_info_valkyrie
op_star
id|p
)paren
(brace
r_int
id|sense
comma
id|in
suffix:semicolon
id|out_8
c_func
(paren
op_amp
id|p-&gt;valkyrie_regs-&gt;msense.r
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* release all lines */
id|__delay
c_func
(paren
l_int|20000
)paren
suffix:semicolon
id|sense
op_assign
(paren
(paren
id|in
op_assign
id|in_8
c_func
(paren
op_amp
id|p-&gt;valkyrie_regs-&gt;msense.r
)paren
)paren
op_amp
l_int|0x70
)paren
op_lshift
l_int|4
suffix:semicolon
multiline_comment|/* drive each sense line low in turn and collect the other 2 */
id|out_8
c_func
(paren
op_amp
id|p-&gt;valkyrie_regs-&gt;msense.r
comma
l_int|4
)paren
suffix:semicolon
multiline_comment|/* drive A low */
id|__delay
c_func
(paren
l_int|20000
)paren
suffix:semicolon
id|sense
op_or_assign
(paren
(paren
id|in
op_assign
id|in_8
c_func
(paren
op_amp
id|p-&gt;valkyrie_regs-&gt;msense.r
)paren
)paren
op_amp
l_int|0x30
)paren
suffix:semicolon
id|out_8
c_func
(paren
op_amp
id|p-&gt;valkyrie_regs-&gt;msense.r
comma
l_int|2
)paren
suffix:semicolon
multiline_comment|/* drive B low */
id|__delay
c_func
(paren
l_int|20000
)paren
suffix:semicolon
id|sense
op_or_assign
(paren
(paren
id|in
op_assign
id|in_8
c_func
(paren
op_amp
id|p-&gt;valkyrie_regs-&gt;msense.r
)paren
)paren
op_amp
l_int|0x40
)paren
op_rshift
l_int|3
suffix:semicolon
id|sense
op_or_assign
(paren
id|in
op_amp
l_int|0x10
)paren
op_rshift
l_int|2
suffix:semicolon
id|out_8
c_func
(paren
op_amp
id|p-&gt;valkyrie_regs-&gt;msense.r
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/* drive C low */
id|__delay
c_func
(paren
l_int|20000
)paren
suffix:semicolon
id|sense
op_or_assign
(paren
(paren
id|in
op_assign
id|in_8
c_func
(paren
op_amp
id|p-&gt;valkyrie_regs-&gt;msense.r
)paren
)paren
op_amp
l_int|0x60
)paren
op_rshift
l_int|5
suffix:semicolon
id|out_8
c_func
(paren
op_amp
id|p-&gt;valkyrie_regs-&gt;msense.r
comma
l_int|7
)paren
suffix:semicolon
r_return
id|sense
suffix:semicolon
)brace
multiline_comment|/*&n; * This routine takes a user-supplied var,&n; * and picks the best vmode/cmode from it.&n; */
multiline_comment|/* [bkn] I did a major overhaul of this function.&n; *&n; * Much of the old code was &quot;swiped by jonh from atyfb.c&quot;. Because&n; * macmodes has mac_var_to_vmode, I felt that it would be better to&n; * rework this function to use that, instead of reinventing the wheel to&n; * add support for vmode 17. This was reinforced by the fact that&n; * the previously swiped atyfb.c code is no longer there.&n; *&n; * So, I swiped and adapted platinum_var_to_par (from platinumfb.c), replacing&n; * most, but not all, of the old code in the process. One side benefit of&n; * swiping the platinumfb code is that we now have more comprehensible error&n; * messages when a vmode/cmode switch fails. (Most of the error messages are&n; * platinumfb.c, but I added two of my own, and I also changed some commas&n; * into colons to make the messages more consistent with other Linux error&n; * messages.) In addition, I think the new code *might* fix some vmode-&n; * switching oddities, but I&squot;m not sure.&n; *&n; * There may be some more opportunities for cleanup in here, but this is a&n; * good start...&n; */
DECL|function|valkyrie_var_to_par
r_static
r_int
id|valkyrie_var_to_par
c_func
(paren
r_struct
id|fb_var_screeninfo
op_star
id|var
comma
r_struct
id|fb_par_valkyrie
op_star
id|par
comma
r_const
r_struct
id|fb_info
op_star
id|fb_info
)paren
(brace
r_int
id|vmode
comma
id|cmode
suffix:semicolon
r_struct
id|valkyrie_regvals
op_star
id|init
suffix:semicolon
r_struct
id|fb_info_valkyrie
op_star
id|p
op_assign
(paren
r_struct
id|fb_info_valkyrie
op_star
)paren
id|fb_info
suffix:semicolon
r_if
c_cond
(paren
id|mac_var_to_vmode
c_func
(paren
id|var
comma
op_amp
id|vmode
comma
op_amp
id|cmode
)paren
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;valkyriefb: can&squot;t do %dx%dx%d.&bslash;n&quot;
comma
id|var-&gt;xres
comma
id|var-&gt;yres
comma
id|var-&gt;bits_per_pixel
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/* Check if we know about the wanted video mode */
r_if
c_cond
(paren
id|vmode
template_param
id|VMODE_MAX
op_logical_or
op_logical_neg
id|valkyrie_reg_init
(braket
id|vmode
op_minus
l_int|1
)braket
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;valkyriefb: vmode %d not valid.&bslash;n&quot;
comma
id|vmode
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
id|cmode
op_ne
id|CMODE_8
op_logical_and
id|cmode
op_ne
id|CMODE_16
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;valkyriefb: cmode %d not valid.&bslash;n&quot;
comma
id|cmode
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
id|var-&gt;xres_virtual
OG
id|var-&gt;xres
op_logical_or
id|var-&gt;yres_virtual
OG
id|var-&gt;yres
op_logical_or
id|var-&gt;xoffset
op_ne
l_int|0
op_logical_or
id|var-&gt;yoffset
op_ne
l_int|0
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|init
op_assign
id|valkyrie_reg_init
(braket
id|vmode
op_minus
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
id|init-&gt;pitch
(braket
id|cmode
)braket
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;valkyriefb: vmode %d does not support &quot;
l_string|&quot;cmode %d.&bslash;n&quot;
comma
id|vmode
comma
id|cmode
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
id|valkyrie_vram_reqd
c_func
(paren
id|vmode
comma
id|cmode
)paren
OG
id|p-&gt;total_vram
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;valkyriefb: not enough ram for vmode %d, &quot;
l_string|&quot;cmode %d.&bslash;n&quot;
comma
id|vmode
comma
id|cmode
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|par-&gt;vmode
op_assign
id|vmode
suffix:semicolon
id|par-&gt;cmode
op_assign
id|cmode
suffix:semicolon
id|par-&gt;init
op_assign
id|init
suffix:semicolon
id|par-&gt;xres
op_assign
id|var-&gt;xres
suffix:semicolon
id|par-&gt;yres
op_assign
id|var-&gt;yres
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
DECL|function|valkyrie_init_fix
r_static
r_void
id|valkyrie_init_fix
c_func
(paren
r_struct
id|fb_fix_screeninfo
op_star
id|fix
comma
r_struct
id|fb_info_valkyrie
op_star
id|p
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
op_star
id|fix
)paren
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|fix-&gt;id
comma
l_string|&quot;valkyrie&quot;
)paren
suffix:semicolon
id|fix-&gt;mmio_start
op_assign
id|p-&gt;valkyrie_regs_phys
suffix:semicolon
id|fix-&gt;mmio_len
op_assign
r_sizeof
(paren
r_struct
id|valkyrie_regs
)paren
suffix:semicolon
id|fix-&gt;type
op_assign
id|FB_TYPE_PACKED_PIXELS
suffix:semicolon
id|fix-&gt;smem_start
op_assign
id|p-&gt;frame_buffer_phys
op_plus
l_int|0x1000
suffix:semicolon
id|fix-&gt;smem_len
op_assign
id|p-&gt;total_vram
suffix:semicolon
id|fix-&gt;type_aux
op_assign
l_int|0
suffix:semicolon
id|fix-&gt;ywrapstep
op_assign
l_int|0
suffix:semicolon
id|fix-&gt;ypanstep
op_assign
l_int|0
suffix:semicolon
id|fix-&gt;xpanstep
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Fix must already be inited above */
DECL|function|valkyrie_par_to_fix
r_static
r_void
id|valkyrie_par_to_fix
c_func
(paren
r_struct
id|fb_par_valkyrie
op_star
id|par
comma
r_struct
id|fb_fix_screeninfo
op_star
id|fix
)paren
(brace
id|fix-&gt;smem_len
op_assign
id|valkyrie_vram_reqd
c_func
(paren
id|par-&gt;vmode
comma
id|par-&gt;cmode
)paren
suffix:semicolon
id|fix-&gt;visual
op_assign
(paren
id|par-&gt;cmode
op_eq
id|CMODE_8
)paren
ques
c_cond
id|FB_VISUAL_PSEUDOCOLOR
suffix:colon
id|FB_VISUAL_DIRECTCOLOR
suffix:semicolon
id|fix-&gt;line_length
op_assign
id|par-&gt;vxres
op_lshift
id|par-&gt;cmode
suffix:semicolon
multiline_comment|/* ywrapstep, xpanstep, ypanstep */
)brace
DECL|function|valkyrie_init_info
r_static
r_void
id|__init
id|valkyrie_init_info
c_func
(paren
r_struct
id|fb_info
op_star
id|info
comma
r_struct
id|fb_info_valkyrie
op_star
id|p
)paren
(brace
id|info-&gt;fbops
op_assign
op_amp
id|valkyriefb_ops
suffix:semicolon
id|info-&gt;screen_base
op_assign
(paren
r_char
op_star
)paren
id|p-&gt;frame_buffer
op_plus
l_int|0x1000
suffix:semicolon
id|info-&gt;flags
op_assign
id|FBINFO_DEFAULT
suffix:semicolon
id|info-&gt;pseudo_palette
op_assign
id|p-&gt;pseudo_palette
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
id|info-&gt;par
op_assign
op_amp
id|p-&gt;par
suffix:semicolon
)brace
multiline_comment|/*&n; * Parse user speficied options (`video=valkyriefb:&squot;)&n; */
DECL|function|valkyriefb_setup
r_int
id|__init
id|valkyriefb_setup
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
)brace
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|valkyriefb_init
id|module_init
c_func
(paren
id|valkyriefb_init
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
