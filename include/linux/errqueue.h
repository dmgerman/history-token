macro_line|#ifndef _LINUX_ERRQUEUE_H
DECL|macro|_LINUX_ERRQUEUE_H
mdefine_line|#define _LINUX_ERRQUEUE_H 1
DECL|struct|sock_extended_err
r_struct
id|sock_extended_err
(brace
DECL|member|ee_errno
id|__u32
id|ee_errno
suffix:semicolon
DECL|member|ee_origin
id|__u8
id|ee_origin
suffix:semicolon
DECL|member|ee_type
id|__u8
id|ee_type
suffix:semicolon
DECL|member|ee_code
id|__u8
id|ee_code
suffix:semicolon
DECL|member|ee_pad
id|__u8
id|ee_pad
suffix:semicolon
DECL|member|ee_info
id|__u32
id|ee_info
suffix:semicolon
DECL|member|ee_data
id|__u32
id|ee_data
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|SO_EE_ORIGIN_NONE
mdefine_line|#define SO_EE_ORIGIN_NONE&t;0
DECL|macro|SO_EE_ORIGIN_LOCAL
mdefine_line|#define SO_EE_ORIGIN_LOCAL&t;1
DECL|macro|SO_EE_ORIGIN_ICMP
mdefine_line|#define SO_EE_ORIGIN_ICMP&t;2
DECL|macro|SO_EE_ORIGIN_ICMP6
mdefine_line|#define SO_EE_ORIGIN_ICMP6&t;3
DECL|macro|SO_EE_OFFENDER
mdefine_line|#define SO_EE_OFFENDER(ee)&t;((struct sockaddr*)((ee)+1))
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/config.h&gt;
DECL|macro|SKB_EXT_ERR
mdefine_line|#define SKB_EXT_ERR(skb) ((struct sock_exterr_skb *) ((skb)-&gt;cb))
DECL|struct|sock_exterr_skb
r_struct
id|sock_exterr_skb
(brace
r_union
(brace
DECL|member|h4
r_struct
id|inet_skb_parm
id|h4
suffix:semicolon
macro_line|#if defined(CONFIG_IPV6) || defined (CONFIG_IPV6_MODULE)
DECL|member|h6
r_struct
id|inet6_skb_parm
id|h6
suffix:semicolon
macro_line|#endif
DECL|member|header
)brace
id|header
suffix:semicolon
DECL|member|ee
r_struct
id|sock_extended_err
id|ee
suffix:semicolon
DECL|member|addr_offset
id|u16
id|addr_offset
suffix:semicolon
DECL|member|port
id|u16
id|port
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
macro_line|#endif
eof
