multiline_comment|/*******************************************************************************&n; *&n; * Module Name: evsci - System Control Interrupt configuration and&n; *                      legacy to ACPI mode state transition functions&n; *              $Revision: 83 $&n; *&n; ******************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000 - 2002, R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &quot;acpi.h&quot;
macro_line|#include &quot;acnamesp.h&quot;
macro_line|#include &quot;achware.h&quot;
macro_line|#include &quot;acevents.h&quot;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_EVENTS
id|ACPI_MODULE_NAME
(paren
l_string|&quot;evsci&quot;
)paren
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ev_sci_handler&n; *&n; * PARAMETERS:  Context   - Calling Context&n; *&n; * RETURN:      Status code indicates whether interrupt was handled.&n; *&n; * DESCRIPTION: Interrupt handler that will figure out what function or&n; *              control method to call to deal with a SCI.  Installed&n; *              using BU interrupt support.&n; *&n; ******************************************************************************/
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
l_string|&quot;Ev_sci_handler&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Make sure that ACPI is enabled by checking SCI_EN.  Note that we are&n;&t; * required to treat the SCI interrupt as sharable, level, active low.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|acpi_hw_bit_register_read
(paren
id|ACPI_BITREG_SCI_ENABLE
comma
id|ACPI_MTX_DO_NOT_LOCK
)paren
)paren
(brace
multiline_comment|/* ACPI is not enabled;  this interrupt cannot be for us */
id|return_VALUE
(paren
id|ACPI_INTERRUPT_NOT_HANDLED
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Fixed Acpi_events:&n;&t; * -------------&n;&t; * Check for and dispatch any Fixed Acpi_events that have occurred&n;&t; */
id|interrupt_handled
op_or_assign
id|acpi_ev_fixed_event_detect
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * GPEs:&n;&t; * -----&n;&t; * Check for and dispatch any GPEs that have occurred&n;&t; */
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
multiline_comment|/******************************************************************************&n; *&n; * FUNCTION:    Acpi_ev_install_sci_handler&n; *&n; * PARAMETERS:  none&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Installs SCI handler.&n; *&n; ******************************************************************************/
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
l_string|&quot;Ev_install_sci_handler&quot;
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
multiline_comment|/******************************************************************************&n; *&n; * FUNCTION:    Acpi_ev_remove_sci_handler&n; *&n; * PARAMETERS:  none&n; *&n; * RETURN:      E_OK if handler uninstalled OK, E_ERROR if handler was not&n; *              installed to begin with&n; *&n; * DESCRIPTION: Remove the SCI interrupt handler.  No further SCIs will be&n; *              taken.&n; *&n; * Note:  It doesn&squot;t seem important to disable all events or set the event&n; *        enable registers to their original values.  The OS should disable&n; *        the SCI interrupt level when the handler is removed, so no more&n; *        events will come in.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ev_remove_sci_handler
id|acpi_ev_remove_sci_handler
(paren
r_void
)paren
(brace
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;Ev_remove_sci_handler&quot;
)paren
suffix:semicolon
multiline_comment|/* Just let the OS remove the handler and disable the level */
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
id|AE_OK
)paren
suffix:semicolon
)brace
eof
