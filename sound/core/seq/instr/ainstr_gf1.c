multiline_comment|/*&n; *   GF1 (GUS) Patch - Instrument routines&n; *   Copyright (c) 1999 by Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &lt;sound/ainstr_gf1.h&gt;
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
l_string|&quot;Advanced Linux Sound Architecture GF1 (GUS) Patch support.&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_CLASSES
c_func
(paren
l_string|&quot;{sound}&quot;
)paren
suffix:semicolon
id|MODULE_SUPPORTED_DEVICE
c_func
(paren
l_string|&quot;sound&quot;
)paren
suffix:semicolon
DECL|variable|snd_seq_gf1_id
r_char
op_star
id|snd_seq_gf1_id
op_assign
id|SNDRV_SEQ_INSTR_ID_GUS_PATCH
suffix:semicolon
DECL|function|snd_seq_gf1_size
r_static
r_int
r_int
id|snd_seq_gf1_size
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
id|GF1_WAVE_16BIT
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
id|GF1_WAVE_STEREO
)paren
id|result
op_lshift_assign
l_int|1
suffix:semicolon
r_return
id|format
suffix:semicolon
)brace
DECL|function|snd_seq_gf1_copy_wave_from_stream
r_static
r_int
id|snd_seq_gf1_copy_wave_from_stream
c_func
(paren
id|snd_gf1_ops_t
op_star
id|ops
comma
id|gf1_instrument_t
op_star
id|ip
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
id|gf1_wave_t
op_star
id|wp
comma
op_star
id|prev
suffix:semicolon
id|gf1_xwave_t
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
id|wp-&gt;flags
op_assign
id|xp.flags
suffix:semicolon
id|wp-&gt;sample_rate
op_assign
id|le32_to_cpu
c_func
(paren
id|xp.sample_rate
)paren
suffix:semicolon
id|wp-&gt;low_frequency
op_assign
id|le32_to_cpu
c_func
(paren
id|xp.low_frequency
)paren
suffix:semicolon
id|wp-&gt;high_frequency
op_assign
id|le32_to_cpu
c_func
(paren
id|xp.high_frequency
)paren
suffix:semicolon
id|wp-&gt;root_frequency
op_assign
id|le32_to_cpu
c_func
(paren
id|xp.root_frequency
)paren
suffix:semicolon
id|wp-&gt;tune
op_assign
id|le16_to_cpu
c_func
(paren
id|xp.tune
)paren
suffix:semicolon
id|wp-&gt;balance
op_assign
id|xp.balance
suffix:semicolon
id|memcpy
c_func
(paren
id|wp-&gt;envelope_rate
comma
id|xp.envelope_rate
comma
l_int|6
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|wp-&gt;envelope_offset
comma
id|xp.envelope_offset
comma
l_int|6
)paren
suffix:semicolon
id|wp-&gt;tremolo_sweep
op_assign
id|xp.tremolo_sweep
suffix:semicolon
id|wp-&gt;tremolo_rate
op_assign
id|xp.tremolo_rate
suffix:semicolon
id|wp-&gt;tremolo_depth
op_assign
id|xp.tremolo_depth
suffix:semicolon
id|wp-&gt;vibrato_sweep
op_assign
id|xp.vibrato_sweep
suffix:semicolon
id|wp-&gt;vibrato_rate
op_assign
id|xp.vibrato_rate
suffix:semicolon
id|wp-&gt;vibrato_depth
op_assign
id|xp.vibrato_depth
suffix:semicolon
id|wp-&gt;scale_frequency
op_assign
id|le16_to_cpu
c_func
(paren
id|xp.scale_frequency
)paren
suffix:semicolon
id|wp-&gt;scale_factor
op_assign
id|le16_to_cpu
c_func
(paren
id|xp.scale_factor
)paren
suffix:semicolon
id|real_size
op_assign
id|snd_seq_gf1_size
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
id|prev
op_assign
id|ip-&gt;wave
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
id|ip-&gt;wave
op_assign
id|wp
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_seq_gf1_wave_free
r_static
r_void
id|snd_seq_gf1_wave_free
c_func
(paren
id|snd_gf1_ops_t
op_star
id|ops
comma
id|gf1_wave_t
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
DECL|function|snd_seq_gf1_instr_free
r_static
r_void
id|snd_seq_gf1_instr_free
c_func
(paren
id|snd_gf1_ops_t
op_star
id|ops
comma
id|gf1_instrument_t
op_star
id|ip
comma
r_int
id|atomic
)paren
(brace
id|gf1_wave_t
op_star
id|wave
suffix:semicolon
r_while
c_loop
(paren
(paren
id|wave
op_assign
id|ip-&gt;wave
)paren
op_ne
l_int|NULL
)paren
(brace
id|ip-&gt;wave
op_assign
id|wave-&gt;next
suffix:semicolon
id|snd_seq_gf1_wave_free
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
)brace
DECL|function|snd_seq_gf1_put
r_static
r_int
id|snd_seq_gf1_put
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
id|snd_gf1_ops_t
op_star
id|ops
op_assign
(paren
id|snd_gf1_ops_t
op_star
)paren
id|private_data
suffix:semicolon
id|gf1_instrument_t
op_star
id|ip
suffix:semicolon
id|gf1_xinstrument_t
id|ix
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
id|GF1_STRU_INSTR
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
id|gf1_instrument_t
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
id|GF1_STRU_WAVE
)paren
(brace
id|snd_seq_gf1_instr_free
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
id|err
op_assign
id|snd_seq_gf1_copy_wave_from_stream
c_func
(paren
id|ops
comma
id|ip
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
id|snd_seq_gf1_instr_free
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
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_seq_gf1_copy_wave_to_stream
r_static
r_int
id|snd_seq_gf1_copy_wave_to_stream
c_func
(paren
id|snd_gf1_ops_t
op_star
id|ops
comma
id|gf1_instrument_t
op_star
id|ip
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
id|gf1_wave_t
op_star
id|wp
suffix:semicolon
id|gf1_xwave_t
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
id|ip-&gt;wave
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
id|GF1_STRU_WAVE
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
id|xp.flags
op_assign
id|wp-&gt;flags
suffix:semicolon
id|xp.sample_rate
op_assign
id|cpu_to_le32
c_func
(paren
id|wp-&gt;sample_rate
)paren
suffix:semicolon
id|xp.low_frequency
op_assign
id|cpu_to_le32
c_func
(paren
id|wp-&gt;low_frequency
)paren
suffix:semicolon
id|xp.high_frequency
op_assign
id|cpu_to_le32
c_func
(paren
id|wp-&gt;high_frequency
)paren
suffix:semicolon
id|xp.root_frequency
op_assign
id|cpu_to_le32
c_func
(paren
id|wp-&gt;root_frequency
)paren
suffix:semicolon
id|xp.tune
op_assign
id|cpu_to_le16
c_func
(paren
id|wp-&gt;tune
)paren
suffix:semicolon
id|xp.balance
op_assign
id|wp-&gt;balance
suffix:semicolon
id|memcpy
c_func
(paren
id|xp.envelope_rate
comma
id|wp-&gt;envelope_rate
comma
l_int|6
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|xp.envelope_offset
comma
id|wp-&gt;envelope_offset
comma
l_int|6
)paren
suffix:semicolon
id|xp.tremolo_sweep
op_assign
id|wp-&gt;tremolo_sweep
suffix:semicolon
id|xp.tremolo_rate
op_assign
id|wp-&gt;tremolo_rate
suffix:semicolon
id|xp.tremolo_depth
op_assign
id|wp-&gt;tremolo_depth
suffix:semicolon
id|xp.vibrato_sweep
op_assign
id|wp-&gt;vibrato_sweep
suffix:semicolon
id|xp.vibrato_rate
op_assign
id|wp-&gt;vibrato_rate
suffix:semicolon
id|xp.vibrato_depth
op_assign
id|wp-&gt;vibrato_depth
suffix:semicolon
id|xp.scale_frequency
op_assign
id|cpu_to_le16
c_func
(paren
id|wp-&gt;scale_frequency
)paren
suffix:semicolon
id|xp.scale_factor
op_assign
id|cpu_to_le16
c_func
(paren
id|wp-&gt;scale_factor
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
id|snd_seq_gf1_size
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
op_star
id|data
op_add_assign
id|wp-&gt;size
suffix:semicolon
op_star
id|len
op_sub_assign
id|wp-&gt;size
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_seq_gf1_get
r_static
r_int
id|snd_seq_gf1_get
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
id|snd_gf1_ops_t
op_star
id|ops
op_assign
(paren
id|snd_gf1_ops_t
op_star
)paren
id|private_data
suffix:semicolon
id|gf1_instrument_t
op_star
id|ip
suffix:semicolon
id|gf1_xinstrument_t
id|ix
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
id|gf1_instrument_t
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
id|GF1_STRU_INSTR
suffix:semicolon
id|ix.exclusion
op_assign
id|cpu_to_le16
c_func
(paren
id|ip-&gt;exclusion
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
r_return
id|snd_seq_gf1_copy_wave_to_stream
c_func
(paren
id|ops
comma
id|ip
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
)brace
DECL|function|snd_seq_gf1_get_size
r_static
r_int
id|snd_seq_gf1_get_size
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
id|gf1_instrument_t
op_star
id|ip
suffix:semicolon
id|gf1_wave_t
op_star
id|wp
suffix:semicolon
op_star
id|size
op_assign
l_int|0
suffix:semicolon
id|ip
op_assign
(paren
id|gf1_instrument_t
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
id|gf1_xinstrument_t
)paren
suffix:semicolon
r_for
c_loop
(paren
id|wp
op_assign
id|ip-&gt;wave
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
id|gf1_xwave_t
)paren
suffix:semicolon
id|result
op_add_assign
id|wp-&gt;size
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
DECL|function|snd_seq_gf1_remove
r_static
r_int
id|snd_seq_gf1_remove
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
id|snd_gf1_ops_t
op_star
id|ops
op_assign
(paren
id|snd_gf1_ops_t
op_star
)paren
id|private_data
suffix:semicolon
id|gf1_instrument_t
op_star
id|ip
suffix:semicolon
id|ip
op_assign
(paren
id|gf1_instrument_t
op_star
)paren
id|KINSTR_DATA
c_func
(paren
id|instr
)paren
suffix:semicolon
id|snd_seq_gf1_instr_free
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
DECL|function|snd_seq_gf1_notify
r_static
r_void
id|snd_seq_gf1_notify
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
id|snd_gf1_ops_t
op_star
id|ops
op_assign
(paren
id|snd_gf1_ops_t
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
DECL|function|snd_seq_gf1_init
r_int
id|snd_seq_gf1_init
c_func
(paren
id|snd_gf1_ops_t
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
id|gf1_instrument_t
)paren
suffix:semicolon
id|ops-&gt;kops.instr_type
op_assign
id|snd_seq_gf1_id
suffix:semicolon
id|ops-&gt;kops.put
op_assign
id|snd_seq_gf1_put
suffix:semicolon
id|ops-&gt;kops.get
op_assign
id|snd_seq_gf1_get
suffix:semicolon
id|ops-&gt;kops.get_size
op_assign
id|snd_seq_gf1_get_size
suffix:semicolon
id|ops-&gt;kops.remove
op_assign
id|snd_seq_gf1_remove
suffix:semicolon
id|ops-&gt;kops.notify
op_assign
id|snd_seq_gf1_notify
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
DECL|function|alsa_ainstr_gf1_init
r_static
r_int
id|__init
id|alsa_ainstr_gf1_init
c_func
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|alsa_ainstr_gf1_exit
r_static
r_void
id|__exit
id|alsa_ainstr_gf1_exit
c_func
(paren
r_void
)paren
(brace
)brace
id|module_init
c_func
(paren
id|alsa_ainstr_gf1_init
)paren
id|module_exit
c_func
(paren
id|alsa_ainstr_gf1_exit
)paren
id|EXPORT_SYMBOL
c_func
(paren
id|snd_seq_gf1_id
)paren
suffix:semicolon
DECL|variable|EXPORT_SYMBOL
id|EXPORT_SYMBOL
c_func
(paren
id|snd_seq_gf1_init
)paren
suffix:semicolon
eof
