multiline_comment|/*&n; * hvconsole.h&n; * Copyright (C) 2004 Ryan S Arnold, IBM Corporation&n; *&n; * LPAR console support.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
macro_line|#ifndef _PPC64_HVCONSOLE_H
DECL|macro|_PPC64_HVCONSOLE_H
mdefine_line|#define _PPC64_HVCONSOLE_H
multiline_comment|/*&n; * This is the max number of console adapters that can/will be found as&n; * console devices on first stage console init.  Any number beyond this range&n; * can&squot;t be used as a console device but is still a valid tty device.&n; */
DECL|macro|MAX_NR_HVC_CONSOLES
mdefine_line|#define MAX_NR_HVC_CONSOLES&t;16
r_extern
r_int
id|hvc_get_chars
c_func
(paren
r_uint32
id|vtermno
comma
r_char
op_star
id|buf
comma
r_int
id|count
)paren
suffix:semicolon
r_extern
r_int
id|hvc_put_chars
c_func
(paren
r_uint32
id|vtermno
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|count
)paren
suffix:semicolon
multiline_comment|/* Early discovery of console adapters. */
r_extern
r_int
id|hvc_find_vtys
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Implemented by a console driver */
r_extern
r_int
id|hvc_instantiate
c_func
(paren
r_uint32
id|vtermno
comma
r_int
id|index
)paren
suffix:semicolon
macro_line|#endif /* _PPC64_HVCONSOLE_H */
eof
