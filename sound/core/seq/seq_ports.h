multiline_comment|/*&n; *   ALSA sequencer Ports &n; *   Copyright (c) 1998 by Frank van de Pol &lt;fvdpol@home.nl&gt;&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#ifndef __SND_SEQ_PORTS_H
DECL|macro|__SND_SEQ_PORTS_H
mdefine_line|#define __SND_SEQ_PORTS_H
macro_line|#include &lt;sound/seq_kernel.h&gt;
macro_line|#include &quot;seq_lock.h&quot;
multiline_comment|/* list of &squot;exported&squot; ports */
multiline_comment|/* Client ports that are not exported are still accessible, but are&n; anonymous ports. &n; &n; If a port supports SUBSCRIPTION, that port can send events to all&n; subscribersto a special address, with address&n; (queue==SNDRV_SEQ_ADDRESS_SUBSCRIBERS). The message is then send to all&n; recipients that are registered in the subscription list. A typical&n; application for these SUBSCRIPTION events is handling of incoming MIDI&n; data. The port doesn&squot;t &squot;know&squot; what other clients are interested in this&n; message. If for instance a MIDI recording application would like to receive&n; the events from that port, it will first have to subscribe with that port.&n; &n;*/
DECL|struct|subscribers_t
r_typedef
r_struct
id|subscribers_t
(brace
DECL|member|info
id|snd_seq_port_subscribe_t
id|info
suffix:semicolon
multiline_comment|/* additional info */
DECL|member|src_list
r_struct
id|list_head
id|src_list
suffix:semicolon
multiline_comment|/* link of sources */
DECL|member|dest_list
r_struct
id|list_head
id|dest_list
suffix:semicolon
multiline_comment|/* link of destinations */
DECL|member|ref_count
id|atomic_t
id|ref_count
suffix:semicolon
DECL|typedef|subscribers_t
)brace
id|subscribers_t
suffix:semicolon
DECL|struct|port_subs_info_t
r_typedef
r_struct
id|port_subs_info_t
(brace
DECL|member|list_head
r_struct
id|list_head
id|list_head
suffix:semicolon
multiline_comment|/* list of subscribed ports */
DECL|member|count
r_int
r_int
id|count
suffix:semicolon
multiline_comment|/* count of subscribers */
DECL|member|exclusive
r_int
r_int
id|exclusive
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* exclusive mode */
DECL|member|list_mutex
r_struct
id|rw_semaphore
id|list_mutex
suffix:semicolon
DECL|member|list_lock
id|rwlock_t
id|list_lock
suffix:semicolon
DECL|member|open
id|snd_seq_kernel_port_open_t
op_star
id|open
suffix:semicolon
DECL|member|close
id|snd_seq_kernel_port_close_t
op_star
id|close
suffix:semicolon
DECL|typedef|port_subs_info_t
)brace
id|port_subs_info_t
suffix:semicolon
DECL|struct|client_port_t
r_typedef
r_struct
id|client_port_t
(brace
DECL|member|addr
id|snd_seq_addr_t
id|addr
suffix:semicolon
multiline_comment|/* client/port number */
DECL|member|owner
r_struct
id|module
op_star
id|owner
suffix:semicolon
multiline_comment|/* owner of this port */
DECL|member|name
r_char
id|name
(braket
l_int|64
)braket
suffix:semicolon
multiline_comment|/* port name */
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
multiline_comment|/* port list */
DECL|member|use_lock
id|snd_use_lock_t
id|use_lock
suffix:semicolon
multiline_comment|/* subscribers */
DECL|member|c_src
id|port_subs_info_t
id|c_src
suffix:semicolon
multiline_comment|/* read (sender) list */
DECL|member|c_dest
id|port_subs_info_t
id|c_dest
suffix:semicolon
multiline_comment|/* write (dest) list */
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
DECL|member|private_data
r_void
op_star
id|private_data
suffix:semicolon
DECL|member|callback_all
r_int
r_int
id|callback_all
suffix:colon
l_int|1
suffix:semicolon
DECL|member|closing
r_int
r_int
id|closing
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* capability, inport, output, sync */
DECL|member|capability
r_int
r_int
id|capability
suffix:semicolon
multiline_comment|/* port capability bits */
DECL|member|type
r_int
r_int
id|type
suffix:semicolon
multiline_comment|/* port type bits */
multiline_comment|/* supported channels */
DECL|member|midi_channels
r_int
id|midi_channels
suffix:semicolon
DECL|member|synth_voices
r_int
id|synth_voices
suffix:semicolon
DECL|typedef|client_port_t
)brace
id|client_port_t
suffix:semicolon
multiline_comment|/* return pointer to port structure and lock port */
id|client_port_t
op_star
id|snd_seq_port_use_ptr
c_func
(paren
id|client_t
op_star
id|client
comma
r_int
id|num
)paren
suffix:semicolon
multiline_comment|/* search for next port - port is locked if found */
id|client_port_t
op_star
id|snd_seq_port_query_nearest
c_func
(paren
id|client_t
op_star
id|client
comma
id|snd_seq_port_info_t
op_star
id|pinfo
)paren
suffix:semicolon
multiline_comment|/* unlock the port */
DECL|macro|snd_seq_port_unlock
mdefine_line|#define snd_seq_port_unlock(port) snd_use_lock_free(&amp;(port)-&gt;use_lock)
multiline_comment|/* create a port, port number is returned (-1 on failure) */
id|client_port_t
op_star
id|snd_seq_create_port
c_func
(paren
id|client_t
op_star
id|client
comma
r_int
id|port_index
)paren
suffix:semicolon
multiline_comment|/* delete a port */
r_int
id|snd_seq_delete_port
c_func
(paren
id|client_t
op_star
id|client
comma
r_int
id|port
)paren
suffix:semicolon
multiline_comment|/* delete all ports */
r_int
id|snd_seq_delete_all_ports
c_func
(paren
id|client_t
op_star
id|client
)paren
suffix:semicolon
multiline_comment|/* set port info fields */
r_int
id|snd_seq_set_port_info
c_func
(paren
id|client_port_t
op_star
id|port
comma
id|snd_seq_port_info_t
op_star
id|info
)paren
suffix:semicolon
multiline_comment|/* get port info fields */
r_int
id|snd_seq_get_port_info
c_func
(paren
id|client_port_t
op_star
id|port
comma
id|snd_seq_port_info_t
op_star
id|info
)paren
suffix:semicolon
multiline_comment|/* add subscriber to subscription list */
r_int
id|snd_seq_port_connect
c_func
(paren
id|client_t
op_star
id|caller
comma
id|client_t
op_star
id|s
comma
id|client_port_t
op_star
id|sp
comma
id|client_t
op_star
id|d
comma
id|client_port_t
op_star
id|dp
comma
id|snd_seq_port_subscribe_t
op_star
id|info
)paren
suffix:semicolon
multiline_comment|/* remove subscriber from subscription list */
r_int
id|snd_seq_port_disconnect
c_func
(paren
id|client_t
op_star
id|caller
comma
id|client_t
op_star
id|s
comma
id|client_port_t
op_star
id|sp
comma
id|client_t
op_star
id|d
comma
id|client_port_t
op_star
id|dp
comma
id|snd_seq_port_subscribe_t
op_star
id|info
)paren
suffix:semicolon
multiline_comment|/* subscribe port */
r_int
id|snd_seq_port_subscribe
c_func
(paren
id|client_port_t
op_star
id|port
comma
id|snd_seq_port_subscribe_t
op_star
id|info
)paren
suffix:semicolon
multiline_comment|/* get matched subscriber */
id|subscribers_t
op_star
id|snd_seq_port_get_subscription
c_func
(paren
id|port_subs_info_t
op_star
id|src_grp
comma
id|snd_seq_addr_t
op_star
id|dest_addr
)paren
suffix:semicolon
macro_line|#endif
eof
