multiline_comment|/*&n; *  drivers/s390/cio/device.c&n; *  bus driver for ccw devices&n; *   $Revision: 1.54 $&n; *&n; *    Copyright (C) 2002 IBM Deutschland Entwicklung GmbH,&n; *&t;&t;&t; IBM Corporation&n; *    Author(s): Arnd Bergmann (arndb@de.ibm.com)&n; *&t;&t; Cornelia Huck (cohuck@de.ibm.com)&n; *&t;&t; Martin Schwidefsky (schwidefsky@de.ibm.com)&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/err.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/workqueue.h&gt;
macro_line|#include &lt;asm/ccwdev.h&gt;
macro_line|#include &lt;asm/cio.h&gt;
macro_line|#include &quot;cio.h&quot;
macro_line|#include &quot;css.h&quot;
macro_line|#include &quot;device.h&quot;
multiline_comment|/******************* bus type handling ***********************/
multiline_comment|/* The Linux driver model distinguishes between a bus type and&n; * the bus itself. Of course we only have one channel&n; * subsystem driver and one channel system per machine, but&n; * we still use the abstraction. T.R. says it&squot;s a good idea. */
r_static
r_int
DECL|function|ccw_bus_match
id|ccw_bus_match
(paren
r_struct
id|device
op_star
id|dev
comma
r_struct
id|device_driver
op_star
id|drv
)paren
(brace
r_struct
id|ccw_device
op_star
id|cdev
op_assign
id|to_ccwdev
c_func
(paren
id|dev
)paren
suffix:semicolon
r_struct
id|ccw_driver
op_star
id|cdrv
op_assign
id|to_ccwdrv
c_func
(paren
id|drv
)paren
suffix:semicolon
r_const
r_struct
id|ccw_device_id
op_star
id|ids
op_assign
id|cdrv-&gt;ids
comma
op_star
id|found
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ids
)paren
r_return
l_int|0
suffix:semicolon
id|found
op_assign
id|ccw_device_id_match
c_func
(paren
id|ids
comma
op_amp
id|cdev-&gt;id
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|found
)paren
r_return
l_int|0
suffix:semicolon
id|cdev-&gt;id.driver_info
op_assign
id|found-&gt;driver_info
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * Hotplugging interface for ccw devices.&n; * Heavily modeled on pci and usb hotplug.&n; */
r_static
r_int
DECL|function|ccw_hotplug
id|ccw_hotplug
(paren
r_struct
id|device
op_star
id|dev
comma
r_char
op_star
op_star
id|envp
comma
r_int
id|num_envp
comma
r_char
op_star
id|buffer
comma
r_int
id|buffer_size
)paren
(brace
r_struct
id|ccw_device
op_star
id|cdev
op_assign
id|to_ccwdev
c_func
(paren
id|dev
)paren
suffix:semicolon
r_int
id|i
op_assign
l_int|0
suffix:semicolon
r_int
id|length
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cdev
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|state
op_eq
id|DEV_STATE_NOT_OPER
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
multiline_comment|/* what we want to pass to /sbin/hotplug */
id|envp
(braket
id|i
op_increment
)braket
op_assign
id|buffer
suffix:semicolon
id|length
op_add_assign
id|snprintf
c_func
(paren
id|buffer
comma
id|buffer_size
op_minus
id|length
comma
l_string|&quot;CU_TYPE=%04X&quot;
comma
id|cdev-&gt;id.cu_type
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|buffer_size
op_minus
id|length
op_le
l_int|0
)paren
op_logical_or
(paren
id|i
op_ge
id|num_envp
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
op_increment
id|length
suffix:semicolon
id|buffer
op_add_assign
id|length
suffix:semicolon
id|envp
(braket
id|i
op_increment
)braket
op_assign
id|buffer
suffix:semicolon
id|length
op_add_assign
id|snprintf
c_func
(paren
id|buffer
comma
id|buffer_size
op_minus
id|length
comma
l_string|&quot;CU_MODEL=%02X&quot;
comma
id|cdev-&gt;id.cu_model
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|buffer_size
op_minus
id|length
op_le
l_int|0
)paren
op_logical_or
(paren
id|i
op_ge
id|num_envp
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
op_increment
id|length
suffix:semicolon
id|buffer
op_add_assign
id|length
suffix:semicolon
multiline_comment|/* The next two can be zero, that&squot;s ok for us */
id|envp
(braket
id|i
op_increment
)braket
op_assign
id|buffer
suffix:semicolon
id|length
op_add_assign
id|snprintf
c_func
(paren
id|buffer
comma
id|buffer_size
op_minus
id|length
comma
l_string|&quot;DEV_TYPE=%04X&quot;
comma
id|cdev-&gt;id.dev_type
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|buffer_size
op_minus
id|length
op_le
l_int|0
)paren
op_logical_or
(paren
id|i
op_ge
id|num_envp
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
op_increment
id|length
suffix:semicolon
id|buffer
op_add_assign
id|length
suffix:semicolon
id|envp
(braket
id|i
op_increment
)braket
op_assign
id|buffer
suffix:semicolon
id|length
op_add_assign
id|snprintf
c_func
(paren
id|buffer
comma
id|buffer_size
op_minus
id|length
comma
l_string|&quot;DEV_MODEL=%02X&quot;
comma
id|cdev-&gt;id.dev_model
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|buffer_size
op_minus
id|length
op_le
l_int|0
)paren
op_logical_or
(paren
id|i
op_ge
id|num_envp
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|envp
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|ccw_bus_type
r_struct
id|bus_type
id|ccw_bus_type
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;ccw&quot;
comma
dot
id|match
op_assign
op_amp
id|ccw_bus_match
comma
dot
id|hotplug
op_assign
op_amp
id|ccw_hotplug
comma
)brace
suffix:semicolon
r_static
r_int
id|io_subchannel_probe
(paren
r_struct
id|device
op_star
)paren
suffix:semicolon
r_void
id|io_subchannel_irq
(paren
r_struct
id|device
op_star
)paren
suffix:semicolon
DECL|variable|io_subchannel_driver
r_static
r_struct
id|css_driver
id|io_subchannel_driver
op_assign
(brace
dot
id|subchannel_type
op_assign
id|SUBCHANNEL_TYPE_IO
comma
dot
id|drv
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;io_subchannel&quot;
comma
dot
id|bus
op_assign
op_amp
id|css_bus_type
comma
dot
id|probe
op_assign
op_amp
id|io_subchannel_probe
comma
)brace
comma
dot
id|irq
op_assign
id|io_subchannel_irq
comma
)brace
suffix:semicolon
DECL|variable|ccw_device_work
r_struct
id|workqueue_struct
op_star
id|ccw_device_work
suffix:semicolon
DECL|variable|ccw_device_init_wq
r_static
id|wait_queue_head_t
id|ccw_device_init_wq
suffix:semicolon
DECL|variable|ccw_device_init_count
r_static
id|atomic_t
id|ccw_device_init_count
suffix:semicolon
r_static
r_int
id|__init
DECL|function|init_ccw_bus_type
id|init_ccw_bus_type
(paren
r_void
)paren
(brace
r_int
id|ret
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|ccw_device_init_wq
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|ccw_device_init_count
comma
l_int|0
)paren
suffix:semicolon
id|ccw_device_work
op_assign
id|create_workqueue
c_func
(paren
l_string|&quot;cio&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ccw_device_work
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
multiline_comment|/* FIXME: better errno ? */
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|bus_register
(paren
op_amp
id|ccw_bus_type
)paren
)paren
)paren
r_return
id|ret
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|driver_register
c_func
(paren
op_amp
id|io_subchannel_driver.drv
)paren
)paren
)paren
r_return
id|ret
suffix:semicolon
id|wait_event
c_func
(paren
id|ccw_device_init_wq
comma
id|atomic_read
c_func
(paren
op_amp
id|ccw_device_init_count
)paren
op_eq
l_int|0
)paren
suffix:semicolon
id|flush_workqueue
c_func
(paren
id|ccw_device_work
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_void
id|__exit
DECL|function|cleanup_ccw_bus_type
id|cleanup_ccw_bus_type
(paren
r_void
)paren
(brace
id|driver_unregister
c_func
(paren
op_amp
id|io_subchannel_driver.drv
)paren
suffix:semicolon
id|bus_unregister
c_func
(paren
op_amp
id|ccw_bus_type
)paren
suffix:semicolon
id|destroy_workqueue
c_func
(paren
id|ccw_device_work
)paren
suffix:semicolon
)brace
DECL|variable|init_ccw_bus_type
id|subsys_initcall
c_func
(paren
id|init_ccw_bus_type
)paren
suffix:semicolon
DECL|variable|cleanup_ccw_bus_type
id|module_exit
c_func
(paren
id|cleanup_ccw_bus_type
)paren
suffix:semicolon
multiline_comment|/************************ device handling **************************/
multiline_comment|/*&n; * A ccw_device has some interfaces in sysfs in addition to the&n; * standard ones.&n; * The following entries are designed to export the information which&n; * resided in 2.4 in /proc/subchannels. Subchannel and device number&n; * are obvious, so they don&squot;t have an entry :)&n; * TODO: Split chpids and pimpampom up? Where is &quot;in use&quot; in the tree?&n; */
r_static
id|ssize_t
DECL|function|chpids_show
id|chpids_show
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
id|subchannel
op_star
id|sch
op_assign
id|to_subchannel
c_func
(paren
id|dev
)paren
suffix:semicolon
r_struct
id|ssd_info
op_star
id|ssd
op_assign
op_amp
id|sch-&gt;ssd_info
suffix:semicolon
id|ssize_t
id|ret
op_assign
l_int|0
suffix:semicolon
r_int
id|chp
suffix:semicolon
r_for
c_loop
(paren
id|chp
op_assign
l_int|0
suffix:semicolon
id|chp
OL
l_int|8
suffix:semicolon
id|chp
op_increment
)paren
id|ret
op_add_assign
id|sprintf
(paren
id|buf
op_plus
id|ret
comma
l_string|&quot;%02x &quot;
comma
id|ssd-&gt;chpid
(braket
id|chp
)braket
)paren
suffix:semicolon
id|ret
op_add_assign
id|sprintf
(paren
id|buf
op_plus
id|ret
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|min
c_func
(paren
(paren
id|ssize_t
)paren
id|PAGE_SIZE
comma
id|ret
)paren
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|pimpampom_show
id|pimpampom_show
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
id|subchannel
op_star
id|sch
op_assign
id|to_subchannel
c_func
(paren
id|dev
)paren
suffix:semicolon
r_struct
id|pmcw
op_star
id|pmcw
op_assign
op_amp
id|sch-&gt;schib.pmcw
suffix:semicolon
r_return
id|sprintf
(paren
id|buf
comma
l_string|&quot;%02x %02x %02x&bslash;n&quot;
comma
id|pmcw-&gt;pim
comma
id|pmcw-&gt;pam
comma
id|pmcw-&gt;pom
)paren
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|devtype_show
id|devtype_show
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
id|ccw_device
op_star
id|cdev
op_assign
id|to_ccwdev
c_func
(paren
id|dev
)paren
suffix:semicolon
r_struct
id|ccw_device_id
op_star
id|id
op_assign
op_amp
(paren
id|cdev-&gt;id
)paren
suffix:semicolon
r_if
c_cond
(paren
id|id-&gt;dev_type
op_ne
l_int|0
)paren
r_return
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%04x/%02x&bslash;n&quot;
comma
id|id-&gt;dev_type
comma
id|id-&gt;dev_model
)paren
suffix:semicolon
r_else
r_return
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;n/a&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|cutype_show
id|cutype_show
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
id|ccw_device
op_star
id|cdev
op_assign
id|to_ccwdev
c_func
(paren
id|dev
)paren
suffix:semicolon
r_struct
id|ccw_device_id
op_star
id|id
op_assign
op_amp
(paren
id|cdev-&gt;id
)paren
suffix:semicolon
r_return
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%04x/%02x&bslash;n&quot;
comma
id|id-&gt;cu_type
comma
id|id-&gt;cu_model
)paren
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|online_show
id|online_show
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
id|ccw_device
op_star
id|cdev
op_assign
id|to_ccwdev
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
id|cdev-&gt;online
ques
c_cond
l_string|&quot;yes&bslash;n&quot;
suffix:colon
l_string|&quot;no&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_void
DECL|function|ccw_device_set_offline
id|ccw_device_set_offline
c_func
(paren
r_struct
id|ccw_device
op_star
id|cdev
)paren
(brace
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cdev
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cdev-&gt;online
op_logical_or
op_logical_neg
id|cdev-&gt;drv
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|cdev-&gt;drv-&gt;set_offline
)paren
r_if
c_cond
(paren
id|cdev-&gt;drv
op_member_access_from_pointer
id|set_offline
c_func
(paren
id|cdev
)paren
op_ne
l_int|0
)paren
r_return
suffix:semicolon
id|cdev-&gt;online
op_assign
l_int|0
suffix:semicolon
id|spin_lock_irq
c_func
(paren
id|cdev-&gt;ccwlock
)paren
suffix:semicolon
id|ret
op_assign
id|ccw_device_offline
c_func
(paren
id|cdev
)paren
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
id|cdev-&gt;ccwlock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
l_int|0
)paren
id|wait_event
c_func
(paren
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|wait_q
comma
id|dev_fsm_final_state
c_func
(paren
id|cdev
)paren
)paren
suffix:semicolon
r_else
singleline_comment|//FIXME: we can&squot;t fail!
id|pr_debug
c_func
(paren
l_string|&quot;ccw_device_offline returned %d, device %s&bslash;n&quot;
comma
id|ret
comma
id|cdev-&gt;dev.bus_id
)paren
suffix:semicolon
)brace
r_void
DECL|function|ccw_device_set_online
id|ccw_device_set_online
c_func
(paren
r_struct
id|ccw_device
op_star
id|cdev
)paren
(brace
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cdev
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|cdev-&gt;online
op_logical_or
op_logical_neg
id|cdev-&gt;drv
)paren
r_return
suffix:semicolon
id|spin_lock_irq
c_func
(paren
id|cdev-&gt;ccwlock
)paren
suffix:semicolon
id|ret
op_assign
id|ccw_device_online
c_func
(paren
id|cdev
)paren
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
id|cdev-&gt;ccwlock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
l_int|0
)paren
id|wait_event
c_func
(paren
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|wait_q
comma
id|dev_fsm_final_state
c_func
(paren
id|cdev
)paren
)paren
suffix:semicolon
r_else
(brace
id|pr_debug
c_func
(paren
l_string|&quot;ccw_device_online returned %d, device %s&bslash;n&quot;
comma
id|ret
comma
id|cdev-&gt;dev.bus_id
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|state
op_ne
id|DEV_STATE_ONLINE
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cdev-&gt;drv-&gt;set_online
op_logical_or
id|cdev-&gt;drv
op_member_access_from_pointer
id|set_online
c_func
(paren
id|cdev
)paren
op_eq
l_int|0
)paren
(brace
id|cdev-&gt;online
op_assign
l_int|1
suffix:semicolon
r_return
suffix:semicolon
)brace
id|spin_lock_irq
c_func
(paren
id|cdev-&gt;ccwlock
)paren
suffix:semicolon
id|ret
op_assign
id|ccw_device_offline
c_func
(paren
id|cdev
)paren
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
id|cdev-&gt;ccwlock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
l_int|0
)paren
id|wait_event
c_func
(paren
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|wait_q
comma
id|dev_fsm_final_state
c_func
(paren
id|cdev
)paren
)paren
suffix:semicolon
r_else
id|pr_debug
c_func
(paren
l_string|&quot;ccw_device_offline returned %d, device %s&bslash;n&quot;
comma
id|ret
comma
id|cdev-&gt;dev.bus_id
)paren
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|online_store
id|online_store
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
id|ccw_device
op_star
id|cdev
op_assign
id|to_ccwdev
c_func
(paren
id|dev
)paren
suffix:semicolon
r_int
r_int
id|value
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cdev-&gt;drv
)paren
r_return
id|count
suffix:semicolon
id|sscanf
c_func
(paren
id|buf
comma
l_string|&quot;%u&quot;
comma
op_amp
id|value
)paren
suffix:semicolon
r_if
c_cond
(paren
id|value
)paren
(brace
r_if
c_cond
(paren
id|cdev-&gt;drv-&gt;set_online
)paren
id|ccw_device_set_online
c_func
(paren
id|cdev
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|cdev-&gt;drv-&gt;set_offline
)paren
id|ccw_device_set_offline
c_func
(paren
id|cdev
)paren
suffix:semicolon
)brace
r_return
id|count
suffix:semicolon
)brace
r_static
r_void
id|ccw_device_unbox_recog
c_func
(paren
r_void
op_star
id|data
)paren
suffix:semicolon
r_static
id|ssize_t
DECL|function|stlck_store
id|stlck_store
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
id|ccw_device
op_star
id|cdev
op_assign
id|to_ccwdev
c_func
(paren
id|dev
)paren
suffix:semicolon
r_int
id|ret
suffix:semicolon
multiline_comment|/* We don&squot;t care what was piped to the attribute 8) */
id|ret
op_assign
id|ccw_device_stlck
c_func
(paren
id|cdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Unconditional reserve failed on device %s, rc=%d&bslash;n&quot;
comma
id|dev-&gt;bus_id
comma
id|ret
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Device was successfully unboxed.&n;&t; * Trigger removal of stlck attribute and device recognition.&n;&t; */
id|INIT_WORK
c_func
(paren
op_amp
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|kick_work
comma
id|ccw_device_unbox_recog
comma
(paren
r_void
op_star
)paren
id|cdev
)paren
suffix:semicolon
id|queue_work
c_func
(paren
id|ccw_device_work
comma
op_amp
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|kick_work
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
id|DEVICE_ATTR
c_func
(paren
id|chpids
comma
l_int|0444
comma
id|chpids_show
comma
l_int|NULL
)paren
suffix:semicolon
r_static
id|DEVICE_ATTR
c_func
(paren
id|pimpampom
comma
l_int|0444
comma
id|pimpampom_show
comma
l_int|NULL
)paren
suffix:semicolon
r_static
id|DEVICE_ATTR
c_func
(paren
id|devtype
comma
l_int|0444
comma
id|devtype_show
comma
l_int|NULL
)paren
suffix:semicolon
r_static
id|DEVICE_ATTR
c_func
(paren
id|cutype
comma
l_int|0444
comma
id|cutype_show
comma
l_int|NULL
)paren
suffix:semicolon
r_static
id|DEVICE_ATTR
c_func
(paren
id|online
comma
l_int|0644
comma
id|online_show
comma
id|online_store
)paren
suffix:semicolon
r_static
id|DEVICE_ATTR
c_func
(paren
id|steal_lock
comma
l_int|0200
comma
l_int|NULL
comma
id|stlck_store
)paren
suffix:semicolon
multiline_comment|/* A device has been unboxed. Start device recognition. */
r_static
r_void
DECL|function|ccw_device_unbox_recog
id|ccw_device_unbox_recog
c_func
(paren
r_void
op_star
id|data
)paren
(brace
r_struct
id|ccw_device
op_star
id|cdev
suffix:semicolon
id|cdev
op_assign
(paren
r_struct
id|ccw_device
op_star
)paren
id|data
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cdev
)paren
r_return
suffix:semicolon
multiline_comment|/* Remove stlck attribute. */
id|device_remove_file
c_func
(paren
op_amp
id|cdev-&gt;dev
comma
op_amp
id|dev_attr_steal_lock
)paren
suffix:semicolon
id|spin_lock_irq
c_func
(paren
id|cdev-&gt;ccwlock
)paren
suffix:semicolon
multiline_comment|/* Device is no longer boxed. */
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|state
op_assign
id|DEV_STATE_NOT_OPER
suffix:semicolon
multiline_comment|/* Finally start device recognition. */
id|ccw_device_recognition
c_func
(paren
id|cdev
)paren
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
id|cdev-&gt;ccwlock
)paren
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|subchannel_add_files
id|subchannel_add_files
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|device_create_file
c_func
(paren
id|dev
comma
op_amp
id|dev_attr_chpids
)paren
)paren
op_logical_or
(paren
id|ret
op_assign
id|device_create_file
c_func
(paren
id|dev
comma
op_amp
id|dev_attr_pimpampom
)paren
)paren
)paren
(brace
id|device_remove_file
c_func
(paren
id|dev
comma
op_amp
id|dev_attr_chpids
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|device_add_files
id|device_add_files
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|device_create_file
c_func
(paren
id|dev
comma
op_amp
id|dev_attr_devtype
)paren
)paren
op_logical_or
(paren
id|ret
op_assign
id|device_create_file
c_func
(paren
id|dev
comma
op_amp
id|dev_attr_cutype
)paren
)paren
op_logical_or
(paren
id|ret
op_assign
id|device_create_file
c_func
(paren
id|dev
comma
op_amp
id|dev_attr_online
)paren
)paren
)paren
(brace
id|device_remove_file
c_func
(paren
id|dev
comma
op_amp
id|dev_attr_cutype
)paren
suffix:semicolon
id|device_remove_file
c_func
(paren
id|dev
comma
op_amp
id|dev_attr_devtype
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Add a &quot;steal lock&quot; attribute to boxed devices.&n; * This allows to trigger an unconditional reserve ccw to eckd dasds&n; * (if the device is something else, there should be no problems more than&n; * a command reject; we don&squot;t have any means of finding out the device&squot;s&n; * type if it was boxed at ipl/attach).&n; */
r_void
DECL|function|ccw_device_add_stlck
id|ccw_device_add_stlck
c_func
(paren
r_struct
id|ccw_device
op_star
id|cdev
)paren
(brace
id|device_create_file
c_func
(paren
op_amp
id|cdev-&gt;dev
comma
op_amp
id|dev_attr_steal_lock
)paren
suffix:semicolon
)brace
multiline_comment|/* this is a simple abstraction for device_register that sets the&n; * correct bus type and adds the bus specific files */
r_static
r_int
DECL|function|ccw_device_register
id|ccw_device_register
c_func
(paren
r_struct
id|ccw_device
op_star
id|cdev
)paren
(brace
r_struct
id|device
op_star
id|dev
op_assign
op_amp
id|cdev-&gt;dev
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|dev-&gt;bus
op_assign
op_amp
id|ccw_bus_type
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|device_add
c_func
(paren
id|dev
)paren
)paren
)paren
r_return
id|ret
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|device_add_files
c_func
(paren
id|dev
)paren
)paren
)paren
id|device_unregister
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_static
r_void
DECL|function|ccw_device_release
id|ccw_device_release
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|ccw_device
op_star
id|cdev
suffix:semicolon
id|cdev
op_assign
id|to_ccwdev
c_func
(paren
id|dev
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|cdev
op_member_access_from_pointer
r_private
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|cdev
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Register recognized device.&n; */
r_static
r_void
DECL|function|io_subchannel_register
id|io_subchannel_register
c_func
(paren
r_void
op_star
id|data
)paren
(brace
r_struct
id|ccw_device
op_star
id|cdev
suffix:semicolon
r_struct
id|subchannel
op_star
id|sch
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|cdev
op_assign
(paren
r_struct
id|ccw_device
op_star
)paren
id|data
suffix:semicolon
id|sch
op_assign
id|to_subchannel
c_func
(paren
id|cdev-&gt;dev.parent
)paren
suffix:semicolon
multiline_comment|/* make it known to the system */
id|ret
op_assign
id|ccw_device_register
c_func
(paren
id|cdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|printk
(paren
id|KERN_WARNING
l_string|&quot;%s: could not register %s&bslash;n&quot;
comma
id|__func__
comma
id|cdev-&gt;dev.bus_id
)paren
suffix:semicolon
id|sch-&gt;dev.driver_data
op_assign
l_int|0
suffix:semicolon
id|kfree
(paren
id|cdev
op_member_access_from_pointer
r_private
)paren
suffix:semicolon
id|kfree
(paren
id|cdev
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|ret
op_assign
id|subchannel_add_files
c_func
(paren
id|cdev-&gt;dev.parent
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: could not add attributes to %04x&bslash;n&quot;
comma
id|__func__
comma
id|sch-&gt;irq
)paren
suffix:semicolon
id|out
suffix:colon
id|put_device
c_func
(paren
op_amp
id|sch-&gt;dev
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * subchannel recognition done. Called from the state machine.&n; */
r_void
DECL|function|io_subchannel_recog_done
id|io_subchannel_recog_done
c_func
(paren
r_struct
id|ccw_device
op_star
id|cdev
)paren
(brace
r_struct
id|subchannel
op_star
id|sch
suffix:semicolon
r_if
c_cond
(paren
id|css_init_done
op_eq
l_int|0
)paren
r_return
suffix:semicolon
r_switch
c_cond
(paren
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|state
)paren
(brace
r_case
id|DEV_STATE_NOT_OPER
suffix:colon
multiline_comment|/* Remove device found not operational. */
id|sch
op_assign
id|to_subchannel
c_func
(paren
id|cdev-&gt;dev.parent
)paren
suffix:semicolon
id|sch-&gt;dev.driver_data
op_assign
l_int|0
suffix:semicolon
id|put_device
c_func
(paren
op_amp
id|sch-&gt;dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cdev-&gt;dev.release
)paren
id|cdev-&gt;dev
dot
id|release
c_func
(paren
op_amp
id|cdev-&gt;dev
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DEV_STATE_OFFLINE
suffix:colon
multiline_comment|/* &n;&t;&t; * We can&squot;t register the device in interrupt context so&n;&t;&t; * we schedule a work item.&n;&t;&t; */
id|INIT_WORK
c_func
(paren
op_amp
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|kick_work
comma
id|io_subchannel_register
comma
(paren
r_void
op_star
)paren
id|cdev
)paren
suffix:semicolon
id|queue_work
c_func
(paren
id|ccw_device_work
comma
op_amp
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|kick_work
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DEV_STATE_BOXED
suffix:colon
multiline_comment|/* Device did not respond in time. */
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|atomic_dec_and_test
c_func
(paren
op_amp
id|ccw_device_init_count
)paren
)paren
id|wake_up
c_func
(paren
op_amp
id|ccw_device_init_wq
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|io_subchannel_recog
id|io_subchannel_recog
c_func
(paren
r_struct
id|ccw_device
op_star
id|cdev
comma
r_struct
id|subchannel
op_star
id|sch
)paren
(brace
r_int
id|rc
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|get_device
c_func
(paren
op_amp
id|sch-&gt;dev
)paren
)paren
(brace
r_if
c_cond
(paren
id|cdev-&gt;dev.release
)paren
id|cdev-&gt;dev
dot
id|release
c_func
(paren
op_amp
id|cdev-&gt;dev
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|sch-&gt;dev.driver_data
op_assign
id|cdev
suffix:semicolon
id|sch-&gt;driver
op_assign
op_amp
id|io_subchannel_driver
suffix:semicolon
id|cdev-&gt;ccwlock
op_assign
op_amp
id|sch-&gt;lock
suffix:semicolon
op_star
id|cdev
op_member_access_from_pointer
r_private
op_assign
(paren
r_struct
id|ccw_device_private
)paren
(brace
dot
id|devno
op_assign
id|sch-&gt;schib.pmcw.dev
comma
dot
id|irq
op_assign
id|sch-&gt;irq
comma
dot
id|state
op_assign
id|DEV_STATE_NOT_OPER
comma
)brace
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|wait_q
)paren
suffix:semicolon
id|init_timer
c_func
(paren
op_amp
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|timer
)paren
suffix:semicolon
multiline_comment|/* Set an initial name for the device. */
id|snprintf
(paren
id|cdev-&gt;dev.name
comma
id|DEVICE_NAME_SIZE
comma
l_string|&quot;ccw device&quot;
)paren
suffix:semicolon
id|snprintf
(paren
id|cdev-&gt;dev.bus_id
comma
id|DEVICE_ID_SIZE
comma
l_string|&quot;0:%04x&quot;
comma
id|sch-&gt;schib.pmcw.dev
)paren
suffix:semicolon
multiline_comment|/* Do first half of device_register. */
id|device_initialize
c_func
(paren
op_amp
id|cdev-&gt;dev
)paren
suffix:semicolon
multiline_comment|/* Increase counter of devices currently in recognition. */
id|atomic_inc
c_func
(paren
op_amp
id|ccw_device_init_count
)paren
suffix:semicolon
multiline_comment|/* Start async. device sensing. */
id|spin_lock_irq
c_func
(paren
id|cdev-&gt;ccwlock
)paren
suffix:semicolon
id|rc
op_assign
id|ccw_device_recognition
c_func
(paren
id|cdev
)paren
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
id|cdev-&gt;ccwlock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
(brace
id|sch-&gt;dev.driver_data
op_assign
l_int|0
suffix:semicolon
id|put_device
c_func
(paren
op_amp
id|sch-&gt;dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cdev-&gt;dev.release
)paren
id|cdev-&gt;dev
dot
id|release
c_func
(paren
op_amp
id|cdev-&gt;dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|atomic_dec_and_test
c_func
(paren
op_amp
id|ccw_device_init_count
)paren
)paren
id|wake_up
c_func
(paren
op_amp
id|ccw_device_init_wq
)paren
suffix:semicolon
)brace
)brace
r_static
r_int
DECL|function|io_subchannel_probe
id|io_subchannel_probe
(paren
r_struct
id|device
op_star
id|pdev
)paren
(brace
r_struct
id|subchannel
op_star
id|sch
suffix:semicolon
r_struct
id|ccw_device
op_star
id|cdev
suffix:semicolon
id|sch
op_assign
id|to_subchannel
c_func
(paren
id|pdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sch-&gt;dev.driver_data
)paren
(brace
multiline_comment|/*&n;&t;&t; * This subchannel already has an associated ccw_device.&n;&t;&t; * Register it and exit. This happens for all early&n;&t;&t; * device, e.g. the console.&n;&t;&t; */
id|ccw_device_register
c_func
(paren
id|sch-&gt;dev.driver_data
)paren
suffix:semicolon
id|subchannel_add_files
c_func
(paren
op_amp
id|sch-&gt;dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|cdev
op_assign
id|kmalloc
(paren
r_sizeof
(paren
op_star
id|cdev
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cdev
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
id|cdev
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|ccw_device
)paren
)paren
suffix:semicolon
id|cdev
op_member_access_from_pointer
r_private
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|ccw_device_private
)paren
comma
id|GFP_KERNEL
op_or
id|GFP_DMA
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cdev
op_member_access_from_pointer
r_private
)paren
(brace
id|kfree
c_func
(paren
id|cdev
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|memset
c_func
(paren
id|cdev
op_member_access_from_pointer
r_private
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|ccw_device_private
)paren
)paren
suffix:semicolon
id|cdev-&gt;dev
op_assign
(paren
r_struct
id|device
)paren
(brace
dot
id|parent
op_assign
id|pdev
comma
dot
id|release
op_assign
id|ccw_device_release
comma
)brace
suffix:semicolon
id|io_subchannel_recog
c_func
(paren
id|cdev
comma
id|to_subchannel
c_func
(paren
id|pdev
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_CCW_CONSOLE
DECL|variable|console_cdev
r_static
r_struct
id|ccw_device
id|console_cdev
suffix:semicolon
DECL|variable|console_private
r_static
r_struct
id|ccw_device_private
id|console_private
suffix:semicolon
DECL|variable|console_cdev_in_use
r_static
r_int
id|console_cdev_in_use
suffix:semicolon
r_static
r_int
DECL|function|ccw_device_console_enable
id|ccw_device_console_enable
(paren
r_struct
id|ccw_device
op_star
id|cdev
comma
r_struct
id|subchannel
op_star
id|sch
)paren
(brace
multiline_comment|/* Initialize the ccw_device structure. */
id|cdev-&gt;dev
op_assign
(paren
r_struct
id|device
)paren
(brace
dot
id|parent
op_assign
op_amp
id|sch-&gt;dev
comma
)brace
suffix:semicolon
multiline_comment|/* Initialize the subchannel structure */
id|sch-&gt;dev
op_assign
(paren
r_struct
id|device
)paren
(brace
dot
id|parent
op_assign
op_amp
id|css_bus_device
comma
dot
id|bus
op_assign
op_amp
id|css_bus_type
comma
)brace
suffix:semicolon
id|io_subchannel_recog
c_func
(paren
id|cdev
comma
id|sch
)paren
suffix:semicolon
multiline_comment|/* Now wait for the async. recognition to come to an end. */
r_while
c_loop
(paren
op_logical_neg
id|dev_fsm_final_state
c_func
(paren
id|cdev
)paren
)paren
id|wait_cons_dev
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|state
op_ne
id|DEV_STATE_OFFLINE
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|ccw_device_online
c_func
(paren
id|cdev
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|dev_fsm_final_state
c_func
(paren
id|cdev
)paren
)paren
id|wait_cons_dev
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|state
op_ne
id|DEV_STATE_ONLINE
)paren
r_return
op_minus
id|EIO
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_struct
id|ccw_device
op_star
DECL|function|ccw_device_probe_console
id|ccw_device_probe_console
c_func
(paren
r_void
)paren
(brace
r_struct
id|subchannel
op_star
id|sch
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|xchg
c_func
(paren
op_amp
id|console_cdev_in_use
comma
l_int|1
)paren
op_ne
l_int|0
)paren
r_return
l_int|NULL
suffix:semicolon
id|sch
op_assign
id|cio_probe_console
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|sch
)paren
)paren
(brace
id|console_cdev_in_use
op_assign
l_int|0
suffix:semicolon
r_return
(paren
r_void
op_star
)paren
id|sch
suffix:semicolon
)brace
id|memset
c_func
(paren
op_amp
id|console_cdev
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|ccw_device
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|console_private
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|ccw_device_private
)paren
)paren
suffix:semicolon
id|console_cdev
dot
r_private
op_assign
op_amp
id|console_private
suffix:semicolon
id|ret
op_assign
id|ccw_device_console_enable
c_func
(paren
op_amp
id|console_cdev
comma
id|sch
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|cio_release_console
c_func
(paren
)paren
suffix:semicolon
id|console_cdev_in_use
op_assign
l_int|0
suffix:semicolon
r_return
id|ERR_PTR
c_func
(paren
id|ret
)paren
suffix:semicolon
)brace
r_return
op_amp
id|console_cdev
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; * get ccw_device matching the busid, but only if owned by cdrv&n; */
r_struct
id|ccw_device
op_star
DECL|function|get_ccwdev_by_busid
id|get_ccwdev_by_busid
c_func
(paren
r_struct
id|ccw_driver
op_star
id|cdrv
comma
r_const
r_char
op_star
id|bus_id
)paren
(brace
r_struct
id|device
op_star
id|d
comma
op_star
id|dev
suffix:semicolon
r_struct
id|device_driver
op_star
id|drv
suffix:semicolon
id|drv
op_assign
id|get_driver
c_func
(paren
op_amp
id|cdrv-&gt;driver
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|drv
)paren
r_return
l_int|0
suffix:semicolon
id|down_read
c_func
(paren
op_amp
id|drv-&gt;bus-&gt;subsys.rwsem
)paren
suffix:semicolon
id|dev
op_assign
l_int|NULL
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|d
comma
op_amp
id|drv-&gt;devices
comma
id|driver_list
)paren
(brace
id|dev
op_assign
id|get_device
c_func
(paren
id|d
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev
op_logical_and
op_logical_neg
id|strncmp
c_func
(paren
id|bus_id
comma
id|dev-&gt;bus_id
comma
id|DEVICE_ID_SIZE
)paren
)paren
r_break
suffix:semicolon
r_else
id|put_device
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
id|up_read
c_func
(paren
op_amp
id|drv-&gt;bus-&gt;subsys.rwsem
)paren
suffix:semicolon
id|put_driver
c_func
(paren
id|drv
)paren
suffix:semicolon
r_return
id|dev
ques
c_cond
id|to_ccwdev
c_func
(paren
id|dev
)paren
suffix:colon
l_int|0
suffix:semicolon
)brace
multiline_comment|/************************** device driver handling ************************/
multiline_comment|/* This is the implementation of the ccw_driver class. The probe, remove&n; * and release methods are initially very similar to the device_driver&n; * implementations, with the difference that they have ccw_device&n; * arguments.&n; *&n; * A ccw driver also contains the information that is needed for&n; * device matching.&n; */
r_static
r_int
DECL|function|ccw_device_probe
id|ccw_device_probe
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|ccw_device
op_star
id|cdev
op_assign
id|to_ccwdev
c_func
(paren
id|dev
)paren
suffix:semicolon
r_struct
id|ccw_driver
op_star
id|cdrv
op_assign
id|to_ccwdrv
c_func
(paren
id|dev-&gt;driver
)paren
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|cdev-&gt;drv
op_assign
id|cdrv
suffix:semicolon
multiline_comment|/* to let the driver call _set_online */
id|ret
op_assign
id|cdrv-&gt;probe
ques
c_cond
id|cdrv
op_member_access_from_pointer
id|probe
c_func
(paren
id|cdev
)paren
suffix:colon
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|cdev-&gt;drv
op_assign
l_int|0
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|ccw_device_remove
id|ccw_device_remove
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|ccw_device
op_star
id|cdev
op_assign
id|to_ccwdev
c_func
(paren
id|dev
)paren
suffix:semicolon
r_struct
id|ccw_driver
op_star
id|cdrv
op_assign
id|cdev-&gt;drv
suffix:semicolon
multiline_comment|/*&n;&t; * Set device offline, so device drivers don&squot;t end up with&n;&t; * doubled code.&n;&t; * This is safe because of the checks in ccw_device_set_offline.&n;&t; */
id|pr_debug
c_func
(paren
l_string|&quot;removing device %s, sch %d, devno %x&bslash;n&quot;
comma
id|cdev-&gt;dev.name
comma
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|irq
comma
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|devno
)paren
suffix:semicolon
id|ccw_device_set_offline
c_func
(paren
id|cdev
)paren
suffix:semicolon
r_return
id|cdrv-&gt;remove
ques
c_cond
id|cdrv
op_member_access_from_pointer
id|remove
c_func
(paren
id|cdev
)paren
suffix:colon
l_int|0
suffix:semicolon
)brace
r_int
DECL|function|ccw_driver_register
id|ccw_driver_register
(paren
r_struct
id|ccw_driver
op_star
id|cdriver
)paren
(brace
r_struct
id|device_driver
op_star
id|drv
op_assign
op_amp
id|cdriver-&gt;driver
suffix:semicolon
id|drv-&gt;bus
op_assign
op_amp
id|ccw_bus_type
suffix:semicolon
id|drv-&gt;name
op_assign
id|cdriver-&gt;name
suffix:semicolon
id|drv-&gt;probe
op_assign
id|ccw_device_probe
suffix:semicolon
id|drv-&gt;remove
op_assign
id|ccw_device_remove
suffix:semicolon
r_return
id|driver_register
c_func
(paren
id|drv
)paren
suffix:semicolon
)brace
r_void
DECL|function|ccw_driver_unregister
id|ccw_driver_unregister
(paren
r_struct
id|ccw_driver
op_star
id|cdriver
)paren
(brace
id|driver_unregister
c_func
(paren
op_amp
id|cdriver-&gt;driver
)paren
suffix:semicolon
)brace
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|ccw_device_set_online
id|EXPORT_SYMBOL
c_func
(paren
id|ccw_device_set_online
)paren
suffix:semicolon
DECL|variable|ccw_device_set_offline
id|EXPORT_SYMBOL
c_func
(paren
id|ccw_device_set_offline
)paren
suffix:semicolon
DECL|variable|ccw_driver_register
id|EXPORT_SYMBOL
c_func
(paren
id|ccw_driver_register
)paren
suffix:semicolon
DECL|variable|ccw_driver_unregister
id|EXPORT_SYMBOL
c_func
(paren
id|ccw_driver_unregister
)paren
suffix:semicolon
DECL|variable|get_ccwdev_by_busid
id|EXPORT_SYMBOL
c_func
(paren
id|get_ccwdev_by_busid
)paren
suffix:semicolon
DECL|variable|ccw_bus_type
id|EXPORT_SYMBOL
c_func
(paren
id|ccw_bus_type
)paren
suffix:semicolon
eof
