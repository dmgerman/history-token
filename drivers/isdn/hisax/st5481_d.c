multiline_comment|/*&n; * Driver for ST5481 USB ISDN modem&n; *&n; * Author       Frode Isaksen&n; * Copyright    2001 by Frode Isaksen      &lt;fisaksen@bewan.com&gt;&n; *              2001 by Kai Germaschewski  &lt;kai.germaschewski@gmx.de&gt;&n; * &n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/usb.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &quot;st5481.h&quot;
r_static
r_void
id|ph_connect
c_func
(paren
r_struct
id|st5481_adapter
op_star
id|adapter
)paren
suffix:semicolon
r_static
r_void
id|ph_disconnect
c_func
(paren
r_struct
id|st5481_adapter
op_star
id|adapter
)paren
suffix:semicolon
DECL|variable|l1fsm
r_static
r_struct
id|Fsm
id|l1fsm
suffix:semicolon
DECL|variable|strL1State
r_static
r_char
op_star
id|strL1State
(braket
)braket
op_assign
(brace
l_string|&quot;ST_L1_F3&quot;
comma
l_string|&quot;ST_L1_F4&quot;
comma
l_string|&quot;ST_L1_F6&quot;
comma
l_string|&quot;ST_L1_F7&quot;
comma
l_string|&quot;ST_L1_F8&quot;
comma
)brace
suffix:semicolon
DECL|variable|strL1Event
r_static
r_char
op_star
id|strL1Event
(braket
)braket
op_assign
(brace
l_string|&quot;EV_IND_DP&quot;
comma
l_string|&quot;EV_IND_1&quot;
comma
l_string|&quot;EV_IND_2&quot;
comma
l_string|&quot;EV_IND_3&quot;
comma
l_string|&quot;EV_IND_RSY&quot;
comma
l_string|&quot;EV_IND_5&quot;
comma
l_string|&quot;EV_IND_6&quot;
comma
l_string|&quot;EV_IND_7&quot;
comma
l_string|&quot;EV_IND_AP&quot;
comma
l_string|&quot;EV_IND_9&quot;
comma
l_string|&quot;EV_IND_10&quot;
comma
l_string|&quot;EV_IND_11&quot;
comma
l_string|&quot;EV_IND_AI8&quot;
comma
l_string|&quot;EV_IND_AI10&quot;
comma
l_string|&quot;EV_IND_AIL&quot;
comma
l_string|&quot;EV_IND_DI&quot;
comma
l_string|&quot;EV_PH_ACTIVATE_REQ&quot;
comma
l_string|&quot;EV_PH_DEACTIVATE_REQ&quot;
comma
l_string|&quot;EV_TIMER3&quot;
comma
)brace
suffix:semicolon
DECL|function|D_L1L2
r_static
r_inline
r_void
id|D_L1L2
c_func
(paren
r_struct
id|st5481_adapter
op_star
id|adapter
comma
r_int
id|pr
comma
r_void
op_star
id|arg
)paren
(brace
r_struct
id|hisax_if
op_star
id|ifc
op_assign
(paren
r_struct
id|hisax_if
op_star
)paren
op_amp
id|adapter-&gt;hisax_d_if
suffix:semicolon
id|ifc
op_member_access_from_pointer
id|l1l2
c_func
(paren
id|ifc
comma
id|pr
comma
id|arg
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|l1_go_f3
id|l1_go_f3
c_func
(paren
r_struct
id|FsmInst
op_star
id|fi
comma
r_int
id|event
comma
r_void
op_star
id|arg
)paren
(brace
r_struct
id|st5481_adapter
op_star
id|adapter
op_assign
id|fi-&gt;userdata
suffix:semicolon
r_if
c_cond
(paren
id|fi-&gt;state
op_eq
id|ST_L1_F7
)paren
id|ph_disconnect
c_func
(paren
id|adapter
)paren
suffix:semicolon
id|FsmChangeState
c_func
(paren
id|fi
comma
id|ST_L1_F3
)paren
suffix:semicolon
id|D_L1L2
c_func
(paren
id|adapter
comma
id|PH_DEACTIVATE
op_or
id|INDICATION
comma
l_int|NULL
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|l1_go_f6
id|l1_go_f6
c_func
(paren
r_struct
id|FsmInst
op_star
id|fi
comma
r_int
id|event
comma
r_void
op_star
id|arg
)paren
(brace
r_struct
id|st5481_adapter
op_star
id|adapter
op_assign
id|fi-&gt;userdata
suffix:semicolon
r_if
c_cond
(paren
id|fi-&gt;state
op_eq
id|ST_L1_F7
)paren
id|ph_disconnect
c_func
(paren
id|adapter
)paren
suffix:semicolon
id|FsmChangeState
c_func
(paren
id|fi
comma
id|ST_L1_F6
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|l1_go_f7
id|l1_go_f7
c_func
(paren
r_struct
id|FsmInst
op_star
id|fi
comma
r_int
id|event
comma
r_void
op_star
id|arg
)paren
(brace
r_struct
id|st5481_adapter
op_star
id|adapter
op_assign
id|fi-&gt;userdata
suffix:semicolon
id|FsmDelTimer
c_func
(paren
op_amp
id|adapter-&gt;timer
comma
l_int|0
)paren
suffix:semicolon
id|ph_connect
c_func
(paren
id|adapter
)paren
suffix:semicolon
id|FsmChangeState
c_func
(paren
id|fi
comma
id|ST_L1_F7
)paren
suffix:semicolon
id|D_L1L2
c_func
(paren
id|adapter
comma
id|PH_ACTIVATE
op_or
id|INDICATION
comma
l_int|NULL
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|l1_go_f8
id|l1_go_f8
c_func
(paren
r_struct
id|FsmInst
op_star
id|fi
comma
r_int
id|event
comma
r_void
op_star
id|arg
)paren
(brace
r_struct
id|st5481_adapter
op_star
id|adapter
op_assign
id|fi-&gt;userdata
suffix:semicolon
r_if
c_cond
(paren
id|fi-&gt;state
op_eq
id|ST_L1_F7
)paren
id|ph_disconnect
c_func
(paren
id|adapter
)paren
suffix:semicolon
id|FsmChangeState
c_func
(paren
id|fi
comma
id|ST_L1_F8
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|l1_timer3
id|l1_timer3
c_func
(paren
r_struct
id|FsmInst
op_star
id|fi
comma
r_int
id|event
comma
r_void
op_star
id|arg
)paren
(brace
r_struct
id|st5481_adapter
op_star
id|adapter
op_assign
id|fi-&gt;userdata
suffix:semicolon
id|st5481_ph_command
c_func
(paren
id|adapter
comma
id|ST5481_CMD_DR
)paren
suffix:semicolon
id|FsmChangeState
c_func
(paren
id|fi
comma
id|ST_L1_F3
)paren
suffix:semicolon
id|D_L1L2
c_func
(paren
id|adapter
comma
id|PH_DEACTIVATE
op_or
id|INDICATION
comma
l_int|NULL
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|l1_ignore
id|l1_ignore
c_func
(paren
r_struct
id|FsmInst
op_star
id|fi
comma
r_int
id|event
comma
r_void
op_star
id|arg
)paren
(brace
)brace
r_static
r_void
DECL|function|l1_activate
id|l1_activate
c_func
(paren
r_struct
id|FsmInst
op_star
id|fi
comma
r_int
id|event
comma
r_void
op_star
id|arg
)paren
(brace
r_struct
id|st5481_adapter
op_star
id|adapter
op_assign
id|fi-&gt;userdata
suffix:semicolon
id|st5481_ph_command
c_func
(paren
id|adapter
comma
id|ST5481_CMD_DR
)paren
suffix:semicolon
id|st5481_ph_command
c_func
(paren
id|adapter
comma
id|ST5481_CMD_PUP
)paren
suffix:semicolon
id|FsmRestartTimer
c_func
(paren
op_amp
id|adapter-&gt;timer
comma
id|TIMER3_VALUE
comma
id|EV_TIMER3
comma
l_int|NULL
comma
l_int|2
)paren
suffix:semicolon
id|st5481_ph_command
c_func
(paren
id|adapter
comma
id|ST5481_CMD_AR8
)paren
suffix:semicolon
id|FsmChangeState
c_func
(paren
id|fi
comma
id|ST_L1_F4
)paren
suffix:semicolon
)brace
DECL|variable|__initdata
r_static
r_struct
id|FsmNode
id|L1FnList
(braket
)braket
id|__initdata
op_assign
(brace
(brace
id|ST_L1_F3
comma
id|EV_IND_DP
comma
id|l1_ignore
)brace
comma
(brace
id|ST_L1_F3
comma
id|EV_IND_AP
comma
id|l1_go_f6
)brace
comma
(brace
id|ST_L1_F3
comma
id|EV_IND_AI8
comma
id|l1_go_f7
)brace
comma
(brace
id|ST_L1_F3
comma
id|EV_IND_AI10
comma
id|l1_go_f7
)brace
comma
(brace
id|ST_L1_F3
comma
id|EV_PH_ACTIVATE_REQ
comma
id|l1_activate
)brace
comma
(brace
id|ST_L1_F4
comma
id|EV_TIMER3
comma
id|l1_timer3
)brace
comma
(brace
id|ST_L1_F4
comma
id|EV_IND_DP
comma
id|l1_go_f3
)brace
comma
(brace
id|ST_L1_F4
comma
id|EV_IND_AP
comma
id|l1_go_f6
)brace
comma
(brace
id|ST_L1_F4
comma
id|EV_IND_AI8
comma
id|l1_go_f7
)brace
comma
(brace
id|ST_L1_F4
comma
id|EV_IND_AI10
comma
id|l1_go_f7
)brace
comma
(brace
id|ST_L1_F6
comma
id|EV_TIMER3
comma
id|l1_timer3
)brace
comma
(brace
id|ST_L1_F6
comma
id|EV_IND_DP
comma
id|l1_go_f3
)brace
comma
(brace
id|ST_L1_F6
comma
id|EV_IND_AP
comma
id|l1_ignore
)brace
comma
(brace
id|ST_L1_F6
comma
id|EV_IND_AI8
comma
id|l1_go_f7
)brace
comma
(brace
id|ST_L1_F6
comma
id|EV_IND_AI10
comma
id|l1_go_f7
)brace
comma
(brace
id|ST_L1_F7
comma
id|EV_IND_RSY
comma
id|l1_go_f8
)brace
comma
(brace
id|ST_L1_F7
comma
id|EV_IND_DP
comma
id|l1_go_f3
)brace
comma
(brace
id|ST_L1_F7
comma
id|EV_IND_AP
comma
id|l1_go_f6
)brace
comma
(brace
id|ST_L1_F7
comma
id|EV_IND_AI8
comma
id|l1_ignore
)brace
comma
(brace
id|ST_L1_F7
comma
id|EV_IND_AI10
comma
id|l1_ignore
)brace
comma
(brace
id|ST_L1_F7
comma
id|EV_IND_RSY
comma
id|l1_go_f8
)brace
comma
(brace
id|ST_L1_F8
comma
id|EV_TIMER3
comma
id|l1_timer3
)brace
comma
(brace
id|ST_L1_F8
comma
id|EV_IND_DP
comma
id|l1_go_f3
)brace
comma
(brace
id|ST_L1_F8
comma
id|EV_IND_AP
comma
id|l1_go_f6
)brace
comma
(brace
id|ST_L1_F8
comma
id|EV_IND_AI8
comma
id|l1_go_f8
)brace
comma
(brace
id|ST_L1_F8
comma
id|EV_IND_AI10
comma
id|l1_go_f8
)brace
comma
(brace
id|ST_L1_F8
comma
id|EV_IND_RSY
comma
id|l1_ignore
)brace
comma
)brace
suffix:semicolon
DECL|function|l1m_debug
r_static
r_void
id|l1m_debug
c_func
(paren
r_struct
id|FsmInst
op_star
id|fi
comma
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
(brace
id|va_list
id|args
suffix:semicolon
r_char
id|buf
(braket
l_int|256
)braket
suffix:semicolon
id|va_start
c_func
(paren
id|args
comma
id|fmt
)paren
suffix:semicolon
id|vsprintf
c_func
(paren
id|buf
comma
id|fmt
comma
id|args
)paren
suffix:semicolon
id|DBG
c_func
(paren
l_int|8
comma
l_string|&quot;%s&quot;
comma
id|buf
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|args
)paren
suffix:semicolon
)brace
multiline_comment|/* ======================================================================&n; * D-Channel out&n; */
multiline_comment|/*&n;  D OUT state machine:&n;  ====================&n;&n;  Transmit short frame (&lt; 16 bytes of encoded data):&n;&n;  L1 FRAME    D_OUT_STATE           USB                  D CHANNEL&n;  --------    -----------           ---                  ---------&n; &n;              FIXME&n;&n; -&gt; [xx..xx]  SHORT_INIT            -&gt; [7Exx..xxC1C27EFF]&n;              SHORT_WAIT_DEN        &lt;&gt; OUT_D_COUNTER=16 &n;                                                 &n;              END_OF_SHORT          &lt;- DEN_EVENT         -&gt; 7Exx&n;                                                          xxxx &n;                                                          xxxx&n;&t;&t;&t;&t;&t;&t;&t;  xxxx &n;&t;&t;&t;&t;&t;&t;&t;  xxxx&n;&t;&t;&t;&t;&t;&t;&t;  xxxx&n;&t;&t;&t;&t;&t;&t;&t;  C1C1 &n;&t;&t;&t;&t;&t;&t;&t;  7EFF &n;              WAIT_FOR_RESET_IDLE   &lt;- D_UNDERRUN        &lt;- (8ms)                        &n;              IDLE                  &lt;&gt; Reset pipe&n;&n;              &n;&n;  Transmit long frame (&gt;= 16 bytes of encoded data):&n;&n;  L1 FRAME    D_OUT_STATE           USB                  D CHANNEL&n;  --------    -----------           ---                  ---------&n;&n; -&gt; [xx...xx] IDLE&n;              WAIT_FOR_STOP         &lt;&gt; OUT_D_COUNTER=0&n;              WAIT_FOR_RESET        &lt;&gt; Reset pipe&n;&t;      STOP&n;&t;      INIT_LONG_FRAME       -&gt; [7Exx..xx]&n;              WAIT_DEN              &lt;&gt; OUT_D_COUNTER=16 &n;              OUT_NORMAL            &lt;- DEN_EVENT       -&gt; 7Exx&n;              END_OF_FRAME_BUSY     -&gt; [xxxx]             xxxx &n;              END_OF_FRAME_NOT_BUSY -&gt; [xxxx]             xxxx&n;&t;&t;&t;&t;    -&gt; [xxxx]&t;&t;  xxxx &n;&t;&t;&t;&t;    -&gt; [C1C2]&t;&t;  xxxx&n;&t;&t;&t;&t;    -&gt; [7EFF]&t;&t;  xxxx&n;&t;&t;&t;&t;&t;&t;&t;  xxxx &n;&t;&t;&t;&t;&t;&t;&t;  xxxx &n;                                                          ....&n;&t;&t;&t;&t;&t;&t;&t;  xxxx&n;&t;&t;&t;&t;&t;&t;&t;  C1C2&n;&t;&t;&t;&t;&t;&t;&t;  7EFF&n;&t;                 &t;    &lt;- D_UNDERRUN      &lt;- (&gt; 8ms)                        &n;              WAIT_FOR_STOP         &lt;&gt; OUT_D_COUNTER=0&n;              WAIT_FOR_RESET        &lt;&gt; Reset pipe&n;&t;      STOP&n;&n;*/
DECL|variable|dout_fsm
r_static
r_struct
id|Fsm
id|dout_fsm
suffix:semicolon
DECL|variable|strDoutState
r_static
r_char
op_star
id|strDoutState
(braket
)braket
op_assign
(brace
l_string|&quot;ST_DOUT_NONE&quot;
comma
l_string|&quot;ST_DOUT_SHORT_INIT&quot;
comma
l_string|&quot;ST_DOUT_SHORT_WAIT_DEN&quot;
comma
l_string|&quot;ST_DOUT_LONG_INIT&quot;
comma
l_string|&quot;ST_DOUT_LONG_WAIT_DEN&quot;
comma
l_string|&quot;ST_DOUT_NORMAL&quot;
comma
l_string|&quot;ST_DOUT_WAIT_FOR_UNDERRUN&quot;
comma
l_string|&quot;ST_DOUT_WAIT_FOR_NOT_BUSY&quot;
comma
l_string|&quot;ST_DOUT_WAIT_FOR_STOP&quot;
comma
l_string|&quot;ST_DOUT_WAIT_FOR_RESET&quot;
comma
)brace
suffix:semicolon
DECL|variable|strDoutEvent
r_static
r_char
op_star
id|strDoutEvent
(braket
)braket
op_assign
(brace
l_string|&quot;EV_DOUT_START_XMIT&quot;
comma
l_string|&quot;EV_DOUT_COMPLETE&quot;
comma
l_string|&quot;EV_DOUT_DEN&quot;
comma
l_string|&quot;EV_DOUT_RESETED&quot;
comma
l_string|&quot;EV_DOUT_STOPPED&quot;
comma
l_string|&quot;EV_DOUT_COLL&quot;
comma
l_string|&quot;EV_DOUT_UNDERRUN&quot;
comma
)brace
suffix:semicolon
DECL|function|dout_debug
r_static
r_void
id|dout_debug
c_func
(paren
r_struct
id|FsmInst
op_star
id|fi
comma
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
(brace
id|va_list
id|args
suffix:semicolon
r_char
id|buf
(braket
l_int|256
)braket
suffix:semicolon
id|va_start
c_func
(paren
id|args
comma
id|fmt
)paren
suffix:semicolon
id|vsprintf
c_func
(paren
id|buf
comma
id|fmt
comma
id|args
)paren
suffix:semicolon
id|DBG
c_func
(paren
l_int|0x2
comma
l_string|&quot;%s&quot;
comma
id|buf
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|args
)paren
suffix:semicolon
)brace
DECL|function|dout_stop_event
r_static
r_void
id|dout_stop_event
c_func
(paren
r_void
op_star
id|context
)paren
(brace
r_struct
id|st5481_adapter
op_star
id|adapter
op_assign
id|context
suffix:semicolon
id|FsmEvent
c_func
(paren
op_amp
id|adapter-&gt;d_out.fsm
comma
id|EV_DOUT_STOPPED
comma
l_int|NULL
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Start the transfer of a D channel frame.&n; */
DECL|function|usb_d_out
r_static
r_void
id|usb_d_out
c_func
(paren
r_struct
id|st5481_adapter
op_star
id|adapter
comma
r_int
id|buf_nr
)paren
(brace
r_struct
id|st5481_d_out
op_star
id|d_out
op_assign
op_amp
id|adapter-&gt;d_out
suffix:semicolon
r_struct
id|urb
op_star
id|urb
suffix:semicolon
r_int
r_int
id|num_packets
comma
id|packet_offset
suffix:semicolon
r_int
id|len
comma
id|buf_size
comma
id|bytes_sent
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_struct
id|usb_iso_packet_descriptor
op_star
id|desc
suffix:semicolon
r_if
c_cond
(paren
id|d_out-&gt;fsm.state
op_ne
id|ST_DOUT_NORMAL
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|test_and_set_bit
c_func
(paren
id|buf_nr
comma
op_amp
id|d_out-&gt;busy
)paren
)paren
(brace
id|DBG
c_func
(paren
l_int|2
comma
l_string|&quot;ep %d urb %d busy %#lx&quot;
comma
id|EP_D_OUT
comma
id|buf_nr
comma
id|d_out-&gt;busy
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|urb
op_assign
id|d_out-&gt;urb
(braket
id|buf_nr
)braket
suffix:semicolon
id|skb
op_assign
id|d_out-&gt;tx_skb
suffix:semicolon
id|buf_size
op_assign
id|NUM_ISO_PACKETS_D
op_star
id|SIZE_ISO_PACKETS_D_OUT
suffix:semicolon
r_if
c_cond
(paren
id|skb
)paren
(brace
id|len
op_assign
id|hdlc_encode
c_func
(paren
op_amp
id|d_out-&gt;hdlc_state
comma
id|skb-&gt;data
comma
id|skb-&gt;len
comma
op_amp
id|bytes_sent
comma
id|urb-&gt;transfer_buffer
comma
id|buf_size
)paren
suffix:semicolon
id|skb_pull
c_func
(paren
id|skb
comma
id|bytes_sent
)paren
suffix:semicolon
)brace
r_else
(brace
singleline_comment|// Send flags or idle
id|len
op_assign
id|hdlc_encode
c_func
(paren
op_amp
id|d_out-&gt;hdlc_state
comma
l_int|NULL
comma
l_int|0
comma
op_amp
id|bytes_sent
comma
id|urb-&gt;transfer_buffer
comma
id|buf_size
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|len
OL
id|buf_size
)paren
(brace
id|FsmChangeState
c_func
(paren
op_amp
id|d_out-&gt;fsm
comma
id|ST_DOUT_WAIT_FOR_UNDERRUN
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|skb
op_logical_and
op_logical_neg
id|skb-&gt;len
)paren
(brace
id|d_out-&gt;tx_skb
op_assign
l_int|NULL
suffix:semicolon
id|D_L1L2
c_func
(paren
id|adapter
comma
id|PH_DATA
op_or
id|CONFIRM
comma
l_int|NULL
)paren
suffix:semicolon
id|dev_kfree_skb_any
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
singleline_comment|// Prepare the URB
id|urb-&gt;transfer_buffer_length
op_assign
id|len
suffix:semicolon
id|num_packets
op_assign
l_int|0
suffix:semicolon
id|packet_offset
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|packet_offset
OL
id|len
)paren
(brace
id|desc
op_assign
op_amp
id|urb-&gt;iso_frame_desc
(braket
id|num_packets
)braket
suffix:semicolon
id|desc-&gt;offset
op_assign
id|packet_offset
suffix:semicolon
id|desc-&gt;length
op_assign
id|SIZE_ISO_PACKETS_D_OUT
suffix:semicolon
r_if
c_cond
(paren
id|len
op_minus
id|packet_offset
OL
id|desc-&gt;length
)paren
id|desc-&gt;length
op_assign
id|len
op_minus
id|packet_offset
suffix:semicolon
id|num_packets
op_increment
suffix:semicolon
id|packet_offset
op_add_assign
id|desc-&gt;length
suffix:semicolon
)brace
id|urb-&gt;number_of_packets
op_assign
id|num_packets
suffix:semicolon
singleline_comment|// Prepare the URB
id|urb-&gt;dev
op_assign
id|adapter-&gt;usb_dev
suffix:semicolon
singleline_comment|// Need to transmit the next buffer 2ms after the DEN_EVENT
id|urb-&gt;transfer_flags
op_assign
l_int|0
suffix:semicolon
id|urb-&gt;start_frame
op_assign
id|usb_get_current_frame_number
c_func
(paren
id|adapter-&gt;usb_dev
)paren
op_plus
l_int|2
suffix:semicolon
id|DBG_ISO_PACKET
c_func
(paren
l_int|0x20
comma
id|urb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|usb_submit_urb
c_func
(paren
id|urb
)paren
OL
l_int|0
)paren
(brace
singleline_comment|// There is another URB queued up
id|urb-&gt;transfer_flags
op_assign
id|USB_ISO_ASAP
suffix:semicolon
id|SUBMIT_URB
c_func
(paren
id|urb
)paren
suffix:semicolon
)brace
)brace
DECL|function|fifo_reseted
r_static
r_void
id|fifo_reseted
c_func
(paren
r_void
op_star
id|context
)paren
(brace
r_struct
id|st5481_adapter
op_star
id|adapter
op_assign
id|context
suffix:semicolon
id|FsmEvent
c_func
(paren
op_amp
id|adapter-&gt;d_out.fsm
comma
id|EV_DOUT_RESETED
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|function|usb_d_out_complete
r_static
r_void
id|usb_d_out_complete
c_func
(paren
r_struct
id|urb
op_star
id|urb
)paren
(brace
r_struct
id|st5481_adapter
op_star
id|adapter
op_assign
id|urb-&gt;context
suffix:semicolon
r_struct
id|st5481_d_out
op_star
id|d_out
op_assign
op_amp
id|adapter-&gt;d_out
suffix:semicolon
r_int
id|buf_nr
suffix:semicolon
id|DBG
c_func
(paren
l_int|2
comma
l_string|&quot;&quot;
)paren
suffix:semicolon
id|buf_nr
op_assign
id|get_buf_nr
c_func
(paren
id|d_out-&gt;urb
comma
id|urb
)paren
suffix:semicolon
id|test_and_clear_bit
c_func
(paren
id|buf_nr
comma
op_amp
id|d_out-&gt;busy
)paren
suffix:semicolon
r_if
c_cond
(paren
id|urb-&gt;status
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|urb-&gt;status
op_ne
op_minus
id|ENOENT
)paren
(brace
id|WARN
c_func
(paren
l_string|&quot;urb status %d&quot;
comma
id|urb-&gt;status
)paren
suffix:semicolon
r_if
c_cond
(paren
id|d_out-&gt;busy
op_eq
l_int|0
)paren
(brace
id|st5481_usb_pipe_reset
c_func
(paren
id|adapter
comma
id|EP_D_OUT
op_or
id|USB_DIR_OUT
comma
id|fifo_reseted
comma
id|adapter
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
r_else
(brace
id|DBG
c_func
(paren
l_int|1
comma
l_string|&quot;urb killed&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
singleline_comment|// Give up
)brace
)brace
id|FsmEvent
c_func
(paren
op_amp
id|adapter-&gt;d_out.fsm
comma
id|EV_DOUT_COMPLETE
comma
(paren
r_void
op_star
)paren
id|buf_nr
)paren
suffix:semicolon
)brace
multiline_comment|/* ====================================================================== */
DECL|function|dout_start_xmit
r_static
r_void
id|dout_start_xmit
c_func
(paren
r_struct
id|FsmInst
op_star
id|fsm
comma
r_int
id|event
comma
r_void
op_star
id|arg
)paren
(brace
singleline_comment|// FIXME unify?
r_struct
id|st5481_adapter
op_star
id|adapter
op_assign
id|fsm-&gt;userdata
suffix:semicolon
r_struct
id|st5481_d_out
op_star
id|d_out
op_assign
op_amp
id|adapter-&gt;d_out
suffix:semicolon
r_struct
id|urb
op_star
id|urb
suffix:semicolon
r_int
id|len
comma
id|bytes_sent
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_int
id|buf_nr
op_assign
l_int|0
suffix:semicolon
id|skb
op_assign
id|d_out-&gt;tx_skb
suffix:semicolon
id|DBG
c_func
(paren
l_int|2
comma
l_string|&quot;len=%d&quot;
comma
id|skb-&gt;len
)paren
suffix:semicolon
id|hdlc_out_init
c_func
(paren
op_amp
id|d_out-&gt;hdlc_state
comma
l_int|1
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|test_and_set_bit
c_func
(paren
id|buf_nr
comma
op_amp
id|d_out-&gt;busy
)paren
)paren
(brace
id|WARN
c_func
(paren
l_string|&quot;ep %d urb %d busy %#lx&quot;
comma
id|EP_D_OUT
comma
id|buf_nr
comma
id|d_out-&gt;busy
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|urb
op_assign
id|d_out-&gt;urb
(braket
id|buf_nr
)braket
suffix:semicolon
id|DBG_SKB
c_func
(paren
l_int|0x10
comma
id|skb
)paren
suffix:semicolon
id|len
op_assign
id|hdlc_encode
c_func
(paren
op_amp
id|d_out-&gt;hdlc_state
comma
id|skb-&gt;data
comma
id|skb-&gt;len
comma
op_amp
id|bytes_sent
comma
id|urb-&gt;transfer_buffer
comma
l_int|16
)paren
suffix:semicolon
id|skb_pull
c_func
(paren
id|skb
comma
id|bytes_sent
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
l_int|16
)paren
(brace
id|FsmChangeState
c_func
(paren
op_amp
id|d_out-&gt;fsm
comma
id|ST_DOUT_SHORT_INIT
)paren
suffix:semicolon
)brace
r_else
id|FsmChangeState
c_func
(paren
op_amp
id|d_out-&gt;fsm
comma
id|ST_DOUT_LONG_INIT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb-&gt;len
op_eq
l_int|0
)paren
(brace
id|d_out-&gt;tx_skb
op_assign
l_int|NULL
suffix:semicolon
id|D_L1L2
c_func
(paren
id|adapter
comma
id|PH_DATA
op_or
id|CONFIRM
comma
l_int|NULL
)paren
suffix:semicolon
id|dev_kfree_skb_any
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
singleline_comment|// Prepare the URB
id|urb-&gt;transfer_buffer_length
op_assign
id|len
suffix:semicolon
id|urb-&gt;iso_frame_desc
(braket
l_int|0
)braket
dot
id|offset
op_assign
l_int|0
suffix:semicolon
id|urb-&gt;iso_frame_desc
(braket
l_int|0
)braket
dot
id|length
op_assign
id|len
suffix:semicolon
id|urb-&gt;number_of_packets
op_assign
l_int|1
suffix:semicolon
singleline_comment|// Prepare the URB
id|urb-&gt;dev
op_assign
id|adapter-&gt;usb_dev
suffix:semicolon
id|urb-&gt;transfer_flags
op_assign
id|USB_ISO_ASAP
suffix:semicolon
id|DBG_ISO_PACKET
c_func
(paren
l_int|0x20
comma
id|urb
)paren
suffix:semicolon
id|SUBMIT_URB
c_func
(paren
id|urb
)paren
suffix:semicolon
)brace
DECL|function|dout_short_fifo
r_static
r_void
id|dout_short_fifo
c_func
(paren
r_struct
id|FsmInst
op_star
id|fsm
comma
r_int
id|event
comma
r_void
op_star
id|arg
)paren
(brace
r_struct
id|st5481_adapter
op_star
id|adapter
op_assign
id|fsm-&gt;userdata
suffix:semicolon
r_struct
id|st5481_d_out
op_star
id|d_out
op_assign
op_amp
id|adapter-&gt;d_out
suffix:semicolon
id|FsmChangeState
c_func
(paren
op_amp
id|d_out-&gt;fsm
comma
id|ST_DOUT_SHORT_WAIT_DEN
)paren
suffix:semicolon
id|st5481_usb_device_ctrl_msg
c_func
(paren
id|adapter
comma
id|OUT_D_COUNTER
comma
l_int|16
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|function|dout_end_short_frame
r_static
r_void
id|dout_end_short_frame
c_func
(paren
r_struct
id|FsmInst
op_star
id|fsm
comma
r_int
id|event
comma
r_void
op_star
id|arg
)paren
(brace
r_struct
id|st5481_adapter
op_star
id|adapter
op_assign
id|fsm-&gt;userdata
suffix:semicolon
r_struct
id|st5481_d_out
op_star
id|d_out
op_assign
op_amp
id|adapter-&gt;d_out
suffix:semicolon
id|FsmChangeState
c_func
(paren
op_amp
id|d_out-&gt;fsm
comma
id|ST_DOUT_WAIT_FOR_UNDERRUN
)paren
suffix:semicolon
)brace
DECL|function|dout_long_enable_fifo
r_static
r_void
id|dout_long_enable_fifo
c_func
(paren
r_struct
id|FsmInst
op_star
id|fsm
comma
r_int
id|event
comma
r_void
op_star
id|arg
)paren
(brace
r_struct
id|st5481_adapter
op_star
id|adapter
op_assign
id|fsm-&gt;userdata
suffix:semicolon
r_struct
id|st5481_d_out
op_star
id|d_out
op_assign
op_amp
id|adapter-&gt;d_out
suffix:semicolon
id|st5481_usb_device_ctrl_msg
c_func
(paren
id|adapter
comma
id|OUT_D_COUNTER
comma
l_int|16
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
id|FsmChangeState
c_func
(paren
op_amp
id|d_out-&gt;fsm
comma
id|ST_DOUT_LONG_WAIT_DEN
)paren
suffix:semicolon
)brace
DECL|function|dout_long_den
r_static
r_void
id|dout_long_den
c_func
(paren
r_struct
id|FsmInst
op_star
id|fsm
comma
r_int
id|event
comma
r_void
op_star
id|arg
)paren
(brace
r_struct
id|st5481_adapter
op_star
id|adapter
op_assign
id|fsm-&gt;userdata
suffix:semicolon
r_struct
id|st5481_d_out
op_star
id|d_out
op_assign
op_amp
id|adapter-&gt;d_out
suffix:semicolon
id|FsmChangeState
c_func
(paren
op_amp
id|d_out-&gt;fsm
comma
id|ST_DOUT_NORMAL
)paren
suffix:semicolon
id|usb_d_out
c_func
(paren
id|adapter
comma
l_int|0
)paren
suffix:semicolon
id|usb_d_out
c_func
(paren
id|adapter
comma
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|dout_reset
r_static
r_void
id|dout_reset
c_func
(paren
r_struct
id|FsmInst
op_star
id|fsm
comma
r_int
id|event
comma
r_void
op_star
id|arg
)paren
(brace
r_struct
id|st5481_adapter
op_star
id|adapter
op_assign
id|fsm-&gt;userdata
suffix:semicolon
r_struct
id|st5481_d_out
op_star
id|d_out
op_assign
op_amp
id|adapter-&gt;d_out
suffix:semicolon
id|FsmChangeState
c_func
(paren
op_amp
id|d_out-&gt;fsm
comma
id|ST_DOUT_WAIT_FOR_RESET
)paren
suffix:semicolon
id|st5481_usb_pipe_reset
c_func
(paren
id|adapter
comma
id|EP_D_OUT
op_or
id|USB_DIR_OUT
comma
id|fifo_reseted
comma
id|adapter
)paren
suffix:semicolon
)brace
DECL|function|dout_stop
r_static
r_void
id|dout_stop
c_func
(paren
r_struct
id|FsmInst
op_star
id|fsm
comma
r_int
id|event
comma
r_void
op_star
id|arg
)paren
(brace
r_struct
id|st5481_adapter
op_star
id|adapter
op_assign
id|fsm-&gt;userdata
suffix:semicolon
r_struct
id|st5481_d_out
op_star
id|d_out
op_assign
op_amp
id|adapter-&gt;d_out
suffix:semicolon
id|FsmChangeState
c_func
(paren
op_amp
id|d_out-&gt;fsm
comma
id|ST_DOUT_WAIT_FOR_STOP
)paren
suffix:semicolon
id|st5481_usb_device_ctrl_msg
c_func
(paren
id|adapter
comma
id|OUT_D_COUNTER
comma
l_int|0
comma
id|dout_stop_event
comma
id|adapter
)paren
suffix:semicolon
)brace
DECL|function|dout_underrun
r_static
r_void
id|dout_underrun
c_func
(paren
r_struct
id|FsmInst
op_star
id|fsm
comma
r_int
id|event
comma
r_void
op_star
id|arg
)paren
(brace
r_struct
id|st5481_adapter
op_star
id|adapter
op_assign
id|fsm-&gt;userdata
suffix:semicolon
r_struct
id|st5481_d_out
op_star
id|d_out
op_assign
op_amp
id|adapter-&gt;d_out
suffix:semicolon
r_if
c_cond
(paren
id|test_bit
c_func
(paren
l_int|0
comma
op_amp
id|d_out-&gt;busy
)paren
op_logical_or
id|test_bit
c_func
(paren
l_int|1
comma
op_amp
id|d_out-&gt;busy
)paren
)paren
(brace
id|FsmChangeState
c_func
(paren
op_amp
id|d_out-&gt;fsm
comma
id|ST_DOUT_WAIT_FOR_NOT_BUSY
)paren
suffix:semicolon
)brace
r_else
(brace
id|dout_stop
c_func
(paren
id|fsm
comma
id|event
comma
id|arg
)paren
suffix:semicolon
)brace
)brace
DECL|function|dout_check_busy
r_static
r_void
id|dout_check_busy
c_func
(paren
r_struct
id|FsmInst
op_star
id|fsm
comma
r_int
id|event
comma
r_void
op_star
id|arg
)paren
(brace
r_struct
id|st5481_adapter
op_star
id|adapter
op_assign
id|fsm-&gt;userdata
suffix:semicolon
r_struct
id|st5481_d_out
op_star
id|d_out
op_assign
op_amp
id|adapter-&gt;d_out
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|test_bit
c_func
(paren
l_int|0
comma
op_amp
id|d_out-&gt;busy
)paren
op_logical_and
op_logical_neg
id|test_bit
c_func
(paren
l_int|1
comma
op_amp
id|d_out-&gt;busy
)paren
)paren
id|dout_stop
c_func
(paren
id|fsm
comma
id|event
comma
id|arg
)paren
suffix:semicolon
)brace
DECL|function|dout_reseted
r_static
r_void
id|dout_reseted
c_func
(paren
r_struct
id|FsmInst
op_star
id|fsm
comma
r_int
id|event
comma
r_void
op_star
id|arg
)paren
(brace
r_struct
id|st5481_adapter
op_star
id|adapter
op_assign
id|fsm-&gt;userdata
suffix:semicolon
r_struct
id|st5481_d_out
op_star
id|d_out
op_assign
op_amp
id|adapter-&gt;d_out
suffix:semicolon
id|FsmChangeState
c_func
(paren
op_amp
id|d_out-&gt;fsm
comma
id|ST_DOUT_NONE
)paren
suffix:semicolon
singleline_comment|// FIXME locking
r_if
c_cond
(paren
id|d_out-&gt;tx_skb
)paren
id|FsmEvent
c_func
(paren
op_amp
id|d_out-&gt;fsm
comma
id|EV_DOUT_START_XMIT
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|function|dout_complete
r_static
r_void
id|dout_complete
c_func
(paren
r_struct
id|FsmInst
op_star
id|fsm
comma
r_int
id|event
comma
r_void
op_star
id|arg
)paren
(brace
r_struct
id|st5481_adapter
op_star
id|adapter
op_assign
id|fsm-&gt;userdata
suffix:semicolon
r_int
id|buf_nr
op_assign
(paren
r_int
)paren
id|arg
suffix:semicolon
id|usb_d_out
c_func
(paren
id|adapter
comma
id|buf_nr
)paren
suffix:semicolon
)brace
DECL|function|dout_ignore
r_static
r_void
id|dout_ignore
c_func
(paren
r_struct
id|FsmInst
op_star
id|fsm
comma
r_int
id|event
comma
r_void
op_star
id|arg
)paren
(brace
)brace
DECL|variable|__initdata
r_static
r_struct
id|FsmNode
id|DoutFnList
(braket
)braket
id|__initdata
op_assign
(brace
(brace
id|ST_DOUT_NONE
comma
id|EV_DOUT_START_XMIT
comma
id|dout_start_xmit
)brace
comma
(brace
id|ST_DOUT_SHORT_INIT
comma
id|EV_DOUT_COMPLETE
comma
id|dout_short_fifo
)brace
comma
(brace
id|ST_DOUT_SHORT_WAIT_DEN
comma
id|EV_DOUT_DEN
comma
id|dout_end_short_frame
)brace
comma
(brace
id|ST_DOUT_SHORT_WAIT_DEN
comma
id|EV_DOUT_UNDERRUN
comma
id|dout_underrun
)brace
comma
(brace
id|ST_DOUT_LONG_INIT
comma
id|EV_DOUT_COMPLETE
comma
id|dout_long_enable_fifo
)brace
comma
(brace
id|ST_DOUT_LONG_WAIT_DEN
comma
id|EV_DOUT_DEN
comma
id|dout_long_den
)brace
comma
(brace
id|ST_DOUT_LONG_WAIT_DEN
comma
id|EV_DOUT_UNDERRUN
comma
id|dout_underrun
)brace
comma
(brace
id|ST_DOUT_NORMAL
comma
id|EV_DOUT_UNDERRUN
comma
id|dout_underrun
)brace
comma
(brace
id|ST_DOUT_NORMAL
comma
id|EV_DOUT_COMPLETE
comma
id|dout_complete
)brace
comma
(brace
id|ST_DOUT_WAIT_FOR_UNDERRUN
comma
id|EV_DOUT_UNDERRUN
comma
id|dout_underrun
)brace
comma
(brace
id|ST_DOUT_WAIT_FOR_UNDERRUN
comma
id|EV_DOUT_COMPLETE
comma
id|dout_ignore
)brace
comma
(brace
id|ST_DOUT_WAIT_FOR_NOT_BUSY
comma
id|EV_DOUT_COMPLETE
comma
id|dout_check_busy
)brace
comma
(brace
id|ST_DOUT_WAIT_FOR_STOP
comma
id|EV_DOUT_STOPPED
comma
id|dout_reset
)brace
comma
(brace
id|ST_DOUT_WAIT_FOR_RESET
comma
id|EV_DOUT_RESETED
comma
id|dout_reseted
)brace
comma
)brace
suffix:semicolon
DECL|function|st5481_d_l2l1
r_void
id|st5481_d_l2l1
c_func
(paren
r_struct
id|hisax_if
op_star
id|hisax_d_if
comma
r_int
id|pr
comma
r_void
op_star
id|arg
)paren
(brace
r_struct
id|st5481_adapter
op_star
id|adapter
op_assign
id|hisax_d_if-&gt;priv
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
op_assign
id|arg
suffix:semicolon
r_switch
c_cond
(paren
id|pr
)paren
(brace
r_case
id|PH_ACTIVATE
op_or
id|REQUEST
suffix:colon
id|FsmEvent
c_func
(paren
op_amp
id|adapter-&gt;l1m
comma
id|EV_PH_ACTIVATE_REQ
comma
l_int|NULL
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PH_DEACTIVATE
op_or
id|REQUEST
suffix:colon
id|FsmEvent
c_func
(paren
op_amp
id|adapter-&gt;l1m
comma
id|EV_PH_DEACTIVATE_REQ
comma
l_int|NULL
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PH_DATA
op_or
id|REQUEST
suffix:colon
id|DBG
c_func
(paren
l_int|2
comma
l_string|&quot;PH_DATA REQUEST len %d&quot;
comma
id|skb-&gt;len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|adapter-&gt;d_out.tx_skb
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|adapter-&gt;d_out.tx_skb
op_assign
id|skb
suffix:semicolon
id|FsmEvent
c_func
(paren
op_amp
id|adapter-&gt;d_out.fsm
comma
id|EV_DOUT_START_XMIT
comma
l_int|NULL
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|WARN
c_func
(paren
l_string|&quot;pr %#x&bslash;n&quot;
comma
id|pr
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/* ======================================================================&n; */
multiline_comment|/*&n; * Start receiving on the D channel since entered state F7.&n; */
DECL|function|ph_connect
r_static
r_void
id|ph_connect
c_func
(paren
r_struct
id|st5481_adapter
op_star
id|adapter
)paren
(brace
r_struct
id|st5481_d_out
op_star
id|d_out
op_assign
op_amp
id|adapter-&gt;d_out
suffix:semicolon
r_struct
id|st5481_in
op_star
id|d_in
op_assign
op_amp
id|adapter-&gt;d_in
suffix:semicolon
id|DBG
c_func
(paren
l_int|8
comma
l_string|&quot;&quot;
)paren
suffix:semicolon
id|FsmChangeState
c_func
(paren
op_amp
id|d_out-&gt;fsm
comma
id|ST_DOUT_NONE
)paren
suffix:semicolon
singleline_comment|//&t;st5481_usb_device_ctrl_msg(adapter, FFMSK_D, OUT_UNDERRUN, NULL, NULL);
id|st5481_usb_device_ctrl_msg
c_func
(paren
id|adapter
comma
id|FFMSK_D
comma
l_int|0xfc
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
id|st5481_in_mode
c_func
(paren
id|d_in
comma
id|L1_MODE_HDLC
)paren
suffix:semicolon
macro_line|#if LOOPBACK
singleline_comment|// Turn loopback on (data sent on B and D looped back)
id|st5481_usb_device_ctrl_msg
c_func
(paren
id|cs
comma
id|LBB
comma
l_int|0x04
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
macro_line|#endif
id|st5481_usb_pipe_reset
c_func
(paren
id|adapter
comma
id|EP_D_OUT
op_or
id|USB_DIR_OUT
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
singleline_comment|// Turn on the green LED to tell that we are in state F7
id|adapter-&gt;leds
op_or_assign
id|GREEN_LED
suffix:semicolon
id|st5481_usb_device_ctrl_msg
c_func
(paren
id|adapter
comma
id|GPIO_OUT
comma
id|adapter-&gt;leds
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Stop receiving on the D channel since not in state F7.&n; */
DECL|function|ph_disconnect
r_static
r_void
id|ph_disconnect
c_func
(paren
r_struct
id|st5481_adapter
op_star
id|adapter
)paren
(brace
id|DBG
c_func
(paren
l_int|8
comma
l_string|&quot;&quot;
)paren
suffix:semicolon
id|st5481_in_mode
c_func
(paren
op_amp
id|adapter-&gt;d_in
comma
id|L1_MODE_NULL
)paren
suffix:semicolon
singleline_comment|// Turn off the green LED to tell that we left state F7
id|adapter-&gt;leds
op_and_assign
op_complement
id|GREEN_LED
suffix:semicolon
id|st5481_usb_device_ctrl_msg
c_func
(paren
id|adapter
comma
id|GPIO_OUT
comma
id|adapter-&gt;leds
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|function|st5481_setup_d_out
r_static
r_int
id|__devinit
id|st5481_setup_d_out
c_func
(paren
r_struct
id|st5481_adapter
op_star
id|adapter
)paren
(brace
r_struct
id|usb_device
op_star
id|dev
op_assign
id|adapter-&gt;usb_dev
suffix:semicolon
r_struct
id|usb_interface_descriptor
op_star
id|altsetting
suffix:semicolon
r_struct
id|usb_endpoint_descriptor
op_star
id|endpoint
suffix:semicolon
r_struct
id|st5481_d_out
op_star
id|d_out
op_assign
op_amp
id|adapter-&gt;d_out
suffix:semicolon
id|DBG
c_func
(paren
l_int|2
comma
l_string|&quot;&quot;
)paren
suffix:semicolon
id|altsetting
op_assign
op_amp
(paren
id|dev-&gt;config-&gt;interface
(braket
l_int|0
)braket
dot
id|altsetting
(braket
l_int|3
)braket
)paren
suffix:semicolon
singleline_comment|// Allocate URBs and buffers for the D channel out
id|endpoint
op_assign
op_amp
id|altsetting-&gt;endpoint
(braket
id|EP_D_OUT
op_minus
l_int|1
)braket
suffix:semicolon
id|DBG
c_func
(paren
l_int|2
comma
l_string|&quot;endpoint address=%02x,packet size=%d&quot;
comma
id|endpoint-&gt;bEndpointAddress
comma
id|endpoint-&gt;wMaxPacketSize
)paren
suffix:semicolon
r_return
id|st5481_setup_isocpipes
c_func
(paren
id|d_out-&gt;urb
comma
id|dev
comma
id|usb_sndisocpipe
c_func
(paren
id|dev
comma
id|endpoint-&gt;bEndpointAddress
)paren
comma
id|NUM_ISO_PACKETS_D
comma
id|SIZE_ISO_PACKETS_D_OUT
comma
id|NUM_ISO_PACKETS_D
op_star
id|SIZE_ISO_PACKETS_D_OUT
comma
id|usb_d_out_complete
comma
id|adapter
)paren
suffix:semicolon
)brace
DECL|function|st5481_release_d_out
r_static
r_void
id|st5481_release_d_out
c_func
(paren
r_struct
id|st5481_adapter
op_star
id|adapter
)paren
(brace
r_struct
id|st5481_d_out
op_star
id|d_out
op_assign
op_amp
id|adapter-&gt;d_out
suffix:semicolon
id|DBG
c_func
(paren
l_int|2
comma
l_string|&quot;&quot;
)paren
suffix:semicolon
id|st5481_release_isocpipes
c_func
(paren
id|d_out-&gt;urb
)paren
suffix:semicolon
)brace
DECL|function|st5481_setup_d
r_int
id|__devinit
id|st5481_setup_d
c_func
(paren
r_struct
id|st5481_adapter
op_star
id|adapter
)paren
(brace
r_int
id|retval
suffix:semicolon
id|DBG
c_func
(paren
l_int|2
comma
l_string|&quot;&quot;
)paren
suffix:semicolon
id|retval
op_assign
id|st5481_setup_d_out
c_func
(paren
id|adapter
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_goto
id|err
suffix:semicolon
id|adapter-&gt;d_in.bufsize
op_assign
id|MAX_DFRAME_LEN_L1
suffix:semicolon
id|adapter-&gt;d_in.num_packets
op_assign
id|NUM_ISO_PACKETS_D
suffix:semicolon
id|adapter-&gt;d_in.packet_size
op_assign
id|SIZE_ISO_PACKETS_D_IN
suffix:semicolon
id|adapter-&gt;d_in.ep
op_assign
id|EP_D_IN
op_or
id|USB_DIR_IN
suffix:semicolon
id|adapter-&gt;d_in.counter
op_assign
id|IN_D_COUNTER
suffix:semicolon
id|adapter-&gt;d_in.adapter
op_assign
id|adapter
suffix:semicolon
id|adapter-&gt;d_in.hisax_if
op_assign
op_amp
id|adapter-&gt;hisax_d_if.ifc
suffix:semicolon
id|retval
op_assign
id|st5481_setup_in
c_func
(paren
op_amp
id|adapter-&gt;d_in
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_goto
id|err_d_out
suffix:semicolon
id|adapter-&gt;l1m.fsm
op_assign
op_amp
id|l1fsm
suffix:semicolon
id|adapter-&gt;l1m.state
op_assign
id|ST_L1_F3
suffix:semicolon
id|adapter-&gt;l1m.debug
op_assign
l_int|1
suffix:semicolon
id|adapter-&gt;l1m.userdata
op_assign
id|adapter
suffix:semicolon
id|adapter-&gt;l1m.printdebug
op_assign
id|l1m_debug
suffix:semicolon
id|FsmInitTimer
c_func
(paren
op_amp
id|adapter-&gt;l1m
comma
op_amp
id|adapter-&gt;timer
)paren
suffix:semicolon
id|adapter-&gt;d_out.fsm.fsm
op_assign
op_amp
id|dout_fsm
suffix:semicolon
id|adapter-&gt;d_out.fsm.state
op_assign
id|ST_DOUT_NONE
suffix:semicolon
id|adapter-&gt;d_out.fsm.debug
op_assign
l_int|1
suffix:semicolon
id|adapter-&gt;d_out.fsm.userdata
op_assign
id|adapter
suffix:semicolon
id|adapter-&gt;d_out.fsm.printdebug
op_assign
id|dout_debug
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|err_d_out
suffix:colon
id|st5481_release_d_out
c_func
(paren
id|adapter
)paren
suffix:semicolon
id|err
suffix:colon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|st5481_release_d
r_void
id|st5481_release_d
c_func
(paren
r_struct
id|st5481_adapter
op_star
id|adapter
)paren
(brace
id|DBG
c_func
(paren
l_int|2
comma
l_string|&quot;&quot;
)paren
suffix:semicolon
id|st5481_release_in
c_func
(paren
op_amp
id|adapter-&gt;d_in
)paren
suffix:semicolon
id|st5481_release_d_out
c_func
(paren
id|adapter
)paren
suffix:semicolon
)brace
multiline_comment|/* ======================================================================&n; * init / exit&n; */
DECL|function|st5481_d_init
r_int
id|__init
id|st5481_d_init
c_func
(paren
r_void
)paren
(brace
r_int
id|retval
suffix:semicolon
id|l1fsm.state_count
op_assign
id|L1_STATE_COUNT
suffix:semicolon
id|l1fsm.event_count
op_assign
id|L1_EVENT_COUNT
suffix:semicolon
id|l1fsm.strEvent
op_assign
id|strL1Event
suffix:semicolon
id|l1fsm.strState
op_assign
id|strL1State
suffix:semicolon
id|retval
op_assign
id|FsmNew
c_func
(paren
op_amp
id|l1fsm
comma
id|L1FnList
comma
id|ARRAY_SIZE
c_func
(paren
id|L1FnList
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_goto
id|err
suffix:semicolon
id|dout_fsm.state_count
op_assign
id|DOUT_STATE_COUNT
suffix:semicolon
id|dout_fsm.event_count
op_assign
id|DOUT_EVENT_COUNT
suffix:semicolon
id|dout_fsm.strEvent
op_assign
id|strDoutEvent
suffix:semicolon
id|dout_fsm.strState
op_assign
id|strDoutState
suffix:semicolon
id|retval
op_assign
id|FsmNew
c_func
(paren
op_amp
id|dout_fsm
comma
id|DoutFnList
comma
id|ARRAY_SIZE
c_func
(paren
id|DoutFnList
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_goto
id|err_l1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|err_l1
suffix:colon
id|FsmFree
c_func
(paren
op_amp
id|l1fsm
)paren
suffix:semicolon
id|err
suffix:colon
r_return
id|retval
suffix:semicolon
)brace
singleline_comment|// can&squot;t be __exit
DECL|function|st5481_d_exit
r_void
id|st5481_d_exit
c_func
(paren
r_void
)paren
(brace
id|FsmFree
c_func
(paren
op_amp
id|l1fsm
)paren
suffix:semicolon
id|FsmFree
c_func
(paren
op_amp
id|dout_fsm
)paren
suffix:semicolon
)brace
eof
