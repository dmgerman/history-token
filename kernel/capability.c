multiline_comment|/*&n; * linux/kernel/capability.c&n; *&n; * Copyright (C) 1997  Andrew Main &lt;zefram@fysh.org&gt;&n; *&n; * Integrated into 2.1.97+,  Andrew G. Morgan &lt;morgan@transmeta.com&gt;&n; * 30 May 2002:&t;Cleanup, Robert M. Love &lt;rml@tech9.net&gt;&n; */
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/security.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
DECL|variable|securebits
r_int
id|securebits
op_assign
id|SECUREBITS_DEFAULT
suffix:semicolon
multiline_comment|/* systemwide security settings */
DECL|variable|cap_bset
id|kernel_cap_t
id|cap_bset
op_assign
id|CAP_INIT_EFF_SET
suffix:semicolon
DECL|variable|securebits
id|EXPORT_SYMBOL
c_func
(paren
id|securebits
)paren
suffix:semicolon
DECL|variable|cap_bset
id|EXPORT_SYMBOL
c_func
(paren
id|cap_bset
)paren
suffix:semicolon
multiline_comment|/*&n; * This global lock protects task-&gt;cap_* for all tasks including current.&n; * Locking rule: acquire this prior to tasklist_lock.&n; */
DECL|variable|task_capability_lock
id|spinlock_t
id|task_capability_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
multiline_comment|/*&n; * For sys_getproccap() and sys_setproccap(), any of the three&n; * capability set pointers may be NULL -- indicating that that set is&n; * uninteresting and/or not to be changed.&n; */
multiline_comment|/*&n; * sys_capget - get the capabilities of a given process.&n; */
DECL|function|sys_capget
id|asmlinkage
r_int
id|sys_capget
c_func
(paren
id|cap_user_header_t
id|header
comma
id|cap_user_data_t
id|dataptr
)paren
(brace
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
id|pid_t
id|pid
suffix:semicolon
id|__u32
id|version
suffix:semicolon
id|task_t
op_star
id|target
suffix:semicolon
r_struct
id|__user_cap_data_struct
id|data
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|version
comma
op_amp
id|header-&gt;version
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|version
op_ne
id|_LINUX_CAPABILITY_VERSION
)paren
(brace
r_if
c_cond
(paren
id|put_user
c_func
(paren
id|_LINUX_CAPABILITY_VERSION
comma
op_amp
id|header-&gt;version
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|pid
comma
op_amp
id|header-&gt;pid
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|pid
OL
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|task_capability_lock
)paren
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|tasklist_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pid
op_logical_and
id|pid
op_ne
id|current-&gt;pid
)paren
(brace
id|target
op_assign
id|find_task_by_pid
c_func
(paren
id|pid
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|target
)paren
(brace
id|ret
op_assign
op_minus
id|ESRCH
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
)brace
r_else
id|target
op_assign
id|current
suffix:semicolon
id|ret
op_assign
id|security_capget
c_func
(paren
id|target
comma
op_amp
id|data.effective
comma
op_amp
id|data.inheritable
comma
op_amp
id|data.permitted
)paren
suffix:semicolon
id|out
suffix:colon
id|read_unlock
c_func
(paren
op_amp
id|tasklist_lock
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|task_capability_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
op_logical_and
id|copy_to_user
c_func
(paren
id|dataptr
comma
op_amp
id|data
comma
r_sizeof
id|data
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * cap_set_pg - set capabilities for all processes in a given process&n; * group.  We call this holding task_capability_lock and tasklist_lock.&n; */
DECL|function|cap_set_pg
r_static
r_inline
r_void
id|cap_set_pg
c_func
(paren
r_int
id|pgrp
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
id|task_t
op_star
id|g
comma
op_star
id|target
suffix:semicolon
id|do_each_task_pid
c_func
(paren
id|pgrp
comma
id|PIDTYPE_PGID
comma
id|g
)paren
(brace
id|target
op_assign
id|g
suffix:semicolon
id|while_each_thread
c_func
(paren
id|g
comma
id|target
)paren
id|security_capset_set
c_func
(paren
id|target
comma
id|effective
comma
id|inheritable
comma
id|permitted
)paren
suffix:semicolon
)brace
id|while_each_task_pid
c_func
(paren
id|pgrp
comma
id|PIDTYPE_PGID
comma
id|g
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * cap_set_all - set capabilities for all processes other than init&n; * and self.  We call this holding task_capability_lock and tasklist_lock.&n; */
DECL|function|cap_set_all
r_static
r_inline
r_void
id|cap_set_all
c_func
(paren
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
id|task_t
op_star
id|g
comma
op_star
id|target
suffix:semicolon
id|do_each_thread
c_func
(paren
id|g
comma
id|target
)paren
(brace
r_if
c_cond
(paren
id|target
op_eq
id|current
op_logical_or
id|target-&gt;pid
op_eq
l_int|1
)paren
r_continue
suffix:semicolon
id|security_capset_set
c_func
(paren
id|target
comma
id|effective
comma
id|inheritable
comma
id|permitted
)paren
suffix:semicolon
)brace
id|while_each_thread
c_func
(paren
id|g
comma
id|target
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * sys_capset - set capabilities for a given process, all processes, or all&n; * processes in a given process group.&n; *&n; * The restrictions on setting capabilities are specified as:&n; *&n; * [pid is for the &squot;target&squot; task.  &squot;current&squot; is the calling task.]&n; *&n; * I: any raised capabilities must be a subset of the (old current) permitted&n; * P: any raised capabilities must be a subset of the (old current) permitted&n; * E: must be set to a subset of (new target) permitted&n; */
DECL|function|sys_capset
id|asmlinkage
r_int
id|sys_capset
c_func
(paren
id|cap_user_header_t
id|header
comma
r_const
id|cap_user_data_t
id|data
)paren
(brace
id|kernel_cap_t
id|inheritable
comma
id|permitted
comma
id|effective
suffix:semicolon
id|__u32
id|version
suffix:semicolon
id|task_t
op_star
id|target
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|pid_t
id|pid
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|version
comma
op_amp
id|header-&gt;version
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|version
op_ne
id|_LINUX_CAPABILITY_VERSION
)paren
(brace
r_if
c_cond
(paren
id|put_user
c_func
(paren
id|_LINUX_CAPABILITY_VERSION
comma
op_amp
id|header-&gt;version
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|pid
comma
op_amp
id|header-&gt;pid
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|pid
op_logical_and
op_logical_neg
id|capable
c_func
(paren
id|CAP_SETPCAP
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|effective
comma
op_amp
id|data-&gt;effective
comma
r_sizeof
(paren
id|effective
)paren
)paren
op_logical_or
id|copy_from_user
c_func
(paren
op_amp
id|inheritable
comma
op_amp
id|data-&gt;inheritable
comma
r_sizeof
(paren
id|inheritable
)paren
)paren
op_logical_or
id|copy_from_user
c_func
(paren
op_amp
id|permitted
comma
op_amp
id|data-&gt;permitted
comma
r_sizeof
(paren
id|permitted
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|task_capability_lock
)paren
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|tasklist_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pid
OG
l_int|0
op_logical_and
id|pid
op_ne
id|current-&gt;pid
)paren
(brace
id|target
op_assign
id|find_task_by_pid
c_func
(paren
id|pid
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|target
)paren
(brace
id|ret
op_assign
op_minus
id|ESRCH
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
)brace
r_else
id|target
op_assign
id|current
suffix:semicolon
id|ret
op_assign
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
id|security_capset_check
c_func
(paren
id|target
comma
op_amp
id|effective
comma
op_amp
id|inheritable
comma
op_amp
id|permitted
)paren
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cap_issubset
c_func
(paren
id|inheritable
comma
id|cap_combine
c_func
(paren
id|target-&gt;cap_inheritable
comma
id|current-&gt;cap_permitted
)paren
)paren
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/* verify restrictions on target&squot;s new Permitted set */
r_if
c_cond
(paren
op_logical_neg
id|cap_issubset
c_func
(paren
id|permitted
comma
id|cap_combine
c_func
(paren
id|target-&gt;cap_permitted
comma
id|current-&gt;cap_permitted
)paren
)paren
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/* verify the _new_Effective_ is a subset of the _new_Permitted_ */
r_if
c_cond
(paren
op_logical_neg
id|cap_issubset
c_func
(paren
id|effective
comma
id|permitted
)paren
)paren
r_goto
id|out
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* having verified that the proposed changes are legal,&n;           we now put them into effect. */
r_if
c_cond
(paren
id|pid
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|pid
op_eq
op_minus
l_int|1
)paren
multiline_comment|/* all procs other than current and init */
id|cap_set_all
c_func
(paren
op_amp
id|effective
comma
op_amp
id|inheritable
comma
op_amp
id|permitted
)paren
suffix:semicolon
r_else
multiline_comment|/* all procs in process group */
id|cap_set_pg
c_func
(paren
op_minus
id|pid
comma
op_amp
id|effective
comma
op_amp
id|inheritable
comma
op_amp
id|permitted
)paren
suffix:semicolon
)brace
r_else
(brace
id|security_capset_set
c_func
(paren
id|target
comma
op_amp
id|effective
comma
op_amp
id|inheritable
comma
op_amp
id|permitted
)paren
suffix:semicolon
)brace
id|out
suffix:colon
id|read_unlock
c_func
(paren
op_amp
id|tasklist_lock
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|task_capability_lock
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
eof
