multiline_comment|/*&n; *&t;ipddp.h: Header for IP-over-DDP driver for Linux.&n; */
macro_line|#ifndef __LINUX_IPDDP_H
DECL|macro|__LINUX_IPDDP_H
mdefine_line|#define __LINUX_IPDDP_H
macro_line|#ifdef __KERNEL__
DECL|macro|SIOCADDIPDDPRT
mdefine_line|#define SIOCADDIPDDPRT   (SIOCDEVPRIVATE)
DECL|macro|SIOCDELIPDDPRT
mdefine_line|#define SIOCDELIPDDPRT   (SIOCDEVPRIVATE+1)
DECL|macro|SIOCFINDIPDDPRT
mdefine_line|#define SIOCFINDIPDDPRT  (SIOCDEVPRIVATE+2)
DECL|struct|ipddp_route
r_struct
id|ipddp_route
(brace
DECL|member|dev
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
multiline_comment|/* Carrier device */
DECL|member|ip
id|__u32
id|ip
suffix:semicolon
multiline_comment|/* IP address */
DECL|member|at
r_struct
id|at_addr
id|at
suffix:semicolon
multiline_comment|/* Gateway appletalk address */
DECL|member|flags
r_int
id|flags
suffix:semicolon
DECL|member|next
r_struct
id|ipddp_route
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|IPDDP_ENCAP
mdefine_line|#define IPDDP_ENCAP&t;1
DECL|macro|IPDDP_DECAP
mdefine_line|#define IPDDP_DECAP&t;2
macro_line|#endif&t;/* __KERNEL__ */
macro_line|#endif&t;/* __LINUX_IPDDP_H */
eof
