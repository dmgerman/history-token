multiline_comment|/*     &n; **********************************************************************&n; *     midi.h&n; *     Copyright 1999, 2000 Creative Labs, Inc. &n; * &n; ********************************************************************** &n; * &n; *     Date                 Author          Summary of changes &n; *     ----                 ------          ------------------ &n; *     October 20, 1999     Bertrand Lee    base code release &n; * &n; ********************************************************************** &n; * &n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version. &n; * &n; *     This program is distributed in the hope that it will be useful, &n; *     but WITHOUT ANY WARRANTY; without even the implied warranty of &n; *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the &n; *     GNU General Public License for more details. &n; * &n; *     You should have received a copy of the GNU General Public &n; *     License along with this program; if not, write to the Free &n; *     Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, &n; *     USA. &n; * &n; ********************************************************************** &n; */
macro_line|#ifndef _MIDI_H
DECL|macro|_MIDI_H
mdefine_line|#define _MIDI_H
DECL|macro|FMODE_MIDI_SHIFT
mdefine_line|#define FMODE_MIDI_SHIFT 3
DECL|macro|FMODE_MIDI_READ
mdefine_line|#define FMODE_MIDI_READ  (FMODE_READ &lt;&lt; FMODE_MIDI_SHIFT)
DECL|macro|FMODE_MIDI_WRITE
mdefine_line|#define FMODE_MIDI_WRITE (FMODE_WRITE &lt;&lt; FMODE_MIDI_SHIFT)
DECL|macro|MIDIIN_STATE_STARTED
mdefine_line|#define MIDIIN_STATE_STARTED 0x00000001
DECL|macro|MIDIIN_STATE_STOPPED
mdefine_line|#define MIDIIN_STATE_STOPPED 0x00000002
DECL|macro|MIDIIN_BUFLEN
mdefine_line|#define MIDIIN_BUFLEN 1024
DECL|struct|emu10k1_mididevice
r_struct
id|emu10k1_mididevice
(brace
DECL|member|card
r_struct
id|emu10k1_card
op_star
id|card
suffix:semicolon
DECL|member|mistate
id|u32
id|mistate
suffix:semicolon
DECL|member|oWait
id|wait_queue_head_t
id|oWait
suffix:semicolon
DECL|member|iWait
id|wait_queue_head_t
id|iWait
suffix:semicolon
DECL|member|iBuf
id|s8
id|iBuf
(braket
id|MIDIIN_BUFLEN
)braket
suffix:semicolon
DECL|member|ird
DECL|member|iwr
DECL|member|icnt
id|u16
id|ird
comma
id|iwr
comma
id|icnt
suffix:semicolon
DECL|member|mid_hdrs
r_struct
id|list_head
id|mid_hdrs
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* uncomment next line to use midi port on Audigy drive */
singleline_comment|//#define USE_AUDIGY_DRIVE_MIDI
macro_line|#ifdef USE_AUDIGY_DRIVE_MIDI
DECL|macro|A_MUDATA
mdefine_line|#define A_MUDATA&t;A_MUDATA2
DECL|macro|A_MUCMD
mdefine_line|#define A_MUCMD&t;&t;A_MUCMD2
DECL|macro|A_MUSTAT
mdefine_line|#define A_MUSTAT&t;A_MUCMD2
DECL|macro|A_IPR_MIDITRANSBUFEMPTY
mdefine_line|#define A_IPR_MIDITRANSBUFEMPTY&t;A_IPR_MIDITRANSBUFEMPTY2
DECL|macro|A_IPR_MIDIRECVBUFEMPTY
mdefine_line|#define A_IPR_MIDIRECVBUFEMPTY&t;A_IPR_MIDIRECVBUFEMPTY2
DECL|macro|A_INTE_MIDITXENABLE
mdefine_line|#define A_INTE_MIDITXENABLE&t;A_INTE_MIDITXENABLE2
DECL|macro|A_INTE_MIDIRXENABLE
mdefine_line|#define A_INTE_MIDIRXENABLE&t;A_INTE_MIDIRXENABLE2
macro_line|#else
DECL|macro|A_MUDATA
mdefine_line|#define A_MUDATA&t;A_MUDATA1
DECL|macro|A_MUCMD
mdefine_line|#define A_MUCMD&t;&t;A_MUCMD1
DECL|macro|A_MUSTAT
mdefine_line|#define A_MUSTAT&t;A_MUCMD1
DECL|macro|A_IPR_MIDITRANSBUFEMPTY
mdefine_line|#define A_IPR_MIDITRANSBUFEMPTY&t;A_IPR_MIDITRANSBUFEMPTY1
DECL|macro|A_IPR_MIDIRECVBUFEMPTY
mdefine_line|#define A_IPR_MIDIRECVBUFEMPTY&t;A_IPR_MIDIRECVBUFEMPTY1
DECL|macro|A_INTE_MIDITXENABLE
mdefine_line|#define A_INTE_MIDITXENABLE&t;A_INTE_MIDITXENABLE1
DECL|macro|A_INTE_MIDIRXENABLE
mdefine_line|#define A_INTE_MIDIRXENABLE&t;A_INTE_MIDIRXENABLE1
macro_line|#endif
macro_line|#endif /* _MIDI_H */
eof
