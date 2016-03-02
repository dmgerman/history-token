multiline_comment|/*&n; * Copyright (c) 2000-2002 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.&t; Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
multiline_comment|/*&n; * This file contains globals needed by XFS that were normally defined&n; * somewhere else in IRIX.&n; */
macro_line|#include &lt;xfs.h&gt;
DECL|variable|xfs_physmem
r_int
r_int
id|xfs_physmem
suffix:semicolon
multiline_comment|/*&n; * Used to serialize atomicIncWithWrap.&n; */
DECL|variable|Atomic_spin
id|spinlock_t
id|Atomic_spin
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
multiline_comment|/*&n; * Global system credential structure.&n; */
DECL|variable|sys_cred_val
DECL|variable|sys_cred
id|cred_t
id|sys_cred_val
comma
op_star
id|sys_cred
op_assign
op_amp
id|sys_cred_val
suffix:semicolon
multiline_comment|/*&n; * The global quota manager. There is only one of these for the entire&n; * system, _not_ one per file system. XQM keeps track of the overall&n; * quota functionality, including maintaining the freelist and hash&n; * tables of dquots.&n; */
DECL|variable|xfs_Gqm
r_struct
id|xfs_qm
op_star
id|xfs_Gqm
suffix:semicolon
DECL|variable|xfs_Gqm_lock
id|mutex_t
id|xfs_Gqm_lock
suffix:semicolon
multiline_comment|/* Export XFS symbols used by xfsidbg */
DECL|variable|xfs_Gqm
id|EXPORT_SYMBOL
c_func
(paren
id|xfs_Gqm
)paren
suffix:semicolon
DECL|variable|xfs_next_bit
id|EXPORT_SYMBOL
c_func
(paren
id|xfs_next_bit
)paren
suffix:semicolon
DECL|variable|xfs_contig_bits
id|EXPORT_SYMBOL
c_func
(paren
id|xfs_contig_bits
)paren
suffix:semicolon
DECL|variable|xfs_bmbt_get_all
id|EXPORT_SYMBOL
c_func
(paren
id|xfs_bmbt_get_all
)paren
suffix:semicolon
macro_line|#if ARCH_CONVERT != ARCH_NOCONVERT
DECL|variable|xfs_bmbt_disk_get_all
id|EXPORT_SYMBOL
c_func
(paren
id|xfs_bmbt_disk_get_all
)paren
suffix:semicolon
macro_line|#endif
eof
