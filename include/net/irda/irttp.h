multiline_comment|/*********************************************************************&n; *                &n; * Filename:      irttp.h&n; * Version:       1.0&n; * Description:   Tiny Transport Protocol (TTP) definitions&n; * Status:        Experimental.&n; * Author:        Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * Created at:    Sun Aug 31 20:14:31 1997&n; * Modified at:   Sun Dec 12 13:09:07 1999&n; * Modified by:   Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * &n; *     Copyright (c) 1998-1999 Dag Brattli &lt;dagb@cs.uit.no&gt;, &n; *     All Rights Reserved.&n; *     &n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version.&n; *&n; *     Neither Dag Brattli nor University of Troms&#xfffd; admit liability nor&n; *     provide warranty for any of this software. This material is &n; *     provided &quot;AS-IS&quot; and at no charge.&n; *&n; ********************************************************************/
macro_line|#ifndef IRTTP_H
DECL|macro|IRTTP_H
mdefine_line|#define IRTTP_H
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;net/irda/irda.h&gt;
macro_line|#include &lt;net/irda/irlmp.h&gt;
macro_line|#include &lt;net/irda/qos.h&gt;
macro_line|#include &lt;net/irda/irqueue.h&gt;
DECL|macro|TTP_MAX_CONNECTIONS
mdefine_line|#define TTP_MAX_CONNECTIONS    LM_MAX_CONNECTIONS
DECL|macro|TTP_HEADER
mdefine_line|#define TTP_HEADER             1
DECL|macro|TTP_MAX_HEADER
mdefine_line|#define TTP_MAX_HEADER         (TTP_HEADER + LMP_MAX_HEADER)
DECL|macro|TTP_SAR_HEADER
mdefine_line|#define TTP_SAR_HEADER         5
DECL|macro|TTP_PARAMETERS
mdefine_line|#define TTP_PARAMETERS         0x80
DECL|macro|TTP_MORE
mdefine_line|#define TTP_MORE               0x80
multiline_comment|/* Transmission queue sizes */
multiline_comment|/* Worst case scenario, two window of data - Jean II */
DECL|macro|TTP_TX_MAX_QUEUE
mdefine_line|#define TTP_TX_MAX_QUEUE&t;14
multiline_comment|/* We need to keep at least 5 frames to make sure that we can refill&n; * appropriately the LAP layer. LAP keeps only two buffers, and we need&n; * to have 7 to make a full window - Jean II */
DECL|macro|TTP_TX_LOW_THRESHOLD
mdefine_line|#define TTP_TX_LOW_THRESHOLD&t;5
multiline_comment|/* Most clients are synchronous with respect to flow control, so we can&n; * keep a low number of Tx buffers in TTP - Jean II */
DECL|macro|TTP_TX_HIGH_THRESHOLD
mdefine_line|#define TTP_TX_HIGH_THRESHOLD&t;7
multiline_comment|/* Receive queue sizes */
multiline_comment|/* Minimum of credit that the peer should hold.&n; * If the peer has less credits than 9 frames, we will explicitely send&n; * him some credits (through irttp_give_credit() and a specific frame).&n; * Note that when we give credits it&squot;s likely that it won&squot;t be sent in&n; * this LAP window, but in the next one. So, we make sure that the peer&n; * has something to send while waiting for credits (one LAP window == 7&n; * + 1 frames while he process the credits). - Jean II */
DECL|macro|TTP_RX_MIN_CREDIT
mdefine_line|#define TTP_RX_MIN_CREDIT&t;8
multiline_comment|/* This is the default maximum number of credits held by the peer, so the&n; * default maximum number of frames he can send us before needing flow&n; * control answer from us (this may be negociated differently at TSAP setup).&n; * We want to minimise the number of times we have to explicitely send some&n; * credit to the peer, hoping we can piggyback it on the return data. In&n; * particular, it doesn&squot;t make sense for us to send credit more than once&n; * per LAP window.&n; * Moreover, giving credits has some latency, so we need strictly more than&n; * a LAP window, otherwise we may already have credits in our Tx queue.&n; * But on the other hand, we don&squot;t want to keep too many Rx buffer here&n; * before starting to flow control the other end, so make it exactly one&n; * LAP window + 1 + MIN_CREDITS. - Jean II */
DECL|macro|TTP_RX_DEFAULT_CREDIT
mdefine_line|#define TTP_RX_DEFAULT_CREDIT&t;16
multiline_comment|/* Maximum number of credits we can allow the peer to have, and therefore&n; * maximum Rx queue size.&n; * Note that we try to deliver packets to the higher layer every time we&n; * receive something, so in normal mode the Rx queue will never contains&n; * more than one or two packets. - Jean II */
DECL|macro|TTP_RX_MAX_CREDIT
mdefine_line|#define TTP_RX_MAX_CREDIT&t;21
multiline_comment|/* What clients should use when calling ttp_open_tsap() */
DECL|macro|DEFAULT_INITIAL_CREDIT
mdefine_line|#define DEFAULT_INITIAL_CREDIT&t;TTP_RX_DEFAULT_CREDIT
multiline_comment|/* Some priorities for disconnect requests */
DECL|macro|P_NORMAL
mdefine_line|#define P_NORMAL    0
DECL|macro|P_HIGH
mdefine_line|#define P_HIGH      1
DECL|macro|TTP_SAR_DISABLE
mdefine_line|#define TTP_SAR_DISABLE 0
DECL|macro|TTP_SAR_UNBOUND
mdefine_line|#define TTP_SAR_UNBOUND 0xffffffff
multiline_comment|/* Parameters */
DECL|macro|TTP_MAX_SDU_SIZE
mdefine_line|#define TTP_MAX_SDU_SIZE 0x01
multiline_comment|/*&n; *  This structure contains all data assosiated with one instance of a TTP &n; *  connection.&n; */
DECL|struct|tsap_cb
r_struct
id|tsap_cb
(brace
DECL|member|q
id|irda_queue_t
id|q
suffix:semicolon
multiline_comment|/* Must be first */
DECL|member|magic
id|magic_t
id|magic
suffix:semicolon
multiline_comment|/* Just in case */
DECL|member|stsap_sel
id|__u8
id|stsap_sel
suffix:semicolon
multiline_comment|/* Source TSAP */
DECL|member|dtsap_sel
id|__u8
id|dtsap_sel
suffix:semicolon
multiline_comment|/* Destination TSAP */
DECL|member|lsap
r_struct
id|lsap_cb
op_star
id|lsap
suffix:semicolon
multiline_comment|/* Corresponding LSAP to this TSAP */
DECL|member|connected
id|__u8
id|connected
suffix:semicolon
multiline_comment|/* TSAP connected */
DECL|member|initial_credit
id|__u8
id|initial_credit
suffix:semicolon
multiline_comment|/* Initial credit to give peer */
DECL|member|avail_credit
r_int
id|avail_credit
suffix:semicolon
multiline_comment|/* Available credit to return to peer */
DECL|member|remote_credit
r_int
id|remote_credit
suffix:semicolon
multiline_comment|/* Credit held by peer TTP entity */
DECL|member|send_credit
r_int
id|send_credit
suffix:semicolon
multiline_comment|/* Credit held by local TTP entity */
DECL|member|tx_queue
r_struct
id|sk_buff_head
id|tx_queue
suffix:semicolon
multiline_comment|/* Frames to be transmitted */
DECL|member|rx_queue
r_struct
id|sk_buff_head
id|rx_queue
suffix:semicolon
multiline_comment|/* Received frames */
DECL|member|rx_fragments
r_struct
id|sk_buff_head
id|rx_fragments
suffix:semicolon
DECL|member|tx_queue_lock
r_int
id|tx_queue_lock
suffix:semicolon
DECL|member|rx_queue_lock
r_int
id|rx_queue_lock
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|notify
id|notify_t
id|notify
suffix:semicolon
multiline_comment|/* Callbacks to client layer */
DECL|member|stats
r_struct
id|net_device_stats
id|stats
suffix:semicolon
DECL|member|todo_timer
r_struct
id|timer_list
id|todo_timer
suffix:semicolon
DECL|member|max_seg_size
id|__u32
id|max_seg_size
suffix:semicolon
multiline_comment|/* Max data that fit into an IrLAP frame */
DECL|member|max_header_size
id|__u8
id|max_header_size
suffix:semicolon
DECL|member|rx_sdu_busy
r_int
id|rx_sdu_busy
suffix:semicolon
multiline_comment|/* RxSdu.busy */
DECL|member|rx_sdu_size
id|__u32
id|rx_sdu_size
suffix:semicolon
multiline_comment|/* Current size of a partially received frame */
DECL|member|rx_max_sdu_size
id|__u32
id|rx_max_sdu_size
suffix:semicolon
multiline_comment|/* Max receive user data size */
DECL|member|tx_sdu_busy
r_int
id|tx_sdu_busy
suffix:semicolon
multiline_comment|/* TxSdu.busy */
DECL|member|tx_max_sdu_size
id|__u32
id|tx_max_sdu_size
suffix:semicolon
multiline_comment|/* Max transmit user data size */
DECL|member|close_pend
r_int
id|close_pend
suffix:semicolon
multiline_comment|/* Close, but disconnect_pend */
DECL|member|disconnect_pend
r_int
id|disconnect_pend
suffix:semicolon
multiline_comment|/* Disconnect, but still data to send */
DECL|member|disconnect_skb
r_struct
id|sk_buff
op_star
id|disconnect_skb
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|irttp_cb
r_struct
id|irttp_cb
(brace
DECL|member|magic
id|magic_t
id|magic
suffix:semicolon
DECL|member|tsaps
id|hashbin_t
op_star
id|tsaps
suffix:semicolon
)brace
suffix:semicolon
r_int
id|irttp_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|irttp_cleanup
c_func
(paren
r_void
)paren
suffix:semicolon
r_struct
id|tsap_cb
op_star
id|irttp_open_tsap
c_func
(paren
id|__u8
id|stsap_sel
comma
r_int
id|credit
comma
id|notify_t
op_star
id|notify
)paren
suffix:semicolon
r_int
id|irttp_close_tsap
c_func
(paren
r_struct
id|tsap_cb
op_star
id|self
)paren
suffix:semicolon
r_int
id|irttp_data_request
c_func
(paren
r_struct
id|tsap_cb
op_star
id|self
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_int
id|irttp_udata_request
c_func
(paren
r_struct
id|tsap_cb
op_star
id|self
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_int
id|irttp_connect_request
c_func
(paren
r_struct
id|tsap_cb
op_star
id|self
comma
id|__u8
id|dtsap_sel
comma
id|__u32
id|saddr
comma
id|__u32
id|daddr
comma
r_struct
id|qos_info
op_star
id|qos
comma
id|__u32
id|max_sdu_size
comma
r_struct
id|sk_buff
op_star
id|userdata
)paren
suffix:semicolon
r_int
id|irttp_connect_response
c_func
(paren
r_struct
id|tsap_cb
op_star
id|self
comma
id|__u32
id|max_sdu_size
comma
r_struct
id|sk_buff
op_star
id|userdata
)paren
suffix:semicolon
r_int
id|irttp_disconnect_request
c_func
(paren
r_struct
id|tsap_cb
op_star
id|self
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
id|priority
)paren
suffix:semicolon
r_void
id|irttp_flow_request
c_func
(paren
r_struct
id|tsap_cb
op_star
id|self
comma
id|LOCAL_FLOW
id|flow
)paren
suffix:semicolon
r_void
id|irttp_status_indication
c_func
(paren
r_void
op_star
id|instance
comma
id|LINK_STATUS
id|link
comma
id|LOCK_STATUS
id|lock
)paren
suffix:semicolon
r_void
id|irttp_flow_indication
c_func
(paren
r_void
op_star
id|instance
comma
r_void
op_star
id|sap
comma
id|LOCAL_FLOW
id|flow
)paren
suffix:semicolon
r_struct
id|tsap_cb
op_star
id|irttp_dup
c_func
(paren
r_struct
id|tsap_cb
op_star
id|self
comma
r_void
op_star
id|instance
)paren
suffix:semicolon
DECL|function|irttp_get_saddr
r_static
id|__inline
id|__u32
id|irttp_get_saddr
c_func
(paren
r_struct
id|tsap_cb
op_star
id|self
)paren
(brace
r_return
id|irlmp_get_saddr
c_func
(paren
id|self-&gt;lsap
)paren
suffix:semicolon
)brace
DECL|function|irttp_get_daddr
r_static
id|__inline
id|__u32
id|irttp_get_daddr
c_func
(paren
r_struct
id|tsap_cb
op_star
id|self
)paren
(brace
r_return
id|irlmp_get_daddr
c_func
(paren
id|self-&gt;lsap
)paren
suffix:semicolon
)brace
DECL|function|irttp_get_max_seg_size
r_static
id|__inline
id|__u32
id|irttp_get_max_seg_size
c_func
(paren
r_struct
id|tsap_cb
op_star
id|self
)paren
(brace
r_return
id|self-&gt;max_seg_size
suffix:semicolon
)brace
multiline_comment|/* After doing a irttp_dup(), this get one of the two socket back into&n; * a state where it&squot;s waiting incomming connections.&n; * Note : this can be used *only* if the socket is not yet connected&n; * (i.e. NO irttp_connect_response() done on this socket).&n; * - Jean II */
DECL|function|irttp_listen
r_static
r_inline
r_void
id|irttp_listen
c_func
(paren
r_struct
id|tsap_cb
op_star
id|self
)paren
(brace
id|irlmp_listen
c_func
(paren
id|self-&gt;lsap
)paren
suffix:semicolon
id|self-&gt;dtsap_sel
op_assign
id|LSAP_ANY
suffix:semicolon
)brace
r_extern
r_struct
id|irttp_cb
op_star
id|irttp
suffix:semicolon
macro_line|#endif /* IRTTP_H */
eof
