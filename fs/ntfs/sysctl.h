multiline_comment|/*&n; * sysctl.h - Defines for sysctl handling in NTFS Linux kernel driver. Part of&n; *&t;      the Linux-NTFS project. Adapted from the old NTFS driver,&n; *&t;      Copyright (C) 1997 Martin von L&#xfffd;wis, R&#xfffd;gis Duchesne.&n; * &n; * Copyright (c) 2002 Anton Altaparmakov.&n; *&n; * This program/include file is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License as published&n; * by the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program/include file is distributed in the hope that it will be &n; * useful, but WITHOUT ANY WARRANTY; without even the implied warranty &n; * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program (in the main directory of the Linux-NTFS &n; * distribution in the file COPYING); if not, write to the Free Software&n; * Foundation,Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef _LINUX_NTFS_SYSCTL_H
DECL|macro|_LINUX_NTFS_SYSCTL_H
mdefine_line|#define _LINUX_NTFS_SYSCTL_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#if (DEBUG &amp;&amp; CONFIG_SYSCTL)
r_extern
r_int
id|ntfs_sysctl
c_func
(paren
r_int
id|add
)paren
suffix:semicolon
macro_line|#else
multiline_comment|/* Just return success. */
DECL|function|ntfs_sysctl
r_static
r_inline
r_int
id|ntfs_sysctl
c_func
(paren
r_int
id|add
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif /* DEBUG &amp;&amp; CONFIG_SYSCTL */
macro_line|#endif /* _LINUX_NTFS_SYSCTL_H */
eof
