multiline_comment|/*&n; **********************************************************************&n; *     isblive_mid.h&n; *     Copyright 1999, 2000 Creative Labs, Inc.&n; *&n; **********************************************************************&n; *&n; *     Date                 Author          Summary of changes&n; *     ----                 ------          ------------------&n; *     October 20, 1999     Bertrand Lee    base code release&n; *&n; **********************************************************************&n; *&n; *     This program is free software; you can redistribute it and/or&n; *     modify it under the terms of the GNU General Public License as&n; *     published by the Free Software Foundation; either version 2 of&n; *     the License, or (at your option) any later version.&n; *&n; *     This program is distributed in the hope that it will be useful,&n; *     but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *     GNU General Public License for more details.&n; *&n; *     You should have received a copy of the GNU General Public&n; *     License along with this program; if not, write to the Free&n; *     Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139,&n; *     USA.&n; *&n; **********************************************************************&n; */
macro_line|#ifndef _ICARDMIDI_H
DECL|macro|_ICARDMIDI_H
mdefine_line|#define _ICARDMIDI_H
multiline_comment|/* MIDI defines */
DECL|macro|MIDI_DATA_FIRST
mdefine_line|#define MIDI_DATA_FIRST                 0x00
DECL|macro|MIDI_DATA_LAST
mdefine_line|#define MIDI_DATA_LAST                  0x7F
DECL|macro|MIDI_STATUS_FIRST
mdefine_line|#define MIDI_STATUS_FIRST               0x80
DECL|macro|MIDI_STATUS_LAST
mdefine_line|#define MIDI_STATUS_LAST                0xFF
multiline_comment|/* Channel status bytes */
DECL|macro|MIDI_STATUS_CHANNEL_FIRST
mdefine_line|#define MIDI_STATUS_CHANNEL_FIRST       0x80
DECL|macro|MIDI_STATUS_CHANNEL_LAST
mdefine_line|#define MIDI_STATUS_CHANNEL_LAST        0xE0
DECL|macro|MIDI_STATUS_CHANNEL_MASK
mdefine_line|#define MIDI_STATUS_CHANNEL_MASK        0xF0
multiline_comment|/* Channel voice messages */
DECL|macro|MIDI_VOICE_NOTE_OFF
mdefine_line|#define MIDI_VOICE_NOTE_OFF             0x80
DECL|macro|MIDI_VOICE_NOTE_ON
mdefine_line|#define MIDI_VOICE_NOTE_ON              0x90
DECL|macro|MIDI_VOICE_POLY_PRESSURE
mdefine_line|#define MIDI_VOICE_POLY_PRESSURE        0xA0
DECL|macro|MIDI_VOICE_CONTROL_CHANGE
mdefine_line|#define MIDI_VOICE_CONTROL_CHANGE       0xB0
DECL|macro|MIDI_VOICE_PROGRAM_CHANGE
mdefine_line|#define MIDI_VOICE_PROGRAM_CHANGE       0xC0
DECL|macro|MIDI_VOICE_CHANNEL_PRESSURE
mdefine_line|#define MIDI_VOICE_CHANNEL_PRESSURE     0xD0
DECL|macro|MIDI_VOICE_PITCH_BEND
mdefine_line|#define MIDI_VOICE_PITCH_BEND           0xE0
multiline_comment|/* Channel mode messages */
DECL|macro|MIDI_MODE_CHANNEL
mdefine_line|#define MIDI_MODE_CHANNEL               MIDI_VOICE_CONTROL_CHANGE
multiline_comment|/* System status bytes */
DECL|macro|MIDI_STATUS_SYSTEM_FIRST
mdefine_line|#define MIDI_STATUS_SYSTEM_FIRST        0xF0
DECL|macro|MIDI_STATUS_SYSTEM_LAST
mdefine_line|#define MIDI_STATUS_SYSTEM_LAST         0xFF
multiline_comment|/* System exclusive messages */
DECL|macro|MIDI_SYSEX_BEGIN
mdefine_line|#define MIDI_SYSEX_BEGIN                0xF0
DECL|macro|MIDI_SYSEX_EOX
mdefine_line|#define MIDI_SYSEX_EOX                  0xF7
multiline_comment|/* System common messages */
DECL|macro|MIDI_COMMON_TCQF
mdefine_line|#define MIDI_COMMON_TCQF                0xF1&t;/* Time code quarter frame  */
DECL|macro|MIDI_COMMON_SONG_POSITION
mdefine_line|#define MIDI_COMMON_SONG_POSITION       0xF2
DECL|macro|MIDI_COMMON_SONG_SELECT
mdefine_line|#define MIDI_COMMON_SONG_SELECT         0xF3
DECL|macro|MIDI_COMMON_UNDEFINED_F4
mdefine_line|#define MIDI_COMMON_UNDEFINED_F4        0xF4
DECL|macro|MIDI_COMMON_UNDEFINED_F5
mdefine_line|#define MIDI_COMMON_UNDEFINED_F5        0xF5
DECL|macro|MIDI_COMMON_TUNE_REQUEST
mdefine_line|#define MIDI_COMMON_TUNE_REQUEST        0xF6
multiline_comment|/* System real-time messages */
DECL|macro|MIDI_RTIME_TIMING_CLOCK
mdefine_line|#define MIDI_RTIME_TIMING_CLOCK         0xF8
DECL|macro|MIDI_RTIME_UNDEFINED_F9
mdefine_line|#define MIDI_RTIME_UNDEFINED_F9         0xF9
DECL|macro|MIDI_RTIME_START
mdefine_line|#define MIDI_RTIME_START                0xFA
DECL|macro|MIDI_RTIME_CONTINUE
mdefine_line|#define MIDI_RTIME_CONTINUE             0xFB
DECL|macro|MIDI_RTIME_STOP
mdefine_line|#define MIDI_RTIME_STOP                 0xFC
DECL|macro|MIDI_RTIME_UNDEFINED_FD
mdefine_line|#define MIDI_RTIME_UNDEFINED_FD         0xFD
DECL|macro|MIDI_RTIME_ACTIVE_SENSING
mdefine_line|#define MIDI_RTIME_ACTIVE_SENSING       0xFE
DECL|macro|MIDI_RTIME_SYSTEM_RESET
mdefine_line|#define MIDI_RTIME_SYSTEM_RESET         0xFF
multiline_comment|/* Flags for flags parm of midiOutCachePatches(), midiOutCacheDrumPatches() */
DECL|macro|MIDI_CACHE_ALL
mdefine_line|#define MIDI_CACHE_ALL                  1
DECL|macro|MIDI_CACHE_BESTFIT
mdefine_line|#define MIDI_CACHE_BESTFIT              2
DECL|macro|MIDI_CACHE_QUERY
mdefine_line|#define MIDI_CACHE_QUERY                3
DECL|macro|MIDI_UNCACHE
mdefine_line|#define MIDI_UNCACHE                    4
multiline_comment|/* Event declarations for MPU IRQ Callbacks */
DECL|macro|ICARDMIDI_INLONGDATA
mdefine_line|#define ICARDMIDI_INLONGDATA            0x00000001 /* MIM_LONGDATA */
DECL|macro|ICARDMIDI_INLONGERROR
mdefine_line|#define ICARDMIDI_INLONGERROR           0x00000002 /* MIM_LONGERROR */
DECL|macro|ICARDMIDI_OUTLONGDATA
mdefine_line|#define ICARDMIDI_OUTLONGDATA           0x00000004 /* MOM_DONE for MPU OUT buffer */
DECL|macro|ICARDMIDI_INDATA
mdefine_line|#define ICARDMIDI_INDATA                0x00000010 /* MIM_DATA */
DECL|macro|ICARDMIDI_INDATAERROR
mdefine_line|#define ICARDMIDI_INDATAERROR           0x00000020 /* MIM_ERROR */
multiline_comment|/* Declaration for flags in CARDMIDIBUFFERHDR */
multiline_comment|/* Make it the same as MHDR_DONE, MHDR_INQUEUE in mmsystem.h */
DECL|macro|MIDIBUF_DONE
mdefine_line|#define MIDIBUF_DONE                    0x00000001
DECL|macro|MIDIBUF_INQUEUE
mdefine_line|#define MIDIBUF_INQUEUE                 0x00000004
multiline_comment|/* Declaration for msg parameter in midiCallbackFn */
DECL|macro|ICARDMIDI_OUTBUFFEROK
mdefine_line|#define ICARDMIDI_OUTBUFFEROK           0x00000001
DECL|macro|ICARDMIDI_INMIDIOK
mdefine_line|#define ICARDMIDI_INMIDIOK              0x00000002
multiline_comment|/* Declaration for technology in struct midi_caps */
DECL|macro|MT_MIDIPORT
mdefine_line|#define MT_MIDIPORT                     0x00000001&t;/* In original MIDIOUTCAPS structure */
DECL|macro|MT_FMSYNTH
mdefine_line|#define MT_FMSYNTH                      0x00000004&t;/* In original MIDIOUTCAPS structure */
DECL|macro|MT_AWESYNTH
mdefine_line|#define MT_AWESYNTH                     0x00001000
DECL|macro|MT_PCISYNTH
mdefine_line|#define MT_PCISYNTH                     0x00002000
DECL|macro|MT_PCISYNTH64
mdefine_line|#define MT_PCISYNTH64                   0x00004000
DECL|macro|CARDMIDI_AWEMASK
mdefine_line|#define CARDMIDI_AWEMASK                0x0000F000
DECL|enum|LocalErrorCode
r_enum
id|LocalErrorCode
(brace
DECL|enumerator|CTSTATUS_NOTENABLED
id|CTSTATUS_NOTENABLED
op_assign
l_int|0x7000
comma
DECL|enumerator|CTSTATUS_READY
id|CTSTATUS_READY
comma
DECL|enumerator|CTSTATUS_BUSY
id|CTSTATUS_BUSY
comma
DECL|enumerator|CTSTATUS_DATAAVAIL
id|CTSTATUS_DATAAVAIL
comma
DECL|enumerator|CTSTATUS_NODATA
id|CTSTATUS_NODATA
comma
DECL|enumerator|CTSTATUS_NEXT_BYTE
id|CTSTATUS_NEXT_BYTE
)brace
suffix:semicolon
multiline_comment|/* MIDI data block header */
DECL|struct|midi_hdr
r_struct
id|midi_hdr
(brace
DECL|member|reserved
id|u8
op_star
id|reserved
suffix:semicolon
multiline_comment|/* Pointer to original locked data block */
DECL|member|bufferlength
id|u32
id|bufferlength
suffix:semicolon
multiline_comment|/* Length of data in data block */
DECL|member|bytesrecorded
id|u32
id|bytesrecorded
suffix:semicolon
multiline_comment|/* Used for input only */
DECL|member|user
id|u32
id|user
suffix:semicolon
multiline_comment|/* For client&squot;s use */
DECL|member|flags
id|u32
id|flags
suffix:semicolon
multiline_comment|/* Assorted flags (see defines) */
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
multiline_comment|/* Reserved for driver */
DECL|member|data
id|u8
op_star
id|data
suffix:semicolon
multiline_comment|/* Second copy of first pointer */
)brace
suffix:semicolon
multiline_comment|/* Enumeration for SetControl */
r_enum
(brace
DECL|enumerator|MIDIOBJVOLUME
id|MIDIOBJVOLUME
op_assign
l_int|0x1
comma
DECL|enumerator|MIDIQUERYACTIVEINST
id|MIDIQUERYACTIVEINST
)brace
suffix:semicolon
DECL|struct|midi_queue
r_struct
id|midi_queue
(brace
DECL|member|next
r_struct
id|midi_queue
op_star
id|next
suffix:semicolon
DECL|member|qtype
id|u32
id|qtype
suffix:semicolon
multiline_comment|/* 0 = short message, 1 = long data */
DECL|member|length
id|u32
id|length
suffix:semicolon
DECL|member|sizeLeft
id|u32
id|sizeLeft
suffix:semicolon
DECL|member|midibyte
id|u8
op_star
id|midibyte
suffix:semicolon
DECL|member|refdata
r_int
r_int
id|refdata
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|midi_openinfo
r_struct
id|midi_openinfo
(brace
DECL|member|cbsize
id|u32
id|cbsize
suffix:semicolon
DECL|member|flags
id|u32
id|flags
suffix:semicolon
DECL|member|refdata
r_int
r_int
id|refdata
suffix:semicolon
DECL|member|streamid
id|u32
id|streamid
suffix:semicolon
)brace
suffix:semicolon
r_int
id|emu10k1_midi_callback
c_func
(paren
r_int
r_int
comma
r_int
r_int
comma
r_int
r_int
op_star
)paren
suffix:semicolon
macro_line|#endif /* _ICARDMIDI_H */
eof
