multiline_comment|/*&n; * DECnet       An implementation of the DECnet protocol suite for the LINUX&n; *              operating system.  DECnet is implemented using the  BSD Socket&n; *              interface as the means of communication with the user level.&n; *&n; *              DECnet Socket Timer Functions&n; *&n; * Author:      Steve Whitehouse &lt;SteveW@ACM.org&gt;&n; *&n; *&n; * Changes:&n; *       Steve Whitehouse      : Made keepalive timer part of the same&n; *                               timer idea.&n; *       Steve Whitehouse      : Added checks for sk-&gt;sock_readers&n; *       David S. Miller       : New socket locking&n; *       Steve Whitehouse      : Timer grabs socket ref.&n; */
macro_line|#include &lt;linux/net.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;net/flow.h&gt;
macro_line|#include &lt;net/dn.h&gt;
multiline_comment|/*&n; * Slow timer is for everything else (n * 500mS)&n; */
DECL|macro|SLOW_INTERVAL
mdefine_line|#define SLOW_INTERVAL (HZ/2)
r_static
r_void
id|dn_slow_timer
c_func
(paren
r_int
r_int
id|arg
)paren
suffix:semicolon
DECL|function|dn_start_slow_timer
r_void
id|dn_start_slow_timer
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
(brace
id|sk-&gt;sk_timer.expires
op_assign
id|jiffies
op_plus
id|SLOW_INTERVAL
suffix:semicolon
id|sk-&gt;sk_timer.function
op_assign
id|dn_slow_timer
suffix:semicolon
id|sk-&gt;sk_timer.data
op_assign
(paren
r_int
r_int
)paren
id|sk
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|sk-&gt;sk_timer
)paren
suffix:semicolon
)brace
DECL|function|dn_stop_slow_timer
r_void
id|dn_stop_slow_timer
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
(brace
id|del_timer
c_func
(paren
op_amp
id|sk-&gt;sk_timer
)paren
suffix:semicolon
)brace
DECL|function|dn_slow_timer
r_static
r_void
id|dn_slow_timer
c_func
(paren
r_int
r_int
id|arg
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
id|arg
suffix:semicolon
r_struct
id|dn_scp
op_star
id|scp
op_assign
id|DN_SK
c_func
(paren
id|sk
)paren
suffix:semicolon
id|sock_hold
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
id|sk-&gt;sk_timer.expires
op_assign
id|jiffies
op_plus
id|HZ
op_div
l_int|10
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|sk-&gt;sk_timer
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * The persist timer is the standard slow timer used for retransmits&n;&t; * in both connection establishment and disconnection as well as&n;&t; * in the RUN state. The different states are catered for by changing&n;&t; * the function pointer in the socket. Setting the timer to a value&n;&t; * of zero turns it off. We allow the persist_fxn to turn the&n;&t; * timer off in a permant way by returning non-zero, so that&n;&t; * timer based routines may remove sockets. This is why we have a&n;&t; * sock_hold()/sock_put() around the timer to prevent the socket&n;&t; * going away in the middle.&n;&t; */
r_if
c_cond
(paren
id|scp-&gt;persist
op_logical_and
id|scp-&gt;persist_fxn
)paren
(brace
r_if
c_cond
(paren
id|scp-&gt;persist
op_le
id|SLOW_INTERVAL
)paren
(brace
id|scp-&gt;persist
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|scp
op_member_access_from_pointer
id|persist_fxn
c_func
(paren
id|sk
)paren
)paren
r_goto
id|out
suffix:semicolon
)brace
r_else
(brace
id|scp-&gt;persist
op_sub_assign
id|SLOW_INTERVAL
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; * Check for keepalive timeout. After the other timer &squot;cos if&n;&t; * the previous timer caused a retransmit, we don&squot;t need to&n;&t; * do this. scp-&gt;stamp is the last time that we sent a packet.&n;&t; * The keepalive function sends a link service packet to the&n;&t; * other end. If it remains unacknowledged, the standard&n;&t; * socket timers will eventually shut the socket down. Each&n;&t; * time we do this, scp-&gt;stamp will be updated, thus&n;&t; * we won&squot;t try and send another until scp-&gt;keepalive has passed&n;&t; * since the last successful transmission.&n;&t; */
r_if
c_cond
(paren
id|scp-&gt;keepalive
op_logical_and
id|scp-&gt;keepalive_fxn
op_logical_and
(paren
id|scp-&gt;state
op_eq
id|DN_RUN
)paren
)paren
(brace
r_if
c_cond
(paren
(paren
id|jiffies
op_minus
id|scp-&gt;stamp
)paren
op_ge
id|scp-&gt;keepalive
)paren
id|scp
op_member_access_from_pointer
id|keepalive_fxn
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
id|sk-&gt;sk_timer.expires
op_assign
id|jiffies
op_plus
id|SLOW_INTERVAL
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|sk-&gt;sk_timer
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
