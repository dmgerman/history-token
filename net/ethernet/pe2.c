macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;net/datalink.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/in.h&gt;
DECL|function|pEII_request
r_static
r_int
id|pEII_request
c_func
(paren
r_struct
id|datalink_proto
op_star
id|dl
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
r_char
op_star
id|dest_node
)paren
(brace
r_struct
id|net_device
op_star
id|dev
op_assign
id|skb-&gt;dev
suffix:semicolon
id|skb-&gt;protocol
op_assign
id|htons
(paren
id|ETH_P_IPX
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;hard_header
)paren
(brace
id|dev
op_member_access_from_pointer
id|hard_header
c_func
(paren
id|skb
comma
id|dev
comma
id|ETH_P_IPX
comma
id|dest_node
comma
l_int|NULL
comma
id|skb-&gt;len
)paren
suffix:semicolon
)brace
r_return
id|dev_queue_xmit
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
r_struct
id|datalink_proto
op_star
DECL|function|make_EII_client
id|make_EII_client
c_func
(paren
r_void
)paren
(brace
r_struct
id|datalink_proto
op_star
id|proto
suffix:semicolon
id|proto
op_assign
(paren
r_struct
id|datalink_proto
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|proto
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|proto
op_ne
l_int|NULL
)paren
(brace
id|proto-&gt;header_length
op_assign
l_int|0
suffix:semicolon
id|proto-&gt;request
op_assign
id|pEII_request
suffix:semicolon
)brace
r_return
id|proto
suffix:semicolon
)brace
DECL|function|destroy_EII_client
r_void
id|destroy_EII_client
c_func
(paren
r_struct
id|datalink_proto
op_star
id|dl
)paren
(brace
r_if
c_cond
(paren
id|dl
)paren
id|kfree
c_func
(paren
id|dl
)paren
suffix:semicolon
)brace
eof
