multiline_comment|/*&n;** -----------------------------------------------------------------------------&n;**&n;**  Perle Specialix driver for Linux&n;**  Ported from existing RIO Driver for SCO sources.&n; *&n; *  (C) 1990 - 2000 Specialix International Ltd., Byfleet, Surrey, UK.&n; *&n; *      This program is free software; you can redistribute it and/or modify&n; *      it under the terms of the GNU General Public License as published by&n; *      the Free Software Foundation; either version 2 of the License, or&n; *      (at your option) any later version.&n; *&n; *      This program is distributed in the hope that it will be useful,&n; *      but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *      GNU General Public License for more details.&n; *&n; *      You should have received a copy of the GNU General Public License&n; *      along with this program; if not, write to the Free Software&n; *      Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;**&n;**&t;Module&t;&t;: top.h&n;**&t;SID&t;&t;: 1.2&n;**&t;Last Modified&t;: 11/6/98 11:34:19&n;**&t;Retrieved&t;: 11/6/98 11:34:22&n;**&n;**  ident @(#)top.h&t;1.2&n;**&n;** -----------------------------------------------------------------------------&n;*/
macro_line|#ifndef __rio_top_h__
DECL|macro|__rio_top_h__
mdefine_line|#define __rio_top_h__
macro_line|#ifdef SCCS_LABELS
DECL|variable|_top_h_sccs_
r_static
r_char
op_star
id|_top_h_sccs_
op_assign
l_string|&quot;@(#)top.h&t;1.2&quot;
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;** Topology information&n;*/
DECL|struct|Top
r_struct
id|Top
(brace
DECL|member|Unit
id|uchar
id|Unit
suffix:semicolon
DECL|member|Link
id|uchar
id|Link
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* __rio_top_h__ */
eof
