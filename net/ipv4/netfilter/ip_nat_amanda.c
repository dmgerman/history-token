multiline_comment|/* Amanda extension for TCP NAT alteration.&n; * (C) 2002 by Brian J. Murrell &lt;netfilter@interlinx.bc.ca&gt;&n; * based on a copy of HW&squot;s ip_nat_irc.c as well as other modules&n; *&n; *      This program is free software; you can redistribute it and/or&n; *      modify it under the terms of the GNU General Public License&n; *      as published by the Free Software Foundation; either version&n; *      2 of the License, or (at your option) any later version.&n; *&n; *&t;Module load syntax:&n; * &t;insmod ip_nat_amanda.o&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/netfilter.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/ip.h&gt;
macro_line|#include &lt;linux/udp.h&gt;
macro_line|#include &lt;net/tcp.h&gt;
macro_line|#include &lt;net/udp.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_nat.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_nat_helper.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_conntrack_helper.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_conntrack_amanda.h&gt;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Brian J. Murrell &lt;netfilter@interlinx.bc.ca&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Amanda NAT helper&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
r_static
r_int
r_int
DECL|function|amanda_nat_expected
id|amanda_nat_expected
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
r_struct
id|ip_ct_amanda_expect
op_star
id|exp_amanda_info
suffix:semicolon
r_struct
id|ip_nat_range
id|range
suffix:semicolon
id|u_int32_t
id|newip
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
id|master-&gt;tuplehash
(braket
id|IP_CT_DIR_REPLY
)braket
dot
id|tuple.dst.ip
suffix:semicolon
r_else
id|newip
op_assign
id|master-&gt;tuplehash
(braket
id|IP_CT_DIR_REPLY
)braket
dot
id|tuple.src.ip
suffix:semicolon
multiline_comment|/* We don&squot;t want to manip the per-protocol, just the IPs. */
id|range.flags
op_assign
id|IP_NAT_RANGE_MAP_IPS
suffix:semicolon
id|range.min_ip
op_assign
id|range.max_ip
op_assign
id|newip
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
id|IP_NAT_MANIP_DST
)paren
(brace
id|exp_amanda_info
op_assign
op_amp
id|ct-&gt;master-&gt;help.exp_amanda_info
suffix:semicolon
id|range.flags
op_or_assign
id|IP_NAT_RANGE_PROTO_SPECIFIED
suffix:semicolon
id|range.min
op_assign
id|range.max
op_assign
(paren
(paren
r_union
id|ip_conntrack_manip_proto
)paren
(brace
dot
id|udp
op_assign
(brace
id|htons
c_func
(paren
id|exp_amanda_info-&gt;port
)paren
)brace
)brace
)paren
suffix:semicolon
)brace
r_return
id|ip_nat_setup_info
c_func
(paren
id|ct
comma
op_amp
id|range
comma
id|hooknum
)paren
suffix:semicolon
)brace
DECL|function|amanda_data_fixup
r_static
r_int
id|amanda_data_fixup
c_func
(paren
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
id|exp
)paren
(brace
r_struct
id|ip_ct_amanda_expect
op_star
id|exp_amanda_info
suffix:semicolon
r_struct
id|ip_conntrack_tuple
id|t
op_assign
id|exp-&gt;tuple
suffix:semicolon
r_char
id|buffer
(braket
r_sizeof
(paren
l_string|&quot;65535&quot;
)paren
)braket
suffix:semicolon
id|u_int16_t
id|port
suffix:semicolon
multiline_comment|/* Alter conntrack&squot;s expectations. */
id|exp_amanda_info
op_assign
op_amp
id|exp-&gt;help.exp_amanda_info
suffix:semicolon
id|t.dst.ip
op_assign
id|ct-&gt;tuplehash
(braket
id|IP_CT_DIR_ORIGINAL
)braket
dot
id|tuple.dst.ip
suffix:semicolon
r_for
c_loop
(paren
id|port
op_assign
id|exp_amanda_info-&gt;port
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
id|exp
comma
op_amp
id|t
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
r_return
l_int|0
suffix:semicolon
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;%u&quot;
comma
id|port
)paren
suffix:semicolon
r_return
id|ip_nat_mangle_udp_packet
c_func
(paren
id|pskb
comma
id|ct
comma
id|ctinfo
comma
id|exp_amanda_info-&gt;offset
comma
id|exp_amanda_info-&gt;len
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
r_int
id|dir
op_assign
id|CTINFO2DIR
c_func
(paren
id|ctinfo
)paren
suffix:semicolon
r_int
id|ret
op_assign
id|NF_ACCEPT
suffix:semicolon
multiline_comment|/* Only mangle things once: original direction in POST_ROUTING&n;&t;   and reply direction on PRE_ROUTING. */
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
r_return
id|NF_ACCEPT
suffix:semicolon
multiline_comment|/* if this exectation has a &quot;offset&quot; the packet needs to be mangled */
r_if
c_cond
(paren
id|exp-&gt;help.exp_amanda_info.offset
op_ne
l_int|0
)paren
r_if
c_cond
(paren
op_logical_neg
id|amanda_data_fixup
c_func
(paren
id|ct
comma
id|pskb
comma
id|ctinfo
comma
id|exp
)paren
)paren
id|ret
op_assign
id|NF_DROP
suffix:semicolon
id|exp-&gt;help.exp_amanda_info.offset
op_assign
l_int|0
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|ip_nat_amanda_helper
r_static
r_struct
id|ip_nat_helper
id|ip_nat_amanda_helper
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
id|ip_nat_helper_unregister
c_func
(paren
op_amp
id|ip_nat_amanda_helper
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
r_struct
id|ip_nat_helper
op_star
id|hlpr
op_assign
op_amp
id|ip_nat_amanda_helper
suffix:semicolon
id|hlpr-&gt;tuple.dst.protonum
op_assign
id|IPPROTO_UDP
suffix:semicolon
id|hlpr-&gt;tuple.src.u.udp.port
op_assign
id|htons
c_func
(paren
l_int|10080
)paren
suffix:semicolon
id|hlpr-&gt;mask.src.u.udp.port
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
id|amanda_nat_expected
suffix:semicolon
id|hlpr-&gt;name
op_assign
l_string|&quot;amanda&quot;
suffix:semicolon
r_return
id|ip_nat_helper_register
c_func
(paren
id|hlpr
)paren
suffix:semicolon
)brace
DECL|variable|amanda
id|NEEDS_CONNTRACK
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
