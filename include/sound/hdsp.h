macro_line|#ifndef __SOUND_HDSP_H
DECL|macro|__SOUND_HDSP_H
mdefine_line|#define __SOUND_HDSP_H
multiline_comment|/*&n; *   Copyright (C) 2003 Thomas Charbonnel (thomas@undata.org)&n; *    &n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
DECL|macro|HDSP_MATRIX_MIXER_SIZE
mdefine_line|#define HDSP_MATRIX_MIXER_SIZE 2048
r_typedef
r_enum
(brace
DECL|enumerator|Digiface
id|Digiface
comma
DECL|enumerator|Multiface
id|Multiface
comma
DECL|enumerator|H9652
id|H9652
comma
DECL|enumerator|Undefined
id|Undefined
comma
DECL|typedef|HDSP_IO_Type
)brace
id|HDSP_IO_Type
suffix:semicolon
DECL|typedef|hdsp_peak_rms_t
r_typedef
r_struct
id|_snd_hdsp_peak_rms
id|hdsp_peak_rms_t
suffix:semicolon
DECL|struct|_snd_hdsp_peak_rms
r_struct
id|_snd_hdsp_peak_rms
(brace
DECL|member|playback_peaks
r_int
r_int
id|playback_peaks
(braket
l_int|26
)braket
suffix:semicolon
DECL|member|input_peaks
r_int
r_int
id|input_peaks
(braket
l_int|26
)braket
suffix:semicolon
DECL|member|output_peaks
r_int
r_int
id|output_peaks
(braket
l_int|28
)braket
suffix:semicolon
DECL|member|playback_rms
r_int
r_int
r_int
id|playback_rms
(braket
l_int|26
)braket
suffix:semicolon
DECL|member|input_rms
r_int
r_int
r_int
id|input_rms
(braket
l_int|26
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|SNDRV_HDSP_IOCTL_GET_PEAK_RMS
mdefine_line|#define SNDRV_HDSP_IOCTL_GET_PEAK_RMS _IOR(&squot;H&squot;, 0x40, hdsp_peak_rms_t)
DECL|typedef|hdsp_config_info_t
r_typedef
r_struct
id|_snd_hdsp_config_info
id|hdsp_config_info_t
suffix:semicolon
DECL|struct|_snd_hdsp_config_info
r_struct
id|_snd_hdsp_config_info
(brace
DECL|member|pref_sync_ref
r_int
r_char
id|pref_sync_ref
suffix:semicolon
DECL|member|wordclock_sync_check
r_int
r_char
id|wordclock_sync_check
suffix:semicolon
DECL|member|spdif_sync_check
r_int
r_char
id|spdif_sync_check
suffix:semicolon
DECL|member|adatsync_sync_check
r_int
r_char
id|adatsync_sync_check
suffix:semicolon
DECL|member|adat_sync_check
r_int
r_char
id|adat_sync_check
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|spdif_in
r_int
r_char
id|spdif_in
suffix:semicolon
DECL|member|spdif_out
r_int
r_char
id|spdif_out
suffix:semicolon
DECL|member|spdif_professional
r_int
r_char
id|spdif_professional
suffix:semicolon
DECL|member|spdif_emphasis
r_int
r_char
id|spdif_emphasis
suffix:semicolon
DECL|member|spdif_nonaudio
r_int
r_char
id|spdif_nonaudio
suffix:semicolon
DECL|member|spdif_sample_rate
r_int
r_int
id|spdif_sample_rate
suffix:semicolon
DECL|member|system_sample_rate
r_int
r_int
id|system_sample_rate
suffix:semicolon
DECL|member|autosync_sample_rate
r_int
r_int
id|autosync_sample_rate
suffix:semicolon
DECL|member|system_clock_mode
r_int
r_char
id|system_clock_mode
suffix:semicolon
DECL|member|clock_source
r_int
r_char
id|clock_source
suffix:semicolon
DECL|member|autosync_ref
r_int
r_char
id|autosync_ref
suffix:semicolon
DECL|member|line_out
r_int
r_char
id|line_out
suffix:semicolon
DECL|member|passthru
r_int
r_char
id|passthru
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|SNDRV_HDSP_IOCTL_GET_CONFIG_INFO
mdefine_line|#define SNDRV_HDSP_IOCTL_GET_CONFIG_INFO _IOR(&squot;H&squot;, 0x41, hdsp_config_info_t)
DECL|typedef|hdsp_firmware_t
r_typedef
r_struct
id|_snd_hdsp_firmware
id|hdsp_firmware_t
suffix:semicolon
DECL|struct|_snd_hdsp_firmware
r_struct
id|_snd_hdsp_firmware
(brace
DECL|member|firmware_data
r_int
r_int
op_star
id|firmware_data
suffix:semicolon
multiline_comment|/* 24413 long words */
)brace
suffix:semicolon
DECL|macro|SNDRV_HDSP_IOCTL_UPLOAD_FIRMWARE
mdefine_line|#define SNDRV_HDSP_IOCTL_UPLOAD_FIRMWARE _IOW(&squot;H&squot;, 0x42, hdsp_firmware_t)
DECL|typedef|hdsp_version_t
r_typedef
r_struct
id|_snd_hdsp_version
id|hdsp_version_t
suffix:semicolon
DECL|struct|_snd_hdsp_version
r_struct
id|_snd_hdsp_version
(brace
DECL|member|io_type
id|HDSP_IO_Type
id|io_type
suffix:semicolon
DECL|member|firmware_rev
r_int
r_int
id|firmware_rev
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|SNDRV_HDSP_IOCTL_GET_VERSION
mdefine_line|#define SNDRV_HDSP_IOCTL_GET_VERSION _IOR(&squot;H&squot;, 0x43, hdsp_version_t)
DECL|typedef|hdsp_mixer_t
r_typedef
r_struct
id|_snd_hdsp_mixer
id|hdsp_mixer_t
suffix:semicolon
DECL|struct|_snd_hdsp_mixer
r_struct
id|_snd_hdsp_mixer
(brace
DECL|member|matrix
r_int
r_int
id|matrix
(braket
id|HDSP_MATRIX_MIXER_SIZE
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|SNDRV_HDSP_IOCTL_GET_MIXER
mdefine_line|#define SNDRV_HDSP_IOCTL_GET_MIXER _IOR(&squot;H&squot;, 0x44, hdsp_mixer_t)
macro_line|#endif /* __SOUND_HDSP_H */
eof
