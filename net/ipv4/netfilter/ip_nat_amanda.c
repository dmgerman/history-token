multiline_comment|/* Amanda extension for TCP NAT alteration.&n; * (C) 2002 by Brian J. Murrell &lt;netfilter@interlinx.bc.ca&gt;&n; * based on a copy of HW&squot;s ip_nat_irc.c as well as other modules&n; *&n; *      This program is free software; you can redistribute it and/or&n; *      modify it under the terms of the GNU General Public License&n; *      as published by the Free Software Foundation; either version&n; *      2 of the License, or (at your option) any later version.&n; *&n; *&t;Module load syntax:&n; * &t;insmod ip_nat_amanda.o&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4.h&gt;
macro_line|#include &lt;linux/ip.h&gt;
macro_line|#include &lt;linux/udp.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;net/tcp.h&gt;
macro_line|#include &lt;net/udp.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_nat.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_nat_helper.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_nat_rule.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_conntrack_helper.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_conntrack_amanda.h&gt;
macro_line|#if 0
mdefine_line|#define DEBUGP printk
mdefine_line|#define DUMP_OFFSET(x)&t;printk(&quot;offset_before=%d, offset_after=%d, correction_pos=%u&bslash;n&quot;, x-&gt;offset_before, x-&gt;offset_after, x-&gt;correction_pos);
macro_line|#else
DECL|macro|DEBUGP
mdefine_line|#define DEBUGP(format, args...)
DECL|macro|DUMP_OFFSET
mdefine_line|#define DUMP_OFFSET(x)
macro_line|#endif
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
multiline_comment|/* protects amanda part of conntracks */
DECL|variable|ip_amanda_lock
id|DECLARE_LOCK_EXTERN
c_func
(paren
id|ip_amanda_lock
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
id|u_int16_t
id|port
suffix:semicolon
r_struct
id|ip_ct_amanda_expect
op_star
id|exp_info
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
id|exp_info
op_assign
op_amp
id|ct-&gt;master-&gt;help.exp_amanda_info
suffix:semicolon
id|newdstip
op_assign
id|ct-&gt;tuplehash
(braket
id|IP_CT_DIR_REPLY
)braket
dot
id|tuple.src.ip
suffix:semicolon
id|newsrcip
op_assign
id|master-&gt;tuplehash
(braket
id|IP_CT_DIR_ORIGINAL
)braket
dot
id|tuple.src.ip
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;nat_expected: %u.%u.%u.%u-&gt;%u.%u.%u.%u&bslash;n&quot;
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
id|port
op_assign
id|exp_info-&gt;port
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
id|mr.range
(braket
l_int|0
)braket
dot
id|flags
op_or_assign
id|IP_NAT_RANGE_PROTO_SPECIFIED
suffix:semicolon
id|mr.range
(braket
l_int|0
)braket
dot
id|min
op_assign
id|mr.range
(braket
l_int|0
)braket
dot
id|max
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
id|port
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
id|mr
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
id|expect
)paren
(brace
id|u_int32_t
id|newip
suffix:semicolon
multiline_comment|/* DATA 99999 MESG 99999 INDEX 99999 */
r_char
id|buffer
(braket
l_int|6
)braket
suffix:semicolon
r_struct
id|ip_conntrack_expect
op_star
id|exp
op_assign
id|expect
suffix:semicolon
r_struct
id|ip_ct_amanda_expect
op_star
id|ct_amanda_info
op_assign
op_amp
id|exp-&gt;help.exp_amanda_info
suffix:semicolon
r_struct
id|ip_conntrack_tuple
id|t
op_assign
id|exp-&gt;tuple
suffix:semicolon
r_int
id|port
suffix:semicolon
id|MUST_BE_LOCKED
c_func
(paren
op_amp
id|ip_amanda_lock
)paren
suffix:semicolon
id|newip
op_assign
id|ct-&gt;tuplehash
(braket
id|IP_CT_DIR_ORIGINAL
)braket
dot
id|tuple.dst.ip
suffix:semicolon
id|DEBUGP
(paren
l_string|&quot;ip_nat_amanda_help: newip = %u.%u.%u.%u&bslash;n&quot;
comma
id|NIPQUAD
c_func
(paren
id|newip
)paren
)paren
suffix:semicolon
multiline_comment|/* Alter conntrack&squot;s expectations. */
multiline_comment|/* We can read expect here without conntrack lock, since it&squot;s&n;&t;   only set in ip_conntrack_amanda, with ip_amanda_lock held&n;&t;   writable */
id|t.dst.ip
op_assign
id|newip
suffix:semicolon
r_for
c_loop
(paren
id|port
op_assign
id|ct_amanda_info-&gt;port
op_plus
l_int|10
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
multiline_comment|/* XXX exp-&gt;seq */
id|ct_amanda_info-&gt;offset
comma
id|ct_amanda_info-&gt;len
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
l_string|&quot;ip_nat_amanda: no exp!!&quot;
)paren
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
l_string|&quot;ip_nat_amanda_help: Not touching dir %s at hook %s&bslash;n&quot;
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
id|hooknum
op_eq
id|NF_IP_LOCAL_IN
ques
c_cond
l_string|&quot;INPUT&quot;
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
l_string|&quot;ip_nat_amanda_help: got beyond not touching: dir %s at hook %s for expect: &quot;
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
id|hooknum
op_eq
id|NF_IP_LOCAL_IN
ques
c_cond
l_string|&quot;INPUT&quot;
suffix:colon
l_string|&quot;???&quot;
)paren
suffix:semicolon
id|DUMP_TUPLE
c_func
(paren
op_amp
id|exp-&gt;tuple
)paren
suffix:semicolon
id|LOCK_BH
c_func
(paren
op_amp
id|ip_amanda_lock
)paren
suffix:semicolon
singleline_comment|// XXX&t;if (exp-&gt;seq != 0)
r_if
c_cond
(paren
id|exp-&gt;help.exp_amanda_info.offset
op_ne
l_int|0
)paren
multiline_comment|/*  if this packet has a &quot;seq&quot; it needs to have it&squot;s content mangled */
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
(brace
id|UNLOCK_BH
c_func
(paren
op_amp
id|ip_amanda_lock
)paren
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;ip_nat_amanda: NF_DROP&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|NF_DROP
suffix:semicolon
)brace
id|exp-&gt;help.exp_amanda_info.offset
op_assign
l_int|0
suffix:semicolon
id|UNLOCK_BH
c_func
(paren
op_amp
id|ip_amanda_lock
)paren
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;ip_nat_amanda: NF_ACCEPT&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|NF_ACCEPT
suffix:semicolon
)brace
DECL|variable|ip_nat_amanda_helper
r_static
r_struct
id|ip_nat_helper
id|ip_nat_amanda_helper
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
id|DEBUGP
c_func
(paren
l_string|&quot;ip_nat_amanda: unregistering nat helper&bslash;n&quot;
)paren
suffix:semicolon
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
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_struct
id|ip_nat_helper
op_star
id|hlpr
suffix:semicolon
id|hlpr
op_assign
op_amp
id|ip_nat_amanda_helper
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
id|DEBUGP
(paren
l_string|&quot;ip_nat_amanda: Trying to register nat helper&bslash;n&quot;
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
l_string|&quot;ip_nat_amanda: error registering nat helper&bslash;n&quot;
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
r_return
id|ret
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
