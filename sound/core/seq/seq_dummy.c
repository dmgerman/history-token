multiline_comment|/*&n; * ALSA sequencer MIDI-through client&n; * Copyright (c) 1999-2000 by Takashi Iwai &lt;tiwai@suse.de&gt;&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/moduleparam.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &quot;seq_clientmgr.h&quot;
macro_line|#include &lt;sound/initval.h&gt;
macro_line|#include &lt;sound/asoundef.h&gt;
multiline_comment|/*&n;&n;  Sequencer MIDI-through client&n;&n;  This gives a simple midi-through client.  All the normal input events&n;  are redirected to output port immediately.&n;  The routing can be done via aconnect program in alsa-utils.&n;&n;  Each client has a static client number 62 (= SNDRV_SEQ_CLIENT_DUMMY).&n;  If you want to auto-load this module, you may add the following alias&n;  in your /etc/conf.modules file.&n;&n;&t;alias snd-seq-client-62  snd-seq-dummy&n;&n;  The module is loaded on demand for client 62, or /proc/asound/seq/&n;  is accessed.  If you don&squot;t need this module to be loaded, alias&n;  snd-seq-client-62 as &quot;off&quot;.  This will help modprobe.&n;&n;  The number of ports to be created can be specified via the module&n;  parameter &quot;ports&quot;.  For example, to create four ports, add the&n;  following option in /etc/modprobe.conf:&n;&n;&t;option snd-seq-dummy ports=4&n;&n;  The modle option &quot;duplex=1&quot; enables duplex operation to the port.&n;  In duplex mode, a pair of ports are created instead of single port,&n;  and events are tunneled between pair-ports.  For example, input to&n;  port A is sent to output port of another port B and vice versa.&n;  In duplex mode, each port has DUPLEX capability.&n;&n; */
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Takashi Iwai &lt;tiwai@suse.de&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;ALSA sequencer MIDI-through client&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_ALIAS
c_func
(paren
l_string|&quot;snd-seq-client-&quot;
id|__stringify
c_func
(paren
id|SNDRV_SEQ_CLIENT_DUMMY
)paren
)paren
suffix:semicolon
DECL|variable|ports
r_static
r_int
id|ports
op_assign
l_int|1
suffix:semicolon
DECL|variable|duplex
r_static
r_int
id|duplex
op_assign
l_int|0
suffix:semicolon
id|module_param
c_func
(paren
id|ports
comma
r_int
comma
l_int|0444
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|ports
comma
l_string|&quot;number of ports to be created&quot;
)paren
suffix:semicolon
id|module_param
c_func
(paren
id|duplex
comma
r_bool
comma
l_int|0444
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|duplex
comma
l_string|&quot;create DUPLEX ports&quot;
)paren
suffix:semicolon
DECL|struct|snd_seq_dummy_port
r_typedef
r_struct
id|snd_seq_dummy_port
(brace
DECL|member|client
r_int
id|client
suffix:semicolon
DECL|member|port
r_int
id|port
suffix:semicolon
DECL|member|duplex
r_int
id|duplex
suffix:semicolon
DECL|member|connect
r_int
id|connect
suffix:semicolon
DECL|typedef|snd_seq_dummy_port_t
)brace
id|snd_seq_dummy_port_t
suffix:semicolon
DECL|variable|my_client
r_static
r_int
id|my_client
op_assign
op_minus
l_int|1
suffix:semicolon
multiline_comment|/*&n; * unuse callback - send ALL_SOUNDS_OFF and RESET_CONTROLLERS events&n; * to subscribers.&n; * Note: this callback is called only after all subscribers are removed.&n; */
r_static
r_int
DECL|function|dummy_unuse
id|dummy_unuse
c_func
(paren
r_void
op_star
id|private_data
comma
id|snd_seq_port_subscribe_t
op_star
id|info
)paren
(brace
id|snd_seq_dummy_port_t
op_star
id|p
suffix:semicolon
r_int
id|i
suffix:semicolon
id|snd_seq_event_t
id|ev
suffix:semicolon
id|p
op_assign
id|private_data
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|ev
comma
l_int|0
comma
r_sizeof
(paren
id|ev
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;duplex
)paren
id|ev.source.port
op_assign
id|p-&gt;connect
suffix:semicolon
r_else
id|ev.source.port
op_assign
id|p-&gt;port
suffix:semicolon
id|ev.dest.client
op_assign
id|SNDRV_SEQ_ADDRESS_SUBSCRIBERS
suffix:semicolon
id|ev.type
op_assign
id|SNDRV_SEQ_EVENT_CONTROLLER
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|16
suffix:semicolon
id|i
op_increment
)paren
(brace
id|ev.data.control.channel
op_assign
id|i
suffix:semicolon
id|ev.data.control.param
op_assign
id|MIDI_CTL_ALL_SOUNDS_OFF
suffix:semicolon
id|snd_seq_kernel_client_dispatch
c_func
(paren
id|p-&gt;client
comma
op_amp
id|ev
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
id|ev.data.control.param
op_assign
id|MIDI_CTL_RESET_CONTROLLERS
suffix:semicolon
id|snd_seq_kernel_client_dispatch
c_func
(paren
id|p-&gt;client
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
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * event input callback - just redirect events to subscribers&n; */
r_static
r_int
DECL|function|dummy_input
id|dummy_input
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
id|snd_seq_dummy_port_t
op_star
id|p
suffix:semicolon
id|snd_seq_event_t
id|tmpev
suffix:semicolon
id|p
op_assign
id|private_data
suffix:semicolon
r_if
c_cond
(paren
id|ev-&gt;source.client
op_eq
id|SNDRV_SEQ_CLIENT_SYSTEM
op_logical_or
id|ev-&gt;type
op_eq
id|SNDRV_SEQ_EVENT_KERNEL_ERROR
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* ignore system messages */
id|tmpev
op_assign
op_star
id|ev
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;duplex
)paren
id|tmpev.source.port
op_assign
id|p-&gt;connect
suffix:semicolon
r_else
id|tmpev.source.port
op_assign
id|p-&gt;port
suffix:semicolon
id|tmpev.dest.client
op_assign
id|SNDRV_SEQ_ADDRESS_SUBSCRIBERS
suffix:semicolon
r_return
id|snd_seq_kernel_client_dispatch
c_func
(paren
id|p-&gt;client
comma
op_amp
id|tmpev
comma
id|atomic
comma
id|hop
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * free_private callback&n; */
r_static
r_void
DECL|function|dummy_free
id|dummy_free
c_func
(paren
r_void
op_star
id|private_data
)paren
(brace
id|snd_seq_dummy_port_t
op_star
id|p
suffix:semicolon
id|p
op_assign
id|private_data
suffix:semicolon
id|kfree
c_func
(paren
id|p
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * create a port&n; */
r_static
id|snd_seq_dummy_port_t
id|__init
op_star
DECL|function|create_port
id|create_port
c_func
(paren
r_int
id|idx
comma
r_int
id|type
)paren
(brace
id|snd_seq_port_info_t
id|pinfo
suffix:semicolon
id|snd_seq_port_callback_t
id|pcb
suffix:semicolon
id|snd_seq_dummy_port_t
op_star
id|rec
suffix:semicolon
r_if
c_cond
(paren
(paren
id|rec
op_assign
id|kcalloc
c_func
(paren
l_int|1
comma
r_sizeof
(paren
op_star
id|rec
)paren
comma
id|GFP_KERNEL
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
l_int|NULL
suffix:semicolon
id|rec-&gt;client
op_assign
id|my_client
suffix:semicolon
id|rec-&gt;duplex
op_assign
id|duplex
suffix:semicolon
id|rec-&gt;connect
op_assign
l_int|0
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|pinfo
comma
l_int|0
comma
r_sizeof
(paren
id|pinfo
)paren
)paren
suffix:semicolon
id|pinfo.addr.client
op_assign
id|my_client
suffix:semicolon
r_if
c_cond
(paren
id|duplex
)paren
id|sprintf
c_func
(paren
id|pinfo.name
comma
l_string|&quot;Midi Through Port-%d:%c&quot;
comma
id|idx
comma
(paren
id|type
ques
c_cond
l_char|&squot;B&squot;
suffix:colon
l_char|&squot;A&squot;
)paren
)paren
suffix:semicolon
r_else
id|sprintf
c_func
(paren
id|pinfo.name
comma
l_string|&quot;Midi Through Port-%d&quot;
comma
id|idx
)paren
suffix:semicolon
id|pinfo.capability
op_assign
id|SNDRV_SEQ_PORT_CAP_READ
op_or
id|SNDRV_SEQ_PORT_CAP_SUBS_READ
suffix:semicolon
id|pinfo.capability
op_or_assign
id|SNDRV_SEQ_PORT_CAP_WRITE
op_or
id|SNDRV_SEQ_PORT_CAP_SUBS_WRITE
suffix:semicolon
r_if
c_cond
(paren
id|duplex
)paren
id|pinfo.capability
op_or_assign
id|SNDRV_SEQ_PORT_CAP_DUPLEX
suffix:semicolon
id|pinfo.type
op_assign
id|SNDRV_SEQ_PORT_TYPE_MIDI_GENERIC
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|pcb
comma
l_int|0
comma
r_sizeof
(paren
id|pcb
)paren
)paren
suffix:semicolon
id|pcb.owner
op_assign
id|THIS_MODULE
suffix:semicolon
id|pcb.unuse
op_assign
id|dummy_unuse
suffix:semicolon
id|pcb.event_input
op_assign
id|dummy_input
suffix:semicolon
id|pcb.private_free
op_assign
id|dummy_free
suffix:semicolon
id|pcb.private_data
op_assign
id|rec
suffix:semicolon
id|pinfo.kernel
op_assign
op_amp
id|pcb
suffix:semicolon
r_if
c_cond
(paren
id|snd_seq_kernel_client_ctl
c_func
(paren
id|my_client
comma
id|SNDRV_SEQ_IOCTL_CREATE_PORT
comma
op_amp
id|pinfo
)paren
OL
l_int|0
)paren
(brace
id|kfree
c_func
(paren
id|rec
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|rec-&gt;port
op_assign
id|pinfo.addr.port
suffix:semicolon
r_return
id|rec
suffix:semicolon
)brace
multiline_comment|/*&n; * register client and create ports&n; */
r_static
r_int
id|__init
DECL|function|register_client
id|register_client
c_func
(paren
r_void
)paren
(brace
id|snd_seq_client_callback_t
id|cb
suffix:semicolon
id|snd_seq_client_info_t
id|cinfo
suffix:semicolon
id|snd_seq_dummy_port_t
op_star
id|rec1
comma
op_star
id|rec2
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|ports
OL
l_int|1
)paren
(brace
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;invalid number of ports %d&bslash;n&quot;
comma
id|ports
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/* create client */
id|memset
c_func
(paren
op_amp
id|cb
comma
l_int|0
comma
r_sizeof
(paren
id|cb
)paren
)paren
suffix:semicolon
id|cb.allow_input
op_assign
l_int|1
suffix:semicolon
id|cb.allow_output
op_assign
l_int|1
suffix:semicolon
id|my_client
op_assign
id|snd_seq_create_kernel_client
c_func
(paren
l_int|NULL
comma
id|SNDRV_SEQ_CLIENT_DUMMY
comma
op_amp
id|cb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|my_client
OL
l_int|0
)paren
r_return
id|my_client
suffix:semicolon
multiline_comment|/* set client name */
id|memset
c_func
(paren
op_amp
id|cinfo
comma
l_int|0
comma
r_sizeof
(paren
id|cinfo
)paren
)paren
suffix:semicolon
id|cinfo.client
op_assign
id|my_client
suffix:semicolon
id|cinfo.type
op_assign
id|KERNEL_CLIENT
suffix:semicolon
id|strcpy
c_func
(paren
id|cinfo.name
comma
l_string|&quot;Midi Through&quot;
)paren
suffix:semicolon
id|snd_seq_kernel_client_ctl
c_func
(paren
id|my_client
comma
id|SNDRV_SEQ_IOCTL_SET_CLIENT_INFO
comma
op_amp
id|cinfo
)paren
suffix:semicolon
multiline_comment|/* create ports */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|ports
suffix:semicolon
id|i
op_increment
)paren
(brace
id|rec1
op_assign
id|create_port
c_func
(paren
id|i
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rec1
op_eq
l_int|NULL
)paren
(brace
id|snd_seq_delete_kernel_client
c_func
(paren
id|my_client
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
r_if
c_cond
(paren
id|duplex
)paren
(brace
id|rec2
op_assign
id|create_port
c_func
(paren
id|i
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rec2
op_eq
l_int|NULL
)paren
(brace
id|snd_seq_delete_kernel_client
c_func
(paren
id|my_client
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|rec1-&gt;connect
op_assign
id|rec2-&gt;port
suffix:semicolon
id|rec2-&gt;connect
op_assign
id|rec1-&gt;port
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * delete client if exists&n; */
r_static
r_void
id|__exit
DECL|function|delete_client
id|delete_client
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|my_client
op_ge
l_int|0
)paren
id|snd_seq_delete_kernel_client
c_func
(paren
id|my_client
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *  Init part&n; */
DECL|function|alsa_seq_dummy_init
r_static
r_int
id|__init
id|alsa_seq_dummy_init
c_func
(paren
r_void
)paren
(brace
r_int
id|err
suffix:semicolon
id|snd_seq_autoload_lock
c_func
(paren
)paren
suffix:semicolon
id|err
op_assign
id|register_client
c_func
(paren
)paren
suffix:semicolon
id|snd_seq_autoload_unlock
c_func
(paren
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|alsa_seq_dummy_exit
r_static
r_void
id|__exit
id|alsa_seq_dummy_exit
c_func
(paren
r_void
)paren
(brace
id|delete_client
c_func
(paren
)paren
suffix:semicolon
)brace
id|module_init
c_func
(paren
id|alsa_seq_dummy_init
)paren
id|module_exit
c_func
(paren
id|alsa_seq_dummy_exit
)paren
eof
