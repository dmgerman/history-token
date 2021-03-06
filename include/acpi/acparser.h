multiline_comment|/******************************************************************************&n; *&n; * Module Name: acparser.h - AML Parser subcomponent prototypes and defines&n; *&n; *****************************************************************************/
multiline_comment|/*&n; * Copyright (C) 2000 - 2005, R. Byron Moore&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. Redistributions in binary form must reproduce at minimum a disclaimer&n; *    substantially similar to the &quot;NO WARRANTY&quot; disclaimer below&n; *    (&quot;Disclaimer&quot;) and any redistribution must be conditioned upon&n; *    including a substantially similar Disclaimer requirement for further&n; *    binary redistribution.&n; * 3. Neither the names of the above-listed copyright holders nor the names&n; *    of any contributors may be used to endorse or promote products derived&n; *    from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;) version 2 as published by the Free&n; * Software Foundation.&n; *&n; * NO WARRANTY&n; * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS&n; * &quot;AS IS&quot; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT&n; * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR&n; * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT&n; * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,&n; * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING&n; * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE&n; * POSSIBILITY OF SUCH DAMAGES.&n; */
macro_line|#ifndef __ACPARSER_H__
DECL|macro|__ACPARSER_H__
mdefine_line|#define __ACPARSER_H__
DECL|macro|OP_HAS_RETURN_VALUE
mdefine_line|#define OP_HAS_RETURN_VALUE             1
multiline_comment|/* variable # arguments */
DECL|macro|ACPI_VAR_ARGS
mdefine_line|#define ACPI_VAR_ARGS                   ACPI_UINT32_MAX
DECL|macro|ACPI_PARSE_DELETE_TREE
mdefine_line|#define ACPI_PARSE_DELETE_TREE          0x0001
DECL|macro|ACPI_PARSE_NO_TREE_DELETE
mdefine_line|#define ACPI_PARSE_NO_TREE_DELETE       0x0000
DECL|macro|ACPI_PARSE_TREE_MASK
mdefine_line|#define ACPI_PARSE_TREE_MASK            0x0001
DECL|macro|ACPI_PARSE_LOAD_PASS1
mdefine_line|#define ACPI_PARSE_LOAD_PASS1           0x0010
DECL|macro|ACPI_PARSE_LOAD_PASS2
mdefine_line|#define ACPI_PARSE_LOAD_PASS2           0x0020
DECL|macro|ACPI_PARSE_EXECUTE
mdefine_line|#define ACPI_PARSE_EXECUTE              0x0030
DECL|macro|ACPI_PARSE_MODE_MASK
mdefine_line|#define ACPI_PARSE_MODE_MASK            0x0030
DECL|macro|ACPI_PARSE_DEFERRED_OP
mdefine_line|#define ACPI_PARSE_DEFERRED_OP          0x0100
multiline_comment|/* Parser external interfaces */
id|acpi_status
id|acpi_psx_load_table
(paren
id|u8
op_star
id|pcode_addr
comma
id|u32
id|pcode_length
)paren
suffix:semicolon
id|acpi_status
id|acpi_psx_execute
(paren
r_struct
id|acpi_parameter_info
op_star
id|info
)paren
suffix:semicolon
multiline_comment|/******************************************************************************&n; *&n; * Parser interfaces&n; *&n; *****************************************************************************/
multiline_comment|/* psargs - Parse AML opcode arguments */
id|u8
op_star
id|acpi_ps_get_next_package_end
(paren
r_struct
id|acpi_parse_state
op_star
id|parser_state
)paren
suffix:semicolon
id|u32
id|acpi_ps_get_next_package_length
(paren
r_struct
id|acpi_parse_state
op_star
id|parser_state
)paren
suffix:semicolon
r_char
op_star
id|acpi_ps_get_next_namestring
(paren
r_struct
id|acpi_parse_state
op_star
id|parser_state
)paren
suffix:semicolon
r_void
id|acpi_ps_get_next_simple_arg
(paren
r_struct
id|acpi_parse_state
op_star
id|parser_state
comma
id|u32
id|arg_type
comma
r_union
id|acpi_parse_object
op_star
id|arg
)paren
suffix:semicolon
id|acpi_status
id|acpi_ps_get_next_namepath
(paren
r_struct
id|acpi_walk_state
op_star
id|walk_state
comma
r_struct
id|acpi_parse_state
op_star
id|parser_state
comma
r_union
id|acpi_parse_object
op_star
id|arg
comma
id|u8
id|method_call
)paren
suffix:semicolon
r_union
id|acpi_parse_object
op_star
id|acpi_ps_get_next_field
(paren
r_struct
id|acpi_parse_state
op_star
id|parser_state
)paren
suffix:semicolon
id|acpi_status
id|acpi_ps_get_next_arg
(paren
r_struct
id|acpi_walk_state
op_star
id|walk_state
comma
r_struct
id|acpi_parse_state
op_star
id|parser_state
comma
id|u32
id|arg_type
comma
r_union
id|acpi_parse_object
op_star
op_star
id|return_arg
)paren
suffix:semicolon
multiline_comment|/* psfind */
r_union
id|acpi_parse_object
op_star
id|acpi_ps_find_name
(paren
r_union
id|acpi_parse_object
op_star
id|scope
comma
id|u32
id|name
comma
id|u32
id|opcode
)paren
suffix:semicolon
r_union
id|acpi_parse_object
op_star
id|acpi_ps_get_parent
(paren
r_union
id|acpi_parse_object
op_star
id|op
)paren
suffix:semicolon
multiline_comment|/* psopcode - AML Opcode information */
r_const
r_struct
id|acpi_opcode_info
op_star
id|acpi_ps_get_opcode_info
(paren
id|u16
id|opcode
)paren
suffix:semicolon
r_char
op_star
id|acpi_ps_get_opcode_name
(paren
id|u16
id|opcode
)paren
suffix:semicolon
multiline_comment|/* psparse - top level parsing routines */
id|u32
id|acpi_ps_get_opcode_size
(paren
id|u32
id|opcode
)paren
suffix:semicolon
r_void
id|acpi_ps_complete_this_op
(paren
r_struct
id|acpi_walk_state
op_star
id|walk_state
comma
r_union
id|acpi_parse_object
op_star
id|op
)paren
suffix:semicolon
id|acpi_status
id|acpi_ps_next_parse_state
(paren
r_struct
id|acpi_walk_state
op_star
id|walk_state
comma
r_union
id|acpi_parse_object
op_star
id|op
comma
id|acpi_status
id|callback_status
)paren
suffix:semicolon
id|acpi_status
id|acpi_ps_find_object
(paren
r_struct
id|acpi_walk_state
op_star
id|walk_state
comma
r_union
id|acpi_parse_object
op_star
op_star
id|out_op
)paren
suffix:semicolon
r_void
id|acpi_ps_delete_parse_tree
(paren
r_union
id|acpi_parse_object
op_star
id|root
)paren
suffix:semicolon
id|acpi_status
id|acpi_ps_parse_loop
(paren
r_struct
id|acpi_walk_state
op_star
id|walk_state
)paren
suffix:semicolon
id|acpi_status
id|acpi_ps_parse_aml
(paren
r_struct
id|acpi_walk_state
op_star
id|walk_state
)paren
suffix:semicolon
id|acpi_status
id|acpi_ps_parse_table
(paren
id|u8
op_star
id|aml
comma
id|u32
id|aml_size
comma
id|acpi_parse_downwards
id|descending_callback
comma
id|acpi_parse_upwards
id|ascending_callback
comma
r_union
id|acpi_parse_object
op_star
op_star
id|root_object
)paren
suffix:semicolon
id|u16
id|acpi_ps_peek_opcode
(paren
r_struct
id|acpi_parse_state
op_star
id|state
)paren
suffix:semicolon
multiline_comment|/* psscope - Scope stack management routines */
id|acpi_status
id|acpi_ps_init_scope
(paren
r_struct
id|acpi_parse_state
op_star
id|parser_state
comma
r_union
id|acpi_parse_object
op_star
id|root
)paren
suffix:semicolon
r_union
id|acpi_parse_object
op_star
id|acpi_ps_get_parent_scope
(paren
r_struct
id|acpi_parse_state
op_star
id|state
)paren
suffix:semicolon
id|u8
id|acpi_ps_has_completed_scope
(paren
r_struct
id|acpi_parse_state
op_star
id|parser_state
)paren
suffix:semicolon
r_void
id|acpi_ps_pop_scope
(paren
r_struct
id|acpi_parse_state
op_star
id|parser_state
comma
r_union
id|acpi_parse_object
op_star
op_star
id|op
comma
id|u32
op_star
id|arg_list
comma
id|u32
op_star
id|arg_count
)paren
suffix:semicolon
id|acpi_status
id|acpi_ps_push_scope
(paren
r_struct
id|acpi_parse_state
op_star
id|parser_state
comma
r_union
id|acpi_parse_object
op_star
id|op
comma
id|u32
id|remaining_args
comma
id|u32
id|arg_count
)paren
suffix:semicolon
r_void
id|acpi_ps_cleanup_scope
(paren
r_struct
id|acpi_parse_state
op_star
id|state
)paren
suffix:semicolon
multiline_comment|/* pstree - parse tree manipulation routines */
r_void
id|acpi_ps_append_arg
c_func
(paren
r_union
id|acpi_parse_object
op_star
id|op
comma
r_union
id|acpi_parse_object
op_star
id|arg
)paren
suffix:semicolon
r_union
id|acpi_parse_object
op_star
id|acpi_ps_find
(paren
r_union
id|acpi_parse_object
op_star
id|scope
comma
r_char
op_star
id|path
comma
id|u16
id|opcode
comma
id|u32
id|create
)paren
suffix:semicolon
r_union
id|acpi_parse_object
op_star
id|acpi_ps_get_arg
c_func
(paren
r_union
id|acpi_parse_object
op_star
id|op
comma
id|u32
id|argn
)paren
suffix:semicolon
macro_line|#ifdef ACPI_FUTURE_USAGE
r_union
id|acpi_parse_object
op_star
id|acpi_ps_get_child
(paren
r_union
id|acpi_parse_object
op_star
id|op
)paren
suffix:semicolon
r_union
id|acpi_parse_object
op_star
id|acpi_ps_get_depth_next
(paren
r_union
id|acpi_parse_object
op_star
id|origin
comma
r_union
id|acpi_parse_object
op_star
id|op
)paren
suffix:semicolon
macro_line|#endif  /*  ACPI_FUTURE_USAGE  */
multiline_comment|/* pswalk - parse tree walk routines */
id|acpi_status
id|acpi_ps_walk_parsed_aml
(paren
r_union
id|acpi_parse_object
op_star
id|start_op
comma
r_union
id|acpi_parse_object
op_star
id|end_op
comma
r_union
id|acpi_operand_object
op_star
id|mth_desc
comma
r_struct
id|acpi_namespace_node
op_star
id|start_node
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
id|caller_return_desc
comma
id|acpi_owner_id
id|owner_id
comma
id|acpi_parse_downwards
id|descending_callback
comma
id|acpi_parse_upwards
id|ascending_callback
)paren
suffix:semicolon
id|acpi_status
id|acpi_ps_get_next_walk_op
(paren
r_struct
id|acpi_walk_state
op_star
id|walk_state
comma
r_union
id|acpi_parse_object
op_star
id|op
comma
id|acpi_parse_upwards
id|ascending_callback
)paren
suffix:semicolon
id|acpi_status
id|acpi_ps_delete_completed_op
(paren
r_struct
id|acpi_walk_state
op_star
id|walk_state
)paren
suffix:semicolon
multiline_comment|/* psutils - parser utilities */
r_union
id|acpi_parse_object
op_star
id|acpi_ps_create_scope_op
(paren
r_void
)paren
suffix:semicolon
r_void
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
suffix:semicolon
r_union
id|acpi_parse_object
op_star
id|acpi_ps_alloc_op
(paren
id|u16
id|opcode
)paren
suffix:semicolon
r_void
id|acpi_ps_free_op
(paren
r_union
id|acpi_parse_object
op_star
id|op
)paren
suffix:semicolon
macro_line|#ifdef ACPI_ENABLE_OBJECT_CACHE
r_void
id|acpi_ps_delete_parse_cache
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
id|u8
id|acpi_ps_is_leading_char
(paren
id|u32
id|c
)paren
suffix:semicolon
id|u8
id|acpi_ps_is_prefix_char
(paren
id|u32
id|c
)paren
suffix:semicolon
macro_line|#ifdef ACPI_FUTURE_USAGE
id|u32
id|acpi_ps_get_name
c_func
(paren
r_union
id|acpi_parse_object
op_star
id|op
)paren
suffix:semicolon
macro_line|#endif
r_void
id|acpi_ps_set_name
c_func
(paren
r_union
id|acpi_parse_object
op_star
id|op
comma
id|u32
id|name
)paren
suffix:semicolon
multiline_comment|/* psdump - display parser tree */
id|u32
id|acpi_ps_sprint_path
(paren
r_char
op_star
id|buffer_start
comma
id|u32
id|buffer_size
comma
r_union
id|acpi_parse_object
op_star
id|op
)paren
suffix:semicolon
id|u32
id|acpi_ps_sprint_op
(paren
r_char
op_star
id|buffer_start
comma
id|u32
id|buffer_size
comma
r_union
id|acpi_parse_object
op_star
id|op
)paren
suffix:semicolon
r_void
id|acpi_ps_show
(paren
r_union
id|acpi_parse_object
op_star
id|op
)paren
suffix:semicolon
macro_line|#endif /* __ACPARSER_H__ */
eof
