multiline_comment|/*&n; * user-mode-linux networking multicast transport&n; * Copyright (C) 2001 by Harald Welte &lt;laforge@gnumonks.org&gt;&n; *&n; * based on the existing uml-networking code, which is&n; * Copyright (C) 2001 Lennert Buytenhek (buytenh@gnu.org) and &n; * James Leu (jleu@mindspring.net).&n; * Copyright (C) 2001 by various other people who didn&squot;t put their name here.&n; *&n; * Licensed under the GPL.&n; *&n; */
macro_line|#include &lt;errno.h&gt;
macro_line|#include &lt;unistd.h&gt;
macro_line|#include &lt;linux/inet.h&gt;
macro_line|#include &lt;sys/socket.h&gt;
macro_line|#include &lt;sys/un.h&gt;
macro_line|#include &lt;sys/time.h&gt;
macro_line|#include &lt;netinet/in.h&gt;
macro_line|#include &quot;net_user.h&quot;
macro_line|#include &quot;mcast.h&quot;
macro_line|#include &quot;kern_util.h&quot;
macro_line|#include &quot;user_util.h&quot;
macro_line|#include &quot;user.h&quot;
DECL|macro|MAX_PACKET
mdefine_line|#define MAX_PACKET (ETH_MAX_PACKET + ETH_HEADER_OTHER)
DECL|function|new_addr
r_static
r_struct
id|sockaddr_in
op_star
id|new_addr
c_func
(paren
r_char
op_star
id|addr
comma
r_int
r_int
id|port
)paren
(brace
r_struct
id|sockaddr_in
op_star
id|sin
suffix:semicolon
id|sin
op_assign
id|um_kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|sockaddr_in
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sin
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;new_addr: allocation of sockaddr_in failed&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|sin-&gt;sin_family
op_assign
id|AF_INET
suffix:semicolon
id|sin-&gt;sin_addr.s_addr
op_assign
id|in_aton
c_func
(paren
id|addr
)paren
suffix:semicolon
id|sin-&gt;sin_port
op_assign
id|port
suffix:semicolon
r_return
id|sin
suffix:semicolon
)brace
DECL|function|mcast_user_init
r_static
r_void
id|mcast_user_init
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
id|mcast_data
op_star
id|pri
op_assign
id|data
suffix:semicolon
id|pri-&gt;mcast_addr
op_assign
id|new_addr
c_func
(paren
id|pri-&gt;addr
comma
id|pri-&gt;port
)paren
suffix:semicolon
id|pri-&gt;dev
op_assign
id|dev
suffix:semicolon
)brace
DECL|function|mcast_open
r_static
r_int
id|mcast_open
c_func
(paren
r_void
op_star
id|data
)paren
(brace
r_struct
id|mcast_data
op_star
id|pri
op_assign
id|data
suffix:semicolon
r_struct
id|sockaddr_in
op_star
id|sin
op_assign
id|pri-&gt;mcast_addr
suffix:semicolon
r_struct
id|ip_mreq
id|mreq
suffix:semicolon
r_int
id|fd
comma
id|yes
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
(paren
id|sin-&gt;sin_addr.s_addr
op_eq
l_int|0
)paren
op_logical_or
(paren
id|sin-&gt;sin_port
op_eq
l_int|0
)paren
)paren
(brace
id|fd
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|fd
op_assign
id|socket
c_func
(paren
id|AF_INET
comma
id|SOCK_DGRAM
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
l_string|&quot;mcast_open : data socket failed, errno = %d&bslash;n&quot;
comma
id|errno
)paren
suffix:semicolon
id|fd
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
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
id|yes
comma
r_sizeof
(paren
id|yes
)paren
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;mcast_open: SO_REUSEADDR failed, errno = %d&bslash;n&quot;
comma
id|errno
)paren
suffix:semicolon
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
id|fd
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/* set ttl according to config */
r_if
c_cond
(paren
id|setsockopt
c_func
(paren
id|fd
comma
id|SOL_IP
comma
id|IP_MULTICAST_TTL
comma
op_amp
id|pri-&gt;ttl
comma
r_sizeof
(paren
id|pri-&gt;ttl
)paren
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;mcast_open: IP_MULTICAST_TTL failed, error = %d&bslash;n&quot;
comma
id|errno
)paren
suffix:semicolon
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
id|fd
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/* set LOOP, so data does get fed back to local sockets */
r_if
c_cond
(paren
id|setsockopt
c_func
(paren
id|fd
comma
id|SOL_IP
comma
id|IP_MULTICAST_LOOP
comma
op_amp
id|yes
comma
r_sizeof
(paren
id|yes
)paren
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;mcast_open: IP_MULTICAST_LOOP failed, error = %d&bslash;n&quot;
comma
id|errno
)paren
suffix:semicolon
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
id|fd
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/* bind socket to mcast address */
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
id|sin
comma
r_sizeof
(paren
op_star
id|sin
)paren
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;mcast_open : data bind failed, errno = %d&bslash;n&quot;
comma
id|errno
)paren
suffix:semicolon
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
id|fd
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/* subscribe to the multicast group */
id|mreq.imr_multiaddr.s_addr
op_assign
id|sin-&gt;sin_addr.s_addr
suffix:semicolon
id|mreq.imr_interface.s_addr
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|setsockopt
c_func
(paren
id|fd
comma
id|SOL_IP
comma
id|IP_ADD_MEMBERSHIP
comma
op_amp
id|mreq
comma
r_sizeof
(paren
id|mreq
)paren
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;mcast_open: IP_ADD_MEMBERSHIP failed, error = %d&bslash;n&quot;
comma
id|errno
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;There appears not to be a multicast-capable network &quot;
l_string|&quot;interface on the host.&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;eth0 should be configured in order to use the &quot;
l_string|&quot;multicast transport.&bslash;n&quot;
)paren
suffix:semicolon
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
id|fd
op_assign
op_minus
id|EINVAL
suffix:semicolon
)brace
id|out
suffix:colon
r_return
id|fd
suffix:semicolon
)brace
DECL|function|mcast_close
r_static
r_void
id|mcast_close
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
id|ip_mreq
id|mreq
suffix:semicolon
r_struct
id|mcast_data
op_star
id|pri
op_assign
id|data
suffix:semicolon
r_struct
id|sockaddr_in
op_star
id|sin
op_assign
id|pri-&gt;mcast_addr
suffix:semicolon
id|mreq.imr_multiaddr.s_addr
op_assign
id|sin-&gt;sin_addr.s_addr
suffix:semicolon
id|mreq.imr_interface.s_addr
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|setsockopt
c_func
(paren
id|fd
comma
id|SOL_IP
comma
id|IP_DROP_MEMBERSHIP
comma
op_amp
id|mreq
comma
r_sizeof
(paren
id|mreq
)paren
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;mcast_open: IP_DROP_MEMBERSHIP failed, error = %d&bslash;n&quot;
comma
id|errno
)paren
suffix:semicolon
)brace
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
)brace
DECL|function|mcast_user_write
r_int
id|mcast_user_write
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
id|mcast_data
op_star
id|pri
)paren
(brace
r_struct
id|sockaddr_in
op_star
id|data_addr
op_assign
id|pri-&gt;mcast_addr
suffix:semicolon
r_return
id|net_sendto
c_func
(paren
id|fd
comma
id|buf
comma
id|len
comma
id|data_addr
comma
r_sizeof
(paren
op_star
id|data_addr
)paren
)paren
suffix:semicolon
)brace
DECL|function|mcast_set_mtu
r_static
r_int
id|mcast_set_mtu
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
DECL|variable|mcast_user_info
r_struct
id|net_user_info
id|mcast_user_info
op_assign
(brace
id|init
suffix:colon
id|mcast_user_init
comma
id|open
suffix:colon
id|mcast_open
comma
id|close
suffix:colon
id|mcast_close
comma
id|remove
suffix:colon
l_int|NULL
comma
id|set_mtu
suffix:colon
id|mcast_set_mtu
comma
id|add_address
suffix:colon
l_int|NULL
comma
id|delete_address
suffix:colon
l_int|NULL
comma
id|max_packet
suffix:colon
id|MAX_PACKET
op_minus
id|ETH_HEADER_OTHER
)brace
suffix:semicolon
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
