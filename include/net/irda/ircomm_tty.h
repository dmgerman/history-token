multiline_comment|/*********************************************************************&n; *                &n; * Filename:      ircomm_tty.h&n; * Version:       &n; * Description:   &n; * Status:        Experimental.&n; * Author:        Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * Created at:    Sun Jun  6 23:24:22 1999&n; * Modified at:   Fri Jan 28 13:16:57 2000&n; * Modified by:   Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * &n; *     Copyright (c) 1999-2000 Dag Brattli, All Rights Reserved.&n; *     &n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version.&n; * &n; *     This program is distributed in the hope that it will be useful,&n; *     but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the&n; *     GNU General Public License for more details.&n; * &n; *     You should have received a copy of the GNU General Public License &n; *     along with this program; if not, write to the Free Software &n; *     Foundation, Inc., 59 Temple Place, Suite 330, Boston, &n; *     MA 02111-1307 USA&n; *     &n; ********************************************************************/
macro_line|#ifndef IRCOMM_TTY_H
DECL|macro|IRCOMM_TTY_H
mdefine_line|#define IRCOMM_TTY_H
macro_line|#include &lt;linux/serial.h&gt;
macro_line|#include &lt;linux/termios.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;net/irda/irias_object.h&gt;
macro_line|#include &lt;net/irda/ircomm_core.h&gt;
macro_line|#include &lt;net/irda/ircomm_param.h&gt;
DECL|macro|IRCOMM_TTY_PORTS
mdefine_line|#define IRCOMM_TTY_PORTS 32
DECL|macro|IRCOMM_TTY_MAGIC
mdefine_line|#define IRCOMM_TTY_MAGIC 0x3432
DECL|macro|IRCOMM_TTY_MAJOR
mdefine_line|#define IRCOMM_TTY_MAJOR 161
DECL|macro|IRCOMM_TTY_MINOR
mdefine_line|#define IRCOMM_TTY_MINOR 0
multiline_comment|/* This is used as an initial value to max_header_size before the proper&n; * value is filled in (5 for ttp, 4 for lmp). This allow us to detect&n; * the state of the underlying connection. - Jean II */
DECL|macro|IRCOMM_TTY_HDR_UNITIALISED
mdefine_line|#define IRCOMM_TTY_HDR_UNITIALISED&t;32
multiline_comment|/*&n; * IrCOMM TTY driver state&n; */
DECL|struct|ircomm_tty_cb
r_struct
id|ircomm_tty_cb
(brace
DECL|member|queue
id|irda_queue_t
id|queue
suffix:semicolon
multiline_comment|/* Must be first */
DECL|member|magic
id|magic_t
id|magic
suffix:semicolon
DECL|member|state
r_int
id|state
suffix:semicolon
multiline_comment|/* Connect state */
DECL|member|tty
r_struct
id|tty_struct
op_star
id|tty
suffix:semicolon
DECL|member|ircomm
r_struct
id|ircomm_cb
op_star
id|ircomm
suffix:semicolon
multiline_comment|/* IrCOMM layer instance */
DECL|member|tx_skb
r_struct
id|sk_buff
op_star
id|tx_skb
suffix:semicolon
multiline_comment|/* Transmit buffer */
DECL|member|ctrl_skb
r_struct
id|sk_buff
op_star
id|ctrl_skb
suffix:semicolon
multiline_comment|/* Control data buffer */
multiline_comment|/* Parameters */
DECL|member|settings
r_struct
id|ircomm_params
id|settings
suffix:semicolon
DECL|member|service_type
id|__u8
id|service_type
suffix:semicolon
multiline_comment|/* The service that we support */
DECL|member|client
r_int
id|client
suffix:semicolon
multiline_comment|/* True if we are a client */
DECL|member|flow
id|LOCAL_FLOW
id|flow
suffix:semicolon
multiline_comment|/* IrTTP flow status */
DECL|member|line
r_int
id|line
suffix:semicolon
DECL|member|flags
id|__u32
id|flags
suffix:semicolon
DECL|member|dlsap_sel
id|__u8
id|dlsap_sel
suffix:semicolon
DECL|member|slsap_sel
id|__u8
id|slsap_sel
suffix:semicolon
DECL|member|saddr
id|__u32
id|saddr
suffix:semicolon
DECL|member|daddr
id|__u32
id|daddr
suffix:semicolon
DECL|member|max_data_size
id|__u32
id|max_data_size
suffix:semicolon
multiline_comment|/* Max data we can transmit in one packet */
DECL|member|max_header_size
id|__u32
id|max_header_size
suffix:semicolon
multiline_comment|/* The amount of header space we must reserve */
DECL|member|iriap
r_struct
id|iriap_cb
op_star
id|iriap
suffix:semicolon
multiline_comment|/* Instance used for querying remote IAS */
DECL|member|obj
r_struct
id|ias_object
op_star
id|obj
suffix:semicolon
DECL|member|skey
r_int
id|skey
suffix:semicolon
DECL|member|ckey
r_int
id|ckey
suffix:semicolon
DECL|member|normal_termios
r_struct
id|termios
id|normal_termios
suffix:semicolon
DECL|member|callout_termios
r_struct
id|termios
id|callout_termios
suffix:semicolon
DECL|member|open_wait
id|wait_queue_head_t
id|open_wait
suffix:semicolon
DECL|member|close_wait
id|wait_queue_head_t
id|close_wait
suffix:semicolon
DECL|member|watchdog_timer
r_struct
id|timer_list
id|watchdog_timer
suffix:semicolon
DECL|member|tqueue
r_struct
id|tq_struct
id|tqueue
suffix:semicolon
DECL|member|close_delay
r_int
r_int
id|close_delay
suffix:semicolon
DECL|member|closing_wait
r_int
r_int
id|closing_wait
suffix:semicolon
multiline_comment|/* time to wait before closing */
DECL|member|session
r_int
id|session
suffix:semicolon
multiline_comment|/* Session of opening process */
DECL|member|pgrp
r_int
id|pgrp
suffix:semicolon
multiline_comment|/* pgrp of opening process */
DECL|member|open_count
r_int
id|open_count
suffix:semicolon
DECL|member|blocked_open
r_int
id|blocked_open
suffix:semicolon
multiline_comment|/* # of blocked opens */
)brace
suffix:semicolon
r_void
id|ircomm_tty_start
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
suffix:semicolon
r_void
id|ircomm_tty_stop
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
suffix:semicolon
r_void
id|ircomm_tty_check_modem_status
c_func
(paren
r_struct
id|ircomm_tty_cb
op_star
id|self
)paren
suffix:semicolon
r_extern
r_void
id|ircomm_tty_change_speed
c_func
(paren
r_struct
id|ircomm_tty_cb
op_star
id|self
)paren
suffix:semicolon
r_extern
r_int
id|ircomm_tty_ioctl
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_struct
id|file
op_star
id|file
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
r_extern
r_void
id|ircomm_tty_set_termios
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_struct
id|termios
op_star
id|old_termios
)paren
suffix:semicolon
r_extern
id|hashbin_t
op_star
id|ircomm_tty
suffix:semicolon
macro_line|#endif
eof
