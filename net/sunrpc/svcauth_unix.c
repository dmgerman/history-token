macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/sunrpc/types.h&gt;
macro_line|#include &lt;linux/sunrpc/xdr.h&gt;
macro_line|#include &lt;linux/sunrpc/svcsock.h&gt;
macro_line|#include &lt;linux/sunrpc/svcauth.h&gt;
macro_line|#include &lt;linux/err.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;linux/hash.h&gt;
DECL|macro|RPCDBG_FACILITY
mdefine_line|#define RPCDBG_FACILITY&t;RPCDBG_AUTH
multiline_comment|/*&n; * AUTHUNIX and AUTHNULL credentials are both handled here.&n; * AUTHNULL is treated just like AUTHUNIX except that the uid/gid&n; * are always nobody (-2).  i.e. we do the same IP address checks for&n; * AUTHNULL as for AUTHUNIX, and that is done here.&n; */
DECL|function|strdup
r_static
r_char
op_star
id|strdup
c_func
(paren
r_char
op_star
id|s
)paren
(brace
r_char
op_star
id|rv
op_assign
id|kmalloc
c_func
(paren
id|strlen
c_func
(paren
id|s
)paren
op_plus
l_int|1
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rv
)paren
id|strcpy
c_func
(paren
id|rv
comma
id|s
)paren
suffix:semicolon
r_return
id|rv
suffix:semicolon
)brace
DECL|struct|unix_domain
r_struct
id|unix_domain
(brace
DECL|member|h
r_struct
id|auth_domain
id|h
suffix:semicolon
DECL|member|addr_changes
r_int
id|addr_changes
suffix:semicolon
multiline_comment|/* other stuff later */
)brace
suffix:semicolon
DECL|function|unix_domain_find
r_struct
id|auth_domain
op_star
id|unix_domain_find
c_func
(paren
r_char
op_star
id|name
)paren
(brace
r_struct
id|auth_domain
op_star
id|rv
comma
id|ud
suffix:semicolon
r_struct
id|unix_domain
op_star
r_new
suffix:semicolon
id|ud.name
op_assign
id|name
suffix:semicolon
id|rv
op_assign
id|auth_domain_lookup
c_func
(paren
op_amp
id|ud
comma
l_int|0
)paren
suffix:semicolon
id|foundit
suffix:colon
r_if
c_cond
(paren
id|rv
op_logical_and
id|rv-&gt;flavour
op_ne
id|RPC_AUTH_UNIX
)paren
(brace
id|auth_domain_put
c_func
(paren
id|rv
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|rv
)paren
r_return
id|rv
suffix:semicolon
r_new
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
r_new
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
r_new
op_eq
l_int|NULL
)paren
r_return
l_int|NULL
suffix:semicolon
id|cache_init
c_func
(paren
op_amp
r_new
op_member_access_from_pointer
id|h.h
)paren
suffix:semicolon
r_new
op_member_access_from_pointer
id|h.name
op_assign
id|strdup
c_func
(paren
id|name
)paren
suffix:semicolon
r_new
op_member_access_from_pointer
id|h.flavour
op_assign
id|RPC_AUTH_UNIX
suffix:semicolon
r_new
op_member_access_from_pointer
id|addr_changes
op_assign
l_int|0
suffix:semicolon
r_new
op_member_access_from_pointer
id|h.h.expiry_time
op_assign
id|NEVER
suffix:semicolon
id|rv
op_assign
id|auth_domain_lookup
c_func
(paren
op_amp
r_new
op_member_access_from_pointer
id|h
comma
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rv
op_eq
op_amp
r_new
op_member_access_from_pointer
id|h
)paren
(brace
r_if
c_cond
(paren
id|atomic_dec_and_test
c_func
(paren
op_amp
r_new
op_member_access_from_pointer
id|h.h.refcnt
)paren
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|auth_domain_put
c_func
(paren
op_amp
r_new
op_member_access_from_pointer
id|h
)paren
suffix:semicolon
r_goto
id|foundit
suffix:semicolon
)brace
r_return
id|rv
suffix:semicolon
)brace
DECL|function|svcauth_unix_domain_release
r_static
r_void
id|svcauth_unix_domain_release
c_func
(paren
r_struct
id|auth_domain
op_star
id|dom
)paren
(brace
r_struct
id|unix_domain
op_star
id|ud
op_assign
id|container_of
c_func
(paren
id|dom
comma
r_struct
id|unix_domain
comma
id|h
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|dom-&gt;name
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|ud
)paren
suffix:semicolon
)brace
multiline_comment|/**************************************************&n; * cache for IP address to unix_domain&n; * as needed by AUTH_UNIX&n; */
DECL|macro|IP_HASHBITS
mdefine_line|#define&t;IP_HASHBITS&t;8
DECL|macro|IP_HASHMAX
mdefine_line|#define&t;IP_HASHMAX&t;(1&lt;&lt;IP_HASHBITS)
DECL|macro|IP_HASHMASK
mdefine_line|#define&t;IP_HASHMASK&t;(IP_HASHMAX-1)
DECL|struct|ip_map
r_struct
id|ip_map
(brace
DECL|member|h
r_struct
id|cache_head
id|h
suffix:semicolon
DECL|member|m_class
r_char
op_star
id|m_class
suffix:semicolon
multiline_comment|/* e.g. &quot;nfsd&quot; */
DECL|member|m_addr
r_struct
id|in_addr
id|m_addr
suffix:semicolon
DECL|member|m_client
r_struct
id|unix_domain
op_star
id|m_client
suffix:semicolon
DECL|member|m_add_change
r_int
id|m_add_change
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|ip_table
r_static
r_struct
id|cache_head
op_star
id|ip_table
(braket
id|IP_HASHMAX
)braket
suffix:semicolon
DECL|function|ip_map_put
r_void
id|ip_map_put
c_func
(paren
r_struct
id|cache_head
op_star
id|item
comma
r_struct
id|cache_detail
op_star
id|cd
)paren
(brace
r_struct
id|ip_map
op_star
id|im
op_assign
id|container_of
c_func
(paren
id|item
comma
r_struct
id|ip_map
comma
id|h
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cache_put
c_func
(paren
id|item
comma
id|cd
)paren
)paren
(brace
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|CACHE_VALID
comma
op_amp
id|item-&gt;flags
)paren
op_logical_and
op_logical_neg
id|test_bit
c_func
(paren
id|CACHE_NEGATIVE
comma
op_amp
id|item-&gt;flags
)paren
)paren
id|auth_domain_put
c_func
(paren
op_amp
id|im-&gt;m_client-&gt;h
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|im
)paren
suffix:semicolon
)brace
)brace
DECL|function|ip_map_hash
r_static
r_inline
r_int
id|ip_map_hash
c_func
(paren
r_struct
id|ip_map
op_star
id|item
)paren
(brace
r_return
id|hash_str
c_func
(paren
id|item-&gt;m_class
comma
id|IP_HASHBITS
)paren
op_xor
id|hash_long
c_func
(paren
(paren
r_int
r_int
)paren
id|item-&gt;m_addr.s_addr
comma
id|IP_HASHBITS
)paren
suffix:semicolon
)brace
DECL|function|ip_map_match
r_static
r_inline
r_int
id|ip_map_match
c_func
(paren
r_struct
id|ip_map
op_star
id|item
comma
r_struct
id|ip_map
op_star
id|tmp
)paren
(brace
r_return
id|strcmp
c_func
(paren
id|tmp-&gt;m_class
comma
id|item-&gt;m_class
)paren
op_eq
l_int|0
op_logical_and
id|tmp-&gt;m_addr.s_addr
op_eq
id|item-&gt;m_addr.s_addr
suffix:semicolon
)brace
DECL|function|ip_map_init
r_static
r_inline
r_void
id|ip_map_init
c_func
(paren
r_struct
id|ip_map
op_star
r_new
comma
r_struct
id|ip_map
op_star
id|item
)paren
(brace
r_new
op_member_access_from_pointer
id|m_class
op_assign
id|item-&gt;m_class
suffix:semicolon
id|item-&gt;m_class
op_assign
l_int|NULL
suffix:semicolon
r_new
op_member_access_from_pointer
id|m_addr.s_addr
op_assign
id|item-&gt;m_addr.s_addr
suffix:semicolon
)brace
DECL|function|ip_map_update
r_static
r_inline
r_void
id|ip_map_update
c_func
(paren
r_struct
id|ip_map
op_star
r_new
comma
r_struct
id|ip_map
op_star
id|item
)paren
(brace
id|cache_get
c_func
(paren
op_amp
id|item-&gt;m_client-&gt;h.h
)paren
suffix:semicolon
r_new
op_member_access_from_pointer
id|m_client
op_assign
id|item-&gt;m_client
suffix:semicolon
r_new
op_member_access_from_pointer
id|m_add_change
op_assign
id|item-&gt;m_add_change
suffix:semicolon
)brace
DECL|function|ip_map_request
r_static
r_void
id|ip_map_request
c_func
(paren
r_struct
id|cache_detail
op_star
id|cd
comma
r_struct
id|cache_head
op_star
id|h
comma
r_char
op_star
op_star
id|bpp
comma
r_int
op_star
id|blen
)paren
(brace
r_char
id|text_addr
(braket
l_int|20
)braket
suffix:semicolon
r_struct
id|ip_map
op_star
id|im
op_assign
id|container_of
c_func
(paren
id|h
comma
r_struct
id|ip_map
comma
id|h
)paren
suffix:semicolon
id|__u32
id|addr
op_assign
id|im-&gt;m_addr.s_addr
suffix:semicolon
id|snprintf
c_func
(paren
id|text_addr
comma
l_int|20
comma
l_string|&quot;%u.%u.%u.%u&quot;
comma
id|ntohl
c_func
(paren
id|addr
)paren
op_rshift
l_int|24
op_amp
l_int|0xff
comma
id|ntohl
c_func
(paren
id|addr
)paren
op_rshift
l_int|16
op_amp
l_int|0xff
comma
id|ntohl
c_func
(paren
id|addr
)paren
op_rshift
l_int|8
op_amp
l_int|0xff
comma
id|ntohl
c_func
(paren
id|addr
)paren
op_rshift
l_int|0
op_amp
l_int|0xff
)paren
suffix:semicolon
id|qword_add
c_func
(paren
id|bpp
comma
id|blen
comma
id|im-&gt;m_class
)paren
suffix:semicolon
id|qword_add
c_func
(paren
id|bpp
comma
id|blen
comma
id|text_addr
)paren
suffix:semicolon
(paren
op_star
id|bpp
)paren
(braket
op_minus
l_int|1
)braket
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
)brace
r_static
r_struct
id|ip_map
op_star
id|ip_map_lookup
c_func
(paren
r_struct
id|ip_map
op_star
comma
r_int
)paren
suffix:semicolon
DECL|function|ip_map_parse
r_static
r_int
id|ip_map_parse
c_func
(paren
r_struct
id|cache_detail
op_star
id|cd
comma
r_char
op_star
id|mesg
comma
r_int
id|mlen
)paren
(brace
multiline_comment|/* class ipaddress [domainname] */
r_char
r_class
(braket
l_int|50
)braket
comma
id|buf
(braket
l_int|50
)braket
suffix:semicolon
r_int
id|len
suffix:semicolon
r_int
id|b1
comma
id|b2
comma
id|b3
comma
id|b4
suffix:semicolon
r_char
id|c
suffix:semicolon
r_struct
id|ip_map
id|ipm
comma
op_star
id|ipmp
suffix:semicolon
r_struct
id|auth_domain
op_star
id|dom
suffix:semicolon
id|time_t
id|expiry
suffix:semicolon
r_if
c_cond
(paren
id|mesg
(braket
id|mlen
op_minus
l_int|1
)braket
op_ne
l_char|&squot;&bslash;n&squot;
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|mesg
(braket
id|mlen
op_minus
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* class */
id|len
op_assign
id|qword_get
c_func
(paren
op_amp
id|mesg
comma
r_class
comma
l_int|50
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_le
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* ip address */
id|len
op_assign
id|qword_get
c_func
(paren
op_amp
id|mesg
comma
id|buf
comma
l_int|50
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_le
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|sscanf
c_func
(paren
id|buf
comma
l_string|&quot;%u.%u.%u.%u%c&quot;
comma
op_amp
id|b1
comma
op_amp
id|b2
comma
op_amp
id|b3
comma
op_amp
id|b4
comma
op_amp
id|c
)paren
op_ne
l_int|4
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|expiry
op_assign
id|get_expiry
c_func
(paren
op_amp
id|mesg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|expiry
op_eq
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* domainname, or empty for NEGATIVE */
id|len
op_assign
id|qword_get
c_func
(paren
op_amp
id|mesg
comma
id|buf
comma
l_int|50
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|len
)paren
(brace
id|dom
op_assign
id|unix_domain_find
c_func
(paren
id|buf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dom
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOENT
suffix:semicolon
)brace
r_else
id|dom
op_assign
l_int|NULL
suffix:semicolon
id|ipm.m_class
op_assign
id|strdup
c_func
(paren
r_class
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ipm.m_class
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|ipm.m_addr.s_addr
op_assign
id|htonl
c_func
(paren
(paren
(paren
(paren
(paren
(paren
id|b1
op_lshift
l_int|8
)paren
op_or
id|b2
)paren
op_lshift
l_int|8
)paren
op_or
id|b3
)paren
op_lshift
l_int|8
)paren
op_or
id|b4
)paren
suffix:semicolon
id|ipm.h.flags
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|dom
)paren
(brace
id|ipm.m_client
op_assign
id|container_of
c_func
(paren
id|dom
comma
r_struct
id|unix_domain
comma
id|h
)paren
suffix:semicolon
id|ipm.m_add_change
op_assign
id|ipm.m_client-&gt;addr_changes
suffix:semicolon
)brace
r_else
id|set_bit
c_func
(paren
id|CACHE_NEGATIVE
comma
op_amp
id|ipm.h.flags
)paren
suffix:semicolon
id|ipm.h.expiry_time
op_assign
id|expiry
suffix:semicolon
id|ipmp
op_assign
id|ip_map_lookup
c_func
(paren
op_amp
id|ipm
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ipmp
)paren
id|ip_map_put
c_func
(paren
op_amp
id|ipmp-&gt;h
comma
op_amp
id|ip_map_cache
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dom
)paren
id|auth_domain_put
c_func
(paren
id|dom
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ipm.m_class
)paren
id|kfree
c_func
(paren
id|ipm.m_class
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ipmp
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|cache_flush
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ip_map_show
r_static
r_int
id|ip_map_show
c_func
(paren
r_struct
id|seq_file
op_star
id|m
comma
r_struct
id|cache_detail
op_star
id|cd
comma
r_struct
id|cache_head
op_star
id|h
)paren
(brace
r_struct
id|ip_map
op_star
id|im
suffix:semicolon
r_struct
id|in_addr
id|addr
suffix:semicolon
r_char
op_star
id|dom
op_assign
l_string|&quot;-no-domain-&quot;
suffix:semicolon
r_if
c_cond
(paren
id|h
op_eq
l_int|NULL
)paren
(brace
id|seq_puts
c_func
(paren
id|m
comma
l_string|&quot;#class IP domain&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|im
op_assign
id|container_of
c_func
(paren
id|h
comma
r_struct
id|ip_map
comma
id|h
)paren
suffix:semicolon
multiline_comment|/* class addr domain */
id|addr
op_assign
id|im-&gt;m_addr
suffix:semicolon
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|CACHE_VALID
comma
op_amp
id|h-&gt;flags
)paren
op_logical_and
op_logical_neg
id|test_bit
c_func
(paren
id|CACHE_NEGATIVE
comma
op_amp
id|h-&gt;flags
)paren
)paren
id|dom
op_assign
id|im-&gt;m_client-&gt;h.name
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;%s %d.%d.%d.%d %s&bslash;n&quot;
comma
id|im-&gt;m_class
comma
id|htonl
c_func
(paren
id|addr.s_addr
)paren
op_rshift
l_int|24
op_amp
l_int|0xff
comma
id|htonl
c_func
(paren
id|addr.s_addr
)paren
op_rshift
l_int|16
op_amp
l_int|0xff
comma
id|htonl
c_func
(paren
id|addr.s_addr
)paren
op_rshift
l_int|8
op_amp
l_int|0xff
comma
id|htonl
c_func
(paren
id|addr.s_addr
)paren
op_rshift
l_int|0
op_amp
l_int|0xff
comma
id|dom
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|ip_map_cache
r_struct
id|cache_detail
id|ip_map_cache
op_assign
(brace
dot
id|hash_size
op_assign
id|IP_HASHMAX
comma
dot
id|hash_table
op_assign
id|ip_table
comma
dot
id|name
op_assign
l_string|&quot;auth.unix.ip&quot;
comma
dot
id|cache_put
op_assign
id|ip_map_put
comma
dot
id|cache_request
op_assign
id|ip_map_request
comma
dot
id|cache_parse
op_assign
id|ip_map_parse
comma
dot
id|cache_show
op_assign
id|ip_map_show
comma
)brace
suffix:semicolon
r_static
id|DefineSimpleCacheLookup
c_func
(paren
id|ip_map
comma
l_int|0
)paren
DECL|function|auth_unix_add_addr
r_int
id|auth_unix_add_addr
c_func
(paren
r_struct
id|in_addr
id|addr
comma
r_struct
id|auth_domain
op_star
id|dom
)paren
(brace
r_struct
id|unix_domain
op_star
id|udom
suffix:semicolon
r_struct
id|ip_map
id|ip
comma
op_star
id|ipmp
suffix:semicolon
r_if
c_cond
(paren
id|dom-&gt;flavour
op_ne
id|RPC_AUTH_UNIX
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|udom
op_assign
id|container_of
c_func
(paren
id|dom
comma
r_struct
id|unix_domain
comma
id|h
)paren
suffix:semicolon
id|ip.m_class
op_assign
id|strdup
c_func
(paren
l_string|&quot;nfsd&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ip.m_class
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|ip.m_addr
op_assign
id|addr
suffix:semicolon
id|ip.m_client
op_assign
id|udom
suffix:semicolon
id|ip.m_add_change
op_assign
id|udom-&gt;addr_changes
op_plus
l_int|1
suffix:semicolon
id|ip.h.flags
op_assign
l_int|0
suffix:semicolon
id|ip.h.expiry_time
op_assign
id|NEVER
suffix:semicolon
id|ipmp
op_assign
id|ip_map_lookup
c_func
(paren
op_amp
id|ip
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ip.m_class
)paren
id|kfree
c_func
(paren
id|ip.m_class
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ipmp
)paren
(brace
id|ip_map_put
c_func
(paren
op_amp
id|ipmp-&gt;h
comma
op_amp
id|ip_map_cache
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_else
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
DECL|function|auth_unix_forget_old
r_int
id|auth_unix_forget_old
c_func
(paren
r_struct
id|auth_domain
op_star
id|dom
)paren
(brace
r_struct
id|unix_domain
op_star
id|udom
suffix:semicolon
r_if
c_cond
(paren
id|dom-&gt;flavour
op_ne
id|RPC_AUTH_UNIX
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|udom
op_assign
id|container_of
c_func
(paren
id|dom
comma
r_struct
id|unix_domain
comma
id|h
)paren
suffix:semicolon
id|udom-&gt;addr_changes
op_increment
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|auth_unix_lookup
r_struct
id|auth_domain
op_star
id|auth_unix_lookup
c_func
(paren
r_struct
id|in_addr
id|addr
)paren
(brace
r_struct
id|ip_map
id|key
comma
op_star
id|ipm
suffix:semicolon
r_struct
id|auth_domain
op_star
id|rv
suffix:semicolon
id|key.m_class
op_assign
l_string|&quot;nfsd&quot;
suffix:semicolon
id|key.m_addr
op_assign
id|addr
suffix:semicolon
id|ipm
op_assign
id|ip_map_lookup
c_func
(paren
op_amp
id|key
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ipm
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|cache_check
c_func
(paren
op_amp
id|ip_map_cache
comma
op_amp
id|ipm-&gt;h
comma
l_int|NULL
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ipm-&gt;m_client-&gt;addr_changes
op_minus
id|ipm-&gt;m_add_change
)paren
OG
l_int|0
)paren
(brace
id|set_bit
c_func
(paren
id|CACHE_NEGATIVE
comma
op_amp
id|ipm-&gt;h.flags
)paren
suffix:semicolon
id|rv
op_assign
l_int|NULL
suffix:semicolon
)brace
r_else
(brace
id|rv
op_assign
op_amp
id|ipm-&gt;m_client-&gt;h
suffix:semicolon
id|cache_get
c_func
(paren
op_amp
id|rv-&gt;h
)paren
suffix:semicolon
)brace
id|ip_map_put
c_func
(paren
op_amp
id|ipm-&gt;h
comma
op_amp
id|ip_map_cache
)paren
suffix:semicolon
r_return
id|rv
suffix:semicolon
)brace
DECL|function|svcauth_unix_purge
r_void
id|svcauth_unix_purge
c_func
(paren
r_void
)paren
(brace
id|cache_purge
c_func
(paren
op_amp
id|ip_map_cache
)paren
suffix:semicolon
id|cache_purge
c_func
(paren
op_amp
id|auth_domain_cache
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|svcauth_null_accept
id|svcauth_null_accept
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
id|u32
op_star
id|authp
)paren
(brace
r_struct
id|kvec
op_star
id|argv
op_assign
op_amp
id|rqstp-&gt;rq_arg.head
(braket
l_int|0
)braket
suffix:semicolon
r_struct
id|kvec
op_star
id|resv
op_assign
op_amp
id|rqstp-&gt;rq_res.head
(braket
l_int|0
)braket
suffix:semicolon
r_int
id|rv
op_assign
l_int|0
suffix:semicolon
r_struct
id|ip_map
id|key
comma
op_star
id|ipm
suffix:semicolon
r_if
c_cond
(paren
id|argv-&gt;iov_len
OL
l_int|3
op_star
l_int|4
)paren
r_return
id|SVC_GARBAGE
suffix:semicolon
r_if
c_cond
(paren
id|svc_getu32
c_func
(paren
id|argv
)paren
op_ne
l_int|0
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;svc: bad null cred&bslash;n&quot;
)paren
suffix:semicolon
op_star
id|authp
op_assign
id|rpc_autherr_badcred
suffix:semicolon
r_return
id|SVC_DENIED
suffix:semicolon
)brace
r_if
c_cond
(paren
id|svc_getu32
c_func
(paren
id|argv
)paren
op_ne
id|RPC_AUTH_NULL
op_logical_or
id|svc_getu32
c_func
(paren
id|argv
)paren
op_ne
l_int|0
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;svc: bad null verf&bslash;n&quot;
)paren
suffix:semicolon
op_star
id|authp
op_assign
id|rpc_autherr_badverf
suffix:semicolon
r_return
id|SVC_DENIED
suffix:semicolon
)brace
multiline_comment|/* Signal that mapping to nobody uid/gid is required */
id|rqstp-&gt;rq_cred.cr_uid
op_assign
(paren
id|uid_t
)paren
op_minus
l_int|1
suffix:semicolon
id|rqstp-&gt;rq_cred.cr_gid
op_assign
(paren
id|gid_t
)paren
op_minus
l_int|1
suffix:semicolon
id|rqstp-&gt;rq_cred.cr_group_info
op_assign
id|groups_alloc
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rqstp-&gt;rq_cred.cr_group_info
op_eq
l_int|NULL
)paren
r_return
id|SVC_DROP
suffix:semicolon
multiline_comment|/* kmalloc failure - client must retry */
multiline_comment|/* Put NULL verifier */
id|svc_putu32
c_func
(paren
id|resv
comma
id|RPC_AUTH_NULL
)paren
suffix:semicolon
id|svc_putu32
c_func
(paren
id|resv
comma
l_int|0
)paren
suffix:semicolon
id|key.m_class
op_assign
id|rqstp-&gt;rq_server-&gt;sv_program-&gt;pg_class
suffix:semicolon
id|key.m_addr
op_assign
id|rqstp-&gt;rq_addr.sin_addr
suffix:semicolon
id|ipm
op_assign
id|ip_map_lookup
c_func
(paren
op_amp
id|key
comma
l_int|0
)paren
suffix:semicolon
id|rqstp-&gt;rq_client
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|ipm
)paren
r_switch
c_cond
(paren
id|cache_check
c_func
(paren
op_amp
id|ip_map_cache
comma
op_amp
id|ipm-&gt;h
comma
op_amp
id|rqstp-&gt;rq_chandle
)paren
)paren
(brace
r_case
op_minus
id|EAGAIN
suffix:colon
id|rv
op_assign
id|SVC_DROP
suffix:semicolon
r_break
suffix:semicolon
r_case
op_minus
id|ENOENT
suffix:colon
id|rv
op_assign
id|SVC_OK
suffix:semicolon
multiline_comment|/* rq_client is NULL */
r_break
suffix:semicolon
r_case
l_int|0
suffix:colon
id|rqstp-&gt;rq_client
op_assign
op_amp
id|ipm-&gt;m_client-&gt;h
suffix:semicolon
id|cache_get
c_func
(paren
op_amp
id|rqstp-&gt;rq_client-&gt;h
)paren
suffix:semicolon
id|ip_map_put
c_func
(paren
op_amp
id|ipm-&gt;h
comma
op_amp
id|ip_map_cache
)paren
suffix:semicolon
id|rv
op_assign
id|SVC_OK
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
r_else
id|rv
op_assign
id|SVC_DROP
suffix:semicolon
r_if
c_cond
(paren
id|rqstp-&gt;rq_client
op_eq
l_int|NULL
op_logical_and
id|rqstp-&gt;rq_proc
op_ne
l_int|0
)paren
op_star
id|authp
op_assign
id|rpc_autherr_badcred
suffix:semicolon
r_return
id|rv
suffix:semicolon
)brace
r_static
r_int
DECL|function|svcauth_null_release
id|svcauth_null_release
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
)paren
(brace
r_if
c_cond
(paren
id|rqstp-&gt;rq_client
)paren
id|auth_domain_put
c_func
(paren
id|rqstp-&gt;rq_client
)paren
suffix:semicolon
id|rqstp-&gt;rq_client
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|rqstp-&gt;rq_cred.cr_group_info
)paren
id|put_group_info
c_func
(paren
id|rqstp-&gt;rq_cred.cr_group_info
)paren
suffix:semicolon
id|rqstp-&gt;rq_cred.cr_group_info
op_assign
l_int|NULL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
multiline_comment|/* don&squot;t drop */
)brace
DECL|variable|svcauth_null
r_struct
id|auth_ops
id|svcauth_null
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;null&quot;
comma
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|flavour
op_assign
id|RPC_AUTH_NULL
comma
dot
id|accept
op_assign
id|svcauth_null_accept
comma
dot
id|release
op_assign
id|svcauth_null_release
comma
)brace
suffix:semicolon
r_int
DECL|function|svcauth_unix_accept
id|svcauth_unix_accept
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
id|u32
op_star
id|authp
)paren
(brace
r_struct
id|kvec
op_star
id|argv
op_assign
op_amp
id|rqstp-&gt;rq_arg.head
(braket
l_int|0
)braket
suffix:semicolon
r_struct
id|kvec
op_star
id|resv
op_assign
op_amp
id|rqstp-&gt;rq_res.head
(braket
l_int|0
)braket
suffix:semicolon
r_struct
id|svc_cred
op_star
id|cred
op_assign
op_amp
id|rqstp-&gt;rq_cred
suffix:semicolon
id|u32
id|slen
comma
id|i
suffix:semicolon
r_int
id|len
op_assign
id|argv-&gt;iov_len
suffix:semicolon
r_int
id|rv
op_assign
l_int|0
suffix:semicolon
r_struct
id|ip_map
id|key
comma
op_star
id|ipm
suffix:semicolon
id|cred-&gt;cr_group_info
op_assign
l_int|NULL
suffix:semicolon
id|rqstp-&gt;rq_client
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
(paren
id|len
op_sub_assign
l_int|3
op_star
l_int|4
)paren
OL
l_int|0
)paren
r_return
id|SVC_GARBAGE
suffix:semicolon
id|svc_getu32
c_func
(paren
id|argv
)paren
suffix:semicolon
multiline_comment|/* length */
id|svc_getu32
c_func
(paren
id|argv
)paren
suffix:semicolon
multiline_comment|/* time stamp */
id|slen
op_assign
id|XDR_QUADLEN
c_func
(paren
id|ntohl
c_func
(paren
id|svc_getu32
c_func
(paren
id|argv
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/* machname length */
r_if
c_cond
(paren
id|slen
OG
l_int|64
op_logical_or
(paren
id|len
op_sub_assign
(paren
id|slen
op_plus
l_int|3
)paren
op_star
l_int|4
)paren
OL
l_int|0
)paren
r_goto
id|badcred
suffix:semicolon
id|argv-&gt;iov_base
op_assign
(paren
r_void
op_star
)paren
(paren
(paren
id|u32
op_star
)paren
id|argv-&gt;iov_base
op_plus
id|slen
)paren
suffix:semicolon
multiline_comment|/* skip machname */
id|argv-&gt;iov_len
op_sub_assign
id|slen
op_star
l_int|4
suffix:semicolon
id|cred-&gt;cr_uid
op_assign
id|ntohl
c_func
(paren
id|svc_getu32
c_func
(paren
id|argv
)paren
)paren
suffix:semicolon
multiline_comment|/* uid */
id|cred-&gt;cr_gid
op_assign
id|ntohl
c_func
(paren
id|svc_getu32
c_func
(paren
id|argv
)paren
)paren
suffix:semicolon
multiline_comment|/* gid */
id|slen
op_assign
id|ntohl
c_func
(paren
id|svc_getu32
c_func
(paren
id|argv
)paren
)paren
suffix:semicolon
multiline_comment|/* gids length */
r_if
c_cond
(paren
id|slen
OG
l_int|16
op_logical_or
(paren
id|len
op_sub_assign
(paren
id|slen
op_plus
l_int|2
)paren
op_star
l_int|4
)paren
OL
l_int|0
)paren
r_goto
id|badcred
suffix:semicolon
id|cred-&gt;cr_group_info
op_assign
id|groups_alloc
c_func
(paren
id|slen
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cred-&gt;cr_group_info
op_eq
l_int|NULL
)paren
r_return
id|SVC_DROP
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
id|slen
suffix:semicolon
id|i
op_increment
)paren
id|GROUP_AT
c_func
(paren
id|cred-&gt;cr_group_info
comma
id|i
)paren
op_assign
id|ntohl
c_func
(paren
id|svc_getu32
c_func
(paren
id|argv
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|svc_getu32
c_func
(paren
id|argv
)paren
op_ne
id|RPC_AUTH_NULL
op_logical_or
id|svc_getu32
c_func
(paren
id|argv
)paren
op_ne
l_int|0
)paren
(brace
op_star
id|authp
op_assign
id|rpc_autherr_badverf
suffix:semicolon
r_return
id|SVC_DENIED
suffix:semicolon
)brace
id|key.m_class
op_assign
id|rqstp-&gt;rq_server-&gt;sv_program-&gt;pg_class
suffix:semicolon
id|key.m_addr
op_assign
id|rqstp-&gt;rq_addr.sin_addr
suffix:semicolon
id|ipm
op_assign
id|ip_map_lookup
c_func
(paren
op_amp
id|key
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ipm
)paren
r_switch
c_cond
(paren
id|cache_check
c_func
(paren
op_amp
id|ip_map_cache
comma
op_amp
id|ipm-&gt;h
comma
op_amp
id|rqstp-&gt;rq_chandle
)paren
)paren
(brace
r_case
op_minus
id|EAGAIN
suffix:colon
id|rv
op_assign
id|SVC_DROP
suffix:semicolon
r_break
suffix:semicolon
r_case
op_minus
id|ENOENT
suffix:colon
id|rv
op_assign
id|SVC_OK
suffix:semicolon
multiline_comment|/* rq_client is NULL */
r_break
suffix:semicolon
r_case
l_int|0
suffix:colon
id|rqstp-&gt;rq_client
op_assign
op_amp
id|ipm-&gt;m_client-&gt;h
suffix:semicolon
id|cache_get
c_func
(paren
op_amp
id|rqstp-&gt;rq_client-&gt;h
)paren
suffix:semicolon
id|ip_map_put
c_func
(paren
op_amp
id|ipm-&gt;h
comma
op_amp
id|ip_map_cache
)paren
suffix:semicolon
id|rv
op_assign
id|SVC_OK
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
r_else
id|rv
op_assign
id|SVC_DROP
suffix:semicolon
r_if
c_cond
(paren
id|rv
op_eq
id|SVC_OK
op_logical_and
id|rqstp-&gt;rq_client
op_eq
l_int|NULL
op_logical_and
id|rqstp-&gt;rq_proc
op_ne
l_int|0
)paren
r_goto
id|badcred
suffix:semicolon
multiline_comment|/* Put NULL verifier */
id|svc_putu32
c_func
(paren
id|resv
comma
id|RPC_AUTH_NULL
)paren
suffix:semicolon
id|svc_putu32
c_func
(paren
id|resv
comma
l_int|0
)paren
suffix:semicolon
r_return
id|rv
suffix:semicolon
id|badcred
suffix:colon
op_star
id|authp
op_assign
id|rpc_autherr_badcred
suffix:semicolon
r_return
id|SVC_DENIED
suffix:semicolon
)brace
r_int
DECL|function|svcauth_unix_release
id|svcauth_unix_release
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
)paren
(brace
multiline_comment|/* Verifier (such as it is) is already in place.&n;&t; */
r_if
c_cond
(paren
id|rqstp-&gt;rq_client
)paren
id|auth_domain_put
c_func
(paren
id|rqstp-&gt;rq_client
)paren
suffix:semicolon
id|rqstp-&gt;rq_client
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|rqstp-&gt;rq_cred.cr_group_info
)paren
id|put_group_info
c_func
(paren
id|rqstp-&gt;rq_cred.cr_group_info
)paren
suffix:semicolon
id|rqstp-&gt;rq_cred.cr_group_info
op_assign
l_int|NULL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|svcauth_unix
r_struct
id|auth_ops
id|svcauth_unix
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;unix&quot;
comma
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|flavour
op_assign
id|RPC_AUTH_UNIX
comma
dot
id|accept
op_assign
id|svcauth_unix_accept
comma
dot
id|release
op_assign
id|svcauth_unix_release
comma
dot
id|domain_release
op_assign
id|svcauth_unix_domain_release
comma
)brace
suffix:semicolon
eof
