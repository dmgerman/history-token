multiline_comment|/*&n; * ip_vs_proto_tcp.c:&t;TCP load balancing support for IPVS&n; *&n; * Version:     $Id: ip_vs_proto_tcp.c,v 1.3 2002/11/30 01:50:35 wensong Exp $&n; *&n; * Authors:     Wensong Zhang &lt;wensong@linuxvirtualserver.org&gt;&n; *              Julian Anastasov &lt;ja@ssi.bg&gt;&n; *&n; *              This program is free software; you can redistribute it and/or&n; *              modify it under the terms of the GNU General Public License&n; *              as published by the Free Software Foundation; either version&n; *              2 of the License, or (at your option) any later version.&n; *&n; * Changes:&n; *&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/ip.h&gt;
macro_line|#include &lt;linux/tcp.h&gt;                  /* for tcphdr */
macro_line|#include &lt;net/ip.h&gt;
macro_line|#include &lt;net/tcp.h&gt;                    /* for csum_tcpudp_magic */
macro_line|#include &lt;linux/netfilter_ipv4.h&gt;
macro_line|#include &lt;net/ip_vs.h&gt;
r_static
r_struct
id|ip_vs_conn
op_star
DECL|function|tcp_conn_in_get
id|tcp_conn_in_get
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
id|__u16
id|_ports
(braket
l_int|2
)braket
comma
op_star
id|pptr
suffix:semicolon
id|pptr
op_assign
id|skb_header_pointer
c_func
(paren
id|skb
comma
id|proto_off
comma
r_sizeof
(paren
id|_ports
)paren
comma
id|_ports
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pptr
op_eq
l_int|NULL
)paren
r_return
l_int|NULL
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
r_return
id|ip_vs_conn_in_get
c_func
(paren
id|iph-&gt;protocol
comma
id|iph-&gt;saddr
comma
id|pptr
(braket
l_int|0
)braket
comma
id|iph-&gt;daddr
comma
id|pptr
(braket
l_int|1
)braket
)paren
suffix:semicolon
)brace
r_else
(brace
r_return
id|ip_vs_conn_in_get
c_func
(paren
id|iph-&gt;protocol
comma
id|iph-&gt;daddr
comma
id|pptr
(braket
l_int|1
)braket
comma
id|iph-&gt;saddr
comma
id|pptr
(braket
l_int|0
)braket
)paren
suffix:semicolon
)brace
)brace
r_static
r_struct
id|ip_vs_conn
op_star
DECL|function|tcp_conn_out_get
id|tcp_conn_out_get
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
id|__u16
id|_ports
(braket
l_int|2
)braket
comma
op_star
id|pptr
suffix:semicolon
id|pptr
op_assign
id|skb_header_pointer
c_func
(paren
id|skb
comma
id|proto_off
comma
r_sizeof
(paren
id|_ports
)paren
comma
id|_ports
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pptr
op_eq
l_int|NULL
)paren
r_return
l_int|NULL
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
r_return
id|ip_vs_conn_out_get
c_func
(paren
id|iph-&gt;protocol
comma
id|iph-&gt;saddr
comma
id|pptr
(braket
l_int|0
)braket
comma
id|iph-&gt;daddr
comma
id|pptr
(braket
l_int|1
)braket
)paren
suffix:semicolon
)brace
r_else
(brace
r_return
id|ip_vs_conn_out_get
c_func
(paren
id|iph-&gt;protocol
comma
id|iph-&gt;daddr
comma
id|pptr
(braket
l_int|1
)braket
comma
id|iph-&gt;saddr
comma
id|pptr
(braket
l_int|0
)braket
)paren
suffix:semicolon
)brace
)brace
r_static
r_int
DECL|function|tcp_conn_schedule
id|tcp_conn_schedule
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
r_struct
id|ip_vs_service
op_star
id|svc
suffix:semicolon
r_struct
id|tcphdr
id|_tcph
comma
op_star
id|th
suffix:semicolon
id|th
op_assign
id|skb_header_pointer
c_func
(paren
id|skb
comma
id|skb-&gt;nh.iph-&gt;ihl
op_star
l_int|4
comma
r_sizeof
(paren
id|_tcph
)paren
comma
op_amp
id|_tcph
)paren
suffix:semicolon
r_if
c_cond
(paren
id|th
op_eq
l_int|NULL
)paren
(brace
op_star
id|verdict
op_assign
id|NF_DROP
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|th-&gt;syn
op_logical_and
(paren
id|svc
op_assign
id|ip_vs_service_get
c_func
(paren
id|skb-&gt;nfmark
comma
id|skb-&gt;nh.iph-&gt;protocol
comma
id|skb-&gt;nh.iph-&gt;daddr
comma
id|th-&gt;dest
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
id|ip_vs_todrop
c_func
(paren
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * It seems that we are very loaded.&n;&t;&t;&t; * We have to drop this packet :(&n;&t;&t;&t; */
id|ip_vs_service_put
c_func
(paren
id|svc
)paren
suffix:semicolon
op_star
id|verdict
op_assign
id|NF_DROP
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Let the virtual server select a real server for the&n;&t;&t; * incoming connection, and create a connection entry.&n;&t;&t; */
op_star
id|cpp
op_assign
id|ip_vs_schedule
c_func
(paren
id|svc
comma
id|skb
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|cpp
)paren
(brace
op_star
id|verdict
op_assign
id|ip_vs_leave
c_func
(paren
id|svc
comma
id|skb
comma
id|pp
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|ip_vs_service_put
c_func
(paren
id|svc
)paren
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|tcp_fast_csum_update
id|tcp_fast_csum_update
c_func
(paren
r_struct
id|tcphdr
op_star
id|tcph
comma
id|u32
id|oldip
comma
id|u32
id|newip
comma
id|u16
id|oldport
comma
id|u16
id|newport
)paren
(brace
id|tcph-&gt;check
op_assign
id|ip_vs_check_diff
c_func
(paren
op_complement
id|oldip
comma
id|newip
comma
id|ip_vs_check_diff
c_func
(paren
id|oldport
op_xor
l_int|0xFFFF
comma
id|newport
comma
id|tcph-&gt;check
)paren
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|tcp_snat_handler
id|tcp_snat_handler
c_func
(paren
r_struct
id|sk_buff
op_star
op_star
id|pskb
comma
r_struct
id|ip_vs_protocol
op_star
id|pp
comma
r_struct
id|ip_vs_conn
op_star
id|cp
)paren
(brace
r_struct
id|tcphdr
op_star
id|tcph
suffix:semicolon
r_int
r_int
id|tcphoff
op_assign
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nh.iph-&gt;ihl
op_star
l_int|4
suffix:semicolon
multiline_comment|/* csum_check requires unshared skb */
r_if
c_cond
(paren
op_logical_neg
id|ip_vs_make_skb_writable
c_func
(paren
id|pskb
comma
id|tcphoff
op_plus
r_sizeof
(paren
op_star
id|tcph
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|cp-&gt;app
op_ne
l_int|NULL
)paren
)paren
(brace
multiline_comment|/* Some checks before mangling */
r_if
c_cond
(paren
id|pp-&gt;csum_check
op_logical_and
op_logical_neg
id|pp
op_member_access_from_pointer
id|csum_check
c_func
(paren
op_star
id|pskb
comma
id|pp
)paren
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Call application helper if needed */
r_if
c_cond
(paren
op_logical_neg
id|ip_vs_app_pkt_out
c_func
(paren
id|cp
comma
id|pskb
)paren
)paren
r_return
l_int|0
suffix:semicolon
)brace
id|tcph
op_assign
(paren
r_void
op_star
)paren
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nh.iph
op_plus
id|tcphoff
suffix:semicolon
id|tcph-&gt;source
op_assign
id|cp-&gt;vport
suffix:semicolon
multiline_comment|/* Adjust TCP checksums */
r_if
c_cond
(paren
op_logical_neg
id|cp-&gt;app
)paren
(brace
multiline_comment|/* Only port and addr are changed, do fast csum update */
id|tcp_fast_csum_update
c_func
(paren
id|tcph
comma
id|cp-&gt;daddr
comma
id|cp-&gt;vaddr
comma
id|cp-&gt;dport
comma
id|cp-&gt;vport
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|ip_summed
op_eq
id|CHECKSUM_HW
)paren
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|ip_summed
op_assign
id|CHECKSUM_NONE
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* full checksum calculation */
id|tcph-&gt;check
op_assign
l_int|0
suffix:semicolon
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|csum
op_assign
id|skb_checksum
c_func
(paren
op_star
id|pskb
comma
id|tcphoff
comma
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|len
op_minus
id|tcphoff
comma
l_int|0
)paren
suffix:semicolon
id|tcph-&gt;check
op_assign
id|csum_tcpudp_magic
c_func
(paren
id|cp-&gt;vaddr
comma
id|cp-&gt;caddr
comma
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|len
op_minus
id|tcphoff
comma
id|cp-&gt;protocol
comma
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|csum
)paren
suffix:semicolon
id|IP_VS_DBG
c_func
(paren
l_int|11
comma
l_string|&quot;O-pkt: %s O-csum=%d (+%zd)&bslash;n&quot;
comma
id|pp-&gt;name
comma
id|tcph-&gt;check
comma
(paren
r_char
op_star
)paren
op_amp
(paren
id|tcph-&gt;check
)paren
op_minus
(paren
r_char
op_star
)paren
id|tcph
)paren
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
r_static
r_int
DECL|function|tcp_dnat_handler
id|tcp_dnat_handler
c_func
(paren
r_struct
id|sk_buff
op_star
op_star
id|pskb
comma
r_struct
id|ip_vs_protocol
op_star
id|pp
comma
r_struct
id|ip_vs_conn
op_star
id|cp
)paren
(brace
r_struct
id|tcphdr
op_star
id|tcph
suffix:semicolon
r_int
r_int
id|tcphoff
op_assign
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nh.iph-&gt;ihl
op_star
l_int|4
suffix:semicolon
multiline_comment|/* csum_check requires unshared skb */
r_if
c_cond
(paren
op_logical_neg
id|ip_vs_make_skb_writable
c_func
(paren
id|pskb
comma
id|tcphoff
op_plus
r_sizeof
(paren
op_star
id|tcph
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|cp-&gt;app
op_ne
l_int|NULL
)paren
)paren
(brace
multiline_comment|/* Some checks before mangling */
r_if
c_cond
(paren
id|pp-&gt;csum_check
op_logical_and
op_logical_neg
id|pp
op_member_access_from_pointer
id|csum_check
c_func
(paren
op_star
id|pskb
comma
id|pp
)paren
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t;&t; *&t;Attempt ip_vs_app call.&n;&t;&t; *&t;It will fix ip_vs_conn and iph ack_seq stuff&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|ip_vs_app_pkt_in
c_func
(paren
id|cp
comma
id|pskb
)paren
)paren
r_return
l_int|0
suffix:semicolon
)brace
id|tcph
op_assign
(paren
r_void
op_star
)paren
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nh.iph
op_plus
id|tcphoff
suffix:semicolon
id|tcph-&gt;dest
op_assign
id|cp-&gt;dport
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Adjust TCP checksums&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|cp-&gt;app
)paren
(brace
multiline_comment|/* Only port and addr are changed, do fast csum update */
id|tcp_fast_csum_update
c_func
(paren
id|tcph
comma
id|cp-&gt;vaddr
comma
id|cp-&gt;daddr
comma
id|cp-&gt;vport
comma
id|cp-&gt;dport
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|ip_summed
op_eq
id|CHECKSUM_HW
)paren
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|ip_summed
op_assign
id|CHECKSUM_NONE
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* full checksum calculation */
id|tcph-&gt;check
op_assign
l_int|0
suffix:semicolon
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|csum
op_assign
id|skb_checksum
c_func
(paren
op_star
id|pskb
comma
id|tcphoff
comma
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|len
op_minus
id|tcphoff
comma
l_int|0
)paren
suffix:semicolon
id|tcph-&gt;check
op_assign
id|csum_tcpudp_magic
c_func
(paren
id|cp-&gt;caddr
comma
id|cp-&gt;daddr
comma
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|len
op_minus
id|tcphoff
comma
id|cp-&gt;protocol
comma
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|csum
)paren
suffix:semicolon
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|ip_summed
op_assign
id|CHECKSUM_UNNECESSARY
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
r_static
r_int
DECL|function|tcp_csum_check
id|tcp_csum_check
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
r_int
r_int
id|tcphoff
op_assign
id|skb-&gt;nh.iph-&gt;ihl
op_star
l_int|4
suffix:semicolon
r_switch
c_cond
(paren
id|skb-&gt;ip_summed
)paren
(brace
r_case
id|CHECKSUM_NONE
suffix:colon
id|skb-&gt;csum
op_assign
id|skb_checksum
c_func
(paren
id|skb
comma
id|tcphoff
comma
id|skb-&gt;len
op_minus
id|tcphoff
comma
l_int|0
)paren
suffix:semicolon
r_case
id|CHECKSUM_HW
suffix:colon
r_if
c_cond
(paren
id|csum_tcpudp_magic
c_func
(paren
id|skb-&gt;nh.iph-&gt;saddr
comma
id|skb-&gt;nh.iph-&gt;daddr
comma
id|skb-&gt;len
op_minus
id|tcphoff
comma
id|skb-&gt;nh.iph-&gt;protocol
comma
id|skb-&gt;csum
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
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* CHECKSUM_UNNECESSARY */
r_break
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|macro|TCP_DIR_INPUT
mdefine_line|#define TCP_DIR_INPUT&t;&t;0
DECL|macro|TCP_DIR_OUTPUT
mdefine_line|#define TCP_DIR_OUTPUT&t;&t;4
DECL|macro|TCP_DIR_INPUT_ONLY
mdefine_line|#define TCP_DIR_INPUT_ONLY&t;8
DECL|variable|tcp_state_off
r_static
r_int
id|tcp_state_off
(braket
id|IP_VS_DIR_LAST
)braket
op_assign
(brace
(braket
id|IP_VS_DIR_INPUT
)braket
op_assign
id|TCP_DIR_INPUT
comma
(braket
id|IP_VS_DIR_OUTPUT
)braket
op_assign
id|TCP_DIR_OUTPUT
comma
(braket
id|IP_VS_DIR_INPUT_ONLY
)braket
op_assign
id|TCP_DIR_INPUT_ONLY
comma
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;Timeout table[state]&n; */
DECL|variable|tcp_timeouts
r_static
r_int
id|tcp_timeouts
(braket
id|IP_VS_TCP_S_LAST
op_plus
l_int|1
)braket
op_assign
(brace
(braket
id|IP_VS_TCP_S_NONE
)braket
op_assign
l_int|2
op_star
id|HZ
comma
(braket
id|IP_VS_TCP_S_ESTABLISHED
)braket
op_assign
l_int|15
op_star
l_int|60
op_star
id|HZ
comma
(braket
id|IP_VS_TCP_S_SYN_SENT
)braket
op_assign
l_int|2
op_star
l_int|60
op_star
id|HZ
comma
(braket
id|IP_VS_TCP_S_SYN_RECV
)braket
op_assign
l_int|1
op_star
l_int|60
op_star
id|HZ
comma
(braket
id|IP_VS_TCP_S_FIN_WAIT
)braket
op_assign
l_int|2
op_star
l_int|60
op_star
id|HZ
comma
(braket
id|IP_VS_TCP_S_TIME_WAIT
)braket
op_assign
l_int|2
op_star
l_int|60
op_star
id|HZ
comma
(braket
id|IP_VS_TCP_S_CLOSE
)braket
op_assign
l_int|10
op_star
id|HZ
comma
(braket
id|IP_VS_TCP_S_CLOSE_WAIT
)braket
op_assign
l_int|60
op_star
id|HZ
comma
(braket
id|IP_VS_TCP_S_LAST_ACK
)braket
op_assign
l_int|30
op_star
id|HZ
comma
(braket
id|IP_VS_TCP_S_LISTEN
)braket
op_assign
l_int|2
op_star
l_int|60
op_star
id|HZ
comma
(braket
id|IP_VS_TCP_S_SYNACK
)braket
op_assign
l_int|120
op_star
id|HZ
comma
(braket
id|IP_VS_TCP_S_LAST
)braket
op_assign
l_int|2
op_star
id|HZ
comma
)brace
suffix:semicolon
macro_line|#if 0
multiline_comment|/* FIXME: This is going to die */
r_static
r_int
id|tcp_timeouts_dos
(braket
id|IP_VS_TCP_S_LAST
op_plus
l_int|1
)braket
op_assign
(brace
(braket
id|IP_VS_TCP_S_NONE
)braket
op_assign
l_int|2
op_star
id|HZ
comma
(braket
id|IP_VS_TCP_S_ESTABLISHED
)braket
op_assign
l_int|8
op_star
l_int|60
op_star
id|HZ
comma
(braket
id|IP_VS_TCP_S_SYN_SENT
)braket
op_assign
l_int|60
op_star
id|HZ
comma
(braket
id|IP_VS_TCP_S_SYN_RECV
)braket
op_assign
l_int|10
op_star
id|HZ
comma
(braket
id|IP_VS_TCP_S_FIN_WAIT
)braket
op_assign
l_int|60
op_star
id|HZ
comma
(braket
id|IP_VS_TCP_S_TIME_WAIT
)braket
op_assign
l_int|60
op_star
id|HZ
comma
(braket
id|IP_VS_TCP_S_CLOSE
)braket
op_assign
l_int|10
op_star
id|HZ
comma
(braket
id|IP_VS_TCP_S_CLOSE_WAIT
)braket
op_assign
l_int|60
op_star
id|HZ
comma
(braket
id|IP_VS_TCP_S_LAST_ACK
)braket
op_assign
l_int|30
op_star
id|HZ
comma
(braket
id|IP_VS_TCP_S_LISTEN
)braket
op_assign
l_int|2
op_star
l_int|60
op_star
id|HZ
comma
(braket
id|IP_VS_TCP_S_SYNACK
)braket
op_assign
l_int|100
op_star
id|HZ
comma
(braket
id|IP_VS_TCP_S_LAST
)braket
op_assign
l_int|2
op_star
id|HZ
comma
)brace
suffix:semicolon
macro_line|#endif
DECL|variable|tcp_state_name_table
r_static
r_char
op_star
id|tcp_state_name_table
(braket
id|IP_VS_TCP_S_LAST
op_plus
l_int|1
)braket
op_assign
(brace
(braket
id|IP_VS_TCP_S_NONE
)braket
op_assign
l_string|&quot;NONE&quot;
comma
(braket
id|IP_VS_TCP_S_ESTABLISHED
)braket
op_assign
l_string|&quot;ESTABLISHED&quot;
comma
(braket
id|IP_VS_TCP_S_SYN_SENT
)braket
op_assign
l_string|&quot;SYN_SENT&quot;
comma
(braket
id|IP_VS_TCP_S_SYN_RECV
)braket
op_assign
l_string|&quot;SYN_RECV&quot;
comma
(braket
id|IP_VS_TCP_S_FIN_WAIT
)braket
op_assign
l_string|&quot;FIN_WAIT&quot;
comma
(braket
id|IP_VS_TCP_S_TIME_WAIT
)braket
op_assign
l_string|&quot;TIME_WAIT&quot;
comma
(braket
id|IP_VS_TCP_S_CLOSE
)braket
op_assign
l_string|&quot;CLOSE&quot;
comma
(braket
id|IP_VS_TCP_S_CLOSE_WAIT
)braket
op_assign
l_string|&quot;CLOSE_WAIT&quot;
comma
(braket
id|IP_VS_TCP_S_LAST_ACK
)braket
op_assign
l_string|&quot;LAST_ACK&quot;
comma
(braket
id|IP_VS_TCP_S_LISTEN
)braket
op_assign
l_string|&quot;LISTEN&quot;
comma
(braket
id|IP_VS_TCP_S_SYNACK
)braket
op_assign
l_string|&quot;SYNACK&quot;
comma
(braket
id|IP_VS_TCP_S_LAST
)braket
op_assign
l_string|&quot;BUG!&quot;
comma
)brace
suffix:semicolon
DECL|macro|sNO
mdefine_line|#define sNO IP_VS_TCP_S_NONE
DECL|macro|sES
mdefine_line|#define sES IP_VS_TCP_S_ESTABLISHED
DECL|macro|sSS
mdefine_line|#define sSS IP_VS_TCP_S_SYN_SENT
DECL|macro|sSR
mdefine_line|#define sSR IP_VS_TCP_S_SYN_RECV
DECL|macro|sFW
mdefine_line|#define sFW IP_VS_TCP_S_FIN_WAIT
DECL|macro|sTW
mdefine_line|#define sTW IP_VS_TCP_S_TIME_WAIT
DECL|macro|sCL
mdefine_line|#define sCL IP_VS_TCP_S_CLOSE
DECL|macro|sCW
mdefine_line|#define sCW IP_VS_TCP_S_CLOSE_WAIT
DECL|macro|sLA
mdefine_line|#define sLA IP_VS_TCP_S_LAST_ACK
DECL|macro|sLI
mdefine_line|#define sLI IP_VS_TCP_S_LISTEN
DECL|macro|sSA
mdefine_line|#define sSA IP_VS_TCP_S_SYNACK
DECL|struct|tcp_states_t
r_struct
id|tcp_states_t
(brace
DECL|member|next_state
r_int
id|next_state
(braket
id|IP_VS_TCP_S_LAST
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|function|tcp_state_name
r_static
r_const
r_char
op_star
id|tcp_state_name
c_func
(paren
r_int
id|state
)paren
(brace
r_if
c_cond
(paren
id|state
op_ge
id|IP_VS_TCP_S_LAST
)paren
r_return
l_string|&quot;ERR!&quot;
suffix:semicolon
r_return
id|tcp_state_name_table
(braket
id|state
)braket
ques
c_cond
id|tcp_state_name_table
(braket
id|state
)braket
suffix:colon
l_string|&quot;?&quot;
suffix:semicolon
)brace
DECL|variable|tcp_states
r_static
r_struct
id|tcp_states_t
id|tcp_states
(braket
)braket
op_assign
(brace
multiline_comment|/*&t;INPUT */
multiline_comment|/*        sNO, sES, sSS, sSR, sFW, sTW, sCL, sCW, sLA, sLI, sSA&t;*/
multiline_comment|/*syn*/
(brace
(brace
id|sSR
comma
id|sES
comma
id|sES
comma
id|sSR
comma
id|sSR
comma
id|sSR
comma
id|sSR
comma
id|sSR
comma
id|sSR
comma
id|sSR
comma
id|sSR
)brace
)brace
comma
multiline_comment|/*fin*/
(brace
(brace
id|sCL
comma
id|sCW
comma
id|sSS
comma
id|sTW
comma
id|sTW
comma
id|sTW
comma
id|sCL
comma
id|sCW
comma
id|sLA
comma
id|sLI
comma
id|sTW
)brace
)brace
comma
multiline_comment|/*ack*/
(brace
(brace
id|sCL
comma
id|sES
comma
id|sSS
comma
id|sES
comma
id|sFW
comma
id|sTW
comma
id|sCL
comma
id|sCW
comma
id|sCL
comma
id|sLI
comma
id|sES
)brace
)brace
comma
multiline_comment|/*rst*/
(brace
(brace
id|sCL
comma
id|sCL
comma
id|sCL
comma
id|sSR
comma
id|sCL
comma
id|sCL
comma
id|sCL
comma
id|sCL
comma
id|sLA
comma
id|sLI
comma
id|sSR
)brace
)brace
comma
multiline_comment|/*&t;OUTPUT */
multiline_comment|/*        sNO, sES, sSS, sSR, sFW, sTW, sCL, sCW, sLA, sLI, sSA&t;*/
multiline_comment|/*syn*/
(brace
(brace
id|sSS
comma
id|sES
comma
id|sSS
comma
id|sSR
comma
id|sSS
comma
id|sSS
comma
id|sSS
comma
id|sSS
comma
id|sSS
comma
id|sLI
comma
id|sSR
)brace
)brace
comma
multiline_comment|/*fin*/
(brace
(brace
id|sTW
comma
id|sFW
comma
id|sSS
comma
id|sTW
comma
id|sFW
comma
id|sTW
comma
id|sCL
comma
id|sTW
comma
id|sLA
comma
id|sLI
comma
id|sTW
)brace
)brace
comma
multiline_comment|/*ack*/
(brace
(brace
id|sES
comma
id|sES
comma
id|sSS
comma
id|sES
comma
id|sFW
comma
id|sTW
comma
id|sCL
comma
id|sCW
comma
id|sLA
comma
id|sES
comma
id|sES
)brace
)brace
comma
multiline_comment|/*rst*/
(brace
(brace
id|sCL
comma
id|sCL
comma
id|sSS
comma
id|sCL
comma
id|sCL
comma
id|sTW
comma
id|sCL
comma
id|sCL
comma
id|sCL
comma
id|sCL
comma
id|sCL
)brace
)brace
comma
multiline_comment|/*&t;INPUT-ONLY */
multiline_comment|/*        sNO, sES, sSS, sSR, sFW, sTW, sCL, sCW, sLA, sLI, sSA&t;*/
multiline_comment|/*syn*/
(brace
(brace
id|sSR
comma
id|sES
comma
id|sES
comma
id|sSR
comma
id|sSR
comma
id|sSR
comma
id|sSR
comma
id|sSR
comma
id|sSR
comma
id|sSR
comma
id|sSR
)brace
)brace
comma
multiline_comment|/*fin*/
(brace
(brace
id|sCL
comma
id|sFW
comma
id|sSS
comma
id|sTW
comma
id|sFW
comma
id|sTW
comma
id|sCL
comma
id|sCW
comma
id|sLA
comma
id|sLI
comma
id|sTW
)brace
)brace
comma
multiline_comment|/*ack*/
(brace
(brace
id|sCL
comma
id|sES
comma
id|sSS
comma
id|sES
comma
id|sFW
comma
id|sTW
comma
id|sCL
comma
id|sCW
comma
id|sCL
comma
id|sLI
comma
id|sES
)brace
)brace
comma
multiline_comment|/*rst*/
(brace
(brace
id|sCL
comma
id|sCL
comma
id|sCL
comma
id|sSR
comma
id|sCL
comma
id|sCL
comma
id|sCL
comma
id|sCL
comma
id|sLA
comma
id|sLI
comma
id|sCL
)brace
)brace
comma
)brace
suffix:semicolon
DECL|variable|tcp_states_dos
r_static
r_struct
id|tcp_states_t
id|tcp_states_dos
(braket
)braket
op_assign
(brace
multiline_comment|/*&t;INPUT */
multiline_comment|/*        sNO, sES, sSS, sSR, sFW, sTW, sCL, sCW, sLA, sLI, sSA&t;*/
multiline_comment|/*syn*/
(brace
(brace
id|sSR
comma
id|sES
comma
id|sES
comma
id|sSR
comma
id|sSR
comma
id|sSR
comma
id|sSR
comma
id|sSR
comma
id|sSR
comma
id|sSR
comma
id|sSA
)brace
)brace
comma
multiline_comment|/*fin*/
(brace
(brace
id|sCL
comma
id|sCW
comma
id|sSS
comma
id|sTW
comma
id|sTW
comma
id|sTW
comma
id|sCL
comma
id|sCW
comma
id|sLA
comma
id|sLI
comma
id|sSA
)brace
)brace
comma
multiline_comment|/*ack*/
(brace
(brace
id|sCL
comma
id|sES
comma
id|sSS
comma
id|sSR
comma
id|sFW
comma
id|sTW
comma
id|sCL
comma
id|sCW
comma
id|sCL
comma
id|sLI
comma
id|sSA
)brace
)brace
comma
multiline_comment|/*rst*/
(brace
(brace
id|sCL
comma
id|sCL
comma
id|sCL
comma
id|sSR
comma
id|sCL
comma
id|sCL
comma
id|sCL
comma
id|sCL
comma
id|sLA
comma
id|sLI
comma
id|sCL
)brace
)brace
comma
multiline_comment|/*&t;OUTPUT */
multiline_comment|/*        sNO, sES, sSS, sSR, sFW, sTW, sCL, sCW, sLA, sLI, sSA&t;*/
multiline_comment|/*syn*/
(brace
(brace
id|sSS
comma
id|sES
comma
id|sSS
comma
id|sSA
comma
id|sSS
comma
id|sSS
comma
id|sSS
comma
id|sSS
comma
id|sSS
comma
id|sLI
comma
id|sSA
)brace
)brace
comma
multiline_comment|/*fin*/
(brace
(brace
id|sTW
comma
id|sFW
comma
id|sSS
comma
id|sTW
comma
id|sFW
comma
id|sTW
comma
id|sCL
comma
id|sTW
comma
id|sLA
comma
id|sLI
comma
id|sTW
)brace
)brace
comma
multiline_comment|/*ack*/
(brace
(brace
id|sES
comma
id|sES
comma
id|sSS
comma
id|sES
comma
id|sFW
comma
id|sTW
comma
id|sCL
comma
id|sCW
comma
id|sLA
comma
id|sES
comma
id|sES
)brace
)brace
comma
multiline_comment|/*rst*/
(brace
(brace
id|sCL
comma
id|sCL
comma
id|sSS
comma
id|sCL
comma
id|sCL
comma
id|sTW
comma
id|sCL
comma
id|sCL
comma
id|sCL
comma
id|sCL
comma
id|sCL
)brace
)brace
comma
multiline_comment|/*&t;INPUT-ONLY */
multiline_comment|/*        sNO, sES, sSS, sSR, sFW, sTW, sCL, sCW, sLA, sLI, sSA&t;*/
multiline_comment|/*syn*/
(brace
(brace
id|sSA
comma
id|sES
comma
id|sES
comma
id|sSR
comma
id|sSA
comma
id|sSA
comma
id|sSA
comma
id|sSA
comma
id|sSA
comma
id|sSA
comma
id|sSA
)brace
)brace
comma
multiline_comment|/*fin*/
(brace
(brace
id|sCL
comma
id|sFW
comma
id|sSS
comma
id|sTW
comma
id|sFW
comma
id|sTW
comma
id|sCL
comma
id|sCW
comma
id|sLA
comma
id|sLI
comma
id|sTW
)brace
)brace
comma
multiline_comment|/*ack*/
(brace
(brace
id|sCL
comma
id|sES
comma
id|sSS
comma
id|sES
comma
id|sFW
comma
id|sTW
comma
id|sCL
comma
id|sCW
comma
id|sCL
comma
id|sLI
comma
id|sES
)brace
)brace
comma
multiline_comment|/*rst*/
(brace
(brace
id|sCL
comma
id|sCL
comma
id|sCL
comma
id|sSR
comma
id|sCL
comma
id|sCL
comma
id|sCL
comma
id|sCL
comma
id|sLA
comma
id|sLI
comma
id|sCL
)brace
)brace
comma
)brace
suffix:semicolon
DECL|variable|tcp_state_table
r_static
r_struct
id|tcp_states_t
op_star
id|tcp_state_table
op_assign
id|tcp_states
suffix:semicolon
DECL|function|tcp_timeout_change
r_static
r_void
id|tcp_timeout_change
c_func
(paren
r_struct
id|ip_vs_protocol
op_star
id|pp
comma
r_int
id|flags
)paren
(brace
r_int
id|on
op_assign
(paren
id|flags
op_amp
l_int|1
)paren
suffix:semicolon
multiline_comment|/* secure_tcp */
multiline_comment|/*&n;&t;** FIXME: change secure_tcp to independent sysctl var&n;&t;** or make it per-service or per-app because it is valid&n;&t;** for most if not for all of the applications. Something&n;&t;** like &quot;capabilities&quot; (flags) for each object.&n;&t;*/
id|tcp_state_table
op_assign
(paren
id|on
ques
c_cond
id|tcp_states_dos
suffix:colon
id|tcp_states
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|tcp_set_state_timeout
id|tcp_set_state_timeout
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
r_return
id|ip_vs_set_state_timeout
c_func
(paren
id|pp-&gt;timeout_table
comma
id|IP_VS_TCP_S_LAST
comma
id|tcp_state_name_table
comma
id|sname
comma
id|to
)paren
suffix:semicolon
)brace
DECL|function|tcp_state_idx
r_static
r_inline
r_int
id|tcp_state_idx
c_func
(paren
r_struct
id|tcphdr
op_star
id|th
)paren
(brace
r_if
c_cond
(paren
id|th-&gt;rst
)paren
r_return
l_int|3
suffix:semicolon
r_if
c_cond
(paren
id|th-&gt;syn
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|th-&gt;fin
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|th-&gt;ack
)paren
r_return
l_int|2
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|set_tcp_state
id|set_tcp_state
c_func
(paren
r_struct
id|ip_vs_protocol
op_star
id|pp
comma
r_struct
id|ip_vs_conn
op_star
id|cp
comma
r_int
id|direction
comma
r_struct
id|tcphdr
op_star
id|th
)paren
(brace
r_int
id|state_idx
suffix:semicolon
r_int
id|new_state
op_assign
id|IP_VS_TCP_S_CLOSE
suffix:semicolon
r_int
id|state_off
op_assign
id|tcp_state_off
(braket
id|direction
)braket
suffix:semicolon
multiline_comment|/*&n;&t; *    Update state offset to INPUT_ONLY if necessary&n;&t; *    or delete NO_OUTPUT flag if output packet detected&n;&t; */
r_if
c_cond
(paren
id|cp-&gt;flags
op_amp
id|IP_VS_CONN_F_NOOUTPUT
)paren
(brace
r_if
c_cond
(paren
id|state_off
op_eq
id|TCP_DIR_OUTPUT
)paren
id|cp-&gt;flags
op_and_assign
op_complement
id|IP_VS_CONN_F_NOOUTPUT
suffix:semicolon
r_else
id|state_off
op_assign
id|TCP_DIR_INPUT_ONLY
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|state_idx
op_assign
id|tcp_state_idx
c_func
(paren
id|th
)paren
)paren
OL
l_int|0
)paren
(brace
id|IP_VS_DBG
c_func
(paren
l_int|8
comma
l_string|&quot;tcp_state_idx=%d!!!&bslash;n&quot;
comma
id|state_idx
)paren
suffix:semicolon
r_goto
id|tcp_state_out
suffix:semicolon
)brace
id|new_state
op_assign
id|tcp_state_table
(braket
id|state_off
op_plus
id|state_idx
)braket
dot
id|next_state
(braket
id|cp-&gt;state
)braket
suffix:semicolon
id|tcp_state_out
suffix:colon
r_if
c_cond
(paren
id|new_state
op_ne
id|cp-&gt;state
)paren
(brace
r_struct
id|ip_vs_dest
op_star
id|dest
op_assign
id|cp-&gt;dest
suffix:semicolon
id|IP_VS_DBG
c_func
(paren
l_int|8
comma
l_string|&quot;%s %s [%c%c%c%c] %u.%u.%u.%u:%d-&gt;&quot;
l_string|&quot;%u.%u.%u.%u:%d state: %s-&gt;%s cnt:%d&bslash;n&quot;
comma
id|pp-&gt;name
comma
(paren
id|state_off
op_eq
id|TCP_DIR_OUTPUT
)paren
ques
c_cond
l_string|&quot;output &quot;
suffix:colon
l_string|&quot;input &quot;
comma
id|th-&gt;syn
ques
c_cond
l_char|&squot;S&squot;
suffix:colon
l_char|&squot;.&squot;
comma
id|th-&gt;fin
ques
c_cond
l_char|&squot;F&squot;
suffix:colon
l_char|&squot;.&squot;
comma
id|th-&gt;ack
ques
c_cond
l_char|&squot;A&squot;
suffix:colon
l_char|&squot;.&squot;
comma
id|th-&gt;rst
ques
c_cond
l_char|&squot;R&squot;
suffix:colon
l_char|&squot;.&squot;
comma
id|NIPQUAD
c_func
(paren
id|cp-&gt;daddr
)paren
comma
id|ntohs
c_func
(paren
id|cp-&gt;dport
)paren
comma
id|NIPQUAD
c_func
(paren
id|cp-&gt;caddr
)paren
comma
id|ntohs
c_func
(paren
id|cp-&gt;cport
)paren
comma
id|tcp_state_name
c_func
(paren
id|cp-&gt;state
)paren
comma
id|tcp_state_name
c_func
(paren
id|new_state
)paren
comma
id|atomic_read
c_func
(paren
op_amp
id|cp-&gt;refcnt
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dest
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|cp-&gt;flags
op_amp
id|IP_VS_CONN_F_INACTIVE
)paren
op_logical_and
(paren
id|new_state
op_ne
id|IP_VS_TCP_S_ESTABLISHED
)paren
)paren
(brace
id|atomic_dec
c_func
(paren
op_amp
id|dest-&gt;activeconns
)paren
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|dest-&gt;inactconns
)paren
suffix:semicolon
id|cp-&gt;flags
op_or_assign
id|IP_VS_CONN_F_INACTIVE
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|cp-&gt;flags
op_amp
id|IP_VS_CONN_F_INACTIVE
)paren
op_logical_and
(paren
id|new_state
op_eq
id|IP_VS_TCP_S_ESTABLISHED
)paren
)paren
(brace
id|atomic_inc
c_func
(paren
op_amp
id|dest-&gt;activeconns
)paren
suffix:semicolon
id|atomic_dec
c_func
(paren
op_amp
id|dest-&gt;inactconns
)paren
suffix:semicolon
id|cp-&gt;flags
op_and_assign
op_complement
id|IP_VS_CONN_F_INACTIVE
suffix:semicolon
)brace
)brace
)brace
id|cp-&gt;timeout
op_assign
id|pp-&gt;timeout_table
(braket
id|cp-&gt;state
op_assign
id|new_state
)braket
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Handle state transitions&n; */
r_static
r_int
DECL|function|tcp_state_transition
id|tcp_state_transition
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
r_struct
id|tcphdr
id|_tcph
comma
op_star
id|th
suffix:semicolon
id|th
op_assign
id|skb_header_pointer
c_func
(paren
id|skb
comma
id|skb-&gt;nh.iph-&gt;ihl
op_star
l_int|4
comma
r_sizeof
(paren
id|_tcph
)paren
comma
op_amp
id|_tcph
)paren
suffix:semicolon
r_if
c_cond
(paren
id|th
op_eq
l_int|NULL
)paren
r_return
l_int|0
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|cp-&gt;lock
)paren
suffix:semicolon
id|set_tcp_state
c_func
(paren
id|pp
comma
id|cp
comma
id|direction
comma
id|th
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|cp-&gt;lock
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Hash table for TCP application incarnations&n; */
DECL|macro|TCP_APP_TAB_BITS
mdefine_line|#define&t;TCP_APP_TAB_BITS&t;4
DECL|macro|TCP_APP_TAB_SIZE
mdefine_line|#define&t;TCP_APP_TAB_SIZE&t;(1 &lt;&lt; TCP_APP_TAB_BITS)
DECL|macro|TCP_APP_TAB_MASK
mdefine_line|#define&t;TCP_APP_TAB_MASK&t;(TCP_APP_TAB_SIZE - 1)
DECL|variable|tcp_apps
r_static
r_struct
id|list_head
id|tcp_apps
(braket
id|TCP_APP_TAB_SIZE
)braket
suffix:semicolon
DECL|variable|tcp_app_lock
r_static
id|spinlock_t
id|tcp_app_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|function|tcp_app_hashkey
r_static
r_inline
id|__u16
id|tcp_app_hashkey
c_func
(paren
id|__u16
id|port
)paren
(brace
r_return
(paren
(paren
id|port
op_rshift
id|TCP_APP_TAB_BITS
)paren
op_xor
id|port
)paren
op_amp
id|TCP_APP_TAB_MASK
suffix:semicolon
)brace
DECL|function|tcp_register_app
r_static
r_int
id|tcp_register_app
c_func
(paren
r_struct
id|ip_vs_app
op_star
id|inc
)paren
(brace
r_struct
id|ip_vs_app
op_star
id|i
suffix:semicolon
id|__u16
id|hash
comma
id|port
op_assign
id|inc-&gt;port
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
id|hash
op_assign
id|tcp_app_hashkey
c_func
(paren
id|port
)paren
suffix:semicolon
id|spin_lock_bh
c_func
(paren
op_amp
id|tcp_app_lock
)paren
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|i
comma
op_amp
id|tcp_apps
(braket
id|hash
)braket
comma
id|p_list
)paren
(brace
r_if
c_cond
(paren
id|i-&gt;port
op_eq
id|port
)paren
(brace
id|ret
op_assign
op_minus
id|EEXIST
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
)brace
id|list_add
c_func
(paren
op_amp
id|inc-&gt;p_list
comma
op_amp
id|tcp_apps
(braket
id|hash
)braket
)paren
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|ip_vs_protocol_tcp.appcnt
)paren
suffix:semicolon
id|out
suffix:colon
id|spin_unlock_bh
c_func
(paren
op_amp
id|tcp_app_lock
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_static
r_void
DECL|function|tcp_unregister_app
id|tcp_unregister_app
c_func
(paren
r_struct
id|ip_vs_app
op_star
id|inc
)paren
(brace
id|spin_lock_bh
c_func
(paren
op_amp
id|tcp_app_lock
)paren
suffix:semicolon
id|atomic_dec
c_func
(paren
op_amp
id|ip_vs_protocol_tcp.appcnt
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|inc-&gt;p_list
)paren
suffix:semicolon
id|spin_unlock_bh
c_func
(paren
op_amp
id|tcp_app_lock
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|tcp_app_conn_bind
id|tcp_app_conn_bind
c_func
(paren
r_struct
id|ip_vs_conn
op_star
id|cp
)paren
(brace
r_int
id|hash
suffix:semicolon
r_struct
id|ip_vs_app
op_star
id|inc
suffix:semicolon
r_int
id|result
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Default binding: bind app only for NAT */
r_if
c_cond
(paren
id|IP_VS_FWD_METHOD
c_func
(paren
id|cp
)paren
op_ne
id|IP_VS_CONN_F_MASQ
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Lookup application incarnations and bind the right one */
id|hash
op_assign
id|tcp_app_hashkey
c_func
(paren
id|cp-&gt;vport
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|tcp_app_lock
)paren
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|inc
comma
op_amp
id|tcp_apps
(braket
id|hash
)braket
comma
id|p_list
)paren
(brace
r_if
c_cond
(paren
id|inc-&gt;port
op_eq
id|cp-&gt;vport
)paren
(brace
r_if
c_cond
(paren
id|unlikely
c_func
(paren
op_logical_neg
id|ip_vs_app_inc_get
c_func
(paren
id|inc
)paren
)paren
)paren
r_break
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|tcp_app_lock
)paren
suffix:semicolon
id|IP_VS_DBG
c_func
(paren
l_int|9
comma
l_string|&quot;%s: Binding conn %u.%u.%u.%u:%u-&gt;&quot;
l_string|&quot;%u.%u.%u.%u:%u to app %s on port %u&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|NIPQUAD
c_func
(paren
id|cp-&gt;caddr
)paren
comma
id|ntohs
c_func
(paren
id|cp-&gt;cport
)paren
comma
id|NIPQUAD
c_func
(paren
id|cp-&gt;vaddr
)paren
comma
id|ntohs
c_func
(paren
id|cp-&gt;vport
)paren
comma
id|inc-&gt;name
comma
id|ntohs
c_func
(paren
id|inc-&gt;port
)paren
)paren
suffix:semicolon
id|cp-&gt;app
op_assign
id|inc
suffix:semicolon
r_if
c_cond
(paren
id|inc-&gt;init_conn
)paren
id|result
op_assign
id|inc
op_member_access_from_pointer
id|init_conn
c_func
(paren
id|inc
comma
id|cp
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
)brace
id|spin_unlock
c_func
(paren
op_amp
id|tcp_app_lock
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|result
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Set LISTEN timeout. (ip_vs_conn_put will setup timer)&n; */
DECL|function|ip_vs_tcp_conn_listen
r_void
id|ip_vs_tcp_conn_listen
c_func
(paren
r_struct
id|ip_vs_conn
op_star
id|cp
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|cp-&gt;lock
)paren
suffix:semicolon
id|cp-&gt;state
op_assign
id|IP_VS_TCP_S_LISTEN
suffix:semicolon
id|cp-&gt;timeout
op_assign
id|ip_vs_protocol_tcp.timeout_table
(braket
id|IP_VS_TCP_S_LISTEN
)braket
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|cp-&gt;lock
)paren
suffix:semicolon
)brace
DECL|function|tcp_init
r_static
r_void
id|tcp_init
c_func
(paren
r_struct
id|ip_vs_protocol
op_star
id|pp
)paren
(brace
id|IP_VS_INIT_HASH_TABLE
c_func
(paren
id|tcp_apps
)paren
suffix:semicolon
id|pp-&gt;timeout_table
op_assign
id|tcp_timeouts
suffix:semicolon
)brace
DECL|function|tcp_exit
r_static
r_void
id|tcp_exit
c_func
(paren
r_struct
id|ip_vs_protocol
op_star
id|pp
)paren
(brace
)brace
DECL|variable|ip_vs_protocol_tcp
r_struct
id|ip_vs_protocol
id|ip_vs_protocol_tcp
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;TCP&quot;
comma
dot
id|protocol
op_assign
id|IPPROTO_TCP
comma
dot
id|dont_defrag
op_assign
l_int|0
comma
dot
id|appcnt
op_assign
id|ATOMIC_INIT
c_func
(paren
l_int|0
)paren
comma
dot
id|init
op_assign
id|tcp_init
comma
dot
m_exit
op_assign
id|tcp_exit
comma
dot
id|register_app
op_assign
id|tcp_register_app
comma
dot
id|unregister_app
op_assign
id|tcp_unregister_app
comma
dot
id|conn_schedule
op_assign
id|tcp_conn_schedule
comma
dot
id|conn_in_get
op_assign
id|tcp_conn_in_get
comma
dot
id|conn_out_get
op_assign
id|tcp_conn_out_get
comma
dot
id|snat_handler
op_assign
id|tcp_snat_handler
comma
dot
id|dnat_handler
op_assign
id|tcp_dnat_handler
comma
dot
id|csum_check
op_assign
id|tcp_csum_check
comma
dot
id|state_name
op_assign
id|tcp_state_name
comma
dot
id|state_transition
op_assign
id|tcp_state_transition
comma
dot
id|app_conn_bind
op_assign
id|tcp_app_conn_bind
comma
dot
id|debug_packet
op_assign
id|ip_vs_tcpudp_debug_packet
comma
dot
id|timeout_change
op_assign
id|tcp_timeout_change
comma
dot
id|set_state_timeout
op_assign
id|tcp_set_state_timeout
comma
)brace
suffix:semicolon
eof
