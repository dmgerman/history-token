multiline_comment|/*&n; * Copyright (c) 2000-2002 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.&t; Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#ifndef __XFS_ALLOC_H__
DECL|macro|__XFS_ALLOC_H__
mdefine_line|#define __XFS_ALLOC_H__
r_struct
id|xfs_buf
suffix:semicolon
r_struct
id|xfs_mount
suffix:semicolon
r_struct
id|xfs_perag
suffix:semicolon
r_struct
id|xfs_trans
suffix:semicolon
multiline_comment|/*&n; * Freespace allocation types.&t;Argument to xfs_alloc_[v]extent.&n; */
DECL|enum|xfs_alloctype
r_typedef
r_enum
id|xfs_alloctype
(brace
DECL|enumerator|XFS_ALLOCTYPE_ANY_AG
id|XFS_ALLOCTYPE_ANY_AG
comma
multiline_comment|/* allocate anywhere, use rotor */
DECL|enumerator|XFS_ALLOCTYPE_FIRST_AG
id|XFS_ALLOCTYPE_FIRST_AG
comma
multiline_comment|/* ... start at ag 0 */
DECL|enumerator|XFS_ALLOCTYPE_START_AG
id|XFS_ALLOCTYPE_START_AG
comma
multiline_comment|/* anywhere, start in this a.g. */
DECL|enumerator|XFS_ALLOCTYPE_THIS_AG
id|XFS_ALLOCTYPE_THIS_AG
comma
multiline_comment|/* anywhere in this a.g. */
DECL|enumerator|XFS_ALLOCTYPE_START_BNO
id|XFS_ALLOCTYPE_START_BNO
comma
multiline_comment|/* near this block else anywhere */
DECL|enumerator|XFS_ALLOCTYPE_NEAR_BNO
id|XFS_ALLOCTYPE_NEAR_BNO
comma
multiline_comment|/* in this a.g. and near this block */
DECL|enumerator|XFS_ALLOCTYPE_THIS_BNO
id|XFS_ALLOCTYPE_THIS_BNO
multiline_comment|/* at exactly this block */
DECL|typedef|xfs_alloctype_t
)brace
id|xfs_alloctype_t
suffix:semicolon
multiline_comment|/*&n; * Flags for xfs_alloc_fix_freelist.&n; */
DECL|macro|XFS_ALLOC_FLAG_TRYLOCK
mdefine_line|#define XFS_ALLOC_FLAG_TRYLOCK&t;0x00000001  /* use trylock for buffer locking */
multiline_comment|/*&n; * Argument structure for xfs_alloc routines.&n; * This is turned into a structure to avoid having 20 arguments passed&n; * down several levels of the stack.&n; */
DECL|struct|xfs_alloc_arg
r_typedef
r_struct
id|xfs_alloc_arg
(brace
DECL|member|tp
r_struct
id|xfs_trans
op_star
id|tp
suffix:semicolon
multiline_comment|/* transaction pointer */
DECL|member|mp
r_struct
id|xfs_mount
op_star
id|mp
suffix:semicolon
multiline_comment|/* file system mount point */
DECL|member|agbp
r_struct
id|xfs_buf
op_star
id|agbp
suffix:semicolon
multiline_comment|/* buffer for a.g. freelist header */
DECL|member|pag
r_struct
id|xfs_perag
op_star
id|pag
suffix:semicolon
multiline_comment|/* per-ag struct for this agno */
DECL|member|fsbno
id|xfs_fsblock_t
id|fsbno
suffix:semicolon
multiline_comment|/* file system block number */
DECL|member|agno
id|xfs_agnumber_t
id|agno
suffix:semicolon
multiline_comment|/* allocation group number */
DECL|member|agbno
id|xfs_agblock_t
id|agbno
suffix:semicolon
multiline_comment|/* allocation group-relative block # */
DECL|member|minlen
id|xfs_extlen_t
id|minlen
suffix:semicolon
multiline_comment|/* minimum size of extent */
DECL|member|maxlen
id|xfs_extlen_t
id|maxlen
suffix:semicolon
multiline_comment|/* maximum size of extent */
DECL|member|mod
id|xfs_extlen_t
id|mod
suffix:semicolon
multiline_comment|/* mod value for extent size */
DECL|member|prod
id|xfs_extlen_t
id|prod
suffix:semicolon
multiline_comment|/* prod value for extent size */
DECL|member|minleft
id|xfs_extlen_t
id|minleft
suffix:semicolon
multiline_comment|/* min blocks must be left after us */
DECL|member|total
id|xfs_extlen_t
id|total
suffix:semicolon
multiline_comment|/* total blocks needed in xaction */
DECL|member|alignment
id|xfs_extlen_t
id|alignment
suffix:semicolon
multiline_comment|/* align answer to multiple of this */
DECL|member|minalignslop
id|xfs_extlen_t
id|minalignslop
suffix:semicolon
multiline_comment|/* slop for minlen+alignment calcs */
DECL|member|len
id|xfs_extlen_t
id|len
suffix:semicolon
multiline_comment|/* output: actual size of extent */
DECL|member|type
id|xfs_alloctype_t
id|type
suffix:semicolon
multiline_comment|/* allocation type XFS_ALLOCTYPE_... */
DECL|member|otype
id|xfs_alloctype_t
id|otype
suffix:semicolon
multiline_comment|/* original allocation type */
DECL|member|wasdel
r_char
id|wasdel
suffix:semicolon
multiline_comment|/* set if allocation was prev delayed */
DECL|member|wasfromfl
r_char
id|wasfromfl
suffix:semicolon
multiline_comment|/* set if allocation is from freelist */
DECL|member|isfl
r_char
id|isfl
suffix:semicolon
multiline_comment|/* set if is freelist blocks - !actg */
DECL|member|userdata
r_char
id|userdata
suffix:semicolon
multiline_comment|/* set if this is user data */
DECL|typedef|xfs_alloc_arg_t
)brace
id|xfs_alloc_arg_t
suffix:semicolon
multiline_comment|/*&n; * Defines for userdata&n; */
DECL|macro|XFS_ALLOC_USERDATA
mdefine_line|#define XFS_ALLOC_USERDATA&t;&t;1&t;/* allocation is for user data*/
DECL|macro|XFS_ALLOC_INITIAL_USER_DATA
mdefine_line|#define XFS_ALLOC_INITIAL_USER_DATA&t;2&t;/* special case start of file */
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * Types for alloc tracing.&n; */
DECL|macro|XFS_ALLOC_KTRACE_ALLOC
mdefine_line|#define XFS_ALLOC_KTRACE_ALLOC&t;1
DECL|macro|XFS_ALLOC_KTRACE_FREE
mdefine_line|#define XFS_ALLOC_KTRACE_FREE&t;2
DECL|macro|XFS_ALLOC_KTRACE_MODAGF
mdefine_line|#define XFS_ALLOC_KTRACE_MODAGF 3
DECL|macro|XFS_ALLOC_KTRACE_BUSY
mdefine_line|#define XFS_ALLOC_KTRACE_BUSY&t;4
DECL|macro|XFS_ALLOC_KTRACE_UNBUSY
mdefine_line|#define XFS_ALLOC_KTRACE_UNBUSY 5
DECL|macro|XFS_ALLOC_KTRACE_BUSYSEARCH
mdefine_line|#define XFS_ALLOC_KTRACE_BUSYSEARCH&t;6
multiline_comment|/*&n; * Allocation tracing buffer size.&n; */
DECL|macro|XFS_ALLOC_TRACE_SIZE
mdefine_line|#define XFS_ALLOC_TRACE_SIZE&t;4096
macro_line|#ifdef&t;XFS_ALL_TRACE
DECL|macro|XFS_ALLOC_TRACE
mdefine_line|#define XFS_ALLOC_TRACE
macro_line|#endif
macro_line|#if !defined(DEBUG)
DECL|macro|XFS_ALLOC_TRACE
macro_line|#undef&t;XFS_ALLOC_TRACE
macro_line|#endif
multiline_comment|/*&n; * Prototypes for visible xfs_alloc.c routines&n; */
multiline_comment|/*&n; * Compute and fill in value of m_ag_maxlevels.&n; */
r_void
id|xfs_alloc_compute_maxlevels
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
)paren
suffix:semicolon
multiline_comment|/* file system mount structure */
multiline_comment|/*&n; * Decide whether to use this allocation group for this allocation.&n; * If so, fix up the btree freelist&squot;s size.&n; * This is external so mkfs can call it, too.&n; */
r_int
multiline_comment|/* error */
id|xfs_alloc_fix_freelist
c_func
(paren
id|xfs_alloc_arg_t
op_star
id|args
comma
multiline_comment|/* allocation argument structure */
r_int
id|flags
)paren
suffix:semicolon
multiline_comment|/* XFS_ALLOC_FLAG_... */
multiline_comment|/*&n; * Get a block from the freelist.&n; * Returns with the buffer for the block gotten.&n; */
r_int
multiline_comment|/* error */
id|xfs_alloc_get_freelist
c_func
(paren
r_struct
id|xfs_trans
op_star
id|tp
comma
multiline_comment|/* transaction pointer */
r_struct
id|xfs_buf
op_star
id|agbp
comma
multiline_comment|/* buffer containing the agf structure */
id|xfs_agblock_t
op_star
id|bnop
)paren
suffix:semicolon
multiline_comment|/* block address retrieved from freelist */
multiline_comment|/*&n; * Log the given fields from the agf structure.&n; */
r_void
id|xfs_alloc_log_agf
c_func
(paren
r_struct
id|xfs_trans
op_star
id|tp
comma
multiline_comment|/* transaction pointer */
r_struct
id|xfs_buf
op_star
id|bp
comma
multiline_comment|/* buffer for a.g. freelist header */
r_int
id|fields
)paren
suffix:semicolon
multiline_comment|/* mask of fields to be logged (XFS_AGF_...) */
multiline_comment|/*&n; * Interface for inode allocation to force the pag data to be initialized.&n; */
r_int
multiline_comment|/* error */
id|xfs_alloc_pagf_init
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
comma
multiline_comment|/* file system mount structure */
r_struct
id|xfs_trans
op_star
id|tp
comma
multiline_comment|/* transaction pointer */
id|xfs_agnumber_t
id|agno
comma
multiline_comment|/* allocation group number */
r_int
id|flags
)paren
suffix:semicolon
multiline_comment|/* XFS_ALLOC_FLAGS_... */
multiline_comment|/*&n; * Put the block on the freelist for the allocation group.&n; */
r_int
multiline_comment|/* error */
id|xfs_alloc_put_freelist
c_func
(paren
r_struct
id|xfs_trans
op_star
id|tp
comma
multiline_comment|/* transaction pointer */
r_struct
id|xfs_buf
op_star
id|agbp
comma
multiline_comment|/* buffer for a.g. freelist header */
r_struct
id|xfs_buf
op_star
id|agflbp
comma
multiline_comment|/* buffer for a.g. free block array */
id|xfs_agblock_t
id|bno
)paren
suffix:semicolon
multiline_comment|/* block being freed */
multiline_comment|/*&n; * Read in the allocation group header (free/alloc section).&n; */
r_int
multiline_comment|/* error  */
id|xfs_alloc_read_agf
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
comma
multiline_comment|/* mount point structure */
r_struct
id|xfs_trans
op_star
id|tp
comma
multiline_comment|/* transaction pointer */
id|xfs_agnumber_t
id|agno
comma
multiline_comment|/* allocation group number */
r_int
id|flags
comma
multiline_comment|/* XFS_ALLOC_FLAG_... */
r_struct
id|xfs_buf
op_star
op_star
id|bpp
)paren
suffix:semicolon
multiline_comment|/* buffer for the ag freelist header */
multiline_comment|/*&n; * Allocate an extent (variable-size).&n; */
r_int
multiline_comment|/* error */
id|xfs_alloc_vextent
c_func
(paren
id|xfs_alloc_arg_t
op_star
id|args
)paren
suffix:semicolon
multiline_comment|/* allocation argument structure */
multiline_comment|/*&n; * Free an extent.&n; */
r_int
multiline_comment|/* error */
id|xfs_free_extent
c_func
(paren
r_struct
id|xfs_trans
op_star
id|tp
comma
multiline_comment|/* transaction pointer */
id|xfs_fsblock_t
id|bno
comma
multiline_comment|/* starting block number of extent */
id|xfs_extlen_t
id|len
)paren
suffix:semicolon
multiline_comment|/* length of extent */
r_void
id|xfs_alloc_mark_busy
c_func
(paren
id|xfs_trans_t
op_star
id|tp
comma
id|xfs_agnumber_t
id|agno
comma
id|xfs_agblock_t
id|bno
comma
id|xfs_extlen_t
id|len
)paren
suffix:semicolon
r_void
id|xfs_alloc_clear_busy
c_func
(paren
id|xfs_trans_t
op_star
id|tp
comma
id|xfs_agnumber_t
id|ag
comma
r_int
id|idx
)paren
suffix:semicolon
macro_line|#endif&t;/* __KERNEL__ */
macro_line|#endif&t;/* __XFS_ALLOC_H__ */
eof
