multiline_comment|/* IP tables module for matching the value of the IPv4 DSCP field&n; *&n; * ipt_dscp.c,v 1.3 2002/08/05 19:00:21 laforge Exp&n; *&n; * (C) 2002 by Harald Welte &lt;laforge@gnumonks.org&gt;&n; *&n; * This software is distributed under the terms  GNU GPL&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ipt_dscp.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_tables.h&gt;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Harald Welte &lt;laforge@gnumonks.org&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;IP tables DSCP matching module&quot;
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
r_const
r_struct
id|ipt_dscp_info
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
id|u_int8_t
id|sh_dscp
op_assign
(paren
(paren
id|info-&gt;dscp
op_lshift
id|IPT_DSCP_SHIFT
)paren
op_amp
id|IPT_DSCP_MASK
)paren
suffix:semicolon
r_return
(paren
(paren
id|iph-&gt;tos
op_amp
id|IPT_DSCP_MASK
)paren
op_eq
id|sh_dscp
)paren
op_xor
id|info-&gt;invert
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
id|ipt_dscp_info
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
DECL|variable|dscp_match
r_static
r_struct
id|ipt_match
id|dscp_match
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;dscp&quot;
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
id|ipt_register_match
c_func
(paren
op_amp
id|dscp_match
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
id|dscp_match
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
