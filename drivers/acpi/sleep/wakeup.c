multiline_comment|/*&n; * wakeup.c - support wakeup devices&n; * Copyright (C) 2004 Li Shaohua &lt;shaohua.li@intel.com&gt;&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/acpi.h&gt;
macro_line|#include &lt;acpi/acpi_drivers.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;acpi/acevents.h&gt;
macro_line|#include &quot;sleep.h&quot;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT&t;&t;ACPI_SYSTEM_COMPONENT
id|ACPI_MODULE_NAME
(paren
l_string|&quot;wakeup_devices&quot;
)paren
r_extern
r_struct
id|list_head
id|acpi_wakeup_device_list
suffix:semicolon
r_extern
id|spinlock_t
id|acpi_device_lock
suffix:semicolon
macro_line|#ifdef CONFIG_ACPI_SLEEP
multiline_comment|/**&n; * acpi_enable_wakeup_device_prep - prepare wakeup devices&n; *&t;@sleep_state:&t;ACPI state&n; * Enable all wakup devices power if the devices&squot; wakeup level&n; * is higher than requested sleep level&n; */
r_void
DECL|function|acpi_enable_wakeup_device_prep
id|acpi_enable_wakeup_device_prep
c_func
(paren
id|u8
id|sleep_state
)paren
(brace
r_struct
id|list_head
op_star
id|node
comma
op_star
id|next
suffix:semicolon
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_enable_wakeup_device_prep&quot;
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|acpi_device_lock
)paren
suffix:semicolon
id|list_for_each_safe
c_func
(paren
id|node
comma
id|next
comma
op_amp
id|acpi_wakeup_device_list
)paren
(brace
r_struct
id|acpi_device
op_star
id|dev
op_assign
id|container_of
c_func
(paren
id|node
comma
r_struct
id|acpi_device
comma
id|wakeup_list
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;wakeup.flags.valid
op_logical_or
op_logical_neg
id|dev-&gt;wakeup.state.enabled
op_logical_or
(paren
id|sleep_state
OG
(paren
id|u32
)paren
id|dev-&gt;wakeup.sleep_state
)paren
)paren
r_continue
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|acpi_device_lock
)paren
suffix:semicolon
id|acpi_enable_wakeup_device_power
c_func
(paren
id|dev
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|acpi_device_lock
)paren
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|acpi_device_lock
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * acpi_enable_wakeup_device - enable wakeup devices&n; *&t;@sleep_state:&t;ACPI state&n; * Enable all wakup devices&squot;s GPE&n; */
r_void
DECL|function|acpi_enable_wakeup_device
id|acpi_enable_wakeup_device
c_func
(paren
id|u8
id|sleep_state
)paren
(brace
r_struct
id|list_head
op_star
id|node
comma
op_star
id|next
suffix:semicolon
multiline_comment|/* &n;&t; * Caution: this routine must be invoked when interrupt is disabled &n;&t; * Refer ACPI2.0: P212&n;&t; */
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_enable_wakeup_device&quot;
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|acpi_device_lock
)paren
suffix:semicolon
id|list_for_each_safe
c_func
(paren
id|node
comma
id|next
comma
op_amp
id|acpi_wakeup_device_list
)paren
(brace
r_struct
id|acpi_device
op_star
id|dev
op_assign
id|container_of
c_func
(paren
id|node
comma
r_struct
id|acpi_device
comma
id|wakeup_list
)paren
suffix:semicolon
multiline_comment|/* If users want to disable run-wake GPE,&n;&t;&t; * we only disable it for wake and leave it for runtime&n;&t;&t; */
r_if
c_cond
(paren
id|dev-&gt;wakeup.flags.run_wake
op_logical_and
op_logical_neg
id|dev-&gt;wakeup.state.enabled
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|acpi_device_lock
)paren
suffix:semicolon
id|acpi_set_gpe_type
c_func
(paren
id|dev-&gt;wakeup.gpe_device
comma
id|dev-&gt;wakeup.gpe_number
comma
id|ACPI_GPE_TYPE_RUNTIME
)paren
suffix:semicolon
multiline_comment|/* Re-enable it, since set_gpe_type will disable it */
id|acpi_enable_gpe
c_func
(paren
id|dev-&gt;wakeup.gpe_device
comma
id|dev-&gt;wakeup.gpe_number
comma
id|ACPI_ISR
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|acpi_device_lock
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;wakeup.flags.valid
op_logical_or
op_logical_neg
id|dev-&gt;wakeup.state.enabled
op_logical_or
(paren
id|sleep_state
OG
(paren
id|u32
)paren
id|dev-&gt;wakeup.sleep_state
)paren
)paren
r_continue
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|acpi_device_lock
)paren
suffix:semicolon
multiline_comment|/* run-wake GPE has been enabled */
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;wakeup.flags.run_wake
)paren
id|acpi_enable_gpe
c_func
(paren
id|dev-&gt;wakeup.gpe_device
comma
id|dev-&gt;wakeup.gpe_number
comma
id|ACPI_ISR
)paren
suffix:semicolon
id|dev-&gt;wakeup.state.active
op_assign
l_int|1
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|acpi_device_lock
)paren
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|acpi_device_lock
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * acpi_disable_wakeup_device - disable devices&squot; wakeup capability&n; *&t;@sleep_state:&t;ACPI state&n; * Disable all wakup devices&squot;s GPE and wakeup capability&n; */
r_void
DECL|function|acpi_disable_wakeup_device
id|acpi_disable_wakeup_device
(paren
id|u8
id|sleep_state
)paren
(brace
r_struct
id|list_head
op_star
id|node
comma
op_star
id|next
suffix:semicolon
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_disable_wakeup_device&quot;
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|acpi_device_lock
)paren
suffix:semicolon
id|list_for_each_safe
c_func
(paren
id|node
comma
id|next
comma
op_amp
id|acpi_wakeup_device_list
)paren
(brace
r_struct
id|acpi_device
op_star
id|dev
op_assign
id|container_of
c_func
(paren
id|node
comma
r_struct
id|acpi_device
comma
id|wakeup_list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;wakeup.flags.run_wake
op_logical_and
op_logical_neg
id|dev-&gt;wakeup.state.enabled
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|acpi_device_lock
)paren
suffix:semicolon
id|acpi_set_gpe_type
c_func
(paren
id|dev-&gt;wakeup.gpe_device
comma
id|dev-&gt;wakeup.gpe_number
comma
id|ACPI_GPE_TYPE_WAKE_RUN
)paren
suffix:semicolon
multiline_comment|/* Re-enable it, since set_gpe_type will disable it */
id|acpi_enable_gpe
c_func
(paren
id|dev-&gt;wakeup.gpe_device
comma
id|dev-&gt;wakeup.gpe_number
comma
id|ACPI_NOT_ISR
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|acpi_device_lock
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;wakeup.flags.valid
op_logical_or
op_logical_neg
id|dev-&gt;wakeup.state.active
op_logical_or
(paren
id|sleep_state
OG
(paren
id|u32
)paren
id|dev-&gt;wakeup.sleep_state
)paren
)paren
r_continue
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|acpi_device_lock
)paren
suffix:semicolon
id|acpi_disable_wakeup_device_power
c_func
(paren
id|dev
)paren
suffix:semicolon
multiline_comment|/* Never disable run-wake GPE */
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;wakeup.flags.run_wake
)paren
(brace
id|acpi_disable_gpe
c_func
(paren
id|dev-&gt;wakeup.gpe_device
comma
id|dev-&gt;wakeup.gpe_number
comma
id|ACPI_NOT_ISR
)paren
suffix:semicolon
id|acpi_clear_gpe
c_func
(paren
id|dev-&gt;wakeup.gpe_device
comma
id|dev-&gt;wakeup.gpe_number
comma
id|ACPI_NOT_ISR
)paren
suffix:semicolon
)brace
id|dev-&gt;wakeup.state.active
op_assign
l_int|0
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|acpi_device_lock
)paren
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|acpi_device_lock
)paren
suffix:semicolon
)brace
DECL|function|acpi_wakeup_device_init
r_static
r_int
id|__init
id|acpi_wakeup_device_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|list_head
op_star
id|node
comma
op_star
id|next
suffix:semicolon
r_if
c_cond
(paren
id|acpi_disabled
)paren
r_return
l_int|0
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;ACPI wakeup devices: &bslash;n&quot;
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|acpi_device_lock
)paren
suffix:semicolon
id|list_for_each_safe
c_func
(paren
id|node
comma
id|next
comma
op_amp
id|acpi_wakeup_device_list
)paren
(brace
r_struct
id|acpi_device
op_star
id|dev
op_assign
id|container_of
c_func
(paren
id|node
comma
r_struct
id|acpi_device
comma
id|wakeup_list
)paren
suffix:semicolon
multiline_comment|/* In case user doesn&squot;t load button driver */
r_if
c_cond
(paren
id|dev-&gt;wakeup.flags.run_wake
op_logical_and
op_logical_neg
id|dev-&gt;wakeup.state.enabled
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|acpi_device_lock
)paren
suffix:semicolon
id|acpi_set_gpe_type
c_func
(paren
id|dev-&gt;wakeup.gpe_device
comma
id|dev-&gt;wakeup.gpe_number
comma
id|ACPI_GPE_TYPE_WAKE_RUN
)paren
suffix:semicolon
id|acpi_enable_gpe
c_func
(paren
id|dev-&gt;wakeup.gpe_device
comma
id|dev-&gt;wakeup.gpe_number
comma
id|ACPI_NOT_ISR
)paren
suffix:semicolon
id|dev-&gt;wakeup.state.enabled
op_assign
l_int|1
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|acpi_device_lock
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;%4s &quot;
comma
id|dev-&gt;pnp.bus_id
)paren
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|acpi_device_lock
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|acpi_wakeup_device_init
id|late_initcall
c_func
(paren
id|acpi_wakeup_device_init
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Disable all wakeup GPEs before power off.&n; * &n; * Since acpi_enter_sleep_state() will disable all&n; * RUNTIME GPEs, we simply mark all GPES that&n; * are not enabled for wakeup from S5 as RUNTIME.&n; */
DECL|function|acpi_wakeup_gpe_poweroff_prepare
r_void
id|acpi_wakeup_gpe_poweroff_prepare
c_func
(paren
r_void
)paren
(brace
r_struct
id|list_head
op_star
id|node
comma
op_star
id|next
suffix:semicolon
id|list_for_each_safe
c_func
(paren
id|node
comma
id|next
comma
op_amp
id|acpi_wakeup_device_list
)paren
(brace
r_struct
id|acpi_device
op_star
id|dev
op_assign
id|container_of
c_func
(paren
id|node
comma
r_struct
id|acpi_device
comma
id|wakeup_list
)paren
suffix:semicolon
multiline_comment|/* The GPE can wakeup system from S5, don&squot;t touch it */
r_if
c_cond
(paren
(paren
id|u32
)paren
id|dev-&gt;wakeup.sleep_state
op_eq
id|ACPI_STATE_S5
)paren
r_continue
suffix:semicolon
multiline_comment|/* acpi_set_gpe_type will automatically disable GPE */
id|acpi_set_gpe_type
c_func
(paren
id|dev-&gt;wakeup.gpe_device
comma
id|dev-&gt;wakeup.gpe_number
comma
id|ACPI_GPE_TYPE_RUNTIME
)paren
suffix:semicolon
)brace
)brace
eof
