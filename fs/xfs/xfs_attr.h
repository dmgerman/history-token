multiline_comment|/*&n; * Copyright (c) 2000, 2002 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.&t; Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#ifndef __XFS_ATTR_H__
DECL|macro|__XFS_ATTR_H__
mdefine_line|#define __XFS_ATTR_H__
multiline_comment|/*&n; * xfs_attr.h&n; *&n; * Large attribute lists are structured around Btrees where all the data&n; * elements are in the leaf nodes.  Attribute names are hashed into an int,&n; * then that int is used as the index into the Btree.  Since the hashval&n; * of an attribute name may not be unique, we may have duplicate keys.&n; * The internal links in the Btree are logical block offsets into the file.&n; *&n; * Small attribute lists use a different format and are packed as tightly&n; * as possible so as to fit into the literal area of the inode.&n; */
macro_line|#ifdef XFS_ALL_TRACE
DECL|macro|XFS_ATTR_TRACE
mdefine_line|#define XFS_ATTR_TRACE
macro_line|#endif
macro_line|#if !defined(DEBUG)
DECL|macro|XFS_ATTR_TRACE
macro_line|#undef XFS_ATTR_TRACE
macro_line|#endif
multiline_comment|/*========================================================================&n; * External interfaces&n; *========================================================================*/
DECL|macro|ATTR_ROOT
mdefine_line|#define ATTR_ROOT&t;0x0002&t;/* use attrs in root namespace, not user */
DECL|macro|ATTR_CREATE
mdefine_line|#define ATTR_CREATE&t;0x0010&t;/* pure create: fail if attr already exists */
DECL|macro|ATTR_REPLACE
mdefine_line|#define ATTR_REPLACE&t;0x0020&t;/* pure set: fail if attr does not exist */
DECL|macro|ATTR_KERNOTIME
mdefine_line|#define ATTR_KERNOTIME&t;0x1000&t;/* [kernel] don&squot;t update inode timestamps */
DECL|macro|ATTR_KERNOVAL
mdefine_line|#define ATTR_KERNOVAL&t;0x2000&t;/* [kernel] get attr size only, not value */
DECL|macro|ATTR_KERNAMELS
mdefine_line|#define ATTR_KERNAMELS&t;0x4000&t;/* [kernel] list attr names (simple list) */
DECL|macro|ATTR_KERNFULLS
mdefine_line|#define ATTR_KERNFULLS&t;0x8000&t;/* [kernel] full attr list, ie. root+user */
multiline_comment|/*&n; * The maximum size (into the kernel or returned from the kernel) of an&n; * attribute value or the buffer used for an attr_list() call.&t;Larger&n; * sizes will result in an ERANGE return code.&n; */
DECL|macro|ATTR_MAX_VALUELEN
mdefine_line|#define ATTR_MAX_VALUELEN&t;(64*1024)&t;/* max length of a value */
multiline_comment|/*&n; * Define how lists of attribute names are returned to the user from&n; * the attr_list() call.  A large, 32bit aligned, buffer is passed in&n; * along with its size.&t; We put an array of offsets at the top that each&n; * reference an attrlist_ent_t and pack the attrlist_ent_t&squot;s at the bottom.&n; */
DECL|struct|attrlist
r_typedef
r_struct
id|attrlist
(brace
DECL|member|al_count
id|__s32
id|al_count
suffix:semicolon
multiline_comment|/* number of entries in attrlist */
DECL|member|al_more
id|__s32
id|al_more
suffix:semicolon
multiline_comment|/* T/F: more attrs (do call again) */
DECL|member|al_offset
id|__s32
id|al_offset
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* byte offsets of attrs [var-sized] */
DECL|typedef|attrlist_t
)brace
id|attrlist_t
suffix:semicolon
multiline_comment|/*&n; * Show the interesting info about one attribute.  This is what the&n; * al_offset[i] entry points to.&n; */
DECL|struct|attrlist_ent
r_typedef
r_struct
id|attrlist_ent
(brace
multiline_comment|/* data from attr_list() */
DECL|member|a_valuelen
id|__u32
id|a_valuelen
suffix:semicolon
multiline_comment|/* number bytes in value of attr */
DECL|member|a_name
r_char
id|a_name
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* attr name (NULL terminated) */
DECL|typedef|attrlist_ent_t
)brace
id|attrlist_ent_t
suffix:semicolon
multiline_comment|/*&n; * Given a pointer to the (char*) buffer containing the attr_list() result,&n; * and an index, return a pointer to the indicated attribute in the buffer.&n; */
DECL|macro|ATTR_ENTRY
mdefine_line|#define ATTR_ENTRY(buffer, index)&t;&t;&bslash;&n;&t;((attrlist_ent_t *)&t;&t;&t;&bslash;&n;&t; &amp;((char *)buffer)[ ((attrlist_t *)(buffer))-&gt;al_offset[index] ])
multiline_comment|/*&n; * Multi-attribute operation vector.&n; */
DECL|struct|attr_multiop
r_typedef
r_struct
id|attr_multiop
(brace
DECL|member|am_opcode
r_int
id|am_opcode
suffix:semicolon
multiline_comment|/* operation to perform (ATTR_OP_GET, etc.) */
DECL|member|am_error
r_int
id|am_error
suffix:semicolon
multiline_comment|/* [out arg] result of this sub-op (an errno) */
DECL|member|am_attrname
r_char
op_star
id|am_attrname
suffix:semicolon
multiline_comment|/* attribute name to work with */
DECL|member|am_attrvalue
r_char
op_star
id|am_attrvalue
suffix:semicolon
multiline_comment|/* [in/out arg] attribute value (raw bytes) */
DECL|member|am_length
r_int
id|am_length
suffix:semicolon
multiline_comment|/* [in/out arg] length of value */
DECL|member|am_flags
r_int
id|am_flags
suffix:semicolon
multiline_comment|/* bitwise OR of attr API flags defined above */
DECL|typedef|attr_multiop_t
)brace
id|attr_multiop_t
suffix:semicolon
DECL|macro|ATTR_OP_GET
mdefine_line|#define ATTR_OP_GET&t;1&t;/* return the indicated attr&squot;s value */
DECL|macro|ATTR_OP_SET
mdefine_line|#define ATTR_OP_SET&t;2&t;/* set/create the indicated attr/value pair */
DECL|macro|ATTR_OP_REMOVE
mdefine_line|#define ATTR_OP_REMOVE&t;3&t;/* remove the indicated attr */
multiline_comment|/*&n; * Kernel-internal version of the attrlist cursor.&n; */
DECL|struct|attrlist_cursor_kern
r_typedef
r_struct
id|attrlist_cursor_kern
(brace
DECL|member|hashval
id|__u32
id|hashval
suffix:semicolon
multiline_comment|/* hash value of next entry to add */
DECL|member|blkno
id|__u32
id|blkno
suffix:semicolon
multiline_comment|/* block containing entry (suggestion) */
DECL|member|offset
id|__u32
id|offset
suffix:semicolon
multiline_comment|/* offset in list of equal-hashvals */
DECL|member|pad1
id|__u16
id|pad1
suffix:semicolon
multiline_comment|/* padding to match user-level */
DECL|member|pad2
id|__u8
id|pad2
suffix:semicolon
multiline_comment|/* padding to match user-level */
DECL|member|initted
id|__u8
id|initted
suffix:semicolon
multiline_comment|/* T/F: cursor has been initialized */
DECL|typedef|attrlist_cursor_kern_t
)brace
id|attrlist_cursor_kern_t
suffix:semicolon
multiline_comment|/*========================================================================&n; * Function prototypes for the kernel.&n; *========================================================================*/
r_struct
id|cred
suffix:semicolon
r_struct
id|vnode
suffix:semicolon
r_struct
id|xfs_inode
suffix:semicolon
r_struct
id|attrlist_cursor_kern
suffix:semicolon
r_struct
id|xfs_ext_attr
suffix:semicolon
r_struct
id|xfs_da_args
suffix:semicolon
multiline_comment|/*&n; * Overall external interface routines.&n; */
r_int
id|xfs_attr_get
c_func
(paren
id|bhv_desc_t
op_star
comma
r_char
op_star
comma
r_char
op_star
comma
r_int
op_star
comma
r_int
comma
r_struct
id|cred
op_star
)paren
suffix:semicolon
r_int
id|xfs_attr_set
c_func
(paren
id|bhv_desc_t
op_star
comma
r_char
op_star
comma
r_char
op_star
comma
r_int
comma
r_int
comma
r_struct
id|cred
op_star
)paren
suffix:semicolon
r_int
id|xfs_attr_remove
c_func
(paren
id|bhv_desc_t
op_star
comma
r_char
op_star
comma
r_int
comma
r_struct
id|cred
op_star
)paren
suffix:semicolon
r_int
id|xfs_attr_list
c_func
(paren
id|bhv_desc_t
op_star
comma
r_char
op_star
comma
r_int
comma
r_int
comma
r_struct
id|attrlist_cursor_kern
op_star
comma
r_struct
id|cred
op_star
)paren
suffix:semicolon
r_int
id|xfs_attr_inactive
c_func
(paren
r_struct
id|xfs_inode
op_star
id|dp
)paren
suffix:semicolon
r_int
id|xfs_attr_node_get
c_func
(paren
r_struct
id|xfs_da_args
op_star
)paren
suffix:semicolon
r_int
id|xfs_attr_leaf_get
c_func
(paren
r_struct
id|xfs_da_args
op_star
)paren
suffix:semicolon
r_int
id|xfs_attr_shortform_getvalue
c_func
(paren
r_struct
id|xfs_da_args
op_star
)paren
suffix:semicolon
r_int
id|xfs_attr_fetch
c_func
(paren
r_struct
id|xfs_inode
op_star
comma
r_char
op_star
comma
r_char
op_star
comma
r_int
)paren
suffix:semicolon
macro_line|#endif&t;/* __XFS_ATTR_H__ */
eof
