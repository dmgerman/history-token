multiline_comment|/*&n; * OSS compatible sequencer driver&n; *&n; * Copyright (C) 1998,99 Takashi Iwai &lt;tiwai@suse.de&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
macro_line|#ifndef __SEQ_OSS_DEVICE_H
DECL|macro|__SEQ_OSS_DEVICE_H
mdefine_line|#define __SEQ_OSS_DEVICE_H
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &lt;sound/seq_oss.h&gt;
macro_line|#include &lt;sound/rawmidi.h&gt;
macro_line|#include &lt;sound/seq_kernel.h&gt;
macro_line|#include &lt;sound/info.h&gt;
multiline_comment|/* enable debug print */
DECL|macro|SNDRV_SEQ_OSS_DEBUG
mdefine_line|#define SNDRV_SEQ_OSS_DEBUG
multiline_comment|/* max. applications */
DECL|macro|SNDRV_SEQ_OSS_MAX_CLIENTS
mdefine_line|#define SNDRV_SEQ_OSS_MAX_CLIENTS&t;16
DECL|macro|SNDRV_SEQ_OSS_MAX_SYNTH_DEVS
mdefine_line|#define SNDRV_SEQ_OSS_MAX_SYNTH_DEVS&t;16
DECL|macro|SNDRV_SEQ_OSS_MAX_MIDI_DEVS
mdefine_line|#define SNDRV_SEQ_OSS_MAX_MIDI_DEVS&t;32
multiline_comment|/* version */
DECL|macro|SNDRV_SEQ_OSS_MAJOR_VERSION
mdefine_line|#define SNDRV_SEQ_OSS_MAJOR_VERSION&t;0
DECL|macro|SNDRV_SEQ_OSS_MINOR_VERSION
mdefine_line|#define SNDRV_SEQ_OSS_MINOR_VERSION&t;1
DECL|macro|SNDRV_SEQ_OSS_TINY_VERSION
mdefine_line|#define SNDRV_SEQ_OSS_TINY_VERSION&t;8
DECL|macro|SNDRV_SEQ_OSS_VERSION_STR
mdefine_line|#define SNDRV_SEQ_OSS_VERSION_STR&t;&quot;0.1.8&quot;
multiline_comment|/* device and proc interface name */
DECL|macro|SNDRV_SEQ_OSS_DEVNAME
mdefine_line|#define SNDRV_SEQ_OSS_DEVNAME&t;&t;&quot;seq_oss&quot;
DECL|macro|SNDRV_SEQ_OSS_PROCNAME
mdefine_line|#define SNDRV_SEQ_OSS_PROCNAME&t;&t;&quot;oss&quot;
multiline_comment|/*&n; * type definitions&n; */
DECL|typedef|seq_oss_devinfo_t
r_typedef
r_struct
id|seq_oss_devinfo_t
id|seq_oss_devinfo_t
suffix:semicolon
DECL|typedef|seq_oss_writeq_t
r_typedef
r_struct
id|seq_oss_writeq_t
id|seq_oss_writeq_t
suffix:semicolon
DECL|typedef|seq_oss_readq_t
r_typedef
r_struct
id|seq_oss_readq_t
id|seq_oss_readq_t
suffix:semicolon
DECL|typedef|seq_oss_timer_t
r_typedef
r_struct
id|seq_oss_timer_t
id|seq_oss_timer_t
suffix:semicolon
DECL|typedef|seq_oss_synthinfo_t
r_typedef
r_struct
id|seq_oss_synthinfo_t
id|seq_oss_synthinfo_t
suffix:semicolon
DECL|typedef|seq_oss_synth_sysex_t
r_typedef
r_struct
id|seq_oss_synth_sysex_t
id|seq_oss_synth_sysex_t
suffix:semicolon
DECL|typedef|seq_oss_chinfo_t
r_typedef
r_struct
id|seq_oss_chinfo_t
id|seq_oss_chinfo_t
suffix:semicolon
DECL|typedef|reltime_t
r_typedef
r_int
r_int
id|reltime_t
suffix:semicolon
DECL|typedef|abstime_t
r_typedef
r_int
r_int
id|abstime_t
suffix:semicolon
DECL|typedef|evrec_t
r_typedef
r_union
id|evrec_t
id|evrec_t
suffix:semicolon
multiline_comment|/*&n; * synthesizer channel information&n; */
DECL|struct|seq_oss_chinfo_t
r_struct
id|seq_oss_chinfo_t
(brace
DECL|member|note
DECL|member|vel
r_int
id|note
comma
id|vel
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * synthesizer information&n; */
DECL|struct|seq_oss_synthinfo_t
r_struct
id|seq_oss_synthinfo_t
(brace
DECL|member|arg
id|snd_seq_oss_arg_t
id|arg
suffix:semicolon
DECL|member|ch
id|seq_oss_chinfo_t
op_star
id|ch
suffix:semicolon
DECL|member|sysex
id|seq_oss_synth_sysex_t
op_star
id|sysex
suffix:semicolon
DECL|member|nr_voices
r_int
id|nr_voices
suffix:semicolon
DECL|member|opened
r_int
id|opened
suffix:semicolon
DECL|member|is_midi
r_int
id|is_midi
suffix:semicolon
DECL|member|midi_mapped
r_int
id|midi_mapped
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * sequencer client information&n; */
DECL|struct|seq_oss_devinfo_t
r_struct
id|seq_oss_devinfo_t
(brace
DECL|member|index
r_int
id|index
suffix:semicolon
multiline_comment|/* application index */
DECL|member|cseq
r_int
id|cseq
suffix:semicolon
multiline_comment|/* sequencer client number */
DECL|member|port
r_int
id|port
suffix:semicolon
multiline_comment|/* sequencer port number */
DECL|member|queue
r_int
id|queue
suffix:semicolon
multiline_comment|/* sequencer queue number */
DECL|member|addr
id|snd_seq_addr_t
id|addr
suffix:semicolon
multiline_comment|/* address of this device */
DECL|member|seq_mode
r_int
id|seq_mode
suffix:semicolon
multiline_comment|/* sequencer mode */
DECL|member|file_mode
r_int
id|file_mode
suffix:semicolon
multiline_comment|/* file access */
multiline_comment|/* midi device table */
DECL|member|max_mididev
r_int
id|max_mididev
suffix:semicolon
multiline_comment|/* synth device table */
DECL|member|max_synthdev
r_int
id|max_synthdev
suffix:semicolon
DECL|member|synths
id|seq_oss_synthinfo_t
id|synths
(braket
id|SNDRV_SEQ_OSS_MAX_SYNTH_DEVS
)braket
suffix:semicolon
DECL|member|synth_opened
r_int
id|synth_opened
suffix:semicolon
multiline_comment|/* output queue */
DECL|member|writeq
id|seq_oss_writeq_t
op_star
id|writeq
suffix:semicolon
multiline_comment|/* midi input queue */
DECL|member|readq
id|seq_oss_readq_t
op_star
id|readq
suffix:semicolon
multiline_comment|/* timer */
DECL|member|timer
id|seq_oss_timer_t
op_star
id|timer
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * function prototypes&n; */
multiline_comment|/* create/delete OSS sequencer client */
r_int
id|snd_seq_oss_create_client
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|snd_seq_oss_delete_client
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* device file interface */
r_int
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
suffix:semicolon
r_void
id|snd_seq_oss_release
c_func
(paren
id|seq_oss_devinfo_t
op_star
id|dp
)paren
suffix:semicolon
r_int
id|snd_seq_oss_ioctl
c_func
(paren
id|seq_oss_devinfo_t
op_star
id|dp
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
r_int
id|snd_seq_oss_read
c_func
(paren
id|seq_oss_devinfo_t
op_star
id|dev
comma
r_char
op_star
id|buf
comma
r_int
id|count
)paren
suffix:semicolon
r_int
id|snd_seq_oss_write
c_func
(paren
id|seq_oss_devinfo_t
op_star
id|dp
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|count
comma
r_struct
id|file
op_star
id|opt
)paren
suffix:semicolon
r_int
r_int
id|snd_seq_oss_poll
c_func
(paren
id|seq_oss_devinfo_t
op_star
id|dp
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
r_void
id|snd_seq_oss_reset
c_func
(paren
id|seq_oss_devinfo_t
op_star
id|dp
)paren
suffix:semicolon
r_void
id|snd_seq_oss_drain_write
c_func
(paren
id|seq_oss_devinfo_t
op_star
id|dp
)paren
suffix:semicolon
multiline_comment|/* */
r_void
id|snd_seq_oss_process_queue
c_func
(paren
id|seq_oss_devinfo_t
op_star
id|dp
comma
id|abstime_t
id|time
)paren
suffix:semicolon
multiline_comment|/* proc interface */
r_void
id|snd_seq_oss_system_info_read
c_func
(paren
id|snd_info_buffer_t
op_star
id|buf
)paren
suffix:semicolon
r_void
id|snd_seq_oss_midi_info_read
c_func
(paren
id|snd_info_buffer_t
op_star
id|buf
)paren
suffix:semicolon
r_void
id|snd_seq_oss_synth_info_read
c_func
(paren
id|snd_info_buffer_t
op_star
id|buf
)paren
suffix:semicolon
r_void
id|snd_seq_oss_readq_info_read
c_func
(paren
id|seq_oss_readq_t
op_star
id|q
comma
id|snd_info_buffer_t
op_star
id|buf
)paren
suffix:semicolon
multiline_comment|/* file mode macros */
DECL|macro|is_read_mode
mdefine_line|#define is_read_mode(mode)&t;((mode) &amp; SNDRV_SEQ_OSS_FILE_READ)
DECL|macro|is_write_mode
mdefine_line|#define is_write_mode(mode)&t;((mode) &amp; SNDRV_SEQ_OSS_FILE_WRITE)
DECL|macro|is_nonblock_mode
mdefine_line|#define is_nonblock_mode(mode)&t;((mode) &amp; SNDRV_SEQ_OSS_FILE_NONBLOCK)
multiline_comment|/* dispatch event */
r_inline
r_static
r_int
DECL|function|snd_seq_oss_dispatch
id|snd_seq_oss_dispatch
c_func
(paren
id|seq_oss_devinfo_t
op_star
id|dp
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
(brace
r_return
id|snd_seq_kernel_client_dispatch
c_func
(paren
id|dp-&gt;cseq
comma
id|ev
comma
id|atomic
comma
id|hop
)paren
suffix:semicolon
)brace
multiline_comment|/* ioctl */
r_inline
r_static
r_int
DECL|function|snd_seq_oss_control
id|snd_seq_oss_control
c_func
(paren
id|seq_oss_devinfo_t
op_star
id|dp
comma
r_int
r_int
id|type
comma
r_void
op_star
id|arg
)paren
(brace
r_return
id|snd_seq_kernel_client_ctl
c_func
(paren
id|dp-&gt;cseq
comma
id|type
comma
id|arg
)paren
suffix:semicolon
)brace
multiline_comment|/* fill the addresses in header */
r_inline
r_static
r_void
DECL|function|snd_seq_oss_fill_addr
id|snd_seq_oss_fill_addr
c_func
(paren
id|seq_oss_devinfo_t
op_star
id|dp
comma
id|snd_seq_event_t
op_star
id|ev
comma
r_int
id|dest_client
comma
r_int
id|dest_port
)paren
(brace
id|ev-&gt;queue
op_assign
id|dp-&gt;queue
suffix:semicolon
id|ev-&gt;source
op_assign
id|dp-&gt;addr
suffix:semicolon
id|ev-&gt;dest.client
op_assign
id|dest_client
suffix:semicolon
id|ev-&gt;dest.port
op_assign
id|dest_port
suffix:semicolon
)brace
multiline_comment|/* misc. functions for proc interface */
r_char
op_star
id|enabled_str
c_func
(paren
r_int
r_bool
)paren
suffix:semicolon
r_char
op_star
id|filemode_str
c_func
(paren
r_int
id|fmode
)paren
suffix:semicolon
multiline_comment|/* for debug */
macro_line|#ifdef SNDRV_SEQ_OSS_DEBUG
r_extern
r_int
id|seq_oss_debug
suffix:semicolon
DECL|macro|debug_printk
mdefine_line|#define debug_printk(x)&t;do { if (seq_oss_debug &gt; 0) snd_printk x; } while (0)
macro_line|#else
DECL|macro|debug_printk
mdefine_line|#define debug_printk(x)&t;/**/
macro_line|#endif
macro_line|#endif /* __SEQ_OSS_DEVICE_H */
eof
