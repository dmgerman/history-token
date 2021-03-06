multiline_comment|/* &n; * Copyright (C) 2001 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#include &lt;stdio.h&gt;
macro_line|#include &lt;stddef.h&gt;
macro_line|#include &lt;stdlib.h&gt;
macro_line|#include &lt;string.h&gt;
macro_line|#include &lt;errno.h&gt;
macro_line|#include &lt;unistd.h&gt;
macro_line|#include &lt;termios.h&gt;
macro_line|#include &lt;sys/socket.h&gt;
macro_line|#include &lt;sys/un.h&gt;
macro_line|#include &lt;netinet/in.h&gt;
macro_line|#include &quot;user_util.h&quot;
macro_line|#include &quot;kern_util.h&quot;
macro_line|#include &quot;user.h&quot;
macro_line|#include &quot;chan_user.h&quot;
macro_line|#include &quot;port.h&quot;
macro_line|#include &quot;helper.h&quot;
macro_line|#include &quot;os.h&quot;
DECL|struct|port_chan
r_struct
id|port_chan
(brace
DECL|member|raw
r_int
id|raw
suffix:semicolon
DECL|member|tt
r_struct
id|termios
id|tt
suffix:semicolon
DECL|member|kernel_data
r_void
op_star
id|kernel_data
suffix:semicolon
DECL|member|dev
r_char
id|dev
(braket
r_sizeof
(paren
l_string|&quot;32768&bslash;0&quot;
)paren
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|function|port_init
r_static
r_void
op_star
id|port_init
c_func
(paren
r_char
op_star
id|str
comma
r_int
id|device
comma
r_struct
id|chan_opts
op_star
id|opts
)paren
(brace
r_struct
id|port_chan
op_star
id|data
suffix:semicolon
r_void
op_star
id|kern_data
suffix:semicolon
r_char
op_star
id|end
suffix:semicolon
r_int
id|port
suffix:semicolon
r_if
c_cond
(paren
op_star
id|str
op_ne
l_char|&squot;:&squot;
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;port_init : channel type &squot;port&squot; must specify a &quot;
l_string|&quot;port number&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|str
op_increment
suffix:semicolon
id|port
op_assign
id|strtoul
c_func
(paren
id|str
comma
op_amp
id|end
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
op_star
id|end
op_ne
l_char|&squot;&bslash;0&squot;
)paren
op_logical_or
(paren
id|end
op_eq
id|str
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;port_init : couldn&squot;t parse port &squot;%s&squot;&bslash;n&quot;
comma
id|str
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|kern_data
op_assign
id|port_data
c_func
(paren
id|port
)paren
suffix:semicolon
r_if
c_cond
(paren
id|kern_data
op_eq
l_int|NULL
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
id|data
op_assign
id|um_kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|data
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|data
op_eq
l_int|NULL
)paren
(brace
r_goto
id|err
suffix:semicolon
)brace
op_star
id|data
op_assign
(paren
(paren
r_struct
id|port_chan
)paren
(brace
dot
id|raw
op_assign
id|opts-&gt;raw
comma
dot
id|kernel_data
op_assign
id|kern_data
)brace
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|data-&gt;dev
comma
l_string|&quot;%d&quot;
comma
id|port
)paren
suffix:semicolon
r_return
id|data
suffix:semicolon
id|err
suffix:colon
id|port_kern_free
c_func
(paren
id|kern_data
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|port_free
r_static
r_void
id|port_free
c_func
(paren
r_void
op_star
id|d
)paren
(brace
r_struct
id|port_chan
op_star
id|data
op_assign
id|d
suffix:semicolon
id|port_kern_free
c_func
(paren
id|data-&gt;kernel_data
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|data
)paren
suffix:semicolon
)brace
DECL|function|port_open
r_static
r_int
id|port_open
c_func
(paren
r_int
id|input
comma
r_int
id|output
comma
r_int
id|primary
comma
r_void
op_star
id|d
comma
r_char
op_star
op_star
id|dev_out
)paren
(brace
r_struct
id|port_chan
op_star
id|data
op_assign
id|d
suffix:semicolon
r_int
id|fd
comma
id|err
suffix:semicolon
id|fd
op_assign
id|port_wait
c_func
(paren
id|data-&gt;kernel_data
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|fd
op_ge
l_int|0
)paren
op_logical_and
id|data-&gt;raw
)paren
(brace
id|CATCH_EINTR
c_func
(paren
id|err
op_assign
id|tcgetattr
c_func
(paren
id|fd
comma
op_amp
id|data-&gt;tt
)paren
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
id|err
op_assign
id|raw
c_func
(paren
id|fd
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
)brace
op_star
id|dev_out
op_assign
id|data-&gt;dev
suffix:semicolon
r_return
id|fd
suffix:semicolon
)brace
DECL|function|port_close
r_static
r_void
id|port_close
c_func
(paren
r_int
id|fd
comma
r_void
op_star
id|d
)paren
(brace
r_struct
id|port_chan
op_star
id|data
op_assign
id|d
suffix:semicolon
id|port_remove_dev
c_func
(paren
id|data-&gt;kernel_data
)paren
suffix:semicolon
id|os_close_file
c_func
(paren
id|fd
)paren
suffix:semicolon
)brace
DECL|function|port_console_write
r_static
r_int
id|port_console_write
c_func
(paren
r_int
id|fd
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|n
comma
r_void
op_star
id|d
)paren
(brace
r_struct
id|port_chan
op_star
id|data
op_assign
id|d
suffix:semicolon
r_return
id|generic_console_write
c_func
(paren
id|fd
comma
id|buf
comma
id|n
comma
op_amp
id|data-&gt;tt
)paren
suffix:semicolon
)brace
DECL|variable|port_ops
r_struct
id|chan_ops
id|port_ops
op_assign
(brace
dot
id|type
op_assign
l_string|&quot;port&quot;
comma
dot
id|init
op_assign
id|port_init
comma
dot
id|open
op_assign
id|port_open
comma
dot
id|close
op_assign
id|port_close
comma
dot
id|read
op_assign
id|generic_read
comma
dot
id|write
op_assign
id|generic_write
comma
dot
id|console_write
op_assign
id|port_console_write
comma
dot
id|window_size
op_assign
id|generic_window_size
comma
dot
id|free
op_assign
id|port_free
comma
dot
id|winch
op_assign
l_int|1
comma
)brace
suffix:semicolon
DECL|function|port_listen_fd
r_int
id|port_listen_fd
c_func
(paren
r_int
id|port
)paren
(brace
r_struct
id|sockaddr_in
id|addr
suffix:semicolon
r_int
id|fd
comma
id|err
comma
id|arg
suffix:semicolon
id|fd
op_assign
id|socket
c_func
(paren
id|PF_INET
comma
id|SOCK_STREAM
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fd
op_eq
op_minus
l_int|1
)paren
(brace
r_return
op_minus
id|errno
suffix:semicolon
)brace
id|arg
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|setsockopt
c_func
(paren
id|fd
comma
id|SOL_SOCKET
comma
id|SO_REUSEADDR
comma
op_amp
id|arg
comma
r_sizeof
(paren
id|arg
)paren
)paren
OL
l_int|0
)paren
(brace
id|err
op_assign
op_minus
id|errno
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|addr.sin_family
op_assign
id|AF_INET
suffix:semicolon
id|addr.sin_port
op_assign
id|htons
c_func
(paren
id|port
)paren
suffix:semicolon
id|addr.sin_addr.s_addr
op_assign
id|htonl
c_func
(paren
id|INADDR_ANY
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bind
c_func
(paren
id|fd
comma
(paren
r_struct
id|sockaddr
op_star
)paren
op_amp
id|addr
comma
r_sizeof
(paren
id|addr
)paren
)paren
OL
l_int|0
)paren
(brace
id|err
op_assign
op_minus
id|errno
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|listen
c_func
(paren
id|fd
comma
l_int|1
)paren
OL
l_int|0
)paren
(brace
id|err
op_assign
op_minus
id|errno
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|err
op_assign
id|os_set_fd_block
c_func
(paren
id|fd
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
(brace
r_goto
id|out
suffix:semicolon
)brace
r_return
id|fd
suffix:semicolon
id|out
suffix:colon
id|os_close_file
c_func
(paren
id|fd
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|struct|port_pre_exec_data
r_struct
id|port_pre_exec_data
(brace
DECL|member|sock_fd
r_int
id|sock_fd
suffix:semicolon
DECL|member|pipe_fd
r_int
id|pipe_fd
suffix:semicolon
)brace
suffix:semicolon
DECL|function|port_pre_exec
r_void
id|port_pre_exec
c_func
(paren
r_void
op_star
id|arg
)paren
(brace
r_struct
id|port_pre_exec_data
op_star
id|data
op_assign
id|arg
suffix:semicolon
id|dup2
c_func
(paren
id|data-&gt;sock_fd
comma
l_int|0
)paren
suffix:semicolon
id|dup2
c_func
(paren
id|data-&gt;sock_fd
comma
l_int|1
)paren
suffix:semicolon
id|dup2
c_func
(paren
id|data-&gt;sock_fd
comma
l_int|2
)paren
suffix:semicolon
id|os_close_file
c_func
(paren
id|data-&gt;sock_fd
)paren
suffix:semicolon
id|dup2
c_func
(paren
id|data-&gt;pipe_fd
comma
l_int|3
)paren
suffix:semicolon
id|os_shutdown_socket
c_func
(paren
l_int|3
comma
l_int|1
comma
l_int|0
)paren
suffix:semicolon
id|os_close_file
c_func
(paren
id|data-&gt;pipe_fd
)paren
suffix:semicolon
)brace
DECL|function|port_connection
r_int
id|port_connection
c_func
(paren
r_int
id|fd
comma
r_int
op_star
id|socket
comma
r_int
op_star
id|pid_out
)paren
(brace
r_int
r_new
comma
id|err
suffix:semicolon
r_char
op_star
id|argv
(braket
)braket
op_assign
(brace
l_string|&quot;/usr/sbin/in.telnetd&quot;
comma
l_string|&quot;-L&quot;
comma
l_string|&quot;/usr/lib/uml/port-helper&quot;
comma
l_int|NULL
)brace
suffix:semicolon
r_struct
id|port_pre_exec_data
id|data
suffix:semicolon
r_new
op_assign
id|os_accept_connection
c_func
(paren
id|fd
)paren
suffix:semicolon
r_if
c_cond
(paren
r_new
OL
l_int|0
)paren
(brace
r_return
r_new
suffix:semicolon
)brace
id|err
op_assign
id|os_pipe
c_func
(paren
id|socket
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
(brace
r_goto
id|out_close
suffix:semicolon
)brace
id|data
op_assign
(paren
(paren
r_struct
id|port_pre_exec_data
)paren
(brace
dot
id|sock_fd
op_assign
r_new
comma
dot
id|pipe_fd
op_assign
id|socket
(braket
l_int|1
)braket
)brace
)paren
suffix:semicolon
id|err
op_assign
id|run_helper
c_func
(paren
id|port_pre_exec
comma
op_amp
id|data
comma
id|argv
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
(brace
r_goto
id|out_shutdown
suffix:semicolon
)brace
op_star
id|pid_out
op_assign
id|err
suffix:semicolon
r_return
r_new
suffix:semicolon
id|out_shutdown
suffix:colon
id|os_shutdown_socket
c_func
(paren
id|socket
(braket
l_int|0
)braket
comma
l_int|1
comma
l_int|1
)paren
suffix:semicolon
id|os_close_file
c_func
(paren
id|socket
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|os_shutdown_socket
c_func
(paren
id|socket
(braket
l_int|1
)braket
comma
l_int|1
comma
l_int|1
)paren
suffix:semicolon
id|os_close_file
c_func
(paren
id|socket
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|out_close
suffix:colon
id|os_close_file
c_func
(paren
r_new
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
