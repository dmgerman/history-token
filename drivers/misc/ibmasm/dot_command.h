multiline_comment|/*&n; * IBM ASM Service Processor Device Driver&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.&n; *&n; * Copyright (C) IBM Corporation, 2004&n; *&n; * Author: Max Asb&#xfffd;ck &lt;amax@us.ibm.com&gt; &n; *&n; */
macro_line|#ifndef __DOT_COMMAND_H__
DECL|macro|__DOT_COMMAND_H__
mdefine_line|#define __DOT_COMMAND_H__
multiline_comment|/*&n; * dot commands are the protocol used to communicate with the service&n; * processor.&n; * They consist of header, a command of variable length and data of&n; * variable length.&n; */
multiline_comment|/* dot command types */
DECL|macro|sp_write
mdefine_line|#define sp_write&t;&t;0
DECL|macro|sp_write_next
mdefine_line|#define sp_write_next&t;&t;1
DECL|macro|sp_read
mdefine_line|#define sp_read&t;&t;&t;2
DECL|macro|sp_read_next
mdefine_line|#define sp_read_next&t;&t;3
DECL|macro|sp_command_response
mdefine_line|#define sp_command_response&t;4
DECL|macro|sp_event
mdefine_line|#define sp_event&t;&t;5
DECL|macro|sp_heartbeat
mdefine_line|#define sp_heartbeat&t;&t;6
macro_line|#pragma pack(1)
DECL|struct|dot_command_header
r_struct
id|dot_command_header
(brace
DECL|member|type
id|u8
id|type
suffix:semicolon
DECL|member|command_size
id|u8
id|command_size
suffix:semicolon
DECL|member|data_size
id|u16
id|data_size
suffix:semicolon
DECL|member|status
id|u8
id|status
suffix:semicolon
DECL|member|reserved
id|u8
id|reserved
suffix:semicolon
)brace
suffix:semicolon
macro_line|#pragma pack()
DECL|function|get_dot_command_size
r_static
r_inline
r_int
id|get_dot_command_size
c_func
(paren
r_void
op_star
id|buffer
)paren
(brace
r_struct
id|dot_command_header
op_star
id|cmd
op_assign
(paren
r_struct
id|dot_command_header
op_star
)paren
id|buffer
suffix:semicolon
r_return
r_sizeof
(paren
r_struct
id|dot_command_header
)paren
op_plus
id|cmd-&gt;command_size
op_plus
id|cmd-&gt;data_size
suffix:semicolon
)brace
DECL|function|get_dot_command_timeout
r_static
r_inline
r_int
r_int
id|get_dot_command_timeout
c_func
(paren
r_void
op_star
id|buffer
)paren
(brace
r_struct
id|dot_command_header
op_star
id|header
op_assign
(paren
r_struct
id|dot_command_header
op_star
)paren
id|buffer
suffix:semicolon
r_int
r_char
op_star
id|cmd
op_assign
id|buffer
op_plus
r_sizeof
(paren
r_struct
id|dot_command_header
)paren
suffix:semicolon
multiline_comment|/* dot commands 6.3.1, 7.1 and 8.x need a longer timeout */
r_if
c_cond
(paren
id|header-&gt;command_size
op_eq
l_int|3
)paren
(brace
r_if
c_cond
(paren
(paren
id|cmd
(braket
l_int|0
)braket
op_eq
l_int|6
)paren
op_logical_and
(paren
id|cmd
(braket
l_int|1
)braket
op_eq
l_int|3
)paren
op_logical_and
(paren
id|cmd
(braket
l_int|2
)braket
op_eq
l_int|1
)paren
)paren
r_return
id|IBMASM_CMD_TIMEOUT_EXTRA
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|header-&gt;command_size
op_eq
l_int|2
)paren
(brace
r_if
c_cond
(paren
(paren
id|cmd
(braket
l_int|0
)braket
op_eq
l_int|7
)paren
op_logical_and
(paren
id|cmd
(braket
l_int|1
)braket
op_eq
l_int|1
)paren
)paren
r_return
id|IBMASM_CMD_TIMEOUT_EXTRA
suffix:semicolon
r_if
c_cond
(paren
id|cmd
(braket
l_int|0
)braket
op_eq
l_int|8
)paren
r_return
id|IBMASM_CMD_TIMEOUT_EXTRA
suffix:semicolon
)brace
r_return
id|IBMASM_CMD_TIMEOUT_NORMAL
suffix:semicolon
)brace
macro_line|#endif /* __DOT_COMMAND_H__ */
eof
