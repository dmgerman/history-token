multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;Implementation of the Transmission Control Protocol(TCP).&n; *&n; * Version:&t;$Id: tcp_timer.c,v 1.88 2002/02/01 22:01:04 davem Exp $&n; *&n; * Authors:&t;Ross Biro, &lt;bir7@leland.Stanford.Edu&gt;&n; *&t;&t;Fred N. van Kempen, &lt;waltje@uWalt.NL.Mugnet.ORG&gt;&n; *&t;&t;Mark Evans, &lt;evansmp@uhura.aston.ac.uk&gt;&n; *&t;&t;Corey Minyard &lt;wf-rch!minyard@relay.EU.net&gt;&n; *&t;&t;Florian La Roche, &lt;flla@stud.uni-sb.de&gt;&n; *&t;&t;Charles Hedrick, &lt;hedrick@klinzhai.rutgers.edu&gt;&n; *&t;&t;Linus Torvalds, &lt;torvalds@cs.helsinki.fi&gt;&n; *&t;&t;Alan Cox, &lt;gw4pts@gw4pts.ampr.org&gt;&n; *&t;&t;Matthew Dillon, &lt;dillon@apollo.west.oic.com&gt;&n; *&t;&t;Arnt Gulbrandsen, &lt;agulbra@nvg.unit.no&gt;&n; *&t;&t;Jorge Cwik, &lt;jorge@laser.satlink.net&gt;&n; */
macro_line|#include &lt;net/tcp.h&gt;
DECL|variable|sysctl_tcp_syn_retries
r_int
id|sysctl_tcp_syn_retries
op_assign
id|TCP_SYN_RETRIES
suffix:semicolon
DECL|variable|sysctl_tcp_synack_retries
r_int
id|sysctl_tcp_synack_retries
op_assign
id|TCP_SYNACK_RETRIES
suffix:semicolon
DECL|variable|sysctl_tcp_keepalive_time
r_int
id|sysctl_tcp_keepalive_time
op_assign
id|TCP_KEEPALIVE_TIME
suffix:semicolon
DECL|variable|sysctl_tcp_keepalive_probes
r_int
id|sysctl_tcp_keepalive_probes
op_assign
id|TCP_KEEPALIVE_PROBES
suffix:semicolon
DECL|variable|sysctl_tcp_keepalive_intvl
r_int
id|sysctl_tcp_keepalive_intvl
op_assign
id|TCP_KEEPALIVE_INTVL
suffix:semicolon
DECL|variable|sysctl_tcp_retries1
r_int
id|sysctl_tcp_retries1
op_assign
id|TCP_RETR1
suffix:semicolon
DECL|variable|sysctl_tcp_retries2
r_int
id|sysctl_tcp_retries2
op_assign
id|TCP_RETR2
suffix:semicolon
DECL|variable|sysctl_tcp_orphan_retries
r_int
id|sysctl_tcp_orphan_retries
suffix:semicolon
r_static
r_void
id|tcp_write_timer
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_static
r_void
id|tcp_delack_timer
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_static
r_void
id|tcp_keepalive_timer
(paren
r_int
r_int
id|data
)paren
suffix:semicolon
DECL|variable|timer_bug_msg
r_const
r_char
id|timer_bug_msg
(braket
)braket
op_assign
id|KERN_DEBUG
l_string|&quot;tcpbug: unknown timer value&bslash;n&quot;
suffix:semicolon
multiline_comment|/*&n; * Using different timers for retransmit, delayed acks and probes&n; * We may wish use just one timer maintaining a list of expire jiffies &n; * to optimize.&n; */
DECL|function|tcp_init_xmit_timers
r_void
id|tcp_init_xmit_timers
c_func
(paren
r_struct
id|sock
op_star
id|sk
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
id|init_timer
c_func
(paren
op_amp
id|tp-&gt;retransmit_timer
)paren
suffix:semicolon
id|tp-&gt;retransmit_timer.function
op_assign
op_amp
id|tcp_write_timer
suffix:semicolon
id|tp-&gt;retransmit_timer.data
op_assign
(paren
r_int
r_int
)paren
id|sk
suffix:semicolon
id|tp-&gt;pending
op_assign
l_int|0
suffix:semicolon
id|init_timer
c_func
(paren
op_amp
id|tp-&gt;delack_timer
)paren
suffix:semicolon
id|tp-&gt;delack_timer.function
op_assign
op_amp
id|tcp_delack_timer
suffix:semicolon
id|tp-&gt;delack_timer.data
op_assign
(paren
r_int
r_int
)paren
id|sk
suffix:semicolon
id|tp-&gt;ack.pending
op_assign
l_int|0
suffix:semicolon
id|init_timer
c_func
(paren
op_amp
id|sk-&gt;timer
)paren
suffix:semicolon
id|sk-&gt;timer.function
op_assign
op_amp
id|tcp_keepalive_timer
suffix:semicolon
id|sk-&gt;timer.data
op_assign
(paren
r_int
r_int
)paren
id|sk
suffix:semicolon
)brace
DECL|function|tcp_clear_xmit_timers
r_void
id|tcp_clear_xmit_timers
c_func
(paren
r_struct
id|sock
op_star
id|sk
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
id|tp-&gt;pending
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|timer_pending
c_func
(paren
op_amp
id|tp-&gt;retransmit_timer
)paren
op_logical_and
id|del_timer
c_func
(paren
op_amp
id|tp-&gt;retransmit_timer
)paren
)paren
id|__sock_put
c_func
(paren
id|sk
)paren
suffix:semicolon
id|tp-&gt;ack.pending
op_assign
l_int|0
suffix:semicolon
id|tp-&gt;ack.blocked
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|timer_pending
c_func
(paren
op_amp
id|tp-&gt;delack_timer
)paren
op_logical_and
id|del_timer
c_func
(paren
op_amp
id|tp-&gt;delack_timer
)paren
)paren
id|__sock_put
c_func
(paren
id|sk
)paren
suffix:semicolon
r_if
c_cond
(paren
id|timer_pending
c_func
(paren
op_amp
id|sk-&gt;timer
)paren
op_logical_and
id|del_timer
c_func
(paren
op_amp
id|sk-&gt;timer
)paren
)paren
(brace
id|__sock_put
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
)brace
DECL|function|tcp_write_err
r_static
r_void
id|tcp_write_err
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
(brace
id|sk-&gt;err
op_assign
id|sk-&gt;err_soft
ques
c_cond
suffix:colon
id|ETIMEDOUT
suffix:semicolon
id|sk
op_member_access_from_pointer
id|error_report
c_func
(paren
id|sk
)paren
suffix:semicolon
id|tcp_done
c_func
(paren
id|sk
)paren
suffix:semicolon
id|NET_INC_STATS_BH
c_func
(paren
id|TCPAbortOnTimeout
)paren
suffix:semicolon
)brace
multiline_comment|/* Do not allow orphaned sockets to eat all our resources.&n; * This is direct violation of TCP specs, but it is required&n; * to prevent DoS attacks. It is called when a retransmission timeout&n; * or zero probe timeout occurs on orphaned socket.&n; *&n; * Criterium is still not confirmed experimentally and may change.&n; * We kill the socket, if:&n; * 1. If number of orphaned sockets exceeds an administratively configured&n; *    limit.&n; * 2. If we have strong memory pressure.&n; */
DECL|function|tcp_out_of_resources
r_static
r_int
id|tcp_out_of_resources
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
id|do_reset
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
r_int
id|orphans
op_assign
id|atomic_read
c_func
(paren
op_amp
id|tcp_orphan_count
)paren
suffix:semicolon
multiline_comment|/* If peer does not open window for long time, or did not transmit &n;&t; * anything for long time, penalize it. */
r_if
c_cond
(paren
(paren
id|s32
)paren
(paren
id|tcp_time_stamp
op_minus
id|tp-&gt;lsndtime
)paren
OG
l_int|2
op_star
id|TCP_RTO_MAX
op_logical_or
op_logical_neg
id|do_reset
)paren
id|orphans
op_lshift_assign
l_int|1
suffix:semicolon
multiline_comment|/* If some dubious ICMP arrived, penalize even more. */
r_if
c_cond
(paren
id|sk-&gt;err_soft
)paren
id|orphans
op_lshift_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|orphans
op_ge
id|sysctl_tcp_max_orphans
op_logical_or
(paren
id|sk-&gt;wmem_queued
OG
id|SOCK_MIN_SNDBUF
op_logical_and
id|atomic_read
c_func
(paren
op_amp
id|tcp_memory_allocated
)paren
OG
id|sysctl_tcp_mem
(braket
l_int|2
)braket
)paren
)paren
(brace
r_if
c_cond
(paren
id|net_ratelimit
c_func
(paren
)paren
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Out of socket memory&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Catch exceptional cases, when connection requires reset.&n;&t;&t; *      1. Last segment was sent recently. */
r_if
c_cond
(paren
(paren
id|s32
)paren
(paren
id|tcp_time_stamp
op_minus
id|tp-&gt;lsndtime
)paren
op_le
id|TCP_TIMEWAIT_LEN
op_logical_or
multiline_comment|/*  2. Window is closed. */
(paren
op_logical_neg
id|tp-&gt;snd_wnd
op_logical_and
op_logical_neg
id|tp-&gt;packets_out
)paren
)paren
id|do_reset
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|do_reset
)paren
id|tcp_send_active_reset
c_func
(paren
id|sk
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
id|tcp_done
c_func
(paren
id|sk
)paren
suffix:semicolon
id|NET_INC_STATS_BH
c_func
(paren
id|TCPAbortOnMemory
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Calculate maximal number or retries on an orphaned socket. */
DECL|function|tcp_orphan_retries
r_static
r_int
id|tcp_orphan_retries
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
id|alive
)paren
(brace
r_int
id|retries
op_assign
id|sysctl_tcp_orphan_retries
suffix:semicolon
multiline_comment|/* May be zero. */
multiline_comment|/* We know from an ICMP that something is wrong. */
r_if
c_cond
(paren
id|sk-&gt;err_soft
op_logical_and
op_logical_neg
id|alive
)paren
id|retries
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* However, if socket sent something recently, select some safe&n;&t; * number of retries. 8 corresponds to &gt;100 seconds with minimal&n;&t; * RTO of 200msec. */
r_if
c_cond
(paren
id|retries
op_eq
l_int|0
op_logical_and
id|alive
)paren
id|retries
op_assign
l_int|8
suffix:semicolon
r_return
id|retries
suffix:semicolon
)brace
multiline_comment|/* A write timeout has occurred. Process the after effects. */
DECL|function|tcp_write_timeout
r_static
r_int
id|tcp_write_timeout
c_func
(paren
r_struct
id|sock
op_star
id|sk
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
r_int
id|retry_until
suffix:semicolon
r_if
c_cond
(paren
(paren
l_int|1
op_lshift
id|sk-&gt;state
)paren
op_amp
(paren
id|TCPF_SYN_SENT
op_or
id|TCPF_SYN_RECV
)paren
)paren
(brace
r_if
c_cond
(paren
id|tp-&gt;retransmits
)paren
id|dst_negative_advice
c_func
(paren
op_amp
id|sk-&gt;dst_cache
)paren
suffix:semicolon
id|retry_until
op_assign
id|tp-&gt;syn_retries
ques
c_cond
suffix:colon
id|sysctl_tcp_syn_retries
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|tp-&gt;retransmits
op_ge
id|sysctl_tcp_retries1
)paren
(brace
multiline_comment|/* NOTE. draft-ietf-tcpimpl-pmtud-01.txt requires pmtu black&n;&t;&t;&t;   hole detection. :-(&n;&n;&t;&t;&t;   It is place to make it. It is not made. I do not want&n;&t;&t;&t;   to make it. It is disguisting. It does not work in any&n;&t;&t;&t;   case. Let me to cite the same draft, which requires for&n;&t;&t;&t;   us to implement this:&n;&n;   &quot;The one security concern raised by this memo is that ICMP black holes&n;   are often caused by over-zealous security administrators who block&n;   all ICMP messages.  It is vitally important that those who design and&n;   deploy security systems understand the impact of strict filtering on&n;   upper-layer protocols.  The safest web site in the world is worthless&n;   if most TCP implementations cannot transfer data from it.  It would&n;   be far nicer to have all of the black holes fixed rather than fixing&n;   all of the TCP implementations.&quot;&n;&n;                           Golden words :-).&n;&t;&t;   */
id|dst_negative_advice
c_func
(paren
op_amp
id|sk-&gt;dst_cache
)paren
suffix:semicolon
)brace
id|retry_until
op_assign
id|sysctl_tcp_retries2
suffix:semicolon
r_if
c_cond
(paren
id|sk-&gt;dead
)paren
(brace
r_int
id|alive
op_assign
(paren
id|tp-&gt;rto
OL
id|TCP_RTO_MAX
)paren
suffix:semicolon
id|retry_until
op_assign
id|tcp_orphan_retries
c_func
(paren
id|sk
comma
id|alive
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tcp_out_of_resources
c_func
(paren
id|sk
comma
id|alive
op_logical_or
id|tp-&gt;retransmits
OL
id|retry_until
)paren
)paren
r_return
l_int|1
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|tp-&gt;retransmits
op_ge
id|retry_until
)paren
(brace
multiline_comment|/* Has it gone just too far? */
id|tcp_write_err
c_func
(paren
id|sk
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|tcp_delack_timer
r_static
r_void
id|tcp_delack_timer
c_func
(paren
r_int
r_int
id|data
)paren
(brace
r_struct
id|sock
op_star
id|sk
op_assign
(paren
r_struct
id|sock
op_star
)paren
id|data
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
id|bh_lock_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sock_owned_by_user
c_func
(paren
id|sk
)paren
)paren
(brace
multiline_comment|/* Try again later. */
id|tp-&gt;ack.blocked
op_assign
l_int|1
suffix:semicolon
id|NET_INC_STATS_BH
c_func
(paren
id|DelayedACKLocked
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mod_timer
c_func
(paren
op_amp
id|tp-&gt;delack_timer
comma
id|jiffies
op_plus
id|TCP_DELACK_MIN
)paren
)paren
id|sock_hold
c_func
(paren
id|sk
)paren
suffix:semicolon
r_goto
id|out_unlock
suffix:semicolon
)brace
id|tcp_mem_reclaim
c_func
(paren
id|sk
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sk-&gt;state
op_eq
id|TCP_CLOSE
op_logical_or
op_logical_neg
(paren
id|tp-&gt;ack.pending
op_amp
id|TCP_ACK_TIMER
)paren
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
(paren
r_int
)paren
(paren
id|tp-&gt;ack.timeout
op_minus
id|jiffies
)paren
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|mod_timer
c_func
(paren
op_amp
id|tp-&gt;delack_timer
comma
id|tp-&gt;ack.timeout
)paren
)paren
id|sock_hold
c_func
(paren
id|sk
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|tp-&gt;ack.pending
op_and_assign
op_complement
id|TCP_ACK_TIMER
suffix:semicolon
r_if
c_cond
(paren
id|skb_queue_len
c_func
(paren
op_amp
id|tp-&gt;ucopy.prequeue
)paren
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
id|net_statistics
(braket
id|smp_processor_id
c_func
(paren
)paren
op_star
l_int|2
)braket
dot
id|TCPSchedulerFailed
op_add_assign
id|skb_queue_len
c_func
(paren
op_amp
id|tp-&gt;ucopy.prequeue
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|skb
op_assign
id|__skb_dequeue
c_func
(paren
op_amp
id|tp-&gt;ucopy.prequeue
)paren
)paren
op_ne
l_int|NULL
)paren
id|sk
op_member_access_from_pointer
id|backlog_rcv
c_func
(paren
id|sk
comma
id|skb
)paren
suffix:semicolon
id|tp-&gt;ucopy.memory
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|tcp_ack_scheduled
c_func
(paren
id|tp
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|tp-&gt;ack.pingpong
)paren
(brace
multiline_comment|/* Delayed ACK missed: inflate ATO. */
id|tp-&gt;ack.ato
op_assign
id|min
c_func
(paren
id|tp-&gt;ack.ato
op_lshift
l_int|1
comma
id|tp-&gt;rto
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Delayed ACK missed: leave pingpong mode and&n;&t;&t;&t; * deflate ATO.&n;&t;&t;&t; */
id|tp-&gt;ack.pingpong
op_assign
l_int|0
suffix:semicolon
id|tp-&gt;ack.ato
op_assign
id|TCP_ATO_MIN
suffix:semicolon
)brace
id|tcp_send_ack
c_func
(paren
id|sk
)paren
suffix:semicolon
id|NET_INC_STATS_BH
c_func
(paren
id|DelayedACKs
)paren
suffix:semicolon
)brace
id|TCP_CHECK_TIMER
c_func
(paren
id|sk
)paren
suffix:semicolon
id|out
suffix:colon
r_if
c_cond
(paren
id|tcp_memory_pressure
)paren
id|tcp_mem_reclaim
c_func
(paren
id|sk
)paren
suffix:semicolon
id|out_unlock
suffix:colon
id|bh_unlock_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
id|sock_put
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
DECL|function|tcp_probe_timer
r_static
r_void
id|tcp_probe_timer
c_func
(paren
r_struct
id|sock
op_star
id|sk
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
r_int
id|max_probes
suffix:semicolon
r_if
c_cond
(paren
id|tp-&gt;packets_out
op_logical_or
op_logical_neg
id|tp-&gt;send_head
)paren
(brace
id|tp-&gt;probes_out
op_assign
l_int|0
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* *WARNING* RFC 1122 forbids this&n;&t; *&n;&t; * It doesn&squot;t AFAIK, because we kill the retransmit timer -AK&n;&t; *&n;&t; * FIXME: We ought not to do it, Solaris 2.5 actually has fixing&n;&t; * this behaviour in Solaris down as a bug fix. [AC]&n;&t; *&n;&t; * Let me to explain. probes_out is zeroed by incoming ACKs&n;&t; * even if they advertise zero window. Hence, connection is killed only&n;&t; * if we received no ACKs for normal connection timeout. It is not killed&n;&t; * only because window stays zero for some time, window may be zero&n;&t; * until armageddon and even later. We are in full accordance&n;&t; * with RFCs, only probe timer combines both retransmission timeout&n;&t; * and probe timeout in one bottle.&t;&t;&t;&t;--ANK&n;&t; */
id|max_probes
op_assign
id|sysctl_tcp_retries2
suffix:semicolon
r_if
c_cond
(paren
id|sk-&gt;dead
)paren
(brace
r_int
id|alive
op_assign
(paren
(paren
id|tp-&gt;rto
op_lshift
id|tp-&gt;backoff
)paren
OL
id|TCP_RTO_MAX
)paren
suffix:semicolon
id|max_probes
op_assign
id|tcp_orphan_retries
c_func
(paren
id|sk
comma
id|alive
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tcp_out_of_resources
c_func
(paren
id|sk
comma
id|alive
op_logical_or
id|tp-&gt;probes_out
op_le
id|max_probes
)paren
)paren
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|tp-&gt;probes_out
OG
id|max_probes
)paren
(brace
id|tcp_write_err
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Only send another probe if we didn&squot;t close things up. */
id|tcp_send_probe0
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; *&t;The TCP retransmit timer.&n; */
DECL|function|tcp_retransmit_timer
r_static
r_void
id|tcp_retransmit_timer
c_func
(paren
r_struct
id|sock
op_star
id|sk
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
r_if
c_cond
(paren
id|tp-&gt;packets_out
op_eq
l_int|0
)paren
r_goto
id|out
suffix:semicolon
id|BUG_TRAP
c_func
(paren
op_logical_neg
id|skb_queue_empty
c_func
(paren
op_amp
id|sk-&gt;write_queue
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tp-&gt;snd_wnd
op_eq
l_int|0
op_logical_and
op_logical_neg
id|sk-&gt;dead
op_logical_and
op_logical_neg
(paren
(paren
l_int|1
op_lshift
id|sk-&gt;state
)paren
op_amp
(paren
id|TCPF_SYN_SENT
op_or
id|TCPF_SYN_RECV
)paren
)paren
)paren
(brace
multiline_comment|/* Receiver dastardly shrinks window. Our retransmits&n;&t;&t; * become zero probes, but we should not timeout this&n;&t;&t; * connection. If the socket is an orphan, time it out,&n;&t;&t; * we cannot allow such beasts to hang infinitely.&n;&t;&t; */
macro_line|#ifdef TCP_DEBUG
r_if
c_cond
(paren
id|net_ratelimit
c_func
(paren
)paren
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
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;TCP: Treason uncloaked! Peer %u.%u.%u.%u:%u/%u shrinks window %u:%u. Repaired.&bslash;n&quot;
comma
id|NIPQUAD
c_func
(paren
id|inet-&gt;daddr
)paren
comma
id|htons
c_func
(paren
id|inet-&gt;dport
)paren
comma
id|inet-&gt;num
comma
id|tp-&gt;snd_una
comma
id|tp-&gt;snd_nxt
)paren
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
id|tcp_time_stamp
op_minus
id|tp-&gt;rcv_tstamp
OG
id|TCP_RTO_MAX
)paren
(brace
id|tcp_write_err
c_func
(paren
id|sk
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|tcp_enter_loss
c_func
(paren
id|sk
comma
l_int|0
)paren
suffix:semicolon
id|tcp_retransmit_skb
c_func
(paren
id|sk
comma
id|skb_peek
c_func
(paren
op_amp
id|sk-&gt;write_queue
)paren
)paren
suffix:semicolon
id|__sk_dst_reset
c_func
(paren
id|sk
)paren
suffix:semicolon
r_goto
id|out_reset_timer
suffix:semicolon
)brace
r_if
c_cond
(paren
id|tcp_write_timeout
c_func
(paren
id|sk
)paren
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|tp-&gt;retransmits
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|tp-&gt;ca_state
op_eq
id|TCP_CA_Disorder
op_logical_or
id|tp-&gt;ca_state
op_eq
id|TCP_CA_Recovery
)paren
(brace
r_if
c_cond
(paren
id|tp-&gt;sack_ok
)paren
(brace
r_if
c_cond
(paren
id|tp-&gt;ca_state
op_eq
id|TCP_CA_Recovery
)paren
id|NET_INC_STATS_BH
c_func
(paren
id|TCPSackRecoveryFail
)paren
suffix:semicolon
r_else
id|NET_INC_STATS_BH
c_func
(paren
id|TCPSackFailures
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|tp-&gt;ca_state
op_eq
id|TCP_CA_Recovery
)paren
id|NET_INC_STATS_BH
c_func
(paren
id|TCPRenoRecoveryFail
)paren
suffix:semicolon
r_else
id|NET_INC_STATS_BH
c_func
(paren
id|TCPRenoFailures
)paren
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|tp-&gt;ca_state
op_eq
id|TCP_CA_Loss
)paren
(brace
id|NET_INC_STATS_BH
c_func
(paren
id|TCPLossFailures
)paren
suffix:semicolon
)brace
r_else
(brace
id|NET_INC_STATS_BH
c_func
(paren
id|TCPTimeouts
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|tcp_use_frto
c_func
(paren
id|sk
)paren
)paren
(brace
id|tcp_enter_frto
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
r_else
(brace
id|tcp_enter_loss
c_func
(paren
id|sk
comma
l_int|0
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|tcp_retransmit_skb
c_func
(paren
id|sk
comma
id|skb_peek
c_func
(paren
op_amp
id|sk-&gt;write_queue
)paren
)paren
OG
l_int|0
)paren
(brace
multiline_comment|/* Retransmission failed because of local congestion,&n;&t;&t; * do not backoff.&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|tp-&gt;retransmits
)paren
id|tp-&gt;retransmits
op_assign
l_int|1
suffix:semicolon
id|tcp_reset_xmit_timer
c_func
(paren
id|sk
comma
id|TCP_TIME_RETRANS
comma
id|min
c_func
(paren
id|tp-&gt;rto
comma
id|TCP_RESOURCE_PROBE_INTERVAL
)paren
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/* Increase the timeout each time we retransmit.  Note that&n;&t; * we do not increase the rtt estimate.  rto is initialized&n;&t; * from rtt, but increases here.  Jacobson (SIGCOMM 88) suggests&n;&t; * that doubling rto each time is the least we can get away with.&n;&t; * In KA9Q, Karn uses this for the first few times, and then&n;&t; * goes to quadratic.  netBSD doubles, but only goes up to *64,&n;&t; * and clamps at 1 to 64 sec afterwards.  Note that 120 sec is&n;&t; * defined in the protocol as the maximum possible RTT.  I guess&n;&t; * we&squot;ll have to use something other than TCP to talk to the&n;&t; * University of Mars.&n;&t; *&n;&t; * PAWS allows us longer timeouts and large windows, so once&n;&t; * implemented ftp to mars will work nicely. We will have to fix&n;&t; * the 120 second clamps though!&n;&t; */
id|tp-&gt;backoff
op_increment
suffix:semicolon
id|tp-&gt;retransmits
op_increment
suffix:semicolon
id|out_reset_timer
suffix:colon
id|tp-&gt;rto
op_assign
id|min
c_func
(paren
id|tp-&gt;rto
op_lshift
l_int|1
comma
id|TCP_RTO_MAX
)paren
suffix:semicolon
id|tcp_reset_xmit_timer
c_func
(paren
id|sk
comma
id|TCP_TIME_RETRANS
comma
id|tp-&gt;rto
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tp-&gt;retransmits
OG
id|sysctl_tcp_retries1
)paren
id|__sk_dst_reset
c_func
(paren
id|sk
)paren
suffix:semicolon
id|out
suffix:colon
suffix:semicolon
)brace
DECL|function|tcp_write_timer
r_static
r_void
id|tcp_write_timer
c_func
(paren
r_int
r_int
id|data
)paren
(brace
r_struct
id|sock
op_star
id|sk
op_assign
(paren
r_struct
id|sock
op_star
)paren
id|data
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
r_int
id|event
suffix:semicolon
id|bh_lock_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sock_owned_by_user
c_func
(paren
id|sk
)paren
)paren
(brace
multiline_comment|/* Try again later */
r_if
c_cond
(paren
op_logical_neg
id|mod_timer
c_func
(paren
op_amp
id|tp-&gt;retransmit_timer
comma
id|jiffies
op_plus
(paren
id|HZ
op_div
l_int|20
)paren
)paren
)paren
id|sock_hold
c_func
(paren
id|sk
)paren
suffix:semicolon
r_goto
id|out_unlock
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sk-&gt;state
op_eq
id|TCP_CLOSE
op_logical_or
op_logical_neg
id|tp-&gt;pending
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
(paren
r_int
)paren
(paren
id|tp-&gt;timeout
op_minus
id|jiffies
)paren
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|mod_timer
c_func
(paren
op_amp
id|tp-&gt;retransmit_timer
comma
id|tp-&gt;timeout
)paren
)paren
id|sock_hold
c_func
(paren
id|sk
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|event
op_assign
id|tp-&gt;pending
suffix:semicolon
id|tp-&gt;pending
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|event
)paren
(brace
r_case
id|TCP_TIME_RETRANS
suffix:colon
id|tcp_retransmit_timer
c_func
(paren
id|sk
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|TCP_TIME_PROBE0
suffix:colon
id|tcp_probe_timer
c_func
(paren
id|sk
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|TCP_CHECK_TIMER
c_func
(paren
id|sk
)paren
suffix:semicolon
id|out
suffix:colon
id|tcp_mem_reclaim
c_func
(paren
id|sk
)paren
suffix:semicolon
id|out_unlock
suffix:colon
id|bh_unlock_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
id|sock_put
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Timer for listening sockets&n; */
DECL|function|tcp_synack_timer
r_static
r_void
id|tcp_synack_timer
c_func
(paren
r_struct
id|sock
op_star
id|sk
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
r_struct
id|tcp_listen_opt
op_star
id|lopt
op_assign
id|tp-&gt;listen_opt
suffix:semicolon
r_int
id|max_retries
op_assign
id|tp-&gt;syn_retries
ques
c_cond
suffix:colon
id|sysctl_tcp_synack_retries
suffix:semicolon
r_int
id|thresh
op_assign
id|max_retries
suffix:semicolon
r_int
r_int
id|now
op_assign
id|jiffies
suffix:semicolon
r_struct
id|open_request
op_star
op_star
id|reqp
comma
op_star
id|req
suffix:semicolon
r_int
id|i
comma
id|budget
suffix:semicolon
r_if
c_cond
(paren
id|lopt
op_eq
l_int|NULL
op_logical_or
id|lopt-&gt;qlen
op_eq
l_int|0
)paren
r_return
suffix:semicolon
multiline_comment|/* Normally all the openreqs are young and become mature&n;&t; * (i.e. converted to established socket) for first timeout.&n;&t; * If synack was not acknowledged for 3 seconds, it means&n;&t; * one of the following things: synack was lost, ack was lost,&n;&t; * rtt is high or nobody planned to ack (i.e. synflood).&n;&t; * When server is a bit loaded, queue is populated with old&n;&t; * open requests, reducing effective size of queue.&n;&t; * When server is well loaded, queue size reduces to zero&n;&t; * after several minutes of work. It is not synflood,&n;&t; * it is normal operation. The solution is pruning&n;&t; * too old entries overriding normal timeout, when&n;&t; * situation becomes dangerous.&n;&t; *&n;&t; * Essentially, we reserve half of room for young&n;&t; * embrions; and abort old ones without pity, if old&n;&t; * ones are about to clog our table.&n;&t; */
r_if
c_cond
(paren
id|lopt-&gt;qlen
op_rshift
(paren
id|lopt-&gt;max_qlen_log
op_minus
l_int|1
)paren
)paren
(brace
r_int
id|young
op_assign
(paren
id|lopt-&gt;qlen_young
op_lshift
l_int|1
)paren
suffix:semicolon
r_while
c_loop
(paren
id|thresh
OG
l_int|2
)paren
(brace
r_if
c_cond
(paren
id|lopt-&gt;qlen
OL
id|young
)paren
r_break
suffix:semicolon
id|thresh
op_decrement
suffix:semicolon
id|young
op_lshift_assign
l_int|1
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|tp-&gt;defer_accept
)paren
id|max_retries
op_assign
id|tp-&gt;defer_accept
suffix:semicolon
id|budget
op_assign
l_int|2
op_star
(paren
id|TCP_SYNQ_HSIZE
op_div
(paren
id|TCP_TIMEOUT_INIT
op_div
id|TCP_SYNQ_INTERVAL
)paren
)paren
suffix:semicolon
id|i
op_assign
id|lopt-&gt;clock_hand
suffix:semicolon
r_do
(brace
id|reqp
op_assign
op_amp
id|lopt-&gt;syn_table
(braket
id|i
)braket
suffix:semicolon
r_while
c_loop
(paren
(paren
id|req
op_assign
op_star
id|reqp
)paren
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
(paren
r_int
)paren
(paren
id|now
op_minus
id|req-&gt;expires
)paren
op_ge
l_int|0
)paren
(brace
r_if
c_cond
(paren
(paren
id|req-&gt;retrans
OL
id|thresh
op_logical_or
(paren
id|req-&gt;acked
op_logical_and
id|req-&gt;retrans
OL
id|max_retries
)paren
)paren
op_logical_and
op_logical_neg
id|req
op_member_access_from_pointer
r_class
op_member_access_from_pointer
id|rtx_syn_ack
c_func
(paren
id|sk
comma
id|req
comma
l_int|NULL
)paren
)paren
(brace
r_int
r_int
id|timeo
suffix:semicolon
r_if
c_cond
(paren
id|req-&gt;retrans
op_increment
op_eq
l_int|0
)paren
id|lopt-&gt;qlen_young
op_decrement
suffix:semicolon
id|timeo
op_assign
id|min
c_func
(paren
(paren
id|TCP_TIMEOUT_INIT
op_lshift
id|req-&gt;retrans
)paren
comma
id|TCP_RTO_MAX
)paren
suffix:semicolon
id|req-&gt;expires
op_assign
id|now
op_plus
id|timeo
suffix:semicolon
id|reqp
op_assign
op_amp
id|req-&gt;dl_next
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/* Drop this request */
id|write_lock
c_func
(paren
op_amp
id|tp-&gt;syn_wait_lock
)paren
suffix:semicolon
op_star
id|reqp
op_assign
id|req-&gt;dl_next
suffix:semicolon
id|write_unlock
c_func
(paren
op_amp
id|tp-&gt;syn_wait_lock
)paren
suffix:semicolon
id|lopt-&gt;qlen
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|req-&gt;retrans
op_eq
l_int|0
)paren
id|lopt-&gt;qlen_young
op_decrement
suffix:semicolon
id|tcp_openreq_free
c_func
(paren
id|req
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|reqp
op_assign
op_amp
id|req-&gt;dl_next
suffix:semicolon
)brace
id|i
op_assign
(paren
id|i
op_plus
l_int|1
)paren
op_amp
(paren
id|TCP_SYNQ_HSIZE
op_minus
l_int|1
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|budget
OG
l_int|0
)paren
suffix:semicolon
id|lopt-&gt;clock_hand
op_assign
id|i
suffix:semicolon
r_if
c_cond
(paren
id|lopt-&gt;qlen
)paren
id|tcp_reset_keepalive_timer
c_func
(paren
id|sk
comma
id|TCP_SYNQ_INTERVAL
)paren
suffix:semicolon
)brace
DECL|function|tcp_delete_keepalive_timer
r_void
id|tcp_delete_keepalive_timer
(paren
r_struct
id|sock
op_star
id|sk
)paren
(brace
r_if
c_cond
(paren
id|timer_pending
c_func
(paren
op_amp
id|sk-&gt;timer
)paren
op_logical_and
id|del_timer
(paren
op_amp
id|sk-&gt;timer
)paren
)paren
id|__sock_put
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
DECL|function|tcp_reset_keepalive_timer
r_void
id|tcp_reset_keepalive_timer
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
r_int
id|len
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|mod_timer
c_func
(paren
op_amp
id|sk-&gt;timer
comma
id|jiffies
op_plus
id|len
)paren
)paren
id|sock_hold
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
DECL|function|tcp_set_keepalive
r_void
id|tcp_set_keepalive
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
id|val
)paren
(brace
r_if
c_cond
(paren
(paren
l_int|1
op_lshift
id|sk-&gt;state
)paren
op_amp
(paren
id|TCPF_CLOSE
op_or
id|TCPF_LISTEN
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|val
op_logical_and
op_logical_neg
id|sk-&gt;keepopen
)paren
id|tcp_reset_keepalive_timer
c_func
(paren
id|sk
comma
id|keepalive_time_when
c_func
(paren
id|tcp_sk
c_func
(paren
id|sk
)paren
)paren
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|val
)paren
id|tcp_delete_keepalive_timer
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
DECL|function|tcp_keepalive_timer
r_static
r_void
id|tcp_keepalive_timer
(paren
r_int
r_int
id|data
)paren
(brace
r_struct
id|sock
op_star
id|sk
op_assign
(paren
r_struct
id|sock
op_star
)paren
id|data
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
id|__u32
id|elapsed
suffix:semicolon
multiline_comment|/* Only process if socket is not in use. */
id|bh_lock_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sock_owned_by_user
c_func
(paren
id|sk
)paren
)paren
(brace
multiline_comment|/* Try again later. */
id|tcp_reset_keepalive_timer
(paren
id|sk
comma
id|HZ
op_div
l_int|20
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sk-&gt;state
op_eq
id|TCP_LISTEN
)paren
(brace
id|tcp_synack_timer
c_func
(paren
id|sk
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sk-&gt;state
op_eq
id|TCP_FIN_WAIT2
op_logical_and
id|sk-&gt;dead
)paren
(brace
r_if
c_cond
(paren
id|tp-&gt;linger2
op_ge
l_int|0
)paren
(brace
r_int
id|tmo
op_assign
id|tcp_fin_time
c_func
(paren
id|tp
)paren
op_minus
id|TCP_TIMEWAIT_LEN
suffix:semicolon
r_if
c_cond
(paren
id|tmo
OG
l_int|0
)paren
(brace
id|tcp_time_wait
c_func
(paren
id|sk
comma
id|TCP_FIN_WAIT2
comma
id|tmo
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
)brace
id|tcp_send_active_reset
c_func
(paren
id|sk
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_goto
id|death
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|sk-&gt;keepopen
op_logical_or
id|sk-&gt;state
op_eq
id|TCP_CLOSE
)paren
r_goto
id|out
suffix:semicolon
id|elapsed
op_assign
id|keepalive_time_when
c_func
(paren
id|tp
)paren
suffix:semicolon
multiline_comment|/* It is alive without keepalive 8) */
r_if
c_cond
(paren
id|tp-&gt;packets_out
op_logical_or
id|tp-&gt;send_head
)paren
r_goto
id|resched
suffix:semicolon
id|elapsed
op_assign
id|tcp_time_stamp
op_minus
id|tp-&gt;rcv_tstamp
suffix:semicolon
r_if
c_cond
(paren
id|elapsed
op_ge
id|keepalive_time_when
c_func
(paren
id|tp
)paren
)paren
(brace
r_if
c_cond
(paren
(paren
op_logical_neg
id|tp-&gt;keepalive_probes
op_logical_and
id|tp-&gt;probes_out
op_ge
id|sysctl_tcp_keepalive_probes
)paren
op_logical_or
(paren
id|tp-&gt;keepalive_probes
op_logical_and
id|tp-&gt;probes_out
op_ge
id|tp-&gt;keepalive_probes
)paren
)paren
(brace
id|tcp_send_active_reset
c_func
(paren
id|sk
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
id|tcp_write_err
c_func
(paren
id|sk
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|tcp_write_wakeup
c_func
(paren
id|sk
)paren
op_le
l_int|0
)paren
(brace
id|tp-&gt;probes_out
op_increment
suffix:semicolon
id|elapsed
op_assign
id|keepalive_intvl_when
c_func
(paren
id|tp
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* If keepalive was lost due to local congestion,&n;&t;&t;&t; * try harder.&n;&t;&t;&t; */
id|elapsed
op_assign
id|TCP_RESOURCE_PROBE_INTERVAL
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* It is tp-&gt;rcv_tstamp + keepalive_time_when(tp) */
id|elapsed
op_assign
id|keepalive_time_when
c_func
(paren
id|tp
)paren
op_minus
id|elapsed
suffix:semicolon
)brace
id|TCP_CHECK_TIMER
c_func
(paren
id|sk
)paren
suffix:semicolon
id|tcp_mem_reclaim
c_func
(paren
id|sk
)paren
suffix:semicolon
id|resched
suffix:colon
id|tcp_reset_keepalive_timer
(paren
id|sk
comma
id|elapsed
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
id|death
suffix:colon
id|tcp_done
c_func
(paren
id|sk
)paren
suffix:semicolon
id|out
suffix:colon
id|bh_unlock_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
id|sock_put
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
eof
