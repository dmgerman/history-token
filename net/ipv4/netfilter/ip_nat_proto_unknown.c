multiline_comment|/* The &quot;unknown&quot; protocol.  This is what is used for protocols we&n; * don&squot;t understand.  It&squot;s returned by ip_ct_find_proto().&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/netfilter.h&gt;
macro_line|#include &lt;linux/if.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_nat.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_nat_rule.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_nat_protocol.h&gt;
DECL|function|unknown_in_range
r_static
r_int
id|unknown_in_range
c_func
(paren
r_const
r_struct
id|ip_conntrack_tuple
op_star
id|tuple
comma
r_enum
id|ip_nat_manip_type
id|manip_type
comma
r_const
r_union
id|ip_conntrack_manip_proto
op_star
id|min
comma
r_const
r_union
id|ip_conntrack_manip_proto
op_star
id|max
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|unknown_unique_tuple
r_static
r_int
id|unknown_unique_tuple
c_func
(paren
r_struct
id|ip_conntrack_tuple
op_star
id|tuple
comma
r_const
r_struct
id|ip_nat_range
op_star
id|range
comma
r_enum
id|ip_nat_manip_type
id|maniptype
comma
r_const
r_struct
id|ip_conntrack
op_star
id|conntrack
)paren
(brace
multiline_comment|/* Sorry: we can&squot;t help you; if it&squot;s not unique, we can&squot;t frob&n;&t;   anything. */
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_void
DECL|function|unknown_manip_pkt
id|unknown_manip_pkt
c_func
(paren
r_struct
id|iphdr
op_star
id|iph
comma
r_int
id|len
comma
r_const
r_struct
id|ip_conntrack_manip
op_star
id|manip
comma
r_enum
id|ip_nat_manip_type
id|maniptype
)paren
(brace
r_return
suffix:semicolon
)brace
r_static
r_int
r_int
DECL|function|unknown_print
id|unknown_print
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
id|match
comma
r_const
r_struct
id|ip_conntrack_tuple
op_star
id|mask
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
r_int
DECL|function|unknown_print_range
id|unknown_print_range
c_func
(paren
r_char
op_star
id|buffer
comma
r_const
r_struct
id|ip_nat_range
op_star
id|range
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|unknown_nat_protocol
r_struct
id|ip_nat_protocol
id|unknown_nat_protocol
op_assign
(brace
(brace
l_int|NULL
comma
l_int|NULL
)brace
comma
l_string|&quot;unknown&quot;
comma
l_int|0
comma
id|unknown_manip_pkt
comma
id|unknown_in_range
comma
id|unknown_unique_tuple
comma
id|unknown_print
comma
id|unknown_print_range
)brace
suffix:semicolon
eof
