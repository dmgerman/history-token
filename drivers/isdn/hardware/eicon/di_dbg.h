multiline_comment|/*&n; *&n;  Copyright (c) Eicon Networks, 2002.&n; *&n;  This source file is supplied for the use with&n;  Eicon Networks range of DIVA Server Adapters.&n; *&n;  Eicon File Revision :    2.1&n; *&n;  This program is free software; you can redistribute it and/or modify&n;  it under the terms of the GNU General Public License as published by&n;  the Free Software Foundation; either version 2, or (at your option)&n;  any later version.&n; *&n;  This program is distributed in the hope that it will be useful,&n;  but WITHOUT ANY WARRANTY OF ANY KIND WHATSOEVER INCLUDING ANY&n;  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n;  See the GNU General Public License for more details.&n; *&n;  You should have received a copy of the GNU General Public License&n;  along with this program; if not, write to the Free Software&n;  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; */
macro_line|#ifndef __DIVA_DI_DBG_INC__
DECL|macro|__DIVA_DI_DBG_INC__
mdefine_line|#define __DIVA_DI_DBG_INC__
macro_line|#if !defined (dtrc)
DECL|macro|dtrc
mdefine_line|#define dtrc(a)
macro_line|#endif
macro_line|#if !defined (dbug)
DECL|macro|dbug
mdefine_line|#define dbug(a)
macro_line|#endif
macro_line|#if !defined USE_EXTENDED_DEBUGS
r_extern
r_void
(paren
op_star
id|dprintf
)paren
(paren
r_char
op_star
comma
dot
dot
dot
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif
eof
