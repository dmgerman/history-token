multiline_comment|/*&n; *  ebt_mark_m&n; *&n; *&t;Authors:&n; *&t;Bart De Schuymer &lt;bart.de.schuymer@pandora.be&gt;&n; *&n; *  July, 2002&n; *&n; */
macro_line|#include &lt;linux/netfilter_bridge/ebtables.h&gt;
macro_line|#include &lt;linux/netfilter_bridge/ebt_mark_m.h&gt;
macro_line|#include &lt;linux/module.h&gt;
DECL|function|ebt_filter_mark
r_static
r_int
id|ebt_filter_mark
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
id|ebt_mark_m_info
op_star
id|info
op_assign
(paren
r_struct
id|ebt_mark_m_info
op_star
)paren
id|data
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;bitmask
op_amp
id|EBT_MARK_OR
)paren
r_return
op_logical_neg
(paren
op_logical_neg
op_logical_neg
(paren
id|skb-&gt;nfmark
op_amp
id|info-&gt;mask
)paren
op_xor
id|info-&gt;invert
)paren
suffix:semicolon
r_return
op_logical_neg
(paren
(paren
(paren
id|skb-&gt;nfmark
op_amp
id|info-&gt;mask
)paren
op_eq
id|info-&gt;mark
)paren
op_xor
id|info-&gt;invert
)paren
suffix:semicolon
)brace
DECL|function|ebt_mark_check
r_static
r_int
id|ebt_mark_check
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
id|ebt_mark_m_info
op_star
id|info
op_assign
(paren
r_struct
id|ebt_mark_m_info
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
id|ebt_mark_m_info
)paren
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
id|EBT_MARK_MASK
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
(paren
id|info-&gt;bitmask
op_amp
id|EBT_MARK_OR
)paren
op_logical_and
(paren
id|info-&gt;bitmask
op_amp
id|EBT_MARK_AND
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|info-&gt;bitmask
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|filter_mark
r_static
r_struct
id|ebt_match
id|filter_mark
op_assign
(brace
(brace
l_int|NULL
comma
l_int|NULL
)brace
comma
id|EBT_MARK_MATCH
comma
id|ebt_filter_mark
comma
id|ebt_mark_check
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
id|filter_mark
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
id|filter_mark
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