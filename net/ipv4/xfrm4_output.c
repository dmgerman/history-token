multiline_comment|/*&n; * xfrm4_output.c - Common IPsec encapsulation code for IPv4.&n; * Copyright (c) 2004 Herbert Xu &lt;herbert@gondor.apana.org.au&gt;&n; * &n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;net/inet_ecn.h&gt;
macro_line|#include &lt;net/ip.h&gt;
macro_line|#include &lt;net/xfrm.h&gt;
macro_line|#include &lt;net/icmp.h&gt;
multiline_comment|/* Add encapsulation header.&n; *&n; * In transport mode, the IP header will be moved forward to make space&n; * for the encapsulation header.&n; *&n; * In tunnel mode, the top IP header will be constructed per RFC 2401.&n; * The following fields in it shall be filled in by x-&gt;type-&gt;output:&n; *&t;tot_len&n; *&t;check&n; *&n; * On exit, skb-&gt;h will be set to the start of the payload to be processed&n; * by x-&gt;type-&gt;output and skb-&gt;nh will be set to the top IP header.&n; */
DECL|function|xfrm4_encap
r_static
r_void
id|xfrm4_encap
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|dst_entry
op_star
id|dst
op_assign
id|skb-&gt;dst
suffix:semicolon
r_struct
id|xfrm_state
op_star
id|x
op_assign
id|dst-&gt;xfrm
suffix:semicolon
r_struct
id|iphdr
op_star
id|iph
comma
op_star
id|top_iph
suffix:semicolon
id|iph
op_assign
id|skb-&gt;nh.iph
suffix:semicolon
id|skb-&gt;h.ipiph
op_assign
id|iph
suffix:semicolon
id|skb-&gt;nh.raw
op_assign
id|skb_push
c_func
(paren
id|skb
comma
id|x-&gt;props.header_len
)paren
suffix:semicolon
id|top_iph
op_assign
id|skb-&gt;nh.iph
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|x-&gt;props.mode
)paren
(brace
id|skb-&gt;h.raw
op_add_assign
id|iph-&gt;ihl
op_star
l_int|4
suffix:semicolon
id|memmove
c_func
(paren
id|top_iph
comma
id|iph
comma
id|iph-&gt;ihl
op_star
l_int|4
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|top_iph-&gt;ihl
op_assign
l_int|5
suffix:semicolon
id|top_iph-&gt;version
op_assign
l_int|4
suffix:semicolon
multiline_comment|/* DS disclosed */
id|top_iph-&gt;tos
op_assign
id|INET_ECN_encapsulate
c_func
(paren
id|iph-&gt;tos
comma
id|iph-&gt;tos
)paren
suffix:semicolon
r_if
c_cond
(paren
id|x-&gt;props.flags
op_amp
id|XFRM_STATE_NOECN
)paren
id|IP_ECN_clear
c_func
(paren
id|top_iph
)paren
suffix:semicolon
id|top_iph-&gt;frag_off
op_assign
id|iph-&gt;frag_off
op_amp
id|htons
c_func
(paren
id|IP_DF
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|top_iph-&gt;frag_off
)paren
id|__ip_select_ident
c_func
(paren
id|top_iph
comma
id|dst
comma
l_int|0
)paren
suffix:semicolon
id|top_iph-&gt;ttl
op_assign
id|dst_path_metric
c_func
(paren
id|dst
comma
id|RTAX_HOPLIMIT
)paren
suffix:semicolon
id|top_iph-&gt;saddr
op_assign
id|x-&gt;props.saddr.a4
suffix:semicolon
id|top_iph-&gt;daddr
op_assign
id|x-&gt;id.daddr.a4
suffix:semicolon
id|top_iph-&gt;protocol
op_assign
id|IPPROTO_IPIP
suffix:semicolon
id|memset
c_func
(paren
op_amp
(paren
id|IPCB
c_func
(paren
id|skb
)paren
op_member_access_from_pointer
id|opt
)paren
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|ip_options
)paren
)paren
suffix:semicolon
)brace
DECL|function|xfrm4_tunnel_check_size
r_static
r_int
id|xfrm4_tunnel_check_size
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_int
id|mtu
comma
id|ret
op_assign
l_int|0
suffix:semicolon
r_struct
id|dst_entry
op_star
id|dst
suffix:semicolon
r_struct
id|iphdr
op_star
id|iph
op_assign
id|skb-&gt;nh.iph
suffix:semicolon
r_if
c_cond
(paren
id|IPCB
c_func
(paren
id|skb
)paren
op_member_access_from_pointer
id|flags
op_amp
id|IPSKB_XFRM_TUNNEL_SIZE
)paren
r_goto
id|out
suffix:semicolon
id|IPCB
c_func
(paren
id|skb
)paren
op_member_access_from_pointer
id|flags
op_or_assign
id|IPSKB_XFRM_TUNNEL_SIZE
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|iph-&gt;frag_off
op_amp
id|htons
c_func
(paren
id|IP_DF
)paren
)paren
op_logical_or
id|skb-&gt;local_df
)paren
r_goto
id|out
suffix:semicolon
id|dst
op_assign
id|skb-&gt;dst
suffix:semicolon
id|mtu
op_assign
id|dst_mtu
c_func
(paren
id|dst
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb-&gt;len
OG
id|mtu
)paren
(brace
id|icmp_send
c_func
(paren
id|skb
comma
id|ICMP_DEST_UNREACH
comma
id|ICMP_FRAG_NEEDED
comma
id|htonl
c_func
(paren
id|mtu
)paren
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EMSGSIZE
suffix:semicolon
)brace
id|out
suffix:colon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|xfrm4_output
r_int
id|xfrm4_output
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|dst_entry
op_star
id|dst
op_assign
id|skb-&gt;dst
suffix:semicolon
r_struct
id|xfrm_state
op_star
id|x
op_assign
id|dst-&gt;xfrm
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
id|skb-&gt;ip_summed
op_eq
id|CHECKSUM_HW
)paren
(brace
id|err
op_assign
id|skb_checksum_help
c_func
(paren
id|skb
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|error_nolock
suffix:semicolon
)brace
r_if
c_cond
(paren
id|x-&gt;props.mode
)paren
(brace
id|err
op_assign
id|xfrm4_tunnel_check_size
c_func
(paren
id|skb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|error_nolock
suffix:semicolon
)brace
id|spin_lock_bh
c_func
(paren
op_amp
id|x-&gt;lock
)paren
suffix:semicolon
id|err
op_assign
id|xfrm_state_check
c_func
(paren
id|x
comma
id|skb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|error
suffix:semicolon
id|xfrm4_encap
c_func
(paren
id|skb
)paren
suffix:semicolon
id|err
op_assign
id|x-&gt;type
op_member_access_from_pointer
id|output
c_func
(paren
id|x
comma
id|skb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|error
suffix:semicolon
id|x-&gt;curlft.bytes
op_add_assign
id|skb-&gt;len
suffix:semicolon
id|x-&gt;curlft.packets
op_increment
suffix:semicolon
id|spin_unlock_bh
c_func
(paren
op_amp
id|x-&gt;lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|skb-&gt;dst
op_assign
id|dst_pop
c_func
(paren
id|dst
)paren
)paren
)paren
(brace
id|err
op_assign
op_minus
id|EHOSTUNREACH
suffix:semicolon
r_goto
id|error_nolock
suffix:semicolon
)brace
id|err
op_assign
id|NET_XMIT_BYPASS
suffix:semicolon
id|out_exit
suffix:colon
r_return
id|err
suffix:semicolon
id|error
suffix:colon
id|spin_unlock_bh
c_func
(paren
op_amp
id|x-&gt;lock
)paren
suffix:semicolon
id|error_nolock
suffix:colon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_goto
id|out_exit
suffix:semicolon
)brace
eof
