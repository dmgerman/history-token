macro_line|#ifndef __SOUND_RAWMIDI_H
DECL|macro|__SOUND_RAWMIDI_H
mdefine_line|#define __SOUND_RAWMIDI_H
multiline_comment|/*&n; *  Abstract layer for MIDI v1.0 stream&n; *  Copyright (c) by Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#include &lt;sound/asound.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
macro_line|#if defined(CONFIG_SND_SEQUENCER) || defined(CONFIG_SND_SEQUENCER_MODULE)
macro_line|#include &quot;seq_device.h&quot;
macro_line|#endif
multiline_comment|/*&n; *  Raw MIDI interface&n; */
DECL|typedef|snd_rawmidi_stream_t
r_typedef
r_enum
id|sndrv_rawmidi_stream
id|snd_rawmidi_stream_t
suffix:semicolon
DECL|typedef|snd_rawmidi_info_t
r_typedef
r_struct
id|sndrv_rawmidi_info
id|snd_rawmidi_info_t
suffix:semicolon
DECL|typedef|snd_rawmidi_params_t
r_typedef
r_struct
id|sndrv_rawmidi_params
id|snd_rawmidi_params_t
suffix:semicolon
DECL|typedef|snd_rawmidi_status_t
r_typedef
r_struct
id|sndrv_rawmidi_status
id|snd_rawmidi_status_t
suffix:semicolon
DECL|macro|SNDRV_RAWMIDI_DEVICES
mdefine_line|#define SNDRV_RAWMIDI_DEVICES&t;&t;8
DECL|macro|SNDRV_RAWMIDI_LFLG_OUTPUT
mdefine_line|#define SNDRV_RAWMIDI_LFLG_OUTPUT&t;(1&lt;&lt;0)
DECL|macro|SNDRV_RAWMIDI_LFLG_INPUT
mdefine_line|#define SNDRV_RAWMIDI_LFLG_INPUT&t;(1&lt;&lt;1)
DECL|macro|SNDRV_RAWMIDI_LFLG_OPEN
mdefine_line|#define SNDRV_RAWMIDI_LFLG_OPEN&t;&t;(3&lt;&lt;0)
DECL|macro|SNDRV_RAWMIDI_LFLG_APPEND
mdefine_line|#define SNDRV_RAWMIDI_LFLG_APPEND&t;(1&lt;&lt;2)
DECL|typedef|snd_rawmidi_runtime_t
r_typedef
r_struct
id|_snd_rawmidi_runtime
id|snd_rawmidi_runtime_t
suffix:semicolon
DECL|typedef|snd_rawmidi_substream_t
r_typedef
r_struct
id|_snd_rawmidi_substream
id|snd_rawmidi_substream_t
suffix:semicolon
DECL|typedef|snd_rawmidi_str_t
r_typedef
r_struct
id|_snd_rawmidi_str
id|snd_rawmidi_str_t
suffix:semicolon
DECL|struct|_snd_rawmidi_ops
r_typedef
r_struct
id|_snd_rawmidi_ops
(brace
DECL|member|open
r_int
(paren
op_star
id|open
)paren
(paren
id|snd_rawmidi_substream_t
op_star
id|substream
)paren
suffix:semicolon
DECL|member|close
r_int
(paren
op_star
id|close
)paren
(paren
id|snd_rawmidi_substream_t
op_star
id|substream
)paren
suffix:semicolon
DECL|member|trigger
r_void
(paren
op_star
id|trigger
)paren
(paren
id|snd_rawmidi_substream_t
op_star
id|substream
comma
r_int
id|up
)paren
suffix:semicolon
DECL|member|drain
r_void
(paren
op_star
id|drain
)paren
(paren
id|snd_rawmidi_substream_t
op_star
id|substream
)paren
suffix:semicolon
DECL|typedef|snd_rawmidi_ops_t
)brace
id|snd_rawmidi_ops_t
suffix:semicolon
DECL|struct|_snd_rawmidi_global_ops
r_typedef
r_struct
id|_snd_rawmidi_global_ops
(brace
DECL|member|dev_register
r_int
(paren
op_star
id|dev_register
)paren
(paren
id|snd_rawmidi_t
op_star
id|rmidi
)paren
suffix:semicolon
DECL|member|dev_unregister
r_int
(paren
op_star
id|dev_unregister
)paren
(paren
id|snd_rawmidi_t
op_star
id|rmidi
)paren
suffix:semicolon
DECL|typedef|snd_rawmidi_global_ops_t
)brace
id|snd_rawmidi_global_ops_t
suffix:semicolon
DECL|struct|_snd_rawmidi_runtime
r_struct
id|_snd_rawmidi_runtime
(brace
DECL|member|trigger
r_int
r_int
id|trigger
suffix:colon
l_int|1
comma
multiline_comment|/* transfer is running */
DECL|member|drain
id|drain
suffix:colon
l_int|1
comma
multiline_comment|/* drain stage */
DECL|member|oss
id|oss
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* OSS compatible mode */
multiline_comment|/* midi stream buffer */
DECL|member|buffer
r_int
r_char
op_star
id|buffer
suffix:semicolon
multiline_comment|/* buffer for MIDI data */
DECL|member|buffer_size
r_int
id|buffer_size
suffix:semicolon
multiline_comment|/* size of buffer */
DECL|member|appl_ptr
r_int
id|appl_ptr
suffix:semicolon
multiline_comment|/* application pointer */
DECL|member|hw_ptr
r_int
id|hw_ptr
suffix:semicolon
multiline_comment|/* hardware pointer */
DECL|member|avail_min
r_int
id|avail_min
suffix:semicolon
multiline_comment|/* min avail for wakeup */
DECL|member|avail
r_int
id|avail
suffix:semicolon
multiline_comment|/* max used buffer for wakeup */
DECL|member|xruns
r_int
id|xruns
suffix:semicolon
multiline_comment|/* over/underruns counter */
multiline_comment|/* misc */
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|sleep
id|wait_queue_head_t
id|sleep
suffix:semicolon
multiline_comment|/* event handler (room [output] or new bytes [input]) */
DECL|member|event
r_void
(paren
op_star
id|event
)paren
(paren
id|snd_rawmidi_substream_t
op_star
id|substream
)paren
suffix:semicolon
multiline_comment|/* private data */
DECL|member|private_data
r_void
op_star
id|private_data
suffix:semicolon
DECL|member|private_free
r_void
(paren
op_star
id|private_free
)paren
(paren
id|snd_rawmidi_substream_t
op_star
id|substream
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|_snd_rawmidi_substream
r_struct
id|_snd_rawmidi_substream
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
multiline_comment|/* list of all substream for given stream */
DECL|member|stream
r_int
id|stream
suffix:semicolon
multiline_comment|/* direction */
DECL|member|number
r_int
id|number
suffix:semicolon
multiline_comment|/* substream number */
DECL|member|opened
r_int
r_int
id|opened
suffix:colon
l_int|1
comma
multiline_comment|/* open flag */
DECL|member|append
id|append
suffix:colon
l_int|1
comma
multiline_comment|/* append flag (merge more streams) */
DECL|member|active_sensing
id|active_sensing
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* send active sensing when close */
DECL|member|use_count
r_int
id|use_count
suffix:semicolon
multiline_comment|/* use counter (for output) */
DECL|member|bytes
r_int
id|bytes
suffix:semicolon
DECL|member|rmidi
id|snd_rawmidi_t
op_star
id|rmidi
suffix:semicolon
DECL|member|pstr
id|snd_rawmidi_str_t
op_star
id|pstr
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|runtime
id|snd_rawmidi_runtime_t
op_star
id|runtime
suffix:semicolon
multiline_comment|/* hardware layer */
DECL|member|ops
id|snd_rawmidi_ops_t
op_star
id|ops
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|_snd_rawmidi_file
r_typedef
r_struct
id|_snd_rawmidi_file
(brace
DECL|member|rmidi
id|snd_rawmidi_t
op_star
id|rmidi
suffix:semicolon
DECL|member|input
id|snd_rawmidi_substream_t
op_star
id|input
suffix:semicolon
DECL|member|output
id|snd_rawmidi_substream_t
op_star
id|output
suffix:semicolon
DECL|typedef|snd_rawmidi_file_t
)brace
id|snd_rawmidi_file_t
suffix:semicolon
DECL|struct|_snd_rawmidi_str
r_struct
id|_snd_rawmidi_str
(brace
DECL|member|substream_count
r_int
r_int
id|substream_count
suffix:semicolon
DECL|member|substream_opened
r_int
r_int
id|substream_opened
suffix:semicolon
DECL|member|substreams
r_struct
id|list_head
id|substreams
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|_snd_rawmidi
r_struct
id|_snd_rawmidi
(brace
DECL|member|card
id|snd_card_t
op_star
id|card
suffix:semicolon
DECL|member|device
r_int
r_int
id|device
suffix:semicolon
multiline_comment|/* device number */
DECL|member|info_flags
r_int
r_int
id|info_flags
suffix:semicolon
multiline_comment|/* SNDRV_RAWMIDI_INFO_XXXX */
DECL|member|id
r_char
id|id
(braket
l_int|64
)braket
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
l_int|80
)braket
suffix:semicolon
macro_line|#ifdef CONFIG_SND_OSSEMUL
DECL|member|ossreg
r_int
id|ossreg
suffix:semicolon
macro_line|#endif
DECL|member|ops
id|snd_rawmidi_global_ops_t
op_star
id|ops
suffix:semicolon
DECL|member|streams
id|snd_rawmidi_str_t
id|streams
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|private_data
r_void
op_star
id|private_data
suffix:semicolon
DECL|member|private_free
r_void
(paren
op_star
id|private_free
)paren
(paren
id|snd_rawmidi_t
op_star
id|rmidi
)paren
suffix:semicolon
DECL|member|open_mutex
r_struct
id|semaphore
id|open_mutex
suffix:semicolon
DECL|member|open_wait
id|wait_queue_head_t
id|open_wait
suffix:semicolon
DECL|member|dev
id|snd_info_entry_t
op_star
id|dev
suffix:semicolon
DECL|member|proc_entry
id|snd_info_entry_t
op_star
id|proc_entry
suffix:semicolon
macro_line|#if defined(CONFIG_SND_SEQUENCER) || defined(CONFIG_SND_SEQUENCER_MODULE)
DECL|member|seq_dev
id|snd_seq_device_t
op_star
id|seq_dev
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
multiline_comment|/* main rawmidi functions */
r_int
id|snd_rawmidi_new
c_func
(paren
id|snd_card_t
op_star
id|card
comma
r_char
op_star
id|id
comma
r_int
id|device
comma
r_int
id|output_count
comma
r_int
id|input_count
comma
id|snd_rawmidi_t
op_star
op_star
id|rmidi
)paren
suffix:semicolon
r_void
id|snd_rawmidi_set_ops
c_func
(paren
id|snd_rawmidi_t
op_star
id|rmidi
comma
r_int
id|stream
comma
id|snd_rawmidi_ops_t
op_star
id|ops
)paren
suffix:semicolon
multiline_comment|/* control functions */
r_int
id|snd_rawmidi_control_ioctl
c_func
(paren
id|snd_card_t
op_star
id|card
comma
id|snd_ctl_file_t
op_star
id|control
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
multiline_comment|/* callbacks */
r_void
id|snd_rawmidi_receive_reset
c_func
(paren
id|snd_rawmidi_substream_t
op_star
id|substream
)paren
suffix:semicolon
r_int
id|snd_rawmidi_receive
c_func
(paren
id|snd_rawmidi_substream_t
op_star
id|substream
comma
r_const
r_int
r_char
op_star
id|buffer
comma
r_int
id|count
)paren
suffix:semicolon
r_void
id|snd_rawmidi_transmit_reset
c_func
(paren
id|snd_rawmidi_substream_t
op_star
id|substream
)paren
suffix:semicolon
r_int
id|snd_rawmidi_transmit_empty
c_func
(paren
id|snd_rawmidi_substream_t
op_star
id|substream
)paren
suffix:semicolon
r_int
id|snd_rawmidi_transmit_peek
c_func
(paren
id|snd_rawmidi_substream_t
op_star
id|substream
comma
r_int
r_char
op_star
id|buffer
comma
r_int
id|count
)paren
suffix:semicolon
r_int
id|snd_rawmidi_transmit_ack
c_func
(paren
id|snd_rawmidi_substream_t
op_star
id|substream
comma
r_int
id|count
)paren
suffix:semicolon
r_int
id|snd_rawmidi_transmit
c_func
(paren
id|snd_rawmidi_substream_t
op_star
id|substream
comma
r_int
r_char
op_star
id|buffer
comma
r_int
id|count
)paren
suffix:semicolon
multiline_comment|/* main midi functions */
r_int
id|snd_rawmidi_info_select
c_func
(paren
id|snd_card_t
op_star
id|card
comma
id|snd_rawmidi_info_t
op_star
id|info
)paren
suffix:semicolon
r_int
id|snd_rawmidi_kernel_open
c_func
(paren
r_int
id|cardnum
comma
r_int
id|device
comma
r_int
id|subdevice
comma
r_int
id|mode
comma
id|snd_rawmidi_file_t
op_star
id|rfile
)paren
suffix:semicolon
r_int
id|snd_rawmidi_kernel_release
c_func
(paren
id|snd_rawmidi_file_t
op_star
id|rfile
)paren
suffix:semicolon
r_int
id|snd_rawmidi_output_params
c_func
(paren
id|snd_rawmidi_substream_t
op_star
id|substream
comma
id|snd_rawmidi_params_t
op_star
id|params
)paren
suffix:semicolon
r_int
id|snd_rawmidi_input_params
c_func
(paren
id|snd_rawmidi_substream_t
op_star
id|substream
comma
id|snd_rawmidi_params_t
op_star
id|params
)paren
suffix:semicolon
r_int
id|snd_rawmidi_drop_output
c_func
(paren
id|snd_rawmidi_substream_t
op_star
id|substream
)paren
suffix:semicolon
r_int
id|snd_rawmidi_drain_output
c_func
(paren
id|snd_rawmidi_substream_t
op_star
id|substream
)paren
suffix:semicolon
r_int
id|snd_rawmidi_drain_input
c_func
(paren
id|snd_rawmidi_substream_t
op_star
id|substream
)paren
suffix:semicolon
r_int
id|snd_rawmidi_kernel_read
c_func
(paren
id|snd_rawmidi_substream_t
op_star
id|substream
comma
r_int
r_char
op_star
id|buf
comma
r_int
id|count
)paren
suffix:semicolon
r_int
id|snd_rawmidi_kernel_write
c_func
(paren
id|snd_rawmidi_substream_t
op_star
id|substream
comma
r_const
r_int
r_char
op_star
id|buf
comma
r_int
id|count
)paren
suffix:semicolon
macro_line|#endif /* __SOUND_RAWMIDI_H */
eof
