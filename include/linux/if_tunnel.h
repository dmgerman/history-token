macro_line|#ifndef _IF_TUNNEL_H_
DECL|macro|_IF_TUNNEL_H_
mdefine_line|#define _IF_TUNNEL_H_
DECL|macro|SIOCGETTUNNEL
mdefine_line|#define SIOCGETTUNNEL   (SIOCDEVPRIVATE + 0)
DECL|macro|SIOCADDTUNNEL
mdefine_line|#define SIOCADDTUNNEL   (SIOCDEVPRIVATE + 1)
DECL|macro|SIOCDELTUNNEL
mdefine_line|#define SIOCDELTUNNEL   (SIOCDEVPRIVATE + 2)
DECL|macro|SIOCCHGTUNNEL
mdefine_line|#define SIOCCHGTUNNEL   (SIOCDEVPRIVATE + 3)
DECL|macro|GRE_CSUM
mdefine_line|#define GRE_CSUM&t;__constant_htons(0x8000)
DECL|macro|GRE_ROUTING
mdefine_line|#define GRE_ROUTING&t;__constant_htons(0x4000)
DECL|macro|GRE_KEY
mdefine_line|#define GRE_KEY&t;&t;__constant_htons(0x2000)
DECL|macro|GRE_SEQ
mdefine_line|#define GRE_SEQ&t;&t;__constant_htons(0x1000)
DECL|macro|GRE_STRICT
mdefine_line|#define GRE_STRICT&t;__constant_htons(0x0800)
DECL|macro|GRE_REC
mdefine_line|#define GRE_REC&t;&t;__constant_htons(0x0700)
DECL|macro|GRE_FLAGS
mdefine_line|#define GRE_FLAGS&t;__constant_htons(0x00F8)
DECL|macro|GRE_VERSION
mdefine_line|#define GRE_VERSION&t;__constant_htons(0x0007)
DECL|struct|ip_tunnel_parm
r_struct
id|ip_tunnel_parm
(brace
DECL|member|name
r_char
id|name
(braket
id|IFNAMSIZ
)braket
suffix:semicolon
DECL|member|link
r_int
id|link
suffix:semicolon
DECL|member|i_flags
id|__u16
id|i_flags
suffix:semicolon
DECL|member|o_flags
id|__u16
id|o_flags
suffix:semicolon
DECL|member|i_key
id|__u32
id|i_key
suffix:semicolon
DECL|member|o_key
id|__u32
id|o_key
suffix:semicolon
DECL|member|iph
r_struct
id|iphdr
id|iph
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* _IF_TUNNEL_H_ */
eof
