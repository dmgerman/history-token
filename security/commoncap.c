multiline_comment|/* Common capabilities, needed by capability.o and root_plug.o &n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/security.h&gt;
macro_line|#include &lt;linux/file.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/swap.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/netlink.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/xattr.h&gt;
macro_line|#include &lt;linux/hugetlb.h&gt;
DECL|function|cap_netlink_send
r_int
id|cap_netlink_send
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
id|NETLINK_CB
c_func
(paren
id|skb
)paren
dot
id|eff_cap
op_assign
id|current-&gt;cap_effective
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|cap_netlink_send
id|EXPORT_SYMBOL
c_func
(paren
id|cap_netlink_send
)paren
suffix:semicolon
DECL|function|cap_netlink_recv
r_int
id|cap_netlink_recv
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|cap_raised
c_func
(paren
id|NETLINK_CB
c_func
(paren
id|skb
)paren
dot
id|eff_cap
comma
id|CAP_NET_ADMIN
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|cap_netlink_recv
id|EXPORT_SYMBOL
c_func
(paren
id|cap_netlink_recv
)paren
suffix:semicolon
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
c_func
(paren
id|tsk-&gt;cap_effective
comma
id|cap
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
op_minus
id|EPERM
suffix:semicolon
)brace
DECL|function|cap_settime
r_int
id|cap_settime
c_func
(paren
r_struct
id|timespec
op_star
id|ts
comma
r_struct
id|timezone
op_star
id|tz
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_TIME
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
r_return
l_int|0
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
c_func
(paren
id|CAP_SYS_PTRACE
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
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
DECL|function|cap_bprm_apply_creds
r_void
id|cap_bprm_apply_creds
(paren
r_struct
id|linux_binprm
op_star
id|bprm
comma
r_int
id|unsafe
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
r_if
c_cond
(paren
id|bprm-&gt;e_uid
op_ne
id|current-&gt;uid
op_logical_or
id|bprm-&gt;e_gid
op_ne
id|current-&gt;gid
op_logical_or
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
id|unsafe
op_amp
op_complement
id|LSM_UNSAFE_PTRACE_CAP
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_SETUID
)paren
)paren
(brace
id|bprm-&gt;e_uid
op_assign
id|current-&gt;uid
suffix:semicolon
id|bprm-&gt;e_gid
op_assign
id|current-&gt;gid
suffix:semicolon
)brace
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
id|current-&gt;cap_permitted
)paren
suffix:semicolon
)brace
)brace
)brace
id|current-&gt;suid
op_assign
id|current-&gt;euid
op_assign
id|current-&gt;fsuid
op_assign
id|bprm-&gt;e_uid
suffix:semicolon
id|current-&gt;sgid
op_assign
id|current-&gt;egid
op_assign
id|current-&gt;fsgid
op_assign
id|bprm-&gt;e_gid
suffix:semicolon
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
id|current-&gt;keep_capabilities
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|cap_bprm_secureexec
r_int
id|cap_bprm_secureexec
(paren
r_struct
id|linux_binprm
op_star
id|bprm
)paren
(brace
multiline_comment|/* If/when this module is enhanced to incorporate capability&n;&t;   bits on files, the test below should be extended to also perform a &n;&t;   test between the old and new capability sets.  For now,&n;&t;   it simply preserves the legacy decision algorithm used by&n;&t;   the old userland. */
r_return
(paren
id|current-&gt;euid
op_ne
id|current-&gt;uid
op_logical_or
id|current-&gt;egid
op_ne
id|current-&gt;gid
)paren
suffix:semicolon
)brace
DECL|function|cap_inode_setxattr
r_int
id|cap_inode_setxattr
c_func
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
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|name
comma
id|XATTR_SECURITY_PREFIX
comma
r_sizeof
(paren
id|XATTR_SECURITY_PREFIX
)paren
op_minus
l_int|1
)paren
op_logical_and
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cap_inode_removexattr
r_int
id|cap_inode_removexattr
c_func
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
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|name
comma
id|XATTR_SECURITY_PREFIX
comma
r_sizeof
(paren
id|XATTR_SECURITY_PREFIX
)paren
op_minus
l_int|1
)paren
op_logical_and
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
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
DECL|function|cap_syslog
r_int
id|cap_syslog
(paren
r_int
id|type
)paren
(brace
r_if
c_cond
(paren
(paren
id|type
op_ne
l_int|3
op_logical_and
id|type
op_ne
l_int|10
)paren
op_logical_and
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Check that a process has enough memory to allocate a new virtual&n; * mapping. 0 means there is enough memory for the allocation to&n; * succeed and -ENOMEM implies there is not.&n; *&n; * We currently support three overcommit policies, which are set via the&n; * vm.overcommit_memory sysctl.  See Documentation/vm/overcommit-accounting&n; *&n; * Strict overcommit modes added 2002 Feb 26 by Alan Cox.&n; * Additional code 2002 Jul 20 by Robert Love.&n; */
DECL|function|cap_vm_enough_memory
r_int
id|cap_vm_enough_memory
c_func
(paren
r_int
id|pages
)paren
(brace
r_int
r_int
id|free
comma
id|allowed
suffix:semicolon
id|vm_acct_memory
c_func
(paren
id|pages
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Sometimes we want to use more memory than we have&n;&t; */
r_if
c_cond
(paren
id|sysctl_overcommit_memory
op_eq
id|OVERCOMMIT_ALWAYS
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|sysctl_overcommit_memory
op_eq
id|OVERCOMMIT_GUESS
)paren
(brace
r_int
r_int
id|n
suffix:semicolon
id|free
op_assign
id|get_page_cache_size
c_func
(paren
)paren
suffix:semicolon
id|free
op_add_assign
id|nr_swap_pages
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Any slabs which are created with the&n;&t;&t; * SLAB_RECLAIM_ACCOUNT flag claim to have contents&n;&t;&t; * which are reclaimable, under pressure.  The dentry&n;&t;&t; * cache and most inode caches should fall into this&n;&t;&t; */
id|free
op_add_assign
id|atomic_read
c_func
(paren
op_amp
id|slab_reclaim_pages
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Leave the last 3% for root&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
)paren
id|free
op_sub_assign
id|free
op_div
l_int|32
suffix:semicolon
r_if
c_cond
(paren
id|free
OG
id|pages
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t;&t; * nr_free_pages() is very expensive on large systems,&n;&t;&t; * only call if we&squot;re about to fail.&n;&t;&t; */
id|n
op_assign
id|nr_free_pages
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
)paren
id|n
op_sub_assign
id|n
op_div
l_int|32
suffix:semicolon
id|free
op_add_assign
id|n
suffix:semicolon
r_if
c_cond
(paren
id|free
OG
id|pages
)paren
r_return
l_int|0
suffix:semicolon
id|vm_unacct_memory
c_func
(paren
id|pages
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|allowed
op_assign
(paren
id|totalram_pages
op_minus
id|hugetlb_total_pages
c_func
(paren
)paren
)paren
op_star
id|sysctl_overcommit_ratio
op_div
l_int|100
suffix:semicolon
multiline_comment|/*&n;&t; * Leave the last 3% for root&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
)paren
id|allowed
op_sub_assign
id|allowed
op_div
l_int|32
suffix:semicolon
id|allowed
op_add_assign
id|total_swap_pages
suffix:semicolon
multiline_comment|/* Don&squot;t let a single process grow too big:&n;&t;   leave 3% of the size of this process for other processes */
id|allowed
op_sub_assign
id|current-&gt;mm-&gt;total_vm
op_div
l_int|32
suffix:semicolon
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|vm_committed_space
)paren
OL
id|allowed
)paren
r_return
l_int|0
suffix:semicolon
id|vm_unacct_memory
c_func
(paren
id|pages
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
DECL|variable|cap_capable
id|EXPORT_SYMBOL
c_func
(paren
id|cap_capable
)paren
suffix:semicolon
DECL|variable|cap_settime
id|EXPORT_SYMBOL
c_func
(paren
id|cap_settime
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
DECL|variable|cap_bprm_apply_creds
id|EXPORT_SYMBOL
c_func
(paren
id|cap_bprm_apply_creds
)paren
suffix:semicolon
DECL|variable|cap_bprm_secureexec
id|EXPORT_SYMBOL
c_func
(paren
id|cap_bprm_secureexec
)paren
suffix:semicolon
DECL|variable|cap_inode_setxattr
id|EXPORT_SYMBOL
c_func
(paren
id|cap_inode_setxattr
)paren
suffix:semicolon
DECL|variable|cap_inode_removexattr
id|EXPORT_SYMBOL
c_func
(paren
id|cap_inode_removexattr
)paren
suffix:semicolon
DECL|variable|cap_task_post_setuid
id|EXPORT_SYMBOL
c_func
(paren
id|cap_task_post_setuid
)paren
suffix:semicolon
DECL|variable|cap_task_reparent_to_init
id|EXPORT_SYMBOL
c_func
(paren
id|cap_task_reparent_to_init
)paren
suffix:semicolon
DECL|variable|cap_syslog
id|EXPORT_SYMBOL
c_func
(paren
id|cap_syslog
)paren
suffix:semicolon
DECL|variable|cap_vm_enough_memory
id|EXPORT_SYMBOL
c_func
(paren
id|cap_vm_enough_memory
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Standard Linux Common Capabilities Security Module&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
