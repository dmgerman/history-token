multiline_comment|/*******************************************************************************&n; *&n; * Module Name: hwregs - Read/write access functions for the various ACPI&n; *                       control and status registers.&n; *&n; ******************************************************************************/
multiline_comment|/*&n; * Copyright (C) 2000 - 2004, R. Byron Moore&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. Redistributions in binary form must reproduce at minimum a disclaimer&n; *    substantially similar to the &quot;NO WARRANTY&quot; disclaimer below&n; *    (&quot;Disclaimer&quot;) and any redistribution must be conditioned upon&n; *    including a substantially similar Disclaimer requirement for further&n; *    binary redistribution.&n; * 3. Neither the names of the above-listed copyright holders nor the names&n; *    of any contributors may be used to endorse or promote products derived&n; *    from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;) version 2 as published by the Free&n; * Software Foundation.&n; *&n; * NO WARRANTY&n; * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS&n; * &quot;AS IS&quot; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT&n; * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR&n; * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT&n; * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,&n; * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING&n; * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE&n; * POSSIBILITY OF SUCH DAMAGES.&n; */
macro_line|#include &lt;acpi/acpi.h&gt;
macro_line|#include &lt;acpi/acnamesp.h&gt;
macro_line|#include &lt;acpi/acevents.h&gt;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_HARDWARE
id|ACPI_MODULE_NAME
(paren
l_string|&quot;hwregs&quot;
)paren
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_hw_clear_acpi_status&n; *&n; * PARAMETERS:  Flags           - Lock the hardware or not&n; *&n; * RETURN:      none&n; *&n; * DESCRIPTION: Clears all fixed and general purpose status bits&n; *              THIS FUNCTION MUST BE CALLED WITH INTERRUPTS DISABLED&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_hw_clear_acpi_status
id|acpi_hw_clear_acpi_status
(paren
id|u32
id|flags
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;hw_clear_acpi_status&quot;
)paren
suffix:semicolon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_IO
comma
l_string|&quot;About to write %04X to %04X&bslash;n&quot;
comma
id|ACPI_BITMASK_ALL_FIXED_STATUS
comma
(paren
id|u16
)paren
id|acpi_gbl_FADT-&gt;xpm1a_evt_blk.address
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|ACPI_MTX_LOCK
)paren
(brace
id|status
op_assign
id|acpi_ut_acquire_mutex
(paren
id|ACPI_MTX_HARDWARE
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
id|status
op_assign
id|acpi_hw_register_write
(paren
id|ACPI_MTX_DO_NOT_LOCK
comma
id|ACPI_REGISTER_PM1_STATUS
comma
id|ACPI_BITMASK_ALL_FIXED_STATUS
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
multiline_comment|/* Clear the fixed events */
r_if
c_cond
(paren
id|acpi_gbl_FADT-&gt;xpm1b_evt_blk.address
)paren
(brace
id|status
op_assign
id|acpi_hw_low_level_write
(paren
l_int|16
comma
id|ACPI_BITMASK_ALL_FIXED_STATUS
comma
op_amp
id|acpi_gbl_FADT-&gt;xpm1b_evt_blk
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
)brace
multiline_comment|/* Clear the GPE Bits in all GPE registers in all GPE blocks */
id|status
op_assign
id|acpi_ev_walk_gpe_list
(paren
id|acpi_hw_clear_gpe_block
comma
id|ACPI_ISR
)paren
suffix:semicolon
id|unlock_and_exit
suffix:colon
r_if
c_cond
(paren
id|flags
op_amp
id|ACPI_MTX_LOCK
)paren
(brace
(paren
r_void
)paren
id|acpi_ut_release_mutex
(paren
id|ACPI_MTX_HARDWARE
)paren
suffix:semicolon
)brace
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_get_sleep_type_data&n; *&n; * PARAMETERS:  sleep_state         - Numeric sleep state&n; *              *sleep_type_a        - Where SLP_TYPa is returned&n; *              *sleep_type_b        - Where SLP_TYPb is returned&n; *&n; * RETURN:      Status - ACPI status&n; *&n; * DESCRIPTION: Obtain the SLP_TYPa and SLP_TYPb values for the requested sleep&n; *              state.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_get_sleep_type_data
id|acpi_get_sleep_type_data
(paren
id|u8
id|sleep_state
comma
id|u8
op_star
id|sleep_type_a
comma
id|u8
op_star
id|sleep_type_b
)paren
(brace
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
r_struct
id|acpi_parameter_info
id|info
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;acpi_get_sleep_type_data&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Validate parameters&n;&t; */
r_if
c_cond
(paren
(paren
id|sleep_state
OG
id|ACPI_S_STATES_MAX
)paren
op_logical_or
op_logical_neg
id|sleep_type_a
op_logical_or
op_logical_neg
id|sleep_type_b
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Evaluate the namespace object containing the values for this state&n;&t; */
id|info.parameters
op_assign
l_int|NULL
suffix:semicolon
id|status
op_assign
id|acpi_ns_evaluate_by_name
(paren
(paren
r_char
op_star
)paren
id|acpi_gbl_sleep_state_names
(braket
id|sleep_state
)braket
comma
op_amp
id|info
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
id|ACPI_DB_EXEC
comma
l_string|&quot;%s while evaluating sleep_state [%s]&bslash;n&quot;
comma
id|acpi_format_exception
(paren
id|status
)paren
comma
id|acpi_gbl_sleep_state_names
(braket
id|sleep_state
)braket
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/* Must have a return object */
r_if
c_cond
(paren
op_logical_neg
id|info.return_object
)paren
(brace
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;Missing Sleep State object&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|status
op_assign
id|AE_NOT_EXIST
suffix:semicolon
)brace
multiline_comment|/* It must be of type Package */
r_else
r_if
c_cond
(paren
id|ACPI_GET_OBJECT_TYPE
(paren
id|info.return_object
)paren
op_ne
id|ACPI_TYPE_PACKAGE
)paren
(brace
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;Sleep State object not a Package&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|status
op_assign
id|AE_AML_OPERAND_TYPE
suffix:semicolon
)brace
multiline_comment|/* The package must have at least two elements */
r_else
r_if
c_cond
(paren
id|info.return_object-&gt;package.count
OL
l_int|2
)paren
(brace
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;Sleep State package does not have at least two elements&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|status
op_assign
id|AE_AML_NO_OPERAND
suffix:semicolon
)brace
multiline_comment|/* The first two elements must both be of type Integer */
r_else
r_if
c_cond
(paren
(paren
id|ACPI_GET_OBJECT_TYPE
(paren
id|info.return_object-&gt;package.elements
(braket
l_int|0
)braket
)paren
op_ne
id|ACPI_TYPE_INTEGER
)paren
op_logical_or
(paren
id|ACPI_GET_OBJECT_TYPE
(paren
id|info.return_object-&gt;package.elements
(braket
l_int|1
)braket
)paren
op_ne
id|ACPI_TYPE_INTEGER
)paren
)paren
(brace
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;Sleep State package elements are not both Integers (%s, %s)&bslash;n&quot;
comma
id|acpi_ut_get_object_type_name
(paren
id|info.return_object-&gt;package.elements
(braket
l_int|0
)braket
)paren
comma
id|acpi_ut_get_object_type_name
(paren
id|info.return_object-&gt;package.elements
(braket
l_int|1
)braket
)paren
)paren
)paren
suffix:semicolon
id|status
op_assign
id|AE_AML_OPERAND_TYPE
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t; * Valid _Sx_ package size, type, and value&n;&t;&t; */
op_star
id|sleep_type_a
op_assign
(paren
id|u8
)paren
(paren
id|info.return_object-&gt;package.elements
(braket
l_int|0
)braket
)paren
op_member_access_from_pointer
id|integer.value
suffix:semicolon
op_star
id|sleep_type_b
op_assign
(paren
id|u8
)paren
(paren
id|info.return_object-&gt;package.elements
(braket
l_int|1
)braket
)paren
op_member_access_from_pointer
id|integer.value
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
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;While evaluating sleep_state [%s], bad Sleep object %p type %s&bslash;n&quot;
comma
id|acpi_gbl_sleep_state_names
(braket
id|sleep_state
)braket
comma
id|info.return_object
comma
id|acpi_ut_get_object_type_name
(paren
id|info.return_object
)paren
)paren
)paren
suffix:semicolon
)brace
id|acpi_ut_remove_reference
(paren
id|info.return_object
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_hw_get_register_bit_mask&n; *&n; * PARAMETERS:  register_id         - Index of ACPI Register to access&n; *&n; * RETURN:      The bit mask to be used when accessing the register&n; *&n; * DESCRIPTION: Map register_id into a register bit mask.&n; *&n; ******************************************************************************/
r_struct
id|acpi_bit_register_info
op_star
DECL|function|acpi_hw_get_bit_register_info
id|acpi_hw_get_bit_register_info
(paren
id|u32
id|register_id
)paren
(brace
id|ACPI_FUNCTION_NAME
(paren
l_string|&quot;hw_get_bit_register_info&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|register_id
OG
id|ACPI_BITREG_MAX
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Invalid bit_register ID: %X&bslash;n&quot;
comma
id|register_id
)paren
)paren
suffix:semicolon
r_return
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
r_return
(paren
op_amp
id|acpi_gbl_bit_register_info
(braket
id|register_id
)braket
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_get_register&n; *&n; * PARAMETERS:  register_id     - ID of ACPI bit_register to access&n; *              return_value    - Value that was read from the register&n; *              Flags           - Lock the hardware or not&n; *&n; * RETURN:      Status and the value read from specified Register.  Value&n; *              returned is normalized to bit0 (is shifted all the way right)&n; *&n; * DESCRIPTION: ACPI bit_register read function.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_get_register
id|acpi_get_register
(paren
id|u32
id|register_id
comma
id|u32
op_star
id|return_value
comma
id|u32
id|flags
)paren
(brace
id|u32
id|register_value
op_assign
l_int|0
suffix:semicolon
r_struct
id|acpi_bit_register_info
op_star
id|bit_reg_info
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;acpi_get_register&quot;
)paren
suffix:semicolon
multiline_comment|/* Get the info structure corresponding to the requested ACPI Register */
id|bit_reg_info
op_assign
id|acpi_hw_get_bit_register_info
(paren
id|register_id
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bit_reg_info
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|flags
op_amp
id|ACPI_MTX_LOCK
)paren
(brace
id|status
op_assign
id|acpi_ut_acquire_mutex
(paren
id|ACPI_MTX_HARDWARE
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
multiline_comment|/* Read from the register */
id|status
op_assign
id|acpi_hw_register_read
(paren
id|ACPI_MTX_DO_NOT_LOCK
comma
id|bit_reg_info-&gt;parent_register
comma
op_amp
id|register_value
)paren
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|ACPI_MTX_LOCK
)paren
(brace
(paren
r_void
)paren
id|acpi_ut_release_mutex
(paren
id|ACPI_MTX_HARDWARE
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ACPI_SUCCESS
(paren
id|status
)paren
)paren
(brace
multiline_comment|/* Normalize the value that was read */
id|register_value
op_assign
(paren
(paren
id|register_value
op_amp
id|bit_reg_info-&gt;access_bit_mask
)paren
op_rshift
id|bit_reg_info-&gt;bit_position
)paren
suffix:semicolon
op_star
id|return_value
op_assign
id|register_value
suffix:semicolon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_IO
comma
l_string|&quot;Read value %8.8X register %X&bslash;n&quot;
comma
id|register_value
comma
id|bit_reg_info-&gt;parent_register
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
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_set_register&n; *&n; * PARAMETERS:  register_id     - ID of ACPI bit_register to access&n; *              Value           - (only used on write) value to write to the&n; *                                Register, NOT pre-normalized to the bit pos&n; *              Flags           - Lock the hardware or not&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: ACPI Bit Register write function.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_set_register
id|acpi_set_register
(paren
id|u32
id|register_id
comma
id|u32
id|value
comma
id|u32
id|flags
)paren
(brace
id|u32
id|register_value
op_assign
l_int|0
suffix:semicolon
r_struct
id|acpi_bit_register_info
op_star
id|bit_reg_info
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_TRACE_U32
(paren
l_string|&quot;acpi_set_register&quot;
comma
id|register_id
)paren
suffix:semicolon
multiline_comment|/* Get the info structure corresponding to the requested ACPI Register */
id|bit_reg_info
op_assign
id|acpi_hw_get_bit_register_info
(paren
id|register_id
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bit_reg_info
)paren
(brace
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;Bad ACPI HW register_id: %X&bslash;n&quot;
comma
id|register_id
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|flags
op_amp
id|ACPI_MTX_LOCK
)paren
(brace
id|status
op_assign
id|acpi_ut_acquire_mutex
(paren
id|ACPI_MTX_HARDWARE
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
multiline_comment|/* Always do a register read first so we can insert the new bits  */
id|status
op_assign
id|acpi_hw_register_read
(paren
id|ACPI_MTX_DO_NOT_LOCK
comma
id|bit_reg_info-&gt;parent_register
comma
op_amp
id|register_value
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
multiline_comment|/*&n;&t; * Decode the Register ID&n;&t; * Register ID = [Register block ID] | [bit ID]&n;&t; *&n;&t; * Check bit ID to fine locate Register offset.&n;&t; * Check Mask to determine Register offset, and then read-write.&n;&t; */
r_switch
c_cond
(paren
id|bit_reg_info-&gt;parent_register
)paren
(brace
r_case
id|ACPI_REGISTER_PM1_STATUS
suffix:colon
multiline_comment|/*&n;&t;&t; * Status Registers are different from the rest.  Clear by&n;&t;&t; * writing 1, and writing 0 has no effect.  So, the only relevant&n;&t;&t; * information is the single bit we&squot;re interested in, all others should&n;&t;&t; * be written as 0 so they will be left unchanged.&n;&t;&t; */
id|value
op_assign
id|ACPI_REGISTER_PREPARE_BITS
(paren
id|value
comma
id|bit_reg_info-&gt;bit_position
comma
id|bit_reg_info-&gt;access_bit_mask
)paren
suffix:semicolon
r_if
c_cond
(paren
id|value
)paren
(brace
id|status
op_assign
id|acpi_hw_register_write
(paren
id|ACPI_MTX_DO_NOT_LOCK
comma
id|ACPI_REGISTER_PM1_STATUS
comma
(paren
id|u16
)paren
id|value
)paren
suffix:semicolon
id|register_value
op_assign
l_int|0
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|ACPI_REGISTER_PM1_ENABLE
suffix:colon
id|ACPI_REGISTER_INSERT_VALUE
(paren
id|register_value
comma
id|bit_reg_info-&gt;bit_position
comma
id|bit_reg_info-&gt;access_bit_mask
comma
id|value
)paren
suffix:semicolon
id|status
op_assign
id|acpi_hw_register_write
(paren
id|ACPI_MTX_DO_NOT_LOCK
comma
id|ACPI_REGISTER_PM1_ENABLE
comma
(paren
id|u16
)paren
id|register_value
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_REGISTER_PM1_CONTROL
suffix:colon
multiline_comment|/*&n;&t;&t; * Write the PM1 Control register.&n;&t;&t; * Note that at this level, the fact that there are actually TWO&n;&t;&t; * registers (A and B - and B may not exist) is abstracted.&n;&t;&t; */
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_IO
comma
l_string|&quot;PM1 control: Read %X&bslash;n&quot;
comma
id|register_value
)paren
)paren
suffix:semicolon
id|ACPI_REGISTER_INSERT_VALUE
(paren
id|register_value
comma
id|bit_reg_info-&gt;bit_position
comma
id|bit_reg_info-&gt;access_bit_mask
comma
id|value
)paren
suffix:semicolon
id|status
op_assign
id|acpi_hw_register_write
(paren
id|ACPI_MTX_DO_NOT_LOCK
comma
id|ACPI_REGISTER_PM1_CONTROL
comma
(paren
id|u16
)paren
id|register_value
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_REGISTER_PM2_CONTROL
suffix:colon
id|status
op_assign
id|acpi_hw_register_read
(paren
id|ACPI_MTX_DO_NOT_LOCK
comma
id|ACPI_REGISTER_PM2_CONTROL
comma
op_amp
id|register_value
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
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_IO
comma
l_string|&quot;PM2 control: Read %X from %8.8X%8.8X&bslash;n&quot;
comma
id|register_value
comma
id|ACPI_FORMAT_UINT64
(paren
id|acpi_gbl_FADT-&gt;xpm2_cnt_blk.address
)paren
)paren
)paren
suffix:semicolon
id|ACPI_REGISTER_INSERT_VALUE
(paren
id|register_value
comma
id|bit_reg_info-&gt;bit_position
comma
id|bit_reg_info-&gt;access_bit_mask
comma
id|value
)paren
suffix:semicolon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_IO
comma
l_string|&quot;About to write %4.4X to %8.8X%8.8X&bslash;n&quot;
comma
id|register_value
comma
id|ACPI_FORMAT_UINT64
(paren
id|acpi_gbl_FADT-&gt;xpm2_cnt_blk.address
)paren
)paren
)paren
suffix:semicolon
id|status
op_assign
id|acpi_hw_register_write
(paren
id|ACPI_MTX_DO_NOT_LOCK
comma
id|ACPI_REGISTER_PM2_CONTROL
comma
(paren
id|u8
)paren
(paren
id|register_value
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
id|unlock_and_exit
suffix:colon
r_if
c_cond
(paren
id|flags
op_amp
id|ACPI_MTX_LOCK
)paren
(brace
(paren
r_void
)paren
id|acpi_ut_release_mutex
(paren
id|ACPI_MTX_HARDWARE
)paren
suffix:semicolon
)brace
multiline_comment|/* Normalize the value that was read */
id|ACPI_DEBUG_EXEC
(paren
id|register_value
op_assign
(paren
(paren
id|register_value
op_amp
id|bit_reg_info-&gt;access_bit_mask
)paren
op_rshift
id|bit_reg_info-&gt;bit_position
)paren
)paren
suffix:semicolon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_IO
comma
l_string|&quot;Set bits: %8.8X actual %8.8X register %X&bslash;n&quot;
comma
id|value
comma
id|register_value
comma
id|bit_reg_info-&gt;parent_register
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/******************************************************************************&n; *&n; * FUNCTION:    acpi_hw_register_read&n; *&n; * PARAMETERS:  use_lock            - Mutex hw access&n; *              register_id         - register_iD + Offset&n; *              return_value        - Value that was read from the register&n; *&n; * RETURN:      Status and the value read.&n; *&n; * DESCRIPTION: Acpi register read function.  Registers are read at the&n; *              given offset.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_hw_register_read
id|acpi_hw_register_read
(paren
id|u8
id|use_lock
comma
id|u32
id|register_id
comma
id|u32
op_star
id|return_value
)paren
(brace
id|u32
id|value1
op_assign
l_int|0
suffix:semicolon
id|u32
id|value2
op_assign
l_int|0
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;hw_register_read&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_MTX_LOCK
op_eq
id|use_lock
)paren
(brace
id|status
op_assign
id|acpi_ut_acquire_mutex
(paren
id|ACPI_MTX_HARDWARE
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
r_switch
c_cond
(paren
id|register_id
)paren
(brace
r_case
id|ACPI_REGISTER_PM1_STATUS
suffix:colon
multiline_comment|/* 16-bit access */
id|status
op_assign
id|acpi_hw_low_level_read
(paren
l_int|16
comma
op_amp
id|value1
comma
op_amp
id|acpi_gbl_FADT-&gt;xpm1a_evt_blk
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
multiline_comment|/* PM1B is optional */
id|status
op_assign
id|acpi_hw_low_level_read
(paren
l_int|16
comma
op_amp
id|value2
comma
op_amp
id|acpi_gbl_FADT-&gt;xpm1b_evt_blk
)paren
suffix:semicolon
id|value1
op_or_assign
id|value2
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_REGISTER_PM1_ENABLE
suffix:colon
multiline_comment|/* 16-bit access */
id|status
op_assign
id|acpi_hw_low_level_read
(paren
l_int|16
comma
op_amp
id|value1
comma
op_amp
id|acpi_gbl_xpm1a_enable
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
multiline_comment|/* PM1B is optional */
id|status
op_assign
id|acpi_hw_low_level_read
(paren
l_int|16
comma
op_amp
id|value2
comma
op_amp
id|acpi_gbl_xpm1b_enable
)paren
suffix:semicolon
id|value1
op_or_assign
id|value2
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_REGISTER_PM1_CONTROL
suffix:colon
multiline_comment|/* 16-bit access */
id|status
op_assign
id|acpi_hw_low_level_read
(paren
l_int|16
comma
op_amp
id|value1
comma
op_amp
id|acpi_gbl_FADT-&gt;xpm1a_cnt_blk
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
id|status
op_assign
id|acpi_hw_low_level_read
(paren
l_int|16
comma
op_amp
id|value2
comma
op_amp
id|acpi_gbl_FADT-&gt;xpm1b_cnt_blk
)paren
suffix:semicolon
id|value1
op_or_assign
id|value2
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_REGISTER_PM2_CONTROL
suffix:colon
multiline_comment|/* 8-bit access */
id|status
op_assign
id|acpi_hw_low_level_read
(paren
l_int|8
comma
op_amp
id|value1
comma
op_amp
id|acpi_gbl_FADT-&gt;xpm2_cnt_blk
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_REGISTER_PM_TIMER
suffix:colon
multiline_comment|/* 32-bit access */
id|status
op_assign
id|acpi_hw_low_level_read
(paren
l_int|32
comma
op_amp
id|value1
comma
op_amp
id|acpi_gbl_FADT-&gt;xpm_tmr_blk
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_REGISTER_SMI_COMMAND_BLOCK
suffix:colon
multiline_comment|/* 8-bit access */
id|status
op_assign
id|acpi_os_read_port
(paren
id|acpi_gbl_FADT-&gt;smi_cmd
comma
op_amp
id|value1
comma
l_int|8
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Unknown Register ID: %X&bslash;n&quot;
comma
id|register_id
)paren
)paren
suffix:semicolon
id|status
op_assign
id|AE_BAD_PARAMETER
suffix:semicolon
r_break
suffix:semicolon
)brace
id|unlock_and_exit
suffix:colon
r_if
c_cond
(paren
id|ACPI_MTX_LOCK
op_eq
id|use_lock
)paren
(brace
(paren
r_void
)paren
id|acpi_ut_release_mutex
(paren
id|ACPI_MTX_HARDWARE
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ACPI_SUCCESS
(paren
id|status
)paren
)paren
(brace
op_star
id|return_value
op_assign
id|value1
suffix:semicolon
)brace
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/******************************************************************************&n; *&n; * FUNCTION:    acpi_hw_register_write&n; *&n; * PARAMETERS:  use_lock            - Mutex hw access&n; *              register_id         - register_iD + Offset&n; *              Value               - The value to write&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Acpi register Write function.  Registers are written at the&n; *              given offset.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_hw_register_write
id|acpi_hw_register_write
(paren
id|u8
id|use_lock
comma
id|u32
id|register_id
comma
id|u32
id|value
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;hw_register_write&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_MTX_LOCK
op_eq
id|use_lock
)paren
(brace
id|status
op_assign
id|acpi_ut_acquire_mutex
(paren
id|ACPI_MTX_HARDWARE
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
r_switch
c_cond
(paren
id|register_id
)paren
(brace
r_case
id|ACPI_REGISTER_PM1_STATUS
suffix:colon
multiline_comment|/* 16-bit access */
id|status
op_assign
id|acpi_hw_low_level_write
(paren
l_int|16
comma
id|value
comma
op_amp
id|acpi_gbl_FADT-&gt;xpm1a_evt_blk
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
multiline_comment|/* PM1B is optional */
id|status
op_assign
id|acpi_hw_low_level_write
(paren
l_int|16
comma
id|value
comma
op_amp
id|acpi_gbl_FADT-&gt;xpm1b_evt_blk
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_REGISTER_PM1_ENABLE
suffix:colon
multiline_comment|/* 16-bit access*/
id|status
op_assign
id|acpi_hw_low_level_write
(paren
l_int|16
comma
id|value
comma
op_amp
id|acpi_gbl_xpm1a_enable
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
multiline_comment|/* PM1B is optional */
id|status
op_assign
id|acpi_hw_low_level_write
(paren
l_int|16
comma
id|value
comma
op_amp
id|acpi_gbl_xpm1b_enable
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_REGISTER_PM1_CONTROL
suffix:colon
multiline_comment|/* 16-bit access */
id|status
op_assign
id|acpi_hw_low_level_write
(paren
l_int|16
comma
id|value
comma
op_amp
id|acpi_gbl_FADT-&gt;xpm1a_cnt_blk
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
id|status
op_assign
id|acpi_hw_low_level_write
(paren
l_int|16
comma
id|value
comma
op_amp
id|acpi_gbl_FADT-&gt;xpm1b_cnt_blk
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_REGISTER_PM1A_CONTROL
suffix:colon
multiline_comment|/* 16-bit access */
id|status
op_assign
id|acpi_hw_low_level_write
(paren
l_int|16
comma
id|value
comma
op_amp
id|acpi_gbl_FADT-&gt;xpm1a_cnt_blk
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_REGISTER_PM1B_CONTROL
suffix:colon
multiline_comment|/* 16-bit access */
id|status
op_assign
id|acpi_hw_low_level_write
(paren
l_int|16
comma
id|value
comma
op_amp
id|acpi_gbl_FADT-&gt;xpm1b_cnt_blk
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_REGISTER_PM2_CONTROL
suffix:colon
multiline_comment|/* 8-bit access */
id|status
op_assign
id|acpi_hw_low_level_write
(paren
l_int|8
comma
id|value
comma
op_amp
id|acpi_gbl_FADT-&gt;xpm2_cnt_blk
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_REGISTER_PM_TIMER
suffix:colon
multiline_comment|/* 32-bit access */
id|status
op_assign
id|acpi_hw_low_level_write
(paren
l_int|32
comma
id|value
comma
op_amp
id|acpi_gbl_FADT-&gt;xpm_tmr_blk
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_REGISTER_SMI_COMMAND_BLOCK
suffix:colon
multiline_comment|/* 8-bit access */
multiline_comment|/* SMI_CMD is currently always in IO space */
id|status
op_assign
id|acpi_os_write_port
(paren
id|acpi_gbl_FADT-&gt;smi_cmd
comma
id|value
comma
l_int|8
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|status
op_assign
id|AE_BAD_PARAMETER
suffix:semicolon
r_break
suffix:semicolon
)brace
id|unlock_and_exit
suffix:colon
r_if
c_cond
(paren
id|ACPI_MTX_LOCK
op_eq
id|use_lock
)paren
(brace
(paren
r_void
)paren
id|acpi_ut_release_mutex
(paren
id|ACPI_MTX_HARDWARE
)paren
suffix:semicolon
)brace
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/******************************************************************************&n; *&n; * FUNCTION:    acpi_hw_low_level_read&n; *&n; * PARAMETERS:  Width               - 8, 16, or 32&n; *              Value               - Where the value is returned&n; *              Reg                 - GAS register structure&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Read from either memory or IO space.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_hw_low_level_read
id|acpi_hw_low_level_read
(paren
id|u32
id|width
comma
id|u32
op_star
id|value
comma
r_struct
id|acpi_generic_address
op_star
id|reg
)paren
(brace
id|u64
id|address
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_NAME
(paren
l_string|&quot;hw_low_level_read&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Must have a valid pointer to a GAS structure, and&n;&t; * a non-zero address within. However, don&squot;t return an error&n;&t; * because the PM1A/B code must not fail if B isn&squot;t present.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|reg
)paren
(brace
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/* Get a local copy of the address.  Handles possible alignment issues */
id|ACPI_MOVE_64_TO_64
(paren
op_amp
id|address
comma
op_amp
id|reg-&gt;address
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|address
)paren
(brace
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
op_star
id|value
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * Two address spaces supported: Memory or IO.&n;&t; * PCI_Config is not supported here because the GAS struct is insufficient&n;&t; */
r_switch
c_cond
(paren
id|reg-&gt;address_space_id
)paren
(brace
r_case
id|ACPI_ADR_SPACE_SYSTEM_MEMORY
suffix:colon
id|status
op_assign
id|acpi_os_read_memory
(paren
(paren
id|acpi_physical_address
)paren
id|address
comma
id|value
comma
id|width
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_ADR_SPACE_SYSTEM_IO
suffix:colon
id|status
op_assign
id|acpi_os_read_port
(paren
(paren
id|acpi_io_address
)paren
id|address
comma
id|value
comma
id|width
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Unsupported address space: %X&bslash;n&quot;
comma
id|reg-&gt;address_space_id
)paren
)paren
suffix:semicolon
r_return
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_IO
comma
l_string|&quot;Read:  %8.8X width %2d from %8.8X%8.8X (%s)&bslash;n&quot;
comma
op_star
id|value
comma
id|width
comma
id|ACPI_FORMAT_UINT64
(paren
id|address
)paren
comma
id|acpi_ut_get_region_name
(paren
id|reg-&gt;address_space_id
)paren
)paren
)paren
suffix:semicolon
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/******************************************************************************&n; *&n; * FUNCTION:    acpi_hw_low_level_write&n; *&n; * PARAMETERS:  Width               - 8, 16, or 32&n; *              Value               - To be written&n; *              Reg                 - GAS register structure&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Write to either memory or IO space.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_hw_low_level_write
id|acpi_hw_low_level_write
(paren
id|u32
id|width
comma
id|u32
id|value
comma
r_struct
id|acpi_generic_address
op_star
id|reg
)paren
(brace
id|u64
id|address
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_NAME
(paren
l_string|&quot;hw_low_level_write&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Must have a valid pointer to a GAS structure, and&n;&t; * a non-zero address within. However, don&squot;t return an error&n;&t; * because the PM1A/B code must not fail if B isn&squot;t present.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|reg
)paren
(brace
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/* Get a local copy of the address.  Handles possible alignment issues */
id|ACPI_MOVE_64_TO_64
(paren
op_amp
id|address
comma
op_amp
id|reg-&gt;address
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|address
)paren
(brace
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Two address spaces supported: Memory or IO.&n;&t; * PCI_Config is not supported here because the GAS struct is insufficient&n;&t; */
r_switch
c_cond
(paren
id|reg-&gt;address_space_id
)paren
(brace
r_case
id|ACPI_ADR_SPACE_SYSTEM_MEMORY
suffix:colon
id|status
op_assign
id|acpi_os_write_memory
(paren
(paren
id|acpi_physical_address
)paren
id|address
comma
id|value
comma
id|width
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_ADR_SPACE_SYSTEM_IO
suffix:colon
id|status
op_assign
id|acpi_os_write_port
(paren
(paren
id|acpi_io_address
)paren
id|address
comma
id|value
comma
id|width
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Unsupported address space: %X&bslash;n&quot;
comma
id|reg-&gt;address_space_id
)paren
)paren
suffix:semicolon
r_return
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_IO
comma
l_string|&quot;Wrote: %8.8X width %2d   to %8.8X%8.8X (%s)&bslash;n&quot;
comma
id|value
comma
id|width
comma
id|ACPI_FORMAT_UINT64
(paren
id|address
)paren
comma
id|acpi_ut_get_region_name
(paren
id|reg-&gt;address_space_id
)paren
)paren
)paren
suffix:semicolon
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
eof
