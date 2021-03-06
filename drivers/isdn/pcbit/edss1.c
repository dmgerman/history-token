multiline_comment|/*&n; * DSS.1 Finite State Machine&n; * base: ITU-T Rec Q.931&n; *&n; * Copyright (C) 1996 Universidade de Lisboa&n; * &n; * Written by Pedro Roque Marques (roque@di.fc.ul.pt)&n; *&n; * This software may be used and distributed according to the terms of &n; * the GNU General Public License, incorporated herein by reference.&n; */
multiline_comment|/*&n; *        TODO: complete the FSM&n; *              move state/event descriptions to a user space logger&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/isdnif.h&gt;
macro_line|#include &quot;pcbit.h&quot;
macro_line|#include &quot;edss1.h&quot;
macro_line|#include &quot;layer2.h&quot;
macro_line|#include &quot;callbacks.h&quot;
r_extern
r_void
id|pcbit_state_change
c_func
(paren
r_struct
id|pcbit_dev
op_star
comma
r_struct
id|pcbit_chan
op_star
comma
r_int
r_int
id|i
comma
r_int
r_int
id|ev
comma
r_int
r_int
id|f
)paren
suffix:semicolon
r_extern
r_struct
id|pcbit_dev
op_star
id|dev_pcbit
(braket
id|MAX_PCBIT_CARDS
)braket
suffix:semicolon
DECL|variable|isdn_state_table
r_char
op_star
id|isdn_state_table
(braket
)braket
op_assign
(brace
l_string|&quot;Closed&quot;
comma
l_string|&quot;Call initiated&quot;
comma
l_string|&quot;Overlap sending&quot;
comma
l_string|&quot;Outgoing call proceeding&quot;
comma
l_string|&quot;NOT DEFINED&quot;
comma
l_string|&quot;Call delivered&quot;
comma
l_string|&quot;Call present&quot;
comma
l_string|&quot;Call received&quot;
comma
l_string|&quot;Connect request&quot;
comma
l_string|&quot;Incoming call proceeding&quot;
comma
l_string|&quot;Active&quot;
comma
l_string|&quot;Disconnect request&quot;
comma
l_string|&quot;Disconnect indication&quot;
comma
l_string|&quot;NOT DEFINED&quot;
comma
l_string|&quot;NOT DEFINED&quot;
comma
l_string|&quot;Suspend request&quot;
comma
l_string|&quot;NOT DEFINED&quot;
comma
l_string|&quot;Resume request&quot;
comma
l_string|&quot;NOT DEFINED&quot;
comma
l_string|&quot;Release Request&quot;
comma
l_string|&quot;NOT DEFINED&quot;
comma
l_string|&quot;NOT DEFINED&quot;
comma
l_string|&quot;NOT DEFINED&quot;
comma
l_string|&quot;NOT DEFINED&quot;
comma
l_string|&quot;NOT DEFINED&quot;
comma
l_string|&quot;Overlap receiving&quot;
comma
l_string|&quot;Select protocol on B-Channel&quot;
comma
l_string|&quot;Activate B-channel protocol&quot;
)brace
suffix:semicolon
macro_line|#ifdef DEBUG_ERRS
r_static
DECL|struct|CauseValue
r_struct
id|CauseValue
(brace
DECL|member|nr
id|byte
id|nr
suffix:semicolon
DECL|member|descr
r_char
op_star
id|descr
suffix:semicolon
DECL|variable|cvlist
)brace
id|cvlist
(braket
)braket
op_assign
initialization_block
suffix:semicolon
macro_line|#endif
DECL|struct|isdn_event_desc
r_static
r_struct
id|isdn_event_desc
(brace
DECL|member|ev
r_int
r_int
id|ev
suffix:semicolon
DECL|member|desc
r_char
op_star
id|desc
suffix:semicolon
DECL|variable|isdn_event_table
)brace
id|isdn_event_table
(braket
)braket
op_assign
(brace
(brace
id|EV_USR_SETUP_REQ
comma
l_string|&quot;CC-&gt;L3: Setup Request&quot;
)brace
comma
(brace
id|EV_USR_SETUP_RESP
comma
l_string|&quot;CC-&gt;L3: Setup Response&quot;
)brace
comma
(brace
id|EV_USR_PROCED_REQ
comma
l_string|&quot;CC-&gt;L3: Proceeding Request&quot;
)brace
comma
(brace
id|EV_USR_RELEASE_REQ
comma
l_string|&quot;CC-&gt;L3: Release Request&quot;
)brace
comma
(brace
id|EV_NET_SETUP
comma
l_string|&quot;NET-&gt;TE: setup &quot;
)brace
comma
(brace
id|EV_NET_CALL_PROC
comma
l_string|&quot;NET-&gt;TE: call proceeding&quot;
)brace
comma
(brace
id|EV_NET_SETUP_ACK
comma
l_string|&quot;NET-&gt;TE: setup acknowledge (more info needed)&quot;
)brace
comma
(brace
id|EV_NET_CONN
comma
l_string|&quot;NET-&gt;TE: connect&quot;
)brace
comma
(brace
id|EV_NET_CONN_ACK
comma
l_string|&quot;NET-&gt;TE: connect acknowledge&quot;
)brace
comma
(brace
id|EV_NET_DISC
comma
l_string|&quot;NET-&gt;TE: disconnect indication&quot;
)brace
comma
(brace
id|EV_NET_RELEASE
comma
l_string|&quot;NET-&gt;TE: release&quot;
)brace
comma
(brace
id|EV_NET_RELEASE_COMP
comma
l_string|&quot;NET-&gt;TE: release complete&quot;
)brace
comma
(brace
id|EV_NET_SELP_RESP
comma
l_string|&quot;Board: Select B-channel protocol ack&quot;
)brace
comma
(brace
id|EV_NET_ACTV_RESP
comma
l_string|&quot;Board: Activate B-channel protocol ack&quot;
)brace
comma
(brace
id|EV_TIMER
comma
l_string|&quot;Timeout&quot;
)brace
comma
(brace
l_int|0
comma
l_string|&quot;NULL&quot;
)brace
)brace
suffix:semicolon
DECL|function|strisdnevent
r_char
op_star
id|strisdnevent
c_func
(paren
id|ushort
id|ev
)paren
(brace
r_struct
id|isdn_event_desc
op_star
id|entry
suffix:semicolon
r_for
c_loop
(paren
id|entry
op_assign
id|isdn_event_table
suffix:semicolon
id|entry-&gt;ev
suffix:semicolon
id|entry
op_increment
)paren
r_if
c_cond
(paren
id|entry-&gt;ev
op_eq
id|ev
)paren
r_break
suffix:semicolon
r_return
id|entry-&gt;desc
suffix:semicolon
)brace
multiline_comment|/*&n; * Euro ISDN finite state machine&n; */
DECL|variable|fsm_timers
r_static
r_struct
id|fsm_timer_entry
id|fsm_timers
(braket
)braket
op_assign
(brace
(brace
id|ST_CALL_PROC
comma
l_int|10
)brace
comma
(brace
id|ST_DISC_REQ
comma
l_int|2
)brace
comma
(brace
id|ST_ACTIVE_SELP
comma
l_int|5
)brace
comma
(brace
id|ST_ACTIVE_ACTV
comma
l_int|5
)brace
comma
(brace
id|ST_INCM_PROC
comma
l_int|10
)brace
comma
(brace
id|ST_CONN_REQ
comma
l_int|2
)brace
comma
(brace
l_int|0xff
comma
l_int|0
)brace
)brace
suffix:semicolon
DECL|variable|fsm_table
r_static
r_struct
id|fsm_entry
id|fsm_table
(braket
)braket
op_assign
(brace
multiline_comment|/* Connect Phase */
multiline_comment|/* Outgoing */
(brace
id|ST_NULL
comma
id|ST_CALL_INIT
comma
id|EV_USR_SETUP_REQ
comma
id|cb_out_1
)brace
comma
(brace
id|ST_CALL_INIT
comma
id|ST_OVER_SEND
comma
id|EV_NET_SETUP_ACK
comma
id|cb_notdone
)brace
comma
(brace
id|ST_CALL_INIT
comma
id|ST_CALL_PROC
comma
id|EV_NET_CALL_PROC
comma
l_int|NULL
)brace
comma
(brace
id|ST_CALL_INIT
comma
id|ST_NULL
comma
id|EV_NET_DISC
comma
id|cb_out_2
)brace
comma
(brace
id|ST_CALL_PROC
comma
id|ST_ACTIVE_SELP
comma
id|EV_NET_CONN
comma
id|cb_out_2
)brace
comma
(brace
id|ST_CALL_PROC
comma
id|ST_NULL
comma
id|EV_NET_DISC
comma
id|cb_disc_1
)brace
comma
(brace
id|ST_CALL_PROC
comma
id|ST_DISC_REQ
comma
id|EV_USR_RELEASE_REQ
comma
id|cb_disc_2
)brace
comma
multiline_comment|/* Incoming */
(brace
id|ST_NULL
comma
id|ST_CALL_PRES
comma
id|EV_NET_SETUP
comma
l_int|NULL
)brace
comma
(brace
id|ST_CALL_PRES
comma
id|ST_INCM_PROC
comma
id|EV_USR_PROCED_REQ
comma
id|cb_in_1
)brace
comma
(brace
id|ST_CALL_PRES
comma
id|ST_DISC_REQ
comma
id|EV_USR_RELEASE_REQ
comma
id|cb_disc_2
)brace
comma
(brace
id|ST_INCM_PROC
comma
id|ST_CONN_REQ
comma
id|EV_USR_SETUP_RESP
comma
id|cb_in_2
)brace
comma
(brace
id|ST_INCM_PROC
comma
id|ST_DISC_REQ
comma
id|EV_USR_RELEASE_REQ
comma
id|cb_disc_2
)brace
comma
(brace
id|ST_CONN_REQ
comma
id|ST_ACTIVE_SELP
comma
id|EV_NET_CONN_ACK
comma
id|cb_in_3
)brace
comma
multiline_comment|/* Active */
(brace
id|ST_ACTIVE
comma
id|ST_NULL
comma
id|EV_NET_DISC
comma
id|cb_disc_1
)brace
comma
(brace
id|ST_ACTIVE
comma
id|ST_DISC_REQ
comma
id|EV_USR_RELEASE_REQ
comma
id|cb_disc_2
)brace
comma
(brace
id|ST_ACTIVE
comma
id|ST_NULL
comma
id|EV_NET_RELEASE
comma
id|cb_disc_3
)brace
comma
multiline_comment|/* Disconnect */
(brace
id|ST_DISC_REQ
comma
id|ST_NULL
comma
id|EV_NET_DISC
comma
id|cb_disc_1
)brace
comma
(brace
id|ST_DISC_REQ
comma
id|ST_NULL
comma
id|EV_NET_RELEASE
comma
id|cb_disc_3
)brace
comma
multiline_comment|/* protocol selection */
(brace
id|ST_ACTIVE_SELP
comma
id|ST_ACTIVE_ACTV
comma
id|EV_NET_SELP_RESP
comma
id|cb_selp_1
)brace
comma
(brace
id|ST_ACTIVE_SELP
comma
id|ST_DISC_REQ
comma
id|EV_USR_RELEASE_REQ
comma
id|cb_disc_2
)brace
comma
(brace
id|ST_ACTIVE_ACTV
comma
id|ST_ACTIVE
comma
id|EV_NET_ACTV_RESP
comma
id|cb_open
)brace
comma
(brace
id|ST_ACTIVE_ACTV
comma
id|ST_DISC_REQ
comma
id|EV_USR_RELEASE_REQ
comma
id|cb_disc_2
)brace
comma
multiline_comment|/* Timers */
(brace
id|ST_CALL_PROC
comma
id|ST_DISC_REQ
comma
id|EV_TIMER
comma
id|cb_disc_2
)brace
comma
(brace
id|ST_DISC_REQ
comma
id|ST_NULL
comma
id|EV_TIMER
comma
id|cb_disc_3
)brace
comma
(brace
id|ST_ACTIVE_SELP
comma
id|ST_DISC_REQ
comma
id|EV_TIMER
comma
id|cb_disc_2
)brace
comma
(brace
id|ST_ACTIVE_ACTV
comma
id|ST_DISC_REQ
comma
id|EV_TIMER
comma
id|cb_disc_2
)brace
comma
(brace
id|ST_INCM_PROC
comma
id|ST_DISC_REQ
comma
id|EV_TIMER
comma
id|cb_disc_2
)brace
comma
(brace
id|ST_CONN_REQ
comma
id|ST_CONN_REQ
comma
id|EV_TIMER
comma
id|cb_in_2
)brace
comma
(brace
l_int|0xff
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
)brace
)brace
suffix:semicolon
DECL|function|pcbit_fsm_timer
r_static
r_void
id|pcbit_fsm_timer
c_func
(paren
r_int
r_int
id|data
)paren
(brace
r_struct
id|pcbit_dev
op_star
id|dev
suffix:semicolon
r_struct
id|pcbit_chan
op_star
id|chan
suffix:semicolon
id|chan
op_assign
(paren
r_struct
id|pcbit_chan
op_star
)paren
id|data
suffix:semicolon
id|del_timer
c_func
(paren
op_amp
id|chan-&gt;fsm_timer
)paren
suffix:semicolon
id|chan-&gt;fsm_timer.function
op_assign
l_int|NULL
suffix:semicolon
id|dev
op_assign
id|chan2dev
c_func
(paren
id|chan
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;pcbit: timer for unknown device&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|pcbit_fsm_event
c_func
(paren
id|dev
comma
id|chan
comma
id|EV_TIMER
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|function|pcbit_fsm_event
r_void
id|pcbit_fsm_event
c_func
(paren
r_struct
id|pcbit_dev
op_star
id|dev
comma
r_struct
id|pcbit_chan
op_star
id|chan
comma
r_int
r_int
id|event
comma
r_struct
id|callb_data
op_star
id|data
)paren
(brace
r_struct
id|fsm_entry
op_star
id|action
suffix:semicolon
r_struct
id|fsm_timer_entry
op_star
id|tentry
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|dev-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_for
c_loop
(paren
id|action
op_assign
id|fsm_table
suffix:semicolon
id|action-&gt;init
op_ne
l_int|0xff
suffix:semicolon
id|action
op_increment
)paren
r_if
c_cond
(paren
id|action-&gt;init
op_eq
id|chan-&gt;fsm_state
op_logical_and
id|action-&gt;event
op_eq
id|event
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|action-&gt;init
op_eq
l_int|0xff
)paren
(brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|dev-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;fsm error: event %x on state %x&bslash;n&quot;
comma
id|event
comma
id|chan-&gt;fsm_state
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|chan-&gt;fsm_timer.function
)paren
(brace
id|del_timer
c_func
(paren
op_amp
id|chan-&gt;fsm_timer
)paren
suffix:semicolon
id|chan-&gt;fsm_timer.function
op_assign
l_int|NULL
suffix:semicolon
)brace
id|chan-&gt;fsm_state
op_assign
id|action-&gt;final
suffix:semicolon
id|pcbit_state_change
c_func
(paren
id|dev
comma
id|chan
comma
id|action-&gt;init
comma
id|event
comma
id|action-&gt;final
)paren
suffix:semicolon
r_for
c_loop
(paren
id|tentry
op_assign
id|fsm_timers
suffix:semicolon
id|tentry-&gt;init
op_ne
l_int|0xff
suffix:semicolon
id|tentry
op_increment
)paren
r_if
c_cond
(paren
id|tentry-&gt;init
op_eq
id|chan-&gt;fsm_state
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|tentry-&gt;init
op_ne
l_int|0xff
)paren
(brace
id|init_timer
c_func
(paren
op_amp
id|chan-&gt;fsm_timer
)paren
suffix:semicolon
id|chan-&gt;fsm_timer.function
op_assign
op_amp
id|pcbit_fsm_timer
suffix:semicolon
id|chan-&gt;fsm_timer.data
op_assign
(paren
id|ulong
)paren
id|chan
suffix:semicolon
id|chan-&gt;fsm_timer.expires
op_assign
id|jiffies
op_plus
id|tentry-&gt;timeout
op_star
id|HZ
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|chan-&gt;fsm_timer
)paren
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|dev-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|action-&gt;callb
)paren
id|action
op_member_access_from_pointer
id|callb
c_func
(paren
id|dev
comma
id|chan
comma
id|data
)paren
suffix:semicolon
)brace
eof
