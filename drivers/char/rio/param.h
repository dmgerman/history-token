multiline_comment|/*&n;** -----------------------------------------------------------------------------&n;**&n;**  Perle Specialix driver for Linux&n;**  Ported from existing RIO Driver for SCO sources.&n; *&n; *  (C) 1990 - 2000 Specialix International Ltd., Byfleet, Surrey, UK.&n; *&n; *      This program is free software; you can redistribute it and/or modify&n; *      it under the terms of the GNU General Public License as published by&n; *      the Free Software Foundation; either version 2 of the License, or&n; *      (at your option) any later version.&n; *&n; *      This program is distributed in the hope that it will be useful,&n; *      but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *      GNU General Public License for more details.&n; *&n; *      You should have received a copy of the GNU General Public License&n; *      along with this program; if not, write to the Free Software&n; *      Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;**&n;**&t;Module&t;&t;: param.h&n;**&t;SID&t;&t;: 1.2&n;**&t;Last Modified&t;: 11/6/98 11:34:12&n;**&t;Retrieved&t;: 11/6/98 11:34:21&n;**&n;**  ident @(#)param.h&t;1.2&n;**&n;** -----------------------------------------------------------------------------&n;*/
macro_line|#ifndef __rio_param_h__
DECL|macro|__rio_param_h__
mdefine_line|#define __rio_param_h__
macro_line|#ifdef SCCS_LABELS
DECL|variable|_param_h_sccs_
r_static
r_char
op_star
id|_param_h_sccs_
op_assign
l_string|&quot;@(#)param.h&t;1.2&quot;
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;** the param command block, as used in OPEN and PARAM calls.&n;*/
DECL|struct|phb_param
r_struct
id|phb_param
(brace
DECL|member|Cmd
id|BYTE
id|Cmd
suffix:semicolon
multiline_comment|/* It is very important that these line up */
DECL|member|Cor1
id|BYTE
id|Cor1
suffix:semicolon
multiline_comment|/* with what is expected at the other end. */
DECL|member|Cor2
id|BYTE
id|Cor2
suffix:semicolon
multiline_comment|/* to confirm that you&squot;ve got it right,    */
DECL|member|Cor4
id|BYTE
id|Cor4
suffix:semicolon
multiline_comment|/* check with cirrus/cirrus.h              */
DECL|member|Cor5
id|BYTE
id|Cor5
suffix:semicolon
DECL|member|TxXon
id|BYTE
id|TxXon
suffix:semicolon
multiline_comment|/* Transmit X-On character */
DECL|member|TxXoff
id|BYTE
id|TxXoff
suffix:semicolon
multiline_comment|/* Transmit X-Off character */
DECL|member|RxXon
id|BYTE
id|RxXon
suffix:semicolon
multiline_comment|/* Receive X-On character */
DECL|member|RxXoff
id|BYTE
id|RxXoff
suffix:semicolon
multiline_comment|/* Receive X-Off character */
DECL|member|LNext
id|BYTE
id|LNext
suffix:semicolon
multiline_comment|/* Literal-next character */
DECL|member|TxBaud
id|BYTE
id|TxBaud
suffix:semicolon
multiline_comment|/* Transmit baudrate */
DECL|member|RxBaud
id|BYTE
id|RxBaud
suffix:semicolon
multiline_comment|/* Receive baudrate */
)brace
suffix:semicolon
macro_line|#endif
eof
