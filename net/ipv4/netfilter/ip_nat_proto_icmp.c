macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/netfilter.h&gt;
macro_line|#include &lt;linux/ip.h&gt;
macro_line|#include &lt;linux/icmp.h&gt;
macro_line|#include &lt;linux/if.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_nat.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_nat_rule.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_nat_protocol.h&gt;
r_static
r_int
DECL|function|icmp_in_range
id|icmp_in_range
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
id|maniptype
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
(paren
id|tuple-&gt;src.u.icmp.id
op_ge
id|min-&gt;icmp.id
op_logical_and
id|tuple-&gt;src.u.icmp.id
op_le
id|max-&gt;icmp.id
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|icmp_unique_tuple
id|icmp_unique_tuple
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
r_static
id|u_int16_t
id|id
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|range_size
op_assign
(paren
r_int
r_int
)paren
id|range-&gt;max.icmp.id
op_minus
id|range-&gt;min.icmp.id
op_plus
l_int|1
suffix:semicolon
r_int
r_int
id|i
suffix:semicolon
multiline_comment|/* If no range specified... */
r_if
c_cond
(paren
op_logical_neg
(paren
id|range-&gt;flags
op_amp
id|IP_NAT_RANGE_PROTO_SPECIFIED
)paren
)paren
id|range_size
op_assign
l_int|0xFFFF
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
id|range_size
suffix:semicolon
id|i
op_increment
comma
id|id
op_increment
)paren
(brace
id|tuple-&gt;src.u.icmp.id
op_assign
id|range-&gt;min.icmp.id
op_plus
(paren
id|id
op_mod
id|range_size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ip_nat_used_tuple
c_func
(paren
id|tuple
comma
id|conntrack
)paren
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
DECL|function|icmp_manip_pkt
id|icmp_manip_pkt
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
id|hdroff
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
r_struct
id|icmphdr
op_star
id|hdr
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|skb_ip_make_writable
c_func
(paren
id|pskb
comma
id|hdroff
op_plus
r_sizeof
(paren
op_star
id|hdr
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|hdr
op_assign
(paren
r_void
op_star
)paren
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|data
op_plus
id|hdroff
suffix:semicolon
id|hdr-&gt;checksum
op_assign
id|ip_nat_cheat_check
c_func
(paren
id|hdr-&gt;un.echo.id
op_xor
l_int|0xFFFF
comma
id|manip-&gt;u.icmp.id
comma
id|hdr-&gt;checksum
)paren
suffix:semicolon
id|hdr-&gt;un.echo.id
op_assign
id|manip-&gt;u.icmp.id
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_static
r_int
r_int
DECL|function|icmp_print
id|icmp_print
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
r_int
r_int
id|len
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|mask-&gt;src.u.icmp.id
)paren
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;id=%u &quot;
comma
id|ntohs
c_func
(paren
id|match-&gt;src.u.icmp.id
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mask-&gt;dst.u.icmp.type
)paren
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;type=%u &quot;
comma
id|ntohs
c_func
(paren
id|match-&gt;dst.u.icmp.type
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mask-&gt;dst.u.icmp.code
)paren
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;code=%u &quot;
comma
id|ntohs
c_func
(paren
id|match-&gt;dst.u.icmp.code
)paren
)paren
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
r_static
r_int
r_int
DECL|function|icmp_print_range
id|icmp_print_range
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
r_if
c_cond
(paren
id|range-&gt;min.icmp.id
op_ne
l_int|0
op_logical_or
id|range-&gt;max.icmp.id
op_ne
l_int|0xFFFF
)paren
r_return
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;id %u-%u &quot;
comma
id|ntohs
c_func
(paren
id|range-&gt;min.icmp.id
)paren
comma
id|ntohs
c_func
(paren
id|range-&gt;max.icmp.id
)paren
)paren
suffix:semicolon
r_else
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|ip_nat_protocol_icmp
r_struct
id|ip_nat_protocol
id|ip_nat_protocol_icmp
op_assign
(brace
(brace
l_int|NULL
comma
l_int|NULL
)brace
comma
l_string|&quot;ICMP&quot;
comma
id|IPPROTO_ICMP
comma
id|icmp_manip_pkt
comma
id|icmp_in_range
comma
id|icmp_unique_tuple
comma
id|icmp_print
comma
id|icmp_print_range
)brace
suffix:semicolon
eof
