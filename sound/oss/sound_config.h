multiline_comment|/* sound_config.h&n; *&n; * A driver for sound cards, misc. configuration parameters.&n; */
multiline_comment|/*&n; * Copyright (C) by Hannu Savolainen 1993-1997&n; *&n; * OSS/Free for Linux is distributed under the GNU GENERAL PUBLIC LICENSE (GPL)&n; * Version 2 (June 1991). See the &quot;COPYING&quot; file distributed with this software&n; * for more info.&n; */
macro_line|#ifndef  _SOUND_CONFIG_H_
DECL|macro|_SOUND_CONFIG_H_
mdefine_line|#define  _SOUND_CONFIG_H_
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/sound.h&gt;
macro_line|#include &quot;os.h&quot;
macro_line|#include &quot;soundvers.h&quot;
macro_line|#ifndef SND_DEFAULT_ENABLE
DECL|macro|SND_DEFAULT_ENABLE
mdefine_line|#define SND_DEFAULT_ENABLE&t;1
macro_line|#endif
macro_line|#ifndef MAX_REALTIME_FACTOR
DECL|macro|MAX_REALTIME_FACTOR
mdefine_line|#define MAX_REALTIME_FACTOR&t;4
macro_line|#endif
multiline_comment|/*&n; * Use always 64k buffer size. There is no reason to use shorter.&n; */
DECL|macro|DSP_BUFFSIZE
macro_line|#undef DSP_BUFFSIZE
DECL|macro|DSP_BUFFSIZE
mdefine_line|#define DSP_BUFFSIZE&t;&t;(64*1024)
macro_line|#ifndef DSP_BUFFCOUNT
DECL|macro|DSP_BUFFCOUNT
mdefine_line|#define DSP_BUFFCOUNT&t;&t;1&t;/* 1 is recommended. */
macro_line|#endif
DECL|macro|FM_MONO
mdefine_line|#define FM_MONO&t;&t;0x388&t;/* This is the I/O address used by AdLib */
macro_line|#ifndef CONFIG_PAS_BASE
DECL|macro|CONFIG_PAS_BASE
mdefine_line|#define CONFIG_PAS_BASE&t;0x388
macro_line|#endif
multiline_comment|/* SEQ_MAX_QUEUE is the maximum number of sequencer events buffered by the&n;   driver. (There is no need to alter this) */
DECL|macro|SEQ_MAX_QUEUE
mdefine_line|#define SEQ_MAX_QUEUE&t;1024
DECL|macro|SBFM_MAXINSTR
mdefine_line|#define SBFM_MAXINSTR&t;&t;(256)&t;/* Size of the FM Instrument bank */
multiline_comment|/* 128 instruments for general MIDI setup and 16 unassigned&t; */
DECL|macro|SND_NDEVS
mdefine_line|#define SND_NDEVS&t;256&t;/* Number of supported devices */
DECL|macro|DSP_DEFAULT_SPEED
mdefine_line|#define DSP_DEFAULT_SPEED&t;8000
DECL|macro|MAX_AUDIO_DEV
mdefine_line|#define MAX_AUDIO_DEV&t;5
DECL|macro|MAX_MIXER_DEV
mdefine_line|#define MAX_MIXER_DEV&t;5
DECL|macro|MAX_SYNTH_DEV
mdefine_line|#define MAX_SYNTH_DEV&t;5
DECL|macro|MAX_MIDI_DEV
mdefine_line|#define MAX_MIDI_DEV&t;6
DECL|macro|MAX_TIMER_DEV
mdefine_line|#define MAX_TIMER_DEV&t;4
DECL|struct|address_info
r_struct
id|address_info
(brace
DECL|member|io_base
r_int
id|io_base
suffix:semicolon
DECL|member|irq
r_int
id|irq
suffix:semicolon
DECL|member|dma
r_int
id|dma
suffix:semicolon
DECL|member|dma2
r_int
id|dma2
suffix:semicolon
DECL|member|always_detect
r_int
id|always_detect
suffix:semicolon
multiline_comment|/* 1=Trust me, it&squot;s there */
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|driver_use_1
r_int
id|driver_use_1
suffix:semicolon
multiline_comment|/* Driver defined field 1 */
DECL|member|driver_use_2
r_int
id|driver_use_2
suffix:semicolon
multiline_comment|/* Driver defined field 2 */
DECL|member|osp
r_int
op_star
id|osp
suffix:semicolon
multiline_comment|/* OS specific info */
DECL|member|card_subtype
r_int
id|card_subtype
suffix:semicolon
multiline_comment|/* Driver specific. Usually 0 */
DECL|member|memptr
r_void
op_star
id|memptr
suffix:semicolon
multiline_comment|/* Module memory chainer */
DECL|member|slots
r_int
id|slots
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* To remember driver slot ids */
)brace
suffix:semicolon
DECL|macro|SYNTH_MAX_VOICES
mdefine_line|#define SYNTH_MAX_VOICES&t;32
DECL|struct|voice_alloc_info
r_struct
id|voice_alloc_info
(brace
DECL|member|max_voice
r_int
id|max_voice
suffix:semicolon
DECL|member|used_voices
r_int
id|used_voices
suffix:semicolon
DECL|member|ptr
r_int
id|ptr
suffix:semicolon
multiline_comment|/* For device specific use */
DECL|member|map
r_int
r_int
id|map
(braket
id|SYNTH_MAX_VOICES
)braket
suffix:semicolon
multiline_comment|/* (ch &lt;&lt; 8) | (note+1) */
DECL|member|timestamp
r_int
id|timestamp
suffix:semicolon
DECL|member|alloc_times
r_int
id|alloc_times
(braket
id|SYNTH_MAX_VOICES
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|channel_info
r_struct
id|channel_info
(brace
DECL|member|pgm_num
r_int
id|pgm_num
suffix:semicolon
DECL|member|bender_value
r_int
id|bender_value
suffix:semicolon
DECL|member|bender_range
r_int
id|bender_range
suffix:semicolon
DECL|member|controllers
r_int
r_char
id|controllers
(braket
l_int|128
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Process wakeup reasons&n; */
DECL|macro|WK_NONE
mdefine_line|#define WK_NONE&t;&t;0x00
DECL|macro|WK_WAKEUP
mdefine_line|#define WK_WAKEUP&t;0x01
DECL|macro|WK_TIMEOUT
mdefine_line|#define WK_TIMEOUT&t;0x02
DECL|macro|WK_SIGNAL
mdefine_line|#define WK_SIGNAL&t;0x04
DECL|macro|WK_SLEEP
mdefine_line|#define WK_SLEEP&t;0x08
DECL|macro|WK_SELECT
mdefine_line|#define WK_SELECT&t;0x10
DECL|macro|WK_ABORT
mdefine_line|#define WK_ABORT&t;0x20
DECL|macro|OPEN_READ
mdefine_line|#define OPEN_READ&t;PCM_ENABLE_INPUT
DECL|macro|OPEN_WRITE
mdefine_line|#define OPEN_WRITE&t;PCM_ENABLE_OUTPUT
DECL|macro|OPEN_READWRITE
mdefine_line|#define OPEN_READWRITE&t;(OPEN_READ|OPEN_WRITE)
macro_line|#if OPEN_READ == FMODE_READ &amp;&amp; OPEN_WRITE == FMODE_WRITE
DECL|function|translate_mode
r_extern
id|__inline__
r_int
id|translate_mode
c_func
(paren
r_struct
id|file
op_star
id|file
)paren
(brace
r_return
id|file-&gt;f_mode
suffix:semicolon
)brace
macro_line|#else
DECL|function|translate_mode
r_extern
id|__inline__
r_int
id|translate_mode
c_func
(paren
r_struct
id|file
op_star
id|file
)paren
(brace
r_return
(paren
(paren
id|file-&gt;f_mode
op_amp
id|FMODE_READ
)paren
ques
c_cond
id|OPEN_READ
suffix:colon
l_int|0
)paren
op_or
(paren
(paren
id|file-&gt;f_mode
op_amp
id|FMODE_WRITE
)paren
ques
c_cond
id|OPEN_WRITE
suffix:colon
l_int|0
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#include &quot;sound_calls.h&quot;
macro_line|#include &quot;dev_table.h&quot;
macro_line|#ifndef DEB
DECL|macro|DEB
mdefine_line|#define DEB(x)
macro_line|#endif
macro_line|#ifndef DDB
DECL|macro|DDB
mdefine_line|#define DDB(x) {}
macro_line|#endif
macro_line|#ifndef MDB
macro_line|#ifdef MODULE
DECL|macro|MDB
mdefine_line|#define MDB(x) x
macro_line|#else
DECL|macro|MDB
mdefine_line|#define MDB(x)
macro_line|#endif
macro_line|#endif
DECL|macro|TIMER_ARMED
mdefine_line|#define TIMER_ARMED&t;121234
DECL|macro|TIMER_NOT_ARMED
mdefine_line|#define TIMER_NOT_ARMED&t;1
macro_line|#endif
eof
