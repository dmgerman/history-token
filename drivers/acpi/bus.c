multiline_comment|/*&n; *  acpi_bus.c - ACPI Bus Driver ($Revision: 80 $)&n; *&n; *  Copyright (C) 2001, 2002 Paul Diefenbaugh &lt;paul.s.diefenbaugh@intel.com&gt;&n; *&n; * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or (at&n; *  your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful, but&n; *  WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n; *  General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License along&n; *  with this program; if not, write to the Free Software Foundation, Inc.,&n; *  59 Temple Place, Suite 330, Boston, MA 02111-1307 USA.&n; *&n; * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/pm.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#ifdef CONFIG_X86
macro_line|#include &lt;asm/mpspec.h&gt;
macro_line|#endif
macro_line|#include &lt;acpi/acpi_bus.h&gt;
macro_line|#include &lt;acpi/acpi_drivers.h&gt;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT&t;&t;ACPI_BUS_COMPONENT
id|ACPI_MODULE_NAME
(paren
l_string|&quot;acpi_bus&quot;
)paren
macro_line|#ifdef&t;CONFIG_X86
r_extern
r_void
id|__init
id|acpi_pic_sci_set_trigger
c_func
(paren
r_int
r_int
id|irq
comma
id|u16
id|trigger
)paren
suffix:semicolon
macro_line|#endif
DECL|variable|acpi_fadt
id|FADT_DESCRIPTOR
id|acpi_fadt
suffix:semicolon
DECL|variable|acpi_fadt
id|EXPORT_SYMBOL
c_func
(paren
id|acpi_fadt
)paren
suffix:semicolon
DECL|variable|acpi_root
r_struct
id|acpi_device
op_star
id|acpi_root
suffix:semicolon
DECL|variable|acpi_root_dir
r_struct
id|proc_dir_entry
op_star
id|acpi_root_dir
suffix:semicolon
DECL|variable|acpi_root_dir
id|EXPORT_SYMBOL
c_func
(paren
id|acpi_root_dir
)paren
suffix:semicolon
DECL|macro|STRUCT_TO_INT
mdefine_line|#define STRUCT_TO_INT(s)&t;(*((int*)&amp;s))
multiline_comment|/* --------------------------------------------------------------------------&n;                                Device Management&n;   -------------------------------------------------------------------------- */
r_int
DECL|function|acpi_bus_get_device
id|acpi_bus_get_device
(paren
id|acpi_handle
id|handle
comma
r_struct
id|acpi_device
op_star
op_star
id|device
)paren
(brace
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_bus_get_device&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|device
)paren
id|return_VALUE
c_func
(paren
op_minus
id|EINVAL
)paren
suffix:semicolon
multiline_comment|/* TBD: Support fixed-feature devices */
id|status
op_assign
id|acpi_get_data
c_func
(paren
id|handle
comma
id|acpi_bus_data_handler
comma
(paren
r_void
op_star
op_star
)paren
id|device
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_FAILURE
c_func
(paren
id|status
)paren
op_logical_or
op_logical_neg
op_star
id|device
)paren
(brace
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_WARN
comma
l_string|&quot;No context for object [%p]&bslash;n&quot;
comma
id|handle
)paren
)paren
suffix:semicolon
id|return_VALUE
c_func
(paren
op_minus
id|ENODEV
)paren
suffix:semicolon
)brace
id|return_VALUE
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
DECL|variable|acpi_bus_get_device
id|EXPORT_SYMBOL
c_func
(paren
id|acpi_bus_get_device
)paren
suffix:semicolon
r_int
DECL|function|acpi_bus_get_status
id|acpi_bus_get_status
(paren
r_struct
id|acpi_device
op_star
id|device
)paren
(brace
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
r_int
r_int
id|sta
op_assign
l_int|0
suffix:semicolon
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_bus_get_status&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|device
)paren
id|return_VALUE
c_func
(paren
op_minus
id|EINVAL
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Evaluate _STA if present.&n;&t; */
r_if
c_cond
(paren
id|device-&gt;flags.dynamic_status
)paren
(brace
id|status
op_assign
id|acpi_evaluate_integer
c_func
(paren
id|device-&gt;handle
comma
l_string|&quot;_STA&quot;
comma
l_int|NULL
comma
op_amp
id|sta
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_FAILURE
c_func
(paren
id|status
)paren
)paren
id|return_VALUE
c_func
(paren
op_minus
id|ENODEV
)paren
suffix:semicolon
id|STRUCT_TO_INT
c_func
(paren
id|device-&gt;status
)paren
op_assign
(paren
r_int
)paren
id|sta
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Otherwise we assume the status of our parent (unless we don&squot;t&n;&t; * have one, in which case status is implied).&n;&t; */
r_else
r_if
c_cond
(paren
id|device-&gt;parent
)paren
id|device-&gt;status
op_assign
id|device-&gt;parent-&gt;status
suffix:semicolon
r_else
id|STRUCT_TO_INT
c_func
(paren
id|device-&gt;status
)paren
op_assign
l_int|0x0F
suffix:semicolon
r_if
c_cond
(paren
id|device-&gt;status.functional
op_logical_and
op_logical_neg
id|device-&gt;status.present
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
id|PREFIX
l_string|&quot;Device [%s] status [%08x]: &quot;
l_string|&quot;functional but not present; setting present&bslash;n&quot;
comma
id|device-&gt;pnp.bus_id
comma
(paren
id|u32
)paren
id|STRUCT_TO_INT
c_func
(paren
id|device-&gt;status
)paren
)paren
suffix:semicolon
id|device-&gt;status.present
op_assign
l_int|1
suffix:semicolon
)brace
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;Device [%s] status [%08x]&bslash;n&quot;
comma
id|device-&gt;pnp.bus_id
comma
(paren
id|u32
)paren
id|STRUCT_TO_INT
c_func
(paren
id|device-&gt;status
)paren
)paren
)paren
suffix:semicolon
id|return_VALUE
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
DECL|variable|acpi_bus_get_status
id|EXPORT_SYMBOL
c_func
(paren
id|acpi_bus_get_status
)paren
suffix:semicolon
multiline_comment|/* --------------------------------------------------------------------------&n;                                 Power Management&n;   -------------------------------------------------------------------------- */
r_int
DECL|function|acpi_bus_get_power
id|acpi_bus_get_power
(paren
id|acpi_handle
id|handle
comma
r_int
op_star
id|state
)paren
(brace
r_int
id|result
op_assign
l_int|0
suffix:semicolon
id|acpi_status
id|status
op_assign
l_int|0
suffix:semicolon
r_struct
id|acpi_device
op_star
id|device
op_assign
l_int|NULL
suffix:semicolon
r_int
r_int
id|psc
op_assign
l_int|0
suffix:semicolon
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_bus_get_power&quot;
)paren
suffix:semicolon
id|result
op_assign
id|acpi_bus_get_device
c_func
(paren
id|handle
comma
op_amp
id|device
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
id|return_VALUE
c_func
(paren
id|result
)paren
suffix:semicolon
op_star
id|state
op_assign
id|ACPI_STATE_UNKNOWN
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|device-&gt;flags.power_manageable
)paren
(brace
multiline_comment|/* TBD: Non-recursive algorithm for walking up hierarchy */
r_if
c_cond
(paren
id|device-&gt;parent
)paren
op_star
id|state
op_assign
id|device-&gt;parent-&gt;power.state
suffix:semicolon
r_else
op_star
id|state
op_assign
id|ACPI_STATE_D0
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t; * Get the device&squot;s power state either directly (via _PSC) or &n;&t;&t; * indirectly (via power resources).&n;&t;&t; */
r_if
c_cond
(paren
id|device-&gt;power.flags.explicit_get
)paren
(brace
id|status
op_assign
id|acpi_evaluate_integer
c_func
(paren
id|device-&gt;handle
comma
l_string|&quot;_PSC&quot;
comma
l_int|NULL
comma
op_amp
id|psc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_FAILURE
c_func
(paren
id|status
)paren
)paren
id|return_VALUE
c_func
(paren
op_minus
id|ENODEV
)paren
suffix:semicolon
id|device-&gt;power.state
op_assign
(paren
r_int
)paren
id|psc
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|device-&gt;power.flags.power_resources
)paren
(brace
id|result
op_assign
id|acpi_power_get_inferred_state
c_func
(paren
id|device
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
id|return_VALUE
c_func
(paren
id|result
)paren
suffix:semicolon
)brace
op_star
id|state
op_assign
id|device-&gt;power.state
suffix:semicolon
)brace
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;Device [%s] power state is D%d&bslash;n&quot;
comma
id|device-&gt;pnp.bus_id
comma
id|device-&gt;power.state
)paren
)paren
suffix:semicolon
id|return_VALUE
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
DECL|variable|acpi_bus_get_power
id|EXPORT_SYMBOL
c_func
(paren
id|acpi_bus_get_power
)paren
suffix:semicolon
r_int
DECL|function|acpi_bus_set_power
id|acpi_bus_set_power
(paren
id|acpi_handle
id|handle
comma
r_int
id|state
)paren
(brace
r_int
id|result
op_assign
l_int|0
suffix:semicolon
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
r_struct
id|acpi_device
op_star
id|device
op_assign
l_int|NULL
suffix:semicolon
r_char
id|object_name
(braket
l_int|5
)braket
op_assign
(brace
l_char|&squot;_&squot;
comma
l_char|&squot;P&squot;
comma
l_char|&squot;S&squot;
comma
l_char|&squot;0&squot;
op_plus
id|state
comma
l_char|&squot;&bslash;0&squot;
)brace
suffix:semicolon
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_bus_set_power&quot;
)paren
suffix:semicolon
id|result
op_assign
id|acpi_bus_get_device
c_func
(paren
id|handle
comma
op_amp
id|device
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
id|return_VALUE
c_func
(paren
id|result
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|state
OL
id|ACPI_STATE_D0
)paren
op_logical_or
(paren
id|state
OG
id|ACPI_STATE_D3
)paren
)paren
id|return_VALUE
c_func
(paren
op_minus
id|EINVAL
)paren
suffix:semicolon
multiline_comment|/* Make sure this is a valid target state */
r_if
c_cond
(paren
op_logical_neg
id|device-&gt;flags.power_manageable
)paren
(brace
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_WARN
comma
l_string|&quot;Device is not power manageable&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|return_VALUE
c_func
(paren
op_minus
id|ENODEV
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|state
op_eq
id|device-&gt;power.state
)paren
(brace
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;Device is already at D%d&bslash;n&quot;
comma
id|state
)paren
)paren
suffix:semicolon
id|return_VALUE
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|device-&gt;power.states
(braket
id|state
)braket
dot
id|flags.valid
)paren
(brace
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_WARN
comma
l_string|&quot;Device does not support D%d&bslash;n&quot;
comma
id|state
)paren
)paren
suffix:semicolon
id|return_VALUE
c_func
(paren
op_minus
id|ENODEV
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|device-&gt;parent
op_logical_and
(paren
id|state
OL
id|device-&gt;parent-&gt;power.state
)paren
)paren
(brace
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_WARN
comma
l_string|&quot;Cannot set device to a higher-powered state than parent&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|return_VALUE
c_func
(paren
op_minus
id|ENODEV
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Transition Power&n;&t; * ----------------&n;&t; * On transitions to a high-powered state we first apply power (via&n;&t; * power resources) then evalute _PSx.  Conversly for transitions to&n;&t; * a lower-powered state.&n;&t; */
r_if
c_cond
(paren
id|state
OL
id|device-&gt;power.state
)paren
(brace
r_if
c_cond
(paren
id|device-&gt;power.flags.power_resources
)paren
(brace
id|result
op_assign
id|acpi_power_transition
c_func
(paren
id|device
comma
id|state
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
r_goto
id|end
suffix:semicolon
)brace
r_if
c_cond
(paren
id|device-&gt;power.states
(braket
id|state
)braket
dot
id|flags.explicit_set
)paren
(brace
id|status
op_assign
id|acpi_evaluate_object
c_func
(paren
id|device-&gt;handle
comma
id|object_name
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_FAILURE
c_func
(paren
id|status
)paren
)paren
(brace
id|result
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|end
suffix:semicolon
)brace
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
id|device-&gt;power.states
(braket
id|state
)braket
dot
id|flags.explicit_set
)paren
(brace
id|status
op_assign
id|acpi_evaluate_object
c_func
(paren
id|device-&gt;handle
comma
id|object_name
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_FAILURE
c_func
(paren
id|status
)paren
)paren
(brace
id|result
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|end
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|device-&gt;power.flags.power_resources
)paren
(brace
id|result
op_assign
id|acpi_power_transition
c_func
(paren
id|device
comma
id|state
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
r_goto
id|end
suffix:semicolon
)brace
)brace
id|end
suffix:colon
r_if
c_cond
(paren
id|result
)paren
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_WARN
comma
l_string|&quot;Error transitioning device [%s] to D%d&bslash;n&quot;
comma
id|device-&gt;pnp.bus_id
comma
id|state
)paren
)paren
suffix:semicolon
r_else
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;Device [%s] transitioned to D%d&bslash;n&quot;
comma
id|device-&gt;pnp.bus_id
comma
id|state
)paren
)paren
suffix:semicolon
id|return_VALUE
c_func
(paren
id|result
)paren
suffix:semicolon
)brace
DECL|variable|acpi_bus_set_power
id|EXPORT_SYMBOL
c_func
(paren
id|acpi_bus_set_power
)paren
suffix:semicolon
multiline_comment|/* --------------------------------------------------------------------------&n;                                Event Management&n;   -------------------------------------------------------------------------- */
r_static
id|DEFINE_SPINLOCK
c_func
(paren
id|acpi_bus_event_lock
)paren
suffix:semicolon
DECL|variable|acpi_bus_event_list
id|LIST_HEAD
c_func
(paren
id|acpi_bus_event_list
)paren
suffix:semicolon
DECL|variable|acpi_bus_event_queue
id|DECLARE_WAIT_QUEUE_HEAD
c_func
(paren
id|acpi_bus_event_queue
)paren
suffix:semicolon
r_extern
r_int
id|event_is_open
suffix:semicolon
r_int
DECL|function|acpi_bus_generate_event
id|acpi_bus_generate_event
(paren
r_struct
id|acpi_device
op_star
id|device
comma
id|u8
id|type
comma
r_int
id|data
)paren
(brace
r_struct
id|acpi_bus_event
op_star
id|event
op_assign
l_int|NULL
suffix:semicolon
r_int
r_int
id|flags
op_assign
l_int|0
suffix:semicolon
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_bus_generate_event&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|device
)paren
id|return_VALUE
c_func
(paren
op_minus
id|EINVAL
)paren
suffix:semicolon
multiline_comment|/* drop event on the floor if no one&squot;s listening */
r_if
c_cond
(paren
op_logical_neg
id|event_is_open
)paren
id|return_VALUE
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|event
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|acpi_bus_event
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|event
)paren
id|return_VALUE
c_func
(paren
op_minus
id|ENOMEM
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|event-&gt;device_class
comma
id|device-&gt;pnp.device_class
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|event-&gt;bus_id
comma
id|device-&gt;pnp.bus_id
)paren
suffix:semicolon
id|event-&gt;type
op_assign
id|type
suffix:semicolon
id|event-&gt;data
op_assign
id|data
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|acpi_bus_event_lock
comma
id|flags
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|event-&gt;node
comma
op_amp
id|acpi_bus_event_list
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|acpi_bus_event_lock
comma
id|flags
)paren
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|acpi_bus_event_queue
)paren
suffix:semicolon
id|return_VALUE
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
DECL|variable|acpi_bus_generate_event
id|EXPORT_SYMBOL
c_func
(paren
id|acpi_bus_generate_event
)paren
suffix:semicolon
r_int
DECL|function|acpi_bus_receive_event
id|acpi_bus_receive_event
(paren
r_struct
id|acpi_bus_event
op_star
id|event
)paren
(brace
r_int
r_int
id|flags
op_assign
l_int|0
suffix:semicolon
r_struct
id|acpi_bus_event
op_star
id|entry
op_assign
l_int|NULL
suffix:semicolon
id|DECLARE_WAITQUEUE
c_func
(paren
id|wait
comma
id|current
)paren
suffix:semicolon
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_bus_receive_event&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|event
)paren
id|return_VALUE
c_func
(paren
op_minus
id|EINVAL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|list_empty
c_func
(paren
op_amp
id|acpi_bus_event_list
)paren
)paren
(brace
id|set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
id|add_wait_queue
c_func
(paren
op_amp
id|acpi_bus_event_queue
comma
op_amp
id|wait
)paren
suffix:semicolon
r_if
c_cond
(paren
id|list_empty
c_func
(paren
op_amp
id|acpi_bus_event_list
)paren
)paren
id|schedule
c_func
(paren
)paren
suffix:semicolon
id|remove_wait_queue
c_func
(paren
op_amp
id|acpi_bus_event_queue
comma
op_amp
id|wait
)paren
suffix:semicolon
id|set_current_state
c_func
(paren
id|TASK_RUNNING
)paren
suffix:semicolon
r_if
c_cond
(paren
id|signal_pending
c_func
(paren
id|current
)paren
)paren
id|return_VALUE
c_func
(paren
op_minus
id|ERESTARTSYS
)paren
suffix:semicolon
)brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|acpi_bus_event_lock
comma
id|flags
)paren
suffix:semicolon
id|entry
op_assign
id|list_entry
c_func
(paren
id|acpi_bus_event_list.next
comma
r_struct
id|acpi_bus_event
comma
id|node
)paren
suffix:semicolon
r_if
c_cond
(paren
id|entry
)paren
id|list_del
c_func
(paren
op_amp
id|entry-&gt;node
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|acpi_bus_event_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|entry
)paren
id|return_VALUE
c_func
(paren
op_minus
id|ENODEV
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|event
comma
id|entry
comma
r_sizeof
(paren
r_struct
id|acpi_bus_event
)paren
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|entry
)paren
suffix:semicolon
id|return_VALUE
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
DECL|variable|acpi_bus_receive_event
id|EXPORT_SYMBOL
c_func
(paren
id|acpi_bus_receive_event
)paren
suffix:semicolon
multiline_comment|/* --------------------------------------------------------------------------&n;                             Notification Handling&n;   -------------------------------------------------------------------------- */
r_static
r_int
DECL|function|acpi_bus_check_device
id|acpi_bus_check_device
(paren
r_struct
id|acpi_device
op_star
id|device
comma
r_int
op_star
id|status_changed
)paren
(brace
id|acpi_status
id|status
op_assign
l_int|0
suffix:semicolon
r_struct
id|acpi_device_status
id|old_status
suffix:semicolon
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_bus_check_device&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|device
)paren
id|return_VALUE
c_func
(paren
op_minus
id|EINVAL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status_changed
)paren
op_star
id|status_changed
op_assign
l_int|0
suffix:semicolon
id|old_status
op_assign
id|device-&gt;status
suffix:semicolon
multiline_comment|/*&n;&t; * Make sure this device&squot;s parent is present before we go about&n;&t; * messing with the device.&n;&t; */
r_if
c_cond
(paren
id|device-&gt;parent
op_logical_and
op_logical_neg
id|device-&gt;parent-&gt;status.present
)paren
(brace
id|device-&gt;status
op_assign
id|device-&gt;parent-&gt;status
suffix:semicolon
r_if
c_cond
(paren
id|STRUCT_TO_INT
c_func
(paren
id|old_status
)paren
op_ne
id|STRUCT_TO_INT
c_func
(paren
id|device-&gt;status
)paren
)paren
(brace
r_if
c_cond
(paren
id|status_changed
)paren
op_star
id|status_changed
op_assign
l_int|1
suffix:semicolon
)brace
id|return_VALUE
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
id|status
op_assign
id|acpi_bus_get_status
c_func
(paren
id|device
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_FAILURE
c_func
(paren
id|status
)paren
)paren
id|return_VALUE
c_func
(paren
op_minus
id|ENODEV
)paren
suffix:semicolon
r_if
c_cond
(paren
id|STRUCT_TO_INT
c_func
(paren
id|old_status
)paren
op_eq
id|STRUCT_TO_INT
c_func
(paren
id|device-&gt;status
)paren
)paren
id|return_VALUE
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status_changed
)paren
op_star
id|status_changed
op_assign
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * Device Insertion/Removal&n;&t; */
r_if
c_cond
(paren
(paren
id|device-&gt;status.present
)paren
op_logical_and
op_logical_neg
(paren
id|old_status.present
)paren
)paren
(brace
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;Device insertion detected&bslash;n&quot;
)paren
)paren
suffix:semicolon
multiline_comment|/* TBD: Handle device insertion */
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
(paren
id|device-&gt;status.present
)paren
op_logical_and
(paren
id|old_status.present
)paren
)paren
(brace
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;Device removal detected&bslash;n&quot;
)paren
)paren
suffix:semicolon
multiline_comment|/* TBD: Handle device removal */
)brace
id|return_VALUE
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|acpi_bus_check_scope
id|acpi_bus_check_scope
(paren
r_struct
id|acpi_device
op_star
id|device
)paren
(brace
r_int
id|result
op_assign
l_int|0
suffix:semicolon
r_int
id|status_changed
op_assign
l_int|0
suffix:semicolon
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_bus_check_scope&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|device
)paren
id|return_VALUE
c_func
(paren
op_minus
id|EINVAL
)paren
suffix:semicolon
multiline_comment|/* Status Change? */
id|result
op_assign
id|acpi_bus_check_device
c_func
(paren
id|device
comma
op_amp
id|status_changed
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
id|return_VALUE
c_func
(paren
id|result
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|status_changed
)paren
id|return_VALUE
c_func
(paren
l_int|0
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * TBD: Enumerate child devices within this device&squot;s scope and&n;&t; *       run acpi_bus_check_device()&squot;s on them.&n;&t; */
id|return_VALUE
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * acpi_bus_notify&n; * ---------------&n; * Callback for all &squot;system-level&squot; device notifications (values 0x00-0x7F).&n; */
r_static
r_void
DECL|function|acpi_bus_notify
id|acpi_bus_notify
(paren
id|acpi_handle
id|handle
comma
id|u32
id|type
comma
r_void
op_star
id|data
)paren
(brace
r_int
id|result
op_assign
l_int|0
suffix:semicolon
r_struct
id|acpi_device
op_star
id|device
op_assign
l_int|NULL
suffix:semicolon
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_bus_notify&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|acpi_bus_get_device
c_func
(paren
id|handle
comma
op_amp
id|device
)paren
)paren
id|return_VOID
suffix:semicolon
r_switch
c_cond
(paren
id|type
)paren
(brace
r_case
id|ACPI_NOTIFY_BUS_CHECK
suffix:colon
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;Received BUS CHECK notification for device [%s]&bslash;n&quot;
comma
id|device-&gt;pnp.bus_id
)paren
)paren
suffix:semicolon
id|result
op_assign
id|acpi_bus_check_scope
c_func
(paren
id|device
)paren
suffix:semicolon
multiline_comment|/* &n;&t;&t; * TBD: We&squot;ll need to outsource certain events to non-ACPI&n;&t;&t; *&t;drivers via the device manager (device.c).&n;&t;&t; */
r_break
suffix:semicolon
r_case
id|ACPI_NOTIFY_DEVICE_CHECK
suffix:colon
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;Received DEVICE CHECK notification for device [%s]&bslash;n&quot;
comma
id|device-&gt;pnp.bus_id
)paren
)paren
suffix:semicolon
id|result
op_assign
id|acpi_bus_check_device
c_func
(paren
id|device
comma
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/* &n;&t;&t; * TBD: We&squot;ll need to outsource certain events to non-ACPI&n;&t;&t; *&t;drivers via the device manager (device.c).&n;&t;&t; */
r_break
suffix:semicolon
r_case
id|ACPI_NOTIFY_DEVICE_WAKE
suffix:colon
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;Received DEVICE WAKE notification for device [%s]&bslash;n&quot;
comma
id|device-&gt;pnp.bus_id
)paren
)paren
suffix:semicolon
multiline_comment|/* TBD */
r_break
suffix:semicolon
r_case
id|ACPI_NOTIFY_EJECT_REQUEST
suffix:colon
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;Received EJECT REQUEST notification for device [%s]&bslash;n&quot;
comma
id|device-&gt;pnp.bus_id
)paren
)paren
suffix:semicolon
multiline_comment|/* TBD */
r_break
suffix:semicolon
r_case
id|ACPI_NOTIFY_DEVICE_CHECK_LIGHT
suffix:colon
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;Received DEVICE CHECK LIGHT notification for device [%s]&bslash;n&quot;
comma
id|device-&gt;pnp.bus_id
)paren
)paren
suffix:semicolon
multiline_comment|/* TBD: Exactly what does &squot;light&squot; mean? */
r_break
suffix:semicolon
r_case
id|ACPI_NOTIFY_FREQUENCY_MISMATCH
suffix:colon
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;Received FREQUENCY MISMATCH notification for device [%s]&bslash;n&quot;
comma
id|device-&gt;pnp.bus_id
)paren
)paren
suffix:semicolon
multiline_comment|/* TBD */
r_break
suffix:semicolon
r_case
id|ACPI_NOTIFY_BUS_MODE_MISMATCH
suffix:colon
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;Received BUS MODE MISMATCH notification for device [%s]&bslash;n&quot;
comma
id|device-&gt;pnp.bus_id
)paren
)paren
suffix:semicolon
multiline_comment|/* TBD */
r_break
suffix:semicolon
r_case
id|ACPI_NOTIFY_POWER_FAULT
suffix:colon
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;Received POWER FAULT notification for device [%s]&bslash;n&quot;
comma
id|device-&gt;pnp.bus_id
)paren
)paren
suffix:semicolon
multiline_comment|/* TBD */
r_break
suffix:semicolon
r_default
suffix:colon
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;Received unknown/unsupported notification [%08x]&bslash;n&quot;
comma
id|type
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|return_VOID
suffix:semicolon
)brace
multiline_comment|/* --------------------------------------------------------------------------&n;                             Initialization/Cleanup&n;   -------------------------------------------------------------------------- */
r_static
r_int
id|__init
DECL|function|acpi_bus_init_irq
id|acpi_bus_init_irq
(paren
r_void
)paren
(brace
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
r_union
id|acpi_object
id|arg
op_assign
(brace
id|ACPI_TYPE_INTEGER
)brace
suffix:semicolon
r_struct
id|acpi_object_list
id|arg_list
op_assign
(brace
l_int|1
comma
op_amp
id|arg
)brace
suffix:semicolon
r_char
op_star
id|message
op_assign
l_int|NULL
suffix:semicolon
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_bus_init_irq&quot;
)paren
suffix:semicolon
multiline_comment|/* &n;&t; * Let the system know what interrupt model we are using by&n;&t; * evaluating the &bslash;_PIC object, if exists.&n;&t; */
r_switch
c_cond
(paren
id|acpi_irq_model
)paren
(brace
r_case
id|ACPI_IRQ_MODEL_PIC
suffix:colon
id|message
op_assign
l_string|&quot;PIC&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_IRQ_MODEL_IOAPIC
suffix:colon
id|message
op_assign
l_string|&quot;IOAPIC&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_IRQ_MODEL_IOSAPIC
suffix:colon
id|message
op_assign
l_string|&quot;IOSAPIC&quot;
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_WARNING
id|PREFIX
l_string|&quot;Unknown interrupt routing model&bslash;n&quot;
)paren
suffix:semicolon
id|return_VALUE
c_func
(paren
op_minus
id|ENODEV
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
id|PREFIX
l_string|&quot;Using %s for interrupt routing&bslash;n&quot;
comma
id|message
)paren
suffix:semicolon
id|arg.integer.value
op_assign
id|acpi_irq_model
suffix:semicolon
id|status
op_assign
id|acpi_evaluate_object
c_func
(paren
l_int|NULL
comma
l_string|&quot;&bslash;&bslash;_PIC&quot;
comma
op_amp
id|arg_list
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_FAILURE
c_func
(paren
id|status
)paren
op_logical_and
(paren
id|status
op_ne
id|AE_NOT_FOUND
)paren
)paren
(brace
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Error evaluating _PIC&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|return_VALUE
c_func
(paren
op_minus
id|ENODEV
)paren
suffix:semicolon
)brace
id|return_VALUE
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_void
id|__init
DECL|function|acpi_early_init
id|acpi_early_init
(paren
r_void
)paren
(brace
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
r_struct
id|acpi_buffer
id|buffer
op_assign
(brace
r_sizeof
(paren
id|acpi_fadt
)paren
comma
op_amp
id|acpi_fadt
)brace
suffix:semicolon
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_early_init&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|acpi_disabled
)paren
id|return_VOID
suffix:semicolon
multiline_comment|/* enable workarounds, unless strict ACPI spec. compliance */
r_if
c_cond
(paren
op_logical_neg
id|acpi_strict
)paren
id|acpi_gbl_enable_interpreter_slack
op_assign
id|TRUE
suffix:semicolon
id|status
op_assign
id|acpi_initialize_subsystem
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_FAILURE
c_func
(paren
id|status
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|PREFIX
l_string|&quot;Unable to initialize the ACPI Interpreter&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|error0
suffix:semicolon
)brace
id|status
op_assign
id|acpi_load_tables
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_FAILURE
c_func
(paren
id|status
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|PREFIX
l_string|&quot;Unable to load the System Description Tables&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|error0
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Get a separate copy of the FADT for use by other drivers.&n;&t; */
id|status
op_assign
id|acpi_get_table
c_func
(paren
id|ACPI_TABLE_FADT
comma
l_int|1
comma
op_amp
id|buffer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_FAILURE
c_func
(paren
id|status
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|PREFIX
l_string|&quot;Unable to get the FADT&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|error0
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_X86
r_if
c_cond
(paren
op_logical_neg
id|acpi_ioapic
)paren
(brace
r_extern
id|acpi_interrupt_flags
id|acpi_sci_flags
suffix:semicolon
multiline_comment|/* compatible (0) means level (3) */
r_if
c_cond
(paren
id|acpi_sci_flags.trigger
op_eq
l_int|0
)paren
id|acpi_sci_flags.trigger
op_assign
l_int|3
suffix:semicolon
multiline_comment|/* Set PIC-mode SCI trigger type */
id|acpi_pic_sci_set_trigger
c_func
(paren
id|acpi_fadt.sci_int
comma
id|acpi_sci_flags.trigger
)paren
suffix:semicolon
)brace
r_else
(brace
r_extern
r_int
id|acpi_sci_override_gsi
suffix:semicolon
multiline_comment|/*&n;&t;&t; * now that acpi_fadt is initialized,&n;&t;&t; * update it with result from INT_SRC_OVR parsing&n;&t;&t; */
id|acpi_fadt.sci_int
op_assign
id|acpi_sci_override_gsi
suffix:semicolon
)brace
macro_line|#endif
id|status
op_assign
id|acpi_enable_subsystem
c_func
(paren
op_complement
(paren
id|ACPI_NO_HARDWARE_INIT
op_or
id|ACPI_NO_ACPI_ENABLE
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_FAILURE
c_func
(paren
id|status
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|PREFIX
l_string|&quot;Unable to enable ACPI&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|error0
suffix:semicolon
)brace
id|return_VOID
suffix:semicolon
id|error0
suffix:colon
id|disable_acpi
c_func
(paren
)paren
suffix:semicolon
id|return_VOID
suffix:semicolon
)brace
r_static
r_int
id|__init
DECL|function|acpi_bus_init
id|acpi_bus_init
(paren
r_void
)paren
(brace
r_int
id|result
op_assign
l_int|0
suffix:semicolon
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
r_extern
id|acpi_status
id|acpi_os_initialize1
c_func
(paren
r_void
)paren
suffix:semicolon
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_bus_init&quot;
)paren
suffix:semicolon
id|status
op_assign
id|acpi_os_initialize1
c_func
(paren
)paren
suffix:semicolon
id|status
op_assign
id|acpi_enable_subsystem
c_func
(paren
id|ACPI_NO_HARDWARE_INIT
op_or
id|ACPI_NO_ACPI_ENABLE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_FAILURE
c_func
(paren
id|status
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|PREFIX
l_string|&quot;Unable to start the ACPI Interpreter&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|error1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ACPI_FAILURE
c_func
(paren
id|status
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|PREFIX
l_string|&quot;Unable to initialize ACPI OS objects&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|error1
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_ACPI_EC
multiline_comment|/*&n;&t; * ACPI 2.0 requires the EC driver to be loaded and work before&n;&t; * the EC device is found in the namespace (i.e. before acpi_initialize_objects()&n;&t; * is called).&n;&t; *&n;&t; * This is accomplished by looking for the ECDT table, and getting &n;&t; * the EC parameters out of that.&n;&t; */
id|status
op_assign
id|acpi_ec_ecdt_probe
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Ignore result. Not having an ECDT is not fatal. */
macro_line|#endif
id|status
op_assign
id|acpi_initialize_objects
c_func
(paren
id|ACPI_FULL_INITIALIZATION
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_FAILURE
c_func
(paren
id|status
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|PREFIX
l_string|&quot;Unable to initialize ACPI objects&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|error1
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
id|PREFIX
l_string|&quot;Interpreter enabled&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Get the system interrupt model and evaluate &bslash;_PIC.&n;&t; */
id|result
op_assign
id|acpi_bus_init_irq
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
r_goto
id|error1
suffix:semicolon
multiline_comment|/*&n;&t; * Register the for all standard device notifications.&n;&t; */
id|status
op_assign
id|acpi_install_notify_handler
c_func
(paren
id|ACPI_ROOT_OBJECT
comma
id|ACPI_SYSTEM_NOTIFY
comma
op_amp
id|acpi_bus_notify
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_FAILURE
c_func
(paren
id|status
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|PREFIX
l_string|&quot;Unable to register for device notifications&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|error1
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Create the top ACPI proc directory&n;&t; */
id|acpi_root_dir
op_assign
id|proc_mkdir
c_func
(paren
id|ACPI_BUS_FILE_ROOT
comma
l_int|NULL
)paren
suffix:semicolon
id|return_VALUE
c_func
(paren
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Mimic structured exception handling */
id|error1
suffix:colon
id|acpi_terminate
c_func
(paren
)paren
suffix:semicolon
id|return_VALUE
c_func
(paren
op_minus
id|ENODEV
)paren
suffix:semicolon
)brace
id|decl_subsys
c_func
(paren
id|acpi
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
DECL|function|acpi_init
r_static
r_int
id|__init
id|acpi_init
(paren
r_void
)paren
(brace
r_int
id|result
op_assign
l_int|0
suffix:semicolon
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_init&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
id|PREFIX
l_string|&quot;Subsystem revision %08x&bslash;n&quot;
comma
id|ACPI_CA_VERSION
)paren
suffix:semicolon
r_if
c_cond
(paren
id|acpi_disabled
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
id|PREFIX
l_string|&quot;Interpreter disabled.&bslash;n&quot;
)paren
suffix:semicolon
id|return_VALUE
c_func
(paren
op_minus
id|ENODEV
)paren
suffix:semicolon
)brace
id|firmware_register
c_func
(paren
op_amp
id|acpi_subsys
)paren
suffix:semicolon
id|result
op_assign
id|acpi_bus_init
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|result
)paren
(brace
macro_line|#ifdef CONFIG_PM
r_if
c_cond
(paren
op_logical_neg
id|PM_IS_ACTIVE
c_func
(paren
)paren
)paren
id|pm_active
op_assign
l_int|1
suffix:semicolon
r_else
(brace
id|printk
c_func
(paren
id|KERN_INFO
id|PREFIX
l_string|&quot;APM is already active, exiting&bslash;n&quot;
)paren
suffix:semicolon
id|disable_acpi
c_func
(paren
)paren
suffix:semicolon
id|result
op_assign
op_minus
id|ENODEV
suffix:semicolon
)brace
macro_line|#endif
)brace
r_else
id|disable_acpi
c_func
(paren
)paren
suffix:semicolon
id|return_VALUE
c_func
(paren
id|result
)paren
suffix:semicolon
)brace
DECL|variable|acpi_init
id|subsys_initcall
c_func
(paren
id|acpi_init
)paren
suffix:semicolon
eof
