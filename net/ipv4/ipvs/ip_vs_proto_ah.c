multiline_comment|/*&n; * ip_vs_proto_ah.c:&t;AH IPSec load balancing support for IPVS&n; *&n; * Version:     $Id: ip_vs_proto_ah.c,v 1.1 2003/07/04 15:04:37 wensong Exp $&n; *&n; * Authors:&t;Julian Anastasov &lt;ja@ssi.bg&gt;, February 2002&n; *&t;&t;Wensong Zhang &lt;wensong@linuxvirtualserver.org&gt;&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;version 2 as published by the Free Software Foundation;&n; *&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/netfilter.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4.h&gt;
macro_line|#include &lt;net/ip_vs.h&gt;
multiline_comment|/* TODO:&n;&n;struct isakmp_hdr {&n;&t;__u8&t;&t;icookie[8];&n;&t;__u8&t;&t;rcookie[8];&n;&t;__u8&t;&t;np;&n;&t;__u8&t;&t;version;&n;&t;__u8&t;&t;xchgtype;&n;&t;__u8&t;&t;flags;&n;&t;__u32&t;&t;msgid;&n;&t;__u32&t;&t;length;&n;};&n;&n;*/
DECL|macro|PORT_ISAKMP
mdefine_line|#define PORT_ISAKMP&t;500
r_static
r_struct
id|ip_vs_conn
op_star
DECL|function|ah_conn_in_get
id|ah_conn_in_get
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
id|IPPROTO_UDP
comma
id|iph-&gt;saddr
comma
id|__constant_htons
c_func
(paren
id|PORT_ISAKMP
)paren
comma
id|iph-&gt;daddr
comma
id|__constant_htons
c_func
(paren
id|PORT_ISAKMP
)paren
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
id|IPPROTO_UDP
comma
id|iph-&gt;daddr
comma
id|__constant_htons
c_func
(paren
id|PORT_ISAKMP
)paren
comma
id|iph-&gt;saddr
comma
id|__constant_htons
c_func
(paren
id|PORT_ISAKMP
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|cp
)paren
(brace
multiline_comment|/*&n;&t;&t; * We are not sure if the packet is from our&n;&t;&t; * service, so our conn_schedule hook should return NF_ACCEPT&n;&t;&t; */
id|IP_VS_DBG
c_func
(paren
l_int|12
comma
l_string|&quot;Unknown ISAKMP entry for outin packet &quot;
l_string|&quot;%s%s %u.%u.%u.%u-&gt;%u.%u.%u.%u&bslash;n&quot;
comma
id|inverse
ques
c_cond
l_string|&quot;ICMP+&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|pp-&gt;name
comma
id|NIPQUAD
c_func
(paren
id|iph-&gt;saddr
)paren
comma
id|NIPQUAD
c_func
(paren
id|iph-&gt;daddr
)paren
)paren
suffix:semicolon
)brace
r_return
id|cp
suffix:semicolon
)brace
r_static
r_struct
id|ip_vs_conn
op_star
DECL|function|ah_conn_out_get
id|ah_conn_out_get
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
id|IPPROTO_UDP
comma
id|iph-&gt;saddr
comma
id|__constant_htons
c_func
(paren
id|PORT_ISAKMP
)paren
comma
id|iph-&gt;daddr
comma
id|__constant_htons
c_func
(paren
id|PORT_ISAKMP
)paren
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
id|__constant_htons
c_func
(paren
id|PORT_ISAKMP
)paren
comma
id|iph-&gt;saddr
comma
id|__constant_htons
c_func
(paren
id|PORT_ISAKMP
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|cp
)paren
(brace
id|IP_VS_DBG
c_func
(paren
l_int|12
comma
l_string|&quot;Unknown ISAKMP entry for inout packet &quot;
l_string|&quot;%s%s %u.%u.%u.%u-&gt;%u.%u.%u.%u&bslash;n&quot;
comma
id|inverse
ques
c_cond
l_string|&quot;ICMP+&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|pp-&gt;name
comma
id|NIPQUAD
c_func
(paren
id|iph-&gt;saddr
)paren
comma
id|NIPQUAD
c_func
(paren
id|iph-&gt;daddr
)paren
)paren
suffix:semicolon
)brace
r_return
id|cp
suffix:semicolon
)brace
r_static
r_int
DECL|function|ah_conn_schedule
id|ah_conn_schedule
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
multiline_comment|/*&n;&t; * AH is only related traffic. Pass the packet to IP stack.&n;&t; */
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
r_void
DECL|function|ah_debug_packet
id|ah_debug_packet
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
id|_iph
comma
op_star
id|ih
suffix:semicolon
id|ih
op_assign
id|skb_header_pointer
c_func
(paren
id|skb
comma
id|offset
comma
r_sizeof
(paren
id|_iph
)paren
comma
op_amp
id|_iph
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ih
op_eq
l_int|NULL
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
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%s %u.%u.%u.%u-&gt;%u.%u.%u.%u&quot;
comma
id|pp-&gt;name
comma
id|NIPQUAD
c_func
(paren
id|ih-&gt;saddr
)paren
comma
id|NIPQUAD
c_func
(paren
id|ih-&gt;daddr
)paren
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
DECL|function|ah_init
r_static
r_void
id|ah_init
c_func
(paren
r_struct
id|ip_vs_protocol
op_star
id|pp
)paren
(brace
multiline_comment|/* nothing to do now */
)brace
DECL|function|ah_exit
r_static
r_void
id|ah_exit
c_func
(paren
r_struct
id|ip_vs_protocol
op_star
id|pp
)paren
(brace
multiline_comment|/* nothing to do now */
)brace
DECL|variable|ip_vs_protocol_ah
r_struct
id|ip_vs_protocol
id|ip_vs_protocol_ah
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;AH&quot;
comma
dot
id|protocol
op_assign
id|IPPROTO_AH
comma
dot
id|dont_defrag
op_assign
l_int|1
comma
dot
id|init
op_assign
id|ah_init
comma
dot
m_exit
op_assign
id|ah_exit
comma
dot
id|conn_schedule
op_assign
id|ah_conn_schedule
comma
dot
id|conn_in_get
op_assign
id|ah_conn_in_get
comma
dot
id|conn_out_get
op_assign
id|ah_conn_out_get
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
l_int|NULL
comma
dot
id|state_transition
op_assign
l_int|NULL
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
id|ah_debug_packet
comma
dot
id|timeout_change
op_assign
l_int|NULL
comma
multiline_comment|/* ISAKMP */
dot
id|set_state_timeout
op_assign
l_int|NULL
comma
)brace
suffix:semicolon
eof
