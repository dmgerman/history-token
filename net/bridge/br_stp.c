multiline_comment|/*&n; *&t;Spanning tree protocol; generic parts&n; *&t;Linux ethernet bridge&n; *&n; *&t;Authors:&n; *&t;Lennert Buytenhek&t;&t;&lt;buytenh@gnu.org&gt;&n; *&n; *&t;$Id: br_stp.c,v 1.4 2000/06/19 10:13:35 davem Exp $&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License&n; *&t;as published by the Free Software Foundation; either version&n; *&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &quot;br_private.h&quot;
macro_line|#include &quot;br_private_stp.h&quot;
DECL|variable|br_port_state_names
r_static
r_const
r_char
op_star
id|br_port_state_names
(braket
)braket
op_assign
(brace
(braket
id|BR_STATE_DISABLED
)braket
op_assign
l_string|&quot;disabled&quot;
comma
(braket
id|BR_STATE_LISTENING
)braket
op_assign
l_string|&quot;listening&quot;
comma
(braket
id|BR_STATE_LEARNING
)braket
op_assign
l_string|&quot;learning&quot;
comma
(braket
id|BR_STATE_FORWARDING
)braket
op_assign
l_string|&quot;forwarding&quot;
comma
(braket
id|BR_STATE_BLOCKING
)braket
op_assign
l_string|&quot;blocking&quot;
comma
)brace
suffix:semicolon
DECL|function|br_log_state
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
(brace
id|pr_info
c_func
(paren
l_string|&quot;%s: port %d(%s) entering %s state&bslash;n&quot;
comma
id|p-&gt;br-&gt;dev-&gt;name
comma
id|p-&gt;port_no
comma
id|p-&gt;dev-&gt;name
comma
id|br_port_state_names
(braket
id|p-&gt;state
)braket
)paren
suffix:semicolon
)brace
multiline_comment|/* called under bridge lock */
DECL|function|br_get_port
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
(brace
r_struct
id|net_bridge_port
op_star
id|p
suffix:semicolon
id|list_for_each_entry_rcu
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
id|p-&gt;port_no
op_eq
id|port_no
)paren
r_return
id|p
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* called under bridge lock */
DECL|function|br_should_become_root_port
r_static
r_int
id|br_should_become_root_port
c_func
(paren
r_const
r_struct
id|net_bridge_port
op_star
id|p
comma
id|u16
id|root_port
)paren
(brace
r_struct
id|net_bridge
op_star
id|br
suffix:semicolon
r_struct
id|net_bridge_port
op_star
id|rp
suffix:semicolon
r_int
id|t
suffix:semicolon
id|br
op_assign
id|p-&gt;br
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;state
op_eq
id|BR_STATE_DISABLED
op_logical_or
id|br_is_designated_port
c_func
(paren
id|p
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|memcmp
c_func
(paren
op_amp
id|br-&gt;bridge_id
comma
op_amp
id|p-&gt;designated_root
comma
l_int|8
)paren
op_le
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|root_port
)paren
r_return
l_int|1
suffix:semicolon
id|rp
op_assign
id|br_get_port
c_func
(paren
id|br
comma
id|root_port
)paren
suffix:semicolon
id|t
op_assign
id|memcmp
c_func
(paren
op_amp
id|p-&gt;designated_root
comma
op_amp
id|rp-&gt;designated_root
comma
l_int|8
)paren
suffix:semicolon
r_if
c_cond
(paren
id|t
OL
l_int|0
)paren
r_return
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
id|t
OG
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;designated_cost
op_plus
id|p-&gt;path_cost
OL
id|rp-&gt;designated_cost
op_plus
id|rp-&gt;path_cost
)paren
r_return
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
id|p-&gt;designated_cost
op_plus
id|p-&gt;path_cost
OG
id|rp-&gt;designated_cost
op_plus
id|rp-&gt;path_cost
)paren
r_return
l_int|0
suffix:semicolon
id|t
op_assign
id|memcmp
c_func
(paren
op_amp
id|p-&gt;designated_bridge
comma
op_amp
id|rp-&gt;designated_bridge
comma
l_int|8
)paren
suffix:semicolon
r_if
c_cond
(paren
id|t
OL
l_int|0
)paren
r_return
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
id|t
OG
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;designated_port
OL
id|rp-&gt;designated_port
)paren
r_return
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
id|p-&gt;designated_port
OG
id|rp-&gt;designated_port
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;port_id
OL
id|rp-&gt;port_id
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* called under bridge lock */
DECL|function|br_root_selection
r_static
r_void
id|br_root_selection
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
id|u16
id|root_port
op_assign
l_int|0
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
id|br_should_become_root_port
c_func
(paren
id|p
comma
id|root_port
)paren
)paren
id|root_port
op_assign
id|p-&gt;port_no
suffix:semicolon
)brace
id|br-&gt;root_port
op_assign
id|root_port
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|root_port
)paren
(brace
id|br-&gt;designated_root
op_assign
id|br-&gt;bridge_id
suffix:semicolon
id|br-&gt;root_path_cost
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|p
op_assign
id|br_get_port
c_func
(paren
id|br
comma
id|root_port
)paren
suffix:semicolon
id|br-&gt;designated_root
op_assign
id|p-&gt;designated_root
suffix:semicolon
id|br-&gt;root_path_cost
op_assign
id|p-&gt;designated_cost
op_plus
id|p-&gt;path_cost
suffix:semicolon
)brace
)brace
multiline_comment|/* called under bridge lock */
DECL|function|br_become_root_bridge
r_void
id|br_become_root_bridge
c_func
(paren
r_struct
id|net_bridge
op_star
id|br
)paren
(brace
id|br-&gt;max_age
op_assign
id|br-&gt;bridge_max_age
suffix:semicolon
id|br-&gt;hello_time
op_assign
id|br-&gt;bridge_hello_time
suffix:semicolon
id|br-&gt;forward_delay
op_assign
id|br-&gt;bridge_forward_delay
suffix:semicolon
id|br_topology_change_detection
c_func
(paren
id|br
)paren
suffix:semicolon
id|del_timer
c_func
(paren
op_amp
id|br-&gt;tcn_timer
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
)brace
multiline_comment|/* called under bridge lock */
DECL|function|br_transmit_config
r_void
id|br_transmit_config
c_func
(paren
r_struct
id|net_bridge_port
op_star
id|p
)paren
(brace
r_struct
id|br_config_bpdu
id|bpdu
suffix:semicolon
r_struct
id|net_bridge
op_star
id|br
suffix:semicolon
r_if
c_cond
(paren
id|timer_pending
c_func
(paren
op_amp
id|p-&gt;hold_timer
)paren
)paren
(brace
id|p-&gt;config_pending
op_assign
l_int|1
suffix:semicolon
r_return
suffix:semicolon
)brace
id|br
op_assign
id|p-&gt;br
suffix:semicolon
id|bpdu.topology_change
op_assign
id|br-&gt;topology_change
suffix:semicolon
id|bpdu.topology_change_ack
op_assign
id|p-&gt;topology_change_ack
suffix:semicolon
id|bpdu.root
op_assign
id|br-&gt;designated_root
suffix:semicolon
id|bpdu.root_path_cost
op_assign
id|br-&gt;root_path_cost
suffix:semicolon
id|bpdu.bridge_id
op_assign
id|br-&gt;bridge_id
suffix:semicolon
id|bpdu.port_id
op_assign
id|p-&gt;port_id
suffix:semicolon
id|bpdu.message_age
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|br_is_root_bridge
c_func
(paren
id|br
)paren
)paren
(brace
r_struct
id|net_bridge_port
op_star
id|root
op_assign
id|br_get_port
c_func
(paren
id|br
comma
id|br-&gt;root_port
)paren
suffix:semicolon
id|bpdu.max_age
op_assign
id|root-&gt;message_age_timer.expires
op_minus
id|jiffies
suffix:semicolon
r_if
c_cond
(paren
id|bpdu.max_age
op_le
l_int|0
)paren
id|bpdu.max_age
op_assign
l_int|1
suffix:semicolon
)brace
id|bpdu.max_age
op_assign
id|br-&gt;max_age
suffix:semicolon
id|bpdu.hello_time
op_assign
id|br-&gt;hello_time
suffix:semicolon
id|bpdu.forward_delay
op_assign
id|br-&gt;forward_delay
suffix:semicolon
id|br_send_config_bpdu
c_func
(paren
id|p
comma
op_amp
id|bpdu
)paren
suffix:semicolon
id|p-&gt;topology_change_ack
op_assign
l_int|0
suffix:semicolon
id|p-&gt;config_pending
op_assign
l_int|0
suffix:semicolon
id|mod_timer
c_func
(paren
op_amp
id|p-&gt;hold_timer
comma
id|jiffies
op_plus
id|BR_HOLD_TIME
)paren
suffix:semicolon
)brace
multiline_comment|/* called under bridge lock */
DECL|function|br_record_config_information
r_static
r_inline
r_void
id|br_record_config_information
c_func
(paren
r_struct
id|net_bridge_port
op_star
id|p
comma
r_const
r_struct
id|br_config_bpdu
op_star
id|bpdu
)paren
(brace
id|p-&gt;designated_root
op_assign
id|bpdu-&gt;root
suffix:semicolon
id|p-&gt;designated_cost
op_assign
id|bpdu-&gt;root_path_cost
suffix:semicolon
id|p-&gt;designated_bridge
op_assign
id|bpdu-&gt;bridge_id
suffix:semicolon
id|p-&gt;designated_port
op_assign
id|bpdu-&gt;port_id
suffix:semicolon
id|mod_timer
c_func
(paren
op_amp
id|p-&gt;message_age_timer
comma
id|jiffies
op_plus
(paren
id|p-&gt;br-&gt;max_age
op_minus
id|bpdu-&gt;message_age
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* called under bridge lock */
DECL|function|br_record_config_timeout_values
r_static
r_inline
r_void
id|br_record_config_timeout_values
c_func
(paren
r_struct
id|net_bridge
op_star
id|br
comma
r_const
r_struct
id|br_config_bpdu
op_star
id|bpdu
)paren
(brace
id|br-&gt;max_age
op_assign
id|bpdu-&gt;max_age
suffix:semicolon
id|br-&gt;hello_time
op_assign
id|bpdu-&gt;hello_time
suffix:semicolon
id|br-&gt;forward_delay
op_assign
id|bpdu-&gt;forward_delay
suffix:semicolon
id|br-&gt;topology_change
op_assign
id|bpdu-&gt;topology_change
suffix:semicolon
)brace
multiline_comment|/* called under bridge lock */
DECL|function|br_transmit_tcn
r_void
id|br_transmit_tcn
c_func
(paren
r_struct
id|net_bridge
op_star
id|br
)paren
(brace
id|br_send_tcn_bpdu
c_func
(paren
id|br_get_port
c_func
(paren
id|br
comma
id|br-&gt;root_port
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* called under bridge lock */
DECL|function|br_should_become_designated_port
r_static
r_int
id|br_should_become_designated_port
c_func
(paren
r_const
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
id|t
suffix:semicolon
id|br
op_assign
id|p-&gt;br
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
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|memcmp
c_func
(paren
op_amp
id|p-&gt;designated_root
comma
op_amp
id|br-&gt;designated_root
comma
l_int|8
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|br-&gt;root_path_cost
OL
id|p-&gt;designated_cost
)paren
r_return
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
id|br-&gt;root_path_cost
OG
id|p-&gt;designated_cost
)paren
r_return
l_int|0
suffix:semicolon
id|t
op_assign
id|memcmp
c_func
(paren
op_amp
id|br-&gt;bridge_id
comma
op_amp
id|p-&gt;designated_bridge
comma
l_int|8
)paren
suffix:semicolon
r_if
c_cond
(paren
id|t
OL
l_int|0
)paren
r_return
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
id|t
OG
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;port_id
OL
id|p-&gt;designated_port
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* called under bridge lock */
DECL|function|br_designated_port_selection
r_static
r_void
id|br_designated_port_selection
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
id|br_should_become_designated_port
c_func
(paren
id|p
)paren
)paren
id|br_become_designated_port
c_func
(paren
id|p
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* called under bridge lock */
DECL|function|br_supersedes_port_info
r_static
r_int
id|br_supersedes_port_info
c_func
(paren
r_struct
id|net_bridge_port
op_star
id|p
comma
r_struct
id|br_config_bpdu
op_star
id|bpdu
)paren
(brace
r_int
id|t
suffix:semicolon
id|t
op_assign
id|memcmp
c_func
(paren
op_amp
id|bpdu-&gt;root
comma
op_amp
id|p-&gt;designated_root
comma
l_int|8
)paren
suffix:semicolon
r_if
c_cond
(paren
id|t
OL
l_int|0
)paren
r_return
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
id|t
OG
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|bpdu-&gt;root_path_cost
OL
id|p-&gt;designated_cost
)paren
r_return
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
id|bpdu-&gt;root_path_cost
OG
id|p-&gt;designated_cost
)paren
r_return
l_int|0
suffix:semicolon
id|t
op_assign
id|memcmp
c_func
(paren
op_amp
id|bpdu-&gt;bridge_id
comma
op_amp
id|p-&gt;designated_bridge
comma
l_int|8
)paren
suffix:semicolon
r_if
c_cond
(paren
id|t
OL
l_int|0
)paren
r_return
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
id|t
OG
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|memcmp
c_func
(paren
op_amp
id|bpdu-&gt;bridge_id
comma
op_amp
id|p-&gt;br-&gt;bridge_id
comma
l_int|8
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|bpdu-&gt;port_id
op_le
id|p-&gt;designated_port
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* called under bridge lock */
DECL|function|br_topology_change_acknowledged
r_static
r_inline
r_void
id|br_topology_change_acknowledged
c_func
(paren
r_struct
id|net_bridge
op_star
id|br
)paren
(brace
id|br-&gt;topology_change_detected
op_assign
l_int|0
suffix:semicolon
id|del_timer
c_func
(paren
op_amp
id|br-&gt;tcn_timer
)paren
suffix:semicolon
)brace
multiline_comment|/* called under bridge lock */
DECL|function|br_topology_change_detection
r_void
id|br_topology_change_detection
c_func
(paren
r_struct
id|net_bridge
op_star
id|br
)paren
(brace
r_int
id|isroot
op_assign
id|br_is_root_bridge
c_func
(paren
id|br
)paren
suffix:semicolon
id|pr_info
c_func
(paren
l_string|&quot;%s: topology change detected, %s&bslash;n&quot;
comma
id|br-&gt;dev-&gt;name
comma
id|isroot
ques
c_cond
l_string|&quot;propgating&quot;
suffix:colon
l_string|&quot;sending tcn bpdu&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|isroot
)paren
(brace
id|br-&gt;topology_change
op_assign
l_int|1
suffix:semicolon
id|mod_timer
c_func
(paren
op_amp
id|br-&gt;topology_change_timer
comma
id|jiffies
op_plus
id|br-&gt;bridge_forward_delay
op_plus
id|br-&gt;bridge_max_age
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|br-&gt;topology_change_detected
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
id|br-&gt;topology_change_detected
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/* called under bridge lock */
DECL|function|br_config_bpdu_generation
r_void
id|br_config_bpdu_generation
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
id|br_transmit_config
c_func
(paren
id|p
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* called under bridge lock */
DECL|function|br_reply
r_static
r_inline
r_void
id|br_reply
c_func
(paren
r_struct
id|net_bridge_port
op_star
id|p
)paren
(brace
id|br_transmit_config
c_func
(paren
id|p
)paren
suffix:semicolon
)brace
multiline_comment|/* called under bridge lock */
DECL|function|br_configuration_update
r_void
id|br_configuration_update
c_func
(paren
r_struct
id|net_bridge
op_star
id|br
)paren
(brace
id|br_root_selection
c_func
(paren
id|br
)paren
suffix:semicolon
id|br_designated_port_selection
c_func
(paren
id|br
)paren
suffix:semicolon
)brace
multiline_comment|/* called under bridge lock */
DECL|function|br_become_designated_port
r_void
id|br_become_designated_port
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
id|br
op_assign
id|p-&gt;br
suffix:semicolon
id|p-&gt;designated_root
op_assign
id|br-&gt;designated_root
suffix:semicolon
id|p-&gt;designated_cost
op_assign
id|br-&gt;root_path_cost
suffix:semicolon
id|p-&gt;designated_bridge
op_assign
id|br-&gt;bridge_id
suffix:semicolon
id|p-&gt;designated_port
op_assign
id|p-&gt;port_id
suffix:semicolon
)brace
multiline_comment|/* called under bridge lock */
DECL|function|br_make_blocking
r_static
r_void
id|br_make_blocking
c_func
(paren
r_struct
id|net_bridge_port
op_star
id|p
)paren
(brace
r_if
c_cond
(paren
id|p-&gt;state
op_ne
id|BR_STATE_DISABLED
op_logical_and
id|p-&gt;state
op_ne
id|BR_STATE_BLOCKING
)paren
(brace
r_if
c_cond
(paren
id|p-&gt;state
op_eq
id|BR_STATE_FORWARDING
op_logical_or
id|p-&gt;state
op_eq
id|BR_STATE_LEARNING
)paren
id|br_topology_change_detection
c_func
(paren
id|p-&gt;br
)paren
suffix:semicolon
id|p-&gt;state
op_assign
id|BR_STATE_BLOCKING
suffix:semicolon
id|br_log_state
c_func
(paren
id|p
)paren
suffix:semicolon
id|del_timer
c_func
(paren
op_amp
id|p-&gt;forward_delay_timer
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* called under bridge lock */
DECL|function|br_make_forwarding
r_static
r_void
id|br_make_forwarding
c_func
(paren
r_struct
id|net_bridge_port
op_star
id|p
)paren
(brace
r_if
c_cond
(paren
id|p-&gt;state
op_eq
id|BR_STATE_BLOCKING
)paren
(brace
r_if
c_cond
(paren
id|p-&gt;br-&gt;stp_enabled
)paren
(brace
id|p-&gt;state
op_assign
id|BR_STATE_LISTENING
suffix:semicolon
)brace
r_else
(brace
id|p-&gt;state
op_assign
id|BR_STATE_LEARNING
suffix:semicolon
)brace
id|br_log_state
c_func
(paren
id|p
)paren
suffix:semicolon
id|mod_timer
c_func
(paren
op_amp
id|p-&gt;forward_delay_timer
comma
id|jiffies
op_plus
id|p-&gt;br-&gt;forward_delay
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* called under bridge lock */
DECL|function|br_port_state_selection
r_void
id|br_port_state_selection
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
(brace
r_if
c_cond
(paren
id|p-&gt;port_no
op_eq
id|br-&gt;root_port
)paren
(brace
id|p-&gt;config_pending
op_assign
l_int|0
suffix:semicolon
id|p-&gt;topology_change_ack
op_assign
l_int|0
suffix:semicolon
id|br_make_forwarding
c_func
(paren
id|p
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|br_is_designated_port
c_func
(paren
id|p
)paren
)paren
(brace
id|del_timer
c_func
(paren
op_amp
id|p-&gt;message_age_timer
)paren
suffix:semicolon
id|br_make_forwarding
c_func
(paren
id|p
)paren
suffix:semicolon
)brace
r_else
(brace
id|p-&gt;config_pending
op_assign
l_int|0
suffix:semicolon
id|p-&gt;topology_change_ack
op_assign
l_int|0
suffix:semicolon
id|br_make_blocking
c_func
(paren
id|p
)paren
suffix:semicolon
)brace
)brace
)brace
)brace
multiline_comment|/* called under bridge lock */
DECL|function|br_topology_change_acknowledge
r_static
r_inline
r_void
id|br_topology_change_acknowledge
c_func
(paren
r_struct
id|net_bridge_port
op_star
id|p
)paren
(brace
id|p-&gt;topology_change_ack
op_assign
l_int|1
suffix:semicolon
id|br_transmit_config
c_func
(paren
id|p
)paren
suffix:semicolon
)brace
multiline_comment|/* called under bridge lock */
DECL|function|br_received_config_bpdu
r_void
id|br_received_config_bpdu
c_func
(paren
r_struct
id|net_bridge_port
op_star
id|p
comma
r_struct
id|br_config_bpdu
op_star
id|bpdu
)paren
(brace
r_struct
id|net_bridge
op_star
id|br
suffix:semicolon
r_int
id|was_root
suffix:semicolon
id|br
op_assign
id|p-&gt;br
suffix:semicolon
id|was_root
op_assign
id|br_is_root_bridge
c_func
(paren
id|br
)paren
suffix:semicolon
r_if
c_cond
(paren
id|br_supersedes_port_info
c_func
(paren
id|p
comma
id|bpdu
)paren
)paren
(brace
id|br_record_config_information
c_func
(paren
id|p
comma
id|bpdu
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
op_logical_neg
id|br_is_root_bridge
c_func
(paren
id|br
)paren
op_logical_and
id|was_root
)paren
(brace
id|del_timer
c_func
(paren
op_amp
id|br-&gt;hello_timer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|br-&gt;topology_change_detected
)paren
(brace
id|del_timer
c_func
(paren
op_amp
id|br-&gt;topology_change_timer
)paren
suffix:semicolon
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
)brace
r_if
c_cond
(paren
id|p-&gt;port_no
op_eq
id|br-&gt;root_port
)paren
(brace
id|br_record_config_timeout_values
c_func
(paren
id|br
comma
id|bpdu
)paren
suffix:semicolon
id|br_config_bpdu_generation
c_func
(paren
id|br
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bpdu-&gt;topology_change_ack
)paren
id|br_topology_change_acknowledged
c_func
(paren
id|br
)paren
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|br_is_designated_port
c_func
(paren
id|p
)paren
)paren
(brace
id|br_reply
c_func
(paren
id|p
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* called under bridge lock */
DECL|function|br_received_tcn_bpdu
r_void
id|br_received_tcn_bpdu
c_func
(paren
r_struct
id|net_bridge_port
op_star
id|p
)paren
(brace
r_if
c_cond
(paren
id|br_is_designated_port
c_func
(paren
id|p
)paren
)paren
(brace
id|pr_info
c_func
(paren
l_string|&quot;%s: received tcn bpdu on port %i(%s)&bslash;n&quot;
comma
id|p-&gt;br-&gt;dev-&gt;name
comma
id|p-&gt;port_no
comma
id|p-&gt;dev-&gt;name
)paren
suffix:semicolon
id|br_topology_change_detection
c_func
(paren
id|p-&gt;br
)paren
suffix:semicolon
id|br_topology_change_acknowledge
c_func
(paren
id|p
)paren
suffix:semicolon
)brace
)brace
eof
