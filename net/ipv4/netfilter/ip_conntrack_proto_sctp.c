multiline_comment|/*&n; * Connection tracking protocol helper module for SCTP.&n; * &n; * SCTP is defined in RFC 2960. References to various sections in this code &n; * are to this RFC.&n; * &n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
multiline_comment|/*&n; * Added support for proc manipulation of timeouts.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/netfilter.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/ip.h&gt;
macro_line|#include &lt;linux/sctp.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_conntrack.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_conntrack_protocol.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/lockhelp.h&gt;
macro_line|#if 0
mdefine_line|#define DEBUGP(format, ...) printk(format, ## __VA_ARGS__)
macro_line|#else
DECL|macro|DEBUGP
mdefine_line|#define DEBUGP(format, args...)
macro_line|#endif
multiline_comment|/* Protects conntrack-&gt;proto.sctp */
r_static
id|DECLARE_RWLOCK
c_func
(paren
id|sctp_lock
)paren
suffix:semicolon
multiline_comment|/* FIXME: Examine ipfilter&squot;s timeouts and conntrack transitions more&n;   closely.  They&squot;re more complex. --RR &n;&n;   And so for me for SCTP :D -Kiran */
DECL|variable|sctp_conntrack_names
r_static
r_const
r_char
op_star
id|sctp_conntrack_names
(braket
)braket
op_assign
(brace
l_string|&quot;NONE&quot;
comma
l_string|&quot;CLOSED&quot;
comma
l_string|&quot;COOKIE_WAIT&quot;
comma
l_string|&quot;COOKIE_ECHOED&quot;
comma
l_string|&quot;ESTABLISHED&quot;
comma
l_string|&quot;SHUTDOWN_SENT&quot;
comma
l_string|&quot;SHUTDOWN_RECD&quot;
comma
l_string|&quot;SHUTDOWN_ACK_SENT&quot;
comma
)brace
suffix:semicolon
DECL|macro|SECS
mdefine_line|#define SECS  * HZ
DECL|macro|MINS
mdefine_line|#define MINS  * 60 SECS
DECL|macro|HOURS
mdefine_line|#define HOURS * 60 MINS
DECL|macro|DAYS
mdefine_line|#define DAYS  * 24 HOURS
DECL|variable|ip_ct_sctp_timeout_closed
r_int
r_int
id|ip_ct_sctp_timeout_closed
op_assign
l_int|10
id|SECS
suffix:semicolon
DECL|variable|ip_ct_sctp_timeout_cookie_wait
r_int
r_int
id|ip_ct_sctp_timeout_cookie_wait
op_assign
l_int|3
id|SECS
suffix:semicolon
DECL|variable|ip_ct_sctp_timeout_cookie_echoed
r_int
r_int
id|ip_ct_sctp_timeout_cookie_echoed
op_assign
l_int|3
id|SECS
suffix:semicolon
DECL|variable|ip_ct_sctp_timeout_established
r_int
r_int
id|ip_ct_sctp_timeout_established
op_assign
l_int|5
id|DAYS
suffix:semicolon
DECL|variable|ip_ct_sctp_timeout_shutdown_sent
r_int
r_int
id|ip_ct_sctp_timeout_shutdown_sent
op_assign
l_int|300
id|SECS
op_div
l_int|1000
suffix:semicolon
DECL|variable|ip_ct_sctp_timeout_shutdown_recd
r_int
r_int
id|ip_ct_sctp_timeout_shutdown_recd
op_assign
l_int|300
id|SECS
op_div
l_int|1000
suffix:semicolon
DECL|variable|ip_ct_sctp_timeout_shutdown_ack_sent
r_int
r_int
id|ip_ct_sctp_timeout_shutdown_ack_sent
op_assign
l_int|3
id|SECS
suffix:semicolon
DECL|variable|sctp_timeouts
r_static
r_int
r_int
op_star
id|sctp_timeouts
(braket
)braket
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* SCTP_CONNTRACK_NONE  */
op_amp
id|ip_ct_sctp_timeout_closed
comma
multiline_comment|/* SCTP_CONNTRACK_CLOSED */
op_amp
id|ip_ct_sctp_timeout_cookie_wait
comma
multiline_comment|/* SCTP_CONNTRACK_COOKIE_WAIT */
op_amp
id|ip_ct_sctp_timeout_cookie_echoed
comma
multiline_comment|/* SCTP_CONNTRACK_COOKIE_ECHOED */
op_amp
id|ip_ct_sctp_timeout_established
comma
multiline_comment|/* SCTP_CONNTRACK_ESTABLISHED */
op_amp
id|ip_ct_sctp_timeout_shutdown_sent
comma
multiline_comment|/* SCTP_CONNTRACK_SHUTDOWN_SENT */
op_amp
id|ip_ct_sctp_timeout_shutdown_recd
comma
multiline_comment|/* SCTP_CONNTRACK_SHUTDOWN_RECD */
op_amp
id|ip_ct_sctp_timeout_shutdown_ack_sent
multiline_comment|/* SCTP_CONNTRACK_SHUTDOWN_ACK_SENT */
)brace
suffix:semicolon
DECL|macro|sNO
mdefine_line|#define sNO SCTP_CONNTRACK_NONE
DECL|macro|sCL
mdefine_line|#define&t;sCL SCTP_CONNTRACK_CLOSED
DECL|macro|sCW
mdefine_line|#define&t;sCW SCTP_CONNTRACK_COOKIE_WAIT
DECL|macro|sCE
mdefine_line|#define&t;sCE SCTP_CONNTRACK_COOKIE_ECHOED
DECL|macro|sES
mdefine_line|#define&t;sES SCTP_CONNTRACK_ESTABLISHED
DECL|macro|sSS
mdefine_line|#define&t;sSS SCTP_CONNTRACK_SHUTDOWN_SENT
DECL|macro|sSR
mdefine_line|#define&t;sSR SCTP_CONNTRACK_SHUTDOWN_RECD
DECL|macro|sSA
mdefine_line|#define&t;sSA SCTP_CONNTRACK_SHUTDOWN_ACK_SENT
DECL|macro|sIV
mdefine_line|#define&t;sIV SCTP_CONNTRACK_MAX
multiline_comment|/* &n;&t;These are the descriptions of the states:&n;&n;NOTE: These state names are tantalizingly similar to the states of an &n;SCTP endpoint. But the interpretation of the states is a little different,&n;considering that these are the states of the connection and not of an end &n;point. Please note the subtleties. -Kiran&n;&n;NONE              - Nothing so far.&n;COOKIE WAIT       - We have seen an INIT chunk in the original direction, or also &n;                    an INIT_ACK chunk in the reply direction.&n;COOKIE ECHOED     - We have seen a COOKIE_ECHO chunk in the original direction.&n;ESTABLISHED       - We have seen a COOKIE_ACK in the reply direction.&n;SHUTDOWN_SENT     - We have seen a SHUTDOWN chunk in the original direction.&n;SHUTDOWN_RECD     - We have seen a SHUTDOWN chunk in the reply directoin.&n;SHUTDOWN_ACK_SENT - We have seen a SHUTDOWN_ACK chunk in the direction opposite&n;                    to that of the SHUTDOWN chunk.&n;CLOSED            - We have seen a SHUTDOWN_COMPLETE chunk in the direction of &n;                    the SHUTDOWN chunk. Connection is closed.&n;*/
multiline_comment|/* TODO&n; - I have assumed that the first INIT is in the original direction. &n; This messes things when an INIT comes in the reply direction in CLOSED&n; state.&n; - Check the error type in the reply dir before transitioning from &n;cookie echoed to closed.&n; - Sec 5.2.4 of RFC 2960&n; - Multi Homing support.&n;*/
multiline_comment|/* SCTP conntrack state transitions */
DECL|variable|sctp_conntracks
r_static
r_enum
id|sctp_conntrack
id|sctp_conntracks
(braket
l_int|2
)braket
(braket
l_int|9
)braket
(braket
id|SCTP_CONNTRACK_MAX
)braket
op_assign
(brace
(brace
multiline_comment|/*&t;ORIGINAL&t;*/
multiline_comment|/*                  sNO, sCL, sCW, sCE, sES, sSS, sSR, sSA */
multiline_comment|/* init         */
(brace
id|sCW
comma
id|sCW
comma
id|sCW
comma
id|sCE
comma
id|sES
comma
id|sSS
comma
id|sSR
comma
id|sSA
)brace
comma
multiline_comment|/* init_ack     */
(brace
id|sCL
comma
id|sCL
comma
id|sCW
comma
id|sCE
comma
id|sES
comma
id|sSS
comma
id|sSR
comma
id|sSA
)brace
comma
multiline_comment|/* abort        */
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
)brace
comma
multiline_comment|/* shutdown     */
(brace
id|sCL
comma
id|sCL
comma
id|sCW
comma
id|sCE
comma
id|sSS
comma
id|sSS
comma
id|sSR
comma
id|sSA
)brace
comma
multiline_comment|/* shutdown_ack */
(brace
id|sSA
comma
id|sCL
comma
id|sCW
comma
id|sCE
comma
id|sES
comma
id|sSA
comma
id|sSA
comma
id|sSA
)brace
comma
multiline_comment|/* error        */
(brace
id|sCL
comma
id|sCL
comma
id|sCW
comma
id|sCE
comma
id|sES
comma
id|sSS
comma
id|sSR
comma
id|sSA
)brace
comma
multiline_comment|/* Cant have Stale cookie*/
multiline_comment|/* cookie_echo  */
(brace
id|sCL
comma
id|sCL
comma
id|sCE
comma
id|sCE
comma
id|sES
comma
id|sSS
comma
id|sSR
comma
id|sSA
)brace
comma
multiline_comment|/* 5.2.4 - Big TODO */
multiline_comment|/* cookie_ack   */
(brace
id|sCL
comma
id|sCL
comma
id|sCW
comma
id|sCE
comma
id|sES
comma
id|sSS
comma
id|sSR
comma
id|sSA
)brace
comma
multiline_comment|/* Cant come in orig dir */
multiline_comment|/* shutdown_comp*/
(brace
id|sCL
comma
id|sCL
comma
id|sCW
comma
id|sCE
comma
id|sES
comma
id|sSS
comma
id|sSR
comma
id|sCL
)brace
)brace
comma
(brace
multiline_comment|/*&t;REPLY&t;*/
multiline_comment|/*                  sNO, sCL, sCW, sCE, sES, sSS, sSR, sSA */
multiline_comment|/* init         */
(brace
id|sIV
comma
id|sCL
comma
id|sCW
comma
id|sCE
comma
id|sES
comma
id|sSS
comma
id|sSR
comma
id|sSA
)brace
comma
multiline_comment|/* INIT in sCL Big TODO */
multiline_comment|/* init_ack     */
(brace
id|sIV
comma
id|sCL
comma
id|sCW
comma
id|sCE
comma
id|sES
comma
id|sSS
comma
id|sSR
comma
id|sSA
)brace
comma
multiline_comment|/* abort        */
(brace
id|sIV
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
)brace
comma
multiline_comment|/* shutdown     */
(brace
id|sIV
comma
id|sCL
comma
id|sCW
comma
id|sCE
comma
id|sSR
comma
id|sSS
comma
id|sSR
comma
id|sSA
)brace
comma
multiline_comment|/* shutdown_ack */
(brace
id|sIV
comma
id|sCL
comma
id|sCW
comma
id|sCE
comma
id|sES
comma
id|sSA
comma
id|sSA
comma
id|sSA
)brace
comma
multiline_comment|/* error        */
(brace
id|sIV
comma
id|sCL
comma
id|sCW
comma
id|sCL
comma
id|sES
comma
id|sSS
comma
id|sSR
comma
id|sSA
)brace
comma
multiline_comment|/* cookie_echo  */
(brace
id|sIV
comma
id|sCL
comma
id|sCW
comma
id|sCE
comma
id|sES
comma
id|sSS
comma
id|sSR
comma
id|sSA
)brace
comma
multiline_comment|/* Cant come in reply dir */
multiline_comment|/* cookie_ack   */
(brace
id|sIV
comma
id|sCL
comma
id|sCW
comma
id|sES
comma
id|sES
comma
id|sSS
comma
id|sSR
comma
id|sSA
)brace
comma
multiline_comment|/* shutdown_comp*/
(brace
id|sIV
comma
id|sCL
comma
id|sCW
comma
id|sCE
comma
id|sES
comma
id|sSS
comma
id|sSR
comma
id|sCL
)brace
)brace
)brace
suffix:semicolon
DECL|function|sctp_pkt_to_tuple
r_static
r_int
id|sctp_pkt_to_tuple
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
id|sctp_sctphdr_t
id|_hdr
comma
op_star
id|hp
suffix:semicolon
id|DEBUGP
c_func
(paren
id|__FUNCTION__
)paren
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Actually only need first 8 bytes. */
id|hp
op_assign
id|skb_header_pointer
c_func
(paren
id|skb
comma
id|dataoff
comma
l_int|8
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
r_return
l_int|0
suffix:semicolon
id|tuple-&gt;src.u.sctp.port
op_assign
id|hp-&gt;source
suffix:semicolon
id|tuple-&gt;dst.u.sctp.port
op_assign
id|hp-&gt;dest
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|sctp_invert_tuple
r_static
r_int
id|sctp_invert_tuple
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
id|DEBUGP
c_func
(paren
id|__FUNCTION__
)paren
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|tuple-&gt;src.u.sctp.port
op_assign
id|orig-&gt;dst.u.sctp.port
suffix:semicolon
id|tuple-&gt;dst.u.sctp.port
op_assign
id|orig-&gt;src.u.sctp.port
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Print out the per-protocol part of the tuple. */
DECL|function|sctp_print_tuple
r_static
r_int
id|sctp_print_tuple
c_func
(paren
r_struct
id|seq_file
op_star
id|s
comma
r_const
r_struct
id|ip_conntrack_tuple
op_star
id|tuple
)paren
(brace
id|DEBUGP
c_func
(paren
id|__FUNCTION__
)paren
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|seq_printf
c_func
(paren
id|s
comma
l_string|&quot;sport=%hu dport=%hu &quot;
comma
id|ntohs
c_func
(paren
id|tuple-&gt;src.u.sctp.port
)paren
comma
id|ntohs
c_func
(paren
id|tuple-&gt;dst.u.sctp.port
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Print out the private part of the conntrack. */
DECL|function|sctp_print_conntrack
r_static
r_int
id|sctp_print_conntrack
c_func
(paren
r_struct
id|seq_file
op_star
id|s
comma
r_const
r_struct
id|ip_conntrack
op_star
id|conntrack
)paren
(brace
r_enum
id|sctp_conntrack
id|state
suffix:semicolon
id|DEBUGP
c_func
(paren
id|__FUNCTION__
)paren
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|READ_LOCK
c_func
(paren
op_amp
id|sctp_lock
)paren
suffix:semicolon
id|state
op_assign
id|conntrack-&gt;proto.sctp.state
suffix:semicolon
id|READ_UNLOCK
c_func
(paren
op_amp
id|sctp_lock
)paren
suffix:semicolon
r_return
id|seq_printf
c_func
(paren
id|s
comma
l_string|&quot;%s &quot;
comma
id|sctp_conntrack_names
(braket
id|state
)braket
)paren
suffix:semicolon
)brace
DECL|macro|for_each_sctp_chunk
mdefine_line|#define for_each_sctp_chunk(skb, sch, _sch, offset, count)&t;&t;&bslash;&n;for (offset = skb-&gt;nh.iph-&gt;ihl * 4 + sizeof(sctp_sctphdr_t), count = 0;&t;&bslash;&n;&t;offset &lt; skb-&gt;len &amp;&amp;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(sch = skb_header_pointer(skb, offset, sizeof(_sch), &amp;_sch));&t;&bslash;&n;&t;offset += (htons(sch-&gt;length) + 3) &amp; ~3, count++)
multiline_comment|/* Some validity checks to make sure the chunks are fine */
DECL|function|do_basic_checks
r_static
r_int
id|do_basic_checks
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
r_char
op_star
id|map
)paren
(brace
id|u_int32_t
id|offset
comma
id|count
suffix:semicolon
id|sctp_chunkhdr_t
id|_sch
comma
op_star
id|sch
suffix:semicolon
r_int
id|flag
suffix:semicolon
id|DEBUGP
c_func
(paren
id|__FUNCTION__
)paren
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|flag
op_assign
l_int|0
suffix:semicolon
id|for_each_sctp_chunk
(paren
id|skb
comma
id|sch
comma
id|_sch
comma
id|offset
comma
id|count
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;Chunk Num: %d  Type: %d&bslash;n&quot;
comma
id|count
comma
id|sch-&gt;type
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sch-&gt;type
op_eq
id|SCTP_CID_INIT
op_logical_or
id|sch-&gt;type
op_eq
id|SCTP_CID_INIT_ACK
op_logical_or
id|sch-&gt;type
op_eq
id|SCTP_CID_SHUTDOWN_COMPLETE
)paren
(brace
id|flag
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Cookie Ack/Echo chunks not the first OR &n;&t;&t;   Init / Init Ack / Shutdown compl chunks not the only chunks */
r_if
c_cond
(paren
(paren
id|sch-&gt;type
op_eq
id|SCTP_CID_COOKIE_ACK
op_logical_or
id|sch-&gt;type
op_eq
id|SCTP_CID_COOKIE_ECHO
op_logical_or
id|flag
)paren
op_logical_and
id|count
op_ne
l_int|0
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;Basic checks failed&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|map
)paren
(brace
id|set_bit
c_func
(paren
id|sch-&gt;type
comma
(paren
r_void
op_star
)paren
id|map
)paren
suffix:semicolon
)brace
)brace
id|DEBUGP
c_func
(paren
l_string|&quot;Basic checks passed&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|new_state
r_static
r_int
id|new_state
c_func
(paren
r_enum
id|ip_conntrack_dir
id|dir
comma
r_enum
id|sctp_conntrack
id|cur_state
comma
r_int
id|chunk_type
)paren
(brace
r_int
id|i
suffix:semicolon
id|DEBUGP
c_func
(paren
id|__FUNCTION__
)paren
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;Chunk type: %d&bslash;n&quot;
comma
id|chunk_type
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|chunk_type
)paren
(brace
r_case
id|SCTP_CID_INIT
suffix:colon
id|DEBUGP
c_func
(paren
l_string|&quot;SCTP_CID_INIT&bslash;n&quot;
)paren
suffix:semicolon
id|i
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SCTP_CID_INIT_ACK
suffix:colon
id|DEBUGP
c_func
(paren
l_string|&quot;SCTP_CID_INIT_ACK&bslash;n&quot;
)paren
suffix:semicolon
id|i
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SCTP_CID_ABORT
suffix:colon
id|DEBUGP
c_func
(paren
l_string|&quot;SCTP_CID_ABORT&bslash;n&quot;
)paren
suffix:semicolon
id|i
op_assign
l_int|2
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SCTP_CID_SHUTDOWN
suffix:colon
id|DEBUGP
c_func
(paren
l_string|&quot;SCTP_CID_SHUTDOWN&bslash;n&quot;
)paren
suffix:semicolon
id|i
op_assign
l_int|3
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SCTP_CID_SHUTDOWN_ACK
suffix:colon
id|DEBUGP
c_func
(paren
l_string|&quot;SCTP_CID_SHUTDOWN_ACK&bslash;n&quot;
)paren
suffix:semicolon
id|i
op_assign
l_int|4
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SCTP_CID_ERROR
suffix:colon
id|DEBUGP
c_func
(paren
l_string|&quot;SCTP_CID_ERROR&bslash;n&quot;
)paren
suffix:semicolon
id|i
op_assign
l_int|5
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SCTP_CID_COOKIE_ECHO
suffix:colon
id|DEBUGP
c_func
(paren
l_string|&quot;SCTP_CID_COOKIE_ECHO&bslash;n&quot;
)paren
suffix:semicolon
id|i
op_assign
l_int|6
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SCTP_CID_COOKIE_ACK
suffix:colon
id|DEBUGP
c_func
(paren
l_string|&quot;SCTP_CID_COOKIE_ACK&bslash;n&quot;
)paren
suffix:semicolon
id|i
op_assign
l_int|7
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SCTP_CID_SHUTDOWN_COMPLETE
suffix:colon
id|DEBUGP
c_func
(paren
l_string|&quot;SCTP_CID_SHUTDOWN_COMPLETE&bslash;n&quot;
)paren
suffix:semicolon
id|i
op_assign
l_int|8
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* Other chunks like DATA, SACK, HEARTBEAT and&n;&t;&t;&t;its ACK do not cause a change in state */
id|DEBUGP
c_func
(paren
l_string|&quot;Unknown chunk type, Will stay in %s&bslash;n&quot;
comma
id|sctp_conntrack_names
(braket
id|cur_state
)braket
)paren
suffix:semicolon
r_return
id|cur_state
suffix:semicolon
)brace
id|DEBUGP
c_func
(paren
l_string|&quot;dir: %d   cur_state: %s  chunk_type: %d  new_state: %s&bslash;n&quot;
comma
id|dir
comma
id|sctp_conntrack_names
(braket
id|cur_state
)braket
comma
id|chunk_type
comma
id|sctp_conntrack_names
(braket
id|sctp_conntracks
(braket
id|dir
)braket
(braket
id|i
)braket
(braket
id|cur_state
)braket
)braket
)paren
suffix:semicolon
r_return
id|sctp_conntracks
(braket
id|dir
)braket
(braket
id|i
)braket
(braket
id|cur_state
)braket
suffix:semicolon
)brace
multiline_comment|/* Returns verdict for packet, or -1 for invalid. */
DECL|function|sctp_packet
r_static
r_int
id|sctp_packet
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
id|sctp_conntrack
id|newconntrack
comma
id|oldsctpstate
suffix:semicolon
r_struct
id|iphdr
op_star
id|iph
op_assign
id|skb-&gt;nh.iph
suffix:semicolon
id|sctp_sctphdr_t
id|_sctph
comma
op_star
id|sh
suffix:semicolon
id|sctp_chunkhdr_t
id|_sch
comma
op_star
id|sch
suffix:semicolon
id|u_int32_t
id|offset
comma
id|count
suffix:semicolon
r_char
id|map
(braket
l_int|256
op_div
r_sizeof
(paren
r_char
)paren
)braket
op_assign
(brace
l_int|0
)brace
suffix:semicolon
id|DEBUGP
c_func
(paren
id|__FUNCTION__
)paren
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|sh
op_assign
id|skb_header_pointer
c_func
(paren
id|skb
comma
id|iph-&gt;ihl
op_star
l_int|4
comma
r_sizeof
(paren
id|_sctph
)paren
comma
op_amp
id|_sctph
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sh
op_eq
l_int|NULL
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|do_basic_checks
c_func
(paren
id|conntrack
comma
id|skb
comma
id|map
)paren
op_ne
l_int|0
)paren
r_return
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* Check the verification tag (Sec 8.5) */
r_if
c_cond
(paren
op_logical_neg
id|test_bit
c_func
(paren
id|SCTP_CID_INIT
comma
(paren
r_void
op_star
)paren
id|map
)paren
op_logical_and
op_logical_neg
id|test_bit
c_func
(paren
id|SCTP_CID_SHUTDOWN_COMPLETE
comma
(paren
r_void
op_star
)paren
id|map
)paren
op_logical_and
op_logical_neg
id|test_bit
c_func
(paren
id|SCTP_CID_COOKIE_ECHO
comma
(paren
r_void
op_star
)paren
id|map
)paren
op_logical_and
op_logical_neg
id|test_bit
c_func
(paren
id|SCTP_CID_ABORT
comma
(paren
r_void
op_star
)paren
id|map
)paren
op_logical_and
op_logical_neg
id|test_bit
c_func
(paren
id|SCTP_CID_SHUTDOWN_ACK
comma
(paren
r_void
op_star
)paren
id|map
)paren
op_logical_and
(paren
id|sh-&gt;vtag
op_ne
id|conntrack-&gt;proto.sctp.vtag
(braket
id|CTINFO2DIR
c_func
(paren
id|ctinfo
)paren
)braket
)paren
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;Verification tag check failed&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|oldsctpstate
op_assign
id|newconntrack
op_assign
id|SCTP_CONNTRACK_MAX
suffix:semicolon
id|for_each_sctp_chunk
(paren
id|skb
comma
id|sch
comma
id|_sch
comma
id|offset
comma
id|count
)paren
(brace
id|WRITE_LOCK
c_func
(paren
op_amp
id|sctp_lock
)paren
suffix:semicolon
multiline_comment|/* Special cases of Verification tag check (Sec 8.5.1) */
r_if
c_cond
(paren
id|sch-&gt;type
op_eq
id|SCTP_CID_INIT
)paren
(brace
multiline_comment|/* Sec 8.5.1 (A) */
r_if
c_cond
(paren
id|sh-&gt;vtag
op_ne
l_int|0
)paren
(brace
id|WRITE_UNLOCK
c_func
(paren
op_amp
id|sctp_lock
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|sch-&gt;type
op_eq
id|SCTP_CID_ABORT
)paren
(brace
multiline_comment|/* Sec 8.5.1 (B) */
r_if
c_cond
(paren
op_logical_neg
(paren
id|sh-&gt;vtag
op_eq
id|conntrack-&gt;proto.sctp.vtag
(braket
id|CTINFO2DIR
c_func
(paren
id|ctinfo
)paren
)braket
)paren
op_logical_and
op_logical_neg
(paren
id|sh-&gt;vtag
op_eq
id|conntrack-&gt;proto.sctp.vtag
(braket
l_int|1
op_minus
id|CTINFO2DIR
c_func
(paren
id|ctinfo
)paren
)braket
)paren
)paren
(brace
id|WRITE_UNLOCK
c_func
(paren
op_amp
id|sctp_lock
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|sch-&gt;type
op_eq
id|SCTP_CID_SHUTDOWN_COMPLETE
)paren
(brace
multiline_comment|/* Sec 8.5.1 (C) */
r_if
c_cond
(paren
op_logical_neg
(paren
id|sh-&gt;vtag
op_eq
id|conntrack-&gt;proto.sctp.vtag
(braket
id|CTINFO2DIR
c_func
(paren
id|ctinfo
)paren
)braket
)paren
op_logical_and
op_logical_neg
(paren
id|sh-&gt;vtag
op_eq
id|conntrack-&gt;proto.sctp.vtag
(braket
l_int|1
op_minus
id|CTINFO2DIR
c_func
(paren
id|ctinfo
)paren
)braket
op_logical_and
(paren
id|sch-&gt;flags
op_amp
l_int|1
)paren
)paren
)paren
(brace
id|WRITE_UNLOCK
c_func
(paren
op_amp
id|sctp_lock
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|sch-&gt;type
op_eq
id|SCTP_CID_COOKIE_ECHO
)paren
(brace
multiline_comment|/* Sec 8.5.1 (D) */
r_if
c_cond
(paren
op_logical_neg
(paren
id|sh-&gt;vtag
op_eq
id|conntrack-&gt;proto.sctp.vtag
(braket
id|CTINFO2DIR
c_func
(paren
id|ctinfo
)paren
)braket
)paren
)paren
(brace
id|WRITE_UNLOCK
c_func
(paren
op_amp
id|sctp_lock
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
)brace
id|oldsctpstate
op_assign
id|conntrack-&gt;proto.sctp.state
suffix:semicolon
id|newconntrack
op_assign
id|new_state
c_func
(paren
id|CTINFO2DIR
c_func
(paren
id|ctinfo
)paren
comma
id|oldsctpstate
comma
id|sch-&gt;type
)paren
suffix:semicolon
multiline_comment|/* Invalid */
r_if
c_cond
(paren
id|newconntrack
op_eq
id|SCTP_CONNTRACK_MAX
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;ip_conntrack_sctp: Invalid dir=%i ctype=%u conntrack=%u&bslash;n&quot;
comma
id|CTINFO2DIR
c_func
(paren
id|ctinfo
)paren
comma
id|sch-&gt;type
comma
id|oldsctpstate
)paren
suffix:semicolon
id|WRITE_UNLOCK
c_func
(paren
op_amp
id|sctp_lock
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* If it is an INIT or an INIT ACK note down the vtag */
r_if
c_cond
(paren
id|sch-&gt;type
op_eq
id|SCTP_CID_INIT
op_logical_or
id|sch-&gt;type
op_eq
id|SCTP_CID_INIT_ACK
)paren
(brace
id|sctp_inithdr_t
id|_inithdr
comma
op_star
id|ih
suffix:semicolon
id|ih
op_assign
id|skb_header_pointer
c_func
(paren
id|skb
comma
id|offset
op_plus
r_sizeof
(paren
id|sctp_chunkhdr_t
)paren
comma
r_sizeof
(paren
id|_inithdr
)paren
comma
op_amp
id|_inithdr
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
id|WRITE_UNLOCK
c_func
(paren
op_amp
id|sctp_lock
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|DEBUGP
c_func
(paren
l_string|&quot;Setting vtag %x for dir %d&bslash;n&quot;
comma
id|ih-&gt;init_tag
comma
id|CTINFO2DIR
c_func
(paren
id|ctinfo
)paren
)paren
suffix:semicolon
id|conntrack-&gt;proto.sctp.vtag
(braket
id|IP_CT_DIR_ORIGINAL
)braket
op_assign
id|ih-&gt;init_tag
suffix:semicolon
)brace
id|conntrack-&gt;proto.sctp.state
op_assign
id|newconntrack
suffix:semicolon
id|WRITE_UNLOCK
c_func
(paren
op_amp
id|sctp_lock
)paren
suffix:semicolon
)brace
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
id|sctp_timeouts
(braket
id|newconntrack
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|oldsctpstate
op_eq
id|SCTP_CONNTRACK_COOKIE_ECHOED
op_logical_and
id|CTINFO2DIR
c_func
(paren
id|ctinfo
)paren
op_eq
id|IP_CT_DIR_REPLY
op_logical_and
id|newconntrack
op_eq
id|SCTP_CONNTRACK_ESTABLISHED
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;Setting assured bit&bslash;n&quot;
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|IPS_ASSURED_BIT
comma
op_amp
id|conntrack-&gt;status
)paren
suffix:semicolon
)brace
r_return
id|NF_ACCEPT
suffix:semicolon
)brace
multiline_comment|/* Called when a new connection for this protocol found. */
DECL|function|sctp_new
r_static
r_int
id|sctp_new
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
id|sctp_conntrack
id|newconntrack
suffix:semicolon
r_struct
id|iphdr
op_star
id|iph
op_assign
id|skb-&gt;nh.iph
suffix:semicolon
id|sctp_sctphdr_t
id|_sctph
comma
op_star
id|sh
suffix:semicolon
id|sctp_chunkhdr_t
id|_sch
comma
op_star
id|sch
suffix:semicolon
id|u_int32_t
id|offset
comma
id|count
suffix:semicolon
r_char
id|map
(braket
l_int|256
op_div
r_sizeof
(paren
r_char
)paren
)braket
op_assign
(brace
l_int|0
)brace
suffix:semicolon
id|DEBUGP
c_func
(paren
id|__FUNCTION__
)paren
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|sh
op_assign
id|skb_header_pointer
c_func
(paren
id|skb
comma
id|iph-&gt;ihl
op_star
l_int|4
comma
r_sizeof
(paren
id|_sctph
)paren
comma
op_amp
id|_sctph
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sh
op_eq
l_int|NULL
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|do_basic_checks
c_func
(paren
id|conntrack
comma
id|skb
comma
id|map
)paren
op_ne
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* If an OOTB packet has any of these chunks discard (Sec 8.4) */
r_if
c_cond
(paren
(paren
id|test_bit
(paren
id|SCTP_CID_ABORT
comma
(paren
r_void
op_star
)paren
id|map
)paren
)paren
op_logical_or
(paren
id|test_bit
(paren
id|SCTP_CID_SHUTDOWN_COMPLETE
comma
(paren
r_void
op_star
)paren
id|map
)paren
)paren
op_logical_or
(paren
id|test_bit
(paren
id|SCTP_CID_COOKIE_ACK
comma
(paren
r_void
op_star
)paren
id|map
)paren
)paren
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
id|newconntrack
op_assign
id|SCTP_CONNTRACK_MAX
suffix:semicolon
id|for_each_sctp_chunk
(paren
id|skb
comma
id|sch
comma
id|_sch
comma
id|offset
comma
id|count
)paren
(brace
multiline_comment|/* Don&squot;t need lock here: this conntrack not in circulation yet */
id|newconntrack
op_assign
id|new_state
(paren
id|IP_CT_DIR_ORIGINAL
comma
id|SCTP_CONNTRACK_NONE
comma
id|sch-&gt;type
)paren
suffix:semicolon
multiline_comment|/* Invalid: delete conntrack */
r_if
c_cond
(paren
id|newconntrack
op_eq
id|SCTP_CONNTRACK_MAX
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;ip_conntrack_sctp: invalid new deleting.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Copy the vtag into the state info */
r_if
c_cond
(paren
id|sch-&gt;type
op_eq
id|SCTP_CID_INIT
)paren
(brace
r_if
c_cond
(paren
id|sh-&gt;vtag
op_eq
l_int|0
)paren
(brace
id|sctp_inithdr_t
id|_inithdr
comma
op_star
id|ih
suffix:semicolon
id|ih
op_assign
id|skb_header_pointer
c_func
(paren
id|skb
comma
id|offset
op_plus
r_sizeof
(paren
id|sctp_chunkhdr_t
)paren
comma
r_sizeof
(paren
id|_inithdr
)paren
comma
op_amp
id|_inithdr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ih
op_eq
l_int|NULL
)paren
r_return
l_int|0
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;Setting vtag %x for new conn&bslash;n&quot;
comma
id|ih-&gt;init_tag
)paren
suffix:semicolon
id|conntrack-&gt;proto.sctp.vtag
(braket
id|IP_CT_DIR_REPLY
)braket
op_assign
id|ih-&gt;init_tag
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Sec 8.5.1 (A) */
r_return
l_int|0
suffix:semicolon
)brace
)brace
multiline_comment|/* If it is a shutdown ack OOTB packet, we expect a return&n;&t;&t;   shutdown complete, otherwise an ABORT Sec 8.4 (5) and (8) */
r_else
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;Setting vtag %x for new conn OOTB&bslash;n&quot;
comma
id|sh-&gt;vtag
)paren
suffix:semicolon
id|conntrack-&gt;proto.sctp.vtag
(braket
id|IP_CT_DIR_REPLY
)braket
op_assign
id|sh-&gt;vtag
suffix:semicolon
)brace
id|conntrack-&gt;proto.sctp.state
op_assign
id|newconntrack
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|variable|ip_conntrack_protocol_sctp
r_struct
id|ip_conntrack_protocol
id|ip_conntrack_protocol_sctp
op_assign
(brace
dot
id|proto
op_assign
id|IPPROTO_SCTP
comma
dot
id|name
op_assign
l_string|&quot;sctp&quot;
comma
dot
id|pkt_to_tuple
op_assign
id|sctp_pkt_to_tuple
comma
dot
id|invert_tuple
op_assign
id|sctp_invert_tuple
comma
dot
id|print_tuple
op_assign
id|sctp_print_tuple
comma
dot
id|print_conntrack
op_assign
id|sctp_print_conntrack
comma
dot
id|packet
op_assign
id|sctp_packet
comma
dot
r_new
op_assign
id|sctp_new
comma
dot
id|destroy
op_assign
l_int|NULL
comma
dot
id|me
op_assign
id|THIS_MODULE
)brace
suffix:semicolon
macro_line|#ifdef CONFIG_SYSCTL
DECL|variable|ip_ct_sysctl_table
r_static
id|ctl_table
id|ip_ct_sysctl_table
(braket
)braket
op_assign
(brace
(brace
dot
id|ctl_name
op_assign
id|NET_IPV4_NF_CONNTRACK_SCTP_TIMEOUT_CLOSED
comma
dot
id|procname
op_assign
l_string|&quot;ip_conntrack_sctp_timeout_closed&quot;
comma
dot
id|data
op_assign
op_amp
id|ip_ct_sctp_timeout_closed
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec_jiffies
comma
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_IPV4_NF_CONNTRACK_SCTP_TIMEOUT_COOKIE_WAIT
comma
dot
id|procname
op_assign
l_string|&quot;ip_conntrack_sctp_timeout_cookie_wait&quot;
comma
dot
id|data
op_assign
op_amp
id|ip_ct_sctp_timeout_cookie_wait
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec_jiffies
comma
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_IPV4_NF_CONNTRACK_SCTP_TIMEOUT_COOKIE_ECHOED
comma
dot
id|procname
op_assign
l_string|&quot;ip_conntrack_sctp_timeout_cookie_echoed&quot;
comma
dot
id|data
op_assign
op_amp
id|ip_ct_sctp_timeout_cookie_echoed
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec_jiffies
comma
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_IPV4_NF_CONNTRACK_SCTP_TIMEOUT_ESTABLISHED
comma
dot
id|procname
op_assign
l_string|&quot;ip_conntrack_sctp_timeout_established&quot;
comma
dot
id|data
op_assign
op_amp
id|ip_ct_sctp_timeout_established
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec_jiffies
comma
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_IPV4_NF_CONNTRACK_SCTP_TIMEOUT_SHUTDOWN_SENT
comma
dot
id|procname
op_assign
l_string|&quot;ip_conntrack_sctp_timeout_shutdown_sent&quot;
comma
dot
id|data
op_assign
op_amp
id|ip_ct_sctp_timeout_shutdown_sent
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec_jiffies
comma
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_IPV4_NF_CONNTRACK_SCTP_TIMEOUT_SHUTDOWN_RECD
comma
dot
id|procname
op_assign
l_string|&quot;ip_conntrack_sctp_timeout_shutdown_recd&quot;
comma
dot
id|data
op_assign
op_amp
id|ip_ct_sctp_timeout_shutdown_recd
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec_jiffies
comma
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_IPV4_NF_CONNTRACK_SCTP_TIMEOUT_SHUTDOWN_ACK_SENT
comma
dot
id|procname
op_assign
l_string|&quot;ip_conntrack_sctp_timeout_shutdown_ack_sent&quot;
comma
dot
id|data
op_assign
op_amp
id|ip_ct_sctp_timeout_shutdown_ack_sent
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec_jiffies
comma
)brace
comma
(brace
dot
id|ctl_name
op_assign
l_int|0
)brace
)brace
suffix:semicolon
DECL|variable|ip_ct_netfilter_table
r_static
id|ctl_table
id|ip_ct_netfilter_table
(braket
)braket
op_assign
(brace
(brace
dot
id|ctl_name
op_assign
id|NET_IPV4_NETFILTER
comma
dot
id|procname
op_assign
l_string|&quot;netfilter&quot;
comma
dot
id|mode
op_assign
l_int|0555
comma
dot
id|child
op_assign
id|ip_ct_sysctl_table
comma
)brace
comma
(brace
dot
id|ctl_name
op_assign
l_int|0
)brace
)brace
suffix:semicolon
DECL|variable|ip_ct_ipv4_table
r_static
id|ctl_table
id|ip_ct_ipv4_table
(braket
)braket
op_assign
(brace
(brace
dot
id|ctl_name
op_assign
id|NET_IPV4
comma
dot
id|procname
op_assign
l_string|&quot;ipv4&quot;
comma
dot
id|mode
op_assign
l_int|0555
comma
dot
id|child
op_assign
id|ip_ct_netfilter_table
comma
)brace
comma
(brace
dot
id|ctl_name
op_assign
l_int|0
)brace
)brace
suffix:semicolon
DECL|variable|ip_ct_net_table
r_static
id|ctl_table
id|ip_ct_net_table
(braket
)braket
op_assign
(brace
(brace
dot
id|ctl_name
op_assign
id|CTL_NET
comma
dot
id|procname
op_assign
l_string|&quot;net&quot;
comma
dot
id|mode
op_assign
l_int|0555
comma
dot
id|child
op_assign
id|ip_ct_ipv4_table
comma
)brace
comma
(brace
dot
id|ctl_name
op_assign
l_int|0
)brace
)brace
suffix:semicolon
DECL|variable|ip_ct_sysctl_header
r_static
r_struct
id|ctl_table_header
op_star
id|ip_ct_sysctl_header
suffix:semicolon
macro_line|#endif
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
r_int
id|ret
suffix:semicolon
id|ret
op_assign
id|ip_conntrack_protocol_register
c_func
(paren
op_amp
id|ip_conntrack_protocol_sctp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ip_conntrack_proto_sctp: protocol register failed&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_SYSCTL
id|ip_ct_sysctl_header
op_assign
id|register_sysctl_table
c_func
(paren
id|ip_ct_net_table
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ip_ct_sysctl_header
op_eq
l_int|NULL
)paren
(brace
id|ret
op_assign
op_minus
id|ENOMEM
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;ip_conntrack_proto_sctp: can&squot;t register to sysctl.&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|cleanup
suffix:semicolon
)brace
macro_line|#endif
r_return
id|ret
suffix:semicolon
macro_line|#ifdef CONFIG_SYSCTL
id|cleanup
suffix:colon
id|ip_conntrack_protocol_unregister
c_func
(paren
op_amp
id|ip_conntrack_protocol_sctp
)paren
suffix:semicolon
macro_line|#endif
id|out
suffix:colon
id|DEBUGP
c_func
(paren
l_string|&quot;SCTP conntrack module loading %s&bslash;n&quot;
comma
id|ret
ques
c_cond
l_string|&quot;failed&quot;
suffix:colon
l_string|&quot;succeeded&quot;
)paren
suffix:semicolon
r_return
id|ret
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
id|ip_conntrack_protocol_unregister
c_func
(paren
op_amp
id|ip_conntrack_protocol_sctp
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SYSCTL
id|unregister_sysctl_table
c_func
(paren
id|ip_ct_sysctl_header
)paren
suffix:semicolon
macro_line|#endif
id|DEBUGP
c_func
(paren
l_string|&quot;SCTP conntrack module unloaded&bslash;n&quot;
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
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Kiran Kumar Immidi&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Netfilter connection tracking protocol helper for SCTP&quot;
)paren
suffix:semicolon
eof
