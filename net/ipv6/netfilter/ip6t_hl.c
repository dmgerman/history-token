multiline_comment|/* Hop Limit matching module */
multiline_comment|/* (C) 2001-2002 Maciej Soltysiak &lt;solt@dns.toxicfilms.tv&gt;&n; * Based on HW&squot;s ttl module&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/netfilter_ipv6/ip6t_hl.h&gt;
macro_line|#include &lt;linux/netfilter_ipv6/ip6_tables.h&gt;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Maciej Soltysiak &lt;solt@dns.toxicfilms.tv&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;IP tables Hop Limit matching module&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|function|match
r_static
r_int
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
id|ip6t_hl_info
op_star
id|info
op_assign
id|matchinfo
suffix:semicolon
r_const
r_struct
id|ipv6hdr
op_star
id|ip6h
op_assign
id|skb-&gt;nh.ipv6h
suffix:semicolon
r_switch
c_cond
(paren
id|info-&gt;mode
)paren
(brace
r_case
id|IP6T_HL_EQ
suffix:colon
r_return
(paren
id|ip6h-&gt;hop_limit
op_eq
id|info-&gt;hop_limit
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IP6T_HL_NE
suffix:colon
r_return
(paren
op_logical_neg
(paren
id|ip6h-&gt;hop_limit
op_eq
id|info-&gt;hop_limit
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IP6T_HL_LT
suffix:colon
r_return
(paren
id|ip6h-&gt;hop_limit
OL
id|info-&gt;hop_limit
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IP6T_HL_GT
suffix:colon
r_return
(paren
id|ip6h-&gt;hop_limit
OG
id|info-&gt;hop_limit
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;ip6t_hl: unknown mode %d&bslash;n&quot;
comma
id|info-&gt;mode
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|checkentry
r_static
r_int
id|checkentry
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
id|matchsize
op_ne
id|IP6T_ALIGN
c_func
(paren
r_sizeof
(paren
r_struct
id|ip6t_hl_info
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
DECL|variable|hl_match
r_static
r_struct
id|ip6t_match
id|hl_match
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;hl&quot;
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
id|checkentry
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
id|hl_match
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
id|hl_match
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
