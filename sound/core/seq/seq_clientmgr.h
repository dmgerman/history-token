multiline_comment|/*&n; *   ALSA sequencer Client Manager&n; *   Copyright (c) 1998-1999 by Frank van de Pol &lt;fvdpol@home.nl&gt;&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#ifndef __SND_SEQ_CLIENTMGR_H
DECL|macro|__SND_SEQ_CLIENTMGR_H
mdefine_line|#define __SND_SEQ_CLIENTMGR_H
macro_line|#include &lt;sound/seq_kernel.h&gt;
macro_line|#include &quot;seq_fifo.h&quot;
macro_line|#include &quot;seq_ports.h&quot;
macro_line|#include &quot;seq_lock.h&quot;
multiline_comment|/* client manager */
DECL|struct|_snd_seq_user_client
r_struct
id|_snd_seq_user_client
(brace
DECL|member|file
r_struct
id|file
op_star
id|file
suffix:semicolon
multiline_comment|/* file struct of client */
multiline_comment|/* ... */
multiline_comment|/* fifo */
DECL|member|fifo
id|fifo_t
op_star
id|fifo
suffix:semicolon
multiline_comment|/* queue for incoming events */
DECL|member|fifo_pool_size
r_int
id|fifo_pool_size
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|_snd_seq_kernel_client
r_struct
id|_snd_seq_kernel_client
(brace
DECL|member|card
id|snd_card_t
op_star
id|card
suffix:semicolon
multiline_comment|/* pointer to client functions */
DECL|member|private_data
r_void
op_star
id|private_data
suffix:semicolon
multiline_comment|/* private data for client */
multiline_comment|/* ... */
)brace
suffix:semicolon
DECL|struct|_snd_seq_client
r_struct
id|_snd_seq_client
(brace
DECL|member|type
id|snd_seq_client_type_t
id|type
suffix:semicolon
DECL|member|accept_input
r_int
r_int
id|accept_input
suffix:colon
l_int|1
comma
DECL|member|accept_output
id|accept_output
suffix:colon
l_int|1
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
l_int|64
)braket
suffix:semicolon
multiline_comment|/* client name */
DECL|member|number
r_int
id|number
suffix:semicolon
multiline_comment|/* client number */
DECL|member|filter
r_int
r_int
id|filter
suffix:semicolon
multiline_comment|/* filter flags */
id|bitmap_member
c_func
(paren
id|client_filter
comma
l_int|256
)paren
suffix:semicolon
id|bitmap_member
c_func
(paren
id|event_filter
comma
l_int|256
)paren
suffix:semicolon
DECL|member|use_lock
id|snd_use_lock_t
id|use_lock
suffix:semicolon
DECL|member|event_lost
r_int
id|event_lost
suffix:semicolon
multiline_comment|/* ports */
DECL|member|num_ports
r_int
id|num_ports
suffix:semicolon
multiline_comment|/* number of ports */
DECL|member|ports_list_head
r_struct
id|list_head
id|ports_list_head
suffix:semicolon
DECL|member|ports_lock
id|rwlock_t
id|ports_lock
suffix:semicolon
DECL|member|ports_mutex
r_struct
id|semaphore
id|ports_mutex
suffix:semicolon
multiline_comment|/* output pool */
DECL|member|pool
id|pool_t
op_star
id|pool
suffix:semicolon
multiline_comment|/* memory pool for this client */
r_union
(brace
DECL|member|user
id|user_client_t
id|user
suffix:semicolon
DECL|member|kernel
id|kernel_client_t
id|kernel
suffix:semicolon
DECL|member|data
)brace
id|data
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* usage statistics */
r_typedef
r_struct
(brace
DECL|member|cur
r_int
id|cur
suffix:semicolon
DECL|member|peak
r_int
id|peak
suffix:semicolon
DECL|typedef|usage_t
)brace
id|usage_t
suffix:semicolon
r_extern
r_int
id|client_init_data
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|snd_sequencer_device_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|snd_sequencer_device_done
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* get locked pointer to client */
r_extern
id|client_t
op_star
id|snd_seq_client_use_ptr
c_func
(paren
r_int
id|clientid
)paren
suffix:semicolon
multiline_comment|/* unlock pointer to client */
DECL|macro|snd_seq_client_unlock
mdefine_line|#define snd_seq_client_unlock(client) snd_use_lock_free(&amp;(client)-&gt;use_lock)
multiline_comment|/* dispatch event to client(s) */
r_extern
r_int
id|snd_seq_dispatch_event
c_func
(paren
id|snd_seq_event_cell_t
op_star
id|cell
comma
r_int
id|atomic
comma
r_int
id|hop
)paren
suffix:semicolon
multiline_comment|/* exported to other modules */
r_extern
r_int
id|snd_seq_register_kernel_client
c_func
(paren
id|snd_seq_client_callback_t
op_star
id|callback
comma
r_void
op_star
id|private_data
)paren
suffix:semicolon
r_extern
r_int
id|snd_seq_unregister_kernel_client
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
r_int
id|snd_seq_kernel_client_enqueue_blocking
c_func
(paren
r_int
id|client
comma
id|snd_seq_event_t
op_star
id|ev
comma
r_struct
id|file
op_star
id|file
comma
r_int
id|atomic
comma
r_int
id|hop
)paren
suffix:semicolon
r_int
id|snd_seq_kernel_client_write_poll
c_func
(paren
r_int
id|clientid
comma
r_struct
id|file
op_star
id|file
comma
id|poll_table
op_star
id|wait
)paren
suffix:semicolon
r_int
id|snd_seq_client_notify_subscription
c_func
(paren
r_int
id|client
comma
r_int
id|port
comma
id|snd_seq_port_subscribe_t
op_star
id|info
comma
r_int
id|evtype
)paren
suffix:semicolon
r_int
id|snd_seq_deliver_event
c_func
(paren
id|client_t
op_star
id|client
comma
id|snd_seq_event_t
op_star
id|event
comma
r_int
id|atomic
comma
r_int
id|hop
)paren
suffix:semicolon
macro_line|#endif
eof
