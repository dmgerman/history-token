multiline_comment|/*&n; * bin.c - binary file operations for sysfs.&n; *&n; * Copyright (c) 2003 Patrick Mochel&n; * Copyright (c) 2003 Matthew Wilcox&n; * Copyright (c) 2004 Silicon Graphics, Inc.&n; */
DECL|macro|DEBUG
macro_line|#undef DEBUG
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/kobject.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &quot;sysfs.h&quot;
r_static
r_int
DECL|function|fill_read
id|fill_read
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_char
op_star
id|buffer
comma
id|loff_t
id|off
comma
r_int
id|count
)paren
(brace
r_struct
id|bin_attribute
op_star
id|attr
op_assign
id|to_bin_attr
c_func
(paren
id|dentry
)paren
suffix:semicolon
r_struct
id|kobject
op_star
id|kobj
op_assign
id|to_kobj
c_func
(paren
id|dentry-&gt;d_parent
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|attr-&gt;read
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
id|attr
op_member_access_from_pointer
id|read
c_func
(paren
id|kobj
comma
id|buffer
comma
id|off
comma
id|count
)paren
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|read
id|read
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_char
id|__user
op_star
id|userbuf
comma
r_int
id|count
comma
id|loff_t
op_star
id|off
)paren
(brace
r_char
op_star
id|buffer
op_assign
id|file-&gt;private_data
suffix:semicolon
r_struct
id|dentry
op_star
id|dentry
op_assign
id|file-&gt;f_dentry
suffix:semicolon
r_int
id|size
op_assign
id|dentry-&gt;d_inode-&gt;i_size
suffix:semicolon
id|loff_t
id|offs
op_assign
op_star
id|off
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|count
OG
id|PAGE_SIZE
)paren
id|count
op_assign
id|PAGE_SIZE
suffix:semicolon
r_if
c_cond
(paren
id|size
)paren
(brace
r_if
c_cond
(paren
id|offs
OG
id|size
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|offs
op_plus
id|count
OG
id|size
)paren
id|count
op_assign
id|size
op_minus
id|offs
suffix:semicolon
)brace
id|ret
op_assign
id|fill_read
c_func
(paren
id|dentry
comma
id|buffer
comma
id|offs
comma
id|count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
id|count
op_assign
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|userbuf
comma
id|buffer
comma
id|count
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;offs = %lld, *off = %lld, count = %zd&bslash;n&quot;
comma
id|offs
comma
op_star
id|off
comma
id|count
)paren
suffix:semicolon
op_star
id|off
op_assign
id|offs
op_plus
id|count
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
r_static
r_int
DECL|function|flush_write
id|flush_write
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_char
op_star
id|buffer
comma
id|loff_t
id|offset
comma
r_int
id|count
)paren
(brace
r_struct
id|bin_attribute
op_star
id|attr
op_assign
id|to_bin_attr
c_func
(paren
id|dentry
)paren
suffix:semicolon
r_struct
id|kobject
op_star
id|kobj
op_assign
id|to_kobj
c_func
(paren
id|dentry-&gt;d_parent
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|attr-&gt;write
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
id|attr
op_member_access_from_pointer
id|write
c_func
(paren
id|kobj
comma
id|buffer
comma
id|offset
comma
id|count
)paren
suffix:semicolon
)brace
DECL|function|write
r_static
id|ssize_t
id|write
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
id|__user
op_star
id|userbuf
comma
r_int
id|count
comma
id|loff_t
op_star
id|off
)paren
(brace
r_char
op_star
id|buffer
op_assign
id|file-&gt;private_data
suffix:semicolon
r_struct
id|dentry
op_star
id|dentry
op_assign
id|file-&gt;f_dentry
suffix:semicolon
r_int
id|size
op_assign
id|dentry-&gt;d_inode-&gt;i_size
suffix:semicolon
id|loff_t
id|offs
op_assign
op_star
id|off
suffix:semicolon
r_if
c_cond
(paren
id|count
OG
id|PAGE_SIZE
)paren
id|count
op_assign
id|PAGE_SIZE
suffix:semicolon
r_if
c_cond
(paren
id|size
)paren
(brace
r_if
c_cond
(paren
id|offs
OG
id|size
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|offs
op_plus
id|count
OG
id|size
)paren
id|count
op_assign
id|size
op_minus
id|offs
suffix:semicolon
)brace
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|buffer
comma
id|userbuf
comma
id|count
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|count
op_assign
id|flush_write
c_func
(paren
id|dentry
comma
id|buffer
comma
id|offs
comma
id|count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
OG
l_int|0
)paren
op_star
id|off
op_assign
id|offs
op_plus
id|count
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
DECL|function|mmap
r_static
r_int
id|mmap
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|vm_area_struct
op_star
id|vma
)paren
(brace
r_struct
id|dentry
op_star
id|dentry
op_assign
id|file-&gt;f_dentry
suffix:semicolon
r_struct
id|bin_attribute
op_star
id|attr
op_assign
id|to_bin_attr
c_func
(paren
id|dentry
)paren
suffix:semicolon
r_struct
id|kobject
op_star
id|kobj
op_assign
id|to_kobj
c_func
(paren
id|dentry-&gt;d_parent
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|attr-&gt;mmap
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
id|attr
op_member_access_from_pointer
id|mmap
c_func
(paren
id|kobj
comma
id|attr
comma
id|vma
)paren
suffix:semicolon
)brace
DECL|function|open
r_static
r_int
id|open
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
(brace
r_struct
id|kobject
op_star
id|kobj
op_assign
id|sysfs_get_kobject
c_func
(paren
id|file-&gt;f_dentry-&gt;d_parent
)paren
suffix:semicolon
r_struct
id|bin_attribute
op_star
id|attr
op_assign
id|to_bin_attr
c_func
(paren
id|file-&gt;f_dentry
)paren
suffix:semicolon
r_int
id|error
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|kobj
op_logical_or
op_logical_neg
id|attr
)paren
r_goto
id|Done
suffix:semicolon
multiline_comment|/* Grab the module reference for this attribute if we have one */
id|error
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|try_module_get
c_func
(paren
id|attr-&gt;attr.owner
)paren
)paren
r_goto
id|Done
suffix:semicolon
id|error
op_assign
op_minus
id|EACCES
suffix:semicolon
r_if
c_cond
(paren
(paren
id|file-&gt;f_mode
op_amp
id|FMODE_WRITE
)paren
op_logical_and
op_logical_neg
(paren
id|attr-&gt;write
op_logical_or
id|attr-&gt;mmap
)paren
)paren
r_goto
id|Error
suffix:semicolon
r_if
c_cond
(paren
(paren
id|file-&gt;f_mode
op_amp
id|FMODE_READ
)paren
op_logical_and
op_logical_neg
(paren
id|attr-&gt;read
op_logical_or
id|attr-&gt;mmap
)paren
)paren
r_goto
id|Error
suffix:semicolon
id|error
op_assign
op_minus
id|ENOMEM
suffix:semicolon
id|file-&gt;private_data
op_assign
id|kmalloc
c_func
(paren
id|PAGE_SIZE
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|file-&gt;private_data
)paren
r_goto
id|Error
suffix:semicolon
id|error
op_assign
l_int|0
suffix:semicolon
r_goto
id|Done
suffix:semicolon
id|Error
suffix:colon
id|module_put
c_func
(paren
id|attr-&gt;attr.owner
)paren
suffix:semicolon
id|Done
suffix:colon
r_if
c_cond
(paren
id|error
op_logical_and
id|kobj
)paren
id|kobject_put
c_func
(paren
id|kobj
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|function|release
r_static
r_int
id|release
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
(brace
r_struct
id|kobject
op_star
id|kobj
op_assign
id|to_kobj
c_func
(paren
id|file-&gt;f_dentry-&gt;d_parent
)paren
suffix:semicolon
r_struct
id|bin_attribute
op_star
id|attr
op_assign
id|to_bin_attr
c_func
(paren
id|file-&gt;f_dentry
)paren
suffix:semicolon
id|u8
op_star
id|buffer
op_assign
id|file-&gt;private_data
suffix:semicolon
r_if
c_cond
(paren
id|kobj
)paren
id|kobject_put
c_func
(paren
id|kobj
)paren
suffix:semicolon
id|module_put
c_func
(paren
id|attr-&gt;attr.owner
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|buffer
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|bin_fops
r_struct
id|file_operations
id|bin_fops
op_assign
(brace
dot
id|read
op_assign
id|read
comma
dot
id|write
op_assign
id|write
comma
dot
id|mmap
op_assign
id|mmap
comma
dot
id|llseek
op_assign
id|generic_file_llseek
comma
dot
id|open
op_assign
id|open
comma
dot
id|release
op_assign
id|release
comma
)brace
suffix:semicolon
multiline_comment|/**&n; *&t;sysfs_create_bin_file - create binary file for object.&n; *&t;@kobj:&t;object.&n; *&t;@attr:&t;attribute descriptor.&n; *&n; */
DECL|function|sysfs_create_bin_file
r_int
id|sysfs_create_bin_file
c_func
(paren
r_struct
id|kobject
op_star
id|kobj
comma
r_struct
id|bin_attribute
op_star
id|attr
)paren
(brace
id|BUG_ON
c_func
(paren
op_logical_neg
id|kobj
op_logical_or
op_logical_neg
id|kobj-&gt;dentry
op_logical_or
op_logical_neg
id|attr
)paren
suffix:semicolon
r_return
id|sysfs_add_file
c_func
(paren
id|kobj-&gt;dentry
comma
op_amp
id|attr-&gt;attr
comma
id|SYSFS_KOBJ_BIN_ATTR
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;sysfs_remove_bin_file - remove binary file for object.&n; *&t;@kobj:&t;object.&n; *&t;@attr:&t;attribute descriptor.&n; *&n; */
DECL|function|sysfs_remove_bin_file
r_int
id|sysfs_remove_bin_file
c_func
(paren
r_struct
id|kobject
op_star
id|kobj
comma
r_struct
id|bin_attribute
op_star
id|attr
)paren
(brace
id|sysfs_hash_and_remove
c_func
(paren
id|kobj-&gt;dentry
comma
id|attr-&gt;attr.name
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|sysfs_create_bin_file
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|sysfs_create_bin_file
)paren
suffix:semicolon
DECL|variable|sysfs_remove_bin_file
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|sysfs_remove_bin_file
)paren
suffix:semicolon
eof
