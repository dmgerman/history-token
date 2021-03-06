multiline_comment|/* Kernel module to match MAC address parameters. */
multiline_comment|/* (C) 1999-2001 Paul `Rusty&squot; Russell&n; * (C) 2002-2004 Netfilter Core Team &lt;coreteam@netfilter.org&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/if_ether.h&gt;
macro_line|#include &lt;linux/netfilter_ipv6/ip6t_mac.h&gt;
macro_line|#include &lt;linux/netfilter_ipv6/ip6_tables.h&gt;
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;MAC address matching module for IPv6&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Netfilter Core Teaam &lt;coreteam@netfilter.org&gt;&quot;
)paren
suffix:semicolon
r_static
r_int
DECL|function|match
id|match
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
id|matchinfo
comma
r_int
id|offset
comma
r_int
r_int
id|protoff
comma
r_int
op_star
id|hotdrop
)paren
(brace
r_const
r_struct
id|ip6t_mac_info
op_star
id|info
op_assign
id|matchinfo
suffix:semicolon
multiline_comment|/* Is mac pointer valid? */
r_return
(paren
id|skb-&gt;mac.raw
op_ge
id|skb-&gt;head
op_logical_and
(paren
id|skb-&gt;mac.raw
op_plus
id|ETH_HLEN
)paren
op_le
id|skb-&gt;data
multiline_comment|/* If so, compare... */
op_logical_and
(paren
(paren
id|memcmp
c_func
(paren
id|eth_hdr
c_func
(paren
id|skb
)paren
op_member_access_from_pointer
id|h_source
comma
id|info-&gt;srcaddr
comma
id|ETH_ALEN
)paren
op_eq
l_int|0
)paren
op_xor
id|info-&gt;invert
)paren
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|ip6t_mac_checkentry
id|ip6t_mac_checkentry
c_func
(paren
r_const
r_char
op_star
id|tablename
comma
r_const
r_struct
id|ip6t_ip6
op_star
id|ip
comma
r_void
op_star
id|matchinfo
comma
r_int
r_int
id|matchsize
comma
r_int
r_int
id|hook_mask
)paren
(brace
r_if
c_cond
(paren
id|hook_mask
op_amp
op_complement
(paren
(paren
l_int|1
op_lshift
id|NF_IP6_PRE_ROUTING
)paren
op_or
(paren
l_int|1
op_lshift
id|NF_IP6_LOCAL_IN
)paren
op_or
(paren
l_int|1
op_lshift
id|NF_IP6_FORWARD
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ip6t_mac: only valid for PRE_ROUTING, LOCAL_IN or&quot;
l_string|&quot; FORWARD&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|matchsize
op_ne
id|IP6T_ALIGN
c_func
(paren
r_sizeof
(paren
r_struct
id|ip6t_mac_info
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|variable|mac_match
r_static
r_struct
id|ip6t_match
id|mac_match
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;mac&quot;
comma
dot
id|match
op_assign
op_amp
id|match
comma
dot
id|checkentry
op_assign
op_amp
id|ip6t_mac_checkentry
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
id|ip6t_register_match
c_func
(paren
op_amp
id|mac_match
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
id|ip6t_unregister_match
c_func
(paren
op_amp
id|mac_match
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
eof
