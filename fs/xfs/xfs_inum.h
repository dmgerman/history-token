multiline_comment|/*&n; * Copyright (c) 2000 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.&t; Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#ifndef __XFS_INUM_H__
DECL|macro|__XFS_INUM_H__
mdefine_line|#define __XFS_INUM_H__
multiline_comment|/*&n; * Inode number format:&n; * low inopblog bits - offset in block&n; * next agblklog bits - block number in ag&n; * next agno_log bits - ag number&n; * high agno_log-agblklog-inopblog bits - 0&n; */
DECL|typedef|xfs_agino_t
r_typedef
id|__uint32_t
id|xfs_agino_t
suffix:semicolon
multiline_comment|/* within allocation grp inode number */
multiline_comment|/*&n; * Useful inode bits for this kernel.&n; * Used in some places where having 64-bits in the 32-bit kernels&n; * costs too much.&n; */
macro_line|#if XFS_BIG_FILESYSTEMS
DECL|typedef|xfs_intino_t
r_typedef
id|xfs_ino_t
id|xfs_intino_t
suffix:semicolon
macro_line|#else
DECL|typedef|xfs_intino_t
r_typedef
id|__uint32_t
id|xfs_intino_t
suffix:semicolon
macro_line|#endif
DECL|macro|NULLFSINO
mdefine_line|#define NULLFSINO&t;((xfs_ino_t)-1)
DECL|macro|NULLAGINO
mdefine_line|#define NULLAGINO&t;((xfs_agino_t)-1)
r_struct
id|xfs_mount
suffix:semicolon
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_INO_MASK)
id|__uint32_t
id|xfs_ino_mask
c_func
(paren
r_int
id|k
)paren
suffix:semicolon
DECL|macro|XFS_INO_MASK
mdefine_line|#define XFS_INO_MASK(k)&t;&t;&t;xfs_ino_mask(k)
macro_line|#else
DECL|macro|XFS_INO_MASK
mdefine_line|#define XFS_INO_MASK(k) ((__uint32_t)((1ULL &lt;&lt; (k)) - 1))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_INO_OFFSET_BITS)
r_int
id|xfs_ino_offset_bits
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
)paren
suffix:semicolon
DECL|macro|XFS_INO_OFFSET_BITS
mdefine_line|#define XFS_INO_OFFSET_BITS(mp)&t;&t;xfs_ino_offset_bits(mp)
macro_line|#else
DECL|macro|XFS_INO_OFFSET_BITS
mdefine_line|#define XFS_INO_OFFSET_BITS(mp) ((mp)-&gt;m_sb.sb_inopblog)
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_INO_AGBNO_BITS)
r_int
id|xfs_ino_agbno_bits
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
)paren
suffix:semicolon
DECL|macro|XFS_INO_AGBNO_BITS
mdefine_line|#define XFS_INO_AGBNO_BITS(mp)&t;&t;xfs_ino_agbno_bits(mp)
macro_line|#else
DECL|macro|XFS_INO_AGBNO_BITS
mdefine_line|#define XFS_INO_AGBNO_BITS(mp)&t;((mp)-&gt;m_sb.sb_agblklog)
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_INO_AGINO_BITS)
r_int
id|xfs_ino_agino_bits
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
)paren
suffix:semicolon
DECL|macro|XFS_INO_AGINO_BITS
mdefine_line|#define XFS_INO_AGINO_BITS(mp)&t;&t;xfs_ino_agino_bits(mp)
macro_line|#else
DECL|macro|XFS_INO_AGINO_BITS
mdefine_line|#define XFS_INO_AGINO_BITS(mp)&t;&t;((mp)-&gt;m_agino_log)
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_INO_AGNO_BITS)
r_int
id|xfs_ino_agno_bits
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
)paren
suffix:semicolon
DECL|macro|XFS_INO_AGNO_BITS
mdefine_line|#define XFS_INO_AGNO_BITS(mp)&t;&t;xfs_ino_agno_bits(mp)
macro_line|#else
DECL|macro|XFS_INO_AGNO_BITS
mdefine_line|#define XFS_INO_AGNO_BITS(mp)&t;((mp)-&gt;m_agno_log)
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_INO_BITS)
r_int
id|xfs_ino_bits
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
)paren
suffix:semicolon
DECL|macro|XFS_INO_BITS
mdefine_line|#define XFS_INO_BITS(mp)&t;&t;xfs_ino_bits(mp)
macro_line|#else
DECL|macro|XFS_INO_BITS
mdefine_line|#define XFS_INO_BITS(mp)&t;(XFS_INO_AGNO_BITS(mp) + XFS_INO_AGINO_BITS(mp))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_INO_TO_AGNO)
id|xfs_agnumber_t
id|xfs_ino_to_agno
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
comma
id|xfs_ino_t
id|i
)paren
suffix:semicolon
DECL|macro|XFS_INO_TO_AGNO
mdefine_line|#define XFS_INO_TO_AGNO(mp,i)&t;&t;xfs_ino_to_agno(mp,i)
macro_line|#else
DECL|macro|XFS_INO_TO_AGNO
mdefine_line|#define XFS_INO_TO_AGNO(mp,i)&t;&bslash;&n;&t;((xfs_agnumber_t)((i) &gt;&gt; XFS_INO_AGINO_BITS(mp)))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_INO_TO_AGINO)
id|xfs_agino_t
id|xfs_ino_to_agino
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
comma
id|xfs_ino_t
id|i
)paren
suffix:semicolon
DECL|macro|XFS_INO_TO_AGINO
mdefine_line|#define XFS_INO_TO_AGINO(mp,i)&t;&t;xfs_ino_to_agino(mp,i)
macro_line|#else
DECL|macro|XFS_INO_TO_AGINO
mdefine_line|#define XFS_INO_TO_AGINO(mp,i)&t;&bslash;&n;&t;((xfs_agino_t)(i) &amp; XFS_INO_MASK(XFS_INO_AGINO_BITS(mp)))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_INO_TO_AGBNO)
id|xfs_agblock_t
id|xfs_ino_to_agbno
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
comma
id|xfs_ino_t
id|i
)paren
suffix:semicolon
DECL|macro|XFS_INO_TO_AGBNO
mdefine_line|#define XFS_INO_TO_AGBNO(mp,i)&t;&t;xfs_ino_to_agbno(mp,i)
macro_line|#else
DECL|macro|XFS_INO_TO_AGBNO
mdefine_line|#define XFS_INO_TO_AGBNO(mp,i)&t;&bslash;&n;&t;(((xfs_agblock_t)(i) &gt;&gt; XFS_INO_OFFSET_BITS(mp)) &amp; &bslash;&n;&t; XFS_INO_MASK(XFS_INO_AGBNO_BITS(mp)))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_INO_TO_OFFSET)
r_int
id|xfs_ino_to_offset
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
comma
id|xfs_ino_t
id|i
)paren
suffix:semicolon
DECL|macro|XFS_INO_TO_OFFSET
mdefine_line|#define XFS_INO_TO_OFFSET(mp,i)&t;&t;xfs_ino_to_offset(mp,i)
macro_line|#else
DECL|macro|XFS_INO_TO_OFFSET
mdefine_line|#define XFS_INO_TO_OFFSET(mp,i) &bslash;&n;&t;((int)(i) &amp; XFS_INO_MASK(XFS_INO_OFFSET_BITS(mp)))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_INO_TO_FSB)
id|xfs_fsblock_t
id|xfs_ino_to_fsb
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
comma
id|xfs_ino_t
id|i
)paren
suffix:semicolon
DECL|macro|XFS_INO_TO_FSB
mdefine_line|#define XFS_INO_TO_FSB(mp,i)&t;&t;xfs_ino_to_fsb(mp,i)
macro_line|#else
DECL|macro|XFS_INO_TO_FSB
mdefine_line|#define XFS_INO_TO_FSB(mp,i)&t;&bslash;&n;&t;XFS_AGB_TO_FSB(mp, XFS_INO_TO_AGNO(mp,i), XFS_INO_TO_AGBNO(mp,i))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_AGINO_TO_INO)
id|xfs_ino_t
id|xfs_agino_to_ino
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
comma
id|xfs_agnumber_t
id|a
comma
id|xfs_agino_t
id|i
)paren
suffix:semicolon
DECL|macro|XFS_AGINO_TO_INO
mdefine_line|#define XFS_AGINO_TO_INO(mp,a,i)&t;xfs_agino_to_ino(mp,a,i)
macro_line|#else
DECL|macro|XFS_AGINO_TO_INO
mdefine_line|#define XFS_AGINO_TO_INO(mp,a,i)&t;&bslash;&n;&t;(((xfs_ino_t)(a) &lt;&lt; XFS_INO_AGINO_BITS(mp)) | (i))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_AGINO_TO_AGBNO)
id|xfs_agblock_t
id|xfs_agino_to_agbno
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
comma
id|xfs_agino_t
id|i
)paren
suffix:semicolon
DECL|macro|XFS_AGINO_TO_AGBNO
mdefine_line|#define XFS_AGINO_TO_AGBNO(mp,i)&t;xfs_agino_to_agbno(mp,i)
macro_line|#else
DECL|macro|XFS_AGINO_TO_AGBNO
mdefine_line|#define XFS_AGINO_TO_AGBNO(mp,i)&t;((i) &gt;&gt; XFS_INO_OFFSET_BITS(mp))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_AGINO_TO_OFFSET)
r_int
id|xfs_agino_to_offset
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
comma
id|xfs_agino_t
id|i
)paren
suffix:semicolon
DECL|macro|XFS_AGINO_TO_OFFSET
mdefine_line|#define XFS_AGINO_TO_OFFSET(mp,i)&t;xfs_agino_to_offset(mp,i)
macro_line|#else
DECL|macro|XFS_AGINO_TO_OFFSET
mdefine_line|#define XFS_AGINO_TO_OFFSET(mp,i)&t;&bslash;&n;&t;((i) &amp; XFS_INO_MASK(XFS_INO_OFFSET_BITS(mp)))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_OFFBNO_TO_AGINO)
id|xfs_agino_t
id|xfs_offbno_to_agino
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
comma
id|xfs_agblock_t
id|b
comma
r_int
id|o
)paren
suffix:semicolon
DECL|macro|XFS_OFFBNO_TO_AGINO
mdefine_line|#define XFS_OFFBNO_TO_AGINO(mp,b,o)&t;xfs_offbno_to_agino(mp,b,o)
macro_line|#else
DECL|macro|XFS_OFFBNO_TO_AGINO
mdefine_line|#define XFS_OFFBNO_TO_AGINO(mp,b,o)&t;&bslash;&n;&t;((xfs_agino_t)(((b) &lt;&lt; XFS_INO_OFFSET_BITS(mp)) | (o)))
macro_line|#endif
macro_line|#if XFS_BIG_FILESYSTEMS
DECL|macro|XFS_MAXINUMBER
mdefine_line|#define XFS_MAXINUMBER&t;&t;((xfs_ino_t)((1ULL &lt;&lt; 56) - 1ULL))
DECL|macro|XFS_INO64_OFFSET
mdefine_line|#define XFS_INO64_OFFSET&t;((xfs_ino_t)(1ULL &lt;&lt; 32))
macro_line|#else
DECL|macro|XFS_MAXINUMBER
mdefine_line|#define XFS_MAXINUMBER&t;&t;((xfs_ino_t)((1ULL &lt;&lt; 32) - 1ULL))
macro_line|#endif
DECL|macro|XFS_MAXINUMBER_32
mdefine_line|#define XFS_MAXINUMBER_32&t;((xfs_ino_t)((1ULL &lt;&lt; 32) - 1ULL))
macro_line|#endif&t;/* __XFS_INUM_H__ */
eof
