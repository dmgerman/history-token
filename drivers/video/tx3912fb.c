multiline_comment|/*&n; *  drivers/video/tx3912fb.c&n; *&n; *  Copyright (C) 1999 Harald Koerfgen&n; *  Copyright (C) 2001 Steven Hill (sjhill@realitydiluted.com)&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License. See the file COPYING in the main directory of this archive for&n; * more details.&n; *&n; *  Framebuffer for LCD controller in TMPR3912/05 and PR31700 processors&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pm.h&gt;
macro_line|#include &lt;linux/fb.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/tx3912.h&gt;
macro_line|#include &lt;video/tx3912.h&gt;
multiline_comment|/*&n; * Frame buffer, palette and console structures&n; */
DECL|variable|fb_info
r_static
r_struct
id|fb_info
id|fb_info
suffix:semicolon
DECL|variable|cfb8
r_static
id|u32
id|cfb8
(braket
l_int|16
)braket
suffix:semicolon
DECL|variable|__initdata
r_static
r_struct
id|fb_fix_screeninfo
id|tx3912fb_fix
id|__initdata
op_assign
(brace
dot
id|id
op_assign
l_string|&quot;tx3912fb&quot;
comma
macro_line|#ifdef CONFIG_NINO_16MB
dot
id|smem_len
op_assign
(paren
l_int|240
op_star
l_int|320
)paren
comma
macro_line|#else
dot
id|smem_len
op_assign
(paren
(paren
l_int|240
op_star
l_int|320
)paren
op_div
l_int|2
)paren
comma
macro_line|#endif
dot
id|type
op_assign
id|FB_TYPE_PACKED_PIXELS
comma
dot
id|visual
op_assign
id|FB_VISUAL_TRUECOLOR
comma
dot
id|xpanstep
op_assign
l_int|1
comma
dot
id|ypanstep
op_assign
l_int|1
comma
dot
id|ywrapstep
op_assign
l_int|1
comma
dot
id|accel
op_assign
id|FB_ACCEL_NONE
comma
)brace
suffix:semicolon
DECL|variable|tx3912fb_var
r_static
r_struct
id|fb_var_screeninfo
id|tx3912fb_var
op_assign
(brace
dot
id|xres
op_assign
l_int|240
comma
dot
id|yres
op_assign
l_int|320
comma
dot
id|xres_virtual
op_assign
l_int|240
comma
dot
id|yres_virtual
op_assign
l_int|320
comma
macro_line|#ifdef CONFIG_NINO_16MB
dot
id|bits_per_pixel
op_assign
l_int|8
comma
dot
id|red
op_assign
(brace
l_int|5
comma
l_int|3
comma
l_int|0
)brace
comma
multiline_comment|/* RGB 332 */
dot
id|green
op_assign
(brace
l_int|2
comma
l_int|3
comma
l_int|0
)brace
comma
dot
id|blue
op_assign
(brace
l_int|0
comma
l_int|2
comma
l_int|0
)brace
comma
macro_line|#else
dot
id|bits_per_pixel
op_assign
l_int|4
comma
macro_line|#endif
dot
id|activate
op_assign
id|FB_ACTIVATE_NOW
comma
dot
id|width
op_assign
op_minus
l_int|1
comma
dot
id|height
op_assign
op_minus
l_int|1
comma
dot
id|pixclock
op_assign
l_int|20000
comma
dot
id|left_margin
op_assign
l_int|64
comma
dot
id|right_margin
op_assign
l_int|64
comma
dot
id|upper_margin
op_assign
l_int|32
comma
dot
id|lower_margin
op_assign
l_int|32
comma
dot
id|hsync_len
op_assign
l_int|64
comma
dot
id|vsync_len
op_assign
l_int|2
comma
dot
id|vmode
op_assign
id|FB_VMODE_NONINTERLACED
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * Interface used by the world&n; */
r_int
id|tx3912fb_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_int
id|tx3912fb_setcolreg
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
multiline_comment|/*&n; * Macros&n; */
DECL|macro|get_line_length
mdefine_line|#define get_line_length(xres_virtual, bpp) &bslash;&n;                (u_long) (((int) xres_virtual * (int) bpp + 7) &gt;&gt; 3)
multiline_comment|/*&n; * Frame buffer operations structure used by console driver&n; */
DECL|variable|tx3912fb_ops
r_static
r_struct
id|fb_ops
id|tx3912fb_ops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|fb_setcolreg
op_assign
id|tx3912fb_setcolreg
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
DECL|function|tx3912fb_check_var
r_static
r_int
id|tx3912fb_check_var
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
multiline_comment|/*&n;&t; * Memory limit&n;&t; */
id|line_length
op_assign
id|get_line_length
c_func
(paren
id|var-&gt;xres_virtual
comma
id|var-&gt;bits_per_pixel
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|line_length
op_star
id|var-&gt;yres_virtual
)paren
OG
id|info-&gt;fix.smem_len
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|tx3912fb_set_par
r_static
r_int
id|tx3912fb_set_par
c_func
(paren
r_struct
id|fb_info
op_star
id|info
)paren
(brace
id|u_long
id|tx3912fb_paddr
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Disable the video logic */
id|outl
c_func
(paren
id|inl
c_func
(paren
id|TX3912_VIDEO_CTRL1
)paren
op_amp
op_complement
(paren
id|TX3912_VIDEO_CTRL1_ENVID
op_or
id|TX3912_VIDEO_CTRL1_DISPON
)paren
comma
id|TX3912_VIDEO_CTRL1
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|200
)paren
suffix:semicolon
multiline_comment|/* Set start address for DMA transfer */
id|outl
c_func
(paren
id|tx3912fb_paddr
comma
id|TX3912_VIDEO_CTRL3
)paren
suffix:semicolon
multiline_comment|/* Set end address for DMA transfer */
id|outl
c_func
(paren
(paren
id|tx3912fb_paddr
op_plus
id|tx3912fb_fix.smem_len
op_plus
l_int|1
)paren
comma
id|TX3912_VIDEO_CTRL4
)paren
suffix:semicolon
multiline_comment|/* Set the pixel depth */
r_switch
c_cond
(paren
id|info-&gt;var.bits_per_pixel
)paren
(brace
r_case
l_int|1
suffix:colon
multiline_comment|/* Monochrome */
id|outl
c_func
(paren
id|inl
c_func
(paren
id|TX3912_VIDEO_CTRL1
)paren
op_amp
op_complement
id|TX3912_VIDEO_CTRL1_BITSEL_MASK
comma
id|TX3912_VIDEO_CTRL1
)paren
suffix:semicolon
id|info-&gt;fix.visual
op_assign
id|FB_VISUAL_MONO10
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
multiline_comment|/* 4-bit gray */
id|outl
c_func
(paren
id|inl
c_func
(paren
id|TX3912_VIDEO_CTRL1
)paren
op_amp
op_complement
id|TX3912_VIDEO_CTRL1_BITSEL_MASK
comma
id|TX3912_VIDEO_CTRL1
)paren
suffix:semicolon
id|outl
c_func
(paren
id|inl
c_func
(paren
id|TX3912_VIDEO_CTRL1
)paren
op_or
id|TX3912_VIDEO_CTRL1_BITSEL_4BIT_GRAY
comma
id|TX3912_VIDEO_CTRL1
)paren
suffix:semicolon
id|info-&gt;fix.visual
op_assign
id|FB_VISUAL_TRUECOLOR
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|8
suffix:colon
multiline_comment|/* 8-bit color */
id|outl
c_func
(paren
id|inl
c_func
(paren
id|TX3912_VIDEO_CTRL1
)paren
op_amp
op_complement
id|TX3912_VIDEO_CTRL1_BITSEL_MASK
comma
id|TX3912_VIDEO_CTRL1
)paren
suffix:semicolon
id|outl
c_func
(paren
id|inl
c_func
(paren
id|TX3912_VIDEO_CTRL1
)paren
op_or
id|TX3912_VIDEO_CTRL1_BITSEL_8BIT_COLOR
comma
id|TX3912_VIDEO_CTRL1
)paren
suffix:semicolon
id|info-&gt;fix.visual
op_assign
id|FB_VISUAL_TRUECOLOR
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
r_default
suffix:colon
multiline_comment|/* 2-bit gray */
id|outl
c_func
(paren
id|inl
c_func
(paren
id|TX3912_VIDEO_CTRL1
)paren
op_amp
op_complement
id|TX3912_VIDEO_CTRL1_BITSEL_MASK
comma
id|TX3912_VIDEO_CTRL1
)paren
suffix:semicolon
id|outl
c_func
(paren
id|inl
c_func
(paren
id|TX3912_VIDEO_CTRL1
)paren
op_or
id|TX3912_VIDEO_CTRL1_BITSEL_2BIT_GRAY
comma
id|TX3912_VIDEO_CTRL1
)paren
suffix:semicolon
id|info-&gt;fix.visual
op_assign
id|FB_VISUAL_PSEUDOCOLOR
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* Enable the video clock */
id|outl
c_func
(paren
id|inl
c_func
(paren
id|TX3912_CLK_CTRL
)paren
op_or
id|TX3912_CLK_CTRL_ENVIDCLK
comma
id|TX3912_CLK_CTRL
)paren
suffix:semicolon
multiline_comment|/* Unfreeze video logic and enable DF toggle */
id|outl
c_func
(paren
id|inl
c_func
(paren
id|TX3912_VIDEO_CTRL1
)paren
op_amp
op_complement
(paren
id|TX3912_VIDEO_CTRL1_ENFREEZEFRAME
op_or
id|TX3912_VIDEO_CTRL1_DFMODE
)paren
comma
id|TX3912_VIDEO_CTRL1
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|200
)paren
suffix:semicolon
multiline_comment|/* Enable the video logic */
id|outl
c_func
(paren
id|inl
c_func
(paren
id|TX3912_VIDEO_CTRL1
)paren
op_or
(paren
id|TX3912_VIDEO_CTRL1_ENVID
op_or
id|TX3912_VIDEO_CTRL1_DISPON
)paren
comma
id|TX3912_VIDEO_CTRL1
)paren
suffix:semicolon
id|info-&gt;fix.line_length
op_assign
id|get_line_length
c_func
(paren
id|var-&gt;xres_virtual
comma
id|var-&gt;bits_per_pixel
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Set a single color register&n; */
DECL|function|tx3912fb_setcolreg
r_static
r_int
id|tx3912fb_setcolreg
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
r_if
c_cond
(paren
id|regno
OL
l_int|16
)paren
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
(paren
id|red
op_amp
l_int|0xe000
)paren
op_rshift
l_int|8
)paren
op_or
(paren
(paren
id|green
op_amp
l_int|0xe000
)paren
op_rshift
l_int|11
)paren
op_or
(paren
(paren
id|blue
op_amp
l_int|0xc000
)paren
op_rshift
l_int|14
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Initialization of the framebuffer&n; */
DECL|function|tx3912fb_init
r_int
id|__init
id|tx3912fb_init
c_func
(paren
r_void
)paren
(brace
id|u_long
id|tx3912fb_paddr
op_assign
l_int|0
suffix:semicolon
r_int
id|size
op_assign
(paren
id|info-&gt;var.bits_per_pixel
op_eq
l_int|8
)paren
ques
c_cond
l_int|256
suffix:colon
l_int|16
suffix:semicolon
multiline_comment|/* Disable the video logic */
id|outl
c_func
(paren
id|inl
c_func
(paren
id|TX3912_VIDEO_CTRL1
)paren
op_amp
op_complement
(paren
id|TX3912_VIDEO_CTRL1_ENVID
op_or
id|TX3912_VIDEO_CTRL1_DISPON
)paren
comma
id|TX3912_VIDEO_CTRL1
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|200
)paren
suffix:semicolon
multiline_comment|/* Set start address for DMA transfer */
id|outl
c_func
(paren
id|tx3912fb_paddr
comma
id|TX3912_VIDEO_CTRL3
)paren
suffix:semicolon
multiline_comment|/* Set end address for DMA transfer */
id|outl
c_func
(paren
(paren
id|tx3912fb_paddr
op_plus
id|tx3912fb_fix.smem_len
op_plus
l_int|1
)paren
comma
id|TX3912_VIDEO_CTRL4
)paren
suffix:semicolon
multiline_comment|/* Set the pixel depth */
r_switch
c_cond
(paren
id|tx3912fb_var.bits_per_pixel
)paren
(brace
r_case
l_int|1
suffix:colon
multiline_comment|/* Monochrome */
id|outl
c_func
(paren
id|inl
c_func
(paren
id|TX3912_VIDEO_CTRL1
)paren
op_amp
op_complement
id|TX3912_VIDEO_CTRL1_BITSEL_MASK
comma
id|TX3912_VIDEO_CTRL1
)paren
suffix:semicolon
id|tx3912fb_fix.visual
op_assign
id|FB_VISUAL_MONO10
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
multiline_comment|/* 4-bit gray */
id|outl
c_func
(paren
id|inl
c_func
(paren
id|TX3912_VIDEO_CTRL1
)paren
op_amp
op_complement
id|TX3912_VIDEO_CTRL1_BITSEL_MASK
comma
id|TX3912_VIDEO_CTRL1
)paren
suffix:semicolon
id|outl
c_func
(paren
id|inl
c_func
(paren
id|TX3912_VIDEO_CTRL1
)paren
op_or
id|TX3912_VIDEO_CTRL1_BITSEL_4BIT_GRAY
comma
id|TX3912_VIDEO_CTRL1
)paren
suffix:semicolon
id|tx3912fb_fix.visual
op_assign
id|FB_VISUAL_TRUECOLOR
suffix:semicolon
id|tx3912fb_fix.grayscale
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|8
suffix:colon
multiline_comment|/* 8-bit color */
id|outl
c_func
(paren
id|inl
c_func
(paren
id|TX3912_VIDEO_CTRL1
)paren
op_amp
op_complement
id|TX3912_VIDEO_CTRL1_BITSEL_MASK
comma
id|TX3912_VIDEO_CTRL1
)paren
suffix:semicolon
id|outl
c_func
(paren
id|inl
c_func
(paren
id|TX3912_VIDEO_CTRL1
)paren
op_or
id|TX3912_VIDEO_CTRL1_BITSEL_8BIT_COLOR
comma
id|TX3912_VIDEO_CTRL1
)paren
suffix:semicolon
id|tx3912fb_fix.visual
op_assign
id|FB_VISUAL_TRUECOLOR
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
r_default
suffix:colon
multiline_comment|/* 2-bit gray */
id|outl
c_func
(paren
id|inl
c_func
(paren
id|TX3912_VIDEO_CTRL1
)paren
op_amp
op_complement
id|TX3912_VIDEO_CTRL1_BITSEL_MASK
comma
id|TX3912_VIDEO_CTRL1
)paren
suffix:semicolon
id|outl
c_func
(paren
id|inl
c_func
(paren
id|TX3912_VIDEO_CTRL1
)paren
op_or
id|TX3912_VIDEO_CTRL1_BITSEL_2BIT_GRAY
comma
id|TX3912_VIDEO_CTRL1
)paren
suffix:semicolon
id|tx3912fb_fix.visual
op_assign
id|FB_VISUAL_PSEUDOCOLOR
suffix:semicolon
id|tx3912fb_fix.grayscale
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* Enable the video clock */
id|outl
c_func
(paren
id|inl
c_func
(paren
id|TX3912_CLK_CTRL
)paren
op_or
id|TX3912_CLK_CTRL_ENVIDCLK
comma
id|TX3912_CLK_CTRL
)paren
suffix:semicolon
multiline_comment|/* Unfreeze video logic and enable DF toggle */
id|outl
c_func
(paren
id|inl
c_func
(paren
id|TX3912_VIDEO_CTRL1
)paren
op_amp
op_complement
(paren
id|TX3912_VIDEO_CTRL1_ENFREEZEFRAME
op_or
id|TX3912_VIDEO_CTRL1_DFMODE
)paren
comma
id|TX3912_VIDEO_CTRL1
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|200
)paren
suffix:semicolon
multiline_comment|/* Clear the framebuffer */
id|memset
c_func
(paren
(paren
r_void
op_star
)paren
id|tx3912fb_fix.smem_start
comma
l_int|0xff
comma
id|tx3912fb_fix.smem_len
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|200
)paren
suffix:semicolon
multiline_comment|/* Enable the video logic */
id|outl
c_func
(paren
id|inl
c_func
(paren
id|TX3912_VIDEO_CTRL1
)paren
op_or
(paren
id|TX3912_VIDEO_CTRL1_ENVID
op_or
id|TX3912_VIDEO_CTRL1_DISPON
)paren
comma
id|TX3912_VIDEO_CTRL1
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Memory limit&n;&t; */
id|tx3912fb_fix.line_length
op_assign
id|get_line_length
c_func
(paren
id|tx3912fb_var.xres_virtual
comma
id|tx3912fb_var.bits_per_pixel
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|tx3912fb_fix.line_length
op_star
id|tx3912fb_var.yres_virtual
)paren
OG
id|tx3912fb_fix.smem_len
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|fb_info.node
op_assign
id|NODEV
suffix:semicolon
id|fb_info.fbops
op_assign
op_amp
id|tx3912fb_ops
suffix:semicolon
id|fb_info.var
op_assign
id|tx3912fb_var
suffix:semicolon
id|fb_info.fix
op_assign
id|tx3912fb_fix
suffix:semicolon
id|fb_info.pseudo_palette
op_assign
id|pseudo_palette
suffix:semicolon
id|fb_info.flags
op_assign
id|FBINFO_FLAG_DEFAULT
suffix:semicolon
multiline_comment|/* Clear the framebuffer */
id|memset
c_func
(paren
(paren
r_void
op_star
)paren
id|fb_info.fix.smem_start
comma
l_int|0xff
comma
id|fb_info.fix.smem_len
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|200
)paren
suffix:semicolon
id|fb_alloc_cmap
c_func
(paren
op_amp
id|info-&gt;cmap
comma
id|size
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
op_amp
id|fb_info
)paren
OL
l_int|0
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;fb%d: TX3912 frame buffer using %uKB.&bslash;n&quot;
comma
id|minor
c_func
(paren
id|fb_info.node
)paren
comma
(paren
id|u_int
)paren
(paren
id|fb_info.fix.smem_len
op_rshift
l_int|10
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|tx3912fb_setup
r_void
id|__init
id|tx3912fb_setup
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
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|options
comma
l_string|&quot;bpp:&quot;
comma
l_int|4
)paren
)paren
id|tx3912fb_var.bits_per_pixel
op_assign
id|simple_strtoul
c_func
(paren
id|options
op_plus
l_int|4
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
)brace
)brace
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
