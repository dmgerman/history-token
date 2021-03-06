multiline_comment|/*&n; * Copyright (C)2002 USAGI/WIDE Project&n; * &n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; * &n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; *&n; * Authors&n; *&n; *&t;Mitsuru KANDA @USAGI       : IPv6 Support &n; * &t;Kazunori MIYAZAWA @USAGI   :&n; * &t;Kunihiro Ishiguro &lt;kunihiro@ipinfusion.com&gt;&n; * &t;&n; * &t;This file is derived from net/ipv4/ah.c.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;net/ip.h&gt;
macro_line|#include &lt;net/ah.h&gt;
macro_line|#include &lt;linux/crypto.h&gt;
macro_line|#include &lt;linux/pfkeyv2.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;net/icmp.h&gt;
macro_line|#include &lt;net/ipv6.h&gt;
macro_line|#include &lt;net/xfrm.h&gt;
macro_line|#include &lt;asm/scatterlist.h&gt;
DECL|function|zero_out_mutable_opts
r_static
r_int
id|zero_out_mutable_opts
c_func
(paren
r_struct
id|ipv6_opt_hdr
op_star
id|opthdr
)paren
(brace
id|u8
op_star
id|opt
op_assign
(paren
id|u8
op_star
)paren
id|opthdr
suffix:semicolon
r_int
id|len
op_assign
id|ipv6_optlen
c_func
(paren
id|opthdr
)paren
suffix:semicolon
r_int
id|off
op_assign
l_int|0
suffix:semicolon
r_int
id|optlen
op_assign
l_int|0
suffix:semicolon
id|off
op_add_assign
l_int|2
suffix:semicolon
id|len
op_sub_assign
l_int|2
suffix:semicolon
r_while
c_loop
(paren
id|len
OG
l_int|0
)paren
(brace
r_switch
c_cond
(paren
id|opt
(braket
id|off
)braket
)paren
(brace
r_case
id|IPV6_TLV_PAD0
suffix:colon
id|optlen
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
(brace
)brace
r_if
c_cond
(paren
id|len
OL
l_int|2
)paren
r_goto
id|bad
suffix:semicolon
id|optlen
op_assign
id|opt
(braket
id|off
op_plus
l_int|1
)braket
op_plus
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
id|optlen
)paren
r_goto
id|bad
suffix:semicolon
r_if
c_cond
(paren
id|opt
(braket
id|off
)braket
op_amp
l_int|0x20
)paren
id|memset
c_func
(paren
op_amp
id|opt
(braket
id|off
op_plus
l_int|2
)braket
comma
l_int|0
comma
id|opt
(braket
id|off
op_plus
l_int|1
)braket
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|off
op_add_assign
id|optlen
suffix:semicolon
id|len
op_sub_assign
id|optlen
suffix:semicolon
)brace
r_if
c_cond
(paren
id|len
op_eq
l_int|0
)paren
r_return
l_int|1
suffix:semicolon
id|bad
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;ipv6_rearrange_rthdr - rearrange IPv6 routing header&n; *&t;@iph: IPv6 header&n; *&t;@rthdr: routing header&n; *&n; *&t;Rearrange the destination address in @iph and the addresses in @rthdr&n; *&t;so that they appear in the order they will at the final destination.&n; *&t;See Appendix A2 of RFC 2402 for details.&n; */
DECL|function|ipv6_rearrange_rthdr
r_static
r_void
id|ipv6_rearrange_rthdr
c_func
(paren
r_struct
id|ipv6hdr
op_star
id|iph
comma
r_struct
id|ipv6_rt_hdr
op_star
id|rthdr
)paren
(brace
r_int
id|segments
comma
id|segments_left
suffix:semicolon
r_struct
id|in6_addr
op_star
id|addrs
suffix:semicolon
r_struct
id|in6_addr
id|final_addr
suffix:semicolon
id|segments_left
op_assign
id|rthdr-&gt;segments_left
suffix:semicolon
r_if
c_cond
(paren
id|segments_left
op_eq
l_int|0
)paren
r_return
suffix:semicolon
id|rthdr-&gt;segments_left
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* The value of rthdr-&gt;hdrlen has been verified either by the system&n;&t; * call if it is locally generated, or by ipv6_rthdr_rcv() for incoming&n;&t; * packets.  So we can assume that it is even and that segments is&n;&t; * greater than or equal to segments_left.&n;&t; *&n;&t; * For the same reason we can assume that this option is of type 0.&n;&t; */
id|segments
op_assign
id|rthdr-&gt;hdrlen
op_rshift
l_int|1
suffix:semicolon
id|addrs
op_assign
(paren
(paren
r_struct
id|rt0_hdr
op_star
)paren
id|rthdr
)paren
op_member_access_from_pointer
id|addr
suffix:semicolon
id|ipv6_addr_copy
c_func
(paren
op_amp
id|final_addr
comma
id|addrs
op_plus
id|segments
op_minus
l_int|1
)paren
suffix:semicolon
id|addrs
op_add_assign
id|segments
op_minus
id|segments_left
suffix:semicolon
id|memmove
c_func
(paren
id|addrs
op_plus
l_int|1
comma
id|addrs
comma
(paren
id|segments_left
op_minus
l_int|1
)paren
op_star
r_sizeof
(paren
op_star
id|addrs
)paren
)paren
suffix:semicolon
id|ipv6_addr_copy
c_func
(paren
id|addrs
comma
op_amp
id|iph-&gt;daddr
)paren
suffix:semicolon
id|ipv6_addr_copy
c_func
(paren
op_amp
id|iph-&gt;daddr
comma
op_amp
id|final_addr
)paren
suffix:semicolon
)brace
DECL|function|ipv6_clear_mutable_options
r_static
r_int
id|ipv6_clear_mutable_options
c_func
(paren
r_struct
id|ipv6hdr
op_star
id|iph
comma
r_int
id|len
)paren
(brace
r_union
(brace
r_struct
id|ipv6hdr
op_star
id|iph
suffix:semicolon
r_struct
id|ipv6_opt_hdr
op_star
id|opth
suffix:semicolon
r_struct
id|ipv6_rt_hdr
op_star
id|rth
suffix:semicolon
r_char
op_star
id|raw
suffix:semicolon
)brace
id|exthdr
op_assign
(brace
dot
id|iph
op_assign
id|iph
)brace
suffix:semicolon
r_char
op_star
id|end
op_assign
id|exthdr.raw
op_plus
id|len
suffix:semicolon
r_int
id|nexthdr
op_assign
id|iph-&gt;nexthdr
suffix:semicolon
id|exthdr.iph
op_increment
suffix:semicolon
r_while
c_loop
(paren
id|exthdr.raw
OL
id|end
)paren
(brace
r_switch
c_cond
(paren
id|nexthdr
)paren
(brace
r_case
id|NEXTHDR_HOP
suffix:colon
r_case
id|NEXTHDR_DEST
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|zero_out_mutable_opts
c_func
(paren
id|exthdr.opth
)paren
)paren
(brace
id|LIMIT_NETDEBUG
c_func
(paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;overrun %sopts&bslash;n&quot;
comma
id|nexthdr
op_eq
id|NEXTHDR_HOP
ques
c_cond
l_string|&quot;hop&quot;
suffix:colon
l_string|&quot;dest&quot;
)paren
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|NEXTHDR_ROUTING
suffix:colon
id|ipv6_rearrange_rthdr
c_func
(paren
id|iph
comma
id|exthdr.rth
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
id|nexthdr
op_assign
id|exthdr.opth-&gt;nexthdr
suffix:semicolon
id|exthdr.raw
op_add_assign
id|ipv6_optlen
c_func
(paren
id|exthdr.opth
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ah6_output
r_static
r_int
id|ah6_output
c_func
(paren
r_struct
id|xfrm_state
op_star
id|x
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_int
id|err
suffix:semicolon
r_int
id|extlen
suffix:semicolon
r_struct
id|ipv6hdr
op_star
id|top_iph
suffix:semicolon
r_struct
id|ip_auth_hdr
op_star
id|ah
suffix:semicolon
r_struct
id|ah_data
op_star
id|ahp
suffix:semicolon
id|u8
id|nexthdr
suffix:semicolon
r_char
id|tmp_base
(braket
l_int|8
)braket
suffix:semicolon
r_struct
(brace
r_struct
id|in6_addr
id|daddr
suffix:semicolon
r_char
id|hdrs
(braket
l_int|0
)braket
suffix:semicolon
)brace
op_star
id|tmp_ext
suffix:semicolon
id|top_iph
op_assign
(paren
r_struct
id|ipv6hdr
op_star
)paren
id|skb-&gt;data
suffix:semicolon
id|top_iph-&gt;payload_len
op_assign
id|htons
c_func
(paren
id|skb-&gt;len
op_minus
r_sizeof
(paren
op_star
id|top_iph
)paren
)paren
suffix:semicolon
id|nexthdr
op_assign
op_star
id|skb-&gt;nh.raw
suffix:semicolon
op_star
id|skb-&gt;nh.raw
op_assign
id|IPPROTO_AH
suffix:semicolon
multiline_comment|/* When there are no extension headers, we only need to save the first&n;&t; * 8 bytes of the base IP header.&n;&t; */
id|memcpy
c_func
(paren
id|tmp_base
comma
id|top_iph
comma
r_sizeof
(paren
id|tmp_base
)paren
)paren
suffix:semicolon
id|tmp_ext
op_assign
l_int|NULL
suffix:semicolon
id|extlen
op_assign
id|skb-&gt;h.raw
op_minus
(paren
r_int
r_char
op_star
)paren
(paren
id|top_iph
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|extlen
)paren
(brace
id|extlen
op_add_assign
r_sizeof
(paren
op_star
id|tmp_ext
)paren
suffix:semicolon
id|tmp_ext
op_assign
id|kmalloc
c_func
(paren
id|extlen
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tmp_ext
)paren
(brace
id|err
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|error
suffix:semicolon
)brace
id|memcpy
c_func
(paren
id|tmp_ext
comma
op_amp
id|top_iph-&gt;daddr
comma
id|extlen
)paren
suffix:semicolon
id|err
op_assign
id|ipv6_clear_mutable_options
c_func
(paren
id|top_iph
comma
id|extlen
op_minus
r_sizeof
(paren
op_star
id|tmp_ext
)paren
op_plus
r_sizeof
(paren
op_star
id|top_iph
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|error_free_iph
suffix:semicolon
)brace
id|ah
op_assign
(paren
r_struct
id|ip_auth_hdr
op_star
)paren
id|skb-&gt;h.raw
suffix:semicolon
id|ah-&gt;nexthdr
op_assign
id|nexthdr
suffix:semicolon
id|top_iph-&gt;priority
op_assign
l_int|0
suffix:semicolon
id|top_iph-&gt;flow_lbl
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
id|top_iph-&gt;flow_lbl
(braket
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
id|top_iph-&gt;flow_lbl
(braket
l_int|2
)braket
op_assign
l_int|0
suffix:semicolon
id|top_iph-&gt;hop_limit
op_assign
l_int|0
suffix:semicolon
id|ahp
op_assign
id|x-&gt;data
suffix:semicolon
id|ah-&gt;hdrlen
op_assign
(paren
id|XFRM_ALIGN8
c_func
(paren
r_sizeof
(paren
r_struct
id|ipv6_auth_hdr
)paren
op_plus
id|ahp-&gt;icv_trunc_len
)paren
op_rshift
l_int|2
)paren
op_minus
l_int|2
suffix:semicolon
id|ah-&gt;reserved
op_assign
l_int|0
suffix:semicolon
id|ah-&gt;spi
op_assign
id|x-&gt;id.spi
suffix:semicolon
id|ah-&gt;seq_no
op_assign
id|htonl
c_func
(paren
op_increment
id|x-&gt;replay.oseq
)paren
suffix:semicolon
id|ahp
op_member_access_from_pointer
id|icv
c_func
(paren
id|ahp
comma
id|skb
comma
id|ah-&gt;auth_data
)paren
suffix:semicolon
id|err
op_assign
l_int|0
suffix:semicolon
id|memcpy
c_func
(paren
id|top_iph
comma
id|tmp_base
comma
r_sizeof
(paren
id|tmp_base
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp_ext
)paren
(brace
id|memcpy
c_func
(paren
op_amp
id|top_iph-&gt;daddr
comma
id|tmp_ext
comma
id|extlen
)paren
suffix:semicolon
id|error_free_iph
suffix:colon
id|kfree
c_func
(paren
id|tmp_ext
)paren
suffix:semicolon
)brace
id|error
suffix:colon
r_return
id|err
suffix:semicolon
)brace
DECL|function|ah6_input
r_static
r_int
id|ah6_input
c_func
(paren
r_struct
id|xfrm_state
op_star
id|x
comma
r_struct
id|xfrm_decap_state
op_star
id|decap
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
multiline_comment|/*&n;&t; * Before process AH&n;&t; * [IPv6][Ext1][Ext2][AH][Dest][Payload]&n;&t; * |&lt;--------------&gt;| hdr_len&n;&t; *&n;&t; * To erase AH:&n;&t; * Keeping copy of cleared headers. After AH processing,&n;&t; * Moving the pointer of skb-&gt;nh.raw by using skb_pull as long as AH&n;&t; * header length. Then copy back the copy as long as hdr_len&n;&t; * If destination header following AH exists, copy it into after [Ext2].&n;&t; * &n;&t; * |&lt;&gt;|[IPv6][Ext1][Ext2][Dest][Payload]&n;&t; * There is offset of AH before IPv6 header after the process.&n;&t; */
r_struct
id|ipv6_auth_hdr
op_star
id|ah
suffix:semicolon
r_struct
id|ah_data
op_star
id|ahp
suffix:semicolon
r_int
r_char
op_star
id|tmp_hdr
op_assign
l_int|NULL
suffix:semicolon
id|u16
id|hdr_len
suffix:semicolon
id|u16
id|ah_hlen
suffix:semicolon
r_int
id|nexthdr
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pskb_may_pull
c_func
(paren
id|skb
comma
r_sizeof
(paren
r_struct
id|ip_auth_hdr
)paren
)paren
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/* We are going to _remove_ AH header to keep sockets happy,&n;&t; * so... Later this can change. */
r_if
c_cond
(paren
id|skb_cloned
c_func
(paren
id|skb
)paren
op_logical_and
id|pskb_expand_head
c_func
(paren
id|skb
comma
l_int|0
comma
l_int|0
comma
id|GFP_ATOMIC
)paren
)paren
r_goto
id|out
suffix:semicolon
id|hdr_len
op_assign
id|skb-&gt;data
op_minus
id|skb-&gt;nh.raw
suffix:semicolon
id|ah
op_assign
(paren
r_struct
id|ipv6_auth_hdr
op_star
)paren
id|skb-&gt;data
suffix:semicolon
id|ahp
op_assign
id|x-&gt;data
suffix:semicolon
id|nexthdr
op_assign
id|ah-&gt;nexthdr
suffix:semicolon
id|ah_hlen
op_assign
(paren
id|ah-&gt;hdrlen
op_plus
l_int|2
)paren
op_lshift
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|ah_hlen
op_ne
id|XFRM_ALIGN8
c_func
(paren
r_sizeof
(paren
r_struct
id|ipv6_auth_hdr
)paren
op_plus
id|ahp-&gt;icv_full_len
)paren
op_logical_and
id|ah_hlen
op_ne
id|XFRM_ALIGN8
c_func
(paren
r_sizeof
(paren
r_struct
id|ipv6_auth_hdr
)paren
op_plus
id|ahp-&gt;icv_trunc_len
)paren
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pskb_may_pull
c_func
(paren
id|skb
comma
id|ah_hlen
)paren
)paren
r_goto
id|out
suffix:semicolon
id|tmp_hdr
op_assign
id|kmalloc
c_func
(paren
id|hdr_len
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tmp_hdr
)paren
r_goto
id|out
suffix:semicolon
id|memcpy
c_func
(paren
id|tmp_hdr
comma
id|skb-&gt;nh.raw
comma
id|hdr_len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ipv6_clear_mutable_options
c_func
(paren
id|skb-&gt;nh.ipv6h
comma
id|hdr_len
)paren
)paren
r_goto
id|out
suffix:semicolon
id|skb-&gt;nh.ipv6h-&gt;priority
op_assign
l_int|0
suffix:semicolon
id|skb-&gt;nh.ipv6h-&gt;flow_lbl
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
id|skb-&gt;nh.ipv6h-&gt;flow_lbl
(braket
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
id|skb-&gt;nh.ipv6h-&gt;flow_lbl
(braket
l_int|2
)braket
op_assign
l_int|0
suffix:semicolon
id|skb-&gt;nh.ipv6h-&gt;hop_limit
op_assign
l_int|0
suffix:semicolon
(brace
id|u8
id|auth_data
(braket
id|MAX_AH_AUTH_LEN
)braket
suffix:semicolon
id|memcpy
c_func
(paren
id|auth_data
comma
id|ah-&gt;auth_data
comma
id|ahp-&gt;icv_trunc_len
)paren
suffix:semicolon
id|memset
c_func
(paren
id|ah-&gt;auth_data
comma
l_int|0
comma
id|ahp-&gt;icv_trunc_len
)paren
suffix:semicolon
id|skb_push
c_func
(paren
id|skb
comma
id|skb-&gt;data
op_minus
id|skb-&gt;nh.raw
)paren
suffix:semicolon
id|ahp
op_member_access_from_pointer
id|icv
c_func
(paren
id|ahp
comma
id|skb
comma
id|ah-&gt;auth_data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|ah-&gt;auth_data
comma
id|auth_data
comma
id|ahp-&gt;icv_trunc_len
)paren
)paren
(brace
id|LIMIT_NETDEBUG
c_func
(paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;ipsec ah authentication error&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|x-&gt;stats.integrity_failed
op_increment
suffix:semicolon
r_goto
id|free_out
suffix:semicolon
)brace
)brace
id|skb-&gt;nh.raw
op_assign
id|skb_pull
c_func
(paren
id|skb
comma
id|ah_hlen
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|skb-&gt;nh.raw
comma
id|tmp_hdr
comma
id|hdr_len
)paren
suffix:semicolon
id|skb-&gt;nh.ipv6h-&gt;payload_len
op_assign
id|htons
c_func
(paren
id|skb-&gt;len
op_minus
r_sizeof
(paren
r_struct
id|ipv6hdr
)paren
)paren
suffix:semicolon
id|skb_pull
c_func
(paren
id|skb
comma
id|hdr_len
)paren
suffix:semicolon
id|skb-&gt;h.raw
op_assign
id|skb-&gt;data
suffix:semicolon
id|kfree
c_func
(paren
id|tmp_hdr
)paren
suffix:semicolon
r_return
id|nexthdr
suffix:semicolon
id|free_out
suffix:colon
id|kfree
c_func
(paren
id|tmp_hdr
)paren
suffix:semicolon
id|out
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|ah6_err
r_static
r_void
id|ah6_err
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|inet6_skb_parm
op_star
id|opt
comma
r_int
id|type
comma
r_int
id|code
comma
r_int
id|offset
comma
id|__u32
id|info
)paren
(brace
r_struct
id|ipv6hdr
op_star
id|iph
op_assign
(paren
r_struct
id|ipv6hdr
op_star
)paren
id|skb-&gt;data
suffix:semicolon
r_struct
id|ip_auth_hdr
op_star
id|ah
op_assign
(paren
r_struct
id|ip_auth_hdr
op_star
)paren
(paren
id|skb-&gt;data
op_plus
id|offset
)paren
suffix:semicolon
r_struct
id|xfrm_state
op_star
id|x
suffix:semicolon
r_if
c_cond
(paren
id|type
op_ne
id|ICMPV6_DEST_UNREACH
op_logical_and
id|type
op_ne
id|ICMPV6_PKT_TOOBIG
)paren
r_return
suffix:semicolon
id|x
op_assign
id|xfrm_state_lookup
c_func
(paren
(paren
id|xfrm_address_t
op_star
)paren
op_amp
id|iph-&gt;daddr
comma
id|ah-&gt;spi
comma
id|IPPROTO_AH
comma
id|AF_INET6
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|x
)paren
r_return
suffix:semicolon
id|NETDEBUG
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;pmtu discovery on SA AH/%08x/&quot;
l_string|&quot;%04x:%04x:%04x:%04x:%04x:%04x:%04x:%04x&bslash;n&quot;
comma
id|ntohl
c_func
(paren
id|ah-&gt;spi
)paren
comma
id|NIP6
c_func
(paren
id|iph-&gt;daddr
)paren
)paren
)paren
suffix:semicolon
id|xfrm_state_put
c_func
(paren
id|x
)paren
suffix:semicolon
)brace
DECL|function|ah6_init_state
r_static
r_int
id|ah6_init_state
c_func
(paren
r_struct
id|xfrm_state
op_star
id|x
comma
r_void
op_star
id|args
)paren
(brace
r_struct
id|ah_data
op_star
id|ahp
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|xfrm_algo_desc
op_star
id|aalg_desc
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|x-&gt;aalg
)paren
r_goto
id|error
suffix:semicolon
multiline_comment|/* null auth can use a zero length key */
r_if
c_cond
(paren
id|x-&gt;aalg-&gt;alg_key_len
OG
l_int|512
)paren
r_goto
id|error
suffix:semicolon
r_if
c_cond
(paren
id|x-&gt;encap
)paren
r_goto
id|error
suffix:semicolon
id|ahp
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|ahp
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ahp
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
id|ahp
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|ahp
)paren
)paren
suffix:semicolon
id|ahp-&gt;key
op_assign
id|x-&gt;aalg-&gt;alg_key
suffix:semicolon
id|ahp-&gt;key_len
op_assign
(paren
id|x-&gt;aalg-&gt;alg_key_len
op_plus
l_int|7
)paren
op_div
l_int|8
suffix:semicolon
id|ahp-&gt;tfm
op_assign
id|crypto_alloc_tfm
c_func
(paren
id|x-&gt;aalg-&gt;alg_name
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ahp-&gt;tfm
)paren
r_goto
id|error
suffix:semicolon
id|ahp-&gt;icv
op_assign
id|ah_hmac_digest
suffix:semicolon
multiline_comment|/*&n;&t; * Lookup the algorithm description maintained by xfrm_algo,&n;&t; * verify crypto transform properties, and store information&n;&t; * we need for AH processing.  This lookup cannot fail here&n;&t; * after a successful crypto_alloc_tfm().&n;&t; */
id|aalg_desc
op_assign
id|xfrm_aalg_get_byname
c_func
(paren
id|x-&gt;aalg-&gt;alg_name
comma
l_int|0
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
op_logical_neg
id|aalg_desc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|aalg_desc-&gt;uinfo.auth.icv_fullbits
op_div
l_int|8
op_ne
id|crypto_tfm_alg_digestsize
c_func
(paren
id|ahp-&gt;tfm
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;AH: %s digestsize %u != %hu&bslash;n&quot;
comma
id|x-&gt;aalg-&gt;alg_name
comma
id|crypto_tfm_alg_digestsize
c_func
(paren
id|ahp-&gt;tfm
)paren
comma
id|aalg_desc-&gt;uinfo.auth.icv_fullbits
op_div
l_int|8
)paren
suffix:semicolon
r_goto
id|error
suffix:semicolon
)brace
id|ahp-&gt;icv_full_len
op_assign
id|aalg_desc-&gt;uinfo.auth.icv_fullbits
op_div
l_int|8
suffix:semicolon
id|ahp-&gt;icv_trunc_len
op_assign
id|aalg_desc-&gt;uinfo.auth.icv_truncbits
op_div
l_int|8
suffix:semicolon
id|BUG_ON
c_func
(paren
id|ahp-&gt;icv_trunc_len
OG
id|MAX_AH_AUTH_LEN
)paren
suffix:semicolon
id|ahp-&gt;work_icv
op_assign
id|kmalloc
c_func
(paren
id|ahp-&gt;icv_full_len
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ahp-&gt;work_icv
)paren
r_goto
id|error
suffix:semicolon
id|x-&gt;props.header_len
op_assign
id|XFRM_ALIGN8
c_func
(paren
r_sizeof
(paren
r_struct
id|ipv6_auth_hdr
)paren
op_plus
id|ahp-&gt;icv_trunc_len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|x-&gt;props.mode
)paren
id|x-&gt;props.header_len
op_add_assign
r_sizeof
(paren
r_struct
id|ipv6hdr
)paren
suffix:semicolon
id|x-&gt;data
op_assign
id|ahp
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|error
suffix:colon
r_if
c_cond
(paren
id|ahp
)paren
(brace
r_if
c_cond
(paren
id|ahp-&gt;work_icv
)paren
id|kfree
c_func
(paren
id|ahp-&gt;work_icv
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ahp-&gt;tfm
)paren
id|crypto_free_tfm
c_func
(paren
id|ahp-&gt;tfm
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|ahp
)paren
suffix:semicolon
)brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|ah6_destroy
r_static
r_void
id|ah6_destroy
c_func
(paren
r_struct
id|xfrm_state
op_star
id|x
)paren
(brace
r_struct
id|ah_data
op_star
id|ahp
op_assign
id|x-&gt;data
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ahp
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|ahp-&gt;work_icv
)paren
(brace
id|kfree
c_func
(paren
id|ahp-&gt;work_icv
)paren
suffix:semicolon
id|ahp-&gt;work_icv
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ahp-&gt;tfm
)paren
(brace
id|crypto_free_tfm
c_func
(paren
id|ahp-&gt;tfm
)paren
suffix:semicolon
id|ahp-&gt;tfm
op_assign
l_int|NULL
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|ahp
)paren
suffix:semicolon
)brace
DECL|variable|ah6_type
r_static
r_struct
id|xfrm_type
id|ah6_type
op_assign
(brace
dot
id|description
op_assign
l_string|&quot;AH6&quot;
comma
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|proto
op_assign
id|IPPROTO_AH
comma
dot
id|init_state
op_assign
id|ah6_init_state
comma
dot
id|destructor
op_assign
id|ah6_destroy
comma
dot
id|input
op_assign
id|ah6_input
comma
dot
id|output
op_assign
id|ah6_output
)brace
suffix:semicolon
DECL|variable|ah6_protocol
r_static
r_struct
id|inet6_protocol
id|ah6_protocol
op_assign
(brace
dot
id|handler
op_assign
id|xfrm6_rcv
comma
dot
id|err_handler
op_assign
id|ah6_err
comma
dot
id|flags
op_assign
id|INET6_PROTO_NOPOLICY
comma
)brace
suffix:semicolon
DECL|function|ah6_init
r_static
r_int
id|__init
id|ah6_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|xfrm_register_type
c_func
(paren
op_amp
id|ah6_type
comma
id|AF_INET6
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;ipv6 ah init: can&squot;t add xfrm type&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EAGAIN
suffix:semicolon
)brace
r_if
c_cond
(paren
id|inet6_add_protocol
c_func
(paren
op_amp
id|ah6_protocol
comma
id|IPPROTO_AH
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;ipv6 ah init: can&squot;t add protocol&bslash;n&quot;
)paren
suffix:semicolon
id|xfrm_unregister_type
c_func
(paren
op_amp
id|ah6_type
comma
id|AF_INET6
)paren
suffix:semicolon
r_return
op_minus
id|EAGAIN
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ah6_fini
r_static
r_void
id|__exit
id|ah6_fini
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|inet6_del_protocol
c_func
(paren
op_amp
id|ah6_protocol
comma
id|IPPROTO_AH
)paren
OL
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;ipv6 ah close: can&squot;t remove protocol&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|xfrm_unregister_type
c_func
(paren
op_amp
id|ah6_type
comma
id|AF_INET6
)paren
OL
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;ipv6 ah close: can&squot;t remove xfrm type&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|variable|ah6_init
id|module_init
c_func
(paren
id|ah6_init
)paren
suffix:semicolon
DECL|variable|ah6_fini
id|module_exit
c_func
(paren
id|ah6_fini
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
