multiline_comment|/*&n; *  file.c - part of debugfs, a tiny little debug file system&n; *&n; *  Copyright (C) 2004 Greg Kroah-Hartman &lt;greg@kroah.com&gt;&n; *  Copyright (C) 2004 IBM Inc.&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License version&n; *&t;2 as published by the Free Software Foundation.&n; *&n; *  debugfs is for people to use instead of /proc or /sys.&n; *  See Documentation/DocBook/kernel-api for more details.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/debugfs.h&gt;
DECL|function|default_read_file
r_static
id|ssize_t
id|default_read_file
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
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|default_write_file
r_static
id|ssize_t
id|default_write_file
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
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_return
id|count
suffix:semicolon
)brace
DECL|function|default_open
r_static
r_int
id|default_open
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
r_if
c_cond
(paren
id|inode-&gt;u.generic_ip
)paren
id|file-&gt;private_data
op_assign
id|inode-&gt;u.generic_ip
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|debugfs_file_operations
r_struct
id|file_operations
id|debugfs_file_operations
op_assign
(brace
dot
id|read
op_assign
id|default_read_file
comma
dot
id|write
op_assign
id|default_write_file
comma
dot
id|open
op_assign
id|default_open
comma
)brace
suffix:semicolon
DECL|macro|simple_type
mdefine_line|#define simple_type(type, format, temptype, strtolfn)&t;&t;&t;&t;&bslash;&n;static ssize_t read_file_##type(struct file *file, char __user *user_buf,&t;&bslash;&n;&t;&t;&t;&t;size_t count, loff_t *ppos)&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;char buf[32];&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;type *val = file-&gt;private_data;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;snprintf(buf, sizeof(buf), format &quot;&bslash;n&quot;, *val);&t;&t;&t;&t;&bslash;&n;&t;return simple_read_from_buffer(user_buf, count, ppos, buf, strlen(buf));&bslash;&n;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;static ssize_t write_file_##type(struct file *file, const char __user *user_buf,&bslash;&n;&t;&t;&t;&t; size_t count, loff_t *ppos)&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;char *endp;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;char buf[32];&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;int buf_size;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;type *val = file-&gt;private_data;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;temptype tmp;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;memset(buf, 0x00, sizeof(buf));&t;&t;&t;&t;&t;&t;&bslash;&n;&t;buf_size = min(count, (sizeof(buf)-1));&t;&t;&t;&t;&t;&bslash;&n;&t;if (copy_from_user(buf, user_buf, buf_size))&t;&t;&t;&t;&bslash;&n;&t;&t;return -EFAULT;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;tmp = strtolfn(buf, &amp;endp, 0);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if ((endp == buf) || ((type)tmp != tmp))&t;&t;&t;&t;&bslash;&n;&t;&t;return -EINVAL;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;*val = tmp;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;return count;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;static struct file_operations fops_##type = {&t;&t;&t;&t;&t;&bslash;&n;&t;.read =&t;&t;read_file_##type,&t;&t;&t;&t;&t;&bslash;&n;&t;.write =&t;write_file_##type,&t;&t;&t;&t;&t;&bslash;&n;&t;.open =&t;&t;default_open,&t;&t;&t;&t;&t;&t;&bslash;&n;};
id|simple_type
c_func
(paren
id|u8
comma
l_string|&quot;%c&quot;
comma
r_int
r_int
comma
id|simple_strtoul
)paren
suffix:semicolon
id|simple_type
c_func
(paren
id|u16
comma
l_string|&quot;%hi&quot;
comma
r_int
r_int
comma
id|simple_strtoul
)paren
suffix:semicolon
id|simple_type
c_func
(paren
id|u32
comma
l_string|&quot;%i&quot;
comma
r_int
r_int
comma
id|simple_strtoul
)paren
suffix:semicolon
multiline_comment|/**&n; * debugfs_create_u8 - create a file in the debugfs filesystem that is used to read and write a unsigned 8 bit value.&n; *&n; * @name: a pointer to a string containing the name of the file to create.&n; * @mode: the permission that the file should have&n; * @parent: a pointer to the parent dentry for this file.  This should be a&n; *          directory dentry if set.  If this paramater is NULL, then the&n; *          file will be created in the root of the debugfs filesystem.&n; * @value: a pointer to the variable that the file should read to and write&n; *         from.&n; *&n; * This function creates a file in debugfs with the given name that&n; * contains the value of the variable @value.  If the @mode variable is so&n; * set, it can be read from, and written to.&n; *&n; * This function will return a pointer to a dentry if it succeeds.  This&n; * pointer must be passed to the debugfs_remove() function when the file is&n; * to be removed (no automatic cleanup happens if your module is unloaded,&n; * you are responsible here.)  If an error occurs, NULL will be returned.&n; *&n; * If debugfs is not enabled in the kernel, the value -ENODEV will be&n; * returned.  It is not wise to check for this value, but rather, check for&n; * NULL or !NULL instead as to eliminate the need for #ifdef in the calling&n; * code.&n; */
DECL|function|debugfs_create_u8
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
id|debugfs_create_file
c_func
(paren
id|name
comma
id|mode
comma
id|parent
comma
id|value
comma
op_amp
id|fops_u8
)paren
suffix:semicolon
)brace
DECL|variable|debugfs_create_u8
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|debugfs_create_u8
)paren
suffix:semicolon
multiline_comment|/**&n; * debugfs_create_u16 - create a file in the debugfs filesystem that is used to read and write a unsigned 8 bit value.&n; *&n; * @name: a pointer to a string containing the name of the file to create.&n; * @mode: the permission that the file should have&n; * @parent: a pointer to the parent dentry for this file.  This should be a&n; *          directory dentry if set.  If this paramater is NULL, then the&n; *          file will be created in the root of the debugfs filesystem.&n; * @value: a pointer to the variable that the file should read to and write&n; *         from.&n; *&n; * This function creates a file in debugfs with the given name that&n; * contains the value of the variable @value.  If the @mode variable is so&n; * set, it can be read from, and written to.&n; *&n; * This function will return a pointer to a dentry if it succeeds.  This&n; * pointer must be passed to the debugfs_remove() function when the file is&n; * to be removed (no automatic cleanup happens if your module is unloaded,&n; * you are responsible here.)  If an error occurs, NULL will be returned.&n; *&n; * If debugfs is not enabled in the kernel, the value -ENODEV will be&n; * returned.  It is not wise to check for this value, but rather, check for&n; * NULL or !NULL instead as to eliminate the need for #ifdef in the calling&n; * code.&n; */
DECL|function|debugfs_create_u16
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
(brace
r_return
id|debugfs_create_file
c_func
(paren
id|name
comma
id|mode
comma
id|parent
comma
id|value
comma
op_amp
id|fops_u16
)paren
suffix:semicolon
)brace
DECL|variable|debugfs_create_u16
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|debugfs_create_u16
)paren
suffix:semicolon
multiline_comment|/**&n; * debugfs_create_u32 - create a file in the debugfs filesystem that is used to read and write a unsigned 8 bit value.&n; *&n; * @name: a pointer to a string containing the name of the file to create.&n; * @mode: the permission that the file should have&n; * @parent: a pointer to the parent dentry for this file.  This should be a&n; *          directory dentry if set.  If this paramater is NULL, then the&n; *          file will be created in the root of the debugfs filesystem.&n; * @value: a pointer to the variable that the file should read to and write&n; *         from.&n; *&n; * This function creates a file in debugfs with the given name that&n; * contains the value of the variable @value.  If the @mode variable is so&n; * set, it can be read from, and written to.&n; *&n; * This function will return a pointer to a dentry if it succeeds.  This&n; * pointer must be passed to the debugfs_remove() function when the file is&n; * to be removed (no automatic cleanup happens if your module is unloaded,&n; * you are responsible here.)  If an error occurs, NULL will be returned.&n; *&n; * If debugfs is not enabled in the kernel, the value -ENODEV will be&n; * returned.  It is not wise to check for this value, but rather, check for&n; * NULL or !NULL instead as to eliminate the need for #ifdef in the calling&n; * code.&n; */
DECL|function|debugfs_create_u32
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
(brace
r_return
id|debugfs_create_file
c_func
(paren
id|name
comma
id|mode
comma
id|parent
comma
id|value
comma
op_amp
id|fops_u32
)paren
suffix:semicolon
)brace
DECL|variable|debugfs_create_u32
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|debugfs_create_u32
)paren
suffix:semicolon
DECL|function|read_file_bool
r_static
id|ssize_t
id|read_file_bool
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
id|user_buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_char
id|buf
(braket
l_int|3
)braket
suffix:semicolon
id|u32
op_star
id|val
op_assign
id|file-&gt;private_data
suffix:semicolon
r_if
c_cond
(paren
op_star
id|val
)paren
id|buf
(braket
l_int|0
)braket
op_assign
l_char|&squot;Y&squot;
suffix:semicolon
r_else
id|buf
(braket
l_int|0
)braket
op_assign
l_char|&squot;N&squot;
suffix:semicolon
id|buf
(braket
l_int|1
)braket
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
id|buf
(braket
l_int|2
)braket
op_assign
l_int|0x00
suffix:semicolon
r_return
id|simple_read_from_buffer
c_func
(paren
id|user_buf
comma
id|count
comma
id|ppos
comma
id|buf
comma
l_int|2
)paren
suffix:semicolon
)brace
DECL|function|write_file_bool
r_static
id|ssize_t
id|write_file_bool
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
id|user_buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_char
id|buf
(braket
l_int|32
)braket
suffix:semicolon
r_int
id|buf_size
suffix:semicolon
id|u32
op_star
id|val
op_assign
id|file-&gt;private_data
suffix:semicolon
id|buf_size
op_assign
id|min
c_func
(paren
id|count
comma
(paren
r_sizeof
(paren
id|buf
)paren
op_minus
l_int|1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|buf
comma
id|user_buf
comma
id|buf_size
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_switch
c_cond
(paren
id|buf
(braket
l_int|0
)braket
)paren
(brace
r_case
l_char|&squot;y&squot;
suffix:colon
r_case
l_char|&squot;Y&squot;
suffix:colon
r_case
l_char|&squot;1&squot;
suffix:colon
op_star
id|val
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;n&squot;
suffix:colon
r_case
l_char|&squot;N&squot;
suffix:colon
r_case
l_char|&squot;0&squot;
suffix:colon
op_star
id|val
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|count
suffix:semicolon
)brace
DECL|variable|fops_bool
r_static
r_struct
id|file_operations
id|fops_bool
op_assign
(brace
dot
id|read
op_assign
id|read_file_bool
comma
dot
id|write
op_assign
id|write_file_bool
comma
dot
id|open
op_assign
id|default_open
comma
)brace
suffix:semicolon
multiline_comment|/**&n; * debugfs_create_bool - create a file in the debugfs filesystem that is used to read and write a boolean value.&n; *&n; * @name: a pointer to a string containing the name of the file to create.&n; * @mode: the permission that the file should have&n; * @parent: a pointer to the parent dentry for this file.  This should be a&n; *          directory dentry if set.  If this paramater is NULL, then the&n; *          file will be created in the root of the debugfs filesystem.&n; * @value: a pointer to the variable that the file should read to and write&n; *         from.&n; *&n; * This function creates a file in debugfs with the given name that&n; * contains the value of the variable @value.  If the @mode variable is so&n; * set, it can be read from, and written to.&n; *&n; * This function will return a pointer to a dentry if it succeeds.  This&n; * pointer must be passed to the debugfs_remove() function when the file is&n; * to be removed (no automatic cleanup happens if your module is unloaded,&n; * you are responsible here.)  If an error occurs, NULL will be returned.&n; *&n; * If debugfs is not enabled in the kernel, the value -ENODEV will be&n; * returned.  It is not wise to check for this value, but rather, check for&n; * NULL or !NULL instead as to eliminate the need for #ifdef in the calling&n; * code.&n; */
DECL|function|debugfs_create_bool
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
(brace
r_return
id|debugfs_create_file
c_func
(paren
id|name
comma
id|mode
comma
id|parent
comma
id|value
comma
op_amp
id|fops_bool
)paren
suffix:semicolon
)brace
DECL|variable|debugfs_create_bool
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|debugfs_create_bool
)paren
suffix:semicolon
eof
