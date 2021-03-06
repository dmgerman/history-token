multiline_comment|/* &n; * Copyright (C) 2002 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#include &lt;unistd.h&gt;
macro_line|#include &lt;stdlib.h&gt;
macro_line|#include &lt;termios.h&gt;
macro_line|#include &lt;pty.h&gt;
macro_line|#include &lt;signal.h&gt;
macro_line|#include &lt;errno.h&gt;
macro_line|#include &lt;string.h&gt;
macro_line|#include &lt;sched.h&gt;
macro_line|#include &lt;sys/socket.h&gt;
macro_line|#include &lt;sys/poll.h&gt;
macro_line|#include &quot;init.h&quot;
macro_line|#include &quot;user.h&quot;
macro_line|#include &quot;kern_util.h&quot;
macro_line|#include &quot;user_util.h&quot;
macro_line|#include &quot;sigio.h&quot;
macro_line|#include &quot;helper.h&quot;
macro_line|#include &quot;os.h&quot;
multiline_comment|/* Changed during early boot */
DECL|variable|pty_output_sigio
r_int
id|pty_output_sigio
op_assign
l_int|0
suffix:semicolon
DECL|variable|pty_close_sigio
r_int
id|pty_close_sigio
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Used as a flag during SIGIO testing early in boot */
DECL|variable|got_sigio
r_static
r_volatile
r_int
id|got_sigio
op_assign
l_int|0
suffix:semicolon
DECL|function|handler
r_void
id|__init
id|handler
c_func
(paren
r_int
id|sig
)paren
(brace
id|got_sigio
op_assign
l_int|1
suffix:semicolon
)brace
DECL|struct|openpty_arg
r_struct
id|openpty_arg
(brace
DECL|member|master
r_int
id|master
suffix:semicolon
DECL|member|slave
r_int
id|slave
suffix:semicolon
DECL|member|err
r_int
id|err
suffix:semicolon
)brace
suffix:semicolon
DECL|function|openpty_cb
r_static
r_void
id|openpty_cb
c_func
(paren
r_void
op_star
id|arg
)paren
(brace
r_struct
id|openpty_arg
op_star
id|info
op_assign
id|arg
suffix:semicolon
id|info-&gt;err
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|openpty
c_func
(paren
op_amp
id|info-&gt;master
comma
op_amp
id|info-&gt;slave
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
)paren
)paren
(brace
id|info-&gt;err
op_assign
op_minus
id|errno
suffix:semicolon
)brace
)brace
DECL|function|check_one_sigio
r_void
id|__init
id|check_one_sigio
c_func
(paren
r_void
(paren
op_star
id|proc
)paren
(paren
r_int
comma
r_int
)paren
)paren
(brace
r_struct
id|sigaction
id|old
comma
r_new
suffix:semicolon
r_struct
id|openpty_arg
id|pty
op_assign
(brace
dot
id|master
op_assign
op_minus
l_int|1
comma
dot
id|slave
op_assign
op_minus
l_int|1
)brace
suffix:semicolon
r_int
id|master
comma
id|slave
comma
id|err
suffix:semicolon
id|initial_thread_cb
c_func
(paren
id|openpty_cb
comma
op_amp
id|pty
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pty.err
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;openpty failed, errno = %d&bslash;n&quot;
comma
op_minus
id|pty.err
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|master
op_assign
id|pty.master
suffix:semicolon
id|slave
op_assign
id|pty.slave
suffix:semicolon
r_if
c_cond
(paren
(paren
id|master
op_eq
op_minus
l_int|1
)paren
op_logical_or
(paren
id|slave
op_eq
op_minus
l_int|1
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;openpty failed to allocate a pty&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Not now, but complain so we now where we failed. */
id|err
op_assign
id|raw
c_func
(paren
id|master
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
id|panic
c_func
(paren
l_string|&quot;check_sigio : __raw failed, errno = %d&bslash;n&quot;
comma
op_minus
id|err
)paren
suffix:semicolon
id|err
op_assign
id|os_sigio_async
c_func
(paren
id|master
comma
id|slave
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
id|panic
c_func
(paren
l_string|&quot;tty_fds : sigio_async failed, err = %d&bslash;n&quot;
comma
op_minus
id|err
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sigaction
c_func
(paren
id|SIGIO
comma
l_int|NULL
comma
op_amp
id|old
)paren
OL
l_int|0
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;check_sigio : sigaction 1 failed, errno = %d&bslash;n&quot;
comma
id|errno
)paren
suffix:semicolon
)brace
r_new
op_assign
id|old
suffix:semicolon
r_new
dot
id|sa_handler
op_assign
id|handler
suffix:semicolon
r_if
c_cond
(paren
id|sigaction
c_func
(paren
id|SIGIO
comma
op_amp
r_new
comma
l_int|NULL
)paren
OL
l_int|0
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;check_sigio : sigaction 2 failed, errno = %d&bslash;n&quot;
comma
id|errno
)paren
suffix:semicolon
)brace
id|got_sigio
op_assign
l_int|0
suffix:semicolon
(paren
op_star
id|proc
)paren
(paren
id|master
comma
id|slave
)paren
suffix:semicolon
id|os_close_file
c_func
(paren
id|master
)paren
suffix:semicolon
id|os_close_file
c_func
(paren
id|slave
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sigaction
c_func
(paren
id|SIGIO
comma
op_amp
id|old
comma
l_int|NULL
)paren
OL
l_int|0
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;check_sigio : sigaction 3 failed, errno = %d&bslash;n&quot;
comma
id|errno
)paren
suffix:semicolon
)brace
)brace
DECL|function|tty_output
r_static
r_void
id|tty_output
c_func
(paren
r_int
id|master
comma
r_int
id|slave
)paren
(brace
r_int
id|n
suffix:semicolon
r_char
id|buf
(braket
l_int|512
)braket
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Checking that host ptys support output SIGIO...&quot;
)paren
suffix:semicolon
id|memset
c_func
(paren
id|buf
comma
l_int|0
comma
r_sizeof
(paren
id|buf
)paren
)paren
suffix:semicolon
r_while
c_loop
(paren
id|os_write_file
c_func
(paren
id|master
comma
id|buf
comma
r_sizeof
(paren
id|buf
)paren
)paren
OG
l_int|0
)paren
(brace
suffix:semicolon
)brace
r_if
c_cond
(paren
id|errno
op_ne
id|EAGAIN
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;check_sigio : write failed, errno = %d&bslash;n&quot;
comma
id|errno
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
(paren
id|n
op_assign
id|os_read_file
c_func
(paren
id|slave
comma
id|buf
comma
r_sizeof
(paren
id|buf
)paren
)paren
)paren
OG
l_int|0
)paren
op_logical_and
op_logical_neg
id|got_sigio
)paren
(brace
suffix:semicolon
)brace
r_if
c_cond
(paren
id|got_sigio
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Yes&bslash;n&quot;
)paren
suffix:semicolon
id|pty_output_sigio
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|n
op_eq
op_minus
id|EAGAIN
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;No, enabling workaround&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|panic
c_func
(paren
l_string|&quot;check_sigio : read failed, err = %d&bslash;n&quot;
comma
id|n
)paren
suffix:semicolon
)brace
)brace
DECL|function|tty_close
r_static
r_void
id|tty_close
c_func
(paren
r_int
id|master
comma
r_int
id|slave
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Checking that host ptys support SIGIO on close...&quot;
)paren
suffix:semicolon
id|os_close_file
c_func
(paren
id|slave
)paren
suffix:semicolon
r_if
c_cond
(paren
id|got_sigio
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Yes&bslash;n&quot;
)paren
suffix:semicolon
id|pty_close_sigio
op_assign
l_int|1
suffix:semicolon
)brace
r_else
id|printk
c_func
(paren
l_string|&quot;No, enabling workaround&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|check_sigio
r_void
id|__init
id|check_sigio
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
(paren
id|os_access
c_func
(paren
l_string|&quot;/dev/ptmx&quot;
comma
id|OS_ACC_R_OK
)paren
OL
l_int|0
)paren
op_logical_and
(paren
id|os_access
c_func
(paren
l_string|&quot;/dev/ptyp0&quot;
comma
id|OS_ACC_R_OK
)paren
OL
l_int|0
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;No pseudo-terminals available - skipping pty SIGIO &quot;
l_string|&quot;check&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|check_one_sigio
c_func
(paren
id|tty_output
)paren
suffix:semicolon
id|check_one_sigio
c_func
(paren
id|tty_close
)paren
suffix:semicolon
)brace
multiline_comment|/* Protected by sigio_lock(), also used by sigio_cleanup, which is an &n; * exitcall.&n; */
DECL|variable|write_sigio_pid
r_static
r_int
id|write_sigio_pid
op_assign
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* These arrays are initialized before the sigio thread is started, and&n; * the descriptors closed after it is killed.  So, it can&squot;t see them change.&n; * On the UML side, they are changed under the sigio_lock.&n; */
DECL|variable|write_sigio_fds
r_static
r_int
id|write_sigio_fds
(braket
l_int|2
)braket
op_assign
(brace
op_minus
l_int|1
comma
op_minus
l_int|1
)brace
suffix:semicolon
DECL|variable|sigio_private
r_static
r_int
id|sigio_private
(braket
l_int|2
)braket
op_assign
(brace
op_minus
l_int|1
comma
op_minus
l_int|1
)brace
suffix:semicolon
DECL|struct|pollfds
r_struct
id|pollfds
(brace
DECL|member|poll
r_struct
id|pollfd
op_star
id|poll
suffix:semicolon
DECL|member|size
r_int
id|size
suffix:semicolon
DECL|member|used
r_int
id|used
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Protected by sigio_lock().  Used by the sigio thread, but the UML thread&n; * synchronizes with it.&n; */
DECL|variable|current_poll
r_struct
id|pollfds
id|current_poll
op_assign
(brace
dot
id|poll
op_assign
l_int|NULL
comma
dot
id|size
op_assign
l_int|0
comma
dot
id|used
op_assign
l_int|0
)brace
suffix:semicolon
DECL|variable|next_poll
r_struct
id|pollfds
id|next_poll
op_assign
(brace
dot
id|poll
op_assign
l_int|NULL
comma
dot
id|size
op_assign
l_int|0
comma
dot
id|used
op_assign
l_int|0
)brace
suffix:semicolon
DECL|function|write_sigio_thread
r_static
r_int
id|write_sigio_thread
c_func
(paren
r_void
op_star
id|unused
)paren
(brace
r_struct
id|pollfds
op_star
id|fds
comma
id|tmp
suffix:semicolon
r_struct
id|pollfd
op_star
id|p
suffix:semicolon
r_int
id|i
comma
id|n
comma
id|respond_fd
suffix:semicolon
r_char
id|c
suffix:semicolon
id|fds
op_assign
op_amp
id|current_poll
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|n
op_assign
id|poll
c_func
(paren
id|fds-&gt;poll
comma
id|fds-&gt;used
comma
op_minus
l_int|1
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
id|EINTR
)paren
(brace
r_continue
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;write_sigio_thread : poll returned %d, &quot;
l_string|&quot;errno = %d&bslash;n&quot;
comma
id|n
comma
id|errno
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|fds-&gt;used
suffix:semicolon
id|i
op_increment
)paren
(brace
id|p
op_assign
op_amp
id|fds-&gt;poll
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;revents
op_eq
l_int|0
)paren
(brace
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|p-&gt;fd
op_eq
id|sigio_private
(braket
l_int|1
)braket
)paren
(brace
id|n
op_assign
id|os_read_file
c_func
(paren
id|sigio_private
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
l_string|&quot;write_sigio_thread : &quot;
l_string|&quot;read failed, err = %d&bslash;n&quot;
comma
op_minus
id|n
)paren
suffix:semicolon
)brace
id|tmp
op_assign
id|current_poll
suffix:semicolon
id|current_poll
op_assign
id|next_poll
suffix:semicolon
id|next_poll
op_assign
id|tmp
suffix:semicolon
id|respond_fd
op_assign
id|sigio_private
(braket
l_int|1
)braket
suffix:semicolon
)brace
r_else
(brace
id|respond_fd
op_assign
id|write_sigio_fds
(braket
l_int|1
)braket
suffix:semicolon
id|fds-&gt;used
op_decrement
suffix:semicolon
id|memmove
c_func
(paren
op_amp
id|fds-&gt;poll
(braket
id|i
)braket
comma
op_amp
id|fds-&gt;poll
(braket
id|i
op_plus
l_int|1
)braket
comma
(paren
id|fds-&gt;used
op_minus
id|i
)paren
op_star
r_sizeof
(paren
op_star
id|fds-&gt;poll
)paren
)paren
suffix:semicolon
)brace
id|n
op_assign
id|os_write_file
c_func
(paren
id|respond_fd
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
l_string|&quot;write_sigio_thread : write failed, &quot;
l_string|&quot;err = %d&bslash;n&quot;
comma
op_minus
id|n
)paren
suffix:semicolon
)brace
)brace
)brace
)brace
DECL|function|need_poll
r_static
r_int
id|need_poll
c_func
(paren
r_int
id|n
)paren
(brace
r_if
c_cond
(paren
id|n
op_le
id|next_poll.size
)paren
(brace
id|next_poll.used
op_assign
id|n
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|next_poll.poll
op_ne
l_int|NULL
)paren
(brace
id|kfree
c_func
(paren
id|next_poll.poll
)paren
suffix:semicolon
)brace
id|next_poll.poll
op_assign
id|um_kmalloc_atomic
c_func
(paren
id|n
op_star
r_sizeof
(paren
r_struct
id|pollfd
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|next_poll.poll
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;need_poll : failed to allocate new pollfds&bslash;n&quot;
)paren
suffix:semicolon
id|next_poll.size
op_assign
l_int|0
suffix:semicolon
id|next_poll.used
op_assign
l_int|0
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|next_poll.size
op_assign
id|n
suffix:semicolon
id|next_poll.used
op_assign
id|n
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Must be called with sigio_lock held, because it&squot;s needed by the marked&n; * critical section. */
DECL|function|update_thread
r_static
r_void
id|update_thread
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|n
suffix:semicolon
r_char
id|c
suffix:semicolon
id|flags
op_assign
id|set_signals
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|n
op_assign
id|os_write_file
c_func
(paren
id|sigio_private
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
l_string|&quot;update_thread : write failed, err = %d&bslash;n&quot;
comma
op_minus
id|n
)paren
suffix:semicolon
r_goto
id|fail
suffix:semicolon
)brace
id|n
op_assign
id|os_read_file
c_func
(paren
id|sigio_private
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
l_string|&quot;update_thread : read failed, err = %d&bslash;n&quot;
comma
op_minus
id|n
)paren
suffix:semicolon
r_goto
id|fail
suffix:semicolon
)brace
id|set_signals
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
suffix:semicolon
id|fail
suffix:colon
multiline_comment|/* Critical section start */
r_if
c_cond
(paren
id|write_sigio_pid
op_ne
op_minus
l_int|1
)paren
(brace
id|os_kill_process
c_func
(paren
id|write_sigio_pid
comma
l_int|1
)paren
suffix:semicolon
)brace
id|write_sigio_pid
op_assign
op_minus
l_int|1
suffix:semicolon
id|os_close_file
c_func
(paren
id|sigio_private
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|os_close_file
c_func
(paren
id|sigio_private
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|os_close_file
c_func
(paren
id|write_sigio_fds
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|os_close_file
c_func
(paren
id|write_sigio_fds
(braket
l_int|1
)braket
)paren
suffix:semicolon
multiline_comment|/* Critical section end */
id|set_signals
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|add_sigio_fd
r_int
id|add_sigio_fd
c_func
(paren
r_int
id|fd
comma
r_int
id|read
)paren
(brace
r_int
id|err
op_assign
l_int|0
comma
id|i
comma
id|n
comma
id|events
suffix:semicolon
id|sigio_lock
c_func
(paren
)paren
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
id|current_poll.used
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|current_poll.poll
(braket
id|i
)braket
dot
id|fd
op_eq
id|fd
)paren
(brace
r_goto
id|out
suffix:semicolon
)brace
)brace
id|n
op_assign
id|current_poll.used
op_plus
l_int|1
suffix:semicolon
id|err
op_assign
id|need_poll
c_func
(paren
id|n
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
r_goto
id|out
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|current_poll.used
suffix:semicolon
id|i
op_increment
)paren
(brace
id|next_poll.poll
(braket
id|i
)braket
op_assign
id|current_poll.poll
(braket
id|i
)braket
suffix:semicolon
)brace
r_if
c_cond
(paren
id|read
)paren
(brace
id|events
op_assign
id|POLLIN
suffix:semicolon
)brace
r_else
id|events
op_assign
id|POLLOUT
suffix:semicolon
id|next_poll.poll
(braket
id|n
op_minus
l_int|1
)braket
op_assign
(paren
(paren
r_struct
id|pollfd
)paren
(brace
dot
id|fd
op_assign
id|fd
comma
dot
id|events
op_assign
id|events
comma
dot
id|revents
op_assign
l_int|0
)brace
)paren
suffix:semicolon
id|update_thread
c_func
(paren
)paren
suffix:semicolon
id|out
suffix:colon
id|sigio_unlock
c_func
(paren
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|ignore_sigio_fd
r_int
id|ignore_sigio_fd
c_func
(paren
r_int
id|fd
)paren
(brace
r_struct
id|pollfd
op_star
id|p
suffix:semicolon
r_int
id|err
op_assign
l_int|0
comma
id|i
comma
id|n
op_assign
l_int|0
suffix:semicolon
id|sigio_lock
c_func
(paren
)paren
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
id|current_poll.used
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|current_poll.poll
(braket
id|i
)braket
dot
id|fd
op_eq
id|fd
)paren
(brace
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|i
op_eq
id|current_poll.used
)paren
(brace
r_goto
id|out
suffix:semicolon
)brace
id|err
op_assign
id|need_poll
c_func
(paren
id|current_poll.used
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
r_goto
id|out
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|current_poll.used
suffix:semicolon
id|i
op_increment
)paren
(brace
id|p
op_assign
op_amp
id|current_poll.poll
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;fd
op_ne
id|fd
)paren
(brace
id|next_poll.poll
(braket
id|n
op_increment
)braket
op_assign
id|current_poll.poll
(braket
id|i
)braket
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|n
op_eq
id|i
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ignore_sigio_fd : fd %d not found&bslash;n&quot;
comma
id|fd
)paren
suffix:semicolon
id|err
op_assign
op_minus
l_int|1
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|update_thread
c_func
(paren
)paren
suffix:semicolon
id|out
suffix:colon
id|sigio_unlock
c_func
(paren
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|setup_initial_poll
r_static
r_int
id|setup_initial_poll
c_func
(paren
r_int
id|fd
)paren
(brace
r_struct
id|pollfd
op_star
id|p
suffix:semicolon
id|p
op_assign
id|um_kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|pollfd
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;setup_initial_poll : failed to allocate poll&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
op_star
id|p
op_assign
(paren
(paren
r_struct
id|pollfd
)paren
(brace
dot
id|fd
op_assign
id|fd
comma
dot
id|events
op_assign
id|POLLIN
comma
dot
id|revents
op_assign
l_int|0
)brace
)paren
suffix:semicolon
id|current_poll
op_assign
(paren
(paren
r_struct
id|pollfds
)paren
(brace
dot
id|poll
op_assign
id|p
comma
dot
id|used
op_assign
l_int|1
comma
dot
id|size
op_assign
l_int|1
)brace
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|write_sigio_workaround
r_void
id|write_sigio_workaround
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|stack
suffix:semicolon
r_int
id|err
suffix:semicolon
id|sigio_lock
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|write_sigio_pid
op_ne
op_minus
l_int|1
)paren
(brace
r_goto
id|out
suffix:semicolon
)brace
id|err
op_assign
id|os_pipe
c_func
(paren
id|write_sigio_fds
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
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;write_sigio_workaround - os_pipe 1 failed, &quot;
l_string|&quot;err = %d&bslash;n&quot;
comma
op_minus
id|err
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|err
op_assign
id|os_pipe
c_func
(paren
id|sigio_private
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
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;write_sigio_workaround - os_pipe 2 failed, &quot;
l_string|&quot;err = %d&bslash;n&quot;
comma
op_minus
id|err
)paren
suffix:semicolon
r_goto
id|out_close1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|setup_initial_poll
c_func
(paren
id|sigio_private
(braket
l_int|1
)braket
)paren
)paren
(brace
r_goto
id|out_close2
suffix:semicolon
)brace
id|write_sigio_pid
op_assign
id|run_helper_thread
c_func
(paren
id|write_sigio_thread
comma
l_int|NULL
comma
id|CLONE_FILES
op_or
id|CLONE_VM
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
id|write_sigio_pid
OL
l_int|0
)paren
(brace
r_goto
id|out_close2
suffix:semicolon
)brace
r_if
c_cond
(paren
id|write_sigio_irq
c_func
(paren
id|write_sigio_fds
(braket
l_int|0
)braket
)paren
)paren
(brace
r_goto
id|out_kill
suffix:semicolon
)brace
id|out
suffix:colon
id|sigio_unlock
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
id|out_kill
suffix:colon
id|os_kill_process
c_func
(paren
id|write_sigio_pid
comma
l_int|1
)paren
suffix:semicolon
id|write_sigio_pid
op_assign
op_minus
l_int|1
suffix:semicolon
id|out_close2
suffix:colon
id|os_close_file
c_func
(paren
id|sigio_private
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|os_close_file
c_func
(paren
id|sigio_private
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|out_close1
suffix:colon
id|os_close_file
c_func
(paren
id|write_sigio_fds
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|os_close_file
c_func
(paren
id|write_sigio_fds
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|sigio_unlock
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|read_sigio_fd
r_int
id|read_sigio_fd
c_func
(paren
r_int
id|fd
)paren
(brace
r_int
id|n
suffix:semicolon
r_char
id|c
suffix:semicolon
id|n
op_assign
id|os_read_file
c_func
(paren
id|fd
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
l_string|&quot;read_sigio_fd - read failed, err = %d&bslash;n&quot;
comma
op_minus
id|n
)paren
suffix:semicolon
r_return
id|n
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;read_sigio_fd - short read, bytes = %d&bslash;n&quot;
comma
id|n
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
)brace
r_return
id|n
suffix:semicolon
)brace
DECL|function|sigio_cleanup
r_static
r_void
id|sigio_cleanup
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|write_sigio_pid
op_ne
op_minus
l_int|1
)paren
(brace
id|os_kill_process
c_func
(paren
id|write_sigio_pid
comma
l_int|1
)paren
suffix:semicolon
id|write_sigio_pid
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
)brace
DECL|variable|sigio_cleanup
id|__uml_exitcall
c_func
(paren
id|sigio_cleanup
)paren
suffix:semicolon
eof
