macro_line|#ifndef __SOUND_SEQ_MIDI_EVENT_H
DECL|macro|__SOUND_SEQ_MIDI_EVENT_H
mdefine_line|#define __SOUND_SEQ_MIDI_EVENT_H
multiline_comment|/*&n; *  MIDI byte &lt;-&gt; sequencer event coder&n; *&n; *  Copyright (C) 1998,99 Takashi Iwai &lt;tiwai@suse.de&gt;,&n; *                        Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
macro_line|#include &quot;asequencer.h&quot;
DECL|macro|MAX_MIDI_EVENT_BUF
mdefine_line|#define MAX_MIDI_EVENT_BUF&t;256
DECL|typedef|snd_midi_event_t
r_typedef
r_struct
id|snd_midi_event_t
id|snd_midi_event_t
suffix:semicolon
multiline_comment|/* midi status */
DECL|struct|snd_midi_event_t
r_struct
id|snd_midi_event_t
(brace
DECL|member|qlen
r_int
id|qlen
suffix:semicolon
multiline_comment|/* queue length */
DECL|member|read
r_int
id|read
suffix:semicolon
multiline_comment|/* chars read */
DECL|member|type
r_int
id|type
suffix:semicolon
multiline_comment|/* current event type */
DECL|member|lastcmd
r_int
r_char
id|lastcmd
suffix:semicolon
multiline_comment|/* last command (for MIDI state handling) */
DECL|member|nostat
r_int
r_char
id|nostat
suffix:semicolon
multiline_comment|/* no state flag */
DECL|member|bufsize
r_int
id|bufsize
suffix:semicolon
multiline_comment|/* allocated buffer size */
DECL|member|buf
r_int
r_char
op_star
id|buf
suffix:semicolon
multiline_comment|/* input buffer */
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
)brace
suffix:semicolon
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
suffix:semicolon
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
suffix:semicolon
r_void
id|snd_midi_event_free
c_func
(paren
id|snd_midi_event_t
op_star
id|dev
)paren
suffix:semicolon
r_void
id|snd_midi_event_init
c_func
(paren
id|snd_midi_event_t
op_star
id|dev
)paren
suffix:semicolon
r_void
id|snd_midi_event_reset_encode
c_func
(paren
id|snd_midi_event_t
op_star
id|dev
)paren
suffix:semicolon
r_void
id|snd_midi_event_reset_decode
c_func
(paren
id|snd_midi_event_t
op_star
id|dev
)paren
suffix:semicolon
r_void
id|snd_midi_event_no_status
c_func
(paren
id|snd_midi_event_t
op_star
id|dev
comma
r_int
id|on
)paren
suffix:semicolon
multiline_comment|/* encode from byte stream - return number of written bytes if success */
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
suffix:semicolon
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
suffix:semicolon
multiline_comment|/* decode from event to bytes - return number of written bytes if success */
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
suffix:semicolon
macro_line|#endif /* __SOUND_SEQ_MIDI_EVENT_H */
eof
