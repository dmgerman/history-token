multiline_comment|/****************************************************************************&n; *******                                                              *******&n; *******                      RUPSTAT&n; *******                                                              *******&n; ****************************************************************************&n;&n; Author  : Jeremy Rolls&n; Date    :&n;&n; *&n; *  (C) 1990 - 2000 Specialix International Ltd., Byfleet, Surrey, UK.&n; *&n; *      This program is free software; you can redistribute it and/or modify&n; *      it under the terms of the GNU General Public License as published by&n; *      the Free Software Foundation; either version 2 of the License, or&n; *      (at your option) any later version.&n; *&n; *      This program is distributed in the hope that it will be useful,&n; *      but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *      GNU General Public License for more details.&n; *&n; *      You should have received a copy of the GNU General Public License&n; *      along with this program; if not, write to the Free Software&n; *      Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n; Version : 0.01&n;&n;&n;                            Mods&n; ----------------------------------------------------------------------------&n;  Date     By                Description&n; ----------------------------------------------------------------------------&n;&n; ***************************************************************************/
macro_line|#ifndef _rupstat_h
DECL|macro|_rupstat_h
mdefine_line|#define _rupstat_h
macro_line|#ifndef lint
macro_line|#ifdef SCCS_LABELS
DECL|variable|_rio_rupstat_h_sccs
r_static
r_char
op_star
id|_rio_rupstat_h_sccs
op_assign
l_string|&quot;@(#)rupstat.h&t;1.1&quot;
suffix:semicolon
macro_line|#endif
macro_line|#endif
DECL|macro|STATUS_SYNC
mdefine_line|#define    STATUS_SYNC    0
DECL|macro|STATUS_REQ_TOP
mdefine_line|#define    STATUS_REQ_TOP 1
DECL|macro|STATUS_TOPOLOGY
mdefine_line|#define    STATUS_TOPOLOGY    2
macro_line|#endif
eof
