multiline_comment|/*&n;** -----------------------------------------------------------------------------&n;**&n;**  Perle Specialix driver for Linux&n;**  Ported from existing RIO Driver for SCO sources.&n; *&n; *  (C) 1990 - 2000 Specialix International Ltd., Byfleet, Surrey, UK.&n; *&n; *      This program is free software; you can redistribute it and/or modify&n; *      it under the terms of the GNU General Public License as published by&n; *      the Free Software Foundation; either version 2 of the License, or&n; *      (at your option) any later version.&n; *&n; *      This program is distributed in the hope that it will be useful,&n; *      but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *      GNU General Public License for more details.&n; *&n; *      You should have received a copy of the GNU General Public License&n; *      along with this program; if not, write to the Free Software&n; *      Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;**&n;**&t;Module&t;&t;: unixrup.h&n;**&t;SID&t;&t;: 1.2&n;**&t;Last Modified&t;: 11/6/98 11:34:20&n;**&t;Retrieved&t;: 11/6/98 11:34:22&n;**&n;**  ident @(#)unixrup.h&t;1.2&n;**&n;** -----------------------------------------------------------------------------&n;*/
macro_line|#ifndef __rio_unixrup_h__
DECL|macro|__rio_unixrup_h__
mdefine_line|#define __rio_unixrup_h__
macro_line|#ifdef SCCS_LABELS
DECL|variable|_unixrup_h_sccs_
r_static
r_char
op_star
id|_unixrup_h_sccs_
op_assign
l_string|&quot;@(#)unixrup.h&t;1.2&quot;
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;**    UnixRup data structure. This contains pointers to actual RUPs on the&n;**    host card, and all the command/boot control stuff.&n;*/
DECL|struct|UnixRup
r_struct
id|UnixRup
(brace
DECL|member|CmdsWaitingP
r_struct
id|CmdBlk
op_star
id|CmdsWaitingP
suffix:semicolon
multiline_comment|/* Commands waiting to be done */
DECL|member|CmdPendingP
r_struct
id|CmdBlk
op_star
id|CmdPendingP
suffix:semicolon
multiline_comment|/* The command currently being sent */
DECL|member|RupP
r_struct
id|RUP
op_star
id|RupP
suffix:semicolon
multiline_comment|/* the Rup to send it to */
DECL|member|Id
id|uint
id|Id
suffix:semicolon
multiline_comment|/* Id number */
DECL|member|BaseSysPort
id|uint
id|BaseSysPort
suffix:semicolon
multiline_comment|/* SysPort of first tty on this RTA */
DECL|member|ModTypes
id|uint
id|ModTypes
suffix:semicolon
multiline_comment|/* Modules on this RTA */
DECL|member|RupLock
id|spinlock_t
id|RupLock
suffix:semicolon
multiline_comment|/* Lock structure for MPX */
multiline_comment|/*    struct lockb     RupLock;&t;*/
multiline_comment|/* Lock structure for MPX */
)brace
suffix:semicolon
macro_line|#endif /* __rio_unixrup_h__ */
eof
