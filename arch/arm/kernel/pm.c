multiline_comment|/*&n; *  linux/arch/arm/kernel/suspend.c&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License.&n; *&n; *  This is the common support code for suspending an ARM machine.&n; *  pm_do_suspend() is responsible for actually putting the CPU to&n; *  sleep.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/pm.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/leds.h&gt;
macro_line|#include &lt;asm/system.h&gt;
multiline_comment|/*&n; * Tell the linker that pm_do_suspend may not be present.&n; */
r_extern
r_int
id|pm_do_suspend
c_func
(paren
r_void
)paren
id|__attribute__
c_func
(paren
(paren
id|weak
)paren
)paren
suffix:semicolon
DECL|function|suspend
r_int
id|suspend
c_func
(paren
r_void
)paren
(brace
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pm_do_suspend
)paren
r_return
op_minus
id|ENOSYS
suffix:semicolon
multiline_comment|/*&n;&t; * Suspend &quot;legacy&quot; devices.&n;&t; */
id|ret
op_assign
id|pm_send_all
c_func
(paren
id|PM_SUSPEND
comma
(paren
r_void
op_star
)paren
l_int|3
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ne
l_int|0
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/*&n;&t; * Tell LDM devices we&squot;re going to suspend.&n;&t; */
id|ret
op_assign
id|device_suspend
c_func
(paren
l_int|4
comma
id|SUSPEND_NOTIFY
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ne
l_int|0
)paren
r_goto
id|resume_legacy
suffix:semicolon
multiline_comment|/*&n;&t; * Disable, devices, and save state.&n;&t; */
id|device_suspend
c_func
(paren
l_int|4
comma
id|SUSPEND_DISABLE
)paren
suffix:semicolon
id|device_suspend
c_func
(paren
l_int|4
comma
id|SUSPEND_SAVE_STATE
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Tell devices that they&squot;re going to be powered off.&n;&t; */
id|device_suspend
c_func
(paren
l_int|4
comma
id|SUSPEND_POWER_DOWN
)paren
suffix:semicolon
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
id|leds_event
c_func
(paren
id|led_stop
)paren
suffix:semicolon
id|ret
op_assign
id|pm_do_suspend
c_func
(paren
)paren
suffix:semicolon
id|leds_event
c_func
(paren
id|led_start
)paren
suffix:semicolon
id|local_irq_enable
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Tell devices that they now have power.&n;&t; */
id|device_resume
c_func
(paren
id|RESUME_POWER_ON
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Resume LDM devices.&n;&t; */
id|device_resume
c_func
(paren
id|RESUME_RESTORE_STATE
)paren
suffix:semicolon
id|device_resume
c_func
(paren
id|RESUME_ENABLE
)paren
suffix:semicolon
id|resume_legacy
suffix:colon
multiline_comment|/*&n;&t; * Resume &quot;legacy&quot; devices.&n;&t; */
id|pm_send_all
c_func
(paren
id|PM_RESUME
comma
(paren
r_void
op_star
)paren
l_int|0
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|ret
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_SYSCTL
multiline_comment|/*&n; * We really want this to die.  It&squot;s a disgusting hack using unallocated&n; * sysctl numbers.  We should be using a real interface.&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sysctl.h&gt;
r_static
r_int
DECL|function|pm_sysctl_proc_handler
id|pm_sysctl_proc_handler
c_func
(paren
id|ctl_table
op_star
id|ctl
comma
r_int
id|write
comma
r_struct
id|file
op_star
id|filp
comma
r_void
op_star
id|buffer
comma
r_int
op_star
id|lenp
)paren
(brace
r_int
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;PM: task %s (pid %d) uses deprecated sysctl PM interface&bslash;n&quot;
comma
id|current-&gt;comm
comma
id|current-&gt;pid
)paren
suffix:semicolon
r_if
c_cond
(paren
id|write
)paren
id|ret
op_assign
id|suspend
c_func
(paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * This came from arch/arm/mach-sa1100/pm.c:&n; * Copyright (c) 2001 Cliff Brake &lt;cbrake@accelent.com&gt;&n; *  with modifications by Nicolas Pitre and Russell King.&n; *&n; * ARGH!  ACPI people defined CTL_ACPI in linux/acpi.h rather than&n; * linux/sysctl.h.&n; *&n; * This means our interface here won&squot;t survive long - it needs a new&n; * interface.  Quick hack to get this working - use sysctl id 9999.&n; */
macro_line|#warning ACPI broke the kernel, this interface needs to be fixed up.
DECL|macro|CTL_ACPI
mdefine_line|#define CTL_ACPI 9999
DECL|macro|ACPI_S1_SLP_TYP
mdefine_line|#define ACPI_S1_SLP_TYP 19
DECL|variable|pm_table
r_static
r_struct
id|ctl_table
id|pm_table
(braket
)braket
op_assign
(brace
(brace
dot
id|ctl_name
op_assign
id|ACPI_S1_SLP_TYP
comma
dot
id|procname
op_assign
l_string|&quot;suspend&quot;
comma
dot
id|mode
op_assign
l_int|0200
comma
dot
id|proc_handler
op_assign
id|pm_sysctl_proc_handler
comma
)brace
comma
(brace
l_int|0
)brace
)brace
suffix:semicolon
DECL|variable|pm_dir_table
r_static
r_struct
id|ctl_table
id|pm_dir_table
(braket
)braket
op_assign
(brace
(brace
dot
id|ctl_name
op_assign
id|CTL_ACPI
comma
dot
id|procname
op_assign
l_string|&quot;pm&quot;
comma
dot
id|mode
op_assign
l_int|0555
comma
dot
id|child
op_assign
id|pm_table
comma
)brace
comma
(brace
l_int|0
)brace
)brace
suffix:semicolon
multiline_comment|/*&n; * Initialize power interface&n; */
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
id|register_sysctl_table
c_func
(paren
id|pm_dir_table
comma
l_int|1
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|pm_init
id|fs_initcall
c_func
(paren
id|pm_init
)paren
suffix:semicolon
macro_line|#endif
eof
