multiline_comment|/*&n; *   ALSA sequencer System services Client&n; *   Copyright (c) 1998-1999 by Frank van de Pol &lt;fvdpol@home.nl&gt;&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
DECL|macro|__NO_VERSION__
mdefine_line|#define __NO_VERSION__
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &quot;seq_system.h&quot;
macro_line|#include &quot;seq_timer.h&quot;
macro_line|#include &quot;seq_queue.h&quot;
multiline_comment|/* internal client that provide system services, access to timer etc. */
multiline_comment|/*&n; * Port &quot;Timer&quot;&n; *      - send tempo /start/stop etc. events to this port to manipulate the &n; *        queue&squot;s timer. The queue address is specified in&n; *&t;  data.queue.queue.&n; *      - this port supports subscription. The received timer events are &n; *        broadcasted to all subscribed clients. The modified tempo&n; *&t;  value is stored on data.queue.value.&n; *&t;  The modifier client/port is not send.&n; *&n; * Port &quot;Announce&quot;&n; *      - does not receive message&n; *      - supports supscription. For each client or port attaching to or &n; *        detaching from the system an announcement is send to the subscribed&n; *        clients.&n; *&n; * Idea: the subscription mechanism might also work handy for distributing &n; * synchronisation and timing information. In this case we would ideally have&n; * a list of subscribers for each type of sync (time, tick), for each timing&n; * queue.&n; *&n; * NOTE: the queue to be started, stopped, etc. must be specified&n; *&t; in data.queue.addr.queue field.  queue is used only for&n; *&t; scheduling, and no longer referred as affected queue.&n; *&t; They are used only for timer broadcast (see above).&n; *&t;&t;&t;&t;&t;&t;&t;-- iwai&n; */
multiline_comment|/* client id of our system client */
DECL|variable|sysclient
r_static
r_int
id|sysclient
op_assign
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* port id numbers for this client */
DECL|variable|announce_port
r_static
r_int
id|announce_port
op_assign
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* fill standard header data, source port &amp; channel are filled in */
DECL|function|setheader
r_static
r_int
id|setheader
c_func
(paren
id|snd_seq_event_t
op_star
id|ev
comma
r_int
id|client
comma
r_int
id|port
)paren
(brace
r_if
c_cond
(paren
id|announce_port
OL
l_int|0
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|memset
c_func
(paren
id|ev
comma
l_int|0
comma
r_sizeof
(paren
id|snd_seq_event_t
)paren
)paren
suffix:semicolon
id|ev-&gt;flags
op_and_assign
op_complement
id|SNDRV_SEQ_EVENT_LENGTH_MASK
suffix:semicolon
id|ev-&gt;flags
op_or_assign
id|SNDRV_SEQ_EVENT_LENGTH_FIXED
suffix:semicolon
id|ev-&gt;source.client
op_assign
id|sysclient
suffix:semicolon
id|ev-&gt;source.port
op_assign
id|announce_port
suffix:semicolon
id|ev-&gt;dest.client
op_assign
id|SNDRV_SEQ_ADDRESS_SUBSCRIBERS
suffix:semicolon
multiline_comment|/* fill data */
multiline_comment|/*ev-&gt;data.addr.queue = SNDRV_SEQ_ADDRESS_UNKNOWN;*/
id|ev-&gt;data.addr.client
op_assign
id|client
suffix:semicolon
id|ev-&gt;data.addr.port
op_assign
id|port
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* entry points for broadcasting system events */
DECL|function|snd_seq_system_broadcast
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
(brace
id|snd_seq_event_t
id|ev
suffix:semicolon
r_if
c_cond
(paren
id|setheader
c_func
(paren
op_amp
id|ev
comma
id|client
comma
id|port
)paren
OL
l_int|0
)paren
r_return
suffix:semicolon
id|ev.type
op_assign
id|type
suffix:semicolon
id|snd_seq_kernel_client_dispatch
c_func
(paren
id|sysclient
comma
op_amp
id|ev
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/* entry points for broadcasting system events */
DECL|function|snd_seq_system_notify
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
(brace
id|ev-&gt;flags
op_assign
id|SNDRV_SEQ_EVENT_LENGTH_FIXED
suffix:semicolon
id|ev-&gt;source.client
op_assign
id|sysclient
suffix:semicolon
id|ev-&gt;source.port
op_assign
id|announce_port
suffix:semicolon
id|ev-&gt;dest.client
op_assign
id|client
suffix:semicolon
id|ev-&gt;dest.port
op_assign
id|port
suffix:semicolon
r_return
id|snd_seq_kernel_client_dispatch
c_func
(paren
id|sysclient
comma
id|ev
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/* call-back handler for timer events */
DECL|function|event_input_timer
r_static
r_int
id|event_input_timer
c_func
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
(brace
r_return
id|snd_seq_control_queue
c_func
(paren
id|ev
comma
id|atomic
comma
id|hop
)paren
suffix:semicolon
)brace
multiline_comment|/* register our internal client */
DECL|function|snd_seq_system_client_init
r_int
id|__init
id|snd_seq_system_client_init
c_func
(paren
r_void
)paren
(brace
id|snd_seq_client_callback_t
id|callbacks
suffix:semicolon
id|snd_seq_port_callback_t
id|pcallbacks
suffix:semicolon
id|snd_seq_client_info_t
id|inf
suffix:semicolon
id|snd_seq_port_info_t
id|port
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|callbacks
comma
l_int|0
comma
r_sizeof
(paren
id|callbacks
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|pcallbacks
comma
l_int|0
comma
r_sizeof
(paren
id|pcallbacks
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|inf
comma
l_int|0
comma
r_sizeof
(paren
id|inf
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|port
comma
l_int|0
comma
r_sizeof
(paren
id|port
)paren
)paren
suffix:semicolon
id|pcallbacks.owner
op_assign
id|THIS_MODULE
suffix:semicolon
id|pcallbacks.event_input
op_assign
id|event_input_timer
suffix:semicolon
multiline_comment|/* register client */
id|callbacks.allow_input
op_assign
id|callbacks.allow_output
op_assign
l_int|1
suffix:semicolon
id|sysclient
op_assign
id|snd_seq_create_kernel_client
c_func
(paren
l_int|NULL
comma
l_int|0
comma
op_amp
id|callbacks
)paren
suffix:semicolon
multiline_comment|/* set our name */
id|inf.client
op_assign
l_int|0
suffix:semicolon
id|inf.type
op_assign
id|KERNEL_CLIENT
suffix:semicolon
id|strcpy
c_func
(paren
id|inf.name
comma
l_string|&quot;System&quot;
)paren
suffix:semicolon
id|snd_seq_kernel_client_ctl
c_func
(paren
id|sysclient
comma
id|SNDRV_SEQ_IOCTL_SET_CLIENT_INFO
comma
op_amp
id|inf
)paren
suffix:semicolon
multiline_comment|/* register timer */
id|strcpy
c_func
(paren
id|port.name
comma
l_string|&quot;Timer&quot;
)paren
suffix:semicolon
id|port.capability
op_assign
id|SNDRV_SEQ_PORT_CAP_WRITE
suffix:semicolon
multiline_comment|/* accept queue control */
id|port.capability
op_or_assign
id|SNDRV_SEQ_PORT_CAP_READ
op_or
id|SNDRV_SEQ_PORT_CAP_SUBS_READ
suffix:semicolon
multiline_comment|/* for broadcast */
id|port.kernel
op_assign
op_amp
id|pcallbacks
suffix:semicolon
id|port.type
op_assign
l_int|0
suffix:semicolon
id|port.flags
op_assign
id|SNDRV_SEQ_PORT_FLG_GIVEN_PORT
suffix:semicolon
id|port.addr.client
op_assign
id|sysclient
suffix:semicolon
id|port.addr.port
op_assign
id|SNDRV_SEQ_PORT_SYSTEM_TIMER
suffix:semicolon
id|snd_seq_kernel_client_ctl
c_func
(paren
id|sysclient
comma
id|SNDRV_SEQ_IOCTL_CREATE_PORT
comma
op_amp
id|port
)paren
suffix:semicolon
multiline_comment|/* register announcement port */
id|strcpy
c_func
(paren
id|port.name
comma
l_string|&quot;Announce&quot;
)paren
suffix:semicolon
id|port.capability
op_assign
id|SNDRV_SEQ_PORT_CAP_READ
op_or
id|SNDRV_SEQ_PORT_CAP_SUBS_READ
suffix:semicolon
multiline_comment|/* for broadcast only */
id|port.kernel
op_assign
l_int|NULL
suffix:semicolon
id|port.type
op_assign
l_int|0
suffix:semicolon
id|port.flags
op_assign
id|SNDRV_SEQ_PORT_FLG_GIVEN_PORT
suffix:semicolon
id|port.addr.client
op_assign
id|sysclient
suffix:semicolon
id|port.addr.port
op_assign
id|SNDRV_SEQ_PORT_SYSTEM_ANNOUNCE
suffix:semicolon
id|snd_seq_kernel_client_ctl
c_func
(paren
id|sysclient
comma
id|SNDRV_SEQ_IOCTL_CREATE_PORT
comma
op_amp
id|port
)paren
suffix:semicolon
id|announce_port
op_assign
id|port.addr.port
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* unregister our internal client */
DECL|function|snd_seq_system_client_done
r_void
id|__exit
id|snd_seq_system_client_done
c_func
(paren
r_void
)paren
(brace
r_int
id|oldsysclient
op_assign
id|sysclient
suffix:semicolon
r_if
c_cond
(paren
id|oldsysclient
op_ge
l_int|0
)paren
(brace
id|sysclient
op_assign
op_minus
l_int|1
suffix:semicolon
id|announce_port
op_assign
op_minus
l_int|1
suffix:semicolon
id|snd_seq_delete_kernel_client
c_func
(paren
id|oldsysclient
)paren
suffix:semicolon
)brace
)brace
eof