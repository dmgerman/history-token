multiline_comment|/****************************************************************************&n; *******                                                              *******&n; *******                R T A    H A R D W A R E&n; *******                                                              *******&n; ****************************************************************************&n;&n; Author  : Ian Nandhra&n; Date    :&n;&n; *&n; *  (C) 1990 - 2000 Specialix International Ltd., Byfleet, Surrey, UK.&n; *&n; *      This program is free software; you can redistribute it and/or modify&n; *      it under the terms of the GNU General Public License as published by&n; *      the Free Software Foundation; either version 2 of the License, or&n; *      (at your option) any later version.&n; *&n; *      This program is distributed in the hope that it will be useful,&n; *      but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *      GNU General Public License for more details.&n; *&n; *      You should have received a copy of the GNU General Public License&n; *      along with this program; if not, write to the Free Software&n; *      Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n; Version : 0.01&n;&n;&n;                            Mods&n; ----------------------------------------------------------------------------&n;  Date     By                Description&n; ----------------------------------------------------------------------------&n;&n; ***************************************************************************/
macro_line|#ifndef lint
macro_line|#ifdef SCCS_LABELS
DECL|variable|_rio_rtahw_h_sccs
r_static
r_char
op_star
id|_rio_rtahw_h_sccs
op_assign
l_string|&quot;@(#)rtahw.h&t;1.5&quot;
suffix:semicolon
macro_line|#endif
macro_line|#endif
DECL|macro|WATCHDOG_ADDR
mdefine_line|#define&t;WATCHDOG_ADDR&t;((unsigned short *)0x7a00)
DECL|macro|RTA_LED_ADDR
mdefine_line|#define RTA_LED_ADDR&t;((unsigned short *)0x7c00)
DECL|macro|SERIALNUM_ADDR
mdefine_line|#define SERIALNUM_ADDR&t;((unsigned char *)0x7809)
DECL|macro|LATCH_ADDR
mdefine_line|#define LATCH_ADDR      ((unsigned char *)0x7800)
multiline_comment|/*&n;** Here we define where the cd1400 chips are in memory.&n;*/
DECL|macro|CD1400_ONE_ADDR
mdefine_line|#define CD1400_ONE_ADDR&t;&t;(0x7300)
DECL|macro|CD1400_TWO_ADDR
mdefine_line|#define CD1400_TWO_ADDR&t;&t;(0x7200)
DECL|macro|CD1400_THREE_ADDR
mdefine_line|#define CD1400_THREE_ADDR&t;(0x7100)
DECL|macro|CD1400_FOUR_ADDR
mdefine_line|#define CD1400_FOUR_ADDR&t;(0x7000)
multiline_comment|/*&n;** Define the different types of modules we can have&n;*/
DECL|enum|module
r_enum
id|module
(brace
DECL|enumerator|MOD_BLANK
id|MOD_BLANK
op_assign
l_int|0x0f
comma
multiline_comment|/* Blank plate attached */
DECL|enumerator|MOD_RS232DB25
id|MOD_RS232DB25
op_assign
l_int|0x00
comma
multiline_comment|/* RS232 DB25 connector */
DECL|enumerator|MOD_RS232RJ45
id|MOD_RS232RJ45
op_assign
l_int|0x01
comma
multiline_comment|/* RS232 RJ45 connector */
DECL|enumerator|MOD_RS422DB25
id|MOD_RS422DB25
op_assign
l_int|0x02
comma
multiline_comment|/* RS422 DB25 connector */
DECL|enumerator|MOD_RS485DB25
id|MOD_RS485DB25
op_assign
l_int|0x03
comma
multiline_comment|/* RS485 DB25 connector */
DECL|enumerator|MOD_PARALLEL
id|MOD_PARALLEL
op_assign
l_int|0x04
multiline_comment|/* Centronics parallel */
)brace
suffix:semicolon
DECL|macro|TYPE_HOST
mdefine_line|#define TYPE_HOST&t;0
DECL|macro|TYPE_RTA8
mdefine_line|#define TYPE_RTA8&t;1
DECL|macro|TYPE_RTA16
mdefine_line|#define TYPE_RTA16&t;2
DECL|macro|WATCH_DOG
mdefine_line|#define&t;WATCH_DOG&t;WATCHDOG_ADDR
multiline_comment|/*********** end of file ***********/
eof
