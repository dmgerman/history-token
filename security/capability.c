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
macro_line|#include &lt;linux/ptrace.h&gt;
DECL|function|cap_capable
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
DECL|function|cap_ptrace
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
DECL|function|cap_bprm_set_security
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
id|task_lock
c_func
(paren
id|current
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
id|current-&gt;sighand-&gt;count
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
id|task_unlock
c_func
(paren
id|current
)paren
suffix:semicolon
id|current-&gt;keep_capabilities
op_assign
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
DECL|function|cap_task_kmod_set_label
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
DECL|variable|cap_capable
id|EXPORT_SYMBOL
c_func
(paren
id|cap_capable
)paren
suffix:semicolon
DECL|variable|cap_ptrace
id|EXPORT_SYMBOL
c_func
(paren
id|cap_ptrace
)paren
suffix:semicolon
DECL|variable|cap_capget
id|EXPORT_SYMBOL
c_func
(paren
id|cap_capget
)paren
suffix:semicolon
DECL|variable|cap_capset_check
id|EXPORT_SYMBOL
c_func
(paren
id|cap_capset_check
)paren
suffix:semicolon
DECL|variable|cap_capset_set
id|EXPORT_SYMBOL
c_func
(paren
id|cap_capset_set
)paren
suffix:semicolon
DECL|variable|cap_bprm_set_security
id|EXPORT_SYMBOL
c_func
(paren
id|cap_bprm_set_security
)paren
suffix:semicolon
DECL|variable|cap_bprm_compute_creds
id|EXPORT_SYMBOL
c_func
(paren
id|cap_bprm_compute_creds
)paren
suffix:semicolon
DECL|variable|cap_task_post_setuid
id|EXPORT_SYMBOL
c_func
(paren
id|cap_task_post_setuid
)paren
suffix:semicolon
DECL|variable|cap_task_kmod_set_label
id|EXPORT_SYMBOL
c_func
(paren
id|cap_task_kmod_set_label
)paren
suffix:semicolon
DECL|variable|cap_task_reparent_to_init
id|EXPORT_SYMBOL
c_func
(paren
id|cap_task_reparent_to_init
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SECURITY
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
id|capable
op_assign
id|cap_capable
comma
dot
id|netlink_send
op_assign
id|cap_netlink_send
comma
dot
id|netlink_recv
op_assign
id|cap_netlink_recv
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
id|task_post_setuid
op_assign
id|cap_task_post_setuid
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
)brace
suffix:semicolon
macro_line|#if defined(CONFIG_SECURITY_CAPABILITIES_MODULE)
DECL|macro|MY_NAME
mdefine_line|#define MY_NAME THIS_MODULE-&gt;name
macro_line|#else
DECL|macro|MY_NAME
mdefine_line|#define MY_NAME &quot;capability&quot;
macro_line|#endif
multiline_comment|/* flag to keep track of how we were registered */
DECL|variable|secondary
r_static
r_int
id|secondary
suffix:semicolon
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
macro_line|#endif&t;/* CONFIG_SECURITY */
eof
