multiline_comment|/*&n; * This is a module which is used for logging packets.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/ip.h&gt;
macro_line|#include &lt;net/icmp.h&gt;
macro_line|#include &lt;net/udp.h&gt;
macro_line|#include &lt;net/tcp.h&gt;
macro_line|#include &lt;net/route.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_tables.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ipt_LOG.h&gt;
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
l_string|&quot;iptables syslog logging module&quot;
)paren
suffix:semicolon
macro_line|#if 0
mdefine_line|#define DEBUGP printk
macro_line|#else
DECL|macro|DEBUGP
mdefine_line|#define DEBUGP(format, args...)
macro_line|#endif
multiline_comment|/* Use lock to serialize, so printks don&squot;t overlap */
DECL|variable|log_lock
r_static
id|spinlock_t
id|log_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
multiline_comment|/* One level of recursion won&squot;t kill us */
DECL|function|dump_packet
r_static
r_void
id|dump_packet
c_func
(paren
r_const
r_struct
id|ipt_log_info
op_star
id|info
comma
r_const
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
r_int
id|iphoff
)paren
(brace
r_struct
id|iphdr
id|iph
suffix:semicolon
r_if
c_cond
(paren
id|skb_copy_bits
c_func
(paren
id|skb
comma
id|iphoff
comma
op_amp
id|iph
comma
r_sizeof
(paren
id|iph
)paren
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;TRUNCATED&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Important fields:&n;&t; * TOS, len, DF/MF, fragment offset, TTL, src, dst, options. */
multiline_comment|/* Max length: 40 &quot;SRC=255.255.255.255 DST=255.255.255.255 &quot; */
id|printk
c_func
(paren
l_string|&quot;SRC=%u.%u.%u.%u DST=%u.%u.%u.%u &quot;
comma
id|NIPQUAD
c_func
(paren
id|iph.saddr
)paren
comma
id|NIPQUAD
c_func
(paren
id|iph.daddr
)paren
)paren
suffix:semicolon
multiline_comment|/* Max length: 46 &quot;LEN=65535 TOS=0xFF PREC=0xFF TTL=255 ID=65535 &quot; */
id|printk
c_func
(paren
l_string|&quot;LEN=%u TOS=0x%02X PREC=0x%02X TTL=%u ID=%u &quot;
comma
id|ntohs
c_func
(paren
id|iph.tot_len
)paren
comma
id|iph.tos
op_amp
id|IPTOS_TOS_MASK
comma
id|iph.tos
op_amp
id|IPTOS_PREC_MASK
comma
id|iph.ttl
comma
id|ntohs
c_func
(paren
id|iph.id
)paren
)paren
suffix:semicolon
multiline_comment|/* Max length: 6 &quot;CE DF MF &quot; */
r_if
c_cond
(paren
id|ntohs
c_func
(paren
id|iph.frag_off
)paren
op_amp
id|IP_CE
)paren
id|printk
c_func
(paren
l_string|&quot;CE &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ntohs
c_func
(paren
id|iph.frag_off
)paren
op_amp
id|IP_DF
)paren
id|printk
c_func
(paren
l_string|&quot;DF &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ntohs
c_func
(paren
id|iph.frag_off
)paren
op_amp
id|IP_MF
)paren
id|printk
c_func
(paren
l_string|&quot;MF &quot;
)paren
suffix:semicolon
multiline_comment|/* Max length: 11 &quot;FRAG:65535 &quot; */
r_if
c_cond
(paren
id|ntohs
c_func
(paren
id|iph.frag_off
)paren
op_amp
id|IP_OFFSET
)paren
id|printk
c_func
(paren
l_string|&quot;FRAG:%u &quot;
comma
id|ntohs
c_func
(paren
id|iph.frag_off
)paren
op_amp
id|IP_OFFSET
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|info-&gt;logflags
op_amp
id|IPT_LOG_IPOPT
)paren
op_logical_and
id|iph.ihl
op_star
l_int|4
op_ne
r_sizeof
(paren
r_struct
id|iphdr
)paren
)paren
(brace
r_int
r_char
id|opt
(braket
l_int|4
op_star
l_int|15
op_minus
r_sizeof
(paren
r_struct
id|iphdr
)paren
)braket
suffix:semicolon
r_int
r_int
id|i
comma
id|optsize
suffix:semicolon
id|optsize
op_assign
id|iph.ihl
op_star
l_int|4
op_minus
r_sizeof
(paren
r_struct
id|iphdr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb_copy_bits
c_func
(paren
id|skb
comma
id|iphoff
op_plus
r_sizeof
(paren
id|iph
)paren
comma
id|opt
comma
id|optsize
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;TRUNCATED&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Max length: 127 &quot;OPT (&quot; 15*4*2chars &quot;) &quot; */
id|printk
c_func
(paren
l_string|&quot;OPT (&quot;
)paren
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
id|optsize
suffix:semicolon
id|i
op_increment
)paren
id|printk
c_func
(paren
l_string|&quot;%02X&quot;
comma
id|opt
(braket
id|i
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;) &quot;
)paren
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|iph.protocol
)paren
(brace
r_case
id|IPPROTO_TCP
suffix:colon
(brace
r_struct
id|tcphdr
id|tcph
suffix:semicolon
multiline_comment|/* Max length: 10 &quot;PROTO=TCP &quot; */
id|printk
c_func
(paren
l_string|&quot;PROTO=TCP &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ntohs
c_func
(paren
id|iph.frag_off
)paren
op_amp
id|IP_OFFSET
)paren
r_break
suffix:semicolon
multiline_comment|/* Max length: 25 &quot;INCOMPLETE [65535 bytes] &quot; */
r_if
c_cond
(paren
id|skb_copy_bits
c_func
(paren
id|skb
comma
id|iphoff
op_plus
id|iph.ihl
op_star
l_int|4
comma
op_amp
id|tcph
comma
r_sizeof
(paren
id|tcph
)paren
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;INCOMPLETE [%u bytes] &quot;
comma
id|skb-&gt;len
op_minus
id|iphoff
op_minus
id|iph.ihl
op_star
l_int|4
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* Max length: 20 &quot;SPT=65535 DPT=65535 &quot; */
id|printk
c_func
(paren
l_string|&quot;SPT=%u DPT=%u &quot;
comma
id|ntohs
c_func
(paren
id|tcph.source
)paren
comma
id|ntohs
c_func
(paren
id|tcph.dest
)paren
)paren
suffix:semicolon
multiline_comment|/* Max length: 30 &quot;SEQ=4294967295 ACK=4294967295 &quot; */
r_if
c_cond
(paren
id|info-&gt;logflags
op_amp
id|IPT_LOG_TCPSEQ
)paren
id|printk
c_func
(paren
l_string|&quot;SEQ=%u ACK=%u &quot;
comma
id|ntohl
c_func
(paren
id|tcph.seq
)paren
comma
id|ntohl
c_func
(paren
id|tcph.ack_seq
)paren
)paren
suffix:semicolon
multiline_comment|/* Max length: 13 &quot;WINDOW=65535 &quot; */
id|printk
c_func
(paren
l_string|&quot;WINDOW=%u &quot;
comma
id|ntohs
c_func
(paren
id|tcph.window
)paren
)paren
suffix:semicolon
multiline_comment|/* Max length: 9 &quot;RES=0x3F &quot; */
id|printk
c_func
(paren
l_string|&quot;RES=0x%02x &quot;
comma
(paren
id|u8
)paren
(paren
id|ntohl
c_func
(paren
id|tcp_flag_word
c_func
(paren
op_amp
id|tcph
)paren
op_amp
id|TCP_RESERVED_BITS
)paren
op_rshift
l_int|22
)paren
)paren
suffix:semicolon
multiline_comment|/* Max length: 32 &quot;CWR ECE URG ACK PSH RST SYN FIN &quot; */
r_if
c_cond
(paren
id|tcph.cwr
)paren
id|printk
c_func
(paren
l_string|&quot;CWR &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tcph.ece
)paren
id|printk
c_func
(paren
l_string|&quot;ECE &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tcph.urg
)paren
id|printk
c_func
(paren
l_string|&quot;URG &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tcph.ack
)paren
id|printk
c_func
(paren
l_string|&quot;ACK &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tcph.psh
)paren
id|printk
c_func
(paren
l_string|&quot;PSH &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tcph.rst
)paren
id|printk
c_func
(paren
l_string|&quot;RST &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tcph.syn
)paren
id|printk
c_func
(paren
l_string|&quot;SYN &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tcph.fin
)paren
id|printk
c_func
(paren
l_string|&quot;FIN &quot;
)paren
suffix:semicolon
multiline_comment|/* Max length: 11 &quot;URGP=65535 &quot; */
id|printk
c_func
(paren
l_string|&quot;URGP=%u &quot;
comma
id|ntohs
c_func
(paren
id|tcph.urg_ptr
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|info-&gt;logflags
op_amp
id|IPT_LOG_TCPOPT
)paren
op_logical_and
id|tcph.doff
op_star
l_int|4
op_ne
r_sizeof
(paren
r_struct
id|tcphdr
)paren
)paren
(brace
r_int
r_char
id|opt
(braket
l_int|4
op_star
l_int|15
op_minus
r_sizeof
(paren
r_struct
id|tcphdr
)paren
)braket
suffix:semicolon
r_int
r_int
id|i
comma
id|optsize
suffix:semicolon
id|optsize
op_assign
id|tcph.doff
op_star
l_int|4
op_minus
r_sizeof
(paren
r_struct
id|tcphdr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb_copy_bits
c_func
(paren
id|skb
comma
id|iphoff
op_plus
id|iph.ihl
op_star
l_int|4
op_plus
r_sizeof
(paren
id|tcph
)paren
comma
id|opt
comma
id|optsize
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;TRUNCATED&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Max length: 127 &quot;OPT (&quot; 15*4*2chars &quot;) &quot; */
id|printk
c_func
(paren
l_string|&quot;OPT (&quot;
)paren
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
id|optsize
suffix:semicolon
id|i
op_increment
)paren
id|printk
c_func
(paren
l_string|&quot;%02X&quot;
comma
id|opt
(braket
id|i
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;) &quot;
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
r_case
id|IPPROTO_UDP
suffix:colon
(brace
r_struct
id|udphdr
id|udph
suffix:semicolon
multiline_comment|/* Max length: 10 &quot;PROTO=UDP &quot; */
id|printk
c_func
(paren
l_string|&quot;PROTO=UDP &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ntohs
c_func
(paren
id|iph.frag_off
)paren
op_amp
id|IP_OFFSET
)paren
r_break
suffix:semicolon
multiline_comment|/* Max length: 25 &quot;INCOMPLETE [65535 bytes] &quot; */
r_if
c_cond
(paren
id|skb_copy_bits
c_func
(paren
id|skb
comma
id|iphoff
op_plus
id|iph.ihl
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
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;INCOMPLETE [%u bytes] &quot;
comma
id|skb-&gt;len
op_minus
id|iphoff
op_minus
id|iph.ihl
op_star
l_int|4
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* Max length: 20 &quot;SPT=65535 DPT=65535 &quot; */
id|printk
c_func
(paren
l_string|&quot;SPT=%u DPT=%u LEN=%u &quot;
comma
id|ntohs
c_func
(paren
id|udph.source
)paren
comma
id|ntohs
c_func
(paren
id|udph.dest
)paren
comma
id|ntohs
c_func
(paren
id|udph.len
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|IPPROTO_ICMP
suffix:colon
(brace
r_struct
id|icmphdr
id|icmph
suffix:semicolon
r_static
r_int
id|required_len
(braket
id|NR_ICMP_TYPES
op_plus
l_int|1
)braket
op_assign
(brace
(braket
id|ICMP_ECHOREPLY
)braket
op_assign
l_int|4
comma
(braket
id|ICMP_DEST_UNREACH
)braket
op_assign
l_int|8
op_plus
r_sizeof
(paren
r_struct
id|iphdr
)paren
op_plus
l_int|8
comma
(braket
id|ICMP_SOURCE_QUENCH
)braket
op_assign
l_int|8
op_plus
r_sizeof
(paren
r_struct
id|iphdr
)paren
op_plus
l_int|8
comma
(braket
id|ICMP_REDIRECT
)braket
op_assign
l_int|8
op_plus
r_sizeof
(paren
r_struct
id|iphdr
)paren
op_plus
l_int|8
comma
(braket
id|ICMP_ECHO
)braket
op_assign
l_int|4
comma
(braket
id|ICMP_TIME_EXCEEDED
)braket
op_assign
l_int|8
op_plus
r_sizeof
(paren
r_struct
id|iphdr
)paren
op_plus
l_int|8
comma
(braket
id|ICMP_PARAMETERPROB
)braket
op_assign
l_int|8
op_plus
r_sizeof
(paren
r_struct
id|iphdr
)paren
op_plus
l_int|8
comma
(braket
id|ICMP_TIMESTAMP
)braket
op_assign
l_int|20
comma
(braket
id|ICMP_TIMESTAMPREPLY
)braket
op_assign
l_int|20
comma
(braket
id|ICMP_ADDRESS
)braket
op_assign
l_int|12
comma
(braket
id|ICMP_ADDRESSREPLY
)braket
op_assign
l_int|12
)brace
suffix:semicolon
multiline_comment|/* Max length: 11 &quot;PROTO=ICMP &quot; */
id|printk
c_func
(paren
l_string|&quot;PROTO=ICMP &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ntohs
c_func
(paren
id|iph.frag_off
)paren
op_amp
id|IP_OFFSET
)paren
r_break
suffix:semicolon
multiline_comment|/* Max length: 25 &quot;INCOMPLETE [65535 bytes] &quot; */
r_if
c_cond
(paren
id|skb_copy_bits
c_func
(paren
id|skb
comma
id|iphoff
op_plus
id|iph.ihl
op_star
l_int|4
comma
op_amp
id|icmph
comma
r_sizeof
(paren
id|icmph
)paren
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;INCOMPLETE [%u bytes] &quot;
comma
id|skb-&gt;len
op_minus
id|iphoff
op_minus
id|iph.ihl
op_star
l_int|4
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* Max length: 18 &quot;TYPE=255 CODE=255 &quot; */
id|printk
c_func
(paren
l_string|&quot;TYPE=%u CODE=%u &quot;
comma
id|icmph.type
comma
id|icmph.code
)paren
suffix:semicolon
multiline_comment|/* Max length: 25 &quot;INCOMPLETE [65535 bytes] &quot; */
r_if
c_cond
(paren
id|icmph.type
op_le
id|NR_ICMP_TYPES
op_logical_and
id|required_len
(braket
id|icmph.type
)braket
op_logical_and
id|skb-&gt;len
op_minus
id|iphoff
op_minus
id|iph.ihl
op_star
l_int|4
OL
id|required_len
(braket
id|icmph.type
)braket
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;INCOMPLETE [%u bytes] &quot;
comma
id|skb-&gt;len
op_minus
id|iphoff
op_minus
id|iph.ihl
op_star
l_int|4
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|icmph.type
)paren
(brace
r_case
id|ICMP_ECHOREPLY
suffix:colon
r_case
id|ICMP_ECHO
suffix:colon
multiline_comment|/* Max length: 19 &quot;ID=65535 SEQ=65535 &quot; */
id|printk
c_func
(paren
l_string|&quot;ID=%u SEQ=%u &quot;
comma
id|ntohs
c_func
(paren
id|icmph.un.echo.id
)paren
comma
id|ntohs
c_func
(paren
id|icmph.un.echo.sequence
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ICMP_PARAMETERPROB
suffix:colon
multiline_comment|/* Max length: 14 &quot;PARAMETER=255 &quot; */
id|printk
c_func
(paren
l_string|&quot;PARAMETER=%u &quot;
comma
id|ntohl
c_func
(paren
id|icmph.un.gateway
)paren
op_rshift
l_int|24
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ICMP_REDIRECT
suffix:colon
multiline_comment|/* Max length: 24 &quot;GATEWAY=255.255.255.255 &quot; */
id|printk
c_func
(paren
l_string|&quot;GATEWAY=%u.%u.%u.%u &quot;
comma
id|NIPQUAD
c_func
(paren
id|icmph.un.gateway
)paren
)paren
suffix:semicolon
multiline_comment|/* Fall through */
r_case
id|ICMP_DEST_UNREACH
suffix:colon
r_case
id|ICMP_SOURCE_QUENCH
suffix:colon
r_case
id|ICMP_TIME_EXCEEDED
suffix:colon
multiline_comment|/* Max length: 3+maxlen */
r_if
c_cond
(paren
op_logical_neg
id|iphoff
)paren
(brace
multiline_comment|/* Only recurse once. */
id|printk
c_func
(paren
l_string|&quot;[&quot;
)paren
suffix:semicolon
id|dump_packet
c_func
(paren
id|info
comma
id|skb
comma
id|iphoff
op_plus
id|iph.ihl
op_star
l_int|4
op_plus
r_sizeof
(paren
id|icmph
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;] &quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* Max length: 10 &quot;MTU=65535 &quot; */
r_if
c_cond
(paren
id|icmph.type
op_eq
id|ICMP_DEST_UNREACH
op_logical_and
id|icmph.code
op_eq
id|ICMP_FRAG_NEEDED
)paren
id|printk
c_func
(paren
l_string|&quot;MTU=%u &quot;
comma
id|ntohs
c_func
(paren
id|icmph.un.frag.mtu
)paren
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
multiline_comment|/* Max Length */
r_case
id|IPPROTO_AH
suffix:colon
(brace
r_struct
id|ip_auth_hdr
id|ah
suffix:semicolon
r_if
c_cond
(paren
id|ntohs
c_func
(paren
id|iph.frag_off
)paren
op_amp
id|IP_OFFSET
)paren
r_break
suffix:semicolon
multiline_comment|/* Max length: 9 &quot;PROTO=AH &quot; */
id|printk
c_func
(paren
l_string|&quot;PROTO=AH &quot;
)paren
suffix:semicolon
multiline_comment|/* Max length: 25 &quot;INCOMPLETE [65535 bytes] &quot; */
r_if
c_cond
(paren
id|skb_copy_bits
c_func
(paren
id|skb
comma
id|iphoff
op_plus
id|iph.ihl
op_star
l_int|4
comma
op_amp
id|ah
comma
r_sizeof
(paren
id|ah
)paren
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;INCOMPLETE [%u bytes] &quot;
comma
id|skb-&gt;len
op_minus
id|iphoff
op_minus
id|iph.ihl
op_star
l_int|4
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* Length: 15 &quot;SPI=0xF1234567 &quot; */
id|printk
c_func
(paren
l_string|&quot;SPI=0x%x &quot;
comma
id|ntohl
c_func
(paren
id|ah.spi
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|IPPROTO_ESP
suffix:colon
(brace
r_struct
id|ip_esp_hdr
id|esph
suffix:semicolon
multiline_comment|/* Max length: 10 &quot;PROTO=ESP &quot; */
id|printk
c_func
(paren
l_string|&quot;PROTO=ESP &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ntohs
c_func
(paren
id|iph.frag_off
)paren
op_amp
id|IP_OFFSET
)paren
r_break
suffix:semicolon
multiline_comment|/* Max length: 25 &quot;INCOMPLETE [65535 bytes] &quot; */
r_if
c_cond
(paren
id|skb_copy_bits
c_func
(paren
id|skb
comma
id|iphoff
op_plus
id|iph.ihl
op_star
l_int|4
comma
op_amp
id|esph
comma
r_sizeof
(paren
id|esph
)paren
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;INCOMPLETE [%u bytes] &quot;
comma
id|skb-&gt;len
op_minus
id|iphoff
op_minus
id|iph.ihl
op_star
l_int|4
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* Length: 15 &quot;SPI=0xF1234567 &quot; */
id|printk
c_func
(paren
l_string|&quot;SPI=0x%x &quot;
comma
id|ntohl
c_func
(paren
id|esph.spi
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* Max length: 10 &quot;PROTO 255 &quot; */
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;PROTO=%u &quot;
comma
id|iph.protocol
)paren
suffix:semicolon
)brace
multiline_comment|/* Proto    Max log string length */
multiline_comment|/* IP:      40+46+6+11+127 = 230 */
multiline_comment|/* TCP:     10+max(25,20+30+13+9+32+11+127) = 252 */
multiline_comment|/* UDP:     10+max(25,20) = 35 */
multiline_comment|/* ICMP:    11+max(25, 18+25+max(19,14,24+3+n+10,3+n+10)) = 91+n */
multiline_comment|/* ESP:     10+max(25)+15 = 50 */
multiline_comment|/* AH:      9+max(25)+15 = 49 */
multiline_comment|/* unknown: 10 */
multiline_comment|/* (ICMP allows recursion one level deep) */
multiline_comment|/* maxlen =  IP + ICMP +  IP + max(TCP,UDP,ICMP,unknown) */
multiline_comment|/* maxlen = 230+   91  + 230 + 252 = 803 */
)brace
r_static
r_int
r_int
DECL|function|ipt_log_target
id|ipt_log_target
c_func
(paren
r_struct
id|sk_buff
op_star
op_star
id|pskb
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
r_int
r_int
id|hooknum
comma
r_const
r_void
op_star
id|targinfo
comma
r_void
op_star
id|userinfo
)paren
(brace
r_const
r_struct
id|ipt_log_info
op_star
id|loginfo
op_assign
id|targinfo
suffix:semicolon
r_char
id|level_string
(braket
l_int|4
)braket
op_assign
l_string|&quot;&lt; &gt;&quot;
suffix:semicolon
id|level_string
(braket
l_int|1
)braket
op_assign
l_char|&squot;0&squot;
op_plus
(paren
id|loginfo-&gt;level
op_mod
l_int|8
)paren
suffix:semicolon
id|spin_lock_bh
c_func
(paren
op_amp
id|log_lock
)paren
suffix:semicolon
id|printk
c_func
(paren
id|level_string
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%sIN=%s OUT=%s &quot;
comma
id|loginfo-&gt;prefix
comma
id|in
ques
c_cond
id|in-&gt;name
suffix:colon
l_string|&quot;&quot;
comma
id|out
ques
c_cond
id|out-&gt;name
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_BRIDGE_NETFILTER
r_if
c_cond
(paren
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nf_bridge
)paren
(brace
r_struct
id|net_device
op_star
id|physindev
op_assign
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nf_bridge-&gt;physindev
suffix:semicolon
r_struct
id|net_device
op_star
id|physoutdev
op_assign
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nf_bridge-&gt;physoutdev
suffix:semicolon
r_if
c_cond
(paren
id|physindev
op_logical_and
id|in
op_ne
id|physindev
)paren
id|printk
c_func
(paren
l_string|&quot;PHYSIN=%s &quot;
comma
id|physindev-&gt;name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|physoutdev
op_logical_and
id|out
op_ne
id|physoutdev
)paren
id|printk
c_func
(paren
l_string|&quot;PHYSOUT=%s &quot;
comma
id|physoutdev-&gt;name
)paren
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
id|in
op_logical_and
op_logical_neg
id|out
)paren
(brace
multiline_comment|/* MAC logging for input chain only. */
id|printk
c_func
(paren
l_string|&quot;MAC=&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|dev
op_logical_and
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|dev-&gt;hard_header_len
op_logical_and
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|mac.raw
op_ne
(paren
r_void
op_star
)paren
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nh.iph
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
r_char
op_star
id|p
op_assign
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|mac.raw
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
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|dev-&gt;hard_header_len
suffix:semicolon
id|i
op_increment
comma
id|p
op_increment
)paren
id|printk
c_func
(paren
l_string|&quot;%02x%c&quot;
comma
op_star
id|p
comma
id|i
op_eq
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|dev-&gt;hard_header_len
op_minus
l_int|1
ques
c_cond
l_char|&squot; &squot;
suffix:colon
l_char|&squot;:&squot;
)paren
suffix:semicolon
)brace
r_else
id|printk
c_func
(paren
l_string|&quot; &quot;
)paren
suffix:semicolon
)brace
id|dump_packet
c_func
(paren
id|loginfo
comma
op_star
id|pskb
comma
l_int|0
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|spin_unlock_bh
c_func
(paren
op_amp
id|log_lock
)paren
suffix:semicolon
r_return
id|IPT_CONTINUE
suffix:semicolon
)brace
DECL|function|ipt_log_checkentry
r_static
r_int
id|ipt_log_checkentry
c_func
(paren
r_const
r_char
op_star
id|tablename
comma
r_const
r_struct
id|ipt_entry
op_star
id|e
comma
r_void
op_star
id|targinfo
comma
r_int
r_int
id|targinfosize
comma
r_int
r_int
id|hook_mask
)paren
(brace
r_const
r_struct
id|ipt_log_info
op_star
id|loginfo
op_assign
id|targinfo
suffix:semicolon
r_if
c_cond
(paren
id|targinfosize
op_ne
id|IPT_ALIGN
c_func
(paren
r_sizeof
(paren
r_struct
id|ipt_log_info
)paren
)paren
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;LOG: targinfosize %u != %u&bslash;n&quot;
comma
id|targinfosize
comma
id|IPT_ALIGN
c_func
(paren
r_sizeof
(paren
r_struct
id|ipt_log_info
)paren
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
id|loginfo-&gt;level
op_ge
l_int|8
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;LOG: level %u &gt;= 8&bslash;n&quot;
comma
id|loginfo-&gt;level
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|loginfo-&gt;prefix
(braket
r_sizeof
(paren
id|loginfo-&gt;prefix
)paren
op_minus
l_int|1
)braket
op_ne
l_char|&squot;&bslash;0&squot;
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;LOG: prefix term %i&bslash;n&quot;
comma
id|loginfo-&gt;prefix
(braket
r_sizeof
(paren
id|loginfo-&gt;prefix
)paren
op_minus
l_int|1
)braket
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
DECL|variable|ipt_log_reg
r_static
r_struct
id|ipt_target
id|ipt_log_reg
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;LOG&quot;
comma
dot
id|target
op_assign
id|ipt_log_target
comma
dot
id|checkentry
op_assign
id|ipt_log_checkentry
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
r_if
c_cond
(paren
id|ipt_register_target
c_func
(paren
op_amp
id|ipt_log_reg
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
l_int|0
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
id|ipt_unregister_target
c_func
(paren
op_amp
id|ipt_log_reg
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
