multiline_comment|/*&n; * Licensed under GNU GPL version 2 Copyright Magnus Boden &lt;mb@ozaba.mine.nu&gt;&n; * Version: 0.0.7&n; *&n; * Thu 21 Mar 2002 Harald Welte &lt;laforge@gnumonks.org&gt;&n; * &t;- Port to newnat API&n; *&n; * This module currently supports DNAT:&n; * iptables -t nat -A PREROUTING -d x.x.x.x -j DNAT --to-dest x.x.x.y&n; *&n; * and SNAT:&n; * iptables -t nat -A POSTROUTING { -j MASQUERADE , -j SNAT --to-source x.x.x.x }&n; *&n; * It has not been tested with&n; * -j SNAT --to-source x.x.x.x-x.x.x.y since I only have one external ip&n; * If you do test this please let me know if it works or not.&n; *&n; */
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
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Magnus Boden &lt;mb@ozaba.mine.nu&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;tfpt NAT helper&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
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
l_string|&quot;port numbers of tftp servers&quot;
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if 0
mdefine_line|#define DEBUGP(format, args...) printk(__FILE__ &quot;:&quot; __FUNCTION__ &quot;: &quot; &bslash;&n;&t;&t;&t;&t;       format, ## args)
macro_line|#else
DECL|macro|DEBUGP
mdefine_line|#define DEBUGP(format, args...)
macro_line|#endif
r_static
r_int
r_int
DECL|function|tftp_nat_help
id|tftp_nat_help
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
r_struct
id|tftphdr
id|tftph
suffix:semicolon
r_struct
id|ip_conntrack_tuple
id|repl
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
r_return
id|NF_ACCEPT
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|exp
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;no conntrack expectation to modify&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|NF_ACCEPT
suffix:semicolon
)brace
r_if
c_cond
(paren
id|skb_copy_bits
c_func
(paren
op_star
id|pskb
comma
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nh.iph-&gt;ihl
op_star
l_int|4
op_plus
r_sizeof
(paren
r_struct
id|udphdr
)paren
comma
op_amp
id|tftph
comma
r_sizeof
(paren
id|tftph
)paren
)paren
op_ne
l_int|0
)paren
r_return
id|NF_DROP
suffix:semicolon
r_switch
c_cond
(paren
id|ntohs
c_func
(paren
id|tftph.opcode
)paren
)paren
(brace
multiline_comment|/* RRQ and WRQ works the same way */
r_case
id|TFTP_OPCODE_READ
suffix:colon
r_case
id|TFTP_OPCODE_WRITE
suffix:colon
id|repl
op_assign
id|ct-&gt;tuplehash
(braket
id|IP_CT_DIR_REPLY
)braket
dot
id|tuple
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;&quot;
)paren
suffix:semicolon
id|DUMP_TUPLE
c_func
(paren
op_amp
id|ct-&gt;tuplehash
(braket
id|IP_CT_DIR_ORIGINAL
)braket
dot
id|tuple
)paren
suffix:semicolon
id|DUMP_TUPLE
c_func
(paren
op_amp
id|ct-&gt;tuplehash
(braket
id|IP_CT_DIR_REPLY
)braket
dot
id|tuple
)paren
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;expecting: &quot;
)paren
suffix:semicolon
id|DUMP_TUPLE
c_func
(paren
op_amp
id|repl
)paren
suffix:semicolon
id|DUMP_TUPLE
c_func
(paren
op_amp
id|exp-&gt;mask
)paren
suffix:semicolon
id|ip_conntrack_change_expect
c_func
(paren
id|exp
comma
op_amp
id|repl
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|DEBUGP
c_func
(paren
l_string|&quot;Unknown opcode&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_return
id|NF_ACCEPT
suffix:semicolon
)brace
r_static
r_int
r_int
DECL|function|tftp_nat_expected
id|tftp_nat_expected
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
r_const
r_struct
id|ip_conntrack
op_star
id|master
op_assign
id|ct-&gt;master-&gt;expectant
suffix:semicolon
r_const
r_struct
id|ip_conntrack_tuple
op_star
id|orig
op_assign
op_amp
id|master-&gt;tuplehash
(braket
id|IP_CT_DIR_ORIGINAL
)braket
dot
id|tuple
suffix:semicolon
r_struct
id|ip_nat_multi_range
id|mr
suffix:semicolon
macro_line|#if 0
r_const
r_struct
id|ip_conntrack_tuple
op_star
id|repl
op_assign
op_amp
id|master-&gt;tuplehash
(braket
id|IP_CT_DIR_REPLY
)braket
dot
id|tuple
suffix:semicolon
r_struct
id|udphdr
id|udph
suffix:semicolon
r_if
c_cond
(paren
id|skb_copy_bits
c_func
(paren
op_star
id|pskb
comma
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nh.iph-&gt;ihl
op_star
l_int|4
comma
op_amp
id|udph
comma
r_sizeof
(paren
id|udph
)paren
)paren
op_ne
l_int|0
)paren
r_return
id|NF_DROP
suffix:semicolon
macro_line|#endif
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
id|mr.rangesize
op_assign
l_int|1
suffix:semicolon
id|mr.range
(braket
l_int|0
)braket
dot
id|flags
op_assign
id|IP_NAT_RANGE_MAP_IPS
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
(brace
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
id|orig-&gt;dst.ip
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;orig: %u.%u.%u.%u:%u &lt;-&gt; %u.%u.%u.%u:%u &quot;
l_string|&quot;newsrc: %u.%u.%u.%u&bslash;n&quot;
comma
id|NIPQUAD
c_func
(paren
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nh.iph-&gt;saddr
)paren
comma
id|ntohs
c_func
(paren
id|udph.source
)paren
comma
id|NIPQUAD
c_func
(paren
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nh.iph-&gt;daddr
)paren
comma
id|ntohs
c_func
(paren
id|udph.dest
)paren
comma
id|NIPQUAD
c_func
(paren
id|orig-&gt;dst.ip
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
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
id|orig-&gt;src.ip
suffix:semicolon
id|mr.range
(braket
l_int|0
)braket
dot
id|min.udp.port
op_assign
id|mr.range
(braket
l_int|0
)braket
dot
id|max.udp.port
op_assign
id|orig-&gt;src.u.udp.port
suffix:semicolon
id|mr.range
(braket
l_int|0
)braket
dot
id|flags
op_or_assign
id|IP_NAT_RANGE_PROTO_SPECIFIED
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;orig: %u.%u.%u.%u:%u &lt;-&gt; %u.%u.%u.%u:%u &quot;
l_string|&quot;newdst: %u.%u.%u.%u:%u&bslash;n&quot;
comma
id|NIPQUAD
c_func
(paren
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nh.iph-&gt;saddr
)paren
comma
id|ntohs
c_func
(paren
id|udph.source
)paren
comma
id|NIPQUAD
c_func
(paren
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nh.iph-&gt;daddr
)paren
comma
id|ntohs
c_func
(paren
id|udph.dest
)paren
comma
id|NIPQUAD
c_func
(paren
id|orig-&gt;src.ip
)paren
comma
id|ntohs
c_func
(paren
id|orig-&gt;src.u.udp.port
)paren
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
DECL|variable|tftp
r_static
r_struct
id|ip_nat_helper
id|tftp
(braket
id|MAX_PORTS
)braket
suffix:semicolon
DECL|variable|tftp_names
r_static
r_char
id|tftp_names
(braket
id|MAX_PORTS
)braket
(braket
l_int|10
)braket
suffix:semicolon
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
l_string|&quot;unregistering helper for port %d&bslash;n&quot;
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
id|tftp
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
id|i
comma
id|ret
op_assign
l_int|0
suffix:semicolon
r_char
op_star
id|tmpname
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ports
(braket
l_int|0
)braket
)paren
id|ports
(braket
l_int|0
)braket
op_assign
id|TFTP_PORT
suffix:semicolon
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
suffix:semicolon
id|i
op_increment
)paren
(brace
id|memset
c_func
(paren
op_amp
id|tftp
(braket
id|i
)braket
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
id|tftp
(braket
id|i
)braket
dot
id|tuple.dst.protonum
op_assign
id|IPPROTO_UDP
suffix:semicolon
id|tftp
(braket
id|i
)braket
dot
id|tuple.src.u.udp.port
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
id|tftp
(braket
id|i
)braket
dot
id|mask.dst.protonum
op_assign
l_int|0xFFFF
suffix:semicolon
id|tftp
(braket
id|i
)braket
dot
id|mask.src.u.udp.port
op_assign
l_int|0xFFFF
suffix:semicolon
id|tftp
(braket
id|i
)braket
dot
id|help
op_assign
id|tftp_nat_help
suffix:semicolon
id|tftp
(braket
id|i
)braket
dot
id|flags
op_assign
l_int|0
suffix:semicolon
id|tftp
(braket
id|i
)braket
dot
id|me
op_assign
id|THIS_MODULE
suffix:semicolon
id|tftp
(braket
id|i
)braket
dot
id|expect
op_assign
id|tftp_nat_expected
suffix:semicolon
id|tmpname
op_assign
op_amp
id|tftp_names
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
id|TFTP_PORT
)paren
id|sprintf
c_func
(paren
id|tmpname
comma
l_string|&quot;tftp&quot;
)paren
suffix:semicolon
r_else
id|sprintf
c_func
(paren
id|tmpname
comma
l_string|&quot;tftp-%d&quot;
comma
id|i
)paren
suffix:semicolon
id|tftp
(braket
id|i
)braket
dot
id|name
op_assign
id|tmpname
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;ip_nat_tftp: registering for port %d: name %s&bslash;n&quot;
comma
id|ports
(braket
id|i
)braket
comma
id|tftp
(braket
id|i
)braket
dot
id|name
)paren
suffix:semicolon
id|ret
op_assign
id|ip_nat_helper_register
c_func
(paren
op_amp
id|tftp
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ip_nat_tftp: unable to register for port %d&bslash;n&quot;
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
id|ret
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
