multiline_comment|/******************************************************************************&n; *&n; * Module Name: nsdump - table dumping routines for debug&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000 - 2002, R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &quot;acpi.h&quot;
macro_line|#include &quot;acnamesp.h&quot;
macro_line|#include &quot;acparser.h&quot;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_NAMESPACE
id|ACPI_MODULE_NAME
(paren
l_string|&quot;nsdump&quot;
)paren
macro_line|#if defined(ACPI_DEBUG_OUTPUT) || defined(ACPI_DEBUGGER)
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ns_print_pathname&n; *&n; * PARAMETERS:  Num_segment         - Number of ACPI name segments&n; *              Pathname            - The compressed (internal) path&n; *&n; * DESCRIPTION: Print an object&squot;s full namespace pathname&n; *&n; ******************************************************************************/
r_void
DECL|function|acpi_ns_print_pathname
id|acpi_ns_print_pathname
(paren
id|u32
id|num_segments
comma
r_char
op_star
id|pathname
)paren
(brace
id|ACPI_FUNCTION_NAME
(paren
l_string|&quot;Ns_print_pathname&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|acpi_dbg_level
op_amp
id|ACPI_LV_NAMES
)paren
op_logical_or
op_logical_neg
(paren
id|acpi_dbg_layer
op_amp
id|ACPI_NAMESPACE
)paren
)paren
(brace
r_return
suffix:semicolon
)brace
multiline_comment|/* Print the entire name */
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_NAMES
comma
l_string|&quot;[&quot;
)paren
)paren
suffix:semicolon
r_while
c_loop
(paren
id|num_segments
)paren
(brace
id|acpi_os_printf
(paren
l_string|&quot;%4.4s&quot;
comma
id|pathname
)paren
suffix:semicolon
id|pathname
op_add_assign
id|ACPI_NAME_SIZE
suffix:semicolon
id|num_segments
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|num_segments
)paren
(brace
id|acpi_os_printf
(paren
l_string|&quot;.&quot;
)paren
suffix:semicolon
)brace
)brace
id|acpi_os_printf
(paren
l_string|&quot;]&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ns_dump_pathname&n; *&n; * PARAMETERS:  Handle              - Object&n; *              Msg                 - Prefix message&n; *              Level               - Desired debug level&n; *              Component           - Caller&squot;s component ID&n; *&n; * DESCRIPTION: Print an object&squot;s full namespace pathname&n; *              Manages allocation/freeing of a pathname buffer&n; *&n; ******************************************************************************/
r_void
DECL|function|acpi_ns_dump_pathname
id|acpi_ns_dump_pathname
(paren
id|acpi_handle
id|handle
comma
r_char
op_star
id|msg
comma
id|u32
id|level
comma
id|u32
id|component
)paren
(brace
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;Ns_dump_pathname&quot;
)paren
suffix:semicolon
multiline_comment|/* Do this only if the requested debug level and component are enabled */
r_if
c_cond
(paren
op_logical_neg
(paren
id|acpi_dbg_level
op_amp
id|level
)paren
op_logical_or
op_logical_neg
(paren
id|acpi_dbg_layer
op_amp
id|component
)paren
)paren
(brace
id|return_VOID
suffix:semicolon
)brace
multiline_comment|/* Convert handle to a full pathname and print it (with supplied message) */
id|acpi_ns_print_node_pathname
(paren
id|handle
comma
id|msg
)paren
suffix:semicolon
id|acpi_os_printf
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|return_VOID
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ns_dump_one_object&n; *&n; * PARAMETERS:  Handle              - Node to be dumped&n; *              Level               - Nesting level of the handle&n; *              Context             - Passed into Walk_namespace&n; *&n; * DESCRIPTION: Dump a single Node&n; *              This procedure is a User_function called by Acpi_ns_walk_namespace.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ns_dump_one_object
id|acpi_ns_dump_one_object
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
id|acpi_walk_info
op_star
id|info
op_assign
(paren
id|acpi_walk_info
op_star
)paren
id|context
suffix:semicolon
id|acpi_namespace_node
op_star
id|this_node
suffix:semicolon
id|acpi_operand_object
op_star
id|obj_desc
op_assign
l_int|NULL
suffix:semicolon
id|acpi_object_type
id|obj_type
suffix:semicolon
id|acpi_object_type
id|type
suffix:semicolon
id|u32
id|bytes_to_dump
suffix:semicolon
id|u32
id|dbg_level
suffix:semicolon
id|u32
id|i
suffix:semicolon
id|ACPI_FUNCTION_NAME
(paren
l_string|&quot;Ns_dump_one_object&quot;
)paren
suffix:semicolon
multiline_comment|/* Is output enabled? */
r_if
c_cond
(paren
op_logical_neg
(paren
id|acpi_dbg_level
op_amp
id|info-&gt;debug_level
)paren
)paren
(brace
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|obj_handle
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;Null object handle&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
id|this_node
op_assign
id|acpi_ns_map_handle_to_node
(paren
id|obj_handle
)paren
suffix:semicolon
id|type
op_assign
id|this_node-&gt;type
suffix:semicolon
multiline_comment|/* Check if the owner matches */
r_if
c_cond
(paren
(paren
id|info-&gt;owner_id
op_ne
id|ACPI_UINT32_MAX
)paren
op_logical_and
(paren
id|info-&gt;owner_id
op_ne
id|this_node-&gt;owner_id
)paren
)paren
(brace
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/* Indent the object according to the level */
id|acpi_os_printf
(paren
l_string|&quot;%2d%*s&quot;
comma
(paren
id|u32
)paren
id|level
op_minus
l_int|1
comma
(paren
r_int
)paren
id|level
op_star
l_int|2
comma
l_string|&quot; &quot;
)paren
suffix:semicolon
multiline_comment|/* Check the node type and name */
r_if
c_cond
(paren
id|type
OG
id|ACPI_TYPE_LOCAL_MAX
)paren
(brace
id|ACPI_REPORT_WARNING
(paren
(paren
l_string|&quot;Invalid ACPI Type %08X&bslash;n&quot;
comma
id|type
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|acpi_ut_valid_acpi_name
(paren
id|this_node-&gt;name.integer
)paren
)paren
(brace
id|ACPI_REPORT_WARNING
(paren
(paren
l_string|&quot;Invalid ACPI Name %08X&bslash;n&quot;
comma
id|this_node-&gt;name.integer
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Now we can print out the pertinent information&n;&t; */
id|acpi_os_printf
(paren
l_string|&quot;%4.4s %-12s %p &quot;
comma
id|this_node-&gt;name.ascii
comma
id|acpi_ut_get_type_name
(paren
id|type
)paren
comma
id|this_node
)paren
suffix:semicolon
id|dbg_level
op_assign
id|acpi_dbg_level
suffix:semicolon
id|acpi_dbg_level
op_assign
l_int|0
suffix:semicolon
id|obj_desc
op_assign
id|acpi_ns_get_attached_object
(paren
id|this_node
)paren
suffix:semicolon
id|acpi_dbg_level
op_assign
id|dbg_level
suffix:semicolon
r_switch
c_cond
(paren
id|info-&gt;display_type
)paren
(brace
r_case
id|ACPI_DISPLAY_SUMMARY
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|obj_desc
)paren
(brace
multiline_comment|/* No attached object, we are done */
id|acpi_os_printf
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|type
)paren
(brace
r_case
id|ACPI_TYPE_PROCESSOR
suffix:colon
id|acpi_os_printf
(paren
l_string|&quot;ID %X Len %.4X Addr %p&bslash;n&quot;
comma
id|obj_desc-&gt;processor.proc_id
comma
id|obj_desc-&gt;processor.length
comma
(paren
r_char
op_star
)paren
id|obj_desc-&gt;processor.address
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_DEVICE
suffix:colon
id|acpi_os_printf
(paren
l_string|&quot;Notify object: %p&quot;
comma
id|obj_desc
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_METHOD
suffix:colon
id|acpi_os_printf
(paren
l_string|&quot;Args %X Len %.4X Aml %p&bslash;n&quot;
comma
(paren
id|u32
)paren
id|obj_desc-&gt;method.param_count
comma
id|obj_desc-&gt;method.aml_length
comma
id|obj_desc-&gt;method.aml_start
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_INTEGER
suffix:colon
id|acpi_os_printf
(paren
l_string|&quot;= %8.8X%8.8X&bslash;n&quot;
comma
id|ACPI_HIDWORD
(paren
id|obj_desc-&gt;integer.value
)paren
comma
id|ACPI_LODWORD
(paren
id|obj_desc-&gt;integer.value
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_PACKAGE
suffix:colon
r_if
c_cond
(paren
id|obj_desc-&gt;common.flags
op_amp
id|AOPOBJ_DATA_VALID
)paren
(brace
id|acpi_os_printf
(paren
l_string|&quot;Elements %.2X&bslash;n&quot;
comma
id|obj_desc-&gt;package.count
)paren
suffix:semicolon
)brace
r_else
(brace
id|acpi_os_printf
(paren
l_string|&quot;[Length not yet evaluated]&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_BUFFER
suffix:colon
r_if
c_cond
(paren
id|obj_desc-&gt;common.flags
op_amp
id|AOPOBJ_DATA_VALID
)paren
(brace
id|acpi_os_printf
(paren
l_string|&quot;Len %.2X&quot;
comma
id|obj_desc-&gt;buffer.length
)paren
suffix:semicolon
multiline_comment|/* Dump some of the buffer */
r_if
c_cond
(paren
id|obj_desc-&gt;buffer.length
OG
l_int|0
)paren
(brace
id|acpi_os_printf
(paren
l_string|&quot; =&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
(paren
id|i
OL
id|obj_desc-&gt;buffer.length
op_logical_and
id|i
OL
l_int|12
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|acpi_os_printf
(paren
l_string|&quot; %.2hX&quot;
comma
id|obj_desc-&gt;buffer.pointer
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
)brace
id|acpi_os_printf
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|acpi_os_printf
(paren
l_string|&quot;[Length not yet evaluated]&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_STRING
suffix:colon
id|acpi_os_printf
(paren
l_string|&quot;Len %.2X &quot;
comma
id|obj_desc-&gt;string.length
)paren
suffix:semicolon
id|acpi_ut_print_string
(paren
id|obj_desc-&gt;string.pointer
comma
l_int|32
)paren
suffix:semicolon
id|acpi_os_printf
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_REGION
suffix:colon
id|acpi_os_printf
(paren
l_string|&quot;[%s]&quot;
comma
id|acpi_ut_get_region_name
(paren
id|obj_desc-&gt;region.space_id
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|obj_desc-&gt;region.flags
op_amp
id|AOPOBJ_DATA_VALID
)paren
(brace
id|acpi_os_printf
(paren
l_string|&quot; Addr %8.8X%8.8X Len %.4X&bslash;n&quot;
comma
id|ACPI_HIDWORD
(paren
id|obj_desc-&gt;region.address
)paren
comma
id|ACPI_LODWORD
(paren
id|obj_desc-&gt;region.address
)paren
comma
id|obj_desc-&gt;region.length
)paren
suffix:semicolon
)brace
r_else
(brace
id|acpi_os_printf
(paren
l_string|&quot; [Address/Length not yet evaluated]&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_LOCAL_REFERENCE
suffix:colon
id|acpi_os_printf
(paren
l_string|&quot;[%s]&bslash;n&quot;
comma
id|acpi_ps_get_opcode_name
(paren
id|obj_desc-&gt;reference.opcode
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_BUFFER_FIELD
suffix:colon
r_if
c_cond
(paren
id|obj_desc-&gt;buffer_field.buffer_obj
op_logical_and
id|obj_desc-&gt;buffer_field.buffer_obj-&gt;buffer.node
)paren
(brace
id|acpi_os_printf
(paren
l_string|&quot;Buf [%4.4s]&quot;
comma
id|obj_desc-&gt;buffer_field.buffer_obj-&gt;buffer.node-&gt;name.ascii
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_LOCAL_REGION_FIELD
suffix:colon
id|acpi_os_printf
(paren
l_string|&quot;Rgn [%4.4s]&quot;
comma
id|obj_desc-&gt;common_field.region_obj-&gt;region.node-&gt;name.ascii
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_LOCAL_BANK_FIELD
suffix:colon
id|acpi_os_printf
(paren
l_string|&quot;Rgn [%4.4s] Bnk [%4.4s]&quot;
comma
id|obj_desc-&gt;common_field.region_obj-&gt;region.node-&gt;name.ascii
comma
id|obj_desc-&gt;bank_field.bank_obj-&gt;common_field.node-&gt;name.ascii
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_LOCAL_INDEX_FIELD
suffix:colon
id|acpi_os_printf
(paren
l_string|&quot;Idx [%4.4s] Dat [%4.4s]&quot;
comma
id|obj_desc-&gt;index_field.index_obj-&gt;common_field.node-&gt;name.ascii
comma
id|obj_desc-&gt;index_field.data_obj-&gt;common_field.node-&gt;name.ascii
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_LOCAL_ALIAS
suffix:colon
id|acpi_os_printf
(paren
l_string|&quot;Target %4.4s (%p)&bslash;n&quot;
comma
(paren
(paren
id|acpi_namespace_node
op_star
)paren
id|obj_desc
)paren
op_member_access_from_pointer
id|name.ascii
comma
id|obj_desc
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|acpi_os_printf
(paren
l_string|&quot;Object %p&bslash;n&quot;
comma
id|obj_desc
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* Common field handling */
r_switch
c_cond
(paren
id|type
)paren
(brace
r_case
id|ACPI_TYPE_BUFFER_FIELD
suffix:colon
r_case
id|ACPI_TYPE_LOCAL_REGION_FIELD
suffix:colon
r_case
id|ACPI_TYPE_LOCAL_BANK_FIELD
suffix:colon
r_case
id|ACPI_TYPE_LOCAL_INDEX_FIELD
suffix:colon
id|acpi_os_printf
(paren
l_string|&quot; Off %.2X Len %.2X Acc %.2hd&bslash;n&quot;
comma
(paren
id|obj_desc-&gt;common_field.base_byte_offset
op_star
l_int|8
)paren
op_plus
id|obj_desc-&gt;common_field.start_field_bit_offset
comma
id|obj_desc-&gt;common_field.bit_length
comma
id|obj_desc-&gt;common_field.access_byte_width
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|ACPI_DISPLAY_OBJECTS
suffix:colon
id|acpi_os_printf
(paren
l_string|&quot;O:%p&quot;
comma
id|obj_desc
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|obj_desc
)paren
(brace
multiline_comment|/* No attached object, we are done */
id|acpi_os_printf
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
id|acpi_os_printf
(paren
l_string|&quot;(R%d)&quot;
comma
id|obj_desc-&gt;common.reference_count
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|type
)paren
(brace
r_case
id|ACPI_TYPE_METHOD
suffix:colon
multiline_comment|/* Name is a Method and its AML offset/length are set */
id|acpi_os_printf
(paren
l_string|&quot; M:%p-%X&bslash;n&quot;
comma
id|obj_desc-&gt;method.aml_start
comma
id|obj_desc-&gt;method.aml_length
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_INTEGER
suffix:colon
id|acpi_os_printf
(paren
l_string|&quot; N:%X%X&bslash;n&quot;
comma
id|ACPI_HIDWORD
c_func
(paren
id|obj_desc-&gt;integer.value
)paren
comma
id|ACPI_LODWORD
c_func
(paren
id|obj_desc-&gt;integer.value
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_STRING
suffix:colon
id|acpi_os_printf
(paren
l_string|&quot; S:%p-%X&bslash;n&quot;
comma
id|obj_desc-&gt;string.pointer
comma
id|obj_desc-&gt;string.length
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_BUFFER
suffix:colon
id|acpi_os_printf
(paren
l_string|&quot; B:%p-%X&bslash;n&quot;
comma
id|obj_desc-&gt;buffer.pointer
comma
id|obj_desc-&gt;buffer.length
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|acpi_os_printf
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
id|acpi_os_printf
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* If debug turned off, done */
r_if
c_cond
(paren
op_logical_neg
(paren
id|acpi_dbg_level
op_amp
id|ACPI_LV_VALUES
)paren
)paren
(brace
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/* If there is an attached object, display it */
id|dbg_level
op_assign
id|acpi_dbg_level
suffix:semicolon
id|acpi_dbg_level
op_assign
l_int|0
suffix:semicolon
id|obj_desc
op_assign
id|acpi_ns_get_attached_object
(paren
id|this_node
)paren
suffix:semicolon
id|acpi_dbg_level
op_assign
id|dbg_level
suffix:semicolon
multiline_comment|/* Dump attached objects */
r_while
c_loop
(paren
id|obj_desc
)paren
(brace
id|obj_type
op_assign
id|ACPI_TYPE_INVALID
suffix:semicolon
id|acpi_os_printf
(paren
l_string|&quot;      Attached Object %p: &quot;
comma
id|obj_desc
)paren
suffix:semicolon
multiline_comment|/* Decode the type of attached object and dump the contents */
r_switch
c_cond
(paren
id|ACPI_GET_DESCRIPTOR_TYPE
(paren
id|obj_desc
)paren
)paren
(brace
r_case
id|ACPI_DESC_TYPE_NAMED
suffix:colon
id|acpi_os_printf
(paren
l_string|&quot;(Ptr to Node)&bslash;n&quot;
)paren
suffix:semicolon
id|bytes_to_dump
op_assign
r_sizeof
(paren
id|acpi_namespace_node
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_DESC_TYPE_OPERAND
suffix:colon
id|obj_type
op_assign
id|ACPI_GET_OBJECT_TYPE
(paren
id|obj_desc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|obj_type
OG
id|ACPI_TYPE_LOCAL_MAX
)paren
(brace
id|acpi_os_printf
(paren
l_string|&quot;(Ptr to ACPI Object type %X [UNKNOWN])&bslash;n&quot;
comma
id|obj_type
)paren
suffix:semicolon
id|bytes_to_dump
op_assign
l_int|32
suffix:semicolon
)brace
r_else
(brace
id|acpi_os_printf
(paren
l_string|&quot;(Ptr to ACPI Object type %s, %X)&bslash;n&quot;
comma
id|acpi_ut_get_type_name
(paren
id|obj_type
)paren
comma
id|obj_type
)paren
suffix:semicolon
id|bytes_to_dump
op_assign
r_sizeof
(paren
id|acpi_operand_object
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
id|acpi_os_printf
(paren
l_string|&quot;(String or Buffer ptr - not an object descriptor)&bslash;n&quot;
)paren
suffix:semicolon
id|bytes_to_dump
op_assign
l_int|16
suffix:semicolon
r_break
suffix:semicolon
)brace
id|ACPI_DUMP_BUFFER
(paren
id|obj_desc
comma
id|bytes_to_dump
)paren
suffix:semicolon
multiline_comment|/* If value is NOT an internal object, we are done */
r_if
c_cond
(paren
id|ACPI_GET_DESCRIPTOR_TYPE
(paren
id|obj_desc
)paren
op_ne
id|ACPI_DESC_TYPE_OPERAND
)paren
(brace
r_goto
id|cleanup
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Valid object, get the pointer to next level, if any&n;&t;&t; */
r_switch
c_cond
(paren
id|obj_type
)paren
(brace
r_case
id|ACPI_TYPE_STRING
suffix:colon
id|obj_desc
op_assign
(paren
r_void
op_star
)paren
id|obj_desc-&gt;string.pointer
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_BUFFER
suffix:colon
id|obj_desc
op_assign
(paren
r_void
op_star
)paren
id|obj_desc-&gt;buffer.pointer
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_BUFFER_FIELD
suffix:colon
id|obj_desc
op_assign
(paren
id|acpi_operand_object
op_star
)paren
id|obj_desc-&gt;buffer_field.buffer_obj
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_PACKAGE
suffix:colon
id|obj_desc
op_assign
(paren
r_void
op_star
)paren
id|obj_desc-&gt;package.elements
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_METHOD
suffix:colon
id|obj_desc
op_assign
(paren
r_void
op_star
)paren
id|obj_desc-&gt;method.aml_start
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_LOCAL_REGION_FIELD
suffix:colon
id|obj_desc
op_assign
(paren
r_void
op_star
)paren
id|obj_desc-&gt;field.region_obj
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_LOCAL_BANK_FIELD
suffix:colon
id|obj_desc
op_assign
(paren
r_void
op_star
)paren
id|obj_desc-&gt;bank_field.region_obj
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_LOCAL_INDEX_FIELD
suffix:colon
id|obj_desc
op_assign
(paren
r_void
op_star
)paren
id|obj_desc-&gt;index_field.index_obj
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_goto
id|cleanup
suffix:semicolon
)brace
id|obj_type
op_assign
id|ACPI_TYPE_INVALID
suffix:semicolon
multiline_comment|/* Terminate loop after next pass */
)brace
id|cleanup
suffix:colon
id|acpi_os_printf
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ns_dump_objects&n; *&n; * PARAMETERS:  Type                - Object type to be dumped&n; *              Max_depth           - Maximum depth of dump.  Use ACPI_UINT32_MAX&n; *                                    for an effectively unlimited depth.&n; *              Owner_id            - Dump only objects owned by this ID.  Use&n; *                                    ACPI_UINT32_MAX to match all owners.&n; *              Start_handle        - Where in namespace to start/end search&n; *&n; * DESCRIPTION: Dump typed objects within the loaded namespace.&n; *              Uses Acpi_ns_walk_namespace in conjunction with Acpi_ns_dump_one_object.&n; *&n; ******************************************************************************/
r_void
DECL|function|acpi_ns_dump_objects
id|acpi_ns_dump_objects
(paren
id|acpi_object_type
id|type
comma
id|u8
id|display_type
comma
id|u32
id|max_depth
comma
id|u32
id|owner_id
comma
id|acpi_handle
id|start_handle
)paren
(brace
id|acpi_walk_info
id|info
suffix:semicolon
id|ACPI_FUNCTION_ENTRY
(paren
)paren
suffix:semicolon
id|info.debug_level
op_assign
id|ACPI_LV_TABLES
suffix:semicolon
id|info.owner_id
op_assign
id|owner_id
suffix:semicolon
id|info.display_type
op_assign
id|display_type
suffix:semicolon
(paren
r_void
)paren
id|acpi_ns_walk_namespace
(paren
id|type
comma
id|start_handle
comma
id|max_depth
comma
id|ACPI_NS_WALK_NO_UNLOCK
comma
id|acpi_ns_dump_one_object
comma
(paren
r_void
op_star
)paren
op_amp
id|info
comma
l_int|NULL
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ns_dump_tables&n; *&n; * PARAMETERS:  Search_base         - Root of subtree to be dumped, or&n; *                                    NS_ALL to dump the entire namespace&n; *              Max_depth           - Maximum depth of dump.  Use INT_MAX&n; *                                    for an effectively unlimited depth.&n; *&n; * DESCRIPTION: Dump the name space, or a portion of it.&n; *&n; ******************************************************************************/
r_void
DECL|function|acpi_ns_dump_tables
id|acpi_ns_dump_tables
(paren
id|acpi_handle
id|search_base
comma
id|u32
id|max_depth
)paren
(brace
id|acpi_handle
id|search_handle
op_assign
id|search_base
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;Ns_dump_tables&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|acpi_gbl_root_node
)paren
(brace
multiline_comment|/*&n;&t;&t; * If the name space has not been initialized,&n;&t;&t; * there is nothing to dump.&n;&t;&t; */
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_TABLES
comma
l_string|&quot;namespace not initialized!&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|return_VOID
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ACPI_NS_ALL
op_eq
id|search_base
)paren
(brace
multiline_comment|/*  entire namespace    */
id|search_handle
op_assign
id|acpi_gbl_root_node
suffix:semicolon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_TABLES
comma
l_string|&quot;&bslash;&bslash;&bslash;n&quot;
)paren
)paren
suffix:semicolon
)brace
id|acpi_ns_dump_objects
(paren
id|ACPI_TYPE_ANY
comma
id|ACPI_DISPLAY_OBJECTS
comma
id|max_depth
comma
id|ACPI_UINT32_MAX
comma
id|search_handle
)paren
suffix:semicolon
id|return_VOID
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ns_dump_entry&n; *&n; * PARAMETERS:  Handle              - Node to be dumped&n; *              Debug_level         - Output level&n; *&n; * DESCRIPTION: Dump a single Node&n; *&n; ******************************************************************************/
r_void
DECL|function|acpi_ns_dump_entry
id|acpi_ns_dump_entry
(paren
id|acpi_handle
id|handle
comma
id|u32
id|debug_level
)paren
(brace
id|acpi_walk_info
id|info
suffix:semicolon
id|ACPI_FUNCTION_ENTRY
(paren
)paren
suffix:semicolon
id|info.debug_level
op_assign
id|debug_level
suffix:semicolon
id|info.owner_id
op_assign
id|ACPI_UINT32_MAX
suffix:semicolon
id|info.display_type
op_assign
id|ACPI_DISPLAY_SUMMARY
suffix:semicolon
(paren
r_void
)paren
id|acpi_ns_dump_one_object
(paren
id|handle
comma
l_int|1
comma
op_amp
id|info
comma
l_int|NULL
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
