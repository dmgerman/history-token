multiline_comment|/******************************************************************************&n; *&n; * Module Name: evgpeblk - GPE block creation and initialization.&n; *&n; *****************************************************************************/
multiline_comment|/*&n; * Copyright (C) 2000 - 2003, R. Byron Moore&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. Redistributions in binary form must reproduce at minimum a disclaimer&n; *    substantially similar to the &quot;NO WARRANTY&quot; disclaimer below&n; *    (&quot;Disclaimer&quot;) and any redistribution must be conditioned upon&n; *    including a substantially similar Disclaimer requirement for further&n; *    binary redistribution.&n; * 3. Neither the names of the above-listed copyright holders nor the names&n; *    of any contributors may be used to endorse or promote products derived&n; *    from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;) version 2 as published by the Free&n; * Software Foundation.&n; *&n; * NO WARRANTY&n; * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS&n; * &quot;AS IS&quot; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT&n; * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR&n; * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT&n; * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,&n; * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING&n; * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE&n; * POSSIBILITY OF SUCH DAMAGES.&n; */
macro_line|#include &lt;acpi/acpi.h&gt;
macro_line|#include &lt;acpi/acevents.h&gt;
macro_line|#include &lt;acpi/acnamesp.h&gt;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_EVENTS
id|ACPI_MODULE_NAME
(paren
l_string|&quot;evgpeblk&quot;
)paren
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ev_valid_gpe_event&n; *&n; * PARAMETERS:  gpe_event_info - Info for this GPE&n; *&n; * RETURN:      TRUE if the gpe_event is valid&n; *&n; * DESCRIPTION: Validate a GPE event.  DO NOT CALL FROM INTERRUPT LEVEL.&n; *              Should be called only when the GPE lists are semaphore locked&n; *              and not subject to change.&n; *&n; ******************************************************************************/
id|u8
DECL|function|acpi_ev_valid_gpe_event
id|acpi_ev_valid_gpe_event
(paren
r_struct
id|acpi_gpe_event_info
op_star
id|gpe_event_info
)paren
(brace
r_struct
id|acpi_gpe_xrupt_info
op_star
id|gpe_xrupt_block
suffix:semicolon
r_struct
id|acpi_gpe_block_info
op_star
id|gpe_block
suffix:semicolon
id|ACPI_FUNCTION_ENTRY
(paren
)paren
suffix:semicolon
multiline_comment|/* No need for spin lock since we are not changing any list elements */
multiline_comment|/* Walk the GPE interrupt levels */
id|gpe_xrupt_block
op_assign
id|acpi_gbl_gpe_xrupt_list_head
suffix:semicolon
r_while
c_loop
(paren
id|gpe_xrupt_block
)paren
(brace
id|gpe_block
op_assign
id|gpe_xrupt_block-&gt;gpe_block_list_head
suffix:semicolon
multiline_comment|/* Walk the GPE blocks on this interrupt level */
r_while
c_loop
(paren
id|gpe_block
)paren
(brace
r_if
c_cond
(paren
(paren
op_amp
id|gpe_block-&gt;event_info
(braket
l_int|0
)braket
op_le
id|gpe_event_info
)paren
op_logical_and
(paren
op_amp
id|gpe_block-&gt;event_info
(braket
(paren
(paren
id|acpi_size
)paren
id|gpe_block-&gt;register_count
)paren
op_star
l_int|8
)braket
OG
id|gpe_event_info
)paren
)paren
(brace
r_return
(paren
id|TRUE
)paren
suffix:semicolon
)brace
id|gpe_block
op_assign
id|gpe_block-&gt;next
suffix:semicolon
)brace
id|gpe_xrupt_block
op_assign
id|gpe_xrupt_block-&gt;next
suffix:semicolon
)brace
r_return
(paren
id|FALSE
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ev_walk_gpe_list&n; *&n; * PARAMETERS:  gpe_walk_callback   - Routine called for each GPE block&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Walk the GPE lists.&n; *              FUNCTION MUST BE CALLED WITH INTERRUPTS DISABLED&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ev_walk_gpe_list
id|acpi_ev_walk_gpe_list
(paren
id|ACPI_GPE_CALLBACK
id|gpe_walk_callback
)paren
(brace
r_struct
id|acpi_gpe_block_info
op_star
id|gpe_block
suffix:semicolon
r_struct
id|acpi_gpe_xrupt_info
op_star
id|gpe_xrupt_info
suffix:semicolon
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ev_walk_gpe_list&quot;
)paren
suffix:semicolon
id|acpi_os_acquire_lock
(paren
id|acpi_gbl_gpe_lock
comma
id|ACPI_ISR
)paren
suffix:semicolon
multiline_comment|/* Walk the interrupt level descriptor list */
id|gpe_xrupt_info
op_assign
id|acpi_gbl_gpe_xrupt_list_head
suffix:semicolon
r_while
c_loop
(paren
id|gpe_xrupt_info
)paren
(brace
multiline_comment|/* Walk all Gpe Blocks attached to this interrupt level */
id|gpe_block
op_assign
id|gpe_xrupt_info-&gt;gpe_block_list_head
suffix:semicolon
r_while
c_loop
(paren
id|gpe_block
)paren
(brace
multiline_comment|/* One callback per GPE block */
id|status
op_assign
id|gpe_walk_callback
(paren
id|gpe_xrupt_info
comma
id|gpe_block
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
id|gpe_block
op_assign
id|gpe_block-&gt;next
suffix:semicolon
)brace
id|gpe_xrupt_info
op_assign
id|gpe_xrupt_info-&gt;next
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
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ev_save_method_info&n; *&n; * PARAMETERS:  Callback from walk_namespace&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Called from acpi_walk_namespace. Expects each object to be a&n; *              control method under the _GPE portion of the namespace.&n; *              Extract the name and GPE type from the object, saving this&n; *              information for quick lookup during GPE dispatch&n; *&n; *              The name of each GPE control method is of the form:&n; *                  &quot;_Lnn&quot; or &quot;_Enn&quot;&n; *                  Where:&n; *                      L      - means that the GPE is level triggered&n; *                      E      - means that the GPE is edge triggered&n; *                      nn     - is the GPE number [in HEX]&n; *&n; ******************************************************************************/
r_static
id|acpi_status
DECL|function|acpi_ev_save_method_info
id|acpi_ev_save_method_info
(paren
id|acpi_handle
id|obj_handle
comma
id|u32
id|level
comma
r_void
op_star
id|obj_desc
comma
r_void
op_star
op_star
id|return_value
)paren
(brace
r_struct
id|acpi_gpe_block_info
op_star
id|gpe_block
op_assign
(paren
r_void
op_star
)paren
id|obj_desc
suffix:semicolon
r_struct
id|acpi_gpe_event_info
op_star
id|gpe_event_info
suffix:semicolon
id|u32
id|gpe_number
suffix:semicolon
r_char
id|name
(braket
id|ACPI_NAME_SIZE
op_plus
l_int|1
)braket
suffix:semicolon
id|u8
id|type
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ev_save_method_info&quot;
)paren
suffix:semicolon
multiline_comment|/* Extract the name from the object and convert to a string */
id|ACPI_MOVE_32_TO_32
(paren
id|name
comma
op_amp
(paren
(paren
r_struct
id|acpi_namespace_node
op_star
)paren
id|obj_handle
)paren
op_member_access_from_pointer
id|name.integer
)paren
suffix:semicolon
id|name
(braket
id|ACPI_NAME_SIZE
)braket
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * Edge/Level determination is based on the 2nd character&n;&t; * of the method name&n;&t; */
r_switch
c_cond
(paren
id|name
(braket
l_int|1
)braket
)paren
(brace
r_case
l_char|&squot;L&squot;
suffix:colon
id|type
op_assign
id|ACPI_EVENT_LEVEL_TRIGGERED
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;E&squot;
suffix:colon
id|type
op_assign
id|ACPI_EVENT_EDGE_TRIGGERED
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* Unknown method type, just ignore it! */
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Unknown GPE method type: %s (name not of form _Lnn or _Enn)&bslash;n&quot;
comma
id|name
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/* Convert the last two characters of the name to the GPE Number */
id|gpe_number
op_assign
id|ACPI_STRTOUL
(paren
op_amp
id|name
(braket
l_int|2
)braket
comma
l_int|NULL
comma
l_int|16
)paren
suffix:semicolon
r_if
c_cond
(paren
id|gpe_number
op_eq
id|ACPI_UINT32_MAX
)paren
(brace
multiline_comment|/* Conversion failed; invalid method, just ignore it */
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Could not extract GPE number from name: %s (name is not of form _Lnn or _Enn)&bslash;n&quot;
comma
id|name
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/* Ensure that we have a valid GPE number for this GPE block */
r_if
c_cond
(paren
(paren
id|gpe_number
OL
id|gpe_block-&gt;block_base_number
)paren
op_logical_or
(paren
id|gpe_number
op_ge
(paren
id|gpe_block-&gt;block_base_number
op_plus
(paren
id|gpe_block-&gt;register_count
op_star
l_int|8
)paren
)paren
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t; * Not valid for this GPE block, just ignore it&n;&t;&t; * However, it may be valid for a different GPE block, since GPE0 and GPE1&n;&t;&t; * methods both appear under &bslash;_GPE.&n;&t;&t; */
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Now we can add this information to the gpe_event_info block&n;&t; * for use during dispatch of this GPE.&n;&t; */
id|gpe_event_info
op_assign
op_amp
id|gpe_block-&gt;event_info
(braket
id|gpe_number
op_minus
id|gpe_block-&gt;block_base_number
)braket
suffix:semicolon
id|gpe_event_info-&gt;flags
op_assign
id|type
suffix:semicolon
id|gpe_event_info-&gt;method_node
op_assign
(paren
r_struct
id|acpi_namespace_node
op_star
)paren
id|obj_handle
suffix:semicolon
multiline_comment|/* Enable the GPE (SCIs should be disabled at this point) */
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
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_LOAD
comma
l_string|&quot;Registered GPE method %s as GPE number 0x%.2X&bslash;n&quot;
comma
id|name
comma
id|gpe_number
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ev_get_gpe_xrupt_block&n; *&n; * PARAMETERS:  interrupt_level     - Interrupt for a GPE block&n; *&n; * RETURN:      A GPE interrupt block&n; *&n; * DESCRIPTION: Get or Create a GPE interrupt block.  There is one interrupt&n; *              block per unique interrupt level used for GPEs.&n; *              Should be called only when the GPE lists are semaphore locked&n; *              and not subject to change.&n; *&n; ******************************************************************************/
r_static
r_struct
id|acpi_gpe_xrupt_info
op_star
DECL|function|acpi_ev_get_gpe_xrupt_block
id|acpi_ev_get_gpe_xrupt_block
(paren
id|u32
id|interrupt_level
)paren
(brace
r_struct
id|acpi_gpe_xrupt_info
op_star
id|next_gpe_xrupt
suffix:semicolon
r_struct
id|acpi_gpe_xrupt_info
op_star
id|gpe_xrupt
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ev_get_gpe_xrupt_block&quot;
)paren
suffix:semicolon
multiline_comment|/* No need for spin lock since we are not changing any list elements here */
id|next_gpe_xrupt
op_assign
id|acpi_gbl_gpe_xrupt_list_head
suffix:semicolon
r_while
c_loop
(paren
id|next_gpe_xrupt
)paren
(brace
r_if
c_cond
(paren
id|next_gpe_xrupt-&gt;interrupt_level
op_eq
id|interrupt_level
)paren
(brace
id|return_PTR
(paren
id|next_gpe_xrupt
)paren
suffix:semicolon
)brace
id|next_gpe_xrupt
op_assign
id|next_gpe_xrupt-&gt;next
suffix:semicolon
)brace
multiline_comment|/* Not found, must allocate a new xrupt descriptor */
id|gpe_xrupt
op_assign
id|ACPI_MEM_CALLOCATE
(paren
r_sizeof
(paren
r_struct
id|acpi_gpe_xrupt_info
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|gpe_xrupt
)paren
(brace
id|return_PTR
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
id|gpe_xrupt-&gt;interrupt_level
op_assign
id|interrupt_level
suffix:semicolon
multiline_comment|/* Install new interrupt descriptor with spin lock */
id|acpi_os_acquire_lock
(paren
id|acpi_gbl_gpe_lock
comma
id|ACPI_NOT_ISR
)paren
suffix:semicolon
r_if
c_cond
(paren
id|acpi_gbl_gpe_xrupt_list_head
)paren
(brace
id|next_gpe_xrupt
op_assign
id|acpi_gbl_gpe_xrupt_list_head
suffix:semicolon
r_while
c_loop
(paren
id|next_gpe_xrupt-&gt;next
)paren
(brace
id|next_gpe_xrupt
op_assign
id|next_gpe_xrupt-&gt;next
suffix:semicolon
)brace
id|next_gpe_xrupt-&gt;next
op_assign
id|gpe_xrupt
suffix:semicolon
id|gpe_xrupt-&gt;previous
op_assign
id|next_gpe_xrupt
suffix:semicolon
)brace
r_else
(brace
id|acpi_gbl_gpe_xrupt_list_head
op_assign
id|gpe_xrupt
suffix:semicolon
)brace
id|acpi_os_release_lock
(paren
id|acpi_gbl_gpe_lock
comma
id|ACPI_NOT_ISR
)paren
suffix:semicolon
multiline_comment|/* Install new interrupt handler if not SCI_INT */
r_if
c_cond
(paren
id|interrupt_level
op_ne
id|acpi_gbl_FADT-&gt;sci_int
)paren
(brace
id|status
op_assign
id|acpi_os_install_interrupt_handler
(paren
id|interrupt_level
comma
id|acpi_ev_gpe_xrupt_handler
comma
id|gpe_xrupt
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
l_string|&quot;Could not install GPE interrupt handler at level 0x%X&bslash;n&quot;
comma
id|interrupt_level
)paren
)paren
suffix:semicolon
id|return_PTR
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
)brace
id|return_PTR
(paren
id|gpe_xrupt
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ev_delete_gpe_xrupt&n; *&n; * PARAMETERS:  gpe_xrupt       - A GPE interrupt info block&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Remove and free a gpe_xrupt block. Remove an associated&n; *              interrupt handler if not the SCI interrupt.&n; *&n; ******************************************************************************/
r_static
id|acpi_status
DECL|function|acpi_ev_delete_gpe_xrupt
id|acpi_ev_delete_gpe_xrupt
(paren
r_struct
id|acpi_gpe_xrupt_info
op_star
id|gpe_xrupt
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ev_delete_gpe_xrupt&quot;
)paren
suffix:semicolon
multiline_comment|/* We never want to remove the SCI interrupt handler */
r_if
c_cond
(paren
id|gpe_xrupt-&gt;interrupt_level
op_eq
id|acpi_gbl_FADT-&gt;sci_int
)paren
(brace
id|gpe_xrupt-&gt;gpe_block_list_head
op_assign
l_int|NULL
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/* Disable this interrupt */
id|status
op_assign
id|acpi_os_remove_interrupt_handler
(paren
id|gpe_xrupt-&gt;interrupt_level
comma
id|acpi_ev_gpe_xrupt_handler
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
multiline_comment|/* Unlink the interrupt block with lock */
id|acpi_os_acquire_lock
(paren
id|acpi_gbl_gpe_lock
comma
id|ACPI_NOT_ISR
)paren
suffix:semicolon
r_if
c_cond
(paren
id|gpe_xrupt-&gt;previous
)paren
(brace
id|gpe_xrupt-&gt;previous-&gt;next
op_assign
id|gpe_xrupt-&gt;next
suffix:semicolon
)brace
r_if
c_cond
(paren
id|gpe_xrupt-&gt;next
)paren
(brace
id|gpe_xrupt-&gt;next-&gt;previous
op_assign
id|gpe_xrupt-&gt;previous
suffix:semicolon
)brace
id|acpi_os_release_lock
(paren
id|acpi_gbl_gpe_lock
comma
id|ACPI_NOT_ISR
)paren
suffix:semicolon
multiline_comment|/* Free the block */
id|ACPI_MEM_FREE
(paren
id|gpe_xrupt
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ev_install_gpe_block&n; *&n; * PARAMETERS:  gpe_block       - New GPE block&n; *              interrupt_level - Level to be associated with this GPE block&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Install new GPE block with mutex support&n; *&n; ******************************************************************************/
r_static
id|acpi_status
DECL|function|acpi_ev_install_gpe_block
id|acpi_ev_install_gpe_block
(paren
r_struct
id|acpi_gpe_block_info
op_star
id|gpe_block
comma
id|u32
id|interrupt_level
)paren
(brace
r_struct
id|acpi_gpe_block_info
op_star
id|next_gpe_block
suffix:semicolon
r_struct
id|acpi_gpe_xrupt_info
op_star
id|gpe_xrupt_block
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ev_install_gpe_block&quot;
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
id|gpe_xrupt_block
op_assign
id|acpi_ev_get_gpe_xrupt_block
(paren
id|interrupt_level
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|gpe_xrupt_block
)paren
(brace
id|status
op_assign
id|AE_NO_MEMORY
suffix:semicolon
r_goto
id|unlock_and_exit
suffix:semicolon
)brace
multiline_comment|/* Install the new block at the end of the list for this interrupt with lock */
id|acpi_os_acquire_lock
(paren
id|acpi_gbl_gpe_lock
comma
id|ACPI_NOT_ISR
)paren
suffix:semicolon
r_if
c_cond
(paren
id|gpe_xrupt_block-&gt;gpe_block_list_head
)paren
(brace
id|next_gpe_block
op_assign
id|gpe_xrupt_block-&gt;gpe_block_list_head
suffix:semicolon
r_while
c_loop
(paren
id|next_gpe_block-&gt;next
)paren
(brace
id|next_gpe_block
op_assign
id|next_gpe_block-&gt;next
suffix:semicolon
)brace
id|next_gpe_block-&gt;next
op_assign
id|gpe_block
suffix:semicolon
id|gpe_block-&gt;previous
op_assign
id|next_gpe_block
suffix:semicolon
)brace
r_else
(brace
id|gpe_xrupt_block-&gt;gpe_block_list_head
op_assign
id|gpe_block
suffix:semicolon
)brace
id|gpe_block-&gt;xrupt_block
op_assign
id|gpe_xrupt_block
suffix:semicolon
id|acpi_os_release_lock
(paren
id|acpi_gbl_gpe_lock
comma
id|ACPI_NOT_ISR
)paren
suffix:semicolon
id|unlock_and_exit
suffix:colon
id|status
op_assign
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
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ev_delete_gpe_block&n; *&n; * PARAMETERS:  gpe_block       - Existing GPE block&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Remove a GPE block&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ev_delete_gpe_block
id|acpi_ev_delete_gpe_block
(paren
r_struct
id|acpi_gpe_block_info
op_star
id|gpe_block
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ev_install_gpe_block&quot;
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
multiline_comment|/* Disable all GPEs in this block */
id|status
op_assign
id|acpi_hw_disable_gpe_block
(paren
id|gpe_block-&gt;xrupt_block
comma
id|gpe_block
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|gpe_block-&gt;previous
op_logical_and
op_logical_neg
id|gpe_block-&gt;next
)paren
(brace
multiline_comment|/* This is the last gpe_block on this interrupt */
id|status
op_assign
id|acpi_ev_delete_gpe_xrupt
(paren
id|gpe_block-&gt;xrupt_block
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
r_else
(brace
multiline_comment|/* Remove the block on this interrupt with lock */
id|acpi_os_acquire_lock
(paren
id|acpi_gbl_gpe_lock
comma
id|ACPI_NOT_ISR
)paren
suffix:semicolon
r_if
c_cond
(paren
id|gpe_block-&gt;previous
)paren
(brace
id|gpe_block-&gt;previous-&gt;next
op_assign
id|gpe_block-&gt;next
suffix:semicolon
)brace
r_else
(brace
id|gpe_block-&gt;xrupt_block-&gt;gpe_block_list_head
op_assign
id|gpe_block-&gt;next
suffix:semicolon
)brace
r_if
c_cond
(paren
id|gpe_block-&gt;next
)paren
(brace
id|gpe_block-&gt;next-&gt;previous
op_assign
id|gpe_block-&gt;previous
suffix:semicolon
)brace
id|acpi_os_release_lock
(paren
id|acpi_gbl_gpe_lock
comma
id|ACPI_NOT_ISR
)paren
suffix:semicolon
)brace
multiline_comment|/* Free the gpe_block */
id|ACPI_MEM_FREE
(paren
id|gpe_block-&gt;register_info
)paren
suffix:semicolon
id|ACPI_MEM_FREE
(paren
id|gpe_block-&gt;event_info
)paren
suffix:semicolon
id|ACPI_MEM_FREE
(paren
id|gpe_block
)paren
suffix:semicolon
id|unlock_and_exit
suffix:colon
id|status
op_assign
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
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ev_create_gpe_info_blocks&n; *&n; * PARAMETERS:  gpe_block   - New GPE block&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Create the register_info and event_info blocks for this GPE block&n; *&n; ******************************************************************************/
r_static
id|acpi_status
DECL|function|acpi_ev_create_gpe_info_blocks
id|acpi_ev_create_gpe_info_blocks
(paren
r_struct
id|acpi_gpe_block_info
op_star
id|gpe_block
)paren
(brace
r_struct
id|acpi_gpe_register_info
op_star
id|gpe_register_info
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|acpi_gpe_event_info
op_star
id|gpe_event_info
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|acpi_gpe_event_info
op_star
id|this_event
suffix:semicolon
r_struct
id|acpi_gpe_register_info
op_star
id|this_register
suffix:semicolon
id|acpi_native_uint
id|i
suffix:semicolon
id|acpi_native_uint
id|j
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ev_create_gpe_info_blocks&quot;
)paren
suffix:semicolon
multiline_comment|/* Allocate the GPE register information block */
id|gpe_register_info
op_assign
id|ACPI_MEM_CALLOCATE
(paren
(paren
id|acpi_size
)paren
id|gpe_block-&gt;register_count
op_star
r_sizeof
(paren
r_struct
id|acpi_gpe_register_info
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|gpe_register_info
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Could not allocate the gpe_register_info table&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Allocate the GPE event_info block. There are eight distinct GPEs&n;&t; * per register.  Initialization to zeros is sufficient.&n;&t; */
id|gpe_event_info
op_assign
id|ACPI_MEM_CALLOCATE
(paren
(paren
(paren
id|acpi_size
)paren
id|gpe_block-&gt;register_count
op_star
id|ACPI_GPE_REGISTER_WIDTH
)paren
op_star
r_sizeof
(paren
r_struct
id|acpi_gpe_event_info
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|gpe_event_info
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Could not allocate the gpe_event_info table&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|status
op_assign
id|AE_NO_MEMORY
suffix:semicolon
r_goto
id|error_exit
suffix:semicolon
)brace
multiline_comment|/* Save the new Info arrays in the GPE block */
id|gpe_block-&gt;register_info
op_assign
id|gpe_register_info
suffix:semicolon
id|gpe_block-&gt;event_info
op_assign
id|gpe_event_info
suffix:semicolon
multiline_comment|/*&n;&t; * Initialize the GPE Register and Event structures.  A goal of these&n;&t; * tables is to hide the fact that there are two separate GPE register sets&n;&t; * in a given gpe hardware block, the status registers occupy the first half,&n;&t; * and the enable registers occupy the second half.&n;&t; */
id|this_register
op_assign
id|gpe_register_info
suffix:semicolon
id|this_event
op_assign
id|gpe_event_info
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
id|gpe_block-&gt;register_count
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/* Init the register_info for this GPE register (8 GPEs) */
id|this_register-&gt;base_gpe_number
op_assign
(paren
id|u8
)paren
(paren
id|gpe_block-&gt;block_base_number
op_plus
(paren
id|i
op_star
id|ACPI_GPE_REGISTER_WIDTH
)paren
)paren
suffix:semicolon
id|ACPI_STORE_ADDRESS
(paren
id|this_register-&gt;status_address.address
comma
(paren
id|gpe_block-&gt;block_address.address
op_plus
id|i
)paren
)paren
suffix:semicolon
id|ACPI_STORE_ADDRESS
(paren
id|this_register-&gt;enable_address.address
comma
(paren
id|gpe_block-&gt;block_address.address
op_plus
id|i
op_plus
id|gpe_block-&gt;register_count
)paren
)paren
suffix:semicolon
id|this_register-&gt;status_address.address_space_id
op_assign
id|gpe_block-&gt;block_address.address_space_id
suffix:semicolon
id|this_register-&gt;enable_address.address_space_id
op_assign
id|gpe_block-&gt;block_address.address_space_id
suffix:semicolon
id|this_register-&gt;status_address.register_bit_width
op_assign
id|ACPI_GPE_REGISTER_WIDTH
suffix:semicolon
id|this_register-&gt;enable_address.register_bit_width
op_assign
id|ACPI_GPE_REGISTER_WIDTH
suffix:semicolon
id|this_register-&gt;status_address.register_bit_offset
op_assign
id|ACPI_GPE_REGISTER_WIDTH
suffix:semicolon
id|this_register-&gt;enable_address.register_bit_offset
op_assign
id|ACPI_GPE_REGISTER_WIDTH
suffix:semicolon
multiline_comment|/* Init the event_info for each GPE within this register */
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
id|this_event-&gt;bit_mask
op_assign
id|acpi_gbl_decode_to8bit
(braket
id|j
)braket
suffix:semicolon
id|this_event-&gt;register_info
op_assign
id|this_register
suffix:semicolon
id|this_event
op_increment
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Clear the status/enable registers.  Note that status registers&n;&t;&t; * are cleared by writing a &squot;1&squot;, while enable registers are cleared&n;&t;&t; * by writing a &squot;0&squot;.&n;&t;&t; */
id|status
op_assign
id|acpi_hw_low_level_write
(paren
id|ACPI_GPE_REGISTER_WIDTH
comma
l_int|0x00
comma
op_amp
id|this_register-&gt;enable_address
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
id|error_exit
suffix:semicolon
)brace
id|status
op_assign
id|acpi_hw_low_level_write
(paren
id|ACPI_GPE_REGISTER_WIDTH
comma
l_int|0xFF
comma
op_amp
id|this_register-&gt;status_address
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
id|error_exit
suffix:semicolon
)brace
id|this_register
op_increment
suffix:semicolon
)brace
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
id|error_exit
suffix:colon
r_if
c_cond
(paren
id|gpe_register_info
)paren
(brace
id|ACPI_MEM_FREE
(paren
id|gpe_register_info
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|gpe_event_info
)paren
(brace
id|ACPI_MEM_FREE
(paren
id|gpe_event_info
)paren
suffix:semicolon
)brace
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ev_create_gpe_block&n; *&n; * PARAMETERS:  gpe_device          - Handle to the parent GPE block&n; *              gpe_block_address   - Address and space_iD&n; *              register_count      - Number of GPE register pairs in the block&n; *              gpe_block_base_number - Starting GPE number for the block&n; *              interrupt_level     - H/W interrupt for the block&n; *              return_gpe_block    - Where the new block descriptor is returned&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Create and Install a block of GPE registers&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ev_create_gpe_block
id|acpi_ev_create_gpe_block
(paren
r_struct
id|acpi_namespace_node
op_star
id|gpe_device
comma
r_struct
id|acpi_generic_address
op_star
id|gpe_block_address
comma
id|u32
id|register_count
comma
id|u8
id|gpe_block_base_number
comma
id|u32
id|interrupt_level
comma
r_struct
id|acpi_gpe_block_info
op_star
op_star
id|return_gpe_block
)paren
(brace
r_struct
id|acpi_gpe_block_info
op_star
id|gpe_block
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ev_create_gpe_block&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|register_count
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/* Allocate a new GPE block */
id|gpe_block
op_assign
id|ACPI_MEM_CALLOCATE
(paren
r_sizeof
(paren
r_struct
id|acpi_gpe_block_info
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|gpe_block
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
)brace
multiline_comment|/* Initialize the new GPE block */
id|gpe_block-&gt;register_count
op_assign
id|register_count
suffix:semicolon
id|gpe_block-&gt;block_base_number
op_assign
id|gpe_block_base_number
suffix:semicolon
id|ACPI_MEMCPY
(paren
op_amp
id|gpe_block-&gt;block_address
comma
id|gpe_block_address
comma
r_sizeof
(paren
r_struct
id|acpi_generic_address
)paren
)paren
suffix:semicolon
multiline_comment|/* Create the register_info and event_info sub-structures */
id|status
op_assign
id|acpi_ev_create_gpe_info_blocks
(paren
id|gpe_block
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
id|ACPI_MEM_FREE
(paren
id|gpe_block
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/* Install the new block in the global list(s) */
id|status
op_assign
id|acpi_ev_install_gpe_block
(paren
id|gpe_block
comma
id|interrupt_level
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
id|ACPI_MEM_FREE
(paren
id|gpe_block
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/* Dump info about this GPE block */
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_INIT
comma
l_string|&quot;GPE %02d to %02d [%4.4s] %d regs at %8.8X%8.8X on int %d&bslash;n&quot;
comma
id|gpe_block-&gt;block_base_number
comma
(paren
id|u32
)paren
(paren
id|gpe_block-&gt;block_base_number
op_plus
(paren
(paren
id|gpe_block-&gt;register_count
op_star
id|ACPI_GPE_REGISTER_WIDTH
)paren
op_minus
l_int|1
)paren
)paren
comma
id|gpe_device-&gt;name.ascii
comma
id|gpe_block-&gt;register_count
comma
id|ACPI_FORMAT_UINT64
(paren
id|gpe_block-&gt;block_address.address
)paren
comma
id|interrupt_level
)paren
)paren
suffix:semicolon
multiline_comment|/* Find all GPE methods (_Lxx, _Exx) for this block */
id|status
op_assign
id|acpi_ns_walk_namespace
(paren
id|ACPI_TYPE_METHOD
comma
id|gpe_device
comma
id|ACPI_UINT32_MAX
comma
id|ACPI_NS_WALK_NO_UNLOCK
comma
id|acpi_ev_save_method_info
comma
id|gpe_block
comma
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/* Return the new block */
r_if
c_cond
(paren
id|return_gpe_block
)paren
(brace
(paren
op_star
id|return_gpe_block
)paren
op_assign
id|gpe_block
suffix:semicolon
)brace
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ev_gpe_initialize&n; *&n; * PARAMETERS:  None&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Initialize the GPE data structures&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ev_gpe_initialize
id|acpi_ev_gpe_initialize
(paren
r_void
)paren
(brace
id|u32
id|register_count0
op_assign
l_int|0
suffix:semicolon
id|u32
id|register_count1
op_assign
l_int|0
suffix:semicolon
id|u32
id|gpe_number_max
op_assign
l_int|0
suffix:semicolon
id|acpi_handle
id|gpe_device
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ev_gpe_initialize&quot;
)paren
suffix:semicolon
multiline_comment|/* Get a handle to the predefined _GPE object */
id|status
op_assign
id|acpi_get_handle
(paren
l_int|NULL
comma
l_string|&quot;&bslash;&bslash;_GPE&quot;
comma
op_amp
id|gpe_device
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
multiline_comment|/*&n;&t; * Initialize the GPE Blocks defined in the FADT&n;&t; *&n;&t; * Why the GPE register block lengths are divided by 2:  From the ACPI Spec,&n;&t; * section &quot;General-Purpose Event Registers&quot;, we have:&n;&t; *&n;&t; * &quot;Each register block contains two registers of equal length&n;&t; *  GPEx_STS and GPEx_EN (where x is 0 or 1). The length of the&n;&t; *  GPE0_STS and GPE0_EN registers is equal to half the GPE0_LEN&n;&t; *  The length of the GPE1_STS and GPE1_EN registers is equal to&n;&t; *  half the GPE1_LEN. If a generic register block is not supported&n;&t; *  then its respective block pointer and block length values in the&n;&t; *  FADT table contain zeros. The GPE0_LEN and GPE1_LEN do not need&n;&t; *  to be the same size.&quot;&n;&t; */
multiline_comment|/*&n;&t; * Determine the maximum GPE number for this machine.&n;&t; *&n;&t; * Note: both GPE0 and GPE1 are optional, and either can exist without&n;&t; * the other.&n;&t; *&n;&t; * If EITHER the register length OR the block address are zero, then that&n;&t; * particular block is not supported.&n;&t; */
r_if
c_cond
(paren
id|acpi_gbl_FADT-&gt;gpe0_blk_len
op_logical_and
id|acpi_gbl_FADT-&gt;xgpe0_blk.address
)paren
(brace
multiline_comment|/* GPE block 0 exists (has both length and address &gt; 0) */
id|register_count0
op_assign
(paren
id|u16
)paren
(paren
id|acpi_gbl_FADT-&gt;gpe0_blk_len
op_div
l_int|2
)paren
suffix:semicolon
id|gpe_number_max
op_assign
(paren
id|register_count0
op_star
id|ACPI_GPE_REGISTER_WIDTH
)paren
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* Install GPE Block 0 */
id|status
op_assign
id|acpi_ev_create_gpe_block
(paren
id|gpe_device
comma
op_amp
id|acpi_gbl_FADT-&gt;xgpe0_blk
comma
id|register_count0
comma
l_int|0
comma
id|acpi_gbl_FADT-&gt;sci_int
comma
op_amp
id|acpi_gbl_gpe_fadt_blocks
(braket
l_int|0
)braket
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
l_string|&quot;Could not create GPE Block 0, %s&bslash;n&quot;
comma
id|acpi_format_exception
(paren
id|status
)paren
)paren
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|acpi_gbl_FADT-&gt;gpe1_blk_len
op_logical_and
id|acpi_gbl_FADT-&gt;xgpe1_blk.address
)paren
(brace
multiline_comment|/* GPE block 1 exists (has both length and address &gt; 0) */
id|register_count1
op_assign
(paren
id|u16
)paren
(paren
id|acpi_gbl_FADT-&gt;gpe1_blk_len
op_div
l_int|2
)paren
suffix:semicolon
multiline_comment|/* Check for GPE0/GPE1 overlap (if both banks exist) */
r_if
c_cond
(paren
(paren
id|register_count0
)paren
op_logical_and
(paren
id|gpe_number_max
op_ge
id|acpi_gbl_FADT-&gt;gpe1_base
)paren
)paren
(brace
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;GPE0 block (GPE 0 to %d) overlaps the GPE1 block (GPE %d to %d) - Ignoring GPE1&bslash;n&quot;
comma
id|gpe_number_max
comma
id|acpi_gbl_FADT-&gt;gpe1_base
comma
id|acpi_gbl_FADT-&gt;gpe1_base
op_plus
(paren
(paren
id|register_count1
op_star
id|ACPI_GPE_REGISTER_WIDTH
)paren
op_minus
l_int|1
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/* Ignore GPE1 block by setting the register count to zero */
id|register_count1
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Install GPE Block 1 */
id|status
op_assign
id|acpi_ev_create_gpe_block
(paren
id|gpe_device
comma
op_amp
id|acpi_gbl_FADT-&gt;xgpe1_blk
comma
id|register_count1
comma
id|acpi_gbl_FADT-&gt;gpe1_base
comma
id|acpi_gbl_FADT-&gt;sci_int
comma
op_amp
id|acpi_gbl_gpe_fadt_blocks
(braket
l_int|1
)braket
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
l_string|&quot;Could not create GPE Block 1, %s&bslash;n&quot;
comma
id|acpi_format_exception
(paren
id|status
)paren
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t;&t; * GPE0 and GPE1 do not have to be contiguous in the GPE number&n;&t;&t;&t; * space. However, GPE0 always starts at GPE number zero.&n;&t;&t;&t; */
id|gpe_number_max
op_assign
id|acpi_gbl_FADT-&gt;gpe1_base
op_plus
(paren
(paren
id|register_count1
op_star
id|ACPI_GPE_REGISTER_WIDTH
)paren
op_minus
l_int|1
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Exit if there are no GPE registers */
r_if
c_cond
(paren
(paren
id|register_count0
op_plus
id|register_count1
)paren
op_eq
l_int|0
)paren
(brace
multiline_comment|/* GPEs are not required by ACPI, this is OK */
id|ACPI_REPORT_INFO
(paren
(paren
l_string|&quot;There are no GPE blocks defined in the FADT&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/* Check for Max GPE number out-of-range */
r_if
c_cond
(paren
id|gpe_number_max
OG
id|ACPI_GPE_MAX
)paren
(brace
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;Maximum GPE number from FADT is too large: 0x%X&bslash;n&quot;
comma
id|gpe_number_max
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_BAD_VALUE
)paren
suffix:semicolon
)brace
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
eof
