multiline_comment|/*&n; *&t;Spanning tree protocol; interface code&n; *&t;Linux ethernet bridge&n; *&n; *&t;Authors:&n; *&t;Lennert Buytenhek&t;&t;&lt;buytenh@gnu.org&gt;&n; *&n; *&t;$Id: br_stp_if.c,v 1.4 2001/04/14 21:14:39 davem Exp $&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License&n; *&t;as published by the Free Software Foundation; either version&n; *&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &quot;br_private.h&quot;
macro_line|#include &quot;br_private_stp.h&quot;
multiline_comment|/* Port id is composed of priority and port number.&n; * NB: least significant bits of priority are dropped to&n; *     make room for more ports.&n; */
DECL|function|br_make_port_id
r_static
r_inline
id|port_id
id|br_make_port_id
c_func
(paren
id|__u8
id|priority
comma
id|__u16
id|port_no
)paren
(brace
r_return
(paren
(paren
id|u16
)paren
id|priority
op_lshift
id|BR_PORT_BITS
)paren
op_or
(paren
id|port_no
op_amp
(paren
(paren
l_int|1
op_lshift
id|BR_PORT_BITS
)paren
op_minus
l_int|1
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* called under bridge lock */
DECL|function|br_init_port
r_void
id|br_init_port
c_func
(paren
r_struct
id|net_bridge_port
op_star
id|p
)paren
(brace
id|p-&gt;port_id
op_assign
id|br_make_port_id
c_func
(paren
id|p-&gt;priority
comma
id|p-&gt;port_no
)paren
suffix:semicolon
id|br_become_designated_port
c_func
(paren
id|p
)paren
suffix:semicolon
id|p-&gt;state
op_assign
id|BR_STATE_BLOCKING
suffix:semicolon
id|p-&gt;topology_change_ack
op_assign
l_int|0
suffix:semicolon
id|p-&gt;config_pending
op_assign
l_int|0
suffix:semicolon
id|br_stp_port_timer_init
c_func
(paren
id|p
)paren
suffix:semicolon
)brace
multiline_comment|/* called under bridge lock */
DECL|function|br_stp_enable_bridge
r_void
id|br_stp_enable_bridge
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
suffix:semicolon
id|spin_lock_bh
c_func
(paren
op_amp
id|br-&gt;lock
)paren
suffix:semicolon
id|mod_timer
c_func
(paren
op_amp
id|br-&gt;hello_timer
comma
id|jiffies
op_plus
id|br-&gt;hello_time
)paren
suffix:semicolon
id|br_config_bpdu_generation
c_func
(paren
id|br
)paren
suffix:semicolon
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
r_if
c_cond
(paren
(paren
id|p-&gt;dev-&gt;flags
op_amp
id|IFF_UP
)paren
op_logical_and
id|netif_carrier_ok
c_func
(paren
id|p-&gt;dev
)paren
)paren
id|br_stp_enable_port
c_func
(paren
id|p
)paren
suffix:semicolon
)brace
id|spin_unlock_bh
c_func
(paren
op_amp
id|br-&gt;lock
)paren
suffix:semicolon
)brace
multiline_comment|/* NO locks held */
DECL|function|br_stp_disable_bridge
r_void
id|br_stp_disable_bridge
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
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|br-&gt;lock
)paren
suffix:semicolon
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
r_if
c_cond
(paren
id|p-&gt;state
op_ne
id|BR_STATE_DISABLED
)paren
id|br_stp_disable_port
c_func
(paren
id|p
)paren
suffix:semicolon
)brace
id|br-&gt;topology_change
op_assign
l_int|0
suffix:semicolon
id|br-&gt;topology_change_detected
op_assign
l_int|0
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|br-&gt;lock
)paren
suffix:semicolon
id|del_timer_sync
c_func
(paren
op_amp
id|br-&gt;hello_timer
)paren
suffix:semicolon
id|del_timer_sync
c_func
(paren
op_amp
id|br-&gt;topology_change_timer
)paren
suffix:semicolon
id|del_timer_sync
c_func
(paren
op_amp
id|br-&gt;tcn_timer
)paren
suffix:semicolon
)brace
multiline_comment|/* called under bridge lock */
DECL|function|br_stp_enable_port
r_void
id|br_stp_enable_port
c_func
(paren
r_struct
id|net_bridge_port
op_star
id|p
)paren
(brace
id|br_init_port
c_func
(paren
id|p
)paren
suffix:semicolon
id|br_port_state_selection
c_func
(paren
id|p-&gt;br
)paren
suffix:semicolon
)brace
multiline_comment|/* called under bridge lock */
DECL|function|br_stp_disable_port
r_void
id|br_stp_disable_port
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
suffix:semicolon
r_int
id|wasroot
suffix:semicolon
id|br
op_assign
id|p-&gt;br
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: port %i(%s) entering %s state&bslash;n&quot;
comma
id|br-&gt;dev-&gt;name
comma
id|p-&gt;port_no
comma
id|p-&gt;dev-&gt;name
comma
l_string|&quot;disabled&quot;
)paren
suffix:semicolon
id|wasroot
op_assign
id|br_is_root_bridge
c_func
(paren
id|br
)paren
suffix:semicolon
id|br_become_designated_port
c_func
(paren
id|p
)paren
suffix:semicolon
id|p-&gt;state
op_assign
id|BR_STATE_DISABLED
suffix:semicolon
id|p-&gt;topology_change_ack
op_assign
l_int|0
suffix:semicolon
id|p-&gt;config_pending
op_assign
l_int|0
suffix:semicolon
id|del_timer
c_func
(paren
op_amp
id|p-&gt;message_age_timer
)paren
suffix:semicolon
id|del_timer
c_func
(paren
op_amp
id|p-&gt;forward_delay_timer
)paren
suffix:semicolon
id|del_timer
c_func
(paren
op_amp
id|p-&gt;hold_timer
)paren
suffix:semicolon
id|br_configuration_update
c_func
(paren
id|br
)paren
suffix:semicolon
id|br_port_state_selection
c_func
(paren
id|br
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
op_logical_and
op_logical_neg
id|wasroot
)paren
id|br_become_root_bridge
c_func
(paren
id|br
)paren
suffix:semicolon
)brace
multiline_comment|/* called under bridge lock */
DECL|function|br_stp_change_bridge_id
r_static
r_void
id|br_stp_change_bridge_id
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
(brace
r_int
r_char
id|oldaddr
(braket
l_int|6
)braket
suffix:semicolon
r_struct
id|net_bridge_port
op_star
id|p
suffix:semicolon
r_int
id|wasroot
suffix:semicolon
id|wasroot
op_assign
id|br_is_root_bridge
c_func
(paren
id|br
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|oldaddr
comma
id|br-&gt;bridge_id.addr
comma
id|ETH_ALEN
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|br-&gt;bridge_id.addr
comma
id|addr
comma
id|ETH_ALEN
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|br-&gt;dev-&gt;dev_addr
comma
id|addr
comma
id|ETH_ALEN
)paren
suffix:semicolon
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
r_if
c_cond
(paren
op_logical_neg
id|memcmp
c_func
(paren
id|p-&gt;designated_bridge.addr
comma
id|oldaddr
comma
id|ETH_ALEN
)paren
)paren
id|memcpy
c_func
(paren
id|p-&gt;designated_bridge.addr
comma
id|addr
comma
id|ETH_ALEN
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|memcmp
c_func
(paren
id|p-&gt;designated_root.addr
comma
id|oldaddr
comma
id|ETH_ALEN
)paren
)paren
id|memcpy
c_func
(paren
id|p-&gt;designated_root.addr
comma
id|addr
comma
id|ETH_ALEN
)paren
suffix:semicolon
)brace
id|br_configuration_update
c_func
(paren
id|br
)paren
suffix:semicolon
id|br_port_state_selection
c_func
(paren
id|br
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
op_logical_and
op_logical_neg
id|wasroot
)paren
id|br_become_root_bridge
c_func
(paren
id|br
)paren
suffix:semicolon
)brace
DECL|variable|br_mac_zero
r_static
r_const
r_int
r_char
id|br_mac_zero
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* called under bridge lock */
DECL|function|br_stp_recalculate_bridge_id
r_void
id|br_stp_recalculate_bridge_id
c_func
(paren
r_struct
id|net_bridge
op_star
id|br
)paren
(brace
r_const
r_int
r_char
op_star
id|addr
op_assign
id|br_mac_zero
suffix:semicolon
r_struct
id|net_bridge_port
op_star
id|p
suffix:semicolon
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
r_if
c_cond
(paren
id|addr
op_eq
id|br_mac_zero
op_logical_or
id|memcmp
c_func
(paren
id|p-&gt;dev-&gt;dev_addr
comma
id|addr
comma
id|ETH_ALEN
)paren
OL
l_int|0
)paren
id|addr
op_assign
id|p-&gt;dev-&gt;dev_addr
suffix:semicolon
)brace
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|br-&gt;bridge_id.addr
comma
id|addr
comma
id|ETH_ALEN
)paren
)paren
id|br_stp_change_bridge_id
c_func
(paren
id|br
comma
id|addr
)paren
suffix:semicolon
)brace
multiline_comment|/* called under bridge lock */
DECL|function|br_stp_set_bridge_priority
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
(brace
r_struct
id|net_bridge_port
op_star
id|p
suffix:semicolon
r_int
id|wasroot
suffix:semicolon
id|wasroot
op_assign
id|br_is_root_bridge
c_func
(paren
id|br
)paren
suffix:semicolon
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
r_if
c_cond
(paren
id|p-&gt;state
op_ne
id|BR_STATE_DISABLED
op_logical_and
id|br_is_designated_port
c_func
(paren
id|p
)paren
)paren
(brace
id|p-&gt;designated_bridge.prio
(braket
l_int|0
)braket
op_assign
(paren
id|newprio
op_rshift
l_int|8
)paren
op_amp
l_int|0xFF
suffix:semicolon
id|p-&gt;designated_bridge.prio
(braket
l_int|1
)braket
op_assign
id|newprio
op_amp
l_int|0xFF
suffix:semicolon
)brace
)brace
id|br-&gt;bridge_id.prio
(braket
l_int|0
)braket
op_assign
(paren
id|newprio
op_rshift
l_int|8
)paren
op_amp
l_int|0xFF
suffix:semicolon
id|br-&gt;bridge_id.prio
(braket
l_int|1
)braket
op_assign
id|newprio
op_amp
l_int|0xFF
suffix:semicolon
id|br_configuration_update
c_func
(paren
id|br
)paren
suffix:semicolon
id|br_port_state_selection
c_func
(paren
id|br
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
op_logical_and
op_logical_neg
id|wasroot
)paren
id|br_become_root_bridge
c_func
(paren
id|br
)paren
suffix:semicolon
)brace
multiline_comment|/* called under bridge lock */
DECL|function|br_stp_set_port_priority
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
(brace
id|port_id
id|new_port_id
op_assign
id|br_make_port_id
c_func
(paren
id|newprio
comma
id|p-&gt;port_no
)paren
suffix:semicolon
r_if
c_cond
(paren
id|br_is_designated_port
c_func
(paren
id|p
)paren
)paren
id|p-&gt;designated_port
op_assign
id|new_port_id
suffix:semicolon
id|p-&gt;port_id
op_assign
id|new_port_id
suffix:semicolon
id|p-&gt;priority
op_assign
id|newprio
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|memcmp
c_func
(paren
op_amp
id|p-&gt;br-&gt;bridge_id
comma
op_amp
id|p-&gt;designated_bridge
comma
l_int|8
)paren
op_logical_and
id|p-&gt;port_id
OL
id|p-&gt;designated_port
)paren
(brace
id|br_become_designated_port
c_func
(paren
id|p
)paren
suffix:semicolon
id|br_port_state_selection
c_func
(paren
id|p-&gt;br
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* called under bridge lock */
DECL|function|br_stp_set_path_cost
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
(brace
id|p-&gt;path_cost
op_assign
id|path_cost
suffix:semicolon
id|br_configuration_update
c_func
(paren
id|p-&gt;br
)paren
suffix:semicolon
id|br_port_state_selection
c_func
(paren
id|p-&gt;br
)paren
suffix:semicolon
)brace
DECL|function|br_show_bridge_id
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
(brace
r_return
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%.2x%.2x.%.2x%.2x%.2x%.2x%.2x%.2x&bslash;n&quot;
comma
id|id-&gt;prio
(braket
l_int|0
)braket
comma
id|id-&gt;prio
(braket
l_int|1
)braket
comma
id|id-&gt;addr
(braket
l_int|0
)braket
comma
id|id-&gt;addr
(braket
l_int|1
)braket
comma
id|id-&gt;addr
(braket
l_int|2
)braket
comma
id|id-&gt;addr
(braket
l_int|3
)braket
comma
id|id-&gt;addr
(braket
l_int|4
)braket
comma
id|id-&gt;addr
(braket
l_int|5
)braket
)paren
suffix:semicolon
)brace
eof
