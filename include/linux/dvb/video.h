multiline_comment|/* &n; * video.h&n; *&n; * Copyright (C) 2000 Marcus Metzler &lt;marcus@convergence.de&gt;&n; *                  &amp; Ralph  Metzler &lt;ralph@convergence.de&gt;&n;                      for convergence integrated media GmbH&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU Lesser General Public License&n; * as published by the Free Software Foundation; either version 2.1&n; * of the License, or (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU Lesser General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.&n; *&n; */
macro_line|#ifndef _DVBVIDEO_H_
DECL|macro|_DVBVIDEO_H_
mdefine_line|#define _DVBVIDEO_H_
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/types.h&gt;
macro_line|#else
macro_line|#include &lt;stdint.h&gt;
macro_line|#include &lt;time.h&gt;
macro_line|#endif
r_typedef
r_enum
(brace
DECL|enumerator|VIDEO_FORMAT_4_3
id|VIDEO_FORMAT_4_3
comma
multiline_comment|/* Select 4:3 format */
DECL|enumerator|VIDEO_FORMAT_16_9
id|VIDEO_FORMAT_16_9
comma
multiline_comment|/* Select 16:9 format. */
DECL|enumerator|VIDEO_FORMAT_221_1
id|VIDEO_FORMAT_221_1
multiline_comment|/* 2.21:1 */
DECL|typedef|video_format_t
)brace
id|video_format_t
suffix:semicolon
r_typedef
r_enum
(brace
DECL|enumerator|VIDEO_SYSTEM_PAL
id|VIDEO_SYSTEM_PAL
comma
DECL|enumerator|VIDEO_SYSTEM_NTSC
id|VIDEO_SYSTEM_NTSC
comma
DECL|enumerator|VIDEO_SYSTEM_PALN
id|VIDEO_SYSTEM_PALN
comma
DECL|enumerator|VIDEO_SYSTEM_PALNc
id|VIDEO_SYSTEM_PALNc
comma
DECL|enumerator|VIDEO_SYSTEM_PALM
id|VIDEO_SYSTEM_PALM
comma
DECL|enumerator|VIDEO_SYSTEM_NTSC60
id|VIDEO_SYSTEM_NTSC60
comma
DECL|enumerator|VIDEO_SYSTEM_PAL60
id|VIDEO_SYSTEM_PAL60
comma
DECL|enumerator|VIDEO_SYSTEM_PALM60
id|VIDEO_SYSTEM_PALM60
DECL|typedef|video_system_t
)brace
id|video_system_t
suffix:semicolon
r_typedef
r_enum
(brace
DECL|enumerator|VIDEO_PAN_SCAN
id|VIDEO_PAN_SCAN
comma
multiline_comment|/* use pan and scan format */
DECL|enumerator|VIDEO_LETTER_BOX
id|VIDEO_LETTER_BOX
comma
multiline_comment|/* use letterbox format */
DECL|enumerator|VIDEO_CENTER_CUT_OUT
id|VIDEO_CENTER_CUT_OUT
multiline_comment|/* use center cut out format */
DECL|typedef|video_displayformat_t
)brace
id|video_displayformat_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|w
r_int
id|w
suffix:semicolon
DECL|member|h
r_int
id|h
suffix:semicolon
DECL|member|aspect_ratio
id|video_format_t
id|aspect_ratio
suffix:semicolon
DECL|typedef|video_size_t
)brace
id|video_size_t
suffix:semicolon
r_typedef
r_enum
(brace
DECL|enumerator|VIDEO_SOURCE_DEMUX
id|VIDEO_SOURCE_DEMUX
comma
multiline_comment|/* Select the demux as the main source */
DECL|enumerator|VIDEO_SOURCE_MEMORY
id|VIDEO_SOURCE_MEMORY
multiline_comment|/* If this source is selected, the stream &n;&t;&t;&t;       comes from the user through the write &n;&t;&t;&t;       system call */
DECL|typedef|video_stream_source_t
)brace
id|video_stream_source_t
suffix:semicolon
r_typedef
r_enum
(brace
DECL|enumerator|VIDEO_STOPPED
id|VIDEO_STOPPED
comma
multiline_comment|/* Video is stopped */
DECL|enumerator|VIDEO_PLAYING
id|VIDEO_PLAYING
comma
multiline_comment|/* Video is currently playing */
DECL|enumerator|VIDEO_FREEZED
id|VIDEO_FREEZED
multiline_comment|/* Video is freezed */
DECL|typedef|video_play_state_t
)brace
id|video_play_state_t
suffix:semicolon
DECL|struct|video_event
r_struct
id|video_event
(brace
DECL|member|type
r_int32
id|type
suffix:semicolon
DECL|macro|VIDEO_EVENT_SIZE_CHANGED
mdefine_line|#define VIDEO_EVENT_SIZE_CHANGED 1
DECL|member|timestamp
id|time_t
id|timestamp
suffix:semicolon
r_union
(brace
DECL|member|size
id|video_size_t
id|size
suffix:semicolon
DECL|member|u
)brace
id|u
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|video_status
r_struct
id|video_status
(brace
DECL|member|video_blank
r_int
id|video_blank
suffix:semicolon
multiline_comment|/* blank video on freeze? */
DECL|member|play_state
id|video_play_state_t
id|play_state
suffix:semicolon
multiline_comment|/* current state of playback */
DECL|member|stream_source
id|video_stream_source_t
id|stream_source
suffix:semicolon
multiline_comment|/* current source (demux/memory) */
DECL|member|video_format
id|video_format_t
id|video_format
suffix:semicolon
multiline_comment|/* current aspect ratio of stream*/
DECL|member|display_format
id|video_displayformat_t
id|display_format
suffix:semicolon
multiline_comment|/* selected cropping mode */
)brace
suffix:semicolon
DECL|struct|video_still_picture
r_struct
id|video_still_picture
(brace
DECL|member|iFrame
r_char
op_star
id|iFrame
suffix:semicolon
multiline_comment|/* pointer to a single iframe in memory */
DECL|member|size
r_int32
id|size
suffix:semicolon
)brace
suffix:semicolon
r_typedef
DECL|struct|video_highlight
r_struct
id|video_highlight
(brace
DECL|member|active
r_int
id|active
suffix:semicolon
multiline_comment|/*    1=show highlight, 0=hide highlight */
DECL|member|contrast1
r_uint8
id|contrast1
suffix:semicolon
multiline_comment|/*    7- 4  Pattern pixel contrast */
multiline_comment|/*    3- 0  Background pixel contrast */
DECL|member|contrast2
r_uint8
id|contrast2
suffix:semicolon
multiline_comment|/*    7- 4  Emphasis pixel-2 contrast */
multiline_comment|/*    3- 0  Emphasis pixel-1 contrast */
DECL|member|color1
r_uint8
id|color1
suffix:semicolon
multiline_comment|/*    7- 4  Pattern pixel color */
multiline_comment|/*    3- 0  Background pixel color */
DECL|member|color2
r_uint8
id|color2
suffix:semicolon
multiline_comment|/*    7- 4  Emphasis pixel-2 color */
multiline_comment|/*    3- 0  Emphasis pixel-1 color */
DECL|member|ypos
r_uint32
id|ypos
suffix:semicolon
multiline_comment|/*   23-22  auto action mode */
multiline_comment|/*   21-12  start y */
multiline_comment|/*    9- 0  end y */
DECL|member|xpos
r_uint32
id|xpos
suffix:semicolon
multiline_comment|/*   23-22  button color number */
multiline_comment|/*   21-12  start x */
multiline_comment|/*    9- 0  end x */
DECL|typedef|video_highlight_t
)brace
id|video_highlight_t
suffix:semicolon
DECL|struct|video_spu
r_typedef
r_struct
id|video_spu
(brace
DECL|member|active
r_int
id|active
suffix:semicolon
DECL|member|stream_id
r_int
id|stream_id
suffix:semicolon
DECL|typedef|video_spu_t
)brace
id|video_spu_t
suffix:semicolon
DECL|struct|video_spu_palette
r_typedef
r_struct
id|video_spu_palette
(brace
multiline_comment|/* SPU Palette information */
DECL|member|length
r_int
id|length
suffix:semicolon
DECL|member|palette
r_uint8
op_star
id|palette
suffix:semicolon
DECL|typedef|video_spu_palette_t
)brace
id|video_spu_palette_t
suffix:semicolon
DECL|struct|video_navi_pack
r_typedef
r_struct
id|video_navi_pack
(brace
DECL|member|length
r_int
id|length
suffix:semicolon
multiline_comment|/* 0 ... 1024 */
DECL|member|data
r_uint8
id|data
(braket
l_int|1024
)braket
suffix:semicolon
DECL|typedef|video_navi_pack_t
)brace
id|video_navi_pack_t
suffix:semicolon
DECL|typedef|video_attributes_t
r_typedef
r_uint16
id|video_attributes_t
suffix:semicolon
multiline_comment|/*   bits: descr. */
multiline_comment|/*   15-14 Video compression mode (0=MPEG-1, 1=MPEG-2) */
multiline_comment|/*   13-12 TV system (0=525/60, 1=625/50) */
multiline_comment|/*   11-10 Aspect ratio (0=4:3, 3=16:9) */
multiline_comment|/*    9- 8 permitted display mode on 4:3 monitor (0=both, 1=only pan-sca */
multiline_comment|/*    7    line 21-1 data present in GOP (1=yes, 0=no) */
multiline_comment|/*    6    line 21-2 data present in GOP (1=yes, 0=no) */
multiline_comment|/*    5- 3 source resolution (0=720x480/576, 1=704x480/576, 2=352x480/57 */
multiline_comment|/*    2    source letterboxed (1=yes, 0=no) */
multiline_comment|/*    0    film/camera mode (0=camera, 1=film (625/50 only)) */
multiline_comment|/* bit definitions for capabilities: */
multiline_comment|/* can the hardware decode MPEG1 and/or MPEG2? */
DECL|macro|VIDEO_CAP_MPEG1
mdefine_line|#define VIDEO_CAP_MPEG1   1 
DECL|macro|VIDEO_CAP_MPEG2
mdefine_line|#define VIDEO_CAP_MPEG2   2
multiline_comment|/* can you send a system and/or program stream to video device?&n;   (you still have to open the video and the audio device but only &n;    send the stream to the video device) */
DECL|macro|VIDEO_CAP_SYS
mdefine_line|#define VIDEO_CAP_SYS     4
DECL|macro|VIDEO_CAP_PROG
mdefine_line|#define VIDEO_CAP_PROG    8
multiline_comment|/* can the driver also handle SPU, NAVI and CSS encoded data? &n;   (CSS API is not present yet) */
DECL|macro|VIDEO_CAP_SPU
mdefine_line|#define VIDEO_CAP_SPU    16
DECL|macro|VIDEO_CAP_NAVI
mdefine_line|#define VIDEO_CAP_NAVI   32
DECL|macro|VIDEO_CAP_CSS
mdefine_line|#define VIDEO_CAP_CSS    64
DECL|macro|VIDEO_STOP
mdefine_line|#define VIDEO_STOP                 _IO(&squot;o&squot;, 21) 
DECL|macro|VIDEO_PLAY
mdefine_line|#define VIDEO_PLAY                 _IO(&squot;o&squot;, 22)
DECL|macro|VIDEO_FREEZE
mdefine_line|#define VIDEO_FREEZE               _IO(&squot;o&squot;, 23)
DECL|macro|VIDEO_CONTINUE
mdefine_line|#define VIDEO_CONTINUE             _IO(&squot;o&squot;, 24)
DECL|macro|VIDEO_SELECT_SOURCE
mdefine_line|#define VIDEO_SELECT_SOURCE        _IO(&squot;o&squot;, 25)
DECL|macro|VIDEO_SET_BLANK
mdefine_line|#define VIDEO_SET_BLANK            _IO(&squot;o&squot;, 26)
DECL|macro|VIDEO_GET_STATUS
mdefine_line|#define VIDEO_GET_STATUS           _IOR(&squot;o&squot;, 27, struct video_status)
DECL|macro|VIDEO_GET_EVENT
mdefine_line|#define VIDEO_GET_EVENT            _IOR(&squot;o&squot;, 28, struct video_event)
DECL|macro|VIDEO_SET_DISPLAY_FORMAT
mdefine_line|#define VIDEO_SET_DISPLAY_FORMAT   _IO(&squot;o&squot;, 29)
DECL|macro|VIDEO_STILLPICTURE
mdefine_line|#define VIDEO_STILLPICTURE         _IOW(&squot;o&squot;, 30, struct video_still_picture)
DECL|macro|VIDEO_FAST_FORWARD
mdefine_line|#define VIDEO_FAST_FORWARD         _IO(&squot;o&squot;, 31)
DECL|macro|VIDEO_SLOWMOTION
mdefine_line|#define VIDEO_SLOWMOTION           _IO(&squot;o&squot;, 32)
DECL|macro|VIDEO_GET_CAPABILITIES
mdefine_line|#define VIDEO_GET_CAPABILITIES     _IOR(&squot;o&squot;, 33, unsigned int)
DECL|macro|VIDEO_CLEAR_BUFFER
mdefine_line|#define VIDEO_CLEAR_BUFFER         _IO(&squot;o&squot;,  34)
DECL|macro|VIDEO_SET_ID
mdefine_line|#define VIDEO_SET_ID               _IO(&squot;o&squot;, 35)
DECL|macro|VIDEO_SET_STREAMTYPE
mdefine_line|#define VIDEO_SET_STREAMTYPE       _IO(&squot;o&squot;, 36)
DECL|macro|VIDEO_SET_FORMAT
mdefine_line|#define VIDEO_SET_FORMAT           _IO(&squot;o&squot;, 37)
DECL|macro|VIDEO_SET_SYSTEM
mdefine_line|#define VIDEO_SET_SYSTEM           _IO(&squot;o&squot;, 38)
DECL|macro|VIDEO_SET_HIGHLIGHT
mdefine_line|#define VIDEO_SET_HIGHLIGHT        _IOW(&squot;o&squot;, 39, video_highlight_t)
DECL|macro|VIDEO_SET_SPU
mdefine_line|#define VIDEO_SET_SPU              _IOW(&squot;o&squot;, 50, video_spu_t)
DECL|macro|VIDEO_SET_SPU_PALETTE
mdefine_line|#define VIDEO_SET_SPU_PALETTE      _IOW(&squot;o&squot;, 51, video_spu_palette_t)
DECL|macro|VIDEO_GET_NAVI
mdefine_line|#define VIDEO_GET_NAVI             _IOR(&squot;o&squot;, 52, video_navi_pack_t)
DECL|macro|VIDEO_SET_ATTRIBUTES
mdefine_line|#define VIDEO_SET_ATTRIBUTES       _IO(&squot;o&squot;, 53)
DECL|macro|VIDEO_GET_SIZE
mdefine_line|#define VIDEO_GET_SIZE             _IOR(&squot;o&squot;, 55, video_size_t)
macro_line|#endif /*_DVBVIDEO_H_*/
eof
