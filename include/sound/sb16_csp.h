macro_line|#ifndef __SOUND_SB16_CSP_H
DECL|macro|__SOUND_SB16_CSP_H
mdefine_line|#define __SOUND_SB16_CSP_H
multiline_comment|/*&n; *  Copyright (c) 1999 by Uros Bizjak &lt;uros@kss-loka.si&gt;&n; *                        Takashi Iwai &lt;tiwai@suse.de&gt;&n; *&n; *  SB16ASP/AWE32 CSP control&n; *&n; *   This program is free software; you can redistribute it and/or modify &n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
multiline_comment|/* CSP modes */
DECL|macro|SNDRV_SB_CSP_MODE_NONE
mdefine_line|#define SNDRV_SB_CSP_MODE_NONE&t;&t;0x00
DECL|macro|SNDRV_SB_CSP_MODE_DSP_READ
mdefine_line|#define SNDRV_SB_CSP_MODE_DSP_READ&t;0x01&t;/* Record from DSP */
DECL|macro|SNDRV_SB_CSP_MODE_DSP_WRITE
mdefine_line|#define SNDRV_SB_CSP_MODE_DSP_WRITE&t;0x02&t;/* Play to DSP */
DECL|macro|SNDRV_SB_CSP_MODE_QSOUND
mdefine_line|#define SNDRV_SB_CSP_MODE_QSOUND&t;&t;0x04&t;/* QSound */
multiline_comment|/* CSP load flags */
DECL|macro|SNDRV_SB_CSP_LOAD_FROMUSER
mdefine_line|#define SNDRV_SB_CSP_LOAD_FROMUSER&t;0x01
DECL|macro|SNDRV_SB_CSP_LOAD_INITBLOCK
mdefine_line|#define SNDRV_SB_CSP_LOAD_INITBLOCK&t;0x02
multiline_comment|/* CSP sample width */
DECL|macro|SNDRV_SB_CSP_SAMPLE_8BIT
mdefine_line|#define SNDRV_SB_CSP_SAMPLE_8BIT&t;&t;0x01
DECL|macro|SNDRV_SB_CSP_SAMPLE_16BIT
mdefine_line|#define SNDRV_SB_CSP_SAMPLE_16BIT&t;&t;0x02
multiline_comment|/* CSP channels */
DECL|macro|SNDRV_SB_CSP_MONO
mdefine_line|#define SNDRV_SB_CSP_MONO&t;&t;&t;0x01
DECL|macro|SNDRV_SB_CSP_STEREO
mdefine_line|#define SNDRV_SB_CSP_STEREO&t;&t;0x02
multiline_comment|/* CSP rates */
DECL|macro|SNDRV_SB_CSP_RATE_8000
mdefine_line|#define SNDRV_SB_CSP_RATE_8000&t;&t;0x01
DECL|macro|SNDRV_SB_CSP_RATE_11025
mdefine_line|#define SNDRV_SB_CSP_RATE_11025&t;&t;0x02
DECL|macro|SNDRV_SB_CSP_RATE_22050
mdefine_line|#define SNDRV_SB_CSP_RATE_22050&t;&t;0x04
DECL|macro|SNDRV_SB_CSP_RATE_44100
mdefine_line|#define SNDRV_SB_CSP_RATE_44100&t;&t;0x08
DECL|macro|SNDRV_SB_CSP_RATE_ALL
mdefine_line|#define SNDRV_SB_CSP_RATE_ALL&t;&t;0x0f
multiline_comment|/* CSP running state */
DECL|macro|SNDRV_SB_CSP_ST_IDLE
mdefine_line|#define SNDRV_SB_CSP_ST_IDLE&t;&t;0x00
DECL|macro|SNDRV_SB_CSP_ST_LOADED
mdefine_line|#define SNDRV_SB_CSP_ST_LOADED&t;&t;0x01
DECL|macro|SNDRV_SB_CSP_ST_RUNNING
mdefine_line|#define SNDRV_SB_CSP_ST_RUNNING&t;&t;0x02
DECL|macro|SNDRV_SB_CSP_ST_PAUSED
mdefine_line|#define SNDRV_SB_CSP_ST_PAUSED&t;&t;0x04
DECL|macro|SNDRV_SB_CSP_ST_AUTO
mdefine_line|#define SNDRV_SB_CSP_ST_AUTO&t;&t;0x08
DECL|macro|SNDRV_SB_CSP_ST_QSOUND
mdefine_line|#define SNDRV_SB_CSP_ST_QSOUND&t;&t;0x10
multiline_comment|/* maximum QSound value (180 degrees right) */
DECL|macro|SNDRV_SB_CSP_QSOUND_MAX_RIGHT
mdefine_line|#define SNDRV_SB_CSP_QSOUND_MAX_RIGHT&t;0x20
multiline_comment|/* maximum microcode RIFF file size */
DECL|macro|SNDRV_SB_CSP_MAX_MICROCODE_FILE_SIZE
mdefine_line|#define SNDRV_SB_CSP_MAX_MICROCODE_FILE_SIZE&t;0x3000
multiline_comment|/* microcode header */
DECL|struct|snd_sb_csp_mc_header
r_typedef
r_struct
id|snd_sb_csp_mc_header
(brace
DECL|member|codec_name
r_char
id|codec_name
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* id name of codec */
DECL|member|func_req
r_int
r_int
id|func_req
suffix:semicolon
multiline_comment|/* requested function */
DECL|typedef|snd_sb_csp_mc_header_t
)brace
id|snd_sb_csp_mc_header_t
suffix:semicolon
multiline_comment|/* microcode to be loaded */
DECL|struct|snd_sb_csp_microcode
r_typedef
r_struct
id|snd_sb_csp_microcode
(brace
DECL|member|info
id|snd_sb_csp_mc_header_t
id|info
suffix:semicolon
DECL|member|data
r_int
r_char
id|data
(braket
id|SNDRV_SB_CSP_MAX_MICROCODE_FILE_SIZE
)braket
suffix:semicolon
DECL|typedef|snd_sb_csp_microcode_t
)brace
id|snd_sb_csp_microcode_t
suffix:semicolon
multiline_comment|/* start CSP with sample_width in mono/stereo */
DECL|struct|snd_sb_csp_start
r_typedef
r_struct
id|snd_sb_csp_start
(brace
DECL|member|sample_width
r_int
id|sample_width
suffix:semicolon
multiline_comment|/* sample width, look above */
DECL|member|channels
r_int
id|channels
suffix:semicolon
multiline_comment|/* channels, look above */
DECL|typedef|snd_sb_csp_start_t
)brace
id|snd_sb_csp_start_t
suffix:semicolon
multiline_comment|/* CSP information */
DECL|struct|snd_sb_csp_info
r_typedef
r_struct
id|snd_sb_csp_info
(brace
DECL|member|codec_name
r_char
id|codec_name
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* id name of codec */
DECL|member|func_nr
r_int
r_int
id|func_nr
suffix:semicolon
multiline_comment|/* function number */
DECL|member|acc_format
r_int
r_int
id|acc_format
suffix:semicolon
multiline_comment|/* accepted PCM formats */
DECL|member|acc_channels
r_int
r_int
id|acc_channels
suffix:semicolon
multiline_comment|/* accepted channels */
DECL|member|acc_width
r_int
r_int
id|acc_width
suffix:semicolon
multiline_comment|/* accepted sample width */
DECL|member|acc_rates
r_int
r_int
id|acc_rates
suffix:semicolon
multiline_comment|/* accepted sample rates */
DECL|member|csp_mode
r_int
r_int
id|csp_mode
suffix:semicolon
multiline_comment|/* CSP mode, see above */
DECL|member|run_channels
r_int
r_int
id|run_channels
suffix:semicolon
multiline_comment|/* current channels  */
DECL|member|run_width
r_int
r_int
id|run_width
suffix:semicolon
multiline_comment|/* current sample width */
DECL|member|version
r_int
r_int
id|version
suffix:semicolon
multiline_comment|/* version id: 0x10 - 0x1f */
DECL|member|state
r_int
r_int
id|state
suffix:semicolon
multiline_comment|/* state bits */
DECL|typedef|snd_sb_csp_info_t
)brace
id|snd_sb_csp_info_t
suffix:semicolon
multiline_comment|/* HWDEP controls */
multiline_comment|/* get CSP information */
DECL|macro|SNDRV_SB_CSP_IOCTL_INFO
mdefine_line|#define SNDRV_SB_CSP_IOCTL_INFO&t;&t;_IOR(&squot;H&squot;, 0x10, snd_sb_csp_info_t)
multiline_comment|/* load microcode to CSP */
DECL|macro|SNDRV_SB_CSP_IOCTL_LOAD_CODE
mdefine_line|#define SNDRV_SB_CSP_IOCTL_LOAD_CODE&t;_IOW(&squot;H&squot;, 0x11, snd_sb_csp_microcode_t)
multiline_comment|/* unload microcode from CSP */
DECL|macro|SNDRV_SB_CSP_IOCTL_UNLOAD_CODE
mdefine_line|#define SNDRV_SB_CSP_IOCTL_UNLOAD_CODE&t;_IO(&squot;H&squot;, 0x12)
multiline_comment|/* start CSP */
DECL|macro|SNDRV_SB_CSP_IOCTL_START
mdefine_line|#define SNDRV_SB_CSP_IOCTL_START&t;&t;_IOW(&squot;H&squot;, 0x13, snd_sb_csp_start_t)
multiline_comment|/* stop CSP */
DECL|macro|SNDRV_SB_CSP_IOCTL_STOP
mdefine_line|#define SNDRV_SB_CSP_IOCTL_STOP&t;&t;_IO(&squot;H&squot;, 0x14)
multiline_comment|/* pause CSP and DMA transfer */
DECL|macro|SNDRV_SB_CSP_IOCTL_PAUSE
mdefine_line|#define SNDRV_SB_CSP_IOCTL_PAUSE&t;&t;_IO(&squot;H&squot;, 0x15)
multiline_comment|/* restart CSP and DMA transfer */
DECL|macro|SNDRV_SB_CSP_IOCTL_RESTART
mdefine_line|#define SNDRV_SB_CSP_IOCTL_RESTART&t;_IO(&squot;H&squot;, 0x16)
macro_line|#ifdef __KERNEL__
macro_line|#include &quot;sb.h&quot;
macro_line|#include &quot;hwdep.h&quot;
DECL|typedef|snd_sb_csp_t
r_typedef
r_struct
id|snd_sb_csp
id|snd_sb_csp_t
suffix:semicolon
multiline_comment|/*&n; * CSP operators&n; */
r_typedef
r_struct
(brace
DECL|member|csp_use
r_int
(paren
op_star
id|csp_use
)paren
(paren
id|snd_sb_csp_t
op_star
id|p
)paren
suffix:semicolon
DECL|member|csp_unuse
r_int
(paren
op_star
id|csp_unuse
)paren
(paren
id|snd_sb_csp_t
op_star
id|p
)paren
suffix:semicolon
DECL|member|csp_autoload
r_int
(paren
op_star
id|csp_autoload
)paren
(paren
id|snd_sb_csp_t
op_star
id|p
comma
r_int
id|pcm_sfmt
comma
r_int
id|play_rec_mode
)paren
suffix:semicolon
DECL|member|csp_start
r_int
(paren
op_star
id|csp_start
)paren
(paren
id|snd_sb_csp_t
op_star
id|p
comma
r_int
id|sample_width
comma
r_int
id|channels
)paren
suffix:semicolon
DECL|member|csp_stop
r_int
(paren
op_star
id|csp_stop
)paren
(paren
id|snd_sb_csp_t
op_star
id|p
)paren
suffix:semicolon
DECL|member|csp_qsound_transfer
r_int
(paren
op_star
id|csp_qsound_transfer
)paren
(paren
id|snd_sb_csp_t
op_star
id|p
)paren
suffix:semicolon
DECL|typedef|snd_sb_csp_ops_t
)brace
id|snd_sb_csp_ops_t
suffix:semicolon
multiline_comment|/*&n; * CSP private data&n; */
DECL|struct|snd_sb_csp
r_struct
id|snd_sb_csp
(brace
DECL|member|chip
id|sb_t
op_star
id|chip
suffix:semicolon
multiline_comment|/* SB16 DSP */
DECL|member|used
r_int
id|used
suffix:semicolon
multiline_comment|/* usage flag - exclusive */
DECL|member|codec_name
r_char
id|codec_name
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* name of codec */
DECL|member|func_nr
r_int
r_int
id|func_nr
suffix:semicolon
multiline_comment|/* function number */
DECL|member|acc_format
r_int
r_int
id|acc_format
suffix:semicolon
multiline_comment|/* accepted PCM formats */
DECL|member|acc_channels
r_int
id|acc_channels
suffix:semicolon
multiline_comment|/* accepted channels */
DECL|member|acc_width
r_int
id|acc_width
suffix:semicolon
multiline_comment|/* accepted sample width */
DECL|member|acc_rates
r_int
id|acc_rates
suffix:semicolon
multiline_comment|/* accepted sample rates */
DECL|member|mode
r_int
id|mode
suffix:semicolon
multiline_comment|/* MODE */
DECL|member|run_channels
r_int
id|run_channels
suffix:semicolon
multiline_comment|/* current CSP channels */
DECL|member|run_width
r_int
id|run_width
suffix:semicolon
multiline_comment|/* current sample width */
DECL|member|version
r_int
id|version
suffix:semicolon
multiline_comment|/* CSP version (0x10 - 0x1f) */
DECL|member|running
r_int
id|running
suffix:semicolon
multiline_comment|/* running state */
DECL|member|ops
id|snd_sb_csp_ops_t
id|ops
suffix:semicolon
multiline_comment|/* operators */
DECL|member|q_lock
id|spinlock_t
id|q_lock
suffix:semicolon
multiline_comment|/* locking */
DECL|member|q_enabled
r_int
id|q_enabled
suffix:semicolon
multiline_comment|/* enabled flag */
DECL|member|qpos_left
r_int
id|qpos_left
suffix:semicolon
multiline_comment|/* left position */
DECL|member|qpos_right
r_int
id|qpos_right
suffix:semicolon
multiline_comment|/* right position */
DECL|member|qpos_changed
r_int
id|qpos_changed
suffix:semicolon
multiline_comment|/* position changed flag */
DECL|member|qsound_switch
id|snd_kcontrol_t
op_star
id|qsound_switch
suffix:semicolon
DECL|member|qsound_space
id|snd_kcontrol_t
op_star
id|qsound_space
suffix:semicolon
DECL|member|access_mutex
r_struct
id|semaphore
id|access_mutex
suffix:semicolon
multiline_comment|/* locking */
DECL|member|proc
id|snd_info_entry_t
op_star
id|proc
suffix:semicolon
multiline_comment|/* proc interface */
)brace
suffix:semicolon
r_int
id|snd_sb_csp_new
c_func
(paren
id|sb_t
op_star
id|chip
comma
r_int
id|device
comma
id|snd_hwdep_t
op_star
op_star
id|rhwdep
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif /* __SOUND_SB16_CSP */
eof
