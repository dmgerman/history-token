multiline_comment|/*&n; * video1394.h - driver for OHCI 1394 boards&n; * Copyright (C)1999,2000 Sebastien Rougeaux &lt;sebastien.rougeaux@anu.edu.au&gt;&n; *                        Peter Schlaile &lt;udbz@rz.uni-karlsruhe.de&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software Foundation,&n; * Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.&n; */
macro_line|#ifndef _VIDEO_1394_H
DECL|macro|_VIDEO_1394_H
mdefine_line|#define _VIDEO_1394_H
macro_line|#include &quot;ieee1394-ioctl.h&quot;
DECL|macro|VIDEO1394_DRIVER_NAME
mdefine_line|#define VIDEO1394_DRIVER_NAME &quot;video1394&quot;
DECL|macro|VIDEO1394_MAX_SIZE
mdefine_line|#define VIDEO1394_MAX_SIZE 0x4000000
r_enum
(brace
DECL|enumerator|VIDEO1394_BUFFER_FREE
id|VIDEO1394_BUFFER_FREE
op_assign
l_int|0
comma
DECL|enumerator|VIDEO1394_BUFFER_QUEUED
id|VIDEO1394_BUFFER_QUEUED
comma
DECL|enumerator|VIDEO1394_BUFFER_READY
id|VIDEO1394_BUFFER_READY
)brace
suffix:semicolon
DECL|macro|VIDEO1394_SYNC_FRAMES
mdefine_line|#define VIDEO1394_SYNC_FRAMES          0x00000001
DECL|macro|VIDEO1394_INCLUDE_ISO_HEADERS
mdefine_line|#define VIDEO1394_INCLUDE_ISO_HEADERS  0x00000002
DECL|macro|VIDEO1394_VARIABLE_PACKET_SIZE
mdefine_line|#define VIDEO1394_VARIABLE_PACKET_SIZE 0x00000004
DECL|struct|video1394_mmap
r_struct
id|video1394_mmap
(brace
DECL|member|channel
r_int
id|channel
suffix:semicolon
multiline_comment|/* -1 to find an open channel in LISTEN/TALK */
DECL|member|sync_tag
r_int
r_int
id|sync_tag
suffix:semicolon
DECL|member|nb_buffers
r_int
r_int
id|nb_buffers
suffix:semicolon
DECL|member|buf_size
r_int
r_int
id|buf_size
suffix:semicolon
DECL|member|packet_size
r_int
r_int
id|packet_size
suffix:semicolon
multiline_comment|/* For VARIABLE_PACKET_SIZE:&n;&t;&t;&t;&t;     Maximum packet size */
DECL|member|fps
r_int
r_int
id|fps
suffix:semicolon
DECL|member|syt_offset
r_int
r_int
id|syt_offset
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* For TALK_QUEUE_BUFFER with VIDEO1394_VARIABLE_PACKET_SIZE use */
DECL|struct|video1394_queue_variable
r_struct
id|video1394_queue_variable
(brace
DECL|member|channel
r_int
r_int
id|channel
suffix:semicolon
DECL|member|buffer
r_int
r_int
id|buffer
suffix:semicolon
DECL|member|packet_sizes
r_int
r_int
id|__user
op_star
id|packet_sizes
suffix:semicolon
multiline_comment|/* Buffer of size:&n;&t;&t;&t;&t;       buf_size / packet_size  */
)brace
suffix:semicolon
DECL|struct|video1394_wait
r_struct
id|video1394_wait
(brace
DECL|member|channel
r_int
r_int
id|channel
suffix:semicolon
DECL|member|buffer
r_int
r_int
id|buffer
suffix:semicolon
DECL|member|filltime
r_struct
id|timeval
id|filltime
suffix:semicolon
multiline_comment|/* time of buffer full */
)brace
suffix:semicolon
macro_line|#endif
eof
