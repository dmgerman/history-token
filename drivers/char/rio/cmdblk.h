multiline_comment|/*&n;** -----------------------------------------------------------------------------&n;**&n;**  Perle Specialix driver for Linux&n;**  Ported from existing RIO Driver for SCO sources.&n; *&n; *  (C) 1990 - 2000 Specialix International Ltd., Byfleet, Surrey, UK.&n; *&n; *      This program is free software; you can redistribute it and/or modify&n; *      it under the terms of the GNU General Public License as published by&n; *      the Free Software Foundation; either version 2 of the License, or&n; *      (at your option) any later version.&n; *&n; *      This program is distributed in the hope that it will be useful,&n; *      but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *      GNU General Public License for more details.&n; *&n; *      You should have received a copy of the GNU General Public License&n; *      along with this program; if not, write to the Free Software&n; *      Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;**&n;**&t;Module&t;&t;: cmdblk.h&n;**&t;SID&t;&t;: 1.2&n;**&t;Last Modified&t;: 11/6/98 11:34:09&n;**&t;Retrieved&t;: 11/6/98 11:34:20&n;**&n;**  ident @(#)cmdblk.h&t;1.2&n;**&n;** -----------------------------------------------------------------------------&n;*/
macro_line|#ifndef __rio_cmdblk_h__
DECL|macro|__rio_cmdblk_h__
mdefine_line|#define __rio_cmdblk_h__
macro_line|#ifdef SCCS_LABELS
macro_line|#ifndef lint
DECL|variable|_cmdblk_h_sccs_
r_static
r_char
op_star
id|_cmdblk_h_sccs_
op_assign
l_string|&quot;@(#)cmdblk.h&t;1.2&quot;
suffix:semicolon
macro_line|#endif
macro_line|#endif
multiline_comment|/*&n;** the structure of a command block, used to queue commands destined for&n;** a rup.&n;*/
DECL|struct|CmdBlk
r_struct
id|CmdBlk
(brace
DECL|member|NextP
r_struct
id|CmdBlk
op_star
id|NextP
suffix:semicolon
multiline_comment|/* Pointer to next command block */
DECL|member|Packet
r_struct
id|PKT
id|Packet
suffix:semicolon
multiline_comment|/* A packet, to copy to the rup */
multiline_comment|/* The func to call to check if OK */
DECL|member|PreFuncP
r_int
(paren
op_star
id|PreFuncP
)paren
(paren
r_int
comma
r_struct
id|CmdBlk
op_star
)paren
suffix:semicolon
DECL|member|PreArg
r_int
id|PreArg
suffix:semicolon
multiline_comment|/* The arg for the func */
multiline_comment|/* The func to call when completed */
DECL|member|PostFuncP
r_int
(paren
op_star
id|PostFuncP
)paren
(paren
r_int
comma
r_struct
id|CmdBlk
op_star
)paren
suffix:semicolon
DECL|member|PostArg
r_int
id|PostArg
suffix:semicolon
multiline_comment|/* The arg for the func */
)brace
suffix:semicolon
DECL|macro|NUM_RIO_CMD_BLKS
mdefine_line|#define NUM_RIO_CMD_BLKS (3 * (MAX_RUP * 4 + LINKS_PER_UNIT * 4))
macro_line|#endif
eof
