multiline_comment|/******************************************************************************&n; *&n; * Module Name: dsinit - Object initialization namespace walk&n; *              $Revision: 2 $&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000 - 2002, R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &quot;acpi.h&quot;
macro_line|#include &quot;acparser.h&quot;
macro_line|#include &quot;amlcode.h&quot;
macro_line|#include &quot;acdispat.h&quot;
macro_line|#include &quot;acnamesp.h&quot;
macro_line|#include &quot;acinterp.h&quot;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_DISPATCHER
id|ACPI_MODULE_NAME
(paren
l_string|&quot;dsinit&quot;
)paren
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ds_init_one_object&n; *&n; * PARAMETERS:  Obj_handle      - Node&n; *              Level           - Current nesting level&n; *              Context         - Points to a init info struct&n; *              Return_value    - Not used&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Callback from Acpi_walk_namespace. Invoked for every object&n; *              within the namespace.&n; *&n; *              Currently, the only objects that require initialization are:&n; *              1) Methods&n; *              2) Operation Regions&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ds_init_one_object
id|acpi_ds_init_one_object
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
id|ACPI_FUNCTION_NAME
(paren
l_string|&quot;Ds_init_one_object&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * We are only interested in objects owned by the table that&n;&t; * was just loaded&n;&t; */
r_if
c_cond
(paren
(paren
(paren
id|acpi_namespace_node
op_star
)paren
id|obj_handle
)paren
op_member_access_from_pointer
id|owner_id
op_ne
id|info-&gt;table_desc-&gt;table_id
)paren
(brace
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
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
r_switch
c_cond
(paren
id|type
)paren
(brace
r_case
id|ACPI_TYPE_REGION
suffix:colon
id|status
op_assign
id|acpi_ds_initialize_region
(paren
id|obj_handle
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
l_string|&quot;Region %p [%4.4s] - Init failure, %s&bslash;n&quot;
comma
id|obj_handle
comma
(paren
(paren
id|acpi_namespace_node
op_star
)paren
id|obj_handle
)paren
op_member_access_from_pointer
id|name.ascii
comma
id|acpi_format_exception
(paren
id|status
)paren
)paren
)paren
suffix:semicolon
)brace
id|info-&gt;op_region_count
op_increment
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_METHOD
suffix:colon
id|info-&gt;method_count
op_increment
suffix:semicolon
multiline_comment|/* Print a dot for each method unless we are going to print the entire pathname */
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
multiline_comment|/*&n;&t;&t; * Set the execution data width (32 or 64) based upon the&n;&t;&t; * revision number of the parent ACPI table.&n;&t;&t; * TBD: This is really for possible future support of integer width&n;&t;&t; * on a per-table basis. Currently, we just use a global for the width.&n;&t;&t; */
r_if
c_cond
(paren
id|info-&gt;table_desc-&gt;pointer-&gt;revision
op_eq
l_int|1
)paren
(brace
(paren
(paren
id|acpi_namespace_node
op_star
)paren
id|obj_handle
)paren
op_member_access_from_pointer
id|flags
op_or_assign
id|ANOBJ_DATA_WIDTH_32
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Always parse methods to detect errors, we may delete&n;&t;&t; * the parse tree below&n;&t;&t; */
id|status
op_assign
id|acpi_ds_parse_method
(paren
id|obj_handle
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
l_string|&quot;Method %p [%4.4s] - parse failure, %s&bslash;n&quot;
comma
id|obj_handle
comma
(paren
(paren
id|acpi_namespace_node
op_star
)paren
id|obj_handle
)paren
op_member_access_from_pointer
id|name.ascii
comma
id|acpi_format_exception
(paren
id|status
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/* This parse failed, but we will continue parsing more methods */
r_break
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Delete the parse tree.  We simple re-parse the method&n;&t;&t; * for every execution since there isn&squot;t much overhead&n;&t;&t; */
id|acpi_ns_delete_namespace_subtree
(paren
id|obj_handle
)paren
suffix:semicolon
id|acpi_ns_delete_namespace_by_owner
(paren
(paren
(paren
id|acpi_namespace_node
op_star
)paren
id|obj_handle
)paren
op_member_access_from_pointer
id|object-&gt;method.owning_id
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_DEVICE
suffix:colon
id|info-&gt;device_count
op_increment
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * We ignore errors from above, and always return OK, since&n;&t; * we don&squot;t want to abort the walk on a single error.&n;&t; */
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ds_initialize_objects&n; *&n; * PARAMETERS:  Table_desc      - Descriptor for parent ACPI table&n; *              Start_node      - Root of subtree to be initialized.&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Walk the namespace starting at &quot;Start_node&quot; and perform any&n; *              necessary initialization on the objects found therein&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ds_initialize_objects
id|acpi_ds_initialize_objects
(paren
id|acpi_table_desc
op_star
id|table_desc
comma
id|acpi_namespace_node
op_star
id|start_node
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
l_string|&quot;Ds_initialize_objects&quot;
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
l_string|&quot;Parsing all Control Methods:&quot;
)paren
)paren
suffix:semicolon
id|info.method_count
op_assign
l_int|0
suffix:semicolon
id|info.op_region_count
op_assign
l_int|0
suffix:semicolon
id|info.object_count
op_assign
l_int|0
suffix:semicolon
id|info.device_count
op_assign
l_int|0
suffix:semicolon
id|info.table_desc
op_assign
id|table_desc
suffix:semicolon
multiline_comment|/* Walk entire namespace from the supplied root */
id|status
op_assign
id|acpi_walk_namespace
(paren
id|ACPI_TYPE_ANY
comma
id|start_node
comma
id|ACPI_UINT32_MAX
comma
id|acpi_ds_init_one_object
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
l_string|&quot;Walk_namespace failed, %s&bslash;n&quot;
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
l_string|&quot;&bslash;nTable [%4.4s] - %hd Objects with %hd Devices %hd Methods %hd Regions&bslash;n&quot;
comma
id|table_desc-&gt;pointer-&gt;signature
comma
id|info.object_count
comma
id|info.device_count
comma
id|info.method_count
comma
id|info.op_region_count
)paren
)paren
suffix:semicolon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_DISPATCH
comma
l_string|&quot;%hd Methods, %hd Regions&bslash;n&quot;
comma
id|info.method_count
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
eof
