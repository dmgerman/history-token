multiline_comment|/******************************************************************************&n; *&n; * Module Name: evxfregn - External Interfaces, ACPI Operation Regions and&n; *                         Address Spaces.&n; *&n; *****************************************************************************/
multiline_comment|/*&n; * Copyright (C) 2000 - 2003, R. Byron Moore&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. Redistributions in binary form must reproduce at minimum a disclaimer&n; *    substantially similar to the &quot;NO WARRANTY&quot; disclaimer below&n; *    (&quot;Disclaimer&quot;) and any redistribution must be conditioned upon&n; *    including a substantially similar Disclaimer requirement for further&n; *    binary redistribution.&n; * 3. Neither the names of the above-listed copyright holders nor the names&n; *    of any contributors may be used to endorse or promote products derived&n; *    from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;) version 2 as published by the Free&n; * Software Foundation.&n; *&n; * NO WARRANTY&n; * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS&n; * &quot;AS IS&quot; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT&n; * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR&n; * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT&n; * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,&n; * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING&n; * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE&n; * POSSIBILITY OF SUCH DAMAGES.&n; */
macro_line|#include &lt;acpi/acpi.h&gt;
macro_line|#include &lt;acpi/acnamesp.h&gt;
macro_line|#include &lt;acpi/acevents.h&gt;
macro_line|#include &lt;acpi/acinterp.h&gt;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_EVENTS
id|ACPI_MODULE_NAME
(paren
l_string|&quot;evxfregn&quot;
)paren
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_install_address_space_handler&n; *&n; * PARAMETERS:  Device          - Handle for the device&n; *              space_id        - The address space ID&n; *              Handler         - Address of the handler&n; *              Setup           - Address of the setup function&n; *              Context         - Value passed to the handler on each access&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Install a handler for all op_regions of a given space_id.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_install_address_space_handler
id|acpi_install_address_space_handler
(paren
id|acpi_handle
id|device
comma
id|acpi_adr_space_type
id|space_id
comma
id|acpi_adr_space_handler
id|handler
comma
id|acpi_adr_space_setup
id|setup
comma
r_void
op_star
id|context
)paren
(brace
r_union
id|acpi_operand_object
op_star
id|obj_desc
suffix:semicolon
r_union
id|acpi_operand_object
op_star
id|handler_obj
suffix:semicolon
r_struct
id|acpi_namespace_node
op_star
id|node
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
id|acpi_object_type
id|type
suffix:semicolon
id|u16
id|flags
op_assign
l_int|0
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;acpi_install_address_space_handler&quot;
)paren
suffix:semicolon
multiline_comment|/* Parameter validation */
r_if
c_cond
(paren
op_logical_neg
id|device
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
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
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/* Convert and validate the device handle */
id|node
op_assign
id|acpi_ns_map_handle_to_node
(paren
id|device
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|node
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
multiline_comment|/*&n;&t; * This registration is valid for only the types below&n;&t; * and the root.  This is where the default handlers&n;&t; * get placed.&n;&t; */
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
id|ACPI_TYPE_PROCESSOR
)paren
op_logical_and
(paren
id|node-&gt;type
op_ne
id|ACPI_TYPE_THERMAL
)paren
op_logical_and
(paren
id|node
op_ne
id|acpi_gbl_root_node
)paren
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
r_if
c_cond
(paren
id|handler
op_eq
id|ACPI_DEFAULT_HANDLER
)paren
(brace
id|flags
op_assign
id|ACPI_ADDR_HANDLER_DEFAULT_INSTALLED
suffix:semicolon
r_switch
c_cond
(paren
id|space_id
)paren
(brace
r_case
id|ACPI_ADR_SPACE_SYSTEM_MEMORY
suffix:colon
id|handler
op_assign
id|acpi_ex_system_memory_space_handler
suffix:semicolon
id|setup
op_assign
id|acpi_ev_system_memory_region_setup
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_ADR_SPACE_SYSTEM_IO
suffix:colon
id|handler
op_assign
id|acpi_ex_system_io_space_handler
suffix:semicolon
id|setup
op_assign
id|acpi_ev_io_space_region_setup
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_ADR_SPACE_PCI_CONFIG
suffix:colon
id|handler
op_assign
id|acpi_ex_pci_config_space_handler
suffix:semicolon
id|setup
op_assign
id|acpi_ev_pci_config_region_setup
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_ADR_SPACE_CMOS
suffix:colon
id|handler
op_assign
id|acpi_ex_cmos_space_handler
suffix:semicolon
id|setup
op_assign
id|acpi_ev_cmos_region_setup
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_ADR_SPACE_PCI_BAR_TARGET
suffix:colon
id|handler
op_assign
id|acpi_ex_pci_bar_space_handler
suffix:semicolon
id|setup
op_assign
id|acpi_ev_pci_bar_region_setup
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_ADR_SPACE_DATA_TABLE
suffix:colon
id|handler
op_assign
id|acpi_ex_data_table_space_handler
suffix:semicolon
id|setup
op_assign
l_int|NULL
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|status
op_assign
id|AE_BAD_PARAMETER
suffix:semicolon
r_goto
id|unlock_and_exit
suffix:semicolon
)brace
)brace
multiline_comment|/* If the caller hasn&squot;t specified a setup routine, use the default */
r_if
c_cond
(paren
op_logical_neg
id|setup
)paren
(brace
id|setup
op_assign
id|acpi_ev_default_region_setup
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
id|obj_desc
)paren
(brace
multiline_comment|/*&n;&t;&t; * The attached device object already exists.&n;&t;&t; * Make sure the handler is not already installed.&n;&t;&t; */
id|handler_obj
op_assign
id|obj_desc-&gt;device.handler
suffix:semicolon
multiline_comment|/* Walk the handler list for this device */
r_while
c_loop
(paren
id|handler_obj
)paren
(brace
multiline_comment|/* Same space_id indicates a handler already installed */
r_if
c_cond
(paren
id|handler_obj-&gt;address_space.space_id
op_eq
id|space_id
)paren
(brace
r_if
c_cond
(paren
id|handler_obj-&gt;address_space.handler
op_eq
id|handler
)paren
(brace
multiline_comment|/*&n;&t;&t;&t;&t;&t; * It is (relatively) OK to attempt to install the SAME&n;&t;&t;&t;&t;&t; * handler twice. This can easily happen with PCI_Config space.&n;&t;&t;&t;&t;&t; */
id|status
op_assign
id|AE_SAME_HANDLER
suffix:semicolon
r_goto
id|unlock_and_exit
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* A handler is already installed */
id|status
op_assign
id|AE_ALREADY_EXISTS
suffix:semicolon
)brace
r_goto
id|unlock_and_exit
suffix:semicolon
)brace
multiline_comment|/* Walk the linked list of handlers */
id|handler_obj
op_assign
id|handler_obj-&gt;address_space.next
suffix:semicolon
)brace
)brace
r_else
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_OPREGION
comma
l_string|&quot;Creating object on Device %p while installing handler&bslash;n&quot;
comma
id|node
)paren
)paren
suffix:semicolon
multiline_comment|/* obj_desc does not exist, create one */
r_if
c_cond
(paren
id|node-&gt;type
op_eq
id|ACPI_TYPE_ANY
)paren
(brace
id|type
op_assign
id|ACPI_TYPE_DEVICE
suffix:semicolon
)brace
r_else
(brace
id|type
op_assign
id|node-&gt;type
suffix:semicolon
)brace
id|obj_desc
op_assign
id|acpi_ut_create_internal_object
(paren
id|type
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|obj_desc
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
multiline_comment|/* Init new descriptor */
id|obj_desc-&gt;common.type
op_assign
(paren
id|u8
)paren
id|type
suffix:semicolon
multiline_comment|/* Attach the new object to the Node */
id|status
op_assign
id|acpi_ns_attach_object
(paren
id|node
comma
id|obj_desc
comma
id|type
)paren
suffix:semicolon
multiline_comment|/* Remove local reference to the object */
id|acpi_ut_remove_reference
(paren
id|obj_desc
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
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_OPREGION
comma
l_string|&quot;Installing address handler for region %s(%X) on Device %4.4s %p(%p)&bslash;n&quot;
comma
id|acpi_ut_get_region_name
(paren
id|space_id
)paren
comma
id|space_id
comma
id|acpi_ut_get_node_name
(paren
id|node
)paren
comma
id|node
comma
id|obj_desc
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Install the handler&n;&t; *&n;&t; * At this point there is no existing handler.&n;&t; * Just allocate the object for the handler and link it&n;&t; * into the list.&n;&t; */
id|handler_obj
op_assign
id|acpi_ut_create_internal_object
(paren
id|ACPI_TYPE_LOCAL_ADDRESS_HANDLER
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|handler_obj
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
multiline_comment|/* Init handler obj */
id|handler_obj-&gt;address_space.space_id
op_assign
(paren
id|u8
)paren
id|space_id
suffix:semicolon
id|handler_obj-&gt;address_space.hflags
op_assign
id|flags
suffix:semicolon
id|handler_obj-&gt;address_space.region_list
op_assign
l_int|NULL
suffix:semicolon
id|handler_obj-&gt;address_space.node
op_assign
id|node
suffix:semicolon
id|handler_obj-&gt;address_space.handler
op_assign
id|handler
suffix:semicolon
id|handler_obj-&gt;address_space.context
op_assign
id|context
suffix:semicolon
id|handler_obj-&gt;address_space.setup
op_assign
id|setup
suffix:semicolon
multiline_comment|/* Install at head of Device.address_space list */
id|handler_obj-&gt;address_space.next
op_assign
id|obj_desc-&gt;device.handler
suffix:semicolon
multiline_comment|/*&n;&t; * The Device object is the first reference on the handler_obj.&n;&t; * Each region that uses the handler adds a reference.&n;&t; */
id|obj_desc-&gt;device.handler
op_assign
id|handler_obj
suffix:semicolon
multiline_comment|/*&n;&t; * Walk the namespace finding all of the regions this&n;&t; * handler will manage.&n;&t; *&n;&t; * Start at the device and search the branch toward&n;&t; * the leaf nodes until either the leaf is encountered or&n;&t; * a device is detected that has an address handler of the&n;&t; * same type.&n;&t; *&n;&t; * In either case, back up and search down the remainder&n;&t; * of the branch&n;&t; */
id|status
op_assign
id|acpi_ns_walk_namespace
(paren
id|ACPI_TYPE_ANY
comma
id|device
comma
id|ACPI_UINT32_MAX
comma
id|ACPI_NS_WALK_UNLOCK
comma
id|acpi_ev_install_handler
comma
id|handler_obj
comma
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Now we can run the _REG methods for all Regions for this&n;&t; * space ID.  This is a separate walk in order to handle any&n;&t; * interdependencies between regions and _REG methods.  (i.e. handlers&n;&t; * must be installed for all regions of this Space ID before we&n;&t; * can run any _REG methods.&n;&t; */
id|status
op_assign
id|acpi_ns_walk_namespace
(paren
id|ACPI_TYPE_ANY
comma
id|device
comma
id|ACPI_UINT32_MAX
comma
id|ACPI_NS_WALK_UNLOCK
comma
id|acpi_ev_reg_run
comma
id|handler_obj
comma
l_int|NULL
)paren
suffix:semicolon
id|unlock_and_exit
suffix:colon
(paren
r_void
)paren
id|acpi_ut_release_mutex
(paren
id|ACPI_MTX_NAMESPACE
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_remove_address_space_handler&n; *&n; * PARAMETERS:  Device          - Handle for the device&n; *              space_id        - The address space ID&n; *              Handler         - Address of the handler&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Remove a previously installed handler.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_remove_address_space_handler
id|acpi_remove_address_space_handler
(paren
id|acpi_handle
id|device
comma
id|acpi_adr_space_type
id|space_id
comma
id|acpi_adr_space_handler
id|handler
)paren
(brace
r_union
id|acpi_operand_object
op_star
id|obj_desc
suffix:semicolon
r_union
id|acpi_operand_object
op_star
id|handler_obj
suffix:semicolon
r_union
id|acpi_operand_object
op_star
id|region_obj
suffix:semicolon
r_union
id|acpi_operand_object
op_star
op_star
id|last_obj_ptr
suffix:semicolon
r_struct
id|acpi_namespace_node
op_star
id|node
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;acpi_remove_address_space_handler&quot;
)paren
suffix:semicolon
multiline_comment|/* Parameter validation */
r_if
c_cond
(paren
op_logical_neg
id|device
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
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
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/* Convert and validate the device handle */
id|node
op_assign
id|acpi_ns_map_handle_to_node
(paren
id|device
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|node
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
multiline_comment|/* Make sure the internal object exists */
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
id|status
op_assign
id|AE_NOT_EXIST
suffix:semicolon
r_goto
id|unlock_and_exit
suffix:semicolon
)brace
multiline_comment|/* Find the address handler the user requested */
id|handler_obj
op_assign
id|obj_desc-&gt;device.handler
suffix:semicolon
id|last_obj_ptr
op_assign
op_amp
id|obj_desc-&gt;device.handler
suffix:semicolon
r_while
c_loop
(paren
id|handler_obj
)paren
(brace
multiline_comment|/* We have a handler, see if user requested this one */
r_if
c_cond
(paren
id|handler_obj-&gt;address_space.space_id
op_eq
id|space_id
)paren
(brace
multiline_comment|/* Matched space_id, first dereference this in the Regions */
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_OPREGION
comma
l_string|&quot;Removing address handler %p(%p) for region %s on Device %p(%p)&bslash;n&quot;
comma
id|handler_obj
comma
id|handler
comma
id|acpi_ut_get_region_name
(paren
id|space_id
)paren
comma
id|node
comma
id|obj_desc
)paren
)paren
suffix:semicolon
id|region_obj
op_assign
id|handler_obj-&gt;address_space.region_list
suffix:semicolon
multiline_comment|/* Walk the handler&squot;s region list */
r_while
c_loop
(paren
id|region_obj
)paren
(brace
multiline_comment|/*&n;&t;&t;&t;&t; * First disassociate the handler from the region.&n;&t;&t;&t;&t; *&n;&t;&t;&t;&t; * NOTE: this doesn&squot;t mean that the region goes away&n;&t;&t;&t;&t; * The region is just inaccessible as indicated to&n;&t;&t;&t;&t; * the _REG method&n;&t;&t;&t;&t; */
id|acpi_ev_detach_region
(paren
id|region_obj
comma
id|TRUE
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t;&t; * Walk the list: Just grab the head because the&n;&t;&t;&t;&t; * detach_region removed the previous head.&n;&t;&t;&t;&t; */
id|region_obj
op_assign
id|handler_obj-&gt;address_space.region_list
suffix:semicolon
)brace
multiline_comment|/* Remove this Handler object from the list */
op_star
id|last_obj_ptr
op_assign
id|handler_obj-&gt;address_space.next
suffix:semicolon
multiline_comment|/* Now we can delete the handler object */
id|acpi_ut_remove_reference
(paren
id|handler_obj
)paren
suffix:semicolon
r_goto
id|unlock_and_exit
suffix:semicolon
)brace
multiline_comment|/* Walk the linked list of handlers */
id|last_obj_ptr
op_assign
op_amp
id|handler_obj-&gt;address_space.next
suffix:semicolon
id|handler_obj
op_assign
id|handler_obj-&gt;address_space.next
suffix:semicolon
)brace
multiline_comment|/* The handler does not exist */
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_OPREGION
comma
l_string|&quot;Unable to remove address handler %p for %s(%X), dev_node %p, obj %p&bslash;n&quot;
comma
id|handler
comma
id|acpi_ut_get_region_name
(paren
id|space_id
)paren
comma
id|space_id
comma
id|node
comma
id|obj_desc
)paren
)paren
suffix:semicolon
id|status
op_assign
id|AE_NOT_EXIST
suffix:semicolon
id|unlock_and_exit
suffix:colon
(paren
r_void
)paren
id|acpi_ut_release_mutex
(paren
id|ACPI_MTX_NAMESPACE
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
eof
