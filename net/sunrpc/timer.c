multiline_comment|/*&n; * linux/net/sunrpc/timer.c&n; *&n; * Estimate RPC request round trip time.&n; *&n; * Based on packet round-trip and variance estimator algorithms described&n; * in appendix A of &quot;Congestion Avoidance and Control&quot; by Van Jacobson&n; * and Michael J. Karels (ACM Computer Communication Review; Proceedings&n; * of the Sigcomm &squot;88 Symposium in Stanford, CA, August, 1988).&n; *&n; * This RTT estimator is used only for RPC over datagram protocols.&n; *&n; * Copyright (C) 2002 Trond Myklebust &lt;trond.myklebust@fys.uio.no&gt;&n; */
macro_line|#include &lt;asm/param.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/sunrpc/clnt.h&gt;
macro_line|#include &lt;linux/sunrpc/xprt.h&gt;
macro_line|#include &lt;linux/sunrpc/timer.h&gt;
DECL|macro|RPC_RTO_MAX
mdefine_line|#define RPC_RTO_MAX (60*HZ)
DECL|macro|RPC_RTO_INIT
mdefine_line|#define RPC_RTO_INIT (HZ/5)
DECL|macro|RPC_RTO_MIN
mdefine_line|#define RPC_RTO_MIN (HZ/10)
r_void
DECL|function|rpc_init_rtt
id|rpc_init_rtt
c_func
(paren
r_struct
id|rpc_rtt
op_star
id|rt
comma
r_int
r_int
id|timeo
)paren
(brace
r_int
r_int
id|init
op_assign
l_int|0
suffix:semicolon
r_int
id|i
suffix:semicolon
id|rt-&gt;timeo
op_assign
id|timeo
suffix:semicolon
r_if
c_cond
(paren
id|timeo
OG
id|RPC_RTO_INIT
)paren
id|init
op_assign
(paren
id|timeo
op_minus
id|RPC_RTO_INIT
)paren
op_lshift
l_int|3
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
l_int|5
suffix:semicolon
id|i
op_increment
)paren
(brace
id|rt-&gt;srtt
(braket
id|i
)braket
op_assign
id|init
suffix:semicolon
id|rt-&gt;sdrtt
(braket
id|i
)braket
op_assign
id|RPC_RTO_INIT
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * NB: When computing the smoothed RTT and standard deviation,&n; *     be careful not to produce negative intermediate results.&n; */
r_void
DECL|function|rpc_update_rtt
id|rpc_update_rtt
c_func
(paren
r_struct
id|rpc_rtt
op_star
id|rt
comma
r_int
id|timer
comma
r_int
id|m
)paren
(brace
r_int
op_star
id|srtt
comma
op_star
id|sdrtt
suffix:semicolon
r_if
c_cond
(paren
id|timer
op_decrement
op_eq
l_int|0
)paren
r_return
suffix:semicolon
multiline_comment|/* jiffies wrapped; ignore this one */
r_if
c_cond
(paren
id|m
OL
l_int|0
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|m
op_eq
l_int|0
)paren
id|m
op_assign
l_int|1L
suffix:semicolon
id|srtt
op_assign
(paren
r_int
op_star
)paren
op_amp
id|rt-&gt;srtt
(braket
id|timer
)braket
suffix:semicolon
id|m
op_sub_assign
op_star
id|srtt
op_rshift
l_int|3
suffix:semicolon
op_star
id|srtt
op_add_assign
id|m
suffix:semicolon
r_if
c_cond
(paren
id|m
OL
l_int|0
)paren
id|m
op_assign
op_minus
id|m
suffix:semicolon
id|sdrtt
op_assign
(paren
r_int
op_star
)paren
op_amp
id|rt-&gt;sdrtt
(braket
id|timer
)braket
suffix:semicolon
id|m
op_sub_assign
op_star
id|sdrtt
op_rshift
l_int|2
suffix:semicolon
op_star
id|sdrtt
op_add_assign
id|m
suffix:semicolon
multiline_comment|/* Set lower bound on the variance */
r_if
c_cond
(paren
op_star
id|sdrtt
OL
id|RPC_RTO_MIN
)paren
op_star
id|sdrtt
op_assign
id|RPC_RTO_MIN
suffix:semicolon
)brace
multiline_comment|/*&n; * Estimate rto for an nfs rpc sent via. an unreliable datagram.&n; * Use the mean and mean deviation of rtt for the appropriate type of rpc&n; * for the frequent rpcs and a default for the others.&n; * The justification for doing &quot;other&quot; this way is that these rpcs&n; * happen so infrequently that timer est. would probably be stale.&n; * Also, since many of these rpcs are&n; * non-idempotent, a conservative timeout is desired.&n; * getattr, lookup,&n; * read, write, commit     - A+4D&n; * other                   - timeo&n; */
r_int
r_int
DECL|function|rpc_calc_rto
id|rpc_calc_rto
c_func
(paren
r_struct
id|rpc_rtt
op_star
id|rt
comma
r_int
id|timer
)paren
(brace
r_int
r_int
id|res
suffix:semicolon
r_if
c_cond
(paren
id|timer
op_decrement
op_eq
l_int|0
)paren
r_return
id|rt-&gt;timeo
suffix:semicolon
id|res
op_assign
(paren
(paren
id|rt-&gt;srtt
(braket
id|timer
)braket
op_plus
l_int|7
)paren
op_rshift
l_int|3
)paren
op_plus
id|rt-&gt;sdrtt
(braket
id|timer
)braket
suffix:semicolon
r_if
c_cond
(paren
id|res
OG
id|RPC_RTO_MAX
)paren
id|res
op_assign
id|RPC_RTO_MAX
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
eof
