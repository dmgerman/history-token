multiline_comment|/*&n; * linux/include/video/vga.h -- standard VGA chipset interaction&n; *&n; * Copyright 1999 Jeff Garzik &lt;jgarzik@mandrakesoft.com&gt;&n; * &n; * Copyright history from vga16fb.c:&n; *&t;Copyright 1999 Ben Pfaff and Petr Vandrovec&n; *&t;Based on VGA info at http://www.goodnet.com/~tinara/FreeVGA/home.htm&n; *&t;Based on VESA framebuffer (c) 1998 Gerd Knorr&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.  &n; *&n; */
macro_line|#ifndef __linux_video_vga_h__
DECL|macro|__linux_video_vga_h__
mdefine_line|#define __linux_video_vga_h__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#ifndef CONFIG_AMIGA
macro_line|#include &lt;asm/vga.h&gt;
macro_line|#endif
macro_line|#include &lt;asm/byteorder.h&gt;
multiline_comment|/* Some of the code below is taken from SVGAlib.  The original,&n;   unmodified copyright notice for that code is below. */
multiline_comment|/* VGAlib version 1.2 - (c) 1993 Tommy Frandsen                    */
multiline_comment|/*                                                                 */
multiline_comment|/* This library is free software; you can redistribute it and/or   */
multiline_comment|/* modify it without any restrictions. This library is distributed */
multiline_comment|/* in the hope that it will be useful, but without any warranty.   */
multiline_comment|/* Multi-chipset support Copyright 1993 Harm Hanemaayer */
multiline_comment|/* partially copyrighted (C) 1993 by Hartmut Schirmer */
multiline_comment|/* VGA data register ports */
DECL|macro|VGA_CRT_DC
mdefine_line|#define VGA_CRT_DC  &t;0x3D5&t;/* CRT Controller Data Register - color emulation */
DECL|macro|VGA_CRT_DM
mdefine_line|#define VGA_CRT_DM  &t;0x3B5&t;/* CRT Controller Data Register - mono emulation */
DECL|macro|VGA_ATT_R
mdefine_line|#define VGA_ATT_R   &t;0x3C1&t;/* Attribute Controller Data Read Register */
DECL|macro|VGA_ATT_W
mdefine_line|#define VGA_ATT_W   &t;0x3C0&t;/* Attribute Controller Data Write Register */
DECL|macro|VGA_GFX_D
mdefine_line|#define VGA_GFX_D   &t;0x3CF&t;/* Graphics Controller Data Register */
DECL|macro|VGA_SEQ_D
mdefine_line|#define VGA_SEQ_D   &t;0x3C5&t;/* Sequencer Data Register */
DECL|macro|VGA_MIS_R
mdefine_line|#define VGA_MIS_R   &t;0x3CC&t;/* Misc Output Read Register */
DECL|macro|VGA_MIS_W
mdefine_line|#define VGA_MIS_W   &t;0x3C2&t;/* Misc Output Write Register */
DECL|macro|VGA_FTC_R
mdefine_line|#define VGA_FTC_R&t;0x3CA&t;/* Feature Control Read Register */
DECL|macro|VGA_IS1_RC
mdefine_line|#define VGA_IS1_RC  &t;0x3DA&t;/* Input Status Register 1 - color emulation */
DECL|macro|VGA_IS1_RM
mdefine_line|#define VGA_IS1_RM  &t;0x3BA&t;/* Input Status Register 1 - mono emulation */
DECL|macro|VGA_PEL_D
mdefine_line|#define VGA_PEL_D   &t;0x3C9&t;/* PEL Data Register */
DECL|macro|VGA_PEL_MSK
mdefine_line|#define VGA_PEL_MSK &t;0x3C6&t;/* PEL mask register */
multiline_comment|/* EGA-specific registers */
DECL|macro|EGA_GFX_E0
mdefine_line|#define EGA_GFX_E0&t;0x3CC&t;/* Graphics enable processor 0 */
DECL|macro|EGA_GFX_E1
mdefine_line|#define EGA_GFX_E1&t;0x3CA&t;/* Graphics enable processor 1 */
multiline_comment|/* VGA index register ports */
DECL|macro|VGA_CRT_IC
mdefine_line|#define VGA_CRT_IC  &t;0x3D4&t;/* CRT Controller Index - color emulation */
DECL|macro|VGA_CRT_IM
mdefine_line|#define VGA_CRT_IM  &t;0x3B4&t;/* CRT Controller Index - mono emulation */
DECL|macro|VGA_ATT_IW
mdefine_line|#define VGA_ATT_IW  &t;0x3C0&t;/* Attribute Controller Index &amp; Data Write Register */
DECL|macro|VGA_GFX_I
mdefine_line|#define VGA_GFX_I   &t;0x3CE&t;/* Graphics Controller Index */
DECL|macro|VGA_SEQ_I
mdefine_line|#define VGA_SEQ_I   &t;0x3C4&t;/* Sequencer Index */
DECL|macro|VGA_PEL_IW
mdefine_line|#define VGA_PEL_IW  &t;0x3C8&t;/* PEL Write Index */
DECL|macro|VGA_PEL_IR
mdefine_line|#define VGA_PEL_IR  &t;0x3C7&t;/* PEL Read Index */
multiline_comment|/* standard VGA indexes max counts */
DECL|macro|VGA_CRT_C
mdefine_line|#define VGA_CRT_C   &t;0x19&t;/* Number of CRT Controller Registers */
DECL|macro|VGA_ATT_C
mdefine_line|#define VGA_ATT_C   &t;0x15&t;/* Number of Attribute Controller Registers */
DECL|macro|VGA_GFX_C
mdefine_line|#define VGA_GFX_C   &t;0x09&t;/* Number of Graphics Controller Registers */
DECL|macro|VGA_SEQ_C
mdefine_line|#define VGA_SEQ_C   &t;0x05&t;/* Number of Sequencer Registers */
DECL|macro|VGA_MIS_C
mdefine_line|#define VGA_MIS_C   &t;0x01&t;/* Number of Misc Output Register */
multiline_comment|/* VGA misc register bit masks */
DECL|macro|VGA_MIS_COLOR
mdefine_line|#define VGA_MIS_COLOR&t;&t;0x01
DECL|macro|VGA_MIS_ENB_MEM_ACCESS
mdefine_line|#define VGA_MIS_ENB_MEM_ACCESS&t;0x02
DECL|macro|VGA_MIS_DCLK_28322_720
mdefine_line|#define VGA_MIS_DCLK_28322_720&t;0x04
DECL|macro|VGA_MIS_ENB_PLL_LOAD
mdefine_line|#define VGA_MIS_ENB_PLL_LOAD&t;(0x04 | 0x08)
DECL|macro|VGA_MIS_SEL_HIGH_PAGE
mdefine_line|#define VGA_MIS_SEL_HIGH_PAGE&t;0x20
multiline_comment|/* VGA CRT controller register indices */
DECL|macro|VGA_CRTC_H_TOTAL
mdefine_line|#define VGA_CRTC_H_TOTAL&t;0
DECL|macro|VGA_CRTC_H_DISP
mdefine_line|#define VGA_CRTC_H_DISP&t;&t;1
DECL|macro|VGA_CRTC_H_BLANK_START
mdefine_line|#define VGA_CRTC_H_BLANK_START&t;2
DECL|macro|VGA_CRTC_H_BLANK_END
mdefine_line|#define VGA_CRTC_H_BLANK_END&t;3
DECL|macro|VGA_CRTC_H_SYNC_START
mdefine_line|#define VGA_CRTC_H_SYNC_START&t;4
DECL|macro|VGA_CRTC_H_SYNC_END
mdefine_line|#define VGA_CRTC_H_SYNC_END&t;5
DECL|macro|VGA_CRTC_V_TOTAL
mdefine_line|#define VGA_CRTC_V_TOTAL&t;6
DECL|macro|VGA_CRTC_OVERFLOW
mdefine_line|#define VGA_CRTC_OVERFLOW&t;7
DECL|macro|VGA_CRTC_PRESET_ROW
mdefine_line|#define VGA_CRTC_PRESET_ROW&t;8
DECL|macro|VGA_CRTC_MAX_SCAN
mdefine_line|#define VGA_CRTC_MAX_SCAN&t;9
DECL|macro|VGA_CRTC_CURSOR_START
mdefine_line|#define VGA_CRTC_CURSOR_START&t;0x0A
DECL|macro|VGA_CRTC_CURSOR_END
mdefine_line|#define VGA_CRTC_CURSOR_END&t;0x0B
DECL|macro|VGA_CRTC_START_HI
mdefine_line|#define VGA_CRTC_START_HI&t;0x0C
DECL|macro|VGA_CRTC_START_LO
mdefine_line|#define VGA_CRTC_START_LO&t;0x0D
DECL|macro|VGA_CRTC_CURSOR_HI
mdefine_line|#define VGA_CRTC_CURSOR_HI&t;0x0E
DECL|macro|VGA_CRTC_CURSOR_LO
mdefine_line|#define VGA_CRTC_CURSOR_LO&t;0x0F
DECL|macro|VGA_CRTC_V_SYNC_START
mdefine_line|#define VGA_CRTC_V_SYNC_START&t;0x10
DECL|macro|VGA_CRTC_V_SYNC_END
mdefine_line|#define VGA_CRTC_V_SYNC_END&t;0x11
DECL|macro|VGA_CRTC_V_DISP_END
mdefine_line|#define VGA_CRTC_V_DISP_END&t;0x12
DECL|macro|VGA_CRTC_OFFSET
mdefine_line|#define VGA_CRTC_OFFSET&t;&t;0x13
DECL|macro|VGA_CRTC_UNDERLINE
mdefine_line|#define VGA_CRTC_UNDERLINE&t;0x14
DECL|macro|VGA_CRTC_V_BLANK_START
mdefine_line|#define VGA_CRTC_V_BLANK_START&t;0x15
DECL|macro|VGA_CRTC_V_BLANK_END
mdefine_line|#define VGA_CRTC_V_BLANK_END&t;0x16
DECL|macro|VGA_CRTC_MODE
mdefine_line|#define VGA_CRTC_MODE&t;&t;0x17
DECL|macro|VGA_CRTC_LINE_COMPARE
mdefine_line|#define VGA_CRTC_LINE_COMPARE&t;0x18
DECL|macro|VGA_CRTC_REGS
mdefine_line|#define VGA_CRTC_REGS&t;&t;VGA_CRT_C
multiline_comment|/* VGA CRT controller bit masks */
DECL|macro|VGA_CR11_LOCK_CR0_CR7
mdefine_line|#define VGA_CR11_LOCK_CR0_CR7&t;0x80 /* lock writes to CR0 - CR7 */
DECL|macro|VGA_CR17_H_V_SIGNALS_ENABLED
mdefine_line|#define VGA_CR17_H_V_SIGNALS_ENABLED 0x80
multiline_comment|/* VGA attribute controller register indices */
DECL|macro|VGA_ATC_PALETTE0
mdefine_line|#define VGA_ATC_PALETTE0&t;0x00
DECL|macro|VGA_ATC_PALETTE1
mdefine_line|#define VGA_ATC_PALETTE1&t;0x01
DECL|macro|VGA_ATC_PALETTE2
mdefine_line|#define VGA_ATC_PALETTE2&t;0x02
DECL|macro|VGA_ATC_PALETTE3
mdefine_line|#define VGA_ATC_PALETTE3&t;0x03
DECL|macro|VGA_ATC_PALETTE4
mdefine_line|#define VGA_ATC_PALETTE4&t;0x04
DECL|macro|VGA_ATC_PALETTE5
mdefine_line|#define VGA_ATC_PALETTE5&t;0x05
DECL|macro|VGA_ATC_PALETTE6
mdefine_line|#define VGA_ATC_PALETTE6&t;0x06
DECL|macro|VGA_ATC_PALETTE7
mdefine_line|#define VGA_ATC_PALETTE7&t;0x07
DECL|macro|VGA_ATC_PALETTE8
mdefine_line|#define VGA_ATC_PALETTE8&t;0x08
DECL|macro|VGA_ATC_PALETTE9
mdefine_line|#define VGA_ATC_PALETTE9&t;0x09
DECL|macro|VGA_ATC_PALETTEA
mdefine_line|#define VGA_ATC_PALETTEA&t;0x0A
DECL|macro|VGA_ATC_PALETTEB
mdefine_line|#define VGA_ATC_PALETTEB&t;0x0B
DECL|macro|VGA_ATC_PALETTEC
mdefine_line|#define VGA_ATC_PALETTEC&t;0x0C
DECL|macro|VGA_ATC_PALETTED
mdefine_line|#define VGA_ATC_PALETTED&t;0x0D
DECL|macro|VGA_ATC_PALETTEE
mdefine_line|#define VGA_ATC_PALETTEE&t;0x0E
DECL|macro|VGA_ATC_PALETTEF
mdefine_line|#define VGA_ATC_PALETTEF&t;0x0F
DECL|macro|VGA_ATC_MODE
mdefine_line|#define VGA_ATC_MODE&t;&t;0x10
DECL|macro|VGA_ATC_OVERSCAN
mdefine_line|#define VGA_ATC_OVERSCAN&t;0x11
DECL|macro|VGA_ATC_PLANE_ENABLE
mdefine_line|#define VGA_ATC_PLANE_ENABLE&t;0x12
DECL|macro|VGA_ATC_PEL
mdefine_line|#define VGA_ATC_PEL&t;&t;0x13
DECL|macro|VGA_ATC_COLOR_PAGE
mdefine_line|#define VGA_ATC_COLOR_PAGE&t;0x14
DECL|macro|VGA_AR_ENABLE_DISPLAY
mdefine_line|#define VGA_AR_ENABLE_DISPLAY&t;0x20
multiline_comment|/* VGA sequencer register indices */
DECL|macro|VGA_SEQ_RESET
mdefine_line|#define VGA_SEQ_RESET&t;&t;0x00
DECL|macro|VGA_SEQ_CLOCK_MODE
mdefine_line|#define VGA_SEQ_CLOCK_MODE&t;0x01
DECL|macro|VGA_SEQ_PLANE_WRITE
mdefine_line|#define VGA_SEQ_PLANE_WRITE&t;0x02
DECL|macro|VGA_SEQ_CHARACTER_MAP
mdefine_line|#define VGA_SEQ_CHARACTER_MAP&t;0x03
DECL|macro|VGA_SEQ_MEMORY_MODE
mdefine_line|#define VGA_SEQ_MEMORY_MODE&t;0x04
multiline_comment|/* VGA sequencer register bit masks */
DECL|macro|VGA_SR01_CHAR_CLK_8DOTS
mdefine_line|#define VGA_SR01_CHAR_CLK_8DOTS&t;0x01 /* bit 0: character clocks 8 dots wide are generated */
DECL|macro|VGA_SR01_SCREEN_OFF
mdefine_line|#define VGA_SR01_SCREEN_OFF&t;0x20 /* bit 5: Screen is off */
DECL|macro|VGA_SR02_ALL_PLANES
mdefine_line|#define VGA_SR02_ALL_PLANES&t;0x0F /* bits 3-0: enable access to all planes */
DECL|macro|VGA_SR04_EXT_MEM
mdefine_line|#define VGA_SR04_EXT_MEM&t;0x02 /* bit 1: allows complete mem access to 256K */
DECL|macro|VGA_SR04_SEQ_MODE
mdefine_line|#define VGA_SR04_SEQ_MODE&t;0x04 /* bit 2: directs system to use a sequential addressing mode */
DECL|macro|VGA_SR04_CHN_4M
mdefine_line|#define VGA_SR04_CHN_4M&t;&t;0x08 /* bit 3: selects modulo 4 addressing for CPU access to display memory */
multiline_comment|/* VGA graphics controller register indices */
DECL|macro|VGA_GFX_SR_VALUE
mdefine_line|#define VGA_GFX_SR_VALUE&t;0x00
DECL|macro|VGA_GFX_SR_ENABLE
mdefine_line|#define VGA_GFX_SR_ENABLE&t;0x01
DECL|macro|VGA_GFX_COMPARE_VALUE
mdefine_line|#define VGA_GFX_COMPARE_VALUE&t;0x02
DECL|macro|VGA_GFX_DATA_ROTATE
mdefine_line|#define VGA_GFX_DATA_ROTATE&t;0x03
DECL|macro|VGA_GFX_PLANE_READ
mdefine_line|#define VGA_GFX_PLANE_READ&t;0x04
DECL|macro|VGA_GFX_MODE
mdefine_line|#define VGA_GFX_MODE&t;&t;0x05
DECL|macro|VGA_GFX_MISC
mdefine_line|#define VGA_GFX_MISC&t;&t;0x06
DECL|macro|VGA_GFX_COMPARE_MASK
mdefine_line|#define VGA_GFX_COMPARE_MASK&t;0x07
DECL|macro|VGA_GFX_BIT_MASK
mdefine_line|#define VGA_GFX_BIT_MASK&t;0x08
multiline_comment|/* VGA graphics controller bit masks */
DECL|macro|VGA_GR06_GRAPHICS_MODE
mdefine_line|#define VGA_GR06_GRAPHICS_MODE&t;0x01
multiline_comment|/* macro for composing an 8-bit VGA register index and value&n; * into a single 16-bit quantity */
DECL|macro|VGA_OUT16VAL
mdefine_line|#define VGA_OUT16VAL(v, r)       (((v) &lt;&lt; 8) | (r))
multiline_comment|/* decide whether we should enable the faster 16-bit VGA register writes */
macro_line|#ifdef __LITTLE_ENDIAN
DECL|macro|VGA_OUTW_WRITE
mdefine_line|#define VGA_OUTW_WRITE
macro_line|#endif
multiline_comment|/*&n; * generic VGA port read/write&n; */
DECL|function|vga_io_r
r_static
r_inline
r_int
r_char
id|vga_io_r
(paren
r_int
r_int
id|port
)paren
(brace
r_return
id|inb
(paren
id|port
)paren
suffix:semicolon
)brace
DECL|function|vga_io_w
r_static
r_inline
r_void
id|vga_io_w
(paren
r_int
r_int
id|port
comma
r_int
r_char
id|val
)paren
(brace
id|outb
(paren
id|val
comma
id|port
)paren
suffix:semicolon
)brace
DECL|function|vga_io_w_fast
r_static
r_inline
r_void
id|vga_io_w_fast
(paren
r_int
r_int
id|port
comma
r_int
r_char
id|reg
comma
r_int
r_char
id|val
)paren
(brace
id|outw
(paren
id|VGA_OUT16VAL
(paren
id|val
comma
id|reg
)paren
comma
id|port
)paren
suffix:semicolon
)brace
DECL|function|vga_mm_r
r_static
r_inline
r_int
r_char
id|vga_mm_r
(paren
id|caddr_t
id|regbase
comma
r_int
r_int
id|port
)paren
(brace
r_return
id|readb
(paren
id|regbase
op_plus
id|port
)paren
suffix:semicolon
)brace
DECL|function|vga_mm_w
r_static
r_inline
r_void
id|vga_mm_w
(paren
id|caddr_t
id|regbase
comma
r_int
r_int
id|port
comma
r_int
r_char
id|val
)paren
(brace
id|writeb
(paren
id|val
comma
id|regbase
op_plus
id|port
)paren
suffix:semicolon
)brace
DECL|function|vga_mm_w_fast
r_static
r_inline
r_void
id|vga_mm_w_fast
(paren
id|caddr_t
id|regbase
comma
r_int
r_int
id|port
comma
r_int
r_char
id|reg
comma
r_int
r_char
id|val
)paren
(brace
id|writew
(paren
id|VGA_OUT16VAL
(paren
id|val
comma
id|reg
)paren
comma
id|regbase
op_plus
id|port
)paren
suffix:semicolon
)brace
DECL|function|vga_r
r_static
r_inline
r_int
r_char
id|vga_r
(paren
id|caddr_t
id|regbase
comma
r_int
r_int
id|port
)paren
(brace
r_if
c_cond
(paren
id|regbase
)paren
r_return
id|vga_mm_r
(paren
id|regbase
comma
id|port
)paren
suffix:semicolon
r_else
r_return
id|vga_io_r
(paren
id|port
)paren
suffix:semicolon
)brace
DECL|function|vga_w
r_static
r_inline
r_void
id|vga_w
(paren
id|caddr_t
id|regbase
comma
r_int
r_int
id|port
comma
r_int
r_char
id|val
)paren
(brace
r_if
c_cond
(paren
id|regbase
)paren
id|vga_mm_w
(paren
id|regbase
comma
id|port
comma
id|val
)paren
suffix:semicolon
r_else
id|vga_io_w
(paren
id|port
comma
id|val
)paren
suffix:semicolon
)brace
DECL|function|vga_w_fast
r_static
r_inline
r_void
id|vga_w_fast
(paren
id|caddr_t
id|regbase
comma
r_int
r_int
id|port
comma
r_int
r_char
id|reg
comma
r_int
r_char
id|val
)paren
(brace
r_if
c_cond
(paren
id|regbase
)paren
id|vga_mm_w_fast
(paren
id|regbase
comma
id|port
comma
id|reg
comma
id|val
)paren
suffix:semicolon
r_else
id|vga_io_w_fast
(paren
id|port
comma
id|reg
comma
id|val
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * VGA CRTC register read/write&n; */
DECL|function|vga_rcrt
r_static
r_inline
r_int
r_char
id|vga_rcrt
(paren
id|caddr_t
id|regbase
comma
r_int
r_char
id|reg
)paren
(brace
id|vga_w
(paren
id|regbase
comma
id|VGA_CRT_IC
comma
id|reg
)paren
suffix:semicolon
r_return
id|vga_r
(paren
id|regbase
comma
id|VGA_CRT_DC
)paren
suffix:semicolon
)brace
DECL|function|vga_wcrt
r_static
r_inline
r_void
id|vga_wcrt
(paren
id|caddr_t
id|regbase
comma
r_int
r_char
id|reg
comma
r_int
r_char
id|val
)paren
(brace
macro_line|#ifdef VGA_OUTW_WRITE
id|vga_w_fast
(paren
id|regbase
comma
id|VGA_CRT_IC
comma
id|reg
comma
id|val
)paren
suffix:semicolon
macro_line|#else
id|vga_w
(paren
id|regbase
comma
id|VGA_CRT_IC
comma
id|reg
)paren
suffix:semicolon
id|vga_w
(paren
id|regbase
comma
id|VGA_CRT_DC
comma
id|val
)paren
suffix:semicolon
macro_line|#endif /* VGA_OUTW_WRITE */
)brace
DECL|function|vga_io_rcrt
r_static
r_inline
r_int
r_char
id|vga_io_rcrt
(paren
r_int
r_char
id|reg
)paren
(brace
id|vga_io_w
(paren
id|VGA_CRT_IC
comma
id|reg
)paren
suffix:semicolon
r_return
id|vga_io_r
(paren
id|VGA_CRT_DC
)paren
suffix:semicolon
)brace
DECL|function|vga_io_wcrt
r_static
r_inline
r_void
id|vga_io_wcrt
(paren
r_int
r_char
id|reg
comma
r_int
r_char
id|val
)paren
(brace
macro_line|#ifdef VGA_OUTW_WRITE
id|vga_io_w_fast
(paren
id|VGA_CRT_IC
comma
id|reg
comma
id|val
)paren
suffix:semicolon
macro_line|#else
id|vga_io_w
(paren
id|VGA_CRT_IC
comma
id|reg
)paren
suffix:semicolon
id|vga_io_w
(paren
id|VGA_CRT_DC
comma
id|val
)paren
suffix:semicolon
macro_line|#endif /* VGA_OUTW_WRITE */
)brace
DECL|function|vga_mm_rcrt
r_static
r_inline
r_int
r_char
id|vga_mm_rcrt
(paren
id|caddr_t
id|regbase
comma
r_int
r_char
id|reg
)paren
(brace
id|vga_mm_w
(paren
id|regbase
comma
id|VGA_CRT_IC
comma
id|reg
)paren
suffix:semicolon
r_return
id|vga_mm_r
(paren
id|regbase
comma
id|VGA_CRT_DC
)paren
suffix:semicolon
)brace
DECL|function|vga_mm_wcrt
r_static
r_inline
r_void
id|vga_mm_wcrt
(paren
id|caddr_t
id|regbase
comma
r_int
r_char
id|reg
comma
r_int
r_char
id|val
)paren
(brace
macro_line|#ifdef VGA_OUTW_WRITE
id|vga_mm_w_fast
(paren
id|regbase
comma
id|VGA_CRT_IC
comma
id|reg
comma
id|val
)paren
suffix:semicolon
macro_line|#else
id|vga_mm_w
(paren
id|regbase
comma
id|VGA_CRT_IC
comma
id|reg
)paren
suffix:semicolon
id|vga_mm_w
(paren
id|regbase
comma
id|VGA_CRT_DC
comma
id|val
)paren
suffix:semicolon
macro_line|#endif /* VGA_OUTW_WRITE */
)brace
multiline_comment|/*&n; * VGA sequencer register read/write&n; */
DECL|function|vga_rseq
r_static
r_inline
r_int
r_char
id|vga_rseq
(paren
id|caddr_t
id|regbase
comma
r_int
r_char
id|reg
)paren
(brace
id|vga_w
(paren
id|regbase
comma
id|VGA_SEQ_I
comma
id|reg
)paren
suffix:semicolon
r_return
id|vga_r
(paren
id|regbase
comma
id|VGA_SEQ_D
)paren
suffix:semicolon
)brace
DECL|function|vga_wseq
r_static
r_inline
r_void
id|vga_wseq
(paren
id|caddr_t
id|regbase
comma
r_int
r_char
id|reg
comma
r_int
r_char
id|val
)paren
(brace
macro_line|#ifdef VGA_OUTW_WRITE
id|vga_w_fast
(paren
id|regbase
comma
id|VGA_SEQ_I
comma
id|reg
comma
id|val
)paren
suffix:semicolon
macro_line|#else
id|vga_w
(paren
id|regbase
comma
id|VGA_SEQ_I
comma
id|reg
)paren
suffix:semicolon
id|vga_w
(paren
id|regbase
comma
id|VGA_SEQ_D
comma
id|val
)paren
suffix:semicolon
macro_line|#endif /* VGA_OUTW_WRITE */
)brace
DECL|function|vga_io_rseq
r_static
r_inline
r_int
r_char
id|vga_io_rseq
(paren
r_int
r_char
id|reg
)paren
(brace
id|vga_io_w
(paren
id|VGA_SEQ_I
comma
id|reg
)paren
suffix:semicolon
r_return
id|vga_io_r
(paren
id|VGA_SEQ_D
)paren
suffix:semicolon
)brace
DECL|function|vga_io_wseq
r_static
r_inline
r_void
id|vga_io_wseq
(paren
r_int
r_char
id|reg
comma
r_int
r_char
id|val
)paren
(brace
macro_line|#ifdef VGA_OUTW_WRITE
id|vga_io_w_fast
(paren
id|VGA_SEQ_I
comma
id|reg
comma
id|val
)paren
suffix:semicolon
macro_line|#else
id|vga_io_w
(paren
id|VGA_SEQ_I
comma
id|reg
)paren
suffix:semicolon
id|vga_io_w
(paren
id|VGA_SEQ_D
comma
id|val
)paren
suffix:semicolon
macro_line|#endif /* VGA_OUTW_WRITE */
)brace
DECL|function|vga_mm_rseq
r_static
r_inline
r_int
r_char
id|vga_mm_rseq
(paren
id|caddr_t
id|regbase
comma
r_int
r_char
id|reg
)paren
(brace
id|vga_mm_w
(paren
id|regbase
comma
id|VGA_SEQ_I
comma
id|reg
)paren
suffix:semicolon
r_return
id|vga_mm_r
(paren
id|regbase
comma
id|VGA_SEQ_D
)paren
suffix:semicolon
)brace
DECL|function|vga_mm_wseq
r_static
r_inline
r_void
id|vga_mm_wseq
(paren
id|caddr_t
id|regbase
comma
r_int
r_char
id|reg
comma
r_int
r_char
id|val
)paren
(brace
macro_line|#ifdef VGA_OUTW_WRITE
id|vga_mm_w_fast
(paren
id|regbase
comma
id|VGA_SEQ_I
comma
id|reg
comma
id|val
)paren
suffix:semicolon
macro_line|#else
id|vga_mm_w
(paren
id|regbase
comma
id|VGA_SEQ_I
comma
id|reg
)paren
suffix:semicolon
id|vga_mm_w
(paren
id|regbase
comma
id|VGA_SEQ_D
comma
id|val
)paren
suffix:semicolon
macro_line|#endif /* VGA_OUTW_WRITE */
)brace
multiline_comment|/*&n; * VGA graphics controller register read/write&n; */
DECL|function|vga_rgfx
r_static
r_inline
r_int
r_char
id|vga_rgfx
(paren
id|caddr_t
id|regbase
comma
r_int
r_char
id|reg
)paren
(brace
id|vga_w
(paren
id|regbase
comma
id|VGA_GFX_I
comma
id|reg
)paren
suffix:semicolon
r_return
id|vga_r
(paren
id|regbase
comma
id|VGA_GFX_D
)paren
suffix:semicolon
)brace
DECL|function|vga_wgfx
r_static
r_inline
r_void
id|vga_wgfx
(paren
id|caddr_t
id|regbase
comma
r_int
r_char
id|reg
comma
r_int
r_char
id|val
)paren
(brace
macro_line|#ifdef VGA_OUTW_WRITE
id|vga_w_fast
(paren
id|regbase
comma
id|VGA_GFX_I
comma
id|reg
comma
id|val
)paren
suffix:semicolon
macro_line|#else
id|vga_w
(paren
id|regbase
comma
id|VGA_GFX_I
comma
id|reg
)paren
suffix:semicolon
id|vga_w
(paren
id|regbase
comma
id|VGA_GFX_D
comma
id|val
)paren
suffix:semicolon
macro_line|#endif /* VGA_OUTW_WRITE */
)brace
DECL|function|vga_io_rgfx
r_static
r_inline
r_int
r_char
id|vga_io_rgfx
(paren
r_int
r_char
id|reg
)paren
(brace
id|vga_io_w
(paren
id|VGA_GFX_I
comma
id|reg
)paren
suffix:semicolon
r_return
id|vga_io_r
(paren
id|VGA_GFX_D
)paren
suffix:semicolon
)brace
DECL|function|vga_io_wgfx
r_static
r_inline
r_void
id|vga_io_wgfx
(paren
r_int
r_char
id|reg
comma
r_int
r_char
id|val
)paren
(brace
macro_line|#ifdef VGA_OUTW_WRITE
id|vga_io_w_fast
(paren
id|VGA_GFX_I
comma
id|reg
comma
id|val
)paren
suffix:semicolon
macro_line|#else
id|vga_io_w
(paren
id|VGA_GFX_I
comma
id|reg
)paren
suffix:semicolon
id|vga_io_w
(paren
id|VGA_GFX_D
comma
id|val
)paren
suffix:semicolon
macro_line|#endif /* VGA_OUTW_WRITE */
)brace
DECL|function|vga_mm_rgfx
r_static
r_inline
r_int
r_char
id|vga_mm_rgfx
(paren
id|caddr_t
id|regbase
comma
r_int
r_char
id|reg
)paren
(brace
id|vga_mm_w
(paren
id|regbase
comma
id|VGA_GFX_I
comma
id|reg
)paren
suffix:semicolon
r_return
id|vga_mm_r
(paren
id|regbase
comma
id|VGA_GFX_D
)paren
suffix:semicolon
)brace
DECL|function|vga_mm_wgfx
r_static
r_inline
r_void
id|vga_mm_wgfx
(paren
id|caddr_t
id|regbase
comma
r_int
r_char
id|reg
comma
r_int
r_char
id|val
)paren
(brace
macro_line|#ifdef VGA_OUTW_WRITE
id|vga_mm_w_fast
(paren
id|regbase
comma
id|VGA_GFX_I
comma
id|reg
comma
id|val
)paren
suffix:semicolon
macro_line|#else
id|vga_mm_w
(paren
id|regbase
comma
id|VGA_GFX_I
comma
id|reg
)paren
suffix:semicolon
id|vga_mm_w
(paren
id|regbase
comma
id|VGA_GFX_D
comma
id|val
)paren
suffix:semicolon
macro_line|#endif /* VGA_OUTW_WRITE */
)brace
multiline_comment|/*&n; * VGA attribute controller register read/write&n; */
DECL|function|vga_rattr
r_static
r_inline
r_int
r_char
id|vga_rattr
(paren
id|caddr_t
id|regbase
comma
r_int
r_char
id|reg
)paren
(brace
id|vga_w
(paren
id|regbase
comma
id|VGA_ATT_IW
comma
id|reg
)paren
suffix:semicolon
r_return
id|vga_r
(paren
id|regbase
comma
id|VGA_ATT_R
)paren
suffix:semicolon
)brace
DECL|function|vga_wattr
r_static
r_inline
r_void
id|vga_wattr
(paren
id|caddr_t
id|regbase
comma
r_int
r_char
id|reg
comma
r_int
r_char
id|val
)paren
(brace
id|vga_w
(paren
id|regbase
comma
id|VGA_ATT_IW
comma
id|reg
)paren
suffix:semicolon
id|vga_w
(paren
id|regbase
comma
id|VGA_ATT_W
comma
id|val
)paren
suffix:semicolon
)brace
DECL|function|vga_io_rattr
r_static
r_inline
r_int
r_char
id|vga_io_rattr
(paren
r_int
r_char
id|reg
)paren
(brace
id|vga_io_w
(paren
id|VGA_ATT_IW
comma
id|reg
)paren
suffix:semicolon
r_return
id|vga_io_r
(paren
id|VGA_ATT_R
)paren
suffix:semicolon
)brace
DECL|function|vga_io_wattr
r_static
r_inline
r_void
id|vga_io_wattr
(paren
r_int
r_char
id|reg
comma
r_int
r_char
id|val
)paren
(brace
id|vga_io_w
(paren
id|VGA_ATT_IW
comma
id|reg
)paren
suffix:semicolon
id|vga_io_w
(paren
id|VGA_ATT_W
comma
id|val
)paren
suffix:semicolon
)brace
DECL|function|vga_mm_rattr
r_static
r_inline
r_int
r_char
id|vga_mm_rattr
(paren
id|caddr_t
id|regbase
comma
r_int
r_char
id|reg
)paren
(brace
id|vga_mm_w
(paren
id|regbase
comma
id|VGA_ATT_IW
comma
id|reg
)paren
suffix:semicolon
r_return
id|vga_mm_r
(paren
id|regbase
comma
id|VGA_ATT_R
)paren
suffix:semicolon
)brace
DECL|function|vga_mm_wattr
r_static
r_inline
r_void
id|vga_mm_wattr
(paren
id|caddr_t
id|regbase
comma
r_int
r_char
id|reg
comma
r_int
r_char
id|val
)paren
(brace
id|vga_mm_w
(paren
id|regbase
comma
id|VGA_ATT_IW
comma
id|reg
)paren
suffix:semicolon
id|vga_mm_w
(paren
id|regbase
comma
id|VGA_ATT_W
comma
id|val
)paren
suffix:semicolon
)brace
macro_line|#endif /* __linux_video_vga_h__ */
eof
