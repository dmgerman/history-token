multiline_comment|/*&n; * Created: 9-Jan-1999 Rolf Fokkens&n; */
r_extern
r_void
id|ess_intr
(paren
id|sb_devc
op_star
id|devc
)paren
suffix:semicolon
r_extern
r_int
id|ess_dsp_init
(paren
id|sb_devc
op_star
id|devc
comma
r_struct
id|address_info
op_star
id|hw_config
)paren
suffix:semicolon
r_extern
r_struct
id|audio_driver
op_star
id|ess_audio_init
(paren
id|sb_devc
op_star
id|devc
comma
r_int
op_star
id|audio_flags
comma
r_int
op_star
id|format_mask
)paren
suffix:semicolon
r_extern
r_int
id|ess_midi_init
(paren
id|sb_devc
op_star
id|devc
comma
r_struct
id|address_info
op_star
id|hw_config
)paren
suffix:semicolon
r_extern
r_void
id|ess_mixer_init
(paren
id|sb_devc
op_star
id|devc
)paren
suffix:semicolon
r_extern
r_int
id|ess_init
(paren
id|sb_devc
op_star
id|devc
comma
r_struct
id|address_info
op_star
id|hw_config
)paren
suffix:semicolon
r_extern
r_int
id|ess_dsp_reset
(paren
id|sb_devc
op_star
id|devc
)paren
suffix:semicolon
r_extern
r_void
id|ess_setmixer
(paren
id|sb_devc
op_star
id|devc
comma
r_int
r_int
id|port
comma
r_int
r_int
id|value
)paren
suffix:semicolon
r_extern
r_int
r_int
id|ess_getmixer
(paren
id|sb_devc
op_star
id|devc
comma
r_int
r_int
id|port
)paren
suffix:semicolon
r_extern
r_int
id|ess_mixer_set
(paren
id|sb_devc
op_star
id|devc
comma
r_int
id|dev
comma
r_int
id|left
comma
r_int
id|right
)paren
suffix:semicolon
r_extern
r_int
id|ess_mixer_reset
(paren
id|sb_devc
op_star
id|devc
)paren
suffix:semicolon
r_extern
r_void
id|ess_mixer_reload
(paren
id|sb_devc
op_star
id|devc
comma
r_int
id|dev
)paren
suffix:semicolon
r_extern
r_int
id|ess_set_recmask
(paren
id|sb_devc
op_star
id|devc
comma
r_int
op_star
id|mask
)paren
suffix:semicolon
eof