macro_line|#ifndef __ASM_SH_POLL_H
DECL|macro|__ASM_SH_POLL_H
mdefine_line|#define __ASM_SH_POLL_H
multiline_comment|/* These are specified by iBCS2 */
DECL|macro|POLLIN
mdefine_line|#define POLLIN&t;&t;0x0001
DECL|macro|POLLPRI
mdefine_line|#define POLLPRI&t;&t;0x0002
DECL|macro|POLLOUT
mdefine_line|#define POLLOUT&t;&t;0x0004
DECL|macro|POLLERR
mdefine_line|#define POLLERR&t;&t;0x0008
DECL|macro|POLLHUP
mdefine_line|#define POLLHUP&t;&t;0x0010
DECL|macro|POLLNVAL
mdefine_line|#define POLLNVAL&t;0x0020
multiline_comment|/* The rest seem to be more-or-less nonstandard. Check them! */
DECL|macro|POLLRDNORM
mdefine_line|#define POLLRDNORM&t;0x0040
DECL|macro|POLLRDBAND
mdefine_line|#define POLLRDBAND&t;0x0080
DECL|macro|POLLWRNORM
mdefine_line|#define POLLWRNORM&t;0x0100
DECL|macro|POLLWRBAND
mdefine_line|#define POLLWRBAND&t;0x0200
DECL|macro|POLLMSG
mdefine_line|#define POLLMSG&t;&t;0x0400
DECL|struct|pollfd
r_struct
id|pollfd
(brace
DECL|member|fd
r_int
id|fd
suffix:semicolon
DECL|member|events
r_int
id|events
suffix:semicolon
DECL|member|revents
r_int
id|revents
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* __ASM_SH_POLL_H */
eof
