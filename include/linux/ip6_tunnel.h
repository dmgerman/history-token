multiline_comment|/*&n; * $Id$&n; */
macro_line|#ifndef _IP6_TUNNEL_H
DECL|macro|_IP6_TUNNEL_H
mdefine_line|#define _IP6_TUNNEL_H
DECL|macro|IPV6_TLV_TNL_ENCAP_LIMIT
mdefine_line|#define IPV6_TLV_TNL_ENCAP_LIMIT 4
DECL|macro|IPV6_DEFAULT_TNL_ENCAP_LIMIT
mdefine_line|#define IPV6_DEFAULT_TNL_ENCAP_LIMIT 4
multiline_comment|/* don&squot;t add encapsulation limit if one isn&squot;t present in inner packet */
DECL|macro|IP6_TNL_F_IGN_ENCAP_LIMIT
mdefine_line|#define IP6_TNL_F_IGN_ENCAP_LIMIT 0x1
multiline_comment|/* copy the traffic class field from the inner packet */
DECL|macro|IP6_TNL_F_USE_ORIG_TCLASS
mdefine_line|#define IP6_TNL_F_USE_ORIG_TCLASS 0x2
multiline_comment|/* copy the flowlabel from the inner packet */
DECL|macro|IP6_TNL_F_USE_ORIG_FLOWLABEL
mdefine_line|#define IP6_TNL_F_USE_ORIG_FLOWLABEL 0x4
multiline_comment|/* being used for Mobile IPv6 */
DECL|macro|IP6_TNL_F_MIP6_DEV
mdefine_line|#define IP6_TNL_F_MIP6_DEV 0x8
DECL|struct|ip6_tnl_parm
r_struct
id|ip6_tnl_parm
(brace
DECL|member|name
r_char
id|name
(braket
id|IFNAMSIZ
)braket
suffix:semicolon
multiline_comment|/* name of tunnel device */
DECL|member|link
r_int
id|link
suffix:semicolon
multiline_comment|/* ifindex of underlying L2 interface */
DECL|member|proto
id|__u8
id|proto
suffix:semicolon
multiline_comment|/* tunnel protocol */
DECL|member|encap_limit
id|__u8
id|encap_limit
suffix:semicolon
multiline_comment|/* encapsulation limit for tunnel */
DECL|member|hop_limit
id|__u8
id|hop_limit
suffix:semicolon
multiline_comment|/* hop limit for tunnel */
DECL|member|flowinfo
id|__u32
id|flowinfo
suffix:semicolon
multiline_comment|/* traffic class and flowlabel for tunnel */
DECL|member|flags
id|__u32
id|flags
suffix:semicolon
multiline_comment|/* tunnel flags */
DECL|member|laddr
r_struct
id|in6_addr
id|laddr
suffix:semicolon
multiline_comment|/* local tunnel end-point address */
DECL|member|raddr
r_struct
id|in6_addr
id|raddr
suffix:semicolon
multiline_comment|/* remote tunnel end-point address */
)brace
suffix:semicolon
macro_line|#endif
eof
