macro_line|#ifndef _LINUX_SOCKET_H
DECL|macro|_LINUX_SOCKET_H
mdefine_line|#define _LINUX_SOCKET_H
macro_line|#if defined(__KERNEL__) || !defined(__GLIBC__) || (__GLIBC__ &lt; 2)
macro_line|#include &lt;asm/socket.h&gt;&t;&t;&t;/* arch-dependent defines&t;*/
macro_line|#include &lt;linux/sockios.h&gt;&t;&t;/* the SIOCxxx I/O controls&t;*/
macro_line|#include &lt;linux/uio.h&gt;&t;&t;&t;/* iovec support&t;&t;*/
macro_line|#include &lt;linux/types.h&gt;&t;&t;/* pid_t&t;&t;&t;*/
DECL|typedef|sa_family_t
r_typedef
r_int
r_int
id|sa_family_t
suffix:semicolon
multiline_comment|/*&n; *&t;1003.1g requires sa_family_t and that sa_data is char.&n; */
DECL|struct|sockaddr
r_struct
id|sockaddr
(brace
DECL|member|sa_family
id|sa_family_t
id|sa_family
suffix:semicolon
multiline_comment|/* address family, AF_xxx&t;*/
DECL|member|sa_data
r_char
id|sa_data
(braket
l_int|14
)braket
suffix:semicolon
multiline_comment|/* 14 bytes of protocol address&t;*/
)brace
suffix:semicolon
DECL|struct|linger
r_struct
id|linger
(brace
DECL|member|l_onoff
r_int
id|l_onoff
suffix:semicolon
multiline_comment|/* Linger active&t;&t;*/
DECL|member|l_linger
r_int
id|l_linger
suffix:semicolon
multiline_comment|/* How long to linger for&t;*/
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;As we do 4.4BSD message passing we use a 4.4BSD message passing&n; *&t;system, not 4.3. Thus msg_accrights(len) are now missing. They&n; *&t;belong in an obscure libc emulation or the bin.&n; */
DECL|struct|msghdr
r_struct
id|msghdr
(brace
DECL|member|msg_name
r_void
op_star
id|msg_name
suffix:semicolon
multiline_comment|/* Socket name&t;&t;&t;*/
DECL|member|msg_namelen
r_int
id|msg_namelen
suffix:semicolon
multiline_comment|/* Length of name&t;&t;*/
DECL|member|msg_iov
r_struct
id|iovec
op_star
id|msg_iov
suffix:semicolon
multiline_comment|/* Data blocks&t;&t;&t;*/
DECL|member|msg_iovlen
id|__kernel_size_t
id|msg_iovlen
suffix:semicolon
multiline_comment|/* Number of blocks&t;&t;*/
DECL|member|msg_control
r_void
op_star
id|msg_control
suffix:semicolon
multiline_comment|/* Per protocol magic (eg BSD file descriptor passing) */
DECL|member|msg_controllen
id|__kernel_size_t
id|msg_controllen
suffix:semicolon
multiline_comment|/* Length of cmsg list */
DECL|member|msg_flags
r_int
id|msg_flags
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;POSIX 1003.1g - ancillary data object information&n; *&t;Ancillary data consits of a sequence of pairs of&n; *&t;(cmsghdr, cmsg_data[])&n; */
DECL|struct|cmsghdr
r_struct
id|cmsghdr
(brace
DECL|member|cmsg_len
id|__kernel_size_t
id|cmsg_len
suffix:semicolon
multiline_comment|/* data byte count, including hdr */
DECL|member|cmsg_level
r_int
id|cmsg_level
suffix:semicolon
multiline_comment|/* originating protocol */
DECL|member|cmsg_type
r_int
id|cmsg_type
suffix:semicolon
multiline_comment|/* protocol-specific type */
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;Ancilliary data object information MACROS&n; *&t;Table 5-14 of POSIX 1003.1g&n; */
DECL|macro|__CMSG_NXTHDR
mdefine_line|#define __CMSG_NXTHDR(ctl, len, cmsg) __cmsg_nxthdr((ctl),(len),(cmsg))
DECL|macro|CMSG_NXTHDR
mdefine_line|#define CMSG_NXTHDR(mhdr, cmsg) cmsg_nxthdr((mhdr), (cmsg))
DECL|macro|CMSG_ALIGN
mdefine_line|#define CMSG_ALIGN(len) ( ((len)+sizeof(long)-1) &amp; ~(sizeof(long)-1) )
DECL|macro|CMSG_DATA
mdefine_line|#define CMSG_DATA(cmsg)&t;((void *)((char *)(cmsg) + CMSG_ALIGN(sizeof(struct cmsghdr))))
DECL|macro|CMSG_SPACE
mdefine_line|#define CMSG_SPACE(len) (CMSG_ALIGN(sizeof(struct cmsghdr)) + CMSG_ALIGN(len))
DECL|macro|CMSG_LEN
mdefine_line|#define CMSG_LEN(len) (CMSG_ALIGN(sizeof(struct cmsghdr)) + (len))
DECL|macro|__CMSG_FIRSTHDR
mdefine_line|#define __CMSG_FIRSTHDR(ctl,len) ((len) &gt;= sizeof(struct cmsghdr) ? &bslash;&n;&t;&t;&t;&t;  (struct cmsghdr *)(ctl) : &bslash;&n;&t;&t;&t;&t;  (struct cmsghdr *)NULL)
DECL|macro|CMSG_FIRSTHDR
mdefine_line|#define CMSG_FIRSTHDR(msg)&t;__CMSG_FIRSTHDR((msg)-&gt;msg_control, (msg)-&gt;msg_controllen)
multiline_comment|/*&n; *&t;This mess will go away with glibc&n; */
macro_line|#ifdef __KERNEL__
DECL|macro|__KINLINE
mdefine_line|#define __KINLINE static inline
macro_line|#elif  defined(__GNUC__) 
DECL|macro|__KINLINE
mdefine_line|#define __KINLINE static __inline__
macro_line|#elif defined(__cplusplus)
DECL|macro|__KINLINE
mdefine_line|#define __KINLINE static inline
macro_line|#else
DECL|macro|__KINLINE
mdefine_line|#define __KINLINE static
macro_line|#endif
multiline_comment|/*&n; *&t;Get the next cmsg header&n; *&n; *&t;PLEASE, do not touch this function. If you think, that it is&n; *&t;incorrect, grep kernel sources and think about consequences&n; *&t;before trying to improve it.&n; *&n; *&t;Now it always returns valid, not truncated ancillary object&n; *&t;HEADER. But caller still MUST check, that cmsg-&gt;cmsg_len is&n; *&t;inside range, given by msg-&gt;msg_controllen before using&n; *&t;ansillary object DATA.&t;&t;&t;&t;--ANK (980731)&n; */
DECL|function|__cmsg_nxthdr
id|__KINLINE
r_struct
id|cmsghdr
op_star
id|__cmsg_nxthdr
c_func
(paren
r_void
op_star
id|__ctl
comma
id|__kernel_size_t
id|__size
comma
r_struct
id|cmsghdr
op_star
id|__cmsg
)paren
(brace
r_struct
id|cmsghdr
op_star
id|__ptr
suffix:semicolon
id|__ptr
op_assign
(paren
r_struct
id|cmsghdr
op_star
)paren
(paren
(paren
(paren
r_int
r_char
op_star
)paren
id|__cmsg
)paren
op_plus
id|CMSG_ALIGN
c_func
(paren
id|__cmsg-&gt;cmsg_len
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
r_int
r_int
)paren
(paren
(paren
r_char
op_star
)paren
(paren
id|__ptr
op_plus
l_int|1
)paren
op_minus
(paren
r_char
op_star
)paren
id|__ctl
)paren
OG
id|__size
)paren
r_return
(paren
r_struct
id|cmsghdr
op_star
)paren
l_int|0
suffix:semicolon
r_return
id|__ptr
suffix:semicolon
)brace
DECL|function|cmsg_nxthdr
id|__KINLINE
r_struct
id|cmsghdr
op_star
id|cmsg_nxthdr
(paren
r_struct
id|msghdr
op_star
id|__msg
comma
r_struct
id|cmsghdr
op_star
id|__cmsg
)paren
(brace
r_return
id|__cmsg_nxthdr
c_func
(paren
id|__msg-&gt;msg_control
comma
id|__msg-&gt;msg_controllen
comma
id|__cmsg
)paren
suffix:semicolon
)brace
multiline_comment|/* &quot;Socket&quot;-level control message types: */
DECL|macro|SCM_RIGHTS
mdefine_line|#define&t;SCM_RIGHTS&t;0x01&t;&t;/* rw: access rights (array of int) */
DECL|macro|SCM_CREDENTIALS
mdefine_line|#define SCM_CREDENTIALS 0x02&t;&t;/* rw: struct ucred&t;&t;*/
DECL|macro|SCM_CONNECT
mdefine_line|#define SCM_CONNECT&t;0x03&t;&t;/* rw: struct scm_connect&t;*/
DECL|struct|ucred
r_struct
id|ucred
(brace
DECL|member|pid
id|__u32
id|pid
suffix:semicolon
DECL|member|uid
id|__u32
id|uid
suffix:semicolon
DECL|member|gid
id|__u32
id|gid
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Supported address families. */
DECL|macro|AF_UNSPEC
mdefine_line|#define AF_UNSPEC&t;0
DECL|macro|AF_UNIX
mdefine_line|#define AF_UNIX&t;&t;1&t;/* Unix domain sockets &t;&t;*/
DECL|macro|AF_LOCAL
mdefine_line|#define AF_LOCAL&t;1&t;/* POSIX name for AF_UNIX&t;*/
DECL|macro|AF_INET
mdefine_line|#define AF_INET&t;&t;2&t;/* Internet IP Protocol &t;*/
DECL|macro|AF_AX25
mdefine_line|#define AF_AX25&t;&t;3&t;/* Amateur Radio AX.25 &t;&t;*/
DECL|macro|AF_IPX
mdefine_line|#define AF_IPX&t;&t;4&t;/* Novell IPX &t;&t;&t;*/
DECL|macro|AF_APPLETALK
mdefine_line|#define AF_APPLETALK&t;5&t;/* AppleTalk DDP &t;&t;*/
DECL|macro|AF_NETROM
mdefine_line|#define AF_NETROM&t;6&t;/* Amateur Radio NET/ROM &t;*/
DECL|macro|AF_BRIDGE
mdefine_line|#define AF_BRIDGE&t;7&t;/* Multiprotocol bridge &t;*/
DECL|macro|AF_ATMPVC
mdefine_line|#define AF_ATMPVC&t;8&t;/* ATM PVCs&t;&t;&t;*/
DECL|macro|AF_X25
mdefine_line|#define AF_X25&t;&t;9&t;/* Reserved for X.25 project &t;*/
DECL|macro|AF_INET6
mdefine_line|#define AF_INET6&t;10&t;/* IP version 6&t;&t;&t;*/
DECL|macro|AF_ROSE
mdefine_line|#define AF_ROSE&t;&t;11&t;/* Amateur Radio X.25 PLP&t;*/
DECL|macro|AF_DECnet
mdefine_line|#define AF_DECnet&t;12&t;/* Reserved for DECnet project&t;*/
DECL|macro|AF_NETBEUI
mdefine_line|#define AF_NETBEUI&t;13&t;/* Reserved for 802.2LLC project*/
DECL|macro|AF_SECURITY
mdefine_line|#define AF_SECURITY&t;14&t;/* Security callback pseudo AF */
DECL|macro|AF_KEY
mdefine_line|#define AF_KEY&t;&t;15      /* PF_KEY key management API */
DECL|macro|AF_NETLINK
mdefine_line|#define AF_NETLINK&t;16
DECL|macro|AF_ROUTE
mdefine_line|#define AF_ROUTE&t;AF_NETLINK /* Alias to emulate 4.4BSD */
DECL|macro|AF_PACKET
mdefine_line|#define AF_PACKET&t;17&t;/* Packet family&t;&t;*/
DECL|macro|AF_ASH
mdefine_line|#define AF_ASH&t;&t;18&t;/* Ash&t;&t;&t;&t;*/
DECL|macro|AF_ECONET
mdefine_line|#define AF_ECONET&t;19&t;/* Acorn Econet&t;&t;&t;*/
DECL|macro|AF_ATMSVC
mdefine_line|#define AF_ATMSVC&t;20&t;/* ATM SVCs&t;&t;&t;*/
DECL|macro|AF_SNA
mdefine_line|#define AF_SNA&t;&t;22&t;/* Linux SNA Project (nutters!) */
DECL|macro|AF_IRDA
mdefine_line|#define AF_IRDA&t;&t;23&t;/* IRDA sockets&t;&t;&t;*/
DECL|macro|AF_PPPOX
mdefine_line|#define AF_PPPOX&t;24&t;/* PPPoX sockets&t;&t;*/
DECL|macro|AF_WANPIPE
mdefine_line|#define AF_WANPIPE&t;25&t;/* Wanpipe API Sockets */
DECL|macro|AF_BLUETOOTH
mdefine_line|#define AF_BLUETOOTH&t;31&t;/* Bluetooth sockets &t;&t;*/
DECL|macro|AF_MAX
mdefine_line|#define AF_MAX&t;&t;32&t;/* For now.. */
multiline_comment|/* Protocol families, same as address families. */
DECL|macro|PF_UNSPEC
mdefine_line|#define PF_UNSPEC&t;AF_UNSPEC
DECL|macro|PF_UNIX
mdefine_line|#define PF_UNIX&t;&t;AF_UNIX
DECL|macro|PF_LOCAL
mdefine_line|#define PF_LOCAL&t;AF_LOCAL
DECL|macro|PF_INET
mdefine_line|#define PF_INET&t;&t;AF_INET
DECL|macro|PF_AX25
mdefine_line|#define PF_AX25&t;&t;AF_AX25
DECL|macro|PF_IPX
mdefine_line|#define PF_IPX&t;&t;AF_IPX
DECL|macro|PF_APPLETALK
mdefine_line|#define PF_APPLETALK&t;AF_APPLETALK
DECL|macro|PF_NETROM
mdefine_line|#define&t;PF_NETROM&t;AF_NETROM
DECL|macro|PF_BRIDGE
mdefine_line|#define PF_BRIDGE&t;AF_BRIDGE
DECL|macro|PF_ATMPVC
mdefine_line|#define PF_ATMPVC&t;AF_ATMPVC
DECL|macro|PF_X25
mdefine_line|#define PF_X25&t;&t;AF_X25
DECL|macro|PF_INET6
mdefine_line|#define PF_INET6&t;AF_INET6
DECL|macro|PF_ROSE
mdefine_line|#define PF_ROSE&t;&t;AF_ROSE
DECL|macro|PF_DECnet
mdefine_line|#define PF_DECnet&t;AF_DECnet
DECL|macro|PF_NETBEUI
mdefine_line|#define PF_NETBEUI&t;AF_NETBEUI
DECL|macro|PF_SECURITY
mdefine_line|#define PF_SECURITY&t;AF_SECURITY
DECL|macro|PF_KEY
mdefine_line|#define PF_KEY&t;&t;AF_KEY
DECL|macro|PF_NETLINK
mdefine_line|#define PF_NETLINK&t;AF_NETLINK
DECL|macro|PF_ROUTE
mdefine_line|#define PF_ROUTE&t;AF_ROUTE
DECL|macro|PF_PACKET
mdefine_line|#define PF_PACKET&t;AF_PACKET
DECL|macro|PF_ASH
mdefine_line|#define PF_ASH&t;&t;AF_ASH
DECL|macro|PF_ECONET
mdefine_line|#define PF_ECONET&t;AF_ECONET
DECL|macro|PF_ATMSVC
mdefine_line|#define PF_ATMSVC&t;AF_ATMSVC
DECL|macro|PF_SNA
mdefine_line|#define PF_SNA&t;&t;AF_SNA
DECL|macro|PF_IRDA
mdefine_line|#define PF_IRDA&t;&t;AF_IRDA
DECL|macro|PF_PPPOX
mdefine_line|#define PF_PPPOX&t;AF_PPPOX
DECL|macro|PF_WANPIPE
mdefine_line|#define PF_WANPIPE&t;AF_WANPIPE
DECL|macro|PF_BLUETOOTH
mdefine_line|#define PF_BLUETOOTH&t;AF_BLUETOOTH
DECL|macro|PF_MAX
mdefine_line|#define PF_MAX&t;&t;AF_MAX
multiline_comment|/* Maximum queue length specifiable by listen.  */
DECL|macro|SOMAXCONN
mdefine_line|#define SOMAXCONN&t;128
multiline_comment|/* Flags we can use with send/ and recv. &n;   Added those for 1003.1g not all are supported yet&n; */
DECL|macro|MSG_OOB
mdefine_line|#define MSG_OOB&t;&t;1
DECL|macro|MSG_PEEK
mdefine_line|#define MSG_PEEK&t;2
DECL|macro|MSG_DONTROUTE
mdefine_line|#define MSG_DONTROUTE&t;4
DECL|macro|MSG_TRYHARD
mdefine_line|#define MSG_TRYHARD     4       /* Synonym for MSG_DONTROUTE for DECnet */
DECL|macro|MSG_CTRUNC
mdefine_line|#define MSG_CTRUNC&t;8
DECL|macro|MSG_PROBE
mdefine_line|#define MSG_PROBE&t;0x10&t;/* Do not send. Only probe path f.e. for MTU */
DECL|macro|MSG_TRUNC
mdefine_line|#define MSG_TRUNC&t;0x20
DECL|macro|MSG_DONTWAIT
mdefine_line|#define MSG_DONTWAIT&t;0x40&t;/* Nonblocking io&t;&t; */
DECL|macro|MSG_EOR
mdefine_line|#define MSG_EOR         0x80&t;/* End of record */
DECL|macro|MSG_WAITALL
mdefine_line|#define MSG_WAITALL&t;0x100&t;/* Wait for a full request */
DECL|macro|MSG_FIN
mdefine_line|#define MSG_FIN         0x200
DECL|macro|MSG_SYN
mdefine_line|#define MSG_SYN&t;&t;0x400
DECL|macro|MSG_CONFIRM
mdefine_line|#define MSG_CONFIRM&t;0x800&t;/* Confirm path validity */
DECL|macro|MSG_RST
mdefine_line|#define MSG_RST&t;&t;0x1000
DECL|macro|MSG_ERRQUEUE
mdefine_line|#define MSG_ERRQUEUE&t;0x2000&t;/* Fetch message from error queue */
DECL|macro|MSG_NOSIGNAL
mdefine_line|#define MSG_NOSIGNAL&t;0x4000&t;/* Do not generate SIGPIPE */
DECL|macro|MSG_MORE
mdefine_line|#define MSG_MORE&t;0x8000&t;/* Sender will send more */
DECL|macro|MSG_EOF
mdefine_line|#define MSG_EOF         MSG_FIN
multiline_comment|/* Setsockoptions(2) level. Thanks to BSD these must match IPPROTO_xxx */
DECL|macro|SOL_IP
mdefine_line|#define SOL_IP&t;&t;0
multiline_comment|/* #define SOL_ICMP&t;1&t;No-no-no! Due to Linux :-) we cannot use SOL_ICMP=1 */
DECL|macro|SOL_TCP
mdefine_line|#define SOL_TCP&t;&t;6
DECL|macro|SOL_UDP
mdefine_line|#define SOL_UDP&t;&t;17
DECL|macro|SOL_IPV6
mdefine_line|#define SOL_IPV6&t;41
DECL|macro|SOL_ICMPV6
mdefine_line|#define SOL_ICMPV6&t;58
DECL|macro|SOL_RAW
mdefine_line|#define SOL_RAW&t;&t;255
DECL|macro|SOL_IPX
mdefine_line|#define SOL_IPX&t;&t;256
DECL|macro|SOL_AX25
mdefine_line|#define SOL_AX25&t;257
DECL|macro|SOL_ATALK
mdefine_line|#define SOL_ATALK&t;258
DECL|macro|SOL_NETROM
mdefine_line|#define SOL_NETROM&t;259
DECL|macro|SOL_ROSE
mdefine_line|#define SOL_ROSE&t;260
DECL|macro|SOL_DECNET
mdefine_line|#define SOL_DECNET&t;261
DECL|macro|SOL_X25
mdefine_line|#define&t;SOL_X25&t;&t;262
DECL|macro|SOL_PACKET
mdefine_line|#define SOL_PACKET&t;263
DECL|macro|SOL_ATM
mdefine_line|#define SOL_ATM&t;&t;264&t;/* ATM layer (cell level) */
DECL|macro|SOL_AAL
mdefine_line|#define SOL_AAL&t;&t;265&t;/* ATM Adaption Layer (packet level) */
DECL|macro|SOL_IRDA
mdefine_line|#define SOL_IRDA        266
multiline_comment|/* IPX options */
DECL|macro|IPX_TYPE
mdefine_line|#define IPX_TYPE&t;1
macro_line|#ifdef __KERNEL__
r_extern
r_int
id|memcpy_fromiovec
c_func
(paren
r_int
r_char
op_star
id|kdata
comma
r_struct
id|iovec
op_star
id|iov
comma
r_int
id|len
)paren
suffix:semicolon
r_extern
r_int
id|memcpy_fromiovecend
c_func
(paren
r_int
r_char
op_star
id|kdata
comma
r_struct
id|iovec
op_star
id|iov
comma
r_int
id|offset
comma
r_int
id|len
)paren
suffix:semicolon
r_extern
r_int
id|csum_partial_copy_fromiovecend
c_func
(paren
r_int
r_char
op_star
id|kdata
comma
r_struct
id|iovec
op_star
id|iov
comma
r_int
id|offset
comma
r_int
r_int
id|len
comma
r_int
op_star
id|csump
)paren
suffix:semicolon
r_extern
r_int
id|verify_iovec
c_func
(paren
r_struct
id|msghdr
op_star
id|m
comma
r_struct
id|iovec
op_star
id|iov
comma
r_char
op_star
id|address
comma
r_int
id|mode
)paren
suffix:semicolon
r_extern
r_int
id|memcpy_toiovec
c_func
(paren
r_struct
id|iovec
op_star
id|v
comma
r_int
r_char
op_star
id|kdata
comma
r_int
id|len
)paren
suffix:semicolon
r_extern
r_void
id|memcpy_tokerneliovec
c_func
(paren
r_struct
id|iovec
op_star
id|iov
comma
r_int
r_char
op_star
id|kdata
comma
r_int
id|len
)paren
suffix:semicolon
r_extern
r_int
id|move_addr_to_user
c_func
(paren
r_void
op_star
id|kaddr
comma
r_int
id|klen
comma
r_void
op_star
id|uaddr
comma
r_int
op_star
id|ulen
)paren
suffix:semicolon
r_extern
r_int
id|move_addr_to_kernel
c_func
(paren
r_void
op_star
id|uaddr
comma
r_int
id|ulen
comma
r_void
op_star
id|kaddr
)paren
suffix:semicolon
r_extern
r_int
id|put_cmsg
c_func
(paren
r_struct
id|msghdr
op_star
comma
r_int
id|level
comma
r_int
id|type
comma
r_int
id|len
comma
r_void
op_star
id|data
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif /* not kernel and not glibc */
macro_line|#endif /* _LINUX_SOCKET_H */
eof
