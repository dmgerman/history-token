multiline_comment|/*&n; *&t;Ioctl handler&n; *&t;Linux ethernet bridge&n; *&n; *&t;Authors:&n; *&t;Lennert Buytenhek&t;&t;&lt;buytenh@gnu.org&gt;&n; *&n; *&t;$Id: br_ioctl.c,v 1.4 2000/11/08 05:16:40 davem Exp $&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License&n; *&t;as published by the Free Software Foundation; either version&n; *&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/if_bridge.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/times.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &quot;br_private.h&quot;
multiline_comment|/* Report time remaining in user HZ  */
DECL|function|timer_residue
r_static
r_int
r_int
id|timer_residue
c_func
(paren
r_const
r_struct
id|timer_list
op_star
id|timer
)paren
(brace
r_return
id|timer_pending
c_func
(paren
id|timer
)paren
ques
c_cond
id|jiffies_to_clock_t
c_func
(paren
id|timer-&gt;expires
op_minus
id|jiffies
)paren
suffix:colon
l_int|0
suffix:semicolon
)brace
DECL|function|br_ioctl_device
r_int
id|br_ioctl_device
c_func
(paren
r_struct
id|net_bridge
op_star
id|br
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg0
comma
r_int
r_int
id|arg1
comma
r_int
r_int
id|arg2
)paren
(brace
r_if
c_cond
(paren
id|br
op_eq
l_int|NULL
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|BRCTL_ADD_IF
suffix:colon
r_case
id|BRCTL_DEL_IF
suffix:colon
(brace
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_NET_ADMIN
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
id|dev
op_assign
id|dev_get_by_index
c_func
(paren
id|arg0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev
op_eq
l_int|NULL
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|cmd
op_eq
id|BRCTL_ADD_IF
)paren
id|ret
op_assign
id|br_add_if
c_func
(paren
id|br
comma
id|dev
)paren
suffix:semicolon
r_else
id|ret
op_assign
id|br_del_if
c_func
(paren
id|br
comma
id|dev
)paren
suffix:semicolon
id|dev_put
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_case
id|BRCTL_GET_BRIDGE_INFO
suffix:colon
(brace
r_struct
id|__bridge_info
id|b
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|b
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|__bridge_info
)paren
)paren
suffix:semicolon
id|rcu_read_lock
c_func
(paren
)paren
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|b.designated_root
comma
op_amp
id|br-&gt;designated_root
comma
l_int|8
)paren
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|b.bridge_id
comma
op_amp
id|br-&gt;bridge_id
comma
l_int|8
)paren
suffix:semicolon
id|b.root_path_cost
op_assign
id|br-&gt;root_path_cost
suffix:semicolon
id|b.max_age
op_assign
id|jiffies_to_clock_t
c_func
(paren
id|br-&gt;max_age
)paren
suffix:semicolon
id|b.hello_time
op_assign
id|jiffies_to_clock_t
c_func
(paren
id|br-&gt;hello_time
)paren
suffix:semicolon
id|b.forward_delay
op_assign
id|br-&gt;forward_delay
suffix:semicolon
id|b.bridge_max_age
op_assign
id|br-&gt;bridge_max_age
suffix:semicolon
id|b.bridge_hello_time
op_assign
id|br-&gt;bridge_hello_time
suffix:semicolon
id|b.bridge_forward_delay
op_assign
id|jiffies_to_clock_t
c_func
(paren
id|br-&gt;bridge_forward_delay
)paren
suffix:semicolon
id|b.topology_change
op_assign
id|br-&gt;topology_change
suffix:semicolon
id|b.topology_change_detected
op_assign
id|br-&gt;topology_change_detected
suffix:semicolon
id|b.root_port
op_assign
id|br-&gt;root_port
suffix:semicolon
id|b.stp_enabled
op_assign
id|br-&gt;stp_enabled
suffix:semicolon
id|b.ageing_time
op_assign
id|jiffies_to_clock_t
c_func
(paren
id|br-&gt;ageing_time
)paren
suffix:semicolon
id|b.hello_timer_value
op_assign
id|timer_residue
c_func
(paren
op_amp
id|br-&gt;hello_timer
)paren
suffix:semicolon
id|b.tcn_timer_value
op_assign
id|timer_residue
c_func
(paren
op_amp
id|br-&gt;tcn_timer
)paren
suffix:semicolon
id|b.topology_change_timer_value
op_assign
id|timer_residue
c_func
(paren
op_amp
id|br-&gt;topology_change_timer
)paren
suffix:semicolon
id|b.gc_timer_value
op_assign
id|timer_residue
c_func
(paren
op_amp
id|br-&gt;gc_timer
)paren
suffix:semicolon
id|rcu_read_unlock
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
r_void
op_star
)paren
id|arg0
comma
op_amp
id|b
comma
r_sizeof
(paren
id|b
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|BRCTL_GET_PORT_LIST
suffix:colon
(brace
r_int
id|num
op_assign
id|arg1
ques
c_cond
id|arg1
suffix:colon
l_int|256
suffix:semicolon
multiline_comment|/* compatiablity */
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_int
op_star
id|indices
suffix:semicolon
id|indices
op_assign
id|kmalloc
c_func
(paren
id|num
op_star
r_sizeof
(paren
r_int
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|indices
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
id|indices
comma
l_int|0
comma
id|num
op_star
r_sizeof
(paren
r_int
)paren
)paren
suffix:semicolon
id|br_get_port_ifindices
c_func
(paren
id|br
comma
id|indices
comma
id|num
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
r_void
op_star
)paren
id|arg0
comma
id|indices
comma
id|num
op_star
r_sizeof
(paren
r_int
)paren
)paren
)paren
id|ret
op_assign
op_minus
id|EFAULT
suffix:semicolon
id|kfree
c_func
(paren
id|indices
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_case
id|BRCTL_SET_BRIDGE_FORWARD_DELAY
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_NET_ADMIN
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
id|spin_lock_bh
c_func
(paren
op_amp
id|br-&gt;lock
)paren
suffix:semicolon
id|br-&gt;bridge_forward_delay
op_assign
id|clock_t_to_jiffies
c_func
(paren
id|arg0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|br_is_root_bridge
c_func
(paren
id|br
)paren
)paren
id|br-&gt;forward_delay
op_assign
id|br-&gt;bridge_forward_delay
suffix:semicolon
id|spin_unlock_bh
c_func
(paren
op_amp
id|br-&gt;lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|BRCTL_SET_BRIDGE_HELLO_TIME
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_NET_ADMIN
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
id|spin_lock_bh
c_func
(paren
op_amp
id|br-&gt;lock
)paren
suffix:semicolon
id|br-&gt;bridge_hello_time
op_assign
id|clock_t_to_jiffies
c_func
(paren
id|arg0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|br_is_root_bridge
c_func
(paren
id|br
)paren
)paren
id|br-&gt;hello_time
op_assign
id|br-&gt;bridge_hello_time
suffix:semicolon
id|spin_unlock_bh
c_func
(paren
op_amp
id|br-&gt;lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|BRCTL_SET_BRIDGE_MAX_AGE
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_NET_ADMIN
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
id|spin_lock_bh
c_func
(paren
op_amp
id|br-&gt;lock
)paren
suffix:semicolon
id|br-&gt;bridge_max_age
op_assign
id|clock_t_to_jiffies
c_func
(paren
id|arg0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|br_is_root_bridge
c_func
(paren
id|br
)paren
)paren
id|br-&gt;max_age
op_assign
id|br-&gt;bridge_max_age
suffix:semicolon
id|spin_unlock_bh
c_func
(paren
op_amp
id|br-&gt;lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|BRCTL_SET_AGEING_TIME
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_NET_ADMIN
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
id|br-&gt;ageing_time
op_assign
id|clock_t_to_jiffies
c_func
(paren
id|arg0
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|BRCTL_GET_PORT_INFO
suffix:colon
(brace
r_struct
id|__port_info
id|p
suffix:semicolon
r_struct
id|net_bridge_port
op_star
id|pt
suffix:semicolon
id|rcu_read_lock
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|pt
op_assign
id|br_get_port
c_func
(paren
id|br
comma
id|arg1
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|rcu_read_unlock
c_func
(paren
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|memset
c_func
(paren
op_amp
id|p
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|__port_info
)paren
)paren
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|p.designated_root
comma
op_amp
id|pt-&gt;designated_root
comma
l_int|8
)paren
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|p.designated_bridge
comma
op_amp
id|pt-&gt;designated_bridge
comma
l_int|8
)paren
suffix:semicolon
id|p.port_id
op_assign
id|pt-&gt;port_id
suffix:semicolon
id|p.designated_port
op_assign
id|pt-&gt;designated_port
suffix:semicolon
id|p.path_cost
op_assign
id|pt-&gt;path_cost
suffix:semicolon
id|p.designated_cost
op_assign
id|pt-&gt;designated_cost
suffix:semicolon
id|p.state
op_assign
id|pt-&gt;state
suffix:semicolon
id|p.top_change_ack
op_assign
id|pt-&gt;topology_change_ack
suffix:semicolon
id|p.config_pending
op_assign
id|pt-&gt;config_pending
suffix:semicolon
id|p.message_age_timer_value
op_assign
id|timer_residue
c_func
(paren
op_amp
id|pt-&gt;message_age_timer
)paren
suffix:semicolon
id|p.forward_delay_timer_value
op_assign
id|timer_residue
c_func
(paren
op_amp
id|pt-&gt;forward_delay_timer
)paren
suffix:semicolon
id|p.hold_timer_value
op_assign
id|timer_residue
c_func
(paren
op_amp
id|pt-&gt;hold_timer
)paren
suffix:semicolon
id|rcu_read_unlock
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
r_void
op_star
)paren
id|arg0
comma
op_amp
id|p
comma
r_sizeof
(paren
id|p
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|BRCTL_SET_BRIDGE_STP_STATE
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_NET_ADMIN
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
id|br-&gt;stp_enabled
op_assign
id|arg0
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|BRCTL_SET_BRIDGE_PRIORITY
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_NET_ADMIN
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
id|spin_lock_bh
c_func
(paren
op_amp
id|br-&gt;lock
)paren
suffix:semicolon
id|br_stp_set_bridge_priority
c_func
(paren
id|br
comma
id|arg0
)paren
suffix:semicolon
id|spin_unlock_bh
c_func
(paren
op_amp
id|br-&gt;lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|BRCTL_SET_PORT_PRIORITY
suffix:colon
(brace
r_struct
id|net_bridge_port
op_star
id|p
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_NET_ADMIN
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
id|spin_lock_bh
c_func
(paren
op_amp
id|br-&gt;lock
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|p
op_assign
id|br_get_port
c_func
(paren
id|br
comma
id|arg0
)paren
)paren
op_eq
l_int|NULL
)paren
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_else
id|br_stp_set_port_priority
c_func
(paren
id|p
comma
id|arg1
)paren
suffix:semicolon
id|spin_unlock_bh
c_func
(paren
op_amp
id|br-&gt;lock
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_case
id|BRCTL_SET_PATH_COST
suffix:colon
(brace
r_struct
id|net_bridge_port
op_star
id|p
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_NET_ADMIN
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
id|spin_lock_bh
c_func
(paren
op_amp
id|br-&gt;lock
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|p
op_assign
id|br_get_port
c_func
(paren
id|br
comma
id|arg0
)paren
)paren
op_eq
l_int|NULL
)paren
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_else
id|br_stp_set_path_cost
c_func
(paren
id|p
comma
id|arg1
)paren
suffix:semicolon
id|spin_unlock_bh
c_func
(paren
op_amp
id|br-&gt;lock
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_case
id|BRCTL_GET_FDB_ENTRIES
suffix:colon
r_return
id|br_fdb_get_entries
c_func
(paren
id|br
comma
(paren
r_void
op_star
)paren
id|arg0
comma
id|arg1
comma
id|arg2
)paren
suffix:semicolon
)brace
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
)brace
DECL|function|br_ioctl_deviceless
r_static
r_int
id|br_ioctl_deviceless
c_func
(paren
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg0
comma
r_int
r_int
id|arg1
)paren
(brace
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|BRCTL_GET_VERSION
suffix:colon
r_return
id|BRCTL_VERSION
suffix:semicolon
r_case
id|BRCTL_GET_BRIDGES
suffix:colon
(brace
r_int
op_star
id|indices
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
id|indices
op_assign
id|kmalloc
c_func
(paren
id|arg1
op_star
r_sizeof
(paren
r_int
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|indices
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
id|indices
comma
l_int|0
comma
id|arg1
op_star
r_sizeof
(paren
r_int
)paren
)paren
suffix:semicolon
id|arg1
op_assign
id|br_get_bridge_ifindices
c_func
(paren
id|indices
comma
id|arg1
)paren
suffix:semicolon
id|ret
op_assign
id|copy_to_user
c_func
(paren
(paren
r_void
op_star
)paren
id|arg0
comma
id|indices
comma
id|arg1
op_star
r_sizeof
(paren
r_int
)paren
)paren
ques
c_cond
op_minus
id|EFAULT
suffix:colon
id|arg1
suffix:semicolon
id|kfree
c_func
(paren
id|indices
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_case
id|BRCTL_ADD_BRIDGE
suffix:colon
r_case
id|BRCTL_DEL_BRIDGE
suffix:colon
(brace
r_char
id|buf
(braket
id|IFNAMSIZ
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_NET_ADMIN
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|buf
comma
(paren
r_void
op_star
)paren
id|arg0
comma
id|IFNAMSIZ
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|buf
(braket
id|IFNAMSIZ
op_minus
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|cmd
op_eq
id|BRCTL_ADD_BRIDGE
)paren
r_return
id|br_add_bridge
c_func
(paren
id|buf
)paren
suffix:semicolon
r_return
id|br_del_bridge
c_func
(paren
id|buf
)paren
suffix:semicolon
)brace
)brace
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
)brace
DECL|function|br_ioctl_deviceless_stub
r_int
id|br_ioctl_deviceless_stub
c_func
(paren
r_int
r_int
id|arg
)paren
(brace
r_int
r_int
id|i
(braket
l_int|3
)braket
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|i
comma
(paren
r_void
op_star
)paren
id|arg
comma
l_int|3
op_star
r_sizeof
(paren
r_int
r_int
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
id|br_ioctl_deviceless
c_func
(paren
id|i
(braket
l_int|0
)braket
comma
id|i
(braket
l_int|1
)braket
comma
id|i
(braket
l_int|2
)braket
)paren
suffix:semicolon
)brace
eof
