multiline_comment|/*&n; * The Linux soundcard driver for 1200 baud and 9600 baud packet radio&n; * (C) 1996-1998 by Thomas Sailer, HB9JNX/AE4WA&n; */
macro_line|#ifndef _SOUNDMODEM_H
DECL|macro|_SOUNDMODEM_H
mdefine_line|#define _SOUNDMODEM_H
multiline_comment|/* -------------------------------------------------------------------- */
multiline_comment|/*&n; * structs for the IOCTL commands&n; */
DECL|struct|sm_debug_data
r_struct
id|sm_debug_data
(brace
DECL|member|int_rate
r_int
r_int
id|int_rate
suffix:semicolon
DECL|member|mod_cycles
r_int
r_int
id|mod_cycles
suffix:semicolon
DECL|member|demod_cycles
r_int
r_int
id|demod_cycles
suffix:semicolon
DECL|member|dma_residue
r_int
r_int
id|dma_residue
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|sm_diag_data
r_struct
id|sm_diag_data
(brace
DECL|member|mode
r_int
r_int
id|mode
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|samplesperbit
r_int
r_int
id|samplesperbit
suffix:semicolon
DECL|member|datalen
r_int
r_int
id|datalen
suffix:semicolon
DECL|member|data
r_int
op_star
id|data
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|sm_mixer_data
r_struct
id|sm_mixer_data
(brace
DECL|member|mixer_type
r_int
r_int
id|mixer_type
suffix:semicolon
DECL|member|sample_rate
r_int
r_int
id|sample_rate
suffix:semicolon
DECL|member|bit_rate
r_int
r_int
id|bit_rate
suffix:semicolon
DECL|member|reg
r_int
r_int
id|reg
suffix:semicolon
DECL|member|data
r_int
r_int
id|data
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|sm_config
r_struct
id|sm_config
(brace
DECL|member|hardware
r_int
id|hardware
suffix:semicolon
DECL|member|mode
r_int
id|mode
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|sm_ioctl
r_struct
id|sm_ioctl
(brace
DECL|member|cmd
r_int
id|cmd
suffix:semicolon
r_union
(brace
DECL|member|cfg
r_struct
id|sm_config
id|cfg
suffix:semicolon
DECL|member|diag
r_struct
id|sm_diag_data
id|diag
suffix:semicolon
DECL|member|mix
r_struct
id|sm_mixer_data
id|mix
suffix:semicolon
DECL|member|dbg
r_struct
id|sm_debug_data
id|dbg
suffix:semicolon
DECL|member|data
)brace
id|data
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* -------------------------------------------------------------------- */
multiline_comment|/*&n; * diagnose modes&n; */
DECL|macro|SM_DIAGMODE_OFF
mdefine_line|#define SM_DIAGMODE_OFF            0
DECL|macro|SM_DIAGMODE_INPUT
mdefine_line|#define SM_DIAGMODE_INPUT          1
DECL|macro|SM_DIAGMODE_DEMOD
mdefine_line|#define SM_DIAGMODE_DEMOD          2
DECL|macro|SM_DIAGMODE_CONSTELLATION
mdefine_line|#define SM_DIAGMODE_CONSTELLATION  3
multiline_comment|/*&n; * diagnose flags&n; */
DECL|macro|SM_DIAGFLAG_DCDGATE
mdefine_line|#define SM_DIAGFLAG_DCDGATE    (1&lt;&lt;0)
DECL|macro|SM_DIAGFLAG_VALID
mdefine_line|#define SM_DIAGFLAG_VALID      (1&lt;&lt;1)
multiline_comment|/*&n; * mixer types&n; */
DECL|macro|SM_MIXER_INVALID
mdefine_line|#define SM_MIXER_INVALID       0
DECL|macro|SM_MIXER_AD1848
mdefine_line|#define SM_MIXER_AD1848        0x10
DECL|macro|SM_MIXER_CRYSTAL
mdefine_line|#define SM_MIXER_CRYSTAL       0x11
DECL|macro|SM_MIXER_CT1335
mdefine_line|#define SM_MIXER_CT1335        0x20
DECL|macro|SM_MIXER_CT1345
mdefine_line|#define SM_MIXER_CT1345        0x21
DECL|macro|SM_MIXER_CT1745
mdefine_line|#define SM_MIXER_CT1745        0x22
multiline_comment|/*&n; * ioctl values&n; */
DECL|macro|SMCTL_DIAGNOSE
mdefine_line|#define SMCTL_DIAGNOSE         0x82
DECL|macro|SMCTL_GETMIXER
mdefine_line|#define SMCTL_GETMIXER         0x83
DECL|macro|SMCTL_SETMIXER
mdefine_line|#define SMCTL_SETMIXER         0x84
DECL|macro|SMCTL_GETDEBUG
mdefine_line|#define SMCTL_GETDEBUG         0x85
multiline_comment|/* -------------------------------------------------------------------- */
macro_line|#endif /* _SOUNDMODEM_H */
multiline_comment|/* --------------------------------------------------------------------- */
eof
