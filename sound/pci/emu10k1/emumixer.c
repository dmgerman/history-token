multiline_comment|/*&n; *  Copyright (c) by Jaroslav Kysela &lt;perex@suse.cz&gt;,&n; *                   Takashi Iwai &lt;tiwai@suse.de&gt;&n; *                   Creative Labs, Inc.&n; *  Routines for control of EMU10K1 chips / mixer routines&n; *&n; *  BUGS:&n; *    --&n; *&n; *  TODO:&n; *    --&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &lt;sound/emu10k1.h&gt;
DECL|macro|chip_t
mdefine_line|#define chip_t emu10k1_t
DECL|function|snd_emu10k1_spdif_info
r_static
r_int
id|snd_emu10k1_spdif_info
c_func
(paren
id|snd_kcontrol_t
op_star
id|kcontrol
comma
id|snd_ctl_elem_info_t
op_star
id|uinfo
)paren
(brace
id|uinfo-&gt;type
op_assign
id|SNDRV_CTL_ELEM_TYPE_IEC958
suffix:semicolon
id|uinfo-&gt;count
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_emu10k1_spdif_get
r_static
r_int
id|snd_emu10k1_spdif_get
c_func
(paren
id|snd_kcontrol_t
op_star
id|kcontrol
comma
id|snd_ctl_elem_value_t
op_star
id|ucontrol
)paren
(brace
id|emu10k1_t
op_star
id|emu
op_assign
id|snd_kcontrol_chip
c_func
(paren
id|kcontrol
)paren
suffix:semicolon
r_int
r_int
id|idx
op_assign
id|snd_ctl_get_ioffidx
c_func
(paren
id|kcontrol
comma
op_amp
id|ucontrol-&gt;id
)paren
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|emu-&gt;reg_lock
comma
id|flags
)paren
suffix:semicolon
id|ucontrol-&gt;value.iec958.status
(braket
l_int|0
)braket
op_assign
(paren
id|emu-&gt;spdif_bits
(braket
id|idx
)braket
op_rshift
l_int|0
)paren
op_amp
l_int|0xff
suffix:semicolon
id|ucontrol-&gt;value.iec958.status
(braket
l_int|1
)braket
op_assign
(paren
id|emu-&gt;spdif_bits
(braket
id|idx
)braket
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
suffix:semicolon
id|ucontrol-&gt;value.iec958.status
(braket
l_int|2
)braket
op_assign
(paren
id|emu-&gt;spdif_bits
(braket
id|idx
)braket
op_rshift
l_int|16
)paren
op_amp
l_int|0xff
suffix:semicolon
id|ucontrol-&gt;value.iec958.status
(braket
l_int|3
)braket
op_assign
(paren
id|emu-&gt;spdif_bits
(braket
id|idx
)braket
op_rshift
l_int|24
)paren
op_amp
l_int|0xff
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|emu-&gt;reg_lock
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_emu10k1_spdif_get_mask
r_static
r_int
id|snd_emu10k1_spdif_get_mask
c_func
(paren
id|snd_kcontrol_t
op_star
id|kcontrol
comma
id|snd_ctl_elem_value_t
op_star
id|ucontrol
)paren
(brace
id|ucontrol-&gt;value.iec958.status
(braket
l_int|0
)braket
op_assign
l_int|0xff
suffix:semicolon
id|ucontrol-&gt;value.iec958.status
(braket
l_int|1
)braket
op_assign
l_int|0xff
suffix:semicolon
id|ucontrol-&gt;value.iec958.status
(braket
l_int|2
)braket
op_assign
l_int|0xff
suffix:semicolon
id|ucontrol-&gt;value.iec958.status
(braket
l_int|3
)braket
op_assign
l_int|0xff
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_emu10k1_spdif_put
r_static
r_int
id|snd_emu10k1_spdif_put
c_func
(paren
id|snd_kcontrol_t
op_star
id|kcontrol
comma
id|snd_ctl_elem_value_t
op_star
id|ucontrol
)paren
(brace
id|emu10k1_t
op_star
id|emu
op_assign
id|snd_kcontrol_chip
c_func
(paren
id|kcontrol
)paren
suffix:semicolon
r_int
r_int
id|idx
op_assign
id|snd_ctl_get_ioffidx
c_func
(paren
id|kcontrol
comma
op_amp
id|ucontrol-&gt;id
)paren
suffix:semicolon
r_int
id|change
suffix:semicolon
r_int
r_int
id|val
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|val
op_assign
(paren
id|ucontrol-&gt;value.iec958.status
(braket
l_int|0
)braket
op_lshift
l_int|0
)paren
op_or
(paren
id|ucontrol-&gt;value.iec958.status
(braket
l_int|1
)braket
op_lshift
l_int|8
)paren
op_or
(paren
id|ucontrol-&gt;value.iec958.status
(braket
l_int|2
)braket
op_lshift
l_int|16
)paren
op_or
(paren
id|ucontrol-&gt;value.iec958.status
(braket
l_int|3
)braket
op_lshift
l_int|24
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|emu-&gt;reg_lock
comma
id|flags
)paren
suffix:semicolon
id|change
op_assign
id|val
op_ne
id|emu-&gt;spdif_bits
(braket
id|idx
)braket
suffix:semicolon
r_if
c_cond
(paren
id|change
)paren
(brace
id|snd_emu10k1_ptr_write
c_func
(paren
id|emu
comma
id|SPCS0
op_plus
id|idx
comma
l_int|0
comma
id|val
)paren
suffix:semicolon
id|emu-&gt;spdif_bits
(braket
id|idx
)braket
op_assign
id|val
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|emu-&gt;reg_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|change
suffix:semicolon
)brace
DECL|variable|snd_emu10k1_spdif_mask_control
r_static
id|snd_kcontrol_new_t
id|snd_emu10k1_spdif_mask_control
op_assign
(brace
dot
id|access
op_assign
id|SNDRV_CTL_ELEM_ACCESS_READ
comma
dot
id|iface
op_assign
id|SNDRV_CTL_ELEM_IFACE_MIXER
comma
dot
id|name
op_assign
id|SNDRV_CTL_NAME_IEC958
c_func
(paren
l_string|&quot;&quot;
comma
id|PLAYBACK
comma
id|MASK
)paren
comma
dot
id|count
op_assign
l_int|4
comma
dot
id|info
op_assign
id|snd_emu10k1_spdif_info
comma
dot
id|get
op_assign
id|snd_emu10k1_spdif_get_mask
)brace
suffix:semicolon
DECL|variable|snd_emu10k1_spdif_control
r_static
id|snd_kcontrol_new_t
id|snd_emu10k1_spdif_control
op_assign
(brace
dot
id|iface
op_assign
id|SNDRV_CTL_ELEM_IFACE_MIXER
comma
dot
id|name
op_assign
id|SNDRV_CTL_NAME_IEC958
c_func
(paren
l_string|&quot;&quot;
comma
id|PLAYBACK
comma
id|DEFAULT
)paren
comma
dot
id|count
op_assign
l_int|4
comma
dot
id|info
op_assign
id|snd_emu10k1_spdif_info
comma
dot
id|get
op_assign
id|snd_emu10k1_spdif_get
comma
dot
id|put
op_assign
id|snd_emu10k1_spdif_put
)brace
suffix:semicolon
DECL|function|update_emu10k1_fxrt
r_static
r_void
id|update_emu10k1_fxrt
c_func
(paren
id|emu10k1_t
op_star
id|emu
comma
r_int
id|voice
comma
r_int
r_char
op_star
id|route
)paren
(brace
r_if
c_cond
(paren
id|emu-&gt;audigy
)paren
(brace
id|snd_emu10k1_ptr_write
c_func
(paren
id|emu
comma
id|A_FXRT1
comma
id|voice
comma
id|snd_emu10k1_compose_audigy_fxrt1
c_func
(paren
id|route
)paren
)paren
suffix:semicolon
id|snd_emu10k1_ptr_write
c_func
(paren
id|emu
comma
id|A_FXRT2
comma
id|voice
comma
id|snd_emu10k1_compose_audigy_fxrt2
c_func
(paren
id|route
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|snd_emu10k1_ptr_write
c_func
(paren
id|emu
comma
id|FXRT
comma
id|voice
comma
id|snd_emu10k1_compose_send_routing
c_func
(paren
id|route
)paren
)paren
suffix:semicolon
)brace
)brace
DECL|function|update_emu10k1_send_volume
r_static
r_void
id|update_emu10k1_send_volume
c_func
(paren
id|emu10k1_t
op_star
id|emu
comma
r_int
id|voice
comma
r_int
r_char
op_star
id|volume
)paren
(brace
id|snd_emu10k1_ptr_write
c_func
(paren
id|emu
comma
id|PTRX_FXSENDAMOUNT_A
comma
id|voice
comma
id|volume
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|snd_emu10k1_ptr_write
c_func
(paren
id|emu
comma
id|PTRX_FXSENDAMOUNT_B
comma
id|voice
comma
id|volume
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|snd_emu10k1_ptr_write
c_func
(paren
id|emu
comma
id|PSST_FXSENDAMOUNT_C
comma
id|voice
comma
id|volume
(braket
l_int|2
)braket
)paren
suffix:semicolon
id|snd_emu10k1_ptr_write
c_func
(paren
id|emu
comma
id|DSL_FXSENDAMOUNT_D
comma
id|voice
comma
id|volume
(braket
l_int|3
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|emu-&gt;audigy
)paren
(brace
r_int
r_int
id|val
op_assign
(paren
(paren
r_int
r_int
)paren
id|volume
(braket
l_int|4
)braket
op_lshift
l_int|24
)paren
op_or
(paren
(paren
r_int
r_int
)paren
id|volume
(braket
l_int|5
)braket
op_lshift
l_int|16
)paren
op_or
(paren
(paren
r_int
r_int
)paren
id|volume
(braket
l_int|6
)braket
op_lshift
l_int|8
)paren
op_or
(paren
r_int
r_int
)paren
id|volume
(braket
l_int|7
)braket
suffix:semicolon
id|snd_emu10k1_ptr_write
c_func
(paren
id|emu
comma
id|A_SENDAMOUNTS
comma
id|voice
comma
id|val
)paren
suffix:semicolon
)brace
)brace
DECL|function|snd_emu10k1_send_routing_info
r_static
r_int
id|snd_emu10k1_send_routing_info
c_func
(paren
id|snd_kcontrol_t
op_star
id|kcontrol
comma
id|snd_ctl_elem_info_t
op_star
id|uinfo
)paren
(brace
id|emu10k1_t
op_star
id|emu
op_assign
id|snd_kcontrol_chip
c_func
(paren
id|kcontrol
)paren
suffix:semicolon
id|uinfo-&gt;type
op_assign
id|SNDRV_CTL_ELEM_TYPE_INTEGER
suffix:semicolon
id|uinfo-&gt;count
op_assign
id|emu-&gt;audigy
ques
c_cond
l_int|3
op_star
l_int|8
suffix:colon
l_int|3
op_star
l_int|4
suffix:semicolon
id|uinfo-&gt;value.integer.min
op_assign
l_int|0
suffix:semicolon
id|uinfo-&gt;value.integer.max
op_assign
id|emu-&gt;audigy
ques
c_cond
l_int|0x3f
suffix:colon
l_int|0x0f
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_emu10k1_send_routing_get
r_static
r_int
id|snd_emu10k1_send_routing_get
c_func
(paren
id|snd_kcontrol_t
op_star
id|kcontrol
comma
id|snd_ctl_elem_value_t
op_star
id|ucontrol
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|emu10k1_t
op_star
id|emu
op_assign
id|snd_kcontrol_chip
c_func
(paren
id|kcontrol
)paren
suffix:semicolon
id|emu10k1_pcm_mixer_t
op_star
id|mix
op_assign
op_amp
id|emu-&gt;pcm_mixer
(braket
id|snd_ctl_get_ioffidx
c_func
(paren
id|kcontrol
comma
op_amp
id|ucontrol-&gt;id
)paren
)braket
suffix:semicolon
r_int
id|voice
comma
id|idx
suffix:semicolon
r_int
id|num_efx
op_assign
id|emu-&gt;audigy
ques
c_cond
l_int|8
suffix:colon
l_int|4
suffix:semicolon
r_int
id|mask
op_assign
id|emu-&gt;audigy
ques
c_cond
l_int|0x3f
suffix:colon
l_int|0x0f
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|emu-&gt;reg_lock
comma
id|flags
)paren
suffix:semicolon
r_for
c_loop
(paren
id|voice
op_assign
l_int|0
suffix:semicolon
id|voice
OL
l_int|3
suffix:semicolon
id|voice
op_increment
)paren
r_for
c_loop
(paren
id|idx
op_assign
l_int|0
suffix:semicolon
id|idx
OL
id|num_efx
suffix:semicolon
id|idx
op_increment
)paren
id|ucontrol-&gt;value.integer.value
(braket
(paren
id|voice
op_star
id|num_efx
)paren
op_plus
id|idx
)braket
op_assign
id|mix-&gt;send_routing
(braket
id|voice
)braket
(braket
id|idx
)braket
op_amp
id|mask
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|emu-&gt;reg_lock
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_emu10k1_send_routing_put
r_static
r_int
id|snd_emu10k1_send_routing_put
c_func
(paren
id|snd_kcontrol_t
op_star
id|kcontrol
comma
id|snd_ctl_elem_value_t
op_star
id|ucontrol
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|emu10k1_t
op_star
id|emu
op_assign
id|snd_kcontrol_chip
c_func
(paren
id|kcontrol
)paren
suffix:semicolon
id|emu10k1_pcm_mixer_t
op_star
id|mix
op_assign
op_amp
id|emu-&gt;pcm_mixer
(braket
id|snd_ctl_get_ioffidx
c_func
(paren
id|kcontrol
comma
op_amp
id|ucontrol-&gt;id
)paren
)braket
suffix:semicolon
r_int
id|change
op_assign
l_int|0
comma
id|voice
comma
id|idx
comma
id|val
suffix:semicolon
r_int
id|num_efx
op_assign
id|emu-&gt;audigy
ques
c_cond
l_int|8
suffix:colon
l_int|4
suffix:semicolon
r_int
id|mask
op_assign
id|emu-&gt;audigy
ques
c_cond
l_int|0x3f
suffix:colon
l_int|0x0f
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|emu-&gt;reg_lock
comma
id|flags
)paren
suffix:semicolon
r_for
c_loop
(paren
id|voice
op_assign
l_int|0
suffix:semicolon
id|voice
OL
l_int|3
suffix:semicolon
id|voice
op_increment
)paren
r_for
c_loop
(paren
id|idx
op_assign
l_int|0
suffix:semicolon
id|idx
OL
id|num_efx
suffix:semicolon
id|idx
op_increment
)paren
(brace
id|val
op_assign
id|ucontrol-&gt;value.integer.value
(braket
(paren
id|voice
op_star
id|num_efx
)paren
op_plus
id|idx
)braket
op_amp
id|mask
suffix:semicolon
r_if
c_cond
(paren
id|mix-&gt;send_routing
(braket
id|voice
)braket
(braket
id|idx
)braket
op_ne
id|val
)paren
(brace
id|mix-&gt;send_routing
(braket
id|voice
)braket
(braket
id|idx
)braket
op_assign
id|val
suffix:semicolon
id|change
op_assign
l_int|1
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|change
op_logical_and
id|mix-&gt;epcm
)paren
(brace
r_if
c_cond
(paren
id|mix-&gt;epcm-&gt;voices
(braket
l_int|0
)braket
op_logical_and
id|mix-&gt;epcm-&gt;voices
(braket
l_int|1
)braket
)paren
(brace
id|update_emu10k1_fxrt
c_func
(paren
id|emu
comma
id|mix-&gt;epcm-&gt;voices
(braket
l_int|0
)braket
op_member_access_from_pointer
id|number
comma
op_amp
id|mix-&gt;send_routing
(braket
l_int|1
)braket
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|update_emu10k1_fxrt
c_func
(paren
id|emu
comma
id|mix-&gt;epcm-&gt;voices
(braket
l_int|1
)braket
op_member_access_from_pointer
id|number
comma
op_amp
id|mix-&gt;send_routing
(braket
l_int|2
)braket
(braket
l_int|0
)braket
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|mix-&gt;epcm-&gt;voices
(braket
l_int|0
)braket
)paren
(brace
id|update_emu10k1_fxrt
c_func
(paren
id|emu
comma
id|mix-&gt;epcm-&gt;voices
(braket
l_int|0
)braket
op_member_access_from_pointer
id|number
comma
op_amp
id|mix-&gt;send_routing
(braket
l_int|0
)braket
(braket
l_int|0
)braket
)paren
suffix:semicolon
)brace
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|emu-&gt;reg_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|change
suffix:semicolon
)brace
DECL|variable|snd_emu10k1_send_routing_control
r_static
id|snd_kcontrol_new_t
id|snd_emu10k1_send_routing_control
op_assign
(brace
dot
id|access
op_assign
id|SNDRV_CTL_ELEM_ACCESS_READWRITE
op_or
id|SNDRV_CTL_ELEM_ACCESS_INACTIVE
comma
dot
id|iface
op_assign
id|SNDRV_CTL_ELEM_IFACE_MIXER
comma
dot
id|name
op_assign
l_string|&quot;EMU10K1 PCM Send Routing&quot;
comma
dot
id|count
op_assign
l_int|32
comma
dot
id|info
op_assign
id|snd_emu10k1_send_routing_info
comma
dot
id|get
op_assign
id|snd_emu10k1_send_routing_get
comma
dot
id|put
op_assign
id|snd_emu10k1_send_routing_put
)brace
suffix:semicolon
DECL|function|snd_emu10k1_send_volume_info
r_static
r_int
id|snd_emu10k1_send_volume_info
c_func
(paren
id|snd_kcontrol_t
op_star
id|kcontrol
comma
id|snd_ctl_elem_info_t
op_star
id|uinfo
)paren
(brace
id|emu10k1_t
op_star
id|emu
op_assign
id|snd_kcontrol_chip
c_func
(paren
id|kcontrol
)paren
suffix:semicolon
id|uinfo-&gt;type
op_assign
id|SNDRV_CTL_ELEM_TYPE_INTEGER
suffix:semicolon
id|uinfo-&gt;count
op_assign
id|emu-&gt;audigy
ques
c_cond
l_int|3
op_star
l_int|8
suffix:colon
l_int|3
op_star
l_int|4
suffix:semicolon
id|uinfo-&gt;value.integer.min
op_assign
l_int|0
suffix:semicolon
id|uinfo-&gt;value.integer.max
op_assign
l_int|255
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_emu10k1_send_volume_get
r_static
r_int
id|snd_emu10k1_send_volume_get
c_func
(paren
id|snd_kcontrol_t
op_star
id|kcontrol
comma
id|snd_ctl_elem_value_t
op_star
id|ucontrol
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|emu10k1_t
op_star
id|emu
op_assign
id|snd_kcontrol_chip
c_func
(paren
id|kcontrol
)paren
suffix:semicolon
id|emu10k1_pcm_mixer_t
op_star
id|mix
op_assign
op_amp
id|emu-&gt;pcm_mixer
(braket
id|snd_ctl_get_ioffidx
c_func
(paren
id|kcontrol
comma
op_amp
id|ucontrol-&gt;id
)paren
)braket
suffix:semicolon
r_int
id|idx
suffix:semicolon
r_int
id|num_efx
op_assign
id|emu-&gt;audigy
ques
c_cond
l_int|8
suffix:colon
l_int|4
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|emu-&gt;reg_lock
comma
id|flags
)paren
suffix:semicolon
r_for
c_loop
(paren
id|idx
op_assign
l_int|0
suffix:semicolon
id|idx
OL
l_int|3
op_star
id|num_efx
suffix:semicolon
id|idx
op_increment
)paren
id|ucontrol-&gt;value.integer.value
(braket
id|idx
)braket
op_assign
id|mix-&gt;send_volume
(braket
id|idx
op_div
id|num_efx
)braket
(braket
id|idx
op_mod
id|num_efx
)braket
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|emu-&gt;reg_lock
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_emu10k1_send_volume_put
r_static
r_int
id|snd_emu10k1_send_volume_put
c_func
(paren
id|snd_kcontrol_t
op_star
id|kcontrol
comma
id|snd_ctl_elem_value_t
op_star
id|ucontrol
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|emu10k1_t
op_star
id|emu
op_assign
id|snd_kcontrol_chip
c_func
(paren
id|kcontrol
)paren
suffix:semicolon
id|emu10k1_pcm_mixer_t
op_star
id|mix
op_assign
op_amp
id|emu-&gt;pcm_mixer
(braket
id|snd_ctl_get_ioffidx
c_func
(paren
id|kcontrol
comma
op_amp
id|ucontrol-&gt;id
)paren
)braket
suffix:semicolon
r_int
id|change
op_assign
l_int|0
comma
id|idx
comma
id|val
suffix:semicolon
r_int
id|num_efx
op_assign
id|emu-&gt;audigy
ques
c_cond
l_int|8
suffix:colon
l_int|4
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|emu-&gt;reg_lock
comma
id|flags
)paren
suffix:semicolon
r_for
c_loop
(paren
id|idx
op_assign
l_int|0
suffix:semicolon
id|idx
OL
l_int|3
op_star
id|num_efx
suffix:semicolon
id|idx
op_increment
)paren
(brace
id|val
op_assign
id|ucontrol-&gt;value.integer.value
(braket
id|idx
)braket
op_amp
l_int|255
suffix:semicolon
r_if
c_cond
(paren
id|mix-&gt;send_volume
(braket
id|idx
op_div
id|num_efx
)braket
(braket
id|idx
op_mod
id|num_efx
)braket
op_ne
id|val
)paren
(brace
id|mix-&gt;send_volume
(braket
id|idx
op_div
id|num_efx
)braket
(braket
id|idx
op_mod
id|num_efx
)braket
op_assign
id|val
suffix:semicolon
id|change
op_assign
l_int|1
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|change
op_logical_and
id|mix-&gt;epcm
)paren
(brace
r_if
c_cond
(paren
id|mix-&gt;epcm-&gt;voices
(braket
l_int|0
)braket
op_logical_and
id|mix-&gt;epcm-&gt;voices
(braket
l_int|1
)braket
)paren
(brace
id|update_emu10k1_send_volume
c_func
(paren
id|emu
comma
id|mix-&gt;epcm-&gt;voices
(braket
l_int|0
)braket
op_member_access_from_pointer
id|number
comma
op_amp
id|mix-&gt;send_volume
(braket
l_int|1
)braket
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|update_emu10k1_send_volume
c_func
(paren
id|emu
comma
id|mix-&gt;epcm-&gt;voices
(braket
l_int|1
)braket
op_member_access_from_pointer
id|number
comma
op_amp
id|mix-&gt;send_volume
(braket
l_int|2
)braket
(braket
l_int|0
)braket
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|mix-&gt;epcm-&gt;voices
(braket
l_int|0
)braket
)paren
(brace
id|update_emu10k1_send_volume
c_func
(paren
id|emu
comma
id|mix-&gt;epcm-&gt;voices
(braket
l_int|0
)braket
op_member_access_from_pointer
id|number
comma
op_amp
id|mix-&gt;send_volume
(braket
l_int|0
)braket
(braket
l_int|0
)braket
)paren
suffix:semicolon
)brace
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|emu-&gt;reg_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|change
suffix:semicolon
)brace
DECL|variable|snd_emu10k1_send_volume_control
r_static
id|snd_kcontrol_new_t
id|snd_emu10k1_send_volume_control
op_assign
(brace
dot
id|access
op_assign
id|SNDRV_CTL_ELEM_ACCESS_READWRITE
op_or
id|SNDRV_CTL_ELEM_ACCESS_INACTIVE
comma
dot
id|iface
op_assign
id|SNDRV_CTL_ELEM_IFACE_MIXER
comma
dot
id|name
op_assign
l_string|&quot;EMU10K1 PCM Send Volume&quot;
comma
dot
id|count
op_assign
l_int|32
comma
dot
id|info
op_assign
id|snd_emu10k1_send_volume_info
comma
dot
id|get
op_assign
id|snd_emu10k1_send_volume_get
comma
dot
id|put
op_assign
id|snd_emu10k1_send_volume_put
)brace
suffix:semicolon
DECL|function|snd_emu10k1_attn_info
r_static
r_int
id|snd_emu10k1_attn_info
c_func
(paren
id|snd_kcontrol_t
op_star
id|kcontrol
comma
id|snd_ctl_elem_info_t
op_star
id|uinfo
)paren
(brace
id|uinfo-&gt;type
op_assign
id|SNDRV_CTL_ELEM_TYPE_INTEGER
suffix:semicolon
id|uinfo-&gt;count
op_assign
l_int|3
suffix:semicolon
id|uinfo-&gt;value.integer.min
op_assign
l_int|0
suffix:semicolon
id|uinfo-&gt;value.integer.max
op_assign
l_int|0xffff
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_emu10k1_attn_get
r_static
r_int
id|snd_emu10k1_attn_get
c_func
(paren
id|snd_kcontrol_t
op_star
id|kcontrol
comma
id|snd_ctl_elem_value_t
op_star
id|ucontrol
)paren
(brace
id|emu10k1_t
op_star
id|emu
op_assign
id|snd_kcontrol_chip
c_func
(paren
id|kcontrol
)paren
suffix:semicolon
id|emu10k1_pcm_mixer_t
op_star
id|mix
op_assign
op_amp
id|emu-&gt;pcm_mixer
(braket
id|snd_ctl_get_ioffidx
c_func
(paren
id|kcontrol
comma
op_amp
id|ucontrol-&gt;id
)paren
)braket
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
id|idx
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|emu-&gt;reg_lock
comma
id|flags
)paren
suffix:semicolon
r_for
c_loop
(paren
id|idx
op_assign
l_int|0
suffix:semicolon
id|idx
OL
l_int|3
suffix:semicolon
id|idx
op_increment
)paren
id|ucontrol-&gt;value.integer.value
(braket
id|idx
)braket
op_assign
id|mix-&gt;attn
(braket
id|idx
)braket
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|emu-&gt;reg_lock
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_emu10k1_attn_put
r_static
r_int
id|snd_emu10k1_attn_put
c_func
(paren
id|snd_kcontrol_t
op_star
id|kcontrol
comma
id|snd_ctl_elem_value_t
op_star
id|ucontrol
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|emu10k1_t
op_star
id|emu
op_assign
id|snd_kcontrol_chip
c_func
(paren
id|kcontrol
)paren
suffix:semicolon
id|emu10k1_pcm_mixer_t
op_star
id|mix
op_assign
op_amp
id|emu-&gt;pcm_mixer
(braket
id|snd_ctl_get_ioffidx
c_func
(paren
id|kcontrol
comma
op_amp
id|ucontrol-&gt;id
)paren
)braket
suffix:semicolon
r_int
id|change
op_assign
l_int|0
comma
id|idx
comma
id|val
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|emu-&gt;reg_lock
comma
id|flags
)paren
suffix:semicolon
r_for
c_loop
(paren
id|idx
op_assign
l_int|0
suffix:semicolon
id|idx
OL
l_int|3
suffix:semicolon
id|idx
op_increment
)paren
(brace
id|val
op_assign
id|ucontrol-&gt;value.integer.value
(braket
id|idx
)braket
op_amp
l_int|0xffff
suffix:semicolon
r_if
c_cond
(paren
id|mix-&gt;attn
(braket
id|idx
)braket
op_ne
id|val
)paren
(brace
id|mix-&gt;attn
(braket
id|idx
)braket
op_assign
id|val
suffix:semicolon
id|change
op_assign
l_int|1
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|change
op_logical_and
id|mix-&gt;epcm
)paren
(brace
r_if
c_cond
(paren
id|mix-&gt;epcm-&gt;voices
(braket
l_int|0
)braket
op_logical_and
id|mix-&gt;epcm-&gt;voices
(braket
l_int|1
)braket
)paren
(brace
id|snd_emu10k1_ptr_write
c_func
(paren
id|emu
comma
id|VTFT_VOLUMETARGET
comma
id|mix-&gt;epcm-&gt;voices
(braket
l_int|0
)braket
op_member_access_from_pointer
id|number
comma
id|mix-&gt;attn
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|snd_emu10k1_ptr_write
c_func
(paren
id|emu
comma
id|VTFT_VOLUMETARGET
comma
id|mix-&gt;epcm-&gt;voices
(braket
l_int|1
)braket
op_member_access_from_pointer
id|number
comma
id|mix-&gt;attn
(braket
l_int|2
)braket
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|mix-&gt;epcm-&gt;voices
(braket
l_int|0
)braket
)paren
(brace
id|snd_emu10k1_ptr_write
c_func
(paren
id|emu
comma
id|VTFT_VOLUMETARGET
comma
id|mix-&gt;epcm-&gt;voices
(braket
l_int|0
)braket
op_member_access_from_pointer
id|number
comma
id|mix-&gt;attn
(braket
l_int|0
)braket
)paren
suffix:semicolon
)brace
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|emu-&gt;reg_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|change
suffix:semicolon
)brace
DECL|variable|snd_emu10k1_attn_control
r_static
id|snd_kcontrol_new_t
id|snd_emu10k1_attn_control
op_assign
(brace
dot
id|access
op_assign
id|SNDRV_CTL_ELEM_ACCESS_READWRITE
op_or
id|SNDRV_CTL_ELEM_ACCESS_INACTIVE
comma
dot
id|iface
op_assign
id|SNDRV_CTL_ELEM_IFACE_MIXER
comma
dot
id|name
op_assign
l_string|&quot;EMU10K1 PCM Volume&quot;
comma
dot
id|count
op_assign
l_int|32
comma
dot
id|info
op_assign
id|snd_emu10k1_attn_info
comma
dot
id|get
op_assign
id|snd_emu10k1_attn_get
comma
dot
id|put
op_assign
id|snd_emu10k1_attn_put
)brace
suffix:semicolon
DECL|function|snd_emu10k1_shared_spdif_info
r_static
r_int
id|snd_emu10k1_shared_spdif_info
c_func
(paren
id|snd_kcontrol_t
op_star
id|kcontrol
comma
id|snd_ctl_elem_info_t
op_star
id|uinfo
)paren
(brace
id|uinfo-&gt;type
op_assign
id|SNDRV_CTL_ELEM_TYPE_BOOLEAN
suffix:semicolon
id|uinfo-&gt;count
op_assign
l_int|1
suffix:semicolon
id|uinfo-&gt;value.integer.min
op_assign
l_int|0
suffix:semicolon
id|uinfo-&gt;value.integer.max
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_emu10k1_shared_spdif_get
r_static
r_int
id|snd_emu10k1_shared_spdif_get
c_func
(paren
id|snd_kcontrol_t
op_star
id|kcontrol
comma
id|snd_ctl_elem_value_t
op_star
id|ucontrol
)paren
(brace
id|emu10k1_t
op_star
id|emu
op_assign
id|snd_kcontrol_chip
c_func
(paren
id|kcontrol
)paren
suffix:semicolon
r_if
c_cond
(paren
id|emu-&gt;audigy
)paren
id|ucontrol-&gt;value.integer.value
(braket
l_int|0
)braket
op_assign
id|inl
c_func
(paren
id|emu-&gt;port
op_plus
id|A_IOCFG
)paren
op_amp
id|A_IOCFG_GPOUT0
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
r_else
id|ucontrol-&gt;value.integer.value
(braket
l_int|0
)braket
op_assign
id|inl
c_func
(paren
id|emu-&gt;port
op_plus
id|HCFG
)paren
op_amp
id|HCFG_GPOUT0
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_emu10k1_shared_spdif_put
r_static
r_int
id|snd_emu10k1_shared_spdif_put
c_func
(paren
id|snd_kcontrol_t
op_star
id|kcontrol
comma
id|snd_ctl_elem_value_t
op_star
id|ucontrol
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|emu10k1_t
op_star
id|emu
op_assign
id|snd_kcontrol_chip
c_func
(paren
id|kcontrol
)paren
suffix:semicolon
r_int
r_int
id|reg
comma
id|val
suffix:semicolon
r_int
id|change
op_assign
l_int|0
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|emu-&gt;reg_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|emu-&gt;audigy
)paren
(brace
id|reg
op_assign
id|inl
c_func
(paren
id|emu-&gt;port
op_plus
id|A_IOCFG
)paren
suffix:semicolon
id|val
op_assign
id|ucontrol-&gt;value.integer.value
(braket
l_int|0
)braket
ques
c_cond
id|A_IOCFG_GPOUT0
suffix:colon
l_int|0
suffix:semicolon
id|change
op_assign
(paren
id|reg
op_amp
id|A_IOCFG_GPOUT0
)paren
op_ne
id|val
suffix:semicolon
r_if
c_cond
(paren
id|change
)paren
(brace
id|reg
op_and_assign
op_complement
id|A_IOCFG_GPOUT0
suffix:semicolon
id|reg
op_or_assign
id|val
suffix:semicolon
id|outl
c_func
(paren
id|reg
op_or
id|val
comma
id|emu-&gt;port
op_plus
id|A_IOCFG
)paren
suffix:semicolon
)brace
)brace
id|reg
op_assign
id|inl
c_func
(paren
id|emu-&gt;port
op_plus
id|HCFG
)paren
suffix:semicolon
id|val
op_assign
id|ucontrol-&gt;value.integer.value
(braket
l_int|0
)braket
ques
c_cond
id|HCFG_GPOUT0
suffix:colon
l_int|0
suffix:semicolon
id|change
op_or_assign
(paren
id|reg
op_amp
id|HCFG_GPOUT0
)paren
op_ne
id|val
suffix:semicolon
r_if
c_cond
(paren
id|change
)paren
(brace
id|reg
op_and_assign
op_complement
id|HCFG_GPOUT0
suffix:semicolon
id|reg
op_or_assign
id|val
suffix:semicolon
id|outl
c_func
(paren
id|reg
op_or
id|val
comma
id|emu-&gt;port
op_plus
id|HCFG
)paren
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|emu-&gt;reg_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|change
suffix:semicolon
)brace
DECL|variable|__devinitdata
r_static
id|snd_kcontrol_new_t
id|snd_emu10k1_shared_spdif
id|__devinitdata
op_assign
(brace
dot
id|iface
op_assign
id|SNDRV_CTL_ELEM_IFACE_MIXER
comma
dot
id|name
op_assign
l_string|&quot;SB Live Analog/Digital Output Jack&quot;
comma
dot
id|info
op_assign
id|snd_emu10k1_shared_spdif_info
comma
dot
id|get
op_assign
id|snd_emu10k1_shared_spdif_get
comma
dot
id|put
op_assign
id|snd_emu10k1_shared_spdif_put
)brace
suffix:semicolon
DECL|variable|__devinitdata
r_static
id|snd_kcontrol_new_t
id|snd_audigy_shared_spdif
id|__devinitdata
op_assign
(brace
dot
id|iface
op_assign
id|SNDRV_CTL_ELEM_IFACE_MIXER
comma
dot
id|name
op_assign
l_string|&quot;Audigy Analog/Digital Output Jack&quot;
comma
dot
id|info
op_assign
id|snd_emu10k1_shared_spdif_info
comma
dot
id|get
op_assign
id|snd_emu10k1_shared_spdif_get
comma
dot
id|put
op_assign
id|snd_emu10k1_shared_spdif_put
)brace
suffix:semicolon
multiline_comment|/*&n; */
DECL|function|snd_emu10k1_mixer_free_ac97
r_static
r_void
id|snd_emu10k1_mixer_free_ac97
c_func
(paren
id|ac97_t
op_star
id|ac97
)paren
(brace
id|emu10k1_t
op_star
id|emu
op_assign
id|snd_magic_cast
c_func
(paren
id|emu10k1_t
comma
id|ac97-&gt;private_data
comma
r_return
)paren
suffix:semicolon
id|emu-&gt;ac97
op_assign
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; */
DECL|function|remove_ctl
r_static
r_int
id|remove_ctl
c_func
(paren
id|snd_card_t
op_star
id|card
comma
r_const
r_char
op_star
id|name
)paren
(brace
id|snd_ctl_elem_id_t
id|id
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|id
comma
l_int|0
comma
r_sizeof
(paren
id|id
)paren
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|id.name
comma
id|name
)paren
suffix:semicolon
id|id.iface
op_assign
id|SNDRV_CTL_ELEM_IFACE_MIXER
suffix:semicolon
r_return
id|snd_ctl_remove_id
c_func
(paren
id|card
comma
op_amp
id|id
)paren
suffix:semicolon
)brace
DECL|function|ctl_find
r_static
id|snd_kcontrol_t
op_star
id|ctl_find
c_func
(paren
id|snd_card_t
op_star
id|card
comma
r_const
r_char
op_star
id|name
)paren
(brace
id|snd_ctl_elem_id_t
id|sid
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|sid
comma
l_int|0
comma
r_sizeof
(paren
id|sid
)paren
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|sid.name
comma
id|name
)paren
suffix:semicolon
id|sid.iface
op_assign
id|SNDRV_CTL_ELEM_IFACE_MIXER
suffix:semicolon
r_return
id|snd_ctl_find_id
c_func
(paren
id|card
comma
op_amp
id|sid
)paren
suffix:semicolon
)brace
DECL|function|rename_ctl
r_static
r_int
id|rename_ctl
c_func
(paren
id|snd_card_t
op_star
id|card
comma
r_const
r_char
op_star
id|src
comma
r_const
r_char
op_star
id|dst
)paren
(brace
id|snd_kcontrol_t
op_star
id|kctl
op_assign
id|ctl_find
c_func
(paren
id|card
comma
id|src
)paren
suffix:semicolon
r_if
c_cond
(paren
id|kctl
)paren
(brace
id|strcpy
c_func
(paren
id|kctl-&gt;id.name
comma
id|dst
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
op_minus
id|ENOENT
suffix:semicolon
)brace
DECL|function|snd_emu10k1_mixer
r_int
id|__devinit
id|snd_emu10k1_mixer
c_func
(paren
id|emu10k1_t
op_star
id|emu
)paren
(brace
id|ac97_t
id|ac97
suffix:semicolon
r_int
id|err
comma
id|pcm
suffix:semicolon
id|snd_kcontrol_t
op_star
id|kctl
suffix:semicolon
id|snd_card_t
op_star
id|card
op_assign
id|emu-&gt;card
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|emu-&gt;no_ac97
)paren
(brace
id|memset
c_func
(paren
op_amp
id|ac97
comma
l_int|0
comma
r_sizeof
(paren
id|ac97
)paren
)paren
suffix:semicolon
id|ac97.write
op_assign
id|snd_emu10k1_ac97_write
suffix:semicolon
id|ac97.read
op_assign
id|snd_emu10k1_ac97_read
suffix:semicolon
id|ac97.private_data
op_assign
id|emu
suffix:semicolon
id|ac97.private_free
op_assign
id|snd_emu10k1_mixer_free_ac97
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_ac97_mixer
c_func
(paren
id|emu-&gt;card
comma
op_amp
id|ac97
comma
op_amp
id|emu-&gt;ac97
)paren
)paren
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
r_if
c_cond
(paren
id|emu-&gt;audigy
op_logical_and
id|emu-&gt;revision
op_eq
l_int|4
)paren
(brace
multiline_comment|/* Master/PCM controls on ac97 of Audigy2 has no effect */
multiline_comment|/* FIXME: keep master volume/switch to be sure.&n;&t;&t;&t; * once after we check that they play really no roles,&n;&t;&t;&t; * they shall be removed.&n;&t;&t;&t; */
id|rename_ctl
c_func
(paren
id|card
comma
l_string|&quot;Master Playback Switch&quot;
comma
l_string|&quot;AC97 Master Playback Switch&quot;
)paren
suffix:semicolon
id|rename_ctl
c_func
(paren
id|card
comma
l_string|&quot;Master Playback Volume&quot;
comma
l_string|&quot;AC97 Master Playback Volume&quot;
)paren
suffix:semicolon
multiline_comment|/* pcm controls are removed */
id|remove_ctl
c_func
(paren
id|card
comma
l_string|&quot;PCM Playback Switch&quot;
)paren
suffix:semicolon
id|remove_ctl
c_func
(paren
id|card
comma
l_string|&quot;PCM Playback Volume&quot;
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
id|emu-&gt;APS
)paren
id|strcpy
c_func
(paren
id|emu-&gt;card-&gt;mixername
comma
l_string|&quot;EMU APS&quot;
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|emu-&gt;audigy
)paren
id|strcpy
c_func
(paren
id|emu-&gt;card-&gt;mixername
comma
l_string|&quot;SB Audigy&quot;
)paren
suffix:semicolon
r_else
id|strcpy
c_func
(paren
id|emu-&gt;card-&gt;mixername
comma
l_string|&quot;Emu10k1&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|emu-&gt;audigy
op_logical_and
id|emu-&gt;revision
op_eq
l_int|4
)paren
(brace
multiline_comment|/* Audigy2 and Audigy2 EX */
multiline_comment|/* use the conventional names */
id|rename_ctl
c_func
(paren
id|card
comma
l_string|&quot;Wave Playback Volume&quot;
comma
l_string|&quot;PCM Playback Volume&quot;
)paren
suffix:semicolon
id|rename_ctl
c_func
(paren
id|card
comma
l_string|&quot;Wave Playback Volume&quot;
comma
l_string|&quot;PCM Capture Volume&quot;
)paren
suffix:semicolon
id|rename_ctl
c_func
(paren
id|card
comma
l_string|&quot;Wave Master Playback Volume&quot;
comma
l_string|&quot;Master Playback Volume&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|kctl
op_assign
id|emu-&gt;ctl_send_routing
op_assign
id|snd_ctl_new1
c_func
(paren
op_amp
id|snd_emu10k1_send_routing_control
comma
id|emu
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_ctl_add
c_func
(paren
id|card
comma
id|kctl
)paren
)paren
)paren
r_return
id|err
suffix:semicolon
r_if
c_cond
(paren
(paren
id|kctl
op_assign
id|emu-&gt;ctl_send_volume
op_assign
id|snd_ctl_new1
c_func
(paren
op_amp
id|snd_emu10k1_send_volume_control
comma
id|emu
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_ctl_add
c_func
(paren
id|card
comma
id|kctl
)paren
)paren
)paren
r_return
id|err
suffix:semicolon
r_if
c_cond
(paren
(paren
id|kctl
op_assign
id|emu-&gt;ctl_attn
op_assign
id|snd_ctl_new1
c_func
(paren
op_amp
id|snd_emu10k1_attn_control
comma
id|emu
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_ctl_add
c_func
(paren
id|card
comma
id|kctl
)paren
)paren
)paren
r_return
id|err
suffix:semicolon
multiline_comment|/* intiailize the routing and volume table for each pcm playback stream */
r_for
c_loop
(paren
id|pcm
op_assign
l_int|0
suffix:semicolon
id|pcm
OL
l_int|32
suffix:semicolon
id|pcm
op_increment
)paren
(brace
id|emu10k1_pcm_mixer_t
op_star
id|mix
suffix:semicolon
r_int
id|v
suffix:semicolon
id|mix
op_assign
op_amp
id|emu-&gt;pcm_mixer
(braket
id|pcm
)braket
suffix:semicolon
id|mix-&gt;epcm
op_assign
l_int|NULL
suffix:semicolon
r_for
c_loop
(paren
id|v
op_assign
l_int|0
suffix:semicolon
id|v
OL
l_int|4
suffix:semicolon
id|v
op_increment
)paren
id|mix-&gt;send_routing
(braket
l_int|0
)braket
(braket
id|v
)braket
op_assign
id|mix-&gt;send_routing
(braket
l_int|1
)braket
(braket
id|v
)braket
op_assign
id|mix-&gt;send_routing
(braket
l_int|2
)braket
(braket
id|v
)braket
op_assign
id|v
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|mix-&gt;send_volume
comma
l_int|0
comma
r_sizeof
(paren
id|mix-&gt;send_volume
)paren
)paren
suffix:semicolon
id|mix-&gt;send_volume
(braket
l_int|0
)braket
(braket
l_int|0
)braket
op_assign
id|mix-&gt;send_volume
(braket
l_int|0
)braket
(braket
l_int|1
)braket
op_assign
id|mix-&gt;send_volume
(braket
l_int|1
)braket
(braket
l_int|0
)braket
op_assign
id|mix-&gt;send_volume
(braket
l_int|2
)braket
(braket
l_int|1
)braket
op_assign
l_int|255
suffix:semicolon
id|mix-&gt;attn
(braket
l_int|0
)braket
op_assign
id|mix-&gt;attn
(braket
l_int|1
)braket
op_assign
id|mix-&gt;attn
(braket
l_int|2
)braket
op_assign
l_int|0xffff
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|emu-&gt;APS
)paren
(brace
multiline_comment|/* FIXME: APS has these controls? */
multiline_comment|/* sb live! and audigy */
r_if
c_cond
(paren
(paren
id|kctl
op_assign
id|snd_ctl_new1
c_func
(paren
op_amp
id|snd_emu10k1_spdif_mask_control
comma
id|emu
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_ctl_add
c_func
(paren
id|card
comma
id|kctl
)paren
)paren
)paren
r_return
id|err
suffix:semicolon
r_if
c_cond
(paren
(paren
id|kctl
op_assign
id|snd_ctl_new1
c_func
(paren
op_amp
id|snd_emu10k1_spdif_control
comma
id|emu
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_ctl_add
c_func
(paren
id|card
comma
id|kctl
)paren
)paren
)paren
r_return
id|err
suffix:semicolon
)brace
r_if
c_cond
(paren
id|emu-&gt;audigy
)paren
(brace
r_if
c_cond
(paren
(paren
id|kctl
op_assign
id|snd_ctl_new1
c_func
(paren
op_amp
id|snd_audigy_shared_spdif
comma
id|emu
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_ctl_add
c_func
(paren
id|card
comma
id|kctl
)paren
)paren
)paren
r_return
id|err
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|emu-&gt;APS
)paren
(brace
multiline_comment|/* sb live! */
r_if
c_cond
(paren
(paren
id|kctl
op_assign
id|snd_ctl_new1
c_func
(paren
op_amp
id|snd_emu10k1_shared_spdif
comma
id|emu
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_ctl_add
c_func
(paren
id|card
comma
id|kctl
)paren
)paren
)paren
r_return
id|err
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
