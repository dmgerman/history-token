multiline_comment|/*&n; *   32bit -&gt; 64bit ioctl wrapper for sequencer API&n; *   Copyright (c) by Takashi Iwai &lt;tiwai@suse.de&gt;&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &lt;sound/timer.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;sound/asequencer.h&gt;
macro_line|#include &quot;ioctl32.h&quot;
DECL|struct|sndrv_seq_port_info32
r_struct
id|sndrv_seq_port_info32
(brace
DECL|member|addr
r_struct
id|sndrv_seq_addr
id|addr
suffix:semicolon
multiline_comment|/* client/port numbers */
DECL|member|name
r_char
id|name
(braket
l_int|64
)braket
suffix:semicolon
multiline_comment|/* port name */
DECL|member|capability
id|u32
id|capability
suffix:semicolon
multiline_comment|/* port capability bits */
DECL|member|type
id|u32
id|type
suffix:semicolon
multiline_comment|/* port type bits */
DECL|member|midi_channels
id|s32
id|midi_channels
suffix:semicolon
multiline_comment|/* channels per MIDI port */
DECL|member|midi_voices
id|s32
id|midi_voices
suffix:semicolon
multiline_comment|/* voices per MIDI port */
DECL|member|synth_voices
id|s32
id|synth_voices
suffix:semicolon
multiline_comment|/* voices per SYNTH port */
DECL|member|read_use
id|s32
id|read_use
suffix:semicolon
multiline_comment|/* R/O: subscribers for output (from this port) */
DECL|member|write_use
id|s32
id|write_use
suffix:semicolon
multiline_comment|/* R/O: subscribers for input (to this port) */
DECL|member|kernel
id|u32
id|kernel
suffix:semicolon
multiline_comment|/* reserved for kernel use (must be NULL) */
DECL|member|flags
id|u32
id|flags
suffix:semicolon
multiline_comment|/* misc. conditioning */
DECL|member|time_queue
r_int
r_char
id|time_queue
suffix:semicolon
multiline_comment|/* queue # for timestamping */
DECL|member|reserved
r_char
id|reserved
(braket
l_int|59
)braket
suffix:semicolon
multiline_comment|/* for future use */
)brace
suffix:semicolon
DECL|macro|CVT_sndrv_seq_port_info
mdefine_line|#define CVT_sndrv_seq_port_info()&bslash;&n;{&bslash;&n;&t;COPY(addr);&bslash;&n;&t;COPY_ARRAY(name);&bslash;&n;&t;COPY(capability);&bslash;&n;&t;COPY(type);&bslash;&n;&t;COPY(midi_channels);&bslash;&n;&t;COPY(midi_voices);&bslash;&n;&t;COPY(synth_voices);&bslash;&n;&t;COPY(read_use);&bslash;&n;&t;COPY(write_use);&bslash;&n;&t;COPY(flags);&bslash;&n;&t;COPY(time_queue);&bslash;&n;}
DECL|variable|seq_port_info
id|DEFINE_ALSA_IOCTL
c_func
(paren
id|seq_port_info
)paren
suffix:semicolon
id|DEFINE_ALSA_IOCTL_ENTRY
c_func
(paren
id|create_port
comma
id|seq_port_info
comma
id|SNDRV_SEQ_IOCTL_CREATE_PORT
)paren
suffix:semicolon
id|DEFINE_ALSA_IOCTL_ENTRY
c_func
(paren
id|delete_port
comma
id|seq_port_info
comma
id|SNDRV_SEQ_IOCTL_DELETE_PORT
)paren
suffix:semicolon
id|DEFINE_ALSA_IOCTL_ENTRY
c_func
(paren
id|get_port_info
comma
id|seq_port_info
comma
id|SNDRV_SEQ_IOCTL_GET_PORT_INFO
)paren
suffix:semicolon
id|DEFINE_ALSA_IOCTL_ENTRY
c_func
(paren
id|set_port_info
comma
id|seq_port_info
comma
id|SNDRV_SEQ_IOCTL_SET_PORT_INFO
)paren
suffix:semicolon
id|DEFINE_ALSA_IOCTL_ENTRY
c_func
(paren
id|query_next_port
comma
id|seq_port_info
comma
id|SNDRV_SEQ_IOCTL_QUERY_NEXT_PORT
)paren
suffix:semicolon
multiline_comment|/*&n; */
DECL|macro|AP
mdefine_line|#define AP(x) snd_ioctl32_##x
r_enum
(brace
DECL|enumerator|SNDRV_SEQ_IOCTL_CREATE_PORT32
id|SNDRV_SEQ_IOCTL_CREATE_PORT32
op_assign
id|_IOWR
c_func
(paren
l_char|&squot;S&squot;
comma
l_int|0x20
comma
r_struct
id|sndrv_seq_port_info32
)paren
comma
DECL|enumerator|SNDRV_SEQ_IOCTL_DELETE_PORT32
id|SNDRV_SEQ_IOCTL_DELETE_PORT32
op_assign
id|_IOW
(paren
l_char|&squot;S&squot;
comma
l_int|0x21
comma
r_struct
id|sndrv_seq_port_info32
)paren
comma
DECL|enumerator|SNDRV_SEQ_IOCTL_GET_PORT_INFO32
id|SNDRV_SEQ_IOCTL_GET_PORT_INFO32
op_assign
id|_IOWR
c_func
(paren
l_char|&squot;S&squot;
comma
l_int|0x22
comma
r_struct
id|sndrv_seq_port_info32
)paren
comma
DECL|enumerator|SNDRV_SEQ_IOCTL_SET_PORT_INFO32
id|SNDRV_SEQ_IOCTL_SET_PORT_INFO32
op_assign
id|_IOW
(paren
l_char|&squot;S&squot;
comma
l_int|0x23
comma
r_struct
id|sndrv_seq_port_info32
)paren
comma
DECL|enumerator|SNDRV_SEQ_IOCTL_QUERY_NEXT_PORT32
id|SNDRV_SEQ_IOCTL_QUERY_NEXT_PORT32
op_assign
id|_IOWR
c_func
(paren
l_char|&squot;S&squot;
comma
l_int|0x52
comma
r_struct
id|sndrv_seq_port_info32
)paren
comma
)brace
suffix:semicolon
DECL|variable|seq_mappers
r_struct
id|ioctl32_mapper
id|seq_mappers
(braket
)braket
op_assign
(brace
id|MAP_COMPAT
c_func
(paren
id|SNDRV_SEQ_IOCTL_PVERSION
)paren
comma
id|MAP_COMPAT
c_func
(paren
id|SNDRV_SEQ_IOCTL_CLIENT_ID
)paren
comma
id|MAP_COMPAT
c_func
(paren
id|SNDRV_SEQ_IOCTL_SYSTEM_INFO
)paren
comma
id|MAP_COMPAT
c_func
(paren
id|SNDRV_SEQ_IOCTL_GET_CLIENT_INFO
)paren
comma
id|MAP_COMPAT
c_func
(paren
id|SNDRV_SEQ_IOCTL_SET_CLIENT_INFO
)paren
comma
(brace
id|SNDRV_SEQ_IOCTL_CREATE_PORT32
comma
id|AP
c_func
(paren
id|create_port
)paren
)brace
comma
(brace
id|SNDRV_SEQ_IOCTL_DELETE_PORT32
comma
id|AP
c_func
(paren
id|delete_port
)paren
)brace
comma
(brace
id|SNDRV_SEQ_IOCTL_GET_PORT_INFO32
comma
id|AP
c_func
(paren
id|get_port_info
)paren
)brace
comma
(brace
id|SNDRV_SEQ_IOCTL_SET_PORT_INFO32
comma
id|AP
c_func
(paren
id|set_port_info
)paren
)brace
comma
id|MAP_COMPAT
c_func
(paren
id|SNDRV_SEQ_IOCTL_SUBSCRIBE_PORT
)paren
comma
id|MAP_COMPAT
c_func
(paren
id|SNDRV_SEQ_IOCTL_UNSUBSCRIBE_PORT
)paren
comma
id|MAP_COMPAT
c_func
(paren
id|SNDRV_SEQ_IOCTL_CREATE_QUEUE
)paren
comma
id|MAP_COMPAT
c_func
(paren
id|SNDRV_SEQ_IOCTL_DELETE_QUEUE
)paren
comma
id|MAP_COMPAT
c_func
(paren
id|SNDRV_SEQ_IOCTL_GET_QUEUE_INFO
)paren
comma
id|MAP_COMPAT
c_func
(paren
id|SNDRV_SEQ_IOCTL_SET_QUEUE_INFO
)paren
comma
id|MAP_COMPAT
c_func
(paren
id|SNDRV_SEQ_IOCTL_GET_NAMED_QUEUE
)paren
comma
id|MAP_COMPAT
c_func
(paren
id|SNDRV_SEQ_IOCTL_GET_QUEUE_STATUS
)paren
comma
id|MAP_COMPAT
c_func
(paren
id|SNDRV_SEQ_IOCTL_GET_QUEUE_TEMPO
)paren
comma
id|MAP_COMPAT
c_func
(paren
id|SNDRV_SEQ_IOCTL_SET_QUEUE_TEMPO
)paren
comma
id|MAP_COMPAT
c_func
(paren
id|SNDRV_SEQ_IOCTL_GET_QUEUE_TIMER
)paren
comma
id|MAP_COMPAT
c_func
(paren
id|SNDRV_SEQ_IOCTL_SET_QUEUE_TIMER
)paren
comma
id|MAP_COMPAT
c_func
(paren
id|SNDRV_SEQ_IOCTL_GET_QUEUE_CLIENT
)paren
comma
id|MAP_COMPAT
c_func
(paren
id|SNDRV_SEQ_IOCTL_SET_QUEUE_CLIENT
)paren
comma
id|MAP_COMPAT
c_func
(paren
id|SNDRV_SEQ_IOCTL_GET_CLIENT_POOL
)paren
comma
id|MAP_COMPAT
c_func
(paren
id|SNDRV_SEQ_IOCTL_SET_CLIENT_POOL
)paren
comma
id|MAP_COMPAT
c_func
(paren
id|SNDRV_SEQ_IOCTL_REMOVE_EVENTS
)paren
comma
id|MAP_COMPAT
c_func
(paren
id|SNDRV_SEQ_IOCTL_QUERY_SUBS
)paren
comma
id|MAP_COMPAT
c_func
(paren
id|SNDRV_SEQ_IOCTL_GET_SUBSCRIPTION
)paren
comma
id|MAP_COMPAT
c_func
(paren
id|SNDRV_SEQ_IOCTL_QUERY_NEXT_CLIENT
)paren
comma
(brace
id|SNDRV_SEQ_IOCTL_QUERY_NEXT_PORT32
comma
id|AP
c_func
(paren
id|query_next_port
)paren
)brace
comma
id|MAP_COMPAT
c_func
(paren
id|SNDRV_SEQ_IOCTL_RUNNING_MODE
)paren
comma
(brace
l_int|0
)brace
comma
)brace
suffix:semicolon
eof
