multiline_comment|/*&n; * suspend.c - Functions for putting devices to sleep. &n; *&n; * Copyright (c) 2003 Patrick Mochel&n; * Copyright (c) 2003 Open Source Development Labs&n; *&n; * This file is released under the GPLv2&n; *&n; */
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &quot;power.h&quot;
r_extern
r_int
id|sysdev_suspend
c_func
(paren
id|u32
id|state
)paren
suffix:semicolon
multiline_comment|/*&n; * The entries in the dpm_active list are in a depth first order, simply&n; * because children are guaranteed to be discovered after parents, and &n; * are inserted at the back of the list on discovery. &n; * &n; * All list on the suspend path are done in reverse order, so we operate&n; * on the leaves of the device tree (or forests, depending on how you want&n; * to look at it ;) first. As nodes are removed from the back of the list, &n; * they are inserted into the front of their destintation lists. &n; *&n; * Things are the reverse on the resume path - iterations are done in&n; * forward order, and nodes are inserted at the back of their destination&n; * lists. This way, the ancestors will be accessed before their descendents.&n; */
multiline_comment|/**&n; *&t;suspend_device - Save state of one device.&n; *&t;@dev:&t;Device.&n; *&t;@state:&t;Power state device is entering.&n; */
DECL|function|suspend_device
r_int
id|suspend_device
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
id|u32
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
id|dev-&gt;bus
op_logical_and
id|dev-&gt;bus-&gt;suspend
)paren
id|error
op_assign
id|dev-&gt;bus
op_member_access_from_pointer
id|suspend
c_func
(paren
id|dev
comma
id|state
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
(brace
id|list_del
c_func
(paren
op_amp
id|dev-&gt;power.entry
)paren
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|dev-&gt;power.entry
comma
op_amp
id|dpm_off
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|error
op_eq
op_minus
id|EAGAIN
)paren
(brace
id|list_del
c_func
(paren
op_amp
id|dev-&gt;power.entry
)paren
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|dev-&gt;power.entry
comma
op_amp
id|dpm_off_irq
)paren
suffix:semicolon
)brace
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;device_suspend - Save state and stop all devices in system.&n; *&t;@state:&t;&t;Power state to put each device in. &n; *&n; *&t;Walk the dpm_active list, call -&gt;suspend() for each device, and move&n; *&t;it to dpm_off. &n; *&t;Check the return value for each. If it returns 0, then we move the&n; *&t;the device to the dpm_off list. If it returns -EAGAIN, we move it to &n; *&t;the dpm_off_irq list. If we get a different error, try and back out. &n; *&n; *&t;If we hit a failure with any of the devices, call device_resume()&n; *&t;above to bring the suspended devices back to life. &n; *&n; *&t;Note this function leaves dpm_sem held to&n; *&t;a) block other devices from registering.&n; *&t;b) prevent other PM operations from happening after we&squot;ve begun.&n; *&t;c) make sure we&squot;re exclusive when we disable interrupts.&n; *&n; */
DECL|function|device_suspend
r_int
id|device_suspend
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
id|down
c_func
(paren
op_amp
id|dpm_sem
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|dpm_active
)paren
)paren
(brace
r_struct
id|list_head
op_star
id|entry
op_assign
id|dpm_active.prev
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
r_if
c_cond
(paren
(paren
id|error
op_assign
id|suspend_device
c_func
(paren
id|dev
comma
id|state
)paren
)paren
)paren
r_goto
id|Error
suffix:semicolon
)brace
id|Done
suffix:colon
id|up
c_func
(paren
op_amp
id|dpm_sem
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
id|Error
suffix:colon
id|device_resume
c_func
(paren
)paren
suffix:semicolon
r_goto
id|Done
suffix:semicolon
)brace
DECL|variable|device_suspend
id|EXPORT_SYMBOL
c_func
(paren
id|device_suspend
)paren
suffix:semicolon
multiline_comment|/**&n; *&t;device_power_down - Shut down special devices.&n; *&t;@state:&t;&t;Power state to enter.&n; *&n; *&t;Walk the dpm_off_irq list, calling -&gt;power_down() for each device that&n; *&t;couldn&squot;t power down the device with interrupts enabled. When we&squot;re &n; *&t;done, power down system devices. &n; */
DECL|function|device_power_down
r_int
id|device_power_down
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
r_struct
id|device
op_star
id|dev
suffix:semicolon
id|list_for_each_entry_reverse
c_func
(paren
id|dev
comma
op_amp
id|dpm_off_irq
comma
id|power.entry
)paren
(brace
r_if
c_cond
(paren
(paren
id|error
op_assign
id|suspend_device
c_func
(paren
id|dev
comma
id|state
)paren
)paren
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|error
)paren
r_goto
id|Error
suffix:semicolon
r_if
c_cond
(paren
(paren
id|error
op_assign
id|sysdev_suspend
c_func
(paren
id|state
)paren
)paren
)paren
r_goto
id|Error
suffix:semicolon
id|Done
suffix:colon
r_return
id|error
suffix:semicolon
id|Error
suffix:colon
id|dpm_power_up
c_func
(paren
)paren
suffix:semicolon
r_goto
id|Done
suffix:semicolon
)brace
DECL|variable|device_power_down
id|EXPORT_SYMBOL
c_func
(paren
id|device_power_down
)paren
suffix:semicolon
eof
