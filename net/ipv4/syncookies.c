multiline_comment|/*&n; *  Syncookies implementation for the Linux kernel&n; *&n; *  Copyright (C) 1997 Andi Kleen&n; *  Based on ideas by D.J.Bernstein and Eric Schenk. &n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *      modify it under the terms of the GNU General Public License&n; *      as published by the Free Software Foundation; either version&n; *      2 of the License, or (at your option) any later version.&n; * &n; *  $Id: syncookies.c,v 1.18 2002/02/01 22:01:04 davem Exp $&n; *&n; *  Missing: IPv6 support. &n; */
macro_line|#include &lt;linux/tcp.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/random.h&gt;
macro_line|#include &lt;linux/cryptohash.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;net/tcp.h&gt;
r_extern
r_int
id|sysctl_tcp_syncookies
suffix:semicolon
DECL|variable|syncookie_secret
r_static
id|__u32
id|syncookie_secret
(braket
l_int|2
)braket
(braket
l_int|16
op_minus
l_int|3
op_plus
id|SHA_DIGEST_WORDS
)braket
suffix:semicolon
DECL|function|init_syncookies
r_static
id|__init
r_int
id|init_syncookies
c_func
(paren
r_void
)paren
(brace
id|get_random_bytes
c_func
(paren
id|syncookie_secret
comma
r_sizeof
(paren
id|syncookie_secret
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|init_syncookies
id|module_init
c_func
(paren
id|init_syncookies
)paren
suffix:semicolon
DECL|macro|COOKIEBITS
mdefine_line|#define COOKIEBITS 24&t;/* Upper bits store count */
DECL|macro|COOKIEMASK
mdefine_line|#define COOKIEMASK (((__u32)1 &lt;&lt; COOKIEBITS) - 1)
DECL|function|cookie_hash
r_static
id|u32
id|cookie_hash
c_func
(paren
id|u32
id|saddr
comma
id|u32
id|daddr
comma
id|u32
id|sport
comma
id|u32
id|dport
comma
id|u32
id|count
comma
r_int
id|c
)paren
(brace
id|__u32
id|tmp
(braket
l_int|16
op_plus
l_int|5
op_plus
id|SHA_WORKSPACE_WORDS
)braket
suffix:semicolon
id|memcpy
c_func
(paren
id|tmp
op_plus
l_int|3
comma
id|syncookie_secret
(braket
id|c
)braket
comma
r_sizeof
(paren
id|syncookie_secret
(braket
id|c
)braket
)paren
)paren
suffix:semicolon
id|tmp
(braket
l_int|0
)braket
op_assign
id|saddr
suffix:semicolon
id|tmp
(braket
l_int|1
)braket
op_assign
id|daddr
suffix:semicolon
id|tmp
(braket
l_int|2
)braket
op_assign
(paren
id|sport
op_lshift
l_int|16
)paren
op_plus
id|dport
suffix:semicolon
id|tmp
(braket
l_int|3
)braket
op_assign
id|count
suffix:semicolon
id|sha_transform
c_func
(paren
id|tmp
op_plus
l_int|16
comma
(paren
id|__u8
op_star
)paren
id|tmp
comma
id|tmp
op_plus
l_int|16
op_plus
l_int|5
)paren
suffix:semicolon
r_return
id|tmp
(braket
l_int|17
)braket
suffix:semicolon
)brace
DECL|function|secure_tcp_syn_cookie
r_static
id|__u32
id|secure_tcp_syn_cookie
c_func
(paren
id|__u32
id|saddr
comma
id|__u32
id|daddr
comma
id|__u16
id|sport
comma
id|__u16
id|dport
comma
id|__u32
id|sseq
comma
id|__u32
id|count
comma
id|__u32
id|data
)paren
(brace
multiline_comment|/*&n;&t; * Compute the secure sequence number.&n;&t; * The output should be:&n;   &t; *   HASH(sec1,saddr,sport,daddr,dport,sec1) + sseq + (count * 2^24)&n;&t; *      + (HASH(sec2,saddr,sport,daddr,dport,count,sec2) % 2^24).&n;&t; * Where sseq is their sequence number and count increases every&n;&t; * minute by 1.&n;&t; * As an extra hack, we add a small &quot;data&quot; value that encodes the&n;&t; * MSS into the second hash value.&n;&t; */
r_return
(paren
id|cookie_hash
c_func
(paren
id|saddr
comma
id|daddr
comma
id|sport
comma
id|dport
comma
l_int|0
comma
l_int|0
)paren
op_plus
id|sseq
op_plus
(paren
id|count
op_lshift
id|COOKIEBITS
)paren
op_plus
(paren
(paren
id|cookie_hash
c_func
(paren
id|saddr
comma
id|daddr
comma
id|sport
comma
id|dport
comma
id|count
comma
l_int|1
)paren
op_plus
id|data
)paren
op_amp
id|COOKIEMASK
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This retrieves the small &quot;data&quot; value from the syncookie.&n; * If the syncookie is bad, the data returned will be out of&n; * range.  This must be checked by the caller.&n; *&n; * The count value used to generate the cookie must be within&n; * &quot;maxdiff&quot; if the current (passed-in) &quot;count&quot;.  The return value&n; * is (__u32)-1 if this test fails.&n; */
DECL|function|check_tcp_syn_cookie
r_static
id|__u32
id|check_tcp_syn_cookie
c_func
(paren
id|__u32
id|cookie
comma
id|__u32
id|saddr
comma
id|__u32
id|daddr
comma
id|__u16
id|sport
comma
id|__u16
id|dport
comma
id|__u32
id|sseq
comma
id|__u32
id|count
comma
id|__u32
id|maxdiff
)paren
(brace
id|__u32
id|diff
suffix:semicolon
multiline_comment|/* Strip away the layers from the cookie */
id|cookie
op_sub_assign
id|cookie_hash
c_func
(paren
id|saddr
comma
id|daddr
comma
id|sport
comma
id|dport
comma
l_int|0
comma
l_int|0
)paren
op_plus
id|sseq
suffix:semicolon
multiline_comment|/* Cookie is now reduced to (count * 2^24) ^ (hash % 2^24) */
id|diff
op_assign
(paren
id|count
op_minus
(paren
id|cookie
op_rshift
id|COOKIEBITS
)paren
)paren
op_amp
(paren
(paren
id|__u32
)paren
op_minus
l_int|1
op_rshift
id|COOKIEBITS
)paren
suffix:semicolon
r_if
c_cond
(paren
id|diff
op_ge
id|maxdiff
)paren
r_return
(paren
id|__u32
)paren
op_minus
l_int|1
suffix:semicolon
r_return
(paren
id|cookie
op_minus
id|cookie_hash
c_func
(paren
id|saddr
comma
id|daddr
comma
id|sport
comma
id|dport
comma
id|count
op_minus
id|diff
comma
l_int|1
)paren
)paren
op_amp
id|COOKIEMASK
suffix:semicolon
multiline_comment|/* Leaving the data behind */
)brace
multiline_comment|/* &n; * This table has to be sorted and terminated with (__u16)-1.&n; * XXX generate a better table.&n; * Unresolved Issues: HIPPI with a 64k MSS is not well supported.&n; */
DECL|variable|msstab
r_static
id|__u16
r_const
id|msstab
(braket
)braket
op_assign
(brace
l_int|64
op_minus
l_int|1
comma
l_int|256
op_minus
l_int|1
comma
l_int|512
op_minus
l_int|1
comma
l_int|536
op_minus
l_int|1
comma
l_int|1024
op_minus
l_int|1
comma
l_int|1440
op_minus
l_int|1
comma
l_int|1460
op_minus
l_int|1
comma
l_int|4312
op_minus
l_int|1
comma
(paren
id|__u16
)paren
op_minus
l_int|1
)brace
suffix:semicolon
multiline_comment|/* The number doesn&squot;t include the -1 terminator */
DECL|macro|NUM_MSS
mdefine_line|#define NUM_MSS (ARRAY_SIZE(msstab) - 1)
multiline_comment|/*&n; * Generate a syncookie.  mssp points to the mss, which is returned&n; * rounded down to the value encoded in the cookie.&n; */
DECL|function|cookie_v4_init_sequence
id|__u32
id|cookie_v4_init_sequence
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_struct
id|sk_buff
op_star
id|skb
comma
id|__u16
op_star
id|mssp
)paren
(brace
r_struct
id|tcp_sock
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
id|mssind
suffix:semicolon
r_const
id|__u16
id|mss
op_assign
op_star
id|mssp
suffix:semicolon
id|tp-&gt;last_synq_overflow
op_assign
id|jiffies
suffix:semicolon
multiline_comment|/* XXX sort msstab[] by probability?  Binary search? */
r_for
c_loop
(paren
id|mssind
op_assign
l_int|0
suffix:semicolon
id|mss
OG
id|msstab
(braket
id|mssind
op_plus
l_int|1
)braket
suffix:semicolon
id|mssind
op_increment
)paren
suffix:semicolon
op_star
id|mssp
op_assign
id|msstab
(braket
id|mssind
)braket
op_plus
l_int|1
suffix:semicolon
id|NET_INC_STATS_BH
c_func
(paren
id|LINUX_MIB_SYNCOOKIESSENT
)paren
suffix:semicolon
r_return
id|secure_tcp_syn_cookie
c_func
(paren
id|skb-&gt;nh.iph-&gt;saddr
comma
id|skb-&gt;nh.iph-&gt;daddr
comma
id|skb-&gt;h.th-&gt;source
comma
id|skb-&gt;h.th-&gt;dest
comma
id|ntohl
c_func
(paren
id|skb-&gt;h.th-&gt;seq
)paren
comma
id|jiffies
op_div
(paren
id|HZ
op_star
l_int|60
)paren
comma
id|mssind
)paren
suffix:semicolon
)brace
multiline_comment|/* &n; * This (misnamed) value is the age of syncookie which is permitted.&n; * Its ideal value should be dependent on TCP_TIMEOUT_INIT and&n; * sysctl_tcp_retries1. It&squot;s a rather complicated formula (exponential&n; * backoff) to compute at runtime so it&squot;s currently hardcoded here.&n; */
DECL|macro|COUNTER_TRIES
mdefine_line|#define COUNTER_TRIES 4
multiline_comment|/*  &n; * Check if a ack sequence number is a valid syncookie. &n; * Return the decoded mss if it is, or 0 if not.&n; */
DECL|function|cookie_check
r_static
r_inline
r_int
id|cookie_check
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
id|__u32
id|cookie
)paren
(brace
id|__u32
id|seq
suffix:semicolon
id|__u32
id|mssind
suffix:semicolon
id|seq
op_assign
id|ntohl
c_func
(paren
id|skb-&gt;h.th-&gt;seq
)paren
op_minus
l_int|1
suffix:semicolon
id|mssind
op_assign
id|check_tcp_syn_cookie
c_func
(paren
id|cookie
comma
id|skb-&gt;nh.iph-&gt;saddr
comma
id|skb-&gt;nh.iph-&gt;daddr
comma
id|skb-&gt;h.th-&gt;source
comma
id|skb-&gt;h.th-&gt;dest
comma
id|seq
comma
id|jiffies
op_div
(paren
id|HZ
op_star
l_int|60
)paren
comma
id|COUNTER_TRIES
)paren
suffix:semicolon
r_return
id|mssind
OL
id|NUM_MSS
ques
c_cond
id|msstab
(braket
id|mssind
)braket
op_plus
l_int|1
suffix:colon
l_int|0
suffix:semicolon
)brace
r_extern
r_struct
id|or_calltable
id|or_ipv4
suffix:semicolon
DECL|function|get_cookie_sock
r_static
r_inline
r_struct
id|sock
op_star
id|get_cookie_sock
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|open_request
op_star
id|req
comma
r_struct
id|dst_entry
op_star
id|dst
)paren
(brace
r_struct
id|tcp_sock
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
id|sock
op_star
id|child
suffix:semicolon
id|child
op_assign
id|tp-&gt;af_specific
op_member_access_from_pointer
id|syn_recv_sock
c_func
(paren
id|sk
comma
id|skb
comma
id|req
comma
id|dst
)paren
suffix:semicolon
r_if
c_cond
(paren
id|child
)paren
(brace
id|sk_set_owner
c_func
(paren
id|child
comma
id|sk-&gt;sk_owner
)paren
suffix:semicolon
id|tcp_acceptq_queue
c_func
(paren
id|sk
comma
id|req
comma
id|child
)paren
suffix:semicolon
)brace
r_else
id|tcp_openreq_free
c_func
(paren
id|req
)paren
suffix:semicolon
r_return
id|child
suffix:semicolon
)brace
DECL|function|cookie_v4_check
r_struct
id|sock
op_star
id|cookie_v4_check
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|ip_options
op_star
id|opt
)paren
(brace
r_struct
id|tcp_sock
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
id|cookie
op_assign
id|ntohl
c_func
(paren
id|skb-&gt;h.th-&gt;ack_seq
)paren
op_minus
l_int|1
suffix:semicolon
r_struct
id|sock
op_star
id|ret
op_assign
id|sk
suffix:semicolon
r_struct
id|open_request
op_star
id|req
suffix:semicolon
r_int
id|mss
suffix:semicolon
r_struct
id|rtable
op_star
id|rt
suffix:semicolon
id|__u8
id|rcv_wscale
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sysctl_tcp_syncookies
op_logical_or
op_logical_neg
id|skb-&gt;h.th-&gt;ack
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|time_after
c_func
(paren
id|jiffies
comma
id|tp-&gt;last_synq_overflow
op_plus
id|TCP_TIMEOUT_INIT
)paren
op_logical_or
(paren
id|mss
op_assign
id|cookie_check
c_func
(paren
id|skb
comma
id|cookie
)paren
)paren
op_eq
l_int|0
)paren
(brace
id|NET_INC_STATS_BH
c_func
(paren
id|LINUX_MIB_SYNCOOKIESFAILED
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|NET_INC_STATS_BH
c_func
(paren
id|LINUX_MIB_SYNCOOKIESRECV
)paren
suffix:semicolon
id|req
op_assign
id|tcp_openreq_alloc
c_func
(paren
)paren
suffix:semicolon
id|ret
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|req
)paren
r_goto
id|out
suffix:semicolon
id|req-&gt;rcv_isn
op_assign
id|htonl
c_func
(paren
id|skb-&gt;h.th-&gt;seq
)paren
op_minus
l_int|1
suffix:semicolon
id|req-&gt;snt_isn
op_assign
id|cookie
suffix:semicolon
id|req-&gt;mss
op_assign
id|mss
suffix:semicolon
id|req-&gt;rmt_port
op_assign
id|skb-&gt;h.th-&gt;source
suffix:semicolon
id|req-&gt;af.v4_req.loc_addr
op_assign
id|skb-&gt;nh.iph-&gt;daddr
suffix:semicolon
id|req-&gt;af.v4_req.rmt_addr
op_assign
id|skb-&gt;nh.iph-&gt;saddr
suffix:semicolon
id|req
op_member_access_from_pointer
r_class
op_assign
op_amp
id|or_ipv4
suffix:semicolon
multiline_comment|/* for savety */
id|req-&gt;af.v4_req.opt
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* We throwed the options of the initial SYN away, so we hope&n;&t; * the ACK carries the same options again (see RFC1122 4.2.3.8)&n;&t; */
r_if
c_cond
(paren
id|opt
op_logical_and
id|opt-&gt;optlen
)paren
(brace
r_int
id|opt_size
op_assign
r_sizeof
(paren
r_struct
id|ip_options
)paren
op_plus
id|opt-&gt;optlen
suffix:semicolon
id|req-&gt;af.v4_req.opt
op_assign
id|kmalloc
c_func
(paren
id|opt_size
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|req-&gt;af.v4_req.opt
)paren
(brace
r_if
c_cond
(paren
id|ip_options_echo
c_func
(paren
id|req-&gt;af.v4_req.opt
comma
id|skb
)paren
)paren
(brace
id|kfree
c_func
(paren
id|req-&gt;af.v4_req.opt
)paren
suffix:semicolon
id|req-&gt;af.v4_req.opt
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
)brace
id|req-&gt;snd_wscale
op_assign
id|req-&gt;rcv_wscale
op_assign
id|req-&gt;tstamp_ok
op_assign
l_int|0
suffix:semicolon
id|req-&gt;wscale_ok
op_assign
id|req-&gt;sack_ok
op_assign
l_int|0
suffix:semicolon
id|req-&gt;expires
op_assign
l_int|0UL
suffix:semicolon
id|req-&gt;retrans
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * We need to lookup the route here to get at the correct&n;&t; * window size. We should better make sure that the window size&n;&t; * hasn&squot;t changed since we received the original syn, but I see&n;&t; * no easy way to do this. &n;&t; */
(brace
r_struct
id|flowi
id|fl
op_assign
(brace
dot
id|nl_u
op_assign
(brace
dot
id|ip4_u
op_assign
(brace
dot
id|daddr
op_assign
(paren
(paren
id|opt
op_logical_and
id|opt-&gt;srr
)paren
ques
c_cond
id|opt-&gt;faddr
suffix:colon
id|req-&gt;af.v4_req.rmt_addr
)paren
comma
dot
id|saddr
op_assign
id|req-&gt;af.v4_req.loc_addr
comma
dot
id|tos
op_assign
id|RT_CONN_FLAGS
c_func
(paren
id|sk
)paren
)brace
)brace
comma
dot
id|proto
op_assign
id|IPPROTO_TCP
comma
dot
id|uli_u
op_assign
(brace
dot
id|ports
op_assign
(brace
dot
id|sport
op_assign
id|skb-&gt;h.th-&gt;dest
comma
dot
id|dport
op_assign
id|skb-&gt;h.th-&gt;source
)brace
)brace
)brace
suffix:semicolon
r_if
c_cond
(paren
id|ip_route_output_key
c_func
(paren
op_amp
id|rt
comma
op_amp
id|fl
)paren
)paren
(brace
id|tcp_openreq_free
c_func
(paren
id|req
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
)brace
multiline_comment|/* Try to redo what tcp_v4_send_synack did. */
id|req-&gt;window_clamp
op_assign
id|dst_metric
c_func
(paren
op_amp
id|rt-&gt;u.dst
comma
id|RTAX_WINDOW
)paren
suffix:semicolon
id|tcp_select_initial_window
c_func
(paren
id|tcp_full_space
c_func
(paren
id|sk
)paren
comma
id|req-&gt;mss
comma
op_amp
id|req-&gt;rcv_wnd
comma
op_amp
id|req-&gt;window_clamp
comma
l_int|0
comma
op_amp
id|rcv_wscale
)paren
suffix:semicolon
multiline_comment|/* BTW win scale with syncookies is 0 by definition */
id|req-&gt;rcv_wscale
op_assign
id|rcv_wscale
suffix:semicolon
id|ret
op_assign
id|get_cookie_sock
c_func
(paren
id|sk
comma
id|skb
comma
id|req
comma
op_amp
id|rt-&gt;u.dst
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|ret
suffix:semicolon
)brace
eof
