multiline_comment|/*&n; *  The Serio abstraction module&n; *&n; *  Copyright (c) 1999-2004 Vojtech Pavlik&n; *  Copyright (c) 2004 Dmitry Torokhov&n; *  Copyright (c) 2003 Daniele Bellucci&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; *&n; * Should you need to contact me, the author, you can do so either by&n; * e-mail - mail your message to &lt;vojtech@ucw.cz&gt;, or by paper mail:&n; * Vojtech Pavlik, Simunkova 1594, Prague 8, 182 00 Czech Republic&n; */
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/serio.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;linux/completion.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/suspend.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Vojtech Pavlik &lt;vojtech@ucw.cz&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Serio abstraction core&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|serio_interrupt
id|EXPORT_SYMBOL
c_func
(paren
id|serio_interrupt
)paren
suffix:semicolon
DECL|variable|serio_register_port
id|EXPORT_SYMBOL
c_func
(paren
id|serio_register_port
)paren
suffix:semicolon
DECL|variable|serio_register_port_delayed
id|EXPORT_SYMBOL
c_func
(paren
id|serio_register_port_delayed
)paren
suffix:semicolon
DECL|variable|serio_unregister_port
id|EXPORT_SYMBOL
c_func
(paren
id|serio_unregister_port
)paren
suffix:semicolon
DECL|variable|serio_unregister_port_delayed
id|EXPORT_SYMBOL
c_func
(paren
id|serio_unregister_port_delayed
)paren
suffix:semicolon
DECL|variable|serio_register_driver
id|EXPORT_SYMBOL
c_func
(paren
id|serio_register_driver
)paren
suffix:semicolon
DECL|variable|serio_unregister_driver
id|EXPORT_SYMBOL
c_func
(paren
id|serio_unregister_driver
)paren
suffix:semicolon
DECL|variable|serio_open
id|EXPORT_SYMBOL
c_func
(paren
id|serio_open
)paren
suffix:semicolon
DECL|variable|serio_close
id|EXPORT_SYMBOL
c_func
(paren
id|serio_close
)paren
suffix:semicolon
DECL|variable|serio_rescan
id|EXPORT_SYMBOL
c_func
(paren
id|serio_rescan
)paren
suffix:semicolon
DECL|variable|serio_reconnect
id|EXPORT_SYMBOL
c_func
(paren
id|serio_reconnect
)paren
suffix:semicolon
r_static
id|DECLARE_MUTEX
c_func
(paren
id|serio_sem
)paren
suffix:semicolon
multiline_comment|/* protects serio_list and serio_diriver_list */
r_static
id|LIST_HEAD
c_func
(paren
id|serio_list
)paren
suffix:semicolon
r_static
id|LIST_HEAD
c_func
(paren
id|serio_driver_list
)paren
suffix:semicolon
DECL|variable|serio_no
r_static
r_int
r_int
id|serio_no
suffix:semicolon
DECL|variable|serio_bus
r_struct
id|bus_type
id|serio_bus
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;serio&quot;
comma
)brace
suffix:semicolon
r_static
r_void
id|serio_find_driver
c_func
(paren
r_struct
id|serio
op_star
id|serio
)paren
suffix:semicolon
r_static
r_void
id|serio_create_port
c_func
(paren
r_struct
id|serio
op_star
id|serio
)paren
suffix:semicolon
r_static
r_void
id|serio_destroy_port
c_func
(paren
r_struct
id|serio
op_star
id|serio
)paren
suffix:semicolon
r_static
r_void
id|serio_connect_port
c_func
(paren
r_struct
id|serio
op_star
id|serio
comma
r_struct
id|serio_driver
op_star
id|drv
)paren
suffix:semicolon
r_static
r_void
id|serio_reconnect_port
c_func
(paren
r_struct
id|serio
op_star
id|serio
)paren
suffix:semicolon
r_static
r_void
id|serio_disconnect_port
c_func
(paren
r_struct
id|serio
op_star
id|serio
)paren
suffix:semicolon
DECL|function|serio_bind_driver
r_static
r_int
id|serio_bind_driver
c_func
(paren
r_struct
id|serio
op_star
id|serio
comma
r_struct
id|serio_driver
op_star
id|drv
)paren
(brace
id|get_driver
c_func
(paren
op_amp
id|drv-&gt;driver
)paren
suffix:semicolon
id|drv
op_member_access_from_pointer
id|connect
c_func
(paren
id|serio
comma
id|drv
)paren
suffix:semicolon
r_if
c_cond
(paren
id|serio-&gt;drv
)paren
(brace
id|down_write
c_func
(paren
op_amp
id|serio_bus.subsys.rwsem
)paren
suffix:semicolon
id|serio-&gt;dev.driver
op_assign
op_amp
id|drv-&gt;driver
suffix:semicolon
id|device_bind_driver
c_func
(paren
op_amp
id|serio-&gt;dev
)paren
suffix:semicolon
id|up_write
c_func
(paren
op_amp
id|serio_bus.subsys.rwsem
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|put_driver
c_func
(paren
op_amp
id|drv-&gt;driver
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* serio_find_driver() must be called with serio_sem down.  */
DECL|function|serio_find_driver
r_static
r_void
id|serio_find_driver
c_func
(paren
r_struct
id|serio
op_star
id|serio
)paren
(brace
r_struct
id|serio_driver
op_star
id|drv
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|drv
comma
op_amp
id|serio_driver_list
comma
id|node
)paren
r_if
c_cond
(paren
id|serio_bind_driver
c_func
(paren
id|serio
comma
id|drv
)paren
)paren
r_break
suffix:semicolon
)brace
multiline_comment|/*&n; * Serio event processing.&n; */
DECL|struct|serio_event
r_struct
id|serio_event
(brace
DECL|member|type
r_int
id|type
suffix:semicolon
DECL|member|serio
r_struct
id|serio
op_star
id|serio
suffix:semicolon
DECL|member|node
r_struct
id|list_head
id|node
suffix:semicolon
)brace
suffix:semicolon
DECL|enum|serio_event_type
r_enum
id|serio_event_type
(brace
DECL|enumerator|SERIO_RESCAN
id|SERIO_RESCAN
comma
DECL|enumerator|SERIO_RECONNECT
id|SERIO_RECONNECT
comma
DECL|enumerator|SERIO_REGISTER_PORT
id|SERIO_REGISTER_PORT
comma
DECL|enumerator|SERIO_UNREGISTER_PORT
id|SERIO_UNREGISTER_PORT
comma
)brace
suffix:semicolon
DECL|variable|serio_event_lock
r_static
id|spinlock_t
id|serio_event_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
multiline_comment|/* protects serio_event_list */
r_static
id|LIST_HEAD
c_func
(paren
id|serio_event_list
)paren
suffix:semicolon
r_static
id|DECLARE_WAIT_QUEUE_HEAD
c_func
(paren
id|serio_wait
)paren
suffix:semicolon
r_static
id|DECLARE_COMPLETION
c_func
(paren
id|serio_exited
)paren
suffix:semicolon
DECL|variable|serio_pid
r_static
r_int
id|serio_pid
suffix:semicolon
DECL|function|serio_queue_event
r_static
r_void
id|serio_queue_event
c_func
(paren
r_struct
id|serio
op_star
id|serio
comma
r_int
id|event_type
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_struct
id|serio_event
op_star
id|event
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|serio_event_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|event
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|serio_event
)paren
comma
id|GFP_ATOMIC
)paren
)paren
)paren
(brace
id|event-&gt;type
op_assign
id|event_type
suffix:semicolon
id|event-&gt;serio
op_assign
id|serio
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|event-&gt;node
comma
op_amp
id|serio_event_list
)paren
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|serio_wait
)paren
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|serio_event_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|serio_get_event
r_static
r_struct
id|serio_event
op_star
id|serio_get_event
c_func
(paren
r_void
)paren
(brace
r_struct
id|serio_event
op_star
id|event
suffix:semicolon
r_struct
id|list_head
op_star
id|node
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|serio_event_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|list_empty
c_func
(paren
op_amp
id|serio_event_list
)paren
)paren
(brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|serio_event_lock
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|node
op_assign
id|serio_event_list.next
suffix:semicolon
id|event
op_assign
id|container_of
c_func
(paren
id|node
comma
r_struct
id|serio_event
comma
id|node
)paren
suffix:semicolon
id|list_del_init
c_func
(paren
id|node
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|serio_event_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|event
suffix:semicolon
)brace
DECL|function|serio_handle_events
r_static
r_void
id|serio_handle_events
c_func
(paren
r_void
)paren
(brace
r_struct
id|serio_event
op_star
id|event
suffix:semicolon
r_while
c_loop
(paren
(paren
id|event
op_assign
id|serio_get_event
c_func
(paren
)paren
)paren
)paren
(brace
id|down
c_func
(paren
op_amp
id|serio_sem
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|event-&gt;type
)paren
(brace
r_case
id|SERIO_REGISTER_PORT
suffix:colon
id|serio_create_port
c_func
(paren
id|event-&gt;serio
)paren
suffix:semicolon
id|serio_connect_port
c_func
(paren
id|event-&gt;serio
comma
l_int|NULL
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SERIO_UNREGISTER_PORT
suffix:colon
id|serio_disconnect_port
c_func
(paren
id|event-&gt;serio
)paren
suffix:semicolon
id|serio_destroy_port
c_func
(paren
id|event-&gt;serio
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SERIO_RECONNECT
suffix:colon
id|serio_reconnect_port
c_func
(paren
id|event-&gt;serio
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SERIO_RESCAN
suffix:colon
id|serio_disconnect_port
c_func
(paren
id|event-&gt;serio
)paren
suffix:semicolon
id|serio_connect_port
c_func
(paren
id|event-&gt;serio
comma
l_int|NULL
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|serio_sem
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|event
)paren
suffix:semicolon
)brace
)brace
DECL|function|serio_remove_pending_events
r_static
r_void
id|serio_remove_pending_events
c_func
(paren
r_struct
id|serio
op_star
id|serio
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
r_struct
id|serio_event
op_star
id|event
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|serio_event_lock
comma
id|flags
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
id|serio_event_list
)paren
(brace
id|event
op_assign
id|container_of
c_func
(paren
id|node
comma
r_struct
id|serio_event
comma
id|node
)paren
suffix:semicolon
r_if
c_cond
(paren
id|event-&gt;serio
op_eq
id|serio
)paren
(brace
id|list_del_init
c_func
(paren
id|node
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|event
)paren
suffix:semicolon
)brace
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|serio_event_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|serio_thread
r_static
r_int
id|serio_thread
c_func
(paren
r_void
op_star
id|nothing
)paren
(brace
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|daemonize
c_func
(paren
l_string|&quot;kseriod&quot;
)paren
suffix:semicolon
id|allow_signal
c_func
(paren
id|SIGTERM
)paren
suffix:semicolon
r_do
(brace
id|serio_handle_events
c_func
(paren
)paren
suffix:semicolon
id|wait_event_interruptible
c_func
(paren
id|serio_wait
comma
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|serio_event_list
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;flags
op_amp
id|PF_FREEZE
)paren
id|refrigerator
c_func
(paren
id|PF_FREEZE
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
op_logical_neg
id|signal_pending
c_func
(paren
id|current
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;serio: kseriod exiting&bslash;n&quot;
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
id|complete_and_exit
c_func
(paren
op_amp
id|serio_exited
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Serio port operations&n; */
DECL|function|serio_show_description
r_static
id|ssize_t
id|serio_show_description
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_char
op_star
id|buf
)paren
(brace
r_struct
id|serio
op_star
id|serio
op_assign
id|to_serio_port
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%s&bslash;n&quot;
comma
id|serio-&gt;name
)paren
suffix:semicolon
)brace
r_static
id|DEVICE_ATTR
c_func
(paren
id|description
comma
id|S_IRUGO
comma
id|serio_show_description
comma
l_int|NULL
)paren
suffix:semicolon
DECL|function|serio_show_driver
r_static
id|ssize_t
id|serio_show_driver
c_func
(paren
r_struct
id|device
op_star
id|dev
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
id|dev-&gt;driver
ques
c_cond
id|dev-&gt;driver-&gt;name
suffix:colon
l_string|&quot;(none)&quot;
)paren
suffix:semicolon
)brace
DECL|function|serio_rebind_driver
r_static
id|ssize_t
id|serio_rebind_driver
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|count
)paren
(brace
r_struct
id|serio
op_star
id|serio
op_assign
id|to_serio_port
c_func
(paren
id|dev
)paren
suffix:semicolon
r_struct
id|device_driver
op_star
id|drv
suffix:semicolon
r_struct
id|kobject
op_star
id|k
suffix:semicolon
r_int
id|retval
suffix:semicolon
id|retval
op_assign
id|down_interruptible
c_func
(paren
op_amp
id|serio_sem
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_return
id|retval
suffix:semicolon
id|retval
op_assign
id|count
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|buf
comma
l_string|&quot;none&quot;
comma
id|count
)paren
)paren
(brace
id|serio_disconnect_port
c_func
(paren
id|serio
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|buf
comma
l_string|&quot;reconnect&quot;
comma
id|count
)paren
)paren
(brace
id|serio_reconnect_port
c_func
(paren
id|serio
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|buf
comma
l_string|&quot;rescan&quot;
comma
id|count
)paren
)paren
(brace
id|serio_disconnect_port
c_func
(paren
id|serio
)paren
suffix:semicolon
id|serio_connect_port
c_func
(paren
id|serio
comma
l_int|NULL
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|k
op_assign
id|kset_find_obj
c_func
(paren
op_amp
id|serio_bus.drivers
comma
id|buf
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
id|drv
op_assign
id|container_of
c_func
(paren
id|k
comma
r_struct
id|device_driver
comma
id|kobj
)paren
suffix:semicolon
id|serio_disconnect_port
c_func
(paren
id|serio
)paren
suffix:semicolon
id|serio_connect_port
c_func
(paren
id|serio
comma
id|to_serio_driver
c_func
(paren
id|drv
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|retval
op_assign
op_minus
id|EINVAL
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|serio_sem
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
r_static
id|DEVICE_ATTR
c_func
(paren
id|driver
comma
id|S_IWUSR
op_or
id|S_IRUGO
comma
id|serio_show_driver
comma
id|serio_rebind_driver
)paren
suffix:semicolon
DECL|function|serio_release_port
r_static
r_void
id|serio_release_port
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|serio
op_star
id|serio
op_assign
id|to_serio_port
c_func
(paren
id|dev
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|serio
)paren
suffix:semicolon
id|module_put
c_func
(paren
id|THIS_MODULE
)paren
suffix:semicolon
)brace
DECL|function|serio_create_port
r_static
r_void
id|serio_create_port
c_func
(paren
r_struct
id|serio
op_star
id|serio
)paren
(brace
id|try_module_get
c_func
(paren
id|THIS_MODULE
)paren
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|serio-&gt;lock
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|serio-&gt;node
comma
op_amp
id|serio_list
)paren
suffix:semicolon
id|snprintf
c_func
(paren
id|serio-&gt;dev.bus_id
comma
r_sizeof
(paren
id|serio-&gt;dev.bus_id
)paren
comma
l_string|&quot;serio%d&quot;
comma
id|serio_no
op_increment
)paren
suffix:semicolon
id|serio-&gt;dev.bus
op_assign
op_amp
id|serio_bus
suffix:semicolon
id|serio-&gt;dev.release
op_assign
id|serio_release_port
suffix:semicolon
r_if
c_cond
(paren
id|serio-&gt;parent
)paren
id|serio-&gt;dev.parent
op_assign
op_amp
id|serio-&gt;parent-&gt;dev
suffix:semicolon
id|device_register
c_func
(paren
op_amp
id|serio-&gt;dev
)paren
suffix:semicolon
id|device_create_file
c_func
(paren
op_amp
id|serio-&gt;dev
comma
op_amp
id|dev_attr_description
)paren
suffix:semicolon
id|device_create_file
c_func
(paren
op_amp
id|serio-&gt;dev
comma
op_amp
id|dev_attr_driver
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * serio_destroy_port() completes deregistration process and removes&n; * port from the system&n; */
DECL|function|serio_destroy_port
r_static
r_void
id|serio_destroy_port
c_func
(paren
r_struct
id|serio
op_star
id|serio
)paren
(brace
r_struct
id|serio_driver
op_star
id|drv
op_assign
id|serio-&gt;drv
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|serio_remove_pending_events
c_func
(paren
id|serio
)paren
suffix:semicolon
id|list_del_init
c_func
(paren
op_amp
id|serio-&gt;node
)paren
suffix:semicolon
r_if
c_cond
(paren
id|drv
)paren
(brace
id|drv
op_member_access_from_pointer
id|disconnect
c_func
(paren
id|serio
)paren
suffix:semicolon
id|down_write
c_func
(paren
op_amp
id|serio_bus.subsys.rwsem
)paren
suffix:semicolon
id|device_release_driver
c_func
(paren
op_amp
id|serio-&gt;dev
)paren
suffix:semicolon
id|up_write
c_func
(paren
op_amp
id|serio_bus.subsys.rwsem
)paren
suffix:semicolon
id|put_driver
c_func
(paren
op_amp
id|drv-&gt;driver
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|serio-&gt;parent
)paren
(brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|serio-&gt;parent-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|serio-&gt;parent-&gt;child
op_assign
l_int|NULL
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|serio-&gt;parent-&gt;lock
comma
id|flags
)paren
suffix:semicolon
)brace
id|device_unregister
c_func
(paren
op_amp
id|serio-&gt;dev
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * serio_connect_port() tries to bind the port and possible all its&n; * children to appropriate drivers. If driver passed in the function will not&n; * try otehr drivers when binding parent port.&n; */
DECL|function|serio_connect_port
r_static
r_void
id|serio_connect_port
c_func
(paren
r_struct
id|serio
op_star
id|serio
comma
r_struct
id|serio_driver
op_star
id|drv
)paren
(brace
id|WARN_ON
c_func
(paren
id|serio-&gt;drv
)paren
suffix:semicolon
id|WARN_ON
c_func
(paren
id|serio-&gt;child
)paren
suffix:semicolon
r_if
c_cond
(paren
id|drv
)paren
id|serio_bind_driver
c_func
(paren
id|serio
comma
id|drv
)paren
suffix:semicolon
r_else
id|serio_find_driver
c_func
(paren
id|serio
)paren
suffix:semicolon
multiline_comment|/* Ok, now bind children, if any */
r_while
c_loop
(paren
id|serio-&gt;child
)paren
(brace
id|serio
op_assign
id|serio-&gt;child
suffix:semicolon
id|WARN_ON
c_func
(paren
id|serio-&gt;drv
)paren
suffix:semicolon
id|WARN_ON
c_func
(paren
id|serio-&gt;child
)paren
suffix:semicolon
id|serio_create_port
c_func
(paren
id|serio
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * With children we just _prefer_ passed in driver,&n;&t;&t; * but we will try other options in case preferred&n;&t;&t; * is not the one&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|drv
op_logical_or
op_logical_neg
id|serio_bind_driver
c_func
(paren
id|serio
comma
id|drv
)paren
)paren
id|serio_find_driver
c_func
(paren
id|serio
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; *&n; */
DECL|function|serio_reconnect_port
r_static
r_void
id|serio_reconnect_port
c_func
(paren
r_struct
id|serio
op_star
id|serio
)paren
(brace
r_do
(brace
r_if
c_cond
(paren
op_logical_neg
id|serio-&gt;drv
op_logical_or
op_logical_neg
id|serio-&gt;drv-&gt;reconnect
op_logical_or
id|serio-&gt;drv
op_member_access_from_pointer
id|reconnect
c_func
(paren
id|serio
)paren
)paren
(brace
id|serio_disconnect_port
c_func
(paren
id|serio
)paren
suffix:semicolon
id|serio_connect_port
c_func
(paren
id|serio
comma
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/* Ok, old children are now gone, we are done */
r_break
suffix:semicolon
)brace
id|serio
op_assign
id|serio-&gt;child
suffix:semicolon
)brace
r_while
c_loop
(paren
id|serio
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * serio_disconnect_port() unbinds a port from its driver. As a side effect&n; * all child ports are unbound and destroyed.&n; */
DECL|function|serio_disconnect_port
r_static
r_void
id|serio_disconnect_port
c_func
(paren
r_struct
id|serio
op_star
id|serio
)paren
(brace
r_struct
id|serio_driver
op_star
id|drv
op_assign
id|serio-&gt;drv
suffix:semicolon
r_struct
id|serio
op_star
id|s
suffix:semicolon
r_if
c_cond
(paren
id|serio-&gt;child
)paren
(brace
multiline_comment|/*&n;&t;&t; * Children ports should be disconnected and destroyed&n;&t;&t; * first, staring with the leaf one, since we don&squot;t want&n;&t;&t; * to do recursion&n;&t;&t; */
r_do
(brace
id|s
op_assign
id|serio-&gt;child
suffix:semicolon
)brace
r_while
c_loop
(paren
id|s-&gt;child
)paren
suffix:semicolon
r_while
c_loop
(paren
id|s
op_ne
id|serio
)paren
(brace
id|s
op_assign
id|s-&gt;parent
suffix:semicolon
id|serio_destroy_port
c_func
(paren
id|s-&gt;child
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; * Ok, no children left, now disconnect this port&n;&t; */
r_if
c_cond
(paren
id|drv
)paren
(brace
id|drv
op_member_access_from_pointer
id|disconnect
c_func
(paren
id|serio
)paren
suffix:semicolon
id|down_write
c_func
(paren
op_amp
id|serio_bus.subsys.rwsem
)paren
suffix:semicolon
id|device_release_driver
c_func
(paren
op_amp
id|serio-&gt;dev
)paren
suffix:semicolon
id|up_write
c_func
(paren
op_amp
id|serio_bus.subsys.rwsem
)paren
suffix:semicolon
id|put_driver
c_func
(paren
op_amp
id|drv-&gt;driver
)paren
suffix:semicolon
)brace
)brace
DECL|function|serio_rescan
r_void
id|serio_rescan
c_func
(paren
r_struct
id|serio
op_star
id|serio
)paren
(brace
id|serio_queue_event
c_func
(paren
id|serio
comma
id|SERIO_RESCAN
)paren
suffix:semicolon
)brace
DECL|function|serio_reconnect
r_void
id|serio_reconnect
c_func
(paren
r_struct
id|serio
op_star
id|serio
)paren
(brace
id|serio_queue_event
c_func
(paren
id|serio
comma
id|SERIO_RECONNECT
)paren
suffix:semicolon
)brace
DECL|function|serio_register_port
r_void
id|serio_register_port
c_func
(paren
r_struct
id|serio
op_star
id|serio
)paren
(brace
id|down
c_func
(paren
op_amp
id|serio_sem
)paren
suffix:semicolon
id|serio_create_port
c_func
(paren
id|serio
)paren
suffix:semicolon
id|serio_connect_port
c_func
(paren
id|serio
comma
l_int|NULL
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|serio_sem
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Submits register request to kseriod for subsequent execution.&n; * Can be used when it is not obvious whether the serio_sem is&n; * taken or not and when delayed execution is feasible.&n; */
DECL|function|serio_register_port_delayed
r_void
id|serio_register_port_delayed
c_func
(paren
r_struct
id|serio
op_star
id|serio
)paren
(brace
id|serio_queue_event
c_func
(paren
id|serio
comma
id|SERIO_REGISTER_PORT
)paren
suffix:semicolon
)brace
DECL|function|serio_unregister_port
r_void
id|serio_unregister_port
c_func
(paren
r_struct
id|serio
op_star
id|serio
)paren
(brace
id|down
c_func
(paren
op_amp
id|serio_sem
)paren
suffix:semicolon
id|serio_disconnect_port
c_func
(paren
id|serio
)paren
suffix:semicolon
id|serio_destroy_port
c_func
(paren
id|serio
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|serio_sem
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Submits unregister request to kseriod for subsequent execution.&n; * Can be used when it is not obvious whether the serio_sem is&n; * taken or not and when delayed execution is feasible.&n; */
DECL|function|serio_unregister_port_delayed
r_void
id|serio_unregister_port_delayed
c_func
(paren
r_struct
id|serio
op_star
id|serio
)paren
(brace
id|serio_queue_event
c_func
(paren
id|serio
comma
id|SERIO_UNREGISTER_PORT
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Serio driver operations&n; */
DECL|function|serio_driver_show_description
r_static
id|ssize_t
id|serio_driver_show_description
c_func
(paren
r_struct
id|device_driver
op_star
id|drv
comma
r_char
op_star
id|buf
)paren
(brace
r_struct
id|serio_driver
op_star
id|driver
op_assign
id|to_serio_driver
c_func
(paren
id|drv
)paren
suffix:semicolon
r_return
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%s&bslash;n&quot;
comma
id|driver-&gt;description
ques
c_cond
id|driver-&gt;description
suffix:colon
l_string|&quot;(none)&quot;
)paren
suffix:semicolon
)brace
r_static
id|DRIVER_ATTR
c_func
(paren
id|description
comma
id|S_IRUGO
comma
id|serio_driver_show_description
comma
l_int|NULL
)paren
suffix:semicolon
DECL|function|serio_register_driver
r_void
id|serio_register_driver
c_func
(paren
r_struct
id|serio_driver
op_star
id|drv
)paren
(brace
r_struct
id|serio
op_star
id|serio
suffix:semicolon
id|down
c_func
(paren
op_amp
id|serio_sem
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|drv-&gt;node
comma
op_amp
id|serio_driver_list
)paren
suffix:semicolon
id|drv-&gt;driver.bus
op_assign
op_amp
id|serio_bus
suffix:semicolon
id|driver_register
c_func
(paren
op_amp
id|drv-&gt;driver
)paren
suffix:semicolon
id|driver_create_file
c_func
(paren
op_amp
id|drv-&gt;driver
comma
op_amp
id|driver_attr_description
)paren
suffix:semicolon
id|start_over
suffix:colon
id|list_for_each_entry
c_func
(paren
id|serio
comma
op_amp
id|serio_list
comma
id|node
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|serio-&gt;drv
)paren
(brace
id|serio_connect_port
c_func
(paren
id|serio
comma
id|drv
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * if new child appeared then the list is changed,&n;&t;&t;&t; * we need to start over&n;&t;&t;&t; */
r_if
c_cond
(paren
id|serio-&gt;child
)paren
r_goto
id|start_over
suffix:semicolon
)brace
)brace
id|up
c_func
(paren
op_amp
id|serio_sem
)paren
suffix:semicolon
)brace
DECL|function|serio_unregister_driver
r_void
id|serio_unregister_driver
c_func
(paren
r_struct
id|serio_driver
op_star
id|drv
)paren
(brace
r_struct
id|serio
op_star
id|serio
suffix:semicolon
id|down
c_func
(paren
op_amp
id|serio_sem
)paren
suffix:semicolon
id|list_del_init
c_func
(paren
op_amp
id|drv-&gt;node
)paren
suffix:semicolon
id|start_over
suffix:colon
id|list_for_each_entry
c_func
(paren
id|serio
comma
op_amp
id|serio_list
comma
id|node
)paren
(brace
r_if
c_cond
(paren
id|serio-&gt;drv
op_eq
id|drv
)paren
(brace
id|serio_disconnect_port
c_func
(paren
id|serio
)paren
suffix:semicolon
id|serio_connect_port
c_func
(paren
id|serio
comma
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/* we could&squot;ve deleted some ports, restart */
r_goto
id|start_over
suffix:semicolon
)brace
)brace
id|driver_unregister
c_func
(paren
op_amp
id|drv-&gt;driver
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|serio_sem
)paren
suffix:semicolon
)brace
multiline_comment|/* called from serio_driver-&gt;connect/disconnect methods under serio_sem */
DECL|function|serio_open
r_int
id|serio_open
c_func
(paren
r_struct
id|serio
op_star
id|serio
comma
r_struct
id|serio_driver
op_star
id|drv
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|serio-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|serio-&gt;drv
op_assign
id|drv
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|serio-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|serio-&gt;open
op_logical_and
id|serio
op_member_access_from_pointer
id|open
c_func
(paren
id|serio
)paren
)paren
(brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|serio-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|serio-&gt;drv
op_assign
l_int|NULL
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|serio-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* called from serio_driver-&gt;connect/disconnect methods under serio_sem */
DECL|function|serio_close
r_void
id|serio_close
c_func
(paren
r_struct
id|serio
op_star
id|serio
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|serio-&gt;close
)paren
id|serio
op_member_access_from_pointer
id|close
c_func
(paren
id|serio
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|serio-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|serio-&gt;drv
op_assign
l_int|NULL
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|serio-&gt;lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|serio_interrupt
id|irqreturn_t
id|serio_interrupt
c_func
(paren
r_struct
id|serio
op_star
id|serio
comma
r_int
r_char
id|data
comma
r_int
r_int
id|dfl
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|irqreturn_t
id|ret
op_assign
id|IRQ_NONE
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|serio-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|likely
c_func
(paren
id|serio-&gt;drv
)paren
)paren
(brace
id|ret
op_assign
id|serio-&gt;drv
op_member_access_from_pointer
id|interrupt
c_func
(paren
id|serio
comma
id|data
comma
id|dfl
comma
id|regs
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
op_logical_neg
id|dfl
)paren
(brace
r_if
c_cond
(paren
(paren
id|serio-&gt;type
op_ne
id|SERIO_8042
op_logical_and
id|serio-&gt;type
op_ne
id|SERIO_8042_XL
)paren
op_logical_or
(paren
id|data
op_eq
l_int|0xaa
)paren
)paren
(brace
id|serio_rescan
c_func
(paren
id|serio
)paren
suffix:semicolon
id|ret
op_assign
id|IRQ_HANDLED
suffix:semicolon
)brace
)brace
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|serio-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|serio_init
r_static
r_int
id|__init
id|serio_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|serio_pid
op_assign
id|kernel_thread
c_func
(paren
id|serio_thread
comma
l_int|NULL
comma
id|CLONE_KERNEL
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;serio: Failed to start kseriod&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|bus_register
c_func
(paren
op_amp
id|serio_bus
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|serio_exit
r_static
r_void
id|__exit
id|serio_exit
c_func
(paren
r_void
)paren
(brace
id|bus_unregister
c_func
(paren
op_amp
id|serio_bus
)paren
suffix:semicolon
id|kill_proc
c_func
(paren
id|serio_pid
comma
id|SIGTERM
comma
l_int|1
)paren
suffix:semicolon
id|wait_for_completion
c_func
(paren
op_amp
id|serio_exited
)paren
suffix:semicolon
)brace
DECL|variable|serio_init
id|module_init
c_func
(paren
id|serio_init
)paren
suffix:semicolon
DECL|variable|serio_exit
id|module_exit
c_func
(paren
id|serio_exit
)paren
suffix:semicolon
eof
