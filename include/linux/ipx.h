macro_line|#ifndef _IPX_H_
DECL|macro|_IPX_H_
mdefine_line|#define _IPX_H_
macro_line|#include &lt;linux/sockios.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
DECL|macro|IPX_NODE_LEN
mdefine_line|#define IPX_NODE_LEN&t;6
DECL|macro|IPX_MTU
mdefine_line|#define IPX_MTU&t;&t;576
DECL|struct|sockaddr_ipx
r_struct
id|sockaddr_ipx
(brace
DECL|member|sipx_family
id|sa_family_t
id|sipx_family
suffix:semicolon
DECL|member|sipx_port
id|__u16
id|sipx_port
suffix:semicolon
DECL|member|sipx_network
id|__u32
id|sipx_network
suffix:semicolon
DECL|member|sipx_node
r_int
r_char
id|sipx_node
(braket
id|IPX_NODE_LEN
)braket
suffix:semicolon
DECL|member|sipx_type
id|__u8
id|sipx_type
suffix:semicolon
DECL|member|sipx_zero
r_int
r_char
id|sipx_zero
suffix:semicolon
multiline_comment|/* 16 byte fill */
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;So we can fit the extra info for SIOCSIFADDR into the address nicely&n; */
DECL|macro|sipx_special
mdefine_line|#define sipx_special&t;sipx_port
DECL|macro|sipx_action
mdefine_line|#define sipx_action&t;sipx_zero
DECL|macro|IPX_DLTITF
mdefine_line|#define IPX_DLTITF&t;0
DECL|macro|IPX_CRTITF
mdefine_line|#define IPX_CRTITF&t;1
DECL|struct|ipx_route_definition
r_typedef
r_struct
id|ipx_route_definition
(brace
DECL|member|ipx_network
id|__u32
id|ipx_network
suffix:semicolon
DECL|member|ipx_router_network
id|__u32
id|ipx_router_network
suffix:semicolon
DECL|member|ipx_router_node
r_int
r_char
id|ipx_router_node
(braket
id|IPX_NODE_LEN
)braket
suffix:semicolon
DECL|typedef|ipx_route_definition
)brace
id|ipx_route_definition
suffix:semicolon
DECL|struct|ipx_interface_definition
r_typedef
r_struct
id|ipx_interface_definition
(brace
DECL|member|ipx_network
id|__u32
id|ipx_network
suffix:semicolon
DECL|member|ipx_device
r_int
r_char
id|ipx_device
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|ipx_dlink_type
r_int
r_char
id|ipx_dlink_type
suffix:semicolon
DECL|macro|IPX_FRAME_NONE
mdefine_line|#define IPX_FRAME_NONE&t;&t;0
DECL|macro|IPX_FRAME_SNAP
mdefine_line|#define IPX_FRAME_SNAP&t;&t;1
DECL|macro|IPX_FRAME_8022
mdefine_line|#define IPX_FRAME_8022&t;&t;2
DECL|macro|IPX_FRAME_ETHERII
mdefine_line|#define IPX_FRAME_ETHERII&t;3
DECL|macro|IPX_FRAME_8023
mdefine_line|#define IPX_FRAME_8023&t;&t;4
DECL|macro|IPX_FRAME_TR_8022
mdefine_line|#define IPX_FRAME_TR_8022       5 /* obsolete */
DECL|member|ipx_special
r_int
r_char
id|ipx_special
suffix:semicolon
DECL|macro|IPX_SPECIAL_NONE
mdefine_line|#define IPX_SPECIAL_NONE&t;0
DECL|macro|IPX_PRIMARY
mdefine_line|#define IPX_PRIMARY&t;&t;1
DECL|macro|IPX_INTERNAL
mdefine_line|#define IPX_INTERNAL&t;&t;2
DECL|member|ipx_node
r_int
r_char
id|ipx_node
(braket
id|IPX_NODE_LEN
)braket
suffix:semicolon
DECL|typedef|ipx_interface_definition
)brace
id|ipx_interface_definition
suffix:semicolon
DECL|struct|ipx_config_data
r_typedef
r_struct
id|ipx_config_data
(brace
DECL|member|ipxcfg_auto_select_primary
r_int
r_char
id|ipxcfg_auto_select_primary
suffix:semicolon
DECL|member|ipxcfg_auto_create_interfaces
r_int
r_char
id|ipxcfg_auto_create_interfaces
suffix:semicolon
DECL|typedef|ipx_config_data
)brace
id|ipx_config_data
suffix:semicolon
multiline_comment|/*&n; * OLD Route Definition for backward compatibility.&n; */
DECL|struct|ipx_route_def
r_struct
id|ipx_route_def
(brace
DECL|member|ipx_network
id|__u32
id|ipx_network
suffix:semicolon
DECL|member|ipx_router_network
id|__u32
id|ipx_router_network
suffix:semicolon
DECL|macro|IPX_ROUTE_NO_ROUTER
mdefine_line|#define IPX_ROUTE_NO_ROUTER&t;0
DECL|member|ipx_router_node
r_int
r_char
id|ipx_router_node
(braket
id|IPX_NODE_LEN
)braket
suffix:semicolon
DECL|member|ipx_device
r_int
r_char
id|ipx_device
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|ipx_flags
r_int
r_int
id|ipx_flags
suffix:semicolon
DECL|macro|IPX_RT_SNAP
mdefine_line|#define IPX_RT_SNAP&t;&t;8
DECL|macro|IPX_RT_8022
mdefine_line|#define IPX_RT_8022&t;&t;4
DECL|macro|IPX_RT_BLUEBOOK
mdefine_line|#define IPX_RT_BLUEBOOK&t;&t;2
DECL|macro|IPX_RT_ROUTED
mdefine_line|#define IPX_RT_ROUTED&t;&t;1
)brace
suffix:semicolon
DECL|macro|SIOCAIPXITFCRT
mdefine_line|#define SIOCAIPXITFCRT&t;&t;(SIOCPROTOPRIVATE)
DECL|macro|SIOCAIPXPRISLT
mdefine_line|#define SIOCAIPXPRISLT&t;&t;(SIOCPROTOPRIVATE+1)
DECL|macro|SIOCIPXCFGDATA
mdefine_line|#define SIOCIPXCFGDATA&t;&t;(SIOCPROTOPRIVATE+2)
DECL|macro|SIOCIPXNCPCONN
mdefine_line|#define SIOCIPXNCPCONN&t;&t;(SIOCPROTOPRIVATE+3)
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/skbuff.h&gt;
r_extern
r_int
id|ipxrtr_route_skb
c_func
(paren
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ipx_if_offset
c_func
(paren
r_int
r_int
id|ipx_net_number
)paren
suffix:semicolon
r_extern
r_void
id|ipx_remove_socket
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
suffix:semicolon
macro_line|#endif /* def __KERNEL__ */
macro_line|#endif /* def _IPX_H_ */
eof
