multiline_comment|/******************************************************************************&n; *&n; * Module Name: evevent - Fixed Event handling and dispatch&n; *&n; *****************************************************************************/
multiline_comment|/*&n; * Copyright (C) 2000 - 2004, R. Byron Moore&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. Redistributions in binary form must reproduce at minimum a disclaimer&n; *    substantially similar to the &quot;NO WARRANTY&quot; disclaimer below&n; *    (&quot;Disclaimer&quot;) and any redistribution must be conditioned upon&n; *    including a substantially similar Disclaimer requirement for further&n; *    binary redistribution.&n; * 3. Neither the names of the above-listed copyright holders nor the names&n; *    of any contributors may be used to endorse or promote products derived&n; *    from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;) version 2 as published by the Free&n; * Software Foundation.&n; *&n; * NO WARRANTY&n; * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS&n; * &quot;AS IS&quot; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT&n; * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR&n; * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT&n; * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,&n; * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING&n; * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE&n; * POSSIBILITY OF SUCH DAMAGES.&n; */
macro_line|#include &lt;acpi/acpi.h&gt;
macro_line|#include &lt;acpi/acevents.h&gt;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_EVENTS
id|ACPI_MODULE_NAME
(paren
l_string|&quot;evevent&quot;
)paren
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ev_initialize_events&n; *&n; * PARAMETERS:  None&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Initialize global data structures for events.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ev_initialize_events
id|acpi_ev_initialize_events
(paren
r_void
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ev_initialize_events&quot;
)paren
suffix:semicolon
multiline_comment|/* Make sure we have ACPI tables */
r_if
c_cond
(paren
op_logical_neg
id|acpi_gbl_DSDT
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_WARN
comma
l_string|&quot;No ACPI tables present!&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_NO_ACPI_TABLES
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Initialize the Fixed and General Purpose Events. This is&n;&t; * done prior to enabling SCIs to prevent interrupts from&n;&t; * occurring before handers are installed.&n;&t; */
id|status
op_assign
id|acpi_ev_fixed_event_initialize
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
l_string|&quot;Unable to initialize fixed events, %s&bslash;n&quot;
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
id|status
op_assign
id|acpi_ev_gpe_initialize
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
l_string|&quot;Unable to initialize general purpose events, %s&bslash;n&quot;
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
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ev_install_xrupt_handlers&n; *&n; * PARAMETERS:  None&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Install interrupt handlers for the SCI and Global Lock&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ev_install_xrupt_handlers
id|acpi_ev_install_xrupt_handlers
(paren
r_void
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ev_install_xrupt_handlers&quot;
)paren
suffix:semicolon
multiline_comment|/* Install the SCI handler */
id|status
op_assign
id|acpi_ev_install_sci_handler
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
l_string|&quot;Unable to install System Control Interrupt Handler, %s&bslash;n&quot;
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
multiline_comment|/* Install the handler for the Global Lock */
id|status
op_assign
id|acpi_ev_init_global_lock_handler
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
l_string|&quot;Unable to initialize Global Lock handler, %s&bslash;n&quot;
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
id|acpi_gbl_events_initialized
op_assign
id|TRUE
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ev_fixed_event_initialize&n; *&n; * PARAMETERS:  None&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Install the fixed event handlers and enable the fixed events.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ev_fixed_event_initialize
id|acpi_ev_fixed_event_initialize
(paren
r_void
)paren
(brace
id|acpi_native_uint
id|i
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
multiline_comment|/*&n;&t; * Initialize the structure that keeps track of fixed event handlers&n;&t; * and enable the fixed events.&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|ACPI_NUM_FIXED_EVENTS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|acpi_gbl_fixed_event_handlers
(braket
id|i
)braket
dot
id|handler
op_assign
l_int|NULL
suffix:semicolon
id|acpi_gbl_fixed_event_handlers
(braket
id|i
)braket
dot
id|context
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Enable the fixed event */
r_if
c_cond
(paren
id|acpi_gbl_fixed_event_info
(braket
id|i
)braket
dot
id|enable_register_id
op_ne
l_int|0xFF
)paren
(brace
id|status
op_assign
id|acpi_set_register
(paren
id|acpi_gbl_fixed_event_info
(braket
id|i
)braket
dot
id|enable_register_id
comma
l_int|0
comma
id|ACPI_MTX_LOCK
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
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
)brace
)brace
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ev_fixed_event_detect&n; *&n; * PARAMETERS:  None&n; *&n; * RETURN:      INTERRUPT_HANDLED or INTERRUPT_NOT_HANDLED&n; *&n; * DESCRIPTION: Checks the PM status register for fixed events&n; *&n; ******************************************************************************/
id|u32
DECL|function|acpi_ev_fixed_event_detect
id|acpi_ev_fixed_event_detect
(paren
r_void
)paren
(brace
id|u32
id|int_status
op_assign
id|ACPI_INTERRUPT_NOT_HANDLED
suffix:semicolon
id|u32
id|fixed_status
suffix:semicolon
id|u32
id|fixed_enable
suffix:semicolon
id|acpi_native_uint
id|i
suffix:semicolon
id|ACPI_FUNCTION_NAME
(paren
l_string|&quot;ev_fixed_event_detect&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Read the fixed feature status and enable registers, as all the cases&n;&t; * depend on their values.  Ignore errors here.&n;&t; */
(paren
r_void
)paren
id|acpi_hw_register_read
(paren
id|ACPI_MTX_DO_NOT_LOCK
comma
id|ACPI_REGISTER_PM1_STATUS
comma
op_amp
id|fixed_status
)paren
suffix:semicolon
(paren
r_void
)paren
id|acpi_hw_register_read
(paren
id|ACPI_MTX_DO_NOT_LOCK
comma
id|ACPI_REGISTER_PM1_ENABLE
comma
op_amp
id|fixed_enable
)paren
suffix:semicolon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_INTERRUPTS
comma
l_string|&quot;Fixed Event Block: Enable %08X Status %08X&bslash;n&quot;
comma
id|fixed_enable
comma
id|fixed_status
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Check for all possible Fixed Events and dispatch those that are active&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|ACPI_NUM_FIXED_EVENTS
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/* Both the status and enable bits must be on for this event */
r_if
c_cond
(paren
(paren
id|fixed_status
op_amp
id|acpi_gbl_fixed_event_info
(braket
id|i
)braket
dot
id|status_bit_mask
)paren
op_logical_and
(paren
id|fixed_enable
op_amp
id|acpi_gbl_fixed_event_info
(braket
id|i
)braket
dot
id|enable_bit_mask
)paren
)paren
(brace
multiline_comment|/* Found an active (signalled) event */
id|int_status
op_or_assign
id|acpi_ev_fixed_event_dispatch
(paren
(paren
id|u32
)paren
id|i
)paren
suffix:semicolon
)brace
)brace
r_return
(paren
id|int_status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ev_fixed_event_dispatch&n; *&n; * PARAMETERS:  Event               - Event type&n; *&n; * RETURN:      INTERRUPT_HANDLED or INTERRUPT_NOT_HANDLED&n; *&n; * DESCRIPTION: Clears the status bit for the requested event, calls the&n; *              handler that previously registered for the event.&n; *&n; ******************************************************************************/
id|u32
DECL|function|acpi_ev_fixed_event_dispatch
id|acpi_ev_fixed_event_dispatch
(paren
id|u32
id|event
)paren
(brace
id|ACPI_FUNCTION_ENTRY
(paren
)paren
suffix:semicolon
multiline_comment|/* Clear the status bit */
(paren
r_void
)paren
id|acpi_set_register
(paren
id|acpi_gbl_fixed_event_info
(braket
id|event
)braket
dot
id|status_register_id
comma
l_int|1
comma
id|ACPI_MTX_DO_NOT_LOCK
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Make sure we&squot;ve got a handler.  If not, report an error.&n;&t; * The event is disabled to prevent further interrupts.&n;&t; */
r_if
c_cond
(paren
l_int|NULL
op_eq
id|acpi_gbl_fixed_event_handlers
(braket
id|event
)braket
dot
id|handler
)paren
(brace
(paren
r_void
)paren
id|acpi_set_register
(paren
id|acpi_gbl_fixed_event_info
(braket
id|event
)braket
dot
id|enable_register_id
comma
l_int|0
comma
id|ACPI_MTX_DO_NOT_LOCK
)paren
suffix:semicolon
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;No installed handler for fixed event [%08X]&bslash;n&quot;
comma
id|event
)paren
)paren
suffix:semicolon
r_return
(paren
id|ACPI_INTERRUPT_NOT_HANDLED
)paren
suffix:semicolon
)brace
multiline_comment|/* Invoke the Fixed Event handler */
r_return
(paren
(paren
id|acpi_gbl_fixed_event_handlers
(braket
id|event
)braket
dot
id|handler
)paren
(paren
id|acpi_gbl_fixed_event_handlers
(braket
id|event
)braket
dot
id|context
)paren
)paren
suffix:semicolon
)brace
eof
