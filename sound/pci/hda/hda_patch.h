multiline_comment|/*&n; * HDA Patches - included by hda_codec.c&n; */
multiline_comment|/* Realtek codecs */
r_extern
r_struct
id|hda_codec_preset
id|snd_hda_preset_realtek
(braket
)braket
suffix:semicolon
multiline_comment|/* C-Media codecs */
r_extern
r_struct
id|hda_codec_preset
id|snd_hda_preset_cmedia
(braket
)braket
suffix:semicolon
DECL|variable|hda_preset_tables
r_static
r_const
r_struct
id|hda_codec_preset
op_star
id|hda_preset_tables
(braket
)braket
op_assign
(brace
id|snd_hda_preset_realtek
comma
id|snd_hda_preset_cmedia
comma
l_int|NULL
)brace
suffix:semicolon
eof
