multiline_comment|/*&n;** -----------------------------------------------------------------------------&n;**&n;**  Perle Specialix driver for Linux&n;**  Ported from existing RIO Driver for SCO sources.&n; *&n; *  (C) 1990 - 2000 Specialix International Ltd., Byfleet, Surrey, UK.&n; *&n; *      This program is free software; you can redistribute it and/or modify&n; *      it under the terms of the GNU General Public License as published by&n; *      the Free Software Foundation; either version 2 of the License, or&n; *      (at your option) any later version.&n; *&n; *      This program is distributed in the hope that it will be useful,&n; *      but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *      GNU General Public License for more details.&n; *&n; *      You should have received a copy of the GNU General Public License&n; *      along with this program; if not, write to the Free Software&n; *      Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;**&n;**&t;Module&t;&t;: riscos.h&n;**&t;SID&t;&t;: 1.2&n;**&t;Last Modified&t;: 11/6/98 11:34:19&n;**&t;Retrieved&t;: 11/6/98 11:34:22&n;**&n;**  ident @(#)riscos.h&t;1.2&n;**&n;** -----------------------------------------------------------------------------&n;*/
macro_line|#ifndef __rio_riscos_h__
DECL|macro|__rio_riscos_h__
mdefine_line|#define __rio_riscos_h__
macro_line|#ifdef SCCS_LABELS
DECL|variable|_riscos_h_sccs_
r_static
r_char
op_star
id|_riscos_h_sccs_
op_assign
l_string|&quot;@(#)riscos.h&t;1.2&quot;
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;** This module used to define all those little itsy bits required for RISC/OS&n;** now it&squot;s full of null macros.&n;*/
multiline_comment|/*&n;**&t;RBYTE reads a byte from a location.&n;**&t;RWORD reads a word from a location.&n;**&t;WBYTE writes a byte to a location.&n;**&t;WWORD writes a word to a location.&n;**&t;RINDW reads a word through a pointer.&n;**&t;WINDW writes a word through a pointer.&n;**&t;RIOSWAB swaps the two bytes of a word, if needed.&n;*/
DECL|macro|RIOSWAB
mdefine_line|#define&t;RIOSWAB(N)      (N)
DECL|macro|WBYTE
mdefine_line|#define&t;WBYTE(A,V)&t;(A)=(uchar)(V)
DECL|macro|WWORD
mdefine_line|#define WWORD(A,V)&t;(A)=(ushort)(V)
DECL|macro|RBYTE
mdefine_line|#define RBYTE(A)&t;(uchar)(A)
DECL|macro|RWORD
mdefine_line|#define RWORD(A)&t;(ushort)(A)
DECL|macro|RINDW
mdefine_line|#define RINDW(A)&t;(*(ushort *)(A))
DECL|macro|WINDW
mdefine_line|#define WINDW(A,V)&t;(*(ushort *)(A)=(ushort)(V))
macro_line|#endif /* __rio_riscos_h__ */
eof
