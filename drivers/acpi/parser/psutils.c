multiline_comment|/******************************************************************************&n; *&n; * Module Name: psutils - Parser miscellaneous utilities (Parser only)&n; *&n; *****************************************************************************/
multiline_comment|/*&n; * Copyright (C) 2000 - 2004, R. Byron Moore&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. Redistributions in binary form must reproduce at minimum a disclaimer&n; *    substantially similar to the &quot;NO WARRANTY&quot; disclaimer below&n; *    (&quot;Disclaimer&quot;) and any redistribution must be conditioned upon&n; *    including a substantially similar Disclaimer requirement for further&n; *    binary redistribution.&n; * 3. Neither the names of the above-listed copyright holders nor the names&n; *    of any contributors may be used to endorse or promote products derived&n; *    from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;) version 2 as published by the Free&n; * Software Foundation.&n; *&n; * NO WARRANTY&n; * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS&n; * &quot;AS IS&quot; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT&n; * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR&n; * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT&n; * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,&n; * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING&n; * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE&n; * POSSIBILITY OF SUCH DAMAGES.&n; */
macro_line|#include &lt;acpi/acpi.h&gt;
macro_line|#include &lt;acpi/acparser.h&gt;
macro_line|#include &lt;acpi/amlcode.h&gt;
macro_line|#include &lt;acpi/acnamesp.h&gt;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_PARSER
id|ACPI_MODULE_NAME
(paren
l_string|&quot;psutils&quot;
)paren
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ps_create_scope_op&n; *&n; * PARAMETERS:  None&n; *&n; * RETURN:      scope_op&n; *&n; * DESCRIPTION: Create a Scope and associated namepath op with the root name&n; *&n; ******************************************************************************/
r_union
id|acpi_parse_object
op_star
DECL|function|acpi_ps_create_scope_op
id|acpi_ps_create_scope_op
(paren
r_void
)paren
(brace
r_union
id|acpi_parse_object
op_star
id|scope_op
suffix:semicolon
id|scope_op
op_assign
id|acpi_ps_alloc_op
(paren
id|AML_SCOPE_OP
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|scope_op
)paren
(brace
r_return
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
id|scope_op-&gt;named.name
op_assign
id|ACPI_ROOT_NAME
suffix:semicolon
r_return
(paren
id|scope_op
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ps_init_op&n; *&n; * PARAMETERS:  Op              - A newly allocated Op object&n; *              Opcode          - Opcode to store in the Op&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Allocate an acpi_op, choose op type (and thus size) based on&n; *              opcode&n; *&n; ******************************************************************************/
r_void
DECL|function|acpi_ps_init_op
id|acpi_ps_init_op
(paren
r_union
id|acpi_parse_object
op_star
id|op
comma
id|u16
id|opcode
)paren
(brace
id|ACPI_FUNCTION_ENTRY
(paren
)paren
suffix:semicolon
id|op-&gt;common.data_type
op_assign
id|ACPI_DESC_TYPE_PARSER
suffix:semicolon
id|op-&gt;common.aml_opcode
op_assign
id|opcode
suffix:semicolon
id|ACPI_DISASM_ONLY_MEMBERS
(paren
id|ACPI_STRNCPY
(paren
id|op-&gt;common.aml_op_name
comma
(paren
id|acpi_ps_get_opcode_info
(paren
id|opcode
)paren
)paren
op_member_access_from_pointer
id|name
comma
r_sizeof
(paren
id|op-&gt;common.aml_op_name
)paren
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ps_alloc_op&n; *&n; * PARAMETERS:  Opcode          - Opcode that will be stored in the new Op&n; *&n; * RETURN:      Pointer to the new Op.&n; *&n; * DESCRIPTION: Allocate an acpi_op, choose op type (and thus size) based on&n; *              opcode.  A cache of opcodes is available for the pure&n; *              GENERIC_OP, since this is by far the most commonly used.&n; *&n; ******************************************************************************/
r_union
id|acpi_parse_object
op_star
DECL|function|acpi_ps_alloc_op
id|acpi_ps_alloc_op
(paren
id|u16
id|opcode
)paren
(brace
r_union
id|acpi_parse_object
op_star
id|op
op_assign
l_int|NULL
suffix:semicolon
id|u32
id|size
suffix:semicolon
id|u8
id|flags
suffix:semicolon
r_const
r_struct
id|acpi_opcode_info
op_star
id|op_info
suffix:semicolon
id|ACPI_FUNCTION_ENTRY
(paren
)paren
suffix:semicolon
id|op_info
op_assign
id|acpi_ps_get_opcode_info
(paren
id|opcode
)paren
suffix:semicolon
multiline_comment|/* Allocate the minimum required size object */
r_if
c_cond
(paren
id|op_info-&gt;flags
op_amp
id|AML_DEFER
)paren
(brace
id|size
op_assign
r_sizeof
(paren
r_struct
id|acpi_parse_obj_named
)paren
suffix:semicolon
id|flags
op_assign
id|ACPI_PARSEOP_DEFERRED
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|op_info-&gt;flags
op_amp
id|AML_NAMED
)paren
(brace
id|size
op_assign
r_sizeof
(paren
r_struct
id|acpi_parse_obj_named
)paren
suffix:semicolon
id|flags
op_assign
id|ACPI_PARSEOP_NAMED
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|opcode
op_eq
id|AML_INT_BYTELIST_OP
)paren
(brace
id|size
op_assign
r_sizeof
(paren
r_struct
id|acpi_parse_obj_named
)paren
suffix:semicolon
id|flags
op_assign
id|ACPI_PARSEOP_BYTELIST
suffix:semicolon
)brace
r_else
(brace
id|size
op_assign
r_sizeof
(paren
r_struct
id|acpi_parse_obj_common
)paren
suffix:semicolon
id|flags
op_assign
id|ACPI_PARSEOP_GENERIC
suffix:semicolon
)brace
r_if
c_cond
(paren
id|size
op_eq
r_sizeof
(paren
r_struct
id|acpi_parse_obj_common
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t; * The generic op is by far the most common (16 to 1)&n;&t;&t; */
id|op
op_assign
id|acpi_ut_acquire_from_cache
(paren
id|ACPI_MEM_LIST_PSNODE
)paren
suffix:semicolon
)brace
r_else
(brace
id|op
op_assign
id|acpi_ut_acquire_from_cache
(paren
id|ACPI_MEM_LIST_PSNODE_EXT
)paren
suffix:semicolon
)brace
multiline_comment|/* Initialize the Op */
r_if
c_cond
(paren
id|op
)paren
(brace
id|acpi_ps_init_op
(paren
id|op
comma
id|opcode
)paren
suffix:semicolon
id|op-&gt;common.flags
op_assign
id|flags
suffix:semicolon
)brace
r_return
(paren
id|op
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ps_free_op&n; *&n; * PARAMETERS:  Op              - Op to be freed&n; *&n; * RETURN:      None.&n; *&n; * DESCRIPTION: Free an Op object.  Either put it on the GENERIC_OP cache list&n; *              or actually free it.&n; *&n; ******************************************************************************/
r_void
DECL|function|acpi_ps_free_op
id|acpi_ps_free_op
(paren
r_union
id|acpi_parse_object
op_star
id|op
)paren
(brace
id|ACPI_FUNCTION_NAME
(paren
l_string|&quot;ps_free_op&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|op-&gt;common.aml_opcode
op_eq
id|AML_INT_RETURN_VALUE_OP
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ALLOCATIONS
comma
l_string|&quot;Free retval op: %p&bslash;n&quot;
comma
id|op
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|op-&gt;common.flags
op_amp
id|ACPI_PARSEOP_GENERIC
)paren
(brace
id|acpi_ut_release_to_cache
(paren
id|ACPI_MEM_LIST_PSNODE
comma
id|op
)paren
suffix:semicolon
)brace
r_else
(brace
id|acpi_ut_release_to_cache
(paren
id|ACPI_MEM_LIST_PSNODE_EXT
comma
id|op
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ps_delete_parse_cache&n; *&n; * PARAMETERS:  None&n; *&n; * RETURN:      None&n; *&n; * DESCRIPTION: Free all objects that are on the parse cache list.&n; *&n; ******************************************************************************/
r_void
DECL|function|acpi_ps_delete_parse_cache
id|acpi_ps_delete_parse_cache
(paren
r_void
)paren
(brace
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ps_delete_parse_cache&quot;
)paren
suffix:semicolon
id|acpi_ut_delete_generic_cache
(paren
id|ACPI_MEM_LIST_PSNODE
)paren
suffix:semicolon
id|acpi_ut_delete_generic_cache
(paren
id|ACPI_MEM_LIST_PSNODE_EXT
)paren
suffix:semicolon
id|return_VOID
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Utility functions&n; *&n; * DESCRIPTION: Low level character and object functions&n; *&n; ******************************************************************************/
multiline_comment|/*&n; * Is &quot;c&quot; a namestring lead character?&n; */
id|u8
DECL|function|acpi_ps_is_leading_char
id|acpi_ps_is_leading_char
(paren
id|u32
id|c
)paren
(brace
r_return
(paren
(paren
id|u8
)paren
(paren
id|c
op_eq
l_char|&squot;_&squot;
op_logical_or
(paren
id|c
op_ge
l_char|&squot;A&squot;
op_logical_and
id|c
op_le
l_char|&squot;Z&squot;
)paren
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Is &quot;c&quot; a namestring prefix character?&n; */
id|u8
DECL|function|acpi_ps_is_prefix_char
id|acpi_ps_is_prefix_char
(paren
id|u32
id|c
)paren
(brace
r_return
(paren
(paren
id|u8
)paren
(paren
id|c
op_eq
l_char|&squot;&bslash;&bslash;&squot;
op_logical_or
id|c
op_eq
l_char|&squot;^&squot;
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Get op&squot;s name (4-byte name segment) or 0 if unnamed&n; */
id|u32
DECL|function|acpi_ps_get_name
id|acpi_ps_get_name
(paren
r_union
id|acpi_parse_object
op_star
id|op
)paren
(brace
multiline_comment|/* The &quot;generic&quot; object has no name associated with it */
r_if
c_cond
(paren
id|op-&gt;common.flags
op_amp
id|ACPI_PARSEOP_GENERIC
)paren
(brace
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/* Only the &quot;Extended&quot; parse objects have a name */
r_return
(paren
id|op-&gt;named.name
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Set op&squot;s name&n; */
r_void
DECL|function|acpi_ps_set_name
id|acpi_ps_set_name
(paren
r_union
id|acpi_parse_object
op_star
id|op
comma
id|u32
id|name
)paren
(brace
multiline_comment|/* The &quot;generic&quot; object has no name associated with it */
r_if
c_cond
(paren
id|op-&gt;common.flags
op_amp
id|ACPI_PARSEOP_GENERIC
)paren
(brace
r_return
suffix:semicolon
)brace
id|op-&gt;named.name
op_assign
id|name
suffix:semicolon
)brace
eof
