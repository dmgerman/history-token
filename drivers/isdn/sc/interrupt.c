multiline_comment|/* $Id: interrupt.c,v 1.4.8.3 2001/09/23 22:24:59 kai Exp $&n; *&n; * Copyright (C) 1996  SpellCaster Telecommunications Inc.&n; *&n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; * For more information, please contact gpl-info@spellcast.com or write:&n; *&n; *     SpellCaster Telecommunications Inc.&n; *     5621 Finch Avenue East, Unit #3&n; *     Scarborough, Ontario  Canada&n; *     M1B 2T9&n; *     +1 (416) 297-8565&n; *     +1 (416) 297-6433 Facsimile&n; */
macro_line|#include &quot;includes.h&quot;
macro_line|#include &quot;hardware.h&quot;
macro_line|#include &quot;message.h&quot;
macro_line|#include &quot;card.h&quot;
macro_line|#include &lt;linux/interrupt.h&gt;
r_extern
r_int
id|indicate_status
c_func
(paren
r_int
comma
r_int
comma
id|ulong
comma
r_char
op_star
)paren
suffix:semicolon
r_extern
r_void
id|check_phystat
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
id|receivemessage
c_func
(paren
r_int
comma
id|RspMessage
op_star
)paren
suffix:semicolon
r_extern
r_int
id|sendmessage
c_func
(paren
r_int
comma
r_int
r_int
comma
r_int
r_int
comma
r_int
r_int
comma
r_int
r_int
comma
r_int
r_int
comma
r_int
r_int
comma
r_int
r_int
op_star
)paren
suffix:semicolon
r_extern
r_void
id|rcvpkt
c_func
(paren
r_int
comma
id|RspMessage
op_star
)paren
suffix:semicolon
r_extern
r_int
id|cinst
suffix:semicolon
r_extern
id|board
op_star
id|sc_adapter
(braket
)braket
suffix:semicolon
DECL|function|get_card_from_irq
r_int
id|get_card_from_irq
c_func
(paren
r_int
id|irq
)paren
(brace
r_int
id|i
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
id|cinst
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|sc_adapter
(braket
id|i
)braket
op_member_access_from_pointer
id|interrupt
op_eq
id|irq
)paren
(brace
r_return
id|i
suffix:semicolon
)brace
)brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * &n; */
DECL|function|interrupt_handler
id|irqreturn_t
id|interrupt_handler
c_func
(paren
r_int
id|interrupt
comma
r_void
op_star
id|cardptr
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|RspMessage
id|rcvmsg
suffix:semicolon
r_int
id|channel
suffix:semicolon
r_int
id|card
suffix:semicolon
id|card
op_assign
id|get_card_from_irq
c_func
(paren
id|interrupt
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|IS_VALID_CARD
c_func
(paren
id|card
)paren
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;Invalid param: %d is not a valid card id&bslash;n&quot;
comma
id|card
)paren
suffix:semicolon
r_return
id|IRQ_NONE
suffix:semicolon
)brace
id|pr_debug
c_func
(paren
l_string|&quot;%s: Entered Interrupt handler&bslash;n&quot;
comma
id|sc_adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|devicename
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Pull all of the waiting messages off the response queue&n;&t; */
r_while
c_loop
(paren
op_logical_neg
id|receivemessage
c_func
(paren
id|card
comma
op_amp
id|rcvmsg
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t; * Push the message to the adapter structure for&n;&t;&t; * send_and_receive to snoop&n;&t;&t; */
r_if
c_cond
(paren
id|sc_adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|want_async_messages
)paren
(brace
id|memcpy
c_func
(paren
op_amp
(paren
id|sc_adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|async_msg
)paren
comma
op_amp
id|rcvmsg
comma
r_sizeof
(paren
id|RspMessage
)paren
)paren
suffix:semicolon
)brace
id|channel
op_assign
(paren
r_int
r_int
)paren
id|rcvmsg.phy_link_no
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Trap Invalid request messages&n;&t;&t; */
r_if
c_cond
(paren
id|IS_CM_MESSAGE
c_func
(paren
id|rcvmsg
comma
l_int|0
comma
l_int|0
comma
id|Invalid
)paren
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;%s: Invalid request Message, rsp_status = %d&bslash;n&quot;
comma
id|sc_adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|devicename
comma
id|rcvmsg.rsp_status
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Check for a linkRead message&n;&t;&t; */
r_if
c_cond
(paren
id|IS_CE_MESSAGE
c_func
(paren
id|rcvmsg
comma
id|Lnk
comma
l_int|1
comma
id|Read
)paren
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;%s: Received packet 0x%x bytes long at 0x%x&bslash;n&quot;
comma
id|sc_adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|devicename
comma
id|rcvmsg.msg_data.response.msg_len
comma
id|rcvmsg.msg_data.response.buff_offset
)paren
suffix:semicolon
id|rcvpkt
c_func
(paren
id|card
comma
op_amp
id|rcvmsg
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Handle a write acknoledgement&n;&t;&t; */
r_if
c_cond
(paren
id|IS_CE_MESSAGE
c_func
(paren
id|rcvmsg
comma
id|Lnk
comma
l_int|1
comma
id|Write
)paren
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;%s: Packet Send ACK on channel %d&bslash;n&quot;
comma
id|sc_adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|devicename
comma
id|rcvmsg.phy_link_no
)paren
suffix:semicolon
id|sc_adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|channel
(braket
id|rcvmsg.phy_link_no
op_minus
l_int|1
)braket
dot
id|free_sendbufs
op_increment
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Handle a connection message&n;&t;&t; */
r_if
c_cond
(paren
id|IS_CE_MESSAGE
c_func
(paren
id|rcvmsg
comma
id|Phy
comma
l_int|1
comma
id|Connect
)paren
)paren
(brace
r_int
r_int
id|callid
suffix:semicolon
id|setup_parm
id|setup
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;%s: Connect message: line %d: status %d: cause 0x%x&bslash;n&quot;
comma
id|sc_adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|devicename
comma
id|rcvmsg.phy_link_no
comma
id|rcvmsg.rsp_status
comma
id|rcvmsg.msg_data.byte_array
(braket
l_int|2
)braket
)paren
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|callid
comma
id|rcvmsg.msg_data.byte_array
comma
r_sizeof
(paren
r_int
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|callid
op_ge
l_int|0x8000
op_logical_and
id|callid
op_le
l_int|0xFFFF
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;%s: Got Dial-Out Rsp&bslash;n&quot;
comma
id|sc_adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|devicename
)paren
suffix:semicolon
id|indicate_status
c_func
(paren
id|card
comma
id|ISDN_STAT_DCONN
comma
(paren
r_int
r_int
)paren
id|rcvmsg.phy_link_no
op_minus
l_int|1
comma
l_int|NULL
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|callid
op_ge
l_int|0x0000
op_logical_and
id|callid
op_le
l_int|0x7FFF
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;%s: Got Incoming Call&bslash;n&quot;
comma
id|sc_adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|devicename
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|setup.phone
comma
op_amp
(paren
id|rcvmsg.msg_data.byte_array
(braket
l_int|4
)braket
)paren
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|setup.eazmsn
comma
id|sc_adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|channel
(braket
id|rcvmsg.phy_link_no
op_minus
l_int|1
)braket
dot
id|dn
)paren
suffix:semicolon
id|setup.si1
op_assign
l_int|7
suffix:semicolon
id|setup.si2
op_assign
l_int|0
suffix:semicolon
id|setup.plan
op_assign
l_int|0
suffix:semicolon
id|setup.screen
op_assign
l_int|0
suffix:semicolon
id|indicate_status
c_func
(paren
id|card
comma
id|ISDN_STAT_ICALL
comma
(paren
r_int
r_int
)paren
id|rcvmsg.phy_link_no
op_minus
l_int|1
comma
(paren
r_char
op_star
)paren
op_amp
id|setup
)paren
suffix:semicolon
id|indicate_status
c_func
(paren
id|card
comma
id|ISDN_STAT_DCONN
comma
(paren
r_int
r_int
)paren
id|rcvmsg.phy_link_no
op_minus
l_int|1
comma
l_int|NULL
)paren
suffix:semicolon
)brace
r_continue
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Handle a disconnection message&n;&t;&t; */
r_if
c_cond
(paren
id|IS_CE_MESSAGE
c_func
(paren
id|rcvmsg
comma
id|Phy
comma
l_int|1
comma
id|Disconnect
)paren
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;%s: disconnect message: line %d: status %d: cause 0x%x&bslash;n&quot;
comma
id|sc_adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|devicename
comma
id|rcvmsg.phy_link_no
comma
id|rcvmsg.rsp_status
comma
id|rcvmsg.msg_data.byte_array
(braket
l_int|2
)braket
)paren
suffix:semicolon
id|indicate_status
c_func
(paren
id|card
comma
id|ISDN_STAT_BHUP
comma
(paren
r_int
r_int
)paren
id|rcvmsg.phy_link_no
op_minus
l_int|1
comma
l_int|NULL
)paren
suffix:semicolon
id|indicate_status
c_func
(paren
id|card
comma
id|ISDN_STAT_DHUP
comma
(paren
r_int
r_int
)paren
id|rcvmsg.phy_link_no
op_minus
l_int|1
comma
l_int|NULL
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Handle a startProc engine up message&n;&t;&t; */
r_if
c_cond
(paren
id|IS_CM_MESSAGE
c_func
(paren
id|rcvmsg
comma
l_int|5
comma
l_int|0
comma
id|MiscEngineUp
)paren
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;%s: Received EngineUp message&bslash;n&quot;
comma
id|sc_adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|devicename
)paren
suffix:semicolon
id|sc_adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|EngineUp
op_assign
l_int|1
suffix:semicolon
id|sendmessage
c_func
(paren
id|card
comma
id|CEPID
comma
id|ceReqTypeCall
comma
id|ceReqClass0
comma
id|ceReqCallGetMyNumber
comma
l_int|1
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
id|sendmessage
c_func
(paren
id|card
comma
id|CEPID
comma
id|ceReqTypeCall
comma
id|ceReqClass0
comma
id|ceReqCallGetMyNumber
comma
l_int|2
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
id|init_timer
c_func
(paren
op_amp
id|sc_adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|stat_timer
)paren
suffix:semicolon
id|sc_adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|stat_timer.function
op_assign
id|check_phystat
suffix:semicolon
id|sc_adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|stat_timer.data
op_assign
id|card
suffix:semicolon
id|sc_adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|stat_timer.expires
op_assign
id|jiffies
op_plus
id|CHECKSTAT_TIME
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|sc_adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|stat_timer
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Start proc response&n;&t;&t; */
r_if
c_cond
(paren
id|IS_CM_MESSAGE
c_func
(paren
id|rcvmsg
comma
l_int|2
comma
l_int|0
comma
id|StartProc
)paren
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;%s: StartProc Response Status %d&bslash;n&quot;
comma
id|sc_adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|devicename
comma
id|rcvmsg.rsp_status
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Handle a GetMyNumber Rsp&n;&t;&t; */
r_if
c_cond
(paren
id|IS_CE_MESSAGE
c_func
(paren
id|rcvmsg
comma
id|Call
comma
l_int|0
comma
id|GetMyNumber
)paren
)paren
(brace
id|strcpy
c_func
(paren
id|sc_adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|channel
(braket
id|rcvmsg.phy_link_no
op_minus
l_int|1
)braket
dot
id|dn
comma
id|rcvmsg.msg_data.byte_array
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * PhyStatus response&n;&t;&t; */
r_if
c_cond
(paren
id|IS_CE_MESSAGE
c_func
(paren
id|rcvmsg
comma
id|Phy
comma
l_int|2
comma
id|Status
)paren
)paren
(brace
r_int
r_int
id|b1stat
comma
id|b2stat
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * Covert the message data to the adapter-&gt;phystat code&n;&t;&t;&t; */
id|b1stat
op_assign
(paren
r_int
r_int
)paren
id|rcvmsg.msg_data.byte_array
(braket
l_int|0
)braket
suffix:semicolon
id|b2stat
op_assign
(paren
r_int
r_int
)paren
id|rcvmsg.msg_data.byte_array
(braket
l_int|1
)braket
suffix:semicolon
id|sc_adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|nphystat
op_assign
(paren
id|b2stat
op_rshift
l_int|8
)paren
op_or
id|b1stat
suffix:semicolon
multiline_comment|/* endian?? */
id|pr_debug
c_func
(paren
l_string|&quot;%s: PhyStat is 0x%2x&bslash;n&quot;
comma
id|sc_adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|devicename
comma
id|sc_adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|nphystat
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/* &n;&t;&t; * Handle a GetFramFormat&n;&t;&t; */
r_if
c_cond
(paren
id|IS_CE_MESSAGE
c_func
(paren
id|rcvmsg
comma
id|Call
comma
l_int|0
comma
id|GetFrameFormat
)paren
)paren
(brace
r_if
c_cond
(paren
id|rcvmsg.msg_data.byte_array
(braket
l_int|0
)braket
op_ne
id|HDLC_PROTO
)paren
(brace
r_int
r_int
id|proto
op_assign
id|HDLC_PROTO
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t;&t; * Set board format to HDLC if it wasn&squot;t already&n;&t;&t;&t;&t; */
id|pr_debug
c_func
(paren
l_string|&quot;%s: current frame format: 0x%x, will change to HDLC&bslash;n&quot;
comma
id|sc_adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|devicename
comma
id|rcvmsg.msg_data.byte_array
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|sendmessage
c_func
(paren
id|card
comma
id|CEPID
comma
id|ceReqTypeCall
comma
id|ceReqClass0
comma
id|ceReqCallSetFrameFormat
comma
(paren
r_int
r_char
)paren
id|channel
op_plus
l_int|1
comma
l_int|1
comma
op_amp
id|proto
)paren
suffix:semicolon
)brace
r_continue
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Hmm...&n;&t;&t; */
id|pr_debug
c_func
(paren
l_string|&quot;%s: Received unhandled message (%d,%d,%d) link %d&bslash;n&quot;
comma
id|sc_adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|devicename
comma
id|rcvmsg.type
comma
id|rcvmsg
dot
r_class
comma
id|rcvmsg.code
comma
id|rcvmsg.phy_link_no
)paren
suffix:semicolon
)brace
multiline_comment|/* while */
id|pr_debug
c_func
(paren
l_string|&quot;%s: Exiting Interrupt Handler&bslash;n&quot;
comma
id|sc_adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|devicename
)paren
suffix:semicolon
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
eof
