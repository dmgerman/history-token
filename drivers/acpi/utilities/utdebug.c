multiline_comment|/******************************************************************************&n; *&n; * Module Name: utdebug - Debug print routines&n; *              $Revision: 104 $&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000 - 2002, R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &quot;acpi.h&quot;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_UTILITIES
id|ACPI_MODULE_NAME
(paren
l_string|&quot;utdebug&quot;
)paren
macro_line|#ifdef ACPI_DEBUG_OUTPUT
DECL|variable|acpi_gbl_prev_thread_id
r_static
id|u32
id|acpi_gbl_prev_thread_id
op_assign
l_int|0xFFFFFFFF
suffix:semicolon
DECL|variable|acpi_gbl_fn_entry_str
r_static
r_char
op_star
id|acpi_gbl_fn_entry_str
op_assign
l_string|&quot;----Entry&quot;
suffix:semicolon
DECL|variable|acpi_gbl_fn_exit_str
r_static
r_char
op_star
id|acpi_gbl_fn_exit_str
op_assign
l_string|&quot;----Exit-&quot;
suffix:semicolon
multiline_comment|/*****************************************************************************&n; *&n; * FUNCTION:    Acpi_ut_init_stack_ptr_trace&n; *&n; * PARAMETERS:  None&n; *&n; * RETURN:      None&n; *&n; * DESCRIPTION: Save the current stack pointer&n; *&n; ****************************************************************************/
r_void
DECL|function|acpi_ut_init_stack_ptr_trace
id|acpi_ut_init_stack_ptr_trace
(paren
r_void
)paren
(brace
id|u32
id|current_sp
suffix:semicolon
id|acpi_gbl_entry_stack_pointer
op_assign
id|ACPI_PTR_DIFF
(paren
op_amp
id|current_sp
comma
l_int|NULL
)paren
suffix:semicolon
)brace
multiline_comment|/*****************************************************************************&n; *&n; * FUNCTION:    Acpi_ut_track_stack_ptr&n; *&n; * PARAMETERS:  None&n; *&n; * RETURN:      None&n; *&n; * DESCRIPTION: Save the current stack pointer&n; *&n; ****************************************************************************/
r_void
DECL|function|acpi_ut_track_stack_ptr
id|acpi_ut_track_stack_ptr
(paren
r_void
)paren
(brace
id|ACPI_SIZE
id|current_sp
suffix:semicolon
id|current_sp
op_assign
id|ACPI_PTR_DIFF
(paren
op_amp
id|current_sp
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|current_sp
OL
id|acpi_gbl_lowest_stack_pointer
)paren
(brace
id|acpi_gbl_lowest_stack_pointer
op_assign
id|current_sp
suffix:semicolon
)brace
r_if
c_cond
(paren
id|acpi_gbl_nesting_level
OG
id|acpi_gbl_deepest_nesting
)paren
(brace
id|acpi_gbl_deepest_nesting
op_assign
id|acpi_gbl_nesting_level
suffix:semicolon
)brace
)brace
multiline_comment|/*****************************************************************************&n; *&n; * FUNCTION:    Acpi_ut_debug_print&n; *&n; * PARAMETERS:  Debug_level         - Requested debug print level&n; *              Proc_name           - Caller&squot;s procedure name&n; *              Module_name         - Caller&squot;s module name (for error output)&n; *              Line_number         - Caller&squot;s line number (for error output)&n; *              Component_id        - Caller&squot;s component ID (for error output)&n; *&n; *              Format              - Printf format field&n; *              ...                 - Optional printf arguments&n; *&n; * RETURN:      None&n; *&n; * DESCRIPTION: Print error message with prefix consisting of the module name,&n; *              line number, and component ID.&n; *&n; ****************************************************************************/
r_void
id|ACPI_INTERNAL_VAR_XFACE
DECL|function|acpi_ut_debug_print
id|acpi_ut_debug_print
(paren
id|u32
id|requested_debug_level
comma
id|u32
id|line_number
comma
id|acpi_debug_print_info
op_star
id|dbg_info
comma
r_char
op_star
id|format
comma
dot
dot
dot
)paren
(brace
id|u32
id|thread_id
suffix:semicolon
id|va_list
id|args
suffix:semicolon
multiline_comment|/*&n;&t; * Stay silent if the debug level or component ID is disabled&n;&t; */
r_if
c_cond
(paren
op_logical_neg
(paren
id|requested_debug_level
op_amp
id|acpi_dbg_level
)paren
op_logical_or
op_logical_neg
(paren
id|dbg_info-&gt;component_id
op_amp
id|acpi_dbg_layer
)paren
)paren
(brace
r_return
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Thread tracking and context switch notification&n;&t; */
id|thread_id
op_assign
id|acpi_os_get_thread_id
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|thread_id
op_ne
id|acpi_gbl_prev_thread_id
)paren
(brace
r_if
c_cond
(paren
id|ACPI_LV_THREADS
op_amp
id|acpi_dbg_level
)paren
(brace
id|acpi_os_printf
(paren
l_string|&quot;&bslash;n**** Context Switch from TID %X to TID %X ****&bslash;n&bslash;n&quot;
comma
id|acpi_gbl_prev_thread_id
comma
id|thread_id
)paren
suffix:semicolon
)brace
id|acpi_gbl_prev_thread_id
op_assign
id|thread_id
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Display the module name, current line number, thread ID (if requested),&n;&t; * current procedure nesting level, and the current procedure name&n;&t; */
id|acpi_os_printf
(paren
l_string|&quot;%8s-%04ld &quot;
comma
id|dbg_info-&gt;module_name
comma
id|line_number
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_LV_THREADS
op_amp
id|acpi_dbg_level
)paren
(brace
id|acpi_os_printf
(paren
l_string|&quot;[%04lX] &quot;
comma
id|thread_id
comma
id|acpi_gbl_nesting_level
comma
id|dbg_info-&gt;proc_name
)paren
suffix:semicolon
)brace
id|acpi_os_printf
(paren
l_string|&quot;[%02ld] %-22.22s: &quot;
comma
id|acpi_gbl_nesting_level
comma
id|dbg_info-&gt;proc_name
)paren
suffix:semicolon
id|va_start
(paren
id|args
comma
id|format
)paren
suffix:semicolon
id|acpi_os_vprintf
(paren
id|format
comma
id|args
)paren
suffix:semicolon
)brace
multiline_comment|/*****************************************************************************&n; *&n; * FUNCTION:    Acpi_ut_debug_print_raw&n; *&n; * PARAMETERS:  Requested_debug_level - Requested debug print level&n; *              Line_number         - Caller&squot;s line number&n; *              Dbg_info            - Contains:&n; *                  Proc_name           - Caller&squot;s procedure name&n; *                  Module_name         - Caller&squot;s module name&n; *                  Component_id        - Caller&squot;s component ID&n; *              Format              - Printf format field&n; *              ...                 - Optional printf arguments&n; *&n; * RETURN:      None&n; *&n; * DESCRIPTION: Print message with no headers.  Has same interface as&n; *              Debug_print so that the same macros can be used.&n; *&n; ****************************************************************************/
r_void
id|ACPI_INTERNAL_VAR_XFACE
DECL|function|acpi_ut_debug_print_raw
id|acpi_ut_debug_print_raw
(paren
id|u32
id|requested_debug_level
comma
id|u32
id|line_number
comma
id|acpi_debug_print_info
op_star
id|dbg_info
comma
r_char
op_star
id|format
comma
dot
dot
dot
)paren
(brace
id|va_list
id|args
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|requested_debug_level
op_amp
id|acpi_dbg_level
)paren
op_logical_or
op_logical_neg
(paren
id|dbg_info-&gt;component_id
op_amp
id|acpi_dbg_layer
)paren
)paren
(brace
r_return
suffix:semicolon
)brace
id|va_start
(paren
id|args
comma
id|format
)paren
suffix:semicolon
id|acpi_os_vprintf
(paren
id|format
comma
id|args
)paren
suffix:semicolon
)brace
multiline_comment|/*****************************************************************************&n; *&n; * FUNCTION:    Acpi_ut_trace&n; *&n; * PARAMETERS:  Line_number         - Caller&squot;s line number&n; *              Dbg_info            - Contains:&n; *                  Proc_name           - Caller&squot;s procedure name&n; *                  Module_name         - Caller&squot;s module name&n; *                  Component_id        - Caller&squot;s component ID&n; *&n; * RETURN:      None&n; *&n; * DESCRIPTION: Function entry trace.  Prints only if TRACE_FUNCTIONS bit is&n; *              set in Debug_level&n; *&n; ****************************************************************************/
r_void
DECL|function|acpi_ut_trace
id|acpi_ut_trace
(paren
id|u32
id|line_number
comma
id|acpi_debug_print_info
op_star
id|dbg_info
)paren
(brace
id|acpi_gbl_nesting_level
op_increment
suffix:semicolon
id|acpi_ut_track_stack_ptr
(paren
)paren
suffix:semicolon
id|acpi_ut_debug_print
(paren
id|ACPI_LV_FUNCTIONS
comma
id|line_number
comma
id|dbg_info
comma
l_string|&quot;%s&bslash;n&quot;
comma
id|acpi_gbl_fn_entry_str
)paren
suffix:semicolon
)brace
multiline_comment|/*****************************************************************************&n; *&n; * FUNCTION:    Acpi_ut_trace_ptr&n; *&n; * PARAMETERS:  Line_number         - Caller&squot;s line number&n; *              Dbg_info            - Contains:&n; *                  Proc_name           - Caller&squot;s procedure name&n; *                  Module_name         - Caller&squot;s module name&n; *                  Component_id        - Caller&squot;s component ID&n; *              Pointer             - Pointer to display&n; *&n; * RETURN:      None&n; *&n; * DESCRIPTION: Function entry trace.  Prints only if TRACE_FUNCTIONS bit is&n; *              set in Debug_level&n; *&n; ****************************************************************************/
r_void
DECL|function|acpi_ut_trace_ptr
id|acpi_ut_trace_ptr
(paren
id|u32
id|line_number
comma
id|acpi_debug_print_info
op_star
id|dbg_info
comma
r_void
op_star
id|pointer
)paren
(brace
id|acpi_gbl_nesting_level
op_increment
suffix:semicolon
id|acpi_ut_track_stack_ptr
(paren
)paren
suffix:semicolon
id|acpi_ut_debug_print
(paren
id|ACPI_LV_FUNCTIONS
comma
id|line_number
comma
id|dbg_info
comma
l_string|&quot;%s %p&bslash;n&quot;
comma
id|acpi_gbl_fn_entry_str
comma
id|pointer
)paren
suffix:semicolon
)brace
multiline_comment|/*****************************************************************************&n; *&n; * FUNCTION:    Acpi_ut_trace_str&n; *&n; * PARAMETERS:  Line_number         - Caller&squot;s line number&n; *              Dbg_info            - Contains:&n; *                  Proc_name           - Caller&squot;s procedure name&n; *                  Module_name         - Caller&squot;s module name&n; *                  Component_id        - Caller&squot;s component ID&n; *              String              - Additional string to display&n; *&n; * RETURN:      None&n; *&n; * DESCRIPTION: Function entry trace.  Prints only if TRACE_FUNCTIONS bit is&n; *              set in Debug_level&n; *&n; ****************************************************************************/
r_void
DECL|function|acpi_ut_trace_str
id|acpi_ut_trace_str
(paren
id|u32
id|line_number
comma
id|acpi_debug_print_info
op_star
id|dbg_info
comma
id|NATIVE_CHAR
op_star
id|string
)paren
(brace
id|acpi_gbl_nesting_level
op_increment
suffix:semicolon
id|acpi_ut_track_stack_ptr
(paren
)paren
suffix:semicolon
id|acpi_ut_debug_print
(paren
id|ACPI_LV_FUNCTIONS
comma
id|line_number
comma
id|dbg_info
comma
l_string|&quot;%s %s&bslash;n&quot;
comma
id|acpi_gbl_fn_entry_str
comma
id|string
)paren
suffix:semicolon
)brace
multiline_comment|/*****************************************************************************&n; *&n; * FUNCTION:    Acpi_ut_trace_u32&n; *&n; * PARAMETERS:  Line_number         - Caller&squot;s line number&n; *              Dbg_info            - Contains:&n; *                  Proc_name           - Caller&squot;s procedure name&n; *                  Module_name         - Caller&squot;s module name&n; *                  Component_id        - Caller&squot;s component ID&n; *              Integer             - Integer to display&n; *&n; * RETURN:      None&n; *&n; * DESCRIPTION: Function entry trace.  Prints only if TRACE_FUNCTIONS bit is&n; *              set in Debug_level&n; *&n; ****************************************************************************/
r_void
DECL|function|acpi_ut_trace_u32
id|acpi_ut_trace_u32
(paren
id|u32
id|line_number
comma
id|acpi_debug_print_info
op_star
id|dbg_info
comma
id|u32
id|integer
)paren
(brace
id|acpi_gbl_nesting_level
op_increment
suffix:semicolon
id|acpi_ut_track_stack_ptr
(paren
)paren
suffix:semicolon
id|acpi_ut_debug_print
(paren
id|ACPI_LV_FUNCTIONS
comma
id|line_number
comma
id|dbg_info
comma
l_string|&quot;%s %08X&bslash;n&quot;
comma
id|acpi_gbl_fn_entry_str
comma
id|integer
)paren
suffix:semicolon
)brace
multiline_comment|/*****************************************************************************&n; *&n; * FUNCTION:    Acpi_ut_exit&n; *&n; * PARAMETERS:  Line_number         - Caller&squot;s line number&n; *              Dbg_info            - Contains:&n; *                  Proc_name           - Caller&squot;s procedure name&n; *                  Module_name         - Caller&squot;s module name&n; *                  Component_id        - Caller&squot;s component ID&n; *&n; * RETURN:      None&n; *&n; * DESCRIPTION: Function exit trace.  Prints only if TRACE_FUNCTIONS bit is&n; *              set in Debug_level&n; *&n; ****************************************************************************/
r_void
DECL|function|acpi_ut_exit
id|acpi_ut_exit
(paren
id|u32
id|line_number
comma
id|acpi_debug_print_info
op_star
id|dbg_info
)paren
(brace
id|acpi_ut_debug_print
(paren
id|ACPI_LV_FUNCTIONS
comma
id|line_number
comma
id|dbg_info
comma
l_string|&quot;%s&bslash;n&quot;
comma
id|acpi_gbl_fn_exit_str
)paren
suffix:semicolon
id|acpi_gbl_nesting_level
op_decrement
suffix:semicolon
)brace
multiline_comment|/*****************************************************************************&n; *&n; * FUNCTION:    Acpi_ut_status_exit&n; *&n; * PARAMETERS:  Line_number         - Caller&squot;s line number&n; *              Dbg_info            - Contains:&n; *                  Proc_name           - Caller&squot;s procedure name&n; *                  Module_name         - Caller&squot;s module name&n; *                  Component_id        - Caller&squot;s component ID&n; *              Status              - Exit status code&n; *&n; * RETURN:      None&n; *&n; * DESCRIPTION: Function exit trace.  Prints only if TRACE_FUNCTIONS bit is&n; *              set in Debug_level. Prints exit status also.&n; *&n; ****************************************************************************/
r_void
DECL|function|acpi_ut_status_exit
id|acpi_ut_status_exit
(paren
id|u32
id|line_number
comma
id|acpi_debug_print_info
op_star
id|dbg_info
comma
id|acpi_status
id|status
)paren
(brace
r_if
c_cond
(paren
id|ACPI_SUCCESS
(paren
id|status
)paren
)paren
(brace
id|acpi_ut_debug_print
(paren
id|ACPI_LV_FUNCTIONS
comma
id|line_number
comma
id|dbg_info
comma
l_string|&quot;%s %s&bslash;n&quot;
comma
id|acpi_gbl_fn_exit_str
comma
id|acpi_format_exception
(paren
id|status
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|acpi_ut_debug_print
(paren
id|ACPI_LV_FUNCTIONS
comma
id|line_number
comma
id|dbg_info
comma
l_string|&quot;%s ****Exception****: %s&bslash;n&quot;
comma
id|acpi_gbl_fn_exit_str
comma
id|acpi_format_exception
(paren
id|status
)paren
)paren
suffix:semicolon
)brace
id|acpi_gbl_nesting_level
op_decrement
suffix:semicolon
)brace
multiline_comment|/*****************************************************************************&n; *&n; * FUNCTION:    Acpi_ut_value_exit&n; *&n; * PARAMETERS:  Line_number         - Caller&squot;s line number&n; *              Dbg_info            - Contains:&n; *                  Proc_name           - Caller&squot;s procedure name&n; *                  Module_name         - Caller&squot;s module name&n; *                  Component_id        - Caller&squot;s component ID&n; *              Value               - Value to be printed with exit msg&n; *&n; * RETURN:      None&n; *&n; * DESCRIPTION: Function exit trace.  Prints only if TRACE_FUNCTIONS bit is&n; *              set in Debug_level. Prints exit value also.&n; *&n; ****************************************************************************/
r_void
DECL|function|acpi_ut_value_exit
id|acpi_ut_value_exit
(paren
id|u32
id|line_number
comma
id|acpi_debug_print_info
op_star
id|dbg_info
comma
id|acpi_integer
id|value
)paren
(brace
id|acpi_ut_debug_print
(paren
id|ACPI_LV_FUNCTIONS
comma
id|line_number
comma
id|dbg_info
comma
l_string|&quot;%s %8.8X%8.8X&bslash;n&quot;
comma
id|acpi_gbl_fn_exit_str
comma
id|ACPI_HIDWORD
(paren
id|value
)paren
comma
id|ACPI_LODWORD
(paren
id|value
)paren
)paren
suffix:semicolon
id|acpi_gbl_nesting_level
op_decrement
suffix:semicolon
)brace
multiline_comment|/*****************************************************************************&n; *&n; * FUNCTION:    Acpi_ut_ptr_exit&n; *&n; * PARAMETERS:  Line_number         - Caller&squot;s line number&n; *              Dbg_info            - Contains:&n; *                  Proc_name           - Caller&squot;s procedure name&n; *                  Module_name         - Caller&squot;s module name&n; *                  Component_id        - Caller&squot;s component ID&n; *              Value               - Value to be printed with exit msg&n; *&n; * RETURN:      None&n; *&n; * DESCRIPTION: Function exit trace.  Prints only if TRACE_FUNCTIONS bit is&n; *              set in Debug_level. Prints exit value also.&n; *&n; ****************************************************************************/
r_void
DECL|function|acpi_ut_ptr_exit
id|acpi_ut_ptr_exit
(paren
id|u32
id|line_number
comma
id|acpi_debug_print_info
op_star
id|dbg_info
comma
id|u8
op_star
id|ptr
)paren
(brace
id|acpi_ut_debug_print
(paren
id|ACPI_LV_FUNCTIONS
comma
id|line_number
comma
id|dbg_info
comma
l_string|&quot;%s %p&bslash;n&quot;
comma
id|acpi_gbl_fn_exit_str
comma
id|ptr
)paren
suffix:semicolon
id|acpi_gbl_nesting_level
op_decrement
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*****************************************************************************&n; *&n; * FUNCTION:    Acpi_ut_dump_buffer&n; *&n; * PARAMETERS:  Buffer              - Buffer to dump&n; *              Count               - Amount to dump, in bytes&n; *              Display             - BYTE, WORD, DWORD, or QWORD display&n; *              Component_iD        - Caller&squot;s component ID&n; *&n; * RETURN:      None&n; *&n; * DESCRIPTION: Generic dump buffer in both hex and ascii.&n; *&n; ****************************************************************************/
r_void
DECL|function|acpi_ut_dump_buffer
id|acpi_ut_dump_buffer
(paren
id|u8
op_star
id|buffer
comma
id|u32
id|count
comma
id|u32
id|display
comma
id|u32
id|component_id
)paren
(brace
id|NATIVE_UINT
id|i
op_assign
l_int|0
suffix:semicolon
id|NATIVE_UINT
id|j
suffix:semicolon
id|u32
id|temp32
suffix:semicolon
id|u8
id|buf_char
suffix:semicolon
multiline_comment|/* Only dump the buffer if tracing is enabled */
r_if
c_cond
(paren
op_logical_neg
(paren
(paren
id|ACPI_LV_TABLES
op_amp
id|acpi_dbg_level
)paren
op_logical_and
(paren
id|component_id
op_amp
id|acpi_dbg_layer
)paren
)paren
)paren
(brace
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|count
OL
l_int|4
)paren
op_logical_or
(paren
id|count
op_amp
l_int|0x01
)paren
)paren
(brace
id|display
op_assign
id|DB_BYTE_DISPLAY
suffix:semicolon
)brace
id|acpi_os_printf
(paren
l_string|&quot;&bslash;nOffset Value&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Nasty little dump buffer routine!&n;&t; */
r_while
c_loop
(paren
id|i
OL
id|count
)paren
(brace
multiline_comment|/* Print current offset */
id|acpi_os_printf
(paren
l_string|&quot;%05X  &quot;
comma
id|i
)paren
suffix:semicolon
multiline_comment|/* Print 16 hex chars */
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
l_int|16
suffix:semicolon
)paren
(brace
r_if
c_cond
(paren
id|i
op_plus
id|j
op_ge
id|count
)paren
(brace
id|acpi_os_printf
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Make sure that the s8 doesn&squot;t get sign-extended! */
r_switch
c_cond
(paren
id|display
)paren
(brace
multiline_comment|/* Default is BYTE display */
r_default
suffix:colon
id|acpi_os_printf
(paren
l_string|&quot;%02X &quot;
comma
op_star
(paren
(paren
id|u8
op_star
)paren
op_amp
id|buffer
(braket
id|i
op_plus
id|j
)braket
)paren
)paren
suffix:semicolon
id|j
op_add_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DB_WORD_DISPLAY
suffix:colon
id|ACPI_MOVE_UNALIGNED16_TO_32
(paren
op_amp
id|temp32
comma
op_amp
id|buffer
(braket
id|i
op_plus
id|j
)braket
)paren
suffix:semicolon
id|acpi_os_printf
(paren
l_string|&quot;%04X &quot;
comma
id|temp32
)paren
suffix:semicolon
id|j
op_add_assign
l_int|2
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DB_DWORD_DISPLAY
suffix:colon
id|ACPI_MOVE_UNALIGNED32_TO_32
(paren
op_amp
id|temp32
comma
op_amp
id|buffer
(braket
id|i
op_plus
id|j
)braket
)paren
suffix:semicolon
id|acpi_os_printf
(paren
l_string|&quot;%08X &quot;
comma
id|temp32
)paren
suffix:semicolon
id|j
op_add_assign
l_int|4
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DB_QWORD_DISPLAY
suffix:colon
id|ACPI_MOVE_UNALIGNED32_TO_32
(paren
op_amp
id|temp32
comma
op_amp
id|buffer
(braket
id|i
op_plus
id|j
)braket
)paren
suffix:semicolon
id|acpi_os_printf
(paren
l_string|&quot;%08X&quot;
comma
id|temp32
)paren
suffix:semicolon
id|ACPI_MOVE_UNALIGNED32_TO_32
(paren
op_amp
id|temp32
comma
op_amp
id|buffer
(braket
id|i
op_plus
id|j
op_plus
l_int|4
)braket
)paren
suffix:semicolon
id|acpi_os_printf
(paren
l_string|&quot;%08X &quot;
comma
id|temp32
)paren
suffix:semicolon
id|j
op_add_assign
l_int|8
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t;&t; * Print the ASCII equivalent characters&n;&t;&t; * But watch out for the bad unprintable ones...&n;&t;&t; */
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
l_int|16
suffix:semicolon
id|j
op_increment
)paren
(brace
r_if
c_cond
(paren
id|i
op_plus
id|j
op_ge
id|count
)paren
(brace
id|acpi_os_printf
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|buf_char
op_assign
id|buffer
(braket
id|i
op_plus
id|j
)braket
suffix:semicolon
r_if
c_cond
(paren
(paren
id|buf_char
OG
l_int|0x1F
op_logical_and
id|buf_char
OL
l_int|0x2E
)paren
op_logical_or
(paren
id|buf_char
OG
l_int|0x2F
op_logical_and
id|buf_char
OL
l_int|0x61
)paren
op_logical_or
(paren
id|buf_char
OG
l_int|0x60
op_logical_and
id|buf_char
OL
l_int|0x7F
)paren
)paren
(brace
id|acpi_os_printf
(paren
l_string|&quot;%c&quot;
comma
id|buf_char
)paren
suffix:semicolon
)brace
r_else
(brace
id|acpi_os_printf
(paren
l_string|&quot;.&quot;
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Done with that line. */
id|acpi_os_printf
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|i
op_add_assign
l_int|16
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
eof
