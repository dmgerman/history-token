multiline_comment|/*&n; * Copyright (C) 2001 Lennert Buytenhek (buytenh@gnu.org)&n; * Copyright (C) 2001 - 2003 Jeff Dike (jdike@addtoit.com)&n; * Licensed under the GPL&n; */
macro_line|#include &lt;stdio.h&gt;
macro_line|#include &lt;stdlib.h&gt;
macro_line|#include &lt;errno.h&gt;
macro_line|#include &lt;signal.h&gt;
macro_line|#include &lt;sys/socket.h&gt;
macro_line|#include &lt;sys/types.h&gt;
macro_line|#include &lt;sys/uio.h&gt;
macro_line|#include &lt;sys/un.h&gt;
macro_line|#include &lt;unistd.h&gt;
macro_line|#include &quot;user.h&quot;
macro_line|#include &quot;mconsole.h&quot;
macro_line|#include &quot;umid.h&quot;
DECL|variable|commands
r_static
r_struct
id|mconsole_command
id|commands
(braket
)braket
op_assign
(brace
(brace
l_string|&quot;version&quot;
comma
id|mconsole_version
comma
id|MCONSOLE_INTR
)brace
comma
(brace
l_string|&quot;halt&quot;
comma
id|mconsole_halt
comma
id|MCONSOLE_PROC
)brace
comma
(brace
l_string|&quot;reboot&quot;
comma
id|mconsole_reboot
comma
id|MCONSOLE_PROC
)brace
comma
(brace
l_string|&quot;config&quot;
comma
id|mconsole_config
comma
id|MCONSOLE_PROC
)brace
comma
(brace
l_string|&quot;remove&quot;
comma
id|mconsole_remove
comma
id|MCONSOLE_PROC
)brace
comma
(brace
l_string|&quot;sysrq&quot;
comma
id|mconsole_sysrq
comma
id|MCONSOLE_INTR
)brace
comma
(brace
l_string|&quot;help&quot;
comma
id|mconsole_help
comma
id|MCONSOLE_INTR
)brace
comma
(brace
l_string|&quot;cad&quot;
comma
id|mconsole_cad
comma
id|MCONSOLE_INTR
)brace
comma
(brace
l_string|&quot;stop&quot;
comma
id|mconsole_stop
comma
id|MCONSOLE_PROC
)brace
comma
(brace
l_string|&quot;go&quot;
comma
id|mconsole_go
comma
id|MCONSOLE_INTR
)brace
comma
(brace
l_string|&quot;log&quot;
comma
id|mconsole_log
comma
id|MCONSOLE_INTR
)brace
comma
(brace
l_string|&quot;proc&quot;
comma
id|mconsole_proc
comma
id|MCONSOLE_PROC
)brace
comma
)brace
suffix:semicolon
multiline_comment|/* Initialized in mconsole_init, which is an initcall */
DECL|variable|mconsole_socket_name
r_char
id|mconsole_socket_name
(braket
l_int|256
)braket
suffix:semicolon
DECL|function|mconsole_reply_v0
r_int
id|mconsole_reply_v0
c_func
(paren
r_struct
id|mc_request
op_star
id|req
comma
r_char
op_star
id|reply
)paren
(brace
r_struct
id|iovec
id|iov
suffix:semicolon
r_struct
id|msghdr
id|msg
suffix:semicolon
id|iov.iov_base
op_assign
id|reply
suffix:semicolon
id|iov.iov_len
op_assign
id|strlen
c_func
(paren
id|reply
)paren
suffix:semicolon
id|msg.msg_name
op_assign
op_amp
(paren
id|req-&gt;origin
)paren
suffix:semicolon
id|msg.msg_namelen
op_assign
id|req-&gt;originlen
suffix:semicolon
id|msg.msg_iov
op_assign
op_amp
id|iov
suffix:semicolon
id|msg.msg_iovlen
op_assign
l_int|1
suffix:semicolon
id|msg.msg_control
op_assign
l_int|NULL
suffix:semicolon
id|msg.msg_controllen
op_assign
l_int|0
suffix:semicolon
id|msg.msg_flags
op_assign
l_int|0
suffix:semicolon
r_return
id|sendmsg
c_func
(paren
id|req-&gt;originating_fd
comma
op_amp
id|msg
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|mconsole_parse
r_static
r_struct
id|mconsole_command
op_star
id|mconsole_parse
c_func
(paren
r_struct
id|mc_request
op_star
id|req
)paren
(brace
r_struct
id|mconsole_command
op_star
id|cmd
suffix:semicolon
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
r_sizeof
(paren
id|commands
)paren
op_div
r_sizeof
(paren
id|commands
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|cmd
op_assign
op_amp
id|commands
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|req-&gt;request.data
comma
id|cmd-&gt;command
comma
id|strlen
c_func
(paren
id|cmd-&gt;command
)paren
)paren
)paren
(brace
r_return
id|cmd
suffix:semicolon
)brace
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|macro|MIN
mdefine_line|#define MIN(a,b) ((a)&lt;(b) ? (a):(b))
DECL|macro|STRINGX
mdefine_line|#define STRINGX(x) #x
DECL|macro|STRING
mdefine_line|#define STRING(x) STRINGX(x)
DECL|function|mconsole_get_request
r_int
id|mconsole_get_request
c_func
(paren
r_int
id|fd
comma
r_struct
id|mc_request
op_star
id|req
)paren
(brace
r_int
id|len
suffix:semicolon
id|req-&gt;originlen
op_assign
r_sizeof
(paren
id|req-&gt;origin
)paren
suffix:semicolon
id|req-&gt;len
op_assign
id|recvfrom
c_func
(paren
id|fd
comma
op_amp
id|req-&gt;request
comma
r_sizeof
(paren
id|req-&gt;request
)paren
comma
l_int|0
comma
(paren
r_struct
id|sockaddr
op_star
)paren
id|req-&gt;origin
comma
op_amp
id|req-&gt;originlen
)paren
suffix:semicolon
r_if
c_cond
(paren
id|req-&gt;len
OL
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|req-&gt;originating_fd
op_assign
id|fd
suffix:semicolon
r_if
c_cond
(paren
id|req-&gt;request.magic
op_ne
id|MCONSOLE_MAGIC
)paren
(brace
multiline_comment|/* Unversioned request */
id|len
op_assign
id|MIN
c_func
(paren
r_sizeof
(paren
id|req-&gt;request.data
)paren
op_minus
l_int|1
comma
id|strlen
c_func
(paren
(paren
r_char
op_star
)paren
op_amp
id|req-&gt;request
)paren
)paren
suffix:semicolon
id|memmove
c_func
(paren
id|req-&gt;request.data
comma
op_amp
id|req-&gt;request
comma
id|len
)paren
suffix:semicolon
id|req-&gt;request.data
(braket
id|len
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|req-&gt;request.magic
op_assign
id|MCONSOLE_MAGIC
suffix:semicolon
id|req-&gt;request.version
op_assign
l_int|0
suffix:semicolon
id|req-&gt;request.len
op_assign
id|len
suffix:semicolon
id|mconsole_reply_v0
c_func
(paren
id|req
comma
l_string|&quot;ERR Version 0 mconsole clients are &quot;
l_string|&quot;not supported by this driver&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|req-&gt;request.len
op_ge
id|MCONSOLE_MAX_DATA
)paren
(brace
id|mconsole_reply
c_func
(paren
id|req
comma
l_string|&quot;Request too large&quot;
comma
l_int|1
comma
l_int|0
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|req-&gt;request.version
op_ne
id|MCONSOLE_VERSION
)paren
(brace
id|mconsole_reply
c_func
(paren
id|req
comma
l_string|&quot;This driver only supports version &quot;
id|STRING
c_func
(paren
id|MCONSOLE_VERSION
)paren
l_string|&quot; clients&quot;
comma
l_int|1
comma
l_int|0
)paren
suffix:semicolon
)brace
id|req-&gt;request.data
(braket
id|req-&gt;request.len
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|req-&gt;cmd
op_assign
id|mconsole_parse
c_func
(paren
id|req
)paren
suffix:semicolon
r_if
c_cond
(paren
id|req-&gt;cmd
op_eq
l_int|NULL
)paren
(brace
id|mconsole_reply
c_func
(paren
id|req
comma
l_string|&quot;Unknown command&quot;
comma
l_int|1
comma
l_int|0
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|mconsole_reply
r_int
id|mconsole_reply
c_func
(paren
r_struct
id|mc_request
op_star
id|req
comma
r_char
op_star
id|str
comma
r_int
id|err
comma
r_int
id|more
)paren
(brace
r_struct
id|mconsole_reply
id|reply
suffix:semicolon
r_int
id|total
comma
id|len
comma
id|n
suffix:semicolon
id|total
op_assign
id|strlen
c_func
(paren
id|str
)paren
suffix:semicolon
r_do
(brace
id|reply.err
op_assign
id|err
suffix:semicolon
multiline_comment|/* err can only be true on the first packet */
id|err
op_assign
l_int|0
suffix:semicolon
id|len
op_assign
id|MIN
c_func
(paren
id|total
comma
id|MCONSOLE_MAX_DATA
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_eq
id|total
)paren
(brace
id|reply.more
op_assign
id|more
suffix:semicolon
)brace
r_else
id|reply.more
op_assign
l_int|1
suffix:semicolon
id|memcpy
c_func
(paren
id|reply.data
comma
id|str
comma
id|len
)paren
suffix:semicolon
id|reply.data
(braket
id|len
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|total
op_sub_assign
id|len
suffix:semicolon
id|str
op_add_assign
id|len
suffix:semicolon
id|reply.len
op_assign
id|len
op_plus
l_int|1
suffix:semicolon
id|len
op_assign
r_sizeof
(paren
id|reply
)paren
op_plus
id|reply.len
op_minus
r_sizeof
(paren
id|reply.data
)paren
suffix:semicolon
id|n
op_assign
id|sendto
c_func
(paren
id|req-&gt;originating_fd
comma
op_amp
id|reply
comma
id|len
comma
l_int|0
comma
(paren
r_struct
id|sockaddr
op_star
)paren
id|req-&gt;origin
comma
id|req-&gt;originlen
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n
OL
l_int|0
)paren
(brace
r_return
op_minus
id|errno
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
id|total
OG
l_int|0
)paren
(brace
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mconsole_unlink_socket
r_int
id|mconsole_unlink_socket
c_func
(paren
r_void
)paren
(brace
id|unlink
c_func
(paren
id|mconsole_socket_name
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|notify_sock
r_static
r_int
id|notify_sock
op_assign
op_minus
l_int|1
suffix:semicolon
DECL|function|mconsole_notify
r_int
id|mconsole_notify
c_func
(paren
r_char
op_star
id|sock_name
comma
r_int
id|type
comma
r_const
r_void
op_star
id|data
comma
r_int
id|len
)paren
(brace
r_struct
id|sockaddr_un
id|target
suffix:semicolon
r_struct
id|mconsole_notify
id|packet
suffix:semicolon
r_int
id|n
comma
id|err
op_assign
l_int|0
suffix:semicolon
id|lock_notify
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|notify_sock
OL
l_int|0
)paren
(brace
id|notify_sock
op_assign
id|socket
c_func
(paren
id|PF_UNIX
comma
id|SOCK_DGRAM
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|notify_sock
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;mconsole_notify - socket failed, errno = %d&bslash;n&quot;
comma
id|errno
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|errno
suffix:semicolon
)brace
)brace
id|unlock_notify
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
r_return
id|err
suffix:semicolon
)brace
id|target.sun_family
op_assign
id|AF_UNIX
suffix:semicolon
id|strcpy
c_func
(paren
id|target.sun_path
comma
id|sock_name
)paren
suffix:semicolon
id|packet.magic
op_assign
id|MCONSOLE_MAGIC
suffix:semicolon
id|packet.version
op_assign
id|MCONSOLE_VERSION
suffix:semicolon
id|packet.type
op_assign
id|type
suffix:semicolon
id|len
op_assign
(paren
id|len
OG
r_sizeof
(paren
id|packet.data
)paren
)paren
ques
c_cond
r_sizeof
(paren
id|packet.data
)paren
suffix:colon
id|len
suffix:semicolon
id|packet.len
op_assign
id|len
suffix:semicolon
id|memcpy
c_func
(paren
id|packet.data
comma
id|data
comma
id|len
)paren
suffix:semicolon
id|err
op_assign
l_int|0
suffix:semicolon
id|len
op_assign
r_sizeof
(paren
id|packet
)paren
op_plus
id|packet.len
op_minus
r_sizeof
(paren
id|packet.data
)paren
suffix:semicolon
id|n
op_assign
id|sendto
c_func
(paren
id|notify_sock
comma
op_amp
id|packet
comma
id|len
comma
l_int|0
comma
(paren
r_struct
id|sockaddr
op_star
)paren
op_amp
id|target
comma
r_sizeof
(paren
id|target
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;mconsole_notify - sendto failed, errno = %d&bslash;n&quot;
comma
id|errno
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|errno
suffix:semicolon
)brace
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
