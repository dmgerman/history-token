multiline_comment|/*&n; * IEEE 1394 for Linux&n; *&n; * kernel ISO transmission/reception&n; *&n; * Copyright (C) 2002 Maas Digital LLC&n; *&n; * This code is licensed under the GPL.  See the file COPYING in the root&n; * directory of the kernel sources for details.&n; */
macro_line|#ifndef IEEE1394_ISO_H
DECL|macro|IEEE1394_ISO_H
mdefine_line|#define IEEE1394_ISO_H
macro_line|#include &quot;hosts.h&quot;
macro_line|#include &quot;dma.h&quot;
multiline_comment|/* high-level ISO interface */
multiline_comment|/* This API sends and receives isochronous packets on a large,&n;   virtually-contiguous kernel memory buffer. The buffer may be mapped&n;   into a user-space process for zero-copy transmission and reception.&n;&n;   There are no explicit boundaries between packets in the buffer. A&n;   packet may be transmitted or received at any location. However,&n;   low-level drivers may impose certain restrictions on alignment or&n;   size of packets. (e.g. in OHCI no packet may cross a page boundary,&n;   and packets should be quadlet-aligned)&n;*/
multiline_comment|/* Packet descriptor - the API maintains a ring buffer of these packet&n;   descriptors in kernel memory (hpsb_iso.infos[]).  */
DECL|struct|hpsb_iso_packet_info
r_struct
id|hpsb_iso_packet_info
(brace
multiline_comment|/* offset of data payload relative to the first byte of the buffer */
DECL|member|offset
id|__u32
id|offset
suffix:semicolon
multiline_comment|/* length of the data payload, in bytes (not including the isochronous header) */
DECL|member|len
id|__u16
id|len
suffix:semicolon
multiline_comment|/* (recv only) the cycle number (mod 8000) on which the packet was received */
DECL|member|cycle
id|__u16
id|cycle
suffix:semicolon
multiline_comment|/* (recv only) channel on which the packet was received */
DECL|member|channel
id|__u8
id|channel
suffix:semicolon
multiline_comment|/* 2-bit &squot;tag&squot; and 4-bit &squot;sy&squot; fields of the isochronous header */
DECL|member|tag
id|__u8
id|tag
suffix:semicolon
DECL|member|sy
id|__u8
id|sy
suffix:semicolon
)brace
suffix:semicolon
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
multiline_comment|/* a function to be called (from interrupt context) after&n;           outgoing packets have been sent, or incoming packets have&n;           arrived */
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
multiline_comment|/* wait for buffer space */
DECL|member|waitq
id|wait_queue_head_t
id|waitq
suffix:semicolon
DECL|member|speed
r_int
id|speed
suffix:semicolon
multiline_comment|/* IEEE1394_SPEED_100, 200, or 400 */
DECL|member|channel
r_int
id|channel
suffix:semicolon
multiline_comment|/* -1 if multichannel */
multiline_comment|/* greatest # of packets between interrupts - controls&n;&t;   the maximum latency of the buffer */
DECL|member|irq_interval
r_int
id|irq_interval
suffix:semicolon
multiline_comment|/* the buffer for packet data payloads */
DECL|member|data_buf
r_struct
id|dma_region
id|data_buf
suffix:semicolon
multiline_comment|/* size of data_buf, in bytes (always a multiple of PAGE_SIZE) */
DECL|member|buf_size
r_int
r_int
id|buf_size
suffix:semicolon
multiline_comment|/* # of packets in the ringbuffer */
DECL|member|buf_packets
r_int
r_int
id|buf_packets
suffix:semicolon
multiline_comment|/* protects packet cursors */
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
multiline_comment|/* the index of the next packet that will be produced&n;&t;   or consumed by the user */
DECL|member|first_packet
r_int
id|first_packet
suffix:semicolon
multiline_comment|/* the index of the next packet that will be transmitted&n;&t;   or received by the 1394 hardware */
DECL|member|pkt_dma
r_int
id|pkt_dma
suffix:semicolon
multiline_comment|/* how many packets, starting at first_packet:&n;&t;   (transmit) are ready to be filled with data&n;&t;   (receive)  contain received data */
DECL|member|n_ready_packets
r_int
id|n_ready_packets
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
multiline_comment|/* starting cycle for DMA (xmit only) */
DECL|member|start_cycle
r_int
id|start_cycle
suffix:semicolon
multiline_comment|/* cycle at which next packet will be transmitted,&n;&t;   -1 if not known */
DECL|member|xmit_cycle
r_int
id|xmit_cycle
suffix:semicolon
multiline_comment|/* ringbuffer of packet descriptors in regular kernel memory&n;&t; * XXX Keep this last, since we use over-allocated memory from&n;&t; * this entry to fill this field. */
DECL|member|infos
r_struct
id|hpsb_iso_packet_info
op_star
id|infos
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
id|data_buf_size
comma
r_int
r_int
id|buf_packets
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
multiline_comment|/* note: if channel = -1, multi-channel receive is enabled */
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
id|data_buf_size
comma
r_int
r_int
id|buf_packets
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
multiline_comment|/* multi-channel only */
r_int
id|hpsb_iso_recv_listen_channel
c_func
(paren
r_struct
id|hpsb_iso
op_star
id|iso
comma
r_int
r_char
id|channel
)paren
suffix:semicolon
r_int
id|hpsb_iso_recv_unlisten_channel
c_func
(paren
r_struct
id|hpsb_iso
op_star
id|iso
comma
r_int
r_char
id|channel
)paren
suffix:semicolon
r_int
id|hpsb_iso_recv_set_channel_mask
c_func
(paren
r_struct
id|hpsb_iso
op_star
id|iso
comma
id|u64
id|mask
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
comma
r_int
id|tag_mask
comma
r_int
id|sync
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
multiline_comment|/* queue a packet for transmission. &squot;offset&squot; is relative to the beginning of the&n;   DMA buffer, where the packet&squot;s data payload should already have been placed */
r_int
id|hpsb_iso_xmit_queue_packet
c_func
(paren
r_struct
id|hpsb_iso
op_star
id|iso
comma
id|u32
id|offset
comma
id|u16
id|len
comma
id|u8
id|tag
comma
id|u8
id|sy
)paren
suffix:semicolon
multiline_comment|/* wait until all queued packets have been transmitted to the bus */
r_int
id|hpsb_iso_xmit_sync
c_func
(paren
r_struct
id|hpsb_iso
op_star
id|iso
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
multiline_comment|/* check for arrival of new packets immediately (even if irq_interval&n;   has not yet been reached) */
r_int
id|hpsb_iso_recv_flush
c_func
(paren
r_struct
id|hpsb_iso
op_star
id|iso
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
multiline_comment|/* the following are callbacks available to low-level drivers */
multiline_comment|/* call after a packet has been transmitted to the bus (interrupt context is OK)&n;   &squot;cycle&squot; is the _exact_ cycle the packet was sent on&n;   &squot;error&squot; should be non-zero if some sort of error occurred when sending the packet&n;*/
r_void
id|hpsb_iso_packet_sent
c_func
(paren
r_struct
id|hpsb_iso
op_star
id|iso
comma
r_int
id|cycle
comma
r_int
id|error
)paren
suffix:semicolon
multiline_comment|/* call after a packet has been received (interrupt context OK) */
r_void
id|hpsb_iso_packet_received
c_func
(paren
r_struct
id|hpsb_iso
op_star
id|iso
comma
id|u32
id|offset
comma
id|u16
id|len
comma
id|u16
id|cycle
comma
id|u8
id|channel
comma
id|u8
id|tag
comma
id|u8
id|sy
)paren
suffix:semicolon
multiline_comment|/* call to wake waiting processes after buffer space has opened up. */
r_void
id|hpsb_iso_wake
c_func
(paren
r_struct
id|hpsb_iso
op_star
id|iso
)paren
suffix:semicolon
macro_line|#endif /* IEEE1394_ISO_H */
eof
