multiline_comment|/****************************************************************************&n; *******                                                              *******&n; *******        B O O T    P A C K E T   H E A D E R   F I L E&n; *******                                                              *******&n; ****************************************************************************&n;&n; Author  : Ian Nandhra&n; Date    :&n;&n; *&n; *  (C) 1990 - 2000 Specialix International Ltd., Byfleet, Surrey, UK.&n; *&n; *      This program is free software; you can redistribute it and/or modify&n; *      it under the terms of the GNU General Public License as published by&n; *      the Free Software Foundation; either version 2 of the License, or&n; *      (at your option) any later version.&n; *&n; *      This program is distributed in the hope that it will be useful,&n; *      but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *      GNU General Public License for more details.&n; *&n; *      You should have received a copy of the GNU General Public License&n; *      along with this program; if not, write to the Free Software&n; *      Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n; Version : 0.01&n;&n;&n;                            Mods&n; ----------------------------------------------------------------------------&n;  Date     By                Description&n; ----------------------------------------------------------------------------&n;&n; ***************************************************************************/
macro_line|#ifndef _pkt_h
DECL|macro|_pkt_h
mdefine_line|#define _pkt_h 1
macro_line|#ifndef lint
macro_line|#ifdef SCCS
DECL|variable|_rio_bootpkt_h_sccs
r_static
r_char
op_star
id|_rio_bootpkt_h_sccs
op_assign
l_string|&quot;@(#)bootpkt.h&t;1.1&quot;
suffix:semicolon
macro_line|#endif
macro_line|#endif
multiline_comment|/*************************************************&n;     * Overlayed onto the Data fields of a regular&n;     * Packet&n;     ************************************************/
DECL|typedef|BOOT_PKT
r_typedef
r_struct
id|BOOT_PKT
id|BOOT_PKT
suffix:semicolon
DECL|struct|BOOT_PKT
r_struct
id|BOOT_PKT
(brace
DECL|member|seq_num
r_int
id|seq_num
suffix:semicolon
DECL|member|data
r_char
id|data
(braket
l_int|10
)braket
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
multiline_comment|/*********** end of file ***********/
eof
