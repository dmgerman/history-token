multiline_comment|/******************************************************************************&n; *&n; * Module Name: hwgpe - Low level GPE enable/disable/clear functions&n; *&n; *****************************************************************************/
multiline_comment|/*&n; * Copyright (C) 2000 - 2004, R. Byron Moore&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. Redistributions in binary form must reproduce at minimum a disclaimer&n; *    substantially similar to the &quot;NO WARRANTY&quot; disclaimer below&n; *    (&quot;Disclaimer&quot;) and any redistribution must be conditioned upon&n; *    including a substantially similar Disclaimer requirement for further&n; *    binary redistribution.&n; * 3. Neither the names of the above-listed copyright holders nor the names&n; *    of any contributors may be used to endorse or promote products derived&n; *    from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;) version 2 as published by the Free&n; * Software Foundation.&n; *&n; * NO WARRANTY&n; * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS&n; * &quot;AS IS&quot; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT&n; * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR&n; * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT&n; * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,&n; * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING&n; * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE&n; * POSSIBILITY OF SUCH DAMAGES.&n; */
macro_line|#include &lt;acpi/acpi.h&gt;
macro_line|#include &lt;acpi/acevents.h&gt;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_HARDWARE
id|ACPI_MODULE_NAME
(paren
l_string|&quot;hwgpe&quot;
)paren
multiline_comment|/******************************************************************************&n; *&n; * FUNCTION:    acpi_hw_enable_gpe&n; *&n; * PARAMETERS:  gpe_number      - The GPE&n; *&n; * RETURN:      None&n; *&n; * DESCRIPTION: Enable a single GPE.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_hw_enable_gpe
id|acpi_hw_enable_gpe
(paren
r_struct
id|acpi_gpe_event_info
op_star
id|gpe_event_info
)paren
(brace
id|u32
id|in_byte
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_ENTRY
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Read the current value of the register, set the appropriate bit&n;&t; * to enable the GPE, and write out the new register.&n;&t; */
id|status
op_assign
id|acpi_hw_low_level_read
(paren
l_int|8
comma
op_amp
id|in_byte
comma
op_amp
id|gpe_event_info-&gt;register_info-&gt;enable_address
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
multiline_comment|/* Write with the new GPE bit enabled */
id|status
op_assign
id|acpi_hw_low_level_write
(paren
l_int|8
comma
(paren
id|in_byte
op_or
id|gpe_event_info-&gt;bit_mask
)paren
comma
op_amp
id|gpe_event_info-&gt;register_info-&gt;enable_address
)paren
suffix:semicolon
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/******************************************************************************&n; *&n; * FUNCTION:    acpi_hw_enable_gpe_for_wakeup&n; *&n; * PARAMETERS:  gpe_number      - The GPE&n; *&n; * RETURN:      None&n; *&n; * DESCRIPTION: Keep track of which GPEs the OS has requested not be&n; *              disabled when going to sleep.&n; *&n; ******************************************************************************/
r_void
DECL|function|acpi_hw_enable_gpe_for_wakeup
id|acpi_hw_enable_gpe_for_wakeup
(paren
r_struct
id|acpi_gpe_event_info
op_star
id|gpe_event_info
)paren
(brace
r_struct
id|acpi_gpe_register_info
op_star
id|gpe_register_info
suffix:semicolon
id|ACPI_FUNCTION_ENTRY
(paren
)paren
suffix:semicolon
multiline_comment|/* Get the info block for the entire GPE register */
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
r_return
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Set the bit so we will not disable this when sleeping&n;&t; */
id|gpe_register_info-&gt;wake_enable
op_or_assign
id|gpe_event_info-&gt;bit_mask
suffix:semicolon
)brace
multiline_comment|/******************************************************************************&n; *&n; * FUNCTION:    acpi_hw_disable_gpe&n; *&n; * PARAMETERS:  gpe_number      - The GPE&n; *&n; * RETURN:      None&n; *&n; * DESCRIPTION: Disable a single GPE.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_hw_disable_gpe
id|acpi_hw_disable_gpe
(paren
r_struct
id|acpi_gpe_event_info
op_star
id|gpe_event_info
)paren
(brace
id|u32
id|in_byte
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
r_struct
id|acpi_gpe_register_info
op_star
id|gpe_register_info
suffix:semicolon
id|ACPI_FUNCTION_ENTRY
(paren
)paren
suffix:semicolon
multiline_comment|/* Get the info block for the entire GPE register */
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
r_return
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Read the current value of the register, clear the appropriate bit,&n;&t; * and write out the new register value to disable the GPE.&n;&t; */
id|status
op_assign
id|acpi_hw_low_level_read
(paren
l_int|8
comma
op_amp
id|in_byte
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
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/* Write the byte with this GPE bit cleared */
id|status
op_assign
id|acpi_hw_low_level_write
(paren
l_int|8
comma
(paren
id|in_byte
op_amp
op_complement
(paren
id|gpe_event_info-&gt;bit_mask
)paren
)paren
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
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
id|acpi_hw_disable_gpe_for_wakeup
(paren
id|gpe_event_info
)paren
suffix:semicolon
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/******************************************************************************&n; *&n; * FUNCTION:    acpi_hw_disable_gpe_for_wakeup&n; *&n; * PARAMETERS:  gpe_number      - The GPE&n; *&n; * RETURN:      None&n; *&n; * DESCRIPTION: Keep track of which GPEs the OS has requested not be&n; *              disabled when going to sleep.&n; *&n; ******************************************************************************/
r_void
DECL|function|acpi_hw_disable_gpe_for_wakeup
id|acpi_hw_disable_gpe_for_wakeup
(paren
r_struct
id|acpi_gpe_event_info
op_star
id|gpe_event_info
)paren
(brace
r_struct
id|acpi_gpe_register_info
op_star
id|gpe_register_info
suffix:semicolon
id|ACPI_FUNCTION_ENTRY
(paren
)paren
suffix:semicolon
multiline_comment|/* Get the info block for the entire GPE register */
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
r_return
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Clear the bit so we will disable this when sleeping&n;&t; */
id|gpe_register_info-&gt;wake_enable
op_and_assign
op_complement
(paren
id|gpe_event_info-&gt;bit_mask
)paren
suffix:semicolon
)brace
multiline_comment|/******************************************************************************&n; *&n; * FUNCTION:    acpi_hw_clear_gpe&n; *&n; * PARAMETERS:  gpe_number      - The GPE&n; *&n; * RETURN:      None&n; *&n; * DESCRIPTION: Clear a single GPE.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_hw_clear_gpe
id|acpi_hw_clear_gpe
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
id|ACPI_FUNCTION_ENTRY
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Write a one to the appropriate bit in the status register to&n;&t; * clear this GPE.&n;&t; */
id|status
op_assign
id|acpi_hw_low_level_write
(paren
l_int|8
comma
id|gpe_event_info-&gt;bit_mask
comma
op_amp
id|gpe_event_info-&gt;register_info-&gt;status_address
)paren
suffix:semicolon
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/******************************************************************************&n; *&n; * FUNCTION:    acpi_hw_get_gpe_status&n; *&n; * PARAMETERS:  gpe_number      - The GPE&n; *&n; * RETURN:      None&n; *&n; * DESCRIPTION: Return the status of a single GPE.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_hw_get_gpe_status
id|acpi_hw_get_gpe_status
(paren
r_struct
id|acpi_gpe_event_info
op_star
id|gpe_event_info
comma
id|acpi_event_status
op_star
id|event_status
)paren
(brace
id|u32
id|in_byte
suffix:semicolon
id|u8
id|bit_mask
suffix:semicolon
r_struct
id|acpi_gpe_register_info
op_star
id|gpe_register_info
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
id|acpi_event_status
id|local_event_status
op_assign
l_int|0
suffix:semicolon
id|ACPI_FUNCTION_ENTRY
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|event_status
)paren
(brace
r_return
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
multiline_comment|/* Get the info block for the entire GPE register */
id|gpe_register_info
op_assign
id|gpe_event_info-&gt;register_info
suffix:semicolon
multiline_comment|/* Get the register bitmask for this GPE */
id|bit_mask
op_assign
id|gpe_event_info-&gt;bit_mask
suffix:semicolon
multiline_comment|/* GPE Enabled? */
id|status
op_assign
id|acpi_hw_low_level_read
(paren
l_int|8
comma
op_amp
id|in_byte
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
r_if
c_cond
(paren
id|bit_mask
op_amp
id|in_byte
)paren
(brace
id|local_event_status
op_or_assign
id|ACPI_EVENT_FLAG_ENABLED
suffix:semicolon
)brace
multiline_comment|/* GPE Enabled for wake? */
r_if
c_cond
(paren
id|bit_mask
op_amp
id|gpe_register_info-&gt;wake_enable
)paren
(brace
id|local_event_status
op_or_assign
id|ACPI_EVENT_FLAG_WAKE_ENABLED
suffix:semicolon
)brace
multiline_comment|/* GPE active (set)? */
id|status
op_assign
id|acpi_hw_low_level_read
(paren
l_int|8
comma
op_amp
id|in_byte
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
r_if
c_cond
(paren
id|bit_mask
op_amp
id|in_byte
)paren
(brace
id|local_event_status
op_or_assign
id|ACPI_EVENT_FLAG_SET
suffix:semicolon
)brace
multiline_comment|/* Set return value */
(paren
op_star
id|event_status
)paren
op_assign
id|local_event_status
suffix:semicolon
id|unlock_and_exit
suffix:colon
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/******************************************************************************&n; *&n; * FUNCTION:    acpi_hw_disable_gpe_block&n; *&n; * PARAMETERS:  gpe_xrupt_info      - GPE Interrupt info&n; *              gpe_block           - Gpe Block info&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Disable all GPEs within a GPE block&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_hw_disable_gpe_block
id|acpi_hw_disable_gpe_block
(paren
r_struct
id|acpi_gpe_xrupt_info
op_star
id|gpe_xrupt_info
comma
r_struct
id|acpi_gpe_block_info
op_star
id|gpe_block
)paren
(brace
id|u32
id|i
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
multiline_comment|/* Examine each GPE Register within the block */
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
multiline_comment|/* Disable all GPEs in this register */
id|status
op_assign
id|acpi_hw_low_level_write
(paren
l_int|8
comma
l_int|0x00
comma
op_amp
id|gpe_block-&gt;register_info
(braket
id|i
)braket
dot
id|enable_address
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
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/******************************************************************************&n; *&n; * FUNCTION:    acpi_hw_clear_gpe_block&n; *&n; * PARAMETERS:  gpe_xrupt_info      - GPE Interrupt info&n; *              gpe_block           - Gpe Block info&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Clear all GPEs within a GPE block&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_hw_clear_gpe_block
id|acpi_hw_clear_gpe_block
(paren
r_struct
id|acpi_gpe_xrupt_info
op_star
id|gpe_xrupt_info
comma
r_struct
id|acpi_gpe_block_info
op_star
id|gpe_block
)paren
(brace
id|u32
id|i
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
multiline_comment|/* Examine each GPE Register within the block */
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
multiline_comment|/* Clear all GPEs in this register */
id|status
op_assign
id|acpi_hw_low_level_write
(paren
l_int|8
comma
l_int|0xFF
comma
op_amp
id|gpe_block-&gt;register_info
(braket
id|i
)braket
dot
id|status_address
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
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/******************************************************************************&n; *&n; * FUNCTION:    acpi_hw_disable_non_wakeup_gpe_block&n; *&n; * PARAMETERS:  gpe_xrupt_info      - GPE Interrupt info&n; *              gpe_block           - Gpe Block info&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Disable all GPEs except wakeup GPEs in a GPE block&n; *&n; ******************************************************************************/
r_static
id|acpi_status
DECL|function|acpi_hw_disable_non_wakeup_gpe_block
id|acpi_hw_disable_non_wakeup_gpe_block
(paren
r_struct
id|acpi_gpe_xrupt_info
op_star
id|gpe_xrupt_info
comma
r_struct
id|acpi_gpe_block_info
op_star
id|gpe_block
)paren
(brace
id|u32
id|i
suffix:semicolon
r_struct
id|acpi_gpe_register_info
op_star
id|gpe_register_info
suffix:semicolon
id|u32
id|in_value
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
multiline_comment|/* Get the register info for the entire GPE block */
id|gpe_register_info
op_assign
id|gpe_block-&gt;register_info
suffix:semicolon
multiline_comment|/* Examine each GPE Register within the block */
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
multiline_comment|/*&n;&t;&t; * Read the enabled status of all GPEs. We&n;&t;&t; * will be using it to restore all the GPEs later.&n;&t;&t; */
id|status
op_assign
id|acpi_hw_low_level_read
(paren
l_int|8
comma
op_amp
id|in_value
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
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
id|gpe_register_info-&gt;enable
op_assign
(paren
id|u8
)paren
id|in_value
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Disable all GPEs except wakeup GPEs.&n;&t;&t; */
id|status
op_assign
id|acpi_hw_low_level_write
(paren
l_int|8
comma
id|gpe_register_info-&gt;wake_enable
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
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
id|gpe_register_info
op_increment
suffix:semicolon
)brace
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/******************************************************************************&n; *&n; * FUNCTION:    acpi_hw_disable_non_wakeup_gpes&n; *&n; * PARAMETERS:  None&n; *&n; * RETURN:      None&n; *&n; * DESCRIPTION: Disable all non-wakeup GPEs&n; *              Called with interrupts disabled. The interrupt handler also&n; *              modifies gpe_register_info-&gt;Enable, so it should not be&n; *              given the chance to run until after non-wake GPEs are&n; *              re-enabled.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_hw_disable_non_wakeup_gpes
id|acpi_hw_disable_non_wakeup_gpes
(paren
r_void
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_ENTRY
(paren
)paren
suffix:semicolon
id|status
op_assign
id|acpi_ev_walk_gpe_list
(paren
id|acpi_hw_disable_non_wakeup_gpe_block
)paren
suffix:semicolon
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/******************************************************************************&n; *&n; * FUNCTION:    acpi_hw_enable_non_wakeup_gpe_block&n; *&n; * PARAMETERS:  gpe_xrupt_info      - GPE Interrupt info&n; *              gpe_block           - Gpe Block info&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Enable a single GPE.&n; *&n; ******************************************************************************/
r_static
id|acpi_status
DECL|function|acpi_hw_enable_non_wakeup_gpe_block
id|acpi_hw_enable_non_wakeup_gpe_block
(paren
r_struct
id|acpi_gpe_xrupt_info
op_star
id|gpe_xrupt_info
comma
r_struct
id|acpi_gpe_block_info
op_star
id|gpe_block
)paren
(brace
id|u32
id|i
suffix:semicolon
r_struct
id|acpi_gpe_register_info
op_star
id|gpe_register_info
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
multiline_comment|/* This callback processes one entire GPE block */
multiline_comment|/* Get the register info for the entire GPE block */
id|gpe_register_info
op_assign
id|gpe_block-&gt;register_info
suffix:semicolon
multiline_comment|/* Examine each GPE register within the block */
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
multiline_comment|/*&n;&t;&t; * We previously stored the enabled status of all GPEs.&n;&t;&t; * Blast them back in.&n;&t;&t; */
id|status
op_assign
id|acpi_hw_low_level_write
(paren
l_int|8
comma
id|gpe_register_info-&gt;enable
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
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
id|gpe_register_info
op_increment
suffix:semicolon
)brace
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/******************************************************************************&n; *&n; * FUNCTION:    acpi_hw_enable_non_wakeup_gpes&n; *&n; * PARAMETERS:  None&n; *&n; * RETURN:      None&n; *&n; * DESCRIPTION: Enable all non-wakeup GPEs we previously enabled.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_hw_enable_non_wakeup_gpes
id|acpi_hw_enable_non_wakeup_gpes
(paren
r_void
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_ENTRY
(paren
)paren
suffix:semicolon
id|status
op_assign
id|acpi_ev_walk_gpe_list
(paren
id|acpi_hw_enable_non_wakeup_gpe_block
)paren
suffix:semicolon
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
eof
