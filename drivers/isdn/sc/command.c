multiline_comment|/* $Id: command.c,v 1.4.10.1 2001/09/23 22:24:59 kai Exp $&n; *&n; * Copyright (C) 1996  SpellCaster Telecommunications Inc.&n; *&n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; * For more information, please contact gpl-info@spellcast.com or write:&n; *&n; *     SpellCaster Telecommunications Inc.&n; *     5621 Finch Avenue East, Unit #3&n; *     Scarborough, Ontario  Canada&n; *     M1B 2T9&n; *     +1 (416) 297-8565&n; *     +1 (416) 297-6433 Facsimile&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &quot;includes.h&quot;&t;&t;/* This must be first */
macro_line|#include &quot;hardware.h&quot;
macro_line|#include &quot;message.h&quot;
macro_line|#include &quot;card.h&quot;
macro_line|#include &quot;scioc.h&quot;
r_int
id|dial
c_func
(paren
r_int
id|card
comma
r_int
r_int
id|channel
comma
id|setup_parm
id|setup
)paren
suffix:semicolon
r_int
id|hangup
c_func
(paren
r_int
id|card
comma
r_int
r_int
id|channel
)paren
suffix:semicolon
r_int
id|answer
c_func
(paren
r_int
id|card
comma
r_int
r_int
id|channel
)paren
suffix:semicolon
r_int
id|clreaz
c_func
(paren
r_int
id|card
comma
r_int
r_int
id|channel
)paren
suffix:semicolon
r_int
id|seteaz
c_func
(paren
r_int
id|card
comma
r_int
r_int
id|channel
comma
r_char
op_star
)paren
suffix:semicolon
r_int
id|setl2
c_func
(paren
r_int
id|card
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
r_int
id|setl3
c_func
(paren
r_int
id|card
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
r_int
id|acceptb
c_func
(paren
r_int
id|card
comma
r_int
r_int
id|channel
)paren
suffix:semicolon
r_extern
r_int
id|cinst
suffix:semicolon
r_extern
id|board
op_star
id|adapter
(braket
)braket
suffix:semicolon
r_extern
r_int
id|sc_ioctl
c_func
(paren
r_int
comma
id|scs_ioctl
op_star
)paren
suffix:semicolon
r_extern
r_int
id|setup_buffers
c_func
(paren
r_int
comma
r_int
comma
r_int
r_int
)paren
suffix:semicolon
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
id|check_reset
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
id|send_and_receive
c_func
(paren
r_int
comma
r_int
r_int
comma
r_int
r_char
comma
r_int
r_char
comma
r_int
r_char
comma
r_int
r_char
comma
r_int
r_char
comma
r_int
r_char
op_star
comma
id|RspMessage
op_star
comma
r_int
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
r_inline
r_void
id|pullphone
c_func
(paren
r_char
op_star
comma
r_char
op_star
)paren
suffix:semicolon
macro_line|#ifdef DEBUG
multiline_comment|/*&n; * Translate command codes to strings&n; */
DECL|variable|commands
r_static
r_char
op_star
id|commands
(braket
)braket
op_assign
(brace
l_string|&quot;ISDN_CMD_IOCTL&quot;
comma
l_string|&quot;ISDN_CMD_DIAL&quot;
comma
l_string|&quot;ISDN_CMD_ACCEPTB&quot;
comma
l_string|&quot;ISDN_CMD_ACCEPTB&quot;
comma
l_string|&quot;ISDN_CMD_HANGUP&quot;
comma
l_string|&quot;ISDN_CMD_CLREAZ&quot;
comma
l_string|&quot;ISDN_CMD_SETEAZ&quot;
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_string|&quot;ISDN_CMD_SETL2&quot;
comma
l_int|NULL
comma
l_string|&quot;ISDN_CMD_SETL3&quot;
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * Translates ISDN4Linux protocol codes to strings for debug messages&n; */
DECL|variable|l3protos
r_static
r_char
op_star
id|l3protos
(braket
)braket
op_assign
(brace
l_string|&quot;ISDN_PROTO_L3_TRANS&quot;
)brace
suffix:semicolon
DECL|variable|l2protos
r_static
r_char
op_star
id|l2protos
(braket
)braket
op_assign
(brace
l_string|&quot;ISDN_PROTO_L2_X75I&quot;
comma
l_string|&quot;ISDN_PROTO_L2_X75UI&quot;
comma
l_string|&quot;ISDN_PROTO_L2_X75BUI&quot;
comma
l_string|&quot;ISDN_PROTO_L2_HDLC&quot;
comma
l_string|&quot;ISDN_PROTO_L2_TRANS&quot;
)brace
suffix:semicolon
macro_line|#endif
DECL|function|get_card_from_id
r_int
id|get_card_from_id
c_func
(paren
r_int
id|driver
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
id|adapter
(braket
id|i
)braket
op_member_access_from_pointer
id|driverId
op_eq
id|driver
)paren
(brace
r_return
id|i
suffix:semicolon
)brace
)brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
multiline_comment|/* &n; * command&n; */
DECL|function|command
r_int
id|command
c_func
(paren
id|isdn_ctrl
op_star
id|cmd
)paren
(brace
r_int
id|card
suffix:semicolon
id|card
op_assign
id|get_card_from_id
c_func
(paren
id|cmd-&gt;driver
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
op_minus
id|ENODEV
suffix:semicolon
)brace
id|pr_debug
c_func
(paren
l_string|&quot;%s: Received %s command from Link Layer&bslash;n&quot;
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|devicename
comma
id|commands
(braket
id|cmd-&gt;command
)braket
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Dispatch the command&n;&t; */
r_switch
c_cond
(paren
id|cmd-&gt;command
)paren
(brace
r_case
id|ISDN_CMD_IOCTL
suffix:colon
(brace
r_int
r_int
id|cmdptr
suffix:semicolon
id|scs_ioctl
id|ioc
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|cmdptr
comma
id|cmd-&gt;parm.num
comma
r_sizeof
(paren
r_int
r_int
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|ioc
comma
(paren
id|scs_ioctl
op_star
)paren
id|cmdptr
comma
r_sizeof
(paren
id|scs_ioctl
)paren
)paren
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;%s: Failed to verify user space 0x%x&bslash;n&quot;
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|devicename
comma
id|cmdptr
)paren
suffix:semicolon
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
id|sc_ioctl
c_func
(paren
id|card
comma
op_amp
id|ioc
)paren
suffix:semicolon
)brace
r_case
id|ISDN_CMD_DIAL
suffix:colon
r_return
id|dial
c_func
(paren
id|card
comma
id|cmd-&gt;arg
comma
id|cmd-&gt;parm.setup
)paren
suffix:semicolon
r_case
id|ISDN_CMD_HANGUP
suffix:colon
r_return
id|hangup
c_func
(paren
id|card
comma
id|cmd-&gt;arg
)paren
suffix:semicolon
r_case
id|ISDN_CMD_ACCEPTD
suffix:colon
r_return
id|answer
c_func
(paren
id|card
comma
id|cmd-&gt;arg
)paren
suffix:semicolon
r_case
id|ISDN_CMD_ACCEPTB
suffix:colon
r_return
id|acceptb
c_func
(paren
id|card
comma
id|cmd-&gt;arg
)paren
suffix:semicolon
r_case
id|ISDN_CMD_CLREAZ
suffix:colon
r_return
id|clreaz
c_func
(paren
id|card
comma
id|cmd-&gt;arg
)paren
suffix:semicolon
r_case
id|ISDN_CMD_SETEAZ
suffix:colon
r_return
id|seteaz
c_func
(paren
id|card
comma
id|cmd-&gt;arg
comma
id|cmd-&gt;parm.num
)paren
suffix:semicolon
r_case
id|ISDN_CMD_SETL2
suffix:colon
r_return
id|setl2
c_func
(paren
id|card
comma
id|cmd-&gt;arg
)paren
suffix:semicolon
r_case
id|ISDN_CMD_SETL3
suffix:colon
r_return
id|setl3
c_func
(paren
id|card
comma
id|cmd-&gt;arg
)paren
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Confirm our ability to communicate with the board.  This test assumes no&n; * other message activity is present&n; */
DECL|function|loopback
r_int
id|loopback
c_func
(paren
r_int
id|card
)paren
(brace
r_int
id|status
suffix:semicolon
r_static
r_char
id|testmsg
(braket
)braket
op_assign
l_string|&quot;Test Message&quot;
suffix:semicolon
id|RspMessage
id|rspmsg
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
op_minus
id|ENODEV
suffix:semicolon
)brace
id|pr_debug
c_func
(paren
l_string|&quot;%s: Sending loopback message&bslash;n&quot;
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|devicename
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Send the loopback message to confirm that memory transfer is&n;&t; * operational&n;&t; */
id|status
op_assign
id|send_and_receive
c_func
(paren
id|card
comma
id|CMPID
comma
id|cmReqType1
comma
id|cmReqClass0
comma
id|cmReqMsgLpbk
comma
l_int|0
comma
(paren
r_int
r_char
)paren
id|strlen
c_func
(paren
id|testmsg
)paren
comma
(paren
r_int
r_char
op_star
)paren
id|testmsg
comma
op_amp
id|rspmsg
comma
id|SAR_TIMEOUT
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|status
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;%s: Loopback message successfully sent&bslash;n&quot;
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|devicename
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|rspmsg.msg_data.byte_array
comma
id|testmsg
)paren
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;%s: Loopback return != sent&bslash;n&quot;
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|devicename
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|pr_debug
c_func
(paren
l_string|&quot;%s: Send loopback message failed&bslash;n&quot;
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|devicename
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * start the onboard firmware&n; */
DECL|function|startproc
r_int
id|startproc
c_func
(paren
r_int
id|card
)paren
(brace
r_int
id|status
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
op_minus
id|ENODEV
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * send start msg &n;&t; */
id|status
op_assign
id|sendmessage
c_func
(paren
id|card
comma
id|CMPID
comma
id|cmReqType2
comma
id|cmReqClass0
comma
id|cmReqStartProc
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;%s: Sent startProc&bslash;n&quot;
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|devicename
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
DECL|function|loadproc
r_int
id|loadproc
c_func
(paren
r_int
id|card
comma
r_char
op_star
id|data
)paren
(brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * Dials the number passed in &n; */
DECL|function|dial
r_int
id|dial
c_func
(paren
r_int
id|card
comma
r_int
r_int
id|channel
comma
id|setup_parm
id|setup
)paren
(brace
r_int
id|status
suffix:semicolon
r_char
id|Phone
(braket
l_int|48
)braket
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
op_minus
id|ENODEV
suffix:semicolon
)brace
multiline_comment|/*extract ISDN number to dial from eaz/msn string*/
id|strcpy
c_func
(paren
id|Phone
comma
id|setup.phone
)paren
suffix:semicolon
multiline_comment|/*send the connection message*/
id|status
op_assign
id|sendmessage
c_func
(paren
id|card
comma
id|CEPID
comma
id|ceReqTypePhy
comma
id|ceReqClass1
comma
id|ceReqPhyConnect
comma
(paren
r_int
r_char
)paren
id|channel
op_plus
l_int|1
comma
id|strlen
c_func
(paren
id|Phone
)paren
comma
(paren
r_int
r_int
op_star
)paren
id|Phone
)paren
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;%s: Dialing %s on channel %d&bslash;n&quot;
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|devicename
comma
id|Phone
comma
id|channel
op_plus
l_int|1
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
multiline_comment|/*&n; * Answer an incoming call &n; */
DECL|function|answer
r_int
id|answer
c_func
(paren
r_int
id|card
comma
r_int
r_int
id|channel
)paren
(brace
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
op_minus
id|ENODEV
suffix:semicolon
)brace
r_if
c_cond
(paren
id|setup_buffers
c_func
(paren
id|card
comma
id|channel
op_plus
l_int|1
comma
id|BUFFER_SIZE
)paren
)paren
(brace
id|hangup
c_func
(paren
id|card
comma
id|channel
op_plus
l_int|1
)paren
suffix:semicolon
r_return
op_minus
id|ENOBUFS
suffix:semicolon
)brace
id|indicate_status
c_func
(paren
id|card
comma
id|ISDN_STAT_BCONN
comma
id|channel
comma
l_int|NULL
)paren
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;%s: Answered incoming call on channel %s&bslash;n&quot;
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|devicename
comma
id|channel
op_plus
l_int|1
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Hangup up the call on specified channel&n; */
DECL|function|hangup
r_int
id|hangup
c_func
(paren
r_int
id|card
comma
r_int
r_int
id|channel
)paren
(brace
r_int
id|status
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
op_minus
id|ENODEV
suffix:semicolon
)brace
id|status
op_assign
id|sendmessage
c_func
(paren
id|card
comma
id|CEPID
comma
id|ceReqTypePhy
comma
id|ceReqClass1
comma
id|ceReqPhyDisconnect
comma
(paren
r_int
r_char
)paren
id|channel
op_plus
l_int|1
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;%s: Sent HANGUP message to channel %d&bslash;n&quot;
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|devicename
comma
id|channel
op_plus
l_int|1
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
multiline_comment|/*&n; * Set the layer 2 protocol (X.25, HDLC, Raw)&n; */
DECL|function|setl2
r_int
id|setl2
c_func
(paren
r_int
id|card
comma
r_int
r_int
id|arg
)paren
(brace
r_int
id|status
op_assign
l_int|0
suffix:semicolon
r_int
id|protocol
comma
id|channel
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
op_minus
id|ENODEV
suffix:semicolon
)brace
id|protocol
op_assign
id|arg
op_rshift
l_int|8
suffix:semicolon
id|channel
op_assign
id|arg
op_amp
l_int|0xff
suffix:semicolon
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|channel
(braket
id|channel
)braket
dot
id|l2_proto
op_assign
id|protocol
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;%s: Level 2 protocol for channel %d set to %s from %d&bslash;n&quot;
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|devicename
comma
id|channel
op_plus
l_int|1
comma
id|l2protos
(braket
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|channel
(braket
id|channel
)braket
dot
id|l2_proto
)braket
comma
id|protocol
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * check that the adapter is also set to the correct protocol&n;&t; */
id|pr_debug
c_func
(paren
l_string|&quot;%s: Sending GetFrameFormat for channel %d&bslash;n&quot;
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|devicename
comma
id|channel
op_plus
l_int|1
)paren
suffix:semicolon
id|status
op_assign
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
id|ceReqCallGetFrameFormat
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
(paren
r_int
r_int
op_star
)paren
id|protocol
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
)paren
(brace
r_return
id|status
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Set the layer 3 protocol&n; */
DECL|function|setl3
r_int
id|setl3
c_func
(paren
r_int
id|card
comma
r_int
r_int
id|channel
)paren
(brace
r_int
id|protocol
op_assign
id|channel
op_rshift
l_int|8
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
op_minus
id|ENODEV
suffix:semicolon
)brace
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|channel
(braket
id|channel
)braket
dot
id|l3_proto
op_assign
id|protocol
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;%s: Level 3 protocol for channel %d set to %s&bslash;n&quot;
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|devicename
comma
id|channel
op_plus
l_int|1
comma
id|l3protos
(braket
id|protocol
)braket
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|acceptb
r_int
id|acceptb
c_func
(paren
r_int
id|card
comma
r_int
r_int
id|channel
)paren
(brace
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
op_minus
id|ENODEV
suffix:semicolon
)brace
r_if
c_cond
(paren
id|setup_buffers
c_func
(paren
id|card
comma
id|channel
op_plus
l_int|1
comma
id|BUFFER_SIZE
)paren
)paren
(brace
id|hangup
c_func
(paren
id|card
comma
id|channel
op_plus
l_int|1
)paren
suffix:semicolon
r_return
op_minus
id|ENOBUFS
suffix:semicolon
)brace
id|pr_debug
c_func
(paren
l_string|&quot;%s: B-Channel connection accepted on channel %d&bslash;n&quot;
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|devicename
comma
id|channel
op_plus
l_int|1
)paren
suffix:semicolon
id|indicate_status
c_func
(paren
id|card
comma
id|ISDN_STAT_BCONN
comma
id|channel
comma
l_int|NULL
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|clreaz
r_int
id|clreaz
c_func
(paren
r_int
id|card
comma
r_int
r_int
id|arg
)paren
(brace
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
op_minus
id|ENODEV
suffix:semicolon
)brace
id|strcpy
c_func
(paren
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|channel
(braket
id|arg
)braket
dot
id|eazlist
comma
l_string|&quot;&quot;
)paren
suffix:semicolon
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|channel
(braket
id|arg
)braket
dot
id|eazclear
op_assign
l_int|1
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;%s: EAZ List cleared for channel %d&bslash;n&quot;
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|devicename
comma
id|arg
op_plus
l_int|1
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|seteaz
r_int
id|seteaz
c_func
(paren
r_int
id|card
comma
r_int
r_int
id|arg
comma
r_char
op_star
id|num
)paren
(brace
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
op_minus
id|ENODEV
suffix:semicolon
)brace
id|strcpy
c_func
(paren
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|channel
(braket
id|arg
)braket
dot
id|eazlist
comma
id|num
)paren
suffix:semicolon
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|channel
(braket
id|arg
)braket
dot
id|eazclear
op_assign
l_int|0
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;%s: EAZ list for channel %d set to: %s&bslash;n&quot;
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|devicename
comma
id|arg
op_plus
l_int|1
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|channel
(braket
id|arg
)braket
dot
id|eazlist
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|reset
r_int
id|reset
c_func
(paren
r_int
id|card
)paren
(brace
r_int
r_int
id|flags
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
op_minus
id|ENODEV
suffix:semicolon
)brace
id|indicate_status
c_func
(paren
id|card
comma
id|ISDN_STAT_STOP
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|EngineUp
)paren
(brace
id|del_timer
c_func
(paren
op_amp
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|stat_timer
)paren
suffix:semicolon
)brace
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|EngineUp
op_assign
l_int|0
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|init_timer
c_func
(paren
op_amp
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|reset_timer
)paren
suffix:semicolon
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|reset_timer.function
op_assign
id|check_reset
suffix:semicolon
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|reset_timer.data
op_assign
id|card
suffix:semicolon
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|reset_timer.expires
op_assign
id|jiffies
op_plus
id|CHECKRESET_TIME
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|reset_timer
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x1
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|ioport
(braket
id|SFT_RESET
)braket
)paren
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;%s: Adapter Reset&bslash;n&quot;
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|devicename
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|flushreadfifo
r_void
id|flushreadfifo
(paren
r_int
id|card
)paren
(brace
r_while
c_loop
(paren
id|inb
c_func
(paren
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|ioport
(braket
id|FIFO_STATUS
)braket
)paren
op_amp
id|RF_HAS_DATA
)paren
(brace
id|inb
c_func
(paren
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|ioport
(braket
id|FIFO_READ
)braket
)paren
suffix:semicolon
)brace
)brace
eof
