macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/netfilter.h&gt;
macro_line|#include &lt;linux/ip.h&gt;
macro_line|#include &lt;linux/udp.h&gt;
macro_line|#include &lt;linux/if.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_nat.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_nat_core.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_nat_rule.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_nat_protocol.h&gt;
r_static
r_int
DECL|function|udp_in_range
id|udp_in_range
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
id|u_int16_t
id|port
suffix:semicolon
r_if
c_cond
(paren
id|maniptype
op_eq
id|IP_NAT_MANIP_SRC
)paren
id|port
op_assign
id|tuple-&gt;src.u.udp.port
suffix:semicolon
r_else
id|port
op_assign
id|tuple-&gt;dst.u.udp.port
suffix:semicolon
r_return
id|ntohs
c_func
(paren
id|port
)paren
op_ge
id|ntohs
c_func
(paren
id|min-&gt;udp.port
)paren
op_logical_and
id|ntohs
c_func
(paren
id|port
)paren
op_le
id|ntohs
c_func
(paren
id|max-&gt;udp.port
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|udp_unique_tuple
id|udp_unique_tuple
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
id|port
op_assign
l_int|0
comma
op_star
id|portptr
suffix:semicolon
r_int
r_int
id|range_size
comma
id|min
comma
id|i
suffix:semicolon
r_if
c_cond
(paren
id|maniptype
op_eq
id|IP_NAT_MANIP_SRC
)paren
id|portptr
op_assign
op_amp
id|tuple-&gt;src.u.udp.port
suffix:semicolon
r_else
id|portptr
op_assign
op_amp
id|tuple-&gt;dst.u.udp.port
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
(brace
multiline_comment|/* If it&squot;s dst rewrite, can&squot;t change port */
r_if
c_cond
(paren
id|maniptype
op_eq
id|IP_NAT_MANIP_DST
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|ntohs
c_func
(paren
op_star
id|portptr
)paren
OL
l_int|1024
)paren
(brace
multiline_comment|/* Loose convention: &gt;&gt; 512 is credential passing */
r_if
c_cond
(paren
id|ntohs
c_func
(paren
op_star
id|portptr
)paren
OL
l_int|512
)paren
(brace
id|min
op_assign
l_int|1
suffix:semicolon
id|range_size
op_assign
l_int|511
op_minus
id|min
op_plus
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|min
op_assign
l_int|600
suffix:semicolon
id|range_size
op_assign
l_int|1023
op_minus
id|min
op_plus
l_int|1
suffix:semicolon
)brace
)brace
r_else
(brace
id|min
op_assign
l_int|1024
suffix:semicolon
id|range_size
op_assign
l_int|65535
op_minus
l_int|1024
op_plus
l_int|1
suffix:semicolon
)brace
)brace
r_else
(brace
id|min
op_assign
id|ntohs
c_func
(paren
id|range-&gt;min.udp.port
)paren
suffix:semicolon
id|range_size
op_assign
id|ntohs
c_func
(paren
id|range-&gt;max.udp.port
)paren
op_minus
id|min
op_plus
l_int|1
suffix:semicolon
)brace
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
id|port
op_increment
)paren
(brace
op_star
id|portptr
op_assign
id|htons
c_func
(paren
id|min
op_plus
id|port
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
DECL|function|udp_manip_pkt
id|udp_manip_pkt
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
id|udphdr
op_star
id|hdr
suffix:semicolon
id|u_int32_t
id|oldip
suffix:semicolon
id|u_int16_t
op_star
id|portptr
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
r_if
c_cond
(paren
id|maniptype
op_eq
id|IP_NAT_MANIP_SRC
)paren
(brace
multiline_comment|/* Get rid of src ip and src pt */
id|oldip
op_assign
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nh.iph-&gt;saddr
suffix:semicolon
id|portptr
op_assign
op_amp
id|hdr-&gt;source
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Get rid of dst ip and dst pt */
id|oldip
op_assign
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nh.iph-&gt;daddr
suffix:semicolon
id|portptr
op_assign
op_amp
id|hdr-&gt;dest
suffix:semicolon
)brace
r_if
c_cond
(paren
id|hdr-&gt;check
)paren
multiline_comment|/* 0 is a special case meaning no checksum */
id|hdr-&gt;check
op_assign
id|ip_nat_cheat_check
c_func
(paren
op_complement
id|oldip
comma
id|manip-&gt;ip
comma
id|ip_nat_cheat_check
c_func
(paren
op_star
id|portptr
op_xor
l_int|0xFFFF
comma
id|manip-&gt;u.udp.port
comma
id|hdr-&gt;check
)paren
)paren
suffix:semicolon
op_star
id|portptr
op_assign
id|manip-&gt;u.udp.port
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_static
r_int
r_int
DECL|function|udp_print
id|udp_print
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
id|mask-&gt;src.u.udp.port
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
l_string|&quot;srcpt=%u &quot;
comma
id|ntohs
c_func
(paren
id|match-&gt;src.u.udp.port
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mask-&gt;dst.u.udp.port
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
l_string|&quot;dstpt=%u &quot;
comma
id|ntohs
c_func
(paren
id|match-&gt;dst.u.udp.port
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
DECL|function|udp_print_range
id|udp_print_range
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
id|range-&gt;min.udp.port
op_ne
l_int|0
op_logical_or
id|range-&gt;max.udp.port
op_ne
l_int|0xFFFF
)paren
(brace
r_if
c_cond
(paren
id|range-&gt;min.udp.port
op_eq
id|range-&gt;max.udp.port
)paren
r_return
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;port %u &quot;
comma
id|ntohs
c_func
(paren
id|range-&gt;min.udp.port
)paren
)paren
suffix:semicolon
r_else
r_return
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;ports %u-%u &quot;
comma
id|ntohs
c_func
(paren
id|range-&gt;min.udp.port
)paren
comma
id|ntohs
c_func
(paren
id|range-&gt;max.udp.port
)paren
)paren
suffix:semicolon
)brace
r_else
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|ip_nat_protocol_udp
r_struct
id|ip_nat_protocol
id|ip_nat_protocol_udp
op_assign
(brace
(brace
l_int|NULL
comma
l_int|NULL
)brace
comma
l_string|&quot;UDP&quot;
comma
id|IPPROTO_UDP
comma
id|udp_manip_pkt
comma
id|udp_in_range
comma
id|udp_unique_tuple
comma
id|udp_print
comma
id|udp_print_range
)brace
suffix:semicolon
eof
