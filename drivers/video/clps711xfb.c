multiline_comment|/*&n; *  linux/drivers/video/clps711xfb.c&n; *&n; *  Copyright (C) 2000-2001 Deep Blue Solutions Ltd.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; *&n; *  Framebuffer driver for the CLPS7111 and EP7212 processors.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/fb.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/hardware/clps7111.h&gt;
macro_line|#include &lt;asm/arch/syspld.h&gt;
DECL|variable|cfb
r_struct
id|fb_info
op_star
id|cfb
suffix:semicolon
DECL|macro|CMAP_MAX_SIZE
mdefine_line|#define CMAP_MAX_SIZE&t;16
multiline_comment|/* The /proc entry for the backlight. */
DECL|variable|clps7111fb_backlight_proc_entry
r_static
r_struct
id|proc_dir_entry
op_star
id|clps7111fb_backlight_proc_entry
op_assign
l_int|NULL
suffix:semicolon
r_static
r_int
id|clps7111fb_proc_backlight_read
c_func
(paren
r_char
op_star
id|page
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|off
comma
r_int
id|count
comma
r_int
op_star
id|eof
comma
r_void
op_star
id|data
)paren
suffix:semicolon
r_static
r_int
id|clps7111fb_proc_backlight_write
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
op_star
id|buffer
comma
r_int
r_int
id|count
comma
r_void
op_star
id|data
)paren
suffix:semicolon
multiline_comment|/*&n; * LCD AC Prescale.  This comes from the LCD panel manufacturers specifications.&n; * This determines how many clocks + 1 of CL1 before the M signal toggles.&n; * The number of lines on the display must not be divisible by this number.&n; */
DECL|variable|lcd_ac_prescale
r_static
r_int
r_int
id|lcd_ac_prescale
op_assign
l_int|13
suffix:semicolon
multiline_comment|/*&n; *    Set a single color register. Return != 0 for invalid regno.&n; */
r_static
r_int
DECL|function|clps7111fb_setcolreg
id|clps7111fb_setcolreg
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
r_int
r_int
id|level
comma
id|mask
comma
id|shift
comma
id|pal
suffix:semicolon
r_if
c_cond
(paren
id|regno
op_ge
(paren
l_int|1
op_lshift
id|info-&gt;var.bits_per_pixel
)paren
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* gray = 0.30*R + 0.58*G + 0.11*B */
id|level
op_assign
(paren
id|red
op_star
l_int|77
op_plus
id|green
op_star
l_int|151
op_plus
id|blue
op_star
l_int|28
)paren
op_rshift
l_int|20
suffix:semicolon
multiline_comment|/*&n;&t; * On an LCD, a high value is dark, while a low value is light. &n;&t; * So we invert the level.&n;&t; *&n;&t; * This isn&squot;t true on all machines, so we only do it on EDB7211.&n;&t; *  --rmk&n;&t; */
r_if
c_cond
(paren
id|machine_is_edb7211
c_func
(paren
)paren
)paren
(brace
id|level
op_assign
l_int|15
op_minus
id|level
suffix:semicolon
)brace
id|shift
op_assign
l_int|4
op_star
(paren
id|regno
op_amp
l_int|7
)paren
suffix:semicolon
id|level
op_lshift_assign
id|shift
suffix:semicolon
id|mask
op_assign
l_int|15
op_lshift
id|shift
suffix:semicolon
id|level
op_and_assign
id|mask
suffix:semicolon
id|regno
op_assign
id|regno
OL
l_int|8
ques
c_cond
id|PALLSW
suffix:colon
id|PALMSW
suffix:semicolon
id|pal
op_assign
id|clps_readl
c_func
(paren
id|regno
)paren
suffix:semicolon
id|pal
op_assign
(paren
id|pal
op_amp
op_complement
id|mask
)paren
op_or
id|level
suffix:semicolon
id|clps_writel
c_func
(paren
id|pal
comma
id|regno
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Validate the purposed mode.&n; */
r_static
r_int
DECL|function|clps7111fb_check_var
id|clps7111fb_check_var
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
id|var-&gt;transp.msb_right
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
id|var-&gt;red.msb_right
op_assign
l_int|0
suffix:semicolon
id|var-&gt;red.offset
op_assign
l_int|0
suffix:semicolon
id|var-&gt;red.length
op_assign
id|var-&gt;bits_per_pixel
suffix:semicolon
id|var-&gt;green
op_assign
id|var-&gt;red
suffix:semicolon
id|var-&gt;blue
op_assign
id|var-&gt;red
suffix:semicolon
r_if
c_cond
(paren
id|var-&gt;bits_per_pixel
OG
l_int|4
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Set the hardware state.&n; */
r_static
r_int
DECL|function|clps7111fb_set_par
id|clps7111fb_set_par
c_func
(paren
r_struct
id|fb_info
op_star
id|info
)paren
(brace
r_int
r_int
id|lcdcon
comma
id|syscon
comma
id|pixclock
suffix:semicolon
r_switch
c_cond
(paren
id|info-&gt;var.bits_per_pixel
)paren
(brace
r_case
l_int|1
suffix:colon
id|info-&gt;fix.visual
op_assign
id|FB_VISUAL_MONO01
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|info-&gt;fix.visual
op_assign
id|FB_VISUAL_PSEUDOCOLOR
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|info-&gt;fix.visual
op_assign
id|FB_VISUAL_PSEUDOCOLOR
suffix:semicolon
r_break
suffix:semicolon
)brace
id|info-&gt;fix.line_length
op_assign
id|info-&gt;var.xres_virtual
op_star
id|info-&gt;var.bits_per_pixel
op_div
l_int|8
suffix:semicolon
id|lcdcon
op_assign
(paren
id|info-&gt;var.xres_virtual
op_star
id|info-&gt;var.yres_virtual
op_star
id|info-&gt;var.bits_per_pixel
)paren
op_div
l_int|128
op_minus
l_int|1
suffix:semicolon
id|lcdcon
op_or_assign
(paren
(paren
id|info-&gt;var.xres_virtual
op_div
l_int|16
)paren
op_minus
l_int|1
)paren
op_lshift
l_int|13
suffix:semicolon
id|lcdcon
op_or_assign
id|lcd_ac_prescale
op_lshift
l_int|25
suffix:semicolon
multiline_comment|/*&n;&t; * Calculate pixel prescale value from the pixclock.  This is:&n;&t; *  36.864MHz / pixclock_mhz - 1.&n;&t; * However, pixclock is in picoseconds, so this ends up being:&n;&t; *  36864000 * pixclock_ps / 10^12 - 1&n;&t; * and this will overflow the 32-bit math.  We perform this as&n;&t; * (9 * 4096000 == 36864000):&n;&t; *  pixclock_ps * 9 * (4096000 / 10^12) - 1&n;&t; */
id|pixclock
op_assign
l_int|9
op_star
id|info-&gt;var.pixclock
op_div
l_int|244140
op_minus
l_int|1
suffix:semicolon
id|lcdcon
op_or_assign
id|pixclock
op_lshift
l_int|19
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;var.bits_per_pixel
op_eq
l_int|4
)paren
id|lcdcon
op_or_assign
id|LCDCON_GSMD
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;var.bits_per_pixel
op_ge
l_int|2
)paren
id|lcdcon
op_or_assign
id|LCDCON_GSEN
suffix:semicolon
multiline_comment|/*&n;&t; * LCDCON must only be changed while the LCD is disabled&n;&t; */
id|syscon
op_assign
id|clps_readl
c_func
(paren
id|SYSCON1
)paren
suffix:semicolon
id|clps_writel
c_func
(paren
id|syscon
op_amp
op_complement
id|SYSCON1_LCDEN
comma
id|SYSCON1
)paren
suffix:semicolon
id|clps_writel
c_func
(paren
id|lcdcon
comma
id|LCDCON
)paren
suffix:semicolon
id|clps_writel
c_func
(paren
id|syscon
op_or
id|SYSCON1_LCDEN
comma
id|SYSCON1
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|clps7111fb_blank
r_static
r_int
id|clps7111fb_blank
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
r_if
c_cond
(paren
id|blank
)paren
(brace
r_if
c_cond
(paren
id|machine_is_edb7211
c_func
(paren
)paren
)paren
(brace
multiline_comment|/* Turn off the LCD backlight. */
id|clps_writeb
c_func
(paren
id|clps_readb
c_func
(paren
id|PDDR
)paren
op_amp
op_complement
id|EDB_PD3_LCDBL
comma
id|PDDR
)paren
suffix:semicolon
multiline_comment|/* Power off the LCD DC-DC converter. */
id|clps_writeb
c_func
(paren
id|clps_readb
c_func
(paren
id|PDDR
)paren
op_amp
op_complement
id|EDB_PD1_LCD_DC_DC_EN
comma
id|PDDR
)paren
suffix:semicolon
multiline_comment|/* Delay for a little while (half a second). */
id|udelay
c_func
(paren
l_int|100
)paren
suffix:semicolon
multiline_comment|/* Power off the LCD panel. */
id|clps_writeb
c_func
(paren
id|clps_readb
c_func
(paren
id|PDDR
)paren
op_amp
op_complement
id|EDB_PD2_LCDEN
comma
id|PDDR
)paren
suffix:semicolon
multiline_comment|/* Power off the LCD controller. */
id|clps_writel
c_func
(paren
id|clps_readl
c_func
(paren
id|SYSCON1
)paren
op_amp
op_complement
id|SYSCON1_LCDEN
comma
id|SYSCON1
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
id|machine_is_edb7211
c_func
(paren
)paren
)paren
(brace
multiline_comment|/* Power up the LCD controller. */
id|clps_writel
c_func
(paren
id|clps_readl
c_func
(paren
id|SYSCON1
)paren
op_or
id|SYSCON1_LCDEN
comma
id|SYSCON1
)paren
suffix:semicolon
multiline_comment|/* Power up the LCD panel. */
id|clps_writeb
c_func
(paren
id|clps_readb
c_func
(paren
id|PDDR
)paren
op_or
id|EDB_PD2_LCDEN
comma
id|PDDR
)paren
suffix:semicolon
multiline_comment|/* Delay for a little while. */
id|udelay
c_func
(paren
l_int|100
)paren
suffix:semicolon
multiline_comment|/* Power up the LCD DC-DC converter. */
id|clps_writeb
c_func
(paren
id|clps_readb
c_func
(paren
id|PDDR
)paren
op_or
id|EDB_PD1_LCD_DC_DC_EN
comma
id|PDDR
)paren
suffix:semicolon
multiline_comment|/* Turn on the LCD backlight. */
id|clps_writeb
c_func
(paren
id|clps_readb
c_func
(paren
id|PDDR
)paren
op_or
id|EDB_PD3_LCDBL
comma
id|PDDR
)paren
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|clps7111fb_ops
r_static
r_struct
id|fb_ops
id|clps7111fb_ops
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
id|clps7111fb_check_var
comma
dot
id|fb_set_par
op_assign
id|clps7111fb_set_par
comma
dot
id|fb_setcolreg
op_assign
id|clps7111fb_setcolreg
comma
dot
id|fb_blank
op_assign
id|clps7111fb_blank
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
id|cfb_cursor
comma
)brace
suffix:semicolon
r_static
r_int
DECL|function|clps7111fb_proc_backlight_read
id|clps7111fb_proc_backlight_read
c_func
(paren
r_char
op_star
id|page
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|off
comma
r_int
id|count
comma
r_int
op_star
id|eof
comma
r_void
op_star
id|data
)paren
(brace
multiline_comment|/* We need at least two characters, one for the digit, and one for&n;&t; * the terminating NULL. */
r_if
c_cond
(paren
id|count
OL
l_int|2
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|machine_is_edb7211
c_func
(paren
)paren
)paren
(brace
r_return
id|sprintf
c_func
(paren
id|page
comma
l_string|&quot;%d&bslash;n&quot;
comma
(paren
id|clps_readb
c_func
(paren
id|PDDR
)paren
op_amp
id|EDB_PD3_LCDBL
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|clps7111fb_proc_backlight_write
id|clps7111fb_proc_backlight_write
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
op_star
id|buffer
comma
r_int
r_int
id|count
comma
r_void
op_star
id|data
)paren
(brace
r_int
r_char
id|char_value
suffix:semicolon
r_int
id|value
suffix:semicolon
r_if
c_cond
(paren
id|count
OL
l_int|1
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|char_value
comma
id|buffer
comma
l_int|1
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|value
op_assign
id|char_value
op_minus
l_char|&squot;0&squot;
suffix:semicolon
r_if
c_cond
(paren
id|machine_is_edb7211
c_func
(paren
)paren
)paren
(brace
r_int
r_char
id|port_d
suffix:semicolon
id|port_d
op_assign
id|clps_readb
c_func
(paren
id|PDDR
)paren
suffix:semicolon
r_if
c_cond
(paren
id|value
)paren
(brace
id|port_d
op_or_assign
id|EDB_PD3_LCDBL
suffix:semicolon
)brace
r_else
(brace
id|port_d
op_and_assign
op_complement
id|EDB_PD3_LCDBL
suffix:semicolon
)brace
id|clps_writeb
c_func
(paren
id|port_d
comma
id|PDDR
)paren
suffix:semicolon
)brace
r_return
id|count
suffix:semicolon
)brace
DECL|function|clps711x_guess_lcd_params
r_static
r_void
id|__init
id|clps711x_guess_lcd_params
c_func
(paren
r_struct
id|fb_info
op_star
id|info
)paren
(brace
r_int
r_int
id|lcdcon
comma
id|syscon
comma
id|size
suffix:semicolon
r_int
r_int
id|phys_base
op_assign
id|PAGE_OFFSET
suffix:semicolon
r_void
op_star
id|virt_base
op_assign
(paren
r_void
op_star
)paren
id|PAGE_OFFSET
suffix:semicolon
id|info-&gt;var.xres_virtual
op_assign
l_int|640
suffix:semicolon
id|info-&gt;var.yres_virtual
op_assign
l_int|240
suffix:semicolon
id|info-&gt;var.bits_per_pixel
op_assign
l_int|4
suffix:semicolon
id|info-&gt;var.activate
op_assign
id|FB_ACTIVATE_NOW
suffix:semicolon
id|info-&gt;var.height
op_assign
op_minus
l_int|1
suffix:semicolon
id|info-&gt;var.width
op_assign
op_minus
l_int|1
suffix:semicolon
id|info-&gt;var.pixclock
op_assign
l_int|93006
suffix:semicolon
multiline_comment|/* 10.752MHz pixel clock */
multiline_comment|/*&n;&t; * If the LCD controller is already running, decode the values&n;&t; * in LCDCON to xres/yres/bpp/pixclock/acprescale&n;&t; */
id|syscon
op_assign
id|clps_readl
c_func
(paren
id|SYSCON1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|syscon
op_amp
id|SYSCON1_LCDEN
)paren
(brace
id|lcdcon
op_assign
id|clps_readl
c_func
(paren
id|LCDCON
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Decode GSMD and GSEN bits to bits per pixel&n;&t;&t; */
r_switch
c_cond
(paren
id|lcdcon
op_amp
(paren
id|LCDCON_GSMD
op_or
id|LCDCON_GSEN
)paren
)paren
(brace
r_case
id|LCDCON_GSMD
op_or
id|LCDCON_GSEN
suffix:colon
id|info-&gt;var.bits_per_pixel
op_assign
l_int|4
suffix:semicolon
r_break
suffix:semicolon
r_case
id|LCDCON_GSEN
suffix:colon
id|info-&gt;var.bits_per_pixel
op_assign
l_int|2
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|info-&gt;var.bits_per_pixel
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Decode xres/yres&n;&t;&t; */
id|info-&gt;var.xres_virtual
op_assign
(paren
(paren
(paren
id|lcdcon
op_rshift
l_int|13
)paren
op_amp
l_int|0x3f
)paren
op_plus
l_int|1
)paren
op_star
l_int|16
suffix:semicolon
id|info-&gt;var.yres_virtual
op_assign
(paren
(paren
(paren
id|lcdcon
op_amp
l_int|0x1fff
)paren
op_plus
l_int|1
)paren
op_star
l_int|128
)paren
op_div
(paren
id|info-&gt;var.xres_virtual
op_star
id|info-&gt;var.bits_per_pixel
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Calculate pixclock&n;&t;&t; */
id|info-&gt;var.pixclock
op_assign
(paren
(paren
(paren
id|lcdcon
op_rshift
l_int|19
)paren
op_amp
l_int|0x3f
)paren
op_plus
l_int|1
)paren
op_star
l_int|244140
op_div
l_int|9
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Grab AC prescale&n;&t;&t; */
id|lcd_ac_prescale
op_assign
(paren
id|lcdcon
op_rshift
l_int|25
)paren
op_amp
l_int|0x1f
suffix:semicolon
)brace
id|info-&gt;var.xres
op_assign
id|info-&gt;var.xres_virtual
suffix:semicolon
id|info-&gt;var.yres
op_assign
id|info-&gt;var.yres_virtual
suffix:semicolon
id|info-&gt;var.grayscale
op_assign
id|info-&gt;var.bits_per_pixel
OG
l_int|1
suffix:semicolon
id|size
op_assign
id|info-&gt;var.xres
op_star
id|info-&gt;var.yres
op_star
id|info-&gt;var.bits_per_pixel
op_div
l_int|8
suffix:semicolon
multiline_comment|/*&n;&t; * Might be worth checking to see if we can use the on-board&n;&t; * RAM if size here...&n;&t; * CLPS7110 - no on-board SRAM&n;&t; * EP7212   - 38400 bytes&n;&t; */
r_if
c_cond
(paren
id|size
OL
l_int|38400
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;CLPS711xFB: could use on-board SRAM?&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|syscon
op_amp
id|SYSCON1_LCDEN
)paren
op_eq
l_int|0
)paren
(brace
multiline_comment|/*&n;&t;&t; * The display isn&squot;t running.  Ensure that&n;&t;&t; * the display memory is empty.&n;&t;&t; */
id|memset
c_func
(paren
id|virt_base
comma
l_int|0
comma
id|size
)paren
suffix:semicolon
)brace
id|info-&gt;screen_base
op_assign
id|virt_base
suffix:semicolon
id|info-&gt;fix.smem_start
op_assign
id|phys_base
suffix:semicolon
id|info-&gt;fix.smem_len
op_assign
id|PAGE_ALIGN
c_func
(paren
id|size
)paren
suffix:semicolon
id|info-&gt;fix.type
op_assign
id|FB_TYPE_PACKED_PIXELS
suffix:semicolon
)brace
DECL|function|clps711xfb_init
r_int
id|__init
id|clps711xfb_init
c_func
(paren
r_void
)paren
(brace
r_int
id|err
op_assign
op_minus
id|ENOMEM
suffix:semicolon
id|cfb
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|cfb
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cfb
)paren
r_goto
id|out
suffix:semicolon
id|memset
c_func
(paren
id|cfb
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|cfb
)paren
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|cfb-&gt;fix.id
comma
l_string|&quot;clps711x&quot;
)paren
suffix:semicolon
id|cfb-&gt;fbops
op_assign
op_amp
id|clps7111fb_ops
suffix:semicolon
id|cfb-&gt;flags
op_assign
id|FBINFO_FLAG_DEFAULT
suffix:semicolon
id|clps711x_guess_lcd_params
c_func
(paren
id|cfb
)paren
suffix:semicolon
id|fb_alloc_cmap
c_func
(paren
op_amp
id|cfb-&gt;cmap
comma
id|CMAP_MAX_SIZE
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Register the /proc entries. */
id|clps7111fb_backlight_proc_entry
op_assign
id|create_proc_entry
c_func
(paren
l_string|&quot;backlight&quot;
comma
l_int|0444
comma
op_amp
id|proc_root
)paren
suffix:semicolon
r_if
c_cond
(paren
id|clps7111fb_backlight_proc_entry
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Couldn&squot;t create the /proc entry for the backlight.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|clps7111fb_backlight_proc_entry-&gt;read_proc
op_assign
op_amp
id|clps7111fb_proc_backlight_read
suffix:semicolon
id|clps7111fb_backlight_proc_entry-&gt;write_proc
op_assign
op_amp
id|clps7111fb_proc_backlight_write
suffix:semicolon
multiline_comment|/*&n;&t; * Power up the LCD&n;&t; */
r_if
c_cond
(paren
id|machine_is_p720t
c_func
(paren
)paren
)paren
(brace
id|PLD_LCDEN
op_assign
id|PLD_LCDEN_EN
suffix:semicolon
id|PLD_PWR
op_or_assign
(paren
id|PLD_S4_ON
op_or
id|PLD_S3_ON
op_or
id|PLD_S2_ON
op_or
id|PLD_S1_ON
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|machine_is_edb7211
c_func
(paren
)paren
)paren
(brace
multiline_comment|/* Power up the LCD panel. */
id|clps_writeb
c_func
(paren
id|clps_readb
c_func
(paren
id|PDDR
)paren
op_or
id|EDB_PD2_LCDEN
comma
id|PDDR
)paren
suffix:semicolon
multiline_comment|/* Delay for a little while. */
id|udelay
c_func
(paren
l_int|100
)paren
suffix:semicolon
multiline_comment|/* Power up the LCD DC-DC converter. */
id|clps_writeb
c_func
(paren
id|clps_readb
c_func
(paren
id|PDDR
)paren
op_or
id|EDB_PD1_LCD_DC_DC_EN
comma
id|PDDR
)paren
suffix:semicolon
multiline_comment|/* Turn on the LCD backlight. */
id|clps_writeb
c_func
(paren
id|clps_readb
c_func
(paren
id|PDDR
)paren
op_or
id|EDB_PD3_LCDBL
comma
id|PDDR
)paren
suffix:semicolon
)brace
id|err
op_assign
id|register_framebuffer
c_func
(paren
id|cfb
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|err
suffix:semicolon
)brace
DECL|function|clps711xfb_exit
r_static
r_void
id|__exit
id|clps711xfb_exit
c_func
(paren
r_void
)paren
(brace
id|unregister_framebuffer
c_func
(paren
id|cfb
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|cfb
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Power down the LCD&n;&t; */
r_if
c_cond
(paren
id|machine_is_p720t
c_func
(paren
)paren
)paren
(brace
id|PLD_LCDEN
op_assign
l_int|0
suffix:semicolon
id|PLD_PWR
op_and_assign
op_complement
(paren
id|PLD_S4_ON
op_or
id|PLD_S3_ON
op_or
id|PLD_S2_ON
op_or
id|PLD_S1_ON
)paren
suffix:semicolon
)brace
)brace
macro_line|#ifdef MODULE
DECL|variable|clps711xfb_init
id|module_init
c_func
(paren
id|clps711xfb_init
)paren
suffix:semicolon
macro_line|#endif
DECL|variable|clps711xfb_exit
id|module_exit
c_func
(paren
id|clps711xfb_exit
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Russell King &lt;rmk@arm.linux.org.uk&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;CLPS711x framebuffer driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
