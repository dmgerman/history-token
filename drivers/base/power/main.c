multiline_comment|/*&n; * drivers/base/power/main.c - Where the driver meets power management.&n; *&n; * Copyright (c) 2003 Patrick Mochel&n; * Copyright (c) 2003 Open Source Development Lab&n; *&n; * This file is released under the GPLv2&n; *&n; *&n; * The driver model core calls device_pm_add() when a device is registered.&n; * This will intialize the embedded device_pm_info object in the device&n; * and add it to the list of power-controlled devices. sysfs entries for&n; * controlling device power management will also be added.&n; *&n; * A different set of lists than the global subsystem list are used to &n; * keep track of power info because we use different lists to hold &n; * devices based on what stage of the power management process they &n; * are in. The power domain dependencies may also differ from the &n; * ancestral dependencies that the subsystem list maintains.&n; */
DECL|macro|DEBUG
macro_line|#undef DEBUG
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &quot;power.h&quot;
DECL|variable|dpm_active
id|LIST_HEAD
c_func
(paren
id|dpm_active
)paren
suffix:semicolon
DECL|variable|dpm_off
id|LIST_HEAD
c_func
(paren
id|dpm_off
)paren
suffix:semicolon
DECL|variable|dpm_off_irq
id|LIST_HEAD
c_func
(paren
id|dpm_off_irq
)paren
suffix:semicolon
DECL|variable|dpm_sem
id|DECLARE_MUTEX
c_func
(paren
id|dpm_sem
)paren
suffix:semicolon
multiline_comment|/*&n; * PM Reference Counting.&n; */
DECL|function|device_pm_hold
r_static
r_inline
r_void
id|device_pm_hold
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
id|dev
)paren
id|atomic_inc
c_func
(paren
op_amp
id|dev-&gt;power.pm_users
)paren
suffix:semicolon
)brace
DECL|function|device_pm_release
r_static
r_inline
r_void
id|device_pm_release
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
id|dev
)paren
id|atomic_dec
c_func
(paren
op_amp
id|dev-&gt;power.pm_users
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;device_pm_set_parent - Specify power dependency.&n; *&t;@dev:&t;&t;Device who needs power.&n; *&t;@parent:&t;Device that supplies power.&n; *&n; *&t;This function is used to manually describe a power-dependency&n; *&t;relationship. It may be used to specify a transversal relationship&n; *&t;(where the power supplier is not the physical (or electrical)&n; *&t;ancestor of a specific device.&n; *&t;The effect of this is that the supplier will not be powered down&n; *&t;before the power dependent.&n; */
DECL|function|device_pm_set_parent
r_void
id|device_pm_set_parent
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_struct
id|device
op_star
id|parent
)paren
(brace
r_struct
id|device
op_star
id|old_parent
op_assign
id|dev-&gt;power.pm_parent
suffix:semicolon
id|device_pm_release
c_func
(paren
id|old_parent
)paren
suffix:semicolon
id|dev-&gt;power.pm_parent
op_assign
id|parent
suffix:semicolon
id|device_pm_hold
c_func
(paren
id|parent
)paren
suffix:semicolon
)brace
DECL|variable|device_pm_set_parent
id|EXPORT_SYMBOL
c_func
(paren
id|device_pm_set_parent
)paren
suffix:semicolon
DECL|function|device_pm_add
r_int
id|device_pm_add
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_int
id|error
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;PM: Adding info for %s:%s&bslash;n&quot;
comma
id|dev-&gt;bus
ques
c_cond
id|dev-&gt;bus-&gt;name
suffix:colon
l_string|&quot;No Bus&quot;
comma
id|dev-&gt;kobj.name
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|dev-&gt;power.pm_users
comma
l_int|0
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|dpm_sem
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|dev-&gt;power.entry
comma
op_amp
id|dpm_active
)paren
suffix:semicolon
id|device_pm_set_parent
c_func
(paren
id|dev
comma
id|dev-&gt;parent
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|error
op_assign
id|dpm_sysfs_add
c_func
(paren
id|dev
)paren
)paren
)paren
id|list_del
c_func
(paren
op_amp
id|dev-&gt;power.entry
)paren
suffix:semicolon
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
)brace
DECL|function|device_pm_remove
r_void
id|device_pm_remove
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;PM: Removing info for %s:%s&bslash;n&quot;
comma
id|dev-&gt;bus
ques
c_cond
id|dev-&gt;bus-&gt;name
suffix:colon
l_string|&quot;No Bus&quot;
comma
id|dev-&gt;kobj.name
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|dpm_sem
)paren
suffix:semicolon
id|dpm_sysfs_remove
c_func
(paren
id|dev
)paren
suffix:semicolon
id|device_pm_release
c_func
(paren
id|dev-&gt;power.pm_parent
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|dev-&gt;power.entry
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
eof
