multiline_comment|/*&n; * BRIEF MODULE DESCRIPTION&n; *&t;Hardware definitions for the Au1100 LCD controller&n; *&n; * Copyright 2002 MontaVista Software&n; * Copyright 2002 Alchemy Semiconductor&n; * Author:&t;Alchemy Semiconductor, MontaVista Software&n; *&n; *  This program is free software; you can redistribute&t; it and/or modify it&n; *  under  the terms of&t; the GNU General  Public License as published by the&n; *  Free Software Foundation;  either version 2 of the&t;License, or (at your&n; *  option) any later version.&n; *&n; *  THIS  SOFTWARE  IS PROVIDED&t;  ``AS&t;IS&squot;&squot; AND   ANY&t;EXPRESS OR IMPLIED&n; *  WARRANTIES,&t;  INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN&n; *  NO&t;EVENT  SHALL   THE AUTHOR  BE&t; LIABLE FOR ANY&t;  DIRECT, INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; *  NOT LIMITED&t;  TO, PROCUREMENT OF  SUBSTITUTE GOODS&t;OR SERVICES; LOSS OF&n; *  USE, DATA,&t;OR PROFITS; OR&t;BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; *  ANY THEORY OF LIABILITY, WHETHER IN&t; CONTRACT, STRICT LIABILITY, OR TORT&n; *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the  GNU General Public License along&n; *  with this program; if not, write  to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#ifndef _AU1100LCD_H
DECL|macro|_AU1100LCD_H
mdefine_line|#define _AU1100LCD_H
multiline_comment|/********************************************************************/
DECL|macro|uint32
mdefine_line|#define uint32 unsigned long
r_typedef
r_volatile
r_struct
(brace
DECL|member|lcd_control
id|uint32
id|lcd_control
suffix:semicolon
DECL|member|lcd_intstatus
id|uint32
id|lcd_intstatus
suffix:semicolon
DECL|member|lcd_intenable
id|uint32
id|lcd_intenable
suffix:semicolon
DECL|member|lcd_horztiming
id|uint32
id|lcd_horztiming
suffix:semicolon
DECL|member|lcd_verttiming
id|uint32
id|lcd_verttiming
suffix:semicolon
DECL|member|lcd_clkcontrol
id|uint32
id|lcd_clkcontrol
suffix:semicolon
DECL|member|lcd_dmaaddr0
id|uint32
id|lcd_dmaaddr0
suffix:semicolon
DECL|member|lcd_dmaaddr1
id|uint32
id|lcd_dmaaddr1
suffix:semicolon
DECL|member|lcd_words
id|uint32
id|lcd_words
suffix:semicolon
DECL|member|lcd_pwmdiv
id|uint32
id|lcd_pwmdiv
suffix:semicolon
DECL|member|lcd_pwmhi
id|uint32
id|lcd_pwmhi
suffix:semicolon
DECL|member|reserved
id|uint32
id|reserved
(braket
(paren
l_int|0x0400
op_minus
l_int|0x002C
)paren
op_div
l_int|4
)braket
suffix:semicolon
DECL|member|lcd_pallettebase
id|uint32
id|lcd_pallettebase
(braket
l_int|256
)braket
suffix:semicolon
DECL|typedef|AU1100_LCD
)brace
id|AU1100_LCD
suffix:semicolon
multiline_comment|/********************************************************************/
DECL|macro|AU1100_LCD_ADDR
mdefine_line|#define AU1100_LCD_ADDR&t;&t;0xB5000000
multiline_comment|/*&n; * Register bit definitions&n; */
multiline_comment|/* lcd_control */
DECL|macro|LCD_CONTROL_SBPPF
mdefine_line|#define LCD_CONTROL_SBPPF&t;&t;(7&lt;&lt;18)
DECL|macro|LCD_CONTROL_SBPPF_655
mdefine_line|#define LCD_CONTROL_SBPPF_655&t;(0&lt;&lt;18)
DECL|macro|LCD_CONTROL_SBPPF_565
mdefine_line|#define LCD_CONTROL_SBPPF_565&t;(1&lt;&lt;18)
DECL|macro|LCD_CONTROL_SBPPF_556
mdefine_line|#define LCD_CONTROL_SBPPF_556&t;(2&lt;&lt;18)
DECL|macro|LCD_CONTROL_SBPPF_1555
mdefine_line|#define LCD_CONTROL_SBPPF_1555&t;(3&lt;&lt;18)
DECL|macro|LCD_CONTROL_SBPPF_5551
mdefine_line|#define LCD_CONTROL_SBPPF_5551&t;(4&lt;&lt;18)
DECL|macro|LCD_CONTROL_WP
mdefine_line|#define LCD_CONTROL_WP&t;&t;&t;(1&lt;&lt;17)
DECL|macro|LCD_CONTROL_WD
mdefine_line|#define LCD_CONTROL_WD&t;&t;&t;(1&lt;&lt;16)
DECL|macro|LCD_CONTROL_C
mdefine_line|#define LCD_CONTROL_C&t;&t;&t;(1&lt;&lt;15)
DECL|macro|LCD_CONTROL_SM
mdefine_line|#define LCD_CONTROL_SM&t;&t;&t;(3&lt;&lt;13)
DECL|macro|LCD_CONTROL_SM_0
mdefine_line|#define LCD_CONTROL_SM_0&t;&t;(0&lt;&lt;13)
DECL|macro|LCD_CONTROL_SM_90
mdefine_line|#define LCD_CONTROL_SM_90&t;&t;(1&lt;&lt;13)
DECL|macro|LCD_CONTROL_SM_180
mdefine_line|#define LCD_CONTROL_SM_180&t;&t;(2&lt;&lt;13)
DECL|macro|LCD_CONTROL_SM_270
mdefine_line|#define LCD_CONTROL_SM_270&t;&t;(3&lt;&lt;13)
DECL|macro|LCD_CONTROL_DB
mdefine_line|#define LCD_CONTROL_DB&t;&t;&t;(1&lt;&lt;12)
DECL|macro|LCD_CONTROL_CCO
mdefine_line|#define LCD_CONTROL_CCO&t;&t;&t;(1&lt;&lt;11)
DECL|macro|LCD_CONTROL_DP
mdefine_line|#define LCD_CONTROL_DP&t;&t;&t;(1&lt;&lt;10)
DECL|macro|LCD_CONTROL_PO
mdefine_line|#define LCD_CONTROL_PO&t;&t;&t;(3&lt;&lt;8)
DECL|macro|LCD_CONTROL_PO_00
mdefine_line|#define LCD_CONTROL_PO_00&t;&t;(0&lt;&lt;8)
DECL|macro|LCD_CONTROL_PO_01
mdefine_line|#define LCD_CONTROL_PO_01&t;&t;(1&lt;&lt;8)
DECL|macro|LCD_CONTROL_PO_10
mdefine_line|#define LCD_CONTROL_PO_10&t;&t;(2&lt;&lt;8)
DECL|macro|LCD_CONTROL_PO_11
mdefine_line|#define LCD_CONTROL_PO_11&t;&t;(3&lt;&lt;8)
DECL|macro|LCD_CONTROL_MPI
mdefine_line|#define LCD_CONTROL_MPI&t;&t;&t;(1&lt;&lt;7)
DECL|macro|LCD_CONTROL_PT
mdefine_line|#define LCD_CONTROL_PT&t;&t;&t;(1&lt;&lt;6)
DECL|macro|LCD_CONTROL_PC
mdefine_line|#define LCD_CONTROL_PC&t;&t;&t;(1&lt;&lt;5)
DECL|macro|LCD_CONTROL_BPP
mdefine_line|#define LCD_CONTROL_BPP&t;&t;&t;(7&lt;&lt;1)
DECL|macro|LCD_CONTROL_BPP_1
mdefine_line|#define LCD_CONTROL_BPP_1&t;&t;(0&lt;&lt;1)
DECL|macro|LCD_CONTROL_BPP_2
mdefine_line|#define LCD_CONTROL_BPP_2&t;&t;(1&lt;&lt;1)
DECL|macro|LCD_CONTROL_BPP_4
mdefine_line|#define LCD_CONTROL_BPP_4&t;&t;(2&lt;&lt;1)
DECL|macro|LCD_CONTROL_BPP_8
mdefine_line|#define LCD_CONTROL_BPP_8&t;&t;(3&lt;&lt;1)
DECL|macro|LCD_CONTROL_BPP_12
mdefine_line|#define LCD_CONTROL_BPP_12&t;&t;(4&lt;&lt;1)
DECL|macro|LCD_CONTROL_BPP_16
mdefine_line|#define LCD_CONTROL_BPP_16&t;&t;(5&lt;&lt;1)
DECL|macro|LCD_CONTROL_GO
mdefine_line|#define LCD_CONTROL_GO&t;&t;&t;(1&lt;&lt;0)
multiline_comment|/* lcd_intstatus, lcd_intenable */
DECL|macro|LCD_INT_SD
mdefine_line|#define LCD_INT_SD&t;&t;&t;&t;(1&lt;&lt;7)
DECL|macro|LCD_INT_OF
mdefine_line|#define LCD_INT_OF&t;&t;&t;&t;(1&lt;&lt;6)
DECL|macro|LCD_INT_UF
mdefine_line|#define LCD_INT_UF&t;&t;&t;&t;(1&lt;&lt;5)
DECL|macro|LCD_INT_SA
mdefine_line|#define LCD_INT_SA&t;&t;&t;&t;(1&lt;&lt;3)
DECL|macro|LCD_INT_SS
mdefine_line|#define LCD_INT_SS&t;&t;&t;&t;(1&lt;&lt;2)
DECL|macro|LCD_INT_S1
mdefine_line|#define LCD_INT_S1&t;&t;&t;&t;(1&lt;&lt;1)
DECL|macro|LCD_INT_S0
mdefine_line|#define LCD_INT_S0&t;&t;&t;&t;(1&lt;&lt;0)
multiline_comment|/* lcd_horztiming */
DECL|macro|LCD_HORZTIMING_HN2
mdefine_line|#define LCD_HORZTIMING_HN2&t;&t;(255&lt;&lt;24)
DECL|macro|LCD_HORZTIMING_HN2_N
mdefine_line|#define LCD_HORZTIMING_HN2_N(N)&t;(((N)-1)&lt;&lt;24)
DECL|macro|LCD_HORZTIMING_HN1
mdefine_line|#define LCD_HORZTIMING_HN1&t;&t;(255&lt;&lt;16)
DECL|macro|LCD_HORZTIMING_HN1_N
mdefine_line|#define LCD_HORZTIMING_HN1_N(N)&t;(((N)-1)&lt;&lt;16)
DECL|macro|LCD_HORZTIMING_HPW
mdefine_line|#define LCD_HORZTIMING_HPW&t;&t;(63&lt;&lt;10)
DECL|macro|LCD_HORZTIMING_HPW_N
mdefine_line|#define LCD_HORZTIMING_HPW_N(N)&t;(((N)-1)&lt;&lt;10)
DECL|macro|LCD_HORZTIMING_PPL
mdefine_line|#define LCD_HORZTIMING_PPL&t;&t;(1023&lt;&lt;0)
DECL|macro|LCD_HORZTIMING_PPL_N
mdefine_line|#define LCD_HORZTIMING_PPL_N(N)&t;(((N)-1)&lt;&lt;0)
multiline_comment|/* lcd_verttiming */
DECL|macro|LCD_VERTTIMING_VN2
mdefine_line|#define LCD_VERTTIMING_VN2&t;&t;(255&lt;&lt;24)
DECL|macro|LCD_VERTTIMING_VN2_N
mdefine_line|#define LCD_VERTTIMING_VN2_N(N)&t;(((N)-1)&lt;&lt;24)
DECL|macro|LCD_VERTTIMING_VN1
mdefine_line|#define LCD_VERTTIMING_VN1&t;&t;(255&lt;&lt;16)
DECL|macro|LCD_VERTTIMING_VN1_N
mdefine_line|#define LCD_VERTTIMING_VN1_N(N)&t;(((N)-1)&lt;&lt;16)
DECL|macro|LCD_VERTTIMING_VPW
mdefine_line|#define LCD_VERTTIMING_VPW&t;&t;(63&lt;&lt;10)
DECL|macro|LCD_VERTTIMING_VPW_N
mdefine_line|#define LCD_VERTTIMING_VPW_N(N)&t;(((N)-1)&lt;&lt;10)
DECL|macro|LCD_VERTTIMING_LPP
mdefine_line|#define LCD_VERTTIMING_LPP&t;&t;(1023&lt;&lt;0)
DECL|macro|LCD_VERTTIMING_LPP_N
mdefine_line|#define LCD_VERTTIMING_LPP_N(N)&t;(((N)-1)&lt;&lt;0)
multiline_comment|/* lcd_clkcontrol */
DECL|macro|LCD_CLKCONTROL_IB
mdefine_line|#define LCD_CLKCONTROL_IB&t;&t;(1&lt;&lt;18)
DECL|macro|LCD_CLKCONTROL_IC
mdefine_line|#define LCD_CLKCONTROL_IC&t;&t;(1&lt;&lt;17)
DECL|macro|LCD_CLKCONTROL_IH
mdefine_line|#define LCD_CLKCONTROL_IH&t;&t;(1&lt;&lt;16)
DECL|macro|LCD_CLKCONTROL_IV
mdefine_line|#define LCD_CLKCONTROL_IV&t;&t;(1&lt;&lt;15)
DECL|macro|LCD_CLKCONTROL_BF
mdefine_line|#define LCD_CLKCONTROL_BF&t;&t;(31&lt;&lt;10)
DECL|macro|LCD_CLKCONTROL_BF_N
mdefine_line|#define LCD_CLKCONTROL_BF_N(N)&t;(((N)-1)&lt;&lt;10)
DECL|macro|LCD_CLKCONTROL_PCD
mdefine_line|#define LCD_CLKCONTROL_PCD&t;&t;(1023&lt;&lt;0)
DECL|macro|LCD_CLKCONTROL_PCD_N
mdefine_line|#define LCD_CLKCONTROL_PCD_N(N)&t;((N)&lt;&lt;0)
multiline_comment|/* lcd_pwmdiv */
DECL|macro|LCD_PWMDIV_EN
mdefine_line|#define LCD_PWMDIV_EN&t;&t;&t;(1&lt;&lt;12)
DECL|macro|LCD_PWMDIV_PWMDIV
mdefine_line|#define LCD_PWMDIV_PWMDIV&t;&t;(2047&lt;&lt;0)
DECL|macro|LCD_PWMDIV_PWMDIV_N
mdefine_line|#define LCD_PWMDIV_PWMDIV_N(N)&t;(((N)-1)&lt;&lt;0)
multiline_comment|/* lcd_pwmhi */
DECL|macro|LCD_PWMHI_PWMHI1
mdefine_line|#define LCD_PWMHI_PWMHI1&t;&t;(2047&lt;&lt;12)
DECL|macro|LCD_PWMHI_PWMHI1_N
mdefine_line|#define LCD_PWMHI_PWMHI1_N(N)&t;((N)&lt;&lt;12)
DECL|macro|LCD_PWMHI_PWMHI0
mdefine_line|#define LCD_PWMHI_PWMHI0&t;&t;(2047&lt;&lt;0)
DECL|macro|LCD_PWMHI_PWMHI0_N
mdefine_line|#define LCD_PWMHI_PWMHI0_N(N)&t;((N)&lt;&lt;0)
multiline_comment|/* lcd_pallettebase - MONOCHROME */
DECL|macro|LCD_PALLETTE_MONO_MI
mdefine_line|#define LCD_PALLETTE_MONO_MI&t;&t;(15&lt;&lt;0)
DECL|macro|LCD_PALLETTE_MONO_MI_N
mdefine_line|#define LCD_PALLETTE_MONO_MI_N(N)&t;((N)&lt;&lt;0)
multiline_comment|/* lcd_pallettebase - COLOR */
DECL|macro|LCD_PALLETTE_COLOR_BI
mdefine_line|#define LCD_PALLETTE_COLOR_BI&t;&t;(15&lt;&lt;8)
DECL|macro|LCD_PALLETTE_COLOR_BI_N
mdefine_line|#define LCD_PALLETTE_COLOR_BI_N(N)&t;((N)&lt;&lt;8)
DECL|macro|LCD_PALLETTE_COLOR_GI
mdefine_line|#define LCD_PALLETTE_COLOR_GI&t;&t;(15&lt;&lt;4)
DECL|macro|LCD_PALLETTE_COLOR_GI_N
mdefine_line|#define LCD_PALLETTE_COLOR_GI_N(N)&t;((N)&lt;&lt;4)
DECL|macro|LCD_PALLETTE_COLOR_RI
mdefine_line|#define LCD_PALLETTE_COLOR_RI&t;&t;(15&lt;&lt;0)
DECL|macro|LCD_PALLETTE_COLOR_RI_N
mdefine_line|#define LCD_PALLETTE_COLOR_RI_N(N)&t;((N)&lt;&lt;0)
multiline_comment|/* lcd_palletebase - COLOR TFT PALLETIZED */
DECL|macro|LCD_PALLETTE_TFT_DC
mdefine_line|#define LCD_PALLETTE_TFT_DC&t;&t;&t;(65535&lt;&lt;0)
DECL|macro|LCD_PALLETTE_TFT_DC_N
mdefine_line|#define LCD_PALLETTE_TFT_DC_N(N)&t;((N)&lt;&lt;0)
multiline_comment|/********************************************************************/
DECL|struct|known_lcd_panels
r_struct
id|known_lcd_panels
(brace
DECL|member|xres
id|uint32
id|xres
suffix:semicolon
DECL|member|yres
id|uint32
id|yres
suffix:semicolon
DECL|member|bpp
id|uint32
id|bpp
suffix:semicolon
DECL|member|panel_name
r_int
r_char
id|panel_name
(braket
l_int|256
)braket
suffix:semicolon
DECL|member|mode_control
id|uint32
id|mode_control
suffix:semicolon
DECL|member|mode_horztiming
id|uint32
id|mode_horztiming
suffix:semicolon
DECL|member|mode_verttiming
id|uint32
id|mode_verttiming
suffix:semicolon
DECL|member|mode_clkcontrol
id|uint32
id|mode_clkcontrol
suffix:semicolon
DECL|member|mode_pwmdiv
id|uint32
id|mode_pwmdiv
suffix:semicolon
DECL|member|mode_pwmhi
id|uint32
id|mode_pwmhi
suffix:semicolon
DECL|member|mode_toyclksrc
id|uint32
id|mode_toyclksrc
suffix:semicolon
DECL|member|mode_backlight
id|uint32
id|mode_backlight
suffix:semicolon
)brace
suffix:semicolon
macro_line|#if defined(__BIG_ENDIAN)
DECL|macro|LCD_DEFAULT_PIX_FORMAT
mdefine_line|#define LCD_DEFAULT_PIX_FORMAT LCD_CONTROL_PO_11
macro_line|#else
DECL|macro|LCD_DEFAULT_PIX_FORMAT
mdefine_line|#define LCD_DEFAULT_PIX_FORMAT LCD_CONTROL_PO_00
macro_line|#endif
multiline_comment|/*&n; * The fb driver assumes that AUX PLL is at 48MHz.  That can&n; * cover up to 800x600 resolution; if you need higher resolution,&n; * you should modify the driver as needed, not just this structure.&n; */
DECL|variable|panels
r_struct
id|known_lcd_panels
id|panels
(braket
)braket
op_assign
(brace
(brace
multiline_comment|/* 0: Pb1100 LCDA: Sharp 320x240 TFT panel */
l_int|320
comma
multiline_comment|/* xres */
l_int|240
comma
multiline_comment|/* yres */
l_int|16
comma
multiline_comment|/* bpp  */
l_string|&quot;Sharp_320x240_16&quot;
comma
multiline_comment|/* mode_control */
(paren
id|LCD_CONTROL_SBPPF_565
multiline_comment|/*LCD_CONTROL_WP*/
multiline_comment|/*LCD_CONTROL_WD*/
op_or
id|LCD_CONTROL_C
op_or
id|LCD_CONTROL_SM_0
multiline_comment|/*LCD_CONTROL_DB*/
multiline_comment|/*LCD_CONTROL_CCO*/
multiline_comment|/*LCD_CONTROL_DP*/
op_or
id|LCD_DEFAULT_PIX_FORMAT
multiline_comment|/*LCD_CONTROL_MPI*/
op_or
id|LCD_CONTROL_PT
op_or
id|LCD_CONTROL_PC
op_or
id|LCD_CONTROL_BPP_16
)paren
comma
multiline_comment|/* mode_horztiming */
(paren
id|LCD_HORZTIMING_HN2_N
c_func
(paren
l_int|8
)paren
op_or
id|LCD_HORZTIMING_HN1_N
c_func
(paren
l_int|60
)paren
op_or
id|LCD_HORZTIMING_HPW_N
c_func
(paren
l_int|12
)paren
op_or
id|LCD_HORZTIMING_PPL_N
c_func
(paren
l_int|320
)paren
)paren
comma
multiline_comment|/* mode_verttiming */
(paren
id|LCD_VERTTIMING_VN2_N
c_func
(paren
l_int|5
)paren
op_or
id|LCD_VERTTIMING_VN1_N
c_func
(paren
l_int|17
)paren
op_or
id|LCD_VERTTIMING_VPW_N
c_func
(paren
l_int|1
)paren
op_or
id|LCD_VERTTIMING_LPP_N
c_func
(paren
l_int|240
)paren
)paren
comma
multiline_comment|/* mode_clkcontrol */
(paren
l_int|0
multiline_comment|/*LCD_CLKCONTROL_IB*/
multiline_comment|/*LCD_CLKCONTROL_IC*/
multiline_comment|/*LCD_CLKCONTROL_IH*/
multiline_comment|/*LCD_CLKCONTROL_IV*/
op_or
id|LCD_CLKCONTROL_PCD_N
c_func
(paren
l_int|1
)paren
)paren
comma
multiline_comment|/* mode_pwmdiv */
l_int|0
comma
multiline_comment|/* mode_pwmhi */
l_int|0
comma
multiline_comment|/* mode_toyclksrc */
(paren
(paren
l_int|1
op_lshift
l_int|7
)paren
op_or
(paren
l_int|1
op_lshift
l_int|6
)paren
op_or
(paren
l_int|1
op_lshift
l_int|5
)paren
)paren
comma
multiline_comment|/* mode_backlight */
l_int|6
)brace
comma
(brace
multiline_comment|/* 1: Pb1100 LCDC 640x480 TFT panel */
l_int|640
comma
multiline_comment|/* xres */
l_int|480
comma
multiline_comment|/* yres */
l_int|16
comma
multiline_comment|/* bpp  */
l_string|&quot;Generic_640x480_16&quot;
comma
multiline_comment|/* mode_control */
l_int|0x004806a
op_or
id|LCD_DEFAULT_PIX_FORMAT
comma
multiline_comment|/* mode_horztiming */
l_int|0x3434d67f
comma
multiline_comment|/* mode_verttiming */
l_int|0x0e0e39df
comma
multiline_comment|/* mode_clkcontrol */
(paren
l_int|0
multiline_comment|/*LCD_CLKCONTROL_IB*/
multiline_comment|/*LCD_CLKCONTROL_IC*/
multiline_comment|/*LCD_CLKCONTROL_IH*/
multiline_comment|/*LCD_CLKCONTROL_IV*/
op_or
id|LCD_CLKCONTROL_PCD_N
c_func
(paren
l_int|1
)paren
)paren
comma
multiline_comment|/* mode_pwmdiv */
l_int|0
comma
multiline_comment|/* mode_pwmhi */
l_int|0
comma
multiline_comment|/* mode_toyclksrc */
(paren
(paren
l_int|1
op_lshift
l_int|7
)paren
op_or
(paren
l_int|1
op_lshift
l_int|6
)paren
op_or
(paren
l_int|0
op_lshift
l_int|5
)paren
)paren
comma
multiline_comment|/* mode_backlight */
l_int|7
)brace
comma
(brace
multiline_comment|/* 2: Pb1100 LCDB 640x480 PrimeView TFT panel */
l_int|640
comma
multiline_comment|/* xres */
l_int|480
comma
multiline_comment|/* yres */
l_int|16
comma
multiline_comment|/* bpp  */
l_string|&quot;PrimeView_640x480_16&quot;
comma
multiline_comment|/* mode_control */
l_int|0x0004886a
op_or
id|LCD_DEFAULT_PIX_FORMAT
comma
multiline_comment|/* mode_horztiming */
l_int|0x0e4bfe7f
comma
multiline_comment|/* mode_verttiming */
l_int|0x210805df
comma
multiline_comment|/* mode_clkcontrol */
l_int|0x00038001
comma
multiline_comment|/* mode_pwmdiv */
l_int|0
comma
multiline_comment|/* mode_pwmhi */
l_int|0
comma
multiline_comment|/* mode_toyclksrc */
(paren
(paren
l_int|1
op_lshift
l_int|7
)paren
op_or
(paren
l_int|1
op_lshift
l_int|6
)paren
op_or
(paren
l_int|0
op_lshift
l_int|5
)paren
)paren
comma
multiline_comment|/* mode_backlight */
l_int|7
)brace
comma
(brace
multiline_comment|/* 3: Pb1100 800x600x16bpp NEON CRT */
l_int|800
comma
multiline_comment|/* xres */
l_int|600
comma
multiline_comment|/* yres */
l_int|16
comma
multiline_comment|/* bpp */
l_string|&quot;NEON_800x600_16&quot;
comma
multiline_comment|/* mode_control */
l_int|0x0004886A
op_or
id|LCD_DEFAULT_PIX_FORMAT
comma
multiline_comment|/* mode_horztiming */
l_int|0x005AFF1F
comma
multiline_comment|/* mode_verttiming */
l_int|0x16000E57
comma
multiline_comment|/* mode_clkcontrol */
l_int|0x00020000
comma
multiline_comment|/* mode_pwmdiv */
l_int|0
comma
multiline_comment|/* mode_pwmhi */
l_int|0
comma
multiline_comment|/* mode_toyclksrc */
(paren
(paren
l_int|1
op_lshift
l_int|7
)paren
op_or
(paren
l_int|1
op_lshift
l_int|6
)paren
op_or
(paren
l_int|0
op_lshift
l_int|5
)paren
)paren
comma
multiline_comment|/* mode_backlight */
l_int|7
)brace
comma
(brace
multiline_comment|/* 4: Pb1100 640x480x16bpp NEON CRT */
l_int|640
comma
multiline_comment|/* xres */
l_int|480
comma
multiline_comment|/* yres */
l_int|16
comma
multiline_comment|/* bpp */
l_string|&quot;NEON_640x480_16&quot;
comma
multiline_comment|/* mode_control */
l_int|0x0004886A
op_or
id|LCD_DEFAULT_PIX_FORMAT
comma
multiline_comment|/* mode_horztiming */
l_int|0x0052E27F
comma
multiline_comment|/* mode_verttiming */
l_int|0x18000DDF
comma
multiline_comment|/* mode_clkcontrol */
l_int|0x00020000
comma
multiline_comment|/* mode_pwmdiv */
l_int|0
comma
multiline_comment|/* mode_pwmhi */
l_int|0
comma
multiline_comment|/* mode_toyclksrc */
(paren
(paren
l_int|1
op_lshift
l_int|7
)paren
op_or
(paren
l_int|1
op_lshift
l_int|6
)paren
op_or
(paren
l_int|0
op_lshift
l_int|5
)paren
)paren
comma
multiline_comment|/* mode_backlight */
l_int|7
)brace
comma
)brace
suffix:semicolon
macro_line|#endif /* _AU1100LCD_H */
eof
