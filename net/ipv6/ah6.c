multiline_comment|/*&n; * Copyright (C)2002 USAGI/WIDE Project&n; * &n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; * &n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; *&n; * Authors&n; *&n; *&t;Mitsuru KANDA @USAGI       : IPv6 Support &n; * &t;Kazunori MIYAZAWA @USAGI   :&n; * &t;Kunihiro Ishiguro          :&n; * &t;&n; * &t;This file is derived from net/ipv4/ah.c.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;net/ip.h&gt;
macro_line|#include &lt;net/xfrm.h&gt;
macro_line|#include &lt;net/ah.h&gt;
macro_line|#include &lt;linux/crypto.h&gt;
macro_line|#include &lt;linux/pfkeyv2.h&gt;
macro_line|#include &lt;net/icmp.h&gt;
macro_line|#include &lt;net/ipv6.h&gt;
macro_line|#include &lt;net/xfrm.h&gt;
macro_line|#include &lt;asm/scatterlist.h&gt;
multiline_comment|/* XXX no ipv6 ah specific */
DECL|macro|NIP6
mdefine_line|#define NIP6(addr) &bslash;&n;&t;ntohs((addr).s6_addr16[0]),&bslash;&n;&t;ntohs((addr).s6_addr16[1]),&bslash;&n;&t;ntohs((addr).s6_addr16[2]),&bslash;&n;&t;ntohs((addr).s6_addr16[3]),&bslash;&n;&t;ntohs((addr).s6_addr16[4]),&bslash;&n;&t;ntohs((addr).s6_addr16[5]),&bslash;&n;&t;ntohs((addr).s6_addr16[6]),&bslash;&n;&t;ntohs((addr).s6_addr16[7])
DECL|function|ah6_output
r_int
id|ah6_output
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
r_int
id|hdr_len
op_assign
r_sizeof
(paren
r_struct
id|ipv6hdr
)paren
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
id|ipv6hdr
op_star
id|iph
op_assign
l_int|NULL
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
id|u16
id|nh_offset
op_assign
l_int|0
suffix:semicolon
id|u8
id|nexthdr
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
r_if
c_cond
(paren
(paren
id|err
op_assign
id|xfrm_state_check_expire
c_func
(paren
id|x
)paren
)paren
op_ne
l_int|0
)paren
r_goto
id|error
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|xfrm_state_check_space
c_func
(paren
id|x
comma
id|skb
)paren
)paren
op_ne
l_int|0
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
id|iph
op_assign
id|skb-&gt;nh.ipv6h
suffix:semicolon
id|skb-&gt;nh.ipv6h
op_assign
(paren
r_struct
id|ipv6hdr
op_star
)paren
id|skb_push
c_func
(paren
id|skb
comma
id|x-&gt;props.header_len
)paren
suffix:semicolon
id|skb-&gt;nh.ipv6h-&gt;version
op_assign
l_int|6
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
id|skb-&gt;nh.ipv6h-&gt;nexthdr
op_assign
id|IPPROTO_AH
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|skb-&gt;nh.ipv6h-&gt;saddr
comma
op_amp
id|x-&gt;props.saddr
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
id|skb-&gt;nh.ipv6h-&gt;daddr
comma
op_amp
id|x-&gt;id.daddr
comma
r_sizeof
(paren
r_struct
id|in6_addr
)paren
)paren
suffix:semicolon
id|ah
op_assign
(paren
r_struct
id|ip_auth_hdr
op_star
)paren
(paren
id|skb-&gt;nh.ipv6h
op_plus
l_int|1
)paren
suffix:semicolon
id|ah-&gt;nexthdr
op_assign
id|IPPROTO_IPV6
suffix:semicolon
)brace
r_else
(brace
id|hdr_len
op_assign
id|skb-&gt;h.raw
op_minus
id|skb-&gt;nh.raw
suffix:semicolon
id|iph
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
id|iph
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
id|iph
comma
id|skb-&gt;data
comma
id|hdr_len
)paren
suffix:semicolon
id|skb-&gt;nh.ipv6h
op_assign
(paren
r_struct
id|ipv6hdr
op_star
)paren
id|skb_push
c_func
(paren
id|skb
comma
id|x-&gt;props.header_len
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|skb-&gt;nh.ipv6h
comma
id|iph
comma
id|hdr_len
)paren
suffix:semicolon
id|nexthdr
op_assign
id|xfrm6_clear_mutable_options
c_func
(paren
id|skb
comma
op_amp
id|nh_offset
comma
id|XFRM_POLICY_OUT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nexthdr
op_eq
l_int|0
)paren
r_goto
id|error
suffix:semicolon
id|skb-&gt;nh.raw
(braket
id|nh_offset
)braket
op_assign
id|IPPROTO_AH
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
id|ah
op_assign
(paren
r_struct
id|ip_auth_hdr
op_star
)paren
(paren
id|skb-&gt;nh.raw
op_plus
id|hdr_len
)paren
suffix:semicolon
id|skb-&gt;h.raw
op_assign
(paren
r_int
r_char
op_star
)paren
id|ah
suffix:semicolon
id|ah-&gt;nexthdr
op_assign
id|nexthdr
suffix:semicolon
)brace
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
r_if
c_cond
(paren
id|x-&gt;props.mode
)paren
(brace
id|skb-&gt;nh.ipv6h-&gt;hop_limit
op_assign
id|iph-&gt;hop_limit
suffix:semicolon
id|skb-&gt;nh.ipv6h-&gt;priority
op_assign
id|iph-&gt;priority
suffix:semicolon
id|skb-&gt;nh.ipv6h-&gt;flow_lbl
(braket
l_int|0
)braket
op_assign
id|iph-&gt;flow_lbl
(braket
l_int|0
)braket
suffix:semicolon
id|skb-&gt;nh.ipv6h-&gt;flow_lbl
(braket
l_int|1
)braket
op_assign
id|iph-&gt;flow_lbl
(braket
l_int|1
)braket
suffix:semicolon
id|skb-&gt;nh.ipv6h-&gt;flow_lbl
(braket
l_int|2
)braket
op_assign
id|iph-&gt;flow_lbl
(braket
l_int|2
)braket
suffix:semicolon
)brace
r_else
(brace
id|memcpy
c_func
(paren
id|skb-&gt;nh.ipv6h
comma
id|iph
comma
id|hdr_len
)paren
suffix:semicolon
id|skb-&gt;nh.raw
(braket
id|nh_offset
)braket
op_assign
id|IPPROTO_AH
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
id|kfree
(paren
id|iph
)paren
suffix:semicolon
)brace
id|skb-&gt;nh.raw
op_assign
id|skb-&gt;data
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
r_return
id|NET_XMIT_BYPASS
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
r_return
id|err
suffix:semicolon
)brace
DECL|function|ah6_input
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
r_int
id|ah_hlen
suffix:semicolon
r_struct
id|ipv6hdr
op_star
id|iph
suffix:semicolon
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
r_int
id|hdr_len
op_assign
id|skb-&gt;h.raw
op_minus
id|skb-&gt;nh.raw
suffix:semicolon
id|u8
id|nexthdr
op_assign
l_int|0
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
id|ah
op_assign
(paren
r_struct
id|ipv6_auth_hdr
op_star
)paren
id|skb-&gt;data
suffix:semicolon
id|iph
op_assign
id|skb-&gt;nh.ipv6h
suffix:semicolon
(brace
id|u8
id|auth_data
(braket
id|ahp-&gt;icv_trunc_len
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
r_if
c_cond
(paren
id|net_ratelimit
c_func
(paren
)paren
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;ipsec ah authentication error&bslash;n&quot;
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
id|nexthdr
op_assign
(paren
(paren
r_struct
id|ipv6hdr
op_star
)paren
id|tmp_hdr
)paren
op_member_access_from_pointer
id|nexthdr
op_assign
id|ah-&gt;nexthdr
suffix:semicolon
id|skb-&gt;nh.raw
op_assign
id|skb_pull
c_func
(paren
id|skb
comma
(paren
id|ah-&gt;hdrlen
op_plus
l_int|2
)paren
op_lshift
l_int|2
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
op_logical_or
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
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;pmtu discvovery on SA AH/%08x/&quot;
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
