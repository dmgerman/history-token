multiline_comment|/*&n; *&t;Spanning tree protocol; timer-related code&n; *&t;Linux ethernet bridge&n; *&n; *&t;Authors:&n; *&t;Lennert Buytenhek&t;&t;&lt;buytenh@gnu.org&gt;&n; *&n; *&t;$Id: br_stp_timer.c,v 1.3 2000/05/05 02:17:17 davem Exp $&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License&n; *&t;as published by the Free Software Foundation; either version&n; *&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/if_bridge.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &quot;br_private.h&quot;
macro_line|#include &quot;br_private_stp.h&quot;
multiline_comment|/* called under bridge lock */
DECL|function|br_is_designated_for_some_port
r_static
r_int
id|br_is_designated_for_some_port
c_func
(paren
r_const
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
op_logical_neg
id|memcmp
c_func
(paren
op_amp
id|p-&gt;designated_bridge
comma
op_amp
id|br-&gt;bridge_id
comma
l_int|8
)paren
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|br_hello_timer_expired
r_static
r_void
id|br_hello_timer_expired
c_func
(paren
r_int
r_int
id|arg
)paren
(brace
r_struct
id|net_bridge
op_star
id|br
op_assign
(paren
r_struct
id|net_bridge
op_star
)paren
id|arg
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;%s: hello timer expired&bslash;n&quot;
comma
id|br-&gt;dev-&gt;name
)paren
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
id|br-&gt;dev-&gt;flags
op_amp
id|IFF_UP
)paren
(brace
id|br_config_bpdu_generation
c_func
(paren
id|br
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
)brace
id|spin_unlock_bh
c_func
(paren
op_amp
id|br-&gt;lock
)paren
suffix:semicolon
)brace
DECL|function|br_message_age_timer_expired
r_static
r_void
id|br_message_age_timer_expired
c_func
(paren
r_int
r_int
id|arg
)paren
(brace
r_struct
id|net_bridge_port
op_star
id|p
op_assign
(paren
r_struct
id|net_bridge_port
op_star
)paren
id|arg
suffix:semicolon
r_struct
id|net_bridge
op_star
id|br
op_assign
id|p-&gt;br
suffix:semicolon
r_const
id|bridge_id
op_star
id|id
op_assign
op_amp
id|p-&gt;designated_bridge
suffix:semicolon
r_int
id|was_root
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;state
op_eq
id|BR_STATE_DISABLED
)paren
r_return
suffix:semicolon
id|pr_info
c_func
(paren
l_string|&quot;%s: neighbor %.2x%.2x.%.2x:%.2x:%.2x:%.2x:%.2x:%.2x lost on port %d(%s)&bslash;n&quot;
comma
id|br-&gt;dev-&gt;name
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
comma
id|p-&gt;port_no
comma
id|p-&gt;dev-&gt;name
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * According to the spec, the message age timer cannot be&n;&t; * running when we are the root bridge. So..  this was_root&n;&t; * check is redundant. I&squot;m leaving it in for now, though.&n;&t; */
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
id|p-&gt;state
op_eq
id|BR_STATE_DISABLED
)paren
r_goto
id|unlock
suffix:semicolon
id|was_root
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
id|was_root
)paren
id|br_become_root_bridge
c_func
(paren
id|br
)paren
suffix:semicolon
id|unlock
suffix:colon
id|spin_unlock_bh
c_func
(paren
op_amp
id|br-&gt;lock
)paren
suffix:semicolon
)brace
DECL|function|br_forward_delay_timer_expired
r_static
r_void
id|br_forward_delay_timer_expired
c_func
(paren
r_int
r_int
id|arg
)paren
(brace
r_struct
id|net_bridge_port
op_star
id|p
op_assign
(paren
r_struct
id|net_bridge_port
op_star
)paren
id|arg
suffix:semicolon
r_struct
id|net_bridge
op_star
id|br
op_assign
id|p-&gt;br
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;%s: %d(%s) forward delay timer&bslash;n&quot;
comma
id|br-&gt;dev-&gt;name
comma
id|p-&gt;port_no
comma
id|p-&gt;dev-&gt;name
)paren
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
id|p-&gt;state
op_eq
id|BR_STATE_LISTENING
)paren
(brace
id|p-&gt;state
op_assign
id|BR_STATE_LEARNING
suffix:semicolon
id|mod_timer
c_func
(paren
op_amp
id|p-&gt;forward_delay_timer
comma
id|jiffies
op_plus
id|br-&gt;forward_delay
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|p-&gt;state
op_eq
id|BR_STATE_LEARNING
)paren
(brace
id|p-&gt;state
op_assign
id|BR_STATE_FORWARDING
suffix:semicolon
r_if
c_cond
(paren
id|br_is_designated_for_some_port
c_func
(paren
id|br
)paren
)paren
id|br_topology_change_detection
c_func
(paren
id|br
)paren
suffix:semicolon
)brace
id|br_log_state
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
DECL|function|br_tcn_timer_expired
r_static
r_void
id|br_tcn_timer_expired
c_func
(paren
r_int
r_int
id|arg
)paren
(brace
r_struct
id|net_bridge
op_star
id|br
op_assign
(paren
r_struct
id|net_bridge
op_star
)paren
id|arg
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;%s: tcn timer expired&bslash;n&quot;
comma
id|br-&gt;dev-&gt;name
)paren
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
id|br-&gt;dev-&gt;flags
op_amp
id|IFF_UP
)paren
(brace
id|br_transmit_tcn
c_func
(paren
id|br
)paren
suffix:semicolon
id|mod_timer
c_func
(paren
op_amp
id|br-&gt;tcn_timer
comma
id|jiffies
op_plus
id|br-&gt;bridge_hello_time
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
DECL|function|br_topology_change_timer_expired
r_static
r_void
id|br_topology_change_timer_expired
c_func
(paren
r_int
r_int
id|arg
)paren
(brace
r_struct
id|net_bridge
op_star
id|br
op_assign
(paren
r_struct
id|net_bridge
op_star
)paren
id|arg
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;%s: topo change timer expired&bslash;n&quot;
comma
id|br-&gt;dev-&gt;name
)paren
suffix:semicolon
id|spin_lock_bh
c_func
(paren
op_amp
id|br-&gt;lock
)paren
suffix:semicolon
id|br-&gt;topology_change_detected
op_assign
l_int|0
suffix:semicolon
id|br-&gt;topology_change
op_assign
l_int|0
suffix:semicolon
id|spin_unlock_bh
c_func
(paren
op_amp
id|br-&gt;lock
)paren
suffix:semicolon
)brace
DECL|function|br_hold_timer_expired
r_static
r_void
id|br_hold_timer_expired
c_func
(paren
r_int
r_int
id|arg
)paren
(brace
r_struct
id|net_bridge_port
op_star
id|p
op_assign
(paren
r_struct
id|net_bridge_port
op_star
)paren
id|arg
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;%s: %d(%s) hold timer expired&bslash;n&quot;
comma
id|p-&gt;br-&gt;dev-&gt;name
comma
id|p-&gt;port_no
comma
id|p-&gt;dev-&gt;name
)paren
suffix:semicolon
id|spin_lock_bh
c_func
(paren
op_amp
id|p-&gt;br-&gt;lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;config_pending
)paren
id|br_transmit_config
c_func
(paren
id|p
)paren
suffix:semicolon
id|spin_unlock_bh
c_func
(paren
op_amp
id|p-&gt;br-&gt;lock
)paren
suffix:semicolon
)brace
DECL|function|br_timer_init
r_static
r_inline
r_void
id|br_timer_init
c_func
(paren
r_struct
id|timer_list
op_star
id|timer
comma
r_void
(paren
op_star
id|_function
)paren
(paren
r_int
r_int
)paren
comma
r_int
r_int
id|_data
)paren
(brace
id|init_timer
c_func
(paren
id|timer
)paren
suffix:semicolon
id|timer-&gt;function
op_assign
id|_function
suffix:semicolon
id|timer-&gt;data
op_assign
id|_data
suffix:semicolon
)brace
DECL|function|br_stp_timer_init
r_void
id|br_stp_timer_init
c_func
(paren
r_struct
id|net_bridge
op_star
id|br
)paren
(brace
id|br_timer_init
c_func
(paren
op_amp
id|br-&gt;hello_timer
comma
id|br_hello_timer_expired
comma
(paren
r_int
r_int
)paren
id|br
)paren
suffix:semicolon
id|br_timer_init
c_func
(paren
op_amp
id|br-&gt;tcn_timer
comma
id|br_tcn_timer_expired
comma
(paren
r_int
r_int
)paren
id|br
)paren
suffix:semicolon
id|br_timer_init
c_func
(paren
op_amp
id|br-&gt;topology_change_timer
comma
id|br_topology_change_timer_expired
comma
(paren
r_int
r_int
)paren
id|br
)paren
suffix:semicolon
id|br_timer_init
c_func
(paren
op_amp
id|br-&gt;gc_timer
comma
id|br_fdb_cleanup
comma
(paren
r_int
r_int
)paren
id|br
)paren
suffix:semicolon
)brace
DECL|function|br_stp_port_timer_init
r_void
id|br_stp_port_timer_init
c_func
(paren
r_struct
id|net_bridge_port
op_star
id|p
)paren
(brace
id|br_timer_init
c_func
(paren
op_amp
id|p-&gt;message_age_timer
comma
id|br_message_age_timer_expired
comma
(paren
r_int
r_int
)paren
id|p
)paren
suffix:semicolon
id|br_timer_init
c_func
(paren
op_amp
id|p-&gt;forward_delay_timer
comma
id|br_forward_delay_timer_expired
comma
(paren
r_int
r_int
)paren
id|p
)paren
suffix:semicolon
id|br_timer_init
c_func
(paren
op_amp
id|p-&gt;hold_timer
comma
id|br_hold_timer_expired
comma
(paren
r_int
r_int
)paren
id|p
)paren
suffix:semicolon
)brace
eof
