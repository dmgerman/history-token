multiline_comment|/*&n; * resume.c - Functions for waking devices up.&n; *&n; * Copyright (c) 2003 Patrick Mochel&n; * Copyright (c) 2003 Open Source Development Labs&n; *&n; * This file is released under the GPLv2&n; *&n; */
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &quot;power.h&quot;
r_extern
r_int
id|sysdev_resume
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/**&n; *&t;resume_device - Restore state for one device.&n; *&t;@dev:&t;Device.&n; *&n; */
DECL|function|resume_device
r_int
id|resume_device
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_if
c_cond
(paren
id|dev-&gt;bus
op_logical_and
id|dev-&gt;bus-&gt;resume
)paren
r_return
id|dev-&gt;bus
op_member_access_from_pointer
id|resume
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dpm_resume
r_void
id|dpm_resume
c_func
(paren
r_void
)paren
(brace
r_while
c_loop
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|dpm_off
)paren
)paren
(brace
r_struct
id|list_head
op_star
id|entry
op_assign
id|dpm_off.next
suffix:semicolon
r_struct
id|device
op_star
id|dev
op_assign
id|to_device
c_func
(paren
id|entry
)paren
suffix:semicolon
id|list_del_init
c_func
(paren
id|entry
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;power.prev_state
)paren
id|resume_device
c_func
(paren
id|dev
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
id|entry
comma
op_amp
id|dpm_active
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/**&n; *&t;device_resume - Restore state of each device in system.&n; *&n; *&t;Walk the dpm_off list, remove each entry, resume the device,&n; *&t;then add it to the dpm_active list. &n; */
DECL|function|device_resume
r_void
id|device_resume
c_func
(paren
r_void
)paren
(brace
id|down
c_func
(paren
op_amp
id|dpm_sem
)paren
suffix:semicolon
id|dpm_resume
c_func
(paren
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|dpm_sem
)paren
suffix:semicolon
)brace
DECL|variable|device_resume
id|EXPORT_SYMBOL
c_func
(paren
id|device_resume
)paren
suffix:semicolon
multiline_comment|/**&n; *&t;device_power_up_irq - Power on some devices. &n; *&n; *&t;Walk the dpm_off_irq list and power each device up. This &n; *&t;is used for devices that required they be powered down with&n; *&t;interrupts disabled. As devices are powered on, they are moved to&n; *&t;the dpm_suspended list.&n; *&n; *&t;Interrupts must be disabled when calling this. &n; */
DECL|function|dpm_power_up
r_void
id|dpm_power_up
c_func
(paren
r_void
)paren
(brace
r_while
c_loop
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|dpm_off_irq
)paren
)paren
(brace
r_struct
id|list_head
op_star
id|entry
op_assign
id|dpm_off_irq.next
suffix:semicolon
id|list_del_init
c_func
(paren
id|entry
)paren
suffix:semicolon
id|resume_device
c_func
(paren
id|to_device
c_func
(paren
id|entry
)paren
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
id|entry
comma
op_amp
id|dpm_active
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/**&n; *&t;device_pm_power_up - Turn on all devices that need special attention.&n; *&n; *&t;Power on system devices then devices that required we shut them down&n; *&t;with interrupts disabled.&n; *&t;Called with interrupts disabled.&n; */
DECL|function|device_power_up
r_void
id|device_power_up
c_func
(paren
r_void
)paren
(brace
id|sysdev_resume
c_func
(paren
)paren
suffix:semicolon
id|dpm_power_up
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|device_power_up
id|EXPORT_SYMBOL
c_func
(paren
id|device_power_up
)paren
suffix:semicolon
eof
