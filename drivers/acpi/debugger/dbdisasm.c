multiline_comment|/*******************************************************************************&n; *&n; * Module Name: dbdisasm - parser op tree display routines&n; *              $Revision: 67 $&n; *&n; ******************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000 - 2002, R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &quot;acpi.h&quot;
macro_line|#include &quot;acparser.h&quot;
macro_line|#include &quot;amlcode.h&quot;
macro_line|#include &quot;acnamesp.h&quot;
macro_line|#include &quot;acdebug.h&quot;
macro_line|#ifdef ENABLE_DEBUGGER
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_DEBUGGER
id|ACPI_MODULE_NAME
(paren
l_string|&quot;dbdisasm&quot;
)paren
DECL|macro|BLOCK_PAREN
mdefine_line|#define BLOCK_PAREN         1
DECL|macro|BLOCK_BRACE
mdefine_line|#define BLOCK_BRACE         2
DECL|macro|DB_NO_OP_INFO
mdefine_line|#define DB_NO_OP_INFO       &quot;            [%2.2d]  &quot;
DECL|macro|DB_FULL_OP_INFO
mdefine_line|#define DB_FULL_OP_INFO     &quot;%5.5X #%4.4hX [%2.2d]  &quot;
DECL|variable|acpi_gbl_db_disasm_indent
id|NATIVE_CHAR
op_star
id|acpi_gbl_db_disasm_indent
op_assign
l_string|&quot;....&quot;
suffix:semicolon
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_db_block_type&n; *&n; * PARAMETERS:  Op              - Object to be examined&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Type of block for this op (parens or braces)&n; *&n; ******************************************************************************/
id|u32
DECL|function|acpi_db_block_type
id|acpi_db_block_type
(paren
id|acpi_parse_object
op_star
id|op
)paren
(brace
r_switch
c_cond
(paren
id|op-&gt;common.aml_opcode
)paren
(brace
r_case
id|AML_METHOD_OP
suffix:colon
r_return
(paren
id|BLOCK_BRACE
)paren
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
r_return
(paren
id|BLOCK_PAREN
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ps_display_object_pathname&n; *&n; * PARAMETERS:  Op              - Object whose pathname is to be obtained&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Diplay the pathname associated with a named object.  Two&n; *              versions. One searches the parse tree (for parser-only&n; *              applications suchas Acpi_dump), and the other searches the&n; *              ACPI namespace (the parse tree is probably deleted)&n; *&n; ******************************************************************************/
macro_line|#ifdef PARSER_ONLY
id|acpi_status
DECL|function|acpi_ps_display_object_pathname
id|acpi_ps_display_object_pathname
(paren
id|acpi_walk_state
op_star
id|walk_state
comma
id|acpi_parse_object
op_star
id|op
)paren
(brace
id|acpi_parse_object
op_star
id|target_op
suffix:semicolon
r_char
op_star
id|name
suffix:semicolon
r_if
c_cond
(paren
id|op-&gt;common.flags
op_amp
id|ACPI_PARSEOP_GENERIC
)paren
(brace
id|name
op_assign
id|op-&gt;common.value.name
suffix:semicolon
r_if
c_cond
(paren
id|name
(braket
l_int|0
)braket
op_eq
l_char|&squot;&bslash;&bslash;&squot;
)paren
(brace
id|acpi_os_printf
(paren
l_string|&quot; (Fully Qualified Pathname)&quot;
)paren
suffix:semicolon
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
id|name
op_assign
(paren
r_char
op_star
)paren
op_amp
id|op-&gt;named.name
suffix:semicolon
)brace
multiline_comment|/* Search parent tree up to the root if necessary */
id|target_op
op_assign
id|acpi_ps_find
(paren
id|op
comma
id|name
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|target_op
)paren
(brace
multiline_comment|/*&n;&t;&t; * Didn&squot;t find the name in the parse tree.  This may be&n;&t;&t; * a problem, or it may simply be one of the predefined names&n;&t;&t; * (such as _OS_).  Rather than worry about looking up all&n;&t;&t; * the predefined names, just display the name as given&n;&t;&t; */
id|acpi_os_printf
(paren
l_string|&quot; **** Path not found in parse tree&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* The target was found, print the name and complete path */
id|acpi_os_printf
(paren
l_string|&quot; (Path &quot;
)paren
suffix:semicolon
id|acpi_db_display_path
(paren
id|target_op
)paren
suffix:semicolon
id|acpi_os_printf
(paren
l_string|&quot;)&quot;
)paren
suffix:semicolon
)brace
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
macro_line|#else
id|acpi_status
DECL|function|acpi_ps_display_object_pathname
id|acpi_ps_display_object_pathname
(paren
id|acpi_walk_state
op_star
id|walk_state
comma
id|acpi_parse_object
op_star
id|op
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
id|acpi_namespace_node
op_star
id|node
suffix:semicolon
id|acpi_buffer
id|buffer
suffix:semicolon
id|u32
id|debug_level
suffix:semicolon
multiline_comment|/* Save current debug level so we don&squot;t get extraneous debug output */
id|debug_level
op_assign
id|acpi_dbg_level
suffix:semicolon
id|acpi_dbg_level
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Just get the Node out of the Op object */
id|node
op_assign
id|op-&gt;common.node
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|node
)paren
(brace
multiline_comment|/* Node not defined in this scope, look it up */
id|status
op_assign
id|acpi_ns_lookup
(paren
id|walk_state-&gt;scope_info
comma
id|op-&gt;common.value.string
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
multiline_comment|/*&n;&t;&t;&t; * We can&squot;t get the pathname since the object&n;&t;&t;&t; * is not in the namespace.  This can happen during single&n;&t;&t;&t; * stepping where a dynamic named object is *about* to be created.&n;&t;&t;&t; */
id|acpi_os_printf
(paren
l_string|&quot; [Path not found]&quot;
)paren
suffix:semicolon
r_goto
m_exit
suffix:semicolon
)brace
multiline_comment|/* Save it for next time. */
id|op-&gt;common.node
op_assign
id|node
suffix:semicolon
)brace
multiline_comment|/* Convert Named_desc/handle to a full pathname */
id|buffer.length
op_assign
id|ACPI_ALLOCATE_LOCAL_BUFFER
suffix:semicolon
id|status
op_assign
id|acpi_ns_handle_to_pathname
(paren
id|node
comma
op_amp
id|buffer
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
id|acpi_os_printf
(paren
l_string|&quot;****Could not get pathname****)&quot;
)paren
suffix:semicolon
r_goto
m_exit
suffix:semicolon
)brace
id|acpi_os_printf
(paren
l_string|&quot; (Path %s)&quot;
comma
id|buffer.pointer
)paren
suffix:semicolon
id|ACPI_MEM_FREE
(paren
id|buffer.pointer
)paren
suffix:semicolon
m_exit
suffix:colon
multiline_comment|/* Restore the debug level */
id|acpi_dbg_level
op_assign
id|debug_level
suffix:semicolon
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_db_display_op&n; *&n; * PARAMETERS:  Origin          - Starting object&n; *              Num_opcodes     - Max number of opcodes to be displayed&n; *&n; * RETURN:      None&n; *&n; * DESCRIPTION: Display parser object and its children&n; *&n; ******************************************************************************/
r_void
DECL|function|acpi_db_display_op
id|acpi_db_display_op
(paren
id|acpi_walk_state
op_star
id|walk_state
comma
id|acpi_parse_object
op_star
id|origin
comma
id|u32
id|num_opcodes
)paren
(brace
id|acpi_parse_object
op_star
id|op
op_assign
id|origin
suffix:semicolon
id|acpi_parse_object
op_star
id|arg
suffix:semicolon
id|acpi_parse_object
op_star
id|depth
suffix:semicolon
id|u32
id|depth_count
op_assign
l_int|0
suffix:semicolon
id|u32
id|last_depth
op_assign
l_int|0
suffix:semicolon
id|u32
id|i
suffix:semicolon
id|u32
id|j
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|op
)paren
(brace
id|acpi_db_display_opcode
(paren
id|walk_state
comma
id|op
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_while
c_loop
(paren
id|op
)paren
(brace
multiline_comment|/* Indentation */
id|depth_count
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|acpi_gbl_db_opt_verbose
)paren
(brace
id|depth_count
op_increment
suffix:semicolon
)brace
multiline_comment|/* Determine the nesting depth of this argument */
r_for
c_loop
(paren
id|depth
op_assign
id|op-&gt;common.parent
suffix:semicolon
id|depth
suffix:semicolon
id|depth
op_assign
id|depth-&gt;common.parent
)paren
(brace
id|arg
op_assign
id|acpi_ps_get_arg
(paren
id|depth
comma
l_int|0
)paren
suffix:semicolon
r_while
c_loop
(paren
id|arg
op_logical_and
id|arg
op_ne
id|origin
)paren
(brace
id|arg
op_assign
id|arg-&gt;common.next
suffix:semicolon
)brace
r_if
c_cond
(paren
id|arg
)paren
(brace
r_break
suffix:semicolon
)brace
id|depth_count
op_increment
suffix:semicolon
)brace
multiline_comment|/* Open a new block if we are nested further than last time */
r_if
c_cond
(paren
id|depth_count
OG
id|last_depth
)paren
(brace
id|VERBOSE_PRINT
(paren
(paren
id|DB_NO_OP_INFO
comma
id|last_depth
)paren
)paren
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
id|last_depth
suffix:semicolon
id|i
op_increment
)paren
(brace
id|acpi_os_printf
(paren
l_string|&quot;%s&quot;
comma
id|acpi_gbl_db_disasm_indent
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|acpi_db_block_type
(paren
id|op
)paren
op_eq
id|BLOCK_PAREN
)paren
(brace
id|acpi_os_printf
(paren
l_string|&quot;(&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|acpi_os_printf
(paren
l_string|&quot;{&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Close a block if we are nested less than last time */
r_else
r_if
c_cond
(paren
id|depth_count
OL
id|last_depth
)paren
(brace
r_for
c_loop
(paren
id|j
op_assign
id|last_depth
suffix:semicolon
id|j
op_ge
(paren
id|depth_count
op_plus
l_int|1
)paren
suffix:semicolon
id|j
op_decrement
)paren
(brace
id|VERBOSE_PRINT
(paren
(paren
id|DB_NO_OP_INFO
comma
(paren
id|j
op_minus
l_int|1
)paren
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|j
suffix:semicolon
id|i
op_increment
)paren
(brace
id|acpi_os_printf
(paren
l_string|&quot;%s&quot;
comma
id|acpi_gbl_db_disasm_indent
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|acpi_db_block_type
(paren
id|op
)paren
op_eq
id|BLOCK_PAREN
)paren
(brace
id|acpi_os_printf
(paren
l_string|&quot;)&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|acpi_os_printf
(paren
l_string|&quot;}&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/* In verbose mode, print the AML offset, opcode and depth count */
id|VERBOSE_PRINT
(paren
(paren
id|DB_FULL_OP_INFO
comma
(paren
id|u32
)paren
id|op-&gt;common.aml_offset
comma
id|op-&gt;common.aml_opcode
comma
id|depth_count
)paren
)paren
suffix:semicolon
multiline_comment|/* Indent the output according to the depth count */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|depth_count
suffix:semicolon
id|i
op_increment
)paren
(brace
id|acpi_os_printf
(paren
l_string|&quot;%s&quot;
comma
id|acpi_gbl_db_disasm_indent
)paren
suffix:semicolon
)brace
multiline_comment|/* Now print the opcode */
id|acpi_db_display_opcode
(paren
id|walk_state
comma
id|op
)paren
suffix:semicolon
multiline_comment|/* Resolve a name reference */
r_if
c_cond
(paren
(paren
id|op-&gt;common.aml_opcode
op_eq
id|AML_INT_NAMEPATH_OP
op_logical_and
id|op-&gt;common.value.name
)paren
op_logical_and
(paren
id|op-&gt;common.parent
)paren
op_logical_and
(paren
id|acpi_gbl_db_opt_verbose
)paren
)paren
(brace
(paren
r_void
)paren
id|acpi_ps_display_object_pathname
(paren
id|walk_state
comma
id|op
)paren
suffix:semicolon
)brace
id|acpi_os_printf
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Get the next node in the tree */
id|op
op_assign
id|acpi_ps_get_depth_next
(paren
id|origin
comma
id|op
)paren
suffix:semicolon
id|last_depth
op_assign
id|depth_count
suffix:semicolon
id|num_opcodes
op_decrement
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|num_opcodes
)paren
(brace
id|op
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
multiline_comment|/* Close the last block(s) */
id|depth_count
op_assign
id|last_depth
op_minus
l_int|1
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
id|last_depth
suffix:semicolon
id|i
op_increment
)paren
(brace
id|VERBOSE_PRINT
(paren
(paren
id|DB_NO_OP_INFO
comma
id|last_depth
op_minus
id|i
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|depth_count
suffix:semicolon
id|j
op_increment
)paren
(brace
id|acpi_os_printf
(paren
l_string|&quot;%s&quot;
comma
id|acpi_gbl_db_disasm_indent
)paren
suffix:semicolon
)brace
id|acpi_os_printf
(paren
l_string|&quot;}&bslash;n&quot;
)paren
suffix:semicolon
id|depth_count
op_decrement
suffix:semicolon
)brace
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_db_display_namestring&n; *&n; * PARAMETERS:  Name                - ACPI Name string to store&n; *&n; * RETURN:      None&n; *&n; * DESCRIPTION: Display namestring. Handles prefix characters&n; *&n; ******************************************************************************/
r_void
DECL|function|acpi_db_display_namestring
id|acpi_db_display_namestring
(paren
id|NATIVE_CHAR
op_star
id|name
)paren
(brace
id|u32
id|seg_count
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|name
)paren
(brace
id|acpi_os_printf
(paren
l_string|&quot;&lt;NULL NAME PTR&gt;&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Handle all Scope Prefix operators */
r_while
c_loop
(paren
id|acpi_ps_is_prefix_char
(paren
id|ACPI_GET8
(paren
id|name
)paren
)paren
)paren
(brace
multiline_comment|/* Append prefix character */
id|acpi_os_printf
(paren
l_string|&quot;%1c&quot;
comma
id|ACPI_GET8
(paren
id|name
)paren
)paren
suffix:semicolon
id|name
op_increment
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|ACPI_GET8
(paren
id|name
)paren
)paren
(brace
r_case
l_int|0
suffix:colon
id|seg_count
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AML_DUAL_NAME_PREFIX
suffix:colon
id|seg_count
op_assign
l_int|2
suffix:semicolon
id|name
op_increment
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AML_MULTI_NAME_PREFIX_OP
suffix:colon
id|seg_count
op_assign
(paren
id|u32
)paren
id|ACPI_GET8
(paren
id|name
op_plus
l_int|1
)paren
suffix:semicolon
id|name
op_add_assign
l_int|2
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|seg_count
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
r_while
c_loop
(paren
id|seg_count
)paren
(brace
multiline_comment|/* Append Name segment */
id|acpi_os_printf
(paren
l_string|&quot;%4.4s&quot;
comma
id|name
)paren
suffix:semicolon
id|seg_count
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|seg_count
)paren
(brace
multiline_comment|/* Not last name, append dot separator */
id|acpi_os_printf
(paren
l_string|&quot;.&quot;
)paren
suffix:semicolon
)brace
id|name
op_add_assign
id|ACPI_NAME_SIZE
suffix:semicolon
)brace
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_db_display_path&n; *&n; * PARAMETERS:  Op                  - Named Op whose path is to be constructed&n; *&n; * RETURN:      None&n; *&n; * DESCRIPTION: Walk backwards from current scope and display the name&n; *              of each previous level of scope up to the root scope&n; *              (like &quot;pwd&quot; does with file systems)&n; *&n; ******************************************************************************/
r_void
DECL|function|acpi_db_display_path
id|acpi_db_display_path
(paren
id|acpi_parse_object
op_star
id|op
)paren
(brace
id|acpi_parse_object
op_star
id|prev
suffix:semicolon
id|acpi_parse_object
op_star
id|search
suffix:semicolon
id|u32
id|name
suffix:semicolon
id|u8
id|do_dot
op_assign
id|FALSE
suffix:semicolon
id|acpi_parse_object
op_star
id|name_path
suffix:semicolon
r_const
id|acpi_opcode_info
op_star
id|op_info
suffix:semicolon
multiline_comment|/* We are only interested in named objects */
id|op_info
op_assign
id|acpi_ps_get_opcode_info
(paren
id|op-&gt;common.aml_opcode
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|op_info-&gt;flags
op_amp
id|AML_NSNODE
)paren
)paren
(brace
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|op_info-&gt;flags
op_amp
id|AML_CREATE
)paren
(brace
multiline_comment|/* Field creation - check for a fully qualified namepath */
r_if
c_cond
(paren
id|op-&gt;common.aml_opcode
op_eq
id|AML_CREATE_FIELD_OP
)paren
(brace
id|name_path
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
id|name_path
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
(paren
id|name_path
)paren
op_logical_and
(paren
id|name_path-&gt;common.value.string
)paren
op_logical_and
(paren
id|name_path-&gt;common.value.string
(braket
l_int|0
)braket
op_eq
l_char|&squot;&bslash;&bslash;&squot;
)paren
)paren
(brace
id|acpi_db_display_namestring
(paren
id|name_path-&gt;common.value.string
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
id|prev
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Start with Root Node */
r_while
c_loop
(paren
id|prev
op_ne
id|op
)paren
(brace
multiline_comment|/* Search upwards in the tree to find scope with &quot;prev&quot; as its parent */
id|search
op_assign
id|op
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_if
c_cond
(paren
id|search-&gt;common.parent
op_eq
id|prev
)paren
(brace
r_break
suffix:semicolon
)brace
multiline_comment|/* Go up one level */
id|search
op_assign
id|search-&gt;common.parent
suffix:semicolon
)brace
r_if
c_cond
(paren
id|prev
)paren
(brace
id|op_info
op_assign
id|acpi_ps_get_opcode_info
(paren
id|search-&gt;common.aml_opcode
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|op_info-&gt;flags
op_amp
id|AML_FIELD
)paren
)paren
(brace
multiline_comment|/* below root scope, append scope name */
r_if
c_cond
(paren
id|do_dot
)paren
(brace
multiline_comment|/* append dot */
id|acpi_os_printf
(paren
l_string|&quot;.&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|op_info-&gt;flags
op_amp
id|AML_CREATE
)paren
(brace
r_if
c_cond
(paren
id|op-&gt;common.aml_opcode
op_eq
id|AML_CREATE_FIELD_OP
)paren
(brace
id|name_path
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
id|name_path
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
(paren
id|name_path
)paren
op_logical_and
(paren
id|name_path-&gt;common.value.string
)paren
)paren
(brace
id|acpi_os_printf
(paren
l_string|&quot;%4.4s&quot;
comma
id|name_path-&gt;common.value.string
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
id|name
op_assign
id|acpi_ps_get_name
(paren
id|search
)paren
suffix:semicolon
id|acpi_os_printf
(paren
l_string|&quot;%4.4s&quot;
comma
op_amp
id|name
)paren
suffix:semicolon
)brace
id|do_dot
op_assign
id|TRUE
suffix:semicolon
)brace
)brace
id|prev
op_assign
id|search
suffix:semicolon
)brace
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_db_display_opcode&n; *&n; * PARAMETERS:  Op                  - Op that is to be printed&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Store printed op in a Buffer and return its length&n; *              (or -1 if out of space)&n; *&n; * NOTE: Terse mode prints out ASL-like code.  Verbose mode adds more info.&n; *&n; ******************************************************************************/
r_void
DECL|function|acpi_db_display_opcode
id|acpi_db_display_opcode
(paren
id|acpi_walk_state
op_star
id|walk_state
comma
id|acpi_parse_object
op_star
id|op
)paren
(brace
id|u8
op_star
id|byte_data
suffix:semicolon
id|u32
id|byte_count
suffix:semicolon
id|u32
id|i
suffix:semicolon
r_const
id|acpi_opcode_info
op_star
id|op_info
op_assign
l_int|NULL
suffix:semicolon
id|u32
id|name
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|op
)paren
(brace
id|acpi_os_printf
(paren
l_string|&quot;&lt;NULL OP PTR&gt;&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* op and arguments */
r_switch
c_cond
(paren
id|op-&gt;common.aml_opcode
)paren
(brace
r_case
id|AML_BYTE_OP
suffix:colon
r_if
c_cond
(paren
id|acpi_gbl_db_opt_verbose
)paren
(brace
id|acpi_os_printf
(paren
l_string|&quot;(u8) 0x%2.2hX&quot;
comma
id|op-&gt;common.value.integer8
)paren
suffix:semicolon
)brace
r_else
(brace
id|acpi_os_printf
(paren
l_string|&quot;0x%2.2hX&quot;
comma
id|op-&gt;common.value.integer8
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|AML_WORD_OP
suffix:colon
r_if
c_cond
(paren
id|acpi_gbl_db_opt_verbose
)paren
(brace
id|acpi_os_printf
(paren
l_string|&quot;(u16) 0x%4.4hX&quot;
comma
id|op-&gt;common.value.integer16
)paren
suffix:semicolon
)brace
r_else
(brace
id|acpi_os_printf
(paren
l_string|&quot;0x%4.4hX&quot;
comma
id|op-&gt;common.value.integer16
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|AML_DWORD_OP
suffix:colon
r_if
c_cond
(paren
id|acpi_gbl_db_opt_verbose
)paren
(brace
id|acpi_os_printf
(paren
l_string|&quot;(u32) 0x%8.8X&quot;
comma
id|op-&gt;common.value.integer32
)paren
suffix:semicolon
)brace
r_else
(brace
id|acpi_os_printf
(paren
l_string|&quot;0x%8.8X&quot;
comma
id|op-&gt;common.value.integer32
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|AML_QWORD_OP
suffix:colon
r_if
c_cond
(paren
id|acpi_gbl_db_opt_verbose
)paren
(brace
id|acpi_os_printf
(paren
l_string|&quot;(u64) 0x%8.8X%8.8X&quot;
comma
id|op-&gt;common.value.integer64.hi
comma
id|op-&gt;common.value.integer64.lo
)paren
suffix:semicolon
)brace
r_else
(brace
id|acpi_os_printf
(paren
l_string|&quot;0x%8.8X%8.8X&quot;
comma
id|op-&gt;common.value.integer64.hi
comma
id|op-&gt;common.value.integer64.lo
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|AML_STRING_OP
suffix:colon
r_if
c_cond
(paren
id|op-&gt;common.value.string
)paren
(brace
id|acpi_os_printf
(paren
l_string|&quot;&bslash;&quot;%s&bslash;&quot;&quot;
comma
id|op-&gt;common.value.string
)paren
suffix:semicolon
)brace
r_else
(brace
id|acpi_os_printf
(paren
l_string|&quot;&lt;&bslash;&quot;NULL STRING PTR&bslash;&quot;&gt;&quot;
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|AML_INT_STATICSTRING_OP
suffix:colon
r_if
c_cond
(paren
id|op-&gt;common.value.string
)paren
(brace
id|acpi_os_printf
(paren
l_string|&quot;&bslash;&quot;%s&bslash;&quot;&quot;
comma
id|op-&gt;common.value.string
)paren
suffix:semicolon
)brace
r_else
(brace
id|acpi_os_printf
(paren
l_string|&quot;&bslash;&quot;&lt;NULL STATIC STRING PTR&gt;&bslash;&quot;&quot;
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|AML_INT_NAMEPATH_OP
suffix:colon
id|acpi_db_display_namestring
(paren
id|op-&gt;common.value.name
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AML_INT_NAMEDFIELD_OP
suffix:colon
id|acpi_os_printf
(paren
l_string|&quot;Named_field (Length 0x%8.8X)  &quot;
comma
id|op-&gt;common.value.integer32
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AML_INT_RESERVEDFIELD_OP
suffix:colon
id|acpi_os_printf
(paren
l_string|&quot;Reserved_field (Length 0x%8.8X) &quot;
comma
id|op-&gt;common.value.integer32
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AML_INT_ACCESSFIELD_OP
suffix:colon
id|acpi_os_printf
(paren
l_string|&quot;Access_field (Length 0x%8.8X) &quot;
comma
id|op-&gt;common.value.integer32
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AML_INT_BYTELIST_OP
suffix:colon
r_if
c_cond
(paren
id|acpi_gbl_db_opt_verbose
)paren
(brace
id|acpi_os_printf
(paren
l_string|&quot;Byte_list   (Length 0x%8.8X)  &quot;
comma
id|op-&gt;common.value.integer32
)paren
suffix:semicolon
)brace
r_else
(brace
id|acpi_os_printf
(paren
l_string|&quot;0x%2.2X&quot;
comma
id|op-&gt;common.value.integer32
)paren
suffix:semicolon
id|byte_count
op_assign
id|op-&gt;common.value.integer32
suffix:semicolon
id|byte_data
op_assign
id|op-&gt;named.data
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
id|byte_count
suffix:semicolon
id|i
op_increment
)paren
(brace
id|acpi_os_printf
(paren
l_string|&quot;, 0x%2.2X&quot;
comma
id|byte_data
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
)brace
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* Just get the opcode name and print it */
id|op_info
op_assign
id|acpi_ps_get_opcode_info
(paren
id|op-&gt;common.aml_opcode
)paren
suffix:semicolon
id|acpi_os_printf
(paren
l_string|&quot;%s&quot;
comma
id|op_info-&gt;name
)paren
suffix:semicolon
macro_line|#ifndef PARSER_ONLY
r_if
c_cond
(paren
(paren
id|op-&gt;common.aml_opcode
op_eq
id|AML_INT_RETURN_VALUE_OP
)paren
op_logical_and
(paren
id|walk_state
)paren
op_logical_and
(paren
id|walk_state-&gt;results
)paren
op_logical_and
(paren
id|walk_state-&gt;results-&gt;results.num_results
)paren
)paren
(brace
id|acpi_db_decode_internal_object
(paren
id|walk_state-&gt;results-&gt;results.obj_desc
(braket
id|walk_state-&gt;results-&gt;results.num_results
op_minus
l_int|1
)braket
)paren
suffix:semicolon
)brace
macro_line|#endif
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|op_info
)paren
(brace
multiline_comment|/* If there is another element in the list, add a comma */
r_if
c_cond
(paren
id|op-&gt;common.next
)paren
(brace
id|acpi_os_printf
(paren
l_string|&quot;,&quot;
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; * If this is a named opcode, print the associated name value&n;&t; */
id|op_info
op_assign
id|acpi_ps_get_opcode_info
(paren
id|op-&gt;common.aml_opcode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|op
op_logical_and
(paren
id|op_info-&gt;flags
op_amp
id|AML_NAMED
)paren
)paren
(brace
id|name
op_assign
id|acpi_ps_get_name
(paren
id|op
)paren
suffix:semicolon
id|acpi_os_printf
(paren
l_string|&quot; %4.4s&quot;
comma
op_amp
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|acpi_gbl_db_opt_verbose
)paren
op_logical_and
(paren
id|op-&gt;common.aml_opcode
op_ne
id|AML_INT_NAMEDFIELD_OP
)paren
)paren
(brace
(paren
r_void
)paren
id|acpi_ps_display_object_pathname
(paren
id|walk_state
comma
id|op
)paren
suffix:semicolon
)brace
)brace
)brace
macro_line|#endif  /* ENABLE_DEBUGGER */
eof
