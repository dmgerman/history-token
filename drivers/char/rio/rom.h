multiline_comment|/****************************************************************************&n; *******                                                              *******&n; *******                      R O M&n; *******                                                              *******&n; ****************************************************************************&n;&n; Author  : Ian Nandhra&n; Date    :&n;&n; *&n; *  (C) 1990 - 2000 Specialix International Ltd., Byfleet, Surrey, UK.&n; *&n; *      This program is free software; you can redistribute it and/or modify&n; *      it under the terms of the GNU General Public License as published by&n; *      the Free Software Foundation; either version 2 of the License, or&n; *      (at your option) any later version.&n; *&n; *      This program is distributed in the hope that it will be useful,&n; *      but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *      GNU General Public License for more details.&n; *&n; *      You should have received a copy of the GNU General Public License&n; *      along with this program; if not, write to the Free Software&n; *      Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n; Version : 0.01&n;&n;&n;                            Mods&n; ----------------------------------------------------------------------------&n;  Date     By                Description&n; ----------------------------------------------------------------------------&n;&n; ***************************************************************************/
macro_line|#ifndef _rom_h
DECL|macro|_rom_h
mdefine_line|#define _rom_h 1
macro_line|#ifndef lint
macro_line|#ifdef SCCS
DECL|variable|_rio_rom_h_sccs
r_static
r_char
op_star
id|_rio_rom_h_sccs
op_assign
l_string|&quot;@(#)rom.h&t;1.1&quot;
suffix:semicolon
macro_line|#endif
macro_line|#endif
DECL|typedef|ROM
r_typedef
r_struct
id|ROM
id|ROM
suffix:semicolon
DECL|struct|ROM
r_struct
id|ROM
(brace
DECL|member|slx
id|u_short
id|slx
suffix:semicolon
DECL|member|pcb_letter_rev
r_char
id|pcb_letter_rev
suffix:semicolon
DECL|member|pcb_number_rev
r_char
id|pcb_number_rev
suffix:semicolon
DECL|member|serial
r_char
id|serial
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|year
r_char
id|year
suffix:semicolon
DECL|member|week
r_char
id|week
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
DECL|macro|HOST_ROM
mdefine_line|#define HOST_ROM    (ROM *) 0x7c00
DECL|macro|RTA_ROM
mdefine_line|#define RTA_ROM&t;    (ROM *) 0x7801
DECL|macro|ROM_LENGTH
mdefine_line|#define ROM_LENGTH  0x20
multiline_comment|/*********** end of file ***********/
eof
