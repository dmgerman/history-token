multiline_comment|/*&n; * runlist.h - Defines for runlist handling in NTFS Linux kernel driver.&n; *&t;       Part of the Linux-NTFS project.&n; *&n; * Copyright (c) 2001-2004 Anton Altaparmakov&n; * Copyright (c) 2002 Richard Russon&n; *&n; * This program/include file is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License as published&n; * by the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program/include file is distributed in the hope that it will be&n; * useful, but WITHOUT ANY WARRANTY; without even the implied warranty&n; * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program (in the main directory of the Linux-NTFS&n; * distribution in the file COPYING); if not, write to the Free Software&n; * Foundation,Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef _LINUX_NTFS_RUNLIST_H
DECL|macro|_LINUX_NTFS_RUNLIST_H
mdefine_line|#define _LINUX_NTFS_RUNLIST_H
macro_line|#include &quot;types.h&quot;
macro_line|#include &quot;layout.h&quot;
macro_line|#include &quot;volume.h&quot;
DECL|function|init_runlist
r_static
r_inline
r_void
id|init_runlist
c_func
(paren
id|runlist
op_star
id|rl
)paren
(brace
id|rl-&gt;rl
op_assign
l_int|NULL
suffix:semicolon
id|init_rwsem
c_func
(paren
op_amp
id|rl-&gt;lock
)paren
suffix:semicolon
)brace
r_typedef
r_enum
(brace
DECL|enumerator|LCN_HOLE
id|LCN_HOLE
op_assign
op_minus
l_int|1
comma
multiline_comment|/* Keep this as highest value or die! */
DECL|enumerator|LCN_RL_NOT_MAPPED
id|LCN_RL_NOT_MAPPED
op_assign
op_minus
l_int|2
comma
DECL|enumerator|LCN_ENOENT
id|LCN_ENOENT
op_assign
op_minus
l_int|3
comma
DECL|typedef|LCN_SPECIAL_VALUES
)brace
id|LCN_SPECIAL_VALUES
suffix:semicolon
r_extern
id|runlist_element
op_star
id|decompress_mapping_pairs
c_func
(paren
r_const
id|ntfs_volume
op_star
id|vol
comma
r_const
id|ATTR_RECORD
op_star
id|attr
comma
id|runlist_element
op_star
id|old_rl
)paren
suffix:semicolon
r_extern
id|LCN
id|ntfs_vcn_to_lcn
c_func
(paren
r_const
id|runlist_element
op_star
id|rl
comma
r_const
id|VCN
id|vcn
)paren
suffix:semicolon
macro_line|#endif /* _LINUX_NTFS_RUNLIST_H */
eof
