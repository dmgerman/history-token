multiline_comment|/* Kernel module to match EUI64 address parameters. */
multiline_comment|/* (C) 2001-2002 Andras Kis-Szabo &lt;kisza@sch.bme.hu&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/ipv6.h&gt;
macro_line|#include &lt;linux/if_ether.h&gt;
macro_line|#include &lt;linux/netfilter_ipv6/ip6_tables.h&gt;
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;IPv6 EUI64 address checking match&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Andras Kis-Szabo &lt;kisza@sch.bme.hu&gt;&quot;
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
r_const
r_void
op_star
id|hdr
comma
id|u_int16_t
id|datalen
comma
r_int
op_star
id|hotdrop
)paren
(brace
r_int
r_char
id|eui64
(braket
l_int|8
)braket
suffix:semicolon
r_int
id|i
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
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
)paren
op_logical_and
id|offset
op_ne
l_int|0
)paren
(brace
op_star
id|hotdrop
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|memset
c_func
(paren
id|eui64
comma
l_int|0
comma
r_sizeof
(paren
id|eui64
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb-&gt;mac.ethernet-&gt;h_proto
op_eq
id|ntohs
c_func
(paren
id|ETH_P_IPV6
)paren
)paren
(brace
r_if
c_cond
(paren
id|skb-&gt;nh.ipv6h-&gt;version
op_eq
l_int|0x6
)paren
(brace
id|memcpy
c_func
(paren
id|eui64
comma
id|skb-&gt;mac.ethernet-&gt;h_source
comma
l_int|3
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|eui64
op_plus
l_int|5
comma
id|skb-&gt;mac.ethernet-&gt;h_source
op_plus
l_int|3
comma
l_int|3
)paren
suffix:semicolon
id|eui64
(braket
l_int|3
)braket
op_assign
l_int|0xff
suffix:semicolon
id|eui64
(braket
l_int|4
)braket
op_assign
l_int|0xfe
suffix:semicolon
id|eui64
(braket
l_int|0
)braket
op_or_assign
l_int|0x02
suffix:semicolon
id|i
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
(paren
id|skb-&gt;nh.ipv6h-&gt;saddr.s6_addr
(braket
l_int|8
op_plus
id|i
)braket
op_eq
id|eui64
(braket
id|i
)braket
)paren
op_logical_and
(paren
id|i
OL
l_int|8
)paren
)paren
id|i
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|i
op_eq
l_int|8
)paren
r_return
l_int|1
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|ip6t_eui64_checkentry
id|ip6t_eui64_checkentry
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
id|NF_IP6_PRE_ROUTING
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ip6t_eui64: only valid for PRE_ROUTING, LOCAL_IN or FORWARD.&bslash;n&quot;
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
r_int
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
DECL|variable|eui64_match
r_static
r_struct
id|ip6t_match
id|eui64_match
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;eui64&quot;
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
id|ip6t_eui64_checkentry
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
id|eui64_match
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
id|eui64_match
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
