macro_line|#ifndef __ASM_CRIS_POLL_H
DECL|macro|__ASM_CRIS_POLL_H
mdefine_line|#define __ASM_CRIS_POLL_H
multiline_comment|/* taken from asm-alpha */
DECL|macro|POLLIN
mdefine_line|#define POLLIN&t;&t;1
DECL|macro|POLLPRI
mdefine_line|#define POLLPRI&t;&t;2
DECL|macro|POLLOUT
mdefine_line|#define POLLOUT&t;&t;4
DECL|macro|POLLERR
mdefine_line|#define POLLERR&t;&t;8
DECL|macro|POLLHUP
mdefine_line|#define POLLHUP&t;&t;16
DECL|macro|POLLNVAL
mdefine_line|#define POLLNVAL&t;32
DECL|macro|POLLRDNORM
mdefine_line|#define POLLRDNORM&t;64
DECL|macro|POLLRDBAND
mdefine_line|#define POLLRDBAND&t;128
DECL|macro|POLLWRNORM
mdefine_line|#define POLLWRNORM&t;256
DECL|macro|POLLWRBAND
mdefine_line|#define POLLWRBAND&t;512
DECL|macro|POLLMSG
mdefine_line|#define POLLMSG&t;&t;1024
DECL|macro|POLLREMOVE
mdefine_line|#define POLLREMOVE&t;4096
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
macro_line|#endif
eof
