multiline_comment|/*&n; * kernel/power/main.c - PM subsystem core functionality.&n; *&n; * Copyright (c) 2003 Patrick Mochel&n; * Copyright (c) 2003 Open Source Development Lab&n; * &n; * This file is release under the GPLv2&n; *&n; */
macro_line|#include &lt;linux/suspend.h&gt;
macro_line|#include &lt;linux/kobject.h&gt;
macro_line|#include &lt;linux/reboot.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pm.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &quot;power.h&quot;
r_static
id|DECLARE_MUTEX
c_func
(paren
id|pm_sem
)paren
suffix:semicolon
DECL|variable|pm_ops
r_static
r_struct
id|pm_ops
op_star
id|pm_ops
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|pm_disk_mode
r_static
id|u32
id|pm_disk_mode
op_assign
id|PM_DISK_SHUTDOWN
suffix:semicolon
macro_line|#ifdef CONFIG_SOFTWARE_SUSPEND
DECL|variable|have_swsusp
r_static
r_int
id|have_swsusp
op_assign
l_int|1
suffix:semicolon
macro_line|#else
DECL|variable|have_swsusp
r_static
r_int
id|have_swsusp
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
r_extern
r_int
id|sys_sync
c_func
(paren
r_void
)paren
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
r_if
c_cond
(paren
id|ops-&gt;pm_disk_mode
op_logical_and
id|ops-&gt;pm_disk_mode
OL
id|PM_DISK_MAX
)paren
id|pm_disk_mode
op_assign
id|ops-&gt;pm_disk_mode
suffix:semicolon
id|up
c_func
(paren
op_amp
id|pm_sem
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;pm_suspend_standby - Enter &squot;standby&squot; state.&n; *&t;&n; *&t;&squot;standby&squot; is also known as &squot;Power-On Suspend&squot;. Here, we power down&n; *&t;devices, disable interrupts, and enter the state.&n; */
DECL|function|pm_suspend_standby
r_static
r_int
id|pm_suspend_standby
c_func
(paren
r_void
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
id|PM_SUSPEND_STANDBY
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
id|PM_SUSPEND_STANDBY
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
id|device_power_up
c_func
(paren
)paren
suffix:semicolon
id|Done
suffix:colon
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;pm_suspend_mem - Enter suspend-to-RAM state.&n; *&n; *&t;Identical to pm_suspend_standby() - we power down devices, disable &n; *&t;interrupts, and enter the low-power state.&n; */
DECL|function|pm_suspend_mem
r_static
r_int
id|pm_suspend_mem
c_func
(paren
r_void
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
id|PM_SUSPEND_STANDBY
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
id|PM_SUSPEND_STANDBY
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
id|device_power_up
c_func
(paren
)paren
suffix:semicolon
id|Done
suffix:colon
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;power_down - Shut machine down for hibernate.&n; *&t;@mode:&t;&t;Suspend-to-disk mode&n; *&n; *&t;Use the platform driver, if configured so, and return gracefully if it&n; *&t;fails. &n; *&t;Otherwise, try to power off and reboot. If they fail, halt the machine,&n; *&t;there ain&squot;t no turning back.&n; */
DECL|function|power_down
r_static
r_int
id|power_down
c_func
(paren
id|u32
id|mode
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|error
op_assign
l_int|0
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|device_power_down
c_func
(paren
id|PM_SUSPEND_DISK
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|mode
)paren
(brace
r_case
id|PM_DISK_PLATFORM
suffix:colon
id|error
op_assign
id|pm_ops
op_member_access_from_pointer
id|enter
c_func
(paren
id|PM_SUSPEND_DISK
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PM_DISK_SHUTDOWN
suffix:colon
id|printk
c_func
(paren
l_string|&quot;Powering off system&bslash;n&quot;
)paren
suffix:semicolon
id|machine_power_off
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PM_DISK_REBOOT
suffix:colon
id|machine_restart
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|machine_halt
c_func
(paren
)paren
suffix:semicolon
id|device_power_up
c_func
(paren
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|__nosavedata
r_static
r_int
id|in_suspend
id|__nosavedata
op_assign
l_int|0
suffix:semicolon
multiline_comment|/**&n; *&t;free_some_memory -  Try to free as much memory as possible&n; *&n; *&t;... but do not OOM-kill anyone&n; *&n; *&t;Notice: all userland should be stopped at this point, or &n; *&t;livelock is possible.&n; */
DECL|function|free_some_memory
r_static
r_void
id|free_some_memory
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Freeing memory: &quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
id|shrink_all_memory
c_func
(paren
l_int|10000
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;.&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;|&bslash;n&quot;
)paren
suffix:semicolon
id|blk_run_queues
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;pm_suspend_disk - The granpappy of power management.&n; *&t;&n; *&t;If we&squot;re going through the firmware, then get it over with quickly.&n; *&n; *&t;If not, then call swsusp to do it&squot;s thing, then figure out how&n; *&t;to power down the system.&n; */
DECL|function|pm_suspend_disk
r_static
r_int
id|pm_suspend_disk
c_func
(paren
r_void
)paren
(brace
r_int
id|error
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;PM: Attempting to suspend to disk.&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pm_disk_mode
op_eq
id|PM_DISK_FIRMWARE
)paren
r_return
id|pm_ops
op_member_access_from_pointer
id|enter
c_func
(paren
id|PM_SUSPEND_DISK
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|have_swsusp
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;PM: snapshotting memory.&bslash;n&quot;
)paren
suffix:semicolon
id|in_suspend
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
(paren
id|error
op_assign
id|swsusp_save
c_func
(paren
)paren
)paren
)paren
r_goto
id|Done
suffix:semicolon
r_if
c_cond
(paren
id|in_suspend
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;PM: writing image.&bslash;n&quot;
)paren
suffix:semicolon
id|error
op_assign
id|swsusp_write
c_func
(paren
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
id|power_down
c_func
(paren
id|pm_disk_mode
)paren
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;PM: Power down failed.&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
id|pr_debug
c_func
(paren
l_string|&quot;PM: Image restored successfully.&bslash;n&quot;
)paren
suffix:semicolon
id|swsusp_free
c_func
(paren
)paren
suffix:semicolon
id|Done
suffix:colon
r_return
id|error
suffix:semicolon
)brace
DECL|macro|decl_state
mdefine_line|#define decl_state(_name) &bslash;&n;&t;{ .name = __stringify(_name), .fn = pm_suspend_##_name }
DECL|struct|pm_state
r_struct
id|pm_state
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|fn
r_int
(paren
op_star
id|fn
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|variable|pm_states
)brace
id|pm_states
(braket
)braket
op_assign
(brace
(braket
id|PM_SUSPEND_STANDBY
)braket
op_assign
id|decl_state
c_func
(paren
id|standby
)paren
comma
(braket
id|PM_SUSPEND_MEM
)braket
op_assign
id|decl_state
c_func
(paren
id|mem
)paren
comma
(braket
id|PM_SUSPEND_DISK
)braket
op_assign
id|decl_state
c_func
(paren
id|disk
)paren
comma
(brace
l_int|NULL
)brace
comma
)brace
suffix:semicolon
multiline_comment|/**&n; *&t;suspend_prepare - Do prep work before entering low-power state.&n; *&t;@state:&t;&t;State we&squot;re entering.&n; *&n; *&t;This is common code that is called for each state that we&squot;re &n; *&t;entering. Allocate a console, stop all processes, then make sure&n; *&t;the platform can enter the requested state.&n; */
DECL|function|suspend_prepare
r_static
r_int
id|suspend_prepare
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
id|pm_prepare_console
c_func
(paren
)paren
suffix:semicolon
id|sys_sync
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
id|pm_ops
op_logical_and
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
multiline_comment|/* Free memory before shutting down devices. */
r_if
c_cond
(paren
id|state
op_eq
id|PM_SUSPEND_DISK
)paren
id|free_some_memory
c_func
(paren
)paren
suffix:semicolon
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
id|Done
suffix:colon
id|pm_restore_console
c_func
(paren
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
id|Finish
suffix:colon
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
id|Thaw
suffix:colon
id|thaw_processes
c_func
(paren
)paren
suffix:semicolon
r_goto
id|Done
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;suspend_finish - Do final work before exiting suspend sequence.&n; *&t;@state:&t;&t;State we&squot;re coming out of.&n; *&n; *&t;Call platform code to clean up, restart processes, and free the &n; *&t;console that we&squot;ve allocated.&n; */
DECL|function|suspend_finish
r_static
r_void
id|suspend_finish
c_func
(paren
id|u32
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
multiline_comment|/**&n; *&t;enter_state - Do common work of entering low-power state.&n; *&t;@state:&t;&t;pm_state structure for state we&squot;re entering.&n; *&n; *&t;Make sure we&squot;re the only ones trying to enter a sleep state. Fail&n; *&t;if someone has beat us to it, since we don&squot;t want anything weird to&n; *&t;happen when we wake up.&n; *&t;Then, do the setup for suspend, enter the state, and cleaup (after&n; *&t;we&squot;ve woken up).&n; */
DECL|function|enter_state
r_static
r_int
id|enter_state
c_func
(paren
id|u32
id|state
)paren
(brace
r_int
id|error
suffix:semicolon
r_struct
id|pm_state
op_star
id|s
op_assign
op_amp
id|pm_states
(braket
id|state
)braket
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
id|s
op_member_access_from_pointer
id|fn
c_func
(paren
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
multiline_comment|/**&n; *&t;pm_suspend - Externally visible function for suspending system.&n; *&t;@state:&t;&t;Enumarted value of state to enter.&n; *&n; *&t;Determine whether or not value is within range, get state &n; *&t;structure, and enter (above).&n; */
DECL|function|pm_suspend
r_int
id|pm_suspend
c_func
(paren
id|u32
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
multiline_comment|/**&n; *&t;pm_resume - Resume from a saved image.&n; *&n; *&t;Called as a late_initcall (so all devices are discovered and &n; *&t;initialized), we call swsusp to see if we have a saved image or not.&n; *&t;If so, we quiesce devices, the restore the saved image. We will &n; *&t;return above (in pm_suspend_disk() ) if everything goes well. &n; *&t;Otherwise, we fail gracefully and return to the normally &n; *&t;scheduled program.&n; *&n; */
DECL|function|pm_resume
r_static
r_int
id|pm_resume
c_func
(paren
r_void
)paren
(brace
r_int
id|error
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|have_swsusp
)paren
r_return
l_int|0
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;PM: Reading swsusp image.&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|error
op_assign
id|swsusp_read
c_func
(paren
)paren
)paren
)paren
r_goto
id|Done
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;PM: Preparing system for restore.&bslash;n&quot;
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
id|PM_SUSPEND_DISK
)paren
)paren
)paren
r_goto
id|Free
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;PM: Restoring saved image.&bslash;n&quot;
)paren
suffix:semicolon
id|swsusp_restore
c_func
(paren
)paren
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;PM: Restore failed, recovering.n&quot;
)paren
suffix:semicolon
id|suspend_finish
c_func
(paren
id|PM_SUSPEND_DISK
)paren
suffix:semicolon
id|Free
suffix:colon
id|swsusp_free
c_func
(paren
)paren
suffix:semicolon
id|Done
suffix:colon
id|pr_debug
c_func
(paren
l_string|&quot;PM: Resume from disk failed.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|pm_resume
id|late_initcall
c_func
(paren
id|pm_resume
)paren
suffix:semicolon
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
DECL|macro|power_attr
mdefine_line|#define power_attr(_name) &bslash;&n;static struct subsys_attribute _name##_attr = {&t;&bslash;&n;&t;.attr&t;= {&t;&t;&t;&t;&bslash;&n;&t;&t;.name = __stringify(_name),&t;&bslash;&n;&t;&t;.mode = 0644,&t;&t;&t;&bslash;&n;&t;},&t;&t;&t;&t;&t;&bslash;&n;&t;.show&t;= _name##_show,&t;&t;&t;&bslash;&n;&t;.store&t;= _name##_store,&t;&t;&bslash;&n;}
DECL|variable|pm_disk_modes
r_static
r_char
op_star
id|pm_disk_modes
(braket
)braket
op_assign
(brace
(braket
id|PM_DISK_FIRMWARE
)braket
op_assign
l_string|&quot;firmware&quot;
comma
(braket
id|PM_DISK_PLATFORM
)braket
op_assign
l_string|&quot;platform&quot;
comma
(braket
id|PM_DISK_SHUTDOWN
)braket
op_assign
l_string|&quot;shutdown&quot;
comma
(braket
id|PM_DISK_REBOOT
)braket
op_assign
l_string|&quot;reboot&quot;
comma
)brace
suffix:semicolon
multiline_comment|/**&n; *&t;disk - Control suspend-to-disk mode&n; *&n; *&t;Suspend-to-disk can be handled in several ways. The greatest &n; *&t;distinction is who writes memory to disk - the firmware or the OS.&n; *&t;If the firmware does it, we assume that it also handles suspending &n; *&t;the system.&n; *&t;If the OS does it, then we have three options for putting the system&n; *&t;to sleep - using the platform driver (e.g. ACPI or other PM registers),&n; *&t;powering off the system or rebooting the system (for testing). &n; *&n; *&t;The system will support either &squot;firmware&squot; or &squot;platform&squot;, and that is&n; *&t;known a priori (and encoded in pm_ops). But, the user may choose&n; *&t;&squot;shutdown&squot; or &squot;reboot&squot; as alternatives.&n; *&n; *&t;show() will display what the mode is currently set to. &n; *&t;store() will accept one of&n; *&n; *&t;&squot;firmware&squot;&n; *&t;&squot;platform&squot;&n; *&t;&squot;shutdown&squot;&n; *&t;&squot;reboot&squot;&n; *&n; *&t;It will only change to &squot;firmware&squot; or &squot;platform&squot; if the system&n; *&t;supports it (as determined from pm_ops-&gt;pm_disk_mode).&n; */
DECL|function|disk_show
r_static
id|ssize_t
id|disk_show
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
r_return
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%s&bslash;n&quot;
comma
id|pm_disk_modes
(braket
id|pm_disk_mode
)braket
)paren
suffix:semicolon
)brace
DECL|function|disk_store
r_static
id|ssize_t
id|disk_store
c_func
(paren
r_struct
id|subsystem
op_star
id|s
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
r_int
id|error
op_assign
l_int|0
suffix:semicolon
r_int
id|i
suffix:semicolon
id|u32
id|mode
op_assign
l_int|0
suffix:semicolon
id|down
c_func
(paren
op_amp
id|pm_sem
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|PM_DISK_FIRMWARE
suffix:semicolon
id|i
OL
id|PM_DISK_MAX
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|buf
comma
id|pm_disk_modes
(braket
id|i
)braket
)paren
)paren
(brace
id|mode
op_assign
id|i
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|mode
)paren
(brace
r_if
c_cond
(paren
id|mode
op_eq
id|PM_DISK_SHUTDOWN
op_logical_or
id|mode
op_eq
id|PM_DISK_REBOOT
)paren
id|pm_disk_mode
op_assign
id|mode
suffix:semicolon
r_else
(brace
r_if
c_cond
(paren
id|pm_ops
op_logical_and
id|pm_ops-&gt;enter
op_logical_and
(paren
id|mode
op_eq
id|pm_ops-&gt;pm_disk_mode
)paren
)paren
id|pm_disk_mode
op_assign
id|mode
suffix:semicolon
r_else
id|error
op_assign
op_minus
id|EINVAL
suffix:semicolon
)brace
)brace
r_else
id|error
op_assign
op_minus
id|EINVAL
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;PM: suspend-to-disk mode set to &squot;%s&squot;&bslash;n&quot;
comma
id|pm_disk_modes
(braket
id|mode
)braket
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|pm_sem
)paren
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
DECL|variable|disk
id|power_attr
c_func
(paren
id|disk
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
dot
id|name
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
dot
id|name
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
id|u32
id|state
op_assign
id|PM_SUSPEND_STANDBY
suffix:semicolon
r_struct
id|pm_state
op_star
id|s
suffix:semicolon
r_int
id|error
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
id|s-&gt;name
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
op_logical_neg
id|strcmp
c_func
(paren
id|buf
comma
id|s-&gt;name
)paren
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|s-&gt;name
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
op_amp
id|disk_attr.attr
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
