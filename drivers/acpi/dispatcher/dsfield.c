multiline_comment|/******************************************************************************&n; *&n; * Module Name: dsfield - Dispatcher field routines&n; *              $Revision: 67 $&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000 - 2002, R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &quot;acpi.h&quot;
macro_line|#include &quot;amlcode.h&quot;
macro_line|#include &quot;acdispat.h&quot;
macro_line|#include &quot;acinterp.h&quot;
macro_line|#include &quot;acnamesp.h&quot;
macro_line|#include &quot;acparser.h&quot;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_DISPATCHER
id|ACPI_MODULE_NAME
(paren
l_string|&quot;dsfield&quot;
)paren
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ds_create_buffer_field&n; *&n; * PARAMETERS:  Opcode              - The opcode to be executed&n; *              Operands            - List of operands for the opcode&n; *              Walk_state          - Current state&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Execute the Create_field operators:&n; *              Create_bit_field_op,&n; *              Create_byte_field_op,&n; *              Create_word_field_op,&n; *              Create_dWord_field_op,&n; *              Create_qWord_field_op,&n; *              Create_field_op     (all of which define fields in buffers)&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ds_create_buffer_field
id|acpi_ds_create_buffer_field
(paren
id|acpi_parse_object
op_star
id|op
comma
id|acpi_walk_state
op_star
id|walk_state
)paren
(brace
id|acpi_parse_object
op_star
id|arg
suffix:semicolon
id|acpi_namespace_node
op_star
id|node
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
id|acpi_operand_object
op_star
id|obj_desc
suffix:semicolon
id|acpi_operand_object
op_star
id|second_desc
op_assign
l_int|NULL
suffix:semicolon
id|u32
id|flags
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;Ds_create_buffer_field&quot;
)paren
suffix:semicolon
multiline_comment|/* Get the Name_string argument */
r_if
c_cond
(paren
id|op-&gt;common.aml_opcode
op_eq
id|AML_CREATE_FIELD_OP
)paren
(brace
id|arg
op_assign
id|acpi_ps_get_arg
(paren
id|op
comma
l_int|3
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Create Bit/Byte/Word/Dword field */
id|arg
op_assign
id|acpi_ps_get_arg
(paren
id|op
comma
l_int|2
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|arg
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_AML_NO_OPERAND
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * During the load phase, we want to enter the name of the field into&n;&t; * the namespace.  During the execute phase (when we evaluate the size&n;&t; * operand), we want to lookup the name&n;&t; */
r_if
c_cond
(paren
id|walk_state-&gt;parse_flags
op_amp
id|ACPI_PARSE_EXECUTE
)paren
(brace
id|flags
op_assign
id|ACPI_NS_NO_UPSEARCH
op_or
id|ACPI_NS_DONT_OPEN_SCOPE
suffix:semicolon
)brace
r_else
(brace
id|flags
op_assign
id|ACPI_NS_NO_UPSEARCH
op_or
id|ACPI_NS_DONT_OPEN_SCOPE
op_or
id|ACPI_NS_ERROR_IF_FOUND
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Enter the Name_string into the namespace&n;&t; */
id|status
op_assign
id|acpi_ns_lookup
(paren
id|walk_state-&gt;scope_info
comma
id|arg-&gt;common.value.string
comma
id|INTERNAL_TYPE_DEF_ANY
comma
id|ACPI_IMODE_LOAD_PASS1
comma
id|flags
comma
id|walk_state
comma
op_amp
(paren
id|node
)paren
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
multiline_comment|/* We could put the returned object (Node) on the object stack for later, but&n;&t; * for now, we will put it in the &quot;op&quot; object that the parser uses, so we&n;&t; * can get it again at the end of this scope&n;&t; */
id|op-&gt;common.node
op_assign
id|node
suffix:semicolon
multiline_comment|/*&n;&t; * If there is no object attached to the node, this node was just created and&n;&t; * we need to create the field object.  Otherwise, this was a lookup of an&n;&t; * existing node and we don&squot;t want to create the field object again.&n;&t; */
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
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * The Field definition is not fully parsed at this time.&n;&t; * (We must save the address of the AML for the buffer and index operands)&n;&t; */
multiline_comment|/* Create the buffer field object */
id|obj_desc
op_assign
id|acpi_ut_create_internal_object
(paren
id|ACPI_TYPE_BUFFER_FIELD
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
id|cleanup
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Remember location in AML stream of the field unit&n;&t; * opcode and operands -- since the buffer and index&n;&t; * operands must be evaluated.&n;&t; */
id|second_desc
op_assign
id|obj_desc-&gt;common.next_object
suffix:semicolon
id|second_desc-&gt;extra.aml_start
op_assign
id|op-&gt;named.data
suffix:semicolon
id|second_desc-&gt;extra.aml_length
op_assign
id|op-&gt;named.length
suffix:semicolon
id|obj_desc-&gt;buffer_field.node
op_assign
id|node
suffix:semicolon
multiline_comment|/* Attach constructed field descriptors to parent node */
id|status
op_assign
id|acpi_ns_attach_object
(paren
id|node
comma
id|obj_desc
comma
id|ACPI_TYPE_BUFFER_FIELD
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
id|cleanup
suffix:semicolon
)brace
id|cleanup
suffix:colon
multiline_comment|/* Remove local reference to the object */
id|acpi_ut_remove_reference
(paren
id|obj_desc
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ds_get_field_names&n; *&n; * PARAMETERS:  Info            - Create_field info structure&n; *  `           Walk_state      - Current method state&n; *              Arg             - First parser arg for the field name list&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Process all named fields in a field declaration.  Names are&n; *              entered into the namespace.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ds_get_field_names
id|acpi_ds_get_field_names
(paren
id|ACPI_CREATE_FIELD_INFO
op_star
id|info
comma
id|acpi_walk_state
op_star
id|walk_state
comma
id|acpi_parse_object
op_star
id|arg
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
id|acpi_integer
id|position
suffix:semicolon
id|ACPI_FUNCTION_TRACE_PTR
(paren
l_string|&quot;Ds_get_field_names&quot;
comma
id|info
)paren
suffix:semicolon
multiline_comment|/* First field starts at bit zero */
id|info-&gt;field_bit_position
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Process all elements in the field list (of parse nodes) */
r_while
c_loop
(paren
id|arg
)paren
(brace
multiline_comment|/*&n;&t;&t; * Three types of field elements are handled:&n;&t;&t; * 1) Offset - specifies a bit offset&n;&t;&t; * 2) Access_as - changes the access mode&n;&t;&t; * 3) Name - Enters a new named field into the namespace&n;&t;&t; */
r_switch
c_cond
(paren
id|arg-&gt;common.aml_opcode
)paren
(brace
r_case
id|AML_INT_RESERVEDFIELD_OP
suffix:colon
id|position
op_assign
(paren
id|acpi_integer
)paren
id|info-&gt;field_bit_position
op_plus
(paren
id|acpi_integer
)paren
id|arg-&gt;common.value.size
suffix:semicolon
r_if
c_cond
(paren
id|position
OG
id|ACPI_UINT32_MAX
)paren
(brace
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;Bit offset within field too large (&gt; 0xFFFFFFFF)&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_SUPPORT
)paren
suffix:semicolon
)brace
id|info-&gt;field_bit_position
op_assign
(paren
id|u32
)paren
id|position
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AML_INT_ACCESSFIELD_OP
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * Get a new Access_type and Access_attribute -- to be used for all&n;&t;&t;&t; * field units that follow, until field end or another Access_as keyword.&n;&t;&t;&t; *&n;&t;&t;&t; * In Field_flags, preserve the flag bits other than the ACCESS_TYPE bits&n;&t;&t;&t; */
id|info-&gt;field_flags
op_assign
(paren
id|u8
)paren
(paren
(paren
id|info-&gt;field_flags
op_amp
op_complement
(paren
id|AML_FIELD_ACCESS_TYPE_MASK
)paren
)paren
op_or
(paren
(paren
id|u8
)paren
(paren
id|arg-&gt;common.value.integer32
op_rshift
l_int|8
)paren
)paren
)paren
suffix:semicolon
id|info-&gt;attribute
op_assign
(paren
id|u8
)paren
(paren
id|arg-&gt;common.value.integer32
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AML_INT_NAMEDFIELD_OP
suffix:colon
multiline_comment|/* Lookup the name */
id|status
op_assign
id|acpi_ns_lookup
(paren
id|walk_state-&gt;scope_info
comma
(paren
id|NATIVE_CHAR
op_star
)paren
op_amp
id|arg-&gt;named.name
comma
id|info-&gt;field_type
comma
id|ACPI_IMODE_EXECUTE
comma
id|ACPI_NS_DONT_OPEN_SCOPE
comma
id|walk_state
comma
op_amp
id|info-&gt;field_node
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
r_if
c_cond
(paren
id|status
op_ne
id|AE_ALREADY_EXISTS
)paren
(brace
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;Field name [%4.4s] already exists in current scope&bslash;n&quot;
comma
(paren
r_char
op_star
)paren
op_amp
id|arg-&gt;named.name
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|arg-&gt;common.node
op_assign
id|info-&gt;field_node
suffix:semicolon
id|info-&gt;field_bit_length
op_assign
id|arg-&gt;common.value.size
suffix:semicolon
multiline_comment|/* Create and initialize an object for the new Field Node */
id|status
op_assign
id|acpi_ex_prep_field_value
(paren
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
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Keep track of bit position for the next field */
id|position
op_assign
(paren
id|acpi_integer
)paren
id|info-&gt;field_bit_position
op_plus
(paren
id|acpi_integer
)paren
id|arg-&gt;common.value.size
suffix:semicolon
r_if
c_cond
(paren
id|position
OG
id|ACPI_UINT32_MAX
)paren
(brace
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;Field [%4.4s] bit offset too large (&gt; 0xFFFFFFFF)&bslash;n&quot;
comma
(paren
r_char
op_star
)paren
op_amp
id|info-&gt;field_node-&gt;name
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_SUPPORT
)paren
suffix:semicolon
)brace
id|info-&gt;field_bit_position
op_add_assign
id|info-&gt;field_bit_length
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Invalid opcode in field list: %X&bslash;n&quot;
comma
id|arg-&gt;common.aml_opcode
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_AML_BAD_OPCODE
)paren
suffix:semicolon
)brace
id|arg
op_assign
id|arg-&gt;common.next
suffix:semicolon
)brace
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ds_create_field&n; *&n; * PARAMETERS:  Op              - Op containing the Field definition and args&n; *              Region_node     - Object for the containing Operation Region&n; *  `           Walk_state      - Current method state&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Create a new field in the specified operation region&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ds_create_field
id|acpi_ds_create_field
(paren
id|acpi_parse_object
op_star
id|op
comma
id|acpi_namespace_node
op_star
id|region_node
comma
id|acpi_walk_state
op_star
id|walk_state
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
id|acpi_parse_object
op_star
id|arg
suffix:semicolon
id|ACPI_CREATE_FIELD_INFO
id|info
suffix:semicolon
id|ACPI_FUNCTION_TRACE_PTR
(paren
l_string|&quot;Ds_create_field&quot;
comma
id|op
)paren
suffix:semicolon
multiline_comment|/* First arg is the name of the parent Op_region (must already exist) */
id|arg
op_assign
id|op-&gt;common.value.arg
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|region_node
)paren
(brace
id|status
op_assign
id|acpi_ns_lookup
(paren
id|walk_state-&gt;scope_info
comma
id|arg-&gt;common.value.name
comma
id|ACPI_TYPE_REGION
comma
id|ACPI_IMODE_EXECUTE
comma
id|ACPI_NS_SEARCH_PARENT
comma
id|walk_state
comma
op_amp
id|region_node
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
)brace
multiline_comment|/* Second arg is the field flags */
id|arg
op_assign
id|arg-&gt;common.next
suffix:semicolon
id|info.field_flags
op_assign
id|arg-&gt;common.value.integer8
suffix:semicolon
id|info.attribute
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Each remaining arg is a Named Field */
id|info.field_type
op_assign
id|INTERNAL_TYPE_REGION_FIELD
suffix:semicolon
id|info.region_node
op_assign
id|region_node
suffix:semicolon
id|status
op_assign
id|acpi_ds_get_field_names
(paren
op_amp
id|info
comma
id|walk_state
comma
id|arg-&gt;common.next
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ds_init_field_objects&n; *&n; * PARAMETERS:  Op              - Op containing the Field definition and args&n; *  `           Walk_state      - Current method state&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: For each &quot;Field Unit&quot; name in the argument list that is&n; *              part of the field declaration, enter the name into the&n; *              namespace.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ds_init_field_objects
id|acpi_ds_init_field_objects
(paren
id|acpi_parse_object
op_star
id|op
comma
id|acpi_walk_state
op_star
id|walk_state
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
id|acpi_parse_object
op_star
id|arg
op_assign
l_int|NULL
suffix:semicolon
id|acpi_namespace_node
op_star
id|node
suffix:semicolon
id|u8
id|type
op_assign
l_int|0
suffix:semicolon
id|ACPI_FUNCTION_TRACE_PTR
(paren
l_string|&quot;Ds_init_field_objects&quot;
comma
id|op
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|walk_state-&gt;opcode
)paren
(brace
r_case
id|AML_FIELD_OP
suffix:colon
id|arg
op_assign
id|acpi_ps_get_arg
(paren
id|op
comma
l_int|2
)paren
suffix:semicolon
id|type
op_assign
id|INTERNAL_TYPE_REGION_FIELD
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AML_BANK_FIELD_OP
suffix:colon
id|arg
op_assign
id|acpi_ps_get_arg
(paren
id|op
comma
l_int|4
)paren
suffix:semicolon
id|type
op_assign
id|INTERNAL_TYPE_BANK_FIELD
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AML_INDEX_FIELD_OP
suffix:colon
id|arg
op_assign
id|acpi_ps_get_arg
(paren
id|op
comma
l_int|3
)paren
suffix:semicolon
id|type
op_assign
id|INTERNAL_TYPE_INDEX_FIELD
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
multiline_comment|/*&n;&t; * Walk the list of entries in the Field_list&n;&t; */
r_while
c_loop
(paren
id|arg
)paren
(brace
multiline_comment|/* Ignore OFFSET and ACCESSAS terms here */
r_if
c_cond
(paren
id|arg-&gt;common.aml_opcode
op_eq
id|AML_INT_NAMEDFIELD_OP
)paren
(brace
id|status
op_assign
id|acpi_ns_lookup
(paren
id|walk_state-&gt;scope_info
comma
(paren
id|NATIVE_CHAR
op_star
)paren
op_amp
id|arg-&gt;named.name
comma
id|type
comma
id|ACPI_IMODE_LOAD_PASS1
comma
id|ACPI_NS_NO_UPSEARCH
op_or
id|ACPI_NS_DONT_OPEN_SCOPE
op_or
id|ACPI_NS_ERROR_IF_FOUND
comma
id|walk_state
comma
op_amp
id|node
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
r_if
c_cond
(paren
id|status
op_ne
id|AE_ALREADY_EXISTS
)paren
(brace
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;Field name [%4.4s] already exists in current scope&bslash;n&quot;
comma
(paren
r_char
op_star
)paren
op_amp
id|arg-&gt;named.name
)paren
)paren
suffix:semicolon
multiline_comment|/* Name already exists, just ignore this error */
id|status
op_assign
id|AE_OK
suffix:semicolon
)brace
id|arg-&gt;common.node
op_assign
id|node
suffix:semicolon
)brace
multiline_comment|/* Move to next field in the list */
id|arg
op_assign
id|arg-&gt;common.next
suffix:semicolon
)brace
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ds_create_bank_field&n; *&n; * PARAMETERS:  Op              - Op containing the Field definition and args&n; *              Region_node     - Object for the containing Operation Region&n; *  `           Walk_state      - Current method state&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Create a new bank field in the specified operation region&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ds_create_bank_field
id|acpi_ds_create_bank_field
(paren
id|acpi_parse_object
op_star
id|op
comma
id|acpi_namespace_node
op_star
id|region_node
comma
id|acpi_walk_state
op_star
id|walk_state
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
id|acpi_parse_object
op_star
id|arg
suffix:semicolon
id|ACPI_CREATE_FIELD_INFO
id|info
suffix:semicolon
id|ACPI_FUNCTION_TRACE_PTR
(paren
l_string|&quot;Ds_create_bank_field&quot;
comma
id|op
)paren
suffix:semicolon
multiline_comment|/* First arg is the name of the parent Op_region (must already exist) */
id|arg
op_assign
id|op-&gt;common.value.arg
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|region_node
)paren
(brace
id|status
op_assign
id|acpi_ns_lookup
(paren
id|walk_state-&gt;scope_info
comma
id|arg-&gt;common.value.name
comma
id|ACPI_TYPE_REGION
comma
id|ACPI_IMODE_EXECUTE
comma
id|ACPI_NS_SEARCH_PARENT
comma
id|walk_state
comma
op_amp
id|region_node
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
)brace
multiline_comment|/* Second arg is the Bank Register (must already exist) */
id|arg
op_assign
id|arg-&gt;common.next
suffix:semicolon
id|status
op_assign
id|acpi_ns_lookup
(paren
id|walk_state-&gt;scope_info
comma
id|arg-&gt;common.value.string
comma
id|INTERNAL_TYPE_BANK_FIELD_DEFN
comma
id|ACPI_IMODE_EXECUTE
comma
id|ACPI_NS_SEARCH_PARENT
comma
id|walk_state
comma
op_amp
id|info.register_node
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
multiline_comment|/* Third arg is the Bank_value */
id|arg
op_assign
id|arg-&gt;common.next
suffix:semicolon
id|info.bank_value
op_assign
id|arg-&gt;common.value.integer32
suffix:semicolon
multiline_comment|/* Fourth arg is the field flags */
id|arg
op_assign
id|arg-&gt;common.next
suffix:semicolon
id|info.field_flags
op_assign
id|arg-&gt;common.value.integer8
suffix:semicolon
multiline_comment|/* Each remaining arg is a Named Field */
id|info.field_type
op_assign
id|INTERNAL_TYPE_BANK_FIELD
suffix:semicolon
id|info.region_node
op_assign
id|region_node
suffix:semicolon
id|status
op_assign
id|acpi_ds_get_field_names
(paren
op_amp
id|info
comma
id|walk_state
comma
id|arg-&gt;common.next
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ds_create_index_field&n; *&n; * PARAMETERS:  Op              - Op containing the Field definition and args&n; *              Region_node     - Object for the containing Operation Region&n; *  `           Walk_state      - Current method state&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Create a new index field in the specified operation region&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ds_create_index_field
id|acpi_ds_create_index_field
(paren
id|acpi_parse_object
op_star
id|op
comma
id|acpi_namespace_node
op_star
id|region_node
comma
id|acpi_walk_state
op_star
id|walk_state
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
id|acpi_parse_object
op_star
id|arg
suffix:semicolon
id|ACPI_CREATE_FIELD_INFO
id|info
suffix:semicolon
id|ACPI_FUNCTION_TRACE_PTR
(paren
l_string|&quot;Ds_create_index_field&quot;
comma
id|op
)paren
suffix:semicolon
multiline_comment|/* First arg is the name of the Index register (must already exist) */
id|arg
op_assign
id|op-&gt;common.value.arg
suffix:semicolon
id|status
op_assign
id|acpi_ns_lookup
(paren
id|walk_state-&gt;scope_info
comma
id|arg-&gt;common.value.string
comma
id|ACPI_TYPE_ANY
comma
id|ACPI_IMODE_EXECUTE
comma
id|ACPI_NS_SEARCH_PARENT
comma
id|walk_state
comma
op_amp
id|info.register_node
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
multiline_comment|/* Second arg is the data register (must already exist) */
id|arg
op_assign
id|arg-&gt;common.next
suffix:semicolon
id|status
op_assign
id|acpi_ns_lookup
(paren
id|walk_state-&gt;scope_info
comma
id|arg-&gt;common.value.string
comma
id|INTERNAL_TYPE_INDEX_FIELD_DEFN
comma
id|ACPI_IMODE_EXECUTE
comma
id|ACPI_NS_SEARCH_PARENT
comma
id|walk_state
comma
op_amp
id|info.data_register_node
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
multiline_comment|/* Next arg is the field flags */
id|arg
op_assign
id|arg-&gt;common.next
suffix:semicolon
id|info.field_flags
op_assign
id|arg-&gt;common.value.integer8
suffix:semicolon
multiline_comment|/* Each remaining arg is a Named Field */
id|info.field_type
op_assign
id|INTERNAL_TYPE_INDEX_FIELD
suffix:semicolon
id|info.region_node
op_assign
id|region_node
suffix:semicolon
id|status
op_assign
id|acpi_ds_get_field_names
(paren
op_amp
id|info
comma
id|walk_state
comma
id|arg-&gt;common.next
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
eof
