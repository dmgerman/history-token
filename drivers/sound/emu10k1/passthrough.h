multiline_comment|/*&n; **********************************************************************&n; *     passthrough.h -- Emu10k1 digital passthrough header file&n; *     Copyright (C) 2001  Juha Yrj&#xfffd;l&#xfffd; &lt;jyrjola@cc.hut.fi&gt;&n; *&n; **********************************************************************&n; *&n; *     Date                 Author          Summary of changes&n; *     ----                 ------          ------------------&n; *     May 15, 2001&t;    Juha Yrj&#xfffd;l&#xfffd;     base code release&n; *&n; **********************************************************************&n; *&n; *     This program is free software; you can redistribute it and/or&n; *     modify it under the terms of the GNU General Public License as&n; *     published by the Free Software Foundation; either version 2 of&n; *     the License, or (at your option) any later version.&n; *&n; *     This program is distributed in the hope that it will be useful,&n; *     but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *     GNU General Public License for more details.&n; *&n; *     You should have received a copy of the GNU General Public&n; *     License along with this program; if not, write to the Free&n; *     Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139,&n; *     USA.&n; *&n; **********************************************************************&n; */
macro_line|#ifndef _PASSTHROUGH_H
DECL|macro|_PASSTHROUGH_H
mdefine_line|#define _PASSTHROUGH_H
macro_line|#include &quot;hwaccess.h&quot;
macro_line|#include &quot;audio.h&quot;
multiline_comment|/* number of 16-bit stereo samples in XTRAM buffer */
DECL|macro|PT_SAMPLES
mdefine_line|#define PT_SAMPLES 0x8000
DECL|macro|PT_BLOCKSAMPLES
mdefine_line|#define PT_BLOCKSAMPLES 0x400
DECL|macro|PT_BLOCKSIZE
mdefine_line|#define PT_BLOCKSIZE (PT_BLOCKSAMPLES*4)
DECL|macro|PT_BLOCKSIZE_LOG2
mdefine_line|#define PT_BLOCKSIZE_LOG2 12
DECL|macro|PT_BLOCKCOUNT
mdefine_line|#define PT_BLOCKCOUNT (PT_SAMPLES/PT_BLOCKSAMPLES)
DECL|macro|PT_INITPTR
mdefine_line|#define PT_INITPTR (PT_SAMPLES/2-1)
DECL|macro|PT_STATE_INACTIVE
mdefine_line|#define PT_STATE_INACTIVE 0
DECL|macro|PT_STATE_ACTIVATED
mdefine_line|#define PT_STATE_ACTIVATED 1
DECL|macro|PT_STATE_PLAYING
mdefine_line|#define PT_STATE_PLAYING 2
multiline_comment|/* passthrough struct */
DECL|struct|pt_data
r_struct
id|pt_data
(brace
DECL|member|selected
DECL|member|state
DECL|member|spcs_to_use
id|u8
id|selected
comma
id|state
comma
id|spcs_to_use
suffix:semicolon
DECL|member|intr_gpr
DECL|member|enable_gpr
DECL|member|pos_gpr
r_int
id|intr_gpr
comma
id|enable_gpr
comma
id|pos_gpr
suffix:semicolon
DECL|member|blocks_played
DECL|member|blocks_copied
DECL|member|old_spcs
id|u32
id|blocks_played
comma
id|blocks_copied
comma
id|old_spcs
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|playptr
DECL|member|copyptr
id|u32
id|playptr
comma
id|copyptr
suffix:semicolon
DECL|member|prepend_size
id|u32
id|prepend_size
suffix:semicolon
DECL|member|buf
id|u8
op_star
id|buf
suffix:semicolon
DECL|member|ac3data
id|u8
id|ac3data
suffix:semicolon
DECL|member|patch_name
DECL|member|intr_gpr_name
DECL|member|enable_gpr_name
DECL|member|pos_gpr_name
r_char
op_star
id|patch_name
comma
op_star
id|intr_gpr_name
comma
op_star
id|enable_gpr_name
comma
op_star
id|pos_gpr_name
suffix:semicolon
DECL|member|wait
id|wait_queue_head_t
id|wait
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
)brace
suffix:semicolon
id|ssize_t
id|emu10k1_pt_write
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|count
)paren
suffix:semicolon
r_void
id|emu10k1_pt_stop
c_func
(paren
r_struct
id|emu10k1_card
op_star
id|card
)paren
suffix:semicolon
r_void
id|emu10k1_pt_waveout_update
c_func
(paren
r_struct
id|emu10k1_wavedevice
op_star
id|wave_dev
)paren
suffix:semicolon
macro_line|#endif /* _PASSTHROUGH_H */
eof
