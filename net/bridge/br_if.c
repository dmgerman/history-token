multiline_comment|/*&n; *&t;Userspace interface&n; *&t;Linux ethernet bridge&n; *&n; *&t;Authors:&n; *&t;Lennert Buytenhek&t;&t;&lt;buytenh@gnu.org&gt;&n; *&n; *&t;$Id: br_if.c,v 1.7 2001/12/24 00:59:55 davem Exp $&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License&n; *&t;as published by the Free Software Foundation; either version&n; *&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/if_arp.h&gt;
macro_line|#include &lt;linux/if_bridge.h&gt;
macro_line|#include &lt;linux/inetdevice.h&gt;
macro_line|#include &lt;linux/rtnetlink.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &quot;br_private.h&quot;
DECL|variable|bridge_list
r_static
r_struct
id|net_bridge
op_star
id|bridge_list
suffix:semicolon
DECL|function|br_initial_port_cost
r_static
r_int
id|br_initial_port_cost
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|dev-&gt;name
comma
l_string|&quot;lec&quot;
comma
l_int|3
)paren
)paren
r_return
l_int|7
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|dev-&gt;name
comma
l_string|&quot;eth&quot;
comma
l_int|3
)paren
)paren
r_return
l_int|100
suffix:semicolon
multiline_comment|/* FIXME handle 100Mbps */
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|dev-&gt;name
comma
l_string|&quot;plip&quot;
comma
l_int|4
)paren
)paren
r_return
l_int|2500
suffix:semicolon
r_return
l_int|100
suffix:semicolon
)brace
multiline_comment|/* called under bridge lock */
DECL|function|__br_del_if
r_static
r_int
id|__br_del_if
c_func
(paren
r_struct
id|net_bridge
op_star
id|br
comma
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|net_bridge_port
op_star
id|p
suffix:semicolon
r_struct
id|net_bridge_port
op_star
op_star
id|pptr
suffix:semicolon
r_if
c_cond
(paren
(paren
id|p
op_assign
id|dev-&gt;br_port
)paren
op_eq
l_int|NULL
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|br_stp_disable_port
c_func
(paren
id|p
)paren
suffix:semicolon
id|dev_set_promiscuity
c_func
(paren
id|dev
comma
op_minus
l_int|1
)paren
suffix:semicolon
id|dev-&gt;br_port
op_assign
l_int|NULL
suffix:semicolon
id|pptr
op_assign
op_amp
id|br-&gt;port_list
suffix:semicolon
r_while
c_loop
(paren
op_star
id|pptr
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
op_star
id|pptr
op_eq
id|p
)paren
(brace
op_star
id|pptr
op_assign
id|p-&gt;next
suffix:semicolon
r_break
suffix:semicolon
)brace
id|pptr
op_assign
op_amp
(paren
(paren
op_star
id|pptr
)paren
op_member_access_from_pointer
id|next
)paren
suffix:semicolon
)brace
id|br_fdb_delete_by_port
c_func
(paren
id|br
comma
id|p
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|p
)paren
suffix:semicolon
id|dev_put
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|__find_br
r_static
r_struct
id|net_bridge
op_star
op_star
id|__find_br
c_func
(paren
r_char
op_star
id|name
)paren
(brace
r_struct
id|net_bridge
op_star
op_star
id|b
suffix:semicolon
r_struct
id|net_bridge
op_star
id|br
suffix:semicolon
id|b
op_assign
op_amp
id|bridge_list
suffix:semicolon
r_while
c_loop
(paren
(paren
id|br
op_assign
op_star
id|b
)paren
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|br-&gt;dev.name
comma
id|name
comma
id|IFNAMSIZ
)paren
)paren
r_return
id|b
suffix:semicolon
id|b
op_assign
op_amp
(paren
id|br-&gt;next
)paren
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|del_ifs
r_static
r_void
id|del_ifs
c_func
(paren
r_struct
id|net_bridge
op_star
id|br
)paren
(brace
id|write_lock_bh
c_func
(paren
op_amp
id|br-&gt;lock
)paren
suffix:semicolon
r_while
c_loop
(paren
id|br-&gt;port_list
op_ne
l_int|NULL
)paren
id|__br_del_if
c_func
(paren
id|br
comma
id|br-&gt;port_list-&gt;dev
)paren
suffix:semicolon
id|write_unlock_bh
c_func
(paren
op_amp
id|br-&gt;lock
)paren
suffix:semicolon
)brace
DECL|function|new_nb
r_static
r_struct
id|net_bridge
op_star
id|new_nb
c_func
(paren
r_char
op_star
id|name
)paren
(brace
r_struct
id|net_bridge
op_star
id|br
suffix:semicolon
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
r_if
c_cond
(paren
(paren
id|br
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|br
)paren
comma
id|GFP_KERNEL
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
l_int|NULL
suffix:semicolon
id|memset
c_func
(paren
id|br
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|br
)paren
)paren
suffix:semicolon
id|dev
op_assign
op_amp
id|br-&gt;dev
suffix:semicolon
id|strncpy
c_func
(paren
id|dev-&gt;name
comma
id|name
comma
id|IFNAMSIZ
)paren
suffix:semicolon
id|dev-&gt;priv
op_assign
id|br
suffix:semicolon
id|ether_setup
c_func
(paren
id|dev
)paren
suffix:semicolon
id|br_dev_setup
c_func
(paren
id|dev
)paren
suffix:semicolon
id|br-&gt;lock
op_assign
id|RW_LOCK_UNLOCKED
suffix:semicolon
id|br-&gt;hash_lock
op_assign
id|RW_LOCK_UNLOCKED
suffix:semicolon
id|br-&gt;bridge_id.prio
(braket
l_int|0
)braket
op_assign
l_int|0x80
suffix:semicolon
id|br-&gt;bridge_id.prio
(braket
l_int|1
)braket
op_assign
l_int|0x00
suffix:semicolon
id|memset
c_func
(paren
id|br-&gt;bridge_id.addr
comma
l_int|0
comma
id|ETH_ALEN
)paren
suffix:semicolon
id|br-&gt;stp_enabled
op_assign
l_int|1
suffix:semicolon
id|br-&gt;designated_root
op_assign
id|br-&gt;bridge_id
suffix:semicolon
id|br-&gt;root_path_cost
op_assign
l_int|0
suffix:semicolon
id|br-&gt;root_port
op_assign
l_int|0
suffix:semicolon
id|br-&gt;bridge_max_age
op_assign
id|br-&gt;max_age
op_assign
l_int|20
op_star
id|HZ
suffix:semicolon
id|br-&gt;bridge_hello_time
op_assign
id|br-&gt;hello_time
op_assign
l_int|2
op_star
id|HZ
suffix:semicolon
id|br-&gt;bridge_forward_delay
op_assign
id|br-&gt;forward_delay
op_assign
l_int|15
op_star
id|HZ
suffix:semicolon
id|br-&gt;topology_change
op_assign
l_int|0
suffix:semicolon
id|br-&gt;topology_change_detected
op_assign
l_int|0
suffix:semicolon
id|br_timer_clear
c_func
(paren
op_amp
id|br-&gt;hello_timer
)paren
suffix:semicolon
id|br_timer_clear
c_func
(paren
op_amp
id|br-&gt;tcn_timer
)paren
suffix:semicolon
id|br_timer_clear
c_func
(paren
op_amp
id|br-&gt;topology_change_timer
)paren
suffix:semicolon
id|br-&gt;ageing_time
op_assign
l_int|300
op_star
id|HZ
suffix:semicolon
id|br-&gt;gc_interval
op_assign
l_int|4
op_star
id|HZ
suffix:semicolon
r_return
id|br
suffix:semicolon
)brace
multiline_comment|/* called under bridge lock */
DECL|function|new_nbp
r_static
r_struct
id|net_bridge_port
op_star
id|new_nbp
c_func
(paren
r_struct
id|net_bridge
op_star
id|br
comma
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|net_bridge_port
op_star
id|p
suffix:semicolon
id|p
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|p
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p
op_eq
l_int|NULL
)paren
r_return
id|p
suffix:semicolon
id|memset
c_func
(paren
id|p
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|p
)paren
)paren
suffix:semicolon
id|p-&gt;br
op_assign
id|br
suffix:semicolon
id|p-&gt;dev
op_assign
id|dev
suffix:semicolon
id|p-&gt;path_cost
op_assign
id|br_initial_port_cost
c_func
(paren
id|dev
)paren
suffix:semicolon
id|p-&gt;priority
op_assign
l_int|0x80
suffix:semicolon
id|dev-&gt;br_port
op_assign
id|p
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
l_int|255
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|br_get_port
c_func
(paren
id|br
comma
id|i
)paren
op_eq
l_int|NULL
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|i
op_eq
l_int|255
)paren
(brace
id|kfree
c_func
(paren
id|p
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|p-&gt;port_no
op_assign
id|i
suffix:semicolon
id|br_init_port
c_func
(paren
id|p
)paren
suffix:semicolon
id|p-&gt;state
op_assign
id|BR_STATE_DISABLED
suffix:semicolon
id|p-&gt;next
op_assign
id|br-&gt;port_list
suffix:semicolon
id|br-&gt;port_list
op_assign
id|p
suffix:semicolon
r_return
id|p
suffix:semicolon
)brace
DECL|function|br_add_bridge
r_int
id|br_add_bridge
c_func
(paren
r_char
op_star
id|name
)paren
(brace
r_struct
id|net_bridge
op_star
id|br
suffix:semicolon
r_if
c_cond
(paren
(paren
id|br
op_assign
id|new_nb
c_func
(paren
id|name
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
id|__dev_get_by_name
c_func
(paren
id|name
)paren
op_ne
l_int|NULL
)paren
(brace
id|kfree
c_func
(paren
id|br
)paren
suffix:semicolon
r_return
op_minus
id|EEXIST
suffix:semicolon
)brace
id|br-&gt;next
op_assign
id|bridge_list
suffix:semicolon
id|bridge_list
op_assign
id|br
suffix:semicolon
id|br_inc_use_count
c_func
(paren
)paren
suffix:semicolon
id|register_netdev
c_func
(paren
op_amp
id|br-&gt;dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|br_del_bridge
r_int
id|br_del_bridge
c_func
(paren
r_char
op_star
id|name
)paren
(brace
r_struct
id|net_bridge
op_star
op_star
id|b
suffix:semicolon
r_struct
id|net_bridge
op_star
id|br
suffix:semicolon
r_if
c_cond
(paren
(paren
id|b
op_assign
id|__find_br
c_func
(paren
id|name
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
id|br
op_assign
op_star
id|b
suffix:semicolon
r_if
c_cond
(paren
id|br-&gt;dev.flags
op_amp
id|IFF_UP
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|del_ifs
c_func
(paren
id|br
)paren
suffix:semicolon
op_star
id|b
op_assign
id|br-&gt;next
suffix:semicolon
id|unregister_netdev
c_func
(paren
op_amp
id|br-&gt;dev
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|br
)paren
suffix:semicolon
id|br_dec_use_count
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|br_add_if
r_int
id|br_add_if
c_func
(paren
r_struct
id|net_bridge
op_star
id|br
comma
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|net_bridge_port
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;br_port
op_ne
l_int|NULL
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;flags
op_amp
id|IFF_LOOPBACK
op_logical_or
id|dev-&gt;type
op_ne
id|ARPHRD_ETHER
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;hard_start_xmit
op_eq
id|br_dev_xmit
)paren
r_return
op_minus
id|ELOOP
suffix:semicolon
id|dev_hold
c_func
(paren
id|dev
)paren
suffix:semicolon
id|write_lock_bh
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
id|new_nbp
c_func
(paren
id|br
comma
id|dev
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|write_unlock_bh
c_func
(paren
op_amp
id|br-&gt;lock
)paren
suffix:semicolon
id|dev_put
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
op_minus
id|EXFULL
suffix:semicolon
)brace
id|dev_set_promiscuity
c_func
(paren
id|dev
comma
l_int|1
)paren
suffix:semicolon
id|br_stp_recalculate_bridge_id
c_func
(paren
id|br
)paren
suffix:semicolon
id|br_fdb_insert
c_func
(paren
id|br
comma
id|p
comma
id|dev-&gt;dev_addr
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|br-&gt;dev.flags
op_amp
id|IFF_UP
)paren
op_logical_and
(paren
id|dev-&gt;flags
op_amp
id|IFF_UP
)paren
)paren
id|br_stp_enable_port
c_func
(paren
id|p
)paren
suffix:semicolon
id|write_unlock_bh
c_func
(paren
op_amp
id|br-&gt;lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|br_del_if
r_int
id|br_del_if
c_func
(paren
r_struct
id|net_bridge
op_star
id|br
comma
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_int
id|retval
suffix:semicolon
id|write_lock_bh
c_func
(paren
op_amp
id|br-&gt;lock
)paren
suffix:semicolon
id|retval
op_assign
id|__br_del_if
c_func
(paren
id|br
comma
id|dev
)paren
suffix:semicolon
id|br_stp_recalculate_bridge_id
c_func
(paren
id|br
)paren
suffix:semicolon
id|write_unlock_bh
c_func
(paren
op_amp
id|br-&gt;lock
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|br_get_bridge_ifindices
r_int
id|br_get_bridge_ifindices
c_func
(paren
r_int
op_star
id|indices
comma
r_int
id|num
)paren
(brace
r_struct
id|net_bridge
op_star
id|br
suffix:semicolon
r_int
id|i
suffix:semicolon
id|br
op_assign
id|bridge_list
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|num
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|br
op_eq
l_int|NULL
)paren
r_break
suffix:semicolon
id|indices
(braket
id|i
)braket
op_assign
id|br-&gt;dev.ifindex
suffix:semicolon
id|br
op_assign
id|br-&gt;next
suffix:semicolon
)brace
r_return
id|i
suffix:semicolon
)brace
multiline_comment|/* called under ioctl_lock */
DECL|function|br_get_port_ifindices
r_void
id|br_get_port_ifindices
c_func
(paren
r_struct
id|net_bridge
op_star
id|br
comma
r_int
op_star
id|ifindices
)paren
(brace
r_struct
id|net_bridge_port
op_star
id|p
suffix:semicolon
id|p
op_assign
id|br-&gt;port_list
suffix:semicolon
r_while
c_loop
(paren
id|p
op_ne
l_int|NULL
)paren
(brace
id|ifindices
(braket
id|p-&gt;port_no
)braket
op_assign
id|p-&gt;dev-&gt;ifindex
suffix:semicolon
id|p
op_assign
id|p-&gt;next
suffix:semicolon
)brace
)brace
eof
