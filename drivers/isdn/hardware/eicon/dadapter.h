multiline_comment|/*&n; *&n;  Copyright (c) Eicon Networks, 2002.&n; *&n;  This source file is supplied for the use with&n;  Eicon Networks range of DIVA Server Adapters.&n; *&n;  Eicon File Revision :    2.1&n; *&n;  This program is free software; you can redistribute it and/or modify&n;  it under the terms of the GNU General Public License as published by&n;  the Free Software Foundation; either version 2, or (at your option)&n;  any later version.&n; *&n;  This program is distributed in the hope that it will be useful,&n;  but WITHOUT ANY WARRANTY OF ANY KIND WHATSOEVER INCLUDING ANY&n;  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n;  See the GNU General Public License for more details.&n; *&n;  You should have received a copy of the GNU General Public License&n;  along with this program; if not, write to the Free Software&n;  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; */
macro_line|#ifndef __DIVA_DIDD_DADAPTER_INC__
DECL|macro|__DIVA_DIDD_DADAPTER_INC__
mdefine_line|#define __DIVA_DIDD_DADAPTER_INC__
r_void
id|diva_didd_load_time_init
(paren
r_void
)paren
suffix:semicolon
r_void
id|diva_didd_load_time_finit
(paren
r_void
)paren
suffix:semicolon
r_int
id|diva_didd_add_descriptor
(paren
id|DESCRIPTOR
op_star
id|d
)paren
suffix:semicolon
r_int
id|diva_didd_remove_descriptor
(paren
id|IDI_CALL
id|request
)paren
suffix:semicolon
r_int
id|diva_didd_read_adapter_array
(paren
id|DESCRIPTOR
op_star
id|buffer
comma
r_int
id|length
)paren
suffix:semicolon
DECL|macro|OLD_MAX_DESCRIPTORS
mdefine_line|#define OLD_MAX_DESCRIPTORS     16
DECL|macro|NEW_MAX_DESCRIPTORS
mdefine_line|#define NEW_MAX_DESCRIPTORS     64
macro_line|#endif
eof
