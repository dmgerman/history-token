macro_line|#ifndef __SOUND_SEQ_OSS_H
DECL|macro|__SOUND_SEQ_OSS_H
mdefine_line|#define __SOUND_SEQ_OSS_H
multiline_comment|/*&n; * OSS compatible sequencer driver&n; *&n; * Copyright (C) 1998,99 Takashi Iwai&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
macro_line|#include &quot;asequencer.h&quot;
macro_line|#include &quot;seq_kernel.h&quot;
multiline_comment|/*&n; * type definitions&n; */
DECL|typedef|snd_seq_oss_arg_t
r_typedef
r_struct
id|snd_seq_oss_arg_t
id|snd_seq_oss_arg_t
suffix:semicolon
DECL|typedef|snd_seq_oss_callback_t
r_typedef
r_struct
id|snd_seq_oss_callback_t
id|snd_seq_oss_callback_t
suffix:semicolon
multiline_comment|/*&n; * argument structure for synthesizer operations&n; */
DECL|struct|snd_seq_oss_arg_t
r_struct
id|snd_seq_oss_arg_t
(brace
multiline_comment|/* given by OSS sequencer */
DECL|member|app_index
r_int
id|app_index
suffix:semicolon
multiline_comment|/* application unique index */
DECL|member|file_mode
r_int
id|file_mode
suffix:semicolon
multiline_comment|/* file mode - see below */
DECL|member|seq_mode
r_int
id|seq_mode
suffix:semicolon
multiline_comment|/* sequencer mode - see below */
multiline_comment|/* following must be initialized in open callback */
DECL|member|addr
id|snd_seq_addr_t
id|addr
suffix:semicolon
multiline_comment|/* opened port address */
DECL|member|private_data
r_void
op_star
id|private_data
suffix:semicolon
multiline_comment|/* private data for lowlevel drivers */
multiline_comment|/* note-on event passing mode: initially given by OSS seq,&n;&t; * but configurable by drivers - see below&n;&t; */
DECL|member|event_passing
r_int
id|event_passing
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * synthesizer operation callbacks&n; */
DECL|struct|snd_seq_oss_callback_t
r_struct
id|snd_seq_oss_callback_t
(brace
DECL|member|owner
r_struct
id|module
op_star
id|owner
suffix:semicolon
DECL|member|open
r_int
(paren
op_star
id|open
)paren
(paren
id|snd_seq_oss_arg_t
op_star
id|p
comma
r_void
op_star
id|closure
)paren
suffix:semicolon
DECL|member|close
r_int
(paren
op_star
id|close
)paren
(paren
id|snd_seq_oss_arg_t
op_star
id|p
)paren
suffix:semicolon
DECL|member|ioctl
r_int
(paren
op_star
id|ioctl
)paren
(paren
id|snd_seq_oss_arg_t
op_star
id|p
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
DECL|member|load_patch
r_int
(paren
op_star
id|load_patch
)paren
(paren
id|snd_seq_oss_arg_t
op_star
id|p
comma
r_int
id|format
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|offs
comma
r_int
id|count
)paren
suffix:semicolon
DECL|member|reset
r_int
(paren
op_star
id|reset
)paren
(paren
id|snd_seq_oss_arg_t
op_star
id|p
)paren
suffix:semicolon
DECL|member|raw_event
r_int
(paren
op_star
id|raw_event
)paren
(paren
id|snd_seq_oss_arg_t
op_star
id|p
comma
r_int
r_char
op_star
id|data
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* flag: file_mode */
DECL|macro|SNDRV_SEQ_OSS_FILE_ACMODE
mdefine_line|#define SNDRV_SEQ_OSS_FILE_ACMODE&t;&t;3
DECL|macro|SNDRV_SEQ_OSS_FILE_READ
mdefine_line|#define SNDRV_SEQ_OSS_FILE_READ&t;&t;1
DECL|macro|SNDRV_SEQ_OSS_FILE_WRITE
mdefine_line|#define SNDRV_SEQ_OSS_FILE_WRITE&t;&t;2
DECL|macro|SNDRV_SEQ_OSS_FILE_NONBLOCK
mdefine_line|#define SNDRV_SEQ_OSS_FILE_NONBLOCK&t;4
multiline_comment|/* flag: seq_mode */
DECL|macro|SNDRV_SEQ_OSS_MODE_SYNTH
mdefine_line|#define SNDRV_SEQ_OSS_MODE_SYNTH&t;&t;0
DECL|macro|SNDRV_SEQ_OSS_MODE_MUSIC
mdefine_line|#define SNDRV_SEQ_OSS_MODE_MUSIC&t;&t;1
multiline_comment|/* flag: event_passing */
DECL|macro|SNDRV_SEQ_OSS_PROCESS_EVENTS
mdefine_line|#define SNDRV_SEQ_OSS_PROCESS_EVENTS&t;0&t;/* key == 255 is processed as velocity change */
DECL|macro|SNDRV_SEQ_OSS_PASS_EVENTS
mdefine_line|#define SNDRV_SEQ_OSS_PASS_EVENTS&t;&t;1&t;/* pass all events to callback */
DECL|macro|SNDRV_SEQ_OSS_PROCESS_KEYPRESS
mdefine_line|#define SNDRV_SEQ_OSS_PROCESS_KEYPRESS&t;2&t;/* key &gt;= 128 will be processed as key-pressure */
multiline_comment|/* default control rate: fixed */
DECL|macro|SNDRV_SEQ_OSS_CTRLRATE
mdefine_line|#define SNDRV_SEQ_OSS_CTRLRATE&t;&t;100
multiline_comment|/* default max queue length: configurable by module option */
DECL|macro|SNDRV_SEQ_OSS_MAX_QLEN
mdefine_line|#define SNDRV_SEQ_OSS_MAX_QLEN&t;&t;1024
multiline_comment|/*&n; * data pointer to snd_seq_register_device&n; */
DECL|struct|snd_seq_oss_reg
r_typedef
r_struct
id|snd_seq_oss_reg
(brace
DECL|member|type
r_int
id|type
suffix:semicolon
DECL|member|subtype
r_int
id|subtype
suffix:semicolon
DECL|member|nvoices
r_int
id|nvoices
suffix:semicolon
DECL|member|oper
id|snd_seq_oss_callback_t
id|oper
suffix:semicolon
DECL|member|private_data
r_void
op_star
id|private_data
suffix:semicolon
DECL|typedef|snd_seq_oss_reg_t
)brace
id|snd_seq_oss_reg_t
suffix:semicolon
multiline_comment|/* device id */
DECL|macro|SNDRV_SEQ_DEV_ID_OSS
mdefine_line|#define SNDRV_SEQ_DEV_ID_OSS&t;&t;&quot;seq-oss&quot;
macro_line|#endif /* __SOUND_SEQ_OSS_H */
eof
