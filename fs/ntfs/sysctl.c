multiline_comment|/*&n; * sysctl.c - Code for sysctl handling in NTFS Linux kernel driver. Part of&n; *&t;      the Linux-NTFS project. Adapted from the old NTFS driver,&n; *&t;      Copyright (C) 1997 Martin von L&#xfffd;wis, R&#xfffd;gis Duchesne.&n; *&n; * Copyright (c) 2002 Anton Altaparmakov.&n; *&n; * This program/include file is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License as published&n; * by the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program/include file is distributed in the hope that it will be &n; * useful, but WITHOUT ANY WARRANTY; without even the implied warranty &n; * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program (in the main directory of the Linux-NTFS &n; * distribution in the file COPYING); if not, write to the Free Software&n; * Foundation,Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifdef DEBUG
macro_line|#include &lt;linux/module.h&gt;
macro_line|#ifdef CONFIG_SYSCTL
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/sysctl.h&gt;
macro_line|#include &quot;sysctl.h&quot;
macro_line|#include &quot;debug.h&quot;
DECL|macro|FS_NTFS
mdefine_line|#define FS_NTFS&t;1
multiline_comment|/* Definition of the ntfs sysctl. */
DECL|variable|ntfs_sysctls
r_static
id|ctl_table
id|ntfs_sysctls
(braket
)braket
op_assign
(brace
(brace
id|FS_NTFS
comma
l_string|&quot;ntfs-debug&quot;
comma
multiline_comment|/* Binary and text IDs. */
op_amp
id|debug_msgs
comma
r_sizeof
(paren
id|debug_msgs
)paren
comma
multiline_comment|/* Data pointer and size. */
l_int|0644
comma
l_int|NULL
comma
op_amp
id|proc_dointvec
)brace
comma
multiline_comment|/* Mode, child, proc handler. */
(brace
l_int|0
)brace
)brace
suffix:semicolon
multiline_comment|/* Define the parent directory /proc/sys/fs. */
DECL|variable|sysctls_root
r_static
id|ctl_table
id|sysctls_root
(braket
)braket
op_assign
(brace
(brace
id|CTL_FS
comma
l_string|&quot;fs&quot;
comma
l_int|NULL
comma
l_int|0
comma
l_int|0555
comma
id|ntfs_sysctls
)brace
comma
(brace
l_int|0
)brace
)brace
suffix:semicolon
multiline_comment|/* Storage for the sysctls header. */
DECL|variable|sysctls_root_table
r_static
r_struct
id|ctl_table_header
op_star
id|sysctls_root_table
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/**&n; * ntfs_sysctl - add or remove the debug sysctl&n; * @add:&t;add (1) or remove (0) the sysctl&n; *&n; * Add or remove the debug sysctl. Return 0 on success or -errno on error.&n; */
DECL|function|ntfs_sysctl
r_int
id|ntfs_sysctl
c_func
(paren
r_int
id|add
)paren
(brace
r_if
c_cond
(paren
id|add
)paren
(brace
id|BUG_ON
c_func
(paren
id|sysctls_root_table
)paren
suffix:semicolon
id|sysctls_root_table
op_assign
id|register_sysctl_table
c_func
(paren
id|sysctls_root
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sysctls_root_table
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
macro_line|#ifdef CONFIG_PROC_FS
multiline_comment|/*&n;&t;&t; * If the proc file system is in use and we are a module, need&n;&t;&t; * to set the owner of our proc entry to our module. In the&n;&t;&t; * non-modular case, THIS_MODULE is NULL, so this is ok.&n;&t;&t; */
id|ntfs_sysctls
(braket
l_int|0
)braket
dot
id|de-&gt;owner
op_assign
id|THIS_MODULE
suffix:semicolon
macro_line|#endif
)brace
r_else
(brace
id|BUG_ON
c_func
(paren
op_logical_neg
id|sysctls_root_table
)paren
suffix:semicolon
id|unregister_sysctl_table
c_func
(paren
id|sysctls_root_table
)paren
suffix:semicolon
id|sysctls_root_table
op_assign
l_int|NULL
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_SYSCTL */
macro_line|#endif /* DEBUG */
eof
