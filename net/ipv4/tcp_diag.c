multiline_comment|/*&n; * tcp_diag.c&t;Module for monitoring TCP sockets.&n; *&n; * Version:&t;$Id: tcp_diag.c,v 1.3 2002/02/01 22:01:04 davem Exp $&n; *&n; * Authors:&t;Alexey Kuznetsov, &lt;kuznet@ms2.inr.ac.ru&gt;&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *      modify it under the terms of the GNU General Public License&n; *      as published by the Free Software Foundation; either version&n; *      2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/random.h&gt;
macro_line|#include &lt;linux/cache.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;net/icmp.h&gt;
macro_line|#include &lt;net/tcp.h&gt;
macro_line|#include &lt;net/ipv6.h&gt;
macro_line|#include &lt;net/inet_common.h&gt;
macro_line|#include &lt;linux/inet.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/tcp_diag.h&gt;
DECL|variable|tcpnl
r_static
r_struct
id|sock
op_star
id|tcpnl
suffix:semicolon
DECL|macro|TCPDIAG_PUT
mdefine_line|#define TCPDIAG_PUT(skb, attrtype, attrlen) &bslash;&n;({ int rtalen = RTA_LENGTH(attrlen);        &bslash;&n;   struct rtattr *rta;                      &bslash;&n;   if (skb_tailroom(skb) &lt; RTA_ALIGN(rtalen)) goto nlmsg_failure; &bslash;&n;   rta = (void*)__skb_put(skb, RTA_ALIGN(rtalen)); &bslash;&n;   rta-&gt;rta_type = attrtype;                &bslash;&n;   rta-&gt;rta_len = rtalen;                   &bslash;&n;   RTA_DATA(rta); })
multiline_comment|/* Return information about state of tcp endpoint in API format. */
DECL|function|tcp_get_info
r_void
id|tcp_get_info
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_struct
id|tcp_info
op_star
id|info
)paren
(brace
r_struct
id|tcp_opt
op_star
id|tp
op_assign
id|tcp_sk
c_func
(paren
id|sk
)paren
suffix:semicolon
id|u32
id|now
op_assign
id|tcp_time_stamp
suffix:semicolon
id|memset
c_func
(paren
id|info
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|info
)paren
)paren
suffix:semicolon
id|info-&gt;tcpi_state
op_assign
id|sk-&gt;sk_state
suffix:semicolon
id|info-&gt;tcpi_ca_state
op_assign
id|tp-&gt;ca_state
suffix:semicolon
id|info-&gt;tcpi_retransmits
op_assign
id|tp-&gt;retransmits
suffix:semicolon
id|info-&gt;tcpi_probes
op_assign
id|tp-&gt;probes_out
suffix:semicolon
id|info-&gt;tcpi_backoff
op_assign
id|tp-&gt;backoff
suffix:semicolon
r_if
c_cond
(paren
id|tp-&gt;tstamp_ok
)paren
id|info-&gt;tcpi_options
op_or_assign
id|TCPI_OPT_TIMESTAMPS
suffix:semicolon
r_if
c_cond
(paren
id|tp-&gt;sack_ok
)paren
id|info-&gt;tcpi_options
op_or_assign
id|TCPI_OPT_SACK
suffix:semicolon
r_if
c_cond
(paren
id|tp-&gt;wscale_ok
)paren
(brace
id|info-&gt;tcpi_options
op_or_assign
id|TCPI_OPT_WSCALE
suffix:semicolon
id|info-&gt;tcpi_snd_wscale
op_assign
id|tp-&gt;snd_wscale
suffix:semicolon
id|info-&gt;tcpi_rcv_wscale
op_assign
id|tp-&gt;rcv_wscale
suffix:semicolon
)brace
r_if
c_cond
(paren
id|tp-&gt;ecn_flags
op_amp
id|TCP_ECN_OK
)paren
id|info-&gt;tcpi_options
op_or_assign
id|TCPI_OPT_ECN
suffix:semicolon
id|info-&gt;tcpi_rto
op_assign
id|jiffies_to_usecs
c_func
(paren
id|tp-&gt;rto
)paren
suffix:semicolon
id|info-&gt;tcpi_ato
op_assign
id|jiffies_to_usecs
c_func
(paren
id|tp-&gt;ack.ato
)paren
suffix:semicolon
id|info-&gt;tcpi_snd_mss
op_assign
id|tp-&gt;mss_cache_std
suffix:semicolon
id|info-&gt;tcpi_rcv_mss
op_assign
id|tp-&gt;ack.rcv_mss
suffix:semicolon
id|info-&gt;tcpi_unacked
op_assign
id|tcp_get_pcount
c_func
(paren
op_amp
id|tp-&gt;packets_out
)paren
suffix:semicolon
id|info-&gt;tcpi_sacked
op_assign
id|tcp_get_pcount
c_func
(paren
op_amp
id|tp-&gt;sacked_out
)paren
suffix:semicolon
id|info-&gt;tcpi_lost
op_assign
id|tcp_get_pcount
c_func
(paren
op_amp
id|tp-&gt;lost_out
)paren
suffix:semicolon
id|info-&gt;tcpi_retrans
op_assign
id|tcp_get_pcount
c_func
(paren
op_amp
id|tp-&gt;retrans_out
)paren
suffix:semicolon
id|info-&gt;tcpi_fackets
op_assign
id|tcp_get_pcount
c_func
(paren
op_amp
id|tp-&gt;fackets_out
)paren
suffix:semicolon
id|info-&gt;tcpi_last_data_sent
op_assign
id|jiffies_to_msecs
c_func
(paren
id|now
op_minus
id|tp-&gt;lsndtime
)paren
suffix:semicolon
id|info-&gt;tcpi_last_data_recv
op_assign
id|jiffies_to_msecs
c_func
(paren
id|now
op_minus
id|tp-&gt;ack.lrcvtime
)paren
suffix:semicolon
id|info-&gt;tcpi_last_ack_recv
op_assign
id|jiffies_to_msecs
c_func
(paren
id|now
op_minus
id|tp-&gt;rcv_tstamp
)paren
suffix:semicolon
id|info-&gt;tcpi_pmtu
op_assign
id|tp-&gt;pmtu_cookie
suffix:semicolon
id|info-&gt;tcpi_rcv_ssthresh
op_assign
id|tp-&gt;rcv_ssthresh
suffix:semicolon
id|info-&gt;tcpi_rtt
op_assign
id|jiffies_to_usecs
c_func
(paren
id|tp-&gt;srtt
)paren
op_rshift
l_int|3
suffix:semicolon
id|info-&gt;tcpi_rttvar
op_assign
id|jiffies_to_usecs
c_func
(paren
id|tp-&gt;mdev
)paren
op_rshift
l_int|2
suffix:semicolon
id|info-&gt;tcpi_snd_ssthresh
op_assign
id|tp-&gt;snd_ssthresh
suffix:semicolon
id|info-&gt;tcpi_snd_cwnd
op_assign
id|tp-&gt;snd_cwnd
suffix:semicolon
id|info-&gt;tcpi_advmss
op_assign
id|tp-&gt;advmss
suffix:semicolon
id|info-&gt;tcpi_reordering
op_assign
id|tp-&gt;reordering
suffix:semicolon
id|info-&gt;tcpi_rcv_rtt
op_assign
id|jiffies_to_usecs
c_func
(paren
id|tp-&gt;rcv_rtt_est.rtt
)paren
op_rshift
l_int|3
suffix:semicolon
id|info-&gt;tcpi_rcv_space
op_assign
id|tp-&gt;rcvq_space.space
suffix:semicolon
)brace
DECL|function|tcpdiag_fill
r_static
r_int
id|tcpdiag_fill
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|sock
op_star
id|sk
comma
r_int
id|ext
comma
id|u32
id|pid
comma
id|u32
id|seq
)paren
(brace
r_struct
id|inet_opt
op_star
id|inet
op_assign
id|inet_sk
c_func
(paren
id|sk
)paren
suffix:semicolon
r_struct
id|tcp_opt
op_star
id|tp
op_assign
id|tcp_sk
c_func
(paren
id|sk
)paren
suffix:semicolon
r_struct
id|tcpdiagmsg
op_star
id|r
suffix:semicolon
r_struct
id|nlmsghdr
op_star
id|nlh
suffix:semicolon
r_struct
id|tcp_info
op_star
id|info
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|tcpdiag_meminfo
op_star
id|minfo
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|tcpvegas_info
op_star
id|vinfo
op_assign
l_int|NULL
suffix:semicolon
r_int
r_char
op_star
id|b
op_assign
id|skb-&gt;tail
suffix:semicolon
id|nlh
op_assign
id|NLMSG_PUT
c_func
(paren
id|skb
comma
id|pid
comma
id|seq
comma
id|TCPDIAG_GETSOCK
comma
r_sizeof
(paren
op_star
id|r
)paren
)paren
suffix:semicolon
id|r
op_assign
id|NLMSG_DATA
c_func
(paren
id|nlh
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sk-&gt;sk_state
op_ne
id|TCP_TIME_WAIT
)paren
(brace
r_if
c_cond
(paren
id|ext
op_amp
(paren
l_int|1
op_lshift
(paren
id|TCPDIAG_MEMINFO
op_minus
l_int|1
)paren
)paren
)paren
id|minfo
op_assign
id|TCPDIAG_PUT
c_func
(paren
id|skb
comma
id|TCPDIAG_MEMINFO
comma
r_sizeof
(paren
op_star
id|minfo
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ext
op_amp
(paren
l_int|1
op_lshift
(paren
id|TCPDIAG_INFO
op_minus
l_int|1
)paren
)paren
)paren
id|info
op_assign
id|TCPDIAG_PUT
c_func
(paren
id|skb
comma
id|TCPDIAG_INFO
comma
r_sizeof
(paren
op_star
id|info
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|tcp_is_westwood
c_func
(paren
id|tp
)paren
op_logical_or
id|tcp_is_vegas
c_func
(paren
id|tp
)paren
)paren
op_logical_and
(paren
id|ext
op_amp
(paren
l_int|1
op_lshift
(paren
id|TCPDIAG_VEGASINFO
op_minus
l_int|1
)paren
)paren
)paren
)paren
id|vinfo
op_assign
id|TCPDIAG_PUT
c_func
(paren
id|skb
comma
id|TCPDIAG_VEGASINFO
comma
r_sizeof
(paren
op_star
id|vinfo
)paren
)paren
suffix:semicolon
)brace
id|r-&gt;tcpdiag_family
op_assign
id|sk-&gt;sk_family
suffix:semicolon
id|r-&gt;tcpdiag_state
op_assign
id|sk-&gt;sk_state
suffix:semicolon
id|r-&gt;tcpdiag_timer
op_assign
l_int|0
suffix:semicolon
id|r-&gt;tcpdiag_retrans
op_assign
l_int|0
suffix:semicolon
id|r-&gt;id.tcpdiag_if
op_assign
id|sk-&gt;sk_bound_dev_if
suffix:semicolon
id|r-&gt;id.tcpdiag_cookie
(braket
l_int|0
)braket
op_assign
(paren
id|u32
)paren
(paren
r_int
r_int
)paren
id|sk
suffix:semicolon
id|r-&gt;id.tcpdiag_cookie
(braket
l_int|1
)braket
op_assign
(paren
id|u32
)paren
(paren
(paren
(paren
r_int
r_int
)paren
id|sk
op_rshift
l_int|31
)paren
op_rshift
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r-&gt;tcpdiag_state
op_eq
id|TCP_TIME_WAIT
)paren
(brace
r_struct
id|tcp_tw_bucket
op_star
id|tw
op_assign
(paren
r_struct
id|tcp_tw_bucket
op_star
)paren
id|sk
suffix:semicolon
r_int
id|tmo
op_assign
id|tw-&gt;tw_ttd
op_minus
id|jiffies
suffix:semicolon
r_if
c_cond
(paren
id|tmo
OL
l_int|0
)paren
id|tmo
op_assign
l_int|0
suffix:semicolon
id|r-&gt;id.tcpdiag_sport
op_assign
id|tw-&gt;tw_sport
suffix:semicolon
id|r-&gt;id.tcpdiag_dport
op_assign
id|tw-&gt;tw_dport
suffix:semicolon
id|r-&gt;id.tcpdiag_src
(braket
l_int|0
)braket
op_assign
id|tw-&gt;tw_rcv_saddr
suffix:semicolon
id|r-&gt;id.tcpdiag_dst
(braket
l_int|0
)braket
op_assign
id|tw-&gt;tw_daddr
suffix:semicolon
id|r-&gt;tcpdiag_state
op_assign
id|tw-&gt;tw_substate
suffix:semicolon
id|r-&gt;tcpdiag_timer
op_assign
l_int|3
suffix:semicolon
id|r-&gt;tcpdiag_expires
op_assign
(paren
id|tmo
op_star
l_int|1000
op_plus
id|HZ
op_minus
l_int|1
)paren
op_div
id|HZ
suffix:semicolon
id|r-&gt;tcpdiag_rqueue
op_assign
l_int|0
suffix:semicolon
id|r-&gt;tcpdiag_wqueue
op_assign
l_int|0
suffix:semicolon
id|r-&gt;tcpdiag_uid
op_assign
l_int|0
suffix:semicolon
id|r-&gt;tcpdiag_inode
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef CONFIG_IPV6
r_if
c_cond
(paren
id|r-&gt;tcpdiag_family
op_eq
id|AF_INET6
)paren
(brace
id|ipv6_addr_copy
c_func
(paren
(paren
r_struct
id|in6_addr
op_star
)paren
id|r-&gt;id.tcpdiag_src
comma
op_amp
id|tw-&gt;tw_v6_rcv_saddr
)paren
suffix:semicolon
id|ipv6_addr_copy
c_func
(paren
(paren
r_struct
id|in6_addr
op_star
)paren
id|r-&gt;id.tcpdiag_dst
comma
op_amp
id|tw-&gt;tw_v6_daddr
)paren
suffix:semicolon
)brace
macro_line|#endif
id|nlh-&gt;nlmsg_len
op_assign
id|skb-&gt;tail
op_minus
id|b
suffix:semicolon
r_return
id|skb-&gt;len
suffix:semicolon
)brace
id|r-&gt;id.tcpdiag_sport
op_assign
id|inet-&gt;sport
suffix:semicolon
id|r-&gt;id.tcpdiag_dport
op_assign
id|inet-&gt;dport
suffix:semicolon
id|r-&gt;id.tcpdiag_src
(braket
l_int|0
)braket
op_assign
id|inet-&gt;rcv_saddr
suffix:semicolon
id|r-&gt;id.tcpdiag_dst
(braket
l_int|0
)braket
op_assign
id|inet-&gt;daddr
suffix:semicolon
macro_line|#ifdef CONFIG_IPV6
r_if
c_cond
(paren
id|r-&gt;tcpdiag_family
op_eq
id|AF_INET6
)paren
(brace
r_struct
id|ipv6_pinfo
op_star
id|np
op_assign
id|inet6_sk
c_func
(paren
id|sk
)paren
suffix:semicolon
id|ipv6_addr_copy
c_func
(paren
(paren
r_struct
id|in6_addr
op_star
)paren
id|r-&gt;id.tcpdiag_src
comma
op_amp
id|np-&gt;rcv_saddr
)paren
suffix:semicolon
id|ipv6_addr_copy
c_func
(paren
(paren
r_struct
id|in6_addr
op_star
)paren
id|r-&gt;id.tcpdiag_dst
comma
op_amp
id|np-&gt;daddr
)paren
suffix:semicolon
)brace
macro_line|#endif
DECL|macro|EXPIRES_IN_MS
mdefine_line|#define EXPIRES_IN_MS(tmo)  ((tmo-jiffies)*1000+HZ-1)/HZ
r_if
c_cond
(paren
id|tp-&gt;pending
op_eq
id|TCP_TIME_RETRANS
)paren
(brace
id|r-&gt;tcpdiag_timer
op_assign
l_int|1
suffix:semicolon
id|r-&gt;tcpdiag_retrans
op_assign
id|tp-&gt;retransmits
suffix:semicolon
id|r-&gt;tcpdiag_expires
op_assign
id|EXPIRES_IN_MS
c_func
(paren
id|tp-&gt;timeout
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|tp-&gt;pending
op_eq
id|TCP_TIME_PROBE0
)paren
(brace
id|r-&gt;tcpdiag_timer
op_assign
l_int|4
suffix:semicolon
id|r-&gt;tcpdiag_retrans
op_assign
id|tp-&gt;probes_out
suffix:semicolon
id|r-&gt;tcpdiag_expires
op_assign
id|EXPIRES_IN_MS
c_func
(paren
id|tp-&gt;timeout
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|timer_pending
c_func
(paren
op_amp
id|sk-&gt;sk_timer
)paren
)paren
(brace
id|r-&gt;tcpdiag_timer
op_assign
l_int|2
suffix:semicolon
id|r-&gt;tcpdiag_retrans
op_assign
id|tp-&gt;probes_out
suffix:semicolon
id|r-&gt;tcpdiag_expires
op_assign
id|EXPIRES_IN_MS
c_func
(paren
id|sk-&gt;sk_timer.expires
)paren
suffix:semicolon
)brace
r_else
(brace
id|r-&gt;tcpdiag_timer
op_assign
l_int|0
suffix:semicolon
id|r-&gt;tcpdiag_expires
op_assign
l_int|0
suffix:semicolon
)brace
DECL|macro|EXPIRES_IN_MS
macro_line|#undef EXPIRES_IN_MS
id|r-&gt;tcpdiag_rqueue
op_assign
id|tp-&gt;rcv_nxt
op_minus
id|tp-&gt;copied_seq
suffix:semicolon
id|r-&gt;tcpdiag_wqueue
op_assign
id|tp-&gt;write_seq
op_minus
id|tp-&gt;snd_una
suffix:semicolon
id|r-&gt;tcpdiag_uid
op_assign
id|sock_i_uid
c_func
(paren
id|sk
)paren
suffix:semicolon
id|r-&gt;tcpdiag_inode
op_assign
id|sock_i_ino
c_func
(paren
id|sk
)paren
suffix:semicolon
r_if
c_cond
(paren
id|minfo
)paren
(brace
id|minfo-&gt;tcpdiag_rmem
op_assign
id|atomic_read
c_func
(paren
op_amp
id|sk-&gt;sk_rmem_alloc
)paren
suffix:semicolon
id|minfo-&gt;tcpdiag_wmem
op_assign
id|sk-&gt;sk_wmem_queued
suffix:semicolon
id|minfo-&gt;tcpdiag_fmem
op_assign
id|sk-&gt;sk_forward_alloc
suffix:semicolon
id|minfo-&gt;tcpdiag_tmem
op_assign
id|atomic_read
c_func
(paren
op_amp
id|sk-&gt;sk_wmem_alloc
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|info
)paren
id|tcp_get_info
c_func
(paren
id|sk
comma
id|info
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vinfo
)paren
(brace
r_if
c_cond
(paren
id|tcp_is_vegas
c_func
(paren
id|tp
)paren
)paren
(brace
id|vinfo-&gt;tcpv_enabled
op_assign
id|tp-&gt;vegas.doing_vegas_now
suffix:semicolon
id|vinfo-&gt;tcpv_rttcnt
op_assign
id|tp-&gt;vegas.cntRTT
suffix:semicolon
id|vinfo-&gt;tcpv_rtt
op_assign
id|jiffies_to_usecs
c_func
(paren
id|tp-&gt;vegas.baseRTT
)paren
suffix:semicolon
id|vinfo-&gt;tcpv_minrtt
op_assign
id|jiffies_to_usecs
c_func
(paren
id|tp-&gt;vegas.minRTT
)paren
suffix:semicolon
)brace
r_else
(brace
id|vinfo-&gt;tcpv_enabled
op_assign
l_int|0
suffix:semicolon
id|vinfo-&gt;tcpv_rttcnt
op_assign
l_int|0
suffix:semicolon
id|vinfo-&gt;tcpv_rtt
op_assign
id|jiffies_to_usecs
c_func
(paren
id|tp-&gt;westwood.rtt
)paren
suffix:semicolon
id|vinfo-&gt;tcpv_minrtt
op_assign
id|jiffies_to_usecs
c_func
(paren
id|tp-&gt;westwood.rtt_min
)paren
suffix:semicolon
)brace
)brace
id|nlh-&gt;nlmsg_len
op_assign
id|skb-&gt;tail
op_minus
id|b
suffix:semicolon
r_return
id|skb-&gt;len
suffix:semicolon
id|nlmsg_failure
suffix:colon
id|skb_trim
c_func
(paren
id|skb
comma
id|b
op_minus
id|skb-&gt;data
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_extern
r_struct
id|sock
op_star
id|tcp_v4_lookup
c_func
(paren
id|u32
id|saddr
comma
id|u16
id|sport
comma
id|u32
id|daddr
comma
id|u16
id|dport
comma
r_int
id|dif
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_IPV6
r_extern
r_struct
id|sock
op_star
id|tcp_v6_lookup
c_func
(paren
r_struct
id|in6_addr
op_star
id|saddr
comma
id|u16
id|sport
comma
r_struct
id|in6_addr
op_star
id|daddr
comma
id|u16
id|dport
comma
r_int
id|dif
)paren
suffix:semicolon
macro_line|#endif
DECL|function|tcpdiag_get_exact
r_static
r_int
id|tcpdiag_get_exact
c_func
(paren
r_struct
id|sk_buff
op_star
id|in_skb
comma
r_const
r_struct
id|nlmsghdr
op_star
id|nlh
)paren
(brace
r_int
id|err
suffix:semicolon
r_struct
id|sock
op_star
id|sk
suffix:semicolon
r_struct
id|tcpdiagreq
op_star
id|req
op_assign
id|NLMSG_DATA
c_func
(paren
id|nlh
)paren
suffix:semicolon
r_struct
id|sk_buff
op_star
id|rep
suffix:semicolon
r_if
c_cond
(paren
id|req-&gt;tcpdiag_family
op_eq
id|AF_INET
)paren
(brace
id|sk
op_assign
id|tcp_v4_lookup
c_func
(paren
id|req-&gt;id.tcpdiag_dst
(braket
l_int|0
)braket
comma
id|req-&gt;id.tcpdiag_dport
comma
id|req-&gt;id.tcpdiag_src
(braket
l_int|0
)braket
comma
id|req-&gt;id.tcpdiag_sport
comma
id|req-&gt;id.tcpdiag_if
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_IPV6
r_else
r_if
c_cond
(paren
id|req-&gt;tcpdiag_family
op_eq
id|AF_INET6
)paren
(brace
id|sk
op_assign
id|tcp_v6_lookup
c_func
(paren
(paren
r_struct
id|in6_addr
op_star
)paren
id|req-&gt;id.tcpdiag_dst
comma
id|req-&gt;id.tcpdiag_dport
comma
(paren
r_struct
id|in6_addr
op_star
)paren
id|req-&gt;id.tcpdiag_src
comma
id|req-&gt;id.tcpdiag_sport
comma
id|req-&gt;id.tcpdiag_if
)paren
suffix:semicolon
)brace
macro_line|#endif
r_else
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sk
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOENT
suffix:semicolon
id|err
op_assign
op_minus
id|ESTALE
suffix:semicolon
r_if
c_cond
(paren
(paren
id|req-&gt;id.tcpdiag_cookie
(braket
l_int|0
)braket
op_ne
id|TCPDIAG_NOCOOKIE
op_logical_or
id|req-&gt;id.tcpdiag_cookie
(braket
l_int|1
)braket
op_ne
id|TCPDIAG_NOCOOKIE
)paren
op_logical_and
(paren
(paren
id|u32
)paren
(paren
r_int
r_int
)paren
id|sk
op_ne
id|req-&gt;id.tcpdiag_cookie
(braket
l_int|0
)braket
op_logical_or
(paren
id|u32
)paren
(paren
(paren
(paren
(paren
r_int
r_int
)paren
id|sk
)paren
op_rshift
l_int|31
)paren
op_rshift
l_int|1
)paren
op_ne
id|req-&gt;id.tcpdiag_cookie
(braket
l_int|1
)braket
)paren
)paren
r_goto
id|out
suffix:semicolon
id|err
op_assign
op_minus
id|ENOMEM
suffix:semicolon
id|rep
op_assign
id|alloc_skb
c_func
(paren
id|NLMSG_SPACE
c_func
(paren
r_sizeof
(paren
r_struct
id|tcpdiagmsg
)paren
op_plus
r_sizeof
(paren
r_struct
id|tcpdiag_meminfo
)paren
op_plus
r_sizeof
(paren
r_struct
id|tcp_info
)paren
op_plus
l_int|64
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rep
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|tcpdiag_fill
c_func
(paren
id|rep
comma
id|sk
comma
id|req-&gt;tcpdiag_ext
comma
id|NETLINK_CB
c_func
(paren
id|in_skb
)paren
dot
id|pid
comma
id|nlh-&gt;nlmsg_seq
)paren
op_le
l_int|0
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|err
op_assign
id|netlink_unicast
c_func
(paren
id|tcpnl
comma
id|rep
comma
id|NETLINK_CB
c_func
(paren
id|in_skb
)paren
dot
id|pid
comma
id|MSG_DONTWAIT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OG
l_int|0
)paren
id|err
op_assign
l_int|0
suffix:semicolon
id|out
suffix:colon
r_if
c_cond
(paren
id|sk
)paren
(brace
r_if
c_cond
(paren
id|sk-&gt;sk_state
op_eq
id|TCP_TIME_WAIT
)paren
id|tcp_tw_put
c_func
(paren
(paren
r_struct
id|tcp_tw_bucket
op_star
)paren
id|sk
)paren
suffix:semicolon
r_else
id|sock_put
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
r_return
id|err
suffix:semicolon
)brace
DECL|function|bitstring_match
r_static
r_int
id|bitstring_match
c_func
(paren
r_const
id|u32
op_star
id|a1
comma
r_const
id|u32
op_star
id|a2
comma
r_int
id|bits
)paren
(brace
r_int
id|words
op_assign
id|bits
op_rshift
l_int|5
suffix:semicolon
id|bits
op_and_assign
l_int|0x1f
suffix:semicolon
r_if
c_cond
(paren
id|words
)paren
(brace
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|a1
comma
id|a2
comma
id|words
op_lshift
l_int|2
)paren
)paren
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|bits
)paren
(brace
id|__u32
id|w1
comma
id|w2
suffix:semicolon
id|__u32
id|mask
suffix:semicolon
id|w1
op_assign
id|a1
(braket
id|words
)braket
suffix:semicolon
id|w2
op_assign
id|a2
(braket
id|words
)braket
suffix:semicolon
id|mask
op_assign
id|htonl
c_func
(paren
(paren
l_int|0xffffffff
)paren
op_lshift
(paren
l_int|32
op_minus
id|bits
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|w1
op_xor
id|w2
)paren
op_amp
id|mask
)paren
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|tcpdiag_bc_run
r_static
r_int
id|tcpdiag_bc_run
c_func
(paren
r_const
r_void
op_star
id|bc
comma
r_int
id|len
comma
r_struct
id|sock
op_star
id|sk
)paren
(brace
r_while
c_loop
(paren
id|len
OG
l_int|0
)paren
(brace
r_int
id|yes
op_assign
l_int|1
suffix:semicolon
r_struct
id|inet_opt
op_star
id|inet
op_assign
id|inet_sk
c_func
(paren
id|sk
)paren
suffix:semicolon
r_const
r_struct
id|tcpdiag_bc_op
op_star
id|op
op_assign
id|bc
suffix:semicolon
r_switch
c_cond
(paren
id|op-&gt;code
)paren
(brace
r_case
id|TCPDIAG_BC_NOP
suffix:colon
r_break
suffix:semicolon
r_case
id|TCPDIAG_BC_JMP
suffix:colon
id|yes
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|TCPDIAG_BC_S_GE
suffix:colon
id|yes
op_assign
id|inet-&gt;num
op_ge
id|op
(braket
l_int|1
)braket
dot
id|no
suffix:semicolon
r_break
suffix:semicolon
r_case
id|TCPDIAG_BC_S_LE
suffix:colon
id|yes
op_assign
id|inet-&gt;num
op_le
id|op
(braket
l_int|1
)braket
dot
id|no
suffix:semicolon
r_break
suffix:semicolon
r_case
id|TCPDIAG_BC_D_GE
suffix:colon
id|yes
op_assign
id|ntohs
c_func
(paren
id|inet-&gt;dport
)paren
op_ge
id|op
(braket
l_int|1
)braket
dot
id|no
suffix:semicolon
r_break
suffix:semicolon
r_case
id|TCPDIAG_BC_D_LE
suffix:colon
id|yes
op_assign
id|ntohs
c_func
(paren
id|inet-&gt;dport
)paren
op_le
id|op
(braket
l_int|1
)braket
dot
id|no
suffix:semicolon
r_break
suffix:semicolon
r_case
id|TCPDIAG_BC_AUTO
suffix:colon
id|yes
op_assign
op_logical_neg
(paren
id|sk-&gt;sk_userlocks
op_amp
id|SOCK_BINDPORT_LOCK
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|TCPDIAG_BC_S_COND
suffix:colon
r_case
id|TCPDIAG_BC_D_COND
suffix:colon
(brace
r_struct
id|tcpdiag_hostcond
op_star
id|cond
op_assign
(paren
r_struct
id|tcpdiag_hostcond
op_star
)paren
(paren
id|op
op_plus
l_int|1
)paren
suffix:semicolon
id|u32
op_star
id|addr
suffix:semicolon
r_if
c_cond
(paren
id|cond-&gt;port
op_ne
op_minus
l_int|1
op_logical_and
id|cond-&gt;port
op_ne
(paren
id|op-&gt;code
op_eq
id|TCPDIAG_BC_S_COND
ques
c_cond
id|inet-&gt;num
suffix:colon
id|ntohs
c_func
(paren
id|inet-&gt;dport
)paren
)paren
)paren
(brace
id|yes
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cond-&gt;prefix_len
op_eq
l_int|0
)paren
r_break
suffix:semicolon
macro_line|#ifdef CONFIG_IPV6
r_if
c_cond
(paren
id|sk-&gt;sk_family
op_eq
id|AF_INET6
)paren
(brace
r_struct
id|ipv6_pinfo
op_star
id|np
op_assign
id|inet6_sk
c_func
(paren
id|sk
)paren
suffix:semicolon
r_if
c_cond
(paren
id|op-&gt;code
op_eq
id|TCPDIAG_BC_S_COND
)paren
id|addr
op_assign
(paren
id|u32
op_star
)paren
op_amp
id|np-&gt;rcv_saddr
suffix:semicolon
r_else
id|addr
op_assign
(paren
id|u32
op_star
)paren
op_amp
id|np-&gt;daddr
suffix:semicolon
)brace
r_else
macro_line|#endif
(brace
r_if
c_cond
(paren
id|op-&gt;code
op_eq
id|TCPDIAG_BC_S_COND
)paren
id|addr
op_assign
op_amp
id|inet-&gt;rcv_saddr
suffix:semicolon
r_else
id|addr
op_assign
op_amp
id|inet-&gt;daddr
suffix:semicolon
)brace
r_if
c_cond
(paren
id|bitstring_match
c_func
(paren
id|addr
comma
id|cond-&gt;addr
comma
id|cond-&gt;prefix_len
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|sk-&gt;sk_family
op_eq
id|AF_INET6
op_logical_and
id|cond-&gt;family
op_eq
id|AF_INET
)paren
(brace
r_if
c_cond
(paren
id|addr
(braket
l_int|0
)braket
op_eq
l_int|0
op_logical_and
id|addr
(braket
l_int|1
)braket
op_eq
l_int|0
op_logical_and
id|addr
(braket
l_int|2
)braket
op_eq
id|htonl
c_func
(paren
l_int|0xffff
)paren
op_logical_and
id|bitstring_match
c_func
(paren
id|addr
op_plus
l_int|3
comma
id|cond-&gt;addr
comma
id|cond-&gt;prefix_len
)paren
)paren
r_break
suffix:semicolon
)brace
id|yes
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|yes
)paren
(brace
id|len
op_sub_assign
id|op-&gt;yes
suffix:semicolon
id|bc
op_add_assign
id|op-&gt;yes
suffix:semicolon
)brace
r_else
(brace
id|len
op_sub_assign
id|op-&gt;no
suffix:semicolon
id|bc
op_add_assign
id|op-&gt;no
suffix:semicolon
)brace
)brace
r_return
(paren
id|len
op_eq
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|valid_cc
r_static
r_int
id|valid_cc
c_func
(paren
r_const
r_void
op_star
id|bc
comma
r_int
id|len
comma
r_int
id|cc
)paren
(brace
r_while
c_loop
(paren
id|len
op_ge
l_int|0
)paren
(brace
r_const
r_struct
id|tcpdiag_bc_op
op_star
id|op
op_assign
id|bc
suffix:semicolon
r_if
c_cond
(paren
id|cc
OG
id|len
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|cc
op_eq
id|len
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|op-&gt;yes
OL
l_int|4
)paren
r_return
l_int|0
suffix:semicolon
id|len
op_sub_assign
id|op-&gt;yes
suffix:semicolon
id|bc
op_add_assign
id|op-&gt;yes
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|tcpdiag_bc_audit
r_static
r_int
id|tcpdiag_bc_audit
c_func
(paren
r_const
r_void
op_star
id|bytecode
comma
r_int
id|bytecode_len
)paren
(brace
r_const
r_int
r_char
op_star
id|bc
op_assign
id|bytecode
suffix:semicolon
r_int
id|len
op_assign
id|bytecode_len
suffix:semicolon
r_while
c_loop
(paren
id|len
OG
l_int|0
)paren
(brace
r_struct
id|tcpdiag_bc_op
op_star
id|op
op_assign
(paren
r_struct
id|tcpdiag_bc_op
op_star
)paren
id|bc
suffix:semicolon
singleline_comment|//printk(&quot;BC: %d %d %d {%d} / %d&bslash;n&quot;, op-&gt;code, op-&gt;yes, op-&gt;no, op[1].no, len);
r_switch
c_cond
(paren
id|op-&gt;code
)paren
(brace
r_case
id|TCPDIAG_BC_AUTO
suffix:colon
r_case
id|TCPDIAG_BC_S_COND
suffix:colon
r_case
id|TCPDIAG_BC_D_COND
suffix:colon
r_case
id|TCPDIAG_BC_S_GE
suffix:colon
r_case
id|TCPDIAG_BC_S_LE
suffix:colon
r_case
id|TCPDIAG_BC_D_GE
suffix:colon
r_case
id|TCPDIAG_BC_D_LE
suffix:colon
r_if
c_cond
(paren
id|op-&gt;yes
template_param
id|len
op_plus
l_int|4
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_case
id|TCPDIAG_BC_JMP
suffix:colon
r_if
c_cond
(paren
id|op-&gt;no
template_param
id|len
op_plus
l_int|4
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|op-&gt;no
OL
id|len
op_logical_and
op_logical_neg
id|valid_cc
c_func
(paren
id|bytecode
comma
id|bytecode_len
comma
id|len
op_minus
id|op-&gt;no
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
r_case
id|TCPDIAG_BC_NOP
suffix:colon
r_if
c_cond
(paren
id|op-&gt;yes
template_param
id|len
op_plus
l_int|4
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|bc
op_add_assign
id|op-&gt;yes
suffix:semicolon
id|len
op_sub_assign
id|op-&gt;yes
suffix:semicolon
)brace
r_return
id|len
op_eq
l_int|0
ques
c_cond
l_int|0
suffix:colon
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|tcpdiag_dump
r_static
r_int
id|tcpdiag_dump
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|netlink_callback
op_star
id|cb
)paren
(brace
r_int
id|i
comma
id|num
suffix:semicolon
r_int
id|s_i
comma
id|s_num
suffix:semicolon
r_struct
id|tcpdiagreq
op_star
id|r
op_assign
id|NLMSG_DATA
c_func
(paren
id|cb-&gt;nlh
)paren
suffix:semicolon
r_struct
id|rtattr
op_star
id|bc
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|cb-&gt;nlh-&gt;nlmsg_len
OG
l_int|4
op_plus
id|NLMSG_SPACE
c_func
(paren
r_sizeof
(paren
r_struct
id|tcpdiagreq
)paren
)paren
)paren
id|bc
op_assign
(paren
r_struct
id|rtattr
op_star
)paren
(paren
id|r
op_plus
l_int|1
)paren
suffix:semicolon
id|s_i
op_assign
id|cb-&gt;args
(braket
l_int|1
)braket
suffix:semicolon
id|s_num
op_assign
id|num
op_assign
id|cb-&gt;args
(braket
l_int|2
)braket
suffix:semicolon
r_if
c_cond
(paren
id|cb-&gt;args
(braket
l_int|0
)braket
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|r-&gt;tcpdiag_states
op_amp
(paren
id|TCPF_LISTEN
op_or
id|TCPF_SYN_RECV
)paren
)paren
)paren
r_goto
id|skip_listen_ht
suffix:semicolon
id|tcp_listen_lock
c_func
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|s_i
suffix:semicolon
id|i
OL
id|TCP_LHTABLE_SIZE
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|sock
op_star
id|sk
suffix:semicolon
r_struct
id|hlist_node
op_star
id|node
suffix:semicolon
r_if
c_cond
(paren
id|i
OG
id|s_i
)paren
id|s_num
op_assign
l_int|0
suffix:semicolon
id|num
op_assign
l_int|0
suffix:semicolon
id|sk_for_each
c_func
(paren
id|sk
comma
id|node
comma
op_amp
id|tcp_listening_hash
(braket
id|i
)braket
)paren
(brace
r_struct
id|inet_opt
op_star
id|inet
op_assign
id|inet_sk
c_func
(paren
id|sk
)paren
suffix:semicolon
r_if
c_cond
(paren
id|num
OL
id|s_num
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|r-&gt;tcpdiag_states
op_amp
id|TCPF_LISTEN
)paren
op_logical_or
id|r-&gt;id.tcpdiag_dport
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|r-&gt;id.tcpdiag_sport
op_ne
id|inet-&gt;sport
op_logical_and
id|r-&gt;id.tcpdiag_sport
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|bc
op_logical_and
op_logical_neg
id|tcpdiag_bc_run
c_func
(paren
id|RTA_DATA
c_func
(paren
id|bc
)paren
comma
id|RTA_PAYLOAD
c_func
(paren
id|bc
)paren
comma
id|sk
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|tcpdiag_fill
c_func
(paren
id|skb
comma
id|sk
comma
id|r-&gt;tcpdiag_ext
comma
id|NETLINK_CB
c_func
(paren
id|cb-&gt;skb
)paren
dot
id|pid
comma
id|cb-&gt;nlh-&gt;nlmsg_seq
)paren
op_le
l_int|0
)paren
(brace
id|tcp_listen_unlock
c_func
(paren
)paren
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
op_increment
id|num
suffix:semicolon
)brace
)brace
id|tcp_listen_unlock
c_func
(paren
)paren
suffix:semicolon
id|skip_listen_ht
suffix:colon
id|cb-&gt;args
(braket
l_int|0
)braket
op_assign
l_int|1
suffix:semicolon
id|s_i
op_assign
id|num
op_assign
id|s_num
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|r-&gt;tcpdiag_states
op_amp
op_complement
(paren
id|TCPF_LISTEN
op_or
id|TCPF_SYN_RECV
)paren
)paren
)paren
r_return
id|skb-&gt;len
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|s_i
suffix:semicolon
id|i
OL
id|tcp_ehash_size
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|tcp_ehash_bucket
op_star
id|head
op_assign
op_amp
id|tcp_ehash
(braket
id|i
)braket
suffix:semicolon
r_struct
id|sock
op_star
id|sk
suffix:semicolon
r_struct
id|hlist_node
op_star
id|node
suffix:semicolon
r_if
c_cond
(paren
id|i
OG
id|s_i
)paren
id|s_num
op_assign
l_int|0
suffix:semicolon
id|read_lock_bh
c_func
(paren
op_amp
id|head-&gt;lock
)paren
suffix:semicolon
id|num
op_assign
l_int|0
suffix:semicolon
id|sk_for_each
c_func
(paren
id|sk
comma
id|node
comma
op_amp
id|head-&gt;chain
)paren
(brace
r_struct
id|inet_opt
op_star
id|inet
op_assign
id|inet_sk
c_func
(paren
id|sk
)paren
suffix:semicolon
r_if
c_cond
(paren
id|num
OL
id|s_num
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|r-&gt;tcpdiag_states
op_amp
(paren
l_int|1
op_lshift
id|sk-&gt;sk_state
)paren
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|r-&gt;id.tcpdiag_sport
op_ne
id|inet-&gt;sport
op_logical_and
id|r-&gt;id.tcpdiag_sport
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|r-&gt;id.tcpdiag_dport
op_ne
id|inet-&gt;dport
op_logical_and
id|r-&gt;id.tcpdiag_dport
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|bc
op_logical_and
op_logical_neg
id|tcpdiag_bc_run
c_func
(paren
id|RTA_DATA
c_func
(paren
id|bc
)paren
comma
id|RTA_PAYLOAD
c_func
(paren
id|bc
)paren
comma
id|sk
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|tcpdiag_fill
c_func
(paren
id|skb
comma
id|sk
comma
id|r-&gt;tcpdiag_ext
comma
id|NETLINK_CB
c_func
(paren
id|cb-&gt;skb
)paren
dot
id|pid
comma
id|cb-&gt;nlh-&gt;nlmsg_seq
)paren
op_le
l_int|0
)paren
(brace
id|read_unlock_bh
c_func
(paren
op_amp
id|head-&gt;lock
)paren
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
op_increment
id|num
suffix:semicolon
)brace
r_if
c_cond
(paren
id|r-&gt;tcpdiag_states
op_amp
id|TCPF_TIME_WAIT
)paren
(brace
id|sk_for_each
c_func
(paren
id|sk
comma
id|node
comma
op_amp
id|tcp_ehash
(braket
id|i
op_plus
id|tcp_ehash_size
)braket
dot
id|chain
)paren
(brace
r_struct
id|inet_opt
op_star
id|inet
op_assign
id|inet_sk
c_func
(paren
id|sk
)paren
suffix:semicolon
r_if
c_cond
(paren
id|num
OL
id|s_num
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|r-&gt;tcpdiag_states
op_amp
(paren
l_int|1
op_lshift
id|sk-&gt;sk_zapped
)paren
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|r-&gt;id.tcpdiag_sport
op_ne
id|inet-&gt;sport
op_logical_and
id|r-&gt;id.tcpdiag_sport
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|r-&gt;id.tcpdiag_dport
op_ne
id|inet-&gt;dport
op_logical_and
id|r-&gt;id.tcpdiag_dport
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|bc
op_logical_and
op_logical_neg
id|tcpdiag_bc_run
c_func
(paren
id|RTA_DATA
c_func
(paren
id|bc
)paren
comma
id|RTA_PAYLOAD
c_func
(paren
id|bc
)paren
comma
id|sk
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|tcpdiag_fill
c_func
(paren
id|skb
comma
id|sk
comma
id|r-&gt;tcpdiag_ext
comma
id|NETLINK_CB
c_func
(paren
id|cb-&gt;skb
)paren
dot
id|pid
comma
id|cb-&gt;nlh-&gt;nlmsg_seq
)paren
op_le
l_int|0
)paren
(brace
id|read_unlock_bh
c_func
(paren
op_amp
id|head-&gt;lock
)paren
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
op_increment
id|num
suffix:semicolon
)brace
)brace
id|read_unlock_bh
c_func
(paren
op_amp
id|head-&gt;lock
)paren
suffix:semicolon
)brace
id|done
suffix:colon
id|cb-&gt;args
(braket
l_int|1
)braket
op_assign
id|i
suffix:semicolon
id|cb-&gt;args
(braket
l_int|2
)braket
op_assign
id|num
suffix:semicolon
r_return
id|skb-&gt;len
suffix:semicolon
)brace
DECL|function|tcpdiag_dump_done
r_static
r_int
id|tcpdiag_dump_done
c_func
(paren
r_struct
id|netlink_callback
op_star
id|cb
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
id|__inline__
r_int
DECL|function|tcpdiag_rcv_msg
id|tcpdiag_rcv_msg
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|nlmsghdr
op_star
id|nlh
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|nlh-&gt;nlmsg_flags
op_amp
id|NLM_F_REQUEST
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|nlh-&gt;nlmsg_type
op_ne
id|TCPDIAG_GETSOCK
)paren
r_goto
id|err_inval
suffix:semicolon
r_if
c_cond
(paren
id|NLMSG_LENGTH
c_func
(paren
r_sizeof
(paren
r_struct
id|tcpdiagreq
)paren
)paren
OG
id|skb-&gt;len
)paren
r_goto
id|err_inval
suffix:semicolon
r_if
c_cond
(paren
id|nlh-&gt;nlmsg_flags
op_amp
id|NLM_F_DUMP
)paren
(brace
r_if
c_cond
(paren
id|nlh-&gt;nlmsg_len
OG
l_int|4
op_plus
id|NLMSG_SPACE
c_func
(paren
r_sizeof
(paren
r_struct
id|tcpdiagreq
)paren
)paren
)paren
(brace
r_struct
id|rtattr
op_star
id|rta
op_assign
(paren
r_struct
id|rtattr
op_star
)paren
(paren
id|NLMSG_DATA
c_func
(paren
id|nlh
)paren
op_plus
r_sizeof
(paren
r_struct
id|tcpdiagreq
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rta-&gt;rta_type
op_ne
id|TCPDIAG_REQ_BYTECODE
op_logical_or
id|rta-&gt;rta_len
template_param
id|nlh-&gt;nlmsg_len
op_minus
id|NLMSG_SPACE
c_func
(paren
r_sizeof
(paren
r_struct
id|tcpdiagreq
)paren
)paren
)paren
r_goto
id|err_inval
suffix:semicolon
r_if
c_cond
(paren
id|tcpdiag_bc_audit
c_func
(paren
id|RTA_DATA
c_func
(paren
id|rta
)paren
comma
id|RTA_PAYLOAD
c_func
(paren
id|rta
)paren
)paren
)paren
r_goto
id|err_inval
suffix:semicolon
)brace
r_return
id|netlink_dump_start
c_func
(paren
id|tcpnl
comma
id|skb
comma
id|nlh
comma
id|tcpdiag_dump
comma
id|tcpdiag_dump_done
)paren
suffix:semicolon
)brace
r_else
(brace
r_return
id|tcpdiag_get_exact
c_func
(paren
id|skb
comma
id|nlh
)paren
suffix:semicolon
)brace
id|err_inval
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|tcpdiag_rcv_skb
r_static
r_inline
r_void
id|tcpdiag_rcv_skb
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_int
id|err
suffix:semicolon
r_struct
id|nlmsghdr
op_star
id|nlh
suffix:semicolon
r_if
c_cond
(paren
id|skb-&gt;len
op_ge
id|NLMSG_SPACE
c_func
(paren
l_int|0
)paren
)paren
(brace
id|nlh
op_assign
(paren
r_struct
id|nlmsghdr
op_star
)paren
id|skb-&gt;data
suffix:semicolon
r_if
c_cond
(paren
id|nlh-&gt;nlmsg_len
OL
r_sizeof
(paren
op_star
id|nlh
)paren
op_logical_or
id|skb-&gt;len
OL
id|nlh-&gt;nlmsg_len
)paren
r_return
suffix:semicolon
id|err
op_assign
id|tcpdiag_rcv_msg
c_func
(paren
id|skb
comma
id|nlh
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
op_logical_or
id|nlh-&gt;nlmsg_flags
op_amp
id|NLM_F_ACK
)paren
id|netlink_ack
c_func
(paren
id|skb
comma
id|nlh
comma
id|err
)paren
suffix:semicolon
)brace
)brace
DECL|function|tcpdiag_rcv
r_static
r_void
id|tcpdiag_rcv
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
id|len
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_while
c_loop
(paren
(paren
id|skb
op_assign
id|skb_dequeue
c_func
(paren
op_amp
id|sk-&gt;sk_receive_queue
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
id|tcpdiag_rcv_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
)brace
DECL|function|tcpdiag_init
r_void
id|__init
id|tcpdiag_init
c_func
(paren
r_void
)paren
(brace
id|tcpnl
op_assign
id|netlink_kernel_create
c_func
(paren
id|NETLINK_TCPDIAG
comma
id|tcpdiag_rcv
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tcpnl
op_eq
l_int|NULL
)paren
id|panic
c_func
(paren
l_string|&quot;tcpdiag_init: Cannot create netlink socket.&quot;
)paren
suffix:semicolon
)brace
eof
