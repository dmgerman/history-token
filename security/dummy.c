multiline_comment|/*&n; * Stub functions for the default security function pointers in case no&n; * security model is loaded.&n; *&n; * Copyright (C) 2001 WireX Communications, Inc &lt;chris@wirex.com&gt;&n; * Copyright (C) 2001 Greg Kroah-Hartman &lt;greg@kroah.com&gt;&n; * Copyright (C) 2001 Networks Associates Technology, Inc &lt;ssmalley@nai.com&gt;&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; */
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
l_int|0
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
DECL|function|dummy_mount
r_static
r_int
id|dummy_mount
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
DECL|function|dummy_check_sb
r_static
r_int
id|dummy_check_sb
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
DECL|function|dummy_umount
r_static
r_int
id|dummy_umount
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
DECL|function|dummy_umount_close
r_static
r_void
id|dummy_umount_close
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
DECL|function|dummy_umount_busy
r_static
r_void
id|dummy_umount_busy
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
DECL|function|dummy_post_remount
r_static
r_void
id|dummy_post_remount
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
DECL|function|dummy_post_mountroot
r_static
r_void
id|dummy_post_mountroot
(paren
r_void
)paren
(brace
r_return
suffix:semicolon
)brace
DECL|function|dummy_post_addmount
r_static
r_void
id|dummy_post_addmount
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
DECL|function|dummy_pivotroot
r_static
r_int
id|dummy_pivotroot
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
DECL|function|dummy_post_pivotroot
r_static
r_void
id|dummy_post_pivotroot
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
id|major
comma
id|dev_t
id|minor
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
id|major
comma
id|dev_t
id|minor
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
DECL|function|dummy_post_lookup
r_static
r_void
id|dummy_post_lookup
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
DECL|function|dummy_delete
r_static
r_void
id|dummy_delete
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
DECL|function|dummy_register
r_static
r_int
id|dummy_register
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
DECL|function|dummy_unregister
r_static
r_int
id|dummy_unregister
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
op_assign
(brace
dot
id|ptrace
op_assign
id|dummy_ptrace
comma
dot
id|capget
op_assign
id|dummy_capget
comma
dot
id|capset_check
op_assign
id|dummy_capset_check
comma
dot
id|capset_set
op_assign
id|dummy_capset_set
comma
dot
id|acct
op_assign
id|dummy_acct
comma
dot
id|capable
op_assign
id|dummy_capable
comma
dot
id|quotactl
op_assign
id|dummy_quotactl
comma
dot
id|quota_on
op_assign
id|dummy_quota_on
comma
dot
id|bprm_alloc_security
op_assign
id|dummy_bprm_alloc_security
comma
dot
id|bprm_free_security
op_assign
id|dummy_bprm_free_security
comma
dot
id|bprm_compute_creds
op_assign
id|dummy_bprm_compute_creds
comma
dot
id|bprm_set_security
op_assign
id|dummy_bprm_set_security
comma
dot
id|bprm_check_security
op_assign
id|dummy_bprm_check_security
comma
dot
id|sb_alloc_security
op_assign
id|dummy_sb_alloc_security
comma
dot
id|sb_free_security
op_assign
id|dummy_sb_free_security
comma
dot
id|sb_statfs
op_assign
id|dummy_sb_statfs
comma
dot
id|sb_mount
op_assign
id|dummy_mount
comma
dot
id|sb_check_sb
op_assign
id|dummy_check_sb
comma
dot
id|sb_umount
op_assign
id|dummy_umount
comma
dot
id|sb_umount_close
op_assign
id|dummy_umount_close
comma
dot
id|sb_umount_busy
op_assign
id|dummy_umount_busy
comma
dot
id|sb_post_remount
op_assign
id|dummy_post_remount
comma
dot
id|sb_post_mountroot
op_assign
id|dummy_post_mountroot
comma
dot
id|sb_post_addmount
op_assign
id|dummy_post_addmount
comma
dot
id|sb_pivotroot
op_assign
id|dummy_pivotroot
comma
dot
id|sb_post_pivotroot
op_assign
id|dummy_post_pivotroot
comma
dot
id|inode_alloc_security
op_assign
id|dummy_inode_alloc_security
comma
dot
id|inode_free_security
op_assign
id|dummy_inode_free_security
comma
dot
id|inode_create
op_assign
id|dummy_inode_create
comma
dot
id|inode_post_create
op_assign
id|dummy_inode_post_create
comma
dot
id|inode_link
op_assign
id|dummy_inode_link
comma
dot
id|inode_post_link
op_assign
id|dummy_inode_post_link
comma
dot
id|inode_unlink
op_assign
id|dummy_inode_unlink
comma
dot
id|inode_symlink
op_assign
id|dummy_inode_symlink
comma
dot
id|inode_post_symlink
op_assign
id|dummy_inode_post_symlink
comma
dot
id|inode_mkdir
op_assign
id|dummy_inode_mkdir
comma
dot
id|inode_post_mkdir
op_assign
id|dummy_inode_post_mkdir
comma
dot
id|inode_rmdir
op_assign
id|dummy_inode_rmdir
comma
dot
id|inode_mknod
op_assign
id|dummy_inode_mknod
comma
dot
id|inode_post_mknod
op_assign
id|dummy_inode_post_mknod
comma
dot
id|inode_rename
op_assign
id|dummy_inode_rename
comma
dot
id|inode_post_rename
op_assign
id|dummy_inode_post_rename
comma
dot
id|inode_readlink
op_assign
id|dummy_inode_readlink
comma
dot
id|inode_follow_link
op_assign
id|dummy_inode_follow_link
comma
dot
id|inode_permission
op_assign
id|dummy_inode_permission
comma
dot
id|inode_permission_lite
op_assign
id|dummy_inode_permission_lite
comma
dot
id|inode_setattr
op_assign
id|dummy_inode_setattr
comma
dot
id|inode_getattr
op_assign
id|dummy_inode_getattr
comma
dot
id|inode_post_lookup
op_assign
id|dummy_post_lookup
comma
dot
id|inode_delete
op_assign
id|dummy_delete
comma
dot
id|inode_setxattr
op_assign
id|dummy_inode_setxattr
comma
dot
id|inode_getxattr
op_assign
id|dummy_inode_getxattr
comma
dot
id|inode_listxattr
op_assign
id|dummy_inode_listxattr
comma
dot
id|inode_removexattr
op_assign
id|dummy_inode_removexattr
comma
dot
id|file_permission
op_assign
id|dummy_file_permission
comma
dot
id|file_alloc_security
op_assign
id|dummy_file_alloc_security
comma
dot
id|file_free_security
op_assign
id|dummy_file_free_security
comma
dot
id|file_ioctl
op_assign
id|dummy_file_ioctl
comma
dot
id|file_mmap
op_assign
id|dummy_file_mmap
comma
dot
id|file_mprotect
op_assign
id|dummy_file_mprotect
comma
dot
id|file_lock
op_assign
id|dummy_file_lock
comma
dot
id|file_fcntl
op_assign
id|dummy_file_fcntl
comma
dot
id|file_set_fowner
op_assign
id|dummy_file_set_fowner
comma
dot
id|file_send_sigiotask
op_assign
id|dummy_file_send_sigiotask
comma
dot
id|file_receive
op_assign
id|dummy_file_receive
comma
dot
id|task_create
op_assign
id|dummy_task_create
comma
dot
id|task_alloc_security
op_assign
id|dummy_task_alloc_security
comma
dot
id|task_free_security
op_assign
id|dummy_task_free_security
comma
dot
id|task_setuid
op_assign
id|dummy_task_setuid
comma
dot
id|task_post_setuid
op_assign
id|dummy_task_post_setuid
comma
dot
id|task_setgid
op_assign
id|dummy_task_setgid
comma
dot
id|task_setpgid
op_assign
id|dummy_task_setpgid
comma
dot
id|task_getpgid
op_assign
id|dummy_task_getpgid
comma
dot
id|task_getsid
op_assign
id|dummy_task_getsid
comma
dot
id|task_setgroups
op_assign
id|dummy_task_setgroups
comma
dot
id|task_setnice
op_assign
id|dummy_task_setnice
comma
dot
id|task_setrlimit
op_assign
id|dummy_task_setrlimit
comma
dot
id|task_setscheduler
op_assign
id|dummy_task_setscheduler
comma
dot
id|task_getscheduler
op_assign
id|dummy_task_getscheduler
comma
dot
id|task_wait
op_assign
id|dummy_task_wait
comma
dot
id|task_kill
op_assign
id|dummy_task_kill
comma
dot
id|task_prctl
op_assign
id|dummy_task_prctl
comma
dot
id|task_kmod_set_label
op_assign
id|dummy_task_kmod_set_label
comma
dot
id|task_reparent_to_init
op_assign
id|dummy_task_reparent_to_init
comma
dot
id|ipc_permission
op_assign
id|dummy_ipc_permission
comma
dot
id|msg_queue_alloc_security
op_assign
id|dummy_msg_queue_alloc_security
comma
dot
id|msg_queue_free_security
op_assign
id|dummy_msg_queue_free_security
comma
dot
id|shm_alloc_security
op_assign
id|dummy_shm_alloc_security
comma
dot
id|shm_free_security
op_assign
id|dummy_shm_free_security
comma
dot
id|sem_alloc_security
op_assign
id|dummy_sem_alloc_security
comma
dot
id|sem_free_security
op_assign
id|dummy_sem_free_security
comma
dot
id|register_security
op_assign
id|dummy_register
comma
dot
id|unregister_security
op_assign
id|dummy_unregister
comma
)brace
suffix:semicolon
eof
