multiline_comment|/*&n; *  linux/include/linux/sunrpc/timer.h&n; *&n; *  Declarations for the RPC transport timer.&n; *&n; *  Copyright (C) 2002 Trond Myklebust &lt;trond.myklebust@fys.uio.no&gt;&n; */
macro_line|#ifndef _LINUX_SUNRPC_TIMER_H
DECL|macro|_LINUX_SUNRPC_TIMER_H
mdefine_line|#define _LINUX_SUNRPC_TIMER_H
macro_line|#include &lt;asm/atomic.h&gt;
DECL|struct|rpc_rtt
r_struct
id|rpc_rtt
(brace
DECL|member|timeo
r_int
r_int
id|timeo
suffix:semicolon
multiline_comment|/* default timeout value */
DECL|member|srtt
r_int
r_int
id|srtt
(braket
l_int|5
)braket
suffix:semicolon
multiline_comment|/* smoothed round trip time &lt;&lt; 3 */
DECL|member|sdrtt
r_int
r_int
id|sdrtt
(braket
l_int|5
)braket
suffix:semicolon
multiline_comment|/* smoothed medium deviation of RTT */
)brace
suffix:semicolon
r_extern
r_void
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
suffix:semicolon
r_extern
r_void
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
suffix:semicolon
r_extern
r_int
r_int
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
suffix:semicolon
macro_line|#endif /* _LINUX_SUNRPC_TIMER_H */
eof
