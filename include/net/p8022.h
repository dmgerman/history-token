macro_line|#ifndef _NET_P8022_H
DECL|macro|_NET_P8022_H
mdefine_line|#define _NET_P8022_H
r_extern
r_struct
id|datalink_proto
op_star
id|register_8022_client
c_func
(paren
r_int
r_char
id|type
comma
r_int
(paren
op_star
id|func
)paren
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|packet_type
op_star
id|pt
)paren
)paren
suffix:semicolon
r_extern
r_void
id|unregister_8022_client
c_func
(paren
r_struct
id|datalink_proto
op_star
id|proto
)paren
suffix:semicolon
macro_line|#endif
eof
