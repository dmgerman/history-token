multiline_comment|/*******************************************************************************&n; *&n; * Module Name: nsobject - Utilities for objects attached to namespace&n; *                         table entries&n; *&n; ******************************************************************************/
multiline_comment|/*&n; * Copyright (C) 2000 - 2004, R. Byron Moore&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. Redistributions in binary form must reproduce at minimum a disclaimer&n; *    substantially similar to the &quot;NO WARRANTY&quot; disclaimer below&n; *    (&quot;Disclaimer&quot;) and any redistribution must be conditioned upon&n; *    including a substantially similar Disclaimer requirement for further&n; *    binary redistribution.&n; * 3. Neither the names of the above-listed copyright holders nor the names&n; *    of any contributors may be used to endorse or promote products derived&n; *    from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;) version 2 as published by the Free&n; * Software Foundation.&n; *&n; * NO WARRANTY&n; * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS&n; * &quot;AS IS&quot; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT&n; * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR&n; * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT&n; * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,&n; * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING&n; * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE&n; * POSSIBILITY OF SUCH DAMAGES.&n; */
macro_line|#include &lt;acpi/acpi.h&gt;
macro_line|#include &lt;acpi/acnamesp.h&gt;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_NAMESPACE
id|ACPI_MODULE_NAME
(paren
l_string|&quot;nsobject&quot;
)paren
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ns_attach_object&n; *&n; * PARAMETERS:  Node                - Parent Node&n; *              Object              - Object to be attached&n; *              Type                - Type of object, or ACPI_TYPE_ANY if not&n; *                                    known&n; *&n; * DESCRIPTION: Record the given object as the value associated with the&n; *              name whose acpi_handle is passed.  If Object is NULL&n; *              and Type is ACPI_TYPE_ANY, set the name as having no value.&n; *              Note: Future may require that the Node-&gt;Flags field be passed&n; *              as a parameter.&n; *&n; * MUTEX:       Assumes namespace is locked&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ns_attach_object
id|acpi_ns_attach_object
(paren
r_struct
id|acpi_namespace_node
op_star
id|node
comma
r_union
id|acpi_operand_object
op_star
id|object
comma
id|acpi_object_type
id|type
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
id|last_obj_desc
suffix:semicolon
id|acpi_object_type
id|object_type
op_assign
id|ACPI_TYPE_ANY
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ns_attach_object&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Parameter validation&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|node
)paren
(brace
multiline_comment|/* Invalid handle */
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;ns_attach_object: Null named_obj handle&bslash;n&quot;
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
op_logical_neg
id|object
op_logical_and
(paren
id|ACPI_TYPE_ANY
op_ne
id|type
)paren
)paren
(brace
multiline_comment|/* Null object */
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;ns_attach_object: Null object, but type not ACPI_TYPE_ANY&bslash;n&quot;
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
id|ACPI_GET_DESCRIPTOR_TYPE
(paren
id|node
)paren
op_ne
id|ACPI_DESC_TYPE_NAMED
)paren
(brace
multiline_comment|/* Not a name handle */
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;ns_attach_object: Invalid handle %p [%s]&bslash;n&quot;
comma
id|node
comma
id|acpi_ut_get_descriptor_name
(paren
id|node
)paren
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
multiline_comment|/* Check if this object is already attached */
r_if
c_cond
(paren
id|node-&gt;object
op_eq
id|object
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_EXEC
comma
l_string|&quot;Obj %p already installed in name_obj %p&bslash;n&quot;
comma
id|object
comma
id|node
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/* If null object, we will just install it */
r_if
c_cond
(paren
op_logical_neg
id|object
)paren
(brace
id|obj_desc
op_assign
l_int|NULL
suffix:semicolon
id|object_type
op_assign
id|ACPI_TYPE_ANY
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * If the source object is a namespace Node with an attached object,&n;&t; * we will use that (attached) object&n;&t; */
r_else
r_if
c_cond
(paren
(paren
id|ACPI_GET_DESCRIPTOR_TYPE
(paren
id|object
)paren
op_eq
id|ACPI_DESC_TYPE_NAMED
)paren
op_logical_and
(paren
(paren
r_struct
id|acpi_namespace_node
op_star
)paren
id|object
)paren
op_member_access_from_pointer
id|object
)paren
(brace
multiline_comment|/*&n;&t;&t; * Value passed is a name handle and that name has a&n;&t;&t; * non-null value.  Use that name&squot;s value and type.&n;&t;&t; */
id|obj_desc
op_assign
(paren
(paren
r_struct
id|acpi_namespace_node
op_star
)paren
id|object
)paren
op_member_access_from_pointer
id|object
suffix:semicolon
id|object_type
op_assign
(paren
(paren
r_struct
id|acpi_namespace_node
op_star
)paren
id|object
)paren
op_member_access_from_pointer
id|type
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Otherwise, we will use the parameter object, but we must type&n;&t; * it first&n;&t; */
r_else
(brace
id|obj_desc
op_assign
(paren
r_union
id|acpi_operand_object
op_star
)paren
id|object
suffix:semicolon
multiline_comment|/* Use the given type */
id|object_type
op_assign
id|type
suffix:semicolon
)brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_EXEC
comma
l_string|&quot;Installing %p into Node %p [%4.4s]&bslash;n&quot;
comma
id|obj_desc
comma
id|node
comma
id|acpi_ut_get_node_name
(paren
id|node
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/* Detach an existing attached object if present */
r_if
c_cond
(paren
id|node-&gt;object
)paren
(brace
id|acpi_ns_detach_object
(paren
id|node
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|obj_desc
)paren
(brace
multiline_comment|/*&n;&t;&t; * Must increment the new value&squot;s reference count&n;&t;&t; * (if it is an internal object)&n;&t;&t; */
id|acpi_ut_add_reference
(paren
id|obj_desc
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Handle objects with multiple descriptors - walk&n;&t;&t; * to the end of the descriptor list&n;&t;&t; */
id|last_obj_desc
op_assign
id|obj_desc
suffix:semicolon
r_while
c_loop
(paren
id|last_obj_desc-&gt;common.next_object
)paren
(brace
id|last_obj_desc
op_assign
id|last_obj_desc-&gt;common.next_object
suffix:semicolon
)brace
multiline_comment|/* Install the object at the front of the object list */
id|last_obj_desc-&gt;common.next_object
op_assign
id|node-&gt;object
suffix:semicolon
)brace
id|node-&gt;type
op_assign
(paren
id|u8
)paren
id|object_type
suffix:semicolon
id|node-&gt;object
op_assign
id|obj_desc
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ns_detach_object&n; *&n; * PARAMETERS:  Node           - An node whose object will be detached&n; *&n; * RETURN:      None.&n; *&n; * DESCRIPTION: Detach/delete an object associated with a namespace node.&n; *              if the object is an allocated object, it is freed.&n; *              Otherwise, the field is simply cleared.&n; *&n; ******************************************************************************/
r_void
DECL|function|acpi_ns_detach_object
id|acpi_ns_detach_object
(paren
r_struct
id|acpi_namespace_node
op_star
id|node
)paren
(brace
r_union
id|acpi_operand_object
op_star
id|obj_desc
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ns_detach_object&quot;
)paren
suffix:semicolon
id|obj_desc
op_assign
id|node-&gt;object
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|obj_desc
op_logical_or
(paren
id|ACPI_GET_OBJECT_TYPE
(paren
id|obj_desc
)paren
op_eq
id|ACPI_TYPE_LOCAL_DATA
)paren
)paren
(brace
id|return_VOID
suffix:semicolon
)brace
multiline_comment|/* Clear the entry in all cases */
id|node-&gt;object
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_GET_DESCRIPTOR_TYPE
(paren
id|obj_desc
)paren
op_eq
id|ACPI_DESC_TYPE_OPERAND
)paren
(brace
id|node-&gt;object
op_assign
id|obj_desc-&gt;common.next_object
suffix:semicolon
r_if
c_cond
(paren
id|node-&gt;object
op_logical_and
(paren
id|ACPI_GET_OBJECT_TYPE
(paren
id|node-&gt;object
)paren
op_ne
id|ACPI_TYPE_LOCAL_DATA
)paren
)paren
(brace
id|node-&gt;object
op_assign
id|node-&gt;object-&gt;common.next_object
suffix:semicolon
)brace
)brace
multiline_comment|/* Reset the node type to untyped */
id|node-&gt;type
op_assign
id|ACPI_TYPE_ANY
suffix:semicolon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_NAMES
comma
l_string|&quot;Node %p [%4.4s] Object %p&bslash;n&quot;
comma
id|node
comma
id|acpi_ut_get_node_name
(paren
id|node
)paren
comma
id|obj_desc
)paren
)paren
suffix:semicolon
multiline_comment|/* Remove one reference on the object (and all subobjects) */
id|acpi_ut_remove_reference
(paren
id|obj_desc
)paren
suffix:semicolon
id|return_VOID
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ns_get_attached_object&n; *&n; * PARAMETERS:  Node             - Parent Node to be examined&n; *&n; * RETURN:      Current value of the object field from the Node whose&n; *              handle is passed&n; *&n; * DESCRIPTION: Obtain the object attached to a namespace node.&n; *&n; ******************************************************************************/
r_union
id|acpi_operand_object
op_star
DECL|function|acpi_ns_get_attached_object
id|acpi_ns_get_attached_object
(paren
r_struct
id|acpi_namespace_node
op_star
id|node
)paren
(brace
id|ACPI_FUNCTION_TRACE_PTR
(paren
l_string|&quot;ns_get_attached_object&quot;
comma
id|node
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|node
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_WARN
comma
l_string|&quot;Null Node ptr&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|return_PTR
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|node-&gt;object
op_logical_or
(paren
(paren
id|ACPI_GET_DESCRIPTOR_TYPE
(paren
id|node-&gt;object
)paren
op_ne
id|ACPI_DESC_TYPE_OPERAND
)paren
op_logical_and
(paren
id|ACPI_GET_DESCRIPTOR_TYPE
(paren
id|node-&gt;object
)paren
op_ne
id|ACPI_DESC_TYPE_NAMED
)paren
)paren
op_logical_or
(paren
id|ACPI_GET_OBJECT_TYPE
(paren
id|node-&gt;object
)paren
op_eq
id|ACPI_TYPE_LOCAL_DATA
)paren
)paren
(brace
id|return_PTR
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
id|return_PTR
(paren
id|node-&gt;object
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ns_get_secondary_object&n; *&n; * PARAMETERS:  Node             - Parent Node to be examined&n; *&n; * RETURN:      Current value of the object field from the Node whose&n; *              handle is passed.&n; *&n; * DESCRIPTION: Obtain a secondary object associated with a namespace node.&n; *&n; ******************************************************************************/
r_union
id|acpi_operand_object
op_star
DECL|function|acpi_ns_get_secondary_object
id|acpi_ns_get_secondary_object
(paren
r_union
id|acpi_operand_object
op_star
id|obj_desc
)paren
(brace
id|ACPI_FUNCTION_TRACE_PTR
(paren
l_string|&quot;ns_get_secondary_object&quot;
comma
id|obj_desc
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
op_logical_neg
id|obj_desc
)paren
op_logical_or
(paren
id|ACPI_GET_OBJECT_TYPE
(paren
id|obj_desc
)paren
op_eq
id|ACPI_TYPE_LOCAL_DATA
)paren
op_logical_or
(paren
op_logical_neg
id|obj_desc-&gt;common.next_object
)paren
op_logical_or
(paren
id|ACPI_GET_OBJECT_TYPE
(paren
id|obj_desc-&gt;common.next_object
)paren
op_eq
id|ACPI_TYPE_LOCAL_DATA
)paren
)paren
(brace
id|return_PTR
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
id|return_PTR
(paren
id|obj_desc-&gt;common.next_object
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ns_attach_data&n; *&n; * PARAMETERS:  Node            - Namespace node&n; *              Handler         - Handler to be associated with the data&n; *              Data            - Data to be attached&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Low-level attach data.  Create and attach a Data object.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ns_attach_data
id|acpi_ns_attach_data
(paren
r_struct
id|acpi_namespace_node
op_star
id|node
comma
id|acpi_object_handler
id|handler
comma
r_void
op_star
id|data
)paren
(brace
r_union
id|acpi_operand_object
op_star
id|prev_obj_desc
suffix:semicolon
r_union
id|acpi_operand_object
op_star
id|obj_desc
suffix:semicolon
r_union
id|acpi_operand_object
op_star
id|data_desc
suffix:semicolon
multiline_comment|/* We only allow one attachment per handler */
id|prev_obj_desc
op_assign
l_int|NULL
suffix:semicolon
id|obj_desc
op_assign
id|node-&gt;object
suffix:semicolon
r_while
c_loop
(paren
id|obj_desc
)paren
(brace
r_if
c_cond
(paren
(paren
id|ACPI_GET_OBJECT_TYPE
(paren
id|obj_desc
)paren
op_eq
id|ACPI_TYPE_LOCAL_DATA
)paren
op_logical_and
(paren
id|obj_desc-&gt;data.handler
op_eq
id|handler
)paren
)paren
(brace
r_return
(paren
id|AE_ALREADY_EXISTS
)paren
suffix:semicolon
)brace
id|prev_obj_desc
op_assign
id|obj_desc
suffix:semicolon
id|obj_desc
op_assign
id|obj_desc-&gt;common.next_object
suffix:semicolon
)brace
multiline_comment|/* Create an internal object for the data */
id|data_desc
op_assign
id|acpi_ut_create_internal_object
(paren
id|ACPI_TYPE_LOCAL_DATA
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|data_desc
)paren
(brace
r_return
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
)brace
id|data_desc-&gt;data.handler
op_assign
id|handler
suffix:semicolon
id|data_desc-&gt;data.pointer
op_assign
id|data
suffix:semicolon
multiline_comment|/* Install the data object */
r_if
c_cond
(paren
id|prev_obj_desc
)paren
(brace
id|prev_obj_desc-&gt;common.next_object
op_assign
id|data_desc
suffix:semicolon
)brace
r_else
(brace
id|node-&gt;object
op_assign
id|data_desc
suffix:semicolon
)brace
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ns_detach_data&n; *&n; * PARAMETERS:  Node            - Namespace node&n; *              Handler         - Handler associated with the data&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Low-level detach data.  Delete the data node, but the caller&n; *              is responsible for the actual data.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ns_detach_data
id|acpi_ns_detach_data
(paren
r_struct
id|acpi_namespace_node
op_star
id|node
comma
id|acpi_object_handler
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
id|prev_obj_desc
suffix:semicolon
id|prev_obj_desc
op_assign
l_int|NULL
suffix:semicolon
id|obj_desc
op_assign
id|node-&gt;object
suffix:semicolon
r_while
c_loop
(paren
id|obj_desc
)paren
(brace
r_if
c_cond
(paren
(paren
id|ACPI_GET_OBJECT_TYPE
(paren
id|obj_desc
)paren
op_eq
id|ACPI_TYPE_LOCAL_DATA
)paren
op_logical_and
(paren
id|obj_desc-&gt;data.handler
op_eq
id|handler
)paren
)paren
(brace
r_if
c_cond
(paren
id|prev_obj_desc
)paren
(brace
id|prev_obj_desc-&gt;common.next_object
op_assign
id|obj_desc-&gt;common.next_object
suffix:semicolon
)brace
r_else
(brace
id|node-&gt;object
op_assign
id|obj_desc-&gt;common.next_object
suffix:semicolon
)brace
id|acpi_ut_remove_reference
(paren
id|obj_desc
)paren
suffix:semicolon
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
id|prev_obj_desc
op_assign
id|obj_desc
suffix:semicolon
id|obj_desc
op_assign
id|obj_desc-&gt;common.next_object
suffix:semicolon
)brace
r_return
(paren
id|AE_NOT_FOUND
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ns_get_attached_data&n; *&n; * PARAMETERS:  Node            - Namespace node&n; *              Handler         - Handler associated with the data&n; *              Data            - Where the data is returned&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Low level interface to obtain data previously associated with&n; *              a namespace node.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ns_get_attached_data
id|acpi_ns_get_attached_data
(paren
r_struct
id|acpi_namespace_node
op_star
id|node
comma
id|acpi_object_handler
id|handler
comma
r_void
op_star
op_star
id|data
)paren
(brace
r_union
id|acpi_operand_object
op_star
id|obj_desc
suffix:semicolon
id|obj_desc
op_assign
id|node-&gt;object
suffix:semicolon
r_while
c_loop
(paren
id|obj_desc
)paren
(brace
r_if
c_cond
(paren
(paren
id|ACPI_GET_OBJECT_TYPE
(paren
id|obj_desc
)paren
op_eq
id|ACPI_TYPE_LOCAL_DATA
)paren
op_logical_and
(paren
id|obj_desc-&gt;data.handler
op_eq
id|handler
)paren
)paren
(brace
op_star
id|data
op_assign
id|obj_desc-&gt;data.pointer
suffix:semicolon
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
id|obj_desc
op_assign
id|obj_desc-&gt;common.next_object
suffix:semicolon
)brace
r_return
(paren
id|AE_NOT_FOUND
)paren
suffix:semicolon
)brace
eof
