multiline_comment|/*&n; * sbni.h - header file for sbni linux device driver&n; *&n; * Copyright (C) 1999 Granch ltd., Yaroslav Polyakov (xenon@granch.ru).&n; *&n; */
multiline_comment|/*&n; * SBNI12 definitions&n; *&n; * Revision 2.0.0  1997/08/27&n; * Initial revision&n; *&n; * Revision 2.1.0  1999/04/26&n; * dev_priv structure changed to support balancing and some other features.&n; *&n; */
macro_line|#ifndef __SBNI_H
DECL|macro|__SBNI_H
mdefine_line|#define __SBNI_H
DECL|macro|SBNI_DEBUG
mdefine_line|#define SBNI_DEBUG 0
macro_line|#if SBNI_DEBUG
DECL|macro|DP
mdefine_line|#define DP( A ) A
macro_line|#else
DECL|macro|DP
mdefine_line|#define DP( A )
macro_line|#endif
DECL|typedef|BOOLEAN
r_typedef
r_int
r_char
id|BOOLEAN
suffix:semicolon
DECL|macro|TRUE
mdefine_line|#define TRUE 1
DECL|macro|FALSE
mdefine_line|#define FALSE 0
DECL|macro|SBNI_IO_EXTENT
mdefine_line|#define&t;SBNI_IO_EXTENT&t;0x4
DECL|macro|SB_MAX_BUFFER_ARRAY
mdefine_line|#define SB_MAX_BUFFER_ARRAY 1023
DECL|macro|CSR0
mdefine_line|#define CSR0&t;0
DECL|macro|CSR1
mdefine_line|#define CSR1&t;1
DECL|macro|DAT
mdefine_line|#define&t;DAT&t;2
multiline_comment|/* CSR0 mapping */
DECL|macro|BU_EMP
mdefine_line|#define BU_EMP&t;(1 &lt;&lt; 1)&t;/* r z    */
DECL|macro|RC_CHK
mdefine_line|#define&t;RC_CHK&t;(1 &lt;&lt; 2)&t;/* rw     */
DECL|macro|CT_ZER
mdefine_line|#define&t;CT_ZER&t;(1 &lt;&lt; 3)&t;/*  w     */
DECL|macro|TR_REQ
mdefine_line|#define&t;TR_REQ&t;(1 &lt;&lt; 4)&t;/* rwz*   */
DECL|macro|TR_RDY
mdefine_line|#define TR_RDY&t;(1 &lt;&lt; 5)&t;/* r z    */
DECL|macro|EN_INT
mdefine_line|#define EN_INT&t;(1 &lt;&lt; 6)&t;/* rwz* */
DECL|macro|RC_RDY
mdefine_line|#define RC_RDY&t;(1 &lt;&lt; 7)&t;/* r z    */
multiline_comment|/* CSR1 mapping */
DECL|macro|PR_RES
mdefine_line|#define PR_RES&t;(1 &lt;&lt; 7)&t;/*  w     */
DECL|struct|sbni_csr1
r_struct
id|sbni_csr1
(brace
DECL|member|rxl
r_int
id|rxl
suffix:colon
l_int|5
suffix:semicolon
DECL|member|rate
r_int
id|rate
suffix:colon
l_int|2
suffix:semicolon
r_int
suffix:colon
l_int|1
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|DEF_RXL_DELTA
mdefine_line|#define DEF_RXL_DELTA&t;-1
DECL|macro|DEF_RXL
mdefine_line|#define DEF_RXL&t;&t;0xf
DECL|macro|DEF_RATE
mdefine_line|#define DEF_RATE&t;0
DECL|macro|DEF_FRAME_LEN
mdefine_line|#define DEF_FRAME_LEN&t;(1023 - 14 - 9)
macro_line|#ifdef MODULE
DECL|macro|SBNI_MAX_NUM_CARDS
mdefine_line|#define SBNI_MAX_NUM_CARDS 8
DECL|macro|SBNI_MAX_SLAVES
mdefine_line|#define SBNI_MAX_SLAVES 8
macro_line|#endif&t;&t;&t;&t;/* MODULE */
DECL|macro|SBNI_SIG
mdefine_line|#define SBNI_SIG 0x5a
DECL|macro|SB_ETHER_MIN_LEN
mdefine_line|#define&t;SB_ETHER_MIN_LEN 60
DECL|macro|SB_FILLING_CHAR
mdefine_line|#define SB_FILLING_CHAR (unsigned char)0x00
DECL|macro|TR_ERROR_COUNT
mdefine_line|#define TR_ERROR_COUNT 32
DECL|macro|CHANGE_LEVEL_START_TICKS
mdefine_line|#define CHANGE_LEVEL_START_TICKS 4
DECL|macro|SBNI_INTERNAL_QUEUE_SIZE
mdefine_line|#define SBNI_INTERNAL_QUEUE_SIZE 10&t;/* 100 ? */
DECL|macro|PACKET_FIRST_FRAME
mdefine_line|#define PACKET_FIRST_FRAME (unsigned short)0x8000
DECL|macro|RECEIVE_FRAME_RESEND
mdefine_line|#define RECEIVE_FRAME_RESEND (unsigned short)0x0800
DECL|macro|PACKET_RESEND
mdefine_line|#define PACKET_RESEND 0x4000
DECL|macro|PACKET_SEND_OK
mdefine_line|#define PACKET_SEND_OK 0x3000
DECL|macro|PACKET_LEN_MASK
mdefine_line|#define PACKET_LEN_MASK (unsigned short)0x03ff
DECL|macro|PACKET_INF_MASK
mdefine_line|#define PACKET_INF_MASK (unsigned short)0x7000
DECL|macro|ETHER_ADDR_LEN
mdefine_line|#define ETHER_ADDR_LEN 6
DECL|macro|SBNI_TIMEOUT
mdefine_line|#define SBNI_TIMEOUT HZ/10&t;/* ticks to wait for pong or packet */
multiline_comment|/* sbni watchdog called SBNI_HZ times per sec. */
DECL|struct|sbni_in_stats
r_struct
id|sbni_in_stats
(brace
DECL|member|all_rx_number
r_int
r_int
id|all_rx_number
suffix:semicolon
DECL|member|bad_rx_number
r_int
r_int
id|bad_rx_number
suffix:semicolon
DECL|member|timeout_number
r_int
r_int
id|timeout_number
suffix:semicolon
DECL|member|all_tx_number
r_int
r_int
id|all_tx_number
suffix:semicolon
DECL|member|resend_tx_number
r_int
r_int
id|resend_tx_number
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; *    Board-specific info in dev-&gt;priv. &n; */
DECL|struct|net_local
r_struct
id|net_local
(brace
DECL|member|stats
r_struct
id|net_device_stats
id|stats
suffix:semicolon
DECL|member|watchdog
r_struct
id|timer_list
id|watchdog
suffix:semicolon
DECL|member|realframelen
r_int
r_int
id|realframelen
suffix:semicolon
multiline_comment|/* the current size of the SB-frame */
DECL|member|eth_trans_buffer_len
r_int
r_int
id|eth_trans_buffer_len
suffix:semicolon
multiline_comment|/* tx buffer length */
DECL|member|outpos
r_int
r_int
id|outpos
suffix:semicolon
DECL|member|inppos
r_int
r_int
id|inppos
suffix:semicolon
DECL|member|frame_len
r_int
r_int
id|frame_len
suffix:semicolon
multiline_comment|/* The set SB-frame size */
DECL|member|tr_err
r_int
r_int
id|tr_err
suffix:semicolon
DECL|member|timer_ticks
r_int
r_int
id|timer_ticks
suffix:semicolon
DECL|member|last_receive_OK
id|BOOLEAN
id|last_receive_OK
suffix:semicolon
DECL|member|tr_resend
id|BOOLEAN
id|tr_resend
suffix:semicolon
DECL|member|wait_frame_number
r_int
r_char
id|wait_frame_number
suffix:semicolon
DECL|member|eth_trans_buffer
r_int
r_char
id|eth_trans_buffer
(braket
l_int|1520
)braket
suffix:semicolon
multiline_comment|/* tx buffer */
DECL|member|HSCounter
r_int
r_char
id|HSCounter
suffix:semicolon
multiline_comment|/* Reserved field */
DECL|member|eth_rcv_buffer
r_int
r_char
id|eth_rcv_buffer
(braket
l_int|2600
)braket
suffix:semicolon
multiline_comment|/* rx buffer */
DECL|member|csr1
r_struct
id|sbni_csr1
id|csr1
suffix:semicolon
multiline_comment|/* Internal Statistics */
DECL|member|in_stats
r_struct
id|sbni_in_stats
id|in_stats
suffix:semicolon
DECL|member|rxl_curr
r_int
id|rxl_curr
suffix:semicolon
multiline_comment|/* current receive level value [0..0xf] */
DECL|member|rxl_delta
r_int
id|rxl_delta
suffix:semicolon
multiline_comment|/* receive level delta (+1, -1)&n;&t;&t;&t;&t;   rxl_delta == 0 - receive level&n;&t;&t;&t;&t;   autodetection&n;&t;&t;&t;&t;   disabled            */
DECL|member|ok_curr
r_int
r_int
id|ok_curr
suffix:semicolon
multiline_comment|/* current ok frames received           */
DECL|member|ok_prev
r_int
r_int
id|ok_prev
suffix:semicolon
multiline_comment|/* previous ok frames received          */
DECL|member|timeout_rxl
r_int
r_int
id|timeout_rxl
suffix:semicolon
DECL|member|queue
r_struct
id|sk_buff_head
id|queue
suffix:semicolon
DECL|member|currframe
r_struct
id|sk_buff
op_star
id|currframe
suffix:semicolon
DECL|member|waitack
id|BOOLEAN
id|waitack
suffix:semicolon
DECL|member|m
r_struct
id|net_device
op_star
id|m
suffix:semicolon
multiline_comment|/* master */
DECL|member|me
r_struct
id|net_device
op_star
id|me
suffix:semicolon
multiline_comment|/* me */
DECL|member|next_lp
r_struct
id|net_local
op_star
id|next_lp
suffix:semicolon
multiline_comment|/* next lp */
DECL|member|carrier
r_int
id|carrier
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|sbni_hard_header
r_struct
id|sbni_hard_header
(brace
multiline_comment|/* internal sbni stuff */
DECL|member|crc
r_int
r_int
id|crc
suffix:semicolon
multiline_comment|/* 4 */
DECL|member|packetlen
r_int
r_int
id|packetlen
suffix:semicolon
multiline_comment|/* 2 */
DECL|member|number
r_int
r_char
id|number
suffix:semicolon
multiline_comment|/* 1 */
DECL|member|reserv
r_int
r_char
id|reserv
suffix:semicolon
multiline_comment|/* 1 */
multiline_comment|/* 8 */
multiline_comment|/* ethernet stuff */
DECL|member|h_dest
r_int
r_char
id|h_dest
(braket
id|ETH_ALEN
)braket
suffix:semicolon
multiline_comment|/* destination eth addr */
DECL|member|h_source
r_int
r_char
id|h_source
(braket
id|ETH_ALEN
)braket
suffix:semicolon
multiline_comment|/* source ether addr    */
DECL|member|h_proto
r_int
r_int
id|h_proto
suffix:semicolon
multiline_comment|/* packet type ID field */
multiline_comment|/* +14 */
multiline_comment|/* 22 */
)brace
suffix:semicolon
DECL|macro|SBNI_HH_SZ
mdefine_line|#define SBNI_HH_SZ 22
DECL|struct|sbni_flags
r_struct
id|sbni_flags
(brace
DECL|member|rxl
r_int
id|rxl
suffix:colon
l_int|4
suffix:semicolon
DECL|member|rate
r_int
id|rate
suffix:colon
l_int|2
suffix:semicolon
DECL|member|fixed_rxl
r_int
id|fixed_rxl
suffix:colon
l_int|1
suffix:semicolon
DECL|member|fixed_rate
r_int
id|fixed_rate
suffix:colon
l_int|1
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|RCV_NO
mdefine_line|#define RCV_NO 0
DECL|macro|RCV_OK
mdefine_line|#define RCV_OK 1
DECL|macro|RCV_WR
mdefine_line|#define RCV_WR 2
DECL|macro|SIOCDEVGETINSTATS
mdefine_line|#define SIOCDEVGETINSTATS &t;SIOCDEVPRIVATE
DECL|macro|SIOCDEVRESINSTATS
mdefine_line|#define SIOCDEVRESINSTATS &t;SIOCDEVPRIVATE+1
DECL|macro|SIOCDEVGHWSTATE
mdefine_line|#define SIOCDEVGHWSTATE   &t;SIOCDEVPRIVATE+2
DECL|macro|SIOCDEVSHWSTATE
mdefine_line|#define SIOCDEVSHWSTATE   &t;SIOCDEVPRIVATE+3
DECL|macro|SIOCDEVENSLAVE
mdefine_line|#define SIOCDEVENSLAVE  &t;SIOCDEVPRIVATE+4
DECL|macro|SIOCDEVEMANSIPATE
mdefine_line|#define SIOCDEVEMANSIPATE  &t;SIOCDEVPRIVATE+5
macro_line|#endif&t;&t;&t;&t;/* __SBNI_H */
eof
