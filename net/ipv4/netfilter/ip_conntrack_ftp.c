multiline_comment|/* FTP extension for IP connection tracking. */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/netfilter.h&gt;
macro_line|#include &lt;linux/ip.h&gt;
macro_line|#include &lt;linux/ctype.h&gt;
macro_line|#include &lt;net/checksum.h&gt;
macro_line|#include &lt;net/tcp.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/lockhelp.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_conntrack_helper.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_conntrack_ftp.h&gt;
DECL|variable|ip_ftp_lock
id|DECLARE_LOCK
c_func
(paren
id|ip_ftp_lock
)paren
suffix:semicolon
DECL|variable|ip_conntrack_ftp
r_struct
id|module
op_star
id|ip_conntrack_ftp
op_assign
id|THIS_MODULE
suffix:semicolon
DECL|macro|MAX_PORTS
mdefine_line|#define MAX_PORTS 8
DECL|variable|ports
r_static
r_int
id|ports
(braket
id|MAX_PORTS
)braket
suffix:semicolon
DECL|variable|ports_c
r_static
r_int
id|ports_c
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef MODULE_PARM
id|MODULE_PARM
c_func
(paren
id|ports
comma
l_string|&quot;1-&quot;
id|__MODULE_STRING
c_func
(paren
id|MAX_PORTS
)paren
l_string|&quot;i&quot;
)paren
suffix:semicolon
macro_line|#endif
DECL|variable|loose
r_static
r_int
id|loose
op_assign
l_int|0
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|loose
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
macro_line|#if 0
mdefine_line|#define DEBUGP printk
macro_line|#else
DECL|macro|DEBUGP
mdefine_line|#define DEBUGP(format, args...)
macro_line|#endif
r_static
r_int
id|try_rfc959
c_func
(paren
r_const
r_char
op_star
comma
r_int
comma
id|u_int32_t
(braket
)braket
comma
r_char
)paren
suffix:semicolon
r_static
r_int
id|try_eprt
c_func
(paren
r_const
r_char
op_star
comma
r_int
comma
id|u_int32_t
(braket
)braket
comma
r_char
)paren
suffix:semicolon
r_static
r_int
id|try_espv_response
c_func
(paren
r_const
r_char
op_star
comma
r_int
comma
id|u_int32_t
(braket
)braket
comma
r_char
)paren
suffix:semicolon
DECL|struct|ftp_search
r_static
r_struct
id|ftp_search
(brace
DECL|member|dir
r_enum
id|ip_conntrack_dir
id|dir
suffix:semicolon
DECL|member|pattern
r_const
r_char
op_star
id|pattern
suffix:semicolon
DECL|member|plen
r_int
id|plen
suffix:semicolon
DECL|member|skip
r_char
id|skip
suffix:semicolon
DECL|member|term
r_char
id|term
suffix:semicolon
DECL|member|ftptype
r_enum
id|ip_ct_ftp_type
id|ftptype
suffix:semicolon
DECL|member|getnum
r_int
(paren
op_star
id|getnum
)paren
(paren
r_const
r_char
op_star
comma
r_int
comma
id|u_int32_t
(braket
)braket
comma
r_char
)paren
suffix:semicolon
DECL|variable|search
)brace
id|search
(braket
)braket
op_assign
(brace
(brace
id|IP_CT_DIR_ORIGINAL
comma
l_string|&quot;PORT&quot;
comma
r_sizeof
(paren
l_string|&quot;PORT&quot;
)paren
op_minus
l_int|1
comma
l_char|&squot; &squot;
comma
l_char|&squot;&bslash;r&squot;
comma
id|IP_CT_FTP_PORT
comma
id|try_rfc959
comma
)brace
comma
(brace
id|IP_CT_DIR_REPLY
comma
l_string|&quot;227 &quot;
comma
r_sizeof
(paren
l_string|&quot;227 &quot;
)paren
op_minus
l_int|1
comma
l_char|&squot;(&squot;
comma
l_char|&squot;)&squot;
comma
id|IP_CT_FTP_PASV
comma
id|try_rfc959
comma
)brace
comma
(brace
id|IP_CT_DIR_ORIGINAL
comma
l_string|&quot;EPRT&quot;
comma
r_sizeof
(paren
l_string|&quot;EPRT&quot;
)paren
op_minus
l_int|1
comma
l_char|&squot; &squot;
comma
l_char|&squot;&bslash;r&squot;
comma
id|IP_CT_FTP_EPRT
comma
id|try_eprt
comma
)brace
comma
(brace
id|IP_CT_DIR_REPLY
comma
l_string|&quot;229 &quot;
comma
r_sizeof
(paren
l_string|&quot;229 &quot;
)paren
op_minus
l_int|1
comma
l_char|&squot;(&squot;
comma
l_char|&squot;)&squot;
comma
id|IP_CT_FTP_EPSV
comma
id|try_espv_response
comma
)brace
comma
)brace
suffix:semicolon
DECL|function|try_number
r_static
r_int
id|try_number
c_func
(paren
r_const
r_char
op_star
id|data
comma
r_int
id|dlen
comma
id|u_int32_t
id|array
(braket
)braket
comma
r_int
id|array_size
comma
r_char
id|sep
comma
r_char
id|term
)paren
(brace
id|u_int32_t
id|i
comma
id|len
suffix:semicolon
id|memset
c_func
(paren
id|array
comma
l_int|0
comma
r_sizeof
(paren
id|array
(braket
l_int|0
)braket
)paren
op_star
id|array_size
)paren
suffix:semicolon
multiline_comment|/* Keep data pointing at next char. */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
comma
id|len
op_assign
l_int|0
suffix:semicolon
id|len
OL
id|dlen
op_logical_and
id|i
OL
id|array_size
suffix:semicolon
id|len
op_increment
comma
id|data
op_increment
)paren
(brace
r_if
c_cond
(paren
op_star
id|data
op_ge
l_char|&squot;0&squot;
op_logical_and
op_star
id|data
op_le
l_char|&squot;9&squot;
)paren
(brace
id|array
(braket
id|i
)braket
op_assign
id|array
(braket
id|i
)braket
op_star
l_int|10
op_plus
op_star
id|data
op_minus
l_char|&squot;0&squot;
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_star
id|data
op_eq
id|sep
)paren
id|i
op_increment
suffix:semicolon
r_else
(brace
multiline_comment|/* Unexpected character; true if it&squot;s the&n;&t;&t;&t;   terminator and we&squot;re finished. */
r_if
c_cond
(paren
op_star
id|data
op_eq
id|term
op_logical_and
id|i
op_eq
id|array_size
op_minus
l_int|1
)paren
r_return
id|len
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;Char %u (got %u nums) `%u&squot; unexpected&bslash;n&quot;
comma
id|len
comma
id|i
comma
op_star
id|data
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
id|DEBUGP
c_func
(paren
l_string|&quot;Failed to fill %u numbers separated by %c&bslash;n&quot;
comma
id|array_size
comma
id|sep
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Returns 0, or length of numbers: 192,168,1,1,5,6 */
DECL|function|try_rfc959
r_static
r_int
id|try_rfc959
c_func
(paren
r_const
r_char
op_star
id|data
comma
r_int
id|dlen
comma
id|u_int32_t
id|array
(braket
l_int|6
)braket
comma
r_char
id|term
)paren
(brace
r_return
id|try_number
c_func
(paren
id|data
comma
id|dlen
comma
id|array
comma
l_int|6
comma
l_char|&squot;,&squot;
comma
id|term
)paren
suffix:semicolon
)brace
multiline_comment|/* Grab port: number up to delimiter */
DECL|function|get_port
r_static
r_int
id|get_port
c_func
(paren
r_const
r_char
op_star
id|data
comma
r_int
id|start
comma
r_int
id|dlen
comma
r_char
id|delim
comma
id|u_int32_t
id|array
(braket
l_int|2
)braket
)paren
(brace
id|u_int16_t
id|port
op_assign
l_int|0
suffix:semicolon
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|start
suffix:semicolon
id|i
OL
id|dlen
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/* Finished? */
r_if
c_cond
(paren
id|data
(braket
id|i
)braket
op_eq
id|delim
)paren
(brace
r_if
c_cond
(paren
id|port
op_eq
l_int|0
)paren
r_break
suffix:semicolon
id|array
(braket
l_int|0
)braket
op_assign
id|port
op_rshift
l_int|8
suffix:semicolon
id|array
(braket
l_int|1
)braket
op_assign
id|port
suffix:semicolon
r_return
id|i
op_plus
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|data
(braket
id|i
)braket
op_ge
l_char|&squot;0&squot;
op_logical_and
id|data
(braket
id|i
)braket
op_le
l_char|&squot;9&squot;
)paren
id|port
op_assign
id|port
op_star
l_int|10
op_plus
id|data
(braket
id|i
)braket
op_minus
l_char|&squot;0&squot;
suffix:semicolon
r_else
multiline_comment|/* Some other crap */
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Returns 0, or length of numbers: |1|132.235.1.2|6275| */
DECL|function|try_eprt
r_static
r_int
id|try_eprt
c_func
(paren
r_const
r_char
op_star
id|data
comma
r_int
id|dlen
comma
id|u_int32_t
id|array
(braket
l_int|6
)braket
comma
r_char
id|term
)paren
(brace
r_char
id|delim
suffix:semicolon
r_int
id|length
suffix:semicolon
multiline_comment|/* First character is delimiter, then &quot;1&quot; for IPv4, then&n;           delimiter again. */
r_if
c_cond
(paren
id|dlen
op_le
l_int|3
)paren
r_return
l_int|0
suffix:semicolon
id|delim
op_assign
id|data
(braket
l_int|0
)braket
suffix:semicolon
r_if
c_cond
(paren
id|isdigit
c_func
(paren
id|delim
)paren
op_logical_or
id|delim
template_param
l_int|126
op_logical_or
id|data
(braket
l_int|1
)braket
op_ne
l_char|&squot;1&squot;
op_logical_or
id|data
(braket
l_int|2
)braket
op_ne
id|delim
)paren
r_return
l_int|0
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;EPRT: Got |1|!&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Now we have IP address. */
id|length
op_assign
id|try_number
c_func
(paren
id|data
op_plus
l_int|3
comma
id|dlen
op_minus
l_int|3
comma
id|array
comma
l_int|4
comma
l_char|&squot;.&squot;
comma
id|delim
)paren
suffix:semicolon
r_if
c_cond
(paren
id|length
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;EPRT: Got IP address!&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Start offset includes initial &quot;|1|&quot;, and trailing delimiter */
r_return
id|get_port
c_func
(paren
id|data
comma
l_int|3
op_plus
id|length
op_plus
l_int|1
comma
id|dlen
comma
id|delim
comma
id|array
op_plus
l_int|4
)paren
suffix:semicolon
)brace
multiline_comment|/* Returns 0, or length of numbers: |||6446| */
DECL|function|try_espv_response
r_static
r_int
id|try_espv_response
c_func
(paren
r_const
r_char
op_star
id|data
comma
r_int
id|dlen
comma
id|u_int32_t
id|array
(braket
l_int|6
)braket
comma
r_char
id|term
)paren
(brace
r_char
id|delim
suffix:semicolon
multiline_comment|/* Three delimiters. */
r_if
c_cond
(paren
id|dlen
op_le
l_int|3
)paren
r_return
l_int|0
suffix:semicolon
id|delim
op_assign
id|data
(braket
l_int|0
)braket
suffix:semicolon
r_if
c_cond
(paren
id|isdigit
c_func
(paren
id|delim
)paren
op_logical_or
id|delim
template_param
l_int|126
op_logical_or
id|data
(braket
l_int|1
)braket
op_ne
id|delim
op_logical_or
id|data
(braket
l_int|2
)braket
op_ne
id|delim
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|get_port
c_func
(paren
id|data
comma
l_int|3
comma
id|dlen
comma
id|delim
comma
id|array
op_plus
l_int|4
)paren
suffix:semicolon
)brace
multiline_comment|/* Return 1 for match, 0 for accept, -1 for partial. */
DECL|function|find_pattern
r_static
r_int
id|find_pattern
c_func
(paren
r_const
r_char
op_star
id|data
comma
r_int
id|dlen
comma
r_const
r_char
op_star
id|pattern
comma
r_int
id|plen
comma
r_char
id|skip
comma
r_char
id|term
comma
r_int
r_int
op_star
id|numoff
comma
r_int
r_int
op_star
id|numlen
comma
id|u_int32_t
id|array
(braket
l_int|6
)braket
comma
r_int
(paren
op_star
id|getnum
)paren
(paren
r_const
r_char
op_star
comma
r_int
comma
id|u_int32_t
(braket
)braket
comma
r_char
)paren
)paren
(brace
r_int
id|i
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;find_pattern `%s&squot;: dlen = %u&bslash;n&quot;
comma
id|pattern
comma
id|dlen
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dlen
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|dlen
op_le
id|plen
)paren
(brace
multiline_comment|/* Short packet: try for partial? */
r_if
c_cond
(paren
id|strnicmp
c_func
(paren
id|data
comma
id|pattern
comma
id|dlen
)paren
op_eq
l_int|0
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_else
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strnicmp
c_func
(paren
id|data
comma
id|pattern
comma
id|plen
)paren
op_ne
l_int|0
)paren
(brace
macro_line|#if 0
r_int
id|i
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;ftp: string mismatch&bslash;n&quot;
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
id|plen
suffix:semicolon
id|i
op_increment
)paren
(brace
id|DEBUGFTP
c_func
(paren
l_string|&quot;ftp:char %u `%c&squot;(%u) vs `%c&squot;(%u)&bslash;n&quot;
comma
id|i
comma
id|data
(braket
id|i
)braket
comma
id|data
(braket
id|i
)braket
comma
id|pattern
(braket
id|i
)braket
comma
id|pattern
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
id|DEBUGP
c_func
(paren
l_string|&quot;Pattern matches!&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Now we&squot;ve found the constant string, try to skip&n;&t;   to the &squot;skip&squot; character */
r_for
c_loop
(paren
id|i
op_assign
id|plen
suffix:semicolon
id|data
(braket
id|i
)braket
op_ne
id|skip
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|i
op_eq
id|dlen
op_minus
l_int|1
)paren
r_return
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* Skip over the last character */
id|i
op_increment
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;Skipped up to `%c&squot;!&bslash;n&quot;
comma
id|skip
)paren
suffix:semicolon
op_star
id|numoff
op_assign
id|i
suffix:semicolon
op_star
id|numlen
op_assign
id|getnum
c_func
(paren
id|data
op_plus
id|i
comma
id|dlen
op_minus
id|i
comma
id|array
comma
id|term
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|numlen
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;Match succeeded!&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* FIXME: This should be in userspace.  Later. */
DECL|function|help
r_static
r_int
id|help
c_func
(paren
r_const
r_struct
id|iphdr
op_star
id|iph
comma
r_int
id|len
comma
r_struct
id|ip_conntrack
op_star
id|ct
comma
r_enum
id|ip_conntrack_info
id|ctinfo
)paren
(brace
multiline_comment|/* tcplen not negative guaranteed by ip_conntrack_tcp.c */
r_struct
id|tcphdr
op_star
id|tcph
op_assign
(paren
r_void
op_star
)paren
id|iph
op_plus
id|iph-&gt;ihl
op_star
l_int|4
suffix:semicolon
r_const
r_char
op_star
id|data
op_assign
(paren
r_const
r_char
op_star
)paren
id|tcph
op_plus
id|tcph-&gt;doff
op_star
l_int|4
suffix:semicolon
r_int
r_int
id|tcplen
op_assign
id|len
op_minus
id|iph-&gt;ihl
op_star
l_int|4
suffix:semicolon
r_int
r_int
id|datalen
op_assign
id|tcplen
op_minus
id|tcph-&gt;doff
op_star
l_int|4
suffix:semicolon
id|u_int32_t
id|old_seq_aft_nl
suffix:semicolon
r_int
id|old_seq_aft_nl_set
suffix:semicolon
id|u_int32_t
id|array
(braket
l_int|6
)braket
op_assign
(brace
l_int|0
)brace
suffix:semicolon
r_int
id|dir
op_assign
id|CTINFO2DIR
c_func
(paren
id|ctinfo
)paren
suffix:semicolon
r_int
r_int
id|matchlen
comma
id|matchoff
suffix:semicolon
r_struct
id|ip_ct_ftp_master
op_star
id|ct_ftp_info
op_assign
op_amp
id|ct-&gt;help.ct_ftp_info
suffix:semicolon
r_struct
id|ip_conntrack_expect
id|expect
comma
op_star
id|exp
op_assign
op_amp
id|expect
suffix:semicolon
r_struct
id|ip_ct_ftp_expect
op_star
id|exp_ftp_info
op_assign
op_amp
id|exp-&gt;help.exp_ftp_info
suffix:semicolon
r_int
r_int
id|i
suffix:semicolon
r_int
id|found
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Until there&squot;s been traffic both ways, don&squot;t look in packets. */
r_if
c_cond
(paren
id|ctinfo
op_ne
id|IP_CT_ESTABLISHED
op_logical_and
id|ctinfo
op_ne
id|IP_CT_ESTABLISHED
op_plus
id|IP_CT_IS_REPLY
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;ftp: Conntrackinfo = %u&bslash;n&quot;
comma
id|ctinfo
)paren
suffix:semicolon
r_return
id|NF_ACCEPT
suffix:semicolon
)brace
multiline_comment|/* Not whole TCP header? */
r_if
c_cond
(paren
id|tcplen
OL
r_sizeof
(paren
r_struct
id|tcphdr
)paren
op_logical_or
id|tcplen
OL
id|tcph-&gt;doff
op_star
l_int|4
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;ftp: tcplen = %u&bslash;n&quot;
comma
(paren
r_int
)paren
id|tcplen
)paren
suffix:semicolon
r_return
id|NF_ACCEPT
suffix:semicolon
)brace
multiline_comment|/* Checksum invalid?  Ignore. */
multiline_comment|/* FIXME: Source route IP option packets --RR */
r_if
c_cond
(paren
id|tcp_v4_check
c_func
(paren
id|tcph
comma
id|tcplen
comma
id|iph-&gt;saddr
comma
id|iph-&gt;daddr
comma
id|csum_partial
c_func
(paren
(paren
r_char
op_star
)paren
id|tcph
comma
id|tcplen
comma
l_int|0
)paren
)paren
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;ftp_help: bad csum: %p %u %u.%u.%u.%u %u.%u.%u.%u&bslash;n&quot;
comma
id|tcph
comma
id|tcplen
comma
id|NIPQUAD
c_func
(paren
id|iph-&gt;saddr
)paren
comma
id|NIPQUAD
c_func
(paren
id|iph-&gt;daddr
)paren
)paren
suffix:semicolon
r_return
id|NF_ACCEPT
suffix:semicolon
)brace
id|LOCK_BH
c_func
(paren
op_amp
id|ip_ftp_lock
)paren
suffix:semicolon
id|old_seq_aft_nl_set
op_assign
id|ct_ftp_info-&gt;seq_aft_nl_set
(braket
id|dir
)braket
suffix:semicolon
id|old_seq_aft_nl
op_assign
id|ct_ftp_info-&gt;seq_aft_nl
(braket
id|dir
)braket
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;conntrack_ftp: datalen %u&bslash;n&quot;
comma
id|datalen
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|datalen
OG
l_int|0
)paren
op_logical_and
(paren
id|data
(braket
id|datalen
op_minus
l_int|1
)braket
op_eq
l_char|&squot;&bslash;n&squot;
)paren
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;conntrack_ftp: datalen %u ends in &bslash;&bslash;n&bslash;n&quot;
comma
id|datalen
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|old_seq_aft_nl_set
op_logical_or
id|after
c_func
(paren
id|ntohl
c_func
(paren
id|tcph-&gt;seq
)paren
op_plus
id|datalen
comma
id|old_seq_aft_nl
)paren
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;conntrack_ftp: updating nl to %u&bslash;n&quot;
comma
id|ntohl
c_func
(paren
id|tcph-&gt;seq
)paren
op_plus
id|datalen
)paren
suffix:semicolon
id|ct_ftp_info-&gt;seq_aft_nl
(braket
id|dir
)braket
op_assign
id|ntohl
c_func
(paren
id|tcph-&gt;seq
)paren
op_plus
id|datalen
suffix:semicolon
id|ct_ftp_info-&gt;seq_aft_nl_set
(braket
id|dir
)braket
op_assign
l_int|1
suffix:semicolon
)brace
)brace
id|UNLOCK_BH
c_func
(paren
op_amp
id|ip_ftp_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|old_seq_aft_nl_set
op_logical_or
(paren
id|ntohl
c_func
(paren
id|tcph-&gt;seq
)paren
op_ne
id|old_seq_aft_nl
)paren
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;ip_conntrack_ftp_help: wrong seq pos %s(%u)&bslash;n&quot;
comma
id|old_seq_aft_nl_set
ques
c_cond
l_string|&quot;&quot;
suffix:colon
l_string|&quot;(UNSET) &quot;
comma
id|old_seq_aft_nl
)paren
suffix:semicolon
r_return
id|NF_ACCEPT
suffix:semicolon
)brace
multiline_comment|/* Initialize IP array to expected address (it&squot;s not mentioned&n;           in EPSV responses) */
id|array
(braket
l_int|0
)braket
op_assign
(paren
id|ntohl
c_func
(paren
id|ct-&gt;tuplehash
(braket
id|dir
)braket
dot
id|tuple.src.ip
)paren
op_rshift
l_int|24
)paren
op_amp
l_int|0xFF
suffix:semicolon
id|array
(braket
l_int|1
)braket
op_assign
(paren
id|ntohl
c_func
(paren
id|ct-&gt;tuplehash
(braket
id|dir
)braket
dot
id|tuple.src.ip
)paren
op_rshift
l_int|16
)paren
op_amp
l_int|0xFF
suffix:semicolon
id|array
(braket
l_int|2
)braket
op_assign
(paren
id|ntohl
c_func
(paren
id|ct-&gt;tuplehash
(braket
id|dir
)braket
dot
id|tuple.src.ip
)paren
op_rshift
l_int|8
)paren
op_amp
l_int|0xFF
suffix:semicolon
id|array
(braket
l_int|3
)braket
op_assign
id|ntohl
c_func
(paren
id|ct-&gt;tuplehash
(braket
id|dir
)braket
dot
id|tuple.src.ip
)paren
op_amp
l_int|0xFF
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
id|search
)paren
op_div
r_sizeof
(paren
id|search
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|search
(braket
id|i
)braket
dot
id|dir
op_ne
id|dir
)paren
r_continue
suffix:semicolon
id|found
op_assign
id|find_pattern
c_func
(paren
id|data
comma
id|datalen
comma
id|search
(braket
id|i
)braket
dot
id|pattern
comma
id|search
(braket
id|i
)braket
dot
id|plen
comma
id|search
(braket
id|i
)braket
dot
id|skip
comma
id|search
(braket
id|i
)braket
dot
id|term
comma
op_amp
id|matchoff
comma
op_amp
id|matchlen
comma
id|array
comma
id|search
(braket
id|i
)braket
dot
id|getnum
)paren
suffix:semicolon
r_if
c_cond
(paren
id|found
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|found
op_eq
op_minus
l_int|1
)paren
(brace
multiline_comment|/* We don&squot;t usually drop packets.  After all, this is&n;&t;&t;   connection tracking, not packet filtering.&n;&t;&t;   However, it is neccessary for accurate tracking in&n;&t;&t;   this case. */
r_if
c_cond
(paren
id|net_ratelimit
c_func
(paren
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;conntrack_ftp: partial %s %u+%u&bslash;n&quot;
comma
id|search
(braket
id|i
)braket
dot
id|pattern
comma
id|ntohl
c_func
(paren
id|tcph-&gt;seq
)paren
comma
id|datalen
)paren
suffix:semicolon
r_return
id|NF_DROP
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|found
op_eq
l_int|0
)paren
multiline_comment|/* No match */
r_return
id|NF_ACCEPT
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;conntrack_ftp: match `%.*s&squot; (%u bytes at %u)&bslash;n&quot;
comma
(paren
r_int
)paren
id|matchlen
comma
id|data
op_plus
id|matchoff
comma
id|matchlen
comma
id|ntohl
c_func
(paren
id|tcph-&gt;seq
)paren
op_plus
id|matchoff
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|expect
comma
l_int|0
comma
r_sizeof
(paren
id|expect
)paren
)paren
suffix:semicolon
multiline_comment|/* Update the ftp info */
id|LOCK_BH
c_func
(paren
op_amp
id|ip_ftp_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|htonl
c_func
(paren
(paren
id|array
(braket
l_int|0
)braket
op_lshift
l_int|24
)paren
op_or
(paren
id|array
(braket
l_int|1
)braket
op_lshift
l_int|16
)paren
op_or
(paren
id|array
(braket
l_int|2
)braket
op_lshift
l_int|8
)paren
op_or
id|array
(braket
l_int|3
)braket
)paren
op_eq
id|ct-&gt;tuplehash
(braket
id|dir
)braket
dot
id|tuple.src.ip
)paren
(brace
id|exp-&gt;seq
op_assign
id|ntohl
c_func
(paren
id|tcph-&gt;seq
)paren
op_plus
id|matchoff
suffix:semicolon
id|exp_ftp_info-&gt;len
op_assign
id|matchlen
suffix:semicolon
id|exp_ftp_info-&gt;ftptype
op_assign
id|search
(braket
id|i
)braket
dot
id|ftptype
suffix:semicolon
id|exp_ftp_info-&gt;port
op_assign
id|array
(braket
l_int|4
)braket
op_lshift
l_int|8
op_or
id|array
(braket
l_int|5
)braket
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Enrico Scholz&squot;s passive FTP to partially RNAT&squot;d ftp&n;&t;&t;   server: it really wants us to connect to a&n;&t;&t;   different IP address.  Simply don&squot;t record it for&n;&t;&t;   NAT. */
id|DEBUGP
c_func
(paren
l_string|&quot;conntrack_ftp: NOT RECORDING: %u,%u,%u,%u != %u.%u.%u.%u&bslash;n&quot;
comma
id|array
(braket
l_int|0
)braket
comma
id|array
(braket
l_int|1
)braket
comma
id|array
(braket
l_int|2
)braket
comma
id|array
(braket
l_int|3
)braket
comma
id|NIPQUAD
c_func
(paren
id|ct-&gt;tuplehash
(braket
id|dir
)braket
dot
id|tuple.src.ip
)paren
)paren
suffix:semicolon
multiline_comment|/* Thanks to Cristiano Lincoln Mattos&n;&t;&t;   &lt;lincoln@cesar.org.br&gt; for reporting this potential&n;&t;&t;   problem (DMZ machines opening holes to internal&n;&t;&t;   networks, or the packet filter itself). */
r_if
c_cond
(paren
op_logical_neg
id|loose
)paren
r_goto
id|out
suffix:semicolon
)brace
id|exp-&gt;tuple
op_assign
(paren
(paren
r_struct
id|ip_conntrack_tuple
)paren
(brace
(brace
id|ct-&gt;tuplehash
(braket
op_logical_neg
id|dir
)braket
dot
id|tuple.src.ip
comma
(brace
l_int|0
)brace
)brace
comma
(brace
id|htonl
c_func
(paren
(paren
id|array
(braket
l_int|0
)braket
op_lshift
l_int|24
)paren
op_or
(paren
id|array
(braket
l_int|1
)braket
op_lshift
l_int|16
)paren
op_or
(paren
id|array
(braket
l_int|2
)braket
op_lshift
l_int|8
)paren
op_or
id|array
(braket
l_int|3
)braket
)paren
comma
(brace
id|htons
c_func
(paren
id|array
(braket
l_int|4
)braket
op_lshift
l_int|8
op_or
id|array
(braket
l_int|5
)braket
)paren
)brace
comma
id|IPPROTO_TCP
)brace
)brace
)paren
suffix:semicolon
id|exp-&gt;mask
op_assign
(paren
(paren
r_struct
id|ip_conntrack_tuple
)paren
(brace
(brace
l_int|0xFFFFFFFF
comma
(brace
l_int|0
)brace
)brace
comma
(brace
l_int|0xFFFFFFFF
comma
(brace
l_int|0xFFFF
)brace
comma
l_int|0xFFFF
)brace
)brace
)paren
suffix:semicolon
id|exp-&gt;expectfn
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Ignore failure; should only happen with NAT */
id|ip_conntrack_expect_related
c_func
(paren
id|ct
comma
op_amp
id|expect
)paren
suffix:semicolon
id|out
suffix:colon
id|UNLOCK_BH
c_func
(paren
op_amp
id|ip_ftp_lock
)paren
suffix:semicolon
r_return
id|NF_ACCEPT
suffix:semicolon
)brace
DECL|variable|ftp
r_static
r_struct
id|ip_conntrack_helper
id|ftp
(braket
id|MAX_PORTS
)braket
suffix:semicolon
DECL|variable|ftp_names
r_static
r_char
id|ftp_names
(braket
id|MAX_PORTS
)braket
(braket
l_int|10
)braket
suffix:semicolon
multiline_comment|/* Not __exit: called from init() */
DECL|function|fini
r_static
r_void
id|fini
c_func
(paren
r_void
)paren
(brace
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
id|ports_c
suffix:semicolon
id|i
op_increment
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;ip_ct_ftp: unregistering helper for port %d&bslash;n&quot;
comma
id|ports
(braket
id|i
)braket
)paren
suffix:semicolon
id|ip_conntrack_helper_unregister
c_func
(paren
op_amp
id|ftp
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
)brace
DECL|function|init
r_static
r_int
id|__init
id|init
c_func
(paren
r_void
)paren
(brace
r_int
id|i
comma
id|ret
suffix:semicolon
r_char
op_star
id|tmpname
suffix:semicolon
r_if
c_cond
(paren
id|ports
(braket
l_int|0
)braket
op_eq
l_int|0
)paren
id|ports
(braket
l_int|0
)braket
op_assign
id|FTP_PORT
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
(paren
id|i
OL
id|MAX_PORTS
)paren
op_logical_and
id|ports
(braket
id|i
)braket
suffix:semicolon
id|i
op_increment
)paren
(brace
id|memset
c_func
(paren
op_amp
id|ftp
(braket
id|i
)braket
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|ip_conntrack_helper
)paren
)paren
suffix:semicolon
id|ftp
(braket
id|i
)braket
dot
id|tuple.src.u.tcp.port
op_assign
id|htons
c_func
(paren
id|ports
(braket
id|i
)braket
)paren
suffix:semicolon
id|ftp
(braket
id|i
)braket
dot
id|tuple.dst.protonum
op_assign
id|IPPROTO_TCP
suffix:semicolon
id|ftp
(braket
id|i
)braket
dot
id|mask.src.u.tcp.port
op_assign
l_int|0xFFFF
suffix:semicolon
id|ftp
(braket
id|i
)braket
dot
id|mask.dst.protonum
op_assign
l_int|0xFFFF
suffix:semicolon
id|ftp
(braket
id|i
)braket
dot
id|max_expected
op_assign
l_int|1
suffix:semicolon
id|ftp
(braket
id|i
)braket
dot
id|timeout
op_assign
l_int|0
suffix:semicolon
id|ftp
(braket
id|i
)braket
dot
id|flags
op_assign
id|IP_CT_HELPER_F_REUSE_EXPECT
suffix:semicolon
id|ftp
(braket
id|i
)braket
dot
id|me
op_assign
id|ip_conntrack_ftp
suffix:semicolon
id|ftp
(braket
id|i
)braket
dot
id|help
op_assign
id|help
suffix:semicolon
id|tmpname
op_assign
op_amp
id|ftp_names
(braket
id|i
)braket
(braket
l_int|0
)braket
suffix:semicolon
r_if
c_cond
(paren
id|ports
(braket
id|i
)braket
op_eq
id|FTP_PORT
)paren
id|sprintf
c_func
(paren
id|tmpname
comma
l_string|&quot;ftp&quot;
)paren
suffix:semicolon
r_else
id|sprintf
c_func
(paren
id|tmpname
comma
l_string|&quot;ftp-%d&quot;
comma
id|ports
(braket
id|i
)braket
)paren
suffix:semicolon
id|ftp
(braket
id|i
)braket
dot
id|name
op_assign
id|tmpname
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;ip_ct_ftp: registering helper for port %d&bslash;n&quot;
comma
id|ports
(braket
id|i
)braket
)paren
suffix:semicolon
id|ret
op_assign
id|ip_conntrack_helper_register
c_func
(paren
op_amp
id|ftp
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|fini
c_func
(paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
id|ports_c
op_increment
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_IP_NF_NAT_NEEDED
DECL|variable|ip_ftp_lock
id|EXPORT_SYMBOL
c_func
(paren
id|ip_ftp_lock
)paren
suffix:semicolon
macro_line|#endif
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|init
id|module_init
c_func
(paren
id|init
)paren
suffix:semicolon
DECL|variable|fini
id|module_exit
c_func
(paren
id|fini
)paren
suffix:semicolon
eof
