multiline_comment|/*&n; * OSS compatible sequencer driver&n; *&n; * open/close and reset interface&n; *&n; * Copyright (C) 1998-1999 Takashi Iwai &lt;tiwai@suse.de&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
macro_line|#include &quot;seq_oss_device.h&quot;
macro_line|#include &quot;seq_oss_synth.h&quot;
macro_line|#include &quot;seq_oss_midi.h&quot;
macro_line|#include &quot;seq_oss_writeq.h&quot;
macro_line|#include &quot;seq_oss_readq.h&quot;
macro_line|#include &quot;seq_oss_timer.h&quot;
macro_line|#include &quot;seq_oss_event.h&quot;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/moduleparam.h&gt;
multiline_comment|/*&n; * common variables&n; */
DECL|variable|maxqlen
r_static
r_int
id|maxqlen
op_assign
id|SNDRV_SEQ_OSS_MAX_QLEN
suffix:semicolon
id|module_param
c_func
(paren
id|maxqlen
comma
r_int
comma
l_int|0444
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|maxqlen
comma
l_string|&quot;maximum queue length&quot;
)paren
suffix:semicolon
DECL|variable|system_client
r_static
r_int
id|system_client
op_assign
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* ALSA sequencer client number */
DECL|variable|system_port
r_static
r_int
id|system_port
op_assign
op_minus
l_int|1
suffix:semicolon
DECL|variable|num_clients
r_static
r_int
id|num_clients
suffix:semicolon
DECL|variable|client_table
r_static
id|seq_oss_devinfo_t
op_star
id|client_table
(braket
id|SNDRV_SEQ_OSS_MAX_CLIENTS
)braket
suffix:semicolon
multiline_comment|/*&n; * prototypes&n; */
r_static
r_int
id|receive_announce
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
r_private
comma
r_int
id|atomic
comma
r_int
id|hop
)paren
suffix:semicolon
r_static
r_int
id|translate_mode
c_func
(paren
r_struct
id|file
op_star
id|file
)paren
suffix:semicolon
r_static
r_int
id|create_port
c_func
(paren
id|seq_oss_devinfo_t
op_star
id|dp
)paren
suffix:semicolon
r_static
r_int
id|delete_port
c_func
(paren
id|seq_oss_devinfo_t
op_star
id|dp
)paren
suffix:semicolon
r_static
r_int
id|alloc_seq_queue
c_func
(paren
id|seq_oss_devinfo_t
op_star
id|dp
)paren
suffix:semicolon
r_static
r_int
id|delete_seq_queue
c_func
(paren
r_int
id|queue
)paren
suffix:semicolon
r_static
r_void
id|free_devinfo
c_func
(paren
r_void
op_star
r_private
)paren
suffix:semicolon
DECL|macro|call_ctl
mdefine_line|#define call_ctl(type,rec) snd_seq_kernel_client_ctl(system_client, type, rec)
multiline_comment|/*&n; * create sequencer client for OSS sequencer&n; */
r_int
id|__init
DECL|function|snd_seq_oss_create_client
id|snd_seq_oss_create_client
c_func
(paren
r_void
)paren
(brace
r_int
id|rc
suffix:semicolon
id|snd_seq_client_callback_t
id|callback
suffix:semicolon
id|snd_seq_client_info_t
op_star
id|info
suffix:semicolon
id|snd_seq_port_info_t
op_star
id|port
suffix:semicolon
id|snd_seq_port_callback_t
id|port_callback
suffix:semicolon
id|info
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|info
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|port
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|port
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|info
op_logical_or
op_logical_neg
id|port
)paren
(brace
id|rc
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|__error
suffix:semicolon
)brace
multiline_comment|/* create ALSA client */
id|memset
c_func
(paren
op_amp
id|callback
comma
l_int|0
comma
r_sizeof
(paren
id|callback
)paren
)paren
suffix:semicolon
id|callback.private_data
op_assign
l_int|NULL
suffix:semicolon
id|callback.allow_input
op_assign
l_int|1
suffix:semicolon
id|callback.allow_output
op_assign
l_int|1
suffix:semicolon
id|rc
op_assign
id|snd_seq_create_kernel_client
c_func
(paren
l_int|NULL
comma
id|SNDRV_SEQ_CLIENT_OSS
comma
op_amp
id|callback
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
OL
l_int|0
)paren
r_goto
id|__error
suffix:semicolon
id|system_client
op_assign
id|rc
suffix:semicolon
id|debug_printk
c_func
(paren
(paren
l_string|&quot;new client = %d&bslash;n&quot;
comma
id|rc
)paren
)paren
suffix:semicolon
multiline_comment|/* set client information */
id|memset
c_func
(paren
id|info
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|info
)paren
)paren
suffix:semicolon
id|info-&gt;client
op_assign
id|system_client
suffix:semicolon
id|info-&gt;type
op_assign
id|KERNEL_CLIENT
suffix:semicolon
id|strcpy
c_func
(paren
id|info-&gt;name
comma
l_string|&quot;OSS sequencer&quot;
)paren
suffix:semicolon
id|rc
op_assign
id|call_ctl
c_func
(paren
id|SNDRV_SEQ_IOCTL_SET_CLIENT_INFO
comma
id|info
)paren
suffix:semicolon
multiline_comment|/* look up midi devices */
id|snd_seq_oss_midi_lookup_ports
c_func
(paren
id|system_client
)paren
suffix:semicolon
multiline_comment|/* create annoucement receiver port */
id|memset
c_func
(paren
id|port
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|port
)paren
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|port-&gt;name
comma
l_string|&quot;Receiver&quot;
)paren
suffix:semicolon
id|port-&gt;addr.client
op_assign
id|system_client
suffix:semicolon
id|port-&gt;capability
op_assign
id|SNDRV_SEQ_PORT_CAP_WRITE
suffix:semicolon
multiline_comment|/* receive only */
id|port-&gt;type
op_assign
l_int|0
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|port_callback
comma
l_int|0
comma
r_sizeof
(paren
id|port_callback
)paren
)paren
suffix:semicolon
multiline_comment|/* don&squot;t set port_callback.owner here. otherwise the module counter&n;&t; * is incremented and we can no longer release the module..&n;&t; */
id|port_callback.event_input
op_assign
id|receive_announce
suffix:semicolon
id|port-&gt;kernel
op_assign
op_amp
id|port_callback
suffix:semicolon
id|call_ctl
c_func
(paren
id|SNDRV_SEQ_IOCTL_CREATE_PORT
comma
id|port
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|system_port
op_assign
id|port-&gt;addr.port
)paren
op_ge
l_int|0
)paren
(brace
id|snd_seq_port_subscribe_t
id|subs
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|subs
comma
l_int|0
comma
r_sizeof
(paren
id|subs
)paren
)paren
suffix:semicolon
id|subs.sender.client
op_assign
id|SNDRV_SEQ_CLIENT_SYSTEM
suffix:semicolon
id|subs.sender.port
op_assign
id|SNDRV_SEQ_PORT_SYSTEM_ANNOUNCE
suffix:semicolon
id|subs.dest.client
op_assign
id|system_client
suffix:semicolon
id|subs.dest.port
op_assign
id|system_port
suffix:semicolon
id|call_ctl
c_func
(paren
id|SNDRV_SEQ_IOCTL_SUBSCRIBE_PORT
comma
op_amp
id|subs
)paren
suffix:semicolon
)brace
id|rc
op_assign
l_int|0
suffix:semicolon
id|__error
suffix:colon
id|kfree
c_func
(paren
id|port
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|info
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
multiline_comment|/*&n; * receive annoucement from system port, and check the midi device&n; */
r_static
r_int
DECL|function|receive_announce
id|receive_announce
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
r_private
comma
r_int
id|atomic
comma
r_int
id|hop
)paren
(brace
id|snd_seq_port_info_t
id|pinfo
suffix:semicolon
r_if
c_cond
(paren
id|atomic
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* it must not happen */
r_switch
c_cond
(paren
id|ev-&gt;type
)paren
(brace
r_case
id|SNDRV_SEQ_EVENT_PORT_START
suffix:colon
r_case
id|SNDRV_SEQ_EVENT_PORT_CHANGE
suffix:colon
r_if
c_cond
(paren
id|ev-&gt;data.addr.client
op_eq
id|system_client
)paren
r_break
suffix:semicolon
multiline_comment|/* ignore myself */
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
id|pinfo.addr
op_assign
id|ev-&gt;data.addr
suffix:semicolon
r_if
c_cond
(paren
id|call_ctl
c_func
(paren
id|SNDRV_SEQ_IOCTL_GET_PORT_INFO
comma
op_amp
id|pinfo
)paren
op_ge
l_int|0
)paren
id|snd_seq_oss_midi_check_new_port
c_func
(paren
op_amp
id|pinfo
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SNDRV_SEQ_EVENT_PORT_EXIT
suffix:colon
r_if
c_cond
(paren
id|ev-&gt;data.addr.client
op_eq
id|system_client
)paren
r_break
suffix:semicolon
multiline_comment|/* ignore myself */
id|snd_seq_oss_midi_check_exit_port
c_func
(paren
id|ev-&gt;data.addr.client
comma
id|ev-&gt;data.addr.port
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * delete OSS sequencer client&n; */
r_int
DECL|function|snd_seq_oss_delete_client
id|snd_seq_oss_delete_client
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|system_client
op_ge
l_int|0
)paren
id|snd_seq_delete_kernel_client
c_func
(paren
id|system_client
)paren
suffix:semicolon
id|snd_seq_oss_midi_clear_all
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * open sequencer device&n; */
r_int
DECL|function|snd_seq_oss_open
id|snd_seq_oss_open
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_int
id|level
)paren
(brace
r_int
id|i
comma
id|rc
suffix:semicolon
id|seq_oss_devinfo_t
op_star
id|dp
suffix:semicolon
r_if
c_cond
(paren
(paren
id|dp
op_assign
id|kcalloc
c_func
(paren
l_int|1
comma
r_sizeof
(paren
op_star
id|dp
)paren
comma
id|GFP_KERNEL
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;can&squot;t malloc device info&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|debug_printk
c_func
(paren
(paren
l_string|&quot;oss_open: dp = %p&bslash;n&quot;
comma
id|dp
)paren
)paren
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
id|SNDRV_SEQ_OSS_MAX_CLIENTS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|client_table
(braket
id|i
)braket
op_eq
l_int|NULL
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
op_ge
id|SNDRV_SEQ_OSS_MAX_CLIENTS
)paren
(brace
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;too many applications&bslash;n&quot;
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|dp
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|dp-&gt;index
op_assign
id|i
suffix:semicolon
id|dp-&gt;cseq
op_assign
id|system_client
suffix:semicolon
id|dp-&gt;port
op_assign
op_minus
l_int|1
suffix:semicolon
id|dp-&gt;queue
op_assign
op_minus
l_int|1
suffix:semicolon
id|dp-&gt;readq
op_assign
l_int|NULL
suffix:semicolon
id|dp-&gt;writeq
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* look up synth and midi devices */
id|snd_seq_oss_synth_setup
c_func
(paren
id|dp
)paren
suffix:semicolon
id|snd_seq_oss_midi_setup
c_func
(paren
id|dp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dp-&gt;synth_opened
op_eq
l_int|0
op_logical_and
id|dp-&gt;max_mididev
op_eq
l_int|0
)paren
(brace
multiline_comment|/* snd_printk(KERN_ERR &quot;no device found&bslash;n&quot;); */
id|rc
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|_error
suffix:semicolon
)brace
multiline_comment|/* create port */
id|debug_printk
c_func
(paren
(paren
l_string|&quot;create new port&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|rc
op_assign
id|create_port
c_func
(paren
id|dp
)paren
)paren
OL
l_int|0
)paren
(brace
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;can&squot;t create port&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|_error
suffix:semicolon
)brace
multiline_comment|/* allocate queue */
id|debug_printk
c_func
(paren
(paren
l_string|&quot;allocate queue&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|rc
op_assign
id|alloc_seq_queue
c_func
(paren
id|dp
)paren
)paren
OL
l_int|0
)paren
r_goto
id|_error
suffix:semicolon
multiline_comment|/* set address */
id|dp-&gt;addr.client
op_assign
id|dp-&gt;cseq
suffix:semicolon
id|dp-&gt;addr.port
op_assign
id|dp-&gt;port
suffix:semicolon
multiline_comment|/*dp-&gt;addr.queue = dp-&gt;queue;*/
multiline_comment|/*dp-&gt;addr.channel = 0;*/
id|dp-&gt;seq_mode
op_assign
id|level
suffix:semicolon
multiline_comment|/* set up file mode */
id|dp-&gt;file_mode
op_assign
id|translate_mode
c_func
(paren
id|file
)paren
suffix:semicolon
multiline_comment|/* initialize read queue */
id|debug_printk
c_func
(paren
(paren
l_string|&quot;initialize read queue&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|is_read_mode
c_func
(paren
id|dp-&gt;file_mode
)paren
)paren
(brace
r_if
c_cond
(paren
(paren
id|dp-&gt;readq
op_assign
id|snd_seq_oss_readq_new
c_func
(paren
id|dp
comma
id|maxqlen
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|rc
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|_error
suffix:semicolon
)brace
)brace
multiline_comment|/* initialize write queue */
id|debug_printk
c_func
(paren
(paren
l_string|&quot;initialize write queue&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|is_write_mode
c_func
(paren
id|dp-&gt;file_mode
)paren
)paren
(brace
id|dp-&gt;writeq
op_assign
id|snd_seq_oss_writeq_new
c_func
(paren
id|dp
comma
id|maxqlen
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dp-&gt;writeq
op_eq
l_int|NULL
)paren
(brace
id|rc
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|_error
suffix:semicolon
)brace
)brace
multiline_comment|/* initialize timer */
id|debug_printk
c_func
(paren
(paren
l_string|&quot;initialize timer&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|dp-&gt;timer
op_assign
id|snd_seq_oss_timer_new
c_func
(paren
id|dp
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;can&squot;t alloc timer&bslash;n&quot;
)paren
suffix:semicolon
id|rc
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|_error
suffix:semicolon
)brace
id|debug_printk
c_func
(paren
(paren
l_string|&quot;timer initialized&bslash;n&quot;
)paren
)paren
suffix:semicolon
multiline_comment|/* set private data pointer */
id|file-&gt;private_data
op_assign
id|dp
suffix:semicolon
multiline_comment|/* set up for mode2 */
r_if
c_cond
(paren
id|level
op_eq
id|SNDRV_SEQ_OSS_MODE_MUSIC
)paren
id|snd_seq_oss_synth_setup_midi
c_func
(paren
id|dp
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|is_read_mode
c_func
(paren
id|dp-&gt;file_mode
)paren
)paren
id|snd_seq_oss_midi_open_all
c_func
(paren
id|dp
comma
id|SNDRV_SEQ_OSS_FILE_READ
)paren
suffix:semicolon
id|client_table
(braket
id|dp-&gt;index
)braket
op_assign
id|dp
suffix:semicolon
id|num_clients
op_increment
suffix:semicolon
id|debug_printk
c_func
(paren
(paren
l_string|&quot;open done&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|_error
suffix:colon
id|snd_seq_oss_synth_cleanup
c_func
(paren
id|dp
)paren
suffix:semicolon
id|snd_seq_oss_midi_cleanup
c_func
(paren
id|dp
)paren
suffix:semicolon
id|i
op_assign
id|dp-&gt;queue
suffix:semicolon
id|delete_port
c_func
(paren
id|dp
)paren
suffix:semicolon
id|delete_seq_queue
c_func
(paren
id|i
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
multiline_comment|/*&n; * translate file flags to private mode&n; */
r_static
r_int
DECL|function|translate_mode
id|translate_mode
c_func
(paren
r_struct
id|file
op_star
id|file
)paren
(brace
r_int
id|file_mode
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|file-&gt;f_flags
op_amp
id|O_ACCMODE
)paren
op_ne
id|O_RDONLY
)paren
id|file_mode
op_or_assign
id|SNDRV_SEQ_OSS_FILE_WRITE
suffix:semicolon
r_if
c_cond
(paren
(paren
id|file-&gt;f_flags
op_amp
id|O_ACCMODE
)paren
op_ne
id|O_WRONLY
)paren
id|file_mode
op_or_assign
id|SNDRV_SEQ_OSS_FILE_READ
suffix:semicolon
r_if
c_cond
(paren
id|file-&gt;f_flags
op_amp
id|O_NONBLOCK
)paren
id|file_mode
op_or_assign
id|SNDRV_SEQ_OSS_FILE_NONBLOCK
suffix:semicolon
r_return
id|file_mode
suffix:semicolon
)brace
multiline_comment|/*&n; * create sequencer port&n; */
r_static
r_int
DECL|function|create_port
id|create_port
c_func
(paren
id|seq_oss_devinfo_t
op_star
id|dp
)paren
(brace
r_int
id|rc
suffix:semicolon
id|snd_seq_port_info_t
id|port
suffix:semicolon
id|snd_seq_port_callback_t
id|callback
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
id|port.addr.client
op_assign
id|dp-&gt;cseq
suffix:semicolon
id|sprintf
c_func
(paren
id|port.name
comma
l_string|&quot;Sequencer-%d&quot;
comma
id|dp-&gt;index
)paren
suffix:semicolon
id|port.capability
op_assign
id|SNDRV_SEQ_PORT_CAP_READ
op_or
id|SNDRV_SEQ_PORT_CAP_WRITE
suffix:semicolon
multiline_comment|/* no subscription */
id|port.type
op_assign
id|SNDRV_SEQ_PORT_TYPE_SPECIFIC
suffix:semicolon
id|port.midi_channels
op_assign
l_int|128
suffix:semicolon
id|port.synth_voices
op_assign
l_int|128
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|callback
comma
l_int|0
comma
r_sizeof
(paren
id|callback
)paren
)paren
suffix:semicolon
id|callback.owner
op_assign
id|THIS_MODULE
suffix:semicolon
id|callback.private_data
op_assign
id|dp
suffix:semicolon
id|callback.event_input
op_assign
id|snd_seq_oss_event_input
suffix:semicolon
id|callback.private_free
op_assign
id|free_devinfo
suffix:semicolon
id|port.kernel
op_assign
op_amp
id|callback
suffix:semicolon
id|rc
op_assign
id|call_ctl
c_func
(paren
id|SNDRV_SEQ_IOCTL_CREATE_PORT
comma
op_amp
id|port
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
OL
l_int|0
)paren
r_return
id|rc
suffix:semicolon
id|dp-&gt;port
op_assign
id|port.addr.port
suffix:semicolon
id|debug_printk
c_func
(paren
(paren
l_string|&quot;new port = %d&bslash;n&quot;
comma
id|port.addr.port
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * delete ALSA port&n; */
r_static
r_int
DECL|function|delete_port
id|delete_port
c_func
(paren
id|seq_oss_devinfo_t
op_star
id|dp
)paren
(brace
r_if
c_cond
(paren
id|dp-&gt;port
OL
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|debug_printk
c_func
(paren
(paren
l_string|&quot;delete_port %i&bslash;n&quot;
comma
id|dp-&gt;port
)paren
)paren
suffix:semicolon
r_return
id|snd_seq_event_port_detach
c_func
(paren
id|dp-&gt;cseq
comma
id|dp-&gt;port
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * allocate a queue&n; */
r_static
r_int
DECL|function|alloc_seq_queue
id|alloc_seq_queue
c_func
(paren
id|seq_oss_devinfo_t
op_star
id|dp
)paren
(brace
id|snd_seq_queue_info_t
id|qinfo
suffix:semicolon
r_int
id|rc
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|qinfo
comma
l_int|0
comma
r_sizeof
(paren
id|qinfo
)paren
)paren
suffix:semicolon
id|qinfo.owner
op_assign
id|system_client
suffix:semicolon
id|qinfo.locked
op_assign
l_int|1
suffix:semicolon
id|strcpy
c_func
(paren
id|qinfo.name
comma
l_string|&quot;OSS Sequencer Emulation&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|rc
op_assign
id|call_ctl
c_func
(paren
id|SNDRV_SEQ_IOCTL_CREATE_QUEUE
comma
op_amp
id|qinfo
)paren
)paren
OL
l_int|0
)paren
r_return
id|rc
suffix:semicolon
id|dp-&gt;queue
op_assign
id|qinfo.queue
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * release queue&n; */
r_static
r_int
DECL|function|delete_seq_queue
id|delete_seq_queue
c_func
(paren
r_int
id|queue
)paren
(brace
id|snd_seq_queue_info_t
id|qinfo
suffix:semicolon
r_int
id|rc
suffix:semicolon
r_if
c_cond
(paren
id|queue
OL
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|qinfo
comma
l_int|0
comma
r_sizeof
(paren
id|qinfo
)paren
)paren
suffix:semicolon
id|qinfo.queue
op_assign
id|queue
suffix:semicolon
id|rc
op_assign
id|call_ctl
c_func
(paren
id|SNDRV_SEQ_IOCTL_DELETE_QUEUE
comma
op_amp
id|qinfo
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
OL
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;seq-oss: unable to delete queue %d (%d)&bslash;n&quot;
comma
id|queue
comma
id|rc
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
multiline_comment|/*&n; * free device informations - private_free callback of port&n; */
r_static
r_void
DECL|function|free_devinfo
id|free_devinfo
c_func
(paren
r_void
op_star
r_private
)paren
(brace
id|seq_oss_devinfo_t
op_star
id|dp
op_assign
(paren
id|seq_oss_devinfo_t
op_star
)paren
r_private
suffix:semicolon
r_if
c_cond
(paren
id|dp-&gt;timer
)paren
id|snd_seq_oss_timer_delete
c_func
(paren
id|dp-&gt;timer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dp-&gt;writeq
)paren
id|snd_seq_oss_writeq_delete
c_func
(paren
id|dp-&gt;writeq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dp-&gt;readq
)paren
id|snd_seq_oss_readq_delete
c_func
(paren
id|dp-&gt;readq
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|dp
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * close sequencer device&n; */
r_void
DECL|function|snd_seq_oss_release
id|snd_seq_oss_release
c_func
(paren
id|seq_oss_devinfo_t
op_star
id|dp
)paren
(brace
r_int
id|queue
suffix:semicolon
id|client_table
(braket
id|dp-&gt;index
)braket
op_assign
l_int|NULL
suffix:semicolon
id|num_clients
op_decrement
suffix:semicolon
id|debug_printk
c_func
(paren
(paren
l_string|&quot;resetting..&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|snd_seq_oss_reset
c_func
(paren
id|dp
)paren
suffix:semicolon
id|debug_printk
c_func
(paren
(paren
l_string|&quot;cleaning up..&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|snd_seq_oss_synth_cleanup
c_func
(paren
id|dp
)paren
suffix:semicolon
id|snd_seq_oss_midi_cleanup
c_func
(paren
id|dp
)paren
suffix:semicolon
multiline_comment|/* clear slot */
id|debug_printk
c_func
(paren
(paren
l_string|&quot;releasing resource..&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|queue
op_assign
id|dp-&gt;queue
suffix:semicolon
r_if
c_cond
(paren
id|dp-&gt;port
op_ge
l_int|0
)paren
id|delete_port
c_func
(paren
id|dp
)paren
suffix:semicolon
id|delete_seq_queue
c_func
(paren
id|queue
)paren
suffix:semicolon
id|debug_printk
c_func
(paren
(paren
l_string|&quot;release done&bslash;n&quot;
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Wait until the queue is empty (if we don&squot;t have nonblock)&n; */
r_void
DECL|function|snd_seq_oss_drain_write
id|snd_seq_oss_drain_write
c_func
(paren
id|seq_oss_devinfo_t
op_star
id|dp
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|dp-&gt;timer-&gt;running
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|is_write_mode
c_func
(paren
id|dp-&gt;file_mode
)paren
op_logical_and
op_logical_neg
id|is_nonblock_mode
c_func
(paren
id|dp-&gt;file_mode
)paren
op_logical_and
id|dp-&gt;writeq
)paren
(brace
id|debug_printk
c_func
(paren
(paren
l_string|&quot;syncing..&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_while
c_loop
(paren
id|snd_seq_oss_writeq_sync
c_func
(paren
id|dp-&gt;writeq
)paren
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * reset sequencer devices&n; */
r_void
DECL|function|snd_seq_oss_reset
id|snd_seq_oss_reset
c_func
(paren
id|seq_oss_devinfo_t
op_star
id|dp
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/* reset all synth devices */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|dp-&gt;max_synthdev
suffix:semicolon
id|i
op_increment
)paren
id|snd_seq_oss_synth_reset
c_func
(paren
id|dp
comma
id|i
)paren
suffix:semicolon
multiline_comment|/* reset all midi devices */
r_if
c_cond
(paren
id|dp-&gt;seq_mode
op_ne
id|SNDRV_SEQ_OSS_MODE_MUSIC
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|dp-&gt;max_mididev
suffix:semicolon
id|i
op_increment
)paren
id|snd_seq_oss_midi_reset
c_func
(paren
id|dp
comma
id|i
)paren
suffix:semicolon
)brace
multiline_comment|/* remove queues */
r_if
c_cond
(paren
id|dp-&gt;readq
)paren
id|snd_seq_oss_readq_clear
c_func
(paren
id|dp-&gt;readq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dp-&gt;writeq
)paren
id|snd_seq_oss_writeq_clear
c_func
(paren
id|dp-&gt;writeq
)paren
suffix:semicolon
multiline_comment|/* reset timer */
id|snd_seq_oss_timer_stop
c_func
(paren
id|dp-&gt;timer
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * misc. functions for proc interface&n; */
r_char
op_star
DECL|function|enabled_str
id|enabled_str
c_func
(paren
r_int
r_bool
)paren
(brace
r_return
r_bool
ques
c_cond
l_string|&quot;enabled&quot;
suffix:colon
l_string|&quot;disabled&quot;
suffix:semicolon
)brace
r_static
r_char
op_star
DECL|function|filemode_str
id|filemode_str
c_func
(paren
r_int
id|val
)paren
(brace
r_static
r_char
op_star
id|str
(braket
)braket
op_assign
(brace
l_string|&quot;none&quot;
comma
l_string|&quot;read&quot;
comma
l_string|&quot;write&quot;
comma
l_string|&quot;read/write&quot;
comma
)brace
suffix:semicolon
r_return
id|str
(braket
id|val
op_amp
id|SNDRV_SEQ_OSS_FILE_ACMODE
)braket
suffix:semicolon
)brace
multiline_comment|/*&n; * proc interface&n; */
r_void
DECL|function|snd_seq_oss_system_info_read
id|snd_seq_oss_system_info_read
c_func
(paren
id|snd_info_buffer_t
op_star
id|buf
)paren
(brace
r_int
id|i
suffix:semicolon
id|seq_oss_devinfo_t
op_star
id|dp
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buf
comma
l_string|&quot;ALSA client number %d&bslash;n&quot;
comma
id|system_client
)paren
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buf
comma
l_string|&quot;ALSA receiver port %d&bslash;n&quot;
comma
id|system_port
)paren
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buf
comma
l_string|&quot;&bslash;nNumber of applications: %d&bslash;n&quot;
comma
id|num_clients
)paren
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
id|num_clients
suffix:semicolon
id|i
op_increment
)paren
(brace
id|snd_iprintf
c_func
(paren
id|buf
comma
l_string|&quot;&bslash;nApplication %d: &quot;
comma
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|dp
op_assign
id|client_table
(braket
id|i
)braket
)paren
op_eq
l_int|NULL
)paren
(brace
id|snd_iprintf
c_func
(paren
id|buf
comma
l_string|&quot;*empty*&bslash;n&quot;
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|snd_iprintf
c_func
(paren
id|buf
comma
l_string|&quot;port %d : queue %d&bslash;n&quot;
comma
id|dp-&gt;port
comma
id|dp-&gt;queue
)paren
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buf
comma
l_string|&quot;  sequencer mode = %s : file open mode = %s&bslash;n&quot;
comma
(paren
id|dp-&gt;seq_mode
ques
c_cond
l_string|&quot;music&quot;
suffix:colon
l_string|&quot;synth&quot;
)paren
comma
id|filemode_str
c_func
(paren
id|dp-&gt;file_mode
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dp-&gt;seq_mode
)paren
id|snd_iprintf
c_func
(paren
id|buf
comma
l_string|&quot;  timer tempo = %d, timebase = %d&bslash;n&quot;
comma
id|dp-&gt;timer-&gt;oss_tempo
comma
id|dp-&gt;timer-&gt;oss_timebase
)paren
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buf
comma
l_string|&quot;  max queue length %d&bslash;n&quot;
comma
id|maxqlen
)paren
suffix:semicolon
r_if
c_cond
(paren
id|is_read_mode
c_func
(paren
id|dp-&gt;file_mode
)paren
op_logical_and
id|dp-&gt;readq
)paren
id|snd_seq_oss_readq_info_read
c_func
(paren
id|dp-&gt;readq
comma
id|buf
)paren
suffix:semicolon
)brace
)brace
eof
