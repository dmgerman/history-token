multiline_comment|/*&n; * Copyright (c) 2000, 2002 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.&t; Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#ifndef __XFS_ATTR_SF_H__
DECL|macro|__XFS_ATTR_SF_H__
mdefine_line|#define __XFS_ATTR_SF_H__
multiline_comment|/*&n; * Attribute storage when stored inside the inode.&n; *&n; * Small attribute lists are packed as tightly as possible so as&n; * to fit into the literal area of the inode.&n; */
r_struct
id|xfs_inode
suffix:semicolon
multiline_comment|/*&n; * Entries are packed toward the top as tight as possible.&n; */
DECL|struct|xfs_attr_shortform
r_typedef
r_struct
id|xfs_attr_shortform
(brace
DECL|struct|xfs_attr_sf_hdr
r_struct
id|xfs_attr_sf_hdr
(brace
multiline_comment|/* constant-structure header block */
DECL|member|totsize
id|__uint16_t
id|totsize
suffix:semicolon
multiline_comment|/* total bytes in shortform list */
DECL|member|count
id|__uint8_t
id|count
suffix:semicolon
multiline_comment|/* count of active entries */
DECL|member|hdr
)brace
id|hdr
suffix:semicolon
DECL|struct|xfs_attr_sf_entry
r_struct
id|xfs_attr_sf_entry
(brace
DECL|member|namelen
id|__uint8_t
id|namelen
suffix:semicolon
multiline_comment|/* actual length of name (no NULL) */
DECL|member|valuelen
id|__uint8_t
id|valuelen
suffix:semicolon
multiline_comment|/* actual length of value (no NULL) */
DECL|member|flags
id|__uint8_t
id|flags
suffix:semicolon
multiline_comment|/* flags bits (see xfs_attr_leaf.h) */
DECL|member|nameval
id|__uint8_t
id|nameval
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* name &amp; value bytes concatenated */
DECL|member|list
)brace
id|list
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* variable sized array */
DECL|typedef|xfs_attr_shortform_t
)brace
id|xfs_attr_shortform_t
suffix:semicolon
DECL|typedef|xfs_attr_sf_hdr_t
r_typedef
r_struct
id|xfs_attr_sf_hdr
id|xfs_attr_sf_hdr_t
suffix:semicolon
DECL|typedef|xfs_attr_sf_entry_t
r_typedef
r_struct
id|xfs_attr_sf_entry
id|xfs_attr_sf_entry_t
suffix:semicolon
multiline_comment|/*&n; * We generate this then sort it, attr_list() must return things in hash-order.&n; */
DECL|struct|xfs_attr_sf_sort
r_typedef
r_struct
id|xfs_attr_sf_sort
(brace
DECL|member|entno
id|__uint8_t
id|entno
suffix:semicolon
multiline_comment|/* entry number in original list */
DECL|member|namelen
id|__uint8_t
id|namelen
suffix:semicolon
multiline_comment|/* length of name value (no null) */
DECL|member|valuelen
id|__uint8_t
id|valuelen
suffix:semicolon
multiline_comment|/* length of value */
DECL|member|flags
id|__uint8_t
id|flags
suffix:semicolon
multiline_comment|/* flags bits (see xfs_attr_leaf.h) */
DECL|member|hash
id|xfs_dahash_t
id|hash
suffix:semicolon
multiline_comment|/* this entry&squot;s hash value */
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
multiline_comment|/* name value, pointer into buffer */
DECL|typedef|xfs_attr_sf_sort_t
)brace
id|xfs_attr_sf_sort_t
suffix:semicolon
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_ATTR_SF_ENTSIZE_BYNAME)
r_int
id|xfs_attr_sf_entsize_byname
c_func
(paren
r_int
id|nlen
comma
r_int
id|vlen
)paren
suffix:semicolon
DECL|macro|XFS_ATTR_SF_ENTSIZE_BYNAME
mdefine_line|#define XFS_ATTR_SF_ENTSIZE_BYNAME(nlen,vlen)&t;&bslash;&n;&t;xfs_attr_sf_entsize_byname(nlen,vlen)
macro_line|#else
DECL|macro|XFS_ATTR_SF_ENTSIZE_BYNAME
mdefine_line|#define XFS_ATTR_SF_ENTSIZE_BYNAME(nlen,vlen)&t;/* space name/value uses */ &bslash;&n;&t;((int)sizeof(xfs_attr_sf_entry_t)-1 + (nlen)+(vlen))
macro_line|#endif
DECL|macro|XFS_ATTR_SF_ENTSIZE_MAX
mdefine_line|#define XFS_ATTR_SF_ENTSIZE_MAX&t;&t;&t;/* max space for name&amp;value */ &bslash;&n;&t;((1 &lt;&lt; (NBBY*(int)sizeof(__uint8_t))) - 1)
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_ATTR_SF_ENTSIZE)
r_int
id|xfs_attr_sf_entsize
c_func
(paren
id|xfs_attr_sf_entry_t
op_star
id|sfep
)paren
suffix:semicolon
DECL|macro|XFS_ATTR_SF_ENTSIZE
mdefine_line|#define XFS_ATTR_SF_ENTSIZE(sfep)&t;xfs_attr_sf_entsize(sfep)
macro_line|#else
DECL|macro|XFS_ATTR_SF_ENTSIZE
mdefine_line|#define XFS_ATTR_SF_ENTSIZE(sfep)&t;&t;/* space an entry uses */ &bslash;&n;&t;((int)sizeof(xfs_attr_sf_entry_t)-1 + (sfep)-&gt;namelen+(sfep)-&gt;valuelen)
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_ATTR_SF_NEXTENTRY)
id|xfs_attr_sf_entry_t
op_star
id|xfs_attr_sf_nextentry
c_func
(paren
id|xfs_attr_sf_entry_t
op_star
id|sfep
)paren
suffix:semicolon
DECL|macro|XFS_ATTR_SF_NEXTENTRY
mdefine_line|#define XFS_ATTR_SF_NEXTENTRY(sfep)&t;xfs_attr_sf_nextentry(sfep)
macro_line|#else
DECL|macro|XFS_ATTR_SF_NEXTENTRY
mdefine_line|#define XFS_ATTR_SF_NEXTENTRY(sfep)&t;&t;/* next entry in struct */ &bslash;&n;&t;((xfs_attr_sf_entry_t *) &bslash;&n;&t;&t;((char *)(sfep) + XFS_ATTR_SF_ENTSIZE(sfep)))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_ATTR_SF_TOTSIZE)
r_int
id|xfs_attr_sf_totsize
c_func
(paren
r_struct
id|xfs_inode
op_star
id|dp
)paren
suffix:semicolon
DECL|macro|XFS_ATTR_SF_TOTSIZE
mdefine_line|#define XFS_ATTR_SF_TOTSIZE(dp)&t;&t;xfs_attr_sf_totsize(dp)
macro_line|#else
DECL|macro|XFS_ATTR_SF_TOTSIZE
mdefine_line|#define XFS_ATTR_SF_TOTSIZE(dp)&t;&t;&t;/* total space in use */ &bslash;&n;&t;(INT_GET(((xfs_attr_shortform_t *)((dp)-&gt;i_afp-&gt;if_u1.if_data))-&gt;hdr.totsize, ARCH_CONVERT))
macro_line|#endif
macro_line|#ifdef XFS_ALL_TRACE
DECL|macro|XFS_ATTR_TRACE
mdefine_line|#define XFS_ATTR_TRACE
macro_line|#endif
macro_line|#if !defined(DEBUG)
DECL|macro|XFS_ATTR_TRACE
macro_line|#undef&t;XFS_ATTR_TRACE
macro_line|#endif
multiline_comment|/*&n; * Kernel tracing support for attribute lists&n; */
r_struct
id|xfs_attr_list_context
suffix:semicolon
r_struct
id|xfs_da_intnode
suffix:semicolon
r_struct
id|xfs_da_node_entry
suffix:semicolon
r_struct
id|xfs_attr_leafblock
suffix:semicolon
DECL|macro|XFS_ATTR_TRACE_SIZE
mdefine_line|#define XFS_ATTR_TRACE_SIZE&t;4096&t;/* size of global trace buffer */
multiline_comment|/*&n; * Trace record types.&n; */
DECL|macro|XFS_ATTR_KTRACE_L_C
mdefine_line|#define XFS_ATTR_KTRACE_L_C&t;1&t;/* context */
DECL|macro|XFS_ATTR_KTRACE_L_CN
mdefine_line|#define XFS_ATTR_KTRACE_L_CN&t;2&t;/* context, node */
DECL|macro|XFS_ATTR_KTRACE_L_CB
mdefine_line|#define XFS_ATTR_KTRACE_L_CB&t;3&t;/* context, btree */
DECL|macro|XFS_ATTR_KTRACE_L_CL
mdefine_line|#define XFS_ATTR_KTRACE_L_CL&t;4&t;/* context, leaf */
macro_line|#if defined(XFS_ATTR_TRACE)
r_void
id|xfs_attr_trace_l_c
c_func
(paren
r_char
op_star
id|where
comma
r_struct
id|xfs_attr_list_context
op_star
id|context
)paren
suffix:semicolon
r_void
id|xfs_attr_trace_l_cn
c_func
(paren
r_char
op_star
id|where
comma
r_struct
id|xfs_attr_list_context
op_star
id|context
comma
r_struct
id|xfs_da_intnode
op_star
id|node
)paren
suffix:semicolon
r_void
id|xfs_attr_trace_l_cb
c_func
(paren
r_char
op_star
id|where
comma
r_struct
id|xfs_attr_list_context
op_star
id|context
comma
r_struct
id|xfs_da_node_entry
op_star
id|btree
)paren
suffix:semicolon
r_void
id|xfs_attr_trace_l_cl
c_func
(paren
r_char
op_star
id|where
comma
r_struct
id|xfs_attr_list_context
op_star
id|context
comma
r_struct
id|xfs_attr_leafblock
op_star
id|leaf
)paren
suffix:semicolon
r_void
id|xfs_attr_trace_enter
c_func
(paren
r_int
id|type
comma
r_char
op_star
id|where
comma
id|__psunsigned_t
id|a2
comma
id|__psunsigned_t
id|a3
comma
id|__psunsigned_t
id|a4
comma
id|__psunsigned_t
id|a5
comma
id|__psunsigned_t
id|a6
comma
id|__psunsigned_t
id|a7
comma
id|__psunsigned_t
id|a8
comma
id|__psunsigned_t
id|a9
comma
id|__psunsigned_t
id|a10
comma
id|__psunsigned_t
id|a11
comma
id|__psunsigned_t
id|a12
comma
id|__psunsigned_t
id|a13
comma
id|__psunsigned_t
id|a14
comma
id|__psunsigned_t
id|a15
)paren
suffix:semicolon
macro_line|#else
DECL|macro|xfs_attr_trace_l_c
mdefine_line|#define xfs_attr_trace_l_c(w,c)
DECL|macro|xfs_attr_trace_l_cn
mdefine_line|#define xfs_attr_trace_l_cn(w,c,n)
DECL|macro|xfs_attr_trace_l_cb
mdefine_line|#define xfs_attr_trace_l_cb(w,c,b)
DECL|macro|xfs_attr_trace_l_cl
mdefine_line|#define xfs_attr_trace_l_cl(w,c,l)
macro_line|#endif /* XFS_ATTR_TRACE */
macro_line|#endif&t;/* __XFS_ATTR_SF_H__ */
eof
