multiline_comment|/*&n; *  debugfs.h - a tiny little debug file system&n; *&n; *  Copyright (C) 2004 Greg Kroah-Hartman &lt;greg@kroah.com&gt;&n; *  Copyright (C) 2004 IBM Inc.&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License version&n; *&t;2 as published by the Free Software Foundation.&n; *&n; *  debugfs is for people to use instead of /proc or /sys.&n; *  See Documentation/DocBook/kernel-api for more details.&n; */
macro_line|#ifndef _DEBUGFS_H_
DECL|macro|_DEBUGFS_H_
mdefine_line|#define _DEBUGFS_H_
macro_line|#if defined(CONFIG_DEBUG_FS)
r_struct
id|dentry
op_star
id|debugfs_create_file
c_func
(paren
r_const
r_char
op_star
id|name
comma
id|mode_t
id|mode
comma
r_struct
id|dentry
op_star
id|parent
comma
r_void
op_star
id|data
comma
r_struct
id|file_operations
op_star
id|fops
)paren
suffix:semicolon
r_struct
id|dentry
op_star
id|debugfs_create_dir
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_struct
id|dentry
op_star
id|parent
)paren
suffix:semicolon
r_void
id|debugfs_remove
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
)paren
suffix:semicolon
r_struct
id|dentry
op_star
id|debugfs_create_u8
c_func
(paren
r_const
r_char
op_star
id|name
comma
id|mode_t
id|mode
comma
r_struct
id|dentry
op_star
id|parent
comma
id|u8
op_star
id|value
)paren
suffix:semicolon
r_struct
id|dentry
op_star
id|debugfs_create_u16
c_func
(paren
r_const
r_char
op_star
id|name
comma
id|mode_t
id|mode
comma
r_struct
id|dentry
op_star
id|parent
comma
id|u16
op_star
id|value
)paren
suffix:semicolon
r_struct
id|dentry
op_star
id|debugfs_create_u32
c_func
(paren
r_const
r_char
op_star
id|name
comma
id|mode_t
id|mode
comma
r_struct
id|dentry
op_star
id|parent
comma
id|u32
op_star
id|value
)paren
suffix:semicolon
r_struct
id|dentry
op_star
id|debugfs_create_bool
c_func
(paren
r_const
r_char
op_star
id|name
comma
id|mode_t
id|mode
comma
r_struct
id|dentry
op_star
id|parent
comma
id|u32
op_star
id|value
)paren
suffix:semicolon
macro_line|#else
multiline_comment|/* &n; * We do not return NULL from these functions if CONFIG_DEBUG_FS is not enabled&n; * so users have a chance to detect if there was a real error or not.  We don&squot;t&n; * want to duplicate the design decision mistakes of procfs and devfs again.&n; */
DECL|function|debugfs_create_file
r_static
r_inline
r_struct
id|dentry
op_star
id|debugfs_create_file
c_func
(paren
r_const
r_char
op_star
id|name
comma
id|mode_t
id|mode
comma
r_struct
id|dentry
op_star
id|parent
comma
r_void
op_star
id|data
comma
r_struct
id|file_operations
op_star
id|fops
)paren
(brace
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|ENODEV
)paren
suffix:semicolon
)brace
DECL|function|debugfs_create_dir
r_static
r_inline
r_struct
id|dentry
op_star
id|debugfs_create_dir
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_struct
id|dentry
op_star
id|parent
)paren
(brace
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|ENODEV
)paren
suffix:semicolon
)brace
DECL|function|debugfs_remove
r_static
r_inline
r_void
id|debugfs_remove
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
)paren
(brace
)brace
DECL|function|debugfs_create_u8
r_static
r_inline
r_struct
id|dentry
op_star
id|debugfs_create_u8
c_func
(paren
r_const
r_char
op_star
id|name
comma
id|mode_t
id|mode
comma
r_struct
id|dentry
op_star
id|parent
comma
id|u8
op_star
id|value
)paren
(brace
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|ENODEV
)paren
suffix:semicolon
)brace
DECL|function|debugfs_create_u16
r_static
r_inline
r_struct
id|dentry
op_star
id|debugfs_create_u16
c_func
(paren
r_const
r_char
op_star
id|name
comma
id|mode_t
id|mode
comma
r_struct
id|dentry
op_star
id|parent
comma
id|u8
op_star
id|value
)paren
(brace
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|ENODEV
)paren
suffix:semicolon
)brace
DECL|function|debugfs_create_u32
r_static
r_inline
r_struct
id|dentry
op_star
id|debugfs_create_u32
c_func
(paren
r_const
r_char
op_star
id|name
comma
id|mode_t
id|mode
comma
r_struct
id|dentry
op_star
id|parent
comma
id|u8
op_star
id|value
)paren
(brace
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|ENODEV
)paren
suffix:semicolon
)brace
DECL|function|debugfs_create_bool
r_static
r_inline
r_struct
id|dentry
op_star
id|debugfs_create_bool
c_func
(paren
r_const
r_char
op_star
id|name
comma
id|mode_t
id|mode
comma
r_struct
id|dentry
op_star
id|parent
comma
id|u8
op_star
id|value
)paren
(brace
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|ENODEV
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#endif
eof
