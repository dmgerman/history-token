macro_line|#ifndef __ALPHA_POLL_H
DECL|macro|__ALPHA_POLL_H
mdefine_line|#define __ALPHA_POLL_H
DECL|macro|POLLIN
mdefine_line|#define POLLIN&t;&t;(1 &lt;&lt; 0)
DECL|macro|POLLPRI
mdefine_line|#define POLLPRI&t;&t;(1 &lt;&lt; 1)
DECL|macro|POLLOUT
mdefine_line|#define POLLOUT&t;&t;(1 &lt;&lt; 2)
DECL|macro|POLLERR
mdefine_line|#define POLLERR&t;&t;(1 &lt;&lt; 3)
DECL|macro|POLLHUP
mdefine_line|#define POLLHUP&t;&t;(1 &lt;&lt; 4)
DECL|macro|POLLNVAL
mdefine_line|#define POLLNVAL&t;(1 &lt;&lt; 5)
DECL|macro|POLLRDNORM
mdefine_line|#define POLLRDNORM&t;(1 &lt;&lt; 6)
DECL|macro|POLLRDBAND
mdefine_line|#define POLLRDBAND&t;(1 &lt;&lt; 7)
DECL|macro|POLLWRNORM
mdefine_line|#define POLLWRNORM&t;(1 &lt;&lt; 8)
DECL|macro|POLLWRBAND
mdefine_line|#define POLLWRBAND&t;(1 &lt;&lt; 9)
DECL|macro|POLLMSG
mdefine_line|#define POLLMSG&t;&t;(1 &lt;&lt; 10)
DECL|macro|POLLREMOVE
mdefine_line|#define POLLREMOVE&t;(1 &lt;&lt; 11)
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
