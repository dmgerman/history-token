multiline_comment|/*&n; * Copyright (c) 2000, 2002 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.&t; Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#ifndef __XFS_BIT_H__
DECL|macro|__XFS_BIT_H__
mdefine_line|#define __XFS_BIT_H__
multiline_comment|/*&n; * XFS bit manipulation routines.&n; */
multiline_comment|/*&n; * masks with n high/low bits set, 32-bit values &amp; 64-bit values&n; */
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_MASK32HI)
id|__uint32_t
id|xfs_mask32hi
c_func
(paren
r_int
id|n
)paren
suffix:semicolon
DECL|macro|XFS_MASK32HI
mdefine_line|#define XFS_MASK32HI(n)&t;&t;xfs_mask32hi(n)
macro_line|#else
DECL|macro|XFS_MASK32HI
mdefine_line|#define XFS_MASK32HI(n)&t;&t;((__uint32_t)-1 &lt;&lt; (32 - (n)))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_MASK64HI)
id|__uint64_t
id|xfs_mask64hi
c_func
(paren
r_int
id|n
)paren
suffix:semicolon
DECL|macro|XFS_MASK64HI
mdefine_line|#define XFS_MASK64HI(n)&t;&t;xfs_mask64hi(n)
macro_line|#else
DECL|macro|XFS_MASK64HI
mdefine_line|#define XFS_MASK64HI(n)&t;&t;((__uint64_t)-1 &lt;&lt; (64 - (n)))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_MASK32LO)
id|__uint32_t
id|xfs_mask32lo
c_func
(paren
r_int
id|n
)paren
suffix:semicolon
DECL|macro|XFS_MASK32LO
mdefine_line|#define XFS_MASK32LO(n)&t;&t;xfs_mask32lo(n)
macro_line|#else
DECL|macro|XFS_MASK32LO
mdefine_line|#define XFS_MASK32LO(n)&t;&t;(((__uint32_t)1 &lt;&lt; (n)) - 1)
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_MASK64LO)
id|__uint64_t
id|xfs_mask64lo
c_func
(paren
r_int
id|n
)paren
suffix:semicolon
DECL|macro|XFS_MASK64LO
mdefine_line|#define XFS_MASK64LO(n)&t;&t;xfs_mask64lo(n)
macro_line|#else
DECL|macro|XFS_MASK64LO
mdefine_line|#define XFS_MASK64LO(n)&t;&t;(((__uint64_t)1 &lt;&lt; (n)) - 1)
macro_line|#endif
multiline_comment|/* Get high bit set out of 32-bit argument, -1 if none set */
r_extern
r_int
id|xfs_highbit32
c_func
(paren
id|__uint32_t
id|v
)paren
suffix:semicolon
multiline_comment|/* Get low bit set out of 64-bit argument, -1 if none set */
r_extern
r_int
id|xfs_lowbit64
c_func
(paren
id|__uint64_t
id|v
)paren
suffix:semicolon
multiline_comment|/* Get high bit set out of 64-bit argument, -1 if none set */
r_extern
r_int
id|xfs_highbit64
c_func
(paren
id|__uint64_t
)paren
suffix:semicolon
multiline_comment|/* Count set bits in map starting with start_bit */
r_extern
r_int
id|xfs_count_bits
c_func
(paren
id|uint
op_star
id|map
comma
id|uint
id|size
comma
id|uint
id|start_bit
)paren
suffix:semicolon
multiline_comment|/* Count continuous one bits in map starting with start_bit */
r_extern
r_int
id|xfs_contig_bits
c_func
(paren
id|uint
op_star
id|map
comma
id|uint
id|size
comma
id|uint
id|start_bit
)paren
suffix:semicolon
multiline_comment|/* Find next set bit in map */
r_extern
r_int
id|xfs_next_bit
c_func
(paren
id|uint
op_star
id|map
comma
id|uint
id|size
comma
id|uint
id|start_bit
)paren
suffix:semicolon
macro_line|#endif&t;/* __XFS_BIT_H__ */
eof
