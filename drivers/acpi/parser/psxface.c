multiline_comment|/******************************************************************************&n; *&n; * Module Name: psxface - Parser external interfaces&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000 - 2003, R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &lt;acpi/acpi.h&gt;
macro_line|#include &lt;acpi/acparser.h&gt;
macro_line|#include &lt;acpi/acdispat.h&gt;
macro_line|#include &lt;acpi/acinterp.h&gt;
macro_line|#include &lt;acpi/acnamesp.h&gt;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_PARSER
id|ACPI_MODULE_NAME
(paren
l_string|&quot;psxface&quot;
)paren
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_psx_execute&n; *&n; * PARAMETERS:  method_node         - A method object containing both the AML&n; *                                    address and length.&n; *              **Params            - List of parameters to pass to method,&n; *                                    terminated by NULL. Params itself may be&n; *                                    NULL if no parameters are being passed.&n; *              **return_obj_desc   - Return object from execution of the&n; *                                    method.&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Execute a control method&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_psx_execute
id|acpi_psx_execute
(paren
r_struct
id|acpi_namespace_node
op_star
id|method_node
comma
r_union
id|acpi_operand_object
op_star
op_star
id|params
comma
r_union
id|acpi_operand_object
op_star
op_star
id|return_obj_desc
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
r_union
id|acpi_operand_object
op_star
id|obj_desc
suffix:semicolon
id|u32
id|i
suffix:semicolon
r_union
id|acpi_parse_object
op_star
id|op
suffix:semicolon
r_struct
id|acpi_walk_state
op_star
id|walk_state
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;psx_execute&quot;
)paren
suffix:semicolon
multiline_comment|/* Validate the Node and get the attached object */
r_if
c_cond
(paren
op_logical_neg
id|method_node
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_NULL_ENTRY
)paren
suffix:semicolon
)brace
id|obj_desc
op_assign
id|acpi_ns_get_attached_object
(paren
id|method_node
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|obj_desc
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_NULL_OBJECT
)paren
suffix:semicolon
)brace
multiline_comment|/* Init for new method, wait on concurrency semaphore */
id|status
op_assign
id|acpi_ds_begin_method_execution
(paren
id|method_node
comma
id|obj_desc
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
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|params
)paren
(brace
multiline_comment|/*&n;&t;&t; * The caller &quot;owns&quot; the parameters, so give each one an extra&n;&t;&t; * reference&n;&t;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|params
(braket
id|i
)braket
suffix:semicolon
id|i
op_increment
)paren
(brace
id|acpi_ut_add_reference
(paren
id|params
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; * 1) Perform the first pass parse of the method to enter any&n;&t; * named objects that it creates into the namespace&n;&t; */
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_PARSE
comma
l_string|&quot;**** Begin Method Parse **** Entry=%p obj=%p&bslash;n&quot;
comma
id|method_node
comma
id|obj_desc
)paren
)paren
suffix:semicolon
multiline_comment|/* Create and init a Root Node */
id|op
op_assign
id|acpi_ps_create_scope_op
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|op
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Get a new owner_id for objects created by this method. Namespace&n;&t; * objects (such as Operation Regions) can be created during the&n;&t; * first pass parse.&n;&t; */
id|obj_desc-&gt;method.owning_id
op_assign
id|acpi_ut_allocate_owner_id
(paren
id|ACPI_OWNER_TYPE_METHOD
)paren
suffix:semicolon
multiline_comment|/* Create and initialize a new walk state */
id|walk_state
op_assign
id|acpi_ds_create_walk_state
(paren
id|obj_desc-&gt;method.owning_id
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|walk_state
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
)brace
id|status
op_assign
id|acpi_ds_init_aml_walk
(paren
id|walk_state
comma
id|op
comma
id|method_node
comma
id|obj_desc-&gt;method.aml_start
comma
id|obj_desc-&gt;method.aml_length
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|1
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
id|acpi_ds_delete_walk_state
(paren
id|walk_state
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/* Parse the AML */
id|status
op_assign
id|acpi_ps_parse_aml
(paren
id|walk_state
)paren
suffix:semicolon
id|acpi_ps_delete_parse_tree
(paren
id|op
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * 2) Execute the method.  Performs second pass parse simultaneously&n;&t; */
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_PARSE
comma
l_string|&quot;**** Begin Method Execution **** Entry=%p obj=%p&bslash;n&quot;
comma
id|method_node
comma
id|obj_desc
)paren
)paren
suffix:semicolon
multiline_comment|/* Create and init a Root Node */
id|op
op_assign
id|acpi_ps_create_scope_op
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|op
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
)brace
multiline_comment|/* Init new op with the method name and pointer back to the NS node */
id|acpi_ps_set_name
(paren
id|op
comma
id|method_node-&gt;name.integer
)paren
suffix:semicolon
id|op-&gt;common.node
op_assign
id|method_node
suffix:semicolon
multiline_comment|/* Create and initialize a new walk state */
id|walk_state
op_assign
id|acpi_ds_create_walk_state
(paren
id|TABLE_ID_DSDT
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|walk_state
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
)brace
id|status
op_assign
id|acpi_ds_init_aml_walk
(paren
id|walk_state
comma
id|op
comma
id|method_node
comma
id|obj_desc-&gt;method.aml_start
comma
id|obj_desc-&gt;method.aml_length
comma
id|params
comma
id|return_obj_desc
comma
l_int|3
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
id|acpi_ds_delete_walk_state
(paren
id|walk_state
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * The walk of the parse tree is where we actually execute the method&n;&t; */
id|status
op_assign
id|acpi_ps_parse_aml
(paren
id|walk_state
)paren
suffix:semicolon
id|acpi_ps_delete_parse_tree
(paren
id|op
)paren
suffix:semicolon
r_if
c_cond
(paren
id|params
)paren
(brace
multiline_comment|/* Take away the extra reference that we gave the parameters above */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|params
(braket
id|i
)braket
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/* Ignore errors, just do them all */
(paren
r_void
)paren
id|acpi_ut_update_object_reference
(paren
id|params
(braket
id|i
)braket
comma
id|REF_DECREMENT
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; * If the method has returned an object, signal this to the caller with&n;&t; * a control exception code&n;&t; */
r_if
c_cond
(paren
op_star
id|return_obj_desc
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_PARSE
comma
l_string|&quot;Method returned obj_desc=%p&bslash;n&quot;
comma
op_star
id|return_obj_desc
)paren
)paren
suffix:semicolon
id|ACPI_DUMP_STACK_ENTRY
(paren
op_star
id|return_obj_desc
)paren
suffix:semicolon
id|status
op_assign
id|AE_CTRL_RETURN_VALUE
suffix:semicolon
)brace
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
eof
