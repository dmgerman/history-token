multiline_comment|/*&n; * Copyright (C) 2001 Lennert Buytenhek (buytenh@gnu.org) and &n; * James Leu (jleu@mindspring.net).&n; * Copyright (C) 2001 by various other people who didn&squot;t put their name here.&n; * Licensed under the GPL.&n; */
macro_line|#include &lt;stdio.h&gt;
macro_line|#include &lt;unistd.h&gt;
macro_line|#include &lt;stddef.h&gt;
macro_line|#include &lt;fcntl.h&gt;
macro_line|#include &lt;stdlib.h&gt;
macro_line|#include &lt;sys/errno.h&gt;
macro_line|#include &lt;sys/socket.h&gt;
macro_line|#include &lt;sys/wait.h&gt;
macro_line|#include &lt;sys/un.h&gt;
macro_line|#include &lt;net/if.h&gt;
macro_line|#include &quot;user.h&quot;
macro_line|#include &quot;kern_util.h&quot;
macro_line|#include &quot;net_user.h&quot;
macro_line|#include &quot;etap.h&quot;
macro_line|#include &quot;helper.h&quot;
macro_line|#include &quot;os.h&quot;
DECL|macro|MAX_PACKET
mdefine_line|#define MAX_PACKET ETH_MAX_PACKET
DECL|function|etap_user_init
r_void
id|etap_user_init
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
id|ethertap_data
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
DECL|struct|addr_change
r_struct
id|addr_change
(brace
DECL|enumerator|ADD_ADDR
DECL|enumerator|DEL_ADDR
DECL|member|what
r_enum
(brace
id|ADD_ADDR
comma
id|DEL_ADDR
)brace
id|what
suffix:semicolon
DECL|member|addr
r_int
r_char
id|addr
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|netmask
r_int
r_char
id|netmask
(braket
l_int|4
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|function|etap_change
r_static
r_void
id|etap_change
c_func
(paren
r_int
id|op
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
comma
r_int
id|fd
)paren
(brace
r_struct
id|addr_change
id|change
suffix:semicolon
r_void
op_star
id|output
suffix:semicolon
id|change.what
op_assign
id|op
suffix:semicolon
id|memcpy
c_func
(paren
id|change.addr
comma
id|addr
comma
r_sizeof
(paren
id|change.addr
)paren
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|change.netmask
comma
id|netmask
comma
r_sizeof
(paren
id|change.netmask
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|write
c_func
(paren
id|fd
comma
op_amp
id|change
comma
r_sizeof
(paren
id|change
)paren
)paren
op_ne
r_sizeof
(paren
id|change
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;etap_change - request failed, errno = %d&bslash;n&quot;
comma
id|errno
)paren
suffix:semicolon
)brace
id|output
op_assign
id|um_kmalloc
c_func
(paren
id|page_size
c_func
(paren
)paren
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
l_string|&quot;etap_change : Failed to allocate output buffer&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|read_output
c_func
(paren
id|fd
comma
id|output
comma
id|page_size
c_func
(paren
)paren
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
)brace
DECL|function|etap_open_addr
r_static
r_void
id|etap_open_addr
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
id|etap_change
c_func
(paren
id|ADD_ADDR
comma
id|addr
comma
id|netmask
comma
op_star
(paren
(paren
r_int
op_star
)paren
id|arg
)paren
)paren
suffix:semicolon
)brace
DECL|function|etap_close_addr
r_static
r_void
id|etap_close_addr
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
id|etap_change
c_func
(paren
id|DEL_ADDR
comma
id|addr
comma
id|netmask
comma
op_star
(paren
(paren
r_int
op_star
)paren
id|arg
)paren
)paren
suffix:semicolon
)brace
DECL|struct|etap_pre_exec_data
r_struct
id|etap_pre_exec_data
(brace
DECL|member|control_remote
r_int
id|control_remote
suffix:semicolon
DECL|member|control_me
r_int
id|control_me
suffix:semicolon
DECL|member|data_me
r_int
id|data_me
suffix:semicolon
)brace
suffix:semicolon
DECL|function|etap_pre_exec
r_static
r_void
id|etap_pre_exec
c_func
(paren
r_void
op_star
id|arg
)paren
(brace
r_struct
id|etap_pre_exec_data
op_star
id|data
op_assign
id|arg
suffix:semicolon
id|dup2
c_func
(paren
id|data-&gt;control_remote
comma
l_int|1
)paren
suffix:semicolon
id|close
c_func
(paren
id|data-&gt;data_me
)paren
suffix:semicolon
id|close
c_func
(paren
id|data-&gt;control_me
)paren
suffix:semicolon
)brace
DECL|function|etap_tramp
r_static
r_int
id|etap_tramp
c_func
(paren
r_char
op_star
id|dev
comma
r_char
op_star
id|gate
comma
r_int
id|control_me
comma
r_int
id|control_remote
comma
r_int
id|data_me
comma
r_int
id|data_remote
)paren
(brace
r_struct
id|etap_pre_exec_data
id|pe_data
suffix:semicolon
r_int
id|pid
comma
id|status
comma
id|err
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
id|data_fd_buf
(braket
r_sizeof
(paren
l_string|&quot;nnnnnn&bslash;0&quot;
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
id|setup_args
(braket
)braket
op_assign
(brace
l_string|&quot;uml_net&quot;
comma
id|version_buf
comma
l_string|&quot;ethertap&quot;
comma
id|dev
comma
id|data_fd_buf
comma
id|gate_buf
comma
l_int|NULL
)brace
suffix:semicolon
r_char
op_star
id|nosetup_args
(braket
)braket
op_assign
(brace
l_string|&quot;uml_net&quot;
comma
id|version_buf
comma
l_string|&quot;ethertap&quot;
comma
id|dev
comma
id|data_fd_buf
comma
l_int|NULL
)brace
suffix:semicolon
r_char
op_star
op_star
id|args
comma
id|c
suffix:semicolon
id|sprintf
c_func
(paren
id|data_fd_buf
comma
l_string|&quot;%d&quot;
comma
id|data_remote
)paren
suffix:semicolon
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
r_if
c_cond
(paren
id|gate
op_ne
l_int|NULL
)paren
(brace
id|strcpy
c_func
(paren
id|gate_buf
comma
id|gate
)paren
suffix:semicolon
id|args
op_assign
id|setup_args
suffix:semicolon
)brace
r_else
id|args
op_assign
id|nosetup_args
suffix:semicolon
id|err
op_assign
l_int|0
suffix:semicolon
id|pe_data.control_remote
op_assign
id|control_remote
suffix:semicolon
id|pe_data.control_me
op_assign
id|control_me
suffix:semicolon
id|pe_data.data_me
op_assign
id|data_me
suffix:semicolon
id|pid
op_assign
id|run_helper
c_func
(paren
id|etap_pre_exec
comma
op_amp
id|pe_data
comma
id|args
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
id|errno
suffix:semicolon
)brace
id|close
c_func
(paren
id|data_remote
)paren
suffix:semicolon
id|close
c_func
(paren
id|control_remote
)paren
suffix:semicolon
r_if
c_cond
(paren
id|read
c_func
(paren
id|control_me
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
l_string|&quot;etap_tramp : read of status failed, errno = %d&bslash;n&quot;
comma
id|errno
)paren
suffix:semicolon
r_return
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|c
op_ne
l_int|1
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;etap_tramp : uml_net failed&bslash;n&quot;
)paren
suffix:semicolon
id|err
op_assign
id|EINVAL
suffix:semicolon
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
l_int|1
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;uml_net didn&squot;t exit with status 1&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
r_return
id|err
suffix:semicolon
)brace
DECL|function|etap_open
r_static
r_int
id|etap_open
c_func
(paren
r_void
op_star
id|data
)paren
(brace
r_struct
id|ethertap_data
op_star
id|pri
op_assign
id|data
suffix:semicolon
r_char
op_star
id|output
suffix:semicolon
r_int
id|data_fds
(braket
l_int|2
)braket
comma
id|control_fds
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
id|tap_open_common
c_func
(paren
id|pri-&gt;dev
comma
id|pri-&gt;gate_addr
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
id|os_pipe
c_func
(paren
id|data_fds
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
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;data os_pipe failed - errno = %d&bslash;n&quot;
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
id|os_pipe
c_func
(paren
id|control_fds
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
l_string|&quot;control os_pipe failed - errno = %d&bslash;n&quot;
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
id|etap_tramp
c_func
(paren
id|pri-&gt;dev_name
comma
id|pri-&gt;gate_addr
comma
id|control_fds
(braket
l_int|0
)braket
comma
id|control_fds
(braket
l_int|1
)braket
comma
id|data_fds
(braket
l_int|0
)braket
comma
id|data_fds
(braket
l_int|1
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
id|read_output
c_func
(paren
id|control_fds
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
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;etap_open : failed to allocate output buffer&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
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
id|err
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;etap_tramp failed - errno = %d&bslash;n&quot;
comma
id|err
)paren
suffix:semicolon
r_return
op_minus
id|err
suffix:semicolon
)brace
id|pri-&gt;data_fd
op_assign
id|data_fds
(braket
l_int|0
)braket
suffix:semicolon
id|pri-&gt;control_fd
op_assign
id|control_fds
(braket
l_int|0
)braket
suffix:semicolon
id|iter_addresses
c_func
(paren
id|pri-&gt;dev
comma
id|etap_open_addr
comma
op_amp
id|pri-&gt;control_fd
)paren
suffix:semicolon
r_return
id|data_fds
(braket
l_int|0
)braket
suffix:semicolon
)brace
DECL|function|etap_close
r_static
r_void
id|etap_close
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
id|ethertap_data
op_star
id|pri
op_assign
id|data
suffix:semicolon
id|iter_addresses
c_func
(paren
id|pri-&gt;dev
comma
id|etap_close_addr
comma
op_amp
id|pri-&gt;control_fd
)paren
suffix:semicolon
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
id|os_shutdown_socket
c_func
(paren
id|pri-&gt;data_fd
comma
l_int|1
comma
l_int|1
)paren
suffix:semicolon
id|close
c_func
(paren
id|pri-&gt;data_fd
)paren
suffix:semicolon
id|pri-&gt;data_fd
op_assign
op_minus
l_int|1
suffix:semicolon
id|close
c_func
(paren
id|pri-&gt;control_fd
)paren
suffix:semicolon
id|pri-&gt;control_fd
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|etap_set_mtu
r_static
r_int
id|etap_set_mtu
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
DECL|function|etap_add_addr
r_static
r_void
id|etap_add_addr
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
id|ethertap_data
op_star
id|pri
op_assign
id|data
suffix:semicolon
id|tap_check_ips
c_func
(paren
id|pri-&gt;gate_addr
comma
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pri-&gt;control_fd
op_eq
op_minus
l_int|1
)paren
(brace
r_return
suffix:semicolon
)brace
id|etap_open_addr
c_func
(paren
id|addr
comma
id|netmask
comma
op_amp
id|pri-&gt;control_fd
)paren
suffix:semicolon
)brace
DECL|function|etap_del_addr
r_static
r_void
id|etap_del_addr
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
id|ethertap_data
op_star
id|pri
op_assign
id|data
suffix:semicolon
r_if
c_cond
(paren
id|pri-&gt;control_fd
op_eq
op_minus
l_int|1
)paren
(brace
r_return
suffix:semicolon
)brace
id|etap_close_addr
c_func
(paren
id|addr
comma
id|netmask
comma
op_amp
id|pri-&gt;control_fd
)paren
suffix:semicolon
)brace
DECL|variable|ethertap_user_info
r_struct
id|net_user_info
id|ethertap_user_info
op_assign
(brace
id|init
suffix:colon
id|etap_user_init
comma
id|open
suffix:colon
id|etap_open
comma
id|close
suffix:colon
id|etap_close
comma
id|remove
suffix:colon
l_int|NULL
comma
id|set_mtu
suffix:colon
id|etap_set_mtu
comma
id|add_address
suffix:colon
id|etap_add_addr
comma
id|delete_address
suffix:colon
id|etap_del_addr
comma
id|max_packet
suffix:colon
id|MAX_PACKET
op_minus
id|ETH_HEADER_ETHERTAP
)brace
suffix:semicolon
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof