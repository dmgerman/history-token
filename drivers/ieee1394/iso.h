multiline_comment|/*&n; * IEEE 1394 for Linux&n; *&n; * kernel ISO transmission/reception&n; *&n; * Copyright (C) 2002 Maas Digital LLC&n; *&n; * This code is licensed under the GPL.  See the file COPYING in the root&n; * directory of the kernel sources for details.&n; */
macro_line|#ifndef IEEE1394_ISO_H
DECL|macro|IEEE1394_ISO_H
mdefine_line|#define IEEE1394_ISO_H
macro_line|#include &quot;hosts.h&quot;
macro_line|#include &quot;dma.h&quot;
multiline_comment|/* high-level ISO interface */
multiline_comment|/* per-packet data embedded in the ringbuffer */
DECL|struct|hpsb_iso_packet_info
r_struct
id|hpsb_iso_packet_info
(brace
DECL|member|len
r_int
r_int
id|len
suffix:semicolon
DECL|member|cycle
r_int
r_int
id|cycle
suffix:semicolon
DECL|member|channel
r_int
r_char
id|channel
suffix:semicolon
multiline_comment|/* recv only */
DECL|member|tag
r_int
r_char
id|tag
suffix:semicolon
DECL|member|sy
r_int
r_char
id|sy
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * each packet in the ringbuffer consists of three things:&n; * 1. the packet&squot;s data payload (no isochronous header)&n; * 2. a struct hpsb_iso_packet_info&n; * 3. some empty space before the next packet&n; *&n; * packets are separated by hpsb_iso.buf_stride bytes&n; * an even number of packets fit on one page&n; * no packet can be larger than one page&n; */
DECL|enum|hpsb_iso_type
DECL|enumerator|HPSB_ISO_RECV
DECL|enumerator|HPSB_ISO_XMIT
r_enum
id|hpsb_iso_type
(brace
id|HPSB_ISO_RECV
op_assign
l_int|0
comma
id|HPSB_ISO_XMIT
op_assign
l_int|1
)brace
suffix:semicolon
DECL|struct|hpsb_iso
r_struct
id|hpsb_iso
(brace
DECL|member|type
r_enum
id|hpsb_iso_type
id|type
suffix:semicolon
multiline_comment|/* pointer to low-level driver and its private data */
DECL|member|host
r_struct
id|hpsb_host
op_star
id|host
suffix:semicolon
DECL|member|hostdata
r_void
op_star
id|hostdata
suffix:semicolon
multiline_comment|/* function to be called (from interrupt context) when the iso status changes */
DECL|member|callback
r_void
(paren
op_star
id|callback
)paren
(paren
r_struct
id|hpsb_iso
op_star
)paren
suffix:semicolon
DECL|member|speed
r_int
id|speed
suffix:semicolon
multiline_comment|/* SPEED_100, 200, or 400 */
DECL|member|channel
r_int
id|channel
suffix:semicolon
multiline_comment|/* greatest # of packets between interrupts - controls&n;&t;   the maximum latency of the buffer */
DECL|member|irq_interval
r_int
id|irq_interval
suffix:semicolon
multiline_comment|/* the packet ringbuffer */
DECL|member|buf
r_struct
id|dma_region
id|buf
suffix:semicolon
multiline_comment|/* # of packets in the ringbuffer */
DECL|member|buf_packets
r_int
r_int
id|buf_packets
suffix:semicolon
multiline_comment|/* offset between successive packets, in bytes -&n;&t;   you can assume that this is a power of 2,&n;&t;   and less than or equal to the page size */
DECL|member|buf_stride
r_int
id|buf_stride
suffix:semicolon
multiline_comment|/* largest possible packet size, in bytes */
DECL|member|max_packet_size
r_int
r_int
id|max_packet_size
suffix:semicolon
multiline_comment|/* offset relative to (buf.kvirt + N*buf_stride) at which&n;&t;   the data payload begins for packet N */
DECL|member|packet_data_offset
r_int
id|packet_data_offset
suffix:semicolon
multiline_comment|/* offset relative to (buf.kvirt + N*buf_stride) at which the&n;&t;   struct hpsb_iso_packet_info is stored for packet N */
DECL|member|packet_info_offset
r_int
id|packet_info_offset
suffix:semicolon
multiline_comment|/* the index of the next packet that will be produced&n;&t;   or consumed by the user */
DECL|member|first_packet
r_int
id|first_packet
suffix:semicolon
multiline_comment|/* number of packets owned by the low-level driver and&n;&t;   queued for transmission or reception.&n;&t;   this is related to the number of packets available&n;&t;   to the user process: n_ready = buf_packets - n_dma_packets */
DECL|member|n_dma_packets
id|atomic_t
id|n_dma_packets
suffix:semicolon
multiline_comment|/* how many times the buffer has overflowed or underflowed */
DECL|member|overflows
id|atomic_t
id|overflows
suffix:semicolon
multiline_comment|/* private flags to track initialization progress */
DECL|macro|HPSB_ISO_DRIVER_INIT
mdefine_line|#define HPSB_ISO_DRIVER_INIT     (1&lt;&lt;0)
DECL|macro|HPSB_ISO_DRIVER_STARTED
mdefine_line|#define HPSB_ISO_DRIVER_STARTED  (1&lt;&lt;1)
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* # of packets left to prebuffer (xmit only) */
DECL|member|prebuffer
r_int
id|prebuffer
suffix:semicolon
multiline_comment|/* starting cycle (xmit only) */
DECL|member|start_cycle
r_int
id|start_cycle
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* functions available to high-level drivers (e.g. raw1394) */
multiline_comment|/* allocate the buffer and DMA context */
r_struct
id|hpsb_iso
op_star
id|hpsb_iso_xmit_init
c_func
(paren
r_struct
id|hpsb_host
op_star
id|host
comma
r_int
r_int
id|buf_packets
comma
r_int
r_int
id|max_packet_size
comma
r_int
id|channel
comma
r_int
id|speed
comma
r_int
id|irq_interval
comma
r_void
(paren
op_star
id|callback
)paren
(paren
r_struct
id|hpsb_iso
op_star
)paren
)paren
suffix:semicolon
r_struct
id|hpsb_iso
op_star
id|hpsb_iso_recv_init
c_func
(paren
r_struct
id|hpsb_host
op_star
id|host
comma
r_int
r_int
id|buf_packets
comma
r_int
r_int
id|max_packet_size
comma
r_int
id|channel
comma
r_int
id|irq_interval
comma
r_void
(paren
op_star
id|callback
)paren
(paren
r_struct
id|hpsb_iso
op_star
)paren
)paren
suffix:semicolon
multiline_comment|/* start/stop DMA */
r_int
id|hpsb_iso_xmit_start
c_func
(paren
r_struct
id|hpsb_iso
op_star
id|iso
comma
r_int
id|start_on_cycle
comma
r_int
id|prebuffer
)paren
suffix:semicolon
r_int
id|hpsb_iso_recv_start
c_func
(paren
r_struct
id|hpsb_iso
op_star
id|iso
comma
r_int
id|start_on_cycle
)paren
suffix:semicolon
r_void
id|hpsb_iso_stop
c_func
(paren
r_struct
id|hpsb_iso
op_star
id|iso
)paren
suffix:semicolon
multiline_comment|/* deallocate buffer and DMA context */
r_void
id|hpsb_iso_shutdown
c_func
(paren
r_struct
id|hpsb_iso
op_star
id|iso
)paren
suffix:semicolon
multiline_comment|/* N packets have been written to the buffer; queue them for transmission */
r_int
id|hpsb_iso_xmit_queue_packets
c_func
(paren
r_struct
id|hpsb_iso
op_star
id|xmit
comma
r_int
r_int
id|n_packets
)paren
suffix:semicolon
multiline_comment|/* N packets have been read out of the buffer, re-use the buffer space */
r_int
id|hpsb_iso_recv_release_packets
c_func
(paren
r_struct
id|hpsb_iso
op_star
id|recv
comma
r_int
r_int
id|n_packets
)paren
suffix:semicolon
multiline_comment|/* returns # of packets ready to send or receive */
r_int
id|hpsb_iso_n_ready
c_func
(paren
r_struct
id|hpsb_iso
op_star
id|iso
)paren
suffix:semicolon
multiline_comment|/* returns a pointer to the payload of packet &squot;pkt&squot; */
r_int
r_char
op_star
id|hpsb_iso_packet_data
c_func
(paren
r_struct
id|hpsb_iso
op_star
id|iso
comma
r_int
r_int
id|pkt
)paren
suffix:semicolon
multiline_comment|/* returns a pointer to the info struct of packet &squot;pkt&squot; */
r_struct
id|hpsb_iso_packet_info
op_star
id|hpsb_iso_packet_info
c_func
(paren
r_struct
id|hpsb_iso
op_star
id|iso
comma
r_int
r_int
id|pkt
)paren
suffix:semicolon
macro_line|#endif /* IEEE1394_ISO_H */
eof
