multiline_comment|/*&n; *  linux/drivers/video/offb.c -- Open Firmware based frame buffer device&n; *&n; *&t;Copyright (C) 1997 Geert Uytterhoeven&n; *&n; *  This driver is partly based on the PowerMac console driver:&n; *&n; *&t;Copyright (C) 1996 Paul Mackerras&n; *&n; *  This file is subject to the terms and conditions of the GNU General Public&n; *  License. See the file COPYING in the main directory of this archive for&n; *  more details.&n; */
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
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#ifdef CONFIG_BOOTX_TEXT
macro_line|#include &lt;asm/bootx.h&gt;
macro_line|#endif
macro_line|#include &lt;video/fbcon.h&gt;
macro_line|#include &lt;video/macmodes.h&gt;
multiline_comment|/* Supported palette hacks */
r_enum
(brace
DECL|enumerator|cmap_unknown
id|cmap_unknown
comma
DECL|enumerator|cmap_m64
id|cmap_m64
comma
multiline_comment|/* ATI Mach64 */
DECL|enumerator|cmap_r128
id|cmap_r128
comma
multiline_comment|/* ATI Rage128 */
DECL|enumerator|cmap_M3A
id|cmap_M3A
comma
multiline_comment|/* ATI Rage Mobility M3 Head A */
DECL|enumerator|cmap_M3B
id|cmap_M3B
comma
multiline_comment|/* ATI Rage Mobility M3 Head B */
DECL|enumerator|cmap_radeon
id|cmap_radeon
comma
multiline_comment|/* ATI Radeon */
DECL|enumerator|cmap_gxt2000
id|cmap_gxt2000
comma
multiline_comment|/* IBM GXT2000 */
)brace
suffix:semicolon
DECL|struct|offb_par
r_struct
id|offb_par
(brace
DECL|member|cmap_adr
r_volatile
r_int
r_char
op_star
id|cmap_adr
suffix:semicolon
DECL|member|cmap_data
r_volatile
r_int
r_char
op_star
id|cmap_data
suffix:semicolon
DECL|member|cmap_type
r_int
id|cmap_type
suffix:semicolon
DECL|member|blanked
r_int
id|blanked
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|default_par
r_struct
id|offb_par
id|default_par
suffix:semicolon
macro_line|#ifdef __powerpc__
DECL|macro|mach_eieio
mdefine_line|#define mach_eieio()&t;eieio()
macro_line|#else
DECL|macro|mach_eieio
mdefine_line|#define mach_eieio()&t;do {} while (0)
macro_line|#endif
multiline_comment|/*&n;     *  Interface used by the world&n;     */
r_int
id|offb_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_int
id|offb_setcolreg
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
id|offb_blank
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
suffix:semicolon
macro_line|#ifdef CONFIG_BOOTX_TEXT
r_extern
id|boot_infos_t
op_star
id|boot_infos
suffix:semicolon
macro_line|#endif
r_static
r_void
id|offb_init_nodriver
c_func
(paren
r_struct
id|device_node
op_star
)paren
suffix:semicolon
r_static
r_void
id|offb_init_fb
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_const
r_char
op_star
id|full_name
comma
r_int
id|width
comma
r_int
id|height
comma
r_int
id|depth
comma
r_int
id|pitch
comma
r_int
r_int
id|address
comma
r_struct
id|device_node
op_star
id|dp
)paren
suffix:semicolon
DECL|variable|offb_ops
r_static
r_struct
id|fb_ops
id|offb_ops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|fb_set_var
op_assign
id|gen_set_var
comma
dot
id|fb_get_cmap
op_assign
id|gen_get_cmap
comma
dot
id|fb_set_cmap
op_assign
id|gen_set_cmap
comma
dot
id|fb_setcolreg
op_assign
id|offb_setcolreg
comma
dot
id|fb_blank
op_assign
id|offb_blank
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
)brace
suffix:semicolon
multiline_comment|/*&n;     *  Set a single color register. The values supplied are already&n;     *  rounded down to the hardware&squot;s capabilities (according to the&n;     *  entries in the var structure). Return != 0 for invalid regno.&n;     */
DECL|function|offb_setcolreg
r_static
r_int
id|offb_setcolreg
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
id|offb_par
op_star
id|par
op_assign
(paren
r_struct
id|offb_par
op_star
)paren
id|info-&gt;par
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|par-&gt;cmap_adr
op_logical_or
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
r_switch
c_cond
(paren
id|par-&gt;cmap_type
)paren
(brace
r_case
id|cmap_m64
suffix:colon
op_star
id|par-&gt;cmap_adr
op_assign
id|regno
suffix:semicolon
id|mach_eieio
c_func
(paren
)paren
suffix:semicolon
op_star
id|par-&gt;cmap_data
op_assign
id|red
suffix:semicolon
id|mach_eieio
c_func
(paren
)paren
suffix:semicolon
op_star
id|par-&gt;cmap_data
op_assign
id|green
suffix:semicolon
id|mach_eieio
c_func
(paren
)paren
suffix:semicolon
op_star
id|par-&gt;cmap_data
op_assign
id|blue
suffix:semicolon
id|mach_eieio
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|cmap_M3A
suffix:colon
multiline_comment|/* Clear PALETTE_ACCESS_CNTL in DAC_CNTL */
id|out_le32
c_func
(paren
(paren
r_int
op_star
)paren
(paren
id|par-&gt;cmap_adr
op_plus
l_int|0x58
)paren
comma
id|in_le32
c_func
(paren
(paren
r_int
op_star
)paren
(paren
id|par-&gt;cmap_adr
op_plus
l_int|0x58
)paren
)paren
op_amp
op_complement
l_int|0x20
)paren
suffix:semicolon
r_case
id|cmap_r128
suffix:colon
multiline_comment|/* Set palette index &amp; data */
id|out_8
c_func
(paren
id|par-&gt;cmap_adr
op_plus
l_int|0xb0
comma
id|regno
)paren
suffix:semicolon
id|out_le32
c_func
(paren
(paren
r_int
op_star
)paren
(paren
id|par-&gt;cmap_adr
op_plus
l_int|0xb4
)paren
comma
(paren
id|red
op_lshift
l_int|16
op_or
id|green
op_lshift
l_int|8
op_or
id|blue
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|cmap_M3B
suffix:colon
multiline_comment|/* Set PALETTE_ACCESS_CNTL in DAC_CNTL */
id|out_le32
c_func
(paren
(paren
r_int
op_star
)paren
(paren
id|par-&gt;cmap_adr
op_plus
l_int|0x58
)paren
comma
id|in_le32
c_func
(paren
(paren
r_int
op_star
)paren
(paren
id|par-&gt;cmap_adr
op_plus
l_int|0x58
)paren
)paren
op_or
l_int|0x20
)paren
suffix:semicolon
multiline_comment|/* Set palette index &amp; data */
id|out_8
c_func
(paren
id|par-&gt;cmap_adr
op_plus
l_int|0xb0
comma
id|regno
)paren
suffix:semicolon
id|out_le32
c_func
(paren
(paren
r_int
op_star
)paren
(paren
id|par-&gt;cmap_adr
op_plus
l_int|0xb4
)paren
comma
(paren
id|red
op_lshift
l_int|16
op_or
id|green
op_lshift
l_int|8
op_or
id|blue
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|cmap_radeon
suffix:colon
multiline_comment|/* Set palette index &amp; data (could be smarter) */
id|out_8
c_func
(paren
id|par-&gt;cmap_adr
op_plus
l_int|0xb0
comma
id|regno
)paren
suffix:semicolon
id|out_le32
c_func
(paren
(paren
r_int
op_star
)paren
(paren
id|par-&gt;cmap_adr
op_plus
l_int|0xb4
)paren
comma
(paren
id|red
op_lshift
l_int|16
op_or
id|green
op_lshift
l_int|8
op_or
id|blue
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|cmap_gxt2000
suffix:colon
id|out_le32
c_func
(paren
(paren
r_int
op_star
)paren
id|par-&gt;cmap_adr
op_plus
id|regno
comma
(paren
id|red
op_lshift
l_int|16
op_or
id|green
op_lshift
l_int|8
op_or
id|blue
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|regno
OL
l_int|16
)paren
r_switch
c_cond
(paren
id|info-&gt;var.bits_per_pixel
)paren
(brace
r_case
l_int|16
suffix:colon
(paren
(paren
id|u16
op_star
)paren
(paren
id|info-&gt;pseudo_palette
)paren
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
r_break
suffix:semicolon
r_case
l_int|32
suffix:colon
(brace
r_int
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
(paren
(paren
id|u32
op_star
)paren
(paren
id|info-&gt;pseudo_palette
)paren
)paren
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
multiline_comment|/*&n;     *  Blank the display.&n;     */
DECL|function|offb_blank
r_static
r_int
id|offb_blank
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
r_struct
id|offb_par
op_star
id|par
op_assign
(paren
r_struct
id|offb_par
op_star
)paren
id|info-&gt;par
suffix:semicolon
r_int
id|i
comma
id|j
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|par-&gt;cmap_adr
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|par-&gt;blanked
)paren
r_if
c_cond
(paren
op_logical_neg
id|blank
)paren
r_return
l_int|0
suffix:semicolon
id|par-&gt;blanked
op_assign
id|blank
suffix:semicolon
r_if
c_cond
(paren
id|blank
)paren
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|256
suffix:semicolon
id|i
op_increment
)paren
(brace
r_switch
c_cond
(paren
id|par-&gt;cmap_type
)paren
(brace
r_case
id|cmap_m64
suffix:colon
op_star
id|par-&gt;cmap_adr
op_assign
id|i
suffix:semicolon
id|mach_eieio
c_func
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
l_int|3
suffix:semicolon
id|j
op_increment
)paren
(brace
op_star
id|par-&gt;cmap_data
op_assign
l_int|0
suffix:semicolon
id|mach_eieio
c_func
(paren
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|cmap_M3A
suffix:colon
multiline_comment|/* Clear PALETTE_ACCESS_CNTL in DAC_CNTL */
id|out_le32
c_func
(paren
(paren
r_int
op_star
)paren
(paren
id|par-&gt;cmap_adr
op_plus
l_int|0x58
)paren
comma
id|in_le32
c_func
(paren
(paren
r_int
op_star
)paren
(paren
id|par
op_member_access_from_pointer
id|cmap_adr
op_plus
l_int|0x58
)paren
)paren
op_amp
op_complement
l_int|0x20
)paren
suffix:semicolon
r_case
id|cmap_r128
suffix:colon
multiline_comment|/* Set palette index &amp; data */
id|out_8
c_func
(paren
id|par-&gt;cmap_adr
op_plus
l_int|0xb0
comma
id|i
)paren
suffix:semicolon
id|out_le32
c_func
(paren
(paren
r_int
op_star
)paren
(paren
id|par-&gt;cmap_adr
op_plus
l_int|0xb4
)paren
comma
l_int|0
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|cmap_M3B
suffix:colon
multiline_comment|/* Set PALETTE_ACCESS_CNTL in DAC_CNTL */
id|out_le32
c_func
(paren
(paren
r_int
op_star
)paren
(paren
id|par-&gt;cmap_adr
op_plus
l_int|0x58
)paren
comma
id|in_le32
c_func
(paren
(paren
r_int
op_star
)paren
(paren
id|par
op_member_access_from_pointer
id|cmap_adr
op_plus
l_int|0x58
)paren
)paren
op_or
l_int|0x20
)paren
suffix:semicolon
multiline_comment|/* Set palette index &amp; data */
id|out_8
c_func
(paren
id|par-&gt;cmap_adr
op_plus
l_int|0xb0
comma
id|i
)paren
suffix:semicolon
id|out_le32
c_func
(paren
(paren
r_int
op_star
)paren
(paren
id|par-&gt;cmap_adr
op_plus
l_int|0xb4
)paren
comma
l_int|0
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|cmap_radeon
suffix:colon
id|out_8
c_func
(paren
id|par-&gt;cmap_adr
op_plus
l_int|0xb0
comma
id|i
)paren
suffix:semicolon
id|out_le32
c_func
(paren
(paren
r_int
op_star
)paren
(paren
id|par-&gt;cmap_adr
op_plus
l_int|0xb4
)paren
comma
l_int|0
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|cmap_gxt2000
suffix:colon
id|out_le32
c_func
(paren
(paren
r_int
op_star
)paren
id|par-&gt;cmap_adr
op_plus
id|i
comma
l_int|0
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_else
id|fb_set_cmap
c_func
(paren
op_amp
id|info-&gt;cmap
comma
l_int|1
comma
id|info
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;     *  Initialisation&n;     */
DECL|function|offb_init
r_int
id|__init
id|offb_init
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
r_int
r_int
id|dpy
suffix:semicolon
macro_line|#ifdef CONFIG_BOOTX_TEXT
r_struct
id|device_node
op_star
id|displays
op_assign
id|find_type_devices
c_func
(paren
l_string|&quot;display&quot;
)paren
suffix:semicolon
r_struct
id|device_node
op_star
id|macos_display
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* If we&squot;re booted from BootX... */
r_if
c_cond
(paren
id|prom_num_displays
op_eq
l_int|0
op_logical_and
id|boot_infos
op_ne
l_int|0
)paren
(brace
r_int
r_int
id|addr
op_assign
(paren
r_int
r_int
)paren
id|boot_infos-&gt;dispDeviceBase
suffix:semicolon
multiline_comment|/* find the device node corresponding to the macos display */
r_for
c_loop
(paren
id|dp
op_assign
id|displays
suffix:semicolon
id|dp
op_ne
l_int|NULL
suffix:semicolon
id|dp
op_assign
id|dp-&gt;next
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * Grrr...  It looks like the MacOS ATI driver&n;&t;&t;&t; * munges the assigned-addresses property (but&n;&t;&t;&t; * the AAPL,address value is OK).&n;&t;&t;&t; */
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|dp-&gt;name
comma
l_string|&quot;ATY,&quot;
comma
l_int|4
)paren
op_eq
l_int|0
op_logical_and
id|dp-&gt;n_addrs
op_eq
l_int|1
)paren
(brace
r_int
r_int
op_star
id|ap
op_assign
(paren
r_int
r_int
op_star
)paren
id|get_property
c_func
(paren
id|dp
comma
l_string|&quot;AAPL,address&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ap
op_ne
l_int|NULL
)paren
(brace
id|dp-&gt;addrs
(braket
l_int|0
)braket
dot
id|address
op_assign
op_star
id|ap
suffix:semicolon
id|dp-&gt;addrs
(braket
l_int|0
)braket
dot
id|size
op_assign
l_int|0x01000000
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t;&t;&t; * The LTPro on the Lombard powerbook has no addresses&n;&t;&t;&t; * on the display nodes, they are on their parent.&n;&t;&t;&t; */
r_if
c_cond
(paren
id|dp-&gt;n_addrs
op_eq
l_int|0
op_logical_and
id|device_is_compatible
c_func
(paren
id|dp
comma
l_string|&quot;ATY,264LTPro&quot;
)paren
)paren
(brace
r_int
id|na
suffix:semicolon
r_int
r_int
op_star
id|ap
op_assign
(paren
r_int
r_int
op_star
)paren
id|get_property
c_func
(paren
id|dp
comma
l_string|&quot;AAPL,address&quot;
comma
op_amp
id|na
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ap
op_ne
l_int|0
)paren
r_for
c_loop
(paren
id|na
op_div_assign
r_sizeof
(paren
r_int
r_int
)paren
suffix:semicolon
id|na
OG
l_int|0
suffix:semicolon
op_decrement
id|na
comma
op_increment
id|ap
)paren
r_if
c_cond
(paren
op_star
id|ap
op_le
id|addr
op_logical_and
id|addr
OL
op_star
id|ap
op_plus
l_int|0x1000000
)paren
r_goto
id|foundit
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t;&t; * See if the display address is in one of the address&n;&t;&t;&t; * ranges for this display.&n;&t;&t;&t; */
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
r_if
c_cond
(paren
id|dp-&gt;addrs
(braket
id|i
)braket
dot
id|address
op_le
id|addr
op_logical_and
id|addr
OL
id|dp-&gt;addrs
(braket
id|i
)braket
dot
id|address
op_plus
id|dp-&gt;addrs
(braket
id|i
)braket
dot
id|size
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
OL
id|dp-&gt;n_addrs
)paren
(brace
id|foundit
suffix:colon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;MacOS display is %s&bslash;n&quot;
comma
id|dp-&gt;full_name
)paren
suffix:semicolon
id|macos_display
op_assign
id|dp
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/* initialize it */
id|offb_init_fb
c_func
(paren
id|macos_display
ques
c_cond
id|macos_display
op_member_access_from_pointer
id|name
suffix:colon
l_string|&quot;MacOS display&quot;
comma
id|macos_display
ques
c_cond
id|macos_display
op_member_access_from_pointer
id|full_name
suffix:colon
l_string|&quot;MacOS display&quot;
comma
id|boot_infos-&gt;dispDeviceRect
(braket
l_int|2
)braket
comma
id|boot_infos-&gt;dispDeviceRect
(braket
l_int|3
)braket
comma
id|boot_infos-&gt;dispDeviceDepth
comma
id|boot_infos-&gt;dispDeviceRowBytes
comma
id|addr
comma
l_int|NULL
)paren
suffix:semicolon
)brace
macro_line|#endif
r_for
c_loop
(paren
id|dpy
op_assign
l_int|0
suffix:semicolon
id|dpy
OL
id|prom_num_displays
suffix:semicolon
id|dpy
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
id|dp
op_assign
id|find_path_device
c_func
(paren
id|prom_display_paths
(braket
id|dpy
)braket
)paren
)paren
)paren
id|offb_init_nodriver
c_func
(paren
id|dp
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|offb_init_nodriver
r_static
r_void
id|__init
id|offb_init_nodriver
c_func
(paren
r_struct
id|device_node
op_star
id|dp
)paren
(brace
r_int
op_star
id|pp
comma
id|i
suffix:semicolon
r_int
r_int
id|len
suffix:semicolon
r_int
id|width
op_assign
l_int|640
comma
id|height
op_assign
l_int|480
comma
id|depth
op_assign
l_int|8
comma
id|pitch
suffix:semicolon
r_int
op_star
id|up
comma
id|address
suffix:semicolon
r_if
c_cond
(paren
(paren
id|pp
op_assign
(paren
r_int
op_star
)paren
id|get_property
c_func
(paren
id|dp
comma
l_string|&quot;depth&quot;
comma
op_amp
id|len
)paren
)paren
op_ne
l_int|NULL
op_logical_and
id|len
op_eq
r_sizeof
(paren
r_int
)paren
)paren
id|depth
op_assign
op_star
id|pp
suffix:semicolon
r_if
c_cond
(paren
(paren
id|pp
op_assign
(paren
r_int
op_star
)paren
id|get_property
c_func
(paren
id|dp
comma
l_string|&quot;width&quot;
comma
op_amp
id|len
)paren
)paren
op_ne
l_int|NULL
op_logical_and
id|len
op_eq
r_sizeof
(paren
r_int
)paren
)paren
id|width
op_assign
op_star
id|pp
suffix:semicolon
r_if
c_cond
(paren
(paren
id|pp
op_assign
(paren
r_int
op_star
)paren
id|get_property
c_func
(paren
id|dp
comma
l_string|&quot;height&quot;
comma
op_amp
id|len
)paren
)paren
op_ne
l_int|NULL
op_logical_and
id|len
op_eq
r_sizeof
(paren
r_int
)paren
)paren
id|height
op_assign
op_star
id|pp
suffix:semicolon
r_if
c_cond
(paren
(paren
id|pp
op_assign
(paren
r_int
op_star
)paren
id|get_property
c_func
(paren
id|dp
comma
l_string|&quot;linebytes&quot;
comma
op_amp
id|len
)paren
)paren
op_ne
l_int|NULL
op_logical_and
id|len
op_eq
r_sizeof
(paren
r_int
)paren
)paren
(brace
id|pitch
op_assign
op_star
id|pp
suffix:semicolon
r_if
c_cond
(paren
id|pitch
op_eq
l_int|1
)paren
id|pitch
op_assign
l_int|0x1000
suffix:semicolon
)brace
r_else
id|pitch
op_assign
id|width
suffix:semicolon
r_if
c_cond
(paren
(paren
id|up
op_assign
(paren
r_int
op_star
)paren
id|get_property
c_func
(paren
id|dp
comma
l_string|&quot;address&quot;
comma
op_amp
id|len
)paren
)paren
op_ne
l_int|NULL
op_logical_and
id|len
op_eq
r_sizeof
(paren
r_int
)paren
)paren
id|address
op_assign
(paren
id|u_long
)paren
op_star
id|up
suffix:semicolon
r_else
(brace
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
r_if
c_cond
(paren
id|dp-&gt;addrs
(braket
id|i
)braket
dot
id|size
op_ge
id|pitch
op_star
id|height
op_star
id|depth
op_div
l_int|8
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ge
id|dp-&gt;n_addrs
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;no framebuffer address found for %s&bslash;n&quot;
comma
id|dp-&gt;full_name
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|address
op_assign
(paren
id|u_long
)paren
id|dp-&gt;addrs
(braket
id|i
)braket
dot
id|address
suffix:semicolon
multiline_comment|/* kludge for valkyrie */
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|dp-&gt;name
comma
l_string|&quot;valkyrie&quot;
)paren
op_eq
l_int|0
)paren
id|address
op_add_assign
l_int|0x1000
suffix:semicolon
)brace
id|offb_init_fb
c_func
(paren
id|dp-&gt;name
comma
id|dp-&gt;full_name
comma
id|width
comma
id|height
comma
id|depth
comma
id|pitch
comma
id|address
comma
id|dp
)paren
suffix:semicolon
)brace
DECL|function|offb_init_fb
r_static
r_void
id|__init
id|offb_init_fb
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_const
r_char
op_star
id|full_name
comma
r_int
id|width
comma
r_int
id|height
comma
r_int
id|depth
comma
r_int
id|pitch
comma
r_int
r_int
id|address
comma
r_struct
id|device_node
op_star
id|dp
)paren
(brace
r_int
r_int
id|res_size
op_assign
id|pitch
op_star
id|height
op_star
id|depth
op_div
l_int|8
suffix:semicolon
r_struct
id|offb_par
op_star
id|par
op_assign
op_amp
id|default_par
suffix:semicolon
r_int
r_int
id|res_start
op_assign
id|address
suffix:semicolon
r_struct
id|fb_fix_screeninfo
op_star
id|fix
suffix:semicolon
r_struct
id|fb_var_screeninfo
op_star
id|var
suffix:semicolon
r_struct
id|fb_info
op_star
id|info
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|request_mem_region
c_func
(paren
id|res_start
comma
id|res_size
comma
l_string|&quot;offb&quot;
)paren
)paren
r_return
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Using unsupported %dx%d %s at %lx, depth=%d, pitch=%d&bslash;n&quot;
comma
id|width
comma
id|height
comma
id|name
comma
id|address
comma
id|depth
comma
id|pitch
)paren
suffix:semicolon
r_if
c_cond
(paren
id|depth
op_ne
l_int|8
op_logical_and
id|depth
op_ne
l_int|16
op_logical_and
id|depth
op_ne
l_int|32
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: can&squot;t use depth = %d&bslash;n&quot;
comma
id|full_name
comma
id|depth
)paren
suffix:semicolon
id|release_mem_region
c_func
(paren
id|res_start
comma
id|res_size
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
r_struct
id|fb_info
)paren
op_plus
r_sizeof
(paren
r_struct
id|display
)paren
op_plus
r_sizeof
(paren
id|u32
)paren
op_star
l_int|17
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
(brace
id|release_mem_region
c_func
(paren
id|res_start
comma
id|res_size
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
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
id|fix
op_assign
op_amp
id|info-&gt;fix
suffix:semicolon
id|var
op_assign
op_amp
id|info-&gt;var
suffix:semicolon
id|strcpy
c_func
(paren
id|fix-&gt;id
comma
l_string|&quot;OFfb &quot;
)paren
suffix:semicolon
id|strncat
c_func
(paren
id|fix-&gt;id
comma
id|name
comma
r_sizeof
(paren
id|fix-&gt;id
)paren
)paren
suffix:semicolon
id|fix-&gt;id
(braket
r_sizeof
(paren
id|fix-&gt;id
)paren
op_minus
l_int|1
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|var-&gt;xres
op_assign
id|var-&gt;xres_virtual
op_assign
id|width
suffix:semicolon
id|var-&gt;yres
op_assign
id|var-&gt;yres_virtual
op_assign
id|height
suffix:semicolon
id|fix-&gt;line_length
op_assign
id|pitch
suffix:semicolon
id|fix-&gt;smem_start
op_assign
id|address
suffix:semicolon
id|fix-&gt;smem_len
op_assign
id|pitch
op_star
id|height
suffix:semicolon
id|fix-&gt;type
op_assign
id|FB_TYPE_PACKED_PIXELS
suffix:semicolon
id|fix-&gt;type_aux
op_assign
l_int|0
suffix:semicolon
id|par-&gt;cmap_type
op_assign
id|cmap_unknown
suffix:semicolon
r_if
c_cond
(paren
id|depth
op_eq
l_int|8
)paren
(brace
multiline_comment|/* XXX kludge for ati */
r_if
c_cond
(paren
id|dp
op_logical_and
op_logical_neg
id|strncmp
c_func
(paren
id|name
comma
l_string|&quot;ATY,Rage128&quot;
comma
l_int|11
)paren
)paren
(brace
r_int
r_int
id|regbase
op_assign
id|dp-&gt;addrs
(braket
l_int|2
)braket
dot
id|address
suffix:semicolon
id|par-&gt;cmap_adr
op_assign
id|ioremap
c_func
(paren
id|regbase
comma
l_int|0x1FFF
)paren
suffix:semicolon
id|par-&gt;cmap_type
op_assign
id|cmap_r128
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|dp
op_logical_and
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|name
comma
l_string|&quot;ATY,RageM3pA&quot;
comma
l_int|12
)paren
op_logical_or
op_logical_neg
id|strncmp
c_func
(paren
id|name
comma
l_string|&quot;ATY,RageM3p12A&quot;
comma
l_int|14
)paren
)paren
)paren
(brace
r_int
r_int
id|regbase
op_assign
id|dp-&gt;parent-&gt;addrs
(braket
l_int|2
)braket
dot
id|address
suffix:semicolon
id|par-&gt;cmap_adr
op_assign
id|ioremap
c_func
(paren
id|regbase
comma
l_int|0x1FFF
)paren
suffix:semicolon
id|par-&gt;cmap_type
op_assign
id|cmap_M3A
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|dp
op_logical_and
op_logical_neg
id|strncmp
c_func
(paren
id|name
comma
l_string|&quot;ATY,RageM3pB&quot;
comma
l_int|12
)paren
)paren
(brace
r_int
r_int
id|regbase
op_assign
id|dp-&gt;parent-&gt;addrs
(braket
l_int|2
)braket
dot
id|address
suffix:semicolon
id|par-&gt;cmap_adr
op_assign
id|ioremap
c_func
(paren
id|regbase
comma
l_int|0x1FFF
)paren
suffix:semicolon
id|par-&gt;cmap_type
op_assign
id|cmap_M3B
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|dp
op_logical_and
op_logical_neg
id|strncmp
c_func
(paren
id|name
comma
l_string|&quot;ATY,Rage6&quot;
comma
l_int|9
)paren
)paren
(brace
r_int
r_int
id|regbase
op_assign
id|dp-&gt;addrs
(braket
l_int|1
)braket
dot
id|address
suffix:semicolon
id|par-&gt;cmap_adr
op_assign
id|ioremap
c_func
(paren
id|regbase
comma
l_int|0x1FFF
)paren
suffix:semicolon
id|par-&gt;cmap_type
op_assign
id|cmap_radeon
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
id|name
comma
l_string|&quot;ATY,&quot;
comma
l_int|4
)paren
)paren
(brace
r_int
r_int
id|base
op_assign
id|address
op_amp
l_int|0xff000000UL
suffix:semicolon
id|par-&gt;cmap_adr
op_assign
id|ioremap
c_func
(paren
id|base
op_plus
l_int|0x7ff000
comma
l_int|0x1000
)paren
op_plus
l_int|0xcc0
suffix:semicolon
id|par-&gt;cmap_data
op_assign
id|info-&gt;cmap_adr
op_plus
l_int|1
suffix:semicolon
id|par-&gt;cmap_type
op_assign
id|cmap_m64
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|device_is_compatible
c_func
(paren
id|dp
comma
l_string|&quot;pci1014,b7&quot;
)paren
)paren
(brace
r_int
r_int
id|regbase
op_assign
id|dp-&gt;addrs
(braket
l_int|0
)braket
dot
id|address
suffix:semicolon
id|par-&gt;cmap_adr
op_assign
id|ioremap
c_func
(paren
id|regbase
op_plus
l_int|0x6000
comma
l_int|0x1000
)paren
suffix:semicolon
id|par-&gt;cmap_type
op_assign
id|cmap_gxt2000
suffix:semicolon
)brace
id|fix-&gt;visual
op_assign
id|par-&gt;cmap_adr
ques
c_cond
id|FB_VISUAL_PSEUDOCOLOR
suffix:colon
id|FB_VISUAL_STATIC_PSEUDOCOLOR
suffix:semicolon
)brace
r_else
id|fix-&gt;visual
op_assign
multiline_comment|/* par-&gt;cmap_adr ? FB_VISUAL_DIRECTCOLOR&n;&t;&t;&t;&t;   : */
id|FB_VISUAL_TRUECOLOR
suffix:semicolon
id|var-&gt;xoffset
op_assign
id|var-&gt;yoffset
op_assign
l_int|0
suffix:semicolon
id|var-&gt;bits_per_pixel
op_assign
id|depth
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
id|var-&gt;bits_per_pixel
op_assign
l_int|8
suffix:semicolon
id|var-&gt;red.offset
op_assign
l_int|0
suffix:semicolon
id|var-&gt;red.length
op_assign
l_int|8
suffix:semicolon
id|var-&gt;green.offset
op_assign
l_int|0
suffix:semicolon
id|var-&gt;green.length
op_assign
l_int|8
suffix:semicolon
id|var-&gt;blue.offset
op_assign
l_int|0
suffix:semicolon
id|var-&gt;blue.length
op_assign
l_int|8
suffix:semicolon
id|var-&gt;transp.offset
op_assign
l_int|0
suffix:semicolon
id|var-&gt;transp.length
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|16
suffix:colon
multiline_comment|/* RGB 555 */
id|var-&gt;bits_per_pixel
op_assign
l_int|16
suffix:semicolon
id|var-&gt;red.offset
op_assign
l_int|10
suffix:semicolon
id|var-&gt;red.length
op_assign
l_int|5
suffix:semicolon
id|var-&gt;green.offset
op_assign
l_int|5
suffix:semicolon
id|var-&gt;green.length
op_assign
l_int|5
suffix:semicolon
id|var-&gt;blue.offset
op_assign
l_int|0
suffix:semicolon
id|var-&gt;blue.length
op_assign
l_int|5
suffix:semicolon
id|var-&gt;transp.offset
op_assign
l_int|0
suffix:semicolon
id|var-&gt;transp.length
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|32
suffix:colon
multiline_comment|/* RGB 888 */
id|var-&gt;bits_per_pixel
op_assign
l_int|32
suffix:semicolon
id|var-&gt;red.offset
op_assign
l_int|16
suffix:semicolon
id|var-&gt;red.length
op_assign
l_int|8
suffix:semicolon
id|var-&gt;green.offset
op_assign
l_int|8
suffix:semicolon
id|var-&gt;green.length
op_assign
l_int|8
suffix:semicolon
id|var-&gt;blue.offset
op_assign
l_int|0
suffix:semicolon
id|var-&gt;blue.length
op_assign
l_int|8
suffix:semicolon
id|var-&gt;transp.offset
op_assign
l_int|24
suffix:semicolon
id|var-&gt;transp.length
op_assign
l_int|8
suffix:semicolon
r_break
suffix:semicolon
)brace
id|var-&gt;red.msb_right
op_assign
id|var-&gt;green.msb_right
op_assign
id|var-&gt;blue.msb_right
op_assign
id|var-&gt;transp.msb_right
op_assign
l_int|0
suffix:semicolon
id|var-&gt;grayscale
op_assign
l_int|0
suffix:semicolon
id|var-&gt;nonstd
op_assign
l_int|0
suffix:semicolon
id|var-&gt;activate
op_assign
l_int|0
suffix:semicolon
id|var-&gt;height
op_assign
id|var-&gt;width
op_assign
op_minus
l_int|1
suffix:semicolon
id|var-&gt;pixclock
op_assign
l_int|10000
suffix:semicolon
id|var-&gt;left_margin
op_assign
id|var-&gt;right_margin
op_assign
l_int|16
suffix:semicolon
id|var-&gt;upper_margin
op_assign
id|var-&gt;lower_margin
op_assign
l_int|16
suffix:semicolon
id|var-&gt;hsync_len
op_assign
id|var-&gt;vsync_len
op_assign
l_int|8
suffix:semicolon
id|var-&gt;sync
op_assign
l_int|0
suffix:semicolon
id|var-&gt;vmode
op_assign
id|FB_VMODE_NONINTERLACED
suffix:semicolon
id|strcpy
c_func
(paren
id|fix-&gt;id
comma
l_string|&quot;OFfb &quot;
)paren
suffix:semicolon
id|strncat
c_func
(paren
id|fix-&gt;id
comma
id|full_name
comma
r_sizeof
(paren
id|fix-&gt;id
)paren
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|info-&gt;modename
comma
id|fix-&gt;id
)paren
suffix:semicolon
id|info-&gt;node
op_assign
id|NODEV
suffix:semicolon
id|info-&gt;fbops
op_assign
op_amp
id|offb_ops
suffix:semicolon
id|info-&gt;screen_base
op_assign
id|ioremap
c_func
(paren
id|address
comma
id|fix-&gt;smem_len
)paren
suffix:semicolon
id|info-&gt;par
op_assign
id|par
suffix:semicolon
id|info-&gt;disp
op_assign
(paren
r_struct
id|display
op_star
)paren
(paren
id|info
op_plus
l_int|1
)paren
suffix:semicolon
id|info-&gt;pseudo_palette
op_assign
(paren
r_void
op_star
)paren
(paren
id|info-&gt;disp
op_plus
l_int|1
)paren
suffix:semicolon
id|info-&gt;currcon
op_assign
op_minus
l_int|1
suffix:semicolon
id|info-&gt;fontname
(braket
l_int|0
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|info-&gt;changevar
op_assign
l_int|NULL
suffix:semicolon
id|info-&gt;switch_con
op_assign
id|gen_switch
suffix:semicolon
id|info-&gt;updatevar
op_assign
id|gen_update_var
suffix:semicolon
id|info-&gt;flags
op_assign
id|FBINFO_FLAG_DEFAULT
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
id|gen_set_disp
c_func
(paren
op_minus
l_int|1
comma
id|info
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
id|kfree
c_func
(paren
id|info
)paren
suffix:semicolon
id|release_mem_region
c_func
(paren
id|res_start
comma
id|res_size
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;fb%d: Open Firmware frame buffer device on %s&bslash;n&quot;
comma
id|GET_FB_IDX
c_func
(paren
id|info-&gt;info.node
)paren
comma
id|full_name
)paren
suffix:semicolon
)brace
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
