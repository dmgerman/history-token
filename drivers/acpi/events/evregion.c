multiline_comment|/******************************************************************************&n; *&n; * Module Name: evregion - ACPI address_space (op_region) handler dispatch&n; *&n; *****************************************************************************/
multiline_comment|/*&n; * Copyright (C) 2000 - 2003, R. Byron Moore&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. Redistributions in binary form must reproduce at minimum a disclaimer&n; *    substantially similar to the &quot;NO WARRANTY&quot; disclaimer below&n; *    (&quot;Disclaimer&quot;) and any redistribution must be conditioned upon&n; *    including a substantially similar Disclaimer requirement for further&n; *    binary redistribution.&n; * 3. Neither the names of the above-listed copyright holders nor the names&n; *    of any contributors may be used to endorse or promote products derived&n; *    from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;) version 2 as published by the Free&n; * Software Foundation.&n; *&n; * NO WARRANTY&n; * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS&n; * &quot;AS IS&quot; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT&n; * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR&n; * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT&n; * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,&n; * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING&n; * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE&n; * POSSIBILITY OF SUCH DAMAGES.&n; */
macro_line|#include &lt;acpi/acpi.h&gt;
macro_line|#include &lt;acpi/acevents.h&gt;
macro_line|#include &lt;acpi/acnamesp.h&gt;
macro_line|#include &lt;acpi/acinterp.h&gt;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_EVENTS
id|ACPI_MODULE_NAME
(paren
l_string|&quot;evregion&quot;
)paren
DECL|macro|ACPI_NUM_DEFAULT_SPACES
mdefine_line|#define ACPI_NUM_DEFAULT_SPACES     4
DECL|variable|acpi_gbl_default_address_spaces
id|u8
id|acpi_gbl_default_address_spaces
(braket
id|ACPI_NUM_DEFAULT_SPACES
)braket
op_assign
(brace
id|ACPI_ADR_SPACE_SYSTEM_MEMORY
comma
id|ACPI_ADR_SPACE_SYSTEM_IO
comma
id|ACPI_ADR_SPACE_PCI_CONFIG
comma
id|ACPI_ADR_SPACE_DATA_TABLE
)brace
suffix:semicolon
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ev_init_address_spaces&n; *&n; * PARAMETERS:  None&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Installs the core subsystem default address space handlers.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ev_init_address_spaces
id|acpi_ev_init_address_spaces
(paren
r_void
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
id|acpi_native_uint
id|i
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ev_init_address_spaces&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * All address spaces (PCI Config, EC, SMBus) are scope dependent&n;&t; * and registration must occur for a specific device.&n;&t; *&n;&t; * In the case of the system memory and IO address spaces there is currently&n;&t; * no device associated with the address space.  For these we use the root.&n;&t; *&n;&t; * We install the default PCI config space handler at the root so&n;&t; * that this space is immediately available even though the we have&n;&t; * not enumerated all the PCI Root Buses yet.  This is to conform&n;&t; * to the ACPI specification which states that the PCI config&n;&t; * space must be always available -- even though we are nowhere&n;&t; * near ready to find the PCI root buses at this point.&n;&t; *&n;&t; * NOTE: We ignore AE_ALREADY_EXISTS because this means that a handler&n;&t; * has already been installed (via acpi_install_address_space_handler).&n;&t; * Similar for AE_SAME_HANDLER.&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|ACPI_NUM_DEFAULT_SPACES
suffix:semicolon
id|i
op_increment
)paren
(brace
id|status
op_assign
id|acpi_install_address_space_handler
(paren
(paren
id|acpi_handle
)paren
id|acpi_gbl_root_node
comma
id|acpi_gbl_default_address_spaces
(braket
id|i
)braket
comma
id|ACPI_DEFAULT_HANDLER
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|status
)paren
(brace
r_case
id|AE_OK
suffix:colon
r_case
id|AE_SAME_HANDLER
suffix:colon
r_case
id|AE_ALREADY_EXISTS
suffix:colon
multiline_comment|/* These exceptions are all OK */
r_break
suffix:semicolon
r_default
suffix:colon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
)brace
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ev_execute_reg_method&n; *&n; * PARAMETERS:  region_obj          - Object structure&n; *              Function            - On (1) or Off (0)&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Execute _REG method for a region&n; *&n; ******************************************************************************/
r_static
id|acpi_status
DECL|function|acpi_ev_execute_reg_method
id|acpi_ev_execute_reg_method
(paren
r_union
id|acpi_operand_object
op_star
id|region_obj
comma
id|u32
id|function
)paren
(brace
r_union
id|acpi_operand_object
op_star
id|params
(braket
l_int|3
)braket
suffix:semicolon
r_union
id|acpi_operand_object
op_star
id|region_obj2
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ev_execute_reg_method&quot;
)paren
suffix:semicolon
id|region_obj2
op_assign
id|acpi_ns_get_secondary_object
(paren
id|region_obj
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|region_obj2
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_NOT_EXIST
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|region_obj2-&gt;extra.method_REG
op_eq
l_int|NULL
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * _REG method has two arguments&n;&t; * Arg0:   Integer: Operation region space ID&n;&t; *          Same value as region_obj-&gt;Region.space_id&n;&t; * Arg1:   Integer: connection status&n;&t; *          1 for connecting the handler,&n;&t; *          0 for disconnecting the handler&n;&t; *          Passed as a parameter&n;&t; */
id|params
(braket
l_int|0
)braket
op_assign
id|acpi_ut_create_internal_object
(paren
id|ACPI_TYPE_INTEGER
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|params
(braket
l_int|0
)braket
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
)brace
id|params
(braket
l_int|1
)braket
op_assign
id|acpi_ut_create_internal_object
(paren
id|ACPI_TYPE_INTEGER
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|params
(braket
l_int|1
)braket
)paren
(brace
id|status
op_assign
id|AE_NO_MEMORY
suffix:semicolon
r_goto
id|cleanup
suffix:semicolon
)brace
multiline_comment|/* Set up the parameter objects */
id|params
(braket
l_int|0
)braket
op_member_access_from_pointer
id|integer.value
op_assign
id|region_obj-&gt;region.space_id
suffix:semicolon
id|params
(braket
l_int|1
)braket
op_member_access_from_pointer
id|integer.value
op_assign
id|function
suffix:semicolon
id|params
(braket
l_int|2
)braket
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Execute the method, no return value */
id|ACPI_DEBUG_EXEC
c_func
(paren
id|acpi_ut_display_init_pathname
(paren
id|ACPI_TYPE_METHOD
comma
id|region_obj2-&gt;extra.method_REG
comma
l_int|NULL
)paren
)paren
suffix:semicolon
id|status
op_assign
id|acpi_ns_evaluate_by_handle
(paren
id|region_obj2-&gt;extra.method_REG
comma
id|params
comma
l_int|NULL
)paren
suffix:semicolon
id|acpi_ut_remove_reference
(paren
id|params
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|cleanup
suffix:colon
id|acpi_ut_remove_reference
(paren
id|params
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ev_address_space_dispatch&n; *&n; * PARAMETERS:  region_obj          - internal region object&n; *              space_id            - ID of the address space (0-255)&n; *              Function            - Read or Write operation&n; *              Address             - Where in the space to read or write&n; *              bit_width           - Field width in bits (8, 16, 32, or 64)&n; *              Value               - Pointer to in or out value&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Dispatch an address space or operation region access to&n; *              a previously installed handler.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ev_address_space_dispatch
id|acpi_ev_address_space_dispatch
(paren
r_union
id|acpi_operand_object
op_star
id|region_obj
comma
id|u32
id|function
comma
id|acpi_physical_address
id|address
comma
id|u32
id|bit_width
comma
r_void
op_star
id|value
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
id|acpi_status
id|status2
suffix:semicolon
id|acpi_adr_space_handler
id|handler
suffix:semicolon
id|acpi_adr_space_setup
id|region_setup
suffix:semicolon
r_union
id|acpi_operand_object
op_star
id|handler_desc
suffix:semicolon
r_union
id|acpi_operand_object
op_star
id|region_obj2
suffix:semicolon
r_void
op_star
id|region_context
op_assign
l_int|NULL
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ev_address_space_dispatch&quot;
)paren
suffix:semicolon
id|region_obj2
op_assign
id|acpi_ns_get_secondary_object
(paren
id|region_obj
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|region_obj2
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_NOT_EXIST
)paren
suffix:semicolon
)brace
multiline_comment|/* Ensure that there is a handler associated with this region */
id|handler_desc
op_assign
id|region_obj-&gt;region.address_space
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|handler_desc
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;no handler for region(%p) [%s]&bslash;n&quot;
comma
id|region_obj
comma
id|acpi_ut_get_region_name
(paren
id|region_obj-&gt;region.space_id
)paren
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_NOT_EXIST
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * It may be the case that the region has never been initialized&n;&t; * Some types of regions require special init code&n;&t; */
r_if
c_cond
(paren
op_logical_neg
(paren
id|region_obj-&gt;region.flags
op_amp
id|AOPOBJ_SETUP_COMPLETE
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t; * This region has not been initialized yet, do it&n;&t;&t; */
id|region_setup
op_assign
id|handler_desc-&gt;address_space.setup
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|region_setup
)paren
(brace
multiline_comment|/* No initialization routine, exit with error */
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;No init routine for region(%p) [%s]&bslash;n&quot;
comma
id|region_obj
comma
id|acpi_ut_get_region_name
(paren
id|region_obj-&gt;region.space_id
)paren
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_NOT_EXIST
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * We must exit the interpreter because the region setup will potentially&n;&t;&t; * execute control methods (e.g., _REG method for this region)&n;&t;&t; */
id|acpi_ex_exit_interpreter
(paren
)paren
suffix:semicolon
id|status
op_assign
id|region_setup
(paren
id|region_obj
comma
id|ACPI_REGION_ACTIVATE
comma
id|handler_desc-&gt;address_space.context
comma
op_amp
id|region_context
)paren
suffix:semicolon
multiline_comment|/* Re-enter the interpreter */
id|status2
op_assign
id|acpi_ex_enter_interpreter
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_FAILURE
(paren
id|status2
)paren
)paren
(brace
id|return_ACPI_STATUS
(paren
id|status2
)paren
suffix:semicolon
)brace
multiline_comment|/* Check for failure of the Region Setup */
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
l_string|&quot;Region Init: %s [%s]&bslash;n&quot;
comma
id|acpi_format_exception
(paren
id|status
)paren
comma
id|acpi_ut_get_region_name
(paren
id|region_obj-&gt;region.space_id
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
multiline_comment|/*&n;&t;&t; * Region initialization may have been completed by region_setup&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
(paren
id|region_obj-&gt;region.flags
op_amp
id|AOPOBJ_SETUP_COMPLETE
)paren
)paren
(brace
id|region_obj-&gt;region.flags
op_or_assign
id|AOPOBJ_SETUP_COMPLETE
suffix:semicolon
r_if
c_cond
(paren
id|region_obj2-&gt;extra.region_context
)paren
(brace
multiline_comment|/* The handler for this region was already installed */
id|ACPI_MEM_FREE
(paren
id|region_context
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t;&t;&t; * Save the returned context for use in all accesses to&n;&t;&t;&t;&t; * this particular region&n;&t;&t;&t;&t; */
id|region_obj2-&gt;extra.region_context
op_assign
id|region_context
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/* We have everything we need, we can invoke the address space handler */
id|handler
op_assign
id|handler_desc-&gt;address_space.handler
suffix:semicolon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_OPREGION
comma
l_string|&quot;Handler %p (@%p) Address %8.8X%8.8X [%s]&bslash;n&quot;
comma
op_amp
id|region_obj-&gt;region.address_space-&gt;address_space
comma
id|handler
comma
id|ACPI_FORMAT_UINT64
(paren
id|address
)paren
comma
id|acpi_ut_get_region_name
(paren
id|region_obj-&gt;region.space_id
)paren
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|handler_desc-&gt;address_space.flags
op_amp
id|ACPI_ADDR_HANDLER_DEFAULT_INSTALLED
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t; * For handlers other than the default (supplied) handlers, we must&n;&t;&t; * exit the interpreter because the handler *might* block -- we don&squot;t&n;&t;&t; * know what it will do, so we can&squot;t hold the lock on the intepreter.&n;&t;&t; */
id|acpi_ex_exit_interpreter
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Call the handler */
id|status
op_assign
id|handler
(paren
id|function
comma
id|address
comma
id|bit_width
comma
id|value
comma
id|handler_desc-&gt;address_space.context
comma
id|region_obj2-&gt;extra.region_context
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
l_string|&quot;Handler for [%s] returned %s&bslash;n&quot;
comma
id|acpi_ut_get_region_name
(paren
id|region_obj-&gt;region.space_id
)paren
comma
id|acpi_format_exception
(paren
id|status
)paren
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|handler_desc-&gt;address_space.flags
op_amp
id|ACPI_ADDR_HANDLER_DEFAULT_INSTALLED
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t; * We just returned from a non-default handler, we must re-enter the&n;&t;&t; * interpreter&n;&t;&t; */
id|status2
op_assign
id|acpi_ex_enter_interpreter
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_FAILURE
(paren
id|status2
)paren
)paren
(brace
id|return_ACPI_STATUS
(paren
id|status2
)paren
suffix:semicolon
)brace
)brace
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ev_detach_region&n; *&n; * PARAMETERS:  region_obj      - Region Object&n; *              acpi_ns_is_locked - Namespace Region Already Locked?&n; *&n; * RETURN:      None&n; *&n; * DESCRIPTION: Break the association between the handler and the region&n; *              this is a two way association.&n; *&n; ******************************************************************************/
r_void
DECL|function|acpi_ev_detach_region
id|acpi_ev_detach_region
c_func
(paren
r_union
id|acpi_operand_object
op_star
id|region_obj
comma
id|u8
id|acpi_ns_is_locked
)paren
(brace
r_union
id|acpi_operand_object
op_star
id|handler_obj
suffix:semicolon
r_union
id|acpi_operand_object
op_star
id|obj_desc
suffix:semicolon
r_union
id|acpi_operand_object
op_star
op_star
id|last_obj_ptr
suffix:semicolon
id|acpi_adr_space_setup
id|region_setup
suffix:semicolon
r_void
op_star
op_star
id|region_context
suffix:semicolon
r_union
id|acpi_operand_object
op_star
id|region_obj2
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ev_detach_region&quot;
)paren
suffix:semicolon
id|region_obj2
op_assign
id|acpi_ns_get_secondary_object
(paren
id|region_obj
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|region_obj2
)paren
(brace
id|return_VOID
suffix:semicolon
)brace
id|region_context
op_assign
op_amp
id|region_obj2-&gt;extra.region_context
suffix:semicolon
multiline_comment|/* Get the address handler from the region object */
id|handler_obj
op_assign
id|region_obj-&gt;region.address_space
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|handler_obj
)paren
(brace
multiline_comment|/* This region has no handler, all done */
id|return_VOID
suffix:semicolon
)brace
multiline_comment|/* Find this region in the handler&squot;s list */
id|obj_desc
op_assign
id|handler_obj-&gt;address_space.region_list
suffix:semicolon
id|last_obj_ptr
op_assign
op_amp
id|handler_obj-&gt;address_space.region_list
suffix:semicolon
r_while
c_loop
(paren
id|obj_desc
)paren
(brace
multiline_comment|/* Is this the correct Region? */
r_if
c_cond
(paren
id|obj_desc
op_eq
id|region_obj
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_OPREGION
comma
l_string|&quot;Removing Region %p from address handler %p&bslash;n&quot;
comma
id|region_obj
comma
id|handler_obj
)paren
)paren
suffix:semicolon
multiline_comment|/* This is it, remove it from the handler&squot;s list */
op_star
id|last_obj_ptr
op_assign
id|obj_desc-&gt;region.next
suffix:semicolon
id|obj_desc-&gt;region.next
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Must clear field */
r_if
c_cond
(paren
id|acpi_ns_is_locked
)paren
(brace
id|status
op_assign
id|acpi_ut_release_mutex
(paren
id|ACPI_MTX_NAMESPACE
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
multiline_comment|/* Now stop region accesses by executing the _REG method */
id|status
op_assign
id|acpi_ev_execute_reg_method
(paren
id|region_obj
comma
l_int|0
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
l_string|&quot;%s from region _REG, [%s]&bslash;n&quot;
comma
id|acpi_format_exception
(paren
id|status
)paren
comma
id|acpi_ut_get_region_name
(paren
id|region_obj-&gt;region.space_id
)paren
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|acpi_ns_is_locked
)paren
(brace
id|status
op_assign
id|acpi_ut_acquire_mutex
(paren
id|ACPI_MTX_NAMESPACE
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
multiline_comment|/* Call the setup handler with the deactivate notification */
id|region_setup
op_assign
id|handler_obj-&gt;address_space.setup
suffix:semicolon
id|status
op_assign
id|region_setup
(paren
id|region_obj
comma
id|ACPI_REGION_DEACTIVATE
comma
id|handler_obj-&gt;address_space.context
comma
id|region_context
)paren
suffix:semicolon
multiline_comment|/* Init routine may fail, Just ignore errors */
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
l_string|&quot;%s from region init, [%s]&bslash;n&quot;
comma
id|acpi_format_exception
(paren
id|status
)paren
comma
id|acpi_ut_get_region_name
(paren
id|region_obj-&gt;region.space_id
)paren
)paren
)paren
suffix:semicolon
)brace
id|region_obj-&gt;region.flags
op_and_assign
op_complement
(paren
id|AOPOBJ_SETUP_COMPLETE
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * Remove handler reference in the region&n;&t;&t;&t; *&n;&t;&t;&t; * NOTE: this doesn&squot;t mean that the region goes away&n;&t;&t;&t; * The region is just inaccessible as indicated to&n;&t;&t;&t; * the _REG method&n;&t;&t;&t; *&n;&t;&t;&t; * If the region is on the handler&squot;s list&n;&t;&t;&t; * this better be the region&squot;s handler&n;&t;&t;&t; */
id|region_obj-&gt;region.address_space
op_assign
l_int|NULL
suffix:semicolon
id|acpi_ut_remove_reference
(paren
id|handler_obj
)paren
suffix:semicolon
id|return_VOID
suffix:semicolon
)brace
multiline_comment|/* Walk the linked list of handlers */
id|last_obj_ptr
op_assign
op_amp
id|obj_desc-&gt;region.next
suffix:semicolon
id|obj_desc
op_assign
id|obj_desc-&gt;region.next
suffix:semicolon
)brace
multiline_comment|/* If we get here, the region was not in the handler&squot;s region list */
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_OPREGION
comma
l_string|&quot;Cannot remove region %p from address handler %p&bslash;n&quot;
comma
id|region_obj
comma
id|handler_obj
)paren
)paren
suffix:semicolon
id|return_VOID
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ev_attach_region&n; *&n; * PARAMETERS:  handler_obj     - Handler Object&n; *              region_obj      - Region Object&n; *              acpi_ns_is_locked - Namespace Region Already Locked?&n; *&n; * RETURN:      None&n; *&n; * DESCRIPTION: Create the association between the handler and the region&n; *              this is a two way association.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ev_attach_region
id|acpi_ev_attach_region
(paren
r_union
id|acpi_operand_object
op_star
id|handler_obj
comma
r_union
id|acpi_operand_object
op_star
id|region_obj
comma
id|u8
id|acpi_ns_is_locked
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
id|acpi_status
id|status2
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ev_attach_region&quot;
)paren
suffix:semicolon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_OPREGION
comma
l_string|&quot;Adding Region %p to address handler %p [%s]&bslash;n&quot;
comma
id|region_obj
comma
id|handler_obj
comma
id|acpi_ut_get_region_name
(paren
id|region_obj-&gt;region.space_id
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/* Link this region to the front of the handler&squot;s list */
id|region_obj-&gt;region.next
op_assign
id|handler_obj-&gt;address_space.region_list
suffix:semicolon
id|handler_obj-&gt;address_space.region_list
op_assign
id|region_obj
suffix:semicolon
multiline_comment|/* Install the region&squot;s handler */
r_if
c_cond
(paren
id|region_obj-&gt;region.address_space
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_ALREADY_EXISTS
)paren
suffix:semicolon
)brace
id|region_obj-&gt;region.address_space
op_assign
id|handler_obj
suffix:semicolon
id|acpi_ut_add_reference
(paren
id|handler_obj
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Tell all users that this region is usable by running the _REG&n;&t; * method&n;&t; */
r_if
c_cond
(paren
id|acpi_ns_is_locked
)paren
(brace
id|status2
op_assign
id|acpi_ut_release_mutex
(paren
id|ACPI_MTX_NAMESPACE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_FAILURE
(paren
id|status2
)paren
)paren
(brace
id|return_ACPI_STATUS
(paren
id|status2
)paren
suffix:semicolon
)brace
)brace
id|status
op_assign
id|acpi_ev_execute_reg_method
(paren
id|region_obj
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|acpi_ns_is_locked
)paren
(brace
id|status2
op_assign
id|acpi_ut_acquire_mutex
(paren
id|ACPI_MTX_NAMESPACE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_FAILURE
(paren
id|status2
)paren
)paren
(brace
id|return_ACPI_STATUS
(paren
id|status2
)paren
suffix:semicolon
)brace
)brace
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ev_install_handler&n; *&n; * PARAMETERS:  Handle              - Node to be dumped&n; *              Level               - Nesting level of the handle&n; *              Context             - Passed into acpi_ns_walk_namespace&n; *&n; * DESCRIPTION: This routine installs an address handler into objects that are&n; *              of type Region or Device.&n; *&n; *              If the Object is a Device, and the device has a handler of&n; *              the same type then the search is terminated in that branch.&n; *&n; *              This is because the existing handler is closer in proximity&n; *              to any more regions than the one we are trying to install.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ev_install_handler
id|acpi_ev_install_handler
(paren
id|acpi_handle
id|obj_handle
comma
id|u32
id|level
comma
r_void
op_star
id|context
comma
r_void
op_star
op_star
id|return_value
)paren
(brace
r_union
id|acpi_operand_object
op_star
id|handler_obj
suffix:semicolon
r_union
id|acpi_operand_object
op_star
id|next_handler_obj
suffix:semicolon
r_union
id|acpi_operand_object
op_star
id|obj_desc
suffix:semicolon
r_struct
id|acpi_namespace_node
op_star
id|node
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_NAME
(paren
l_string|&quot;ev_install_handler&quot;
)paren
suffix:semicolon
id|handler_obj
op_assign
(paren
r_union
id|acpi_operand_object
op_star
)paren
id|context
suffix:semicolon
multiline_comment|/* Parameter validation */
r_if
c_cond
(paren
op_logical_neg
id|handler_obj
)paren
(brace
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/* Convert and validate the device handle */
id|node
op_assign
id|acpi_ns_map_handle_to_node
(paren
id|obj_handle
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|node
)paren
(brace
r_return
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * We only care about regions.and objects&n;&t; * that are allowed to have address space handlers&n;&t; */
r_if
c_cond
(paren
(paren
id|node-&gt;type
op_ne
id|ACPI_TYPE_DEVICE
)paren
op_logical_and
(paren
id|node-&gt;type
op_ne
id|ACPI_TYPE_REGION
)paren
op_logical_and
(paren
id|node
op_ne
id|acpi_gbl_root_node
)paren
)paren
(brace
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/* Check for an existing internal object */
id|obj_desc
op_assign
id|acpi_ns_get_attached_object
(paren
id|node
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|obj_desc
)paren
(brace
multiline_comment|/* No object, just exit */
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/* Devices are handled different than regions */
r_if
c_cond
(paren
id|ACPI_GET_OBJECT_TYPE
(paren
id|obj_desc
)paren
op_eq
id|ACPI_TYPE_DEVICE
)paren
(brace
multiline_comment|/* Check if this Device already has a handler for this address space */
id|next_handler_obj
op_assign
id|obj_desc-&gt;device.address_space
suffix:semicolon
r_while
c_loop
(paren
id|next_handler_obj
)paren
(brace
multiline_comment|/* Found a handler, is it for the same address space? */
r_if
c_cond
(paren
id|next_handler_obj-&gt;address_space.space_id
op_eq
id|handler_obj-&gt;address_space.space_id
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_OPREGION
comma
l_string|&quot;Found handler for region [%s] in device %p(%p) handler %p&bslash;n&quot;
comma
id|acpi_ut_get_region_name
(paren
id|handler_obj-&gt;address_space.space_id
)paren
comma
id|obj_desc
comma
id|next_handler_obj
comma
id|handler_obj
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t;&t; * Since the object we found it on was a device, then it&n;&t;&t;&t;&t; * means that someone has already installed a handler for&n;&t;&t;&t;&t; * the branch of the namespace from this device on.  Just&n;&t;&t;&t;&t; * bail out telling the walk routine to not traverse this&n;&t;&t;&t;&t; * branch.  This preserves the scoping rule for handlers.&n;&t;&t;&t;&t; */
r_return
(paren
id|AE_CTRL_DEPTH
)paren
suffix:semicolon
)brace
multiline_comment|/* Walk the linked list of handlers attached to this device */
id|next_handler_obj
op_assign
id|next_handler_obj-&gt;address_space.next
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * As long as the device didn&squot;t have a handler for this&n;&t;&t; * space we don&squot;t care about it.  We just ignore it and&n;&t;&t; * proceed.&n;&t;&t; */
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/* Object is a Region */
r_if
c_cond
(paren
id|obj_desc-&gt;region.space_id
op_ne
id|handler_obj-&gt;address_space.space_id
)paren
(brace
multiline_comment|/*&n;&t;&t; * This region is for a different address space&n;&t;&t; * -- just ignore it&n;&t;&t; */
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Now we have a region and it is for the handler&squot;s address&n;&t; * space type.&n;&t; *&n;&t; * First disconnect region for any previous handler (if any)&n;&t; */
id|acpi_ev_detach_region
(paren
id|obj_desc
comma
id|FALSE
)paren
suffix:semicolon
multiline_comment|/* Connect the region to the new handler */
id|status
op_assign
id|acpi_ev_attach_region
(paren
id|handler_obj
comma
id|obj_desc
comma
id|FALSE
)paren
suffix:semicolon
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
eof
