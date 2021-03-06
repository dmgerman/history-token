multiline_comment|/*&n; *  ebt_pkttype&n; *&n; *&t;Authors:&n; *&t;Bart De Schuymer &lt;bdschuym@pandora.be&gt;&n; *&n; *  April, 2003&n; *&n; */
macro_line|#include &lt;linux/netfilter_bridge/ebtables.h&gt;
macro_line|#include &lt;linux/netfilter_bridge/ebt_pkttype.h&gt;
macro_line|#include &lt;linux/module.h&gt;
DECL|function|ebt_filter_pkttype
r_static
r_int
id|ebt_filter_pkttype
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
id|ebt_pkttype_info
op_star
id|info
op_assign
(paren
r_struct
id|ebt_pkttype_info
op_star
)paren
id|data
suffix:semicolon
r_return
(paren
id|skb-&gt;pkt_type
op_ne
id|info-&gt;pkt_type
)paren
op_xor
id|info-&gt;invert
suffix:semicolon
)brace
DECL|function|ebt_pkttype_check
r_static
r_int
id|ebt_pkttype_check
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
id|ebt_pkttype_info
op_star
id|info
op_assign
(paren
r_struct
id|ebt_pkttype_info
op_star
)paren
id|data
suffix:semicolon
r_if
c_cond
(paren
id|datalen
op_ne
id|EBT_ALIGN
c_func
(paren
r_sizeof
(paren
r_struct
id|ebt_pkttype_info
)paren
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;invert
op_ne
l_int|0
op_logical_and
id|info-&gt;invert
op_ne
l_int|1
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* Allow any pkt_type value */
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|filter_pkttype
r_static
r_struct
id|ebt_match
id|filter_pkttype
op_assign
(brace
dot
id|name
op_assign
id|EBT_PKTTYPE_MATCH
comma
dot
id|match
op_assign
id|ebt_filter_pkttype
comma
dot
id|check
op_assign
id|ebt_pkttype_check
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
id|filter_pkttype
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
id|filter_pkttype
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
