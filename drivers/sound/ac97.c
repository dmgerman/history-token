macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &quot;ac97.h&quot;
multiline_comment|/* Flag for mono controls. */
DECL|macro|MO
mdefine_line|#define MO 0
multiline_comment|/* And for stereo. */
DECL|macro|ST
mdefine_line|#define ST 1
multiline_comment|/* Whether or not the bits in the channel are inverted. */
DECL|macro|INV
mdefine_line|#define INV 1
DECL|macro|NINV
mdefine_line|#define NINV 0
DECL|struct|ac97_chn_desc
r_static
r_struct
id|ac97_chn_desc
(brace
DECL|member|ac97_regnum
r_int
id|ac97_regnum
suffix:semicolon
DECL|member|oss_channel
r_int
id|oss_channel
suffix:semicolon
DECL|member|maxval
r_int
id|maxval
suffix:semicolon
DECL|member|is_stereo
r_int
id|is_stereo
suffix:semicolon
DECL|member|oss_mask
r_int
id|oss_mask
suffix:semicolon
DECL|member|recordNum
r_int
id|recordNum
suffix:semicolon
DECL|member|regmask
id|u16
id|regmask
suffix:semicolon
DECL|member|is_inverted
r_int
id|is_inverted
suffix:semicolon
DECL|variable|mixerRegs
)brace
id|mixerRegs
(braket
)braket
op_assign
(brace
(brace
id|AC97_MASTER_VOL_STEREO
comma
id|SOUND_MIXER_VOLUME
comma
l_int|0x3f
comma
id|ST
comma
id|SOUND_MASK_VOLUME
comma
l_int|5
comma
l_int|0x0000
comma
id|INV
)brace
comma
(brace
id|AC97_MASTER_VOL_MONO
comma
id|SOUND_MIXER_PHONEOUT
comma
l_int|0x3f
comma
id|MO
comma
id|SOUND_MASK_PHONEOUT
comma
l_int|6
comma
l_int|0x0000
comma
id|INV
)brace
comma
(brace
id|AC97_MASTER_TONE
comma
id|SOUND_MIXER_TREBLE
comma
l_int|0x0f
comma
id|MO
comma
id|SOUND_MASK_TREBLE
comma
op_minus
l_int|1
comma
l_int|0x00ff
comma
id|INV
)brace
comma
(brace
id|AC97_MASTER_TONE
comma
id|SOUND_MIXER_BASS
comma
l_int|0x0f
comma
id|MO
comma
id|SOUND_MASK_BASS
comma
op_minus
l_int|1
comma
l_int|0xff00
comma
id|INV
)brace
comma
(brace
id|AC97_PCBEEP_VOL
comma
id|SOUND_MIXER_SPEAKER
comma
l_int|0x0f
comma
id|MO
comma
id|SOUND_MASK_SPEAKER
comma
op_minus
l_int|1
comma
l_int|0x001e
comma
id|INV
)brace
comma
(brace
id|AC97_PHONE_VOL
comma
id|SOUND_MIXER_PHONEIN
comma
l_int|0x1f
comma
id|MO
comma
id|SOUND_MASK_PHONEIN
comma
l_int|7
comma
l_int|0x0000
comma
id|INV
)brace
comma
(brace
id|AC97_MIC_VOL
comma
id|SOUND_MIXER_MIC
comma
l_int|0x1f
comma
id|MO
comma
id|SOUND_MASK_MIC
comma
l_int|0
comma
l_int|0x0000
comma
id|INV
)brace
comma
(brace
id|AC97_LINEIN_VOL
comma
id|SOUND_MIXER_LINE
comma
l_int|0x1f
comma
id|ST
comma
id|SOUND_MASK_LINE
comma
l_int|4
comma
l_int|0x0000
comma
id|INV
)brace
comma
(brace
id|AC97_CD_VOL
comma
id|SOUND_MIXER_CD
comma
l_int|0x1f
comma
id|ST
comma
id|SOUND_MASK_CD
comma
l_int|1
comma
l_int|0x0000
comma
id|INV
)brace
comma
(brace
id|AC97_VIDEO_VOL
comma
id|SOUND_MIXER_VIDEO
comma
l_int|0x1f
comma
id|ST
comma
id|SOUND_MASK_VIDEO
comma
l_int|2
comma
l_int|0x0000
comma
id|INV
)brace
comma
(brace
id|AC97_AUX_VOL
comma
id|SOUND_MIXER_LINE1
comma
l_int|0x1f
comma
id|ST
comma
id|SOUND_MASK_LINE1
comma
l_int|3
comma
l_int|0x0000
comma
id|INV
)brace
comma
(brace
id|AC97_PCMOUT_VOL
comma
id|SOUND_MIXER_PCM
comma
l_int|0x1f
comma
id|ST
comma
id|SOUND_MASK_PCM
comma
op_minus
l_int|1
comma
l_int|0x0000
comma
id|INV
)brace
comma
(brace
id|AC97_RECORD_GAIN
comma
id|SOUND_MIXER_IGAIN
comma
l_int|0x0f
comma
id|ST
comma
id|SOUND_MASK_IGAIN
comma
op_minus
l_int|1
comma
l_int|0x0000
comma
id|NINV
)brace
comma
(brace
op_minus
l_int|1
comma
op_minus
l_int|1
comma
l_int|0xff
comma
l_int|0
comma
l_int|0
comma
op_minus
l_int|1
comma
l_int|0x0000
comma
l_int|0
)brace
comma
)brace
suffix:semicolon
r_static
r_struct
id|ac97_chn_desc
op_star
DECL|function|ac97_find_chndesc
id|ac97_find_chndesc
(paren
r_struct
id|ac97_hwint
op_star
id|dev
comma
r_int
id|oss_channel
)paren
(brace
r_int
id|x
suffix:semicolon
r_for
c_loop
(paren
id|x
op_assign
l_int|0
suffix:semicolon
id|mixerRegs
(braket
id|x
)braket
dot
id|oss_channel
op_ne
op_minus
l_int|1
suffix:semicolon
id|x
op_increment
)paren
(brace
r_if
c_cond
(paren
id|mixerRegs
(braket
id|x
)braket
dot
id|oss_channel
op_eq
id|oss_channel
)paren
r_return
id|mixerRegs
op_plus
id|x
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|ac97_is_valid_channel
id|ac97_is_valid_channel
(paren
r_struct
id|ac97_hwint
op_star
id|dev
comma
r_struct
id|ac97_chn_desc
op_star
id|chn
)paren
(brace
r_return
(paren
id|dev-&gt;last_written_mixer_values
(braket
id|chn-&gt;ac97_regnum
op_div
l_int|2
)braket
op_ne
id|AC97_REG_UNSUPPORTED
)paren
suffix:semicolon
)brace
r_int
DECL|function|ac97_init
id|ac97_init
(paren
r_struct
id|ac97_hwint
op_star
id|dev
)paren
(brace
r_int
id|x
suffix:semicolon
r_int
id|reg0
suffix:semicolon
multiline_comment|/* Clear out the arrays of cached values. */
r_for
c_loop
(paren
id|x
op_assign
l_int|0
suffix:semicolon
id|x
OL
id|AC97_REG_CNT
suffix:semicolon
id|x
op_increment
)paren
id|dev-&gt;last_written_mixer_values
(braket
id|x
)braket
op_assign
id|AC97_REGVAL_UNKNOWN
suffix:semicolon
r_for
c_loop
(paren
id|x
op_assign
l_int|0
suffix:semicolon
id|x
OL
id|SOUND_MIXER_NRDEVICES
suffix:semicolon
id|x
op_increment
)paren
id|dev-&gt;last_written_OSS_values
(braket
id|x
)braket
op_assign
id|AC97_REGVAL_UNKNOWN
suffix:semicolon
multiline_comment|/* Clear the device masks.  */
id|dev-&gt;mixer_devmask
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;mixer_stereomask
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;mixer_recmask
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* ??? Do a &quot;standard reset&quot; via register 0? */
multiline_comment|/* Hardware-dependent reset.  */
r_if
c_cond
(paren
id|dev-&gt;reset_device
(paren
id|dev
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* Check the mixer device capabilities.  */
id|reg0
op_assign
id|dev-&gt;read_reg
(paren
id|dev
comma
id|AC97_RESET
)paren
suffix:semicolon
r_if
c_cond
(paren
id|reg0
OL
l_int|0
)paren
r_return
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* Check for support for treble/bass controls.  */
r_if
c_cond
(paren
op_logical_neg
(paren
id|reg0
op_amp
l_int|4
)paren
)paren
(brace
id|dev-&gt;last_written_mixer_values
(braket
id|AC97_MASTER_TONE
op_div
l_int|2
)braket
op_assign
id|AC97_REG_UNSUPPORTED
suffix:semicolon
)brace
multiline_comment|/* ??? There may be other tests here? */
multiline_comment|/* Fill in the device masks.  */
r_for
c_loop
(paren
id|x
op_assign
l_int|0
suffix:semicolon
id|mixerRegs
(braket
id|x
)braket
dot
id|ac97_regnum
op_ne
op_minus
l_int|1
suffix:semicolon
id|x
op_increment
)paren
(brace
r_if
c_cond
(paren
id|ac97_is_valid_channel
(paren
id|dev
comma
id|mixerRegs
op_plus
id|x
)paren
)paren
(brace
id|dev-&gt;mixer_devmask
op_or_assign
id|mixerRegs
(braket
id|x
)braket
dot
id|oss_mask
suffix:semicolon
r_if
c_cond
(paren
id|mixerRegs
(braket
id|x
)braket
dot
id|is_stereo
)paren
id|dev-&gt;mixer_stereomask
op_or_assign
id|mixerRegs
(braket
id|x
)braket
dot
id|oss_mask
suffix:semicolon
r_if
c_cond
(paren
id|mixerRegs
(braket
id|x
)braket
dot
id|recordNum
op_ne
op_minus
l_int|1
)paren
id|dev-&gt;mixer_recmask
op_or_assign
id|mixerRegs
(braket
id|x
)braket
dot
id|oss_mask
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Reset the mixer to the currently saved settings.  */
r_int
DECL|function|ac97_reset
id|ac97_reset
(paren
r_struct
id|ac97_hwint
op_star
id|dev
)paren
(brace
r_int
id|x
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;reset_device
(paren
id|dev
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* Now set the registers back to their last-written values. */
r_for
c_loop
(paren
id|x
op_assign
l_int|0
suffix:semicolon
id|mixerRegs
(braket
id|x
)braket
dot
id|ac97_regnum
op_ne
op_minus
l_int|1
suffix:semicolon
id|x
op_increment
)paren
(brace
r_int
id|regnum
op_assign
id|mixerRegs
(braket
id|x
)braket
dot
id|ac97_regnum
suffix:semicolon
r_int
id|value
op_assign
id|dev-&gt;last_written_mixer_values
(braket
id|regnum
op_div
l_int|2
)braket
suffix:semicolon
r_if
c_cond
(paren
id|value
op_ge
l_int|0
)paren
id|ac97_put_register
(paren
id|dev
comma
id|regnum
comma
id|value
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Return the contents of register REG; use the cache if the value in it&n;   is valid.  Returns a negative error code on failure. */
r_int
DECL|function|ac97_get_register
id|ac97_get_register
(paren
r_struct
id|ac97_hwint
op_star
id|dev
comma
id|u8
id|reg
)paren
(brace
r_if
c_cond
(paren
id|reg
OG
l_int|127
op_logical_or
(paren
id|reg
op_amp
l_int|1
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* See if it&squot;s in the cache, or if it&squot;s just plain invalid.  */
r_switch
c_cond
(paren
id|dev-&gt;last_written_mixer_values
(braket
id|reg
op_div
l_int|2
)braket
)paren
(brace
r_case
id|AC97_REG_UNSUPPORTED
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AC97_REGVAL_UNKNOWN
suffix:colon
id|dev-&gt;last_written_mixer_values
(braket
id|reg
op_div
l_int|2
)braket
op_assign
id|dev-&gt;read_reg
(paren
id|dev
comma
id|reg
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
r_return
id|dev-&gt;last_written_mixer_values
(braket
id|reg
op_div
l_int|2
)braket
suffix:semicolon
)brace
multiline_comment|/* Write VALUE to AC97 register REG, and cache its value in the last-written&n;   cache.  Returns a negative error code on failure, or 0 on success. */
r_int
DECL|function|ac97_put_register
id|ac97_put_register
(paren
r_struct
id|ac97_hwint
op_star
id|dev
comma
id|u8
id|reg
comma
id|u16
id|value
)paren
(brace
r_if
c_cond
(paren
id|reg
OG
l_int|127
op_logical_or
(paren
id|reg
op_amp
l_int|1
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;last_written_mixer_values
(braket
id|reg
op_div
l_int|2
)braket
op_eq
id|AC97_REG_UNSUPPORTED
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_else
(brace
r_int
id|res
op_assign
id|dev-&gt;write_reg
(paren
id|dev
comma
id|reg
comma
id|value
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
op_ge
l_int|0
)paren
(brace
id|dev-&gt;last_written_mixer_values
(braket
id|reg
op_div
l_int|2
)braket
op_assign
id|value
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_else
r_return
id|res
suffix:semicolon
)brace
)brace
multiline_comment|/* Scale VALUE (a value fro 0 to MAXVAL) to a value from 0-100.  If&n;   IS_STEREO is set, VALUE is a stereo value; the left channel value&n;   is in the lower 8 bits, and the right channel value is in the upper&n;   8 bits.&n;&n;   A negative error code is returned on failure, or the unsigned&n;   scaled value on success.  */
r_static
r_int
DECL|function|ac97_scale_to_oss_val
id|ac97_scale_to_oss_val
(paren
r_int
id|value
comma
r_int
id|maxval
comma
r_int
id|is_stereo
comma
r_int
id|inv
)paren
(brace
multiline_comment|/* Muted?  */
r_if
c_cond
(paren
id|value
op_amp
id|AC97_MUTE
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|is_stereo
)paren
r_return
(paren
id|ac97_scale_to_oss_val
(paren
id|value
op_amp
l_int|255
comma
id|maxval
comma
l_int|0
comma
id|inv
)paren
op_lshift
l_int|8
)paren
op_or
(paren
id|ac97_scale_to_oss_val
(paren
(paren
id|value
op_rshift
l_int|8
)paren
op_amp
l_int|255
comma
id|maxval
comma
l_int|0
comma
id|inv
)paren
op_lshift
l_int|0
)paren
suffix:semicolon
r_else
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/* Inverted. */
r_if
c_cond
(paren
id|inv
)paren
id|value
op_assign
id|maxval
op_minus
id|value
suffix:semicolon
id|i
op_assign
(paren
id|value
op_star
l_int|100
op_plus
(paren
id|maxval
op_div
l_int|2
)paren
)paren
op_div
id|maxval
suffix:semicolon
r_if
c_cond
(paren
id|i
OG
l_int|100
)paren
id|i
op_assign
l_int|100
suffix:semicolon
r_if
c_cond
(paren
id|i
OL
l_int|0
)paren
id|i
op_assign
l_int|0
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
)brace
r_static
r_int
DECL|function|ac97_scale_from_oss_val
id|ac97_scale_from_oss_val
(paren
r_int
id|value
comma
r_int
id|maxval
comma
r_int
id|is_stereo
comma
r_int
id|inv
)paren
(brace
r_if
c_cond
(paren
id|is_stereo
)paren
r_return
(paren
id|ac97_scale_from_oss_val
(paren
id|value
op_amp
l_int|255
comma
id|maxval
comma
l_int|0
comma
id|inv
)paren
op_lshift
l_int|8
)paren
op_or
(paren
id|ac97_scale_from_oss_val
(paren
(paren
id|value
op_rshift
l_int|8
)paren
op_amp
l_int|255
comma
id|maxval
comma
l_int|0
comma
id|inv
)paren
op_lshift
l_int|0
)paren
suffix:semicolon
r_else
(brace
r_int
id|i
op_assign
(paren
(paren
id|value
op_amp
l_int|255
)paren
op_star
id|maxval
op_plus
l_int|50
)paren
op_div
l_int|100
suffix:semicolon
r_if
c_cond
(paren
id|inv
)paren
id|i
op_assign
id|maxval
op_minus
id|i
suffix:semicolon
r_if
c_cond
(paren
id|i
OL
l_int|0
)paren
id|i
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|i
OG
id|maxval
)paren
id|i
op_assign
id|maxval
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
)brace
r_int
DECL|function|ac97_set_mixer
id|ac97_set_mixer
(paren
r_struct
id|ac97_hwint
op_star
id|dev
comma
r_int
id|oss_channel
comma
id|u16
id|oss_value
)paren
(brace
r_int
id|scaled_value
suffix:semicolon
r_struct
id|ac97_chn_desc
op_star
id|channel
op_assign
id|ac97_find_chndesc
(paren
id|dev
comma
id|oss_channel
)paren
suffix:semicolon
r_int
id|result
suffix:semicolon
r_if
c_cond
(paren
id|channel
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ac97_is_valid_channel
(paren
id|dev
comma
id|channel
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|scaled_value
op_assign
id|ac97_scale_from_oss_val
(paren
id|oss_value
comma
id|channel-&gt;maxval
comma
id|channel-&gt;is_stereo
comma
id|channel-&gt;is_inverted
)paren
suffix:semicolon
r_if
c_cond
(paren
id|scaled_value
OL
l_int|0
)paren
r_return
id|scaled_value
suffix:semicolon
r_if
c_cond
(paren
id|channel-&gt;regmask
op_ne
l_int|0
)paren
(brace
r_int
id|mv
suffix:semicolon
r_int
id|oldval
op_assign
id|ac97_get_register
(paren
id|dev
comma
id|channel-&gt;ac97_regnum
)paren
suffix:semicolon
r_if
c_cond
(paren
id|oldval
OL
l_int|0
)paren
r_return
id|oldval
suffix:semicolon
r_for
c_loop
(paren
id|mv
op_assign
id|channel-&gt;regmask
suffix:semicolon
op_logical_neg
(paren
id|mv
op_amp
l_int|1
)paren
suffix:semicolon
id|mv
op_rshift_assign
l_int|1
)paren
id|scaled_value
op_lshift_assign
l_int|1
suffix:semicolon
id|scaled_value
op_and_assign
id|channel-&gt;regmask
suffix:semicolon
id|scaled_value
op_or_assign
(paren
id|oldval
op_amp
op_complement
id|channel-&gt;regmask
)paren
suffix:semicolon
)brace
id|result
op_assign
id|ac97_put_register
(paren
id|dev
comma
id|channel-&gt;ac97_regnum
comma
id|scaled_value
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
op_eq
l_int|0
)paren
id|dev-&gt;last_written_OSS_values
(braket
id|oss_channel
)braket
op_assign
id|oss_value
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
r_int
DECL|function|ac97_get_mixer_scaled
id|ac97_get_mixer_scaled
(paren
r_struct
id|ac97_hwint
op_star
id|dev
comma
r_int
id|oss_channel
)paren
(brace
r_struct
id|ac97_chn_desc
op_star
id|channel
op_assign
id|ac97_find_chndesc
(paren
id|dev
comma
id|oss_channel
)paren
suffix:semicolon
r_int
id|regval
suffix:semicolon
r_if
c_cond
(paren
id|channel
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ac97_is_valid_channel
(paren
id|dev
comma
id|channel
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|regval
op_assign
id|ac97_get_register
(paren
id|dev
comma
id|channel-&gt;ac97_regnum
)paren
suffix:semicolon
r_if
c_cond
(paren
id|regval
OL
l_int|0
)paren
r_return
id|regval
suffix:semicolon
r_if
c_cond
(paren
id|channel-&gt;regmask
op_ne
l_int|0
)paren
(brace
r_int
id|mv
suffix:semicolon
id|regval
op_and_assign
id|channel-&gt;regmask
suffix:semicolon
r_for
c_loop
(paren
id|mv
op_assign
id|channel-&gt;regmask
suffix:semicolon
op_logical_neg
(paren
id|mv
op_amp
l_int|1
)paren
suffix:semicolon
id|mv
op_rshift_assign
l_int|1
)paren
id|regval
op_rshift_assign
l_int|1
suffix:semicolon
)brace
r_return
id|ac97_scale_to_oss_val
(paren
id|regval
comma
id|channel-&gt;maxval
comma
id|channel-&gt;is_stereo
comma
id|channel-&gt;is_inverted
)paren
suffix:semicolon
)brace
r_int
DECL|function|ac97_get_recmask
id|ac97_get_recmask
(paren
r_struct
id|ac97_hwint
op_star
id|dev
)paren
(brace
r_int
id|recReg
op_assign
id|ac97_get_register
(paren
id|dev
comma
id|AC97_RECORD_SELECT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|recReg
OL
l_int|0
)paren
r_return
id|recReg
suffix:semicolon
r_else
(brace
r_int
id|x
suffix:semicolon
r_for
c_loop
(paren
id|x
op_assign
l_int|0
suffix:semicolon
id|mixerRegs
(braket
id|x
)braket
dot
id|ac97_regnum
op_ge
l_int|0
suffix:semicolon
id|x
op_increment
)paren
(brace
r_if
c_cond
(paren
id|mixerRegs
(braket
id|x
)braket
dot
id|recordNum
op_eq
(paren
id|recReg
op_amp
l_int|7
)paren
)paren
r_return
id|mixerRegs
(braket
id|x
)braket
dot
id|oss_mask
suffix:semicolon
)brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
)brace
r_int
DECL|function|ac97_set_recmask
id|ac97_set_recmask
(paren
r_struct
id|ac97_hwint
op_star
id|dev
comma
r_int
id|oss_recmask
)paren
(brace
r_int
id|x
suffix:semicolon
r_if
c_cond
(paren
id|oss_recmask
op_eq
l_int|0
)paren
id|oss_recmask
op_assign
id|SOUND_MIXER_MIC
suffix:semicolon
r_for
c_loop
(paren
id|x
op_assign
l_int|0
suffix:semicolon
id|mixerRegs
(braket
id|x
)braket
dot
id|ac97_regnum
op_ge
l_int|0
suffix:semicolon
id|x
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
id|mixerRegs
(braket
id|x
)braket
dot
id|recordNum
op_ge
l_int|0
)paren
op_logical_and
(paren
id|oss_recmask
op_amp
id|mixerRegs
(braket
id|x
)braket
dot
id|oss_mask
)paren
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|mixerRegs
(braket
id|x
)braket
dot
id|ac97_regnum
OL
l_int|0
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_else
(brace
r_int
id|regval
op_assign
(paren
id|mixerRegs
(braket
id|x
)braket
dot
id|recordNum
op_lshift
l_int|8
)paren
op_or
id|mixerRegs
(braket
id|x
)braket
dot
id|recordNum
suffix:semicolon
r_int
id|res
op_assign
id|ac97_put_register
(paren
id|dev
comma
id|AC97_RECORD_SELECT
comma
id|regval
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
op_eq
l_int|0
)paren
r_return
id|ac97_get_recmask
(paren
id|dev
)paren
suffix:semicolon
r_else
r_return
id|res
suffix:semicolon
)brace
)brace
multiline_comment|/* Set the mixer DEV to the list of values in VALUE_LIST.  Return 0 on&n;   success, or a negative error code.  */
r_int
DECL|function|ac97_set_values
id|ac97_set_values
(paren
r_struct
id|ac97_hwint
op_star
id|dev
comma
r_struct
id|ac97_mixer_value_list
op_star
id|value_list
)paren
(brace
r_int
id|x
suffix:semicolon
r_for
c_loop
(paren
id|x
op_assign
l_int|0
suffix:semicolon
id|value_list
(braket
id|x
)braket
dot
id|oss_channel
op_ne
op_minus
l_int|1
suffix:semicolon
id|x
op_increment
)paren
(brace
r_int
id|chnum
op_assign
id|value_list
(braket
id|x
)braket
dot
id|oss_channel
suffix:semicolon
r_struct
id|ac97_chn_desc
op_star
id|chent
op_assign
id|ac97_find_chndesc
(paren
id|dev
comma
id|chnum
)paren
suffix:semicolon
r_if
c_cond
(paren
id|chent
op_ne
l_int|NULL
)paren
(brace
id|u16
id|val
suffix:semicolon
r_int
id|res
suffix:semicolon
r_if
c_cond
(paren
id|chent-&gt;is_stereo
)paren
id|val
op_assign
(paren
id|value_list
(braket
id|x
)braket
dot
id|value.stereo.right
op_lshift
l_int|8
)paren
op_or
id|value_list
(braket
id|x
)braket
dot
id|value.stereo.left
suffix:semicolon
r_else
(brace
multiline_comment|/* We do this so the returned value looks OK in the&n;&t;&t;   mixer app.  It&squot;s not necessary otherwise.  */
id|val
op_assign
(paren
id|value_list
(braket
id|x
)braket
dot
id|value.mono
op_lshift
l_int|8
)paren
op_or
id|value_list
(braket
id|x
)braket
dot
id|value.mono
suffix:semicolon
)brace
id|res
op_assign
id|ac97_set_mixer
(paren
id|dev
comma
id|chnum
comma
id|val
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
OL
l_int|0
)paren
r_return
id|res
suffix:semicolon
)brace
r_else
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_int
DECL|function|ac97_mixer_ioctl
id|ac97_mixer_ioctl
(paren
r_struct
id|ac97_hwint
op_star
id|dev
comma
r_int
r_int
id|cmd
comma
id|caddr_t
id|arg
)paren
(brace
r_int
id|ret
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|SOUND_MIXER_READ_RECSRC
suffix:colon
id|ret
op_assign
id|ac97_get_recmask
(paren
id|dev
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SOUND_MIXER_WRITE_RECSRC
suffix:colon
(brace
r_if
c_cond
(paren
id|get_user
(paren
id|ret
comma
(paren
r_int
op_star
)paren
id|arg
)paren
)paren
id|ret
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_else
id|ret
op_assign
id|ac97_set_recmask
(paren
id|dev
comma
id|ret
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|SOUND_MIXER_READ_CAPS
suffix:colon
id|ret
op_assign
id|SOUND_CAP_EXCL_INPUT
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SOUND_MIXER_READ_DEVMASK
suffix:colon
id|ret
op_assign
id|dev-&gt;mixer_devmask
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SOUND_MIXER_READ_RECMASK
suffix:colon
id|ret
op_assign
id|dev-&gt;mixer_recmask
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SOUND_MIXER_READ_STEREODEVS
suffix:colon
id|ret
op_assign
id|dev-&gt;mixer_stereomask
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* Read or write request. */
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|_IOC_TYPE
(paren
id|cmd
)paren
op_eq
l_char|&squot;M&squot;
)paren
(brace
r_int
id|dir
op_assign
id|_SIOC_DIR
(paren
id|cmd
)paren
suffix:semicolon
r_int
id|channel
op_assign
id|_IOC_NR
(paren
id|cmd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|channel
op_ge
l_int|0
op_logical_and
id|channel
OL
id|SOUND_MIXER_NRDEVICES
)paren
(brace
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|dir
op_amp
id|_SIOC_WRITE
)paren
(brace
r_int
id|val
suffix:semicolon
r_if
c_cond
(paren
id|get_user
(paren
id|val
comma
(paren
r_int
op_star
)paren
id|arg
)paren
op_eq
l_int|0
)paren
id|ret
op_assign
id|ac97_set_mixer
(paren
id|dev
comma
id|channel
comma
id|val
)paren
suffix:semicolon
r_else
id|ret
op_assign
op_minus
id|EFAULT
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ret
op_ge
l_int|0
op_logical_and
(paren
id|dir
op_amp
id|_SIOC_READ
)paren
)paren
(brace
r_if
c_cond
(paren
id|dev-&gt;last_written_OSS_values
(braket
id|channel
)braket
op_eq
id|AC97_REGVAL_UNKNOWN
)paren
id|dev-&gt;last_written_OSS_values
(braket
id|channel
)braket
op_assign
id|ac97_get_mixer_scaled
(paren
id|dev
comma
id|channel
)paren
suffix:semicolon
id|ret
op_assign
id|dev-&gt;last_written_OSS_values
(braket
id|channel
)braket
suffix:semicolon
)brace
)brace
)brace
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
r_else
r_return
id|put_user
c_func
(paren
id|ret
comma
(paren
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
)brace
DECL|variable|ac97_init
id|EXPORT_SYMBOL
c_func
(paren
id|ac97_init
)paren
suffix:semicolon
DECL|variable|ac97_set_values
id|EXPORT_SYMBOL
c_func
(paren
id|ac97_set_values
)paren
suffix:semicolon
DECL|variable|ac97_set_mixer
id|EXPORT_SYMBOL
c_func
(paren
id|ac97_set_mixer
)paren
suffix:semicolon
DECL|variable|ac97_get_register
id|EXPORT_SYMBOL
c_func
(paren
id|ac97_get_register
)paren
suffix:semicolon
DECL|variable|ac97_put_register
id|EXPORT_SYMBOL
c_func
(paren
id|ac97_put_register
)paren
suffix:semicolon
DECL|variable|ac97_get_mixer_scaled
id|EXPORT_SYMBOL
c_func
(paren
id|ac97_get_mixer_scaled
)paren
suffix:semicolon
DECL|variable|ac97_mixer_ioctl
id|EXPORT_SYMBOL
c_func
(paren
id|ac97_mixer_ioctl
)paren
suffix:semicolon
DECL|variable|ac97_reset
id|EXPORT_SYMBOL
c_func
(paren
id|ac97_reset
)paren
suffix:semicolon
"&f;"
multiline_comment|/*&n; * Local variables:&n; *  c-basic-offset: 4&n; * End:&n; */
eof
