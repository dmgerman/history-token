multiline_comment|/*&n; * Stub functions for the default security function pointers in case no&n; * security model is loaded.&n; *&n; * Copyright (C) 2001 WireX Communications, Inc &lt;chris@wirex.com&gt;&n; * Copyright (C) 2001 Greg Kroah-Hartman &lt;greg@kroah.com&gt;&n; * Copyright (C) 2001 Networks Associates Technology, Inc &lt;ssmalley@nai.com&gt;&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; */
DECL|macro|DEBUG
macro_line|#undef DEBUG
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/security.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/netlink.h&gt;
DECL|function|dummy_ptrace
r_static
r_int
id|dummy_ptrace
(paren
r_struct
id|task_struct
op_star
id|parent
comma
r_struct
id|task_struct
op_star
id|child
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dummy_capget
r_static
r_int
id|dummy_capget
(paren
r_struct
id|task_struct
op_star
id|target
comma
id|kernel_cap_t
op_star
id|effective
comma
id|kernel_cap_t
op_star
id|inheritable
comma
id|kernel_cap_t
op_star
id|permitted
)paren
(brace
op_star
id|effective
op_assign
op_star
id|inheritable
op_assign
op_star
id|permitted
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|issecure
c_func
(paren
id|SECURE_NOROOT
)paren
)paren
(brace
r_if
c_cond
(paren
id|target-&gt;euid
op_eq
l_int|0
)paren
(brace
op_star
id|permitted
op_or_assign
(paren
op_complement
l_int|0
op_amp
op_complement
id|CAP_FS_MASK
)paren
suffix:semicolon
op_star
id|effective
op_or_assign
(paren
op_complement
l_int|0
op_amp
op_complement
id|CAP_TO_MASK
c_func
(paren
id|CAP_SETPCAP
)paren
op_amp
op_complement
id|CAP_FS_MASK
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|target-&gt;fsuid
op_eq
l_int|0
)paren
(brace
op_star
id|permitted
op_or_assign
id|CAP_FS_MASK
suffix:semicolon
op_star
id|effective
op_or_assign
id|CAP_FS_MASK
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dummy_capset_check
r_static
r_int
id|dummy_capset_check
(paren
r_struct
id|task_struct
op_star
id|target
comma
id|kernel_cap_t
op_star
id|effective
comma
id|kernel_cap_t
op_star
id|inheritable
comma
id|kernel_cap_t
op_star
id|permitted
)paren
(brace
r_return
op_minus
id|EPERM
suffix:semicolon
)brace
DECL|function|dummy_capset_set
r_static
r_void
id|dummy_capset_set
(paren
r_struct
id|task_struct
op_star
id|target
comma
id|kernel_cap_t
op_star
id|effective
comma
id|kernel_cap_t
op_star
id|inheritable
comma
id|kernel_cap_t
op_star
id|permitted
)paren
(brace
r_return
suffix:semicolon
)brace
DECL|function|dummy_acct
r_static
r_int
id|dummy_acct
(paren
r_struct
id|file
op_star
id|file
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dummy_capable
r_static
r_int
id|dummy_capable
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
r_int
id|cap
)paren
(brace
r_if
c_cond
(paren
id|cap_is_fs_cap
(paren
id|cap
)paren
ques
c_cond
id|tsk-&gt;fsuid
op_eq
l_int|0
suffix:colon
id|tsk-&gt;euid
op_eq
l_int|0
)paren
multiline_comment|/* capability granted */
r_return
l_int|0
suffix:semicolon
multiline_comment|/* capability denied */
r_return
op_minus
id|EPERM
suffix:semicolon
)brace
DECL|function|dummy_quotactl
r_static
r_int
id|dummy_quotactl
(paren
r_int
id|cmds
comma
r_int
id|type
comma
r_int
id|id
comma
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dummy_quota_on
r_static
r_int
id|dummy_quota_on
(paren
r_struct
id|file
op_star
id|f
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dummy_bprm_alloc_security
r_static
r_int
id|dummy_bprm_alloc_security
(paren
r_struct
id|linux_binprm
op_star
id|bprm
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dummy_bprm_free_security
r_static
r_void
id|dummy_bprm_free_security
(paren
r_struct
id|linux_binprm
op_star
id|bprm
)paren
(brace
r_return
suffix:semicolon
)brace
DECL|function|dummy_bprm_compute_creds
r_static
r_void
id|dummy_bprm_compute_creds
(paren
r_struct
id|linux_binprm
op_star
id|bprm
)paren
(brace
r_return
suffix:semicolon
)brace
DECL|function|dummy_bprm_set_security
r_static
r_int
id|dummy_bprm_set_security
(paren
r_struct
id|linux_binprm
op_star
id|bprm
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dummy_bprm_check_security
r_static
r_int
id|dummy_bprm_check_security
(paren
r_struct
id|linux_binprm
op_star
id|bprm
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dummy_sb_alloc_security
r_static
r_int
id|dummy_sb_alloc_security
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dummy_sb_free_security
r_static
r_void
id|dummy_sb_free_security
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_return
suffix:semicolon
)brace
DECL|function|dummy_sb_statfs
r_static
r_int
id|dummy_sb_statfs
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dummy_sb_mount
r_static
r_int
id|dummy_sb_mount
(paren
r_char
op_star
id|dev_name
comma
r_struct
id|nameidata
op_star
id|nd
comma
r_char
op_star
id|type
comma
r_int
r_int
id|flags
comma
r_void
op_star
id|data
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dummy_sb_check_sb
r_static
r_int
id|dummy_sb_check_sb
(paren
r_struct
id|vfsmount
op_star
id|mnt
comma
r_struct
id|nameidata
op_star
id|nd
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dummy_sb_umount
r_static
r_int
id|dummy_sb_umount
(paren
r_struct
id|vfsmount
op_star
id|mnt
comma
r_int
id|flags
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dummy_sb_umount_close
r_static
r_void
id|dummy_sb_umount_close
(paren
r_struct
id|vfsmount
op_star
id|mnt
)paren
(brace
r_return
suffix:semicolon
)brace
DECL|function|dummy_sb_umount_busy
r_static
r_void
id|dummy_sb_umount_busy
(paren
r_struct
id|vfsmount
op_star
id|mnt
)paren
(brace
r_return
suffix:semicolon
)brace
DECL|function|dummy_sb_post_remount
r_static
r_void
id|dummy_sb_post_remount
(paren
r_struct
id|vfsmount
op_star
id|mnt
comma
r_int
r_int
id|flags
comma
r_void
op_star
id|data
)paren
(brace
r_return
suffix:semicolon
)brace
DECL|function|dummy_sb_post_mountroot
r_static
r_void
id|dummy_sb_post_mountroot
(paren
r_void
)paren
(brace
r_return
suffix:semicolon
)brace
DECL|function|dummy_sb_post_addmount
r_static
r_void
id|dummy_sb_post_addmount
(paren
r_struct
id|vfsmount
op_star
id|mnt
comma
r_struct
id|nameidata
op_star
id|nd
)paren
(brace
r_return
suffix:semicolon
)brace
DECL|function|dummy_sb_pivotroot
r_static
r_int
id|dummy_sb_pivotroot
(paren
r_struct
id|nameidata
op_star
id|old_nd
comma
r_struct
id|nameidata
op_star
id|new_nd
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dummy_sb_post_pivotroot
r_static
r_void
id|dummy_sb_post_pivotroot
(paren
r_struct
id|nameidata
op_star
id|old_nd
comma
r_struct
id|nameidata
op_star
id|new_nd
)paren
(brace
r_return
suffix:semicolon
)brace
DECL|function|dummy_inode_alloc_security
r_static
r_int
id|dummy_inode_alloc_security
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dummy_inode_free_security
r_static
r_void
id|dummy_inode_free_security
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_return
suffix:semicolon
)brace
DECL|function|dummy_inode_create
r_static
r_int
id|dummy_inode_create
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|dentry
op_star
id|dentry
comma
r_int
id|mask
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dummy_inode_post_create
r_static
r_void
id|dummy_inode_post_create
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|dentry
op_star
id|dentry
comma
r_int
id|mask
)paren
(brace
r_return
suffix:semicolon
)brace
DECL|function|dummy_inode_link
r_static
r_int
id|dummy_inode_link
(paren
r_struct
id|dentry
op_star
id|old_dentry
comma
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|dentry
op_star
id|new_dentry
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dummy_inode_post_link
r_static
r_void
id|dummy_inode_post_link
(paren
r_struct
id|dentry
op_star
id|old_dentry
comma
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|dentry
op_star
id|new_dentry
)paren
(brace
r_return
suffix:semicolon
)brace
DECL|function|dummy_inode_unlink
r_static
r_int
id|dummy_inode_unlink
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|dentry
op_star
id|dentry
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dummy_inode_symlink
r_static
r_int
id|dummy_inode_symlink
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|dentry
op_star
id|dentry
comma
r_const
r_char
op_star
id|name
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dummy_inode_post_symlink
r_static
r_void
id|dummy_inode_post_symlink
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|dentry
op_star
id|dentry
comma
r_const
r_char
op_star
id|name
)paren
(brace
r_return
suffix:semicolon
)brace
DECL|function|dummy_inode_mkdir
r_static
r_int
id|dummy_inode_mkdir
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|dentry
op_star
id|dentry
comma
r_int
id|mask
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dummy_inode_post_mkdir
r_static
r_void
id|dummy_inode_post_mkdir
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|dentry
op_star
id|dentry
comma
r_int
id|mask
)paren
(brace
r_return
suffix:semicolon
)brace
DECL|function|dummy_inode_rmdir
r_static
r_int
id|dummy_inode_rmdir
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|dentry
op_star
id|dentry
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dummy_inode_mknod
r_static
r_int
id|dummy_inode_mknod
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|dentry
op_star
id|dentry
comma
r_int
id|mode
comma
id|dev_t
id|dev
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dummy_inode_post_mknod
r_static
r_void
id|dummy_inode_post_mknod
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|dentry
op_star
id|dentry
comma
r_int
id|mode
comma
id|dev_t
id|dev
)paren
(brace
r_return
suffix:semicolon
)brace
DECL|function|dummy_inode_rename
r_static
r_int
id|dummy_inode_rename
(paren
r_struct
id|inode
op_star
id|old_inode
comma
r_struct
id|dentry
op_star
id|old_dentry
comma
r_struct
id|inode
op_star
id|new_inode
comma
r_struct
id|dentry
op_star
id|new_dentry
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dummy_inode_post_rename
r_static
r_void
id|dummy_inode_post_rename
(paren
r_struct
id|inode
op_star
id|old_inode
comma
r_struct
id|dentry
op_star
id|old_dentry
comma
r_struct
id|inode
op_star
id|new_inode
comma
r_struct
id|dentry
op_star
id|new_dentry
)paren
(brace
r_return
suffix:semicolon
)brace
DECL|function|dummy_inode_readlink
r_static
r_int
id|dummy_inode_readlink
(paren
r_struct
id|dentry
op_star
id|dentry
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dummy_inode_follow_link
r_static
r_int
id|dummy_inode_follow_link
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_struct
id|nameidata
op_star
id|nameidata
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dummy_inode_permission
r_static
r_int
id|dummy_inode_permission
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|mask
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dummy_inode_permission_lite
r_static
r_int
id|dummy_inode_permission_lite
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|mask
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dummy_inode_setattr
r_static
r_int
id|dummy_inode_setattr
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_struct
id|iattr
op_star
id|iattr
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dummy_inode_getattr
r_static
r_int
id|dummy_inode_getattr
(paren
r_struct
id|vfsmount
op_star
id|mnt
comma
r_struct
id|dentry
op_star
id|dentry
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dummy_inode_post_lookup
r_static
r_void
id|dummy_inode_post_lookup
(paren
r_struct
id|inode
op_star
id|ino
comma
r_struct
id|dentry
op_star
id|d
)paren
(brace
r_return
suffix:semicolon
)brace
DECL|function|dummy_inode_delete
r_static
r_void
id|dummy_inode_delete
(paren
r_struct
id|inode
op_star
id|ino
)paren
(brace
r_return
suffix:semicolon
)brace
DECL|function|dummy_inode_setxattr
r_static
r_int
id|dummy_inode_setxattr
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_char
op_star
id|name
comma
r_void
op_star
id|value
comma
r_int
id|size
comma
r_int
id|flags
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dummy_inode_getxattr
r_static
r_int
id|dummy_inode_getxattr
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_char
op_star
id|name
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dummy_inode_listxattr
r_static
r_int
id|dummy_inode_listxattr
(paren
r_struct
id|dentry
op_star
id|dentry
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dummy_inode_removexattr
r_static
r_int
id|dummy_inode_removexattr
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_char
op_star
id|name
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dummy_file_permission
r_static
r_int
id|dummy_file_permission
(paren
r_struct
id|file
op_star
id|file
comma
r_int
id|mask
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dummy_file_alloc_security
r_static
r_int
id|dummy_file_alloc_security
(paren
r_struct
id|file
op_star
id|file
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dummy_file_free_security
r_static
r_void
id|dummy_file_free_security
(paren
r_struct
id|file
op_star
id|file
)paren
(brace
r_return
suffix:semicolon
)brace
DECL|function|dummy_file_ioctl
r_static
r_int
id|dummy_file_ioctl
(paren
r_struct
id|file
op_star
id|file
comma
r_int
r_int
id|command
comma
r_int
r_int
id|arg
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dummy_file_mmap
r_static
r_int
id|dummy_file_mmap
(paren
r_struct
id|file
op_star
id|file
comma
r_int
r_int
id|prot
comma
r_int
r_int
id|flags
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dummy_file_mprotect
r_static
r_int
id|dummy_file_mprotect
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|prot
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dummy_file_lock
r_static
r_int
id|dummy_file_lock
(paren
r_struct
id|file
op_star
id|file
comma
r_int
r_int
id|cmd
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dummy_file_fcntl
r_static
r_int
id|dummy_file_fcntl
(paren
r_struct
id|file
op_star
id|file
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dummy_file_set_fowner
r_static
r_int
id|dummy_file_set_fowner
(paren
r_struct
id|file
op_star
id|file
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dummy_file_send_sigiotask
r_static
r_int
id|dummy_file_send_sigiotask
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
r_struct
id|fown_struct
op_star
id|fown
comma
r_int
id|fd
comma
r_int
id|reason
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dummy_file_receive
r_static
r_int
id|dummy_file_receive
(paren
r_struct
id|file
op_star
id|file
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dummy_task_create
r_static
r_int
id|dummy_task_create
(paren
r_int
r_int
id|clone_flags
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dummy_task_alloc_security
r_static
r_int
id|dummy_task_alloc_security
(paren
r_struct
id|task_struct
op_star
id|p
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dummy_task_free_security
r_static
r_void
id|dummy_task_free_security
(paren
r_struct
id|task_struct
op_star
id|p
)paren
(brace
r_return
suffix:semicolon
)brace
DECL|function|dummy_task_setuid
r_static
r_int
id|dummy_task_setuid
(paren
id|uid_t
id|id0
comma
id|uid_t
id|id1
comma
id|uid_t
id|id2
comma
r_int
id|flags
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dummy_task_post_setuid
r_static
r_int
id|dummy_task_post_setuid
(paren
id|uid_t
id|id0
comma
id|uid_t
id|id1
comma
id|uid_t
id|id2
comma
r_int
id|flags
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dummy_task_setgid
r_static
r_int
id|dummy_task_setgid
(paren
id|gid_t
id|id0
comma
id|gid_t
id|id1
comma
id|gid_t
id|id2
comma
r_int
id|flags
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dummy_task_setpgid
r_static
r_int
id|dummy_task_setpgid
(paren
r_struct
id|task_struct
op_star
id|p
comma
id|pid_t
id|pgid
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dummy_task_getpgid
r_static
r_int
id|dummy_task_getpgid
(paren
r_struct
id|task_struct
op_star
id|p
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dummy_task_getsid
r_static
r_int
id|dummy_task_getsid
(paren
r_struct
id|task_struct
op_star
id|p
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dummy_task_setgroups
r_static
r_int
id|dummy_task_setgroups
(paren
r_int
id|gidsetsize
comma
id|gid_t
op_star
id|grouplist
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dummy_task_setnice
r_static
r_int
id|dummy_task_setnice
(paren
r_struct
id|task_struct
op_star
id|p
comma
r_int
id|nice
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dummy_task_setrlimit
r_static
r_int
id|dummy_task_setrlimit
(paren
r_int
r_int
id|resource
comma
r_struct
id|rlimit
op_star
id|new_rlim
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dummy_task_setscheduler
r_static
r_int
id|dummy_task_setscheduler
(paren
r_struct
id|task_struct
op_star
id|p
comma
r_int
id|policy
comma
r_struct
id|sched_param
op_star
id|lp
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dummy_task_getscheduler
r_static
r_int
id|dummy_task_getscheduler
(paren
r_struct
id|task_struct
op_star
id|p
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dummy_task_wait
r_static
r_int
id|dummy_task_wait
(paren
r_struct
id|task_struct
op_star
id|p
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dummy_task_kill
r_static
r_int
id|dummy_task_kill
(paren
r_struct
id|task_struct
op_star
id|p
comma
r_struct
id|siginfo
op_star
id|info
comma
r_int
id|sig
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dummy_task_prctl
r_static
r_int
id|dummy_task_prctl
(paren
r_int
id|option
comma
r_int
r_int
id|arg2
comma
r_int
r_int
id|arg3
comma
r_int
r_int
id|arg4
comma
r_int
r_int
id|arg5
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dummy_task_kmod_set_label
r_static
r_void
id|dummy_task_kmod_set_label
(paren
r_void
)paren
(brace
r_return
suffix:semicolon
)brace
DECL|function|dummy_task_reparent_to_init
r_static
r_void
id|dummy_task_reparent_to_init
(paren
r_struct
id|task_struct
op_star
id|p
)paren
(brace
id|p-&gt;euid
op_assign
id|p-&gt;fsuid
op_assign
l_int|0
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|dummy_ipc_permission
r_static
r_int
id|dummy_ipc_permission
(paren
r_struct
id|kern_ipc_perm
op_star
id|ipcp
comma
r_int
id|flag
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dummy_msg_queue_alloc_security
r_static
r_int
id|dummy_msg_queue_alloc_security
(paren
r_struct
id|msg_queue
op_star
id|msq
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dummy_msg_queue_free_security
r_static
r_void
id|dummy_msg_queue_free_security
(paren
r_struct
id|msg_queue
op_star
id|msq
)paren
(brace
r_return
suffix:semicolon
)brace
DECL|function|dummy_shm_alloc_security
r_static
r_int
id|dummy_shm_alloc_security
(paren
r_struct
id|shmid_kernel
op_star
id|shp
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dummy_shm_free_security
r_static
r_void
id|dummy_shm_free_security
(paren
r_struct
id|shmid_kernel
op_star
id|shp
)paren
(brace
r_return
suffix:semicolon
)brace
DECL|function|dummy_sem_alloc_security
r_static
r_int
id|dummy_sem_alloc_security
(paren
r_struct
id|sem_array
op_star
id|sma
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dummy_sem_free_security
r_static
r_void
id|dummy_sem_free_security
(paren
r_struct
id|sem_array
op_star
id|sma
)paren
(brace
r_return
suffix:semicolon
)brace
DECL|function|dummy_register_security
r_static
r_int
id|dummy_register_security
(paren
r_const
r_char
op_star
id|name
comma
r_struct
id|security_operations
op_star
id|ops
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|dummy_unregister_security
r_static
r_int
id|dummy_unregister_security
(paren
r_const
r_char
op_star
id|name
comma
r_struct
id|security_operations
op_star
id|ops
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|variable|dummy_security_ops
r_struct
id|security_operations
id|dummy_security_ops
suffix:semicolon
DECL|macro|set_to_dummy_if_null
mdefine_line|#define set_to_dummy_if_null(ops, function)&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if (!ops-&gt;function) {&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;ops-&gt;function = dummy_##function;&t;&t;&bslash;&n;&t;&t;&t;pr_debug(&quot;Had to override the &quot; #function&t;&bslash;&n;&t;&t;&t;&t; &quot; security operation with the dummy one.&bslash;n&quot;);&bslash;&n;&t;&t;&t;}&t;&t;&t;&t;&t;&t;&bslash;&n;&t;} while (0)
DECL|function|security_fixup_ops
r_void
id|security_fixup_ops
(paren
r_struct
id|security_operations
op_star
id|ops
)paren
(brace
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|ptrace
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|capget
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|capset_check
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|capset_set
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|acct
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|capable
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|quotactl
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|quota_on
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|bprm_alloc_security
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|bprm_free_security
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|bprm_compute_creds
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|bprm_set_security
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|bprm_check_security
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|sb_alloc_security
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|sb_free_security
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|sb_statfs
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|sb_mount
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|sb_check_sb
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|sb_umount
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|sb_umount_close
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|sb_umount_busy
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|sb_post_remount
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|sb_post_mountroot
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|sb_post_addmount
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|sb_pivotroot
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|sb_post_pivotroot
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|inode_alloc_security
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|inode_free_security
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|inode_create
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|inode_post_create
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|inode_link
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|inode_post_link
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|inode_unlink
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|inode_symlink
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|inode_post_symlink
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|inode_mkdir
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|inode_post_mkdir
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|inode_rmdir
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|inode_mknod
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|inode_post_mknod
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|inode_rename
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|inode_post_rename
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|inode_readlink
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|inode_follow_link
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|inode_permission
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|inode_permission_lite
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|inode_setattr
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|inode_getattr
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|inode_post_lookup
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|inode_delete
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|inode_setxattr
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|inode_getxattr
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|inode_listxattr
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|inode_removexattr
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|file_permission
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|file_alloc_security
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|file_free_security
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|file_ioctl
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|file_mmap
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|file_mprotect
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|file_lock
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|file_fcntl
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|file_set_fowner
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|file_send_sigiotask
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|file_receive
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|task_create
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|task_alloc_security
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|task_free_security
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|task_setuid
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|task_post_setuid
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|task_setgid
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|task_setpgid
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|task_getpgid
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|task_getsid
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|task_setgroups
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|task_setnice
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|task_setrlimit
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|task_setscheduler
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|task_getscheduler
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|task_wait
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|task_kill
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|task_prctl
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|task_kmod_set_label
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|task_reparent_to_init
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|ipc_permission
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|msg_queue_alloc_security
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|msg_queue_free_security
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|shm_alloc_security
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|shm_free_security
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|sem_alloc_security
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|sem_free_security
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|register_security
)paren
suffix:semicolon
id|set_to_dummy_if_null
c_func
(paren
id|ops
comma
id|unregister_security
)paren
suffix:semicolon
)brace
eof
