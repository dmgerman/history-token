multiline_comment|/****************************************************************************&n; *******                                                              *******&n; *******                     D E F A U L T S&n; *******                                                              *******&n; ****************************************************************************&n;&n; Author  : Ian Nandhra&n; Date    :&n;&n; *&n; *  (C) 1990 - 2000 Specialix International Ltd., Byfleet, Surrey, UK.&n; *&n; *      This program is free software; you can redistribute it and/or modify&n; *      it under the terms of the GNU General Public License as published by&n; *      the Free Software Foundation; either version 2 of the License, or&n; *      (at your option) any later version.&n; *&n; *      This program is distributed in the hope that it will be useful,&n; *      but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *      GNU General Public License for more details.&n; *&n; *      You should have received a copy of the GNU General Public License&n; *      along with this program; if not, write to the Free Software&n; *      Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n; Version : 0.01&n;&n;&n;                            Mods&n; ----------------------------------------------------------------------------&n;  Date     By                Description&n; ----------------------------------------------------------------------------&n;&n; ***************************************************************************/
macro_line|#ifndef lint
macro_line|#ifdef SCCS
DECL|variable|_rio_defaults_h_sccs
r_static
r_char
op_star
id|_rio_defaults_h_sccs
op_assign
l_string|&quot;@(#)defaults.h&t;1.1&quot;
suffix:semicolon
macro_line|#endif
macro_line|#endif
DECL|macro|MILLISECOND
mdefine_line|#define MILLISECOND           (int) (1000/64)   /* 15.625 low ticks */
DECL|macro|SECOND
mdefine_line|#define SECOND                (int) 15625       /* Low priority ticks */
macro_line|#ifdef RTA
DECL|macro|RX_LIMIT
mdefine_line|#define RX_LIMIT       (ushort) 3
macro_line|#endif
macro_line|#ifdef HOST
DECL|macro|RX_LIMIT
mdefine_line|#define RX_LIMIT       (ushort) 1
macro_line|#endif
DECL|macro|LINK_TIMEOUT
mdefine_line|#define LINK_TIMEOUT          (int) (POLL_PERIOD / 2)
multiline_comment|/*********** end of file ***********/
eof
