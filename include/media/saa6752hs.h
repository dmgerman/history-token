multiline_comment|/*&n;    saa6752hs.h - definition for saa6752hs MPEG encoder&n;&n;    Copyright (C) 2003 Andrew de Quincey &lt;adq@lidskialf.net&gt;&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;*/
macro_line|#ifndef _SAA6752HS_H
DECL|macro|_SAA6752HS_H
mdefine_line|#define _SAA6752HS_H
DECL|enum|mpeg_bitrate_mode
r_enum
id|mpeg_bitrate_mode
(brace
DECL|enumerator|MPEG_BITRATE_MODE_VBR
id|MPEG_BITRATE_MODE_VBR
op_assign
l_int|0
comma
multiline_comment|/* Variable bitrate */
DECL|enumerator|MPEG_BITRATE_MODE_CBR
id|MPEG_BITRATE_MODE_CBR
op_assign
l_int|1
comma
multiline_comment|/* Constant bitrate */
DECL|enumerator|MPEG_BITRATE_MODE_MAX
id|MPEG_BITRATE_MODE_MAX
)brace
suffix:semicolon
DECL|enum|mpeg_audio_bitrate
r_enum
id|mpeg_audio_bitrate
(brace
DECL|enumerator|MPEG_AUDIO_BITRATE_256
id|MPEG_AUDIO_BITRATE_256
op_assign
l_int|0
comma
multiline_comment|/* 256 kBit/sec */
DECL|enumerator|MPEG_AUDIO_BITRATE_384
id|MPEG_AUDIO_BITRATE_384
op_assign
l_int|1
comma
multiline_comment|/* 384 kBit/sec */
DECL|enumerator|MPEG_AUDIO_BITRATE_MAX
id|MPEG_AUDIO_BITRATE_MAX
)brace
suffix:semicolon
DECL|macro|MPEG_VIDEO_TARGET_BITRATE_MAX
mdefine_line|#define MPEG_VIDEO_TARGET_BITRATE_MAX 27000
DECL|macro|MPEG_VIDEO_MAX_BITRATE_MAX
mdefine_line|#define MPEG_VIDEO_MAX_BITRATE_MAX 27000
DECL|macro|MPEG_TOTAL_BITRATE_MAX
mdefine_line|#define MPEG_TOTAL_BITRATE_MAX 27000
DECL|struct|mpeg_params
r_struct
id|mpeg_params
(brace
DECL|member|bitrate_mode
r_enum
id|mpeg_bitrate_mode
id|bitrate_mode
suffix:semicolon
DECL|member|video_target_bitrate
r_int
r_int
id|video_target_bitrate
suffix:semicolon
DECL|member|video_max_bitrate
r_int
r_int
id|video_max_bitrate
suffix:semicolon
singleline_comment|// only used for VBR
DECL|member|audio_bitrate
r_enum
id|mpeg_audio_bitrate
id|audio_bitrate
suffix:semicolon
DECL|member|total_bitrate
r_int
r_int
id|total_bitrate
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|MPEG_SETPARAMS
mdefine_line|#define MPEG_SETPARAMS             _IOW(&squot;6&squot;,100,struct mpeg_params)
macro_line|#endif 
singleline_comment|// _SAA6752HS_H
multiline_comment|/*&n; * Local variables:&n; * c-basic-offset: 8&n; * End:&n; */
eof
