multiline_comment|/******************************************************************************&n; *&n; * Module Name: exdump - Interpreter debug output routines&n; *&n; *****************************************************************************/
multiline_comment|/*&n; * Copyright (C) 2000 - 2003, R. Byron Moore&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. Redistributions in binary form must reproduce at minimum a disclaimer&n; *    substantially similar to the &quot;NO WARRANTY&quot; disclaimer below&n; *    (&quot;Disclaimer&quot;) and any redistribution must be conditioned upon&n; *    including a substantially similar Disclaimer requirement for further&n; *    binary redistribution.&n; * 3. Neither the names of the above-listed copyright holders nor the names&n; *    of any contributors may be used to endorse or promote products derived&n; *    from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;) version 2 as published by the Free&n; * Software Foundation.&n; *&n; * NO WARRANTY&n; * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS&n; * &quot;AS IS&quot; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT&n; * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR&n; * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT&n; * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,&n; * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING&n; * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE&n; * POSSIBILITY OF SUCH DAMAGES.&n; */
macro_line|#include &lt;acpi/acpi.h&gt;
macro_line|#include &lt;acpi/acinterp.h&gt;
macro_line|#include &lt;acpi/amlcode.h&gt;
macro_line|#include &lt;acpi/acnamesp.h&gt;
macro_line|#include &lt;acpi/acparser.h&gt;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_EXECUTER
id|ACPI_MODULE_NAME
(paren
l_string|&quot;exdump&quot;
)paren
multiline_comment|/*&n; * The following routines are used for debug output only&n; */
macro_line|#if defined(ACPI_DEBUG_OUTPUT) || defined(ACPI_DEBUGGER)
multiline_comment|/*****************************************************************************&n; *&n; * FUNCTION:    acpi_ex_dump_operand&n; *&n; * PARAMETERS:  *obj_desc         - Pointer to entry to be dumped&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Dump an operand object&n; *&n; ****************************************************************************/
r_void
DECL|function|acpi_ex_dump_operand
id|acpi_ex_dump_operand
(paren
r_union
id|acpi_operand_object
op_star
id|obj_desc
)paren
(brace
id|u8
op_star
id|buf
op_assign
l_int|NULL
suffix:semicolon
id|u32
id|length
suffix:semicolon
r_union
id|acpi_operand_object
op_star
op_star
id|element
suffix:semicolon
id|u16
id|element_index
suffix:semicolon
id|ACPI_FUNCTION_NAME
(paren
l_string|&quot;ex_dump_operand&quot;
)paren
r_if
c_cond
(paren
op_logical_neg
(paren
(paren
id|ACPI_LV_EXEC
op_amp
id|acpi_dbg_level
)paren
op_logical_and
(paren
id|_COMPONENT
op_amp
id|acpi_dbg_layer
)paren
)paren
)paren
(brace
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|obj_desc
)paren
(brace
multiline_comment|/*&n;&t;&t; * This usually indicates that something serious is wrong&n;&t;&t; */
id|acpi_os_printf
(paren
l_string|&quot;Null Object Descriptor&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ACPI_GET_DESCRIPTOR_TYPE
(paren
id|obj_desc
)paren
op_eq
id|ACPI_DESC_TYPE_NAMED
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_EXEC
comma
l_string|&quot;%p is a NS Node: &quot;
comma
id|obj_desc
)paren
)paren
suffix:semicolon
id|ACPI_DUMP_ENTRY
(paren
id|obj_desc
comma
id|ACPI_LV_EXEC
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
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
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_EXEC
comma
l_string|&quot;%p is not a node or operand object: [%s]&bslash;n&quot;
comma
id|obj_desc
comma
id|acpi_ut_get_descriptor_name
(paren
id|obj_desc
)paren
)paren
)paren
suffix:semicolon
id|ACPI_DUMP_BUFFER
(paren
id|obj_desc
comma
r_sizeof
(paren
r_union
id|acpi_operand_object
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* obj_desc is a valid object */
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_EXEC
comma
l_string|&quot;%p &quot;
comma
id|obj_desc
)paren
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|ACPI_GET_OBJECT_TYPE
(paren
id|obj_desc
)paren
)paren
(brace
r_case
id|ACPI_TYPE_LOCAL_REFERENCE
suffix:colon
r_switch
c_cond
(paren
id|obj_desc-&gt;reference.opcode
)paren
(brace
r_case
id|AML_DEBUG_OP
suffix:colon
id|acpi_os_printf
(paren
l_string|&quot;Reference: Debug&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AML_NAME_OP
suffix:colon
id|ACPI_DUMP_PATHNAME
(paren
id|obj_desc-&gt;reference.object
comma
l_string|&quot;Reference: Name: &quot;
comma
id|ACPI_LV_INFO
comma
id|_COMPONENT
)paren
suffix:semicolon
id|ACPI_DUMP_ENTRY
(paren
id|obj_desc-&gt;reference.object
comma
id|ACPI_LV_INFO
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AML_INDEX_OP
suffix:colon
id|acpi_os_printf
(paren
l_string|&quot;Reference: Index %p&bslash;n&quot;
comma
id|obj_desc-&gt;reference.object
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AML_REF_OF_OP
suffix:colon
id|acpi_os_printf
(paren
l_string|&quot;Reference: (ref_of) %p&bslash;n&quot;
comma
id|obj_desc-&gt;reference.object
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AML_ARG_OP
suffix:colon
id|acpi_os_printf
(paren
l_string|&quot;Reference: Arg%d&quot;
comma
id|obj_desc-&gt;reference.offset
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_GET_OBJECT_TYPE
(paren
id|obj_desc
)paren
op_eq
id|ACPI_TYPE_INTEGER
)paren
(brace
multiline_comment|/* Value is an Integer */
id|acpi_os_printf
(paren
l_string|&quot; value is [%8.8X%8.8x]&quot;
comma
id|ACPI_FORMAT_UINT64
(paren
id|obj_desc-&gt;integer.value
)paren
)paren
suffix:semicolon
)brace
id|acpi_os_printf
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AML_LOCAL_OP
suffix:colon
id|acpi_os_printf
(paren
l_string|&quot;Reference: Local%d&quot;
comma
id|obj_desc-&gt;reference.offset
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_GET_OBJECT_TYPE
(paren
id|obj_desc
)paren
op_eq
id|ACPI_TYPE_INTEGER
)paren
(brace
multiline_comment|/* Value is an Integer */
id|acpi_os_printf
(paren
l_string|&quot; value is [%8.8X%8.8x]&quot;
comma
id|ACPI_FORMAT_UINT64
(paren
id|obj_desc-&gt;integer.value
)paren
)paren
suffix:semicolon
)brace
id|acpi_os_printf
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AML_INT_NAMEPATH_OP
suffix:colon
id|acpi_os_printf
(paren
l_string|&quot;Reference.Node-&gt;Name %X&bslash;n&quot;
comma
id|obj_desc-&gt;reference.node-&gt;name.integer
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* Unknown opcode */
id|acpi_os_printf
(paren
l_string|&quot;Unknown Reference opcode=%X&bslash;n&quot;
comma
id|obj_desc-&gt;reference.opcode
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_BUFFER
suffix:colon
id|acpi_os_printf
(paren
l_string|&quot;Buffer len %X @ %p &bslash;n&quot;
comma
id|obj_desc-&gt;buffer.length
comma
id|obj_desc-&gt;buffer.pointer
)paren
suffix:semicolon
id|length
op_assign
id|obj_desc-&gt;buffer.length
suffix:semicolon
r_if
c_cond
(paren
id|length
OG
l_int|64
)paren
(brace
id|length
op_assign
l_int|64
suffix:semicolon
)brace
multiline_comment|/* Debug only -- dump the buffer contents */
r_if
c_cond
(paren
id|obj_desc-&gt;buffer.pointer
)paren
(brace
id|acpi_os_printf
(paren
l_string|&quot;Buffer Contents: &quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|buf
op_assign
id|obj_desc-&gt;buffer.pointer
suffix:semicolon
id|length
op_decrement
suffix:semicolon
op_increment
id|buf
)paren
(brace
id|acpi_os_printf
(paren
l_string|&quot; %02x&quot;
comma
op_star
id|buf
)paren
suffix:semicolon
)brace
id|acpi_os_printf
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_INTEGER
suffix:colon
id|acpi_os_printf
(paren
l_string|&quot;Integer %8.8X%8.8X&bslash;n&quot;
comma
id|ACPI_FORMAT_UINT64
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
id|acpi_os_printf
(paren
l_string|&quot;Package count %X @ %p&bslash;n&quot;
comma
id|obj_desc-&gt;package.count
comma
id|obj_desc-&gt;package.elements
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * If elements exist, package vector pointer is valid,&n;&t;&t; * and debug_level exceeds 1, dump package&squot;s elements.&n;&t;&t; */
r_if
c_cond
(paren
id|obj_desc-&gt;package.count
op_logical_and
id|obj_desc-&gt;package.elements
op_logical_and
id|acpi_dbg_level
OG
l_int|1
)paren
(brace
r_for
c_loop
(paren
id|element_index
op_assign
l_int|0
comma
id|element
op_assign
id|obj_desc-&gt;package.elements
suffix:semicolon
id|element_index
OL
id|obj_desc-&gt;package.count
suffix:semicolon
op_increment
id|element_index
comma
op_increment
id|element
)paren
(brace
id|acpi_ex_dump_operand
(paren
op_star
id|element
)paren
suffix:semicolon
)brace
)brace
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
l_string|&quot;Region %s (%X)&quot;
comma
id|acpi_ut_get_region_name
(paren
id|obj_desc-&gt;region.space_id
)paren
comma
id|obj_desc-&gt;region.space_id
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * If the address and length have not been evaluated,&n;&t;&t; * don&squot;t print them.&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
(paren
id|obj_desc-&gt;region.flags
op_amp
id|AOPOBJ_DATA_VALID
)paren
)paren
(brace
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
l_string|&quot; base %8.8X%8.8X Length %X&bslash;n&quot;
comma
id|ACPI_FORMAT_UINT64
(paren
id|obj_desc-&gt;region.address
)paren
comma
id|obj_desc-&gt;region.length
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
l_string|&quot;String length %X @ %p &quot;
comma
id|obj_desc-&gt;string.length
comma
id|obj_desc-&gt;string.pointer
)paren
suffix:semicolon
id|acpi_ut_print_string
(paren
id|obj_desc-&gt;string.pointer
comma
id|ACPI_UINT8_MAX
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
id|ACPI_TYPE_LOCAL_BANK_FIELD
suffix:colon
id|acpi_os_printf
(paren
l_string|&quot;bank_field&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_LOCAL_REGION_FIELD
suffix:colon
id|acpi_os_printf
(paren
l_string|&quot;region_field: Bits=%X acc_width=%X Lock=%X Update=%X at byte=%X bit=%X of below:&bslash;n&quot;
comma
id|obj_desc-&gt;field.bit_length
comma
id|obj_desc-&gt;field.access_byte_width
comma
id|obj_desc-&gt;field.field_flags
op_amp
id|AML_FIELD_LOCK_RULE_MASK
comma
id|obj_desc-&gt;field.field_flags
op_amp
id|AML_FIELD_UPDATE_RULE_MASK
comma
id|obj_desc-&gt;field.base_byte_offset
comma
id|obj_desc-&gt;field.start_field_bit_offset
)paren
suffix:semicolon
id|ACPI_DUMP_STACK_ENTRY
(paren
id|obj_desc-&gt;field.region_obj
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_LOCAL_INDEX_FIELD
suffix:colon
id|acpi_os_printf
(paren
l_string|&quot;index_field&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_BUFFER_FIELD
suffix:colon
id|acpi_os_printf
(paren
l_string|&quot;buffer_field: %X bits at byte %X bit %X of &bslash;n&quot;
comma
id|obj_desc-&gt;buffer_field.bit_length
comma
id|obj_desc-&gt;buffer_field.base_byte_offset
comma
id|obj_desc-&gt;buffer_field.start_field_bit_offset
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|obj_desc-&gt;buffer_field.buffer_obj
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_EXEC
comma
l_string|&quot;*NULL* &bslash;n&quot;
)paren
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|ACPI_GET_OBJECT_TYPE
(paren
id|obj_desc-&gt;buffer_field.buffer_obj
)paren
op_ne
id|ACPI_TYPE_BUFFER
)paren
(brace
id|acpi_os_printf
(paren
l_string|&quot;*not a Buffer* &bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|ACPI_DUMP_STACK_ENTRY
(paren
id|obj_desc-&gt;buffer_field.buffer_obj
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_EVENT
suffix:colon
id|acpi_os_printf
(paren
l_string|&quot;Event&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_METHOD
suffix:colon
id|acpi_os_printf
(paren
l_string|&quot;Method(%X) @ %p:%X&bslash;n&quot;
comma
id|obj_desc-&gt;method.param_count
comma
id|obj_desc-&gt;method.aml_start
comma
id|obj_desc-&gt;method.aml_length
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_MUTEX
suffix:colon
id|acpi_os_printf
(paren
l_string|&quot;Mutex&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_DEVICE
suffix:colon
id|acpi_os_printf
(paren
l_string|&quot;Device&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_POWER
suffix:colon
id|acpi_os_printf
(paren
l_string|&quot;Power&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_PROCESSOR
suffix:colon
id|acpi_os_printf
(paren
l_string|&quot;Processor&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_THERMAL
suffix:colon
id|acpi_os_printf
(paren
l_string|&quot;Thermal&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* Unknown Type */
id|acpi_os_printf
(paren
l_string|&quot;Unknown Type %X&bslash;n&quot;
comma
id|ACPI_GET_OBJECT_TYPE
(paren
id|obj_desc
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
multiline_comment|/*****************************************************************************&n; *&n; * FUNCTION:    acpi_ex_dump_operands&n; *&n; * PARAMETERS:  interpreter_mode     - Load or Exec&n; *              *Ident              - Identification&n; *              num_levels          - # of stack entries to dump above line&n; *              *Note               - Output notation&n; *&n; * DESCRIPTION: Dump the object stack&n; *&n; ****************************************************************************/
r_void
DECL|function|acpi_ex_dump_operands
id|acpi_ex_dump_operands
(paren
r_union
id|acpi_operand_object
op_star
op_star
id|operands
comma
id|acpi_interpreter_mode
id|interpreter_mode
comma
r_char
op_star
id|ident
comma
id|u32
id|num_levels
comma
r_char
op_star
id|note
comma
r_char
op_star
id|module_name
comma
id|u32
id|line_number
)paren
(brace
id|acpi_native_uint
id|i
suffix:semicolon
r_union
id|acpi_operand_object
op_star
op_star
id|obj_desc
suffix:semicolon
id|ACPI_FUNCTION_NAME
(paren
l_string|&quot;ex_dump_operands&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ident
)paren
(brace
id|ident
op_assign
l_string|&quot;?&quot;
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|note
)paren
(brace
id|note
op_assign
l_string|&quot;?&quot;
suffix:semicolon
)brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_EXEC
comma
l_string|&quot;************* Operand Stack Contents (Opcode [%s], %d Operands)&bslash;n&quot;
comma
id|ident
comma
id|num_levels
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|num_levels
op_eq
l_int|0
)paren
(brace
id|num_levels
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Dump the operand stack starting at the top */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|num_levels
OG
l_int|0
suffix:semicolon
id|i
op_decrement
comma
id|num_levels
op_decrement
)paren
(brace
id|obj_desc
op_assign
op_amp
id|operands
(braket
id|i
)braket
suffix:semicolon
id|acpi_ex_dump_operand
(paren
op_star
id|obj_desc
)paren
suffix:semicolon
)brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_EXEC
comma
l_string|&quot;************* Stack dump from %s(%d), %s&bslash;n&quot;
comma
id|module_name
comma
id|line_number
comma
id|note
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*****************************************************************************&n; *&n; * FUNCTION:    acpi_ex_out*&n; *&n; * PARAMETERS:  Title               - Descriptive text&n; *              Value               - Value to be displayed&n; *&n; * DESCRIPTION: Object dump output formatting functions.  These functions&n; *              reduce the number of format strings required and keeps them&n; *              all in one place for easy modification.&n; *&n; ****************************************************************************/
r_void
DECL|function|acpi_ex_out_string
id|acpi_ex_out_string
(paren
r_char
op_star
id|title
comma
r_char
op_star
id|value
)paren
(brace
id|acpi_os_printf
(paren
l_string|&quot;%20s : %s&bslash;n&quot;
comma
id|title
comma
id|value
)paren
suffix:semicolon
)brace
r_void
DECL|function|acpi_ex_out_pointer
id|acpi_ex_out_pointer
(paren
r_char
op_star
id|title
comma
r_void
op_star
id|value
)paren
(brace
id|acpi_os_printf
(paren
l_string|&quot;%20s : %p&bslash;n&quot;
comma
id|title
comma
id|value
)paren
suffix:semicolon
)brace
r_void
DECL|function|acpi_ex_out_integer
id|acpi_ex_out_integer
(paren
r_char
op_star
id|title
comma
id|u32
id|value
)paren
(brace
id|acpi_os_printf
(paren
l_string|&quot;%20s : %X&bslash;n&quot;
comma
id|title
comma
id|value
)paren
suffix:semicolon
)brace
r_void
DECL|function|acpi_ex_out_address
id|acpi_ex_out_address
(paren
r_char
op_star
id|title
comma
id|acpi_physical_address
id|value
)paren
(brace
macro_line|#if ACPI_MACHINE_WIDTH == 16
id|acpi_os_printf
(paren
l_string|&quot;%20s : %p&bslash;n&quot;
comma
id|title
comma
id|value
)paren
suffix:semicolon
macro_line|#else
id|acpi_os_printf
(paren
l_string|&quot;%20s : %8.8X%8.8X&bslash;n&quot;
comma
id|title
comma
id|ACPI_FORMAT_UINT64
(paren
id|value
)paren
)paren
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/*****************************************************************************&n; *&n; * FUNCTION:    acpi_ex_dump_node&n; *&n; * PARAMETERS:  *Node           - Descriptor to dump&n; *              Flags               - Force display&n; *&n; * DESCRIPTION: Dumps the members of the given.Node&n; *&n; ****************************************************************************/
r_void
DECL|function|acpi_ex_dump_node
id|acpi_ex_dump_node
(paren
r_struct
id|acpi_namespace_node
op_star
id|node
comma
id|u32
id|flags
)paren
(brace
id|ACPI_FUNCTION_ENTRY
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|flags
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
(paren
id|ACPI_LV_OBJECTS
op_amp
id|acpi_dbg_level
)paren
op_logical_and
(paren
id|_COMPONENT
op_amp
id|acpi_dbg_layer
)paren
)paren
)paren
(brace
r_return
suffix:semicolon
)brace
)brace
id|acpi_os_printf
(paren
l_string|&quot;%20s : %4.4s&bslash;n&quot;
comma
l_string|&quot;Name&quot;
comma
id|acpi_ut_get_node_name
(paren
id|node
)paren
)paren
suffix:semicolon
id|acpi_ex_out_string
(paren
l_string|&quot;Type&quot;
comma
id|acpi_ut_get_type_name
(paren
id|node-&gt;type
)paren
)paren
suffix:semicolon
id|acpi_ex_out_integer
(paren
l_string|&quot;Flags&quot;
comma
id|node-&gt;flags
)paren
suffix:semicolon
id|acpi_ex_out_integer
(paren
l_string|&quot;Owner Id&quot;
comma
id|node-&gt;owner_id
)paren
suffix:semicolon
id|acpi_ex_out_integer
(paren
l_string|&quot;Reference Count&quot;
comma
id|node-&gt;reference_count
)paren
suffix:semicolon
id|acpi_ex_out_pointer
(paren
l_string|&quot;Attached Object&quot;
comma
id|acpi_ns_get_attached_object
(paren
id|node
)paren
)paren
suffix:semicolon
id|acpi_ex_out_pointer
(paren
l_string|&quot;child_list&quot;
comma
id|node-&gt;child
)paren
suffix:semicolon
id|acpi_ex_out_pointer
(paren
l_string|&quot;next_peer&quot;
comma
id|node-&gt;peer
)paren
suffix:semicolon
id|acpi_ex_out_pointer
(paren
l_string|&quot;Parent&quot;
comma
id|acpi_ns_get_parent_node
(paren
id|node
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*****************************************************************************&n; *&n; * FUNCTION:    acpi_ex_dump_object_descriptor&n; *&n; * PARAMETERS:  *Object             - Descriptor to dump&n; *              Flags               - Force display&n; *&n; * DESCRIPTION: Dumps the members of the object descriptor given.&n; *&n; ****************************************************************************/
r_void
DECL|function|acpi_ex_dump_object_descriptor
id|acpi_ex_dump_object_descriptor
(paren
r_union
id|acpi_operand_object
op_star
id|obj_desc
comma
id|u32
id|flags
)paren
(brace
id|u32
id|i
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ex_dump_object_descriptor&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|flags
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
(paren
id|ACPI_LV_OBJECTS
op_amp
id|acpi_dbg_level
)paren
op_logical_and
(paren
id|_COMPONENT
op_amp
id|acpi_dbg_layer
)paren
)paren
)paren
(brace
id|return_VOID
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|ACPI_GET_DESCRIPTOR_TYPE
(paren
id|obj_desc
)paren
op_eq
id|ACPI_DESC_TYPE_NAMED
)paren
(brace
id|acpi_ex_dump_node
(paren
(paren
r_struct
id|acpi_namespace_node
op_star
)paren
id|obj_desc
comma
id|flags
)paren
suffix:semicolon
id|acpi_os_printf
(paren
l_string|&quot;&bslash;nAttached Object (%p):&bslash;n&quot;
comma
(paren
(paren
r_struct
id|acpi_namespace_node
op_star
)paren
id|obj_desc
)paren
op_member_access_from_pointer
id|object
)paren
suffix:semicolon
id|acpi_ex_dump_object_descriptor
(paren
(paren
(paren
r_struct
id|acpi_namespace_node
op_star
)paren
id|obj_desc
)paren
op_member_access_from_pointer
id|object
comma
id|flags
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
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
id|acpi_os_printf
(paren
l_string|&quot;ex_dump_object_descriptor: %p is not an ACPI operand object: [%s]&bslash;n&quot;
comma
id|obj_desc
comma
id|acpi_ut_get_descriptor_name
(paren
id|obj_desc
)paren
)paren
suffix:semicolon
id|return_VOID
suffix:semicolon
)brace
multiline_comment|/* Common Fields */
id|acpi_ex_out_string
(paren
l_string|&quot;Type&quot;
comma
id|acpi_ut_get_object_type_name
(paren
id|obj_desc
)paren
)paren
suffix:semicolon
id|acpi_ex_out_integer
(paren
l_string|&quot;Reference Count&quot;
comma
id|obj_desc-&gt;common.reference_count
)paren
suffix:semicolon
id|acpi_ex_out_integer
(paren
l_string|&quot;Flags&quot;
comma
id|obj_desc-&gt;common.flags
)paren
suffix:semicolon
multiline_comment|/* Object-specific Fields */
r_switch
c_cond
(paren
id|ACPI_GET_OBJECT_TYPE
(paren
id|obj_desc
)paren
)paren
(brace
r_case
id|ACPI_TYPE_INTEGER
suffix:colon
id|acpi_os_printf
(paren
l_string|&quot;%20s : %8.8X%8.8X&bslash;n&quot;
comma
l_string|&quot;Value&quot;
comma
id|ACPI_FORMAT_UINT64
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
id|acpi_ex_out_integer
(paren
l_string|&quot;Length&quot;
comma
id|obj_desc-&gt;string.length
)paren
suffix:semicolon
id|acpi_os_printf
(paren
l_string|&quot;%20s : %p &quot;
comma
l_string|&quot;Pointer&quot;
comma
id|obj_desc-&gt;string.pointer
)paren
suffix:semicolon
id|acpi_ut_print_string
(paren
id|obj_desc-&gt;string.pointer
comma
id|ACPI_UINT8_MAX
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
id|ACPI_TYPE_BUFFER
suffix:colon
id|acpi_ex_out_integer
(paren
l_string|&quot;Length&quot;
comma
id|obj_desc-&gt;buffer.length
)paren
suffix:semicolon
id|acpi_ex_out_pointer
(paren
l_string|&quot;Pointer&quot;
comma
id|obj_desc-&gt;buffer.pointer
)paren
suffix:semicolon
id|ACPI_DUMP_BUFFER
(paren
id|obj_desc-&gt;buffer.pointer
comma
id|obj_desc-&gt;buffer.length
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_PACKAGE
suffix:colon
id|acpi_ex_out_integer
(paren
l_string|&quot;Flags&quot;
comma
id|obj_desc-&gt;package.flags
)paren
suffix:semicolon
id|acpi_ex_out_integer
(paren
l_string|&quot;Count&quot;
comma
id|obj_desc-&gt;package.count
)paren
suffix:semicolon
id|acpi_ex_out_pointer
(paren
l_string|&quot;Elements&quot;
comma
id|obj_desc-&gt;package.elements
)paren
suffix:semicolon
multiline_comment|/* Dump the package contents */
r_if
c_cond
(paren
id|obj_desc-&gt;package.count
OG
l_int|0
)paren
(brace
id|acpi_os_printf
(paren
l_string|&quot;&bslash;nPackage Contents:&bslash;n&quot;
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
id|obj_desc-&gt;package.count
suffix:semicolon
id|i
op_increment
)paren
(brace
id|acpi_os_printf
(paren
l_string|&quot;[%.3d] %p&quot;
comma
id|i
comma
id|obj_desc-&gt;package.elements
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|obj_desc-&gt;package.elements
(braket
id|i
)braket
)paren
(brace
id|acpi_os_printf
(paren
l_string|&quot; %s&quot;
comma
id|acpi_ut_get_object_type_name
(paren
id|obj_desc-&gt;package.elements
(braket
id|i
)braket
)paren
)paren
suffix:semicolon
)brace
id|acpi_os_printf
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_DEVICE
suffix:colon
id|acpi_ex_out_pointer
(paren
l_string|&quot;Handler&quot;
comma
id|obj_desc-&gt;device.handler
)paren
suffix:semicolon
id|acpi_ex_out_pointer
(paren
l_string|&quot;system_notify&quot;
comma
id|obj_desc-&gt;device.system_notify
)paren
suffix:semicolon
id|acpi_ex_out_pointer
(paren
l_string|&quot;device_notify&quot;
comma
id|obj_desc-&gt;device.device_notify
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_EVENT
suffix:colon
id|acpi_ex_out_pointer
(paren
l_string|&quot;Semaphore&quot;
comma
id|obj_desc-&gt;event.semaphore
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_METHOD
suffix:colon
id|acpi_ex_out_integer
(paren
l_string|&quot;param_count&quot;
comma
id|obj_desc-&gt;method.param_count
)paren
suffix:semicolon
id|acpi_ex_out_integer
(paren
l_string|&quot;Concurrency&quot;
comma
id|obj_desc-&gt;method.concurrency
)paren
suffix:semicolon
id|acpi_ex_out_pointer
(paren
l_string|&quot;Semaphore&quot;
comma
id|obj_desc-&gt;method.semaphore
)paren
suffix:semicolon
id|acpi_ex_out_integer
(paren
l_string|&quot;owning_id&quot;
comma
id|obj_desc-&gt;method.owning_id
)paren
suffix:semicolon
id|acpi_ex_out_integer
(paren
l_string|&quot;aml_length&quot;
comma
id|obj_desc-&gt;method.aml_length
)paren
suffix:semicolon
id|acpi_ex_out_pointer
(paren
l_string|&quot;aml_start&quot;
comma
id|obj_desc-&gt;method.aml_start
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_MUTEX
suffix:colon
id|acpi_ex_out_integer
(paren
l_string|&quot;sync_level&quot;
comma
id|obj_desc-&gt;mutex.sync_level
)paren
suffix:semicolon
id|acpi_ex_out_pointer
(paren
l_string|&quot;owner_thread&quot;
comma
id|obj_desc-&gt;mutex.owner_thread
)paren
suffix:semicolon
id|acpi_ex_out_integer
(paren
l_string|&quot;acquisition_depth&quot;
comma
id|obj_desc-&gt;mutex.acquisition_depth
)paren
suffix:semicolon
id|acpi_ex_out_pointer
(paren
l_string|&quot;Semaphore&quot;
comma
id|obj_desc-&gt;mutex.semaphore
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_REGION
suffix:colon
id|acpi_ex_out_integer
(paren
l_string|&quot;space_id&quot;
comma
id|obj_desc-&gt;region.space_id
)paren
suffix:semicolon
id|acpi_ex_out_integer
(paren
l_string|&quot;Flags&quot;
comma
id|obj_desc-&gt;region.flags
)paren
suffix:semicolon
id|acpi_ex_out_address
(paren
l_string|&quot;Address&quot;
comma
id|obj_desc-&gt;region.address
)paren
suffix:semicolon
id|acpi_ex_out_integer
(paren
l_string|&quot;Length&quot;
comma
id|obj_desc-&gt;region.length
)paren
suffix:semicolon
id|acpi_ex_out_pointer
(paren
l_string|&quot;Handler&quot;
comma
id|obj_desc-&gt;region.handler
)paren
suffix:semicolon
id|acpi_ex_out_pointer
(paren
l_string|&quot;Next&quot;
comma
id|obj_desc-&gt;region.next
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_POWER
suffix:colon
id|acpi_ex_out_integer
(paren
l_string|&quot;system_level&quot;
comma
id|obj_desc-&gt;power_resource.system_level
)paren
suffix:semicolon
id|acpi_ex_out_integer
(paren
l_string|&quot;resource_order&quot;
comma
id|obj_desc-&gt;power_resource.resource_order
)paren
suffix:semicolon
id|acpi_ex_out_pointer
(paren
l_string|&quot;system_notify&quot;
comma
id|obj_desc-&gt;power_resource.system_notify
)paren
suffix:semicolon
id|acpi_ex_out_pointer
(paren
l_string|&quot;device_notify&quot;
comma
id|obj_desc-&gt;power_resource.device_notify
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_PROCESSOR
suffix:colon
id|acpi_ex_out_integer
(paren
l_string|&quot;Processor ID&quot;
comma
id|obj_desc-&gt;processor.proc_id
)paren
suffix:semicolon
id|acpi_ex_out_integer
(paren
l_string|&quot;Length&quot;
comma
id|obj_desc-&gt;processor.length
)paren
suffix:semicolon
id|acpi_ex_out_address
(paren
l_string|&quot;Address&quot;
comma
(paren
id|acpi_physical_address
)paren
id|obj_desc-&gt;processor.address
)paren
suffix:semicolon
id|acpi_ex_out_pointer
(paren
l_string|&quot;system_notify&quot;
comma
id|obj_desc-&gt;processor.system_notify
)paren
suffix:semicolon
id|acpi_ex_out_pointer
(paren
l_string|&quot;device_notify&quot;
comma
id|obj_desc-&gt;processor.device_notify
)paren
suffix:semicolon
id|acpi_ex_out_pointer
(paren
l_string|&quot;Handler&quot;
comma
id|obj_desc-&gt;processor.handler
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_THERMAL
suffix:colon
id|acpi_ex_out_pointer
(paren
l_string|&quot;system_notify&quot;
comma
id|obj_desc-&gt;thermal_zone.system_notify
)paren
suffix:semicolon
id|acpi_ex_out_pointer
(paren
l_string|&quot;device_notify&quot;
comma
id|obj_desc-&gt;thermal_zone.device_notify
)paren
suffix:semicolon
id|acpi_ex_out_pointer
(paren
l_string|&quot;Handler&quot;
comma
id|obj_desc-&gt;thermal_zone.handler
)paren
suffix:semicolon
r_break
suffix:semicolon
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
id|acpi_ex_out_integer
(paren
l_string|&quot;field_flags&quot;
comma
id|obj_desc-&gt;common_field.field_flags
)paren
suffix:semicolon
id|acpi_ex_out_integer
(paren
l_string|&quot;access_byte_width&quot;
comma
id|obj_desc-&gt;common_field.access_byte_width
)paren
suffix:semicolon
id|acpi_ex_out_integer
(paren
l_string|&quot;bit_length&quot;
comma
id|obj_desc-&gt;common_field.bit_length
)paren
suffix:semicolon
id|acpi_ex_out_integer
(paren
l_string|&quot;fld_bit_offset&quot;
comma
id|obj_desc-&gt;common_field.start_field_bit_offset
)paren
suffix:semicolon
id|acpi_ex_out_integer
(paren
l_string|&quot;base_byte_offset&quot;
comma
id|obj_desc-&gt;common_field.base_byte_offset
)paren
suffix:semicolon
id|acpi_ex_out_integer
(paren
l_string|&quot;datum_valid_bits&quot;
comma
id|obj_desc-&gt;common_field.datum_valid_bits
)paren
suffix:semicolon
id|acpi_ex_out_integer
(paren
l_string|&quot;end_fld_valid_bits&quot;
comma
id|obj_desc-&gt;common_field.end_field_valid_bits
)paren
suffix:semicolon
id|acpi_ex_out_integer
(paren
l_string|&quot;end_buf_valid_bits&quot;
comma
id|obj_desc-&gt;common_field.end_buffer_valid_bits
)paren
suffix:semicolon
id|acpi_ex_out_pointer
(paren
l_string|&quot;parent_node&quot;
comma
id|obj_desc-&gt;common_field.node
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|ACPI_GET_OBJECT_TYPE
(paren
id|obj_desc
)paren
)paren
(brace
r_case
id|ACPI_TYPE_BUFFER_FIELD
suffix:colon
id|acpi_ex_out_pointer
(paren
l_string|&quot;buffer_obj&quot;
comma
id|obj_desc-&gt;buffer_field.buffer_obj
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_LOCAL_REGION_FIELD
suffix:colon
id|acpi_ex_out_pointer
(paren
l_string|&quot;region_obj&quot;
comma
id|obj_desc-&gt;field.region_obj
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_LOCAL_BANK_FIELD
suffix:colon
id|acpi_ex_out_integer
(paren
l_string|&quot;Value&quot;
comma
id|obj_desc-&gt;bank_field.value
)paren
suffix:semicolon
id|acpi_ex_out_pointer
(paren
l_string|&quot;region_obj&quot;
comma
id|obj_desc-&gt;bank_field.region_obj
)paren
suffix:semicolon
id|acpi_ex_out_pointer
(paren
l_string|&quot;bank_obj&quot;
comma
id|obj_desc-&gt;bank_field.bank_obj
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_LOCAL_INDEX_FIELD
suffix:colon
id|acpi_ex_out_integer
(paren
l_string|&quot;Value&quot;
comma
id|obj_desc-&gt;index_field.value
)paren
suffix:semicolon
id|acpi_ex_out_pointer
(paren
l_string|&quot;Index&quot;
comma
id|obj_desc-&gt;index_field.index_obj
)paren
suffix:semicolon
id|acpi_ex_out_pointer
(paren
l_string|&quot;Data&quot;
comma
id|obj_desc-&gt;index_field.data_obj
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* All object types covered above */
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_LOCAL_REFERENCE
suffix:colon
id|acpi_ex_out_integer
(paren
l_string|&quot;target_type&quot;
comma
id|obj_desc-&gt;reference.target_type
)paren
suffix:semicolon
id|acpi_ex_out_string
(paren
l_string|&quot;Opcode&quot;
comma
(paren
id|acpi_ps_get_opcode_info
(paren
id|obj_desc-&gt;reference.opcode
)paren
)paren
op_member_access_from_pointer
id|name
)paren
suffix:semicolon
id|acpi_ex_out_integer
(paren
l_string|&quot;Offset&quot;
comma
id|obj_desc-&gt;reference.offset
)paren
suffix:semicolon
id|acpi_ex_out_pointer
(paren
l_string|&quot;obj_desc&quot;
comma
id|obj_desc-&gt;reference.object
)paren
suffix:semicolon
id|acpi_ex_out_pointer
(paren
l_string|&quot;Node&quot;
comma
id|obj_desc-&gt;reference.node
)paren
suffix:semicolon
id|acpi_ex_out_pointer
(paren
l_string|&quot;Where&quot;
comma
id|obj_desc-&gt;reference.where
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_LOCAL_ADDRESS_HANDLER
suffix:colon
id|acpi_ex_out_integer
(paren
l_string|&quot;space_id&quot;
comma
id|obj_desc-&gt;address_space.space_id
)paren
suffix:semicolon
id|acpi_ex_out_pointer
(paren
l_string|&quot;Next&quot;
comma
id|obj_desc-&gt;address_space.next
)paren
suffix:semicolon
id|acpi_ex_out_pointer
(paren
l_string|&quot;region_list&quot;
comma
id|obj_desc-&gt;address_space.region_list
)paren
suffix:semicolon
id|acpi_ex_out_pointer
(paren
l_string|&quot;Node&quot;
comma
id|obj_desc-&gt;address_space.node
)paren
suffix:semicolon
id|acpi_ex_out_pointer
(paren
l_string|&quot;Context&quot;
comma
id|obj_desc-&gt;address_space.context
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_LOCAL_NOTIFY
suffix:colon
id|acpi_ex_out_pointer
(paren
l_string|&quot;Node&quot;
comma
id|obj_desc-&gt;notify.node
)paren
suffix:semicolon
id|acpi_ex_out_pointer
(paren
l_string|&quot;Context&quot;
comma
id|obj_desc-&gt;notify.context
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_LOCAL_ALIAS
suffix:colon
r_case
id|ACPI_TYPE_LOCAL_EXTRA
suffix:colon
r_case
id|ACPI_TYPE_LOCAL_DATA
suffix:colon
r_default
suffix:colon
id|acpi_os_printf
(paren
l_string|&quot;ex_dump_object_descriptor: Display not implemented for object type %s&bslash;n&quot;
comma
id|acpi_ut_get_object_type_name
(paren
id|obj_desc
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|return_VOID
suffix:semicolon
)brace
macro_line|#endif
eof
