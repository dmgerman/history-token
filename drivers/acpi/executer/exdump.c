multiline_comment|/******************************************************************************&n; *&n; * Module Name: exdump - Interpreter debug output routines&n; *              $Revision: 159 $&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000 - 2002, R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &quot;acpi.h&quot;
macro_line|#include &quot;acinterp.h&quot;
macro_line|#include &quot;amlcode.h&quot;
macro_line|#include &quot;acnamesp.h&quot;
macro_line|#include &quot;acparser.h&quot;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_EXECUTER
id|ACPI_MODULE_NAME
(paren
l_string|&quot;exdump&quot;
)paren
multiline_comment|/*&n; * The following routines are used for debug output only&n; */
macro_line|#if defined(ACPI_DEBUG_OUTPUT) || defined(ACPI_DEBUGGER)
multiline_comment|/*****************************************************************************&n; *&n; * FUNCTION:    Acpi_ex_dump_operand&n; *&n; * PARAMETERS:  *Obj_desc         - Pointer to entry to be dumped&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Dump an operand object&n; *&n; ****************************************************************************/
r_void
DECL|function|acpi_ex_dump_operand
id|acpi_ex_dump_operand
(paren
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
id|u32
id|i
suffix:semicolon
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
l_string|&quot;Ex_dump_operand&quot;
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
multiline_comment|/*&n;&t;&t; * This usually indicates that something serious is wrong --&n;&t;&t; * since most (if not all)&n;&t;&t; * code that dumps the stack expects something to be there!&n;&t;&t; */
id|acpi_os_printf
(paren
l_string|&quot;Null stack entry ptr&bslash;n&quot;
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
l_string|&quot;%p NS Node: &quot;
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
l_string|&quot;%p is not a local object&bslash;n&quot;
comma
id|obj_desc
)paren
)paren
suffix:semicolon
id|ACPI_DUMP_BUFFER
(paren
id|obj_desc
comma
r_sizeof
(paren
id|acpi_operand_object
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*  Obj_desc is a valid object */
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
id|INTERNAL_TYPE_REFERENCE
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
l_string|&quot;Reference: (Ref_of) %p&bslash;n&quot;
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
multiline_comment|/* Value is a Number */
id|acpi_os_printf
(paren
l_string|&quot; value is [%8.8X%8.8x]&quot;
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
multiline_comment|/* Value is a Number */
id|acpi_os_printf
(paren
l_string|&quot; value is [%8.8X%8.8x]&quot;
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
multiline_comment|/*  unknown opcode  */
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
id|INTERNAL_TYPE_IF
suffix:colon
id|acpi_os_printf
(paren
l_string|&quot;If [Integer] %8.8X%8.8X&bslash;n&quot;
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
id|INTERNAL_TYPE_WHILE
suffix:colon
id|acpi_os_printf
(paren
l_string|&quot;While [Integer] %8.8X%8.8X&bslash;n&quot;
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
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_STRING
suffix:colon
id|acpi_os_printf
(paren
l_string|&quot;String length %X @ %p &bslash;&quot;&quot;
comma
id|obj_desc-&gt;string.length
comma
id|obj_desc-&gt;string.pointer
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
id|obj_desc-&gt;string.length
suffix:semicolon
id|i
op_increment
)paren
(brace
id|acpi_os_printf
(paren
l_string|&quot;%c&quot;
comma
id|obj_desc-&gt;string.pointer
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
id|acpi_os_printf
(paren
l_string|&quot;&bslash;&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|INTERNAL_TYPE_BANK_FIELD
suffix:colon
id|acpi_os_printf
(paren
l_string|&quot;Bank_field&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|INTERNAL_TYPE_REGION_FIELD
suffix:colon
id|acpi_os_printf
(paren
l_string|&quot;Region_field: Bits=%X Acc_width=%X Lock=%X Update=%X at byte=%X bit=%X of below:&bslash;n&quot;
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
id|INTERNAL_TYPE_INDEX_FIELD
suffix:colon
id|acpi_os_printf
(paren
l_string|&quot;Index_field&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_BUFFER_FIELD
suffix:colon
id|acpi_os_printf
(paren
l_string|&quot;Buffer_field: %X bits at byte %X bit %X of &bslash;n&quot;
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
multiline_comment|/*****************************************************************************&n; *&n; * FUNCTION:    Acpi_ex_dump_operands&n; *&n; * PARAMETERS:  Interpreter_mode     - Load or Exec&n; *              *Ident              - Identification&n; *              Num_levels          - # of stack entries to dump above line&n; *              *Note               - Output notation&n; *&n; * DESCRIPTION: Dump the object stack&n; *&n; ****************************************************************************/
r_void
DECL|function|acpi_ex_dump_operands
id|acpi_ex_dump_operands
(paren
id|acpi_operand_object
op_star
op_star
id|operands
comma
id|acpi_interpreter_mode
id|interpreter_mode
comma
id|NATIVE_CHAR
op_star
id|ident
comma
id|u32
id|num_levels
comma
id|NATIVE_CHAR
op_star
id|note
comma
id|NATIVE_CHAR
op_star
id|module_name
comma
id|u32
id|line_number
)paren
(brace
id|NATIVE_UINT
id|i
suffix:semicolon
id|acpi_operand_object
op_star
op_star
id|obj_desc
suffix:semicolon
id|ACPI_FUNCTION_NAME
(paren
l_string|&quot;Ex_dump_operands&quot;
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
multiline_comment|/*****************************************************************************&n; *&n; * FUNCTION:    Acpi_ex_out*&n; *&n; * PARAMETERS:  Title               - Descriptive text&n; *              Value               - Value to be displayed&n; *&n; * DESCRIPTION: Object dump output formatting functions.  These functions&n; *              reduce the number of format strings required and keeps them&n; *              all in one place for easy modification.&n; *&n; ****************************************************************************/
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
id|ACPI_PHYSICAL_ADDRESS
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
id|ACPI_HIDWORD
(paren
id|value
)paren
comma
id|ACPI_LODWORD
(paren
id|value
)paren
)paren
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/*****************************************************************************&n; *&n; * FUNCTION:    Acpi_ex_dump_node&n; *&n; * PARAMETERS:  *Node           - Descriptor to dump&n; *              Flags               - Force display&n; *&n; * DESCRIPTION: Dumps the members of the given.Node&n; *&n; ****************************************************************************/
r_void
DECL|function|acpi_ex_dump_node
id|acpi_ex_dump_node
(paren
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
id|node-&gt;name.ascii
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
l_string|&quot;Child_list&quot;
comma
id|node-&gt;child
)paren
suffix:semicolon
id|acpi_ex_out_pointer
(paren
l_string|&quot;Next_peer&quot;
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
multiline_comment|/*****************************************************************************&n; *&n; * FUNCTION:    Acpi_ex_dump_object_descriptor&n; *&n; * PARAMETERS:  *Object             - Descriptor to dump&n; *              Flags               - Force display&n; *&n; * DESCRIPTION: Dumps the members of the object descriptor given.&n; *&n; ****************************************************************************/
r_void
DECL|function|acpi_ex_dump_object_descriptor
id|acpi_ex_dump_object_descriptor
(paren
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
l_string|&quot;Ex_dump_object_descriptor&quot;
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
op_ne
id|ACPI_DESC_TYPE_OPERAND
)paren
(brace
id|acpi_os_printf
(paren
l_string|&quot;Ex_dump_object_descriptor: %p is not a valid ACPI object&bslash;n&quot;
comma
id|obj_desc
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
id|ACPI_TYPE_STRING
suffix:colon
id|acpi_ex_out_integer
(paren
l_string|&quot;Length&quot;
comma
id|obj_desc-&gt;string.length
)paren
suffix:semicolon
id|acpi_ex_out_pointer
(paren
l_string|&quot;Pointer&quot;
comma
id|obj_desc-&gt;string.pointer
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
l_string|&quot;Addr_handler&quot;
comma
id|obj_desc-&gt;device.addr_handler
)paren
suffix:semicolon
id|acpi_ex_out_pointer
(paren
l_string|&quot;Sys_handler&quot;
comma
id|obj_desc-&gt;device.sys_handler
)paren
suffix:semicolon
id|acpi_ex_out_pointer
(paren
l_string|&quot;Drv_handler&quot;
comma
id|obj_desc-&gt;device.drv_handler
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
l_string|&quot;Param_count&quot;
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
l_string|&quot;Owning_id&quot;
comma
id|obj_desc-&gt;method.owning_id
)paren
suffix:semicolon
id|acpi_ex_out_integer
(paren
l_string|&quot;Aml_length&quot;
comma
id|obj_desc-&gt;method.aml_length
)paren
suffix:semicolon
id|acpi_ex_out_pointer
(paren
l_string|&quot;Aml_start&quot;
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
l_string|&quot;Sync_level&quot;
comma
id|obj_desc-&gt;mutex.sync_level
)paren
suffix:semicolon
id|acpi_ex_out_pointer
(paren
l_string|&quot;Owner_thread&quot;
comma
id|obj_desc-&gt;mutex.owner_thread
)paren
suffix:semicolon
id|acpi_ex_out_integer
(paren
l_string|&quot;Acquisition_depth&quot;
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
l_string|&quot;Space_id&quot;
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
l_string|&quot;Addr_handler&quot;
comma
id|obj_desc-&gt;region.addr_handler
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
l_string|&quot;System_level&quot;
comma
id|obj_desc-&gt;power_resource.system_level
)paren
suffix:semicolon
id|acpi_ex_out_integer
(paren
l_string|&quot;Resource_order&quot;
comma
id|obj_desc-&gt;power_resource.resource_order
)paren
suffix:semicolon
id|acpi_ex_out_pointer
(paren
l_string|&quot;Sys_handler&quot;
comma
id|obj_desc-&gt;power_resource.sys_handler
)paren
suffix:semicolon
id|acpi_ex_out_pointer
(paren
l_string|&quot;Drv_handler&quot;
comma
id|obj_desc-&gt;power_resource.drv_handler
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
id|ACPI_PHYSICAL_ADDRESS
)paren
id|obj_desc-&gt;processor.address
)paren
suffix:semicolon
id|acpi_ex_out_pointer
(paren
l_string|&quot;Sys_handler&quot;
comma
id|obj_desc-&gt;processor.sys_handler
)paren
suffix:semicolon
id|acpi_ex_out_pointer
(paren
l_string|&quot;Drv_handler&quot;
comma
id|obj_desc-&gt;processor.drv_handler
)paren
suffix:semicolon
id|acpi_ex_out_pointer
(paren
l_string|&quot;Addr_handler&quot;
comma
id|obj_desc-&gt;processor.addr_handler
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_THERMAL
suffix:colon
id|acpi_ex_out_pointer
(paren
l_string|&quot;Sys_handler&quot;
comma
id|obj_desc-&gt;thermal_zone.sys_handler
)paren
suffix:semicolon
id|acpi_ex_out_pointer
(paren
l_string|&quot;Drv_handler&quot;
comma
id|obj_desc-&gt;thermal_zone.drv_handler
)paren
suffix:semicolon
id|acpi_ex_out_pointer
(paren
l_string|&quot;Addr_handler&quot;
comma
id|obj_desc-&gt;thermal_zone.addr_handler
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_BUFFER_FIELD
suffix:colon
r_case
id|INTERNAL_TYPE_REGION_FIELD
suffix:colon
r_case
id|INTERNAL_TYPE_BANK_FIELD
suffix:colon
r_case
id|INTERNAL_TYPE_INDEX_FIELD
suffix:colon
id|acpi_ex_out_integer
(paren
l_string|&quot;Field_flags&quot;
comma
id|obj_desc-&gt;common_field.field_flags
)paren
suffix:semicolon
id|acpi_ex_out_integer
(paren
l_string|&quot;Access_byte_width&quot;
comma
id|obj_desc-&gt;common_field.access_byte_width
)paren
suffix:semicolon
id|acpi_ex_out_integer
(paren
l_string|&quot;Bit_length&quot;
comma
id|obj_desc-&gt;common_field.bit_length
)paren
suffix:semicolon
id|acpi_ex_out_integer
(paren
l_string|&quot;Fld_bit_offset&quot;
comma
id|obj_desc-&gt;common_field.start_field_bit_offset
)paren
suffix:semicolon
id|acpi_ex_out_integer
(paren
l_string|&quot;Base_byte_offset&quot;
comma
id|obj_desc-&gt;common_field.base_byte_offset
)paren
suffix:semicolon
id|acpi_ex_out_integer
(paren
l_string|&quot;Datum_valid_bits&quot;
comma
id|obj_desc-&gt;common_field.datum_valid_bits
)paren
suffix:semicolon
id|acpi_ex_out_integer
(paren
l_string|&quot;End_fld_valid_bits&quot;
comma
id|obj_desc-&gt;common_field.end_field_valid_bits
)paren
suffix:semicolon
id|acpi_ex_out_integer
(paren
l_string|&quot;End_buf_valid_bits&quot;
comma
id|obj_desc-&gt;common_field.end_buffer_valid_bits
)paren
suffix:semicolon
id|acpi_ex_out_pointer
(paren
l_string|&quot;Parent_node&quot;
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
l_string|&quot;Buffer_obj&quot;
comma
id|obj_desc-&gt;buffer_field.buffer_obj
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|INTERNAL_TYPE_REGION_FIELD
suffix:colon
id|acpi_ex_out_pointer
(paren
l_string|&quot;Region_obj&quot;
comma
id|obj_desc-&gt;field.region_obj
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|INTERNAL_TYPE_BANK_FIELD
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
l_string|&quot;Region_obj&quot;
comma
id|obj_desc-&gt;bank_field.region_obj
)paren
suffix:semicolon
id|acpi_ex_out_pointer
(paren
l_string|&quot;Bank_obj&quot;
comma
id|obj_desc-&gt;bank_field.bank_obj
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|INTERNAL_TYPE_INDEX_FIELD
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
id|INTERNAL_TYPE_REFERENCE
suffix:colon
id|acpi_ex_out_integer
(paren
l_string|&quot;Target_type&quot;
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
l_string|&quot;Obj_desc&quot;
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
id|INTERNAL_TYPE_ADDRESS_HANDLER
suffix:colon
id|acpi_ex_out_integer
(paren
l_string|&quot;Space_id&quot;
comma
id|obj_desc-&gt;addr_handler.space_id
)paren
suffix:semicolon
id|acpi_ex_out_pointer
(paren
l_string|&quot;Next&quot;
comma
id|obj_desc-&gt;addr_handler.next
)paren
suffix:semicolon
id|acpi_ex_out_pointer
(paren
l_string|&quot;Region_list&quot;
comma
id|obj_desc-&gt;addr_handler.region_list
)paren
suffix:semicolon
id|acpi_ex_out_pointer
(paren
l_string|&quot;Node&quot;
comma
id|obj_desc-&gt;addr_handler.node
)paren
suffix:semicolon
id|acpi_ex_out_pointer
(paren
l_string|&quot;Context&quot;
comma
id|obj_desc-&gt;addr_handler.context
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|INTERNAL_TYPE_NOTIFY
suffix:colon
id|acpi_ex_out_pointer
(paren
l_string|&quot;Node&quot;
comma
id|obj_desc-&gt;notify_handler.node
)paren
suffix:semicolon
id|acpi_ex_out_pointer
(paren
l_string|&quot;Context&quot;
comma
id|obj_desc-&gt;notify_handler.context
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|INTERNAL_TYPE_ALIAS
suffix:colon
r_case
id|INTERNAL_TYPE_FIELD_DEFN
suffix:colon
r_case
id|INTERNAL_TYPE_BANK_FIELD_DEFN
suffix:colon
r_case
id|INTERNAL_TYPE_INDEX_FIELD_DEFN
suffix:colon
r_case
id|INTERNAL_TYPE_IF
suffix:colon
r_case
id|INTERNAL_TYPE_ELSE
suffix:colon
r_case
id|INTERNAL_TYPE_WHILE
suffix:colon
r_case
id|INTERNAL_TYPE_SCOPE
suffix:colon
r_case
id|INTERNAL_TYPE_DEF_ANY
suffix:colon
r_case
id|INTERNAL_TYPE_EXTRA
suffix:colon
r_case
id|INTERNAL_TYPE_DATA
suffix:colon
r_default
suffix:colon
id|acpi_os_printf
(paren
l_string|&quot;Ex_dump_object_descriptor: Display not implemented for object type %s&bslash;n&quot;
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
