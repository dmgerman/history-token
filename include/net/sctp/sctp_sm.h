multiline_comment|/* SCTP kernel reference Implementation&n; * Copyright (c) 1999-2000 Cisco, Inc.&n; * Copyright (c) 1999-2001 Motorola, Inc.&n; * Copyright (c) 2001 Intel Corp.&n; * Copyright (c) 2001-2002 International Business Machines Corp.&n; * &n; * This file is part of the SCTP kernel reference Implementation&n; * &n; * This file is part of the implementation of the add-IP extension,&n; * based on &lt;draft-ietf-tsvwg-addip-sctp-02.txt&gt; June 29, 2001,&n; * for the SCTP kernel reference Implementation.&n; * &n; * $Header: /cvsroot/lksctp/lksctp/sctp_cvs/include/net/sctp/sctp_sm.h,v 1.34 2002/08/21 18:34:04 jgrimm Exp $&n; * &n; * These are definitions needed by the state machine.&n; * &n; * The SCTP reference implementation is free software; &n; * you can redistribute it and/or modify it under the terms of &n; * the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; * &n; * The SCTP reference implementation is distributed in the hope that it &n; * will be useful, but WITHOUT ANY WARRANTY; without even the implied&n; *                 ************************&n; * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; * See the GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with GNU CC; see the file COPYING.  If not, write to&n; * the Free Software Foundation, 59 Temple Place - Suite 330,&n; * Boston, MA 02111-1307, USA.  &n; * &n; * Please send any bug reports or fixes you make to the&n; * email addresses:&n; *    lksctp developers &lt;lksctp-developers@lists.sourceforge.net&gt;&n; * &n; * Or submit a bug report through the following website:&n; *    http://www.sf.net/projects/lksctp&n; *&n; * Written or modified by: &n; *    La Monte H.P. Yarroll &lt;piggy@acm.org&gt;&n; *    Karl Knutson &lt;karl@athena.chicago.il.us&gt;&n; *    Xingang Guo &lt;xingang.guo@intel.com&gt;&n; *    Jon Grimm &lt;jgrimm@us.ibm.com&gt;&n; *    Dajiang Zhang &lt;dajiang.zhang@nokia.com&gt;&n; *    Sridhar Samudrala &lt;sri@us.ibm.com&gt;&n; *    Daisy Chang &lt;daisyc@us.ibm.com&gt;&n; *&n; * Any bugs reported given to us we will try to fix... any fixes shared will&n; * be incorporated into the next SCTP release.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/compiler.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;net/sctp/sctp_command.h&gt;
macro_line|#include &lt;net/sctp/sctp.h&gt;
macro_line|#ifndef __sctp_sm_h__
DECL|macro|__sctp_sm_h__
mdefine_line|#define __sctp_sm_h__
multiline_comment|/*&n; * Possible values for the disposition are:&n; */
r_typedef
r_enum
(brace
DECL|enumerator|SCTP_DISPOSITION_DISCARD
id|SCTP_DISPOSITION_DISCARD
comma
multiline_comment|/* No further processing.  */
DECL|enumerator|SCTP_DISPOSITION_CONSUME
id|SCTP_DISPOSITION_CONSUME
comma
multiline_comment|/* Process return values normally.  */
DECL|enumerator|SCTP_DISPOSITION_NOMEM
id|SCTP_DISPOSITION_NOMEM
comma
multiline_comment|/* We ran out of memory--recover.  */
DECL|enumerator|SCTP_DISPOSITION_DELETE_TCB
id|SCTP_DISPOSITION_DELETE_TCB
comma
multiline_comment|/* Close the association.  */
DECL|enumerator|SCTP_DISPOSITION_ABORT
id|SCTP_DISPOSITION_ABORT
comma
multiline_comment|/* Close the association NOW.  */
DECL|enumerator|SCTP_DISPOSITION_VIOLATION
id|SCTP_DISPOSITION_VIOLATION
comma
multiline_comment|/* The peer is misbehaving.  */
DECL|enumerator|SCTP_DISPOSITION_NOT_IMPL
id|SCTP_DISPOSITION_NOT_IMPL
comma
multiline_comment|/* This entry is not implemented.  */
DECL|enumerator|SCTP_DISPOSITION_ERROR
id|SCTP_DISPOSITION_ERROR
comma
multiline_comment|/* This is plain old user error.  */
DECL|enumerator|SCTP_DISPOSITION_BUG
id|SCTP_DISPOSITION_BUG
comma
multiline_comment|/* This is a bug.  */
DECL|typedef|sctp_disposition_t
)brace
id|sctp_disposition_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|name
r_int
id|name
suffix:semicolon
DECL|member|action
r_int
id|action
suffix:semicolon
DECL|typedef|sctp_sm_command_t
)brace
id|sctp_sm_command_t
suffix:semicolon
DECL|typedef|sctp_state_fn_t
r_typedef
id|sctp_disposition_t
(paren
id|sctp_state_fn_t
)paren
(paren
r_const
id|sctp_endpoint_t
op_star
comma
r_const
id|sctp_association_t
op_star
comma
r_const
id|sctp_subtype_t
id|type
comma
r_void
op_star
id|arg
comma
id|sctp_cmd_seq_t
op_star
)paren
suffix:semicolon
DECL|typedef|sctp_timer_event_t
r_typedef
r_void
(paren
id|sctp_timer_event_t
)paren
(paren
r_int
r_int
)paren
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|fn
id|sctp_state_fn_t
op_star
id|fn
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|typedef|sctp_sm_table_entry_t
)brace
id|sctp_sm_table_entry_t
suffix:semicolon
multiline_comment|/* A naming convention of &quot;sctp_sf_xxx&quot; applies to all the state functions &n; * currently in use.&n; */
multiline_comment|/* Prototypes for generic state functions. */
DECL|variable|sctp_sf_not_impl
id|sctp_state_fn_t
id|sctp_sf_not_impl
suffix:semicolon
DECL|variable|sctp_sf_bug
id|sctp_state_fn_t
id|sctp_sf_bug
suffix:semicolon
multiline_comment|/* Prototypes for gener timer state functions. */
DECL|variable|sctp_sf_timer_ignore
id|sctp_state_fn_t
id|sctp_sf_timer_ignore
suffix:semicolon
multiline_comment|/* Prototypes for chunk state functions. */
DECL|variable|sctp_sf_do_9_1_abort
id|sctp_state_fn_t
id|sctp_sf_do_9_1_abort
suffix:semicolon
DECL|variable|sctp_sf_cookie_wait_abort
id|sctp_state_fn_t
id|sctp_sf_cookie_wait_abort
suffix:semicolon
DECL|variable|sctp_sf_cookie_echoed_abort
id|sctp_state_fn_t
id|sctp_sf_cookie_echoed_abort
suffix:semicolon
DECL|variable|sctp_sf_do_5_1B_init
id|sctp_state_fn_t
id|sctp_sf_do_5_1B_init
suffix:semicolon
DECL|variable|sctp_sf_do_5_1C_ack
id|sctp_state_fn_t
id|sctp_sf_do_5_1C_ack
suffix:semicolon
DECL|variable|sctp_sf_do_5_1D_ce
id|sctp_state_fn_t
id|sctp_sf_do_5_1D_ce
suffix:semicolon
DECL|variable|sctp_sf_do_5_1E_ca
id|sctp_state_fn_t
id|sctp_sf_do_5_1E_ca
suffix:semicolon
DECL|variable|sctp_sf_do_4_C
id|sctp_state_fn_t
id|sctp_sf_do_4_C
suffix:semicolon
DECL|variable|sctp_sf_eat_data_6_2
id|sctp_state_fn_t
id|sctp_sf_eat_data_6_2
suffix:semicolon
DECL|variable|sctp_sf_eat_data_fast_4_4
id|sctp_state_fn_t
id|sctp_sf_eat_data_fast_4_4
suffix:semicolon
DECL|variable|sctp_sf_eat_sack_6_2
id|sctp_state_fn_t
id|sctp_sf_eat_sack_6_2
suffix:semicolon
DECL|variable|sctp_sf_tabort_8_4_8
id|sctp_state_fn_t
id|sctp_sf_tabort_8_4_8
suffix:semicolon
DECL|variable|sctp_sf_operr_notify
id|sctp_state_fn_t
id|sctp_sf_operr_notify
suffix:semicolon
DECL|variable|sctp_sf_t1_timer_expire
id|sctp_state_fn_t
id|sctp_sf_t1_timer_expire
suffix:semicolon
DECL|variable|sctp_sf_t2_timer_expire
id|sctp_state_fn_t
id|sctp_sf_t2_timer_expire
suffix:semicolon
DECL|variable|sctp_sf_sendbeat_8_3
id|sctp_state_fn_t
id|sctp_sf_sendbeat_8_3
suffix:semicolon
DECL|variable|sctp_sf_beat_8_3
id|sctp_state_fn_t
id|sctp_sf_beat_8_3
suffix:semicolon
DECL|variable|sctp_sf_backbeat_8_3
id|sctp_state_fn_t
id|sctp_sf_backbeat_8_3
suffix:semicolon
DECL|variable|sctp_sf_do_9_2_final
id|sctp_state_fn_t
id|sctp_sf_do_9_2_final
suffix:semicolon
DECL|variable|sctp_sf_do_9_2_shutdown
id|sctp_state_fn_t
id|sctp_sf_do_9_2_shutdown
suffix:semicolon
DECL|variable|sctp_sf_do_ecn_cwr
id|sctp_state_fn_t
id|sctp_sf_do_ecn_cwr
suffix:semicolon
DECL|variable|sctp_sf_do_ecne
id|sctp_state_fn_t
id|sctp_sf_do_ecne
suffix:semicolon
DECL|variable|sctp_sf_ootb
id|sctp_state_fn_t
id|sctp_sf_ootb
suffix:semicolon
DECL|variable|sctp_sf_shut_8_4_5
id|sctp_state_fn_t
id|sctp_sf_shut_8_4_5
suffix:semicolon
DECL|variable|sctp_sf_pdiscard
id|sctp_state_fn_t
id|sctp_sf_pdiscard
suffix:semicolon
DECL|variable|sctp_sf_violation
id|sctp_state_fn_t
id|sctp_sf_violation
suffix:semicolon
DECL|variable|sctp_sf_discard_chunk
id|sctp_state_fn_t
id|sctp_sf_discard_chunk
suffix:semicolon
DECL|variable|sctp_sf_do_5_2_1_siminit
id|sctp_state_fn_t
id|sctp_sf_do_5_2_1_siminit
suffix:semicolon
DECL|variable|sctp_sf_do_5_2_2_dupinit
id|sctp_state_fn_t
id|sctp_sf_do_5_2_2_dupinit
suffix:semicolon
DECL|variable|sctp_sf_do_5_2_4_dupcook
id|sctp_state_fn_t
id|sctp_sf_do_5_2_4_dupcook
suffix:semicolon
multiline_comment|/* Prototypes for primitive event state functions.  */
DECL|variable|sctp_sf_do_prm_asoc
id|sctp_state_fn_t
id|sctp_sf_do_prm_asoc
suffix:semicolon
DECL|variable|sctp_sf_do_prm_send
id|sctp_state_fn_t
id|sctp_sf_do_prm_send
suffix:semicolon
DECL|variable|sctp_sf_do_9_2_prm_shutdown
id|sctp_state_fn_t
id|sctp_sf_do_9_2_prm_shutdown
suffix:semicolon
DECL|variable|sctp_sf_cookie_wait_prm_shutdown
id|sctp_state_fn_t
id|sctp_sf_cookie_wait_prm_shutdown
suffix:semicolon
DECL|variable|sctp_sf_cookie_echoed_prm_shutdown
id|sctp_state_fn_t
id|sctp_sf_cookie_echoed_prm_shutdown
suffix:semicolon
DECL|variable|sctp_sf_do_9_1_prm_abort
id|sctp_state_fn_t
id|sctp_sf_do_9_1_prm_abort
suffix:semicolon
DECL|variable|sctp_sf_cookie_wait_prm_abort
id|sctp_state_fn_t
id|sctp_sf_cookie_wait_prm_abort
suffix:semicolon
DECL|variable|sctp_sf_cookie_echoed_prm_abort
id|sctp_state_fn_t
id|sctp_sf_cookie_echoed_prm_abort
suffix:semicolon
DECL|variable|sctp_sf_error_closed
id|sctp_state_fn_t
id|sctp_sf_error_closed
suffix:semicolon
DECL|variable|sctp_sf_error_shutdown
id|sctp_state_fn_t
id|sctp_sf_error_shutdown
suffix:semicolon
DECL|variable|sctp_sf_ignore_primitive
id|sctp_state_fn_t
id|sctp_sf_ignore_primitive
suffix:semicolon
multiline_comment|/* Prototypes for other event state functions.  */
DECL|variable|sctp_sf_do_9_2_start_shutdown
id|sctp_state_fn_t
id|sctp_sf_do_9_2_start_shutdown
suffix:semicolon
DECL|variable|sctp_sf_do_9_2_shutdown_ack
id|sctp_state_fn_t
id|sctp_sf_do_9_2_shutdown_ack
suffix:semicolon
DECL|variable|sctp_sf_ignore_other
id|sctp_state_fn_t
id|sctp_sf_ignore_other
suffix:semicolon
multiline_comment|/* Prototypes for timeout event state functions.  */
DECL|variable|sctp_sf_do_6_3_3_rtx
id|sctp_state_fn_t
id|sctp_sf_do_6_3_3_rtx
suffix:semicolon
DECL|variable|sctp_sf_do_6_2_sack
id|sctp_state_fn_t
id|sctp_sf_do_6_2_sack
suffix:semicolon
DECL|variable|sctp_sf_autoclose_timer_expire
id|sctp_state_fn_t
id|sctp_sf_autoclose_timer_expire
suffix:semicolon
multiline_comment|/* These are state functions which are either obsolete or not in use yet. &n; * If any of these functions needs to be revived, it should be renamed with&n; * the &quot;sctp_sf_xxx&quot; prefix, and be moved to the above prototype groups.&n; */
multiline_comment|/* Prototypes for chunk state functions.  Not in use. */
DECL|variable|sctp_sf_do_5_2_6_stale
id|sctp_state_fn_t
id|sctp_sf_do_5_2_6_stale
suffix:semicolon
DECL|variable|sctp_sf_do_9_2_reshutack
id|sctp_state_fn_t
id|sctp_sf_do_9_2_reshutack
suffix:semicolon
DECL|variable|sctp_sf_do_9_2_reshut
id|sctp_state_fn_t
id|sctp_sf_do_9_2_reshut
suffix:semicolon
DECL|variable|sctp_sf_do_9_2_shutack
id|sctp_state_fn_t
id|sctp_sf_do_9_2_shutack
suffix:semicolon
DECL|variable|lucky
id|sctp_state_fn_t
id|lucky
suffix:semicolon
DECL|variable|other_stupid
id|sctp_state_fn_t
id|other_stupid
suffix:semicolon
multiline_comment|/* Prototypes for timeout event state functions.  Not in use. */
DECL|variable|sctp_do_4_2_reinit
id|sctp_state_fn_t
id|sctp_do_4_2_reinit
suffix:semicolon
DECL|variable|sctp_do_4_3_reecho
id|sctp_state_fn_t
id|sctp_do_4_3_reecho
suffix:semicolon
DECL|variable|sctp_do_9_2_reshut
id|sctp_state_fn_t
id|sctp_do_9_2_reshut
suffix:semicolon
DECL|variable|sctp_do_9_2_reshutack
id|sctp_state_fn_t
id|sctp_do_9_2_reshutack
suffix:semicolon
DECL|variable|sctp_do_8_3_hb_err
id|sctp_state_fn_t
id|sctp_do_8_3_hb_err
suffix:semicolon
DECL|variable|sctp_heartoff
id|sctp_state_fn_t
id|sctp_heartoff
suffix:semicolon
multiline_comment|/* Prototypes for addip related state functions.  Not in use. */
DECL|variable|sctp_addip_do_asconf
id|sctp_state_fn_t
id|sctp_addip_do_asconf
suffix:semicolon
DECL|variable|sctp_addip_do_asconf_ack
id|sctp_state_fn_t
id|sctp_addip_do_asconf_ack
suffix:semicolon
multiline_comment|/* Prototypes for utility support functions.  */
r_uint8
id|sctp_get_chunk_type
c_func
(paren
id|sctp_chunk_t
op_star
id|chunk
)paren
suffix:semicolon
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
suffix:semicolon
id|time_t
id|timeval_sub
c_func
(paren
r_struct
id|timeval
op_star
comma
r_struct
id|timeval
op_star
)paren
suffix:semicolon
id|sctp_association_t
op_star
id|sctp_make_temp_asoc
c_func
(paren
r_const
id|sctp_endpoint_t
op_star
comma
id|sctp_chunk_t
op_star
comma
r_const
r_int
id|priority
)paren
suffix:semicolon
r_uint32
id|sctp_generate_verification_tag
c_func
(paren
r_void
)paren
suffix:semicolon
id|sctpParam_t
id|sctp_get_my_addrs_raw
c_func
(paren
r_const
id|sctp_association_t
op_star
comma
r_const
r_int
id|priority
comma
r_int
op_star
id|addrs_len
)paren
suffix:semicolon
r_void
id|sctp_populate_tie_tags
c_func
(paren
r_uint8
op_star
id|cookie
comma
r_uint32
id|curTag
comma
r_uint32
id|hisTag
)paren
suffix:semicolon
multiline_comment|/* Prototypes for chunk-building functions.  */
id|sctp_chunk_t
op_star
id|sctp_make_init
c_func
(paren
r_const
id|sctp_association_t
op_star
comma
r_const
id|sctp_bind_addr_t
op_star
comma
r_int
id|priority
)paren
suffix:semicolon
id|sctp_chunk_t
op_star
id|sctp_make_init_ack
c_func
(paren
r_const
id|sctp_association_t
op_star
comma
r_const
id|sctp_chunk_t
op_star
comma
r_const
r_int
id|priority
)paren
suffix:semicolon
id|sctp_chunk_t
op_star
id|sctp_make_cookie_echo
c_func
(paren
r_const
id|sctp_association_t
op_star
comma
r_const
id|sctp_chunk_t
op_star
)paren
suffix:semicolon
id|sctp_chunk_t
op_star
id|sctp_make_cookie_ack
c_func
(paren
r_const
id|sctp_association_t
op_star
comma
r_const
id|sctp_chunk_t
op_star
)paren
suffix:semicolon
id|sctp_chunk_t
op_star
id|sctp_make_cwr
c_func
(paren
r_const
id|sctp_association_t
op_star
comma
r_const
r_uint32
id|lowest_tsn
comma
r_const
id|sctp_chunk_t
op_star
)paren
suffix:semicolon
id|sctp_chunk_t
op_star
id|sctp_make_datafrag
c_func
(paren
id|sctp_association_t
op_star
comma
r_const
r_struct
id|sctp_sndrcvinfo
op_star
id|sinfo
comma
r_int
id|len
comma
r_const
r_uint8
op_star
id|data
comma
r_uint8
id|flags
comma
r_uint16
id|ssn
)paren
suffix:semicolon
id|sctp_chunk_t
op_star
id|sctp_make_datafrag_empty
c_func
(paren
id|sctp_association_t
op_star
comma
r_const
r_struct
id|sctp_sndrcvinfo
op_star
id|sinfo
comma
r_int
id|len
comma
r_const
r_uint8
id|flags
comma
r_uint16
id|ssn
)paren
suffix:semicolon
id|sctp_chunk_t
op_star
id|sctp_make_data
c_func
(paren
id|sctp_association_t
op_star
comma
r_const
r_struct
id|sctp_sndrcvinfo
op_star
id|sinfo
comma
r_int
id|len
comma
r_const
r_uint8
op_star
id|data
)paren
suffix:semicolon
id|sctp_chunk_t
op_star
id|sctp_make_data_empty
c_func
(paren
id|sctp_association_t
op_star
comma
r_const
r_struct
id|sctp_sndrcvinfo
op_star
comma
r_int
id|len
)paren
suffix:semicolon
id|sctp_chunk_t
op_star
id|sctp_make_ecne
c_func
(paren
r_const
id|sctp_association_t
op_star
comma
r_const
r_uint32
)paren
suffix:semicolon
id|sctp_chunk_t
op_star
id|sctp_make_sack
c_func
(paren
r_const
id|sctp_association_t
op_star
)paren
suffix:semicolon
id|sctp_chunk_t
op_star
id|sctp_make_shutdown
c_func
(paren
r_const
id|sctp_association_t
op_star
id|asoc
)paren
suffix:semicolon
id|sctp_chunk_t
op_star
id|sctp_make_shutdown_ack
c_func
(paren
r_const
id|sctp_association_t
op_star
id|asoc
comma
r_const
id|sctp_chunk_t
op_star
)paren
suffix:semicolon
id|sctp_chunk_t
op_star
id|sctp_make_shutdown_complete
c_func
(paren
r_const
id|sctp_association_t
op_star
comma
r_const
id|sctp_chunk_t
op_star
)paren
suffix:semicolon
r_void
id|sctp_init_cause
c_func
(paren
id|sctp_chunk_t
op_star
comma
r_uint16
id|cause
comma
r_const
r_void
op_star
comma
r_int
)paren
suffix:semicolon
id|sctp_chunk_t
op_star
id|sctp_make_abort
c_func
(paren
r_const
id|sctp_association_t
op_star
comma
r_const
id|sctp_chunk_t
op_star
comma
r_const
r_int
id|hint
)paren
suffix:semicolon
id|sctp_chunk_t
op_star
id|sctp_make_abort_no_data
c_func
(paren
r_const
id|sctp_association_t
op_star
comma
r_const
id|sctp_chunk_t
op_star
comma
r_uint32
id|tsn
)paren
suffix:semicolon
id|sctp_chunk_t
op_star
id|sctp_make_heartbeat
c_func
(paren
r_const
id|sctp_association_t
op_star
comma
r_const
id|sctp_transport_t
op_star
comma
r_const
r_void
op_star
id|payload
comma
r_const
r_int
id|paylen
)paren
suffix:semicolon
id|sctp_chunk_t
op_star
id|sctp_make_heartbeat_ack
c_func
(paren
r_const
id|sctp_association_t
op_star
comma
r_const
id|sctp_chunk_t
op_star
comma
r_const
r_void
op_star
id|payload
comma
r_const
r_int
id|paylen
)paren
suffix:semicolon
id|sctp_chunk_t
op_star
id|sctp_make_op_error
c_func
(paren
r_const
id|sctp_association_t
op_star
comma
r_const
id|sctp_chunk_t
op_star
id|chunk
comma
r_uint16
id|cause_code
comma
r_const
r_void
op_star
id|payload
comma
r_int
id|paylen
)paren
suffix:semicolon
r_void
id|sctp_chunk_assign_tsn
c_func
(paren
id|sctp_chunk_t
op_star
)paren
suffix:semicolon
multiline_comment|/* Prototypes for statetable processing. */
r_int
id|sctp_do_sm
c_func
(paren
id|sctp_event_t
id|event_type
comma
id|sctp_subtype_t
id|subtype
comma
id|sctp_state_t
id|state
comma
id|sctp_endpoint_t
op_star
comma
id|sctp_association_t
op_star
id|asoc
comma
r_void
op_star
id|event_arg
comma
r_int
id|priority
)paren
suffix:semicolon
r_int
id|sctp_side_effects
c_func
(paren
id|sctp_event_t
id|event_type
comma
id|sctp_subtype_t
id|subtype
comma
id|sctp_state_t
id|state
comma
id|sctp_endpoint_t
op_star
comma
id|sctp_association_t
op_star
id|asoc
comma
r_void
op_star
id|event_arg
comma
id|sctp_disposition_t
id|status
comma
id|sctp_cmd_seq_t
op_star
id|commands
comma
r_int
id|priority
)paren
suffix:semicolon
multiline_comment|/* 2nd level prototypes */
r_int
id|sctp_cmd_interpreter
c_func
(paren
id|sctp_event_t
id|event_type
comma
id|sctp_subtype_t
id|subtype
comma
id|sctp_state_t
id|state
comma
id|sctp_endpoint_t
op_star
id|ep
comma
id|sctp_association_t
op_star
id|asoc
comma
r_void
op_star
id|event_arg
comma
id|sctp_disposition_t
id|status
comma
id|sctp_cmd_seq_t
op_star
id|retval
comma
r_int
id|priority
)paren
suffix:semicolon
r_int
id|sctp_gen_sack
c_func
(paren
id|sctp_association_t
op_star
comma
r_int
id|force
comma
id|sctp_cmd_seq_t
op_star
)paren
suffix:semicolon
r_void
id|sctp_do_TSNdup
c_func
(paren
id|sctp_association_t
op_star
comma
id|sctp_chunk_t
op_star
comma
r_int
id|gap
)paren
suffix:semicolon
r_void
id|sctp_generate_t3_rtx_event
c_func
(paren
r_int
r_int
id|peer
)paren
suffix:semicolon
r_void
id|sctp_generate_heartbeat_event
c_func
(paren
r_int
r_int
id|peer
)paren
suffix:semicolon
id|sctp_sackhdr_t
op_star
id|sctp_sm_pull_sack
c_func
(paren
id|sctp_chunk_t
op_star
)paren
suffix:semicolon
id|sctp_cookie_param_t
op_star
id|sctp_pack_cookie
c_func
(paren
r_const
id|sctp_endpoint_t
op_star
comma
r_const
id|sctp_association_t
op_star
comma
r_const
id|sctp_chunk_t
op_star
comma
r_int
op_star
id|cookie_len
comma
r_const
r_uint8
op_star
comma
r_int
id|addrs_len
)paren
suffix:semicolon
id|sctp_association_t
op_star
id|sctp_unpack_cookie
c_func
(paren
r_const
id|sctp_endpoint_t
op_star
comma
r_const
id|sctp_association_t
op_star
comma
id|sctp_chunk_t
op_star
comma
r_int
id|priority
comma
r_int
op_star
id|err
)paren
suffix:semicolon
r_int
id|sctp_addip_addr_config
c_func
(paren
id|sctp_association_t
op_star
comma
id|sctp_param_t
comma
r_struct
id|sockaddr_storage
op_star
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* 3rd level prototypes */
r_uint32
id|sctp_generate_tag
c_func
(paren
r_const
id|sctp_endpoint_t
op_star
)paren
suffix:semicolon
r_uint32
id|sctp_generate_tsn
c_func
(paren
r_const
id|sctp_endpoint_t
op_star
)paren
suffix:semicolon
multiline_comment|/* 4th level prototypes */
r_void
id|sctp_param2sockaddr
c_func
(paren
id|sockaddr_storage_t
op_star
id|addr
comma
r_const
id|sctpParam_t
id|param
comma
r_uint16
id|port
)paren
suffix:semicolon
r_int
id|sctp_addr2sockaddr
c_func
(paren
r_const
id|sctpParam_t
comma
id|sockaddr_storage_t
op_star
)paren
suffix:semicolon
r_int
id|sockaddr2sctp_addr
c_func
(paren
r_const
id|sockaddr_storage_t
op_star
comma
id|sctpParam_t
)paren
suffix:semicolon
multiline_comment|/* Extern declarations for major data structures.  */
id|sctp_sm_table_entry_t
op_star
id|sctp_chunk_event_lookup
c_func
(paren
id|sctp_cid_t
comma
id|sctp_state_t
)paren
suffix:semicolon
r_extern
id|sctp_sm_table_entry_t
id|primitive_event_table
(braket
id|SCTP_NUM_PRIMITIVE_TYPES
)braket
(braket
id|SCTP_STATE_NUM_STATES
)braket
suffix:semicolon
r_extern
id|sctp_sm_table_entry_t
id|other_event_table
(braket
id|SCTP_NUM_OTHER_TYPES
)braket
(braket
id|SCTP_STATE_NUM_STATES
)braket
suffix:semicolon
r_extern
id|sctp_sm_table_entry_t
id|timeout_event_table
(braket
id|SCTP_NUM_TIMEOUT_TYPES
)braket
(braket
id|SCTP_STATE_NUM_STATES
)braket
suffix:semicolon
r_extern
id|sctp_timer_event_t
op_star
id|sctp_timer_events
(braket
id|SCTP_NUM_TIMEOUT_TYPES
)braket
suffix:semicolon
multiline_comment|/* These are some handy utility macros... */
multiline_comment|/* Get the size of a DATA chunk payload. */
r_static
r_inline
r_uint16
DECL|function|sctp_data_size
id|sctp_data_size
c_func
(paren
id|sctp_chunk_t
op_star
id|chunk
)paren
(brace
r_uint16
id|size
suffix:semicolon
id|size
op_assign
id|ntohs
c_func
(paren
id|chunk-&gt;chunk_hdr-&gt;length
)paren
suffix:semicolon
id|size
op_sub_assign
r_sizeof
(paren
id|sctp_data_chunk_t
)paren
suffix:semicolon
r_return
id|size
suffix:semicolon
)brace
multiline_comment|/* sctp_data_size( ) */
multiline_comment|/* Compare two TSNs */
multiline_comment|/* RFC 1982 - Serial Number Arithmetic&n; *&n; * 2. Comparison&n; *  Then, s1 is said to be equal to s2 if and only if i1 is equal to i2,&n; *  in all other cases, s1 is not equal to s2.&n; *&n; * s1 is said to be less than s2 if, and only if, s1 is not equal to s2,&n; * and&n; *&n; *      (i1 &lt; i2 and i2 - i1 &lt; 2^(SERIAL_BITS - 1)) or&n; *      (i1 &gt; i2 and i1 - i2 &gt; 2^(SERIAL_BITS - 1))&n; *&n; * s1 is said to be greater than s2 if, and only if, s1 is not equal to&n; * s2, and&n; *&n; *      (i1 &lt; i2 and i2 - i1 &gt; 2^(SERIAL_BITS - 1)) or&n; *      (i1 &gt; i2 and i1 - i2 &lt; 2^(SERIAL_BITS - 1)) &n; */
multiline_comment|/*&n; * RFC 2960&n; *  1.6 Serial Number Arithmetic &n; *&n; * Comparisons and arithmetic on TSNs in this document SHOULD use Serial&n; * Number Arithmetic as defined in [RFC1982] where SERIAL_BITS = 32.&n; */
r_enum
(brace
DECL|enumerator|TSN_SIGN_BIT
id|TSN_SIGN_BIT
op_assign
(paren
l_int|1
op_lshift
l_int|31
)paren
)brace
suffix:semicolon
r_static
r_inline
r_int
DECL|function|TSN_lt
id|TSN_lt
c_func
(paren
id|__u32
id|s
comma
id|__u32
id|t
)paren
(brace
r_return
(paren
(paren
(paren
id|s
)paren
op_minus
(paren
id|t
)paren
)paren
op_amp
id|TSN_SIGN_BIT
)paren
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|TSN_lte
id|TSN_lte
c_func
(paren
id|__u32
id|s
comma
id|__u32
id|t
)paren
(brace
r_return
(paren
(paren
(paren
id|s
)paren
op_eq
(paren
id|t
)paren
)paren
op_logical_or
(paren
(paren
(paren
id|s
)paren
op_minus
(paren
id|t
)paren
)paren
op_amp
id|TSN_SIGN_BIT
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Compare two SSNs */
multiline_comment|/*&n; * RFC 2960&n; *  1.6 Serial Number Arithmetic &n; *&n; * Comparisons and arithmetic on Stream Sequence Numbers in this document &n; * SHOULD use Serial Number Arithmetic as defined in [RFC1982] where &n; * SERIAL_BITS = 16.&n; */
r_enum
(brace
DECL|enumerator|SSN_SIGN_BIT
id|SSN_SIGN_BIT
op_assign
(paren
l_int|1
op_lshift
l_int|15
)paren
)brace
suffix:semicolon
r_static
r_inline
r_int
DECL|function|SSN_lt
id|SSN_lt
c_func
(paren
id|__u16
id|s
comma
id|__u16
id|t
)paren
(brace
r_return
(paren
(paren
(paren
id|s
)paren
op_minus
(paren
id|t
)paren
)paren
op_amp
id|SSN_SIGN_BIT
)paren
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|SSN_lte
id|SSN_lte
c_func
(paren
id|__u16
id|s
comma
id|__u16
id|t
)paren
(brace
r_return
(paren
(paren
(paren
id|s
)paren
op_eq
(paren
id|t
)paren
)paren
op_logical_or
(paren
(paren
(paren
id|s
)paren
op_minus
(paren
id|t
)paren
)paren
op_amp
id|SSN_SIGN_BIT
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Run sctp_add_cmd() generating a BUG() if there is a failure.  */
r_static
r_inline
r_void
DECL|function|sctp_add_cmd_sf
id|sctp_add_cmd_sf
c_func
(paren
id|sctp_cmd_seq_t
op_star
id|seq
comma
id|sctp_verb_t
id|verb
comma
id|sctp_arg_t
id|obj
)paren
(brace
r_if
c_cond
(paren
id|unlikely
c_func
(paren
op_logical_neg
id|sctp_add_cmd
c_func
(paren
id|seq
comma
id|verb
comma
id|obj
)paren
)paren
)paren
(brace
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* sctp_add_cmd_sf() */
macro_line|#endif /* __sctp_sm_h__ */
eof
