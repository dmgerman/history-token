multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997, 2000-2003 Silicon Graphics, Inc. All rights reserved.&n; */
macro_line|#ifndef _ASM_IA64_SN_LABELCL_H
DECL|macro|_ASM_IA64_SN_LABELCL_H
mdefine_line|#define _ASM_IA64_SN_LABELCL_H
DECL|macro|LABELCL_MAGIC
mdefine_line|#define LABELCL_MAGIC 0x4857434c&t;/* &squot;HWLC&squot; */
DECL|macro|LABEL_LENGTH_MAX
mdefine_line|#define LABEL_LENGTH_MAX 256&t;&t;/* Includes NULL char */
DECL|macro|INFO_DESC_PRIVATE
mdefine_line|#define INFO_DESC_PRIVATE (-1)      &t;/* default */
DECL|macro|INFO_DESC_EXPORT
mdefine_line|#define INFO_DESC_EXPORT  0       &t;/* export info itself */
multiline_comment|/*&n; * Internal Error codes.&n; */
DECL|enum|labelcl_error_e
DECL|enumerator|LABELCL_SUCCESS
r_typedef
r_enum
id|labelcl_error_e
(brace
id|LABELCL_SUCCESS
comma
multiline_comment|/* 0 */
DECL|enumerator|LABELCL_DUP
id|LABELCL_DUP
comma
multiline_comment|/* 1 */
DECL|enumerator|LABELCL_NOT_FOUND
id|LABELCL_NOT_FOUND
comma
multiline_comment|/* 2 */
DECL|enumerator|LABELCL_BAD_PARAM
id|LABELCL_BAD_PARAM
comma
multiline_comment|/* 3 */
DECL|enumerator|LABELCL_HIT_LIMIT
id|LABELCL_HIT_LIMIT
comma
multiline_comment|/* 4 */
DECL|enumerator|LABELCL_CANNOT_ALLOC
id|LABELCL_CANNOT_ALLOC
comma
multiline_comment|/* 5 */
DECL|enumerator|LABELCL_ILLEGAL_REQUEST
id|LABELCL_ILLEGAL_REQUEST
comma
multiline_comment|/* 6 */
DECL|enumerator|LABELCL_IN_USE
id|LABELCL_IN_USE
multiline_comment|/* 7 */
DECL|typedef|labelcl_error_t
)brace
id|labelcl_error_t
suffix:semicolon
multiline_comment|/*&n; * Description of a label entry.&n; */
DECL|struct|label_info_s
r_typedef
r_struct
id|label_info_s
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|desc
id|arb_info_desc_t
id|desc
suffix:semicolon
DECL|member|info
id|arbitrary_info_t
id|info
suffix:semicolon
DECL|typedef|label_info_t
)brace
id|label_info_t
suffix:semicolon
multiline_comment|/*&n; * Definition of the data structure that provides the link to &n; * the hwgraph fastinfo and the label entries associated with a &n; * particular hwgraph entry.&n; */
DECL|struct|labelcl_info_s
r_typedef
r_struct
id|labelcl_info_s
(brace
DECL|member|hwcl_magic
r_int
r_int
id|hwcl_magic
suffix:semicolon
DECL|member|num_labels
r_int
r_int
id|num_labels
suffix:semicolon
DECL|member|label_list
r_void
op_star
id|label_list
suffix:semicolon
DECL|member|IDX_list
id|arbitrary_info_t
id|IDX_list
(braket
id|HWGRAPH_NUM_INDEX_INFO
)braket
suffix:semicolon
DECL|typedef|labelcl_info_t
)brace
id|labelcl_info_t
suffix:semicolon
multiline_comment|/*&n; * Definitions for the string table that holds the actual names &n; * of the labels.&n; */
DECL|struct|string_table_item
r_struct
id|string_table_item
(brace
DECL|member|next
r_struct
id|string_table_item
op_star
id|next
suffix:semicolon
DECL|member|string
r_char
id|string
(braket
l_int|1
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|string_table
r_struct
id|string_table
(brace
DECL|member|string_table_head
r_struct
id|string_table_item
op_star
id|string_table_head
suffix:semicolon
DECL|member|string_table_generation
r_int
id|string_table_generation
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|STRTBL_BASIC_SIZE
mdefine_line|#define STRTBL_BASIC_SIZE ((size_t)(((struct string_table_item *)0)-&gt;string))
DECL|macro|STRTBL_ITEM_SIZE
mdefine_line|#define STRTBL_ITEM_SIZE(str_length) (STRTBL_BASIC_SIZE + (str_length) + 1)
DECL|macro|STRTBL_ALLOC
mdefine_line|#define STRTBL_ALLOC(str_length) &bslash;&n;        ((struct string_table_item *)kmalloc(STRTBL_ITEM_SIZE(str_length), GFP_KERNEL))
DECL|macro|STRTBL_FREE
mdefine_line|#define STRTBL_FREE(ptr) kfree(ptr)
r_extern
id|labelcl_info_t
op_star
id|labelcl_info_create
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|labelcl_info_destroy
c_func
(paren
id|labelcl_info_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|labelcl_info_add_LBL
c_func
(paren
id|vertex_hdl_t
comma
r_char
op_star
comma
id|arb_info_desc_t
comma
id|arbitrary_info_t
)paren
suffix:semicolon
r_extern
r_int
id|labelcl_info_remove_LBL
c_func
(paren
id|vertex_hdl_t
comma
r_char
op_star
comma
id|arb_info_desc_t
op_star
comma
id|arbitrary_info_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|labelcl_info_replace_LBL
c_func
(paren
id|vertex_hdl_t
comma
r_char
op_star
comma
id|arb_info_desc_t
comma
id|arbitrary_info_t
comma
id|arb_info_desc_t
op_star
comma
id|arbitrary_info_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|labelcl_info_get_LBL
c_func
(paren
id|vertex_hdl_t
comma
r_char
op_star
comma
id|arb_info_desc_t
op_star
comma
id|arbitrary_info_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|labelcl_info_get_next_LBL
c_func
(paren
id|vertex_hdl_t
comma
r_char
op_star
comma
id|arb_info_desc_t
op_star
comma
id|arbitrary_info_t
op_star
comma
id|labelcl_info_place_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|labelcl_info_replace_IDX
c_func
(paren
id|vertex_hdl_t
comma
r_int
comma
id|arbitrary_info_t
comma
id|arbitrary_info_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|labelcl_info_connectpt_set
c_func
(paren
id|vertex_hdl_t
comma
id|vertex_hdl_t
)paren
suffix:semicolon
r_extern
r_int
id|labelcl_info_get_IDX
c_func
(paren
id|vertex_hdl_t
comma
r_int
comma
id|arbitrary_info_t
op_star
)paren
suffix:semicolon
macro_line|#endif /* _ASM_IA64_SN_LABELCL_H */
eof
