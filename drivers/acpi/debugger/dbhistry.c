multiline_comment|/******************************************************************************&n; *&n; * Module Name: dbhistry - debugger HISTORY command&n; *              $Revision: 18 $&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000, 2001 R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &quot;acpi.h&quot;
macro_line|#include &quot;acparser.h&quot;
macro_line|#include &quot;acdispat.h&quot;
macro_line|#include &quot;amlcode.h&quot;
macro_line|#include &quot;acnamesp.h&quot;
macro_line|#include &quot;acparser.h&quot;
macro_line|#include &quot;acevents.h&quot;
macro_line|#include &quot;acinterp.h&quot;
macro_line|#include &quot;acdebug.h&quot;
macro_line|#include &quot;actables.h&quot;
macro_line|#ifdef ENABLE_DEBUGGER
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_DEBUGGER
id|MODULE_NAME
(paren
l_string|&quot;dbhistry&quot;
)paren
DECL|macro|HI_NO_HISTORY
mdefine_line|#define HI_NO_HISTORY       0
DECL|macro|HI_RECORD_HISTORY
mdefine_line|#define HI_RECORD_HISTORY   1
DECL|macro|HISTORY_SIZE
mdefine_line|#define HISTORY_SIZE        20
DECL|struct|history_info
r_typedef
r_struct
id|history_info
(brace
DECL|member|command
id|NATIVE_CHAR
id|command
(braket
l_int|80
)braket
suffix:semicolon
DECL|member|cmd_num
id|u32
id|cmd_num
suffix:semicolon
DECL|typedef|HISTORY_INFO
)brace
id|HISTORY_INFO
suffix:semicolon
DECL|variable|history_buffer
id|HISTORY_INFO
id|history_buffer
(braket
id|HISTORY_SIZE
)braket
suffix:semicolon
DECL|variable|lo_history
id|u16
id|lo_history
op_assign
l_int|0
suffix:semicolon
DECL|variable|num_history
id|u16
id|num_history
op_assign
l_int|0
suffix:semicolon
DECL|variable|next_history_index
id|u16
id|next_history_index
op_assign
l_int|0
suffix:semicolon
DECL|variable|next_cmd_num
id|u32
id|next_cmd_num
op_assign
l_int|1
suffix:semicolon
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_db_add_to_history&n; *&n; * PARAMETERS:  Command_line    - Command to add&n; *&n; * RETURN:      None&n; *&n; * DESCRIPTION: Add a command line to the history buffer.&n; *&n; ******************************************************************************/
r_void
DECL|function|acpi_db_add_to_history
id|acpi_db_add_to_history
(paren
id|NATIVE_CHAR
op_star
id|command_line
)paren
(brace
multiline_comment|/* Put command into the next available slot */
id|STRCPY
(paren
id|history_buffer
(braket
id|next_history_index
)braket
dot
id|command
comma
id|command_line
)paren
suffix:semicolon
id|history_buffer
(braket
id|next_history_index
)braket
dot
id|cmd_num
op_assign
id|next_cmd_num
suffix:semicolon
multiline_comment|/* Adjust indexes */
r_if
c_cond
(paren
(paren
id|num_history
op_eq
id|HISTORY_SIZE
)paren
op_logical_and
(paren
id|next_history_index
op_eq
id|lo_history
)paren
)paren
(brace
id|lo_history
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|lo_history
op_ge
id|HISTORY_SIZE
)paren
(brace
id|lo_history
op_assign
l_int|0
suffix:semicolon
)brace
)brace
id|next_history_index
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|next_history_index
op_ge
id|HISTORY_SIZE
)paren
(brace
id|next_history_index
op_assign
l_int|0
suffix:semicolon
)brace
id|next_cmd_num
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|num_history
OL
id|HISTORY_SIZE
)paren
(brace
id|num_history
op_increment
suffix:semicolon
)brace
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_db_display_history&n; *&n; * PARAMETERS:  None&n; *&n; * RETURN:      None&n; *&n; * DESCRIPTION: Display the contents of the history buffer&n; *&n; ******************************************************************************/
r_void
DECL|function|acpi_db_display_history
id|acpi_db_display_history
(paren
r_void
)paren
(brace
id|NATIVE_UINT
id|i
suffix:semicolon
id|u16
id|history_index
suffix:semicolon
id|history_index
op_assign
id|lo_history
suffix:semicolon
multiline_comment|/* Dump entire history buffer */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|num_history
suffix:semicolon
id|i
op_increment
)paren
(brace
id|acpi_os_printf
(paren
l_string|&quot;%ld %s&bslash;n&quot;
comma
id|history_buffer
(braket
id|history_index
)braket
dot
id|cmd_num
comma
id|history_buffer
(braket
id|history_index
)braket
dot
id|command
)paren
suffix:semicolon
id|history_index
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|history_index
op_ge
id|HISTORY_SIZE
)paren
(brace
id|history_index
op_assign
l_int|0
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_db_get_from_history&n; *&n; * PARAMETERS:  Command_num_arg         - String containing the number of the&n; *                                        command to be retrieved&n; *&n; * RETURN:      None&n; *&n; * DESCRIPTION: Get a command from the history buffer&n; *&n; ******************************************************************************/
id|NATIVE_CHAR
op_star
DECL|function|acpi_db_get_from_history
id|acpi_db_get_from_history
(paren
id|NATIVE_CHAR
op_star
id|command_num_arg
)paren
(brace
id|NATIVE_UINT
id|i
suffix:semicolon
id|u16
id|history_index
suffix:semicolon
id|u32
id|cmd_num
suffix:semicolon
r_if
c_cond
(paren
id|command_num_arg
op_eq
l_int|NULL
)paren
(brace
id|cmd_num
op_assign
id|next_cmd_num
op_minus
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|cmd_num
op_assign
id|STRTOUL
(paren
id|command_num_arg
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/* Search history buffer */
id|history_index
op_assign
id|lo_history
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|num_history
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|history_buffer
(braket
id|history_index
)braket
dot
id|cmd_num
op_eq
id|cmd_num
)paren
(brace
multiline_comment|/* Found the commnad, return it */
r_return
(paren
id|history_buffer
(braket
id|history_index
)braket
dot
id|command
)paren
suffix:semicolon
)brace
id|history_index
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|history_index
op_ge
id|HISTORY_SIZE
)paren
(brace
id|history_index
op_assign
l_int|0
suffix:semicolon
)brace
)brace
id|acpi_os_printf
(paren
l_string|&quot;Invalid history number: %d&bslash;n&quot;
comma
id|history_index
)paren
suffix:semicolon
r_return
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
macro_line|#endif /* ENABLE_DEBUGGER */
eof
