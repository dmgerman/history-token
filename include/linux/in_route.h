macro_line|#ifndef _LINUX_IN_ROUTE_H
DECL|macro|_LINUX_IN_ROUTE_H
mdefine_line|#define _LINUX_IN_ROUTE_H
multiline_comment|/* IPv4 routing cache flags */
DECL|macro|RTCF_DEAD
mdefine_line|#define RTCF_DEAD&t;RTNH_F_DEAD
DECL|macro|RTCF_ONLINK
mdefine_line|#define RTCF_ONLINK&t;RTNH_F_ONLINK
multiline_comment|/* Obsolete flag. About to be deleted */
DECL|macro|RTCF_NOPMTUDISC
mdefine_line|#define RTCF_NOPMTUDISC RTM_F_NOPMTUDISC
DECL|macro|RTCF_NOTIFY
mdefine_line|#define RTCF_NOTIFY&t;0x00010000
DECL|macro|RTCF_DIRECTDST
mdefine_line|#define RTCF_DIRECTDST&t;0x00020000
DECL|macro|RTCF_REDIRECTED
mdefine_line|#define RTCF_REDIRECTED&t;0x00040000
DECL|macro|RTCF_TPROXY
mdefine_line|#define RTCF_TPROXY&t;0x00080000
DECL|macro|RTCF_FAST
mdefine_line|#define RTCF_FAST&t;0x00200000
DECL|macro|RTCF_MASQ
mdefine_line|#define RTCF_MASQ&t;0x00400000
DECL|macro|RTCF_SNAT
mdefine_line|#define RTCF_SNAT&t;0x00800000
DECL|macro|RTCF_DOREDIRECT
mdefine_line|#define RTCF_DOREDIRECT 0x01000000
DECL|macro|RTCF_DIRECTSRC
mdefine_line|#define RTCF_DIRECTSRC&t;0x04000000
DECL|macro|RTCF_DNAT
mdefine_line|#define RTCF_DNAT&t;0x08000000
DECL|macro|RTCF_BROADCAST
mdefine_line|#define RTCF_BROADCAST&t;0x10000000
DECL|macro|RTCF_MULTICAST
mdefine_line|#define RTCF_MULTICAST&t;0x20000000
DECL|macro|RTCF_REJECT
mdefine_line|#define RTCF_REJECT&t;0x40000000
DECL|macro|RTCF_LOCAL
mdefine_line|#define RTCF_LOCAL&t;0x80000000
DECL|macro|RTCF_NAT
mdefine_line|#define RTCF_NAT&t;(RTCF_DNAT|RTCF_SNAT)
DECL|macro|RT_TOS
mdefine_line|#define RT_TOS(tos)&t;((tos)&amp;IPTOS_TOS_MASK)
macro_line|#endif /* _LINUX_IN_ROUTE_H */
eof
