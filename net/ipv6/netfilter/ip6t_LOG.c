multiline_comment|/*&n; * This is a module which is used for logging packets.&n; */
multiline_comment|/* (C) 2001 Jan Rekorajski &lt;baggins@pld.org.pl&gt;&n; * (C) 2002-2004 Netfilter Core Team &lt;coreteam@netfilter.org&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/moduleparam.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/ip.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/icmpv6.h&gt;
macro_line|#include &lt;net/udp.h&gt;
macro_line|#include &lt;net/tcp.h&gt;
macro_line|#include &lt;net/ipv6.h&gt;
macro_line|#include &lt;linux/netfilter.h&gt;
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
DECL|variable|nflog
r_static
r_int
r_int
id|nflog
op_assign
l_int|1
suffix:semicolon
id|module_param
c_func
(paren
id|nflog
comma
r_int
comma
l_int|0400
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|nflog
comma
l_string|&quot;register as internal netfilter logging module&quot;
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
multiline_comment|/* Use lock to serialize, so printks don&squot;t overlap */
r_static
id|DEFINE_SPINLOCK
c_func
(paren
id|log_lock
)paren
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
id|ip6t_log_info
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
id|ip6hoff
comma
r_int
id|recurse
)paren
(brace
id|u_int8_t
id|currenthdr
suffix:semicolon
r_int
id|fragment
suffix:semicolon
r_struct
id|ipv6hdr
id|_ip6h
comma
op_star
id|ih
suffix:semicolon
r_int
r_int
id|ptr
suffix:semicolon
r_int
r_int
id|hdrlen
op_assign
l_int|0
suffix:semicolon
id|ih
op_assign
id|skb_header_pointer
c_func
(paren
id|skb
comma
id|ip6hoff
comma
r_sizeof
(paren
id|_ip6h
)paren
comma
op_amp
id|_ip6h
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ih
op_eq
l_int|NULL
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
multiline_comment|/* Max length: 88 &quot;SRC=0000.0000.0000.0000.0000.0000.0000.0000 DST=0000.0000.0000.0000.0000.0000.0000.0000&quot; */
id|printk
c_func
(paren
l_string|&quot;SRC=%04x:%04x:%04x:%04x:%04x:%04x:%04x:%04x &quot;
comma
id|NIP6
c_func
(paren
id|ih-&gt;saddr
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
id|ih-&gt;daddr
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
id|ih-&gt;payload_len
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
id|ih
)paren
op_amp
l_int|0x0ff00000
)paren
op_rshift
l_int|20
comma
id|ih-&gt;hop_limit
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
id|ih
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
id|ptr
op_assign
id|ip6hoff
op_plus
r_sizeof
(paren
r_struct
id|ipv6hdr
)paren
suffix:semicolon
id|currenthdr
op_assign
id|ih-&gt;nexthdr
suffix:semicolon
r_while
c_loop
(paren
id|currenthdr
op_ne
id|NEXTHDR_NONE
op_logical_and
id|ip6t_ext_hdr
c_func
(paren
id|currenthdr
)paren
)paren
(brace
r_struct
id|ipv6_opt_hdr
id|_hdr
comma
op_star
id|hp
suffix:semicolon
id|hp
op_assign
id|skb_header_pointer
c_func
(paren
id|skb
comma
id|ptr
comma
r_sizeof
(paren
id|_hdr
)paren
comma
op_amp
id|_hdr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hp
op_eq
l_int|NULL
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
multiline_comment|/* Max length: 48 &quot;OPT (...) &quot; */
r_if
c_cond
(paren
id|info-&gt;logflags
op_amp
id|IP6T_LOG_IPOPT
)paren
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
id|_fhdr
comma
op_star
id|fh
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;FRAG:&quot;
)paren
suffix:semicolon
id|fh
op_assign
id|skb_header_pointer
c_func
(paren
id|skb
comma
id|ptr
comma
r_sizeof
(paren
id|_fhdr
)paren
comma
op_amp
id|_fhdr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fh
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;TRUNCATED &quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Max length: 6 &quot;65535 &quot; */
id|printk
c_func
(paren
l_string|&quot;%u &quot;
comma
id|ntohs
c_func
(paren
id|fh-&gt;frag_off
)paren
op_amp
l_int|0xFFF8
)paren
suffix:semicolon
multiline_comment|/* Max length: 11 &quot;INCOMPLETE &quot; */
r_if
c_cond
(paren
id|fh-&gt;frag_off
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
id|ntohl
c_func
(paren
id|fh-&gt;identification
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ntohs
c_func
(paren
id|fh-&gt;frag_off
)paren
op_amp
l_int|0xFFF8
)paren
id|fragment
op_assign
l_int|1
suffix:semicolon
id|hdrlen
op_assign
l_int|8
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
r_if
c_cond
(paren
id|fragment
)paren
(brace
r_if
c_cond
(paren
id|info-&gt;logflags
op_amp
id|IP6T_LOG_IPOPT
)paren
id|printk
c_func
(paren
l_string|&quot;)&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|hdrlen
op_assign
id|ipv6_optlen
c_func
(paren
id|hp
)paren
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* Max Length */
r_case
id|IPPROTO_AH
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
id|ip_auth_hdr
id|_ahdr
comma
op_star
id|ah
suffix:semicolon
multiline_comment|/* Max length: 3 &quot;AH &quot; */
id|printk
c_func
(paren
l_string|&quot;AH &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fragment
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;)&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|ah
op_assign
id|skb_header_pointer
c_func
(paren
id|skb
comma
id|ptr
comma
r_sizeof
(paren
id|_ahdr
)paren
comma
op_amp
id|_ahdr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ah
op_eq
l_int|NULL
)paren
(brace
multiline_comment|/*&n;&t;&t;&t;&t;&t; * Max length: 26 &quot;INCOMPLETE [65535 &t;&n;&t;&t;&t;&t;&t; *  bytes] )&quot;&n;&t;&t;&t;&t;&t; */
id|printk
c_func
(paren
l_string|&quot;INCOMPLETE [%u bytes] )&quot;
comma
id|skb-&gt;len
op_minus
id|ptr
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Length: 15 &quot;SPI=0xF1234567 */
id|printk
c_func
(paren
l_string|&quot;SPI=0x%x &quot;
comma
id|ntohl
c_func
(paren
id|ah-&gt;spi
)paren
)paren
suffix:semicolon
)brace
id|hdrlen
op_assign
(paren
id|hp-&gt;hdrlen
op_plus
l_int|2
)paren
op_lshift
l_int|2
suffix:semicolon
r_break
suffix:semicolon
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
id|ip_esp_hdr
id|_esph
comma
op_star
id|eh
suffix:semicolon
multiline_comment|/* Max length: 4 &quot;ESP &quot; */
id|printk
c_func
(paren
l_string|&quot;ESP &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fragment
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;)&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t;&t;&t; * Max length: 26 &quot;INCOMPLETE [65535 bytes] )&quot;&n;&t;&t;&t;&t; */
id|eh
op_assign
id|skb_header_pointer
c_func
(paren
id|skb
comma
id|ptr
comma
r_sizeof
(paren
id|_esph
)paren
comma
op_amp
id|_esph
)paren
suffix:semicolon
r_if
c_cond
(paren
id|eh
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;INCOMPLETE [%u bytes] )&quot;
comma
id|skb-&gt;len
op_minus
id|ptr
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Length: 16 &quot;SPI=0xF1234567 )&quot; */
id|printk
c_func
(paren
l_string|&quot;SPI=0x%x )&quot;
comma
id|ntohl
c_func
(paren
id|eh-&gt;spi
)paren
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* Max length: 20 &quot;Unknown Ext Hdr 255&quot; */
id|printk
c_func
(paren
l_string|&quot;Unknown Ext Hdr %u&quot;
comma
id|currenthdr
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|info-&gt;logflags
op_amp
id|IP6T_LOG_IPOPT
)paren
id|printk
c_func
(paren
l_string|&quot;) &quot;
)paren
suffix:semicolon
id|currenthdr
op_assign
id|hp-&gt;nexthdr
suffix:semicolon
id|ptr
op_add_assign
id|hdrlen
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
id|_tcph
comma
op_star
id|th
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
multiline_comment|/* Max length: 25 &quot;INCOMPLETE [65535 bytes] &quot; */
id|th
op_assign
id|skb_header_pointer
c_func
(paren
id|skb
comma
id|ptr
comma
r_sizeof
(paren
id|_tcph
)paren
comma
op_amp
id|_tcph
)paren
suffix:semicolon
r_if
c_cond
(paren
id|th
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;INCOMPLETE [%u bytes] &quot;
comma
id|skb-&gt;len
op_minus
id|ptr
)paren
suffix:semicolon
r_return
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
id|th-&gt;source
)paren
comma
id|ntohs
c_func
(paren
id|th-&gt;dest
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
id|th-&gt;seq
)paren
comma
id|ntohl
c_func
(paren
id|th-&gt;ack_seq
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
id|th-&gt;window
)paren
)paren
suffix:semicolon
multiline_comment|/* Max length: 9 &quot;RES=0x3C &quot; */
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
id|th
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
id|th-&gt;cwr
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
id|th-&gt;ece
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
id|th-&gt;urg
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
id|th-&gt;ack
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
id|th-&gt;psh
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
id|th-&gt;rst
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
id|th-&gt;syn
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
id|th-&gt;fin
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
id|th-&gt;urg_ptr
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
id|th-&gt;doff
op_star
l_int|4
OG
r_sizeof
(paren
r_struct
id|tcphdr
)paren
)paren
(brace
id|u_int8_t
id|_opt
(braket
l_int|60
op_minus
r_sizeof
(paren
r_struct
id|tcphdr
)paren
)braket
comma
op_star
id|op
suffix:semicolon
r_int
r_int
id|i
suffix:semicolon
r_int
r_int
id|optsize
op_assign
id|th-&gt;doff
op_star
l_int|4
op_minus
r_sizeof
(paren
r_struct
id|tcphdr
)paren
suffix:semicolon
id|op
op_assign
id|skb_header_pointer
c_func
(paren
id|skb
comma
id|ptr
op_plus
r_sizeof
(paren
r_struct
id|tcphdr
)paren
comma
id|optsize
comma
id|_opt
)paren
suffix:semicolon
r_if
c_cond
(paren
id|op
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;OPT (TRUNCATED)&quot;
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
id|op
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
id|_udph
comma
op_star
id|uh
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
multiline_comment|/* Max length: 25 &quot;INCOMPLETE [65535 bytes] &quot; */
id|uh
op_assign
id|skb_header_pointer
c_func
(paren
id|skb
comma
id|ptr
comma
r_sizeof
(paren
id|_udph
)paren
comma
op_amp
id|_udph
)paren
suffix:semicolon
r_if
c_cond
(paren
id|uh
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;INCOMPLETE [%u bytes] &quot;
comma
id|skb-&gt;len
op_minus
id|ptr
)paren
suffix:semicolon
r_return
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
id|uh-&gt;source
)paren
comma
id|ntohs
c_func
(paren
id|uh-&gt;dest
)paren
comma
id|ntohs
c_func
(paren
id|uh-&gt;len
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
id|_icmp6h
comma
op_star
id|ic
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
multiline_comment|/* Max length: 25 &quot;INCOMPLETE [65535 bytes] &quot; */
id|ic
op_assign
id|skb_header_pointer
c_func
(paren
id|skb
comma
id|ptr
comma
r_sizeof
(paren
id|_icmp6h
)paren
comma
op_amp
id|_icmp6h
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ic
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;INCOMPLETE [%u bytes] &quot;
comma
id|skb-&gt;len
op_minus
id|ptr
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Max length: 18 &quot;TYPE=255 CODE=255 &quot; */
id|printk
c_func
(paren
l_string|&quot;TYPE=%u CODE=%u &quot;
comma
id|ic-&gt;icmp6_type
comma
id|ic-&gt;icmp6_code
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|ic-&gt;icmp6_type
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
id|ic-&gt;icmp6_identifier
)paren
comma
id|ntohs
c_func
(paren
id|ic-&gt;icmp6_sequence
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
id|ic-&gt;icmp6_pointer
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
id|skb
comma
id|ptr
op_plus
r_sizeof
(paren
id|_icmp6h
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
id|ic-&gt;icmp6_type
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
id|ic-&gt;icmp6_mtu
)paren
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
multiline_comment|/* Max length: 10 &quot;PROTO=255 &quot; */
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
r_void
DECL|function|ip6t_log_packet
id|ip6t_log_packet
c_func
(paren
r_int
r_int
id|hooknum
comma
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
r_struct
id|ip6t_log_info
op_star
id|loginfo
comma
r_const
r_char
op_star
id|level_string
comma
r_const
r_char
op_star
id|prefix
)paren
(brace
r_struct
id|ipv6hdr
op_star
id|ipv6h
op_assign
id|skb-&gt;nh.ipv6h
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
id|prefix
op_eq
l_int|NULL
ques
c_cond
id|loginfo-&gt;prefix
suffix:colon
id|prefix
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
id|skb-&gt;dev
op_logical_and
id|skb-&gt;dev-&gt;hard_header_len
op_logical_and
id|skb-&gt;mac.raw
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
id|skb-&gt;dev-&gt;type
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
id|skb-&gt;mac.raw
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
id|skb-&gt;dev-&gt;hard_header_len
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
id|skb-&gt;dev-&gt;hard_header_len
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
id|skb-&gt;mac.raw
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
id|skb-&gt;head
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
id|skb-&gt;dev-&gt;addr_len
op_eq
l_int|4
)paren
op_logical_and
id|skb-&gt;dev-&gt;hard_header_len
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
id|skb-&gt;mac.raw
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
id|skb
comma
(paren
id|u8
op_star
)paren
id|skb-&gt;nh.ipv6h
op_minus
id|skb-&gt;data
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
id|ip6t_log_packet
c_func
(paren
id|hooknum
comma
op_star
id|pskb
comma
id|in
comma
id|out
comma
id|loginfo
comma
id|level_string
comma
l_int|NULL
)paren
suffix:semicolon
r_return
id|IP6T_CONTINUE
suffix:semicolon
)brace
r_static
r_void
DECL|function|ip6t_logfn
id|ip6t_logfn
c_func
(paren
r_int
r_int
id|hooknum
comma
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
r_char
op_star
id|prefix
)paren
(brace
r_struct
id|ip6t_log_info
id|loginfo
op_assign
(brace
dot
id|level
op_assign
l_int|0
comma
dot
id|logflags
op_assign
id|IP6T_LOG_MASK
comma
dot
id|prefix
op_assign
l_string|&quot;&quot;
)brace
suffix:semicolon
id|ip6t_log_packet
c_func
(paren
id|hooknum
comma
id|skb
comma
id|in
comma
id|out
comma
op_amp
id|loginfo
comma
id|KERN_WARNING
comma
id|prefix
)paren
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
dot
id|name
op_assign
l_string|&quot;LOG&quot;
comma
dot
id|target
op_assign
id|ip6t_log_target
comma
dot
id|checkentry
op_assign
id|ip6t_log_checkentry
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
r_if
c_cond
(paren
id|nflog
)paren
id|nf_log_register
c_func
(paren
id|PF_INET6
comma
op_amp
id|ip6t_logfn
)paren
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
r_if
c_cond
(paren
id|nflog
)paren
id|nf_log_unregister
c_func
(paren
id|PF_INET6
comma
op_amp
id|ip6t_logfn
)paren
suffix:semicolon
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
