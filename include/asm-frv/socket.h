macro_line|#ifndef _ASM_SOCKET_H
DECL|macro|_ASM_SOCKET_H
mdefine_line|#define _ASM_SOCKET_H
macro_line|#include &lt;asm/sockios.h&gt;
multiline_comment|/* For setsockopt(2) */
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
mdefine_line|#define SO_PEERNAME             28
DECL|macro|SO_TIMESTAMP
mdefine_line|#define SO_TIMESTAMP&t;&t;29
DECL|macro|SCM_TIMESTAMP
mdefine_line|#define SCM_TIMESTAMP&t;&t;SO_TIMESTAMP
DECL|macro|SO_ACCEPTCONN
mdefine_line|#define SO_ACCEPTCONN&t;&t;30
DECL|macro|SO_PEERSEC
mdefine_line|#define SO_PEERSEC&t;&t;31
macro_line|#endif /* _ASM_SOCKET_H */
eof
