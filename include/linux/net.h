multiline_comment|/*&n; * NET&t;&t;An implementation of the SOCKET network access protocol.&n; *&t;&t;This is the master header file for the Linux NET layer,&n; *&t;&t;or, in plain English: the networking handling part of the&n; *&t;&t;kernel.&n; *&n; * Version:&t;@(#)net.h&t;1.0.3&t;05/25/93&n; *&n; * Authors:&t;Orest Zborowski, &lt;obz@Kodak.COM&gt;&n; *&t;&t;Ross Biro, &lt;bir7@leland.Stanford.Edu&gt;&n; *&t;&t;Fred N. van Kempen, &lt;waltje@uWalt.NL.Mugnet.ORG&gt;&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _LINUX_NET_H
DECL|macro|_LINUX_NET_H
mdefine_line|#define _LINUX_NET_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;linux/stringify.h&gt;
macro_line|#include &lt;asm/socket.h&gt;
r_struct
id|poll_table_struct
suffix:semicolon
r_struct
id|inode
suffix:semicolon
DECL|macro|NPROTO
mdefine_line|#define NPROTO&t;&t;32&t;&t;/* should be enough for now..&t;*/
DECL|macro|SYS_SOCKET
mdefine_line|#define SYS_SOCKET&t;1&t;&t;/* sys_socket(2)&t;&t;*/
DECL|macro|SYS_BIND
mdefine_line|#define SYS_BIND&t;2&t;&t;/* sys_bind(2)&t;&t;&t;*/
DECL|macro|SYS_CONNECT
mdefine_line|#define SYS_CONNECT&t;3&t;&t;/* sys_connect(2)&t;&t;*/
DECL|macro|SYS_LISTEN
mdefine_line|#define SYS_LISTEN&t;4&t;&t;/* sys_listen(2)&t;&t;*/
DECL|macro|SYS_ACCEPT
mdefine_line|#define SYS_ACCEPT&t;5&t;&t;/* sys_accept(2)&t;&t;*/
DECL|macro|SYS_GETSOCKNAME
mdefine_line|#define SYS_GETSOCKNAME&t;6&t;&t;/* sys_getsockname(2)&t;&t;*/
DECL|macro|SYS_GETPEERNAME
mdefine_line|#define SYS_GETPEERNAME&t;7&t;&t;/* sys_getpeername(2)&t;&t;*/
DECL|macro|SYS_SOCKETPAIR
mdefine_line|#define SYS_SOCKETPAIR&t;8&t;&t;/* sys_socketpair(2)&t;&t;*/
DECL|macro|SYS_SEND
mdefine_line|#define SYS_SEND&t;9&t;&t;/* sys_send(2)&t;&t;&t;*/
DECL|macro|SYS_RECV
mdefine_line|#define SYS_RECV&t;10&t;&t;/* sys_recv(2)&t;&t;&t;*/
DECL|macro|SYS_SENDTO
mdefine_line|#define SYS_SENDTO&t;11&t;&t;/* sys_sendto(2)&t;&t;*/
DECL|macro|SYS_RECVFROM
mdefine_line|#define SYS_RECVFROM&t;12&t;&t;/* sys_recvfrom(2)&t;&t;*/
DECL|macro|SYS_SHUTDOWN
mdefine_line|#define SYS_SHUTDOWN&t;13&t;&t;/* sys_shutdown(2)&t;&t;*/
DECL|macro|SYS_SETSOCKOPT
mdefine_line|#define SYS_SETSOCKOPT&t;14&t;&t;/* sys_setsockopt(2)&t;&t;*/
DECL|macro|SYS_GETSOCKOPT
mdefine_line|#define SYS_GETSOCKOPT&t;15&t;&t;/* sys_getsockopt(2)&t;&t;*/
DECL|macro|SYS_SENDMSG
mdefine_line|#define SYS_SENDMSG&t;16&t;&t;/* sys_sendmsg(2)&t;&t;*/
DECL|macro|SYS_RECVMSG
mdefine_line|#define SYS_RECVMSG&t;17&t;&t;/* sys_recvmsg(2)&t;&t;*/
r_typedef
r_enum
(brace
DECL|enumerator|SS_FREE
id|SS_FREE
op_assign
l_int|0
comma
multiline_comment|/* not allocated&t;&t;*/
DECL|enumerator|SS_UNCONNECTED
id|SS_UNCONNECTED
comma
multiline_comment|/* unconnected to any socket&t;*/
DECL|enumerator|SS_CONNECTING
id|SS_CONNECTING
comma
multiline_comment|/* in process of connecting&t;*/
DECL|enumerator|SS_CONNECTED
id|SS_CONNECTED
comma
multiline_comment|/* connected to socket&t;&t;*/
DECL|enumerator|SS_DISCONNECTING
id|SS_DISCONNECTING
multiline_comment|/* in process of disconnecting&t;*/
DECL|typedef|socket_state
)brace
id|socket_state
suffix:semicolon
DECL|macro|__SO_ACCEPTCON
mdefine_line|#define __SO_ACCEPTCON&t;(1 &lt;&lt; 16)&t;/* performed a listen&t;&t;*/
macro_line|#ifdef __KERNEL__
DECL|macro|SOCK_ASYNC_NOSPACE
mdefine_line|#define SOCK_ASYNC_NOSPACE&t;0
DECL|macro|SOCK_ASYNC_WAITDATA
mdefine_line|#define SOCK_ASYNC_WAITDATA&t;1
DECL|macro|SOCK_NOSPACE
mdefine_line|#define SOCK_NOSPACE&t;&t;2
DECL|macro|SOCK_PASSCRED
mdefine_line|#define SOCK_PASSCRED&t;&t;3
macro_line|#ifndef ARCH_HAS_SOCKET_TYPES
multiline_comment|/** sock_type - Socket types&n; * &n; * When adding some new socket type please&n; * grep ARCH_HAS_SOCKET_TYPE include/asm-* /socket.h, at least MIPS&n; * overrides this enum for binary compat reasons.&n; * &n; * @SOCK_STREAM - stream (connection) socket&n; * @SOCK_DGRAM - datagram (conn.less) socket&n; * @SOCK_RAW - raw socket&n; * @SOCK_RDM - reliably-delivered message&n; * @SOCK_SEQPACKET - sequential packet socket &n; * @SOCK_PACKET - linux specific way of getting packets at the dev level.&n; *&t;&t;  For writing rarp and other similar things on the user level.&n; */
DECL|enum|sock_type
r_enum
id|sock_type
(brace
DECL|enumerator|SOCK_STREAM
id|SOCK_STREAM
op_assign
l_int|1
comma
DECL|enumerator|SOCK_DGRAM
id|SOCK_DGRAM
op_assign
l_int|2
comma
DECL|enumerator|SOCK_RAW
id|SOCK_RAW
op_assign
l_int|3
comma
DECL|enumerator|SOCK_RDM
id|SOCK_RDM
op_assign
l_int|4
comma
DECL|enumerator|SOCK_SEQPACKET
id|SOCK_SEQPACKET
op_assign
l_int|5
comma
DECL|enumerator|SOCK_PACKET
id|SOCK_PACKET
op_assign
l_int|10
comma
)brace
suffix:semicolon
DECL|macro|SOCK_MAX
mdefine_line|#define SOCK_MAX (SOCK_PACKET + 1)
macro_line|#endif /* ARCH_HAS_SOCKET_TYPES */
multiline_comment|/**&n; *  struct socket - general BSD socket&n; *  @state - socket state (%SS_CONNECTED, etc)&n; *  @flags - socket flags (%SOCK_ASYNC_NOSPACE, etc)&n; *  @ops - protocol specific socket operations&n; *  @fasync_list - Asynchronous wake up list&n; *  @file - File back pointer for gc&n; *  @sk - internal networking protocol agnostic socket representation&n; *  @wait - wait queue for several uses&n; *  @type - socket type (%SOCK_STREAM, etc)&n; *  @passcred - credentials (used only in Unix Sockets (aka PF_LOCAL))&n; */
DECL|struct|socket
r_struct
id|socket
(brace
DECL|member|state
id|socket_state
id|state
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|ops
r_struct
id|proto_ops
op_star
id|ops
suffix:semicolon
DECL|member|fasync_list
r_struct
id|fasync_struct
op_star
id|fasync_list
suffix:semicolon
DECL|member|file
r_struct
id|file
op_star
id|file
suffix:semicolon
DECL|member|sk
r_struct
id|sock
op_star
id|sk
suffix:semicolon
DECL|member|wait
id|wait_queue_head_t
id|wait
suffix:semicolon
DECL|member|type
r_int
id|type
suffix:semicolon
)brace
suffix:semicolon
r_struct
id|vm_area_struct
suffix:semicolon
r_struct
id|page
suffix:semicolon
r_struct
id|kiocb
suffix:semicolon
r_struct
id|sockaddr
suffix:semicolon
r_struct
id|msghdr
suffix:semicolon
r_struct
id|module
suffix:semicolon
DECL|struct|proto_ops
r_struct
id|proto_ops
(brace
DECL|member|family
r_int
id|family
suffix:semicolon
DECL|member|owner
r_struct
id|module
op_star
id|owner
suffix:semicolon
DECL|member|release
r_int
(paren
op_star
id|release
)paren
(paren
r_struct
id|socket
op_star
id|sock
)paren
suffix:semicolon
DECL|member|bind
r_int
(paren
op_star
id|bind
)paren
(paren
r_struct
id|socket
op_star
id|sock
comma
r_struct
id|sockaddr
op_star
id|myaddr
comma
r_int
id|sockaddr_len
)paren
suffix:semicolon
DECL|member|connect
r_int
(paren
op_star
id|connect
)paren
(paren
r_struct
id|socket
op_star
id|sock
comma
r_struct
id|sockaddr
op_star
id|vaddr
comma
r_int
id|sockaddr_len
comma
r_int
id|flags
)paren
suffix:semicolon
DECL|member|socketpair
r_int
(paren
op_star
id|socketpair
)paren
(paren
r_struct
id|socket
op_star
id|sock1
comma
r_struct
id|socket
op_star
id|sock2
)paren
suffix:semicolon
DECL|member|accept
r_int
(paren
op_star
id|accept
)paren
(paren
r_struct
id|socket
op_star
id|sock
comma
r_struct
id|socket
op_star
id|newsock
comma
r_int
id|flags
)paren
suffix:semicolon
DECL|member|getname
r_int
(paren
op_star
id|getname
)paren
(paren
r_struct
id|socket
op_star
id|sock
comma
r_struct
id|sockaddr
op_star
id|addr
comma
r_int
op_star
id|sockaddr_len
comma
r_int
id|peer
)paren
suffix:semicolon
DECL|member|poll
r_int
r_int
(paren
op_star
id|poll
)paren
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|socket
op_star
id|sock
comma
r_struct
id|poll_table_struct
op_star
id|wait
)paren
suffix:semicolon
DECL|member|ioctl
r_int
(paren
op_star
id|ioctl
)paren
(paren
r_struct
id|socket
op_star
id|sock
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
DECL|member|listen
r_int
(paren
op_star
id|listen
)paren
(paren
r_struct
id|socket
op_star
id|sock
comma
r_int
id|len
)paren
suffix:semicolon
DECL|member|shutdown
r_int
(paren
op_star
id|shutdown
)paren
(paren
r_struct
id|socket
op_star
id|sock
comma
r_int
id|flags
)paren
suffix:semicolon
DECL|member|setsockopt
r_int
(paren
op_star
id|setsockopt
)paren
(paren
r_struct
id|socket
op_star
id|sock
comma
r_int
id|level
comma
r_int
id|optname
comma
r_char
id|__user
op_star
id|optval
comma
r_int
id|optlen
)paren
suffix:semicolon
DECL|member|getsockopt
r_int
(paren
op_star
id|getsockopt
)paren
(paren
r_struct
id|socket
op_star
id|sock
comma
r_int
id|level
comma
r_int
id|optname
comma
r_char
id|__user
op_star
id|optval
comma
r_int
id|__user
op_star
id|optlen
)paren
suffix:semicolon
DECL|member|sendmsg
r_int
(paren
op_star
id|sendmsg
)paren
(paren
r_struct
id|kiocb
op_star
id|iocb
comma
r_struct
id|socket
op_star
id|sock
comma
r_struct
id|msghdr
op_star
id|m
comma
r_int
id|total_len
)paren
suffix:semicolon
DECL|member|recvmsg
r_int
(paren
op_star
id|recvmsg
)paren
(paren
r_struct
id|kiocb
op_star
id|iocb
comma
r_struct
id|socket
op_star
id|sock
comma
r_struct
id|msghdr
op_star
id|m
comma
r_int
id|total_len
comma
r_int
id|flags
)paren
suffix:semicolon
DECL|member|mmap
r_int
(paren
op_star
id|mmap
)paren
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|socket
op_star
id|sock
comma
r_struct
id|vm_area_struct
op_star
id|vma
)paren
suffix:semicolon
DECL|member|sendpage
id|ssize_t
(paren
op_star
id|sendpage
)paren
(paren
r_struct
id|socket
op_star
id|sock
comma
r_struct
id|page
op_star
id|page
comma
r_int
id|offset
comma
r_int
id|size
comma
r_int
id|flags
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|net_proto_family
r_struct
id|net_proto_family
(brace
DECL|member|family
r_int
id|family
suffix:semicolon
DECL|member|create
r_int
(paren
op_star
id|create
)paren
(paren
r_struct
id|socket
op_star
id|sock
comma
r_int
id|protocol
)paren
suffix:semicolon
multiline_comment|/* These are counters for the number of different methods of&n;&t;   each we support */
DECL|member|authentication
r_int
id|authentication
suffix:semicolon
DECL|member|encryption
r_int
id|encryption
suffix:semicolon
DECL|member|encrypt_net
r_int
id|encrypt_net
suffix:semicolon
DECL|member|owner
r_struct
id|module
op_star
id|owner
suffix:semicolon
)brace
suffix:semicolon
r_struct
id|iovec
suffix:semicolon
r_struct
id|kvec
suffix:semicolon
r_extern
r_int
id|sock_wake_async
c_func
(paren
r_struct
id|socket
op_star
id|sk
comma
r_int
id|how
comma
r_int
id|band
)paren
suffix:semicolon
r_extern
r_int
id|sock_register
c_func
(paren
r_struct
id|net_proto_family
op_star
id|fam
)paren
suffix:semicolon
r_extern
r_int
id|sock_unregister
c_func
(paren
r_int
id|family
)paren
suffix:semicolon
r_extern
r_int
id|sock_create
c_func
(paren
r_int
id|family
comma
r_int
id|type
comma
r_int
id|proto
comma
r_struct
id|socket
op_star
op_star
id|res
)paren
suffix:semicolon
r_extern
r_int
id|sock_create_kern
c_func
(paren
r_int
id|family
comma
r_int
id|type
comma
r_int
id|proto
comma
r_struct
id|socket
op_star
op_star
id|res
)paren
suffix:semicolon
r_extern
r_int
id|sock_create_lite
c_func
(paren
r_int
id|family
comma
r_int
id|type
comma
r_int
id|proto
comma
r_struct
id|socket
op_star
op_star
id|res
)paren
suffix:semicolon
r_extern
r_void
id|sock_release
c_func
(paren
r_struct
id|socket
op_star
id|sock
)paren
suffix:semicolon
r_extern
r_int
id|sock_sendmsg
c_func
(paren
r_struct
id|socket
op_star
id|sock
comma
r_struct
id|msghdr
op_star
id|msg
comma
r_int
id|len
)paren
suffix:semicolon
r_extern
r_int
id|sock_recvmsg
c_func
(paren
r_struct
id|socket
op_star
id|sock
comma
r_struct
id|msghdr
op_star
id|msg
comma
r_int
id|size
comma
r_int
id|flags
)paren
suffix:semicolon
r_extern
r_int
id|sock_map_fd
c_func
(paren
r_struct
id|socket
op_star
id|sock
)paren
suffix:semicolon
r_extern
r_struct
id|socket
op_star
id|sockfd_lookup
c_func
(paren
r_int
id|fd
comma
r_int
op_star
id|err
)paren
suffix:semicolon
DECL|macro|sockfd_put
mdefine_line|#define&t;&t;     sockfd_put(sock) fput(sock-&gt;file)
r_extern
r_int
id|net_ratelimit
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_int
id|net_random
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|net_srandom
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|net_random_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|kernel_sendmsg
c_func
(paren
r_struct
id|socket
op_star
id|sock
comma
r_struct
id|msghdr
op_star
id|msg
comma
r_struct
id|kvec
op_star
id|vec
comma
r_int
id|num
comma
r_int
id|len
)paren
suffix:semicolon
r_extern
r_int
id|kernel_recvmsg
c_func
(paren
r_struct
id|socket
op_star
id|sock
comma
r_struct
id|msghdr
op_star
id|msg
comma
r_struct
id|kvec
op_star
id|vec
comma
r_int
id|num
comma
r_int
id|len
comma
r_int
id|flags
)paren
suffix:semicolon
macro_line|#ifndef CONFIG_SMP
DECL|macro|SOCKOPS_WRAPPED
mdefine_line|#define SOCKOPS_WRAPPED(name) name
DECL|macro|SOCKOPS_WRAP
mdefine_line|#define SOCKOPS_WRAP(name, fam)
macro_line|#else
DECL|macro|SOCKOPS_WRAPPED
mdefine_line|#define SOCKOPS_WRAPPED(name) __unlocked_##name
DECL|macro|SOCKCALL_WRAP
mdefine_line|#define SOCKCALL_WRAP(name, call, parms, args)&t;&t;&bslash;&n;static int __lock_##name##_##call  parms&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;int ret;&t;&t;&t;&t;&t;&bslash;&n;&t;lock_kernel();&t;&t;&t;&t;&t;&bslash;&n;&t;ret = __unlocked_##name##_ops.call  args ;&bslash;&n;&t;unlock_kernel();&t;&t;&t;&t;&bslash;&n;&t;return ret;&t;&t;&t;&t;&t;&bslash;&n;}
DECL|macro|SOCKCALL_UWRAP
mdefine_line|#define SOCKCALL_UWRAP(name, call, parms, args)&t;&t;&bslash;&n;static unsigned int __lock_##name##_##call  parms&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;int ret;&t;&t;&t;&t;&t;&bslash;&n;&t;lock_kernel();&t;&t;&t;&t;&t;&bslash;&n;&t;ret = __unlocked_##name##_ops.call  args ;&bslash;&n;&t;unlock_kernel();&t;&t;&t;&t;&bslash;&n;&t;return ret;&t;&t;&t;&t;&t;&bslash;&n;}
DECL|macro|SOCKOPS_WRAP
mdefine_line|#define SOCKOPS_WRAP(name, fam)&t;&t;&t;&t;&t;&bslash;&n;SOCKCALL_WRAP(name, release, (struct socket *sock), (sock))&t;&bslash;&n;SOCKCALL_WRAP(name, bind, (struct socket *sock, struct sockaddr *uaddr, int addr_len), &bslash;&n;&t;      (sock, uaddr, addr_len))&t;&t;&t;&t;&bslash;&n;SOCKCALL_WRAP(name, connect, (struct socket *sock, struct sockaddr * uaddr, &bslash;&n;&t;&t;&t;      int addr_len, int flags), &t;&bslash;&n;&t;      (sock, uaddr, addr_len, flags))&t;&t;&t;&bslash;&n;SOCKCALL_WRAP(name, socketpair, (struct socket *sock1, struct socket *sock2), &bslash;&n;&t;      (sock1, sock2))&t;&t;&t;&t;&t;&bslash;&n;SOCKCALL_WRAP(name, accept, (struct socket *sock, struct socket *newsock, &bslash;&n;&t;&t;&t; int flags), (sock, newsock, flags)) &bslash;&n;SOCKCALL_WRAP(name, getname, (struct socket *sock, struct sockaddr *uaddr, &bslash;&n;&t;&t;&t; int *addr_len, int peer), (sock, uaddr, addr_len, peer)) &bslash;&n;SOCKCALL_UWRAP(name, poll, (struct file *file, struct socket *sock, struct poll_table_struct *wait), &bslash;&n;&t;      (file, sock, wait)) &bslash;&n;SOCKCALL_WRAP(name, ioctl, (struct socket *sock, unsigned int cmd, &bslash;&n;&t;&t;&t; unsigned long arg), (sock, cmd, arg)) &bslash;&n;SOCKCALL_WRAP(name, listen, (struct socket *sock, int len), (sock, len)) &bslash;&n;SOCKCALL_WRAP(name, shutdown, (struct socket *sock, int flags), (sock, flags)) &bslash;&n;SOCKCALL_WRAP(name, setsockopt, (struct socket *sock, int level, int optname, &bslash;&n;&t;&t;&t; char __user *optval, int optlen), (sock, level, optname, optval, optlen)) &bslash;&n;SOCKCALL_WRAP(name, getsockopt, (struct socket *sock, int level, int optname, &bslash;&n;&t;&t;&t; char __user *optval, int __user *optlen), (sock, level, optname, optval, optlen)) &bslash;&n;SOCKCALL_WRAP(name, sendmsg, (struct kiocb *iocb, struct socket *sock, struct msghdr *m, size_t len), &bslash;&n;&t;      (iocb, sock, m, len)) &bslash;&n;SOCKCALL_WRAP(name, recvmsg, (struct kiocb *iocb, struct socket *sock, struct msghdr *m, size_t len, int flags), &bslash;&n;&t;      (iocb, sock, m, len, flags)) &bslash;&n;SOCKCALL_WRAP(name, mmap, (struct file *file, struct socket *sock, struct vm_area_struct *vma), &bslash;&n;&t;      (file, sock, vma)) &bslash;&n;&t;      &bslash;&n;static struct proto_ops name##_ops = {&t;&t;&t;&bslash;&n;&t;.family&t;&t;= fam,&t;&t;&t;&t;&bslash;&n;&t;.owner&t;&t;= THIS_MODULE,&t;&t;&t;&bslash;&n;&t;.release&t;= __lock_##name##_release,&t;&bslash;&n;&t;.bind&t;&t;= __lock_##name##_bind,&t;&t;&bslash;&n;&t;.connect&t;= __lock_##name##_connect,&t;&bslash;&n;&t;.socketpair&t;= __lock_##name##_socketpair,&t;&bslash;&n;&t;.accept&t;&t;= __lock_##name##_accept,&t;&bslash;&n;&t;.getname&t;= __lock_##name##_getname,&t;&bslash;&n;&t;.poll&t;&t;= __lock_##name##_poll,&t;&t;&bslash;&n;&t;.ioctl&t;&t;= __lock_##name##_ioctl,&t;&bslash;&n;&t;.listen&t;&t;= __lock_##name##_listen,&t;&bslash;&n;&t;.shutdown&t;= __lock_##name##_shutdown,&t;&bslash;&n;&t;.setsockopt&t;= __lock_##name##_setsockopt,&t;&bslash;&n;&t;.getsockopt&t;= __lock_##name##_getsockopt,&t;&bslash;&n;&t;.sendmsg&t;= __lock_##name##_sendmsg,&t;&bslash;&n;&t;.recvmsg&t;= __lock_##name##_recvmsg,&t;&bslash;&n;&t;.mmap&t;&t;= __lock_##name##_mmap,&t;&t;&bslash;&n;};
macro_line|#endif
DECL|macro|MODULE_ALIAS_NETPROTO
mdefine_line|#define MODULE_ALIAS_NETPROTO(proto) &bslash;&n;&t;MODULE_ALIAS(&quot;net-pf-&quot; __stringify(proto))
macro_line|#endif /* __KERNEL__ */
macro_line|#endif&t;/* _LINUX_NET_H */
eof
