multiline_comment|/*******************************************************************************&n; *&n; * Module Name: dbexec - debugger control method execution&n; *              $Revision: 42 $&n; *&n; ******************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000 - 2002, R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &quot;acpi.h&quot;
macro_line|#include &quot;acdebug.h&quot;
macro_line|#ifdef ENABLE_DEBUGGER
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_DEBUGGER
id|ACPI_MODULE_NAME
(paren
l_string|&quot;dbexec&quot;
)paren
DECL|variable|acpi_gbl_db_method_info
r_static
id|acpi_db_method_info
id|acpi_gbl_db_method_info
suffix:semicolon
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_db_execute_method&n; *&n; * PARAMETERS:  Info            - Valid info segment&n; *              Return_obj      - Where to put return object&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Execute a control method.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_db_execute_method
id|acpi_db_execute_method
(paren
id|acpi_db_method_info
op_star
id|info
comma
id|acpi_buffer
op_star
id|return_obj
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
id|acpi_object_list
id|param_objects
suffix:semicolon
id|acpi_object
id|params
(braket
id|MTH_NUM_ARGS
)braket
suffix:semicolon
id|u32
id|i
suffix:semicolon
r_if
c_cond
(paren
id|acpi_gbl_db_output_to_file
op_logical_and
op_logical_neg
id|acpi_dbg_level
)paren
(brace
id|acpi_os_printf
(paren
l_string|&quot;Warning: debug output is not enabled!&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* Are there arguments to the method? */
r_if
c_cond
(paren
id|info-&gt;args
op_logical_and
id|info-&gt;args
(braket
l_int|0
)braket
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|info-&gt;args
(braket
id|i
)braket
op_logical_and
id|i
OL
id|MTH_NUM_ARGS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|params
(braket
id|i
)braket
dot
id|type
op_assign
id|ACPI_TYPE_INTEGER
suffix:semicolon
id|params
(braket
id|i
)braket
dot
id|integer.value
op_assign
id|ACPI_STRTOUL
(paren
id|info-&gt;args
(braket
id|i
)braket
comma
l_int|NULL
comma
l_int|16
)paren
suffix:semicolon
)brace
id|param_objects.pointer
op_assign
id|params
suffix:semicolon
id|param_objects.count
op_assign
id|i
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Setup default parameters */
id|params
(braket
l_int|0
)braket
dot
id|type
op_assign
id|ACPI_TYPE_INTEGER
suffix:semicolon
id|params
(braket
l_int|0
)braket
dot
id|integer.value
op_assign
l_int|0x01020304
suffix:semicolon
id|params
(braket
l_int|1
)braket
dot
id|type
op_assign
id|ACPI_TYPE_STRING
suffix:semicolon
id|params
(braket
l_int|1
)braket
dot
id|string.length
op_assign
l_int|12
suffix:semicolon
id|params
(braket
l_int|1
)braket
dot
id|string.pointer
op_assign
l_string|&quot;AML Debugger&quot;
suffix:semicolon
id|param_objects.pointer
op_assign
id|params
suffix:semicolon
id|param_objects.count
op_assign
l_int|2
suffix:semicolon
)brace
multiline_comment|/* Prepare for a return object of arbitrary size */
id|return_obj-&gt;pointer
op_assign
id|acpi_gbl_db_buffer
suffix:semicolon
id|return_obj-&gt;length
op_assign
id|ACPI_DEBUG_BUFFER_SIZE
suffix:semicolon
multiline_comment|/* Do the actual method execution */
id|status
op_assign
id|acpi_evaluate_object
(paren
l_int|NULL
comma
id|info-&gt;pathname
comma
op_amp
id|param_objects
comma
id|return_obj
)paren
suffix:semicolon
id|acpi_gbl_cm_single_step
op_assign
id|FALSE
suffix:semicolon
id|acpi_gbl_method_executing
op_assign
id|FALSE
suffix:semicolon
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_db_execute_setup&n; *&n; * PARAMETERS:  Info            - Valid method info&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Setup info segment prior to method execution&n; *&n; ******************************************************************************/
r_void
DECL|function|acpi_db_execute_setup
id|acpi_db_execute_setup
(paren
id|acpi_db_method_info
op_star
id|info
)paren
(brace
multiline_comment|/* Catenate the current scope to the supplied name */
id|info-&gt;pathname
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|info-&gt;name
(braket
l_int|0
)braket
op_ne
l_char|&squot;&bslash;&bslash;&squot;
)paren
op_logical_and
(paren
id|info-&gt;name
(braket
l_int|0
)braket
op_ne
l_char|&squot;/&squot;
)paren
)paren
(brace
id|ACPI_STRCAT
(paren
id|info-&gt;pathname
comma
id|acpi_gbl_db_scope_buf
)paren
suffix:semicolon
)brace
id|ACPI_STRCAT
(paren
id|info-&gt;pathname
comma
id|info-&gt;name
)paren
suffix:semicolon
id|acpi_db_prep_namestring
(paren
id|info-&gt;pathname
)paren
suffix:semicolon
id|acpi_db_set_output_destination
(paren
id|ACPI_DB_DUPLICATE_OUTPUT
)paren
suffix:semicolon
id|acpi_os_printf
(paren
l_string|&quot;Executing %s&bslash;n&quot;
comma
id|info-&gt;pathname
)paren
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;flags
op_amp
id|EX_SINGLE_STEP
)paren
(brace
id|acpi_gbl_cm_single_step
op_assign
id|TRUE
suffix:semicolon
id|acpi_db_set_output_destination
(paren
id|ACPI_DB_CONSOLE_OUTPUT
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* No single step, allow redirection to a file */
id|acpi_db_set_output_destination
(paren
id|ACPI_DB_REDIRECTABLE_OUTPUT
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_db_get_outstanding_allocations&n; *&n; * PARAMETERS:  None&n; *&n; * RETURN:      Current global allocation count minus cache entries&n; *&n; * DESCRIPTION: Determine the current number of &quot;outstanding&quot; allocations --&n; *              those allocations that have not been freed and also are not&n; *              in one of the various object caches.&n; *&n; ******************************************************************************/
id|u32
DECL|function|acpi_db_get_outstanding_allocations
id|acpi_db_get_outstanding_allocations
(paren
r_void
)paren
(brace
id|u32
id|outstanding
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef ACPI_DBG_TRACK_ALLOCATIONS
id|u32
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|ACPI_MEM_LIST_FIRST_CACHE_LIST
suffix:semicolon
id|i
OL
id|ACPI_NUM_MEM_LISTS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|outstanding
op_add_assign
(paren
id|acpi_gbl_memory_lists
(braket
id|i
)braket
dot
id|total_allocated
op_minus
id|acpi_gbl_memory_lists
(braket
id|i
)braket
dot
id|total_freed
op_minus
id|acpi_gbl_memory_lists
(braket
id|i
)braket
dot
id|cache_depth
)paren
suffix:semicolon
)brace
macro_line|#endif
r_return
(paren
id|outstanding
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_db_execute&n; *&n; * PARAMETERS:  Name                - Name of method to execute&n; *              Args                - Parameters to the method&n; *              Flags               - single step/no single step&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Execute a control method.  Name is relative to the current&n; *              scope.&n; *&n; ******************************************************************************/
r_void
DECL|function|acpi_db_execute
id|acpi_db_execute
(paren
id|NATIVE_CHAR
op_star
id|name
comma
id|NATIVE_CHAR
op_star
op_star
id|args
comma
id|u32
id|flags
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
id|acpi_buffer
id|return_obj
suffix:semicolon
macro_line|#ifdef ACPI_DEBUG
id|u32
id|previous_allocations
suffix:semicolon
id|u32
id|allocations
suffix:semicolon
multiline_comment|/* Memory allocation tracking */
id|previous_allocations
op_assign
id|acpi_db_get_outstanding_allocations
(paren
)paren
suffix:semicolon
macro_line|#endif
id|acpi_gbl_db_method_info.name
op_assign
id|name
suffix:semicolon
id|acpi_gbl_db_method_info.args
op_assign
id|args
suffix:semicolon
id|acpi_gbl_db_method_info.flags
op_assign
id|flags
suffix:semicolon
id|return_obj.pointer
op_assign
l_int|NULL
suffix:semicolon
id|return_obj.length
op_assign
id|ACPI_ALLOCATE_BUFFER
suffix:semicolon
id|acpi_db_execute_setup
(paren
op_amp
id|acpi_gbl_db_method_info
)paren
suffix:semicolon
id|status
op_assign
id|acpi_db_execute_method
(paren
op_amp
id|acpi_gbl_db_method_info
comma
op_amp
id|return_obj
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Allow any handlers in separate threads to complete.&n;&t; * (Such as Notify handlers invoked from AML executed above).&n;&t; */
id|acpi_os_sleep
(paren
l_int|0
comma
l_int|10
)paren
suffix:semicolon
macro_line|#ifdef ACPI_DEBUG
multiline_comment|/* Memory allocation tracking */
id|allocations
op_assign
id|acpi_db_get_outstanding_allocations
(paren
)paren
op_minus
id|previous_allocations
suffix:semicolon
id|acpi_db_set_output_destination
(paren
id|ACPI_DB_DUPLICATE_OUTPUT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|allocations
OG
l_int|0
)paren
(brace
id|acpi_os_printf
(paren
l_string|&quot;Outstanding: %ld allocations after execution&bslash;n&quot;
comma
id|allocations
)paren
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
id|ACPI_FAILURE
(paren
id|status
)paren
)paren
(brace
id|acpi_os_printf
(paren
l_string|&quot;Execution of %s failed with status %s&bslash;n&quot;
comma
id|acpi_gbl_db_method_info.pathname
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
multiline_comment|/* Display a return object, if any */
r_if
c_cond
(paren
id|return_obj.length
)paren
(brace
id|acpi_os_printf
(paren
l_string|&quot;Execution of %s returned object %p Buflen %X&bslash;n&quot;
comma
id|acpi_gbl_db_method_info.pathname
comma
id|return_obj.pointer
comma
id|return_obj.length
)paren
suffix:semicolon
id|acpi_db_dump_object
(paren
id|return_obj.pointer
comma
l_int|1
)paren
suffix:semicolon
)brace
r_else
(brace
id|acpi_os_printf
(paren
l_string|&quot;No return object from execution of %s&bslash;n&quot;
comma
id|acpi_gbl_db_method_info.pathname
)paren
suffix:semicolon
)brace
)brace
id|acpi_db_set_output_destination
(paren
id|ACPI_DB_CONSOLE_OUTPUT
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_db_method_thread&n; *&n; * PARAMETERS:  Context             - Execution info segment&n; *&n; * RETURN:      None&n; *&n; * DESCRIPTION: Debugger execute thread.  Waits for a command line, then&n; *              simply dispatches it.&n; *&n; ******************************************************************************/
r_void
id|ACPI_SYSTEM_XFACE
DECL|function|acpi_db_method_thread
id|acpi_db_method_thread
(paren
r_void
op_star
id|context
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
id|acpi_db_method_info
op_star
id|info
op_assign
id|context
suffix:semicolon
id|u32
id|i
suffix:semicolon
id|acpi_buffer
id|return_obj
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
id|info-&gt;num_loops
suffix:semicolon
id|i
op_increment
)paren
(brace
id|status
op_assign
id|acpi_db_execute_method
(paren
id|info
comma
op_amp
id|return_obj
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_SUCCESS
(paren
id|status
)paren
)paren
(brace
r_if
c_cond
(paren
id|return_obj.length
)paren
(brace
id|acpi_os_printf
(paren
l_string|&quot;Execution of %s returned object %p Buflen %X&bslash;n&quot;
comma
id|info-&gt;pathname
comma
id|return_obj.pointer
comma
id|return_obj.length
)paren
suffix:semicolon
id|acpi_db_dump_object
(paren
id|return_obj.pointer
comma
l_int|1
)paren
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/* Signal our completion */
id|status
op_assign
id|acpi_os_signal_semaphore
(paren
id|info-&gt;thread_gate
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_FAILURE
(paren
id|status
)paren
)paren
(brace
id|acpi_os_printf
(paren
l_string|&quot;Could not signal debugger semaphore&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_db_create_execution_threads&n; *&n; * PARAMETERS:  Num_threads_arg         - Number of threads to create&n; *              Num_loops_arg           - Loop count for the thread(s)&n; *              Method_name_arg         - Control method to execute&n; *&n; * RETURN:      None&n; *&n; * DESCRIPTION: Create threads to execute method(s)&n; *&n; ******************************************************************************/
r_void
DECL|function|acpi_db_create_execution_threads
id|acpi_db_create_execution_threads
(paren
id|NATIVE_CHAR
op_star
id|num_threads_arg
comma
id|NATIVE_CHAR
op_star
id|num_loops_arg
comma
id|NATIVE_CHAR
op_star
id|method_name_arg
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
id|u32
id|num_threads
suffix:semicolon
id|u32
id|num_loops
suffix:semicolon
id|u32
id|i
suffix:semicolon
id|acpi_handle
id|thread_gate
suffix:semicolon
multiline_comment|/* Get the arguments */
id|num_threads
op_assign
id|ACPI_STRTOUL
(paren
id|num_threads_arg
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
id|num_loops
op_assign
id|ACPI_STRTOUL
(paren
id|num_loops_arg
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|num_threads
op_logical_or
op_logical_neg
id|num_loops
)paren
(brace
id|acpi_os_printf
(paren
l_string|&quot;Bad argument: Threads %X, Loops %X&bslash;n&quot;
comma
id|num_threads
comma
id|num_loops
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Create the synchronization semaphore */
id|status
op_assign
id|acpi_os_create_semaphore
(paren
l_int|1
comma
l_int|0
comma
op_amp
id|thread_gate
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_FAILURE
(paren
id|status
)paren
)paren
(brace
id|acpi_os_printf
(paren
l_string|&quot;Could not create semaphore, %s&bslash;n&quot;
comma
id|acpi_format_exception
(paren
id|status
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Setup the context to be passed to each thread */
id|acpi_gbl_db_method_info.name
op_assign
id|method_name_arg
suffix:semicolon
id|acpi_gbl_db_method_info.args
op_assign
l_int|NULL
suffix:semicolon
id|acpi_gbl_db_method_info.flags
op_assign
l_int|0
suffix:semicolon
id|acpi_gbl_db_method_info.num_loops
op_assign
id|num_loops
suffix:semicolon
id|acpi_gbl_db_method_info.thread_gate
op_assign
id|thread_gate
suffix:semicolon
id|acpi_db_execute_setup
(paren
op_amp
id|acpi_gbl_db_method_info
)paren
suffix:semicolon
multiline_comment|/* Create the threads */
id|acpi_os_printf
(paren
l_string|&quot;Creating %X threads to execute %X times each&bslash;n&quot;
comma
id|num_threads
comma
id|num_loops
)paren
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
(paren
id|num_threads
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|status
op_assign
id|acpi_os_queue_for_execution
(paren
id|OSD_PRIORITY_MED
comma
id|acpi_db_method_thread
comma
op_amp
id|acpi_gbl_db_method_info
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_FAILURE
(paren
id|status
)paren
)paren
(brace
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/* Wait for all threads to complete */
id|i
op_assign
id|num_threads
suffix:semicolon
r_while
c_loop
(paren
id|i
)paren
multiline_comment|/* Brain damage for OSD implementations that only support wait of 1 unit */
(brace
id|status
op_assign
id|acpi_os_wait_semaphore
(paren
id|thread_gate
comma
l_int|1
comma
id|WAIT_FOREVER
)paren
suffix:semicolon
id|i
op_decrement
suffix:semicolon
)brace
multiline_comment|/* Cleanup and exit */
(paren
r_void
)paren
id|acpi_os_delete_semaphore
(paren
id|thread_gate
)paren
suffix:semicolon
id|acpi_db_set_output_destination
(paren
id|ACPI_DB_DUPLICATE_OUTPUT
)paren
suffix:semicolon
id|acpi_os_printf
(paren
l_string|&quot;All threads (%X) have completed&bslash;n&quot;
comma
id|num_threads
)paren
suffix:semicolon
id|acpi_db_set_output_destination
(paren
id|ACPI_DB_CONSOLE_OUTPUT
)paren
suffix:semicolon
)brace
macro_line|#endif /* ENABLE_DEBUGGER */
eof
