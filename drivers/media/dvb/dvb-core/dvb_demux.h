multiline_comment|/* &n; * dvb_demux.h - DVB kernel demux API&n; *&n; * Copyright (C) 2000-2001 Marcus Metzler &lt;marcus@convergence.de&gt;&n; *                       &amp; Ralph  Metzler &lt;ralph@convergence.de&gt;&n; *                         for convergence integrated media GmbH&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU Lesser General Public License&n; * as published by the Free Software Foundation; either version 2.1&n; * of the License, or (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU Lesser General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.&n; *&n; */
macro_line|#ifndef _DVB_DEMUX_H_
DECL|macro|_DVB_DEMUX_H_
mdefine_line|#define _DVB_DEMUX_H_
macro_line|#include &lt;asm/semaphore.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &quot;demux.h&quot;
DECL|macro|DMX_TYPE_TS
mdefine_line|#define DMX_TYPE_TS  0
DECL|macro|DMX_TYPE_SEC
mdefine_line|#define DMX_TYPE_SEC 1
DECL|macro|DMX_TYPE_PES
mdefine_line|#define DMX_TYPE_PES 2
DECL|macro|DMX_STATE_FREE
mdefine_line|#define DMX_STATE_FREE      0
DECL|macro|DMX_STATE_ALLOCATED
mdefine_line|#define DMX_STATE_ALLOCATED 1
DECL|macro|DMX_STATE_SET
mdefine_line|#define DMX_STATE_SET       2
DECL|macro|DMX_STATE_READY
mdefine_line|#define DMX_STATE_READY     3
DECL|macro|DMX_STATE_GO
mdefine_line|#define DMX_STATE_GO        4
DECL|macro|DVB_DEMUX_MASK_MAX
mdefine_line|#define DVB_DEMUX_MASK_MAX 18
DECL|struct|dvb_demux_filter
r_struct
id|dvb_demux_filter
(brace
DECL|member|filter
r_struct
id|dmx_section_filter
id|filter
suffix:semicolon
DECL|member|maskandmode
id|u8
id|maskandmode
(braket
id|DMX_MAX_FILTER_SIZE
)braket
suffix:semicolon
DECL|member|maskandnotmode
id|u8
id|maskandnotmode
(braket
id|DMX_MAX_FILTER_SIZE
)braket
suffix:semicolon
DECL|member|doneq
r_int
id|doneq
suffix:semicolon
DECL|member|next
r_struct
id|dvb_demux_filter
op_star
id|next
suffix:semicolon
DECL|member|feed
r_struct
id|dvb_demux_feed
op_star
id|feed
suffix:semicolon
DECL|member|index
r_int
id|index
suffix:semicolon
DECL|member|state
r_int
id|state
suffix:semicolon
DECL|member|type
r_int
id|type
suffix:semicolon
DECL|member|pesto
r_int
id|pesto
suffix:semicolon
DECL|member|handle
id|u16
id|handle
suffix:semicolon
DECL|member|hw_handle
id|u16
id|hw_handle
suffix:semicolon
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
DECL|member|ts_state
r_int
id|ts_state
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|DMX_FEED_ENTRY
mdefine_line|#define DMX_FEED_ENTRY(pos) list_entry(pos, struct dvb_demux_feed, list_head)
DECL|struct|dvb_demux_feed
r_struct
id|dvb_demux_feed
(brace
r_union
(brace
DECL|member|ts
r_struct
id|dmx_ts_feed
id|ts
suffix:semicolon
DECL|member|sec
r_struct
id|dmx_section_feed
id|sec
suffix:semicolon
DECL|member|feed
)brace
id|feed
suffix:semicolon
r_union
(brace
DECL|member|ts
id|dmx_ts_cb
id|ts
suffix:semicolon
DECL|member|sec
id|dmx_section_cb
id|sec
suffix:semicolon
DECL|member|cb
)brace
id|cb
suffix:semicolon
DECL|member|demux
r_struct
id|dvb_demux
op_star
id|demux
suffix:semicolon
DECL|member|priv
r_void
op_star
id|priv
suffix:semicolon
DECL|member|type
r_int
id|type
suffix:semicolon
DECL|member|state
r_int
id|state
suffix:semicolon
DECL|member|pid
id|u16
id|pid
suffix:semicolon
DECL|member|buffer
id|u8
op_star
id|buffer
suffix:semicolon
DECL|member|buffer_size
r_int
id|buffer_size
suffix:semicolon
DECL|member|descramble
r_int
id|descramble
suffix:semicolon
DECL|member|timeout
r_struct
id|timespec
id|timeout
suffix:semicolon
DECL|member|filter
r_struct
id|dvb_demux_filter
op_star
id|filter
suffix:semicolon
DECL|member|cb_length
r_int
id|cb_length
suffix:semicolon
DECL|member|ts_type
r_int
id|ts_type
suffix:semicolon
DECL|member|pes_type
r_enum
id|dmx_ts_pes
id|pes_type
suffix:semicolon
DECL|member|cc
r_int
id|cc
suffix:semicolon
DECL|member|peslen
id|u16
id|peslen
suffix:semicolon
DECL|member|list_head
r_struct
id|list_head
id|list_head
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|dvb_demux
r_struct
id|dvb_demux
(brace
DECL|member|dmx
r_struct
id|dmx_demux
id|dmx
suffix:semicolon
DECL|member|priv
r_void
op_star
id|priv
suffix:semicolon
DECL|member|filternum
r_int
id|filternum
suffix:semicolon
DECL|member|feednum
r_int
id|feednum
suffix:semicolon
DECL|member|start_feed
r_int
(paren
op_star
id|start_feed
)paren
(paren
r_struct
id|dvb_demux_feed
op_star
id|feed
)paren
suffix:semicolon
DECL|member|stop_feed
r_int
(paren
op_star
id|stop_feed
)paren
(paren
r_struct
id|dvb_demux_feed
op_star
id|feed
)paren
suffix:semicolon
DECL|member|write_to_decoder
r_int
(paren
op_star
id|write_to_decoder
)paren
(paren
r_struct
id|dvb_demux_feed
op_star
id|feed
comma
r_const
id|u8
op_star
id|buf
comma
r_int
id|len
)paren
suffix:semicolon
DECL|member|check_crc32
id|u32
(paren
op_star
id|check_crc32
)paren
(paren
r_struct
id|dvb_demux_feed
op_star
id|feed
comma
r_const
id|u8
op_star
id|buf
comma
r_int
id|len
)paren
suffix:semicolon
DECL|member|memcopy
r_void
(paren
op_star
id|memcopy
)paren
(paren
r_struct
id|dvb_demux_feed
op_star
id|feed
comma
id|u8
op_star
id|dst
comma
r_const
id|u8
op_star
id|src
comma
r_int
id|len
)paren
suffix:semicolon
DECL|member|users
r_int
id|users
suffix:semicolon
DECL|macro|MAX_DVB_DEMUX_USERS
mdefine_line|#define MAX_DVB_DEMUX_USERS 10
DECL|member|filter
r_struct
id|dvb_demux_filter
op_star
id|filter
suffix:semicolon
DECL|member|feed
r_struct
id|dvb_demux_feed
op_star
id|feed
suffix:semicolon
DECL|member|frontend_list
r_struct
id|list_head
id|frontend_list
suffix:semicolon
DECL|member|pesfilter
r_struct
id|dvb_demux_feed
op_star
id|pesfilter
(braket
id|DMX_TS_PES_OTHER
)braket
suffix:semicolon
DECL|member|pids
id|u16
id|pids
(braket
id|DMX_TS_PES_OTHER
)braket
suffix:semicolon
DECL|member|playing
r_int
id|playing
suffix:semicolon
DECL|member|recording
r_int
id|recording
suffix:semicolon
DECL|macro|DMX_MAX_PID
mdefine_line|#define DMX_MAX_PID 0x2000
DECL|member|feed_list
r_struct
id|list_head
id|feed_list
suffix:semicolon
DECL|member|tsbuf
id|u8
id|tsbuf
(braket
l_int|188
)braket
suffix:semicolon
DECL|member|tsbufp
r_int
id|tsbufp
suffix:semicolon
DECL|member|mutex
r_struct
id|semaphore
id|mutex
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
)brace
suffix:semicolon
r_int
id|dvb_dmx_init
c_func
(paren
r_struct
id|dvb_demux
op_star
id|dvbdemux
)paren
suffix:semicolon
r_int
id|dvb_dmx_release
c_func
(paren
r_struct
id|dvb_demux
op_star
id|dvbdemux
)paren
suffix:semicolon
r_void
id|dvb_dmx_swfilter_packet
c_func
(paren
r_struct
id|dvb_demux
op_star
id|dvbdmx
comma
r_const
id|u8
op_star
id|buf
)paren
suffix:semicolon
r_void
id|dvb_dmx_swfilter_packets
c_func
(paren
r_struct
id|dvb_demux
op_star
id|dvbdmx
comma
r_const
id|u8
op_star
id|buf
comma
r_int
id|count
)paren
suffix:semicolon
r_void
id|dvb_dmx_swfilter
c_func
(paren
r_struct
id|dvb_demux
op_star
id|demux
comma
r_const
id|u8
op_star
id|buf
comma
r_int
id|count
)paren
suffix:semicolon
r_int
id|dvbdmx_connect_frontend
c_func
(paren
r_struct
id|dmx_demux
op_star
id|demux
comma
r_struct
id|dmx_frontend
op_star
id|frontend
)paren
suffix:semicolon
r_int
id|dvbdmx_disconnect_frontend
c_func
(paren
r_struct
id|dmx_demux
op_star
id|demux
)paren
suffix:semicolon
macro_line|#endif /* _DVB_DEMUX_H_ */
eof
