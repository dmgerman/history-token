multiline_comment|/*&n; *  ALSA sequencer System Client&n; *  Copyright (c) 1998 by Frank van de Pol &lt;fvdpol@home.nl&gt;&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#ifndef __SND_SEQ_SYSTEM_H
DECL|macro|__SND_SEQ_SYSTEM_H
mdefine_line|#define __SND_SEQ_SYSTEM_H
macro_line|#include &lt;sound/seq_kernel.h&gt;
multiline_comment|/* entry points for broadcasting system events */
r_void
id|snd_seq_system_broadcast
c_func
(paren
r_int
id|client
comma
r_int
id|port
comma
r_int
id|type
)paren
suffix:semicolon
DECL|macro|snd_seq_system_client_ev_client_start
mdefine_line|#define snd_seq_system_client_ev_client_start(client) snd_seq_system_broadcast(client, 0, SNDRV_SEQ_EVENT_CLIENT_START)
DECL|macro|snd_seq_system_client_ev_client_exit
mdefine_line|#define snd_seq_system_client_ev_client_exit(client) snd_seq_system_broadcast(client, 0, SNDRV_SEQ_EVENT_CLIENT_EXIT)
DECL|macro|snd_seq_system_client_ev_client_change
mdefine_line|#define snd_seq_system_client_ev_client_change(client) snd_seq_system_broadcast(client, 0, SNDRV_SEQ_EVENT_CLIENT_CHANGE)
DECL|macro|snd_seq_system_client_ev_port_start
mdefine_line|#define snd_seq_system_client_ev_port_start(client, port) snd_seq_system_broadcast(client, port, SNDRV_SEQ_EVENT_PORT_START)
DECL|macro|snd_seq_system_client_ev_port_exit
mdefine_line|#define snd_seq_system_client_ev_port_exit(client, port) snd_seq_system_broadcast(client, port, SNDRV_SEQ_EVENT_PORT_EXIT)
DECL|macro|snd_seq_system_client_ev_port_change
mdefine_line|#define snd_seq_system_client_ev_port_change(client, port) snd_seq_system_broadcast(client, port, SNDRV_SEQ_EVENT_PORT_CHANGE)
r_int
id|snd_seq_system_notify
c_func
(paren
r_int
id|client
comma
r_int
id|port
comma
id|snd_seq_event_t
op_star
id|ev
)paren
suffix:semicolon
multiline_comment|/* register our internal client */
r_int
id|snd_seq_system_client_init
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* unregister our internal client */
r_void
id|snd_seq_system_client_done
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
eof
