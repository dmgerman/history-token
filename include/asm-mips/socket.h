macro_line|#ifndef _ASM_SOCKET_H
DECL|macro|_ASM_SOCKET_H
mdefine_line|#define _ASM_SOCKET_H
macro_line|#include &lt;asm/sockios.h&gt;
multiline_comment|/*&n; * For setsockoptions(2)&n; *&n; * This defines are ABI conformant as far as Linux supports these ...&n; */
DECL|macro|SOL_SOCKET
mdefine_line|#define SOL_SOCKET&t;0xffff
DECL|macro|SO_DEBUG
mdefine_line|#define SO_DEBUG&t;0x0001&t;/* Record debugging information.  */
DECL|macro|SO_REUSEADDR
mdefine_line|#define SO_REUSEADDR&t;0x0004&t;/* Allow reuse of local addresses.  */
DECL|macro|SO_KEEPALIVE
mdefine_line|#define SO_KEEPALIVE&t;0x0008&t;/* Keep connections alive and send&n;&t;&t;&t;&t;   SIGPIPE when they die.  */
DECL|macro|SO_DONTROUTE
mdefine_line|#define SO_DONTROUTE&t;0x0010&t;/* Don&squot;t do local routing.  */
DECL|macro|SO_BROADCAST
mdefine_line|#define SO_BROADCAST&t;0x0020&t;/* Allow transmission of&n;&t;&t;&t;&t;   broadcast messages.  */
DECL|macro|SO_LINGER
mdefine_line|#define SO_LINGER&t;0x0080&t;/* Block on close of a reliable&n;&t;&t;&t;&t;   socket to transmit pending data.  */
DECL|macro|SO_OOBINLINE
mdefine_line|#define SO_OOBINLINE 0x0100&t;/* Receive out-of-band data in-band.  */
macro_line|#if 0
id|To
id|add
suffix:colon
mdefine_line|#define SO_REUSEPORT 0x0200&t;/* Allow local address and port reuse.  */
macro_line|#endif
DECL|macro|SO_TYPE
mdefine_line|#define SO_TYPE&t;&t;0x1008&t;/* Compatible name for SO_STYLE.  */
DECL|macro|SO_STYLE
mdefine_line|#define SO_STYLE&t;SO_TYPE&t;/* Synonym */
DECL|macro|SO_ERROR
mdefine_line|#define SO_ERROR&t;0x1007&t;/* get error status and clear */
DECL|macro|SO_SNDBUF
mdefine_line|#define SO_SNDBUF&t;0x1001&t;/* Send buffer size. */
DECL|macro|SO_RCVBUF
mdefine_line|#define SO_RCVBUF&t;0x1002&t;/* Receive buffer. */
DECL|macro|SO_SNDLOWAT
mdefine_line|#define SO_SNDLOWAT&t;0x1003&t;/* send low-water mark */
DECL|macro|SO_RCVLOWAT
mdefine_line|#define SO_RCVLOWAT&t;0x1004&t;/* receive low-water mark */
DECL|macro|SO_SNDTIMEO
mdefine_line|#define SO_SNDTIMEO&t;0x1005&t;/* send timeout */
DECL|macro|SO_RCVTIMEO
mdefine_line|#define SO_RCVTIMEO &t;0x1006&t;/* receive timeout */
multiline_comment|/* linux-specific, might as well be the same as on i386 */
DECL|macro|SO_NO_CHECK
mdefine_line|#define SO_NO_CHECK&t;11
DECL|macro|SO_PRIORITY
mdefine_line|#define SO_PRIORITY&t;12
DECL|macro|SO_BSDCOMPAT
mdefine_line|#define SO_BSDCOMPAT&t;14
DECL|macro|SO_PASSCRED
mdefine_line|#define SO_PASSCRED&t;17
DECL|macro|SO_PEERCRED
mdefine_line|#define SO_PEERCRED&t;18
multiline_comment|/* Security levels - as per NRL IPv6 - don&squot;t actually do anything */
DECL|macro|SO_SECURITY_AUTHENTICATION
mdefine_line|#define SO_SECURITY_AUTHENTICATION&t;&t;22
DECL|macro|SO_SECURITY_ENCRYPTION_TRANSPORT
mdefine_line|#define SO_SECURITY_ENCRYPTION_TRANSPORT&t;23
DECL|macro|SO_SECURITY_ENCRYPTION_NETWORK
mdefine_line|#define SO_SECURITY_ENCRYPTION_NETWORK&t;&t;24
DECL|macro|SO_BINDTODEVICE
mdefine_line|#define SO_BINDTODEVICE&t;&t;25
multiline_comment|/* Socket filtering */
DECL|macro|SO_ATTACH_FILTER
mdefine_line|#define SO_ATTACH_FILTER        26
DECL|macro|SO_DETACH_FILTER
mdefine_line|#define SO_DETACH_FILTER        27
DECL|macro|SO_PEERNAME
mdefine_line|#define SO_PEERNAME             28
DECL|macro|SO_TIMESTAMP
mdefine_line|#define SO_TIMESTAMP&t;&t;29
DECL|macro|SCM_TIMESTAMP
mdefine_line|#define SCM_TIMESTAMP&t;&t;SO_TIMESTAMP
multiline_comment|/* Nast libc5 fixup - bletch */
macro_line|#if defined(__KERNEL__)
multiline_comment|/* Socket types. */
DECL|macro|SOCK_DGRAM
mdefine_line|#define SOCK_DGRAM&t;1&t;&t;/* datagram (conn.less) socket&t;*/
DECL|macro|SOCK_STREAM
mdefine_line|#define SOCK_STREAM&t;2&t;&t;/* stream (connection) socket&t;*/
DECL|macro|SOCK_RAW
mdefine_line|#define SOCK_RAW&t;3&t;&t;/* raw socket&t;&t;&t;*/
DECL|macro|SOCK_RDM
mdefine_line|#define SOCK_RDM&t;4&t;&t;/* reliably-delivered message&t;*/
DECL|macro|SOCK_SEQPACKET
mdefine_line|#define SOCK_SEQPACKET&t;5&t;&t;/* sequential packet socket&t;*/
DECL|macro|SOCK_PACKET
mdefine_line|#define SOCK_PACKET&t;10&t;&t;/* linux specific way of&t;*/
multiline_comment|/* getting packets at the dev&t;*/
multiline_comment|/* level.  For writing rarp and&t;*/
multiline_comment|/* other similar things on the&t;*/
multiline_comment|/* user level.&t;&t;&t;*/
macro_line|#endif
macro_line|#endif /* _ASM_SOCKET_H */
eof
