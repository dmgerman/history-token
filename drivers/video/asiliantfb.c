multiline_comment|/*&n; * drivers/video/asiliantfb.c&n; *  frame buffer driver for Asiliant 69000 chip&n; *  Copyright (C) 2001-2003 Saito.K &amp; Jeanne&n; *&n; *  from driver/video/chipsfb.c and,&n; *&n; *  drivers/video/asiliantfb.c -- frame buffer device for&n; *  Asiliant 69030 chip (formerly Intel, formerly Chips &amp; Technologies)&n; *  Author: apc@agelectronics.co.uk&n; *  Copyright (C) 2000 AG Electronics&n; *  Note: the data sheets don&squot;t seem to be available from Asiliant.&n; *  They are available by searching developer.intel.com, but are not otherwise&n; *  linked to.&n; *&n; *  This driver should be portable with minimal effort to the 69000 display&n; *  chip, and to the twin-display mode of the 69030.&n; *  Contains code from Thomas Hhenleitner &lt;th@visuelle-maschinen.de&gt; (thanks)&n; *&n; *  Derived from the CT65550 driver chipsfb.c:&n; *  Copyright (C) 1998 Paul Mackerras&n; *  ...which was derived from the Powermac &quot;chips&quot; driver:&n; *  Copyright (C) 1997 Fabio Riccardi.&n; *  And from the frame buffer device for Open Firmware-initialized devices:&n; *  Copyright (C) 1997 Geert Uytterhoeven.&n; *&n; *  This file is subject to the terms and conditions of the GNU General Public&n; *  License. See the file COPYING in the main directory of this archive for&n; *  more details.&n; */
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
multiline_comment|/* Built in clock of the 69030 */
DECL|variable|Fref
r_const
r_int
id|Fref
op_assign
l_int|14318180
suffix:semicolon
DECL|macro|mmio_base
mdefine_line|#define mmio_base (p-&gt;screen_base + 0x400000)
DECL|macro|mm_write_ind
mdefine_line|#define mm_write_ind(num, val, ap, dp)&t;do { &bslash;&n;&t;writeb((num), mmio_base + (ap)); writeb((val), mmio_base + (dp)); &bslash;&n;} while (0)
DECL|function|mm_write_xr
r_static
r_void
id|mm_write_xr
c_func
(paren
r_struct
id|fb_info
op_star
id|p
comma
id|u8
id|reg
comma
id|u8
id|data
)paren
(brace
id|mm_write_ind
c_func
(paren
id|reg
comma
id|data
comma
l_int|0x7ac
comma
l_int|0x7ad
)paren
suffix:semicolon
)brace
DECL|macro|write_xr
mdefine_line|#define write_xr(num, val)&t;mm_write_xr(p, num, val)
DECL|function|mm_write_fr
r_static
r_void
id|mm_write_fr
c_func
(paren
r_struct
id|fb_info
op_star
id|p
comma
id|u8
id|reg
comma
id|u8
id|data
)paren
(brace
id|mm_write_ind
c_func
(paren
id|reg
comma
id|data
comma
l_int|0x7a0
comma
l_int|0x7a1
)paren
suffix:semicolon
)brace
DECL|macro|write_fr
mdefine_line|#define write_fr(num, val)&t;mm_write_fr(p, num, val)
DECL|function|mm_write_cr
r_static
r_void
id|mm_write_cr
c_func
(paren
r_struct
id|fb_info
op_star
id|p
comma
id|u8
id|reg
comma
id|u8
id|data
)paren
(brace
id|mm_write_ind
c_func
(paren
id|reg
comma
id|data
comma
l_int|0x7a8
comma
l_int|0x7a9
)paren
suffix:semicolon
)brace
DECL|macro|write_cr
mdefine_line|#define write_cr(num, val)&t;mm_write_cr(p, num, val)
DECL|function|mm_write_gr
r_static
r_void
id|mm_write_gr
c_func
(paren
r_struct
id|fb_info
op_star
id|p
comma
id|u8
id|reg
comma
id|u8
id|data
)paren
(brace
id|mm_write_ind
c_func
(paren
id|reg
comma
id|data
comma
l_int|0x79c
comma
l_int|0x79d
)paren
suffix:semicolon
)brace
DECL|macro|write_gr
mdefine_line|#define write_gr(num, val)&t;mm_write_gr(p, num, val)
DECL|function|mm_write_sr
r_static
r_void
id|mm_write_sr
c_func
(paren
r_struct
id|fb_info
op_star
id|p
comma
id|u8
id|reg
comma
id|u8
id|data
)paren
(brace
id|mm_write_ind
c_func
(paren
id|reg
comma
id|data
comma
l_int|0x788
comma
l_int|0x789
)paren
suffix:semicolon
)brace
DECL|macro|write_sr
mdefine_line|#define write_sr(num, val)&t;mm_write_sr(p, num, val)
DECL|function|mm_write_ar
r_static
r_void
id|mm_write_ar
c_func
(paren
r_struct
id|fb_info
op_star
id|p
comma
id|u8
id|reg
comma
id|u8
id|data
)paren
(brace
id|readb
c_func
(paren
id|mmio_base
op_plus
l_int|0x7b4
)paren
suffix:semicolon
id|mm_write_ind
c_func
(paren
id|reg
comma
id|data
comma
l_int|0x780
comma
l_int|0x780
)paren
suffix:semicolon
)brace
DECL|macro|write_ar
mdefine_line|#define write_ar(num, val)&t;mm_write_ar(p, num, val)
multiline_comment|/*&n; * Exported functions&n; */
r_int
id|asiliantfb_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_int
id|asiliantfb_pci_init
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
id|asiliantfb_check_var
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
id|asiliantfb_set_par
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
id|asiliantfb_setcolreg
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
DECL|variable|asiliantfb_ops
r_static
r_struct
id|fb_ops
id|asiliantfb_ops
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
id|asiliantfb_check_var
comma
dot
id|fb_set_par
op_assign
id|asiliantfb_set_par
comma
dot
id|fb_setcolreg
op_assign
id|asiliantfb_setcolreg
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
multiline_comment|/* Calculate the ratios for the dot clocks without using a single long long&n; * value */
DECL|function|asiliant_calc_dclk2
r_static
r_void
id|asiliant_calc_dclk2
c_func
(paren
id|u32
op_star
id|ppixclock
comma
id|u8
op_star
id|dclk2_m
comma
id|u8
op_star
id|dclk2_n
comma
id|u8
op_star
id|dclk2_div
)paren
(brace
r_int
id|pixclock
op_assign
op_star
id|ppixclock
suffix:semicolon
r_int
id|Ftarget
op_assign
l_int|1000000
op_star
(paren
l_int|1000000
op_div
id|pixclock
)paren
suffix:semicolon
r_int
id|n
suffix:semicolon
r_int
id|best_error
op_assign
l_int|0xffffffff
suffix:semicolon
r_int
id|best_m
op_assign
l_int|0xffffffff
comma
id|best_n
op_assign
l_int|0xffffffff
suffix:semicolon
r_int
id|ratio
suffix:semicolon
r_int
id|remainder
suffix:semicolon
r_int
r_char
id|divisor
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Calculate the frequency required. This is hard enough. */
id|ratio
op_assign
l_int|1000000
op_div
id|pixclock
suffix:semicolon
id|remainder
op_assign
l_int|1000000
op_mod
id|pixclock
suffix:semicolon
id|Ftarget
op_assign
l_int|1000000
op_star
id|ratio
op_plus
(paren
l_int|1000000
op_star
id|remainder
)paren
op_div
id|pixclock
suffix:semicolon
r_while
c_loop
(paren
id|Ftarget
OL
l_int|100000000
)paren
(brace
id|divisor
op_add_assign
l_int|0x10
suffix:semicolon
id|Ftarget
op_lshift_assign
l_int|1
suffix:semicolon
)brace
id|ratio
op_assign
id|Ftarget
op_div
id|Fref
suffix:semicolon
id|remainder
op_assign
id|Ftarget
op_mod
id|Fref
suffix:semicolon
multiline_comment|/* This expresses the constraint that 150kHz &lt;= Fref/n &lt;= 5Mhz,&n;&t; * together with 3 &lt;= n &lt;= 257. */
r_for
c_loop
(paren
id|n
op_assign
l_int|3
suffix:semicolon
id|n
op_le
l_int|257
suffix:semicolon
id|n
op_increment
)paren
(brace
r_int
id|m
op_assign
id|n
op_star
id|ratio
op_plus
(paren
id|n
op_star
id|remainder
)paren
op_div
id|Fref
suffix:semicolon
multiline_comment|/* 3 &lt;= m &lt;= 257 */
r_if
c_cond
(paren
id|m
op_ge
l_int|3
op_logical_and
id|m
op_le
l_int|257
)paren
(brace
r_int
id|new_error
op_assign
(paren
(paren
id|Ftarget
op_star
id|n
)paren
op_minus
(paren
id|Fref
op_star
id|m
)paren
)paren
op_ge
l_int|0
ques
c_cond
(paren
(paren
id|Ftarget
op_star
id|n
)paren
op_minus
(paren
id|Fref
op_star
id|m
)paren
)paren
suffix:colon
(paren
(paren
id|Fref
op_star
id|m
)paren
op_minus
(paren
id|Ftarget
op_star
id|n
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|new_error
OL
id|best_error
)paren
(brace
id|best_n
op_assign
id|n
suffix:semicolon
id|best_m
op_assign
id|m
suffix:semicolon
id|best_error
op_assign
id|new_error
suffix:semicolon
)brace
)brace
multiline_comment|/* But if VLD = 4, then 4m &lt;= 1028 */
r_else
r_if
c_cond
(paren
id|m
op_le
l_int|1028
)paren
(brace
multiline_comment|/* remember there are still only 8-bits of precision in m, so&n;&t;&t;&t; * avoid over-optimistic error calculations */
r_int
id|new_error
op_assign
(paren
(paren
id|Ftarget
op_star
id|n
)paren
op_minus
(paren
id|Fref
op_star
(paren
id|m
op_amp
op_complement
l_int|3
)paren
)paren
)paren
op_ge
l_int|0
ques
c_cond
(paren
(paren
id|Ftarget
op_star
id|n
)paren
op_minus
(paren
id|Fref
op_star
(paren
id|m
op_amp
op_complement
l_int|3
)paren
)paren
)paren
suffix:colon
(paren
(paren
id|Fref
op_star
(paren
id|m
op_amp
op_complement
l_int|3
)paren
)paren
op_minus
(paren
id|Ftarget
op_star
id|n
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|new_error
OL
id|best_error
)paren
(brace
id|best_n
op_assign
id|n
suffix:semicolon
id|best_m
op_assign
id|m
suffix:semicolon
id|best_error
op_assign
id|new_error
suffix:semicolon
)brace
)brace
)brace
r_if
c_cond
(paren
id|best_m
OG
l_int|257
)paren
id|best_m
op_rshift_assign
l_int|2
suffix:semicolon
multiline_comment|/* divide m by 4, and leave VCO loop divide at 4 */
r_else
id|divisor
op_or_assign
l_int|4
suffix:semicolon
multiline_comment|/* or set VCO loop divide to 1 */
op_star
id|dclk2_m
op_assign
id|best_m
op_minus
l_int|2
suffix:semicolon
op_star
id|dclk2_n
op_assign
id|best_n
op_minus
l_int|2
suffix:semicolon
op_star
id|dclk2_div
op_assign
id|divisor
suffix:semicolon
op_star
id|ppixclock
op_assign
id|pixclock
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|asiliant_set_timing
r_static
r_void
id|asiliant_set_timing
c_func
(paren
r_struct
id|fb_info
op_star
id|p
)paren
(brace
r_int
id|hd
op_assign
id|p-&gt;var.xres
op_div
l_int|8
suffix:semicolon
r_int
id|hs
op_assign
(paren
id|p-&gt;var.xres
op_plus
id|p-&gt;var.right_margin
)paren
op_div
l_int|8
suffix:semicolon
r_int
id|he
op_assign
(paren
id|p-&gt;var.xres
op_plus
id|p-&gt;var.right_margin
op_plus
id|p-&gt;var.hsync_len
)paren
op_div
l_int|8
suffix:semicolon
r_int
id|ht
op_assign
(paren
id|p-&gt;var.left_margin
op_plus
id|p-&gt;var.xres
op_plus
id|p-&gt;var.right_margin
op_plus
id|p-&gt;var.hsync_len
)paren
op_div
l_int|8
suffix:semicolon
r_int
id|vd
op_assign
id|p-&gt;var.yres
suffix:semicolon
r_int
id|vs
op_assign
id|p-&gt;var.yres
op_plus
id|p-&gt;var.lower_margin
suffix:semicolon
r_int
id|ve
op_assign
id|p-&gt;var.yres
op_plus
id|p-&gt;var.lower_margin
op_plus
id|p-&gt;var.vsync_len
suffix:semicolon
r_int
id|vt
op_assign
id|p-&gt;var.upper_margin
op_plus
id|p-&gt;var.yres
op_plus
id|p-&gt;var.lower_margin
op_plus
id|p-&gt;var.vsync_len
suffix:semicolon
r_int
id|wd
op_assign
(paren
id|p-&gt;var.xres_virtual
op_star
(paren
(paren
id|p-&gt;var.bits_per_pixel
op_plus
l_int|7
)paren
op_div
l_int|8
)paren
)paren
op_div
l_int|8
suffix:semicolon
r_if
c_cond
(paren
(paren
id|p-&gt;var.xres
op_eq
l_int|640
)paren
op_logical_and
(paren
id|p-&gt;var.yres
op_eq
l_int|480
)paren
op_logical_and
(paren
id|p-&gt;var.pixclock
op_eq
l_int|39722
)paren
)paren
(brace
id|write_fr
c_func
(paren
l_int|0x01
comma
l_int|0x02
)paren
suffix:semicolon
multiline_comment|/* LCD */
)brace
r_else
(brace
id|write_fr
c_func
(paren
l_int|0x01
comma
l_int|0x01
)paren
suffix:semicolon
multiline_comment|/* CRT */
)brace
id|write_cr
c_func
(paren
l_int|0x11
comma
(paren
id|ve
op_minus
l_int|1
)paren
op_amp
l_int|0x0f
)paren
suffix:semicolon
id|write_cr
c_func
(paren
l_int|0x00
comma
(paren
id|ht
op_minus
l_int|5
)paren
op_amp
l_int|0xff
)paren
suffix:semicolon
id|write_cr
c_func
(paren
l_int|0x01
comma
id|hd
op_minus
l_int|1
)paren
suffix:semicolon
id|write_cr
c_func
(paren
l_int|0x02
comma
id|hd
)paren
suffix:semicolon
id|write_cr
c_func
(paren
l_int|0x03
comma
(paren
(paren
id|ht
op_minus
l_int|1
)paren
op_amp
l_int|0x1f
)paren
op_or
l_int|0x80
)paren
suffix:semicolon
id|write_cr
c_func
(paren
l_int|0x04
comma
id|hs
)paren
suffix:semicolon
id|write_cr
c_func
(paren
l_int|0x05
comma
(paren
(paren
(paren
id|ht
op_minus
l_int|1
)paren
op_amp
l_int|0x20
)paren
op_lshift
l_int|2
)paren
op_or
(paren
id|he
op_amp
l_int|0x1f
)paren
)paren
suffix:semicolon
id|write_cr
c_func
(paren
l_int|0x3c
comma
(paren
id|ht
op_minus
l_int|1
)paren
op_amp
l_int|0xc0
)paren
suffix:semicolon
id|write_cr
c_func
(paren
l_int|0x06
comma
(paren
id|vt
op_minus
l_int|2
)paren
op_amp
l_int|0xff
)paren
suffix:semicolon
id|write_cr
c_func
(paren
l_int|0x30
comma
(paren
id|vt
op_minus
l_int|2
)paren
op_rshift
l_int|8
)paren
suffix:semicolon
id|write_cr
c_func
(paren
l_int|0x07
comma
l_int|0x00
)paren
suffix:semicolon
id|write_cr
c_func
(paren
l_int|0x08
comma
l_int|0x00
)paren
suffix:semicolon
id|write_cr
c_func
(paren
l_int|0x09
comma
l_int|0x00
)paren
suffix:semicolon
id|write_cr
c_func
(paren
l_int|0x10
comma
(paren
id|vs
op_minus
l_int|1
)paren
op_amp
l_int|0xff
)paren
suffix:semicolon
id|write_cr
c_func
(paren
l_int|0x32
comma
(paren
(paren
id|vs
op_minus
l_int|1
)paren
op_rshift
l_int|8
)paren
op_amp
l_int|0xf
)paren
suffix:semicolon
id|write_cr
c_func
(paren
l_int|0x11
comma
(paren
(paren
id|ve
op_minus
l_int|1
)paren
op_amp
l_int|0x0f
)paren
op_or
l_int|0x80
)paren
suffix:semicolon
id|write_cr
c_func
(paren
l_int|0x12
comma
(paren
id|vd
op_minus
l_int|1
)paren
op_amp
l_int|0xff
)paren
suffix:semicolon
id|write_cr
c_func
(paren
l_int|0x31
comma
(paren
(paren
id|vd
op_minus
l_int|1
)paren
op_amp
l_int|0xf00
)paren
op_rshift
l_int|8
)paren
suffix:semicolon
id|write_cr
c_func
(paren
l_int|0x13
comma
id|wd
op_amp
l_int|0xff
)paren
suffix:semicolon
id|write_cr
c_func
(paren
l_int|0x41
comma
(paren
id|wd
op_amp
l_int|0xf00
)paren
op_rshift
l_int|8
)paren
suffix:semicolon
id|write_cr
c_func
(paren
l_int|0x15
comma
(paren
id|vs
op_minus
l_int|1
)paren
op_amp
l_int|0xff
)paren
suffix:semicolon
id|write_cr
c_func
(paren
l_int|0x33
comma
(paren
(paren
id|vs
op_minus
l_int|1
)paren
op_rshift
l_int|8
)paren
op_amp
l_int|0xf
)paren
suffix:semicolon
id|write_cr
c_func
(paren
l_int|0x38
comma
(paren
(paren
id|ht
op_minus
l_int|5
)paren
op_amp
l_int|0x100
)paren
op_rshift
l_int|8
)paren
suffix:semicolon
id|write_cr
c_func
(paren
l_int|0x16
comma
(paren
id|vt
op_minus
l_int|1
)paren
op_amp
l_int|0xff
)paren
suffix:semicolon
id|write_cr
c_func
(paren
l_int|0x18
comma
l_int|0x00
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;var.xres
op_eq
l_int|640
)paren
(brace
id|writeb
c_func
(paren
l_int|0xc7
comma
id|mmio_base
op_plus
l_int|0x784
)paren
suffix:semicolon
multiline_comment|/* set misc output reg */
)brace
r_else
(brace
id|writeb
c_func
(paren
l_int|0x07
comma
id|mmio_base
op_plus
l_int|0x784
)paren
suffix:semicolon
multiline_comment|/* set misc output reg */
)brace
)brace
DECL|function|asiliantfb_check_var
r_static
r_int
id|asiliantfb_check_var
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
id|p
)paren
(brace
r_int
r_int
id|Ftarget
comma
id|ratio
comma
id|remainder
suffix:semicolon
id|ratio
op_assign
l_int|1000000
op_div
id|var-&gt;pixclock
suffix:semicolon
id|remainder
op_assign
l_int|1000000
op_mod
id|var-&gt;pixclock
suffix:semicolon
id|Ftarget
op_assign
l_int|1000000
op_star
id|ratio
op_plus
(paren
l_int|1000000
op_star
id|remainder
)paren
op_div
id|var-&gt;pixclock
suffix:semicolon
multiline_comment|/* First check the constraint that the maximum post-VCO divisor is 32,&n;&t; * and the maximum Fvco is 220MHz */
r_if
c_cond
(paren
id|Ftarget
OG
l_int|220000000
op_logical_or
id|Ftarget
OL
l_int|3125000
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;asiliantfb dotclock must be between 3.125 and 220MHz&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
id|var-&gt;xres_virtual
op_assign
id|var-&gt;xres
suffix:semicolon
id|var-&gt;yres_virtual
op_assign
id|var-&gt;yres
suffix:semicolon
r_if
c_cond
(paren
id|var-&gt;bits_per_pixel
op_eq
l_int|24
)paren
(brace
id|var-&gt;red.offset
op_assign
l_int|16
suffix:semicolon
id|var-&gt;green.offset
op_assign
l_int|8
suffix:semicolon
id|var-&gt;blue.offset
op_assign
l_int|0
suffix:semicolon
id|var-&gt;red.length
op_assign
id|var-&gt;blue.length
op_assign
id|var-&gt;green.length
op_assign
l_int|8
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|var-&gt;bits_per_pixel
op_eq
l_int|16
)paren
(brace
r_switch
c_cond
(paren
id|var-&gt;red.offset
)paren
(brace
r_case
l_int|11
suffix:colon
id|var-&gt;green.length
op_assign
l_int|6
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|10
suffix:colon
id|var-&gt;green.length
op_assign
l_int|5
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|var-&gt;green.offset
op_assign
l_int|5
suffix:semicolon
id|var-&gt;blue.offset
op_assign
l_int|0
suffix:semicolon
id|var-&gt;red.length
op_assign
id|var-&gt;blue.length
op_assign
l_int|5
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|var-&gt;bits_per_pixel
op_eq
l_int|8
)paren
(brace
id|var-&gt;red.offset
op_assign
id|var-&gt;green.offset
op_assign
id|var-&gt;blue.offset
op_assign
l_int|0
suffix:semicolon
id|var-&gt;red.length
op_assign
id|var-&gt;green.length
op_assign
id|var-&gt;blue.length
op_assign
l_int|8
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|asiliantfb_set_par
r_static
r_int
id|asiliantfb_set_par
c_func
(paren
r_struct
id|fb_info
op_star
id|p
)paren
(brace
id|u8
id|dclk2_m
suffix:semicolon
multiline_comment|/* Holds m-2 value for register */
id|u8
id|dclk2_n
suffix:semicolon
multiline_comment|/* Holds n-2 value for register */
id|u8
id|dclk2_div
suffix:semicolon
multiline_comment|/* Holds divisor bitmask */
multiline_comment|/* Set pixclock */
id|asiliant_calc_dclk2
c_func
(paren
op_amp
id|p-&gt;var.pixclock
comma
op_amp
id|dclk2_m
comma
op_amp
id|dclk2_n
comma
op_amp
id|dclk2_div
)paren
suffix:semicolon
multiline_comment|/* Set color depth */
r_if
c_cond
(paren
id|p-&gt;var.bits_per_pixel
op_eq
l_int|24
)paren
(brace
id|write_xr
c_func
(paren
l_int|0x81
comma
l_int|0x16
)paren
suffix:semicolon
multiline_comment|/* 24 bit packed color mode */
id|write_xr
c_func
(paren
l_int|0x82
comma
l_int|0x00
)paren
suffix:semicolon
multiline_comment|/* Disable palettes */
id|write_xr
c_func
(paren
l_int|0x20
comma
l_int|0x20
)paren
suffix:semicolon
multiline_comment|/* 24 bit blitter mode */
)brace
r_else
r_if
c_cond
(paren
id|p-&gt;var.bits_per_pixel
op_eq
l_int|16
)paren
(brace
r_if
c_cond
(paren
id|p-&gt;var.red.offset
op_eq
l_int|11
)paren
id|write_xr
c_func
(paren
l_int|0x81
comma
l_int|0x15
)paren
suffix:semicolon
multiline_comment|/* 16 bit color mode */
r_else
id|write_xr
c_func
(paren
l_int|0x81
comma
l_int|0x14
)paren
suffix:semicolon
multiline_comment|/* 15 bit color mode */
id|write_xr
c_func
(paren
l_int|0x82
comma
l_int|0x00
)paren
suffix:semicolon
multiline_comment|/* Disable palettes */
id|write_xr
c_func
(paren
l_int|0x20
comma
l_int|0x10
)paren
suffix:semicolon
multiline_comment|/* 16 bit blitter mode */
)brace
r_else
r_if
c_cond
(paren
id|p-&gt;var.bits_per_pixel
op_eq
l_int|8
)paren
(brace
id|write_xr
c_func
(paren
l_int|0x0a
comma
l_int|0x02
)paren
suffix:semicolon
multiline_comment|/* Linear */
id|write_xr
c_func
(paren
l_int|0x81
comma
l_int|0x12
)paren
suffix:semicolon
multiline_comment|/* 8 bit color mode */
id|write_xr
c_func
(paren
l_int|0x82
comma
l_int|0x00
)paren
suffix:semicolon
multiline_comment|/* Graphics gamma enable */
id|write_xr
c_func
(paren
l_int|0x20
comma
l_int|0x00
)paren
suffix:semicolon
multiline_comment|/* 8 bit blitter mode */
)brace
id|p-&gt;fix.line_length
op_assign
id|p-&gt;var.xres
op_star
(paren
id|p-&gt;var.bits_per_pixel
op_rshift
l_int|3
)paren
suffix:semicolon
id|p-&gt;fix.visual
op_assign
(paren
id|p-&gt;var.bits_per_pixel
op_eq
l_int|8
)paren
ques
c_cond
id|FB_VISUAL_PSEUDOCOLOR
suffix:colon
id|FB_VISUAL_TRUECOLOR
suffix:semicolon
id|write_xr
c_func
(paren
l_int|0xc4
comma
id|dclk2_m
)paren
suffix:semicolon
id|write_xr
c_func
(paren
l_int|0xc5
comma
id|dclk2_n
)paren
suffix:semicolon
id|write_xr
c_func
(paren
l_int|0xc7
comma
id|dclk2_div
)paren
suffix:semicolon
multiline_comment|/* Set up the CR registers */
id|asiliant_set_timing
c_func
(paren
id|p
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|asiliantfb_setcolreg
r_static
r_int
id|asiliantfb_setcolreg
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
id|p
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
multiline_comment|/* Set hardware palete */
id|writeb
c_func
(paren
id|regno
comma
id|mmio_base
op_plus
l_int|0x790
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|writeb
c_func
(paren
id|red
comma
id|mmio_base
op_plus
l_int|0x791
)paren
suffix:semicolon
id|writeb
c_func
(paren
id|green
comma
id|mmio_base
op_plus
l_int|0x791
)paren
suffix:semicolon
id|writeb
c_func
(paren
id|blue
comma
id|mmio_base
op_plus
l_int|0x791
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|p-&gt;var.bits_per_pixel
)paren
(brace
r_case
l_int|15
suffix:colon
r_if
c_cond
(paren
id|regno
OL
l_int|16
)paren
(brace
(paren
(paren
id|u32
op_star
)paren
(paren
id|p-&gt;pseudo_palette
)paren
)paren
(braket
id|regno
)braket
op_assign
(paren
(paren
id|red
op_amp
l_int|0xf8
)paren
op_lshift
l_int|7
)paren
op_or
(paren
(paren
id|green
op_amp
l_int|0xf8
)paren
op_lshift
l_int|2
)paren
op_or
(paren
(paren
id|blue
op_amp
l_int|0xf8
)paren
op_rshift
l_int|3
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_int|16
suffix:colon
r_if
c_cond
(paren
id|regno
OL
l_int|16
)paren
(brace
(paren
(paren
id|u32
op_star
)paren
(paren
id|p-&gt;pseudo_palette
)paren
)paren
(braket
id|regno
)braket
op_assign
(paren
(paren
id|red
op_amp
l_int|0xf8
)paren
op_lshift
l_int|8
)paren
op_or
(paren
(paren
id|green
op_amp
l_int|0xfc
)paren
op_lshift
l_int|3
)paren
op_or
(paren
(paren
id|blue
op_amp
l_int|0xf8
)paren
op_rshift
l_int|3
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_int|24
suffix:colon
r_if
c_cond
(paren
id|regno
OL
l_int|24
)paren
(brace
(paren
(paren
id|u32
op_star
)paren
(paren
id|p-&gt;pseudo_palette
)paren
)paren
(braket
id|regno
)braket
op_assign
(paren
id|red
op_lshift
l_int|16
)paren
op_or
(paren
id|green
op_lshift
l_int|8
)paren
op_or
(paren
id|blue
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
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
multiline_comment|/* Reset register */
(brace
l_int|0x01
comma
l_int|0x01
)brace
comma
multiline_comment|/* Clocking mode */
(brace
l_int|0x02
comma
l_int|0x0f
)brace
comma
multiline_comment|/* Plane mask */
(brace
l_int|0x04
comma
l_int|0x0e
)brace
multiline_comment|/* Memory mode */
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
l_int|0x03
comma
l_int|0x00
)brace
comma
multiline_comment|/* Data rotate */
(brace
l_int|0x05
comma
l_int|0x00
)brace
comma
multiline_comment|/* Graphics mode */
(brace
l_int|0x06
comma
l_int|0x01
)brace
comma
multiline_comment|/* Miscellaneous */
(brace
l_int|0x08
comma
l_int|0x00
)brace
multiline_comment|/* Bit mask */
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
multiline_comment|/* Mode control */
(brace
l_int|0x11
comma
l_int|0x00
)brace
comma
multiline_comment|/* Overscan */
(brace
l_int|0x12
comma
l_int|0x0f
)brace
comma
multiline_comment|/* Memory plane enable */
(brace
l_int|0x13
comma
l_int|0x00
)brace
multiline_comment|/* Horizontal pixel panning */
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
l_int|0x0c
comma
l_int|0x00
)brace
comma
multiline_comment|/* Start address high */
(brace
l_int|0x0d
comma
l_int|0x00
)brace
comma
multiline_comment|/* Start address low */
(brace
l_int|0x40
comma
l_int|0x00
)brace
comma
multiline_comment|/* Extended Start Address */
(brace
l_int|0x41
comma
l_int|0x00
)brace
comma
multiline_comment|/* Extended Start Address */
(brace
l_int|0x14
comma
l_int|0x00
)brace
comma
multiline_comment|/* Underline location */
(brace
l_int|0x17
comma
l_int|0xe3
)brace
comma
multiline_comment|/* CRT mode control */
(brace
l_int|0x70
comma
l_int|0x00
)brace
multiline_comment|/* Interlace control */
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
l_int|0x08
comma
l_int|0xcc
)brace
comma
(brace
l_int|0x0a
comma
l_int|0x08
)brace
comma
(brace
l_int|0x18
comma
l_int|0x00
)brace
comma
(brace
l_int|0x1e
comma
l_int|0x80
)brace
comma
(brace
l_int|0x40
comma
l_int|0x83
)brace
comma
(brace
l_int|0x41
comma
l_int|0x00
)brace
comma
(brace
l_int|0x48
comma
l_int|0x13
)brace
comma
(brace
l_int|0x4d
comma
l_int|0x60
)brace
comma
(brace
l_int|0x4e
comma
l_int|0x0f
)brace
comma
(brace
l_int|0x0b
comma
l_int|0x01
)brace
comma
(brace
l_int|0x21
comma
l_int|0x51
)brace
comma
(brace
l_int|0x22
comma
l_int|0x1d
)brace
comma
(brace
l_int|0x23
comma
l_int|0x5f
)brace
comma
(brace
l_int|0x20
comma
l_int|0x4f
)brace
comma
(brace
l_int|0x34
comma
l_int|0x00
)brace
comma
(brace
l_int|0x24
comma
l_int|0x51
)brace
comma
(brace
l_int|0x25
comma
l_int|0x00
)brace
comma
(brace
l_int|0x27
comma
l_int|0x0b
)brace
comma
(brace
l_int|0x26
comma
l_int|0x00
)brace
comma
(brace
l_int|0x37
comma
l_int|0x80
)brace
comma
(brace
l_int|0x33
comma
l_int|0x0b
)brace
comma
(brace
l_int|0x35
comma
l_int|0x11
)brace
comma
(brace
l_int|0x36
comma
l_int|0x02
)brace
comma
(brace
l_int|0x31
comma
l_int|0xea
)brace
comma
(brace
l_int|0x32
comma
l_int|0x0c
)brace
comma
(brace
l_int|0x30
comma
l_int|0xdf
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
(brace
l_int|0x12
comma
l_int|0x50
)brace
comma
(brace
l_int|0x13
comma
l_int|0x00
)brace
comma
(brace
l_int|0x16
comma
l_int|0x03
)brace
comma
(brace
l_int|0x17
comma
l_int|0xbd
)brace
comma
(brace
l_int|0x1a
comma
l_int|0x00
)brace
comma
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
l_int|200
)brace
comma
multiline_comment|/* MCLK ratio M */
(brace
l_int|0xcd
comma
l_int|18
)brace
comma
multiline_comment|/* MCLK ratio N */
(brace
l_int|0xce
comma
l_int|0x90
)brace
comma
multiline_comment|/* MCLK divisor = 2 */
(brace
l_int|0xc4
comma
l_int|209
)brace
comma
(brace
l_int|0xc5
comma
l_int|118
)brace
comma
(brace
l_int|0xc7
comma
l_int|32
)brace
comma
(brace
l_int|0xcf
comma
l_int|0x06
)brace
comma
(brace
l_int|0x09
comma
l_int|0x01
)brace
comma
multiline_comment|/* IO Control - CRT controller extensions */
(brace
l_int|0x0a
comma
l_int|0x02
)brace
comma
multiline_comment|/* Frame buffer mapping */
(brace
l_int|0x0b
comma
l_int|0x01
)brace
comma
multiline_comment|/* PCI burst write */
(brace
l_int|0x40
comma
l_int|0x03
)brace
comma
multiline_comment|/* Memory access control */
(brace
l_int|0x80
comma
l_int|0x82
)brace
comma
multiline_comment|/* Pixel pipeline configuration 0 */
(brace
l_int|0x81
comma
l_int|0x12
)brace
comma
multiline_comment|/* Pixel pipeline configuration 1 */
(brace
l_int|0x82
comma
l_int|0x08
)brace
comma
multiline_comment|/* Pixel pipeline configuration 2 */
(brace
l_int|0xd0
comma
l_int|0x0f
)brace
comma
(brace
l_int|0xd1
comma
l_int|0x01
)brace
comma
)brace
suffix:semicolon
DECL|function|chips_hw_init
r_static
r_void
id|__devinit
id|chips_hw_init
c_func
(paren
r_struct
id|fb_info
op_star
id|p
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
id|write_xr
c_func
(paren
l_int|0x81
comma
l_int|0x12
)paren
suffix:semicolon
id|write_xr
c_func
(paren
l_int|0x82
comma
l_int|0x08
)paren
suffix:semicolon
id|write_xr
c_func
(paren
l_int|0x20
comma
l_int|0x00
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
multiline_comment|/* Enable video output in attribute index register */
id|writeb
c_func
(paren
l_int|0x20
comma
id|mmio_base
op_plus
l_int|0x780
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
DECL|variable|__devinitdata
r_static
r_struct
id|fb_fix_screeninfo
id|asiliantfb_fix
id|__devinitdata
op_assign
(brace
dot
id|id
op_assign
l_string|&quot;Asiliant 69000&quot;
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
l_int|640
comma
dot
id|smem_len
op_assign
l_int|0x200000
comma
multiline_comment|/* 2MB */
)brace
suffix:semicolon
DECL|variable|__devinitdata
r_static
r_struct
id|fb_var_screeninfo
id|asiliantfb_var
id|__devinitdata
op_assign
(brace
dot
id|xres
op_assign
l_int|640
comma
dot
id|yres
op_assign
l_int|480
comma
dot
id|xres_virtual
op_assign
l_int|640
comma
dot
id|yres_virtual
op_assign
l_int|480
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
l_int|39722
comma
dot
id|left_margin
op_assign
l_int|48
comma
dot
id|right_margin
op_assign
l_int|16
comma
dot
id|upper_margin
op_assign
l_int|33
comma
dot
id|lower_margin
op_assign
l_int|10
comma
dot
id|hsync_len
op_assign
l_int|96
comma
dot
id|vsync_len
op_assign
l_int|2
comma
)brace
suffix:semicolon
DECL|function|init_asiliant
r_static
r_void
id|__devinit
id|init_asiliant
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
id|asiliantfb_fix
suffix:semicolon
id|p-&gt;fix.smem_start
op_assign
id|addr
suffix:semicolon
id|p-&gt;var
op_assign
id|asiliantfb_var
suffix:semicolon
id|p-&gt;fbops
op_assign
op_amp
id|asiliantfb_ops
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
l_string|&quot;C&amp;T 69000 framebuffer failed to register&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;fb%d: Asiliant 69000 frame buffer (%dK RAM detected)&bslash;n&quot;
comma
id|p-&gt;node
comma
id|p-&gt;fix.smem_len
op_div
l_int|1024
)paren
suffix:semicolon
id|writeb
c_func
(paren
l_int|0xff
comma
id|mmio_base
op_plus
l_int|0x78c
)paren
suffix:semicolon
id|chips_hw_init
c_func
(paren
id|p
)paren
suffix:semicolon
)brace
r_static
r_int
id|__devinit
DECL|function|asiliantfb_pci_init
id|asiliantfb_pci_init
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
r_int
r_int
id|addr
comma
id|size
suffix:semicolon
r_struct
id|fb_info
op_star
id|p
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
op_logical_neg
id|request_mem_region
c_func
(paren
id|addr
comma
id|size
comma
l_string|&quot;asiliantfb&quot;
)paren
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|p
op_assign
id|framebuffer_alloc
c_func
(paren
r_sizeof
(paren
id|u32
)paren
op_star
l_int|256
comma
op_amp
id|dp-&gt;dev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
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
id|p-&gt;pseudo_palette
op_assign
id|p-&gt;par
suffix:semicolon
id|p-&gt;par
op_assign
l_int|NULL
suffix:semicolon
id|p-&gt;screen_base
op_assign
id|ioremap
c_func
(paren
id|addr
comma
l_int|0x800000
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
id|framebuffer_release
c_func
(paren
id|p
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|pci_write_config_dword
c_func
(paren
id|dp
comma
l_int|4
comma
l_int|0x02800083
)paren
suffix:semicolon
id|writeb
c_func
(paren
l_int|3
comma
id|p-&gt;screen_base
op_plus
l_int|0x400784
)paren
suffix:semicolon
id|init_asiliant
c_func
(paren
id|p
comma
id|addr
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
DECL|function|asiliantfb_remove
r_static
r_void
id|__devexit
id|asiliantfb_remove
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
id|pci_set_drvdata
c_func
(paren
id|dp
comma
l_int|NULL
)paren
suffix:semicolon
id|framebuffer_release
c_func
(paren
id|p
)paren
suffix:semicolon
)brace
DECL|variable|__devinitdata
r_static
r_struct
id|pci_device_id
id|asiliantfb_pci_tbl
(braket
)braket
id|__devinitdata
op_assign
(brace
(brace
id|PCI_VENDOR_ID_CT
comma
id|PCI_DEVICE_ID_CT_69000
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
id|asiliantfb_pci_tbl
)paren
suffix:semicolon
DECL|variable|asiliantfb_driver
r_static
r_struct
id|pci_driver
id|asiliantfb_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;asiliantfb&quot;
comma
dot
id|id_table
op_assign
id|asiliantfb_pci_tbl
comma
dot
id|probe
op_assign
id|asiliantfb_pci_init
comma
dot
id|remove
op_assign
id|__devexit_p
c_func
(paren
id|asiliantfb_remove
)paren
comma
)brace
suffix:semicolon
DECL|function|asiliantfb_init
r_int
id|__init
id|asiliantfb_init
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
l_string|&quot;asiliantfb&quot;
comma
l_int|NULL
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_return
id|pci_module_init
c_func
(paren
op_amp
id|asiliantfb_driver
)paren
suffix:semicolon
)brace
DECL|variable|asiliantfb_init
id|module_init
c_func
(paren
id|asiliantfb_init
)paren
suffix:semicolon
DECL|function|asiliantfb_exit
r_static
r_void
id|__exit
id|asiliantfb_exit
c_func
(paren
r_void
)paren
(brace
id|pci_unregister_driver
c_func
(paren
op_amp
id|asiliantfb_driver
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
