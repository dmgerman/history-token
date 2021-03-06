macro_line|#ifndef _NET_INET_IPX_H_
DECL|macro|_NET_INET_IPX_H_
mdefine_line|#define _NET_INET_IPX_H_
multiline_comment|/*&n; *&t;The following information is in its entirety obtained from:&n; *&n; *&t;Novell &squot;IPX Router Specification&squot; Version 1.10 &n; *&t;&t;Part No. 107-000029-001&n; *&n; *&t;Which is available from ftp.novell.com&n; */
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;net/datalink.h&gt;
macro_line|#include &lt;linux/ipx.h&gt;
macro_line|#include &lt;linux/list.h&gt;
DECL|struct|ipx_address
r_struct
id|ipx_address
(brace
DECL|member|net
id|__u32
id|net
suffix:semicolon
DECL|member|node
id|__u8
id|node
(braket
id|IPX_NODE_LEN
)braket
suffix:semicolon
DECL|member|sock
id|__u16
id|sock
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|ipx_broadcast_node
mdefine_line|#define ipx_broadcast_node&t;&quot;&bslash;377&bslash;377&bslash;377&bslash;377&bslash;377&bslash;377&quot;
DECL|macro|ipx_this_node
mdefine_line|#define ipx_this_node           &quot;&bslash;0&bslash;0&bslash;0&bslash;0&bslash;0&bslash;0&quot;
DECL|macro|IPX_MAX_PPROP_HOPS
mdefine_line|#define IPX_MAX_PPROP_HOPS 8
DECL|struct|ipxhdr
r_struct
id|ipxhdr
(brace
DECL|member|ipx_checksum
id|__u16
id|ipx_checksum
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|macro|IPX_NO_CHECKSUM
mdefine_line|#define IPX_NO_CHECKSUM&t;0xFFFF
DECL|member|ipx_pktsize
id|__u16
id|ipx_pktsize
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|ipx_tctrl
id|__u8
id|ipx_tctrl
suffix:semicolon
DECL|member|ipx_type
id|__u8
id|ipx_type
suffix:semicolon
DECL|macro|IPX_TYPE_UNKNOWN
mdefine_line|#define IPX_TYPE_UNKNOWN&t;0x00
DECL|macro|IPX_TYPE_RIP
mdefine_line|#define IPX_TYPE_RIP&t;&t;0x01&t;/* may also be 0 */
DECL|macro|IPX_TYPE_SAP
mdefine_line|#define IPX_TYPE_SAP&t;&t;0x04&t;/* may also be 0 */
DECL|macro|IPX_TYPE_SPX
mdefine_line|#define IPX_TYPE_SPX&t;&t;0x05&t;/* SPX protocol */
DECL|macro|IPX_TYPE_NCP
mdefine_line|#define IPX_TYPE_NCP&t;&t;0x11&t;/* $lots for docs on this (SPIT) */
DECL|macro|IPX_TYPE_PPROP
mdefine_line|#define IPX_TYPE_PPROP&t;&t;0x14&t;/* complicated flood fill brdcast */
DECL|member|ipx_dest
r_struct
id|ipx_address
id|ipx_dest
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|ipx_source
r_struct
id|ipx_address
id|ipx_source
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|function|ipx_hdr
r_static
id|__inline__
r_struct
id|ipxhdr
op_star
id|ipx_hdr
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_return
(paren
r_struct
id|ipxhdr
op_star
)paren
id|skb-&gt;h.raw
suffix:semicolon
)brace
DECL|struct|ipx_interface
r_struct
id|ipx_interface
(brace
multiline_comment|/* IPX address */
DECL|member|if_netnum
id|__u32
id|if_netnum
suffix:semicolon
DECL|member|if_node
r_int
r_char
id|if_node
(braket
id|IPX_NODE_LEN
)braket
suffix:semicolon
DECL|member|refcnt
id|atomic_t
id|refcnt
suffix:semicolon
multiline_comment|/* physical device info */
DECL|member|if_dev
r_struct
id|net_device
op_star
id|if_dev
suffix:semicolon
DECL|member|if_dlink
r_struct
id|datalink_proto
op_star
id|if_dlink
suffix:semicolon
DECL|member|if_dlink_type
r_int
r_int
id|if_dlink_type
suffix:semicolon
multiline_comment|/* socket support */
DECL|member|if_sknum
r_int
r_int
id|if_sknum
suffix:semicolon
DECL|member|if_sklist
r_struct
id|hlist_head
id|if_sklist
suffix:semicolon
DECL|member|if_sklist_lock
id|spinlock_t
id|if_sklist_lock
suffix:semicolon
multiline_comment|/* administrative overhead */
DECL|member|if_ipx_offset
r_int
id|if_ipx_offset
suffix:semicolon
DECL|member|if_internal
r_int
r_char
id|if_internal
suffix:semicolon
DECL|member|if_primary
r_int
r_char
id|if_primary
suffix:semicolon
DECL|member|node
r_struct
id|list_head
id|node
suffix:semicolon
multiline_comment|/* node in ipx_interfaces list */
)brace
suffix:semicolon
DECL|struct|ipx_route
r_struct
id|ipx_route
(brace
DECL|member|ir_net
id|__u32
id|ir_net
suffix:semicolon
DECL|member|ir_intrfc
r_struct
id|ipx_interface
op_star
id|ir_intrfc
suffix:semicolon
DECL|member|ir_routed
r_int
r_char
id|ir_routed
suffix:semicolon
DECL|member|ir_router_node
r_int
r_char
id|ir_router_node
(braket
id|IPX_NODE_LEN
)braket
suffix:semicolon
DECL|member|node
r_struct
id|list_head
id|node
suffix:semicolon
multiline_comment|/* node in ipx_routes list */
DECL|member|refcnt
id|atomic_t
id|refcnt
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
DECL|struct|ipx_cb
r_struct
id|ipx_cb
(brace
DECL|member|ipx_tctrl
id|u8
id|ipx_tctrl
suffix:semicolon
DECL|member|ipx_dest_net
id|u32
id|ipx_dest_net
suffix:semicolon
DECL|member|ipx_source_net
id|u32
id|ipx_source_net
suffix:semicolon
r_struct
(brace
DECL|member|netnum
id|u32
id|netnum
suffix:semicolon
DECL|member|index
r_int
id|index
suffix:semicolon
DECL|member|last_hop
)brace
id|last_hop
suffix:semicolon
)brace
suffix:semicolon
macro_line|#include &lt;net/sock.h&gt;
DECL|struct|ipx_sock
r_struct
id|ipx_sock
(brace
multiline_comment|/* struct sock has to be the first member of ipx_sock */
DECL|member|sk
r_struct
id|sock
id|sk
suffix:semicolon
DECL|member|dest_addr
r_struct
id|ipx_address
id|dest_addr
suffix:semicolon
DECL|member|intrfc
r_struct
id|ipx_interface
op_star
id|intrfc
suffix:semicolon
DECL|member|port
r_int
r_int
id|port
suffix:semicolon
macro_line|#ifdef CONFIG_IPX_INTERN
DECL|member|node
r_int
r_char
id|node
(braket
id|IPX_NODE_LEN
)braket
suffix:semicolon
macro_line|#endif
DECL|member|type
r_int
r_int
id|type
suffix:semicolon
multiline_comment|/*&n;&t; * To handle special ncp connection-handling sockets for mars_nwe,&n; &t; * the connection number must be stored in the socket.&n;&t; */
DECL|member|ipx_ncp_conn
r_int
r_int
id|ipx_ncp_conn
suffix:semicolon
)brace
suffix:semicolon
DECL|function|ipx_sk
r_static
r_inline
r_struct
id|ipx_sock
op_star
id|ipx_sk
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
(brace
r_return
(paren
r_struct
id|ipx_sock
op_star
)paren
id|sk
suffix:semicolon
)brace
DECL|macro|IPX_SKB_CB
mdefine_line|#define IPX_SKB_CB(__skb) ((struct ipx_cb *)&amp;((__skb)-&gt;cb[0]))
macro_line|#endif
DECL|macro|IPX_MIN_EPHEMERAL_SOCKET
mdefine_line|#define IPX_MIN_EPHEMERAL_SOCKET&t;0x4000
DECL|macro|IPX_MAX_EPHEMERAL_SOCKET
mdefine_line|#define IPX_MAX_EPHEMERAL_SOCKET&t;0x7fff
r_extern
r_struct
id|list_head
id|ipx_routes
suffix:semicolon
r_extern
id|rwlock_t
id|ipx_routes_lock
suffix:semicolon
r_extern
r_struct
id|list_head
id|ipx_interfaces
suffix:semicolon
r_extern
r_struct
id|ipx_interface
op_star
id|ipx_interfaces_head
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|spinlock_t
id|ipx_interfaces_lock
suffix:semicolon
r_extern
r_struct
id|ipx_interface
op_star
id|ipx_primary_net
suffix:semicolon
r_extern
r_int
id|ipx_proc_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|ipx_proc_exit
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_const
r_char
op_star
id|ipx_frame_name
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_const
r_char
op_star
id|ipx_device_name
c_func
(paren
r_struct
id|ipx_interface
op_star
id|intrfc
)paren
suffix:semicolon
DECL|function|ipxitf_hold
r_static
id|__inline__
r_void
id|ipxitf_hold
c_func
(paren
r_struct
id|ipx_interface
op_star
id|intrfc
)paren
(brace
id|atomic_inc
c_func
(paren
op_amp
id|intrfc-&gt;refcnt
)paren
suffix:semicolon
)brace
r_extern
r_void
id|ipxitf_down
c_func
(paren
r_struct
id|ipx_interface
op_star
id|intrfc
)paren
suffix:semicolon
DECL|function|ipxitf_put
r_static
id|__inline__
r_void
id|ipxitf_put
c_func
(paren
r_struct
id|ipx_interface
op_star
id|intrfc
)paren
(brace
r_if
c_cond
(paren
id|atomic_dec_and_test
c_func
(paren
op_amp
id|intrfc-&gt;refcnt
)paren
)paren
id|ipxitf_down
c_func
(paren
id|intrfc
)paren
suffix:semicolon
)brace
DECL|function|ipxrtr_hold
r_static
id|__inline__
r_void
id|ipxrtr_hold
c_func
(paren
r_struct
id|ipx_route
op_star
id|rt
)paren
(brace
id|atomic_inc
c_func
(paren
op_amp
id|rt-&gt;refcnt
)paren
suffix:semicolon
)brace
DECL|function|ipxrtr_put
r_static
id|__inline__
r_void
id|ipxrtr_put
c_func
(paren
r_struct
id|ipx_route
op_star
id|rt
)paren
(brace
r_if
c_cond
(paren
id|atomic_dec_and_test
c_func
(paren
op_amp
id|rt-&gt;refcnt
)paren
)paren
id|kfree
c_func
(paren
id|rt
)paren
suffix:semicolon
)brace
macro_line|#endif /* _NET_INET_IPX_H_ */
eof
