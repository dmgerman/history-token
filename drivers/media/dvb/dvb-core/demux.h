multiline_comment|/* demux.h &n; *&n; * Copyright (c) 2002 Convergence GmbH&n; * &n; * based on code:&n; * Copyright (c) 2000 Nokia Research Center&n; *                    Tampere, FINLAND&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU Lesser General Public License&n; * as published by the Free Software Foundation; either version 2.1&n; * of the License, or (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU Lesser General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.&n; *&n; */
macro_line|#ifndef __DEMUX_H 
DECL|macro|__DEMUX_H
mdefine_line|#define __DEMUX_H 
macro_line|#ifndef __KERNEL__ 
DECL|macro|__KERNEL__
mdefine_line|#define __KERNEL__ 
macro_line|#endif 
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/list.h&gt; 
macro_line|#include &lt;linux/time.h&gt; 
macro_line|#include &lt;linux/errno.h&gt;
multiline_comment|/*--------------------------------------------------------------------------*/
multiline_comment|/* Common definitions */
multiline_comment|/*--------------------------------------------------------------------------*/
multiline_comment|/*&n; * DMX_MAX_FILTER_SIZE: Maximum length (in bytes) of a section/PES filter.&n; */
macro_line|#ifndef DMX_MAX_FILTER_SIZE 
DECL|macro|DMX_MAX_FILTER_SIZE
mdefine_line|#define DMX_MAX_FILTER_SIZE 18
macro_line|#endif 
multiline_comment|/*&n; * dmx_success_t: Success codes for the Demux Callback API. &n; */
r_typedef
r_enum
(brace
DECL|enumerator|DMX_OK
id|DMX_OK
op_assign
l_int|0
comma
multiline_comment|/* Received Ok */
DECL|enumerator|DMX_LENGTH_ERROR
id|DMX_LENGTH_ERROR
comma
multiline_comment|/* Incorrect length */
DECL|enumerator|DMX_OVERRUN_ERROR
id|DMX_OVERRUN_ERROR
comma
multiline_comment|/* Receiver ring buffer overrun */
DECL|enumerator|DMX_CRC_ERROR
id|DMX_CRC_ERROR
comma
multiline_comment|/* Incorrect CRC */
DECL|enumerator|DMX_FRAME_ERROR
id|DMX_FRAME_ERROR
comma
multiline_comment|/* Frame alignment error */
DECL|enumerator|DMX_FIFO_ERROR
id|DMX_FIFO_ERROR
comma
multiline_comment|/* Receiver FIFO overrun */
DECL|enumerator|DMX_MISSED_ERROR
id|DMX_MISSED_ERROR
multiline_comment|/* Receiver missed packet */
DECL|typedef|dmx_success_t
)brace
id|dmx_success_t
suffix:semicolon
multiline_comment|/*--------------------------------------------------------------------------*/
multiline_comment|/* TS packet reception */
multiline_comment|/*--------------------------------------------------------------------------*/
multiline_comment|/* TS filter type for set() */
DECL|macro|TS_PACKET
mdefine_line|#define TS_PACKET       1   /* send TS packets (188 bytes) to callback (default) */ 
DECL|macro|TS_PAYLOAD_ONLY
mdefine_line|#define&t;TS_PAYLOAD_ONLY 2   /* in case TS_PACKET is set, only send the TS&n;&t;&t;&t;       payload (&lt;=184 bytes per packet) to callback */
DECL|macro|TS_DECODER
mdefine_line|#define TS_DECODER      4   /* send stream to built-in decoder (if present) */
multiline_comment|/* PES type for filters which write to built-in decoder */
multiline_comment|/* these should be kept identical to the types in dmx.h */
r_typedef
r_enum
(brace
multiline_comment|/* also send packets to decoder (if it exists) */
DECL|enumerator|DMX_TS_PES_AUDIO0
id|DMX_TS_PES_AUDIO0
comma
DECL|enumerator|DMX_TS_PES_VIDEO0
id|DMX_TS_PES_VIDEO0
comma
DECL|enumerator|DMX_TS_PES_TELETEXT0
id|DMX_TS_PES_TELETEXT0
comma
DECL|enumerator|DMX_TS_PES_SUBTITLE0
id|DMX_TS_PES_SUBTITLE0
comma
DECL|enumerator|DMX_TS_PES_PCR0
id|DMX_TS_PES_PCR0
comma
DECL|enumerator|DMX_TS_PES_AUDIO1
id|DMX_TS_PES_AUDIO1
comma
DECL|enumerator|DMX_TS_PES_VIDEO1
id|DMX_TS_PES_VIDEO1
comma
DECL|enumerator|DMX_TS_PES_TELETEXT1
id|DMX_TS_PES_TELETEXT1
comma
DECL|enumerator|DMX_TS_PES_SUBTITLE1
id|DMX_TS_PES_SUBTITLE1
comma
DECL|enumerator|DMX_TS_PES_PCR1
id|DMX_TS_PES_PCR1
comma
DECL|enumerator|DMX_TS_PES_AUDIO2
id|DMX_TS_PES_AUDIO2
comma
DECL|enumerator|DMX_TS_PES_VIDEO2
id|DMX_TS_PES_VIDEO2
comma
DECL|enumerator|DMX_TS_PES_TELETEXT2
id|DMX_TS_PES_TELETEXT2
comma
DECL|enumerator|DMX_TS_PES_SUBTITLE2
id|DMX_TS_PES_SUBTITLE2
comma
DECL|enumerator|DMX_TS_PES_PCR2
id|DMX_TS_PES_PCR2
comma
DECL|enumerator|DMX_TS_PES_AUDIO3
id|DMX_TS_PES_AUDIO3
comma
DECL|enumerator|DMX_TS_PES_VIDEO3
id|DMX_TS_PES_VIDEO3
comma
DECL|enumerator|DMX_TS_PES_TELETEXT3
id|DMX_TS_PES_TELETEXT3
comma
DECL|enumerator|DMX_TS_PES_SUBTITLE3
id|DMX_TS_PES_SUBTITLE3
comma
DECL|enumerator|DMX_TS_PES_PCR3
id|DMX_TS_PES_PCR3
comma
DECL|enumerator|DMX_TS_PES_OTHER
id|DMX_TS_PES_OTHER
DECL|typedef|dmx_ts_pes_t
)brace
id|dmx_ts_pes_t
suffix:semicolon
DECL|macro|DMX_TS_PES_AUDIO
mdefine_line|#define DMX_TS_PES_AUDIO    DMX_TS_PES_AUDIO0
DECL|macro|DMX_TS_PES_VIDEO
mdefine_line|#define DMX_TS_PES_VIDEO    DMX_TS_PES_VIDEO0
DECL|macro|DMX_TS_PES_TELETEXT
mdefine_line|#define DMX_TS_PES_TELETEXT DMX_TS_PES_TELETEXT0
DECL|macro|DMX_TS_PES_SUBTITLE
mdefine_line|#define DMX_TS_PES_SUBTITLE DMX_TS_PES_SUBTITLE0
DECL|macro|DMX_TS_PES_PCR
mdefine_line|#define DMX_TS_PES_PCR      DMX_TS_PES_PCR0
DECL|struct|dmx_ts_feed_s
r_struct
id|dmx_ts_feed_s
(brace
DECL|member|is_filtering
r_int
id|is_filtering
suffix:semicolon
multiline_comment|/* Set to non-zero when filtering in progress */
DECL|member|parent
r_struct
id|dmx_demux_s
op_star
id|parent
suffix:semicolon
multiline_comment|/* Back-pointer */
DECL|member|priv
r_void
op_star
id|priv
suffix:semicolon
multiline_comment|/* Pointer to private data of the API client */
DECL|member|set
r_int
(paren
op_star
id|set
)paren
(paren
r_struct
id|dmx_ts_feed_s
op_star
id|feed
comma
r_uint16
id|pid
comma
r_int
id|type
comma
id|dmx_ts_pes_t
id|pes_type
comma
r_int
id|callback_length
comma
r_int
id|circular_buffer_size
comma
r_int
id|descramble
comma
r_struct
id|timespec
id|timeout
)paren
suffix:semicolon
DECL|member|start_filtering
r_int
(paren
op_star
id|start_filtering
)paren
(paren
r_struct
id|dmx_ts_feed_s
op_star
id|feed
)paren
suffix:semicolon
DECL|member|stop_filtering
r_int
(paren
op_star
id|stop_filtering
)paren
(paren
r_struct
id|dmx_ts_feed_s
op_star
id|feed
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|dmx_ts_feed_t
r_typedef
r_struct
id|dmx_ts_feed_s
id|dmx_ts_feed_t
suffix:semicolon
multiline_comment|/*--------------------------------------------------------------------------*/
multiline_comment|/* Section reception */
multiline_comment|/*--------------------------------------------------------------------------*/
r_typedef
r_struct
(brace
DECL|member|filter_value
id|__u8
id|filter_value
(braket
id|DMX_MAX_FILTER_SIZE
)braket
suffix:semicolon
DECL|member|filter_mask
id|__u8
id|filter_mask
(braket
id|DMX_MAX_FILTER_SIZE
)braket
suffix:semicolon
DECL|member|filter_mode
id|__u8
id|filter_mode
(braket
id|DMX_MAX_FILTER_SIZE
)braket
suffix:semicolon
DECL|member|parent
r_struct
id|dmx_section_feed_s
op_star
id|parent
suffix:semicolon
multiline_comment|/* Back-pointer */
DECL|member|priv
r_void
op_star
id|priv
suffix:semicolon
multiline_comment|/* Pointer to private data of the API client */
DECL|typedef|dmx_section_filter_t
)brace
id|dmx_section_filter_t
suffix:semicolon
DECL|struct|dmx_section_feed_s
r_struct
id|dmx_section_feed_s
(brace
DECL|member|is_filtering
r_int
id|is_filtering
suffix:semicolon
multiline_comment|/* Set to non-zero when filtering in progress */
DECL|member|parent
r_struct
id|dmx_demux_s
op_star
id|parent
suffix:semicolon
multiline_comment|/* Back-pointer */
DECL|member|priv
r_void
op_star
id|priv
suffix:semicolon
multiline_comment|/* Pointer to private data of the API client */
DECL|member|set
r_int
(paren
op_star
id|set
)paren
(paren
r_struct
id|dmx_section_feed_s
op_star
id|feed
comma
id|__u16
id|pid
comma
r_int
id|circular_buffer_size
comma
r_int
id|descramble
comma
r_int
id|check_crc
)paren
suffix:semicolon
DECL|member|allocate_filter
r_int
(paren
op_star
id|allocate_filter
)paren
(paren
r_struct
id|dmx_section_feed_s
op_star
id|feed
comma
id|dmx_section_filter_t
op_star
op_star
id|filter
)paren
suffix:semicolon
DECL|member|release_filter
r_int
(paren
op_star
id|release_filter
)paren
(paren
r_struct
id|dmx_section_feed_s
op_star
id|feed
comma
id|dmx_section_filter_t
op_star
id|filter
)paren
suffix:semicolon
DECL|member|start_filtering
r_int
(paren
op_star
id|start_filtering
)paren
(paren
r_struct
id|dmx_section_feed_s
op_star
id|feed
)paren
suffix:semicolon
DECL|member|stop_filtering
r_int
(paren
op_star
id|stop_filtering
)paren
(paren
r_struct
id|dmx_section_feed_s
op_star
id|feed
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|dmx_section_feed_t
r_typedef
r_struct
id|dmx_section_feed_s
id|dmx_section_feed_t
suffix:semicolon
multiline_comment|/*--------------------------------------------------------------------------*/
multiline_comment|/* Callback functions */
multiline_comment|/*--------------------------------------------------------------------------*/
DECL|typedef|dmx_ts_cb
r_typedef
r_int
(paren
op_star
id|dmx_ts_cb
)paren
(paren
id|__u8
op_star
id|buffer1
comma
r_int
id|buffer1_length
comma
id|__u8
op_star
id|buffer2
comma
r_int
id|buffer2_length
comma
id|dmx_ts_feed_t
op_star
id|source
comma
id|dmx_success_t
id|success
)paren
suffix:semicolon
DECL|typedef|dmx_section_cb
r_typedef
r_int
(paren
op_star
id|dmx_section_cb
)paren
(paren
id|__u8
op_star
id|buffer1
comma
r_int
id|buffer1_len
comma
id|__u8
op_star
id|buffer2
comma
r_int
id|buffer2_len
comma
id|dmx_section_filter_t
op_star
id|source
comma
id|dmx_success_t
id|success
)paren
suffix:semicolon
multiline_comment|/*--------------------------------------------------------------------------*/
multiline_comment|/* DVB Front-End */
multiline_comment|/*--------------------------------------------------------------------------*/
r_typedef
r_enum
(brace
DECL|enumerator|DMX_MEMORY_FE
id|DMX_MEMORY_FE
comma
DECL|enumerator|DMX_FRONTEND_0
id|DMX_FRONTEND_0
comma
DECL|enumerator|DMX_FRONTEND_1
id|DMX_FRONTEND_1
comma
DECL|enumerator|DMX_FRONTEND_2
id|DMX_FRONTEND_2
comma
DECL|enumerator|DMX_FRONTEND_3
id|DMX_FRONTEND_3
comma
DECL|enumerator|DMX_STREAM_0
id|DMX_STREAM_0
comma
multiline_comment|/* external stream input, e.g. LVDS */
DECL|enumerator|DMX_STREAM_1
id|DMX_STREAM_1
comma
DECL|enumerator|DMX_STREAM_2
id|DMX_STREAM_2
comma
DECL|enumerator|DMX_STREAM_3
id|DMX_STREAM_3
DECL|typedef|dmx_frontend_source_t
)brace
id|dmx_frontend_source_t
suffix:semicolon
r_typedef
r_struct
(brace
multiline_comment|/* The following char* fields point to NULL terminated strings */
DECL|member|id
r_char
op_star
id|id
suffix:semicolon
multiline_comment|/* Unique front-end identifier */
DECL|member|vendor
r_char
op_star
id|vendor
suffix:semicolon
multiline_comment|/* Name of the front-end vendor */
DECL|member|model
r_char
op_star
id|model
suffix:semicolon
multiline_comment|/* Name of the front-end model */
DECL|member|connectivity_list
r_struct
id|list_head
id|connectivity_list
suffix:semicolon
multiline_comment|/* List of front-ends that can &n;&t;&t;&t;&t;&t;       be connected to a particular &n;&t;&t;&t;&t;&t;       demux */
DECL|member|priv
r_void
op_star
id|priv
suffix:semicolon
multiline_comment|/* Pointer to private data of the API client */
DECL|member|source
id|dmx_frontend_source_t
id|source
suffix:semicolon
DECL|typedef|dmx_frontend_t
)brace
id|dmx_frontend_t
suffix:semicolon
multiline_comment|/*--------------------------------------------------------------------------*/
multiline_comment|/* MPEG-2 TS Demux */
multiline_comment|/*--------------------------------------------------------------------------*/
multiline_comment|/* &n; * Flags OR&squot;ed in the capabilites field of struct dmx_demux_s. &n; */
DECL|macro|DMX_TS_FILTERING
mdefine_line|#define DMX_TS_FILTERING                        1 
DECL|macro|DMX_PES_FILTERING
mdefine_line|#define DMX_PES_FILTERING                       2 
DECL|macro|DMX_SECTION_FILTERING
mdefine_line|#define DMX_SECTION_FILTERING                   4 
DECL|macro|DMX_MEMORY_BASED_FILTERING
mdefine_line|#define DMX_MEMORY_BASED_FILTERING              8    /* write() available */ 
DECL|macro|DMX_CRC_CHECKING
mdefine_line|#define DMX_CRC_CHECKING                        16 
DECL|macro|DMX_TS_DESCRAMBLING
mdefine_line|#define DMX_TS_DESCRAMBLING                     32 
DECL|macro|DMX_SECTION_PAYLOAD_DESCRAMBLING
mdefine_line|#define DMX_SECTION_PAYLOAD_DESCRAMBLING        64 
DECL|macro|DMX_MAC_ADDRESS_DESCRAMBLING
mdefine_line|#define DMX_MAC_ADDRESS_DESCRAMBLING            128 
multiline_comment|/* &n; * Demux resource type identifier. &n;*/
multiline_comment|/* &n; * DMX_FE_ENTRY(): Casts elements in the list of registered &n; * front-ends from the generic type struct list_head&n; * to the type * dmx_frontend_t&n; *. &n;*/
DECL|macro|DMX_FE_ENTRY
mdefine_line|#define DMX_FE_ENTRY(list) list_entry(list, dmx_frontend_t, connectivity_list) 
DECL|struct|dmx_demux_s
r_struct
id|dmx_demux_s
(brace
multiline_comment|/* The following char* fields point to NULL terminated strings */
DECL|member|id
r_char
op_star
id|id
suffix:semicolon
multiline_comment|/* Unique demux identifier */
DECL|member|vendor
r_char
op_star
id|vendor
suffix:semicolon
multiline_comment|/* Name of the demux vendor */
DECL|member|model
r_char
op_star
id|model
suffix:semicolon
multiline_comment|/* Name of the demux model */
DECL|member|capabilities
id|__u32
id|capabilities
suffix:semicolon
multiline_comment|/* Bitfield of capability flags */
DECL|member|frontend
id|dmx_frontend_t
op_star
id|frontend
suffix:semicolon
multiline_comment|/* Front-end connected to the demux */
DECL|member|reg_list
r_struct
id|list_head
id|reg_list
suffix:semicolon
multiline_comment|/* List of registered demuxes */
DECL|member|priv
r_void
op_star
id|priv
suffix:semicolon
multiline_comment|/* Pointer to private data of the API client */
DECL|member|users
r_int
id|users
suffix:semicolon
multiline_comment|/* Number of users */
DECL|member|open
r_int
(paren
op_star
id|open
)paren
(paren
r_struct
id|dmx_demux_s
op_star
id|demux
)paren
suffix:semicolon
DECL|member|close
r_int
(paren
op_star
id|close
)paren
(paren
r_struct
id|dmx_demux_s
op_star
id|demux
)paren
suffix:semicolon
DECL|member|write
r_int
(paren
op_star
id|write
)paren
(paren
r_struct
id|dmx_demux_s
op_star
id|demux
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|count
)paren
suffix:semicolon
DECL|member|allocate_ts_feed
r_int
(paren
op_star
id|allocate_ts_feed
)paren
(paren
r_struct
id|dmx_demux_s
op_star
id|demux
comma
id|dmx_ts_feed_t
op_star
op_star
id|feed
comma
id|dmx_ts_cb
id|callback
)paren
suffix:semicolon
DECL|member|release_ts_feed
r_int
(paren
op_star
id|release_ts_feed
)paren
(paren
r_struct
id|dmx_demux_s
op_star
id|demux
comma
id|dmx_ts_feed_t
op_star
id|feed
)paren
suffix:semicolon
DECL|member|allocate_section_feed
r_int
(paren
op_star
id|allocate_section_feed
)paren
(paren
r_struct
id|dmx_demux_s
op_star
id|demux
comma
id|dmx_section_feed_t
op_star
op_star
id|feed
comma
id|dmx_section_cb
id|callback
)paren
suffix:semicolon
DECL|member|release_section_feed
r_int
(paren
op_star
id|release_section_feed
)paren
(paren
r_struct
id|dmx_demux_s
op_star
id|demux
comma
id|dmx_section_feed_t
op_star
id|feed
)paren
suffix:semicolon
DECL|member|descramble_mac_address
r_int
(paren
op_star
id|descramble_mac_address
)paren
(paren
r_struct
id|dmx_demux_s
op_star
id|demux
comma
id|__u8
op_star
id|buffer1
comma
r_int
id|buffer1_length
comma
id|__u8
op_star
id|buffer2
comma
r_int
id|buffer2_length
comma
id|__u16
id|pid
)paren
suffix:semicolon
DECL|member|descramble_section_payload
r_int
(paren
op_star
id|descramble_section_payload
)paren
(paren
r_struct
id|dmx_demux_s
op_star
id|demux
comma
id|__u8
op_star
id|buffer1
comma
r_int
id|buffer1_length
comma
id|__u8
op_star
id|buffer2
comma
r_int
id|buffer2_length
comma
id|__u16
id|pid
)paren
suffix:semicolon
DECL|member|add_frontend
r_int
(paren
op_star
id|add_frontend
)paren
(paren
r_struct
id|dmx_demux_s
op_star
id|demux
comma
id|dmx_frontend_t
op_star
id|frontend
)paren
suffix:semicolon
DECL|member|remove_frontend
r_int
(paren
op_star
id|remove_frontend
)paren
(paren
r_struct
id|dmx_demux_s
op_star
id|demux
comma
id|dmx_frontend_t
op_star
id|frontend
)paren
suffix:semicolon
DECL|member|get_frontends
r_struct
id|list_head
op_star
(paren
op_star
id|get_frontends
)paren
(paren
r_struct
id|dmx_demux_s
op_star
id|demux
)paren
suffix:semicolon
DECL|member|connect_frontend
r_int
(paren
op_star
id|connect_frontend
)paren
(paren
r_struct
id|dmx_demux_s
op_star
id|demux
comma
id|dmx_frontend_t
op_star
id|frontend
)paren
suffix:semicolon
DECL|member|disconnect_frontend
r_int
(paren
op_star
id|disconnect_frontend
)paren
(paren
r_struct
id|dmx_demux_s
op_star
id|demux
)paren
suffix:semicolon
DECL|member|get_pes_pids
r_int
(paren
op_star
id|get_pes_pids
)paren
(paren
r_struct
id|dmx_demux_s
op_star
id|demux
comma
id|__u16
op_star
id|pids
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|dmx_demux_t
r_typedef
r_struct
id|dmx_demux_s
id|dmx_demux_t
suffix:semicolon
multiline_comment|/*--------------------------------------------------------------------------*/
multiline_comment|/* Demux directory */
multiline_comment|/*--------------------------------------------------------------------------*/
multiline_comment|/* &n; * DMX_DIR_ENTRY(): Casts elements in the list of registered &n; * demuxes from the generic type struct list_head* to the type dmx_demux_t&n; *. &n; */
DECL|macro|DMX_DIR_ENTRY
mdefine_line|#define DMX_DIR_ENTRY(list) list_entry(list, dmx_demux_t, reg_list)
r_int
id|dmx_register_demux
(paren
id|dmx_demux_t
op_star
id|demux
)paren
suffix:semicolon
r_int
id|dmx_unregister_demux
(paren
id|dmx_demux_t
op_star
id|demux
)paren
suffix:semicolon
r_struct
id|list_head
op_star
id|dmx_get_demuxes
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* #ifndef __DEMUX_H */
eof
