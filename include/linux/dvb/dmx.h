multiline_comment|/* &n; * dmx.h&n; *&n; * Copyright (C) 2000 Marcus Metzler &lt;marcus@convergence.de&gt;&n; *                  &amp; Ralph  Metzler &lt;ralph@convergence.de&gt;&n;                      for convergence integrated media GmbH&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU Lesser General Public License&n; * as published by the Free Software Foundation; either version 2.1&n; * of the License, or (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU Lesser General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.&n; *&n; */
macro_line|#ifndef _DVBDMX_H_
DECL|macro|_DVBDMX_H_
mdefine_line|#define _DVBDMX_H_
macro_line|#include &lt;asm/types.h&gt;
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/time.h&gt;
macro_line|#else
macro_line|#include &lt;time.h&gt;
macro_line|#endif
DECL|macro|DMX_FILTER_SIZE
mdefine_line|#define DMX_FILTER_SIZE 16
r_typedef
r_enum
(brace
DECL|enumerator|DMX_OUT_DECODER
id|DMX_OUT_DECODER
comma
multiline_comment|/* Streaming directly to decoder. */
DECL|enumerator|DMX_OUT_TAP
id|DMX_OUT_TAP
comma
multiline_comment|/* Output going to a memory buffer */
multiline_comment|/* (to be retrieved via the read command).*/
DECL|enumerator|DMX_OUT_TS_TAP
id|DMX_OUT_TS_TAP
multiline_comment|/* Output multiplexed into a new TS  */
multiline_comment|/* (to be retrieved by reading from the */
multiline_comment|/* logical DVR device).                 */
DECL|typedef|dmx_output_t
)brace
id|dmx_output_t
suffix:semicolon
r_typedef
r_enum
(brace
DECL|enumerator|DMX_IN_FRONTEND
id|DMX_IN_FRONTEND
comma
multiline_comment|/* Input from a front-end device.  */
DECL|enumerator|DMX_IN_DVR
id|DMX_IN_DVR
multiline_comment|/* Input from the logical DVR device.  */
DECL|typedef|dmx_input_t
)brace
id|dmx_input_t
suffix:semicolon
r_typedef
r_enum
(brace
DECL|enumerator|DMX_PES_AUDIO0
id|DMX_PES_AUDIO0
comma
DECL|enumerator|DMX_PES_VIDEO0
id|DMX_PES_VIDEO0
comma
DECL|enumerator|DMX_PES_TELETEXT0
id|DMX_PES_TELETEXT0
comma
DECL|enumerator|DMX_PES_SUBTITLE0
id|DMX_PES_SUBTITLE0
comma
DECL|enumerator|DMX_PES_PCR0
id|DMX_PES_PCR0
comma
DECL|enumerator|DMX_PES_AUDIO1
id|DMX_PES_AUDIO1
comma
DECL|enumerator|DMX_PES_VIDEO1
id|DMX_PES_VIDEO1
comma
DECL|enumerator|DMX_PES_TELETEXT1
id|DMX_PES_TELETEXT1
comma
DECL|enumerator|DMX_PES_SUBTITLE1
id|DMX_PES_SUBTITLE1
comma
DECL|enumerator|DMX_PES_PCR1
id|DMX_PES_PCR1
comma
DECL|enumerator|DMX_PES_AUDIO2
id|DMX_PES_AUDIO2
comma
DECL|enumerator|DMX_PES_VIDEO2
id|DMX_PES_VIDEO2
comma
DECL|enumerator|DMX_PES_TELETEXT2
id|DMX_PES_TELETEXT2
comma
DECL|enumerator|DMX_PES_SUBTITLE2
id|DMX_PES_SUBTITLE2
comma
DECL|enumerator|DMX_PES_PCR2
id|DMX_PES_PCR2
comma
DECL|enumerator|DMX_PES_AUDIO3
id|DMX_PES_AUDIO3
comma
DECL|enumerator|DMX_PES_VIDEO3
id|DMX_PES_VIDEO3
comma
DECL|enumerator|DMX_PES_TELETEXT3
id|DMX_PES_TELETEXT3
comma
DECL|enumerator|DMX_PES_SUBTITLE3
id|DMX_PES_SUBTITLE3
comma
DECL|enumerator|DMX_PES_PCR3
id|DMX_PES_PCR3
comma
DECL|enumerator|DMX_PES_OTHER
id|DMX_PES_OTHER
DECL|typedef|dmx_pes_type_t
)brace
id|dmx_pes_type_t
suffix:semicolon
DECL|macro|DMX_PES_AUDIO
mdefine_line|#define DMX_PES_AUDIO    DMX_PES_AUDIO0
DECL|macro|DMX_PES_VIDEO
mdefine_line|#define DMX_PES_VIDEO    DMX_PES_VIDEO0
DECL|macro|DMX_PES_TELETEXT
mdefine_line|#define DMX_PES_TELETEXT DMX_PES_TELETEXT0
DECL|macro|DMX_PES_SUBTITLE
mdefine_line|#define DMX_PES_SUBTITLE DMX_PES_SUBTITLE0
DECL|macro|DMX_PES_PCR
mdefine_line|#define DMX_PES_PCR      DMX_PES_PCR0
r_typedef
r_enum
(brace
DECL|enumerator|DMX_SCRAMBLING_EV
id|DMX_SCRAMBLING_EV
comma
DECL|enumerator|DMX_FRONTEND_EV
id|DMX_FRONTEND_EV
DECL|typedef|dmx_event_t
)brace
id|dmx_event_t
suffix:semicolon
r_typedef
r_enum
(brace
DECL|enumerator|DMX_SCRAMBLING_OFF
id|DMX_SCRAMBLING_OFF
comma
DECL|enumerator|DMX_SCRAMBLING_ON
id|DMX_SCRAMBLING_ON
DECL|typedef|dmx_scrambling_status_t
)brace
id|dmx_scrambling_status_t
suffix:semicolon
DECL|struct|dmx_filter
r_typedef
r_struct
id|dmx_filter
(brace
DECL|member|filter
id|__u8
id|filter
(braket
id|DMX_FILTER_SIZE
)braket
suffix:semicolon
DECL|member|mask
id|__u8
id|mask
(braket
id|DMX_FILTER_SIZE
)braket
suffix:semicolon
DECL|member|mode
id|__u8
id|mode
(braket
id|DMX_FILTER_SIZE
)braket
suffix:semicolon
DECL|typedef|dmx_filter_t
)brace
id|dmx_filter_t
suffix:semicolon
DECL|struct|dmx_sct_filter_params
r_struct
id|dmx_sct_filter_params
(brace
DECL|member|pid
id|__u16
id|pid
suffix:semicolon
DECL|member|filter
id|dmx_filter_t
id|filter
suffix:semicolon
DECL|member|timeout
id|__u32
id|timeout
suffix:semicolon
DECL|member|flags
id|__u32
id|flags
suffix:semicolon
DECL|macro|DMX_CHECK_CRC
mdefine_line|#define DMX_CHECK_CRC       1
DECL|macro|DMX_ONESHOT
mdefine_line|#define DMX_ONESHOT         2
DECL|macro|DMX_IMMEDIATE_START
mdefine_line|#define DMX_IMMEDIATE_START 4
DECL|macro|DMX_KERNEL_CLIENT
mdefine_line|#define DMX_KERNEL_CLIENT   0x8000
)brace
suffix:semicolon
DECL|struct|dmx_pes_filter_params
r_struct
id|dmx_pes_filter_params
(brace
DECL|member|pid
id|__u16
id|pid
suffix:semicolon
DECL|member|input
id|dmx_input_t
id|input
suffix:semicolon
DECL|member|output
id|dmx_output_t
id|output
suffix:semicolon
DECL|member|pes_type
id|dmx_pes_type_t
id|pes_type
suffix:semicolon
DECL|member|flags
id|__u32
id|flags
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|dmx_event
r_struct
id|dmx_event
(brace
DECL|member|event
id|dmx_event_t
id|event
suffix:semicolon
DECL|member|timeStamp
id|time_t
id|timeStamp
suffix:semicolon
r_union
(brace
DECL|member|scrambling
id|dmx_scrambling_status_t
id|scrambling
suffix:semicolon
DECL|member|u
)brace
id|u
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|dmx_caps
r_typedef
r_struct
id|dmx_caps
(brace
DECL|member|caps
id|__u32
id|caps
suffix:semicolon
DECL|member|num_decoders
r_int
id|num_decoders
suffix:semicolon
DECL|typedef|dmx_caps_t
)brace
id|dmx_caps_t
suffix:semicolon
r_typedef
r_enum
(brace
DECL|enumerator|DMX_SOURCE_FRONT0
id|DMX_SOURCE_FRONT0
op_assign
l_int|0
comma
DECL|enumerator|DMX_SOURCE_FRONT1
id|DMX_SOURCE_FRONT1
comma
DECL|enumerator|DMX_SOURCE_FRONT2
id|DMX_SOURCE_FRONT2
comma
DECL|enumerator|DMX_SOURCE_FRONT3
id|DMX_SOURCE_FRONT3
comma
DECL|enumerator|DMX_SOURCE_DVR0
id|DMX_SOURCE_DVR0
op_assign
l_int|16
comma
DECL|enumerator|DMX_SOURCE_DVR1
id|DMX_SOURCE_DVR1
comma
DECL|enumerator|DMX_SOURCE_DVR2
id|DMX_SOURCE_DVR2
comma
DECL|enumerator|DMX_SOURCE_DVR3
id|DMX_SOURCE_DVR3
DECL|typedef|dmx_source_t
)brace
id|dmx_source_t
suffix:semicolon
DECL|struct|dmx_stc
r_struct
id|dmx_stc
(brace
DECL|member|num
r_int
r_int
id|num
suffix:semicolon
multiline_comment|/* input : which STC? 0..N */
DECL|member|base
r_int
r_int
id|base
suffix:semicolon
multiline_comment|/* output: divisor for stc to get 90 kHz clock */
DECL|member|stc
id|__u64
id|stc
suffix:semicolon
multiline_comment|/* output: stc in &squot;base&squot;*90 kHz units */
)brace
suffix:semicolon
DECL|macro|DMX_START
mdefine_line|#define DMX_START                _IO(&squot;o&squot;,41) 
DECL|macro|DMX_STOP
mdefine_line|#define DMX_STOP                 _IO(&squot;o&squot;,42)
DECL|macro|DMX_SET_FILTER
mdefine_line|#define DMX_SET_FILTER           _IOW(&squot;o&squot;,43,struct dmx_sct_filter_params)
DECL|macro|DMX_SET_PES_FILTER
mdefine_line|#define DMX_SET_PES_FILTER       _IOW(&squot;o&squot;,44,struct dmx_pes_filter_params)
DECL|macro|DMX_SET_BUFFER_SIZE
mdefine_line|#define DMX_SET_BUFFER_SIZE      _IO(&squot;o&squot;,45)
DECL|macro|DMX_GET_EVENT
mdefine_line|#define DMX_GET_EVENT            _IOR(&squot;o&squot;,46,struct dmx_event)
DECL|macro|DMX_GET_PES_PIDS
mdefine_line|#define DMX_GET_PES_PIDS         _IOR(&squot;o&squot;, 47, __u16[5])
DECL|macro|DMX_GET_CAPS
mdefine_line|#define DMX_GET_CAPS             _IOR(&squot;o&squot;,48,dmx_caps_t)
DECL|macro|DMX_SET_SOURCE
mdefine_line|#define DMX_SET_SOURCE           _IOW(&squot;o&squot;,49,dmx_source_t)
DECL|macro|DMX_GET_STC
mdefine_line|#define DMX_GET_STC              _IOWR(&squot;o&squot;,50,struct dmx_stc)
macro_line|#endif /*_DVBDMX_H_*/
eof
