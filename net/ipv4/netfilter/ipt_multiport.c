multiline_comment|/* Kernel module to match one of a list of TCP/UDP ports: ports are in&n;   the same place so we can treat them as equal. */
multiline_comment|/* (C) 1999-2001 Paul `Rusty&squot; Russell&n; * (C) 2002-2004 Netfilter Core Team &lt;coreteam@netfilter.org&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/udp.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ipt_multiport.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_tables.h&gt;
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Netfilter Core Team &lt;coreteam@netfilter.org&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;iptables multiple port match module&quot;
)paren
suffix:semicolon
macro_line|#if 0
mdefine_line|#define duprintf(format, args...) printk(format , ## args)
macro_line|#else
DECL|macro|duprintf
mdefine_line|#define duprintf(format, args...)
macro_line|#endif
multiline_comment|/* Returns 1 if the port is matched by the test, 0 otherwise. */
r_static
r_inline
r_int
DECL|function|ports_match
id|ports_match
c_func
(paren
r_const
id|u_int16_t
op_star
id|portlist
comma
r_enum
id|ipt_multiport_flags
id|flags
comma
id|u_int8_t
id|count
comma
id|u_int16_t
id|src
comma
id|u_int16_t
id|dst
)paren
(brace
r_int
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
id|count
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|flags
op_ne
id|IPT_MULTIPORT_DESTINATION
op_logical_and
id|portlist
(braket
id|i
)braket
op_eq
id|src
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_ne
id|IPT_MULTIPORT_SOURCE
op_logical_and
id|portlist
(braket
id|i
)braket
op_eq
id|dst
)paren
r_return
l_int|1
suffix:semicolon
)brace
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
id|u16
id|_ports
(braket
l_int|2
)braket
comma
op_star
id|pptr
suffix:semicolon
r_const
r_struct
id|ipt_multiport
op_star
id|multiinfo
op_assign
id|matchinfo
suffix:semicolon
multiline_comment|/* Must not be a fragment. */
r_if
c_cond
(paren
id|offset
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Must be big enough to read ports (both UDP and TCP have&n;           them at the start). */
id|pptr
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
id|_ports
)paren
comma
op_amp
id|_ports
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pptr
op_eq
l_int|NULL
)paren
(brace
multiline_comment|/* We&squot;ve been asked to examine this packet, and we&n;&t;&t; * can&squot;t.  Hence, no choice but to drop.&n;&t;&t; */
id|duprintf
c_func
(paren
l_string|&quot;ipt_multiport:&quot;
l_string|&quot; Dropping evil offset=0 tinygram.&bslash;n&quot;
)paren
suffix:semicolon
op_star
id|hotdrop
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
id|ports_match
c_func
(paren
id|multiinfo-&gt;ports
comma
id|multiinfo-&gt;flags
comma
id|multiinfo-&gt;count
comma
id|ntohs
c_func
(paren
id|pptr
(braket
l_int|0
)braket
)paren
comma
id|ntohs
c_func
(paren
id|pptr
(braket
l_int|1
)braket
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Called when user tries to insert an entry of this type. */
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
r_const
r_struct
id|ipt_multiport
op_star
id|multiinfo
op_assign
id|matchinfo
suffix:semicolon
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
id|ipt_multiport
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Must specify proto == TCP/UDP, no unknown flags or bad count */
r_return
(paren
id|ip-&gt;proto
op_eq
id|IPPROTO_TCP
op_logical_or
id|ip-&gt;proto
op_eq
id|IPPROTO_UDP
)paren
op_logical_and
op_logical_neg
(paren
id|ip-&gt;invflags
op_amp
id|IPT_INV_PROTO
)paren
op_logical_and
id|matchsize
op_eq
id|IPT_ALIGN
c_func
(paren
r_sizeof
(paren
r_struct
id|ipt_multiport
)paren
)paren
op_logical_and
(paren
id|multiinfo-&gt;flags
op_eq
id|IPT_MULTIPORT_SOURCE
op_logical_or
id|multiinfo-&gt;flags
op_eq
id|IPT_MULTIPORT_DESTINATION
op_logical_or
id|multiinfo-&gt;flags
op_eq
id|IPT_MULTIPORT_EITHER
)paren
op_logical_and
id|multiinfo-&gt;count
op_le
id|IPT_MULTI_PORTS
suffix:semicolon
)brace
DECL|variable|multiport_match
r_static
r_struct
id|ipt_match
id|multiport_match
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;multiport&quot;
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
id|multiport_match
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
id|multiport_match
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
