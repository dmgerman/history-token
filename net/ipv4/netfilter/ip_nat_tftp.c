multiline_comment|/* (C) 2001-2002 Magnus Boden &lt;mb@ozaba.mine.nu&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * Version: 0.0.7&n; *&n; * Thu 21 Mar 2002 Harald Welte &lt;laforge@gnumonks.org&gt;&n; * &t;- Port to newnat API&n; *&n; * This module currently supports DNAT:&n; * iptables -t nat -A PREROUTING -d x.x.x.x -j DNAT --to-dest x.x.x.y&n; *&n; * and SNAT:&n; * iptables -t nat -A POSTROUTING { -j MASQUERADE , -j SNAT --to-source x.x.x.x }&n; *&n; * It has not been tested with&n; * -j SNAT --to-source x.x.x.x-x.x.x.y since I only have one external ip&n; * If you do test this please let me know if it works or not.&n; *&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4.h&gt;
macro_line|#include &lt;linux/ip.h&gt;
macro_line|#include &lt;linux/udp.h&gt;
macro_line|#include &lt;linux/netfilter.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_tables.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_conntrack_helper.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_conntrack_tftp.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_nat_helper.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_nat_rule.h&gt;
macro_line|#include &lt;linux/moduleparam.h&gt;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Magnus Boden &lt;mb@ozaba.mine.nu&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;tftp NAT helper&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|function|help
r_static
r_int
r_int
id|help
c_func
(paren
r_struct
id|sk_buff
op_star
op_star
id|pskb
comma
r_enum
id|ip_conntrack_info
id|ctinfo
comma
r_struct
id|ip_conntrack_expect
op_star
id|exp
)paren
(brace
id|exp-&gt;saved_proto.udp.port
op_assign
id|exp-&gt;tuple.dst.u.tcp.port
suffix:semicolon
id|exp-&gt;dir
op_assign
id|IP_CT_DIR_REPLY
suffix:semicolon
id|exp-&gt;expectfn
op_assign
id|ip_nat_follow_master
suffix:semicolon
r_if
c_cond
(paren
id|ip_conntrack_expect_related
c_func
(paren
id|exp
)paren
op_ne
l_int|0
)paren
(brace
id|ip_conntrack_expect_free
c_func
(paren
id|exp
)paren
suffix:semicolon
r_return
id|NF_DROP
suffix:semicolon
)brace
r_return
id|NF_ACCEPT
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
id|ip_nat_tftp_hook
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Make sure noone calls it, meanwhile. */
id|synchronize_net
c_func
(paren
)paren
suffix:semicolon
)brace
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
id|BUG_ON
c_func
(paren
id|ip_nat_tftp_hook
)paren
suffix:semicolon
id|ip_nat_tftp_hook
op_assign
id|help
suffix:semicolon
r_return
l_int|0
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
