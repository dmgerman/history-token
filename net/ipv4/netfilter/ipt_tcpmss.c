multiline_comment|/* Kernel module to match TCP MSS values. */
multiline_comment|/* Copyright (C) 2000 Marc Boucher &lt;marc@mbsi.ca&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;net/tcp.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ipt_tcpmss.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_tables.h&gt;
DECL|macro|TH_SYN
mdefine_line|#define TH_SYN 0x02
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Marc Boucher &lt;marc@mbsi.ca&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;iptables TCP MSS match module&quot;
)paren
suffix:semicolon
multiline_comment|/* Returns 1 if the mss option is set and matched by the range, 0 otherwise */
r_static
r_inline
r_int
DECL|function|mssoption_match
id|mssoption_match
c_func
(paren
id|u_int16_t
id|min
comma
id|u_int16_t
id|max
comma
r_const
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
id|invert
comma
r_int
op_star
id|hotdrop
)paren
(brace
r_struct
id|tcphdr
id|_tcph
comma
op_star
id|th
suffix:semicolon
multiline_comment|/* tcp.doff is only 4 bits, ie. max 15 * 4 bytes */
id|u8
id|_opt
(braket
l_int|15
op_star
l_int|4
op_minus
r_sizeof
(paren
id|_tcph
)paren
)braket
comma
op_star
id|op
suffix:semicolon
r_int
r_int
id|i
comma
id|optlen
suffix:semicolon
multiline_comment|/* If we don&squot;t have the whole header, drop packet. */
id|th
op_assign
id|skb_header_pointer
c_func
(paren
id|skb
comma
id|skb-&gt;nh.iph-&gt;ihl
op_star
l_int|4
comma
r_sizeof
(paren
id|_tcph
)paren
comma
op_amp
id|_tcph
)paren
suffix:semicolon
r_if
c_cond
(paren
id|th
op_eq
l_int|NULL
)paren
r_goto
id|dropit
suffix:semicolon
multiline_comment|/* Malformed. */
r_if
c_cond
(paren
id|th-&gt;doff
op_star
l_int|4
OL
r_sizeof
(paren
op_star
id|th
)paren
)paren
r_goto
id|dropit
suffix:semicolon
id|optlen
op_assign
id|th-&gt;doff
op_star
l_int|4
op_minus
r_sizeof
(paren
op_star
id|th
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|optlen
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/* Truncated options. */
id|op
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
op_star
id|th
)paren
comma
id|optlen
comma
id|_opt
)paren
suffix:semicolon
r_if
c_cond
(paren
id|op
op_eq
l_int|NULL
)paren
r_goto
id|dropit
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
id|optlen
suffix:semicolon
)paren
(brace
r_if
c_cond
(paren
id|op
(braket
id|i
)braket
op_eq
id|TCPOPT_MSS
op_logical_and
(paren
id|optlen
op_minus
id|i
)paren
op_ge
id|TCPOLEN_MSS
op_logical_and
id|op
(braket
id|i
op_plus
l_int|1
)braket
op_eq
id|TCPOLEN_MSS
)paren
(brace
id|u_int16_t
id|mssval
suffix:semicolon
id|mssval
op_assign
(paren
id|op
(braket
id|i
op_plus
l_int|2
)braket
op_lshift
l_int|8
)paren
op_or
id|op
(braket
id|i
op_plus
l_int|3
)braket
suffix:semicolon
r_return
(paren
id|mssval
op_ge
id|min
op_logical_and
id|mssval
op_le
id|max
)paren
op_xor
id|invert
suffix:semicolon
)brace
r_if
c_cond
(paren
id|op
(braket
id|i
)braket
OL
l_int|2
)paren
id|i
op_increment
suffix:semicolon
r_else
id|i
op_add_assign
id|op
(braket
id|i
op_plus
l_int|1
)braket
ques
c_cond
suffix:colon
l_int|1
suffix:semicolon
)brace
id|out
suffix:colon
r_return
id|invert
suffix:semicolon
id|dropit
suffix:colon
op_star
id|hotdrop
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
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
id|ipt_tcpmss_match_info
op_star
id|info
op_assign
id|matchinfo
suffix:semicolon
r_return
id|mssoption_match
c_func
(paren
id|info-&gt;mss_min
comma
id|info-&gt;mss_max
comma
id|skb
comma
id|info-&gt;invert
comma
id|hotdrop
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|checkentry
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
id|ipt_tcpmss_match_info
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Must specify -p tcp */
r_if
c_cond
(paren
id|ip-&gt;proto
op_ne
id|IPPROTO_TCP
op_logical_or
(paren
id|ip-&gt;invflags
op_amp
id|IPT_INV_PROTO
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;tcpmss: Only works on TCP packets&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|variable|tcpmss_match
r_static
r_struct
id|ipt_match
id|tcpmss_match
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;tcpmss&quot;
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
id|tcpmss_match
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
id|tcpmss_match
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
