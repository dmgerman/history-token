macro_line|#ifndef _ASM_SOCKET_H
DECL|macro|_ASM_SOCKET_H
mdefine_line|#define _ASM_SOCKET_H
macro_line|#include &lt;asm/sockios.h&gt;
multiline_comment|/* For setsockopt(2) */
multiline_comment|/*&n; * Note: we only bother about making the SOL_SOCKET options&n; * same as OSF/1, as that&squot;s all that &quot;normal&quot; programs are&n; * likely to set.  We don&squot;t necessarily want to be binary&n; * compatible with _everything_. &n; */
DECL|macro|SOL_SOCKET
mdefine_line|#define SOL_SOCKET&t;0xffff
DECL|macro|SO_DEBUG
mdefine_line|#define SO_DEBUG&t;0x0001
DECL|macro|SO_REUSEADDR
mdefine_line|#define SO_REUSEADDR&t;0x0004
DECL|macro|SO_KEEPALIVE
mdefine_line|#define SO_KEEPALIVE&t;0x0008
DECL|macro|SO_DONTROUTE
mdefine_line|#define SO_DONTROUTE&t;0x0010
DECL|macro|SO_BROADCAST
mdefine_line|#define SO_BROADCAST&t;0x0020
DECL|macro|SO_LINGER
mdefine_line|#define SO_LINGER&t;0x0080
DECL|macro|SO_OOBINLINE
mdefine_line|#define SO_OOBINLINE&t;0x0100
multiline_comment|/* To add :#define SO_REUSEPORT 0x0200 */
DECL|macro|SO_TYPE
mdefine_line|#define SO_TYPE&t;&t;0x1008
DECL|macro|SO_ERROR
mdefine_line|#define SO_ERROR&t;0x1007
DECL|macro|SO_SNDBUF
mdefine_line|#define SO_SNDBUF&t;0x1001
DECL|macro|SO_RCVBUF
mdefine_line|#define SO_RCVBUF&t;0x1002
DECL|macro|SO_RCVLOWAT
mdefine_line|#define&t;SO_RCVLOWAT&t;0x1010
DECL|macro|SO_SNDLOWAT
mdefine_line|#define&t;SO_SNDLOWAT&t;0x1011
DECL|macro|SO_RCVTIMEO
mdefine_line|#define&t;SO_RCVTIMEO&t;0x1012
DECL|macro|SO_SNDTIMEO
mdefine_line|#define&t;SO_SNDTIMEO&t;0x1013
DECL|macro|SO_ACCEPTCONN
mdefine_line|#define SO_ACCEPTCONN&t;0x1014
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
DECL|macro|SO_BINDTODEVICE
mdefine_line|#define SO_BINDTODEVICE 25
multiline_comment|/* Socket filtering */
DECL|macro|SO_ATTACH_FILTER
mdefine_line|#define SO_ATTACH_FILTER        26
DECL|macro|SO_DETACH_FILTER
mdefine_line|#define SO_DETACH_FILTER        27
DECL|macro|SO_PEERNAME
mdefine_line|#define SO_PEERNAME&t;&t;28
DECL|macro|SO_TIMESTAMP
mdefine_line|#define SO_TIMESTAMP&t;&t;29
DECL|macro|SCM_TIMESTAMP
mdefine_line|#define SCM_TIMESTAMP&t;&t;SO_TIMESTAMP
DECL|macro|SO_PEERSEC
mdefine_line|#define SO_PEERSEC&t;&t;30
multiline_comment|/* Security levels - as per NRL IPv6 - don&squot;t actually do anything */
DECL|macro|SO_SECURITY_AUTHENTICATION
mdefine_line|#define SO_SECURITY_AUTHENTICATION&t;&t;19
DECL|macro|SO_SECURITY_ENCRYPTION_TRANSPORT
mdefine_line|#define SO_SECURITY_ENCRYPTION_TRANSPORT&t;20
DECL|macro|SO_SECURITY_ENCRYPTION_NETWORK
mdefine_line|#define SO_SECURITY_ENCRYPTION_NETWORK&t;&t;21
macro_line|#endif /* _ASM_SOCKET_H */
eof
