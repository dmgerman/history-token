multiline_comment|/*&n; *&t;Linux ethernet bridge&n; *&n; *&t;Authors:&n; *&t;Lennert Buytenhek&t;&t;&lt;buytenh@gnu.org&gt;&n; *&n; *&t;$Id: br_private.h,v 1.7 2001/12/24 00:59:55 davem Exp $&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License&n; *&t;as published by the Free Software Foundation; either version&n; *&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _BR_PRIVATE_H
DECL|macro|_BR_PRIVATE_H
mdefine_line|#define _BR_PRIVATE_H
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/if_bridge.h&gt;
DECL|macro|BR_HASH_BITS
mdefine_line|#define BR_HASH_BITS 8
DECL|macro|BR_HASH_SIZE
mdefine_line|#define BR_HASH_SIZE (1 &lt;&lt; BR_HASH_BITS)
DECL|macro|BR_HOLD_TIME
mdefine_line|#define BR_HOLD_TIME (1*HZ)
DECL|macro|BR_PORT_BITS
mdefine_line|#define BR_PORT_BITS&t;10
DECL|macro|BR_MAX_PORTS
mdefine_line|#define BR_MAX_PORTS&t;(1&lt;&lt;BR_PORT_BITS)
DECL|typedef|bridge_id
r_typedef
r_struct
id|bridge_id
id|bridge_id
suffix:semicolon
DECL|typedef|mac_addr
r_typedef
r_struct
id|mac_addr
id|mac_addr
suffix:semicolon
DECL|typedef|port_id
r_typedef
id|__u16
id|port_id
suffix:semicolon
DECL|struct|bridge_id
r_struct
id|bridge_id
(brace
DECL|member|prio
r_int
r_char
id|prio
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|addr
r_int
r_char
id|addr
(braket
l_int|6
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|mac_addr
r_struct
id|mac_addr
(brace
DECL|member|addr
r_int
r_char
id|addr
(braket
l_int|6
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|net_bridge_fdb_entry
r_struct
id|net_bridge_fdb_entry
(brace
DECL|member|hlist
r_struct
id|hlist_node
id|hlist
suffix:semicolon
DECL|member|dst
r_struct
id|net_bridge_port
op_star
id|dst
suffix:semicolon
r_union
(brace
DECL|member|age_list
r_struct
id|list_head
id|age_list
suffix:semicolon
DECL|member|rcu
r_struct
id|rcu_head
id|rcu
suffix:semicolon
DECL|member|u
)brace
id|u
suffix:semicolon
DECL|member|use_count
id|atomic_t
id|use_count
suffix:semicolon
DECL|member|ageing_timer
r_int
r_int
id|ageing_timer
suffix:semicolon
DECL|member|addr
id|mac_addr
id|addr
suffix:semicolon
DECL|member|is_local
r_int
r_char
id|is_local
suffix:semicolon
DECL|member|is_static
r_int
r_char
id|is_static
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|net_bridge_port
r_struct
id|net_bridge_port
(brace
DECL|member|br
r_struct
id|net_bridge
op_star
id|br
suffix:semicolon
DECL|member|dev
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
multiline_comment|/* STP */
DECL|member|priority
id|u8
id|priority
suffix:semicolon
DECL|member|state
id|u8
id|state
suffix:semicolon
DECL|member|port_no
id|u16
id|port_no
suffix:semicolon
DECL|member|topology_change_ack
r_int
r_char
id|topology_change_ack
suffix:semicolon
DECL|member|config_pending
r_int
r_char
id|config_pending
suffix:semicolon
DECL|member|port_id
id|port_id
id|port_id
suffix:semicolon
DECL|member|designated_port
id|port_id
id|designated_port
suffix:semicolon
DECL|member|designated_root
id|bridge_id
id|designated_root
suffix:semicolon
DECL|member|designated_bridge
id|bridge_id
id|designated_bridge
suffix:semicolon
DECL|member|path_cost
id|u32
id|path_cost
suffix:semicolon
DECL|member|designated_cost
id|u32
id|designated_cost
suffix:semicolon
DECL|member|forward_delay_timer
r_struct
id|timer_list
id|forward_delay_timer
suffix:semicolon
DECL|member|hold_timer
r_struct
id|timer_list
id|hold_timer
suffix:semicolon
DECL|member|message_age_timer
r_struct
id|timer_list
id|message_age_timer
suffix:semicolon
DECL|member|kobj
r_struct
id|kobject
id|kobj
suffix:semicolon
DECL|member|rcu
r_struct
id|rcu_head
id|rcu
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|net_bridge
r_struct
id|net_bridge
(brace
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|port_list
r_struct
id|list_head
id|port_list
suffix:semicolon
DECL|member|dev
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
DECL|member|statistics
r_struct
id|net_device_stats
id|statistics
suffix:semicolon
DECL|member|hash_lock
id|spinlock_t
id|hash_lock
suffix:semicolon
DECL|member|hash
r_struct
id|hlist_head
id|hash
(braket
id|BR_HASH_SIZE
)braket
suffix:semicolon
DECL|member|age_list
r_struct
id|list_head
id|age_list
suffix:semicolon
multiline_comment|/* STP */
DECL|member|designated_root
id|bridge_id
id|designated_root
suffix:semicolon
DECL|member|bridge_id
id|bridge_id
id|bridge_id
suffix:semicolon
DECL|member|root_path_cost
id|u32
id|root_path_cost
suffix:semicolon
DECL|member|max_age
r_int
r_int
id|max_age
suffix:semicolon
DECL|member|hello_time
r_int
r_int
id|hello_time
suffix:semicolon
DECL|member|forward_delay
r_int
r_int
id|forward_delay
suffix:semicolon
DECL|member|bridge_max_age
r_int
r_int
id|bridge_max_age
suffix:semicolon
DECL|member|ageing_time
r_int
r_int
id|ageing_time
suffix:semicolon
DECL|member|bridge_hello_time
r_int
r_int
id|bridge_hello_time
suffix:semicolon
DECL|member|bridge_forward_delay
r_int
r_int
id|bridge_forward_delay
suffix:semicolon
DECL|member|root_port
id|u16
id|root_port
suffix:semicolon
DECL|member|stp_enabled
r_int
r_char
id|stp_enabled
suffix:semicolon
DECL|member|topology_change
r_int
r_char
id|topology_change
suffix:semicolon
DECL|member|topology_change_detected
r_int
r_char
id|topology_change_detected
suffix:semicolon
DECL|member|hello_timer
r_struct
id|timer_list
id|hello_timer
suffix:semicolon
DECL|member|tcn_timer
r_struct
id|timer_list
id|tcn_timer
suffix:semicolon
DECL|member|topology_change_timer
r_struct
id|timer_list
id|topology_change_timer
suffix:semicolon
DECL|member|gc_timer
r_struct
id|timer_list
id|gc_timer
suffix:semicolon
DECL|member|ifobj
r_struct
id|kobject
id|ifobj
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|notifier_block
id|br_device_notifier
suffix:semicolon
r_extern
r_const
r_int
r_char
id|bridge_ula
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* called under bridge lock */
DECL|function|br_is_root_bridge
r_static
r_inline
r_int
id|br_is_root_bridge
c_func
(paren
r_const
r_struct
id|net_bridge
op_star
id|br
)paren
(brace
r_return
op_logical_neg
id|memcmp
c_func
(paren
op_amp
id|br-&gt;bridge_id
comma
op_amp
id|br-&gt;designated_root
comma
l_int|8
)paren
suffix:semicolon
)brace
multiline_comment|/* br_device.c */
r_extern
r_void
id|br_dev_setup
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_int
id|br_dev_xmit
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
multiline_comment|/* br_fdb.c */
r_extern
r_void
id|br_fdb_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|br_fdb_fini
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|br_fdb_changeaddr
c_func
(paren
r_struct
id|net_bridge_port
op_star
id|p
comma
r_const
r_int
r_char
op_star
id|newaddr
)paren
suffix:semicolon
r_extern
r_void
id|br_fdb_cleanup
c_func
(paren
r_int
r_int
id|arg
)paren
suffix:semicolon
r_extern
r_void
id|br_fdb_delete_by_port
c_func
(paren
r_struct
id|net_bridge
op_star
id|br
comma
r_struct
id|net_bridge_port
op_star
id|p
)paren
suffix:semicolon
r_extern
r_struct
id|net_bridge_fdb_entry
op_star
id|__br_fdb_get
c_func
(paren
r_struct
id|net_bridge
op_star
id|br
comma
r_const
r_int
r_char
op_star
id|addr
)paren
suffix:semicolon
r_extern
r_struct
id|net_bridge_fdb_entry
op_star
id|br_fdb_get
c_func
(paren
r_struct
id|net_bridge
op_star
id|br
comma
r_int
r_char
op_star
id|addr
)paren
suffix:semicolon
r_extern
r_void
id|br_fdb_put
c_func
(paren
r_struct
id|net_bridge_fdb_entry
op_star
id|ent
)paren
suffix:semicolon
r_extern
r_int
id|br_fdb_fillbuf
c_func
(paren
r_struct
id|net_bridge
op_star
id|br
comma
r_void
op_star
id|buf
comma
r_int
r_int
id|count
comma
r_int
r_int
id|off
)paren
suffix:semicolon
r_extern
r_int
id|br_fdb_insert
c_func
(paren
r_struct
id|net_bridge
op_star
id|br
comma
r_struct
id|net_bridge_port
op_star
id|source
comma
r_const
r_int
r_char
op_star
id|addr
comma
r_int
id|is_local
)paren
suffix:semicolon
multiline_comment|/* br_forward.c */
r_extern
r_void
id|br_deliver
c_func
(paren
r_const
r_struct
id|net_bridge_port
op_star
id|to
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_extern
r_int
id|br_dev_queue_push_xmit
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_extern
r_void
id|br_forward
c_func
(paren
r_const
r_struct
id|net_bridge_port
op_star
id|to
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_extern
r_int
id|br_forward_finish
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_extern
r_void
id|br_flood_deliver
c_func
(paren
r_struct
id|net_bridge
op_star
id|br
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
id|clone
)paren
suffix:semicolon
r_extern
r_void
id|br_flood_forward
c_func
(paren
r_struct
id|net_bridge
op_star
id|br
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
id|clone
)paren
suffix:semicolon
multiline_comment|/* br_if.c */
r_extern
r_int
id|br_add_bridge
c_func
(paren
r_const
r_char
op_star
id|name
)paren
suffix:semicolon
r_extern
r_int
id|br_del_bridge
c_func
(paren
r_const
r_char
op_star
id|name
)paren
suffix:semicolon
r_extern
r_void
id|br_cleanup_bridges
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
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
suffix:semicolon
r_extern
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
suffix:semicolon
r_extern
r_int
id|br_min_mtu
c_func
(paren
r_const
r_struct
id|net_bridge
op_star
id|br
)paren
suffix:semicolon
multiline_comment|/* br_input.c */
r_extern
r_int
id|br_handle_frame_finish
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_extern
r_int
id|br_handle_frame
c_func
(paren
r_struct
id|net_bridge_port
op_star
id|p
comma
r_struct
id|sk_buff
op_star
op_star
id|pskb
)paren
suffix:semicolon
multiline_comment|/* br_ioctl.c */
r_extern
r_int
id|br_dev_ioctl
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|ifreq
op_star
id|rq
comma
r_int
id|cmd
)paren
suffix:semicolon
r_extern
r_int
id|br_ioctl_deviceless_stub
c_func
(paren
r_int
r_int
id|cmd
comma
r_void
id|__user
op_star
id|arg
)paren
suffix:semicolon
multiline_comment|/* br_netfilter.c */
r_extern
r_int
id|br_netfilter_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|br_netfilter_fini
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* br_stp.c */
r_extern
r_void
id|br_log_state
c_func
(paren
r_const
r_struct
id|net_bridge_port
op_star
id|p
)paren
suffix:semicolon
r_extern
r_struct
id|net_bridge_port
op_star
id|br_get_port
c_func
(paren
r_struct
id|net_bridge
op_star
id|br
comma
id|u16
id|port_no
)paren
suffix:semicolon
r_extern
r_void
id|br_init_port
c_func
(paren
r_struct
id|net_bridge_port
op_star
id|p
)paren
suffix:semicolon
r_extern
r_void
id|br_become_designated_port
c_func
(paren
r_struct
id|net_bridge_port
op_star
id|p
)paren
suffix:semicolon
multiline_comment|/* br_stp_if.c */
r_extern
r_void
id|br_stp_enable_bridge
c_func
(paren
r_struct
id|net_bridge
op_star
id|br
)paren
suffix:semicolon
r_extern
r_void
id|br_stp_disable_bridge
c_func
(paren
r_struct
id|net_bridge
op_star
id|br
)paren
suffix:semicolon
r_extern
r_void
id|br_stp_enable_port
c_func
(paren
r_struct
id|net_bridge_port
op_star
id|p
)paren
suffix:semicolon
r_extern
r_void
id|br_stp_disable_port
c_func
(paren
r_struct
id|net_bridge_port
op_star
id|p
)paren
suffix:semicolon
r_extern
r_void
id|br_stp_recalculate_bridge_id
c_func
(paren
r_struct
id|net_bridge
op_star
id|br
)paren
suffix:semicolon
r_extern
r_void
id|br_stp_set_bridge_priority
c_func
(paren
r_struct
id|net_bridge
op_star
id|br
comma
id|u16
id|newprio
)paren
suffix:semicolon
r_extern
r_void
id|br_stp_set_port_priority
c_func
(paren
r_struct
id|net_bridge_port
op_star
id|p
comma
id|u8
id|newprio
)paren
suffix:semicolon
r_extern
r_void
id|br_stp_set_path_cost
c_func
(paren
r_struct
id|net_bridge_port
op_star
id|p
comma
id|u32
id|path_cost
)paren
suffix:semicolon
r_extern
id|ssize_t
id|br_show_bridge_id
c_func
(paren
r_char
op_star
id|buf
comma
r_const
r_struct
id|bridge_id
op_star
id|id
)paren
suffix:semicolon
multiline_comment|/* br_stp_bpdu.c */
r_extern
r_int
id|br_stp_handle_bpdu
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
multiline_comment|/* br_stp_timer.c */
r_extern
r_void
id|br_stp_timer_init
c_func
(paren
r_struct
id|net_bridge
op_star
id|br
)paren
suffix:semicolon
r_extern
r_void
id|br_stp_port_timer_init
c_func
(paren
r_struct
id|net_bridge_port
op_star
id|p
)paren
suffix:semicolon
r_extern
r_int
r_int
id|br_timer_value
c_func
(paren
r_const
r_struct
id|timer_list
op_star
id|timer
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SYSFS
multiline_comment|/* br_sysfs_if.c */
r_extern
r_int
id|br_sysfs_addif
c_func
(paren
r_struct
id|net_bridge_port
op_star
id|p
)paren
suffix:semicolon
r_extern
r_void
id|br_sysfs_removeif
c_func
(paren
r_struct
id|net_bridge_port
op_star
id|p
)paren
suffix:semicolon
r_extern
r_void
id|br_sysfs_freeif
c_func
(paren
r_struct
id|net_bridge_port
op_star
id|p
)paren
suffix:semicolon
multiline_comment|/* br_sysfs_br.c */
r_extern
r_int
id|br_sysfs_addbr
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|br_sysfs_delbr
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
macro_line|#else
DECL|macro|br_sysfs_addif
mdefine_line|#define br_sysfs_addif(p)&t;(0)
DECL|macro|br_sysfs_removeif
mdefine_line|#define br_sysfs_removeif(p)&t;do { } while(0)
DECL|macro|br_sysfs_freeif
mdefine_line|#define br_sysfs_freeif(p)&t;kfree(p)
DECL|macro|br_sysfs_addbr
mdefine_line|#define br_sysfs_addbr(dev)&t;(0)
DECL|macro|br_sysfs_delbr
mdefine_line|#define br_sysfs_delbr(dev)&t;do { } while(0)
macro_line|#endif /* CONFIG_SYSFS */
macro_line|#endif
eof
