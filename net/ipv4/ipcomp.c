multiline_comment|/*&n; * IP Payload Compression Protocol (IPComp) - RFC3173.&n; *&n; * Copyright (c) 2003 James Morris &lt;jmorris@intercode.com.au&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the Free&n; * Software Foundation; either version 2 of the License, or (at your option) &n; * any later version.&n; *&n; * Todo:&n; *   - Tunable compression parameters.&n; *   - Compression stats.&n; *   - Adaptive compression.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;asm/scatterlist.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
macro_line|#include &lt;linux/crypto.h&gt;
macro_line|#include &lt;linux/pfkeyv2.h&gt;
macro_line|#include &lt;linux/percpu.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/rtnetlink.h&gt;
macro_line|#include &lt;net/ip.h&gt;
macro_line|#include &lt;net/xfrm.h&gt;
macro_line|#include &lt;net/icmp.h&gt;
macro_line|#include &lt;net/ipcomp.h&gt;
DECL|struct|ipcomp_tfms
r_struct
id|ipcomp_tfms
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|tfms
r_struct
id|crypto_tfm
op_star
op_star
id|tfms
suffix:semicolon
DECL|member|users
r_int
id|users
suffix:semicolon
)brace
suffix:semicolon
r_static
id|DECLARE_MUTEX
c_func
(paren
id|ipcomp_resource_sem
)paren
suffix:semicolon
DECL|variable|ipcomp_scratches
r_static
r_void
op_star
op_star
id|ipcomp_scratches
suffix:semicolon
DECL|variable|ipcomp_scratch_users
r_static
r_int
id|ipcomp_scratch_users
suffix:semicolon
r_static
id|LIST_HEAD
c_func
(paren
id|ipcomp_tfms_list
)paren
suffix:semicolon
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
suffix:semicolon
r_struct
id|crypto_tfm
op_star
id|tfm
suffix:semicolon
r_int
id|cpu
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
id|cpu
op_assign
id|get_cpu
c_func
(paren
)paren
suffix:semicolon
id|scratch
op_assign
op_star
id|per_cpu_ptr
c_func
(paren
id|ipcomp_scratches
comma
id|cpu
)paren
suffix:semicolon
id|tfm
op_assign
op_star
id|per_cpu_ptr
c_func
(paren
id|ipcd-&gt;tfms
comma
id|cpu
)paren
suffix:semicolon
id|err
op_assign
id|crypto_comp_decompress
c_func
(paren
id|tfm
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
id|put_cpu
c_func
(paren
)paren
suffix:semicolon
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
suffix:semicolon
r_struct
id|crypto_tfm
op_star
id|tfm
suffix:semicolon
r_int
id|cpu
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
id|cpu
op_assign
id|get_cpu
c_func
(paren
)paren
suffix:semicolon
id|scratch
op_assign
op_star
id|per_cpu_ptr
c_func
(paren
id|ipcomp_scratches
comma
id|cpu
)paren
suffix:semicolon
id|tfm
op_assign
op_star
id|per_cpu_ptr
c_func
(paren
id|ipcd-&gt;tfms
comma
id|cpu
)paren
suffix:semicolon
id|err
op_assign
id|crypto_comp_compress
c_func
(paren
id|tfm
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
id|put_cpu
c_func
(paren
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
op_plus
r_sizeof
(paren
r_struct
id|ip_comp_hdr
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|out
suffix:colon
id|put_cpu
c_func
(paren
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|ipcomp_output
r_static
r_int
id|ipcomp_output
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
r_struct
id|iphdr
op_star
id|iph
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
r_int
id|hdr_len
op_assign
l_int|0
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
id|skb-&gt;len
)paren
suffix:semicolon
id|hdr_len
op_assign
id|iph-&gt;ihl
op_star
l_int|4
suffix:semicolon
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
multiline_comment|/* Don&squot;t bother compressing */
r_if
c_cond
(paren
id|x-&gt;props.mode
)paren
(brace
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
id|iph-&gt;tot_len
op_assign
id|htons
c_func
(paren
id|skb-&gt;len
)paren
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
id|iph-&gt;protocol
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
id|iph-&gt;protocol
op_assign
id|IPPROTO_COMP
suffix:semicolon
id|ip_send_check
c_func
(paren
id|iph
)paren
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
id|NETDEBUG
c_func
(paren
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
id|t-&gt;props.flags
op_assign
id|x-&gt;props.flags
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
id|t-&gt;km.state
op_assign
id|XFRM_STATE_DEAD
suffix:semicolon
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
DECL|function|ipcomp_free_scratches
r_static
r_void
id|ipcomp_free_scratches
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_void
op_star
op_star
id|scratches
suffix:semicolon
r_if
c_cond
(paren
op_decrement
id|ipcomp_scratch_users
)paren
r_return
suffix:semicolon
id|scratches
op_assign
id|ipcomp_scratches
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|scratches
)paren
r_return
suffix:semicolon
id|for_each_cpu
c_func
(paren
id|i
)paren
(brace
r_void
op_star
id|scratch
op_assign
op_star
id|per_cpu_ptr
c_func
(paren
id|scratches
comma
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
id|scratch
)paren
id|vfree
c_func
(paren
id|scratch
)paren
suffix:semicolon
)brace
id|free_percpu
c_func
(paren
id|scratches
)paren
suffix:semicolon
)brace
DECL|function|ipcomp_alloc_scratches
r_static
r_void
op_star
op_star
id|ipcomp_alloc_scratches
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_void
op_star
op_star
id|scratches
suffix:semicolon
r_if
c_cond
(paren
id|ipcomp_scratch_users
op_increment
)paren
r_return
id|ipcomp_scratches
suffix:semicolon
id|scratches
op_assign
id|alloc_percpu
c_func
(paren
r_void
op_star
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|scratches
)paren
r_return
l_int|NULL
suffix:semicolon
id|ipcomp_scratches
op_assign
id|scratches
suffix:semicolon
id|for_each_cpu
c_func
(paren
id|i
)paren
(brace
r_void
op_star
id|scratch
op_assign
id|vmalloc
c_func
(paren
id|IPCOMP_SCRATCH_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|scratch
)paren
r_return
l_int|NULL
suffix:semicolon
op_star
id|per_cpu_ptr
c_func
(paren
id|scratches
comma
id|i
)paren
op_assign
id|scratch
suffix:semicolon
)brace
r_return
id|scratches
suffix:semicolon
)brace
DECL|function|ipcomp_free_tfms
r_static
r_void
id|ipcomp_free_tfms
c_func
(paren
r_struct
id|crypto_tfm
op_star
op_star
id|tfms
)paren
(brace
r_struct
id|ipcomp_tfms
op_star
id|pos
suffix:semicolon
r_int
id|cpu
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|pos
comma
op_amp
id|ipcomp_tfms_list
comma
id|list
)paren
(brace
r_if
c_cond
(paren
id|pos-&gt;tfms
op_eq
id|tfms
)paren
r_break
suffix:semicolon
)brace
id|BUG_TRAP
c_func
(paren
id|pos
)paren
suffix:semicolon
r_if
c_cond
(paren
op_decrement
id|pos-&gt;users
)paren
r_return
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|pos-&gt;list
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|pos
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tfms
)paren
r_return
suffix:semicolon
id|for_each_cpu
c_func
(paren
id|cpu
)paren
(brace
r_struct
id|crypto_tfm
op_star
id|tfm
op_assign
op_star
id|per_cpu_ptr
c_func
(paren
id|tfms
comma
id|cpu
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tfm
)paren
id|crypto_free_tfm
c_func
(paren
id|tfm
)paren
suffix:semicolon
)brace
id|free_percpu
c_func
(paren
id|tfms
)paren
suffix:semicolon
)brace
DECL|function|ipcomp_alloc_tfms
r_static
r_struct
id|crypto_tfm
op_star
op_star
id|ipcomp_alloc_tfms
c_func
(paren
r_const
r_char
op_star
id|alg_name
)paren
(brace
r_struct
id|ipcomp_tfms
op_star
id|pos
suffix:semicolon
r_struct
id|crypto_tfm
op_star
op_star
id|tfms
suffix:semicolon
r_int
id|cpu
suffix:semicolon
multiline_comment|/* This can be any valid CPU ID so we don&squot;t need locking. */
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|pos
comma
op_amp
id|ipcomp_tfms_list
comma
id|list
)paren
(brace
r_struct
id|crypto_tfm
op_star
id|tfm
suffix:semicolon
id|tfms
op_assign
id|pos-&gt;tfms
suffix:semicolon
id|tfm
op_assign
op_star
id|per_cpu_ptr
c_func
(paren
id|tfms
comma
id|cpu
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|crypto_tfm_alg_name
c_func
(paren
id|tfm
)paren
comma
id|alg_name
)paren
)paren
(brace
id|pos-&gt;users
op_increment
suffix:semicolon
r_return
id|tfms
suffix:semicolon
)brace
)brace
id|pos
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|pos
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pos
)paren
r_return
l_int|NULL
suffix:semicolon
id|pos-&gt;users
op_assign
l_int|1
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|pos-&gt;list
)paren
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|pos-&gt;list
comma
op_amp
id|ipcomp_tfms_list
)paren
suffix:semicolon
id|pos-&gt;tfms
op_assign
id|tfms
op_assign
id|alloc_percpu
c_func
(paren
r_struct
id|crypto_tfm
op_star
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tfms
)paren
r_goto
id|error
suffix:semicolon
id|for_each_cpu
c_func
(paren
id|cpu
)paren
(brace
r_struct
id|crypto_tfm
op_star
id|tfm
op_assign
id|crypto_alloc_tfm
c_func
(paren
id|alg_name
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tfm
)paren
r_goto
id|error
suffix:semicolon
op_star
id|per_cpu_ptr
c_func
(paren
id|tfms
comma
id|cpu
)paren
op_assign
id|tfm
suffix:semicolon
)brace
r_return
id|tfms
suffix:semicolon
id|error
suffix:colon
id|ipcomp_free_tfms
c_func
(paren
id|tfms
)paren
suffix:semicolon
r_return
l_int|NULL
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
id|ipcd-&gt;tfms
)paren
id|ipcomp_free_tfms
c_func
(paren
id|ipcd-&gt;tfms
)paren
suffix:semicolon
id|ipcomp_free_scratches
c_func
(paren
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
id|down
c_func
(paren
op_amp
id|ipcomp_resource_sem
)paren
suffix:semicolon
id|ipcomp_free_data
c_func
(paren
id|ipcd
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|ipcomp_resource_sem
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
r_if
c_cond
(paren
id|x-&gt;encap
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
id|out
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
id|iphdr
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|ipcomp_resource_sem
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ipcomp_alloc_scratches
c_func
(paren
)paren
)paren
r_goto
id|error
suffix:semicolon
id|ipcd-&gt;tfms
op_assign
id|ipcomp_alloc_tfms
c_func
(paren
id|x-&gt;calg-&gt;alg_name
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ipcd-&gt;tfms
)paren
r_goto
id|error
suffix:semicolon
id|up
c_func
(paren
op_amp
id|ipcomp_resource_sem
)paren
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
id|error_tunnel
suffix:semicolon
)brace
id|calg_desc
op_assign
id|xfrm_calg_get_byname
c_func
(paren
id|x-&gt;calg-&gt;alg_name
comma
l_int|0
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
id|error_tunnel
suffix:colon
id|down
c_func
(paren
op_amp
id|ipcomp_resource_sem
)paren
suffix:semicolon
id|error
suffix:colon
id|ipcomp_free_data
c_func
(paren
id|ipcd
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|ipcomp_resource_sem
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|ipcd
)paren
suffix:semicolon
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
id|net_protocol
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
