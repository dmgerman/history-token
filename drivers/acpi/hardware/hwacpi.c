multiline_comment|/******************************************************************************&n; *&n; * Module Name: hwacpi - ACPI Hardware Initialization/Mode Interface&n; *              $Revision: 58 $&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000 - 2002, R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &quot;acpi.h&quot;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_HARDWARE
id|ACPI_MODULE_NAME
(paren
l_string|&quot;hwacpi&quot;
)paren
multiline_comment|/******************************************************************************&n; *&n; * FUNCTION:    Acpi_hw_initialize&n; *&n; * PARAMETERS:  None&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Initialize and validate various ACPI registers&n; *&n; ******************************************************************************/
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
l_string|&quot;Hw_initialize&quot;
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
multiline_comment|/******************************************************************************&n; *&n; * FUNCTION:    Acpi_hw_set_mode&n; *&n; * PARAMETERS:  Mode            - SYS_MODE_ACPI or SYS_MODE_LEGACY&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Transitions the system into the requested mode.&n; *&n; ******************************************************************************/
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
l_string|&quot;Hw_set_mode&quot;
)paren
suffix:semicolon
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
id|acpi_integer
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
id|acpi_integer
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
id|status
op_assign
id|AE_NO_HARDWARE_RESPONSE
suffix:semicolon
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
id|status
op_assign
id|AE_OK
suffix:semicolon
r_break
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
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/******************************************************************************&n; *&n; * FUNCTION:    Acpi_hw_get_mode&n; *&n; * PARAMETERS:  none&n; *&n; * RETURN:      SYS_MODE_ACPI or SYS_MODE_LEGACY&n; *&n; * DESCRIPTION: Return current operating state of system.  Determined by&n; *              querying the SCI_EN bit.&n; *&n; ******************************************************************************/
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
l_string|&quot;Hw_get_mode&quot;
)paren
suffix:semicolon
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
