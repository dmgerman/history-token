multiline_comment|/* SCTP kernel reference Implementation&n; * (C) Copyright IBM Corp. 2001, 2004&n; * Copyright (C) 1999-2001 Cisco, Motorola&n; *&n; * This file is part of the SCTP kernel reference Implementation&n; *&n; * These are the definitions needed for the command object.&n; *&n; * The SCTP reference implementation  is free software;&n; * you can redistribute it and/or modify it under the terms of&n; * the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; *&n; * the SCTP reference implementation  is distributed in the hope that it&n; * will be useful, but WITHOUT ANY WARRANTY; without even the implied&n; *                 ************************&n; * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; * See the GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with GNU CC; see the file COPYING.  If not, write to&n; * the Free Software Foundation, 59 Temple Place - Suite 330,&n; * Boston, MA 02111-1307, USA.&n; *&n; * Please send any bug reports or fixes you make to one of the&n; * following email addresses:&n; *&n; * La Monte H.P. Yarroll &lt;piggy@acm.org&gt;&n; * Karl Knutson &lt;karl@athena.chicago.il.us&gt;&n; * Ardelle Fan &lt;ardelle.fan@intel.com&gt;&n; * Sridhar Samudrala &lt;sri@us.ibm.com&gt;&n; *&n; * Any bugs reported given to us we will try to fix... any fixes shared will&n; * be incorporated into the next SCTP release.&n; */
macro_line|#ifndef __net_sctp_command_h__
DECL|macro|__net_sctp_command_h__
mdefine_line|#define __net_sctp_command_h__
macro_line|#include &lt;net/sctp/constants.h&gt;
macro_line|#include &lt;net/sctp/structs.h&gt;
r_typedef
r_enum
(brace
DECL|enumerator|SCTP_CMD_NOP
id|SCTP_CMD_NOP
op_assign
l_int|0
comma
multiline_comment|/* Do nothing. */
DECL|enumerator|SCTP_CMD_NEW_ASOC
id|SCTP_CMD_NEW_ASOC
comma
multiline_comment|/* Register a new association.  */
DECL|enumerator|SCTP_CMD_DELETE_TCB
id|SCTP_CMD_DELETE_TCB
comma
multiline_comment|/* Delete the current association. */
DECL|enumerator|SCTP_CMD_NEW_STATE
id|SCTP_CMD_NEW_STATE
comma
multiline_comment|/* Enter a new state.  */
DECL|enumerator|SCTP_CMD_REPORT_TSN
id|SCTP_CMD_REPORT_TSN
comma
multiline_comment|/* Record the arrival of a TSN.  */
DECL|enumerator|SCTP_CMD_GEN_SACK
id|SCTP_CMD_GEN_SACK
comma
multiline_comment|/* Send a Selective ACK (maybe).  */
DECL|enumerator|SCTP_CMD_PROCESS_SACK
id|SCTP_CMD_PROCESS_SACK
comma
multiline_comment|/* Process an inbound SACK.  */
DECL|enumerator|SCTP_CMD_GEN_INIT_ACK
id|SCTP_CMD_GEN_INIT_ACK
comma
multiline_comment|/* Generate an INIT ACK chunk.  */
DECL|enumerator|SCTP_CMD_PEER_INIT
id|SCTP_CMD_PEER_INIT
comma
multiline_comment|/* Process a INIT from the peer.  */
DECL|enumerator|SCTP_CMD_GEN_COOKIE_ECHO
id|SCTP_CMD_GEN_COOKIE_ECHO
comma
multiline_comment|/* Generate a COOKIE ECHO chunk. */
DECL|enumerator|SCTP_CMD_CHUNK_ULP
id|SCTP_CMD_CHUNK_ULP
comma
multiline_comment|/* Send a chunk to the sockets layer.  */
DECL|enumerator|SCTP_CMD_EVENT_ULP
id|SCTP_CMD_EVENT_ULP
comma
multiline_comment|/* Send a notification to the sockets layer. */
DECL|enumerator|SCTP_CMD_REPLY
id|SCTP_CMD_REPLY
comma
multiline_comment|/* Send a chunk to our peer.  */
DECL|enumerator|SCTP_CMD_SEND_PKT
id|SCTP_CMD_SEND_PKT
comma
multiline_comment|/* Send a full packet to our peer.  */
DECL|enumerator|SCTP_CMD_RETRAN
id|SCTP_CMD_RETRAN
comma
multiline_comment|/* Mark a transport for retransmission.  */
DECL|enumerator|SCTP_CMD_ECN_CE
id|SCTP_CMD_ECN_CE
comma
multiline_comment|/* Do delayed CE processing.   */
DECL|enumerator|SCTP_CMD_ECN_ECNE
id|SCTP_CMD_ECN_ECNE
comma
multiline_comment|/* Do delayed ECNE processing. */
DECL|enumerator|SCTP_CMD_ECN_CWR
id|SCTP_CMD_ECN_CWR
comma
multiline_comment|/* Do delayed CWR processing.  */
DECL|enumerator|SCTP_CMD_TIMER_START
id|SCTP_CMD_TIMER_START
comma
multiline_comment|/* Start a timer.  */
DECL|enumerator|SCTP_CMD_TIMER_RESTART
id|SCTP_CMD_TIMER_RESTART
comma
multiline_comment|/* Restart a timer. */
DECL|enumerator|SCTP_CMD_TIMER_STOP
id|SCTP_CMD_TIMER_STOP
comma
multiline_comment|/* Stop a timer. */
DECL|enumerator|SCTP_CMD_COUNTER_RESET
id|SCTP_CMD_COUNTER_RESET
comma
multiline_comment|/* Reset a counter. */
DECL|enumerator|SCTP_CMD_COUNTER_INC
id|SCTP_CMD_COUNTER_INC
comma
multiline_comment|/* Increment a counter. */
DECL|enumerator|SCTP_CMD_INIT_RESTART
id|SCTP_CMD_INIT_RESTART
comma
multiline_comment|/* High level, do init timer work. */
DECL|enumerator|SCTP_CMD_INIT_FAILED
id|SCTP_CMD_INIT_FAILED
comma
multiline_comment|/* High level, do init failure work. */
DECL|enumerator|SCTP_CMD_REPORT_DUP
id|SCTP_CMD_REPORT_DUP
comma
multiline_comment|/* Report a duplicate TSN.  */
DECL|enumerator|SCTP_CMD_STRIKE
id|SCTP_CMD_STRIKE
comma
multiline_comment|/* Mark a strike against a transport.  */
DECL|enumerator|SCTP_CMD_TRANSMIT
id|SCTP_CMD_TRANSMIT
comma
multiline_comment|/* Transmit the outqueue. */
DECL|enumerator|SCTP_CMD_HB_TIMERS_START
id|SCTP_CMD_HB_TIMERS_START
comma
multiline_comment|/* Start the heartbeat timers. */
DECL|enumerator|SCTP_CMD_HB_TIMER_UPDATE
id|SCTP_CMD_HB_TIMER_UPDATE
comma
multiline_comment|/* Update a heartbeat timers.  */
DECL|enumerator|SCTP_CMD_HB_TIMERS_STOP
id|SCTP_CMD_HB_TIMERS_STOP
comma
multiline_comment|/* Stop the heartbeat timers.  */
DECL|enumerator|SCTP_CMD_TRANSPORT_RESET
id|SCTP_CMD_TRANSPORT_RESET
comma
multiline_comment|/* Reset the status of a transport. */
DECL|enumerator|SCTP_CMD_TRANSPORT_ON
id|SCTP_CMD_TRANSPORT_ON
comma
multiline_comment|/* Mark the transport as active. */
DECL|enumerator|SCTP_CMD_REPORT_ERROR
id|SCTP_CMD_REPORT_ERROR
comma
multiline_comment|/* Pass this error back out of the sm. */
DECL|enumerator|SCTP_CMD_REPORT_BAD_TAG
id|SCTP_CMD_REPORT_BAD_TAG
comma
multiline_comment|/* Verification tags didn&squot;t match. */
DECL|enumerator|SCTP_CMD_PROCESS_CTSN
id|SCTP_CMD_PROCESS_CTSN
comma
multiline_comment|/* Sideeffect from shutdown. */
DECL|enumerator|SCTP_CMD_ASSOC_FAILED
id|SCTP_CMD_ASSOC_FAILED
comma
multiline_comment|/* Handle association failure. */
DECL|enumerator|SCTP_CMD_DISCARD_PACKET
id|SCTP_CMD_DISCARD_PACKET
comma
multiline_comment|/* Discard the whole packet. */
DECL|enumerator|SCTP_CMD_GEN_SHUTDOWN
id|SCTP_CMD_GEN_SHUTDOWN
comma
multiline_comment|/* Generate a SHUTDOWN chunk. */
DECL|enumerator|SCTP_CMD_UPDATE_ASSOC
id|SCTP_CMD_UPDATE_ASSOC
comma
multiline_comment|/* Update association information. */
DECL|enumerator|SCTP_CMD_PURGE_OUTQUEUE
id|SCTP_CMD_PURGE_OUTQUEUE
comma
multiline_comment|/* Purge all data waiting to be sent. */
DECL|enumerator|SCTP_CMD_SETUP_T2
id|SCTP_CMD_SETUP_T2
comma
multiline_comment|/* Hi-level, setup T2-shutdown parms.  */
DECL|enumerator|SCTP_CMD_RTO_PENDING
id|SCTP_CMD_RTO_PENDING
comma
multiline_comment|/* Set transport&squot;s rto_pending. */
DECL|enumerator|SCTP_CMD_PART_DELIVER
id|SCTP_CMD_PART_DELIVER
comma
multiline_comment|/* Partial data delivery considerations. */
DECL|enumerator|SCTP_CMD_RENEGE
id|SCTP_CMD_RENEGE
comma
multiline_comment|/* Renege data on an association. */
DECL|enumerator|SCTP_CMD_SETUP_T4
id|SCTP_CMD_SETUP_T4
comma
multiline_comment|/* ADDIP, setup T4 RTO timer parms. */
DECL|enumerator|SCTP_CMD_PROCESS_OPERR
id|SCTP_CMD_PROCESS_OPERR
comma
multiline_comment|/* Process an ERROR chunk. */
DECL|enumerator|SCTP_CMD_REPORT_FWDTSN
id|SCTP_CMD_REPORT_FWDTSN
comma
multiline_comment|/* Report new cumulative TSN Ack. */
DECL|enumerator|SCTP_CMD_PROCESS_FWDTSN
id|SCTP_CMD_PROCESS_FWDTSN
comma
multiline_comment|/* Skips were reported, so process further. */
DECL|enumerator|SCTP_CMD_CLEAR_INIT_TAG
id|SCTP_CMD_CLEAR_INIT_TAG
comma
multiline_comment|/* Clears association peer&squot;s inittag. */
DECL|enumerator|SCTP_CMD_DEL_NON_PRIMARY
id|SCTP_CMD_DEL_NON_PRIMARY
comma
multiline_comment|/* Removes non-primary peer transports. */
DECL|enumerator|SCTP_CMD_T3_RTX_TIMERS_STOP
id|SCTP_CMD_T3_RTX_TIMERS_STOP
comma
multiline_comment|/* Stops T3-rtx pending timers */
DECL|enumerator|SCTP_CMD_FORCE_PRIM_RETRAN
id|SCTP_CMD_FORCE_PRIM_RETRAN
comma
multiline_comment|/* Forces retrans. over primary path. */
DECL|enumerator|SCTP_CMD_LAST
id|SCTP_CMD_LAST
DECL|typedef|sctp_verb_t
)brace
id|sctp_verb_t
suffix:semicolon
DECL|macro|SCTP_CMD_MAX
mdefine_line|#define SCTP_CMD_MAX&t;&t;(SCTP_CMD_LAST - 1)
DECL|macro|SCTP_CMD_NUM_VERBS
mdefine_line|#define SCTP_CMD_NUM_VERBS&t;(SCTP_CMD_MAX + 1)
multiline_comment|/* How many commands can you put in an sctp_cmd_seq_t?&n; * This is a rather arbitrary number, ideally derived from a careful&n; * analysis of the state functions, but in reality just taken from&n; * thin air in the hopes othat we don&squot;t trigger a kernel panic.&n; */
DECL|macro|SCTP_MAX_NUM_COMMANDS
mdefine_line|#define SCTP_MAX_NUM_COMMANDS 14
r_typedef
r_union
(brace
DECL|member|i32
id|__s32
id|i32
suffix:semicolon
DECL|member|u32
id|__u32
id|u32
suffix:semicolon
DECL|member|u16
id|__u16
id|u16
suffix:semicolon
DECL|member|u8
id|__u8
id|u8
suffix:semicolon
DECL|member|error
r_int
id|error
suffix:semicolon
DECL|member|state
id|sctp_state_t
id|state
suffix:semicolon
DECL|member|to
id|sctp_event_timeout_t
id|to
suffix:semicolon
DECL|member|counter
id|sctp_counter_t
id|counter
suffix:semicolon
DECL|member|ptr
r_void
op_star
id|ptr
suffix:semicolon
DECL|member|chunk
r_struct
id|sctp_chunk
op_star
id|chunk
suffix:semicolon
DECL|member|asoc
r_struct
id|sctp_association
op_star
id|asoc
suffix:semicolon
DECL|member|transport
r_struct
id|sctp_transport
op_star
id|transport
suffix:semicolon
DECL|member|bp
r_struct
id|sctp_bind_addr
op_star
id|bp
suffix:semicolon
DECL|member|init
id|sctp_init_chunk_t
op_star
id|init
suffix:semicolon
DECL|member|ulpevent
r_struct
id|sctp_ulpevent
op_star
id|ulpevent
suffix:semicolon
DECL|member|packet
r_struct
id|sctp_packet
op_star
id|packet
suffix:semicolon
DECL|member|sackh
id|sctp_sackhdr_t
op_star
id|sackh
suffix:semicolon
DECL|typedef|sctp_arg_t
)brace
id|sctp_arg_t
suffix:semicolon
multiline_comment|/* We are simulating ML type constructors here.&n; *&n; * SCTP_ARG_CONSTRUCTOR(NAME, TYPE, ELT) builds a function called&n; * SCTP_NAME() which takes an argument of type TYPE and returns an&n; * sctp_arg_t.  It does this by inserting the sole argument into the&n; * ELT union element of a local sctp_arg_t.&n; *&n; * E.g., SCTP_ARG_CONSTRUCTOR(I32, __s32, i32) builds SCTP_I32(arg),&n; * which takes an __s32 and returns a sctp_arg_t containing the&n; * __s32.  So, after foo = SCTP_I32(arg), foo.i32 == arg.&n; */
DECL|function|SCTP_NULL
r_static
r_inline
id|sctp_arg_t
id|SCTP_NULL
c_func
(paren
r_void
)paren
(brace
id|sctp_arg_t
id|retval
suffix:semicolon
id|retval.ptr
op_assign
l_int|NULL
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|SCTP_NOFORCE
r_static
r_inline
id|sctp_arg_t
id|SCTP_NOFORCE
c_func
(paren
r_void
)paren
(brace
id|sctp_arg_t
id|retval
suffix:semicolon
id|retval.i32
op_assign
l_int|0
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|SCTP_FORCE
r_static
r_inline
id|sctp_arg_t
id|SCTP_FORCE
c_func
(paren
r_void
)paren
(brace
id|sctp_arg_t
id|retval
suffix:semicolon
id|retval.i32
op_assign
l_int|1
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|macro|SCTP_ARG_CONSTRUCTOR
mdefine_line|#define SCTP_ARG_CONSTRUCTOR(name, type, elt) &bslash;&n;static inline sctp_arg_t&t;&bslash;&n;SCTP_## name (type arg)&t;&t;&bslash;&n;{ sctp_arg_t retval; retval.elt = arg; return retval; }
id|SCTP_ARG_CONSTRUCTOR
c_func
(paren
id|I32
comma
id|__s32
comma
id|i32
)paren
id|SCTP_ARG_CONSTRUCTOR
c_func
(paren
id|U32
comma
id|__u32
comma
id|u32
)paren
id|SCTP_ARG_CONSTRUCTOR
c_func
(paren
id|U16
comma
id|__u16
comma
id|u16
)paren
id|SCTP_ARG_CONSTRUCTOR
c_func
(paren
id|U8
comma
id|__u8
comma
id|u8
)paren
id|SCTP_ARG_CONSTRUCTOR
c_func
(paren
id|ERROR
comma
r_int
comma
id|error
)paren
id|SCTP_ARG_CONSTRUCTOR
c_func
(paren
id|STATE
comma
id|sctp_state_t
comma
id|state
)paren
id|SCTP_ARG_CONSTRUCTOR
c_func
(paren
id|COUNTER
comma
id|sctp_counter_t
comma
id|counter
)paren
id|SCTP_ARG_CONSTRUCTOR
c_func
(paren
id|TO
comma
id|sctp_event_timeout_t
comma
id|to
)paren
id|SCTP_ARG_CONSTRUCTOR
c_func
(paren
id|PTR
comma
r_void
op_star
comma
id|ptr
)paren
id|SCTP_ARG_CONSTRUCTOR
c_func
(paren
id|CHUNK
comma
r_struct
id|sctp_chunk
op_star
comma
id|chunk
)paren
id|SCTP_ARG_CONSTRUCTOR
c_func
(paren
id|ASOC
comma
r_struct
id|sctp_association
op_star
comma
id|asoc
)paren
id|SCTP_ARG_CONSTRUCTOR
c_func
(paren
id|TRANSPORT
comma
r_struct
id|sctp_transport
op_star
comma
id|transport
)paren
id|SCTP_ARG_CONSTRUCTOR
c_func
(paren
id|BA
comma
r_struct
id|sctp_bind_addr
op_star
comma
id|bp
)paren
id|SCTP_ARG_CONSTRUCTOR
c_func
(paren
id|PEER_INIT
comma
id|sctp_init_chunk_t
op_star
comma
id|init
)paren
id|SCTP_ARG_CONSTRUCTOR
c_func
(paren
id|ULPEVENT
comma
r_struct
id|sctp_ulpevent
op_star
comma
id|ulpevent
)paren
id|SCTP_ARG_CONSTRUCTOR
c_func
(paren
id|PACKET
comma
r_struct
id|sctp_packet
op_star
comma
id|packet
)paren
id|SCTP_ARG_CONSTRUCTOR
c_func
(paren
id|SACKH
comma
id|sctp_sackhdr_t
op_star
comma
id|sackh
)paren
r_typedef
r_struct
(brace
DECL|member|obj
id|sctp_arg_t
id|obj
suffix:semicolon
DECL|member|verb
id|sctp_verb_t
id|verb
suffix:semicolon
DECL|typedef|sctp_cmd_t
)brace
id|sctp_cmd_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|cmds
id|sctp_cmd_t
id|cmds
(braket
id|SCTP_MAX_NUM_COMMANDS
)braket
suffix:semicolon
DECL|member|next_free_slot
id|__u8
id|next_free_slot
suffix:semicolon
DECL|member|next_cmd
id|__u8
id|next_cmd
suffix:semicolon
DECL|typedef|sctp_cmd_seq_t
)brace
id|sctp_cmd_seq_t
suffix:semicolon
multiline_comment|/* Initialize a block of memory as a command sequence.&n; * Return 0 if the initialization fails.&n; */
r_int
id|sctp_init_cmd_seq
c_func
(paren
id|sctp_cmd_seq_t
op_star
id|seq
)paren
suffix:semicolon
multiline_comment|/* Add a command to an sctp_cmd_seq_t.&n; * Return 0 if the command sequence is full.&n; *&n; * Use the SCTP_* constructors defined by SCTP_ARG_CONSTRUCTOR() above&n; * to wrap data which goes in the obj argument.&n; */
r_int
id|sctp_add_cmd
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
suffix:semicolon
multiline_comment|/* Return the next command structure in an sctp_cmd_seq.&n; * Return NULL at the end of the sequence.&n; */
id|sctp_cmd_t
op_star
id|sctp_next_cmd
c_func
(paren
id|sctp_cmd_seq_t
op_star
id|seq
)paren
suffix:semicolon
macro_line|#endif /* __net_sctp_command_h__ */
eof
