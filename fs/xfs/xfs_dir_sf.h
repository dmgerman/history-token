multiline_comment|/*&n; * Copyright (c) 2000 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.&t; Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#ifndef __XFS_DIR_SF_H__
DECL|macro|__XFS_DIR_SF_H__
mdefine_line|#define __XFS_DIR_SF_H__
multiline_comment|/*&n; * Directory layout when stored internal to an inode.&n; *&n; * Small directories are packed as tightly as possible so as to&n; * fit into the literal area of the inode.&n; */
DECL|member|i
DECL|typedef|xfs_dir_ino_t
r_typedef
r_struct
(brace
id|__uint8_t
id|i
(braket
r_sizeof
(paren
id|xfs_ino_t
)paren
)braket
suffix:semicolon
)brace
id|xfs_dir_ino_t
suffix:semicolon
multiline_comment|/*&n; * The parent directory has a dedicated field, and the self-pointer must&n; * be calculated on the fly.&n; *&n; * Entries are packed toward the top as tight as possible.  The header&n; * and the elements much be bcopy()&squot;d out into a work area to get correct&n; * alignment for the inode number fields.&n; */
DECL|struct|xfs_dir_shortform
r_typedef
r_struct
id|xfs_dir_shortform
(brace
DECL|struct|xfs_dir_sf_hdr
r_struct
id|xfs_dir_sf_hdr
(brace
multiline_comment|/* constant-structure header block */
DECL|member|parent
id|xfs_dir_ino_t
id|parent
suffix:semicolon
multiline_comment|/* parent dir inode number */
DECL|member|count
id|__uint8_t
id|count
suffix:semicolon
multiline_comment|/* count of active entries */
DECL|member|hdr
)brace
id|hdr
suffix:semicolon
DECL|struct|xfs_dir_sf_entry
r_struct
id|xfs_dir_sf_entry
(brace
DECL|member|inumber
id|xfs_dir_ino_t
id|inumber
suffix:semicolon
multiline_comment|/* referenced inode number */
DECL|member|namelen
id|__uint8_t
id|namelen
suffix:semicolon
multiline_comment|/* actual length of name (no NULL) */
DECL|member|name
id|__uint8_t
id|name
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* name */
DECL|member|list
)brace
id|list
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* variable sized array */
DECL|typedef|xfs_dir_shortform_t
)brace
id|xfs_dir_shortform_t
suffix:semicolon
DECL|typedef|xfs_dir_sf_hdr_t
r_typedef
r_struct
id|xfs_dir_sf_hdr
id|xfs_dir_sf_hdr_t
suffix:semicolon
DECL|typedef|xfs_dir_sf_entry_t
r_typedef
r_struct
id|xfs_dir_sf_entry
id|xfs_dir_sf_entry_t
suffix:semicolon
multiline_comment|/*&n; * We generate this then sort it, so that readdirs are returned in&n; * hash-order.&t;Else seekdir won&squot;t work.&n; */
DECL|struct|xfs_dir_sf_sort
r_typedef
r_struct
id|xfs_dir_sf_sort
(brace
DECL|member|entno
id|__uint8_t
id|entno
suffix:semicolon
multiline_comment|/* .=0, ..=1, else entry# + 2 */
DECL|member|seqno
id|__uint8_t
id|seqno
suffix:semicolon
multiline_comment|/* sequence # with same hash value */
DECL|member|namelen
id|__uint8_t
id|namelen
suffix:semicolon
multiline_comment|/* length of name value (no null) */
DECL|member|hash
id|xfs_dahash_t
id|hash
suffix:semicolon
multiline_comment|/* this entry&squot;s hash value */
DECL|member|ino
id|xfs_intino_t
id|ino
suffix:semicolon
multiline_comment|/* this entry&squot;s inode number */
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
multiline_comment|/* name value, pointer into buffer */
DECL|typedef|xfs_dir_sf_sort_t
)brace
id|xfs_dir_sf_sort_t
suffix:semicolon
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_DIR_SF_GET_DIRINO)
r_void
id|xfs_dir_sf_get_dirino_arch
c_func
(paren
id|xfs_dir_ino_t
op_star
id|from
comma
id|xfs_ino_t
op_star
id|to
comma
id|xfs_arch_t
id|arch
)paren
suffix:semicolon
r_void
id|xfs_dir_sf_get_dirino
c_func
(paren
id|xfs_dir_ino_t
op_star
id|from
comma
id|xfs_ino_t
op_star
id|to
)paren
suffix:semicolon
DECL|macro|XFS_DIR_SF_GET_DIRINO_ARCH
mdefine_line|#define XFS_DIR_SF_GET_DIRINO_ARCH(from,to,arch)    xfs_dir_sf_get_dirino_arch(from, to, arch)
DECL|macro|XFS_DIR_SF_GET_DIRINO
mdefine_line|#define XFS_DIR_SF_GET_DIRINO(from,to)&t;&t;    xfs_dir_sf_get_dirino(from, to)
macro_line|#else
DECL|macro|XFS_DIR_SF_GET_DIRINO_ARCH
mdefine_line|#define XFS_DIR_SF_GET_DIRINO_ARCH(from,to,arch)    DIRINO_COPY_ARCH(from,to,arch)
DECL|macro|XFS_DIR_SF_GET_DIRINO
mdefine_line|#define XFS_DIR_SF_GET_DIRINO(from,to)&t;&t;    DIRINO_COPY_ARCH(from,to,ARCH_NOCONVERT)
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_DIR_SF_PUT_DIRINO)
r_void
id|xfs_dir_sf_put_dirino_arch
c_func
(paren
id|xfs_ino_t
op_star
id|from
comma
id|xfs_dir_ino_t
op_star
id|to
comma
id|xfs_arch_t
id|arch
)paren
suffix:semicolon
r_void
id|xfs_dir_sf_put_dirino
c_func
(paren
id|xfs_ino_t
op_star
id|from
comma
id|xfs_dir_ino_t
op_star
id|to
)paren
suffix:semicolon
DECL|macro|XFS_DIR_SF_PUT_DIRINO_ARCH
mdefine_line|#define XFS_DIR_SF_PUT_DIRINO_ARCH(from,to,arch)    xfs_dir_sf_put_dirino_arch(from, to, arch)
DECL|macro|XFS_DIR_SF_PUT_DIRINO
mdefine_line|#define XFS_DIR_SF_PUT_DIRINO(from,to)&t;&t;    xfs_dir_sf_put_dirino(from, to)
macro_line|#else
DECL|macro|XFS_DIR_SF_PUT_DIRINO_ARCH
mdefine_line|#define XFS_DIR_SF_PUT_DIRINO_ARCH(from,to,arch)    DIRINO_COPY_ARCH(from,to,arch)
DECL|macro|XFS_DIR_SF_PUT_DIRINO
mdefine_line|#define XFS_DIR_SF_PUT_DIRINO(from,to)&t;&t;    DIRINO_COPY_ARCH(from,to,ARCH_NOCONVERT)
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_DIR_SF_ENTSIZE_BYNAME)
r_int
id|xfs_dir_sf_entsize_byname
c_func
(paren
r_int
id|len
)paren
suffix:semicolon
DECL|macro|XFS_DIR_SF_ENTSIZE_BYNAME
mdefine_line|#define XFS_DIR_SF_ENTSIZE_BYNAME(len)&t;&t;xfs_dir_sf_entsize_byname(len)
macro_line|#else
DECL|macro|XFS_DIR_SF_ENTSIZE_BYNAME
mdefine_line|#define XFS_DIR_SF_ENTSIZE_BYNAME(len)&t;&t;/* space a name uses */ &bslash;&n;&t;((uint)sizeof(xfs_dir_sf_entry_t)-1 + (len))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_DIR_SF_ENTSIZE_BYENTRY)
r_int
id|xfs_dir_sf_entsize_byentry
c_func
(paren
id|xfs_dir_sf_entry_t
op_star
id|sfep
)paren
suffix:semicolon
DECL|macro|XFS_DIR_SF_ENTSIZE_BYENTRY
mdefine_line|#define XFS_DIR_SF_ENTSIZE_BYENTRY(sfep)&t;xfs_dir_sf_entsize_byentry(sfep)
macro_line|#else
DECL|macro|XFS_DIR_SF_ENTSIZE_BYENTRY
mdefine_line|#define XFS_DIR_SF_ENTSIZE_BYENTRY(sfep)&t;/* space an entry uses */ &bslash;&n;&t;((uint)sizeof(xfs_dir_sf_entry_t)-1 + (sfep)-&gt;namelen)
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_DIR_SF_NEXTENTRY)
id|xfs_dir_sf_entry_t
op_star
id|xfs_dir_sf_nextentry
c_func
(paren
id|xfs_dir_sf_entry_t
op_star
id|sfep
)paren
suffix:semicolon
DECL|macro|XFS_DIR_SF_NEXTENTRY
mdefine_line|#define XFS_DIR_SF_NEXTENTRY(sfep)&t;&t;xfs_dir_sf_nextentry(sfep)
macro_line|#else
DECL|macro|XFS_DIR_SF_NEXTENTRY
mdefine_line|#define XFS_DIR_SF_NEXTENTRY(sfep)&t;&t;/* next entry in struct */ &bslash;&n;&t;((xfs_dir_sf_entry_t *) &bslash;&n;&t;&t;((char *)(sfep) + XFS_DIR_SF_ENTSIZE_BYENTRY(sfep)))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_DIR_SF_ALLFIT)
r_int
id|xfs_dir_sf_allfit
c_func
(paren
r_int
id|count
comma
r_int
id|totallen
)paren
suffix:semicolon
DECL|macro|XFS_DIR_SF_ALLFIT
mdefine_line|#define XFS_DIR_SF_ALLFIT(count,totallen)&t;&bslash;&n;&t;xfs_dir_sf_allfit(count,totallen)
macro_line|#else
DECL|macro|XFS_DIR_SF_ALLFIT
mdefine_line|#define XFS_DIR_SF_ALLFIT(count,totallen)&t;/* will all entries fit? */ &bslash;&n;&t;((uint)sizeof(xfs_dir_sf_hdr_t) + &bslash;&n;&t;       ((uint)sizeof(xfs_dir_sf_entry_t)-1)*(count) + (totallen))
macro_line|#endif
macro_line|#ifdef XFS_ALL_TRACE
DECL|macro|XFS_DIR_TRACE
mdefine_line|#define XFS_DIR_TRACE
macro_line|#endif
macro_line|#if !defined(DEBUG)
DECL|macro|XFS_DIR_TRACE
macro_line|#undef XFS_DIR_TRACE
macro_line|#endif
multiline_comment|/*&n; * Kernel tracing support for directories.&n; */
r_struct
id|uio
suffix:semicolon
r_struct
id|xfs_inode
suffix:semicolon
r_struct
id|xfs_da_intnode
suffix:semicolon
r_struct
id|xfs_dinode
suffix:semicolon
r_struct
id|xfs_dir_leafblock
suffix:semicolon
r_struct
id|xfs_dir_leaf_entry
suffix:semicolon
DECL|macro|XFS_DIR_TRACE_SIZE
mdefine_line|#define XFS_DIR_TRACE_SIZE&t;4096&t;/* size of global trace buffer */
multiline_comment|/*&n; * Trace record types.&n; */
DECL|macro|XFS_DIR_KTRACE_G_DU
mdefine_line|#define XFS_DIR_KTRACE_G_DU&t;1&t;/* dp, uio */
DECL|macro|XFS_DIR_KTRACE_G_DUB
mdefine_line|#define XFS_DIR_KTRACE_G_DUB&t;2&t;/* dp, uio, bno */
DECL|macro|XFS_DIR_KTRACE_G_DUN
mdefine_line|#define XFS_DIR_KTRACE_G_DUN&t;3&t;/* dp, uio, node */
DECL|macro|XFS_DIR_KTRACE_G_DUL
mdefine_line|#define XFS_DIR_KTRACE_G_DUL&t;4&t;/* dp, uio, leaf */
DECL|macro|XFS_DIR_KTRACE_G_DUE
mdefine_line|#define XFS_DIR_KTRACE_G_DUE&t;5&t;/* dp, uio, leaf entry */
DECL|macro|XFS_DIR_KTRACE_G_DUC
mdefine_line|#define XFS_DIR_KTRACE_G_DUC&t;6&t;/* dp, uio, cookie */
macro_line|#if defined(XFS_DIR_TRACE)
r_void
id|xfs_dir_trace_g_du
c_func
(paren
r_char
op_star
id|where
comma
r_struct
id|xfs_inode
op_star
id|dp
comma
r_struct
id|uio
op_star
id|uio
)paren
suffix:semicolon
r_void
id|xfs_dir_trace_g_dub
c_func
(paren
r_char
op_star
id|where
comma
r_struct
id|xfs_inode
op_star
id|dp
comma
r_struct
id|uio
op_star
id|uio
comma
id|xfs_dablk_t
id|bno
)paren
suffix:semicolon
r_void
id|xfs_dir_trace_g_dun
c_func
(paren
r_char
op_star
id|where
comma
r_struct
id|xfs_inode
op_star
id|dp
comma
r_struct
id|uio
op_star
id|uio
comma
r_struct
id|xfs_da_intnode
op_star
id|node
)paren
suffix:semicolon
r_void
id|xfs_dir_trace_g_dul
c_func
(paren
r_char
op_star
id|where
comma
r_struct
id|xfs_inode
op_star
id|dp
comma
r_struct
id|uio
op_star
id|uio
comma
r_struct
id|xfs_dir_leafblock
op_star
id|leaf
)paren
suffix:semicolon
r_void
id|xfs_dir_trace_g_due
c_func
(paren
r_char
op_star
id|where
comma
r_struct
id|xfs_inode
op_star
id|dp
comma
r_struct
id|uio
op_star
id|uio
comma
r_struct
id|xfs_dir_leaf_entry
op_star
id|entry
)paren
suffix:semicolon
r_void
id|xfs_dir_trace_g_duc
c_func
(paren
r_char
op_star
id|where
comma
r_struct
id|xfs_inode
op_star
id|dp
comma
r_struct
id|uio
op_star
id|uio
comma
id|xfs_off_t
id|cookie
)paren
suffix:semicolon
r_void
id|xfs_dir_trace_enter
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
id|a0
comma
id|__psunsigned_t
id|a1
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
)paren
suffix:semicolon
macro_line|#else
DECL|macro|xfs_dir_trace_g_du
mdefine_line|#define xfs_dir_trace_g_du(w,d,u)
DECL|macro|xfs_dir_trace_g_dub
mdefine_line|#define xfs_dir_trace_g_dub(w,d,u,b)
DECL|macro|xfs_dir_trace_g_dun
mdefine_line|#define xfs_dir_trace_g_dun(w,d,u,n)
DECL|macro|xfs_dir_trace_g_dul
mdefine_line|#define xfs_dir_trace_g_dul(w,d,u,l)
DECL|macro|xfs_dir_trace_g_due
mdefine_line|#define xfs_dir_trace_g_due(w,d,u,e)
DECL|macro|xfs_dir_trace_g_duc
mdefine_line|#define xfs_dir_trace_g_duc(w,d,u,c)
macro_line|#endif /* DEBUG */
macro_line|#endif&t;/* __XFS_DIR_SF_H__ */
eof
