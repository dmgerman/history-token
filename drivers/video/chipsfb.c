multiline_comment|/*&n; *  drivers/video/chipsfb.c -- frame buffer device for&n; *  Chips &amp; Technologies 65550 chip.&n; *&n; *  Copyright (C) 1998-2002 Paul Mackerras&n; *&n; *  This file is derived from the Powermac &quot;chips&quot; driver:&n; *  Copyright (C) 1997 Fabio Riccardi.&n; *  And from the frame buffer device for Open Firmware-initialized devices:&n; *  Copyright (C) 1997 Geert Uytterhoeven.&n; *&n; *  This file is subject to the terms and conditions of the GNU General Public&n; *  License. See the file COPYING in the main directory of this archive for&n; *  more details.&n; */
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
macro_line|#include &lt;asm/io.h&gt;
macro_line|#ifdef CONFIG_PMAC_BACKLIGHT
macro_line|#include &lt;asm/backlight.h&gt;
macro_line|#endif
macro_line|#ifdef CONFIG_PMAC_PBOOK
macro_line|#include &lt;linux/adb.h&gt;
macro_line|#include &lt;linux/pmu.h&gt;
macro_line|#endif
multiline_comment|/*&n; * Since we access the display with inb/outb to fixed port numbers,&n; * we can only handle one 6555x chip.  -- paulus&n; */
DECL|variable|chipsfb_info
r_static
r_struct
id|fb_info
id|chipsfb_info
suffix:semicolon
DECL|macro|write_ind
mdefine_line|#define write_ind(num, val, ap, dp)&t;do { &bslash;&n;&t;outb((num), (ap)); outb((val), (dp)); &bslash;&n;} while (0)
DECL|macro|read_ind
mdefine_line|#define read_ind(num, var, ap, dp)&t;do { &bslash;&n;&t;outb((num), (ap)); var = inb((dp)); &bslash;&n;} while (0)
multiline_comment|/* extension registers */
DECL|macro|write_xr
mdefine_line|#define write_xr(num, val)&t;write_ind(num, val, 0x3d6, 0x3d7)
DECL|macro|read_xr
mdefine_line|#define read_xr(num, var)&t;read_ind(num, var, 0x3d6, 0x3d7)
multiline_comment|/* flat panel registers */
DECL|macro|write_fr
mdefine_line|#define write_fr(num, val)&t;write_ind(num, val, 0x3d0, 0x3d1)
DECL|macro|read_fr
mdefine_line|#define read_fr(num, var)&t;read_ind(num, var, 0x3d0, 0x3d1)
multiline_comment|/* CRTC registers */
DECL|macro|write_cr
mdefine_line|#define write_cr(num, val)&t;write_ind(num, val, 0x3d4, 0x3d5)
DECL|macro|read_cr
mdefine_line|#define read_cr(num, var)&t;read_ind(num, var, 0x3d4, 0x3d5)
multiline_comment|/* graphics registers */
DECL|macro|write_gr
mdefine_line|#define write_gr(num, val)&t;write_ind(num, val, 0x3ce, 0x3cf)
DECL|macro|read_gr
mdefine_line|#define read_gr(num, var)&t;read_ind(num, var, 0x3ce, 0x3cf)
multiline_comment|/* sequencer registers */
DECL|macro|write_sr
mdefine_line|#define write_sr(num, val)&t;write_ind(num, val, 0x3c4, 0x3c5)
DECL|macro|read_sr
mdefine_line|#define read_sr(num, var)&t;read_ind(num, var, 0x3c4, 0x3c5)
multiline_comment|/* attribute registers - slightly strange */
DECL|macro|write_ar
mdefine_line|#define write_ar(num, val)&t;do { &bslash;&n;&t;inb(0x3da); write_ind(num, val, 0x3c0, 0x3c0); &bslash;&n;} while (0)
DECL|macro|read_ar
mdefine_line|#define read_ar(num, var)&t;do { &bslash;&n;&t;inb(0x3da); read_ind(num, var, 0x3c0, 0x3c1); &bslash;&n;} while (0)
macro_line|#ifdef CONFIG_PMAC_PBOOK
DECL|variable|save_framebuffer
r_static
r_int
r_char
op_star
id|save_framebuffer
suffix:semicolon
r_int
id|chips_sleep_notify
c_func
(paren
r_struct
id|pmu_sleep_notifier
op_star
id|self
comma
r_int
id|when
)paren
suffix:semicolon
DECL|variable|chips_sleep_notifier
r_static
r_struct
id|pmu_sleep_notifier
id|chips_sleep_notifier
op_assign
(brace
id|chips_sleep_notify
comma
id|SLEEP_LEVEL_VIDEO
comma
)brace
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Exported functions&n; */
r_int
id|chips_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_int
id|chipsfb_pci_init
c_func
(paren
r_struct
id|pci_dev
op_star
id|dp
comma
r_const
r_struct
id|pci_device_id
op_star
)paren
suffix:semicolon
r_static
r_int
id|chipsfb_check_var
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
id|chipsfb_set_par
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
id|chipsfb_setcolreg
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
id|chipsfb_blank
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
DECL|variable|chipsfb_ops
r_static
r_struct
id|fb_ops
id|chipsfb_ops
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
id|chipsfb_check_var
comma
dot
id|fb_set_par
op_assign
id|chipsfb_set_par
comma
dot
id|fb_setcolreg
op_assign
id|chipsfb_setcolreg
comma
dot
id|fb_blank
op_assign
id|chipsfb_blank
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
DECL|function|chipsfb_check_var
r_static
r_int
id|chipsfb_check_var
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
r_if
c_cond
(paren
id|var-&gt;xres
OG
l_int|800
op_logical_or
id|var-&gt;yres
OG
l_int|600
op_logical_or
id|var-&gt;xres_virtual
OG
l_int|800
op_logical_or
id|var-&gt;yres_virtual
OG
l_int|600
op_logical_or
(paren
id|var-&gt;bits_per_pixel
op_ne
l_int|8
op_logical_and
id|var-&gt;bits_per_pixel
op_ne
l_int|16
)paren
op_logical_or
id|var-&gt;nonstd
op_logical_or
(paren
id|var-&gt;vmode
op_amp
id|FB_VMODE_MASK
)paren
op_ne
id|FB_VMODE_NONINTERLACED
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|var-&gt;xres
op_assign
id|var-&gt;xres_virtual
op_assign
l_int|800
suffix:semicolon
id|var-&gt;yres
op_assign
id|var-&gt;yres_virtual
op_assign
l_int|600
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|chipsfb_set_par
r_static
r_int
id|chipsfb_set_par
c_func
(paren
r_struct
id|fb_info
op_star
id|info
)paren
(brace
r_if
c_cond
(paren
id|info-&gt;var.bits_per_pixel
op_eq
l_int|16
)paren
(brace
id|write_cr
c_func
(paren
l_int|0x13
comma
l_int|200
)paren
suffix:semicolon
singleline_comment|// Set line length (doublewords)
id|write_xr
c_func
(paren
l_int|0x81
comma
l_int|0x14
)paren
suffix:semicolon
singleline_comment|// 15 bit (555) color mode
id|write_xr
c_func
(paren
l_int|0x82
comma
l_int|0x00
)paren
suffix:semicolon
singleline_comment|// Disable palettes
id|write_xr
c_func
(paren
l_int|0x20
comma
l_int|0x10
)paren
suffix:semicolon
singleline_comment|// 16 bit blitter mode
id|info-&gt;fix.line_length
op_assign
l_int|800
op_star
l_int|2
suffix:semicolon
id|info-&gt;fix.visual
op_assign
id|FB_VISUAL_TRUECOLOR
suffix:semicolon
id|info-&gt;var.red.offset
op_assign
l_int|10
suffix:semicolon
id|info-&gt;var.green.offset
op_assign
l_int|5
suffix:semicolon
id|info-&gt;var.blue.offset
op_assign
l_int|0
suffix:semicolon
id|info-&gt;var.red.length
op_assign
id|info-&gt;var.green.length
op_assign
id|info-&gt;var.blue.length
op_assign
l_int|5
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* p-&gt;var.bits_per_pixel == 8 */
id|write_cr
c_func
(paren
l_int|0x13
comma
l_int|100
)paren
suffix:semicolon
singleline_comment|// Set line length (doublewords)
id|write_xr
c_func
(paren
l_int|0x81
comma
l_int|0x12
)paren
suffix:semicolon
singleline_comment|// 8 bit color mode
id|write_xr
c_func
(paren
l_int|0x82
comma
l_int|0x08
)paren
suffix:semicolon
singleline_comment|// Graphics gamma enable
id|write_xr
c_func
(paren
l_int|0x20
comma
l_int|0x00
)paren
suffix:semicolon
singleline_comment|// 8 bit blitter mode
id|info-&gt;fix.line_length
op_assign
l_int|800
suffix:semicolon
id|info-&gt;fix.visual
op_assign
id|FB_VISUAL_PSEUDOCOLOR
suffix:semicolon
id|info-&gt;var.red.offset
op_assign
id|info-&gt;var.green.offset
op_assign
id|info-&gt;var.blue.offset
op_assign
l_int|0
suffix:semicolon
id|info-&gt;var.red.length
op_assign
id|info-&gt;var.green.length
op_assign
id|info-&gt;var.blue.length
op_assign
l_int|8
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|chipsfb_blank
r_static
r_int
id|chipsfb_blank
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
macro_line|#ifdef CONFIG_PMAC_BACKLIGHT
singleline_comment|// used to disable backlight only for blank &gt; 1, but it seems
singleline_comment|// useful at blank = 1 too (saves battery, extends backlight life)
id|set_backlight_enable
c_func
(paren
op_logical_neg
id|blank
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_PMAC_BACKLIGHT */
r_return
l_int|1
suffix:semicolon
multiline_comment|/* get fb_blank to set the colormap to all black */
)brace
DECL|function|chipsfb_setcolreg
r_static
r_int
id|chipsfb_setcolreg
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
id|outb
c_func
(paren
id|regno
comma
l_int|0x3c8
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|outb
c_func
(paren
id|red
comma
l_int|0x3c9
)paren
suffix:semicolon
id|outb
c_func
(paren
id|green
comma
l_int|0x3c9
)paren
suffix:semicolon
id|outb
c_func
(paren
id|blue
comma
l_int|0x3c9
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|struct|chips_init_reg
r_struct
id|chips_init_reg
(brace
DECL|member|addr
r_int
r_char
id|addr
suffix:semicolon
DECL|member|data
r_int
r_char
id|data
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|N_ELTS
mdefine_line|#define N_ELTS(x)&t;(sizeof(x) / sizeof(x[0]))
DECL|variable|chips_init_sr
r_static
r_struct
id|chips_init_reg
id|chips_init_sr
(braket
)braket
op_assign
(brace
(brace
l_int|0x00
comma
l_int|0x03
)brace
comma
(brace
l_int|0x01
comma
l_int|0x01
)brace
comma
(brace
l_int|0x02
comma
l_int|0x0f
)brace
comma
(brace
l_int|0x04
comma
l_int|0x0e
)brace
)brace
suffix:semicolon
DECL|variable|chips_init_gr
r_static
r_struct
id|chips_init_reg
id|chips_init_gr
(braket
)braket
op_assign
(brace
(brace
l_int|0x05
comma
l_int|0x00
)brace
comma
(brace
l_int|0x06
comma
l_int|0x0d
)brace
comma
(brace
l_int|0x08
comma
l_int|0xff
)brace
)brace
suffix:semicolon
DECL|variable|chips_init_ar
r_static
r_struct
id|chips_init_reg
id|chips_init_ar
(braket
)braket
op_assign
(brace
(brace
l_int|0x10
comma
l_int|0x01
)brace
comma
(brace
l_int|0x12
comma
l_int|0x0f
)brace
comma
(brace
l_int|0x13
comma
l_int|0x00
)brace
)brace
suffix:semicolon
DECL|variable|chips_init_cr
r_static
r_struct
id|chips_init_reg
id|chips_init_cr
(braket
)braket
op_assign
(brace
(brace
l_int|0x00
comma
l_int|0x7f
)brace
comma
(brace
l_int|0x01
comma
l_int|0x63
)brace
comma
(brace
l_int|0x02
comma
l_int|0x63
)brace
comma
(brace
l_int|0x03
comma
l_int|0x83
)brace
comma
(brace
l_int|0x04
comma
l_int|0x66
)brace
comma
(brace
l_int|0x05
comma
l_int|0x10
)brace
comma
(brace
l_int|0x06
comma
l_int|0x72
)brace
comma
(brace
l_int|0x07
comma
l_int|0x3e
)brace
comma
(brace
l_int|0x08
comma
l_int|0x00
)brace
comma
(brace
l_int|0x09
comma
l_int|0x40
)brace
comma
(brace
l_int|0x0c
comma
l_int|0x00
)brace
comma
(brace
l_int|0x0d
comma
l_int|0x00
)brace
comma
(brace
l_int|0x10
comma
l_int|0x59
)brace
comma
(brace
l_int|0x11
comma
l_int|0x0d
)brace
comma
(brace
l_int|0x12
comma
l_int|0x57
)brace
comma
(brace
l_int|0x13
comma
l_int|0x64
)brace
comma
(brace
l_int|0x14
comma
l_int|0x00
)brace
comma
(brace
l_int|0x15
comma
l_int|0x57
)brace
comma
(brace
l_int|0x16
comma
l_int|0x73
)brace
comma
(brace
l_int|0x17
comma
l_int|0xe3
)brace
comma
(brace
l_int|0x18
comma
l_int|0xff
)brace
comma
(brace
l_int|0x30
comma
l_int|0x02
)brace
comma
(brace
l_int|0x31
comma
l_int|0x02
)brace
comma
(brace
l_int|0x32
comma
l_int|0x02
)brace
comma
(brace
l_int|0x33
comma
l_int|0x02
)brace
comma
(brace
l_int|0x40
comma
l_int|0x00
)brace
comma
(brace
l_int|0x41
comma
l_int|0x00
)brace
comma
(brace
l_int|0x40
comma
l_int|0x80
)brace
)brace
suffix:semicolon
DECL|variable|chips_init_fr
r_static
r_struct
id|chips_init_reg
id|chips_init_fr
(braket
)braket
op_assign
(brace
(brace
l_int|0x01
comma
l_int|0x02
)brace
comma
(brace
l_int|0x03
comma
l_int|0x08
)brace
comma
(brace
l_int|0x04
comma
l_int|0x81
)brace
comma
(brace
l_int|0x05
comma
l_int|0x21
)brace
comma
(brace
l_int|0x08
comma
l_int|0x0c
)brace
comma
(brace
l_int|0x0a
comma
l_int|0x74
)brace
comma
(brace
l_int|0x0b
comma
l_int|0x11
)brace
comma
(brace
l_int|0x10
comma
l_int|0x0c
)brace
comma
(brace
l_int|0x11
comma
l_int|0xe0
)brace
comma
multiline_comment|/* { 0x12, 0x40 }, -- 3400 needs 40, 2400 needs 48, no way to tell */
(brace
l_int|0x20
comma
l_int|0x63
)brace
comma
(brace
l_int|0x21
comma
l_int|0x68
)brace
comma
(brace
l_int|0x22
comma
l_int|0x19
)brace
comma
(brace
l_int|0x23
comma
l_int|0x7f
)brace
comma
(brace
l_int|0x24
comma
l_int|0x68
)brace
comma
(brace
l_int|0x26
comma
l_int|0x00
)brace
comma
(brace
l_int|0x27
comma
l_int|0x0f
)brace
comma
(brace
l_int|0x30
comma
l_int|0x57
)brace
comma
(brace
l_int|0x31
comma
l_int|0x58
)brace
comma
(brace
l_int|0x32
comma
l_int|0x0d
)brace
comma
(brace
l_int|0x33
comma
l_int|0x72
)brace
comma
(brace
l_int|0x34
comma
l_int|0x02
)brace
comma
(brace
l_int|0x35
comma
l_int|0x22
)brace
comma
(brace
l_int|0x36
comma
l_int|0x02
)brace
comma
(brace
l_int|0x37
comma
l_int|0x00
)brace
)brace
suffix:semicolon
DECL|variable|chips_init_xr
r_static
r_struct
id|chips_init_reg
id|chips_init_xr
(braket
)braket
op_assign
(brace
(brace
l_int|0xce
comma
l_int|0x00
)brace
comma
multiline_comment|/* set default memory clock */
(brace
l_int|0xcc
comma
l_int|0x43
)brace
comma
multiline_comment|/* memory clock ratio */
(brace
l_int|0xcd
comma
l_int|0x18
)brace
comma
(brace
l_int|0xce
comma
l_int|0xa1
)brace
comma
(brace
l_int|0xc8
comma
l_int|0x84
)brace
comma
(brace
l_int|0xc9
comma
l_int|0x0a
)brace
comma
(brace
l_int|0xca
comma
l_int|0x00
)brace
comma
(brace
l_int|0xcb
comma
l_int|0x20
)brace
comma
(brace
l_int|0xcf
comma
l_int|0x06
)brace
comma
(brace
l_int|0xd0
comma
l_int|0x0e
)brace
comma
(brace
l_int|0x09
comma
l_int|0x01
)brace
comma
(brace
l_int|0x0a
comma
l_int|0x02
)brace
comma
(brace
l_int|0x0b
comma
l_int|0x01
)brace
comma
(brace
l_int|0x20
comma
l_int|0x00
)brace
comma
(brace
l_int|0x40
comma
l_int|0x03
)brace
comma
(brace
l_int|0x41
comma
l_int|0x01
)brace
comma
(brace
l_int|0x42
comma
l_int|0x00
)brace
comma
(brace
l_int|0x80
comma
l_int|0x82
)brace
comma
(brace
l_int|0x81
comma
l_int|0x12
)brace
comma
(brace
l_int|0x82
comma
l_int|0x08
)brace
comma
(brace
l_int|0xa0
comma
l_int|0x00
)brace
comma
(brace
l_int|0xa8
comma
l_int|0x00
)brace
)brace
suffix:semicolon
DECL|function|chips_hw_init
r_static
r_void
id|__init
id|chips_hw_init
c_func
(paren
r_void
)paren
(brace
r_int
id|i
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
id|N_ELTS
c_func
(paren
id|chips_init_xr
)paren
suffix:semicolon
op_increment
id|i
)paren
id|write_xr
c_func
(paren
id|chips_init_xr
(braket
id|i
)braket
dot
id|addr
comma
id|chips_init_xr
(braket
id|i
)braket
dot
id|data
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x29
comma
l_int|0x3c2
)paren
suffix:semicolon
multiline_comment|/* set misc output reg */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|N_ELTS
c_func
(paren
id|chips_init_sr
)paren
suffix:semicolon
op_increment
id|i
)paren
id|write_sr
c_func
(paren
id|chips_init_sr
(braket
id|i
)braket
dot
id|addr
comma
id|chips_init_sr
(braket
id|i
)braket
dot
id|data
)paren
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
id|N_ELTS
c_func
(paren
id|chips_init_gr
)paren
suffix:semicolon
op_increment
id|i
)paren
id|write_gr
c_func
(paren
id|chips_init_gr
(braket
id|i
)braket
dot
id|addr
comma
id|chips_init_gr
(braket
id|i
)braket
dot
id|data
)paren
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
id|N_ELTS
c_func
(paren
id|chips_init_ar
)paren
suffix:semicolon
op_increment
id|i
)paren
id|write_ar
c_func
(paren
id|chips_init_ar
(braket
id|i
)braket
dot
id|addr
comma
id|chips_init_ar
(braket
id|i
)braket
dot
id|data
)paren
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
id|N_ELTS
c_func
(paren
id|chips_init_cr
)paren
suffix:semicolon
op_increment
id|i
)paren
id|write_cr
c_func
(paren
id|chips_init_cr
(braket
id|i
)braket
dot
id|addr
comma
id|chips_init_cr
(braket
id|i
)braket
dot
id|data
)paren
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
id|N_ELTS
c_func
(paren
id|chips_init_fr
)paren
suffix:semicolon
op_increment
id|i
)paren
id|write_fr
c_func
(paren
id|chips_init_fr
(braket
id|i
)braket
dot
id|addr
comma
id|chips_init_fr
(braket
id|i
)braket
dot
id|data
)paren
suffix:semicolon
)brace
DECL|variable|__initdata
r_static
r_struct
id|fb_fix_screeninfo
id|chipsfb_fix
id|__initdata
op_assign
(brace
dot
id|id
op_assign
l_string|&quot;C&amp;T 65550&quot;
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
id|accel
op_assign
id|FB_ACCEL_NONE
comma
dot
id|line_length
op_assign
l_int|800
comma
singleline_comment|// FIXME: Assumes 1MB frame buffer, but 65550 supports 1MB or 2MB.
singleline_comment|// * &quot;3500&quot; PowerBook G3 (the original PB G3) has 2MB.
singleline_comment|// * 2400 has 1MB composed of 2 Mitsubishi M5M4V4265CTP DRAM chips.
singleline_comment|//   Motherboard actually supports 2MB -- there are two blank locations
singleline_comment|//   for a second pair of DRAMs.  (Thanks, Apple!)
singleline_comment|// * 3400 has 1MB (I think).  Don&squot;t know if it&squot;s expandable.
singleline_comment|// -- Tim Seufert
dot
id|smem_len
op_assign
l_int|0x100000
comma
multiline_comment|/* 1MB */
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
r_struct
id|fb_var_screeninfo
id|chipsfb_var
id|__initdata
op_assign
(brace
dot
id|xres
op_assign
l_int|800
comma
dot
id|yres
op_assign
l_int|600
comma
dot
id|xres_virtual
op_assign
l_int|800
comma
dot
id|yres_virtual
op_assign
l_int|600
comma
dot
id|bits_per_pixel
op_assign
l_int|8
comma
dot
id|red
op_assign
(brace
dot
id|length
op_assign
l_int|8
)brace
comma
dot
id|green
op_assign
(brace
dot
id|length
op_assign
l_int|8
)brace
comma
dot
id|blue
op_assign
(brace
dot
id|length
op_assign
l_int|8
)brace
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
dot
id|pixclock
op_assign
l_int|10000
comma
dot
id|left_margin
op_assign
l_int|16
comma
dot
id|right_margin
op_assign
l_int|16
comma
dot
id|upper_margin
op_assign
l_int|16
comma
dot
id|lower_margin
op_assign
l_int|16
comma
dot
id|hsync_len
op_assign
l_int|8
comma
dot
id|vsync_len
op_assign
l_int|8
comma
)brace
suffix:semicolon
DECL|function|init_chips
r_static
r_void
id|__init
id|init_chips
c_func
(paren
r_struct
id|fb_info
op_star
id|p
comma
r_int
r_int
id|addr
)paren
(brace
id|p-&gt;fix
op_assign
id|chipsfb_fix
suffix:semicolon
id|p-&gt;fix.smem_start
op_assign
id|addr
suffix:semicolon
id|p-&gt;var
op_assign
id|chipsfb_var
suffix:semicolon
id|p-&gt;fbops
op_assign
op_amp
id|chipsfb_ops
suffix:semicolon
id|p-&gt;flags
op_assign
id|FBINFO_DEFAULT
suffix:semicolon
id|fb_alloc_cmap
c_func
(paren
op_amp
id|p-&gt;cmap
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
id|p
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;C&amp;T 65550 framebuffer failed to register&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;fb%d: Chips 65550 frame buffer (%dK RAM detected)&bslash;n&quot;
comma
id|p-&gt;node
comma
id|p-&gt;fix.smem_len
op_div
l_int|1024
)paren
suffix:semicolon
id|chips_hw_init
c_func
(paren
)paren
suffix:semicolon
)brace
r_static
r_int
id|__devinit
DECL|function|chipsfb_pci_init
id|chipsfb_pci_init
c_func
(paren
r_struct
id|pci_dev
op_star
id|dp
comma
r_const
r_struct
id|pci_device_id
op_star
id|ent
)paren
(brace
r_struct
id|fb_info
op_star
id|p
op_assign
op_amp
id|chipsfb_info
suffix:semicolon
r_int
r_int
id|addr
comma
id|size
suffix:semicolon
r_int
r_int
id|cmd
suffix:semicolon
r_if
c_cond
(paren
(paren
id|dp-&gt;resource
(braket
l_int|0
)braket
dot
id|flags
op_amp
id|IORESOURCE_MEM
)paren
op_eq
l_int|0
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|addr
op_assign
id|pci_resource_start
c_func
(paren
id|dp
comma
l_int|0
)paren
suffix:semicolon
id|size
op_assign
id|pci_resource_len
c_func
(paren
id|dp
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|addr
op_eq
l_int|0
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;screen_base
op_ne
l_int|0
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
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
l_string|&quot;chipsfb&quot;
)paren
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
macro_line|#ifdef __BIG_ENDIAN
id|addr
op_add_assign
l_int|0x800000
suffix:semicolon
singleline_comment|// Use big-endian aperture
macro_line|#endif
multiline_comment|/* we should use pci_enable_device here, but,&n;&t;   the device doesn&squot;t declare its I/O ports in its BARs&n;&t;   so pci_enable_device won&squot;t turn on I/O responses */
id|pci_read_config_word
c_func
(paren
id|dp
comma
id|PCI_COMMAND
comma
op_amp
id|cmd
)paren
suffix:semicolon
id|cmd
op_or_assign
l_int|3
suffix:semicolon
multiline_comment|/* enable memory and IO space */
id|pci_write_config_word
c_func
(paren
id|dp
comma
id|PCI_COMMAND
comma
id|cmd
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PMAC_BACKLIGHT
multiline_comment|/* turn on the backlight */
id|set_backlight_enable
c_func
(paren
l_int|1
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_PMAC_BACKLIGHT */
id|p-&gt;screen_base
op_assign
id|__ioremap
c_func
(paren
id|addr
comma
l_int|0x200000
comma
id|_PAGE_NO_CACHE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;screen_base
op_eq
l_int|NULL
)paren
(brace
id|release_mem_region
c_func
(paren
id|addr
comma
id|size
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|p-&gt;device
op_assign
op_amp
id|dp-&gt;dev
suffix:semicolon
id|init_chips
c_func
(paren
id|p
comma
id|addr
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PMAC_PBOOK
id|pmu_register_sleep_notifier
c_func
(paren
op_amp
id|chips_sleep_notifier
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_PMAC_PBOOK */
multiline_comment|/* Clear the entire framebuffer */
id|memset
c_func
(paren
id|p-&gt;screen_base
comma
l_int|0
comma
l_int|0x100000
)paren
suffix:semicolon
id|pci_set_drvdata
c_func
(paren
id|dp
comma
id|p
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|chipsfb_remove
r_static
r_void
id|__devexit
id|chipsfb_remove
c_func
(paren
r_struct
id|pci_dev
op_star
id|dp
)paren
(brace
r_struct
id|fb_info
op_star
id|p
op_assign
id|pci_get_drvdata
c_func
(paren
id|dp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p
op_ne
op_amp
id|chipsfb_info
op_logical_or
id|p-&gt;screen_base
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
id|unregister_framebuffer
c_func
(paren
id|p
)paren
suffix:semicolon
id|iounmap
c_func
(paren
id|p-&gt;screen_base
)paren
suffix:semicolon
id|p-&gt;screen_base
op_assign
l_int|NULL
suffix:semicolon
id|release_mem_region
c_func
(paren
id|pci_resource_start
c_func
(paren
id|dp
comma
l_int|0
)paren
comma
id|pci_resource_len
c_func
(paren
id|dp
comma
l_int|0
)paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PMAC_PBOOK
id|pmu_unregister_sleep_notifier
c_func
(paren
op_amp
id|chips_sleep_notifier
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_PMAC_PBOOK */
)brace
DECL|variable|chipsfb_pci_tbl
r_static
r_struct
id|pci_device_id
id|chipsfb_pci_tbl
(braket
)braket
op_assign
(brace
(brace
id|PCI_VENDOR_ID_CT
comma
id|PCI_DEVICE_ID_CT_65550
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
)brace
comma
(brace
l_int|0
)brace
)brace
suffix:semicolon
id|MODULE_DEVICE_TABLE
c_func
(paren
id|pci
comma
id|chipsfb_pci_tbl
)paren
suffix:semicolon
DECL|variable|chipsfb_driver
r_static
r_struct
id|pci_driver
id|chipsfb_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;chipsfb&quot;
comma
dot
id|id_table
op_assign
id|chipsfb_pci_tbl
comma
dot
id|probe
op_assign
id|chipsfb_pci_init
comma
dot
id|remove
op_assign
id|__devexit_p
c_func
(paren
id|chipsfb_remove
)paren
comma
)brace
suffix:semicolon
DECL|function|chips_init
r_int
id|__init
id|chips_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|fb_get_options
c_func
(paren
l_string|&quot;chipsfb&quot;
comma
l_int|NULL
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_return
id|pci_register_driver
c_func
(paren
op_amp
id|chipsfb_driver
)paren
suffix:semicolon
)brace
DECL|variable|chips_init
id|module_init
c_func
(paren
id|chips_init
)paren
suffix:semicolon
DECL|function|chipsfb_exit
r_static
r_void
id|__exit
id|chipsfb_exit
c_func
(paren
r_void
)paren
(brace
id|pci_unregister_driver
c_func
(paren
op_amp
id|chipsfb_driver
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_PMAC_PBOOK
multiline_comment|/*&n; * Save the contents of the frame buffer when we go to sleep,&n; * and restore it when we wake up again.&n; */
r_int
DECL|function|chips_sleep_notify
id|chips_sleep_notify
c_func
(paren
r_struct
id|pmu_sleep_notifier
op_star
id|self
comma
r_int
id|when
)paren
(brace
r_struct
id|fb_info
op_star
id|p
op_assign
op_amp
id|chipsfb_info
suffix:semicolon
r_int
id|nb
op_assign
id|p-&gt;var.yres
op_star
id|p-&gt;fix.line_length
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;screen_base
op_eq
l_int|NULL
)paren
r_return
id|PBOOK_SLEEP_OK
suffix:semicolon
r_switch
c_cond
(paren
id|when
)paren
(brace
r_case
id|PBOOK_SLEEP_REQUEST
suffix:colon
id|save_framebuffer
op_assign
id|vmalloc
c_func
(paren
id|nb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|save_framebuffer
op_eq
l_int|NULL
)paren
r_return
id|PBOOK_SLEEP_REFUSE
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PBOOK_SLEEP_REJECT
suffix:colon
r_if
c_cond
(paren
id|save_framebuffer
)paren
(brace
id|vfree
c_func
(paren
id|save_framebuffer
)paren
suffix:semicolon
id|save_framebuffer
op_assign
l_int|NULL
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|PBOOK_SLEEP_NOW
suffix:colon
id|chipsfb_blank
c_func
(paren
l_int|1
comma
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
id|save_framebuffer
)paren
id|memcpy
c_func
(paren
id|save_framebuffer
comma
id|p-&gt;screen_base
comma
id|nb
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PBOOK_WAKE
suffix:colon
r_if
c_cond
(paren
id|save_framebuffer
)paren
(brace
id|memcpy
c_func
(paren
id|p-&gt;screen_base
comma
id|save_framebuffer
comma
id|nb
)paren
suffix:semicolon
id|vfree
c_func
(paren
id|save_framebuffer
)paren
suffix:semicolon
id|save_framebuffer
op_assign
l_int|NULL
suffix:semicolon
)brace
id|chipsfb_blank
c_func
(paren
l_int|0
comma
id|p
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|PBOOK_SLEEP_OK
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_PMAC_PBOOK */
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
