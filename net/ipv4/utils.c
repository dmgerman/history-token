multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;Various kernel-resident INET utility functions; mainly&n; *&t;&t;for format conversion and debugging output.&n; *&n; * Version:&t;$Id: utils.c,v 1.8 2000/10/03 07:29:01 anton Exp $&n; *&n; * Author:&t;Fred N. van Kempen, &lt;waltje@uWalt.NL.Mugnet.ORG&gt;&n; *&n; * Fixes:&n; *&t;&t;Alan Cox&t;:&t;verify_area check.&n; *&t;&t;Alan Cox&t;:&t;removed old debugging.&n; *&t;&t;Andi Kleen&t;:&t;add net_ratelimit()  &n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;stdarg.h&gt;
macro_line|#include &lt;linux/inet.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/etherdevice.h&gt;
macro_line|#include &lt;net/ip.h&gt;
macro_line|#include &lt;net/protocol.h&gt;
macro_line|#include &lt;net/tcp.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
multiline_comment|/*&n; *&t;Display an IP address in readable format. &n; */
DECL|function|in_ntoa
r_char
op_star
id|in_ntoa
c_func
(paren
id|__u32
id|in
)paren
(brace
r_static
r_char
id|buff
(braket
l_int|18
)braket
suffix:semicolon
r_char
op_star
id|p
suffix:semicolon
id|p
op_assign
(paren
r_char
op_star
)paren
op_amp
id|in
suffix:semicolon
id|sprintf
c_func
(paren
id|buff
comma
l_string|&quot;%d.%d.%d.%d&quot;
comma
(paren
id|p
(braket
l_int|0
)braket
op_amp
l_int|255
)paren
comma
(paren
id|p
(braket
l_int|1
)braket
op_amp
l_int|255
)paren
comma
(paren
id|p
(braket
l_int|2
)braket
op_amp
l_int|255
)paren
comma
(paren
id|p
(braket
l_int|3
)braket
op_amp
l_int|255
)paren
)paren
suffix:semicolon
r_return
id|buff
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Convert an ASCII string to binary IP. &n; */
DECL|function|in_aton
id|__u32
id|in_aton
c_func
(paren
r_const
r_char
op_star
id|str
)paren
(brace
r_int
r_int
id|l
suffix:semicolon
r_int
r_int
id|val
suffix:semicolon
r_int
id|i
suffix:semicolon
id|l
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
l_int|4
suffix:semicolon
id|i
op_increment
)paren
(brace
id|l
op_lshift_assign
l_int|8
suffix:semicolon
r_if
c_cond
(paren
op_star
id|str
op_ne
l_char|&squot;&bslash;0&squot;
)paren
(brace
id|val
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
op_star
id|str
op_ne
l_char|&squot;&bslash;0&squot;
op_logical_and
op_star
id|str
op_ne
l_char|&squot;.&squot;
)paren
(brace
id|val
op_mul_assign
l_int|10
suffix:semicolon
id|val
op_add_assign
op_star
id|str
op_minus
l_char|&squot;0&squot;
suffix:semicolon
id|str
op_increment
suffix:semicolon
)brace
id|l
op_or_assign
id|val
suffix:semicolon
r_if
c_cond
(paren
op_star
id|str
op_ne
l_char|&squot;&bslash;0&squot;
)paren
id|str
op_increment
suffix:semicolon
)brace
)brace
r_return
id|htonl
c_func
(paren
id|l
)paren
suffix:semicolon
)brace
eof
