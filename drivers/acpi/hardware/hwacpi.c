multiline_comment|/******************************************************************************&n; *&n; * Module Name: hwacpi - ACPI Hardware Initialization/Mode Interface&n; *&n; *****************************************************************************/
multiline_comment|/*&n; * Copyright (C) 2000 - 2004, R. Byron Moore&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. Redistributions in binary form must reproduce at minimum a disclaimer&n; *    substantially similar to the &quot;NO WARRANTY&quot; disclaimer below&n; *    (&quot;Disclaimer&quot;) and any redistribution must be conditioned upon&n; *    including a substantially similar Disclaimer requirement for further&n; *    binary redistribution.&n; * 3. Neither the names of the above-listed copyright holders nor the names&n; *    of any contributors may be used to endorse or promote products derived&n; *    from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;) version 2 as published by the Free&n; * Software Foundation.&n; *&n; * NO WARRANTY&n; * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS&n; * &quot;AS IS&quot; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT&n; * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR&n; * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT&n; * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,&n; * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING&n; * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE&n; * POSSIBILITY OF SUCH DAMAGES.&n; */
macro_line|#include &lt;acpi/acpi.h&gt;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_HARDWARE
id|ACPI_MODULE_NAME
(paren
l_string|&quot;hwacpi&quot;
)paren
multiline_comment|/******************************************************************************&n; *&n; * FUNCTION:    acpi_hw_initialize&n; *&n; * PARAMETERS:  None&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Initialize and validate various ACPI registers&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_hw_initialize
id|acpi_hw_initialize
(paren
r_void
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;hw_initialize&quot;
)paren
suffix:semicolon
multiline_comment|/* We must have the ACPI tables by the time we get here */
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
id|ACPI_DB_ERROR
comma
l_string|&quot;A FADT is not loaded&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_NO_ACPI_TABLES
)paren
suffix:semicolon
)brace
multiline_comment|/* Sanity check the FADT for valid values */
id|status
op_assign
id|acpi_ut_validate_fadt
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
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/******************************************************************************&n; *&n; * FUNCTION:    acpi_hw_set_mode&n; *&n; * PARAMETERS:  Mode            - SYS_MODE_ACPI or SYS_MODE_LEGACY&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Transitions the system into the requested mode.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_hw_set_mode
id|acpi_hw_set_mode
(paren
id|u32
id|mode
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
id|u32
id|retry
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;hw_set_mode&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * ACPI 2.0 clarified that if SMI_CMD in FADT is zero,&n;&t; * system does not support mode transition.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|acpi_gbl_FADT-&gt;smi_cmd
)paren
(brace
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;No SMI_CMD in FADT, mode transition failed.&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_NO_HARDWARE_RESPONSE
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * ACPI 2.0 clarified the meaning of ACPI_ENABLE and ACPI_DISABLE&n;&t; * in FADT: If it is zero, enabling or disabling is not supported.&n;&t; * As old systems may have used zero for mode transition,&n;&t; * we make sure both the numbers are zero to determine these&n;&t; * transitions are not supported.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|acpi_gbl_FADT-&gt;acpi_enable
op_logical_and
op_logical_neg
id|acpi_gbl_FADT-&gt;acpi_disable
)paren
(brace
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;No ACPI mode transition supported in this system (enable/disable both zero)&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|mode
)paren
(brace
r_case
id|ACPI_SYS_MODE_ACPI
suffix:colon
multiline_comment|/* BIOS should have disabled ALL fixed and GP events */
id|status
op_assign
id|acpi_os_write_port
(paren
id|acpi_gbl_FADT-&gt;smi_cmd
comma
(paren
id|u32
)paren
id|acpi_gbl_FADT-&gt;acpi_enable
comma
l_int|8
)paren
suffix:semicolon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;Attempting to enable ACPI mode&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_SYS_MODE_LEGACY
suffix:colon
multiline_comment|/*&n;&t;&t; * BIOS should clear all fixed status bits and restore fixed event&n;&t;&t; * enable bits to default&n;&t;&t; */
id|status
op_assign
id|acpi_os_write_port
(paren
id|acpi_gbl_FADT-&gt;smi_cmd
comma
(paren
id|u32
)paren
id|acpi_gbl_FADT-&gt;acpi_disable
comma
l_int|8
)paren
suffix:semicolon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;Attempting to enable Legacy (non-ACPI) mode&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|return_ACPI_STATUS
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
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
l_string|&quot;Could not write mode change, %s&bslash;n&quot;
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
multiline_comment|/*&n;&t; * Some hardware takes a LONG time to switch modes. Give them 3 sec to&n;&t; * do so, but allow faster systems to proceed more quickly.&n;&t; */
id|retry
op_assign
l_int|3000
suffix:semicolon
r_while
c_loop
(paren
id|retry
)paren
(brace
r_if
c_cond
(paren
id|acpi_hw_get_mode
c_func
(paren
)paren
op_eq
id|mode
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;Mode %X successfully enabled&bslash;n&quot;
comma
id|mode
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
id|acpi_os_stall
c_func
(paren
l_int|1000
)paren
suffix:semicolon
id|retry
op_decrement
suffix:semicolon
)brace
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;Hardware never changed modes&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_NO_HARDWARE_RESPONSE
)paren
suffix:semicolon
)brace
multiline_comment|/******************************************************************************&n; *&n; * FUNCTION:    acpi_hw_get_mode&n; *&n; * PARAMETERS:  none&n; *&n; * RETURN:      SYS_MODE_ACPI or SYS_MODE_LEGACY&n; *&n; * DESCRIPTION: Return current operating state of system.  Determined by&n; *              querying the SCI_EN bit.&n; *&n; ******************************************************************************/
id|u32
DECL|function|acpi_hw_get_mode
id|acpi_hw_get_mode
(paren
r_void
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
id|u32
id|value
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;hw_get_mode&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * ACPI 2.0 clarified that if SMI_CMD in FADT is zero,&n;&t; * system does not support mode transition.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|acpi_gbl_FADT-&gt;smi_cmd
)paren
(brace
id|return_VALUE
(paren
id|ACPI_SYS_MODE_ACPI
)paren
suffix:semicolon
)brace
id|status
op_assign
id|acpi_get_register
(paren
id|ACPI_BITREG_SCI_ENABLE
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
id|return_VALUE
(paren
id|ACPI_SYS_MODE_LEGACY
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|value
)paren
(brace
id|return_VALUE
(paren
id|ACPI_SYS_MODE_ACPI
)paren
suffix:semicolon
)brace
r_else
(brace
id|return_VALUE
(paren
id|ACPI_SYS_MODE_LEGACY
)paren
suffix:semicolon
)brace
)brace
eof
