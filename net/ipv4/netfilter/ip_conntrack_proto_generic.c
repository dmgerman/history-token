multiline_comment|/* (C) 1999-2001 Paul `Rusty&squot; Russell&n; * (C) 2002-2004 Netfilter Core Team &lt;coreteam@netfilter.org&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/netfilter.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_conntrack_protocol.h&gt;
DECL|variable|ip_ct_generic_timeout
r_int
r_int
id|ip_ct_generic_timeout
op_assign
l_int|600
op_star
id|HZ
suffix:semicolon
DECL|function|generic_pkt_to_tuple
r_static
r_int
id|generic_pkt_to_tuple
c_func
(paren
r_const
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
r_int
id|dataoff
comma
r_struct
id|ip_conntrack_tuple
op_star
id|tuple
)paren
(brace
id|tuple-&gt;src.u.all
op_assign
l_int|0
suffix:semicolon
id|tuple-&gt;dst.u.all
op_assign
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|generic_invert_tuple
r_static
r_int
id|generic_invert_tuple
c_func
(paren
r_struct
id|ip_conntrack_tuple
op_star
id|tuple
comma
r_const
r_struct
id|ip_conntrack_tuple
op_star
id|orig
)paren
(brace
id|tuple-&gt;src.u.all
op_assign
l_int|0
suffix:semicolon
id|tuple-&gt;dst.u.all
op_assign
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Print out the per-protocol part of the tuple. */
DECL|function|generic_print_tuple
r_static
r_int
r_int
id|generic_print_tuple
c_func
(paren
r_char
op_star
id|buffer
comma
r_const
r_struct
id|ip_conntrack_tuple
op_star
id|tuple
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Print out the private part of the conntrack. */
DECL|function|generic_print_conntrack
r_static
r_int
r_int
id|generic_print_conntrack
c_func
(paren
r_char
op_star
id|buffer
comma
r_const
r_struct
id|ip_conntrack
op_star
id|state
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Returns verdict for packet, or -1 for invalid. */
DECL|function|packet
r_static
r_int
id|packet
c_func
(paren
r_struct
id|ip_conntrack
op_star
id|conntrack
comma
r_const
r_struct
id|sk_buff
op_star
id|skb
comma
r_enum
id|ip_conntrack_info
id|ctinfo
)paren
(brace
id|ip_ct_refresh_acct
c_func
(paren
id|conntrack
comma
id|ctinfo
comma
id|skb
comma
id|ip_ct_generic_timeout
)paren
suffix:semicolon
r_return
id|NF_ACCEPT
suffix:semicolon
)brace
multiline_comment|/* Called when a new connection for this protocol found. */
DECL|function|new
r_static
r_int
r_new
(paren
r_struct
id|ip_conntrack
op_star
id|conntrack
comma
r_const
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|variable|ip_conntrack_generic_protocol
r_struct
id|ip_conntrack_protocol
id|ip_conntrack_generic_protocol
op_assign
(brace
(brace
l_int|NULL
comma
l_int|NULL
)brace
comma
l_int|0
comma
l_string|&quot;unknown&quot;
comma
id|generic_pkt_to_tuple
comma
id|generic_invert_tuple
comma
id|generic_print_tuple
comma
id|generic_print_conntrack
comma
id|packet
comma
r_new
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
)brace
suffix:semicolon
eof
