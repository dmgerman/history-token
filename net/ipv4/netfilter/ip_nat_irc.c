multiline_comment|/* IRC extension for TCP NAT alteration.&n; * (C) 2000-2001 by Harald Welte &lt;laforge@gnumonks.org&gt;&n; * (C) 2004 Rusty Russell &lt;rusty@rustcorp.com.au&gt; IBM Corporation&n; * based on a copy of RR&squot;s ip_nat_ftp.c&n; *&n; * ip_nat_irc.c,v 1.16 2001/12/06 07:42:10 laforge Exp&n; *&n; *      This program is free software; you can redistribute it and/or&n; *      modify it under the terms of the GNU General Public License&n; *      as published by the Free Software Foundation; either version&n; *      2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4.h&gt;
macro_line|#include &lt;linux/ip.h&gt;
macro_line|#include &lt;linux/tcp.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;net/tcp.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_nat.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_nat_helper.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_nat_rule.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_conntrack_irc.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_conntrack_helper.h&gt;
macro_line|#include &lt;linux/moduleparam.h&gt;
macro_line|#if 0
mdefine_line|#define DEBUGP printk
macro_line|#else
DECL|macro|DEBUGP
mdefine_line|#define DEBUGP(format, args...)
macro_line|#endif
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Harald Welte &lt;laforge@gnumonks.org&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;IRC (DCC) NAT helper&quot;
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
r_int
r_int
id|matchoff
comma
r_int
r_int
id|matchlen
comma
r_struct
id|ip_conntrack_expect
op_star
id|exp
)paren
(brace
id|u_int16_t
id|port
suffix:semicolon
r_int
r_int
id|ret
suffix:semicolon
multiline_comment|/* &quot;4294967296 65635 &quot; */
r_char
id|buffer
(braket
l_int|18
)braket
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;IRC_NAT: info (seq %u + %u) in %u&bslash;n&quot;
comma
id|expect-&gt;seq
comma
id|exp_irc_info-&gt;len
comma
id|ntohl
c_func
(paren
id|tcph-&gt;seq
)paren
)paren
suffix:semicolon
multiline_comment|/* Reply comes from server. */
id|exp-&gt;saved_proto.tcp.port
op_assign
id|exp-&gt;tuple.dst.u.tcp.port
suffix:semicolon
id|exp-&gt;dir
op_assign
id|IP_CT_DIR_REPLY
suffix:semicolon
multiline_comment|/* When you see the packet, we need to NAT it the same as the&n;&t; * this one. */
id|exp-&gt;expectfn
op_assign
id|ip_nat_follow_master
suffix:semicolon
multiline_comment|/* Try to get same port: if not, try to change it. */
r_for
c_loop
(paren
id|port
op_assign
id|ntohs
c_func
(paren
id|exp-&gt;saved_proto.tcp.port
)paren
suffix:semicolon
id|port
op_ne
l_int|0
suffix:semicolon
id|port
op_increment
)paren
(brace
id|exp-&gt;tuple.dst.u.tcp.port
op_assign
id|htons
c_func
(paren
id|port
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ip_conntrack_expect_related
c_func
(paren
id|exp
)paren
op_eq
l_int|0
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|port
op_eq
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
multiline_comment|/*      strlen(&quot;&bslash;1DCC CHAT chat AAAAAAAA P&bslash;1&bslash;n&quot;)=27&n;&t; *      strlen(&quot;&bslash;1DCC SCHAT chat AAAAAAAA P&bslash;1&bslash;n&quot;)=28&n;&t; *      strlen(&quot;&bslash;1DCC SEND F AAAAAAAA P S&bslash;1&bslash;n&quot;)=26&n;&t; *      strlen(&quot;&bslash;1DCC MOVE F AAAAAAAA P S&bslash;1&bslash;n&quot;)=26&n;&t; *      strlen(&quot;&bslash;1DCC TSEND F AAAAAAAA P S&bslash;1&bslash;n&quot;)=27&n;&t; *              AAAAAAAAA: bound addr (1.0.0.0==16777216, min 8 digits,&n;&t; *                      255.255.255.255==4294967296, 10 digits)&n;&t; *              P:         bound port (min 1 d, max 5d (65635))&n;&t; *              F:         filename   (min 1 d )&n;&t; *              S:         size       (min 1 d )&n;&t; *              0x01, &bslash;n:  terminators&n;&t; */
multiline_comment|/* AAA = &quot;us&quot;, ie. where server normally talks to. */
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;%u %u&quot;
comma
id|ntohl
c_func
(paren
id|exp-&gt;master-&gt;tuplehash
(braket
id|IP_CT_DIR_REPLY
)braket
dot
id|tuple.dst.ip
)paren
comma
id|port
)paren
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;ip_nat_irc: Inserting &squot;%s&squot; == %u.%u.%u.%u, port %u&bslash;n&quot;
comma
id|buffer
comma
id|NIPQUAD
c_func
(paren
id|exp-&gt;tuple.src.ip
)paren
comma
id|port
)paren
suffix:semicolon
id|ret
op_assign
id|ip_nat_mangle_tcp_packet
c_func
(paren
id|pskb
comma
id|exp-&gt;master
comma
id|ctinfo
comma
id|matchoff
comma
id|matchlen
comma
id|buffer
comma
id|strlen
c_func
(paren
id|buffer
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ne
id|NF_ACCEPT
)paren
id|ip_conntrack_unexpect_related
c_func
(paren
id|exp
)paren
suffix:semicolon
r_return
id|ret
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
id|ip_nat_irc_hook
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
id|ip_nat_irc_hook
)paren
suffix:semicolon
id|ip_nat_irc_hook
op_assign
id|help
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Prior to 2.6.11, we had a ports param.  No longer, but don&squot;t break users. */
DECL|function|warn_set
r_static
r_int
id|warn_set
c_func
(paren
r_const
r_char
op_star
id|val
comma
r_struct
id|kernel_param
op_star
id|kp
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
id|__stringify
c_func
(paren
id|KBUILD_MODNAME
)paren
l_string|&quot;: kernel &gt;= 2.6.10 only uses &squot;ports&squot; for conntrack modules&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|module_param_call
c_func
(paren
id|ports
comma
id|warn_set
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|0
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
