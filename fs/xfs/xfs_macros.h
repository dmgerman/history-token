multiline_comment|/*&n; * Copyright (c) 2000 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.&t; Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#ifndef __XFS_MACROS_H__
DECL|macro|__XFS_MACROS_H__
mdefine_line|#define __XFS_MACROS_H__
multiline_comment|/*&n; * Set for debug kernels and simulation&n; * These replacements save space.&n; * Used in xfs_macros.c.&n; */
DECL|macro|XFS_WANT_SPACE_C
mdefine_line|#define XFS_WANT_SPACE_C&t;&bslash;&n;&t;(!defined(_STANDALONE) &amp;&amp; defined(DEBUG))
multiline_comment|/*&n; * Set for debug simulation and kernel builds, but not for standalone.&n; * These replacements do not save space.&n; * Used in xfs_macros.c.&n; */
DECL|macro|XFS_WANT_FUNCS_C
mdefine_line|#define XFS_WANT_FUNCS_C&t;&bslash;&n;&t;(!defined(_STANDALONE) &amp;&amp; defined(DEBUG))
multiline_comment|/*&n; * Corresponding names used in .h files.&n; */
DECL|macro|XFS_WANT_SPACE
mdefine_line|#define XFS_WANT_SPACE&t;(XFS_WANT_SPACE_C &amp;&amp; !defined(XFS_MACRO_C))
DECL|macro|XFS_WANT_FUNCS
mdefine_line|#define XFS_WANT_FUNCS&t;(XFS_WANT_FUNCS_C &amp;&amp; !defined(XFS_MACRO_C))
multiline_comment|/*&n; * These are the macros that get turned into functions to save space.&n; */
DECL|macro|XFSSO_NULLSTARTBLOCK
mdefine_line|#define XFSSO_NULLSTARTBLOCK 1
DECL|macro|XFSSO_XFS_AGB_TO_DADDR
mdefine_line|#define XFSSO_XFS_AGB_TO_DADDR 1
DECL|macro|XFSSO_XFS_AGB_TO_FSB
mdefine_line|#define XFSSO_XFS_AGB_TO_FSB 1
DECL|macro|XFSSO_XFS_AGINO_TO_INO
mdefine_line|#define XFSSO_XFS_AGINO_TO_INO 1
DECL|macro|XFSSO_XFS_ALLOC_BLOCK_MINRECS
mdefine_line|#define XFSSO_XFS_ALLOC_BLOCK_MINRECS 1
DECL|macro|XFSSO_XFS_ATTR_SF_NEXTENTRY
mdefine_line|#define XFSSO_XFS_ATTR_SF_NEXTENTRY 1
DECL|macro|XFSSO_XFS_BMAP_BLOCK_DMAXRECS
mdefine_line|#define XFSSO_XFS_BMAP_BLOCK_DMAXRECS 1
DECL|macro|XFSSO_XFS_BMAP_BLOCK_IMAXRECS
mdefine_line|#define XFSSO_XFS_BMAP_BLOCK_IMAXRECS 1
DECL|macro|XFSSO_XFS_BMAP_BLOCK_IMINRECS
mdefine_line|#define XFSSO_XFS_BMAP_BLOCK_IMINRECS 1
DECL|macro|XFSSO_XFS_BMAP_INIT
mdefine_line|#define XFSSO_XFS_BMAP_INIT 1
DECL|macro|XFSSO_XFS_BMAP_PTR_IADDR
mdefine_line|#define XFSSO_XFS_BMAP_PTR_IADDR 1
DECL|macro|XFSSO_XFS_BMAP_SANITY_CHECK
mdefine_line|#define XFSSO_XFS_BMAP_SANITY_CHECK 1
DECL|macro|XFSSO_XFS_BMAPI_AFLAG
mdefine_line|#define XFSSO_XFS_BMAPI_AFLAG 1
DECL|macro|XFSSO_XFS_CFORK_SIZE
mdefine_line|#define XFSSO_XFS_CFORK_SIZE 1
DECL|macro|XFSSO_XFS_DA_COOKIE_BNO
mdefine_line|#define XFSSO_XFS_DA_COOKIE_BNO 1
DECL|macro|XFSSO_XFS_DA_COOKIE_ENTRY
mdefine_line|#define XFSSO_XFS_DA_COOKIE_ENTRY 1
DECL|macro|XFSSO_XFS_DADDR_TO_AGBNO
mdefine_line|#define XFSSO_XFS_DADDR_TO_AGBNO 1
DECL|macro|XFSSO_XFS_DADDR_TO_FSB
mdefine_line|#define XFSSO_XFS_DADDR_TO_FSB 1
DECL|macro|XFSSO_XFS_DFORK_PTR
mdefine_line|#define XFSSO_XFS_DFORK_PTR 1
DECL|macro|XFSSO_XFS_DIR_SF_GET_DIRINO
mdefine_line|#define XFSSO_XFS_DIR_SF_GET_DIRINO 1
DECL|macro|XFSSO_XFS_DIR_SF_NEXTENTRY
mdefine_line|#define XFSSO_XFS_DIR_SF_NEXTENTRY 1
DECL|macro|XFSSO_XFS_DIR_SF_PUT_DIRINO
mdefine_line|#define XFSSO_XFS_DIR_SF_PUT_DIRINO 1
DECL|macro|XFSSO_XFS_FILBLKS_MIN
mdefine_line|#define XFSSO_XFS_FILBLKS_MIN 1
DECL|macro|XFSSO_XFS_FSB_SANITY_CHECK
mdefine_line|#define XFSSO_XFS_FSB_SANITY_CHECK 1
DECL|macro|XFSSO_XFS_FSB_TO_DADDR
mdefine_line|#define XFSSO_XFS_FSB_TO_DADDR 1
DECL|macro|XFSSO_XFS_FSB_TO_DB
mdefine_line|#define XFSSO_XFS_FSB_TO_DB 1
DECL|macro|XFSSO_XFS_IALLOC_INODES
mdefine_line|#define XFSSO_XFS_IALLOC_INODES 1
DECL|macro|XFSSO_XFS_IFORK_ASIZE
mdefine_line|#define XFSSO_XFS_IFORK_ASIZE 1
DECL|macro|XFSSO_XFS_IFORK_DSIZE
mdefine_line|#define XFSSO_XFS_IFORK_DSIZE 1
DECL|macro|XFSSO_XFS_IFORK_FORMAT
mdefine_line|#define XFSSO_XFS_IFORK_FORMAT 1
DECL|macro|XFSSO_XFS_IFORK_NEXT_SET
mdefine_line|#define XFSSO_XFS_IFORK_NEXT_SET 1
DECL|macro|XFSSO_XFS_IFORK_NEXTENTS
mdefine_line|#define XFSSO_XFS_IFORK_NEXTENTS 1
DECL|macro|XFSSO_XFS_IFORK_PTR
mdefine_line|#define XFSSO_XFS_IFORK_PTR 1
DECL|macro|XFSSO_XFS_ILOG_FBROOT
mdefine_line|#define XFSSO_XFS_ILOG_FBROOT 1
DECL|macro|XFSSO_XFS_ILOG_FEXT
mdefine_line|#define XFSSO_XFS_ILOG_FEXT 1
DECL|macro|XFSSO_XFS_INO_MASK
mdefine_line|#define XFSSO_XFS_INO_MASK 1
DECL|macro|XFSSO_XFS_INO_TO_FSB
mdefine_line|#define XFSSO_XFS_INO_TO_FSB 1
DECL|macro|XFSSO_XFS_INODE_CLEAR_READ_AHEAD
mdefine_line|#define XFSSO_XFS_INODE_CLEAR_READ_AHEAD 1
DECL|macro|XFSSO_XFS_MIN_FREELIST
mdefine_line|#define XFSSO_XFS_MIN_FREELIST 1
DECL|macro|XFSSO_XFS_SB_GOOD_VERSION
mdefine_line|#define XFSSO_XFS_SB_GOOD_VERSION 1
DECL|macro|XFSSO_XFS_SB_VERSION_HASNLINK
mdefine_line|#define XFSSO_XFS_SB_VERSION_HASNLINK 1
DECL|macro|XFSSO_XLOG_GRANT_ADD_SPACE
mdefine_line|#define XFSSO_XLOG_GRANT_ADD_SPACE 1
DECL|macro|XFSSO_XLOG_GRANT_SUB_SPACE
mdefine_line|#define XFSSO_XLOG_GRANT_SUB_SPACE 1
macro_line|#endif&t;/* __XFS_MACROS_H__ */
eof
