multiline_comment|/****************************************************************************&n; *******                                                              *******&n; *******                H O S T      H A R D W A R E&n; *******                                                              *******&n; ****************************************************************************&n;&n; Author  : Ian Nandhra / Jeremy Rolls&n; Date    :&n;&n; *&n; *  (C) 1990 - 2000 Specialix International Ltd., Byfleet, Surrey, UK.&n; *&n; *      This program is free software; you can redistribute it and/or modify&n; *      it under the terms of the GNU General Public License as published by&n; *      the Free Software Foundation; either version 2 of the License, or&n; *      (at your option) any later version.&n; *&n; *      This program is distributed in the hope that it will be useful,&n; *      but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *      GNU General Public License for more details.&n; *&n; *      You should have received a copy of the GNU General Public License&n; *      along with this program; if not, write to the Free Software&n; *      Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n; Version : 0.01&n;&n;&n;                            Mods&n; ----------------------------------------------------------------------------&n;  Date     By                Description&n; ----------------------------------------------------------------------------&n;&n; ***************************************************************************/
macro_line|#ifndef lint
macro_line|#ifdef SCCS_LABELS
DECL|variable|_rio_hosthw_h_sccs
r_static
r_char
op_star
id|_rio_hosthw_h_sccs
op_assign
l_string|&quot;@(#)hosthw.h&t;1.2&quot;
suffix:semicolon
macro_line|#endif
macro_line|#endif
DECL|macro|SET_OTHER_INTERRUPT
mdefine_line|#define SET_OTHER_INTERRUPT  ( (volatile u_short *) 0x7c80 )
DECL|macro|SET_EISA_INTERRUPT
mdefine_line|#define SET_EISA_INTERRUPT  ( (volatile u_short *) 0x7ef0 )
DECL|macro|EISA_HOST
mdefine_line|#define EISA_HOST    0x30
DECL|macro|AT_HOST
mdefine_line|#define AT_HOST      0xa0
DECL|macro|MCA_HOST
mdefine_line|#define MCA_HOST     0xb0
DECL|macro|PCI_HOST
mdefine_line|#define PCI_HOST     0xd0
DECL|macro|PRODUCT_MASK
mdefine_line|#define PRODUCT_MASK 0xf0
multiline_comment|/*********** end of file ***********/
eof
