multiline_comment|/*&n; * IP Payload Compression Protocol (IPComp) for IPv6 - RFC3173&n; *&n; * Copyright (C)2003 USAGI/WIDE Project&n; *&n; * Author&t;Mitsuru KANDA  &lt;mk@linux-ipv6.org&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; * &n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
multiline_comment|/* &n; * [Memo]&n; *&n; * Outbound:&n; *  The compression of IP datagram MUST be done before AH/ESP processing, &n; *  fragmentation, and the addition of Hop-by-Hop/Routing header. &n; *&n; * Inbound:&n; *  The decompression of IP datagram MUST be done after the reassembly, &n; *  AH/ESP processing.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;net/inet_ecn.h&gt;
macro_line|#include &lt;net/ip.h&gt;
macro_line|#include &lt;net/xfrm.h&gt;
macro_line|#include &lt;net/ipcomp.h&gt;
macro_line|#include &lt;asm/scatterlist.h&gt;
macro_line|#include &lt;linux/crypto.h&gt;
macro_line|#include &lt;linux/pfkeyv2.h&gt;
macro_line|#include &lt;linux/random.h&gt;
macro_line|#include &lt;net/icmp.h&gt;
macro_line|#include &lt;net/ipv6.h&gt;
macro_line|#include &lt;linux/ipv6.h&gt;
macro_line|#include &lt;linux/icmpv6.h&gt;
DECL|function|ipcomp6_input
r_static
r_int
id|ipcomp6_input
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
r_int
id|err
op_assign
l_int|0
suffix:semicolon
id|u8
id|nexthdr
op_assign
l_int|0
suffix:semicolon
r_int
id|hdr_len
op_assign
id|skb-&gt;h.raw
op_minus
id|skb-&gt;nh.raw
suffix:semicolon
r_int
r_char
op_star
id|tmp_hdr
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|ipv6hdr
op_star
id|iph
suffix:semicolon
r_int
id|plen
comma
id|dlen
suffix:semicolon
r_struct
id|ipcomp_data
op_star
id|ipcd
op_assign
id|x-&gt;data
suffix:semicolon
id|u8
op_star
id|start
comma
op_star
id|scratch
op_assign
id|ipcd-&gt;scratch
suffix:semicolon
r_if
c_cond
(paren
(paren
id|skb_is_nonlinear
c_func
(paren
id|skb
)paren
op_logical_or
id|skb_cloned
c_func
(paren
id|skb
)paren
)paren
op_logical_and
id|skb_linearize
c_func
(paren
id|skb
comma
id|GFP_ATOMIC
)paren
op_ne
l_int|0
)paren
(brace
id|err
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|skb-&gt;ip_summed
op_assign
id|CHECKSUM_NONE
suffix:semicolon
multiline_comment|/* Remove ipcomp header and decompress original payload */
id|iph
op_assign
id|skb-&gt;nh.ipv6h
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
id|iph
comma
id|hdr_len
)paren
suffix:semicolon
id|nexthdr
op_assign
op_star
(paren
id|u8
op_star
)paren
id|skb-&gt;data
suffix:semicolon
id|skb_pull
c_func
(paren
id|skb
comma
r_sizeof
(paren
r_struct
id|ipv6_comp_hdr
)paren
)paren
suffix:semicolon
id|skb-&gt;nh.raw
op_add_assign
r_sizeof
(paren
r_struct
id|ipv6_comp_hdr
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
id|iph
op_assign
id|skb-&gt;nh.ipv6h
suffix:semicolon
id|iph-&gt;payload_len
op_assign
id|htons
c_func
(paren
id|ntohs
c_func
(paren
id|iph-&gt;payload_len
)paren
op_minus
r_sizeof
(paren
r_struct
id|ipv6_comp_hdr
)paren
)paren
suffix:semicolon
id|skb-&gt;h.raw
op_assign
id|skb-&gt;data
suffix:semicolon
multiline_comment|/* decompression */
id|plen
op_assign
id|skb-&gt;len
suffix:semicolon
id|dlen
op_assign
id|IPCOMP_SCRATCH_SIZE
suffix:semicolon
id|start
op_assign
id|skb-&gt;data
suffix:semicolon
id|err
op_assign
id|crypto_comp_decompress
c_func
(paren
id|ipcd-&gt;tfm
comma
id|start
comma
id|plen
comma
id|scratch
comma
op_amp
id|dlen
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dlen
OL
(paren
id|plen
op_plus
r_sizeof
(paren
r_struct
id|ipv6_comp_hdr
)paren
)paren
)paren
(brace
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|err
op_assign
id|pskb_expand_head
c_func
(paren
id|skb
comma
l_int|0
comma
id|dlen
op_minus
id|plen
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
r_goto
id|out
suffix:semicolon
)brace
id|skb_put
c_func
(paren
id|skb
comma
id|dlen
op_minus
id|plen
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|skb-&gt;data
comma
id|scratch
comma
id|dlen
)paren
suffix:semicolon
id|iph
op_assign
id|skb-&gt;nh.ipv6h
suffix:semicolon
id|iph-&gt;payload_len
op_assign
id|htons
c_func
(paren
id|skb-&gt;len
)paren
suffix:semicolon
id|out
suffix:colon
r_if
c_cond
(paren
id|tmp_hdr
)paren
id|kfree
c_func
(paren
id|tmp_hdr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|error_out
suffix:semicolon
r_return
id|nexthdr
suffix:semicolon
id|error_out
suffix:colon
r_return
id|err
suffix:semicolon
)brace
DECL|function|ipcomp6_output
r_static
r_int
id|ipcomp6_output
c_func
(paren
r_struct
id|sk_buff
op_star
op_star
id|pskb
)paren
(brace
r_int
id|err
suffix:semicolon
r_struct
id|dst_entry
op_star
id|dst
op_assign
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|dst
suffix:semicolon
r_struct
id|xfrm_state
op_star
id|x
op_assign
id|dst-&gt;xfrm
suffix:semicolon
r_struct
id|ipv6hdr
op_star
id|top_iph
suffix:semicolon
r_int
id|hdr_len
suffix:semicolon
r_struct
id|ipv6_comp_hdr
op_star
id|ipch
suffix:semicolon
r_struct
id|ipcomp_data
op_star
id|ipcd
op_assign
id|x-&gt;data
suffix:semicolon
r_int
id|plen
comma
id|dlen
suffix:semicolon
id|u8
op_star
id|start
comma
op_star
id|scratch
op_assign
id|ipcd-&gt;scratch
suffix:semicolon
id|hdr_len
op_assign
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|h.raw
op_minus
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|data
suffix:semicolon
multiline_comment|/* check whether datagram len is larger than threshold */
r_if
c_cond
(paren
(paren
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|len
op_minus
id|hdr_len
)paren
OL
id|ipcd-&gt;threshold
)paren
(brace
r_goto
id|out_ok
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|skb_is_nonlinear
c_func
(paren
op_star
id|pskb
)paren
op_logical_or
id|skb_cloned
c_func
(paren
op_star
id|pskb
)paren
)paren
op_logical_and
id|skb_linearize
c_func
(paren
op_star
id|pskb
comma
id|GFP_ATOMIC
)paren
op_ne
l_int|0
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
multiline_comment|/* compression */
id|plen
op_assign
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|len
op_minus
id|hdr_len
suffix:semicolon
id|dlen
op_assign
id|IPCOMP_SCRATCH_SIZE
suffix:semicolon
id|start
op_assign
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|h.raw
suffix:semicolon
id|err
op_assign
id|crypto_comp_compress
c_func
(paren
id|ipcd-&gt;tfm
comma
id|start
comma
id|plen
comma
id|scratch
comma
op_amp
id|dlen
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
r_goto
id|error
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|dlen
op_plus
r_sizeof
(paren
r_struct
id|ipv6_comp_hdr
)paren
)paren
op_ge
id|plen
)paren
(brace
r_goto
id|out_ok
suffix:semicolon
)brace
id|memcpy
c_func
(paren
id|start
op_plus
r_sizeof
(paren
r_struct
id|ip_comp_hdr
)paren
comma
id|scratch
comma
id|dlen
)paren
suffix:semicolon
id|pskb_trim
c_func
(paren
op_star
id|pskb
comma
id|hdr_len
op_plus
id|dlen
op_plus
r_sizeof
(paren
r_struct
id|ip_comp_hdr
)paren
)paren
suffix:semicolon
multiline_comment|/* insert ipcomp header and replace datagram */
id|top_iph
op_assign
(paren
r_struct
id|ipv6hdr
op_star
)paren
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|data
suffix:semicolon
id|top_iph-&gt;payload_len
op_assign
id|htons
c_func
(paren
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|len
op_minus
r_sizeof
(paren
r_struct
id|ipv6hdr
)paren
)paren
suffix:semicolon
id|ipch
op_assign
(paren
r_struct
id|ipv6_comp_hdr
op_star
)paren
id|start
suffix:semicolon
id|ipch-&gt;nexthdr
op_assign
op_star
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nh.raw
suffix:semicolon
id|ipch-&gt;flags
op_assign
l_int|0
suffix:semicolon
id|ipch-&gt;cpi
op_assign
id|htons
c_func
(paren
(paren
id|u16
)paren
id|ntohl
c_func
(paren
id|x-&gt;id.spi
)paren
)paren
suffix:semicolon
op_star
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nh.raw
op_assign
id|IPPROTO_COMP
suffix:semicolon
id|out_ok
suffix:colon
id|err
op_assign
l_int|0
suffix:semicolon
id|error
suffix:colon
r_return
id|err
suffix:semicolon
)brace
DECL|function|ipcomp6_err
r_static
r_void
id|ipcomp6_err
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
id|u32
id|spi
suffix:semicolon
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
id|ipv6_comp_hdr
op_star
id|ipcomph
op_assign
(paren
r_struct
id|ipv6_comp_hdr
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
id|spi
op_assign
id|ntohl
c_func
(paren
id|ntohs
c_func
(paren
id|ipcomph-&gt;cpi
)paren
)paren
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
id|spi
comma
id|IPPROTO_COMP
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
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;pmtu discovery on SA IPCOMP/%08x/&quot;
l_string|&quot;%04x:%04x:%04x:%04x:%04x:%04x:%04x:%04x&bslash;n&quot;
comma
id|spi
comma
id|NIP6
c_func
(paren
id|iph-&gt;daddr
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
DECL|function|ipcomp6_tunnel_create
r_static
r_struct
id|xfrm_state
op_star
id|ipcomp6_tunnel_create
c_func
(paren
r_struct
id|xfrm_state
op_star
id|x
)paren
(brace
r_struct
id|xfrm_state
op_star
id|t
op_assign
l_int|NULL
suffix:semicolon
id|t
op_assign
id|xfrm_state_alloc
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|t
)paren
r_goto
id|out
suffix:semicolon
id|t-&gt;id.proto
op_assign
id|IPPROTO_IPV6
suffix:semicolon
id|t-&gt;id.spi
op_assign
id|xfrm6_tunnel_alloc_spi
c_func
(paren
(paren
id|xfrm_address_t
op_star
)paren
op_amp
id|x-&gt;props.saddr
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|t-&gt;id.daddr.a6
comma
id|x-&gt;id.daddr.a6
comma
r_sizeof
(paren
r_struct
id|in6_addr
)paren
)paren
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|t-&gt;sel
comma
op_amp
id|x-&gt;sel
comma
r_sizeof
(paren
id|t-&gt;sel
)paren
)paren
suffix:semicolon
id|t-&gt;props.family
op_assign
id|AF_INET6
suffix:semicolon
id|t-&gt;props.mode
op_assign
l_int|1
suffix:semicolon
id|memcpy
c_func
(paren
id|t-&gt;props.saddr.a6
comma
id|x-&gt;props.saddr.a6
comma
r_sizeof
(paren
r_struct
id|in6_addr
)paren
)paren
suffix:semicolon
id|t-&gt;type
op_assign
id|xfrm_get_type
c_func
(paren
id|IPPROTO_IPV6
comma
id|t-&gt;props.family
)paren
suffix:semicolon
r_if
c_cond
(paren
id|t-&gt;type
op_eq
l_int|NULL
)paren
r_goto
id|error
suffix:semicolon
r_if
c_cond
(paren
id|t-&gt;type
op_member_access_from_pointer
id|init_state
c_func
(paren
id|t
comma
l_int|NULL
)paren
)paren
r_goto
id|error
suffix:semicolon
id|t-&gt;km.state
op_assign
id|XFRM_STATE_VALID
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|t-&gt;tunnel_users
comma
l_int|1
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|t
suffix:semicolon
id|error
suffix:colon
id|xfrm_state_put
c_func
(paren
id|t
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
DECL|function|ipcomp6_tunnel_attach
r_static
r_int
id|ipcomp6_tunnel_attach
c_func
(paren
r_struct
id|xfrm_state
op_star
id|x
)paren
(brace
r_int
id|err
op_assign
l_int|0
suffix:semicolon
r_struct
id|xfrm_state
op_star
id|t
op_assign
l_int|NULL
suffix:semicolon
id|u32
id|spi
suffix:semicolon
id|spi
op_assign
id|xfrm6_tunnel_spi_lookup
c_func
(paren
(paren
id|xfrm_address_t
op_star
)paren
op_amp
id|x-&gt;props.saddr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|spi
)paren
id|t
op_assign
id|xfrm_state_lookup
c_func
(paren
(paren
id|xfrm_address_t
op_star
)paren
op_amp
id|x-&gt;id.daddr
comma
id|spi
comma
id|IPPROTO_IPV6
comma
id|AF_INET6
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|t
)paren
(brace
id|t
op_assign
id|ipcomp6_tunnel_create
c_func
(paren
id|x
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|t
)paren
(brace
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|xfrm_state_insert
c_func
(paren
id|t
)paren
suffix:semicolon
id|xfrm_state_hold
c_func
(paren
id|t
)paren
suffix:semicolon
)brace
id|x-&gt;tunnel
op_assign
id|t
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|t-&gt;tunnel_users
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|err
suffix:semicolon
)brace
DECL|function|ipcomp6_free_data
r_static
r_void
id|ipcomp6_free_data
c_func
(paren
r_struct
id|ipcomp_data
op_star
id|ipcd
)paren
(brace
r_if
c_cond
(paren
id|ipcd-&gt;tfm
)paren
id|crypto_free_tfm
c_func
(paren
id|ipcd-&gt;tfm
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ipcd-&gt;scratch
)paren
id|kfree
c_func
(paren
id|ipcd-&gt;scratch
)paren
suffix:semicolon
)brace
DECL|function|ipcomp6_destroy
r_static
r_void
id|ipcomp6_destroy
c_func
(paren
r_struct
id|xfrm_state
op_star
id|x
)paren
(brace
r_struct
id|ipcomp_data
op_star
id|ipcd
op_assign
id|x-&gt;data
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ipcd
)paren
r_return
suffix:semicolon
id|xfrm_state_delete_tunnel
c_func
(paren
id|x
)paren
suffix:semicolon
id|ipcomp6_free_data
c_func
(paren
id|ipcd
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|ipcd
)paren
suffix:semicolon
id|xfrm6_tunnel_free_spi
c_func
(paren
(paren
id|xfrm_address_t
op_star
)paren
op_amp
id|x-&gt;props.saddr
)paren
suffix:semicolon
)brace
DECL|function|ipcomp6_init_state
r_static
r_int
id|ipcomp6_init_state
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
r_int
id|err
suffix:semicolon
r_struct
id|ipcomp_data
op_star
id|ipcd
suffix:semicolon
r_struct
id|xfrm_algo_desc
op_star
id|calg_desc
suffix:semicolon
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|x-&gt;calg
)paren
r_goto
id|out
suffix:semicolon
id|err
op_assign
op_minus
id|ENOMEM
suffix:semicolon
id|ipcd
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|ipcd
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ipcd
)paren
r_goto
id|error
suffix:semicolon
id|memset
c_func
(paren
id|ipcd
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|ipcd
)paren
)paren
suffix:semicolon
id|x-&gt;props.header_len
op_assign
l_int|0
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
id|ipcd-&gt;scratch
op_assign
id|kmalloc
c_func
(paren
id|IPCOMP_SCRATCH_SIZE
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ipcd-&gt;scratch
)paren
r_goto
id|error
suffix:semicolon
id|ipcd-&gt;tfm
op_assign
id|crypto_alloc_tfm
c_func
(paren
id|x-&gt;calg-&gt;alg_name
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ipcd-&gt;tfm
)paren
r_goto
id|error
suffix:semicolon
r_if
c_cond
(paren
id|x-&gt;props.mode
)paren
(brace
id|err
op_assign
id|ipcomp6_tunnel_attach
c_func
(paren
id|x
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
)brace
id|calg_desc
op_assign
id|xfrm_calg_get_byname
c_func
(paren
id|x-&gt;calg-&gt;alg_name
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
op_logical_neg
id|calg_desc
)paren
suffix:semicolon
id|ipcd-&gt;threshold
op_assign
id|calg_desc-&gt;uinfo.comp.threshold
suffix:semicolon
id|x-&gt;data
op_assign
id|ipcd
suffix:semicolon
id|err
op_assign
l_int|0
suffix:semicolon
id|out
suffix:colon
r_return
id|err
suffix:semicolon
id|error
suffix:colon
r_if
c_cond
(paren
id|ipcd
)paren
(brace
id|ipcomp6_free_data
c_func
(paren
id|ipcd
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|ipcd
)paren
suffix:semicolon
)brace
r_goto
id|out
suffix:semicolon
)brace
DECL|variable|ipcomp6_type
r_static
r_struct
id|xfrm_type
id|ipcomp6_type
op_assign
(brace
dot
id|description
op_assign
l_string|&quot;IPCOMP6&quot;
comma
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|proto
op_assign
id|IPPROTO_COMP
comma
dot
id|init_state
op_assign
id|ipcomp6_init_state
comma
dot
id|destructor
op_assign
id|ipcomp6_destroy
comma
dot
id|input
op_assign
id|ipcomp6_input
comma
dot
id|output
op_assign
id|ipcomp6_output
comma
)brace
suffix:semicolon
DECL|variable|ipcomp6_protocol
r_static
r_struct
id|inet6_protocol
id|ipcomp6_protocol
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
id|ipcomp6_err
comma
dot
id|flags
op_assign
id|INET6_PROTO_NOPOLICY
comma
)brace
suffix:semicolon
DECL|function|ipcomp6_init
r_static
r_int
id|__init
id|ipcomp6_init
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
id|ipcomp6_type
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
l_string|&quot;ipcomp6 init: can&squot;t add xfrm type&bslash;n&quot;
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
id|ipcomp6_protocol
comma
id|IPPROTO_COMP
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;ipcomp6 init: can&squot;t add protocol&bslash;n&quot;
)paren
suffix:semicolon
id|xfrm_unregister_type
c_func
(paren
op_amp
id|ipcomp6_type
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
DECL|function|ipcomp6_fini
r_static
r_void
id|__exit
id|ipcomp6_fini
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
id|ipcomp6_protocol
comma
id|IPPROTO_COMP
)paren
OL
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;ipv6 ipcomp close: can&squot;t remove protocol&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|xfrm_unregister_type
c_func
(paren
op_amp
id|ipcomp6_type
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
l_string|&quot;ipv6 ipcomp close: can&squot;t remove xfrm type&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|variable|ipcomp6_init
id|module_init
c_func
(paren
id|ipcomp6_init
)paren
suffix:semicolon
DECL|variable|ipcomp6_fini
id|module_exit
c_func
(paren
id|ipcomp6_fini
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;IP Payload Compression Protocol (IPComp) for IPv6 - RFC3173&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Mitsuru KANDA &lt;mk@linux-ipv6.org&gt;&quot;
)paren
suffix:semicolon
eof
