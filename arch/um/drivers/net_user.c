multiline_comment|/* &n; * Copyright (C) 2001, 2002 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#include &lt;stddef.h&gt;
macro_line|#include &lt;stdarg.h&gt;
macro_line|#include &lt;unistd.h&gt;
macro_line|#include &lt;stdio.h&gt;
macro_line|#include &lt;errno.h&gt;
macro_line|#include &lt;stdlib.h&gt;
macro_line|#include &lt;string.h&gt;
macro_line|#include &lt;sys/socket.h&gt;
macro_line|#include &lt;sys/wait.h&gt;
macro_line|#include &quot;user.h&quot;
macro_line|#include &quot;user_util.h&quot;
macro_line|#include &quot;kern_util.h&quot;
macro_line|#include &quot;net_user.h&quot;
macro_line|#include &quot;helper.h&quot;
macro_line|#include &quot;os.h&quot;
DECL|function|tap_open_common
r_int
id|tap_open_common
c_func
(paren
r_void
op_star
id|dev
comma
r_char
op_star
id|gate_addr
)paren
(brace
r_int
id|tap_addr
(braket
l_int|4
)braket
suffix:semicolon
r_if
c_cond
(paren
id|gate_addr
op_eq
l_int|NULL
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sscanf
c_func
(paren
id|gate_addr
comma
l_string|&quot;%d.%d.%d.%d&quot;
comma
op_amp
id|tap_addr
(braket
l_int|0
)braket
comma
op_amp
id|tap_addr
(braket
l_int|1
)braket
comma
op_amp
id|tap_addr
(braket
l_int|2
)braket
comma
op_amp
id|tap_addr
(braket
l_int|3
)braket
)paren
op_ne
l_int|4
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Invalid tap IP address - &squot;%s&squot;&bslash;n&quot;
comma
id|gate_addr
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|tap_check_ips
r_void
id|tap_check_ips
c_func
(paren
r_char
op_star
id|gate_addr
comma
r_char
op_star
id|eth_addr
)paren
(brace
r_int
id|tap_addr
(braket
l_int|4
)braket
suffix:semicolon
r_if
c_cond
(paren
(paren
id|gate_addr
op_ne
l_int|NULL
)paren
op_logical_and
(paren
id|sscanf
c_func
(paren
id|gate_addr
comma
l_string|&quot;%d.%d.%d.%d&quot;
comma
op_amp
id|tap_addr
(braket
l_int|0
)braket
comma
op_amp
id|tap_addr
(braket
l_int|1
)braket
comma
op_amp
id|tap_addr
(braket
l_int|2
)braket
comma
op_amp
id|tap_addr
(braket
l_int|3
)braket
)paren
op_eq
l_int|4
)paren
op_logical_and
(paren
id|eth_addr
(braket
l_int|0
)braket
op_eq
id|tap_addr
(braket
l_int|0
)braket
)paren
op_logical_and
(paren
id|eth_addr
(braket
l_int|1
)braket
op_eq
id|tap_addr
(braket
l_int|1
)braket
)paren
op_logical_and
(paren
id|eth_addr
(braket
l_int|2
)braket
op_eq
id|tap_addr
(braket
l_int|2
)braket
)paren
op_logical_and
(paren
id|eth_addr
(braket
l_int|3
)braket
op_eq
id|tap_addr
(braket
l_int|3
)braket
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;The tap IP address and the UML eth IP address&quot;
l_string|&quot; must be different&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
DECL|function|read_output
r_void
id|read_output
c_func
(paren
r_int
id|fd
comma
r_char
op_star
id|output
comma
r_int
id|len
)paren
(brace
r_int
id|remain
comma
id|n
comma
id|actual
suffix:semicolon
r_char
id|c
suffix:semicolon
r_if
c_cond
(paren
id|output
op_eq
l_int|NULL
)paren
(brace
id|output
op_assign
op_amp
id|c
suffix:semicolon
id|len
op_assign
r_sizeof
(paren
id|c
)paren
suffix:semicolon
)brace
op_star
id|output
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|n
op_assign
id|os_read_file
c_func
(paren
id|fd
comma
op_amp
id|remain
comma
r_sizeof
(paren
id|remain
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
id|remain
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;read_output - read of length failed, err = %d&bslash;n&quot;
comma
op_minus
id|n
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_while
c_loop
(paren
id|remain
op_ne
l_int|0
)paren
(brace
id|n
op_assign
(paren
id|remain
OL
id|len
)paren
ques
c_cond
id|remain
suffix:colon
id|len
suffix:semicolon
id|actual
op_assign
id|os_read_file
c_func
(paren
id|fd
comma
id|output
comma
id|n
)paren
suffix:semicolon
r_if
c_cond
(paren
id|actual
op_ne
id|n
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;read_output - read of data failed, &quot;
l_string|&quot;err = %d&bslash;n&quot;
comma
op_minus
id|actual
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|remain
op_sub_assign
id|actual
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
DECL|function|net_read
r_int
id|net_read
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
)paren
(brace
r_int
id|n
suffix:semicolon
id|n
op_assign
id|os_read_file
c_func
(paren
id|fd
comma
id|buf
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n
op_eq
op_minus
id|EAGAIN
)paren
(brace
r_return
l_int|0
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
id|ENOTCONN
suffix:semicolon
)brace
r_return
id|n
suffix:semicolon
)brace
DECL|function|net_recvfrom
r_int
id|net_recvfrom
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
)paren
(brace
r_int
id|n
suffix:semicolon
r_while
c_loop
(paren
(paren
(paren
id|n
op_assign
id|recvfrom
c_func
(paren
id|fd
comma
id|buf
comma
id|len
comma
l_int|0
comma
l_int|NULL
comma
l_int|NULL
)paren
)paren
OL
l_int|0
)paren
op_logical_and
(paren
id|errno
op_eq
id|EINTR
)paren
)paren
(brace
suffix:semicolon
)brace
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
id|ENOTCONN
suffix:semicolon
)brace
r_return
id|n
suffix:semicolon
)brace
DECL|function|net_write
r_int
id|net_write
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
)paren
(brace
r_int
id|n
suffix:semicolon
id|n
op_assign
id|os_write_file
c_func
(paren
id|fd
comma
id|buf
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n
op_eq
op_minus
id|EAGAIN
)paren
(brace
r_return
l_int|0
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
id|ENOTCONN
suffix:semicolon
)brace
r_return
id|n
suffix:semicolon
)brace
DECL|function|net_send
r_int
id|net_send
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
)paren
(brace
r_int
id|n
suffix:semicolon
r_while
c_loop
(paren
(paren
(paren
id|n
op_assign
id|send
c_func
(paren
id|fd
comma
id|buf
comma
id|len
comma
l_int|0
)paren
)paren
OL
l_int|0
)paren
op_logical_and
(paren
id|errno
op_eq
id|EINTR
)paren
)paren
(brace
suffix:semicolon
)brace
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
id|ENOTCONN
suffix:semicolon
)brace
r_return
id|n
suffix:semicolon
)brace
DECL|function|net_sendto
r_int
id|net_sendto
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
r_void
op_star
id|to
comma
r_int
id|sock_len
)paren
(brace
r_int
id|n
suffix:semicolon
r_while
c_loop
(paren
(paren
(paren
id|n
op_assign
id|sendto
c_func
(paren
id|fd
comma
id|buf
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
id|to
comma
id|sock_len
)paren
)paren
OL
l_int|0
)paren
op_logical_and
(paren
id|errno
op_eq
id|EINTR
)paren
)paren
(brace
suffix:semicolon
)brace
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
id|ENOTCONN
suffix:semicolon
)brace
r_return
id|n
suffix:semicolon
)brace
DECL|struct|change_pre_exec_data
r_struct
id|change_pre_exec_data
(brace
DECL|member|close_me
r_int
id|close_me
suffix:semicolon
DECL|member|stdout
r_int
id|stdout
suffix:semicolon
)brace
suffix:semicolon
DECL|function|change_pre_exec
r_static
r_void
id|change_pre_exec
c_func
(paren
r_void
op_star
id|arg
)paren
(brace
r_struct
id|change_pre_exec_data
op_star
id|data
op_assign
id|arg
suffix:semicolon
id|os_close_file
c_func
(paren
id|data-&gt;close_me
)paren
suffix:semicolon
id|dup2
c_func
(paren
id|data-&gt;stdout
comma
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|change_tramp
r_static
r_int
id|change_tramp
c_func
(paren
r_char
op_star
op_star
id|argv
comma
r_char
op_star
id|output
comma
r_int
id|output_len
)paren
(brace
r_int
id|pid
comma
id|fds
(braket
l_int|2
)braket
comma
id|err
suffix:semicolon
r_struct
id|change_pre_exec_data
id|pe_data
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
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;change_tramp - pipe failed, err = %d&bslash;n&quot;
comma
op_minus
id|err
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
id|pe_data.close_me
op_assign
id|fds
(braket
l_int|0
)braket
suffix:semicolon
id|pe_data.stdout
op_assign
id|fds
(braket
l_int|1
)braket
suffix:semicolon
id|pid
op_assign
id|run_helper
c_func
(paren
id|change_pre_exec
comma
op_amp
id|pe_data
comma
id|argv
comma
l_int|NULL
)paren
suffix:semicolon
id|os_close_file
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
id|waitpid
c_func
(paren
id|pid
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
r_return
id|pid
suffix:semicolon
)brace
DECL|function|change
r_static
r_void
id|change
c_func
(paren
r_char
op_star
id|dev
comma
r_char
op_star
id|what
comma
r_int
r_char
op_star
id|addr
comma
r_int
r_char
op_star
id|netmask
)paren
(brace
r_char
id|addr_buf
(braket
r_sizeof
(paren
l_string|&quot;255.255.255.255&bslash;0&quot;
)paren
)braket
suffix:semicolon
r_char
id|netmask_buf
(braket
r_sizeof
(paren
l_string|&quot;255.255.255.255&bslash;0&quot;
)paren
)braket
suffix:semicolon
r_char
id|version
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
id|version
comma
id|what
comma
id|dev
comma
id|addr_buf
comma
id|netmask_buf
comma
l_int|NULL
)brace
suffix:semicolon
r_char
op_star
id|output
suffix:semicolon
r_int
id|output_len
comma
id|pid
suffix:semicolon
id|sprintf
c_func
(paren
id|version
comma
l_string|&quot;%d&quot;
comma
id|UML_NET_VERSION
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|addr_buf
comma
l_string|&quot;%d.%d.%d.%d&quot;
comma
id|addr
(braket
l_int|0
)braket
comma
id|addr
(braket
l_int|1
)braket
comma
id|addr
(braket
l_int|2
)braket
comma
id|addr
(braket
l_int|3
)braket
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|netmask_buf
comma
l_string|&quot;%d.%d.%d.%d&quot;
comma
id|netmask
(braket
l_int|0
)braket
comma
id|netmask
(braket
l_int|1
)braket
comma
id|netmask
(braket
l_int|2
)braket
comma
id|netmask
(braket
l_int|3
)braket
)paren
suffix:semicolon
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
l_string|&quot;change : failed to allocate output buffer&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|pid
op_assign
id|change_tramp
c_func
(paren
id|argv
comma
id|output
comma
id|output_len
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
r_return
suffix:semicolon
)brace
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
)brace
DECL|function|open_addr
r_void
id|open_addr
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
id|arg
)paren
(brace
id|change
c_func
(paren
id|arg
comma
l_string|&quot;add&quot;
comma
id|addr
comma
id|netmask
)paren
suffix:semicolon
)brace
DECL|function|close_addr
r_void
id|close_addr
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
id|arg
)paren
(brace
id|change
c_func
(paren
id|arg
comma
l_string|&quot;del&quot;
comma
id|addr
comma
id|netmask
)paren
suffix:semicolon
)brace
DECL|function|split_if_spec
r_char
op_star
id|split_if_spec
c_func
(paren
r_char
op_star
id|str
comma
dot
dot
dot
)paren
(brace
r_char
op_star
op_star
id|arg
comma
op_star
id|end
suffix:semicolon
id|va_list
id|ap
suffix:semicolon
id|va_start
c_func
(paren
id|ap
comma
id|str
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|arg
op_assign
id|va_arg
c_func
(paren
id|ap
comma
r_char
op_star
op_star
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
op_star
id|str
op_eq
l_char|&squot;&bslash;0&squot;
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
id|end
op_assign
id|strchr
c_func
(paren
id|str
comma
l_char|&squot;,&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|end
op_ne
id|str
)paren
(brace
op_star
id|arg
op_assign
id|str
suffix:semicolon
)brace
r_if
c_cond
(paren
id|end
op_eq
l_int|NULL
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
op_star
id|end
op_increment
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|str
op_assign
id|end
suffix:semicolon
)brace
id|va_end
c_func
(paren
id|ap
)paren
suffix:semicolon
r_return
id|str
suffix:semicolon
)brace
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
