multiline_comment|/* $Id: isdnl1.h,v 2.9.6.3 2001/09/23 22:24:49 kai Exp $&n; *&n; * Layer 1 defines&n; *&n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; */
DECL|macro|D_RCVBUFREADY
mdefine_line|#define D_RCVBUFREADY&t;0
DECL|macro|D_XMTBUFREADY
mdefine_line|#define D_XMTBUFREADY&t;1
DECL|macro|D_L1STATECHANGE
mdefine_line|#define D_L1STATECHANGE&t;2
DECL|macro|D_CLEARBUSY
mdefine_line|#define D_CLEARBUSY&t;3
DECL|macro|D_RX_MON0
mdefine_line|#define D_RX_MON0&t;4
DECL|macro|D_RX_MON1
mdefine_line|#define D_RX_MON1&t;5
DECL|macro|D_TX_MON0
mdefine_line|#define D_TX_MON0&t;6
DECL|macro|D_TX_MON1
mdefine_line|#define D_TX_MON1&t;7
DECL|macro|E_RCVBUFREADY
mdefine_line|#define E_RCVBUFREADY&t;8
DECL|macro|B_RCVBUFREADY
mdefine_line|#define B_RCVBUFREADY   0
DECL|macro|B_XMTBUFREADY
mdefine_line|#define B_XMTBUFREADY   1
DECL|macro|B_CMPLREADY
mdefine_line|#define B_CMPLREADY     2
DECL|macro|B_LL_NOCARRIER
mdefine_line|#define B_LL_NOCARRIER&t;8
DECL|macro|B_LL_CONNECT
mdefine_line|#define B_LL_CONNECT&t;9
DECL|macro|B_LL_OK
mdefine_line|#define B_LL_OK&t;&t;10
r_extern
r_void
id|debugl1
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
suffix:semicolon
r_extern
r_void
id|DChannel_proc_xmt
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
)paren
suffix:semicolon
r_extern
r_void
id|DChannel_proc_rcv
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
)paren
suffix:semicolon
r_extern
r_void
id|l1_msg
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
r_int
id|pr
comma
r_void
op_star
id|arg
)paren
suffix:semicolon
r_extern
r_void
id|l1_msg_b
c_func
(paren
r_struct
id|PStack
op_star
id|st
comma
r_int
id|pr
comma
r_void
op_star
id|arg
)paren
suffix:semicolon
macro_line|#ifdef L2FRAME_DEBUG
r_extern
r_void
id|Logl2Frame
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_char
op_star
id|buf
comma
r_int
id|dir
)paren
suffix:semicolon
macro_line|#endif
r_static
r_inline
r_void
DECL|function|sched_b_event
id|sched_b_event
c_func
(paren
r_struct
id|BCState
op_star
id|bcs
comma
r_int
id|event
)paren
(brace
id|set_bit
c_func
(paren
id|event
comma
op_amp
id|bcs-&gt;event
)paren
suffix:semicolon
id|schedule_work
c_func
(paren
op_amp
id|bcs-&gt;work
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|sched_d_event
id|sched_d_event
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
r_int
id|event
)paren
(brace
id|set_bit
c_func
(paren
id|event
comma
op_amp
id|cs-&gt;event
)paren
suffix:semicolon
id|schedule_work
c_func
(paren
op_amp
id|cs-&gt;work
)paren
suffix:semicolon
)brace
multiline_comment|/* called with the card lock held */
r_static
r_inline
r_void
DECL|function|xmit_complete_b
id|xmit_complete_b
c_func
(paren
r_struct
id|BCState
op_star
id|bcs
)paren
(brace
id|skb_queue_tail
c_func
(paren
op_amp
id|bcs-&gt;cmpl_queue
comma
id|bcs-&gt;tx_skb
)paren
suffix:semicolon
id|sched_b_event
c_func
(paren
id|bcs
comma
id|B_CMPLREADY
)paren
suffix:semicolon
id|bcs-&gt;tx_skb
op_assign
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* called with the card lock held */
r_static
r_inline
r_void
DECL|function|xmit_ready_b
id|xmit_ready_b
c_func
(paren
r_struct
id|BCState
op_star
id|bcs
)paren
(brace
id|bcs-&gt;tx_skb
op_assign
id|skb_dequeue
c_func
(paren
op_amp
id|bcs-&gt;squeue
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bcs-&gt;tx_skb
)paren
(brace
id|bcs-&gt;count
op_assign
l_int|0
suffix:semicolon
id|set_bit
c_func
(paren
id|BC_FLG_BUSY
comma
op_amp
id|bcs-&gt;Flag
)paren
suffix:semicolon
id|bcs-&gt;cs
op_member_access_from_pointer
id|BC_Send_Data
c_func
(paren
id|bcs
)paren
suffix:semicolon
)brace
r_else
(brace
id|clear_bit
c_func
(paren
id|BC_FLG_BUSY
comma
op_amp
id|bcs-&gt;Flag
)paren
suffix:semicolon
id|sched_b_event
c_func
(paren
id|bcs
comma
id|B_XMTBUFREADY
)paren
suffix:semicolon
)brace
)brace
r_static
r_inline
r_void
DECL|function|xmit_data_req_b
id|xmit_data_req_b
c_func
(paren
r_struct
id|BCState
op_star
id|bcs
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|IsdnCardState
op_star
id|cs
op_assign
id|bcs-&gt;cs
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|cs-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bcs-&gt;tx_skb
)paren
(brace
id|skb_queue_tail
c_func
(paren
op_amp
id|bcs-&gt;squeue
comma
id|skb
)paren
suffix:semicolon
)brace
r_else
(brace
id|set_bit
c_func
(paren
id|BC_FLG_BUSY
comma
op_amp
id|bcs-&gt;Flag
)paren
suffix:semicolon
id|bcs-&gt;tx_skb
op_assign
id|skb
suffix:semicolon
id|bcs-&gt;count
op_assign
l_int|0
suffix:semicolon
id|bcs-&gt;cs
op_member_access_from_pointer
id|BC_Send_Data
c_func
(paren
id|bcs
)paren
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|cs-&gt;lock
comma
id|flags
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|xmit_pull_ind_b
id|xmit_pull_ind_b
c_func
(paren
r_struct
id|BCState
op_star
id|bcs
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|IsdnCardState
op_star
id|cs
op_assign
id|bcs-&gt;cs
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|cs-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bcs-&gt;tx_skb
)paren
(brace
id|WARN_ON
c_func
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_else
(brace
id|set_bit
c_func
(paren
id|BC_FLG_BUSY
comma
op_amp
id|bcs-&gt;Flag
)paren
suffix:semicolon
id|bcs-&gt;tx_skb
op_assign
id|skb
suffix:semicolon
id|bcs-&gt;count
op_assign
l_int|0
suffix:semicolon
id|bcs-&gt;cs
op_member_access_from_pointer
id|BC_Send_Data
c_func
(paren
id|bcs
)paren
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|cs-&gt;lock
comma
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/* If busy, the PH_PULL | CONFIRM scheduling is handled under&n; * the card lock by xmit_ready_b() above, so no race */
r_static
r_inline
r_void
DECL|function|xmit_pull_req_b
id|xmit_pull_req_b
c_func
(paren
r_struct
id|PStack
op_star
id|st
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|BCState
op_star
id|bcs
op_assign
id|st-&gt;l1.bcs
suffix:semicolon
r_struct
id|IsdnCardState
op_star
id|cs
op_assign
id|bcs-&gt;cs
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
id|busy
op_assign
l_int|0
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|cs-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bcs-&gt;tx_skb
)paren
(brace
id|set_bit
c_func
(paren
id|FLG_L1_PULL_REQ
comma
op_amp
id|st-&gt;l1.Flags
)paren
suffix:semicolon
id|busy
op_assign
l_int|1
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|cs-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|busy
)paren
id|L1L2
c_func
(paren
id|st
comma
id|PH_PULL
op_or
id|CONFIRM
comma
l_int|NULL
)paren
suffix:semicolon
)brace
multiline_comment|/* called with the card lock held */
r_static
r_inline
r_void
DECL|function|xmit_restart_b
id|xmit_restart_b
c_func
(paren
r_struct
id|BCState
op_star
id|bcs
)paren
(brace
macro_line|#ifdef ERROR_STATISTIC
id|bcs-&gt;err_tx
op_increment
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
op_logical_neg
id|bcs-&gt;tx_skb
)paren
(brace
id|WARN_ON
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|skb_push
c_func
(paren
id|bcs-&gt;tx_skb
comma
id|bcs-&gt;count
)paren
suffix:semicolon
id|bcs-&gt;tx_cnt
op_add_assign
id|bcs-&gt;count
suffix:semicolon
id|bcs-&gt;count
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Useful for HSCX work-alike&squot;s */
multiline_comment|/* ---------------------------------------------------------------------- */
multiline_comment|/* XPR - transmit pool ready */
multiline_comment|/* called with the card lock held */
r_static
r_inline
r_void
DECL|function|xmit_xpr_b
id|xmit_xpr_b
c_func
(paren
r_struct
id|BCState
op_star
id|bcs
)paren
(brace
multiline_comment|/* current frame? */
r_if
c_cond
(paren
id|bcs-&gt;tx_skb
)paren
(brace
multiline_comment|/* last frame not done yet? */
r_if
c_cond
(paren
id|bcs-&gt;tx_skb-&gt;len
)paren
(brace
id|bcs-&gt;cs
op_member_access_from_pointer
id|BC_Send_Data
c_func
(paren
id|bcs
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|xmit_complete_b
c_func
(paren
id|bcs
)paren
suffix:semicolon
id|bcs-&gt;count
op_assign
l_int|0
suffix:semicolon
)brace
id|xmit_ready_b
c_func
(paren
id|bcs
)paren
suffix:semicolon
)brace
multiline_comment|/* XDU - transmit data underrun */
multiline_comment|/* called with the card lock held */
r_static
r_inline
r_void
DECL|function|xmit_xdu_b
id|xmit_xdu_b
c_func
(paren
r_struct
id|BCState
op_star
id|bcs
comma
r_void
(paren
op_star
id|reset_xmit
)paren
(paren
r_struct
id|BCState
op_star
id|bcs
)paren
)paren
(brace
r_struct
id|IsdnCardState
op_star
id|cs
op_assign
id|bcs-&gt;cs
suffix:semicolon
r_if
c_cond
(paren
id|cs-&gt;debug
op_amp
id|L1_DEB_WARN
)paren
id|debugl1
c_func
(paren
id|cs
comma
l_string|&quot;HSCX %c EXIR XDU&quot;
comma
l_char|&squot;A&squot;
op_plus
id|bcs-&gt;channel
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bcs-&gt;mode
op_eq
id|L1_MODE_TRANS
)paren
(brace
id|cs
op_member_access_from_pointer
id|BC_Send_Data
c_func
(paren
id|bcs
)paren
suffix:semicolon
)brace
r_else
(brace
id|xmit_restart_b
c_func
(paren
id|bcs
)paren
suffix:semicolon
id|reset_xmit
c_func
(paren
id|bcs
)paren
suffix:semicolon
)brace
)brace
r_static
r_inline
r_int
r_char
op_star
DECL|function|xmit_fill_fifo_b
id|xmit_fill_fifo_b
c_func
(paren
r_struct
id|BCState
op_star
id|bcs
comma
r_int
id|fifo_size
comma
r_int
op_star
id|count
comma
r_int
op_star
id|more
)paren
(brace
r_struct
id|IsdnCardState
op_star
id|cs
op_assign
id|bcs-&gt;cs
suffix:semicolon
r_int
r_char
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
(paren
id|cs-&gt;debug
op_amp
id|L1_DEB_HSCX
)paren
op_logical_and
op_logical_neg
(paren
id|cs-&gt;debug
op_amp
id|L1_DEB_HSCX_FIFO
)paren
)paren
id|debugl1
c_func
(paren
id|cs
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bcs-&gt;tx_skb
op_logical_or
id|bcs-&gt;tx_skb-&gt;len
op_le
l_int|0
)paren
(brace
id|WARN_ON
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
op_star
id|more
op_assign
(paren
id|bcs-&gt;mode
op_eq
id|L1_MODE_TRANS
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bcs-&gt;tx_skb-&gt;len
OG
id|fifo_size
)paren
(brace
op_star
id|more
op_assign
l_int|1
suffix:semicolon
op_star
id|count
op_assign
id|fifo_size
suffix:semicolon
)brace
r_else
(brace
op_star
id|count
op_assign
id|bcs-&gt;tx_skb-&gt;len
suffix:semicolon
)brace
id|p
op_assign
id|bcs-&gt;tx_skb-&gt;data
suffix:semicolon
id|skb_pull
c_func
(paren
id|bcs-&gt;tx_skb
comma
op_star
id|count
)paren
suffix:semicolon
id|bcs-&gt;tx_cnt
op_sub_assign
op_star
id|count
suffix:semicolon
id|bcs-&gt;count
op_add_assign
op_star
id|count
suffix:semicolon
r_if
c_cond
(paren
id|cs-&gt;debug
op_amp
id|L1_DEB_HSCX_FIFO
)paren
(brace
r_char
op_star
id|t
op_assign
id|bcs-&gt;blog
suffix:semicolon
id|t
op_add_assign
id|sprintf
c_func
(paren
id|t
comma
l_string|&quot;%s %c cnt %d&quot;
comma
id|__FUNCTION__
comma
id|bcs-&gt;hw.hscx.hscx
ques
c_cond
l_char|&squot;B&squot;
suffix:colon
l_char|&squot;A&squot;
comma
op_star
id|count
)paren
suffix:semicolon
id|QuickHex
c_func
(paren
id|t
comma
id|p
comma
op_star
id|count
)paren
suffix:semicolon
id|debugl1
c_func
(paren
id|cs
comma
id|bcs-&gt;blog
)paren
suffix:semicolon
)brace
r_return
id|p
suffix:semicolon
)brace
r_static
r_inline
r_int
r_char
op_star
DECL|function|xmit_fill_fifo_d
id|xmit_fill_fifo_d
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
r_int
id|fifo_size
comma
r_int
op_star
id|count
comma
r_int
op_star
id|more
)paren
(brace
r_int
r_char
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
(paren
id|cs-&gt;debug
op_amp
id|L1_DEB_ISAC
)paren
op_logical_and
op_logical_neg
(paren
id|cs-&gt;debug
op_amp
id|L1_DEB_ISAC_FIFO
)paren
)paren
id|debugl1
c_func
(paren
id|cs
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cs-&gt;tx_skb
op_logical_or
id|cs-&gt;tx_skb-&gt;len
op_le
l_int|0
)paren
(brace
id|WARN_ON
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
op_star
id|more
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|cs-&gt;tx_skb-&gt;len
OG
id|fifo_size
)paren
(brace
op_star
id|more
op_assign
l_int|1
suffix:semicolon
op_star
id|count
op_assign
id|fifo_size
suffix:semicolon
)brace
r_else
(brace
op_star
id|count
op_assign
id|cs-&gt;tx_skb-&gt;len
suffix:semicolon
)brace
id|p
op_assign
id|cs-&gt;tx_skb-&gt;data
suffix:semicolon
id|skb_pull
c_func
(paren
id|cs-&gt;tx_skb
comma
op_star
id|count
)paren
suffix:semicolon
id|cs-&gt;tx_cnt
op_add_assign
op_star
id|count
suffix:semicolon
r_if
c_cond
(paren
id|cs-&gt;debug
op_amp
id|L1_DEB_ISAC_FIFO
)paren
(brace
r_char
op_star
id|t
op_assign
id|cs-&gt;dlog
suffix:semicolon
id|t
op_add_assign
id|sprintf
c_func
(paren
id|t
comma
l_string|&quot;%s cnt %d&quot;
comma
id|__FUNCTION__
comma
op_star
id|count
)paren
suffix:semicolon
id|QuickHex
c_func
(paren
id|t
comma
id|p
comma
op_star
id|count
)paren
suffix:semicolon
id|debugl1
c_func
(paren
id|cs
comma
id|cs-&gt;dlog
)paren
suffix:semicolon
)brace
r_return
id|p
suffix:semicolon
)brace
eof
