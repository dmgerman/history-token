multiline_comment|/*&n; *&t;Spanning tree protocol; interface code&n; *&t;Linux ethernet bridge&n; *&n; *&t;Authors:&n; *&t;Lennert Buytenhek&t;&t;&lt;buytenh@gnu.org&gt;&n; *&n; *&t;$Id: br_stp_if.c,v 1.4 2001/04/14 21:14:39 davem Exp $&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License&n; *&t;as published by the Free Software Foundation; either version&n; *&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/if_bridge.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &quot;br_private.h&quot;
macro_line|#include &quot;br_private_stp.h&quot;
DECL|function|br_make_port_id
id|__u16
id|br_make_port_id
c_func
(paren
r_struct
id|net_bridge_port
op_star
id|p
)paren
(brace
r_return
(paren
id|p-&gt;priority
op_lshift
l_int|8
)paren
op_or
id|p-&gt;port_no
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
id|p
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
id|br_timer_clear
c_func
(paren
op_amp
id|p-&gt;message_age_timer
)paren
suffix:semicolon
id|br_timer_clear
c_func
(paren
op_amp
id|p-&gt;forward_delay_timer
)paren
suffix:semicolon
id|br_timer_clear
c_func
(paren
op_amp
id|p-&gt;hold_timer
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
r_struct
id|timer_list
op_star
id|timer
op_assign
op_amp
id|br-&gt;tick
suffix:semicolon
id|init_timer
c_func
(paren
id|timer
)paren
suffix:semicolon
id|timer-&gt;data
op_assign
(paren
r_int
r_int
)paren
id|br
suffix:semicolon
id|timer-&gt;function
op_assign
id|br_tick
suffix:semicolon
id|timer-&gt;expires
op_assign
id|jiffies
op_plus
l_int|1
suffix:semicolon
id|add_timer
c_func
(paren
id|timer
)paren
suffix:semicolon
id|br_timer_set
c_func
(paren
op_amp
id|br-&gt;hello_timer
comma
id|jiffies
)paren
suffix:semicolon
id|br_config_bpdu_generation
c_func
(paren
id|br
)paren
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
r_if
c_cond
(paren
id|p-&gt;dev-&gt;flags
op_amp
id|IFF_UP
)paren
id|br_stp_enable_port
c_func
(paren
id|p
)paren
suffix:semicolon
id|p
op_assign
id|p-&gt;next
suffix:semicolon
)brace
id|br_timer_set
c_func
(paren
op_amp
id|br-&gt;gc_timer
comma
id|jiffies
)paren
suffix:semicolon
)brace
multiline_comment|/* called under bridge lock */
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
id|br-&gt;topology_change_timer
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
id|br-&gt;gc_timer
)paren
suffix:semicolon
id|br_fdb_cleanup
c_func
(paren
id|br
)paren
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
id|p
op_assign
id|p-&gt;next
suffix:semicolon
)brace
id|del_timer_sync
c_func
(paren
op_amp
id|br-&gt;tick
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
id|br-&gt;dev.name
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
id|br_timer_clear
c_func
(paren
op_amp
id|p-&gt;message_age_timer
)paren
suffix:semicolon
id|br_timer_clear
c_func
(paren
op_amp
id|p-&gt;forward_delay_timer
)paren
suffix:semicolon
id|br_timer_clear
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
id|br-&gt;dev.dev_addr
comma
id|addr
comma
id|ETH_ALEN
)paren
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
id|p
op_assign
id|p-&gt;next
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
r_int
r_char
id|br_mac_zero
(braket
l_int|6
)braket
op_assign
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
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
r_int
r_char
op_star
id|addr
suffix:semicolon
r_struct
id|net_bridge_port
op_star
id|p
suffix:semicolon
id|addr
op_assign
id|br_mac_zero
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
id|p
op_assign
id|p-&gt;next
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
r_int
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
id|p
op_assign
id|p-&gt;next
suffix:semicolon
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
r_int
id|newprio
)paren
(brace
id|__u16
id|new_port_id
suffix:semicolon
id|p-&gt;priority
op_assign
id|newprio
op_amp
l_int|0xFF
suffix:semicolon
id|new_port_id
op_assign
id|br_make_port_id
c_func
(paren
id|p
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
r_int
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
eof
