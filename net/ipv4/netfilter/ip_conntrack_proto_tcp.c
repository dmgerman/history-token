multiline_comment|/* (C) 1999-2001 Paul `Rusty&squot; Russell&n; * (C) 2002-2004 Netfilter Core Team &lt;coreteam@netfilter.org&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/netfilter.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/ip.h&gt;
macro_line|#include &lt;linux/tcp.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;net/tcp.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_conntrack.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_conntrack_protocol.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/lockhelp.h&gt;
macro_line|#if 0
mdefine_line|#define DEBUGP printk
macro_line|#else
DECL|macro|DEBUGP
mdefine_line|#define DEBUGP(format, args...)
macro_line|#endif
multiline_comment|/* Protects conntrack-&gt;proto.tcp */
r_static
id|DECLARE_RWLOCK
c_func
(paren
id|tcp_lock
)paren
suffix:semicolon
multiline_comment|/* FIXME: Examine ipfilter&squot;s timeouts and conntrack transitions more&n;   closely.  They&squot;re more complex. --RR */
multiline_comment|/* Actually, I believe that neither ipmasq (where this code is stolen&n;   from) nor ipfilter do it exactly right.  A new conntrack machine taking&n;   into account packet loss (which creates uncertainty as to exactly&n;   the conntrack of the connection) is required.  RSN.  --RR */
DECL|variable|tcp_conntrack_names
r_static
r_const
r_char
op_star
id|tcp_conntrack_names
(braket
)braket
op_assign
(brace
l_string|&quot;NONE&quot;
comma
l_string|&quot;ESTABLISHED&quot;
comma
l_string|&quot;SYN_SENT&quot;
comma
l_string|&quot;SYN_RECV&quot;
comma
l_string|&quot;FIN_WAIT&quot;
comma
l_string|&quot;TIME_WAIT&quot;
comma
l_string|&quot;CLOSE&quot;
comma
l_string|&quot;CLOSE_WAIT&quot;
comma
l_string|&quot;LAST_ACK&quot;
comma
l_string|&quot;LISTEN&quot;
)brace
suffix:semicolon
DECL|macro|SECS
mdefine_line|#define SECS *HZ
DECL|macro|MINS
mdefine_line|#define MINS * 60 SECS
DECL|macro|HOURS
mdefine_line|#define HOURS * 60 MINS
DECL|macro|DAYS
mdefine_line|#define DAYS * 24 HOURS
DECL|variable|ip_ct_tcp_timeout_syn_sent
r_int
r_int
id|ip_ct_tcp_timeout_syn_sent
op_assign
l_int|2
id|MINS
suffix:semicolon
DECL|variable|ip_ct_tcp_timeout_syn_recv
r_int
r_int
id|ip_ct_tcp_timeout_syn_recv
op_assign
l_int|60
id|SECS
suffix:semicolon
DECL|variable|ip_ct_tcp_timeout_established
r_int
r_int
id|ip_ct_tcp_timeout_established
op_assign
l_int|5
id|DAYS
suffix:semicolon
DECL|variable|ip_ct_tcp_timeout_fin_wait
r_int
r_int
id|ip_ct_tcp_timeout_fin_wait
op_assign
l_int|2
id|MINS
suffix:semicolon
DECL|variable|ip_ct_tcp_timeout_close_wait
r_int
r_int
id|ip_ct_tcp_timeout_close_wait
op_assign
l_int|60
id|SECS
suffix:semicolon
DECL|variable|ip_ct_tcp_timeout_last_ack
r_int
r_int
id|ip_ct_tcp_timeout_last_ack
op_assign
l_int|30
id|SECS
suffix:semicolon
DECL|variable|ip_ct_tcp_timeout_time_wait
r_int
r_int
id|ip_ct_tcp_timeout_time_wait
op_assign
l_int|2
id|MINS
suffix:semicolon
DECL|variable|ip_ct_tcp_timeout_close
r_int
r_int
id|ip_ct_tcp_timeout_close
op_assign
l_int|10
id|SECS
suffix:semicolon
DECL|variable|tcp_timeouts
r_static
r_int
r_int
op_star
id|tcp_timeouts
(braket
)braket
op_assign
(brace
l_int|NULL
comma
multiline_comment|/*      TCP_CONNTRACK_NONE */
op_amp
id|ip_ct_tcp_timeout_established
comma
multiline_comment|/*      TCP_CONNTRACK_ESTABLISHED,      */
op_amp
id|ip_ct_tcp_timeout_syn_sent
comma
multiline_comment|/*      TCP_CONNTRACK_SYN_SENT, */
op_amp
id|ip_ct_tcp_timeout_syn_recv
comma
multiline_comment|/*      TCP_CONNTRACK_SYN_RECV, */
op_amp
id|ip_ct_tcp_timeout_fin_wait
comma
multiline_comment|/*      TCP_CONNTRACK_FIN_WAIT, */
op_amp
id|ip_ct_tcp_timeout_time_wait
comma
multiline_comment|/*      TCP_CONNTRACK_TIME_WAIT,        */
op_amp
id|ip_ct_tcp_timeout_close
comma
multiline_comment|/*      TCP_CONNTRACK_CLOSE,    */
op_amp
id|ip_ct_tcp_timeout_close_wait
comma
multiline_comment|/*      TCP_CONNTRACK_CLOSE_WAIT,       */
op_amp
id|ip_ct_tcp_timeout_last_ack
comma
multiline_comment|/*      TCP_CONNTRACK_LAST_ACK, */
l_int|NULL
comma
multiline_comment|/*      TCP_CONNTRACK_LISTEN */
)brace
suffix:semicolon
DECL|macro|sNO
mdefine_line|#define sNO TCP_CONNTRACK_NONE
DECL|macro|sES
mdefine_line|#define sES TCP_CONNTRACK_ESTABLISHED
DECL|macro|sSS
mdefine_line|#define sSS TCP_CONNTRACK_SYN_SENT
DECL|macro|sSR
mdefine_line|#define sSR TCP_CONNTRACK_SYN_RECV
DECL|macro|sFW
mdefine_line|#define sFW TCP_CONNTRACK_FIN_WAIT
DECL|macro|sTW
mdefine_line|#define sTW TCP_CONNTRACK_TIME_WAIT
DECL|macro|sCL
mdefine_line|#define sCL TCP_CONNTRACK_CLOSE
DECL|macro|sCW
mdefine_line|#define sCW TCP_CONNTRACK_CLOSE_WAIT
DECL|macro|sLA
mdefine_line|#define sLA TCP_CONNTRACK_LAST_ACK
DECL|macro|sLI
mdefine_line|#define sLI TCP_CONNTRACK_LISTEN
DECL|macro|sIV
mdefine_line|#define sIV TCP_CONNTRACK_MAX
DECL|variable|tcp_conntracks
r_static
r_enum
id|tcp_conntrack
id|tcp_conntracks
(braket
l_int|2
)braket
(braket
l_int|5
)braket
(braket
id|TCP_CONNTRACK_MAX
)braket
op_assign
(brace
(brace
multiline_comment|/*&t;ORIGINAL */
multiline_comment|/* &t;  sNO, sES, sSS, sSR, sFW, sTW, sCL, sCW, sLA, sLI &t;*/
multiline_comment|/*syn*/
(brace
id|sSS
comma
id|sES
comma
id|sSS
comma
id|sSR
comma
id|sSS
comma
id|sSS
comma
id|sSS
comma
id|sSS
comma
id|sSS
comma
id|sLI
)brace
comma
multiline_comment|/*fin*/
(brace
id|sTW
comma
id|sFW
comma
id|sSS
comma
id|sTW
comma
id|sFW
comma
id|sTW
comma
id|sCL
comma
id|sTW
comma
id|sLA
comma
id|sLI
)brace
comma
multiline_comment|/*ack*/
(brace
id|sES
comma
id|sES
comma
id|sSS
comma
id|sES
comma
id|sFW
comma
id|sTW
comma
id|sCL
comma
id|sCW
comma
id|sLA
comma
id|sES
)brace
comma
multiline_comment|/*rst*/
(brace
id|sCL
comma
id|sCL
comma
id|sSS
comma
id|sCL
comma
id|sCL
comma
id|sTW
comma
id|sCL
comma
id|sCL
comma
id|sCL
comma
id|sCL
)brace
comma
multiline_comment|/*none*/
(brace
id|sIV
comma
id|sIV
comma
id|sIV
comma
id|sIV
comma
id|sIV
comma
id|sIV
comma
id|sIV
comma
id|sIV
comma
id|sIV
comma
id|sIV
)brace
)brace
comma
(brace
multiline_comment|/*&t;REPLY */
multiline_comment|/* &t;  sNO, sES, sSS, sSR, sFW, sTW, sCL, sCW, sLA, sLI &t;*/
multiline_comment|/*syn*/
(brace
id|sSR
comma
id|sES
comma
id|sSR
comma
id|sSR
comma
id|sSR
comma
id|sSR
comma
id|sSR
comma
id|sSR
comma
id|sSR
comma
id|sSR
)brace
comma
multiline_comment|/*fin*/
(brace
id|sCL
comma
id|sCW
comma
id|sSS
comma
id|sTW
comma
id|sTW
comma
id|sTW
comma
id|sCL
comma
id|sCW
comma
id|sLA
comma
id|sLI
)brace
comma
multiline_comment|/*ack*/
(brace
id|sCL
comma
id|sES
comma
id|sSS
comma
id|sSR
comma
id|sFW
comma
id|sTW
comma
id|sCL
comma
id|sCW
comma
id|sCL
comma
id|sLI
)brace
comma
multiline_comment|/*rst*/
(brace
id|sCL
comma
id|sCL
comma
id|sCL
comma
id|sCL
comma
id|sCL
comma
id|sCL
comma
id|sCL
comma
id|sCL
comma
id|sLA
comma
id|sLI
)brace
comma
multiline_comment|/*none*/
(brace
id|sIV
comma
id|sIV
comma
id|sIV
comma
id|sIV
comma
id|sIV
comma
id|sIV
comma
id|sIV
comma
id|sIV
comma
id|sIV
comma
id|sIV
)brace
)brace
)brace
suffix:semicolon
DECL|function|tcp_pkt_to_tuple
r_static
r_int
id|tcp_pkt_to_tuple
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
id|tcphdr
id|hdr
suffix:semicolon
multiline_comment|/* Actually only need first 8 bytes. */
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
l_int|8
)paren
op_ne
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|tuple-&gt;src.u.tcp.port
op_assign
id|hdr.source
suffix:semicolon
id|tuple-&gt;dst.u.tcp.port
op_assign
id|hdr.dest
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|tcp_invert_tuple
r_static
r_int
id|tcp_invert_tuple
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
id|tuple-&gt;src.u.tcp.port
op_assign
id|orig-&gt;dst.u.tcp.port
suffix:semicolon
id|tuple-&gt;dst.u.tcp.port
op_assign
id|orig-&gt;src.u.tcp.port
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Print out the per-protocol part of the tuple. */
DECL|function|tcp_print_tuple
r_static
r_int
r_int
id|tcp_print_tuple
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
l_string|&quot;sport=%hu dport=%hu &quot;
comma
id|ntohs
c_func
(paren
id|tuple-&gt;src.u.tcp.port
)paren
comma
id|ntohs
c_func
(paren
id|tuple-&gt;dst.u.tcp.port
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Print out the private part of the conntrack. */
DECL|function|tcp_print_conntrack
r_static
r_int
r_int
id|tcp_print_conntrack
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
r_enum
id|tcp_conntrack
id|state
suffix:semicolon
id|READ_LOCK
c_func
(paren
op_amp
id|tcp_lock
)paren
suffix:semicolon
id|state
op_assign
id|conntrack-&gt;proto.tcp.state
suffix:semicolon
id|READ_UNLOCK
c_func
(paren
op_amp
id|tcp_lock
)paren
suffix:semicolon
r_return
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;%s &quot;
comma
id|tcp_conntrack_names
(braket
id|state
)braket
)paren
suffix:semicolon
)brace
DECL|function|get_conntrack_index
r_static
r_int
r_int
id|get_conntrack_index
c_func
(paren
r_const
r_struct
id|tcphdr
op_star
id|tcph
)paren
(brace
r_if
c_cond
(paren
id|tcph-&gt;rst
)paren
r_return
l_int|3
suffix:semicolon
r_else
r_if
c_cond
(paren
id|tcph-&gt;syn
)paren
r_return
l_int|0
suffix:semicolon
r_else
r_if
c_cond
(paren
id|tcph-&gt;fin
)paren
r_return
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
id|tcph-&gt;ack
)paren
r_return
l_int|2
suffix:semicolon
r_else
r_return
l_int|4
suffix:semicolon
)brace
multiline_comment|/* Returns verdict for packet, or -1 for invalid. */
DECL|function|tcp_packet
r_static
r_int
id|tcp_packet
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
r_enum
id|tcp_conntrack
id|newconntrack
comma
id|oldtcpstate
suffix:semicolon
r_struct
id|tcphdr
id|tcph
suffix:semicolon
r_if
c_cond
(paren
id|skb_copy_bits
c_func
(paren
id|skb
comma
id|skb-&gt;nh.iph-&gt;ihl
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
op_ne
l_int|0
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|skb-&gt;len
OL
id|skb-&gt;nh.iph-&gt;ihl
op_star
l_int|4
op_plus
id|tcph.doff
op_star
l_int|4
)paren
r_return
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* If only reply is a RST, we can consider ourselves not to&n;&t;   have an established connection: this is a fairly common&n;&t;   problem case, so we can delete the conntrack&n;&t;   immediately.  --RR */
r_if
c_cond
(paren
op_logical_neg
id|test_bit
c_func
(paren
id|IPS_SEEN_REPLY_BIT
comma
op_amp
id|conntrack-&gt;status
)paren
op_logical_and
id|tcph.rst
)paren
(brace
r_if
c_cond
(paren
id|del_timer
c_func
(paren
op_amp
id|conntrack-&gt;timeout
)paren
)paren
id|conntrack-&gt;timeout
dot
id|function
c_func
(paren
(paren
r_int
r_int
)paren
id|conntrack
)paren
suffix:semicolon
r_return
id|NF_ACCEPT
suffix:semicolon
)brace
id|WRITE_LOCK
c_func
(paren
op_amp
id|tcp_lock
)paren
suffix:semicolon
id|oldtcpstate
op_assign
id|conntrack-&gt;proto.tcp.state
suffix:semicolon
id|newconntrack
op_assign
id|tcp_conntracks
(braket
id|CTINFO2DIR
c_func
(paren
id|ctinfo
)paren
)braket
(braket
id|get_conntrack_index
c_func
(paren
op_amp
id|tcph
)paren
)braket
(braket
id|oldtcpstate
)braket
suffix:semicolon
multiline_comment|/* Invalid */
r_if
c_cond
(paren
id|newconntrack
op_eq
id|TCP_CONNTRACK_MAX
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;ip_conntrack_tcp: Invalid dir=%i index=%u conntrack=%u&bslash;n&quot;
comma
id|CTINFO2DIR
c_func
(paren
id|ctinfo
)paren
comma
id|get_conntrack_index
c_func
(paren
op_amp
id|tcph
)paren
comma
id|conntrack-&gt;proto.tcp.state
)paren
suffix:semicolon
id|WRITE_UNLOCK
c_func
(paren
op_amp
id|tcp_lock
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|conntrack-&gt;proto.tcp.state
op_assign
id|newconntrack
suffix:semicolon
multiline_comment|/* Poor man&squot;s window tracking: record SYN/ACK for handshake check */
r_if
c_cond
(paren
id|oldtcpstate
op_eq
id|TCP_CONNTRACK_SYN_SENT
op_logical_and
id|CTINFO2DIR
c_func
(paren
id|ctinfo
)paren
op_eq
id|IP_CT_DIR_REPLY
op_logical_and
id|tcph.syn
op_logical_and
id|tcph.ack
)paren
(brace
id|conntrack-&gt;proto.tcp.handshake_ack
op_assign
id|htonl
c_func
(paren
id|ntohl
c_func
(paren
id|tcph.seq
)paren
op_plus
l_int|1
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/* Set ASSURED if we see valid ack in ESTABLISHED after SYN_RECV */
r_if
c_cond
(paren
id|oldtcpstate
op_eq
id|TCP_CONNTRACK_SYN_RECV
op_logical_and
id|CTINFO2DIR
c_func
(paren
id|ctinfo
)paren
op_eq
id|IP_CT_DIR_ORIGINAL
op_logical_and
id|tcph.ack
op_logical_and
op_logical_neg
id|tcph.syn
op_logical_and
id|tcph.ack_seq
op_eq
id|conntrack-&gt;proto.tcp.handshake_ack
)paren
id|set_bit
c_func
(paren
id|IPS_ASSURED_BIT
comma
op_amp
id|conntrack-&gt;status
)paren
suffix:semicolon
id|out
suffix:colon
id|WRITE_UNLOCK
c_func
(paren
op_amp
id|tcp_lock
)paren
suffix:semicolon
id|ip_ct_refresh_acct
c_func
(paren
id|conntrack
comma
id|ctinfo
comma
id|skb
comma
op_star
id|tcp_timeouts
(braket
id|newconntrack
)braket
)paren
suffix:semicolon
r_return
id|NF_ACCEPT
suffix:semicolon
)brace
multiline_comment|/* Called when a new connection for this protocol found. */
DECL|function|tcp_new
r_static
r_int
id|tcp_new
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
r_enum
id|tcp_conntrack
id|newconntrack
suffix:semicolon
r_struct
id|tcphdr
id|tcph
suffix:semicolon
r_if
c_cond
(paren
id|skb_copy_bits
c_func
(paren
id|skb
comma
id|skb-&gt;nh.iph-&gt;ihl
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
op_ne
l_int|0
)paren
r_return
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* Don&squot;t need lock here: this conntrack not in circulation yet */
id|newconntrack
op_assign
id|tcp_conntracks
(braket
l_int|0
)braket
(braket
id|get_conntrack_index
c_func
(paren
op_amp
id|tcph
)paren
)braket
(braket
id|TCP_CONNTRACK_NONE
)braket
suffix:semicolon
multiline_comment|/* Invalid: delete conntrack */
r_if
c_cond
(paren
id|newconntrack
op_eq
id|TCP_CONNTRACK_MAX
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;ip_conntrack_tcp: invalid new deleting.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|conntrack-&gt;proto.tcp.state
op_assign
id|newconntrack
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|tcp_exp_matches_pkt
r_static
r_int
id|tcp_exp_matches_pkt
c_func
(paren
r_struct
id|ip_conntrack_expect
op_star
id|exp
comma
r_const
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_const
r_struct
id|iphdr
op_star
id|iph
op_assign
id|skb-&gt;nh.iph
suffix:semicolon
r_struct
id|tcphdr
id|tcph
suffix:semicolon
r_int
r_int
id|datalen
suffix:semicolon
r_if
c_cond
(paren
id|skb_copy_bits
c_func
(paren
id|skb
comma
id|skb-&gt;nh.iph-&gt;ihl
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
op_ne
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|datalen
op_assign
id|skb-&gt;len
op_minus
id|iph-&gt;ihl
op_star
l_int|4
op_minus
id|tcph.doff
op_star
l_int|4
suffix:semicolon
r_return
id|between
c_func
(paren
id|exp-&gt;seq
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
id|tcph.seq
)paren
op_plus
id|datalen
)paren
suffix:semicolon
)brace
DECL|variable|ip_conntrack_protocol_tcp
r_struct
id|ip_conntrack_protocol
id|ip_conntrack_protocol_tcp
op_assign
(brace
dot
id|proto
op_assign
id|IPPROTO_TCP
comma
dot
id|name
op_assign
l_string|&quot;tcp&quot;
comma
dot
id|pkt_to_tuple
op_assign
id|tcp_pkt_to_tuple
comma
dot
id|invert_tuple
op_assign
id|tcp_invert_tuple
comma
dot
id|print_tuple
op_assign
id|tcp_print_tuple
comma
dot
id|print_conntrack
op_assign
id|tcp_print_conntrack
comma
dot
id|packet
op_assign
id|tcp_packet
comma
dot
r_new
op_assign
id|tcp_new
comma
dot
id|exp_matches_pkt
op_assign
id|tcp_exp_matches_pkt
comma
)brace
suffix:semicolon
eof
