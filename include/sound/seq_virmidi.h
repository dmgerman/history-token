macro_line|#ifndef __SOUND_SEQ_VIRMIDI_H
DECL|macro|__SOUND_SEQ_VIRMIDI_H
mdefine_line|#define __SOUND_SEQ_VIRMIDI_H
multiline_comment|/*&n; *  Virtual Raw MIDI client on Sequencer&n; *  Copyright (c) 2000 by Takashi Iwai &lt;tiwai@suse.de&gt;,&n; *                        Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#include &quot;rawmidi.h&quot;
macro_line|#include &quot;seq_midi_event.h&quot;
DECL|typedef|snd_virmidi_dev_t
r_typedef
r_struct
id|_snd_virmidi_dev
id|snd_virmidi_dev_t
suffix:semicolon
multiline_comment|/*&n; * device file instance:&n; * This instance is created at each time the midi device file is&n; * opened.  Each instance has its own input buffer and MIDI parser&n; * (buffer), and is associated with the device instance.&n; */
DECL|struct|_snd_virmidi
r_typedef
r_struct
id|_snd_virmidi
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|seq_mode
r_int
id|seq_mode
suffix:semicolon
DECL|member|client
r_int
id|client
suffix:semicolon
DECL|member|port
r_int
id|port
suffix:semicolon
DECL|member|trigger
r_int
id|trigger
suffix:colon
l_int|1
suffix:semicolon
DECL|member|parser
id|snd_midi_event_t
op_star
id|parser
suffix:semicolon
DECL|member|event
id|snd_seq_event_t
id|event
suffix:semicolon
DECL|member|rdev
id|snd_virmidi_dev_t
op_star
id|rdev
suffix:semicolon
DECL|member|substream
id|snd_rawmidi_substream_t
op_star
id|substream
suffix:semicolon
DECL|typedef|snd_virmidi_t
)brace
id|snd_virmidi_t
suffix:semicolon
DECL|macro|SNDRV_VIRMIDI_SUBSCRIBE
mdefine_line|#define SNDRV_VIRMIDI_SUBSCRIBE&t;(1&lt;&lt;0)
DECL|macro|SNDRV_VIRMIDI_USE
mdefine_line|#define SNDRV_VIRMIDI_USE&t;&t;(1&lt;&lt;1)
multiline_comment|/*&n; * device record:&n; * Each virtual midi device has one device instance.  It contains&n; * common information and the linked-list of opened files, &n; */
DECL|struct|_snd_virmidi_dev
r_struct
id|_snd_virmidi_dev
(brace
DECL|member|card
id|snd_card_t
op_star
id|card
suffix:semicolon
multiline_comment|/* associated card */
DECL|member|rmidi
id|snd_rawmidi_t
op_star
id|rmidi
suffix:semicolon
multiline_comment|/* rawmidi device */
DECL|member|seq_mode
r_int
id|seq_mode
suffix:semicolon
multiline_comment|/* SNDRV_VIRMIDI_XXX */
DECL|member|device
r_int
id|device
suffix:semicolon
multiline_comment|/* sequencer device */
DECL|member|client
r_int
id|client
suffix:semicolon
multiline_comment|/* created/attached client */
DECL|member|port
r_int
id|port
suffix:semicolon
multiline_comment|/* created/attached port */
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* SNDRV_VIRMIDI_* */
DECL|member|filelist_lock
id|rwlock_t
id|filelist_lock
suffix:semicolon
DECL|member|filelist
r_struct
id|list_head
id|filelist
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* sequencer mode:&n; * ATTACH = input/output events from midi device are routed to the&n; *          attached sequencer port.  sequencer port is not created&n; *          by virmidi itself.&n; * DISPATCH = input/output events are routed to subscribers.&n; *            sequencer port is created in virmidi.&n; */
DECL|macro|SNDRV_VIRMIDI_SEQ_NONE
mdefine_line|#define SNDRV_VIRMIDI_SEQ_NONE&t;&t;0
DECL|macro|SNDRV_VIRMIDI_SEQ_ATTACH
mdefine_line|#define SNDRV_VIRMIDI_SEQ_ATTACH&t;&t;1
DECL|macro|SNDRV_VIRMIDI_SEQ_DISPATCH
mdefine_line|#define SNDRV_VIRMIDI_SEQ_DISPATCH&t;2
r_int
id|snd_virmidi_new
c_func
(paren
id|snd_card_t
op_star
id|card
comma
r_int
id|device
comma
id|snd_rawmidi_t
op_star
op_star
id|rrmidi
)paren
suffix:semicolon
macro_line|#endif /* __SOUND_SEQ_VIRMIDI */
eof
