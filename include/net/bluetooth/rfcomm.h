multiline_comment|/* &n;   RFCOMM implementation for Linux Bluetooth stack (BlueZ).&n;   Copyright (C) 2002 Maxim Krasnyansky &lt;maxk@qualcomm.com&gt;&n;   Copyright (C) 2002 Marcel Holtmann &lt;marcel@holtmann.org&gt;&n;&n;   This program is free software; you can redistribute it and/or modify&n;   it under the terms of the GNU General Public License version 2 as&n;   published by the Free Software Foundation;&n;&n;   THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS&n;   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n;   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF THIRD PARTY RIGHTS.&n;   IN NO EVENT SHALL THE COPYRIGHT HOLDER(S) AND AUTHOR(S) BE LIABLE FOR ANY&n;   CLAIM, OR ANY SPECIAL INDIRECT OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES &n;   WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN &n;   ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF &n;   OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.&n;&n;   ALL LIABILITY, INCLUDING LIABILITY FOR INFRINGEMENT OF ANY PATENTS, &n;   COPYRIGHTS, TRADEMARKS OR OTHER RIGHTS, RELATING TO USE OF THIS &n;   SOFTWARE IS DISCLAIMED.&n;*/
macro_line|#ifndef __RFCOMM_H
DECL|macro|__RFCOMM_H
mdefine_line|#define __RFCOMM_H
DECL|macro|RFCOMM_PSM
mdefine_line|#define RFCOMM_PSM 3
DECL|macro|RFCOMM_CONN_TIMEOUT
mdefine_line|#define RFCOMM_CONN_TIMEOUT (HZ * 30)
DECL|macro|RFCOMM_DISC_TIMEOUT
mdefine_line|#define RFCOMM_DISC_TIMEOUT (HZ * 20)
DECL|macro|RFCOMM_AUTH_TIMEOUT
mdefine_line|#define RFCOMM_AUTH_TIMEOUT (HZ * 25)
DECL|macro|RFCOMM_DEFAULT_MTU
mdefine_line|#define RFCOMM_DEFAULT_MTU&t;127
DECL|macro|RFCOMM_DEFAULT_CREDITS
mdefine_line|#define RFCOMM_DEFAULT_CREDITS&t;7
DECL|macro|RFCOMM_MAX_L2CAP_MTU
mdefine_line|#define RFCOMM_MAX_L2CAP_MTU&t;1024
DECL|macro|RFCOMM_MAX_CREDITS
mdefine_line|#define RFCOMM_MAX_CREDITS&t;40
DECL|macro|RFCOMM_SKB_HEAD_RESERVE
mdefine_line|#define RFCOMM_SKB_HEAD_RESERVE&t;8
DECL|macro|RFCOMM_SKB_TAIL_RESERVE
mdefine_line|#define RFCOMM_SKB_TAIL_RESERVE&t;2
DECL|macro|RFCOMM_SKB_RESERVE
mdefine_line|#define RFCOMM_SKB_RESERVE  (RFCOMM_SKB_HEAD_RESERVE + RFCOMM_SKB_TAIL_RESERVE)
DECL|macro|RFCOMM_SABM
mdefine_line|#define RFCOMM_SABM&t;0x2f
DECL|macro|RFCOMM_DISC
mdefine_line|#define RFCOMM_DISC&t;0x43
DECL|macro|RFCOMM_UA
mdefine_line|#define RFCOMM_UA&t;0x63
DECL|macro|RFCOMM_DM
mdefine_line|#define RFCOMM_DM&t;0x0f
DECL|macro|RFCOMM_UIH
mdefine_line|#define RFCOMM_UIH&t;0xef
DECL|macro|RFCOMM_TEST
mdefine_line|#define RFCOMM_TEST&t;0x08
DECL|macro|RFCOMM_FCON
mdefine_line|#define RFCOMM_FCON&t;0x28
DECL|macro|RFCOMM_FCOFF
mdefine_line|#define RFCOMM_FCOFF&t;0x18
DECL|macro|RFCOMM_MSC
mdefine_line|#define RFCOMM_MSC&t;0x38
DECL|macro|RFCOMM_RPN
mdefine_line|#define RFCOMM_RPN&t;0x24
DECL|macro|RFCOMM_RLS
mdefine_line|#define RFCOMM_RLS&t;0x14
DECL|macro|RFCOMM_PN
mdefine_line|#define RFCOMM_PN&t;0x20
DECL|macro|RFCOMM_NSC
mdefine_line|#define RFCOMM_NSC&t;0x04
DECL|macro|RFCOMM_V24_FC
mdefine_line|#define RFCOMM_V24_FC&t;0x02
DECL|macro|RFCOMM_V24_RTC
mdefine_line|#define RFCOMM_V24_RTC&t;0x04
DECL|macro|RFCOMM_V24_RTR
mdefine_line|#define RFCOMM_V24_RTR&t;0x08
DECL|macro|RFCOMM_V24_IC
mdefine_line|#define RFCOMM_V24_IC&t;0x40
DECL|macro|RFCOMM_V24_DV
mdefine_line|#define RFCOMM_V24_DV&t;0x80
DECL|macro|RFCOMM_RPN_BR_2400
mdefine_line|#define RFCOMM_RPN_BR_2400&t;0x0
DECL|macro|RFCOMM_RPN_BR_4800
mdefine_line|#define RFCOMM_RPN_BR_4800&t;0x1
DECL|macro|RFCOMM_RPN_BR_7200
mdefine_line|#define RFCOMM_RPN_BR_7200&t;0x2
DECL|macro|RFCOMM_RPN_BR_9600
mdefine_line|#define RFCOMM_RPN_BR_9600&t;0x3
DECL|macro|RFCOMM_RPN_BR_19200
mdefine_line|#define RFCOMM_RPN_BR_19200&t;0x4
DECL|macro|RFCOMM_RPN_BR_38400
mdefine_line|#define RFCOMM_RPN_BR_38400&t;0x5
DECL|macro|RFCOMM_RPN_BR_57600
mdefine_line|#define RFCOMM_RPN_BR_57600&t;0x6
DECL|macro|RFCOMM_RPN_BR_115200
mdefine_line|#define RFCOMM_RPN_BR_115200&t;0x7
DECL|macro|RFCOMM_RPN_BR_230400
mdefine_line|#define RFCOMM_RPN_BR_230400&t;0x8
DECL|macro|RFCOMM_RPN_DATA_5
mdefine_line|#define RFCOMM_RPN_DATA_5&t;0x0
DECL|macro|RFCOMM_RPN_DATA_6
mdefine_line|#define RFCOMM_RPN_DATA_6&t;0x1
DECL|macro|RFCOMM_RPN_DATA_7
mdefine_line|#define RFCOMM_RPN_DATA_7&t;0x2
DECL|macro|RFCOMM_RPN_DATA_8
mdefine_line|#define RFCOMM_RPN_DATA_8&t;0x3
DECL|macro|RFCOMM_RPN_STOP_1
mdefine_line|#define RFCOMM_RPN_STOP_1&t;0
DECL|macro|RFCOMM_RPN_STOP_15
mdefine_line|#define RFCOMM_RPN_STOP_15&t;1
DECL|macro|RFCOMM_RPN_PARITY_NONE
mdefine_line|#define RFCOMM_RPN_PARITY_NONE&t;0x0
DECL|macro|RFCOMM_RPN_PARITY_ODD
mdefine_line|#define RFCOMM_RPN_PARITY_ODD&t;0x4
DECL|macro|RFCOMM_RPN_PARITY_EVEN
mdefine_line|#define RFCOMM_RPN_PARITY_EVEN&t;0x5
DECL|macro|RFCOMM_RPN_PARITY_MARK
mdefine_line|#define RFCOMM_RPN_PARITY_MARK&t;0x6
DECL|macro|RFCOMM_RPN_PARITY_SPACE
mdefine_line|#define RFCOMM_RPN_PARITY_SPACE&t;0x7
DECL|macro|RFCOMM_RPN_FLOW_NONE
mdefine_line|#define RFCOMM_RPN_FLOW_NONE&t;0x00
DECL|macro|RFCOMM_RPN_XON_CHAR
mdefine_line|#define RFCOMM_RPN_XON_CHAR&t;0x11
DECL|macro|RFCOMM_RPN_XOFF_CHAR
mdefine_line|#define RFCOMM_RPN_XOFF_CHAR&t;0x13
DECL|macro|RFCOMM_RPN_PM_BITRATE
mdefine_line|#define RFCOMM_RPN_PM_BITRATE&t;&t;0x0001
DECL|macro|RFCOMM_RPN_PM_DATA
mdefine_line|#define RFCOMM_RPN_PM_DATA&t;&t;0x0002
DECL|macro|RFCOMM_RPN_PM_STOP
mdefine_line|#define RFCOMM_RPN_PM_STOP&t;&t;0x0004
DECL|macro|RFCOMM_RPN_PM_PARITY
mdefine_line|#define RFCOMM_RPN_PM_PARITY&t;&t;0x0008
DECL|macro|RFCOMM_RPN_PM_PARITY_TYPE
mdefine_line|#define RFCOMM_RPN_PM_PARITY_TYPE&t;0x0010
DECL|macro|RFCOMM_RPN_PM_XON
mdefine_line|#define RFCOMM_RPN_PM_XON&t;&t;0x0020
DECL|macro|RFCOMM_RPN_PM_XOFF
mdefine_line|#define RFCOMM_RPN_PM_XOFF&t;&t;0x0040
DECL|macro|RFCOMM_RPN_PM_FLOW
mdefine_line|#define RFCOMM_RPN_PM_FLOW&t;&t;0x3F00
DECL|macro|RFCOMM_RPN_PM_ALL
mdefine_line|#define RFCOMM_RPN_PM_ALL&t;&t;0x3F7F
DECL|struct|rfcomm_hdr
r_struct
id|rfcomm_hdr
(brace
DECL|member|addr
id|u8
id|addr
suffix:semicolon
DECL|member|ctrl
id|u8
id|ctrl
suffix:semicolon
DECL|member|len
id|u8
id|len
suffix:semicolon
singleline_comment|// Actual size can be 2 bytes
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|rfcomm_cmd
r_struct
id|rfcomm_cmd
(brace
DECL|member|addr
id|u8
id|addr
suffix:semicolon
DECL|member|ctrl
id|u8
id|ctrl
suffix:semicolon
DECL|member|len
id|u8
id|len
suffix:semicolon
DECL|member|fcs
id|u8
id|fcs
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|rfcomm_mcc
r_struct
id|rfcomm_mcc
(brace
DECL|member|type
id|u8
id|type
suffix:semicolon
DECL|member|len
id|u8
id|len
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|rfcomm_pn
r_struct
id|rfcomm_pn
(brace
DECL|member|dlci
id|u8
id|dlci
suffix:semicolon
DECL|member|flow_ctrl
id|u8
id|flow_ctrl
suffix:semicolon
DECL|member|priority
id|u8
id|priority
suffix:semicolon
DECL|member|ack_timer
id|u8
id|ack_timer
suffix:semicolon
DECL|member|mtu
id|u16
id|mtu
suffix:semicolon
DECL|member|max_retrans
id|u8
id|max_retrans
suffix:semicolon
DECL|member|credits
id|u8
id|credits
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|rfcomm_rpn
r_struct
id|rfcomm_rpn
(brace
DECL|member|dlci
id|u8
id|dlci
suffix:semicolon
DECL|member|bit_rate
id|u8
id|bit_rate
suffix:semicolon
DECL|member|line_settings
id|u8
id|line_settings
suffix:semicolon
DECL|member|flow_ctrl
id|u8
id|flow_ctrl
suffix:semicolon
DECL|member|xon_char
id|u8
id|xon_char
suffix:semicolon
DECL|member|xoff_char
id|u8
id|xoff_char
suffix:semicolon
DECL|member|param_mask
id|u16
id|param_mask
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|rfcomm_rls
r_struct
id|rfcomm_rls
(brace
DECL|member|dlci
id|u8
id|dlci
suffix:semicolon
DECL|member|status
id|u8
id|status
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|rfcomm_msc
r_struct
id|rfcomm_msc
(brace
DECL|member|dlci
id|u8
id|dlci
suffix:semicolon
DECL|member|v24_sig
id|u8
id|v24_sig
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* ---- Core structures, flags etc ---- */
DECL|struct|rfcomm_session
r_struct
id|rfcomm_session
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|sock
r_struct
id|socket
op_star
id|sock
suffix:semicolon
DECL|member|state
r_int
r_int
id|state
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|refcnt
id|atomic_t
id|refcnt
suffix:semicolon
DECL|member|initiator
r_int
id|initiator
suffix:semicolon
multiline_comment|/* Default DLC parameters */
DECL|member|cfc
r_int
id|cfc
suffix:semicolon
DECL|member|mtu
id|uint
id|mtu
suffix:semicolon
DECL|member|dlcs
r_struct
id|list_head
id|dlcs
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|rfcomm_dlc
r_struct
id|rfcomm_dlc
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|session
r_struct
id|rfcomm_session
op_star
id|session
suffix:semicolon
DECL|member|tx_queue
r_struct
id|sk_buff_head
id|tx_queue
suffix:semicolon
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|state
r_int
r_int
id|state
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|refcnt
id|atomic_t
id|refcnt
suffix:semicolon
DECL|member|dlci
id|u8
id|dlci
suffix:semicolon
DECL|member|addr
id|u8
id|addr
suffix:semicolon
DECL|member|priority
id|u8
id|priority
suffix:semicolon
DECL|member|v24_sig
id|u8
id|v24_sig
suffix:semicolon
DECL|member|mscex
id|u8
id|mscex
suffix:semicolon
DECL|member|link_mode
id|u32
id|link_mode
suffix:semicolon
DECL|member|mtu
id|uint
id|mtu
suffix:semicolon
DECL|member|cfc
id|uint
id|cfc
suffix:semicolon
DECL|member|rx_credits
id|uint
id|rx_credits
suffix:semicolon
DECL|member|tx_credits
id|uint
id|tx_credits
suffix:semicolon
DECL|member|owner
r_void
op_star
id|owner
suffix:semicolon
DECL|member|data_ready
r_void
(paren
op_star
id|data_ready
)paren
(paren
r_struct
id|rfcomm_dlc
op_star
id|d
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
DECL|member|state_change
r_void
(paren
op_star
id|state_change
)paren
(paren
r_struct
id|rfcomm_dlc
op_star
id|d
comma
r_int
id|err
)paren
suffix:semicolon
DECL|member|modem_status
r_void
(paren
op_star
id|modem_status
)paren
(paren
r_struct
id|rfcomm_dlc
op_star
id|d
comma
id|u8
id|v24_sig
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* DLC and session flags */
DECL|macro|RFCOMM_RX_THROTTLED
mdefine_line|#define RFCOMM_RX_THROTTLED 0
DECL|macro|RFCOMM_TX_THROTTLED
mdefine_line|#define RFCOMM_TX_THROTTLED 1
DECL|macro|RFCOMM_TIMED_OUT
mdefine_line|#define RFCOMM_TIMED_OUT    2
DECL|macro|RFCOMM_MSC_PENDING
mdefine_line|#define RFCOMM_MSC_PENDING  3 
DECL|macro|RFCOMM_AUTH_PENDING
mdefine_line|#define RFCOMM_AUTH_PENDING 4
DECL|macro|RFCOMM_AUTH_ACCEPT
mdefine_line|#define RFCOMM_AUTH_ACCEPT  5
DECL|macro|RFCOMM_AUTH_REJECT
mdefine_line|#define RFCOMM_AUTH_REJECT  6
multiline_comment|/* Scheduling flags and events */
DECL|macro|RFCOMM_SCHED_STATE
mdefine_line|#define RFCOMM_SCHED_STATE  0
DECL|macro|RFCOMM_SCHED_RX
mdefine_line|#define RFCOMM_SCHED_RX     1
DECL|macro|RFCOMM_SCHED_TX
mdefine_line|#define RFCOMM_SCHED_TX     2
DECL|macro|RFCOMM_SCHED_TIMEO
mdefine_line|#define RFCOMM_SCHED_TIMEO  3
DECL|macro|RFCOMM_SCHED_AUTH
mdefine_line|#define RFCOMM_SCHED_AUTH   4
DECL|macro|RFCOMM_SCHED_WAKEUP
mdefine_line|#define RFCOMM_SCHED_WAKEUP 31
multiline_comment|/* MSC exchange flags */
DECL|macro|RFCOMM_MSCEX_TX
mdefine_line|#define RFCOMM_MSCEX_TX     1
DECL|macro|RFCOMM_MSCEX_RX
mdefine_line|#define RFCOMM_MSCEX_RX     2
DECL|macro|RFCOMM_MSCEX_OK
mdefine_line|#define RFCOMM_MSCEX_OK     (RFCOMM_MSCEX_TX + RFCOMM_MSCEX_RX)
multiline_comment|/* CFC states */
DECL|macro|RFCOMM_CFC_UNKNOWN
mdefine_line|#define RFCOMM_CFC_UNKNOWN  -1
DECL|macro|RFCOMM_CFC_DISABLED
mdefine_line|#define RFCOMM_CFC_DISABLED 0
DECL|macro|RFCOMM_CFC_ENABLED
mdefine_line|#define RFCOMM_CFC_ENABLED  RFCOMM_MAX_CREDITS
multiline_comment|/* ---- RFCOMM DLCs (channels) ---- */
r_struct
id|rfcomm_dlc
op_star
id|rfcomm_dlc_alloc
c_func
(paren
r_int
id|prio
)paren
suffix:semicolon
r_void
id|rfcomm_dlc_free
c_func
(paren
r_struct
id|rfcomm_dlc
op_star
id|d
)paren
suffix:semicolon
r_int
id|rfcomm_dlc_open
c_func
(paren
r_struct
id|rfcomm_dlc
op_star
id|d
comma
id|bdaddr_t
op_star
id|src
comma
id|bdaddr_t
op_star
id|dst
comma
id|u8
id|channel
)paren
suffix:semicolon
r_int
id|rfcomm_dlc_close
c_func
(paren
r_struct
id|rfcomm_dlc
op_star
id|d
comma
r_int
id|reason
)paren
suffix:semicolon
r_int
id|rfcomm_dlc_send
c_func
(paren
r_struct
id|rfcomm_dlc
op_star
id|d
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_int
id|rfcomm_dlc_set_modem_status
c_func
(paren
r_struct
id|rfcomm_dlc
op_star
id|d
comma
id|u8
id|v24_sig
)paren
suffix:semicolon
r_int
id|rfcomm_dlc_get_modem_status
c_func
(paren
r_struct
id|rfcomm_dlc
op_star
id|d
comma
id|u8
op_star
id|v24_sig
)paren
suffix:semicolon
DECL|macro|rfcomm_dlc_lock
mdefine_line|#define rfcomm_dlc_lock(d)     spin_lock(&amp;d-&gt;lock)
DECL|macro|rfcomm_dlc_unlock
mdefine_line|#define rfcomm_dlc_unlock(d)   spin_unlock(&amp;d-&gt;lock)
DECL|function|rfcomm_dlc_hold
r_static
r_inline
r_void
id|rfcomm_dlc_hold
c_func
(paren
r_struct
id|rfcomm_dlc
op_star
id|d
)paren
(brace
id|atomic_inc
c_func
(paren
op_amp
id|d-&gt;refcnt
)paren
suffix:semicolon
)brace
DECL|function|rfcomm_dlc_put
r_static
r_inline
r_void
id|rfcomm_dlc_put
c_func
(paren
r_struct
id|rfcomm_dlc
op_star
id|d
)paren
(brace
r_if
c_cond
(paren
id|atomic_dec_and_test
c_func
(paren
op_amp
id|d-&gt;refcnt
)paren
)paren
id|rfcomm_dlc_free
c_func
(paren
id|d
)paren
suffix:semicolon
)brace
r_extern
r_void
id|FASTCALL
c_func
(paren
id|__rfcomm_dlc_throttle
c_func
(paren
r_struct
id|rfcomm_dlc
op_star
id|d
)paren
)paren
suffix:semicolon
r_extern
r_void
id|FASTCALL
c_func
(paren
id|__rfcomm_dlc_unthrottle
c_func
(paren
r_struct
id|rfcomm_dlc
op_star
id|d
)paren
)paren
suffix:semicolon
DECL|function|rfcomm_dlc_throttle
r_static
r_inline
r_void
id|rfcomm_dlc_throttle
c_func
(paren
r_struct
id|rfcomm_dlc
op_star
id|d
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|test_and_set_bit
c_func
(paren
id|RFCOMM_RX_THROTTLED
comma
op_amp
id|d-&gt;flags
)paren
)paren
id|__rfcomm_dlc_throttle
c_func
(paren
id|d
)paren
suffix:semicolon
)brace
DECL|function|rfcomm_dlc_unthrottle
r_static
r_inline
r_void
id|rfcomm_dlc_unthrottle
c_func
(paren
r_struct
id|rfcomm_dlc
op_star
id|d
)paren
(brace
r_if
c_cond
(paren
id|test_and_clear_bit
c_func
(paren
id|RFCOMM_RX_THROTTLED
comma
op_amp
id|d-&gt;flags
)paren
)paren
id|__rfcomm_dlc_unthrottle
c_func
(paren
id|d
)paren
suffix:semicolon
)brace
multiline_comment|/* ---- RFCOMM sessions ---- */
r_void
id|rfcomm_session_getaddr
c_func
(paren
r_struct
id|rfcomm_session
op_star
id|s
comma
id|bdaddr_t
op_star
id|src
comma
id|bdaddr_t
op_star
id|dst
)paren
suffix:semicolon
DECL|function|rfcomm_session_hold
r_static
r_inline
r_void
id|rfcomm_session_hold
c_func
(paren
r_struct
id|rfcomm_session
op_star
id|s
)paren
(brace
id|atomic_inc
c_func
(paren
op_amp
id|s-&gt;refcnt
)paren
suffix:semicolon
)brace
multiline_comment|/* ---- RFCOMM chechsum ---- */
r_extern
id|u8
id|rfcomm_crc_table
(braket
)braket
suffix:semicolon
multiline_comment|/* ---- RFCOMM sockets ---- */
DECL|struct|sockaddr_rc
r_struct
id|sockaddr_rc
(brace
DECL|member|rc_family
id|sa_family_t
id|rc_family
suffix:semicolon
DECL|member|rc_bdaddr
id|bdaddr_t
id|rc_bdaddr
suffix:semicolon
DECL|member|rc_channel
id|u8
id|rc_channel
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|RFCOMM_CONNINFO
mdefine_line|#define RFCOMM_CONNINFO&t;0x02
DECL|struct|rfcomm_conninfo
r_struct
id|rfcomm_conninfo
(brace
DECL|member|hci_handle
id|__u16
id|hci_handle
suffix:semicolon
DECL|member|dev_class
id|__u8
id|dev_class
(braket
l_int|3
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|RFCOMM_LM
mdefine_line|#define RFCOMM_LM&t;0x03
DECL|macro|RFCOMM_LM_MASTER
mdefine_line|#define RFCOMM_LM_MASTER&t;0x0001
DECL|macro|RFCOMM_LM_AUTH
mdefine_line|#define RFCOMM_LM_AUTH&t;&t;0x0002
DECL|macro|RFCOMM_LM_ENCRYPT
mdefine_line|#define RFCOMM_LM_ENCRYPT&t;0x0004
DECL|macro|RFCOMM_LM_TRUSTED
mdefine_line|#define RFCOMM_LM_TRUSTED&t;0x0008
DECL|macro|RFCOMM_LM_RELIABLE
mdefine_line|#define RFCOMM_LM_RELIABLE&t;0x0010
DECL|macro|RFCOMM_LM_SECURE
mdefine_line|#define RFCOMM_LM_SECURE&t;0x0020
DECL|macro|rfcomm_pi
mdefine_line|#define rfcomm_pi(sk)   ((struct rfcomm_pinfo *)sk-&gt;sk_protinfo)
DECL|struct|rfcomm_pinfo
r_struct
id|rfcomm_pinfo
(brace
DECL|member|dlc
r_struct
id|rfcomm_dlc
op_star
id|dlc
suffix:semicolon
DECL|member|channel
id|u8
id|channel
suffix:semicolon
DECL|member|link_mode
id|u32
id|link_mode
suffix:semicolon
)brace
suffix:semicolon
r_int
id|rfcomm_init_sockets
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|rfcomm_cleanup_sockets
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|rfcomm_connect_ind
c_func
(paren
r_struct
id|rfcomm_session
op_star
id|s
comma
id|u8
id|channel
comma
r_struct
id|rfcomm_dlc
op_star
op_star
id|d
)paren
suffix:semicolon
multiline_comment|/* ---- RFCOMM TTY ---- */
DECL|macro|RFCOMM_MAX_DEV
mdefine_line|#define RFCOMM_MAX_DEV  256
DECL|macro|RFCOMMCREATEDEV
mdefine_line|#define RFCOMMCREATEDEV&t;&t;_IOW(&squot;R&squot;, 200, int)
DECL|macro|RFCOMMRELEASEDEV
mdefine_line|#define RFCOMMRELEASEDEV&t;_IOW(&squot;R&squot;, 201, int)
DECL|macro|RFCOMMGETDEVLIST
mdefine_line|#define RFCOMMGETDEVLIST&t;_IOR(&squot;R&squot;, 210, int)
DECL|macro|RFCOMMGETDEVINFO
mdefine_line|#define RFCOMMGETDEVINFO&t;_IOR(&squot;R&squot;, 211, int)
DECL|macro|RFCOMMSTEALDLC
mdefine_line|#define RFCOMMSTEALDLC&t;&t;_IOW(&squot;R&squot;, 220, int)
DECL|macro|RFCOMM_REUSE_DLC
mdefine_line|#define RFCOMM_REUSE_DLC      0
DECL|macro|RFCOMM_RELEASE_ONHUP
mdefine_line|#define RFCOMM_RELEASE_ONHUP  1
DECL|macro|RFCOMM_HANGUP_NOW
mdefine_line|#define RFCOMM_HANGUP_NOW     2
DECL|macro|RFCOMM_TTY_ATTACHED
mdefine_line|#define RFCOMM_TTY_ATTACHED   3
DECL|struct|rfcomm_dev_req
r_struct
id|rfcomm_dev_req
(brace
DECL|member|dev_id
id|s16
id|dev_id
suffix:semicolon
DECL|member|flags
id|u32
id|flags
suffix:semicolon
DECL|member|src
id|bdaddr_t
id|src
suffix:semicolon
DECL|member|dst
id|bdaddr_t
id|dst
suffix:semicolon
DECL|member|channel
id|u8
id|channel
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|rfcomm_dev_info
r_struct
id|rfcomm_dev_info
(brace
DECL|member|id
id|s16
id|id
suffix:semicolon
DECL|member|flags
id|u32
id|flags
suffix:semicolon
DECL|member|state
id|u16
id|state
suffix:semicolon
DECL|member|src
id|bdaddr_t
id|src
suffix:semicolon
DECL|member|dst
id|bdaddr_t
id|dst
suffix:semicolon
DECL|member|channel
id|u8
id|channel
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|rfcomm_dev_list_req
r_struct
id|rfcomm_dev_list_req
(brace
DECL|member|dev_num
id|u16
id|dev_num
suffix:semicolon
DECL|member|dev_info
r_struct
id|rfcomm_dev_info
id|dev_info
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
r_int
id|rfcomm_dev_ioctl
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
r_int
id|cmd
comma
r_void
id|__user
op_star
id|arg
)paren
suffix:semicolon
r_int
id|rfcomm_init_ttys
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|rfcomm_cleanup_ttys
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_struct
id|proc_dir_entry
op_star
id|proc_bt_rfcomm
suffix:semicolon
macro_line|#endif /* __RFCOMM_H */
eof
