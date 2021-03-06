multiline_comment|/*&n; **********************************************************************&n; *     sblive_mi.h&n; *     Copyright 1999, 2000 Creative Labs, Inc.&n; *&n; **********************************************************************&n; *&n; *     Date                 Author          Summary of changes&n; *     ----                 ------          ------------------&n; *     October 20, 1999     Bertrand Lee    base code release&n; *     November 2, 1999     Alan Cox        cleaned up&n; *&n; **********************************************************************&n; *&n; *     This program is free software; you can redistribute it and/or&n; *     modify it under the terms of the GNU General Public License as&n; *     published by the Free Software Foundation; either version 2 of&n; *     the License, or (at your option) any later version.&n; *&n; *     This program is distributed in the hope that it will be useful,&n; *     but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *     GNU General Public License for more details.&n; *&n; *     You should have received a copy of the GNU General Public&n; *     License along with this program; if not, write to the Free&n; *     Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139,&n; *     USA.&n; *&n; **********************************************************************&n; */
macro_line|#ifndef _CARDMI_H
DECL|macro|_CARDMI_H
mdefine_line|#define _CARDMI_H
macro_line|#include &quot;icardmid.h&quot;
macro_line|#include &lt;linux/interrupt.h&gt;
r_typedef
r_enum
(brace
DECL|enumerator|STIN_PARSE
id|STIN_PARSE
op_assign
l_int|0
comma
DECL|enumerator|STIN_3BYTE
id|STIN_3BYTE
comma
multiline_comment|/* 0x80, 0x90, 0xA0, 0xB0, 0xE0 */
DECL|enumerator|STIN_3BYTE_KEY
id|STIN_3BYTE_KEY
comma
multiline_comment|/* Byte 1 */
DECL|enumerator|STIN_3BYTE_VEL
id|STIN_3BYTE_VEL
comma
multiline_comment|/* Byte 1 */
DECL|enumerator|STIN_2BYTE
id|STIN_2BYTE
comma
multiline_comment|/* 0xC0, 0xD0 */
DECL|enumerator|STIN_2BYTE_KEY
id|STIN_2BYTE_KEY
comma
multiline_comment|/* Byte 1 */
DECL|enumerator|STIN_SYS_COMMON_2
id|STIN_SYS_COMMON_2
comma
multiline_comment|/* 0xF1, 0xF3  */
DECL|enumerator|STIN_SYS_COMMON_2_KEY
id|STIN_SYS_COMMON_2_KEY
comma
DECL|enumerator|STIN_SYS_COMMON_3
id|STIN_SYS_COMMON_3
comma
multiline_comment|/* 0xF2 */
DECL|enumerator|STIN_SYS_COMMON_3_KEY
id|STIN_SYS_COMMON_3_KEY
comma
DECL|enumerator|STIN_SYS_COMMON_3_VEL
id|STIN_SYS_COMMON_3_VEL
comma
DECL|enumerator|STIN_SYS_EX_NORM
id|STIN_SYS_EX_NORM
comma
multiline_comment|/* 0xF0, Normal mode */
DECL|enumerator|STIN_SYS_REAL
id|STIN_SYS_REAL
DECL|typedef|midi_in_state
)brace
id|midi_in_state
suffix:semicolon
multiline_comment|/* flags for card MIDI in object */
DECL|macro|FLAGS_MIDM_STARTED
mdefine_line|#define FLAGS_MIDM_STARTED          0x00001000      
singleline_comment|// Data has started to come in after Midm Start
DECL|macro|MIDIIN_MAX_BUFFER_SIZE
mdefine_line|#define MIDIIN_MAX_BUFFER_SIZE      200             
singleline_comment|// Definition for struct emu10k1_mpuin
DECL|struct|midi_data
r_struct
id|midi_data
(brace
DECL|member|data
id|u8
id|data
suffix:semicolon
DECL|member|timein
id|u32
id|timein
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|emu10k1_mpuin
r_struct
id|emu10k1_mpuin
(brace
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|firstmidiq
r_struct
id|midi_queue
op_star
id|firstmidiq
suffix:semicolon
DECL|member|lastmidiq
r_struct
id|midi_queue
op_star
id|lastmidiq
suffix:semicolon
DECL|member|qhead
DECL|member|qtail
r_int
id|qhead
comma
id|qtail
suffix:semicolon
DECL|member|midiq
r_struct
id|midi_data
id|midiq
(braket
id|MIDIIN_MAX_BUFFER_SIZE
)braket
suffix:semicolon
DECL|member|tasklet
r_struct
id|tasklet_struct
id|tasklet
suffix:semicolon
DECL|member|openinfo
r_struct
id|midi_openinfo
id|openinfo
suffix:semicolon
multiline_comment|/* For MIDI state machine */
DECL|member|status
id|u8
id|status
suffix:semicolon
multiline_comment|/* For MIDI running status */
DECL|member|fstatus
id|u8
id|fstatus
suffix:semicolon
multiline_comment|/* For 0xFn status only */
DECL|member|curstate
id|midi_in_state
id|curstate
suffix:semicolon
DECL|member|laststate
id|midi_in_state
id|laststate
suffix:semicolon
DECL|member|timestart
id|u32
id|timestart
suffix:semicolon
DECL|member|timein
id|u32
id|timein
suffix:semicolon
DECL|member|data
id|u8
id|data
suffix:semicolon
)brace
suffix:semicolon
r_int
id|emu10k1_mpuin_open
c_func
(paren
r_struct
id|emu10k1_card
op_star
comma
r_struct
id|midi_openinfo
op_star
)paren
suffix:semicolon
r_int
id|emu10k1_mpuin_close
c_func
(paren
r_struct
id|emu10k1_card
op_star
)paren
suffix:semicolon
r_int
id|emu10k1_mpuin_add_buffer
c_func
(paren
r_struct
id|emu10k1_mpuin
op_star
comma
r_struct
id|midi_hdr
op_star
)paren
suffix:semicolon
r_int
id|emu10k1_mpuin_start
c_func
(paren
r_struct
id|emu10k1_card
op_star
)paren
suffix:semicolon
r_int
id|emu10k1_mpuin_stop
c_func
(paren
r_struct
id|emu10k1_card
op_star
)paren
suffix:semicolon
r_int
id|emu10k1_mpuin_reset
c_func
(paren
r_struct
id|emu10k1_card
op_star
)paren
suffix:semicolon
r_int
id|emu10k1_mpuin_irqhandler
c_func
(paren
r_struct
id|emu10k1_card
op_star
)paren
suffix:semicolon
r_void
id|emu10k1_mpuin_bh
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
macro_line|#endif  /* _CARDMI_H */
eof
