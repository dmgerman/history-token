multiline_comment|/*&n; * Driver for Digigram miXart soundcards&n; *&n; * main header file&n; *&n; * Copyright (c) 2003 by Digigram &lt;alsa@digigram.com&gt;&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
macro_line|#ifndef __SOUND_MIXART_H
DECL|macro|__SOUND_MIXART_H
mdefine_line|#define __SOUND_MIXART_H
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;sound/pcm.h&gt;
DECL|macro|MIXART_DRIVER_VERSION
mdefine_line|#define MIXART_DRIVER_VERSION&t;0x000100&t;/* 0.1.0 */
multiline_comment|/*&n; */
DECL|macro|mixart_t_magic
mdefine_line|#define mixart_t_magic&t;&t;0xa17a3e01
DECL|macro|mixart_mgr_t_magic
mdefine_line|#define mixart_mgr_t_magic&t;0xa17a3e02
DECL|typedef|mixart_t
r_typedef
r_struct
id|snd_mixart
id|mixart_t
suffix:semicolon
DECL|typedef|mixart_mgr_t
r_typedef
r_struct
id|snd_mixart_mgr
id|mixart_mgr_t
suffix:semicolon
DECL|typedef|mixart_stream_t
r_typedef
r_struct
id|snd_mixart_stream
id|mixart_stream_t
suffix:semicolon
DECL|typedef|mixart_pipe_t
r_typedef
r_struct
id|snd_mixart_pipe
id|mixart_pipe_t
suffix:semicolon
DECL|typedef|mixart_bufferinfo_t
r_typedef
r_struct
id|mixart_bufferinfo
id|mixart_bufferinfo_t
suffix:semicolon
DECL|typedef|mixart_flowinfo_t
r_typedef
r_struct
id|mixart_flowinfo
id|mixart_flowinfo_t
suffix:semicolon
DECL|typedef|mixart_uid_t
r_typedef
r_struct
id|mixart_uid
id|mixart_uid_t
suffix:semicolon
DECL|struct|mixart_uid
r_struct
id|mixart_uid
(brace
DECL|member|object_id
id|u32
id|object_id
suffix:semicolon
DECL|member|desc
id|u32
id|desc
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|mem_area
r_struct
id|mem_area
(brace
DECL|member|phys
r_int
r_int
id|phys
suffix:semicolon
DECL|member|virt
r_void
id|__iomem
op_star
id|virt
suffix:semicolon
DECL|member|res
r_struct
id|resource
op_star
id|res
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|mixart_route_t
r_typedef
r_struct
id|mixart_route
id|mixart_route_t
suffix:semicolon
DECL|struct|mixart_route
r_struct
id|mixart_route
(brace
DECL|member|connected
r_int
r_char
id|connected
suffix:semicolon
DECL|member|phase_inv
r_int
r_char
id|phase_inv
suffix:semicolon
DECL|member|volume
r_int
id|volume
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* firmware status codes  */
DECL|macro|MIXART_MOTHERBOARD_XLX_INDEX
mdefine_line|#define MIXART_MOTHERBOARD_XLX_INDEX  0
DECL|macro|MIXART_MOTHERBOARD_ELF_INDEX
mdefine_line|#define MIXART_MOTHERBOARD_ELF_INDEX  1
DECL|macro|MIXART_AESEBUBOARD_XLX_INDEX
mdefine_line|#define MIXART_AESEBUBOARD_XLX_INDEX  2
DECL|macro|MIXART_HARDW_FILES_MAX_INDEX
mdefine_line|#define MIXART_HARDW_FILES_MAX_INDEX  3  /* xilinx, elf, AESEBU xilinx */
DECL|macro|MIXART_MAX_CARDS
mdefine_line|#define MIXART_MAX_CARDS&t;4
DECL|macro|MSG_FIFO_SIZE
mdefine_line|#define MSG_FIFO_SIZE           16
DECL|macro|MIXART_MAX_PHYS_CONNECTORS
mdefine_line|#define MIXART_MAX_PHYS_CONNECTORS  (MIXART_MAX_CARDS * 2 * 2) /* 4 * stereo * (analog+digital) */
DECL|struct|snd_mixart_mgr
r_struct
id|snd_mixart_mgr
(brace
DECL|member|num_cards
r_int
r_int
id|num_cards
suffix:semicolon
DECL|member|chip
id|mixart_t
op_star
id|chip
(braket
id|MIXART_MAX_CARDS
)braket
suffix:semicolon
DECL|member|pci
r_struct
id|pci_dev
op_star
id|pci
suffix:semicolon
DECL|member|irq
r_int
id|irq
suffix:semicolon
multiline_comment|/* memory-maps */
DECL|member|mem
r_struct
id|mem_area
id|mem
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* share the name */
DECL|member|shortname
r_char
id|shortname
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* short name of this soundcard */
DECL|member|longname
r_char
id|longname
(braket
l_int|80
)braket
suffix:semicolon
multiline_comment|/* name of this soundcard */
multiline_comment|/* message tasklet */
DECL|member|msg_taskq
r_struct
id|tasklet_struct
id|msg_taskq
suffix:semicolon
multiline_comment|/* one and only blocking message or notification may be pending  */
DECL|member|pending_event
id|u32
id|pending_event
suffix:semicolon
DECL|member|msg_sleep
id|wait_queue_head_t
id|msg_sleep
suffix:semicolon
multiline_comment|/* messages stored for tasklet */
DECL|member|msg_fifo
id|u32
id|msg_fifo
(braket
id|MSG_FIFO_SIZE
)braket
suffix:semicolon
DECL|member|msg_fifo_readptr
r_int
id|msg_fifo_readptr
suffix:semicolon
DECL|member|msg_fifo_writeptr
r_int
id|msg_fifo_writeptr
suffix:semicolon
DECL|member|msg_processed
id|atomic_t
id|msg_processed
suffix:semicolon
multiline_comment|/* number of messages to be processed in takslet */
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
multiline_comment|/* interrupt spinlock */
DECL|member|msg_lock
id|spinlock_t
id|msg_lock
suffix:semicolon
multiline_comment|/* mailbox spinlock */
DECL|member|msg_mutex
r_struct
id|semaphore
id|msg_mutex
suffix:semicolon
multiline_comment|/* mutex for blocking_requests */
DECL|member|setup_mutex
r_struct
id|semaphore
id|setup_mutex
suffix:semicolon
multiline_comment|/* mutex used in hw_params, open and close */
multiline_comment|/* hardware interface */
DECL|member|hwdep
id|snd_hwdep_t
op_star
id|hwdep
suffix:semicolon
DECL|member|board_type
r_int
r_int
id|board_type
suffix:semicolon
multiline_comment|/* read from embedded once elf file is loaded, 250 = miXart8, 251 = with AES, 252 = with Cobranet */
DECL|member|flowinfo
r_struct
id|snd_dma_buffer
id|flowinfo
suffix:semicolon
DECL|member|bufferinfo
r_struct
id|snd_dma_buffer
id|bufferinfo
suffix:semicolon
DECL|member|uid_console_manager
id|mixart_uid_t
id|uid_console_manager
suffix:semicolon
DECL|member|sample_rate
r_int
id|sample_rate
suffix:semicolon
DECL|member|ref_count_rate
r_int
id|ref_count_rate
suffix:semicolon
DECL|member|mixer_mutex
r_struct
id|semaphore
id|mixer_mutex
suffix:semicolon
multiline_comment|/* mutex for mixer */
)brace
suffix:semicolon
DECL|macro|MIXART_STREAM_STATUS_FREE
mdefine_line|#define MIXART_STREAM_STATUS_FREE&t;0
DECL|macro|MIXART_STREAM_STATUS_OPEN
mdefine_line|#define MIXART_STREAM_STATUS_OPEN&t;1
DECL|macro|MIXART_STREAM_STATUS_RUNNING
mdefine_line|#define MIXART_STREAM_STATUS_RUNNING&t;2
DECL|macro|MIXART_STREAM_STATUS_DRAINING
mdefine_line|#define MIXART_STREAM_STATUS_DRAINING&t;3
DECL|macro|MIXART_STREAM_STATUS_PAUSE
mdefine_line|#define MIXART_STREAM_STATUS_PAUSE&t;4
DECL|macro|MIXART_PLAYBACK_STREAMS
mdefine_line|#define MIXART_PLAYBACK_STREAMS&t;&t;4
DECL|macro|MIXART_CAPTURE_STREAMS
mdefine_line|#define MIXART_CAPTURE_STREAMS&t;&t;1
DECL|macro|MIXART_PCM_ANALOG
mdefine_line|#define MIXART_PCM_ANALOG&t;&t;0
DECL|macro|MIXART_PCM_DIGITAL
mdefine_line|#define MIXART_PCM_DIGITAL&t;&t;1
DECL|macro|MIXART_PCM_TOTAL
mdefine_line|#define MIXART_PCM_TOTAL&t;&t;2
DECL|macro|MIXART_MAX_STREAM_PER_CARD
mdefine_line|#define MIXART_MAX_STREAM_PER_CARD  (MIXART_PCM_TOTAL * (MIXART_PLAYBACK_STREAMS + MIXART_CAPTURE_STREAMS) )
DECL|macro|MIXART_NOTIFY_CARD_MASK
mdefine_line|#define MIXART_NOTIFY_CARD_MASK&t;&t;0xF000
DECL|macro|MIXART_NOTIFY_CARD_OFFSET
mdefine_line|#define MIXART_NOTIFY_CARD_OFFSET&t;12
DECL|macro|MIXART_NOTIFY_PCM_MASK
mdefine_line|#define MIXART_NOTIFY_PCM_MASK&t;&t;0x0F00
DECL|macro|MIXART_NOTIFY_PCM_OFFSET
mdefine_line|#define MIXART_NOTIFY_PCM_OFFSET&t;8
DECL|macro|MIXART_NOTIFY_CAPT_MASK
mdefine_line|#define MIXART_NOTIFY_CAPT_MASK&t;&t;0x0080
DECL|macro|MIXART_NOTIFY_SUBS_MASK
mdefine_line|#define MIXART_NOTIFY_SUBS_MASK&t;&t;0x007F
DECL|struct|snd_mixart_stream
r_struct
id|snd_mixart_stream
(brace
DECL|member|substream
id|snd_pcm_substream_t
op_star
id|substream
suffix:semicolon
DECL|member|pipe
id|mixart_pipe_t
op_star
id|pipe
suffix:semicolon
DECL|member|pcm_number
r_int
id|pcm_number
suffix:semicolon
DECL|member|status
r_int
id|status
suffix:semicolon
multiline_comment|/* nothing, running, draining */
DECL|member|abs_period_elapsed
id|u64
id|abs_period_elapsed
suffix:semicolon
multiline_comment|/* last absolute stream position where period_elapsed was called (multiple of runtime-&gt;period_size) */
DECL|member|buf_periods
id|u32
id|buf_periods
suffix:semicolon
multiline_comment|/* periods counter in the buffer (&lt; runtime-&gt;periods) */
DECL|member|buf_period_frag
id|u32
id|buf_period_frag
suffix:semicolon
multiline_comment|/* defines with buf_period_pos the exact position in the buffer (&lt; runtime-&gt;period_size) */
DECL|member|channels
r_int
id|channels
suffix:semicolon
)brace
suffix:semicolon
DECL|enum|mixart_pipe_status
r_enum
id|mixart_pipe_status
(brace
DECL|enumerator|PIPE_UNDEFINED
id|PIPE_UNDEFINED
comma
DECL|enumerator|PIPE_STOPPED
id|PIPE_STOPPED
comma
DECL|enumerator|PIPE_RUNNING
id|PIPE_RUNNING
comma
DECL|enumerator|PIPE_CLOCK_SET
id|PIPE_CLOCK_SET
)brace
suffix:semicolon
DECL|struct|snd_mixart_pipe
r_struct
id|snd_mixart_pipe
(brace
DECL|member|group_uid
id|mixart_uid_t
id|group_uid
suffix:semicolon
multiline_comment|/* id of the pipe, as returned by embedded */
DECL|member|stream_count
r_int
id|stream_count
suffix:semicolon
DECL|member|uid_left_connector
id|mixart_uid_t
id|uid_left_connector
suffix:semicolon
multiline_comment|/* UID&squot;s for the audio connectors */
DECL|member|uid_right_connector
id|mixart_uid_t
id|uid_right_connector
suffix:semicolon
DECL|member|status
r_enum
id|mixart_pipe_status
id|status
suffix:semicolon
DECL|member|references
r_int
id|references
suffix:semicolon
multiline_comment|/* number of subs openned */
DECL|member|monitoring
r_int
id|monitoring
suffix:semicolon
multiline_comment|/* pipe used for monitoring issue */
)brace
suffix:semicolon
DECL|struct|snd_mixart
r_struct
id|snd_mixart
(brace
DECL|member|card
id|snd_card_t
op_star
id|card
suffix:semicolon
DECL|member|mgr
id|mixart_mgr_t
op_star
id|mgr
suffix:semicolon
DECL|member|chip_idx
r_int
id|chip_idx
suffix:semicolon
multiline_comment|/* zero based */
DECL|member|hwdep
id|snd_hwdep_t
op_star
id|hwdep
suffix:semicolon
multiline_comment|/* DSP loader, only for the first card */
DECL|member|pcm
id|snd_pcm_t
op_star
id|pcm
suffix:semicolon
multiline_comment|/* PCM analog i/o */
DECL|member|pcm_dig
id|snd_pcm_t
op_star
id|pcm_dig
suffix:semicolon
multiline_comment|/* PCM digital i/o */
multiline_comment|/* allocate stereo pipe for instance */
DECL|member|pipe_in_ana
id|mixart_pipe_t
id|pipe_in_ana
suffix:semicolon
DECL|member|pipe_out_ana
id|mixart_pipe_t
id|pipe_out_ana
suffix:semicolon
multiline_comment|/* if AES/EBU daughter board is available, additional pipes possible on pcm_dig */
DECL|member|pipe_in_dig
id|mixart_pipe_t
id|pipe_in_dig
suffix:semicolon
DECL|member|pipe_out_dig
id|mixart_pipe_t
id|pipe_out_dig
suffix:semicolon
DECL|member|playback_stream
id|mixart_stream_t
id|playback_stream
(braket
id|MIXART_PCM_TOTAL
)braket
(braket
id|MIXART_PLAYBACK_STREAMS
)braket
suffix:semicolon
multiline_comment|/* 0 = pcm, 1 = pcm_dig */
DECL|member|capture_stream
id|mixart_stream_t
id|capture_stream
(braket
id|MIXART_PCM_TOTAL
)braket
suffix:semicolon
multiline_comment|/* 0 = pcm, 1 = pcm_dig */
multiline_comment|/* UID&squot;s for the physical io&squot;s */
DECL|member|uid_out_analog_physio
id|mixart_uid_t
id|uid_out_analog_physio
suffix:semicolon
DECL|member|uid_in_analog_physio
id|mixart_uid_t
id|uid_in_analog_physio
suffix:semicolon
DECL|member|analog_playback_active
r_int
id|analog_playback_active
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Mixer : Master Playback active (!mute) */
DECL|member|analog_playback_volume
r_int
id|analog_playback_volume
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Mixer : Master Playback Volume */
DECL|member|analog_capture_volume
r_int
id|analog_capture_volume
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Mixer : Master Capture Volume */
DECL|member|digital_playback_active
r_int
id|digital_playback_active
(braket
l_int|2
op_star
id|MIXART_PLAYBACK_STREAMS
)braket
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Mixer : Digital Playback Active [(analog+AES output)*streams][stereo]*/
DECL|member|digital_playback_volume
r_int
id|digital_playback_volume
(braket
l_int|2
op_star
id|MIXART_PLAYBACK_STREAMS
)braket
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Mixer : Digital Playback Volume [(analog+AES output)*streams][stereo]*/
DECL|member|digital_capture_volume
r_int
id|digital_capture_volume
(braket
l_int|2
)braket
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Mixer : Digital Capture Volume [analog+AES output][stereo] */
DECL|member|monitoring_active
r_int
id|monitoring_active
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Mixer : Monitoring Active */
DECL|member|monitoring_volume
r_int
id|monitoring_volume
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Mixer : Monitoring Volume */
)brace
suffix:semicolon
DECL|struct|mixart_bufferinfo
r_struct
id|mixart_bufferinfo
(brace
DECL|member|buffer_address
id|u32
id|buffer_address
suffix:semicolon
DECL|member|reserved
id|u32
id|reserved
(braket
l_int|5
)braket
suffix:semicolon
DECL|member|available_length
id|u32
id|available_length
suffix:semicolon
DECL|member|buffer_id
id|u32
id|buffer_id
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|mixart_flowinfo
r_struct
id|mixart_flowinfo
(brace
DECL|member|bufferinfo_array_phy_address
id|u32
id|bufferinfo_array_phy_address
suffix:semicolon
DECL|member|reserved
id|u32
id|reserved
(braket
l_int|11
)braket
suffix:semicolon
DECL|member|bufferinfo_count
id|u32
id|bufferinfo_count
suffix:semicolon
DECL|member|capture
id|u32
id|capture
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* exported */
r_int
id|snd_mixart_create_pcm
c_func
(paren
id|mixart_t
op_star
id|chip
)paren
suffix:semicolon
id|mixart_pipe_t
op_star
id|snd_mixart_add_ref_pipe
c_func
(paren
id|mixart_t
op_star
id|chip
comma
r_int
id|pcm_number
comma
r_int
id|capture
comma
r_int
id|monitoring
)paren
suffix:semicolon
r_int
id|snd_mixart_kill_ref_pipe
c_func
(paren
id|mixart_mgr_t
op_star
id|mgr
comma
id|mixart_pipe_t
op_star
id|pipe
comma
r_int
id|monitoring
)paren
suffix:semicolon
macro_line|#endif /* __SOUND_MIXART_H */
eof
