multiline_comment|/*&n; * attrib.h - Defines for attribute handling in NTFS Linux kernel driver.&n; *&t;      Part of the Linux-NTFS project.&n; *&n; * Copyright (c) 2001,2002 Anton Altaparmakov.&n; * Copyright (C) 2002 Richard Russon.&n; *&n; * This program/include file is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License as published&n; * by the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program/include file is distributed in the hope that it will be &n; * useful, but WITHOUT ANY WARRANTY; without even the implied warranty &n; * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program (in the main directory of the Linux-NTFS &n; * distribution in the file COPYING); if not, write to the Free Software&n; * Foundation,Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef _LINUX_NTFS_ATTRIB_H
DECL|macro|_LINUX_NTFS_ATTRIB_H
mdefine_line|#define _LINUX_NTFS_ATTRIB_H
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &quot;endian.h&quot;
macro_line|#include &quot;types.h&quot;
macro_line|#include &quot;layout.h&quot;
r_typedef
r_enum
(brace
DECL|enumerator|LCN_HOLE
id|LCN_HOLE
op_assign
op_minus
l_int|1
comma
multiline_comment|/* Keep this as highest value or die! */
DECL|enumerator|LCN_RL_NOT_MAPPED
id|LCN_RL_NOT_MAPPED
op_assign
op_minus
l_int|2
comma
DECL|enumerator|LCN_ENOENT
id|LCN_ENOENT
op_assign
op_minus
l_int|3
comma
DECL|enumerator|LCN_EINVAL
id|LCN_EINVAL
op_assign
op_minus
l_int|4
comma
DECL|typedef|LCN_SPECIAL_VALUES
)brace
id|LCN_SPECIAL_VALUES
suffix:semicolon
multiline_comment|/**&n; * attr_search_context - used in attribute search functions&n; * @mrec:&t;buffer containing mft record to search&n; * @attr:&t;attribute record in @mrec where to begin/continue search&n; * @is_first:&t;if true lookup_attr() begins search with @attr, else after @attr&n; *&n; * Structure must be initialized to zero before the first call to one of the&n; * attribute search functions. Initialize @mrec to point to the mft record to&n; * search, and @attr to point to the first attribute within @mrec (not necessary&n; * if calling the _first() functions), and set @is_first to TRUE (not necessary&n; * if calling the _first() functions).&n; *&n; * If @is_first is TRUE, the search begins with @attr. If @is_first is FALSE,&n; * the search begins after @attr. This is so that, after the first call to one&n; * of the search attribute functions, we can call the function again, without&n; * any modification of the search context, to automagically get the next&n; * matching attribute.&n; */
r_typedef
r_struct
(brace
DECL|member|mrec
id|MFT_RECORD
op_star
id|mrec
suffix:semicolon
DECL|member|attr
id|ATTR_RECORD
op_star
id|attr
suffix:semicolon
DECL|member|is_first
id|BOOL
id|is_first
suffix:semicolon
DECL|member|ntfs_ino
id|ntfs_inode
op_star
id|ntfs_ino
suffix:semicolon
DECL|member|al_entry
id|ATTR_LIST_ENTRY
op_star
id|al_entry
suffix:semicolon
DECL|member|base_ntfs_ino
id|ntfs_inode
op_star
id|base_ntfs_ino
suffix:semicolon
DECL|member|base_mrec
id|MFT_RECORD
op_star
id|base_mrec
suffix:semicolon
DECL|member|base_attr
id|ATTR_RECORD
op_star
id|base_attr
suffix:semicolon
DECL|typedef|attr_search_context
)brace
id|attr_search_context
suffix:semicolon
r_extern
id|run_list_element
op_star
id|decompress_mapping_pairs
c_func
(paren
r_const
id|ntfs_volume
op_star
id|vol
comma
r_const
id|ATTR_RECORD
op_star
id|attr
comma
id|run_list_element
op_star
id|old_rl
)paren
suffix:semicolon
r_extern
r_int
id|map_run_list
c_func
(paren
id|ntfs_inode
op_star
id|ni
comma
id|VCN
id|vcn
)paren
suffix:semicolon
r_extern
id|LCN
id|vcn_to_lcn
c_func
(paren
r_const
id|run_list_element
op_star
id|rl
comma
r_const
id|VCN
id|vcn
)paren
suffix:semicolon
r_extern
id|BOOL
id|find_attr
c_func
(paren
r_const
id|ATTR_TYPES
id|type
comma
r_const
id|uchar_t
op_star
id|name
comma
r_const
id|u32
id|name_len
comma
r_const
id|IGNORE_CASE_BOOL
id|ic
comma
r_const
id|u8
op_star
id|val
comma
r_const
id|u32
id|val_len
comma
id|attr_search_context
op_star
id|ctx
)paren
suffix:semicolon
id|BOOL
id|lookup_attr
c_func
(paren
r_const
id|ATTR_TYPES
id|type
comma
r_const
id|uchar_t
op_star
id|name
comma
r_const
id|u32
id|name_len
comma
r_const
id|IGNORE_CASE_BOOL
id|ic
comma
r_const
id|VCN
id|lowest_vcn
comma
r_const
id|u8
op_star
id|val
comma
r_const
id|u32
id|val_len
comma
id|attr_search_context
op_star
id|ctx
)paren
suffix:semicolon
r_extern
r_int
id|load_attribute_list
c_func
(paren
id|ntfs_volume
op_star
id|vol
comma
id|run_list_element
op_star
id|rl
comma
id|u8
op_star
id|al
comma
r_const
id|s64
id|size
)paren
suffix:semicolon
DECL|function|attribute_value_length
r_static
r_inline
id|s64
id|attribute_value_length
c_func
(paren
r_const
id|ATTR_RECORD
op_star
id|a
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|a-&gt;non_resident
)paren
r_return
(paren
id|s64
)paren
id|le32_to_cpu
c_func
(paren
id|a
op_member_access_from_pointer
id|_ARA
c_func
(paren
id|value_length
)paren
)paren
suffix:semicolon
r_return
id|sle64_to_cpu
c_func
(paren
id|a
op_member_access_from_pointer
id|_ANR
c_func
(paren
id|data_size
)paren
)paren
suffix:semicolon
)brace
r_extern
r_void
id|reinit_attr_search_ctx
c_func
(paren
id|attr_search_context
op_star
id|ctx
)paren
suffix:semicolon
r_extern
r_int
id|get_attr_search_ctx
c_func
(paren
id|attr_search_context
op_star
op_star
id|ctx
comma
id|ntfs_inode
op_star
id|ni
comma
id|MFT_RECORD
op_star
id|mrec
)paren
suffix:semicolon
r_extern
r_void
id|put_attr_search_ctx
c_func
(paren
id|attr_search_context
op_star
id|ctx
)paren
suffix:semicolon
macro_line|#endif /* _LINUX_NTFS_ATTRIB_H */
eof
