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
DECL|function|dummy_sys_security
r_static
r_int
id|dummy_sys_security
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
id|ptrace
suffix:colon
id|dummy_ptrace
comma
id|capget
suffix:colon
id|dummy_capget
comma
id|capset_check
suffix:colon
id|dummy_capset_check
comma
id|capset_set
suffix:colon
id|dummy_capset_set
comma
id|capable
suffix:colon
id|dummy_capable
comma
id|sys_security
suffix:colon
id|dummy_sys_security
comma
id|bprm_alloc_security
suffix:colon
id|dummy_bprm_alloc_security
comma
id|bprm_free_security
suffix:colon
id|dummy_bprm_free_security
comma
id|bprm_compute_creds
suffix:colon
id|dummy_bprm_compute_creds
comma
id|bprm_set_security
suffix:colon
id|dummy_bprm_set_security
comma
id|bprm_check_security
suffix:colon
id|dummy_bprm_check_security
comma
id|task_create
suffix:colon
id|dummy_task_create
comma
id|task_alloc_security
suffix:colon
id|dummy_task_alloc_security
comma
id|task_free_security
suffix:colon
id|dummy_task_free_security
comma
id|task_setuid
suffix:colon
id|dummy_task_setuid
comma
id|task_post_setuid
suffix:colon
id|dummy_task_post_setuid
comma
id|task_setgid
suffix:colon
id|dummy_task_setgid
comma
id|task_setpgid
suffix:colon
id|dummy_task_setpgid
comma
id|task_getpgid
suffix:colon
id|dummy_task_getpgid
comma
id|task_getsid
suffix:colon
id|dummy_task_getsid
comma
id|task_setgroups
suffix:colon
id|dummy_task_setgroups
comma
id|task_setnice
suffix:colon
id|dummy_task_setnice
comma
id|task_setrlimit
suffix:colon
id|dummy_task_setrlimit
comma
id|task_setscheduler
suffix:colon
id|dummy_task_setscheduler
comma
id|task_getscheduler
suffix:colon
id|dummy_task_getscheduler
comma
id|task_wait
suffix:colon
id|dummy_task_wait
comma
id|task_kill
suffix:colon
id|dummy_task_kill
comma
id|task_prctl
suffix:colon
id|dummy_task_prctl
comma
id|task_kmod_set_label
suffix:colon
id|dummy_task_kmod_set_label
comma
id|task_reparent_to_init
suffix:colon
id|dummy_task_reparent_to_init
comma
id|register_security
suffix:colon
id|dummy_register
comma
id|unregister_security
suffix:colon
id|dummy_unregister
comma
)brace
suffix:semicolon
eof
