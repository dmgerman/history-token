multiline_comment|/*&n; * linux/drivers/video/tx3912fb.h&n; *&n; * Copyright (C) 2001 Steven Hill (sjhill@realitydiluted.com)&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License. See the file COPYING in the main directory of this archive for&n; * more details.&n; *&n; * Includes for TMPR3912/05 and PR31700 LCD controller registers&n; */
macro_line|#include &lt;asm/tx3912.h&gt;
DECL|macro|VidCtrl1
mdefine_line|#define VidCtrl1        REG_AT(0x028)
DECL|macro|VidCtrl2
mdefine_line|#define VidCtrl2        REG_AT(0x02C)
DECL|macro|VidCtrl3
mdefine_line|#define VidCtrl3        REG_AT(0x030)
DECL|macro|VidCtrl4
mdefine_line|#define VidCtrl4        REG_AT(0x034)
DECL|macro|VidCtrl5
mdefine_line|#define VidCtrl5        REG_AT(0x038)
DECL|macro|VidCtrl6
mdefine_line|#define VidCtrl6        REG_AT(0x03C)
DECL|macro|VidCtrl7
mdefine_line|#define VidCtrl7        REG_AT(0x040)
DECL|macro|VidCtrl8
mdefine_line|#define VidCtrl8        REG_AT(0x044)
DECL|macro|VidCtrl9
mdefine_line|#define VidCtrl9        REG_AT(0x048)
DECL|macro|VidCtrl10
mdefine_line|#define VidCtrl10       REG_AT(0x04C)
DECL|macro|VidCtrl11
mdefine_line|#define VidCtrl11       REG_AT(0x050)
DECL|macro|VidCtrl12
mdefine_line|#define VidCtrl12       REG_AT(0x054)
DECL|macro|VidCtrl13
mdefine_line|#define VidCtrl13       REG_AT(0x058)
DECL|macro|VidCtrl14
mdefine_line|#define VidCtrl14       REG_AT(0x05C)
multiline_comment|/* Video Control 1 Register */
DECL|macro|LINECNT
mdefine_line|#define LINECNT         0xffc00000
DECL|macro|LINECNT_SHIFT
mdefine_line|#define LINECNT_SHIFT   22
DECL|macro|LOADDLY
mdefine_line|#define LOADDLY         BIT(21)
DECL|macro|BAUDVAL
mdefine_line|#define BAUDVAL         (BIT(20) | BIT(19) | BIT(18) | BIT(17) | BIT(16))
DECL|macro|BAUDVAL_SHIFT
mdefine_line|#define BAUDVAL_SHIFT   16
DECL|macro|VIDDONEVAL
mdefine_line|#define VIDDONEVAL      (BIT(15) | BIT(14) | BIT(13) | BIT(12) | BIT(11) | BIT(10) | BIT(9))
DECL|macro|VIDDONEVAL_SHIFT
mdefine_line|#define VIDDONEVAL_SHIFT  9
DECL|macro|ENFREEZEFRAME
mdefine_line|#define ENFREEZEFRAME   BIT(8)
DECL|macro|TX3912_VIDCTRL1_BITSEL_MASK
mdefine_line|#define TX3912_VIDCTRL1_BITSEL_MASK&t;0x000000c0
DECL|macro|TX3912_VIDCTRL1_2BIT_GRAY
mdefine_line|#define TX3912_VIDCTRL1_2BIT_GRAY&t;0x00000040
DECL|macro|TX3912_VIDCTRL1_4BIT_GRAY
mdefine_line|#define TX3912_VIDCTRL1_4BIT_GRAY&t;0x00000080
DECL|macro|TX3912_VIDCTRL1_8BIT_COLOR
mdefine_line|#define TX3912_VIDCTRL1_8BIT_COLOR&t;0x000000c0
DECL|macro|BITSEL_SHIFT
mdefine_line|#define BITSEL_SHIFT    6
DECL|macro|DISPSPLIT
mdefine_line|#define DISPSPLIT       BIT(5)
DECL|macro|DISP8
mdefine_line|#define DISP8           BIT(4)
DECL|macro|DFMODE
mdefine_line|#define DFMODE          BIT(3)
DECL|macro|INVVID
mdefine_line|#define INVVID          BIT(2)
DECL|macro|DISPON
mdefine_line|#define DISPON          BIT(1)
DECL|macro|ENVID
mdefine_line|#define ENVID           BIT(0)
multiline_comment|/* Video Control 2 Register */
DECL|macro|VIDRATE_MASK
mdefine_line|#define VIDRATE_MASK    0xffc00000
DECL|macro|VIDRATE_SHIFT
mdefine_line|#define VIDRATE_SHIFT   22
DECL|macro|HORZVAL_MASK
mdefine_line|#define HORZVAL_MASK    0x001ff000
DECL|macro|HORZVAL_SHIFT
mdefine_line|#define HORZVAL_SHIFT   12
DECL|macro|LINEVAL_MASK
mdefine_line|#define LINEVAL_MASK    0x000001ff
multiline_comment|/* Video Control 3 Register */
DECL|macro|TX3912_VIDCTRL3_VIDBANK_MASK
mdefine_line|#define TX3912_VIDCTRL3_VIDBANK_MASK    0xfff00000
DECL|macro|TX3912_VIDCTRL3_VIDBASEHI_MASK
mdefine_line|#define TX3912_VIDCTRL3_VIDBASEHI_MASK  0x000ffff0
multiline_comment|/* Video Control 4 Register */
DECL|macro|TX3912_VIDCTRL4_VIDBASELO_MASK
mdefine_line|#define TX3912_VIDCTRL4_VIDBASELO_MASK  0x000ffff0
multiline_comment|/*&n; * Begin platform specific configurations&n; */
macro_line|#if defined(CONFIG_NINO_4MB) || defined(CONFIG_NINO_8MB)
DECL|macro|FB_X_RES
mdefine_line|#define FB_X_RES       240
DECL|macro|FB_Y_RES
mdefine_line|#define FB_Y_RES       320
macro_line|#if defined(CONFIG_FBCON_CFB4)
DECL|macro|FB_BPP
mdefine_line|#define FB_BPP         4
macro_line|#else
macro_line|#if defined(CONFIG_FBCON_CFB2)
DECL|macro|FB_BPP
mdefine_line|#define FB_BPP         2
macro_line|#else
DECL|macro|FB_BPP
mdefine_line|#define FB_BPP         1
macro_line|#endif
macro_line|#endif
DECL|macro|FB_IS_GREY
mdefine_line|#define FB_IS_GREY     1
DECL|macro|FB_IS_INVERSE
mdefine_line|#define FB_IS_INVERSE  0
macro_line|#endif
macro_line|#ifdef CONFIG_NINO_16MB
DECL|macro|FB_X_RES
mdefine_line|#define FB_X_RES       240
DECL|macro|FB_Y_RES
mdefine_line|#define FB_Y_RES       320
DECL|macro|FB_BPP
mdefine_line|#define FB_BPP         8
DECL|macro|FB_IS_GREY
mdefine_line|#define FB_IS_GREY     0
DECL|macro|FB_IS_INVERSE
mdefine_line|#define FB_IS_INVERSE  0
macro_line|#endif
multiline_comment|/*&n; * Define virtual resolutions if necessary&n; */
macro_line|#ifndef FB_X_VIRTUAL_RES
DECL|macro|FB_X_VIRTUAL_RES
mdefine_line|#define FB_X_VIRTUAL_RES FB_X_RES
macro_line|#endif
macro_line|#ifndef FB_Y_VIRTUAL_RES
DECL|macro|FB_Y_VIRTUAL_RES
mdefine_line|#define FB_Y_VIRTUAL_RES FB_Y_RES
macro_line|#endif
multiline_comment|/*&n; * Framebuffer address and size&n; */
DECL|variable|tx3912fb_paddr
id|u_long
id|tx3912fb_paddr
op_assign
l_int|0
suffix:semicolon
DECL|variable|tx3912fb_vaddr
id|u_long
id|tx3912fb_vaddr
op_assign
l_int|0
suffix:semicolon
DECL|variable|tx3912fb_size
id|u_long
id|tx3912fb_size
op_assign
(paren
id|FB_X_RES
op_star
id|FB_Y_RES
op_star
id|FB_BPP
op_div
l_int|8
)paren
suffix:semicolon
multiline_comment|/*&n; * Framebuffer info structure&n; */
DECL|variable|tx3912fb_info
r_static
r_struct
id|fb_var_screeninfo
id|tx3912fb_info
op_assign
(brace
id|FB_X_RES
comma
id|FB_Y_RES
comma
id|FB_X_VIRTUAL_RES
comma
id|FB_Y_VIRTUAL_RES
comma
l_int|0
comma
l_int|0
comma
id|FB_BPP
comma
id|FB_IS_GREY
comma
(brace
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
(brace
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
(brace
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
(brace
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
l_int|0
comma
id|FB_ACTIVATE_NOW
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
l_int|0
comma
l_int|20000
comma
l_int|64
comma
l_int|64
comma
l_int|32
comma
l_int|32
comma
l_int|64
comma
l_int|2
comma
l_int|0
comma
id|FB_VMODE_NONINTERLACED
comma
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
)brace
suffix:semicolon
multiline_comment|/*&n; * Framebuffer name&n; */
DECL|variable|TX3912FB_NAME
r_static
r_char
id|TX3912FB_NAME
(braket
l_int|16
)braket
op_assign
l_string|&quot;tx3912fb&quot;
suffix:semicolon
eof
