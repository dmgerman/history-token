multiline_comment|/* Kernel module to match suspect packets. */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/ip.h&gt;
macro_line|#include &lt;linux/udp.h&gt;
macro_line|#include &lt;linux/tcp.h&gt;
macro_line|#include &lt;linux/icmp.h&gt;
macro_line|#include &lt;net/checksum.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_tables.h&gt;
DECL|macro|limpk
mdefine_line|#define limpk(format, args...)&t;&t;&t;&t;&t;&t; &bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t; &bslash;&n;&t;if (net_ratelimit())&t;&t;&t;&t;&t;&t; &bslash;&n;&t;&t;printk(&quot;ipt_unclean: %s&quot; format,&t;&t;&t; &bslash;&n;&t;&t;       embedded ? &quot;(embedded packet) &quot; : &quot;&quot; , ## args);  &bslash;&n;} while(0)
DECL|enum|icmp_error_status
r_enum
id|icmp_error_status
(brace
DECL|enumerator|ICMP_MAY_BE_ERROR
id|ICMP_MAY_BE_ERROR
comma
DECL|enumerator|ICMP_IS_ERROR
id|ICMP_IS_ERROR
comma
DECL|enumerator|ICMP_NOT_ERROR
id|ICMP_NOT_ERROR
)brace
suffix:semicolon
DECL|struct|icmp_info
r_struct
id|icmp_info
(brace
DECL|member|min_len
DECL|member|max_len
r_int
id|min_len
comma
id|max_len
suffix:semicolon
DECL|member|err
r_enum
id|icmp_error_status
id|err
suffix:semicolon
DECL|member|min_code
DECL|member|max_code
id|u_int8_t
id|min_code
comma
id|max_code
suffix:semicolon
)brace
suffix:semicolon
r_static
r_int
id|check_ip
c_func
(paren
r_struct
id|iphdr
op_star
id|iph
comma
r_int
id|length
comma
r_int
id|embedded
)paren
suffix:semicolon
multiline_comment|/* ICMP-specific checks. */
r_static
r_int
DECL|function|check_icmp
id|check_icmp
c_func
(paren
r_const
r_struct
id|icmphdr
op_star
id|icmph
comma
id|u_int16_t
id|datalen
comma
r_int
r_int
id|offset
comma
r_int
id|more_frags
comma
r_int
id|embedded
)paren
(brace
r_static
r_struct
id|icmp_info
id|info
(braket
)braket
op_assign
(brace
(braket
id|ICMP_ECHOREPLY
)braket
op_assign
(brace
l_int|8
comma
l_int|65536
comma
id|ICMP_NOT_ERROR
comma
l_int|0
comma
l_int|0
)brace
comma
(braket
id|ICMP_DEST_UNREACH
)braket
op_assign
(brace
l_int|8
op_plus
l_int|28
comma
l_int|65536
comma
id|ICMP_IS_ERROR
comma
l_int|0
comma
l_int|15
)brace
comma
(braket
id|ICMP_SOURCE_QUENCH
)braket
op_assign
(brace
l_int|8
op_plus
l_int|28
comma
l_int|65536
comma
id|ICMP_IS_ERROR
comma
l_int|0
comma
l_int|0
)brace
comma
(braket
id|ICMP_REDIRECT
)braket
op_assign
(brace
l_int|8
op_plus
l_int|28
comma
l_int|65536
comma
id|ICMP_IS_ERROR
comma
l_int|0
comma
l_int|3
)brace
comma
(braket
id|ICMP_ECHO
)braket
op_assign
(brace
l_int|8
comma
l_int|65536
comma
id|ICMP_NOT_ERROR
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* Router advertisement. */
(braket
l_int|9
)braket
op_assign
(brace
l_int|8
comma
l_int|8
op_plus
l_int|255
op_star
l_int|8
comma
id|ICMP_NOT_ERROR
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* Router solicitation. */
(braket
l_int|10
)braket
op_assign
(brace
l_int|8
comma
l_int|8
comma
id|ICMP_NOT_ERROR
comma
l_int|0
comma
l_int|0
)brace
comma
(braket
id|ICMP_TIME_EXCEEDED
)braket
op_assign
(brace
l_int|8
op_plus
l_int|28
comma
l_int|65536
comma
id|ICMP_IS_ERROR
comma
l_int|0
comma
l_int|1
)brace
comma
(braket
id|ICMP_PARAMETERPROB
)braket
op_assign
(brace
l_int|8
op_plus
l_int|28
comma
l_int|65536
comma
id|ICMP_IS_ERROR
comma
l_int|0
comma
l_int|1
)brace
comma
(braket
id|ICMP_TIMESTAMP
)braket
op_assign
(brace
l_int|20
comma
l_int|20
comma
id|ICMP_NOT_ERROR
comma
l_int|0
comma
l_int|0
)brace
comma
(braket
id|ICMP_TIMESTAMPREPLY
)braket
op_assign
(brace
l_int|20
comma
l_int|20
comma
id|ICMP_NOT_ERROR
comma
l_int|0
comma
l_int|0
)brace
comma
(braket
id|ICMP_INFO_REQUEST
)braket
op_assign
(brace
l_int|8
comma
l_int|65536
comma
id|ICMP_NOT_ERROR
comma
l_int|0
comma
l_int|0
)brace
comma
(braket
id|ICMP_INFO_REPLY
)braket
op_assign
(brace
l_int|8
comma
l_int|65536
comma
id|ICMP_NOT_ERROR
comma
l_int|0
comma
l_int|0
)brace
comma
(braket
id|ICMP_ADDRESS
)braket
op_assign
(brace
l_int|12
comma
l_int|12
comma
id|ICMP_NOT_ERROR
comma
l_int|0
comma
l_int|0
)brace
comma
(braket
id|ICMP_ADDRESSREPLY
)braket
op_assign
(brace
l_int|12
comma
l_int|12
comma
id|ICMP_NOT_ERROR
comma
l_int|0
comma
l_int|0
)brace
)brace
suffix:semicolon
multiline_comment|/* Can&squot;t do anything if it&squot;s a fragment. */
r_if
c_cond
(paren
id|offset
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* Must cover type and code. */
r_if
c_cond
(paren
id|datalen
OL
l_int|2
)paren
(brace
id|limpk
c_func
(paren
l_string|&quot;ICMP len=%u too short&bslash;n&quot;
comma
id|datalen
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* If not embedded. */
r_if
c_cond
(paren
op_logical_neg
id|embedded
)paren
(brace
multiline_comment|/* Bad checksum?  Don&squot;t print, just ignore. */
r_if
c_cond
(paren
op_logical_neg
id|more_frags
op_logical_and
id|ip_compute_csum
c_func
(paren
(paren
r_int
r_char
op_star
)paren
id|icmph
comma
id|datalen
)paren
op_ne
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* CHECK: Truncated ICMP (even if first fragment). */
r_if
c_cond
(paren
id|icmph-&gt;type
OL
r_sizeof
(paren
id|info
)paren
op_div
r_sizeof
(paren
r_struct
id|icmp_info
)paren
op_logical_and
id|info
(braket
id|icmph-&gt;type
)braket
dot
id|min_len
op_ne
l_int|0
op_logical_and
id|datalen
OL
id|info
(braket
id|icmph-&gt;type
)braket
dot
id|min_len
)paren
(brace
id|limpk
c_func
(paren
l_string|&quot;ICMP type %u len %u too short&bslash;n&quot;
comma
id|icmph-&gt;type
comma
id|datalen
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* CHECK: Check within known error ICMPs. */
r_if
c_cond
(paren
id|icmph-&gt;type
OL
r_sizeof
(paren
id|info
)paren
op_div
r_sizeof
(paren
r_struct
id|icmp_info
)paren
op_logical_and
id|info
(braket
id|icmph-&gt;type
)braket
dot
id|err
op_eq
id|ICMP_IS_ERROR
)paren
(brace
multiline_comment|/* CHECK: Embedded packet must be at least&n;&t;&t;&t;   length of iph + 8 bytes. */
r_struct
id|iphdr
op_star
id|inner
op_assign
(paren
r_void
op_star
)paren
id|icmph
op_plus
l_int|8
suffix:semicolon
multiline_comment|/* datalen &gt; 8 since all ICMP_IS_ERROR types&n;                           have min length &gt; 8 */
r_if
c_cond
(paren
id|datalen
op_minus
l_int|8
OL
r_sizeof
(paren
r_struct
id|iphdr
)paren
)paren
(brace
id|limpk
c_func
(paren
l_string|&quot;ICMP error internal way too short&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|datalen
op_minus
l_int|8
OL
id|inner-&gt;ihl
op_star
l_int|4
op_plus
l_int|8
)paren
(brace
id|limpk
c_func
(paren
l_string|&quot;ICMP error internal too short&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|check_ip
c_func
(paren
id|inner
comma
id|datalen
op_minus
l_int|8
comma
l_int|1
)paren
)paren
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* CHECK: Can&squot;t embed ICMP unless known non-error. */
r_if
c_cond
(paren
id|icmph-&gt;type
op_ge
r_sizeof
(paren
id|info
)paren
op_div
r_sizeof
(paren
r_struct
id|icmp_info
)paren
op_logical_or
id|info
(braket
id|icmph-&gt;type
)braket
dot
id|err
op_ne
id|ICMP_NOT_ERROR
)paren
(brace
id|limpk
c_func
(paren
l_string|&quot;ICMP type %u not embeddable&bslash;n&quot;
comma
id|icmph-&gt;type
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
multiline_comment|/* CHECK: Invalid ICMP codes. */
r_if
c_cond
(paren
id|icmph-&gt;type
OL
r_sizeof
(paren
id|info
)paren
op_div
r_sizeof
(paren
r_struct
id|icmp_info
)paren
op_logical_and
(paren
id|icmph-&gt;code
template_param
id|info
(braket
id|icmph-&gt;type
)braket
dot
id|max_code
)paren
)paren
(brace
id|limpk
c_func
(paren
l_string|&quot;ICMP type=%u code=%u&bslash;n&quot;
comma
id|icmph-&gt;type
comma
id|icmph-&gt;code
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* CHECK: Above maximum length. */
r_if
c_cond
(paren
id|icmph-&gt;type
template_param
id|info
(braket
id|icmph-&gt;type
)braket
dot
id|max_len
)paren
(brace
id|limpk
c_func
(paren
l_string|&quot;ICMP type=%u too long: %u bytes&bslash;n&quot;
comma
id|icmph-&gt;type
comma
id|datalen
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|icmph-&gt;type
)paren
(brace
r_case
id|ICMP_PARAMETERPROB
suffix:colon
(brace
multiline_comment|/* CHECK: Problem param must be within error packet&squot;s&n;&t;&t; * IP header. */
r_struct
id|iphdr
op_star
id|iph
op_assign
(paren
r_void
op_star
)paren
id|icmph
op_plus
l_int|8
suffix:semicolon
id|u_int32_t
id|arg
op_assign
id|ntohl
c_func
(paren
id|icmph-&gt;un.gateway
)paren
suffix:semicolon
r_if
c_cond
(paren
id|icmph-&gt;code
op_eq
l_int|0
)paren
(brace
multiline_comment|/* Code 0 means that upper 8 bits is pointer&n;                           to problem. */
r_if
c_cond
(paren
(paren
id|arg
op_rshift
l_int|24
)paren
op_ge
id|iph-&gt;ihl
op_star
l_int|4
)paren
(brace
id|limpk
c_func
(paren
l_string|&quot;ICMP PARAMETERPROB ptr = %u&bslash;n&quot;
comma
id|ntohl
c_func
(paren
id|icmph-&gt;un.gateway
)paren
op_rshift
l_int|24
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|arg
op_and_assign
l_int|0x00FFFFFF
suffix:semicolon
)brace
multiline_comment|/* CHECK: Rest must be zero. */
r_if
c_cond
(paren
id|arg
)paren
(brace
id|limpk
c_func
(paren
l_string|&quot;ICMP PARAMETERPROB nonzero arg = %u&bslash;n&quot;
comma
id|arg
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
r_case
id|ICMP_TIME_EXCEEDED
suffix:colon
r_case
id|ICMP_SOURCE_QUENCH
suffix:colon
multiline_comment|/* CHECK: Unused must be zero. */
r_if
c_cond
(paren
id|icmph-&gt;un.gateway
op_ne
l_int|0
)paren
(brace
id|limpk
c_func
(paren
l_string|&quot;ICMP type=%u unused = %u&bslash;n&quot;
comma
id|icmph-&gt;type
comma
id|ntohl
c_func
(paren
id|icmph-&gt;un.gateway
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* UDP-specific checks. */
r_static
r_int
DECL|function|check_udp
id|check_udp
c_func
(paren
r_const
r_struct
id|iphdr
op_star
id|iph
comma
r_const
r_struct
id|udphdr
op_star
id|udph
comma
id|u_int16_t
id|datalen
comma
r_int
r_int
id|offset
comma
r_int
id|more_frags
comma
r_int
id|embedded
)paren
(brace
multiline_comment|/* Can&squot;t do anything if it&squot;s a fragment. */
r_if
c_cond
(paren
id|offset
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* CHECK: Must cover UDP header. */
r_if
c_cond
(paren
id|datalen
OL
r_sizeof
(paren
r_struct
id|udphdr
)paren
)paren
(brace
id|limpk
c_func
(paren
l_string|&quot;UDP len=%u too short&bslash;n&quot;
comma
id|datalen
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Bad checksum?  Don&squot;t print, just say it&squot;s unclean. */
multiline_comment|/* FIXME: SRC ROUTE packets won&squot;t match checksum --RR */
r_if
c_cond
(paren
op_logical_neg
id|more_frags
op_logical_and
op_logical_neg
id|embedded
op_logical_and
id|csum_tcpudp_magic
c_func
(paren
id|iph-&gt;saddr
comma
id|iph-&gt;daddr
comma
id|datalen
comma
id|IPPROTO_UDP
comma
id|csum_partial
c_func
(paren
(paren
r_char
op_star
)paren
id|udph
comma
id|datalen
comma
l_int|0
)paren
)paren
op_ne
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* CHECK: Ports can&squot;t be zero. */
r_if
c_cond
(paren
op_logical_neg
id|udph-&gt;source
op_logical_or
op_logical_neg
id|udph-&gt;dest
)paren
(brace
id|limpk
c_func
(paren
l_string|&quot;UDP zero ports %u/%u&bslash;n&quot;
comma
id|ntohs
c_func
(paren
id|udph-&gt;source
)paren
comma
id|ntohs
c_func
(paren
id|udph-&gt;dest
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|more_frags
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|embedded
)paren
(brace
multiline_comment|/* CHECK: UDP length must match. */
r_if
c_cond
(paren
id|ntohs
c_func
(paren
id|udph-&gt;len
)paren
op_ne
id|datalen
)paren
(brace
id|limpk
c_func
(paren
l_string|&quot;UDP len too short %u vs %u&bslash;n&quot;
comma
id|ntohs
c_func
(paren
id|udph-&gt;len
)paren
comma
id|datalen
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* CHECK: UDP length be &gt;= this truncated pkt. */
r_if
c_cond
(paren
id|ntohs
c_func
(paren
id|udph-&gt;len
)paren
OL
id|datalen
)paren
(brace
id|limpk
c_func
(paren
l_string|&quot;UDP len too long %u vs %u&bslash;n&quot;
comma
id|ntohs
c_func
(paren
id|udph-&gt;len
)paren
comma
id|datalen
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
)brace
r_else
(brace
multiline_comment|/* CHECK: UDP length must be &gt; this frag&squot;s length. */
r_if
c_cond
(paren
id|ntohs
c_func
(paren
id|udph-&gt;len
)paren
op_le
id|datalen
)paren
(brace
id|limpk
c_func
(paren
l_string|&quot;UDP fragment len too short %u vs %u&bslash;n&quot;
comma
id|ntohs
c_func
(paren
id|udph-&gt;len
)paren
comma
id|datalen
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|macro|TH_FIN
mdefine_line|#define&t;TH_FIN&t;0x01
DECL|macro|TH_SYN
mdefine_line|#define&t;TH_SYN&t;0x02
DECL|macro|TH_RST
mdefine_line|#define&t;TH_RST&t;0x04
DECL|macro|TH_PUSH
mdefine_line|#define&t;TH_PUSH&t;0x08
DECL|macro|TH_ACK
mdefine_line|#define&t;TH_ACK&t;0x10
DECL|macro|TH_URG
mdefine_line|#define&t;TH_URG&t;0x20
multiline_comment|/* TCP-specific checks. */
r_static
r_int
DECL|function|check_tcp
id|check_tcp
c_func
(paren
r_const
r_struct
id|iphdr
op_star
id|iph
comma
r_const
r_struct
id|tcphdr
op_star
id|tcph
comma
id|u_int16_t
id|datalen
comma
r_int
r_int
id|offset
comma
r_int
id|more_frags
comma
r_int
id|embedded
)paren
(brace
id|u_int8_t
op_star
id|opt
op_assign
(paren
id|u_int8_t
op_star
)paren
id|tcph
suffix:semicolon
id|u_int8_t
op_star
id|endhdr
op_assign
(paren
id|u_int8_t
op_star
)paren
id|tcph
op_plus
id|tcph-&gt;doff
op_star
l_int|4
suffix:semicolon
id|u_int8_t
id|tcpflags
suffix:semicolon
r_int
id|end_of_options
op_assign
l_int|0
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/* CHECK: Can&squot;t have offset=1: used to override TCP syn-checks. */
multiline_comment|/* In fact, this is caught below (offset &lt; 516). */
multiline_comment|/* Can&squot;t do anything if it&squot;s a fragment. */
r_if
c_cond
(paren
id|offset
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* CHECK: Smaller than minimal TCP hdr. */
r_if
c_cond
(paren
id|datalen
OL
r_sizeof
(paren
r_struct
id|tcphdr
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|embedded
)paren
(brace
id|limpk
c_func
(paren
l_string|&quot;Packet length %u &lt; TCP header.&bslash;n&quot;
comma
id|datalen
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Must have ports available (datalen &gt;= 8), from&n;                   check_icmp which set embedded = 1 */
multiline_comment|/* CHECK: TCP ports inside ICMP error */
r_if
c_cond
(paren
op_logical_neg
id|tcph-&gt;source
op_logical_or
op_logical_neg
id|tcph-&gt;dest
)paren
(brace
id|limpk
c_func
(paren
l_string|&quot;Zero TCP ports %u/%u.&bslash;n&quot;
comma
id|htons
c_func
(paren
id|tcph-&gt;source
)paren
comma
id|htons
c_func
(paren
id|tcph-&gt;dest
)paren
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
multiline_comment|/* CHECK: Smaller than actual TCP hdr. */
r_if
c_cond
(paren
id|datalen
OL
id|tcph-&gt;doff
op_star
l_int|4
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|embedded
)paren
(brace
id|limpk
c_func
(paren
l_string|&quot;Packet length %u &lt; actual TCP header.&bslash;n&quot;
comma
id|datalen
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_else
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Bad checksum?  Don&squot;t print, just say it&squot;s unclean. */
multiline_comment|/* FIXME: SRC ROUTE packets won&squot;t match checksum --RR */
r_if
c_cond
(paren
op_logical_neg
id|more_frags
op_logical_and
op_logical_neg
id|embedded
op_logical_and
id|csum_tcpudp_magic
c_func
(paren
id|iph-&gt;saddr
comma
id|iph-&gt;daddr
comma
id|datalen
comma
id|IPPROTO_TCP
comma
id|csum_partial
c_func
(paren
(paren
r_char
op_star
)paren
id|tcph
comma
id|datalen
comma
l_int|0
)paren
)paren
op_ne
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* CHECK: TCP ports non-zero */
r_if
c_cond
(paren
op_logical_neg
id|tcph-&gt;source
op_logical_or
op_logical_neg
id|tcph-&gt;dest
)paren
(brace
id|limpk
c_func
(paren
l_string|&quot;Zero TCP ports %u/%u.&bslash;n&quot;
comma
id|htons
c_func
(paren
id|tcph-&gt;source
)paren
comma
id|htons
c_func
(paren
id|tcph-&gt;dest
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* CHECK: TCP reserved bits zero. */
r_if
c_cond
(paren
id|tcp_flag_word
c_func
(paren
id|tcph
)paren
op_amp
id|TCP_RESERVED_BITS
)paren
(brace
id|limpk
c_func
(paren
l_string|&quot;TCP reserved bits not zero&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* CHECK: TCP flags. */
id|tcpflags
op_assign
(paren
(paren
id|u_int8_t
op_star
)paren
id|tcph
)paren
(braket
l_int|13
)braket
suffix:semicolon
r_if
c_cond
(paren
id|tcpflags
op_ne
id|TH_SYN
op_logical_and
id|tcpflags
op_ne
(paren
id|TH_SYN
op_or
id|TH_ACK
)paren
op_logical_and
id|tcpflags
op_ne
(paren
id|TH_RST
op_or
id|TH_ACK
)paren
op_logical_and
id|tcpflags
op_ne
(paren
id|TH_RST
op_or
id|TH_ACK
op_or
id|TH_PUSH
)paren
op_logical_and
id|tcpflags
op_ne
(paren
id|TH_FIN
op_or
id|TH_ACK
)paren
op_logical_and
id|tcpflags
op_ne
id|TH_ACK
op_logical_and
id|tcpflags
op_ne
(paren
id|TH_ACK
op_or
id|TH_PUSH
)paren
op_logical_and
id|tcpflags
op_ne
(paren
id|TH_ACK
op_or
id|TH_URG
)paren
op_logical_and
id|tcpflags
op_ne
(paren
id|TH_ACK
op_or
id|TH_URG
op_or
id|TH_PUSH
)paren
op_logical_and
id|tcpflags
op_ne
(paren
id|TH_FIN
op_or
id|TH_ACK
op_or
id|TH_PUSH
)paren
op_logical_and
id|tcpflags
op_ne
(paren
id|TH_FIN
op_or
id|TH_ACK
op_or
id|TH_URG
)paren
op_logical_and
id|tcpflags
op_ne
(paren
id|TH_FIN
op_or
id|TH_ACK
op_or
id|TH_URG
op_or
id|TH_PUSH
)paren
)paren
(brace
id|limpk
c_func
(paren
l_string|&quot;TCP flags bad: %u&bslash;n&quot;
comma
id|tcpflags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
r_sizeof
(paren
r_struct
id|tcphdr
)paren
suffix:semicolon
id|i
OL
id|tcph-&gt;doff
op_star
l_int|4
suffix:semicolon
)paren
(brace
r_switch
c_cond
(paren
id|opt
(braket
id|i
)braket
)paren
(brace
r_case
l_int|0
suffix:colon
id|end_of_options
op_assign
l_int|1
suffix:semicolon
id|i
op_increment
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|i
op_increment
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
(brace
)brace
multiline_comment|/* CHECK: options after EOO. */
r_if
c_cond
(paren
id|end_of_options
)paren
(brace
id|limpk
c_func
(paren
l_string|&quot;TCP option %u after end&bslash;n&quot;
comma
id|opt
(braket
id|i
)braket
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* CHECK: options at tail. */
r_else
r_if
c_cond
(paren
id|i
op_plus
l_int|1
op_ge
id|tcph-&gt;doff
op_star
l_int|4
)paren
(brace
id|limpk
c_func
(paren
l_string|&quot;TCP option %u at tail&bslash;n&quot;
comma
id|opt
(braket
id|i
)braket
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* CHECK: zero-length options. */
r_else
r_if
c_cond
(paren
id|opt
(braket
id|i
op_plus
l_int|1
)braket
op_eq
l_int|0
)paren
(brace
id|limpk
c_func
(paren
l_string|&quot;TCP option %u 0 len&bslash;n&quot;
comma
id|opt
(braket
id|i
)braket
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* CHECK: oversize options. */
r_else
r_if
c_cond
(paren
op_amp
id|opt
(braket
id|i
)braket
op_plus
id|opt
(braket
id|i
op_plus
l_int|1
)braket
OG
id|endhdr
)paren
(brace
id|limpk
c_func
(paren
l_string|&quot;TCP option %u at %Zu too long&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|opt
(braket
id|i
)braket
comma
id|i
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Move to next option */
id|i
op_add_assign
id|opt
(braket
id|i
op_plus
l_int|1
)braket
suffix:semicolon
)brace
)brace
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Returns 1 if ok */
multiline_comment|/* Standard IP checks. */
r_static
r_int
DECL|function|check_ip
id|check_ip
c_func
(paren
r_struct
id|iphdr
op_star
id|iph
comma
r_int
id|length
comma
r_int
id|embedded
)paren
(brace
id|u_int8_t
op_star
id|opt
op_assign
(paren
id|u_int8_t
op_star
)paren
id|iph
suffix:semicolon
id|u_int8_t
op_star
id|endhdr
op_assign
(paren
id|u_int8_t
op_star
)paren
id|iph
op_plus
id|iph-&gt;ihl
op_star
l_int|4
suffix:semicolon
r_int
id|end_of_options
op_assign
l_int|0
suffix:semicolon
r_void
op_star
id|protoh
suffix:semicolon
r_int
id|datalen
suffix:semicolon
r_int
r_int
id|i
suffix:semicolon
r_int
r_int
id|offset
suffix:semicolon
multiline_comment|/* Should only happen for local outgoing raw-socket packets. */
multiline_comment|/* CHECK: length &gt;= ip header. */
r_if
c_cond
(paren
id|length
OL
r_sizeof
(paren
r_struct
id|iphdr
)paren
op_logical_or
id|length
OL
id|iph-&gt;ihl
op_star
l_int|4
)paren
(brace
id|limpk
c_func
(paren
l_string|&quot;Packet length %Zu &lt; IP header.&bslash;n&quot;
comma
id|length
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|offset
op_assign
id|ntohs
c_func
(paren
id|iph-&gt;frag_off
)paren
op_amp
id|IP_OFFSET
suffix:semicolon
id|protoh
op_assign
(paren
r_void
op_star
)paren
id|iph
op_plus
id|iph-&gt;ihl
op_star
l_int|4
suffix:semicolon
id|datalen
op_assign
id|length
op_minus
id|iph-&gt;ihl
op_star
l_int|4
suffix:semicolon
multiline_comment|/* CHECK: Embedded fragment. */
r_if
c_cond
(paren
id|embedded
op_logical_and
id|offset
)paren
(brace
id|limpk
c_func
(paren
l_string|&quot;Embedded fragment.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
r_sizeof
(paren
r_struct
id|iphdr
)paren
suffix:semicolon
id|i
OL
id|iph-&gt;ihl
op_star
l_int|4
suffix:semicolon
)paren
(brace
r_switch
c_cond
(paren
id|opt
(braket
id|i
)braket
)paren
(brace
r_case
l_int|0
suffix:colon
id|end_of_options
op_assign
l_int|1
suffix:semicolon
id|i
op_increment
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|i
op_increment
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
(brace
)brace
multiline_comment|/* CHECK: options after EOO. */
r_if
c_cond
(paren
id|end_of_options
)paren
(brace
id|limpk
c_func
(paren
l_string|&quot;IP option %u after end&bslash;n&quot;
comma
id|opt
(braket
id|i
)braket
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* CHECK: options at tail. */
r_else
r_if
c_cond
(paren
id|i
op_plus
l_int|1
op_ge
id|iph-&gt;ihl
op_star
l_int|4
)paren
(brace
id|limpk
c_func
(paren
l_string|&quot;IP option %u at tail&bslash;n&quot;
comma
id|opt
(braket
id|i
)braket
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* CHECK: zero-length or one-length options. */
r_else
r_if
c_cond
(paren
id|opt
(braket
id|i
op_plus
l_int|1
)braket
OL
l_int|2
)paren
(brace
id|limpk
c_func
(paren
l_string|&quot;IP option %u %u len&bslash;n&quot;
comma
id|opt
(braket
id|i
)braket
comma
id|opt
(braket
id|i
op_plus
l_int|1
)braket
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* CHECK: oversize options. */
r_else
r_if
c_cond
(paren
op_amp
id|opt
(braket
id|i
)braket
op_plus
id|opt
(braket
id|i
op_plus
l_int|1
)braket
OG
id|endhdr
)paren
(brace
id|limpk
c_func
(paren
l_string|&quot;IP option %u at %u too long&bslash;n&quot;
comma
id|opt
(braket
id|i
)braket
comma
id|i
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Move to next option */
id|i
op_add_assign
id|opt
(braket
id|i
op_plus
l_int|1
)braket
suffix:semicolon
)brace
)brace
multiline_comment|/* Fragment checks. */
multiline_comment|/* CHECK: More fragments, but doesn&squot;t fill 8-byte boundary. */
r_if
c_cond
(paren
(paren
id|ntohs
c_func
(paren
id|iph-&gt;frag_off
)paren
op_amp
id|IP_MF
)paren
op_logical_and
(paren
id|ntohs
c_func
(paren
id|iph-&gt;tot_len
)paren
op_mod
l_int|8
)paren
op_ne
l_int|0
)paren
(brace
id|limpk
c_func
(paren
l_string|&quot;Truncated fragment %u long.&bslash;n&quot;
comma
id|ntohs
c_func
(paren
id|iph-&gt;tot_len
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* CHECK: Oversize fragment a-la Ping of Death. */
r_if
c_cond
(paren
id|offset
op_star
l_int|8
op_plus
id|datalen
OG
l_int|65535
)paren
(brace
id|limpk
c_func
(paren
l_string|&quot;Oversize fragment to %u.&bslash;n&quot;
comma
id|offset
op_star
l_int|8
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* CHECK: DF set and offset or MF set. */
r_if
c_cond
(paren
(paren
id|ntohs
c_func
(paren
id|iph-&gt;frag_off
)paren
op_amp
id|IP_DF
)paren
op_logical_and
(paren
id|offset
op_logical_or
(paren
id|ntohs
c_func
(paren
id|iph-&gt;frag_off
)paren
op_amp
id|IP_MF
)paren
)paren
)paren
(brace
id|limpk
c_func
(paren
l_string|&quot;DF set and offset=%u, MF=%u.&bslash;n&quot;
comma
id|offset
comma
id|ntohs
c_func
(paren
id|iph-&gt;frag_off
)paren
op_amp
id|IP_MF
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* CHECK: Zero-sized fragments. */
r_if
c_cond
(paren
(paren
id|offset
op_logical_or
(paren
id|ntohs
c_func
(paren
id|iph-&gt;frag_off
)paren
op_amp
id|IP_MF
)paren
)paren
op_logical_and
id|datalen
op_eq
l_int|0
)paren
(brace
id|limpk
c_func
(paren
l_string|&quot;Zero size fragment offset=%u&bslash;n&quot;
comma
id|offset
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Note: we can have even middle fragments smaller than this:&n;&t;   consider a large packet passing through a 600MTU then&n;&t;   576MTU link: this gives a fragment of 24 data bytes.  But&n;&t;   everyone packs fragments largest first, hence a fragment&n;&t;   can&squot;t START before 576 - MAX_IP_HEADER_LEN. */
multiline_comment|/* Used to be min-size 576: I recall Alan Cox saying ax25 goes&n;&t;   down to 128 (576 taken from RFC 791: All hosts must be&n;&t;   prepared to accept datagrams of up to 576 octets).  Use 128&n;&t;   here. */
DECL|macro|MIN_LIKELY_MTU
mdefine_line|#define MIN_LIKELY_MTU 128
multiline_comment|/* CHECK: Min size of first frag = 128. */
r_if
c_cond
(paren
(paren
id|ntohs
c_func
(paren
id|iph-&gt;frag_off
)paren
op_amp
id|IP_MF
)paren
op_logical_and
id|offset
op_eq
l_int|0
op_logical_and
id|ntohs
c_func
(paren
id|iph-&gt;tot_len
)paren
OL
id|MIN_LIKELY_MTU
)paren
(brace
id|limpk
c_func
(paren
l_string|&quot;First fragment size %u &lt; %u&bslash;n&quot;
comma
id|ntohs
c_func
(paren
id|iph-&gt;tot_len
)paren
comma
id|MIN_LIKELY_MTU
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* CHECK: Min offset of frag = 128 - IP hdr len. */
r_if
c_cond
(paren
id|offset
op_logical_and
id|offset
op_star
l_int|8
OL
id|MIN_LIKELY_MTU
op_minus
id|iph-&gt;ihl
op_star
l_int|4
)paren
(brace
id|limpk
c_func
(paren
l_string|&quot;Fragment starts at %u &lt; %u&bslash;n&quot;
comma
id|offset
op_star
l_int|8
comma
id|MIN_LIKELY_MTU
op_minus
id|iph-&gt;ihl
op_star
l_int|4
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* CHECK: Protocol specification non-zero. */
r_if
c_cond
(paren
id|iph-&gt;protocol
op_eq
l_int|0
)paren
(brace
id|limpk
c_func
(paren
l_string|&quot;Zero protocol&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Per-protocol checks. */
r_switch
c_cond
(paren
id|iph-&gt;protocol
)paren
(brace
r_case
id|IPPROTO_ICMP
suffix:colon
r_return
id|check_icmp
c_func
(paren
id|protoh
comma
id|datalen
comma
id|offset
comma
(paren
id|ntohs
c_func
(paren
id|iph-&gt;frag_off
)paren
op_amp
id|IP_MF
)paren
comma
id|embedded
)paren
suffix:semicolon
r_case
id|IPPROTO_UDP
suffix:colon
r_return
id|check_udp
c_func
(paren
id|iph
comma
id|protoh
comma
id|datalen
comma
id|offset
comma
(paren
id|ntohs
c_func
(paren
id|iph-&gt;frag_off
)paren
op_amp
id|IP_MF
)paren
comma
id|embedded
)paren
suffix:semicolon
r_case
id|IPPROTO_TCP
suffix:colon
r_return
id|check_tcp
c_func
(paren
id|iph
comma
id|protoh
comma
id|datalen
comma
id|offset
comma
(paren
id|ntohs
c_func
(paren
id|iph-&gt;frag_off
)paren
op_amp
id|IP_MF
)paren
comma
id|embedded
)paren
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* Ignorance is bliss. */
r_return
l_int|1
suffix:semicolon
)brace
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
r_const
r_void
op_star
id|hdr
comma
id|u_int16_t
id|datalen
comma
r_int
op_star
id|hotdrop
)paren
(brace
r_return
op_logical_neg
id|check_ip
c_func
(paren
id|skb-&gt;nh.iph
comma
id|skb-&gt;len
comma
l_int|0
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
r_if
c_cond
(paren
id|matchsize
op_ne
id|IPT_ALIGN
c_func
(paren
l_int|0
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|variable|unclean_match
r_static
r_struct
id|ipt_match
id|unclean_match
op_assign
(brace
(brace
l_int|NULL
comma
l_int|NULL
)brace
comma
l_string|&quot;unclean&quot;
comma
op_amp
id|match
comma
op_amp
id|checkentry
comma
l_int|NULL
comma
id|THIS_MODULE
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
id|unclean_match
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
id|unclean_match
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
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
