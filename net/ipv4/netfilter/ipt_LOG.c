multiline_comment|/*&n; * This is a module which is used for logging packets.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/ip.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;net/icmp.h&gt;
macro_line|#include &lt;net/udp.h&gt;
macro_line|#include &lt;net/tcp.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_tables.h&gt;
r_struct
id|in_device
suffix:semicolon
macro_line|#include &lt;net/route.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ipt_LOG.h&gt;
macro_line|#if 0
mdefine_line|#define DEBUGP printk
macro_line|#else
DECL|macro|DEBUGP
mdefine_line|#define DEBUGP(format, args...)
macro_line|#endif
DECL|struct|esphdr
r_struct
id|esphdr
(brace
DECL|member|spi
id|__u32
id|spi
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* FIXME evil kludge */
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
r_struct
id|iphdr
op_star
id|iph
comma
r_int
r_int
id|len
comma
r_int
id|recurse
)paren
(brace
r_void
op_star
id|protoh
op_assign
(paren
id|u_int32_t
op_star
)paren
id|iph
op_plus
id|iph-&gt;ihl
suffix:semicolon
r_int
r_int
id|datalen
op_assign
id|len
op_minus
id|iph-&gt;ihl
op_star
l_int|4
suffix:semicolon
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
id|iph-&gt;saddr
)paren
comma
id|NIPQUAD
c_func
(paren
id|iph-&gt;daddr
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
id|iph-&gt;tot_len
)paren
comma
id|iph-&gt;tos
op_amp
id|IPTOS_TOS_MASK
comma
id|iph-&gt;tos
op_amp
id|IPTOS_PREC_MASK
comma
id|iph-&gt;ttl
comma
id|ntohs
c_func
(paren
id|iph-&gt;id
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
id|iph-&gt;frag_off
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
id|iph-&gt;frag_off
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
id|iph-&gt;frag_off
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
id|iph-&gt;frag_off
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
id|iph-&gt;frag_off
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
id|iph-&gt;ihl
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
r_int
id|i
suffix:semicolon
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
id|i
op_increment
)paren
id|printk
c_func
(paren
l_string|&quot;%02X&quot;
comma
(paren
(paren
id|u_int8_t
op_star
)paren
id|iph
)paren
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
id|iph-&gt;protocol
)paren
(brace
r_case
id|IPPROTO_TCP
suffix:colon
(brace
r_struct
id|tcphdr
op_star
id|tcph
op_assign
id|protoh
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
id|iph-&gt;frag_off
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
id|datalen
OL
r_sizeof
(paren
op_star
id|tcph
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;INCOMPLETE [%u bytes] &quot;
comma
id|datalen
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
id|tcph-&gt;source
)paren
comma
id|ntohs
c_func
(paren
id|tcph-&gt;dest
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
id|tcph-&gt;seq
)paren
comma
id|ntohl
c_func
(paren
id|tcph-&gt;ack_seq
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
id|tcph-&gt;window
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
id|u_int8_t
)paren
(paren
id|ntohl
c_func
(paren
id|tcp_flag_word
c_func
(paren
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
multiline_comment|/* Max length: 36 &quot;URG ACK PSH RST SYN FIN &quot; */
r_if
c_cond
(paren
id|tcph-&gt;urg
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
id|tcph-&gt;ack
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
id|tcph-&gt;psh
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
id|tcph-&gt;rst
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
id|tcph-&gt;syn
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
id|tcph-&gt;fin
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
id|tcph-&gt;urg_ptr
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
id|tcph-&gt;doff
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
r_int
id|i
suffix:semicolon
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
id|i
op_increment
)paren
id|printk
c_func
(paren
l_string|&quot;%02X&quot;
comma
(paren
(paren
id|u_int8_t
op_star
)paren
id|tcph
)paren
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
op_star
id|udph
op_assign
id|protoh
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
id|iph-&gt;frag_off
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
id|datalen
OL
r_sizeof
(paren
op_star
id|udph
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;INCOMPLETE [%u bytes] &quot;
comma
id|datalen
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
id|udph-&gt;source
)paren
comma
id|ntohs
c_func
(paren
id|udph-&gt;dest
)paren
comma
id|ntohs
c_func
(paren
id|udph-&gt;len
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
op_star
id|icmph
op_assign
id|protoh
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
id|iph-&gt;frag_off
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
id|datalen
OL
l_int|4
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;INCOMPLETE [%u bytes] &quot;
comma
id|datalen
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
id|icmph-&gt;type
comma
id|icmph-&gt;code
)paren
suffix:semicolon
multiline_comment|/* Max length: 25 &quot;INCOMPLETE [65535 bytes] &quot; */
r_if
c_cond
(paren
id|icmph-&gt;type
op_le
id|NR_ICMP_TYPES
op_logical_and
id|required_len
(braket
id|icmph-&gt;type
)braket
op_logical_and
id|datalen
OL
id|required_len
(braket
id|icmph-&gt;type
)braket
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;INCOMPLETE [%u bytes] &quot;
comma
id|datalen
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|icmph-&gt;type
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
id|icmph-&gt;un.echo.id
)paren
comma
id|ntohs
c_func
(paren
id|icmph-&gt;un.echo.sequence
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
id|icmph-&gt;un.gateway
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
id|icmph-&gt;un.gateway
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
id|recurse
)paren
(brace
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
(paren
r_struct
id|iphdr
op_star
)paren
(paren
id|icmph
op_plus
l_int|1
)paren
comma
id|datalen
op_minus
r_sizeof
(paren
r_struct
id|iphdr
)paren
comma
l_int|0
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
id|icmph-&gt;type
op_eq
id|ICMP_DEST_UNREACH
op_logical_and
id|icmph-&gt;code
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
id|icmph-&gt;un.frag.mtu
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
r_case
id|IPPROTO_ESP
suffix:colon
(brace
r_struct
id|esphdr
op_star
id|esph
op_assign
id|protoh
suffix:semicolon
r_int
id|esp
op_assign
(paren
id|iph-&gt;protocol
op_eq
id|IPPROTO_ESP
)paren
suffix:semicolon
multiline_comment|/* Max length: 10 &quot;PROTO=ESP &quot; */
id|printk
c_func
(paren
l_string|&quot;PROTO=%s &quot;
comma
id|esp
ques
c_cond
l_string|&quot;ESP&quot;
suffix:colon
l_string|&quot;AH&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ntohs
c_func
(paren
id|iph-&gt;frag_off
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
id|datalen
OL
r_sizeof
(paren
op_star
id|esph
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;INCOMPLETE [%u bytes] &quot;
comma
id|datalen
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
id|esph-&gt;spi
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
id|iph-&gt;protocol
)paren
suffix:semicolon
)brace
multiline_comment|/* Proto    Max log string length */
multiline_comment|/* IP:      40+46+6+11+127 = 230 */
multiline_comment|/* TCP:     10+max(25,20+30+13+9+36+11+127) = 256 */
multiline_comment|/* UDP:     10+max(25,20) = 35 */
multiline_comment|/* ICMP:    11+max(25, 18+25+max(19,14,24+3+n+10,3+n+10)) = 91+n */
multiline_comment|/* ESP:     10+max(25)+15 = 50 */
multiline_comment|/* AH:      9+max(25)+15 = 49 */
multiline_comment|/* unknown: 10 */
multiline_comment|/* (ICMP allows recursion one level deep) */
multiline_comment|/* maxlen =  IP + ICMP +  IP + max(TCP,UDP,ICMP,unknown) */
multiline_comment|/* maxlen = 230+   91  + 230 + 256 = 807 */
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
r_int
r_int
id|hooknum
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
id|targinfo
comma
r_void
op_star
id|userinfo
)paren
(brace
r_struct
id|iphdr
op_star
id|iph
op_assign
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nh.iph
suffix:semicolon
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
id|iph
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
id|iph
comma
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|len
comma
l_int|1
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
(brace
l_int|NULL
comma
l_int|NULL
)brace
comma
l_string|&quot;LOG&quot;
comma
id|ipt_log_target
comma
id|ipt_log_checkentry
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
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
