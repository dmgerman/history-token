multiline_comment|/*&n; * iptables module to match IP address ranges&n; *&n; * (C) 2003 Jozsef Kadlecsik &lt;kadlec@blackhole.kfki.hu&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/ip.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_tables.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ipt_iprange.h&gt;
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Jozsef Kadlecsik &lt;kadlec@blackhole.kfki.hu&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;iptables arbitrary IP range match module&quot;
)paren
suffix:semicolon
macro_line|#if 0
mdefine_line|#define DEBUGP printk
macro_line|#else
DECL|macro|DEBUGP
mdefine_line|#define DEBUGP(format, args...)
macro_line|#endif
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
op_star
id|hotdrop
)paren
(brace
r_const
r_struct
id|ipt_iprange_info
op_star
id|info
op_assign
id|matchinfo
suffix:semicolon
r_const
r_struct
id|iphdr
op_star
id|iph
op_assign
id|skb-&gt;nh.iph
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;flags
op_amp
id|IPRANGE_SRC
)paren
(brace
r_if
c_cond
(paren
(paren
(paren
id|ntohl
c_func
(paren
id|iph-&gt;saddr
)paren
OL
id|ntohl
c_func
(paren
id|info-&gt;src.min_ip
)paren
)paren
op_logical_or
(paren
id|ntohl
c_func
(paren
id|iph-&gt;saddr
)paren
OG
id|ntohl
c_func
(paren
id|info-&gt;src.max_ip
)paren
)paren
)paren
op_xor
op_logical_neg
op_logical_neg
(paren
id|info-&gt;flags
op_amp
id|IPRANGE_SRC_INV
)paren
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;src IP %u.%u.%u.%u NOT in range %s&quot;
l_string|&quot;%u.%u.%u.%u-%u.%u.%u.%u&bslash;n&quot;
comma
id|NIPQUAD
c_func
(paren
id|iph-&gt;saddr
)paren
comma
id|info-&gt;flags
op_amp
id|IPRANGE_SRC_INV
ques
c_cond
l_string|&quot;(INV) &quot;
suffix:colon
l_string|&quot;&quot;
comma
id|NIPQUAD
c_func
(paren
id|info-&gt;src.min_ip
)paren
comma
id|NIPQUAD
c_func
(paren
id|info-&gt;src.max_ip
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|info-&gt;flags
op_amp
id|IPRANGE_DST
)paren
(brace
r_if
c_cond
(paren
(paren
(paren
id|ntohl
c_func
(paren
id|iph-&gt;daddr
)paren
OL
id|ntohl
c_func
(paren
id|info-&gt;dst.min_ip
)paren
)paren
op_logical_or
(paren
id|ntohl
c_func
(paren
id|iph-&gt;daddr
)paren
OG
id|ntohl
c_func
(paren
id|info-&gt;dst.max_ip
)paren
)paren
)paren
op_xor
op_logical_neg
op_logical_neg
(paren
id|info-&gt;flags
op_amp
id|IPRANGE_DST_INV
)paren
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;dst IP %u.%u.%u.%u NOT in range %s&quot;
l_string|&quot;%u.%u.%u.%u-%u.%u.%u.%u&bslash;n&quot;
comma
id|NIPQUAD
c_func
(paren
id|iph-&gt;daddr
)paren
comma
id|info-&gt;flags
op_amp
id|IPRANGE_DST_INV
ques
c_cond
l_string|&quot;(INV) &quot;
suffix:colon
l_string|&quot;&quot;
comma
id|NIPQUAD
c_func
(paren
id|info-&gt;dst.min_ip
)paren
comma
id|NIPQUAD
c_func
(paren
id|info-&gt;dst.max_ip
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|check
r_static
r_int
id|check
c_func
(paren
r_const
r_char
op_star
id|tablename
comma
r_const
r_struct
id|ipt_ip
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
multiline_comment|/* verify size */
r_if
c_cond
(paren
id|matchsize
op_ne
id|IPT_ALIGN
c_func
(paren
r_sizeof
(paren
r_struct
id|ipt_iprange_info
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
DECL|variable|iprange_match
r_static
r_struct
id|ipt_match
id|iprange_match
op_assign
(brace
dot
id|list
op_assign
(brace
l_int|NULL
comma
l_int|NULL
)brace
comma
dot
id|name
op_assign
l_string|&quot;iprange&quot;
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
id|check
comma
dot
id|destroy
op_assign
l_int|NULL
comma
dot
id|me
op_assign
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
id|ipt_register_match
c_func
(paren
op_amp
id|iprange_match
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
id|ipt_unregister_match
c_func
(paren
op_amp
id|iprange_match
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
