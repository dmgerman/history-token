multiline_comment|/*&n; *  ebt_ip&n; *&n; *&t;Authors:&n; *&t;Bart De Schuymer &lt;bart.de.schuymer@pandora.be&gt;&n; *&n; *  April, 2002&n; *&n; */
macro_line|#include &lt;linux/netfilter_bridge/ebtables.h&gt;
macro_line|#include &lt;linux/netfilter_bridge/ebt_ip.h&gt;
macro_line|#include &lt;linux/ip.h&gt;
macro_line|#include &lt;linux/module.h&gt;
DECL|function|ebt_filter_ip
r_static
r_int
id|ebt_filter_ip
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
id|ebt_ip_info
op_star
id|info
op_assign
(paren
r_struct
id|ebt_ip_info
op_star
)paren
id|data
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;bitmask
op_amp
id|EBT_IP_TOS
op_logical_and
id|FWINV
c_func
(paren
id|info-&gt;tos
op_ne
(paren
id|skb.nh.iph
)paren
op_member_access_from_pointer
id|tos
comma
id|EBT_IP_TOS
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
id|EBT_IP_PROTO
op_logical_and
id|FWINV
c_func
(paren
id|info-&gt;protocol
op_ne
(paren
id|skb.nh.iph
)paren
op_member_access_from_pointer
id|protocol
comma
id|EBT_IP_PROTO
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
id|EBT_IP_SOURCE
op_logical_and
id|FWINV
c_func
(paren
(paren
(paren
id|skb.nh.iph
)paren
op_member_access_from_pointer
id|saddr
op_amp
id|info-&gt;smsk
)paren
op_ne
id|info-&gt;saddr
comma
id|EBT_IP_SOURCE
)paren
)paren
r_return
id|EBT_NOMATCH
suffix:semicolon
r_if
c_cond
(paren
(paren
id|info-&gt;bitmask
op_amp
id|EBT_IP_DEST
)paren
op_logical_and
id|FWINV
c_func
(paren
(paren
(paren
id|skb.nh.iph
)paren
op_member_access_from_pointer
id|daddr
op_amp
id|info-&gt;dmsk
)paren
op_ne
id|info-&gt;daddr
comma
id|EBT_IP_DEST
)paren
)paren
r_return
id|EBT_NOMATCH
suffix:semicolon
r_return
id|EBT_MATCH
suffix:semicolon
)brace
DECL|function|ebt_ip_check
r_static
r_int
id|ebt_ip_check
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
id|ebt_ip_info
op_star
id|info
op_assign
(paren
r_struct
id|ebt_ip_info
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
id|ebt_ip_info
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|e-&gt;ethproto
op_ne
id|__constant_htons
c_func
(paren
id|ETH_P_IP
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
id|EBT_IP_MASK
op_logical_or
id|info-&gt;invflags
op_amp
op_complement
id|EBT_IP_MASK
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|filter_ip
r_static
r_struct
id|ebt_match
id|filter_ip
op_assign
(brace
(brace
l_int|NULL
comma
l_int|NULL
)brace
comma
id|EBT_IP_MATCH
comma
id|ebt_filter_ip
comma
id|ebt_ip_check
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
id|filter_ip
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
id|filter_ip
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
