multiline_comment|/*&n; *  ebt_arp&n; *&n; *&t;Authors:&n; *&t;Bart De Schuymer &lt;bart.de.schuymer@pandora.be&gt;&n; *&t;Tim Gardner &lt;timg@tpi.com&gt;&n; *&n; *  April, 2002&n; *&n; */
macro_line|#include &lt;linux/netfilter_bridge/ebtables.h&gt;
macro_line|#include &lt;linux/netfilter_bridge/ebt_arp.h&gt;
macro_line|#include &lt;linux/if_arp.h&gt;
macro_line|#include &lt;linux/module.h&gt;
DECL|function|ebt_filter_arp
r_static
r_int
id|ebt_filter_arp
c_func
(paren
r_const
r_struct
id|sk_buff
op_star
id|skb
comma
r_const
r_struct
id|net_device
op_star
id|in
comma
r_const
r_struct
id|net_device
op_star
id|out
comma
r_const
r_void
op_star
id|data
comma
r_int
r_int
id|datalen
)paren
(brace
r_struct
id|ebt_arp_info
op_star
id|info
op_assign
(paren
r_struct
id|ebt_arp_info
op_star
)paren
id|data
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;bitmask
op_amp
id|EBT_ARP_OPCODE
op_logical_and
id|FWINV
c_func
(paren
id|info-&gt;opcode
op_ne
(paren
id|skb.nh.arph
)paren
op_member_access_from_pointer
id|ar_op
comma
id|EBT_ARP_OPCODE
)paren
)paren
r_return
id|EBT_NOMATCH
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;bitmask
op_amp
id|EBT_ARP_HTYPE
op_logical_and
id|FWINV
c_func
(paren
id|info-&gt;htype
op_ne
(paren
id|skb.nh.arph
)paren
op_member_access_from_pointer
id|ar_hrd
comma
id|EBT_ARP_HTYPE
)paren
)paren
r_return
id|EBT_NOMATCH
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;bitmask
op_amp
id|EBT_ARP_PTYPE
op_logical_and
id|FWINV
c_func
(paren
id|info-&gt;ptype
op_ne
(paren
id|skb.nh.arph
)paren
op_member_access_from_pointer
id|ar_pro
comma
id|EBT_ARP_PTYPE
)paren
)paren
r_return
id|EBT_NOMATCH
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;bitmask
op_amp
(paren
id|EBT_ARP_SRC_IP
op_or
id|EBT_ARP_DST_IP
)paren
)paren
(brace
r_uint32
id|arp_len
op_assign
r_sizeof
(paren
r_struct
id|arphdr
)paren
op_plus
(paren
l_int|2
op_star
(paren
(paren
id|skb.nh.arph
)paren
op_member_access_from_pointer
id|ar_hln
)paren
)paren
op_plus
(paren
l_int|2
op_star
(paren
(paren
id|skb.nh.arph
)paren
op_member_access_from_pointer
id|ar_pln
)paren
)paren
suffix:semicolon
r_uint32
id|dst
suffix:semicolon
r_uint32
id|src
suffix:semicolon
singleline_comment|// Make sure the packet is long enough.
r_if
c_cond
(paren
(paren
(paren
id|skb.nh.raw
)paren
op_plus
id|arp_len
)paren
OG
id|skb.tail
)paren
r_return
id|EBT_NOMATCH
suffix:semicolon
singleline_comment|// IPv4 addresses are always 4 bytes.
r_if
c_cond
(paren
(paren
id|skb.nh.arph
)paren
op_member_access_from_pointer
id|ar_pln
op_ne
r_sizeof
(paren
r_uint32
)paren
)paren
r_return
id|EBT_NOMATCH
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;bitmask
op_amp
id|EBT_ARP_SRC_IP
)paren
(brace
id|memcpy
c_func
(paren
op_amp
id|src
comma
(paren
id|skb.nh.raw
)paren
op_plus
r_sizeof
(paren
r_struct
id|arphdr
)paren
op_plus
(paren
id|skb.nh.arph
)paren
op_member_access_from_pointer
id|ar_hln
comma
r_sizeof
(paren
r_uint32
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|FWINV
c_func
(paren
id|info-&gt;saddr
op_ne
(paren
id|src
op_amp
id|info-&gt;smsk
)paren
comma
id|EBT_ARP_SRC_IP
)paren
)paren
r_return
id|EBT_NOMATCH
suffix:semicolon
)brace
r_if
c_cond
(paren
id|info-&gt;bitmask
op_amp
id|EBT_ARP_DST_IP
)paren
(brace
id|memcpy
c_func
(paren
op_amp
id|dst
comma
(paren
id|skb.nh.raw
)paren
op_plus
r_sizeof
(paren
r_struct
id|arphdr
)paren
op_plus
(paren
l_int|2
op_star
(paren
(paren
id|skb.nh.arph
)paren
op_member_access_from_pointer
id|ar_hln
)paren
)paren
op_plus
(paren
(paren
id|skb.nh.arph
)paren
op_member_access_from_pointer
id|ar_pln
)paren
comma
r_sizeof
(paren
r_uint32
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|FWINV
c_func
(paren
id|info-&gt;daddr
op_ne
(paren
id|dst
op_amp
id|info-&gt;dmsk
)paren
comma
id|EBT_ARP_DST_IP
)paren
)paren
r_return
id|EBT_NOMATCH
suffix:semicolon
)brace
)brace
r_return
id|EBT_MATCH
suffix:semicolon
)brace
DECL|function|ebt_arp_check
r_static
r_int
id|ebt_arp_check
c_func
(paren
r_const
r_char
op_star
id|tablename
comma
r_int
r_int
id|hookmask
comma
r_const
r_struct
id|ebt_entry
op_star
id|e
comma
r_void
op_star
id|data
comma
r_int
r_int
id|datalen
)paren
(brace
r_struct
id|ebt_arp_info
op_star
id|info
op_assign
(paren
r_struct
id|ebt_arp_info
op_star
)paren
id|data
suffix:semicolon
r_if
c_cond
(paren
id|datalen
op_ne
r_sizeof
(paren
r_struct
id|ebt_arp_info
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
(paren
id|e-&gt;ethproto
op_ne
id|__constant_htons
c_func
(paren
id|ETH_P_ARP
)paren
op_logical_and
id|e-&gt;ethproto
op_ne
id|__constant_htons
c_func
(paren
id|ETH_P_RARP
)paren
)paren
op_logical_or
id|e-&gt;invflags
op_amp
id|EBT_IPROTO
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;bitmask
op_amp
op_complement
id|EBT_ARP_MASK
op_logical_or
id|info-&gt;invflags
op_amp
op_complement
id|EBT_ARP_MASK
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|filter_arp
r_static
r_struct
id|ebt_match
id|filter_arp
op_assign
(brace
(brace
l_int|NULL
comma
l_int|NULL
)brace
comma
id|EBT_ARP_MATCH
comma
id|ebt_filter_arp
comma
id|ebt_arp_check
comma
l_int|NULL
comma
id|THIS_MODULE
)brace
suffix:semicolon
DECL|function|init
r_static
r_int
id|__init
id|init
c_func
(paren
r_void
)paren
(brace
r_return
id|ebt_register_match
c_func
(paren
op_amp
id|filter_arp
)paren
suffix:semicolon
)brace
DECL|function|fini
r_static
r_void
id|__exit
id|fini
c_func
(paren
r_void
)paren
(brace
id|ebt_unregister_match
c_func
(paren
op_amp
id|filter_arp
)paren
suffix:semicolon
)brace
DECL|variable|init
id|module_init
c_func
(paren
id|init
)paren
suffix:semicolon
DECL|variable|fini
id|module_exit
c_func
(paren
id|fini
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof