multiline_comment|/*&n; *  linux/fs/proc/root.c&n; *&n; *  Copyright (C) 1991, 1992 Linus Torvalds&n; *&n; *  proc root directory handling functions&n; */
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
DECL|variable|proc_net
DECL|variable|proc_bus
DECL|variable|proc_root_fs
DECL|variable|proc_root_driver
r_struct
id|proc_dir_entry
op_star
id|proc_net
comma
op_star
id|proc_bus
comma
op_star
id|proc_root_fs
comma
op_star
id|proc_root_driver
suffix:semicolon
macro_line|#ifdef CONFIG_SYSCTL
DECL|variable|proc_sys_root
r_struct
id|proc_dir_entry
op_star
id|proc_sys_root
suffix:semicolon
macro_line|#endif
r_static
id|DECLARE_FSTYPE
c_func
(paren
id|proc_fs_type
comma
l_string|&quot;proc&quot;
comma
id|proc_read_super
comma
id|FS_SINGLE
)paren
suffix:semicolon
DECL|function|proc_root_init
r_void
id|__init
id|proc_root_init
c_func
(paren
r_void
)paren
(brace
r_int
id|err
op_assign
id|register_filesystem
c_func
(paren
op_amp
id|proc_fs_type
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_return
suffix:semicolon
id|proc_mnt
op_assign
id|kern_mount
c_func
(paren
op_amp
id|proc_fs_type
)paren
suffix:semicolon
id|err
op_assign
id|PTR_ERR
c_func
(paren
id|proc_mnt
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|proc_mnt
)paren
)paren
(brace
id|unregister_filesystem
c_func
(paren
op_amp
id|proc_fs_type
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|proc_misc_init
c_func
(paren
)paren
suffix:semicolon
id|proc_net
op_assign
id|proc_mkdir
c_func
(paren
l_string|&quot;net&quot;
comma
l_int|0
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SYSVIPC
id|proc_mkdir
c_func
(paren
l_string|&quot;sysvipc&quot;
comma
l_int|0
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_SYSCTL
id|proc_sys_root
op_assign
id|proc_mkdir
c_func
(paren
l_string|&quot;sys&quot;
comma
l_int|0
)paren
suffix:semicolon
macro_line|#endif
id|proc_root_fs
op_assign
id|proc_mkdir
c_func
(paren
l_string|&quot;fs&quot;
comma
l_int|0
)paren
suffix:semicolon
id|proc_root_driver
op_assign
id|proc_mkdir
c_func
(paren
l_string|&quot;driver&quot;
comma
l_int|0
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_SUN_OPENPROMFS) || defined(CONFIG_SUN_OPENPROMFS_MODULE)
multiline_comment|/* just give it a mountpoint */
id|proc_mkdir
c_func
(paren
l_string|&quot;openprom&quot;
comma
l_int|0
)paren
suffix:semicolon
macro_line|#endif
id|proc_tty_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PROC_DEVICETREE
id|proc_device_tree_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_PPC_RTAS
id|proc_rtas_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|proc_bus
op_assign
id|proc_mkdir
c_func
(paren
l_string|&quot;bus&quot;
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|proc_root_lookup
r_static
r_struct
id|dentry
op_star
id|proc_root_lookup
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|dentry
op_star
id|dentry
)paren
(brace
r_if
c_cond
(paren
id|dir-&gt;i_ino
op_eq
id|PROC_ROOT_INO
)paren
(brace
multiline_comment|/* check for safety... */
r_int
id|nlink
op_assign
id|proc_root.nlink
suffix:semicolon
id|nlink
op_add_assign
id|nr_threads
suffix:semicolon
id|dir-&gt;i_nlink
op_assign
id|nlink
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|proc_lookup
c_func
(paren
id|dir
comma
id|dentry
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
r_return
id|proc_pid_lookup
c_func
(paren
id|dir
comma
id|dentry
)paren
suffix:semicolon
)brace
DECL|function|proc_root_readdir
r_static
r_int
id|proc_root_readdir
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
r_void
op_star
id|dirent
comma
id|filldir_t
id|filldir
)paren
(brace
r_int
r_int
id|nr
op_assign
id|filp-&gt;f_pos
suffix:semicolon
r_if
c_cond
(paren
id|nr
OL
id|FIRST_PROCESS_ENTRY
)paren
(brace
r_int
id|error
op_assign
id|proc_readdir
c_func
(paren
id|filp
comma
id|dirent
comma
id|filldir
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
op_le
l_int|0
)paren
r_return
id|error
suffix:semicolon
id|filp-&gt;f_pos
op_assign
id|FIRST_PROCESS_ENTRY
suffix:semicolon
)brace
r_return
id|proc_pid_readdir
c_func
(paren
id|filp
comma
id|dirent
comma
id|filldir
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * The root /proc directory is special, as it has the&n; * &lt;pid&gt; directories. Thus we don&squot;t use the generic&n; * directory handling functions for that..&n; */
DECL|variable|proc_root_operations
r_static
r_struct
id|file_operations
id|proc_root_operations
op_assign
(brace
id|read
suffix:colon
id|generic_read_dir
comma
id|readdir
suffix:colon
id|proc_root_readdir
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * proc root can do almost nothing..&n; */
DECL|variable|proc_root_inode_operations
r_static
r_struct
id|inode_operations
id|proc_root_inode_operations
op_assign
(brace
id|lookup
suffix:colon
id|proc_root_lookup
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * This is the root &quot;inode&quot; in the /proc tree..&n; */
DECL|variable|proc_root
r_struct
id|proc_dir_entry
id|proc_root
op_assign
(brace
id|low_ino
suffix:colon
id|PROC_ROOT_INO
comma
id|namelen
suffix:colon
l_int|5
comma
id|name
suffix:colon
l_string|&quot;/proc&quot;
comma
id|mode
suffix:colon
id|S_IFDIR
op_or
id|S_IRUGO
op_or
id|S_IXUGO
comma
id|nlink
suffix:colon
l_int|2
comma
id|proc_iops
suffix:colon
op_amp
id|proc_root_inode_operations
comma
id|proc_fops
suffix:colon
op_amp
id|proc_root_operations
comma
id|parent
suffix:colon
op_amp
id|proc_root
comma
)brace
suffix:semicolon
macro_line|#ifdef CONFIG_SYSCTL
DECL|variable|proc_sys_root
id|EXPORT_SYMBOL
c_func
(paren
id|proc_sys_root
)paren
suffix:semicolon
macro_line|#endif
DECL|variable|proc_symlink
id|EXPORT_SYMBOL
c_func
(paren
id|proc_symlink
)paren
suffix:semicolon
DECL|variable|proc_mknod
id|EXPORT_SYMBOL
c_func
(paren
id|proc_mknod
)paren
suffix:semicolon
DECL|variable|proc_mkdir
id|EXPORT_SYMBOL
c_func
(paren
id|proc_mkdir
)paren
suffix:semicolon
DECL|variable|create_proc_entry
id|EXPORT_SYMBOL
c_func
(paren
id|create_proc_entry
)paren
suffix:semicolon
DECL|variable|remove_proc_entry
id|EXPORT_SYMBOL
c_func
(paren
id|remove_proc_entry
)paren
suffix:semicolon
DECL|variable|proc_root
id|EXPORT_SYMBOL
c_func
(paren
id|proc_root
)paren
suffix:semicolon
DECL|variable|proc_root_fs
id|EXPORT_SYMBOL
c_func
(paren
id|proc_root_fs
)paren
suffix:semicolon
DECL|variable|proc_net
id|EXPORT_SYMBOL
c_func
(paren
id|proc_net
)paren
suffix:semicolon
DECL|variable|proc_bus
id|EXPORT_SYMBOL
c_func
(paren
id|proc_bus
)paren
suffix:semicolon
DECL|variable|proc_root_driver
id|EXPORT_SYMBOL
c_func
(paren
id|proc_root_driver
)paren
suffix:semicolon
eof
