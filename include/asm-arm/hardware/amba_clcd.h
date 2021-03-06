multiline_comment|/*&n; * linux/include/asm-arm/hardware/amba_clcd.h -- Integrator LCD panel.&n; *&n; * David A Rusling&n; *&n; * Copyright (C) 2001 ARM Limited&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file COPYING in the main directory of this archive&n; * for more details.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/fb.h&gt;
multiline_comment|/*&n; * CLCD Controller Internal Register addresses&n; */
DECL|macro|CLCD_TIM0
mdefine_line|#define CLCD_TIM0&t;&t;0x00000000
DECL|macro|CLCD_TIM1
mdefine_line|#define CLCD_TIM1 &t;&t;0x00000004
DECL|macro|CLCD_TIM2
mdefine_line|#define CLCD_TIM2 &t;&t;0x00000008
DECL|macro|CLCD_TIM3
mdefine_line|#define CLCD_TIM3 &t;&t;0x0000000c
DECL|macro|CLCD_UBAS
mdefine_line|#define CLCD_UBAS &t;&t;0x00000010
DECL|macro|CLCD_LBAS
mdefine_line|#define CLCD_LBAS &t;&t;0x00000014
macro_line|#ifndef CONFIG_ARCH_VERSATILE
DECL|macro|CLCD_IENB
mdefine_line|#define CLCD_IENB &t;&t;0x00000018
DECL|macro|CLCD_CNTL
mdefine_line|#define CLCD_CNTL &t;&t;0x0000001c
macro_line|#else
multiline_comment|/*&n; * Someone rearranged these two registers on the Versatile&n; * platform...&n; */
DECL|macro|CLCD_IENB
mdefine_line|#define CLCD_IENB &t;&t;0x0000001c
DECL|macro|CLCD_CNTL
mdefine_line|#define CLCD_CNTL &t;&t;0x00000018
macro_line|#endif
DECL|macro|CLCD_STAT
mdefine_line|#define CLCD_STAT &t;&t;0x00000020
DECL|macro|CLCD_INTR
mdefine_line|#define CLCD_INTR &t;&t;0x00000024
DECL|macro|CLCD_UCUR
mdefine_line|#define CLCD_UCUR &t;&t;0x00000028
DECL|macro|CLCD_LCUR
mdefine_line|#define CLCD_LCUR &t;&t;0x0000002C
DECL|macro|CLCD_PALL
mdefine_line|#define CLCD_PALL &t;&t;0x00000200
DECL|macro|CLCD_PALETTE
mdefine_line|#define CLCD_PALETTE&t;&t;0x00000200
DECL|macro|TIM2_CLKSEL
mdefine_line|#define TIM2_CLKSEL&t;&t;(1 &lt;&lt; 5)
DECL|macro|TIM2_IVS
mdefine_line|#define TIM2_IVS&t;&t;(1 &lt;&lt; 11)
DECL|macro|TIM2_IHS
mdefine_line|#define TIM2_IHS&t;&t;(1 &lt;&lt; 12)
DECL|macro|TIM2_IPC
mdefine_line|#define TIM2_IPC&t;&t;(1 &lt;&lt; 13)
DECL|macro|TIM2_IOE
mdefine_line|#define TIM2_IOE&t;&t;(1 &lt;&lt; 14)
DECL|macro|TIM2_BCD
mdefine_line|#define TIM2_BCD&t;&t;(1 &lt;&lt; 26)
DECL|macro|CNTL_LCDEN
mdefine_line|#define CNTL_LCDEN&t;&t;(1 &lt;&lt; 0)
DECL|macro|CNTL_LCDBPP1
mdefine_line|#define CNTL_LCDBPP1&t;&t;(0 &lt;&lt; 1)
DECL|macro|CNTL_LCDBPP2
mdefine_line|#define CNTL_LCDBPP2&t;&t;(1 &lt;&lt; 1)
DECL|macro|CNTL_LCDBPP4
mdefine_line|#define CNTL_LCDBPP4&t;&t;(2 &lt;&lt; 1)
DECL|macro|CNTL_LCDBPP8
mdefine_line|#define CNTL_LCDBPP8&t;&t;(3 &lt;&lt; 1)
DECL|macro|CNTL_LCDBPP16
mdefine_line|#define CNTL_LCDBPP16&t;&t;(4 &lt;&lt; 1)
DECL|macro|CNTL_LCDBPP24
mdefine_line|#define CNTL_LCDBPP24&t;&t;(5 &lt;&lt; 1)
DECL|macro|CNTL_LCDBW
mdefine_line|#define CNTL_LCDBW&t;&t;(1 &lt;&lt; 4)
DECL|macro|CNTL_LCDTFT
mdefine_line|#define CNTL_LCDTFT&t;&t;(1 &lt;&lt; 5)
DECL|macro|CNTL_LCDMONO8
mdefine_line|#define CNTL_LCDMONO8&t;&t;(1 &lt;&lt; 6)
DECL|macro|CNTL_LCDDUAL
mdefine_line|#define CNTL_LCDDUAL&t;&t;(1 &lt;&lt; 7)
DECL|macro|CNTL_BGR
mdefine_line|#define CNTL_BGR&t;&t;(1 &lt;&lt; 8)
DECL|macro|CNTL_BEBO
mdefine_line|#define CNTL_BEBO&t;&t;(1 &lt;&lt; 9)
DECL|macro|CNTL_BEPO
mdefine_line|#define CNTL_BEPO&t;&t;(1 &lt;&lt; 10)
DECL|macro|CNTL_LCDPWR
mdefine_line|#define CNTL_LCDPWR&t;&t;(1 &lt;&lt; 11)
DECL|macro|CNTL_LCDVCOMP
mdefine_line|#define CNTL_LCDVCOMP(x)&t;((x) &lt;&lt; 12)
DECL|macro|CNTL_LDMAFIFOTIME
mdefine_line|#define CNTL_LDMAFIFOTIME&t;(1 &lt;&lt; 15)
DECL|macro|CNTL_WATERMARK
mdefine_line|#define CNTL_WATERMARK&t;&t;(1 &lt;&lt; 16)
DECL|struct|clcd_panel
r_struct
id|clcd_panel
(brace
DECL|member|mode
r_struct
id|fb_videomode
id|mode
suffix:semicolon
DECL|member|width
r_int
r_int
id|width
suffix:semicolon
multiline_comment|/* width in mm */
DECL|member|height
r_int
r_int
id|height
suffix:semicolon
multiline_comment|/* height in mm */
DECL|member|tim2
id|u32
id|tim2
suffix:semicolon
DECL|member|tim3
id|u32
id|tim3
suffix:semicolon
DECL|member|cntl
id|u32
id|cntl
suffix:semicolon
DECL|member|bpp
r_int
r_int
id|bpp
suffix:colon
l_int|8
comma
DECL|member|fixedtimings
id|fixedtimings
suffix:colon
l_int|1
comma
DECL|member|grayscale
id|grayscale
suffix:colon
l_int|1
suffix:semicolon
DECL|member|connector
r_int
r_int
id|connector
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|clcd_regs
r_struct
id|clcd_regs
(brace
DECL|member|tim0
id|u32
id|tim0
suffix:semicolon
DECL|member|tim1
id|u32
id|tim1
suffix:semicolon
DECL|member|tim2
id|u32
id|tim2
suffix:semicolon
DECL|member|tim3
id|u32
id|tim3
suffix:semicolon
DECL|member|cntl
id|u32
id|cntl
suffix:semicolon
DECL|member|pixclock
r_int
r_int
id|pixclock
suffix:semicolon
)brace
suffix:semicolon
r_struct
id|clcd_fb
suffix:semicolon
multiline_comment|/*&n; * the board-type specific routines&n; */
DECL|struct|clcd_board
r_struct
id|clcd_board
(brace
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
multiline_comment|/*&n;&t; * Optional.  Check whether the var structure is acceptable&n;&t; * for this display.&n;&t; */
DECL|member|check
r_int
(paren
op_star
id|check
)paren
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
suffix:semicolon
multiline_comment|/*&n;&t; * Compulsary.  Decode fb-&gt;fb.var into regs-&gt;*.  In the case of&n;&t; * fixed timing, set regs-&gt;* to the register values required.&n;&t; */
DECL|member|decode
r_void
(paren
op_star
id|decode
)paren
(paren
r_struct
id|clcd_fb
op_star
id|fb
comma
r_struct
id|clcd_regs
op_star
id|regs
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Optional.  Disable any extra display hardware.&n;&t; */
DECL|member|disable
r_void
(paren
op_star
id|disable
)paren
(paren
r_struct
id|clcd_fb
op_star
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Optional.  Enable any extra display hardware.&n;&t; */
DECL|member|enable
r_void
(paren
op_star
id|enable
)paren
(paren
r_struct
id|clcd_fb
op_star
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Setup platform specific parts of CLCD driver&n;&t; */
DECL|member|setup
r_int
(paren
op_star
id|setup
)paren
(paren
r_struct
id|clcd_fb
op_star
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * mmap the framebuffer memory&n;&t; */
DECL|member|mmap
r_int
(paren
op_star
id|mmap
)paren
(paren
r_struct
id|clcd_fb
op_star
comma
r_struct
id|vm_area_struct
op_star
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Remove platform specific parts of CLCD driver&n;&t; */
DECL|member|remove
r_void
(paren
op_star
id|remove
)paren
(paren
r_struct
id|clcd_fb
op_star
)paren
suffix:semicolon
)brace
suffix:semicolon
r_struct
id|amba_device
suffix:semicolon
r_struct
id|clk
suffix:semicolon
multiline_comment|/* this data structure describes each frame buffer device we find */
DECL|struct|clcd_fb
r_struct
id|clcd_fb
(brace
DECL|member|fb
r_struct
id|fb_info
id|fb
suffix:semicolon
DECL|member|dev
r_struct
id|amba_device
op_star
id|dev
suffix:semicolon
DECL|member|clk
r_struct
id|clk
op_star
id|clk
suffix:semicolon
DECL|member|panel
r_struct
id|clcd_panel
op_star
id|panel
suffix:semicolon
DECL|member|board
r_struct
id|clcd_board
op_star
id|board
suffix:semicolon
DECL|member|board_data
r_void
op_star
id|board_data
suffix:semicolon
DECL|member|regs
r_void
id|__iomem
op_star
id|regs
suffix:semicolon
DECL|member|clcd_cntl
id|u32
id|clcd_cntl
suffix:semicolon
DECL|member|cmap
id|u32
id|cmap
(braket
l_int|16
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|function|clcdfb_decode
r_static
r_inline
r_void
id|clcdfb_decode
c_func
(paren
r_struct
id|clcd_fb
op_star
id|fb
comma
r_struct
id|clcd_regs
op_star
id|regs
)paren
(brace
id|u32
id|val
suffix:semicolon
multiline_comment|/*&n;&t; * Program the CLCD controller registers and start the CLCD&n;&t; */
id|val
op_assign
(paren
(paren
id|fb-&gt;fb.var.xres
op_div
l_int|16
)paren
op_minus
l_int|1
)paren
op_lshift
l_int|2
suffix:semicolon
id|val
op_or_assign
(paren
id|fb-&gt;fb.var.hsync_len
op_minus
l_int|1
)paren
op_lshift
l_int|8
suffix:semicolon
id|val
op_or_assign
(paren
id|fb-&gt;fb.var.right_margin
op_minus
l_int|1
)paren
op_lshift
l_int|16
suffix:semicolon
id|val
op_or_assign
(paren
id|fb-&gt;fb.var.left_margin
op_minus
l_int|1
)paren
op_lshift
l_int|24
suffix:semicolon
id|regs-&gt;tim0
op_assign
id|val
suffix:semicolon
id|val
op_assign
id|fb-&gt;fb.var.yres
op_minus
l_int|1
suffix:semicolon
id|val
op_or_assign
(paren
id|fb-&gt;fb.var.vsync_len
op_minus
l_int|1
)paren
op_lshift
l_int|10
suffix:semicolon
id|val
op_or_assign
id|fb-&gt;fb.var.lower_margin
op_lshift
l_int|16
suffix:semicolon
id|val
op_or_assign
id|fb-&gt;fb.var.upper_margin
op_lshift
l_int|24
suffix:semicolon
id|regs-&gt;tim1
op_assign
id|val
suffix:semicolon
id|val
op_assign
id|fb-&gt;panel-&gt;tim2
suffix:semicolon
id|val
op_or_assign
id|fb-&gt;fb.var.sync
op_amp
id|FB_SYNC_HOR_HIGH_ACT
ques
c_cond
l_int|0
suffix:colon
id|TIM2_IHS
suffix:semicolon
id|val
op_or_assign
id|fb-&gt;fb.var.sync
op_amp
id|FB_SYNC_VERT_HIGH_ACT
ques
c_cond
l_int|0
suffix:colon
id|TIM2_IVS
suffix:semicolon
r_if
c_cond
(paren
id|fb-&gt;panel-&gt;cntl
op_amp
id|CNTL_LCDTFT
)paren
id|val
op_or_assign
(paren
id|fb-&gt;fb.var.xres_virtual
op_minus
l_int|1
)paren
op_lshift
l_int|16
suffix:semicolon
r_else
r_if
c_cond
(paren
id|fb-&gt;panel-&gt;cntl
op_amp
id|CNTL_LCDBW
)paren
id|printk
c_func
(paren
l_string|&quot;what value for CPL for stnmono panels?&quot;
)paren
suffix:semicolon
r_else
id|val
op_or_assign
(paren
(paren
id|fb-&gt;fb.var.xres_virtual
op_star
l_int|8
op_div
l_int|3
)paren
op_minus
l_int|1
)paren
op_lshift
l_int|16
suffix:semicolon
id|regs-&gt;tim2
op_assign
id|val
suffix:semicolon
id|regs-&gt;tim3
op_assign
id|fb-&gt;panel-&gt;tim3
suffix:semicolon
id|val
op_assign
id|fb-&gt;panel-&gt;cntl
suffix:semicolon
r_if
c_cond
(paren
id|fb-&gt;fb.var.grayscale
)paren
id|val
op_or_assign
id|CNTL_LCDBW
suffix:semicolon
r_switch
c_cond
(paren
id|fb-&gt;fb.var.bits_per_pixel
)paren
(brace
r_case
l_int|1
suffix:colon
id|val
op_or_assign
id|CNTL_LCDBPP1
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|val
op_or_assign
id|CNTL_LCDBPP2
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|val
op_or_assign
id|CNTL_LCDBPP4
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|8
suffix:colon
id|val
op_or_assign
id|CNTL_LCDBPP8
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|16
suffix:colon
id|val
op_or_assign
id|CNTL_LCDBPP16
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|24
suffix:colon
id|val
op_or_assign
id|CNTL_LCDBPP24
suffix:semicolon
r_break
suffix:semicolon
)brace
id|regs-&gt;cntl
op_assign
id|val
suffix:semicolon
id|regs-&gt;pixclock
op_assign
id|fb-&gt;fb.var.pixclock
suffix:semicolon
)brace
DECL|function|clcdfb_check
r_static
r_inline
r_int
id|clcdfb_check
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
id|var-&gt;xres_virtual
op_assign
id|var-&gt;xres
op_assign
(paren
id|var-&gt;xres
op_plus
l_int|7
)paren
op_amp
op_complement
l_int|7
suffix:semicolon
id|var-&gt;yres_virtual
op_assign
id|var-&gt;yres
suffix:semicolon
DECL|macro|CHECK
mdefine_line|#define CHECK(e,l,h) (var-&gt;e &lt; l || var-&gt;e &gt; h)
r_if
c_cond
(paren
id|CHECK
c_func
(paren
id|right_margin
comma
(paren
l_int|5
op_plus
l_int|1
)paren
comma
l_int|256
)paren
op_logical_or
multiline_comment|/* back porch */
id|CHECK
c_func
(paren
id|left_margin
comma
(paren
l_int|5
op_plus
l_int|1
)paren
comma
l_int|256
)paren
op_logical_or
multiline_comment|/* front porch */
id|CHECK
c_func
(paren
id|hsync_len
comma
(paren
l_int|5
op_plus
l_int|1
)paren
comma
l_int|256
)paren
op_logical_or
id|var-&gt;xres
OG
l_int|4096
op_logical_or
id|var-&gt;lower_margin
OG
l_int|255
op_logical_or
multiline_comment|/* back porch */
id|var-&gt;upper_margin
OG
l_int|255
op_logical_or
multiline_comment|/* front porch */
id|var-&gt;vsync_len
OG
l_int|32
op_logical_or
id|var-&gt;yres
OG
l_int|1024
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
DECL|macro|CHECK
macro_line|#undef CHECK
multiline_comment|/* single panel mode: PCD = max(PCD, 1) */
multiline_comment|/* dual panel mode: PCD = max(PCD, 5) */
multiline_comment|/*&n;&t; * You can&squot;t change the grayscale setting, and&n;&t; * we can only do non-interlaced video.&n;&t; */
r_if
c_cond
(paren
id|var-&gt;grayscale
op_ne
id|fb-&gt;fb.var.grayscale
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
DECL|macro|CHECK
mdefine_line|#define CHECK(e) (var-&gt;e != fb-&gt;fb.var.e)
r_if
c_cond
(paren
id|fb-&gt;panel-&gt;fixedtimings
op_logical_and
(paren
id|CHECK
c_func
(paren
id|xres
)paren
op_logical_or
id|CHECK
c_func
(paren
id|yres
)paren
op_logical_or
id|CHECK
c_func
(paren
id|bits_per_pixel
)paren
op_logical_or
id|CHECK
c_func
(paren
id|pixclock
)paren
op_logical_or
id|CHECK
c_func
(paren
id|left_margin
)paren
op_logical_or
id|CHECK
c_func
(paren
id|right_margin
)paren
op_logical_or
id|CHECK
c_func
(paren
id|upper_margin
)paren
op_logical_or
id|CHECK
c_func
(paren
id|lower_margin
)paren
op_logical_or
id|CHECK
c_func
(paren
id|hsync_len
)paren
op_logical_or
id|CHECK
c_func
(paren
id|vsync_len
)paren
op_logical_or
id|CHECK
c_func
(paren
id|sync
)paren
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
DECL|macro|CHECK
macro_line|#undef CHECK
id|var-&gt;nonstd
op_assign
l_int|0
suffix:semicolon
id|var-&gt;accel_flags
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
