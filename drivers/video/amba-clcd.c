multiline_comment|/*&n; *  linux/drivers/video/amba-clcd.c&n; *&n; * Copyright (C) 2001 ARM Limited, by David A Rusling&n; * Updated to 2.5, Deep Blue Solutions Ltd.&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file COPYING in the main directory of this archive&n; * for more details.&n; *&n; *  ARM PrimeCell PL110 Color LCD Controller&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/fb.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;asm/hardware/amba.h&gt;
macro_line|#include &lt;asm/hardware/clock.h&gt;
macro_line|#include &lt;asm/hardware/amba_clcd.h&gt;
DECL|macro|to_clcd
mdefine_line|#define to_clcd(info)&t;container_of(info, struct clcd_fb, fb)
multiline_comment|/* This is limited to 16 characters when displayed by X startup */
DECL|variable|clcd_name
r_static
r_const
r_char
op_star
id|clcd_name
op_assign
l_string|&quot;CLCD FB&quot;
suffix:semicolon
multiline_comment|/*&n; * Unfortunately, the enable/disable functions may be called either from&n; * process or IRQ context, and we _need_ to delay.  This is _not_ good.&n; */
DECL|function|clcdfb_sleep
r_static
r_inline
r_void
id|clcdfb_sleep
c_func
(paren
r_int
r_int
id|ms
)paren
(brace
r_if
c_cond
(paren
id|in_atomic
c_func
(paren
)paren
)paren
(brace
id|mdelay
c_func
(paren
id|ms
)paren
suffix:semicolon
)brace
r_else
(brace
id|msleep
c_func
(paren
id|ms
)paren
suffix:semicolon
)brace
)brace
DECL|function|clcdfb_set_start
r_static
r_inline
r_void
id|clcdfb_set_start
c_func
(paren
r_struct
id|clcd_fb
op_star
id|fb
)paren
(brace
r_int
r_int
id|ustart
op_assign
id|fb-&gt;fb.fix.smem_start
suffix:semicolon
r_int
r_int
id|lstart
suffix:semicolon
id|ustart
op_add_assign
id|fb-&gt;fb.var.yoffset
op_star
id|fb-&gt;fb.fix.line_length
suffix:semicolon
id|lstart
op_assign
id|ustart
op_plus
id|fb-&gt;fb.var.yres
op_star
id|fb-&gt;fb.fix.line_length
op_div
l_int|2
suffix:semicolon
id|writel
c_func
(paren
id|ustart
comma
id|fb-&gt;regs
op_plus
id|CLCD_UBAS
)paren
suffix:semicolon
id|writel
c_func
(paren
id|lstart
comma
id|fb-&gt;regs
op_plus
id|CLCD_LBAS
)paren
suffix:semicolon
)brace
DECL|function|clcdfb_disable
r_static
r_void
id|clcdfb_disable
c_func
(paren
r_struct
id|clcd_fb
op_star
id|fb
)paren
(brace
id|u32
id|val
suffix:semicolon
r_if
c_cond
(paren
id|fb-&gt;board-&gt;disable
)paren
id|fb-&gt;board
op_member_access_from_pointer
id|disable
c_func
(paren
id|fb
)paren
suffix:semicolon
id|val
op_assign
id|readl
c_func
(paren
id|fb-&gt;regs
op_plus
id|CLCD_CNTL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|val
op_amp
id|CNTL_LCDPWR
)paren
(brace
id|val
op_and_assign
op_complement
id|CNTL_LCDPWR
suffix:semicolon
id|writel
c_func
(paren
id|val
comma
id|fb-&gt;regs
op_plus
id|CLCD_CNTL
)paren
suffix:semicolon
id|clcdfb_sleep
c_func
(paren
l_int|20
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|val
op_amp
id|CNTL_LCDEN
)paren
(brace
id|val
op_and_assign
op_complement
id|CNTL_LCDEN
suffix:semicolon
id|writel
c_func
(paren
id|val
comma
id|fb-&gt;regs
op_plus
id|CLCD_CNTL
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Disable CLCD clock source.&n;&t; */
id|clk_disable
c_func
(paren
id|fb-&gt;clk
)paren
suffix:semicolon
)brace
DECL|function|clcdfb_enable
r_static
r_void
id|clcdfb_enable
c_func
(paren
r_struct
id|clcd_fb
op_star
id|fb
comma
id|u32
id|cntl
)paren
(brace
multiline_comment|/*&n;&t; * Enable the CLCD clock source.&n;&t; */
id|clk_enable
c_func
(paren
id|fb-&gt;clk
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Bring up by first enabling..&n;&t; */
id|cntl
op_or_assign
id|CNTL_LCDEN
suffix:semicolon
id|writel
c_func
(paren
id|cntl
comma
id|fb-&gt;regs
op_plus
id|CLCD_CNTL
)paren
suffix:semicolon
id|clcdfb_sleep
c_func
(paren
l_int|20
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * and now apply power.&n;&t; */
id|cntl
op_or_assign
id|CNTL_LCDPWR
suffix:semicolon
id|writel
c_func
(paren
id|cntl
comma
id|fb-&gt;regs
op_plus
id|CLCD_CNTL
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * finally, enable the interface.&n;&t; */
r_if
c_cond
(paren
id|fb-&gt;board-&gt;enable
)paren
id|fb-&gt;board
op_member_access_from_pointer
id|enable
c_func
(paren
id|fb
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|clcdfb_set_bitfields
id|clcdfb_set_bitfields
c_func
(paren
r_struct
id|clcd_fb
op_star
id|fb
comma
r_struct
id|fb_var_screeninfo
op_star
id|var
)paren
(brace
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|var-&gt;transp
comma
l_int|0
comma
r_sizeof
(paren
id|var-&gt;transp
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|var-&gt;red
comma
l_int|0
comma
r_sizeof
(paren
id|var-&gt;red
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|var-&gt;green
comma
l_int|0
comma
r_sizeof
(paren
id|var-&gt;green
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|var-&gt;blue
comma
l_int|0
comma
r_sizeof
(paren
id|var-&gt;blue
)paren
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|var-&gt;bits_per_pixel
)paren
(brace
r_case
l_int|1
suffix:colon
r_case
l_int|2
suffix:colon
r_case
l_int|4
suffix:colon
r_case
l_int|8
suffix:colon
id|var-&gt;red.length
op_assign
l_int|8
suffix:semicolon
id|var-&gt;red.offset
op_assign
l_int|0
suffix:semicolon
id|var-&gt;green.length
op_assign
l_int|8
suffix:semicolon
id|var-&gt;green.offset
op_assign
l_int|0
suffix:semicolon
id|var-&gt;blue.length
op_assign
l_int|8
suffix:semicolon
id|var-&gt;blue.offset
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|16
suffix:colon
id|var-&gt;red.length
op_assign
l_int|5
suffix:semicolon
id|var-&gt;green.length
op_assign
l_int|5
suffix:semicolon
id|var-&gt;blue.length
op_assign
l_int|5
suffix:semicolon
r_if
c_cond
(paren
id|fb-&gt;panel-&gt;cntl
op_amp
id|CNTL_BGR
)paren
(brace
id|var-&gt;red.offset
op_assign
l_int|10
suffix:semicolon
id|var-&gt;green.offset
op_assign
l_int|5
suffix:semicolon
id|var-&gt;blue.offset
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|var-&gt;red.offset
op_assign
l_int|0
suffix:semicolon
id|var-&gt;green.offset
op_assign
l_int|5
suffix:semicolon
id|var-&gt;blue.offset
op_assign
l_int|10
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
id|fb-&gt;panel-&gt;cntl
op_amp
id|CNTL_LCDTFT
)paren
(brace
id|var-&gt;red.length
op_assign
l_int|8
suffix:semicolon
id|var-&gt;green.length
op_assign
l_int|8
suffix:semicolon
id|var-&gt;blue.length
op_assign
l_int|8
suffix:semicolon
r_if
c_cond
(paren
id|fb-&gt;panel-&gt;cntl
op_amp
id|CNTL_BGR
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
)brace
r_else
(brace
id|var-&gt;red.offset
op_assign
l_int|0
suffix:semicolon
id|var-&gt;green.offset
op_assign
l_int|8
suffix:semicolon
id|var-&gt;blue.offset
op_assign
l_int|16
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
r_default
suffix:colon
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|clcdfb_check_var
r_static
r_int
id|clcdfb_check_var
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
r_struct
id|clcd_fb
op_star
id|fb
op_assign
id|to_clcd
c_func
(paren
id|info
)paren
suffix:semicolon
r_int
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|fb-&gt;board-&gt;check
)paren
id|ret
op_assign
id|fb-&gt;board
op_member_access_from_pointer
id|check
c_func
(paren
id|fb
comma
id|var
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
l_int|0
)paren
id|ret
op_assign
id|clcdfb_set_bitfields
c_func
(paren
id|fb
comma
id|var
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|clcdfb_set_par
r_static
r_int
id|clcdfb_set_par
c_func
(paren
r_struct
id|fb_info
op_star
id|info
)paren
(brace
r_struct
id|clcd_fb
op_star
id|fb
op_assign
id|to_clcd
c_func
(paren
id|info
)paren
suffix:semicolon
r_struct
id|clcd_regs
id|regs
suffix:semicolon
id|fb-&gt;fb.fix.line_length
op_assign
id|fb-&gt;fb.var.xres_virtual
op_star
id|fb-&gt;fb.var.bits_per_pixel
op_div
l_int|8
suffix:semicolon
r_if
c_cond
(paren
id|fb-&gt;fb.var.bits_per_pixel
op_le
l_int|8
)paren
id|fb-&gt;fb.fix.visual
op_assign
id|FB_VISUAL_PSEUDOCOLOR
suffix:semicolon
r_else
id|fb-&gt;fb.fix.visual
op_assign
id|FB_VISUAL_TRUECOLOR
suffix:semicolon
id|fb-&gt;board
op_member_access_from_pointer
id|decode
c_func
(paren
id|fb
comma
op_amp
id|regs
)paren
suffix:semicolon
id|clcdfb_disable
c_func
(paren
id|fb
)paren
suffix:semicolon
id|writel
c_func
(paren
id|regs.tim0
comma
id|fb-&gt;regs
op_plus
id|CLCD_TIM0
)paren
suffix:semicolon
id|writel
c_func
(paren
id|regs.tim1
comma
id|fb-&gt;regs
op_plus
id|CLCD_TIM1
)paren
suffix:semicolon
id|writel
c_func
(paren
id|regs.tim2
comma
id|fb-&gt;regs
op_plus
id|CLCD_TIM2
)paren
suffix:semicolon
id|writel
c_func
(paren
id|regs.tim3
comma
id|fb-&gt;regs
op_plus
id|CLCD_TIM3
)paren
suffix:semicolon
id|clcdfb_set_start
c_func
(paren
id|fb
)paren
suffix:semicolon
id|clk_set_rate
c_func
(paren
id|fb-&gt;clk
comma
l_int|1000000000
op_div
id|regs.pixclock
)paren
suffix:semicolon
id|fb-&gt;clcd_cntl
op_assign
id|regs.cntl
suffix:semicolon
id|clcdfb_enable
c_func
(paren
id|fb
comma
id|regs.cntl
)paren
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;CLCD: Registers set to&bslash;n&quot;
id|KERN_INFO
l_string|&quot;  %08x %08x %08x %08x&bslash;n&quot;
id|KERN_INFO
l_string|&quot;  %08x %08x %08x %08x&bslash;n&quot;
comma
id|readl
c_func
(paren
id|fb-&gt;regs
op_plus
id|CLCD_TIM0
)paren
comma
id|readl
c_func
(paren
id|fb-&gt;regs
op_plus
id|CLCD_TIM1
)paren
comma
id|readl
c_func
(paren
id|fb-&gt;regs
op_plus
id|CLCD_TIM2
)paren
comma
id|readl
c_func
(paren
id|fb-&gt;regs
op_plus
id|CLCD_TIM3
)paren
comma
id|readl
c_func
(paren
id|fb-&gt;regs
op_plus
id|CLCD_UBAS
)paren
comma
id|readl
c_func
(paren
id|fb-&gt;regs
op_plus
id|CLCD_LBAS
)paren
comma
id|readl
c_func
(paren
id|fb-&gt;regs
op_plus
id|CLCD_IENB
)paren
comma
id|readl
c_func
(paren
id|fb-&gt;regs
op_plus
id|CLCD_CNTL
)paren
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|convert_bitfield
r_static
r_inline
id|u32
id|convert_bitfield
c_func
(paren
r_int
id|val
comma
r_struct
id|fb_bitfield
op_star
id|bf
)paren
(brace
r_int
r_int
id|mask
op_assign
(paren
l_int|1
op_lshift
id|bf-&gt;length
)paren
op_minus
l_int|1
suffix:semicolon
r_return
(paren
id|val
op_rshift
(paren
l_int|16
op_minus
id|bf-&gt;length
)paren
op_amp
id|mask
)paren
op_lshift
id|bf-&gt;offset
suffix:semicolon
)brace
multiline_comment|/*&n; *  Set a single color register. The values supplied have a 16 bit&n; *  magnitude.  Return != 0 for invalid regno.&n; */
r_static
r_int
DECL|function|clcdfb_setcolreg
id|clcdfb_setcolreg
c_func
(paren
r_int
r_int
id|regno
comma
r_int
r_int
id|red
comma
r_int
r_int
id|green
comma
r_int
r_int
id|blue
comma
r_int
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
id|clcd_fb
op_star
id|fb
op_assign
id|to_clcd
c_func
(paren
id|info
)paren
suffix:semicolon
r_if
c_cond
(paren
id|regno
OL
l_int|16
)paren
id|fb-&gt;cmap
(braket
id|regno
)braket
op_assign
id|convert_bitfield
c_func
(paren
id|transp
comma
op_amp
id|fb-&gt;fb.var.transp
)paren
op_or
id|convert_bitfield
c_func
(paren
id|blue
comma
op_amp
id|fb-&gt;fb.var.blue
)paren
op_or
id|convert_bitfield
c_func
(paren
id|green
comma
op_amp
id|fb-&gt;fb.var.green
)paren
op_or
id|convert_bitfield
c_func
(paren
id|red
comma
op_amp
id|fb-&gt;fb.var.red
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fb-&gt;fb.var.bits_per_pixel
op_eq
l_int|8
op_logical_and
id|regno
OL
l_int|256
)paren
(brace
r_int
id|hw_reg
op_assign
id|CLCD_PALETTE
op_plus
(paren
(paren
id|regno
op_star
l_int|2
)paren
op_amp
op_complement
l_int|3
)paren
suffix:semicolon
id|u32
id|val
comma
id|mask
comma
id|newval
suffix:semicolon
id|newval
op_assign
(paren
id|red
op_rshift
l_int|11
)paren
op_amp
l_int|0x001f
suffix:semicolon
id|newval
op_or_assign
(paren
id|green
op_rshift
l_int|6
)paren
op_amp
l_int|0x03e0
suffix:semicolon
id|newval
op_or_assign
(paren
id|blue
op_rshift
l_int|1
)paren
op_amp
l_int|0x7c00
suffix:semicolon
multiline_comment|/*&n;&t;&t; * 3.2.11: if we&squot;re configured for big endian&n;&t;&t; * byte order, the palette entries are swapped.&n;&t;&t; */
r_if
c_cond
(paren
id|fb-&gt;clcd_cntl
op_amp
id|CNTL_BEBO
)paren
id|regno
op_xor_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|regno
op_amp
l_int|1
)paren
(brace
id|newval
op_lshift_assign
l_int|16
suffix:semicolon
id|mask
op_assign
l_int|0x0000ffff
suffix:semicolon
)brace
r_else
(brace
id|mask
op_assign
l_int|0xffff0000
suffix:semicolon
)brace
id|val
op_assign
id|readl
c_func
(paren
id|fb-&gt;regs
op_plus
id|hw_reg
)paren
op_amp
id|mask
suffix:semicolon
id|writel
c_func
(paren
id|val
op_or
id|newval
comma
id|fb-&gt;regs
op_plus
id|hw_reg
)paren
suffix:semicolon
)brace
r_return
id|regno
OG
l_int|255
suffix:semicolon
)brace
multiline_comment|/*&n; *  Blank the screen if blank_mode != 0, else unblank. If blank == NULL&n; *  then the caller blanks by setting the CLUT (Color Look Up Table) to all&n; *  black. Return 0 if blanking succeeded, != 0 if un-/blanking failed due&n; *  to e.g. a video mode which doesn&squot;t support it. Implements VESA suspend&n; *  and powerdown modes on hardware that supports disabling hsync/vsync:&n; *    blank_mode == 2: suspend vsync&n; *    blank_mode == 3: suspend hsync&n; *    blank_mode == 4: powerdown&n; */
DECL|function|clcdfb_blank
r_static
r_int
id|clcdfb_blank
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
id|clcd_fb
op_star
id|fb
op_assign
id|to_clcd
c_func
(paren
id|info
)paren
suffix:semicolon
r_if
c_cond
(paren
id|blank_mode
op_ne
l_int|0
)paren
(brace
id|clcdfb_disable
c_func
(paren
id|fb
)paren
suffix:semicolon
)brace
r_else
(brace
id|clcdfb_enable
c_func
(paren
id|fb
comma
id|fb-&gt;clcd_cntl
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|clcdfb_ops
r_static
r_struct
id|fb_ops
id|clcdfb_ops
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
id|clcdfb_check_var
comma
dot
id|fb_set_par
op_assign
id|clcdfb_set_par
comma
dot
id|fb_setcolreg
op_assign
id|clcdfb_setcolreg
comma
dot
id|fb_blank
op_assign
id|clcdfb_blank
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
DECL|function|clcdfb_register
r_static
r_int
id|clcdfb_register
c_func
(paren
r_struct
id|clcd_fb
op_star
id|fb
)paren
(brace
r_int
id|ret
suffix:semicolon
id|fb-&gt;clk
op_assign
id|clk_get
c_func
(paren
op_amp
id|fb-&gt;dev-&gt;dev
comma
l_string|&quot;CLCDCLK&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|fb-&gt;clk
)paren
)paren
(brace
id|ret
op_assign
id|PTR_ERR
c_func
(paren
id|fb-&gt;clk
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|ret
op_assign
id|clk_use
c_func
(paren
id|fb-&gt;clk
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_goto
id|free_clk
suffix:semicolon
id|fb-&gt;fb.fix.mmio_start
op_assign
id|fb-&gt;dev-&gt;res.start
suffix:semicolon
id|fb-&gt;fb.fix.mmio_len
op_assign
id|SZ_4K
suffix:semicolon
id|fb-&gt;regs
op_assign
id|ioremap
c_func
(paren
id|fb-&gt;fb.fix.mmio_start
comma
id|fb-&gt;fb.fix.mmio_len
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fb-&gt;regs
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;CLCD: unable to remap registers&bslash;n&quot;
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|unuse_clk
suffix:semicolon
)brace
id|fb-&gt;fb.fbops
op_assign
op_amp
id|clcdfb_ops
suffix:semicolon
id|fb-&gt;fb.flags
op_assign
id|FBINFO_FLAG_DEFAULT
suffix:semicolon
id|fb-&gt;fb.pseudo_palette
op_assign
id|fb-&gt;cmap
suffix:semicolon
id|strncpy
c_func
(paren
id|fb-&gt;fb.fix.id
comma
id|clcd_name
comma
r_sizeof
(paren
id|fb-&gt;fb.fix.id
)paren
)paren
suffix:semicolon
id|fb-&gt;fb.fix.type
op_assign
id|FB_TYPE_PACKED_PIXELS
suffix:semicolon
id|fb-&gt;fb.fix.type_aux
op_assign
l_int|0
suffix:semicolon
id|fb-&gt;fb.fix.xpanstep
op_assign
l_int|0
suffix:semicolon
id|fb-&gt;fb.fix.ypanstep
op_assign
l_int|0
suffix:semicolon
id|fb-&gt;fb.fix.ywrapstep
op_assign
l_int|0
suffix:semicolon
id|fb-&gt;fb.fix.accel
op_assign
id|FB_ACCEL_NONE
suffix:semicolon
id|fb-&gt;fb.var.xres
op_assign
id|fb-&gt;panel-&gt;mode.xres
suffix:semicolon
id|fb-&gt;fb.var.yres
op_assign
id|fb-&gt;panel-&gt;mode.yres
suffix:semicolon
id|fb-&gt;fb.var.xres_virtual
op_assign
id|fb-&gt;panel-&gt;mode.xres
suffix:semicolon
id|fb-&gt;fb.var.yres_virtual
op_assign
id|fb-&gt;panel-&gt;mode.yres
suffix:semicolon
id|fb-&gt;fb.var.bits_per_pixel
op_assign
id|fb-&gt;panel-&gt;bpp
suffix:semicolon
id|fb-&gt;fb.var.grayscale
op_assign
id|fb-&gt;panel-&gt;grayscale
suffix:semicolon
id|fb-&gt;fb.var.pixclock
op_assign
id|fb-&gt;panel-&gt;mode.pixclock
suffix:semicolon
id|fb-&gt;fb.var.left_margin
op_assign
id|fb-&gt;panel-&gt;mode.left_margin
suffix:semicolon
id|fb-&gt;fb.var.right_margin
op_assign
id|fb-&gt;panel-&gt;mode.right_margin
suffix:semicolon
id|fb-&gt;fb.var.upper_margin
op_assign
id|fb-&gt;panel-&gt;mode.upper_margin
suffix:semicolon
id|fb-&gt;fb.var.lower_margin
op_assign
id|fb-&gt;panel-&gt;mode.lower_margin
suffix:semicolon
id|fb-&gt;fb.var.hsync_len
op_assign
id|fb-&gt;panel-&gt;mode.hsync_len
suffix:semicolon
id|fb-&gt;fb.var.vsync_len
op_assign
id|fb-&gt;panel-&gt;mode.vsync_len
suffix:semicolon
id|fb-&gt;fb.var.sync
op_assign
id|fb-&gt;panel-&gt;mode.sync
suffix:semicolon
id|fb-&gt;fb.var.vmode
op_assign
id|fb-&gt;panel-&gt;mode.vmode
suffix:semicolon
id|fb-&gt;fb.var.activate
op_assign
id|FB_ACTIVATE_NOW
suffix:semicolon
id|fb-&gt;fb.var.nonstd
op_assign
l_int|0
suffix:semicolon
id|fb-&gt;fb.var.height
op_assign
id|fb-&gt;panel-&gt;height
suffix:semicolon
id|fb-&gt;fb.var.width
op_assign
id|fb-&gt;panel-&gt;width
suffix:semicolon
id|fb-&gt;fb.var.accel_flags
op_assign
l_int|0
suffix:semicolon
id|fb-&gt;fb.monspecs.hfmin
op_assign
l_int|0
suffix:semicolon
id|fb-&gt;fb.monspecs.hfmax
op_assign
l_int|100000
suffix:semicolon
id|fb-&gt;fb.monspecs.vfmin
op_assign
l_int|0
suffix:semicolon
id|fb-&gt;fb.monspecs.vfmax
op_assign
l_int|400
suffix:semicolon
id|fb-&gt;fb.monspecs.dclkmin
op_assign
l_int|1000000
suffix:semicolon
id|fb-&gt;fb.monspecs.dclkmax
op_assign
l_int|100000000
suffix:semicolon
multiline_comment|/*&n;&t; * Make sure that the bitfields are set appropriately.&n;&t; */
id|clcdfb_set_bitfields
c_func
(paren
id|fb
comma
op_amp
id|fb-&gt;fb.var
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Allocate colourmap.&n;&t; */
id|fb_alloc_cmap
c_func
(paren
op_amp
id|fb-&gt;fb.cmap
comma
l_int|256
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Ensure interrupts are disabled.&n;&t; */
id|writel
c_func
(paren
l_int|0
comma
id|fb-&gt;regs
op_plus
id|CLCD_IENB
)paren
suffix:semicolon
id|fb_set_var
c_func
(paren
op_amp
id|fb-&gt;fb
comma
op_amp
id|fb-&gt;fb.var
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;CLCD: %s hardware, %s display&bslash;n&quot;
comma
id|fb-&gt;board-&gt;name
comma
id|fb-&gt;panel-&gt;mode.name
)paren
suffix:semicolon
id|ret
op_assign
id|register_framebuffer
c_func
(paren
op_amp
id|fb-&gt;fb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
l_int|0
)paren
r_goto
id|out
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;CLCD: cannot register framebuffer (%d)&bslash;n&quot;
comma
id|ret
)paren
suffix:semicolon
id|iounmap
c_func
(paren
id|fb-&gt;regs
)paren
suffix:semicolon
id|unuse_clk
suffix:colon
id|clk_unuse
c_func
(paren
id|fb-&gt;clk
)paren
suffix:semicolon
id|free_clk
suffix:colon
id|clk_put
c_func
(paren
id|fb-&gt;clk
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|clcdfb_probe
r_static
r_int
id|clcdfb_probe
c_func
(paren
r_struct
id|amba_device
op_star
id|dev
comma
r_void
op_star
id|id
)paren
(brace
r_struct
id|clcd_board
op_star
id|board
op_assign
id|dev-&gt;dev.platform_data
suffix:semicolon
r_struct
id|clcd_fb
op_star
id|fb
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|board
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|ret
op_assign
id|amba_request_regions
c_func
(paren
id|dev
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;CLCD: unable to reserve regs region&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|fb
op_assign
(paren
r_struct
id|clcd_fb
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|clcd_fb
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fb
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;CLCD: could not allocate new clcd_fb struct&bslash;n&quot;
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|free_region
suffix:semicolon
)brace
id|memset
c_func
(paren
id|fb
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|clcd_fb
)paren
)paren
suffix:semicolon
id|fb-&gt;dev
op_assign
id|dev
suffix:semicolon
id|fb-&gt;board
op_assign
id|board
suffix:semicolon
id|ret
op_assign
id|fb-&gt;board
op_member_access_from_pointer
id|setup
c_func
(paren
id|fb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_goto
id|free_fb
suffix:semicolon
id|ret
op_assign
id|clcdfb_register
c_func
(paren
id|fb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
l_int|0
)paren
(brace
id|amba_set_drvdata
c_func
(paren
id|dev
comma
id|fb
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|fb-&gt;board
op_member_access_from_pointer
id|remove
c_func
(paren
id|fb
)paren
suffix:semicolon
id|free_fb
suffix:colon
id|kfree
c_func
(paren
id|fb
)paren
suffix:semicolon
id|free_region
suffix:colon
id|amba_release_regions
c_func
(paren
id|dev
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|clcdfb_remove
r_static
r_int
id|clcdfb_remove
c_func
(paren
r_struct
id|amba_device
op_star
id|dev
)paren
(brace
r_struct
id|clcd_fb
op_star
id|fb
op_assign
id|amba_get_drvdata
c_func
(paren
id|dev
)paren
suffix:semicolon
id|amba_set_drvdata
c_func
(paren
id|dev
comma
l_int|NULL
)paren
suffix:semicolon
id|clcdfb_disable
c_func
(paren
id|fb
)paren
suffix:semicolon
id|unregister_framebuffer
c_func
(paren
op_amp
id|fb-&gt;fb
)paren
suffix:semicolon
id|iounmap
c_func
(paren
id|fb-&gt;regs
)paren
suffix:semicolon
id|clk_unuse
c_func
(paren
id|fb-&gt;clk
)paren
suffix:semicolon
id|clk_put
c_func
(paren
id|fb-&gt;clk
)paren
suffix:semicolon
id|fb-&gt;board
op_member_access_from_pointer
id|remove
c_func
(paren
id|fb
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|fb
)paren
suffix:semicolon
id|amba_release_regions
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|clcdfb_id_table
r_static
r_struct
id|amba_id
id|clcdfb_id_table
(braket
)braket
op_assign
(brace
(brace
dot
id|id
op_assign
l_int|0x00041110
comma
dot
id|mask
op_assign
l_int|0x000fffff
comma
)brace
comma
(brace
l_int|0
comma
l_int|0
)brace
comma
)brace
suffix:semicolon
DECL|variable|clcd_driver
r_static
r_struct
id|amba_driver
id|clcd_driver
op_assign
(brace
dot
id|drv
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;clcd-pl110&quot;
comma
)brace
comma
dot
id|probe
op_assign
id|clcdfb_probe
comma
dot
id|remove
op_assign
id|clcdfb_remove
comma
dot
id|id_table
op_assign
id|clcdfb_id_table
comma
)brace
suffix:semicolon
DECL|function|amba_clcdfb_init
r_int
id|__init
id|amba_clcdfb_init
c_func
(paren
r_void
)paren
(brace
r_return
id|amba_driver_register
c_func
(paren
op_amp
id|clcd_driver
)paren
suffix:semicolon
)brace
macro_line|#ifdef MODULE
DECL|variable|amba_clcdfb_init
id|module_init
c_func
(paren
id|amba_clcdfb_init
)paren
suffix:semicolon
macro_line|#endif
DECL|function|amba_clcdfb_exit
r_static
r_void
id|__exit
id|amba_clcdfb_exit
c_func
(paren
r_void
)paren
(brace
id|amba_driver_unregister
c_func
(paren
op_amp
id|clcd_driver
)paren
suffix:semicolon
)brace
DECL|variable|amba_clcdfb_exit
id|module_exit
c_func
(paren
id|amba_clcdfb_exit
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;ARM PrimeCell PL110 CLCD core driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
