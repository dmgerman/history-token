multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;Definitions for the TCP protocol.&n; *&n; * Version:&t;@(#)tcp.h&t;1.0.2&t;04/28/93&n; *&n; * Author:&t;Fred N. van Kempen, &lt;waltje@uWalt.NL.Mugnet.ORG&gt;&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _LINUX_TCP_H
DECL|macro|_LINUX_TCP_H
mdefine_line|#define _LINUX_TCP_H
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;linux/ip.h&gt;
DECL|struct|tcphdr
r_struct
id|tcphdr
(brace
DECL|member|source
id|__u16
id|source
suffix:semicolon
DECL|member|dest
id|__u16
id|dest
suffix:semicolon
DECL|member|seq
id|__u32
id|seq
suffix:semicolon
DECL|member|ack_seq
id|__u32
id|ack_seq
suffix:semicolon
macro_line|#if defined(__LITTLE_ENDIAN_BITFIELD)
DECL|member|res1
id|__u16
id|res1
suffix:colon
l_int|4
comma
DECL|member|doff
id|doff
suffix:colon
l_int|4
comma
DECL|member|fin
id|fin
suffix:colon
l_int|1
comma
DECL|member|syn
id|syn
suffix:colon
l_int|1
comma
DECL|member|rst
id|rst
suffix:colon
l_int|1
comma
DECL|member|psh
id|psh
suffix:colon
l_int|1
comma
DECL|member|ack
id|ack
suffix:colon
l_int|1
comma
DECL|member|urg
id|urg
suffix:colon
l_int|1
comma
DECL|member|ece
id|ece
suffix:colon
l_int|1
comma
DECL|member|cwr
id|cwr
suffix:colon
l_int|1
suffix:semicolon
macro_line|#elif defined(__BIG_ENDIAN_BITFIELD)
DECL|member|doff
id|__u16
id|doff
suffix:colon
l_int|4
comma
DECL|member|res1
id|res1
suffix:colon
l_int|4
comma
DECL|member|cwr
id|cwr
suffix:colon
l_int|1
comma
DECL|member|ece
id|ece
suffix:colon
l_int|1
comma
DECL|member|urg
id|urg
suffix:colon
l_int|1
comma
DECL|member|ack
id|ack
suffix:colon
l_int|1
comma
DECL|member|psh
id|psh
suffix:colon
l_int|1
comma
DECL|member|rst
id|rst
suffix:colon
l_int|1
comma
DECL|member|syn
id|syn
suffix:colon
l_int|1
comma
DECL|member|fin
id|fin
suffix:colon
l_int|1
suffix:semicolon
macro_line|#else
macro_line|#error&t;&quot;Adjust your &lt;asm/byteorder.h&gt; defines&quot;
macro_line|#endif&t;
DECL|member|window
id|__u16
id|window
suffix:semicolon
DECL|member|check
id|__u16
id|check
suffix:semicolon
DECL|member|urg_ptr
id|__u16
id|urg_ptr
suffix:semicolon
)brace
suffix:semicolon
r_enum
(brace
DECL|enumerator|TCP_ESTABLISHED
id|TCP_ESTABLISHED
op_assign
l_int|1
comma
DECL|enumerator|TCP_SYN_SENT
id|TCP_SYN_SENT
comma
DECL|enumerator|TCP_SYN_RECV
id|TCP_SYN_RECV
comma
DECL|enumerator|TCP_FIN_WAIT1
id|TCP_FIN_WAIT1
comma
DECL|enumerator|TCP_FIN_WAIT2
id|TCP_FIN_WAIT2
comma
DECL|enumerator|TCP_TIME_WAIT
id|TCP_TIME_WAIT
comma
DECL|enumerator|TCP_CLOSE
id|TCP_CLOSE
comma
DECL|enumerator|TCP_CLOSE_WAIT
id|TCP_CLOSE_WAIT
comma
DECL|enumerator|TCP_LAST_ACK
id|TCP_LAST_ACK
comma
DECL|enumerator|TCP_LISTEN
id|TCP_LISTEN
comma
DECL|enumerator|TCP_CLOSING
id|TCP_CLOSING
comma
multiline_comment|/* now a valid state */
DECL|enumerator|TCP_MAX_STATES
id|TCP_MAX_STATES
multiline_comment|/* Leave at the end! */
)brace
suffix:semicolon
DECL|macro|TCP_STATE_MASK
mdefine_line|#define TCP_STATE_MASK&t;0xF
DECL|macro|TCP_ACTION_FIN
mdefine_line|#define TCP_ACTION_FIN&t;(1 &lt;&lt; 7)
r_enum
(brace
DECL|enumerator|TCPF_ESTABLISHED
id|TCPF_ESTABLISHED
op_assign
(paren
l_int|1
op_lshift
l_int|1
)paren
comma
DECL|enumerator|TCPF_SYN_SENT
id|TCPF_SYN_SENT
op_assign
(paren
l_int|1
op_lshift
l_int|2
)paren
comma
DECL|enumerator|TCPF_SYN_RECV
id|TCPF_SYN_RECV
op_assign
(paren
l_int|1
op_lshift
l_int|3
)paren
comma
DECL|enumerator|TCPF_FIN_WAIT1
id|TCPF_FIN_WAIT1
op_assign
(paren
l_int|1
op_lshift
l_int|4
)paren
comma
DECL|enumerator|TCPF_FIN_WAIT2
id|TCPF_FIN_WAIT2
op_assign
(paren
l_int|1
op_lshift
l_int|5
)paren
comma
DECL|enumerator|TCPF_TIME_WAIT
id|TCPF_TIME_WAIT
op_assign
(paren
l_int|1
op_lshift
l_int|6
)paren
comma
DECL|enumerator|TCPF_CLOSE
id|TCPF_CLOSE
op_assign
(paren
l_int|1
op_lshift
l_int|7
)paren
comma
DECL|enumerator|TCPF_CLOSE_WAIT
id|TCPF_CLOSE_WAIT
op_assign
(paren
l_int|1
op_lshift
l_int|8
)paren
comma
DECL|enumerator|TCPF_LAST_ACK
id|TCPF_LAST_ACK
op_assign
(paren
l_int|1
op_lshift
l_int|9
)paren
comma
DECL|enumerator|TCPF_LISTEN
id|TCPF_LISTEN
op_assign
(paren
l_int|1
op_lshift
l_int|10
)paren
comma
DECL|enumerator|TCPF_CLOSING
id|TCPF_CLOSING
op_assign
(paren
l_int|1
op_lshift
l_int|11
)paren
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;The union cast uses a gcc extension to avoid aliasing problems&n; *  (union is compatible to any of its members)&n; *  This means this part of the code is -fstrict-aliasing safe now.&n; */
DECL|union|tcp_word_hdr
r_union
id|tcp_word_hdr
(brace
DECL|member|hdr
r_struct
id|tcphdr
id|hdr
suffix:semicolon
DECL|member|words
id|__u32
id|words
(braket
l_int|5
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|tcp_flag_word
mdefine_line|#define tcp_flag_word(tp) ( ((union tcp_word_hdr *)(tp))-&gt;words [3]) 
r_enum
(brace
DECL|enumerator|TCP_FLAG_CWR
id|TCP_FLAG_CWR
op_assign
id|__constant_htonl
c_func
(paren
l_int|0x00800000
)paren
comma
DECL|enumerator|TCP_FLAG_ECE
id|TCP_FLAG_ECE
op_assign
id|__constant_htonl
c_func
(paren
l_int|0x00400000
)paren
comma
DECL|enumerator|TCP_FLAG_URG
id|TCP_FLAG_URG
op_assign
id|__constant_htonl
c_func
(paren
l_int|0x00200000
)paren
comma
DECL|enumerator|TCP_FLAG_ACK
id|TCP_FLAG_ACK
op_assign
id|__constant_htonl
c_func
(paren
l_int|0x00100000
)paren
comma
DECL|enumerator|TCP_FLAG_PSH
id|TCP_FLAG_PSH
op_assign
id|__constant_htonl
c_func
(paren
l_int|0x00080000
)paren
comma
DECL|enumerator|TCP_FLAG_RST
id|TCP_FLAG_RST
op_assign
id|__constant_htonl
c_func
(paren
l_int|0x00040000
)paren
comma
DECL|enumerator|TCP_FLAG_SYN
id|TCP_FLAG_SYN
op_assign
id|__constant_htonl
c_func
(paren
l_int|0x00020000
)paren
comma
DECL|enumerator|TCP_FLAG_FIN
id|TCP_FLAG_FIN
op_assign
id|__constant_htonl
c_func
(paren
l_int|0x00010000
)paren
comma
DECL|enumerator|TCP_RESERVED_BITS
id|TCP_RESERVED_BITS
op_assign
id|__constant_htonl
c_func
(paren
l_int|0x0F000000
)paren
comma
DECL|enumerator|TCP_DATA_OFFSET
id|TCP_DATA_OFFSET
op_assign
id|__constant_htonl
c_func
(paren
l_int|0xF0000000
)paren
)brace
suffix:semicolon
multiline_comment|/* TCP socket options */
DECL|macro|TCP_NODELAY
mdefine_line|#define TCP_NODELAY&t;&t;1&t;/* Turn off Nagle&squot;s algorithm. */
DECL|macro|TCP_MAXSEG
mdefine_line|#define TCP_MAXSEG&t;&t;2&t;/* Limit MSS */
DECL|macro|TCP_CORK
mdefine_line|#define TCP_CORK&t;&t;3&t;/* Never send partially complete segments */
DECL|macro|TCP_KEEPIDLE
mdefine_line|#define TCP_KEEPIDLE&t;&t;4&t;/* Start keeplives after this period */
DECL|macro|TCP_KEEPINTVL
mdefine_line|#define TCP_KEEPINTVL&t;&t;5&t;/* Interval between keepalives */
DECL|macro|TCP_KEEPCNT
mdefine_line|#define TCP_KEEPCNT&t;&t;6&t;/* Number of keepalives before death */
DECL|macro|TCP_SYNCNT
mdefine_line|#define TCP_SYNCNT&t;&t;7&t;/* Number of SYN retransmits */
DECL|macro|TCP_LINGER2
mdefine_line|#define TCP_LINGER2&t;&t;8&t;/* Life time of orphaned FIN-WAIT-2 state */
DECL|macro|TCP_DEFER_ACCEPT
mdefine_line|#define TCP_DEFER_ACCEPT&t;9&t;/* Wake up listener only when data arrive */
DECL|macro|TCP_WINDOW_CLAMP
mdefine_line|#define TCP_WINDOW_CLAMP&t;10&t;/* Bound advertised window */
DECL|macro|TCP_INFO
mdefine_line|#define TCP_INFO&t;&t;11&t;/* Information about this connection. */
DECL|macro|TCP_QUICKACK
mdefine_line|#define TCP_QUICKACK&t;&t;12&t;/* Block/reenable quick acks */
DECL|macro|TCPI_OPT_TIMESTAMPS
mdefine_line|#define TCPI_OPT_TIMESTAMPS&t;1
DECL|macro|TCPI_OPT_SACK
mdefine_line|#define TCPI_OPT_SACK&t;&t;2
DECL|macro|TCPI_OPT_WSCALE
mdefine_line|#define TCPI_OPT_WSCALE&t;&t;4
DECL|macro|TCPI_OPT_ECN
mdefine_line|#define TCPI_OPT_ECN&t;&t;8
DECL|enum|tcp_ca_state
r_enum
id|tcp_ca_state
(brace
DECL|enumerator|TCP_CA_Open
id|TCP_CA_Open
op_assign
l_int|0
comma
DECL|macro|TCPF_CA_Open
mdefine_line|#define TCPF_CA_Open&t;(1&lt;&lt;TCP_CA_Open)
DECL|enumerator|TCP_CA_Disorder
id|TCP_CA_Disorder
op_assign
l_int|1
comma
DECL|macro|TCPF_CA_Disorder
mdefine_line|#define TCPF_CA_Disorder (1&lt;&lt;TCP_CA_Disorder)
DECL|enumerator|TCP_CA_CWR
id|TCP_CA_CWR
op_assign
l_int|2
comma
DECL|macro|TCPF_CA_CWR
mdefine_line|#define TCPF_CA_CWR&t;(1&lt;&lt;TCP_CA_CWR)
DECL|enumerator|TCP_CA_Recovery
id|TCP_CA_Recovery
op_assign
l_int|3
comma
DECL|macro|TCPF_CA_Recovery
mdefine_line|#define TCPF_CA_Recovery (1&lt;&lt;TCP_CA_Recovery)
DECL|enumerator|TCP_CA_Loss
id|TCP_CA_Loss
op_assign
l_int|4
DECL|macro|TCPF_CA_Loss
mdefine_line|#define TCPF_CA_Loss&t;(1&lt;&lt;TCP_CA_Loss)
)brace
suffix:semicolon
DECL|struct|tcp_info
r_struct
id|tcp_info
(brace
DECL|member|tcpi_state
id|__u8
id|tcpi_state
suffix:semicolon
DECL|member|tcpi_ca_state
id|__u8
id|tcpi_ca_state
suffix:semicolon
DECL|member|tcpi_retransmits
id|__u8
id|tcpi_retransmits
suffix:semicolon
DECL|member|tcpi_probes
id|__u8
id|tcpi_probes
suffix:semicolon
DECL|member|tcpi_backoff
id|__u8
id|tcpi_backoff
suffix:semicolon
DECL|member|tcpi_options
id|__u8
id|tcpi_options
suffix:semicolon
DECL|member|tcpi_snd_wscale
DECL|member|tcpi_rcv_wscale
id|__u8
id|tcpi_snd_wscale
suffix:colon
l_int|4
comma
id|tcpi_rcv_wscale
suffix:colon
l_int|4
suffix:semicolon
DECL|member|tcpi_rto
id|__u32
id|tcpi_rto
suffix:semicolon
DECL|member|tcpi_ato
id|__u32
id|tcpi_ato
suffix:semicolon
DECL|member|tcpi_snd_mss
id|__u32
id|tcpi_snd_mss
suffix:semicolon
DECL|member|tcpi_rcv_mss
id|__u32
id|tcpi_rcv_mss
suffix:semicolon
DECL|member|tcpi_unacked
id|__u32
id|tcpi_unacked
suffix:semicolon
DECL|member|tcpi_sacked
id|__u32
id|tcpi_sacked
suffix:semicolon
DECL|member|tcpi_lost
id|__u32
id|tcpi_lost
suffix:semicolon
DECL|member|tcpi_retrans
id|__u32
id|tcpi_retrans
suffix:semicolon
DECL|member|tcpi_fackets
id|__u32
id|tcpi_fackets
suffix:semicolon
multiline_comment|/* Times. */
DECL|member|tcpi_last_data_sent
id|__u32
id|tcpi_last_data_sent
suffix:semicolon
DECL|member|tcpi_last_ack_sent
id|__u32
id|tcpi_last_ack_sent
suffix:semicolon
multiline_comment|/* Not remembered, sorry. */
DECL|member|tcpi_last_data_recv
id|__u32
id|tcpi_last_data_recv
suffix:semicolon
DECL|member|tcpi_last_ack_recv
id|__u32
id|tcpi_last_ack_recv
suffix:semicolon
multiline_comment|/* Metrics. */
DECL|member|tcpi_pmtu
id|__u32
id|tcpi_pmtu
suffix:semicolon
DECL|member|tcpi_rcv_ssthresh
id|__u32
id|tcpi_rcv_ssthresh
suffix:semicolon
DECL|member|tcpi_rtt
id|__u32
id|tcpi_rtt
suffix:semicolon
DECL|member|tcpi_rttvar
id|__u32
id|tcpi_rttvar
suffix:semicolon
DECL|member|tcpi_snd_ssthresh
id|__u32
id|tcpi_snd_ssthresh
suffix:semicolon
DECL|member|tcpi_snd_cwnd
id|__u32
id|tcpi_snd_cwnd
suffix:semicolon
DECL|member|tcpi_advmss
id|__u32
id|tcpi_advmss
suffix:semicolon
DECL|member|tcpi_reordering
id|__u32
id|tcpi_reordering
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* This defines a selective acknowledgement block. */
DECL|struct|tcp_sack_block
r_struct
id|tcp_sack_block
(brace
DECL|member|start_seq
id|__u32
id|start_seq
suffix:semicolon
DECL|member|end_seq
id|__u32
id|end_seq
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|tcp_opt
r_struct
id|tcp_opt
(brace
DECL|member|tcp_header_len
r_int
id|tcp_header_len
suffix:semicolon
multiline_comment|/* Bytes of tcp header to send&t;&t;*/
multiline_comment|/*&n; *&t;Header prediction flags&n; *&t;0x5?10 &lt;&lt; 16 + snd_wnd in net byte order&n; */
DECL|member|pred_flags
id|__u32
id|pred_flags
suffix:semicolon
multiline_comment|/*&n; *&t;RFC793 variables by their proper names. This means you can&n; *&t;read the code and the spec side by side (and laugh ...)&n; *&t;See RFC793 and RFC1122. The RFC writes these in capitals.&n; */
DECL|member|rcv_nxt
id|__u32
id|rcv_nxt
suffix:semicolon
multiline_comment|/* What we want to receive next &t;*/
DECL|member|snd_nxt
id|__u32
id|snd_nxt
suffix:semicolon
multiline_comment|/* Next sequence we send&t;&t;*/
DECL|member|snd_una
id|__u32
id|snd_una
suffix:semicolon
multiline_comment|/* First byte we want an ack for&t;*/
DECL|member|snd_sml
id|__u32
id|snd_sml
suffix:semicolon
multiline_comment|/* Last byte of the most recently transmitted small packet */
DECL|member|rcv_tstamp
id|__u32
id|rcv_tstamp
suffix:semicolon
multiline_comment|/* timestamp of last received ACK (for keepalives) */
DECL|member|lsndtime
id|__u32
id|lsndtime
suffix:semicolon
multiline_comment|/* timestamp of last sent data packet (for restart window) */
multiline_comment|/* Delayed ACK control data */
r_struct
(brace
DECL|member|pending
id|__u8
id|pending
suffix:semicolon
multiline_comment|/* ACK is pending */
DECL|member|quick
id|__u8
id|quick
suffix:semicolon
multiline_comment|/* Scheduled number of quick acks&t;*/
DECL|member|pingpong
id|__u8
id|pingpong
suffix:semicolon
multiline_comment|/* The session is interactive&t;&t;*/
DECL|member|blocked
id|__u8
id|blocked
suffix:semicolon
multiline_comment|/* Delayed ACK was blocked by socket lock*/
DECL|member|ato
id|__u32
id|ato
suffix:semicolon
multiline_comment|/* Predicted tick of soft clock&t;&t;*/
DECL|member|timeout
r_int
r_int
id|timeout
suffix:semicolon
multiline_comment|/* Currently scheduled timeout&t;&t;*/
DECL|member|lrcvtime
id|__u32
id|lrcvtime
suffix:semicolon
multiline_comment|/* timestamp of last received data packet*/
DECL|member|last_seg_size
id|__u16
id|last_seg_size
suffix:semicolon
multiline_comment|/* Size of last incoming segment&t;*/
DECL|member|rcv_mss
id|__u16
id|rcv_mss
suffix:semicolon
multiline_comment|/* MSS used for delayed ACK decisions&t;*/
DECL|member|ack
)brace
id|ack
suffix:semicolon
multiline_comment|/* Data for direct copy to user */
r_struct
(brace
DECL|member|prequeue
r_struct
id|sk_buff_head
id|prequeue
suffix:semicolon
DECL|member|task
r_struct
id|task_struct
op_star
id|task
suffix:semicolon
DECL|member|iov
r_struct
id|iovec
op_star
id|iov
suffix:semicolon
DECL|member|memory
r_int
id|memory
suffix:semicolon
DECL|member|len
r_int
id|len
suffix:semicolon
DECL|member|ucopy
)brace
id|ucopy
suffix:semicolon
DECL|member|snd_wl1
id|__u32
id|snd_wl1
suffix:semicolon
multiline_comment|/* Sequence for window update&t;&t;*/
DECL|member|snd_wnd
id|__u32
id|snd_wnd
suffix:semicolon
multiline_comment|/* The window we expect to receive&t;*/
DECL|member|max_window
id|__u32
id|max_window
suffix:semicolon
multiline_comment|/* Maximal window ever seen from peer&t;*/
DECL|member|pmtu_cookie
id|__u32
id|pmtu_cookie
suffix:semicolon
multiline_comment|/* Last pmtu seen by socket&t;&t;*/
DECL|member|mss_cache
id|__u16
id|mss_cache
suffix:semicolon
multiline_comment|/* Cached effective mss, not including SACKS */
DECL|member|mss_clamp
id|__u16
id|mss_clamp
suffix:semicolon
multiline_comment|/* Maximal mss, negotiated at connection setup */
DECL|member|ext_header_len
id|__u16
id|ext_header_len
suffix:semicolon
multiline_comment|/* Network protocol overhead (IP/IPv6 options) */
DECL|member|ca_state
id|__u8
id|ca_state
suffix:semicolon
multiline_comment|/* State of fast-retransmit machine &t;*/
DECL|member|retransmits
id|__u8
id|retransmits
suffix:semicolon
multiline_comment|/* Number of unrecovered RTO timeouts.&t;*/
DECL|member|reordering
id|__u8
id|reordering
suffix:semicolon
multiline_comment|/* Packet reordering metric.&t;&t;*/
DECL|member|queue_shrunk
id|__u8
id|queue_shrunk
suffix:semicolon
multiline_comment|/* Write queue has been shrunk recently.*/
DECL|member|defer_accept
id|__u8
id|defer_accept
suffix:semicolon
multiline_comment|/* User waits for some data after accept() */
multiline_comment|/* RTT measurement */
DECL|member|backoff
id|__u8
id|backoff
suffix:semicolon
multiline_comment|/* backoff&t;&t;&t;&t;*/
DECL|member|srtt
id|__u32
id|srtt
suffix:semicolon
multiline_comment|/* smothed round trip time &lt;&lt; 3&t;&t;*/
DECL|member|mdev
id|__u32
id|mdev
suffix:semicolon
multiline_comment|/* medium deviation&t;&t;&t;*/
DECL|member|mdev_max
id|__u32
id|mdev_max
suffix:semicolon
multiline_comment|/* maximal mdev for the last rtt period&t;*/
DECL|member|rttvar
id|__u32
id|rttvar
suffix:semicolon
multiline_comment|/* smoothed mdev_max&t;&t;&t;*/
DECL|member|rtt_seq
id|__u32
id|rtt_seq
suffix:semicolon
multiline_comment|/* sequence number to update rttvar&t;*/
DECL|member|rto
id|__u32
id|rto
suffix:semicolon
multiline_comment|/* retransmit timeout&t;&t;&t;*/
DECL|member|packets_out
id|__u32
id|packets_out
suffix:semicolon
multiline_comment|/* Packets which are &quot;in flight&quot;&t;*/
DECL|member|left_out
id|__u32
id|left_out
suffix:semicolon
multiline_comment|/* Packets which leaved network&t;&t;*/
DECL|member|retrans_out
id|__u32
id|retrans_out
suffix:semicolon
multiline_comment|/* Retransmitted packets out&t;&t;*/
multiline_comment|/*&n; *&t;Slow start and congestion control (see also Nagle, and Karn &amp; Partridge)&n; */
DECL|member|snd_ssthresh
id|__u32
id|snd_ssthresh
suffix:semicolon
multiline_comment|/* Slow start size threshold&t;&t;*/
DECL|member|snd_cwnd
id|__u32
id|snd_cwnd
suffix:semicolon
multiline_comment|/* Sending congestion window&t;&t;*/
DECL|member|snd_cwnd_cnt
id|__u16
id|snd_cwnd_cnt
suffix:semicolon
multiline_comment|/* Linear increase counter&t;&t;*/
DECL|member|snd_cwnd_clamp
id|__u16
id|snd_cwnd_clamp
suffix:semicolon
multiline_comment|/* Do not allow snd_cwnd to grow above this */
DECL|member|snd_cwnd_used
id|__u32
id|snd_cwnd_used
suffix:semicolon
DECL|member|snd_cwnd_stamp
id|__u32
id|snd_cwnd_stamp
suffix:semicolon
multiline_comment|/* Two commonly used timers in both sender and receiver paths. */
DECL|member|timeout
r_int
r_int
id|timeout
suffix:semicolon
DECL|member|retransmit_timer
r_struct
id|timer_list
id|retransmit_timer
suffix:semicolon
multiline_comment|/* Resend (no ack)&t;*/
DECL|member|delack_timer
r_struct
id|timer_list
id|delack_timer
suffix:semicolon
multiline_comment|/* Ack delay &t;&t;*/
DECL|member|out_of_order_queue
r_struct
id|sk_buff_head
id|out_of_order_queue
suffix:semicolon
multiline_comment|/* Out of order segments go here */
DECL|member|af_specific
r_struct
id|tcp_func
op_star
id|af_specific
suffix:semicolon
multiline_comment|/* Operations which are AF_INET{4,6} specific&t;*/
DECL|member|send_head
r_struct
id|sk_buff
op_star
id|send_head
suffix:semicolon
multiline_comment|/* Front of stuff to transmit&t;&t;&t;*/
DECL|member|sndmsg_page
r_struct
id|page
op_star
id|sndmsg_page
suffix:semicolon
multiline_comment|/* Cached page for sendmsg&t;&t;&t;*/
DECL|member|sndmsg_off
id|u32
id|sndmsg_off
suffix:semicolon
multiline_comment|/* Cached offset for sendmsg&t;&t;&t;*/
DECL|member|rcv_wnd
id|__u32
id|rcv_wnd
suffix:semicolon
multiline_comment|/* Current receiver window&t;&t;*/
DECL|member|rcv_wup
id|__u32
id|rcv_wup
suffix:semicolon
multiline_comment|/* rcv_nxt on last window update sent&t;*/
DECL|member|write_seq
id|__u32
id|write_seq
suffix:semicolon
multiline_comment|/* Tail(+1) of data held in tcp send buffer */
DECL|member|pushed_seq
id|__u32
id|pushed_seq
suffix:semicolon
multiline_comment|/* Last pushed seq, required to talk to windows */
DECL|member|copied_seq
id|__u32
id|copied_seq
suffix:semicolon
multiline_comment|/* Head of yet unread data&t;&t;*/
multiline_comment|/*&n; *      Options received (usually on last packet, some only on SYN packets).&n; */
DECL|member|tstamp_ok
r_char
id|tstamp_ok
comma
multiline_comment|/* TIMESTAMP seen on SYN packet&t;&t;*/
DECL|member|wscale_ok
id|wscale_ok
comma
multiline_comment|/* Wscale seen on SYN packet&t;&t;*/
DECL|member|sack_ok
id|sack_ok
suffix:semicolon
multiline_comment|/* SACK seen on SYN packet&t;&t;*/
DECL|member|saw_tstamp
r_char
id|saw_tstamp
suffix:semicolon
multiline_comment|/* Saw TIMESTAMP on last packet&t;&t;*/
DECL|member|snd_wscale
id|__u8
id|snd_wscale
suffix:semicolon
multiline_comment|/* Window scaling received from sender&t;*/
DECL|member|rcv_wscale
id|__u8
id|rcv_wscale
suffix:semicolon
multiline_comment|/* Window scaling to send to receiver&t;*/
DECL|member|nonagle
id|__u8
id|nonagle
suffix:semicolon
multiline_comment|/* Disable Nagle algorithm?             */
DECL|member|keepalive_probes
id|__u8
id|keepalive_probes
suffix:semicolon
multiline_comment|/* num of allowed keep alive probes&t;*/
multiline_comment|/*&t;PAWS/RTTM data&t;*/
DECL|member|rcv_tsval
id|__u32
id|rcv_tsval
suffix:semicolon
multiline_comment|/* Time stamp value             &t;*/
DECL|member|rcv_tsecr
id|__u32
id|rcv_tsecr
suffix:semicolon
multiline_comment|/* Time stamp echo reply        &t;*/
DECL|member|ts_recent
id|__u32
id|ts_recent
suffix:semicolon
multiline_comment|/* Time stamp to echo next&t;&t;*/
DECL|member|ts_recent_stamp
r_int
id|ts_recent_stamp
suffix:semicolon
multiline_comment|/* Time we stored ts_recent (for aging) */
multiline_comment|/*&t;SACKs data&t;*/
DECL|member|user_mss
id|__u16
id|user_mss
suffix:semicolon
multiline_comment|/* mss requested by user in ioctl */
DECL|member|dsack
id|__u8
id|dsack
suffix:semicolon
multiline_comment|/* D-SACK is scheduled&t;&t;&t;*/
DECL|member|eff_sacks
id|__u8
id|eff_sacks
suffix:semicolon
multiline_comment|/* Size of SACK array to send with next packet */
DECL|member|duplicate_sack
r_struct
id|tcp_sack_block
id|duplicate_sack
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* D-SACK block */
DECL|member|selective_acks
r_struct
id|tcp_sack_block
id|selective_acks
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* The SACKS themselves*/
DECL|member|window_clamp
id|__u32
id|window_clamp
suffix:semicolon
multiline_comment|/* Maximal window to advertise&t;&t;*/
DECL|member|rcv_ssthresh
id|__u32
id|rcv_ssthresh
suffix:semicolon
multiline_comment|/* Current window clamp&t;&t;&t;*/
DECL|member|probes_out
id|__u8
id|probes_out
suffix:semicolon
multiline_comment|/* unanswered 0 window probes&t;&t;*/
DECL|member|num_sacks
id|__u8
id|num_sacks
suffix:semicolon
multiline_comment|/* Number of SACK blocks&t;&t;*/
DECL|member|advmss
id|__u16
id|advmss
suffix:semicolon
multiline_comment|/* Advertised MSS&t;&t;&t;*/
DECL|member|syn_retries
id|__u8
id|syn_retries
suffix:semicolon
multiline_comment|/* num of allowed syn retries */
DECL|member|ecn_flags
id|__u8
id|ecn_flags
suffix:semicolon
multiline_comment|/* ECN status bits.&t;&t;&t;*/
DECL|member|prior_ssthresh
id|__u16
id|prior_ssthresh
suffix:semicolon
multiline_comment|/* ssthresh saved at recovery start&t;*/
DECL|member|lost_out
id|__u32
id|lost_out
suffix:semicolon
multiline_comment|/* Lost packets&t;&t;&t;&t;*/
DECL|member|sacked_out
id|__u32
id|sacked_out
suffix:semicolon
multiline_comment|/* SACK&squot;d packets&t;&t;&t;*/
DECL|member|fackets_out
id|__u32
id|fackets_out
suffix:semicolon
multiline_comment|/* FACK&squot;d packets&t;&t;&t;*/
DECL|member|high_seq
id|__u32
id|high_seq
suffix:semicolon
multiline_comment|/* snd_nxt at onset of congestion&t;*/
DECL|member|retrans_stamp
id|__u32
id|retrans_stamp
suffix:semicolon
multiline_comment|/* Timestamp of the last retransmit,&n;&t;&t;&t;&t; * also used in SYN-SENT to remember stamp of&n;&t;&t;&t;&t; * the first SYN. */
DECL|member|undo_marker
id|__u32
id|undo_marker
suffix:semicolon
multiline_comment|/* tracking retrans started here. */
DECL|member|undo_retrans
r_int
id|undo_retrans
suffix:semicolon
multiline_comment|/* number of undoable retransmissions. */
DECL|member|urg_seq
id|__u32
id|urg_seq
suffix:semicolon
multiline_comment|/* Seq of received urgent pointer */
DECL|member|urg_data
id|__u16
id|urg_data
suffix:semicolon
multiline_comment|/* Saved octet of OOB data and control flags */
DECL|member|pending
id|__u8
id|pending
suffix:semicolon
multiline_comment|/* Scheduled timer event&t;*/
DECL|member|urg_mode
id|__u8
id|urg_mode
suffix:semicolon
multiline_comment|/* In urgent mode&t;&t;*/
DECL|member|snd_up
id|__u32
id|snd_up
suffix:semicolon
multiline_comment|/* Urgent pointer&t;&t;*/
multiline_comment|/* The syn_wait_lock is necessary only to avoid tcp_get_info having&n;&t; * to grab the main lock sock while browsing the listening hash&n;&t; * (otherwise it&squot;s deadlock prone).&n;&t; * This lock is acquired in read mode only from tcp_get_info() and&n;&t; * it&squot;s acquired in write mode _only_ from code that is actively&n;&t; * changing the syn_wait_queue. All readers that are holding&n;&t; * the master sock lock don&squot;t need to grab this lock in read mode&n;&t; * too as the syn_wait_queue writes are always protected from&n;&t; * the main sock lock.&n;&t; */
DECL|member|syn_wait_lock
id|rwlock_t
id|syn_wait_lock
suffix:semicolon
DECL|member|listen_opt
r_struct
id|tcp_listen_opt
op_star
id|listen_opt
suffix:semicolon
multiline_comment|/* FIFO of established children */
DECL|member|accept_queue
r_struct
id|open_request
op_star
id|accept_queue
suffix:semicolon
DECL|member|accept_queue_tail
r_struct
id|open_request
op_star
id|accept_queue_tail
suffix:semicolon
DECL|member|write_pending
r_int
id|write_pending
suffix:semicolon
multiline_comment|/* A write to socket waits to start. */
DECL|member|keepalive_time
r_int
r_int
id|keepalive_time
suffix:semicolon
multiline_comment|/* time before keep alive takes place */
DECL|member|keepalive_intvl
r_int
r_int
id|keepalive_intvl
suffix:semicolon
multiline_comment|/* time interval between keep alive probes */
DECL|member|linger2
r_int
id|linger2
suffix:semicolon
DECL|member|last_synq_overflow
r_int
r_int
id|last_synq_overflow
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* WARNING: don&squot;t change the layout of the members in tcp_sock! */
DECL|struct|tcp_sock
r_struct
id|tcp_sock
(brace
DECL|member|sk
r_struct
id|sock
id|sk
suffix:semicolon
macro_line|#if defined(CONFIG_IPV6) || defined(CONFIG_IPV6_MODULE)
DECL|member|pinet6
r_struct
id|ipv6_pinfo
op_star
id|pinet6
suffix:semicolon
macro_line|#endif
DECL|member|inet
r_struct
id|inet_opt
id|inet
suffix:semicolon
DECL|member|tcp
r_struct
id|tcp_opt
id|tcp
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|tcp_sk
mdefine_line|#define tcp_sk(__sk) (&amp;((struct tcp_sock *)__sk)-&gt;tcp)
macro_line|#endif&t;/* _LINUX_TCP_H */
eof
