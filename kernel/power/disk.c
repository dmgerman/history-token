multiline_comment|/*&n; * kernel/power/disk.c - Suspend-to-disk support.&n; *&n; * Copyright (c) 2003 Patrick Mochel&n; * Copyright (c) 2003 Open Source Development Lab&n; *&n; * This file is released under the GPLv2.&n; *&n; */
macro_line|#include &lt;linux/suspend.h&gt;
macro_line|#include &lt;linux/syscalls.h&gt;
macro_line|#include &lt;linux/reboot.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &quot;power.h&quot;
r_extern
id|u32
id|pm_disk_mode
suffix:semicolon
r_extern
r_struct
id|pm_ops
op_star
id|pm_ops
suffix:semicolon
r_extern
r_int
id|swsusp_suspend
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|swsusp_write
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|swsusp_read
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|swsusp_resume
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|swsusp_free
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|variable|noresume
r_static
r_int
id|noresume
op_assign
l_int|0
suffix:semicolon
DECL|variable|resume_file
r_char
id|resume_file
(braket
l_int|256
)braket
op_assign
id|CONFIG_PM_STD_PARTITION
suffix:semicolon
multiline_comment|/**&n; *&t;power_down - Shut machine down for hibernate.&n; *&t;@mode:&t;&t;Suspend-to-disk mode&n; *&n; *&t;Use the platform driver, if configured so, and return gracefully if it&n; *&t;fails.&n; *&t;Otherwise, try to power off and reboot. If they fail, halt the machine,&n; *&t;there ain&squot;t no turning back.&n; */
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
r_switch
c_cond
(paren
id|mode
)paren
(brace
r_case
id|PM_DISK_PLATFORM
suffix:colon
id|device_power_down
c_func
(paren
id|PM_SUSPEND_DISK
)paren
suffix:semicolon
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
id|device_shutdown
c_func
(paren
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
id|device_shutdown
c_func
(paren
)paren
suffix:semicolon
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
multiline_comment|/* Valid image is on the disk, if we continue we risk serious data corruption&n;&t;   after resume. */
id|printk
c_func
(paren
l_string|&quot;Please power me down manually&bslash;n&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
suffix:semicolon
)brace
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
multiline_comment|/**&n; *&t;free_some_memory -  Try to free as much memory as possible&n; *&n; *&t;... but do not OOM-kill anyone&n; *&n; *&t;Notice: all userland should be stopped at this point, or&n; *&t;livelock is possible.&n; */
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
)brace
DECL|function|platform_finish
r_static
r_inline
r_void
id|platform_finish
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|pm_disk_mode
op_eq
id|PM_DISK_PLATFORM
)paren
(brace
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
id|PM_SUSPEND_DISK
)paren
suffix:semicolon
)brace
)brace
DECL|function|finish
r_static
r_void
id|finish
c_func
(paren
r_void
)paren
(brace
id|device_resume
c_func
(paren
)paren
suffix:semicolon
id|platform_finish
c_func
(paren
)paren
suffix:semicolon
id|enable_nonboot_cpus
c_func
(paren
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
DECL|function|prepare
r_static
r_int
id|prepare
c_func
(paren
r_void
)paren
(brace
r_int
id|error
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
id|EBUSY
suffix:semicolon
r_goto
id|Thaw
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pm_disk_mode
op_eq
id|PM_DISK_PLATFORM
)paren
(brace
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
id|PM_SUSPEND_DISK
)paren
)paren
)paren
r_goto
id|Thaw
suffix:semicolon
)brace
)brace
multiline_comment|/* Free memory before shutting down devices. */
id|free_some_memory
c_func
(paren
)paren
suffix:semicolon
id|disable_nonboot_cpus
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
id|PM_SUSPEND_DISK
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
id|platform_finish
c_func
(paren
)paren
suffix:semicolon
id|Thaw
suffix:colon
id|enable_nonboot_cpus
c_func
(paren
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
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;pm_suspend_disk - The granpappy of power management.&n; *&n; *&t;If we&squot;re going through the firmware, then get it over with quickly.&n; *&n; *&t;If not, then call pmdis to do it&squot;s thing, then figure out how&n; *&t;to power down the system.&n; */
DECL|function|pm_suspend_disk
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
r_if
c_cond
(paren
(paren
id|error
op_assign
id|prepare
c_func
(paren
)paren
)paren
)paren
r_return
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
id|swsusp_suspend
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
multiline_comment|/*&n;&t;&t; * FIXME: Leftover from swsusp. Are they necessary?&n;&t;&t; */
id|mb
c_func
(paren
)paren
suffix:semicolon
id|barrier
c_func
(paren
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
(brace
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
id|finish
c_func
(paren
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;software_resume - Resume from a saved image.&n; *&n; *&t;Called as a late_initcall (so all devices are discovered and&n; *&t;initialized), we call pmdisk to see if we have a saved image or not.&n; *&t;If so, we quiesce devices, the restore the saved image. We will&n; *&t;return above (in pm_suspend_disk() ) if everything goes well.&n; *&t;Otherwise, we fail gracefully and return to the normally&n; *&t;scheduled program.&n; *&n; */
DECL|function|software_resume
r_static
r_int
id|software_resume
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
id|noresume
)paren
(brace
multiline_comment|/**&n;&t;&t; * FIXME: If noresume is specified, we need to find the partition&n;&t;&t; * and reset it back to normal swap space.&n;&t;&t; */
r_return
l_int|0
suffix:semicolon
)brace
id|pr_debug
c_func
(paren
l_string|&quot;PM: Reading pmdisk image.&bslash;n&quot;
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
id|prepare
c_func
(paren
)paren
)paren
)paren
r_goto
id|Free
suffix:semicolon
id|barrier
c_func
(paren
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;PM: Restoring saved image.&bslash;n&quot;
)paren
suffix:semicolon
id|swsusp_resume
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
id|finish
c_func
(paren
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
DECL|variable|software_resume
id|late_initcall
c_func
(paren
id|software_resume
)paren
suffix:semicolon
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
multiline_comment|/**&n; *&t;disk - Control suspend-to-disk mode&n; *&n; *&t;Suspend-to-disk can be handled in several ways. The greatest&n; *&t;distinction is who writes memory to disk - the firmware or the OS.&n; *&t;If the firmware does it, we assume that it also handles suspending&n; *&t;the system.&n; *&t;If the OS does it, then we have three options for putting the system&n; *&t;to sleep - using the platform driver (e.g. ACPI or other PM registers),&n; *&t;powering off the system or rebooting the system (for testing).&n; *&n; *&t;The system will support either &squot;firmware&squot; or &squot;platform&squot;, and that is&n; *&t;known a priori (and encoded in pm_ops). But, the user may choose&n; *&t;&squot;shutdown&squot; or &squot;reboot&squot; as alternatives.&n; *&n; *&t;show() will display what the mode is currently set to.&n; *&t;store() will accept one of&n; *&n; *&t;&squot;firmware&squot;&n; *&t;&squot;platform&squot;&n; *&t;&squot;shutdown&squot;&n; *&t;&squot;reboot&squot;&n; *&n; *&t;It will only change to &squot;firmware&squot; or &squot;platform&squot; if the system&n; *&t;supports it (as determined from pm_ops-&gt;pm_disk_mode).&n; */
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
r_int
id|len
suffix:semicolon
r_char
op_star
id|p
suffix:semicolon
id|u32
id|mode
op_assign
l_int|0
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
id|strncmp
c_func
(paren
id|buf
comma
id|pm_disk_modes
(braket
id|i
)braket
comma
id|len
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
DECL|function|pm_disk_init
r_static
r_int
id|__init
id|pm_disk_init
c_func
(paren
r_void
)paren
(brace
r_return
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
)brace
DECL|variable|pm_disk_init
id|core_initcall
c_func
(paren
id|pm_disk_init
)paren
suffix:semicolon
DECL|function|resume_setup
r_static
r_int
id|__init
id|resume_setup
c_func
(paren
r_char
op_star
id|str
)paren
(brace
r_if
c_cond
(paren
id|noresume
)paren
r_return
l_int|1
suffix:semicolon
id|strncpy
c_func
(paren
id|resume_file
comma
id|str
comma
l_int|255
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|noresume_setup
r_static
r_int
id|__init
id|noresume_setup
c_func
(paren
r_char
op_star
id|str
)paren
(brace
id|noresume
op_assign
l_int|1
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;noresume&quot;
comma
id|noresume_setup
)paren
suffix:semicolon
id|__setup
c_func
(paren
l_string|&quot;resume=&quot;
comma
id|resume_setup
)paren
suffix:semicolon
eof
