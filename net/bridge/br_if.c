multiline_comment|/*&n; *&t;Userspace interface&n; *&t;Linux ethernet bridge&n; *&n; *&t;Authors:&n; *&t;Lennert Buytenhek&t;&t;&lt;buytenh@gnu.org&gt;&n; *&n; *&t;$Id: br_if.c,v 1.7 2001/12/24 00:59:55 davem Exp $&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License&n; *&t;as published by the Free Software Foundation; either version&n; *&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/ethtool.h&gt;
macro_line|#include &lt;linux/if_arp.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/rtnetlink.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &quot;br_private.h&quot;
multiline_comment|/*&n; * Determine initial path cost based on speed.&n; * using recommendations from 802.1d standard&n; *&n; * Need to simulate user ioctl because not all device&squot;s that support&n; * ethtool, use ethtool_ops.  Also, since driver might sleep need to&n; * not be holding any locks.&n; */
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
r_struct
id|ethtool_cmd
id|ecmd
op_assign
(brace
id|ETHTOOL_GSET
)brace
suffix:semicolon
r_struct
id|ifreq
id|ifr
suffix:semicolon
id|mm_segment_t
id|old_fs
suffix:semicolon
r_int
id|err
suffix:semicolon
id|strncpy
c_func
(paren
id|ifr.ifr_name
comma
id|dev-&gt;name
comma
id|IFNAMSIZ
)paren
suffix:semicolon
id|ifr.ifr_data
op_assign
(paren
r_void
op_star
)paren
op_amp
id|ecmd
suffix:semicolon
id|old_fs
op_assign
id|get_fs
c_func
(paren
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|KERNEL_DS
)paren
suffix:semicolon
id|err
op_assign
id|dev_ethtool
c_func
(paren
op_amp
id|ifr
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|old_fs
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|err
)paren
(brace
r_switch
c_cond
(paren
id|ecmd.speed
)paren
(brace
r_case
id|SPEED_100
suffix:colon
r_return
l_int|19
suffix:semicolon
r_case
id|SPEED_1000
suffix:colon
r_return
l_int|4
suffix:semicolon
r_case
id|SPEED_10000
suffix:colon
r_return
l_int|2
suffix:semicolon
r_case
id|SPEED_10
suffix:colon
r_return
l_int|100
suffix:semicolon
r_default
suffix:colon
id|pr_info
c_func
(paren
l_string|&quot;bridge: can&squot;t decode speed from %s: %d&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|ecmd.speed
)paren
suffix:semicolon
r_return
l_int|100
suffix:semicolon
)brace
)brace
multiline_comment|/* Old silly heuristics based on name */
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
multiline_comment|/* assume old 10Mbps */
)brace
DECL|function|destroy_nbp
r_static
r_void
id|destroy_nbp
c_func
(paren
r_void
op_star
id|arg
)paren
(brace
r_struct
id|net_bridge_port
op_star
id|p
op_assign
id|arg
suffix:semicolon
r_struct
id|net_device
op_star
id|dev
op_assign
id|p-&gt;dev
suffix:semicolon
id|dev-&gt;br_port
op_assign
l_int|NULL
suffix:semicolon
id|p-&gt;br
op_assign
l_int|NULL
suffix:semicolon
id|p-&gt;dev
op_assign
l_int|NULL
suffix:semicolon
id|dev_put
c_func
(paren
id|dev
)paren
suffix:semicolon
id|br_sysfs_freeif
c_func
(paren
id|p
)paren
suffix:semicolon
)brace
multiline_comment|/* called with RTNL */
DECL|function|del_nbp
r_static
r_void
id|del_nbp
c_func
(paren
r_struct
id|net_bridge_port
op_star
id|p
)paren
(brace
r_struct
id|net_bridge
op_star
id|br
op_assign
id|p-&gt;br
suffix:semicolon
r_struct
id|net_device
op_star
id|dev
op_assign
id|p-&gt;dev
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
id|spin_lock_bh
c_func
(paren
op_amp
id|br-&gt;lock
)paren
suffix:semicolon
id|br_stp_disable_port
c_func
(paren
id|p
)paren
suffix:semicolon
id|spin_unlock_bh
c_func
(paren
op_amp
id|br-&gt;lock
)paren
suffix:semicolon
id|br_fdb_delete_by_port
c_func
(paren
id|br
comma
id|p
)paren
suffix:semicolon
id|list_del_rcu
c_func
(paren
op_amp
id|p-&gt;list
)paren
suffix:semicolon
id|del_timer_sync
c_func
(paren
op_amp
id|p-&gt;message_age_timer
)paren
suffix:semicolon
id|del_timer_sync
c_func
(paren
op_amp
id|p-&gt;forward_delay_timer
)paren
suffix:semicolon
id|del_timer_sync
c_func
(paren
op_amp
id|p-&gt;hold_timer
)paren
suffix:semicolon
id|call_rcu
c_func
(paren
op_amp
id|p-&gt;rcu
comma
id|destroy_nbp
comma
id|p
)paren
suffix:semicolon
)brace
multiline_comment|/* called with RTNL */
DECL|function|del_br
r_static
r_void
id|del_br
c_func
(paren
r_struct
id|net_bridge
op_star
id|br
)paren
(brace
r_struct
id|net_bridge_port
op_star
id|p
comma
op_star
id|n
suffix:semicolon
id|list_for_each_entry_safe
c_func
(paren
id|p
comma
id|n
comma
op_amp
id|br-&gt;port_list
comma
id|list
)paren
(brace
id|br_sysfs_removeif
c_func
(paren
id|p
)paren
suffix:semicolon
id|del_nbp
c_func
(paren
id|p
)paren
suffix:semicolon
)brace
id|del_timer_sync
c_func
(paren
op_amp
id|br-&gt;gc_timer
)paren
suffix:semicolon
id|br_sysfs_delbr
c_func
(paren
id|br-&gt;dev
)paren
suffix:semicolon
id|unregister_netdevice
c_func
(paren
id|br-&gt;dev
)paren
suffix:semicolon
)brace
DECL|function|new_bridge_dev
r_static
r_struct
id|net_device
op_star
id|new_bridge_dev
c_func
(paren
r_const
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
id|dev
op_assign
id|alloc_netdev
c_func
(paren
r_sizeof
(paren
r_struct
id|net_bridge
)paren
comma
id|name
comma
id|br_dev_setup
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
r_return
l_int|NULL
suffix:semicolon
id|br
op_assign
id|netdev_priv
c_func
(paren
id|dev
)paren
suffix:semicolon
id|br-&gt;dev
op_assign
id|dev
suffix:semicolon
id|br-&gt;lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|br-&gt;port_list
)paren
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
l_int|0
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
id|br-&gt;ageing_time
op_assign
l_int|300
op_star
id|HZ
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|br-&gt;age_list
)paren
suffix:semicolon
id|br_stp_timer_init
c_func
(paren
id|br
)paren
suffix:semicolon
r_return
id|dev
suffix:semicolon
)brace
multiline_comment|/* find an available port number */
DECL|function|find_portno
r_static
r_int
id|find_portno
c_func
(paren
r_struct
id|net_bridge
op_star
id|br
)paren
(brace
r_int
id|index
suffix:semicolon
r_struct
id|net_bridge_port
op_star
id|p
suffix:semicolon
r_int
r_int
op_star
id|inuse
suffix:semicolon
id|inuse
op_assign
id|kmalloc
c_func
(paren
id|BITS_TO_LONGS
c_func
(paren
id|BR_MAX_PORTS
)paren
op_star
r_sizeof
(paren
r_int
r_int
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inuse
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
id|inuse
comma
l_int|0
comma
id|BITS_TO_LONGS
c_func
(paren
id|BR_MAX_PORTS
)paren
op_star
r_sizeof
(paren
r_int
r_int
)paren
)paren
suffix:semicolon
id|set_bit
c_func
(paren
l_int|0
comma
id|inuse
)paren
suffix:semicolon
multiline_comment|/* zero is reserved */
id|list_for_each_entry
c_func
(paren
id|p
comma
op_amp
id|br-&gt;port_list
comma
id|list
)paren
(brace
id|set_bit
c_func
(paren
id|p-&gt;port_no
comma
id|inuse
)paren
suffix:semicolon
)brace
id|index
op_assign
id|find_first_zero_bit
c_func
(paren
id|inuse
comma
id|BR_MAX_PORTS
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|inuse
)paren
suffix:semicolon
r_return
(paren
id|index
op_ge
id|BR_MAX_PORTS
)paren
ques
c_cond
op_minus
id|EXFULL
suffix:colon
id|index
suffix:semicolon
)brace
multiline_comment|/* called with RTNL */
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
comma
r_int
r_int
id|cost
)paren
(brace
r_int
id|index
suffix:semicolon
r_struct
id|net_bridge_port
op_star
id|p
suffix:semicolon
id|index
op_assign
id|find_portno
c_func
(paren
id|br
)paren
suffix:semicolon
r_if
c_cond
(paren
id|index
OL
l_int|0
)paren
r_return
id|ERR_PTR
c_func
(paren
id|index
)paren
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
id|ERR_PTR
c_func
(paren
op_minus
id|ENOMEM
)paren
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
id|dev_hold
c_func
(paren
id|dev
)paren
suffix:semicolon
id|p-&gt;dev
op_assign
id|dev
suffix:semicolon
id|p-&gt;path_cost
op_assign
id|cost
suffix:semicolon
id|p-&gt;priority
op_assign
l_int|0x8000
op_rshift
id|BR_PORT_BITS
suffix:semicolon
id|dev-&gt;br_port
op_assign
id|p
suffix:semicolon
id|p-&gt;port_no
op_assign
id|index
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
id|kobject_init
c_func
(paren
op_amp
id|p-&gt;kobj
)paren
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
r_const
r_char
op_star
id|name
)paren
(brace
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|dev
op_assign
id|new_bridge_dev
c_func
(paren
id|name
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
id|rtnl_lock
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strchr
c_func
(paren
id|dev-&gt;name
comma
l_char|&squot;%&squot;
)paren
)paren
(brace
id|ret
op_assign
id|dev_alloc_name
c_func
(paren
id|dev
comma
id|dev-&gt;name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_goto
id|err1
suffix:semicolon
)brace
id|ret
op_assign
id|register_netdevice
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_goto
id|err2
suffix:semicolon
multiline_comment|/* network device kobject is not setup until&n;&t; * after rtnl_unlock does it&squot;s hotplug magic.&n;&t; * so hold reference to avoid race.&n;&t; */
id|dev_hold
c_func
(paren
id|dev
)paren
suffix:semicolon
id|rtnl_unlock
c_func
(paren
)paren
suffix:semicolon
id|ret
op_assign
id|br_sysfs_addbr
c_func
(paren
id|dev
)paren
suffix:semicolon
id|dev_put
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
id|unregister_netdev
c_func
(paren
id|dev
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|ret
suffix:semicolon
id|err2
suffix:colon
id|free_netdev
c_func
(paren
id|dev
)paren
suffix:semicolon
id|err1
suffix:colon
id|rtnl_unlock
c_func
(paren
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
DECL|function|br_del_bridge
r_int
id|br_del_bridge
c_func
(paren
r_const
r_char
op_star
id|name
)paren
(brace
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
id|rtnl_lock
c_func
(paren
)paren
suffix:semicolon
id|dev
op_assign
id|__dev_get_by_name
c_func
(paren
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev
op_eq
l_int|NULL
)paren
id|ret
op_assign
op_minus
id|ENXIO
suffix:semicolon
multiline_comment|/* Could not find device */
r_else
r_if
c_cond
(paren
op_logical_neg
(paren
id|dev-&gt;priv_flags
op_amp
id|IFF_EBRIDGE
)paren
)paren
(brace
multiline_comment|/* Attempt to delete non bridge device! */
id|ret
op_assign
op_minus
id|EPERM
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|dev-&gt;flags
op_amp
id|IFF_UP
)paren
(brace
multiline_comment|/* Not shutdown yet. */
id|ret
op_assign
op_minus
id|EBUSY
suffix:semicolon
)brace
r_else
id|del_br
c_func
(paren
id|netdev_priv
c_func
(paren
id|dev
)paren
)paren
suffix:semicolon
id|rtnl_unlock
c_func
(paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* called with RTNL */
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
r_int
id|err
op_assign
l_int|0
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
id|IS_ERR
c_func
(paren
id|p
op_assign
id|new_nbp
c_func
(paren
id|br
comma
id|dev
comma
id|br_initial_port_cost
c_func
(paren
id|dev
)paren
)paren
)paren
)paren
r_return
id|PTR_ERR
c_func
(paren
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
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
)paren
)paren
id|destroy_nbp
c_func
(paren
id|p
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
(paren
id|err
op_assign
id|br_sysfs_addif
c_func
(paren
id|p
)paren
)paren
)paren
id|del_nbp
c_func
(paren
id|p
)paren
suffix:semicolon
r_else
(brace
id|dev_set_promiscuity
c_func
(paren
id|dev
comma
l_int|1
)paren
suffix:semicolon
id|list_add_rcu
c_func
(paren
op_amp
id|p-&gt;list
comma
op_amp
id|br-&gt;port_list
)paren
suffix:semicolon
id|spin_lock_bh
c_func
(paren
op_amp
id|br-&gt;lock
)paren
suffix:semicolon
id|br_stp_recalculate_bridge_id
c_func
(paren
id|br
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|br-&gt;dev-&gt;flags
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
id|spin_unlock_bh
c_func
(paren
op_amp
id|br-&gt;lock
)paren
suffix:semicolon
)brace
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/* called with RTNL */
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
r_struct
id|net_bridge_port
op_star
id|p
op_assign
id|dev-&gt;br_port
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
op_logical_or
id|p-&gt;br
op_ne
id|br
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|br_sysfs_removeif
c_func
(paren
id|p
)paren
suffix:semicolon
id|del_nbp
c_func
(paren
id|p
)paren
suffix:semicolon
id|spin_lock_bh
c_func
(paren
op_amp
id|br-&gt;lock
)paren
suffix:semicolon
id|br_stp_recalculate_bridge_id
c_func
(paren
id|br
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
)brace
DECL|function|br_cleanup_bridges
r_void
id|__exit
id|br_cleanup_bridges
c_func
(paren
r_void
)paren
(brace
r_struct
id|net_device
op_star
id|dev
comma
op_star
id|nxt
suffix:semicolon
id|rtnl_lock
c_func
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|dev
op_assign
id|dev_base
suffix:semicolon
id|dev
suffix:semicolon
id|dev
op_assign
id|nxt
)paren
(brace
id|nxt
op_assign
id|dev-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;priv_flags
op_amp
id|IFF_EBRIDGE
)paren
id|del_br
c_func
(paren
id|dev-&gt;priv
)paren
suffix:semicolon
)brace
id|rtnl_unlock
c_func
(paren
)paren
suffix:semicolon
)brace
eof
