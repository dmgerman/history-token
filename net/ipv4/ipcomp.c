multiline_comment|/*&n; * IP Payload Compression Protocol (IPComp) - RFC3173.&n; *&n; * Copyright (c) 2003 James Morris &lt;jmorris@intercode.com.au&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the Free&n; * Software Foundation; either version 2 of the License, or (at your option) &n; * any later version.&n; *&n; * Todo:&n; *   - Tunable compression parameters.&n; *   - Compression stats.&n; *   - Adaptive compression.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;asm/scatterlist.h&gt;
macro_line|#include &lt;linux/crypto.h&gt;
macro_line|#include &lt;linux/pfkeyv2.h&gt;
macro_line|#include &lt;net/ip.h&gt;
macro_line|#include &lt;net/xfrm.h&gt;
macro_line|#include &lt;net/icmp.h&gt;
macro_line|#include &lt;net/esp.h&gt;
macro_line|#include &lt;net/ipcomp.h&gt;
DECL|function|ipcomp_decompress
r_static
r_int
id|ipcomp_decompress
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
comma
id|plen
comma
id|dlen
suffix:semicolon
r_struct
id|iphdr
op_star
id|iph
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
r_goto
id|out
suffix:semicolon
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
id|ip_comp_hdr
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
r_goto
id|out
suffix:semicolon
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
id|skb-&gt;nh.iph
suffix:semicolon
id|iph-&gt;tot_len
op_assign
id|htons
c_func
(paren
id|dlen
op_plus
id|iph-&gt;ihl
op_star
l_int|4
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|err
suffix:semicolon
)brace
DECL|function|ipcomp_input
r_static
r_int
id|ipcomp_input
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
id|u8
id|nexthdr
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
r_struct
id|iphdr
op_star
id|iph
suffix:semicolon
r_union
(brace
r_struct
id|iphdr
id|iph
suffix:semicolon
r_char
id|buf
(braket
l_int|60
)braket
suffix:semicolon
)brace
id|tmp_iph
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
id|skb-&gt;nh.iph
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|tmp_iph
comma
id|iph
comma
id|iph-&gt;ihl
op_star
l_int|4
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
id|ip_comp_hdr
)paren
)paren
suffix:semicolon
id|skb-&gt;nh.raw
op_add_assign
r_sizeof
(paren
r_struct
id|ip_comp_hdr
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|skb-&gt;nh.raw
comma
op_amp
id|tmp_iph
comma
id|tmp_iph.iph.ihl
op_star
l_int|4
)paren
suffix:semicolon
id|iph
op_assign
id|skb-&gt;nh.iph
suffix:semicolon
id|iph-&gt;tot_len
op_assign
id|htons
c_func
(paren
id|ntohs
c_func
(paren
id|iph-&gt;tot_len
)paren
op_minus
r_sizeof
(paren
r_struct
id|ip_comp_hdr
)paren
)paren
suffix:semicolon
id|iph-&gt;protocol
op_assign
id|nexthdr
suffix:semicolon
id|skb-&gt;h.raw
op_assign
id|skb-&gt;data
suffix:semicolon
id|err
op_assign
id|ipcomp_decompress
c_func
(paren
id|x
comma
id|skb
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|err
suffix:semicolon
)brace
DECL|function|ipcomp_compress
r_static
r_int
id|ipcomp_compress
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
comma
id|plen
comma
id|dlen
comma
id|ihlen
suffix:semicolon
r_struct
id|iphdr
op_star
id|iph
op_assign
id|skb-&gt;nh.iph
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
id|ihlen
op_assign
id|iph-&gt;ihl
op_star
l_int|4
suffix:semicolon
id|plen
op_assign
id|skb-&gt;len
op_minus
id|ihlen
suffix:semicolon
id|dlen
op_assign
id|IPCOMP_SCRATCH_SIZE
suffix:semicolon
id|start
op_assign
id|skb-&gt;data
op_plus
id|ihlen
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
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
(paren
id|dlen
op_plus
r_sizeof
(paren
r_struct
id|ip_comp_hdr
)paren
)paren
op_ge
id|plen
)paren
(brace
id|err
op_assign
op_minus
id|EMSGSIZE
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|memcpy
c_func
(paren
id|start
comma
id|scratch
comma
id|dlen
)paren
suffix:semicolon
id|pskb_trim
c_func
(paren
id|skb
comma
id|ihlen
op_plus
id|dlen
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|err
suffix:semicolon
)brace
DECL|function|ipcomp_tunnel_encap
r_static
r_void
id|ipcomp_tunnel_encap
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
r_struct
id|dst_entry
op_star
id|dst
op_assign
id|skb-&gt;dst
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
id|top_iph
op_assign
(paren
r_struct
id|iphdr
op_star
)paren
id|skb_push
c_func
(paren
id|skb
comma
r_sizeof
(paren
r_struct
id|iphdr
)paren
)paren
suffix:semicolon
id|top_iph-&gt;ihl
op_assign
l_int|5
suffix:semicolon
id|top_iph-&gt;version
op_assign
l_int|4
suffix:semicolon
id|top_iph-&gt;tos
op_assign
id|iph-&gt;tos
suffix:semicolon
id|top_iph-&gt;tot_len
op_assign
id|htons
c_func
(paren
id|skb-&gt;len
)paren
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
id|iph-&gt;ttl
suffix:semicolon
id|top_iph-&gt;check
op_assign
l_int|0
suffix:semicolon
id|top_iph-&gt;saddr
op_assign
id|x-&gt;props.saddr.a4
suffix:semicolon
id|top_iph-&gt;daddr
op_assign
id|x-&gt;id.daddr.a4
suffix:semicolon
id|top_iph-&gt;frag_off
op_assign
id|iph-&gt;frag_off
op_amp
op_complement
id|htons
c_func
(paren
id|IP_MF
op_or
id|IP_OFFSET
)paren
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
id|skb-&gt;nh.raw
op_assign
id|skb-&gt;data
suffix:semicolon
)brace
DECL|function|ipcomp_output
r_static
r_int
id|ipcomp_output
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
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
r_struct
id|ip_comp_hdr
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
r_union
(brace
r_struct
id|iphdr
id|iph
suffix:semicolon
r_char
id|buf
(braket
l_int|60
)braket
suffix:semicolon
)brace
id|tmp_iph
suffix:semicolon
r_int
id|hdr_len
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|skb-&gt;ip_summed
op_eq
id|CHECKSUM_HW
op_logical_and
id|skb_checksum_help
c_func
(paren
id|skb
)paren
op_eq
l_int|NULL
)paren
(brace
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
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
id|xfrm_check_output
c_func
(paren
id|x
comma
id|skb
comma
id|AF_INET
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
multiline_comment|/* Don&squot;t bother compressing */
r_if
c_cond
(paren
op_logical_neg
id|x-&gt;props.mode
)paren
(brace
id|iph
op_assign
id|skb-&gt;nh.iph
suffix:semicolon
id|hdr_len
op_assign
id|iph-&gt;ihl
op_star
l_int|4
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|skb-&gt;len
op_minus
id|hdr_len
)paren
OL
id|ipcd-&gt;threshold
)paren
(brace
r_if
c_cond
(paren
id|x-&gt;props.mode
)paren
(brace
id|ipcomp_tunnel_encap
c_func
(paren
id|x
comma
id|skb
)paren
suffix:semicolon
id|iph
op_assign
id|skb-&gt;nh.iph
suffix:semicolon
id|iph-&gt;protocol
op_assign
id|IPPROTO_IPIP
suffix:semicolon
id|ip_send_check
c_func
(paren
id|iph
)paren
suffix:semicolon
)brace
r_goto
id|out_ok
suffix:semicolon
)brace
r_if
c_cond
(paren
id|x-&gt;props.mode
)paren
id|ipcomp_tunnel_encap
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
id|error
suffix:semicolon
)brace
id|err
op_assign
id|ipcomp_compress
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
(brace
r_if
c_cond
(paren
id|err
op_eq
op_minus
id|EMSGSIZE
)paren
(brace
r_if
c_cond
(paren
id|x-&gt;props.mode
)paren
(brace
id|iph
op_assign
id|skb-&gt;nh.iph
suffix:semicolon
id|iph-&gt;protocol
op_assign
id|IPPROTO_IPIP
suffix:semicolon
id|ip_send_check
c_func
(paren
id|iph
)paren
suffix:semicolon
)brace
r_goto
id|out_ok
suffix:semicolon
)brace
r_goto
id|error
suffix:semicolon
)brace
multiline_comment|/* Install ipcomp header, convert into ipcomp datagram. */
id|iph
op_assign
id|skb-&gt;nh.iph
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|tmp_iph
comma
id|iph
comma
id|iph-&gt;ihl
op_star
l_int|4
)paren
suffix:semicolon
id|top_iph
op_assign
(paren
r_struct
id|iphdr
op_star
)paren
id|skb_push
c_func
(paren
id|skb
comma
r_sizeof
(paren
r_struct
id|ip_comp_hdr
)paren
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|top_iph
comma
op_amp
id|tmp_iph
comma
id|iph-&gt;ihl
op_star
l_int|4
)paren
suffix:semicolon
id|iph
op_assign
id|top_iph
suffix:semicolon
id|iph-&gt;tot_len
op_assign
id|htons
c_func
(paren
id|skb-&gt;len
)paren
suffix:semicolon
id|iph-&gt;protocol
op_assign
id|IPPROTO_COMP
suffix:semicolon
id|iph-&gt;check
op_assign
l_int|0
suffix:semicolon
id|ipch
op_assign
(paren
r_struct
id|ip_comp_hdr
op_star
)paren
(paren
(paren
r_char
op_star
)paren
id|iph
op_plus
id|iph-&gt;ihl
op_star
l_int|4
)paren
suffix:semicolon
id|ipch-&gt;nexthdr
op_assign
id|x-&gt;props.mode
ques
c_cond
id|IPPROTO_IPIP
suffix:colon
id|tmp_iph.iph.protocol
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
id|ip_send_check
c_func
(paren
id|iph
)paren
suffix:semicolon
id|skb-&gt;nh.raw
op_assign
id|skb-&gt;data
suffix:semicolon
id|out_ok
suffix:colon
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
(paren
id|skb-&gt;dst
op_assign
id|dst_pop
c_func
(paren
id|dst
)paren
)paren
op_eq
l_int|NULL
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
DECL|function|ipcomp4_err
r_static
r_void
id|ipcomp4_err
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
id|u32
id|info
)paren
(brace
id|u32
id|spi
suffix:semicolon
r_struct
id|iphdr
op_star
id|iph
op_assign
(paren
r_struct
id|iphdr
op_star
)paren
id|skb-&gt;data
suffix:semicolon
r_struct
id|ip_comp_hdr
op_star
id|ipch
op_assign
(paren
r_struct
id|ip_comp_hdr
op_star
)paren
(paren
id|skb-&gt;data
op_plus
(paren
id|iph-&gt;ihl
op_lshift
l_int|2
)paren
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
id|skb-&gt;h.icmph-&gt;type
op_ne
id|ICMP_DEST_UNREACH
op_logical_or
id|skb-&gt;h.icmph-&gt;code
op_ne
id|ICMP_FRAG_NEEDED
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
id|ipch-&gt;cpi
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
id|AF_INET
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
l_string|&quot;pmtu discovery on SA IPCOMP/%08x/%u.%u.%u.%u&bslash;n&quot;
comma
id|spi
comma
id|NIPQUAD
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
multiline_comment|/* We always hold one tunnel user reference to indicate a tunnel */
DECL|function|ipcomp_tunnel_create
r_static
r_struct
id|xfrm_state
op_star
id|ipcomp_tunnel_create
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
id|t
op_eq
l_int|NULL
)paren
r_goto
id|out
suffix:semicolon
id|t-&gt;id.proto
op_assign
id|IPPROTO_IPIP
suffix:semicolon
id|t-&gt;id.spi
op_assign
id|x-&gt;props.saddr.a4
suffix:semicolon
id|t-&gt;id.daddr.a4
op_assign
id|x-&gt;id.daddr.a4
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
id|AF_INET
suffix:semicolon
id|t-&gt;props.mode
op_assign
l_int|1
suffix:semicolon
id|t-&gt;props.saddr.a4
op_assign
id|x-&gt;props.saddr.a4
suffix:semicolon
id|t-&gt;type
op_assign
id|xfrm_get_type
c_func
(paren
id|IPPROTO_IPIP
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
id|t
op_assign
l_int|NULL
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/*&n; * Must be protected by xfrm_cfg_sem.  State and tunnel user references are&n; * always incremented on success.&n; */
DECL|function|ipcomp_tunnel_attach
r_static
r_int
id|ipcomp_tunnel_attach
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
suffix:semicolon
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
id|x-&gt;id.daddr.a4
comma
id|x-&gt;props.saddr.a4
comma
id|IPPROTO_IPIP
comma
id|AF_INET
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
id|ipcomp_tunnel_create
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
DECL|function|ipcomp_free_data
r_static
r_void
id|ipcomp_free_data
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
DECL|function|ipcomp_destroy
r_static
r_void
id|ipcomp_destroy
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
id|ipcomp_free_data
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
DECL|function|ipcomp_init_state
r_static
r_int
id|ipcomp_init_state
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
op_assign
op_minus
id|ENOMEM
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
r_sizeof
(paren
r_struct
id|ip_comp_hdr
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
id|iphdr
)paren
suffix:semicolon
id|x-&gt;data
op_assign
id|ipcd
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
id|ipcomp_tunnel_attach
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
id|ipcomp_free_data
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
DECL|variable|ipcomp_type
r_static
r_struct
id|xfrm_type
id|ipcomp_type
op_assign
(brace
dot
id|description
op_assign
l_string|&quot;IPCOMP4&quot;
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
id|ipcomp_init_state
comma
dot
id|destructor
op_assign
id|ipcomp_destroy
comma
dot
id|input
op_assign
id|ipcomp_input
comma
dot
id|output
op_assign
id|ipcomp_output
)brace
suffix:semicolon
DECL|variable|ipcomp4_protocol
r_static
r_struct
id|inet_protocol
id|ipcomp4_protocol
op_assign
(brace
dot
id|handler
op_assign
id|xfrm4_rcv
comma
dot
id|err_handler
op_assign
id|ipcomp4_err
comma
dot
id|no_policy
op_assign
l_int|1
comma
)brace
suffix:semicolon
DECL|function|ipcomp4_init
r_static
r_int
id|__init
id|ipcomp4_init
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
id|ipcomp_type
comma
id|AF_INET
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;ipcomp init: can&squot;t add xfrm type&bslash;n&quot;
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
id|inet_add_protocol
c_func
(paren
op_amp
id|ipcomp4_protocol
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
l_string|&quot;ipcomp init: can&squot;t add protocol&bslash;n&quot;
)paren
suffix:semicolon
id|xfrm_unregister_type
c_func
(paren
op_amp
id|ipcomp_type
comma
id|AF_INET
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
DECL|function|ipcomp4_fini
r_static
r_void
id|__exit
id|ipcomp4_fini
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|inet_del_protocol
c_func
(paren
op_amp
id|ipcomp4_protocol
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
l_string|&quot;ip ipcomp close: can&squot;t remove protocol&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|xfrm_unregister_type
c_func
(paren
op_amp
id|ipcomp_type
comma
id|AF_INET
)paren
OL
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;ip ipcomp close: can&squot;t remove xfrm type&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|variable|ipcomp4_init
id|module_init
c_func
(paren
id|ipcomp4_init
)paren
suffix:semicolon
DECL|variable|ipcomp4_fini
id|module_exit
c_func
(paren
id|ipcomp4_fini
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
l_string|&quot;IP Payload Compression Protocol (IPComp) - RFC3173&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;James Morris &lt;jmorris@intercode.com.au&gt;&quot;
)paren
suffix:semicolon
eof
