multiline_comment|/*&n; * ip_vs_ftp.c: IPVS ftp application module&n; *&n; * Version:&t;$Id: ip_vs_ftp.c,v 1.13 2002/09/15 08:14:08 wensong Exp $&n; *&n; * Authors:&t;Wensong Zhang &lt;wensong@linuxvirtualserver.org&gt;&n; *&n; * Changes:&n; *&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License&n; *&t;as published by the Free Software Foundation; either version&n; *&t;2 of the License, or (at your option) any later version.&n; *&n; * Most code here is taken from ip_masq_ftp.c in kernel 2.2. The difference&n; * is that ip_vs_ftp module handles the reverse direction to ip_masq_ftp.&n; *&n; *&t;&t;IP_MASQ_FTP ftp masquerading module&n; *&n; * Version:&t;@(#)ip_masq_ftp.c 0.04   02/05/96&n; *&n; * Author:&t;Wouter Gadeyne&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/ip.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;net/protocol.h&gt;
macro_line|#include &lt;net/tcp.h&gt;
macro_line|#include &lt;net/ip_vs.h&gt;
DECL|macro|SERVER_STRING
mdefine_line|#define SERVER_STRING &quot;227 Entering Passive Mode (&quot;
DECL|macro|CLIENT_STRING
mdefine_line|#define CLIENT_STRING &quot;PORT &quot;
multiline_comment|/*&n; * List of ports (up to IP_VS_APP_MAX_PORTS) to be handled by helper&n; * First port is set to the default port.&n; */
DECL|variable|ports
r_static
r_int
id|ports
(braket
id|IP_VS_APP_MAX_PORTS
)braket
op_assign
(brace
l_int|21
comma
l_int|0
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;Debug level&n; */
macro_line|#ifdef CONFIG_IP_VS_DEBUG
DECL|variable|debug
r_static
r_int
id|debug
op_assign
l_int|0
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|debug
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
macro_line|#endif
id|MODULE_PARM
c_func
(paren
id|ports
comma
l_string|&quot;1-&quot;
id|__MODULE_STRING
c_func
(paren
id|IP_VS_APP_MAX_PORTS
)paren
l_string|&quot;i&quot;
)paren
suffix:semicolon
multiline_comment|/*&t;Dummy variable */
DECL|variable|ip_vs_ftp_pasv
r_static
r_int
id|ip_vs_ftp_pasv
suffix:semicolon
r_static
r_int
DECL|function|ip_vs_ftp_init_conn
id|ip_vs_ftp_init_conn
c_func
(paren
r_struct
id|ip_vs_app
op_star
id|app
comma
r_struct
id|ip_vs_conn
op_star
id|cp
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|ip_vs_ftp_done_conn
id|ip_vs_ftp_done_conn
c_func
(paren
r_struct
id|ip_vs_app
op_star
id|app
comma
r_struct
id|ip_vs_conn
op_star
id|cp
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Get &lt;addr,port&gt; from the string &quot;xxx.xxx.xxx.xxx,ppp,ppp&quot;, started&n; * with the &quot;pattern&quot; and terminated with the &quot;term&quot; character.&n; * &lt;addr,port&gt; is in network order.&n; */
DECL|function|ip_vs_ftp_get_addrport
r_static
r_int
id|ip_vs_ftp_get_addrport
c_func
(paren
r_char
op_star
id|data
comma
r_char
op_star
id|data_limit
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
id|term
comma
id|__u32
op_star
id|addr
comma
id|__u16
op_star
id|port
comma
r_char
op_star
op_star
id|start
comma
r_char
op_star
op_star
id|end
)paren
(brace
r_int
r_char
id|p1
comma
id|p2
comma
id|p3
comma
id|p4
comma
id|p5
comma
id|p6
suffix:semicolon
r_while
c_loop
(paren
id|data
OL
id|data_limit
)paren
(brace
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
id|data
op_increment
suffix:semicolon
r_continue
suffix:semicolon
)brace
op_star
id|start
op_assign
id|data
op_plus
id|plen
suffix:semicolon
id|p1
op_assign
id|simple_strtoul
c_func
(paren
id|data
op_plus
id|plen
comma
op_amp
id|data
comma
l_int|10
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|data
op_ne
l_char|&squot;,&squot;
)paren
r_continue
suffix:semicolon
id|p2
op_assign
id|simple_strtoul
c_func
(paren
id|data
op_plus
l_int|1
comma
op_amp
id|data
comma
l_int|10
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|data
op_ne
l_char|&squot;,&squot;
)paren
r_continue
suffix:semicolon
id|p3
op_assign
id|simple_strtoul
c_func
(paren
id|data
op_plus
l_int|1
comma
op_amp
id|data
comma
l_int|10
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|data
op_ne
l_char|&squot;,&squot;
)paren
r_continue
suffix:semicolon
id|p4
op_assign
id|simple_strtoul
c_func
(paren
id|data
op_plus
l_int|1
comma
op_amp
id|data
comma
l_int|10
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|data
op_ne
l_char|&squot;,&squot;
)paren
r_continue
suffix:semicolon
id|p5
op_assign
id|simple_strtoul
c_func
(paren
id|data
op_plus
l_int|1
comma
op_amp
id|data
comma
l_int|10
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|data
op_ne
l_char|&squot;,&squot;
)paren
r_continue
suffix:semicolon
id|p6
op_assign
id|simple_strtoul
c_func
(paren
id|data
op_plus
l_int|1
comma
op_amp
id|data
comma
l_int|10
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|data
op_ne
id|term
)paren
r_continue
suffix:semicolon
op_star
id|end
op_assign
id|data
suffix:semicolon
op_star
id|addr
op_assign
(paren
id|p4
op_lshift
l_int|24
)paren
op_or
(paren
id|p3
op_lshift
l_int|16
)paren
op_or
(paren
id|p2
op_lshift
l_int|8
)paren
op_or
id|p1
suffix:semicolon
op_star
id|port
op_assign
(paren
id|p6
op_lshift
l_int|8
)paren
op_or
id|p5
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Look at outgoing ftp packets to catch the response to a PASV command&n; * from the server (inside-to-outside).&n; * When we see one, we build a connection entry with the client address,&n; * client port 0 (unknown at the moment), the server address and the&n; * server port.  Mark the current connection entry as a control channel&n; * of the new entry. All this work is just to make the data connection&n; * can be scheduled to the right server later.&n; *&n; * The outgoing packet should be something like&n; *   &quot;227 Entering Passive Mode (xxx,xxx,xxx,xxx,ppp,ppp)&quot;.&n; * xxx,xxx,xxx,xxx is the server address, ppp,ppp is the server port number.&n; */
DECL|function|ip_vs_ftp_out
r_static
r_int
id|ip_vs_ftp_out
c_func
(paren
r_struct
id|ip_vs_app
op_star
id|app
comma
r_struct
id|ip_vs_conn
op_star
id|cp
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|iphdr
op_star
id|iph
suffix:semicolon
r_struct
id|tcphdr
op_star
id|th
suffix:semicolon
r_char
op_star
id|data
comma
op_star
id|data_limit
suffix:semicolon
r_char
op_star
id|start
comma
op_star
id|end
suffix:semicolon
id|__u32
id|from
suffix:semicolon
id|__u16
id|port
suffix:semicolon
r_struct
id|ip_vs_conn
op_star
id|n_cp
suffix:semicolon
r_char
id|buf
(braket
l_int|24
)braket
suffix:semicolon
multiline_comment|/* xxx.xxx.xxx.xxx,ppp,ppp&bslash;000 */
r_int
id|buf_len
suffix:semicolon
r_int
id|diff
suffix:semicolon
multiline_comment|/* Only useful for established sessions */
r_if
c_cond
(paren
id|cp-&gt;state
op_ne
id|IP_VS_TCP_S_ESTABLISHED
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|cp-&gt;app_data
op_eq
op_amp
id|ip_vs_ftp_pasv
)paren
(brace
id|iph
op_assign
id|skb-&gt;nh.iph
suffix:semicolon
id|th
op_assign
(paren
r_struct
id|tcphdr
op_star
)paren
op_amp
(paren
(paren
(paren
r_char
op_star
)paren
id|iph
)paren
(braket
id|iph-&gt;ihl
op_star
l_int|4
)braket
)paren
suffix:semicolon
id|data
op_assign
(paren
r_char
op_star
)paren
id|th
op_plus
(paren
id|th-&gt;doff
op_lshift
l_int|2
)paren
suffix:semicolon
id|data_limit
op_assign
id|skb-&gt;tail
suffix:semicolon
r_if
c_cond
(paren
id|ip_vs_ftp_get_addrport
c_func
(paren
id|data
comma
id|data_limit
comma
id|SERVER_STRING
comma
r_sizeof
(paren
id|SERVER_STRING
)paren
op_minus
l_int|1
comma
l_char|&squot;)&squot;
comma
op_amp
id|from
comma
op_amp
id|port
comma
op_amp
id|start
comma
op_amp
id|end
)paren
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|IP_VS_DBG
c_func
(paren
l_int|1
op_minus
id|debug
comma
l_string|&quot;PASV response (%u.%u.%u.%u:%d) -&gt; &quot;
l_string|&quot;%u.%u.%u.%u:%d detected&bslash;n&quot;
comma
id|NIPQUAD
c_func
(paren
id|from
)paren
comma
id|ntohs
c_func
(paren
id|port
)paren
comma
id|NIPQUAD
c_func
(paren
id|cp-&gt;caddr
)paren
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Now update or create an connection entry for it&n;&t;&t; */
id|n_cp
op_assign
id|ip_vs_conn_out_get
c_func
(paren
id|iph-&gt;protocol
comma
id|from
comma
id|port
comma
id|cp-&gt;caddr
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|n_cp
)paren
(brace
id|n_cp
op_assign
id|ip_vs_conn_new
c_func
(paren
id|IPPROTO_TCP
comma
id|cp-&gt;caddr
comma
l_int|0
comma
id|cp-&gt;vaddr
comma
id|port
comma
id|from
comma
id|port
comma
id|IP_VS_CONN_F_NO_CPORT
comma
id|cp-&gt;dest
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|n_cp
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* add its controller */
id|ip_vs_control_add
c_func
(paren
id|n_cp
comma
id|cp
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Replace the old passive address with the new one&n;&t;&t; */
id|from
op_assign
id|n_cp-&gt;vaddr
suffix:semicolon
id|port
op_assign
id|n_cp-&gt;vport
suffix:semicolon
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%d,%d,%d,%d,%d,%d&quot;
comma
id|NIPQUAD
c_func
(paren
id|from
)paren
comma
id|port
op_amp
l_int|255
comma
id|port
op_rshift
l_int|8
op_amp
l_int|255
)paren
suffix:semicolon
id|buf_len
op_assign
id|strlen
c_func
(paren
id|buf
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Calculate required delta-offset to keep TCP happy&n;&t;&t; */
id|diff
op_assign
id|buf_len
op_minus
(paren
id|end
op_minus
id|start
)paren
suffix:semicolon
r_if
c_cond
(paren
id|diff
op_eq
l_int|0
)paren
(brace
multiline_comment|/* simply replace it with new passive address */
id|memcpy
c_func
(paren
id|start
comma
id|buf
comma
id|buf_len
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* fixme: return value isn&squot;t checked here */
id|ip_vs_skb_replace
c_func
(paren
id|skb
comma
id|GFP_ATOMIC
comma
id|start
comma
id|end
op_minus
id|start
comma
id|buf
comma
id|buf_len
)paren
suffix:semicolon
)brace
id|cp-&gt;app_data
op_assign
l_int|NULL
suffix:semicolon
id|ip_vs_tcp_conn_listen
c_func
(paren
id|n_cp
)paren
suffix:semicolon
id|ip_vs_conn_put
c_func
(paren
id|n_cp
)paren
suffix:semicolon
r_return
id|diff
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Look at incoming ftp packets to catch the PASV/PORT command&n; * (outside-to-inside).&n; *&n; * The incoming packet having the PORT command should be something like&n; *      &quot;PORT xxx,xxx,xxx,xxx,ppp,ppp&bslash;n&quot;.&n; * xxx,xxx,xxx,xxx is the client address, ppp,ppp is the client port number.&n; * In this case, we create a connection entry using the client address and&n; * port, so that the active ftp data connection from the server can reach&n; * the client.&n; */
DECL|function|ip_vs_ftp_in
r_static
r_int
id|ip_vs_ftp_in
c_func
(paren
r_struct
id|ip_vs_app
op_star
id|app
comma
r_struct
id|ip_vs_conn
op_star
id|cp
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|iphdr
op_star
id|iph
suffix:semicolon
r_struct
id|tcphdr
op_star
id|th
suffix:semicolon
r_char
op_star
id|data
comma
op_star
id|data_start
comma
op_star
id|data_limit
suffix:semicolon
r_char
op_star
id|start
comma
op_star
id|end
suffix:semicolon
id|__u32
id|to
suffix:semicolon
id|__u16
id|port
suffix:semicolon
r_struct
id|ip_vs_conn
op_star
id|n_cp
suffix:semicolon
multiline_comment|/* Only useful for established sessions */
r_if
c_cond
(paren
id|cp-&gt;state
op_ne
id|IP_VS_TCP_S_ESTABLISHED
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * Detecting whether it is passive&n;&t; */
id|iph
op_assign
id|skb-&gt;nh.iph
suffix:semicolon
id|th
op_assign
(paren
r_struct
id|tcphdr
op_star
)paren
op_amp
(paren
(paren
(paren
r_char
op_star
)paren
id|iph
)paren
(braket
id|iph-&gt;ihl
op_star
l_int|4
)braket
)paren
suffix:semicolon
multiline_comment|/* Since there may be OPTIONS in the TCP packet and the HLEN is&n;&t;   the length of the header in 32-bit multiples, it is accurate&n;&t;   to calculate data address by th+HLEN*4 */
id|data
op_assign
id|data_start
op_assign
(paren
r_char
op_star
)paren
id|th
op_plus
(paren
id|th-&gt;doff
op_lshift
l_int|2
)paren
suffix:semicolon
id|data_limit
op_assign
id|skb-&gt;tail
suffix:semicolon
r_while
c_loop
(paren
id|data
OL
id|data_limit
)paren
(brace
r_if
c_cond
(paren
id|strnicmp
c_func
(paren
id|data
comma
l_string|&quot;PASV&bslash;r&bslash;n&quot;
comma
l_int|6
)paren
op_eq
l_int|0
)paren
(brace
id|IP_VS_DBG
c_func
(paren
l_int|1
op_minus
id|debug
comma
l_string|&quot;got PASV at %d of %d&bslash;n&quot;
comma
id|data
op_minus
id|data_start
comma
id|data_limit
op_minus
id|data_start
)paren
suffix:semicolon
id|cp-&gt;app_data
op_assign
op_amp
id|ip_vs_ftp_pasv
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|data
op_increment
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * To support virtual FTP server, the scenerio is as follows:&n;&t; *       FTP client ----&gt; Load Balancer ----&gt; FTP server&n;&t; * First detect the port number in the application data,&n;&t; * then create a new connection entry for the coming data&n;&t; * connection.&n;&t; */
id|data
op_assign
id|data_start
suffix:semicolon
id|data_limit
op_assign
id|skb-&gt;h.raw
op_plus
id|skb-&gt;len
op_minus
l_int|18
suffix:semicolon
r_if
c_cond
(paren
id|ip_vs_ftp_get_addrport
c_func
(paren
id|data
comma
id|data_limit
comma
id|CLIENT_STRING
comma
r_sizeof
(paren
id|CLIENT_STRING
)paren
op_minus
l_int|1
comma
l_char|&squot;&bslash;r&squot;
comma
op_amp
id|to
comma
op_amp
id|port
comma
op_amp
id|start
comma
op_amp
id|end
)paren
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|IP_VS_DBG
c_func
(paren
l_int|1
op_minus
id|debug
comma
l_string|&quot;PORT %u.%u.%u.%u:%d detected&bslash;n&quot;
comma
id|NIPQUAD
c_func
(paren
id|to
)paren
comma
id|ntohs
c_func
(paren
id|port
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Now update or create a connection entry for it&n;&t; */
id|IP_VS_DBG
c_func
(paren
l_int|1
op_minus
id|debug
comma
l_string|&quot;protocol %s %u.%u.%u.%u:%d %u.%u.%u.%u:%d&bslash;n&quot;
comma
id|ip_vs_proto_name
c_func
(paren
id|iph-&gt;protocol
)paren
comma
id|NIPQUAD
c_func
(paren
id|to
)paren
comma
id|ntohs
c_func
(paren
id|port
)paren
comma
id|NIPQUAD
c_func
(paren
id|iph-&gt;daddr
)paren
comma
l_int|0
)paren
suffix:semicolon
id|n_cp
op_assign
id|ip_vs_conn_in_get
c_func
(paren
id|iph-&gt;protocol
comma
id|to
comma
id|port
comma
id|iph-&gt;daddr
comma
id|htons
c_func
(paren
id|ntohs
c_func
(paren
id|cp-&gt;vport
)paren
op_minus
l_int|1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|n_cp
)paren
(brace
id|n_cp
op_assign
id|ip_vs_conn_new
c_func
(paren
id|IPPROTO_TCP
comma
id|to
comma
id|port
comma
id|cp-&gt;vaddr
comma
id|htons
c_func
(paren
id|ntohs
c_func
(paren
id|cp-&gt;vport
)paren
op_minus
l_int|1
)paren
comma
id|cp-&gt;daddr
comma
id|htons
c_func
(paren
id|ntohs
c_func
(paren
id|cp-&gt;dport
)paren
op_minus
l_int|1
)paren
comma
l_int|0
comma
id|cp-&gt;dest
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|n_cp
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* add its controller */
id|ip_vs_control_add
c_func
(paren
id|n_cp
comma
id|cp
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *&t;Move tunnel to listen state&n;&t; */
id|ip_vs_tcp_conn_listen
c_func
(paren
id|n_cp
)paren
suffix:semicolon
id|ip_vs_conn_put
c_func
(paren
id|n_cp
)paren
suffix:semicolon
multiline_comment|/* no diff required for incoming packets */
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|ip_vs_ftp
r_static
r_struct
id|ip_vs_app
id|ip_vs_ftp
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;ftp&quot;
comma
dot
id|type
op_assign
id|IP_VS_APP_TYPE_FTP
comma
dot
id|protocol
op_assign
id|IPPROTO_TCP
comma
dot
id|module
op_assign
id|THIS_MODULE
comma
dot
id|incs_list
op_assign
id|LIST_HEAD_INIT
c_func
(paren
id|ip_vs_ftp.incs_list
)paren
comma
dot
id|init_conn
op_assign
id|ip_vs_ftp_init_conn
comma
dot
id|done_conn
op_assign
id|ip_vs_ftp_done_conn
comma
dot
id|bind_conn
op_assign
l_int|NULL
comma
dot
id|unbind_conn
op_assign
l_int|NULL
comma
dot
id|pkt_out
op_assign
id|ip_vs_ftp_out
comma
dot
id|pkt_in
op_assign
id|ip_vs_ftp_in
comma
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;ip_vs_ftp initialization&n; */
DECL|function|ip_vs_ftp_init
r_static
r_int
id|__init
id|ip_vs_ftp_init
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
r_struct
id|ip_vs_app
op_star
id|app
op_assign
op_amp
id|ip_vs_ftp
suffix:semicolon
id|ret
op_assign
id|register_ip_vs_app
c_func
(paren
id|app
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_return
id|ret
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
id|IP_VS_APP_MAX_PORTS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|ports
(braket
id|i
)braket
)paren
r_continue
suffix:semicolon
id|ret
op_assign
id|register_ip_vs_app_inc
c_func
(paren
id|app
comma
id|app-&gt;protocol
comma
id|ports
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
r_break
suffix:semicolon
id|IP_VS_DBG
c_func
(paren
l_int|1
op_minus
id|debug
comma
l_string|&quot;%s: loaded support on port[%d] = %d&bslash;n&quot;
comma
id|app-&gt;name
comma
id|i
comma
id|ports
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ret
)paren
id|unregister_ip_vs_app
c_func
(paren
id|app
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;ip_vs_ftp finish.&n; */
DECL|function|ip_vs_ftp_exit
r_static
r_void
id|__exit
id|ip_vs_ftp_exit
c_func
(paren
r_void
)paren
(brace
id|unregister_ip_vs_app
c_func
(paren
op_amp
id|ip_vs_ftp
)paren
suffix:semicolon
)brace
DECL|variable|ip_vs_ftp_init
id|module_init
c_func
(paren
id|ip_vs_ftp_init
)paren
suffix:semicolon
DECL|variable|ip_vs_ftp_exit
id|module_exit
c_func
(paren
id|ip_vs_ftp_exit
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
