multiline_comment|/*&n; * sound/ad1848_mixer.h&n; *&n; * Definitions for the mixer of AD1848 and compatible codecs.&n; */
multiline_comment|/*&n; * Copyright (C) by Hannu Savolainen 1993-1997&n; *&n; * OSS/Free for Linux is distributed under the GNU GENERAL PUBLIC LICENSE (GPL)&n; * Version 2 (June 1991). See the &quot;COPYING&quot; file distributed with this software&n; * for more info.&n; */
multiline_comment|/*&n; * The AD1848 codec has generic input lines called Line, Aux1 and Aux2.&n; * Sound card manufacturers have connected actual inputs (CD, synth, line,&n; * etc) to these inputs in different order. Therefore it&squot;s difficult&n; * to assign mixer channels to these inputs correctly. The following&n; * contains two alternative mappings. The first one is for GUS MAX and&n; * the second is just a generic one (line1, line2 and line3).&n; * (Actually this is not a mapping but rather some kind of interleaving&n; * solution).&n; */
DECL|macro|MODE1_REC_DEVICES
mdefine_line|#define MODE1_REC_DEVICES&t;&t;(SOUND_MASK_LINE3 | SOUND_MASK_MIC | &bslash;&n;&t;&t;&t;&t;&t; SOUND_MASK_LINE1 | SOUND_MASK_IMIX)
DECL|macro|SPRO_REC_DEVICES
mdefine_line|#define SPRO_REC_DEVICES&t;&t;(SOUND_MASK_LINE | SOUND_MASK_MIC | &bslash;&n;&t;&t;&t;&t;&t; SOUND_MASK_CD | SOUND_MASK_LINE1)
DECL|macro|MODE1_MIXER_DEVICES
mdefine_line|#define MODE1_MIXER_DEVICES&t;&t;(SOUND_MASK_LINE1 | SOUND_MASK_MIC | &bslash;&n;&t;&t;&t;&t;&t; SOUND_MASK_LINE2 | &bslash;&n;&t;&t;&t;&t;&t; SOUND_MASK_IGAIN | &bslash;&n;&t;&t;&t;&t;&t; SOUND_MASK_PCM | SOUND_MASK_IMIX)
DECL|macro|MODE2_MIXER_DEVICES
mdefine_line|#define MODE2_MIXER_DEVICES&t;&t;(SOUND_MASK_LINE1 | SOUND_MASK_LINE2 | &bslash;&n;&t;&t;&t;&t;&t; SOUND_MASK_MIC | &bslash;&n;&t;&t;&t;&t;&t; SOUND_MASK_LINE3 | SOUND_MASK_SPEAKER | &bslash;&n;&t;&t;&t;&t;&t; SOUND_MASK_IGAIN | &bslash;&n;&t;&t;&t;&t;&t; SOUND_MASK_PCM | SOUND_MASK_IMIX)
DECL|macro|MODE3_MIXER_DEVICES
mdefine_line|#define MODE3_MIXER_DEVICES&t;&t;(MODE2_MIXER_DEVICES | SOUND_MASK_VOLUME)
multiline_comment|/* OPTi 82C930 has no IMIX level control, but it can still be selected as an&n; * input&n; */
DECL|macro|C930_MIXER_DEVICES
mdefine_line|#define C930_MIXER_DEVICES&t;(SOUND_MASK_LINE1 | SOUND_MASK_LINE2 | &bslash;&n;&t;&t;&t;&t; SOUND_MASK_MIC | SOUND_MASK_VOLUME | &bslash;&n;&t;&t;&t;&t; SOUND_MASK_LINE3 | &bslash;&n;&t;&t;&t;&t; SOUND_MASK_IGAIN | SOUND_MASK_PCM)
DECL|macro|SPRO_MIXER_DEVICES
mdefine_line|#define SPRO_MIXER_DEVICES&t;(SOUND_MASK_VOLUME | SOUND_MASK_PCM | &bslash;&n;&t;&t;&t;&t; SOUND_MASK_LINE | SOUND_MASK_SYNTH | &bslash;&n;&t;&t;&t;&t; SOUND_MASK_CD | SOUND_MASK_MIC | &bslash;&n;&t;&t;&t;&t; SOUND_MASK_SPEAKER | SOUND_MASK_LINE1 | &bslash;&n;&t;&t;&t;&t; SOUND_MASK_OGAIN)
DECL|struct|mixer_def
r_struct
id|mixer_def
(brace
DECL|member|regno
r_int
r_int
id|regno
suffix:colon
l_int|6
suffix:semicolon
multiline_comment|/* register number for volume */
DECL|member|polarity
r_int
r_int
id|polarity
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* volume polarity: 0=normal, 1=reversed */
DECL|member|bitpos
r_int
r_int
id|bitpos
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* position of bits in register for volume */
DECL|member|nbits
r_int
r_int
id|nbits
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* number of bits in register for volume */
DECL|member|mutereg
r_int
r_int
id|mutereg
suffix:colon
l_int|6
suffix:semicolon
multiline_comment|/* register number for mute bit */
DECL|member|mutepol
r_int
r_int
id|mutepol
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* mute polarity: 0=normal, 1=reversed */
DECL|member|mutepos
r_int
r_int
id|mutepos
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* position of mute bit in register */
DECL|member|recreg
r_int
r_int
id|recreg
suffix:colon
l_int|6
suffix:semicolon
multiline_comment|/* register number for recording bit */
DECL|member|recpol
r_int
r_int
id|recpol
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* recording polarity: 0=normal, 1=reversed */
DECL|member|recpos
r_int
r_int
id|recpos
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* position of recording bit in register */
)brace
suffix:semicolon
DECL|variable|mix_cvt
r_static
r_char
id|mix_cvt
(braket
l_int|101
)braket
op_assign
(brace
l_int|0
comma
l_int|0
comma
l_int|3
comma
l_int|7
comma
l_int|10
comma
l_int|13
comma
l_int|16
comma
l_int|19
comma
l_int|21
comma
l_int|23
comma
l_int|26
comma
l_int|28
comma
l_int|30
comma
l_int|32
comma
l_int|34
comma
l_int|35
comma
l_int|37
comma
l_int|39
comma
l_int|40
comma
l_int|42
comma
l_int|43
comma
l_int|45
comma
l_int|46
comma
l_int|47
comma
l_int|49
comma
l_int|50
comma
l_int|51
comma
l_int|52
comma
l_int|53
comma
l_int|55
comma
l_int|56
comma
l_int|57
comma
l_int|58
comma
l_int|59
comma
l_int|60
comma
l_int|61
comma
l_int|62
comma
l_int|63
comma
l_int|64
comma
l_int|65
comma
l_int|65
comma
l_int|66
comma
l_int|67
comma
l_int|68
comma
l_int|69
comma
l_int|70
comma
l_int|70
comma
l_int|71
comma
l_int|72
comma
l_int|73
comma
l_int|73
comma
l_int|74
comma
l_int|75
comma
l_int|75
comma
l_int|76
comma
l_int|77
comma
l_int|77
comma
l_int|78
comma
l_int|79
comma
l_int|79
comma
l_int|80
comma
l_int|81
comma
l_int|81
comma
l_int|82
comma
l_int|82
comma
l_int|83
comma
l_int|84
comma
l_int|84
comma
l_int|85
comma
l_int|85
comma
l_int|86
comma
l_int|86
comma
l_int|87
comma
l_int|87
comma
l_int|88
comma
l_int|88
comma
l_int|89
comma
l_int|89
comma
l_int|90
comma
l_int|90
comma
l_int|91
comma
l_int|91
comma
l_int|92
comma
l_int|92
comma
l_int|93
comma
l_int|93
comma
l_int|94
comma
l_int|94
comma
l_int|95
comma
l_int|95
comma
l_int|96
comma
l_int|96
comma
l_int|96
comma
l_int|97
comma
l_int|97
comma
l_int|98
comma
l_int|98
comma
l_int|98
comma
l_int|99
comma
l_int|99
comma
l_int|100
)brace
suffix:semicolon
DECL|typedef|mixer_ent
r_typedef
r_struct
id|mixer_def
id|mixer_ent
suffix:semicolon
DECL|typedef|mixer_ents
r_typedef
id|mixer_ent
id|mixer_ents
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/*&n; * Most of the mixer entries work in backwards. Setting the polarity field&n; * makes them to work correctly.&n; *&n; * The channel numbering used by individual sound cards is not fixed. Some&n; * cards have assigned different meanings for the AUX1, AUX2 and LINE inputs.&n; * The current version doesn&squot;t try to compensate this.&n; */
DECL|macro|MIX_ENT
mdefine_line|#define MIX_ENT(name, reg_l, pola_l, pos_l, len_l, reg_r, pola_r, pos_r, len_r, mute_bit)&t;&bslash;&n;&t;[name] = {{reg_l, pola_l, pos_l, len_l, reg_l, 0, mute_bit, 0, 0, 8},&t;&t;&t;&bslash;&n;&t;&t;  {reg_r, pola_r, pos_r, len_r, reg_r, 0, mute_bit, 0, 0, 8}}
DECL|macro|MIX_ENT2
mdefine_line|#define MIX_ENT2(name, reg_l, pola_l, pos_l, len_l, mute_reg_l, mute_pola_l, mute_pos_l, &bslash;&n;&t;&t;    rec_reg_l, rec_pola_l, rec_pos_l,&t;&t;&t;&t;&t; &bslash;&n;&t;&t; reg_r, pola_r, pos_r, len_r, mute_reg_r, mute_pola_r, mute_pos_r,&t; &bslash;&n;&t;&t;    rec_reg_r, rec_pola_r, rec_pos_r)&t;&t;&t;&t;&t; &bslash;&n;&t;[name] = {{reg_l, pola_l, pos_l, len_l, mute_reg_l, mute_pola_l, mute_pos_l,&t; &bslash;&n;&t;&t;    rec_reg_l, rec_pola_l, rec_pos_l},&t;&t;&t;&t;&t; &bslash;&n;&t;&t;  {reg_r, pola_r, pos_r, len_r, mute_reg_r, mute_pola_r, mute_pos_r,&t; &bslash;&n;&t;&t;    rec_reg_r, rec_pola_r, rec_pos_r}}
DECL|variable|ad1848_mix_devices
r_static
id|mixer_ents
id|ad1848_mix_devices
(braket
l_int|32
)braket
op_assign
(brace
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_VOLUME
comma
l_int|27
comma
l_int|1
comma
l_int|0
comma
l_int|4
comma
l_int|29
comma
l_int|1
comma
l_int|0
comma
l_int|4
comma
l_int|8
)paren
comma
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_BASS
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|8
)paren
comma
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_TREBLE
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|8
)paren
comma
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_SYNTH
comma
l_int|4
comma
l_int|1
comma
l_int|0
comma
l_int|5
comma
l_int|5
comma
l_int|1
comma
l_int|0
comma
l_int|5
comma
l_int|7
)paren
comma
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_PCM
comma
l_int|6
comma
l_int|1
comma
l_int|0
comma
l_int|6
comma
l_int|7
comma
l_int|1
comma
l_int|0
comma
l_int|6
comma
l_int|7
)paren
comma
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_SPEAKER
comma
l_int|26
comma
l_int|1
comma
l_int|0
comma
l_int|4
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|8
)paren
comma
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_LINE
comma
l_int|18
comma
l_int|1
comma
l_int|0
comma
l_int|5
comma
l_int|19
comma
l_int|1
comma
l_int|0
comma
l_int|5
comma
l_int|7
)paren
comma
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_MIC
comma
l_int|0
comma
l_int|0
comma
l_int|5
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|5
comma
l_int|1
comma
l_int|8
)paren
comma
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_CD
comma
l_int|2
comma
l_int|1
comma
l_int|0
comma
l_int|5
comma
l_int|3
comma
l_int|1
comma
l_int|0
comma
l_int|5
comma
l_int|7
)paren
comma
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_IMIX
comma
l_int|13
comma
l_int|1
comma
l_int|2
comma
l_int|6
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|8
)paren
comma
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_ALTPCM
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|8
)paren
comma
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_RECLEV
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|8
)paren
comma
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_IGAIN
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|4
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|4
comma
l_int|8
)paren
comma
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_OGAIN
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|8
)paren
comma
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_LINE1
comma
l_int|2
comma
l_int|1
comma
l_int|0
comma
l_int|5
comma
l_int|3
comma
l_int|1
comma
l_int|0
comma
l_int|5
comma
l_int|7
)paren
comma
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_LINE2
comma
l_int|4
comma
l_int|1
comma
l_int|0
comma
l_int|5
comma
l_int|5
comma
l_int|1
comma
l_int|0
comma
l_int|5
comma
l_int|7
)paren
comma
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_LINE3
comma
l_int|18
comma
l_int|1
comma
l_int|0
comma
l_int|5
comma
l_int|19
comma
l_int|1
comma
l_int|0
comma
l_int|5
comma
l_int|7
)paren
)brace
suffix:semicolon
DECL|variable|iwave_mix_devices
r_static
id|mixer_ents
id|iwave_mix_devices
(braket
l_int|32
)braket
op_assign
(brace
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_VOLUME
comma
l_int|25
comma
l_int|1
comma
l_int|0
comma
l_int|5
comma
l_int|27
comma
l_int|1
comma
l_int|0
comma
l_int|5
comma
l_int|8
)paren
comma
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_BASS
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|8
)paren
comma
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_TREBLE
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|8
)paren
comma
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_SYNTH
comma
l_int|4
comma
l_int|1
comma
l_int|0
comma
l_int|5
comma
l_int|5
comma
l_int|1
comma
l_int|0
comma
l_int|5
comma
l_int|7
)paren
comma
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_PCM
comma
l_int|6
comma
l_int|1
comma
l_int|0
comma
l_int|6
comma
l_int|7
comma
l_int|1
comma
l_int|0
comma
l_int|6
comma
l_int|7
)paren
comma
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_SPEAKER
comma
l_int|26
comma
l_int|1
comma
l_int|0
comma
l_int|4
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|8
)paren
comma
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_LINE
comma
l_int|18
comma
l_int|1
comma
l_int|0
comma
l_int|5
comma
l_int|19
comma
l_int|1
comma
l_int|0
comma
l_int|5
comma
l_int|7
)paren
comma
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_MIC
comma
l_int|0
comma
l_int|0
comma
l_int|5
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|5
comma
l_int|1
comma
l_int|8
)paren
comma
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_CD
comma
l_int|2
comma
l_int|1
comma
l_int|0
comma
l_int|5
comma
l_int|3
comma
l_int|1
comma
l_int|0
comma
l_int|5
comma
l_int|7
)paren
comma
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_IMIX
comma
l_int|16
comma
l_int|1
comma
l_int|0
comma
l_int|5
comma
l_int|17
comma
l_int|1
comma
l_int|0
comma
l_int|5
comma
l_int|8
)paren
comma
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_ALTPCM
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|8
)paren
comma
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_RECLEV
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|8
)paren
comma
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_IGAIN
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|4
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|4
comma
l_int|8
)paren
comma
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_OGAIN
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|8
)paren
comma
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_LINE1
comma
l_int|2
comma
l_int|1
comma
l_int|0
comma
l_int|5
comma
l_int|3
comma
l_int|1
comma
l_int|0
comma
l_int|5
comma
l_int|7
)paren
comma
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_LINE2
comma
l_int|4
comma
l_int|1
comma
l_int|0
comma
l_int|5
comma
l_int|5
comma
l_int|1
comma
l_int|0
comma
l_int|5
comma
l_int|7
)paren
comma
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_LINE3
comma
l_int|18
comma
l_int|1
comma
l_int|0
comma
l_int|5
comma
l_int|19
comma
l_int|1
comma
l_int|0
comma
l_int|5
comma
l_int|7
)paren
)brace
suffix:semicolon
DECL|variable|cs42xb_mix_devices
r_static
id|mixer_ents
id|cs42xb_mix_devices
(braket
l_int|32
)braket
op_assign
(brace
multiline_comment|/* Digital master volume actually has seven bits, but we only use&n;&t;   six to avoid the discontinuity when the analog gain kicks in. */
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_VOLUME
comma
l_int|46
comma
l_int|1
comma
l_int|0
comma
l_int|6
comma
l_int|47
comma
l_int|1
comma
l_int|0
comma
l_int|6
comma
l_int|7
)paren
comma
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_BASS
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|8
)paren
comma
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_TREBLE
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|8
)paren
comma
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_SYNTH
comma
l_int|4
comma
l_int|1
comma
l_int|0
comma
l_int|5
comma
l_int|5
comma
l_int|1
comma
l_int|0
comma
l_int|5
comma
l_int|7
)paren
comma
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_PCM
comma
l_int|6
comma
l_int|1
comma
l_int|0
comma
l_int|6
comma
l_int|7
comma
l_int|1
comma
l_int|0
comma
l_int|6
comma
l_int|7
)paren
comma
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_SPEAKER
comma
l_int|26
comma
l_int|1
comma
l_int|0
comma
l_int|4
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|8
)paren
comma
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_LINE
comma
l_int|18
comma
l_int|1
comma
l_int|0
comma
l_int|5
comma
l_int|19
comma
l_int|1
comma
l_int|0
comma
l_int|5
comma
l_int|7
)paren
comma
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_MIC
comma
l_int|34
comma
l_int|1
comma
l_int|0
comma
l_int|5
comma
l_int|35
comma
l_int|1
comma
l_int|0
comma
l_int|5
comma
l_int|7
)paren
comma
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_CD
comma
l_int|2
comma
l_int|1
comma
l_int|0
comma
l_int|5
comma
l_int|3
comma
l_int|1
comma
l_int|0
comma
l_int|5
comma
l_int|7
)paren
comma
multiline_comment|/* For the IMIX entry, it was not possible to use the MIX_ENT macro&n;&t;   because the mute bit is in different positions for the two&n;&t;   channels and requires reverse polarity. */
(braket
id|SOUND_MIXER_IMIX
)braket
op_assign
(brace
(brace
l_int|13
comma
l_int|1
comma
l_int|2
comma
l_int|6
comma
l_int|13
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|8
)brace
comma
(brace
l_int|42
comma
l_int|1
comma
l_int|0
comma
l_int|6
comma
l_int|42
comma
l_int|1
comma
l_int|7
comma
l_int|0
comma
l_int|0
comma
l_int|8
)brace
)brace
comma
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_ALTPCM
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|8
)paren
comma
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_RECLEV
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|8
)paren
comma
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_IGAIN
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|4
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|4
comma
l_int|8
)paren
comma
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_OGAIN
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|8
)paren
comma
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_LINE1
comma
l_int|2
comma
l_int|1
comma
l_int|0
comma
l_int|5
comma
l_int|3
comma
l_int|1
comma
l_int|0
comma
l_int|5
comma
l_int|7
)paren
comma
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_LINE2
comma
l_int|4
comma
l_int|1
comma
l_int|0
comma
l_int|5
comma
l_int|5
comma
l_int|1
comma
l_int|0
comma
l_int|5
comma
l_int|7
)paren
comma
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_LINE3
comma
l_int|38
comma
l_int|1
comma
l_int|0
comma
l_int|6
comma
l_int|39
comma
l_int|1
comma
l_int|0
comma
l_int|6
comma
l_int|7
)paren
)brace
suffix:semicolon
multiline_comment|/* OPTi 82C930 has somewhat different port addresses.&n; * Note: VOLUME == SPEAKER, SYNTH == LINE2, LINE == LINE3, CD == LINE1&n; * VOLUME, SYNTH, LINE, CD are not enabled above.&n; * MIC is level of mic monitoring direct to output. Same for CD, LINE, etc.&n; */
DECL|variable|c930_mix_devices
r_static
id|mixer_ents
id|c930_mix_devices
(braket
l_int|32
)braket
op_assign
(brace
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_VOLUME
comma
l_int|22
comma
l_int|1
comma
l_int|1
comma
l_int|5
comma
l_int|23
comma
l_int|1
comma
l_int|1
comma
l_int|5
comma
l_int|7
)paren
comma
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_BASS
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|8
)paren
comma
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_TREBLE
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|8
)paren
comma
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_SYNTH
comma
l_int|4
comma
l_int|1
comma
l_int|1
comma
l_int|4
comma
l_int|5
comma
l_int|1
comma
l_int|1
comma
l_int|4
comma
l_int|7
)paren
comma
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_PCM
comma
l_int|6
comma
l_int|1
comma
l_int|0
comma
l_int|5
comma
l_int|7
comma
l_int|1
comma
l_int|0
comma
l_int|5
comma
l_int|7
)paren
comma
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_SPEAKER
comma
l_int|22
comma
l_int|1
comma
l_int|1
comma
l_int|5
comma
l_int|23
comma
l_int|1
comma
l_int|1
comma
l_int|5
comma
l_int|7
)paren
comma
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_LINE
comma
l_int|18
comma
l_int|1
comma
l_int|1
comma
l_int|4
comma
l_int|19
comma
l_int|1
comma
l_int|1
comma
l_int|4
comma
l_int|7
)paren
comma
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_MIC
comma
l_int|20
comma
l_int|1
comma
l_int|1
comma
l_int|4
comma
l_int|21
comma
l_int|1
comma
l_int|1
comma
l_int|4
comma
l_int|7
)paren
comma
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_CD
comma
l_int|2
comma
l_int|1
comma
l_int|1
comma
l_int|4
comma
l_int|3
comma
l_int|1
comma
l_int|1
comma
l_int|4
comma
l_int|7
)paren
comma
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_IMIX
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|8
)paren
comma
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_ALTPCM
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|8
)paren
comma
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_RECLEV
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|8
)paren
comma
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_IGAIN
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|4
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|4
comma
l_int|8
)paren
comma
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_OGAIN
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|8
)paren
comma
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_LINE1
comma
l_int|2
comma
l_int|1
comma
l_int|1
comma
l_int|4
comma
l_int|3
comma
l_int|1
comma
l_int|1
comma
l_int|4
comma
l_int|7
)paren
comma
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_LINE2
comma
l_int|4
comma
l_int|1
comma
l_int|1
comma
l_int|4
comma
l_int|5
comma
l_int|1
comma
l_int|1
comma
l_int|4
comma
l_int|7
)paren
comma
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_LINE3
comma
l_int|18
comma
l_int|1
comma
l_int|1
comma
l_int|4
comma
l_int|19
comma
l_int|1
comma
l_int|1
comma
l_int|4
comma
l_int|7
)paren
)brace
suffix:semicolon
DECL|variable|spro_mix_devices
r_static
id|mixer_ents
id|spro_mix_devices
(braket
l_int|32
)braket
op_assign
(brace
id|MIX_ENT
(paren
id|SOUND_MIXER_VOLUME
comma
l_int|19
comma
l_int|0
comma
l_int|4
comma
l_int|4
comma
l_int|19
comma
l_int|0
comma
l_int|0
comma
l_int|4
comma
l_int|8
)paren
comma
id|MIX_ENT
(paren
id|SOUND_MIXER_BASS
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|8
)paren
comma
id|MIX_ENT
(paren
id|SOUND_MIXER_TREBLE
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|8
)paren
comma
id|MIX_ENT2
c_func
(paren
id|SOUND_MIXER_SYNTH
comma
l_int|4
comma
l_int|1
comma
l_int|1
comma
l_int|4
comma
l_int|23
comma
l_int|0
comma
l_int|3
comma
l_int|0
comma
l_int|0
comma
l_int|8
comma
l_int|5
comma
l_int|1
comma
l_int|1
comma
l_int|4
comma
l_int|23
comma
l_int|0
comma
l_int|3
comma
l_int|0
comma
l_int|0
comma
l_int|8
)paren
comma
id|MIX_ENT
(paren
id|SOUND_MIXER_PCM
comma
l_int|6
comma
l_int|1
comma
l_int|1
comma
l_int|4
comma
l_int|7
comma
l_int|1
comma
l_int|1
comma
l_int|4
comma
l_int|8
)paren
comma
id|MIX_ENT
(paren
id|SOUND_MIXER_SPEAKER
comma
l_int|18
comma
l_int|0
comma
l_int|3
comma
l_int|2
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|8
)paren
comma
id|MIX_ENT2
c_func
(paren
id|SOUND_MIXER_LINE
comma
l_int|20
comma
l_int|0
comma
l_int|4
comma
l_int|4
comma
l_int|17
comma
l_int|1
comma
l_int|4
comma
l_int|16
comma
l_int|0
comma
l_int|2
comma
l_int|20
comma
l_int|0
comma
l_int|0
comma
l_int|4
comma
l_int|17
comma
l_int|1
comma
l_int|3
comma
l_int|16
comma
l_int|0
comma
l_int|1
)paren
comma
id|MIX_ENT2
c_func
(paren
id|SOUND_MIXER_MIC
comma
l_int|18
comma
l_int|0
comma
l_int|0
comma
l_int|3
comma
l_int|17
comma
l_int|1
comma
l_int|0
comma
l_int|16
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
comma
id|MIX_ENT2
c_func
(paren
id|SOUND_MIXER_CD
comma
l_int|21
comma
l_int|0
comma
l_int|4
comma
l_int|4
comma
l_int|17
comma
l_int|1
comma
l_int|2
comma
l_int|16
comma
l_int|0
comma
l_int|4
comma
l_int|21
comma
l_int|0
comma
l_int|0
comma
l_int|4
comma
l_int|17
comma
l_int|1
comma
l_int|1
comma
l_int|16
comma
l_int|0
comma
l_int|3
)paren
comma
id|MIX_ENT
(paren
id|SOUND_MIXER_IMIX
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|8
)paren
comma
id|MIX_ENT
(paren
id|SOUND_MIXER_ALTPCM
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|8
)paren
comma
id|MIX_ENT
(paren
id|SOUND_MIXER_RECLEV
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|8
)paren
comma
id|MIX_ENT
(paren
id|SOUND_MIXER_IGAIN
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|8
)paren
comma
id|MIX_ENT
(paren
id|SOUND_MIXER_OGAIN
comma
l_int|17
comma
l_int|1
comma
l_int|6
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|8
)paren
comma
multiline_comment|/* This is external wavetable */
id|MIX_ENT2
c_func
(paren
id|SOUND_MIXER_LINE1
comma
l_int|22
comma
l_int|0
comma
l_int|4
comma
l_int|4
comma
l_int|23
comma
l_int|1
comma
l_int|1
comma
l_int|23
comma
l_int|0
comma
l_int|4
comma
l_int|22
comma
l_int|0
comma
l_int|0
comma
l_int|4
comma
l_int|23
comma
l_int|1
comma
l_int|0
comma
l_int|23
comma
l_int|0
comma
l_int|5
)paren
comma
)brace
suffix:semicolon
DECL|variable|default_mixer_levels
r_static
r_int
id|default_mixer_levels
(braket
l_int|32
)braket
op_assign
(brace
l_int|0x3232
comma
multiline_comment|/* Master Volume */
l_int|0x3232
comma
multiline_comment|/* Bass */
l_int|0x3232
comma
multiline_comment|/* Treble */
l_int|0x4b4b
comma
multiline_comment|/* FM */
l_int|0x3232
comma
multiline_comment|/* PCM */
l_int|0x1515
comma
multiline_comment|/* PC Speaker */
l_int|0x2020
comma
multiline_comment|/* Ext Line */
l_int|0x1010
comma
multiline_comment|/* Mic */
l_int|0x4b4b
comma
multiline_comment|/* CD */
l_int|0x0000
comma
multiline_comment|/* Recording monitor */
l_int|0x4b4b
comma
multiline_comment|/* Second PCM */
l_int|0x4b4b
comma
multiline_comment|/* Recording level */
l_int|0x4b4b
comma
multiline_comment|/* Input gain */
l_int|0x4b4b
comma
multiline_comment|/* Output gain */
l_int|0x2020
comma
multiline_comment|/* Line1 */
l_int|0x2020
comma
multiline_comment|/* Line2 */
l_int|0x1515
multiline_comment|/* Line3 (usually line in)*/
)brace
suffix:semicolon
DECL|macro|LEFT_CHN
mdefine_line|#define LEFT_CHN&t;0
DECL|macro|RIGHT_CHN
mdefine_line|#define RIGHT_CHN&t;1
multiline_comment|/*&n; * Channel enable bits for ioctl(SOUND_MIXER_PRIVATE1)&n; */
macro_line|#ifndef AUDIO_SPEAKER
DECL|macro|AUDIO_SPEAKER
mdefine_line|#define&t;AUDIO_SPEAKER&t;&t;0x01&t;/* Enable mono output */
DECL|macro|AUDIO_HEADPHONE
mdefine_line|#define&t;AUDIO_HEADPHONE&t;&t;0x02&t;/* Sparc only */
DECL|macro|AUDIO_LINE_OUT
mdefine_line|#define&t;AUDIO_LINE_OUT&t;&t;0x04&t;/* Sparc only */
macro_line|#endif
eof
