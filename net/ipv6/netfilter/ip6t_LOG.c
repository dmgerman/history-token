multiline_comment|/*&n; * This is a module which is used for logging packets.&n; */
multiline_comment|/* (C) 2001 Jan Rekorajski &lt;baggins@pld.org.pl&gt;&n; * (C) 2002-2004 Netfilter Core Team &lt;coreteam@netfilter.org&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/ip.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/icmpv6.h&gt;
macro_line|#include &lt;net/udp.h&gt;
macro_line|#include &lt;net/tcp.h&gt;
macro_line|#include &lt;net/ipv6.h&gt;
macro_line|#include &lt;linux/netfilter_ipv6/ip6_tables.h&gt;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Jan Rekorajski &lt;baggins@pld.org.pl&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;IP6 tables LOG target module&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
r_struct
id|in_device
suffix:semicolon
macro_line|#include &lt;net/route.h&gt;
macro_line|#include &lt;linux/netfilter_ipv6/ip6t_LOG.h&gt;
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
multiline_comment|/* takes in current header and pointer to the header */
multiline_comment|/* if another header exists, sets hdrptr to the next header&n;   and returns the new header value, else returns 0 */
DECL|function|ip6_nexthdr
r_static
id|u_int8_t
id|ip6_nexthdr
c_func
(paren
id|u_int8_t
id|currenthdr
comma
id|u_int8_t
op_star
op_star
id|hdrptr
)paren
(brace
id|u_int8_t
id|hdrlen
comma
id|nexthdr
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|currenthdr
)paren
(brace
r_case
id|IPPROTO_AH
suffix:colon
multiline_comment|/* whoever decided to do the length of AUTH for ipv6&n;&t;&t;in 32bit units unlike other headers should be beaten...&n;&t;&t;repeatedly...with a large stick...no, an even LARGER&n;&t;&t;stick...no, you&squot;re still not thinking big enough */
id|nexthdr
op_assign
op_star
op_star
id|hdrptr
suffix:semicolon
id|hdrlen
op_assign
op_star
id|hdrptr
(braket
l_int|1
)braket
op_star
l_int|4
op_plus
l_int|8
suffix:semicolon
op_star
id|hdrptr
op_assign
op_star
id|hdrptr
op_plus
id|hdrlen
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/*stupid rfc2402 */
r_case
id|IPPROTO_DSTOPTS
suffix:colon
r_case
id|IPPROTO_ROUTING
suffix:colon
r_case
id|IPPROTO_HOPOPTS
suffix:colon
id|nexthdr
op_assign
op_star
op_star
id|hdrptr
suffix:semicolon
id|hdrlen
op_assign
op_star
id|hdrptr
(braket
l_int|1
)braket
op_star
l_int|8
op_plus
l_int|8
suffix:semicolon
op_star
id|hdrptr
op_assign
op_star
id|hdrptr
op_plus
id|hdrlen
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPPROTO_FRAGMENT
suffix:colon
id|nexthdr
op_assign
op_star
op_star
id|hdrptr
suffix:semicolon
op_star
id|hdrptr
op_assign
op_star
id|hdrptr
op_plus
l_int|8
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|nexthdr
suffix:semicolon
)brace
multiline_comment|/* One level of recursion won&squot;t kill us */
DECL|function|dump_packet
r_static
r_void
id|dump_packet
c_func
(paren
r_const
r_struct
id|ip6t_log_info
op_star
id|info
comma
r_struct
id|ipv6hdr
op_star
id|ipv6h
comma
r_int
id|recurse
)paren
(brace
id|u_int8_t
id|currenthdr
op_assign
id|ipv6h-&gt;nexthdr
suffix:semicolon
id|u_int8_t
op_star
id|hdrptr
suffix:semicolon
r_int
id|fragment
suffix:semicolon
multiline_comment|/* Max length: 88 &quot;SRC=0000.0000.0000.0000.0000.0000.0000.0000 DST=0000.0000.0000.0000.0000.0000.0000.0000&quot; */
id|printk
c_func
(paren
l_string|&quot;SRC=%04x:%04x:%04x:%04x:%04x:%04x:%04x:%04x &quot;
comma
id|NIP6
c_func
(paren
id|ipv6h-&gt;saddr
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;DST=%04x:%04x:%04x:%04x:%04x:%04x:%04x:%04x &quot;
comma
id|NIP6
c_func
(paren
id|ipv6h-&gt;daddr
)paren
)paren
suffix:semicolon
multiline_comment|/* Max length: 44 &quot;LEN=65535 TC=255 HOPLIMIT=255 FLOWLBL=FFFFF &quot; */
id|printk
c_func
(paren
l_string|&quot;LEN=%Zu TC=%u HOPLIMIT=%u FLOWLBL=%u &quot;
comma
id|ntohs
c_func
(paren
id|ipv6h-&gt;payload_len
)paren
op_plus
r_sizeof
(paren
r_struct
id|ipv6hdr
)paren
comma
(paren
id|ntohl
c_func
(paren
op_star
(paren
id|u_int32_t
op_star
)paren
id|ipv6h
)paren
op_amp
l_int|0x0ff00000
)paren
op_rshift
l_int|20
comma
id|ipv6h-&gt;hop_limit
comma
(paren
id|ntohl
c_func
(paren
op_star
(paren
id|u_int32_t
op_star
)paren
id|ipv6h
)paren
op_amp
l_int|0x000fffff
)paren
)paren
suffix:semicolon
id|fragment
op_assign
l_int|0
suffix:semicolon
id|hdrptr
op_assign
(paren
id|u_int8_t
op_star
)paren
(paren
id|ipv6h
op_plus
l_int|1
)paren
suffix:semicolon
r_while
c_loop
(paren
id|currenthdr
)paren
(brace
r_if
c_cond
(paren
(paren
id|currenthdr
op_eq
id|IPPROTO_TCP
)paren
op_logical_or
(paren
id|currenthdr
op_eq
id|IPPROTO_UDP
)paren
op_logical_or
(paren
id|currenthdr
op_eq
id|IPPROTO_ICMPV6
)paren
)paren
r_break
suffix:semicolon
multiline_comment|/* Max length: 48 &quot;OPT (...) &quot; */
id|printk
c_func
(paren
l_string|&quot;OPT ( &quot;
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|currenthdr
)paren
(brace
r_case
id|IPPROTO_FRAGMENT
suffix:colon
(brace
r_struct
id|frag_hdr
op_star
id|fhdr
op_assign
(paren
r_struct
id|frag_hdr
op_star
)paren
id|hdrptr
suffix:semicolon
multiline_comment|/* Max length: 11 &quot;FRAG:65535 &quot; */
id|printk
c_func
(paren
l_string|&quot;FRAG:%u &quot;
comma
id|ntohs
c_func
(paren
id|fhdr-&gt;frag_off
)paren
op_amp
l_int|0xFFF8
)paren
suffix:semicolon
multiline_comment|/* Max length: 11 &quot;INCOMPLETE &quot; */
r_if
c_cond
(paren
id|fhdr-&gt;frag_off
op_amp
id|htons
c_func
(paren
l_int|0x0001
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;INCOMPLETE &quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;ID:%08x &quot;
comma
id|fhdr-&gt;identification
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ntohs
c_func
(paren
id|fhdr-&gt;frag_off
)paren
op_amp
l_int|0xFFF8
)paren
id|fragment
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|IPPROTO_DSTOPTS
suffix:colon
r_case
id|IPPROTO_ROUTING
suffix:colon
r_case
id|IPPROTO_HOPOPTS
suffix:colon
r_break
suffix:semicolon
multiline_comment|/* Max Length */
r_case
id|IPPROTO_AH
suffix:colon
r_case
id|IPPROTO_ESP
suffix:colon
r_if
c_cond
(paren
id|info-&gt;logflags
op_amp
id|IP6T_LOG_IPOPT
)paren
(brace
r_struct
id|esphdr
op_star
id|esph
op_assign
(paren
r_struct
id|esphdr
op_star
)paren
id|hdrptr
suffix:semicolon
r_int
id|esp
op_assign
(paren
id|currenthdr
op_eq
id|IPPROTO_ESP
)paren
suffix:semicolon
multiline_comment|/* Max length: 4 &quot;ESP &quot; */
id|printk
c_func
(paren
l_string|&quot;%s &quot;
comma
id|esp
ques
c_cond
l_string|&quot;ESP&quot;
suffix:colon
l_string|&quot;AH&quot;
)paren
suffix:semicolon
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
r_default
suffix:colon
r_break
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;) &quot;
)paren
suffix:semicolon
id|currenthdr
op_assign
id|ip6_nexthdr
c_func
(paren
id|currenthdr
comma
op_amp
id|hdrptr
)paren
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|currenthdr
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
(paren
r_struct
id|tcphdr
op_star
)paren
id|hdrptr
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
id|fragment
)paren
r_break
suffix:semicolon
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
id|IP6T_LOG_TCPSEQ
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
multiline_comment|/* Max length: 32 &quot;CWR ECE URG ACK PSH RST SYN FIN &quot; */
r_if
c_cond
(paren
id|tcph-&gt;cwr
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
id|tcph-&gt;ece
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
id|IP6T_LOG_TCPOPT
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
(paren
r_struct
id|udphdr
op_star
)paren
id|hdrptr
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
id|fragment
)paren
r_break
suffix:semicolon
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
id|IPPROTO_ICMPV6
suffix:colon
(brace
r_struct
id|icmp6hdr
op_star
id|icmp6h
op_assign
(paren
r_struct
id|icmp6hdr
op_star
)paren
id|hdrptr
suffix:semicolon
multiline_comment|/* Max length: 13 &quot;PROTO=ICMPv6 &quot; */
id|printk
c_func
(paren
l_string|&quot;PROTO=ICMPv6 &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fragment
)paren
r_break
suffix:semicolon
multiline_comment|/* Max length: 18 &quot;TYPE=255 CODE=255 &quot; */
id|printk
c_func
(paren
l_string|&quot;TYPE=%u CODE=%u &quot;
comma
id|icmp6h-&gt;icmp6_type
comma
id|icmp6h-&gt;icmp6_code
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|icmp6h-&gt;icmp6_type
)paren
(brace
r_case
id|ICMPV6_ECHO_REQUEST
suffix:colon
r_case
id|ICMPV6_ECHO_REPLY
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
id|icmp6h-&gt;icmp6_identifier
)paren
comma
id|ntohs
c_func
(paren
id|icmp6h-&gt;icmp6_sequence
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ICMPV6_MGM_QUERY
suffix:colon
r_case
id|ICMPV6_MGM_REPORT
suffix:colon
r_case
id|ICMPV6_MGM_REDUCTION
suffix:colon
r_break
suffix:semicolon
r_case
id|ICMPV6_PARAMPROB
suffix:colon
multiline_comment|/* Max length: 17 &quot;POINTER=ffffffff &quot; */
id|printk
c_func
(paren
l_string|&quot;POINTER=%08x &quot;
comma
id|ntohl
c_func
(paren
id|icmp6h-&gt;icmp6_pointer
)paren
)paren
suffix:semicolon
multiline_comment|/* Fall through */
r_case
id|ICMPV6_DEST_UNREACH
suffix:colon
r_case
id|ICMPV6_PKT_TOOBIG
suffix:colon
r_case
id|ICMPV6_TIME_EXCEED
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
id|ipv6hdr
op_star
)paren
(paren
id|icmp6h
op_plus
l_int|1
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
id|icmp6h-&gt;icmp6_type
op_eq
id|ICMPV6_PKT_TOOBIG
)paren
id|printk
c_func
(paren
l_string|&quot;MTU=%u &quot;
comma
id|ntohl
c_func
(paren
id|icmp6h-&gt;icmp6_mtu
)paren
)paren
suffix:semicolon
)brace
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
id|currenthdr
)paren
suffix:semicolon
)brace
)brace
r_static
r_int
r_int
DECL|function|ip6t_log_target
id|ip6t_log_target
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
id|ipv6hdr
op_star
id|ipv6h
op_assign
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nh.ipv6h
suffix:semicolon
r_const
r_struct
id|ip6t_log_info
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
id|ipv6h
)paren
(brace
r_if
c_cond
(paren
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|dev-&gt;type
op_ne
id|ARPHRD_SIT
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
r_if
c_cond
(paren
id|p
op_minus
(paren
id|ETH_ALEN
op_star
l_int|2
op_plus
l_int|2
)paren
OG
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|head
)paren
(brace
id|p
op_sub_assign
(paren
id|ETH_ALEN
op_plus
l_int|2
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
(paren
id|ETH_ALEN
)paren
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
l_string|&quot;%02x%s&quot;
comma
op_star
id|p
comma
id|i
op_eq
id|ETH_ALEN
op_minus
l_int|1
ques
c_cond
l_string|&quot;-&gt;&quot;
suffix:colon
l_string|&quot;:&quot;
)paren
suffix:semicolon
id|p
op_sub_assign
(paren
id|ETH_ALEN
op_star
l_int|2
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
(paren
id|ETH_ALEN
)paren
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
id|ETH_ALEN
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
r_if
c_cond
(paren
(paren
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|dev-&gt;addr_len
op_eq
l_int|4
)paren
op_logical_and
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|dev-&gt;hard_header_len
OG
l_int|20
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;TUNNEL=&quot;
)paren
suffix:semicolon
id|p
op_assign
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|mac.raw
op_plus
l_int|12
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
l_int|4
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
l_string|&quot;%3d%s&quot;
comma
op_star
id|p
comma
id|i
op_eq
l_int|3
ques
c_cond
l_string|&quot;-&gt;&quot;
suffix:colon
l_string|&quot;.&quot;
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
l_int|4
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
l_string|&quot;%3d%c&quot;
comma
op_star
id|p
comma
id|i
op_eq
l_int|3
ques
c_cond
l_char|&squot; &squot;
suffix:colon
l_char|&squot;.&squot;
)paren
suffix:semicolon
)brace
)brace
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
id|ipv6h
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
id|IP6T_CONTINUE
suffix:semicolon
)brace
DECL|function|ip6t_log_checkentry
r_static
r_int
id|ip6t_log_checkentry
c_func
(paren
r_const
r_char
op_star
id|tablename
comma
r_const
r_struct
id|ip6t_entry
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
id|ip6t_log_info
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
id|IP6T_ALIGN
c_func
(paren
r_sizeof
(paren
r_struct
id|ip6t_log_info
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
id|IP6T_ALIGN
c_func
(paren
r_sizeof
(paren
r_struct
id|ip6t_log_info
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
DECL|variable|ip6t_log_reg
r_static
r_struct
id|ip6t_target
id|ip6t_log_reg
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
id|ip6t_log_target
comma
id|ip6t_log_checkentry
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
id|ip6t_register_target
c_func
(paren
op_amp
id|ip6t_log_reg
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
id|ip6t_unregister_target
c_func
(paren
op_amp
id|ip6t_log_reg
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
