multiline_comment|/****************************************************************************&n; *******                                                              *******&n; *******                      L T T&n; *******                                                              *******&n; ****************************************************************************&n;&n; Author  : Ian Nandhra / Jeremy Rolls&n; Date    :&n;&n; *&n; *  (C) 1990 - 2000 Specialix International Ltd., Byfleet, Surrey, UK.&n; *&n; *      This program is free software; you can redistribute it and/or modify&n; *      it under the terms of the GNU General Public License as published by&n; *      the Free Software Foundation; either version 2 of the License, or&n; *      (at your option) any later version.&n; *&n; *      This program is distributed in the hope that it will be useful,&n; *      but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *      GNU General Public License for more details.&n; *&n; *      You should have received a copy of the GNU General Public License&n; *      along with this program; if not, write to the Free Software&n; *      Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n; Version : 0.01&n;&n;&n;                            Mods&n; ----------------------------------------------------------------------------&n;  Date     By                Description&n; ----------------------------------------------------------------------------&n;&n; ***************************************************************************/
macro_line|#ifndef lint
macro_line|#ifdef SCCS_LABELS
DECL|variable|_rio_ltt_h_sccs
r_static
r_char
op_star
id|_rio_ltt_h_sccs
op_assign
l_string|&quot;@(#)ltt.h&t;1.1&quot;
suffix:semicolon
macro_line|#endif
macro_line|#endif
macro_line|#ifdef DCIRRUS
DECL|macro|LTT_STACK
mdefine_line|#define LTT_STACK       (unsigned short)  600
macro_line|#else
DECL|macro|LTT_STACK
mdefine_line|#define LTT_STACK       (ushort) 200
macro_line|#endif
multiline_comment|/*********** end of file ***********/
eof
