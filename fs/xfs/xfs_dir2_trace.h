multiline_comment|/*&n; * Copyright (c) 2000 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.&t; Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#ifndef __XFS_DIR2_TRACE_H__
DECL|macro|__XFS_DIR2_TRACE_H__
mdefine_line|#define __XFS_DIR2_TRACE_H__
multiline_comment|/*&n; * Tracing for xfs v2 directories.&n; */
r_struct
id|ktrace
suffix:semicolon
r_struct
id|xfs_dabuf
suffix:semicolon
r_struct
id|xfs_da_args
suffix:semicolon
macro_line|#ifdef XFS_ALL_TRACE
DECL|macro|XFS_DIR2_TRACE
mdefine_line|#define XFS_DIR2_TRACE
macro_line|#endif&t;/* XFS_ALL_TRACE */
macro_line|#if !defined(DEBUG)
DECL|macro|XFS_DIR2_TRACE
macro_line|#undef XFS_DIR2_TRACE
macro_line|#endif&t;/* !DEBUG */
DECL|macro|XFS_DIR2_GTRACE_SIZE
mdefine_line|#define XFS_DIR2_GTRACE_SIZE&t;&t;4096&t;/* global buffer */
DECL|macro|XFS_DIR2_KTRACE_SIZE
mdefine_line|#define XFS_DIR2_KTRACE_SIZE&t;&t;32&t;/* per-inode buffer */
DECL|macro|XFS_DIR2_KTRACE_ARGS
mdefine_line|#define XFS_DIR2_KTRACE_ARGS&t;&t;1&t;/* args only */
DECL|macro|XFS_DIR2_KTRACE_ARGS_B
mdefine_line|#define XFS_DIR2_KTRACE_ARGS_B&t;&t;2&t;/* args + buffer */
DECL|macro|XFS_DIR2_KTRACE_ARGS_BB
mdefine_line|#define XFS_DIR2_KTRACE_ARGS_BB&t;&t;3&t;/* args + 2 buffers */
DECL|macro|XFS_DIR2_KTRACE_ARGS_DB
mdefine_line|#define XFS_DIR2_KTRACE_ARGS_DB&t;&t;4&t;/* args, db, buffer */
DECL|macro|XFS_DIR2_KTRACE_ARGS_I
mdefine_line|#define XFS_DIR2_KTRACE_ARGS_I&t;&t;5&t;/* args, inum */
DECL|macro|XFS_DIR2_KTRACE_ARGS_S
mdefine_line|#define XFS_DIR2_KTRACE_ARGS_S&t;&t;6&t;/* args, int */
DECL|macro|XFS_DIR2_KTRACE_ARGS_SB
mdefine_line|#define XFS_DIR2_KTRACE_ARGS_SB&t;&t;7&t;/* args, int, buffer */
DECL|macro|XFS_DIR2_KTRACE_ARGS_BIBII
mdefine_line|#define XFS_DIR2_KTRACE_ARGS_BIBII&t;8&t;/* args, buf/int/buf/int/int */
macro_line|#ifdef XFS_DIR2_TRACE
r_void
id|xfs_dir2_trace_args
c_func
(paren
r_char
op_star
id|where
comma
r_struct
id|xfs_da_args
op_star
id|args
)paren
suffix:semicolon
r_void
id|xfs_dir2_trace_args_b
c_func
(paren
r_char
op_star
id|where
comma
r_struct
id|xfs_da_args
op_star
id|args
comma
r_struct
id|xfs_dabuf
op_star
id|bp
)paren
suffix:semicolon
r_void
id|xfs_dir2_trace_args_bb
c_func
(paren
r_char
op_star
id|where
comma
r_struct
id|xfs_da_args
op_star
id|args
comma
r_struct
id|xfs_dabuf
op_star
id|lbp
comma
r_struct
id|xfs_dabuf
op_star
id|dbp
)paren
suffix:semicolon
r_void
id|xfs_dir2_trace_args_bibii
c_func
(paren
r_char
op_star
id|where
comma
r_struct
id|xfs_da_args
op_star
id|args
comma
r_struct
id|xfs_dabuf
op_star
id|bs
comma
r_int
id|ss
comma
r_struct
id|xfs_dabuf
op_star
id|bd
comma
r_int
id|sd
comma
r_int
id|c
)paren
suffix:semicolon
r_void
id|xfs_dir2_trace_args_db
c_func
(paren
r_char
op_star
id|where
comma
r_struct
id|xfs_da_args
op_star
id|args
comma
id|xfs_dir2_db_t
id|db
comma
r_struct
id|xfs_dabuf
op_star
id|bp
)paren
suffix:semicolon
r_void
id|xfs_dir2_trace_args_i
c_func
(paren
r_char
op_star
id|where
comma
r_struct
id|xfs_da_args
op_star
id|args
comma
id|xfs_ino_t
id|i
)paren
suffix:semicolon
r_void
id|xfs_dir2_trace_args_s
c_func
(paren
r_char
op_star
id|where
comma
r_struct
id|xfs_da_args
op_star
id|args
comma
r_int
id|s
)paren
suffix:semicolon
r_void
id|xfs_dir2_trace_args_sb
c_func
(paren
r_char
op_star
id|where
comma
r_struct
id|xfs_da_args
op_star
id|args
comma
r_int
id|s
comma
r_struct
id|xfs_dabuf
op_star
id|bp
)paren
suffix:semicolon
macro_line|#else&t;/* XFS_DIR2_TRACE */
DECL|macro|xfs_dir2_trace_args
mdefine_line|#define xfs_dir2_trace_args(where, args)
DECL|macro|xfs_dir2_trace_args_b
mdefine_line|#define xfs_dir2_trace_args_b(where, args, bp)
DECL|macro|xfs_dir2_trace_args_bb
mdefine_line|#define xfs_dir2_trace_args_bb(where, args, lbp, dbp)
DECL|macro|xfs_dir2_trace_args_bibii
mdefine_line|#define xfs_dir2_trace_args_bibii(where, args, bs, ss, bd, sd, c)
DECL|macro|xfs_dir2_trace_args_db
mdefine_line|#define xfs_dir2_trace_args_db(where, args, db, bp)
DECL|macro|xfs_dir2_trace_args_i
mdefine_line|#define xfs_dir2_trace_args_i(where, args, i)
DECL|macro|xfs_dir2_trace_args_s
mdefine_line|#define xfs_dir2_trace_args_s(where, args, s)
DECL|macro|xfs_dir2_trace_args_sb
mdefine_line|#define xfs_dir2_trace_args_sb(where, args, s, bp)
macro_line|#endif&t;/* XFS_DIR2_TRACE */
r_extern
r_struct
id|ktrace
op_star
id|xfs_dir2_trace_buf
suffix:semicolon
macro_line|#endif&t;/* __XFS_DIR2_TRACE_H__ */
eof
