multiline_comment|/*&n; *  Copyright (c) by Uros Bizjak &lt;uros@kss-loka.si&gt;&n; *                   &n; *  Routines for OPL2/OPL3/OPL4 control&n; *&n; *   This program is free software; you can redistribute it and/or modify &n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
DECL|macro|__NO_VERSION__
mdefine_line|#define __NO_VERSION__
macro_line|#include &lt;sound/opl3.h&gt;
DECL|macro|__SND_OSS_COMPAT__
mdefine_line|#define __SND_OSS_COMPAT__
macro_line|#include &lt;sound/asound_fm.h&gt;
multiline_comment|/*&n; *    There is 18 possible 2 OP voices&n; *      (9 in the left and 9 in the right).&n; *      The first OP is the modulator and 2nd is the carrier.&n; *&n; *      The first three voices in the both sides may be connected&n; *      with another voice to a 4 OP voice. For example voice 0&n; *      can be connected with voice 3. The operators of voice 3 are&n; *      used as operators 3 and 4 of the new 4 OP voice.&n; *      In this case the 2 OP voice number 0 is the &squot;first half&squot; and&n; *      voice 3 is the second.&n; */
multiline_comment|/*&n; *    Register offset table for OPL2/3 voices,&n; *    OPL2 / one OPL3 register array side only&n; */
DECL|variable|snd_opl3_regmap
r_char
id|snd_opl3_regmap
(braket
id|MAX_OPL2_VOICES
)braket
(braket
l_int|4
)braket
op_assign
(brace
multiline_comment|/*&t;  OP1   OP2   OP3   OP4&t;&t;*/
multiline_comment|/*&t; ------------------------&t;*/
(brace
l_int|0x00
comma
l_int|0x03
comma
l_int|0x08
comma
l_int|0x0b
)brace
comma
(brace
l_int|0x01
comma
l_int|0x04
comma
l_int|0x09
comma
l_int|0x0c
)brace
comma
(brace
l_int|0x02
comma
l_int|0x05
comma
l_int|0x0a
comma
l_int|0x0d
)brace
comma
(brace
l_int|0x08
comma
l_int|0x0b
comma
l_int|0x00
comma
l_int|0x00
)brace
comma
(brace
l_int|0x09
comma
l_int|0x0c
comma
l_int|0x00
comma
l_int|0x00
)brace
comma
(brace
l_int|0x0a
comma
l_int|0x0d
comma
l_int|0x00
comma
l_int|0x00
)brace
comma
(brace
l_int|0x10
comma
l_int|0x13
comma
l_int|0x00
comma
l_int|0x00
)brace
comma
multiline_comment|/* used by percussive voices */
(brace
l_int|0x11
comma
l_int|0x14
comma
l_int|0x00
comma
l_int|0x00
)brace
comma
multiline_comment|/* if the percussive mode */
(brace
l_int|0x12
comma
l_int|0x15
comma
l_int|0x00
comma
l_int|0x00
)brace
multiline_comment|/* is selected (only left reg block) */
)brace
suffix:semicolon
multiline_comment|/*&n; * prototypes&n; */
r_static
r_int
id|snd_opl3_play_note
c_func
(paren
id|opl3_t
op_star
id|opl3
comma
id|snd_dm_fm_note_t
op_star
id|note
)paren
suffix:semicolon
r_static
r_int
id|snd_opl3_set_voice
c_func
(paren
id|opl3_t
op_star
id|opl3
comma
id|snd_dm_fm_voice_t
op_star
id|voice
)paren
suffix:semicolon
r_static
r_int
id|snd_opl3_set_params
c_func
(paren
id|opl3_t
op_star
id|opl3
comma
id|snd_dm_fm_params_t
op_star
id|params
)paren
suffix:semicolon
r_static
r_int
id|snd_opl3_set_mode
c_func
(paren
id|opl3_t
op_star
id|opl3
comma
r_int
id|mode
)paren
suffix:semicolon
r_static
r_int
id|snd_opl3_set_connection
c_func
(paren
id|opl3_t
op_star
id|opl3
comma
r_int
id|connection
)paren
suffix:semicolon
multiline_comment|/* ------------------------------ */
multiline_comment|/*&n; * open the device exclusively&n; */
DECL|function|snd_opl3_open
r_int
id|snd_opl3_open
c_func
(paren
id|snd_hwdep_t
op_star
id|hw
comma
r_struct
id|file
op_star
id|file
)paren
(brace
id|opl3_t
op_star
id|opl3
op_assign
id|snd_magic_cast
c_func
(paren
id|opl3_t
comma
id|hw-&gt;private_data
comma
r_return
op_minus
id|ENXIO
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|opl3-&gt;access_mutex
)paren
suffix:semicolon
r_if
c_cond
(paren
id|opl3-&gt;used
)paren
(brace
id|up
c_func
(paren
op_amp
id|opl3-&gt;access_mutex
)paren
suffix:semicolon
r_return
op_minus
id|EAGAIN
suffix:semicolon
)brace
id|opl3-&gt;used
op_increment
suffix:semicolon
id|up
c_func
(paren
op_amp
id|opl3-&gt;access_mutex
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * ioctl for hwdep device:&n; */
DECL|function|snd_opl3_ioctl
r_int
id|snd_opl3_ioctl
c_func
(paren
id|snd_hwdep_t
op_star
id|hw
comma
r_struct
id|file
op_star
id|file
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
id|opl3_t
op_star
id|opl3
op_assign
id|snd_magic_cast
c_func
(paren
id|opl3_t
comma
id|hw-&gt;private_data
comma
r_return
op_minus
id|ENXIO
)paren
suffix:semicolon
id|snd_assert
c_func
(paren
id|opl3
op_ne
l_int|NULL
comma
r_return
op_minus
id|EINVAL
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
multiline_comment|/* get information */
r_case
id|SNDRV_DM_FM_IOCTL_INFO
suffix:colon
(brace
id|snd_dm_fm_info_t
id|info
suffix:semicolon
id|info.fm_mode
op_assign
id|opl3-&gt;fm_mode
suffix:semicolon
id|info.rhythm
op_assign
id|opl3-&gt;rhythm
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
id|snd_dm_fm_info_t
op_star
)paren
id|arg
comma
op_amp
id|info
comma
r_sizeof
(paren
id|snd_dm_fm_info_t
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|SNDRV_DM_FM_IOCTL_RESET
suffix:colon
macro_line|#ifdef CONFIG_SND_OSSEMUL
r_case
id|SNDRV_DM_FM_OSS_IOCTL_RESET
suffix:colon
macro_line|#endif
id|snd_opl3_reset
c_func
(paren
id|opl3
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|SNDRV_DM_FM_IOCTL_PLAY_NOTE
suffix:colon
macro_line|#ifdef CONFIG_SND_OSSEMUL
r_case
id|SNDRV_DM_FM_OSS_IOCTL_PLAY_NOTE
suffix:colon
macro_line|#endif
(brace
id|snd_dm_fm_note_t
id|note
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|note
comma
(paren
id|snd_dm_fm_note_t
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|snd_dm_fm_note_t
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
id|snd_opl3_play_note
c_func
(paren
id|opl3
comma
op_amp
id|note
)paren
suffix:semicolon
)brace
r_case
id|SNDRV_DM_FM_IOCTL_SET_VOICE
suffix:colon
macro_line|#ifdef CONFIG_SND_OSSEMUL
r_case
id|SNDRV_DM_FM_OSS_IOCTL_SET_VOICE
suffix:colon
macro_line|#endif
(brace
id|snd_dm_fm_voice_t
id|voice
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|voice
comma
(paren
id|snd_dm_fm_voice_t
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|snd_dm_fm_voice_t
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
id|snd_opl3_set_voice
c_func
(paren
id|opl3
comma
op_amp
id|voice
)paren
suffix:semicolon
)brace
r_case
id|SNDRV_DM_FM_IOCTL_SET_PARAMS
suffix:colon
macro_line|#ifdef CONFIG_SND_OSSEMUL
r_case
id|SNDRV_DM_FM_OSS_IOCTL_SET_PARAMS
suffix:colon
macro_line|#endif
(brace
id|snd_dm_fm_params_t
id|params
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|params
comma
(paren
id|snd_dm_fm_params_t
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|snd_dm_fm_params_t
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
id|snd_opl3_set_params
c_func
(paren
id|opl3
comma
op_amp
id|params
)paren
suffix:semicolon
)brace
r_case
id|SNDRV_DM_FM_IOCTL_SET_MODE
suffix:colon
macro_line|#ifdef CONFIG_SND_OSSEMUL
r_case
id|SNDRV_DM_FM_OSS_IOCTL_SET_MODE
suffix:colon
macro_line|#endif
r_return
id|snd_opl3_set_mode
c_func
(paren
id|opl3
comma
(paren
r_int
)paren
id|arg
)paren
suffix:semicolon
r_case
id|SNDRV_DM_FM_IOCTL_SET_CONNECTION
suffix:colon
macro_line|#ifdef CONFIG_SND_OSSEMUL
r_case
id|SNDRV_DM_FM_OSS_IOCTL_SET_OPL
suffix:colon
macro_line|#endif
r_return
id|snd_opl3_set_connection
c_func
(paren
id|opl3
comma
(paren
r_int
)paren
id|arg
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SND_DEBUG
r_default
suffix:colon
id|snd_printk
c_func
(paren
l_string|&quot;unknown IOCTL: 0x%x&bslash;n&quot;
comma
id|cmd
)paren
suffix:semicolon
macro_line|#endif
)brace
r_return
op_minus
id|ENOTTY
suffix:semicolon
)brace
multiline_comment|/*&n; * close the device&n; */
DECL|function|snd_opl3_release
r_int
id|snd_opl3_release
c_func
(paren
id|snd_hwdep_t
op_star
id|hw
comma
r_struct
id|file
op_star
id|file
)paren
(brace
id|opl3_t
op_star
id|opl3
op_assign
id|snd_magic_cast
c_func
(paren
id|opl3_t
comma
id|hw-&gt;private_data
comma
r_return
op_minus
id|ENXIO
)paren
suffix:semicolon
id|snd_opl3_reset
c_func
(paren
id|opl3
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|opl3-&gt;access_mutex
)paren
suffix:semicolon
id|opl3-&gt;used
op_decrement
suffix:semicolon
id|up
c_func
(paren
op_amp
id|opl3-&gt;access_mutex
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* ------------------------------ */
DECL|function|snd_opl3_reset
r_void
id|snd_opl3_reset
c_func
(paren
id|opl3_t
op_star
id|opl3
)paren
(brace
r_int
r_int
id|opl3_reg
suffix:semicolon
r_int
r_int
id|reg_side
suffix:semicolon
r_int
r_char
id|voice_offset
suffix:semicolon
r_int
id|max_voices
comma
id|i
suffix:semicolon
id|max_voices
op_assign
(paren
id|opl3-&gt;hardware
OL
id|OPL3_HW_OPL3
)paren
ques
c_cond
id|MAX_OPL2_VOICES
suffix:colon
id|MAX_OPL3_VOICES
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|max_voices
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/* Get register array side and offset of voice */
r_if
c_cond
(paren
id|i
OL
id|MAX_OPL2_VOICES
)paren
(brace
multiline_comment|/* Left register block for voices 0 .. 8 */
id|reg_side
op_assign
id|OPL3_LEFT
suffix:semicolon
id|voice_offset
op_assign
id|i
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Right register block for voices 9 .. 17 */
id|reg_side
op_assign
id|OPL3_RIGHT
suffix:semicolon
id|voice_offset
op_assign
id|i
op_minus
id|MAX_OPL2_VOICES
suffix:semicolon
)brace
id|opl3_reg
op_assign
id|reg_side
op_or
(paren
id|OPL3_REG_KSL_LEVEL
op_plus
id|snd_opl3_regmap
(braket
id|voice_offset
)braket
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|opl3
op_member_access_from_pointer
id|command
c_func
(paren
id|opl3
comma
id|opl3_reg
comma
id|OPL3_TOTAL_LEVEL_MASK
)paren
suffix:semicolon
multiline_comment|/* Operator 1 volume */
id|opl3_reg
op_assign
id|reg_side
op_or
(paren
id|OPL3_REG_KSL_LEVEL
op_plus
id|snd_opl3_regmap
(braket
id|voice_offset
)braket
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|opl3
op_member_access_from_pointer
id|command
c_func
(paren
id|opl3
comma
id|opl3_reg
comma
id|OPL3_TOTAL_LEVEL_MASK
)paren
suffix:semicolon
multiline_comment|/* Operator 2 volume */
id|opl3_reg
op_assign
id|reg_side
op_or
(paren
id|OPL3_REG_KEYON_BLOCK
op_plus
id|voice_offset
)paren
suffix:semicolon
id|opl3
op_member_access_from_pointer
id|command
c_func
(paren
id|opl3
comma
id|opl3_reg
comma
l_int|0x00
)paren
suffix:semicolon
multiline_comment|/* Note off */
)brace
r_if
c_cond
(paren
id|opl3-&gt;hardware
op_ge
id|OPL3_HW_OPL3
)paren
id|opl3
op_member_access_from_pointer
id|command
c_func
(paren
id|opl3
comma
id|OPL3_RIGHT
op_or
id|OPL3_REG_MODE
comma
l_int|0x00
)paren
suffix:semicolon
multiline_comment|/* Enter OPL2 mode */
id|opl3-&gt;max_voices
op_assign
id|MAX_OPL2_VOICES
suffix:semicolon
id|opl3-&gt;fm_mode
op_assign
id|SNDRV_DM_FM_MODE_OPL2
suffix:semicolon
id|opl3
op_member_access_from_pointer
id|command
c_func
(paren
id|opl3
comma
id|OPL3_LEFT
op_or
id|OPL3_REG_TEST
comma
id|OPL3_ENABLE_WAVE_SELECT
)paren
suffix:semicolon
id|opl3
op_member_access_from_pointer
id|command
c_func
(paren
id|opl3
comma
id|OPL3_LEFT
op_or
id|OPL3_REG_PERCUSSION
comma
l_int|0x00
)paren
suffix:semicolon
multiline_comment|/* Melodic mode */
id|opl3-&gt;rhythm
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|snd_opl3_play_note
r_static
r_int
id|snd_opl3_play_note
c_func
(paren
id|opl3_t
op_star
id|opl3
comma
id|snd_dm_fm_note_t
op_star
id|note
)paren
(brace
r_int
r_int
id|reg_side
suffix:semicolon
r_int
r_char
id|voice_offset
suffix:semicolon
r_int
r_int
id|opl3_reg
suffix:semicolon
r_int
r_char
id|reg_val
suffix:semicolon
multiline_comment|/* Voices 0 -  8 in OPL2 mode */
multiline_comment|/* Voices 0 - 17 in OPL3 mode */
r_if
c_cond
(paren
id|note-&gt;voice
op_ge
(paren
(paren
id|opl3-&gt;fm_mode
op_eq
id|SNDRV_DM_FM_MODE_OPL3
)paren
ques
c_cond
id|MAX_OPL3_VOICES
suffix:colon
id|MAX_OPL2_VOICES
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* Get register array side and offset of voice */
r_if
c_cond
(paren
id|note-&gt;voice
OL
id|MAX_OPL2_VOICES
)paren
(brace
multiline_comment|/* Left register block for voices 0 .. 8 */
id|reg_side
op_assign
id|OPL3_LEFT
suffix:semicolon
id|voice_offset
op_assign
id|note-&gt;voice
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Right register block for voices 9 .. 17 */
id|reg_side
op_assign
id|OPL3_RIGHT
suffix:semicolon
id|voice_offset
op_assign
id|note-&gt;voice
op_minus
id|MAX_OPL2_VOICES
suffix:semicolon
)brace
multiline_comment|/* Set lower 8 bits of note frequency */
id|reg_val
op_assign
(paren
r_int
r_char
)paren
id|note-&gt;fnum
suffix:semicolon
id|opl3_reg
op_assign
id|reg_side
op_or
(paren
id|OPL3_REG_FNUM_LOW
op_plus
id|voice_offset
)paren
suffix:semicolon
id|opl3
op_member_access_from_pointer
id|command
c_func
(paren
id|opl3
comma
id|opl3_reg
comma
id|reg_val
)paren
suffix:semicolon
id|reg_val
op_assign
l_int|0x00
suffix:semicolon
multiline_comment|/* Set output sound flag */
r_if
c_cond
(paren
id|note-&gt;key_on
)paren
id|reg_val
op_or_assign
id|OPL3_KEYON_BIT
suffix:semicolon
multiline_comment|/* Set octave */
id|reg_val
op_or_assign
(paren
id|note-&gt;octave
op_lshift
l_int|2
)paren
op_amp
id|OPL3_BLOCKNUM_MASK
suffix:semicolon
multiline_comment|/* Set higher 2 bits of note frequency */
id|reg_val
op_or_assign
(paren
r_int
r_char
)paren
(paren
id|note-&gt;fnum
op_rshift
l_int|8
)paren
op_amp
id|OPL3_FNUM_HIGH_MASK
suffix:semicolon
multiline_comment|/* Set OPL3 KEYON_BLOCK register of requested voice */
id|opl3_reg
op_assign
id|reg_side
op_or
(paren
id|OPL3_REG_KEYON_BLOCK
op_plus
id|voice_offset
)paren
suffix:semicolon
id|opl3
op_member_access_from_pointer
id|command
c_func
(paren
id|opl3
comma
id|opl3_reg
comma
id|reg_val
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_opl3_set_voice
r_static
r_int
id|snd_opl3_set_voice
c_func
(paren
id|opl3_t
op_star
id|opl3
comma
id|snd_dm_fm_voice_t
op_star
id|voice
)paren
(brace
r_int
r_int
id|reg_side
suffix:semicolon
r_int
r_char
id|op_offset
suffix:semicolon
r_int
r_char
id|voice_offset
suffix:semicolon
r_int
r_int
id|opl3_reg
suffix:semicolon
r_int
r_char
id|reg_val
suffix:semicolon
multiline_comment|/* Only operators 1 and 2 */
r_if
c_cond
(paren
id|voice-&gt;op
OG
l_int|1
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* Voices 0 -  8 in OPL2 mode */
multiline_comment|/* Voices 0 - 17 in OPL3 mode */
r_if
c_cond
(paren
id|voice-&gt;voice
op_ge
(paren
(paren
id|opl3-&gt;fm_mode
op_eq
id|SNDRV_DM_FM_MODE_OPL3
)paren
ques
c_cond
id|MAX_OPL3_VOICES
suffix:colon
id|MAX_OPL2_VOICES
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* Get register array side and offset of voice */
r_if
c_cond
(paren
id|voice-&gt;voice
OL
id|MAX_OPL2_VOICES
)paren
(brace
multiline_comment|/* Left register block for voices 0 .. 8 */
id|reg_side
op_assign
id|OPL3_LEFT
suffix:semicolon
id|voice_offset
op_assign
id|voice-&gt;voice
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Right register block for voices 9 .. 17 */
id|reg_side
op_assign
id|OPL3_RIGHT
suffix:semicolon
id|voice_offset
op_assign
id|voice-&gt;voice
op_minus
id|MAX_OPL2_VOICES
suffix:semicolon
)brace
multiline_comment|/* Get register offset of operator */
id|op_offset
op_assign
id|snd_opl3_regmap
(braket
id|voice_offset
)braket
(braket
id|voice-&gt;op
)braket
suffix:semicolon
id|reg_val
op_assign
l_int|0x00
suffix:semicolon
multiline_comment|/* Set amplitude modulation (tremolo) effect */
r_if
c_cond
(paren
id|voice-&gt;am
)paren
id|reg_val
op_or_assign
id|OPL3_TREMOLO_ON
suffix:semicolon
multiline_comment|/* Set vibrato effect */
r_if
c_cond
(paren
id|voice-&gt;vibrato
)paren
id|reg_val
op_or_assign
id|OPL3_VIBRATO_ON
suffix:semicolon
multiline_comment|/* Set sustaining sound phase */
r_if
c_cond
(paren
id|voice-&gt;do_sustain
)paren
id|reg_val
op_or_assign
id|OPL3_SUSTAIN_ON
suffix:semicolon
multiline_comment|/* Set keyboard scaling bit */
r_if
c_cond
(paren
id|voice-&gt;kbd_scale
)paren
id|reg_val
op_or_assign
id|OPL3_KSR
suffix:semicolon
multiline_comment|/* Set harmonic or frequency multiplier */
id|reg_val
op_or_assign
id|voice-&gt;harmonic
op_amp
id|OPL3_MULTIPLE_MASK
suffix:semicolon
multiline_comment|/* Set OPL3 AM_VIB register of requested voice/operator */
id|opl3_reg
op_assign
id|reg_side
op_or
(paren
id|OPL3_REG_AM_VIB
op_plus
id|op_offset
)paren
suffix:semicolon
id|opl3
op_member_access_from_pointer
id|command
c_func
(paren
id|opl3
comma
id|opl3_reg
comma
id|reg_val
)paren
suffix:semicolon
multiline_comment|/* Set decreasing volume of higher notes */
id|reg_val
op_assign
(paren
id|voice-&gt;scale_level
op_lshift
l_int|6
)paren
op_amp
id|OPL3_KSL_MASK
suffix:semicolon
multiline_comment|/* Set output volume */
id|reg_val
op_or_assign
op_complement
id|voice-&gt;volume
op_amp
id|OPL3_TOTAL_LEVEL_MASK
suffix:semicolon
multiline_comment|/* Set OPL3 KSL_LEVEL register of requested voice/operator */
id|opl3_reg
op_assign
id|reg_side
op_or
(paren
id|OPL3_REG_KSL_LEVEL
op_plus
id|op_offset
)paren
suffix:semicolon
id|opl3
op_member_access_from_pointer
id|command
c_func
(paren
id|opl3
comma
id|opl3_reg
comma
id|reg_val
)paren
suffix:semicolon
multiline_comment|/* Set attack phase level */
id|reg_val
op_assign
(paren
id|voice-&gt;attack
op_lshift
l_int|4
)paren
op_amp
id|OPL3_ATTACK_MASK
suffix:semicolon
multiline_comment|/* Set decay phase level */
id|reg_val
op_or_assign
id|voice-&gt;decay
op_amp
id|OPL3_DECAY_MASK
suffix:semicolon
multiline_comment|/* Set OPL3 ATTACK_DECAY register of requested voice/operator */
id|opl3_reg
op_assign
id|reg_side
op_or
(paren
id|OPL3_REG_ATTACK_DECAY
op_plus
id|op_offset
)paren
suffix:semicolon
id|opl3
op_member_access_from_pointer
id|command
c_func
(paren
id|opl3
comma
id|opl3_reg
comma
id|reg_val
)paren
suffix:semicolon
multiline_comment|/* Set sustain phase level */
id|reg_val
op_assign
(paren
id|voice-&gt;sustain
op_lshift
l_int|4
)paren
op_amp
id|OPL3_SUSTAIN_MASK
suffix:semicolon
multiline_comment|/* Set release phase level */
id|reg_val
op_or_assign
id|voice-&gt;release
op_amp
id|OPL3_RELEASE_MASK
suffix:semicolon
multiline_comment|/* Set OPL3 SUSTAIN_RELEASE register of requested voice/operator */
id|opl3_reg
op_assign
id|reg_side
op_or
(paren
id|OPL3_REG_SUSTAIN_RELEASE
op_plus
id|op_offset
)paren
suffix:semicolon
id|opl3
op_member_access_from_pointer
id|command
c_func
(paren
id|opl3
comma
id|opl3_reg
comma
id|reg_val
)paren
suffix:semicolon
multiline_comment|/* Set inter-operator feedback */
id|reg_val
op_assign
(paren
id|voice-&gt;feedback
op_lshift
l_int|1
)paren
op_amp
id|OPL3_FEEDBACK_MASK
suffix:semicolon
multiline_comment|/* Set inter-operator connection */
r_if
c_cond
(paren
id|voice-&gt;connection
)paren
id|reg_val
op_or_assign
id|OPL3_CONNECTION_BIT
suffix:semicolon
multiline_comment|/* OPL-3 only */
r_if
c_cond
(paren
id|opl3-&gt;fm_mode
op_eq
id|SNDRV_DM_FM_MODE_OPL3
)paren
(brace
r_if
c_cond
(paren
id|voice-&gt;left
)paren
id|reg_val
op_or_assign
id|OPL3_VOICE_TO_LEFT
suffix:semicolon
r_if
c_cond
(paren
id|voice-&gt;right
)paren
id|reg_val
op_or_assign
id|OPL3_VOICE_TO_RIGHT
suffix:semicolon
)brace
multiline_comment|/* Feedback/connection bits are applicable to voice */
id|opl3_reg
op_assign
id|reg_side
op_or
(paren
id|OPL3_REG_FEEDBACK_CONNECTION
op_plus
id|voice_offset
)paren
suffix:semicolon
id|opl3
op_member_access_from_pointer
id|command
c_func
(paren
id|opl3
comma
id|opl3_reg
comma
id|reg_val
)paren
suffix:semicolon
multiline_comment|/* Select waveform */
id|reg_val
op_assign
id|voice-&gt;waveform
op_amp
id|OPL3_WAVE_SELECT_MASK
suffix:semicolon
id|opl3_reg
op_assign
id|reg_side
op_or
(paren
id|OPL3_REG_WAVE_SELECT
op_plus
id|op_offset
)paren
suffix:semicolon
id|opl3
op_member_access_from_pointer
id|command
c_func
(paren
id|opl3
comma
id|opl3_reg
comma
id|reg_val
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_opl3_set_params
r_static
r_int
id|snd_opl3_set_params
c_func
(paren
id|opl3_t
op_star
id|opl3
comma
id|snd_dm_fm_params_t
op_star
id|params
)paren
(brace
r_int
r_char
id|reg_val
suffix:semicolon
id|reg_val
op_assign
l_int|0x00
suffix:semicolon
multiline_comment|/* Set keyboard split method */
r_if
c_cond
(paren
id|params-&gt;kbd_split
)paren
id|reg_val
op_or_assign
id|OPL3_KEYBOARD_SPLIT
suffix:semicolon
id|opl3
op_member_access_from_pointer
id|command
c_func
(paren
id|opl3
comma
id|OPL3_LEFT
op_or
id|OPL3_REG_KBD_SPLIT
comma
id|reg_val
)paren
suffix:semicolon
id|reg_val
op_assign
l_int|0x00
suffix:semicolon
multiline_comment|/* Set amplitude modulation (tremolo) depth */
r_if
c_cond
(paren
id|params-&gt;am_depth
)paren
id|reg_val
op_or_assign
id|OPL3_TREMOLO_DEPTH
suffix:semicolon
multiline_comment|/* Set vibrato depth */
r_if
c_cond
(paren
id|params-&gt;vib_depth
)paren
id|reg_val
op_or_assign
id|OPL3_VIBRATO_DEPTH
suffix:semicolon
multiline_comment|/* Set percussion mode */
r_if
c_cond
(paren
id|params-&gt;rhythm
)paren
(brace
id|reg_val
op_or_assign
id|OPL3_PERCUSSION_ENABLE
suffix:semicolon
id|opl3-&gt;rhythm
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|opl3-&gt;rhythm
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Play percussion instruments */
r_if
c_cond
(paren
id|params-&gt;bass
)paren
id|reg_val
op_or_assign
id|OPL3_BASSDRUM_ON
suffix:semicolon
r_if
c_cond
(paren
id|params-&gt;snare
)paren
id|reg_val
op_or_assign
id|OPL3_SNAREDRUM_ON
suffix:semicolon
r_if
c_cond
(paren
id|params-&gt;tomtom
)paren
id|reg_val
op_or_assign
id|OPL3_TOMTOM_ON
suffix:semicolon
r_if
c_cond
(paren
id|params-&gt;cymbal
)paren
id|reg_val
op_or_assign
id|OPL3_CYMBAL_ON
suffix:semicolon
r_if
c_cond
(paren
id|params-&gt;hihat
)paren
id|reg_val
op_or_assign
id|OPL3_HIHAT_ON
suffix:semicolon
id|opl3
op_member_access_from_pointer
id|command
c_func
(paren
id|opl3
comma
id|OPL3_LEFT
op_or
id|OPL3_REG_PERCUSSION
comma
id|reg_val
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_opl3_set_mode
r_static
r_int
id|snd_opl3_set_mode
c_func
(paren
id|opl3_t
op_star
id|opl3
comma
r_int
id|mode
)paren
(brace
r_if
c_cond
(paren
(paren
id|mode
op_eq
id|SNDRV_DM_FM_MODE_OPL3
)paren
op_logical_and
(paren
id|opl3-&gt;hardware
OL
id|OPL3_HW_OPL3
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|mode
op_eq
id|SNDRV_DM_FM_MODE_OPL3
)paren
(brace
id|opl3
op_member_access_from_pointer
id|command
c_func
(paren
id|opl3
comma
id|OPL3_RIGHT
op_or
id|OPL3_REG_MODE
comma
id|OPL3_OPL3_ENABLE
)paren
suffix:semicolon
multiline_comment|/* Enter OPL3 mode */
id|opl3-&gt;fm_mode
op_assign
id|SNDRV_DM_FM_MODE_OPL3
suffix:semicolon
id|opl3
op_member_access_from_pointer
id|command
c_func
(paren
id|opl3
comma
id|OPL3_RIGHT
op_or
id|OPL3_REG_CONNECTION_SELECT
comma
l_int|0x00
)paren
suffix:semicolon
multiline_comment|/* Clear 4-op connections */
)brace
r_else
(brace
id|opl3
op_member_access_from_pointer
id|command
c_func
(paren
id|opl3
comma
id|OPL3_RIGHT
op_or
id|OPL3_REG_MODE
comma
l_int|0x00
)paren
suffix:semicolon
multiline_comment|/* Enter OPL2 mode */
id|opl3-&gt;fm_mode
op_assign
id|SNDRV_DM_FM_MODE_OPL2
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_opl3_set_connection
r_static
r_int
id|snd_opl3_set_connection
c_func
(paren
id|opl3_t
op_star
id|opl3
comma
r_int
id|connection
)paren
(brace
r_int
r_char
id|reg_val
suffix:semicolon
multiline_comment|/* OPL-3 only */
r_if
c_cond
(paren
id|opl3-&gt;fm_mode
op_ne
id|SNDRV_DM_FM_MODE_OPL3
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|reg_val
op_assign
id|connection
op_amp
(paren
id|OPL3_RIGHT_4OP_0
op_or
id|OPL3_RIGHT_4OP_1
op_or
id|OPL3_RIGHT_4OP_2
op_or
id|OPL3_LEFT_4OP_0
op_or
id|OPL3_LEFT_4OP_1
op_or
id|OPL3_LEFT_4OP_2
)paren
suffix:semicolon
multiline_comment|/* Set 4-op connections */
id|opl3
op_member_access_from_pointer
id|command
c_func
(paren
id|opl3
comma
id|OPL3_RIGHT
op_or
id|OPL3_REG_CONNECTION_SELECT
comma
id|reg_val
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof