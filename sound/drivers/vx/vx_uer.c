multiline_comment|/*&n; * Driver for Digigram VX soundcards&n; *&n; * IEC958 stuff&n; *&n; * Copyright (c) 2002 by Takashi Iwai &lt;tiwai@suse.de&gt;&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &lt;sound/vx_core.h&gt;
macro_line|#include &quot;vx_cmd.h&quot;
multiline_comment|/*&n; * vx_modify_board_clock - tell the board that its clock has been modified&n; * @sync: DSP needs to resynchronize its FIFO&n; */
DECL|function|vx_modify_board_clock
r_static
r_int
id|vx_modify_board_clock
c_func
(paren
id|vx_core_t
op_star
id|chip
comma
r_int
id|sync
)paren
(brace
r_struct
id|vx_rmh
id|rmh
suffix:semicolon
id|vx_init_rmh
c_func
(paren
op_amp
id|rmh
comma
id|CMD_MODIFY_CLOCK
)paren
suffix:semicolon
multiline_comment|/* Ask the DSP to resynchronize its FIFO. */
r_if
c_cond
(paren
id|sync
)paren
id|rmh.Cmd
(braket
l_int|0
)braket
op_or_assign
id|CMD_MODIFY_CLOCK_S_BIT
suffix:semicolon
r_return
id|vx_send_msg
c_func
(paren
id|chip
comma
op_amp
id|rmh
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * vx_modify_board_inputs - resync audio inputs&n; */
DECL|function|vx_modify_board_inputs
r_static
r_int
id|vx_modify_board_inputs
c_func
(paren
id|vx_core_t
op_star
id|chip
)paren
(brace
r_struct
id|vx_rmh
id|rmh
suffix:semicolon
id|vx_init_rmh
c_func
(paren
op_amp
id|rmh
comma
id|CMD_RESYNC_AUDIO_INPUTS
)paren
suffix:semicolon
id|rmh.Cmd
(braket
l_int|0
)braket
op_or_assign
l_int|1
op_lshift
l_int|0
suffix:semicolon
multiline_comment|/* reference: AUDIO 0 */
r_return
id|vx_send_msg
c_func
(paren
id|chip
comma
op_amp
id|rmh
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * vx_read_one_cbit - read one bit from UER config&n; * @index: the bit index&n; * returns 0 or 1.&n; */
DECL|function|vx_read_one_cbit
r_static
r_int
id|vx_read_one_cbit
c_func
(paren
id|vx_core_t
op_star
id|chip
comma
r_int
id|index
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|val
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|chip-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|chip-&gt;type
op_ge
id|VX_TYPE_VXPOCKET
)paren
(brace
id|vx_outb
c_func
(paren
id|chip
comma
id|CSUER
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/* read */
id|vx_outb
c_func
(paren
id|chip
comma
id|RUER
comma
id|index
op_amp
id|XX_UER_CBITS_OFFSET_MASK
)paren
suffix:semicolon
id|val
op_assign
(paren
id|vx_inb
c_func
(paren
id|chip
comma
id|RUER
)paren
op_rshift
l_int|7
)paren
op_amp
l_int|0x01
suffix:semicolon
)brace
r_else
(brace
id|vx_outl
c_func
(paren
id|chip
comma
id|CSUER
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/* read */
id|vx_outl
c_func
(paren
id|chip
comma
id|RUER
comma
id|index
op_amp
id|XX_UER_CBITS_OFFSET_MASK
)paren
suffix:semicolon
id|val
op_assign
(paren
id|vx_inl
c_func
(paren
id|chip
comma
id|RUER
)paren
op_rshift
l_int|7
)paren
op_amp
l_int|0x01
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|chip-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
multiline_comment|/*&n; * vx_write_one_cbit - write one bit to UER config&n; * @index: the bit index&n; * @val: bit value, 0 or 1&n; */
DECL|function|vx_write_one_cbit
r_static
r_void
id|vx_write_one_cbit
c_func
(paren
id|vx_core_t
op_star
id|chip
comma
r_int
id|index
comma
r_int
id|val
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|val
op_assign
op_logical_neg
op_logical_neg
id|val
suffix:semicolon
multiline_comment|/* 0 or 1 */
id|spin_lock_irqsave
c_func
(paren
op_amp
id|chip-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vx_is_pcmcia
c_func
(paren
id|chip
)paren
)paren
(brace
id|vx_outb
c_func
(paren
id|chip
comma
id|CSUER
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* write */
id|vx_outb
c_func
(paren
id|chip
comma
id|RUER
comma
(paren
id|val
op_lshift
l_int|7
)paren
op_or
(paren
id|index
op_amp
id|XX_UER_CBITS_OFFSET_MASK
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|vx_outl
c_func
(paren
id|chip
comma
id|CSUER
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* write */
id|vx_outl
c_func
(paren
id|chip
comma
id|RUER
comma
(paren
id|val
op_lshift
l_int|7
)paren
op_or
(paren
id|index
op_amp
id|XX_UER_CBITS_OFFSET_MASK
)paren
)paren
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|chip-&gt;lock
comma
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * vx_read_uer_status - read the current UER status&n; * @mode: pointer to store the UER mode, VX_UER_MODE_XXX&n; *&n; * returns the frequency of UER, or 0 if not sync,&n; * or a negative error code.&n; */
DECL|function|vx_read_uer_status
r_static
r_int
id|vx_read_uer_status
c_func
(paren
id|vx_core_t
op_star
id|chip
comma
r_int
op_star
id|mode
)paren
(brace
r_int
id|val
comma
id|freq
suffix:semicolon
multiline_comment|/* Default values */
id|freq
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Read UER status */
r_if
c_cond
(paren
id|vx_is_pcmcia
c_func
(paren
id|chip
)paren
)paren
id|val
op_assign
id|vx_inb
c_func
(paren
id|chip
comma
id|CSUER
)paren
suffix:semicolon
r_else
id|val
op_assign
id|vx_inl
c_func
(paren
id|chip
comma
id|CSUER
)paren
suffix:semicolon
r_if
c_cond
(paren
id|val
OL
l_int|0
)paren
r_return
id|val
suffix:semicolon
multiline_comment|/* If clock is present, read frequency */
r_if
c_cond
(paren
id|val
op_amp
id|VX_SUER_CLOCK_PRESENT_MASK
)paren
(brace
r_switch
c_cond
(paren
id|val
op_amp
id|VX_SUER_FREQ_MASK
)paren
(brace
r_case
id|VX_SUER_FREQ_32KHz_MASK
suffix:colon
id|freq
op_assign
l_int|32000
suffix:semicolon
r_break
suffix:semicolon
r_case
id|VX_SUER_FREQ_44KHz_MASK
suffix:colon
id|freq
op_assign
l_int|44100
suffix:semicolon
r_break
suffix:semicolon
r_case
id|VX_SUER_FREQ_48KHz_MASK
suffix:colon
id|freq
op_assign
l_int|48000
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|val
op_amp
id|VX_SUER_DATA_PRESENT_MASK
)paren
multiline_comment|/* bit 0 corresponds to consumer/professional bit */
op_star
id|mode
op_assign
id|vx_read_one_cbit
c_func
(paren
id|chip
comma
l_int|0
)paren
ques
c_cond
id|VX_UER_MODE_PROFESSIONAL
suffix:colon
id|VX_UER_MODE_CONSUMER
suffix:semicolon
r_else
op_star
id|mode
op_assign
id|VX_UER_MODE_NOT_PRESENT
suffix:semicolon
r_return
id|freq
suffix:semicolon
)brace
multiline_comment|/*&n; * compute the sample clock value from frequency&n; *&n; * The formula is as follows:&n; *&n; *    HexFreq = (dword) ((double) ((double) 28224000 / (double) Frequency))&n; *    switch ( HexFreq &amp; 0x00000F00 )&n; *    case 0x00000100: ;&n; *    case 0x00000200:&n; *    case 0x00000300: HexFreq -= 0x00000201 ;&n; *    case 0x00000400:&n; *    case 0x00000500:&n; *    case 0x00000600:&n; *    case 0x00000700: HexFreq = (dword) (((double) 28224000 / (double) (Frequency*2)) - 1)&n; *    default        : HexFreq = (dword) ((double) 28224000 / (double) (Frequency*4)) - 0x000001FF&n; */
DECL|function|vx_calc_clock_from_freq
r_static
r_int
id|vx_calc_clock_from_freq
c_func
(paren
id|vx_core_t
op_star
id|chip
comma
r_int
id|freq
)paren
(brace
DECL|macro|XX_FECH48000
mdefine_line|#define XX_FECH48000                    0x0000004B
DECL|macro|XX_FECH32000
mdefine_line|#define XX_FECH32000                    0x00000171
DECL|macro|XX_FECH24000
mdefine_line|#define XX_FECH24000                    0x0000024B
DECL|macro|XX_FECH16000
mdefine_line|#define XX_FECH16000                    0x00000371
DECL|macro|XX_FECH12000
mdefine_line|#define XX_FECH12000                    0x0000044B
DECL|macro|XX_FECH8000
mdefine_line|#define XX_FECH8000                     0x00000571
DECL|macro|XX_FECH44100
mdefine_line|#define XX_FECH44100                    0x0000007F
DECL|macro|XX_FECH29400
mdefine_line|#define XX_FECH29400                    0x0000016F
DECL|macro|XX_FECH22050
mdefine_line|#define XX_FECH22050                    0x0000027F
DECL|macro|XX_FECH14000
mdefine_line|#define XX_FECH14000                    0x000003EF
DECL|macro|XX_FECH11025
mdefine_line|#define XX_FECH11025                    0x0000047F
DECL|macro|XX_FECH7350
mdefine_line|#define XX_FECH7350                     0x000005BF
r_switch
c_cond
(paren
id|freq
)paren
(brace
r_case
l_int|48000
suffix:colon
r_return
id|XX_FECH48000
suffix:semicolon
r_case
l_int|44100
suffix:colon
r_return
id|XX_FECH44100
suffix:semicolon
r_case
l_int|32000
suffix:colon
r_return
id|XX_FECH32000
suffix:semicolon
r_case
l_int|29400
suffix:colon
r_return
id|XX_FECH29400
suffix:semicolon
r_case
l_int|24000
suffix:colon
r_return
id|XX_FECH24000
suffix:semicolon
r_case
l_int|22050
suffix:colon
r_return
id|XX_FECH22050
suffix:semicolon
r_case
l_int|16000
suffix:colon
r_return
id|XX_FECH16000
suffix:semicolon
r_case
l_int|14000
suffix:colon
r_return
id|XX_FECH14000
suffix:semicolon
r_case
l_int|12000
suffix:colon
r_return
id|XX_FECH12000
suffix:semicolon
r_case
l_int|11025
suffix:colon
r_return
id|XX_FECH11025
suffix:semicolon
r_case
l_int|8000
suffix:colon
r_return
id|XX_FECH8000
suffix:semicolon
r_case
l_int|7350
suffix:colon
r_return
id|XX_FECH7350
suffix:semicolon
r_default
suffix:colon
r_return
id|freq
suffix:semicolon
multiline_comment|/* The value is already correct */
)brace
)brace
multiline_comment|/*&n; * vx_change_clock_source - change the clock source&n; * @source: the new source&n; */
DECL|function|vx_change_clock_source
r_static
r_void
id|vx_change_clock_source
c_func
(paren
id|vx_core_t
op_star
id|chip
comma
r_int
id|source
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* we mute DAC to prevent clicks */
id|vx_toggle_dac_mute
c_func
(paren
id|chip
comma
l_int|1
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|chip-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|chip-&gt;ops
op_member_access_from_pointer
id|set_clock_source
c_func
(paren
id|chip
comma
id|source
)paren
suffix:semicolon
id|chip-&gt;clock_source
op_assign
id|source
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|chip-&gt;lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* unmute */
id|vx_toggle_dac_mute
c_func
(paren
id|chip
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * set the internal clock&n; */
DECL|function|vx_set_internal_clock
r_void
id|vx_set_internal_clock
c_func
(paren
id|vx_core_t
op_star
id|chip
comma
r_int
r_int
id|freq
)paren
(brace
r_int
id|clock
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* Get real clock value */
id|clock
op_assign
id|vx_calc_clock_from_freq
c_func
(paren
id|chip
comma
id|freq
)paren
suffix:semicolon
id|snd_printdd
c_func
(paren
id|KERN_DEBUG
l_string|&quot;set internal clock to 0x%x from freq %d&bslash;n&quot;
comma
id|clock
comma
id|freq
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|chip-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vx_is_pcmcia
c_func
(paren
id|chip
)paren
)paren
(brace
id|vx_outb
c_func
(paren
id|chip
comma
id|HIFREQ
comma
(paren
id|clock
op_rshift
l_int|8
)paren
op_amp
l_int|0x0f
)paren
suffix:semicolon
id|vx_outb
c_func
(paren
id|chip
comma
id|LOFREQ
comma
id|clock
op_amp
l_int|0xff
)paren
suffix:semicolon
)brace
r_else
(brace
id|vx_outl
c_func
(paren
id|chip
comma
id|HIFREQ
comma
(paren
id|clock
op_rshift
l_int|8
)paren
op_amp
l_int|0x0f
)paren
suffix:semicolon
id|vx_outl
c_func
(paren
id|chip
comma
id|LOFREQ
comma
id|clock
op_amp
l_int|0xff
)paren
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|chip-&gt;lock
comma
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * set the iec958 status bits&n; * @bits: 32-bit status bits&n; */
DECL|function|vx_set_iec958_status
r_void
id|vx_set_iec958_status
c_func
(paren
id|vx_core_t
op_star
id|chip
comma
r_int
r_int
id|bits
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|chip-&gt;chip_status
op_amp
id|VX_STAT_IS_STALE
)paren
r_return
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
l_int|32
suffix:semicolon
id|i
op_increment
)paren
id|vx_write_one_cbit
c_func
(paren
id|chip
comma
id|i
comma
id|bits
op_amp
(paren
l_int|1
op_lshift
id|i
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * vx_set_clock - change the clock and audio source if necessary&n; */
DECL|function|vx_set_clock
r_int
id|vx_set_clock
c_func
(paren
id|vx_core_t
op_star
id|chip
comma
r_int
r_int
id|freq
)paren
(brace
r_int
id|src_changed
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|chip-&gt;chip_status
op_amp
id|VX_STAT_IS_STALE
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* change the audio source if possible */
id|vx_sync_audio_source
c_func
(paren
id|chip
)paren
suffix:semicolon
r_if
c_cond
(paren
id|chip-&gt;clock_mode
op_eq
id|VX_CLOCK_MODE_EXTERNAL
op_logical_or
(paren
id|chip-&gt;clock_mode
op_eq
id|VX_CLOCK_MODE_AUTO
op_logical_and
id|chip-&gt;audio_source
op_eq
id|VX_AUDIO_SRC_DIGITAL
)paren
)paren
(brace
r_if
c_cond
(paren
id|chip-&gt;clock_source
op_ne
id|UER_SYNC
)paren
(brace
id|vx_change_clock_source
c_func
(paren
id|chip
comma
id|UER_SYNC
)paren
suffix:semicolon
id|mdelay
c_func
(paren
l_int|6
)paren
suffix:semicolon
id|src_changed
op_assign
l_int|1
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|chip-&gt;clock_mode
op_eq
id|VX_CLOCK_MODE_INTERNAL
op_logical_or
(paren
id|chip-&gt;clock_mode
op_eq
id|VX_CLOCK_MODE_AUTO
op_logical_and
id|chip-&gt;audio_source
op_ne
id|VX_AUDIO_SRC_DIGITAL
)paren
)paren
(brace
r_if
c_cond
(paren
id|chip-&gt;clock_source
op_ne
id|INTERNAL_QUARTZ
)paren
(brace
id|vx_change_clock_source
c_func
(paren
id|chip
comma
id|INTERNAL_QUARTZ
)paren
suffix:semicolon
id|src_changed
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|chip-&gt;freq
op_eq
id|freq
)paren
r_return
l_int|0
suffix:semicolon
id|vx_set_internal_clock
c_func
(paren
id|chip
comma
id|freq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|src_changed
)paren
id|vx_modify_board_inputs
c_func
(paren
id|chip
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|chip-&gt;freq
op_eq
id|freq
)paren
r_return
l_int|0
suffix:semicolon
id|chip-&gt;freq
op_assign
id|freq
suffix:semicolon
id|vx_modify_board_clock
c_func
(paren
id|chip
comma
l_int|1
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * vx_change_frequency - called from interrupt handler&n; */
DECL|function|vx_change_frequency
r_int
id|vx_change_frequency
c_func
(paren
id|vx_core_t
op_star
id|chip
)paren
(brace
r_int
id|freq
suffix:semicolon
r_if
c_cond
(paren
id|chip-&gt;chip_status
op_amp
id|VX_STAT_IS_STALE
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|chip-&gt;clock_source
op_eq
id|INTERNAL_QUARTZ
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * Read the real UER board frequency&n;&t; */
id|freq
op_assign
id|vx_read_uer_status
c_func
(paren
id|chip
comma
op_amp
id|chip-&gt;uer_detected
)paren
suffix:semicolon
r_if
c_cond
(paren
id|freq
OL
l_int|0
)paren
r_return
id|freq
suffix:semicolon
multiline_comment|/*&n;&t; * The frequency computed by the DSP is good and&n;&t; * is different from the previous computed.&n;&t; */
r_if
c_cond
(paren
id|freq
op_eq
l_int|48000
op_logical_or
id|freq
op_eq
l_int|44100
op_logical_or
id|freq
op_eq
l_int|32000
)paren
id|chip-&gt;freq_detected
op_assign
id|freq
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
