multiline_comment|/****************************************************************************&n; *******                                                              *******&n; *******          S Y S T E M   M A P   H E A D E R&n; *******                                                              *******&n; ****************************************************************************&n;&n; Author  : Ian Nandhra&n; Date    :&n;&n; *&n; *  (C) 1990 - 2000 Specialix International Ltd., Byfleet, Surrey, UK.&n; *&n; *      This program is free software; you can redistribute it and/or modify&n; *      it under the terms of the GNU General Public License as published by&n; *      the Free Software Foundation; either version 2 of the License, or&n; *      (at your option) any later version.&n; *&n; *      This program is distributed in the hope that it will be useful,&n; *      but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *      GNU General Public License for more details.&n; *&n; *      You should have received a copy of the GNU General Public License&n; *      along with this program; if not, write to the Free Software&n; *      Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n; Version : 0.01&n;&n;&n;                            Mods&n; ----------------------------------------------------------------------------&n;  Date     By                Description&n; ----------------------------------------------------------------------------&n;&n; ***************************************************************************/
macro_line|#ifndef lint
macro_line|#ifdef SCCS_LABELS
DECL|variable|_rio_sysmap_h_sccs
r_static
r_char
op_star
id|_rio_sysmap_h_sccs
op_assign
l_string|&quot;@(#)sysmap.h&t;1.1&quot;
suffix:semicolon
macro_line|#endif
macro_line|#endif
DECL|macro|SYSTEM_MAP_LEN
mdefine_line|#define SYSTEM_MAP_LEN     64           /* Len of System Map array */
DECL|typedef|SYS_MAP
r_typedef
r_struct
id|SYS_MAP
id|SYS_MAP
suffix:semicolon
DECL|typedef|SYS_MAP_LINK
r_typedef
r_struct
id|SYS_MAP_LINK
id|SYS_MAP_LINK
suffix:semicolon
DECL|struct|SYS_MAP_LINK
r_struct
id|SYS_MAP_LINK
(brace
DECL|member|id
r_int
id|id
suffix:semicolon
multiline_comment|/* Unit Id */
DECL|member|link
r_int
id|link
suffix:semicolon
multiline_comment|/* Id&squot;s Link */
DECL|member|been_here
r_int
id|been_here
suffix:semicolon
multiline_comment|/* Used by map_gen */
)brace
suffix:semicolon
DECL|struct|SYS_MAP
r_struct
id|SYS_MAP
(brace
DECL|member|serial_num
r_char
id|serial_num
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|link
id|SYS_MAP_LINK
id|link
(braket
l_int|4
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*********** end of file ***********/
eof
