multiline_comment|/******************************************************************************&n; *&n; * Module Name: nsinit - namespace initialization&n; *              $Revision: 52 $&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000 - 2002, R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &quot;acpi.h&quot;
macro_line|#include &quot;acnamesp.h&quot;
macro_line|#include &quot;acdispat.h&quot;
macro_line|#include &quot;acinterp.h&quot;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_NAMESPACE
id|ACPI_MODULE_NAME
(paren
l_string|&quot;nsinit&quot;
)paren
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ns_initialize_objects&n; *&n; * PARAMETERS:  None&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Walk the entire namespace and perform any necessary&n; *              initialization on the objects found therein&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ns_initialize_objects
id|acpi_ns_initialize_objects
(paren
r_void
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
id|acpi_init_walk_info
id|info
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;Ns_initialize_objects&quot;
)paren
suffix:semicolon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_DISPATCH
comma
l_string|&quot;**** Starting initialization of namespace objects ****&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|ACPI_DEBUG_PRINT_RAW
(paren
(paren
id|ACPI_DB_INIT
comma
l_string|&quot;Completing Region/Field/Buffer/Package initialization:&quot;
)paren
)paren
suffix:semicolon
multiline_comment|/* Set all init info to zero */
id|ACPI_MEMSET
(paren
op_amp
id|info
comma
l_int|0
comma
r_sizeof
(paren
id|acpi_init_walk_info
)paren
)paren
suffix:semicolon
multiline_comment|/* Walk entire namespace from the supplied root */
id|status
op_assign
id|acpi_walk_namespace
(paren
id|ACPI_TYPE_ANY
comma
id|ACPI_ROOT_OBJECT
comma
id|ACPI_UINT32_MAX
comma
id|acpi_ns_init_one_object
comma
op_amp
id|info
comma
l_int|NULL
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
l_string|&quot;Walk_namespace failed! %s&bslash;n&quot;
comma
id|acpi_format_exception
(paren
id|status
)paren
)paren
)paren
suffix:semicolon
)brace
id|ACPI_DEBUG_PRINT_RAW
(paren
(paren
id|ACPI_DB_INIT
comma
l_string|&quot;&bslash;nInitialized %hd/%hd Regions %hd/%hd Fields %hd/%hd Buffers %hd/%hd Packages (%hd nodes)&bslash;n&quot;
comma
id|info.op_region_init
comma
id|info.op_region_count
comma
id|info.field_init
comma
id|info.field_count
comma
id|info.buffer_init
comma
id|info.buffer_count
comma
id|info.package_init
comma
id|info.package_count
comma
id|info.object_count
)paren
)paren
suffix:semicolon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_DISPATCH
comma
l_string|&quot;%hd Control Methods found&bslash;n&quot;
comma
id|info.method_count
)paren
)paren
suffix:semicolon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_DISPATCH
comma
l_string|&quot;%hd Op Regions found&bslash;n&quot;
comma
id|info.op_region_count
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ns_initialize_devices&n; *&n; * PARAMETERS:  None&n; *&n; * RETURN:      acpi_status&n; *&n; * DESCRIPTION: Walk the entire namespace and initialize all ACPI devices.&n; *              This means running _INI on all present devices.&n; *&n; *              Note: We install PCI config space handler on region access,&n; *              not here.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ns_initialize_devices
id|acpi_ns_initialize_devices
(paren
r_void
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
id|acpi_device_walk_info
id|info
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;Ns_initialize_devices&quot;
)paren
suffix:semicolon
multiline_comment|/* Init counters */
id|info.device_count
op_assign
l_int|0
suffix:semicolon
id|info.num_STA
op_assign
l_int|0
suffix:semicolon
id|info.num_INI
op_assign
l_int|0
suffix:semicolon
id|ACPI_DEBUG_PRINT_RAW
(paren
(paren
id|ACPI_DB_INIT
comma
l_string|&quot;Executing all Device _STA and_INI methods:&quot;
)paren
)paren
suffix:semicolon
multiline_comment|/* Walk namespace for all objects of type Device */
id|status
op_assign
id|acpi_ns_walk_namespace
(paren
id|ACPI_TYPE_DEVICE
comma
id|ACPI_ROOT_OBJECT
comma
id|ACPI_UINT32_MAX
comma
id|FALSE
comma
id|acpi_ns_init_one_device
comma
op_amp
id|info
comma
l_int|NULL
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
l_string|&quot;Walk_namespace failed! %s&bslash;n&quot;
comma
id|acpi_format_exception
(paren
id|status
)paren
)paren
)paren
suffix:semicolon
)brace
id|ACPI_DEBUG_PRINT_RAW
(paren
(paren
id|ACPI_DB_INIT
comma
l_string|&quot;&bslash;n%hd Devices found containing: %hd _STA, %hd _INI methods&bslash;n&quot;
comma
id|info.device_count
comma
id|info.num_STA
comma
id|info.num_INI
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ns_init_one_object&n; *&n; * PARAMETERS:  Obj_handle      - Node&n; *              Level           - Current nesting level&n; *              Context         - Points to a init info struct&n; *              Return_value    - Not used&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Callback from Acpi_walk_namespace. Invoked for every object&n; *              within the  namespace.&n; *&n; *              Currently, the only objects that require initialization are:&n; *              1) Methods&n; *              2) Op Regions&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ns_init_one_object
id|acpi_ns_init_one_object
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
id|acpi_object_type
id|type
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
id|acpi_init_walk_info
op_star
id|info
op_assign
(paren
id|acpi_init_walk_info
op_star
)paren
id|context
suffix:semicolon
id|acpi_namespace_node
op_star
id|node
op_assign
(paren
id|acpi_namespace_node
op_star
)paren
id|obj_handle
suffix:semicolon
id|acpi_operand_object
op_star
id|obj_desc
suffix:semicolon
id|ACPI_FUNCTION_NAME
(paren
l_string|&quot;Ns_init_one_object&quot;
)paren
suffix:semicolon
id|info-&gt;object_count
op_increment
suffix:semicolon
multiline_comment|/* And even then, we are only interested in a few object types */
id|type
op_assign
id|acpi_ns_get_type
(paren
id|obj_handle
)paren
suffix:semicolon
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
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/* Increment counters for object types we are looking for */
r_switch
c_cond
(paren
id|type
)paren
(brace
r_case
id|ACPI_TYPE_REGION
suffix:colon
id|info-&gt;op_region_count
op_increment
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_BUFFER_FIELD
suffix:colon
id|info-&gt;field_count
op_increment
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_BUFFER
suffix:colon
id|info-&gt;buffer_count
op_increment
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_PACKAGE
suffix:colon
id|info-&gt;package_count
op_increment
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* No init required, just exit now */
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * If the object is already initialized, nothing else to do&n;&t; */
r_if
c_cond
(paren
id|obj_desc-&gt;common.flags
op_amp
id|AOPOBJ_DATA_VALID
)paren
(brace
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Must lock the interpreter before executing AML code&n;&t; */
id|status
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
multiline_comment|/*&n;&t; * Each of these types can contain executable AML code within&n;&t; * the declaration.&n;&t; */
r_switch
c_cond
(paren
id|type
)paren
(brace
r_case
id|ACPI_TYPE_REGION
suffix:colon
id|info-&gt;op_region_init
op_increment
suffix:semicolon
id|status
op_assign
id|acpi_ds_get_region_arguments
(paren
id|obj_desc
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_BUFFER_FIELD
suffix:colon
id|info-&gt;field_init
op_increment
suffix:semicolon
id|status
op_assign
id|acpi_ds_get_buffer_field_arguments
(paren
id|obj_desc
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_BUFFER
suffix:colon
id|info-&gt;buffer_init
op_increment
suffix:semicolon
id|status
op_assign
id|acpi_ds_get_buffer_arguments
(paren
id|obj_desc
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_PACKAGE
suffix:colon
id|info-&gt;package_init
op_increment
suffix:semicolon
id|status
op_assign
id|acpi_ds_get_package_arguments
(paren
id|obj_desc
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* No other types can get here */
r_break
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
id|ACPI_DEBUG_PRINT_RAW
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Could not execute arguments for [%4.4s] (%s), %s&bslash;n&quot;
comma
id|node-&gt;name.ascii
comma
id|acpi_ut_get_type_name
(paren
id|type
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
multiline_comment|/* Print a dot for each object unless we are going to print the entire pathname */
r_if
c_cond
(paren
op_logical_neg
(paren
id|acpi_dbg_level
op_amp
id|ACPI_LV_INIT_NAMES
)paren
)paren
(brace
id|acpi_os_printf
(paren
l_string|&quot;.&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * We ignore errors from above, and always return OK, since&n;&t; * we don&squot;t want to abort the walk on any single error.&n;&t; */
id|acpi_ex_exit_interpreter
(paren
)paren
suffix:semicolon
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ns_init_one_device&n; *&n; * PARAMETERS:  acpi_walk_callback&n; *&n; * RETURN:      acpi_status&n; *&n; * DESCRIPTION: This is called once per device soon after ACPI is enabled&n; *              to initialize each device. It determines if the device is&n; *              present, and if so, calls _INI.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ns_init_one_device
id|acpi_ns_init_one_device
(paren
id|acpi_handle
id|obj_handle
comma
id|u32
id|nesting_level
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
id|acpi_status
id|status
suffix:semicolon
id|acpi_namespace_node
op_star
id|node
suffix:semicolon
id|u32
id|flags
suffix:semicolon
id|acpi_device_walk_info
op_star
id|info
op_assign
(paren
id|acpi_device_walk_info
op_star
)paren
id|context
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;Ns_init_one_device&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|acpi_dbg_level
op_le
id|ACPI_LV_ALL_EXCEPTIONS
)paren
op_logical_and
(paren
op_logical_neg
(paren
id|acpi_dbg_level
op_amp
id|ACPI_LV_INFO
)paren
)paren
)paren
(brace
id|acpi_os_printf
(paren
l_string|&quot;.&quot;
)paren
suffix:semicolon
)brace
id|info-&gt;device_count
op_increment
suffix:semicolon
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
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
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
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Run _STA to determine if we can run _INI on the device.&n;&t; */
id|ACPI_DEBUG_EXEC
(paren
id|acpi_ut_display_init_pathname
(paren
id|ACPI_TYPE_METHOD
comma
id|node
comma
l_string|&quot;_STA&quot;
)paren
)paren
suffix:semicolon
id|status
op_assign
id|acpi_ut_execute_STA
(paren
id|node
comma
op_amp
id|flags
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
multiline_comment|/* Ignore error and move on to next device */
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
id|info-&gt;num_STA
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|flags
op_amp
l_int|0x01
)paren
)paren
(brace
multiline_comment|/* don&squot;t look at children of a not present device */
id|return_ACPI_STATUS
c_func
(paren
id|AE_CTRL_DEPTH
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * The device is present. Run _INI.&n;&t; */
id|ACPI_DEBUG_EXEC
(paren
id|acpi_ut_display_init_pathname
(paren
id|ACPI_TYPE_METHOD
comma
id|obj_handle
comma
l_string|&quot;_INI&quot;
)paren
)paren
suffix:semicolon
id|status
op_assign
id|acpi_ns_evaluate_relative
(paren
id|obj_handle
comma
l_string|&quot;_INI&quot;
comma
l_int|NULL
comma
l_int|NULL
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
multiline_comment|/* No _INI (AE_NOT_FOUND) means device requires no initialization */
r_if
c_cond
(paren
id|status
op_ne
id|AE_NOT_FOUND
)paren
(brace
multiline_comment|/* Ignore error and move on to next device */
macro_line|#ifdef ACPI_DEBUG_OUTPUT
id|NATIVE_CHAR
op_star
id|scope_name
op_assign
id|acpi_ns_get_external_pathname
(paren
id|obj_handle
)paren
suffix:semicolon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_WARN
comma
l_string|&quot;%s._INI failed: %s&bslash;n&quot;
comma
id|scope_name
comma
id|acpi_format_exception
(paren
id|status
)paren
)paren
)paren
suffix:semicolon
id|ACPI_MEM_FREE
(paren
id|scope_name
)paren
suffix:semicolon
macro_line|#endif
)brace
id|status
op_assign
id|AE_OK
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Count of successful INIs */
id|info-&gt;num_INI
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|acpi_gbl_init_handler
)paren
(brace
multiline_comment|/* External initialization handler is present, call it */
id|status
op_assign
id|acpi_gbl_init_handler
(paren
id|obj_handle
comma
id|ACPI_INIT_DEVICE_INI
)paren
suffix:semicolon
)brace
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
eof
