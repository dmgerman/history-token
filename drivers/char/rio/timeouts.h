multiline_comment|/****************************************************************************&n; *******                                                              *******&n; *******                     T I M E O U T S&n; *******                                                              *******&n; ****************************************************************************&n;&n; Author  : Ian Nandhra&n; Date    :&n;&n; *&n; *  (C) 1990 - 2000 Specialix International Ltd., Byfleet, Surrey, UK.&n; *&n; *      This program is free software; you can redistribute it and/or modify&n; *      it under the terms of the GNU General Public License as published by&n; *      the Free Software Foundation; either version 2 of the License, or&n; *      (at your option) any later version.&n; *&n; *      This program is distributed in the hope that it will be useful,&n; *      but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *      GNU General Public License for more details.&n; *&n; *      You should have received a copy of the GNU General Public License&n; *      along with this program; if not, write to the Free Software&n; *      Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n; Version : 0.01&n;&n;&n;                            Mods&n; ----------------------------------------------------------------------------&n;  Date     By                Description&n; ----------------------------------------------------------------------------&n;&n; ***************************************************************************/
macro_line|#ifndef lint
macro_line|#ifdef SCCS_LABELS
DECL|variable|_rio_defaults_h_sccs
r_static
r_char
op_star
id|_rio_defaults_h_sccs
op_assign
l_string|&quot;@(#)timeouts.h&t;1.3&quot;
suffix:semicolon
macro_line|#endif
macro_line|#endif
DECL|macro|MILLISECOND
mdefine_line|#define MILLISECOND           (int) (1000/64)   /* 15.625 low ticks */
DECL|macro|SECOND
mdefine_line|#define SECOND                (int) 15625       /* Low priority ticks */
DECL|macro|TX_TIMEOUT
mdefine_line|#define TX_TIMEOUT          (int) (200 * MILLISECOND)
multiline_comment|/*********** end of file ***********/
eof
