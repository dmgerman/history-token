multiline_comment|/******************************************************************************&n; *&n; * Module Name: evxfevnt - External Interfaces, ACPI event disable/enable&n; *&n; *****************************************************************************/
multiline_comment|/*&n; * Copyright (C) 2000 - 2003, R. Byron Moore&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. Redistributions in binary form must reproduce at minimum a disclaimer&n; *    substantially similar to the &quot;NO WARRANTY&quot; disclaimer below&n; *    (&quot;Disclaimer&quot;) and any redistribution must be conditioned upon&n; *    including a substantially similar Disclaimer requirement for further&n; *    binary redistribution.&n; * 3. Neither the names of the above-listed copyright holders nor the names&n; *    of any contributors may be used to endorse or promote products derived&n; *    from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;) version 2 as published by the Free&n; * Software Foundation.&n; *&n; * NO WARRANTY&n; * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS&n; * &quot;AS IS&quot; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT&n; * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR&n; * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT&n; * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,&n; * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING&n; * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE&n; * POSSIBILITY OF SUCH DAMAGES.&n; */
macro_line|#include &lt;acpi/acpi.h&gt;
macro_line|#include &lt;acpi/acevents.h&gt;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_EVENTS
id|ACPI_MODULE_NAME
(paren
l_string|&quot;evxfevnt&quot;
)paren
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_enable&n; *&n; * PARAMETERS:  None&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Transfers the system into ACPI mode.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_enable
id|acpi_enable
(paren
r_void
)paren
(brace
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;acpi_enable&quot;
)paren
suffix:semicolon
multiline_comment|/* Make sure we have the FADT*/
r_if
c_cond
(paren
op_logical_neg
id|acpi_gbl_FADT
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_WARN
comma
l_string|&quot;No FADT information present!&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_NO_ACPI_TABLES
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|acpi_hw_get_mode
c_func
(paren
)paren
op_eq
id|ACPI_SYS_MODE_ACPI
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_INIT
comma
l_string|&quot;System is already in ACPI mode&bslash;n&quot;
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Transition to ACPI mode */
id|status
op_assign
id|acpi_hw_set_mode
(paren
id|ACPI_SYS_MODE_ACPI
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
l_string|&quot;Could not transition to ACPI mode.&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_INIT
comma
l_string|&quot;Transition to ACPI mode successful&bslash;n&quot;
)paren
)paren
suffix:semicolon
)brace
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_disable&n; *&n; * PARAMETERS:  None&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Transfers the system into LEGACY mode.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_disable
id|acpi_disable
(paren
r_void
)paren
(brace
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;acpi_disable&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|acpi_gbl_FADT
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_WARN
comma
l_string|&quot;No FADT information present!&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_NO_ACPI_TABLES
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|acpi_hw_get_mode
c_func
(paren
)paren
op_eq
id|ACPI_SYS_MODE_LEGACY
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_INIT
comma
l_string|&quot;System is already in legacy (non-ACPI) mode&bslash;n&quot;
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Transition to LEGACY mode */
id|status
op_assign
id|acpi_hw_set_mode
(paren
id|ACPI_SYS_MODE_LEGACY
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
id|ACPI_DB_ERROR
comma
l_string|&quot;Could not exit ACPI mode to legacy mode&quot;
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_INIT
comma
l_string|&quot;ACPI mode disabled&bslash;n&quot;
)paren
)paren
suffix:semicolon
)brace
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_enable_event&n; *&n; * PARAMETERS:  Event           - The fixed eventto be enabled&n; *              Flags           - Reserved&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Enable an ACPI event (fixed)&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_enable_event
id|acpi_enable_event
(paren
id|u32
id|event
comma
id|u32
id|flags
)paren
(brace
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
id|u32
id|value
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;acpi_enable_event&quot;
)paren
suffix:semicolon
multiline_comment|/* Decode the Fixed Event */
r_if
c_cond
(paren
id|event
OG
id|ACPI_EVENT_MAX
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Enable the requested fixed event (by writing a one to the&n;&t; * enable register bit)&n;&t; */
id|status
op_assign
id|acpi_set_register
(paren
id|acpi_gbl_fixed_event_info
(braket
id|event
)braket
dot
id|enable_register_id
comma
l_int|1
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
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/* Make sure that the hardware responded */
id|status
op_assign
id|acpi_get_register
(paren
id|acpi_gbl_fixed_event_info
(braket
id|event
)braket
dot
id|enable_register_id
comma
op_amp
id|value
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
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|value
op_ne
l_int|1
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Could not enable %s event&bslash;n&quot;
comma
id|acpi_ut_get_event_name
(paren
id|event
)paren
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_NO_HARDWARE_RESPONSE
)paren
suffix:semicolon
)brace
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_enable_gpe&n; *&n; * PARAMETERS:  gpe_device      - Parent GPE Device&n; *              gpe_number      - GPE level within the GPE block&n; *              Flags           - Just enable, or also wake enable?&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Enable an ACPI event (general purpose)&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_enable_gpe
id|acpi_enable_gpe
(paren
id|acpi_handle
id|gpe_device
comma
id|u32
id|gpe_number
comma
id|u32
id|flags
)paren
(brace
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
r_struct
id|acpi_gpe_event_info
op_star
id|gpe_event_info
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;acpi_enable_gpe&quot;
)paren
suffix:semicolon
id|status
op_assign
id|acpi_ut_acquire_mutex
(paren
id|ACPI_MTX_EVENTS
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
multiline_comment|/* Ensure that we have a valid GPE number */
id|gpe_event_info
op_assign
id|acpi_ev_get_gpe_event_info
(paren
id|gpe_device
comma
id|gpe_number
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|gpe_event_info
)paren
(brace
id|status
op_assign
id|AE_BAD_PARAMETER
suffix:semicolon
r_goto
id|unlock_and_exit
suffix:semicolon
)brace
multiline_comment|/* Enable the requested GPE number */
id|status
op_assign
id|acpi_hw_enable_gpe
(paren
id|gpe_event_info
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
r_goto
id|unlock_and_exit
suffix:semicolon
)brace
r_if
c_cond
(paren
id|flags
op_amp
id|ACPI_EVENT_WAKE_ENABLE
)paren
(brace
id|acpi_hw_enable_gpe_for_wakeup
(paren
id|gpe_event_info
)paren
suffix:semicolon
)brace
id|unlock_and_exit
suffix:colon
(paren
r_void
)paren
id|acpi_ut_release_mutex
(paren
id|ACPI_MTX_EVENTS
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_disable_event&n; *&n; * PARAMETERS:  Event           - The fixed eventto be enabled&n; *              Flags           - Reserved&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Disable an ACPI event (fixed)&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_disable_event
id|acpi_disable_event
(paren
id|u32
id|event
comma
id|u32
id|flags
)paren
(brace
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
id|u32
id|value
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;acpi_disable_event&quot;
)paren
suffix:semicolon
multiline_comment|/* Decode the Fixed Event */
r_if
c_cond
(paren
id|event
OG
id|ACPI_EVENT_MAX
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Disable the requested fixed event (by writing a zero to the&n;&t; * enable register bit)&n;&t; */
id|status
op_assign
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
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
id|status
op_assign
id|acpi_get_register
(paren
id|acpi_gbl_fixed_event_info
(braket
id|event
)braket
dot
id|enable_register_id
comma
op_amp
id|value
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
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|value
op_ne
l_int|0
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Could not disable %s events&bslash;n&quot;
comma
id|acpi_ut_get_event_name
(paren
id|event
)paren
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_NO_HARDWARE_RESPONSE
)paren
suffix:semicolon
)brace
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_disable_gpe&n; *&n; * PARAMETERS:  gpe_device      - Parent GPE Device&n; *              gpe_number      - GPE level within the GPE block&n; *              Flags           - Just enable, or also wake enable?&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Disable an ACPI event (general purpose)&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_disable_gpe
id|acpi_disable_gpe
(paren
id|acpi_handle
id|gpe_device
comma
id|u32
id|gpe_number
comma
id|u32
id|flags
)paren
(brace
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
r_struct
id|acpi_gpe_event_info
op_star
id|gpe_event_info
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;acpi_disable_gpe&quot;
)paren
suffix:semicolon
id|status
op_assign
id|acpi_ut_acquire_mutex
(paren
id|ACPI_MTX_EVENTS
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
multiline_comment|/* Ensure that we have a valid GPE number */
id|gpe_event_info
op_assign
id|acpi_ev_get_gpe_event_info
(paren
id|gpe_device
comma
id|gpe_number
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|gpe_event_info
)paren
(brace
id|status
op_assign
id|AE_BAD_PARAMETER
suffix:semicolon
r_goto
id|unlock_and_exit
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Only disable the requested GPE number for wake if specified.&n;&t; * Otherwise, turn it totally off&n;&t; */
r_if
c_cond
(paren
id|flags
op_amp
id|ACPI_EVENT_WAKE_DISABLE
)paren
(brace
id|acpi_hw_disable_gpe_for_wakeup
(paren
id|gpe_event_info
)paren
suffix:semicolon
)brace
r_else
(brace
id|status
op_assign
id|acpi_hw_disable_gpe
(paren
id|gpe_event_info
)paren
suffix:semicolon
)brace
id|unlock_and_exit
suffix:colon
(paren
r_void
)paren
id|acpi_ut_release_mutex
(paren
id|ACPI_MTX_EVENTS
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_clear_event&n; *&n; * PARAMETERS:  Event           - The fixed event to be cleared&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Clear an ACPI event (fixed)&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_clear_event
id|acpi_clear_event
(paren
id|u32
id|event
)paren
(brace
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;acpi_clear_event&quot;
)paren
suffix:semicolon
multiline_comment|/* Decode the Fixed Event */
r_if
c_cond
(paren
id|event
OG
id|ACPI_EVENT_MAX
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Clear the requested fixed event (By writing a one to the&n;&t; * status register bit)&n;&t; */
id|status
op_assign
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
id|ACPI_MTX_LOCK
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_clear_gpe&n; *&n; * PARAMETERS:  gpe_device      - Parent GPE Device&n; *              gpe_number      - GPE level within the GPE block&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Clear an ACPI event (general purpose)&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_clear_gpe
id|acpi_clear_gpe
(paren
id|acpi_handle
id|gpe_device
comma
id|u32
id|gpe_number
)paren
(brace
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
r_struct
id|acpi_gpe_event_info
op_star
id|gpe_event_info
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;acpi_clear_gpe&quot;
)paren
suffix:semicolon
id|status
op_assign
id|acpi_ut_acquire_mutex
(paren
id|ACPI_MTX_EVENTS
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
multiline_comment|/* Ensure that we have a valid GPE number */
id|gpe_event_info
op_assign
id|acpi_ev_get_gpe_event_info
(paren
id|gpe_device
comma
id|gpe_number
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|gpe_event_info
)paren
(brace
id|status
op_assign
id|AE_BAD_PARAMETER
suffix:semicolon
r_goto
id|unlock_and_exit
suffix:semicolon
)brace
id|status
op_assign
id|acpi_hw_clear_gpe
(paren
id|gpe_event_info
)paren
suffix:semicolon
id|unlock_and_exit
suffix:colon
(paren
r_void
)paren
id|acpi_ut_release_mutex
(paren
id|ACPI_MTX_EVENTS
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_get_event_status&n; *&n; * PARAMETERS:  Event           - The fixed event&n; *              Event Status    - Where the current status of the event will&n; *                                be returned&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Obtains and returns the current status of the event&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_get_event_status
id|acpi_get_event_status
(paren
id|u32
id|event
comma
id|acpi_event_status
op_star
id|event_status
)paren
(brace
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;acpi_get_event_status&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|event_status
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
multiline_comment|/* Decode the Fixed Event */
r_if
c_cond
(paren
id|event
OG
id|ACPI_EVENT_MAX
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
multiline_comment|/* Get the status of the requested fixed event */
id|status
op_assign
id|acpi_get_register
(paren
id|acpi_gbl_fixed_event_info
(braket
id|event
)braket
dot
id|status_register_id
comma
id|event_status
comma
id|ACPI_MTX_LOCK
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_get_gpe_status&n; *&n; * PARAMETERS:  gpe_device      - Parent GPE Device&n; *              gpe_number      - GPE level within the GPE block&n; *              Event Status    - Where the current status of the event will&n; *                                be returned&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Get status of an event (general purpose)&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_get_gpe_status
id|acpi_get_gpe_status
(paren
id|acpi_handle
id|gpe_device
comma
id|u32
id|gpe_number
comma
id|acpi_event_status
op_star
id|event_status
)paren
(brace
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
r_struct
id|acpi_gpe_event_info
op_star
id|gpe_event_info
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;acpi_get_gpe_status&quot;
)paren
suffix:semicolon
id|status
op_assign
id|acpi_ut_acquire_mutex
(paren
id|ACPI_MTX_EVENTS
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
multiline_comment|/* Ensure that we have a valid GPE number */
id|gpe_event_info
op_assign
id|acpi_ev_get_gpe_event_info
(paren
id|gpe_device
comma
id|gpe_number
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|gpe_event_info
)paren
(brace
id|status
op_assign
id|AE_BAD_PARAMETER
suffix:semicolon
r_goto
id|unlock_and_exit
suffix:semicolon
)brace
multiline_comment|/* Obtain status on the requested GPE number */
id|status
op_assign
id|acpi_hw_get_gpe_status
(paren
id|gpe_event_info
comma
id|event_status
)paren
suffix:semicolon
id|unlock_and_exit
suffix:colon
(paren
r_void
)paren
id|acpi_ut_release_mutex
(paren
id|ACPI_MTX_EVENTS
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
eof
