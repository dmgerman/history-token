multiline_comment|/*&n; * quota.h - Defines for NTFS kernel quota ($Quota) handling.  Part of the&n; *&t;     Linux-NTFS project.&n; *&n; * Copyright (c) 2004 Anton Altaparmakov&n; *&n; * This program/include file is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License as published&n; * by the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program/include file is distributed in the hope that it will be&n; * useful, but WITHOUT ANY WARRANTY; without even the implied warranty&n; * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program (in the main directory of the Linux-NTFS&n; * distribution in the file COPYING); if not, write to the Free Software&n; * Foundation,Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef _LINUX_NTFS_QUOTA_H
DECL|macro|_LINUX_NTFS_QUOTA_H
mdefine_line|#define _LINUX_NTFS_QUOTA_H
macro_line|#ifdef NTFS_RW
macro_line|#include &quot;types.h&quot;
macro_line|#include &quot;volume.h&quot;
r_extern
id|BOOL
id|ntfs_mark_quotas_out_of_date
c_func
(paren
id|ntfs_volume
op_star
id|vol
)paren
suffix:semicolon
macro_line|#endif /* NTFS_RW */
macro_line|#endif /* _LINUX_NTFS_QUOTA_H */
eof
