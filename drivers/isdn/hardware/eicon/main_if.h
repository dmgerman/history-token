multiline_comment|/*&n; *&n;  Copyright (c) Eicon Technology Corporation, 2000.&n; *&n;  This source file is supplied for the use with Eicon&n;  Technology Corporation&squot;s range of DIVA Server Adapters.&n; *&n;  This program is free software; you can redistribute it and/or modify&n;  it under the terms of the GNU General Public License as published by&n;  the Free Software Foundation; either version 2, or (at your option)&n;  any later version.&n; *&n;  This program is distributed in the hope that it will be useful,&n;  but WITHOUT ANY WARRANTY OF ANY KIND WHATSOEVER INCLUDING ANY&n;  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n;  See the GNU General Public License for more details.&n; *&n;  You should have received a copy of the GNU General Public License&n;  along with this program; if not, write to the Free Software&n;  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; */
multiline_comment|/*------------------------------------------------------------------*/
multiline_comment|/* file: main_if.h                                                  */
multiline_comment|/*------------------------------------------------------------------*/
macro_line|# ifndef MAIN_IF___H
DECL|macro|MAIN_IF___H
macro_line|# define MAIN_IF___H
macro_line|# include &quot;debug_if.h&quot;
r_void
id|DI_lock
(paren
r_void
)paren
suffix:semicolon
r_void
id|DI_unlock
(paren
r_void
)paren
suffix:semicolon
macro_line|#ifdef NOT_YET_NEEDED
r_void
id|DI_nttime
(paren
id|LARGE_INTEGER
op_star
id|NTtime
)paren
suffix:semicolon
r_void
id|DI_ntlcltime
c_func
(paren
id|LARGE_INTEGER
op_star
id|NTtime
comma
id|LARGE_INTEGER
op_star
id|lclNTtime
)paren
suffix:semicolon
r_void
id|DI_nttimefields
c_func
(paren
id|LARGE_INTEGER
op_star
id|NTtime
comma
id|TIME_FIELDS
op_star
id|TimeFields
)paren
suffix:semicolon
r_int
r_int
id|DI_wintime
c_func
(paren
id|LARGE_INTEGER
op_star
id|NTtime
)paren
suffix:semicolon
r_int
r_int
id|DiInsertProcessorNumber
(paren
r_int
id|type
)paren
suffix:semicolon
r_void
id|DiProcessEventLog
(paren
r_int
r_int
id|id
comma
r_int
r_int
id|msgID
comma
id|va_list
id|ap
)paren
suffix:semicolon
r_void
id|StartIoctlTimer
(paren
r_void
(paren
op_star
id|Handler
)paren
(paren
r_void
)paren
comma
r_int
r_int
id|msec
)paren
suffix:semicolon
r_void
id|StopIoctlTimer
(paren
r_void
)paren
suffix:semicolon
r_void
id|UnpendIoctl
(paren
id|DbgRequest
op_star
id|pDbgReq
)paren
suffix:semicolon
macro_line|#endif
r_void
id|add_to_q
c_func
(paren
r_int
comma
r_char
op_star
comma
r_int
r_int
)paren
suffix:semicolon
macro_line|# endif /* MAIN_IF___H */
eof
