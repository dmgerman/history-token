multiline_comment|/******************************************************************************&n; *&n; * Module Name: evgpe - General Purpose Event handling and dispatch&n; *&n; *****************************************************************************/
multiline_comment|/*&n; * Copyright (C) 2000 - 2004, R. Byron Moore&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. Redistributions in binary form must reproduce at minimum a disclaimer&n; *    substantially similar to the &quot;NO WARRANTY&quot; disclaimer below&n; *    (&quot;Disclaimer&quot;) and any redistribution must be conditioned upon&n; *    including a substantially similar Disclaimer requirement for further&n; *    binary redistribution.&n; * 3. Neither the names of the above-listed copyright holders nor the names&n; *    of any contributors may be used to endorse or promote products derived&n; *    from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;) version 2 as published by the Free&n; * Software Foundation.&n; *&n; * NO WARRANTY&n; * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS&n; * &quot;AS IS&quot; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT&n; * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR&n; * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT&n; * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,&n; * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING&n; * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE&n; * POSSIBILITY OF SUCH DAMAGES.&n; */
macro_line|#include &lt;acpi/acpi.h&gt;
macro_line|#include &lt;acpi/acevents.h&gt;
macro_line|#include &lt;acpi/acnamesp.h&gt;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_EVENTS
id|ACPI_MODULE_NAME
(paren
l_string|&quot;evgpe&quot;
)paren
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ev_set_gpe_type&n; *&n; * PARAMETERS:  gpe_event_info          - GPE to set&n; *              Type                    - New type&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Sets the new type for the GPE (wake, run, or wake/run)&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ev_set_gpe_type
id|acpi_ev_set_gpe_type
(paren
r_struct
id|acpi_gpe_event_info
op_star
id|gpe_event_info
comma
id|u8
id|type
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ev_set_gpe_type&quot;
)paren
suffix:semicolon
multiline_comment|/* Validate type and update register enable masks */
r_switch
c_cond
(paren
id|type
)paren
(brace
r_case
id|ACPI_GPE_TYPE_WAKE
suffix:colon
r_case
id|ACPI_GPE_TYPE_RUNTIME
suffix:colon
r_case
id|ACPI_GPE_TYPE_WAKE_RUN
suffix:colon
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
multiline_comment|/* Disable the GPE if currently enabled */
id|status
op_assign
id|acpi_ev_disable_gpe
(paren
id|gpe_event_info
)paren
suffix:semicolon
multiline_comment|/* Type was validated above */
id|gpe_event_info-&gt;flags
op_and_assign
op_complement
id|ACPI_GPE_TYPE_MASK
suffix:semicolon
multiline_comment|/* Clear type bits */
id|gpe_event_info-&gt;flags
op_or_assign
id|type
suffix:semicolon
multiline_comment|/* Insert type */
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ev_update_gpe_enable_masks&n; *&n; * PARAMETERS:  gpe_event_info          - GPE to update&n; *              Type                    - What to do: ACPI_GPE_DISABLE or&n; *                                        ACPI_GPE_ENABLE&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Updates GPE register enable masks based on the GPE type&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ev_update_gpe_enable_masks
id|acpi_ev_update_gpe_enable_masks
(paren
r_struct
id|acpi_gpe_event_info
op_star
id|gpe_event_info
comma
id|u8
id|type
)paren
(brace
r_struct
id|acpi_gpe_register_info
op_star
id|gpe_register_info
suffix:semicolon
id|u8
id|register_bit
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ev_update_gpe_enable_masks&quot;
)paren
suffix:semicolon
id|gpe_register_info
op_assign
id|gpe_event_info-&gt;register_info
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|gpe_register_info
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_NOT_EXIST
)paren
suffix:semicolon
)brace
id|register_bit
op_assign
id|gpe_event_info-&gt;register_bit
suffix:semicolon
multiline_comment|/* 1) Disable case.  Simply clear all enable bits */
r_if
c_cond
(paren
id|type
op_eq
id|ACPI_GPE_DISABLE
)paren
(brace
id|ACPI_CLEAR_BIT
(paren
id|gpe_register_info-&gt;enable_for_wake
comma
id|register_bit
)paren
suffix:semicolon
id|ACPI_CLEAR_BIT
(paren
id|gpe_register_info-&gt;enable_for_run
comma
id|register_bit
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/* 2) Enable case.  Set/Clear the appropriate enable bits */
r_switch
c_cond
(paren
id|gpe_event_info-&gt;flags
op_amp
id|ACPI_GPE_TYPE_MASK
)paren
(brace
r_case
id|ACPI_GPE_TYPE_WAKE
suffix:colon
id|ACPI_SET_BIT
(paren
id|gpe_register_info-&gt;enable_for_wake
comma
id|register_bit
)paren
suffix:semicolon
id|ACPI_CLEAR_BIT
(paren
id|gpe_register_info-&gt;enable_for_run
comma
id|register_bit
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_GPE_TYPE_RUNTIME
suffix:colon
id|ACPI_CLEAR_BIT
(paren
id|gpe_register_info-&gt;enable_for_wake
comma
id|register_bit
)paren
suffix:semicolon
id|ACPI_SET_BIT
(paren
id|gpe_register_info-&gt;enable_for_run
comma
id|register_bit
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_GPE_TYPE_WAKE_RUN
suffix:colon
id|ACPI_SET_BIT
(paren
id|gpe_register_info-&gt;enable_for_wake
comma
id|register_bit
)paren
suffix:semicolon
id|ACPI_SET_BIT
(paren
id|gpe_register_info-&gt;enable_for_run
comma
id|register_bit
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
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ev_enable_gpe&n; *&n; * PARAMETERS:  gpe_event_info          - GPE to enable&n; *              write_to_hardware       - Enable now, or just mark data structs&n; *                                        (WAKE GPEs should be deferred)&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Enable a GPE based on the GPE type&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ev_enable_gpe
id|acpi_ev_enable_gpe
(paren
r_struct
id|acpi_gpe_event_info
op_star
id|gpe_event_info
comma
id|u8
id|write_to_hardware
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ev_enable_gpe&quot;
)paren
suffix:semicolon
multiline_comment|/* Make sure HW enable masks are updated */
id|status
op_assign
id|acpi_ev_update_gpe_enable_masks
(paren
id|gpe_event_info
comma
id|ACPI_GPE_ENABLE
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
multiline_comment|/* Mark wake-enabled or HW enable, or both */
r_switch
c_cond
(paren
id|gpe_event_info-&gt;flags
op_amp
id|ACPI_GPE_TYPE_MASK
)paren
(brace
r_case
id|ACPI_GPE_TYPE_WAKE
suffix:colon
id|ACPI_SET_BIT
(paren
id|gpe_event_info-&gt;flags
comma
id|ACPI_GPE_WAKE_ENABLED
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_GPE_TYPE_WAKE_RUN
suffix:colon
id|ACPI_SET_BIT
(paren
id|gpe_event_info-&gt;flags
comma
id|ACPI_GPE_WAKE_ENABLED
)paren
suffix:semicolon
multiline_comment|/*lint -fallthrough */
r_case
id|ACPI_GPE_TYPE_RUNTIME
suffix:colon
id|ACPI_SET_BIT
(paren
id|gpe_event_info-&gt;flags
comma
id|ACPI_GPE_RUN_ENABLED
)paren
suffix:semicolon
r_if
c_cond
(paren
id|write_to_hardware
)paren
(brace
multiline_comment|/* Clear the GPE (of stale events), then enable it */
id|status
op_assign
id|acpi_hw_clear_gpe
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
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/* Enable the requested runtime GPE */
id|status
op_assign
id|acpi_hw_write_gpe_enable_reg
(paren
id|gpe_event_info
)paren
suffix:semicolon
)brace
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
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ev_disable_gpe&n; *&n; * PARAMETERS:  gpe_event_info          - GPE to disable&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Disable a GPE based on the GPE type&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ev_disable_gpe
id|acpi_ev_disable_gpe
(paren
r_struct
id|acpi_gpe_event_info
op_star
id|gpe_event_info
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ev_disable_gpe&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|gpe_event_info-&gt;flags
op_amp
id|ACPI_GPE_ENABLE_MASK
)paren
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/* Make sure HW enable masks are updated */
id|status
op_assign
id|acpi_ev_update_gpe_enable_masks
(paren
id|gpe_event_info
comma
id|ACPI_GPE_DISABLE
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
multiline_comment|/* Mark wake-disabled or HW disable, or both */
r_switch
c_cond
(paren
id|gpe_event_info-&gt;flags
op_amp
id|ACPI_GPE_TYPE_MASK
)paren
(brace
r_case
id|ACPI_GPE_TYPE_WAKE
suffix:colon
id|ACPI_CLEAR_BIT
(paren
id|gpe_event_info-&gt;flags
comma
id|ACPI_GPE_WAKE_ENABLED
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_GPE_TYPE_WAKE_RUN
suffix:colon
id|ACPI_CLEAR_BIT
(paren
id|gpe_event_info-&gt;flags
comma
id|ACPI_GPE_WAKE_ENABLED
)paren
suffix:semicolon
multiline_comment|/*lint -fallthrough */
r_case
id|ACPI_GPE_TYPE_RUNTIME
suffix:colon
multiline_comment|/* Disable the requested runtime GPE */
id|ACPI_CLEAR_BIT
(paren
id|gpe_event_info-&gt;flags
comma
id|ACPI_GPE_RUN_ENABLED
)paren
suffix:semicolon
id|status
op_assign
id|acpi_hw_write_gpe_enable_reg
(paren
id|gpe_event_info
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
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ev_get_gpe_event_info&n; *&n; * PARAMETERS:  gpe_device          - Device node.  NULL for GPE0/GPE1&n; *              gpe_number          - Raw GPE number&n; *&n; * RETURN:      A GPE event_info struct. NULL if not a valid GPE&n; *&n; * DESCRIPTION: Returns the event_info struct associated with this GPE.&n; *              Validates the gpe_block and the gpe_number&n; *&n; *              Should be called only when the GPE lists are semaphore locked&n; *              and not subject to change.&n; *&n; ******************************************************************************/
r_struct
id|acpi_gpe_event_info
op_star
DECL|function|acpi_ev_get_gpe_event_info
id|acpi_ev_get_gpe_event_info
(paren
id|acpi_handle
id|gpe_device
comma
id|u32
id|gpe_number
)paren
(brace
r_union
id|acpi_operand_object
op_star
id|obj_desc
suffix:semicolon
r_struct
id|acpi_gpe_block_info
op_star
id|gpe_block
suffix:semicolon
id|acpi_native_uint
id|i
suffix:semicolon
id|ACPI_FUNCTION_ENTRY
(paren
)paren
suffix:semicolon
multiline_comment|/* A NULL gpe_block means use the FADT-defined GPE block(s) */
r_if
c_cond
(paren
op_logical_neg
id|gpe_device
)paren
(brace
multiline_comment|/* Examine GPE Block 0 and 1 (These blocks are permanent) */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|ACPI_MAX_GPE_BLOCKS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|gpe_block
op_assign
id|acpi_gbl_gpe_fadt_blocks
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|gpe_block
)paren
(brace
r_if
c_cond
(paren
(paren
id|gpe_number
op_ge
id|gpe_block-&gt;block_base_number
)paren
op_logical_and
(paren
id|gpe_number
OL
id|gpe_block-&gt;block_base_number
op_plus
(paren
id|gpe_block-&gt;register_count
op_star
l_int|8
)paren
)paren
)paren
(brace
r_return
(paren
op_amp
id|gpe_block-&gt;event_info
(braket
id|gpe_number
op_minus
id|gpe_block-&gt;block_base_number
)braket
)paren
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/* The gpe_number was not in the range of either FADT GPE block */
r_return
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
multiline_comment|/* A Non-NULL gpe_device means this is a GPE Block Device */
id|obj_desc
op_assign
id|acpi_ns_get_attached_object
(paren
(paren
r_struct
id|acpi_namespace_node
op_star
)paren
id|gpe_device
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|obj_desc
op_logical_or
op_logical_neg
id|obj_desc-&gt;device.gpe_block
)paren
(brace
r_return
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
id|gpe_block
op_assign
id|obj_desc-&gt;device.gpe_block
suffix:semicolon
r_if
c_cond
(paren
(paren
id|gpe_number
op_ge
id|gpe_block-&gt;block_base_number
)paren
op_logical_and
(paren
id|gpe_number
OL
id|gpe_block-&gt;block_base_number
op_plus
(paren
id|gpe_block-&gt;register_count
op_star
l_int|8
)paren
)paren
)paren
(brace
r_return
(paren
op_amp
id|gpe_block-&gt;event_info
(braket
id|gpe_number
op_minus
id|gpe_block-&gt;block_base_number
)braket
)paren
suffix:semicolon
)brace
r_return
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ev_gpe_detect&n; *&n; * PARAMETERS:  gpe_xrupt_list      - Interrupt block for this interrupt.&n; *                                    Can have multiple GPE blocks attached.&n; *&n; * RETURN:      INTERRUPT_HANDLED or INTERRUPT_NOT_HANDLED&n; *&n; * DESCRIPTION: Detect if any GP events have occurred.  This function is&n; *              executed at interrupt level.&n; *&n; ******************************************************************************/
id|u32
DECL|function|acpi_ev_gpe_detect
id|acpi_ev_gpe_detect
(paren
r_struct
id|acpi_gpe_xrupt_info
op_star
id|gpe_xrupt_list
)paren
(brace
id|u32
id|int_status
op_assign
id|ACPI_INTERRUPT_NOT_HANDLED
suffix:semicolon
id|u8
id|enabled_status_byte
suffix:semicolon
r_struct
id|acpi_gpe_register_info
op_star
id|gpe_register_info
suffix:semicolon
id|u32
id|status_reg
suffix:semicolon
id|u32
id|enable_reg
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
r_struct
id|acpi_gpe_block_info
op_star
id|gpe_block
suffix:semicolon
id|acpi_native_uint
id|i
suffix:semicolon
id|acpi_native_uint
id|j
suffix:semicolon
id|ACPI_FUNCTION_NAME
(paren
l_string|&quot;ev_gpe_detect&quot;
)paren
suffix:semicolon
multiline_comment|/* Check for the case where there are no GPEs */
r_if
c_cond
(paren
op_logical_neg
id|gpe_xrupt_list
)paren
(brace
r_return
(paren
id|int_status
)paren
suffix:semicolon
)brace
multiline_comment|/* Examine all GPE blocks attached to this interrupt level */
id|acpi_os_acquire_lock
(paren
id|acpi_gbl_gpe_lock
comma
id|ACPI_ISR
)paren
suffix:semicolon
id|gpe_block
op_assign
id|gpe_xrupt_list-&gt;gpe_block_list_head
suffix:semicolon
r_while
c_loop
(paren
id|gpe_block
)paren
(brace
multiline_comment|/*&n;&t;&t; * Read all of the 8-bit GPE status and enable registers&n;&t;&t; * in this GPE block, saving all of them.&n;&t;&t; * Find all currently active GP events.&n;&t;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|gpe_block-&gt;register_count
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/* Get the next status/enable pair */
id|gpe_register_info
op_assign
op_amp
id|gpe_block-&gt;register_info
(braket
id|i
)braket
suffix:semicolon
multiline_comment|/* Read the Status Register */
id|status
op_assign
id|acpi_hw_low_level_read
(paren
id|ACPI_GPE_REGISTER_WIDTH
comma
op_amp
id|status_reg
comma
op_amp
id|gpe_register_info-&gt;status_address
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
multiline_comment|/* Read the Enable Register */
id|status
op_assign
id|acpi_hw_low_level_read
(paren
id|ACPI_GPE_REGISTER_WIDTH
comma
op_amp
id|enable_reg
comma
op_amp
id|gpe_register_info-&gt;enable_address
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
id|ACPI_DB_INTERRUPTS
comma
l_string|&quot;GPE pair: Status %8.8X%8.8X = %02X, Enable %8.8X%8.8X = %02X&bslash;n&quot;
comma
id|ACPI_FORMAT_UINT64
(paren
id|gpe_register_info-&gt;status_address.address
)paren
comma
id|status_reg
comma
id|ACPI_FORMAT_UINT64
(paren
id|gpe_register_info-&gt;enable_address.address
)paren
comma
id|enable_reg
)paren
)paren
suffix:semicolon
multiline_comment|/* First check if there is anything active at all in this register */
id|enabled_status_byte
op_assign
(paren
id|u8
)paren
(paren
id|status_reg
op_amp
id|enable_reg
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|enabled_status_byte
)paren
(brace
multiline_comment|/* No active GPEs in this register, move on */
r_continue
suffix:semicolon
)brace
multiline_comment|/* Now look at the individual GPEs in this byte register */
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|ACPI_GPE_REGISTER_WIDTH
suffix:semicolon
id|j
op_increment
)paren
(brace
multiline_comment|/* Examine one GPE bit */
r_if
c_cond
(paren
id|enabled_status_byte
op_amp
id|acpi_gbl_decode_to8bit
(braket
id|j
)braket
)paren
(brace
multiline_comment|/*&n;&t;&t;&t;&t;&t; * Found an active GPE. Dispatch the event to a handler&n;&t;&t;&t;&t;&t; * or method.&n;&t;&t;&t;&t;&t; */
id|int_status
op_or_assign
id|acpi_ev_gpe_dispatch
(paren
op_amp
id|gpe_block-&gt;event_info
(braket
(paren
id|i
op_star
id|ACPI_GPE_REGISTER_WIDTH
)paren
op_plus
id|j
)braket
comma
(paren
id|u32
)paren
id|j
op_plus
id|gpe_register_info-&gt;base_gpe_number
)paren
suffix:semicolon
)brace
)brace
)brace
id|gpe_block
op_assign
id|gpe_block-&gt;next
suffix:semicolon
)brace
id|unlock_and_exit
suffix:colon
id|acpi_os_release_lock
(paren
id|acpi_gbl_gpe_lock
comma
id|ACPI_ISR
)paren
suffix:semicolon
r_return
(paren
id|int_status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ev_asynch_execute_gpe_method&n; *&n; * PARAMETERS:  Context (gpe_event_info) - Info for this GPE&n; *&n; * RETURN:      None&n; *&n; * DESCRIPTION: Perform the actual execution of a GPE control method.  This&n; *              function is called from an invocation of acpi_os_queue_for_execution&n; *              (and therefore does NOT execute at interrupt level) so that&n; *              the control method itself is not executed in the context of&n; *              an interrupt handler.&n; *&n; ******************************************************************************/
r_static
r_void
id|ACPI_SYSTEM_XFACE
DECL|function|acpi_ev_asynch_execute_gpe_method
id|acpi_ev_asynch_execute_gpe_method
(paren
r_void
op_star
id|context
)paren
(brace
r_struct
id|acpi_gpe_event_info
op_star
id|gpe_event_info
op_assign
(paren
r_void
op_star
)paren
id|context
suffix:semicolon
id|u32
id|gpe_number
op_assign
l_int|0
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
r_struct
id|acpi_gpe_event_info
id|local_gpe_event_info
suffix:semicolon
r_struct
id|acpi_parameter_info
id|info
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ev_asynch_execute_gpe_method&quot;
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
id|return_VOID
suffix:semicolon
)brace
multiline_comment|/* Must revalidate the gpe_number/gpe_block */
r_if
c_cond
(paren
op_logical_neg
id|acpi_ev_valid_gpe_event
(paren
id|gpe_event_info
)paren
)paren
(brace
id|status
op_assign
id|acpi_ut_release_mutex
(paren
id|ACPI_MTX_EVENTS
)paren
suffix:semicolon
id|return_VOID
suffix:semicolon
)brace
multiline_comment|/* Set the GPE flags for return to enabled state */
(paren
r_void
)paren
id|acpi_ev_enable_gpe
(paren
id|gpe_event_info
comma
id|FALSE
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Take a snapshot of the GPE info for this level - we copy the&n;&t; * info to prevent a race condition with remove_handler/remove_block.&n;&t; */
id|ACPI_MEMCPY
(paren
op_amp
id|local_gpe_event_info
comma
id|gpe_event_info
comma
r_sizeof
(paren
r_struct
id|acpi_gpe_event_info
)paren
)paren
suffix:semicolon
id|status
op_assign
id|acpi_ut_release_mutex
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
id|return_VOID
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Must check for control method type dispatch one more&n;&t; * time to avoid race with ev_gpe_install_handler&n;&t; */
r_if
c_cond
(paren
(paren
id|local_gpe_event_info.flags
op_amp
id|ACPI_GPE_DISPATCH_MASK
)paren
op_eq
id|ACPI_GPE_DISPATCH_METHOD
)paren
(brace
multiline_comment|/*&n;&t;&t; * Invoke the GPE Method (_Lxx, _Exx) i.e., evaluate the _Lxx/_Exx&n;&t;&t; * control method that corresponds to this GPE&n;&t;&t; */
id|info.node
op_assign
id|local_gpe_event_info.dispatch.method_node
suffix:semicolon
id|info.parameters
op_assign
id|ACPI_CAST_PTR
(paren
r_union
id|acpi_operand_object
op_star
comma
id|gpe_event_info
)paren
suffix:semicolon
id|info.parameter_type
op_assign
id|ACPI_PARAM_GPE
suffix:semicolon
id|status
op_assign
id|acpi_ns_evaluate_by_handle
(paren
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
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;%s while evaluating method [%4.4s] for GPE[%2X]&bslash;n&quot;
comma
id|acpi_format_exception
(paren
id|status
)paren
comma
id|acpi_ut_get_node_name
(paren
id|local_gpe_event_info.dispatch.method_node
)paren
comma
id|gpe_number
)paren
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
(paren
id|local_gpe_event_info.flags
op_amp
id|ACPI_GPE_XRUPT_TYPE_MASK
)paren
op_eq
id|ACPI_GPE_LEVEL_TRIGGERED
)paren
(brace
multiline_comment|/*&n;&t;&t; * GPE is level-triggered, we clear the GPE status bit after&n;&t;&t; * handling the event.&n;&t;&t; */
id|status
op_assign
id|acpi_hw_clear_gpe
(paren
op_amp
id|local_gpe_event_info
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
id|return_VOID
suffix:semicolon
)brace
)brace
multiline_comment|/* Enable this GPE */
(paren
r_void
)paren
id|acpi_hw_write_gpe_enable_reg
(paren
op_amp
id|local_gpe_event_info
)paren
suffix:semicolon
id|return_VOID
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ev_gpe_dispatch&n; *&n; * PARAMETERS:  gpe_event_info  - info for this GPE&n; *              gpe_number      - Number relative to the parent GPE block&n; *&n; * RETURN:      INTERRUPT_HANDLED or INTERRUPT_NOT_HANDLED&n; *&n; * DESCRIPTION: Dispatch a General Purpose Event to either a function (e.g. EC)&n; *              or method (e.g. _Lxx/_Exx) handler.&n; *&n; *              This function executes at interrupt level.&n; *&n; ******************************************************************************/
id|u32
DECL|function|acpi_ev_gpe_dispatch
id|acpi_ev_gpe_dispatch
(paren
r_struct
id|acpi_gpe_event_info
op_star
id|gpe_event_info
comma
id|u32
id|gpe_number
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ev_gpe_dispatch&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * If edge-triggered, clear the GPE status bit now.  Note that&n;&t; * level-triggered events are cleared after the GPE is serviced.&n;&t; */
r_if
c_cond
(paren
(paren
id|gpe_event_info-&gt;flags
op_amp
id|ACPI_GPE_XRUPT_TYPE_MASK
)paren
op_eq
id|ACPI_GPE_EDGE_TRIGGERED
)paren
(brace
id|status
op_assign
id|acpi_hw_clear_gpe
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
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;acpi_ev_gpe_dispatch: Unable to clear GPE[%2X]&bslash;n&quot;
comma
id|gpe_number
)paren
)paren
suffix:semicolon
id|return_VALUE
(paren
id|ACPI_INTERRUPT_NOT_HANDLED
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Save current system state */
r_if
c_cond
(paren
id|acpi_gbl_system_awake_and_running
)paren
(brace
id|ACPI_SET_BIT
(paren
id|gpe_event_info-&gt;flags
comma
id|ACPI_GPE_SYSTEM_RUNNING
)paren
suffix:semicolon
)brace
r_else
(brace
id|ACPI_CLEAR_BIT
(paren
id|gpe_event_info-&gt;flags
comma
id|ACPI_GPE_SYSTEM_RUNNING
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Dispatch the GPE to either an installed handler, or the control&n;&t; * method associated with this GPE (_Lxx or _Exx).&n;&t; * If a handler exists, we invoke it and do not attempt to run the method.&n;&t; * If there is neither a handler nor a method, we disable the level to&n;&t; * prevent further events from coming in here.&n;&t; */
r_switch
c_cond
(paren
id|gpe_event_info-&gt;flags
op_amp
id|ACPI_GPE_DISPATCH_MASK
)paren
(brace
r_case
id|ACPI_GPE_DISPATCH_HANDLER
suffix:colon
multiline_comment|/*&n;&t;&t; * Invoke the installed handler (at interrupt level)&n;&t;&t; * Ignore return status for now.  TBD: leave GPE disabled on error?&n;&t;&t; */
(paren
r_void
)paren
id|gpe_event_info-&gt;dispatch.handler-&gt;address
(paren
id|gpe_event_info-&gt;dispatch.handler-&gt;context
)paren
suffix:semicolon
multiline_comment|/* It is now safe to clear level-triggered events. */
r_if
c_cond
(paren
(paren
id|gpe_event_info-&gt;flags
op_amp
id|ACPI_GPE_XRUPT_TYPE_MASK
)paren
op_eq
id|ACPI_GPE_LEVEL_TRIGGERED
)paren
(brace
id|status
op_assign
id|acpi_hw_clear_gpe
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
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;acpi_ev_gpe_dispatch: Unable to clear GPE[%2X]&bslash;n&quot;
comma
id|gpe_number
)paren
)paren
suffix:semicolon
id|return_VALUE
(paren
id|ACPI_INTERRUPT_NOT_HANDLED
)paren
suffix:semicolon
)brace
)brace
r_break
suffix:semicolon
r_case
id|ACPI_GPE_DISPATCH_METHOD
suffix:colon
multiline_comment|/*&n;&t;&t; * Disable GPE, so it doesn&squot;t keep firing before the method has a&n;&t;&t; * chance to run.&n;&t;&t; */
id|status
op_assign
id|acpi_ev_disable_gpe
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
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;acpi_ev_gpe_dispatch: Unable to disable GPE[%2X]&bslash;n&quot;
comma
id|gpe_number
)paren
)paren
suffix:semicolon
id|return_VALUE
(paren
id|ACPI_INTERRUPT_NOT_HANDLED
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Execute the method associated with the GPE&n;&t;&t; * NOTE: Level-triggered GPEs are cleared after the method completes.&n;&t;&t; */
r_if
c_cond
(paren
id|ACPI_FAILURE
(paren
id|acpi_os_queue_for_execution
(paren
id|OSD_PRIORITY_GPE
comma
id|acpi_ev_asynch_execute_gpe_method
comma
id|gpe_event_info
)paren
)paren
)paren
(brace
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;acpi_ev_gpe_dispatch: Unable to queue handler for GPE[%2X], event is disabled&bslash;n&quot;
comma
id|gpe_number
)paren
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* No handler or method to run! */
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;acpi_ev_gpe_dispatch: No handler or method for GPE[%2X], disabling event&bslash;n&quot;
comma
id|gpe_number
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Disable the GPE.  The GPE will remain disabled until the ACPI&n;&t;&t; * Core Subsystem is restarted, or a handler is installed.&n;&t;&t; */
id|status
op_assign
id|acpi_ev_disable_gpe
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
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;acpi_ev_gpe_dispatch: Unable to disable GPE[%2X]&bslash;n&quot;
comma
id|gpe_number
)paren
)paren
suffix:semicolon
id|return_VALUE
(paren
id|ACPI_INTERRUPT_NOT_HANDLED
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
id|return_VALUE
(paren
id|ACPI_INTERRUPT_HANDLED
)paren
suffix:semicolon
)brace
macro_line|#ifdef ACPI_GPE_NOTIFY_CHECK
multiline_comment|/*******************************************************************************&n; * TBD: NOT USED, PROTOTYPE ONLY AND WILL PROBABLY BE REMOVED&n; *&n; * FUNCTION:    acpi_ev_check_for_wake_only_gpe&n; *&n; * PARAMETERS:  gpe_event_info  - info for this GPE&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Determine if a a GPE is &quot;wake-only&quot;.&n; *&n; *              Called from Notify() code in interpreter when a &quot;device_wake&quot;&n; *              Notify comes in.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ev_check_for_wake_only_gpe
id|acpi_ev_check_for_wake_only_gpe
(paren
r_struct
id|acpi_gpe_event_info
op_star
id|gpe_event_info
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ev_check_for_wake_only_gpe&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|gpe_event_info
)paren
op_logical_and
multiline_comment|/* Only &gt;0 for _Lxx/_Exx */
(paren
(paren
id|gpe_event_info-&gt;flags
op_amp
id|ACPI_GPE_SYSTEM_MASK
)paren
op_eq
id|ACPI_GPE_SYSTEM_RUNNING
)paren
)paren
multiline_comment|/* System state at GPE time */
(brace
multiline_comment|/* This must be a wake-only GPE, disable it */
id|status
op_assign
id|acpi_ev_disable_gpe
(paren
id|gpe_event_info
)paren
suffix:semicolon
multiline_comment|/* Set GPE to wake-only.  Do not change wake disabled/enabled status */
id|acpi_ev_set_gpe_type
(paren
id|gpe_event_info
comma
id|ACPI_GPE_TYPE_WAKE
)paren
suffix:semicolon
id|ACPI_REPORT_INFO
(paren
(paren
l_string|&quot;GPE %p was updated from wake/run to wake-only&bslash;n&quot;
comma
id|gpe_event_info
)paren
)paren
suffix:semicolon
multiline_comment|/* This was a wake-only GPE */
id|return_ACPI_STATUS
(paren
id|AE_WAKE_ONLY_GPE
)paren
suffix:semicolon
)brace
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
