multiline_comment|/*&n; *  Copyright (c) by Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *  Universal interface for Audio Codec &squot;97&n; *&n; *  For more details look to AC &squot;97 component specification revision 2.2&n; *  by Intel Corporation (http://developer.intel.com) and to datasheets&n; *  for specific codecs.&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &lt;sound/pcm.h&gt;
macro_line|#include &lt;sound/control.h&gt;
macro_line|#include &lt;sound/ac97_codec.h&gt;
macro_line|#include &quot;ac97_patch.h&quot;
macro_line|#include &quot;ac97_id.h&quot;
macro_line|#include &quot;ac97_local.h&quot;
DECL|macro|chip_t
mdefine_line|#define chip_t ac97_t
multiline_comment|/*&n; *  PCM support&n; */
DECL|variable|rate_reg_tables
r_static
r_int
r_char
id|rate_reg_tables
(braket
l_int|2
)braket
(braket
l_int|4
)braket
(braket
l_int|9
)braket
op_assign
(brace
(brace
multiline_comment|/* standard rates */
(brace
multiline_comment|/* 3&amp;4 front, 7&amp;8 rear, 6&amp;9 center/lfe */
id|AC97_PCM_FRONT_DAC_RATE
comma
multiline_comment|/* slot 3 */
id|AC97_PCM_FRONT_DAC_RATE
comma
multiline_comment|/* slot 4 */
l_int|0xff
comma
multiline_comment|/* slot 5 */
id|AC97_PCM_LFE_DAC_RATE
comma
multiline_comment|/* slot 6 */
id|AC97_PCM_SURR_DAC_RATE
comma
multiline_comment|/* slot 7 */
id|AC97_PCM_SURR_DAC_RATE
comma
multiline_comment|/* slot 8 */
id|AC97_PCM_LFE_DAC_RATE
comma
multiline_comment|/* slot 9 */
l_int|0xff
comma
multiline_comment|/* slot 10 */
l_int|0xff
comma
multiline_comment|/* slot 11 */
)brace
comma
(brace
multiline_comment|/* 7&amp;8 front, 6&amp;9 rear, 10&amp;11 center/lfe */
l_int|0xff
comma
multiline_comment|/* slot 3 */
l_int|0xff
comma
multiline_comment|/* slot 4 */
l_int|0xff
comma
multiline_comment|/* slot 5 */
id|AC97_PCM_SURR_DAC_RATE
comma
multiline_comment|/* slot 6 */
id|AC97_PCM_FRONT_DAC_RATE
comma
multiline_comment|/* slot 7 */
id|AC97_PCM_FRONT_DAC_RATE
comma
multiline_comment|/* slot 8 */
id|AC97_PCM_SURR_DAC_RATE
comma
multiline_comment|/* slot 9 */
id|AC97_PCM_LFE_DAC_RATE
comma
multiline_comment|/* slot 10 */
id|AC97_PCM_LFE_DAC_RATE
comma
multiline_comment|/* slot 11 */
)brace
comma
(brace
multiline_comment|/* 6&amp;9 front, 10&amp;11 rear, 3&amp;4 center/lfe */
id|AC97_PCM_LFE_DAC_RATE
comma
multiline_comment|/* slot 3 */
id|AC97_PCM_LFE_DAC_RATE
comma
multiline_comment|/* slot 4 */
l_int|0xff
comma
multiline_comment|/* slot 5 */
id|AC97_PCM_FRONT_DAC_RATE
comma
multiline_comment|/* slot 6 */
l_int|0xff
comma
multiline_comment|/* slot 7 */
l_int|0xff
comma
multiline_comment|/* slot 8 */
id|AC97_PCM_FRONT_DAC_RATE
comma
multiline_comment|/* slot 9 */
id|AC97_PCM_SURR_DAC_RATE
comma
multiline_comment|/* slot 10 */
id|AC97_PCM_SURR_DAC_RATE
comma
multiline_comment|/* slot 11 */
)brace
comma
(brace
multiline_comment|/* 10&amp;11 front, 3&amp;4 rear, 7&amp;8 center/lfe */
id|AC97_PCM_SURR_DAC_RATE
comma
multiline_comment|/* slot 3 */
id|AC97_PCM_SURR_DAC_RATE
comma
multiline_comment|/* slot 4 */
l_int|0xff
comma
multiline_comment|/* slot 5 */
l_int|0xff
comma
multiline_comment|/* slot 6 */
id|AC97_PCM_LFE_DAC_RATE
comma
multiline_comment|/* slot 7 */
id|AC97_PCM_LFE_DAC_RATE
comma
multiline_comment|/* slot 8 */
id|AC97_PCM_FRONT_DAC_RATE
comma
multiline_comment|/* slot 9 */
id|AC97_PCM_FRONT_DAC_RATE
comma
multiline_comment|/* slot 10 */
id|AC97_PCM_FRONT_DAC_RATE
comma
multiline_comment|/* slot 11 */
)brace
comma
)brace
comma
(brace
multiline_comment|/* FIXME: double rates */
(brace
multiline_comment|/* 3&amp;4 front, 7&amp;8 rear, 6&amp;9 center/lfe */
id|AC97_PCM_FRONT_DAC_RATE
comma
multiline_comment|/* slot 3 */
id|AC97_PCM_FRONT_DAC_RATE
comma
multiline_comment|/* slot 4 */
l_int|0xff
comma
multiline_comment|/* slot 5 */
id|AC97_PCM_LFE_DAC_RATE
comma
multiline_comment|/* slot 6 */
id|AC97_PCM_SURR_DAC_RATE
comma
multiline_comment|/* slot 7 */
id|AC97_PCM_SURR_DAC_RATE
comma
multiline_comment|/* slot 8 */
id|AC97_PCM_LFE_DAC_RATE
comma
multiline_comment|/* slot 9 */
l_int|0xff
comma
multiline_comment|/* slot 10 */
l_int|0xff
comma
multiline_comment|/* slot 11 */
)brace
comma
(brace
multiline_comment|/* 7&amp;8 front, 6&amp;9 rear, 10&amp;11 center/lfe */
l_int|0xff
comma
multiline_comment|/* slot 3 */
l_int|0xff
comma
multiline_comment|/* slot 4 */
l_int|0xff
comma
multiline_comment|/* slot 5 */
id|AC97_PCM_SURR_DAC_RATE
comma
multiline_comment|/* slot 6 */
id|AC97_PCM_FRONT_DAC_RATE
comma
multiline_comment|/* slot 7 */
id|AC97_PCM_FRONT_DAC_RATE
comma
multiline_comment|/* slot 8 */
id|AC97_PCM_SURR_DAC_RATE
comma
multiline_comment|/* slot 9 */
id|AC97_PCM_LFE_DAC_RATE
comma
multiline_comment|/* slot 10 */
id|AC97_PCM_LFE_DAC_RATE
comma
multiline_comment|/* slot 11 */
)brace
comma
(brace
multiline_comment|/* 6&amp;9 front, 10&amp;11 rear, 3&amp;4 center/lfe */
id|AC97_PCM_LFE_DAC_RATE
comma
multiline_comment|/* slot 3 */
id|AC97_PCM_LFE_DAC_RATE
comma
multiline_comment|/* slot 4 */
l_int|0xff
comma
multiline_comment|/* slot 5 */
id|AC97_PCM_FRONT_DAC_RATE
comma
multiline_comment|/* slot 6 */
l_int|0xff
comma
multiline_comment|/* slot 7 */
l_int|0xff
comma
multiline_comment|/* slot 8 */
id|AC97_PCM_FRONT_DAC_RATE
comma
multiline_comment|/* slot 9 */
id|AC97_PCM_SURR_DAC_RATE
comma
multiline_comment|/* slot 10 */
id|AC97_PCM_SURR_DAC_RATE
comma
multiline_comment|/* slot 11 */
)brace
comma
(brace
multiline_comment|/* 10&amp;11 front, 3&amp;4 rear, 7&amp;8 center/lfe */
id|AC97_PCM_SURR_DAC_RATE
comma
multiline_comment|/* slot 3 */
id|AC97_PCM_SURR_DAC_RATE
comma
multiline_comment|/* slot 4 */
l_int|0xff
comma
multiline_comment|/* slot 5 */
l_int|0xff
comma
multiline_comment|/* slot 6 */
id|AC97_PCM_LFE_DAC_RATE
comma
multiline_comment|/* slot 7 */
id|AC97_PCM_LFE_DAC_RATE
comma
multiline_comment|/* slot 8 */
id|AC97_PCM_FRONT_DAC_RATE
comma
multiline_comment|/* slot 9 */
id|AC97_PCM_FRONT_DAC_RATE
comma
multiline_comment|/* slot 10 */
id|AC97_PCM_FRONT_DAC_RATE
comma
multiline_comment|/* slot 11 */
)brace
)brace
)brace
suffix:semicolon
multiline_comment|/* FIXME: more various mappings for ADC? */
DECL|variable|rate_cregs
r_static
r_int
r_char
id|rate_cregs
(braket
l_int|9
)braket
op_assign
(brace
id|AC97_PCM_LR_ADC_RATE
comma
multiline_comment|/* 3 */
id|AC97_PCM_LR_ADC_RATE
comma
multiline_comment|/* 4 */
l_int|0xff
comma
multiline_comment|/* 5 */
id|AC97_PCM_MIC_ADC_RATE
comma
multiline_comment|/* 6 */
l_int|0xff
comma
multiline_comment|/* 7 */
l_int|0xff
comma
multiline_comment|/* 8 */
l_int|0xff
comma
multiline_comment|/* 9 */
l_int|0xff
comma
multiline_comment|/* 10 */
l_int|0xff
comma
multiline_comment|/* 11 */
)brace
suffix:semicolon
DECL|function|get_slot_reg
r_static
r_int
r_char
id|get_slot_reg
c_func
(paren
r_struct
id|ac97_pcm
op_star
id|pcm
comma
r_int
r_int
id|cidx
comma
r_int
r_int
id|slot
comma
r_int
id|dbl
)paren
(brace
r_if
c_cond
(paren
id|slot
OL
l_int|3
)paren
r_return
l_int|0xff
suffix:semicolon
r_if
c_cond
(paren
id|slot
OG
l_int|11
)paren
r_return
l_int|0xff
suffix:semicolon
r_if
c_cond
(paren
id|pcm-&gt;spdif
)paren
r_return
id|AC97_SPDIF
suffix:semicolon
multiline_comment|/* pseudo register */
r_if
c_cond
(paren
id|pcm-&gt;stream
op_eq
id|SNDRV_PCM_STREAM_PLAYBACK
)paren
r_return
id|rate_reg_tables
(braket
id|dbl
)braket
(braket
id|pcm-&gt;r
(braket
id|dbl
)braket
dot
id|rate_table
(braket
id|cidx
)braket
)braket
(braket
id|slot
op_minus
l_int|3
)braket
suffix:semicolon
r_else
r_return
id|rate_cregs
(braket
id|slot
op_minus
l_int|3
)braket
suffix:semicolon
)brace
DECL|function|set_spdif_rate
r_static
r_int
id|set_spdif_rate
c_func
(paren
id|ac97_t
op_star
id|ac97
comma
r_int
r_int
id|rate
)paren
(brace
r_int
r_int
id|old
comma
id|bits
comma
id|reg
comma
id|mask
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|ac97-&gt;ext_id
op_amp
id|AC97_EI_SPDIF
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
id|ac97-&gt;flags
op_amp
id|AC97_CS_SPDIF
)paren
(brace
r_switch
c_cond
(paren
id|rate
)paren
(brace
r_case
l_int|48000
suffix:colon
id|bits
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|44100
suffix:colon
id|bits
op_assign
l_int|1
op_lshift
id|AC97_SC_SPSR_SHIFT
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* invalid - disable output */
id|snd_ac97_update_bits
c_func
(paren
id|ac97
comma
id|AC97_EXTENDED_STATUS
comma
id|AC97_EA_SPDIF
comma
l_int|0
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|reg
op_assign
id|AC97_CSR_SPDIF
suffix:semicolon
id|mask
op_assign
l_int|1
op_lshift
id|AC97_SC_SPSR_SHIFT
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|ac97-&gt;id
op_eq
id|AC97_ID_CM9739
op_logical_and
id|rate
op_ne
l_int|48000
)paren
(brace
id|snd_ac97_update_bits
c_func
(paren
id|ac97
comma
id|AC97_EXTENDED_STATUS
comma
id|AC97_EA_SPDIF
comma
l_int|0
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|rate
)paren
(brace
r_case
l_int|44100
suffix:colon
id|bits
op_assign
id|AC97_SC_SPSR_44K
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|48000
suffix:colon
id|bits
op_assign
id|AC97_SC_SPSR_48K
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|32000
suffix:colon
id|bits
op_assign
id|AC97_SC_SPSR_32K
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* invalid - disable output */
id|snd_ac97_update_bits
c_func
(paren
id|ac97
comma
id|AC97_EXTENDED_STATUS
comma
id|AC97_EA_SPDIF
comma
l_int|0
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|reg
op_assign
id|AC97_SPDIF
suffix:semicolon
id|mask
op_assign
id|AC97_SC_SPSR_MASK
suffix:semicolon
)brace
id|spin_lock
c_func
(paren
op_amp
id|ac97-&gt;reg_lock
)paren
suffix:semicolon
id|old
op_assign
id|ac97-&gt;regs
(braket
id|reg
)braket
op_amp
id|mask
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|ac97-&gt;reg_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|old
op_ne
id|bits
)paren
(brace
id|snd_ac97_update_bits
c_func
(paren
id|ac97
comma
id|AC97_EXTENDED_STATUS
comma
id|AC97_EA_SPDIF
comma
l_int|0
)paren
suffix:semicolon
id|snd_ac97_update_bits
c_func
(paren
id|ac97
comma
id|reg
comma
id|mask
comma
id|bits
)paren
suffix:semicolon
)brace
id|snd_ac97_update_bits
c_func
(paren
id|ac97
comma
id|AC97_EXTENDED_STATUS
comma
id|AC97_EA_SPDIF
comma
id|AC97_EA_SPDIF
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * snd_ac97_set_rate - change the rate of the given input/output.&n; * @ac97: the ac97 instance&n; * @reg: the register to change&n; * @rate: the sample rate to set&n; *&n; * Changes the rate of the given input/output on the codec.&n; * If the codec doesn&squot;t support VAR, the rate must be 48000 (except&n; * for SPDIF).&n; *&n; * The valid registers are AC97_PMC_MIC_ADC_RATE,&n; * AC97_PCM_FRONT_DAC_RATE, AC97_PCM_LR_ADC_RATE.&n; * AC97_PCM_SURR_DAC_RATE and AC97_PCM_LFE_DAC_RATE are accepted&n; * if the codec supports them.&n; * AC97_SPDIF is accepted as a pseudo register to modify the SPDIF&n; * status bits.&n; *&n; * Returns zero if successful, or a negative error code on failure.&n; */
DECL|function|snd_ac97_set_rate
r_int
id|snd_ac97_set_rate
c_func
(paren
id|ac97_t
op_star
id|ac97
comma
r_int
id|reg
comma
r_int
r_int
id|rate
)paren
(brace
r_int
r_int
id|tmp
suffix:semicolon
r_switch
c_cond
(paren
id|reg
)paren
(brace
r_case
id|AC97_PCM_MIC_ADC_RATE
suffix:colon
r_if
c_cond
(paren
(paren
id|ac97-&gt;regs
(braket
id|AC97_EXTENDED_STATUS
)braket
op_amp
id|AC97_EA_VRM
)paren
op_eq
l_int|0
)paren
multiline_comment|/* MIC VRA */
r_if
c_cond
(paren
id|rate
op_ne
l_int|48000
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AC97_PCM_FRONT_DAC_RATE
suffix:colon
r_case
id|AC97_PCM_LR_ADC_RATE
suffix:colon
r_if
c_cond
(paren
(paren
id|ac97-&gt;regs
(braket
id|AC97_EXTENDED_STATUS
)braket
op_amp
id|AC97_EA_VRA
)paren
op_eq
l_int|0
)paren
multiline_comment|/* VRA */
r_if
c_cond
(paren
id|rate
op_ne
l_int|48000
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AC97_PCM_SURR_DAC_RATE
suffix:colon
r_if
c_cond
(paren
op_logical_neg
(paren
id|ac97-&gt;scaps
op_amp
id|AC97_SCAP_SURROUND_DAC
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AC97_PCM_LFE_DAC_RATE
suffix:colon
r_if
c_cond
(paren
op_logical_neg
(paren
id|ac97-&gt;scaps
op_amp
id|AC97_SCAP_CENTER_LFE_DAC
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AC97_SPDIF
suffix:colon
multiline_comment|/* special case */
r_return
id|set_spdif_rate
c_func
(paren
id|ac97
comma
id|rate
)paren
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|tmp
op_assign
(paren
(paren
r_int
r_int
)paren
id|rate
op_star
id|ac97-&gt;bus-&gt;clock
)paren
op_div
l_int|48000
suffix:semicolon
r_if
c_cond
(paren
id|tmp
OG
l_int|65535
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|snd_ac97_update
c_func
(paren
id|ac97
comma
id|reg
comma
id|tmp
op_amp
l_int|0xffff
)paren
suffix:semicolon
id|snd_ac97_read
c_func
(paren
id|ac97
comma
id|reg
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|get_pslots
r_static
r_int
r_int
id|get_pslots
c_func
(paren
id|ac97_t
op_star
id|ac97
comma
r_int
r_char
op_star
id|rate_table
comma
r_int
r_int
op_star
id|spdif_slots
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|ac97_is_audio
c_func
(paren
id|ac97
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|ac97_is_rev22
c_func
(paren
id|ac97
)paren
op_logical_or
id|ac97_can_amap
c_func
(paren
id|ac97
)paren
)paren
(brace
r_int
r_int
id|slots
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|ac97_is_rev22
c_func
(paren
id|ac97
)paren
)paren
(brace
multiline_comment|/* Note: it&squot;s simply emulation of AMAP behaviour */
id|u16
id|es
suffix:semicolon
id|es
op_assign
id|ac97-&gt;regs
(braket
id|AC97_EXTENDED_STATUS
)braket
op_and_assign
op_complement
id|AC97_EI_DACS_SLOT_MASK
suffix:semicolon
r_switch
c_cond
(paren
id|ac97-&gt;addr
)paren
(brace
r_case
l_int|1
suffix:colon
r_case
l_int|2
suffix:colon
id|es
op_or_assign
(paren
l_int|1
op_lshift
id|AC97_EI_DACS_SLOT_SHIFT
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|es
op_or_assign
(paren
l_int|2
op_lshift
id|AC97_EI_DACS_SLOT_SHIFT
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|snd_ac97_write_cache
c_func
(paren
id|ac97
comma
id|AC97_EXTENDED_STATUS
comma
id|es
)paren
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|ac97-&gt;addr
)paren
(brace
r_case
l_int|0
suffix:colon
id|slots
op_or_assign
(paren
l_int|1
op_lshift
id|AC97_SLOT_PCM_LEFT
)paren
op_or
(paren
l_int|1
op_lshift
id|AC97_SLOT_PCM_RIGHT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ac97-&gt;scaps
op_amp
id|AC97_SCAP_SURROUND_DAC
)paren
id|slots
op_or_assign
(paren
l_int|1
op_lshift
id|AC97_SLOT_PCM_SLEFT
)paren
op_or
(paren
l_int|1
op_lshift
id|AC97_SLOT_PCM_SRIGHT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ac97-&gt;scaps
op_amp
id|AC97_SCAP_CENTER_LFE_DAC
)paren
id|slots
op_or_assign
(paren
l_int|1
op_lshift
id|AC97_SLOT_PCM_CENTER
)paren
op_or
(paren
l_int|1
op_lshift
id|AC97_SLOT_LFE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ac97-&gt;ext_id
op_amp
id|AC97_EI_SPDIF
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|ac97-&gt;scaps
op_amp
id|AC97_SCAP_SURROUND_DAC
)paren
)paren
op_star
id|spdif_slots
op_assign
(paren
l_int|1
op_lshift
id|AC97_SLOT_SPDIF_LEFT
)paren
op_or
(paren
l_int|1
op_lshift
id|AC97_SLOT_SPDIF_RIGHT
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
(paren
id|ac97-&gt;scaps
op_amp
id|AC97_SCAP_CENTER_LFE_DAC
)paren
)paren
op_star
id|spdif_slots
op_assign
(paren
l_int|1
op_lshift
id|AC97_SLOT_SPDIF_LEFT1
)paren
op_or
(paren
l_int|1
op_lshift
id|AC97_SLOT_SPDIF_RIGHT1
)paren
suffix:semicolon
r_else
op_star
id|spdif_slots
op_assign
(paren
l_int|1
op_lshift
id|AC97_SLOT_SPDIF_LEFT2
)paren
op_or
(paren
l_int|1
op_lshift
id|AC97_SLOT_SPDIF_RIGHT2
)paren
suffix:semicolon
)brace
op_star
id|rate_table
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
r_case
l_int|2
suffix:colon
id|slots
op_or_assign
(paren
l_int|1
op_lshift
id|AC97_SLOT_PCM_SLEFT
)paren
op_or
(paren
l_int|1
op_lshift
id|AC97_SLOT_PCM_SRIGHT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ac97-&gt;scaps
op_amp
id|AC97_SCAP_SURROUND_DAC
)paren
id|slots
op_or_assign
(paren
l_int|1
op_lshift
id|AC97_SLOT_PCM_CENTER
)paren
op_or
(paren
l_int|1
op_lshift
id|AC97_SLOT_LFE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ac97-&gt;ext_id
op_amp
id|AC97_EI_SPDIF
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|ac97-&gt;scaps
op_amp
id|AC97_SCAP_SURROUND_DAC
)paren
)paren
op_star
id|spdif_slots
op_assign
(paren
l_int|1
op_lshift
id|AC97_SLOT_SPDIF_LEFT1
)paren
op_or
(paren
l_int|1
op_lshift
id|AC97_SLOT_SPDIF_RIGHT1
)paren
suffix:semicolon
r_else
op_star
id|spdif_slots
op_assign
(paren
l_int|1
op_lshift
id|AC97_SLOT_SPDIF_LEFT2
)paren
op_or
(paren
l_int|1
op_lshift
id|AC97_SLOT_SPDIF_RIGHT2
)paren
suffix:semicolon
)brace
op_star
id|rate_table
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|slots
op_or_assign
(paren
l_int|1
op_lshift
id|AC97_SLOT_PCM_CENTER
)paren
op_or
(paren
l_int|1
op_lshift
id|AC97_SLOT_LFE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ac97-&gt;ext_id
op_amp
id|AC97_EI_SPDIF
)paren
op_star
id|spdif_slots
op_assign
(paren
l_int|1
op_lshift
id|AC97_SLOT_SPDIF_LEFT2
)paren
op_or
(paren
l_int|1
op_lshift
id|AC97_SLOT_SPDIF_RIGHT2
)paren
suffix:semicolon
op_star
id|rate_table
op_assign
l_int|2
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|slots
suffix:semicolon
)brace
r_else
(brace
r_int
r_int
id|slots
suffix:semicolon
id|slots
op_assign
(paren
l_int|1
op_lshift
id|AC97_SLOT_PCM_LEFT
)paren
op_or
(paren
l_int|1
op_lshift
id|AC97_SLOT_PCM_RIGHT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ac97-&gt;scaps
op_amp
id|AC97_SCAP_SURROUND_DAC
)paren
id|slots
op_or_assign
(paren
l_int|1
op_lshift
id|AC97_SLOT_PCM_SLEFT
)paren
op_or
(paren
l_int|1
op_lshift
id|AC97_SLOT_PCM_SRIGHT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ac97-&gt;scaps
op_amp
id|AC97_SCAP_CENTER_LFE_DAC
)paren
id|slots
op_or_assign
(paren
l_int|1
op_lshift
id|AC97_SLOT_PCM_CENTER
)paren
op_or
(paren
l_int|1
op_lshift
id|AC97_SLOT_LFE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ac97-&gt;ext_id
op_amp
id|AC97_EI_SPDIF
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|ac97-&gt;scaps
op_amp
id|AC97_SCAP_SURROUND_DAC
)paren
)paren
op_star
id|spdif_slots
op_assign
(paren
l_int|1
op_lshift
id|AC97_SLOT_SPDIF_LEFT
)paren
op_or
(paren
l_int|1
op_lshift
id|AC97_SLOT_SPDIF_RIGHT
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
(paren
id|ac97-&gt;scaps
op_amp
id|AC97_SCAP_CENTER_LFE_DAC
)paren
)paren
op_star
id|spdif_slots
op_assign
(paren
l_int|1
op_lshift
id|AC97_SLOT_SPDIF_LEFT1
)paren
op_or
(paren
l_int|1
op_lshift
id|AC97_SLOT_SPDIF_RIGHT1
)paren
suffix:semicolon
r_else
op_star
id|spdif_slots
op_assign
(paren
l_int|1
op_lshift
id|AC97_SLOT_SPDIF_LEFT2
)paren
op_or
(paren
l_int|1
op_lshift
id|AC97_SLOT_SPDIF_RIGHT2
)paren
suffix:semicolon
)brace
op_star
id|rate_table
op_assign
l_int|0
suffix:semicolon
r_return
id|slots
suffix:semicolon
)brace
)brace
DECL|function|get_cslots
r_static
r_int
r_int
id|get_cslots
c_func
(paren
id|ac97_t
op_star
id|ac97
)paren
(brace
r_int
r_int
id|slots
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ac97_is_audio
c_func
(paren
id|ac97
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|slots
op_assign
(paren
l_int|1
op_lshift
id|AC97_SLOT_PCM_LEFT
)paren
op_or
(paren
l_int|1
op_lshift
id|AC97_SLOT_PCM_RIGHT
)paren
suffix:semicolon
id|slots
op_or_assign
(paren
l_int|1
op_lshift
id|AC97_SLOT_MIC
)paren
suffix:semicolon
r_return
id|slots
suffix:semicolon
)brace
DECL|function|get_rates
r_static
r_int
r_int
id|get_rates
c_func
(paren
r_struct
id|ac97_pcm
op_star
id|pcm
comma
r_int
r_int
id|cidx
comma
r_int
r_int
id|slots
comma
r_int
id|dbl
)paren
(brace
r_int
id|i
comma
id|idx
suffix:semicolon
r_int
r_int
id|rates
op_assign
op_complement
l_int|0
suffix:semicolon
r_int
r_char
id|reg
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|3
suffix:semicolon
id|i
OL
l_int|12
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|slots
op_amp
(paren
l_int|1
op_lshift
id|i
)paren
)paren
)paren
r_continue
suffix:semicolon
id|reg
op_assign
id|get_slot_reg
c_func
(paren
id|pcm
comma
id|cidx
comma
id|i
comma
id|dbl
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|reg
)paren
(brace
r_case
id|AC97_PCM_FRONT_DAC_RATE
suffix:colon
id|idx
op_assign
id|AC97_RATES_FRONT_DAC
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AC97_PCM_SURR_DAC_RATE
suffix:colon
id|idx
op_assign
id|AC97_RATES_SURR_DAC
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AC97_PCM_LFE_DAC_RATE
suffix:colon
id|idx
op_assign
id|AC97_RATES_LFE_DAC
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AC97_PCM_LR_ADC_RATE
suffix:colon
id|idx
op_assign
id|AC97_RATES_ADC
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AC97_PCM_MIC_ADC_RATE
suffix:colon
id|idx
op_assign
id|AC97_RATES_MIC_ADC
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|idx
op_assign
id|AC97_RATES_SPDIF
suffix:semicolon
r_break
suffix:semicolon
)brace
id|rates
op_and_assign
id|pcm-&gt;r
(braket
id|dbl
)braket
dot
id|codec
(braket
id|cidx
)braket
op_member_access_from_pointer
id|rates
(braket
id|idx
)braket
suffix:semicolon
)brace
r_return
id|rates
suffix:semicolon
)brace
multiline_comment|/**&n; * snd_ac97_pcm_assign - assign AC97 slots to given PCM streams&n; * @bus: the ac97 bus instance&n; * @pcms_count: count of PCMs to be assigned&n; * @pcms: PCMs to be assigned&n; *&n; * It assigns available AC97 slots for given PCMs. If none or only&n; * some slots are available, pcm-&gt;xxx.slots and pcm-&gt;xxx.rslots[] members&n; * are reduced and might be zero.&n; */
DECL|function|snd_ac97_pcm_assign
r_int
id|snd_ac97_pcm_assign
c_func
(paren
id|ac97_bus_t
op_star
id|bus
comma
r_int
r_int
id|pcms_count
comma
r_const
r_struct
id|ac97_pcm
op_star
id|pcms
)paren
(brace
r_int
id|i
comma
id|j
comma
id|k
suffix:semicolon
r_const
r_struct
id|ac97_pcm
op_star
id|pcm
suffix:semicolon
r_struct
id|ac97_pcm
op_star
id|rpcms
comma
op_star
id|rpcm
suffix:semicolon
r_int
r_int
id|avail_slots
(braket
l_int|2
)braket
(braket
l_int|4
)braket
suffix:semicolon
r_int
r_char
id|rate_table
(braket
l_int|2
)braket
(braket
l_int|4
)braket
suffix:semicolon
r_int
r_int
id|tmp
comma
id|slots
suffix:semicolon
r_int
r_int
id|spdif_slots
(braket
l_int|4
)braket
suffix:semicolon
r_int
r_int
id|rates
suffix:semicolon
id|ac97_t
op_star
id|codec
suffix:semicolon
id|rpcms
op_assign
id|snd_kcalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|ac97_pcm
)paren
op_star
id|pcms_count
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rpcms
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
id|avail_slots
comma
l_int|0
comma
r_sizeof
(paren
id|avail_slots
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
id|rate_table
comma
l_int|0
comma
r_sizeof
(paren
id|rate_table
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
id|spdif_slots
comma
l_int|0
comma
r_sizeof
(paren
id|spdif_slots
)paren
)paren
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
l_int|4
suffix:semicolon
id|i
op_increment
)paren
(brace
id|codec
op_assign
id|bus-&gt;codec
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|codec
)paren
r_continue
suffix:semicolon
id|avail_slots
(braket
l_int|0
)braket
(braket
id|i
)braket
op_assign
id|get_pslots
c_func
(paren
id|codec
comma
op_amp
id|rate_table
(braket
l_int|0
)braket
(braket
id|i
)braket
comma
op_amp
id|spdif_slots
(braket
id|i
)braket
)paren
suffix:semicolon
id|avail_slots
(braket
l_int|1
)braket
(braket
id|i
)braket
op_assign
id|get_cslots
c_func
(paren
id|codec
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|codec-&gt;scaps
op_amp
id|AC97_SCAP_INDEP_SDIN
)paren
)paren
(brace
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|i
suffix:semicolon
id|j
op_increment
)paren
(brace
r_if
c_cond
(paren
id|bus-&gt;codec
(braket
id|j
)braket
)paren
id|avail_slots
(braket
l_int|1
)braket
(braket
id|i
)braket
op_and_assign
op_complement
id|avail_slots
(braket
l_int|1
)braket
(braket
id|j
)braket
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/* FIXME: add double rate allocation */
multiline_comment|/* first step - exclusive devices */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|pcms_count
suffix:semicolon
id|i
op_increment
)paren
(brace
id|pcm
op_assign
op_amp
id|pcms
(braket
id|i
)braket
suffix:semicolon
id|rpcm
op_assign
op_amp
id|rpcms
(braket
id|i
)braket
suffix:semicolon
multiline_comment|/* low-level driver thinks that it&squot;s more clever */
r_if
c_cond
(paren
id|pcm-&gt;copy_flag
)paren
(brace
op_star
id|rpcm
op_assign
op_star
id|pcm
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|rpcm-&gt;stream
op_assign
id|pcm-&gt;stream
suffix:semicolon
id|rpcm-&gt;exclusive
op_assign
id|pcm-&gt;exclusive
suffix:semicolon
id|rpcm-&gt;spdif
op_assign
id|pcm-&gt;spdif
suffix:semicolon
id|rpcm-&gt;private_value
op_assign
id|pcm-&gt;private_value
suffix:semicolon
id|rpcm-&gt;bus
op_assign
id|bus
suffix:semicolon
id|rpcm-&gt;rates
op_assign
op_complement
l_int|0
suffix:semicolon
id|slots
op_assign
id|pcm-&gt;r
(braket
l_int|0
)braket
dot
id|slots
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
l_int|4
op_logical_and
id|slots
suffix:semicolon
id|j
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|bus-&gt;codec
(braket
id|j
)braket
)paren
r_continue
suffix:semicolon
id|rates
op_assign
op_complement
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|pcm-&gt;spdif
op_logical_and
id|pcm-&gt;stream
op_eq
l_int|0
)paren
id|tmp
op_assign
id|spdif_slots
(braket
id|j
)braket
suffix:semicolon
r_else
id|tmp
op_assign
id|avail_slots
(braket
id|pcm-&gt;stream
)braket
(braket
id|j
)braket
suffix:semicolon
r_if
c_cond
(paren
id|pcm-&gt;exclusive
)paren
(brace
multiline_comment|/* exclusive access */
id|tmp
op_and_assign
id|slots
suffix:semicolon
r_for
c_loop
(paren
id|k
op_assign
l_int|0
suffix:semicolon
id|k
OL
id|i
suffix:semicolon
id|k
op_increment
)paren
(brace
r_if
c_cond
(paren
id|rpcm-&gt;stream
op_eq
id|rpcms
(braket
id|k
)braket
dot
id|stream
)paren
id|tmp
op_and_assign
op_complement
id|rpcms
(braket
id|k
)braket
dot
id|r
(braket
l_int|0
)braket
dot
id|rslots
(braket
id|j
)braket
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* non-exclusive access */
id|tmp
op_and_assign
id|pcm-&gt;r
(braket
l_int|0
)braket
dot
id|slots
suffix:semicolon
)brace
r_if
c_cond
(paren
id|tmp
)paren
(brace
id|rpcm-&gt;r
(braket
l_int|0
)braket
dot
id|rslots
(braket
id|j
)braket
op_assign
id|tmp
suffix:semicolon
id|rpcm-&gt;r
(braket
l_int|0
)braket
dot
id|codec
(braket
id|j
)braket
op_assign
id|bus-&gt;codec
(braket
id|j
)braket
suffix:semicolon
id|rpcm-&gt;r
(braket
l_int|0
)braket
dot
id|rate_table
(braket
id|j
)braket
op_assign
id|rate_table
(braket
id|pcm-&gt;stream
)braket
(braket
id|j
)braket
suffix:semicolon
id|rates
op_assign
id|get_rates
c_func
(paren
id|rpcm
comma
id|j
comma
id|tmp
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pcm-&gt;exclusive
)paren
id|avail_slots
(braket
id|pcm-&gt;stream
)braket
(braket
id|j
)braket
op_and_assign
op_complement
id|tmp
suffix:semicolon
)brace
id|slots
op_and_assign
op_complement
id|tmp
suffix:semicolon
id|rpcm-&gt;r
(braket
l_int|0
)braket
dot
id|slots
op_or_assign
id|tmp
suffix:semicolon
id|rpcm-&gt;rates
op_and_assign
id|rates
suffix:semicolon
)brace
r_if
c_cond
(paren
id|rpcm-&gt;rates
op_eq
op_complement
l_int|0
)paren
id|rpcm-&gt;rates
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* not used */
)brace
id|bus-&gt;pcms_count
op_assign
id|pcms_count
suffix:semicolon
id|bus-&gt;pcms
op_assign
id|rpcms
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * snd_ac97_pcm_open - opens the given AC97 pcm&n; * @pcm: the ac97 pcm instance&n; * @rate: rate in Hz, if codec does not support VRA, this value must be 48000Hz&n; * @cfg: output stream characteristics&n; * @slots: a subset of allocated slots (snd_ac97_pcm_assign) for this pcm&n; *&n; * It locks the specified slots and sets the given rate to AC97 registers.&n; */
DECL|function|snd_ac97_pcm_open
r_int
id|snd_ac97_pcm_open
c_func
(paren
r_struct
id|ac97_pcm
op_star
id|pcm
comma
r_int
r_int
id|rate
comma
r_enum
id|ac97_pcm_cfg
id|cfg
comma
r_int
r_int
id|slots
)paren
(brace
id|ac97_bus_t
op_star
id|bus
suffix:semicolon
r_int
id|i
comma
id|cidx
comma
id|r
op_assign
l_int|0
comma
id|ok_flag
suffix:semicolon
r_int
r_int
id|reg_ok
op_assign
l_int|0
suffix:semicolon
r_int
r_char
id|reg
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|rate
OG
l_int|48000
)paren
multiline_comment|/* FIXME: add support for double rate */
r_return
op_minus
id|EINVAL
suffix:semicolon
id|bus
op_assign
id|pcm-&gt;bus
suffix:semicolon
r_if
c_cond
(paren
id|cfg
op_eq
id|AC97_PCM_CFG_SPDIF
)paren
(brace
r_int
id|err
suffix:semicolon
r_for
c_loop
(paren
id|cidx
op_assign
l_int|0
suffix:semicolon
id|cidx
OL
l_int|4
suffix:semicolon
id|cidx
op_increment
)paren
r_if
c_cond
(paren
id|bus-&gt;codec
(braket
id|cidx
)braket
op_logical_and
(paren
id|bus-&gt;codec
(braket
id|cidx
)braket
op_member_access_from_pointer
id|ext_id
op_amp
id|AC97_EI_SPDIF
)paren
)paren
(brace
id|err
op_assign
id|set_spdif_rate
c_func
(paren
id|bus-&gt;codec
(braket
id|cidx
)braket
comma
id|rate
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
)brace
)brace
id|spin_lock_irq
c_func
(paren
op_amp
id|pcm-&gt;bus-&gt;bus_lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|3
suffix:semicolon
id|i
OL
l_int|12
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|slots
op_amp
(paren
l_int|1
op_lshift
id|i
)paren
)paren
)paren
r_continue
suffix:semicolon
id|ok_flag
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|cidx
op_assign
l_int|0
suffix:semicolon
id|cidx
OL
l_int|4
suffix:semicolon
id|cidx
op_increment
)paren
(brace
r_if
c_cond
(paren
id|bus-&gt;used_slots
(braket
id|pcm-&gt;stream
)braket
(braket
id|cidx
)braket
op_amp
(paren
l_int|1
op_lshift
id|i
)paren
)paren
(brace
id|spin_unlock_irq
c_func
(paren
op_amp
id|pcm-&gt;bus-&gt;bus_lock
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|EBUSY
suffix:semicolon
r_goto
id|error
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pcm-&gt;r
(braket
id|r
)braket
dot
id|rslots
(braket
id|cidx
)braket
op_amp
(paren
l_int|1
op_lshift
id|i
)paren
)paren
(brace
id|bus-&gt;used_slots
(braket
id|pcm-&gt;stream
)braket
(braket
id|cidx
)braket
op_or_assign
(paren
l_int|1
op_lshift
id|i
)paren
suffix:semicolon
id|ok_flag
op_increment
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|ok_flag
)paren
(brace
id|spin_unlock_irq
c_func
(paren
op_amp
id|pcm-&gt;bus-&gt;bus_lock
)paren
suffix:semicolon
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;cannot find configuration for AC97 slot %i&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|EAGAIN
suffix:semicolon
r_goto
id|error
suffix:semicolon
)brace
)brace
id|spin_unlock_irq
c_func
(paren
op_amp
id|pcm-&gt;bus-&gt;bus_lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|3
suffix:semicolon
id|i
OL
l_int|12
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|slots
op_amp
(paren
l_int|1
op_lshift
id|i
)paren
)paren
)paren
r_continue
suffix:semicolon
r_for
c_loop
(paren
id|cidx
op_assign
l_int|0
suffix:semicolon
id|cidx
OL
l_int|4
suffix:semicolon
id|cidx
op_increment
)paren
(brace
r_if
c_cond
(paren
id|pcm-&gt;r
(braket
id|r
)braket
dot
id|rslots
(braket
id|cidx
)braket
op_amp
(paren
l_int|1
op_lshift
id|i
)paren
)paren
(brace
id|reg
op_assign
id|get_slot_reg
c_func
(paren
id|pcm
comma
id|cidx
comma
id|i
comma
id|r
)paren
suffix:semicolon
r_if
c_cond
(paren
id|reg
op_eq
l_int|0xff
)paren
(brace
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;invalid AC97 slot %i?&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|reg_ok
op_amp
(paren
l_int|1
op_lshift
(paren
id|reg
op_minus
id|AC97_PCM_FRONT_DAC_RATE
)paren
)paren
)paren
r_continue
suffix:semicolon
singleline_comment|//printk(KERN_DEBUG &quot;setting ac97 reg 0x%x to rate %d&bslash;n&quot;, reg, rate);
id|err
op_assign
id|snd_ac97_set_rate
c_func
(paren
id|pcm-&gt;r
(braket
id|r
)braket
dot
id|codec
(braket
id|cidx
)braket
comma
id|reg
comma
id|rate
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;error in snd_ac97_set_rate: cidx=%d, reg=0x%x, rate=%d, err=%d&bslash;n&quot;
comma
id|cidx
comma
id|reg
comma
id|rate
comma
id|err
)paren
suffix:semicolon
r_else
id|reg_ok
op_or_assign
(paren
l_int|1
op_lshift
(paren
id|reg
op_minus
id|AC97_PCM_FRONT_DAC_RATE
)paren
)paren
suffix:semicolon
)brace
)brace
)brace
id|pcm-&gt;aslots
op_assign
id|slots
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|error
suffix:colon
id|pcm-&gt;aslots
op_assign
id|slots
suffix:semicolon
id|snd_ac97_pcm_close
c_func
(paren
id|pcm
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/**&n; * snd_ac97_pcm_close - closes the given AC97 pcm&n; * @pcm: the ac97 pcm instance&n; *&n; * It frees the locked AC97 slots.&n; */
DECL|function|snd_ac97_pcm_close
r_int
id|snd_ac97_pcm_close
c_func
(paren
r_struct
id|ac97_pcm
op_star
id|pcm
)paren
(brace
id|ac97_bus_t
op_star
id|bus
suffix:semicolon
r_int
r_int
id|slots
op_assign
id|pcm-&gt;aslots
suffix:semicolon
r_int
id|i
comma
id|cidx
suffix:semicolon
id|bus
op_assign
id|pcm-&gt;bus
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|pcm-&gt;bus-&gt;bus_lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|3
suffix:semicolon
id|i
OL
l_int|12
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|slots
op_amp
(paren
l_int|1
op_lshift
id|i
)paren
)paren
)paren
r_continue
suffix:semicolon
r_for
c_loop
(paren
id|cidx
op_assign
l_int|0
suffix:semicolon
id|cidx
OL
l_int|4
suffix:semicolon
id|cidx
op_increment
)paren
id|bus-&gt;used_slots
(braket
id|pcm-&gt;stream
)braket
(braket
id|cidx
)braket
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|i
)paren
suffix:semicolon
)brace
id|pcm-&gt;aslots
op_assign
l_int|0
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|pcm-&gt;bus-&gt;bus_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
