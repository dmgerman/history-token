multiline_comment|/* IRC extension for TCP NAT alteration.&n; * (C) 2000-2001 by Harald Welte &lt;laforge@gnumonks.org&gt;&n; * based on a copy of RR&squot;s ip_nat_ftp.c&n; *&n; * ip_nat_irc.c,v 1.16 2001/12/06 07:42:10 laforge Exp&n; *&n; *      This program is free software; you can redistribute it and/or&n; *      modify it under the terms of the GNU General Public License&n; *      as published by the Free Software Foundation; either version&n; *      2 of the License, or (at your option) any later version.&n; *&n; *&t;Module load syntax:&n; * &t;insmod ip_nat_irc.o ports=port1,port2,...port&lt;MAX_PORTS&gt;&n; *&t;&n; * &t;please give the ports of all IRC servers You wish to connect to.&n; *&t;If You don&squot;t specify ports, the default will be port 6667&n; */
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
macro_line|#if 0
mdefine_line|#define DEBUGP printk
macro_line|#else
DECL|macro|DEBUGP
mdefine_line|#define DEBUGP(format, args...)
macro_line|#endif
DECL|macro|MAX_PORTS
mdefine_line|#define MAX_PORTS 8
DECL|variable|ports
r_static
r_int
id|ports
(braket
id|MAX_PORTS
)braket
suffix:semicolon
DECL|variable|ports_c
r_static
r_int
id|ports_c
op_assign
l_int|0
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Harald Welte &lt;laforge@gnumonks.org&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;IRC (DCC) network address translation module&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
macro_line|#ifdef MODULE_PARM
id|MODULE_PARM
c_func
(paren
id|ports
comma
l_string|&quot;1-&quot;
id|__MODULE_STRING
c_func
(paren
id|MAX_PORTS
)paren
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|ports
comma
l_string|&quot;port numbers of IRC servers&quot;
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* protects irc part of conntracks */
DECL|variable|ip_irc_lock
id|DECLARE_LOCK_EXTERN
c_func
(paren
id|ip_irc_lock
)paren
suffix:semicolon
multiline_comment|/* FIXME: Time out? --RR */
r_static
r_int
r_int
DECL|function|irc_nat_expected
id|irc_nat_expected
c_func
(paren
r_struct
id|sk_buff
op_star
op_star
id|pskb
comma
r_int
r_int
id|hooknum
comma
r_struct
id|ip_conntrack
op_star
id|ct
comma
r_struct
id|ip_nat_info
op_star
id|info
)paren
(brace
r_struct
id|ip_nat_multi_range
id|mr
suffix:semicolon
id|u_int32_t
id|newdstip
comma
id|newsrcip
comma
id|newip
suffix:semicolon
r_struct
id|ip_conntrack
op_star
id|master
op_assign
id|master_ct
c_func
(paren
id|ct
)paren
suffix:semicolon
id|IP_NF_ASSERT
c_func
(paren
id|info
)paren
suffix:semicolon
id|IP_NF_ASSERT
c_func
(paren
id|master
)paren
suffix:semicolon
id|IP_NF_ASSERT
c_func
(paren
op_logical_neg
(paren
id|info-&gt;initialized
op_amp
(paren
l_int|1
op_lshift
id|HOOK2MANIP
c_func
(paren
id|hooknum
)paren
)paren
)paren
)paren
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;nat_expected: We have a connection!&bslash;n&quot;
)paren
suffix:semicolon
id|newdstip
op_assign
id|master-&gt;tuplehash
(braket
id|IP_CT_DIR_ORIGINAL
)braket
dot
id|tuple.src.ip
suffix:semicolon
id|newsrcip
op_assign
id|ct-&gt;tuplehash
(braket
id|IP_CT_DIR_ORIGINAL
)braket
dot
id|tuple.src.ip
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;nat_expected: DCC cmd. %u.%u.%u.%u-&gt;%u.%u.%u.%u&bslash;n&quot;
comma
id|NIPQUAD
c_func
(paren
id|newsrcip
)paren
comma
id|NIPQUAD
c_func
(paren
id|newdstip
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|HOOK2MANIP
c_func
(paren
id|hooknum
)paren
op_eq
id|IP_NAT_MANIP_SRC
)paren
id|newip
op_assign
id|newsrcip
suffix:semicolon
r_else
id|newip
op_assign
id|newdstip
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;nat_expected: IP to %u.%u.%u.%u&bslash;n&quot;
comma
id|NIPQUAD
c_func
(paren
id|newip
)paren
)paren
suffix:semicolon
id|mr.rangesize
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* We don&squot;t want to manip the per-protocol, just the IPs. */
id|mr.range
(braket
l_int|0
)braket
dot
id|flags
op_assign
id|IP_NAT_RANGE_MAP_IPS
suffix:semicolon
id|mr.range
(braket
l_int|0
)braket
dot
id|min_ip
op_assign
id|mr.range
(braket
l_int|0
)braket
dot
id|max_ip
op_assign
id|newip
suffix:semicolon
r_return
id|ip_nat_setup_info
c_func
(paren
id|ct
comma
op_amp
id|mr
comma
id|hooknum
)paren
suffix:semicolon
)brace
DECL|function|irc_data_fixup
r_static
r_int
id|irc_data_fixup
c_func
(paren
r_const
r_struct
id|ip_ct_irc_expect
op_star
id|ct_irc_info
comma
r_struct
id|ip_conntrack
op_star
id|ct
comma
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
id|expect
)paren
(brace
id|u_int32_t
id|newip
suffix:semicolon
r_struct
id|ip_conntrack_tuple
id|t
suffix:semicolon
r_struct
id|iphdr
op_star
id|iph
op_assign
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nh.iph
suffix:semicolon
r_struct
id|tcphdr
op_star
id|tcph
op_assign
(paren
r_void
op_star
)paren
id|iph
op_plus
id|iph-&gt;ihl
op_star
l_int|4
suffix:semicolon
r_int
id|port
suffix:semicolon
multiline_comment|/* &quot;4294967296 65635 &quot; */
r_char
id|buffer
(braket
l_int|18
)braket
suffix:semicolon
id|MUST_BE_LOCKED
c_func
(paren
op_amp
id|ip_irc_lock
)paren
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;IRC_NAT: info (seq %u + %u) in %u&bslash;n&quot;
comma
id|expect-&gt;seq
comma
id|ct_irc_info-&gt;len
comma
id|ntohl
c_func
(paren
id|tcph-&gt;seq
)paren
)paren
suffix:semicolon
id|newip
op_assign
id|ct-&gt;tuplehash
(braket
id|IP_CT_DIR_REPLY
)braket
dot
id|tuple.dst.ip
suffix:semicolon
multiline_comment|/* Alter conntrack&squot;s expectations. */
multiline_comment|/* We can read expect here without conntrack lock, since it&squot;s&n;&t;   only set in ip_conntrack_irc, with ip_irc_lock held&n;&t;   writable */
id|t
op_assign
id|expect-&gt;tuple
suffix:semicolon
id|t.dst.ip
op_assign
id|newip
suffix:semicolon
r_for
c_loop
(paren
id|port
op_assign
id|ct_irc_info-&gt;port
suffix:semicolon
id|port
op_ne
l_int|0
suffix:semicolon
id|port
op_increment
)paren
(brace
id|t.dst.u.tcp.port
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
id|ip_conntrack_change_expect
c_func
(paren
id|expect
comma
op_amp
id|t
)paren
op_eq
l_int|0
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;using port %d&quot;
comma
id|port
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|port
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/*      strlen(&quot;&bslash;1DCC CHAT chat AAAAAAAA P&bslash;1&bslash;n&quot;)=27&n;&t; *      strlen(&quot;&bslash;1DCC SCHAT chat AAAAAAAA P&bslash;1&bslash;n&quot;)=28&n;&t; *      strlen(&quot;&bslash;1DCC SEND F AAAAAAAA P S&bslash;1&bslash;n&quot;)=26&n;&t; *      strlen(&quot;&bslash;1DCC MOVE F AAAAAAAA P S&bslash;1&bslash;n&quot;)=26&n;&t; *      strlen(&quot;&bslash;1DCC TSEND F AAAAAAAA P S&bslash;1&bslash;n&quot;)=27&n;&t; *              AAAAAAAAA: bound addr (1.0.0.0==16777216, min 8 digits,&n;&t; *                      255.255.255.255==4294967296, 10 digits)&n;&t; *              P:         bound port (min 1 d, max 5d (65635))&n;&t; *              F:         filename   (min 1 d )&n;&t; *              S:         size       (min 1 d )&n;&t; *              0x01, &bslash;n:  terminators&n;&t; */
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
id|newip
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
id|newip
)paren
comma
id|port
)paren
suffix:semicolon
r_return
id|ip_nat_mangle_tcp_packet
c_func
(paren
id|pskb
comma
id|ct
comma
id|ctinfo
comma
id|expect-&gt;seq
op_minus
id|ntohl
c_func
(paren
id|tcph-&gt;seq
)paren
comma
id|ct_irc_info-&gt;len
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
)brace
DECL|function|help
r_static
r_int
r_int
id|help
c_func
(paren
r_struct
id|ip_conntrack
op_star
id|ct
comma
r_struct
id|ip_conntrack_expect
op_star
id|exp
comma
r_struct
id|ip_nat_info
op_star
id|info
comma
r_enum
id|ip_conntrack_info
id|ctinfo
comma
r_int
r_int
id|hooknum
comma
r_struct
id|sk_buff
op_star
op_star
id|pskb
)paren
(brace
r_struct
id|iphdr
op_star
id|iph
op_assign
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nh.iph
suffix:semicolon
r_struct
id|tcphdr
op_star
id|tcph
op_assign
(paren
r_void
op_star
)paren
id|iph
op_plus
id|iph-&gt;ihl
op_star
l_int|4
suffix:semicolon
r_int
r_int
id|datalen
suffix:semicolon
r_int
id|dir
suffix:semicolon
r_struct
id|ip_ct_irc_expect
op_star
id|ct_irc_info
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|exp
)paren
id|DEBUGP
c_func
(paren
l_string|&quot;ip_nat_irc: no exp!!&quot;
)paren
suffix:semicolon
id|ct_irc_info
op_assign
op_amp
id|exp-&gt;help.exp_irc_info
suffix:semicolon
multiline_comment|/* Only mangle things once: original direction in POST_ROUTING&n;&t;   and reply direction on PRE_ROUTING. */
id|dir
op_assign
id|CTINFO2DIR
c_func
(paren
id|ctinfo
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
(paren
id|hooknum
op_eq
id|NF_IP_POST_ROUTING
op_logical_and
id|dir
op_eq
id|IP_CT_DIR_ORIGINAL
)paren
op_logical_or
(paren
id|hooknum
op_eq
id|NF_IP_PRE_ROUTING
op_logical_and
id|dir
op_eq
id|IP_CT_DIR_REPLY
)paren
)paren
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;nat_irc: Not touching dir %s at hook %s&bslash;n&quot;
comma
id|dir
op_eq
id|IP_CT_DIR_ORIGINAL
ques
c_cond
l_string|&quot;ORIG&quot;
suffix:colon
l_string|&quot;REPLY&quot;
comma
id|hooknum
op_eq
id|NF_IP_POST_ROUTING
ques
c_cond
l_string|&quot;POSTROUTING&quot;
suffix:colon
id|hooknum
op_eq
id|NF_IP_PRE_ROUTING
ques
c_cond
l_string|&quot;PREROUTING&quot;
suffix:colon
id|hooknum
op_eq
id|NF_IP_LOCAL_OUT
ques
c_cond
l_string|&quot;OUTPUT&quot;
suffix:colon
l_string|&quot;???&quot;
)paren
suffix:semicolon
r_return
id|NF_ACCEPT
suffix:semicolon
)brace
id|DEBUGP
c_func
(paren
l_string|&quot;got beyond not touching&bslash;n&quot;
)paren
suffix:semicolon
id|datalen
op_assign
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|len
op_minus
id|iph-&gt;ihl
op_star
l_int|4
op_minus
id|tcph-&gt;doff
op_star
l_int|4
suffix:semicolon
id|LOCK_BH
c_func
(paren
op_amp
id|ip_irc_lock
)paren
suffix:semicolon
multiline_comment|/* Check whether the whole IP/address pattern is carried in the payload */
r_if
c_cond
(paren
id|between
c_func
(paren
id|exp-&gt;seq
op_plus
id|ct_irc_info-&gt;len
comma
id|ntohl
c_func
(paren
id|tcph-&gt;seq
)paren
comma
id|ntohl
c_func
(paren
id|tcph-&gt;seq
)paren
op_plus
id|datalen
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|irc_data_fixup
c_func
(paren
id|ct_irc_info
comma
id|ct
comma
id|pskb
comma
id|ctinfo
comma
id|exp
)paren
)paren
(brace
id|UNLOCK_BH
c_func
(paren
op_amp
id|ip_irc_lock
)paren
suffix:semicolon
r_return
id|NF_DROP
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* Half a match?  This means a partial retransmisison.&n;&t;&t;   It&squot;s a cracker being funky. */
r_if
c_cond
(paren
id|net_ratelimit
c_func
(paren
)paren
)paren
(brace
id|printk
(paren
l_string|&quot;IRC_NAT: partial packet %u/%u in %u/%u&bslash;n&quot;
comma
id|exp-&gt;seq
comma
id|ct_irc_info-&gt;len
comma
id|ntohl
c_func
(paren
id|tcph-&gt;seq
)paren
comma
id|ntohl
c_func
(paren
id|tcph-&gt;seq
)paren
op_plus
id|datalen
)paren
suffix:semicolon
)brace
id|UNLOCK_BH
c_func
(paren
op_amp
id|ip_irc_lock
)paren
suffix:semicolon
r_return
id|NF_DROP
suffix:semicolon
)brace
id|UNLOCK_BH
c_func
(paren
op_amp
id|ip_irc_lock
)paren
suffix:semicolon
r_return
id|NF_ACCEPT
suffix:semicolon
)brace
DECL|variable|ip_nat_irc_helpers
r_static
r_struct
id|ip_nat_helper
id|ip_nat_irc_helpers
(braket
id|MAX_PORTS
)braket
suffix:semicolon
DECL|variable|irc_names
r_static
r_char
id|irc_names
(braket
id|MAX_PORTS
)braket
(braket
l_int|10
)braket
suffix:semicolon
multiline_comment|/* This function is intentionally _NOT_ defined as  __exit, because&n; * it is needed by init() */
DECL|function|fini
r_static
r_void
id|fini
c_func
(paren
r_void
)paren
(brace
r_int
id|i
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
id|ports_c
suffix:semicolon
id|i
op_increment
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;ip_nat_irc: unregistering helper for port %d&bslash;n&quot;
comma
id|ports
(braket
id|i
)braket
)paren
suffix:semicolon
id|ip_nat_helper_unregister
c_func
(paren
op_amp
id|ip_nat_irc_helpers
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
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
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_int
id|i
suffix:semicolon
r_struct
id|ip_nat_helper
op_star
id|hlpr
suffix:semicolon
r_char
op_star
id|tmpname
suffix:semicolon
r_if
c_cond
(paren
id|ports
(braket
l_int|0
)braket
op_eq
l_int|0
)paren
(brace
id|ports
(braket
l_int|0
)braket
op_assign
id|IRC_PORT
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
(paren
id|i
OL
id|MAX_PORTS
)paren
op_logical_and
id|ports
(braket
id|i
)braket
op_ne
l_int|0
suffix:semicolon
id|i
op_increment
)paren
(brace
id|hlpr
op_assign
op_amp
id|ip_nat_irc_helpers
(braket
id|i
)braket
suffix:semicolon
id|memset
c_func
(paren
id|hlpr
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|ip_nat_helper
)paren
)paren
suffix:semicolon
id|hlpr-&gt;tuple.dst.protonum
op_assign
id|IPPROTO_TCP
suffix:semicolon
id|hlpr-&gt;tuple.src.u.tcp.port
op_assign
id|htons
c_func
(paren
id|ports
(braket
id|i
)braket
)paren
suffix:semicolon
id|hlpr-&gt;mask.src.u.tcp.port
op_assign
l_int|0xFFFF
suffix:semicolon
id|hlpr-&gt;mask.dst.protonum
op_assign
l_int|0xFFFF
suffix:semicolon
id|hlpr-&gt;help
op_assign
id|help
suffix:semicolon
id|hlpr-&gt;flags
op_assign
l_int|0
suffix:semicolon
id|hlpr-&gt;me
op_assign
id|THIS_MODULE
suffix:semicolon
id|hlpr-&gt;expect
op_assign
id|irc_nat_expected
suffix:semicolon
id|tmpname
op_assign
op_amp
id|irc_names
(braket
id|i
)braket
(braket
l_int|0
)braket
suffix:semicolon
r_if
c_cond
(paren
id|ports
(braket
id|i
)braket
op_eq
id|IRC_PORT
)paren
id|sprintf
c_func
(paren
id|tmpname
comma
l_string|&quot;irc&quot;
)paren
suffix:semicolon
r_else
id|sprintf
c_func
(paren
id|tmpname
comma
l_string|&quot;irc-%d&quot;
comma
id|i
)paren
suffix:semicolon
id|hlpr-&gt;name
op_assign
id|tmpname
suffix:semicolon
id|DEBUGP
(paren
l_string|&quot;ip_nat_irc: Trying to register helper for port %d: name %s&bslash;n&quot;
comma
id|ports
(braket
id|i
)braket
comma
id|hlpr-&gt;name
)paren
suffix:semicolon
id|ret
op_assign
id|ip_nat_helper_register
c_func
(paren
id|hlpr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|printk
(paren
l_string|&quot;ip_nat_irc: error registering helper for port %d&bslash;n&quot;
comma
id|ports
(braket
id|i
)braket
)paren
suffix:semicolon
id|fini
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|ports_c
op_increment
suffix:semicolon
)brace
r_return
id|ret
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
