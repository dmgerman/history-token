multiline_comment|/*&n;    saa6752hs.h - definition for saa6752hs MPEG encoder&n;&n;    Copyright (C) 2003 Andrew de Quincey &lt;adq@lidskialf.net&gt;&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;*/
macro_line|#if 0 /* ndef _SAA6752HS_H */
mdefine_line|#define _SAA6752HS_H
r_enum
id|mpeg_video_bitrate_mode
(brace
id|MPEG_VIDEO_BITRATE_MODE_VBR
op_assign
l_int|0
comma
multiline_comment|/* Variable bitrate */
id|MPEG_VIDEO_BITRATE_MODE_CBR
op_assign
l_int|1
comma
multiline_comment|/* Constant bitrate */
id|MPEG_VIDEO_BITRATE_MODE_MAX
)brace
suffix:semicolon
r_enum
id|mpeg_audio_bitrate
(brace
id|MPEG_AUDIO_BITRATE_256
op_assign
l_int|0
comma
multiline_comment|/* 256 kBit/sec */
id|MPEG_AUDIO_BITRATE_384
op_assign
l_int|1
comma
multiline_comment|/* 384 kBit/sec */
id|MPEG_AUDIO_BITRATE_MAX
)brace
suffix:semicolon
r_enum
id|mpeg_video_format
(brace
id|MPEG_VIDEO_FORMAT_D1
op_assign
l_int|0
comma
id|MPEG_VIDEO_FORMAT_2_3_D1
op_assign
l_int|1
comma
id|MPEG_VIDEO_FORMAT_1_2_D1
op_assign
l_int|2
comma
id|MPEG_VIDEO_FORMAT_SIF
op_assign
l_int|3
comma
id|MPEG_VIDEO_FORMAT_MAX
)brace
suffix:semicolon
mdefine_line|#define MPEG_VIDEO_TARGET_BITRATE_MAX 27000
mdefine_line|#define MPEG_VIDEO_MAX_BITRATE_MAX 27000
mdefine_line|#define MPEG_TOTAL_BITRATE_MAX 27000
mdefine_line|#define MPEG_PID_MAX ((1 &lt;&lt; 14) - 1)
r_struct
id|mpeg_params
(brace
r_enum
id|mpeg_video_bitrate_mode
id|video_bitrate_mode
suffix:semicolon
r_int
r_int
id|video_target_bitrate
suffix:semicolon
r_int
r_int
id|video_max_bitrate
suffix:semicolon
singleline_comment|// only used for VBR
r_enum
id|mpeg_audio_bitrate
id|audio_bitrate
suffix:semicolon
r_int
r_int
id|total_bitrate
suffix:semicolon
r_int
r_int
id|pmt_pid
suffix:semicolon
r_int
r_int
id|video_pid
suffix:semicolon
r_int
r_int
id|audio_pid
suffix:semicolon
r_int
r_int
id|pcr_pid
suffix:semicolon
r_enum
id|mpeg_video_format
id|video_format
suffix:semicolon
)brace
suffix:semicolon
mdefine_line|#define MPEG_SETPARAMS             _IOW(&squot;6&squot;,100,struct mpeg_params)
macro_line|#endif 
singleline_comment|// _SAA6752HS_H
multiline_comment|/*&n; * Local variables:&n; * c-basic-offset: 8&n; * End:&n; */
eof
