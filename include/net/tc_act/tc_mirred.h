macro_line|#ifndef __NET_TC_MIR_H
DECL|macro|__NET_TC_MIR_H
mdefine_line|#define __NET_TC_MIR_H
macro_line|#include &lt;net/act_api.h&gt;
DECL|struct|tcf_mirred
r_struct
id|tcf_mirred
(brace
id|tca_gen
c_func
(paren
id|mirred
)paren
suffix:semicolon
DECL|member|eaction
r_int
id|eaction
suffix:semicolon
DECL|member|ifindex
r_int
id|ifindex
suffix:semicolon
DECL|member|ok_push
r_int
id|ok_push
suffix:semicolon
DECL|member|dev
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
eof
