multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * Copyright (C) Jonathan Naylor G4KLX (g4klx@g4klx.demon.co.uk)&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/sockios.h&gt;
macro_line|#include &lt;linux/net.h&gt;
macro_line|#include &lt;net/ax25.h&gt;
macro_line|#include &lt;linux/inet.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/if_arp.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/termios.h&gt;&t;/* For TIOCINQ/OUTQ */
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/notifier.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/netfilter.h&gt;
macro_line|#include &lt;linux/sysctl.h&gt;
macro_line|#include &lt;net/ip.h&gt;
macro_line|#include &lt;net/arp.h&gt;
multiline_comment|/*&n; *&t;IP over AX.25 encapsulation.&n; */
multiline_comment|/*&n; *&t;Shove an AX.25 UI header on an IP packet and handle ARP&n; */
macro_line|#ifdef CONFIG_INET
DECL|function|ax25_encapsulate
r_int
id|ax25_encapsulate
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|net_device
op_star
id|dev
comma
r_int
r_int
id|type
comma
r_void
op_star
id|daddr
comma
r_void
op_star
id|saddr
comma
r_int
id|len
)paren
(brace
r_int
r_char
op_star
id|buff
suffix:semicolon
multiline_comment|/* they sometimes come back to us... */
r_if
c_cond
(paren
id|type
op_eq
id|ETH_P_AX25
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* header is an AX.25 UI frame from us to them */
id|buff
op_assign
id|skb_push
c_func
(paren
id|skb
comma
id|AX25_HEADER_LEN
)paren
suffix:semicolon
op_star
id|buff
op_increment
op_assign
l_int|0x00
suffix:semicolon
multiline_comment|/* KISS DATA */
r_if
c_cond
(paren
id|daddr
op_ne
l_int|NULL
)paren
id|memcpy
c_func
(paren
id|buff
comma
id|daddr
comma
id|dev-&gt;addr_len
)paren
suffix:semicolon
multiline_comment|/* Address specified */
id|buff
(braket
l_int|6
)braket
op_and_assign
op_complement
id|AX25_CBIT
suffix:semicolon
id|buff
(braket
l_int|6
)braket
op_and_assign
op_complement
id|AX25_EBIT
suffix:semicolon
id|buff
(braket
l_int|6
)braket
op_or_assign
id|AX25_SSSID_SPARE
suffix:semicolon
id|buff
op_add_assign
id|AX25_ADDR_LEN
suffix:semicolon
r_if
c_cond
(paren
id|saddr
op_ne
l_int|NULL
)paren
id|memcpy
c_func
(paren
id|buff
comma
id|saddr
comma
id|dev-&gt;addr_len
)paren
suffix:semicolon
r_else
id|memcpy
c_func
(paren
id|buff
comma
id|dev-&gt;dev_addr
comma
id|dev-&gt;addr_len
)paren
suffix:semicolon
id|buff
(braket
l_int|6
)braket
op_and_assign
op_complement
id|AX25_CBIT
suffix:semicolon
id|buff
(braket
l_int|6
)braket
op_or_assign
id|AX25_EBIT
suffix:semicolon
id|buff
(braket
l_int|6
)braket
op_or_assign
id|AX25_SSSID_SPARE
suffix:semicolon
id|buff
op_add_assign
id|AX25_ADDR_LEN
suffix:semicolon
op_star
id|buff
op_increment
op_assign
id|AX25_UI
suffix:semicolon
multiline_comment|/* UI */
multiline_comment|/* Append a suitable AX.25 PID */
r_switch
c_cond
(paren
id|type
)paren
(brace
r_case
id|ETH_P_IP
suffix:colon
op_star
id|buff
op_increment
op_assign
id|AX25_P_IP
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ETH_P_ARP
suffix:colon
op_star
id|buff
op_increment
op_assign
id|AX25_P_ARP
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;AX.25: ax25_encapsulate - wrong protocol type 0x%2.2x&bslash;n&quot;
comma
id|type
)paren
suffix:semicolon
op_star
id|buff
op_increment
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|daddr
op_ne
l_int|NULL
)paren
r_return
id|AX25_HEADER_LEN
suffix:semicolon
r_return
op_minus
id|AX25_HEADER_LEN
suffix:semicolon
multiline_comment|/* Unfinished header */
)brace
DECL|function|ax25_rebuild_header
r_int
id|ax25_rebuild_header
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|sk_buff
op_star
id|ourskb
suffix:semicolon
r_int
r_char
op_star
id|bp
op_assign
id|skb-&gt;data
suffix:semicolon
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
id|ax25_address
op_star
id|src
comma
op_star
id|dst
suffix:semicolon
id|ax25_dev
op_star
id|ax25_dev
suffix:semicolon
id|ax25_route
id|_route
comma
op_star
id|route
op_assign
op_amp
id|_route
suffix:semicolon
id|ax25_cb
op_star
id|ax25
suffix:semicolon
id|dst
op_assign
(paren
id|ax25_address
op_star
)paren
(paren
id|bp
op_plus
l_int|1
)paren
suffix:semicolon
id|src
op_assign
(paren
id|ax25_address
op_star
)paren
(paren
id|bp
op_plus
l_int|8
)paren
suffix:semicolon
r_if
c_cond
(paren
id|arp_find
c_func
(paren
id|bp
op_plus
l_int|1
comma
id|skb
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|route
op_assign
id|ax25_rt_find_route
c_func
(paren
id|route
comma
id|dst
comma
l_int|NULL
)paren
suffix:semicolon
id|dev
op_assign
id|route-&gt;dev
suffix:semicolon
r_if
c_cond
(paren
id|dev
op_eq
l_int|NULL
)paren
id|dev
op_assign
id|skb-&gt;dev
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ax25_dev
op_assign
id|ax25_dev_ax25dev
c_func
(paren
id|dev
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
r_goto
id|put
suffix:semicolon
)brace
r_if
c_cond
(paren
id|bp
(braket
l_int|16
)braket
op_eq
id|AX25_P_IP
)paren
(brace
r_if
c_cond
(paren
id|route-&gt;ip_mode
op_eq
l_char|&squot;V&squot;
op_logical_or
(paren
id|route-&gt;ip_mode
op_eq
l_char|&squot; &squot;
op_logical_and
id|ax25_dev-&gt;values
(braket
id|AX25_VALUES_IPDEFMODE
)braket
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; *&t;We copy the buffer and release the original thereby&n;&t;&t;&t; *&t;keeping it straight&n;&t;&t;&t; *&n;&t;&t;&t; *&t;Note: we report 1 back so the caller will&n;&t;&t;&t; *&t;not feed the frame direct to the physical device&n;&t;&t;&t; *&t;We don&squot;t want that to happen. (It won&squot;t be upset&n;&t;&t;&t; *&t;as we have pulled the frame from the queue by&n;&t;&t;&t; *&t;freeing it).&n;&t;&t;&t; *&n;&t;&t;&t; *&t;NB: TCP modifies buffers that are still&n;&t;&t;&t; *&t;on a device queue, thus we use skb_copy()&n;&t;&t;&t; *      instead of using skb_clone() unless this&n;&t;&t;&t; *&t;gets fixed.&n;&t;&t;&t; */
id|ax25_address
id|src_c
suffix:semicolon
id|ax25_address
id|dst_c
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ourskb
op_assign
id|skb_copy
c_func
(paren
id|skb
comma
id|GFP_ATOMIC
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_goto
id|put
suffix:semicolon
)brace
r_if
c_cond
(paren
id|skb-&gt;sk
op_ne
l_int|NULL
)paren
id|skb_set_owner_w
c_func
(paren
id|ourskb
comma
id|skb-&gt;sk
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
multiline_comment|/* dl9sau: bugfix&n;&t;&t;&t; * after kfree_skb(), dst and src which were pointer&n;&t;&t;&t; * to bp which is part of skb-&gt;data would not be valid&n;&t;&t;&t; * anymore hope that after skb_pull(ourskb, ..) our&n;&t;&t;&t; * dsc_c and src_c will not become invalid&n;&t;&t;&t; */
id|bp
op_assign
id|ourskb-&gt;data
suffix:semicolon
id|dst_c
op_assign
op_star
(paren
id|ax25_address
op_star
)paren
(paren
id|bp
op_plus
l_int|1
)paren
suffix:semicolon
id|src_c
op_assign
op_star
(paren
id|ax25_address
op_star
)paren
(paren
id|bp
op_plus
l_int|8
)paren
suffix:semicolon
id|skb_pull
c_func
(paren
id|ourskb
comma
id|AX25_HEADER_LEN
op_minus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* Keep PID */
id|ourskb-&gt;nh.raw
op_assign
id|ourskb-&gt;data
suffix:semicolon
id|ax25
op_assign
id|ax25_send_frame
c_func
(paren
id|ourskb
comma
id|ax25_dev-&gt;values
(braket
id|AX25_VALUES_PACLEN
)braket
comma
op_amp
id|src_c
comma
op_amp
id|dst_c
comma
id|route-&gt;digipeat
comma
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ax25
)paren
(brace
id|ax25_cb_put
c_func
(paren
id|ax25
)paren
suffix:semicolon
)brace
r_goto
id|put
suffix:semicolon
)brace
)brace
id|bp
(braket
l_int|7
)braket
op_and_assign
op_complement
id|AX25_CBIT
suffix:semicolon
id|bp
(braket
l_int|7
)braket
op_and_assign
op_complement
id|AX25_EBIT
suffix:semicolon
id|bp
(braket
l_int|7
)braket
op_or_assign
id|AX25_SSSID_SPARE
suffix:semicolon
id|bp
(braket
l_int|14
)braket
op_and_assign
op_complement
id|AX25_CBIT
suffix:semicolon
id|bp
(braket
l_int|14
)braket
op_or_assign
id|AX25_EBIT
suffix:semicolon
id|bp
(braket
l_int|14
)braket
op_or_assign
id|AX25_SSSID_SPARE
suffix:semicolon
id|skb_pull
c_func
(paren
id|skb
comma
id|AX25_KISS_HEADER_LEN
)paren
suffix:semicolon
r_if
c_cond
(paren
id|route-&gt;digipeat
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
(paren
id|ourskb
op_assign
id|ax25_rt_build_path
c_func
(paren
id|skb
comma
id|src
comma
id|dst
comma
id|route-&gt;digipeat
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_goto
id|put
suffix:semicolon
)brace
id|skb
op_assign
id|ourskb
suffix:semicolon
)brace
id|skb-&gt;dev
op_assign
id|dev
suffix:semicolon
id|ax25_queue_xmit
c_func
(paren
id|skb
)paren
suffix:semicolon
id|put
suffix:colon
id|ax25_put_route
c_func
(paren
id|route
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
macro_line|#else&t;/* INET */
DECL|function|ax25_encapsulate
r_int
id|ax25_encapsulate
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|net_device
op_star
id|dev
comma
r_int
r_int
id|type
comma
r_void
op_star
id|daddr
comma
r_void
op_star
id|saddr
comma
r_int
id|len
)paren
(brace
r_return
op_minus
id|AX25_HEADER_LEN
suffix:semicolon
)brace
DECL|function|ax25_rebuild_header
r_int
id|ax25_rebuild_header
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
macro_line|#endif
eof
