multiline_comment|/*&n; *   IWFFFF - AMD InterWave (tm) - Instrument routines&n; *   Copyright (c) 1999 by Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &lt;sound/ainstr_iw.h&gt;
macro_line|#include &lt;sound/initval.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Jaroslav Kysela &lt;perex@suse.cz&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Advanced Linux Sound Architecture IWFFFF support.&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|function|snd_seq_iwffff_size
r_static
r_int
r_int
id|snd_seq_iwffff_size
c_func
(paren
r_int
r_int
id|size
comma
r_int
r_int
id|format
)paren
(brace
r_int
r_int
id|result
op_assign
id|size
suffix:semicolon
r_if
c_cond
(paren
id|format
op_amp
id|IWFFFF_WAVE_16BIT
)paren
id|result
op_lshift_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|format
op_amp
id|IWFFFF_WAVE_STEREO
)paren
id|result
op_lshift_assign
l_int|1
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|function|snd_seq_iwffff_copy_lfo_from_stream
r_static
r_void
id|snd_seq_iwffff_copy_lfo_from_stream
c_func
(paren
id|iwffff_lfo_t
op_star
id|fp
comma
id|iwffff_xlfo_t
op_star
id|fx
)paren
(brace
id|fp-&gt;freq
op_assign
id|le16_to_cpu
c_func
(paren
id|fx-&gt;freq
)paren
suffix:semicolon
id|fp-&gt;depth
op_assign
id|le16_to_cpu
c_func
(paren
id|fx-&gt;depth
)paren
suffix:semicolon
id|fp-&gt;sweep
op_assign
id|le16_to_cpu
c_func
(paren
id|fx-&gt;sweep
)paren
suffix:semicolon
id|fp-&gt;shape
op_assign
id|fx-&gt;shape
suffix:semicolon
id|fp-&gt;delay
op_assign
id|fx-&gt;delay
suffix:semicolon
)brace
DECL|function|snd_seq_iwffff_copy_env_from_stream
r_static
r_int
id|snd_seq_iwffff_copy_env_from_stream
c_func
(paren
id|__u32
id|req_stype
comma
id|iwffff_layer_t
op_star
id|lp
comma
id|iwffff_env_t
op_star
id|ep
comma
id|iwffff_xenv_t
op_star
id|ex
comma
r_char
id|__user
op_star
op_star
id|data
comma
r_int
op_star
id|len
comma
r_int
id|gfp_mask
)paren
(brace
id|__u32
id|stype
suffix:semicolon
id|iwffff_env_record_t
op_star
id|rp
comma
op_star
id|rp_last
suffix:semicolon
id|iwffff_xenv_record_t
id|rx
suffix:semicolon
id|iwffff_env_point_t
op_star
id|pp
suffix:semicolon
id|iwffff_xenv_point_t
id|px
suffix:semicolon
r_int
id|points_size
comma
id|idx
suffix:semicolon
id|ep-&gt;flags
op_assign
id|ex-&gt;flags
suffix:semicolon
id|ep-&gt;mode
op_assign
id|ex-&gt;mode
suffix:semicolon
id|ep-&gt;index
op_assign
id|ex-&gt;index
suffix:semicolon
id|rp_last
op_assign
l_int|NULL
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_if
c_cond
(paren
op_star
id|len
OL
(paren
r_int
)paren
r_sizeof
(paren
id|__u32
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|stype
comma
op_star
id|data
comma
r_sizeof
(paren
id|stype
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|stype
op_eq
id|IWFFFF_STRU_WAVE
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|req_stype
op_ne
id|stype
)paren
(brace
r_if
c_cond
(paren
id|stype
op_eq
id|IWFFFF_STRU_ENV_RECP
op_logical_or
id|stype
op_eq
id|IWFFFF_STRU_ENV_RECV
)paren
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_star
id|len
OL
(paren
r_int
)paren
r_sizeof
(paren
id|rx
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|rx
comma
op_star
id|data
comma
r_sizeof
(paren
id|rx
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
op_star
id|data
op_add_assign
r_sizeof
(paren
id|rx
)paren
suffix:semicolon
op_star
id|len
op_sub_assign
r_sizeof
(paren
id|rx
)paren
suffix:semicolon
id|points_size
op_assign
(paren
id|le16_to_cpu
c_func
(paren
id|rx.nattack
)paren
op_plus
id|le16_to_cpu
c_func
(paren
id|rx.nrelease
)paren
)paren
op_star
l_int|2
op_star
r_sizeof
(paren
id|__u16
)paren
suffix:semicolon
r_if
c_cond
(paren
id|points_size
OG
op_star
id|len
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|rp
op_assign
id|kcalloc
c_func
(paren
l_int|1
comma
r_sizeof
(paren
op_star
id|rp
)paren
op_plus
id|points_size
comma
id|gfp_mask
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rp
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|rp-&gt;nattack
op_assign
id|le16_to_cpu
c_func
(paren
id|rx.nattack
)paren
suffix:semicolon
id|rp-&gt;nrelease
op_assign
id|le16_to_cpu
c_func
(paren
id|rx.nrelease
)paren
suffix:semicolon
id|rp-&gt;sustain_offset
op_assign
id|le16_to_cpu
c_func
(paren
id|rx.sustain_offset
)paren
suffix:semicolon
id|rp-&gt;sustain_rate
op_assign
id|le16_to_cpu
c_func
(paren
id|rx.sustain_rate
)paren
suffix:semicolon
id|rp-&gt;release_rate
op_assign
id|le16_to_cpu
c_func
(paren
id|rx.release_rate
)paren
suffix:semicolon
id|rp-&gt;hirange
op_assign
id|rx.hirange
suffix:semicolon
id|pp
op_assign
(paren
id|iwffff_env_point_t
op_star
)paren
(paren
id|rp
op_plus
l_int|1
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
id|rp-&gt;nattack
op_plus
id|rp-&gt;nrelease
suffix:semicolon
id|idx
op_increment
)paren
(brace
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|px
comma
op_star
id|data
comma
r_sizeof
(paren
id|px
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
op_star
id|data
op_add_assign
r_sizeof
(paren
id|px
)paren
suffix:semicolon
op_star
id|len
op_sub_assign
r_sizeof
(paren
id|px
)paren
suffix:semicolon
id|pp-&gt;offset
op_assign
id|le16_to_cpu
c_func
(paren
id|px.offset
)paren
suffix:semicolon
id|pp-&gt;rate
op_assign
id|le16_to_cpu
c_func
(paren
id|px.rate
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ep-&gt;record
op_eq
l_int|NULL
)paren
(brace
id|ep-&gt;record
op_assign
id|rp
suffix:semicolon
)brace
r_else
(brace
id|rp_last
op_assign
id|rp
suffix:semicolon
)brace
id|rp_last
op_assign
id|rp
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_seq_iwffff_copy_wave_from_stream
r_static
r_int
id|snd_seq_iwffff_copy_wave_from_stream
c_func
(paren
id|snd_iwffff_ops_t
op_star
id|ops
comma
id|iwffff_layer_t
op_star
id|lp
comma
r_char
id|__user
op_star
op_star
id|data
comma
r_int
op_star
id|len
comma
r_int
id|atomic
)paren
(brace
id|iwffff_wave_t
op_star
id|wp
comma
op_star
id|prev
suffix:semicolon
id|iwffff_xwave_t
id|xp
suffix:semicolon
r_int
id|err
comma
id|gfp_mask
suffix:semicolon
r_int
r_int
id|real_size
suffix:semicolon
id|gfp_mask
op_assign
id|atomic
ques
c_cond
id|GFP_ATOMIC
suffix:colon
id|GFP_KERNEL
suffix:semicolon
r_if
c_cond
(paren
op_star
id|len
OL
(paren
r_int
)paren
r_sizeof
(paren
id|xp
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|xp
comma
op_star
id|data
comma
r_sizeof
(paren
id|xp
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
op_star
id|data
op_add_assign
r_sizeof
(paren
id|xp
)paren
suffix:semicolon
op_star
id|len
op_sub_assign
r_sizeof
(paren
id|xp
)paren
suffix:semicolon
id|wp
op_assign
id|kcalloc
c_func
(paren
l_int|1
comma
r_sizeof
(paren
op_star
id|wp
)paren
comma
id|gfp_mask
)paren
suffix:semicolon
r_if
c_cond
(paren
id|wp
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|wp-&gt;share_id
(braket
l_int|0
)braket
op_assign
id|le32_to_cpu
c_func
(paren
id|xp.share_id
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|wp-&gt;share_id
(braket
l_int|1
)braket
op_assign
id|le32_to_cpu
c_func
(paren
id|xp.share_id
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|wp-&gt;share_id
(braket
l_int|2
)braket
op_assign
id|le32_to_cpu
c_func
(paren
id|xp.share_id
(braket
l_int|2
)braket
)paren
suffix:semicolon
id|wp-&gt;share_id
(braket
l_int|3
)braket
op_assign
id|le32_to_cpu
c_func
(paren
id|xp.share_id
(braket
l_int|3
)braket
)paren
suffix:semicolon
id|wp-&gt;format
op_assign
id|le32_to_cpu
c_func
(paren
id|xp.format
)paren
suffix:semicolon
id|wp-&gt;address.memory
op_assign
id|le32_to_cpu
c_func
(paren
id|xp.offset
)paren
suffix:semicolon
id|wp-&gt;size
op_assign
id|le32_to_cpu
c_func
(paren
id|xp.size
)paren
suffix:semicolon
id|wp-&gt;start
op_assign
id|le32_to_cpu
c_func
(paren
id|xp.start
)paren
suffix:semicolon
id|wp-&gt;loop_start
op_assign
id|le32_to_cpu
c_func
(paren
id|xp.loop_start
)paren
suffix:semicolon
id|wp-&gt;loop_end
op_assign
id|le32_to_cpu
c_func
(paren
id|xp.loop_end
)paren
suffix:semicolon
id|wp-&gt;loop_repeat
op_assign
id|le16_to_cpu
c_func
(paren
id|xp.loop_repeat
)paren
suffix:semicolon
id|wp-&gt;sample_ratio
op_assign
id|le32_to_cpu
c_func
(paren
id|xp.sample_ratio
)paren
suffix:semicolon
id|wp-&gt;attenuation
op_assign
id|xp.attenuation
suffix:semicolon
id|wp-&gt;low_note
op_assign
id|xp.low_note
suffix:semicolon
id|wp-&gt;high_note
op_assign
id|xp.high_note
suffix:semicolon
id|real_size
op_assign
id|snd_seq_iwffff_size
c_func
(paren
id|wp-&gt;size
comma
id|wp-&gt;format
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|wp-&gt;format
op_amp
id|IWFFFF_WAVE_ROM
)paren
)paren
(brace
r_if
c_cond
(paren
(paren
r_int
)paren
id|real_size
OG
op_star
id|len
)paren
(brace
id|kfree
c_func
(paren
id|wp
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|ops-&gt;put_sample
)paren
(brace
id|err
op_assign
id|ops
op_member_access_from_pointer
id|put_sample
c_func
(paren
id|ops-&gt;private_data
comma
id|wp
comma
op_star
id|data
comma
id|real_size
comma
id|atomic
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
(brace
id|kfree
c_func
(paren
id|wp
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|wp-&gt;format
op_amp
id|IWFFFF_WAVE_ROM
)paren
)paren
(brace
op_star
id|data
op_add_assign
id|real_size
suffix:semicolon
op_star
id|len
op_sub_assign
id|real_size
suffix:semicolon
)brace
id|prev
op_assign
id|lp-&gt;wave
suffix:semicolon
r_if
c_cond
(paren
id|prev
)paren
(brace
r_while
c_loop
(paren
id|prev-&gt;next
)paren
id|prev
op_assign
id|prev-&gt;next
suffix:semicolon
id|prev-&gt;next
op_assign
id|wp
suffix:semicolon
)brace
r_else
(brace
id|lp-&gt;wave
op_assign
id|wp
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_seq_iwffff_env_free
r_static
r_void
id|snd_seq_iwffff_env_free
c_func
(paren
id|snd_iwffff_ops_t
op_star
id|ops
comma
id|iwffff_env_t
op_star
id|env
comma
r_int
id|atomic
)paren
(brace
id|iwffff_env_record_t
op_star
id|rec
suffix:semicolon
r_while
c_loop
(paren
(paren
id|rec
op_assign
id|env-&gt;record
)paren
op_ne
l_int|NULL
)paren
(brace
id|env-&gt;record
op_assign
id|rec-&gt;next
suffix:semicolon
id|kfree
c_func
(paren
id|rec
)paren
suffix:semicolon
)brace
)brace
DECL|function|snd_seq_iwffff_wave_free
r_static
r_void
id|snd_seq_iwffff_wave_free
c_func
(paren
id|snd_iwffff_ops_t
op_star
id|ops
comma
id|iwffff_wave_t
op_star
id|wave
comma
r_int
id|atomic
)paren
(brace
r_if
c_cond
(paren
id|ops-&gt;remove_sample
)paren
id|ops
op_member_access_from_pointer
id|remove_sample
c_func
(paren
id|ops-&gt;private_data
comma
id|wave
comma
id|atomic
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|wave
)paren
suffix:semicolon
)brace
DECL|function|snd_seq_iwffff_instr_free
r_static
r_void
id|snd_seq_iwffff_instr_free
c_func
(paren
id|snd_iwffff_ops_t
op_star
id|ops
comma
id|iwffff_instrument_t
op_star
id|ip
comma
r_int
id|atomic
)paren
(brace
id|iwffff_layer_t
op_star
id|layer
suffix:semicolon
id|iwffff_wave_t
op_star
id|wave
suffix:semicolon
r_while
c_loop
(paren
(paren
id|layer
op_assign
id|ip-&gt;layer
)paren
op_ne
l_int|NULL
)paren
(brace
id|ip-&gt;layer
op_assign
id|layer-&gt;next
suffix:semicolon
id|snd_seq_iwffff_env_free
c_func
(paren
id|ops
comma
op_amp
id|layer-&gt;penv
comma
id|atomic
)paren
suffix:semicolon
id|snd_seq_iwffff_env_free
c_func
(paren
id|ops
comma
op_amp
id|layer-&gt;venv
comma
id|atomic
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|wave
op_assign
id|layer-&gt;wave
)paren
op_ne
l_int|NULL
)paren
(brace
id|layer-&gt;wave
op_assign
id|wave-&gt;next
suffix:semicolon
id|snd_seq_iwffff_wave_free
c_func
(paren
id|ops
comma
id|wave
comma
id|atomic
)paren
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|layer
)paren
suffix:semicolon
)brace
)brace
DECL|function|snd_seq_iwffff_put
r_static
r_int
id|snd_seq_iwffff_put
c_func
(paren
r_void
op_star
id|private_data
comma
id|snd_seq_kinstr_t
op_star
id|instr
comma
r_char
id|__user
op_star
id|instr_data
comma
r_int
id|len
comma
r_int
id|atomic
comma
r_int
id|cmd
)paren
(brace
id|snd_iwffff_ops_t
op_star
id|ops
op_assign
(paren
id|snd_iwffff_ops_t
op_star
)paren
id|private_data
suffix:semicolon
id|iwffff_instrument_t
op_star
id|ip
suffix:semicolon
id|iwffff_xinstrument_t
id|ix
suffix:semicolon
id|iwffff_layer_t
op_star
id|lp
comma
op_star
id|prev_lp
suffix:semicolon
id|iwffff_xlayer_t
id|lx
suffix:semicolon
r_int
id|err
comma
id|gfp_mask
suffix:semicolon
r_if
c_cond
(paren
id|cmd
op_ne
id|SNDRV_SEQ_INSTR_PUT_CMD_CREATE
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|gfp_mask
op_assign
id|atomic
ques
c_cond
id|GFP_ATOMIC
suffix:colon
id|GFP_KERNEL
suffix:semicolon
multiline_comment|/* copy instrument data */
r_if
c_cond
(paren
id|len
OL
(paren
r_int
)paren
r_sizeof
(paren
id|ix
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|ix
comma
id|instr_data
comma
r_sizeof
(paren
id|ix
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|ix.stype
op_ne
id|IWFFFF_STRU_INSTR
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|instr_data
op_add_assign
r_sizeof
(paren
id|ix
)paren
suffix:semicolon
id|len
op_sub_assign
r_sizeof
(paren
id|ix
)paren
suffix:semicolon
id|ip
op_assign
(paren
id|iwffff_instrument_t
op_star
)paren
id|KINSTR_DATA
c_func
(paren
id|instr
)paren
suffix:semicolon
id|ip-&gt;exclusion
op_assign
id|le16_to_cpu
c_func
(paren
id|ix.exclusion
)paren
suffix:semicolon
id|ip-&gt;layer_type
op_assign
id|le16_to_cpu
c_func
(paren
id|ix.layer_type
)paren
suffix:semicolon
id|ip-&gt;exclusion_group
op_assign
id|le16_to_cpu
c_func
(paren
id|ix.exclusion_group
)paren
suffix:semicolon
id|ip-&gt;effect1
op_assign
id|ix.effect1
suffix:semicolon
id|ip-&gt;effect1_depth
op_assign
id|ix.effect1_depth
suffix:semicolon
id|ip-&gt;effect2
op_assign
id|ix.effect2
suffix:semicolon
id|ip-&gt;effect2_depth
op_assign
id|ix.effect2_depth
suffix:semicolon
multiline_comment|/* copy layers */
id|prev_lp
op_assign
l_int|NULL
suffix:semicolon
r_while
c_loop
(paren
id|len
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|len
OL
(paren
r_int
)paren
r_sizeof
(paren
id|iwffff_xlayer_t
)paren
)paren
(brace
id|snd_seq_iwffff_instr_free
c_func
(paren
id|ops
comma
id|ip
comma
id|atomic
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|lx
comma
id|instr_data
comma
r_sizeof
(paren
id|lx
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|instr_data
op_add_assign
r_sizeof
(paren
id|lx
)paren
suffix:semicolon
id|len
op_sub_assign
r_sizeof
(paren
id|lx
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lx.stype
op_ne
id|IWFFFF_STRU_LAYER
)paren
(brace
id|snd_seq_iwffff_instr_free
c_func
(paren
id|ops
comma
id|ip
comma
id|atomic
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|lp
op_assign
id|kcalloc
c_func
(paren
l_int|1
comma
r_sizeof
(paren
op_star
id|lp
)paren
comma
id|gfp_mask
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lp
op_eq
l_int|NULL
)paren
(brace
id|snd_seq_iwffff_instr_free
c_func
(paren
id|ops
comma
id|ip
comma
id|atomic
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
r_if
c_cond
(paren
id|prev_lp
)paren
(brace
id|prev_lp-&gt;next
op_assign
id|lp
suffix:semicolon
)brace
r_else
(brace
id|ip-&gt;layer
op_assign
id|lp
suffix:semicolon
)brace
id|prev_lp
op_assign
id|lp
suffix:semicolon
id|lp-&gt;flags
op_assign
id|lx.flags
suffix:semicolon
id|lp-&gt;velocity_mode
op_assign
id|lx.velocity_mode
suffix:semicolon
id|lp-&gt;layer_event
op_assign
id|lx.layer_event
suffix:semicolon
id|lp-&gt;low_range
op_assign
id|lx.low_range
suffix:semicolon
id|lp-&gt;high_range
op_assign
id|lx.high_range
suffix:semicolon
id|lp-&gt;pan
op_assign
id|lx.pan
suffix:semicolon
id|lp-&gt;pan_freq_scale
op_assign
id|lx.pan_freq_scale
suffix:semicolon
id|lp-&gt;attenuation
op_assign
id|lx.attenuation
suffix:semicolon
id|snd_seq_iwffff_copy_lfo_from_stream
c_func
(paren
op_amp
id|lp-&gt;tremolo
comma
op_amp
id|lx.tremolo
)paren
suffix:semicolon
id|snd_seq_iwffff_copy_lfo_from_stream
c_func
(paren
op_amp
id|lp-&gt;vibrato
comma
op_amp
id|lx.vibrato
)paren
suffix:semicolon
id|lp-&gt;freq_scale
op_assign
id|le16_to_cpu
c_func
(paren
id|lx.freq_scale
)paren
suffix:semicolon
id|lp-&gt;freq_center
op_assign
id|lx.freq_center
suffix:semicolon
id|err
op_assign
id|snd_seq_iwffff_copy_env_from_stream
c_func
(paren
id|IWFFFF_STRU_ENV_RECP
comma
id|lp
comma
op_amp
id|lp-&gt;penv
comma
op_amp
id|lx.penv
comma
op_amp
id|instr_data
comma
op_amp
id|len
comma
id|gfp_mask
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
(brace
id|snd_seq_iwffff_instr_free
c_func
(paren
id|ops
comma
id|ip
comma
id|atomic
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
id|err
op_assign
id|snd_seq_iwffff_copy_env_from_stream
c_func
(paren
id|IWFFFF_STRU_ENV_RECV
comma
id|lp
comma
op_amp
id|lp-&gt;venv
comma
op_amp
id|lx.venv
comma
op_amp
id|instr_data
comma
op_amp
id|len
comma
id|gfp_mask
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
(brace
id|snd_seq_iwffff_instr_free
c_func
(paren
id|ops
comma
id|ip
comma
id|atomic
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
r_while
c_loop
(paren
id|len
OG
(paren
r_int
)paren
r_sizeof
(paren
id|__u32
)paren
)paren
(brace
id|__u32
id|stype
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|stype
comma
id|instr_data
comma
r_sizeof
(paren
id|stype
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|stype
op_ne
id|IWFFFF_STRU_WAVE
)paren
r_break
suffix:semicolon
id|err
op_assign
id|snd_seq_iwffff_copy_wave_from_stream
c_func
(paren
id|ops
comma
id|lp
comma
op_amp
id|instr_data
comma
op_amp
id|len
comma
id|atomic
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
(brace
id|snd_seq_iwffff_instr_free
c_func
(paren
id|ops
comma
id|ip
comma
id|atomic
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_seq_iwffff_copy_lfo_to_stream
r_static
r_void
id|snd_seq_iwffff_copy_lfo_to_stream
c_func
(paren
id|iwffff_xlfo_t
op_star
id|fx
comma
id|iwffff_lfo_t
op_star
id|fp
)paren
(brace
id|fx-&gt;freq
op_assign
id|cpu_to_le16
c_func
(paren
id|fp-&gt;freq
)paren
suffix:semicolon
id|fx-&gt;depth
op_assign
id|cpu_to_le16
c_func
(paren
id|fp-&gt;depth
)paren
suffix:semicolon
id|fx-&gt;sweep
op_assign
id|cpu_to_le16
c_func
(paren
id|fp-&gt;sweep
)paren
suffix:semicolon
id|fp-&gt;shape
op_assign
id|fx-&gt;shape
suffix:semicolon
id|fp-&gt;delay
op_assign
id|fx-&gt;delay
suffix:semicolon
)brace
DECL|function|snd_seq_iwffff_copy_env_to_stream
r_static
r_int
id|snd_seq_iwffff_copy_env_to_stream
c_func
(paren
id|__u32
id|req_stype
comma
id|iwffff_layer_t
op_star
id|lp
comma
id|iwffff_xenv_t
op_star
id|ex
comma
id|iwffff_env_t
op_star
id|ep
comma
r_char
id|__user
op_star
op_star
id|data
comma
r_int
op_star
id|len
)paren
(brace
id|iwffff_env_record_t
op_star
id|rp
suffix:semicolon
id|iwffff_xenv_record_t
id|rx
suffix:semicolon
id|iwffff_env_point_t
op_star
id|pp
suffix:semicolon
id|iwffff_xenv_point_t
id|px
suffix:semicolon
r_int
id|points_size
comma
id|idx
suffix:semicolon
id|ex-&gt;flags
op_assign
id|ep-&gt;flags
suffix:semicolon
id|ex-&gt;mode
op_assign
id|ep-&gt;mode
suffix:semicolon
id|ex-&gt;index
op_assign
id|ep-&gt;index
suffix:semicolon
r_for
c_loop
(paren
id|rp
op_assign
id|ep-&gt;record
suffix:semicolon
id|rp
suffix:semicolon
id|rp
op_assign
id|rp-&gt;next
)paren
(brace
r_if
c_cond
(paren
op_star
id|len
OL
(paren
r_int
)paren
r_sizeof
(paren
id|rx
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|rx
comma
l_int|0
comma
r_sizeof
(paren
id|rx
)paren
)paren
suffix:semicolon
id|rx.stype
op_assign
id|req_stype
suffix:semicolon
id|rx.nattack
op_assign
id|cpu_to_le16
c_func
(paren
id|rp-&gt;nattack
)paren
suffix:semicolon
id|rx.nrelease
op_assign
id|cpu_to_le16
c_func
(paren
id|rp-&gt;nrelease
)paren
suffix:semicolon
id|rx.sustain_offset
op_assign
id|cpu_to_le16
c_func
(paren
id|rp-&gt;sustain_offset
)paren
suffix:semicolon
id|rx.sustain_rate
op_assign
id|cpu_to_le16
c_func
(paren
id|rp-&gt;sustain_rate
)paren
suffix:semicolon
id|rx.release_rate
op_assign
id|cpu_to_le16
c_func
(paren
id|rp-&gt;release_rate
)paren
suffix:semicolon
id|rx.hirange
op_assign
id|cpu_to_le16
c_func
(paren
id|rp-&gt;hirange
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
op_star
id|data
comma
op_amp
id|rx
comma
r_sizeof
(paren
id|rx
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
op_star
id|data
op_add_assign
r_sizeof
(paren
id|rx
)paren
suffix:semicolon
op_star
id|len
op_sub_assign
r_sizeof
(paren
id|rx
)paren
suffix:semicolon
id|points_size
op_assign
(paren
id|rp-&gt;nattack
op_plus
id|rp-&gt;nrelease
)paren
op_star
l_int|2
op_star
r_sizeof
(paren
id|__u16
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|len
OL
id|points_size
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|pp
op_assign
(paren
id|iwffff_env_point_t
op_star
)paren
(paren
id|rp
op_plus
l_int|1
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
id|rp-&gt;nattack
op_plus
id|rp-&gt;nrelease
suffix:semicolon
id|idx
op_increment
)paren
(brace
id|px.offset
op_assign
id|cpu_to_le16
c_func
(paren
id|pp-&gt;offset
)paren
suffix:semicolon
id|px.rate
op_assign
id|cpu_to_le16
c_func
(paren
id|pp-&gt;rate
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
op_star
id|data
comma
op_amp
id|px
comma
r_sizeof
(paren
id|px
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
op_star
id|data
op_add_assign
r_sizeof
(paren
id|px
)paren
suffix:semicolon
op_star
id|len
op_sub_assign
r_sizeof
(paren
id|px
)paren
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_seq_iwffff_copy_wave_to_stream
r_static
r_int
id|snd_seq_iwffff_copy_wave_to_stream
c_func
(paren
id|snd_iwffff_ops_t
op_star
id|ops
comma
id|iwffff_layer_t
op_star
id|lp
comma
r_char
id|__user
op_star
op_star
id|data
comma
r_int
op_star
id|len
comma
r_int
id|atomic
)paren
(brace
id|iwffff_wave_t
op_star
id|wp
suffix:semicolon
id|iwffff_xwave_t
id|xp
suffix:semicolon
r_int
id|err
suffix:semicolon
r_int
r_int
id|real_size
suffix:semicolon
r_for
c_loop
(paren
id|wp
op_assign
id|lp-&gt;wave
suffix:semicolon
id|wp
suffix:semicolon
id|wp
op_assign
id|wp-&gt;next
)paren
(brace
r_if
c_cond
(paren
op_star
id|len
OL
(paren
r_int
)paren
r_sizeof
(paren
id|xp
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|xp
comma
l_int|0
comma
r_sizeof
(paren
id|xp
)paren
)paren
suffix:semicolon
id|xp.stype
op_assign
id|IWFFFF_STRU_WAVE
suffix:semicolon
id|xp.share_id
(braket
l_int|0
)braket
op_assign
id|cpu_to_le32
c_func
(paren
id|wp-&gt;share_id
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|xp.share_id
(braket
l_int|1
)braket
op_assign
id|cpu_to_le32
c_func
(paren
id|wp-&gt;share_id
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|xp.share_id
(braket
l_int|2
)braket
op_assign
id|cpu_to_le32
c_func
(paren
id|wp-&gt;share_id
(braket
l_int|2
)braket
)paren
suffix:semicolon
id|xp.share_id
(braket
l_int|3
)braket
op_assign
id|cpu_to_le32
c_func
(paren
id|wp-&gt;share_id
(braket
l_int|3
)braket
)paren
suffix:semicolon
id|xp.format
op_assign
id|cpu_to_le32
c_func
(paren
id|wp-&gt;format
)paren
suffix:semicolon
r_if
c_cond
(paren
id|wp-&gt;format
op_amp
id|IWFFFF_WAVE_ROM
)paren
id|xp.offset
op_assign
id|cpu_to_le32
c_func
(paren
id|wp-&gt;address.memory
)paren
suffix:semicolon
id|xp.size
op_assign
id|cpu_to_le32
c_func
(paren
id|wp-&gt;size
)paren
suffix:semicolon
id|xp.start
op_assign
id|cpu_to_le32
c_func
(paren
id|wp-&gt;start
)paren
suffix:semicolon
id|xp.loop_start
op_assign
id|cpu_to_le32
c_func
(paren
id|wp-&gt;loop_start
)paren
suffix:semicolon
id|xp.loop_end
op_assign
id|cpu_to_le32
c_func
(paren
id|wp-&gt;loop_end
)paren
suffix:semicolon
id|xp.loop_repeat
op_assign
id|cpu_to_le32
c_func
(paren
id|wp-&gt;loop_repeat
)paren
suffix:semicolon
id|xp.sample_ratio
op_assign
id|cpu_to_le32
c_func
(paren
id|wp-&gt;sample_ratio
)paren
suffix:semicolon
id|xp.attenuation
op_assign
id|wp-&gt;attenuation
suffix:semicolon
id|xp.low_note
op_assign
id|wp-&gt;low_note
suffix:semicolon
id|xp.high_note
op_assign
id|wp-&gt;high_note
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
op_star
id|data
comma
op_amp
id|xp
comma
r_sizeof
(paren
id|xp
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
op_star
id|data
op_add_assign
r_sizeof
(paren
id|xp
)paren
suffix:semicolon
op_star
id|len
op_sub_assign
r_sizeof
(paren
id|xp
)paren
suffix:semicolon
id|real_size
op_assign
id|snd_seq_iwffff_size
c_func
(paren
id|wp-&gt;size
comma
id|wp-&gt;format
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|wp-&gt;format
op_amp
id|IWFFFF_WAVE_ROM
)paren
)paren
(brace
r_if
c_cond
(paren
op_star
id|len
OL
(paren
r_int
)paren
id|real_size
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ops-&gt;get_sample
)paren
(brace
id|err
op_assign
id|ops
op_member_access_from_pointer
id|get_sample
c_func
(paren
id|ops-&gt;private_data
comma
id|wp
comma
op_star
id|data
comma
id|real_size
comma
id|atomic
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
r_if
c_cond
(paren
op_logical_neg
(paren
id|wp-&gt;format
op_amp
id|IWFFFF_WAVE_ROM
)paren
)paren
(brace
op_star
id|data
op_add_assign
id|real_size
suffix:semicolon
op_star
id|len
op_sub_assign
id|real_size
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_seq_iwffff_get
r_static
r_int
id|snd_seq_iwffff_get
c_func
(paren
r_void
op_star
id|private_data
comma
id|snd_seq_kinstr_t
op_star
id|instr
comma
r_char
id|__user
op_star
id|instr_data
comma
r_int
id|len
comma
r_int
id|atomic
comma
r_int
id|cmd
)paren
(brace
id|snd_iwffff_ops_t
op_star
id|ops
op_assign
(paren
id|snd_iwffff_ops_t
op_star
)paren
id|private_data
suffix:semicolon
id|iwffff_instrument_t
op_star
id|ip
suffix:semicolon
id|iwffff_xinstrument_t
id|ix
suffix:semicolon
id|iwffff_layer_t
op_star
id|lp
suffix:semicolon
id|iwffff_xlayer_t
id|lx
suffix:semicolon
r_char
id|__user
op_star
id|layer_instr_data
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
id|cmd
op_ne
id|SNDRV_SEQ_INSTR_GET_CMD_FULL
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
(paren
r_int
)paren
r_sizeof
(paren
id|ix
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|ix
comma
l_int|0
comma
r_sizeof
(paren
id|ix
)paren
)paren
suffix:semicolon
id|ip
op_assign
(paren
id|iwffff_instrument_t
op_star
)paren
id|KINSTR_DATA
c_func
(paren
id|instr
)paren
suffix:semicolon
id|ix.stype
op_assign
id|IWFFFF_STRU_INSTR
suffix:semicolon
id|ix.exclusion
op_assign
id|cpu_to_le16
c_func
(paren
id|ip-&gt;exclusion
)paren
suffix:semicolon
id|ix.layer_type
op_assign
id|cpu_to_le16
c_func
(paren
id|ip-&gt;layer_type
)paren
suffix:semicolon
id|ix.exclusion_group
op_assign
id|cpu_to_le16
c_func
(paren
id|ip-&gt;exclusion_group
)paren
suffix:semicolon
id|ix.effect1
op_assign
id|cpu_to_le16
c_func
(paren
id|ip-&gt;effect1
)paren
suffix:semicolon
id|ix.effect1_depth
op_assign
id|cpu_to_le16
c_func
(paren
id|ip-&gt;effect1_depth
)paren
suffix:semicolon
id|ix.effect2
op_assign
id|ip-&gt;effect2
suffix:semicolon
id|ix.effect2_depth
op_assign
id|ip-&gt;effect2_depth
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|instr_data
comma
op_amp
id|ix
comma
r_sizeof
(paren
id|ix
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|instr_data
op_add_assign
r_sizeof
(paren
id|ix
)paren
suffix:semicolon
id|len
op_sub_assign
r_sizeof
(paren
id|ix
)paren
suffix:semicolon
r_for
c_loop
(paren
id|lp
op_assign
id|ip-&gt;layer
suffix:semicolon
id|lp
suffix:semicolon
id|lp
op_assign
id|lp-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|len
OL
(paren
r_int
)paren
r_sizeof
(paren
id|lx
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|lx
comma
l_int|0
comma
r_sizeof
(paren
id|lx
)paren
)paren
suffix:semicolon
id|lx.stype
op_assign
id|IWFFFF_STRU_LAYER
suffix:semicolon
id|lx.flags
op_assign
id|lp-&gt;flags
suffix:semicolon
id|lx.velocity_mode
op_assign
id|lp-&gt;velocity_mode
suffix:semicolon
id|lx.layer_event
op_assign
id|lp-&gt;layer_event
suffix:semicolon
id|lx.low_range
op_assign
id|lp-&gt;low_range
suffix:semicolon
id|lx.high_range
op_assign
id|lp-&gt;high_range
suffix:semicolon
id|lx.pan
op_assign
id|lp-&gt;pan
suffix:semicolon
id|lx.pan_freq_scale
op_assign
id|lp-&gt;pan_freq_scale
suffix:semicolon
id|lx.attenuation
op_assign
id|lp-&gt;attenuation
suffix:semicolon
id|snd_seq_iwffff_copy_lfo_to_stream
c_func
(paren
op_amp
id|lx.tremolo
comma
op_amp
id|lp-&gt;tremolo
)paren
suffix:semicolon
id|snd_seq_iwffff_copy_lfo_to_stream
c_func
(paren
op_amp
id|lx.vibrato
comma
op_amp
id|lp-&gt;vibrato
)paren
suffix:semicolon
id|layer_instr_data
op_assign
id|instr_data
suffix:semicolon
id|instr_data
op_add_assign
r_sizeof
(paren
id|lx
)paren
suffix:semicolon
id|len
op_sub_assign
r_sizeof
(paren
id|lx
)paren
suffix:semicolon
id|err
op_assign
id|snd_seq_iwffff_copy_env_to_stream
c_func
(paren
id|IWFFFF_STRU_ENV_RECP
comma
id|lp
comma
op_amp
id|lx.penv
comma
op_amp
id|lp-&gt;penv
comma
op_amp
id|instr_data
comma
op_amp
id|len
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
id|err
op_assign
id|snd_seq_iwffff_copy_env_to_stream
c_func
(paren
id|IWFFFF_STRU_ENV_RECV
comma
id|lp
comma
op_amp
id|lx.venv
comma
op_amp
id|lp-&gt;venv
comma
op_amp
id|instr_data
comma
op_amp
id|len
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
multiline_comment|/* layer structure updating is now finished */
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|layer_instr_data
comma
op_amp
id|lx
comma
r_sizeof
(paren
id|lx
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|err
op_assign
id|snd_seq_iwffff_copy_wave_to_stream
c_func
(paren
id|ops
comma
id|lp
comma
op_amp
id|instr_data
comma
op_amp
id|len
comma
id|atomic
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
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_seq_iwffff_env_size_in_stream
r_static
r_int
id|snd_seq_iwffff_env_size_in_stream
c_func
(paren
id|iwffff_env_t
op_star
id|ep
)paren
(brace
r_int
id|result
op_assign
l_int|0
suffix:semicolon
id|iwffff_env_record_t
op_star
id|rp
suffix:semicolon
r_for
c_loop
(paren
id|rp
op_assign
id|ep-&gt;record
suffix:semicolon
id|rp
suffix:semicolon
id|rp
op_assign
id|rp-&gt;next
)paren
(brace
id|result
op_add_assign
r_sizeof
(paren
id|iwffff_xenv_record_t
)paren
suffix:semicolon
id|result
op_add_assign
(paren
id|rp-&gt;nattack
op_plus
id|rp-&gt;nrelease
)paren
op_star
l_int|2
op_star
r_sizeof
(paren
id|__u16
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_seq_iwffff_wave_size_in_stream
r_static
r_int
id|snd_seq_iwffff_wave_size_in_stream
c_func
(paren
id|iwffff_layer_t
op_star
id|lp
)paren
(brace
r_int
id|result
op_assign
l_int|0
suffix:semicolon
id|iwffff_wave_t
op_star
id|wp
suffix:semicolon
r_for
c_loop
(paren
id|wp
op_assign
id|lp-&gt;wave
suffix:semicolon
id|wp
suffix:semicolon
id|wp
op_assign
id|wp-&gt;next
)paren
(brace
id|result
op_add_assign
r_sizeof
(paren
id|iwffff_xwave_t
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|wp-&gt;format
op_amp
id|IWFFFF_WAVE_ROM
)paren
)paren
id|result
op_add_assign
id|wp-&gt;size
suffix:semicolon
)brace
r_return
id|result
suffix:semicolon
)brace
DECL|function|snd_seq_iwffff_get_size
r_static
r_int
id|snd_seq_iwffff_get_size
c_func
(paren
r_void
op_star
id|private_data
comma
id|snd_seq_kinstr_t
op_star
id|instr
comma
r_int
op_star
id|size
)paren
(brace
r_int
id|result
suffix:semicolon
id|iwffff_instrument_t
op_star
id|ip
suffix:semicolon
id|iwffff_layer_t
op_star
id|lp
suffix:semicolon
op_star
id|size
op_assign
l_int|0
suffix:semicolon
id|ip
op_assign
(paren
id|iwffff_instrument_t
op_star
)paren
id|KINSTR_DATA
c_func
(paren
id|instr
)paren
suffix:semicolon
id|result
op_assign
r_sizeof
(paren
id|iwffff_xinstrument_t
)paren
suffix:semicolon
r_for
c_loop
(paren
id|lp
op_assign
id|ip-&gt;layer
suffix:semicolon
id|lp
suffix:semicolon
id|lp
op_assign
id|lp-&gt;next
)paren
(brace
id|result
op_add_assign
r_sizeof
(paren
id|iwffff_xlayer_t
)paren
suffix:semicolon
id|result
op_add_assign
id|snd_seq_iwffff_env_size_in_stream
c_func
(paren
op_amp
id|lp-&gt;penv
)paren
suffix:semicolon
id|result
op_add_assign
id|snd_seq_iwffff_env_size_in_stream
c_func
(paren
op_amp
id|lp-&gt;venv
)paren
suffix:semicolon
id|result
op_add_assign
id|snd_seq_iwffff_wave_size_in_stream
c_func
(paren
id|lp
)paren
suffix:semicolon
)brace
op_star
id|size
op_assign
id|result
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_seq_iwffff_remove
r_static
r_int
id|snd_seq_iwffff_remove
c_func
(paren
r_void
op_star
id|private_data
comma
id|snd_seq_kinstr_t
op_star
id|instr
comma
r_int
id|atomic
)paren
(brace
id|snd_iwffff_ops_t
op_star
id|ops
op_assign
(paren
id|snd_iwffff_ops_t
op_star
)paren
id|private_data
suffix:semicolon
id|iwffff_instrument_t
op_star
id|ip
suffix:semicolon
id|ip
op_assign
(paren
id|iwffff_instrument_t
op_star
)paren
id|KINSTR_DATA
c_func
(paren
id|instr
)paren
suffix:semicolon
id|snd_seq_iwffff_instr_free
c_func
(paren
id|ops
comma
id|ip
comma
id|atomic
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_seq_iwffff_notify
r_static
r_void
id|snd_seq_iwffff_notify
c_func
(paren
r_void
op_star
id|private_data
comma
id|snd_seq_kinstr_t
op_star
id|instr
comma
r_int
id|what
)paren
(brace
id|snd_iwffff_ops_t
op_star
id|ops
op_assign
(paren
id|snd_iwffff_ops_t
op_star
)paren
id|private_data
suffix:semicolon
r_if
c_cond
(paren
id|ops-&gt;notify
)paren
id|ops
op_member_access_from_pointer
id|notify
c_func
(paren
id|ops-&gt;private_data
comma
id|instr
comma
id|what
)paren
suffix:semicolon
)brace
DECL|function|snd_seq_iwffff_init
r_int
id|snd_seq_iwffff_init
c_func
(paren
id|snd_iwffff_ops_t
op_star
id|ops
comma
r_void
op_star
id|private_data
comma
id|snd_seq_kinstr_ops_t
op_star
id|next
)paren
(brace
id|memset
c_func
(paren
id|ops
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|ops
)paren
)paren
suffix:semicolon
id|ops-&gt;private_data
op_assign
id|private_data
suffix:semicolon
id|ops-&gt;kops.private_data
op_assign
id|ops
suffix:semicolon
id|ops-&gt;kops.add_len
op_assign
r_sizeof
(paren
id|iwffff_instrument_t
)paren
suffix:semicolon
id|ops-&gt;kops.instr_type
op_assign
id|SNDRV_SEQ_INSTR_ID_INTERWAVE
suffix:semicolon
id|ops-&gt;kops.put
op_assign
id|snd_seq_iwffff_put
suffix:semicolon
id|ops-&gt;kops.get
op_assign
id|snd_seq_iwffff_get
suffix:semicolon
id|ops-&gt;kops.get_size
op_assign
id|snd_seq_iwffff_get_size
suffix:semicolon
id|ops-&gt;kops.remove
op_assign
id|snd_seq_iwffff_remove
suffix:semicolon
id|ops-&gt;kops.notify
op_assign
id|snd_seq_iwffff_notify
suffix:semicolon
id|ops-&gt;kops.next
op_assign
id|next
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *  Init part&n; */
DECL|function|alsa_ainstr_iw_init
r_static
r_int
id|__init
id|alsa_ainstr_iw_init
c_func
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|alsa_ainstr_iw_exit
r_static
r_void
id|__exit
id|alsa_ainstr_iw_exit
c_func
(paren
r_void
)paren
(brace
)brace
id|module_init
c_func
(paren
id|alsa_ainstr_iw_init
)paren
id|module_exit
c_func
(paren
id|alsa_ainstr_iw_exit
)paren
id|EXPORT_SYMBOL
c_func
(paren
id|snd_seq_iwffff_init
)paren
suffix:semicolon
eof
