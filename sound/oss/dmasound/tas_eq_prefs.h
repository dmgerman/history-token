macro_line|#ifndef _TAS_EQ_PREFS_H_
DECL|macro|_TAS_EQ_PREFS_H_
mdefine_line|#define _TAS_EQ_PREFS_H_
DECL|struct|tas_eq_pref_t
r_struct
id|tas_eq_pref_t
(brace
DECL|member|sample_rate
id|u_int
id|sample_rate
suffix:semicolon
DECL|member|device_id
id|u_int
id|device_id
suffix:semicolon
DECL|member|output_id
id|u_int
id|output_id
suffix:semicolon
DECL|member|speaker_id
id|u_int
id|speaker_id
suffix:semicolon
DECL|member|drce
r_struct
id|tas_drce_t
op_star
id|drce
suffix:semicolon
DECL|member|filter_count
id|u_int
id|filter_count
suffix:semicolon
DECL|member|biquads
r_struct
id|tas_biquad_ctrl_t
op_star
id|biquads
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* _TAS_EQ_PREFS_H_ */
multiline_comment|/*&n; * Local Variables:&n; * tab-width: 8&n; * indent-tabs-mode: t&n; * c-basic-offset: 8&n; * End:&n; */
eof
