multiline_comment|/* FTP extension for IP connection tracking. */
multiline_comment|/* (C) 1999-2001 Paul `Rusty&squot; Russell  &n; * (C) 2002-2004 Netfilter Core Team &lt;coreteam@netfilter.org&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
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
macro_line|#include &lt;linux/moduleparam.h&gt;
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Rusty Russell &lt;rusty@rustcorp.com.au&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;ftp connection tracking helper&quot;
)paren
suffix:semicolon
multiline_comment|/* This is slow, but it&squot;s simple. --RR */
DECL|variable|ftp_buffer
r_static
r_char
id|ftp_buffer
(braket
l_int|65536
)braket
suffix:semicolon
r_static
id|DECLARE_LOCK
c_func
(paren
id|ip_ftp_lock
)paren
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
suffix:semicolon
id|module_param_array
c_func
(paren
id|ports
comma
r_int
comma
op_amp
id|ports_c
comma
l_int|0400
)paren
suffix:semicolon
DECL|variable|loose
r_static
r_int
id|loose
suffix:semicolon
id|module_param
c_func
(paren
id|loose
comma
r_int
comma
l_int|0600
)paren
suffix:semicolon
DECL|variable|ip_nat_ftp_hook
r_int
r_int
(paren
op_star
id|ip_nat_ftp_hook
)paren
(paren
r_struct
id|sk_buff
op_star
op_star
id|pskb
comma
r_enum
id|ip_conntrack_info
id|ctinfo
comma
r_enum
id|ip_ct_ftp_type
id|type
comma
r_int
r_int
id|matchoff
comma
r_int
r_int
id|matchlen
comma
r_struct
id|ip_conntrack_expect
op_star
id|exp
comma
id|u32
op_star
id|seq
)paren
suffix:semicolon
DECL|variable|ip_nat_ftp_hook
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|ip_nat_ftp_hook
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
id|try_epsv_response
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
id|try_epsv_response
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
DECL|function|try_epsv_response
r_static
r_int
id|try_epsv_response
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
id|DEBUGP
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
multiline_comment|/* Look up to see if we&squot;re just after a &bslash;n. */
DECL|function|find_nl_seq
r_static
r_int
id|find_nl_seq
c_func
(paren
id|u16
id|seq
comma
r_const
r_struct
id|ip_ct_ftp_master
op_star
id|info
comma
r_int
id|dir
)paren
(brace
r_int
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
id|info-&gt;seq_aft_nl_num
(braket
id|dir
)braket
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|info-&gt;seq_aft_nl
(braket
id|dir
)braket
(braket
id|i
)braket
op_eq
id|seq
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* We don&squot;t update if it&squot;s older than what we have. */
DECL|function|update_nl_seq
r_static
r_void
id|update_nl_seq
c_func
(paren
id|u16
id|nl_seq
comma
r_struct
id|ip_ct_ftp_master
op_star
id|info
comma
r_int
id|dir
)paren
(brace
r_int
r_int
id|i
comma
id|oldest
op_assign
id|NUM_SEQ_TO_REMEMBER
suffix:semicolon
multiline_comment|/* Look for oldest: if we find exact match, we&squot;re done. */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|info-&gt;seq_aft_nl_num
(braket
id|dir
)braket
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|info-&gt;seq_aft_nl
(braket
id|dir
)braket
(braket
id|i
)braket
op_eq
id|nl_seq
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|oldest
op_eq
id|info-&gt;seq_aft_nl_num
(braket
id|dir
)braket
op_logical_or
id|before
c_func
(paren
id|info-&gt;seq_aft_nl
(braket
id|dir
)braket
(braket
id|i
)braket
comma
id|oldest
)paren
)paren
id|oldest
op_assign
id|i
suffix:semicolon
)brace
r_if
c_cond
(paren
id|info-&gt;seq_aft_nl_num
(braket
id|dir
)braket
OL
id|NUM_SEQ_TO_REMEMBER
)paren
id|info-&gt;seq_aft_nl
(braket
id|dir
)braket
(braket
id|info-&gt;seq_aft_nl_num
(braket
id|dir
)braket
op_increment
)braket
op_assign
id|nl_seq
suffix:semicolon
r_else
r_if
c_cond
(paren
id|oldest
op_ne
id|NUM_SEQ_TO_REMEMBER
)paren
id|info-&gt;seq_aft_nl
(braket
id|dir
)braket
(braket
id|oldest
)braket
op_assign
id|nl_seq
suffix:semicolon
)brace
DECL|function|help
r_static
r_int
id|help
c_func
(paren
r_struct
id|sk_buff
op_star
op_star
id|pskb
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
r_int
r_int
id|dataoff
comma
id|datalen
suffix:semicolon
r_struct
id|tcphdr
id|_tcph
comma
op_star
id|th
suffix:semicolon
r_char
op_star
id|fb_ptr
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|u32
id|seq
comma
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
op_star
id|exp
suffix:semicolon
r_int
r_int
id|i
suffix:semicolon
r_int
id|found
op_assign
l_int|0
comma
id|ends_in_nl
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
id|th
op_assign
id|skb_header_pointer
c_func
(paren
op_star
id|pskb
comma
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nh.iph-&gt;ihl
op_star
l_int|4
comma
r_sizeof
(paren
id|_tcph
)paren
comma
op_amp
id|_tcph
)paren
suffix:semicolon
r_if
c_cond
(paren
id|th
op_eq
l_int|NULL
)paren
r_return
id|NF_ACCEPT
suffix:semicolon
id|dataoff
op_assign
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nh.iph-&gt;ihl
op_star
l_int|4
op_plus
id|th-&gt;doff
op_star
l_int|4
suffix:semicolon
multiline_comment|/* No data? */
r_if
c_cond
(paren
id|dataoff
op_ge
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|len
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;ftp: pskblen = %u&bslash;n&quot;
comma
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|len
)paren
suffix:semicolon
r_return
id|NF_ACCEPT
suffix:semicolon
)brace
id|datalen
op_assign
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|len
op_minus
id|dataoff
suffix:semicolon
id|LOCK_BH
c_func
(paren
op_amp
id|ip_ftp_lock
)paren
suffix:semicolon
id|fb_ptr
op_assign
id|skb_header_pointer
c_func
(paren
op_star
id|pskb
comma
id|dataoff
comma
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|len
op_minus
id|dataoff
comma
id|ftp_buffer
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
id|fb_ptr
op_eq
l_int|NULL
)paren
suffix:semicolon
id|ends_in_nl
op_assign
(paren
id|fb_ptr
(braket
id|datalen
op_minus
l_int|1
)braket
op_eq
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
id|seq
op_assign
id|ntohl
c_func
(paren
id|th-&gt;seq
)paren
op_plus
id|datalen
suffix:semicolon
multiline_comment|/* Look up to see if we&squot;re just after a &bslash;n. */
r_if
c_cond
(paren
op_logical_neg
id|find_nl_seq
c_func
(paren
id|ntohl
c_func
(paren
id|th-&gt;seq
)paren
comma
id|ct_ftp_info
comma
id|dir
)paren
)paren
(brace
multiline_comment|/* Now if this ends in &bslash;n, update ftp info. */
id|DEBUGP
c_func
(paren
l_string|&quot;ip_conntrack_ftp_help: wrong seq pos %s(%u) or %s(%u)&bslash;n&quot;
comma
id|ct_ftp_info-&gt;seq_aft_nl
(braket
l_int|0
)braket
(braket
id|dir
)braket
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
id|ret
op_assign
id|NF_ACCEPT
suffix:semicolon
r_goto
id|out_update_nl
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
id|ARRAY_SIZE
c_func
(paren
id|search
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
id|fb_ptr
comma
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|len
op_minus
id|dataoff
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
multiline_comment|/* We don&squot;t usually drop packets.  After all, this is&n;&t;&t;   connection tracking, not packet filtering.&n;&t;&t;   However, it is necessary for accurate tracking in&n;&t;&t;   this case. */
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
id|th-&gt;seq
)paren
comma
id|datalen
)paren
suffix:semicolon
id|ret
op_assign
id|NF_DROP
suffix:semicolon
r_goto
id|out
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
(brace
multiline_comment|/* No match */
id|ret
op_assign
id|NF_ACCEPT
suffix:semicolon
r_goto
id|out_update_nl
suffix:semicolon
)brace
id|DEBUGP
c_func
(paren
l_string|&quot;conntrack_ftp: match `%s&squot; (%u bytes at %u)&bslash;n&quot;
comma
id|fb_ptr
op_plus
id|matchoff
comma
id|matchlen
comma
id|ntohl
c_func
(paren
id|th-&gt;seq
)paren
op_plus
id|matchoff
)paren
suffix:semicolon
multiline_comment|/* Allocate expectation which will be inserted */
id|exp
op_assign
id|ip_conntrack_expect_alloc
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|exp
op_eq
l_int|NULL
)paren
(brace
id|ret
op_assign
id|NF_DROP
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/* We refer to the reverse direction (&quot;!dir&quot;) tuples here,&n;&t; * because we&squot;re expecting something in the other direction.&n;&t; * Doesn&squot;t matter unless NAT is happening.  */
id|exp-&gt;tuple.dst.ip
op_assign
id|ct-&gt;tuplehash
(braket
op_logical_neg
id|dir
)braket
dot
id|tuple.dst.ip
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
op_ne
id|ct-&gt;tuplehash
(braket
id|dir
)braket
dot
id|tuple.src.ip
)paren
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
(brace
id|ret
op_assign
id|NF_ACCEPT
suffix:semicolon
id|ip_conntrack_expect_free
c_func
(paren
id|exp
)paren
suffix:semicolon
r_goto
id|out_update_nl
suffix:semicolon
)brace
id|exp-&gt;tuple.dst.ip
op_assign
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
suffix:semicolon
)brace
id|exp-&gt;tuple.src.ip
op_assign
id|ct-&gt;tuplehash
(braket
op_logical_neg
id|dir
)braket
dot
id|tuple.src.ip
suffix:semicolon
id|exp-&gt;tuple.dst.u.tcp.port
op_assign
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
suffix:semicolon
id|exp-&gt;tuple.src.u.tcp.port
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Don&squot;t care. */
id|exp-&gt;tuple.dst.protonum
op_assign
id|IPPROTO_TCP
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
dot
id|tcp
op_assign
(brace
l_int|0xFFFF
)brace
)brace
comma
l_int|0xFF
)brace
)brace
)paren
suffix:semicolon
id|exp-&gt;expectfn
op_assign
l_int|NULL
suffix:semicolon
id|exp-&gt;master
op_assign
id|ct
suffix:semicolon
multiline_comment|/* Now, NAT might want to mangle the packet, and register the&n;&t; * (possibly changed) expectation itself. */
r_if
c_cond
(paren
id|ip_nat_ftp_hook
)paren
id|ret
op_assign
id|ip_nat_ftp_hook
c_func
(paren
id|pskb
comma
id|ctinfo
comma
id|search
(braket
id|i
)braket
dot
id|ftptype
comma
id|matchoff
comma
id|matchlen
comma
id|exp
comma
op_amp
id|seq
)paren
suffix:semicolon
r_else
(brace
multiline_comment|/* Can&squot;t expect this?  Best to drop packet now. */
r_if
c_cond
(paren
id|ip_conntrack_expect_related
c_func
(paren
id|exp
)paren
op_ne
l_int|0
)paren
(brace
id|ip_conntrack_expect_free
c_func
(paren
id|exp
)paren
suffix:semicolon
id|ret
op_assign
id|NF_DROP
suffix:semicolon
)brace
r_else
id|ret
op_assign
id|NF_ACCEPT
suffix:semicolon
)brace
id|out_update_nl
suffix:colon
multiline_comment|/* Now if this ends in &bslash;n, update ftp info.  Seq may have been&n;&t; * adjusted by NAT code. */
r_if
c_cond
(paren
id|ends_in_nl
)paren
id|update_nl_seq
c_func
(paren
id|seq
comma
id|ct_ftp_info
comma
id|dir
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
id|ret
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
id|ports_c
op_eq
l_int|0
)paren
id|ports
(braket
id|ports_c
op_increment
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
id|i
OL
id|ports_c
suffix:semicolon
id|i
op_increment
)paren
(brace
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
l_int|0xFF
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
l_int|5
op_star
l_int|60
suffix:semicolon
multiline_comment|/* 5 minutes */
id|ftp
(braket
id|i
)braket
dot
id|me
op_assign
id|THIS_MODULE
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
)brace
r_return
l_int|0
suffix:semicolon
)brace
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
