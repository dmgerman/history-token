multiline_comment|/******************************************************************************&n; *&n; * Module Name: evevent - Fixed and General Purpose Even handling and dispatch&n; *              $Revision: 71 $&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000 - 2002, R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &quot;acpi.h&quot;
macro_line|#include &quot;achware.h&quot;
macro_line|#include &quot;acevents.h&quot;
macro_line|#include &quot;acnamesp.h&quot;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_EVENTS
id|ACPI_MODULE_NAME
(paren
l_string|&quot;evevent&quot;
)paren
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ev_initialize&n; *&n; * PARAMETERS:  None&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Initialize global data structures for events.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ev_initialize
id|acpi_ev_initialize
(paren
r_void
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;Ev_initialize&quot;
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
multiline_comment|/*&n;&t; * Initialize the Fixed and General Purpose Acpi_events prior. This is&n;&t; * done prior to enabling SCIs to prevent interrupts from occuring&n;&t; * before handers are installed.&n;&t; */
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
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_FATAL
comma
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
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_FATAL
comma
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
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ev_handler_initialize&n; *&n; * PARAMETERS:  None&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Install handlers for the SCI, Global Lock, and GPEs.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ev_handler_initialize
id|acpi_ev_handler_initialize
(paren
r_void
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;Ev_initialize&quot;
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
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_FATAL
comma
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
multiline_comment|/* Install handlers for control method GPE handlers (_Lxx, _Exx) */
id|status
op_assign
id|acpi_ev_init_gpe_control_methods
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
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_FATAL
comma
l_string|&quot;Unable to initialize GPE control methods, %s&bslash;n&quot;
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
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_FATAL
comma
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
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ev_fixed_event_initialize&n; *&n; * PARAMETERS:  None&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Install the fixed event handlers and enable the fixed events.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ev_fixed_event_initialize
id|acpi_ev_fixed_event_initialize
(paren
r_void
)paren
(brace
id|NATIVE_UINT
id|i
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
id|acpi_hw_bit_register_write
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
)brace
)brace
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ev_fixed_event_detect&n; *&n; * PARAMETERS:  None&n; *&n; * RETURN:      INTERRUPT_HANDLED or INTERRUPT_NOT_HANDLED&n; *&n; * DESCRIPTION: Checks the PM status register for fixed events&n; *&n; ******************************************************************************/
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
id|gpe_status
suffix:semicolon
id|u32
id|gpe_enable
suffix:semicolon
id|NATIVE_UINT
id|i
suffix:semicolon
id|ACPI_FUNCTION_NAME
(paren
l_string|&quot;Ev_fixed_event_detect&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Read the fixed feature status and enable registers, as all the cases&n;&t; * depend on their values.&n;&t; */
id|gpe_status
op_assign
id|acpi_hw_register_read
(paren
id|ACPI_MTX_DO_NOT_LOCK
comma
id|ACPI_REGISTER_PM1_STATUS
)paren
suffix:semicolon
id|gpe_enable
op_assign
id|acpi_hw_register_read
(paren
id|ACPI_MTX_DO_NOT_LOCK
comma
id|ACPI_REGISTER_PM1_ENABLE
)paren
suffix:semicolon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_INTERRUPTS
comma
l_string|&quot;Fixed Acpi_event Block: Enable %08X Status %08X&bslash;n&quot;
comma
id|gpe_enable
comma
id|gpe_status
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
id|gpe_status
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
id|gpe_enable
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
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ev_fixed_event_dispatch&n; *&n; * PARAMETERS:  Event               - Event type&n; *&n; * RETURN:      INTERRUPT_HANDLED or INTERRUPT_NOT_HANDLED&n; *&n; * DESCRIPTION: Clears the status bit for the requested event, calls the&n; *              handler that previously registered for the event.&n; *&n; ******************************************************************************/
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
id|acpi_hw_bit_register_write
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
id|acpi_hw_bit_register_write
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
l_string|&quot;Ev_gpe_dispatch: No installed handler for fixed event [%08X]&bslash;n&quot;
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
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ev_gpe_initialize&n; *&n; * PARAMETERS:  None&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Initialize the GPE data structures&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ev_gpe_initialize
id|acpi_ev_gpe_initialize
(paren
r_void
)paren
(brace
id|NATIVE_UINT
id|i
suffix:semicolon
id|NATIVE_UINT
id|j
suffix:semicolon
id|NATIVE_UINT
id|gpe_block
suffix:semicolon
id|u32
id|gpe_register
suffix:semicolon
id|u32
id|gpe_number_index
suffix:semicolon
id|u32
id|gpe_number
suffix:semicolon
id|ACPI_GPE_REGISTER_INFO
op_star
id|gpe_register_info
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;Ev_gpe_initialize&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Initialize the GPE Block globals&n;&t; *&n;&t; * Why the GPE register block lengths divided by 2:  From the ACPI Spec,&n;&t; * section &quot;General-Purpose Event Registers&quot;, we have:&n;&t; *&n;&t; * &quot;Each register block contains two registers of equal length&n;&t; *  GPEx_STS and GPEx_EN (where x is 0 or 1). The length of the&n;&t; *  GPE0_STS and GPE0_EN registers is equal to half the GPE0_LEN&n;&t; *  The length of the GPE1_STS and GPE1_EN registers is equal to&n;&t; *  half the GPE1_LEN. If a generic register block is not supported&n;&t; *  then its respective block pointer and block length values in the&n;&t; *  FADT table contain zeros. The GPE0_LEN and GPE1_LEN do not need&n;&t; *  to be the same size.&quot;&n;&t; */
id|acpi_gbl_gpe_block_info
(braket
l_int|0
)braket
dot
id|register_count
op_assign
(paren
id|u16
)paren
id|ACPI_DIV_2
(paren
id|acpi_gbl_FADT-&gt;gpe0_blk_len
)paren
suffix:semicolon
id|acpi_gbl_gpe_block_info
(braket
l_int|1
)braket
dot
id|register_count
op_assign
(paren
id|u16
)paren
id|ACPI_DIV_2
(paren
id|acpi_gbl_FADT-&gt;gpe1_blk_len
)paren
suffix:semicolon
id|acpi_gbl_gpe_block_info
(braket
l_int|0
)braket
dot
id|block_address
op_assign
(paren
id|u16
)paren
id|ACPI_GET_ADDRESS
(paren
id|acpi_gbl_FADT-&gt;Xgpe0_blk.address
)paren
suffix:semicolon
id|acpi_gbl_gpe_block_info
(braket
l_int|1
)braket
dot
id|block_address
op_assign
(paren
id|u16
)paren
id|ACPI_GET_ADDRESS
(paren
id|acpi_gbl_FADT-&gt;Xgpe1_blk.address
)paren
suffix:semicolon
id|acpi_gbl_gpe_block_info
(braket
l_int|0
)braket
dot
id|block_base_number
op_assign
l_int|0
suffix:semicolon
id|acpi_gbl_gpe_block_info
(braket
l_int|1
)braket
dot
id|block_base_number
op_assign
id|acpi_gbl_FADT-&gt;gpe1_base
suffix:semicolon
id|acpi_gbl_gpe_register_count
op_assign
id|acpi_gbl_gpe_block_info
(braket
l_int|0
)braket
dot
id|register_count
op_plus
id|acpi_gbl_gpe_block_info
(braket
l_int|1
)braket
dot
id|register_count
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|acpi_gbl_gpe_register_count
)paren
(brace
id|ACPI_REPORT_WARNING
(paren
(paren
l_string|&quot;Zero GPEs are defined in the FADT&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/* Determine the maximum GPE number for this machine */
id|acpi_gbl_gpe_number_max
op_assign
id|ACPI_MUL_8
(paren
id|acpi_gbl_gpe_block_info
(braket
l_int|0
)braket
dot
id|register_count
)paren
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|acpi_gbl_gpe_block_info
(braket
l_int|1
)braket
dot
id|register_count
)paren
(brace
multiline_comment|/* Check for GPE0/GPE1 overlap */
r_if
c_cond
(paren
id|acpi_gbl_gpe_number_max
op_ge
id|acpi_gbl_FADT-&gt;gpe1_base
)paren
(brace
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;GPE0 block overlaps the GPE1 block&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_BAD_VALUE
)paren
suffix:semicolon
)brace
multiline_comment|/* GPE0 and GPE1 do not have to be contiguous in the GPE number space */
id|acpi_gbl_gpe_number_max
op_assign
id|acpi_gbl_FADT-&gt;gpe1_base
op_plus
(paren
id|ACPI_MUL_8
(paren
id|acpi_gbl_gpe_block_info
(braket
l_int|1
)braket
dot
id|register_count
)paren
op_minus
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/* Check for Max GPE number out-of-range */
r_if
c_cond
(paren
id|acpi_gbl_gpe_number_max
OG
id|ACPI_GPE_MAX
)paren
(brace
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;Maximum GPE number from FADT is too large: 0x%X&bslash;n&quot;
comma
id|acpi_gbl_gpe_number_max
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_BAD_VALUE
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Allocate the GPE number-to-index translation table&n;&t; */
id|acpi_gbl_gpe_number_to_index
op_assign
id|ACPI_MEM_CALLOCATE
(paren
r_sizeof
(paren
id|ACPI_GPE_INDEX_INFO
)paren
op_star
(paren
id|acpi_gbl_gpe_number_max
op_plus
l_int|1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|acpi_gbl_gpe_number_to_index
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Could not allocate the Gpe_number_to_index table&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
)brace
multiline_comment|/* Set the Gpe index table to GPE_INVALID */
id|ACPI_MEMSET
(paren
id|acpi_gbl_gpe_number_to_index
comma
(paren
r_int
)paren
id|ACPI_GPE_INVALID
comma
r_sizeof
(paren
id|ACPI_GPE_INDEX_INFO
)paren
op_star
(paren
id|acpi_gbl_gpe_number_max
op_plus
l_int|1
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Allocate the GPE register information block&n;&t; */
id|acpi_gbl_gpe_register_info
op_assign
id|ACPI_MEM_CALLOCATE
(paren
id|acpi_gbl_gpe_register_count
op_star
r_sizeof
(paren
id|ACPI_GPE_REGISTER_INFO
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|acpi_gbl_gpe_register_info
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Could not allocate the Gpe_register_info table&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_goto
id|error_exit1
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Allocate the GPE dispatch handler block.  There are eight distinct GPEs&n;&t; * per register.  Initialization to zeros is sufficient.&n;&t; */
id|acpi_gbl_gpe_number_info
op_assign
id|ACPI_MEM_CALLOCATE
(paren
id|ACPI_MUL_8
(paren
id|acpi_gbl_gpe_register_count
)paren
op_star
r_sizeof
(paren
id|ACPI_GPE_NUMBER_INFO
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|acpi_gbl_gpe_number_info
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Could not allocate the Gpe_number_info table&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_goto
id|error_exit2
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Initialize the GPE information and validation tables.  A goal of these&n;&t; * tables is to hide the fact that there are two separate GPE register sets&n;&t; * in a given gpe hardware block, the status registers occupy the first half,&n;&t; * and the enable registers occupy the second half.  Another goal is to hide&n;&t; * the fact that there may be multiple GPE hardware blocks.&n;&t; */
id|gpe_register
op_assign
l_int|0
suffix:semicolon
id|gpe_number_index
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|gpe_block
op_assign
l_int|0
suffix:semicolon
id|gpe_block
OL
id|ACPI_MAX_GPE_BLOCKS
suffix:semicolon
id|gpe_block
op_increment
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|acpi_gbl_gpe_block_info
(braket
id|gpe_block
)braket
dot
id|register_count
suffix:semicolon
id|i
op_increment
)paren
(brace
id|gpe_register_info
op_assign
op_amp
id|acpi_gbl_gpe_register_info
(braket
id|gpe_register
)braket
suffix:semicolon
multiline_comment|/* Init the Register info for this entire GPE register (8 GPEs) */
id|gpe_register_info-&gt;base_gpe_number
op_assign
(paren
id|u8
)paren
(paren
id|acpi_gbl_gpe_block_info
(braket
id|gpe_block
)braket
dot
id|block_base_number
op_plus
(paren
id|ACPI_MUL_8
(paren
id|i
)paren
)paren
)paren
suffix:semicolon
id|gpe_register_info-&gt;status_addr
op_assign
(paren
id|u16
)paren
(paren
id|acpi_gbl_gpe_block_info
(braket
id|gpe_block
)braket
dot
id|block_address
op_plus
id|i
)paren
suffix:semicolon
id|gpe_register_info-&gt;enable_addr
op_assign
(paren
id|u16
)paren
(paren
id|acpi_gbl_gpe_block_info
(braket
id|gpe_block
)braket
dot
id|block_address
op_plus
id|i
op_plus
id|acpi_gbl_gpe_block_info
(braket
id|gpe_block
)braket
dot
id|register_count
)paren
suffix:semicolon
multiline_comment|/* Init the Index mapping info for each GPE number within this register */
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
l_int|8
suffix:semicolon
id|j
op_increment
)paren
(brace
id|gpe_number
op_assign
id|gpe_register_info-&gt;base_gpe_number
op_plus
id|j
suffix:semicolon
id|acpi_gbl_gpe_number_to_index
(braket
id|gpe_number
)braket
dot
id|number_index
op_assign
(paren
id|u8
)paren
id|gpe_number_index
suffix:semicolon
id|acpi_gbl_gpe_number_info
(braket
id|gpe_number_index
)braket
dot
id|bit_mask
op_assign
id|acpi_gbl_decode_to8bit
(braket
id|j
)braket
suffix:semicolon
id|gpe_number_index
op_increment
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t;&t; * Clear the status/enable registers.  Note that status registers&n;&t;&t;&t; * are cleared by writing a &squot;1&squot;, while enable registers are cleared&n;&t;&t;&t; * by writing a &squot;0&squot;.&n;&t;&t;&t; */
id|acpi_os_write_port
(paren
id|gpe_register_info-&gt;enable_addr
comma
l_int|0x00
comma
l_int|8
)paren
suffix:semicolon
id|acpi_os_write_port
(paren
id|gpe_register_info-&gt;status_addr
comma
l_int|0xFF
comma
l_int|8
)paren
suffix:semicolon
id|gpe_register
op_increment
suffix:semicolon
)brace
)brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;GPE registers: %X@%8.8X%8.8X (Blk0) %X@%8.8X%8.8X (Blk1)&bslash;n&quot;
comma
id|acpi_gbl_gpe_block_info
(braket
l_int|0
)braket
dot
id|register_count
comma
id|ACPI_HIDWORD
(paren
id|acpi_gbl_FADT-&gt;Xgpe0_blk.address
)paren
comma
id|ACPI_LODWORD
(paren
id|acpi_gbl_FADT-&gt;Xgpe0_blk.address
)paren
comma
id|acpi_gbl_gpe_block_info
(braket
l_int|1
)braket
dot
id|register_count
comma
id|ACPI_HIDWORD
(paren
id|acpi_gbl_FADT-&gt;Xgpe1_blk.address
)paren
comma
id|ACPI_LODWORD
(paren
id|acpi_gbl_FADT-&gt;Xgpe1_blk.address
)paren
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
multiline_comment|/* Error cleanup */
id|error_exit2
suffix:colon
id|ACPI_MEM_FREE
(paren
id|acpi_gbl_gpe_register_info
)paren
suffix:semicolon
id|error_exit1
suffix:colon
id|ACPI_MEM_FREE
(paren
id|acpi_gbl_gpe_number_to_index
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ev_save_method_info&n; *&n; * PARAMETERS:  None&n; *&n; * RETURN:      None&n; *&n; * DESCRIPTION: Called from Acpi_walk_namespace. Expects each object to be a&n; *              control method under the _GPE portion of the namespace.&n; *              Extract the name and GPE type from the object, saving this&n; *              information for quick lookup during GPE dispatch&n; *&n; *              The name of each GPE control method is of the form:&n; *                  &quot;_Lnn&quot; or &quot;_Enn&quot;&n; *              Where:&n; *                  L      - means that the GPE is level triggered&n; *                  E      - means that the GPE is edge triggered&n; *                  nn     - is the GPE number [in HEX]&n; *&n; ******************************************************************************/
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
id|u32
id|gpe_number
suffix:semicolon
id|u32
id|gpe_number_index
suffix:semicolon
id|NATIVE_CHAR
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
id|ACPI_FUNCTION_NAME
(paren
l_string|&quot;Ev_save_method_info&quot;
)paren
suffix:semicolon
multiline_comment|/* Extract the name from the object and convert to a string */
id|ACPI_MOVE_UNALIGNED32_TO_32
(paren
id|name
comma
op_amp
(paren
(paren
id|acpi_namespace_node
op_star
)paren
id|obj_handle
)paren
op_member_access_from_pointer
id|name
)paren
suffix:semicolon
id|name
(braket
id|ACPI_NAME_SIZE
)braket
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * Edge/Level determination is based on the 2nd character of the method name&n;&t; */
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
r_return
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
l_string|&quot;Could not extract GPE number from name: %s (name not of form _Lnn or _Enn)&bslash;n&quot;
comma
id|name
)paren
)paren
suffix:semicolon
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/* Get GPE index and ensure that we have a valid GPE number */
id|gpe_number_index
op_assign
id|acpi_ev_get_gpe_number_index
(paren
id|gpe_number
)paren
suffix:semicolon
r_if
c_cond
(paren
id|gpe_number_index
op_eq
id|ACPI_GPE_INVALID
)paren
(brace
multiline_comment|/* Not valid, all we can do here is ignore it */
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Now we can add this information to the Gpe_info block&n;&t; * for use during dispatch of this GPE.&n;&t; */
id|acpi_gbl_gpe_number_info
(braket
id|gpe_number_index
)braket
dot
id|type
op_assign
id|type
suffix:semicolon
id|acpi_gbl_gpe_number_info
(braket
id|gpe_number_index
)braket
dot
id|method_handle
op_assign
id|obj_handle
suffix:semicolon
multiline_comment|/*&n;&t; * Enable the GPE (SCIs should be disabled at this point)&n;&t; */
id|acpi_hw_enable_gpe
(paren
id|gpe_number
)paren
suffix:semicolon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;Registered GPE method %s as GPE number %X&bslash;n&quot;
comma
id|name
comma
id|gpe_number
)paren
)paren
suffix:semicolon
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ev_init_gpe_control_methods&n; *&n; * PARAMETERS:  None&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Obtain the control methods associated with the GPEs.&n; *              NOTE: Must be called AFTER namespace initialization!&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ev_init_gpe_control_methods
id|acpi_ev_init_gpe_control_methods
(paren
r_void
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;Ev_init_gpe_control_methods&quot;
)paren
suffix:semicolon
multiline_comment|/* Get a permanent handle to the _GPE object */
id|status
op_assign
id|acpi_get_handle
(paren
l_int|NULL
comma
l_string|&quot;&bslash;&bslash;_GPE&quot;
comma
op_amp
id|acpi_gbl_gpe_obj_handle
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
multiline_comment|/* Traverse the namespace under &bslash;_GPE to find all methods there */
id|status
op_assign
id|acpi_walk_namespace
(paren
id|ACPI_TYPE_METHOD
comma
id|acpi_gbl_gpe_obj_handle
comma
id|ACPI_UINT32_MAX
comma
id|acpi_ev_save_method_info
comma
l_int|NULL
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
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ev_gpe_detect&n; *&n; * PARAMETERS:  None&n; *&n; * RETURN:      INTERRUPT_HANDLED or INTERRUPT_NOT_HANDLED&n; *&n; * DESCRIPTION: Detect if any GP events have occurred.  This function is&n; *              executed at interrupt level.&n; *&n; ******************************************************************************/
id|u32
DECL|function|acpi_ev_gpe_detect
id|acpi_ev_gpe_detect
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
id|i
suffix:semicolon
id|u32
id|j
suffix:semicolon
id|u8
id|enabled_status_byte
suffix:semicolon
id|u8
id|bit_mask
suffix:semicolon
id|ACPI_GPE_REGISTER_INFO
op_star
id|gpe_register_info
suffix:semicolon
id|ACPI_FUNCTION_NAME
(paren
l_string|&quot;Ev_gpe_detect&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Read all of the 8-bit GPE status and enable registers&n;&t; * in both of the register blocks, saving all of it.&n;&t; * Find all currently active GP events.&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|acpi_gbl_gpe_register_count
suffix:semicolon
id|i
op_increment
)paren
(brace
id|gpe_register_info
op_assign
op_amp
id|acpi_gbl_gpe_register_info
(braket
id|i
)braket
suffix:semicolon
id|acpi_os_read_port
(paren
id|gpe_register_info-&gt;status_addr
comma
op_amp
id|gpe_register_info-&gt;status
comma
l_int|8
)paren
suffix:semicolon
id|acpi_os_read_port
(paren
id|gpe_register_info-&gt;enable_addr
comma
op_amp
id|gpe_register_info-&gt;enable
comma
l_int|8
)paren
suffix:semicolon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_INTERRUPTS
comma
l_string|&quot;GPE block at %X - Enable %08X Status %08X&bslash;n&quot;
comma
id|gpe_register_info-&gt;enable_addr
comma
id|gpe_register_info-&gt;status
comma
id|gpe_register_info-&gt;enable
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
id|gpe_register_info-&gt;status
op_amp
id|gpe_register_info-&gt;enable
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
comma
id|bit_mask
op_assign
l_int|1
suffix:semicolon
id|j
OL
l_int|8
suffix:semicolon
id|j
op_increment
comma
id|bit_mask
op_lshift_assign
l_int|1
)paren
(brace
multiline_comment|/* Examine one GPE bit */
r_if
c_cond
(paren
id|enabled_status_byte
op_amp
id|bit_mask
)paren
(brace
multiline_comment|/*&n;&t;&t;&t;&t; * Found an active GPE.  Dispatch the event to a handler&n;&t;&t;&t;&t; * or method.&n;&t;&t;&t;&t; */
id|int_status
op_or_assign
id|acpi_ev_gpe_dispatch
(paren
id|gpe_register_info-&gt;base_gpe_number
op_plus
id|j
)paren
suffix:semicolon
)brace
)brace
)brace
r_return
(paren
id|int_status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ev_asynch_execute_gpe_method&n; *&n; * PARAMETERS:  Gpe_number      - The 0-based GPE number&n; *&n; * RETURN:      None&n; *&n; * DESCRIPTION: Perform the actual execution of a GPE control method.  This&n; *              function is called from an invocation of Acpi_os_queue_for_execution&n; *              (and therefore does NOT execute at interrupt level) so that&n; *              the control method itself is not executed in the context of&n; *              the SCI interrupt handler.&n; *&n; ******************************************************************************/
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
id|u32
id|gpe_number
op_assign
(paren
id|u32
)paren
id|ACPI_TO_INTEGER
(paren
id|context
)paren
suffix:semicolon
id|u32
id|gpe_number_index
suffix:semicolon
id|ACPI_GPE_NUMBER_INFO
id|gpe_info
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;Ev_asynch_execute_gpe_method&quot;
)paren
suffix:semicolon
id|gpe_number_index
op_assign
id|acpi_ev_get_gpe_number_index
(paren
id|gpe_number
)paren
suffix:semicolon
r_if
c_cond
(paren
id|gpe_number_index
op_eq
id|ACPI_GPE_INVALID
)paren
(brace
id|return_VOID
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Take a snapshot of the GPE info for this level - we copy the&n;&t; * info to prevent a race condition with Remove_handler.&n;&t; */
r_if
c_cond
(paren
id|ACPI_FAILURE
(paren
id|acpi_ut_acquire_mutex
(paren
id|ACPI_MTX_EVENTS
)paren
)paren
)paren
(brace
id|return_VOID
suffix:semicolon
)brace
id|gpe_info
op_assign
id|acpi_gbl_gpe_number_info
(braket
id|gpe_number_index
)braket
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_FAILURE
(paren
id|acpi_ut_release_mutex
(paren
id|ACPI_MTX_EVENTS
)paren
)paren
)paren
(brace
id|return_VOID
suffix:semicolon
)brace
r_if
c_cond
(paren
id|gpe_info.method_handle
)paren
(brace
multiline_comment|/*&n;&t;&t; * Invoke the GPE Method (_Lxx, _Exx):&n;&t;&t; * (Evaluate the _Lxx/_Exx control method that corresponds to this GPE.)&n;&t;&t; */
id|acpi_ns_evaluate_by_handle
(paren
id|gpe_info.method_handle
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|gpe_info.type
op_amp
id|ACPI_EVENT_LEVEL_TRIGGERED
)paren
(brace
multiline_comment|/*&n;&t;&t; * GPE is level-triggered, we clear the GPE status bit after handling&n;&t;&t; * the event.&n;&t;&t; */
id|acpi_hw_clear_gpe
(paren
id|gpe_number
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Enable the GPE.&n;&t; */
id|acpi_hw_enable_gpe
(paren
id|gpe_number
)paren
suffix:semicolon
id|return_VOID
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ev_gpe_dispatch&n; *&n; * PARAMETERS:  Gpe_number      - The 0-based GPE number&n; *&n; * RETURN:      INTERRUPT_HANDLED or INTERRUPT_NOT_HANDLED&n; *&n; * DESCRIPTION: Dispatch a General Purpose Event to either a function (e.g. EC)&n; *              or method (e.g. _Lxx/_Exx) handler.  This function executes&n; *              at interrupt level.&n; *&n; ******************************************************************************/
id|u32
DECL|function|acpi_ev_gpe_dispatch
id|acpi_ev_gpe_dispatch
(paren
id|u32
id|gpe_number
)paren
(brace
id|u32
id|gpe_number_index
suffix:semicolon
id|ACPI_GPE_NUMBER_INFO
op_star
id|gpe_info
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;Ev_gpe_dispatch&quot;
)paren
suffix:semicolon
id|gpe_number_index
op_assign
id|acpi_ev_get_gpe_number_index
(paren
id|gpe_number
)paren
suffix:semicolon
r_if
c_cond
(paren
id|gpe_number_index
op_eq
id|ACPI_GPE_INVALID
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Invalid event, GPE[%X].&bslash;n&quot;
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
multiline_comment|/*&n;&t; * We don&squot;t have to worry about mutex on Gpe_info because we are&n;&t; * executing at interrupt level.&n;&t; */
id|gpe_info
op_assign
op_amp
id|acpi_gbl_gpe_number_info
(braket
id|gpe_number_index
)braket
suffix:semicolon
multiline_comment|/*&n;&t; * If edge-triggered, clear the GPE status bit now.  Note that&n;&t; * level-triggered events are cleared after the GPE is serviced.&n;&t; */
r_if
c_cond
(paren
id|gpe_info-&gt;type
op_amp
id|ACPI_EVENT_EDGE_TRIGGERED
)paren
(brace
id|acpi_hw_clear_gpe
(paren
id|gpe_number
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Dispatch the GPE to either an installed handler, or the control&n;&t; * method associated with this GPE (_Lxx or _Exx).&n;&t; * If a handler exists, we invoke it and do not attempt to run the method.&n;&t; * If there is neither a handler nor a method, we disable the level to&n;&t; * prevent further events from coming in here.&n;&t; */
r_if
c_cond
(paren
id|gpe_info-&gt;handler
)paren
(brace
multiline_comment|/* Invoke the installed handler (at interrupt level) */
id|gpe_info-&gt;handler
(paren
id|gpe_info-&gt;context
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|gpe_info-&gt;method_handle
)paren
(brace
multiline_comment|/*&n;&t;&t; * Execute the method associated with the GPE.&n;&t;&t; */
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
id|ACPI_TO_POINTER
(paren
id|gpe_number
)paren
)paren
)paren
)paren
(brace
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;Acpi_ev_gpe_dispatch: Unable to queue handler for GPE[%X], disabling event&bslash;n&quot;
comma
id|gpe_number
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * Disable the GPE on error.  The GPE will remain disabled until the ACPI&n;&t;&t;&t; * Core Subsystem is restarted, or the handler is reinstalled.&n;&t;&t;&t; */
id|acpi_hw_disable_gpe
(paren
id|gpe_number
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* No handler or method to run! */
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;Acpi_ev_gpe_dispatch: No handler or method for GPE[%X], disabling event&bslash;n&quot;
comma
id|gpe_number
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Disable the GPE.  The GPE will remain disabled until the ACPI&n;&t;&t; * Core Subsystem is restarted, or the handler is reinstalled.&n;&t;&t; */
id|acpi_hw_disable_gpe
(paren
id|gpe_number
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * It is now safe to clear level-triggered evnets.&n;&t; */
r_if
c_cond
(paren
id|gpe_info-&gt;type
op_amp
id|ACPI_EVENT_LEVEL_TRIGGERED
)paren
(brace
id|acpi_hw_clear_gpe
(paren
id|gpe_number
)paren
suffix:semicolon
)brace
id|return_VALUE
(paren
id|ACPI_INTERRUPT_HANDLED
)paren
suffix:semicolon
)brace
eof
