multiline_comment|/*&n; * ip_vs_proto_icmp.c:&t;ICMP load balancing support for IP Virtual Server&n; *&n; * Authors:&t;Julian Anastasov &lt;ja@ssi.bg&gt;, March 2002&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;version 2 as published by the Free Software Foundation;&n; *&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/icmp.h&gt;
macro_line|#include &lt;linux/netfilter.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4.h&gt;
macro_line|#include &lt;net/ip_vs.h&gt;
DECL|variable|icmp_timeouts
r_static
r_int
id|icmp_timeouts
(braket
l_int|1
)braket
op_assign
(brace
l_int|1
op_star
l_int|60
op_star
id|HZ
)brace
suffix:semicolon
DECL|variable|icmp_state_name_table
r_static
r_char
op_star
id|icmp_state_name_table
(braket
l_int|1
)braket
op_assign
(brace
l_string|&quot;ICMP&quot;
)brace
suffix:semicolon
r_struct
id|ip_vs_conn
op_star
DECL|function|icmp_conn_in_get
id|icmp_conn_in_get
c_func
(paren
r_const
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|ip_vs_protocol
op_star
id|pp
comma
r_const
r_struct
id|iphdr
op_star
id|iph
comma
r_int
r_int
id|proto_off
comma
r_int
id|inverse
)paren
(brace
macro_line|#if 0
r_struct
id|ip_vs_conn
op_star
id|cp
suffix:semicolon
r_if
c_cond
(paren
id|likely
c_func
(paren
op_logical_neg
id|inverse
)paren
)paren
(brace
id|cp
op_assign
id|ip_vs_conn_in_get
c_func
(paren
id|iph-&gt;protocol
comma
id|iph-&gt;saddr
comma
l_int|0
comma
id|iph-&gt;daddr
comma
l_int|0
)paren
suffix:semicolon
)brace
r_else
(brace
id|cp
op_assign
id|ip_vs_conn_in_get
c_func
(paren
id|iph-&gt;protocol
comma
id|iph-&gt;daddr
comma
l_int|0
comma
id|iph-&gt;saddr
comma
l_int|0
)paren
suffix:semicolon
)brace
r_return
id|cp
suffix:semicolon
macro_line|#else
r_return
l_int|NULL
suffix:semicolon
macro_line|#endif
)brace
r_struct
id|ip_vs_conn
op_star
DECL|function|icmp_conn_out_get
id|icmp_conn_out_get
c_func
(paren
r_const
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|ip_vs_protocol
op_star
id|pp
comma
r_const
r_struct
id|iphdr
op_star
id|iph
comma
r_int
r_int
id|proto_off
comma
r_int
id|inverse
)paren
(brace
macro_line|#if 0
r_struct
id|ip_vs_conn
op_star
id|cp
suffix:semicolon
r_if
c_cond
(paren
id|likely
c_func
(paren
op_logical_neg
id|inverse
)paren
)paren
(brace
id|cp
op_assign
id|ip_vs_conn_out_get
c_func
(paren
id|iph-&gt;protocol
comma
id|iph-&gt;saddr
comma
l_int|0
comma
id|iph-&gt;daddr
comma
l_int|0
)paren
suffix:semicolon
)brace
r_else
(brace
id|cp
op_assign
id|ip_vs_conn_out_get
c_func
(paren
id|IPPROTO_UDP
comma
id|iph-&gt;daddr
comma
l_int|0
comma
id|iph-&gt;saddr
comma
l_int|0
)paren
suffix:semicolon
)brace
r_return
id|cp
suffix:semicolon
macro_line|#else
r_return
l_int|NULL
suffix:semicolon
macro_line|#endif
)brace
r_static
r_int
DECL|function|icmp_conn_schedule
id|icmp_conn_schedule
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|ip_vs_protocol
op_star
id|pp
comma
r_int
op_star
id|verdict
comma
r_struct
id|ip_vs_conn
op_star
op_star
id|cpp
)paren
(brace
op_star
id|verdict
op_assign
id|NF_ACCEPT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|icmp_csum_check
id|icmp_csum_check
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|ip_vs_protocol
op_star
id|pp
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|skb-&gt;nh.iph-&gt;frag_off
op_amp
id|__constant_htons
c_func
(paren
id|IP_OFFSET
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
id|skb-&gt;ip_summed
op_ne
id|CHECKSUM_UNNECESSARY
)paren
(brace
r_if
c_cond
(paren
id|ip_vs_checksum_complete
c_func
(paren
id|skb
comma
id|skb-&gt;nh.iph-&gt;ihl
op_star
l_int|4
)paren
)paren
(brace
id|IP_VS_DBG_RL_PKT
c_func
(paren
l_int|0
comma
id|pp
comma
id|skb
comma
l_int|0
comma
l_string|&quot;Failed checksum for&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
)brace
r_return
l_int|1
suffix:semicolon
)brace
r_static
r_void
DECL|function|icmp_debug_packet
id|icmp_debug_packet
c_func
(paren
r_struct
id|ip_vs_protocol
op_star
id|pp
comma
r_const
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
id|offset
comma
r_const
r_char
op_star
id|msg
)paren
(brace
r_char
id|buf
(braket
l_int|256
)braket
suffix:semicolon
r_struct
id|iphdr
id|iph
suffix:semicolon
r_struct
id|icmphdr
id|icmph
suffix:semicolon
r_if
c_cond
(paren
id|skb_copy_bits
c_func
(paren
id|skb
comma
id|offset
comma
op_amp
id|iph
comma
r_sizeof
(paren
id|iph
)paren
)paren
OL
l_int|0
)paren
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%s TRUNCATED&quot;
comma
id|pp-&gt;name
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|iph.frag_off
op_amp
id|__constant_htons
c_func
(paren
id|IP_OFFSET
)paren
)paren
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%s %u.%u.%u.%u-&gt;%u.%u.%u.%u frag&quot;
comma
id|pp-&gt;name
comma
id|NIPQUAD
c_func
(paren
id|iph.saddr
)paren
comma
id|NIPQUAD
c_func
(paren
id|iph.daddr
)paren
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|skb_copy_bits
c_func
(paren
id|skb
comma
id|offset
op_plus
id|iph.ihl
op_star
l_int|4
comma
op_amp
id|icmph
comma
r_sizeof
(paren
id|icmph
)paren
)paren
OL
l_int|0
)paren
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%s TRUNCATED to %u bytes&bslash;n&quot;
comma
id|pp-&gt;name
comma
id|skb-&gt;len
op_minus
id|offset
)paren
suffix:semicolon
r_else
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%s %u.%u.%u.%u-&gt;%u.%u.%u.%u T:%d C:%d&quot;
comma
id|pp-&gt;name
comma
id|NIPQUAD
c_func
(paren
id|iph.saddr
)paren
comma
id|NIPQUAD
c_func
(paren
id|iph.daddr
)paren
comma
id|icmph.type
comma
id|icmph.code
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;IPVS: %s: %s&bslash;n&quot;
comma
id|msg
comma
id|buf
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|icmp_state_transition
id|icmp_state_transition
c_func
(paren
r_struct
id|ip_vs_conn
op_star
id|cp
comma
r_int
id|direction
comma
r_const
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|ip_vs_protocol
op_star
id|pp
)paren
(brace
id|cp-&gt;timeout
op_assign
id|pp-&gt;timeout_table
(braket
id|IP_VS_ICMP_S_NORMAL
)braket
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_static
r_int
DECL|function|icmp_set_state_timeout
id|icmp_set_state_timeout
c_func
(paren
r_struct
id|ip_vs_protocol
op_star
id|pp
comma
r_char
op_star
id|sname
comma
r_int
id|to
)paren
(brace
r_int
id|num
suffix:semicolon
r_char
op_star
op_star
id|names
suffix:semicolon
id|num
op_assign
id|IP_VS_ICMP_S_LAST
suffix:semicolon
id|names
op_assign
id|icmp_state_name_table
suffix:semicolon
r_return
id|ip_vs_set_state_timeout
c_func
(paren
id|pp-&gt;timeout_table
comma
id|num
comma
id|names
comma
id|sname
comma
id|to
)paren
suffix:semicolon
)brace
DECL|function|icmp_init
r_static
r_void
id|icmp_init
c_func
(paren
r_struct
id|ip_vs_protocol
op_star
id|pp
)paren
(brace
id|pp-&gt;timeout_table
op_assign
id|icmp_timeouts
suffix:semicolon
)brace
DECL|function|icmp_exit
r_static
r_void
id|icmp_exit
c_func
(paren
r_struct
id|ip_vs_protocol
op_star
id|pp
)paren
(brace
)brace
DECL|variable|ip_vs_protocol_icmp
r_struct
id|ip_vs_protocol
id|ip_vs_protocol_icmp
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;ICMP&quot;
comma
dot
id|protocol
op_assign
id|IPPROTO_ICMP
comma
dot
id|dont_defrag
op_assign
l_int|0
comma
dot
id|init
op_assign
id|icmp_init
comma
dot
m_exit
op_assign
id|icmp_exit
comma
dot
id|conn_schedule
op_assign
id|icmp_conn_schedule
comma
dot
id|conn_in_get
op_assign
id|icmp_conn_in_get
comma
dot
id|conn_out_get
op_assign
id|icmp_conn_out_get
comma
dot
id|snat_handler
op_assign
l_int|NULL
comma
dot
id|dnat_handler
op_assign
l_int|NULL
comma
dot
id|csum_check
op_assign
id|icmp_csum_check
comma
dot
id|state_transition
op_assign
id|icmp_state_transition
comma
dot
id|register_app
op_assign
l_int|NULL
comma
dot
id|unregister_app
op_assign
l_int|NULL
comma
dot
id|app_conn_bind
op_assign
l_int|NULL
comma
dot
id|debug_packet
op_assign
id|icmp_debug_packet
comma
dot
id|timeout_change
op_assign
l_int|NULL
comma
dot
id|set_state_timeout
op_assign
id|icmp_set_state_timeout
comma
)brace
suffix:semicolon
eof
