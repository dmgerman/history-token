multiline_comment|/****************************************************************************&n; *******                                                              *******&n; *******                    S A M . H&n; *******                                                              *******&n; ****************************************************************************&n;&n; Author  : Ian Nandhra&n; Date    :&n;&n; *&n; *  (C) 1990 - 2000 Specialix International Ltd., Byfleet, Surrey, UK.&n; *&n; *      This program is free software; you can redistribute it and/or modify&n; *      it under the terms of the GNU General Public License as published by&n; *      the Free Software Foundation; either version 2 of the License, or&n; *      (at your option) any later version.&n; *&n; *      This program is distributed in the hope that it will be useful,&n; *      but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *      GNU General Public License for more details.&n; *&n; *      You should have received a copy of the GNU General Public License&n; *      along with this program; if not, write to the Free Software&n; *      Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n; Version : 0.01&n;&n;&n;                            Mods&n; ----------------------------------------------------------------------------&n;  Date     By                Description&n; ----------------------------------------------------------------------------&n;&n; ***************************************************************************/
macro_line|#ifndef _sam_h
DECL|macro|_sam_h
mdefine_line|#define _sam_h 1
macro_line|#ifdef SCCS_LABELS
macro_line|#ifndef lint
multiline_comment|/* static char *_rio_sam_h_sccs = &quot;@(#)sam.h&t;1.3&quot;; */
macro_line|#endif
macro_line|#endif
macro_line|#if !defined( HOST ) &amp;&amp; !defined( INKERNEL )
DECL|macro|RTA
mdefine_line|#define RTA 1
macro_line|#endif
DECL|macro|NUM_FREE_LIST_UNITS
mdefine_line|#define NUM_FREE_LIST_UNITS     500
macro_line|#ifndef FALSE
DECL|macro|FALSE
mdefine_line|#define FALSE (short)  0x00
macro_line|#endif
macro_line|#ifndef TRUE
DECL|macro|TRUE
mdefine_line|#define TRUE  (short)  !FALSE
macro_line|#endif
DECL|macro|TX
mdefine_line|#define TX    TRUE
DECL|macro|RX
mdefine_line|#define RX    FALSE
DECL|typedef|FREE_LIST
r_typedef
r_struct
id|FREE_LIST
id|FREE_LIST
suffix:semicolon
DECL|struct|FREE_LIST
r_struct
id|FREE_LIST
(brace
DECL|member|next
id|FREE_LIST_ptr
id|next
suffix:semicolon
DECL|member|prev
id|FREE_LIST_ptr
id|prev
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
multiline_comment|/*********** end of file ***********/
eof
