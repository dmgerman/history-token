multiline_comment|/* &n; * Copyright (C) 2000, 2001 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#include &lt;unistd.h&gt;
macro_line|#include &lt;stdlib.h&gt;
macro_line|#include &lt;errno.h&gt;
macro_line|#include &lt;termios.h&gt;
macro_line|#include &lt;fcntl.h&gt;
macro_line|#include &lt;string.h&gt;
macro_line|#include &lt;signal.h&gt;
macro_line|#include &lt;sys/stat.h&gt;
macro_line|#include &lt;sys/ioctl.h&gt;
macro_line|#include &lt;sys/socket.h&gt;
macro_line|#include &quot;kern_util.h&quot;
macro_line|#include &quot;user_util.h&quot;
macro_line|#include &quot;chan_user.h&quot;
macro_line|#include &quot;user.h&quot;
macro_line|#include &quot;helper.h&quot;
macro_line|#include &quot;os.h&quot;
DECL|function|generic_close
r_void
id|generic_close
c_func
(paren
r_int
id|fd
comma
r_void
op_star
id|unused
)paren
(brace
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
)brace
DECL|function|generic_read
r_int
id|generic_read
c_func
(paren
r_int
id|fd
comma
r_char
op_star
id|c_out
comma
r_void
op_star
id|unused
)paren
(brace
r_int
id|n
suffix:semicolon
id|n
op_assign
id|read
c_func
(paren
id|fd
comma
id|c_out
comma
r_sizeof
(paren
op_star
id|c_out
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
r_if
c_cond
(paren
id|errno
op_eq
id|EAGAIN
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_return
op_minus
id|errno
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|n
op_eq
l_int|0
)paren
(brace
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|generic_write
r_int
id|generic_write
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
id|unused
)paren
(brace
r_int
id|count
suffix:semicolon
id|count
op_assign
id|write
c_func
(paren
id|fd
comma
id|buf
comma
id|n
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
OL
l_int|0
)paren
(brace
r_return
op_minus
id|errno
suffix:semicolon
)brace
r_return
id|count
suffix:semicolon
)brace
DECL|function|generic_console_write
r_int
id|generic_console_write
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
id|unused
)paren
(brace
r_struct
id|termios
id|save
comma
r_new
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
id|isatty
c_func
(paren
id|fd
)paren
)paren
(brace
id|tcgetattr
c_func
(paren
id|fd
comma
op_amp
id|save
)paren
suffix:semicolon
r_new
op_assign
id|save
suffix:semicolon
r_new
dot
id|c_oflag
op_or_assign
id|OPOST
suffix:semicolon
id|tcsetattr
c_func
(paren
id|fd
comma
id|TCSAFLUSH
comma
op_amp
r_new
)paren
suffix:semicolon
)brace
id|err
op_assign
id|generic_write
c_func
(paren
id|fd
comma
id|buf
comma
id|n
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|isatty
c_func
(paren
id|fd
)paren
)paren
(brace
id|tcsetattr
c_func
(paren
id|fd
comma
id|TCSAFLUSH
comma
op_amp
id|save
)paren
suffix:semicolon
)brace
r_return
id|err
suffix:semicolon
)brace
DECL|function|generic_window_size
r_int
id|generic_window_size
c_func
(paren
r_int
id|fd
comma
r_void
op_star
id|unused
comma
r_int
r_int
op_star
id|rows_out
comma
r_int
r_int
op_star
id|cols_out
)paren
(brace
r_struct
id|winsize
id|size
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|ioctl
c_func
(paren
id|fd
comma
id|TIOCGWINSZ
comma
op_amp
id|size
)paren
op_eq
l_int|0
)paren
(brace
id|ret
op_assign
(paren
(paren
op_star
id|rows_out
op_ne
id|size.ws_row
)paren
op_logical_or
(paren
op_star
id|cols_out
op_ne
id|size.ws_col
)paren
)paren
suffix:semicolon
op_star
id|rows_out
op_assign
id|size.ws_row
suffix:semicolon
op_star
id|cols_out
op_assign
id|size.ws_col
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|generic_free
r_void
id|generic_free
c_func
(paren
r_void
op_star
id|data
)paren
(brace
id|kfree
c_func
(paren
id|data
)paren
suffix:semicolon
)brace
DECL|function|winch_handler
r_static
r_void
id|winch_handler
c_func
(paren
r_int
id|sig
)paren
(brace
)brace
DECL|struct|winch_data
r_struct
id|winch_data
(brace
DECL|member|pty_fd
r_int
id|pty_fd
suffix:semicolon
DECL|member|pipe_fd
r_int
id|pipe_fd
suffix:semicolon
DECL|member|close_me
r_int
id|close_me
suffix:semicolon
)brace
suffix:semicolon
DECL|function|winch_thread
r_static
r_int
id|winch_thread
c_func
(paren
r_void
op_star
id|arg
)paren
(brace
r_struct
id|winch_data
op_star
id|data
op_assign
id|arg
suffix:semicolon
id|sigset_t
id|sigs
suffix:semicolon
r_int
id|pty_fd
comma
id|pipe_fd
suffix:semicolon
r_char
id|c
op_assign
l_int|1
suffix:semicolon
id|close
c_func
(paren
id|data-&gt;close_me
)paren
suffix:semicolon
id|pty_fd
op_assign
id|data-&gt;pty_fd
suffix:semicolon
id|pipe_fd
op_assign
id|data-&gt;pipe_fd
suffix:semicolon
r_if
c_cond
(paren
id|write
c_func
(paren
id|pipe_fd
comma
op_amp
id|c
comma
r_sizeof
(paren
id|c
)paren
)paren
op_ne
r_sizeof
(paren
id|c
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;winch_thread : failed to write synchronization &quot;
l_string|&quot;byte, errno = %d&bslash;n&quot;
comma
id|errno
)paren
suffix:semicolon
)brace
id|signal
c_func
(paren
id|SIGWINCH
comma
id|winch_handler
)paren
suffix:semicolon
id|sigfillset
c_func
(paren
op_amp
id|sigs
)paren
suffix:semicolon
id|sigdelset
c_func
(paren
op_amp
id|sigs
comma
id|SIGWINCH
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sigprocmask
c_func
(paren
id|SIG_SETMASK
comma
op_amp
id|sigs
comma
l_int|NULL
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;winch_thread : sigprocmask failed, errno = %d&bslash;n&quot;
comma
id|errno
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|setsid
c_func
(paren
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;winch_thread : setsid failed, errno = %d&bslash;n&quot;
comma
id|errno
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ioctl
c_func
(paren
id|pty_fd
comma
id|TIOCSCTTY
comma
l_int|0
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;winch_thread : TIOCSCTTY failed, errno = %d&bslash;n&quot;
comma
id|errno
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|tcsetpgrp
c_func
(paren
id|pty_fd
comma
id|os_getpid
c_func
(paren
)paren
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;winch_thread : tcsetpgrp failed, errno = %d&bslash;n&quot;
comma
id|errno
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|read
c_func
(paren
id|pipe_fd
comma
op_amp
id|c
comma
r_sizeof
(paren
id|c
)paren
)paren
op_ne
r_sizeof
(paren
id|c
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;winch_thread : failed to read synchronization byte, &quot;
l_string|&quot;errno = %d&bslash;n&quot;
comma
id|errno
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|pause
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|write
c_func
(paren
id|pipe_fd
comma
op_amp
id|c
comma
r_sizeof
(paren
id|c
)paren
)paren
op_ne
r_sizeof
(paren
id|c
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;winch_thread : write failed, errno = %d&bslash;n&quot;
comma
id|errno
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|variable|tracer_winch
r_static
r_int
id|tracer_winch
(braket
l_int|2
)braket
suffix:semicolon
DECL|function|tracer_winch_handler
r_static
r_void
id|tracer_winch_handler
c_func
(paren
r_int
id|sig
)paren
(brace
r_char
id|c
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|write
c_func
(paren
id|tracer_winch
(braket
l_int|1
)braket
comma
op_amp
id|c
comma
r_sizeof
(paren
id|c
)paren
)paren
op_ne
r_sizeof
(paren
id|c
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;tracer_winch_handler - write failed, errno = %d&bslash;n&quot;
comma
id|errno
)paren
suffix:semicolon
)brace
)brace
DECL|function|setup_tracer_winch
r_void
id|setup_tracer_winch
c_func
(paren
r_void
)paren
(brace
r_int
id|err
suffix:semicolon
id|err
op_assign
id|os_pipe
c_func
(paren
id|tracer_winch
comma
l_int|1
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;setup_tracer_winch : os_pipe failed, errno = %d&bslash;n&quot;
comma
op_minus
id|err
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|signal
c_func
(paren
id|SIGWINCH
comma
id|tracer_winch_handler
)paren
suffix:semicolon
)brace
DECL|function|winch_tramp
r_static
r_int
id|winch_tramp
c_func
(paren
r_int
id|fd
comma
r_void
op_star
id|device_data
comma
r_int
op_star
id|fd_out
)paren
(brace
r_struct
id|winch_data
id|data
suffix:semicolon
r_int
r_int
id|stack
suffix:semicolon
r_int
id|fds
(braket
l_int|2
)braket
comma
id|pid
comma
id|n
comma
id|err
suffix:semicolon
r_char
id|c
suffix:semicolon
id|err
op_assign
id|os_pipe
c_func
(paren
id|fds
comma
l_int|1
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;winch_tramp : os_pipe failed, errno = %d&bslash;n&quot;
comma
op_minus
id|err
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
id|data
op_assign
(paren
(paren
r_struct
id|winch_data
)paren
(brace
id|pty_fd
suffix:colon
id|fd
comma
id|pipe_fd
suffix:colon
id|fds
(braket
l_int|1
)braket
comma
id|close_me
suffix:colon
id|fds
(braket
l_int|0
)braket
)brace
)paren
suffix:semicolon
id|pid
op_assign
id|run_helper_thread
c_func
(paren
id|winch_thread
comma
op_amp
id|data
comma
l_int|0
comma
op_amp
id|stack
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pid
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;fork of winch_thread failed - errno = %d&bslash;n&quot;
comma
id|errno
)paren
suffix:semicolon
r_return
id|pid
suffix:semicolon
)brace
id|close
c_func
(paren
id|fds
(braket
l_int|1
)braket
)paren
suffix:semicolon
op_star
id|fd_out
op_assign
id|fds
(braket
l_int|0
)braket
suffix:semicolon
id|n
op_assign
id|read
c_func
(paren
id|fds
(braket
l_int|0
)braket
comma
op_amp
id|c
comma
r_sizeof
(paren
id|c
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n
op_ne
r_sizeof
(paren
id|c
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;winch_tramp : failed to read synchronization byte&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;read returned %d, errno = %d&bslash;n&quot;
comma
id|n
comma
id|errno
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;fd %d will not support SIGWINCH&bslash;n&quot;
comma
id|fd
)paren
suffix:semicolon
op_star
id|fd_out
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
r_return
id|pid
suffix:semicolon
)brace
DECL|function|register_winch
r_void
id|register_winch
c_func
(paren
r_int
id|fd
comma
r_void
op_star
id|device_data
)paren
(brace
r_int
id|pid
comma
id|thread
comma
id|thread_fd
suffix:semicolon
r_char
id|c
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|isatty
c_func
(paren
id|fd
)paren
)paren
(brace
r_return
suffix:semicolon
)brace
id|pid
op_assign
id|tcgetpgrp
c_func
(paren
id|fd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pid
op_eq
id|tracing_pid
)paren
(brace
id|register_winch_irq
c_func
(paren
id|tracer_winch
(braket
l_int|0
)braket
comma
id|fd
comma
op_minus
l_int|1
comma
id|device_data
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|pid
op_eq
op_minus
l_int|1
)paren
(brace
id|thread
op_assign
id|winch_tramp
c_func
(paren
id|fd
comma
id|device_data
comma
op_amp
id|thread_fd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fd
op_ne
op_minus
l_int|1
)paren
(brace
id|register_winch_irq
c_func
(paren
id|thread_fd
comma
id|fd
comma
id|thread
comma
id|device_data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|write
c_func
(paren
id|thread_fd
comma
op_amp
id|c
comma
r_sizeof
(paren
id|c
)paren
)paren
op_ne
r_sizeof
(paren
id|c
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;register_winch : failed to write &quot;
l_string|&quot;synchronization byte&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
)brace
)brace
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof