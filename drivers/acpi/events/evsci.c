multiline_comment|/*******************************************************************************&n; *&n; * Module Name: evsci - System Control Interrupt configuration and&n; *                      legacy to ACPI mode state transition functions&n; *&n; ******************************************************************************/
multiline_comment|/*&n; * Copyright (C) 2000 - 2003, R. Byron Moore&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. Redistributions in binary form must reproduce at minimum a disclaimer&n; *    substantially similar to the &quot;NO WARRANTY&quot; disclaimer below&n; *    (&quot;Disclaimer&quot;) and any redistribution must be conditioned upon&n; *    including a substantially similar Disclaimer requirement for further&n; *    binary redistribution.&n; * 3. Neither the names of the above-listed copyright holders nor the names&n; *    of any contributors may be used to endorse or promote products derived&n; *    from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;) version 2 as published by the Free&n; * Software Foundation.&n; *&n; * NO WARRANTY&n; * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS&n; * &quot;AS IS&quot; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT&n; * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR&n; * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT&n; * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,&n; * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING&n; * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE&n; * POSSIBILITY OF SUCH DAMAGES.&n; */
macro_line|#include &lt;acpi/acpi.h&gt;
macro_line|#include &lt;acpi/acevents.h&gt;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_EVENTS
id|ACPI_MODULE_NAME
(paren
l_string|&quot;evsci&quot;
)paren
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ev_sci_handler&n; *&n; * PARAMETERS:  Context   - Calling Context&n; *&n; * RETURN:      Status code indicates whether interrupt was handled.&n; *&n; * DESCRIPTION: Interrupt handler that will figure out what function or&n; *              control method to call to deal with a SCI.  Installed&n; *              using BU interrupt support.&n; *&n; ******************************************************************************/
r_static
id|u32
id|ACPI_SYSTEM_XFACE
DECL|function|acpi_ev_sci_handler
id|acpi_ev_sci_handler
(paren
r_void
op_star
id|context
)paren
(brace
id|u32
id|interrupt_handled
op_assign
id|ACPI_INTERRUPT_NOT_HANDLED
suffix:semicolon
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;ev_sci_handler&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * We are guaranteed by the ACPI CA initialization/shutdown code that&n;&t; * if this interrupt handler is installed, ACPI is enabled.&n;&t; */
multiline_comment|/*&n;&t; * Fixed acpi_events:&n;&t; * Check for and dispatch any Fixed acpi_events that have occurred&n;&t; */
id|interrupt_handled
op_or_assign
id|acpi_ev_fixed_event_detect
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * GPEs:&n;&t; * Check for and dispatch any GPEs that have occurred&n;&t; */
id|interrupt_handled
op_or_assign
id|acpi_ev_gpe_detect
(paren
)paren
suffix:semicolon
id|return_VALUE
(paren
id|interrupt_handled
)paren
suffix:semicolon
)brace
multiline_comment|/******************************************************************************&n; *&n; * FUNCTION:    acpi_ev_install_sci_handler&n; *&n; * PARAMETERS:  none&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Installs SCI handler.&n; *&n; ******************************************************************************/
id|u32
DECL|function|acpi_ev_install_sci_handler
id|acpi_ev_install_sci_handler
(paren
r_void
)paren
(brace
id|u32
id|status
op_assign
id|AE_OK
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ev_install_sci_handler&quot;
)paren
suffix:semicolon
id|status
op_assign
id|acpi_os_install_interrupt_handler
(paren
(paren
id|u32
)paren
id|acpi_gbl_FADT-&gt;sci_int
comma
id|acpi_ev_sci_handler
comma
l_int|NULL
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/******************************************************************************&n; *&n; * FUNCTION:    acpi_ev_remove_sci_handler&n; *&n; * PARAMETERS:  none&n; *&n; * RETURN:      E_OK if handler uninstalled OK, E_ERROR if handler was not&n; *              installed to begin with&n; *&n; * DESCRIPTION: Remove the SCI interrupt handler.  No further SCIs will be&n; *              taken.&n; *&n; * Note:  It doesn&squot;t seem important to disable all events or set the event&n; *        enable registers to their original values.  The OS should disable&n; *        the SCI interrupt level when the handler is removed, so no more&n; *        events will come in.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ev_remove_sci_handler
id|acpi_ev_remove_sci_handler
(paren
r_void
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ev_remove_sci_handler&quot;
)paren
suffix:semicolon
multiline_comment|/* Just let the OS remove the handler and disable the level */
id|status
op_assign
id|acpi_os_remove_interrupt_handler
(paren
(paren
id|u32
)paren
id|acpi_gbl_FADT-&gt;sci_int
comma
id|acpi_ev_sci_handler
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
eof
