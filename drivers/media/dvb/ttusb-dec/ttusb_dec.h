multiline_comment|/*&n; * TTUSB DEC Driver&n; *&n; * Copyright (C) 2003 Alex Woods &lt;linux-dvb@giblets.org&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; */
macro_line|#ifndef _TTUSB_DEC_H
DECL|macro|_TTUSB_DEC_H
mdefine_line|#define _TTUSB_DEC_H
macro_line|#include &lt;asm/semaphore.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &quot;dmxdev.h&quot;
macro_line|#include &quot;dvb_demux.h&quot;
macro_line|#include &quot;dvb_filter.h&quot;
macro_line|#include &quot;dvb_i2c.h&quot;
macro_line|#include &quot;dvb_net.h&quot;
DECL|macro|DRIVER_NAME
mdefine_line|#define DRIVER_NAME&t;&t;&quot;TechnoTrend/Hauppauge DEC USB&quot;
DECL|macro|COMMAND_PIPE
mdefine_line|#define COMMAND_PIPE&t;&t;0x03
DECL|macro|RESULT_PIPE
mdefine_line|#define RESULT_PIPE&t;&t;0x84
DECL|macro|STREAM_PIPE
mdefine_line|#define STREAM_PIPE&t;&t;0x88
DECL|macro|COMMAND_PACKET_SIZE
mdefine_line|#define COMMAND_PACKET_SIZE&t;0x3c
DECL|macro|ARM_PACKET_SIZE
mdefine_line|#define ARM_PACKET_SIZE&t;&t;0x1000
DECL|macro|ISO_BUF_COUNT
mdefine_line|#define ISO_BUF_COUNT&t;&t;0x04
DECL|macro|FRAMES_PER_ISO_BUF
mdefine_line|#define FRAMES_PER_ISO_BUF&t;0x04
DECL|macro|ISO_FRAME_SIZE
mdefine_line|#define ISO_FRAME_SIZE&t;&t;0x0380
DECL|macro|MAX_AV_PES_LENGTH
mdefine_line|#define&t;MAX_AV_PES_LENGTH&t;6144
DECL|struct|ttusb_dec
r_struct
id|ttusb_dec
(brace
multiline_comment|/* DVB bits */
DECL|member|adapter
r_struct
id|dvb_adapter
op_star
id|adapter
suffix:semicolon
DECL|member|dmxdev
r_struct
id|dmxdev
id|dmxdev
suffix:semicolon
DECL|member|demux
r_struct
id|dvb_demux
id|demux
suffix:semicolon
DECL|member|frontend
r_struct
id|dmx_frontend
id|frontend
suffix:semicolon
DECL|member|i2c_bus
r_struct
id|dvb_i2c_bus
op_star
id|i2c_bus
suffix:semicolon
DECL|member|dvb_net
r_struct
id|dvb_net
id|dvb_net
suffix:semicolon
DECL|member|pid
id|u16
id|pid
(braket
id|DMX_PES_OTHER
)braket
suffix:semicolon
multiline_comment|/* USB bits */
DECL|member|udev
r_struct
id|usb_device
op_star
id|udev
suffix:semicolon
DECL|member|trans_count
id|u8
id|trans_count
suffix:semicolon
DECL|member|command_pipe
r_int
r_int
id|command_pipe
suffix:semicolon
DECL|member|result_pipe
r_int
r_int
id|result_pipe
suffix:semicolon
DECL|member|stream_pipe
r_int
r_int
id|stream_pipe
suffix:semicolon
DECL|member|interface
r_int
id|interface
suffix:semicolon
DECL|member|usb_sem
r_struct
id|semaphore
id|usb_sem
suffix:semicolon
DECL|member|iso_buffer
r_void
op_star
id|iso_buffer
suffix:semicolon
DECL|member|iso_dma_handle
id|dma_addr_t
id|iso_dma_handle
suffix:semicolon
DECL|member|iso_urb
r_struct
id|urb
op_star
id|iso_urb
(braket
id|ISO_BUF_COUNT
)braket
suffix:semicolon
DECL|member|iso_stream_count
r_int
id|iso_stream_count
suffix:semicolon
DECL|member|iso_sem
r_struct
id|semaphore
id|iso_sem
suffix:semicolon
DECL|member|av_pes
id|u8
id|av_pes
(braket
id|MAX_AV_PES_LENGTH
op_plus
l_int|4
)braket
suffix:semicolon
DECL|member|av_pes_state
r_int
id|av_pes_state
suffix:semicolon
DECL|member|av_pes_length
r_int
id|av_pes_length
suffix:semicolon
DECL|member|av_pes_payload_length
r_int
id|av_pes_payload_length
suffix:semicolon
DECL|member|a_pes2ts
r_struct
id|dvb_filter_pes2ts
id|a_pes2ts
suffix:semicolon
DECL|member|v_pes2ts
r_struct
id|dvb_filter_pes2ts
id|v_pes2ts
suffix:semicolon
DECL|member|v_pes
id|u8
id|v_pes
(braket
l_int|16
op_plus
id|MAX_AV_PES_LENGTH
)braket
suffix:semicolon
DECL|member|v_pes_length
r_int
id|v_pes_length
suffix:semicolon
DECL|member|v_pes_postbytes
r_int
id|v_pes_postbytes
suffix:semicolon
DECL|member|urb_frame_list
r_struct
id|list_head
id|urb_frame_list
suffix:semicolon
DECL|member|urb_tasklet
r_struct
id|tasklet_struct
id|urb_tasklet
suffix:semicolon
DECL|member|urb_frame_list_lock
id|spinlock_t
id|urb_frame_list_lock
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|urb_frame
r_struct
id|urb_frame
(brace
DECL|member|data
id|u8
id|data
(braket
id|ISO_FRAME_SIZE
)braket
suffix:semicolon
DECL|member|length
r_int
id|length
suffix:semicolon
DECL|member|urb_frame_list
r_struct
id|list_head
id|urb_frame_list
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
eof
