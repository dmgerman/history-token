macro_line|#ifndef _ASM_SOCKET_H
DECL|macro|_ASM_SOCKET_H
mdefine_line|#define _ASM_SOCKET_H
multiline_comment|/* almost the same as asm-i386/socket.h */
macro_line|#include &lt;asm/sockios.h&gt;
multiline_comment|/* For setsockoptions(2) */
DECL|macro|SOL_SOCKET
mdefine_line|#define SOL_SOCKET&t;1
DECL|macro|SO_DEBUG
mdefine_line|#define SO_DEBUG&t;1
DECL|macro|SO_REUSEADDR
mdefine_line|#define SO_REUSEADDR&t;2
DECL|macro|SO_TYPE
mdefine_line|#define SO_TYPE&t;&t;3
DECL|macro|SO_ERROR
mdefine_line|#define SO_ERROR&t;4
DECL|macro|SO_DONTROUTE
mdefine_line|#define SO_DONTROUTE&t;5
DECL|macro|SO_BROADCAST
mdefine_line|#define SO_BROADCAST&t;6
DECL|macro|SO_SNDBUF
mdefine_line|#define SO_SNDBUF&t;7
DECL|macro|SO_RCVBUF
mdefine_line|#define SO_RCVBUF&t;8
DECL|macro|SO_KEEPALIVE
mdefine_line|#define SO_KEEPALIVE&t;9
DECL|macro|SO_OOBINLINE
mdefine_line|#define SO_OOBINLINE&t;10
DECL|macro|SO_NO_CHECK
mdefine_line|#define SO_NO_CHECK&t;11
DECL|macro|SO_PRIORITY
mdefine_line|#define SO_PRIORITY&t;12
DECL|macro|SO_LINGER
mdefine_line|#define SO_LINGER&t;13
DECL|macro|SO_BSDCOMPAT
mdefine_line|#define SO_BSDCOMPAT&t;14
multiline_comment|/* To add :#define SO_REUSEPORT 15 */
DECL|macro|SO_PASSCRED
mdefine_line|#define SO_PASSCRED&t;16
DECL|macro|SO_PEERCRED
mdefine_line|#define SO_PEERCRED&t;17
DECL|macro|SO_RCVLOWAT
mdefine_line|#define SO_RCVLOWAT&t;18
DECL|macro|SO_SNDLOWAT
mdefine_line|#define SO_SNDLOWAT&t;19
DECL|macro|SO_RCVTIMEO
mdefine_line|#define SO_RCVTIMEO&t;20
DECL|macro|SO_SNDTIMEO
mdefine_line|#define SO_SNDTIMEO&t;21
multiline_comment|/* Security levels - as per NRL IPv6 - don&squot;t actually do anything */
DECL|macro|SO_SECURITY_AUTHENTICATION
mdefine_line|#define SO_SECURITY_AUTHENTICATION&t;&t;22
DECL|macro|SO_SECURITY_ENCRYPTION_TRANSPORT
mdefine_line|#define SO_SECURITY_ENCRYPTION_TRANSPORT&t;23
DECL|macro|SO_SECURITY_ENCRYPTION_NETWORK
mdefine_line|#define SO_SECURITY_ENCRYPTION_NETWORK&t;&t;24
DECL|macro|SO_BINDTODEVICE
mdefine_line|#define SO_BINDTODEVICE&t;25
multiline_comment|/* Socket filtering */
DECL|macro|SO_ATTACH_FILTER
mdefine_line|#define SO_ATTACH_FILTER        26
DECL|macro|SO_DETACH_FILTER
mdefine_line|#define SO_DETACH_FILTER        27
DECL|macro|SO_PEERNAME
mdefine_line|#define SO_PEERNAME&t;&t;28
DECL|macro|SO_TIMESTAMP
mdefine_line|#define SO_TIMESTAMP           29
DECL|macro|SCM_TIMESTAMP
mdefine_line|#define SCM_TIMESTAMP          SO_TIMESTAMP
macro_line|#if defined(__KERNEL__)
multiline_comment|/* Socket types. */
DECL|macro|SOCK_STREAM
mdefine_line|#define SOCK_STREAM     1               /* stream (connection) socket   */
DECL|macro|SOCK_DGRAM
mdefine_line|#define SOCK_DGRAM      2               /* datagram (conn.less) socket  */
DECL|macro|SOCK_RAW
mdefine_line|#define SOCK_RAW        3               /* raw socket                   */
DECL|macro|SOCK_RDM
mdefine_line|#define SOCK_RDM        4               /* reliably-delivered message   */
DECL|macro|SOCK_SEQPACKET
mdefine_line|#define SOCK_SEQPACKET  5               /* sequential packet socket     */
DECL|macro|SOCK_PACKET
mdefine_line|#define SOCK_PACKET     10              /* linux specific way of        */
multiline_comment|/* getting packets at the dev   */
multiline_comment|/* level.  For writing rarp and */
multiline_comment|/* other similar things on the  */
multiline_comment|/* user level.                  */
macro_line|#endif
macro_line|#endif /* _ASM_SOCKET_H */
eof
