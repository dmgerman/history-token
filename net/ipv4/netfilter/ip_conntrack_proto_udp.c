multiline_comment|/* (C) 1999-2001 Paul `Rusty&squot; Russell&n; * (C) 2002-2004 Netfilter Core Team &lt;coreteam@netfilter.org&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/netfilter.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/udp.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_conntrack_protocol.h&gt;
DECL|variable|ip_ct_udp_timeout
r_int
r_int
id|ip_ct_udp_timeout
op_assign
l_int|30
op_star
id|HZ
suffix:semicolon
DECL|variable|ip_ct_udp_timeout_stream
r_int
r_int
id|ip_ct_udp_timeout_stream
op_assign
l_int|180
op_star
id|HZ
suffix:semicolon
DECL|function|udp_pkt_to_tuple
r_static
r_int
id|udp_pkt_to_tuple
c_func
(paren
r_const
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
r_int
id|dataoff
comma
r_struct
id|ip_conntrack_tuple
op_star
id|tuple
)paren
(brace
r_struct
id|udphdr
id|hdr
suffix:semicolon
multiline_comment|/* Actually only need first 8 bytes. */
r_if
c_cond
(paren
id|skb_copy_bits
c_func
(paren
id|skb
comma
id|dataoff
comma
op_amp
id|hdr
comma
l_int|8
)paren
op_ne
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|tuple-&gt;src.u.udp.port
op_assign
id|hdr.source
suffix:semicolon
id|tuple-&gt;dst.u.udp.port
op_assign
id|hdr.dest
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|udp_invert_tuple
r_static
r_int
id|udp_invert_tuple
c_func
(paren
r_struct
id|ip_conntrack_tuple
op_star
id|tuple
comma
r_const
r_struct
id|ip_conntrack_tuple
op_star
id|orig
)paren
(brace
id|tuple-&gt;src.u.udp.port
op_assign
id|orig-&gt;dst.u.udp.port
suffix:semicolon
id|tuple-&gt;dst.u.udp.port
op_assign
id|orig-&gt;src.u.udp.port
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Print out the per-protocol part of the tuple. */
DECL|function|udp_print_tuple
r_static
r_int
r_int
id|udp_print_tuple
c_func
(paren
r_char
op_star
id|buffer
comma
r_const
r_struct
id|ip_conntrack_tuple
op_star
id|tuple
)paren
(brace
r_return
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;sport=%hu dport=%hu &quot;
comma
id|ntohs
c_func
(paren
id|tuple-&gt;src.u.udp.port
)paren
comma
id|ntohs
c_func
(paren
id|tuple-&gt;dst.u.udp.port
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Print out the private part of the conntrack. */
DECL|function|udp_print_conntrack
r_static
r_int
r_int
id|udp_print_conntrack
c_func
(paren
r_char
op_star
id|buffer
comma
r_const
r_struct
id|ip_conntrack
op_star
id|conntrack
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Returns verdict for packet, and may modify conntracktype */
DECL|function|udp_packet
r_static
r_int
id|udp_packet
c_func
(paren
r_struct
id|ip_conntrack
op_star
id|conntrack
comma
r_const
r_struct
id|sk_buff
op_star
id|skb
comma
r_enum
id|ip_conntrack_info
id|conntrackinfo
)paren
(brace
multiline_comment|/* If we&squot;ve seen traffic both ways, this is some kind of UDP&n;&t;   stream.  Extend timeout. */
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|IPS_SEEN_REPLY_BIT
comma
op_amp
id|conntrack-&gt;status
)paren
)paren
(brace
id|ip_ct_refresh
c_func
(paren
id|conntrack
comma
id|ip_ct_udp_timeout_stream
)paren
suffix:semicolon
multiline_comment|/* Also, more likely to be important, and not a probe */
id|set_bit
c_func
(paren
id|IPS_ASSURED_BIT
comma
op_amp
id|conntrack-&gt;status
)paren
suffix:semicolon
)brace
r_else
id|ip_ct_refresh
c_func
(paren
id|conntrack
comma
id|ip_ct_udp_timeout
)paren
suffix:semicolon
r_return
id|NF_ACCEPT
suffix:semicolon
)brace
multiline_comment|/* Called when a new connection for this protocol found. */
DECL|function|udp_new
r_static
r_int
id|udp_new
c_func
(paren
r_struct
id|ip_conntrack
op_star
id|conntrack
comma
r_const
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|variable|ip_conntrack_protocol_udp
r_struct
id|ip_conntrack_protocol
id|ip_conntrack_protocol_udp
op_assign
(brace
(brace
l_int|NULL
comma
l_int|NULL
)brace
comma
id|IPPROTO_UDP
comma
l_string|&quot;udp&quot;
comma
id|udp_pkt_to_tuple
comma
id|udp_invert_tuple
comma
id|udp_print_tuple
comma
id|udp_print_conntrack
comma
id|udp_packet
comma
id|udp_new
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
)brace
suffix:semicolon
eof
