multiline_comment|/*&n; * Copyright (C) 1996  SpellCaster Telecommunications Inc.&n; *&n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; */
macro_line|#include &quot;includes.h&quot;
macro_line|#include &quot;hardware.h&quot;
macro_line|#include &quot;message.h&quot;
macro_line|#include &quot;card.h&quot;
macro_line|#include &quot;scioc.h&quot;
r_extern
r_int
id|indicate_status
c_func
(paren
r_int
comma
r_int
comma
r_int
r_int
comma
r_char
op_star
)paren
suffix:semicolon
r_extern
r_int
id|startproc
c_func
(paren
r_int
)paren
suffix:semicolon
r_extern
r_int
id|loadproc
c_func
(paren
r_int
comma
r_char
op_star
id|record
)paren
suffix:semicolon
r_extern
r_int
id|reset
c_func
(paren
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
id|board
op_star
id|adapter
(braket
)braket
suffix:semicolon
r_int
id|GetStatus
c_func
(paren
r_int
id|card
comma
id|boardInfo
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * Process private IOCTL messages (typically from scctrl)&n; */
DECL|function|sc_ioctl
r_int
id|sc_ioctl
c_func
(paren
r_int
id|card
comma
id|scs_ioctl
op_star
id|data
)paren
(brace
r_switch
c_cond
(paren
id|data-&gt;command
)paren
(brace
r_case
id|SCIOCRESET
suffix:colon
multiline_comment|/* Perform a hard reset of the adapter */
(brace
id|pr_debug
c_func
(paren
l_string|&quot;%s: SCIOCRESET: ioctl received&bslash;n&quot;
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|devicename
)paren
suffix:semicolon
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|StartOnReset
op_assign
l_int|0
suffix:semicolon
r_return
(paren
id|reset
c_func
(paren
id|card
)paren
)paren
suffix:semicolon
)brace
r_case
id|SCIOCLOAD
suffix:colon
(brace
id|RspMessage
id|rcvmsg
suffix:semicolon
r_char
id|srec
(braket
id|SCIOC_SRECSIZE
)braket
suffix:semicolon
r_int
id|status
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;%s: SCIOLOAD: ioctl received&bslash;n&quot;
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
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|EngineUp
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;%s: SCIOCLOAD: command failed, LoadProc while engine running.&bslash;n&quot;
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
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Get the SRec from user space&n;&t;&t; */
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|srec
comma
(paren
r_char
op_star
)paren
id|data-&gt;dataptr
comma
r_sizeof
(paren
id|srec
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|status
op_assign
id|send_and_receive
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
id|cmReqLoadProc
comma
l_int|0
comma
r_sizeof
(paren
id|srec
)paren
comma
id|srec
comma
op_amp
id|rcvmsg
comma
id|SAR_TIMEOUT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;%s: SCIOCLOAD: command failed, status = %d&bslash;n&quot;
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|devicename
comma
id|status
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|pr_debug
c_func
(paren
l_string|&quot;%s: SCIOCLOAD: command successful&bslash;n&quot;
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
)brace
r_case
id|SCIOCSTART
suffix:colon
(brace
id|pr_debug
c_func
(paren
l_string|&quot;%s: SCIOSTART: ioctl received&bslash;n&quot;
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
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|EngineUp
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;%s: SCIOCSTART: command failed, engine already running.&bslash;n&quot;
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
l_int|1
suffix:semicolon
)brace
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|StartOnReset
op_assign
l_int|1
suffix:semicolon
id|startproc
c_func
(paren
id|card
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|SCIOCSETSWITCH
suffix:colon
(brace
id|RspMessage
id|rcvmsg
suffix:semicolon
r_char
id|switchtype
suffix:semicolon
r_int
id|status
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;%s: SCIOSETSWITCH: ioctl received&bslash;n&quot;
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|devicename
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Get the switch type from user space&n;&t;&t; */
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|switchtype
comma
(paren
r_char
op_star
)paren
id|data-&gt;dataptr
comma
r_sizeof
(paren
r_char
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;%s: SCIOCSETSWITCH: setting switch type to %d&bslash;n&quot;
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|devicename
comma
id|switchtype
)paren
suffix:semicolon
id|status
op_assign
id|send_and_receive
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
id|ceReqCallSetSwitchType
comma
l_int|0
comma
r_sizeof
(paren
r_char
)paren
comma
op_amp
id|switchtype
comma
op_amp
id|rcvmsg
comma
id|SAR_TIMEOUT
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|status
op_logical_and
op_logical_neg
id|rcvmsg.rsp_status
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;%s: SCIOCSETSWITCH: command successful&bslash;n&quot;
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
r_else
(brace
id|pr_debug
c_func
(paren
l_string|&quot;%s: SCIOCSETSWITCH: command failed (status = %d)&bslash;n&quot;
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|devicename
comma
id|status
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
)brace
r_case
id|SCIOCGETSWITCH
suffix:colon
(brace
id|RspMessage
id|rcvmsg
suffix:semicolon
r_char
id|switchtype
suffix:semicolon
r_int
id|status
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;%s: SCIOGETSWITCH: ioctl received&bslash;n&quot;
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|devicename
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Get the switch type from the board&n;&t;&t; */
id|status
op_assign
id|send_and_receive
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
id|ceReqCallGetSwitchType
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
op_amp
id|rcvmsg
comma
id|SAR_TIMEOUT
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|status
op_logical_and
op_logical_neg
id|rcvmsg.rsp_status
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;%s: SCIOCGETSWITCH: command successful&bslash;n&quot;
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|devicename
)paren
suffix:semicolon
)brace
r_else
(brace
id|pr_debug
c_func
(paren
l_string|&quot;%s: SCIOCGETSWITCH: command failed (status = %d)&bslash;n&quot;
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|devicename
comma
id|status
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
id|switchtype
op_assign
id|rcvmsg.msg_data.byte_array
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Package the switch type and send to user space&n;&t;&t; */
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
r_char
op_star
)paren
id|data-&gt;dataptr
comma
op_amp
id|switchtype
comma
r_sizeof
(paren
r_char
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|SCIOCGETSPID
suffix:colon
(brace
id|RspMessage
id|rcvmsg
suffix:semicolon
r_char
id|spid
(braket
id|SCIOC_SPIDSIZE
)braket
suffix:semicolon
r_int
id|status
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;%s: SCIOGETSPID: ioctl received&bslash;n&quot;
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|devicename
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Get the spid from the board&n;&t;&t; */
id|status
op_assign
id|send_and_receive
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
id|ceReqCallGetSPID
comma
id|data-&gt;channel
comma
l_int|0
comma
l_int|0
comma
op_amp
id|rcvmsg
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
l_string|&quot;%s: SCIOCGETSPID: command successful&bslash;n&quot;
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|devicename
)paren
suffix:semicolon
)brace
r_else
(brace
id|pr_debug
c_func
(paren
l_string|&quot;%s: SCIOCGETSPID: command failed (status = %d)&bslash;n&quot;
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|devicename
comma
id|status
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
id|strcpy
c_func
(paren
id|spid
comma
id|rcvmsg.msg_data.byte_array
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Package the switch type and send to user space&n;&t;&t; */
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
r_char
op_star
)paren
id|data-&gt;dataptr
comma
id|spid
comma
r_sizeof
(paren
id|spid
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|SCIOCSETSPID
suffix:colon
(brace
id|RspMessage
id|rcvmsg
suffix:semicolon
r_char
id|spid
(braket
id|SCIOC_SPIDSIZE
)braket
suffix:semicolon
r_int
id|status
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;%s: DCBIOSETSPID: ioctl received&bslash;n&quot;
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|devicename
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Get the spid from user space&n;&t;&t; */
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|spid
comma
(paren
r_char
op_star
)paren
id|data-&gt;dataptr
comma
r_sizeof
(paren
id|spid
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;%s: SCIOCSETSPID: setting channel %d spid to %s&bslash;n&quot;
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|devicename
comma
id|data-&gt;channel
comma
id|spid
)paren
suffix:semicolon
id|status
op_assign
id|send_and_receive
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
id|ceReqCallSetSPID
comma
id|data-&gt;channel
comma
id|strlen
c_func
(paren
id|spid
)paren
comma
id|spid
comma
op_amp
id|rcvmsg
comma
id|SAR_TIMEOUT
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|status
op_logical_and
op_logical_neg
id|rcvmsg.rsp_status
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;%s: SCIOCSETSPID: command successful&bslash;n&quot;
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
r_else
(brace
id|pr_debug
c_func
(paren
l_string|&quot;%s: SCIOCSETSPID: command failed (status = %d)&bslash;n&quot;
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|devicename
comma
id|status
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
)brace
r_case
id|SCIOCGETDN
suffix:colon
(brace
id|RspMessage
id|rcvmsg
suffix:semicolon
r_char
id|dn
(braket
id|SCIOC_DNSIZE
)braket
suffix:semicolon
r_int
id|status
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;%s: SCIOGETDN: ioctl received&bslash;n&quot;
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|devicename
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Get the dn from the board&n;&t;&t; */
id|status
op_assign
id|send_and_receive
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
id|data-&gt;channel
comma
l_int|0
comma
l_int|0
comma
op_amp
id|rcvmsg
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
l_string|&quot;%s: SCIOCGETDN: command successful&bslash;n&quot;
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|devicename
)paren
suffix:semicolon
)brace
r_else
(brace
id|pr_debug
c_func
(paren
l_string|&quot;%s: SCIOCGETDN: command failed (status = %d)&bslash;n&quot;
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|devicename
comma
id|status
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
id|strcpy
c_func
(paren
id|dn
comma
id|rcvmsg.msg_data.byte_array
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Package the dn and send to user space&n;&t;&t; */
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
r_char
op_star
)paren
id|data-&gt;dataptr
comma
id|dn
comma
r_sizeof
(paren
id|dn
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|SCIOCSETDN
suffix:colon
(brace
id|RspMessage
id|rcvmsg
suffix:semicolon
r_char
id|dn
(braket
id|SCIOC_DNSIZE
)braket
suffix:semicolon
r_int
id|status
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;%s: SCIOSETDN: ioctl received&bslash;n&quot;
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|devicename
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Get the spid from user space&n;&t;&t; */
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|dn
comma
(paren
r_char
op_star
)paren
id|data-&gt;dataptr
comma
r_sizeof
(paren
id|dn
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;%s: SCIOCSETDN: setting channel %d dn to %s&bslash;n&quot;
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|devicename
comma
id|data-&gt;channel
comma
id|dn
)paren
suffix:semicolon
id|status
op_assign
id|send_and_receive
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
id|ceReqCallSetMyNumber
comma
id|data-&gt;channel
comma
id|strlen
c_func
(paren
id|dn
)paren
comma
id|dn
comma
op_amp
id|rcvmsg
comma
id|SAR_TIMEOUT
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|status
op_logical_and
op_logical_neg
id|rcvmsg.rsp_status
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;%s: SCIOCSETDN: command successful&bslash;n&quot;
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
r_else
(brace
id|pr_debug
c_func
(paren
l_string|&quot;%s: SCIOCSETDN: command failed (status = %d)&bslash;n&quot;
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|devicename
comma
id|status
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
)brace
r_case
id|SCIOCTRACE
suffix:colon
id|pr_debug
c_func
(paren
l_string|&quot;%s: SCIOTRACE: ioctl received&bslash;n&quot;
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|devicename
)paren
suffix:semicolon
multiline_comment|/*&t;&t;adapter[card]-&gt;trace = !adapter[card]-&gt;trace; &n;&t;&t;pr_debug(&quot;%s: SCIOCTRACE: tracing turned %s&bslash;n&quot;, adapter[card]-&gt;devicename,&n;&t;&t;&t;adapter[card]-&gt;trace ? &quot;ON&quot; : &quot;OFF&quot;); */
r_break
suffix:semicolon
r_case
id|SCIOCSTAT
suffix:colon
(brace
id|boardInfo
id|bi
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;%s: SCIOSTAT: ioctl received&bslash;n&quot;
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|devicename
)paren
suffix:semicolon
id|GetStatus
c_func
(paren
id|card
comma
op_amp
id|bi
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
id|boardInfo
op_star
)paren
id|data-&gt;dataptr
comma
op_amp
id|bi
comma
r_sizeof
(paren
id|boardInfo
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|SCIOCGETSPEED
suffix:colon
(brace
id|RspMessage
id|rcvmsg
suffix:semicolon
r_char
id|speed
suffix:semicolon
r_int
id|status
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;%s: SCIOGETSPEED: ioctl received&bslash;n&quot;
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|devicename
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Get the speed from the board&n;&t;&t; */
id|status
op_assign
id|send_and_receive
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
id|ceReqCallGetCallType
comma
id|data-&gt;channel
comma
l_int|0
comma
l_int|0
comma
op_amp
id|rcvmsg
comma
id|SAR_TIMEOUT
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|status
op_logical_and
op_logical_neg
id|rcvmsg.rsp_status
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;%s: SCIOCGETSPEED: command successful&bslash;n&quot;
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|devicename
)paren
suffix:semicolon
)brace
r_else
(brace
id|pr_debug
c_func
(paren
l_string|&quot;%s: SCIOCGETSPEED: command failed (status = %d)&bslash;n&quot;
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|devicename
comma
id|status
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
id|speed
op_assign
id|rcvmsg.msg_data.byte_array
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Package the switch type and send to user space&n;&t;&t; */
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
r_char
op_star
)paren
id|data-&gt;dataptr
comma
op_amp
id|speed
comma
r_sizeof
(paren
r_char
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|SCIOCSETSPEED
suffix:colon
id|pr_debug
c_func
(paren
l_string|&quot;%s: SCIOCSETSPEED: ioctl received&bslash;n&quot;
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|devicename
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SCIOCLOOPTST
suffix:colon
id|pr_debug
c_func
(paren
l_string|&quot;%s: SCIOCLOOPTST: ioctl received&bslash;n&quot;
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|devicename
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|GetStatus
r_int
id|GetStatus
c_func
(paren
r_int
id|card
comma
id|boardInfo
op_star
id|bi
)paren
(brace
id|RspMessage
id|rcvmsg
suffix:semicolon
r_int
id|i
comma
id|status
suffix:semicolon
multiline_comment|/*&n;&t; * Fill in some of the basic info about the board&n;&t; */
id|bi-&gt;modelid
op_assign
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|model
suffix:semicolon
id|strcpy
c_func
(paren
id|bi-&gt;serial_no
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|hwconfig.serial_no
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|bi-&gt;part_no
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|hwconfig.part_no
)paren
suffix:semicolon
id|bi-&gt;iobase
op_assign
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|iobase
suffix:semicolon
id|bi-&gt;rambase
op_assign
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|rambase
suffix:semicolon
id|bi-&gt;irq
op_assign
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|interrupt
suffix:semicolon
id|bi-&gt;ramsize
op_assign
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|hwconfig.ram_size
suffix:semicolon
id|bi-&gt;interface
op_assign
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|hwconfig.st_u_sense
suffix:semicolon
id|strcpy
c_func
(paren
id|bi-&gt;load_ver
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|load_ver
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|bi-&gt;proc_ver
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|proc_ver
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Get the current PhyStats and LnkStats&n;&t; */
id|status
op_assign
id|send_and_receive
c_func
(paren
id|card
comma
id|CEPID
comma
id|ceReqTypePhy
comma
id|ceReqClass2
comma
id|ceReqPhyStatus
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
comma
op_amp
id|rcvmsg
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
r_if
c_cond
(paren
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|model
OL
id|PRI_BOARD
)paren
(brace
id|bi-&gt;l1_status
op_assign
id|rcvmsg.msg_data.byte_array
(braket
l_int|2
)braket
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
id|BRI_CHANNELS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|bi-&gt;status.bristats
(braket
id|i
)braket
dot
id|phy_stat
op_assign
id|rcvmsg.msg_data.byte_array
(braket
id|i
)braket
suffix:semicolon
)brace
)brace
r_else
(brace
id|bi-&gt;l1_status
op_assign
id|rcvmsg.msg_data.byte_array
(braket
l_int|0
)braket
suffix:semicolon
id|bi-&gt;l2_status
op_assign
id|rcvmsg.msg_data.byte_array
(braket
l_int|1
)braket
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
id|PRI_CHANNELS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|bi-&gt;status.pristats
(braket
id|i
)braket
dot
id|phy_stat
op_assign
id|rcvmsg.msg_data.byte_array
(braket
id|i
op_plus
l_int|2
)braket
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n;&t; * Get the call types for each channel&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|nChannels
suffix:semicolon
id|i
op_increment
)paren
(brace
id|status
op_assign
id|send_and_receive
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
id|ceReqCallGetCallType
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
comma
op_amp
id|rcvmsg
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
r_if
c_cond
(paren
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|model
op_eq
id|PRI_BOARD
)paren
(brace
id|bi-&gt;status.pristats
(braket
id|i
)braket
dot
id|call_type
op_assign
id|rcvmsg.msg_data.byte_array
(braket
l_int|0
)braket
suffix:semicolon
)brace
r_else
(brace
id|bi-&gt;status.bristats
(braket
id|i
)braket
dot
id|call_type
op_assign
id|rcvmsg.msg_data.byte_array
(braket
l_int|0
)braket
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n;&t; * If PRI, get the call states and service states for each channel&n;&t; */
r_if
c_cond
(paren
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|model
op_eq
id|PRI_BOARD
)paren
(brace
multiline_comment|/*&n;&t;&t; * Get the call states&n;&t;&t; */
id|status
op_assign
id|send_and_receive
c_func
(paren
id|card
comma
id|CEPID
comma
id|ceReqTypeStat
comma
id|ceReqClass2
comma
id|ceReqPhyChCallState
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
comma
op_amp
id|rcvmsg
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
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|PRI_CHANNELS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|bi-&gt;status.pristats
(braket
id|i
)braket
dot
id|call_state
op_assign
id|rcvmsg.msg_data.byte_array
(braket
id|i
)braket
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t;&t; * Get the service states&n;&t;&t; */
id|status
op_assign
id|send_and_receive
c_func
(paren
id|card
comma
id|CEPID
comma
id|ceReqTypeStat
comma
id|ceReqClass2
comma
id|ceReqPhyChServState
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
comma
op_amp
id|rcvmsg
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
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|PRI_CHANNELS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|bi-&gt;status.pristats
(braket
id|i
)braket
dot
id|serv_state
op_assign
id|rcvmsg.msg_data.byte_array
(braket
id|i
)braket
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t;&t; * Get the link stats for the channels&n;&t;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
op_le
id|PRI_CHANNELS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|status
op_assign
id|send_and_receive
c_func
(paren
id|card
comma
id|CEPID
comma
id|ceReqTypeLnk
comma
id|ceReqClass0
comma
id|ceReqLnkGetStats
comma
id|i
comma
l_int|0
comma
l_int|NULL
comma
op_amp
id|rcvmsg
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
id|bi-&gt;status.pristats
(braket
id|i
op_minus
l_int|1
)braket
dot
id|link_stats.tx_good
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
id|bi-&gt;status.pristats
(braket
id|i
op_minus
l_int|1
)braket
dot
id|link_stats.tx_bad
op_assign
(paren
r_int
r_int
)paren
id|rcvmsg.msg_data.byte_array
(braket
l_int|4
)braket
suffix:semicolon
id|bi-&gt;status.pristats
(braket
id|i
op_minus
l_int|1
)braket
dot
id|link_stats.rx_good
op_assign
(paren
r_int
r_int
)paren
id|rcvmsg.msg_data.byte_array
(braket
l_int|8
)braket
suffix:semicolon
id|bi-&gt;status.pristats
(braket
id|i
op_minus
l_int|1
)braket
dot
id|link_stats.rx_bad
op_assign
(paren
r_int
r_int
)paren
id|rcvmsg.msg_data.byte_array
(braket
l_int|12
)braket
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t;&t; * Link stats for the D channel&n;&t;&t; */
id|status
op_assign
id|send_and_receive
c_func
(paren
id|card
comma
id|CEPID
comma
id|ceReqTypeLnk
comma
id|ceReqClass0
comma
id|ceReqLnkGetStats
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
comma
op_amp
id|rcvmsg
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
id|bi-&gt;dch_stats.tx_good
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
id|bi-&gt;dch_stats.tx_bad
op_assign
(paren
r_int
r_int
)paren
id|rcvmsg.msg_data.byte_array
(braket
l_int|4
)braket
suffix:semicolon
id|bi-&gt;dch_stats.rx_good
op_assign
(paren
r_int
r_int
)paren
id|rcvmsg.msg_data.byte_array
(braket
l_int|8
)braket
suffix:semicolon
id|bi-&gt;dch_stats.rx_bad
op_assign
(paren
r_int
r_int
)paren
id|rcvmsg.msg_data.byte_array
(braket
l_int|12
)braket
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * If BRI or POTS, Get SPID, DN and call types for each channel&n;&t; */
multiline_comment|/*&n;&t; * Get the link stats for the channels&n;&t; */
id|status
op_assign
id|send_and_receive
c_func
(paren
id|card
comma
id|CEPID
comma
id|ceReqTypeLnk
comma
id|ceReqClass0
comma
id|ceReqLnkGetStats
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
comma
op_amp
id|rcvmsg
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
id|bi-&gt;dch_stats.tx_good
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
id|bi-&gt;dch_stats.tx_bad
op_assign
(paren
r_int
r_int
)paren
id|rcvmsg.msg_data.byte_array
(braket
l_int|4
)braket
suffix:semicolon
id|bi-&gt;dch_stats.rx_good
op_assign
(paren
r_int
r_int
)paren
id|rcvmsg.msg_data.byte_array
(braket
l_int|8
)braket
suffix:semicolon
id|bi-&gt;dch_stats.rx_bad
op_assign
(paren
r_int
r_int
)paren
id|rcvmsg.msg_data.byte_array
(braket
l_int|12
)braket
suffix:semicolon
id|bi-&gt;status.bristats
(braket
l_int|0
)braket
dot
id|link_stats.tx_good
op_assign
(paren
r_int
r_int
)paren
id|rcvmsg.msg_data.byte_array
(braket
l_int|16
)braket
suffix:semicolon
id|bi-&gt;status.bristats
(braket
l_int|0
)braket
dot
id|link_stats.tx_bad
op_assign
(paren
r_int
r_int
)paren
id|rcvmsg.msg_data.byte_array
(braket
l_int|20
)braket
suffix:semicolon
id|bi-&gt;status.bristats
(braket
l_int|0
)braket
dot
id|link_stats.rx_good
op_assign
(paren
r_int
r_int
)paren
id|rcvmsg.msg_data.byte_array
(braket
l_int|24
)braket
suffix:semicolon
id|bi-&gt;status.bristats
(braket
l_int|0
)braket
dot
id|link_stats.rx_bad
op_assign
(paren
r_int
r_int
)paren
id|rcvmsg.msg_data.byte_array
(braket
l_int|28
)braket
suffix:semicolon
id|bi-&gt;status.bristats
(braket
l_int|1
)braket
dot
id|link_stats.tx_good
op_assign
(paren
r_int
r_int
)paren
id|rcvmsg.msg_data.byte_array
(braket
l_int|32
)braket
suffix:semicolon
id|bi-&gt;status.bristats
(braket
l_int|1
)braket
dot
id|link_stats.tx_bad
op_assign
(paren
r_int
r_int
)paren
id|rcvmsg.msg_data.byte_array
(braket
l_int|36
)braket
suffix:semicolon
id|bi-&gt;status.bristats
(braket
l_int|1
)braket
dot
id|link_stats.rx_good
op_assign
(paren
r_int
r_int
)paren
id|rcvmsg.msg_data.byte_array
(braket
l_int|40
)braket
suffix:semicolon
id|bi-&gt;status.bristats
(braket
l_int|1
)braket
dot
id|link_stats.rx_bad
op_assign
(paren
r_int
r_int
)paren
id|rcvmsg.msg_data.byte_array
(braket
l_int|44
)braket
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Get the SPIDs&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|BRI_CHANNELS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|status
op_assign
id|send_and_receive
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
id|ceReqCallGetSPID
comma
id|i
op_plus
l_int|1
comma
l_int|0
comma
l_int|NULL
comma
op_amp
id|rcvmsg
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
id|strcpy
c_func
(paren
id|bi-&gt;status.bristats
(braket
id|i
)braket
dot
id|spid
comma
id|rcvmsg.msg_data.byte_array
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Get the DNs&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|BRI_CHANNELS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|status
op_assign
id|send_and_receive
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
id|i
op_plus
l_int|1
comma
l_int|0
comma
l_int|NULL
comma
op_amp
id|rcvmsg
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
id|strcpy
c_func
(paren
id|bi-&gt;status.bristats
(braket
id|i
)braket
dot
id|dn
comma
id|rcvmsg.msg_data.byte_array
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
