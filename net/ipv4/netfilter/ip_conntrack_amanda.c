multiline_comment|/* Amanda extension for IP connection tracking, Version 0.2&n; * (C) 2002 by Brian J. Murrell &lt;netfilter@interlinx.bc.ca&gt;&n; * based on HW&squot;s ip_conntrack_irc.c as well as other modules&n; *&n; *      This program is free software; you can redistribute it and/or&n; *      modify it under the terms of the GNU General Public License&n; *      as published by the Free Software Foundation; either version&n; *      2 of the License, or (at your option) any later version.&n; *&n; *&t;Module load syntax:&n; * &t;insmod ip_conntrack_amanda.o [master_timeout=n]&n; *&t;&n; *&t;Where master_timeout is the timeout (in seconds) of the master&n; *&t;connection (port 10080).  This defaults to 5 minutes but if&n; *&t;your clients take longer than 5 minutes to do their work&n; *&t;before getting back to the Amanda server, you can increase&n; *&t;this value.&n; *&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/netfilter.h&gt;
macro_line|#include &lt;linux/ip.h&gt;
macro_line|#include &lt;net/checksum.h&gt;
macro_line|#include &lt;net/udp.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/lockhelp.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_conntrack_helper.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_conntrack_amanda.h&gt;
DECL|variable|master_timeout
r_static
r_int
r_int
id|master_timeout
op_assign
l_int|300
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Brian J. Murrell &lt;netfilter@interlinx.bc.ca&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Amanda connection tracking module&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|master_timeout
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|master_timeout
comma
l_string|&quot;timeout for the master connection&quot;
)paren
suffix:semicolon
DECL|variable|conns
r_static
r_char
op_star
id|conns
(braket
)braket
op_assign
(brace
l_string|&quot;DATA &quot;
comma
l_string|&quot;MESG &quot;
comma
l_string|&quot;INDEX &quot;
)brace
suffix:semicolon
multiline_comment|/* This is slow, but it&squot;s simple. --RR */
DECL|variable|amanda_buffer
r_static
r_char
id|amanda_buffer
(braket
l_int|65536
)braket
suffix:semicolon
r_static
id|DECLARE_LOCK
c_func
(paren
id|amanda_buffer_lock
)paren
suffix:semicolon
DECL|function|help
r_static
r_int
id|help
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|ip_conntrack
op_star
id|ct
comma
r_enum
id|ip_conntrack_info
id|ctinfo
)paren
(brace
r_struct
id|ip_conntrack_expect
op_star
id|exp
suffix:semicolon
r_struct
id|ip_ct_amanda_expect
op_star
id|exp_amanda_info
suffix:semicolon
r_char
op_star
id|data
comma
op_star
id|data_limit
comma
op_star
id|tmp
suffix:semicolon
r_int
r_int
id|dataoff
comma
id|i
suffix:semicolon
id|u_int16_t
id|port
comma
id|len
suffix:semicolon
multiline_comment|/* Only look at packets from the Amanda server */
r_if
c_cond
(paren
id|CTINFO2DIR
c_func
(paren
id|ctinfo
)paren
op_eq
id|IP_CT_DIR_ORIGINAL
)paren
r_return
id|NF_ACCEPT
suffix:semicolon
multiline_comment|/* increase the UDP timeout of the master connection as replies from&n;&t; * Amanda clients to the server can be quite delayed */
id|ip_ct_refresh
c_func
(paren
id|ct
comma
id|master_timeout
op_star
id|HZ
)paren
suffix:semicolon
multiline_comment|/* No data? */
id|dataoff
op_assign
id|skb-&gt;nh.iph-&gt;ihl
op_star
l_int|4
op_plus
r_sizeof
(paren
r_struct
id|udphdr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dataoff
op_ge
id|skb-&gt;len
)paren
(brace
r_if
c_cond
(paren
id|net_ratelimit
c_func
(paren
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;amanda_help: skblen = %u&bslash;n&quot;
comma
id|skb-&gt;len
)paren
suffix:semicolon
r_return
id|NF_ACCEPT
suffix:semicolon
)brace
id|LOCK_BH
c_func
(paren
op_amp
id|amanda_buffer_lock
)paren
suffix:semicolon
id|skb_copy_bits
c_func
(paren
id|skb
comma
id|dataoff
comma
id|amanda_buffer
comma
id|skb-&gt;len
op_minus
id|dataoff
)paren
suffix:semicolon
id|data
op_assign
id|amanda_buffer
suffix:semicolon
id|data_limit
op_assign
id|amanda_buffer
op_plus
id|skb-&gt;len
op_minus
id|dataoff
suffix:semicolon
op_star
id|data_limit
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
multiline_comment|/* Search for the CONNECT string */
id|data
op_assign
id|strstr
c_func
(paren
id|data
comma
l_string|&quot;CONNECT &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|data
)paren
r_goto
id|out
suffix:semicolon
id|data
op_add_assign
id|strlen
c_func
(paren
l_string|&quot;CONNECT &quot;
)paren
suffix:semicolon
multiline_comment|/* Only search first line. */
r_if
c_cond
(paren
(paren
id|tmp
op_assign
id|strchr
c_func
(paren
id|data
comma
l_char|&squot;&bslash;n&squot;
)paren
)paren
)paren
op_star
id|tmp
op_assign
l_char|&squot;&bslash;0&squot;
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
id|ARRAY_SIZE
c_func
(paren
id|conns
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
r_char
op_star
id|match
op_assign
id|strstr
c_func
(paren
id|data
comma
id|conns
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|match
)paren
r_continue
suffix:semicolon
id|tmp
op_assign
id|data
op_assign
id|match
op_plus
id|strlen
c_func
(paren
id|conns
(braket
id|i
)braket
)paren
suffix:semicolon
id|port
op_assign
id|simple_strtoul
c_func
(paren
id|data
comma
op_amp
id|data
comma
l_int|10
)paren
suffix:semicolon
id|len
op_assign
id|data
op_minus
id|tmp
suffix:semicolon
r_if
c_cond
(paren
id|port
op_eq
l_int|0
op_logical_or
id|len
OG
l_int|5
)paren
r_break
suffix:semicolon
id|exp
op_assign
id|ip_conntrack_expect_alloc
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|exp
op_eq
l_int|NULL
)paren
r_goto
id|out
suffix:semicolon
id|exp-&gt;tuple.src.ip
op_assign
id|ct-&gt;tuplehash
(braket
id|IP_CT_DIR_ORIGINAL
)braket
dot
id|tuple.src.ip
suffix:semicolon
id|exp-&gt;tuple.dst.ip
op_assign
id|ct-&gt;tuplehash
(braket
id|IP_CT_DIR_ORIGINAL
)braket
dot
id|tuple.dst.ip
suffix:semicolon
id|exp-&gt;tuple.dst.protonum
op_assign
id|IPPROTO_TCP
suffix:semicolon
id|exp-&gt;mask.src.ip
op_assign
l_int|0xFFFFFFFF
suffix:semicolon
id|exp-&gt;mask.dst.ip
op_assign
l_int|0xFFFFFFFF
suffix:semicolon
id|exp-&gt;mask.dst.protonum
op_assign
l_int|0xFFFF
suffix:semicolon
id|exp-&gt;mask.dst.u.tcp.port
op_assign
l_int|0xFFFF
suffix:semicolon
id|exp_amanda_info
op_assign
op_amp
id|exp-&gt;help.exp_amanda_info
suffix:semicolon
id|exp_amanda_info-&gt;offset
op_assign
id|tmp
op_minus
id|amanda_buffer
suffix:semicolon
id|exp_amanda_info-&gt;port
op_assign
id|port
suffix:semicolon
id|exp_amanda_info-&gt;len
op_assign
id|len
suffix:semicolon
id|exp-&gt;tuple.dst.u.tcp.port
op_assign
id|htons
c_func
(paren
id|port
)paren
suffix:semicolon
id|ip_conntrack_expect_related
c_func
(paren
id|exp
comma
id|ct
)paren
suffix:semicolon
)brace
id|out
suffix:colon
id|UNLOCK_BH
c_func
(paren
op_amp
id|amanda_buffer_lock
)paren
suffix:semicolon
r_return
id|NF_ACCEPT
suffix:semicolon
)brace
DECL|variable|amanda_helper
r_static
r_struct
id|ip_conntrack_helper
id|amanda_helper
op_assign
(brace
dot
id|max_expected
op_assign
id|ARRAY_SIZE
c_func
(paren
id|conns
)paren
comma
dot
id|timeout
op_assign
l_int|180
comma
dot
id|flags
op_assign
id|IP_CT_HELPER_F_REUSE_EXPECT
comma
dot
id|me
op_assign
id|THIS_MODULE
comma
dot
id|help
op_assign
id|help
comma
dot
id|name
op_assign
l_string|&quot;amanda&quot;
comma
dot
id|tuple
op_assign
(brace
dot
id|src
op_assign
(brace
dot
id|u
op_assign
(brace
id|__constant_htons
c_func
(paren
l_int|10080
)paren
)brace
)brace
comma
dot
id|dst
op_assign
(brace
dot
id|protonum
op_assign
id|IPPROTO_UDP
)brace
comma
)brace
comma
dot
id|mask
op_assign
(brace
dot
id|src
op_assign
(brace
dot
id|u
op_assign
(brace
l_int|0xFFFF
)brace
)brace
comma
dot
id|dst
op_assign
(brace
dot
id|protonum
op_assign
l_int|0xFFFF
)brace
comma
)brace
comma
)brace
suffix:semicolon
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
id|ip_conntrack_helper_unregister
c_func
(paren
op_amp
id|amanda_helper
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
r_return
id|ip_conntrack_helper_register
c_func
(paren
op_amp
id|amanda_helper
)paren
suffix:semicolon
)brace
DECL|variable|amanda
id|PROVIDES_CONNTRACK
c_func
(paren
id|amanda
)paren
suffix:semicolon
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
