multiline_comment|/*&n; *  ebt_among&n; *&n; *&t;Authors:&n; *&t;Grzegorz Borowiak &lt;grzes@gnu.univ.gda.pl&gt;&n; *&n; *  August, 2003&n; *&n; */
macro_line|#include &lt;linux/netfilter_bridge/ebtables.h&gt;
macro_line|#include &lt;linux/netfilter_bridge/ebt_among.h&gt;
macro_line|#include &lt;linux/ip.h&gt;
macro_line|#include &lt;linux/if_arp.h&gt;
macro_line|#include &lt;linux/module.h&gt;
DECL|function|ebt_mac_wormhash_contains
r_static
r_int
id|ebt_mac_wormhash_contains
c_func
(paren
r_const
r_struct
id|ebt_mac_wormhash
op_star
id|wh
comma
r_const
r_char
op_star
id|mac
comma
r_uint32
id|ip
)paren
(brace
multiline_comment|/* You may be puzzled as to how this code works.&n;&t; * Some tricks were used, refer to &n;&t; * &t;include/linux/netfilter_bridge/ebt_among.h&n;&t; * as there you can find a solution of this mystery.&n;&t; */
r_const
r_struct
id|ebt_mac_wormhash_tuple
op_star
id|p
suffix:semicolon
r_int
id|start
comma
id|limit
comma
id|i
suffix:semicolon
r_uint32
id|cmp
(braket
l_int|2
)braket
op_assign
(brace
l_int|0
comma
l_int|0
)brace
suffix:semicolon
r_int
id|key
op_assign
(paren
r_const
r_int
r_char
)paren
id|mac
(braket
l_int|5
)braket
suffix:semicolon
id|memcpy
c_func
(paren
(paren
(paren
r_char
op_star
)paren
id|cmp
)paren
op_plus
l_int|2
comma
id|mac
comma
l_int|6
)paren
suffix:semicolon
id|start
op_assign
id|wh-&gt;table
(braket
id|key
)braket
suffix:semicolon
id|limit
op_assign
id|wh-&gt;table
(braket
id|key
op_plus
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
id|ip
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
id|start
suffix:semicolon
id|i
OL
id|limit
suffix:semicolon
id|i
op_increment
)paren
(brace
id|p
op_assign
op_amp
id|wh-&gt;pool
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|cmp
(braket
l_int|1
)braket
op_eq
id|p-&gt;cmp
(braket
l_int|1
)braket
op_logical_and
id|cmp
(braket
l_int|0
)braket
op_eq
id|p-&gt;cmp
(braket
l_int|0
)braket
)paren
(brace
r_if
c_cond
(paren
id|p-&gt;ip
op_eq
l_int|0
op_logical_or
id|p-&gt;ip
op_eq
id|ip
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
)brace
)brace
)brace
r_else
(brace
r_for
c_loop
(paren
id|i
op_assign
id|start
suffix:semicolon
id|i
OL
id|limit
suffix:semicolon
id|i
op_increment
)paren
(brace
id|p
op_assign
op_amp
id|wh-&gt;pool
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|cmp
(braket
l_int|1
)braket
op_eq
id|p-&gt;cmp
(braket
l_int|1
)braket
op_logical_and
id|cmp
(braket
l_int|0
)braket
op_eq
id|p-&gt;cmp
(braket
l_int|0
)braket
)paren
(brace
r_if
c_cond
(paren
id|p-&gt;ip
op_eq
l_int|0
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
)brace
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ebt_mac_wormhash_check_integrity
r_static
r_int
id|ebt_mac_wormhash_check_integrity
c_func
(paren
r_const
r_struct
id|ebt_mac_wormhash
op_star
id|wh
)paren
(brace
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|256
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|wh-&gt;table
(braket
id|i
)braket
OG
id|wh-&gt;table
(braket
id|i
op_plus
l_int|1
)braket
)paren
r_return
op_minus
l_int|0x100
op_minus
id|i
suffix:semicolon
r_if
c_cond
(paren
id|wh-&gt;table
(braket
id|i
)braket
OL
l_int|0
)paren
r_return
op_minus
l_int|0x200
op_minus
id|i
suffix:semicolon
r_if
c_cond
(paren
id|wh-&gt;table
(braket
id|i
)braket
OG
id|wh-&gt;poolsize
)paren
r_return
op_minus
l_int|0x300
op_minus
id|i
suffix:semicolon
)brace
r_if
c_cond
(paren
id|wh-&gt;table
(braket
l_int|256
)braket
OG
id|wh-&gt;poolsize
)paren
r_return
op_minus
l_int|0xc00
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|get_ip_dst
r_static
r_int
id|get_ip_dst
c_func
(paren
r_const
r_struct
id|sk_buff
op_star
id|skb
comma
r_uint32
op_star
id|addr
)paren
(brace
r_if
c_cond
(paren
id|eth_hdr
c_func
(paren
id|skb
)paren
op_member_access_from_pointer
id|h_proto
op_eq
id|htons
c_func
(paren
id|ETH_P_IP
)paren
)paren
(brace
r_struct
id|iphdr
id|_iph
comma
op_star
id|ih
suffix:semicolon
id|ih
op_assign
id|skb_header_pointer
c_func
(paren
id|skb
comma
l_int|0
comma
r_sizeof
(paren
id|_iph
)paren
comma
op_amp
id|_iph
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ih
op_eq
l_int|NULL
)paren
r_return
op_minus
l_int|1
suffix:semicolon
op_star
id|addr
op_assign
id|ih-&gt;daddr
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|eth_hdr
c_func
(paren
id|skb
)paren
op_member_access_from_pointer
id|h_proto
op_eq
id|htons
c_func
(paren
id|ETH_P_ARP
)paren
)paren
(brace
r_struct
id|arphdr
id|_arph
comma
op_star
id|ah
suffix:semicolon
r_uint32
id|buf
comma
op_star
id|bp
suffix:semicolon
id|ah
op_assign
id|skb_header_pointer
c_func
(paren
id|skb
comma
l_int|0
comma
r_sizeof
(paren
id|_arph
)paren
comma
op_amp
id|_arph
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ah
op_eq
l_int|NULL
op_logical_or
id|ah-&gt;ar_pln
op_ne
r_sizeof
(paren
r_uint32
)paren
op_logical_or
id|ah-&gt;ar_hln
op_ne
id|ETH_ALEN
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|bp
op_assign
id|skb_header_pointer
c_func
(paren
id|skb
comma
r_sizeof
(paren
r_struct
id|arphdr
)paren
op_plus
l_int|2
op_star
id|ETH_ALEN
op_plus
r_sizeof
(paren
r_uint32
)paren
comma
r_sizeof
(paren
r_uint32
)paren
comma
op_amp
id|buf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bp
op_eq
l_int|NULL
)paren
r_return
op_minus
l_int|1
suffix:semicolon
op_star
id|addr
op_assign
op_star
id|bp
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|get_ip_src
r_static
r_int
id|get_ip_src
c_func
(paren
r_const
r_struct
id|sk_buff
op_star
id|skb
comma
r_uint32
op_star
id|addr
)paren
(brace
r_if
c_cond
(paren
id|eth_hdr
c_func
(paren
id|skb
)paren
op_member_access_from_pointer
id|h_proto
op_eq
id|htons
c_func
(paren
id|ETH_P_IP
)paren
)paren
(brace
r_struct
id|iphdr
id|_iph
comma
op_star
id|ih
suffix:semicolon
id|ih
op_assign
id|skb_header_pointer
c_func
(paren
id|skb
comma
l_int|0
comma
r_sizeof
(paren
id|_iph
)paren
comma
op_amp
id|_iph
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ih
op_eq
l_int|NULL
)paren
r_return
op_minus
l_int|1
suffix:semicolon
op_star
id|addr
op_assign
id|ih-&gt;saddr
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|eth_hdr
c_func
(paren
id|skb
)paren
op_member_access_from_pointer
id|h_proto
op_eq
id|htons
c_func
(paren
id|ETH_P_ARP
)paren
)paren
(brace
r_struct
id|arphdr
id|_arph
comma
op_star
id|ah
suffix:semicolon
r_uint32
id|buf
comma
op_star
id|bp
suffix:semicolon
id|ah
op_assign
id|skb_header_pointer
c_func
(paren
id|skb
comma
l_int|0
comma
r_sizeof
(paren
id|_arph
)paren
comma
op_amp
id|_arph
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ah
op_eq
l_int|NULL
op_logical_or
id|ah-&gt;ar_pln
op_ne
r_sizeof
(paren
r_uint32
)paren
op_logical_or
id|ah-&gt;ar_hln
op_ne
id|ETH_ALEN
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|bp
op_assign
id|skb_header_pointer
c_func
(paren
id|skb
comma
r_sizeof
(paren
r_struct
id|arphdr
)paren
op_plus
id|ETH_ALEN
comma
r_sizeof
(paren
r_uint32
)paren
comma
op_amp
id|buf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bp
op_eq
l_int|NULL
)paren
r_return
op_minus
l_int|1
suffix:semicolon
op_star
id|addr
op_assign
op_star
id|bp
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ebt_filter_among
r_static
r_int
id|ebt_filter_among
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
id|ebt_among_info
op_star
id|info
op_assign
(paren
r_struct
id|ebt_among_info
op_star
)paren
id|data
suffix:semicolon
r_const
r_char
op_star
id|dmac
comma
op_star
id|smac
suffix:semicolon
r_const
r_struct
id|ebt_mac_wormhash
op_star
id|wh_dst
comma
op_star
id|wh_src
suffix:semicolon
r_uint32
id|dip
op_assign
l_int|0
comma
id|sip
op_assign
l_int|0
suffix:semicolon
id|wh_dst
op_assign
id|ebt_among_wh_dst
c_func
(paren
id|info
)paren
suffix:semicolon
id|wh_src
op_assign
id|ebt_among_wh_src
c_func
(paren
id|info
)paren
suffix:semicolon
r_if
c_cond
(paren
id|wh_src
)paren
(brace
id|smac
op_assign
id|eth_hdr
c_func
(paren
id|skb
)paren
op_member_access_from_pointer
id|h_source
suffix:semicolon
r_if
c_cond
(paren
id|get_ip_src
c_func
(paren
id|skb
comma
op_amp
id|sip
)paren
)paren
r_return
id|EBT_NOMATCH
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|info-&gt;bitmask
op_amp
id|EBT_AMONG_SRC_NEG
)paren
)paren
(brace
multiline_comment|/* we match only if it contains */
r_if
c_cond
(paren
op_logical_neg
id|ebt_mac_wormhash_contains
c_func
(paren
id|wh_src
comma
id|smac
comma
id|sip
)paren
)paren
r_return
id|EBT_NOMATCH
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* we match only if it DOES NOT contain */
r_if
c_cond
(paren
id|ebt_mac_wormhash_contains
c_func
(paren
id|wh_src
comma
id|smac
comma
id|sip
)paren
)paren
r_return
id|EBT_NOMATCH
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|wh_dst
)paren
(brace
id|dmac
op_assign
id|eth_hdr
c_func
(paren
id|skb
)paren
op_member_access_from_pointer
id|h_dest
suffix:semicolon
r_if
c_cond
(paren
id|get_ip_dst
c_func
(paren
id|skb
comma
op_amp
id|dip
)paren
)paren
r_return
id|EBT_NOMATCH
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|info-&gt;bitmask
op_amp
id|EBT_AMONG_DST_NEG
)paren
)paren
(brace
multiline_comment|/* we match only if it contains */
r_if
c_cond
(paren
op_logical_neg
id|ebt_mac_wormhash_contains
c_func
(paren
id|wh_dst
comma
id|dmac
comma
id|dip
)paren
)paren
r_return
id|EBT_NOMATCH
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* we match only if it DOES NOT contain */
r_if
c_cond
(paren
id|ebt_mac_wormhash_contains
c_func
(paren
id|wh_dst
comma
id|dmac
comma
id|dip
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
DECL|function|ebt_among_check
r_static
r_int
id|ebt_among_check
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
id|ebt_among_info
op_star
id|info
op_assign
(paren
r_struct
id|ebt_among_info
op_star
)paren
id|data
suffix:semicolon
r_int
id|expected_length
op_assign
r_sizeof
(paren
r_struct
id|ebt_among_info
)paren
suffix:semicolon
r_const
r_struct
id|ebt_mac_wormhash
op_star
id|wh_dst
comma
op_star
id|wh_src
suffix:semicolon
r_int
id|err
suffix:semicolon
id|wh_dst
op_assign
id|ebt_among_wh_dst
c_func
(paren
id|info
)paren
suffix:semicolon
id|wh_src
op_assign
id|ebt_among_wh_src
c_func
(paren
id|info
)paren
suffix:semicolon
id|expected_length
op_add_assign
id|ebt_mac_wormhash_size
c_func
(paren
id|wh_dst
)paren
suffix:semicolon
id|expected_length
op_add_assign
id|ebt_mac_wormhash_size
c_func
(paren
id|wh_src
)paren
suffix:semicolon
r_if
c_cond
(paren
id|datalen
op_ne
id|EBT_ALIGN
c_func
(paren
id|expected_length
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;ebtables: among: wrong size: %d&quot;
l_string|&quot;against expected %d, rounded to %Zd&bslash;n&quot;
comma
id|datalen
comma
id|expected_length
comma
id|EBT_ALIGN
c_func
(paren
id|expected_length
)paren
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|wh_dst
op_logical_and
(paren
id|err
op_assign
id|ebt_mac_wormhash_check_integrity
c_func
(paren
id|wh_dst
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;ebtables: among: dst integrity fail: %x&bslash;n&quot;
comma
op_minus
id|err
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|wh_src
op_logical_and
(paren
id|err
op_assign
id|ebt_mac_wormhash_check_integrity
c_func
(paren
id|wh_src
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;ebtables: among: src integrity fail: %x&bslash;n&quot;
comma
op_minus
id|err
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|filter_among
r_static
r_struct
id|ebt_match
id|filter_among
op_assign
(brace
dot
id|name
op_assign
id|EBT_AMONG_MATCH
comma
dot
id|match
op_assign
id|ebt_filter_among
comma
dot
id|check
op_assign
id|ebt_among_check
comma
dot
id|me
op_assign
id|THIS_MODULE
comma
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
id|filter_among
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
id|filter_among
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
