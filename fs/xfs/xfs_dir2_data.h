multiline_comment|/*&n; * Copyright (c) 2000 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.&t; Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#ifndef __XFS_DIR2_DATA_H__
DECL|macro|__XFS_DIR2_DATA_H__
mdefine_line|#define __XFS_DIR2_DATA_H__
multiline_comment|/*&n; * Directory format 2, data block structures.&n; */
r_struct
id|xfs_dabuf
suffix:semicolon
r_struct
id|xfs_da_args
suffix:semicolon
r_struct
id|xfs_inode
suffix:semicolon
r_struct
id|xfs_trans
suffix:semicolon
multiline_comment|/*&n; * Constants.&n; */
DECL|macro|XFS_DIR2_DATA_MAGIC
mdefine_line|#define XFS_DIR2_DATA_MAGIC&t;0x58443244&t;/* XD2D: for multiblock dirs */
DECL|macro|XFS_DIR2_DATA_ALIGN_LOG
mdefine_line|#define XFS_DIR2_DATA_ALIGN_LOG 3&t;&t;/* i.e., 8 bytes */
DECL|macro|XFS_DIR2_DATA_ALIGN
mdefine_line|#define XFS_DIR2_DATA_ALIGN&t;(1 &lt;&lt; XFS_DIR2_DATA_ALIGN_LOG)
DECL|macro|XFS_DIR2_DATA_FREE_TAG
mdefine_line|#define XFS_DIR2_DATA_FREE_TAG&t;0xffff
DECL|macro|XFS_DIR2_DATA_FD_COUNT
mdefine_line|#define XFS_DIR2_DATA_FD_COUNT&t;3
multiline_comment|/*&n; * Directory address space divided into sections,&n; * spaces separated by 32gb.&n; */
DECL|macro|XFS_DIR2_SPACE_SIZE
mdefine_line|#define XFS_DIR2_SPACE_SIZE&t;(1ULL &lt;&lt; (32 + XFS_DIR2_DATA_ALIGN_LOG))
DECL|macro|XFS_DIR2_DATA_SPACE
mdefine_line|#define XFS_DIR2_DATA_SPACE&t;0
DECL|macro|XFS_DIR2_DATA_OFFSET
mdefine_line|#define XFS_DIR2_DATA_OFFSET&t;(XFS_DIR2_DATA_SPACE * XFS_DIR2_SPACE_SIZE)
DECL|macro|XFS_DIR2_DATA_FIRSTDB
mdefine_line|#define XFS_DIR2_DATA_FIRSTDB(mp)&t;&bslash;&n;&t;XFS_DIR2_BYTE_TO_DB(mp, XFS_DIR2_DATA_OFFSET)
multiline_comment|/*&n; * Offsets of . and .. in data space (always block 0)&n; */
DECL|macro|XFS_DIR2_DATA_DOT_OFFSET
mdefine_line|#define XFS_DIR2_DATA_DOT_OFFSET&t;&bslash;&n;&t;((xfs_dir2_data_aoff_t)sizeof(xfs_dir2_data_hdr_t))
DECL|macro|XFS_DIR2_DATA_DOTDOT_OFFSET
mdefine_line|#define XFS_DIR2_DATA_DOTDOT_OFFSET&t;&bslash;&n;&t;(XFS_DIR2_DATA_DOT_OFFSET + XFS_DIR2_DATA_ENTSIZE(1))
DECL|macro|XFS_DIR2_DATA_FIRST_OFFSET
mdefine_line|#define XFS_DIR2_DATA_FIRST_OFFSET&t;&t;&bslash;&n;&t;(XFS_DIR2_DATA_DOTDOT_OFFSET + XFS_DIR2_DATA_ENTSIZE(2))
multiline_comment|/*&n; * Structures.&n; */
multiline_comment|/*&n; * Describe a free area in the data block.&n; * The freespace will be formatted as a xfs_dir2_data_unused_t.&n; */
DECL|struct|xfs_dir2_data_free
r_typedef
r_struct
id|xfs_dir2_data_free
(brace
DECL|member|offset
id|xfs_dir2_data_off_t
id|offset
suffix:semicolon
multiline_comment|/* start of freespace */
DECL|member|length
id|xfs_dir2_data_off_t
id|length
suffix:semicolon
multiline_comment|/* length of freespace */
DECL|typedef|xfs_dir2_data_free_t
)brace
id|xfs_dir2_data_free_t
suffix:semicolon
multiline_comment|/*&n; * Header for the data blocks.&n; * Always at the beginning of a directory-sized block.&n; * The code knows that XFS_DIR2_DATA_FD_COUNT is 3.&n; */
DECL|struct|xfs_dir2_data_hdr
r_typedef
r_struct
id|xfs_dir2_data_hdr
(brace
DECL|member|magic
id|__uint32_t
id|magic
suffix:semicolon
multiline_comment|/* XFS_DIR2_DATA_MAGIC */
multiline_comment|/* or XFS_DIR2_BLOCK_MAGIC */
DECL|member|bestfree
id|xfs_dir2_data_free_t
id|bestfree
(braket
id|XFS_DIR2_DATA_FD_COUNT
)braket
suffix:semicolon
DECL|typedef|xfs_dir2_data_hdr_t
)brace
id|xfs_dir2_data_hdr_t
suffix:semicolon
multiline_comment|/*&n; * Active entry in a data block.  Aligned to 8 bytes.&n; * Tag appears as the last 2 bytes.&n; */
DECL|struct|xfs_dir2_data_entry
r_typedef
r_struct
id|xfs_dir2_data_entry
(brace
DECL|member|inumber
id|xfs_ino_t
id|inumber
suffix:semicolon
multiline_comment|/* inode number */
DECL|member|namelen
id|__uint8_t
id|namelen
suffix:semicolon
multiline_comment|/* name length */
DECL|member|name
id|__uint8_t
id|name
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* name bytes, no null */
multiline_comment|/* variable offset */
DECL|member|tag
id|xfs_dir2_data_off_t
id|tag
suffix:semicolon
multiline_comment|/* starting offset of us */
DECL|typedef|xfs_dir2_data_entry_t
)brace
id|xfs_dir2_data_entry_t
suffix:semicolon
multiline_comment|/*&n; * Unused entry in a data block.  Aligned to 8 bytes.&n; * Tag appears as the last 2 bytes.&n; */
DECL|struct|xfs_dir2_data_unused
r_typedef
r_struct
id|xfs_dir2_data_unused
(brace
DECL|member|freetag
id|__uint16_t
id|freetag
suffix:semicolon
multiline_comment|/* XFS_DIR2_DATA_FREE_TAG */
DECL|member|length
id|xfs_dir2_data_off_t
id|length
suffix:semicolon
multiline_comment|/* total free length */
multiline_comment|/* variable offset */
DECL|member|tag
id|xfs_dir2_data_off_t
id|tag
suffix:semicolon
multiline_comment|/* starting offset of us */
DECL|typedef|xfs_dir2_data_unused_t
)brace
id|xfs_dir2_data_unused_t
suffix:semicolon
r_typedef
r_union
(brace
DECL|member|entry
id|xfs_dir2_data_entry_t
id|entry
suffix:semicolon
DECL|member|unused
id|xfs_dir2_data_unused_t
id|unused
suffix:semicolon
DECL|typedef|xfs_dir2_data_union_t
)brace
id|xfs_dir2_data_union_t
suffix:semicolon
multiline_comment|/*&n; * Generic data block structure, for xfs_db.&n; */
DECL|struct|xfs_dir2_data
r_typedef
r_struct
id|xfs_dir2_data
(brace
DECL|member|hdr
id|xfs_dir2_data_hdr_t
id|hdr
suffix:semicolon
multiline_comment|/* magic XFS_DIR2_DATA_MAGIC */
DECL|member|u
id|xfs_dir2_data_union_t
id|u
(braket
l_int|1
)braket
suffix:semicolon
DECL|typedef|xfs_dir2_data_t
)brace
id|xfs_dir2_data_t
suffix:semicolon
multiline_comment|/*&n; * Macros.&n; */
multiline_comment|/*&n; * Size of a data entry.&n; */
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_DIR2_DATA_ENTSIZE)
r_int
id|xfs_dir2_data_entsize
c_func
(paren
r_int
id|n
)paren
suffix:semicolon
DECL|macro|XFS_DIR2_DATA_ENTSIZE
mdefine_line|#define XFS_DIR2_DATA_ENTSIZE(n)&t;xfs_dir2_data_entsize(n)
macro_line|#else
DECL|macro|XFS_DIR2_DATA_ENTSIZE
mdefine_line|#define XFS_DIR2_DATA_ENTSIZE(n)&t;&bslash;&n;&t;((int)(roundup(offsetof(xfs_dir2_data_entry_t, name[0]) + (n) + &bslash;&n;&t;&t; (uint)sizeof(xfs_dir2_data_off_t), XFS_DIR2_DATA_ALIGN)))
macro_line|#endif
multiline_comment|/*&n; * Pointer to an entry&squot;s tag word.&n; */
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_DIR2_DATA_ENTRY_TAG_P)
id|xfs_dir2_data_off_t
op_star
id|xfs_dir2_data_entry_tag_p
c_func
(paren
id|xfs_dir2_data_entry_t
op_star
id|dep
)paren
suffix:semicolon
DECL|macro|XFS_DIR2_DATA_ENTRY_TAG_P
mdefine_line|#define XFS_DIR2_DATA_ENTRY_TAG_P(dep)&t;xfs_dir2_data_entry_tag_p(dep)
macro_line|#else
DECL|macro|XFS_DIR2_DATA_ENTRY_TAG_P
mdefine_line|#define XFS_DIR2_DATA_ENTRY_TAG_P(dep)&t;&bslash;&n;&t;((xfs_dir2_data_off_t *)&bslash;&n;&t; ((char *)(dep) + XFS_DIR2_DATA_ENTSIZE((dep)-&gt;namelen) - &bslash;&n;&t;  (uint)sizeof(xfs_dir2_data_off_t)))
macro_line|#endif
multiline_comment|/*&n; * Pointer to a freespace&squot;s tag word.&n; */
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_DIR2_DATA_UNUSED_TAG_P)
id|xfs_dir2_data_off_t
op_star
id|xfs_dir2_data_unused_tag_p_arch
c_func
(paren
id|xfs_dir2_data_unused_t
op_star
id|dup
comma
id|xfs_arch_t
id|arch
)paren
suffix:semicolon
DECL|macro|XFS_DIR2_DATA_UNUSED_TAG_P_ARCH
mdefine_line|#define XFS_DIR2_DATA_UNUSED_TAG_P_ARCH(dup,arch) &bslash;&n;&t;xfs_dir2_data_unused_tag_p_arch(dup,arch)
macro_line|#else
DECL|macro|XFS_DIR2_DATA_UNUSED_TAG_P_ARCH
mdefine_line|#define XFS_DIR2_DATA_UNUSED_TAG_P_ARCH(dup,arch)&t;&bslash;&n;&t;((xfs_dir2_data_off_t *)&bslash;&n;&t; ((char *)(dup) + INT_GET((dup)-&gt;length, arch) &bslash;&n;&t;&t;&t;- (uint)sizeof(xfs_dir2_data_off_t)))
macro_line|#endif
multiline_comment|/*&n; * Function declarations.&n; */
macro_line|#ifdef DEBUG
r_extern
r_void
id|xfs_dir2_data_check
c_func
(paren
r_struct
id|xfs_inode
op_star
id|dp
comma
r_struct
id|xfs_dabuf
op_star
id|bp
)paren
suffix:semicolon
macro_line|#else
DECL|macro|xfs_dir2_data_check
mdefine_line|#define xfs_dir2_data_check(dp,bp)
macro_line|#endif
r_extern
id|xfs_dir2_data_free_t
op_star
id|xfs_dir2_data_freefind
c_func
(paren
id|xfs_dir2_data_t
op_star
id|d
comma
id|xfs_dir2_data_unused_t
op_star
id|dup
)paren
suffix:semicolon
r_extern
id|xfs_dir2_data_free_t
op_star
id|xfs_dir2_data_freeinsert
c_func
(paren
id|xfs_dir2_data_t
op_star
id|d
comma
id|xfs_dir2_data_unused_t
op_star
id|dup
comma
r_int
op_star
id|loghead
)paren
suffix:semicolon
r_extern
r_void
id|xfs_dir2_data_freeremove
c_func
(paren
id|xfs_dir2_data_t
op_star
id|d
comma
id|xfs_dir2_data_free_t
op_star
id|dfp
comma
r_int
op_star
id|loghead
)paren
suffix:semicolon
r_extern
r_void
id|xfs_dir2_data_freescan
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
comma
id|xfs_dir2_data_t
op_star
id|d
comma
r_int
op_star
id|loghead
comma
r_char
op_star
id|aendp
)paren
suffix:semicolon
r_extern
r_int
id|xfs_dir2_data_init
c_func
(paren
r_struct
id|xfs_da_args
op_star
id|args
comma
id|xfs_dir2_db_t
id|blkno
comma
r_struct
id|xfs_dabuf
op_star
op_star
id|bpp
)paren
suffix:semicolon
r_extern
r_void
id|xfs_dir2_data_log_entry
c_func
(paren
r_struct
id|xfs_trans
op_star
id|tp
comma
r_struct
id|xfs_dabuf
op_star
id|bp
comma
id|xfs_dir2_data_entry_t
op_star
id|dep
)paren
suffix:semicolon
r_extern
r_void
id|xfs_dir2_data_log_header
c_func
(paren
r_struct
id|xfs_trans
op_star
id|tp
comma
r_struct
id|xfs_dabuf
op_star
id|bp
)paren
suffix:semicolon
r_extern
r_void
id|xfs_dir2_data_log_unused
c_func
(paren
r_struct
id|xfs_trans
op_star
id|tp
comma
r_struct
id|xfs_dabuf
op_star
id|bp
comma
id|xfs_dir2_data_unused_t
op_star
id|dup
)paren
suffix:semicolon
r_extern
r_void
id|xfs_dir2_data_make_free
c_func
(paren
r_struct
id|xfs_trans
op_star
id|tp
comma
r_struct
id|xfs_dabuf
op_star
id|bp
comma
id|xfs_dir2_data_aoff_t
id|offset
comma
id|xfs_dir2_data_aoff_t
id|len
comma
r_int
op_star
id|needlogp
comma
r_int
op_star
id|needscanp
)paren
suffix:semicolon
r_extern
r_void
id|xfs_dir2_data_use_free
c_func
(paren
r_struct
id|xfs_trans
op_star
id|tp
comma
r_struct
id|xfs_dabuf
op_star
id|bp
comma
id|xfs_dir2_data_unused_t
op_star
id|dup
comma
id|xfs_dir2_data_aoff_t
id|offset
comma
id|xfs_dir2_data_aoff_t
id|len
comma
r_int
op_star
id|needlogp
comma
r_int
op_star
id|needscanp
)paren
suffix:semicolon
macro_line|#endif&t;/* __XFS_DIR2_DATA_H__ */
eof
