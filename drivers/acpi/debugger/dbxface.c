multiline_comment|/*******************************************************************************&n; *&n; * Module Name: dbxface - AML Debugger external interfaces&n; *              $Revision: 37 $&n; *&n; ******************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000, 2001 R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &quot;acpi.h&quot;
macro_line|#include &quot;acparser.h&quot;
macro_line|#include &quot;amlcode.h&quot;
macro_line|#include &quot;acnamesp.h&quot;
macro_line|#include &quot;acparser.h&quot;
macro_line|#include &quot;acevents.h&quot;
macro_line|#include &quot;acinterp.h&quot;
macro_line|#include &quot;acdebug.h&quot;
macro_line|#ifdef ENABLE_DEBUGGER
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_DEBUGGER
id|MODULE_NAME
(paren
l_string|&quot;dbxface&quot;
)paren
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_db_single_step&n; *&n; * PARAMETERS:  Walk_state      - Current walk&n; *              Op              - Current executing op&n; *              Op_type         - Type of the current AML Opcode&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Called just before execution of an AML opcode.&n; *&n; ******************************************************************************/
id|ACPI_STATUS
DECL|function|acpi_db_single_step
id|acpi_db_single_step
(paren
id|ACPI_WALK_STATE
op_star
id|walk_state
comma
id|ACPI_PARSE_OBJECT
op_star
id|op
comma
id|u8
id|op_type
)paren
(brace
id|ACPI_PARSE_OBJECT
op_star
id|next
suffix:semicolon
id|ACPI_STATUS
id|status
op_assign
id|AE_OK
suffix:semicolon
id|u32
id|original_debug_level
suffix:semicolon
id|ACPI_PARSE_OBJECT
op_star
id|display_op
suffix:semicolon
multiline_comment|/* Is there a breakpoint set? */
r_if
c_cond
(paren
id|walk_state-&gt;method_breakpoint
)paren
(brace
multiline_comment|/* Check if the breakpoint has been reached or passed */
r_if
c_cond
(paren
id|walk_state-&gt;method_breakpoint
op_le
id|op-&gt;aml_offset
)paren
(brace
multiline_comment|/* Hit the breakpoint, resume single step, reset breakpoint */
id|acpi_os_printf
(paren
l_string|&quot;***Break*** at AML offset %X&bslash;n&quot;
comma
id|op-&gt;aml_offset
)paren
suffix:semicolon
id|acpi_gbl_cm_single_step
op_assign
id|TRUE
suffix:semicolon
id|acpi_gbl_step_to_next_call
op_assign
id|FALSE
suffix:semicolon
id|walk_state-&gt;method_breakpoint
op_assign
l_int|0
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; * Check if this is an opcode that we are interested in --&n;&t; * namely, opcodes that have arguments&n;&t; */
r_if
c_cond
(paren
id|op-&gt;opcode
op_eq
id|AML_INT_NAMEDFIELD_OP
)paren
(brace
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|op_type
)paren
(brace
r_case
id|OPTYPE_UNDEFINED
suffix:colon
r_case
id|OPTYPE_CONSTANT
suffix:colon
multiline_comment|/* argument type only */
r_case
id|OPTYPE_LITERAL
suffix:colon
multiline_comment|/* argument type only */
r_case
id|OPTYPE_DATA_TERM
suffix:colon
multiline_comment|/* argument type only */
r_case
id|OPTYPE_LOCAL_VARIABLE
suffix:colon
multiline_comment|/* argument type only */
r_case
id|OPTYPE_METHOD_ARGUMENT
suffix:colon
multiline_comment|/* argument type only */
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OPTYPE_NAMED_OBJECT
suffix:colon
r_switch
c_cond
(paren
id|op-&gt;opcode
)paren
(brace
r_case
id|AML_INT_NAMEPATH_OP
suffix:colon
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; * Under certain debug conditions, display this opcode and its operands&n;&t; */
r_if
c_cond
(paren
(paren
id|output_to_file
)paren
op_logical_or
(paren
id|acpi_gbl_cm_single_step
)paren
op_logical_or
(paren
id|acpi_dbg_level
op_amp
id|TRACE_PARSE
)paren
)paren
(brace
r_if
c_cond
(paren
(paren
id|output_to_file
)paren
op_logical_or
(paren
id|acpi_dbg_level
op_amp
id|TRACE_PARSE
)paren
)paren
(brace
id|acpi_os_printf
(paren
l_string|&quot;&bslash;n[Aml_debug] Next AML Opcode to execute:&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Display this op (and only this op - zero out the NEXT field temporarily,&n;&t;&t; * and disable parser trace output for the duration of the display because&n;&t;&t; * we don&squot;t want the extraneous debug output)&n;&t;&t; */
id|original_debug_level
op_assign
id|acpi_dbg_level
suffix:semicolon
id|acpi_dbg_level
op_and_assign
op_complement
(paren
id|TRACE_PARSE
op_or
id|TRACE_FUNCTIONS
)paren
suffix:semicolon
id|next
op_assign
id|op-&gt;next
suffix:semicolon
id|op-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|display_op
op_assign
id|op
suffix:semicolon
r_if
c_cond
(paren
id|op-&gt;parent
)paren
(brace
r_if
c_cond
(paren
(paren
id|op-&gt;parent-&gt;opcode
op_eq
id|AML_IF_OP
)paren
op_logical_or
(paren
id|op-&gt;parent-&gt;opcode
op_eq
id|AML_WHILE_OP
)paren
)paren
(brace
id|display_op
op_assign
id|op-&gt;parent
suffix:semicolon
)brace
)brace
multiline_comment|/* Now we can display it */
id|acpi_db_display_op
(paren
id|walk_state
comma
id|display_op
comma
id|ACPI_UINT32_MAX
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|op-&gt;opcode
op_eq
id|AML_IF_OP
)paren
op_logical_or
(paren
id|op-&gt;opcode
op_eq
id|AML_WHILE_OP
)paren
)paren
(brace
r_if
c_cond
(paren
id|walk_state-&gt;control_state-&gt;common.value
)paren
(brace
id|acpi_os_printf
(paren
l_string|&quot;Predicate was TRUE, executed block&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|acpi_os_printf
(paren
l_string|&quot;Predicate is FALSE, skipping block&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|op-&gt;opcode
op_eq
id|AML_ELSE_OP
)paren
(brace
multiline_comment|/* TBD */
)brace
multiline_comment|/* Restore everything */
id|op-&gt;next
op_assign
id|next
suffix:semicolon
id|acpi_os_printf
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|acpi_dbg_level
op_assign
id|original_debug_level
suffix:semicolon
)brace
multiline_comment|/* If we are not single stepping, just continue executing the method */
r_if
c_cond
(paren
op_logical_neg
id|acpi_gbl_cm_single_step
)paren
(brace
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * If we are executing a step-to-call command,&n;&t; * Check if this is a method call.&n;&t; */
r_if
c_cond
(paren
id|acpi_gbl_step_to_next_call
)paren
(brace
r_if
c_cond
(paren
id|op-&gt;opcode
op_ne
id|AML_INT_METHODCALL_OP
)paren
(brace
multiline_comment|/* Not a method call, just keep executing */
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/* Found a method call, stop executing */
id|acpi_gbl_step_to_next_call
op_assign
id|FALSE
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * If the next opcode is a method call, we will &quot;step over&quot; it&n;&t; * by default.&n;&t; */
r_if
c_cond
(paren
id|op-&gt;opcode
op_eq
id|AML_INT_METHODCALL_OP
)paren
(brace
id|acpi_gbl_cm_single_step
op_assign
id|FALSE
suffix:semicolon
multiline_comment|/* No more single step while executing called method */
multiline_comment|/* Set the breakpoint on the call, it will stop execution as soon as we return */
multiline_comment|/* TBD: [Future] don&squot;t kill the user breakpoint! */
id|walk_state-&gt;method_breakpoint
op_assign
multiline_comment|/* Op-&gt;Aml_offset + */
l_int|1
suffix:semicolon
multiline_comment|/* Must be non-zero! */
)brace
multiline_comment|/* TBD: [Investigate] what are the namespace locking issues here */
multiline_comment|/* Acpi_ut_release_mutex (ACPI_MTX_NAMESPACE); */
multiline_comment|/* Go into the command loop and await next user command */
id|acpi_gbl_method_executing
op_assign
id|TRUE
suffix:semicolon
id|status
op_assign
id|AE_CTRL_TRUE
suffix:semicolon
r_while
c_loop
(paren
id|status
op_eq
id|AE_CTRL_TRUE
)paren
(brace
r_if
c_cond
(paren
id|acpi_gbl_debugger_configuration
op_eq
id|DEBUGGER_MULTI_THREADED
)paren
(brace
multiline_comment|/* Handshake with the front-end that gets user command lines */
id|acpi_ut_release_mutex
(paren
id|ACPI_MTX_DEBUG_CMD_COMPLETE
)paren
suffix:semicolon
id|acpi_ut_acquire_mutex
(paren
id|ACPI_MTX_DEBUG_CMD_READY
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Single threaded, we must get a command line ourselves */
multiline_comment|/* Force output to console until a command is entered */
id|acpi_db_set_output_destination
(paren
id|DB_CONSOLE_OUTPUT
)paren
suffix:semicolon
multiline_comment|/* Different prompt if method is executing */
r_if
c_cond
(paren
op_logical_neg
id|acpi_gbl_method_executing
)paren
(brace
id|acpi_os_printf
(paren
l_string|&quot;%1c &quot;
comma
id|DB_COMMAND_PROMPT
)paren
suffix:semicolon
)brace
r_else
(brace
id|acpi_os_printf
(paren
l_string|&quot;%1c &quot;
comma
id|DB_EXECUTE_PROMPT
)paren
suffix:semicolon
)brace
multiline_comment|/* Get the user input line */
id|acpi_os_get_line
(paren
id|line_buf
)paren
suffix:semicolon
)brace
id|status
op_assign
id|acpi_db_command_dispatch
(paren
id|line_buf
comma
id|walk_state
comma
id|op
)paren
suffix:semicolon
)brace
multiline_comment|/* Acpi_ut_acquire_mutex (ACPI_MTX_NAMESPACE); */
multiline_comment|/* User commands complete, continue execution of the interrupted method */
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_db_initialize&n; *&n; * PARAMETERS:  None&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Init and start debugger&n; *&n; ******************************************************************************/
r_int
DECL|function|acpi_db_initialize
id|acpi_db_initialize
(paren
r_void
)paren
(brace
multiline_comment|/* Init globals */
id|buffer
op_assign
id|acpi_os_allocate
(paren
id|BUFFER_SIZE
)paren
suffix:semicolon
multiline_comment|/* Initial scope is the root */
id|scope_buf
(braket
l_int|0
)braket
op_assign
l_char|&squot;&bslash;&bslash;&squot;
suffix:semicolon
id|scope_buf
(braket
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * If configured for multi-thread support, the debug executor runs in&n;&t; * a separate thread so that the front end can be in another address&n;&t; * space, environment, or even another machine.&n;&t; */
r_if
c_cond
(paren
id|acpi_gbl_debugger_configuration
op_amp
id|DEBUGGER_MULTI_THREADED
)paren
(brace
multiline_comment|/* These were created with one unit, grab it */
id|acpi_ut_acquire_mutex
(paren
id|ACPI_MTX_DEBUG_CMD_COMPLETE
)paren
suffix:semicolon
id|acpi_ut_acquire_mutex
(paren
id|ACPI_MTX_DEBUG_CMD_READY
)paren
suffix:semicolon
multiline_comment|/* Create the debug execution thread to execute commands */
id|acpi_os_queue_for_execution
(paren
l_int|0
comma
id|acpi_db_execute_thread
comma
l_int|NULL
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|opt_verbose
)paren
(brace
id|INDENT_STRING
op_assign
l_string|&quot;    &quot;
suffix:semicolon
id|opt_disasm
op_assign
id|TRUE
suffix:semicolon
id|opt_stats
op_assign
id|FALSE
suffix:semicolon
)brace
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
macro_line|#endif /* ENABLE_DEBUGGER */
eof
