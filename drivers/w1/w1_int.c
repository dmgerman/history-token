multiline_comment|/*&n; * &t;w1_int.c&n; *&n; * Copyright (c) 2004 Evgeniy Polyakov &lt;johnpol@2ka.mipt.ru&gt;&n; * &n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &quot;w1.h&quot;
macro_line|#include &quot;w1_log.h&quot;
DECL|variable|w1_ids
r_static
id|u32
id|w1_ids
op_assign
l_int|1
suffix:semicolon
r_extern
r_struct
id|device_driver
id|w1_driver
suffix:semicolon
r_extern
r_struct
id|bus_type
id|w1_bus_type
suffix:semicolon
r_extern
r_struct
id|device
id|w1_device
suffix:semicolon
r_extern
r_struct
id|device_attribute
id|w1_master_attribute
suffix:semicolon
r_extern
r_int
id|w1_max_slave_count
suffix:semicolon
r_extern
r_struct
id|list_head
id|w1_masters
suffix:semicolon
r_extern
id|spinlock_t
id|w1_mlock
suffix:semicolon
r_extern
r_int
id|w1_process
c_func
(paren
r_void
op_star
)paren
suffix:semicolon
DECL|function|w1_alloc_dev
r_struct
id|w1_master
op_star
id|w1_alloc_dev
c_func
(paren
id|u32
id|id
comma
r_int
id|slave_count
comma
r_struct
id|device_driver
op_star
id|driver
comma
r_struct
id|device
op_star
id|device
)paren
(brace
r_struct
id|w1_master
op_star
id|dev
suffix:semicolon
r_int
id|err
suffix:semicolon
multiline_comment|/*&n;&t; * We are in process context(kernel thread), so can sleep.&n;&t; */
id|dev
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|w1_master
)paren
op_plus
r_sizeof
(paren
r_struct
id|w1_bus_master
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Failed to allocate %zd bytes for new w1 device.&bslash;n&quot;
comma
r_sizeof
(paren
r_struct
id|w1_master
)paren
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|memset
c_func
(paren
id|dev
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|w1_master
)paren
op_plus
r_sizeof
(paren
r_struct
id|w1_bus_master
)paren
)paren
suffix:semicolon
id|dev-&gt;bus_master
op_assign
(paren
r_struct
id|w1_bus_master
op_star
)paren
(paren
id|dev
op_plus
l_int|1
)paren
suffix:semicolon
id|dev-&gt;owner
op_assign
id|THIS_MODULE
suffix:semicolon
id|dev-&gt;max_slave_count
op_assign
id|slave_count
suffix:semicolon
id|dev-&gt;slave_count
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;attempts
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;kpid
op_assign
op_minus
l_int|1
suffix:semicolon
id|dev-&gt;initialized
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;id
op_assign
id|id
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|dev-&gt;refcnt
comma
l_int|2
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|dev-&gt;slist
)paren
suffix:semicolon
id|init_MUTEX
c_func
(paren
op_amp
id|dev-&gt;mutex
)paren
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|dev-&gt;kwait
)paren
suffix:semicolon
id|init_completion
c_func
(paren
op_amp
id|dev-&gt;dev_released
)paren
suffix:semicolon
id|init_completion
c_func
(paren
op_amp
id|dev-&gt;dev_exited
)paren
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|dev-&gt;dev
comma
id|device
comma
r_sizeof
(paren
r_struct
id|device
)paren
)paren
suffix:semicolon
id|snprintf
c_func
(paren
id|dev-&gt;dev.bus_id
comma
r_sizeof
(paren
id|dev-&gt;dev.bus_id
)paren
comma
l_string|&quot;w1_bus_master%u&quot;
comma
id|dev-&gt;id
)paren
suffix:semicolon
id|snprintf
c_func
(paren
id|dev-&gt;name
comma
r_sizeof
(paren
id|dev-&gt;name
)paren
comma
l_string|&quot;w1_bus_master%u&quot;
comma
id|dev-&gt;id
)paren
suffix:semicolon
id|dev-&gt;driver
op_assign
id|driver
suffix:semicolon
id|dev-&gt;groups
op_assign
l_int|23
suffix:semicolon
id|dev-&gt;seq
op_assign
l_int|1
suffix:semicolon
id|dev-&gt;nls
op_assign
id|netlink_kernel_create
c_func
(paren
id|NETLINK_NFLOG
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;nls
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Failed to create new netlink socket(%u).&bslash;n&quot;
comma
id|NETLINK_NFLOG
)paren
suffix:semicolon
id|memset
c_func
(paren
id|dev
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|w1_master
)paren
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|dev
)paren
suffix:semicolon
id|dev
op_assign
l_int|NULL
suffix:semicolon
)brace
id|err
op_assign
id|device_register
c_func
(paren
op_amp
id|dev-&gt;dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Failed to register master device. err=%d&bslash;n&quot;
comma
id|err
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;nls-&gt;sk_socket
)paren
id|sock_release
c_func
(paren
id|dev-&gt;nls-&gt;sk_socket
)paren
suffix:semicolon
id|memset
c_func
(paren
id|dev
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|w1_master
)paren
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|dev
)paren
suffix:semicolon
id|dev
op_assign
l_int|NULL
suffix:semicolon
)brace
r_return
id|dev
suffix:semicolon
)brace
DECL|function|w1_free_dev
r_void
id|w1_free_dev
c_func
(paren
r_struct
id|w1_master
op_star
id|dev
)paren
(brace
id|device_unregister
c_func
(paren
op_amp
id|dev-&gt;dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;nls-&gt;sk_socket
)paren
id|sock_release
c_func
(paren
id|dev-&gt;nls-&gt;sk_socket
)paren
suffix:semicolon
id|memset
c_func
(paren
id|dev
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|w1_master
)paren
op_plus
r_sizeof
(paren
r_struct
id|w1_bus_master
)paren
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
DECL|function|w1_add_master_device
r_int
id|w1_add_master_device
c_func
(paren
r_struct
id|w1_bus_master
op_star
id|master
)paren
(brace
r_struct
id|w1_master
op_star
id|dev
suffix:semicolon
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
id|dev
op_assign
id|w1_alloc_dev
c_func
(paren
id|w1_ids
op_increment
comma
id|w1_max_slave_count
comma
op_amp
id|w1_driver
comma
op_amp
id|w1_device
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|dev-&gt;kpid
op_assign
id|kernel_thread
c_func
(paren
op_amp
id|w1_process
comma
id|dev
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;kpid
OL
l_int|0
)paren
(brace
id|dev_err
c_func
(paren
op_amp
id|dev-&gt;dev
comma
l_string|&quot;Failed to create new kernel thread. err=%d&bslash;n&quot;
comma
id|dev-&gt;kpid
)paren
suffix:semicolon
id|retval
op_assign
id|dev-&gt;kpid
suffix:semicolon
r_goto
id|err_out_free_dev
suffix:semicolon
)brace
id|retval
op_assign
id|device_create_file
c_func
(paren
op_amp
id|dev-&gt;dev
comma
op_amp
id|w1_master_attribute
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_goto
id|err_out_kill_thread
suffix:semicolon
id|memcpy
c_func
(paren
id|dev-&gt;bus_master
comma
id|master
comma
r_sizeof
(paren
r_struct
id|w1_bus_master
)paren
)paren
suffix:semicolon
id|dev-&gt;initialized
op_assign
l_int|1
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|w1_mlock
)paren
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|dev-&gt;w1_master_entry
comma
op_amp
id|w1_masters
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|w1_mlock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|err_out_kill_thread
suffix:colon
id|dev-&gt;need_exit
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|kill_proc
c_func
(paren
id|dev-&gt;kpid
comma
id|SIGTERM
comma
l_int|1
)paren
)paren
id|dev_err
c_func
(paren
op_amp
id|dev-&gt;dev
comma
l_string|&quot;Failed to send signal to w1 kernel thread %d.&bslash;n&quot;
comma
id|dev-&gt;kpid
)paren
suffix:semicolon
id|wait_for_completion
c_func
(paren
op_amp
id|dev-&gt;dev_exited
)paren
suffix:semicolon
id|err_out_free_dev
suffix:colon
id|w1_free_dev
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|__w1_remove_master_device
r_void
id|__w1_remove_master_device
c_func
(paren
r_struct
id|w1_master
op_star
id|dev
)paren
(brace
r_int
id|err
suffix:semicolon
id|dev-&gt;need_exit
op_assign
l_int|1
suffix:semicolon
id|err
op_assign
id|kill_proc
c_func
(paren
id|dev-&gt;kpid
comma
id|SIGTERM
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
id|dev_err
c_func
(paren
op_amp
id|dev-&gt;dev
comma
l_string|&quot;%s: Failed to send signal to w1 kernel thread %d.&bslash;n&quot;
comma
id|__func__
comma
id|dev-&gt;kpid
)paren
suffix:semicolon
r_while
c_loop
(paren
id|atomic_read
c_func
(paren
op_amp
id|dev-&gt;refcnt
)paren
)paren
id|schedule_timeout
c_func
(paren
l_int|10
)paren
suffix:semicolon
id|w1_free_dev
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
DECL|function|w1_remove_master_device
r_void
id|w1_remove_master_device
c_func
(paren
r_struct
id|w1_bus_master
op_star
id|bm
)paren
(brace
r_struct
id|w1_master
op_star
id|dev
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|list_head
op_star
id|ent
comma
op_star
id|n
suffix:semicolon
id|list_for_each_safe
c_func
(paren
id|ent
comma
id|n
comma
op_amp
id|w1_masters
)paren
(brace
id|dev
op_assign
id|list_entry
c_func
(paren
id|ent
comma
r_struct
id|w1_master
comma
id|w1_master_entry
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;initialized
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;bus_master-&gt;data
op_eq
id|bm-&gt;data
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Device doesn&squot;t exist.&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|__w1_remove_master_device
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
DECL|variable|w1_alloc_dev
id|EXPORT_SYMBOL
c_func
(paren
id|w1_alloc_dev
)paren
suffix:semicolon
DECL|variable|w1_free_dev
id|EXPORT_SYMBOL
c_func
(paren
id|w1_free_dev
)paren
suffix:semicolon
DECL|variable|w1_add_master_device
id|EXPORT_SYMBOL
c_func
(paren
id|w1_add_master_device
)paren
suffix:semicolon
DECL|variable|w1_remove_master_device
id|EXPORT_SYMBOL
c_func
(paren
id|w1_remove_master_device
)paren
suffix:semicolon
DECL|variable|__w1_remove_master_device
id|EXPORT_SYMBOL
c_func
(paren
id|__w1_remove_master_device
)paren
suffix:semicolon
eof
