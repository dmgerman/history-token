multiline_comment|/*&n; *  Capabilities Linux Security Module&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/security.h&gt;
macro_line|#include &lt;linux/file.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/netlink.h&gt;
multiline_comment|/* flag to keep track of how we were registered */
DECL|variable|secondary
r_static
r_int
id|secondary
suffix:semicolon
DECL|function|cap_capable
r_static
r_int
id|cap_capable
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
multiline_comment|/* Derived from include/linux/sched.h:capable. */
r_if
c_cond
(paren
id|cap_raised
(paren
id|tsk-&gt;cap_effective
comma
id|cap
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_else
r_return
op_minus
id|EPERM
suffix:semicolon
)brace
DECL|function|cap_sys_security
r_static
r_int
id|cap_sys_security
(paren
r_int
r_int
id|id
comma
r_int
r_int
id|call
comma
r_int
r_int
op_star
id|args
)paren
(brace
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
DECL|function|cap_quotactl
r_static
r_int
id|cap_quotactl
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
DECL|function|cap_quota_on
r_static
r_int
id|cap_quota_on
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
DECL|function|cap_ptrace
r_static
r_int
id|cap_ptrace
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
multiline_comment|/* Derived from arch/i386/kernel/ptrace.c:sys_ptrace. */
r_if
c_cond
(paren
op_logical_neg
id|cap_issubset
(paren
id|child-&gt;cap_permitted
comma
id|current-&gt;cap_permitted
)paren
op_logical_and
op_logical_neg
id|capable
(paren
id|CAP_SYS_PTRACE
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
r_else
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cap_capget
r_static
r_int
id|cap_capget
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
multiline_comment|/* Derived from kernel/capability.c:sys_capget. */
op_star
id|effective
op_assign
id|cap_t
(paren
id|target-&gt;cap_effective
)paren
suffix:semicolon
op_star
id|inheritable
op_assign
id|cap_t
(paren
id|target-&gt;cap_inheritable
)paren
suffix:semicolon
op_star
id|permitted
op_assign
id|cap_t
(paren
id|target-&gt;cap_permitted
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cap_capset_check
r_static
r_int
id|cap_capset_check
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
multiline_comment|/* Derived from kernel/capability.c:sys_capset. */
multiline_comment|/* verify restrictions on target&squot;s new Inheritable set */
r_if
c_cond
(paren
op_logical_neg
id|cap_issubset
(paren
op_star
id|inheritable
comma
id|cap_combine
(paren
id|target-&gt;cap_inheritable
comma
id|current-&gt;cap_permitted
)paren
)paren
)paren
(brace
r_return
op_minus
id|EPERM
suffix:semicolon
)brace
multiline_comment|/* verify restrictions on target&squot;s new Permitted set */
r_if
c_cond
(paren
op_logical_neg
id|cap_issubset
(paren
op_star
id|permitted
comma
id|cap_combine
(paren
id|target-&gt;cap_permitted
comma
id|current-&gt;cap_permitted
)paren
)paren
)paren
(brace
r_return
op_minus
id|EPERM
suffix:semicolon
)brace
multiline_comment|/* verify the _new_Effective_ is a subset of the _new_Permitted_ */
r_if
c_cond
(paren
op_logical_neg
id|cap_issubset
(paren
op_star
id|effective
comma
op_star
id|permitted
)paren
)paren
(brace
r_return
op_minus
id|EPERM
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cap_capset_set
r_static
r_void
id|cap_capset_set
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
id|target-&gt;cap_effective
op_assign
op_star
id|effective
suffix:semicolon
id|target-&gt;cap_inheritable
op_assign
op_star
id|inheritable
suffix:semicolon
id|target-&gt;cap_permitted
op_assign
op_star
id|permitted
suffix:semicolon
)brace
DECL|function|cap_acct
r_static
r_int
id|cap_acct
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
DECL|function|cap_bprm_alloc_security
r_static
r_int
id|cap_bprm_alloc_security
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
DECL|function|cap_bprm_set_security
r_static
r_int
id|cap_bprm_set_security
(paren
r_struct
id|linux_binprm
op_star
id|bprm
)paren
(brace
multiline_comment|/* Copied from fs/exec.c:prepare_binprm. */
multiline_comment|/* We don&squot;t have VFS support for capabilities yet */
id|cap_clear
(paren
id|bprm-&gt;cap_inheritable
)paren
suffix:semicolon
id|cap_clear
(paren
id|bprm-&gt;cap_permitted
)paren
suffix:semicolon
id|cap_clear
(paren
id|bprm-&gt;cap_effective
)paren
suffix:semicolon
multiline_comment|/*  To support inheritance of root-permissions and suid-root&n;&t; *  executables under compatibility mode, we raise all three&n;&t; *  capability sets for the file.&n;&t; *&n;&t; *  If only the real uid is 0, we only raise the inheritable&n;&t; *  and permitted sets of the executable file.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|issecure
(paren
id|SECURE_NOROOT
)paren
)paren
(brace
r_if
c_cond
(paren
id|bprm-&gt;e_uid
op_eq
l_int|0
op_logical_or
id|current-&gt;uid
op_eq
l_int|0
)paren
(brace
id|cap_set_full
(paren
id|bprm-&gt;cap_inheritable
)paren
suffix:semicolon
id|cap_set_full
(paren
id|bprm-&gt;cap_permitted
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|bprm-&gt;e_uid
op_eq
l_int|0
)paren
id|cap_set_full
(paren
id|bprm-&gt;cap_effective
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cap_bprm_check_security
r_static
r_int
id|cap_bprm_check_security
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
DECL|function|cap_bprm_free_security
r_static
r_void
id|cap_bprm_free_security
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
multiline_comment|/* Copied from fs/exec.c */
DECL|function|must_not_trace_exec
r_static
r_inline
r_int
id|must_not_trace_exec
(paren
r_struct
id|task_struct
op_star
id|p
)paren
(brace
r_return
(paren
id|p-&gt;ptrace
op_amp
id|PT_PTRACED
)paren
op_logical_and
op_logical_neg
(paren
id|p-&gt;ptrace
op_amp
id|PT_PTRACE_CAP
)paren
suffix:semicolon
)brace
DECL|function|cap_bprm_compute_creds
r_static
r_void
id|cap_bprm_compute_creds
(paren
r_struct
id|linux_binprm
op_star
id|bprm
)paren
(brace
multiline_comment|/* Derived from fs/exec.c:compute_creds. */
id|kernel_cap_t
id|new_permitted
comma
id|working
suffix:semicolon
r_int
id|do_unlock
op_assign
l_int|0
suffix:semicolon
id|new_permitted
op_assign
id|cap_intersect
(paren
id|bprm-&gt;cap_permitted
comma
id|cap_bset
)paren
suffix:semicolon
id|working
op_assign
id|cap_intersect
(paren
id|bprm-&gt;cap_inheritable
comma
id|current-&gt;cap_inheritable
)paren
suffix:semicolon
id|new_permitted
op_assign
id|cap_combine
(paren
id|new_permitted
comma
id|working
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cap_issubset
(paren
id|new_permitted
comma
id|current-&gt;cap_permitted
)paren
)paren
(brace
id|current-&gt;mm-&gt;dumpable
op_assign
l_int|0
suffix:semicolon
id|lock_kernel
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|must_not_trace_exec
(paren
id|current
)paren
op_logical_or
id|atomic_read
(paren
op_amp
id|current-&gt;fs-&gt;count
)paren
OG
l_int|1
op_logical_or
id|atomic_read
(paren
op_amp
id|current-&gt;files-&gt;count
)paren
OG
l_int|1
op_logical_or
id|atomic_read
(paren
op_amp
id|current-&gt;sig-&gt;count
)paren
OG
l_int|1
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|capable
(paren
id|CAP_SETPCAP
)paren
)paren
(brace
id|new_permitted
op_assign
id|cap_intersect
(paren
id|new_permitted
comma
id|current
op_member_access_from_pointer
id|cap_permitted
)paren
suffix:semicolon
)brace
)brace
id|do_unlock
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/* For init, we want to retain the capabilities set&n;&t; * in the init_task struct. Thus we skip the usual&n;&t; * capability rules */
r_if
c_cond
(paren
id|current-&gt;pid
op_ne
l_int|1
)paren
(brace
id|current-&gt;cap_permitted
op_assign
id|new_permitted
suffix:semicolon
id|current-&gt;cap_effective
op_assign
id|cap_intersect
(paren
id|new_permitted
comma
id|bprm-&gt;cap_effective
)paren
suffix:semicolon
)brace
multiline_comment|/* AUD: Audit candidate if current-&gt;cap_effective is set */
r_if
c_cond
(paren
id|do_unlock
)paren
id|unlock_kernel
(paren
)paren
suffix:semicolon
id|current-&gt;keep_capabilities
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|cap_sb_alloc_security
r_static
r_int
id|cap_sb_alloc_security
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
DECL|function|cap_sb_free_security
r_static
r_void
id|cap_sb_free_security
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
DECL|function|cap_sb_statfs
r_static
r_int
id|cap_sb_statfs
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
DECL|function|cap_mount
r_static
r_int
id|cap_mount
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
DECL|function|cap_check_sb
r_static
r_int
id|cap_check_sb
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
DECL|function|cap_umount
r_static
r_int
id|cap_umount
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
DECL|function|cap_umount_close
r_static
r_void
id|cap_umount_close
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
DECL|function|cap_umount_busy
r_static
r_void
id|cap_umount_busy
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
DECL|function|cap_post_remount
r_static
r_void
id|cap_post_remount
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
DECL|function|cap_post_mountroot
r_static
r_void
id|cap_post_mountroot
(paren
r_void
)paren
(brace
r_return
suffix:semicolon
)brace
DECL|function|cap_post_addmount
r_static
r_void
id|cap_post_addmount
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
DECL|function|cap_pivotroot
r_static
r_int
id|cap_pivotroot
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
DECL|function|cap_post_pivotroot
r_static
r_void
id|cap_post_pivotroot
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
DECL|function|cap_inode_alloc_security
r_static
r_int
id|cap_inode_alloc_security
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
DECL|function|cap_inode_free_security
r_static
r_void
id|cap_inode_free_security
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
DECL|function|cap_inode_create
r_static
r_int
id|cap_inode_create
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
DECL|function|cap_inode_post_create
r_static
r_void
id|cap_inode_post_create
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
DECL|function|cap_inode_link
r_static
r_int
id|cap_inode_link
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
DECL|function|cap_inode_post_link
r_static
r_void
id|cap_inode_post_link
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
DECL|function|cap_inode_unlink
r_static
r_int
id|cap_inode_unlink
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
DECL|function|cap_inode_symlink
r_static
r_int
id|cap_inode_symlink
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
DECL|function|cap_inode_post_symlink
r_static
r_void
id|cap_inode_post_symlink
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
DECL|function|cap_inode_mkdir
r_static
r_int
id|cap_inode_mkdir
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
DECL|function|cap_inode_post_mkdir
r_static
r_void
id|cap_inode_post_mkdir
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
DECL|function|cap_inode_rmdir
r_static
r_int
id|cap_inode_rmdir
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
DECL|function|cap_inode_mknod
r_static
r_int
id|cap_inode_mknod
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
DECL|function|cap_inode_post_mknod
r_static
r_void
id|cap_inode_post_mknod
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
DECL|function|cap_inode_rename
r_static
r_int
id|cap_inode_rename
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
DECL|function|cap_inode_post_rename
r_static
r_void
id|cap_inode_post_rename
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
DECL|function|cap_inode_readlink
r_static
r_int
id|cap_inode_readlink
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
DECL|function|cap_inode_follow_link
r_static
r_int
id|cap_inode_follow_link
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
DECL|function|cap_inode_permission
r_static
r_int
id|cap_inode_permission
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
DECL|function|cap_inode_permission_lite
r_static
r_int
id|cap_inode_permission_lite
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
DECL|function|cap_inode_setattr
r_static
r_int
id|cap_inode_setattr
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
DECL|function|cap_inode_getattr
r_static
r_int
id|cap_inode_getattr
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
DECL|function|cap_post_lookup
r_static
r_void
id|cap_post_lookup
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
DECL|function|cap_delete
r_static
r_void
id|cap_delete
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
DECL|function|cap_inode_setxattr
r_static
r_int
id|cap_inode_setxattr
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
DECL|function|cap_inode_getxattr
r_static
r_int
id|cap_inode_getxattr
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
DECL|function|cap_inode_listxattr
r_static
r_int
id|cap_inode_listxattr
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
DECL|function|cap_inode_removexattr
r_static
r_int
id|cap_inode_removexattr
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
DECL|function|cap_file_permission
r_static
r_int
id|cap_file_permission
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
DECL|function|cap_file_alloc_security
r_static
r_int
id|cap_file_alloc_security
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
DECL|function|cap_file_free_security
r_static
r_void
id|cap_file_free_security
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
DECL|function|cap_file_ioctl
r_static
r_int
id|cap_file_ioctl
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
DECL|function|cap_file_mmap
r_static
r_int
id|cap_file_mmap
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
DECL|function|cap_file_mprotect
r_static
r_int
id|cap_file_mprotect
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
DECL|function|cap_file_lock
r_static
r_int
id|cap_file_lock
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
DECL|function|cap_file_fcntl
r_static
r_int
id|cap_file_fcntl
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
DECL|function|cap_file_set_fowner
r_static
r_int
id|cap_file_set_fowner
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
DECL|function|cap_file_send_sigiotask
r_static
r_int
id|cap_file_send_sigiotask
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
DECL|function|cap_file_receive
r_static
r_int
id|cap_file_receive
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
DECL|function|cap_task_create
r_static
r_int
id|cap_task_create
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
DECL|function|cap_task_alloc_security
r_static
r_int
id|cap_task_alloc_security
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
DECL|function|cap_task_free_security
r_static
r_void
id|cap_task_free_security
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
DECL|function|cap_task_setuid
r_static
r_int
id|cap_task_setuid
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
multiline_comment|/* moved from kernel/sys.c. */
multiline_comment|/* &n; * cap_emulate_setxuid() fixes the effective / permitted capabilities of&n; * a process after a call to setuid, setreuid, or setresuid.&n; *&n; *  1) When set*uiding _from_ one of {r,e,s}uid == 0 _to_ all of&n; *  {r,e,s}uid != 0, the permitted and effective capabilities are&n; *  cleared.&n; *&n; *  2) When set*uiding _from_ euid == 0 _to_ euid != 0, the effective&n; *  capabilities of the process are cleared.&n; *&n; *  3) When set*uiding _from_ euid != 0 _to_ euid == 0, the effective&n; *  capabilities are set to the permitted capabilities.&n; *&n; *  fsuid is handled elsewhere. fsuid == 0 and {r,e,s}uid!= 0 should &n; *  never happen.&n; *&n; *  -astor &n; *&n; * cevans - New behaviour, Oct &squot;99&n; * A process may, via prctl(), elect to keep its capabilities when it&n; * calls setuid() and switches away from uid==0. Both permitted and&n; * effective sets will be retained.&n; * Without this change, it was impossible for a daemon to drop only some&n; * of its privilege. The call to setuid(!=0) would drop all privileges!&n; * Keeping uid 0 is not an option because uid 0 owns too many vital&n; * files..&n; * Thanks to Olaf Kirch and Peter Benie for spotting this.&n; */
DECL|function|cap_emulate_setxuid
r_static
r_inline
r_void
id|cap_emulate_setxuid
(paren
r_int
id|old_ruid
comma
r_int
id|old_euid
comma
r_int
id|old_suid
)paren
(brace
r_if
c_cond
(paren
(paren
id|old_ruid
op_eq
l_int|0
op_logical_or
id|old_euid
op_eq
l_int|0
op_logical_or
id|old_suid
op_eq
l_int|0
)paren
op_logical_and
(paren
id|current-&gt;uid
op_ne
l_int|0
op_logical_and
id|current-&gt;euid
op_ne
l_int|0
op_logical_and
id|current-&gt;suid
op_ne
l_int|0
)paren
op_logical_and
op_logical_neg
id|current-&gt;keep_capabilities
)paren
(brace
id|cap_clear
(paren
id|current-&gt;cap_permitted
)paren
suffix:semicolon
id|cap_clear
(paren
id|current-&gt;cap_effective
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|old_euid
op_eq
l_int|0
op_logical_and
id|current-&gt;euid
op_ne
l_int|0
)paren
(brace
id|cap_clear
(paren
id|current-&gt;cap_effective
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|old_euid
op_ne
l_int|0
op_logical_and
id|current-&gt;euid
op_eq
l_int|0
)paren
(brace
id|current-&gt;cap_effective
op_assign
id|current-&gt;cap_permitted
suffix:semicolon
)brace
)brace
DECL|function|cap_task_post_setuid
r_static
r_int
id|cap_task_post_setuid
(paren
id|uid_t
id|old_ruid
comma
id|uid_t
id|old_euid
comma
id|uid_t
id|old_suid
comma
r_int
id|flags
)paren
(brace
r_switch
c_cond
(paren
id|flags
)paren
(brace
r_case
id|LSM_SETID_RE
suffix:colon
r_case
id|LSM_SETID_ID
suffix:colon
r_case
id|LSM_SETID_RES
suffix:colon
multiline_comment|/* Copied from kernel/sys.c:setreuid/setuid/setresuid. */
r_if
c_cond
(paren
op_logical_neg
id|issecure
(paren
id|SECURE_NO_SETUID_FIXUP
)paren
)paren
(brace
id|cap_emulate_setxuid
(paren
id|old_ruid
comma
id|old_euid
comma
id|old_suid
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|LSM_SETID_FS
suffix:colon
(brace
id|uid_t
id|old_fsuid
op_assign
id|old_ruid
suffix:semicolon
multiline_comment|/* Copied from kernel/sys.c:setfsuid. */
multiline_comment|/*&n;&t;&t;&t; * FIXME - is fsuser used for all CAP_FS_MASK capabilities?&n;&t;&t;&t; *          if not, we might be a bit too harsh here.&n;&t;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|issecure
(paren
id|SECURE_NO_SETUID_FIXUP
)paren
)paren
(brace
r_if
c_cond
(paren
id|old_fsuid
op_eq
l_int|0
op_logical_and
id|current-&gt;fsuid
op_ne
l_int|0
)paren
(brace
id|cap_t
(paren
id|current-&gt;cap_effective
)paren
op_and_assign
op_complement
id|CAP_FS_MASK
suffix:semicolon
)brace
r_if
c_cond
(paren
id|old_fsuid
op_ne
l_int|0
op_logical_and
id|current-&gt;fsuid
op_eq
l_int|0
)paren
(brace
id|cap_t
(paren
id|current-&gt;cap_effective
)paren
op_or_assign
(paren
id|cap_t
(paren
id|current-&gt;cap_permitted
)paren
op_amp
id|CAP_FS_MASK
)paren
suffix:semicolon
)brace
)brace
r_break
suffix:semicolon
)brace
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cap_task_setgid
r_static
r_int
id|cap_task_setgid
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
DECL|function|cap_task_setpgid
r_static
r_int
id|cap_task_setpgid
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
DECL|function|cap_task_getpgid
r_static
r_int
id|cap_task_getpgid
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
DECL|function|cap_task_getsid
r_static
r_int
id|cap_task_getsid
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
DECL|function|cap_task_setgroups
r_static
r_int
id|cap_task_setgroups
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
DECL|function|cap_task_setnice
r_static
r_int
id|cap_task_setnice
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
DECL|function|cap_task_setrlimit
r_static
r_int
id|cap_task_setrlimit
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
DECL|function|cap_task_setscheduler
r_static
r_int
id|cap_task_setscheduler
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
DECL|function|cap_task_getscheduler
r_static
r_int
id|cap_task_getscheduler
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
DECL|function|cap_task_wait
r_static
r_int
id|cap_task_wait
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
DECL|function|cap_task_kill
r_static
r_int
id|cap_task_kill
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
DECL|function|cap_task_prctl
r_static
r_int
id|cap_task_prctl
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
DECL|function|cap_task_kmod_set_label
r_static
r_void
id|cap_task_kmod_set_label
(paren
r_void
)paren
(brace
id|cap_set_full
(paren
id|current-&gt;cap_effective
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|cap_task_reparent_to_init
r_static
r_void
id|cap_task_reparent_to_init
(paren
r_struct
id|task_struct
op_star
id|p
)paren
(brace
id|p-&gt;cap_effective
op_assign
id|CAP_INIT_EFF_SET
suffix:semicolon
id|p-&gt;cap_inheritable
op_assign
id|CAP_INIT_INH_SET
suffix:semicolon
id|p-&gt;cap_permitted
op_assign
id|CAP_FULL_SET
suffix:semicolon
id|p-&gt;keep_capabilities
op_assign
l_int|0
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|cap_ipc_permission
r_static
r_int
id|cap_ipc_permission
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
DECL|function|cap_msg_queue_alloc_security
r_static
r_int
id|cap_msg_queue_alloc_security
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
DECL|function|cap_msg_queue_free_security
r_static
r_void
id|cap_msg_queue_free_security
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
DECL|function|cap_shm_alloc_security
r_static
r_int
id|cap_shm_alloc_security
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
DECL|function|cap_shm_free_security
r_static
r_void
id|cap_shm_free_security
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
DECL|function|cap_sem_alloc_security
r_static
r_int
id|cap_sem_alloc_security
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
DECL|function|cap_sem_free_security
r_static
r_void
id|cap_sem_free_security
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
DECL|function|cap_register
r_static
r_int
id|cap_register
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
DECL|function|cap_unregister
r_static
r_int
id|cap_unregister
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
DECL|variable|capability_ops
r_static
r_struct
id|security_operations
id|capability_ops
op_assign
(brace
dot
id|ptrace
op_assign
id|cap_ptrace
comma
dot
id|capget
op_assign
id|cap_capget
comma
dot
id|capset_check
op_assign
id|cap_capset_check
comma
dot
id|capset_set
op_assign
id|cap_capset_set
comma
dot
id|acct
op_assign
id|cap_acct
comma
dot
id|capable
op_assign
id|cap_capable
comma
dot
id|sys_security
op_assign
id|cap_sys_security
comma
dot
id|quotactl
op_assign
id|cap_quotactl
comma
dot
id|quota_on
op_assign
id|cap_quota_on
comma
dot
id|bprm_alloc_security
op_assign
id|cap_bprm_alloc_security
comma
dot
id|bprm_free_security
op_assign
id|cap_bprm_free_security
comma
dot
id|bprm_compute_creds
op_assign
id|cap_bprm_compute_creds
comma
dot
id|bprm_set_security
op_assign
id|cap_bprm_set_security
comma
dot
id|bprm_check_security
op_assign
id|cap_bprm_check_security
comma
dot
id|sb_alloc_security
op_assign
id|cap_sb_alloc_security
comma
dot
id|sb_free_security
op_assign
id|cap_sb_free_security
comma
dot
id|sb_statfs
op_assign
id|cap_sb_statfs
comma
dot
id|sb_mount
op_assign
id|cap_mount
comma
dot
id|sb_check_sb
op_assign
id|cap_check_sb
comma
dot
id|sb_umount
op_assign
id|cap_umount
comma
dot
id|sb_umount_close
op_assign
id|cap_umount_close
comma
dot
id|sb_umount_busy
op_assign
id|cap_umount_busy
comma
dot
id|sb_post_remount
op_assign
id|cap_post_remount
comma
dot
id|sb_post_mountroot
op_assign
id|cap_post_mountroot
comma
dot
id|sb_post_addmount
op_assign
id|cap_post_addmount
comma
dot
id|sb_pivotroot
op_assign
id|cap_pivotroot
comma
dot
id|sb_post_pivotroot
op_assign
id|cap_post_pivotroot
comma
dot
id|inode_alloc_security
op_assign
id|cap_inode_alloc_security
comma
dot
id|inode_free_security
op_assign
id|cap_inode_free_security
comma
dot
id|inode_create
op_assign
id|cap_inode_create
comma
dot
id|inode_post_create
op_assign
id|cap_inode_post_create
comma
dot
id|inode_link
op_assign
id|cap_inode_link
comma
dot
id|inode_post_link
op_assign
id|cap_inode_post_link
comma
dot
id|inode_unlink
op_assign
id|cap_inode_unlink
comma
dot
id|inode_symlink
op_assign
id|cap_inode_symlink
comma
dot
id|inode_post_symlink
op_assign
id|cap_inode_post_symlink
comma
dot
id|inode_mkdir
op_assign
id|cap_inode_mkdir
comma
dot
id|inode_post_mkdir
op_assign
id|cap_inode_post_mkdir
comma
dot
id|inode_rmdir
op_assign
id|cap_inode_rmdir
comma
dot
id|inode_mknod
op_assign
id|cap_inode_mknod
comma
dot
id|inode_post_mknod
op_assign
id|cap_inode_post_mknod
comma
dot
id|inode_rename
op_assign
id|cap_inode_rename
comma
dot
id|inode_post_rename
op_assign
id|cap_inode_post_rename
comma
dot
id|inode_readlink
op_assign
id|cap_inode_readlink
comma
dot
id|inode_follow_link
op_assign
id|cap_inode_follow_link
comma
dot
id|inode_permission
op_assign
id|cap_inode_permission
comma
dot
id|inode_permission_lite
op_assign
id|cap_inode_permission_lite
comma
dot
id|inode_setattr
op_assign
id|cap_inode_setattr
comma
dot
id|inode_getattr
op_assign
id|cap_inode_getattr
comma
dot
id|inode_post_lookup
op_assign
id|cap_post_lookup
comma
dot
id|inode_delete
op_assign
id|cap_delete
comma
dot
id|inode_setxattr
op_assign
id|cap_inode_setxattr
comma
dot
id|inode_getxattr
op_assign
id|cap_inode_getxattr
comma
dot
id|inode_listxattr
op_assign
id|cap_inode_listxattr
comma
dot
id|inode_removexattr
op_assign
id|cap_inode_removexattr
comma
dot
id|file_permission
op_assign
id|cap_file_permission
comma
dot
id|file_alloc_security
op_assign
id|cap_file_alloc_security
comma
dot
id|file_free_security
op_assign
id|cap_file_free_security
comma
dot
id|file_ioctl
op_assign
id|cap_file_ioctl
comma
dot
id|file_mmap
op_assign
id|cap_file_mmap
comma
dot
id|file_mprotect
op_assign
id|cap_file_mprotect
comma
dot
id|file_lock
op_assign
id|cap_file_lock
comma
dot
id|file_fcntl
op_assign
id|cap_file_fcntl
comma
dot
id|file_set_fowner
op_assign
id|cap_file_set_fowner
comma
dot
id|file_send_sigiotask
op_assign
id|cap_file_send_sigiotask
comma
dot
id|file_receive
op_assign
id|cap_file_receive
comma
dot
id|task_create
op_assign
id|cap_task_create
comma
dot
id|task_alloc_security
op_assign
id|cap_task_alloc_security
comma
dot
id|task_free_security
op_assign
id|cap_task_free_security
comma
dot
id|task_setuid
op_assign
id|cap_task_setuid
comma
dot
id|task_post_setuid
op_assign
id|cap_task_post_setuid
comma
dot
id|task_setgid
op_assign
id|cap_task_setgid
comma
dot
id|task_setpgid
op_assign
id|cap_task_setpgid
comma
dot
id|task_getpgid
op_assign
id|cap_task_getpgid
comma
dot
id|task_getsid
op_assign
id|cap_task_getsid
comma
dot
id|task_setgroups
op_assign
id|cap_task_setgroups
comma
dot
id|task_setnice
op_assign
id|cap_task_setnice
comma
dot
id|task_setrlimit
op_assign
id|cap_task_setrlimit
comma
dot
id|task_setscheduler
op_assign
id|cap_task_setscheduler
comma
dot
id|task_getscheduler
op_assign
id|cap_task_getscheduler
comma
dot
id|task_wait
op_assign
id|cap_task_wait
comma
dot
id|task_kill
op_assign
id|cap_task_kill
comma
dot
id|task_prctl
op_assign
id|cap_task_prctl
comma
dot
id|task_kmod_set_label
op_assign
id|cap_task_kmod_set_label
comma
dot
id|task_reparent_to_init
op_assign
id|cap_task_reparent_to_init
comma
dot
id|ipc_permission
op_assign
id|cap_ipc_permission
comma
dot
id|msg_queue_alloc_security
op_assign
id|cap_msg_queue_alloc_security
comma
dot
id|msg_queue_free_security
op_assign
id|cap_msg_queue_free_security
comma
dot
id|shm_alloc_security
op_assign
id|cap_shm_alloc_security
comma
dot
id|shm_free_security
op_assign
id|cap_shm_free_security
comma
dot
id|sem_alloc_security
op_assign
id|cap_sem_alloc_security
comma
dot
id|sem_free_security
op_assign
id|cap_sem_free_security
comma
dot
id|register_security
op_assign
id|cap_register
comma
dot
id|unregister_security
op_assign
id|cap_unregister
comma
)brace
suffix:semicolon
macro_line|#if defined(CONFIG_SECURITY_CAPABILITIES_MODULE)
DECL|macro|MY_NAME
mdefine_line|#define MY_NAME THIS_MODULE-&gt;name
macro_line|#else
DECL|macro|MY_NAME
mdefine_line|#define MY_NAME &quot;capability&quot;
macro_line|#endif
DECL|function|capability_init
r_static
r_int
id|__init
id|capability_init
(paren
r_void
)paren
(brace
multiline_comment|/* register ourselves with the security framework */
r_if
c_cond
(paren
id|register_security
(paren
op_amp
id|capability_ops
)paren
)paren
(brace
id|printk
(paren
id|KERN_INFO
l_string|&quot;Failure registering capabilities with the kernel&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* try registering with primary module */
r_if
c_cond
(paren
id|mod_reg_security
(paren
id|MY_NAME
comma
op_amp
id|capability_ops
)paren
)paren
(brace
id|printk
(paren
id|KERN_INFO
l_string|&quot;Failure registering capabilities &quot;
l_string|&quot;with primary security module.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|secondary
op_assign
l_int|1
suffix:semicolon
)brace
id|printk
(paren
id|KERN_INFO
l_string|&quot;Capability LSM initialized&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|capability_exit
r_static
r_void
id|__exit
id|capability_exit
(paren
r_void
)paren
(brace
multiline_comment|/* remove ourselves from the security framework */
r_if
c_cond
(paren
id|secondary
)paren
(brace
r_if
c_cond
(paren
id|mod_unreg_security
(paren
id|MY_NAME
comma
op_amp
id|capability_ops
)paren
)paren
id|printk
(paren
id|KERN_INFO
l_string|&quot;Failure unregistering capabilities &quot;
l_string|&quot;with primary module.&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|unregister_security
(paren
op_amp
id|capability_ops
)paren
)paren
(brace
id|printk
(paren
id|KERN_INFO
l_string|&quot;Failure unregistering capabilities with the kernel&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
DECL|variable|capability_init
id|module_init
(paren
id|capability_init
)paren
suffix:semicolon
DECL|variable|capability_exit
id|module_exit
(paren
id|capability_exit
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Standard Linux Capabilities Security Module&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
