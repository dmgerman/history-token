multiline_comment|/*&n; * JFFS -- Journaling Flash File System, Linux implementation.&n; *&n; * Copyright (C) 2000  Axis Communications AB.&n; *&n; * Created by Simon Kagstrom &lt;simonk@axis.com&gt;.&n; *&n; * This is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * $Id: jffs_proc.h,v 1.2 2000/11/15 22:04:12 sjhill Exp $&n; */
multiline_comment|/* jffs_proc.h defines a structure for inclusion in the proc-file system.  */
macro_line|#ifndef __LINUX_JFFS_PROC_H__
DECL|macro|__LINUX_JFFS_PROC_H__
mdefine_line|#define __LINUX_JFFS_PROC_H__
macro_line|#include &lt;linux/proc_fs.h&gt;
multiline_comment|/* The proc_dir_entry for jffs (defined in jffs_proc.c).  */
r_extern
r_struct
id|proc_dir_entry
op_star
id|jffs_proc_root
suffix:semicolon
r_int
id|jffs_register_jffs_proc_dir
c_func
(paren
id|kdev_t
id|dev
comma
r_struct
id|jffs_control
op_star
id|c
)paren
suffix:semicolon
r_int
id|jffs_unregister_jffs_proc_dir
c_func
(paren
r_struct
id|jffs_control
op_star
id|c
)paren
suffix:semicolon
macro_line|#endif /* __LINUX_JFFS_PROC_H__ */
eof
