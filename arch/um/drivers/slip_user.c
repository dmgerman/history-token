macro_line|#include &lt;stdio.h&gt;
macro_line|#include &lt;stdlib.h&gt;
macro_line|#include &lt;unistd.h&gt;
macro_line|#include &lt;stddef.h&gt;
macro_line|#include &lt;sched.h&gt;
macro_line|#include &lt;string.h&gt;
macro_line|#include &lt;sys/fcntl.h&gt;
macro_line|#include &lt;sys/errno.h&gt;
macro_line|#include &lt;sys/termios.h&gt;
macro_line|#include &lt;sys/wait.h&gt;
macro_line|#include &lt;sys/ioctl.h&gt;
macro_line|#include &lt;sys/signal.h&gt;
macro_line|#include &quot;user_util.h&quot;
macro_line|#include &quot;kern_util.h&quot;
macro_line|#include &quot;user.h&quot;
macro_line|#include &quot;net_user.h&quot;
macro_line|#include &quot;slip.h&quot;
macro_line|#include &quot;helper.h&quot;
macro_line|#include &quot;os.h&quot;
DECL|function|slip_user_init
r_void
id|slip_user_init
c_func
(paren
r_void
op_star
id|data
comma
r_void
op_star
id|dev
)paren
(brace
r_struct
id|slip_data
op_star
id|pri
op_assign
id|data
suffix:semicolon
id|pri-&gt;dev
op_assign
id|dev
suffix:semicolon
)brace
DECL|function|set_up_tty
r_static
r_int
id|set_up_tty
c_func
(paren
r_int
id|fd
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|termios
id|tios
suffix:semicolon
r_if
c_cond
(paren
id|tcgetattr
c_func
(paren
id|fd
comma
op_amp
id|tios
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;could not get initial terminal attributes&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|tios.c_cflag
op_assign
id|CS8
op_or
id|CREAD
op_or
id|HUPCL
op_or
id|CLOCAL
suffix:semicolon
id|tios.c_iflag
op_assign
id|IGNBRK
op_or
id|IGNPAR
suffix:semicolon
id|tios.c_oflag
op_assign
l_int|0
suffix:semicolon
id|tios.c_lflag
op_assign
l_int|0
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
id|NCCS
suffix:semicolon
id|i
op_increment
)paren
id|tios.c_cc
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
id|tios.c_cc
(braket
id|VMIN
)braket
op_assign
l_int|1
suffix:semicolon
id|tios.c_cc
(braket
id|VTIME
)braket
op_assign
l_int|0
suffix:semicolon
id|cfsetospeed
c_func
(paren
op_amp
id|tios
comma
id|B38400
)paren
suffix:semicolon
id|cfsetispeed
c_func
(paren
op_amp
id|tios
comma
id|B38400
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tcsetattr
c_func
(paren
id|fd
comma
id|TCSAFLUSH
comma
op_amp
id|tios
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;failed to set terminal attributes&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|struct|slip_pre_exec_data
r_struct
id|slip_pre_exec_data
(brace
DECL|member|stdin
r_int
id|stdin
suffix:semicolon
DECL|member|stdout
r_int
id|stdout
suffix:semicolon
DECL|member|close_me
r_int
id|close_me
suffix:semicolon
)brace
suffix:semicolon
DECL|function|slip_pre_exec
r_static
r_void
id|slip_pre_exec
c_func
(paren
r_void
op_star
id|arg
)paren
(brace
r_struct
id|slip_pre_exec_data
op_star
id|data
op_assign
id|arg
suffix:semicolon
r_if
c_cond
(paren
id|data-&gt;stdin
op_ne
op_minus
l_int|1
)paren
(brace
id|dup2
c_func
(paren
id|data-&gt;stdin
comma
l_int|0
)paren
suffix:semicolon
)brace
id|dup2
c_func
(paren
id|data-&gt;stdout
comma
l_int|1
)paren
suffix:semicolon
id|close
c_func
(paren
id|data-&gt;close_me
)paren
suffix:semicolon
)brace
DECL|function|slip_tramp
r_static
r_int
id|slip_tramp
c_func
(paren
r_char
op_star
op_star
id|argv
comma
r_int
id|fd
)paren
(brace
r_struct
id|slip_pre_exec_data
id|pe_data
suffix:semicolon
r_char
op_star
id|output
suffix:semicolon
r_int
id|status
comma
id|pid
comma
id|fds
(braket
l_int|2
)braket
comma
id|err
comma
id|output_len
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
l_int|0
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
l_string|&quot;slip_tramp : pipe failed, errno = %d&bslash;n&quot;
comma
op_minus
id|err
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
id|err
op_assign
l_int|0
suffix:semicolon
id|pe_data.stdin
op_assign
id|fd
suffix:semicolon
id|pe_data.stdout
op_assign
id|fds
(braket
l_int|1
)braket
suffix:semicolon
id|pe_data.close_me
op_assign
id|fds
(braket
l_int|0
)braket
suffix:semicolon
id|pid
op_assign
id|run_helper
c_func
(paren
id|slip_pre_exec
comma
op_amp
id|pe_data
comma
id|argv
comma
l_int|NULL
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
id|err
op_assign
id|pid
suffix:semicolon
)brace
r_else
(brace
id|output_len
op_assign
id|page_size
c_func
(paren
)paren
suffix:semicolon
id|output
op_assign
id|um_kmalloc
c_func
(paren
id|output_len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|output
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;slip_tramp : failed to allocate output &quot;
l_string|&quot;buffer&bslash;n&quot;
)paren
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
id|read_output
c_func
(paren
id|fds
(braket
l_int|0
)braket
comma
id|output
comma
id|output_len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|output
op_ne
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s&quot;
comma
id|output
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|output
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|waitpid
c_func
(paren
id|pid
comma
op_amp
id|status
comma
l_int|0
)paren
OL
l_int|0
)paren
(brace
id|err
op_assign
id|errno
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|WIFEXITED
c_func
(paren
id|status
)paren
op_logical_or
(paren
id|WEXITSTATUS
c_func
(paren
id|status
)paren
op_ne
l_int|0
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;&squot;%s&squot; didn&squot;t exit with status 0&bslash;n&quot;
comma
id|argv
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|err
op_assign
id|EINVAL
suffix:semicolon
)brace
)brace
r_return
id|err
suffix:semicolon
)brace
DECL|function|slip_open
r_static
r_int
id|slip_open
c_func
(paren
r_void
op_star
id|data
)paren
(brace
r_struct
id|slip_data
op_star
id|pri
op_assign
id|data
suffix:semicolon
r_char
id|version_buf
(braket
r_sizeof
(paren
l_string|&quot;nnnnn&bslash;0&quot;
)paren
)braket
suffix:semicolon
r_char
id|gate_buf
(braket
r_sizeof
(paren
l_string|&quot;nnn.nnn.nnn.nnn&bslash;0&quot;
)paren
)braket
suffix:semicolon
r_char
op_star
id|argv
(braket
)braket
op_assign
(brace
l_string|&quot;uml_net&quot;
comma
id|version_buf
comma
l_string|&quot;slip&quot;
comma
l_string|&quot;up&quot;
comma
id|gate_buf
comma
l_int|NULL
)brace
suffix:semicolon
r_int
id|sfd
comma
id|mfd
comma
id|disc
comma
id|sencap
comma
id|err
suffix:semicolon
r_if
c_cond
(paren
(paren
id|mfd
op_assign
id|get_pty
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
l_string|&quot;umn : Failed to open pty&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|sfd
op_assign
id|os_open_file
c_func
(paren
id|ptsname
c_func
(paren
id|mfd
)paren
comma
id|of_rdwr
c_func
(paren
id|OPENFLAGS
c_func
(paren
)paren
)paren
comma
l_int|0
)paren
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Couldn&squot;t open tty for slip line&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|set_up_tty
c_func
(paren
id|sfd
)paren
)paren
(brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|pri-&gt;slave
op_assign
id|sfd
suffix:semicolon
id|pri-&gt;pos
op_assign
l_int|0
suffix:semicolon
id|pri-&gt;esc
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|pri-&gt;gate_addr
op_ne
l_int|NULL
)paren
(brace
id|sprintf
c_func
(paren
id|version_buf
comma
l_string|&quot;%d&quot;
comma
id|UML_NET_VERSION
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|gate_buf
comma
id|pri-&gt;gate_addr
)paren
suffix:semicolon
id|err
op_assign
id|slip_tramp
c_func
(paren
id|argv
comma
id|sfd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;slip_tramp failed - errno = %d&bslash;n&quot;
comma
id|err
)paren
suffix:semicolon
r_return
op_minus
id|err
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ioctl
c_func
(paren
id|pri-&gt;slave
comma
id|SIOCGIFNAME
comma
id|pri-&gt;name
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;SIOCGIFNAME failed, errno = %d&bslash;n&quot;
comma
id|errno
)paren
suffix:semicolon
r_return
op_minus
id|errno
suffix:semicolon
)brace
id|iter_addresses
c_func
(paren
id|pri-&gt;dev
comma
id|open_addr
comma
id|pri-&gt;name
)paren
suffix:semicolon
)brace
r_else
(brace
id|disc
op_assign
id|N_SLIP
suffix:semicolon
r_if
c_cond
(paren
id|ioctl
c_func
(paren
id|sfd
comma
id|TIOCSETD
comma
op_amp
id|disc
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Failed to set slip line discipline - &quot;
l_string|&quot;errno = %d&bslash;n&quot;
comma
id|errno
)paren
suffix:semicolon
r_return
op_minus
id|errno
suffix:semicolon
)brace
id|sencap
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|ioctl
c_func
(paren
id|sfd
comma
id|SIOCSIFENCAP
comma
op_amp
id|sencap
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Failed to sett slip encapsulation - &quot;
l_string|&quot;errno = %d&bslash;n&quot;
comma
id|errno
)paren
suffix:semicolon
r_return
op_minus
id|errno
suffix:semicolon
)brace
)brace
r_return
id|mfd
suffix:semicolon
)brace
DECL|function|slip_close
r_static
r_void
id|slip_close
c_func
(paren
r_int
id|fd
comma
r_void
op_star
id|data
)paren
(brace
r_struct
id|slip_data
op_star
id|pri
op_assign
id|data
suffix:semicolon
r_char
id|version_buf
(braket
r_sizeof
(paren
l_string|&quot;nnnnn&bslash;0&quot;
)paren
)braket
suffix:semicolon
r_char
op_star
id|argv
(braket
)braket
op_assign
(brace
l_string|&quot;uml_net&quot;
comma
id|version_buf
comma
l_string|&quot;slip&quot;
comma
l_string|&quot;down&quot;
comma
id|pri-&gt;name
comma
l_int|NULL
)brace
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
id|pri-&gt;gate_addr
op_ne
l_int|NULL
)paren
(brace
id|iter_addresses
c_func
(paren
id|pri-&gt;dev
comma
id|close_addr
comma
id|pri-&gt;name
)paren
suffix:semicolon
)brace
id|sprintf
c_func
(paren
id|version_buf
comma
l_string|&quot;%d&quot;
comma
id|UML_NET_VERSION
)paren
suffix:semicolon
id|err
op_assign
id|slip_tramp
c_func
(paren
id|argv
comma
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;slip_tramp failed - errno = %d&bslash;n&quot;
comma
id|err
)paren
suffix:semicolon
)brace
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
id|close
c_func
(paren
id|pri-&gt;slave
)paren
suffix:semicolon
id|pri-&gt;slave
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* SLIP protocol characters. */
DECL|macro|END
mdefine_line|#define END             0300&t;&t;/* indicates end of frame&t;*/
DECL|macro|ESC
mdefine_line|#define ESC             0333&t;&t;/* indicates byte stuffing&t;*/
DECL|macro|ESC_END
mdefine_line|#define ESC_END         0334&t;&t;/* ESC ESC_END means END &squot;data&squot;&t;*/
DECL|macro|ESC_ESC
mdefine_line|#define ESC_ESC         0335&t;&t;/* ESC ESC_ESC means ESC &squot;data&squot;&t;*/
DECL|function|slip_unesc
r_static
r_int
id|slip_unesc
c_func
(paren
r_struct
id|slip_data
op_star
id|sl
comma
r_int
r_char
id|c
)paren
(brace
r_int
id|ret
suffix:semicolon
r_switch
c_cond
(paren
id|c
)paren
(brace
r_case
id|END
suffix:colon
id|sl-&gt;esc
op_assign
l_int|0
suffix:semicolon
id|ret
op_assign
id|sl-&gt;pos
suffix:semicolon
id|sl-&gt;pos
op_assign
l_int|0
suffix:semicolon
r_return
id|ret
suffix:semicolon
r_case
id|ESC
suffix:colon
id|sl-&gt;esc
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|ESC_ESC
suffix:colon
r_if
c_cond
(paren
id|sl-&gt;esc
)paren
(brace
id|sl-&gt;esc
op_assign
l_int|0
suffix:semicolon
id|c
op_assign
id|ESC
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|ESC_END
suffix:colon
r_if
c_cond
(paren
id|sl-&gt;esc
)paren
(brace
id|sl-&gt;esc
op_assign
l_int|0
suffix:semicolon
id|c
op_assign
id|END
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
id|sl-&gt;buf
(braket
id|sl-&gt;pos
op_increment
)braket
op_assign
id|c
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|slip_user_read
r_int
id|slip_user_read
c_func
(paren
r_int
id|fd
comma
r_void
op_star
id|buf
comma
r_int
id|len
comma
r_struct
id|slip_data
op_star
id|pri
)paren
(brace
r_int
id|i
comma
id|n
comma
id|size
comma
id|start
suffix:semicolon
id|n
op_assign
id|net_read
c_func
(paren
id|fd
comma
op_amp
id|pri-&gt;buf
(braket
id|pri-&gt;pos
)braket
comma
r_sizeof
(paren
id|pri-&gt;buf
)paren
op_minus
id|pri-&gt;pos
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n
op_le
l_int|0
)paren
(brace
r_return
id|n
suffix:semicolon
)brace
id|start
op_assign
id|pri-&gt;pos
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
id|n
suffix:semicolon
id|i
op_increment
)paren
(brace
id|size
op_assign
id|slip_unesc
c_func
(paren
id|pri
comma
id|pri-&gt;buf
(braket
id|start
op_plus
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|size
)paren
(brace
id|memcpy
c_func
(paren
id|buf
comma
id|pri-&gt;buf
comma
id|size
)paren
suffix:semicolon
r_return
id|size
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|slip_esc
r_static
r_int
id|slip_esc
c_func
(paren
r_int
r_char
op_star
id|s
comma
r_int
r_char
op_star
id|d
comma
r_int
id|len
)paren
(brace
r_int
r_char
op_star
id|ptr
op_assign
id|d
suffix:semicolon
r_int
r_char
id|c
suffix:semicolon
multiline_comment|/*&n;&t; * Send an initial END character to flush out any&n;&t; * data that may have accumulated in the receiver&n;&t; * due to line noise.&n;&t; */
op_star
id|ptr
op_increment
op_assign
id|END
suffix:semicolon
multiline_comment|/*&n;&t; * For each byte in the packet, send the appropriate&n;&t; * character sequence, according to the SLIP protocol.&n;&t; */
r_while
c_loop
(paren
id|len
op_decrement
OG
l_int|0
)paren
(brace
r_switch
c_cond
(paren
id|c
op_assign
op_star
id|s
op_increment
)paren
(brace
r_case
id|END
suffix:colon
op_star
id|ptr
op_increment
op_assign
id|ESC
suffix:semicolon
op_star
id|ptr
op_increment
op_assign
id|ESC_END
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ESC
suffix:colon
op_star
id|ptr
op_increment
op_assign
id|ESC
suffix:semicolon
op_star
id|ptr
op_increment
op_assign
id|ESC_ESC
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
op_star
id|ptr
op_increment
op_assign
id|c
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
op_star
id|ptr
op_increment
op_assign
id|END
suffix:semicolon
r_return
(paren
id|ptr
op_minus
id|d
)paren
suffix:semicolon
)brace
DECL|function|slip_user_write
r_int
id|slip_user_write
c_func
(paren
r_int
id|fd
comma
r_void
op_star
id|buf
comma
r_int
id|len
comma
r_struct
id|slip_data
op_star
id|pri
)paren
(brace
r_int
id|actual
comma
id|n
suffix:semicolon
id|actual
op_assign
id|slip_esc
c_func
(paren
id|buf
comma
id|pri-&gt;buf
comma
id|len
)paren
suffix:semicolon
id|n
op_assign
id|net_write
c_func
(paren
id|fd
comma
id|pri-&gt;buf
comma
id|actual
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
id|n
suffix:semicolon
)brace
r_else
r_return
id|len
suffix:semicolon
)brace
DECL|function|slip_set_mtu
r_static
r_int
id|slip_set_mtu
c_func
(paren
r_int
id|mtu
comma
r_void
op_star
id|data
)paren
(brace
r_return
id|mtu
suffix:semicolon
)brace
DECL|function|slip_add_addr
r_static
r_void
id|slip_add_addr
c_func
(paren
r_int
r_char
op_star
id|addr
comma
r_int
r_char
op_star
id|netmask
comma
r_void
op_star
id|data
)paren
(brace
r_struct
id|slip_data
op_star
id|pri
op_assign
id|data
suffix:semicolon
r_if
c_cond
(paren
id|pri-&gt;slave
op_eq
op_minus
l_int|1
)paren
(brace
r_return
suffix:semicolon
)brace
id|open_addr
c_func
(paren
id|addr
comma
id|netmask
comma
id|pri-&gt;name
)paren
suffix:semicolon
)brace
DECL|function|slip_del_addr
r_static
r_void
id|slip_del_addr
c_func
(paren
r_int
r_char
op_star
id|addr
comma
r_int
r_char
op_star
id|netmask
comma
r_void
op_star
id|data
)paren
(brace
r_struct
id|slip_data
op_star
id|pri
op_assign
id|data
suffix:semicolon
r_if
c_cond
(paren
id|pri-&gt;slave
op_eq
op_minus
l_int|1
)paren
(brace
r_return
suffix:semicolon
)brace
id|close_addr
c_func
(paren
id|addr
comma
id|netmask
comma
id|pri-&gt;name
)paren
suffix:semicolon
)brace
DECL|variable|slip_user_info
r_struct
id|net_user_info
id|slip_user_info
op_assign
(brace
id|init
suffix:colon
id|slip_user_init
comma
id|open
suffix:colon
id|slip_open
comma
id|close
suffix:colon
id|slip_close
comma
id|remove
suffix:colon
l_int|NULL
comma
id|set_mtu
suffix:colon
id|slip_set_mtu
comma
id|add_address
suffix:colon
id|slip_add_addr
comma
id|delete_address
suffix:colon
id|slip_del_addr
comma
id|max_packet
suffix:colon
id|BUF_SIZE
)brace
suffix:semicolon
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
