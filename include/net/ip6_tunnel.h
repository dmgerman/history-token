multiline_comment|/*&n; * $Id$&n; */
macro_line|#ifndef _NET_IP6_TUNNEL_H
DECL|macro|_NET_IP6_TUNNEL_H
mdefine_line|#define _NET_IP6_TUNNEL_H
macro_line|#include &lt;linux/ipv6.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/ip6_tunnel.h&gt;
multiline_comment|/* capable of sending packets */
DECL|macro|IP6_TNL_F_CAP_XMIT
mdefine_line|#define IP6_TNL_F_CAP_XMIT 0x10000
multiline_comment|/* capable of receiving packets */
DECL|macro|IP6_TNL_F_CAP_RCV
mdefine_line|#define IP6_TNL_F_CAP_RCV 0x20000
DECL|macro|IP6_TNL_MAX
mdefine_line|#define IP6_TNL_MAX 128
multiline_comment|/* IPv6 tunnel */
DECL|struct|ip6_tnl
r_struct
id|ip6_tnl
(brace
DECL|member|next
r_struct
id|ip6_tnl
op_star
id|next
suffix:semicolon
multiline_comment|/* next tunnel in list */
DECL|member|dev
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
multiline_comment|/* virtual device associated with tunnel */
DECL|member|stat
r_struct
id|net_device_stats
id|stat
suffix:semicolon
multiline_comment|/* statistics for tunnel device */
DECL|member|recursion
r_int
id|recursion
suffix:semicolon
multiline_comment|/* depth of hard_start_xmit recursion */
DECL|member|parms
r_struct
id|ip6_tnl_parm
id|parms
suffix:semicolon
multiline_comment|/* tunnel configuration paramters */
DECL|member|fl
r_struct
id|flowi
id|fl
suffix:semicolon
multiline_comment|/* flowi template for xmit */
)brace
suffix:semicolon
multiline_comment|/* Tunnel encapsulation limit destination sub-option */
DECL|struct|ipv6_tlv_tnl_enc_lim
r_struct
id|ipv6_tlv_tnl_enc_lim
(brace
DECL|member|type
id|__u8
id|type
suffix:semicolon
multiline_comment|/* type-code for option         */
DECL|member|length
id|__u8
id|length
suffix:semicolon
multiline_comment|/* option length                */
DECL|member|encap_limit
id|__u8
id|encap_limit
suffix:semicolon
multiline_comment|/* tunnel encapsulation limit   */
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
macro_line|#ifdef __KERNEL__
macro_line|#ifdef CONFIG_IPV6_TUNNEL
r_extern
r_int
id|__init
id|ip6_tunnel_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|ip6_tunnel_cleanup
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif
macro_line|#endif
eof
