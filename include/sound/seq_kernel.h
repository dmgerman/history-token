macro_line|#ifndef __SOUND_SEQ_KERNEL_H
DECL|macro|__SOUND_SEQ_KERNEL_H
mdefine_line|#define __SOUND_SEQ_KERNEL_H
multiline_comment|/*&n; *  Main kernel header file for the ALSA sequencer&n; *  Copyright (c) 1998 by Frank van de Pol &lt;fvdpol@home.nl&gt;&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &quot;asequencer.h&quot;
DECL|typedef|snd_seq_tick_time_t
r_typedef
id|sndrv_seq_tick_time_t
id|snd_seq_tick_time_t
suffix:semicolon
DECL|typedef|snd_seq_position_t
r_typedef
id|sndrv_seq_position_t
id|snd_seq_position_t
suffix:semicolon
DECL|typedef|snd_seq_frequency_t
r_typedef
id|sndrv_seq_frequency_t
id|snd_seq_frequency_t
suffix:semicolon
DECL|typedef|snd_seq_instr_cluster_t
r_typedef
id|sndrv_seq_instr_cluster_t
id|snd_seq_instr_cluster_t
suffix:semicolon
DECL|typedef|snd_seq_client_type_t
r_typedef
r_enum
id|sndrv_seq_client_type
id|snd_seq_client_type_t
suffix:semicolon
DECL|typedef|snd_seq_stop_mode_t
r_typedef
r_enum
id|sndrv_seq_stop_mode
id|snd_seq_stop_mode_t
suffix:semicolon
DECL|typedef|snd_seq_port_info_t
r_typedef
r_struct
id|sndrv_seq_port_info
id|snd_seq_port_info_t
suffix:semicolon
DECL|typedef|snd_seq_port_subscribe_t
r_typedef
r_struct
id|sndrv_seq_port_subscribe
id|snd_seq_port_subscribe_t
suffix:semicolon
DECL|typedef|snd_seq_event_t
r_typedef
r_struct
id|sndrv_seq_event
id|snd_seq_event_t
suffix:semicolon
DECL|typedef|snd_seq_addr_t
r_typedef
r_struct
id|sndrv_seq_addr
id|snd_seq_addr_t
suffix:semicolon
DECL|typedef|snd_seq_ev_volume_t
r_typedef
r_struct
id|sndrv_seq_ev_volume
id|snd_seq_ev_volume_t
suffix:semicolon
DECL|typedef|snd_seq_ev_loop_t
r_typedef
r_struct
id|sndrv_seq_ev_loop
id|snd_seq_ev_loop_t
suffix:semicolon
DECL|typedef|snd_seq_remove_events_t
r_typedef
r_struct
id|sndrv_seq_remove_events
id|snd_seq_remove_events_t
suffix:semicolon
DECL|typedef|snd_seq_query_subs_t
r_typedef
r_struct
id|sndrv_seq_query_subs
id|snd_seq_query_subs_t
suffix:semicolon
DECL|typedef|snd_seq_real_time_t
r_typedef
r_struct
id|sndrv_seq_real_time
id|snd_seq_real_time_t
suffix:semicolon
DECL|typedef|snd_seq_system_info_t
r_typedef
r_struct
id|sndrv_seq_system_info
id|snd_seq_system_info_t
suffix:semicolon
DECL|typedef|snd_seq_client_info_t
r_typedef
r_struct
id|sndrv_seq_client_info
id|snd_seq_client_info_t
suffix:semicolon
DECL|typedef|snd_seq_queue_info_t
r_typedef
r_struct
id|sndrv_seq_queue_info
id|snd_seq_queue_info_t
suffix:semicolon
DECL|typedef|snd_seq_queue_status_t
r_typedef
r_struct
id|sndrv_seq_queue_status
id|snd_seq_queue_status_t
suffix:semicolon
DECL|typedef|snd_seq_queue_tempo_t
r_typedef
r_struct
id|sndrv_seq_queue_tempo
id|snd_seq_queue_tempo_t
suffix:semicolon
DECL|typedef|snd_seq_queue_owner_t
r_typedef
r_struct
id|sndrv_seq_queue_owner
id|snd_seq_queue_owner_t
suffix:semicolon
DECL|typedef|snd_seq_queue_timer_t
r_typedef
r_struct
id|sndrv_seq_queue_timer
id|snd_seq_queue_timer_t
suffix:semicolon
DECL|typedef|snd_seq_queue_client_t
r_typedef
r_struct
id|sndrv_seq_queue_client
id|snd_seq_queue_client_t
suffix:semicolon
DECL|typedef|snd_seq_client_pool_t
r_typedef
r_struct
id|sndrv_seq_client_pool
id|snd_seq_client_pool_t
suffix:semicolon
DECL|typedef|snd_seq_instr_t
r_typedef
r_struct
id|sndrv_seq_instr
id|snd_seq_instr_t
suffix:semicolon
DECL|typedef|snd_seq_instr_data_t
r_typedef
r_struct
id|sndrv_seq_instr_data
id|snd_seq_instr_data_t
suffix:semicolon
DECL|typedef|snd_seq_instr_header_t
r_typedef
r_struct
id|sndrv_seq_instr_header
id|snd_seq_instr_header_t
suffix:semicolon
DECL|typedef|snd_seq_timestamp_t
r_typedef
r_union
id|sndrv_seq_timestamp
id|snd_seq_timestamp_t
suffix:semicolon
DECL|macro|snd_seq_event_bounce_ext_data
mdefine_line|#define snd_seq_event_bounce_ext_data&t;sndrv_seq_event_bounce_ext_data 
DECL|macro|snd_seq_ev_is_result_type
mdefine_line|#define snd_seq_ev_is_result_type&t;sndrv_seq_ev_is_result_type     
DECL|macro|snd_seq_ev_is_channel_type
mdefine_line|#define snd_seq_ev_is_channel_type&t;sndrv_seq_ev_is_channel_type    
DECL|macro|snd_seq_ev_is_note_type
mdefine_line|#define snd_seq_ev_is_note_type&t;&t;sndrv_seq_ev_is_note_type       
DECL|macro|snd_seq_ev_is_control_type
mdefine_line|#define snd_seq_ev_is_control_type&t;sndrv_seq_ev_is_control_type    
DECL|macro|snd_seq_ev_is_queue_type
mdefine_line|#define snd_seq_ev_is_queue_type&t;sndrv_seq_ev_is_queue_type      
DECL|macro|snd_seq_ev_is_message_type
mdefine_line|#define snd_seq_ev_is_message_type&t;sndrv_seq_ev_is_message_type    
DECL|macro|snd_seq_ev_is_sample_type
mdefine_line|#define snd_seq_ev_is_sample_type&t;sndrv_seq_ev_is_sample_type     
DECL|macro|snd_seq_ev_is_user_type
mdefine_line|#define snd_seq_ev_is_user_type&t;&t;sndrv_seq_ev_is_user_type       
DECL|macro|snd_seq_ev_is_fixed_type
mdefine_line|#define snd_seq_ev_is_fixed_type&t;sndrv_seq_ev_is_fixed_type      
DECL|macro|snd_seq_ev_is_instr_type
mdefine_line|#define snd_seq_ev_is_instr_type&t;sndrv_seq_ev_is_instr_type      
DECL|macro|snd_seq_ev_is_variable_type
mdefine_line|#define snd_seq_ev_is_variable_type&t;sndrv_seq_ev_is_variable_type   
DECL|macro|snd_seq_ev_is_reserved
mdefine_line|#define snd_seq_ev_is_reserved&t;&t;sndrv_seq_ev_is_reserved        
DECL|macro|snd_seq_ev_is_direct
mdefine_line|#define snd_seq_ev_is_direct&t;&t;sndrv_seq_ev_is_direct          
DECL|macro|snd_seq_ev_is_prior
mdefine_line|#define snd_seq_ev_is_prior&t;&t;sndrv_seq_ev_is_prior           
DECL|macro|snd_seq_ev_length_type
mdefine_line|#define snd_seq_ev_length_type&t;&t;sndrv_seq_ev_length_type        
DECL|macro|snd_seq_ev_is_fixed
mdefine_line|#define snd_seq_ev_is_fixed&t;&t;sndrv_seq_ev_is_fixed           
DECL|macro|snd_seq_ev_is_variable
mdefine_line|#define snd_seq_ev_is_variable&t;&t;sndrv_seq_ev_is_variable        
DECL|macro|snd_seq_ev_is_varusr
mdefine_line|#define snd_seq_ev_is_varusr&t;&t;sndrv_seq_ev_is_varusr          
DECL|macro|snd_seq_ev_timestamp_type
mdefine_line|#define snd_seq_ev_timestamp_type&t;sndrv_seq_ev_timestamp_type     
DECL|macro|snd_seq_ev_is_tick
mdefine_line|#define snd_seq_ev_is_tick&t;&t;sndrv_seq_ev_is_tick            
DECL|macro|snd_seq_ev_is_real
mdefine_line|#define snd_seq_ev_is_real&t;&t;sndrv_seq_ev_is_real            
DECL|macro|snd_seq_ev_timemode_type
mdefine_line|#define snd_seq_ev_timemode_type&t;sndrv_seq_ev_timemode_type      
DECL|macro|snd_seq_ev_is_abstime
mdefine_line|#define snd_seq_ev_is_abstime&t;&t;sndrv_seq_ev_is_abstime         
DECL|macro|snd_seq_ev_is_reltime
mdefine_line|#define snd_seq_ev_is_reltime&t;&t;sndrv_seq_ev_is_reltime         
DECL|macro|snd_seq_queue_sync_port
mdefine_line|#define snd_seq_queue_sync_port&t;&t;sndrv_seq_queue_sync_port       
DECL|macro|snd_seq_queue_owner
mdefine_line|#define snd_seq_queue_owner&t;&t;sndrv_seq_queue_owner           
multiline_comment|/* maximum number of events dequeued per schedule interval */
DECL|macro|SNDRV_SEQ_MAX_DEQUEUE
mdefine_line|#define SNDRV_SEQ_MAX_DEQUEUE&t;&t;50
multiline_comment|/* maximum number of queues */
DECL|macro|SNDRV_SEQ_MAX_QUEUES
mdefine_line|#define SNDRV_SEQ_MAX_QUEUES&t;&t;8
multiline_comment|/* max number of concurrent clients */
DECL|macro|SNDRV_SEQ_MAX_CLIENTS
mdefine_line|#define SNDRV_SEQ_MAX_CLIENTS &t;&t;192
multiline_comment|/* max number of concurrent ports */
DECL|macro|SNDRV_SEQ_MAX_PORTS
mdefine_line|#define SNDRV_SEQ_MAX_PORTS &t;&t;254
multiline_comment|/* max number of events in memory pool */
DECL|macro|SNDRV_SEQ_MAX_EVENTS
mdefine_line|#define SNDRV_SEQ_MAX_EVENTS&t;&t;2000
multiline_comment|/* default number of events in memory chunk */
DECL|macro|SNDRV_SEQ_DEFAULT_CHUNK_EVENTS
mdefine_line|#define SNDRV_SEQ_DEFAULT_CHUNK_EVENTS&t;64
multiline_comment|/* default number of events in memory pool */
DECL|macro|SNDRV_SEQ_DEFAULT_EVENTS
mdefine_line|#define SNDRV_SEQ_DEFAULT_EVENTS&t;500
multiline_comment|/* max number of events in memory pool for one client (outqueue) */
DECL|macro|SNDRV_SEQ_MAX_CLIENT_EVENTS
mdefine_line|#define SNDRV_SEQ_MAX_CLIENT_EVENTS&t;2000
multiline_comment|/* default number of events in memory pool for one client (outqueue) */
DECL|macro|SNDRV_SEQ_DEFAULT_CLIENT_EVENTS
mdefine_line|#define SNDRV_SEQ_DEFAULT_CLIENT_EVENTS&t;200
multiline_comment|/* max delivery path length */
DECL|macro|SNDRV_SEQ_MAX_HOPS
mdefine_line|#define SNDRV_SEQ_MAX_HOPS&t;&t;10
multiline_comment|/* max size of event size */
DECL|macro|SNDRV_SEQ_MAX_EVENT_LEN
mdefine_line|#define SNDRV_SEQ_MAX_EVENT_LEN&t;&t;0x3fffffff
multiline_comment|/* typedefs */
r_struct
id|_snd_seq_user_client
suffix:semicolon
r_struct
id|_snd_seq_kernel_client
suffix:semicolon
r_struct
id|_snd_seq_client
suffix:semicolon
r_struct
id|_snd_seq_queue
suffix:semicolon
DECL|typedef|user_client_t
r_typedef
r_struct
id|_snd_seq_user_client
id|user_client_t
suffix:semicolon
DECL|typedef|kernel_client_t
r_typedef
r_struct
id|_snd_seq_kernel_client
id|kernel_client_t
suffix:semicolon
DECL|typedef|client_t
r_typedef
r_struct
id|_snd_seq_client
id|client_t
suffix:semicolon
DECL|typedef|queue_t
r_typedef
r_struct
id|_snd_seq_queue
id|queue_t
suffix:semicolon
multiline_comment|/* call-backs for kernel client */
r_typedef
r_struct
(brace
DECL|member|private_data
r_void
op_star
id|private_data
suffix:semicolon
DECL|member|allow_input
r_int
id|allow_input
suffix:colon
l_int|1
comma
DECL|member|allow_output
id|allow_output
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/*...*/
DECL|typedef|snd_seq_client_callback_t
)brace
id|snd_seq_client_callback_t
suffix:semicolon
multiline_comment|/* call-backs for kernel port */
DECL|typedef|snd_seq_kernel_port_open_t
r_typedef
r_int
(paren
id|snd_seq_kernel_port_open_t
)paren
(paren
r_void
op_star
id|private_data
comma
id|snd_seq_port_subscribe_t
op_star
id|info
)paren
suffix:semicolon
DECL|typedef|snd_seq_kernel_port_close_t
r_typedef
r_int
(paren
id|snd_seq_kernel_port_close_t
)paren
(paren
r_void
op_star
id|private_data
comma
id|snd_seq_port_subscribe_t
op_star
id|info
)paren
suffix:semicolon
DECL|typedef|snd_seq_kernel_port_input_t
r_typedef
r_int
(paren
id|snd_seq_kernel_port_input_t
)paren
(paren
id|snd_seq_event_t
op_star
id|ev
comma
r_int
id|direct
comma
r_void
op_star
id|private_data
comma
r_int
id|atomic
comma
r_int
id|hop
)paren
suffix:semicolon
DECL|typedef|snd_seq_kernel_port_private_free_t
r_typedef
r_void
(paren
id|snd_seq_kernel_port_private_free_t
)paren
(paren
r_void
op_star
id|private_data
)paren
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|owner
r_struct
id|module
op_star
id|owner
suffix:semicolon
DECL|member|private_data
r_void
op_star
id|private_data
suffix:semicolon
DECL|member|subscribe
id|snd_seq_kernel_port_open_t
op_star
id|subscribe
suffix:semicolon
DECL|member|unsubscribe
id|snd_seq_kernel_port_close_t
op_star
id|unsubscribe
suffix:semicolon
DECL|member|use
id|snd_seq_kernel_port_open_t
op_star
id|use
suffix:semicolon
DECL|member|unuse
id|snd_seq_kernel_port_close_t
op_star
id|unuse
suffix:semicolon
DECL|member|event_input
id|snd_seq_kernel_port_input_t
op_star
id|event_input
suffix:semicolon
DECL|member|private_free
id|snd_seq_kernel_port_private_free_t
op_star
id|private_free
suffix:semicolon
DECL|member|callback_all
r_int
r_int
id|callback_all
suffix:semicolon
multiline_comment|/* call subscribe callbacks at each connection/disconnection */
multiline_comment|/*...*/
DECL|typedef|snd_seq_port_callback_t
)brace
id|snd_seq_port_callback_t
suffix:semicolon
multiline_comment|/* interface for kernel client */
r_extern
r_int
id|snd_seq_create_kernel_client
c_func
(paren
id|snd_card_t
op_star
id|card
comma
r_int
id|client_index
comma
id|snd_seq_client_callback_t
op_star
id|callback
)paren
suffix:semicolon
r_extern
r_int
id|snd_seq_delete_kernel_client
c_func
(paren
r_int
id|client
)paren
suffix:semicolon
r_extern
r_int
id|snd_seq_kernel_client_enqueue
c_func
(paren
r_int
id|client
comma
id|snd_seq_event_t
op_star
id|ev
comma
r_int
id|atomic
comma
r_int
id|hop
)paren
suffix:semicolon
r_extern
r_int
id|snd_seq_kernel_client_dispatch
c_func
(paren
r_int
id|client
comma
id|snd_seq_event_t
op_star
id|ev
comma
r_int
id|atomic
comma
r_int
id|hop
)paren
suffix:semicolon
r_extern
r_int
id|snd_seq_kernel_client_ctl
c_func
(paren
r_int
id|client
comma
r_int
r_int
id|cmd
comma
r_void
op_star
id|arg
)paren
suffix:semicolon
DECL|macro|SNDRV_SEQ_EXT_MASK
mdefine_line|#define SNDRV_SEQ_EXT_MASK&t;0xc0000000
DECL|macro|SNDRV_SEQ_EXT_USRPTR
mdefine_line|#define SNDRV_SEQ_EXT_USRPTR&t;0x80000000
DECL|macro|SNDRV_SEQ_EXT_CHAINED
mdefine_line|#define SNDRV_SEQ_EXT_CHAINED&t;0x40000000
DECL|typedef|snd_seq_dump_func_t
r_typedef
r_int
(paren
op_star
id|snd_seq_dump_func_t
)paren
(paren
r_void
op_star
id|ptr
comma
r_void
op_star
id|buf
comma
r_int
id|count
)paren
suffix:semicolon
r_int
id|snd_seq_expand_var_event
c_func
(paren
r_const
id|snd_seq_event_t
op_star
id|event
comma
r_int
id|count
comma
r_char
op_star
id|buf
comma
r_int
id|in_kernel
comma
r_int
id|size_aligned
)paren
suffix:semicolon
r_int
id|snd_seq_dump_var_event
c_func
(paren
r_const
id|snd_seq_event_t
op_star
id|event
comma
id|snd_seq_dump_func_t
id|func
comma
r_void
op_star
id|private_data
)paren
suffix:semicolon
multiline_comment|/* port callback routines */
r_void
id|snd_port_init_callback
c_func
(paren
id|snd_seq_port_callback_t
op_star
id|p
)paren
suffix:semicolon
id|snd_seq_port_callback_t
op_star
id|snd_port_alloc_callback
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* port attach/detach */
r_int
id|snd_seq_event_port_attach
c_func
(paren
r_int
id|client
comma
id|snd_seq_port_callback_t
op_star
id|pcbp
comma
r_int
id|cap
comma
r_int
id|type
comma
r_char
op_star
id|portname
)paren
suffix:semicolon
r_int
id|snd_seq_event_port_detach
c_func
(paren
r_int
id|client
comma
r_int
id|port
)paren
suffix:semicolon
macro_line|#endif /* __SOUND_SEQ_KERNEL_H */
eof
