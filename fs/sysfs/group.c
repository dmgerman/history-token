multiline_comment|/*&n; * fs/sysfs/group.c - Operations for adding/removing multiple files at once.&n; *&n; * Copyright (c) 2003 Patrick Mochel&n; * Copyright (c) 2003 Open Source Development Lab&n; *&n; * This file is released undert the GPL v2. &n; *&n; */
macro_line|#include &lt;linux/kobject.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/dcache.h&gt;
macro_line|#include &lt;linux/err.h&gt;
macro_line|#include &quot;sysfs.h&quot;
DECL|function|remove_files
r_static
r_void
id|remove_files
c_func
(paren
r_struct
id|dentry
op_star
id|dir
comma
r_const
r_struct
id|attribute_group
op_star
id|grp
)paren
(brace
r_struct
id|attribute
op_star
r_const
op_star
id|attr
suffix:semicolon
r_for
c_loop
(paren
id|attr
op_assign
id|grp-&gt;attrs
suffix:semicolon
op_star
id|attr
suffix:semicolon
id|attr
op_increment
)paren
id|sysfs_hash_and_remove
c_func
(paren
id|dir
comma
(paren
op_star
id|attr
)paren
op_member_access_from_pointer
id|name
)paren
suffix:semicolon
)brace
DECL|function|create_files
r_static
r_int
id|create_files
c_func
(paren
r_struct
id|dentry
op_star
id|dir
comma
r_const
r_struct
id|attribute_group
op_star
id|grp
)paren
(brace
r_struct
id|attribute
op_star
r_const
op_star
id|attr
suffix:semicolon
r_int
id|error
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|attr
op_assign
id|grp-&gt;attrs
suffix:semicolon
op_star
id|attr
op_logical_and
op_logical_neg
id|error
suffix:semicolon
id|attr
op_increment
)paren
(brace
id|error
op_assign
id|sysfs_add_file
c_func
(paren
id|dir
comma
op_star
id|attr
comma
id|SYSFS_KOBJ_ATTR
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|error
)paren
id|remove_files
c_func
(paren
id|dir
comma
id|grp
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|function|sysfs_create_group
r_int
id|sysfs_create_group
c_func
(paren
r_struct
id|kobject
op_star
id|kobj
comma
r_const
r_struct
id|attribute_group
op_star
id|grp
)paren
(brace
r_struct
id|dentry
op_star
id|dir
suffix:semicolon
r_int
id|error
suffix:semicolon
id|BUG_ON
c_func
(paren
op_logical_neg
id|kobj
op_logical_or
op_logical_neg
id|kobj-&gt;dentry
)paren
suffix:semicolon
r_if
c_cond
(paren
id|grp-&gt;name
)paren
(brace
id|error
op_assign
id|sysfs_create_subdir
c_func
(paren
id|kobj
comma
id|grp-&gt;name
comma
op_amp
id|dir
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
id|error
suffix:semicolon
)brace
r_else
id|dir
op_assign
id|kobj-&gt;dentry
suffix:semicolon
id|dir
op_assign
id|dget
c_func
(paren
id|dir
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|error
op_assign
id|create_files
c_func
(paren
id|dir
comma
id|grp
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
id|grp-&gt;name
)paren
id|sysfs_remove_subdir
c_func
(paren
id|dir
)paren
suffix:semicolon
)brace
id|dput
c_func
(paren
id|dir
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|function|sysfs_remove_group
r_void
id|sysfs_remove_group
c_func
(paren
r_struct
id|kobject
op_star
id|kobj
comma
r_const
r_struct
id|attribute_group
op_star
id|grp
)paren
(brace
r_struct
id|dentry
op_star
id|dir
suffix:semicolon
r_if
c_cond
(paren
id|grp-&gt;name
)paren
id|dir
op_assign
id|sysfs_get_dentry
c_func
(paren
id|kobj-&gt;dentry
comma
id|grp-&gt;name
)paren
suffix:semicolon
r_else
id|dir
op_assign
id|dget
c_func
(paren
id|kobj-&gt;dentry
)paren
suffix:semicolon
id|remove_files
c_func
(paren
id|dir
comma
id|grp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|grp-&gt;name
)paren
id|sysfs_remove_subdir
c_func
(paren
id|dir
)paren
suffix:semicolon
multiline_comment|/* release the ref. taken in this routine */
id|dput
c_func
(paren
id|dir
)paren
suffix:semicolon
)brace
DECL|variable|sysfs_create_group
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|sysfs_create_group
)paren
suffix:semicolon
DECL|variable|sysfs_remove_group
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|sysfs_remove_group
)paren
suffix:semicolon
eof
