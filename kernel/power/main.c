multiline_comment|/*&n; * kernel/power/main.c - PM subsystem core functionality.&n; *&n; * Copyright (c) 2003 Patrick Mochel&n; * Copyright (c) 2003 Open Source Development Lab&n; * &n; * This file is released under the GPLv2&n; *&n; */
macro_line|#include &lt;linux/suspend.h&gt;
macro_line|#include &lt;linux/kobject.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pm.h&gt;
macro_line|#include &quot;power.h&quot;
DECL|variable|pm_sem
id|DECLARE_MUTEX
c_func
(paren
id|pm_sem
)paren
suffix:semicolon
DECL|variable|pm_ops
r_struct
id|pm_ops
op_star
id|pm_ops
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|pm_disk_mode
id|suspend_disk_method_t
id|pm_disk_mode
op_assign
id|PM_DISK_SHUTDOWN
suffix:semicolon
multiline_comment|/**&n; *&t;pm_set_ops - Set the global power method table. &n; *&t;@ops:&t;Pointer to ops structure.&n; */
DECL|function|pm_set_ops
r_void
id|pm_set_ops
c_func
(paren
r_struct
id|pm_ops
op_star
id|ops
)paren
(brace
id|down
c_func
(paren
op_amp
id|pm_sem
)paren
suffix:semicolon
id|pm_ops
op_assign
id|ops
suffix:semicolon
id|up
c_func
(paren
op_amp
id|pm_sem
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;suspend_prepare - Do prep work before entering low-power state.&n; *&t;@state:&t;&t;State we&squot;re entering.&n; *&n; *&t;This is common code that is called for each state that we&squot;re &n; *&t;entering. Allocate a console, stop all processes, then make sure&n; *&t;the platform can enter the requested state.&n; */
DECL|function|suspend_prepare
r_static
r_int
id|suspend_prepare
c_func
(paren
id|suspend_state_t
id|state
)paren
(brace
r_int
id|error
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pm_ops
op_logical_or
op_logical_neg
id|pm_ops-&gt;enter
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
id|pm_prepare_console
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|freeze_processes
c_func
(paren
)paren
)paren
(brace
id|error
op_assign
op_minus
id|EAGAIN
suffix:semicolon
r_goto
id|Thaw
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pm_ops-&gt;prepare
)paren
(brace
r_if
c_cond
(paren
(paren
id|error
op_assign
id|pm_ops
op_member_access_from_pointer
id|prepare
c_func
(paren
id|state
)paren
)paren
)paren
r_goto
id|Thaw
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|error
op_assign
id|device_suspend
c_func
(paren
id|state
)paren
)paren
)paren
r_goto
id|Finish
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|Finish
suffix:colon
r_if
c_cond
(paren
id|pm_ops-&gt;finish
)paren
id|pm_ops
op_member_access_from_pointer
id|finish
c_func
(paren
id|state
)paren
suffix:semicolon
id|Thaw
suffix:colon
id|thaw_processes
c_func
(paren
)paren
suffix:semicolon
id|pm_restore_console
c_func
(paren
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|function|suspend_enter
r_static
r_int
id|suspend_enter
c_func
(paren
id|u32
id|state
)paren
(brace
r_int
id|error
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|error
op_assign
id|device_power_down
c_func
(paren
id|state
)paren
)paren
)paren
r_goto
id|Done
suffix:semicolon
id|error
op_assign
id|pm_ops
op_member_access_from_pointer
id|enter
c_func
(paren
id|state
)paren
suffix:semicolon
id|device_power_up
c_func
(paren
)paren
suffix:semicolon
id|Done
suffix:colon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;suspend_finish - Do final work before exiting suspend sequence.&n; *&t;@state:&t;&t;State we&squot;re coming out of.&n; *&n; *&t;Call platform code to clean up, restart processes, and free the &n; *&t;console that we&squot;ve allocated.&n; */
DECL|function|suspend_finish
r_static
r_void
id|suspend_finish
c_func
(paren
id|suspend_state_t
id|state
)paren
(brace
id|device_resume
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pm_ops
op_logical_and
id|pm_ops-&gt;finish
)paren
id|pm_ops
op_member_access_from_pointer
id|finish
c_func
(paren
id|state
)paren
suffix:semicolon
id|thaw_processes
c_func
(paren
)paren
suffix:semicolon
id|pm_restore_console
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|pm_states
r_char
op_star
id|pm_states
(braket
)braket
op_assign
(brace
(braket
id|PM_SUSPEND_STANDBY
)braket
op_assign
l_string|&quot;standby&quot;
comma
(braket
id|PM_SUSPEND_MEM
)braket
op_assign
l_string|&quot;mem&quot;
comma
(braket
id|PM_SUSPEND_DISK
)braket
op_assign
l_string|&quot;disk&quot;
comma
l_int|NULL
comma
)brace
suffix:semicolon
multiline_comment|/**&n; *&t;enter_state - Do common work of entering low-power state.&n; *&t;@state:&t;&t;pm_state structure for state we&squot;re entering.&n; *&n; *&t;Make sure we&squot;re the only ones trying to enter a sleep state. Fail&n; *&t;if someone has beat us to it, since we don&squot;t want anything weird to&n; *&t;happen when we wake up.&n; *&t;Then, do the setup for suspend, enter the state, and cleaup (after&n; *&t;we&squot;ve woken up).&n; */
DECL|function|enter_state
r_static
r_int
id|enter_state
c_func
(paren
id|suspend_state_t
id|state
)paren
(brace
r_int
id|error
suffix:semicolon
r_if
c_cond
(paren
id|down_trylock
c_func
(paren
op_amp
id|pm_sem
)paren
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
multiline_comment|/* Suspend is hard to get right on SMP. */
r_if
c_cond
(paren
id|num_online_cpus
c_func
(paren
)paren
op_ne
l_int|1
)paren
(brace
id|error
op_assign
op_minus
id|EPERM
suffix:semicolon
r_goto
id|Unlock
suffix:semicolon
)brace
r_if
c_cond
(paren
id|state
op_eq
id|PM_SUSPEND_DISK
)paren
(brace
id|error
op_assign
id|pm_suspend_disk
c_func
(paren
)paren
suffix:semicolon
r_goto
id|Unlock
suffix:semicolon
)brace
id|pr_debug
c_func
(paren
l_string|&quot;PM: Preparing system for suspend&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|error
op_assign
id|suspend_prepare
c_func
(paren
id|state
)paren
)paren
)paren
r_goto
id|Unlock
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;PM: Entering state.&bslash;n&quot;
)paren
suffix:semicolon
id|error
op_assign
id|suspend_enter
c_func
(paren
id|state
)paren
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;PM: Finishing up.&bslash;n&quot;
)paren
suffix:semicolon
id|suspend_finish
c_func
(paren
id|state
)paren
suffix:semicolon
id|Unlock
suffix:colon
id|up
c_func
(paren
op_amp
id|pm_sem
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/*&n; * This is main interface to the outside world. It needs to be&n; * called from process context.&n; */
DECL|function|software_suspend
r_int
id|software_suspend
c_func
(paren
r_void
)paren
(brace
r_return
id|enter_state
c_func
(paren
id|PM_SUSPEND_DISK
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;pm_suspend - Externally visible function for suspending system.&n; *&t;@state:&t;&t;Enumarted value of state to enter.&n; *&n; *&t;Determine whether or not value is within range, get state &n; *&t;structure, and enter (above).&n; */
DECL|function|pm_suspend
r_int
id|pm_suspend
c_func
(paren
id|suspend_state_t
id|state
)paren
(brace
r_if
c_cond
(paren
id|state
OG
id|PM_SUSPEND_ON
op_logical_and
id|state
OL
id|PM_SUSPEND_MAX
)paren
r_return
id|enter_state
c_func
(paren
id|state
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|decl_subsys
c_func
(paren
id|power
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/**&n; *&t;state - control system power state.&n; *&n; *&t;show() returns what states are supported, which is hard-coded to&n; *&t;&squot;standby&squot; (Power-On Suspend), &squot;mem&squot; (Suspend-to-RAM), and&n; *&t;&squot;disk&squot; (Suspend-to-Disk).&n; *&n; *&t;store() accepts one of those strings, translates it into the &n; *&t;proper enumerated value, and initiates a suspend transition.&n; */
DECL|function|state_show
r_static
id|ssize_t
id|state_show
c_func
(paren
r_struct
id|subsystem
op_star
id|subsys
comma
r_char
op_star
id|buf
)paren
(brace
r_int
id|i
suffix:semicolon
r_char
op_star
id|s
op_assign
id|buf
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|PM_SUSPEND_MAX
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|pm_states
(braket
id|i
)braket
)paren
id|s
op_add_assign
id|sprintf
c_func
(paren
id|s
comma
l_string|&quot;%s &quot;
comma
id|pm_states
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
id|s
op_add_assign
id|sprintf
c_func
(paren
id|s
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_return
(paren
id|s
op_minus
id|buf
)paren
suffix:semicolon
)brace
DECL|function|state_store
r_static
id|ssize_t
id|state_store
c_func
(paren
r_struct
id|subsystem
op_star
id|subsys
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|n
)paren
(brace
id|suspend_state_t
id|state
op_assign
id|PM_SUSPEND_STANDBY
suffix:semicolon
r_char
op_star
op_star
id|s
suffix:semicolon
r_char
op_star
id|p
suffix:semicolon
r_int
id|error
suffix:semicolon
r_int
id|len
suffix:semicolon
id|p
op_assign
id|memchr
c_func
(paren
id|buf
comma
l_char|&squot;&bslash;n&squot;
comma
id|n
)paren
suffix:semicolon
id|len
op_assign
id|p
ques
c_cond
id|p
op_minus
id|buf
suffix:colon
id|n
suffix:semicolon
r_for
c_loop
(paren
id|s
op_assign
op_amp
id|pm_states
(braket
id|state
)braket
suffix:semicolon
id|state
OL
id|PM_SUSPEND_MAX
suffix:semicolon
id|s
op_increment
comma
id|state
op_increment
)paren
(brace
r_if
c_cond
(paren
op_star
id|s
op_logical_and
op_logical_neg
id|strncmp
c_func
(paren
id|buf
comma
op_star
id|s
comma
id|len
)paren
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_star
id|s
)paren
id|error
op_assign
id|enter_state
c_func
(paren
id|state
)paren
suffix:semicolon
r_else
id|error
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_return
id|error
ques
c_cond
id|error
suffix:colon
id|n
suffix:semicolon
)brace
DECL|variable|state
id|power_attr
c_func
(paren
id|state
)paren
suffix:semicolon
DECL|variable|g
r_static
r_struct
id|attribute
op_star
id|g
(braket
)braket
op_assign
(brace
op_amp
id|state_attr.attr
comma
l_int|NULL
comma
)brace
suffix:semicolon
DECL|variable|attr_group
r_static
r_struct
id|attribute_group
id|attr_group
op_assign
(brace
dot
id|attrs
op_assign
id|g
comma
)brace
suffix:semicolon
DECL|function|pm_init
r_static
r_int
id|__init
id|pm_init
c_func
(paren
r_void
)paren
(brace
r_int
id|error
op_assign
id|subsystem_register
c_func
(paren
op_amp
id|power_subsys
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
id|error
op_assign
id|sysfs_create_group
c_func
(paren
op_amp
id|power_subsys.kset.kobj
comma
op_amp
id|attr_group
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|variable|pm_init
id|core_initcall
c_func
(paren
id|pm_init
)paren
suffix:semicolon
eof
