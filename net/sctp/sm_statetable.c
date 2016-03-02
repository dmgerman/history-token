multiline_comment|/* SCTP kernel reference Implementation&n; * Copyright (c) 1999-2000 Cisco, Inc.&n; * Copyright (c) 1999-2001 Motorola, Inc.&n; * Copyright (c) 2001 International Business Machines, Corp.&n; * Copyright (c) 2001 Intel Corp.&n; * Copyright (c) 2001 Nokia, Inc.&n; *&n; * This file is part of the SCTP kernel reference Implementation&n; *&n; * These are the state tables for the SCTP state machine.&n; *&n; * The SCTP reference implementation is free software;&n; * you can redistribute it and/or modify it under the terms of&n; * the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; *&n; * The SCTP reference implementation is distributed in the hope that it&n; * will be useful, but WITHOUT ANY WARRANTY; without even the implied&n; *                 ************************&n; * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; * See the GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with GNU CC; see the file COPYING.  If not, write to&n; * the Free Software Foundation, 59 Temple Place - Suite 330,&n; * Boston, MA 02111-1307, USA.&n; *&n; * Please send any bug reports or fixes you make to the&n; * email address(es):&n; *    lksctp developers &lt;lksctp-developers@lists.sourceforge.net&gt;&n; *&n; * Or submit a bug report through the following website:&n; *    http://www.sf.net/projects/lksctp&n; *&n; * Written or modified by:&n; *    La Monte H.P. Yarroll &lt;piggy@acm.org&gt;&n; *    Karl Knutson          &lt;karl@athena.chicago.il.us&gt;&n; *    Jon Grimm             &lt;jgrimm@us.ibm.com&gt;&n; *    Hui Huang&t;&t;    &lt;hui.huang@nokia.com&gt;&n; *    Daisy Chang&t;    &lt;daisyc@us.ibm.com&gt;&n; *&n; * Any bugs reported given to us we will try to fix... any fixes shared will&n; * be incorporated into the next SCTP release.&n; */
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;net/sctp/sctp.h&gt;
macro_line|#include &lt;net/sctp/sm.h&gt;
DECL|variable|bug
id|sctp_sm_table_entry_t
id|bug
op_assign
(brace
dot
id|fn
op_assign
id|sctp_sf_bug
comma
dot
id|name
op_assign
l_string|&quot;sctp_sf_bug&quot;
)brace
suffix:semicolon
DECL|macro|DO_LOOKUP
mdefine_line|#define DO_LOOKUP(_max, _type, _table) &bslash;&n;&t;if ((event_subtype._type &gt; (_max))) { &bslash;&n;&t;&t;printk(KERN_WARNING &bslash;&n;&t;&t;       &quot;sctp table %p possible attack:&quot; &bslash;&n;&t;&t;       &quot; event %d exceeds max %d&bslash;n&quot;, &bslash;&n;&t;&t;       _table, event_subtype._type, _max); &bslash;&n;&t;&t;return &amp;bug; &bslash;&n;&t;} &bslash;&n;&t;return &amp;_table[event_subtype._type][(int)state];
DECL|function|sctp_sm_lookup_event
id|sctp_sm_table_entry_t
op_star
id|sctp_sm_lookup_event
c_func
(paren
id|sctp_event_t
id|event_type
comma
id|sctp_state_t
id|state
comma
id|sctp_subtype_t
id|event_subtype
)paren
(brace
r_switch
c_cond
(paren
id|event_type
)paren
(brace
r_case
id|SCTP_EVENT_T_CHUNK
suffix:colon
r_return
id|sctp_chunk_event_lookup
c_func
(paren
id|event_subtype.chunk
comma
id|state
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SCTP_EVENT_T_TIMEOUT
suffix:colon
id|DO_LOOKUP
c_func
(paren
id|SCTP_EVENT_TIMEOUT_MAX
comma
id|timeout
comma
id|timeout_event_table
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SCTP_EVENT_T_OTHER
suffix:colon
id|DO_LOOKUP
c_func
(paren
id|SCTP_EVENT_OTHER_MAX
comma
id|other
comma
id|other_event_table
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SCTP_EVENT_T_PRIMITIVE
suffix:colon
id|DO_LOOKUP
c_func
(paren
id|SCTP_EVENT_PRIMITIVE_MAX
comma
id|primitive
comma
id|primitive_event_table
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* Yikes!  We got an illegal event type.  */
r_return
op_amp
id|bug
suffix:semicolon
)brace
suffix:semicolon
)brace
DECL|macro|TYPE_SCTP_DATA
mdefine_line|#define TYPE_SCTP_DATA { &bslash;&n;&t;/* SCTP_STATE_EMPTY */ &bslash;&n;&t;{.fn = sctp_sf_ootb, .name = &quot;sctp_sf_ootb&quot;}, &bslash;&n;&t;/* SCTP_STATE_CLOSED */ &bslash;&n;&t;{.fn = sctp_sf_tabort_8_4_8, .name = &quot;sctp_sf_tabort_8_4_8&quot;}, &bslash;&n;&t;/* SCTP_STATE_COOKIE_WAIT */ &bslash;&n;&t;{.fn = sctp_sf_discard_chunk, .name = &quot;sctp_sf_discard_chunk&quot;}, &bslash;&n;&t;/* SCTP_STATE_COOKIE_ECHOED */ &bslash;&n;&t;{.fn = sctp_sf_discard_chunk, .name = &quot;sctp_sf_discard_chunk&quot;}, &bslash;&n;&t;/* SCTP_STATE_ESTABLISHED */ &bslash;&n;&t;{.fn = sctp_sf_eat_data_6_2, .name = &quot;sctp_sf_eat_data_6_2&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_PENDING */ &bslash;&n;&t;{.fn = sctp_sf_eat_data_6_2, .name = &quot;sctp_sf_eat_data_6_2&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_SENT */ &bslash;&n;&t;{.fn = sctp_sf_eat_data_fast_4_4, .name = &quot;sctp_sf_eat_data_fast_4_4&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_RECEIVED */ &bslash;&n;&t;{.fn = sctp_sf_discard_chunk, .name = &quot;sctp_sf_discard_chunk&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_ACK_SENT */ &bslash;&n;&t;{.fn = sctp_sf_discard_chunk, .name = &quot;sctp_sf_discard_chunk&quot;}, &bslash;&n;} /* TYPE_SCTP_DATA */
DECL|macro|TYPE_SCTP_INIT
mdefine_line|#define TYPE_SCTP_INIT { &bslash;&n;&t;/* SCTP_STATE_EMPTY */ &bslash;&n;&t;{.fn = sctp_sf_bug, .name = &quot;sctp_sf_bug&quot;}, &bslash;&n;&t;/* SCTP_STATE_CLOSED */ &bslash;&n;&t;{.fn = sctp_sf_do_5_1B_init, .name = &quot;sctp_sf_do_5_1B_init&quot;}, &bslash;&n;&t;/* SCTP_STATE_COOKIE_WAIT */ &bslash;&n;&t;{.fn = sctp_sf_do_5_2_1_siminit, .name = &quot;sctp_sf_do_5_2_1_siminit&quot;}, &bslash;&n;&t;/* SCTP_STATE_COOKIE_ECHOED */ &bslash;&n;&t;{.fn = sctp_sf_do_5_2_1_siminit, .name = &quot;sctp_sf_do_5_2_1_siminit&quot;}, &bslash;&n;&t;/* SCTP_STATE_ESTABLISHED */ &bslash;&n;&t;{.fn = sctp_sf_do_5_2_2_dupinit, .name = &quot;sctp_sf_do_5_2_2_dupinit&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_PENDING */ &bslash;&n;&t;{.fn = sctp_sf_do_5_2_2_dupinit, .name = &quot;sctp_sf_do_5_2_2_dupinit&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_SENT */ &bslash;&n;&t;{.fn = sctp_sf_do_5_2_2_dupinit, .name = &quot;sctp_sf_do_5_2_2_dupinit&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_RECEIVED */ &bslash;&n;&t;{.fn = sctp_sf_do_5_2_2_dupinit, .name = &quot;sctp_sf_do_5_2_2_dupinit&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_ACK_SENT */ &bslash;&n;&t;{.fn = sctp_sf_do_9_2_reshutack, .name = &quot;sctp_sf_do_9_2_reshutack&quot;}, &bslash;&n;} /* TYPE_SCTP_INIT */
DECL|macro|TYPE_SCTP_INIT_ACK
mdefine_line|#define TYPE_SCTP_INIT_ACK { &bslash;&n;&t;/* SCTP_STATE_EMPTY */ &bslash;&n;&t;{.fn = sctp_sf_ootb, .name = &quot;sctp_sf_ootb&quot;}, &bslash;&n;&t;/* SCTP_STATE_CLOSED */ &bslash;&n;&t;{.fn = sctp_sf_discard_chunk, .name = &quot;sctp_sf_discard_chunk&quot;}, &bslash;&n;&t;/* SCTP_STATE_COOKIE_WAIT */ &bslash;&n;&t;{.fn = sctp_sf_do_5_1C_ack, .name = &quot;sctp_sf_do_5_1C_ack&quot;}, &bslash;&n;&t;/* SCTP_STATE_COOKIE_ECHOED */ &bslash;&n;&t;{.fn = sctp_sf_discard_chunk, .name = &quot;sctp_sf_discard_chunk&quot;}, &bslash;&n;&t;/* SCTP_STATE_ESTABLISHED */ &bslash;&n;&t;{.fn = sctp_sf_discard_chunk, .name = &quot;sctp_sf_discard_chunk&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_PENDING */ &bslash;&n;&t;{.fn = sctp_sf_discard_chunk, .name = &quot;sctp_sf_discard_chunk&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_SENT */ &bslash;&n;&t;{.fn = sctp_sf_discard_chunk, .name = &quot;sctp_sf_discard_chunk&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_RECEIVED */ &bslash;&n;&t;{.fn = sctp_sf_discard_chunk, .name = &quot;sctp_sf_discard_chunk&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_ACK_SENT */ &bslash;&n;&t;{.fn = sctp_sf_discard_chunk, .name = &quot;sctp_sf_discard_chunk&quot;}, &bslash;&n;} /* TYPE_SCTP_INIT_ACK */
DECL|macro|TYPE_SCTP_SACK
mdefine_line|#define TYPE_SCTP_SACK { &bslash;&n;&t;/*  SCTP_STATE_EMPTY */ &bslash;&n;&t;{.fn = sctp_sf_ootb, .name = &quot;sctp_sf_ootb&quot;}, &bslash;&n;&t;/* SCTP_STATE_CLOSED */ &bslash;&n;&t;{.fn = sctp_sf_tabort_8_4_8, .name = &quot;sctp_sf_tabort_8_4_8&quot;}, &bslash;&n;&t;/* SCTP_STATE_COOKIE_WAIT */ &bslash;&n;&t;{.fn = sctp_sf_discard_chunk, .name = &quot;sctp_sf_discard_chunk&quot;}, &bslash;&n;&t;/* SCTP_STATE_COOKIE_ECHOED */ &bslash;&n;&t;{.fn = sctp_sf_eat_sack_6_2, .name = &quot;sctp_sf_eat_sack_6_2&quot;}, &bslash;&n;&t;/* SCTP_STATE_ESTABLISHED */ &bslash;&n;&t;{.fn = sctp_sf_eat_sack_6_2, .name = &quot;sctp_sf_eat_sack_6_2&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_PENDING */ &bslash;&n;&t;{.fn = sctp_sf_eat_sack_6_2, .name = &quot;sctp_sf_eat_sack_6_2&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_SENT */ &bslash;&n;&t;{.fn = sctp_sf_discard_chunk, .name = &quot;sctp_sf_discard_chunk&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_RECEIVED */ &bslash;&n;&t;{.fn = sctp_sf_eat_sack_6_2, .name = &quot;sctp_sf_eat_sack_6_2&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_ACK_SENT */ &bslash;&n;&t;{.fn = sctp_sf_discard_chunk, .name = &quot;sctp_sf_discard_chunk&quot;}, &bslash;&n;} /* TYPE_SCTP_SACK */
DECL|macro|TYPE_SCTP_HEARTBEAT
mdefine_line|#define TYPE_SCTP_HEARTBEAT { &bslash;&n;&t;/*  SCTP_STATE_EMPTY */ &bslash;&n;&t;{.fn = sctp_sf_ootb, .name = &quot;sctp_sf_ootb&quot;}, &bslash;&n;&t;/* SCTP_STATE_CLOSED */ &bslash;&n;&t;{.fn = sctp_sf_tabort_8_4_8, .name = &quot;sctp_sf_tabort_8_4_8&quot;}, &bslash;&n;&t;/* SCTP_STATE_COOKIE_WAIT */ &bslash;&n;&t;{.fn = sctp_sf_discard_chunk, .name = &quot;sctp_sf_discard_chunk&quot;}, &bslash;&n;&t;/* SCTP_STATE_COOKIE_ECHOED */ &bslash;&n;&t;{.fn = sctp_sf_beat_8_3, .name = &quot;sctp_sf_beat_8_3&quot;}, &bslash;&n;&t;/* SCTP_STATE_ESTABLISHED */ &bslash;&n;&t;{.fn = sctp_sf_beat_8_3, .name = &quot;sctp_sf_beat_8_3&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_PENDING */ &bslash;&n;&t;{.fn = sctp_sf_beat_8_3, .name = &quot;sctp_sf_beat_8_3&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_SENT */ &bslash;&n;&t;{.fn = sctp_sf_beat_8_3, .name = &quot;sctp_sf_beat_8_3&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_RECEIVED */ &bslash;&n;&t;{.fn = sctp_sf_beat_8_3, .name = &quot;sctp_sf_beat_8_3&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_ACK_SENT */ &bslash;&n;&t;/* This should not happen, but we are nice.  */ &bslash;&n;&t;{.fn = sctp_sf_beat_8_3, .name = &quot;sctp_sf_beat_8_3&quot;}, &bslash;&n;} /* TYPE_SCTP_HEARTBEAT */
DECL|macro|TYPE_SCTP_HEARTBEAT_ACK
mdefine_line|#define TYPE_SCTP_HEARTBEAT_ACK { &bslash;&n;&t;/*  SCTP_STATE_EMPTY */ &bslash;&n;&t;{.fn = sctp_sf_ootb, .name = &quot;sctp_sf_ootb&quot;}, &bslash;&n;&t;/* SCTP_STATE_CLOSED */ &bslash;&n;&t;{.fn = sctp_sf_tabort_8_4_8, .name = &quot;sctp_sf_tabort_8_4_8&quot;}, &bslash;&n;&t;/* SCTP_STATE_COOKIE_WAIT */ &bslash;&n;&t;{.fn = sctp_sf_violation, .name = &quot;sctp_sf_violation&quot;}, &bslash;&n;&t;/* SCTP_STATE_COOKIE_ECHOED */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_ESTABLISHED */ &bslash;&n;&t;{.fn = sctp_sf_backbeat_8_3, .name = &quot;sctp_sf_backbeat_8_3&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_PENDING */ &bslash;&n;&t;{.fn = sctp_sf_backbeat_8_3, .name = &quot;sctp_sf_backbeat_8_3&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_SENT */ &bslash;&n;&t;{.fn = sctp_sf_backbeat_8_3, .name = &quot;sctp_sf_backbeat_8_3&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_RECEIVED */ &bslash;&n;&t;{.fn = sctp_sf_backbeat_8_3, .name = &quot;sctp_sf_backbeat_8_3&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_ACK_SENT */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;} /* TYPE_SCTP_HEARTBEAT_ACK */
DECL|macro|TYPE_SCTP_ABORT
mdefine_line|#define TYPE_SCTP_ABORT { &bslash;&n;&t;/* SCTP_STATE_EMPTY */ &bslash;&n;&t;{.fn = sctp_sf_ootb, .name = &quot;sctp_sf_ootb&quot;}, &bslash;&n;&t;/* SCTP_STATE_CLOSED */ &bslash;&n;&t;{.fn = sctp_sf_pdiscard, .name = &quot;sctp_sf_pdiscard&quot;}, &bslash;&n;&t;/* SCTP_STATE_COOKIE_WAIT */ &bslash;&n;&t;{.fn = sctp_sf_cookie_wait_abort, .name = &quot;sctp_sf_cookie_wait_abort&quot;}, &bslash;&n;&t;/* SCTP_STATE_COOKIE_ECHOED */ &bslash;&n;&t;{.fn = sctp_sf_cookie_echoed_abort, &bslash;&n;&t; .name = &quot;sctp_sf_cookie_echoed_abort&quot;}, &bslash;&n;&t;/* SCTP_STATE_ESTABLISHED */ &bslash;&n;&t;{.fn = sctp_sf_do_9_1_abort, .name = &quot;sctp_sf_do_9_1_abort&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_PENDING */ &bslash;&n;&t;{.fn = sctp_sf_shutdown_pending_abort, &bslash;&n;&t;.name = &quot;sctp_sf_shutdown_pending_abort&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_SENT */ &bslash;&n;&t;{.fn = sctp_sf_shutdown_sent_abort, &bslash;&n;&t;.name = &quot;sctp_sf_shutdown_sent_abort&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_RECEIVED */ &bslash;&n;&t;{.fn = sctp_sf_do_9_1_abort, .name = &quot;sctp_sf_do_9_1_abort&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_ACK_SENT */ &bslash;&n;&t;{.fn = sctp_sf_shutdown_ack_sent_abort, &bslash;&n;&t;.name = &quot;sctp_sf_shutdown_ack_sent_abort&quot;}, &bslash;&n;} /* TYPE_SCTP_ABORT */
DECL|macro|TYPE_SCTP_SHUTDOWN
mdefine_line|#define TYPE_SCTP_SHUTDOWN { &bslash;&n;&t;/* SCTP_STATE_EMPTY */ &bslash;&n;&t;{.fn = sctp_sf_ootb, .name = &quot;sctp_sf_ootb&quot;}, &bslash;&n;&t;/* SCTP_STATE_CLOSED */ &bslash;&n;&t;{.fn = sctp_sf_tabort_8_4_8, .name = &quot;sctp_sf_tabort_8_4_8&quot;}, &bslash;&n;&t;/* SCTP_STATE_COOKIE_WAIT */ &bslash;&n;&t;{.fn = sctp_sf_discard_chunk, .name = &quot;sctp_sf_discard_chunk&quot;}, &bslash;&n;&t;/* SCTP_STATE_COOKIE_ECHOED */ &bslash;&n;&t;{.fn = sctp_sf_discard_chunk, .name = &quot;sctp_sf_discard_chunk&quot;}, &bslash;&n;&t;/* SCTP_STATE_ESTABLISHED */ &bslash;&n;&t;{.fn = sctp_sf_do_9_2_shutdown, .name = &quot;sctp_sf_do_9_2_shutdown&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_PENDING */ &bslash;&n;&t;{.fn = sctp_sf_discard_chunk, .name = &quot;sctp_sf_discard_chunk&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_SENT */ &bslash;&n;&t;{.fn = sctp_sf_do_9_2_shutdown_ack, &bslash;&n;&t; .name = &quot;sctp_sf_do_9_2_shutdown_ack&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_RECEIVED */ &bslash;&n;&t;{.fn = sctp_sf_discard_chunk, .name = &quot;sctp_sf_discard_chunk&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_ACK_SENT */ &bslash;&n;&t;{.fn = sctp_sf_discard_chunk, .name = &quot;sctp_sf_discard_chunk&quot;}, &bslash;&n;} /* TYPE_SCTP_SHUTDOWN */
DECL|macro|TYPE_SCTP_SHUTDOWN_ACK
mdefine_line|#define TYPE_SCTP_SHUTDOWN_ACK { &bslash;&n;&t;/* SCTP_STATE_EMPTY */ &bslash;&n;&t;{.fn = sctp_sf_ootb, .name = &quot;sctp_sf_ootb&quot;}, &bslash;&n;&t;/* SCTP_STATE_CLOSED */ &bslash;&n;&t;{.fn = sctp_sf_ootb, .name = &quot;sctp_sf_ootb&quot;}, &bslash;&n;&t;/* SCTP_STATE_COOKIE_WAIT */ &bslash;&n;&t;{.fn = sctp_sf_ootb, .name = &quot;sctp_sf_ootb&quot;}, &bslash;&n;&t;/* SCTP_STATE_COOKIE_ECHOED */ &bslash;&n;&t;{.fn = sctp_sf_discard_chunk, .name = &quot;sctp_sf_discard_chunk&quot;}, &bslash;&n;&t;/* SCTP_STATE_ESTABLISHED */ &bslash;&n;&t;{.fn = sctp_sf_violation, .name = &quot;sctp_sf_violation&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_PENDING */ &bslash;&n;&t;{.fn = sctp_sf_violation, .name = &quot;sctp_sf_violation&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_SENT */ &bslash;&n;&t;{.fn = sctp_sf_do_9_2_final, .name = &quot;sctp_sf_do_9_2_final&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_RECEIVED */ &bslash;&n;&t;{.fn = sctp_sf_violation, .name = &quot;sctp_sf_violation&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_ACK_SENT */ &bslash;&n;&t;{.fn = sctp_sf_do_9_2_final, .name = &quot;sctp_sf_do_9_2_final&quot;}, &bslash;&n;} /* TYPE_SCTP_SHUTDOWN_ACK */
DECL|macro|TYPE_SCTP_ERROR
mdefine_line|#define TYPE_SCTP_ERROR { &bslash;&n;&t;/* SCTP_STATE_EMPTY */ &bslash;&n;&t;{.fn = sctp_sf_ootb, .name = &quot;sctp_sf_ootb&quot;}, &bslash;&n;&t;/* SCTP_STATE_CLOSED */ &bslash;&n;&t;{.fn = sctp_sf_tabort_8_4_8, .name = &quot;sctp_sf_tabort_8_4_8&quot;}, &bslash;&n;&t;/* SCTP_STATE_COOKIE_WAIT */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_COOKIE_ECHOED */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_ESTABLISHED */ &bslash;&n;&t;{.fn = sctp_sf_operr_notify, .name = &quot;sctp_sf_operr_notify&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_PENDING */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_SENT */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_RECEIVED */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_ACK_SENT */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;} /* TYPE_SCTP_ERROR */
DECL|macro|TYPE_SCTP_COOKIE_ECHO
mdefine_line|#define TYPE_SCTP_COOKIE_ECHO { &bslash;&n;&t;/* SCTP_STATE_EMPTY */ &bslash;&n;&t;{.fn = sctp_sf_bug, .name = &quot;sctp_sf_bug&quot;}, &bslash;&n;&t;/* SCTP_STATE_CLOSED */ &bslash;&n;&t;{.fn = sctp_sf_do_5_1D_ce, .name = &quot;sctp_sf_do_5_1D_ce&quot;}, &bslash;&n;&t;/* SCTP_STATE_COOKIE_WAIT */ &bslash;&n;&t;{.fn = sctp_sf_do_5_2_4_dupcook, .name = &quot;sctp_sf_do_5_2_4_dupcook&quot;}, &bslash;&n;&t;/* SCTP_STATE_COOKIE_ECHOED */ &bslash;&n;&t;{.fn = sctp_sf_do_5_2_4_dupcook, .name = &quot;sctp_sf_do_5_2_4_dupcook&quot;}, &bslash;&n;&t;/* SCTP_STATE_ESTABLISHED */ &bslash;&n;&t;{.fn = sctp_sf_do_5_2_4_dupcook, .name = &quot;sctp_sf_do_5_2_4_dupcook&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_PENDING */ &bslash;&n;&t;{.fn = sctp_sf_do_5_2_4_dupcook, .name = &quot;sctp_sf_do_5_2_4_dupcook&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_SENT */ &bslash;&n;&t;{.fn = sctp_sf_do_5_2_4_dupcook, .name = &quot;sctp_sf_do_5_2_4_dupcook&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_RECEIVED */ &bslash;&n;&t;{.fn = sctp_sf_do_5_2_4_dupcook, .name = &quot;sctp_sf_do_5_2_4_dupcook&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_ACK_SENT */ &bslash;&n;&t;{.fn = sctp_sf_do_5_2_4_dupcook, .name = &quot;sctp_sf_do_5_2_4_dupcook&quot;}, &bslash;&n;} /* TYPE_SCTP_COOKIE_ECHO */
DECL|macro|TYPE_SCTP_COOKIE_ACK
mdefine_line|#define TYPE_SCTP_COOKIE_ACK { &bslash;&n;&t;/* SCTP_STATE_EMPTY */ &bslash;&n;&t;{.fn = sctp_sf_ootb, .name = &quot;sctp_sf_ootb&quot;}, &bslash;&n;&t;/* SCTP_STATE_CLOSED */ &bslash;&n;&t;{.fn = sctp_sf_discard_chunk, .name = &quot;sctp_sf_discard_chunk&quot;}, &bslash;&n;&t;/* SCTP_STATE_COOKIE_WAIT */ &bslash;&n;&t;{.fn = sctp_sf_discard_chunk, .name = &quot;sctp_sf_discard_chunk&quot;}, &bslash;&n;&t;/* SCTP_STATE_COOKIE_ECHOED */ &bslash;&n;&t;{.fn = sctp_sf_do_5_1E_ca, .name = &quot;sctp_sf_do_5_1E_ca&quot;}, &bslash;&n;&t;/* SCTP_STATE_ESTABLISHED */ &bslash;&n;&t;{.fn = sctp_sf_discard_chunk, .name = &quot;sctp_sf_discard_chunk&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_PENDING */ &bslash;&n;&t;{.fn = sctp_sf_discard_chunk, .name = &quot;sctp_sf_discard_chunk&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_SENT */ &bslash;&n;&t;{.fn = sctp_sf_discard_chunk, .name = &quot;sctp_sf_discard_chunk&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_RECEIVED */ &bslash;&n;&t;{.fn = sctp_sf_discard_chunk, .name = &quot;sctp_sf_discard_chunk&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_ACK_SENT */ &bslash;&n;&t;{.fn = sctp_sf_discard_chunk, .name = &quot;sctp_sf_discard_chunk&quot;}, &bslash;&n;} /* TYPE_SCTP_COOKIE_ACK */
DECL|macro|TYPE_SCTP_ECN_ECNE
mdefine_line|#define TYPE_SCTP_ECN_ECNE { &bslash;&n;&t;/* SCTP_STATE_EMPTY */ &bslash;&n;&t;{.fn = sctp_sf_ootb, .name = &quot;sctp_sf_ootb&quot;}, &bslash;&n;&t;/* SCTP_STATE_CLOSED */ &bslash;&n;&t;{.fn = sctp_sf_bug, .name = &quot;sctp_sf_bug&quot;}, &bslash;&n;&t;/* SCTP_STATE_COOKIE_WAIT */ &bslash;&n;&t;{.fn = sctp_sf_bug, .name = &quot;sctp_sf_bug&quot;}, &bslash;&n;&t;/* SCTP_STATE_COOKIE_ECHOED */ &bslash;&n;&t;{.fn = sctp_sf_do_ecne, .name = &quot;sctp_sf_do_ecne&quot;}, &bslash;&n;&t;/* SCTP_STATE_ESTABLISHED */ &bslash;&n;&t;{.fn = sctp_sf_do_ecne, .name = &quot;sctp_sf_do_ecne&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_PENDING */ &bslash;&n;&t;{.fn = sctp_sf_do_ecne, .name = &quot;sctp_sf_do_ecne&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_SENT */ &bslash;&n;&t;{.fn = sctp_sf_do_ecne, .name = &quot;sctp_sf_do_ecne&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_RECEIVED */ &bslash;&n;&t;{.fn = sctp_sf_do_ecne, .name = &quot;sctp_sf_do_ecne&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_ACK_SENT */ &bslash;&n;&t;{.fn = sctp_sf_bug, .name = &quot;sctp_sf_bug&quot;}, &bslash;&n;} /* TYPE_SCTP_ECN_ECNE */
DECL|macro|TYPE_SCTP_ECN_CWR
mdefine_line|#define TYPE_SCTP_ECN_CWR { &bslash;&n;&t;/* SCTP_STATE_EMPTY */ &bslash;&n;&t;{.fn = sctp_sf_ootb, .name = &quot;sctp_sf_ootb&quot;}, &bslash;&n;&t;/* SCTP_STATE_CLOSED */ &bslash;&n;&t;{.fn = sctp_sf_discard_chunk, .name = &quot;sctp_sf_discard_chunk&quot;}, &bslash;&n;&t;/* SCTP_STATE_COOKIE_WAIT */ &bslash;&n;&t;{.fn = sctp_sf_discard_chunk, .name = &quot;sctp_sf_discard_chunk&quot;}, &bslash;&n;&t;/* SCTP_STATE_COOKIE_ECHOED */ &bslash;&n;&t;{.fn = sctp_sf_discard_chunk, .name = &quot;sctp_sf_discard_chunk&quot;}, &bslash;&n;&t;/* SCTP_STATE_ESTABLISHED */ &bslash;&n;&t;{.fn = sctp_sf_do_ecn_cwr, .name = &quot;sctp_sf_do_ecn_cwr&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_PENDING */ &bslash;&n;&t;{.fn = sctp_sf_do_ecn_cwr, .name = &quot;sctp_sf_do_ecn_cwr&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_SENT */ &bslash;&n;&t;{.fn = sctp_sf_do_ecn_cwr, .name = &quot;sctp_sf_do_ecn_cwr&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_RECEIVED */ &bslash;&n;&t;{.fn = sctp_sf_discard_chunk, .name = &quot;sctp_sf_discard_chunk&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_ACK_SENT */ &bslash;&n;&t;{.fn = sctp_sf_bug, .name = &quot;sctp_sf_bug&quot;}, &bslash;&n;} /* TYPE_SCTP_ECN_CWR */
DECL|macro|TYPE_SCTP_SHUTDOWN_COMPLETE
mdefine_line|#define TYPE_SCTP_SHUTDOWN_COMPLETE { &bslash;&n;&t;/* SCTP_STATE_EMPTY */ &bslash;&n;&t;{.fn = sctp_sf_ootb, .name = &quot;sctp_sf_ootb&quot;}, &bslash;&n;&t;/* SCTP_STATE_CLOSED */ &bslash;&n;&t;{.fn = sctp_sf_discard_chunk, .name = &quot;sctp_sf_discard_chunk&quot;}, &bslash;&n;&t;/* SCTP_STATE_COOKIE_WAIT */ &bslash;&n;&t;{.fn = sctp_sf_discard_chunk, .name = &quot;sctp_sf_discard_chunk&quot;}, &bslash;&n;&t;/* SCTP_STATE_COOKIE_ECHOED */ &bslash;&n;&t;{.fn = sctp_sf_discard_chunk, .name = &quot;sctp_sf_discard_chunk&quot;}, &bslash;&n;&t;/* SCTP_STATE_ESTABLISHED */ &bslash;&n;&t;{.fn = sctp_sf_discard_chunk, .name = &quot;sctp_sf_discard_chunk&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_PENDING */ &bslash;&n;&t;{.fn = sctp_sf_discard_chunk, .name = &quot;sctp_sf_discard_chunk&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_SENT */ &bslash;&n;&t;{.fn = sctp_sf_discard_chunk, .name = &quot;sctp_sf_discard_chunk&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_RECEIVED */ &bslash;&n;&t;{.fn = sctp_sf_discard_chunk, .name = &quot;sctp_sf_discard_chunk&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_ACK_SENT */ &bslash;&n;&t;{.fn = sctp_sf_do_4_C, .name = &quot;sctp_sf_do_4_C&quot;}, &bslash;&n;} /* TYPE_SCTP_SHUTDOWN_COMPLETE */
multiline_comment|/* The primary index for this table is the chunk type.&n; * The secondary index for this table is the state.&n; *&n; * For base protocol (RFC 2960).&n; */
DECL|variable|chunk_event_table
id|sctp_sm_table_entry_t
id|chunk_event_table
(braket
id|SCTP_NUM_BASE_CHUNK_TYPES
)braket
(braket
id|SCTP_STATE_NUM_STATES
)braket
op_assign
(brace
id|TYPE_SCTP_DATA
comma
id|TYPE_SCTP_INIT
comma
id|TYPE_SCTP_INIT_ACK
comma
id|TYPE_SCTP_SACK
comma
id|TYPE_SCTP_HEARTBEAT
comma
id|TYPE_SCTP_HEARTBEAT_ACK
comma
id|TYPE_SCTP_ABORT
comma
id|TYPE_SCTP_SHUTDOWN
comma
id|TYPE_SCTP_SHUTDOWN_ACK
comma
id|TYPE_SCTP_ERROR
comma
id|TYPE_SCTP_COOKIE_ECHO
comma
id|TYPE_SCTP_COOKIE_ACK
comma
id|TYPE_SCTP_ECN_ECNE
comma
id|TYPE_SCTP_ECN_CWR
comma
id|TYPE_SCTP_SHUTDOWN_COMPLETE
comma
)brace
suffix:semicolon
multiline_comment|/* state_fn_t chunk_event_table[][] */
r_static
id|sctp_sm_table_entry_t
DECL|variable|chunk_event_table_asconf
id|chunk_event_table_asconf
(braket
id|SCTP_STATE_NUM_STATES
)braket
op_assign
(brace
multiline_comment|/* SCTP_STATE_EMPTY */
(brace
dot
id|fn
op_assign
id|sctp_sf_discard_chunk
comma
dot
id|name
op_assign
l_string|&quot;sctp_sf_discard_chunk&quot;
)brace
comma
multiline_comment|/* SCTP_STATE_CLOSED */
(brace
dot
id|fn
op_assign
id|sctp_sf_discard_chunk
comma
dot
id|name
op_assign
l_string|&quot;sctp_sf_discard_chunk&quot;
)brace
comma
multiline_comment|/* SCTP_STATE_COOKIE_WAIT */
(brace
dot
id|fn
op_assign
id|sctp_sf_discard_chunk
comma
dot
id|name
op_assign
l_string|&quot;sctp_sf_discard_chunk&quot;
)brace
comma
multiline_comment|/* SCTP_STATE_COOKIE_ECHOED */
(brace
dot
id|fn
op_assign
id|sctp_sf_discard_chunk
comma
dot
id|name
op_assign
l_string|&quot;sctp_sf_discard_chunk&quot;
)brace
comma
multiline_comment|/* SCTP_STATE_ESTABLISHED */
(brace
dot
id|fn
op_assign
id|sctp_sf_discard_chunk
comma
dot
id|name
op_assign
l_string|&quot;sctp_sf_discard_chunk (will be sctp_addip_do_asconf)&quot;
)brace
comma
multiline_comment|/* SCTP_STATE_SHUTDOWN_PENDING */
(brace
dot
id|fn
op_assign
id|sctp_sf_discard_chunk
comma
dot
id|name
op_assign
l_string|&quot;sctp_sf_discard_chunk&quot;
)brace
comma
multiline_comment|/* SCTP_STATE_SHUTDOWN_SENT */
(brace
dot
id|fn
op_assign
id|sctp_sf_discard_chunk
comma
dot
id|name
op_assign
l_string|&quot;sctp_sf_discard_chunk&quot;
)brace
comma
multiline_comment|/* SCTP_STATE_SHUTDOWN_RECEIVED */
(brace
dot
id|fn
op_assign
id|sctp_sf_discard_chunk
comma
dot
id|name
op_assign
l_string|&quot;sctp_sf_discard_chunk&quot;
)brace
comma
multiline_comment|/* SCTP_STATE_SHUTDOWN_ACK_SENT */
(brace
dot
id|fn
op_assign
id|sctp_sf_discard_chunk
comma
dot
id|name
op_assign
l_string|&quot;sctp_sf_discard_chunk&quot;
)brace
comma
)brace
suffix:semicolon
multiline_comment|/* chunk asconf */
r_static
id|sctp_sm_table_entry_t
DECL|variable|chunk_event_table_asconf_ack
id|chunk_event_table_asconf_ack
(braket
id|SCTP_STATE_NUM_STATES
)braket
op_assign
(brace
multiline_comment|/* SCTP_STATE_EMPTY */
(brace
dot
id|fn
op_assign
id|sctp_sf_discard_chunk
comma
dot
id|name
op_assign
l_string|&quot;sctp_sf_discard_chunk&quot;
)brace
comma
multiline_comment|/* SCTP_STATE_CLOSED */
(brace
dot
id|fn
op_assign
id|sctp_sf_discard_chunk
comma
dot
id|name
op_assign
l_string|&quot;sctp_sf_discard_chunk&quot;
)brace
comma
multiline_comment|/* SCTP_STATE_COOKIE_WAIT */
(brace
dot
id|fn
op_assign
id|sctp_sf_discard_chunk
comma
dot
id|name
op_assign
l_string|&quot;sctp_sf_discard_chunk&quot;
)brace
comma
multiline_comment|/* SCTP_STATE_COOKIE_ECHOED */
(brace
dot
id|fn
op_assign
id|sctp_sf_discard_chunk
comma
dot
id|name
op_assign
l_string|&quot;sctp_sf_discard_chunk&quot;
)brace
comma
multiline_comment|/* SCTP_STATE_ESTABLISHED */
(brace
dot
id|fn
op_assign
id|sctp_sf_discard_chunk
comma
dot
id|name
op_assign
l_string|&quot;sctp_sf_discard_chunk (will be sctp_addip_do_asconf_ack)&quot;
)brace
comma
multiline_comment|/* SCTP_STATE_SHUTDOWN_PENDING */
(brace
dot
id|fn
op_assign
id|sctp_sf_discard_chunk
comma
dot
id|name
op_assign
l_string|&quot;sctp_sf_discard_chunk&quot;
)brace
comma
multiline_comment|/* SCTP_STATE_SHUTDOWN_SENT */
(brace
dot
id|fn
op_assign
id|sctp_sf_discard_chunk
comma
dot
id|name
op_assign
l_string|&quot;sctp_sf_discard_chunk&quot;
)brace
comma
multiline_comment|/* SCTP_STATE_SHUTDOWN_RECEIVED */
(brace
dot
id|fn
op_assign
id|sctp_sf_discard_chunk
comma
dot
id|name
op_assign
l_string|&quot;sctp_sf_discard_chunk&quot;
)brace
comma
multiline_comment|/* SCTP_STATE_SHUTDOWN_ACK_SENT */
(brace
dot
id|fn
op_assign
id|sctp_sf_discard_chunk
comma
dot
id|name
op_assign
l_string|&quot;sctp_sf_discard_chunk&quot;
)brace
comma
)brace
suffix:semicolon
multiline_comment|/* chunk asconf_ack */
r_static
id|sctp_sm_table_entry_t
DECL|variable|chunk_event_table_unknown
id|chunk_event_table_unknown
(braket
id|SCTP_STATE_NUM_STATES
)braket
op_assign
(brace
multiline_comment|/* SCTP_STATE_EMPTY */
(brace
dot
id|fn
op_assign
id|sctp_sf_ootb
comma
dot
id|name
op_assign
l_string|&quot;sctp_sf_ootb&quot;
)brace
comma
multiline_comment|/* SCTP_STATE_CLOSED */
(brace
dot
id|fn
op_assign
id|sctp_sf_tabort_8_4_8
comma
dot
id|name
op_assign
l_string|&quot;sctp_sf_tabort_8_4_8&quot;
)brace
comma
multiline_comment|/* SCTP_STATE_COOKIE_WAIT */
(brace
dot
id|fn
op_assign
id|sctp_sf_unk_chunk
comma
dot
id|name
op_assign
l_string|&quot;sctp_sf_unk_chunk&quot;
)brace
comma
multiline_comment|/* SCTP_STATE_COOKIE_ECHOED */
(brace
dot
id|fn
op_assign
id|sctp_sf_unk_chunk
comma
dot
id|name
op_assign
l_string|&quot;sctp_sf_unk_chunk&quot;
)brace
comma
multiline_comment|/* SCTP_STATE_ESTABLISHED */
(brace
dot
id|fn
op_assign
id|sctp_sf_unk_chunk
comma
dot
id|name
op_assign
l_string|&quot;sctp_sf_unk_chunk&quot;
)brace
comma
multiline_comment|/* SCTP_STATE_SHUTDOWN_PENDING */
(brace
dot
id|fn
op_assign
id|sctp_sf_unk_chunk
comma
dot
id|name
op_assign
l_string|&quot;sctp_sf_unk_chunk&quot;
)brace
comma
multiline_comment|/* SCTP_STATE_SHUTDOWN_SENT */
(brace
dot
id|fn
op_assign
id|sctp_sf_unk_chunk
comma
dot
id|name
op_assign
l_string|&quot;sctp_sf_unk_chunk&quot;
)brace
comma
multiline_comment|/* SCTP_STATE_SHUTDOWN_RECEIVED */
(brace
dot
id|fn
op_assign
id|sctp_sf_unk_chunk
comma
dot
id|name
op_assign
l_string|&quot;sctp_sf_unk_chunk&quot;
)brace
comma
multiline_comment|/* SCTP_STATE_SHUTDOWN_ACK_SENT */
(brace
dot
id|fn
op_assign
id|sctp_sf_unk_chunk
comma
dot
id|name
op_assign
l_string|&quot;sctp_sf_unk_chunk&quot;
)brace
comma
)brace
suffix:semicolon
multiline_comment|/* chunk unknown */
DECL|macro|TYPE_SCTP_PRIMITIVE_INITIALIZE
mdefine_line|#define TYPE_SCTP_PRIMITIVE_INITIALIZE  { &bslash;&n;&t;/* SCTP_STATE_EMPTY */ &bslash;&n;&t;{.fn = sctp_sf_bug, .name = &quot;sctp_sf_bug&quot;}, &bslash;&n;&t;/* SCTP_STATE_CLOSED */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_COOKIE_WAIT */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_COOKIE_ECHOED */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_ESTABLISHED */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_PENDING */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_SENT */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_RECEIVED */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_ACK_SENT */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;} /* TYPE_SCTP_PRIMITIVE_INITIALIZE */
DECL|macro|TYPE_SCTP_PRIMITIVE_ASSOCIATE
mdefine_line|#define TYPE_SCTP_PRIMITIVE_ASSOCIATE  { &bslash;&n;&t;/* SCTP_STATE_EMPTY */ &bslash;&n;&t;{.fn = sctp_sf_bug, .name = &quot;sctp_sf_bug&quot;}, &bslash;&n;&t;/* SCTP_STATE_CLOSED */ &bslash;&n;&t;{.fn = sctp_sf_do_prm_asoc, .name = &quot;sctp_sf_do_prm_asoc&quot;}, &bslash;&n;&t;/* SCTP_STATE_COOKIE_WAIT */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_COOKIE_ECHOED */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_ESTABLISHED */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_PENDING */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_SENT */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_RECEIVED */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_ACK_SENT */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;} /* TYPE_SCTP_PRIMITIVE_ASSOCIATE */
DECL|macro|TYPE_SCTP_PRIMITIVE_SHUTDOWN
mdefine_line|#define TYPE_SCTP_PRIMITIVE_SHUTDOWN  { &bslash;&n;&t;/* SCTP_STATE_EMPTY */ &bslash;&n;&t;{.fn = sctp_sf_bug, .name = &quot;sctp_sf_bug&quot;}, &bslash;&n;&t;/* SCTP_STATE_CLOSED */ &bslash;&n;&t;{.fn = sctp_sf_error_closed, .name = &quot;sctp_sf_error_closed&quot;}, &bslash;&n;&t;/* SCTP_STATE_COOKIE_WAIT */ &bslash;&n;&t;{.fn = sctp_sf_cookie_wait_prm_shutdown, &bslash;&n;&t; .name = &quot;sctp_sf_cookie_wait_prm_shutdown&quot;}, &bslash;&n;&t;/* SCTP_STATE_COOKIE_ECHOED */ &bslash;&n;&t;{.fn = sctp_sf_cookie_echoed_prm_shutdown, &bslash;&n;&t; .name = &quot;sctp_sf_cookie_echoed_prm_shutdown&quot;},&bslash;&n;&t;/* SCTP_STATE_ESTABLISHED */ &bslash;&n;&t;{.fn = sctp_sf_do_9_2_prm_shutdown, &bslash;&n;&t; .name = &quot;sctp_sf_do_9_2_prm_shutdown&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_PENDING */ &bslash;&n;&t;{.fn = sctp_sf_ignore_primitive, .name = &quot;sctp_sf_ignore_primitive&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_SENT */ &bslash;&n;&t;{.fn = sctp_sf_ignore_primitive, .name = &quot;sctp_sf_ignore_primitive&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_RECEIVED */ &bslash;&n;&t;{.fn = sctp_sf_ignore_primitive, .name = &quot;sctp_sf_ignore_primitive&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_ACK_SENT */ &bslash;&n;&t;{.fn = sctp_sf_ignore_primitive, .name = &quot;sctp_sf_ignore_primitive&quot;}, &bslash;&n;} /* TYPE_SCTP_PRIMITIVE_SHUTDOWN */
DECL|macro|TYPE_SCTP_PRIMITIVE_ABORT
mdefine_line|#define TYPE_SCTP_PRIMITIVE_ABORT  { &bslash;&n;&t;/* SCTP_STATE_EMPTY */ &bslash;&n;&t;{.fn = sctp_sf_bug, .name = &quot;sctp_sf_bug&quot;}, &bslash;&n;&t;/* SCTP_STATE_CLOSED */ &bslash;&n;&t;{.fn = sctp_sf_error_closed, .name = &quot;sctp_sf_error_closed&quot;}, &bslash;&n;&t;/* SCTP_STATE_COOKIE_WAIT */ &bslash;&n;&t;{.fn = sctp_sf_cookie_wait_prm_abort, &bslash;&n;&t;.name = &quot;sctp_sf_cookie_wait_prm_abort&quot;}, &bslash;&n;&t;/* SCTP_STATE_COOKIE_ECHOED */ &bslash;&n;&t;{.fn = sctp_sf_cookie_echoed_prm_abort, &bslash;&n;&t;.name = &quot;sctp_sf_cookie_echoed_prm_abort&quot;}, &bslash;&n;&t;/* SCTP_STATE_ESTABLISHED */ &bslash;&n;&t;{.fn = sctp_sf_do_9_1_prm_abort, &bslash;&n;&t;.name = &quot;sctp_sf_do_9_1_prm_abort&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_PENDING */ &bslash;&n;&t;{.fn = sctp_sf_shutdown_pending_prm_abort, &bslash;&n;&t;.name = &quot;sctp_sf_shutdown_pending_prm_abort&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_SENT */ &bslash;&n;&t;{.fn = sctp_sf_shutdown_sent_prm_abort, &bslash;&n;&t;.name = &quot;sctp_sf_shutdown_sent_prm_abort&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_RECEIVED */ &bslash;&n;&t;{.fn = sctp_sf_do_9_1_prm_abort, &bslash;&n;&t;.name = &quot;sctp_sf_do_9_1_prm_abort&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_ACK_SENT */ &bslash;&n;&t;{.fn = sctp_sf_shutdown_ack_sent_prm_abort, &bslash;&n;&t;.name = &quot;sctp_sf_shutdown_ack_sent_prm_abort&quot;}, &bslash;&n;} /* TYPE_SCTP_PRIMITIVE_ABORT */
DECL|macro|TYPE_SCTP_PRIMITIVE_SEND
mdefine_line|#define TYPE_SCTP_PRIMITIVE_SEND  { &bslash;&n;&t;/* SCTP_STATE_EMPTY */ &bslash;&n;&t;{.fn = sctp_sf_bug, .name = &quot;sctp_sf_bug&quot;}, &bslash;&n;&t;/* SCTP_STATE_CLOSED */ &bslash;&n;&t;{.fn = sctp_sf_error_closed, .name = &quot;sctp_sf_error_closed&quot;}, &bslash;&n;&t;/* SCTP_STATE_COOKIE_WAIT */ &bslash;&n;&t;{.fn = sctp_sf_do_prm_send, .name = &quot;sctp_sf_do_prm_send&quot;}, &bslash;&n;&t;/* SCTP_STATE_COOKIE_ECHOED */ &bslash;&n;&t;{.fn = sctp_sf_do_prm_send, .name = &quot;sctp_sf_do_prm_send&quot;}, &bslash;&n;&t;/* SCTP_STATE_ESTABLISHED */ &bslash;&n;&t;{.fn = sctp_sf_do_prm_send, .name = &quot;sctp_sf_do_prm_send&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_PENDING */ &bslash;&n;&t;{.fn = sctp_sf_error_shutdown, .name = &quot;sctp_sf_error_shutdown&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_SENT */ &bslash;&n;&t;{.fn = sctp_sf_error_shutdown, .name = &quot;sctp_sf_error_shutdown&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_RECEIVED */ &bslash;&n;&t;{.fn = sctp_sf_error_shutdown, .name = &quot;sctp_sf_error_shutdown&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_ACK_SENT */ &bslash;&n;&t;{.fn = sctp_sf_error_shutdown, .name = &quot;sctp_sf_error_shutdown&quot;}, &bslash;&n;} /* TYPE_SCTP_PRIMITIVE_SEND */
DECL|macro|TYPE_SCTP_PRIMITIVE_SETPRIMARY
mdefine_line|#define TYPE_SCTP_PRIMITIVE_SETPRIMARY  { &bslash;&n;&t;/* SCTP_STATE_EMPTY */ &bslash;&n;&t;{.fn = sctp_sf_bug, .name = &quot;sctp_sf_bug&quot;}, &bslash;&n;&t;/* SCTP_STATE_CLOSED */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_COOKIE_WAIT */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_COOKIE_ECHOED */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_ESTABLISHED */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_PENDING */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_SENT */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_RECEIVED */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_ACK_SENT */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;} /* TYPE_SCTP_PRIMITIVE_SETPRIMARY */
DECL|macro|TYPE_SCTP_PRIMITIVE_RECEIVE
mdefine_line|#define TYPE_SCTP_PRIMITIVE_RECEIVE  { &bslash;&n;&t;/* SCTP_STATE_EMPTY */ &bslash;&n;&t;{.fn = sctp_sf_bug, .name = &quot;sctp_sf_bug&quot;}, &bslash;&n;&t;/* SCTP_STATE_CLOSED */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_COOKIE_WAIT */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_COOKIE_ECHOED */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_ESTABLISHED */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_PENDING */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_SENT */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_RECEIVED */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_ACK_SENT */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;} /* TYPE_SCTP_PRIMITIVE_RECEIVE */
DECL|macro|TYPE_SCTP_PRIMITIVE_STATUS
mdefine_line|#define TYPE_SCTP_PRIMITIVE_STATUS  { &bslash;&n;&t;/* SCTP_STATE_EMPTY */ &bslash;&n;&t;{.fn = sctp_sf_bug, .name = &quot;sctp_sf_bug&quot;}, &bslash;&n;&t;/* SCTP_STATE_CLOSED */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_COOKIE_WAIT */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_COOKIE_ECHOED */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_ESTABLISHED */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_PENDING */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_SENT */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_RECEIVED */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_ACK_SENT */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;} /* TYPE_SCTP_PRIMITIVE_STATUS */
DECL|macro|TYPE_SCTP_PRIMITIVE_CHANGEHEARTBEAT
mdefine_line|#define TYPE_SCTP_PRIMITIVE_CHANGEHEARTBEAT  { &bslash;&n;&t;/* SCTP_STATE_EMPTY */ &bslash;&n;&t;{.fn = sctp_sf_bug, .name = &quot;sctp_sf_bug&quot;}, &bslash;&n;&t;/* SCTP_STATE_CLOSED */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_COOKIE_WAIT */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_COOKIE_ECHOED */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_ESTABLISHED */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_PENDING */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_SENT */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_RECEIVED */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_ACK_SENT */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;} /* TYPE_SCTP_PRIMITIVE_CHANGEHEARTBEAT */
DECL|macro|TYPE_SCTP_PRIMITIVE_REQUESTHEARTBEAT
mdefine_line|#define TYPE_SCTP_PRIMITIVE_REQUESTHEARTBEAT  { &bslash;&n;&t;/* SCTP_STATE_EMPTY */ &bslash;&n;&t;{.fn = sctp_sf_bug, .name = &quot;sctp_sf_bug&quot;}, &bslash;&n;&t;/* SCTP_STATE_CLOSED */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_COOKIE_WAIT */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_COOKIE_ECHOED */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_ESTABLISHED */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_PENDING */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_SENT */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_RECEIVED */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_ACK_SENT */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;} /* TYPE_SCTP_PRIMITIVE_REQUESTHEARTBEAT */
DECL|macro|TYPE_SCTP_PRIMITIVE_GETSRTTREPORT
mdefine_line|#define TYPE_SCTP_PRIMITIVE_GETSRTTREPORT  { &bslash;&n;&t;/* SCTP_STATE_EMPTY */ &bslash;&n;&t;{.fn = sctp_sf_bug, .name = &quot;sctp_sf_bug&quot;}, &bslash;&n;&t;/* SCTP_STATE_CLOSED */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_COOKIE_WAIT */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_COOKIE_ECHOED */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_ESTABLISHED */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_PENDING */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_SENT */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_RECEIVED */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_ACK_SENT */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;} /* TYPE_SCTP_PRIMITIVE_GETSRTTREPORT */
DECL|macro|TYPE_SCTP_PRIMITIVE_SETFAILURETHRESHOLD
mdefine_line|#define TYPE_SCTP_PRIMITIVE_SETFAILURETHRESHOLD  { &bslash;&n;&t;/* SCTP_STATE_EMPTY */ &bslash;&n;&t;{.fn = sctp_sf_bug, .name = &quot;sctp_sf_bug&quot;}, &bslash;&n;&t;/* SCTP_STATE_CLOSED */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_COOKIE_WAIT */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_COOKIE_ECHOED */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_ESTABLISHED */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_PENDING */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_SENT */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_RECEIVED */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_ACK_SENT */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;} /* TYPE_SCTP_PRIMITIVE_SETFAILURETHRESHOLD */
DECL|macro|TYPE_SCTP_PRIMITIVE_SETPROTOPARAMETERS
mdefine_line|#define TYPE_SCTP_PRIMITIVE_SETPROTOPARAMETERS  { &bslash;&n;&t;/* SCTP_STATE_EMPTY */ &bslash;&n;&t;{.fn = sctp_sf_bug, .name = &quot;sctp_sf_bug&quot;}, &bslash;&n;&t;/* SCTP_STATE_CLOSED */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_COOKIE_WAIT */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_COOKIE_ECHOED */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_ESTABLISHED */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_PENDING */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_SENT */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_RECEIVED */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_ACK_SENT */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;} /* TYPE_SCTP_PRIMITIVE_SETPROTOPARAMETERS */
DECL|macro|TYPE_SCTP_PRIMITIVE_RECEIVE_UNSENT
mdefine_line|#define TYPE_SCTP_PRIMITIVE_RECEIVE_UNSENT  { &bslash;&n;&t;/* SCTP_STATE_EMPTY */ &bslash;&n;&t;{.fn = sctp_sf_bug, .name = &quot;sctp_sf_bug&quot;}, &bslash;&n;&t;/* SCTP_STATE_CLOSED */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_COOKIE_WAIT */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_COOKIE_ECHOED */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_ESTABLISHED */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_PENDING */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_SENT */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_RECEIVED */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_ACK_SENT */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;} /* TYPE_SCTP_PRIMITIVE_RECEIVE_UNSENT */
DECL|macro|TYPE_SCTP_PRIMITIVE_RECEIVE_UNACKED
mdefine_line|#define TYPE_SCTP_PRIMITIVE_RECEIVE_UNACKED  { &bslash;&n;&t;/* SCTP_STATE_EMPTY */ &bslash;&n;&t;{.fn = sctp_sf_bug, .name = &quot;sctp_sf_bug&quot;}, &bslash;&n;&t;/* SCTP_STATE_CLOSED */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_COOKIE_WAIT */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_COOKIE_ECHOED */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_ESTABLISHED */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_PENDING */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_SENT */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_RECEIVED */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_ACK_SENT */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;} /* TYPE_SCTP_PRIMITIVE_RECEIVE_UNACKED */
DECL|macro|TYPE_SCTP_PRIMITIVE_DESTROY
mdefine_line|#define TYPE_SCTP_PRIMITIVE_DESTROY  { &bslash;&n;&t;/* SCTP_STATE_EMPTY */ &bslash;&n;&t;{.fn = sctp_sf_bug, .name = &quot;sctp_sf_bug&quot;}, &bslash;&n;&t;/* SCTP_STATE_CLOSED */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_COOKIE_WAIT */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_COOKIE_ECHOED */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_ESTABLISHED */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_PENDING */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_SENT */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_RECEIVED */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_ACK_SENT */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;} /* TYPE_SCTP_PRIMITIVE_DESTROY */
multiline_comment|/* The primary index for this table is the primitive type.&n; * The secondary index for this table is the state.&n; */
DECL|variable|primitive_event_table
id|sctp_sm_table_entry_t
id|primitive_event_table
(braket
id|SCTP_NUM_PRIMITIVE_TYPES
)braket
(braket
id|SCTP_STATE_NUM_STATES
)braket
op_assign
(brace
id|TYPE_SCTP_PRIMITIVE_INITIALIZE
comma
id|TYPE_SCTP_PRIMITIVE_ASSOCIATE
comma
id|TYPE_SCTP_PRIMITIVE_SHUTDOWN
comma
id|TYPE_SCTP_PRIMITIVE_ABORT
comma
id|TYPE_SCTP_PRIMITIVE_SEND
comma
id|TYPE_SCTP_PRIMITIVE_SETPRIMARY
comma
id|TYPE_SCTP_PRIMITIVE_RECEIVE
comma
id|TYPE_SCTP_PRIMITIVE_STATUS
comma
id|TYPE_SCTP_PRIMITIVE_CHANGEHEARTBEAT
comma
id|TYPE_SCTP_PRIMITIVE_REQUESTHEARTBEAT
comma
id|TYPE_SCTP_PRIMITIVE_GETSRTTREPORT
comma
id|TYPE_SCTP_PRIMITIVE_SETFAILURETHRESHOLD
comma
id|TYPE_SCTP_PRIMITIVE_SETPROTOPARAMETERS
comma
id|TYPE_SCTP_PRIMITIVE_RECEIVE_UNSENT
comma
id|TYPE_SCTP_PRIMITIVE_RECEIVE_UNACKED
comma
id|TYPE_SCTP_PRIMITIVE_DESTROY
comma
)brace
suffix:semicolon
DECL|macro|TYPE_SCTP_OTHER_NO_PENDING_TSN
mdefine_line|#define TYPE_SCTP_OTHER_NO_PENDING_TSN  { &bslash;&n;&t;/* SCTP_STATE_EMPTY */ &bslash;&n;&t;{.fn = sctp_sf_bug, .name = &quot;sctp_sf_bug&quot;}, &bslash;&n;&t;/* SCTP_STATE_CLOSED */ &bslash;&n;&t;{.fn = sctp_sf_ignore_other, .name = &quot;sctp_sf_ignore_other&quot;}, &bslash;&n;&t;/* SCTP_STATE_COOKIE_WAIT */ &bslash;&n;&t;{.fn = sctp_sf_ignore_other, .name = &quot;sctp_sf_ignore_other&quot;}, &bslash;&n;&t;/* SCTP_STATE_COOKIE_ECHOED */ &bslash;&n;&t;{.fn = sctp_sf_ignore_other, .name = &quot;sctp_sf_ignore_other&quot;}, &bslash;&n;&t;/* SCTP_STATE_ESTABLISHED */ &bslash;&n;&t;{.fn = sctp_sf_ignore_other, .name = &quot;sctp_sf_ignore_other&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_PENDING */ &bslash;&n;&t;{.fn = sctp_sf_do_9_2_start_shutdown, &bslash;&n;&t; .name = &quot;sctp_do_9_2_start_shutdown&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_SENT */ &bslash;&n;&t;{.fn = sctp_sf_ignore_other, .name = &quot;sctp_sf_ignore_other&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_RECEIVED */ &bslash;&n;&t;{.fn = sctp_sf_do_9_2_shutdown_ack, &bslash;&n;&t; .name = &quot;sctp_sf_do_9_2_shutdown_ack&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_ACK_SENT */ &bslash;&n;&t;{.fn = sctp_sf_ignore_other, .name = &quot;sctp_sf_ignore_other&quot;}, &bslash;&n;}
DECL|macro|TYPE_SCTP_OTHER_ICMP_UNREACHFRAG
mdefine_line|#define TYPE_SCTP_OTHER_ICMP_UNREACHFRAG  { &bslash;&n;&t;/* SCTP_STATE_EMPTY */ &bslash;&n;&t;{.fn = sctp_sf_bug, .name = &quot;sctp_sf_bug&quot;}, &bslash;&n;&t;/* SCTP_STATE_CLOSED */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_COOKIE_WAIT */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_COOKIE_ECHOED */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_ESTABLISHED */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_PENDING */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_SENT */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_RECEIVED */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_ACK_SENT */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;}
DECL|variable|other_event_table
id|sctp_sm_table_entry_t
id|other_event_table
(braket
id|SCTP_NUM_OTHER_TYPES
)braket
(braket
id|SCTP_STATE_NUM_STATES
)braket
op_assign
(brace
id|TYPE_SCTP_OTHER_NO_PENDING_TSN
comma
id|TYPE_SCTP_OTHER_ICMP_UNREACHFRAG
comma
)brace
suffix:semicolon
DECL|macro|TYPE_SCTP_EVENT_TIMEOUT_NONE
mdefine_line|#define TYPE_SCTP_EVENT_TIMEOUT_NONE { &bslash;&n;&t;/* SCTP_STATE_EMPTY */ &bslash;&n;&t;{.fn = sctp_sf_bug, .name = &quot;sctp_sf_bug&quot;}, &bslash;&n;&t;/* SCTP_STATE_CLOSED */ &bslash;&n;&t;{.fn = sctp_sf_bug, .name = &quot;sctp_sf_bug&quot;}, &bslash;&n;&t;/* SCTP_STATE_COOKIE_WAIT */ &bslash;&n;&t;{.fn = sctp_sf_bug, .name = &quot;sctp_sf_bug&quot;}, &bslash;&n;&t;/* SCTP_STATE_COOKIE_ECHOED */ &bslash;&n;&t;{.fn = sctp_sf_bug, .name = &quot;sctp_sf_bug&quot;}, &bslash;&n;&t;/* SCTP_STATE_ESTABLISHED */ &bslash;&n;&t;{.fn = sctp_sf_bug, .name = &quot;sctp_sf_bug&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_PENDING */ &bslash;&n;&t;{.fn = sctp_sf_bug, .name = &quot;sctp_sf_bug&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_SENT */ &bslash;&n;&t;{.fn = sctp_sf_bug, .name = &quot;sctp_sf_bug&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_RECEIVED */ &bslash;&n;&t;{.fn = sctp_sf_bug, .name = &quot;sctp_sf_bug&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_ACK_SENT */ &bslash;&n;&t;{.fn = sctp_sf_bug, .name = &quot;sctp_sf_bug&quot;}, &bslash;&n;}
DECL|macro|TYPE_SCTP_EVENT_TIMEOUT_T1_COOKIE
mdefine_line|#define TYPE_SCTP_EVENT_TIMEOUT_T1_COOKIE { &bslash;&n;&t;/* SCTP_STATE_EMPTY */ &bslash;&n;&t;{.fn = sctp_sf_bug, .name = &quot;sctp_sf_bug&quot;}, &bslash;&n;&t;/* SCTP_STATE_CLOSED */ &bslash;&n;&t;{.fn = sctp_sf_timer_ignore, .name = &quot;sctp_sf_timer_ignore&quot;}, &bslash;&n;&t;/* SCTP_STATE_COOKIE_WAIT */ &bslash;&n;&t;{.fn = sctp_sf_bug, .name = &quot;sctp_sf_bug&quot;}, &bslash;&n;&t;/* SCTP_STATE_COOKIE_ECHOED */ &bslash;&n;&t;{.fn = sctp_sf_t1_timer_expire, .name = &quot;sctp_sf_t1_timer_expire&quot;}, &bslash;&n;&t;/* SCTP_STATE_ESTABLISHED */ &bslash;&n;&t;{.fn = sctp_sf_timer_ignore, .name = &quot;sctp_sf_timer_ignore&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_PENDING */ &bslash;&n;&t;{.fn = sctp_sf_timer_ignore, .name = &quot;sctp_sf_timer_ignore&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_SENT */ &bslash;&n;&t;{.fn = sctp_sf_timer_ignore, .name = &quot;sctp_sf_timer_ignore&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_RECEIVED */ &bslash;&n;&t;{.fn = sctp_sf_timer_ignore, .name = &quot;sctp_sf_timer_ignore&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_ACK_SENT */ &bslash;&n;&t;{.fn = sctp_sf_timer_ignore, .name = &quot;sctp_sf_timer_ignore&quot;}, &bslash;&n;}
DECL|macro|TYPE_SCTP_EVENT_TIMEOUT_T1_INIT
mdefine_line|#define TYPE_SCTP_EVENT_TIMEOUT_T1_INIT { &bslash;&n;&t;/* SCTP_STATE_EMPTY */ &bslash;&n;&t;{.fn = sctp_sf_bug, .name = &quot;sctp_sf_bug&quot;}, &bslash;&n;&t;/* SCTP_STATE_CLOSED */ &bslash;&n;&t;{.fn = sctp_sf_timer_ignore, .name = &quot;sctp_sf_timer_ignore&quot;}, &bslash;&n;&t;/* SCTP_STATE_COOKIE_WAIT */ &bslash;&n;&t;{.fn = sctp_sf_t1_timer_expire, .name = &quot;sctp_sf_t1_timer_expire&quot;}, &bslash;&n;&t;/* SCTP_STATE_COOKIE_ECHOED */ &bslash;&n;&t;{.fn = sctp_sf_timer_ignore, .name = &quot;sctp_sf_timer_ignore&quot;}, &bslash;&n;&t;/* SCTP_STATE_ESTABLISHED */ &bslash;&n;&t;{.fn = sctp_sf_timer_ignore, .name = &quot;sctp_sf_timer_ignore&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_PENDING */ &bslash;&n;&t;{.fn = sctp_sf_timer_ignore, .name = &quot;sctp_sf_timer_ignore&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_SENT */ &bslash;&n;&t;{.fn = sctp_sf_timer_ignore, .name = &quot;sctp_sf_timer_ignore&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_RECEIVED */ &bslash;&n;&t;{.fn = sctp_sf_timer_ignore, .name = &quot;sctp_sf_timer_ignore&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_ACK_SENT */ &bslash;&n;&t;{.fn = sctp_sf_timer_ignore, .name = &quot;sctp_sf_timer_ignore&quot;}, &bslash;&n;}
DECL|macro|TYPE_SCTP_EVENT_TIMEOUT_T2_SHUTDOWN
mdefine_line|#define TYPE_SCTP_EVENT_TIMEOUT_T2_SHUTDOWN { &bslash;&n;&t;/* SCTP_STATE_EMPTY */ &bslash;&n;&t;{.fn = sctp_sf_bug, .name = &quot;sctp_sf_bug&quot;}, &bslash;&n;&t;/* SCTP_STATE_CLOSED */ &bslash;&n;&t;{.fn = sctp_sf_timer_ignore, .name = &quot;sctp_sf_timer_ignore&quot;}, &bslash;&n;&t;/* SCTP_STATE_COOKIE_WAIT */ &bslash;&n;&t;{.fn = sctp_sf_timer_ignore, .name = &quot;sctp_sf_timer_ignore&quot;}, &bslash;&n;&t;/* SCTP_STATE_COOKIE_ECHOED */ &bslash;&n;&t;{.fn = sctp_sf_timer_ignore, .name = &quot;sctp_sf_timer_ignore&quot;}, &bslash;&n;&t;/* SCTP_STATE_ESTABLISHED */ &bslash;&n;&t;{.fn = sctp_sf_timer_ignore, .name = &quot;sctp_sf_timer_ignore&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_PENDING */ &bslash;&n;&t;{.fn = sctp_sf_timer_ignore, .name = &quot;sctp_sf_timer_ignore&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_SENT */ &bslash;&n;&t;{.fn = sctp_sf_t2_timer_expire, .name = &quot;sctp_sf_t2_timer_expire&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_RECEIVED */ &bslash;&n;&t;{.fn = sctp_sf_timer_ignore, .name = &quot;sctp_sf_timer_ignore&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_ACK_SENT */ &bslash;&n;&t;{.fn = sctp_sf_t2_timer_expire, .name = &quot;sctp_sf_t2_timer_expire&quot;}, &bslash;&n;}
DECL|macro|TYPE_SCTP_EVENT_TIMEOUT_T3_RTX
mdefine_line|#define TYPE_SCTP_EVENT_TIMEOUT_T3_RTX { &bslash;&n;&t;/* SCTP_STATE_EMPTY */ &bslash;&n;&t;{.fn = sctp_sf_bug, .name = &quot;sctp_sf_bug&quot;}, &bslash;&n;&t;/* SCTP_STATE_CLOSED */ &bslash;&n;&t;{.fn = sctp_sf_timer_ignore, .name = &quot;sctp_sf_timer_ignore&quot;}, &bslash;&n;&t;/* SCTP_STATE_COOKIE_WAIT */ &bslash;&n;&t;{.fn = sctp_sf_timer_ignore, .name = &quot;sctp_sf_timer_ignore&quot;}, &bslash;&n;&t;/* SCTP_STATE_COOKIE_ECHOED */ &bslash;&n;&t;{.fn = sctp_sf_do_6_3_3_rtx, .name = &quot;sctp_sf_do_6_3_3_rtx&quot;}, &bslash;&n;&t;/* SCTP_STATE_ESTABLISHED */ &bslash;&n;&t;{.fn = sctp_sf_do_6_3_3_rtx, .name = &quot;sctp_sf_do_6_3_3_rtx&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_PENDING */ &bslash;&n;&t;{.fn = sctp_sf_do_6_3_3_rtx, .name = &quot;sctp_sf_do_6_3_3_rtx&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_SENT */ &bslash;&n;&t;{.fn = sctp_sf_timer_ignore, .name = &quot;sctp_sf_timer_ignore&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_RECEIVED */ &bslash;&n;&t;{.fn = sctp_sf_do_6_3_3_rtx, .name = &quot;sctp_sf_do_6_3_3_rtx&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_ACK_SENT */ &bslash;&n;&t;{.fn = sctp_sf_timer_ignore, .name = &quot;sctp_sf_timer_ignore&quot;}, &bslash;&n;}
DECL|macro|TYPE_SCTP_EVENT_TIMEOUT_T4_RTO
mdefine_line|#define TYPE_SCTP_EVENT_TIMEOUT_T4_RTO { &bslash;&n;&t;/* SCTP_STATE_EMPTY */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_CLOSED */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_COOKIE_WAIT */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_COOKIE_ECHOED */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_ESTABLISHED */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_PENDING */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_SENT */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_RECEIVED */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_ACK_SENT */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;}
DECL|macro|TYPE_SCTP_EVENT_TIMEOUT_T5_SHUTDOWN_GUARD
mdefine_line|#define TYPE_SCTP_EVENT_TIMEOUT_T5_SHUTDOWN_GUARD { &bslash;&n;&t;/* SCTP_STATE_EMPTY */ &bslash;&n;&t;{.fn = sctp_sf_bug, .name = &quot;sctp_sf_bug&quot;}, &bslash;&n;&t;/* SCTP_STATE_CLOSED */ &bslash;&n;&t;{.fn = sctp_sf_timer_ignore, .name = &quot;sctp_sf_timer_ignore&quot;}, &bslash;&n;&t;/* SCTP_STATE_COOKIE_WAIT */ &bslash;&n;&t;{.fn = sctp_sf_timer_ignore, .name = &quot;sctp_sf_timer_ignore&quot;}, &bslash;&n;&t;/* SCTP_STATE_COOKIE_ECHOED */ &bslash;&n;&t;{.fn = sctp_sf_timer_ignore, .name = &quot;sctp_sf_timer_ignore&quot;}, &bslash;&n;&t;/* SCTP_STATE_ESTABLISHED */ &bslash;&n;&t;{.fn = sctp_sf_timer_ignore, .name = &quot;sctp_sf_timer_ignore&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_PENDING */ &bslash;&n;&t;{.fn = sctp_sf_timer_ignore, .name = &quot;sctp_sf_timer_ignore&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_SENT */ &bslash;&n;&t;{.fn = sctp_sf_t5_timer_expire, .name = &quot;sctp_sf_t5_timer_expire&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_RECEIVED */ &bslash;&n;&t;{.fn = sctp_sf_timer_ignore, .name = &quot;sctp_sf_timer_ignore&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_ACK_SENT */ &bslash;&n;&t;{.fn = sctp_sf_timer_ignore, .name = &quot;sctp_sf_timer_ignore&quot;}, &bslash;&n;}
DECL|macro|TYPE_SCTP_EVENT_TIMEOUT_HEARTBEAT
mdefine_line|#define TYPE_SCTP_EVENT_TIMEOUT_HEARTBEAT { &bslash;&n;&t;/* SCTP_STATE_EMPTY */ &bslash;&n;&t;{.fn = sctp_sf_bug, .name = &quot;sctp_sf_bug&quot;}, &bslash;&n;&t;/* SCTP_STATE_CLOSED */ &bslash;&n;&t;{.fn = sctp_sf_timer_ignore, .name = &quot;sctp_sf_timer_ignore&quot;}, &bslash;&n;&t;/* SCTP_STATE_COOKIE_WAIT */ &bslash;&n;&t;{.fn = sctp_sf_timer_ignore, .name = &quot;sctp_sf_timer_ignore&quot;}, &bslash;&n;&t;/* SCTP_STATE_COOKIE_ECHOED */ &bslash;&n;&t;{.fn = sctp_sf_timer_ignore, .name = &quot;sctp_sf_timer_ignore&quot;}, &bslash;&n;&t;/* SCTP_STATE_ESTABLISHED */ &bslash;&n;&t;{.fn = sctp_sf_sendbeat_8_3, .name = &quot;sctp_sf_sendbeat_8_3&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_PENDING */ &bslash;&n;&t;{.fn = sctp_sf_sendbeat_8_3, .name = &quot;sctp_sf_sendbeat_8_3&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_SENT */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_RECEIVED */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_ACK_SENT */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;}
DECL|macro|TYPE_SCTP_EVENT_TIMEOUT_SACK
mdefine_line|#define TYPE_SCTP_EVENT_TIMEOUT_SACK { &bslash;&n;&t;/* SCTP_STATE_EMPTY */ &bslash;&n;&t;{.fn = sctp_sf_bug, .name = &quot;sctp_sf_bug&quot;}, &bslash;&n;&t;/* SCTP_STATE_CLOSED */ &bslash;&n;&t;{.fn = sctp_sf_timer_ignore, .name = &quot;sctp_sf_timer_ignore&quot;}, &bslash;&n;&t;/* SCTP_STATE_COOKIE_WAIT */ &bslash;&n;&t;{.fn = sctp_sf_timer_ignore, .name = &quot;sctp_sf_timer_ignore&quot;}, &bslash;&n;&t;/* SCTP_STATE_COOKIE_ECHOED */ &bslash;&n;&t;{.fn = sctp_sf_timer_ignore, .name = &quot;sctp_sf_timer_ignore&quot;}, &bslash;&n;&t;/* SCTP_STATE_ESTABLISHED */ &bslash;&n;&t;{.fn = sctp_sf_do_6_2_sack, .name = &quot;sctp_sf_do_6_2_sack&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_PENDING */ &bslash;&n;&t;{.fn = sctp_sf_do_6_2_sack, .name = &quot;sctp_sf_do_6_2_sack&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_SENT */ &bslash;&n;&t;{.fn = sctp_sf_do_6_2_sack, .name = &quot;sctp_sf_do_6_2_sack&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_RECEIVED */ &bslash;&n;&t;{.fn = sctp_sf_timer_ignore, .name = &quot;sctp_sf_timer_ignore&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_ACK_SENT */ &bslash;&n;&t;{.fn = sctp_sf_timer_ignore, .name = &quot;sctp_sf_timer_ignore&quot;}, &bslash;&n;}
DECL|macro|TYPE_SCTP_EVENT_TIMEOUT_AUTOCLOSE
mdefine_line|#define TYPE_SCTP_EVENT_TIMEOUT_AUTOCLOSE { &bslash;&n;&t;/* SCTP_STATE_EMPTY */ &bslash;&n;&t;{.fn = sctp_sf_timer_ignore, .name = &quot;sctp_sf_timer_ignore&quot;}, &bslash;&n;&t;/* SCTP_STATE_CLOSED */ &bslash;&n;&t;{.fn = sctp_sf_timer_ignore, .name = &quot;sctp_sf_timer_ignore&quot;}, &bslash;&n;&t;/* SCTP_STATE_COOKIE_WAIT */ &bslash;&n;&t;{.fn = sctp_sf_timer_ignore, .name = &quot;sctp_sf_timer_ignore&quot;}, &bslash;&n;&t;/* SCTP_STATE_COOKIE_ECHOED */ &bslash;&n;&t;{.fn = sctp_sf_timer_ignore, .name = &quot;sctp_sf_timer_ignore&quot;}, &bslash;&n;&t;/* SCTP_STATE_ESTABLISHED */ &bslash;&n;&t;{.fn = sctp_sf_autoclose_timer_expire, &bslash;&n;&t; .name = &quot;sctp_sf_autoclose_timer_expire&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_PENDING */ &bslash;&n;&t;{.fn = sctp_sf_timer_ignore, .name = &quot;sctp_sf_timer_ignore&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_SENT */ &bslash;&n;&t;{.fn = sctp_sf_timer_ignore, .name = &quot;sctp_sf_timer_ignore&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_RECEIVED */ &bslash;&n;&t;{.fn = sctp_sf_timer_ignore, .name = &quot;sctp_sf_timer_ignore&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_ACK_SENT */ &bslash;&n;&t;{.fn = sctp_sf_timer_ignore, .name = &quot;sctp_sf_timer_ignore&quot;}, &bslash;&n;}
DECL|macro|TYPE_SCTP_EVENT_TIMEOUT_PMTU_RAISE
mdefine_line|#define TYPE_SCTP_EVENT_TIMEOUT_PMTU_RAISE { &bslash;&n;&t;/* SCTP_STATE_EMPTY */ &bslash;&n;&t;{.fn = sctp_sf_bug, .name = &quot;sctp_sf_bug&quot;}, &bslash;&n;&t;/* SCTP_STATE_CLOSED */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_COOKIE_WAIT */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_COOKIE_ECHOED */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_ESTABLISHED */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_PENDING */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_SENT */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_RECEIVED */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;&t;/* SCTP_STATE_SHUTDOWN_ACK_SENT */ &bslash;&n;&t;{.fn = sctp_sf_not_impl, .name = &quot;sctp_sf_not_impl&quot;}, &bslash;&n;}
DECL|variable|timeout_event_table
id|sctp_sm_table_entry_t
id|timeout_event_table
(braket
id|SCTP_NUM_TIMEOUT_TYPES
)braket
(braket
id|SCTP_STATE_NUM_STATES
)braket
op_assign
(brace
id|TYPE_SCTP_EVENT_TIMEOUT_NONE
comma
id|TYPE_SCTP_EVENT_TIMEOUT_T1_COOKIE
comma
id|TYPE_SCTP_EVENT_TIMEOUT_T1_INIT
comma
id|TYPE_SCTP_EVENT_TIMEOUT_T2_SHUTDOWN
comma
id|TYPE_SCTP_EVENT_TIMEOUT_T3_RTX
comma
id|TYPE_SCTP_EVENT_TIMEOUT_T4_RTO
comma
id|TYPE_SCTP_EVENT_TIMEOUT_T5_SHUTDOWN_GUARD
comma
id|TYPE_SCTP_EVENT_TIMEOUT_HEARTBEAT
comma
id|TYPE_SCTP_EVENT_TIMEOUT_SACK
comma
id|TYPE_SCTP_EVENT_TIMEOUT_AUTOCLOSE
comma
id|TYPE_SCTP_EVENT_TIMEOUT_PMTU_RAISE
comma
)brace
suffix:semicolon
DECL|function|sctp_chunk_event_lookup
id|sctp_sm_table_entry_t
op_star
id|sctp_chunk_event_lookup
c_func
(paren
id|sctp_cid_t
id|cid
comma
id|sctp_state_t
id|state
)paren
(brace
r_if
c_cond
(paren
id|state
OG
id|SCTP_STATE_MAX
)paren
r_return
op_amp
id|bug
suffix:semicolon
r_if
c_cond
(paren
id|cid
op_ge
l_int|0
op_logical_and
id|cid
op_le
id|SCTP_CID_BASE_MAX
)paren
(brace
r_return
op_amp
id|chunk_event_table
(braket
id|cid
)braket
(braket
id|state
)braket
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|cid
)paren
(brace
r_case
id|SCTP_CID_ASCONF
suffix:colon
r_return
op_amp
id|chunk_event_table_asconf
(braket
id|state
)braket
suffix:semicolon
r_case
id|SCTP_CID_ASCONF_ACK
suffix:colon
r_return
op_amp
id|chunk_event_table_asconf_ack
(braket
id|state
)braket
suffix:semicolon
r_default
suffix:colon
r_return
op_amp
id|chunk_event_table_unknown
(braket
id|state
)braket
suffix:semicolon
)brace
)brace
eof
