multiline_comment|/*&n; * ip_vs_proto_udp.c:&t;UDP load balancing support for IPVS&n; *&n; * Version:     $Id: ip_vs_proto_udp.c,v 1.3 2002/11/30 01:50:35 wensong Exp $&n; *&n; * Authors:     Wensong Zhang &lt;wensong@linuxvirtualserver.org&gt;&n; *              Julian Anastasov &lt;ja@ssi.bg&gt;&n; *&n; *              This program is free software; you can redistribute it and/or&n; *              modify it under the terms of the GNU General Public License&n; *              as published by the Free Software Foundation; either version&n; *              2 of the License, or (at your option) any later version.&n; *&n; * Changes:&n; *&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4.h&gt;
macro_line|#include &lt;net/ip_vs.h&gt;
r_static
r_struct
id|ip_vs_conn
op_star
DECL|function|udp_conn_in_get
id|udp_conn_in_get
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
id|cp
op_assign
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
id|cp
op_assign
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
r_return
id|cp
suffix:semicolon
)brace
r_static
r_struct
id|ip_vs_conn
op_star
DECL|function|udp_conn_out_get
id|udp_conn_out_get
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
id|skb-&gt;nh.iph-&gt;ihl
op_star
l_int|4
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
id|cp
op_assign
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
id|cp
op_assign
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
r_return
id|cp
suffix:semicolon
)brace
r_static
r_int
DECL|function|udp_conn_schedule
id|udp_conn_schedule
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
id|udphdr
id|_udph
comma
op_star
id|uh
suffix:semicolon
id|uh
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
id|_udph
)paren
comma
op_amp
id|_udph
)paren
suffix:semicolon
r_if
c_cond
(paren
id|uh
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
id|uh-&gt;dest
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
DECL|function|udp_fast_csum_update
id|udp_fast_csum_update
c_func
(paren
r_struct
id|udphdr
op_star
id|uhdr
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
id|uhdr-&gt;check
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
id|uhdr-&gt;check
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|uhdr-&gt;check
)paren
id|uhdr-&gt;check
op_assign
l_int|0xFFFF
suffix:semicolon
)brace
r_static
r_int
DECL|function|udp_snat_handler
id|udp_snat_handler
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
id|udphdr
op_star
id|udph
suffix:semicolon
r_int
r_int
id|udphoff
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
id|udphoff
op_plus
r_sizeof
(paren
op_star
id|udph
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
multiline_comment|/*&n;&t;&t; *&t;Call application helper if needed&n;&t;&t; */
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
id|udph
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
id|udphoff
suffix:semicolon
id|udph-&gt;source
op_assign
id|cp-&gt;vport
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Adjust UDP checksums&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|cp-&gt;app
op_logical_and
(paren
id|udph-&gt;check
op_ne
l_int|0
)paren
)paren
(brace
multiline_comment|/* Only port and addr are changed, do fast csum update */
id|udp_fast_csum_update
c_func
(paren
id|udph
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
id|udph-&gt;check
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
id|udphoff
comma
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|len
op_minus
id|udphoff
comma
l_int|0
)paren
suffix:semicolon
id|udph-&gt;check
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
id|udphoff
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
r_if
c_cond
(paren
id|udph-&gt;check
op_eq
l_int|0
)paren
id|udph-&gt;check
op_assign
l_int|0xFFFF
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
id|udph-&gt;check
comma
(paren
r_char
op_star
)paren
op_amp
(paren
id|udph-&gt;check
)paren
op_minus
(paren
r_char
op_star
)paren
id|udph
)paren
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
r_static
r_int
DECL|function|udp_dnat_handler
id|udp_dnat_handler
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
id|udphdr
op_star
id|udph
suffix:semicolon
r_int
r_int
id|udphoff
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
id|udphoff
op_plus
r_sizeof
(paren
op_star
id|udph
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
multiline_comment|/*&n;&t;&t; *&t;Attempt ip_vs_app call.&n;&t;&t; *&t;It will fix ip_vs_conn&n;&t;&t; */
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
id|udph
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
id|udphoff
suffix:semicolon
id|udph-&gt;dest
op_assign
id|cp-&gt;dport
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Adjust UDP checksums&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|cp-&gt;app
op_logical_and
(paren
id|udph-&gt;check
op_ne
l_int|0
)paren
)paren
(brace
multiline_comment|/* Only port and addr are changed, do fast csum update */
id|udp_fast_csum_update
c_func
(paren
id|udph
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
id|udph-&gt;check
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
id|udphoff
comma
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|len
op_minus
id|udphoff
comma
l_int|0
)paren
suffix:semicolon
id|udph-&gt;check
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
id|udphoff
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
r_if
c_cond
(paren
id|udph-&gt;check
op_eq
l_int|0
)paren
id|udph-&gt;check
op_assign
l_int|0xFFFF
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
DECL|function|udp_csum_check
id|udp_csum_check
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
r_struct
id|udphdr
id|_udph
comma
op_star
id|uh
suffix:semicolon
r_int
r_int
id|udphoff
op_assign
id|skb-&gt;nh.iph-&gt;ihl
op_star
l_int|4
suffix:semicolon
id|uh
op_assign
id|skb_header_pointer
c_func
(paren
id|skb
comma
id|udphoff
comma
r_sizeof
(paren
id|_udph
)paren
comma
op_amp
id|_udph
)paren
suffix:semicolon
r_if
c_cond
(paren
id|uh
op_eq
l_int|NULL
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|uh-&gt;check
op_ne
l_int|0
)paren
(brace
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
id|udphoff
comma
id|skb-&gt;len
op_minus
id|udphoff
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
id|udphoff
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
)brace
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Note: the caller guarantees that only one of register_app,&n; *&t;unregister_app or app_conn_bind is called each time.&n; */
DECL|macro|UDP_APP_TAB_BITS
mdefine_line|#define&t;UDP_APP_TAB_BITS&t;4
DECL|macro|UDP_APP_TAB_SIZE
mdefine_line|#define&t;UDP_APP_TAB_SIZE&t;(1 &lt;&lt; UDP_APP_TAB_BITS)
DECL|macro|UDP_APP_TAB_MASK
mdefine_line|#define&t;UDP_APP_TAB_MASK&t;(UDP_APP_TAB_SIZE - 1)
DECL|variable|udp_apps
r_static
r_struct
id|list_head
id|udp_apps
(braket
id|UDP_APP_TAB_SIZE
)braket
suffix:semicolon
r_static
id|DEFINE_SPINLOCK
c_func
(paren
id|udp_app_lock
)paren
suffix:semicolon
DECL|function|udp_app_hashkey
r_static
r_inline
id|__u16
id|udp_app_hashkey
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
id|UDP_APP_TAB_BITS
)paren
op_xor
id|port
)paren
op_amp
id|UDP_APP_TAB_MASK
suffix:semicolon
)brace
DECL|function|udp_register_app
r_static
r_int
id|udp_register_app
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
id|udp_app_hashkey
c_func
(paren
id|port
)paren
suffix:semicolon
id|spin_lock_bh
c_func
(paren
op_amp
id|udp_app_lock
)paren
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|i
comma
op_amp
id|udp_apps
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
id|udp_apps
(braket
id|hash
)braket
)paren
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|ip_vs_protocol_udp.appcnt
)paren
suffix:semicolon
id|out
suffix:colon
id|spin_unlock_bh
c_func
(paren
op_amp
id|udp_app_lock
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_static
r_void
DECL|function|udp_unregister_app
id|udp_unregister_app
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
id|udp_app_lock
)paren
suffix:semicolon
id|atomic_dec
c_func
(paren
op_amp
id|ip_vs_protocol_udp.appcnt
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
id|udp_app_lock
)paren
suffix:semicolon
)brace
DECL|function|udp_app_conn_bind
r_static
r_int
id|udp_app_conn_bind
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
id|udp_app_hashkey
c_func
(paren
id|cp-&gt;vport
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|udp_app_lock
)paren
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|inc
comma
op_amp
id|udp_apps
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
id|udp_app_lock
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
id|udp_app_lock
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|result
suffix:semicolon
)brace
DECL|variable|udp_timeouts
r_static
r_int
id|udp_timeouts
(braket
id|IP_VS_UDP_S_LAST
op_plus
l_int|1
)braket
op_assign
(brace
(braket
id|IP_VS_UDP_S_NORMAL
)braket
op_assign
l_int|5
op_star
l_int|60
op_star
id|HZ
comma
(braket
id|IP_VS_UDP_S_LAST
)braket
op_assign
l_int|2
op_star
id|HZ
comma
)brace
suffix:semicolon
DECL|variable|udp_state_name_table
r_static
r_char
op_star
id|udp_state_name_table
(braket
id|IP_VS_UDP_S_LAST
op_plus
l_int|1
)braket
op_assign
(brace
(braket
id|IP_VS_UDP_S_NORMAL
)braket
op_assign
l_string|&quot;UDP&quot;
comma
(braket
id|IP_VS_UDP_S_LAST
)braket
op_assign
l_string|&quot;BUG!&quot;
comma
)brace
suffix:semicolon
r_static
r_int
DECL|function|udp_set_state_timeout
id|udp_set_state_timeout
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
id|IP_VS_UDP_S_LAST
comma
id|udp_state_name_table
comma
id|sname
comma
id|to
)paren
suffix:semicolon
)brace
DECL|function|udp_state_name
r_static
r_const
r_char
op_star
id|udp_state_name
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
id|IP_VS_UDP_S_LAST
)paren
r_return
l_string|&quot;ERR!&quot;
suffix:semicolon
r_return
id|udp_state_name_table
(braket
id|state
)braket
ques
c_cond
id|udp_state_name_table
(braket
id|state
)braket
suffix:colon
l_string|&quot;?&quot;
suffix:semicolon
)brace
r_static
r_int
DECL|function|udp_state_transition
id|udp_state_transition
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
id|IP_VS_UDP_S_NORMAL
)braket
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|udp_init
r_static
r_void
id|udp_init
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
id|udp_apps
)paren
suffix:semicolon
id|pp-&gt;timeout_table
op_assign
id|udp_timeouts
suffix:semicolon
)brace
DECL|function|udp_exit
r_static
r_void
id|udp_exit
c_func
(paren
r_struct
id|ip_vs_protocol
op_star
id|pp
)paren
(brace
)brace
DECL|variable|ip_vs_protocol_udp
r_struct
id|ip_vs_protocol
id|ip_vs_protocol_udp
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;UDP&quot;
comma
dot
id|protocol
op_assign
id|IPPROTO_UDP
comma
dot
id|dont_defrag
op_assign
l_int|0
comma
dot
id|init
op_assign
id|udp_init
comma
dot
m_exit
op_assign
id|udp_exit
comma
dot
id|conn_schedule
op_assign
id|udp_conn_schedule
comma
dot
id|conn_in_get
op_assign
id|udp_conn_in_get
comma
dot
id|conn_out_get
op_assign
id|udp_conn_out_get
comma
dot
id|snat_handler
op_assign
id|udp_snat_handler
comma
dot
id|dnat_handler
op_assign
id|udp_dnat_handler
comma
dot
id|csum_check
op_assign
id|udp_csum_check
comma
dot
id|state_transition
op_assign
id|udp_state_transition
comma
dot
id|state_name
op_assign
id|udp_state_name
comma
dot
id|register_app
op_assign
id|udp_register_app
comma
dot
id|unregister_app
op_assign
id|udp_unregister_app
comma
dot
id|app_conn_bind
op_assign
id|udp_app_conn_bind
comma
dot
id|debug_packet
op_assign
id|ip_vs_tcpudp_debug_packet
comma
dot
id|timeout_change
op_assign
l_int|NULL
comma
dot
id|set_state_timeout
op_assign
id|udp_set_state_timeout
comma
)brace
suffix:semicolon
eof
