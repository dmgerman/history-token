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
mdefine_line|#define B_RCVBUFREADY 0
DECL|macro|B_XMTBUFREADY
mdefine_line|#define B_XMTBUFREADY 1
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
eof
