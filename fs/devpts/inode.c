multiline_comment|/* -*- linux-c -*- --------------------------------------------------------- *&n; *&n; * linux/fs/devpts/inode.c&n; *&n; *  Copyright 1998 H. Peter Anvin -- All Rights Reserved&n; *&n; * This file is part of the Linux kernel and is made available under&n; * the terms of the GNU General Public License, version 2, or at your&n; * option, any later version, incorporated herein by reference.&n; *&n; * ------------------------------------------------------------------------- */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/namei.h&gt;
macro_line|#include &lt;linux/mount.h&gt;
macro_line|#include &quot;xattr.h&quot;
DECL|macro|DEVPTS_SUPER_MAGIC
mdefine_line|#define DEVPTS_SUPER_MAGIC 0x1cd1
DECL|variable|devpts_mnt
r_static
r_struct
id|vfsmount
op_star
id|devpts_mnt
suffix:semicolon
DECL|variable|devpts_root
r_static
r_struct
id|dentry
op_star
id|devpts_root
suffix:semicolon
r_static
r_struct
(brace
DECL|member|setuid
r_int
id|setuid
suffix:semicolon
DECL|member|setgid
r_int
id|setgid
suffix:semicolon
DECL|member|uid
id|uid_t
id|uid
suffix:semicolon
DECL|member|gid
id|gid_t
id|gid
suffix:semicolon
DECL|member|mode
id|umode_t
id|mode
suffix:semicolon
DECL|variable|config
)brace
id|config
op_assign
(brace
dot
id|mode
op_assign
l_int|0600
)brace
suffix:semicolon
DECL|function|devpts_remount
r_static
r_int
id|devpts_remount
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
op_star
id|flags
comma
r_char
op_star
id|data
)paren
(brace
r_int
id|setuid
op_assign
l_int|0
suffix:semicolon
r_int
id|setgid
op_assign
l_int|0
suffix:semicolon
id|uid_t
id|uid
op_assign
l_int|0
suffix:semicolon
id|gid_t
id|gid
op_assign
l_int|0
suffix:semicolon
id|umode_t
id|mode
op_assign
l_int|0600
suffix:semicolon
r_char
op_star
id|this_char
suffix:semicolon
id|this_char
op_assign
l_int|NULL
suffix:semicolon
r_while
c_loop
(paren
(paren
id|this_char
op_assign
id|strsep
c_func
(paren
op_amp
id|data
comma
l_string|&quot;,&quot;
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
r_int
id|n
suffix:semicolon
r_char
id|dummy
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|this_char
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|sscanf
c_func
(paren
id|this_char
comma
l_string|&quot;uid=%i%c&quot;
comma
op_amp
id|n
comma
op_amp
id|dummy
)paren
op_eq
l_int|1
)paren
(brace
id|setuid
op_assign
l_int|1
suffix:semicolon
id|uid
op_assign
id|n
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|sscanf
c_func
(paren
id|this_char
comma
l_string|&quot;gid=%i%c&quot;
comma
op_amp
id|n
comma
op_amp
id|dummy
)paren
op_eq
l_int|1
)paren
(brace
id|setgid
op_assign
l_int|1
suffix:semicolon
id|gid
op_assign
id|n
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|sscanf
c_func
(paren
id|this_char
comma
l_string|&quot;mode=%o%c&quot;
comma
op_amp
id|n
comma
op_amp
id|dummy
)paren
op_eq
l_int|1
)paren
id|mode
op_assign
id|n
op_amp
op_complement
id|S_IFMT
suffix:semicolon
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;devpts: called with bogus options&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
)brace
id|config.setuid
op_assign
id|setuid
suffix:semicolon
id|config.setgid
op_assign
id|setgid
suffix:semicolon
id|config.uid
op_assign
id|uid
suffix:semicolon
id|config.gid
op_assign
id|gid
suffix:semicolon
id|config.mode
op_assign
id|mode
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|devpts_sops
r_static
r_struct
id|super_operations
id|devpts_sops
op_assign
(brace
dot
id|statfs
op_assign
id|simple_statfs
comma
dot
id|remount_fs
op_assign
id|devpts_remount
comma
)brace
suffix:semicolon
r_static
r_int
DECL|function|devpts_fill_super
id|devpts_fill_super
c_func
(paren
r_struct
id|super_block
op_star
id|s
comma
r_void
op_star
id|data
comma
r_int
id|silent
)paren
(brace
r_struct
id|inode
op_star
id|inode
suffix:semicolon
id|s-&gt;s_blocksize
op_assign
l_int|1024
suffix:semicolon
id|s-&gt;s_blocksize_bits
op_assign
l_int|10
suffix:semicolon
id|s-&gt;s_magic
op_assign
id|DEVPTS_SUPER_MAGIC
suffix:semicolon
id|s-&gt;s_op
op_assign
op_amp
id|devpts_sops
suffix:semicolon
id|inode
op_assign
id|new_inode
c_func
(paren
id|s
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
)paren
r_goto
id|fail
suffix:semicolon
id|inode-&gt;i_ino
op_assign
l_int|1
suffix:semicolon
id|inode-&gt;i_mtime
op_assign
id|inode-&gt;i_atime
op_assign
id|inode-&gt;i_ctime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|inode-&gt;i_blocks
op_assign
l_int|0
suffix:semicolon
id|inode-&gt;i_blksize
op_assign
l_int|1024
suffix:semicolon
id|inode-&gt;i_uid
op_assign
id|inode-&gt;i_gid
op_assign
l_int|0
suffix:semicolon
id|inode-&gt;i_mode
op_assign
id|S_IFDIR
op_or
id|S_IRUGO
op_or
id|S_IXUGO
op_or
id|S_IWUSR
suffix:semicolon
id|inode-&gt;i_op
op_assign
op_amp
id|simple_dir_inode_operations
suffix:semicolon
id|inode-&gt;i_fop
op_assign
op_amp
id|simple_dir_operations
suffix:semicolon
id|inode-&gt;i_nlink
op_assign
l_int|2
suffix:semicolon
id|devpts_root
op_assign
id|s-&gt;s_root
op_assign
id|d_alloc_root
c_func
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|s-&gt;s_root
)paren
r_return
l_int|0
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;devpts: get root dentry failed&bslash;n&quot;
)paren
suffix:semicolon
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
id|fail
suffix:colon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
DECL|function|devpts_get_sb
r_static
r_struct
id|super_block
op_star
id|devpts_get_sb
c_func
(paren
r_struct
id|file_system_type
op_star
id|fs_type
comma
r_int
id|flags
comma
r_const
r_char
op_star
id|dev_name
comma
r_void
op_star
id|data
)paren
(brace
r_return
id|get_sb_single
c_func
(paren
id|fs_type
comma
id|flags
comma
id|data
comma
id|devpts_fill_super
)paren
suffix:semicolon
)brace
DECL|variable|devpts_fs_type
r_static
r_struct
id|file_system_type
id|devpts_fs_type
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|name
op_assign
l_string|&quot;devpts&quot;
comma
dot
id|get_sb
op_assign
id|devpts_get_sb
comma
dot
id|kill_sb
op_assign
id|kill_anon_super
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * The normal naming convention is simply /dev/pts/&lt;number&gt;; this conforms&n; * to the System V naming convention&n; */
DECL|function|get_node
r_static
r_struct
id|dentry
op_star
id|get_node
c_func
(paren
r_int
id|num
)paren
(brace
r_char
id|s
(braket
l_int|10
)braket
suffix:semicolon
r_struct
id|dentry
op_star
id|root
op_assign
id|devpts_root
suffix:semicolon
id|down
c_func
(paren
op_amp
id|root-&gt;d_inode-&gt;i_sem
)paren
suffix:semicolon
r_return
id|lookup_one_len
c_func
(paren
id|s
comma
id|root
comma
id|sprintf
c_func
(paren
id|s
comma
l_string|&quot;%d&quot;
comma
id|num
)paren
)paren
suffix:semicolon
)brace
DECL|variable|devpts_file_inode_operations
r_static
r_struct
id|inode_operations
id|devpts_file_inode_operations
op_assign
(brace
dot
id|setxattr
op_assign
id|devpts_setxattr
comma
dot
id|getxattr
op_assign
id|devpts_getxattr
comma
dot
id|listxattr
op_assign
id|devpts_listxattr
comma
dot
id|removexattr
op_assign
id|devpts_removexattr
comma
)brace
suffix:semicolon
DECL|function|devpts_pty_new
r_void
id|devpts_pty_new
c_func
(paren
r_int
id|number
comma
id|dev_t
id|device
)paren
(brace
r_struct
id|dentry
op_star
id|dentry
suffix:semicolon
r_struct
id|inode
op_star
id|inode
op_assign
id|new_inode
c_func
(paren
id|devpts_mnt-&gt;mnt_sb
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
)paren
r_return
suffix:semicolon
id|inode-&gt;i_ino
op_assign
id|number
op_plus
l_int|2
suffix:semicolon
id|inode-&gt;i_blksize
op_assign
l_int|1024
suffix:semicolon
id|inode-&gt;i_uid
op_assign
id|config.setuid
ques
c_cond
id|config.uid
suffix:colon
id|current-&gt;fsuid
suffix:semicolon
id|inode-&gt;i_gid
op_assign
id|config.setgid
ques
c_cond
id|config.gid
suffix:colon
id|current-&gt;fsgid
suffix:semicolon
id|inode-&gt;i_mtime
op_assign
id|inode-&gt;i_atime
op_assign
id|inode-&gt;i_ctime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|init_special_inode
c_func
(paren
id|inode
comma
id|S_IFCHR
op_or
id|config.mode
comma
id|device
)paren
suffix:semicolon
id|inode-&gt;i_op
op_assign
op_amp
id|devpts_file_inode_operations
suffix:semicolon
id|dentry
op_assign
id|get_node
c_func
(paren
id|number
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|IS_ERR
c_func
(paren
id|dentry
)paren
op_logical_and
op_logical_neg
id|dentry-&gt;d_inode
)paren
id|d_instantiate
c_func
(paren
id|dentry
comma
id|inode
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|devpts_root-&gt;d_inode-&gt;i_sem
)paren
suffix:semicolon
)brace
DECL|function|devpts_pty_kill
r_void
id|devpts_pty_kill
c_func
(paren
r_int
id|number
)paren
(brace
r_struct
id|dentry
op_star
id|dentry
op_assign
id|get_node
c_func
(paren
id|number
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|IS_ERR
c_func
(paren
id|dentry
)paren
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
r_if
c_cond
(paren
id|inode
)paren
(brace
id|inode-&gt;i_nlink
op_decrement
suffix:semicolon
id|d_delete
c_func
(paren
id|dentry
)paren
suffix:semicolon
id|dput
c_func
(paren
id|dentry
)paren
suffix:semicolon
)brace
id|dput
c_func
(paren
id|dentry
)paren
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|devpts_root-&gt;d_inode-&gt;i_sem
)paren
suffix:semicolon
)brace
DECL|function|init_devpts_fs
r_static
r_int
id|__init
id|init_devpts_fs
c_func
(paren
r_void
)paren
(brace
r_int
id|err
op_assign
id|init_devpts_xattr
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_return
id|err
suffix:semicolon
id|err
op_assign
id|register_filesystem
c_func
(paren
op_amp
id|devpts_fs_type
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|err
)paren
(brace
id|devpts_mnt
op_assign
id|kern_mount
c_func
(paren
op_amp
id|devpts_fs_type
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|devpts_mnt
)paren
)paren
id|err
op_assign
id|PTR_ERR
c_func
(paren
id|devpts_mnt
)paren
suffix:semicolon
)brace
r_return
id|err
suffix:semicolon
)brace
DECL|function|exit_devpts_fs
r_static
r_void
id|__exit
id|exit_devpts_fs
c_func
(paren
r_void
)paren
(brace
id|unregister_filesystem
c_func
(paren
op_amp
id|devpts_fs_type
)paren
suffix:semicolon
id|mntput
c_func
(paren
id|devpts_mnt
)paren
suffix:semicolon
id|exit_devpts_xattr
c_func
(paren
)paren
suffix:semicolon
)brace
id|module_init
c_func
(paren
id|init_devpts_fs
)paren
id|module_exit
c_func
(paren
id|exit_devpts_fs
)paren
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
