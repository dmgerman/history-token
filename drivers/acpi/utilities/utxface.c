multiline_comment|/******************************************************************************&n; *&n; * Module Name: utxface - External interfaces for &quot;global&quot; ACPI functions&n; *&n; *****************************************************************************/
multiline_comment|/*&n; * Copyright (C) 2000 - 2004, R. Byron Moore&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. Redistributions in binary form must reproduce at minimum a disclaimer&n; *    substantially similar to the &quot;NO WARRANTY&quot; disclaimer below&n; *    (&quot;Disclaimer&quot;) and any redistribution must be conditioned upon&n; *    including a substantially similar Disclaimer requirement for further&n; *    binary redistribution.&n; * 3. Neither the names of the above-listed copyright holders nor the names&n; *    of any contributors may be used to endorse or promote products derived&n; *    from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;) version 2 as published by the Free&n; * Software Foundation.&n; *&n; * NO WARRANTY&n; * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS&n; * &quot;AS IS&quot; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT&n; * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR&n; * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT&n; * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,&n; * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING&n; * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE&n; * POSSIBILITY OF SUCH DAMAGES.&n; */
macro_line|#include &lt;acpi/acpi.h&gt;
macro_line|#include &lt;acpi/acevents.h&gt;
macro_line|#include &lt;acpi/acnamesp.h&gt;
macro_line|#include &lt;acpi/acparser.h&gt;
macro_line|#include &lt;acpi/acdispat.h&gt;
macro_line|#include &lt;acpi/acdebug.h&gt;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_UTILITIES
id|ACPI_MODULE_NAME
(paren
l_string|&quot;utxface&quot;
)paren
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_initialize_subsystem&n; *&n; * PARAMETERS:  None&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Initializes all global variables.  This is the first function&n; *              called, so any early initialization belongs here.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_initialize_subsystem
id|acpi_initialize_subsystem
(paren
r_void
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;acpi_initialize_subsystem&quot;
)paren
suffix:semicolon
id|ACPI_DEBUG_EXEC
(paren
id|acpi_ut_init_stack_ptr_trace
(paren
)paren
)paren
suffix:semicolon
multiline_comment|/* Initialize all globals used by the subsystem */
id|acpi_ut_init_globals
(paren
)paren
suffix:semicolon
multiline_comment|/* Initialize the OS-Dependent layer */
id|status
op_assign
id|acpi_os_initialize
(paren
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
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;OSD failed to initialize, %s&bslash;n&quot;
comma
id|acpi_format_exception
(paren
id|status
)paren
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/* Create the default mutex objects */
id|status
op_assign
id|acpi_ut_mutex_initialize
(paren
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
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;Global mutex creation failure, %s&bslash;n&quot;
comma
id|acpi_format_exception
(paren
id|status
)paren
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Initialize the namespace manager and&n;&t; * the root of the namespace tree&n;&t; */
id|status
op_assign
id|acpi_ns_root_initialize
(paren
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
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;Namespace initialization failure, %s&bslash;n&quot;
comma
id|acpi_format_exception
(paren
id|status
)paren
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/* If configured, initialize the AML debugger */
id|ACPI_DEBUGGER_EXEC
(paren
id|status
op_assign
id|acpi_db_initialize
(paren
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_enable_subsystem&n; *&n; * PARAMETERS:  Flags           - Init/enable Options&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Completes the subsystem initialization including hardware.&n; *              Puts system into ACPI mode if it isn&squot;t already.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_enable_subsystem
id|acpi_enable_subsystem
(paren
id|u32
id|flags
)paren
(brace
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;acpi_enable_subsystem&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * We must initialize the hardware before we can enable ACPI.&n;&t; * The values from the FADT are validated here.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
(paren
id|flags
op_amp
id|ACPI_NO_HARDWARE_INIT
)paren
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_EXEC
comma
l_string|&quot;[Init] Initializing ACPI hardware&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|status
op_assign
id|acpi_hw_initialize
(paren
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
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; * Enable ACPI mode&n;&t; */
r_if
c_cond
(paren
op_logical_neg
(paren
id|flags
op_amp
id|ACPI_NO_ACPI_ENABLE
)paren
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_EXEC
comma
l_string|&quot;[Init] Going into ACPI mode&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|acpi_gbl_original_mode
op_assign
id|acpi_hw_get_mode
c_func
(paren
)paren
suffix:semicolon
id|status
op_assign
id|acpi_enable
(paren
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
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_WARN
comma
l_string|&quot;acpi_enable failed.&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; * Initialize ACPI Event handling&n;&t; *&n;&t; * NOTE: We must have the hardware AND events initialized before we can execute&n;&t; * ANY control methods SAFELY.  Any control method can require ACPI hardware&n;&t; * support, so the hardware MUST be initialized before execution!&n;&t; */
r_if
c_cond
(paren
op_logical_neg
(paren
id|flags
op_amp
id|ACPI_NO_EVENT_INIT
)paren
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_EXEC
comma
l_string|&quot;[Init] Initializing ACPI events&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|status
op_assign
id|acpi_ev_initialize
(paren
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
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Install the SCI handler, Global Lock handler, and GPE handlers */
r_if
c_cond
(paren
op_logical_neg
(paren
id|flags
op_amp
id|ACPI_NO_HANDLER_INIT
)paren
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_EXEC
comma
l_string|&quot;[Init] Installing SCI/GL/GPE handlers&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|status
op_assign
id|acpi_ev_handler_initialize
(paren
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
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
)brace
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_initialize_objects&n; *&n; * PARAMETERS:  Flags           - Init/enable Options&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Completes namespace initialization by initializing device&n; *              objects and executing AML code for Regions, buffers, etc.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_initialize_objects
id|acpi_initialize_objects
(paren
id|u32
id|flags
)paren
(brace
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;acpi_initialize_objects&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Install the default op_region handlers. These are installed unless&n;&t; * other handlers have already been installed via the&n;&t; * install_address_space_handler interface.&n;&t; *&n;&t; * NOTE: This will cause _REG methods to be run.  Any objects accessed&n;&t; * by the _REG methods will be automatically initialized, even if they&n;&t; * contain executable AML (see call to acpi_ns_initialize_objects below).&n;&t; */
r_if
c_cond
(paren
op_logical_neg
(paren
id|flags
op_amp
id|ACPI_NO_ADDRESS_SPACE_INIT
)paren
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_EXEC
comma
l_string|&quot;[Init] Installing default address space handlers&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|status
op_assign
id|acpi_ev_init_address_spaces
(paren
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
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; * Initialize the objects that remain uninitialized.  This&n;&t; * runs the executable AML that may be part of the declaration of these&n;&t; * objects: operation_regions, buffer_fields, Buffers, and Packages.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
(paren
id|flags
op_amp
id|ACPI_NO_OBJECT_INIT
)paren
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_EXEC
comma
l_string|&quot;[Init] Initializing ACPI Objects&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|status
op_assign
id|acpi_ns_initialize_objects
(paren
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
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; * Initialize all device objects in the namespace&n;&t; * This runs the _STA and _INI methods.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
(paren
id|flags
op_amp
id|ACPI_NO_DEVICE_INIT
)paren
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_EXEC
comma
l_string|&quot;[Init] Initializing ACPI Devices&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|status
op_assign
id|acpi_ns_initialize_devices
(paren
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
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; * Empty the caches (delete the cached objects) on the assumption that&n;&t; * the table load filled them up more than they will be at runtime --&n;&t; * thus wasting non-paged memory.&n;&t; */
id|status
op_assign
id|acpi_purge_cached_objects
(paren
)paren
suffix:semicolon
id|acpi_gbl_startup_flags
op_or_assign
id|ACPI_INITIALIZED_OK
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_terminate&n; *&n; * PARAMETERS:  None&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Shutdown the ACPI subsystem.  Release all resources.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_terminate
id|acpi_terminate
(paren
r_void
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;acpi_terminate&quot;
)paren
suffix:semicolon
multiline_comment|/* Terminate the AML Debugger if present */
id|ACPI_DEBUGGER_EXEC
c_func
(paren
id|acpi_gbl_db_terminate_threads
op_assign
id|TRUE
)paren
suffix:semicolon
multiline_comment|/* Shutdown and free all resources */
id|acpi_ut_subsystem_shutdown
(paren
)paren
suffix:semicolon
multiline_comment|/* Free the mutex objects */
id|acpi_ut_mutex_terminate
(paren
)paren
suffix:semicolon
macro_line|#ifdef ACPI_DEBUGGER
multiline_comment|/* Shut down the debugger */
id|acpi_db_terminate
(paren
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Now we can shutdown the OS-dependent layer */
id|status
op_assign
id|acpi_os_terminate
(paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*****************************************************************************&n; *&n; * FUNCTION:    acpi_subsystem_status&n; *&n; * PARAMETERS:  None&n; *&n; * RETURN:      Status of the ACPI subsystem&n; *&n; * DESCRIPTION: Other drivers that use the ACPI subsystem should call this&n; *              before making any other calls, to ensure the subsystem initial-&n; *              ized successfully.&n; *&n; ****************************************************************************/
id|acpi_status
DECL|function|acpi_subsystem_status
id|acpi_subsystem_status
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|acpi_gbl_startup_flags
op_amp
id|ACPI_INITIALIZED_OK
)paren
(brace
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
r_else
(brace
r_return
(paren
id|AE_ERROR
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/******************************************************************************&n; *&n; * FUNCTION:    acpi_get_system_info&n; *&n; * PARAMETERS:  out_buffer      - a pointer to a buffer to receive the&n; *                                resources for the device&n; *              buffer_length   - the number of bytes available in the buffer&n; *&n; * RETURN:      Status          - the status of the call&n; *&n; * DESCRIPTION: This function is called to get information about the current&n; *              state of the ACPI subsystem.  It will return system information&n; *              in the out_buffer.&n; *&n; *              If the function fails an appropriate status will be returned&n; *              and the value of out_buffer is undefined.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_get_system_info
id|acpi_get_system_info
(paren
r_struct
id|acpi_buffer
op_star
id|out_buffer
)paren
(brace
r_struct
id|acpi_system_info
op_star
id|info_ptr
suffix:semicolon
id|u32
id|i
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;acpi_get_system_info&quot;
)paren
suffix:semicolon
multiline_comment|/* Parameter validation */
id|status
op_assign
id|acpi_ut_validate_buffer
(paren
id|out_buffer
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
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/* Validate/Allocate/Clear caller buffer */
id|status
op_assign
id|acpi_ut_initialize_buffer
(paren
id|out_buffer
comma
r_sizeof
(paren
r_struct
id|acpi_system_info
)paren
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
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Populate the return buffer&n;&t; */
id|info_ptr
op_assign
(paren
r_struct
id|acpi_system_info
op_star
)paren
id|out_buffer-&gt;pointer
suffix:semicolon
id|info_ptr-&gt;acpi_ca_version
op_assign
id|ACPI_CA_VERSION
suffix:semicolon
multiline_comment|/* System flags (ACPI capabilities) */
id|info_ptr-&gt;flags
op_assign
id|ACPI_SYS_MODE_ACPI
suffix:semicolon
multiline_comment|/* Timer resolution - 24 or 32 bits  */
r_if
c_cond
(paren
op_logical_neg
id|acpi_gbl_FADT
)paren
(brace
id|info_ptr-&gt;timer_resolution
op_assign
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|acpi_gbl_FADT-&gt;tmr_val_ext
op_eq
l_int|0
)paren
(brace
id|info_ptr-&gt;timer_resolution
op_assign
l_int|24
suffix:semicolon
)brace
r_else
(brace
id|info_ptr-&gt;timer_resolution
op_assign
l_int|32
suffix:semicolon
)brace
multiline_comment|/* Clear the reserved fields */
id|info_ptr-&gt;reserved1
op_assign
l_int|0
suffix:semicolon
id|info_ptr-&gt;reserved2
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Current debug levels */
id|info_ptr-&gt;debug_layer
op_assign
id|acpi_dbg_layer
suffix:semicolon
id|info_ptr-&gt;debug_level
op_assign
id|acpi_dbg_level
suffix:semicolon
multiline_comment|/* Current status of the ACPI tables, per table type */
id|info_ptr-&gt;num_table_types
op_assign
id|NUM_ACPI_TABLE_TYPES
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
id|NUM_ACPI_TABLE_TYPES
suffix:semicolon
id|i
op_increment
)paren
(brace
id|info_ptr-&gt;table_info
(braket
id|i
)braket
dot
id|count
op_assign
id|acpi_gbl_table_lists
(braket
id|i
)braket
dot
id|count
suffix:semicolon
)brace
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*****************************************************************************&n; *&n; * FUNCTION:    acpi_install_initialization_handler&n; *&n; * PARAMETERS:  Handler             - Callback procedure&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Install an initialization handler&n; *&n; * TBD: When a second function is added, must save the Function also.&n; *&n; ****************************************************************************/
id|acpi_status
DECL|function|acpi_install_initialization_handler
id|acpi_install_initialization_handler
(paren
id|acpi_init_handler
id|handler
comma
id|u32
id|function
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|handler
)paren
(brace
r_return
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|acpi_gbl_init_handler
)paren
(brace
r_return
(paren
id|AE_ALREADY_EXISTS
)paren
suffix:semicolon
)brace
id|acpi_gbl_init_handler
op_assign
id|handler
suffix:semicolon
r_return
id|AE_OK
suffix:semicolon
)brace
multiline_comment|/*****************************************************************************&n; *&n; * FUNCTION:    acpi_purge_cached_objects&n; *&n; * PARAMETERS:  None&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Empty all caches (delete the cached objects)&n; *&n; ****************************************************************************/
id|acpi_status
DECL|function|acpi_purge_cached_objects
id|acpi_purge_cached_objects
(paren
r_void
)paren
(brace
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;acpi_purge_cached_objects&quot;
)paren
suffix:semicolon
id|acpi_ut_delete_generic_state_cache
(paren
)paren
suffix:semicolon
id|acpi_ut_delete_object_cache
(paren
)paren
suffix:semicolon
id|acpi_ds_delete_walk_state_cache
(paren
)paren
suffix:semicolon
id|acpi_ps_delete_parse_cache
(paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
eof
