macro_line|#ifndef _X25DEVICE_H
DECL|macro|_X25DEVICE_H
mdefine_line|#define _X25DEVICE_H
macro_line|#include &lt;linux/if_ether.h&gt;
macro_line|#include &lt;linux/if_packet.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
DECL|function|x25_type_trans
r_static
r_inline
r_int
r_int
id|x25_type_trans
c_func
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
)paren
(brace
id|skb-&gt;mac.raw
op_assign
id|skb-&gt;data
suffix:semicolon
id|skb-&gt;input_dev
op_assign
id|skb-&gt;dev
op_assign
id|dev
suffix:semicolon
id|skb-&gt;pkt_type
op_assign
id|PACKET_HOST
suffix:semicolon
r_return
id|htons
c_func
(paren
id|ETH_P_X25
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
