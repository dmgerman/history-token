multiline_comment|/*&n;   Driver for the SAA5246A or SAA5281 Teletext (=Videotext) decoder chips from&n;   Philips.&n;&n;   Copyright (C) 2004 Michael Geng (linux@MichaelGeng.de)&n;&n;   This program is free software; you can redistribute it and/or modify&n;   it under the terms of the GNU General Public License as published by&n;   the Free Software Foundation; either version 2 of the License, or&n;   (at your option) any later version.&n;&n;   This program is distributed in the hope that it will be useful,&n;   but WITHOUT ANY WARRANTY; without even the implied warranty of&n;   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;   GNU General Public License for more details.&n;&n;   You should have received a copy of the GNU General Public License&n;   along with this program; if not, write to the Free Software&n;   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n; */
macro_line|#ifndef __SAA5246A_H__
DECL|macro|__SAA5246A_H__
mdefine_line|#define __SAA5246A_H__
DECL|macro|MAJOR_VERSION
mdefine_line|#define MAJOR_VERSION 1&t;&t;/* driver major version number */
DECL|macro|MINOR_VERSION
mdefine_line|#define MINOR_VERSION 8&t;&t;/* driver minor version number */
DECL|macro|IF_NAME
mdefine_line|#define IF_NAME &quot;SAA5246A&quot;
DECL|macro|I2C_ADDRESS
mdefine_line|#define I2C_ADDRESS 17
multiline_comment|/* Number of DAUs = number of pages that can be searched at the same time. */
DECL|macro|NUM_DAUS
mdefine_line|#define NUM_DAUS 4
DECL|macro|NUM_ROWS_PER_PAGE
mdefine_line|#define NUM_ROWS_PER_PAGE 40
multiline_comment|/* first column is 0 (not 1) */
DECL|macro|POS_TIME_START
mdefine_line|#define POS_TIME_START 32
DECL|macro|POS_TIME_END
mdefine_line|#define POS_TIME_END 39
DECL|macro|POS_HEADER_START
mdefine_line|#define POS_HEADER_START 7
DECL|macro|POS_HEADER_END
mdefine_line|#define POS_HEADER_END 31
multiline_comment|/* Returns TRUE if the part of the videotext page described with req contains&n;   (at least parts of) the time field */
DECL|macro|REQ_CONTAINS_TIME
mdefine_line|#define REQ_CONTAINS_TIME(p_req) &bslash;&n;&t;((p_req)-&gt;start &lt;= POS_TIME_END &amp;&amp; &bslash;&n;&t; (p_req)-&gt;end   &gt;= POS_TIME_START)
multiline_comment|/* Returns TRUE if the part of the videotext page described with req contains&n;   (at least parts of) the page header */
DECL|macro|REQ_CONTAINS_HEADER
mdefine_line|#define REQ_CONTAINS_HEADER(p_req) &bslash;&n;&t;((p_req)-&gt;start &lt;= POS_HEADER_END &amp;&amp; &bslash;&n;&t; (p_req)-&gt;end   &gt;= POS_HEADER_START)
macro_line|#ifndef FALSE
DECL|macro|FALSE
mdefine_line|#define FALSE 0
DECL|macro|TRUE
mdefine_line|#define TRUE 1
macro_line|#endif
multiline_comment|/*****************************************************************************/
multiline_comment|/* Mode register numbers of the SAA5246A&t;&t;&t;&t;     */
multiline_comment|/*****************************************************************************/
DECL|macro|SAA5246A_REGISTER_R0
mdefine_line|#define SAA5246A_REGISTER_R0    0
DECL|macro|SAA5246A_REGISTER_R1
mdefine_line|#define SAA5246A_REGISTER_R1    1
DECL|macro|SAA5246A_REGISTER_R2
mdefine_line|#define SAA5246A_REGISTER_R2    2
DECL|macro|SAA5246A_REGISTER_R3
mdefine_line|#define SAA5246A_REGISTER_R3    3
DECL|macro|SAA5246A_REGISTER_R4
mdefine_line|#define SAA5246A_REGISTER_R4    4
DECL|macro|SAA5246A_REGISTER_R5
mdefine_line|#define SAA5246A_REGISTER_R5    5
DECL|macro|SAA5246A_REGISTER_R6
mdefine_line|#define SAA5246A_REGISTER_R6    6
DECL|macro|SAA5246A_REGISTER_R7
mdefine_line|#define SAA5246A_REGISTER_R7    7
DECL|macro|SAA5246A_REGISTER_R8
mdefine_line|#define SAA5246A_REGISTER_R8    8
DECL|macro|SAA5246A_REGISTER_R9
mdefine_line|#define SAA5246A_REGISTER_R9    9
DECL|macro|SAA5246A_REGISTER_R10
mdefine_line|#define SAA5246A_REGISTER_R10  10
DECL|macro|SAA5246A_REGISTER_R11
mdefine_line|#define SAA5246A_REGISTER_R11  11
DECL|macro|SAA5246A_REGISTER_R11B
mdefine_line|#define SAA5246A_REGISTER_R11B 11
multiline_comment|/* SAA5246A mode registers often autoincrement to the next register.&n;   Therefore we use variable argument lists. The following macro indicates&n;   the end of a command list. */
DECL|macro|COMMAND_END
mdefine_line|#define COMMAND_END (- 1)
multiline_comment|/*****************************************************************************/
multiline_comment|/* Contents of the mode registers of the SAA5246A&t;&t;&t;     */
multiline_comment|/*****************************************************************************/
multiline_comment|/* Register R0 (Advanced Control) */
DECL|macro|R0_SELECT_R11
mdefine_line|#define R0_SELECT_R11&t;&t;&t;&t;&t;   0x00
DECL|macro|R0_SELECT_R11B
mdefine_line|#define R0_SELECT_R11B&t;&t;&t;&t;&t;   0x01
DECL|macro|R0_PLL_TIME_CONSTANT_LONG
mdefine_line|#define R0_PLL_TIME_CONSTANT_LONG&t;&t;&t;   0x00
DECL|macro|R0_PLL_TIME_CONSTANT_SHORT
mdefine_line|#define R0_PLL_TIME_CONSTANT_SHORT&t;&t;&t;   0x02
DECL|macro|R0_ENABLE_nODD_EVEN_OUTPUT
mdefine_line|#define R0_ENABLE_nODD_EVEN_OUTPUT&t;&t;&t;   0x00
DECL|macro|R0_DISABLE_nODD_EVEN_OUTPUT
mdefine_line|#define R0_DISABLE_nODD_EVEN_OUTPUT&t;&t;&t;   0x04
DECL|macro|R0_ENABLE_HDR_POLL
mdefine_line|#define R0_ENABLE_HDR_POLL&t;&t;&t;&t;   0x00
DECL|macro|R0_DISABLE_HDR_POLL
mdefine_line|#define R0_DISABLE_HDR_POLL&t;&t;&t;&t;   0x10
DECL|macro|R0_DO_NOT_FORCE_nODD_EVEN_LOW_IF_PICTURE_DISPLAYED
mdefine_line|#define R0_DO_NOT_FORCE_nODD_EVEN_LOW_IF_PICTURE_DISPLAYED 0x00
DECL|macro|R0_FORCE_nODD_EVEN_LOW_IF_PICTURE_DISPLAYED
mdefine_line|#define R0_FORCE_nODD_EVEN_LOW_IF_PICTURE_DISPLAYED&t;   0x20
DECL|macro|R0_NO_FREE_RUN_PLL
mdefine_line|#define R0_NO_FREE_RUN_PLL&t;&t;&t;&t;   0x00
DECL|macro|R0_FREE_RUN_PLL
mdefine_line|#define R0_FREE_RUN_PLL&t;&t;&t;&t;&t;   0x40
DECL|macro|R0_NO_AUTOMATIC_FASTEXT_PROMPT
mdefine_line|#define R0_NO_AUTOMATIC_FASTEXT_PROMPT&t;&t;&t;   0x00
DECL|macro|R0_AUTOMATIC_FASTEXT_PROMPT
mdefine_line|#define R0_AUTOMATIC_FASTEXT_PROMPT&t;&t;&t;   0x80
multiline_comment|/* Register R1 (Mode) */
DECL|macro|R1_INTERLACED_312_AND_HALF_312_AND_HALF_LINES
mdefine_line|#define R1_INTERLACED_312_AND_HALF_312_AND_HALF_LINES&t;   0x00
DECL|macro|R1_NON_INTERLACED_312_313_LINES
mdefine_line|#define R1_NON_INTERLACED_312_313_LINES&t;&t;&t;   0x01
DECL|macro|R1_NON_INTERLACED_312_312_LINES
mdefine_line|#define R1_NON_INTERLACED_312_312_LINES&t;&t;&t;   0x02
DECL|macro|R1_FFB_LEADING_EDGE_IN_FIRST_BROAD_PULSE
mdefine_line|#define R1_FFB_LEADING_EDGE_IN_FIRST_BROAD_PULSE&t;   0x03
DECL|macro|R1_FFB_LEADING_EDGE_IN_SECOND_BROAD_PULSE
mdefine_line|#define R1_FFB_LEADING_EDGE_IN_SECOND_BROAD_PULSE&t;   0x07
DECL|macro|R1_DEW
mdefine_line|#define R1_DEW&t;&t;&t;&t;&t;&t;   0x00
DECL|macro|R1_FULL_FIELD
mdefine_line|#define R1_FULL_FIELD&t;&t;&t;&t;&t;   0x08
DECL|macro|R1_EXTENDED_PACKET_DISABLE
mdefine_line|#define R1_EXTENDED_PACKET_DISABLE&t;&t;&t;   0x00
DECL|macro|R1_EXTENDED_PACKET_ENABLE
mdefine_line|#define R1_EXTENDED_PACKET_ENABLE&t;&t;&t;   0x10
DECL|macro|R1_DAUS_ALL_ON
mdefine_line|#define R1_DAUS_ALL_ON&t;&t;&t;&t;&t;   0x00
DECL|macro|R1_DAUS_ALL_OFF
mdefine_line|#define R1_DAUS_ALL_OFF&t;&t;&t;&t;&t;   0x20
DECL|macro|R1_7_BITS_PLUS_PARITY
mdefine_line|#define R1_7_BITS_PLUS_PARITY&t;&t;&t;&t;   0x00
DECL|macro|R1_8_BITS_NO_PARITY
mdefine_line|#define R1_8_BITS_NO_PARITY&t;&t;&t;&t;   0x40
DECL|macro|R1_VCS_TO_SCS
mdefine_line|#define R1_VCS_TO_SCS&t;&t;&t;&t;&t;   0x00
DECL|macro|R1_NO_VCS_TO_SCS
mdefine_line|#define R1_NO_VCS_TO_SCS&t;&t;&t;&t;   0x80
multiline_comment|/* Register R2 (Page request address) */
DECL|macro|R2_IN_R3_SELECT_PAGE_HUNDREDS
mdefine_line|#define R2_IN_R3_SELECT_PAGE_HUNDREDS&t;&t;&t;   0x00
DECL|macro|R2_IN_R3_SELECT_PAGE_TENS
mdefine_line|#define R2_IN_R3_SELECT_PAGE_TENS&t;&t;&t;   0x01
DECL|macro|R2_IN_R3_SELECT_PAGE_UNITS
mdefine_line|#define R2_IN_R3_SELECT_PAGE_UNITS&t;&t;&t;   0x02
DECL|macro|R2_IN_R3_SELECT_HOURS_TENS
mdefine_line|#define R2_IN_R3_SELECT_HOURS_TENS&t;&t;&t;   0x03
DECL|macro|R2_IN_R3_SELECT_HOURS_UNITS
mdefine_line|#define R2_IN_R3_SELECT_HOURS_UNITS&t;&t;&t;   0x04
DECL|macro|R2_IN_R3_SELECT_MINUTES_TENS
mdefine_line|#define R2_IN_R3_SELECT_MINUTES_TENS&t;&t;&t;   0x05
DECL|macro|R2_IN_R3_SELECT_MINUTES_UNITS
mdefine_line|#define R2_IN_R3_SELECT_MINUTES_UNITS&t;&t;&t;   0x06
DECL|macro|R2_DAU_0
mdefine_line|#define R2_DAU_0&t;&t;&t;&t;&t;   0x00
DECL|macro|R2_DAU_1
mdefine_line|#define R2_DAU_1&t;&t;&t;&t;&t;   0x10
DECL|macro|R2_DAU_2
mdefine_line|#define R2_DAU_2&t;&t;&t;&t;&t;   0x20
DECL|macro|R2_DAU_3
mdefine_line|#define R2_DAU_3&t;&t;&t;&t;&t;   0x30
DECL|macro|R2_BANK_0
mdefine_line|#define R2_BANK_0&t;&t;&t;&t;&t;   0x00
DECL|macro|R2_BANK
mdefine_line|#define R2_BANK 1&t;&t;&t;&t;&t;   0x40
DECL|macro|R2_HAMMING_CHECK_ON
mdefine_line|#define R2_HAMMING_CHECK_ON&t;&t;&t;&t;   0x80
DECL|macro|R2_HAMMING_CHECK_OFF
mdefine_line|#define R2_HAMMING_CHECK_OFF&t;&t;&t;&t;   0x00
multiline_comment|/* Register R3 (Page request data) */
DECL|macro|R3_PAGE_HUNDREDS_0
mdefine_line|#define R3_PAGE_HUNDREDS_0&t;&t;&t;&t;   0x00
DECL|macro|R3_PAGE_HUNDREDS_1
mdefine_line|#define R3_PAGE_HUNDREDS_1&t;&t;&t;&t;   0x01
DECL|macro|R3_PAGE_HUNDREDS_2
mdefine_line|#define R3_PAGE_HUNDREDS_2&t;&t;&t;&t;   0x02
DECL|macro|R3_PAGE_HUNDREDS_3
mdefine_line|#define R3_PAGE_HUNDREDS_3&t;&t;&t;&t;   0x03
DECL|macro|R3_PAGE_HUNDREDS_4
mdefine_line|#define R3_PAGE_HUNDREDS_4&t;&t;&t;&t;   0x04
DECL|macro|R3_PAGE_HUNDREDS_5
mdefine_line|#define R3_PAGE_HUNDREDS_5&t;&t;&t;&t;   0x05
DECL|macro|R3_PAGE_HUNDREDS_6
mdefine_line|#define R3_PAGE_HUNDREDS_6&t;&t;&t;&t;   0x06
DECL|macro|R3_PAGE_HUNDREDS_7
mdefine_line|#define R3_PAGE_HUNDREDS_7&t;&t;&t;&t;   0x07
DECL|macro|R3_HOLD_PAGE
mdefine_line|#define R3_HOLD_PAGE&t;&t;&t;&t;&t;   0x00
DECL|macro|R3_UPDATE_PAGE
mdefine_line|#define R3_UPDATE_PAGE&t;&t;&t;&t;&t;   0x08
DECL|macro|R3_PAGE_HUNDREDS_DO_NOT_CARE
mdefine_line|#define R3_PAGE_HUNDREDS_DO_NOT_CARE&t;&t;&t;   0x00
DECL|macro|R3_PAGE_HUNDREDS_DO_CARE
mdefine_line|#define R3_PAGE_HUNDREDS_DO_CARE&t;&t;&t;   0x10
DECL|macro|R3_PAGE_TENS_DO_NOT_CARE
mdefine_line|#define R3_PAGE_TENS_DO_NOT_CARE&t;&t;&t;   0x00
DECL|macro|R3_PAGE_TENS_DO_CARE
mdefine_line|#define R3_PAGE_TENS_DO_CARE&t;&t;&t;&t;   0x10
DECL|macro|R3_PAGE_UNITS_DO_NOT_CARE
mdefine_line|#define R3_PAGE_UNITS_DO_NOT_CARE&t;&t;&t;   0x00
DECL|macro|R3_PAGE_UNITS_DO_CARE
mdefine_line|#define R3_PAGE_UNITS_DO_CARE&t;&t;&t;&t;   0x10
DECL|macro|R3_HOURS_TENS_DO_NOT_CARE
mdefine_line|#define R3_HOURS_TENS_DO_NOT_CARE&t;&t;&t;   0x00
DECL|macro|R3_HOURS_TENS_DO_CARE
mdefine_line|#define R3_HOURS_TENS_DO_CARE&t;&t;&t;&t;   0x10
DECL|macro|R3_HOURS_UNITS_DO_NOT_CARE
mdefine_line|#define R3_HOURS_UNITS_DO_NOT_CARE&t;&t;&t;   0x00
DECL|macro|R3_HOURS_UNITS_DO_CARE
mdefine_line|#define R3_HOURS_UNITS_DO_CARE&t;&t;&t;&t;   0x10
DECL|macro|R3_MINUTES_TENS_DO_NOT_CARE
mdefine_line|#define R3_MINUTES_TENS_DO_NOT_CARE&t;&t;&t;   0x00
DECL|macro|R3_MINUTES_TENS_DO_CARE
mdefine_line|#define R3_MINUTES_TENS_DO_CARE&t;&t;&t;&t;   0x10
DECL|macro|R3_MINUTES_UNITS_DO_NOT_CARE
mdefine_line|#define R3_MINUTES_UNITS_DO_NOT_CARE&t;&t;&t;   0x00
DECL|macro|R3_MINUTES_UNITS_DO_CARE
mdefine_line|#define R3_MINUTES_UNITS_DO_CARE&t;&t;&t;   0x10
multiline_comment|/* Register R4 (Display chapter) */
DECL|macro|R4_DISPLAY_PAGE_0
mdefine_line|#define R4_DISPLAY_PAGE_0&t;&t;&t;&t;   0x00
DECL|macro|R4_DISPLAY_PAGE_1
mdefine_line|#define R4_DISPLAY_PAGE_1&t;&t;&t;&t;   0x01
DECL|macro|R4_DISPLAY_PAGE_2
mdefine_line|#define R4_DISPLAY_PAGE_2&t;&t;&t;&t;   0x02
DECL|macro|R4_DISPLAY_PAGE_3
mdefine_line|#define R4_DISPLAY_PAGE_3&t;&t;&t;&t;   0x03
DECL|macro|R4_DISPLAY_PAGE_4
mdefine_line|#define R4_DISPLAY_PAGE_4&t;&t;&t;&t;   0x04
DECL|macro|R4_DISPLAY_PAGE_5
mdefine_line|#define R4_DISPLAY_PAGE_5&t;&t;&t;&t;   0x05
DECL|macro|R4_DISPLAY_PAGE_6
mdefine_line|#define R4_DISPLAY_PAGE_6&t;&t;&t;&t;   0x06
DECL|macro|R4_DISPLAY_PAGE_7
mdefine_line|#define R4_DISPLAY_PAGE_7&t;&t;&t;&t;   0x07
multiline_comment|/* Register R5 (Normal display control) */
DECL|macro|R5_PICTURE_INSIDE_BOXING_OFF
mdefine_line|#define R5_PICTURE_INSIDE_BOXING_OFF&t;&t;&t;   0x00
DECL|macro|R5_PICTURE_INSIDE_BOXING_ON
mdefine_line|#define R5_PICTURE_INSIDE_BOXING_ON&t;&t;&t;   0x01
DECL|macro|R5_PICTURE_OUTSIDE_BOXING_OFF
mdefine_line|#define R5_PICTURE_OUTSIDE_BOXING_OFF&t;&t;&t;   0x00
DECL|macro|R5_PICTURE_OUTSIDE_BOXING_ON
mdefine_line|#define R5_PICTURE_OUTSIDE_BOXING_ON&t;&t;&t;   0x02
DECL|macro|R5_TEXT_INSIDE_BOXING_OFF
mdefine_line|#define R5_TEXT_INSIDE_BOXING_OFF&t;&t;&t;   0x00
DECL|macro|R5_TEXT_INSIDE_BOXING_ON
mdefine_line|#define R5_TEXT_INSIDE_BOXING_ON&t;&t;&t;   0x04
DECL|macro|R5_TEXT_OUTSIDE_BOXING_OFF
mdefine_line|#define R5_TEXT_OUTSIDE_BOXING_OFF&t;&t;&t;   0x00
DECL|macro|R5_TEXT_OUTSIDE_BOXING_ON
mdefine_line|#define R5_TEXT_OUTSIDE_BOXING_ON&t;&t;&t;   0x08
DECL|macro|R5_CONTRAST_REDUCTION_INSIDE_BOXING_OFF
mdefine_line|#define R5_CONTRAST_REDUCTION_INSIDE_BOXING_OFF&t;&t;   0x00
DECL|macro|R5_CONTRAST_REDUCTION_INSIDE_BOXING_ON
mdefine_line|#define R5_CONTRAST_REDUCTION_INSIDE_BOXING_ON&t;&t;   0x10
DECL|macro|R5_CONTRAST_REDUCTION_OUTSIDE_BOXING_OFF
mdefine_line|#define R5_CONTRAST_REDUCTION_OUTSIDE_BOXING_OFF&t;   0x00
DECL|macro|R5_CONTRAST_REDUCTION_OUTSIDE_BOXING_ON
mdefine_line|#define R5_CONTRAST_REDUCTION_OUTSIDE_BOXING_ON&t;&t;   0x20
DECL|macro|R5_BACKGROUND_COLOR_INSIDE_BOXING_OFF
mdefine_line|#define R5_BACKGROUND_COLOR_INSIDE_BOXING_OFF&t;&t;   0x00
DECL|macro|R5_BACKGROUND_COLOR_INSIDE_BOXING_ON
mdefine_line|#define R5_BACKGROUND_COLOR_INSIDE_BOXING_ON&t;&t;   0x40
DECL|macro|R5_BACKGROUND_COLOR_OUTSIDE_BOXING_OFF
mdefine_line|#define R5_BACKGROUND_COLOR_OUTSIDE_BOXING_OFF&t;&t;   0x00
DECL|macro|R5_BACKGROUND_COLOR_OUTSIDE_BOXING_ON
mdefine_line|#define R5_BACKGROUND_COLOR_OUTSIDE_BOXING_ON&t;&t;   0x80
multiline_comment|/* Register R6 (Newsflash display) */
DECL|macro|R6_NEWSFLASH_PICTURE_INSIDE_BOXING_OFF
mdefine_line|#define R6_NEWSFLASH_PICTURE_INSIDE_BOXING_OFF&t;&t;   0x00
DECL|macro|R6_NEWSFLASH_PICTURE_INSIDE_BOXING_ON
mdefine_line|#define R6_NEWSFLASH_PICTURE_INSIDE_BOXING_ON&t;&t;   0x01
DECL|macro|R6_NEWSFLASH_PICTURE_OUTSIDE_BOXING_OFF
mdefine_line|#define R6_NEWSFLASH_PICTURE_OUTSIDE_BOXING_OFF&t;&t;   0x00
DECL|macro|R6_NEWSFLASH_PICTURE_OUTSIDE_BOXING_ON
mdefine_line|#define R6_NEWSFLASH_PICTURE_OUTSIDE_BOXING_ON&t;&t;   0x02
DECL|macro|R6_NEWSFLASH_TEXT_INSIDE_BOXING_OFF
mdefine_line|#define R6_NEWSFLASH_TEXT_INSIDE_BOXING_OFF&t;&t;   0x00
DECL|macro|R6_NEWSFLASH_TEXT_INSIDE_BOXING_ON
mdefine_line|#define R6_NEWSFLASH_TEXT_INSIDE_BOXING_ON&t;&t;   0x04
DECL|macro|R6_NEWSFLASH_TEXT_OUTSIDE_BOXING_OFF
mdefine_line|#define R6_NEWSFLASH_TEXT_OUTSIDE_BOXING_OFF&t;&t;   0x00
DECL|macro|R6_NEWSFLASH_TEXT_OUTSIDE_BOXING_ON
mdefine_line|#define R6_NEWSFLASH_TEXT_OUTSIDE_BOXING_ON&t;&t;   0x08
DECL|macro|R6_NEWSFLASH_CONTRAST_REDUCTION_INSIDE_BOXING_OFF
mdefine_line|#define R6_NEWSFLASH_CONTRAST_REDUCTION_INSIDE_BOXING_OFF  0x00
DECL|macro|R6_NEWSFLASH_CONTRAST_REDUCTION_INSIDE_BOXING_ON
mdefine_line|#define R6_NEWSFLASH_CONTRAST_REDUCTION_INSIDE_BOXING_ON   0x10
DECL|macro|R6_NEWSFLASH_CONTRAST_REDUCTION_OUTSIDE_BOXING_OFF
mdefine_line|#define R6_NEWSFLASH_CONTRAST_REDUCTION_OUTSIDE_BOXING_OFF 0x00
DECL|macro|R6_NEWSFLASH_CONTRAST_REDUCTION_OUTSIDE_BOXING_ON
mdefine_line|#define R6_NEWSFLASH_CONTRAST_REDUCTION_OUTSIDE_BOXING_ON  0x20
DECL|macro|R6_NEWSFLASH_BACKGROUND_COLOR_INSIDE_BOXING_OFF
mdefine_line|#define R6_NEWSFLASH_BACKGROUND_COLOR_INSIDE_BOXING_OFF    0x00
DECL|macro|R6_NEWSFLASH_BACKGROUND_COLOR_INSIDE_BOXING_ON
mdefine_line|#define R6_NEWSFLASH_BACKGROUND_COLOR_INSIDE_BOXING_ON&t;   0x40
DECL|macro|R6_NEWSFLASH_BACKGROUND_COLOR_OUTSIDE_BOXING_OFF
mdefine_line|#define R6_NEWSFLASH_BACKGROUND_COLOR_OUTSIDE_BOXING_OFF   0x00
DECL|macro|R6_NEWSFLASH_BACKGROUND_COLOR_OUTSIDE_BOXING_ON
mdefine_line|#define R6_NEWSFLASH_BACKGROUND_COLOR_OUTSIDE_BOXING_ON    0x80
multiline_comment|/* Register R7 (Display mode) */
DECL|macro|R7_BOX_OFF_ROW_0
mdefine_line|#define R7_BOX_OFF_ROW_0&t;&t;&t;&t;   0x00
DECL|macro|R7_BOX_ON_ROW_0
mdefine_line|#define R7_BOX_ON_ROW_0&t;&t;&t;&t;&t;   0x01
DECL|macro|R7_BOX_OFF_ROW_1_TO_23
mdefine_line|#define R7_BOX_OFF_ROW_1_TO_23&t;&t;&t;&t;   0x00
DECL|macro|R7_BOX_ON_ROW_1_TO_23
mdefine_line|#define R7_BOX_ON_ROW_1_TO_23&t;&t;&t;&t;   0x02
DECL|macro|R7_BOX_OFF_ROW_24
mdefine_line|#define R7_BOX_OFF_ROW_24&t;&t;&t;&t;   0x00
DECL|macro|R7_BOX_ON_ROW_24
mdefine_line|#define R7_BOX_ON_ROW_24&t;&t;&t;&t;   0x04
DECL|macro|R7_SINGLE_HEIGHT
mdefine_line|#define R7_SINGLE_HEIGHT&t;&t;&t;&t;   0x00
DECL|macro|R7_DOUBLE_HEIGHT
mdefine_line|#define R7_DOUBLE_HEIGHT&t;&t;&t;&t;   0x08
DECL|macro|R7_TOP_HALF
mdefine_line|#define R7_TOP_HALF&t;&t;&t;&t;&t;   0x00
DECL|macro|R7_BOTTOM_HALF
mdefine_line|#define R7_BOTTOM_HALF&t;&t;&t;&t;&t;   0x10
DECL|macro|R7_REVEAL_OFF
mdefine_line|#define R7_REVEAL_OFF&t;&t;&t;&t;&t;   0x00
DECL|macro|R7_REVEAL_ON
mdefine_line|#define R7_REVEAL_ON&t;&t;&t;&t;&t;   0x20
DECL|macro|R7_CURSER_OFF
mdefine_line|#define R7_CURSER_OFF&t;&t;&t;&t;&t;   0x00
DECL|macro|R7_CURSER_ON
mdefine_line|#define R7_CURSER_ON&t;&t;&t;&t;&t;   0x40
DECL|macro|R7_STATUS_BOTTOM
mdefine_line|#define R7_STATUS_BOTTOM&t;&t;&t;&t;   0x00
DECL|macro|R7_STATUS_TOP
mdefine_line|#define R7_STATUS_TOP&t;&t;&t;&t;&t;   0x80
multiline_comment|/* Register R8 (Active chapter) */
DECL|macro|R8_ACTIVE_CHAPTER_0
mdefine_line|#define R8_ACTIVE_CHAPTER_0&t;&t;&t;&t;   0x00
DECL|macro|R8_ACTIVE_CHAPTER_1
mdefine_line|#define R8_ACTIVE_CHAPTER_1&t;&t;&t;&t;   0x01
DECL|macro|R8_ACTIVE_CHAPTER_2
mdefine_line|#define R8_ACTIVE_CHAPTER_2&t;&t;&t;&t;   0x02
DECL|macro|R8_ACTIVE_CHAPTER_3
mdefine_line|#define R8_ACTIVE_CHAPTER_3&t;&t;&t;&t;   0x03
DECL|macro|R8_ACTIVE_CHAPTER_4
mdefine_line|#define R8_ACTIVE_CHAPTER_4&t;&t;&t;&t;   0x04
DECL|macro|R8_ACTIVE_CHAPTER_5
mdefine_line|#define R8_ACTIVE_CHAPTER_5&t;&t;&t;&t;   0x05
DECL|macro|R8_ACTIVE_CHAPTER_6
mdefine_line|#define R8_ACTIVE_CHAPTER_6&t;&t;&t;&t;   0x06
DECL|macro|R8_ACTIVE_CHAPTER_7
mdefine_line|#define R8_ACTIVE_CHAPTER_7&t;&t;&t;&t;   0x07
DECL|macro|R8_CLEAR_MEMORY
mdefine_line|#define R8_CLEAR_MEMORY&t;&t;&t;&t;&t;   0x08
DECL|macro|R8_DO_NOT_CLEAR_MEMORY
mdefine_line|#define R8_DO_NOT_CLEAR_MEMORY&t;&t;&t;&t;   0x00
multiline_comment|/* Register R9 (Curser row) */
DECL|macro|R9_CURSER_ROW_0
mdefine_line|#define R9_CURSER_ROW_0&t;&t;&t;&t;&t;   0x00
DECL|macro|R9_CURSER_ROW_1
mdefine_line|#define R9_CURSER_ROW_1&t;&t;&t;&t;&t;   0x01
DECL|macro|R9_CURSER_ROW_2
mdefine_line|#define R9_CURSER_ROW_2&t;&t;&t;&t;&t;   0x02
DECL|macro|R9_CURSER_ROW_25
mdefine_line|#define R9_CURSER_ROW_25&t;&t;&t;&t;   0x19
multiline_comment|/* Register R10 (Curser column) */
DECL|macro|R10_CURSER_COLUMN_0
mdefine_line|#define R10_CURSER_COLUMN_0&t;&t;&t;&t;   0x00
DECL|macro|R10_CURSER_COLUMN_6
mdefine_line|#define R10_CURSER_COLUMN_6&t;&t;&t;&t;   0x06
DECL|macro|R10_CURSER_COLUMN_8
mdefine_line|#define R10_CURSER_COLUMN_8&t;&t;&t;&t;   0x08
multiline_comment|/*****************************************************************************/
multiline_comment|/* Row 25 control data in column 0 to 9&t;&t;&t;&t;&t;     */
multiline_comment|/*****************************************************************************/
DECL|macro|ROW25_COLUMN0_PAGE_UNITS
mdefine_line|#define ROW25_COLUMN0_PAGE_UNITS&t;&t;&t;   0x0F
DECL|macro|ROW25_COLUMN1_PAGE_TENS
mdefine_line|#define ROW25_COLUMN1_PAGE_TENS&t;&t;&t;&t;   0x0F
DECL|macro|ROW25_COLUMN2_MINUTES_UNITS
mdefine_line|#define ROW25_COLUMN2_MINUTES_UNITS&t;&t;&t;   0x0F
DECL|macro|ROW25_COLUMN3_MINUTES_TENS
mdefine_line|#define ROW25_COLUMN3_MINUTES_TENS&t;&t;&t;   0x07
DECL|macro|ROW25_COLUMN3_DELETE_PAGE
mdefine_line|#define ROW25_COLUMN3_DELETE_PAGE&t;&t;&t;   0x08
DECL|macro|ROW25_COLUMN4_HOUR_UNITS
mdefine_line|#define ROW25_COLUMN4_HOUR_UNITS&t;&t;&t;   0x0F
DECL|macro|ROW25_COLUMN5_HOUR_TENS
mdefine_line|#define ROW25_COLUMN5_HOUR_TENS&t;&t;&t;&t;   0x03
DECL|macro|ROW25_COLUMN5_INSERT_HEADLINE
mdefine_line|#define ROW25_COLUMN5_INSERT_HEADLINE&t;&t;&t;   0x04
DECL|macro|ROW25_COLUMN5_INSERT_SUBTITLE
mdefine_line|#define ROW25_COLUMN5_INSERT_SUBTITLE&t;&t;&t;   0x08
DECL|macro|ROW25_COLUMN6_SUPPRESS_HEADER
mdefine_line|#define ROW25_COLUMN6_SUPPRESS_HEADER&t;&t;&t;   0x01
DECL|macro|ROW25_COLUMN6_UPDATE_PAGE
mdefine_line|#define ROW25_COLUMN6_UPDATE_PAGE&t;&t;&t;   0x02
DECL|macro|ROW25_COLUMN6_INTERRUPTED_SEQUENCE
mdefine_line|#define ROW25_COLUMN6_INTERRUPTED_SEQUENCE&t;&t;   0x04
DECL|macro|ROW25_COLUMN6_SUPPRESS_DISPLAY
mdefine_line|#define ROW25_COLUMN6_SUPPRESS_DISPLAY&t;&t;&t;   0x08
DECL|macro|ROW25_COLUMN7_SERIAL_MODE
mdefine_line|#define ROW25_COLUMN7_SERIAL_MODE&t;&t;&t;   0x01
DECL|macro|ROW25_COLUMN7_CHARACTER_SET
mdefine_line|#define ROW25_COLUMN7_CHARACTER_SET&t;&t;&t;   0x0E
DECL|macro|ROW25_COLUMN8_PAGE_HUNDREDS
mdefine_line|#define ROW25_COLUMN8_PAGE_HUNDREDS&t;&t;&t;   0x07
DECL|macro|ROW25_COLUMN8_PAGE_NOT_FOUND
mdefine_line|#define ROW25_COLUMN8_PAGE_NOT_FOUND&t;&t;&t;   0x10
DECL|macro|ROW25_COLUMN9_PAGE_BEING_LOOKED_FOR
mdefine_line|#define ROW25_COLUMN9_PAGE_BEING_LOOKED_FOR&t;&t;   0x20
DECL|macro|ROW25_COLUMN0_TO_7_HAMMING_ERROR
mdefine_line|#define ROW25_COLUMN0_TO_7_HAMMING_ERROR&t;&t;   0x10
multiline_comment|/*****************************************************************************/
multiline_comment|/* Helper macros for extracting page, hour and minute digits&t;&t;     */
multiline_comment|/*****************************************************************************/
multiline_comment|/* BYTE_POS  0 is at row 0, column 0,&n;   BYTE_POS  1 is at row 0, column 1,&n;   BYTE_POS 40 is at row 1, column 0, (with NUM_ROWS_PER_PAGE = 40)&n;   BYTE_POS 41 is at row 1, column 1, (with NUM_ROWS_PER_PAGE = 40),&n;   ... */
DECL|macro|ROW
mdefine_line|#define ROW(BYTE_POS)    (BYTE_POS / NUM_ROWS_PER_PAGE)
DECL|macro|COLUMN
mdefine_line|#define COLUMN(BYTE_POS) (BYTE_POS % NUM_ROWS_PER_PAGE)
multiline_comment|/*****************************************************************************/
multiline_comment|/* Helper macros for extracting page, hour and minute digits&t;&t;     */
multiline_comment|/*****************************************************************************/
multiline_comment|/* Macros for extracting hundreds, tens and units of a page number which&n;   must be in the range 0 ... 0x799.&n;   Note that page is coded in hexadecimal, i.e. 0x123 means page 123.&n;   page 0x.. means page 8.. */
DECL|macro|HUNDREDS_OF_PAGE
mdefine_line|#define HUNDREDS_OF_PAGE(page) (((page) / 0x100) &amp; 0x7)
DECL|macro|TENS_OF_PAGE
mdefine_line|#define TENS_OF_PAGE(page)     (((page) / 0x10)  &amp; 0xF)
DECL|macro|UNITS_OF_PAGE
mdefine_line|#define UNITS_OF_PAGE(page)     ((page) &amp; 0xF)
multiline_comment|/* Macros for extracting tens and units of a hour information which&n;   must be in the range 0 ... 0x24.&n;   Note that hour is coded in hexadecimal, i.e. 0x12 means 12 hours */
DECL|macro|TENS_OF_HOUR
mdefine_line|#define TENS_OF_HOUR(hour)  ((hour) / 0x10)
DECL|macro|UNITS_OF_HOUR
mdefine_line|#define UNITS_OF_HOUR(hour) ((hour) &amp; 0xF)
multiline_comment|/* Macros for extracting tens and units of a minute information which&n;   must be in the range 0 ... 0x59.&n;   Note that minute is coded in hexadecimal, i.e. 0x12 means 12 minutes */
DECL|macro|TENS_OF_MINUTE
mdefine_line|#define TENS_OF_MINUTE(minute)  ((minute) / 0x10)
DECL|macro|UNITS_OF_MINUTE
mdefine_line|#define UNITS_OF_MINUTE(minute) ((minute) &amp; 0xF)
DECL|macro|HOUR_MAX
mdefine_line|#define HOUR_MAX   0x23
DECL|macro|MINUTE_MAX
mdefine_line|#define MINUTE_MAX 0x59
DECL|macro|PAGE_MAX
mdefine_line|#define PAGE_MAX   0x8FF
macro_line|#endif  /* __SAA5246A_H__ */
eof
