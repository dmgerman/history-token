multiline_comment|/*  ----------------------------------------------------------------------&n;&n;    Copyright (C) 2000  Cesar Miquel  (miquel@df.uba.ar)&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n;    ---------------------------------------------------------------------- */
DECL|macro|RIO_SEND_COMMAND
mdefine_line|#define RIO_SEND_COMMAND&t;&t;&t;0x1
DECL|macro|RIO_RECV_COMMAND
mdefine_line|#define RIO_RECV_COMMAND&t;&t;&t;0x2
DECL|macro|RIO_DIR_OUT
mdefine_line|#define RIO_DIR_OUT               &t;        0x0
DECL|macro|RIO_DIR_IN
mdefine_line|#define RIO_DIR_IN&t;&t;&t;&t;0x1
DECL|struct|RioCommand
r_struct
id|RioCommand
(brace
DECL|member|length
r_int
id|length
suffix:semicolon
DECL|member|request
r_int
id|request
suffix:semicolon
DECL|member|requesttype
r_int
id|requesttype
suffix:semicolon
DECL|member|value
r_int
id|value
suffix:semicolon
DECL|member|index
r_int
id|index
suffix:semicolon
DECL|member|buffer
r_void
op_star
id|buffer
suffix:semicolon
DECL|member|timeout
r_int
id|timeout
suffix:semicolon
)brace
suffix:semicolon
eof
