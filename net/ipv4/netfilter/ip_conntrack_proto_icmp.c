macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/netfilter.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/icmp.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_conntrack_protocol.h&gt;
DECL|macro|ICMP_TIMEOUT
mdefine_line|#define ICMP_TIMEOUT (30*HZ)
macro_line|#if 0
mdefine_line|#define DEBUGP printk
macro_line|#else
DECL|macro|DEBUGP
mdefine_line|#define DEBUGP(format, args...)
macro_line|#endif
DECL|function|icmp_pkt_to_tuple
r_static
r_int
id|icmp_pkt_to_tuple
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
r_struct
id|icmphdr
id|hdr
suffix:semicolon
r_if
c_cond
(paren
id|skb_copy_bits
c_func
(paren
id|skb
comma
id|dataoff
comma
op_amp
id|hdr
comma
r_sizeof
(paren
id|hdr
)paren
)paren
op_ne
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|tuple-&gt;dst.u.icmp.type
op_assign
id|hdr.type
suffix:semicolon
id|tuple-&gt;src.u.icmp.id
op_assign
id|hdr.un.echo.id
suffix:semicolon
id|tuple-&gt;dst.u.icmp.code
op_assign
id|hdr.code
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|icmp_invert_tuple
r_static
r_int
id|icmp_invert_tuple
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
multiline_comment|/* Add 1; spaces filled with 0. */
r_static
id|u_int8_t
id|invmap
(braket
)braket
op_assign
(brace
(braket
id|ICMP_ECHO
)braket
op_assign
id|ICMP_ECHOREPLY
op_plus
l_int|1
comma
(braket
id|ICMP_ECHOREPLY
)braket
op_assign
id|ICMP_ECHO
op_plus
l_int|1
comma
(braket
id|ICMP_TIMESTAMP
)braket
op_assign
id|ICMP_TIMESTAMPREPLY
op_plus
l_int|1
comma
(braket
id|ICMP_TIMESTAMPREPLY
)braket
op_assign
id|ICMP_TIMESTAMP
op_plus
l_int|1
comma
(braket
id|ICMP_INFO_REQUEST
)braket
op_assign
id|ICMP_INFO_REPLY
op_plus
l_int|1
comma
(braket
id|ICMP_INFO_REPLY
)braket
op_assign
id|ICMP_INFO_REQUEST
op_plus
l_int|1
comma
(braket
id|ICMP_ADDRESS
)braket
op_assign
id|ICMP_ADDRESSREPLY
op_plus
l_int|1
comma
(braket
id|ICMP_ADDRESSREPLY
)braket
op_assign
id|ICMP_ADDRESS
op_plus
l_int|1
)brace
suffix:semicolon
r_if
c_cond
(paren
id|orig-&gt;dst.u.icmp.type
op_ge
r_sizeof
(paren
id|invmap
)paren
op_logical_or
op_logical_neg
id|invmap
(braket
id|orig-&gt;dst.u.icmp.type
)braket
)paren
r_return
l_int|0
suffix:semicolon
id|tuple-&gt;src.u.icmp.id
op_assign
id|orig-&gt;src.u.icmp.id
suffix:semicolon
id|tuple-&gt;dst.u.icmp.type
op_assign
id|invmap
(braket
id|orig-&gt;dst.u.icmp.type
)braket
op_minus
l_int|1
suffix:semicolon
id|tuple-&gt;dst.u.icmp.code
op_assign
id|orig-&gt;dst.u.icmp.code
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Print out the per-protocol part of the tuple. */
DECL|function|icmp_print_tuple
r_static
r_int
r_int
id|icmp_print_tuple
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
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;type=%u code=%u id=%u &quot;
comma
id|tuple-&gt;dst.u.icmp.type
comma
id|tuple-&gt;dst.u.icmp.code
comma
id|ntohs
c_func
(paren
id|tuple-&gt;src.u.icmp.id
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Print out the private part of the conntrack. */
DECL|function|icmp_print_conntrack
r_static
r_int
r_int
id|icmp_print_conntrack
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
id|conntrack
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Returns verdict for packet, or -1 for invalid. */
DECL|function|icmp_packet
r_static
r_int
id|icmp_packet
c_func
(paren
r_struct
id|ip_conntrack
op_star
id|ct
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
multiline_comment|/* Try to delete connection immediately after all replies:&n;           won&squot;t actually vanish as we still have skb, and del_timer&n;           means this will only run once even if count hits zero twice&n;           (theoretically possible with SMP) */
r_if
c_cond
(paren
id|CTINFO2DIR
c_func
(paren
id|ctinfo
)paren
op_eq
id|IP_CT_DIR_REPLY
)paren
(brace
r_if
c_cond
(paren
id|atomic_dec_and_test
c_func
(paren
op_amp
id|ct-&gt;proto.icmp.count
)paren
op_logical_and
id|del_timer
c_func
(paren
op_amp
id|ct-&gt;timeout
)paren
)paren
id|ct-&gt;timeout
dot
id|function
c_func
(paren
(paren
r_int
r_int
)paren
id|ct
)paren
suffix:semicolon
)brace
r_else
(brace
id|atomic_inc
c_func
(paren
op_amp
id|ct-&gt;proto.icmp.count
)paren
suffix:semicolon
id|ip_ct_refresh
c_func
(paren
id|ct
comma
id|ICMP_TIMEOUT
)paren
suffix:semicolon
)brace
r_return
id|NF_ACCEPT
suffix:semicolon
)brace
multiline_comment|/* Called when a new connection for this protocol found. */
DECL|function|icmp_new
r_static
r_int
id|icmp_new
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
)paren
(brace
r_static
id|u_int8_t
id|valid_new
(braket
)braket
op_assign
(brace
(braket
id|ICMP_ECHO
)braket
op_assign
l_int|1
comma
(braket
id|ICMP_TIMESTAMP
)braket
op_assign
l_int|1
comma
(braket
id|ICMP_INFO_REQUEST
)braket
op_assign
l_int|1
comma
(braket
id|ICMP_ADDRESS
)braket
op_assign
l_int|1
)brace
suffix:semicolon
r_if
c_cond
(paren
id|conntrack-&gt;tuplehash
(braket
l_int|0
)braket
dot
id|tuple.dst.u.icmp.type
op_ge
r_sizeof
(paren
id|valid_new
)paren
op_logical_or
op_logical_neg
id|valid_new
(braket
id|conntrack-&gt;tuplehash
(braket
l_int|0
)braket
dot
id|tuple.dst.u.icmp.type
)braket
)paren
(brace
multiline_comment|/* Can&squot;t create a new ICMP `conn&squot; with this. */
id|DEBUGP
c_func
(paren
l_string|&quot;icmp: can&squot;t create new conn with type %u&bslash;n&quot;
comma
id|conntrack-&gt;tuplehash
(braket
l_int|0
)braket
dot
id|tuple.dst.u.icmp.type
)paren
suffix:semicolon
id|DUMP_TUPLE
c_func
(paren
op_amp
id|conntrack-&gt;tuplehash
(braket
l_int|0
)braket
dot
id|tuple
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|atomic_set
c_func
(paren
op_amp
id|conntrack-&gt;proto.icmp.count
comma
l_int|0
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|variable|ip_conntrack_protocol_icmp
r_struct
id|ip_conntrack_protocol
id|ip_conntrack_protocol_icmp
op_assign
(brace
(brace
l_int|NULL
comma
l_int|NULL
)brace
comma
id|IPPROTO_ICMP
comma
l_string|&quot;icmp&quot;
comma
id|icmp_pkt_to_tuple
comma
id|icmp_invert_tuple
comma
id|icmp_print_tuple
comma
id|icmp_print_conntrack
comma
id|icmp_packet
comma
id|icmp_new
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
)brace
suffix:semicolon
eof
