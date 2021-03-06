macro_line|#include &quot;linux/kernel.h&quot;
macro_line|#include &quot;linux/stddef.h&quot;
macro_line|#include &quot;linux/init.h&quot;
macro_line|#include &quot;linux/netdevice.h&quot;
macro_line|#include &quot;linux/if_arp.h&quot;
macro_line|#include &quot;net_kern.h&quot;
macro_line|#include &quot;net_user.h&quot;
macro_line|#include &quot;kern.h&quot;
macro_line|#include &quot;slirp.h&quot;
DECL|struct|slirp_init
r_struct
id|slirp_init
(brace
DECL|member|argw
r_struct
id|arg_list_dummy_wrapper
id|argw
suffix:semicolon
multiline_comment|/* XXX should be simpler... */
)brace
suffix:semicolon
DECL|function|slirp_init
r_void
id|slirp_init
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_void
op_star
id|data
)paren
(brace
r_struct
id|uml_net_private
op_star
r_private
suffix:semicolon
r_struct
id|slirp_data
op_star
id|spri
suffix:semicolon
r_struct
id|slirp_init
op_star
id|init
op_assign
id|data
suffix:semicolon
r_int
id|i
suffix:semicolon
r_private
op_assign
id|dev-&gt;priv
suffix:semicolon
id|spri
op_assign
(paren
r_struct
id|slirp_data
op_star
)paren
r_private
op_member_access_from_pointer
id|user
suffix:semicolon
op_star
id|spri
op_assign
(paren
(paren
r_struct
id|slirp_data
)paren
(brace
dot
id|argw
op_assign
id|init-&gt;argw
comma
dot
id|pid
op_assign
op_minus
l_int|1
comma
dot
id|slave
op_assign
op_minus
l_int|1
comma
dot
id|ibuf
op_assign
(brace
l_char|&squot;&bslash;0&squot;
)brace
comma
dot
id|obuf
op_assign
(brace
l_char|&squot;&bslash;0&squot;
)brace
comma
dot
id|pos
op_assign
l_int|0
comma
dot
id|esc
op_assign
l_int|0
comma
dot
id|dev
op_assign
id|dev
)brace
)paren
suffix:semicolon
id|dev-&gt;init
op_assign
l_int|NULL
suffix:semicolon
id|dev-&gt;hard_header_len
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;header_cache_update
op_assign
l_int|NULL
suffix:semicolon
id|dev-&gt;hard_header_cache
op_assign
l_int|NULL
suffix:semicolon
id|dev-&gt;hard_header
op_assign
l_int|NULL
suffix:semicolon
id|dev-&gt;addr_len
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;type
op_assign
id|ARPHRD_SLIP
suffix:semicolon
id|dev-&gt;tx_queue_len
op_assign
l_int|256
suffix:semicolon
id|dev-&gt;flags
op_assign
id|IFF_NOARP
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;SLIRP backend - command line:&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|spri-&gt;argw.argv
(braket
id|i
)braket
op_ne
l_int|NULL
suffix:semicolon
id|i
op_increment
)paren
(brace
id|printk
c_func
(paren
l_string|&quot; &squot;%s&squot;&quot;
comma
id|spri-&gt;argw.argv
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|slirp_protocol
r_static
r_int
r_int
id|slirp_protocol
c_func
(paren
r_struct
id|sk_buff
op_star
id|skbuff
)paren
(brace
r_return
id|htons
c_func
(paren
id|ETH_P_IP
)paren
suffix:semicolon
)brace
DECL|function|slirp_read
r_static
r_int
id|slirp_read
c_func
(paren
r_int
id|fd
comma
r_struct
id|sk_buff
op_star
op_star
id|skb
comma
r_struct
id|uml_net_private
op_star
id|lp
)paren
(brace
r_return
id|slirp_user_read
c_func
(paren
id|fd
comma
(paren
op_star
id|skb
)paren
op_member_access_from_pointer
id|mac.raw
comma
(paren
op_star
id|skb
)paren
op_member_access_from_pointer
id|dev-&gt;mtu
comma
(paren
r_struct
id|slirp_data
op_star
)paren
op_amp
id|lp-&gt;user
)paren
suffix:semicolon
)brace
DECL|function|slirp_write
r_static
r_int
id|slirp_write
c_func
(paren
r_int
id|fd
comma
r_struct
id|sk_buff
op_star
op_star
id|skb
comma
r_struct
id|uml_net_private
op_star
id|lp
)paren
(brace
r_return
id|slirp_user_write
c_func
(paren
id|fd
comma
(paren
op_star
id|skb
)paren
op_member_access_from_pointer
id|data
comma
(paren
op_star
id|skb
)paren
op_member_access_from_pointer
id|len
comma
(paren
r_struct
id|slirp_data
op_star
)paren
op_amp
id|lp-&gt;user
)paren
suffix:semicolon
)brace
DECL|variable|slirp_kern_info
r_struct
id|net_kern_info
id|slirp_kern_info
op_assign
(brace
dot
id|init
op_assign
id|slirp_init
comma
dot
id|protocol
op_assign
id|slirp_protocol
comma
dot
id|read
op_assign
id|slirp_read
comma
dot
id|write
op_assign
id|slirp_write
comma
)brace
suffix:semicolon
DECL|function|slirp_setup
r_static
r_int
id|slirp_setup
c_func
(paren
r_char
op_star
id|str
comma
r_char
op_star
op_star
id|mac_out
comma
r_void
op_star
id|data
)paren
(brace
r_struct
id|slirp_init
op_star
id|init
op_assign
id|data
suffix:semicolon
r_int
id|i
op_assign
l_int|0
suffix:semicolon
op_star
id|init
op_assign
(paren
(paren
r_struct
id|slirp_init
)paren
(brace
id|argw
suffix:colon
(brace
(brace
l_string|&quot;slirp&quot;
comma
l_int|NULL
)brace
)brace
)brace
)paren
suffix:semicolon
id|str
op_assign
id|split_if_spec
c_func
(paren
id|str
comma
id|mac_out
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|str
op_eq
l_int|NULL
)paren
(brace
multiline_comment|/* no command line given after MAC addr */
r_return
l_int|1
suffix:semicolon
)brace
r_do
(brace
r_if
c_cond
(paren
id|i
op_ge
id|SLIRP_MAX_ARGS
op_minus
l_int|1
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;slirp_setup: truncating slirp arguments&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|init-&gt;argw.argv
(braket
id|i
op_increment
)braket
op_assign
id|str
suffix:semicolon
r_while
c_loop
(paren
op_star
id|str
op_logical_and
op_star
id|str
op_ne
l_char|&squot;,&squot;
)paren
(brace
r_if
c_cond
(paren
op_star
id|str
op_eq
l_char|&squot;_&squot;
)paren
(brace
op_star
id|str
op_assign
l_char|&squot; &squot;
suffix:semicolon
)brace
id|str
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
op_star
id|str
op_ne
l_char|&squot;,&squot;
)paren
(brace
r_break
suffix:semicolon
)brace
op_star
id|str
op_increment
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
)brace
r_while
c_loop
(paren
l_int|1
)paren
(brace
suffix:semicolon
)brace
id|init-&gt;argw.argv
(braket
id|i
)braket
op_assign
l_int|NULL
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|variable|slirp_transport
r_static
r_struct
id|transport
id|slirp_transport
op_assign
(brace
dot
id|list
op_assign
id|LIST_HEAD_INIT
c_func
(paren
id|slirp_transport.list
)paren
comma
dot
id|name
op_assign
l_string|&quot;slirp&quot;
comma
dot
id|setup
op_assign
id|slirp_setup
comma
dot
id|user
op_assign
op_amp
id|slirp_user_info
comma
dot
id|kern
op_assign
op_amp
id|slirp_kern_info
comma
dot
id|private_size
op_assign
r_sizeof
(paren
r_struct
id|slirp_data
)paren
comma
dot
id|setup_size
op_assign
r_sizeof
(paren
r_struct
id|slirp_init
)paren
comma
)brace
suffix:semicolon
DECL|function|register_slirp
r_static
r_int
id|register_slirp
c_func
(paren
r_void
)paren
(brace
id|register_transport
c_func
(paren
op_amp
id|slirp_transport
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|variable|register_slirp
id|__initcall
c_func
(paren
id|register_slirp
)paren
suffix:semicolon
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
