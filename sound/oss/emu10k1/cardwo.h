multiline_comment|/*     &n; **********************************************************************&n; *     cardwo.h -- header file for card wave out functions&n; *     Copyright 1999, 2000 Creative Labs, Inc. &n; * &n; ********************************************************************** &n; * &n; *     Date                 Author          Summary of changes &n; *     ----                 ------          ------------------ &n; *     October 20, 1999     Bertrand Lee    base code release &n; * &n; ********************************************************************** &n; * &n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version. &n; * &n; *     This program is distributed in the hope that it will be useful, &n; *     but WITHOUT ANY WARRANTY; without even the implied warranty of &n; *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the &n; *     GNU General Public License for more details. &n; * &n; *     You should have received a copy of the GNU General Public &n; *     License along with this program; if not, write to the Free &n; *     Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, &n; *     USA. &n; * &n; ********************************************************************** &n; */
macro_line|#ifndef _CARDWO_H
DECL|macro|_CARDWO_H
mdefine_line|#define _CARDWO_H
macro_line|#include &quot;icardwav.h&quot;
macro_line|#include &quot;audio.h&quot;
macro_line|#include &quot;voicemgr.h&quot;
macro_line|#include &quot;timer.h&quot;
multiline_comment|/* setting this to other than a power of two may break some applications */
DECL|macro|WAVEOUT_MAXBUFSIZE
mdefine_line|#define WAVEOUT_MAXBUFSIZE&t;MAXBUFSIZE
DECL|macro|WAVEOUT_DEFAULTFRAGLEN
mdefine_line|#define WAVEOUT_DEFAULTFRAGLEN&t;20 /* Time to play a fragment in ms (latency) */
DECL|macro|WAVEOUT_DEFAULTBUFLEN
mdefine_line|#define WAVEOUT_DEFAULTBUFLEN&t;500 /* Time to play the entire buffer in ms */
DECL|macro|WAVEOUT_MINFRAGSHIFT
mdefine_line|#define WAVEOUT_MINFRAGSHIFT&t;6 /* Minimum fragment size in bytes is 2^6 */
DECL|macro|WAVEOUT_MINFRAGS
mdefine_line|#define WAVEOUT_MINFRAGS&t;3 /* _don&squot;t_ go bellow 3, it would break silence filling */
DECL|macro|WAVEOUT_MAXVOICES
mdefine_line|#define WAVEOUT_MAXVOICES&t;6
DECL|struct|waveout_buffer
r_struct
id|waveout_buffer
(brace
DECL|member|ossfragshift
id|u16
id|ossfragshift
suffix:semicolon
DECL|member|numfrags
id|u32
id|numfrags
suffix:semicolon
DECL|member|fragment_size
id|u32
id|fragment_size
suffix:semicolon
multiline_comment|/* in bytes units */
DECL|member|size
id|u32
id|size
suffix:semicolon
multiline_comment|/* in bytes units */
DECL|member|pages
id|u32
id|pages
suffix:semicolon
multiline_comment|/* buffer size in page units*/
DECL|member|silence_pos
id|u32
id|silence_pos
suffix:semicolon
multiline_comment|/* software cursor position (including silence bytes) */
DECL|member|hw_pos
id|u32
id|hw_pos
suffix:semicolon
multiline_comment|/* hardware cursor position */
DECL|member|free_bytes
id|u32
id|free_bytes
suffix:semicolon
multiline_comment|/* free bytes available on the buffer (not including silence bytes) */
DECL|member|fill_silence
id|u8
id|fill_silence
suffix:semicolon
DECL|member|silence_bytes
id|u32
id|silence_bytes
suffix:semicolon
multiline_comment|/* silence bytes on the buffer */
)brace
suffix:semicolon
DECL|struct|woinst
r_struct
id|woinst
(brace
DECL|member|state
id|u8
id|state
suffix:semicolon
DECL|member|num_voices
id|u8
id|num_voices
suffix:semicolon
DECL|member|voice
r_struct
id|emu_voice
id|voice
(braket
id|WAVEOUT_MAXVOICES
)braket
suffix:semicolon
DECL|member|timer
r_struct
id|emu_timer
id|timer
suffix:semicolon
DECL|member|format
r_struct
id|wave_format
id|format
suffix:semicolon
DECL|member|buffer
r_struct
id|waveout_buffer
id|buffer
suffix:semicolon
DECL|member|wait_queue
id|wait_queue_head_t
id|wait_queue
suffix:semicolon
DECL|member|mmapped
id|u8
id|mmapped
suffix:semicolon
DECL|member|total_copied
id|u32
id|total_copied
suffix:semicolon
multiline_comment|/* total number of bytes written() to the buffer (excluding silence) */
DECL|member|total_played
id|u32
id|total_played
suffix:semicolon
multiline_comment|/* total number of bytes played including silence */
DECL|member|blocks
id|u32
id|blocks
suffix:semicolon
DECL|member|device
id|u8
id|device
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
)brace
suffix:semicolon
r_int
id|emu10k1_waveout_open
c_func
(paren
r_struct
id|emu10k1_wavedevice
op_star
)paren
suffix:semicolon
r_void
id|emu10k1_waveout_close
c_func
(paren
r_struct
id|emu10k1_wavedevice
op_star
)paren
suffix:semicolon
r_void
id|emu10k1_waveout_start
c_func
(paren
r_struct
id|emu10k1_wavedevice
op_star
)paren
suffix:semicolon
r_void
id|emu10k1_waveout_stop
c_func
(paren
r_struct
id|emu10k1_wavedevice
op_star
)paren
suffix:semicolon
r_void
id|emu10k1_waveout_getxfersize
c_func
(paren
r_struct
id|woinst
op_star
comma
id|u32
op_star
)paren
suffix:semicolon
r_void
id|emu10k1_waveout_xferdata
c_func
(paren
r_struct
id|woinst
op_star
comma
id|u8
id|__user
op_star
comma
id|u32
op_star
)paren
suffix:semicolon
r_void
id|emu10k1_waveout_fillsilence
c_func
(paren
r_struct
id|woinst
op_star
)paren
suffix:semicolon
r_int
id|emu10k1_waveout_setformat
c_func
(paren
r_struct
id|emu10k1_wavedevice
op_star
comma
r_struct
id|wave_format
op_star
)paren
suffix:semicolon
r_void
id|emu10k1_waveout_update
c_func
(paren
r_struct
id|woinst
op_star
)paren
suffix:semicolon
macro_line|#endif /* _CARDWO_H */
eof
