multiline_comment|/*&n; * lcnalloc.h - Exports for NTFS kernel cluster (de)allocation.  Part of the&n; *&t;&t;Linux-NTFS project.&n; *&n; * Copyright (c) 2004 Anton Altaparmakov&n; *&n; * This program/include file is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License as published&n; * by the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program/include file is distributed in the hope that it will be&n; * useful, but WITHOUT ANY WARRANTY; without even the implied warranty&n; * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program (in the main directory of the Linux-NTFS&n; * distribution in the file COPYING); if not, write to the Free Software&n; * Foundation,Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef _LINUX_NTFS_LCNALLOC_H
DECL|macro|_LINUX_NTFS_LCNALLOC_H
mdefine_line|#define _LINUX_NTFS_LCNALLOC_H
macro_line|#ifdef NTFS_RW
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &quot;types.h&quot;
macro_line|#include &quot;volume.h&quot;
r_typedef
r_enum
(brace
DECL|enumerator|FIRST_ZONE
id|FIRST_ZONE
op_assign
l_int|0
comma
multiline_comment|/* For sanity checking. */
DECL|enumerator|MFT_ZONE
id|MFT_ZONE
op_assign
l_int|0
comma
multiline_comment|/* Allocate from $MFT zone. */
DECL|enumerator|DATA_ZONE
id|DATA_ZONE
op_assign
l_int|1
comma
multiline_comment|/* Allocate from $DATA zone. */
DECL|enumerator|LAST_ZONE
id|LAST_ZONE
op_assign
l_int|1
comma
multiline_comment|/* For sanity checking. */
DECL|typedef|NTFS_CLUSTER_ALLOCATION_ZONES
)brace
id|NTFS_CLUSTER_ALLOCATION_ZONES
suffix:semicolon
r_extern
id|runlist_element
op_star
id|ntfs_cluster_alloc
c_func
(paren
id|ntfs_volume
op_star
id|vol
comma
r_const
id|VCN
id|start_vcn
comma
r_const
id|s64
id|count
comma
r_const
id|LCN
id|start_lcn
comma
r_const
id|NTFS_CLUSTER_ALLOCATION_ZONES
id|zone
)paren
suffix:semicolon
r_extern
id|s64
id|__ntfs_cluster_free
c_func
(paren
r_struct
id|inode
op_star
id|vi
comma
r_const
id|VCN
id|start_vcn
comma
id|s64
id|count
comma
r_const
id|BOOL
id|is_rollback
)paren
suffix:semicolon
multiline_comment|/**&n; * ntfs_cluster_free - free clusters on an ntfs volume&n; * @vi:&t;&t;vfs inode whose runlist describes the clusters to free&n; * @start_vcn:&t;vcn in the runlist of @vi at which to start freeing clusters&n; * @count:&t;number of clusters to free or -1 for all clusters&n; *&n; * Free @count clusters starting at the cluster @start_vcn in the runlist&n; * described by the vfs inode @vi.&n; *&n; * If @count is -1, all clusters from @start_vcn to the end of the runlist are&n; * deallocated.  Thus, to completely free all clusters in a runlist, use&n; * @start_vcn = 0 and @count = -1.&n; *&n; * Note, ntfs_cluster_free() does not modify the runlist at all, so the caller&n; * has to deal with it later.&n; *&n; * Return the number of deallocated clusters (not counting sparse ones) on&n; * success and -errno on error.&n; *&n; * Locking: - The runlist described by @vi must be unlocked on entry and is&n; *&t;      unlocked on return.&n; *&t;    - This function takes the runlist lock of @vi for reading and&n; *&t;      sometimes for writing and sometimes modifies the runlist.&n; *&t;    - The volume lcn bitmap must be unlocked on entry and is unlocked&n; *&t;      on return.&n; *&t;    - This function takes the volume lcn bitmap lock for writing and&n; *&t;      modifies the bitmap contents.&n; */
DECL|function|ntfs_cluster_free
r_static
r_inline
id|s64
id|ntfs_cluster_free
c_func
(paren
r_struct
id|inode
op_star
id|vi
comma
r_const
id|VCN
id|start_vcn
comma
id|s64
id|count
)paren
(brace
r_return
id|__ntfs_cluster_free
c_func
(paren
id|vi
comma
id|start_vcn
comma
id|count
comma
id|FALSE
)paren
suffix:semicolon
)brace
macro_line|#endif /* NTFS_RW */
macro_line|#endif /* defined _LINUX_NTFS_LCNALLOC_H */
eof
