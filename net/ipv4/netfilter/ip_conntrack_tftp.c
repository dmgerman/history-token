multiline_comment|/* (C) 2001-2002 Magnus Boden &lt;mb@ozaba.mine.nu&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * Version: 0.0.7&n; *&n; * Thu 21 Mar 2002 Harald Welte &lt;laforge@gnumonks.org&gt;&n; * &t;- port to newnat API&n; *&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/ip.h&gt;
macro_line|#include &lt;linux/udp.h&gt;
macro_line|#include &lt;linux/netfilter.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_tables.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_conntrack_helper.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_conntrack_tftp.h&gt;
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
l_string|&quot;tftp connection tracking helper&quot;
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
suffix:semicolon
id|module_param_array
c_func
(paren
id|ports
comma
r_int
comma
op_amp
id|ports_c
comma
l_int|0400
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
macro_line|#if 0
mdefine_line|#define DEBUGP(format, args...) printk(&quot;%s:%s:&quot; format, &bslash;&n;                                       __FILE__, __FUNCTION__ , ## args)
macro_line|#else
DECL|macro|DEBUGP
mdefine_line|#define DEBUGP(format, args...)
macro_line|#endif
DECL|function|tftp_help
r_static
r_int
id|tftp_help
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
id|tftphdr
id|_tftph
comma
op_star
id|tfh
suffix:semicolon
r_struct
id|ip_conntrack_expect
op_star
id|exp
suffix:semicolon
id|tfh
op_assign
id|skb_header_pointer
c_func
(paren
id|skb
comma
id|skb-&gt;nh.iph-&gt;ihl
op_star
l_int|4
op_plus
r_sizeof
(paren
r_struct
id|udphdr
)paren
comma
r_sizeof
(paren
id|_tftph
)paren
comma
op_amp
id|_tftph
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tfh
op_eq
l_int|NULL
)paren
r_return
id|NF_ACCEPT
suffix:semicolon
r_switch
c_cond
(paren
id|ntohs
c_func
(paren
id|tfh-&gt;opcode
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
r_return
id|NF_ACCEPT
suffix:semicolon
id|exp-&gt;tuple
op_assign
id|ct-&gt;tuplehash
(braket
id|IP_CT_DIR_REPLY
)braket
dot
id|tuple
suffix:semicolon
id|exp-&gt;mask.src.ip
op_assign
l_int|0xffffffff
suffix:semicolon
id|exp-&gt;mask.dst.ip
op_assign
l_int|0xffffffff
suffix:semicolon
id|exp-&gt;mask.dst.u.udp.port
op_assign
l_int|0xffff
suffix:semicolon
id|exp-&gt;mask.dst.protonum
op_assign
l_int|0xffff
suffix:semicolon
id|exp-&gt;expectfn
op_assign
l_int|NULL
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;expect: &quot;
)paren
suffix:semicolon
id|DUMP_TUPLE
c_func
(paren
op_amp
id|exp-&gt;tuple
)paren
suffix:semicolon
id|DUMP_TUPLE
c_func
(paren
op_amp
id|exp-&gt;mask
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
r_break
suffix:semicolon
r_case
id|TFTP_OPCODE_DATA
suffix:colon
r_case
id|TFTP_OPCODE_ACK
suffix:colon
id|DEBUGP
c_func
(paren
l_string|&quot;Data/ACK opcode&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|TFTP_OPCODE_ERROR
suffix:colon
id|DEBUGP
c_func
(paren
l_string|&quot;Error opcode&bslash;n&quot;
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
DECL|variable|tftp
r_static
r_struct
id|ip_conntrack_helper
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
id|ip_conntrack_helper_unregister
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
suffix:semicolon
r_char
op_star
id|tmpname
suffix:semicolon
r_if
c_cond
(paren
id|ports_c
op_eq
l_int|0
)paren
id|ports
(braket
id|ports_c
op_increment
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
id|i
OL
id|ports_c
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/* Create helper structure */
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
id|ip_conntrack_helper
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
id|max_expected
op_assign
l_int|1
suffix:semicolon
id|tftp
(braket
id|i
)braket
dot
id|timeout
op_assign
l_int|0
suffix:semicolon
id|tftp
(braket
id|i
)braket
dot
id|flags
op_assign
id|IP_CT_HELPER_F_REUSE_EXPECT
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
id|help
op_assign
id|tftp_help
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
l_string|&quot;port #%d: %d&bslash;n&quot;
comma
id|i
comma
id|ports
(braket
id|i
)braket
)paren
suffix:semicolon
id|ret
op_assign
id|ip_conntrack_helper_register
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
l_string|&quot;ERROR registering helper for port %d&bslash;n&quot;
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
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|tftp
id|PROVIDES_CONNTRACK
c_func
(paren
id|tftp
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
