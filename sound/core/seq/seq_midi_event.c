multiline_comment|/*&n; *  MIDI byte &lt;-&gt; sequencer event coder&n; *&n; *  Copyright (C) 1998,99 Takashi Iwai &lt;tiwai@suse.de&gt;,&n; *                        Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &lt;sound/seq_kernel.h&gt;
macro_line|#include &lt;sound/seq_midi_event.h&gt;
macro_line|#include &lt;sound/asoundef.h&gt;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Takashi Iwai &lt;tiwai@suse.de&gt;, Jaroslav Kysela &lt;perex@suse.cz&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;MIDI byte &lt;-&gt; sequencer event coder&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
multiline_comment|/* queue type */
multiline_comment|/* from 0 to 7 are normal commands (note off, on, etc.) */
DECL|macro|ST_NOTEOFF
mdefine_line|#define ST_NOTEOFF&t;0
DECL|macro|ST_NOTEON
mdefine_line|#define ST_NOTEON&t;1
DECL|macro|ST_SPECIAL
mdefine_line|#define ST_SPECIAL&t;8
DECL|macro|ST_SYSEX
mdefine_line|#define ST_SYSEX&t;ST_SPECIAL
multiline_comment|/* from 8 to 15 are events for 0xf0-0xf7 */
multiline_comment|/* status event types */
DECL|typedef|event_encode_t
r_typedef
r_void
(paren
op_star
id|event_encode_t
)paren
(paren
id|snd_midi_event_t
op_star
id|dev
comma
id|snd_seq_event_t
op_star
id|ev
)paren
suffix:semicolon
DECL|typedef|event_decode_t
r_typedef
r_void
(paren
op_star
id|event_decode_t
)paren
(paren
id|snd_seq_event_t
op_star
id|ev
comma
r_int
r_char
op_star
id|buf
)paren
suffix:semicolon
multiline_comment|/*&n; * prototypes&n; */
r_static
r_void
id|note_event
c_func
(paren
id|snd_midi_event_t
op_star
id|dev
comma
id|snd_seq_event_t
op_star
id|ev
)paren
suffix:semicolon
r_static
r_void
id|one_param_ctrl_event
c_func
(paren
id|snd_midi_event_t
op_star
id|dev
comma
id|snd_seq_event_t
op_star
id|ev
)paren
suffix:semicolon
r_static
r_void
id|pitchbend_ctrl_event
c_func
(paren
id|snd_midi_event_t
op_star
id|dev
comma
id|snd_seq_event_t
op_star
id|ev
)paren
suffix:semicolon
r_static
r_void
id|two_param_ctrl_event
c_func
(paren
id|snd_midi_event_t
op_star
id|dev
comma
id|snd_seq_event_t
op_star
id|ev
)paren
suffix:semicolon
r_static
r_void
id|one_param_event
c_func
(paren
id|snd_midi_event_t
op_star
id|dev
comma
id|snd_seq_event_t
op_star
id|ev
)paren
suffix:semicolon
r_static
r_void
id|songpos_event
c_func
(paren
id|snd_midi_event_t
op_star
id|dev
comma
id|snd_seq_event_t
op_star
id|ev
)paren
suffix:semicolon
r_static
r_void
id|note_decode
c_func
(paren
id|snd_seq_event_t
op_star
id|ev
comma
r_int
r_char
op_star
id|buf
)paren
suffix:semicolon
r_static
r_void
id|one_param_decode
c_func
(paren
id|snd_seq_event_t
op_star
id|ev
comma
r_int
r_char
op_star
id|buf
)paren
suffix:semicolon
r_static
r_void
id|pitchbend_decode
c_func
(paren
id|snd_seq_event_t
op_star
id|ev
comma
r_int
r_char
op_star
id|buf
)paren
suffix:semicolon
r_static
r_void
id|two_param_decode
c_func
(paren
id|snd_seq_event_t
op_star
id|ev
comma
r_int
r_char
op_star
id|buf
)paren
suffix:semicolon
r_static
r_void
id|songpos_decode
c_func
(paren
id|snd_seq_event_t
op_star
id|ev
comma
r_int
r_char
op_star
id|buf
)paren
suffix:semicolon
multiline_comment|/*&n; * event list&n; */
DECL|struct|status_event_list_t
r_static
r_struct
id|status_event_list_t
(brace
DECL|member|event
r_int
id|event
suffix:semicolon
DECL|member|qlen
r_int
id|qlen
suffix:semicolon
DECL|member|encode
id|event_encode_t
id|encode
suffix:semicolon
DECL|member|decode
id|event_decode_t
id|decode
suffix:semicolon
DECL|variable|status_event
)brace
id|status_event
(braket
)braket
op_assign
(brace
multiline_comment|/* 0x80 - 0xf0 */
(brace
id|SNDRV_SEQ_EVENT_NOTEOFF
comma
l_int|2
comma
id|note_event
comma
id|note_decode
)brace
comma
(brace
id|SNDRV_SEQ_EVENT_NOTEON
comma
l_int|2
comma
id|note_event
comma
id|note_decode
)brace
comma
(brace
id|SNDRV_SEQ_EVENT_KEYPRESS
comma
l_int|2
comma
id|note_event
comma
id|note_decode
)brace
comma
(brace
id|SNDRV_SEQ_EVENT_CONTROLLER
comma
l_int|2
comma
id|two_param_ctrl_event
comma
id|two_param_decode
)brace
comma
(brace
id|SNDRV_SEQ_EVENT_PGMCHANGE
comma
l_int|1
comma
id|one_param_ctrl_event
comma
id|one_param_decode
)brace
comma
(brace
id|SNDRV_SEQ_EVENT_CHANPRESS
comma
l_int|1
comma
id|one_param_ctrl_event
comma
id|one_param_decode
)brace
comma
(brace
id|SNDRV_SEQ_EVENT_PITCHBEND
comma
l_int|2
comma
id|pitchbend_ctrl_event
comma
id|pitchbend_decode
)brace
comma
(brace
id|SNDRV_SEQ_EVENT_NONE
comma
l_int|0
comma
l_int|NULL
comma
l_int|NULL
)brace
comma
multiline_comment|/* 0xf0 */
multiline_comment|/* 0xf0 - 0xff */
(brace
id|SNDRV_SEQ_EVENT_SYSEX
comma
l_int|1
comma
l_int|NULL
comma
l_int|NULL
)brace
comma
multiline_comment|/* sysex: 0xf0 */
(brace
id|SNDRV_SEQ_EVENT_QFRAME
comma
l_int|1
comma
id|one_param_event
comma
id|one_param_decode
)brace
comma
multiline_comment|/* 0xf1 */
(brace
id|SNDRV_SEQ_EVENT_SONGPOS
comma
l_int|2
comma
id|songpos_event
comma
id|songpos_decode
)brace
comma
multiline_comment|/* 0xf2 */
(brace
id|SNDRV_SEQ_EVENT_SONGSEL
comma
l_int|1
comma
id|one_param_event
comma
id|one_param_decode
)brace
comma
multiline_comment|/* 0xf3 */
(brace
id|SNDRV_SEQ_EVENT_NONE
comma
l_int|0
comma
l_int|NULL
comma
l_int|NULL
)brace
comma
multiline_comment|/* 0xf4 */
(brace
id|SNDRV_SEQ_EVENT_NONE
comma
l_int|0
comma
l_int|NULL
comma
l_int|NULL
)brace
comma
multiline_comment|/* 0xf5 */
(brace
id|SNDRV_SEQ_EVENT_TUNE_REQUEST
comma
l_int|0
comma
l_int|NULL
comma
l_int|NULL
)brace
comma
multiline_comment|/* 0xf6 */
(brace
id|SNDRV_SEQ_EVENT_NONE
comma
l_int|0
comma
l_int|NULL
comma
l_int|NULL
)brace
comma
multiline_comment|/* 0xf7 */
(brace
id|SNDRV_SEQ_EVENT_CLOCK
comma
l_int|0
comma
l_int|NULL
comma
l_int|NULL
)brace
comma
multiline_comment|/* 0xf8 */
(brace
id|SNDRV_SEQ_EVENT_NONE
comma
l_int|0
comma
l_int|NULL
comma
l_int|NULL
)brace
comma
multiline_comment|/* 0xf9 */
(brace
id|SNDRV_SEQ_EVENT_START
comma
l_int|0
comma
l_int|NULL
comma
l_int|NULL
)brace
comma
multiline_comment|/* 0xfa */
(brace
id|SNDRV_SEQ_EVENT_CONTINUE
comma
l_int|0
comma
l_int|NULL
comma
l_int|NULL
)brace
comma
multiline_comment|/* 0xfb */
(brace
id|SNDRV_SEQ_EVENT_STOP
comma
l_int|0
comma
l_int|NULL
comma
l_int|NULL
)brace
comma
multiline_comment|/* 0xfc */
(brace
id|SNDRV_SEQ_EVENT_NONE
comma
l_int|0
comma
l_int|NULL
comma
l_int|NULL
)brace
comma
multiline_comment|/* 0xfd */
(brace
id|SNDRV_SEQ_EVENT_SENSING
comma
l_int|0
comma
l_int|NULL
comma
l_int|NULL
)brace
comma
multiline_comment|/* 0xfe */
(brace
id|SNDRV_SEQ_EVENT_RESET
comma
l_int|0
comma
l_int|NULL
comma
l_int|NULL
)brace
comma
multiline_comment|/* 0xff */
)brace
suffix:semicolon
r_static
r_int
id|extra_decode_ctrl14
c_func
(paren
id|snd_midi_event_t
op_star
id|dev
comma
r_int
r_char
op_star
id|buf
comma
r_int
id|len
comma
id|snd_seq_event_t
op_star
id|ev
)paren
suffix:semicolon
DECL|struct|extra_event_list_t
r_static
r_struct
id|extra_event_list_t
(brace
DECL|member|event
r_int
id|event
suffix:semicolon
DECL|member|decode
r_int
(paren
op_star
id|decode
)paren
(paren
id|snd_midi_event_t
op_star
id|dev
comma
r_int
r_char
op_star
id|buf
comma
r_int
id|len
comma
id|snd_seq_event_t
op_star
id|ev
)paren
suffix:semicolon
DECL|variable|extra_event
)brace
id|extra_event
(braket
)braket
op_assign
(brace
(brace
id|SNDRV_SEQ_EVENT_CONTROL14
comma
id|extra_decode_ctrl14
)brace
comma
multiline_comment|/*{SNDRV_SEQ_EVENT_NONREGPARAM, extra_decode_nrpn},*/
multiline_comment|/*{SNDRV_SEQ_EVENT_REGPARAM, extra_decode_rpn},*/
)brace
suffix:semicolon
DECL|macro|numberof
mdefine_line|#define numberof(ary)&t;(sizeof(ary)/sizeof(ary[0]))
multiline_comment|/*&n; *  new/delete record&n; */
DECL|function|snd_midi_event_new
r_int
id|snd_midi_event_new
c_func
(paren
r_int
id|bufsize
comma
id|snd_midi_event_t
op_star
op_star
id|rdev
)paren
(brace
id|snd_midi_event_t
op_star
id|dev
suffix:semicolon
op_star
id|rdev
op_assign
l_int|NULL
suffix:semicolon
id|dev
op_assign
(paren
id|snd_midi_event_t
op_star
)paren
id|snd_kcalloc
c_func
(paren
r_sizeof
(paren
id|snd_midi_event_t
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
id|bufsize
OG
l_int|0
)paren
(brace
id|dev-&gt;buf
op_assign
id|kmalloc
c_func
(paren
id|bufsize
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;buf
op_eq
l_int|NULL
)paren
(brace
id|kfree
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
)brace
id|dev-&gt;bufsize
op_assign
id|bufsize
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|dev-&gt;lock
)paren
suffix:semicolon
op_star
id|rdev
op_assign
id|dev
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_midi_event_free
r_void
id|snd_midi_event_free
c_func
(paren
id|snd_midi_event_t
op_star
id|dev
)paren
(brace
r_if
c_cond
(paren
id|dev
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|dev-&gt;buf
)paren
id|kfree
c_func
(paren
id|dev-&gt;buf
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * initialize record&n; */
DECL|function|reset_encode
r_inline
r_static
r_void
id|reset_encode
c_func
(paren
id|snd_midi_event_t
op_star
id|dev
)paren
(brace
id|dev-&gt;read
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;qlen
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;type
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|snd_midi_event_reset_encode
r_void
id|snd_midi_event_reset_encode
c_func
(paren
id|snd_midi_event_t
op_star
id|dev
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|dev-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|reset_encode
c_func
(paren
id|dev
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|dev-&gt;lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|snd_midi_event_reset_decode
r_void
id|snd_midi_event_reset_decode
c_func
(paren
id|snd_midi_event_t
op_star
id|dev
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|dev-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|dev-&gt;lastcmd
op_assign
l_int|0xff
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|dev-&gt;lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|snd_midi_event_init
r_void
id|snd_midi_event_init
c_func
(paren
id|snd_midi_event_t
op_star
id|dev
)paren
(brace
id|snd_midi_event_reset_encode
c_func
(paren
id|dev
)paren
suffix:semicolon
id|snd_midi_event_reset_decode
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * resize buffer&n; */
DECL|function|snd_midi_event_resize_buffer
r_int
id|snd_midi_event_resize_buffer
c_func
(paren
id|snd_midi_event_t
op_star
id|dev
comma
r_int
id|bufsize
)paren
(brace
r_int
r_char
op_star
id|new_buf
comma
op_star
id|old_buf
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|bufsize
op_eq
id|dev-&gt;bufsize
)paren
r_return
l_int|0
suffix:semicolon
id|new_buf
op_assign
id|kmalloc
c_func
(paren
id|bufsize
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|new_buf
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|dev-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|old_buf
op_assign
id|dev-&gt;buf
suffix:semicolon
id|dev-&gt;buf
op_assign
id|new_buf
suffix:semicolon
id|dev-&gt;bufsize
op_assign
id|bufsize
suffix:semicolon
id|reset_encode
c_func
(paren
id|dev
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|dev-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|old_buf
)paren
id|kfree
c_func
(paren
id|old_buf
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *  read bytes and encode to sequencer event if finished&n; *  return the size of encoded bytes&n; */
DECL|function|snd_midi_event_encode
r_int
id|snd_midi_event_encode
c_func
(paren
id|snd_midi_event_t
op_star
id|dev
comma
r_int
r_char
op_star
id|buf
comma
r_int
id|count
comma
id|snd_seq_event_t
op_star
id|ev
)paren
(brace
r_int
id|result
op_assign
l_int|0
suffix:semicolon
r_int
id|rc
suffix:semicolon
id|ev-&gt;type
op_assign
id|SNDRV_SEQ_EVENT_NONE
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
OG
l_int|0
)paren
(brace
id|rc
op_assign
id|snd_midi_event_encode_byte
c_func
(paren
id|dev
comma
op_star
id|buf
op_increment
comma
id|ev
)paren
suffix:semicolon
id|result
op_increment
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
r_else
r_if
c_cond
(paren
id|rc
OG
l_int|0
)paren
r_return
id|result
suffix:semicolon
)brace
r_return
id|result
suffix:semicolon
)brace
multiline_comment|/*&n; *  read one byte and encode to sequencer event:&n; *  return 1 if MIDI bytes are encoded to an event&n; *         0 data is not finished&n; *         negative for error&n; */
DECL|function|snd_midi_event_encode_byte
r_int
id|snd_midi_event_encode_byte
c_func
(paren
id|snd_midi_event_t
op_star
id|dev
comma
r_int
id|c
comma
id|snd_seq_event_t
op_star
id|ev
)paren
(brace
r_int
id|rc
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|c
op_and_assign
l_int|0xff
suffix:semicolon
r_if
c_cond
(paren
id|c
op_ge
id|MIDI_CMD_COMMON_CLOCK
)paren
(brace
multiline_comment|/* real-time event */
id|ev-&gt;type
op_assign
id|status_event
(braket
id|ST_SPECIAL
op_plus
id|c
op_minus
l_int|0xf0
)braket
dot
id|event
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
r_return
l_int|1
suffix:semicolon
)brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|dev-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;qlen
OG
l_int|0
)paren
(brace
multiline_comment|/* rest of command */
id|dev-&gt;buf
(braket
id|dev-&gt;read
op_increment
)braket
op_assign
id|c
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;type
op_ne
id|ST_SYSEX
)paren
id|dev-&gt;qlen
op_decrement
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* new command */
id|dev-&gt;read
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|c
op_amp
l_int|0x80
)paren
(brace
id|dev-&gt;buf
(braket
l_int|0
)braket
op_assign
id|c
suffix:semicolon
r_if
c_cond
(paren
(paren
id|c
op_amp
l_int|0xf0
)paren
op_eq
l_int|0xf0
)paren
multiline_comment|/* special events */
id|dev-&gt;type
op_assign
(paren
id|c
op_amp
l_int|0x0f
)paren
op_plus
id|ST_SPECIAL
suffix:semicolon
r_else
id|dev-&gt;type
op_assign
(paren
id|c
op_rshift
l_int|4
)paren
op_amp
l_int|0x07
suffix:semicolon
id|dev-&gt;qlen
op_assign
id|status_event
(braket
id|dev-&gt;type
)braket
dot
id|qlen
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* process this byte as argument */
id|dev-&gt;buf
(braket
id|dev-&gt;read
op_increment
)braket
op_assign
id|c
suffix:semicolon
id|dev-&gt;qlen
op_assign
id|status_event
(braket
id|dev-&gt;type
)braket
dot
id|qlen
op_minus
l_int|1
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|dev-&gt;qlen
op_eq
l_int|0
)paren
(brace
id|ev-&gt;type
op_assign
id|status_event
(braket
id|dev-&gt;type
)braket
dot
id|event
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
r_if
c_cond
(paren
id|status_event
(braket
id|dev-&gt;type
)braket
dot
id|encode
)paren
multiline_comment|/* set data values */
id|status_event
(braket
id|dev-&gt;type
)braket
dot
id|encode
c_func
(paren
id|dev
comma
id|ev
)paren
suffix:semicolon
id|rc
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|dev-&gt;type
op_eq
id|ST_SYSEX
)paren
(brace
r_if
c_cond
(paren
id|c
op_eq
id|MIDI_CMD_COMMON_SYSEX_END
op_logical_or
id|dev-&gt;read
op_ge
id|dev-&gt;bufsize
)paren
(brace
id|ev-&gt;flags
op_and_assign
op_complement
id|SNDRV_SEQ_EVENT_LENGTH_MASK
suffix:semicolon
id|ev-&gt;flags
op_or_assign
id|SNDRV_SEQ_EVENT_LENGTH_VARIABLE
suffix:semicolon
id|ev-&gt;type
op_assign
id|SNDRV_SEQ_EVENT_SYSEX
suffix:semicolon
id|ev-&gt;data.ext.len
op_assign
id|dev-&gt;read
suffix:semicolon
id|ev-&gt;data.ext.ptr
op_assign
id|dev-&gt;buf
suffix:semicolon
r_if
c_cond
(paren
id|c
op_ne
id|MIDI_CMD_COMMON_SYSEX_END
)paren
id|dev-&gt;read
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* continue to parse */
r_else
id|reset_encode
c_func
(paren
id|dev
)paren
suffix:semicolon
multiline_comment|/* all parsed */
id|rc
op_assign
l_int|1
suffix:semicolon
)brace
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|dev-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
multiline_comment|/* encode note event */
DECL|function|note_event
r_static
r_void
id|note_event
c_func
(paren
id|snd_midi_event_t
op_star
id|dev
comma
id|snd_seq_event_t
op_star
id|ev
)paren
(brace
id|ev-&gt;data.note.channel
op_assign
id|dev-&gt;buf
(braket
l_int|0
)braket
op_amp
l_int|0x0f
suffix:semicolon
id|ev-&gt;data.note.note
op_assign
id|dev-&gt;buf
(braket
l_int|1
)braket
suffix:semicolon
id|ev-&gt;data.note.velocity
op_assign
id|dev-&gt;buf
(braket
l_int|2
)braket
suffix:semicolon
)brace
multiline_comment|/* encode one parameter controls */
DECL|function|one_param_ctrl_event
r_static
r_void
id|one_param_ctrl_event
c_func
(paren
id|snd_midi_event_t
op_star
id|dev
comma
id|snd_seq_event_t
op_star
id|ev
)paren
(brace
id|ev-&gt;data.control.channel
op_assign
id|dev-&gt;buf
(braket
l_int|0
)braket
op_amp
l_int|0x0f
suffix:semicolon
id|ev-&gt;data.control.value
op_assign
id|dev-&gt;buf
(braket
l_int|1
)braket
suffix:semicolon
)brace
multiline_comment|/* encode pitch wheel change */
DECL|function|pitchbend_ctrl_event
r_static
r_void
id|pitchbend_ctrl_event
c_func
(paren
id|snd_midi_event_t
op_star
id|dev
comma
id|snd_seq_event_t
op_star
id|ev
)paren
(brace
id|ev-&gt;data.control.channel
op_assign
id|dev-&gt;buf
(braket
l_int|0
)braket
op_amp
l_int|0x0f
suffix:semicolon
id|ev-&gt;data.control.value
op_assign
(paren
r_int
)paren
id|dev-&gt;buf
(braket
l_int|2
)braket
op_star
l_int|128
op_plus
(paren
r_int
)paren
id|dev-&gt;buf
(braket
l_int|1
)braket
op_minus
l_int|8192
suffix:semicolon
)brace
multiline_comment|/* encode midi control change */
DECL|function|two_param_ctrl_event
r_static
r_void
id|two_param_ctrl_event
c_func
(paren
id|snd_midi_event_t
op_star
id|dev
comma
id|snd_seq_event_t
op_star
id|ev
)paren
(brace
id|ev-&gt;data.control.channel
op_assign
id|dev-&gt;buf
(braket
l_int|0
)braket
op_amp
l_int|0x0f
suffix:semicolon
id|ev-&gt;data.control.param
op_assign
id|dev-&gt;buf
(braket
l_int|1
)braket
suffix:semicolon
id|ev-&gt;data.control.value
op_assign
id|dev-&gt;buf
(braket
l_int|2
)braket
suffix:semicolon
)brace
multiline_comment|/* encode one parameter value*/
DECL|function|one_param_event
r_static
r_void
id|one_param_event
c_func
(paren
id|snd_midi_event_t
op_star
id|dev
comma
id|snd_seq_event_t
op_star
id|ev
)paren
(brace
id|ev-&gt;data.control.value
op_assign
id|dev-&gt;buf
(braket
l_int|1
)braket
suffix:semicolon
)brace
multiline_comment|/* encode song position */
DECL|function|songpos_event
r_static
r_void
id|songpos_event
c_func
(paren
id|snd_midi_event_t
op_star
id|dev
comma
id|snd_seq_event_t
op_star
id|ev
)paren
(brace
id|ev-&gt;data.control.value
op_assign
(paren
r_int
)paren
id|dev-&gt;buf
(braket
l_int|2
)braket
op_star
l_int|128
op_plus
(paren
r_int
)paren
id|dev-&gt;buf
(braket
l_int|1
)braket
suffix:semicolon
)brace
multiline_comment|/*&n; * decode from a sequencer event to midi bytes&n; * return the size of decoded midi events&n; */
DECL|function|snd_midi_event_decode
r_int
id|snd_midi_event_decode
c_func
(paren
id|snd_midi_event_t
op_star
id|dev
comma
r_int
r_char
op_star
id|buf
comma
r_int
id|count
comma
id|snd_seq_event_t
op_star
id|ev
)paren
(brace
r_int
id|cmd
comma
id|type
suffix:semicolon
r_if
c_cond
(paren
id|ev-&gt;type
op_eq
id|SNDRV_SEQ_EVENT_NONE
)paren
r_return
op_minus
id|ENOENT
suffix:semicolon
r_for
c_loop
(paren
id|type
op_assign
l_int|0
suffix:semicolon
id|type
OL
id|numberof
c_func
(paren
id|status_event
)paren
suffix:semicolon
id|type
op_increment
)paren
(brace
r_if
c_cond
(paren
id|ev-&gt;type
op_eq
id|status_event
(braket
id|type
)braket
dot
id|event
)paren
r_goto
id|__found
suffix:semicolon
)brace
r_for
c_loop
(paren
id|type
op_assign
l_int|0
suffix:semicolon
id|type
OL
id|numberof
c_func
(paren
id|extra_event
)paren
suffix:semicolon
id|type
op_increment
)paren
(brace
r_if
c_cond
(paren
id|ev-&gt;type
op_eq
id|extra_event
(braket
id|type
)braket
dot
id|event
)paren
r_return
id|extra_event
(braket
id|type
)braket
dot
id|decode
c_func
(paren
id|dev
comma
id|buf
comma
id|count
comma
id|ev
)paren
suffix:semicolon
)brace
r_return
op_minus
id|ENOENT
suffix:semicolon
id|__found
suffix:colon
r_if
c_cond
(paren
id|type
op_ge
id|ST_SPECIAL
)paren
id|cmd
op_assign
l_int|0xf0
op_plus
(paren
id|type
op_minus
id|ST_SPECIAL
)paren
suffix:semicolon
r_else
multiline_comment|/* data.note.channel and data.control.channel is identical */
id|cmd
op_assign
l_int|0x80
op_or
(paren
id|type
op_lshift
l_int|4
)paren
op_or
(paren
id|ev-&gt;data.note.channel
op_amp
l_int|0x0f
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cmd
op_eq
id|MIDI_CMD_COMMON_SYSEX
)paren
(brace
id|snd_midi_event_reset_decode
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
id|snd_seq_expand_var_event
c_func
(paren
id|ev
comma
id|count
comma
id|buf
comma
l_int|1
comma
l_int|0
)paren
suffix:semicolon
)brace
r_else
(brace
r_int
id|qlen
suffix:semicolon
r_int
r_char
id|xbuf
(braket
l_int|4
)braket
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|dev-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|cmd
op_amp
l_int|0xf0
)paren
op_eq
l_int|0xf0
op_logical_or
id|dev-&gt;lastcmd
op_ne
id|cmd
)paren
(brace
id|dev-&gt;lastcmd
op_assign
id|cmd
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|dev-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|xbuf
(braket
l_int|0
)braket
op_assign
id|cmd
suffix:semicolon
r_if
c_cond
(paren
id|status_event
(braket
id|type
)braket
dot
id|decode
)paren
id|status_event
(braket
id|type
)braket
dot
id|decode
c_func
(paren
id|ev
comma
id|xbuf
op_plus
l_int|1
)paren
suffix:semicolon
id|qlen
op_assign
id|status_event
(braket
id|type
)braket
dot
id|qlen
op_plus
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|dev-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status_event
(braket
id|type
)braket
dot
id|decode
)paren
id|status_event
(braket
id|type
)braket
dot
id|decode
c_func
(paren
id|ev
comma
id|xbuf
op_plus
l_int|0
)paren
suffix:semicolon
id|qlen
op_assign
id|status_event
(braket
id|type
)braket
dot
id|qlen
suffix:semicolon
)brace
r_if
c_cond
(paren
id|count
OL
id|qlen
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memcpy
c_func
(paren
id|buf
comma
id|xbuf
comma
id|qlen
)paren
suffix:semicolon
r_return
id|qlen
suffix:semicolon
)brace
)brace
multiline_comment|/* decode note event */
DECL|function|note_decode
r_static
r_void
id|note_decode
c_func
(paren
id|snd_seq_event_t
op_star
id|ev
comma
r_int
r_char
op_star
id|buf
)paren
(brace
id|buf
(braket
l_int|0
)braket
op_assign
id|ev-&gt;data.note.note
op_amp
l_int|0x7f
suffix:semicolon
id|buf
(braket
l_int|1
)braket
op_assign
id|ev-&gt;data.note.velocity
op_amp
l_int|0x7f
suffix:semicolon
)brace
multiline_comment|/* decode one parameter controls */
DECL|function|one_param_decode
r_static
r_void
id|one_param_decode
c_func
(paren
id|snd_seq_event_t
op_star
id|ev
comma
r_int
r_char
op_star
id|buf
)paren
(brace
id|buf
(braket
l_int|0
)braket
op_assign
id|ev-&gt;data.control.value
op_amp
l_int|0x7f
suffix:semicolon
)brace
multiline_comment|/* decode pitch wheel change */
DECL|function|pitchbend_decode
r_static
r_void
id|pitchbend_decode
c_func
(paren
id|snd_seq_event_t
op_star
id|ev
comma
r_int
r_char
op_star
id|buf
)paren
(brace
r_int
id|value
op_assign
id|ev-&gt;data.control.value
op_plus
l_int|8192
suffix:semicolon
id|buf
(braket
l_int|0
)braket
op_assign
id|value
op_amp
l_int|0x7f
suffix:semicolon
id|buf
(braket
l_int|1
)braket
op_assign
(paren
id|value
op_rshift
l_int|7
)paren
op_amp
l_int|0x7f
suffix:semicolon
)brace
multiline_comment|/* decode midi control change */
DECL|function|two_param_decode
r_static
r_void
id|two_param_decode
c_func
(paren
id|snd_seq_event_t
op_star
id|ev
comma
r_int
r_char
op_star
id|buf
)paren
(brace
id|buf
(braket
l_int|0
)braket
op_assign
id|ev-&gt;data.control.param
op_amp
l_int|0x7f
suffix:semicolon
id|buf
(braket
l_int|1
)braket
op_assign
id|ev-&gt;data.control.value
op_amp
l_int|0x7f
suffix:semicolon
)brace
multiline_comment|/* decode song position */
DECL|function|songpos_decode
r_static
r_void
id|songpos_decode
c_func
(paren
id|snd_seq_event_t
op_star
id|ev
comma
r_int
r_char
op_star
id|buf
)paren
(brace
id|buf
(braket
l_int|0
)braket
op_assign
id|ev-&gt;data.control.value
op_amp
l_int|0x7f
suffix:semicolon
id|buf
(braket
l_int|1
)braket
op_assign
(paren
id|ev-&gt;data.control.value
op_rshift
l_int|7
)paren
op_amp
l_int|0x7f
suffix:semicolon
)brace
multiline_comment|/* decode 14bit control */
DECL|function|extra_decode_ctrl14
r_static
r_int
id|extra_decode_ctrl14
c_func
(paren
id|snd_midi_event_t
op_star
id|dev
comma
r_int
r_char
op_star
id|buf
comma
r_int
id|count
comma
id|snd_seq_event_t
op_star
id|ev
)paren
(brace
r_if
c_cond
(paren
id|ev-&gt;data.control.param
OL
l_int|32
)paren
(brace
r_if
c_cond
(paren
id|count
OL
l_int|5
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|buf
(braket
l_int|0
)braket
op_assign
id|MIDI_CMD_CONTROL
op_or
(paren
id|ev-&gt;data.control.channel
op_amp
l_int|0x0f
)paren
suffix:semicolon
id|buf
(braket
l_int|1
)braket
op_assign
id|ev-&gt;data.control.param
suffix:semicolon
id|buf
(braket
l_int|2
)braket
op_assign
(paren
id|ev-&gt;data.control.value
op_rshift
l_int|7
)paren
op_amp
l_int|0x7f
suffix:semicolon
id|buf
(braket
l_int|3
)braket
op_assign
id|ev-&gt;data.control.param
op_plus
l_int|32
suffix:semicolon
id|buf
(braket
l_int|4
)braket
op_assign
id|ev-&gt;data.control.value
op_amp
l_int|0x7f
suffix:semicolon
id|dev-&gt;lastcmd
op_assign
id|buf
(braket
l_int|0
)braket
suffix:semicolon
r_return
l_int|5
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|count
OL
l_int|3
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|buf
(braket
l_int|0
)braket
op_assign
id|MIDI_CMD_CONTROL
op_or
(paren
id|ev-&gt;data.control.channel
op_amp
l_int|0x0f
)paren
suffix:semicolon
id|buf
(braket
l_int|1
)braket
op_assign
id|ev-&gt;data.control.param
op_amp
l_int|0x7f
suffix:semicolon
id|buf
(braket
l_int|4
)braket
op_assign
id|ev-&gt;data.control.value
op_amp
l_int|0x7f
suffix:semicolon
id|dev-&gt;lastcmd
op_assign
id|buf
(braket
l_int|0
)braket
suffix:semicolon
r_return
l_int|3
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; *  exports&n; */
DECL|variable|snd_midi_event_new
id|EXPORT_SYMBOL
c_func
(paren
id|snd_midi_event_new
)paren
suffix:semicolon
DECL|variable|snd_midi_event_free
id|EXPORT_SYMBOL
c_func
(paren
id|snd_midi_event_free
)paren
suffix:semicolon
DECL|variable|snd_midi_event_resize_buffer
id|EXPORT_SYMBOL
c_func
(paren
id|snd_midi_event_resize_buffer
)paren
suffix:semicolon
DECL|variable|snd_midi_event_init
id|EXPORT_SYMBOL
c_func
(paren
id|snd_midi_event_init
)paren
suffix:semicolon
DECL|variable|snd_midi_event_reset_encode
id|EXPORT_SYMBOL
c_func
(paren
id|snd_midi_event_reset_encode
)paren
suffix:semicolon
DECL|variable|snd_midi_event_reset_decode
id|EXPORT_SYMBOL
c_func
(paren
id|snd_midi_event_reset_decode
)paren
suffix:semicolon
DECL|variable|snd_midi_event_encode
id|EXPORT_SYMBOL
c_func
(paren
id|snd_midi_event_encode
)paren
suffix:semicolon
DECL|variable|snd_midi_event_encode_byte
id|EXPORT_SYMBOL
c_func
(paren
id|snd_midi_event_encode_byte
)paren
suffix:semicolon
DECL|variable|snd_midi_event_decode
id|EXPORT_SYMBOL
c_func
(paren
id|snd_midi_event_decode
)paren
suffix:semicolon
eof