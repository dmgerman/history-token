multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * Copyright (C) Alan Cox GW4PTS (alan@lxorguk.ukuu.org.uk)&n; * Copyright (C) Jonathan Naylor G4KLX (g4klx@g4klx.demon.co.uk)&n; * Copyright (C) Joerg Reuter DL1BKE (jreuter@yaina.de)&n; * Copyright (C) Hans-Joachim Hetscher DD8NE (dd8ne@bnv-bamberg.de)&n; */
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
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/netfilter.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;net/ip.h&gt;&t;&t;&t;/* For ip_rcv */
macro_line|#include &lt;net/tcp.h&gt;
macro_line|#include &lt;net/arp.h&gt;&t;&t;&t;/* For arp_rcv */
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
multiline_comment|/*&n; *&t;Given a fragment, queue it on the fragment queue and if the fragment&n; *&t;is complete, send it back to ax25_rx_iframe.&n; */
DECL|function|ax25_rx_fragment
r_static
r_int
id|ax25_rx_fragment
c_func
(paren
id|ax25_cb
op_star
id|ax25
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|sk_buff
op_star
id|skbn
comma
op_star
id|skbo
suffix:semicolon
r_if
c_cond
(paren
id|ax25-&gt;fragno
op_ne
l_int|0
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
op_star
id|skb-&gt;data
op_amp
id|AX25_SEG_FIRST
)paren
)paren
(brace
r_if
c_cond
(paren
(paren
id|ax25-&gt;fragno
op_minus
l_int|1
)paren
op_eq
(paren
op_star
id|skb-&gt;data
op_amp
id|AX25_SEG_REM
)paren
)paren
(brace
multiline_comment|/* Enqueue fragment */
id|ax25-&gt;fragno
op_assign
op_star
id|skb-&gt;data
op_amp
id|AX25_SEG_REM
suffix:semicolon
id|skb_pull
c_func
(paren
id|skb
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/* skip fragno */
id|ax25-&gt;fraglen
op_add_assign
id|skb-&gt;len
suffix:semicolon
id|skb_queue_tail
c_func
(paren
op_amp
id|ax25-&gt;frag_queue
comma
id|skb
)paren
suffix:semicolon
multiline_comment|/* Last fragment received ? */
r_if
c_cond
(paren
id|ax25-&gt;fragno
op_eq
l_int|0
)paren
(brace
id|skbn
op_assign
id|alloc_skb
c_func
(paren
id|AX25_MAX_HEADER_LEN
op_plus
id|ax25-&gt;fraglen
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|skbn
)paren
(brace
id|skb_queue_purge
c_func
(paren
op_amp
id|ax25-&gt;frag_queue
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|skb_reserve
c_func
(paren
id|skbn
comma
id|AX25_MAX_HEADER_LEN
)paren
suffix:semicolon
id|skbn-&gt;dev
op_assign
id|ax25-&gt;ax25_dev-&gt;dev
suffix:semicolon
id|skbn-&gt;h.raw
op_assign
id|skbn-&gt;data
suffix:semicolon
id|skbn-&gt;nh.raw
op_assign
id|skbn-&gt;data
suffix:semicolon
multiline_comment|/* Copy data from the fragments */
r_while
c_loop
(paren
(paren
id|skbo
op_assign
id|skb_dequeue
c_func
(paren
op_amp
id|ax25-&gt;frag_queue
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
id|memcpy
c_func
(paren
id|skb_put
c_func
(paren
id|skbn
comma
id|skbo-&gt;len
)paren
comma
id|skbo-&gt;data
comma
id|skbo-&gt;len
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skbo
)paren
suffix:semicolon
)brace
id|ax25-&gt;fraglen
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|ax25_rx_iframe
c_func
(paren
id|ax25
comma
id|skbn
)paren
op_eq
l_int|0
)paren
id|kfree_skb
c_func
(paren
id|skbn
)paren
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
)brace
)brace
r_else
(brace
multiline_comment|/* First fragment received */
r_if
c_cond
(paren
op_star
id|skb-&gt;data
op_amp
id|AX25_SEG_FIRST
)paren
(brace
id|skb_queue_purge
c_func
(paren
op_amp
id|ax25-&gt;frag_queue
)paren
suffix:semicolon
id|ax25-&gt;fragno
op_assign
op_star
id|skb-&gt;data
op_amp
id|AX25_SEG_REM
suffix:semicolon
id|skb_pull
c_func
(paren
id|skb
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/* skip fragno */
id|ax25-&gt;fraglen
op_assign
id|skb-&gt;len
suffix:semicolon
id|skb_queue_tail
c_func
(paren
op_amp
id|ax25-&gt;frag_queue
comma
id|skb
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;This is where all valid I frames are sent to, to be dispatched to&n; *&t;whichever protocol requires them.&n; */
DECL|function|ax25_rx_iframe
r_int
id|ax25_rx_iframe
c_func
(paren
id|ax25_cb
op_star
id|ax25
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_int
(paren
op_star
id|func
)paren
(paren
r_struct
id|sk_buff
op_star
comma
id|ax25_cb
op_star
)paren
suffix:semicolon
r_volatile
r_int
id|queued
op_assign
l_int|0
suffix:semicolon
r_int
r_char
id|pid
suffix:semicolon
r_if
c_cond
(paren
id|skb
op_eq
l_int|NULL
)paren
r_return
l_int|0
suffix:semicolon
id|ax25_start_idletimer
c_func
(paren
id|ax25
)paren
suffix:semicolon
id|pid
op_assign
op_star
id|skb-&gt;data
suffix:semicolon
macro_line|#ifdef CONFIG_INET
r_if
c_cond
(paren
id|pid
op_eq
id|AX25_P_IP
)paren
(brace
multiline_comment|/* working around a TCP bug to keep additional listeners&n;&t;&t; * happy. TCP re-uses the buffer and destroys the original&n;&t;&t; * content.&n;&t;&t; */
r_struct
id|sk_buff
op_star
id|skbn
op_assign
id|skb_copy
c_func
(paren
id|skb
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skbn
op_ne
l_int|NULL
)paren
(brace
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
id|skb
op_assign
id|skbn
suffix:semicolon
)brace
id|skb_pull
c_func
(paren
id|skb
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/* Remove PID */
id|skb-&gt;h.raw
op_assign
id|skb-&gt;data
suffix:semicolon
id|skb-&gt;nh.raw
op_assign
id|skb-&gt;data
suffix:semicolon
id|skb-&gt;dev
op_assign
id|ax25-&gt;ax25_dev-&gt;dev
suffix:semicolon
id|skb-&gt;pkt_type
op_assign
id|PACKET_HOST
suffix:semicolon
id|skb-&gt;protocol
op_assign
id|htons
c_func
(paren
id|ETH_P_IP
)paren
suffix:semicolon
id|ip_rcv
c_func
(paren
id|skb
comma
id|skb-&gt;dev
comma
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/* Wrong ptype */
r_return
l_int|1
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
id|pid
op_eq
id|AX25_P_SEGMENT
)paren
(brace
id|skb_pull
c_func
(paren
id|skb
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/* Remove PID */
r_return
id|ax25_rx_fragment
c_func
(paren
id|ax25
comma
id|skb
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|func
op_assign
id|ax25_protocol_function
c_func
(paren
id|pid
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
id|skb_pull
c_func
(paren
id|skb
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/* Remove PID */
r_return
(paren
op_star
id|func
)paren
(paren
id|skb
comma
id|ax25
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ax25-&gt;sk
op_ne
l_int|NULL
op_logical_and
id|ax25-&gt;ax25_dev-&gt;values
(braket
id|AX25_VALUES_CONMODE
)braket
op_eq
l_int|2
)paren
(brace
r_if
c_cond
(paren
(paren
op_logical_neg
id|ax25-&gt;pidincl
op_logical_and
id|ax25-&gt;sk-&gt;sk_protocol
op_eq
id|pid
)paren
op_logical_or
id|ax25-&gt;pidincl
)paren
(brace
r_if
c_cond
(paren
id|sock_queue_rcv_skb
c_func
(paren
id|ax25-&gt;sk
comma
id|skb
)paren
op_eq
l_int|0
)paren
id|queued
op_assign
l_int|1
suffix:semicolon
r_else
id|ax25-&gt;condition
op_or_assign
id|AX25_COND_OWN_RX_BUSY
suffix:semicolon
)brace
)brace
r_return
id|queued
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Higher level upcall for a LAPB frame&n; */
DECL|function|ax25_process_rx_frame
r_static
r_int
id|ax25_process_rx_frame
c_func
(paren
id|ax25_cb
op_star
id|ax25
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
id|type
comma
r_int
id|dama
)paren
(brace
r_int
id|queued
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|ax25-&gt;state
op_eq
id|AX25_STATE_0
)paren
r_return
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|ax25-&gt;ax25_dev-&gt;values
(braket
id|AX25_VALUES_PROTOCOL
)braket
)paren
(brace
r_case
id|AX25_PROTO_STD_SIMPLEX
suffix:colon
r_case
id|AX25_PROTO_STD_DUPLEX
suffix:colon
id|queued
op_assign
id|ax25_std_frame_in
c_func
(paren
id|ax25
comma
id|skb
comma
id|type
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#ifdef CONFIG_AX25_DAMA_SLAVE
r_case
id|AX25_PROTO_DAMA_SLAVE
suffix:colon
r_if
c_cond
(paren
id|dama
op_logical_or
id|ax25-&gt;ax25_dev-&gt;dama.slave
)paren
id|queued
op_assign
id|ax25_ds_frame_in
c_func
(paren
id|ax25
comma
id|skb
comma
id|type
)paren
suffix:semicolon
r_else
id|queued
op_assign
id|ax25_std_frame_in
c_func
(paren
id|ax25
comma
id|skb
comma
id|type
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
)brace
r_return
id|queued
suffix:semicolon
)brace
DECL|function|ax25_rcv
r_static
r_int
id|ax25_rcv
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
id|ax25_address
op_star
id|dev_addr
comma
r_struct
id|packet_type
op_star
id|ptype
)paren
(brace
id|ax25_address
id|src
comma
id|dest
comma
op_star
id|next_digi
op_assign
l_int|NULL
suffix:semicolon
r_int
id|type
op_assign
l_int|0
comma
id|mine
op_assign
l_int|0
comma
id|dama
suffix:semicolon
r_struct
id|sock
op_star
id|make
comma
op_star
id|sk
suffix:semicolon
id|ax25_digi
id|dp
comma
id|reverse_dp
suffix:semicolon
id|ax25_cb
op_star
id|ax25
suffix:semicolon
id|ax25_dev
op_star
id|ax25_dev
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Process the AX.25/LAPB frame.&n;&t; */
id|skb-&gt;h.raw
op_assign
id|skb-&gt;data
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
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *&t;Parse the address header.&n;&t; */
r_if
c_cond
(paren
id|ax25_addr_parse
c_func
(paren
id|skb-&gt;data
comma
id|skb-&gt;len
comma
op_amp
id|src
comma
op_amp
id|dest
comma
op_amp
id|dp
comma
op_amp
id|type
comma
op_amp
id|dama
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
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *&t;Ours perhaps ?&n;&t; */
r_if
c_cond
(paren
id|dp.lastrepeat
op_plus
l_int|1
OL
id|dp.ndigi
)paren
multiline_comment|/* Not yet digipeated completely */
id|next_digi
op_assign
op_amp
id|dp.calls
(braket
id|dp.lastrepeat
op_plus
l_int|1
)braket
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Pull of the AX.25 headers leaving the CTRL/PID bytes&n;&t; */
id|skb_pull
c_func
(paren
id|skb
comma
id|ax25_addr_size
c_func
(paren
op_amp
id|dp
)paren
)paren
suffix:semicolon
multiline_comment|/* For our port addresses ? */
r_if
c_cond
(paren
id|ax25cmp
c_func
(paren
op_amp
id|dest
comma
id|dev_addr
)paren
op_eq
l_int|0
op_logical_and
id|dp.lastrepeat
op_plus
l_int|1
op_eq
id|dp.ndigi
)paren
id|mine
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Also match on any registered callsign from L3/4 */
r_if
c_cond
(paren
op_logical_neg
id|mine
op_logical_and
id|ax25_listen_mine
c_func
(paren
op_amp
id|dest
comma
id|dev
)paren
op_logical_and
id|dp.lastrepeat
op_plus
l_int|1
op_eq
id|dp.ndigi
)paren
id|mine
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* UI frame - bypass LAPB processing */
r_if
c_cond
(paren
(paren
op_star
id|skb-&gt;data
op_amp
op_complement
l_int|0x10
)paren
op_eq
id|AX25_UI
op_logical_and
id|dp.lastrepeat
op_plus
l_int|1
op_eq
id|dp.ndigi
)paren
(brace
id|skb-&gt;h.raw
op_assign
id|skb-&gt;data
op_plus
l_int|2
suffix:semicolon
multiline_comment|/* skip control and pid */
id|ax25_send_to_raw
c_func
(paren
op_amp
id|dest
comma
id|skb
comma
id|skb-&gt;data
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mine
op_logical_and
id|ax25cmp
c_func
(paren
op_amp
id|dest
comma
(paren
id|ax25_address
op_star
)paren
id|dev-&gt;broadcast
)paren
op_ne
l_int|0
)paren
(brace
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Now we are pointing at the pid byte */
r_switch
c_cond
(paren
id|skb-&gt;data
(braket
l_int|1
)braket
)paren
(brace
macro_line|#ifdef CONFIG_INET
r_case
id|AX25_P_IP
suffix:colon
id|skb_pull
c_func
(paren
id|skb
comma
l_int|2
)paren
suffix:semicolon
multiline_comment|/* drop PID/CTRL */
id|skb-&gt;h.raw
op_assign
id|skb-&gt;data
suffix:semicolon
id|skb-&gt;nh.raw
op_assign
id|skb-&gt;data
suffix:semicolon
id|skb-&gt;dev
op_assign
id|dev
suffix:semicolon
id|skb-&gt;pkt_type
op_assign
id|PACKET_HOST
suffix:semicolon
id|skb-&gt;protocol
op_assign
id|htons
c_func
(paren
id|ETH_P_IP
)paren
suffix:semicolon
id|ip_rcv
c_func
(paren
id|skb
comma
id|dev
comma
id|ptype
)paren
suffix:semicolon
multiline_comment|/* Note ptype here is the wrong one, fix me later */
r_break
suffix:semicolon
r_case
id|AX25_P_ARP
suffix:colon
id|skb_pull
c_func
(paren
id|skb
comma
l_int|2
)paren
suffix:semicolon
id|skb-&gt;h.raw
op_assign
id|skb-&gt;data
suffix:semicolon
id|skb-&gt;nh.raw
op_assign
id|skb-&gt;data
suffix:semicolon
id|skb-&gt;dev
op_assign
id|dev
suffix:semicolon
id|skb-&gt;pkt_type
op_assign
id|PACKET_HOST
suffix:semicolon
id|skb-&gt;protocol
op_assign
id|htons
c_func
(paren
id|ETH_P_ARP
)paren
suffix:semicolon
id|arp_rcv
c_func
(paren
id|skb
comma
id|dev
comma
id|ptype
)paren
suffix:semicolon
multiline_comment|/* Note ptype here is wrong... */
r_break
suffix:semicolon
macro_line|#endif
r_case
id|AX25_P_TEXT
suffix:colon
multiline_comment|/* Now find a suitable dgram socket */
id|sk
op_assign
id|ax25_get_socket
c_func
(paren
op_amp
id|dest
comma
op_amp
id|src
comma
id|SOCK_DGRAM
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sk
op_ne
l_int|NULL
)paren
(brace
id|bh_lock_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|sk-&gt;sk_rmem_alloc
)paren
op_ge
id|sk-&gt;sk_rcvbuf
)paren
(brace
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t;&t;&t;&t; *&t;Remove the control and PID.&n;&t;&t;&t;&t;&t; */
id|skb_pull
c_func
(paren
id|skb
comma
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sock_queue_rcv_skb
c_func
(paren
id|sk
comma
id|skb
)paren
op_ne
l_int|0
)paren
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
id|bh_unlock_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
id|sock_put
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
r_else
(brace
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
multiline_comment|/* Will scan SOCK_AX25 RAW sockets */
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *&t;Is connected mode supported on this device ?&n;&t; *&t;If not, should we DM the incoming frame (except DMs) or&n;&t; *&t;silently ignore them. For now we stay quiet.&n;&t; */
r_if
c_cond
(paren
id|ax25_dev-&gt;values
(braket
id|AX25_VALUES_CONMODE
)braket
op_eq
l_int|0
)paren
(brace
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* LAPB */
multiline_comment|/* AX.25 state 1-4 */
id|ax25_digi_invert
c_func
(paren
op_amp
id|dp
comma
op_amp
id|reverse_dp
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ax25
op_assign
id|ax25_find_cb
c_func
(paren
op_amp
id|dest
comma
op_amp
id|src
comma
op_amp
id|reverse_dp
comma
id|dev
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
multiline_comment|/*&n;&t;&t; *&t;Process the frame. If it is queued up internally it&n;&t;&t; *&t;returns one otherwise we free it immediately. This&n;&t;&t; *&t;routine itself wakes the user context layers so we do&n;&t;&t; *&t;no further work&n;&t;&t; */
r_if
c_cond
(paren
id|ax25_process_rx_frame
c_func
(paren
id|ax25
comma
id|skb
comma
id|type
comma
id|dama
)paren
op_eq
l_int|0
)paren
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
id|ax25_cb_put
c_func
(paren
id|ax25
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* AX.25 state 0 (disconnected) */
multiline_comment|/* a) received not a SABM(E) */
r_if
c_cond
(paren
(paren
op_star
id|skb-&gt;data
op_amp
op_complement
id|AX25_PF
)paren
op_ne
id|AX25_SABM
op_logical_and
(paren
op_star
id|skb-&gt;data
op_amp
op_complement
id|AX25_PF
)paren
op_ne
id|AX25_SABME
)paren
(brace
multiline_comment|/*&n;&t;&t; *&t;Never reply to a DM. Also ignore any connects for&n;&t;&t; *&t;addresses that are not our interfaces and not a socket.&n;&t;&t; */
r_if
c_cond
(paren
(paren
op_star
id|skb-&gt;data
op_amp
op_complement
id|AX25_PF
)paren
op_ne
id|AX25_DM
op_logical_and
id|mine
)paren
id|ax25_return_dm
c_func
(paren
id|dev
comma
op_amp
id|src
comma
op_amp
id|dest
comma
op_amp
id|dp
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* b) received SABM(E) */
r_if
c_cond
(paren
id|dp.lastrepeat
op_plus
l_int|1
op_eq
id|dp.ndigi
)paren
id|sk
op_assign
id|ax25_find_listener
c_func
(paren
op_amp
id|dest
comma
l_int|0
comma
id|dev
comma
id|SOCK_SEQPACKET
)paren
suffix:semicolon
r_else
id|sk
op_assign
id|ax25_find_listener
c_func
(paren
id|next_digi
comma
l_int|1
comma
id|dev
comma
id|SOCK_SEQPACKET
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sk
op_ne
l_int|NULL
)paren
(brace
id|bh_lock_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sk_acceptq_is_full
c_func
(paren
id|sk
)paren
op_logical_or
(paren
id|make
op_assign
id|ax25_make_new
c_func
(paren
id|sk
comma
id|ax25_dev
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|mine
)paren
id|ax25_return_dm
c_func
(paren
id|dev
comma
op_amp
id|src
comma
op_amp
id|dest
comma
op_amp
id|dp
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
id|bh_unlock_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
id|sock_put
c_func
(paren
id|sk
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|ax25
op_assign
id|ax25_sk
c_func
(paren
id|make
)paren
suffix:semicolon
id|skb_set_owner_r
c_func
(paren
id|skb
comma
id|make
)paren
suffix:semicolon
id|skb_queue_head
c_func
(paren
op_amp
id|sk-&gt;sk_receive_queue
comma
id|skb
)paren
suffix:semicolon
id|make-&gt;sk_state
op_assign
id|TCP_ESTABLISHED
suffix:semicolon
id|sk-&gt;sk_ack_backlog
op_increment
suffix:semicolon
id|bh_unlock_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
op_logical_neg
id|mine
)paren
(brace
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|ax25
op_assign
id|ax25_create_cb
c_func
(paren
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|ax25_return_dm
c_func
(paren
id|dev
comma
op_amp
id|src
comma
op_amp
id|dest
comma
op_amp
id|dp
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|ax25_fillin_cb
c_func
(paren
id|ax25
comma
id|ax25_dev
)paren
suffix:semicolon
)brace
id|ax25-&gt;source_addr
op_assign
id|dest
suffix:semicolon
id|ax25-&gt;dest_addr
op_assign
id|src
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Sort out any digipeated paths.&n;&t; */
r_if
c_cond
(paren
id|dp.ndigi
op_logical_and
op_logical_neg
id|ax25-&gt;digipeat
op_logical_and
(paren
id|ax25-&gt;digipeat
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
id|ax25_digi
)paren
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
id|ax25_destroy_socket
c_func
(paren
id|ax25
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sk
)paren
id|sock_put
c_func
(paren
id|sk
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dp.ndigi
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|ax25-&gt;digipeat
op_ne
l_int|NULL
)paren
(brace
id|kfree
c_func
(paren
id|ax25-&gt;digipeat
)paren
suffix:semicolon
id|ax25-&gt;digipeat
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* Reverse the source SABM&squot;s path */
id|memcpy
c_func
(paren
id|ax25-&gt;digipeat
comma
op_amp
id|reverse_dp
comma
r_sizeof
(paren
id|ax25_digi
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
op_star
id|skb-&gt;data
op_amp
op_complement
id|AX25_PF
)paren
op_eq
id|AX25_SABME
)paren
(brace
id|ax25-&gt;modulus
op_assign
id|AX25_EMODULUS
suffix:semicolon
id|ax25-&gt;window
op_assign
id|ax25_dev-&gt;values
(braket
id|AX25_VALUES_EWINDOW
)braket
suffix:semicolon
)brace
r_else
(brace
id|ax25-&gt;modulus
op_assign
id|AX25_MODULUS
suffix:semicolon
id|ax25-&gt;window
op_assign
id|ax25_dev-&gt;values
(braket
id|AX25_VALUES_WINDOW
)braket
suffix:semicolon
)brace
id|ax25_send_control
c_func
(paren
id|ax25
comma
id|AX25_UA
comma
id|AX25_POLLON
comma
id|AX25_RESPONSE
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_AX25_DAMA_SLAVE
r_if
c_cond
(paren
id|dama
op_logical_and
id|ax25-&gt;ax25_dev-&gt;values
(braket
id|AX25_VALUES_PROTOCOL
)braket
op_eq
id|AX25_PROTO_DAMA_SLAVE
)paren
id|ax25_dama_on
c_func
(paren
id|ax25
)paren
suffix:semicolon
macro_line|#endif
id|ax25-&gt;state
op_assign
id|AX25_STATE_3
suffix:semicolon
id|ax25_cb_add
c_func
(paren
id|ax25
)paren
suffix:semicolon
id|ax25_start_heartbeat
c_func
(paren
id|ax25
)paren
suffix:semicolon
id|ax25_start_t3timer
c_func
(paren
id|ax25
)paren
suffix:semicolon
id|ax25_start_idletimer
c_func
(paren
id|ax25
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sk
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|sock_flag
c_func
(paren
id|sk
comma
id|SOCK_DEAD
)paren
)paren
id|sk
op_member_access_from_pointer
id|sk_data_ready
c_func
(paren
id|sk
comma
id|skb-&gt;len
)paren
suffix:semicolon
id|sock_put
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
r_else
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Receive an AX.25 frame via a SLIP interface.&n; */
DECL|function|ax25_kiss_rcv
r_int
id|ax25_kiss_rcv
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
r_struct
id|packet_type
op_star
id|ptype
)paren
(brace
id|skb-&gt;sk
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Initially we don&squot;t know who it&squot;s for */
id|skb-&gt;destructor
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Who initializes this, dammit?! */
r_if
c_cond
(paren
(paren
op_star
id|skb-&gt;data
op_amp
l_int|0x0F
)paren
op_ne
l_int|0
)paren
(brace
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
multiline_comment|/* Not a KISS data frame */
r_return
l_int|0
suffix:semicolon
)brace
id|skb_pull
c_func
(paren
id|skb
comma
id|AX25_KISS_HEADER_LEN
)paren
suffix:semicolon
multiline_comment|/* Remove the KISS byte */
r_return
id|ax25_rcv
c_func
(paren
id|skb
comma
id|dev
comma
(paren
id|ax25_address
op_star
)paren
id|dev-&gt;dev_addr
comma
id|ptype
)paren
suffix:semicolon
)brace
eof
