multiline_comment|/* &n;   CMTP implementation for Linux Bluetooth stack (BlueZ).&n;   Copyright (C) 2002-2003 Marcel Holtmann &lt;marcel@holtmann.org&gt;&n;&n;   This program is free software; you can redistribute it and/or modify&n;   it under the terms of the GNU General Public License version 2 as&n;   published by the Free Software Foundation;&n;&n;   THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS&n;   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n;   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF THIRD PARTY RIGHTS.&n;   IN NO EVENT SHALL THE COPYRIGHT HOLDER(S) AND AUTHOR(S) BE LIABLE FOR ANY&n;   CLAIM, OR ANY SPECIAL INDIRECT OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES &n;   WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN &n;   ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF &n;   OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.&n;&n;   ALL LIABILITY, INCLUDING LIABILITY FOR INFRINGEMENT OF ANY PATENTS, &n;   COPYRIGHTS, TRADEMARKS OR OTHER RIGHTS, RELATING TO USE OF THIS &n;   SOFTWARE IS DISCLAIMED.&n;*/
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/ioctl.h&gt;
macro_line|#include &lt;linux/file.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;linux/isdn/capilli.h&gt;
macro_line|#include &lt;linux/isdn/capicmd.h&gt;
macro_line|#include &lt;linux/isdn/capiutil.h&gt;
macro_line|#include &quot;cmtp.h&quot;
macro_line|#ifndef CONFIG_BT_CMTP_DEBUG
DECL|macro|BT_DBG
macro_line|#undef  BT_DBG
DECL|macro|BT_DBG
mdefine_line|#define BT_DBG(D...)
macro_line|#endif
DECL|macro|CAPI_INTEROPERABILITY
mdefine_line|#define CAPI_INTEROPERABILITY&t;&t;0x20
DECL|macro|CAPI_INTEROPERABILITY_REQ
mdefine_line|#define CAPI_INTEROPERABILITY_REQ&t;CAPICMD(CAPI_INTEROPERABILITY, CAPI_REQ)
DECL|macro|CAPI_INTEROPERABILITY_CONF
mdefine_line|#define CAPI_INTEROPERABILITY_CONF&t;CAPICMD(CAPI_INTEROPERABILITY, CAPI_CONF)
DECL|macro|CAPI_INTEROPERABILITY_IND
mdefine_line|#define CAPI_INTEROPERABILITY_IND&t;CAPICMD(CAPI_INTEROPERABILITY, CAPI_IND)
DECL|macro|CAPI_INTEROPERABILITY_RESP
mdefine_line|#define CAPI_INTEROPERABILITY_RESP&t;CAPICMD(CAPI_INTEROPERABILITY, CAPI_RESP)
DECL|macro|CAPI_INTEROPERABILITY_REQ_LEN
mdefine_line|#define CAPI_INTEROPERABILITY_REQ_LEN&t;(CAPI_MSG_BASELEN + 2)
DECL|macro|CAPI_INTEROPERABILITY_CONF_LEN
mdefine_line|#define CAPI_INTEROPERABILITY_CONF_LEN&t;(CAPI_MSG_BASELEN + 4)
DECL|macro|CAPI_INTEROPERABILITY_IND_LEN
mdefine_line|#define CAPI_INTEROPERABILITY_IND_LEN&t;(CAPI_MSG_BASELEN + 2)
DECL|macro|CAPI_INTEROPERABILITY_RESP_LEN
mdefine_line|#define CAPI_INTEROPERABILITY_RESP_LEN&t;(CAPI_MSG_BASELEN + 2)
DECL|macro|CAPI_FUNCTION_REGISTER
mdefine_line|#define CAPI_FUNCTION_REGISTER&t;&t;0
DECL|macro|CAPI_FUNCTION_RELEASE
mdefine_line|#define CAPI_FUNCTION_RELEASE&t;&t;1
DECL|macro|CAPI_FUNCTION_GET_PROFILE
mdefine_line|#define CAPI_FUNCTION_GET_PROFILE&t;2
DECL|macro|CAPI_FUNCTION_GET_MANUFACTURER
mdefine_line|#define CAPI_FUNCTION_GET_MANUFACTURER&t;3
DECL|macro|CAPI_FUNCTION_GET_VERSION
mdefine_line|#define CAPI_FUNCTION_GET_VERSION&t;4
DECL|macro|CAPI_FUNCTION_GET_SERIAL_NUMBER
mdefine_line|#define CAPI_FUNCTION_GET_SERIAL_NUMBER&t;5
DECL|macro|CAPI_FUNCTION_MANUFACTURER
mdefine_line|#define CAPI_FUNCTION_MANUFACTURER&t;6
DECL|macro|CAPI_FUNCTION_LOOPBACK
mdefine_line|#define CAPI_FUNCTION_LOOPBACK&t;&t;7
DECL|macro|CMTP_MSGNUM
mdefine_line|#define CMTP_MSGNUM&t;1
DECL|macro|CMTP_APPLID
mdefine_line|#define CMTP_APPLID&t;2
DECL|macro|CMTP_MAPPING
mdefine_line|#define CMTP_MAPPING&t;3
DECL|function|cmtp_application_add
r_static
r_struct
id|cmtp_application
op_star
id|cmtp_application_add
c_func
(paren
r_struct
id|cmtp_session
op_star
id|session
comma
id|__u16
id|appl
)paren
(brace
r_struct
id|cmtp_application
op_star
id|app
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|app
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;session %p application %p appl %d&quot;
comma
id|session
comma
id|app
comma
id|appl
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|app
)paren
r_return
l_int|NULL
suffix:semicolon
id|memset
c_func
(paren
id|app
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|app
)paren
)paren
suffix:semicolon
id|app-&gt;state
op_assign
id|BT_OPEN
suffix:semicolon
id|app-&gt;appl
op_assign
id|appl
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|app-&gt;list
comma
op_amp
id|session-&gt;applications
)paren
suffix:semicolon
r_return
id|app
suffix:semicolon
)brace
DECL|function|cmtp_application_del
r_static
r_void
id|cmtp_application_del
c_func
(paren
r_struct
id|cmtp_session
op_star
id|session
comma
r_struct
id|cmtp_application
op_star
id|app
)paren
(brace
id|BT_DBG
c_func
(paren
l_string|&quot;session %p application %p&quot;
comma
id|session
comma
id|app
)paren
suffix:semicolon
r_if
c_cond
(paren
id|app
)paren
(brace
id|list_del
c_func
(paren
op_amp
id|app-&gt;list
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|app
)paren
suffix:semicolon
)brace
)brace
DECL|function|cmtp_application_get
r_static
r_struct
id|cmtp_application
op_star
id|cmtp_application_get
c_func
(paren
r_struct
id|cmtp_session
op_star
id|session
comma
r_int
id|pattern
comma
id|__u16
id|value
)paren
(brace
r_struct
id|cmtp_application
op_star
id|app
suffix:semicolon
r_struct
id|list_head
op_star
id|p
comma
op_star
id|n
suffix:semicolon
id|list_for_each_safe
c_func
(paren
id|p
comma
id|n
comma
op_amp
id|session-&gt;applications
)paren
(brace
id|app
op_assign
id|list_entry
c_func
(paren
id|p
comma
r_struct
id|cmtp_application
comma
id|list
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|pattern
)paren
(brace
r_case
id|CMTP_MSGNUM
suffix:colon
r_if
c_cond
(paren
id|app-&gt;msgnum
op_eq
id|value
)paren
r_return
id|app
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CMTP_APPLID
suffix:colon
r_if
c_cond
(paren
id|app-&gt;appl
op_eq
id|value
)paren
r_return
id|app
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CMTP_MAPPING
suffix:colon
r_if
c_cond
(paren
id|app-&gt;mapping
op_eq
id|value
)paren
r_return
id|app
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|cmtp_msgnum_get
r_static
r_int
id|cmtp_msgnum_get
c_func
(paren
r_struct
id|cmtp_session
op_star
id|session
)paren
(brace
id|session-&gt;msgnum
op_increment
suffix:semicolon
r_if
c_cond
(paren
(paren
id|session-&gt;msgnum
op_amp
l_int|0xff
)paren
OG
l_int|200
)paren
id|session-&gt;msgnum
op_assign
id|CMTP_INITIAL_MSGNUM
op_plus
l_int|1
suffix:semicolon
r_return
id|session-&gt;msgnum
suffix:semicolon
)brace
DECL|function|cmtp_send_capimsg
r_static
r_void
id|cmtp_send_capimsg
c_func
(paren
r_struct
id|cmtp_session
op_star
id|session
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|cmtp_scb
op_star
id|scb
op_assign
(paren
r_void
op_star
)paren
id|skb-&gt;cb
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;session %p skb %p len %d&quot;
comma
id|session
comma
id|skb
comma
id|skb-&gt;len
)paren
suffix:semicolon
id|scb-&gt;id
op_assign
op_minus
l_int|1
suffix:semicolon
id|scb-&gt;data
op_assign
(paren
id|CAPIMSG_COMMAND
c_func
(paren
id|skb-&gt;data
)paren
op_eq
id|CAPI_DATA_B3
)paren
suffix:semicolon
id|skb_queue_tail
c_func
(paren
op_amp
id|session-&gt;transmit
comma
id|skb
)paren
suffix:semicolon
id|cmtp_schedule
c_func
(paren
id|session
)paren
suffix:semicolon
)brace
DECL|function|cmtp_send_interopmsg
r_static
r_void
id|cmtp_send_interopmsg
c_func
(paren
r_struct
id|cmtp_session
op_star
id|session
comma
id|__u8
id|subcmd
comma
id|__u16
id|appl
comma
id|__u16
id|msgnum
comma
id|__u16
id|function
comma
r_int
r_char
op_star
id|buf
comma
r_int
id|len
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_int
r_char
op_star
id|s
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;session %p subcmd 0x%02x appl %d msgnum %d&quot;
comma
id|session
comma
id|subcmd
comma
id|appl
comma
id|msgnum
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|skb
op_assign
id|alloc_skb
c_func
(paren
id|CAPI_MSG_BASELEN
op_plus
l_int|6
op_plus
id|len
comma
id|GFP_ATOMIC
)paren
)paren
)paren
(brace
id|BT_ERR
c_func
(paren
l_string|&quot;Can&squot;t allocate memory for interoperability packet&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|s
op_assign
id|skb_put
c_func
(paren
id|skb
comma
id|CAPI_MSG_BASELEN
op_plus
l_int|6
op_plus
id|len
)paren
suffix:semicolon
id|capimsg_setu16
c_func
(paren
id|s
comma
l_int|0
comma
id|CAPI_MSG_BASELEN
op_plus
l_int|6
op_plus
id|len
)paren
suffix:semicolon
id|capimsg_setu16
c_func
(paren
id|s
comma
l_int|2
comma
id|appl
)paren
suffix:semicolon
id|capimsg_setu8
(paren
id|s
comma
l_int|4
comma
id|CAPI_INTEROPERABILITY
)paren
suffix:semicolon
id|capimsg_setu8
(paren
id|s
comma
l_int|5
comma
id|subcmd
)paren
suffix:semicolon
id|capimsg_setu16
c_func
(paren
id|s
comma
l_int|6
comma
id|msgnum
)paren
suffix:semicolon
multiline_comment|/* Interoperability selector (Bluetooth Device Management) */
id|capimsg_setu16
c_func
(paren
id|s
comma
l_int|8
comma
l_int|0x0001
)paren
suffix:semicolon
id|capimsg_setu8
(paren
id|s
comma
l_int|10
comma
l_int|3
op_plus
id|len
)paren
suffix:semicolon
id|capimsg_setu16
c_func
(paren
id|s
comma
l_int|11
comma
id|function
)paren
suffix:semicolon
id|capimsg_setu8
(paren
id|s
comma
l_int|13
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
l_int|0
)paren
id|memcpy
c_func
(paren
id|s
op_plus
l_int|14
comma
id|buf
comma
id|len
)paren
suffix:semicolon
id|cmtp_send_capimsg
c_func
(paren
id|session
comma
id|skb
)paren
suffix:semicolon
)brace
DECL|function|cmtp_recv_interopmsg
r_static
r_void
id|cmtp_recv_interopmsg
c_func
(paren
r_struct
id|cmtp_session
op_star
id|session
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|capi_ctr
op_star
id|ctrl
op_assign
op_amp
id|session-&gt;ctrl
suffix:semicolon
r_struct
id|cmtp_application
op_star
id|application
suffix:semicolon
id|__u16
id|appl
comma
id|msgnum
comma
id|func
comma
id|info
suffix:semicolon
id|__u32
id|controller
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;session %p skb %p len %d&quot;
comma
id|session
comma
id|skb
comma
id|skb-&gt;len
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|CAPIMSG_SUBCOMMAND
c_func
(paren
id|skb-&gt;data
)paren
)paren
(brace
r_case
id|CAPI_CONF
suffix:colon
id|func
op_assign
id|CAPIMSG_U16
c_func
(paren
id|skb-&gt;data
comma
id|CAPI_MSG_BASELEN
op_plus
l_int|5
)paren
suffix:semicolon
id|info
op_assign
id|CAPIMSG_U16
c_func
(paren
id|skb-&gt;data
comma
id|CAPI_MSG_BASELEN
op_plus
l_int|8
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|func
)paren
(brace
r_case
id|CAPI_FUNCTION_REGISTER
suffix:colon
id|msgnum
op_assign
id|CAPIMSG_MSGID
c_func
(paren
id|skb-&gt;data
)paren
suffix:semicolon
id|application
op_assign
id|cmtp_application_get
c_func
(paren
id|session
comma
id|CMTP_MSGNUM
comma
id|msgnum
)paren
suffix:semicolon
r_if
c_cond
(paren
id|application
)paren
(brace
id|application-&gt;state
op_assign
id|BT_CONNECTED
suffix:semicolon
id|application-&gt;msgnum
op_assign
l_int|0
suffix:semicolon
id|application-&gt;mapping
op_assign
id|CAPIMSG_APPID
c_func
(paren
id|skb-&gt;data
)paren
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|session-&gt;wait
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|CAPI_FUNCTION_RELEASE
suffix:colon
id|appl
op_assign
id|CAPIMSG_APPID
c_func
(paren
id|skb-&gt;data
)paren
suffix:semicolon
id|application
op_assign
id|cmtp_application_get
c_func
(paren
id|session
comma
id|CMTP_MAPPING
comma
id|appl
)paren
suffix:semicolon
r_if
c_cond
(paren
id|application
)paren
(brace
id|application-&gt;state
op_assign
id|BT_CLOSED
suffix:semicolon
id|application-&gt;msgnum
op_assign
l_int|0
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|session-&gt;wait
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|CAPI_FUNCTION_GET_PROFILE
suffix:colon
id|controller
op_assign
id|CAPIMSG_U16
c_func
(paren
id|skb-&gt;data
comma
id|CAPI_MSG_BASELEN
op_plus
l_int|11
)paren
suffix:semicolon
id|msgnum
op_assign
id|CAPIMSG_MSGID
c_func
(paren
id|skb-&gt;data
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|info
op_logical_and
(paren
id|msgnum
op_eq
id|CMTP_INITIAL_MSGNUM
)paren
)paren
(brace
id|session-&gt;ncontroller
op_assign
id|controller
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|session-&gt;wait
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|info
op_logical_and
id|ctrl
)paren
(brace
id|memcpy
c_func
(paren
op_amp
id|ctrl-&gt;profile
comma
id|skb-&gt;data
op_plus
id|CAPI_MSG_BASELEN
op_plus
l_int|11
comma
r_sizeof
(paren
id|capi_profile
)paren
)paren
suffix:semicolon
id|session-&gt;state
op_assign
id|BT_CONNECTED
suffix:semicolon
id|capi_ctr_ready
c_func
(paren
id|ctrl
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|CAPI_FUNCTION_GET_MANUFACTURER
suffix:colon
id|controller
op_assign
id|CAPIMSG_U32
c_func
(paren
id|skb-&gt;data
comma
id|CAPI_MSG_BASELEN
op_plus
l_int|10
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|info
op_logical_and
id|ctrl
)paren
(brace
id|strncpy
c_func
(paren
id|ctrl-&gt;manu
comma
id|skb-&gt;data
op_plus
id|CAPI_MSG_BASELEN
op_plus
l_int|15
comma
id|skb-&gt;data
(braket
id|CAPI_MSG_BASELEN
op_plus
l_int|14
)braket
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|CAPI_FUNCTION_GET_VERSION
suffix:colon
id|controller
op_assign
id|CAPIMSG_U32
c_func
(paren
id|skb-&gt;data
comma
id|CAPI_MSG_BASELEN
op_plus
l_int|12
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|info
op_logical_and
id|ctrl
)paren
(brace
id|ctrl-&gt;version.majorversion
op_assign
id|CAPIMSG_U32
c_func
(paren
id|skb-&gt;data
comma
id|CAPI_MSG_BASELEN
op_plus
l_int|16
)paren
suffix:semicolon
id|ctrl-&gt;version.minorversion
op_assign
id|CAPIMSG_U32
c_func
(paren
id|skb-&gt;data
comma
id|CAPI_MSG_BASELEN
op_plus
l_int|20
)paren
suffix:semicolon
id|ctrl-&gt;version.majormanuversion
op_assign
id|CAPIMSG_U32
c_func
(paren
id|skb-&gt;data
comma
id|CAPI_MSG_BASELEN
op_plus
l_int|24
)paren
suffix:semicolon
id|ctrl-&gt;version.minormanuversion
op_assign
id|CAPIMSG_U32
c_func
(paren
id|skb-&gt;data
comma
id|CAPI_MSG_BASELEN
op_plus
l_int|28
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|CAPI_FUNCTION_GET_SERIAL_NUMBER
suffix:colon
id|controller
op_assign
id|CAPIMSG_U32
c_func
(paren
id|skb-&gt;data
comma
id|CAPI_MSG_BASELEN
op_plus
l_int|12
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|info
op_logical_and
id|ctrl
)paren
(brace
id|memset
c_func
(paren
id|ctrl-&gt;serial
comma
l_int|0
comma
id|CAPI_SERIAL_LEN
)paren
suffix:semicolon
id|strncpy
c_func
(paren
id|ctrl-&gt;serial
comma
id|skb-&gt;data
op_plus
id|CAPI_MSG_BASELEN
op_plus
l_int|17
comma
id|skb-&gt;data
(braket
id|CAPI_MSG_BASELEN
op_plus
l_int|16
)braket
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|CAPI_IND
suffix:colon
id|func
op_assign
id|CAPIMSG_U16
c_func
(paren
id|skb-&gt;data
comma
id|CAPI_MSG_BASELEN
op_plus
l_int|3
)paren
suffix:semicolon
r_if
c_cond
(paren
id|func
op_eq
id|CAPI_FUNCTION_LOOPBACK
)paren
(brace
id|appl
op_assign
id|CAPIMSG_APPID
c_func
(paren
id|skb-&gt;data
)paren
suffix:semicolon
id|msgnum
op_assign
id|CAPIMSG_MSGID
c_func
(paren
id|skb-&gt;data
)paren
suffix:semicolon
id|cmtp_send_interopmsg
c_func
(paren
id|session
comma
id|CAPI_RESP
comma
id|appl
comma
id|msgnum
comma
id|func
comma
id|skb-&gt;data
op_plus
id|CAPI_MSG_BASELEN
op_plus
l_int|6
comma
id|skb-&gt;data
(braket
id|CAPI_MSG_BASELEN
op_plus
l_int|5
)braket
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
DECL|function|cmtp_recv_capimsg
r_void
id|cmtp_recv_capimsg
c_func
(paren
r_struct
id|cmtp_session
op_star
id|session
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|capi_ctr
op_star
id|ctrl
op_assign
op_amp
id|session-&gt;ctrl
suffix:semicolon
r_struct
id|cmtp_application
op_star
id|application
suffix:semicolon
id|__u16
id|cmd
comma
id|appl
suffix:semicolon
id|__u32
id|contr
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;session %p skb %p len %d&quot;
comma
id|session
comma
id|skb
comma
id|skb-&gt;len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|CAPIMSG_COMMAND
c_func
(paren
id|skb-&gt;data
)paren
op_eq
id|CAPI_INTEROPERABILITY
)paren
(brace
id|cmtp_recv_interopmsg
c_func
(paren
id|session
comma
id|skb
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|session-&gt;flags
op_amp
(paren
l_int|1
op_lshift
id|CMTP_LOOPBACK
)paren
)paren
(brace
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|cmd
op_assign
id|CAPICMD
c_func
(paren
id|CAPIMSG_COMMAND
c_func
(paren
id|skb-&gt;data
)paren
comma
id|CAPIMSG_SUBCOMMAND
c_func
(paren
id|skb-&gt;data
)paren
)paren
suffix:semicolon
id|appl
op_assign
id|CAPIMSG_APPID
c_func
(paren
id|skb-&gt;data
)paren
suffix:semicolon
id|contr
op_assign
id|CAPIMSG_CONTROL
c_func
(paren
id|skb-&gt;data
)paren
suffix:semicolon
id|application
op_assign
id|cmtp_application_get
c_func
(paren
id|session
comma
id|CMTP_MAPPING
comma
id|appl
)paren
suffix:semicolon
r_if
c_cond
(paren
id|application
)paren
(brace
id|appl
op_assign
id|application-&gt;appl
suffix:semicolon
id|CAPIMSG_SETAPPID
c_func
(paren
id|skb-&gt;data
comma
id|appl
)paren
suffix:semicolon
)brace
r_else
(brace
id|BT_ERR
c_func
(paren
l_string|&quot;Can&squot;t find application with id %d&quot;
comma
id|appl
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|contr
op_amp
l_int|0x7f
)paren
op_eq
l_int|0x01
)paren
(brace
id|contr
op_assign
(paren
id|contr
op_amp
l_int|0xffffff80
)paren
op_or
id|session-&gt;num
suffix:semicolon
id|CAPIMSG_SETCONTROL
c_func
(paren
id|skb-&gt;data
comma
id|contr
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|ctrl
)paren
(brace
id|BT_ERR
c_func
(paren
l_string|&quot;Can&squot;t find controller %d for message&quot;
comma
id|session-&gt;num
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|capi_ctr_handle_message
c_func
(paren
id|ctrl
comma
id|appl
comma
id|skb
)paren
suffix:semicolon
)brace
DECL|function|cmtp_load_firmware
r_static
r_int
id|cmtp_load_firmware
c_func
(paren
r_struct
id|capi_ctr
op_star
id|ctrl
comma
id|capiloaddata
op_star
id|data
)paren
(brace
id|BT_DBG
c_func
(paren
l_string|&quot;ctrl %p data %p&quot;
comma
id|ctrl
comma
id|data
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cmtp_reset_ctr
r_static
r_void
id|cmtp_reset_ctr
c_func
(paren
r_struct
id|capi_ctr
op_star
id|ctrl
)paren
(brace
r_struct
id|cmtp_session
op_star
id|session
op_assign
id|ctrl-&gt;driverdata
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;ctrl %p&quot;
comma
id|ctrl
)paren
suffix:semicolon
id|capi_ctr_reseted
c_func
(paren
id|ctrl
)paren
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|session-&gt;terminate
)paren
suffix:semicolon
id|cmtp_schedule
c_func
(paren
id|session
)paren
suffix:semicolon
)brace
DECL|function|cmtp_register_appl
r_static
r_void
id|cmtp_register_appl
c_func
(paren
r_struct
id|capi_ctr
op_star
id|ctrl
comma
id|__u16
id|appl
comma
id|capi_register_params
op_star
id|rp
)paren
(brace
id|DECLARE_WAITQUEUE
c_func
(paren
id|wait
comma
id|current
)paren
suffix:semicolon
r_struct
id|cmtp_session
op_star
id|session
op_assign
id|ctrl-&gt;driverdata
suffix:semicolon
r_struct
id|cmtp_application
op_star
id|application
suffix:semicolon
r_int
r_int
id|timeo
op_assign
id|CMTP_INTEROP_TIMEOUT
suffix:semicolon
r_int
r_char
id|buf
(braket
l_int|8
)braket
suffix:semicolon
r_int
id|err
op_assign
l_int|0
comma
id|nconn
comma
id|want
op_assign
id|rp-&gt;level3cnt
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;ctrl %p appl %d level3cnt %d datablkcnt %d datablklen %d&quot;
comma
id|ctrl
comma
id|appl
comma
id|rp-&gt;level3cnt
comma
id|rp-&gt;datablkcnt
comma
id|rp-&gt;datablklen
)paren
suffix:semicolon
id|application
op_assign
id|cmtp_application_add
c_func
(paren
id|session
comma
id|appl
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|application
)paren
(brace
id|BT_ERR
c_func
(paren
l_string|&quot;Can&squot;t allocate memory for new application&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|want
OL
l_int|0
)paren
id|nconn
op_assign
id|ctrl-&gt;profile.nbchannel
op_star
op_minus
id|want
suffix:semicolon
r_else
id|nconn
op_assign
id|want
suffix:semicolon
r_if
c_cond
(paren
id|nconn
op_eq
l_int|0
)paren
id|nconn
op_assign
id|ctrl-&gt;profile.nbchannel
suffix:semicolon
id|capimsg_setu16
c_func
(paren
id|buf
comma
l_int|0
comma
id|nconn
)paren
suffix:semicolon
id|capimsg_setu16
c_func
(paren
id|buf
comma
l_int|2
comma
id|rp-&gt;datablkcnt
)paren
suffix:semicolon
id|capimsg_setu16
c_func
(paren
id|buf
comma
l_int|4
comma
id|rp-&gt;datablklen
)paren
suffix:semicolon
id|application-&gt;state
op_assign
id|BT_CONFIG
suffix:semicolon
id|application-&gt;msgnum
op_assign
id|cmtp_msgnum_get
c_func
(paren
id|session
)paren
suffix:semicolon
id|cmtp_send_interopmsg
c_func
(paren
id|session
comma
id|CAPI_REQ
comma
l_int|0x0000
comma
id|application-&gt;msgnum
comma
id|CAPI_FUNCTION_REGISTER
comma
id|buf
comma
l_int|6
)paren
suffix:semicolon
id|add_wait_queue
c_func
(paren
op_amp
id|session-&gt;wait
comma
op_amp
id|wait
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|timeo
)paren
(brace
id|err
op_assign
op_minus
id|EAGAIN
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|application-&gt;state
op_eq
id|BT_CLOSED
)paren
(brace
id|err
op_assign
op_minus
id|application-&gt;err
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|application-&gt;state
op_eq
id|BT_CONNECTED
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|signal_pending
c_func
(paren
id|current
)paren
)paren
(brace
id|err
op_assign
op_minus
id|EINTR
suffix:semicolon
r_break
suffix:semicolon
)brace
id|timeo
op_assign
id|schedule_timeout
c_func
(paren
id|timeo
)paren
suffix:semicolon
)brace
id|set_current_state
c_func
(paren
id|TASK_RUNNING
)paren
suffix:semicolon
id|remove_wait_queue
c_func
(paren
op_amp
id|session-&gt;wait
comma
op_amp
id|wait
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|cmtp_application_del
c_func
(paren
id|session
comma
id|application
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
DECL|function|cmtp_release_appl
r_static
r_void
id|cmtp_release_appl
c_func
(paren
r_struct
id|capi_ctr
op_star
id|ctrl
comma
id|__u16
id|appl
)paren
(brace
r_struct
id|cmtp_session
op_star
id|session
op_assign
id|ctrl-&gt;driverdata
suffix:semicolon
r_struct
id|cmtp_application
op_star
id|application
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;ctrl %p appl %d&quot;
comma
id|ctrl
comma
id|appl
)paren
suffix:semicolon
id|application
op_assign
id|cmtp_application_get
c_func
(paren
id|session
comma
id|CMTP_APPLID
comma
id|appl
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|application
)paren
(brace
id|BT_ERR
c_func
(paren
l_string|&quot;Can&squot;t find application&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|application-&gt;msgnum
op_assign
id|cmtp_msgnum_get
c_func
(paren
id|session
)paren
suffix:semicolon
id|cmtp_send_interopmsg
c_func
(paren
id|session
comma
id|CAPI_REQ
comma
id|application-&gt;mapping
comma
id|application-&gt;msgnum
comma
id|CAPI_FUNCTION_RELEASE
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
id|wait_event_interruptible_timeout
c_func
(paren
id|session-&gt;wait
comma
(paren
id|application-&gt;state
op_eq
id|BT_CLOSED
)paren
comma
id|CMTP_INTEROP_TIMEOUT
)paren
suffix:semicolon
id|cmtp_application_del
c_func
(paren
id|session
comma
id|application
)paren
suffix:semicolon
)brace
DECL|function|cmtp_send_message
r_static
id|u16
id|cmtp_send_message
c_func
(paren
r_struct
id|capi_ctr
op_star
id|ctrl
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|cmtp_session
op_star
id|session
op_assign
id|ctrl-&gt;driverdata
suffix:semicolon
r_struct
id|cmtp_application
op_star
id|application
suffix:semicolon
id|__u16
id|appl
suffix:semicolon
id|__u32
id|contr
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;ctrl %p skb %p&quot;
comma
id|ctrl
comma
id|skb
)paren
suffix:semicolon
id|appl
op_assign
id|CAPIMSG_APPID
c_func
(paren
id|skb-&gt;data
)paren
suffix:semicolon
id|contr
op_assign
id|CAPIMSG_CONTROL
c_func
(paren
id|skb-&gt;data
)paren
suffix:semicolon
id|application
op_assign
id|cmtp_application_get
c_func
(paren
id|session
comma
id|CMTP_APPLID
comma
id|appl
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
op_logical_neg
id|application
)paren
op_logical_or
(paren
id|application-&gt;state
op_ne
id|BT_CONNECTED
)paren
)paren
(brace
id|BT_ERR
c_func
(paren
l_string|&quot;Can&squot;t find application with id %d&quot;
comma
id|appl
)paren
suffix:semicolon
r_return
id|CAPI_ILLAPPNR
suffix:semicolon
)brace
id|CAPIMSG_SETAPPID
c_func
(paren
id|skb-&gt;data
comma
id|application-&gt;mapping
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|contr
op_amp
l_int|0x7f
)paren
op_eq
id|session-&gt;num
)paren
(brace
id|contr
op_assign
(paren
id|contr
op_amp
l_int|0xffffff80
)paren
op_or
l_int|0x01
suffix:semicolon
id|CAPIMSG_SETCONTROL
c_func
(paren
id|skb-&gt;data
comma
id|contr
)paren
suffix:semicolon
)brace
id|cmtp_send_capimsg
c_func
(paren
id|session
comma
id|skb
)paren
suffix:semicolon
r_return
id|CAPI_NOERROR
suffix:semicolon
)brace
DECL|function|cmtp_procinfo
r_static
r_char
op_star
id|cmtp_procinfo
c_func
(paren
r_struct
id|capi_ctr
op_star
id|ctrl
)paren
(brace
r_return
l_string|&quot;CAPI Message Transport Protocol&quot;
suffix:semicolon
)brace
DECL|function|cmtp_ctr_read_proc
r_static
r_int
id|cmtp_ctr_read_proc
c_func
(paren
r_char
op_star
id|page
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|off
comma
r_int
id|count
comma
r_int
op_star
id|eof
comma
r_struct
id|capi_ctr
op_star
id|ctrl
)paren
(brace
r_struct
id|cmtp_session
op_star
id|session
op_assign
id|ctrl-&gt;driverdata
suffix:semicolon
r_struct
id|cmtp_application
op_star
id|app
suffix:semicolon
r_struct
id|list_head
op_star
id|p
comma
op_star
id|n
suffix:semicolon
r_int
id|len
op_assign
l_int|0
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|page
op_plus
id|len
comma
l_string|&quot;%s&bslash;n&bslash;n&quot;
comma
id|cmtp_procinfo
c_func
(paren
id|ctrl
)paren
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|page
op_plus
id|len
comma
l_string|&quot;addr %s&bslash;n&quot;
comma
id|session-&gt;name
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|page
op_plus
id|len
comma
l_string|&quot;ctrl %d&bslash;n&quot;
comma
id|session-&gt;num
)paren
suffix:semicolon
id|list_for_each_safe
c_func
(paren
id|p
comma
id|n
comma
op_amp
id|session-&gt;applications
)paren
(brace
id|app
op_assign
id|list_entry
c_func
(paren
id|p
comma
r_struct
id|cmtp_application
comma
id|list
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|page
op_plus
id|len
comma
l_string|&quot;appl %d -&gt; %d&bslash;n&quot;
comma
id|app-&gt;appl
comma
id|app-&gt;mapping
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|off
op_plus
id|count
op_ge
id|len
)paren
op_star
id|eof
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
id|off
)paren
r_return
l_int|0
suffix:semicolon
op_star
id|start
op_assign
id|page
op_plus
id|off
suffix:semicolon
r_return
(paren
(paren
id|count
OL
id|len
op_minus
id|off
)paren
ques
c_cond
id|count
suffix:colon
id|len
op_minus
id|off
)paren
suffix:semicolon
)brace
DECL|function|cmtp_attach_device
r_int
id|cmtp_attach_device
c_func
(paren
r_struct
id|cmtp_session
op_star
id|session
)paren
(brace
r_int
r_char
id|buf
(braket
l_int|4
)braket
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;session %p&quot;
comma
id|session
)paren
suffix:semicolon
id|capimsg_setu32
c_func
(paren
id|buf
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
id|cmtp_send_interopmsg
c_func
(paren
id|session
comma
id|CAPI_REQ
comma
l_int|0xffff
comma
id|CMTP_INITIAL_MSGNUM
comma
id|CAPI_FUNCTION_GET_PROFILE
comma
id|buf
comma
l_int|4
)paren
suffix:semicolon
id|ret
op_assign
id|wait_event_interruptible_timeout
c_func
(paren
id|session-&gt;wait
comma
id|session-&gt;ncontroller
comma
id|CMTP_INTEROP_TIMEOUT
)paren
suffix:semicolon
id|BT_INFO
c_func
(paren
l_string|&quot;Found %d CAPI controller(s) on device %s&quot;
comma
id|session-&gt;ncontroller
comma
id|session-&gt;name
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
r_return
op_minus
id|ETIMEDOUT
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|session-&gt;ncontroller
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
id|session-&gt;ncontroller
OG
l_int|1
)paren
id|BT_INFO
c_func
(paren
l_string|&quot;Setting up only CAPI controller 1&quot;
)paren
suffix:semicolon
id|session-&gt;ctrl.owner
op_assign
id|THIS_MODULE
suffix:semicolon
id|session-&gt;ctrl.driverdata
op_assign
id|session
suffix:semicolon
id|strcpy
c_func
(paren
id|session-&gt;ctrl.name
comma
id|session-&gt;name
)paren
suffix:semicolon
id|session-&gt;ctrl.driver_name
op_assign
l_string|&quot;cmtp&quot;
suffix:semicolon
id|session-&gt;ctrl.load_firmware
op_assign
id|cmtp_load_firmware
suffix:semicolon
id|session-&gt;ctrl.reset_ctr
op_assign
id|cmtp_reset_ctr
suffix:semicolon
id|session-&gt;ctrl.register_appl
op_assign
id|cmtp_register_appl
suffix:semicolon
id|session-&gt;ctrl.release_appl
op_assign
id|cmtp_release_appl
suffix:semicolon
id|session-&gt;ctrl.send_message
op_assign
id|cmtp_send_message
suffix:semicolon
id|session-&gt;ctrl.procinfo
op_assign
id|cmtp_procinfo
suffix:semicolon
id|session-&gt;ctrl.ctr_read_proc
op_assign
id|cmtp_ctr_read_proc
suffix:semicolon
r_if
c_cond
(paren
id|attach_capi_ctr
c_func
(paren
op_amp
id|session-&gt;ctrl
)paren
OL
l_int|0
)paren
(brace
id|BT_ERR
c_func
(paren
l_string|&quot;Can&squot;t attach new controller&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|session-&gt;num
op_assign
id|session-&gt;ctrl.cnr
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;session %p num %d&quot;
comma
id|session
comma
id|session-&gt;num
)paren
suffix:semicolon
id|capimsg_setu32
c_func
(paren
id|buf
comma
l_int|0
comma
l_int|1
)paren
suffix:semicolon
id|cmtp_send_interopmsg
c_func
(paren
id|session
comma
id|CAPI_REQ
comma
l_int|0xffff
comma
id|cmtp_msgnum_get
c_func
(paren
id|session
)paren
comma
id|CAPI_FUNCTION_GET_MANUFACTURER
comma
id|buf
comma
l_int|4
)paren
suffix:semicolon
id|cmtp_send_interopmsg
c_func
(paren
id|session
comma
id|CAPI_REQ
comma
l_int|0xffff
comma
id|cmtp_msgnum_get
c_func
(paren
id|session
)paren
comma
id|CAPI_FUNCTION_GET_VERSION
comma
id|buf
comma
l_int|4
)paren
suffix:semicolon
id|cmtp_send_interopmsg
c_func
(paren
id|session
comma
id|CAPI_REQ
comma
l_int|0xffff
comma
id|cmtp_msgnum_get
c_func
(paren
id|session
)paren
comma
id|CAPI_FUNCTION_GET_SERIAL_NUMBER
comma
id|buf
comma
l_int|4
)paren
suffix:semicolon
id|cmtp_send_interopmsg
c_func
(paren
id|session
comma
id|CAPI_REQ
comma
l_int|0xffff
comma
id|cmtp_msgnum_get
c_func
(paren
id|session
)paren
comma
id|CAPI_FUNCTION_GET_PROFILE
comma
id|buf
comma
l_int|4
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cmtp_detach_device
r_void
id|cmtp_detach_device
c_func
(paren
r_struct
id|cmtp_session
op_star
id|session
)paren
(brace
id|BT_DBG
c_func
(paren
l_string|&quot;session %p&quot;
comma
id|session
)paren
suffix:semicolon
id|detach_capi_ctr
c_func
(paren
op_amp
id|session-&gt;ctrl
)paren
suffix:semicolon
)brace
eof
