multiline_comment|/* $Id: isdn_audio.h,v 1.9.6.1 2001/09/23 22:24:31 kai Exp $&n; *&n; * Linux ISDN subsystem, audio conversion and compression (linklevel).&n; *&n; * Copyright 1994-1999 by Fritz Elfert (fritz@isdn4linux.de)&n; *&n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; */
DECL|macro|DTMF_NPOINTS
mdefine_line|#define DTMF_NPOINTS 205        /* Number of samples for DTMF recognition */
DECL|struct|adpcm_state
r_typedef
r_struct
id|adpcm_state
(brace
DECL|member|a
r_int
id|a
suffix:semicolon
DECL|member|d
r_int
id|d
suffix:semicolon
DECL|member|word
r_int
id|word
suffix:semicolon
DECL|member|nleft
r_int
id|nleft
suffix:semicolon
DECL|member|nbits
r_int
id|nbits
suffix:semicolon
DECL|typedef|adpcm_state
)brace
id|adpcm_state
suffix:semicolon
DECL|struct|dtmf_state
r_typedef
r_struct
id|dtmf_state
(brace
DECL|member|last
r_char
id|last
suffix:semicolon
DECL|member|idx
r_int
id|idx
suffix:semicolon
DECL|member|buf
r_int
id|buf
(braket
id|DTMF_NPOINTS
)braket
suffix:semicolon
DECL|typedef|dtmf_state
)brace
id|dtmf_state
suffix:semicolon
DECL|struct|silence_state
r_typedef
r_struct
id|silence_state
(brace
DECL|member|state
r_int
id|state
suffix:semicolon
DECL|member|idx
r_int
r_int
id|idx
suffix:semicolon
DECL|typedef|silence_state
)brace
id|silence_state
suffix:semicolon
r_extern
r_void
id|isdn_audio_ulaw2alaw
c_func
(paren
r_int
r_char
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|isdn_audio_alaw2ulaw
c_func
(paren
r_int
r_char
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
id|adpcm_state
op_star
id|isdn_audio_adpcm_init
c_func
(paren
id|adpcm_state
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|isdn_audio_adpcm2xlaw
c_func
(paren
id|adpcm_state
op_star
comma
r_int
comma
r_int
r_char
op_star
comma
r_int
r_char
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|isdn_audio_xlaw2adpcm
c_func
(paren
id|adpcm_state
op_star
comma
r_int
comma
r_int
r_char
op_star
comma
r_int
r_char
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|isdn_audio_2adpcm_flush
c_func
(paren
id|adpcm_state
op_star
id|s
comma
r_int
r_char
op_star
id|out
)paren
suffix:semicolon
r_extern
r_void
id|isdn_audio_calc_dtmf
c_func
(paren
id|modem_info
op_star
comma
r_int
r_char
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|isdn_audio_eval_dtmf
c_func
(paren
id|modem_info
op_star
)paren
suffix:semicolon
id|dtmf_state
op_star
id|isdn_audio_dtmf_init
c_func
(paren
id|dtmf_state
op_star
)paren
suffix:semicolon
r_extern
r_void
id|isdn_audio_calc_silence
c_func
(paren
id|modem_info
op_star
comma
r_int
r_char
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|isdn_audio_eval_silence
c_func
(paren
id|modem_info
op_star
)paren
suffix:semicolon
id|silence_state
op_star
id|isdn_audio_silence_init
c_func
(paren
id|silence_state
op_star
)paren
suffix:semicolon
r_extern
r_void
id|isdn_audio_put_dle_code
c_func
(paren
id|modem_info
op_star
comma
id|u_char
)paren
suffix:semicolon
eof