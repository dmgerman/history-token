multiline_comment|/* &n; * dmxdev.h&n; *&n; * Copyright (C) 2000 Ralph  Metzler &lt;ralph@convergence.de&gt;&n; *                  &amp; Marcus Metzler &lt;marcus@convergence.de&gt;&n;                      for convergence integrated media GmbH&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU Lesser General Public License&n; * as published by the Free Software Foundation; either version 2.1&n; * of the License, or (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU Lesser General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.&n; *&n; */
macro_line|#ifndef _DMXDEV_H_
DECL|macro|_DMXDEV_H_
mdefine_line|#define _DMXDEV_H_
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
macro_line|#include &lt;linux/dvb/dmx.h&gt;
macro_line|#include &quot;dvbdev.h&quot;
macro_line|#include &quot;demux.h&quot;
DECL|enum|dmxdevype
r_enum
id|dmxdevype
(brace
DECL|enumerator|DMXDEV_TYPE_NONE
id|DMXDEV_TYPE_NONE
comma
DECL|enumerator|DMXDEV_TYPE_SEC
id|DMXDEV_TYPE_SEC
comma
DECL|enumerator|DMXDEV_TYPE_PES
id|DMXDEV_TYPE_PES
comma
)brace
suffix:semicolon
DECL|enum|dmxdev_state
r_enum
id|dmxdev_state
(brace
DECL|enumerator|DMXDEV_STATE_FREE
id|DMXDEV_STATE_FREE
comma
DECL|enumerator|DMXDEV_STATE_ALLOCATED
id|DMXDEV_STATE_ALLOCATED
comma
DECL|enumerator|DMXDEV_STATE_SET
id|DMXDEV_STATE_SET
comma
DECL|enumerator|DMXDEV_STATE_GO
id|DMXDEV_STATE_GO
comma
DECL|enumerator|DMXDEV_STATE_DONE
id|DMXDEV_STATE_DONE
comma
DECL|enumerator|DMXDEV_STATE_TIMEDOUT
id|DMXDEV_STATE_TIMEDOUT
)brace
suffix:semicolon
DECL|struct|dmxdev_buffer
r_struct
id|dmxdev_buffer
(brace
DECL|member|data
id|u8
op_star
id|data
suffix:semicolon
DECL|member|size
r_int
id|size
suffix:semicolon
DECL|member|pread
r_int
id|pread
suffix:semicolon
DECL|member|pwrite
r_int
id|pwrite
suffix:semicolon
DECL|member|queue
id|wait_queue_head_t
id|queue
suffix:semicolon
DECL|member|error
r_int
id|error
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|dmxdev_filter
r_struct
id|dmxdev_filter
(brace
DECL|member|dvbdev
r_struct
id|dvb_device
op_star
id|dvbdev
suffix:semicolon
r_union
(brace
DECL|member|sec
r_struct
id|dmx_section_filter
op_star
id|sec
suffix:semicolon
DECL|member|filter
)brace
id|filter
suffix:semicolon
r_union
(brace
DECL|member|ts
r_struct
id|dmx_ts_feed
op_star
id|ts
suffix:semicolon
DECL|member|sec
r_struct
id|dmx_section_feed
op_star
id|sec
suffix:semicolon
DECL|member|feed
)brace
id|feed
suffix:semicolon
r_union
(brace
DECL|member|sec
r_struct
id|dmx_sct_filter_params
id|sec
suffix:semicolon
DECL|member|pes
r_struct
id|dmx_pes_filter_params
id|pes
suffix:semicolon
DECL|member|params
)brace
id|params
suffix:semicolon
DECL|member|type
r_int
id|type
suffix:semicolon
DECL|member|state
r_enum
id|dmxdev_state
id|state
suffix:semicolon
DECL|member|dev
r_struct
id|dmxdev
op_star
id|dev
suffix:semicolon
DECL|member|buffer
r_struct
id|dmxdev_buffer
id|buffer
suffix:semicolon
DECL|member|mutex
r_struct
id|semaphore
id|mutex
suffix:semicolon
multiline_comment|/* only for sections */
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
DECL|member|todo
r_int
id|todo
suffix:semicolon
DECL|member|secheader
id|u8
id|secheader
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|pid
id|u16
id|pid
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|dmxdev_dvr
r_struct
id|dmxdev_dvr
(brace
DECL|member|state
r_int
id|state
suffix:semicolon
DECL|member|dev
r_struct
id|dmxdev
op_star
id|dev
suffix:semicolon
DECL|member|buffer
r_struct
id|dmxdev_buffer
id|buffer
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|dmxdev
r_struct
id|dmxdev
(brace
DECL|member|dvbdev
r_struct
id|dvb_device
op_star
id|dvbdev
suffix:semicolon
DECL|member|dvr_dvbdev
r_struct
id|dvb_device
op_star
id|dvr_dvbdev
suffix:semicolon
DECL|member|filter
r_struct
id|dmxdev_filter
op_star
id|filter
suffix:semicolon
DECL|member|dvr
r_struct
id|dmxdev_dvr
op_star
id|dvr
suffix:semicolon
DECL|member|demux
r_struct
id|dmx_demux
op_star
id|demux
suffix:semicolon
DECL|member|filternum
r_int
id|filternum
suffix:semicolon
DECL|member|capabilities
r_int
id|capabilities
suffix:semicolon
DECL|macro|DMXDEV_CAP_DUPLEX
mdefine_line|#define DMXDEV_CAP_DUPLEX 1
DECL|member|dvr_orig_fe
r_struct
id|dmx_frontend
op_star
id|dvr_orig_fe
suffix:semicolon
DECL|member|dvr_buffer
r_struct
id|dmxdev_buffer
id|dvr_buffer
suffix:semicolon
DECL|macro|DVR_BUFFER_SIZE
mdefine_line|#define DVR_BUFFER_SIZE (10*188*1024)
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
id|dvb_dmxdev_init
c_func
(paren
r_struct
id|dmxdev
op_star
id|dmxdev
comma
r_struct
id|dvb_adapter
op_star
)paren
suffix:semicolon
r_void
id|dvb_dmxdev_release
c_func
(paren
r_struct
id|dmxdev
op_star
id|dmxdev
)paren
suffix:semicolon
macro_line|#endif /* _DMXDEV_H_ */
eof
